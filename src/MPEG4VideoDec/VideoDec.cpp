#include "stdafx.h"
#include "MPEG4VideoDec.h"

#include <cstdio>

#if AMIGA
#define TRACE printf
#endif

#include "VideoDec.h"

//#include "MP4File.h"
//#include "MP4Track.h"

//#include "../gm/GraphicsGems.h"

#include "vlctables.h"

#define LMEDIAEXT DECLSPEC_DLLIMPORT

namespace System
{
LMEDIAEXT void init_idct(void);
LMEDIAEXT void idct(short *block);
LMEDIAEXT int GetNBits(int range);

namespace Mpeg4
{

MacroBlock::MacroBlock()
{
	m_intra = 0;

	std::memset(QF, 0, sizeof(QF));
	std::memset(F, 0, sizeof(F));
	std::memset(motion_vector, 0, sizeof(motion_vector));
}

/* take sign of a, either -1, 0, or 1 */
#define ZSGN(a)		(((a)<0) ? -1 : (a)>0 ? 1 : 0)	

/* take binary sign of a, either -1, or 1 if >= 0 */
#define SGN(a)		(((a)<0) ? -1 : 1)

#define sign(x) ((x) > 0 ? 1 : -1)					// see p.22/H.263

int Median(int v1, int v2, int v3)
{
	if (v1 < v2)
	{
		if (v3 < v1)
			return v1;
		else if (v3 < v2)
			return v3;
		else
			return v2;
	}
	else
	{
		if (v3 > v1)
			return v1;
		else if (v3 > v2)
			return v3;
		else
			return v2;
	}
}

template<class T>
int inline Sign(T a)
{
	return ZSGN(a);
}

int divroundnearest(int i, int iDenom)
{
	ASSERT(iDenom > 0);

	if(i >= 0)
		return (i+(iDenom>>1))/iDenom;
	else
		return (i-(iDenom>>1))/iDenom;
}

struct vtab2
{
	int len;
	uint32 mask;
	int index;
};

inline int getvariablebits(System::IO::CBitStream32* pBitStream, const vtab_byte table[], int maxlen)
{
	int value = pBitStream->looknbits(maxlen);
	pBitStream->skipnbits(table[value].len);
	return table[value].index;
}

/*
VLC table for mcbpc for I-VOPs and S-VOPs with low_latence_sprite_enable==1 and
sprite_transmit_mode==”piece”
*/

char* str_table_B6[] =
{
"1",// 3 00
"001",// 3 01
"010",// 3 10
"011",// 3 11
"0001",// 4 00
"000001",// 4 01
"000010",// 4 10
"000011",// 4 11
"000000001",// Stuffing --
NULL
};

extern vtab_byte table_B6[512];

/*
static vtab2 table_B6[] =
{
1, 1, 0,
3, 2, 2,
3, 3, 3,
3, 1, 1,
4, 1, 4,
6, 2, 6,
6, 3, 7,
6, 1, 5,
9, 1, 8,
0
};
*/

/*
VLC table for mcbpc for P-VOPs and S-VOPs with low_latence_sprite_enable==1 and
sprite_transmit_mode==”update”, and S(GMC)-VOPs
*/

char* str_table_B7[] =
{
"1",// 0 00
"0011",// 0 01
"0010",// 0 10
"000101",// 0 11
"011",// 1 00
"0000111",// 1 01
"0000110",// 1 10
"000000101",// 1 11
"010",// 2 00
"0000101",// 2 01
"0000100",// 2 10
"00000101",// 2 11
"00011",// 3 00
"00000100",// 3 01
"00000011",// 3 10
"0000011",// 3 11
"000100",// 4 00
"000000100",// 4 01
"000000011",// 4 10
"000000010",// 4 11
"000000001",// Stuffing --
NULL
};

extern vtab_byte table_B7[512];

/*
static vtab2 table_B7[] =
{
1, 1, 0,
3, 2, 8,
3, 3, 4,
4, 2, 2,
4, 3, 1,
5, 3, 12,
6, 4, 16,
6, 5, 3,
7, 5, 9,
7, 6, 6,
7, 7, 5,
7, 4, 10,
7, 3, 15,
8, 3, 14,
8, 4, 13,
8, 5, 11,
9, 5, 7,
9, 4, 17,
9, 3, 18,
9, 2, 19,
9, 1, 20,
0
};
*/

struct mcbpc
{
	int mbtype;
	int cbpc;
};

#define BITS2(b0,b1)			((b0<<0)|(b1<<1))
#define BITS4(b0,b1,b2,b3) ((b0<<0)|(b1<<1)|(b2<<2)|(b3<<3))

/*
VLC table for mcbpc for I-VOPs and S-VOPs with low_latence_sprite_enable==1 and
sprite_transmit_mode==”piece”
*/
mcbpc mcbpc_B6[] =
{
3, 0,
3, 1,
3, 2,
3, 3,
4, 0,
4, 1,
4, 2,
4, 3,
-1,0// Stuffing --
};

/*
VLC table for mcbpc for P-VOPs and S-VOPs with low_latence_sprite_enable==1 and
sprite_transmit_mode==”update”, and S(GMC)-VOPs
*/
mcbpc mcbpc_B7[] =
{
0, 0,
0, 1,
0, 2,
0, 3,
1, 0,
1, 1,
1, 2,
1, 3,
2, 0,
2, 1,
2, 2,
2, 3,
3, 0,
3, 1,
3, 2,
3, 3,
4, 0,
4, 1,
4, 2,
4, 3,
-1,0,// Stuffing --
};

char* str_table_B8[] =
{
"0011",
/*
00
00
11
11
*/

"00101",
/*
00
01
11
10
*/

"00100",
/*
00
10
11
01
*/

"1001",
/*
00
11
11
00
*/

"00011",
/*
01
00
10
11
*/

"0111",
/*
01
01
10
10
*/

"000010",
/*
01
10
10
01
*/

"1011",
/*
01
11
10
00
*/

"00010",
/*
10
00
01
11
*/

"000011",
/*
10
01
01
10
*/

"0101",
/*
10
10
01
01
*/

"1010",
/*
10
11
01
00
*/

"0100",
/*
11
00
00
11
*/

"1000",
/*
11
01
00
10
*/

"0110",
/*
11
10
00
01
*/

"11",
/*
11
11
00
00
*/

NULL
};

extern vtab_byte table_B8[64];

/*
static vtab2 table_B8[] =
{
2, 3, 15,
4, 11, 7,
4, 8, 13,
4, 9, 3,
4, 7, 5,
4, 10, 11,
4, 4, 12,
4, 3, 0,
4, 6, 14,
4, 5, 10,
5, 3, 4,
5, 4, 2,
5, 5, 1,
5, 2, 8,
6, 2, 6,
6, 3, 9,
0
};
*/

/*
Table B-8 -- VLC table for cbpy in the case of four non-transparent blocks

intra then inter
*/
uint8 cbpy_B8[][2] =
{
BITS4(0,0,0,0),BITS4(1,1,1,1),
BITS4(0,0,0,1),BITS4(1,1,1,0),
BITS4(0,0,1,0),BITS4(1,1,0,1),
BITS4(0,0,1,1),BITS4(1,1,0,0),
BITS4(0,1,0,0),BITS4(1,0,1,1),
BITS4(0,1,0,1),BITS4(1,0,1,0),
BITS4(0,1,1,0),BITS4(1,0,0,1),
BITS4(0,1,1,1),BITS4(1,0,0,0),
BITS4(1,0,0,0),BITS4(0,1,1,1),
BITS4(1,0,0,1),BITS4(0,1,1,0),
BITS4(1,0,1,0),BITS4(0,1,0,1),
BITS4(1,0,1,1),BITS4(0,1,0,0),
BITS4(1,1,0,0),BITS4(0,0,1,1),
BITS4(1,1,0,1),BITS4(0,0,1,0),
BITS4(1,1,1,0),BITS4(0,0,0,1),
BITS4(1,1,1,1),BITS4(0,0,0,0),
};

//Table B-12 -- VLC table for MVD

char* str_table_B12[] =
{
"0000000000101",// -16
"0000000000111",// -15.5
"000000000101",// -15
"000000000111",// -14.5
"000000001001",// -14
"000000001011",// -13.5
"000000001101",// -13
"000000001111",// -12.5
"00000001001",// -12
"00000001011",// -11.5
"00000001101",// -11
"00000001111",// -10.5
"00000010001",// -10
"00000010011",// -9.5
"00000010101",// -9
"00000010111",// -8.5
"00000011001",// -8
"00000011011",// -7.5
"00000011101",// -7
"00000011111",// -6.5
"00000100001",// -6
"00000100011",// -5.5
"0000010011",// -5
"0000010101",// -4.5
"0000010111",// -4
"00000111",// -3.5
"00001001",// -3
"00001011",// -2.5
"0000111",// -2
"00011",// -1.5
"0011",// -1
"011",// -0.5
"1",// 0
"010",// 0.5
"0010",// 1
"00010",// 1.5
"0000110",// 2
"00001010",// 2.5
"00001000",// 3
"00000110",// 3.5
"0000010110",// 4
"0000010100",// 4.5
"0000010010",// 5
"00000100010",// 5.5
"00000100000",// 6
"00000011110",// 6.5
"00000011100",// 7
"00000011010",// 7.5
"00000011000",// 8
"00000010110",// 8.5
"00000010100",// 9
"00000010010",// 9.5
"00000010000",// 10
"00000001110",// 10.5
"00000001100",// 11
"00000001010",// 11.5
"00000001000",// 12
"000000001110",// 12.5
"000000001100",// 13
"000000001010",// 13.5
"000000001000",// 14
"000000000110",// 14.5
"000000000100",// 15
"0000000000110",// 15.5
"0000000000100",// 16
NULL
};

/*
static vtab2 table_B12[] =
{
1, 1, 32,
3, 2, 33,
3, 3, 31,
4, 2, 34,
4, 3, 30,
5, 3, 29,
5, 2, 35,
7, 7, 28,
7, 6, 36,
8, 10, 37,
8, 8, 38,
8, 6, 39,
8, 11, 27,
8, 9, 26,
8, 7, 25,
10, 21, 23,
10, 23, 24,
10, 22, 40,
10, 18, 42,
10, 19, 22,
10, 20, 41,
11, 11, 9,
11, 13, 10,
11, 27, 17,
11, 33, 20,
11, 31, 19,
11, 25, 16,
11, 19, 13,
11, 9, 8,
11, 8, 56,
11, 12, 54,
11, 29, 18,
11, 23, 15,
11, 17, 12,
11, 15, 11,
11, 21, 14,
11, 35, 21,
11, 10, 55,
11, 28, 46,
11, 30, 45,
11, 14, 53,
11, 16, 52,
11, 34, 43,
11, 32, 44,
11, 20, 50,
11, 18, 51,
11, 26, 47,
11, 24, 48,
11, 22, 49,
12, 15, 7,
12, 13, 6,
12, 7, 3,
12, 5, 2,
12, 9, 4,
12, 11, 5,
12, 6, 61,
12, 4, 62,
12, 14, 57,
12, 12, 58,
12, 10, 59,
12, 8, 60,
13, 5, 0,
13, 7, 1,
13, 6, 63,
13, 4, 64,
0
};
*/

extern struct vtab_byte table_B12[8192];

/*
Table B-13 -- Variable length codes for dct_dc_size_luminance
Variable length code dct_dc_size_luminance
*/

char* str_table_B13[] =
{
"011",// 0
"11",// 1
"10",// 2
"010",// 3
"001",// 4
"0001",// 5
"00001",// 6
"000001",// 7
"0000001",// 8
"00000001",// 9
"000000001",// 10
"0000000001",// 11
"00000000001",// 12
NULL
};

/*
NOTE The variable length code for dct_dc_size_luminance of 10, 11 and 12 are not valid for any object types where the
pixel depth is 8 bits. They shall not be present in a bitstream conforming to these object types.
*/
/*
static vtab2 table_B13[] =
{
2, 3, 1,
2, 2, 2,
3, 2, 3,
3, 1, 4,
3, 3, 0,
4, 1, 5,
5, 1, 6,
6, 1, 7,
7, 1, 8,
8, 1, 9,
9, 1, 10,
10, 1, 11,
11, 1, 12,
0
};
*/

extern vtab_byte table_B13[2048];

/*
Table B-14 -- Variable length codes for dct_dc_size_chrominance
Variable length code dct_dc_size_chrominance
*/

char* str_table_B14[] =
{
"11",// 0
"10",// 1
"01",// 2
"001",// 3
"0001",// 4
"00001",// 5
"000001",// 6
"0000001",// 7
"00000001",// 8
"000000001",// 9
"0000000001",// 10
"00000000001",// 11
"000000000001",// 12
NULL
};

/*
NOTE The variable length code for dct_dc_size_chrominance of 10, 11 and 12 are not valid for any object types where the
pixel depth is 8 bits. They shall not be present in a bitstream conforming to these object types.
*/
/*
static vtab2 table_B14[] =
{
2, 2, 1,
2, 1, 2,
2, 3, 0,
3, 1, 3,
4, 1, 4,
5, 1, 5,
6, 1, 6,
7, 1, 7,
8, 1, 8,
9, 1, 9,
10, 1, 10,
11, 1, 11,
12, 1, 12,
0
};
*/

extern vtab_byte table_B14[];


/*
© ISO/IEC 2001 – All rights reserved 343
Table B-16 -- VLC Table for Intra Luminance and Chrominance TCOEF
VLC CODE LAST RUN LEVEL VLC CODE LAST RUN LEVEL
*/

char* str_table_B16[] =
{
"10",//s 0 0 1 
"0111",// s 1 0 1
"1111",// s 0 0 3 
"000011001",//s 0 11 1
"010101",//s 0 0 6 
"00000000101",//s 1 0 6
"0010111",//s 0 0 9 
"001111",//s 1 1 1
"00011111",// s 0 0 10 
"00000000100",//s 1 0 7
"000100101",//s 0 0 13 
"001110",//s 1 2 1
"000100100",//s 0 0 14 
"001101",//s 0 5 1
"0000100001",//s 0 0 17 
"001100",//s 1 0 2
"0000100000",//s 0 0 18 
"0010011",//s 1 5 1
"00000000111",//s 0 0 21 
"0010010",//s 0 6 1
"00000000110",//s 0 0 22 
"0010001",//s 1 3 1
"00000100000",//s 0 0 23 
"0010000",//s 1 4 1
"110",//s 0 0 2 
"00011010",// s 1 9 1
"010100",//s 0 1 2 
"00011001",// s 0 8 1
"00011110",// s 0 0 11
"00011000",// s 0 9 1
"0000001111",//s 0 0 19 
"00010111",// s 0 10 1
"00000100001",//s 0 0 24 
"00010110",// s 1 0 3
"000001010000",//s 0 0 25 
"00010101",// s 1 6 1
"1110",//s 0 1 1 
"00010100",// s 1 7 1
"00011101",// s 0 0 12 
"00010011",// s 1 8 1
"0000001110",//s 0 0 20 
"000011000",//s 0 12 1
"000001010001",//s 0 0 26 
"000010111",//s 1 0 4
"01101",//s 0 0 4 
"000010110",//s 1 1 2
"000100011",//s 0 0 15 
"000010101",//s 1 10 1
"0000001101",//s 0 1 7 
"000010100",//s 1 11 1
"01100",//s 0 0 5 
"000010011",//s 1 12 1
"000100010",//s 0 4 2 
"000010010",//s 1 13 1
"000001010010",//s 0 0 27 
"000010001",//s 1 14 1
"01011",//s 0 2 1 
"0000000111",//s 0 13 1
"0000001100",//s 0 2 4 
"0000000110",//s 1 0 5
"000001010011",//s 0 1 9 
"0000000101",//s 1 1 3
"010011",//s 0 0 7 
"0000000100",//s 1 2 2
"0000001011",//s 0 3 4 
"00000100100",//s 1 3 2
"000001010100",//s 0 6 3 
"00000100101",//s 1 4 2
"010010",//s 0 0 8 
"00000100110",//s 1 15 1
"0000001010",//s 0 4 3 
"00000100111",//s 1 16 1
"010001",//s 0 3 1 
"000001011000",//s 0 14 1
"0000001001",//s 0 8 2 
"000001011001",//s 1 0 8
"010000",//s 0 4 1 
"000001011010",//s 1 5 2
"0000001000",//s 0 5 3 
"000001011011",//s 1 6 2
"0010110",//s 0 1 3 
"000001011100",//s 1 17 1
"000001010101",//s 0 1 10 
"000001011101",//s 1 18 1
"0010101",//s 0 2 2 
"000001011110",//s 1 19 1
"0010100",//s 0 7 1 
"000001011111",//s 1 20 1
"00011100",// s 0 1 4 
"0000011",// escape
"00011011",// s 0 3 2
"000100001",//s 0 0 16
"000100000",//s 0 1 5
"000011111",//s 0 1 6
"000011110",//s 0 2 3
"000011101",//s 0 3 3
"000011100",//s 0 5 2
"000011011",//s 0 6 2
"000011010",//s 0 7 2
"00000100010",//s 0 1 8
"00000100011",//s 0 9 2
"000001010110",//s 0 2 5
"000001010111",//s 0 7 3
NULL
};

/*
static vtab2 vlctable_B16[] =
{
2, 2, 0,
3, 6, 24,
4, 14, 36,
4, 7, 1,
4, 15, 2,
5, 13, 44,
5, 12, 50,
5, 11, 56,
6, 19, 62,
6, 21, 4,
6, 15, 7,
6, 18, 68,
6, 14, 11,
6, 13, 13,
6, 20, 26,
6, 12, 15,
6, 17, 72,
6, 16, 76,
7, 20, 86,
7, 22, 80,
7, 19, 17,
7, 21, 84,
7, 17, 21,
7, 16, 23,
7, 3, 89,	// escape
7, 23, 6,
7, 18, 19,
8, 23, 31,
8, 30, 28,
8, 24, 29,
8, 28, 88,
8, 25, 27,
8, 31, 8,
8, 22, 33,
8, 27, 90,
8, 21, 35,
8, 26, 25,
8, 20, 37,
8, 29, 38,
8, 19, 39,
9, 24, 41,
9, 37, 10,
9, 23, 43,
9, 25, 3,
9, 22, 45,
9, 35, 46,
9, 21, 47,
9, 36, 12,
9, 19, 51,
9, 20, 49,
9, 31, 93,
9, 26, 98,
9, 34, 52,
9, 18, 53,
9, 27, 97,
9, 17, 55,
9, 29, 95,
9, 30, 94,
9, 32, 92,
9, 28, 96,
9, 33, 91,
10, 12, 58,
10, 5, 61,
10, 4, 63,
10, 33, 14,
10, 32, 16,
10, 7, 57,
10, 14, 40,
10, 6, 59,
10, 11, 64,
10, 10, 70,
10, 15, 30,
10, 13, 48,
10, 9, 74,
10, 8, 78,
11, 33, 32,
11, 37, 67,
11, 38, 69,
11, 39, 71,
11, 36, 65,
11, 6, 20,
11, 32, 22,
11, 5, 5,
11, 35, 100,
11, 7, 18,
11, 4, 9,
11, 34, 99,
12, 91, 79,
12, 95, 87,
12, 92, 81,
12, 85, 82,
12, 93, 83,
12, 94, 85,
12, 88, 73,
12, 84, 66,
12, 80, 34,
12, 83, 60,
12, 82, 54,
12, 81, 42,
12, 90, 77,
12, 89, 75,
12, 86, 101,
12, 87, 102,
0
};
*/

extern struct vtab_byte table_B16[4096];

/*
Table B-17 -- VLC table for Inter Lumimance and Chrominance TCOEF
VLC CODE LAST RUN LEVEL VLC CODE LAST RUN LEVEL
*/

char* str_table_B17[] =
{
"10",//s 0 0 1 
"0111",// s 1 0 1
"1111",// s 0 0 2 
"000011001",//s 1 0 2
"010101",//s 0 0 3 
"00000000101",//s 1 0 3
"0010111",//s 0 0 4 
"001111",//s 1 1 1
"00011111",// s 0 0 5 
"00000000100",//s 1 1 2
"000100101",//s 0 0 6 
"001110",//s 1 2 1
"000100100",//s 0 0 7 
"001101",//s 1 3 1
"0000100001",//s 0 0 8 
"001100",//s 1 4 1
"0000100000",//s 0 0 9 
"0010011",//s 1 5 1
"00000000111",//s 0 0 10 
"0010010",//s 1 6 1
"00000000110",//s 0 0 11 
"0010001",//s 1 7 1
"00000100000",//s 0 0 12 
"0010000",//s 1 8 1
"110",//s 0 1 1 
"00011010",// s 1 9 1
"010100",//s 0 1 2 
"00011001",// s 1 10 1
"00011110",// s 0 1 3 
"00011000",// s 1 11 1
"0000001111",//s 0 1 4 
"00010111",// s 1 12 1
"00000100001",//s 0 1 5 
"00010110",// s 1 13 1
"000001010000",//s 0 1 6 
"00010101",// s 1 14 1
"1110",// s 0 2 1 
"00010100",// s 1 15 1
"00011101",// s 0 2 2 
"00010011",// s 1 16 1
"0000001110",//s 0 2 3 
"000011000",//s 1 17 1
"000001010001",//s 0 2 4 
"000010111",//s 1 18 1
"01101",//s 0 3 1 
"000010110",//s 1 19 1
"000100011",//s 0 3 2 
"000010101",//s 1 20 1
"0000001101",//s 0 3 3 
"000010100",//s 1 21 1
"01100",//s 0 4 1 
"000010011",//s 1 22 1
"000100010",//s 0 4 2 
"000010010",//s 1 23 1
"000001010010",//s 0 4 3 
"000010001",//s 1 24 1
"01011",//s 0 5 1 
"0000000111",//s 1 25 1
"0000001100",//s 0 5 2 
"0000000110",//s 1 26 1
"000001010011",//s 0 5 3 
"0000000101",//s 1 27 1
"010011",//s 0 6 1 
"0000000100",//s 1 28 1
"0000001011",//s 0 6 2 
"00000100100",//s 1 29 1
"000001010100",//s 0 6 3 
"00000100101",//s 1 30 1
"010010",//s 0 7 1 
"00000100110",//s 1 31 1
"0000001010",//s 0 7 2 
"00000100111",//s 1 32 1
"010001",//s 0 8 1 
"000001011000",//s 1 33 1
"0000001001",//s 0 8 2 
"000001011001",//s 1 34 1
"010000",//s 0 9 1 
"000001011010",//s 1 35 1
"0000001000",//s 0 9 2 
"000001011011",//s 1 36 1
"0010110",//s 0 10 1 
"000001011100",//s 1 37 1
"000001010101",//s 0 10 2 
"000001011101",//s 1 38 1
"0010101",//s 0 11 1 
"000001011110",//s 1 39 1
"0010100",//s 0 12 1 
"000001011111",//s 1 40 1
"00011100",// s 0 13 1 
"0000011",// escape
"00011011",// s 0 14 1
"000100001",//s 0 15 1
"000100000",//s 0 16 1
"000011111",//s 0 17 1
"000011110",//s 0 18 1
"000011101",//s 0 19 1
"000011100",//s 0 20 1
"000011011",//s 0 21 1
"000011010",//s 0 22 1
"00000100010",//s 0 23 1
"00000100011",//s 0 24 1
"000001010110",//s 0 25 1
"000001010111",//s 0 26 1
NULL
};

extern vtab_byte table_B17[4096];

/*
static vtab2 vlctable_B17[] =
{
2, 2, 0,
3, 6, 24,
4, 14, 36,
4, 7, 1,
4, 15, 2,
5, 13, 44,
5, 12, 50,
5, 11, 56,
6, 19, 62,
6, 21, 4,
6, 15, 7,
6, 18, 68,
6, 14, 11,
6, 13, 13,
6, 20, 26,
6, 12, 15,
6, 17, 72,
6, 16, 76,
7, 20, 86,
7, 22, 80,
7, 19, 17,
7, 21, 84,
7, 17, 21,
7, 16, 23,
7, 3, 89,
7, 23, 6,
7, 18, 19,
8, 23, 31,
8, 30, 28,
8, 24, 29,
8, 28, 88,
8, 25, 27,
8, 31, 8,
8, 22, 33,
8, 27, 90,
8, 21, 35,
8, 26, 25,
8, 20, 37,
8, 29, 38,
8, 19, 39,
9, 24, 41,
9, 37, 10,
9, 23, 43,
9, 25, 3,
9, 22, 45,
9, 35, 46,
9, 21, 47,
9, 36, 12,
9, 19, 51,
9, 20, 49,
9, 31, 93,
9, 26, 98,
9, 34, 52,
9, 18, 53,
9, 27, 97,
9, 17, 55,
9, 29, 95,
9, 30, 94,
9, 32, 92,
9, 28, 96,
9, 33, 91,
10, 12, 58,
10, 5, 61,
10, 4, 63,
10, 33, 14,
10, 32, 16,
10, 7, 57,
10, 14, 40,
10, 6, 59,
10, 11, 64,
10, 10, 70,
10, 15, 30,
10, 13, 48,
10, 9, 74,
10, 8, 78,
11, 33, 32,
11, 37, 67,
11, 38, 69,
11, 39, 71,
11, 36, 65,
11, 6, 20,
11, 32, 22,
11, 5, 5,
11, 35, 100,
11, 7, 18,
11, 4, 9,
11, 34, 99,
12, 91, 79,
12, 95, 87,
12, 92, 81,
12, 85, 82,
12, 93, 83,
12, 94, 85,
12, 88, 73,
12, 84, 66,
12, 80, 34,
12, 83, 60,
12, 82, 54,
12, 81, 42,
12, 90, 77,
12, 89, 75,
12, 86, 101,
12, 87, 102,
0
};
*/

struct lrl
{
	bool last;
	int run;
	int level;
};

// LAST,RUN,LEVEL
static lrl lrl_B16[] =
{
0, 0, 1,
1, 0, 1,
0, 0, 3,
0, 11, 1,
0, 0, 6,
1, 0, 6,
0, 0, 9,
1, 1, 1,
0, 0, 10, 
1, 0, 7,
0, 0, 13, 
1, 2, 1,
0, 0, 14, 
0, 5, 1,
0, 0, 17, 
1, 0, 2,
0, 0, 18, 
1, 5, 1,
0, 0, 21, 
0, 6, 1,
0, 0, 22, 
1, 3, 1,
0, 0, 23, 
1, 4, 1,
0, 0, 2,
1, 9, 1,
0, 1, 2,
0, 8, 1,
0, 0, 11,
0, 9, 1,
0, 0, 19, 
0, 10, 1,
0, 0, 24,
1, 0, 3,
0, 0, 25, 
1, 6, 1,
0, 1, 1,
1, 7, 1,
0, 0, 12,
1, 8, 1,
0, 0, 20,
0, 12, 1,
0, 0, 26,
1, 0, 4,
0, 0, 4,
1, 1, 2,
0, 0, 15,
1, 10, 1,
0, 1, 7,
1, 11, 1,
0, 0, 5,
1, 12, 1,
0, 4, 2,
1, 13, 1,
0, 0, 27,
1, 14, 1,
0, 2, 1,
0, 13, 1,
0, 2, 4,
1, 0, 5,
0, 1, 9,
1, 1, 3,
0, 0, 7,
1, 2, 2,
0, 3, 4,
1, 3, 2,
0, 6, 3,
1, 4, 2,
0, 0, 8,
1, 15, 1,
0, 4, 3,
1, 16, 1,
0, 3, 1,
0, 14, 1,
0, 8, 2,
1, 0, 8,
0, 4, 1,
1, 5, 2,
0, 5, 3,
1, 6, 2,
0, 1, 3,
1, 17, 1,
0, 1, 10,
1, 18, 1,
0, 2, 2,
1, 19, 1,
0, 7, 1,
1, 20, 1,
0, 1, 4,
0,0,0,// escape
0, 3, 2,
0, 0, 16,
0, 1, 5,
0, 1, 6,
0, 2, 3,
0, 3, 3,
0, 5, 2,
0, 6, 2,
0, 7, 2,
0, 1, 8,
0, 9, 2,
0, 2, 5,
0, 7, 3,
};

// LAST,RUN,LEVEL
static lrl lrl_B17[] =
{
0, 0, 1, 
1, 0, 1,
0, 0, 2,
1, 0, 2,
0, 0, 3,
1, 0, 3,
0, 0, 4,
1, 1, 1,
0, 0, 5,
1, 1, 2,
0, 0, 6,
1, 2, 1,
0, 0, 7,
1, 3, 1,
0, 0, 8,
1, 4, 1,
0, 0, 9,
1, 5, 1,
0, 0, 10,
1, 6, 1,
0, 0, 11,
1, 7, 1,
0, 0, 12,
1, 8, 1,
0, 1, 1,
1, 9, 1,
0, 1, 2,
1, 10, 1,
0, 1, 3 ,
1, 11, 1,
0, 1, 4 ,
1, 12, 1,
0, 1, 5 ,
1, 13, 1,
0, 1, 6 ,
1, 14, 1,
0, 2, 1 ,
1, 15, 1,
0, 2, 2 ,
1, 16, 1,
0, 2, 3 ,
1, 17, 1,
0, 2, 4 ,
1, 18, 1,
0, 3, 1 ,
1, 19, 1,
0, 3, 2 ,
1, 20, 1,
0, 3, 3 ,
1, 21, 1,
0, 4, 1 ,
1, 22, 1,
0, 4, 2 ,
1, 23, 1,
0, 4, 3 ,
1, 24, 1,
0, 5, 1 ,
1, 25, 1,
0, 5, 2 ,
1, 26, 1,
0, 5, 3 ,
1, 27, 1,
0, 6, 1 ,
1, 28, 1,
0, 6, 2 ,
1, 29, 1,
0, 6, 3 ,
1, 30, 1,
0, 7, 1 ,
1, 31, 1,
0, 7, 2 ,
1, 32, 1,
0, 8, 1 ,
1, 33, 1,
0, 8, 2 ,
1, 34, 1,
0, 9, 1 ,
1, 35, 1,
0, 9, 2 ,
1, 36, 1,
0, 10, 1 ,
1, 37, 1,
0, 10, 2 ,
1, 38, 1,
0, 11, 1 ,
1, 39, 1,
0, 12, 1 ,
1, 40, 1,
0, 13, 1 ,
0,0,0,//"0000011",// escape
0, 14, 1,
0, 15, 1,
0, 16, 1,
0, 17, 1,
0, 18, 1,
0, 19, 1,
0, 20, 1,
0, 21, 1,
0, 22, 1,
0, 23, 1,
0, 24, 1,
0, 25, 1,
0, 26, 1,
};

static uint8 intra_default[8][8] =
{
8, 17, 18, 19, 21, 23, 25, 27,
17, 18, 19, 21, 23, 25, 27, 28,
20, 21, 22, 23, 24, 26, 28, 30,
21, 22, 23, 24, 26, 28, 30, 32,
22, 23, 24, 26, 28, 30, 32, 35,
23, 24, 26, 28, 30, 32, 35, 38,
25, 26, 28, 30, 32, 35, 38, 41,
27, 28, 30, 32, 35, 38, 41, 45,
};

#if 0
int getvariablebits(System::IO::CBitStream32* pBitStream, vtab2 table[], int maxlen = 32)
{
	int len = 0;
	DWORD value = 0;
	vtab2* p = table;

	ASSERT(p->len);

	do
	{
		value <<= 1;

		value |= (int)pBitStream->getbit();
		len++;

		while (p->len == len)
		{
			if (p->mask == value)
			{
				vtab2* p2 = p+1;
				while (p2->len == len)
				{
					ASSERT(p2->mask != value);
					p2++;
				}

				return p->index;
			}

			p++;
		}
	}
	while (p->len);

	throw -2;
	//ASSERT(0);
	return -1;
}
#endif

MPEG4VideoDecExt int next_start_code(System::IO::CBitStream32* pBitStream)
{
// TODO, read all bits with one call to getnbits() to make it byte-aligned
	if (!pBitStream->is_byte_aligned())
	{
		int bit = pBitStream->getbit();
		if (bit != 0)
		{
			TRACE("warning in bitstream\n");
			;//THROW(-1);
		}

		while (!pBitStream->is_byte_aligned())
		{
			int bit = pBitStream->getbit();
			if (bit != 1)
			{
				TRACE("warning in bitstream\n");
				;//THROW(-1);
			}
		}
	}

	/*
	int n24;
	while ((n24 = pBitStream->getnbits(24)) != 0x1)
	{
		pBitStream->ungetbits(24);
		int byte = pBitStream->getnbits(8);
		if (byte != 0)
		{
			TRACE("warning in bitstream\n");
			;//THROW(-1);
		}
	}
	*/

//	int n24;
	while ((pBitStream->looknbits(24)) != 0x1)
	{
	//	pBitStream->ungetbits(24);
		int byte = pBitStream->getnbits(8);
		if (byte != 0)
		{
			TRACE("warning in bitstream\n");
			;//THROW(-1);
		}
	}
	
	int n24 = pBitStream->getnbits(24);

//	ASSERT(n24 == 0x1);
	uint32 m_next_code = 0x100 | pBitStream->getnbits(8);

	return m_next_code;
}

MPEG4VideoDecExt int nextbits_bytealigned(System::IO::CBitStream32* pBitStream, int nbits)
{
	ASSERT(0);
	int nextbits;
#if 0

	int n = 0;
	if (pBitStream->is_byte_aligned())
	{
	//	BYTE byte = pBitStream->getbyte();
/*		if (byte == 0x7F)
		{
			nextbits = pBitStream->getnbits(nbits);
			n += 8;
		}
		else
*/		{
	//		pBitStream->ungetbyte();
			nextbits = pBitStream->getnbits(nbits);
		}
		n += nbits;
	}
	else
	{
	// First byte align
		n = 8-pBitStream->m_bitcnt;
		pBitStream->getnbits(n);

		nextbits = pBitStream->getnbits(nbits);
		n += nbits;
	}

	pBitStream->ungetbits(n);
#endif

	return nextbits;
}

void get_marker_bit(System::IO::CBitStream32* pBitStream)
{
	int marker_bit = pBitStream->getbit();
	if (marker_bit != 1)
	{
		ASSERT(0);
		throw L"Error in bitstream";
	}
}

/////////////////////////////////////////////////////////////////////////////
// VideoDec

/* vop_coding_type

00 intra-coded (I)
01 predictive-coded (P)
10 bidirectionally-predictive-coded (B)
11 sprite (S)

*/

bool transparent_mb()
{
	return false;	// ???
}

bool transparent_block(int i)
{
	return false;	// ???
}

/* Table 7.13
ref_select_code forward prediction reference
00 Most recently decoded enhancement VOP belonging to the same layer
for which “vop_coded == 1”.
01 Most recently VOP in display order belonging to the reference layer for
which “vop_coded == 1”.
10 Next VOP in display order belonging to the reference layer.
11 Temporally coincident VOP in the reference layer (no motion vectors)
*/

/* Table 7.14
ref_select_code forward temporal reference backward temporal reference
00 Most recently decoded enhancement
VOP of the same layer for which
“vop_coded == 1”.
Temporally coincident VOP in the
reference layer (no motion vectors)
01 Most recently decoded enhancement
VOP of the same layer for which
“vop_coded == 1”.
Most recent VOP in display order
belonging to the reference layer.
10 Most recently decoded enhancement
VOP of the same layer for which
“vop_coded == 1”.
Next VOP in display order
belonging to the reference layer.
11 Most recent VOP in display order
belonging to the reference layer for
which “vop_coded == 1”.
Next VOP in display order
belonging to the reference layer.
*/

/*
Table 6-21 -- Meaning of intra_dc_vlc_thr

index meaning of intra_dc_vlc_thr code

0 Use Intra DC VLC for entire VOP 000
1 Switch to Intra AC VLC at running Qp >=13 001
2 Switch to Intra AC VLC at running Qp >=15 010
3 Switch to Intra AC VLC at running Qp >=17 011
4 Switch to Intra AC VLC at running Qp >=19 100
5 Switch to Intra AC VLC at running Qp >=21 101
6 Switch to Intra AC VLC at running Qp >=23 110
7 Use Intra AC VLC for entire VOP 111
*/

int grgiDCSwitchingThreshold[8] = {512, 13, 15, 17, 19, 21, 23, 0};

static int scan[3][8][8] =
{
	// alternate horizontal
	{
		0, 1, 2, 3, 10, 11, 12, 13,
		4, 5, 8, 9, 17, 16, 15, 14,
		6, 7, 19, 18, 26, 27, 28, 29,
		20, 21, 24, 25, 30, 31, 32, 33,
		22, 23, 34, 35, 42, 43, 44, 45,
		36, 37, 40, 41, 46, 47, 48, 49,
		38, 39, 50, 51, 56, 57, 58, 59,
		52, 53, 54, 55, 60, 61, 62, 63,
	},

	// alternate vertical
	{
		0,	4,	6,	20,	22,	36,	38,	52,
		1,	5,	7,	21,	23,	37,	39,	53,
		2,	8,	19,	24,	34,	40,	50,	54,
		3,	9,	18,	25,	35,	41,	51,	55,
		10,	17,	26,	30,	42,	46,	56,	60,
		11,	16,	27,	31,	43,	47,	57,	61,
		12,	15,	28,	32,	44,	48,	58,	62,
		13,	14,	29,	33,	45,	49,	59,	63,
	},

	// zigzag
	{
		0,	1,	5,	6,	14,	15,	27,	28,
		2,	4,	7,	13,	16,	26,	29,	42,
		3,	8,	12,	17,	25,	30,	41,	43,
		9,	11,	18,	24,	31,	40,	44,	53,
		10,	19,	23,	32,	39,	45,	52,	54,
		20,	22,	33,	38,	46,	51,	55,	60,
		21,	34,	37,	47,	50,	56,	59,	61,
		35,	36,	48,	49,	57,	58,	62,	63,
	},
};

////////////////////////////////////////////////////////////////////
//


static int QuantizerScale[][2] =
{
	{0, 0},// (forbidden)
	{2,	1},
	{4,	2},
	{6,	3},
	{8,	4},
	{10,	5},
	{12,	6},
	{14,	7},
	{16,	8},
	{18,	10},
	{20,	12},
	{22,	14},
	{24,	16},
	{26,	18},
	{28,	20},
	{30,	22},
	{32,	24},
	{34,	28},
	{36,	32},
	{38,	36},
	{40,	40},
	{42,	44},
	{44,	48},
	{46,	52},
	{48,	56},
	{50,	64},
	{52,	72},
	{54,	80},
	{56,	88},
	{58,	96},
	{60,	104},
	{62,	112},
};

////////////////////////////////////////////////////////////////////
// CVideoObjectPlane

VideoObjectPlane::VideoObjectPlane()
{
	m_sprite_transmit_mode = SpriteTransmit_piece;

	m_ref_select_code = 0;

	m_macroblocks = NULL;
	m_mb_cols = m_mb_rows = 0;

	m_ybuf = NULL;
	m_crbuf = NULL;
	m_cbbuf = NULL;

//	MVx = 0;
//	MVy = 0;

	m_pPrevVOP = NULL;

m_vop_coding_type = 0;
m_ref_select_code = 0;
m_sprite_transmit_mode = 0;
m_intra_dc_vlc_thr = 0;
m_vop_reduced_resolution = 0;
//	unsigned int m_vop_quant;	// Don't need to remember this
m_vop_fcode_forward = 0;
m_vop_fcode_backward = 0;

// Member values
//	int m_quantiser_scale;	// Qp for current macroblock?
m_macroblocks = 0;
m_mb_cols = 0;
m_mb_rows = 0;

m_Qp[0] = 0;	// running Qp, one for luminance and one for chrominance?
m_Qp[1] = 0;
//	int MVx;
//	int MVy;

m_horizontal_mv_data = 0;
m_horizontal_mv_residual = 0;
m_vertical_mv_data = 0;
m_vertical_mv_residual = 0;
mb_address = 0;
}

VideoObjectPlane::~VideoObjectPlane()
{
	delete [] m_macroblocks;

	free(m_ybuf);
	free(m_crbuf);
	free(m_cbbuf);
}

void VideoObjectPlane::decode_block(int mb_address, int i, int ac_pred_flag, int macroblock_intra, int QFS[8*8], short f[8][8])
{
	MacroBlock* pCurrentMB = m_macroblocks + mb_address;
	int mb_row = mb_address / m_mb_cols;
	int mb_column = mb_address % m_mb_cols;

	pCurrentMB->m_intra = macroblock_intra;

	int quantiser_scale = pCurrentMB->m_quantiser_scale;//m_vop_quant;	// TODO
//	int quantiser_scale = QuantizerScale[pCurrentMB->m_quantiser_scale][0];//m_vop_quant;	// TODO

	ASSERT(quantiser_scale > 0);

	int dc_scaler;// = 1;

	if (i < 4)	// luminance block
	{
		/*
		if (iQP <= 4)
		{
			iDcScalerY = 8;
			iDcScalerC = 8;
		}
		else if (iQP >= 5 && iQP <= 8)
		{
			iDcScalerY = 2 * iQP;
			iDcScalerC = (iQP + 13) / 2;
		}
		else if (iQP >= 9 && iQP <= 24)
		{
			iDcScalerY = iQP + 8;
			iDcScalerC = (iQP + 13) / 2;
		}
		else	{
			iDcScalerY = 2 * iQP - 16;
			iDcScalerC = iQP - 6;
		}
		*/

		// Not sure about this
		if (quantiser_scale <= 4)
		{
			dc_scaler = 8;
		}
		else if (quantiser_scale <= 8)
		{
			dc_scaler = (quantiser_scale*2);
		}
		else if (quantiser_scale <= 24)
		{
			dc_scaler = (quantiser_scale+8);
		}
		else // <= 31
		{
			dc_scaler = (quantiser_scale * 2 - 16);
		}

//		dc_scaler = QuantizerScale[quantiser_scale][0];
	}
	else	// chrominance block
	{
		if (quantiser_scale <= 4)
			dc_scaler = 8;
		else if (quantiser_scale <= 24)
			dc_scaler = (quantiser_scale + 13) / 2;
		else
			dc_scaler = quantiser_scale - 6;
	}

	ASSERT(dc_scaler > 0 && dc_scaler < 64);

/*
If any of the blocks A, B or C are outside of the VOP boundary, or the video packet boundary, or they do not belong
to an intra coded macroblock, their F[0][0] values are assumed to take a value of 2(bits_per_pixel+2) and are used to
compute the prediction values.
*/

	int (*QF)[8] = pCurrentMB->QF[i];
	short (*F)[8] = pCurrentMB->F[i];

	int (*QFA)[8] = NULL;
	int (*QFB)[8] = NULL;
	int (*QFC)[8] = NULL;
	short (*FA)[8] = NULL;
	short (*FB)[8] = NULL;
	short (*FC)[8] = NULL;

	int predOutside = 1<<(m_config->m_bits_per_pixel+2);
	//int predOutside = pow(2, m_config->m_bits_per_pixel+2);
	short FOutside[8][8];
	{	// TODO, do this once on startup
		for (int u = 0; u < 8; u++)
		{
			for (int v = 0; v < 8; v++)
			{
				FOutside[u][v] = predOutside;
			}
		}
	}

	MacroBlock* pLeftMB = NULL;
	MacroBlock* pAboveMB = NULL;
	MacroBlock* pAboveLeftMB = NULL;

	if (macroblock_intra)
	{

		if (i < 4)
		{
			/* blocks are laid within the macroblock like this:
				01
				23
			and
				BC
				AX

			X = current
			*/
			if (i == 0)
			{
				FA = FOutside;
				if (mb_column > 0)
				{
					pLeftMB = pCurrentMB - 1;
					if (pLeftMB->m_intra)
					{
						QFA = pLeftMB->QF[1];
						FA = pLeftMB->F[1];
					}
				}

				FC = FOutside;
				if (mb_row > 0)
				{
					pAboveMB = pCurrentMB - m_mb_cols;

					if (pAboveMB->m_intra)
					{
						QFC = pAboveMB->QF[2];
						FC = pAboveMB->F[2];
					}
				}

				FB = FOutside;
				if (mb_row > 0 && mb_column > 0)
				{
					pAboveLeftMB = pCurrentMB - m_mb_cols - 1;

					if (pAboveLeftMB->m_intra)
					{
						QFB = pAboveLeftMB->QF[3];
						FB = pAboveLeftMB->F[3];
					}
				}
			}
			else if (i == 1)
			{
				pLeftMB = pCurrentMB;

				QFA = pCurrentMB->QF[0];
				FA = pCurrentMB->F[0];

				FB = FOutside;
				FC = FOutside;

				if (mb_row > 0)
				{
					pAboveMB = pCurrentMB - m_mb_cols;
					if (pAboveMB->m_intra)
					{
						QFB = pAboveMB->QF[2];
						FB = pAboveMB->F[2];

						QFC = pAboveMB->QF[3];
						FC = pAboveMB->F[3];
					}
				}
			}
			else if (i == 2)
			{
				pAboveMB = pCurrentMB;

				QFC = pCurrentMB->QF[0];
				FC = pCurrentMB->F[0];

				FA = FOutside;
				FB = FOutside;

				if (mb_column > 0)
				{
					pLeftMB = pCurrentMB - 1;

					if (pLeftMB->m_intra)
					{
						QFA = pLeftMB->QF[3];
						FA = pLeftMB->F[3];

						QFB = pLeftMB->QF[1];
						FB = pLeftMB->F[1];
					}
				}
			}
			else if (i == 3)
			{
				pLeftMB = pCurrentMB;
				pAboveMB = pCurrentMB;

				QFA = pCurrentMB->QF[2];
				FA = pCurrentMB->F[2];

				QFB = pCurrentMB->QF[0];
				FB = pCurrentMB->F[0];

				QFC = pCurrentMB->QF[1];
				FC = pCurrentMB->F[1];
			}
		}
		else
		{
			FA = FOutside;
			if (mb_column > 0)
			{
				pLeftMB = pCurrentMB - 1;
				if (pLeftMB->m_intra)
				{
					QFA = pLeftMB->QF[i];
					FA = pLeftMB->F[i];
				}
			}

			FC = FOutside;
			if (mb_row > 0)
			{
				pAboveMB = pCurrentMB - m_mb_cols;
				if (pAboveMB->m_intra)
				{
					QFC = pAboveMB->QF[i];
					FC = pAboveMB->F[i];
				}
			}

			FB = FOutside;
			if (mb_row > 0 && mb_column > 0)
			{
				pAboveLeftMB = pCurrentMB - m_mb_cols - 1;
				if (pAboveLeftMB->m_intra)
				{
					QFB = pAboveLeftMB->QF[i];
					FB = pAboveLeftMB->F[i];
				}
			}
		}
	}
	else
	{
		FA = FOutside;
		FB = FOutside;
		FC = FOutside;
	}

	int predictHorizontal;
	if (abs(FA[0][0] - FB[0][0]) < abs(FB[0][0] - FC[0][0]))
	{
	//	predict from block C
		predictHorizontal = false;
	}
	else
	{
	//	predict from block A
		predictHorizontal = true;
	}
	//predictHorizontal = TRUE;

	/*
The scan that shall be used is determined by the following method. For intra
blocks, if acpred_flag=0, zigzag scan is selected for all blocks in a macroblock. Otherwise, DC prediction direction
is used to select a scan on block basis.
*/

//////////////////////////////////////////////////////////////////////////
// Inverse scan

	// Output after this step is PQF

	int PQF[8][8];

	int scan_type;
	if (macroblock_intra)
	{
		if (ac_pred_flag == 0)
		{
			scan_type = 2;	// Zigzag
		}
		else
		{
		//	ASSERT(macroblock_intra);
			// if the DC prediction refers to the horizontally adjacent block,
			// alternate-vertical scan is selected for the current block.
			if (predictHorizontal)
				scan_type = 1;
			else
				scan_type = 0;
		}
	}
	else
	{
		/*
		if (predictHorizontal)
			scan_type = 1;
		else
			scan_type = 0;
			*/
		scan_type = 2;	// Zig-Zag
	}

	if ((m_config->m_video_object_layer_shape != LayerShape_rectangular)/* && (sadct_disable==0) && (opaque_pels < 64)*/)
	{
		ASSERT(0);
#if 0
		coeff_count=0;
		for (n=0; n<64; n++)
		{
			PQF[inv_scan_v[scan_type][n]][inv_scan_u[scan_type][n]]=0;
			if (coeff_width[inv_scan_v[scan_type][n]] > inv_scan_u[scan_type][n])
			{
				PQF[inv_scan_v[scan_type][n]][inv_scan_u[scan_type][n]]=
					QFS[coeff_count];
				coeff_count++;
			}
		}
#endif
	}
	else
	{
		/* ????
		for (int n = 0; n < 64; n++)
		{
			PQF[inv_scan_v[scan_type][n]][inv_scan_u[scan_type][n]] = QFS[n];
		}
	*/

		for (int v = 0; v < 8; v++)
		{
			for (int u = 0; u < 8; u++)
			{
				PQF[v][u] = QFS[scan[scan_type][v][u]];
			}
		}
	}

/////////////////////////////////////////////////////////////////////////////
// Inverse AC & DC prediction

	// Output after this step is QF

#if 0

if (predict from block C)
	QFx[0][0] = PQFx[0][0] + FC[0][0] // dc_scaler
else
	QFx[0][0] = PQFx[0][0] + FA[0][0] // dc_scaler

#endif

	{
		for (int u = 0; u < 8; u++)
		{
			for (int v = 0; v < 8; v++)
			{
				QF[v][u] = PQF[v][u];
			}
		}
	}

	if (macroblock_intra)
	{
		if (!predictHorizontal)
		{
			QF[0][0] = PQF[0][0] + divroundnearest(FC[0][0], dc_scaler);
			//QF[0][0] = PQF[0][0] + FC[0][0] / quantiser_scale;
		}
		else
		{
			QF[0][0] = PQF[0][0] + divroundnearest(FA[0][0], dc_scaler);
			//QF[0][0] = PQF[0][0] + FA[0][0] / quantiser_scale;
		}
	}

	//QF[0][0] = 64;

	//int predX = QF[0][0];	// pred of this block
	//pCurrentMB->m_pred[i] = predX;

	if (ac_pred_flag)
	{

	// The quantisation stepsize is equal to twice the quantiser_scale.

		int QP = quantiser_scale * 2;

		if (predictHorizontal)
		{
			if (QFA)
			{
				int QPA = pLeftMB->m_quantiser_scale * 2;	// TODO

				for (int v = 1; v < 8; v++)
				{
					QF[v][0] = PQF[v][0] + (QFA[v][0] * QPA) / QP;
				}
			}
		}
		else
		{
			if (QFC)
			{
				int QPC = pAboveMB->m_quantiser_scale * 2;	// TODO

				for (int u = 1; u < 8; u++)
				{
					QF[0][u] = PQF[0][u] + (QFC[0][u] * QPC) / QP;
				}
			}
		}
	}
	/*
	else
	{
		;//MessageBeep(-1);
	}
	*/

///////////////////////////////////////////////////////////////////////////
// Inverse quantisation

	// Output after this step is F

	int maxv = (1<<(m_config->m_bits_per_pixel+3))-1;
	int minv = -(1<<(m_config->m_bits_per_pixel+3));

	if	(m_config->m_quant_type == 1)	// first inverse quantisation method
	{
		uint8 (*W)[8];
		
		if (macroblock_intra)
			W = intra_default;//m_intra_quantiser_matrix;
		else
			ASSERT(0);//W_ = m_non_intra_quantiser_matrix;

		short F_[8][8];
		short F__[8][8];

		int v, u;

		for (v = 0; v < 8; v++)
		{
			for (u = 0; u < 8; u++)
			{
				if (QF[v][u] == 0)
				{
					F__[v][u] = 0;
				}
				else if ((u==0) && (v==0) && (macroblock_intra))
				{
					F__[v][u] = dc_scaler * QF[v][u];
				}
				else
				{
					if (macroblock_intra)
					{
						F__[v][u] = (QF[v][u] * W/*[0]*/[v][u] * quantiser_scale * 2) / 16;
					}
					else
					{
						F__[v][u] = (((QF[v][u] * 2) + Sign(QF[v][u])) * W/*[1]*/[v][u]);
					}
				}
			}
		}

		// Saturation and mismatch control
		// (mismatch control is only applicable to the first inverse quantisation method)

		int sum = 0;
		for (v = 0; v < 8; v++)
		{
			for (u = 0; u < 8; u++)
			{
				if ( F__[v][u] > maxv)			F_[v][u] = maxv;
				else if ( F__[v][u] < minv)	F_[v][u] = minv;
				else									F_[v][u] = F__[v][u];

				sum = sum + F_[v][u];
				F[v][u] = F_[v][u];
			}
		}

		if ((sum & 1) == 0)
		{
			if ((F[7][7] & 1) != 0)
			{
				F[7][7] = F_[7][7] - 1;
			}
			else
			{
				F[7][7] = F_[7][7] + 1;
			}
		}
	}
	else //if	(m_config->m_quant_type == 0)	// second inverse quantisation method
	{
		//short F_[8][8]; // No need for this, since there's no mismatch control
		short F__[8][8];

		int v, u;

		for (v = 0; v < 8; v++)
		{
			for (u = 0; u < 8; u++)
			{
				// Saturation
				if (QF[v][u] > 2047)			QF[v][u] = 2047;
				else if (QF[v][u] < -2048)	QF[v][u] = -2048;
				//else								QF[v][u] = QF[v][u];

				if (QF[v][u] == 0)
				{
					F__[v][u] = 0;
				}
				else if ((u==0) && (v==0) && (macroblock_intra))
				{
					F__[v][u] = dc_scaler * QF[v][u];
				}
				else
				{
					if (quantiser_scale & 1)	// odd
					{
						F__[v][u] = (2*abs(QF[v][u])+1) * quantiser_scale;
					}
					else	// even
					{
						F__[v][u] = (2*abs(QF[v][u])+1) * quantiser_scale - 1;
					}

					F__[v][u] = Sign(QF[v][u]) * abs(F__[v][u]);
				}

				if (F__[v][u] > maxv)			F__[v][u] = maxv;
				else if (F__[v][u] < minv)		F__[v][u] = minv;
				//else								QF[v][u] = QF[v][u];

				F[v][u] = F__[v][u];
			}
		}
	}

	{
		for (int i = 0; i < 64; i++)
		{
			((short*)f)[i] = ((short*)F)[i];
		}
	}
}

/*
int lookbits(System::IO::CBitStream32* pBitStream, int nbits)
{
	int value = 0;
	if (pBitStream->m_bitcnt > 0)
	{
		value = (pBitStream->m_curbyte>>pBitStream->m_bitcnt);
		nbits -= pBitStream->m_bitcnt;
	}
	pBitStream->getbyte();
	
	//oldc[(uint8)(pBitStream->m_bytepos-1)];

	int value = pBitStream->getnbits(nbits);
	pBitStream->ungetbits(nbits);
	return value;
}
*/


inline bool GetLevelRun(System::IO::CBitStream32* pBitStream, vtab_byte* vlctable, const lrl* lrltable, int inter, int& run, int& signed_level)
{
//	ASSERT((sizeof(table_B16)-1)/sizeof(vtab2) == sizeof(lrl_B16)/sizeof(lrl));
//	DCT coefficient 3-24 vlclbf

//	pBitStream->getnbits(12);
//	pBitStream->ungetbits(12);
//	int vlc = getvariablebits(pBitStream, vlctable);

	/*
	{
		int v = pBitStream->getnbits(23);
	}
	*/

	/*
	{
		int v = pBitStream->getnbits(13);
		pBitStream->ungetbits(13);
	}
	*/

	/*
	{
		int v = pBitStream->lookbits(13);
	}
	*/

	int value = pBitStream->looknbits(12);
	int vlc = vlctable[value].index;
	pBitStream->skipnbits(vlctable[value].len);

//	TRACE("%d\n", vlc);

	bool last;

//	int run;
//	int signed_level;

	if (vlc == 89)	// escape
	//if (vlc == 102)	// escape
	{
/*
Type 1: ESC is followed by “0”, and the code following ESC + ”0” is decoded as a variable length code using the
standard Tcoef VLC codes given in Table B-16 and Table B-17, but the values of LEVEL are modified following

LEVELs= sign(LEVEL+) x [ abs( LEVEL+) + LMAX ]

where LEVEL+ is the value after variable length decoding and LMAX is obtained from Table B-19 and Table B-20
as a function of the decoded values of RUN and LAST.
		*/
		if (pBitStream->getbit() == 0)
		{
//			int vlc = getvariablebits(pBitStream, vlctable);
			int value = pBitStream->looknbits(12);
			int vlc = vlctable[value].index;
			pBitStream->skipnbits(vlctable[value].len);

			ASSERT(vlc != 89);
			bool s = pBitStream->getbit();

			int LMAX;
			/*
Table B-19 -- ESCL(a), LMAX values of intra macroblocks
LAST RUN LMAX LAST RUN LMAX
0 0 27 
0 1 10 
0 2 5 
0 3 4 
0 4-7 3 
0 8-9 2
0 10-14 1
0 others N/A*

1 0 8
1 1 3
1 2-6 2
1 7-20 1
1 others N/A
*/
			run = lrltable[vlc].run;

			if (lrltable[vlc].last == 0)
			{
				if (!inter)
				{
					if (run == 0)			LMAX = 27;
					else if (run == 1)	LMAX = 10;
					else if (run == 2)	LMAX = 5;
					else if (run == 3)	LMAX = 4;
					else if (run <= 7)	LMAX = 3;
					else if (run <= 9)	LMAX = 2;
					else if (run <= 14)	LMAX = 1;
					else
						ASSERT(0);
				}
				else
				{
					if (run == 0)	LMAX = 12;
					else if (run == 1)	LMAX = 6;
					else if (run == 2)	LMAX = 4;
					else if (run <= 6)	LMAX = 3;
					else if (run <= 10)	LMAX = 2;
					else if (run <= 26)	LMAX = 1;
					else
						ASSERT(0);
				}
			}
			else	// if (lrl_B16[vlc].last == 1)
			{
				if (!inter)
				{
					if (run == 0)			LMAX = 8;
					else if (run == 1)	LMAX = 3;
					else if (run <= 6)	LMAX = 2;
					else if (run <= 20)	LMAX = 1;
					else
						ASSERT(0);
				}
				else
				{
					if (run == 0)			LMAX = 3;
					else if (run == 1)	LMAX = 2;
					else if (run <= 40)	LMAX = 1;
					else
						ASSERT(0);
				}
			}

			signed_level = lrltable[vlc].level + LMAX;
			if (s == 1)
				signed_level = -signed_level;

			last = lrltable[vlc].last;
		}
/*
Type 2: ESC is followed by “10”, and the code following ESC + “10” is decoded as a variable length code using the
standard Tcoef VLC codes given in Table B-16 and Table B-17, but the values of RUN are modified following
decoding to give the restored value RUNS, as follows:
RUNS= RUN+ + (RMAX + 1)
where RUN+ is the value after variable length decoding. RMAX is obtained from Table B-21 and Table B-22 as a
function of the decoded values of LEVEL and LAST.
*/					else if (pBitStream->getbit() == 0)
		{
		//	int vlc = getvariablebits(pBitStream, vlctable);
			int value = pBitStream->looknbits(12);
			int vlc = vlctable[value].index;
			pBitStream->skipnbits(vlctable[value].len);

			ASSERT(vlc != 89);
			int s = pBitStream->getbit();

			int RMAX;

			int lev = lrltable[vlc].level;
			last = lrltable[vlc].last;

			if (last == 0)
			{
				if (!inter)
				{
					if (lev == 1) RMAX = 14;
					else if (lev == 2) RMAX = 9;
					else if (lev == 3) RMAX = 7;
					else if (lev == 4) RMAX = 3;
					else if (lev == 5) RMAX = 2;
					else if (lev <= 10) RMAX = 1;
					else if (lev <= 27) RMAX = 0;
					else
						ASSERT(0);
				}
				else
				{
					if (lev == 1) RMAX = 26;
					else if (lev == 2) RMAX = 10;
					else if (lev == 3) RMAX = 6;
					else if (lev == 4) RMAX = 2;
					else if (lev <= 6) RMAX = 1;
					else if (lev <= 12) RMAX = 0;
					else
						ASSERT(0);
				}
			}
			else
			{
				if (!inter)
				{
					if (lev == 1) RMAX = 20;
					else if (lev == 2) RMAX = 6;
					else if (lev == 3) RMAX = 1;
					else if (lev <= 8) RMAX = 0;
					else
						ASSERT(0);
				}
				else
				{
					if (lev == 1) RMAX = 40;
					else if (lev == 2) RMAX = 1;
					else if (lev == 3) RMAX = 0;
					else
						ASSERT(0);
				}
			}

			run = lrltable[vlc].run + (RMAX + 1);
			signed_level = lrltable[vlc].level;
			if (s == 1)
				signed_level = -signed_level;
		}
/*
Type 3: ESC is followed by “11”, and the code following ESC + “11” is decoded as fixed length codes. This type of
escape codes are represented by 1-bit LAST, 6-bit RUN and 12-bit LEVEL. A marker bit is inserted before and after
the 12-bit-LEVEL in order to avoid the resync_marker emulation. Use of this escape sequence for encoding the
combinations listed in Table B-16 and Table B-17 is prohibited. The codes for RUN and LEVEL are given in Table
B-18 a and b.
*/					else
		{
			last = pBitStream->getbit();
			run = pBitStream->getnbits(6);

			get_marker_bit(pBitStream);
			//pBitStream->getbit();

			signed_level = pBitStream->getnbits(12);

			get_marker_bit(pBitStream);
			//pBitStream->getbit();

			ASSERT(signed_level != 0);
			if (signed_level == 0)
			{
				ASSERT(0);
				throw L"Error in bitstream";
			}

			int iMaxAC = (1<<(12-1)) - 1;
			ASSERT(signed_level!=iMaxAC+1);
			if (signed_level > iMaxAC)
				signed_level -= (1<<12);
			ASSERT(signed_level != 0);

			/*
			if (signed_level > 2047)
			{
				//signed_level = -(signed_level-2047);
				signed_level |= 0xf000;
			}
			*/
		}
	//	decodeEscape(pBitStream, signed_level, run, last, g_rgiLMAXintra, g_rgiRMAXintra, &d, vlc);
	}
	else
	{
	//	decodeIntraVLCtableIndex(pBitStream, vlc, signed_level, run, last);
		int s = pBitStream->getbit();

		last = lrltable[vlc].last;
		run = lrltable[vlc].run;
		signed_level = lrltable[vlc].level;

		if (s == 1)
			signed_level = -signed_level;
	}

	return last;
}

void VideoObjectPlane::block(System::IO::CBitStream32* pBitStream, int mb_address, int i, int derived_mb_type, int inter, int pattern_code[6], int QFS[8*8])
{
//	CHuffmanDecoder* m_pentrdecIntraDCy = new CHuffmanDecoder ( g_rgVlcIntraDCy);
//	CHuffmanDecoder* m_pentrdecIntraDCc = new CHuffmanDecoder ( g_rgVlcIntraDCc);

	bool use_intra_dc_vlc;

	if (inter == 0)	// intra-macroblock
	{
		if (m_Qp[0] >= grgiDCSwitchingThreshold[m_intra_dc_vlc_thr])
			use_intra_dc_vlc = false;
		else
			use_intra_dc_vlc = true;
	}
	else
	{
		use_intra_dc_vlc = false;
	}

	int n = 0;

	{
		if (!m_config->m_data_partitioned &&
			(derived_mb_type == 3 || derived_mb_type == 4))
		{
		//	ASSERT(pattern_code[i]);	// hm..

			if (m_config->m_short_video_header == 1)
			{
				int intra_dc_coefficient = pBitStream->getnbits(8);// uimsbf
				ASSERT(0);
			}
			else if (use_intra_dc_vlc)
			{
				int dct_dc_size;
				int dct_dc_differential;

				if (i < 4)
				{
					int value = pBitStream->looknbits(11);
					dct_dc_size = table_B13[value].index;
					pBitStream->skipnbits(table_B13[value].len);

					//getvariablebits(pBitStream, table_B13);//, 11);//2-11 vlclbf

					//dct_dc_size = m_pentrdecIntraDCy->decodeSymbol(pBitStream);

					if (m_config->m_bits_per_pixel == 8)	// pixel-depth = 8
					{
						if (dct_dc_size >= 10)
						{
							ASSERT(0);
							throw L"Error in bitstream";
						}
					}

					if (dct_dc_size != 0)
					{
						dct_dc_differential = pBitStream->getnbits(dct_dc_size);

					//	int nbits = GetNBits(dct_dc_differential);
					//	ASSERT(nbits == dct_dc_size);

						//	dct_dc_differential 1-12 vlclbf

						if (dct_dc_size > 8)
							get_marker_bit(pBitStream);// 1 bslbf
					}
				}
				else
				{
					/*
					if (!pattern_code[i])
					{
						MessageBeep(-1);
					}
					*/
				//	dct_dc_size = getvariablebits(pBitStream, table_B14);//, 12);//2-12 vlclbf
				//	dct_dc_size = m_pentrdecIntraDCc->decodeSymbol(pBitStream);
					int value = pBitStream->looknbits(12);
					dct_dc_size = table_B14[value].index;
					pBitStream->skipnbits(table_B14[value].len);

					if (m_config->m_bits_per_pixel == 8)	// pixel-depth = 8
					{
						if (dct_dc_size >= 10)
						{
							ASSERT(0);
							throw L"Error in bitstream";
						}
					}

					if (dct_dc_size != 0)
					{
						dct_dc_differential = pBitStream->getnbits(dct_dc_size);
					//	dct_dc_differential 1-12 vlclbf

				//		int nbits = GetNBits(dct_dc_differential);
				//		ASSERT(nbits == dct_dc_size);

						if (dct_dc_size > 8)
							get_marker_bit(pBitStream);// 1 bslbf
					}
				}

				int dct_diff;

				if (dct_dc_size == 0)
				{
					dct_diff = 0;
				}
				else
				{
					if (dct_dc_size<=8)
					{ // NBIT
						char chDiffIntraDC = dct_dc_differential;
						//	(BYTE) m_pentrdecSet->m_pentrdecIntraDCy->bitstream()->getBits (lSzDiffIntraDC);	
						if (!((1 << (dct_dc_size - 1)) & chDiffIntraDC))
							dct_diff = -1 * ((0x00FF >> (8 - dct_dc_size)) & (~chDiffIntraDC));
						else
							dct_diff = (int) chDiffIntraDC;
					}
					else
					{
						ASSERT(0);
					}

#if 0
					int half_range = pow(2, dct_dc_size - 1);	// TODO use 1<<...
					if (dct_dc_differential >= half_range)
						dct_diff = dct_dc_differential;
					else
						dct_diff = (dct_dc_differential + 1) - (2 * half_range);
#endif
				}
				QFS[0] = dct_diff;
	#if 0
				QFS[0] = m_dc_dct_pred[cc] + dct_diff;
	#endif
			//	m_dc_dct_pred[cc] = QFS[0];

				n = 1;	// Done first one
			}
		}

		if (pattern_code[i])
		{
			vtab_byte* vlctable;
			lrl* lrltable;
			//int escape;
			if (inter)
			{
				vlctable = table_B17;
				lrltable = lrl_B17;
			//	escape = 89;
			}
			else
			{
				vlctable = table_B16;
				lrltable = lrl_B16;
			//	escape = 89;
			}

			if (m_config->m_short_video_header == 1)
			{
	// Fourth method is used
				ASSERT(0);
			}
			else if (!m_config->m_reversible_vlc)
			{
				/*
	The first three of these modes are used when short_video_header is 0 and in the case that the reversible
	VLC tables are not used,
	*/
				bool last = 0;

			//	CHuffmanDecoder d(g_rgVlcDCTIntra);

				do
				{
					int run;
					int signed_level;
					last = GetLevelRun(pBitStream, vlctable, lrltable, inter, run, signed_level);

					if (n+run+1 > 64)
					{
#if 0
						ASSERT(0);
						throw "Error in bitstream";
#endif
						TRACE("Error in bitstream");
						run = 0;
						THROW(-1);
					}

					for (int m = 0; m < run; m++)
					{
						QFS[n] = 0;
						n++;
					}
					QFS[n] = signed_level;
					n++;

#if _DEBUG
					if (n == 64)
					{
						ASSERT(last);
					}
#endif
				}
				while (!last);
			}
			else
			{
	/* In the case that the reversible VLC
	tables are used, the fifth escape coding method as in Table B-23 is used.
	*/
				ASSERT(0);
			}
		}
		/*
		else
		{
			MessageBeep(-1);
		}
		*/
	}

	// Set remaining to zero
	while (n < 64)
	{
		QFS[n++] = 0;
	}
}

/*
NOTE : “last” is defined to be the LAST flag resulting from reading the most recent DCT coefficient.

/*
6.2.7.1 Alpha Block
The syntax for DCT coefficient decoding is the same as for block(i) in subclause 6.2.8.
*/
/*
alpha_block( i )
{
last = 0
if(!data_partitioned &&
(vop_coding_type == “I” || (vop_coding_type == “P” ||
(vop_coding_type == “S” && sprite_enable == “GMC”))
&& !not_coded &&
(derived_mb_type == 3 || derived_mb_type == 4)))) {
dct_dc_size_alpha 2-11 vlclbf
if(dct_dc_size_alpha != 0)
dct_dc_differential 1-12 vlclbf
if (dct_dc_size_alpha > 8)
marker_bit 1 bslbf
}
if ( pattern_code[i] )
while ( ! last )
DCT coefficient 3-24 vlclbf
}
*/

void VideoObjectPlane::interlaced_information(System::IO::CBitStream32* pBitStream, int mb_type, int derived_mb_type, int mcsel)
{
	TRACE("Interlaced, not yet supported");
	ASSERT(0);

#if 0
	if ((derived_mb_type == 3) || (derived_mb_type == 4) || (cbp != 0))
	{
		int dct_type = pBitStream->getbit();//1 bslbf
	}

	if ( ((m_vop_coding_type == Coded_P) &&
		((derived_mb_type == 0) || (derived_mb_type == 1)) ) ||
		((m_config->m_sprite_enable == SpriteEnabled_GMC) && (m_vop_coding_type == Coded_S) &&
		(derived_mb_type < 2) && (!mcsel)) ||
		((m_vop_coding_type == Coded_B) && (mb_type != 1)) )
	{
		ASSERT(0);
#if 0
		field_prediction 1 bslbf

		if (field_prediction)
		{
			if (vop_coding_type == “P” ||
				(vop_coding_type == “B” &&
				mb_type != “001”) )
			{
				forward_top_field_reference 1 bslbf
				forward_bottom_field_reference 1 bslbf
			}
			if ((vop_coding_type == “B”) &&
				(mb_type != “0001”) )
			{
				backward_top_field_reference 1 bslbf
				backward_bottom_field_reference 1 bslbf
			}
		}
#endif
	}
#endif
}

enum
{
	MotionMode_forward,
	MotionMode_backward,
	MotionMode_direct,
};

int get_mv_data(System::IO::CBitStream32* pBitStream)
{
	int value = pBitStream->looknbits(13);//getvariablebits(pBitStream, table_B12, 13)-32
	pBitStream->skipnbits(table_B12[value].len);
	return table_B12[value].index - 32;
}

void VideoObjectPlane::motion_vector(System::IO::CBitStream32* pBitStream, int mode)
{
	if (mode == MotionMode_direct)
	{
		ASSERT(0);
#if 0
		horizontal_mv_data 1-13 vlclbf
		vertical_mv_data 1-13 vlclbf
#endif
	}
	else if (mode == MotionMode_forward)
	{
		m_horizontal_mv_data = get_mv_data(pBitStream);
		if ((m_vop_fcode_forward != 1) && (m_horizontal_mv_data != 0))
		{
			// r_size = vop_fcode_forward - 1 or r_size = vop_fcode_backward - 1
			m_horizontal_mv_residual = pBitStream->getnbits(m_vop_fcode_forward-1);	//1-6 uimsbf
		}

		m_vertical_mv_data = get_mv_data(pBitStream);
		if ((m_vop_fcode_forward != 1) && (m_vertical_mv_data != 0))
		{
			m_vertical_mv_residual = pBitStream->getnbits(m_vop_fcode_forward-1);	// 1-6 uimsbf
		}
	}
	else if (mode == MotionMode_backward)
	{
		ASSERT(0);
#if 0
		horizontal_mv_data 1-13 vlclbf
		if ((vop_fcode_backward != 1) && (horizontal_mv_data != 0))
			horizontal_mv_residual 1-6 uimsbf
		vertical_mv_data 1-13 vlclbf
		if ((vop_fcode_backward != 1) && (vertical_mv_data != 0))
			vertical_mv_residual 1-6 uimsbf
#endif
	}
}

int VideoObjectPlane::clip_ref(uint8* ref, int component_size, int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x > m_mb_cols * component_size-1)
		x = m_mb_cols * component_size-1;

