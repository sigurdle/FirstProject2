#include "StdAfx.h"
#include <stdio.h>
#include "LMPEGAudio.h"
#include "LMPEGAudioDecoder.h"

#include "AudioSequence.h"

#include "MPEG4VideoDec/vlctables.h"

int bitrate_layer_II[16] =
{
	0,	// free
	32,
	48,
	56,
	64,
	80,
	96,
	112,
	128,
	160,
	192,
	224,
	256,
	320,
	384,
	-1	// forbidden
};

int sampling_freq_tab[4] =
{
	44100,
	48000,
	32000,
	0,	// reserved
};

int B2a_nbal[30] =
{
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
};

int B2_nbal[8] =
{
	4,
	4,
	3,
	3,
	3,
	3,
	3,
	3,
};

int B2_levels[8][16] =
{
	{0, 3, 5, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767},
	{0, 3, 5, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767},
	{0, 3, 5, 9, 15, 31, 63, 127},
	{0, 3, 5, 9, 15, 31, 63, 127},
	{0, 3, 5, 9, 15, 31, 63, 127},
	{0, 3, 5, 9, 15, 31, 63, 127},
	{0, 3, 5, 9, 15, 31, 63, 127},
	{0, 3, 5, 9, 15, 31, 63, 127},
};

int B2a_levels[30][16] =
{
	{0, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535},
	{0, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535},
	{0, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 65535},
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 7, 9, 15, 31, 65535 },
	{0, 3, 5, 65535 },
	{0, 3, 5, 65535 },
	{0, 3, 5, 65535 },
	{0, 3, 5, 65535 },
	{0, 3, 5, 65535 },
	{0, 3, 5, 65535 },
	{0, 3, 5, 65535 },
};

bool grouping_tab[18] =
{
	(bool)-1,
	true,
	true,
	false,
	true,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
};

int bits_per_codeword_tab[18] =
{
-1,
5,
7,
3,
10,
4,
5,
6,
7,
8,
9,
10,
11,
12,
13,
14,
15,
16
};

static double c_tab[17] = { 1.33333333333, 1.60000000000, 1.14285714286,
                        1.77777777777, 1.06666666666, 1.03225806452,
                        1.01587301587, 1.00787401575, 1.00392156863,
                        1.00195694716, 1.00097751711, 1.00048851979,
                        1.00024420024, 1.00012208522, 1.00006103888,
                        1.00003051851, 1.00001525902 };

static double d_tab[17] = { 0.500000000, 0.500000000, 0.250000000, 0.500000000,
                        0.125000000, 0.062500000, 0.031250000, 0.015625000,
                        0.007812500, 0.003906250, 0.001953125, 0.0009765625,
                        0.00048828125, 0.00024414063, 0.00012207031,
                        0.00006103516, 0.00003051758 };

static double D_tab[512];

double multiple[64] = {
2.00000000000000, 1.58740105196820, 1.25992104989487,
1.00000000000000, 0.79370052598410, 0.62996052494744, 0.50000000000000,
0.39685026299205, 0.31498026247372, 0.25000000000000, 0.19842513149602,
0.15749013123686, 0.12500000000000, 0.09921256574801, 0.07874506561843,
0.06250000000000, 0.04960628287401, 0.03937253280921, 0.03125000000000,
0.02480314143700, 0.01968626640461, 0.01562500000000, 0.01240157071850,
0.00984313320230, 0.00781250000000, 0.00620078535925, 0.00492156660115,
0.00390625000000, 0.00310039267963, 0.00246078330058, 0.00195312500000,
0.00155019633981, 0.00123039165029, 0.00097656250000, 0.00077509816991,
0.00061519582514, 0.00048828125000, 0.00038754908495, 0.00030759791257,
0.00024414062500, 0.00019377454248, 0.00015379895629, 0.00012207031250,
0.00009688727124, 0.00007689947814, 0.00006103515625, 0.00004844363562,
0.00003844973907, 0.00003051757813, 0.00002422181781, 0.00001922486954,
0.00001525878906, 0.00001211090890, 0.00000961243477, 0.00000762939453,
0.00000605545445, 0.00000480621738, 0.00000381469727, 0.00000302772723,
0.00000240310869, 0.00000190734863, 0.00000151386361, 0.00000120155435,
1E-20
};

