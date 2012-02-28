#include "stdafx.h"
#include "IFFParser.h"

namespace System
{
namespace MediaShow
{

bool UnpackRowByteRun1(char** pSource, char** pDest, /*WORD srcBytes,*/ int dstBytes)
{
	char* source = *pSource;
	char* dest = *pDest;

	bool	error = true;	// Assume error until we make it through the loop

	while (dstBytes > 0)
	{
	//	if ((srcBytes -= 1) < 0) goto ErrorExit;

		int n = *source++;

		if (n >= 0)
		{
			n += 1;

		 //	if ((srcBytes -= n) < 0) goto ErrorExit;
			if ((dstBytes -= n) < 0) goto ErrorExit;

			while (n--)
			{
				*dest++ = *source++;
			}
		}
		else if (n != -128)
		{
			n = -n + 1;

		//	if ((srcBytes -= 1) < 0) goto ErrorExit;
			if ((dstBytes -= n) < 0) goto ErrorExit;

			char c = *source++;

			while (n--)
			{
				*dest++ = c;
			}
		}
	}

	error = false;	// Success

ErrorExit:

// Update the pointers
	*pSource = source;
	*pDest = dest;

	return error;
}

/**************************************************************************

	Animation opcode decoders

**************************************************************************/

bool decode_op5(BitMapHeader *bmhd,
					 AnimationHeader *anhd,
					 LONG deltadata[],
					 uint8* planes[])
{
	bool	error = true;

	uint8* in, *planeptr, *dest;
	uint8 	op, op_count, count, byt;
	int	xor_mode = (anhd->ah_Flags & 2);
	uint16 linebytes = RowBytes(bmhd->bmh_Width);

//	TRACE("XOR: %s\n", (xor_mode)? "Yes": "No");

	for (uint8 i = 0; i < bmhd->bmh_Planes; i++)
	{
		if (deltadata[i])
		{
			in = (uint8*)deltadata+BigEndian32(deltadata[i]);
			planeptr = planes[i];

			uint16	lbcount = linebytes;

			while (lbcount--)
			{
				op_count = *in++;
				dest = planeptr++;

				LONG	row = bmhd->bmh_Height;

				while (op_count--)
				{
					op = *in++;

					if (op & 0x80)    // high bit set
					{
						op &= 0x7f;    // mask down

						if ((row -= op) < 0) goto ErrorExit;

						if (xor_mode)
						{
							while (op--)
							{
								*dest ^= *in++;
								dest += linebytes;
							}
						}
						else
						{
							while (op--)
							{
								*dest = *in++;
								dest += linebytes;
							}
						}
					}
					else if (op == 0) // same op
					{
						count = *in++;
						byt = *in++;

						if ((row -= count) < 0) goto ErrorExit;

						if (xor_mode)
						{
							while (count--)
							{
								*dest ^= byt;
								dest += linebytes;
							}
						}
						else
						{
							while (count--)
							{
								*dest = byt;
								dest += linebytes;
							}
						}
					}
					else  // skip op
					{
						if ((row -= op) < 0) goto ErrorExit;
						dest += linebytes*op;
					}
				}
			}
		}
	}

	error = false;

ErrorExit:

	return error;
}

bool decode_op7(BitMapHeader *bmhd,
					 AnimationHeader *anhd,
					 LONG deltadata[],
					 uint8* planes[])
{
	bool	error = true;	// Assume error until we make it through the loop

	int xor_mode = (anhd->ah_Flags & 2);
	int long_mode = (anhd->ah_Flags & 1);
	int mode = xor_mode | long_mode;

	uint16	item_size = (long_mode)? 4: 2;
	uint16	linebytes = RowBytes(bmhd->bmh_Width);

	for (uint8 i = 0; i < bmhd->bmh_Planes; i++)
	{
		if (deltadata[i])
		{
			uint8*	oplist   = (uint8*)deltadata+BigEndian32(deltadata[i]);
			uint8*	datalist = (uint8*)deltadata+BigEndian32(deltadata[i+8]);
			uint8*	planeptr = planes[i];

			int	lbcount;

			if (long_mode)
				lbcount = linebytes>>2;
			else
				lbcount = linebytes>>1;

			while (lbcount--)
			{
				uint8	op_count = *oplist++;

				uint8*	dest = planeptr;
				planeptr += item_size;

				int	row = bmhd->bmh_Height;

				while (op_count--)
				{
					uint8	op = *oplist++;

					if (op & 0x80)    // high bit set
					{
						op &= 0x7f;    // mask down

						if ((row -= op) < 0) goto ErrorExit;

						if (xor_mode)
						{
							while (op--)
							{
								if (long_mode)
									*(uint32*)dest ^= *(uint32*)datalist;
								else
									*(uint16*)dest ^= *(uint16*)datalist;

								datalist += item_size;
								dest += linebytes;
							}
						}
						else
						{
							while (op--)
							{
								if (long_mode)
									*(uint32*)dest = *(uint32*)datalist;
								else
									*(uint16*)dest = *(uint16*)datalist;

								datalist += item_size;
								dest += linebytes;
							}
						}
					}
					else if (op == 0) // same op
					{
						uint32	dataitem;

						uint8	count = *oplist++;

						if ((row -= count) < 0) goto ErrorExit;

						if (long_mode)
							dataitem = *(uint32*)datalist;
						else
							dataitem = *(uint16*)datalist;

						datalist += item_size;

						if (xor_mode)
						{
							if (long_mode)
							{
								while (count--)
								{
									*(uint32*)dest ^= dataitem;
									dest += linebytes;
								}
							}
							else
							{
								while (count--)
								{
									*(uint16*)dest ^= dataitem;
									dest += linebytes;
								}
							}
						}
						else
						{
							if (long_mode)
							{
								while (count--)
								{
									*(uint32*)dest = dataitem;
									dest += linebytes;
								}
							}
							else
							{
								while (count--)
								{
									*(uint16*)dest = dataitem;
									dest += linebytes;
								}
							}
						}
					}
					else  // skip op
					{
						if ((row -= op) < 0) goto ErrorExit;
						dest += linebytes*op;
					}
				}
			}
		}
	}

	error = false;	// Success

ErrorExit:

	return error;
}

}	// MediaShow
}