	if (y < 0)
		y = 0;
	else if (y > m_mb_rows * component_size-1)
		y = m_mb_rows * component_size-1;

	return ref[y * m_mb_cols * component_size + x];
}

void VideoObjectPlane::mc(short pred[8][8], uint8* ref, int component_size, int x, int y, int width, int height, int dx_halfpel, int dy_halfpel)
{
	int dx = dx_halfpel >> 1;
	int dy = dy_halfpel >> 1;

	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			int x_ref = x + dx + ix;
			int y_ref = y + dy + iy;

			if (dy_halfpel & 1)
			{
				if (dx_halfpel & 1)
				{
					pred[iy][ix] = (
						clip_ref(ref, component_size, x_ref+0, y_ref+0) +
						clip_ref(ref, component_size, x_ref+1, y_ref+0) +
						clip_ref(ref, component_size, x_ref+0, y_ref+1) +
						clip_ref(ref, component_size, x_ref+1, y_ref+1) +
						2/*rounding*/) / 4;
				}
				else
				{
					pred[iy][ix] = (
						clip_ref(ref, component_size, x_ref, y_ref+0) +
						clip_ref(ref, component_size, x_ref, y_ref+1) +
						1/*rounding*/) / 2;
				}
			}
			else
			{
				if (dx_halfpel & 1)
				{
					pred[iy][ix] = (
						clip_ref(ref, component_size, x_ref+0, y_ref) +
						clip_ref(ref, component_size, x_ref+1, y_ref) +
						1/*rounding*/) / 2;
				}
				else
				{
					pred[iy][ix] = clip_ref(ref, component_size, x_ref, y_ref);
				}
			}
		}
	}
}