namespace System
{
namespace MediaShow
{

void MPEGAudioSequence::header()
{
	uint16 syncword = m_file->getnbits(12);
	ASSERT(syncword == 0xFFF);
	int ID = m_file->getbit();

	m_layer = 4 - m_file->getnbits(2);
	if (m_layer == 0) THROW(-1);

	m_protection_bit = m_file->getbit();
	m_bitrate_index = m_file->getnbits(4);
	m_sampling_frequency = m_file->getnbits(2);
	m_padding_bit = m_file->getbit();
	int private_bit = m_file->getbit();
	m_mode = m_file->getnbits(2);
	int m_mode_extension = m_file->getnbits(2);
	int copyright = m_file->getbit();
	int original = m_file->getbit();
	int emphasis = m_file->getnbits(2);

	if (m_mode == 3)
		m_nchannels = 1;
	else
		m_nchannels = 2;	// TODO ???

	if (m_layer == 1)
		ASSERT(0);
	else if (m_layer == 2)
		m_N = 144 * bitrate_layer_II[m_bitrate_index]*1000 / sampling_freq_tab[m_sampling_frequency];
	else
		;//ASSERT(0);

	if (m_padding_bit)
		m_N++;
}

void MPEGAudioSequence::error_check()
{
	if (m_protection_bit == 0)
	{
		//crc_check();
		m_file->getnbits(16);
	}
}

//void CAudioSequence::dequant_sample(int sample[2][3])

double V[2][1024];

double MatrixCos[64][32];

void synthesize_layerII(double sample[32], short outsample[32], int ch)
{
	// shift
	{
		for (int i = 1023; i >= 64; i--)
		{
			V[ch][i] = V[ch][i-64];
		}
	}

	// matrixing
	{
		for (int i = 0; i < 64; i++)
		{
			V[ch][i] = 0;
			for (int k = 0; k < 32; k++)
			{
			//	V[ch][i] += cos((16+i)*(2*k+1) * M_PI/64) * sample[k];
				V[ch][i] += MatrixCos[i][k] * sample[k];
			}
		}
	}

	// Build a 512 values vector U
	double U[512];
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				int i64j = i*64+j;
				int i128j = i*128+j;

				U[i64j] = V[ch][i128j];
				U[i64j+32] = V[ch][i128j+96];
			}
		}
	}

	// Window by 512 coefficients
	double W[512];
	{
		for (int i = 0; i < 512; i++)
		{
			W[i] = U[i] * D_tab[i];
		}
	}

	// Calculate 32 samples
	{
		for (int j = 0; j < 32; j++)
		{
			double sum = 0;

			for (int i = 0; i < 16; i++)
			{
				sum += W[j+32*i];
			}

			long isum = sum * 32768;

			/*
			if (isum != 0)
			{
				TRACE("");
			}
			*/

			if (isum < -32768)
				outsample[j] = -32768;
			else if (isum > 32767)
				outsample[j] = 32767;
			else
				outsample[j] = isum;
		}
	}
}

