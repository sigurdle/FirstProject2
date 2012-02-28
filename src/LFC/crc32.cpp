#include "stdafx.h"
#include "LFC.h"

namespace System
{
using namespace IO;

uint32 crc_table[256];
bool crc_table_computed = false;

/* Make the table for a fast CRC. */
void make_crc_table()
{
	unsigned long c;
	int n, k;
	
	for (n = 0; n < 256; n++)
	{
		c = (unsigned long) n;
		for (k = 0; k < 8; k++)
		{
			if (c & 1)
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		crc_table[n] = c;
	}
	crc_table_computed = true;
}

LFCEXT uint32 CalculateCRC32(Stream& stream, uint32 crc)
{
	if (!crc_table_computed)
	{
		make_crc_table();
	}

	ubyte buf[256];

	while (1)
	{
		size_t nRead = stream.Read(buf, 256);
		for (size_t i = 0; i < nRead; ++i)
		{
			crc = crc_table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
		}

		if (nRead < 256)
			break;
	}

	return crc;
}

}