void VideoObjectPlane::macroblock(System::IO::CBitStream32* pBitStream, int mb_address)
{
	int block_count = 6;	// 4:2:0 chroma format (the only one supported in MPEG4)

	if (m_vop_coding_type != Coded_B)
	{
		if (m_config->m_video_object_layer_shape != LayerShape_rectangular
			&& !(m_config->m_sprite_enable == SpriteEnabled_static && m_config->m_low_latency_sprite_enable
			&& m_sprite_transmit_mode == SpriteTransmit_update))
		{
			ASSERT(0);
#if 0
			mb_binary_shape_coding();
#endif
		}

		if (m_config->m_video_object_layer_shape != LayerShape_binary_only)
		{
			if (!transparent_mb())
			{
				int not_coded = 0;

				int derived_mb_type = 0;
				int pattern_code[6] = {1,1,1,1,1,1};
				int ac_pred_flag = 0;
				int inter = 99999;	// Not yet set, TODO remove

				if (m_config->m_video_object_layer_shape != LayerShape_rectangular && !(m_config->m_sprite_enable = SpriteEnabled_static && m_config->m_low_latency_sprite_enable && m_sprite_transmit_mode == SpriteTransmit_update))
				{
					ASSERT(0);
#if 0
					do
					{
						if (m_vop_coding_type != Coded_I && !(m_config->m_sprite_enable == SpriteEnabled_static && m_sprite_transmit_mode == SpriteTransmit_piece))
						{
							not_coded 1 bslbf
						}
		
						if (!not_coded || m_vop_coding_type == Coded_I
							|| (m_vop_coding_type == Coded_S
							&& low_latency_sprite_enable
							&& m_sprite_transmit_mode == SpriteTransmit_piece))
						{
							ASSERT(0);
						mcbpc 1-9 vlclbf
						}
					}
					while(!(not_coded || derived_mb_type != “stuffing”))
#endif
				}
				else
				{
					// TODO, the following logic can be improved
					if (m_vop_coding_type != Coded_I && !(m_config->m_sprite_enable == SpriteEnabled_static && m_sprite_transmit_mode == SpriteTransmit_piece))
					{
						not_coded = pBitStream->getbit();//1 bslbf
					}
					if (not_coded)
					{
					;//	TRACE("not_coded\n");
					}
	
					// TODO, the following logic can be improved
					if (!not_coded ||
						(m_vop_coding_type == Coded_I) ||
						(m_vop_coding_type == Coded_S && m_config->m_low_latency_sprite_enable && m_sprite_transmit_mode == SpriteTransmit_piece))
					{
						if (m_vop_coding_type == Coded_I)
						{
							//CHuffmanDecoder* m_pentrdecMCBPCintra = new CHuffmanDecoder (g_rgVlcMCBPCintra);

							//derived_mb_type = m_pentrdecMCBPCintra
							int mcbpc = 8;
							while (mcbpc == 8)
							{
							//	mcbpc = m_pentrdecMCBPCintra->decodeSymbol (pBitStream);
								mcbpc = getvariablebits(pBitStream, table_B6, 9);
							}
//#if 0
							//mcbpc 1-9 vlclbf
/*
VLC table for mcbpc for I-VOPs and S-VOPs with low_latence_sprite_enable==1 and
sprite_transmit_mode==”piece”*/
//							int mcbpc = getvariablebits(pBitStream, table_B6, 9);

							derived_mb_type = mcbpc_B6[mcbpc].mbtype;
					//		pattern_code[4] = (mcbpc_B6[mcbpc].cbpc & 1) == 1;
					//		pattern_code[5] = (mcbpc_B6[mcbpc].cbpc & 2) == 2;

							int iCBPC = mcbpc & 3;

							pattern_code[4] = ((iCBPC >> 1));
							pattern_code[5] = (iCBPC & 1);

						//	ASSERT(((iCBPC >> 1) & 1) == (pattern_code[4]!=0));
						//	ASSERT(((iCBPC & 1)) == (pattern_code[5]!=0));

//#endif
							inter = 0;
						}
						else if (m_vop_coding_type == Coded_P)
						{
							/*
VLC table for mcbpc for P-VOPs and S-VOPs with low_latence_sprite_enable==1 and
sprite_transmit_mode==”update”, and S(GMC)-VOPs							
							*/
							int mcbpc = getvariablebits(pBitStream, table_B7, 9);

							derived_mb_type = mcbpc_B7[mcbpc].mbtype;
#if 0
							pattern_code[4] = (mcbpc_B7[mcbpc].cbpc & 1) == 1;
							pattern_code[5] = (mcbpc_B7[mcbpc].cbpc & 2) == 2;
#endif
							int iCBPC = mcbpc % 4;

							pattern_code[4] = ((iCBPC >> 1) & 1);
							pattern_code[5] = ((iCBPC & 1));

							if (derived_mb_type == 3 || derived_mb_type == 4)
								inter = 0;	// 0 ??
							else
								inter = 1;	// ??
						}
						/*
						P-VOPs using the short video header format (i.e., when short_video_header is 1), mcbpc codes indicating
						macroblock type 2 shall not be used.
						*/
						if (m_config->m_short_video_header && m_vop_coding_type == Coded_P)
						{
							ASSERT(derived_mb_type != 2);
						}
					}
				}
				/*
					{
						int nextbits;

						nextbits = nextbits_bytealigned(pBitStream, 16+1);
						if (nextbits == 1)	// resync marker
						{
							ASSERT(0);
						}

						nextbits = nextbits_bytealigned(pBitStream, 23);
						if (nextbits == 0)	// start-code
						{
							ASSERT(0);
						}
					}
					*/

				if (	!not_coded || m_vop_coding_type == Coded_I
						|| (m_vop_coding_type == Coded_S && m_config->m_low_latency_sprite_enable
						&& m_sprite_transmit_mode == SpriteTransmit_piece))
				{
					int mcsel = 0;

					if (m_vop_coding_type == Coded_S && m_config->m_sprite_enable == SpriteEnabled_GMC && (derived_mb_type == 0 || derived_mb_type == 1))
					{
						ASSERT(0);
						mcsel = pBitStream->getbit();//1 bslbf
					}
	
					if (!m_config->m_short_video_header &&
						(derived_mb_type == 3 || derived_mb_type == 4))
					{
						ac_pred_flag = pBitStream->getbit();//1 bslbf
						if (ac_pred_flag)
						{
							//MessageBeep(-1);
						}
					}
					/*
					{
						int nextbits;

						nextbits = nextbits_bytealigned(pBitStream, 16+1);
						if (nextbits == 1)	// resync marker
						{
							ASSERT(0);
						}

						nextbits = nextbits_bytealigned(pBitStream, 23);
						if (nextbits == 0)	// start-code
						{
							ASSERT(0);
						}
					}
					*/

					if (derived_mb_type != -1/*“stuffing”*/)
					{
					//	cbpy 1-6 vlclbf
						int cbpy = getvariablebits(pBitStream, table_B8, 6);

					//	BYTE* p = cbpy_B8;

						//int y = cbpy_B8[2][1];

						/*
						if (inter)
							cbpy = 15-cbpy;
							*/

						/*
						pattern_code[0] = (cbpy & 1) == 1;
						pattern_code[1] = (cbpy & 2) == 2;
						pattern_code[2] = (cbpy & 4) == 4;
						pattern_code[3] = (cbpy & 8) == 8;
						*/
						pattern_code[0] = (cbpy_B8[cbpy][inter] & 1) == 1;
						pattern_code[1] = (cbpy_B8[cbpy][inter] & 2) == 2;
						pattern_code[2] = (cbpy_B8[cbpy][inter] & 4) == 4;
						pattern_code[3] = (cbpy_B8[cbpy][inter] & 8) == 8;
					}
					else
					{
						ASSERT(0);
/*
						int mb_row = mb_address / m_mb_cols;
						int mb_column = mb_address % m_mb_cols;

						ASSERT(inter);

						for (int i = 0; i < block_count; i++)
						{
							BYTE p[8][8];
							if (inter)
							{
								if (i < 4)
								{
									int nrow = i/2;
									int ncol = i%2;

									for (int y = 0; y < 8; y++)
									{
										for (int x = 0; x < 8; x++)
										{
											int index = (mb_row*m_mb_cols*16*16 + mb_column*16) + (nrow*8*m_mb_cols*16 + ncol*8) + (y*m_mb_cols*16 + x);
											p[y][x] = m_pDecoder->pPrevVOP->m_ybuf[index];
										}
									}
								}
								else
								{
									BYTE* buf;
									if (i == 5)
										buf = m_pDecoder->pPrevVOP->m_cbbuf;
									else
										buf = m_pDecoder->pPrevVOP->m_crbuf;

									for (int y = 0; y < 8; y++)
									{
										for (int x = 0; x < 8; x++)
										{
											int index = (mb_row*m_mb_cols*8*8 + mb_column*8) + (0*8*m_mb_cols*8 + 0*8) + (y*m_mb_cols*8 + x);
											p[y][x] = buf[index];
										}
									}
								}
							}

							if (i < 4)
							{
								int nrow = i/2;
								int ncol = i%2;

								for (int y = 0; y < 8; y++)
								{
									for (int x = 0; x < 8; x++)
									{
										int index = (mb_row*m_mb_cols*16*16 + mb_column*16) + (nrow*8*m_mb_cols*16 + ncol*8) + (y*m_mb_cols*16 + x);
										m_ybuf[index] = p[y][x];
									}
								}
							}
							else
							{
								BYTE* buf;
								if (i == 5)
									buf = m_cbbuf;
								else
									buf = m_crbuf;

								for (int y = 0; y < 8; y++)
								{
									for (int x = 0; x < 8; x++)
									{
										int index = (mb_row*m_mb_cols*8*8 + mb_column*8) + (0*8*m_mb_cols*8 + 0*8) + (y*m_mb_cols*8 + x);
										buf[index] = p[y][x];
									}
								}
							}
						}

						return;
						*/
					}

					MacroBlock* pmb = m_macroblocks + mb_address;
					int mb_row = mb_address / m_mb_cols;
					int mb_column = mb_address % m_mb_cols;

					pmb->m_quantiser_scale = m_Qp[0];

					if (derived_mb_type == 1 || derived_mb_type == 4)
					{
						int dquant = pBitStream->getnbits(2);// bslbf
						switch (dquant)
						{
						case 0: pmb->m_quantiser_scale -= 1; break;
						case 1: pmb->m_quantiser_scale -= 2; break;
						case 2: pmb->m_quantiser_scale += 1; break;
						case 3: pmb->m_quantiser_scale += 2; break;
						}
						int range = (1<<m_config->m_quant_precision)-1;

						if (pmb->m_quantiser_scale < 1)
							pmb->m_quantiser_scale = 1;
						else if (pmb->m_quantiser_scale > range)
							pmb->m_quantiser_scale = range;
					}

					if (m_config->m_interlaced)
					{
						interlaced_information(pBitStream, -1/*mb_type, only used in B-VOP*/, derived_mb_type, mcsel);
					}

					/*
					{
						int nextbits;

						nextbits = nextbits_bytealigned(pBitStream, 16+1);
						if (nextbits == 1)	// resync marker
						{
							ASSERT(0);
						}

						nextbits = nextbits_bytealigned(pBitStream, 23);
						if (nextbits == 0)	// start-code
						{
							ASSERT(0);
						}
					}
					*/

					m_horizontal_mv_data = 99999;
					m_vertical_mv_data = 99999;

					if ( !(m_ref_select_code == 3 && m_config->m_scalability)
							&& m_config->m_sprite_enable != SpriteEnabled_static)
					{
						if (	(derived_mb_type == 0 || derived_mb_type == 1)
								&& (m_vop_coding_type == Coded_P
								|| (m_vop_coding_type == Coded_S && !mcsel)))
						{
							motion_vector(pBitStream, MotionMode_forward);	// one motion vector for entire macroblock
#if 0	// TODO
							if (m_interlaced && field_prediction)
								motion_vector(“forward”)
#endif
						}
				//		else //???
						if (derived_mb_type == 2)
						{
							// 4 motion vectors for macroblock
							ASSERT(0);
							for (int j = 0; j < 4; j++)
							{
								if (!transparent_block(j))
								{
									motion_vector(pBitStream, MotionMode_forward);
								}
							}
						}
					}

					/*
					if (mb_address == 0)	// First macroblock
					{
			// Initialize running Qp to quantization parameter (m_quantiser_scale)
						m_Qp[0] = pmb->m_quantiser_scale;
						m_Qp[1] = pmb->m_quantiser_scale;
					}
					*/
					// Running Qp, the next macroblock will use this macroblocks quantization parameter
					m_Qp[0] = pmb->m_quantiser_scale;
					m_Qp[1] = pmb->m_quantiser_scale;

					if (inter)
					{
						for (int i = 0; i < 1; i++)
						{
							int* pMV1 = NULL;
							int* pMV2 = NULL;
							int* pMV3 = NULL;

							int MV1[2];
							int MV2[2];
							int MV3[2];

							if (i == 0)
							{
								if (mb_column > 0)
								{
									pMV1 = pmb[-1].motion_vector[1];
									MV1[0] = pMV1[0];
									MV1[1] = pMV1[1];
								}

								if (mb_row > 0)
								{
									pMV2 = pmb[- m_mb_cols].motion_vector[2];
									MV2[0] = pMV2[0];
									MV2[1] = pMV2[1];
								}

								if (mb_column < m_mb_cols-1)
								{
									if (mb_row > 0)
									{
										// This is what the spec says ?
										pMV3 = pmb[ 1 - m_mb_cols].motion_vector[2];

									
										// ?? This seems more correct ??
									//	pMV3 = pmb[- m_mb_cols].motion_vector[3];
										MV3[0] = pMV3[0];
										MV3[1] = pMV3[1];
									}
								}
							}
							else if (i == 1)
							{
								pMV1 = pmb->motion_vector[0];
								MV1[0] = pMV1[0];
								MV1[1] = pMV1[1];

								if (mb_row > 0)
								{
									pMV2 = pmb[-m_mb_cols].motion_vector[3];
									MV2[0] = pMV2[0];
									MV2[1] = pMV2[1];

									if (mb_column < m_mb_cols-1)
									{
										pMV3 = pmb[ 1 - m_mb_cols].motion_vector[2];
										MV3[0] = pMV3[0];
										MV3[1] = pMV3[1];
									}
								}
							}
							else if (i == 2)
							{
								if (mb_column > 0)
								{
									pMV1 = pmb[-1].motion_vector[1];
									MV1[0] = pMV1[0];
									MV1[1] = pMV1[1];
								}

								pMV2 = pmb->motion_vector[0];
								MV2[0] = pMV2[0];
								MV2[1] = pMV2[1];

								pMV3 = pmb->motion_vector[1];
								MV3[0] = pMV3[0];
								MV3[1] = pMV3[1];
							}
							else if (i == 3)
							{
								pMV1 = pmb->motion_vector[2];
								MV1[0] = pMV1[0];
								MV1[1] = pMV1[1];

								pMV2 = pmb->motion_vector[0];
								MV2[0] = pMV2[0];
								MV2[1] = pMV2[1];

								pMV3 = pmb->motion_vector[1];
								MV3[0] = pMV3[0];
								MV3[1] = pMV3[1];
							}

							if (pMV1 == NULL && pMV2 == NULL && pMV3 == NULL)	// All three are invalid
							{
								MV1[0] = MV2[0] = MV3[0] = 0;
								MV1[1] = MV2[1] = MV3[1] = 0;
							}
						// Two invalid
						// They are set to the valid one
						// TODO, the median can now just be set directly since they're all equal
							else if (pMV2 == NULL && pMV3 == NULL)
							{
								MV2[0] = MV1[0];
								MV2[1] = MV1[1];

								MV3[0] = MV1[0];
								MV3[1] = MV1[1];
							}
							else if (pMV1 == NULL && pMV3 == NULL)
							{
								MV1[0] = MV2[0];
								MV1[1] = MV2[1];

								MV3[0] = MV2[0];
								MV3[1] = MV2[1];
							}
							else if (pMV1 == NULL && pMV2 == NULL)
							{
								MV1[0] = MV3[0];
								MV1[1] = MV3[1];

								MV2[0] = MV3[0];
								MV2[1] = MV3[1];
							}
						// one invalid, it is set to zero
							else if (pMV3 == NULL)
							{
								MV3[0] = 0;
								MV3[1] = 0;
							}
							else if (pMV2 == NULL)
							{
								MV2[0] = 0;
								MV2[1] = 0;
							}
							else if (pMV1 == NULL)
							{
								MV1[0] = 0;
								MV1[1] = 0;
							}

							int Px = Median(MV1[0], MV2[0], MV3[0]);
							int Py = Median(MV1[1], MV2[1], MV3[1]);

							int vop_fcode = m_vop_fcode_forward;

							int r_size = vop_fcode - 1;
							int f = 1 << r_size;
							int high = ( 32 * f ) - 1;
							int low = ( (-32) * f );
							int range = ( 64 * f );

							int MVDx;
							int MVDy;

							if (m_horizontal_mv_data == 99999)
								MessageBeep(-1);

							if ( (f == 1) || (m_horizontal_mv_data == 0) )
								MVDx = m_horizontal_mv_data;
							else
							{
								MVDx = ( ( abs(m_horizontal_mv_data) - 1 ) * f ) + m_horizontal_mv_residual + 1;
								if (m_horizontal_mv_data < 0)
									MVDx = - MVDx;
							}

							if ( (f == 1) || (m_vertical_mv_data == 0) )
								MVDy = m_vertical_mv_data;
							else
							{
								MVDy = ( ( abs(m_vertical_mv_data) - 1 ) * f ) + m_vertical_mv_residual + 1;
								if (m_vertical_mv_data < 0)
									MVDy = - MVDy;
							}

	#if 0	// TODO
							if(quarter_sample==1)
							{
								MVDx = MVDx / 2.0;
								MVDy = MVDy / 2.0;
							}
	#endif

							int MVx = Px + MVDx;
							if ( MVx < low )
								MVx = MVx + range;
							if (MVx > high)
								MVx = MVx - range;

							int MVy = Py + MVDy;
							if ( MVy < low )
								MVy = MVy + range;
							if (MVy > high)
								MVy = MVy - range;

							pmb->motion_vector[i][0] = MVx;
							pmb->motion_vector[i][1] = MVy;
						}

						pmb->motion_vector[1][0] = pmb->motion_vector[0][0];
						pmb->motion_vector[1][1] = pmb->motion_vector[0][1];
						pmb->motion_vector[2][0] = pmb->motion_vector[0][0];
						pmb->motion_vector[2][1] = pmb->motion_vector[0][1];
						pmb->motion_vector[3][0] = pmb->motion_vector[0][0];
						pmb->motion_vector[3][1] = pmb->motion_vector[0][1];
					}

					for (int i = 0; i < block_count; i++)
					{
						if (!transparent_block(i))
						{
							int QFS[8*8];
							block(pBitStream, mb_address, i, derived_mb_type, inter, pattern_code, QFS);

							/*
							if (m_vop_coding_type == Coded_P && i == 0)
							{
								TRACE("mb: %d, %d\n", mb_address, QFS[0]);
							}
							*/

							//if (m_vop_coding_type == Coded_I)
							{
								short f[8][8];
								decode_block(mb_address, i, ac_pred_flag, !inter, QFS, f);
								idct((short*)f);

								short p[8][8];
							//		memset(p, 0, sizeof(p));
								if (inter)
								{
									VideoObjectPlane* refVOP = m_pPrevVOP;
								//	if (m_pPrevVOP == NULL)
								//		THROW(-1);
									ASSERT(refVOP);

									if (i < 4)
									{
										int nrow = i >> 1;
										int ncol = i & 1;

										mc(p, refVOP->m_ybuf, 16, mb_column*16 + ncol*8, mb_row*16 + nrow*8, 8, 8, pmb->motion_vector[i][0], pmb->motion_vector[i][1]);
									}
									else if (i == 4)
									{
										mc(p, refVOP->m_crbuf, 8, mb_column*8, mb_row*8, 8, 8, pmb->motion_vector[0][0]>>1, pmb->motion_vector[0][1]>>1);
									}
									else if (i == 5)
									{
										mc(p, refVOP->m_cbbuf, 8, mb_column*8, mb_row*8, 8, 8, pmb->motion_vector[0][0]>>1, pmb->motion_vector[0][1]>>1);
									}
								}
								/*
								if (inter)
								{
									if (i < 4)
									{
										int nrow = i/2;
										int ncol = i%2;

										for (int y = 0; y < 8; y++)
										{
											for (int x = 0; x < 8; x++)
											{
												int index = (mb_row*m_mb_cols*16*16 + mb_column*16) + (nrow*8*m_mb_cols*16 + ncol*8) + (y*m_mb_cols*16 + x);
												p[y][x] = m_pDecoder->pPrevVOP->m_ybuf[index];
											}
										}
									}
									else
									{
										BYTE* buf;
										if (i == 5)
											buf = m_pDecoder->pPrevVOP->m_cbbuf;
										else
											buf = m_pDecoder->pPrevVOP->m_crbuf;

										for (int y = 0; y < 8; y++)
										{
											for (int x = 0; x < 8; x++)
											{
												int index = (mb_row*m_mb_cols*8*8 + mb_column*8) + (0*8*m_mb_cols*8 + 0*8) + (y*m_mb_cols*8 + x);
												p[y][x] = buf[index];
											}
										}
									}
								}
								*/
								else
								{
									std::memset(p, 0, sizeof(p));
								}

								short d[8][8];
								{
									for (int y = 0; y < 8; y++)
									{
										for (int x = 0; x < 8; x++)
										{
											int dyx = f[y][x] + p[y][x];	// p[y][x] is used on the spec?
											
										//	int dyx;
											/*
											if (inter)
												dyx = p[y][x];
											else
												*/
										//		dyx = f[y][x];

											if (dyx < 0) dyx = 0;
											else if (dyx > 255) dyx = 255;

											d[y][x] = dyx;
										}
									}
								}

								if (i < 4)
								{
									int nrow = i/2;
									int ncol = i%2;

									for (int y = 0; y < 8; y++)
									{
										for (int x = 0; x < 8; x++)
										{
											int index = (mb_row*m_mb_cols*16*16 + mb_column*16) + (nrow*8*m_mb_cols*16 + ncol*8) + (y*m_mb_cols*16 + x);
											m_ybuf[index] = d[y][x];
										}
									}
								}
								else
								{
									uint8* buf;
									if (i == 5)
										buf = m_cbbuf;
									else
										buf = m_crbuf;

									for (int y = 0; y < 8; y++)
									{
										for (int x = 0; x < 8; x++)
										{
											int index = (mb_row*m_mb_cols*8*8 + mb_column*8) + (0*8*m_mb_cols*8 + 0*8) + (y*m_mb_cols*8 + x);
											buf[index] = d[y][x];
										}
									}
								}
							}
						}
					}

					// Running Qp, the next macroblock will use this macroblocks quantization parameter
					m_Qp[0] = pmb->m_quantiser_scale;
					m_Qp[1] = pmb->m_quantiser_scale;
				}
				else
				{
					MacroBlock* pmb = m_macroblocks + mb_address;
					pmb->m_intra = 0;
				}
			}
		}
	}
	else
	{
#if 0
		if (m_config->m_video_object_layer_shape != LayerShape_rectangular)
			mb_binary_shape_coding();
	if ((co_located_not_coded != 1 || (m_config->m_scalability && (ref_select_code != '11'
	|| enhancement_type == 1)) || (sprite_enable == “GMC”
	&& backward_reference_vop_coding_type == “S”))
	&& video_object_layer_shape != “binary only”) {
	if (!transparent_mb()) {
	modb 1-2 vlclbf
	if (modb != ‘1’) {
	mb_type 1-4 vlclbf
	if (modb == ‘00’)
	cbpb 3-6 vlclbf
	if (ref_select_code != ‘00’ || !scalability) {
	if (mb_type != “1” && cbpb!=0)
	dbquant 1-2 vlclbf
	if (interlaced)
	interlaced_information()
	Licensed to /SIGURD LERSTAD
	ISO Store order #: 576358/Downloaded: 2004-01-03
	Single user licence only, copying and networking prohibited
	ISO/IEC 14496-2:2001(E)
	© ISO/IEC 2001 – All rights reserved 55
	if (mb_type == ‘01’ ||
	mb_type == ‘0001’) {
	motion_vector(“forward”)
	if (interlaced && field_prediction)
	motion_vector(“forward”)
	}
	if (mb_type == ‘01’ || mb_type == ‘001’) {
	motion_vector(“backward”)
	if (interlaced && field_prediction)
	motion_vector(“backward”)
	}
	if (mb_type == “1”)
	motion_vector(“direct”)
	}
	if (ref_select_code == ‘00’ && scalability &&
	cbpb !=0 ) {
	dbquant 1-2 vlclbf
	if (mb_type == ‘01’ || mb_type == ‘1’)
	motion_vector(“forward”)
	}
	for (i = 0; i < block_count; i++)
	if(!transparent_block(i))
	block(i)
	}
	}
	}
#endif
	}

	if (m_config->m_video_object_layer_shape == LayerShape_grayscale && !transparent_mb())
	{
		ASSERT(0);
#if 0
		for(int j = 0; j < aux_comp_count; j++)
		{
			if(vop_coding_type==”I” || ((vop_coding_type==”P” ||
				(vop_coding_type==”S” && sprite_enable==”GMC”))
				&& !not_coded &&
				(derived_mb_type==3 || derived_mb_type==4)))
			{
				coda_i 1 bslbf
				if(coda_i==”coded”)
				{
					ac_pred_flag_alpha 1 bslbf
					cbpa 1-6 vlclbf
					for(i=0;i<alpha_block_count;i++)
						if(!transparent_block())
							alpha_block(i)
				}
			}
			else
			{ /* P, S(GMC) or B macroblock */
				if(vop_coding_type == ”P” || (sprite_enable == “GMC” &&
					(vop_coding_type==“S”
					|| backward_reference_vop_coding_type==“S”))
					|| co_located_not_coded != 1)
				{
					coda_pb 1-2 vlclbf
					if(coda_pb==”coded”)
					{
						cbpa 1-6 vlclbf
						for(i=0;i<alpha_block_count;i++)
							if(!transparent_block())
								alpha_block(i)
					}
				}
			}
		}
#endif
	}
}
/*
NOTE: The value of block_count is 6 in the 4:2:0 format. The value of alpha_block_count is 4.
backward_reference_vop_coding_type means the vop_coding_type of the backward reference VOP as described
in subclause 7.6.7.
*/