void MPEGAudioSequence::audio_data_layerII(short* outsamp)
{
//	memset(V, 0, sizeof(V));
	// Determine sblimit
	int sblimit;

	int freq = sampling_freq_tab[m_sampling_frequency];
	int bitrate_per_channel = bitrate_layer_II[m_bitrate_index];	// TODO

	int (*nbal);
	int (*levels)[16];
	
//	if (m_mode != 3)	// single_channel
//		bitrate_per_channel /= 2;
	bitrate_per_channel /= m_nchannels;

	if (freq == 44100 && (bitrate_per_channel == 96 || bitrate_per_channel == 112 || bitrate_per_channel == 128 || bitrate_per_channel == 160 || bitrate_per_channel == 192 || bitrate_per_channel == 0))
	{
		sblimit = 30;
		nbal = B2a_nbal;
		levels = B2a_levels;
	}
	else if (freq == 44100 && (bitrate_per_channel == 32 || bitrate_per_channel == 48))
	{
		sblimit = 8;
		nbal = B2_nbal;
		levels = B2_levels;
	}
	else if (freq == 32000)
	{
		sblimit = 8;
		nbal = B2_nbal;
		levels = B2_levels;
	}
	else
	{
		// TODO
		ASSERT(0);
		THROW(-1);
	}

	int nsample = 0;

	// Determine bound
	int bound;
	if (m_layer == 1)
	{
		if (m_mode == 1)	// joint_stereo
		{
			ASSERT(0);
		}
		else
			bound = 32;
	}
	else if (m_layer == 2)
	{
		if (m_mode == 1)	// joint_stereo
		{
			ASSERT(0);
		}
		else
		{
			bound = sblimit;
		}
	}
	else
		ASSERT(0);

	//int nch = m_nchannels;

	int allocation[2][32];

	int sb;

	for (sb = 0; sb < bound; sb++)
	{
		for (int ch = 0; ch < m_nchannels; ch++)
		{
			unsigned int bits = m_file->getnbits(nbal[sb]);
			allocation[ch][sb] = levels[sb][bits];
		}
	}

	for (sb = bound; sb < sblimit; sb++)
	{
		unsigned int bits = m_file->getnbits(nbal[sb]);

		allocation[0][sb] = levels[sb][bits];
		allocation[1][sb] = allocation[0][sb];
	}

	int scfsi[2][32];

	for (sb = 0; sb < sblimit; sb++)
	{
		for (int ch = 0; ch < m_nchannels; ch++)
		{
			if (allocation[ch][sb] != 0)
			{
				scfsi[ch][sb] = m_file->getnbits(2);
			}
		}
	}

	int scalefactor[2][32][3];

	for (sb = 0; sb < sblimit; sb++)
	{
		for (int ch = 0; ch < m_nchannels; ch++)
		{
			if (allocation[ch][sb] != 0)
			{
				if (scfsi[ch][sb] == 0)
				{
					scalefactor[ch][sb][0] = m_file->getnbits(6);
					scalefactor[ch][sb][1] = m_file->getnbits(6);
					scalefactor[ch][sb][2] = m_file->getnbits(6);
				}
				else if (scfsi[ch][sb] == 1)
				{
					scalefactor[ch][sb][0] = m_file->getnbits(6);
					scalefactor[ch][sb][1] = scalefactor[ch][sb][0];
					scalefactor[ch][sb][2] = m_file->getnbits(6);
				}
				else if (scfsi[ch][sb] == 3)
				{
					scalefactor[ch][sb][0] = m_file->getnbits(6);
					scalefactor[ch][sb][1] = m_file->getnbits(6);
					scalefactor[ch][sb][2] = scalefactor[ch][sb][1];
				}
				else if (scfsi[ch][sb] == 2)
				{
					scalefactor[ch][sb][0] = m_file->getnbits(6);
					scalefactor[ch][sb][1] = scalefactor[ch][sb][0];
					scalefactor[ch][sb][2] = scalefactor[ch][sb][0];
				}
			}
		}
	}

	bool grouping[2][32];
	int bits_per_codeword[2][32];
	int alloc_index[2][32];

	{
		for (int ch = 0; ch < m_nchannels; ch++)
		{
			for (int sb = 0; sb < sblimit; sb++)
			{
				int allocindex;
				switch (allocation[ch][sb])
				{
				case 0:allocindex = 0; break;
				case 3: allocindex = 1; break;
				case 5: allocindex = 2; break;
				case 7: allocindex = 3; break;
				case 9: allocindex = 4; break;
				case 15: allocindex = 5; break;
				case 31: allocindex = 6; break;
				case 63: allocindex = 7; break;
				case 127: allocindex = 8; break;
				case 255: allocindex = 9; break;
				case 511: allocindex = 10; break;
				case 1023: allocindex = 11; break;
				case 2047: allocindex = 12; break;
				case 4095: allocindex = 13; break;
				case 8191: allocindex = 14; break;
				case 16383: allocindex = 15; break;
				case 32767: allocindex = 16; break;
				case 65535: allocindex = 17; break;
				default:
					ASSERT(0);
				}

				grouping[ch][sb] = grouping_tab[allocindex];
				bits_per_codeword[ch][sb] = bits_per_codeword_tab[allocindex];
				alloc_index[ch][sb] = allocindex;//bits_per_codeword_tab[allocindex];
			}
		}
	}

//	int samplecode[2][32][12];
//	int sample[2][32][36];

	for (int gr = 0; gr < 12; gr++)
	{
		//int sample[2][3][32];
		double fraction_samples[2][3][32] = {0};
		{
			for (int sb = 0; sb < bound; sb++)
			{
				for (int ch = 0; ch < m_nchannels; ch++)
				{
					if (allocation[ch][sb] != 0)
					{
						int sample[3];

						if (grouping[ch][sb])
						{
							//samplecode[ch][sb][gr]
							ASSERT(bits_per_codeword[ch][sb]>= 5 && bits_per_codeword[ch][sb] <= 10);
							unsigned int c = m_file->getnbits(bits_per_codeword[ch][sb]);	// 5..10
						//	nsample += 3;

							int nlevels = allocation[ch][sb];

							// degroup the combined sample code into three samples
							for (int s = 0; s < 3; s++)
							{
								sample[s] = c % nlevels;
								c = c / nlevels;
							}
						}
						else
						{
							for (int s = 0; s < 3; s++)
							{
								ASSERT(bits_per_codeword[ch][sb]>= 3 && bits_per_codeword[ch][sb] <= 16);
								sample[s] = m_file->getnbits(bits_per_codeword[ch][sb]);	// 3..16

								nsample++;
							}
						}

						for (int s = 0; s < 3; s++)
						{
							int nlevels = allocation[ch][sb];

							double fraction;

							// This code stolen, I wish I could understand it
							{
								/* locate MSB in the sample */
								int x = 0;
								while ((1L<<x) < nlevels) x++;//(*alloc)[i][bit_alloc[k][i]].steps) x++;

								/* MSB inversion */
								if (((sample[s] >> x-1) & 1) == 1)
									 fraction = 0.0;
								else  fraction = -1.0;

								/* Form a 2's complement sample */
								fraction += (double) (sample[s] & ((1<<x-1)-1)) /
									 (double) (1L<<x-1);
							}

						//	TRACE("%d,", alloc_index[ch][sb]-1);

							// Dequantize
							fraction += d_tab[alloc_index[ch][sb]-1];
							fraction *= c_tab[alloc_index[ch][sb]-1];

							fraction *= multiple[scalefactor[ch][sb][gr>>2]];

/*
							// Invert MSB
							if (sample[ch][sb][3*gr+s] & (1<<n))
								sample[ch][sb][3*gr+s] &= ~(1<<n);
							else
								sample[ch][sb][3*gr+s] &= (1<<n);
								*/

							fraction_samples[ch][s][sb] = fraction;
						}
					}
				}
			}
		}

		{
			for (int sb = bound; sb < sblimit; sb++)
			{
				ASSERT(0);

#if 0
				if (allocation[0][sb] != 0)
				{
					if (grouping[0][sb])
					{
						samplecode[0][sb][gr] = m_file->getnbits(bits_per_codeword[0][sb]);	// 5..10
						nsample += 3;
					}
					else
					{
						for (int s = 0; s < 3; s++)
						{
							sample[0][sb][3*gr+s] = m_file->getnbits(bits_per_codeword[0][sb]);	// 3.16
							nsample++;
						}
					}
				}
#endif
			}
		}

		short pcm_samples[2][3][32];
		{
			for (int s = 0; s < 3; s++)
			{
				for (int ch = 0; ch < m_nchannels; ch++)
				{
					synthesize_layerII(fraction_samples[ch][s], pcm_samples[ch][s], ch);
				}
				//synthesize(fraction_samples[1][s], pcm_samples[1][s], 1);
			}

		}

		{
			for (int s = 0; s < 3; s++)
			{
				for (int sb = 0; sb < 32; sb++)
				{
					for (int ch = 0; ch < m_nchannels; ch++)
					{
						*outsamp++ = pcm_samples[ch][s][sb];
					}
				}
			}
		}
	}
}

