#pragma once

#include "LFC/BitStream.h"

namespace System
{
namespace MediaShow
{

//	class CBitStream;

#define         SBLIMIT                 32	// Max sblimit
#define         SSLIMIT                 18

#define         HAN_SIZE                512
#define         SCALE_BLOCK             12
#define         SCALE_RANGE             64
#define         SCALE                   32768
#define         CRC16_POLYNOMIAL        0x8005

/* Structure for Reading Layer II Allocation Tables from File */

#if 0
typedef struct
{
//	unsigned int    steps;
	WORD    bits;
//	unsigned int    group;
//	unsigned int    quant;
	WORD	values[15];
}
sb_alloc, *alloc_ptr;
#endif

/* Structure for Reading Layer II Allocation Tables from File */

typedef struct {
    unsigned int    steps;
    unsigned int    bits;
    unsigned int    group;
    unsigned int    quant;
} sb_alloc, *alloc_ptr;

typedef sb_alloc        al_table[SBLIMIT][16];

//typedef sb_alloc        al_table[SBLIMIT][16];

#define         MAX_U_32_NUM            0xFFFFFFFF
#define         PI                      3.14159265358979
#define         PI4                     PI/4
#define         PI64                    PI/64
#define         LN_TO_LOG10             0.2302585093

#define         VOL_REF_NUM             0
#define         MPEG_AUDIO_ID           1
#define         MAC_WINDOW_SIZE         24

/* MPEG Header Definitions - Mode Values */

#define         MPG_MD_STEREO           0
#define         MPG_MD_JOINT_STEREO     1
#define         MPG_MD_DUAL_CHANNEL     2
#define         MPG_MD_MONO             3

/* Mode Extention */

#define         MPG_MD_LR_LR             0
#define         MPG_MD_LR_I              1
#define         MPG_MD_MS_LR             2
#define         MPG_MD_MS_I              3

typedef short PCM[2][SSLIMIT][SBLIMIT];
typedef unsigned int SAM[2][3][SBLIMIT];
typedef double FRA[2][3][SBLIMIT];
typedef double VE[2][HAN_SIZE];

class layer
{
public:
	uint8	error_protection : 1,//m_protection_bit : 1,
			bitrate_index : 4,
			sampling_frequency : 2,
			mode : 2,
			mode_ext : 2,
			m_copyright : 1,
			m_original : 1,
			padding : 1;

	uint8 m_layer;
};

#if 0
class frame_params
{
public:
	frame_params()
	{
		header = new layer;
	}

	layer* header;
	al_table* alloc;
	int sblimit;
	int jsbound;
	int stereo;

	ULONGLONG m_fileDataBytePos;
	ULONGLONG m_fileDataBitCnt;
};

/* Layer III side information. */

		struct gr_info_s
		{
			unsigned part2_3_length;
			unsigned big_values;
			unsigned global_gain;
			unsigned scalefac_compress;
			unsigned window_switching_flag;
			unsigned block_type;
			unsigned mixed_block_flag;
			unsigned table_select[3];
			unsigned subblock_gain[3];
			unsigned region0_count;
			unsigned region1_count;
			unsigned preflag;
			unsigned scalefac_scale;
			unsigned count1table_select;
			};

typedef struct {
	unsigned main_data_begin;
	unsigned private_bits;
	struct ch_info_s {
	    unsigned scfsi[4];
		gr_info_s gr[2];
		} ch[2];
	} III_side_info_t;

/* Layer III scale factors. */

typedef struct {
	int l[23];            /* [cb] */
	int s[3][13];         /* [window][cb] */
	} III_scalefac_t[2];  /* [ch] */

#endif

#ifndef MPEGAUDIOEXT
#define MPEGAUDIOEXT DECLSPEC_DLLIMPORT
#endif

class MPEGAUDIOEXT MPEGAudioSequence
{
public:

	MPEGAudioSequence();

	System::IO::CBitStream32* m_file;

	void Open(System::IO::ISequentialByteStream* stream);

	// header fields
	unsigned m_layer : 2;
	bool m_protection_bit : 1;
	bool m_padding_bit : 1;
	unsigned m_sampling_frequency : 2;
	unsigned m_bitrate_index : 4;
	unsigned m_mode : 2;

	unsigned long m_N;

	unsigned int m_nchannels;

	void seek_sync();

	class SideInfo_layerIII
	{
	public:
		bool scfsi[2][4];
		uint16 part2_3_length[2][2];
		uint16 big_values[2][2];
		uint8 global_gain[2][2];
		uint8 scalefac_compress[2][2];
		bool window_switching_flag[2][2];
		uint8 block_type[2][2];
		bool mixed_block_flag[2][2];
		uint8 table_select[2][2][3];
		uint8 subblock_gain[2][2][3];
		uint8 regionO_count[2][2];
		uint8 region1_count[2][2];
		bool preflag[2][2];
		bool scalefac_scale[2][2];
		bool countltable_select[2][2];
	};

	void header();
	void error_check();
	void audio_data_layerII(short* outsamp);
	void audio_data_layerIII(short* outsamp);
	void main_data_layerIII(const SideInfo_layerIII& si);
	void HuffmanCodebits(const SideInfo_layerIII& si, int gr, int ch);

	void frame(short* pcmsamples);

};

class MPEGAudioDecoder;

class AudioSequence :
	public BaseOutputPinImpl,
	public IMediaSeeking
{
public:
	AudioSequence();

	//LONGLONG m_nSamples;

	MPEGAudioSequence* m_mpeg_audio;

#if 0
	CUPtrList m_frames;//	frame_params frame;

	PCM FAR *pcm_sample;
	SAM FAR *sample;
	FRA FAR *fraction;
	VE FAR *w;

	III_side_info_t III_side_info;
#endif

	//DWORD m_threadId;
	HANDLE m_hThread;

	ErrorCode audio_sequence();

	//BOOL seek_sync();

	//	void frame_layer_I();
//	void frame_layer_II_III();

#if 0
	void frame();
	void header(frame_params *fr_ps);
	void error_check(frame_params* frame);

	void audio_data_layer1();
	void audio_data_layer2(frame_params* frame, LPWORD outsamp);
	void audio_data_layer3(frame_params& fr_ps);

	void ancillary_data();

	void decode_bitalloc_layer2(unsigned int bit_alloc[2][SBLIMIT], frame_params *fr_ps);
	void decode_scale_layer2(
		unsigned int scfsi[2][SBLIMIT],
		unsigned int bit_alloc[2][SBLIMIT],
		unsigned int scale_index[2][3][SBLIMIT],
		frame_params *fr_ps);

	void buffer_sample_layer2(
		unsigned int FAR sample[2][3][SBLIMIT],
		unsigned int bit_alloc[2][SBLIMIT],
		frame_params *fr_ps);

#endif

#if 0
	LONGLONG GetSamples();
	//STDMETHOD(GetFormat)(WAVEFORMATEX *pVal);
	//STDMETHOD(GetChunkSize)(long nchunk, ULONG* pVal);
	ErrorCode ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples);
#endif

	virtual ErrorCode CheckMediaType(MediaType* mt)
	{
		if (mt->GetMajorType() != LMEDIATYPE_Audio)
			return Error;

		return Success;
	}

	virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);
	//virtual ErrorCode Run(LONGLONG tStart);

	virtual ErrorCode Pause();

	inline MPEGAudioDecoder* GetFilter() const
	{
		return (MPEGAudioDecoder*)m_pFilter;
	}

// IMediaSeeking
	ErrorCode Seek(TimeUnit unit, LONGLONG t);
	ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);
	ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal);
};

}	// MediaShow
}	// System