void next_resync_marker(System::IO::CBitStream32* pBitStream)
{
	int bit = pBitStream->getnbits(1);
	ASSERT(bit == 0);
	while (!pBitStream->is_byte_aligned())
	{
		int bit = pBitStream->getnbits(1);
		ASSERT(bit == 1);
	}
}

void VideoObjectPlane::video_packet_header(System::IO::CBitStream32* pBitStream)
{
	next_resync_marker(pBitStream);
	int resync_marker = pBitStream->getnbits(17);
	ASSERT(resync_marker == 1);

//resync_marker 17-23 uimsbf
	if (m_config->m_video_object_layer_shape != LayerShape_rectangular)
	{
		ASSERT(0);
#if 0
		header_extension_code 1 bslbf
		if (header_extension_code
			&& !(sprite_enable = “static“ && vop_coding_type == “I”))
		{
			vop_width 13 uimsbf
			marker_bit 1 bslbf
			vop_height 13 uimsbf
			marker_bit 1 bslbf
			vop_horizontal_mc_spatial_ref 13 simsbf
			marker_bit 1 bslbf
			vop_vertical_mc_spatial_ref 13 simsbf
			marker_bit 1 bslbf
		}
#endif
	}

	int macroblock_count;
	if (m_config->m_reduced_resolution_vop_enable)
	{
		macroblock_count = (m_mb_rows)*(m_mb_cols);
	}
	else
	{
	}

	macroblock_count = GetNBits((m_mb_cols * m_mb_rows)-1);

	int macroblock_number = pBitStream->getnbits(macroblock_count);//(1-14 vlclbf
	if (m_config->m_video_object_layer_shape != LayerShape_binary_only)
	{
		int quant_scale = pBitStream->getnbits(5);// uimsbf	// TODO ??

		m_Qp[0] = quant_scale;
	}

	int header_extension_code = 0;
	if (m_config->m_video_object_layer_shape == LayerShape_rectangular)
		header_extension_code = pBitStream->getbit();//1 bslbf
	if (header_extension_code)
	{
		int modulo_time_base;
		do
		{
			modulo_time_base = pBitStream->getbit();//1 bslbf
		}
		while (modulo_time_base != 0);

		get_marker_bit(pBitStream);// 1 bslbf
		//vop_time_increment 1-16 bslbf
		int vop_time_increment_length = GetNBits(m_config->m_vop_time_increment_resolution);
		uint16 vop_time_increment = pBitStream->getnbits(vop_time_increment_length);//1-16 uimsbf

		get_marker_bit(pBitStream);//1 bslbf
		int vop_coding_type = pBitStream->getnbits(2);// uimsbf
		if (m_config->m_video_object_layer_shape != LayerShape_rectangular)
		{
			ASSERT(0);
#if 0
			change_conv_ratio_disable 1 bslbf
			if (vop_coding_type != “I”)
				vop_shape_coding_type 1 bslbf
#endif
		}
		if (m_config->m_video_object_layer_shape != LayerShape_binary_only)
		{
			m_intra_dc_vlc_thr = pBitStream->getnbits(3);// uimsbf
#if 0	// TODO
			if (m_config->m_sprite_enable == SpriteEnabled_GMC && m_vop_coding_type == Coded_S
				&& no_of_sprite_warping_points > 0)
			{
				sprite_trajectory()
			}
#endif

			if ((m_config->m_reduced_resolution_vop_enable)
				&& (m_config->m_video_object_layer_shape == LayerShape_rectangular)
				&& ((m_vop_coding_type == Coded_P) || (m_vop_coding_type == Coded_I)))
			{
				int vop_reduced_resolution = pBitStream->getbit();//1 bslbf
				ASSERT(0);
			}

			if (vop_coding_type != Coded_I)
				m_vop_fcode_forward = pBitStream->getnbits(3);// uimsbf
			if (vop_coding_type == Coded_B)
				m_vop_fcode_backward = pBitStream->getnbits(3);// uimsbf

			if (m_vop_fcode_forward != 1)
			{
				TRACE("");
			}
		}
	}

	if (m_config->m_newpred_enable)
	{
		ASSERT(0);
#if 0
		vop_id 4-15 uimsbf
		int vop_id_for_prediction_indication = pBitStream->getbit();//1 bslbf
		if (vop_id_for_prediction_indication)
			vop_id_for_prediction 4-15 uimsbf
		get_marker_bit(pBitStream);// 1 bslbf
#endif
	}
}