void MPEGAudioSequence::audio_data_layerIII(short* outsamp)
{
	int main_data_begin = m_file->getnbits(9);

	m_file->m_countBits = 0;

	if (m_mode == 3/*single_channel*/)
	{
		int private_bits = m_file->getnbits(5);
	}
	else
	{
		int private_bits = m_file->getnbits(3);
	}

	SideInfo_layerIII si;

	for (int ch = 0; ch < m_nchannels; ch++)
	{
		for (int scfsi_band = 0; scfsi_band < 4; scfsi_band++)
		{
			si.scfsi[ch][scfsi_band] = m_file->getbit();
		}
	}

	for (int gr = 0; gr < 2; gr++)
	{
		for (int ch = 0; ch < m_nchannels; ch++)
		{
			si.part2_3_length[gr][ch] = m_file->getnbits(12);
			si.big_values[gr][ch] = m_file->getnbits(9);
			si.global_gain[gr][ch] = m_file->getnbits(8);
			si.scalefac_compress[gr][ch] = m_file->getnbits(4);
			si.window_switching_flag[gr][ch] = m_file->getbit();

			if (si.window_switching_flag[gr][ch])
			{
				si.block_type[gr][ch] = m_file->getnbits(2);
				si.mixed_block_flag[gr][ch] = m_file->getbit();

				for (int region = 0; region < 2; region++)
				{
					si.table_select[gr][ch][region] = m_file->getnbits(5);
				}
			
				for (int window = 0; window < 3; window++)
				{
					si.subblock_gain[gr][ch][window] = m_file->getnbits(3);
				}
			}
			else
			{
				for (int region = 0; region < 3; region++)
				{
					si.table_select[gr][ch][region] = m_file->getnbits(5);
				}
				si.regionO_count[gr][ch] = m_file->getnbits(4);
				si.region1_count[gr][ch] = m_file->getnbits(3);
			}

			si.preflag[gr][ch] = m_file->getbit();
			si.scalefac_scale[gr][ch] = m_file->getbit();
			si.countltable_select[gr][ch] = m_file->getbit();
		}
	}

	main_data_layerIII(si);
}

