#include "stdafx.h"

#include "IFFParser.h"

namespace System
{
namespace MediaShow
{

void PlanarToChunkyScanline(uint8* bits, uint8 bitcount, int width, uint8* planes[], uint8 nplanes, uint32 camg, ColorRegister *colors)
{
	if (bitcount == 1)	// It's the same as windows internal format
	{
		ASSERT(nplanes == 1);

		memcpy(bits, planes[0], RowBytes(width));
	}
	else
	{
		uint8* planeptr[MAXPLANES];
		uint8	plane;
		uint8	bit = 7;

		for (plane = 0; plane < nplanes; plane++)
			planeptr[plane] = planes[plane];

	//	BYTE red = 0, green = 0, blue = 0;			// Used for AMIGA HAM (Hold And Modify)
		uint8 rgbcolor[3];
		rgbcolor[0] = 0;
		rgbcolor[1] = 0;
		rgbcolor[2] = 0;

		//BYTE*			rgbbits = (BYTE*)bits;	// As well
		//WORD*			rgbbits2 = (WORD*)(bits);		// For 16bit

		for (int x = 0; x < width; x++)
		{
			uint8 colorindex = 0;
			uint8 bitmask = 1<<bit;

			if (nplanes < 24)
			{
				for (plane = 0; plane < nplanes; plane++)
				{
					if (*planeptr[plane] & bitmask) colorindex |= (1<<plane);
				}
			}
			else
			{
				rgbcolor[0] = rgbcolor[1] = rgbcolor[2] = 0;

				for (plane = 0; plane < 8; plane++)
				{
					if (*planeptr[plane] & bitmask) rgbcolor[0] |= (1<<plane);
				}

				for (plane = 0; plane < 8; plane++)
				{
					if (*planeptr[8+plane] & bitmask) rgbcolor[1] |= (1<<plane);
				}
				
				for (plane = 0; plane < 8; plane++)
				{
					if (*planeptr[16+plane] & bitmask) rgbcolor[2] |= (1<<plane);
				}
			}

			if (bitcount <= 4)
			{
				if (x & 1)
				{
					*bits |= colorindex;
					bits++;
				}
				else
				{
					*bits = colorindex<<4;
				}
			}
			else if (bitcount <= 8)
			{
				*bits++ = colorindex;
			}
			else if (bitcount >= 16)
			{
				if (camg & AMIGA_HAM)	// HAM
				{
					if (nplanes == 6)	// HAM6
					{
						uint8 modifybits = colorindex & 0x30;	// Mask bits 4 and 5

						if (modifybits == 0x20)			// Modify red
						{
							rgbcolor[0] = ((colorindex)<<4) | (colorindex & ~0x30);
						}
						else if (modifybits == 0x30)	// Modify green
						{
							rgbcolor[1] = ((colorindex)<<4) | (colorindex & ~0x30);
						}
						else if (modifybits == 0x10)	// Modify blue
						{
							rgbcolor[2] = ((colorindex)<<4) | (colorindex & ~0x30);
						}
						else	// Absolute color
						{
							ASSERT(colorindex < 16);
							*(ColorRegister*)rgbcolor = colors[colorindex];
						}
					}
					else	// HAM8
					{
						uint8 modifybits = colorindex & 0xc0;	// Mask bits 6 and 7

						if (modifybits == 0x80)			// Modify red
						{
							rgbcolor[0] = ((colorindex & ~0xc0)<<2);// | (colorindex & ~0xc0);
						}
						else if (modifybits == 0xc0)	// Modify green
						{
							rgbcolor[1] = ((colorindex & ~0xc0)<<2);// | (colorindex & ~0xc0);
						}
						else if (modifybits == 0x40)	// Modify blue
						{
							rgbcolor[2] = ((colorindex & ~0xc0)<<2);// | (colorindex & ~0xc0);
						}
						else	// Absolute color
						{
							ASSERT(colorindex < 64);
							*(ColorRegister*)rgbcolor = colors[colorindex];
						}
					}

					if (bitcount == 16)
					{
						*(uint16*)bits =	((uint16)(rgbcolor[0] >> 3) << 10) |
										((uint16)(rgbcolor[1] >> 3) << 5) |
										(rgbcolor[2] >> 3);
						bits += 2;
					}
					else	// 24
					{
						bits[2] = rgbcolor[0];
						bits[1] = rgbcolor[1];
						bits[0] = rgbcolor[2];

						bits += bitcount/8;
					}
				}
				else if (nplanes == 24)	// 24-bits ILBM
				{
					bits[2] = rgbcolor[0];
					bits[1] = rgbcolor[1];
					bits[0] = rgbcolor[2];

					bits += bitcount/8;
				}
				else
				{
					bits[2] = colors[colorindex].Red;
					bits[1] = colors[colorindex].Green;
					bits[0] = colors[colorindex].Blue;

					bits += bitcount/8;
				}
			}

			if (bit == 0)
			{
				for (plane = 0; plane < nplanes; plane++)
					planeptr[plane]++;

				bit = 7;
			}
			else
				bit--;
		}
	}
}

void ChunkyToPlanar(uint8* bits, uint8* planes[], uint8 bitcount, uint8 nplanes, int width, int height)
{
	int srcRowBytes = ROWBYTES_DWORDAligned(width, bitcount);
	int destRowBytes = RowBytes(width);

	for (int row = 0; row < height; row++)
	{
		uint8*	bitsptr = &bits[srcRowBytes*row];
		uint8*	plane[24];

		for (uint8 i = 0; i < bitcount; i++)
			plane[i] = planes[i]+destRowBytes*row;

		if (nplanes == 1 && bitcount == 1)
		{
			memcpy(plane[0], bitsptr, destRowBytes);
		}
		else
		{
			uint8	bit = 7;

			for (int col = 0; col < width; col++)
			{
				uint8	index;	// Color index
				uint8	red, green, blue;	// For 24bit

				if (bitcount == 8)
				{
					index = *bitsptr++;
				}
				else if (bitcount == 4)
				{
					if (col & 1)
						index = *bitsptr++ & 0x0f;
					else
						index = *bitsptr>>4;
				}
				else if (bitcount == 24)
				{
					blue = *bitsptr++;
					green = *bitsptr++;
					red = *bitsptr++;
				}

				uint8	bitmask = 1<<bit;

				if (bitcount < 24)
				{
					for (uint8 i = 0; i < nplanes; i++)
					{
						if (index & (1<<i))
							*plane[i] |= bitmask;
						else
							*plane[i] &= ~bitmask;
					}
				}
				else
				{
					uint8	i;
					for (i = 0; i < 8; i++)
					{
						if (red & (1<<i))
							*plane[i] |= bitmask;
						else
							*plane[i] &= ~bitmask;
					}

					for (i = 0; i < 8; i++)
					{
						if (green & (1<<i))
							*plane[8+i] |= bitmask;
						else
							*plane[8+i] &= ~bitmask;
					}

					for (i = 0; i < 8; i++)
					{
						if (blue & (1<<i))
							*plane[16+i] |= bitmask;
						else
							*plane[16+i] &= ~bitmask;
					}
				}

				if (bit == 0)
				{
					bit = 7;

					for (uint8 i = 0; i < nplanes; i++)
						plane[i]++;
				}
				else
					bit--;
			}
		}
	}
}

}	// MediaShow
}