#if 0
bool checkResyncMarker(System::IO::CBitStream32* pBitStream)
{
	/*
	if(short_video_header)
		return FALSE; // added by swinder
		*/

	int nBitsPeeked;
	int iStuffedBits = m_pbitstrmIn->peekBitsTillByteAlign (nBitsPeeked);
	int nBitsResyncMarker = 17;//NUMBITS_VP_RESYNC_MARKER;
	/*
	if(m_volmd.bShapeOnly==FALSE)
	{
		if(m_vopmd.vopPredType == PVOP || (m_uiSprite == 2 && m_vopmd.vopPredType == SPRITE)) // GMC
			nBitsResyncMarker += (m_vopmd.mvInfoForward.uiFCode - 1);
		else if(m_vopmd.vopPredType == BVOP)
			nBitsResyncMarker += max(m_vopmd.mvInfoForward.uiFCode, m_vopmd.mvInfoBackward.uiFCode) - 1;
	}
	*/
		
	//assert (nBitsPeeked > 0 && nBitsPeeked <= 8);
	if (iStuffedBits == ((1 << (nBitsPeeked - 1)) - 1))
	{
		return (m_pbitstrmIn->peekBitsFromByteAlign (nBitsResyncMarker) == RESYNC_MARKER);
	}
	return FALSE;
}
#endif