static uint8 slen1[16] =
{
	0,
	0,
	0,
	0,
	3,
	1,
	1,
	1,
	2,
	2,
	2,
	3,
	3,
	3,
	4,
	4,
};

static uint8 slen2[16] =
{
	0,
	1,
	2,
	3,
	0,
	1,
	2,
	3,
	1,
	2,
	3,
	1,
	2,
	3,
	2,
	3,
};

char* str_codetable_6[] =
{
"111",
"O11",
"O0101",
"0000001",
"110",
"10",
"0011",
"00010",
"0101",
"0100",
"00100",
"O00001",
"O00011",
"O0011",
"O00010",
"0000000",
};

struct xylen
{
	int x, y, len;
};

extern vtab_byte codetable6_codes[128];

xylen codetable6_xyz[] =
{
0,0,3,
0,1,3,
0,2,5,
0,3,7,
1,0,3,
1,1,2,
1,2,4,
1,3,5,
2,0,4,
2,1,4,
2,2,5,
2,3,6,
3,0,6,
3,1,5,
3,2,6,
3,3,7,
};

char* str_codetable10[] =
{
"1",
"010",
"001010",
"00010111",
"000100011",
"000011110",
"000001100",
"0000010001",
"011",
"0011",
"001000",
"0001100",
"00010010",
"000010101",
"00001100",
"00000111",
"001011",
"001001",
"0001111",
"00010101",
"000100000",
"0000101000",
"000010011",
"000000110",
"0001110",
"0001101",
"00010110",
"000100010",
"0000101110",
"0000010111",
"000010010",
"0000000111",
"00010100",
"00010011",
"000100001",
"0000101111",
"0000011011",
"0000010110",
"0000001001",
"0000000011",
"000011111",
"000010110",
"0000101001",
"0000011010",
"00000010101",
"00000010100",
"0000000101",
"00000000011",
"00001110",
"00001101",
"000001010",
"0000001011",
"0000010000",
"0000000110",
"00000000101",
"00000000001",
"000001001",
"00001000",
"000000111",
"0000001000",
"0000000100",
"00000000100",
"00000000010",
"00000000000",
};

/*
char* str_codetable24[] =
{
"1111",
"1101"
101110
1010000
10010010
100000110
011111000
0110110010
0110101010
01010011101
01010001101
01010001001
01001101101
01000000101
010000001000
001011000
1110
1100
10101
100110
1000111
10000010
01111010
011011000
011010001
011000110
};
*/

#ifdef _DEBUG

struct vtab2
{
	int len;
	uint32 mask;
	int index;
};

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

