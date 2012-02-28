#ifndef __VOCFMT_H_
#define __VOCFMT_H_

namespace System
{
namespace MediaShow
{

#pragma pack(push, 1)

struct VOCHEADER
{
	char signature[19];
	uint8 eof;
	uint16 offset;
	uint16 version;
	uint16 version2;
};

enum BlockType : unsigned char
{
	VOC_Sound_Data = 1,
	VOC_Sound_continue = 2,
	VOC_Silence = 3,
	VOC_Extended_Sound_data = 9,
};

class DATABLOCK
{
public:
	int Read(IO::Stream* stream);

	unsigned int size;
	BlockType type;
	/*
	unsigned long	type : 8,
						size : 24;
						*/
};

struct SOUNDBLOCK1
{
	uint8 sampleRate;
	uint8 compression;
};

struct SOUNDBLOCK9
{
	uint16 sampleRate;
	uint16 pad;
	uint8 bits;
	uint8 channels;
	uint8 compression;	// PCM=4, ALaw=6, uLaw=7
	uint8 reserved[5];
};

/*
TYPE: 09
SIZE: 12 + length of data
INFO: 12 (twelve) bytes
  
INFO STRUCTURE:
  
Bytes 0-1: (Word) Sample Rate (e.g. 44100)
Bytes 2-3: zero (could be that bytes 0-3 are a DWord for Sample Rate)
Byte 4: Sample Size in bits (e.g. 16)
Byte 5: Number of channels (e.g. 1 for mono, 2 for stereo)
Byte 6: Unknown (equal to 4 in all files I examined)
Bytes 7-11: zero
*/
#pragma pack(pop)

}	// Media
}

#endif // __VOCFMT_H_