void VideoObjectPlane::combined_motion_shape_texture(System::IO::CBitStream32* pBitStream)
{
	//int mb_address = 0;
	do
	{
		{
			int nextbits;

#if 0
			// Stuffing
			while(pBitStream->getnbits(9) == 1)
			{
				MessageBeep(-1);
			}
			pBitStream->ungetbits(9);
#endif

			/*
			bool b = checkResyncMarker(pBitStream);
			if (b)
			{
				break;
			}
			*/
#if 0
			nextbits = nextbits_bytealigned(pBitStream, 16+1);
			if (nextbits == 1)	// resync marker
			{
				ASSERT(!m_config->m_resync_marker_disable);
				break;
			}
#endif
/*
			nextbits = nextbits_bytealigned(pBitStream, 23);
			if (nextbits == 0)	// start-code
			{
				break;
			}
			*/
		}

		if (pBitStream->eof())
		{
			TRACE("Premature eof, mb_address: %d\n", mb_address);
			break;
		}

/*		if (m_vop_coding_type == Coded_P && mb_address == 72)
		{
			TRACE("");
		}

		if (mb_address == 176)
		{
			TRACE("");
		}
*/
		if (mb_address == 16*40+39)
		{
			TRACE("");
		}
		macroblock(pBitStream, mb_address);
		mb_address++;

//		if (mb_address == 125)
		if (m_vop_coding_type == Coded_P && mb_address == 73)
		{
		//	break;
		}

		/*
		if (mb_address == 177)
		{
			pBitStream->align();

			while (1)
			{
				int nextbits = nextbits_bytealigned(pBitStream, 32);

				pBitStream->getbyte();
			}
		}
		*/

//		break;

		if (mb_address == m_mb_cols * m_mb_rows)
		{
			break;
		}
		/*
		if (pBitStream->eof())
		{
			break;
		}
		*/

	// resync marker

#if 0
		int nextbits;

		nextbits = nextbits_bytealigned(pBitStream, 16+1);
		if (nextbits == 1)	// resync marker
		{
			MessageBeep(-1);//break;
		}
#endif

#if 0
		int nextbits = nextbits_bytealigned(pBitStream, 23);
		if (nextbits == 0)	// start-code
		{
		//	pBitStream->align();
		//	pBitStream->getnbits(23);
		//	int b = pBitStream->getbit();
		//	int code = pBitStream->getnbits(8);
		//	TRACE("start-code\n");
			break;
		}
#endif
	}
	while (1);//!pBitStream->eof());//nextbits_bytealigned() != resync_marker && nextbits_bytealigned() != ‘000 0000 0000 0000 0000 0000’);

	/*
	if (!pBitStream->eof())
	{
		while (nextbits_bytealigned(pBitStream, 8) == 0x7F)
		{
			pBitStream->byte_align();
			pBitStream->getnbits(8);
		}
	}
	*/

	TRACE("");
}

void VideoObjectPlane::motion_shape_texture(System::IO::CBitStream32* pBitStream)
{
	if (m_config->m_data_partitioned)
	{
		ASSERT(0);
	//	data_partitioned_motion_shape_texture();
	}
	else
	{
		combined_motion_shape_texture(pBitStream);
	}
}

void VideoObjectPlane::ReadVideoObjectPlane(System::IO::CBitStream32* pBitStream)
{
//	vop_start_code 32 bslbf
	m_vop_coding_type = pBitStream->getnbits(2);	//2 uimsbf

	/*
	if (m_vop_coding_type != Coded_I)	// TODO remove
	{
		return;
	}
	*/

	if (m_vop_coding_type == Coded_I)
		TRACE("I-VOP\n");
	else if (m_vop_coding_type == Coded_P)
		TRACE("P-VOP\n");
	else if (m_vop_coding_type == Coded_S)
		TRACE("S-VOP\n");
	else
		ASSERT(0);

	int modulo_time_base;
	do
	{
		modulo_time_base = pBitStream->getbit();//1 bslbf
	}
	while (modulo_time_base != 0);

	get_marker_bit(pBitStream);//  marker_bit 1 bslbf

	// range=(0,vop_time_increment_resolution)
	int vop_time_increment_length = GetNBits(m_config->m_vop_time_increment_resolution);
	uint16 vop_time_increment = pBitStream->getnbits(vop_time_increment_length);//1-16 uimsbf

	get_marker_bit(pBitStream);	//marker_bit 1 bslbf
	int vop_coded = pBitStream->getbit();	// 1 bslbf
	if (vop_coded == 0)
	{
		//next_start_code()	// ???
		return;
	}

	if (m_config->m_newpred_enable)
	{
		int vop_time_increment_length = GetNBits(m_config->m_vop_time_increment_resolution);

		int vop_id_length = MIN(vop_time_increment_length+3, 15);

		while (pBitStream->getbit() == 0);
		pBitStream->ungetbits(1);

		int vop_id = pBitStream->getnbits(vop_id_length);//4-15 uimsbf

		int vop_id_for_prediction_indication = pBitStream->getbit();//1 bslbf
		if (vop_id_for_prediction_indication)
		{
		//	while (pBitStream->getbit() == 0);
		//	pBitStream->ungetbits(1);

			int vop_id_for_prediction = pBitStream->getnbits(vop_id_length);//4-15 uimsbf
			get_marker_bit(pBitStream);// 1 bslbf
		}

	}
  
	if ((m_config->m_video_object_layer_shape != LayerShape_binary_only) &&
			  (m_vop_coding_type == Coded_P ||
			  (m_vop_coding_type == Coded_S && m_config->m_sprite_enable == SpriteEnabled_GMC)))
	{
		int vop_rounding_type = pBitStream->getbit();//1 bslbf
		//TRACE("vop_rounding_type: %d\n", vop_rounding_type);
	}
	
	if ((m_config->m_reduced_resolution_vop_enable) &&
		(m_config->m_video_object_layer_shape == LayerShape_rectangular) &&
		((m_vop_coding_type == Coded_P) || (m_vop_coding_type == Coded_I)))
	{
		m_vop_reduced_resolution = pBitStream->getbit();//1 bslbf
	}
	else
		m_vop_reduced_resolution = 0;

	ASSERT(m_vop_reduced_resolution == 0);	// Not yet supported

	if (m_config->m_video_object_layer_shape != LayerShape_rectangular)
	{
		ASSERT(0);
#if 0
		if (!(m_config->m_sprite_enable == SpriteEnabled_static && vop_coding_type == Coded_I))
		{
			int vop_width = pBitStream->getnbits(13);// uimsbf
			get_marker_bit(pBitStream);// 1 bslbf
			int vop_height = pBitStream->getnbits(13);// uimsbf
			get_marker_bit(pBitStream);// 1 bslbf
			int vop_horizontal_mc_spatial_ref = pBitStream->getnbits(13);// simsbf
			get_marker_bit(pBitStream);// 1 bslbf
			int vop_vertical_mc_spatial_ref = pBitStream->getnbits(13);// simsbf
			get_marker_bit(pBitStream);// 1 bslbf
		}

		if ((m_config->m_video_object_layer_shape != LayerShape_binary_only) && scalability && enhancement_type)
		{
			int background_composition = pBitStream->getbit();//1 bslbf
		}

		int change_conv_ratio_disable = pBitStream->getbit();//1 bslbf
		int vop_constant_alpha = pBitStream->getbit();//1 bslbf
		if (vop_constant_alpha)
		{
			int vop_constant_alpha_value = pBitStream->getnbits(8);// bslbf
		}
#endif
	}

	if (m_config->m_video_object_layer_shape != LayerShape_binary_only)
	{
		if (!m_config->m_complexity_estimation_disable)
		{
			ASSERT(0);
#if 0
			read_vop_complexity_estimation_header()
#endif
		}
	}

	if (m_config->m_video_object_layer_shape != LayerShape_binary_only)
	{
		m_intra_dc_vlc_thr = pBitStream->getnbits(3);// uimsbf
		if (m_intra_dc_vlc_thr != 0)	// Use Intra DC VLC for entire VOP
		{
		//	TRACE("intra_dc_vlc_thr: %d\n", m_intra_dc_vlc_thr);
		}

		if (m_config->m_interlaced)
		{
			int top_field_first = pBitStream->getbit();//1 bslbf
			int alternate_vertical_scan_flag = pBitStream->getbit();//1 bslbf
		}
	}
		
	if ((m_config->m_sprite_enable == SpriteEnabled_static || m_config->m_sprite_enable == SpriteEnabled_GMC) && m_vop_coding_type == Coded_S)
	{
			ASSERT(0);
#if 0
		  if (no_of_sprite_warping_points > 0)
			  sprite_trajectory()
			  if (sprite_brightness_change)
				  brightness_change_factor()
				  if(sprite_enable == “static”)
				  {
					  if (sprite_transmit_mode != “stop”
						  && low_latency_sprite_enable)
					  {
						  do
						  {
							  sprite_transmit_mode 2 uimsbf
								  if ((sprite_transmit_mode == “piece”) ||
									  (sprite_transmit_mode == “update”))
									  decode_sprite_piece()
						  }
						  while (sprite_transmit_mode != “stop” &&
						  sprite_transmit_mode != “pause”)
					  }
					  next_start_code()
						  return()
				  }
#endif
	}

	if (m_config->m_video_object_layer_shape != LayerShape_binary_only)
	{
		int vop_quant = pBitStream->getnbits(m_config->m_quant_precision);// 3-9 uimsbf
		if (vop_quant == 0)
		{
			TRACE("Error in bitstream: vop_quant cannot be 0");
			throw Error;
		}

		m_Qp[0] = vop_quant;
		//m_macroblocks->m_quantiser_scale = vop_quant;	// Initialize first macroblock?

		if (m_config->m_video_object_layer_shape == LayerShape_grayscale)
		{
			ASSERT(0);
#if 0
			for (int i = 0; i < aux_comp_count; i++)
			{
				int vop_alpha_quant[456];
				vop_alpha_quant[i] = pBitStream->getnbits(6);// uimsbf
			}
#endif
		}
	
		if (m_vop_coding_type != Coded_I)
		{
			m_vop_fcode_forward = pBitStream->getnbits(3);// uimsbf
		}

		if (m_vop_coding_type == Coded_B)
		{
			m_vop_fcode_backward = pBitStream->getnbits(3);// uimsbf
		}

		if (!m_config->m_scalability)
		{
			if (m_config->m_video_object_layer_shape != LayerShape_rectangular && m_vop_coding_type != Coded_I)
			{
				int vop_shape_coding_type = pBitStream->getbit();//1 bslbf
			}

			motion_shape_texture(pBitStream);

#if 0	// TODO Had this
			while (nextbits_bytealigned(pBitStream, 17) == 1/*resync_marker*/)
			{
			//	pBitStream->align();
			//	pBitStream->getnbits(17);

				video_packet_header(pBitStream);
				motion_shape_texture(pBitStream);
			}
#endif
		}
		else
		{
			ASSERT(0);
#if 0
				if (enhancement_type)
					  {
						  load_backward_shape 1 bslbf
						  if (load_backward_shape)
						  {
							  backward_shape_width 13 uimsbf
							  marker_bit 1 bslbf
							  backward_shape_ height 13 uimsbf
							  marker_bit 1 bslbf
							  backward_shape_horizontal_mc_spatial_ref 13 simsbf
							  marker_bit 1 bslbf
							  backward_shape_vertical_mc_spatial_ref 13 simsbf
							  backward_shape()
							  load_forward_shape 1 bslbf
							  if (load_forward_shape)
							  {
								  forward_shape_width 13 uimsbf
									  marker_bit 1 bslbf
									  forward_shape_height 13 uimsbf
									  marker_bit 1 bslbf
									  forward_shape_horizontal_mc_spatial_ref 13 simsbf
									  marker_bit 1 bslbf
									  forward_shape_vertical_mc_spatial_ref 13 simsbf
									  forward_shape()
							  }
						  }
					  }
#endif
			m_ref_select_code = pBitStream->getnbits(2);// uimsbf
			combined_motion_shape_texture(pBitStream);
		}
	}
	else
	{
		ASSERT(0);
#if 0
			combined_motion_shape_texture();
			while (nextbits_bytealigned() == resync_marker)
			{
				video_packet_header();
				combined_motion_shape_texture();
			}
#endif
	}
	//next_start_code();
}