void MPEGAudioSequence::main_data_layerIII(const SideInfo_layerIII& si)
{
#if 0//_DEBUG
	char* (*table) = str_codetable24;

	if (table)
	{
		int maxlen = 11;

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
				// note, zero and big o

				ASSERT(*p == 'O' || *p == '0' || *p == '1' || *p == 'l');

				mask <<= 1;
				if (*p == '1' || *p == 'l') mask |= 1;
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

		return;
	}
#endif

	uint8 scalefac_l[2][2][12];
	uint8 scalefac_s[2][2][12][3];

	for (int gr = 0; gr < 2; gr++)
	{
		for (int ch = 0; ch < m_nchannels; ch++)
		{
			if (si.window_switching_flag[gr][ch] == 1 && si.block_type[gr][ch] == 2)
			{
				if (si.mixed_block_flag[gr][ch] == 1)
				{
					int sfb;

					for (sfb = 0; sfb < 8; sfb++)
					{
						scalefac_l[gr][ch][sfb] = m_file->getnbits(slen1[si.scalefac_compress[gr][ch]]);
					}

					for (sfb = 3; sfb < 12; sfb++)
					{
						for (int window = 0; window < 3; window++)
						{
							scalefac_s[gr][ch][sfb][window] = m_file->getnbits(slen1[si.scalefac_compress[gr][ch]]);
						}
					}
				}
				else
				{
					ASSERT(0);
				}
			}
			else
			{
				if (si.scfsi[ch][0] == 0 || gr == 0)
				{
					for (int sfb = 0; sfb < 6; sfb++)
					{
						scalefac_l[gr][ch][sfb] = m_file->getnbits(slen1[si.scalefac_compress[gr][ch]]);
					}
				}

				if (si.scfsi[ch][1] == 0 || gr == 0)
				{
					for (int sfb = 6; sfb < 11; sfb++)
					{
						scalefac_l[gr][ch][sfb] = m_file->getnbits(slen2[si.scalefac_compress[gr][ch]]);
					}
				}

				if (si.scfsi[ch][2] == 0 || gr == 0)
				{
					for (int sfb = 11; sfb < 16; sfb++)
					{
						scalefac_l[gr][ch][sfb] = m_file->getnbits(slen1[si.scalefac_compress[gr][ch]]);
					}
				}

				if (si.scfsi[ch][3] == 0 || gr == 0)
				{
					for (int sfb = 16; sfb < 21; sfb++)
					{
						scalefac_l[gr][ch][sfb] = m_file->getnbits(slen1[si.scalefac_compress[gr][ch]]);
					}
				}

				ASSERT(0);
			}

			HuffmanCodebits(si, gr, ch);
		}
	}
}

void MPEGAudioSequence::HuffmanCodebits(const SideInfo_layerIII& si, int gr, int ch)
{
	for (int l = 0; l < si.big_values[gr][ch]*2; l += 2)
	{
	}
}

void MPEGAudioSequence::frame(short* pcmsamples)
{
	m_file->byte_align();
	header();
	if (m_layer == 1)
	{
		ASSERT(0);
		THROW(-1);
#if 0
		mpeg1_error_check()
		mpeg1_audio_data()
		mc_extension_part1()
		mpeg1_header()
		mpeg1_error_check()
		mpeg1_audio_data()
		mc_extension_part2()
		mpeg1_header()
		mpeg1_error_check()
		mpeg1_audio_data()
		mc_extension_part3()
		mpeg1_ancillary_data()
#endif
	}
	else	// layer II and III
	{
		error_check();

		if (m_layer == 2)
			audio_data_layerII(pcmsamples);
		else
			audio_data_layerIII(pcmsamples);

//		m_file->skipnbits(8*5);
#if 0
		mc_extension()
		mpeg1_ancillary_data()
#endif
	}
}

ErrorCode AudioSequence::audio_sequence()
{
#if 0
	for (int i = 0; i < 20; i++)
	{
		frame();
		m_file->byte_align();

		while (1)
		{
			if (m_file->looknbits(12) == 0xFFF)
				break;
			m_file->skipnbits(8);
		}
	}
#endif
	return 0;
}

// IMediaSeeking
ErrorCode AudioSequence::Seek(TimeUnit unit, LONGLONG t)
{
	return Success;
}

ErrorCode AudioSequence::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
	*pVal = -1;
#if 0
	LONGLONG nSamples = GetSamples();

	LPWAVEFORMATEX pwfx = (LPWAVEFORMATEX)m_mt.pbFormat;

	*pVal = LTIME_SCALE * nSamples / pwfx->nSamplesPerSec;
#endif

	return Success;
}

ErrorCode AudioSequence::GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
{
	ASSERT(0);
	return Success;
}

#if 0
LONGLONG AudioSequence::GetSamples()
{
	return m_frames.GetCount()*1152;
}
#endif

