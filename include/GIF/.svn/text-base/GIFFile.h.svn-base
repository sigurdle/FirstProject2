#ifndef __GIFFILE_H
#define __GIFFILE_H

#include "giffmt.h"
#include "LMedia/LZWDecoder.h"

namespace System
{
namespace Imaging
{

class GifExt GIFFrame : public Object
{
public:
	CTOR GIFFrame()
	{
		m_fileOffset = 0;
		memset(&gctrl, 0, sizeof(GIFCONTROL));
	}

	GIFIMAGEDESCR	gid;		// Logical image description
	GIFCONTROL		gctrl;	// Graphic control extension
//	WORD	transparentColor;

	uint m_fileOffset;

	int pass2_offset;
	int pass3_offset;
	int pass4_offset;
};

class GifExt GIFDecoder : public Object
{
public:
	CTOR GIFDecoder();

	static ErrorCode ReadMarker(IO::Stream* stream);

	int Open(IO::Stream* stream);

	int GetWidth() const;
	int GetHeight() const;

	int AddNextFrame();
	int DecodeImage(GIFFrame* pFrame, uint8* bits, int rowbytes, int bitcount, bool bReadData);

	int StartScan(GIFFrame* pFrame);

	int GetActualRow(GIFFrame* pFrame, int row);
	int ReadScanline(GIFFrame* pFrame, uint8* idata, int bitcount);
	int GetPixelRows(uint8* bits, int rowbytes, int bitcount, const GIFSCREENDESCR *gsd, const GIFIMAGEDESCR *gid, const GIFCONTROL *gctrl, const GIFCOLORTRIPLET* colorTable, bool bReadData);

public:	// TODO protected

	GIFFILEHEADER m_gfh;     // Gif file header
	GIFSCREENDESCR m_gsd;		// Logical screen description
	int m_numColors;
	GIFCOLORTRIPLET	*m_globalColors;
	vector<GIFFrame*> m_frames;
	int row;
	GIFCOLORTRIPLET* colorTable;

protected:

	_Ptr<IO::Stream> m_stream;

	char m_input_code_size;		/* codesize given in GIF file */

	unsigned char m_code_buf[256+4];		/* current input data block */
	unsigned char m_code_len;
	unsigned char m_code_offset;

	class Stream : public IO::Stream
	{
	public:

		void ReadByte(ubyte* pv);

		virtual size_t Read(void* pv, size_t cb) override;

		virtual size_t Write(const void* pv, size_t cb) override
		{
			return 0;
		}

		virtual uint64 Seek(int64 move, IO::SeekOrigin origin) override
		{
			return 0;
		}

		virtual uint64 GetSize() override
		{
			return 0;
		}

		GIFDecoder* m_p;
	};

	_Ptr<Stream> m_lzwstream;
	LZWDecoder<0>* m_LZWDecoder;

	uint8 GetDataBlock(ubyte* buf);
	void SkipDataBlocks();

	int LZWReadByte();

	friend class Stream;
};

}	// Imaging
}	// System

#endif	// __GIFFILE_H