#ifdef _DEBUG
int compare( const void *arg1, const void *arg2 )
{
   /* Compare all of both strings: */
   if (((vtab2*)arg1)->len > ((vtab2*)arg2)->len)
		return 1;
	else if (((vtab2*)arg1)->len < ((vtab2*)arg2)->len)
		return -1;
	else
		return 0;
}

int compare3( const void *arg1, const void *arg2 )
{
   /* Compare all of both strings: */
   if (((vtab2*)arg1)->mask > ((vtab2*)arg2)->mask)
		return 1;
	else if (((vtab2*)arg1)->mask < ((vtab2*)arg2)->mask)
		return -1;
	else
		ASSERT(0);
		/*if (((vtab2*)arg1)->mask > ((vtab2*)arg2)->mask)
		return 1;
	else
		return -1;
		*/
}

#endif

////////////////////////////////////////////////////
// VideoDec

VideoDec::VideoDec()
{
//	m_pTrack = NULL;

//	m_pInputPin = NULL;
//	m_pVideo = NULL;

	m_config = NULL;

//	m_threadId = 0;
//	m_hThread = NULL;

	/*
	m_pInputPin = new CInputPin;
	m_pInputPin->m_pFilter = this;
	m_pInputPin->m_id = L"Stream Input";	// ??
	AddPin(m_pInputPin);

	m_pVideo = new CVideoSequence;
	m_pVideo->m_pFilter = this;
	m_pVideo->m_id = L"Video Output";
	AddPin(m_pVideo);
*/

//	pPrevVOP = NULL;

	init_idct();	// Do this somewhere else
}

MPEG4VideoDecExt int user_data(System::IO::CBitStream32* pBitStream, int start_code)
{
	ASSERT(start_code == 0x1b2);

	while (pBitStream->looknbits(24) != 1/*'0000 0000 0000 0000 0000 0001'*/ )
	{
		pBitStream->getnbits(8);	//	user_data 8
	}

	//pBitStream->ungetbits(24);

#if 0
	while (pBitStream->getnbits(24) != 1/*'0000 0000 0000 0000 0000 0001'*/ )
	{
		pBitStream->ungetbits(24-8);	//	user_data 8
	}

	pBitStream->ungetbits(24);
#endif

	return next_start_code(pBitStream);

	/*
	user_data_start_code 32 bslbf
	while( next_bits() != ‘0000 0000 0000 0000 0000 0001’ )
	{
		user_data 8 uimsbf
	}
	*/
}

/*
name start code value
(hexadecimal)
video_object_start_code 00 through 1F
video_object_layer_start_code 20 through 2F
reserved 30 through AF
visual_object_sequence_start_code B0
visual_object_sequence_end_code B1
user_data_start_code B2
group_of_vop_start_code B3
video_session_error_code B4
visual_object_start_code B5
vop_start_code B6
reserved B7-B9
fba_object_start_code BA
fba_object_plane_start_code BB
mesh_object_start_code BC
mesh_object_plane_start_code BD
still_texture_object_start_code BE
texture_spatial_layer_start_code BF
texture_snr_layer_start_code C0
texture_tile_start_code C1
texture_shape_layer_start_code C2
stuffing_start_code C3
reserved C4-C5
System start codes (see note) C6 through FF
NOTE System start codes are defined in ISO/IEC 14496-1:1999

*/

/*
aspect_ratio_info pixel aspect ratios
0000 Forbidden
0001 1:1 (Square)
0010 12:11 (625-type for 4:3 picture)
0011 10:11 (525-type for 4:3 picture)
0110-1110 Reserved
1111 extended PAR
chroma_
*/


void video_signal_type(System::IO::CBitStream32* pBitStream)
{
	int video_signal_type = pBitStream->getbit();// 1 bslbf

	if (video_signal_type)
	{
		int video_format = pBitStream->getnbits(3);// uimsbf
		int video_range = pBitStream->getbit();// 1 bslbf
		int colour_description = pBitStream->getbit();//1 bslbf
		if (colour_description)
		{
			int colour_primaries = pBitStream->getnbits(8);// uimsbf
			int transfer_characteristics = pBitStream->getnbits(8);// uimsbf
			int matrix_coefficients = pBitStream->getnbits(8);// uimsbf
		}
	}
}

int VideoDec::VisualObject(System::IO::CBitStream32* pBitStream, int start_code)
{
	ASSERT(start_code == 0x1B5);	//visual_object_start_code 32 bslbf

	int is_visual_object_identifier = pBitStream->getbit();//1 uimsbf
	if (is_visual_object_identifier)
	{
		m_config->m_visual_object_verid = pBitStream->getnbits(4);// uimsbf
		int visual_object_priority = pBitStream->getnbits(3);// uimsbf
	}
	else
	{
		m_config->m_visual_object_verid = 1;
	}

	int visual_object_type = pBitStream->getnbits(4);// uimsbf
	if (visual_object_type == 0)
	{
		throw L"Error in bitstream: Unsupported visual object type";
		ASSERT(0);
	}

	if (visual_object_type == VisualObjectType_videoID || visual_object_type == VisualObjectType_stillTextureID)
	{
		video_signal_type(pBitStream);
	}

	start_code = next_start_code(pBitStream);
	while (start_code == 0x1B2/*user_data_start_code*/)
	{
		start_code = user_data(pBitStream, start_code);
	}

	if (visual_object_type == VisualObjectType_videoID)
	{
		if (start_code >= 0x100 && start_code <= 0x11F)	// //	video_object_start_code 32 bslbf
		{
			start_code = next_start_code(pBitStream);
			start_code = m_config->VideoObjectLayer(pBitStream, start_code);
		}
	}
	else
		ASSERT(0);

	return start_code;
#if 0
	else if (visual_object_type == “still texture ID”)
	{
		StillTextureObject()
	}
	else if (visual_object_type == “mesh ID”)
	{
		MeshObject()
	}
	else if (visual_object_type == “FBA ID”)
	{
		FBAObject()
	}
	else if (visual_object_type == “3D mesh ID”)
	{
		3D_Mesh_Object()
	}
	if (next_bits() != “0000 0000 0000 0000 0000 0001”)
	next_start_code()
#endif
}

void VideoDec::VisualObjectSequence(System::IO::CBitStream32* pBitStream, int start_code)
{
	do
	{
		//visual_object_sequence_start_code 32 bslbf
		//int start_code = next_start_code(pBitStream);	// 0x1B0
		ASSERT(start_code == 0x1B0);

		int profile_and_level_indication = pBitStream->getnbits(8);// uimsbf

		start_code = pBitStream->getnbits(32);
		while (start_code == 0x1B2/*user_data_start_code*/)
		{
			start_code = user_data(pBitStream, start_code);
		}
		//pBitStream->ungetbits(32);

		if (start_code != 0x1B5)
		{
			ASSERT(0);
			throw L"Error in bitstream: Expected VisualObject";
		}

		start_code = VisualObject(pBitStream, start_code);

		break;	// TODO remove ???
		// = pBitStream->getnbits(32);
	}
	while (start_code != 0x1B1/*visual_object_sequence_end_code*/);

	//visual_object_sequence_end_code 32 bslbf
}

void MP4VConfig::define_vop_complexity_estimation_header(System::IO::CBitStream32* pBitStream)
{
	int estimation_method = pBitStream->getnbits(2);// uimsbf

	if (estimation_method == 0 || estimation_method == 1)
	{
		int shape_complexity_estimation_disable = pBitStream->getbit();// 1
		if (!shape_complexity_estimation_disable)
		{
			int opaque = pBitStream->getbit();// 1 bslbf
			int transparent = pBitStream->getbit();// 1 bslbf
			int intra_cae = pBitStream->getbit();// 1 bslbf
			int inter_cae = pBitStream->getbit();// 1 bslbf
			int no_update = pBitStream->getbit();// 1 bslbf
			int upsampling = pBitStream->getbit();// 1 bslbf
		}
		int texture_complexity_estimation_set_1_disable = pBitStream->getbit();// 1 bslbf
		if (!texture_complexity_estimation_set_1_disable)
		{
			int intra_blocks = pBitStream->getbit();// 1 bslbf
			int inter_blocks = pBitStream->getbit();// 1 bslbf
			int inter4v_blocks = pBitStream->getbit();// 1 bslbf
			int not_coded_blocks = pBitStream->getbit();// 1 bslbf
		}
		get_marker_bit(pBitStream);// 1 bslbf
		int texture_complexity_estimation_set_2_disable = pBitStream->getbit();// 1 bslbf
		if (!texture_complexity_estimation_set_2_disable)
		{
			int dct_coefs = pBitStream->getbit();// 1 bslbf
			int dct_lines = pBitStream->getbit();// 1 bslbf
			int vlc_symbols = pBitStream->getbit();// 1 bslbf
			int vlc_bits = pBitStream->getbit();// 1 bslbf
		}
		int motion_compensation_complexity_disable = pBitStream->getbit();//1 bslbf
		if (!motion_compensation_complexity_disable)
		{
			int apm = pBitStream->getbit();// 1 bslbf
			int npm = pBitStream->getbit();// 1 bslbf
			int interpolate_mc_q = pBitStream->getbit();// 1 bslbf
			int forw_back_mc_q = pBitStream->getbit();// 1 bslbf
			int halfpel2 = pBitStream->getbit();// 1 bslbf
			int halfpel4 = pBitStream->getbit();// 1 bslbf
		}
		get_marker_bit(pBitStream);// 1 bslbf

		if (estimation_method == 1)
		{
			int version2_complexity_estimation_disable = pBitStream->getbit();//1 bslbf
			if (!version2_complexity_estimation_disable)
			{
				int sadct = pBitStream->getbit();//1 bslbf
				int quarterpel = pBitStream->getbit();//1 bslbf
			}
		}
	}
}