ErrorCode AudioSequence::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
		//memcpy(&((LVIDEOINFOHEADER2*)mediaType->pbFormat)->bmiHeader, m_pBitmapInfoHeader, sizeof(BITMAPINFOHEADER)+m_pBitmapInfoHeader->biClrUsed*sizeof(RGBQUAD));


		WaveFormat* pwfx = new WaveFormat;

	//	frame_params* frame = (frame_params*)m_frames.GetHead();

		//int nChannels = 2;//frame->stereo;

		pwfx->wf->wFormatTag = WAVE_FORMAT_PCM;
		pwfx->wf->nChannels = m_mpeg_audio->m_nchannels;
		pwfx->wf->wBitsPerSample = 16;
		pwfx->wf->nBlockAlign = m_mpeg_audio->m_nchannels * (16 / 8);
		pwfx->wf->nSamplesPerSec = sampling_freq_tab[m_mpeg_audio->m_sampling_frequency];
		pwfx->wf->nAvgBytesPerSec = pwfx->wf->nSamplesPerSec*pwfx->wf->nBlockAlign;
		pwfx->wf->cbSize = 0;

		MediaType* mediaType = new MediaType(LMEDIATYPE_Audio, GUID_NULL, GUID_NULL, pwfx);
	//	mediaType.SetMajorType(LMEDIATYPE_Audio);
	//	mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
	//	mediaType.SetFormat(pwfx);

		*pMediaType = mediaType;

		return Success_True;
	}
	else
	{
	//	pMediaType = NULL;
		return Success_False;
	}
}

#if 0
STDMETHODIMP CAudioSequence::GetFormat(WAVEFORMATEX *pVal)
{
	/*
       pcm_aiff_data.numChannels       = stereo;
       pcm_aiff_data.numSampleFrames   = sample_frames;
       pcm_aiff_data.sampleSize        = 16;
       pcm_aiff_data.sampleRate        = s_freq[info.sampling_frequency]*1000;
*/
	frame_params* frame = (frame_params*)m_frames.GetHead();

	int m_nChannels = frame->stereo;

	pVal->wFormatTag = WAVE_FORMAT_PCM;
	pVal->nChannels = m_nChannels;
	pVal->wBitsPerSample = 16;
	pVal->nBlockAlign = m_nChannels * 16 / 8;
	pVal->nSamplesPerSec = s_freq[frame->m_sampling_frequency_index]*1000;
	pVal->cbSize = 0;

	return S_OK;
}
#endif

#if 0
STDMETHODIMP CAudioSequence::GetChunkSize(long nchunk, ULONG* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 0;

	if (nchunk < m_frames.GetCount())
	{
		*pVal = 1152;	// number of samples for one frame in layer2

		return S_OK;
	}
	else
		return S_FALSE;
}
#endif

#if 0
ErrorCode CAudioSequence::ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples)
{
	ASSERT(0);
#if 0
	if (nchunk < m_frames.GetCount())
	{
		frame_params* frame = (frame_params*)m_frames.GetAt(m_frames.FindIndex(nchunk));

		LARGE_INTEGER li;
		li.QuadPart = frame->m_fileDataBytePos;
		m_file->m_byteStream->Seek(li, STREAM_SEEK_SET, NULL);
		m_file->m_bitcnt = frame->m_fileDataBitCnt;

		try
		{
			if (frame->header->m_layer == 1) audio_data_layer1();
			else if (frame->header->m_layer == 2) audio_data_layer2(frame, (LPWORD)buffer);
			else if (frame->header->m_layer == 3) audio_data_layer3(*frame);
		}
		catch(int code)
		{
			return S_FALSE;
		}

		return S_OK;
	}
	else
#endif
		return E_FAIL;
}
#endif

void MPEGAudioSequence::Open(System::IO::ISequentialByteStream* stream)
{
	m_file = new System::IO::CBitStream32(new System::IO::CByteStream(stream));
}

void MPEGAudioSequence::seek_sync()
{
	m_file->byte_align();
	while (1)
	{
		if (m_file->looknbits(12) == 0xFFF)
			break;
		m_file->skipnbits(8);
	}
}

#if AMIGA
#define WINAPI
#endif

