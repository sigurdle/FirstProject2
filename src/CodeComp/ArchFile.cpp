#include "stdafx.h"
#include "ArchFile.h"

using namespace std;

namespace System
{
using namespace IO;

static long fget32(Stream& pStream)
{
	long v;
	pStream.Read(&v, 4);
	return BigEndian32(v);
}

uint ArchiveHeader::GetHeaderSize()
{
	uint _Size = 0;
	for (int i = 0; i < 10; i++)
	{
		if (Size[i] >= '0' && Size[i] <= '9')
		{
			_Size *= 10;
			_Size += Size[i]-'0';
		}
		else
			break;
	}

	return _Size;
}

ArchFile::ArchFile()
{
	m_nsymboldefs = NULL;
	m_symdefs = NULL;
	m_strbuffer = NULL;
}

ArchFile::~ArchFile()
{
	if (m_strbuffer)
	{
		delete[] m_strbuffer;
	}
}

uint ArchFile::GetNumberOfSymbols()
{
	return symbols.size();
}

long ArchFile::Read(IO::Stream& pStream)
{
	uint8 signature[8];
	pStream.Read(signature, 8);

	if (memcmp(signature, "!<arch>\n", 8))
		return -1;

	int linkerMember = 0;

	char* namemap = NULL;

	while (1)
	{
		ArchiveHeader header;
		if (pStream.Read(&header, sizeof(header)) != sizeof(header))
		{
			break;
		}

		if (header.End[0] != 0x60 || header.End[1] != '\n')
		{
		//	printf("Corrupt file\n");
			return -1;
		}

		uint Size = header.GetHeaderSize();

		long startpos = pStream.Seek(0, System::IO::STREAM_SEEK_CUR);

	//	printf("Member Name: %.16s\n", header.Name);

		if (!strncmp(header.Name, "__.SYMDEF", 9))
		{
			uint32 symsize = fget32(pStream);
			m_nsymboldefs = symsize / 8;
			m_symdefs = new SYMDEF[m_nsymboldefs];
			pStream.Read(m_symdefs, symsize);
			{
				for (uint i = 0; i < m_nsymboldefs; i++)
				{
					m_symdefs[i].fileoffset = BigEndian32(m_symdefs[i].fileoffset);
					m_symdefs[i].nameindex = BigEndian32(m_symdefs[i].nameindex);
				}
			}

			ULONG strsize = fget32(pStream);
			m_strbuffer = new char[strsize];
			pStream.Read(m_strbuffer, strsize);

			for (uint i = 0; i < m_nsymboldefs; i++)
			{
			//	TRACE("%s\n", m_strbuffer + m_symdefs[i].nameindex);
				m_symdefmap[m_strbuffer + m_symdefs[i].nameindex] = m_symdefs[i].fileoffset;
			}
		}
		else if (!strncmp(header.Name, "//", 2) || !strncmp(header.Name, "ARFILENAMES/", 12))
		{
			if (namemap != NULL)
				THROW(-1);

			namemap = new char[Size];
			pStream.Read(namemap, Size);

			char* p = (char*)namemap;
			char* end = p + Size;
			while (p < end)
			{
				while (*p != '\n')
				{
					p++;
				}

			//	TRACE("%s\n", name.c_str());

				*p = 0;
				p++;
			}
		}
		else if (header.Name[0] == ' ')
		{
			if (namemap == NULL)
			{
				THROW(-1);
			}

			int n = str2int(header.Name+1);

		//	TRACE("%s, %d\n", namemap+n, Size);

			Member member;
			member.name = string_copy(namemap+n);
			member.Offset = pStream.Seek(0, System::IO::STREAM_SEEK_CUR);
			member.Size = Size;

			m_members.Add(member);
		}
		else if (header.Name[0] == '#')
		{
			//printf("\n");
//			ASSERT(0);
		}
		else if (header.Name[0] == '/')
		{
			if (linkerMember == 0)
			{
				uint NumberOfSymbols = fget32(pStream);
			//	fread(&NumberOfSymbols, 1, 4, fp);
				uint32* Offsets = new uint32[NumberOfSymbols];

				int i;

				for (i = 0; i < NumberOfSymbols; i++)
				{
					Offsets[i] = fget32(pStream);//, 1, NumberOfSymbols*4, fp);
				}

				for (i = 0; i < NumberOfSymbols; i++)
				{
					String str;
					while (1)
					{
						char c;
						if (pStream.Read(&c, 1) != 1)
							break;

						if (c == 0)
							break;

						ASSERT(0);
#if 0
						str = str->Append(c);
#endif
					}

				//	TRACE("%s\n", str.c_str());

					symbols.insert(symbolmap::value_type(str, Offsets[i]));
				}

				linkerMember = 1;
			}
		}
		else
		{
			int i = 16;
			while (header.Name[i-1] == ' ')
			{
				i--;
			}
			header.Name[i] = '\0';

			Member member;
			member.name = string_copy(header.Name);
			member.Offset = pStream.Seek(0, System::IO::STREAM_SEEK_CUR);
			member.Size = Size;

			m_members.Add(member);

		//	TRACE("%s, %d\n", header.Name, Size);
		}

		if (pStream.Seek(0, System::IO::STREAM_SEEK_CUR) > startpos + Size)
		{
		//	printf("Read past archive member\n");
			return -2;
		}
		if (Size & 1) Size += 1;	// even
		pStream.Seek(startpos + Size, System::IO::STREAM_SEEK_SET);
	}

	return 0;
}

}	// System