int MP4VConfig::VideoObjectLayer(System::IO::CBitStream32* pBitStream, int start_code)
{
	if (start_code >= 0x120 && start_code <= 0x12F/*video_object_layer_start_code*/)
	{
		m_short_video_header = 0;

		//int video_object_layer_start_code 32 bslbf
		int random_accessible_vol = pBitStream->getbit();//1 bslbf
		int video_object_type_indication = pBitStream->getnbits(8);// uimsbf
		TRACE("video_object_type_indication: %d\n", video_object_type_indication);

		int is_object_layer_identifier = pBitStream->getbit();//1 uimsbf

	//	TRACE("random_accessible_vol: %d\n", random_accessible_vol);
	//	TRACE("video_object_type_indication: %d\n", video_object_type_indication);
	//	TRACE("is_object_layer_identifier: %d\n", is_object_layer_identifier);

		int video_object_layer_verid;
		if (is_object_layer_identifier)
		{
			video_object_layer_verid = pBitStream->getnbits(4);// uimsbf
			if (video_object_layer_verid == 0)
			{
				ASSERT(0);
				throw L"Unsupported video_object_layer_verid";
			}
			int video_object_layer_priority = pBitStream->getnbits(3);// uimsbf
		}
		else
		{
			video_object_layer_verid = m_visual_object_verid;
		}
		
		int aspect_ratio_info = pBitStream->getnbits(4);// uimsbf

		if (aspect_ratio_info == 15/*“extended_PAR”*/)
		{
			int par_width = pBitStream->getnbits(8);// uimsbf
			int par_height = pBitStream->getnbits(8);// uimsbf
		}
		
		int vol_control_parameters = pBitStream->getbit();//1 bslbf
		if (vol_control_parameters)
		{
			m_chroma_format = pBitStream->getnbits(2);// uimsbf

			if (m_chroma_format != 1)
			{
				ASSERT(0);
				throw L"Only chroma format 4:2:0 supported in MPEG4";
			}

			int low_delay = pBitStream->getbit();//1 uimsbf
			int vbv_parameters = pBitStream->getbit();//1 blsbf
			if (vbv_parameters)
			{
				int first_half_bit_rate = pBitStream->getnbits(15);// uimsbf
				get_marker_bit(pBitStream);//marker_bit 1 bslbf
				int latter_half_bit_rate = pBitStream->getnbits(15);// uimsbf
				get_marker_bit(pBitStream);// 1 bslbf
				int first_half_vbv_buffer_size = pBitStream->getnbits(15);// uimsbf
				get_marker_bit(pBitStream);// 1 bslbf
				int latter_half_vbv_buffer_size = pBitStream->getnbits(3);// uimsbf
				int first_half_vbv_occupancy = pBitStream->getnbits(11);// uimsbf
				get_marker_bit(pBitStream);// 1 blsbf
				int latter_half_vbv_occupancy = pBitStream->getnbits(15);// uimsbf
				get_marker_bit(pBitStream);// 1 blsbf
			}
		}
		else
		{
			m_chroma_format = 1; // 4:2:0
		}

		m_video_object_layer_shape = pBitStream->getnbits(2);// uimsbf
	//	TRACE("m_video_object_layer_shape: %d\n", m_video_object_layer_shape);
		if (m_video_object_layer_shape == LayerShape_grayscale && video_object_layer_verid != 0x1/*‘0001’*/)
		{
			int video_object_layer_shape_extension = pBitStream->getnbits(4);// uimsbf
		}

		get_marker_bit(pBitStream);// 1 bslbf
		m_vop_time_increment_resolution = pBitStream->getnbits(16);// uimsbf
		get_marker_bit(pBitStream);// 1 bslbf
		int fixed_vop_rate = pBitStream->getbit();//1 bslbf

		if (fixed_vop_rate)
		{
			ASSERT(0);
			//fixed_vop_time_increment 1-16 uimsbf
		}

		if (m_video_object_layer_shape != LayerShape_binary_only)
		{
			if (m_video_object_layer_shape == LayerShape_rectangular)
			{
				get_marker_bit(pBitStream);// 1 bslbf
				m_video_object_layer_width = pBitStream->getnbits(13);// uimsbf
				get_marker_bit(pBitStream);// 1 bslbf
				m_video_object_layer_height = pBitStream->getnbits(13);// uimsbf
				get_marker_bit(pBitStream);// 1 bslbf
			}
			m_interlaced = pBitStream->getbit();//1 bslbf
			//ASSERT(m_interlaced == 0);

			int obmc_disable = pBitStream->getbit();//1 bslbf
		//	TRACE("obmc_disable: %d\n", obmc_disable);
			ASSERT(obmc_disable == 1);

			if (video_object_layer_verid == 0x1/*‘0001’*/)
			{
				m_sprite_enable = pBitStream->getbit();//1 bslbf
			}
			else
			{
				m_sprite_enable = pBitStream->getnbits(2);// uimsbf
				if (m_sprite_enable == SpriteEnabled_reserved)
				{
					ASSERT(0);
					throw L"Unsupported sprite_enable value";
				}
			}

			if (m_sprite_enable == SpriteEnabled_static || m_sprite_enable == SpriteEnabled_GMC)
			{
				ASSERT(0);
#if 0
				if (sprite_enable != SpriteEnabled_GMC)
				{
					sprite_width 13 uimsbf
					marker_bit 1 bslbf
					sprite_height 13 uimsbf
					marker_bit 1 bslbf
					sprite_left_coordinate 13 simsbf
					marker_bit 1 bslbf
					sprite_top_coordinate 13 simsbf
					marker_bit 1 bslbf
				}
				no_of_sprite_warping_points 6 uimsbf
				sprite_warping_accuracy 2 uimsbf
				sprite_brightness_change 1 bslbf
				if (sprite_enable != “GMC”)
					m_low_latency_sprite_enable 1 bslbf
#endif
			}

			if (video_object_layer_verid != 0x1 && m_video_object_layer_shape != LayerShape_rectangular)
			{
				m_sadct_disable = pBitStream->getbit();//1 bslbf
				ASSERT(m_sadct_disable == 1);
			}
			int not_8_bit = pBitStream->getbit();//1 bslbf

			if (not_8_bit)
			{
				m_quant_precision = pBitStream->getnbits(4);// uimsbf
				m_bits_per_pixel = pBitStream->getnbits(4);// uimsbf
			}
			else
			{
				m_quant_precision = 5;	// ???
				m_bits_per_pixel = 8;	// ???
			}

			if (m_bits_per_pixel != 8)
			{
				ASSERT(0);
				throw L"Only 8 bits per pixel is supported";
			}

			if (m_video_object_layer_shape == LayerShape_grayscale)
			{
				int no_gray_quant_update = pBitStream->getbit();//1 bslbf
				int composition_method = pBitStream->getbit();// 1 bslbf
				int linear_composition = pBitStream->getbit();// 1 bslbf
			}

			m_quant_type = pBitStream->getbit();// 1 bslbf
		//	TRACE("m_quant_type: %d\n", m_quant_type);
			if (m_quant_type == 1)	// Use first inverse quantisation method
			{
				int load_intra_quant_mat = pBitStream->getbit();//1 bslbf
				if (load_intra_quant_mat)
				{
					ASSERT(0);
				//	for (int i = 0; i < 
				//	intra_quant_mat 8*[2-64] uimsbf
				}
				else
				{
				}

				int load_nonintra_quant_mat = pBitStream->getbit();//1 bslbf
				if (load_nonintra_quant_mat)
				{
					ASSERT(0);
				//	nonintra_quant_mat 8*[2-64] uimsbf
				}
				else
				{
				}

				if (m_video_object_layer_shape == LayerShape_grayscale)
				{
					ASSERT(0);
#if 0
					for(int i = 0; i < aux_comp_count; i++)
					{
						load_intra_quant_mat_grayscale 1 bslbf
						if(load_intra_quant_mat_grayscale)
							intra_quant_mat_grayscale[i] 8*[2-64] uimsbf
						load_nonintra_quant_mat_grayscale 1 bslbf
						if(load_nonintra_quant_mat_grayscale)
							nonintra_quant_mat_grayscale[i] 8*[2-64] uimsbf
					}
#endif
				}
			}
			//else Use second inverse quantisation method

			if (video_object_layer_verid != 0x1/*‘0001’*/)
			{
				int quarter_sample = pBitStream->getbit();//1 bslbf
				// TODO
			}

			m_complexity_estimation_disable = pBitStream->getbit();//1 bslbf
			if (!m_complexity_estimation_disable)
			{
				//ASSERT(0);
				define_vop_complexity_estimation_header(pBitStream);
			}
			m_resync_marker_disable = pBitStream->getbit();//1 bslbf
			m_data_partitioned = pBitStream->getbit();//1 bslbf
			if (m_data_partitioned)
			{
				ASSERT(0);	// Not yet supported
				m_reversible_vlc = pBitStream->getbit();//1 bslbf
			}
			else
			{
				m_reversible_vlc = 0;	// ???
			}

			if (video_object_layer_verid != 0x1/*’0001’*/)
			{
				m_newpred_enable = pBitStream->getbit();//1 bslbf
				if (m_newpred_enable)
				{
					int requested_upstream_message_type = pBitStream->getnbits(2);// uimsbf
					int newpred_segment_type = pBitStream->getbit();//1 bslbf
				}
				m_reduced_resolution_vop_enable = pBitStream->getbit();//1 bslbf
			}
			else
			{
				m_newpred_enable = 0;	// ??
				m_reduced_resolution_vop_enable = 0;	// ??
			}

			m_scalability = pBitStream->getbit();//1 bslbf
			if (m_scalability)
			{
				ASSERT(0);
				TRACE("MP4Video - scalability = 1\n");

				int hierarchy_type = pBitStream->getbit();//1 bslbf
				int ref_layer_id = pBitStream->getnbits(4);// uimsbf
				int ref_layer_sampling_direc = pBitStream->getbit();//1 bslbf
				int hor_sampling_factor_n = pBitStream->getnbits(5);// uimsbf
				int hor_sampling_factor_m = pBitStream->getnbits(5);// uimsbf
				int vert_sampling_factor_n = pBitStream->getnbits(5);// uimsbf
				int vert_sampling_factor_m = pBitStream->getnbits(5);// uimsbf

				int enhancement_type = pBitStream->getbit();//1 bslbf

				if (m_video_object_layer_shape == LayerShape_binary && hierarchy_type == 0)
				{
					int use_ref_shape = pBitStream->getbit();//1 bslbf
					int use_ref_texture = pBitStream->getbit();//1 bslbf
					int shape_hor_sampling_factor_n = pBitStream->getnbits(5);// uimsbf
					int shape_hor_sampling_factor_m = pBitStream->getnbits(5);// uimsbf
					int shape_vert_sampling_factor_n = pBitStream->getnbits(5);// uimsbf
					int shape_vert_sampling_factor_m = pBitStream->getnbits(5);// uimsbf
				}
			}
		}
		else
		{
			ASSERT(0);

#if 0
			if(video_object_layer_verid !=”0001”)
			{
				scalability 1 bslbf
				if(scalability)
				{
					ref_layer_id 4 uimsbf
					shape_hor_sampling_factor_n 5 uimsbf
					shape_hor_sampling_factor_m 5 uimsbf
					shape_vert_sampling_factor_n 5 uimsbf
					shape_vert_sampling_factor_m 5 uimsbf
				}
			}
			resync_marker_disable 1 bslbf
#endif
		}

		return -1;	// TODO Remove ???

		start_code = next_start_code(pBitStream);

		while (start_code == 0x1b2/* next_bits()== user_data_start_code*/)
		{
			start_code = user_data(pBitStream, start_code);
		}

		if (m_sprite_enable == SpriteEnabled_static && !m_low_latency_sprite_enable)
		{
			ASSERT(0);
			//VideoObjectPlane(pBitStream);
		}

		return start_code;
#if 0
		do
		{
			if (start_code == 0x1b3/*next_bits() == group_of_vop_start_code*/)
			{
				ASSERT(0);
				//Group_of_VideoObjectPlane();
			}

			VideoObjectPlane();

			if ((preceding_vop_coding_type == "B" ||
				preceding_vop_coding_type == "S" ||
				video_object_layer_shape != "rectangular") &&
				next_bits() == stuffing_start_code)
			{
				stuffing_start_code 32 bslbf
					while (next_bits() != ‘0000 0000 0000 0000 0000 0001’)
						stuffing_byte 8 bslbf
			}
		}
		while ((start_code == 0x1b3/*group_of_vop_start_code*/) ||
				(start_code == 0x1b6/*vop_start_code*/));
//		while ((next_bits() == group_of_vop_start_code) ||
//				(next_bits() == vop_start_code));
#endif
	}
	else
	{
		m_short_video_header = 1;
		ASSERT(0);
#if 0
		do
		{
			video_plane_with_short_header()
		}
		while(next_bits() == short_video_start_marker);
#endif
		return start_code;
	}
}
//NOTE — preceding_vop_coding_type has the same value as vop_coding_type in the immediately preceding
//VideoObjectPlane() in the decoding order.

int VideoDec::Group_of_VideoObjectPlane(System::IO::CBitStream32* pBitStream)
{
	//group_of_vop_start_code 32 bslbf
	int time_code = pBitStream->getnbits(18);
	int closed_gov = pBitStream->getbit();//1 bslbf
	int broken_link = pBitStream->getbit();//1 bslbf

	int start_code = next_start_code(pBitStream);
	while (start_code == 0xB2)	// user_data_start_code
	{
		ASSERT(0);
		start_code = user_data(pBitStream, start_code);
	}

	return start_code;
}

ErrorCode VideoDec::Read()
{
#if 0
	System::IO::CBitStream bitstream(m_stream);
	System::IO::CBitStream32* pBitStream = &bitstream;

	try
	{
		m_start_code = next_start_code(pBitStream);
		if (m_start_code >= 0x100 && m_start_code <= 0x11F)
		{
			m_start_code = next_start_code(pBitStream);
			if (m_start_code >= 0x120 && m_start_code <= 0x12F)
			{
				m_config = new CMP4VConfig;

				// TODO
				/*m_start_code =*/ m_config->VideoObjectLayer(pBitStream, m_start_code);

				m_start_code = next_start_code(pBitStream);
			}
			else
			{
				TRACE("Expected video_object_layer_start_code");
				throw E_FAIL;
			}

			////// ready for vop or vop_group
		}
	}
	catch (ErrorCode hr)
	{
		TRACE("\n");
		return hr;
	}
#endif
	return Success;
}

#if 0
static DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
	CoInitialize(NULL);

	ErrorCode hr;

//	EnterCriticalSection(&pFilter->m_pLock);

	VideoDec* p = (VideoDec*)lpParameter;

	/*
	ULARGE_INTEGER curpos;
	LARGE_INTEGER li;
	li.QuadPart = 0;
	m_stream->Seek(li, STREAM_SEEK_CUR, &curpos);
	*/

//	CComQIPtr<ILMemInputPin> memInput = p->m_pVideo->m_connectedTo;
//	if (memInput)
	{
		ErrorCode hr = S_OK;

		if (p->m_pTrack)
		{
		//	int count = min(2, m_pTrack->m_chunks.GetSize());
			int count = p->m_pTrack->m_samples.GetSize();

			LONGLONG t = 0;

			p->pPrevVOP = NULL;

		//	for (int i = 0; i < 8; i++)
			for (int i = 0; i < 600; i++)
			{
			//	TRACE("%d - ", i);
			//	if (i == 64)
			//	Sleep(1500);//MessageBeep(-1);

				ILMediaSample* sample;
				p->m_pVideo->m_pAllocator->GetBuffer(0, &sample);

				p->m_stream->Seek(p->m_pTrack->m_samples[i].m_fileOffset, System::IO::STREAM_SEEK_SET);

			//	TRACE("{\nsamplesize: %d .. ", p->m_pTrack->m_samples[i].m_fileSize);

				LONGLONG duration = LTIME_SCALE * p->m_pTrack->m_samples[i].m_duration / p->m_pTrack->m_pMovie->m_movieHeader.m_timeScale;

				LONGLONG timeStart = t;
				LONGLONG timeEnd = t+duration;
				t += duration;

				System::IO::CBitStream bitstream(p->m_stream);
				System::IO::CBitStream32* pBitStream = &bitstream;

				//m_pBitStream = &bitstream;
				//m_sampleSize = ;

				bitstream.m_bitstreamSize = p->m_pTrack->m_samples[i].m_fileSize*8;

				try
				{
					int start_code = next_start_code(pBitStream);
			//		DWORD start_code = bitstream.getnbits(32);

					if (start_code == 0x1b6)	// vop_start_code (Video Object Plane)
					{
						CVideoObjectPlane* vop = new CVideoObjectPlane;
						vop->m_pDecoder = p;
						vop->m_config = p->m_config;
						vop->m_mb_cols = (p->m_config->m_video_object_layer_width+15)/16;
						vop->m_mb_rows = (p->m_config->m_video_object_layer_height+15)/16;
						vop->m_macroblocks = new MacroBlock[vop->m_mb_cols*vop->m_mb_rows];
						vop->m_ybuf = (uint8*)calloc(1, (vop->m_mb_rows*16)*(vop->m_mb_cols*16));
						vop->m_crbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
						vop->m_cbbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
						vop->mb_address = 0;

						if (p->pPrevVOP)
						{
							memcpy(vop->m_ybuf, p->pPrevVOP->m_ybuf, vop->m_mb_cols*vop->m_mb_rows*16*16);
							memcpy(vop->m_crbuf, p->pPrevVOP->m_crbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
							memcpy(vop->m_cbbuf, p->pPrevVOP->m_cbbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
						}

						vop->VideoObjectPlane(pBitStream);

					//	if (vop.m_vop_coding_type == Coded_I)	// TODO remove
						{
							p->m_pVideo->SetSampleRGBData(sample, vop);
						}

						if (p->pPrevVOP)
						{
							delete p->pPrevVOP;
						}
						p->pPrevVOP = vop;

						sample->SetTime(&timeStart, &timeEnd);

						hr = p->m_pVideo->m_pInputPin->Receive(sample);
					//	if (hr != S_OK)	// Stop if FAILED or S_FALSE
					//		break;
					}
					else if (start_code >= 0x100 && start_code <= 0x11F)	// //	video_object_start_code 32 bslbf
					{
					//	TRACE("video_object\n");
						start_code = next_start_code(pBitStream);
						start_code = p->m_config->VideoObjectLayer(pBitStream, start_code);

						start_code = next_start_code(pBitStream);

						while (start_code == 0x1b2/* next_bits()== user_data_start_code*/)
						{
							start_code = user_data(pBitStream, start_code);
						}

					//	TRACE("left: %d\n", ((pBitStream->m_bitstreamSize+7)/8) - ((pBitStream->m_countBits+7)/8));

						if (start_code == 0x1b6)	// vop_start_code (Video Object Plane)
						{
							CVideoObjectPlane* vop = new CVideoObjectPlane;
							vop->m_pDecoder = p;
							vop->m_config = p->m_config;
							vop->m_mb_cols = (p->m_config->m_video_object_layer_width+15)/16;
							vop->m_mb_rows = (p->m_config->m_video_object_layer_height+15)/16;
							vop->m_macroblocks = new MacroBlock[vop->m_mb_cols*vop->m_mb_rows];
							vop->m_ybuf = (uint8*)calloc(1, (vop->m_mb_rows*16)*(vop->m_mb_cols*16));
							vop->m_crbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
							vop->m_cbbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
							vop->mb_address = 0;

							if (p->pPrevVOP)
							{
								memcpy(vop->m_ybuf, p->pPrevVOP->m_ybuf, vop->m_mb_cols*vop->m_mb_rows*16*16);
								memcpy(vop->m_crbuf, p->pPrevVOP->m_crbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
								memcpy(vop->m_cbbuf, p->pPrevVOP->m_cbbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
							}

							vop->VideoObjectPlane(pBitStream);

							p->m_pVideo->SetSampleRGBData(sample, vop);

							if (p->pPrevVOP)
							{
								delete p->pPrevVOP;
							}
							p->pPrevVOP = vop;

							sample->SetTime(&timeStart, &timeEnd);

							hr = p->m_pVideo->m_pInputPin->Receive(sample);
						//	if (hr != S_OK)	// Stop if FAILED or S_FALSE
						//		break;
						}
						else
							ASSERT(0);
					}
					else
					{
						MessageBeep(-1);
					}

					if (((pBitStream->m_countBits+7)/8) < ((pBitStream->m_bitstreamSize+7)/8))
					{
						TRACE("eof not reached\n");
					}

				//	TRACE("}\n");
				}
				catch(int)
				{
					ASSERT(0);
				}
			}

			if (p->pPrevVOP)
			{
				delete p->pPrevVOP;
				p->pPrevVOP = NULL;
			}
		}
		else
		{
			ASSERT(0);
		}

	//	li.QuadPart = curpos.QuadPart;
	//	m_stream->Seek(li, STREAM_SEEK_SET, NULL);

		if (SUCCEEDED(hr))	// Don't send this if the downstream filter failed in Receive?
			p->m_pVideo->m_connectedTo->EndOfStream();
	}

	CoUninitialize();

	return 0;
}
#endif

#if 0
ErrorCode VideoDec::Run(LONGLONG tStart)
{

	m_criticalSection.Lock();

	m_state = LState_Running;
	m_tStart = tStart;

	m_criticalSection.Unlock();

	m_hThread = CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(VideoDec*)this, 0, &m_threadId);

	return S_OK;
}
#endif

#if 0
CVideoObjectPlane* VideoDec::ReadFrame(System::IO::CBitStream32* pBitStream)
{
#ifdef _DEBUG
	char* (*table) = NULL;//str_table_B8;

	if (table)
	{
		int maxlen = 6;

		int count = 0;
		while (table[count])
		{
			count++;
		}

		int len = 0;

		vtab2 vtable[10000];

		/*
		int n = 0;
		vtable[n].mask = 0;
		vtable[n].index = 0;
		vtable[n].len = len2;
		*/

		int i = 0;
		while (table[i])
		{
			int mask = 0;
			char* p = table[i];
			while (*p)
			{
				ASSERT(*p == '0' || *p == '1');

				mask <<= 1;
				if (*p == '1') mask |= 1;
				p++;
			}

			int len2 = p - table[i];
			ASSERT(len2 <= maxlen);

			vtable[i].mask = mask << (maxlen-len2);
			vtable[i].index = i;
			vtable[i].len = len2;

			i++;
		}

		qsort(vtable, count, sizeof(vtab2), compare3);

		//vtable[i].len = 12;
		vtable[i].mask = 1<<maxlen;

		FILE* fp = fopen("C:\\mpeg_tab.cpp", "wb");
		{
			int code = 0;

			while (code < vtable[0].mask)
			{
				fprintf(fp, "%d, %d,\n", vtable[0].len, vtable[0].index);
				code++;
			}

			for (int i = 0; i < count; i++)
			{
				ASSERT(code == vtable[i].mask);

				while (code < vtable[i+1].mask)
				{
					fprintf(fp, "%d, %d,\n", vtable[i].len, vtable[i].index);
					code++;
				}
			}
			//ASSERT(code == 4096);

			/*
			for (int i = 0; i < count; i++)
			{
			}
			*/
		}

		fclose(fp);

		return 0;
	}
#endif

#if 0
	printf("ReadFrame\n");

	CVideoObjectPlane* vop = new CVideoObjectPlane;
	//vop->m_pDecoder = this;
	vop->m_config = m_config;
	vop->m_mb_cols = (m_config->m_video_object_layer_width+15)/16;
	vop->m_mb_rows = (m_config->m_video_object_layer_height+15)/16;
	vop->m_macroblocks = new MacroBlock[vop->m_mb_cols*vop->m_mb_rows];
	vop->m_ybuf = (uint8*)calloc(1, (vop->m_mb_rows*16)*(vop->m_mb_cols*16));
	vop->m_crbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
	vop->m_cbbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
	vop->mb_address = 0;

	if (vop->pPrevVOP)
	{
		memcpy(vop->m_ybuf, vop->pPrevVOP->m_ybuf, vop->m_mb_cols*vop->m_mb_rows*16*16);
	}

	vop->VideoObjectPlane(pBitStream);

	return vop;
#endif
	return NULL;
}
#endif

}	// Mpeg4
}	// System
