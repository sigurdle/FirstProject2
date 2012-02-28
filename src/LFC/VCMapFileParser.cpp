#include "stdafx.h"
#include "LFC.h"
#include "VCMapFileParser.h"

namespace System
{

int VCMapFileParser::Parse(StringIn filename, IMapFileDataReceiver* receiver)
{
	VERIFY(receiver);

	CString cfilename(filename);

	FILE* fp;
	errno_t err = fopen_s(&fp, cfilename, "r");
	if (fp)
	{
		try
		{
			char line[2048];

			if (fgets(line, _countof(line), fp) == NULL)
			{
				raise(Exception("error: empty file"));
			}

			fgets(line, _countof(line), fp);

			fscanf_s(fp, " Timestamp is");
			fgets(line, _countof(line), fp);

			DWORD load_address;
			int n = fscanf_s(fp, " Preferred load address is %x\n", &load_address);
			if (n != 1)
			{
				raise(Exception("error in map file"));
			}

			receiver->OnLoadAddress(load_address);
			fgets(line, _countof(line), fp);

			while (1)
			{
				fgets(line, _countof(line), fp);

				int section;
				int section_offset;
				int length;
				char name[256];
				char classname[256];
				int n = sscanf_s(line, " %x:%x %xH %s %s", &section, &section_offset, &length, name, sizeof(name), classname, sizeof(classname));
				if (n == EOF)
					break;

				if (n != 5)
				{
					raise(Exception("error: %x:%x %xH %s %s"));
				}

				receiver->OnGroup(section, section_offset, length, name, classname);
			}

			fgets(line, _countof(line), fp);
			fgets(line, _countof(line), fp);

			uint nsymbols = 0;
			while (!feof(fp))
			{
				fgets(line, _countof(line), fp);

				int section;
				int section_offset;
				int flat_address;
				char symbolname[1024];
				//char objfilename[512];

				int n = sscanf_s(line, " %x:%x %s %x", &section, &section_offset, symbolname, sizeof(symbolname), &flat_address/*, objfilename*/);
				if (n == EOF)
					break;

				if (n != 4)
				{
					IO::StringWriter str;
					str << "Parse error: " << line;

					raise(Exception(str.str()));
				}

				receiver->OnSymbol(section, section_offset, flat_address, symbolname, NULL);
				++nsymbols;
			}

			fclose(fp);
			return 0;
		}
		catch (Exception* e)
		{
			UNREFERENCED_PARAMETER(e);

			fclose(fp);
			_unlink(cfilename);	// Delete file
		}
	}

	return -1;
}

}	// System