static MSWindows::DWORD WINAPI AudioRunProc(void* lpParameter)
{
	AudioSequence* p = (AudioSequence*)(IPin*)lpParameter;

	TRY
	{
		LONGLONG timeStart = 0;
		while (1)
		{
			p->m_mpeg_audio->seek_sync();

			int nBlockAlign = p->m_mpeg_audio->m_nchannels*2;

			IMediaSample* sample;
			p->m_pAllocator->GetBuffer(nBlockAlign * 1152, &sample);
		//	if (FAILED(hr))
		//		break;

			LONGLONG timeEnd = timeStart + TIME_SCALE * 1152 / sampling_freq_tab[p->m_mpeg_audio->m_sampling_frequency];

			sample->SetTime(&timeStart, &timeEnd);

			timeStart = timeEnd;

			LSampleData sampledata;
			if (sample->LockBits(&sampledata) >= 0)
			{
				p->m_mpeg_audio->frame((short*)sampledata.idata);
			//	p->ReadChunk(i, (LPSTR)sampledata.idata, 1152);

				sample->UnlockBits();

				/*
				LONGLONG sampleDuration = LTIME_SCALE * p->m_pAVIStream->m_aviStreamHeader.dwScale / p->m_pAVIStream->m_aviStreamHeader.dwRate;

				LONGLONG timeStart = sampleDuration*i;//p->m_currentFrame;
				LONGLONG timeEnd = timeStart+sampleDuration;

				sample->SetTime(&timeStart, &timeEnd);
				*/

			/*	hr =*/ p->m_pInputPin->Receive(sample);
			//	if (FAILED(hr))
			//		break;

				sample->Release();
			}

	//		p->frame();

			p->m_mpeg_audio->m_file->byte_align();

			/*
			while (1)
			{
				if (p->m_mpeg_audio->m_file->looknbits(12) == 0xFFF)
					break;
				p->m_mpeg_audio->m_file->skipnbits(8);
			}
			*/
		}
	}
	CATCH(int)
	{
	}

	p->ConnectedTo()->EndOfStream();

#if 0
	ErrorCode hr = S_OK;

	for (int i = 0; i < p->m_frames.GetCount(); i++)
	{
		UPOSITION pos = p->m_frames.FindIndex(i);
		frame_params* frame = (frame_params*)p->m_frames.GetAt(pos);

		int nBlockAlign = frame->stereo*16/8;


		CComPtr<ILMediaSample> sample;
		p->m_pAllocator->GetBuffer(nBlockAlign * 1152, &sample);
		if (FAILED(hr))
			break;

		LSampleData sampledata;
		if (SUCCEEDED(sample->LockBits(&sampledata)))
		{
			p->ReadChunk(i, (LPSTR)sampledata.idata, 1152);

			sample->UnlockBits();

			/*
			LONGLONG sampleDuration = LTIME_SCALE * p->m_pAVIStream->m_aviStreamHeader.dwScale / p->m_pAVIStream->m_aviStreamHeader.dwRate;

			LONGLONG timeStart = sampleDuration*i;//p->m_currentFrame;
			LONGLONG timeEnd = timeStart+sampleDuration;

			sample->SetTime(&timeStart, &timeEnd);
			*/

			hr = p->m_pInputPin->Receive(sample);
			if (FAILED(hr))
				break;
		}
	}

	if (SUCCEEDED(hr))
		p->m_connectedTo->EndOfStream();	

#endif
	return 0;
}

void read_syn_window(double window[HAN_SIZE])
{
    int i,j[4];
    FILE *fp;
    double f[4];
    char t[150];

#if WIN32
	fp = fopen("C:/mmstudio/mpegaudio/tables/dewindow", "r");
#else
	fp = fopen("WinHD_C:/mmstudio/mpegaudio/tables/dewindow", "r");
#endif
	if (fp == NULL)
	{
		printf("Please check synthesis window table 'dewindow'\n");
		VERIFY(0);
	}
	for (i=0;i<512;i+=4) {
		fgets(t, 150, fp);
		sscanf(t,"D[%d] = %lf D[%d] = %lf D[%d] = %lf D[%d] = %lf\n",
			j, f,j+1,f+1,j+2,f+2,j+3,f+3);
		if (i==j[0]) {
			window[i] = f[0];
			window[i+1] = f[1];
			window[i+2] = f[2];
			window[i+3] = f[3];
		}
		else {
			printf("Check index in synthesis window table\n");
			VERIFY(0);
		}
		fgets(t,150,fp);
	}
	fclose(fp);
}

MPEGAudioSequence::MPEGAudioSequence()
{
	m_file = NULL;
	read_syn_window(D_tab);

	for (int i = 0; i < 64; i++)
	{
		for (int k = 0; k < 32; k++)
		{
			MatrixCos[i][k] = cos((16+i)*(2*k+1) * M_PI/64);
		}
	}

}

AudioSequence::AudioSequence()
{
	//m_nSamples = 0;

//	m_threadId = 0;
	m_hThread = NULL;

	m_mpeg_audio = new MPEGAudioSequence;
}

ErrorCode AudioSequence::Pause(/*LONGLONG tStart*/)
{
	m_hThread = CreateThread(AudioRunProc, (void*)(IPin*)this);
	//m_hThread = CreateThread(NULL, NULL, AudioRunProc, (LPVOID)(IPin*)this, 0, &m_threadId);
	if (m_hThread == NULL)
		return Error;

	return Success;
}

}	// MediaShow
}
