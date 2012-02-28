#include "stdafx.h"
#include "../Include/AmigaHunkParser.h"

using namespace std;
using namespace System;
using namespace System::IO;

static long fget32(Stream* pStream)
{
	long v;
	pStream->Read(&v, 4);
	return BigEndian32(v);
}

AmigaHunkParser::AmigaHunkParser()
{
	stab = NULL;
	nstabs = 0;

	m_pDebugInfo = NULL;
}

AmigaHunkParser::~AmigaHunkParser()
{
}

uint AmigaHunkParser::GetNumberOfSections()
{
	return header.num_hunks;
}

uint AmigaHunkParser::GetNumberOfSymbols()
{
	return m_symbols.GetSize();
}

ObjectSymbol* AmigaHunkParser::GetSymbol(uint index)
{
	return m_symbols[index];
}

ULONG AmigaHunkParser::GetDataSize(uint nSection)
{
	return m_hunks[nSection].m_size;
}

uint8* AmigaHunkParser::GetData(uint nSection)
{
	return m_hunks[nSection].m_data;
}

long AmigaHunkParser::Read(Stream* stream)
{
//	pStream->Seek(0, DataStreamReader::end);
	ULONG filesize = stream->GetSize();
//	pStream->Seek(0, DataStreamReader::begin);

	/*
	fseek(fp, 0, SEEK_END);
	long filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	*/

	stream->Read(&header, sizeof(HUNK_Header));

	header.num_hunks = BigEndian32(header.num_hunks);
	header.pad0 = BigEndian32(header.pad0);
	header.first = BigEndian32(header.first);
	header.last = BigEndian32(header.last);

	for (uint i = 0; i < header.num_hunks; i++)
	{
		Hunk hunk;
		hunk.m_size = fget32(stream);
		hunk.m_size *= 4;

		m_hunks.Add(hunk);

	//	printf("\thunk size: %d bytes\n", hunk.m_size*4);
	}

	int nhunk = 0;
//	for (i = 0; i < totalhunks; i++)

	while (1)
	{
	//	CHunk& hunk = Hunks[nhunk];

		uint32 hunk_ID = fget32(stream);
	//	if (hunk_ID == HUNK_END)
	//		break;

#if 0
		char * str = GetHunkStr(hunk_ID);

		printf("%s\n", str);
#endif

		long pos = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (pos >= filesize)
			break;

		if ((hunk_ID & ID_MASK) == HUNK_CODE)
		{
			uint32 codelongs = fget32(stream);
		//	ATLASSERT(codelongs == hunk.m_size);

			uint8* data = new uint8[codelongs*4];
			if (data)
			{
				stream->Read(data, codelongs*4);

				m_hunks[nhunk].m_data = data;

				/*
				ULONG size = min(codelongs*4, 4096);
				pass2_CODE(data, size, NULL);//0, NULL);
				delete [] data;
				*/
			}
		}
		else if ((hunk_ID & ID_MASK) == HUNK_RELOC32)
		{
			uint32 offsets = fget32(stream);

			while (offsets)
			{
				uint32 hunk_number = fget32(stream);
			//	printf("hunk_number: %d\n", hunk_number);

				for (uint i = 0; i < offsets; ++i)
				{
					uint32 offset = fget32(stream);
				//	printf("\toffset: %d\n", offset);
				}

				offsets = fget32(stream);
			}
		}
		else if ((hunk_ID & ID_MASK) == HUNK_DATA)
		{
			uint32 longs = fget32(stream);
			stream->Seek(longs*4, System::IO::STREAM_SEEK_CUR);

		//	printf("\t%d bytes\n", longs*4);
		}
		else if ((hunk_ID & ID_MASK) == HUNK_SYMBOL)
		{
		//	ULONG longs = fget32(fp);
			uint32 size = fget32(stream);//*hunk_ptr++;

			while (size)
			{
		#if 0
				printf("size: %d\n", size);
				struct SymbolNode	*symnode;

				if (symnode = malloc(sizeof(struct SymbolNode)))
				{
					symnode->SymPtr = hunk_ptr-1;
					AddTail((struct List *)&SymbolList, (struct Node *)symnode);
				}
		#endif
			//	long v = fget(fp);
				//long s[2000];
				//s[0] = size;
				uint8* data = new uint8[size*4+4];
				stream->Read(data, size*4+4);
			//	fread(s, size*4+4, 1, fp);
			//	fseek(fp, size*4, SEEK_CUR);

			//	fseek(fp, size*4, SEEK_CUR);

			//	long poff = BigEndian32(*s);
				long offset = BigEndian32(((uint32*)data)[size]);
			//	long offset = fget32(fp);
			//	printf("%s / offset: %x\n", (char*)data, offset);

				if (nhunk == 0)	// TODO
				{
					ObjectSymbol* pSymbol = new ObjectSymbol;
					pSymbol->n_name = _strdup((char*)data);
					pSymbol->n_value = offset;

					m_symbols.Add(pSymbol);
				}
			//	fget32(fp);

			//	hunk_ptr += size;
			//	hunk_ptr++;

				size = fget32(stream);//*hunk_ptr++;
			}

		}
		else if ((hunk_ID & ID_MASK) == HUNK_BSS)
		{
			uint32 longs = fget32(stream);
		}
		else if ((hunk_ID & ID_MASK) == HUNK_DEBUG)
		{
			uint32 longs = fget32(stream);
			uint8* buffer = new uint8[longs*4];

			stream->Read(buffer, longs*4);

			long stroffset = ((long*)buffer)[1];
			stroffset = BigEndian32(stroffset);

			stab = (nlist*)(buffer + 12);
			stabstr = (char*)(buffer + 12 + stroffset);

			nstabs = stroffset / sizeof(nlist);

			int last_fun_address = 0;

			for (int i = 0; i < nstabs; i++)
			{
				nlist* n = &stab[i];
				n->n_un.n_strx = BigEndian32(n->n_un.n_strx);
				n->n_value = BigEndian32(n->n_value);
				n->n_desc = BigEndian16(n->n_desc);

				n->n_un.n_name = stabstr + n->n_un.n_strx;

				if (n->n_type == N_SO)
				{
					//printf("name: \"%s\"\n", n->n_un.n_name);
				}
				/*
				else if (n.n_type == N_FUN)
				{
					last_fun_address = n.n_value;
				}
				else if (n.n_type == N_SOL)
				{
					printf("name: \"%s\"\n", name);
				}
				else if (n.n_type == N_SLINE)
				{
					printf("%x - %d\n", n.n_value, n.n_desc);
				}
				*/
			}
		}
		else if (hunk_ID & HUNKF_ADVISORY)	// Can be skipped
		{
			uint32 longs = fget32(stream);
			stream->Seek(longs*4, System::IO::STREAM_SEEK_CUR);

		//	printf("size: %d(%x)\n", longs*4, longs*4);
		}
		else if ((hunk_ID & ID_MASK) == HUNK_END)
		{
			// End of current segment
			nhunk++;
		}
		else
		{
	//		printf("Unrecognized hunk %x\n", hunk_ID);
		}
	}

	return 0;
}

DebugInfo* AmigaHunkParser::GetDebugInfo(Scope* pGlobalScope)
{
	if (m_pDebugInfo == NULL)
	{
		m_pDebugInfo = new StabDebugInfo;
		m_pDebugInfo->m_pGlobalScope = pGlobalScope;
#if 0
		m_pDebugInfo->FromStab(0, stab, nstabs);
#endif
	}

	return m_pDebugInfo;
}
