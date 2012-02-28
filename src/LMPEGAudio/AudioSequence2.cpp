#include "stdafx.h"
#include "LMPEGAudio.h"
#include "LMPEGAudioDecoder.h"

#include "AudioSequence.h"

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

int B1_nbal[8] =
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

int B1_levels[8][16] =
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

int grouping_tab[18] =
{
	-1,
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

namespace LMedia
{

void CAudioSequence::header()
{
	WORD syncword = m_file->getnbits(12);
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

	if (m_layer == 1)
		ASSERT(0);
	else if (m_layer == 2)
		m_N = 144 * bitrate_layer_II[m_bitrate_index]*1000 / sampling_freq_tab[m_sampling_frequency];
	else
		ASSERT(0);

	if (m_padding_bit)
		m_N++;
}

void CAudioSequence::error_check()
{
	if (m_protection_bit == 0)
	{
		ASSERT(0);	// Not yet supported
		THROW(-1);
		//crc_check();
	}
}

void CAudioSequence::audio_data()
{
	// Determine sblimit
	int sblimit;

	int freq = sampling_freq_tab[m_sampling_frequency];
	int bitrate_per_channel = bitrate_layer_II[m_bitrate_index];	// TODO

	if (m_mode != 3)	// single_channel
		bitrate_per_channel /= 2;

	if (freq == 44100 && (bitrate_per_channel == 32 || bitrate_per_channel == 48))
	{
		sblimit = 8;
	}
	else if (freq == 32000)
	{
		sblimit = 8;
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

	int nch = 2;	// ? number of channels

	int allocation[2][32];

	for (int sb = 0; sb < bound; sb++)
	{
		for (int ch=0; ch < nch; ch++)
		{
			unsigned int bits = m_file->getnbits(B1_nbal[sb]);
			allocation[ch][sb] = B1_levels[sb][bits];
		}
	}

	for (sb = bound; sb < sblimit; sb++)
	{
		unsigned int bits = m_file->getnbits(B1_nbal[sb]);

		allocation[0][sb] = B1_levels[sb][bits];
		allocation[1][sb] = allocation[0][sb];
	}

	int scfsi[2][32];

	for (sb = 0; sb < sblimit; sb++)
	{
		for (int ch = 0; ch < nch; ch++)
		{
			if (allocation[ch][sb] != 0)
			{
				scfsi[ch][sb] = m_file->getnbits(2);
			}
			else
				ASSERT(0);
		}
	}

	int scalefactor[2][32][3];

	for (sb = 0; sb < sblimit; sb++)
	{
		for (int ch = 0; ch < nch; ch++)
		{
			if (allocation[ch][sb] != 0)
			{
				if (scfsi[ch][sb] == 0)
				{
					scalefactor[ch][sb][0] = m_file->getnbits(6);
					scalefactor[ch][sb][1] = m_file->getnbits(6);
					scalefactor[ch][sb][2] = m_file->getnbits(6);
				}
				else if ((scfsi[ch][sb] == 1) || (scfsi[ch][sb] == 3))
				{
					scalefactor[ch][sb][0] = m_file->getnbits(6);
					scalefactor[ch][sb][2] = m_file->getnbits(6);
				}
				else if (scfsi[ch][sb] == 2)
				{
					scalefactor[ch][sb][0] = m_file->getnbits(6);
				}
			}
		}
	}

	bool grouping[2][32];
	int bits_per_codeword[2][32];

	{
		for (int ch = 0; ch < nch; ch++)
		{
			for (int sb = 0; sb < sblimit; sb++)
			{
				int allocindex;
				switch (allocation[ch][sb])
				{
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
			}
		}
	}

	int samplecode[2][32][12];
	int sample[2][32][36];

	for (int gr = 0; gr < 12; gr++)
	{
		{
			for (int sb = 0; sb < bound; sb++)
			{
				for (int ch = 0; ch < nch; ch++)
				{
					if (allocation[ch][sb] != 0)
					{
						if (grouping[ch][sb])
						{
							ASSERT(bits_per_codeword[ch][sb]>= 5 && bits_per_codeword[ch][sb] <= 10);
							samplecode[ch][sb][gr] = m_file->getnbits(bits_per_codeword[ch][sb]);	// 5..10
							nsample += 3;
						}
						else
						{
							for (int s = 0; s < 3; s++)
							{
								ASSERT(bits_per_codeword[ch][sb]>= 3 && bits_per_codeword[ch][sb] <= 16);
								sample[ch][sb][3*gr+s] = m_file->getnbits(bits_per_codeword[ch][sb]);	// 3..16
								nsample++;
							}
						}
					}
				}
			}
		}

		{
			for (int sb = bound; sb < sblimit; sb++)
			{
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
			}
		}
	}

	MessageBeep(-1);
}

void CAudioSequence::frame()
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
		audio_data();

//		m_file->skipnbits(8*5);
#if 0
		mc_extension()
		mpeg1_ancillary_data()
#endif
	}
}

HRESULT CAudioSequence::audio_sequence()
{
	for (int i = 0; i < 2; i++)
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
	return 0;
}

// Layer 2 tables

double  s_freq[4] = {44.1, 48, 32, 0};

int     bitrate[3][15] = {
          {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448},
          {0,32,48,56,64,80,96,112,128,160,192,224,256,320,384},
          {0,32,40,48,56,64,80,96,112,128,160,192,224,256,320}
        };

double FAR multiple[64] = {
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

////////////////////////////////////

/***********************************************************************
/*
/* Read one of the data files ("alloc_*") specifying the bit allocation/
/* quatization parameters for each subband in layer II encoding
/*
/**********************************************************************/

int read_bit_alloc(char* name, al_table *alloc)        /* read in table, return # subbands */
{
        unsigned int a, b, c, d, i, j;
        FILE *fp;
        char /*name[16],*/ t[80];
        int sblim;

		  /*
        strcpy(name, "alloc_0");

        switch (table) {
                case 0 : name[6] = '0';         break;
                case 1 : name[6] = '1';         break;
                case 2 : name[6] = '2';         break;
                case 3 : name[6] = '3';         break;
                default : name[6] = '0';
        }
		  */

        if (!(fp = fopen(name, "r"))) {
                printf("Please check bit allocation table %s\n", name);
                exit(1);
        }

        printf("using bit allocation table %s\n", name);

        fgets(t, 80, fp);
        sscanf(t, "%d\n", &sblim);
        while (!feof(fp)) {
                fgets(t, 80, fp);
                sscanf(t, "%d %d %d %d %d %d\n", &i, &j, &a, &b, &c, &d);
                        (*alloc)[i][j].steps = a;
                        (*alloc)[i][j].bits  = b;
                        (*alloc)[i][j].group = c;
                        (*alloc)[i][j].quant = d;
        }
        fclose(fp);
        return sblim;
}

al_table	alloc_table[4];
int alloc_sb_limit[4];

void* mem_alloc(DWORD size, char* unused)
{
	return GlobalAlloc(GMEM_ZEROINIT, size);
}

/*************************************************************
/*
/*   Pass the subband sample through the synthesis window
/*
/**************************************************************/

/* create in synthesis filter */

void create_syn_filter(double FAR filter[64][SBLIMIT])
{
    int i,k;

    for (i=0; i<64; i++)
        for (k=0; k<32; k++) {
            if ((filter[i][k] = 1e9*cos((double)((PI64*i+PI4)*(2*k+1)))) >= 0)
                modf(filter[i][k]+0.5, &filter[i][k]);
            else
                modf(filter[i][k]-0.5, &filter[i][k]);
            filter[i][k] *= 1e-9;
        }
}

/***************************************************************
/*
/*   Window the restored sample
/*
/***************************************************************/

/* read in synthesis window */

void read_syn_window(double FAR window[HAN_SIZE])
{
    int i,j[4];
    FILE *fp;
    double f[4];
    char t[150];

    if (!(fp = fopen("C:\\mpegaudio\\tables\\dewindow", "r") ))
	 {
        printf("Please check synthesis window table 'dewindow'\n");
        exit(1);
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
            exit(1);
        }
        fgets(t,150,fp);
    }
    fclose(fp);
}

int SubBandSynthesis (double *bandPtr, int channel, short *samples)
{
    int i,j,k;
    double *bufOffsetPtr, sum;
    static int init = 1;
    typedef double NN[64][32];
    static NN FAR *filter;
    typedef double BB[2][2*HAN_SIZE];
    static BB FAR *buf;
    static int bufOffset[2] = {64,64};
    static double FAR *window;
    int clip = 0;               /* count & return how many samples clipped */

    if (init) {
        buf = (BB FAR *) mem_alloc(sizeof(BB),"BB");
        filter = (NN FAR *) mem_alloc(sizeof(NN), "NN");
        create_syn_filter(*filter);
        window = (double FAR *) mem_alloc(sizeof(double) * HAN_SIZE, "WIN");
        read_syn_window(window);
        init = 0;
    }
/*    if (channel == 0) */
    bufOffset[channel] = (bufOffset[channel] - 64) & 0x3ff;
    bufOffsetPtr = &((*buf)[channel][bufOffset[channel]]);

    for (i=0; i<64; i++) {
        sum = 0;
        for (k=0; k<32; k++)
            sum += bandPtr[k] * (*filter)[i][k];
        bufOffsetPtr[i] = sum;
    }
    /*  S(i,j) = D(j+32i) * U(j+32i+((i+1)>>1)*64)  */
    /*  samples(i,j) = MWindow(j+32i) * bufPtr(j+32i+((i+1)>>1)*64)  */
    for (j=0; j<32; j++) {
        sum = 0;
        for (i=0; i<16; i++) {
            k = j + (i<<5);
            sum += window[k] * (*buf) [channel] [( (k + ( ((i+1)>>1) <<6) ) +
                                                  bufOffset[channel]) & 0x3ff];
        }

/*   {long foo = (sum > 0) ? sum * SCALE + 0.5 : sum * SCALE - 0.5; */
     {long foo = sum * SCALE;
     if (foo >= (long) SCALE)      {samples[j] = SCALE-1; ++clip;}
     else if (foo < (long) -SCALE) {samples[j] = -SCALE;  ++clip;}
     else                           samples[j] = foo;
 }
    }
    return(clip);
}

/**************************************************************
/*
/*   Restore the compressed sample to a factional number.
/*   first complement the MSB of the sample
/*    for layer I :
/*    Use s = (s' + 2^(-nb+1) ) * 2^nb / (2^nb-1)
/*   for Layer II :
/*   Use the formula s = s' * c + d
/*
/**************************************************************/

static double c[17] = { 1.33333333333, 1.60000000000, 1.14285714286,
                        1.77777777777, 1.06666666666, 1.03225806452,
                        1.01587301587, 1.00787401575, 1.00392156863,
                        1.00195694716, 1.00097751711, 1.00048851979,
                        1.00024420024, 1.00012208522, 1.00006103888,
                        1.00003051851, 1.00001525902 };

static double d[17] = { 0.500000000, 0.500000000, 0.250000000, 0.500000000,
                        0.125000000, 0.062500000, 0.031250000, 0.015625000,
                        0.007812500, 0.003906250, 0.001953125, 0.0009765625,
                        0.00048828125, 0.00024414063, 0.00012207031,
                        0.00006103516, 0.00003051758 };

/************************** Layer II stuff ************************/

void dequantize_sample_layer2(unsigned int FAR sample[2][3][SBLIMIT], unsigned int bit_alloc[2][SBLIMIT], double FAR fraction[2][3][SBLIMIT], frame_params *fr_ps)
{
    int i, j, k, x;
    int stereo = fr_ps->stereo;
    int sblimit = fr_ps->sblimit;
    al_table *alloc = fr_ps->alloc;

    for (i=0;i<sblimit;i++) 
		 for (j=0;j<3;j++) 
			 for (k=0;k<stereo;k++)
        if (bit_alloc[k][i]) {

            /* locate MSB in the sample */
            x = 0;
            while ((1L<<x) < (*alloc)[i][bit_alloc[k][i]].steps) x++;

            /* MSB inversion */
            if (((sample[k][j][i] >> x-1) & 1) == 1)
                fraction[k][j][i] = 0.0;
            else  fraction[k][j][i] = -1.0;

            /* Form a 2's complement sample */
            fraction[k][j][i] += (double) (sample[k][j][i] & ((1<<x-1)-1)) /
                (double) (1L<<x-1);

            /* Dequantize the sample */
            fraction[k][j][i] += d[(*alloc)[i][bit_alloc[k][i]].quant];
            fraction[k][j][i] *= c[(*alloc)[i][bit_alloc[k][i]].quant];
        }
        else fraction[k][j][i] = 0.0;   
   
    for (i=sblimit;i<SBLIMIT;i++) for (j=0;j<3;j++) for(k=0;k<stereo;k++)
        fraction[k][j][i] = 0.0;
}

/************************************************************
/*
/*   Restore the original value of the sample ie multiply
/*    the fraction value by its scalefactor.
/*
/************************************************************/

/************************* Layer II Stuff **********************/

void denormalize_sample_layer2(
	double FAR fraction[2][3][SBLIMIT],
	unsigned int scale_index[2][3][SBLIMIT],
	frame_params *fr_ps,
	int x
)
{
    int i,j;//,k;
    int stereo = fr_ps->stereo;
    int sblimit = fr_ps->sblimit;

    for (i=0;i<sblimit;i++) for (j=0;j<stereo;j++) {
        fraction[j][0][i] *= multiple[scale_index[j][x][i]];
        fraction[j][1][i] *= multiple[scale_index[j][x][i]];
        fraction[j][2][i] *= multiple[scale_index[j][x][i]];
    }
}

unsigned long hgetbits(CBitStream* bs, int nbits)
{
	return bs->getnbits(nbits);	// ??
}

int getbits(CBitStream* bs, int nbits)
{
	return bs->getnbits(nbits);
}

int get1bit(CBitStream* bs)
{
	return bs->getbit();
}

/************************* Layer III routines **********************/

void III_get_side_info(CBitStream* bs, III_side_info_t* si, frame_params* fr_ps)
{
   int ch, gr, i;
   int stereo = fr_ps->stereo;
   
   si->main_data_begin = bs->getnbits(9);
   if (stereo == 1)
      si->private_bits = bs->getnbits(5);
	else
		si->private_bits = bs->getnbits(3);

   for (ch=0; ch<stereo; ch++)
      for (i=0; i<4; i++)
      si->ch[ch].scfsi[i] = bs->getbit();

   for (gr=0; gr<2; gr++)
	{
      for (ch=0; ch<stereo; ch++)
		{
         si->ch[ch].gr[gr].part2_3_length = bs->getnbits(12);
         si->ch[ch].gr[gr].big_values = bs->getnbits(9);
         si->ch[ch].gr[gr].global_gain = bs->getnbits(8);
         si->ch[ch].gr[gr].scalefac_compress = bs->getnbits(4);
         si->ch[ch].gr[gr].window_switching_flag = bs->getbit();

         if (si->ch[ch].gr[gr].window_switching_flag)
			{
            si->ch[ch].gr[gr].block_type = bs->getnbits(2);
            si->ch[ch].gr[gr].mixed_block_flag = bs->getbit();
            for (i=0; i<2; i++)
               si->ch[ch].gr[gr].table_select[i] = bs->getnbits(5);
            for (i=0; i<3; i++)
               si->ch[ch].gr[gr].subblock_gain[i] = bs->getnbits(3);
               
            /* Set region_count parameters since they are implicit in this case. */
            
            if (si->ch[ch].gr[gr].block_type == 0) {
               printf("Side info bad: block_type == 0 in split block.\n");
               exit(0);
               }
            else if (si->ch[ch].gr[gr].block_type == 2
                     && si->ch[ch].gr[gr].mixed_block_flag == 0)
               si->ch[ch].gr[gr].region0_count = 8; /* MI 9; */
            else si->ch[ch].gr[gr].region0_count = 7; /* MI 8; */
            si->ch[ch].gr[gr].region1_count = 20 -
				      si->ch[ch].gr[gr].region0_count;
            }
         else {
            for (i=0; i<3; i++)
               si->ch[ch].gr[gr].table_select[i] = getbits(bs, 5);
            si->ch[ch].gr[gr].region0_count = getbits(bs, 4);
            si->ch[ch].gr[gr].region1_count = getbits(bs, 3);
            si->ch[ch].gr[gr].block_type = 0;
            }      
         si->ch[ch].gr[gr].preflag = get1bit(bs);
         si->ch[ch].gr[gr].scalefac_scale = get1bit(bs);
         si->ch[ch].gr[gr].count1table_select = get1bit(bs);
         }
      }
}

#if 0
void III_put_side_info(CBitStream* bs, III_side_info_t *si, frame_params *fr_ps)
{
   int ch, gr, i;
   int stereo = fr_ps->stereo;
 
   putbits(bs, si->main_data_begin,9);
   if (stereo == 1)
      putbits(bs, si->private_bits, 5);
      else putbits(bs, si->private_bits, 3);

   for (ch=0; ch<stereo; ch++)
      for (i=0; i<4; i++)
         put1bit(bs, si->ch[ch].scfsi[i]);

   for (gr=0; gr<2; gr++) {
      for (ch=0; ch<stereo; ch++) {
         putbits(bs, si->ch[ch].gr[gr].part2_3_length, 12);
         putbits(bs, si->ch[ch].gr[gr].big_values, 9);
         putbits(bs, si->ch[ch].gr[gr].global_gain, 8);
         putbits(bs, si->ch[ch].gr[gr].scalefac_compress, 4);
         put1bit(bs, si->ch[ch].gr[gr].window_switching_flag);
         if (si->ch[ch].gr[gr].window_switching_flag) {
            putbits(bs, si->ch[ch].gr[gr].block_type, 2);
            put1bit(bs, si->ch[ch].gr[gr].mixed_block_flag);
            for (i=0; i<2; i++)
               putbits(bs, si->ch[ch].gr[gr].table_select[i], 5);
            for (i=0; i<3; i++)
               putbits(bs, si->ch[ch].gr[gr].subblock_gain[i], 3);
            }
         else {
            for (i=0; i<3; i++)
            putbits(bs, si->ch[ch].gr[gr].table_select[i], 5);
            putbits(bs, si->ch[ch].gr[gr].region0_count, 4);
            putbits(bs, si->ch[ch].gr[gr].region1_count, 3);
            }      

         put1bit(bs, si->ch[ch].gr[gr].preflag);
         put1bit(bs, si->ch[ch].gr[gr].scalefac_scale);
         put1bit(bs, si->ch[ch].gr[gr].count1table_select);
         }
      }
}
#endif

struct {
   int l[5];
   int s[3];} sfbtable = {{0, 6, 11, 16, 21},
                          {0, 6, 12}};
                         
int slen[2][16] = {{0, 0, 0, 0, 3, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4},
                   {0, 1, 2, 3, 0, 1, 2, 3, 1, 2, 3, 1, 2, 3, 2, 3}};
struct  {
   int l[23];
   int s[14];} sfBandIndex[3] =   
   {{{0,4,8,12,16,20,24,30,36,44,52,62,74,90,110,134,162,196,238,288,342,418,576},
     {0,4,8,12,16,22,30,40,52,66,84,106,136,192}},
    {{0,4,8,12,16,20,24,30,36,42,50,60,72,88,106,128,156,190,230,276,330,384,576},
     {0,4,8,12,16,22,28,38,50,64,80,100,126,192}},
    {{0,4,8,12,16,20,24,30,36,44,54,66,82,102,126,156,194,240,296,364,448,550,576},
     {0,4,8,12,16,22,30,42,58,78,104,138,180,192}}};


void III_get_scale_factors(CBitStream* bs, III_scalefac_t *scalefac, III_side_info_t *si, int gr, int ch, frame_params *fr_ps)
{
int sfb, i, window;
struct gr_info_s *gr_info = &(si->ch[ch].gr[gr]);

    if (gr_info->window_switching_flag && (gr_info->block_type == 2))
	 { 
      if (gr_info->mixed_block_flag)
		{ /* MIXED */ /* NEW - ag 11/25 */
         for (sfb = 0; sfb < 8; sfb++)
            (*scalefac)[ch].l[sfb] = hgetbits( bs,
                 slen[0][gr_info->scalefac_compress]);
         for (sfb = 3; sfb < 6; sfb++)
            for (window=0; window<3; window++)
               (*scalefac)[ch].s[window][sfb] = hgetbits(bs,
                 slen[0][gr_info->scalefac_compress]);
         for (sfb = 6; sfb < 12; sfb++)
            for (window=0; window<3; window++)
               (*scalefac)[ch].s[window][sfb] = hgetbits(bs,
                 slen[1][gr_info->scalefac_compress]);
         for (sfb=12,window=0; window<3; window++)
            (*scalefac)[ch].s[window][sfb] = 0;
      }
      else
		{  /* SHORT*/
         for (i=0; i<2; i++) 
            for (sfb = sfbtable.s[i]; sfb < sfbtable.s[i+1]; sfb++)
               for (window=0; window<3; window++)
                  (*scalefac)[ch].s[window][sfb] = hgetbits(bs, 
                    slen[i][gr_info->scalefac_compress]);
         for (sfb=12,window=0; window<3; window++)
            (*scalefac)[ch].s[window][sfb] = 0;
      }
    }          
    else
	 {   /* LONG types 0,1,3 */
        for (i=0; i<4; i++) {
           if ((si->ch[ch].scfsi[i] == 0) || (gr == 0))
              for (sfb = sfbtable.l[i]; sfb < sfbtable.l[i+1]; sfb++)
                  (*scalefac)[ch].l[sfb] = hgetbits(bs,
                 slen[(i<2)?0:1][gr_info->scalefac_compress]);
        }
        (*scalefac)[ch].l[22] = 0; 
    }
}


/* Already declared in huffman.c
struct huffcodetab ht[HTN];
*/
int huffman_initialized = FALSE;

void initialize_huffman()
{
   FILE *fi;

	ASSERT(0);
#if 0
	
   if (huffman_initialized) return;
   if (!(fi = OpenTableFile("huffdec") )) {
      printf("Please check huffman table 'huffdec'\n");
      exit(1);
   }

   if (fi==NULL) {

      fprintf(stderr,"decoder table open error\n");

      exit(3);

      }

   if (read_decoder_table(fi) != HTN) {
      fprintf(stderr,"decoder table read error\n");
      exit(4);
      }
huffman_initialized = TRUE;
#endif
}

III_hufman_decode(long int is[SBLIMIT][SSLIMIT], III_side_info_t *si, int ch, int gr, int part2_start, frame_params *fr_ps)
{
	ASSERT(0);
#if 0
   int i, x, y;
   int v, w;
   struct huffcodetab *h;
   int region1Start;
   int region2Start;
   int bt = (*si).ch[ch].gr[gr].window_switching_flag && ((*si).ch[ch].gr[gr].block_type == 2);

   initialize_huffman();

   /* Find region boundary for short block case. */
   
   if ( ((*si).ch[ch].gr[gr].window_switching_flag) && 
        ((*si).ch[ch].gr[gr].block_type == 2) ) { 
   
      /* Region2. */

      region1Start = 36;  /* sfb[9/3]*3=36 */
      region2Start = 576; /* No Region2 for short block case. */
   }


   else {          /* Find region boundary for long block case. */

      region1Start = sfBandIndex[fr_ps->header->sampling_frequency]
                           .l[(*si).ch[ch].gr[gr].region0_count + 1]; /* MI */
      region2Start = sfBandIndex[fr_ps->header->sampling_frequency]
                              .l[(*si).ch[ch].gr[gr].region0_count +
                              (*si).ch[ch].gr[gr].region1_count + 2]; /* MI */
      }


   /* Read bigvalues area. */
   for (i=0; i<(*si).ch[ch].gr[gr].big_values*2; i+=2) {
      if      (i<region1Start) h = &ht[(*si).ch[ch].gr[gr].table_select[0]];
      else if (i<region2Start) h = &ht[(*si).ch[ch].gr[gr].table_select[1]];
           else                h = &ht[(*si).ch[ch].gr[gr].table_select[2]];
      huffman_decoder(h, &x, &y, &v, &w);
      is[i/SSLIMIT][i%SSLIMIT] = x;
      is[(i+1)/SSLIMIT][(i+1)%SSLIMIT] = y;
      }

   /* Read count1 area. */
   h = &ht[(*si).ch[ch].gr[gr].count1table_select+32];
   while ((hsstell() < part2_start + (*si).ch[ch].gr[gr].part2_3_length ) &&
     ( i < SSLIMIT*SBLIMIT )) {
      huffman_decoder(h, &x, &y, &v, &w);
      is[i/SSLIMIT][i%SSLIMIT] = v;
      is[(i+1)/SSLIMIT][(i+1)%SSLIMIT] = w;
      is[(i+2)/SSLIMIT][(i+2)%SSLIMIT] = x;
      is[(i+3)/SSLIMIT][(i+3)%SSLIMIT] = y;
      i += 4;
      }

   if (hsstell() > part2_start + (*si).ch[ch].gr[gr].part2_3_length)
   {  i -=4;
      rewindNbits(hsstell()-part2_start - (*si).ch[ch].gr[gr].part2_3_length);
   }

   /* Dismiss stuffing Bits */
   if ( hsstell() < part2_start + (*si).ch[ch].gr[gr].part2_3_length )
      hgetbits( part2_start + (*si).ch[ch].gr[gr].part2_3_length - hsstell());

   /* Zero out rest. */
   for (; i<SSLIMIT*SBLIMIT; i++)
      is[i/SSLIMIT][i%SSLIMIT] = 0;
#endif
}


int pretab[22] = {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3,3,2,0};

void III_dequantize_sample(long int is[SBLIMIT][SSLIMIT], double xr[SBLIMIT][SSLIMIT], III_scalefac_t *scalefac, struct gr_info_s *gr_info, int ch,frame_params *fr_ps)
{
   int ss,sb,cb=0,sfreq=fr_ps->header->sampling_frequency;
   int stereo = fr_ps->stereo;
   int next_cb_boundary, cb_begin, cb_width, sign;

   /* choose correct scalefactor band per block type, initalize boundary */

   if (gr_info->window_switching_flag && (gr_info->block_type == 2) )
      if (gr_info->mixed_block_flag) 
         next_cb_boundary=sfBandIndex[sfreq].l[1];  /* LONG blocks: 0,1,3 */
      else {
         next_cb_boundary=sfBandIndex[sfreq].s[1]*3; /* pure SHORT block */
    cb_width = sfBandIndex[sfreq].s[1];
    cb_begin = 0;
      }  
   else 
      next_cb_boundary=sfBandIndex[sfreq].l[1];  /* LONG blocks: 0,1,3 */

   /* apply formula per block type */

   for (sb=0 ; sb < SBLIMIT ; sb++)
      for (ss=0 ; ss < SSLIMIT ; ss++) {

         if ( (sb*18)+ss == next_cb_boundary)  { /* Adjust critical band boundary */
            if (gr_info->window_switching_flag && (gr_info->block_type == 2)) {
               if (gr_info->mixed_block_flag)  {
                  if (((sb*18)+ss) == sfBandIndex[sfreq].l[8])  {
                     next_cb_boundary=sfBandIndex[sfreq].s[4]*3; 
                     cb = 3;
                     cb_width = sfBandIndex[sfreq].s[cb+1] - 
                                sfBandIndex[sfreq].s[cb];
                     cb_begin = sfBandIndex[sfreq].s[cb]*3;      
                  }
                  else if (((sb*18)+ss) < sfBandIndex[sfreq].l[8]) 
                     next_cb_boundary = sfBandIndex[sfreq].l[(++cb)+1];
                  else {
                     next_cb_boundary = sfBandIndex[sfreq].s[(++cb)+1]*3;
                     cb_width = sfBandIndex[sfreq].s[cb+1] - 
                                    sfBandIndex[sfreq].s[cb];
                     cb_begin = sfBandIndex[sfreq].s[cb]*3;      
                  }   
               }
               else  {
                  next_cb_boundary = sfBandIndex[sfreq].s[(++cb)+1]*3;
                  cb_width = sfBandIndex[sfreq].s[cb+1] - 
                               sfBandIndex[sfreq].s[cb];
                cb_begin = sfBandIndex[sfreq].s[cb]*3;      
               } 
            }
            else /* long blocks */
               next_cb_boundary = sfBandIndex[sfreq].l[(++cb)+1];
         }

         /* Compute overall (global) scaling. */

         xr[sb][ss] = pow( 2.0 , (0.25 * (gr_info->global_gain - 210.0)));

         /* Do long/short dependent scaling operations. */
        
         if (gr_info->window_switching_flag && (
            ((gr_info->block_type == 2) && (gr_info->mixed_block_flag == 0)) ||
            ((gr_info->block_type == 2) && gr_info->mixed_block_flag && (sb >= 2)) )) {

            xr[sb][ss] *= pow(2.0, 0.25 * -8.0 * 
                    gr_info->subblock_gain[(((sb*18)+ss) - cb_begin)/cb_width]);
            xr[sb][ss] *= pow(2.0, 0.25 * -2.0 * (1.0+gr_info->scalefac_scale)
              * (*scalefac)[ch].s[(((sb*18)+ss) - cb_begin)/cb_width][cb]);
         }
         else {   /* LONG block types 0,1,3 & 1st 2 subbands of switched blocks */
            xr[sb][ss] *= pow(2.0, -0.5 * (1.0+gr_info->scalefac_scale)
                                        * ((*scalefac)[ch].l[cb]
                                        + gr_info->preflag * pretab[cb]));
         }

         /* Scale quantized value. */
        
         sign = (is[sb][ss]<0) ? 1 : 0; 
         xr[sb][ss] *= pow( (double) abs(is[sb][ss]), ((double)4.0/3.0) );
         if (sign) xr[sb][ss] = -xr[sb][ss];
      }
}

III_reorder (double xr[SBLIMIT][SSLIMIT], double ro[SBLIMIT][SSLIMIT], struct gr_info_s *gr_info, frame_params *fr_ps) 
{
   int sfreq=fr_ps->header->sampling_frequency;
   int sfb, sfb_start, sfb_lines;
   int sb, ss, window, freq, src_line, des_line;

   for(sb=0;sb<SBLIMIT;sb++)
      for(ss=0;ss<SSLIMIT;ss++) 
         ro[sb][ss] = 0;

   if (gr_info->window_switching_flag && (gr_info->block_type == 2)) {
      if (gr_info->mixed_block_flag) {
         /* NO REORDER FOR LOW 2 SUBBANDS */
         for (sb=0 ; sb < 2 ; sb++)
            for (ss=0 ; ss < SSLIMIT ; ss++) {
               ro[sb][ss] = xr[sb][ss];
            }
         /* REORDERING FOR REST SWITCHED SHORT */
         for(sfb=3,sfb_start=sfBandIndex[sfreq].s[3],
            sfb_lines=sfBandIndex[sfreq].s[4] - sfb_start; 
            sfb < 13; sfb++,sfb_start=sfBandIndex[sfreq].s[sfb],
            (sfb_lines=sfBandIndex[sfreq].s[sfb+1] - sfb_start))
               for(window=0; window<3; window++)
                  for(freq=0;freq<sfb_lines;freq++) {
                     src_line = sfb_start*3 + window*sfb_lines + freq; 
                     des_line = (sfb_start*3) + window + (freq*3);
                     ro[des_line/SSLIMIT][des_line%SSLIMIT] = 
                                    xr[src_line/SSLIMIT][src_line%SSLIMIT];
               }
      } 
      else {  /* pure short */
         for(sfb=0,sfb_start=0,sfb_lines=sfBandIndex[sfreq].s[1]; 
            sfb < 13; sfb++,sfb_start=sfBandIndex[sfreq].s[sfb],
            (sfb_lines=sfBandIndex[sfreq].s[sfb+1] - sfb_start))
               for(window=0; window<3; window++)
                  for(freq=0;freq<sfb_lines;freq++) {
                     src_line = sfb_start*3 + window*sfb_lines + freq; 
                     des_line = (sfb_start*3) + window + (freq*3);
                     ro[des_line/SSLIMIT][des_line%SSLIMIT] = 
                                    xr[src_line/SSLIMIT][src_line%SSLIMIT];
               }
      }
   }
   else {   /*long blocks */
      for (sb=0 ; sb < SBLIMIT ; sb++)
         for (ss=0 ; ss < SSLIMIT ; ss++) 
            ro[sb][ss] = xr[sb][ss];
   }
}



void III_stereo(double xr[2][SBLIMIT][SSLIMIT], double lr[2][SBLIMIT][SSLIMIT], III_scalefac_t *scalefac, struct gr_info_s *gr_info, frame_params *fr_ps)
{
   int sfreq = fr_ps->header->sampling_frequency;
   int stereo = fr_ps->stereo;
   int ms_stereo = (fr_ps->header->mode == MPG_MD_JOINT_STEREO) &&
                   (fr_ps->header->mode_ext & 0x2); 
   int i_stereo = (fr_ps->header->mode == MPG_MD_JOINT_STEREO) &&
                  (fr_ps->header->mode_ext & 0x1);
   int js_bound;  /* frequency line that marks the beggining of the zero part */  
   int sfb,next_sfb_boundary;
   int i,j,sb,ss,ch,is_pos[576]; 
   double is_ratio[576];
  
   /* intialization */
   for ( i=0; i<576; i++ )
      is_pos[i] = 7;

   if ((stereo == 2) && i_stereo )
   {  if (gr_info->window_switching_flag && (gr_info->block_type == 2))
      {  if( gr_info->mixed_block_flag )
         {  int max_sfb = 0;

            for ( j=0; j<3; j++ )
            {  int sfbcnt;
               sfbcnt = 2;
               for( sfb=12; sfb >=3; sfb-- )
               {  int lines;
                  lines = sfBandIndex[sfreq].s[sfb+1]-sfBandIndex[sfreq].s[sfb];
                  i = 3*sfBandIndex[sfreq].s[sfb] + (j+1) * lines - 1;
                  while ( lines > 0 )
                  {  if ( xr[1][i/SSLIMIT][i%SSLIMIT] != 0.0 )
                     {  sfbcnt = sfb;
                        sfb = -10;
                        lines = -10;
                     }
                     lines--;
                     i--;
                  }
               }
               sfb = sfbcnt + 1;

               if ( sfb > max_sfb )
                  max_sfb = sfb;

               while( sfb<12 )
               {  sb = sfBandIndex[sfreq].s[sfb+1]-sfBandIndex[sfreq].s[sfb];
                  i = 3*sfBandIndex[sfreq].s[sfb] + j * sb;
                  for ( ; sb > 0; sb--)
                  {  is_pos[i] = (*scalefac)[1].s[j][sfb];
                     if ( is_pos[i] != 7 )
                        is_ratio[i] = tan( is_pos[i] * (PI / 12));
                     i++;
                  }
                  sfb++;
               }
               sb = sfBandIndex[sfreq].s[11]-sfBandIndex[sfreq].s[10];
               sfb = 3*sfBandIndex[sfreq].s[10] + j * sb;
               sb = sfBandIndex[sfreq].s[12]-sfBandIndex[sfreq].s[11];
               i = 3*sfBandIndex[sfreq].s[11] + j * sb;
               for ( ; sb > 0; sb-- )
               {  is_pos[i] = is_pos[sfb];
                  is_ratio[i] = is_ratio[sfb];
                  i++;
               }
             }
             if ( max_sfb <= 3 )
             {  i = 2;
                ss = 17;
                sb = -1;
                while ( i >= 0 )
                {  if ( xr[1][i][ss] != 0.0 )
                   {  sb = i*18+ss;
                      i = -1;
                   } else
                   {  ss--;
                      if ( ss < 0 )
                      {  i--;
                         ss = 17;
                      }
                   }
                }
                i = 0;
                while ( sfBandIndex[sfreq].l[i] <= sb )
                   i++;
                sfb = i;
                i = sfBandIndex[sfreq].l[i];
                for ( ; sfb<8; sfb++ )
                {  sb = sfBandIndex[sfreq].l[sfb+1]-sfBandIndex[sfreq].l[sfb];
                   for ( ; sb > 0; sb--)
                   {  is_pos[i] = (*scalefac)[1].l[sfb];
                      if ( is_pos[i] != 7 )
                         is_ratio[i] = tan( is_pos[i] * (PI / 12));
                      i++;
                   }
                }
            }
         } else
         {  for ( j=0; j<3; j++ )
            {  int sfbcnt;
               sfbcnt = -1;
               for( sfb=12; sfb >=0; sfb-- )
               {  int lines;
                  lines = sfBandIndex[sfreq].s[sfb+1]-sfBandIndex[sfreq].s[sfb];
                  i = 3*sfBandIndex[sfreq].s[sfb] + (j+1) * lines - 1;
                  while ( lines > 0 )
                  {  if ( xr[1][i/SSLIMIT][i%SSLIMIT] != 0.0 )
                     {  sfbcnt = sfb;
                        sfb = -10;
                        lines = -10;
                     }
                     lines--;
                     i--;
                  }
               }
               sfb = sfbcnt + 1;
               while( sfb<12 )
               {  sb = sfBandIndex[sfreq].s[sfb+1]-sfBandIndex[sfreq].s[sfb];
                  i = 3*sfBandIndex[sfreq].s[sfb] + j * sb;
                  for ( ; sb > 0; sb--)
                  {  is_pos[i] = (*scalefac)[1].s[j][sfb];
                     if ( is_pos[i] != 7 )
                        is_ratio[i] = tan( is_pos[i] * (PI / 12));
                     i++;
                  }
                  sfb++;
               }

               sb = sfBandIndex[sfreq].s[11]-sfBandIndex[sfreq].s[10];
               sfb = 3*sfBandIndex[sfreq].s[10] + j * sb;
               sb = sfBandIndex[sfreq].s[12]-sfBandIndex[sfreq].s[11];
               i = 3*sfBandIndex[sfreq].s[11] + j * sb;
               for ( ; sb > 0; sb-- )
               {  is_pos[i] = is_pos[sfb];
                  is_ratio[i] = is_ratio[sfb];
                  i++;
               }
            }
         }
      } else
      {  i = 31;
         ss = 17;
         sb = 0;
         while ( i >= 0 )
         {  if ( xr[1][i][ss] != 0.0 )
            {  sb = i*18+ss;
               i = -1;
            } else
            {  ss--;
               if ( ss < 0 )
               {  i--;
                  ss = 17;
               }
            }
         }
         i = 0;
         while ( sfBandIndex[sfreq].l[i] <= sb )
            i++;
         sfb = i;
         i = sfBandIndex[sfreq].l[i];
         for ( ; sfb<21; sfb++ )
         {  sb = sfBandIndex[sfreq].l[sfb+1] - sfBandIndex[sfreq].l[sfb];
            for ( ; sb > 0; sb--)
            {  is_pos[i] = (*scalefac)[1].l[sfb];
               if ( is_pos[i] != 7 )
                  is_ratio[i] = tan( is_pos[i] * (PI / 12));
               i++;
            }
         }
         sfb = sfBandIndex[sfreq].l[20];
         for ( sb = 576 - sfBandIndex[sfreq].l[21]; sb > 0; sb-- )
         {  is_pos[i] = is_pos[sfb];
            is_ratio[i] = is_ratio[sfb];
            i++;
         }
      }
   }

   for(ch=0;ch<2;ch++)
      for(sb=0;sb<SBLIMIT;sb++)
         for(ss=0;ss<SSLIMIT;ss++) 
            lr[ch][sb][ss] = 0;

   if (stereo==2) 
      for(sb=0;sb<SBLIMIT;sb++)
         for(ss=0;ss<SSLIMIT;ss++) {
            i = (sb*18)+ss;
            if ( is_pos[i] == 7 ) {
               if ( ms_stereo ) {
                  lr[0][sb][ss] = (xr[0][sb][ss]+xr[1][sb][ss])/1.41421356;
                  lr[1][sb][ss] = (xr[0][sb][ss]-xr[1][sb][ss])/1.41421356;
               }
               else {
                  lr[0][sb][ss] = xr[0][sb][ss];
                  lr[1][sb][ss] = xr[1][sb][ss];
               }
            }
            else if (i_stereo ) {
               lr[0][sb][ss] = xr[0][sb][ss] * (is_ratio[i]/(1+is_ratio[i]));
               lr[1][sb][ss] = xr[0][sb][ss] * (1/(1+is_ratio[i])); 
            }
            else {
               printf("Error in streo processing\n");
            }
         }
   else  /* mono , bypass xr[0][][] to lr[0][][]*/
      for(sb=0;sb<SBLIMIT;sb++)
         for(ss=0;ss<SSLIMIT;ss++)
            lr[0][sb][ss] = xr[0][sb][ss];

}

double Ci[8]={-0.6,-0.535,-0.33,-0.185,-0.095,-0.041,-0.0142,-0.0037};

void III_antialias(double xr[SBLIMIT][SSLIMIT], double hybridIn[SBLIMIT][SSLIMIT], struct gr_info_s *gr_info, frame_params *fr_ps)
{
   static int    init = 1;
   static double ca[8],cs[8];
   double        bu,bd;  /* upper and lower butterfly inputs */
   int           ss,sb,sblim;

   if (init) {
      int i;
      double    sq;
      for (i=0;i<8;i++) {
         sq=sqrt(1.0+Ci[i]*Ci[i]);
         cs[i] = 1.0/sq;
         ca[i] = Ci[i]/sq;
      }
      init = 0;
   }
   
   /* clear all inputs */  
      
    for(sb=0;sb<SBLIMIT;sb++)
       for(ss=0;ss<SSLIMIT;ss++)
          hybridIn[sb][ss] = xr[sb][ss];

   if  (gr_info->window_switching_flag && (gr_info->block_type == 2) &&
       !gr_info->mixed_block_flag ) return;

   if ( gr_info->window_switching_flag && gr_info->mixed_block_flag &&
     (gr_info->block_type == 2))
      sblim = 1;
   else
      sblim = SBLIMIT-1;

   /* 31 alias-reduction operations between each pair of sub-bands */
   /* with 8 butterflies between each pair                         */

   for(sb=0;sb<sblim;sb++)   
      for(ss=0;ss<8;ss++) {      
         bu = xr[sb][17-ss];
         bd = xr[sb+1][ss];
         hybridIn[sb][17-ss] = (bu * cs[ss]) - (bd * ca[ss]);
         hybridIn[sb+1][ss] = (bd * cs[ss]) + (bu * ca[ss]);
         }  
}

void inv_mdct(double in[18], double out[36], int block_type)
{
/*------------------------------------------------------------------*/
/*                                                                  */
/*    Function: Calculation of the inverse MDCT                     */
/*    In the case of short blocks the 3 output vectors are already  */
/*    overlapped and added in this modul.                           */
/*                                                                  */
/*    New layer3                                                    */
/*                                                                  */
/*------------------------------------------------------------------*/

int     k,i,m,N,p;
double  tmp[12],sum;
static  double  win[4][36];
static  int init=0;
static  double COS[4*36];

    if(init==0){

    /* type 0 */
      for(i=0;i<36;i++)
         win[0][i] = sin( PI/36 *(i+0.5) );

    /* type 1*/
      for(i=0;i<18;i++)
         win[1][i] = sin( PI/36 *(i+0.5) );
      for(i=18;i<24;i++)
         win[1][i] = 1.0;
      for(i=24;i<30;i++)
         win[1][i] = sin( PI/12 *(i+0.5-18) );
      for(i=30;i<36;i++)
         win[1][i] = 0.0;

    /* type 3*/
      for(i=0;i<6;i++)
         win[3][i] = 0.0;
      for(i=6;i<12;i++)
         win[3][i] = sin( PI/12 *(i+0.5-6) );
      for(i=12;i<18;i++)
         win[3][i] =1.0;
      for(i=18;i<36;i++)
         win[3][i] = sin( PI/36*(i+0.5) );

    /* type 2*/
      for(i=0;i<12;i++)
         win[2][i] = sin( PI/12*(i+0.5) ) ;
      for(i=12;i<36;i++)
         win[2][i] = 0.0 ;

      for (i=0; i<4*36; i++)
         COS[i] = cos(PI/(2*36) * i);

      init++;
    }

    for(i=0;i<36;i++)
       out[i]=0;

    if(block_type == 2){
       N=12;
       for(i=0;i<3;i++){
          for(p= 0;p<N;p++){
             sum = 0.0;
             for(m=0;m<N/2;m++)
                sum += in[i+3*m] * cos( PI/(2*N)*(2*p+1+N/2)*(2*m+1) );
             tmp[p] = sum * win[block_type][p] ;
          }
          for(p=0;p<N;p++)
             out[6*i+p+6] += tmp[p];
       }
    }
    else{
      N=36;
      for(p= 0;p<N;p++){
         sum = 0.0;
         for(m=0;m<N/2;m++)
           sum += in[m] * COS[((2*p+1+N/2)*(2*m+1))%(4*36)];
         out[p] = sum * win[block_type][p];
      }
    }
}

void III_hybrid(double fsIn[SSLIMIT],   /* freq samples per subband in */
					 double tsOut[SSLIMIT],  /* time samples per subband out */
					 int sb, int ch, struct gr_info_s *gr_info, frame_params *fr_ps)

{
   int ss;
   double rawout[36];
   static double prevblck[2][SBLIMIT][SSLIMIT];
   static int init = 1;
   int bt;

   if (init) {
      int i,j,k;
      
      for(i=0;i<2;i++)
         for(j=0;j<SBLIMIT;j++)
            for(k=0;k<SSLIMIT;k++)
               prevblck[i][j][k]=0.0;
      init = 0;
   }

   bt = (gr_info->window_switching_flag && gr_info->mixed_block_flag &&
          (sb < 2)) ? 0 : gr_info->block_type; 

   inv_mdct( fsIn, rawout, bt);

   /* overlap addition */
   for(ss=0; ss<SSLIMIT; ss++) {
      tsOut[ss] = rawout[ss] + prevblck[ch][sb][ss];
      prevblck[ch][sb][ss] = rawout[ss+18];
   }
}

/* Return the number of slots for main data of current frame, */

int main_data_slots(frame_params fr_ps)
{
	int nSlots;

   nSlots = (144 * bitrate[2][fr_ps.header->bitrate_index])
	    / s_freq[fr_ps.header->sampling_frequency];
  if (fr_ps.header->padding) nSlots++;
  nSlots -= 4;
  if (fr_ps.header->error_protection) nSlots -= 2;
  if (fr_ps.stereo == 1) nSlots -= 17; else nSlots -=32;
  return(nSlots);
}


/////////////////////////////////////////////////////////////////////////
//

BOOL CAudioSequence::seek_sync()
{
	m_file->byte_align();

	while (TRUE/*!m_file->eof()*/)
	{
		try
		{
			WORD syncword = m_file->getnbits(12);
			if (syncword == 0xfff)
				return TRUE;
		}
		catch(int code)
		{
			return FALSE;
		}

		m_file->ungetbits(4);	// make still byte-aligned
		ASSERT(m_file->is_byte_aligned());
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////////////
//

HRESULT CAudioSequence::audio_sequence()
{
    pcm_sample = (PCM FAR *) mem_alloc((long) sizeof(PCM), "PCM Samp");
    sample = (SAM FAR *) mem_alloc((long) sizeof(SAM), "Sample");
    fraction = (FRA FAR *) mem_alloc((long) sizeof(FRA), "fraction");
    w = (VE FAR *) mem_alloc((long) sizeof(VE), "w");

	alloc_sb_limit[0] = read_bit_alloc("C:\\mpegaudio\\tables\\alloc_0", &alloc_table[0]);
	alloc_sb_limit[1] = read_bit_alloc("C:\\mpegaudio\\tables\\alloc_1", &alloc_table[1]);
	alloc_sb_limit[2] = read_bit_alloc("C:\\mpegaudio\\tables\\alloc_2", &alloc_table[2]);
	alloc_sb_limit[3] = read_bit_alloc("C:\\mpegaudio\\tables\\alloc_3", &alloc_table[3]);

//	m_nSamples = 1152;	// TODO, number of samples for one frame in layer2

	while (seek_sync())
	{
		try
		{
			frame();

#ifdef _DEBUG
			if (!(m_frames.GetCount() % 100))
			{
				TRACE("audio frame: %d\n", m_frames.GetCount());
			}
#endif
			/*
			if (m_frames.GetCount() > 800)
			{
				break;
			}
			*/
		}
		catch(int)
		{
			return S_FALSE;	// Partial success
		}
	}

	return S_OK;
}

void CAudioSequence::frame()
{
	frame_params* frame = new frame_params;

	m_frames.AddTail(frame);

	header(frame);
	error_check(frame);

//	LARGE_INTEGER li;
//	li.QuadPart = 0;

	frame->m_fileDataBytePos = m_file->m_byteStream->Seek(0, STREAM_SEEK_CUR);
	frame->m_fileDataBitCnt = m_file->m_bitcnt;

	audio_data_layer2(frame, NULL);

	/*
	if (frame.m_layer == 1) audio_data_layer1();
	else if (frame.m_layer == 2) audio_data_layer2(frame);
	else if (frame.m_layer == 3) audio_data_layer3();
*/
//	ancillary_data();
}

int js_bound(int lay, int m_ext)
{
static int jsb_table[3][4] =  { { 4, 8, 12, 16 }, { 4, 8, 12, 16},
                                { 0, 4, 8, 16} };  /* lay+m_e -> jsbound */

    if(lay<1 || lay >3 || m_ext<0 || m_ext>3) {
        fprintf(stderr, "js_bound bad layer/modext (%d/%d)\n", lay, m_ext);
        exit(1);
    }
    return(jsb_table[lay-1][m_ext]);
}

void CAudioSequence::header(frame_params* frame)
{
	BYTE ID = m_file->getbit();
	frame->header->m_layer = 4-m_file->getnbits(2);
	frame->header->error_protection = m_file->getbit();
	frame->header->bitrate_index = m_file->getnbits(4);
	frame->header->sampling_frequency = m_file->getnbits(2);
	frame->header->padding = m_file->getbit();//padding,-bit
	m_file->getbit();//private-bit
	frame->header->mode = m_file->getnbits(2);
	frame->header->mode_ext = m_file->getnbits(2);//mode-extension
	frame->header->m_copyright = m_file->getbit();
	frame->header->m_original = m_file->getbit();//original or copy
	m_file->getnbits(2);//emphasis

	frame->stereo = (frame->header->mode == MPG_MD_MONO) ? 1 : 2;

	if (frame->header->m_layer == 2)
	 {
        int table, lay, ws, bsp, br_per_ch, sfrq;
        //int sblim = fra->sblimit;     /* return current value if no load */

        lay = frame->header->m_layer-1;
        bsp = frame->header->bitrate_index;
        br_per_ch = bitrate[lay][bsp] / frame->stereo;
        ws = frame->header->sampling_frequency;
        sfrq = s_freq[ws];
        /* decision rules refer to per-channel bitrates (kbits/sec/chan) */
        if ((sfrq == 48 && br_per_ch >= 56) ||
            (br_per_ch >= 56 && br_per_ch <= 80)) table = 0;
        else if (sfrq != 48 && br_per_ch >= 96) table = 1;
        else if (sfrq != 32 && br_per_ch <= 48) table = 2;
        else table = 3;
		  /*
        if (fr_ps->tab_num != table)
		  {
           if (fr_ps->tab_num >= 0)
              mem_free((void **)&(fr_ps->alloc));
           frame->alloc = (al_table FAR *) mem_alloc(sizeof(al_table),
                                                         "alloc");
           frame->sblimit = read_bit_alloc(fr_ps->tab_num = table, fr_ps->alloc);
        }
		  */
		  frame->sblimit = alloc_sb_limit[table];
		  frame->alloc = &alloc_table[table];

	 }
    else
	 {
		 frame->sblimit = SBLIMIT;
	 }

    if(frame->header->mode == MPG_MD_JOINT_STEREO)
        frame->jsbound = js_bound(frame->header->m_layer, frame->header->mode_ext);
    else
        frame->jsbound = frame->sblimit;
    /* alloc, tab_num set in pick_table */
}

void CAudioSequence::error_check(frame_params* frame)
{
	if (frame->header->error_protection == 0)
	{
		WORD crc_check = m_file->getnbits(16);
	}
}

void CAudioSequence::audio_data_layer1()
{
	ASSERT(0);
}

void CAudioSequence::decode_bitalloc_layer2(unsigned int bit_alloc[2][SBLIMIT], frame_params *fr_ps)
{
	int stereo = fr_ps->stereo;
	int sblimit = fr_ps->sblimit;
	int jsbound = fr_ps->jsbound;
	al_table *alloc = fr_ps->alloc;

	int sb;
	int ch;

	for (sb = 0; sb < jsbound; sb++)
	{
		for (ch = 0; ch < stereo; ch++)
		{
			bit_alloc[ch][sb] = m_file->getnbits((*alloc)[sb][0].bits);
		}
	}

// This loop is for joint-stereo
	for (sb = jsbound; sb < sblimit; sb++)
	{
		bit_alloc[0][sb]	= m_file->getnbits((*alloc)[sb][0].bits);
		bit_alloc[1][sb] = bit_alloc[0][sb];
	}
}

void CAudioSequence::decode_scale_layer2(
	unsigned int scfsi[2][SBLIMIT],
	unsigned int bit_alloc[2][SBLIMIT],
	unsigned int scale_index[2][3][SBLIMIT],
	frame_params *fr_ps
)
{
    int i,j;
    int stereo = fr_ps->stereo;
    int sblimit = fr_ps->sblimit;
   
    for (i=0;i<sblimit;i++) for (j=0;j<stereo;j++) /* 2 bit scfsi */
        if (bit_alloc[j][i]) scfsi[j][i] = (char) m_file->getnbits(2);
    for (i=sblimit;i<SBLIMIT;i++) for (j=0;j<stereo;j++)   
        scfsi[j][i] = 0;

    for (i=0;i<sblimit;i++) for (j=0;j<stereo;j++) {
        if (bit_alloc[j][i])   
            switch (scfsi[j][i]) {
                /* all three scale factors transmitted */
             case 0 : scale_index[j][0][i] = m_file->getnbits(6);
                scale_index[j][1][i] = m_file->getnbits(6);
                scale_index[j][2][i] = m_file->getnbits(6);
                break;
                /* scale factor 1 & 3 transmitted */
             case 1 : scale_index[j][0][i] =
                 scale_index[j][1][i] = m_file->getnbits(6);
                scale_index[j][2][i] = m_file->getnbits(6);
                break;
                /* scale factor 1 & 2 transmitted */
             case 3 : scale_index[j][0][i] = m_file->getnbits(6);
                scale_index[j][1][i] =
                    scale_index[j][2][i] =  m_file->getnbits(6);
                break;
                /* only one scale factor transmitted */
             case 2 : scale_index[j][0][i] =
                 scale_index[j][1][i] =
                     scale_index[j][2][i] = m_file->getnbits(6);
                break;
                default : break;
            }
        else {
            scale_index[j][0][i] = scale_index[j][1][i] =
                scale_index[j][2][i] = SCALE_RANGE-1;
        }
    }
    for (i=sblimit;i<SBLIMIT;i++) for (j=0;j<stereo;j++) {
        scale_index[j][0][i] = scale_index[j][1][i] =
            scale_index[j][2][i] = SCALE_RANGE-1;
    }
}

void CAudioSequence::buffer_sample_layer2(
	unsigned int FAR sample[2][3][SBLIMIT],
	unsigned int bit_alloc[2][SBLIMIT],
	frame_params *fr_ps
)
{
	int stereo = fr_ps->stereo;
	int sblimit = fr_ps->sblimit;
	int jsbound = fr_ps->jsbound;
	al_table *alloc = fr_ps->alloc;

	int i, j, k, m;

	for (i=0;i<sblimit;i++) for (j=0;j<((i<jsbound)?stereo:1);j++) {
		if (bit_alloc[j][i]) {
			/* check for grouping in subband */
			if ((*alloc)[i][bit_alloc[j][i]].group==3)
				for (m=0;m<3;m++) {
					k = (*alloc)[i][bit_alloc[j][i]].bits;
					sample[j][m][i] = (unsigned int)m_file->getnbits(k);
				}         
            else {              /* bit_alloc = 3, 5, 9 */
					unsigned int nlevels, c=0;
					
					nlevels = (*alloc)[i][bit_alloc[j][i]].steps;
					k=(*alloc)[i][bit_alloc[j][i]].bits;
					c = (unsigned int)m_file->getnbits(k);
					for (k=0;k<3;k++) {
						sample[j][k][i] = c % nlevels;
						c /= nlevels;
					}
            }
		}
		else {                  /* for no sample transmitted */
			for (k=0;k<3;k++) sample[j][k][i] = 0;
		}
		if(stereo == 2 && i>= jsbound) /* joint stereo : copy L to R */
			for (k=0;k<3;k++) sample[1][k][i] = sample[0][k][i];
	}

	for (i=sblimit;i<SBLIMIT;i++) for (j=0;j<stereo;j++) for (k=0;k<3;k++)
		sample[j][k][i] = 0;
}

void CAudioSequence::audio_data_layer2(frame_params* frame, LPWORD outsamp)
{

	unsigned int bit_alloc[2][32];
	unsigned int scfsi[2][32];
	unsigned int scale_index[2][3][32];

    int topSb = 0;

	decode_bitalloc_layer2(bit_alloc, frame);
	decode_scale_layer2(scfsi, bit_alloc, scale_index, frame);

    int clip = 0;
    for (int i = 0; i < SCALE_BLOCK/*12*/; i++)
	 {
       buffer_sample_layer2((*sample),bit_alloc,frame);

		 if (outsamp)
		 {
			 dequantize_sample_layer2((*sample),bit_alloc,(*fraction),frame);
			 denormalize_sample_layer2((*fraction),scale_index,frame,i>>2);

			 if(topSb>0)        /* debug : clear channels to 0 */
			 {
				 for(int j = topSb; j< frame->sblimit; ++j)
				 {
					 for(int k=0; k < frame->stereo; ++k)
					 {
						 (*fraction)[k][0][j] =
						 (*fraction)[k][1][j] =
						 (*fraction)[k][2][j] = 0;
					 }
				 }
			 }

			 for (int j=0;j<3;j++)
			 {
				 for (int k=0;k < frame->stereo;k++)
				 {
					 clip += SubBandSynthesis (&((*fraction)[k][j][0]), k,
						 &((*pcm_sample)[k][j][0]));
				 }
			 }
				 /*
			 out_fifo(*pcm_sample, 3, &fr_ps, done, musicout,
						 &sample_frames);
						 */

			 int num = 3;
			 {
				  for (int i = 0; i < num; i++)
				  {
					  for (int j = 0; j < SBLIMIT; j++)
					  {
						//(*psampFrames)++;
						for (int l=0;l<frame->stereo;l++)
						{
							/*
							 if (!(k%1600) && k)
							 {
								  fwrite(outsamp,2,1600,outFile);
								  k = 0;
							 }
							 */
							 *outsamp++ = (*pcm_sample)[l][i][j];
						}
					  }
				 }
			 }
		 }
    }
    if(clip > 0) printf("%d samples clipped\n", clip);

	 /*
   int bitsPerSlot = 8;        

	unsigned long samplesPerFrame;

	samplesPerFrame = 1152;

	int sb;
	int ch;
*/

}

void CAudioSequence::audio_data_layer3(frame_params& fr_ps)
{
	ASSERT(0);
#if 0
	int nSlots;
	int gr, ch, ss, sb, main_data_end, flush_main ;
	int  bytes_to_discard ;
	static int frame_start = 0;
	int bitsPerSlot = 8;
	int samplesPerFrame = 1152;
	
	III_get_side_info(m_file, &III_side_info, &fr_ps);
	nSlots = main_data_slots(fr_ps);
	for (; nSlots > 0; nSlots--)  /* read main data. */
		hputbuf((unsigned int) getbits(&bs,8), 8);
	main_data_end = hsstell() / 8; /*of privious frame*/
	if ( flush_main=(hsstell() % bitsPerSlot) ) { 
		hgetbits((int)(bitsPerSlot - flush_main));
		main_data_end ++;
	}
	bytes_to_discard = frame_start - main_data_end
		- III_side_info.main_data_begin ;
	if( main_data_end > 4096 )
	{   frame_start -= 4096;
	rewindNbytes( 4096 );
	}
	
	frame_start += main_data_slots(fr_ps);
	if (bytes_to_discard < 0) {
		printf("Not enough main data to decode frame %d.  Frame discarded.\n", 
			frameNum - 1); break;
	}
	for (; bytes_to_discard > 0; bytes_to_discard--) hgetbits(8);
	
	clip = 0;
	for (gr=0;gr<2;gr++) {
      double lr[2][SBLIMIT][SSLIMIT],ro[2][SBLIMIT][SSLIMIT];
		
      for (ch=0; ch<stereo; ch++) {
			long int is[SBLIMIT][SSLIMIT];   /* Quantized samples. */
			int part2_start;
			part2_start = hsstell();
			III_get_scale_factors(III_scalefac,&III_side_info,gr,ch,
				&fr_ps);
			III_hufman_decode(is, &III_side_info, ch, gr, part2_start,
				&fr_ps);
			III_dequantize_sample(is, ro[ch], III_scalefac,
				&(III_side_info.ch[ch].gr[gr]), ch, &fr_ps);
      }
      III_stereo(ro,lr,III_scalefac,
			&(III_side_info.ch[0].gr[gr]), &fr_ps);
      for (ch=0; ch<stereo; ch++) {
			double re[SBLIMIT][SSLIMIT];
			double hybridIn[SBLIMIT][SSLIMIT];/* Hybrid filter input */
			double hybridOut[SBLIMIT][SSLIMIT];/* Hybrid filter out */
			double polyPhaseIn[SBLIMIT];     /* PolyPhase Input. */
			
			III_reorder (lr[ch],re,&(III_side_info.ch[ch].gr[gr]),
				&fr_ps);
			III_antialias(re, hybridIn, /* Antialias butterflies. */
				&(III_side_info.ch[ch].gr[gr]), &fr_ps);
			for (sb=0; sb<SBLIMIT; sb++) { /* Hybrid synthesis. */
				III_hybrid(hybridIn[sb], hybridOut[sb], sb, ch,
					&(III_side_info.ch[ch].gr[gr]), &fr_ps);
			}
			for (ss=0;ss<18;ss++) /*Frequency inversion for polyphase.*/
				for (sb=0; sb<SBLIMIT; sb++)
					if ((ss%2) && (sb%2))
						hybridOut[sb][ss] = -hybridOut[sb][ss];
					for (ss=0;ss<18;ss++) { /* Polyphase synthesis */
						for (sb=0; sb<SBLIMIT; sb++)
							polyPhaseIn[sb] = hybridOut[sb][ss];
						clip += SubBandSynthesis (polyPhaseIn, ch,
							&((*pcm_sample)[ch][ss][0]));
               }
		}
		/* Output PCM sample points for one granule. */
		out_fifo(*pcm_sample, 18, &fr_ps, done, musicout,
			&sample_frames);
	}
	if(clip > 0) printf("%d samples clipped.\n", clip);
#endif
}

void CAudioSequence::ancillary_data()
{
	/*
	if ((m_layer == 1) || (m_layer = 2))
	{
		int no_of_ancillary_bits = 0;

		for (int i = 0; i < no_of_ancillary_bits; i++)
		{
			m_file->getbit();//ancillary-bit
		}
	}
	*/
}


// ILMediaSeeking
HRESULT CAudioSequence::Seek(LONGLONG t)
{
	return S_OK;
}

HRESULT CAudioSequence::GetDuration(LONGLONG* pVal)
{
	LONGLONG nSamples = GetSamples();

	LPWAVEFORMATEX pwfx = (LPWAVEFORMATEX)m_mt.pbFormat;

	*pVal = LTIME_SCALE * nSamples / pwfx->nSamplesPerSec;

	return S_OK;
}

HRESULT CAudioSequence::GetCurrentPosition(LONGLONG* pVal)
{
	ASSERT(0);
	return S_OK;
}

LONGLONG CAudioSequence::GetSamples()
{
	return m_frames.GetCount()*1152;
}

HRESULT CAudioSequence::GetMediaType(int iPosition, MediaType* pMediaType)
{
	if (iPosition == 0)
	{
		MediaType mediaType;
		mediaType.Create(sizeof(WAVEFORMATEX));

		//memcpy(&((LVIDEOINFOHEADER2*)mediaType->pbFormat)->bmiHeader, m_pBitmapInfoHeader, sizeof(BITMAPINFOHEADER)+m_pBitmapInfoHeader->biClrUsed*sizeof(RGBQUAD));

		mediaType.majortype = LMEDIATYPE_Audio;
		mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

		LPWAVEFORMATEX pwfx = (LPWAVEFORMATEX)mediaType.pbFormat;

		frame_params* frame = (frame_params*)m_frames.GetHead();

		int nChannels = frame->stereo;

		pwfx->wFormatTag = WAVE_FORMAT_PCM;
		pwfx->nChannels = nChannels;
		pwfx->wBitsPerSample = 16;
		pwfx->nBlockAlign = nChannels * 16 / 8;
		ASSERT(0);
#if 0
		pwfx->nSamplesPerSec = s_freq[frame->header->sampling_frequency]*1000;
#endif
		pwfx->nAvgBytesPerSec = pwfx->nSamplesPerSec*pwfx->nBlockAlign;
		pwfx->cbSize = 0;

		*pMediaType = mediaType;

		return S_OK;
	}
	else
	{
	//	pMediaType = NULL;
		return S_FALSE;
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

HRESULT CAudioSequence::ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples)
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

static DWORD WINAPI AudioRunProc(LPVOID lpParameter)
{
	CAudioSequence* p = (CAudioSequence*)(ILPin*)lpParameter;

	ASSERT(0);
#if 0

	HRESULT hr = S_OK;

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

ILBaseFilter* CAudioSequence::QueryFilter() const
{
	return m_pFilter;
}

HRESULT CAudioSequence::Run(LONGLONG tStart)
{
	m_hThread = CreateThread(NULL, NULL, AudioRunProc, (LPVOID)(ILPin*)this, 0, &m_threadId);
	if (m_hThread == NULL)
		return E_FAIL;

	return S_OK;
}

}	// LMedia