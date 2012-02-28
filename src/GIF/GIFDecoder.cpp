#include "stdafx.h"
#include "GIF.h"
#include "GIFDecoder.h"

namespace System
{
namespace MediaShow
{


#if 0
typedef struct tagGIFCONTEXT
{
	GIFFILEHEADER		gfh;     // Gif file header
	GIFSCREENDESCR		gsd;		// Logical screen description
	int numColors;
	GIFCOLORTRIPLET	*globalColors;

	unsigned char code_buf[256+4];		/* current input data block */
	int last_byte;		/* # of bytes in code_buf */
	int last_bit;			/* # of bits in code_buf */
	int cur_bit;			/* next bit index to read */
	BOOL	out_of_blocks;	/* TRUE if hit terminator data block */

	char input_code_size;		/* codesize given in GIF file */
	int clear_code,end_code;	/* values for Clear and End codes */

	int code_size;		/* current actual code size */
	int limit_code;		/* 2^code_size */
	int max_code;	  	/* first unused code value */
	BOOL first_time;  	/* flags first call to LZWReadByte */

/* Private state for LZWReadByte */
	int oldcode;			/* previous LZW symbol */
	int firstcode;		/* first byte of oldcode's expansion */

/* LZW symbol table and expansion stack */

	WORD	*symbol_head;	// => table of prefix symbols
	BYTE	*symbol_tail;	// => table of suffix bytes
	BYTE	*symbol_stack;	// => stack for symbol expansions
	BYTE	*sp;		// stack pointer
}
GIFCONTEXT;
#endif



#if 0
/* (Re)initialize LZW state; shared code for startup and Clear processing */
void CGIFDecoder::ReInitLZW()
{
  m_code_size = m_input_code_size + 1;
  m_limit_code = m_clear_code << 1;	/* 2^code_size */
  m_max_code = m_clear_code + 2;	/* first unused code value */
  m_sp = m_symbol_stack;		/* init stack to empty */
}

/* Initialize for a series of LZWReadByte (and hence GetCode) calls */
void CGIFDecoder::InitLZWCode()
{
/* GetCode initialization */
  m_last_byte = 2;		/* make safe to "recopy last two bytes" */
  m_last_bit = 0;		/* nothing in the buffer */
  m_cur_bit = 0;		/* force buffer load on first call */
  m_out_of_blocks = FALSE;

/* LZWReadByte initialization: */
/* compute special code values (note that these do not change later) */
  m_clear_code = 1 << m_input_code_size;
  m_end_code = m_clear_code + 1;
  m_first_time = TRUE;

  ReInitLZW();
}

int CGIFDecoder::GetCode()
/* Fetch the next code_size bits from the GIF data */
/* We assume code_size is less than 16 */
{
  register long accum;
  int offs, ret, count;

  while ( (m_cur_bit + m_code_size) > m_last_bit)
  {
 /* Time to reload the buffer */
	 if (m_out_of_blocks)
	 {
		return m_end_code;	/* fake something useful */
	 }

 /* preserve last two bytes of what we have -- assume code_size <= 16 */
	 m_code_buf[0] = m_code_buf[m_last_byte-2];
	 m_code_buf[1] = m_code_buf[m_last_byte-1];

	 /* Load more bytes; set flag if we reach the terminator block */
	 if ((count = GetDataBlock(&m_code_buf[2])) == 0)
	 {
		m_out_of_blocks = TRUE;
		return m_end_code;	/* fake something useful */
	 }

	 /* Reset counters */
	 m_cur_bit = (m_cur_bit - m_last_bit) + 16;
	 m_last_byte = 2 + count;
	 m_last_bit = m_last_byte * 8;
  }

  /* Form up next 24 bits in accum */
  offs = m_cur_bit >> 3;	/* byte containing cur_bit */

  accum = m_code_buf[offs+2];
  accum <<= 8;
  accum |= m_code_buf[offs+1];
  accum <<= 8;
  accum |= m_code_buf[offs];

 /* Right-align cur_bit in accum, then mask off desired number of bits */
  accum >>= (m_cur_bit & 7);
  ret = ((int) accum) & ((1 << m_code_size) - 1);

  m_cur_bit += m_code_size;

  return ret;
}

#define LZW_ERROR	-1//0xffff

int CGIFDecoder::LZWReadByte()
/* Read an LZW-compressed byte */
{
//	GIFCONTEXT* gif = (GIFCONTEXT*)r->UserPtr;
//	ASSERT(gif);

	register int code;		/* current working code */
  int incode;			/* saves actual input code */

// First time, just eat the expected Clear code(s) and return next code, */
// which is expected to be a raw byte. */
  if (m_first_time)
  {
	 m_first_time = FALSE;
	 code = m_clear_code;	/* enables sharing code with Clear case */
  }
  else
  {
	 /* If any codes are stacked from a previously read symbol, return them */
	 if (m_sp > m_symbol_stack)
		return (int) *(-- m_sp);

	 /* Time to read a new symbol */
	 code = GetCode();
  }

	if (code == m_clear_code)
	{
	 /* Reinit state, swallow any extra Clear codes, and */
	 /* return next code, which is expected to be a raw byte. */
		ReInitLZW();

		do
		{
			code = GetCode();
		}
		while (code == m_clear_code);

		if (code > m_clear_code) /* make sure it is a raw byte */
		{
			return LZW_ERROR;
//			code = 0;			/* use something valid */
		}

	 /* make firstcode, oldcode valid! */
		m_firstcode = m_oldcode = code;
		return code;
	}

  if (code == m_end_code)
  {
	 /* Skip the rest of the image, unless GetCode already read terminator */
	 if (!m_out_of_blocks)
	 {
		SkipDataBlocks();
		m_out_of_blocks = TRUE;
	 }
	 /* Complain that there's not enough data */

		return LZW_ERROR;
	 /* Pad data with 0's */
//	 return 0;			/* fake something usable */
	}

  /* Got normal raw byte or LZW symbol */
  incode = code;		/* save for a moment */

  if (code >= m_max_code) { /* special case for not-yet-defined symbol */
	 /* code == max_code is OK; anything bigger is bad data */
	 if (code > m_max_code)
	 {
		return LZW_ERROR;
		incode = 0;		/* prevent creation of loops in symbol table */
	 }
	 /* this symbol will be defined as oldcode/firstcode */
	 *(m_sp++) = (BYTE) m_firstcode;
	 code = m_oldcode;
  }

  /* If it's a symbol, expand it into the stack */
  while (code >= m_clear_code)
  {
	 *(m_sp++) = m_symbol_tail[code]; /* tail is a byte value */
	 code = m_symbol_head[code]; /* head is another LZW symbol */
  }
  /* At this point code just represents a raw byte */
  m_firstcode = code;	/* save for possible future use */

  /* If there's room in table, */
  if ((code = m_max_code) < LZW_TABLE_SIZE)
  {
	 /* Define a new symbol = prev sym + head of this sym's expansion */
	 m_symbol_head[code] = m_oldcode;
	 m_symbol_tail[code] = (BYTE) m_firstcode;
	 m_max_code++;

 /* Is it time to increase code_size? */
	 if ((m_max_code >= m_limit_code) && (m_code_size < MAX_LZW_BITS))
	{
		m_code_size++;
		m_limit_code <<= 1;	/* keep equal to 2^code_size */
	 }
  }

  m_oldcode = incode;	/* save last input symbol for future use */

  return m_firstcode;	/* return first byte of symbol's expansion */
}
#endif

///////////////////////////////////////////////////////////////////////////////////
//

CGIFDecoder::~CGIFDecoder()
{
	Disconnect();
}

ErrorCode CGIFDecoder::CInputPin::CompleteConnect(IPin* pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

	return GetFilter()->Open();
}

ErrorCode CGIFDecoder::Disconnect()
{
#if 0	// Have this
	if (m_globalColors) GlobalFree(m_globalColors);
//	m_sample = NULL;
#endif

	/*
	if (m_symbol_head) GlobalFree(m_symbol_head);
	if (m_symbol_tail) GlobalFree(m_symbol_tail);
	if (m_symbol_stack) GlobalFree(m_symbol_stack);
	*/

	m_stream = NULL;

	return Success;
}

ErrorCode CGIFDecoder::Open()
{
	m_gifFile = new Imaging::GIFFormat;
	ErrorCode hr = m_gifFile->Open(m_stream);
	if (hr == 0)
	{
		while (m_gifFile->AddNextFrame() == 0)
		{
		}

		m_rowbytes = m_gifFile->GetWidth()*3;
		m_imageBits = new uint8[m_rowbytes * m_gifFile->GetHeight()];
	}
	return hr;
}

ErrorCode CGIFDecoder::Seek(long frame)
{
	ASSERT(0);
#if 0
	if (frame != m_currentFrame)
	{
		long from, to;

		if (frame > m_currentFrame)
		{
			from = m_currentFrame+1;
			to = frame;
		}
		else
		{
			from = 0;
			to = frame;
		}

		UPOSITION pos = m_gifFile->m_frames.FindIndex(from);

		for (int i = from; i <= to; i++)
		{
			GIFFrame* pFrame = (GIFFrame*)m_gifFile->m_frames.GetNext(pos);

			m_stream->Seek(pFrame->m_fileOffset, System::IO::STREAM_SEEK_SET);

			m_gifFile->DecodeImage(pFrame, m_imageBits, m_rowbytes, 24, true);
		}

		m_currentFrame = frame;

		{
			IMediaSample* sample;
			m_pImages->m_pAllocator->GetBuffer(0, &sample);

			LSampleData sampledata;
			sample->LockBits(&sampledata);

			int width = m_gifFile->GetWidth();
			int height = m_gifFile->GetHeight();

			for (int y = 0; y < height; y++)
			{
				uint8* dest = sampledata.idata + sampledata.rowbytes*y;
				uint8* src = m_imageBits + m_rowbytes*y;

				for (int x = 0; x < width; x++)
				{
					dest[0] = src[0];
					dest[1] = src[1];
					dest[2] = src[2];

					dest += 3;
					src += 3;
				}
			}
			sample->UnlockBits();

			m_pImages->m_pInputPin->Receive(sample);
			sample->Release();
		}
	}
#endif
	return 0;
}

// IMediaSeeking
ErrorCode CGIFDecoder::CImages::Seek(TimeUnit unit, LONGLONG t)
{
	ASSERT(0);
#if 0
	long nframe = 0;

	if (unit == TimeFormat_ref)
	{
	// Find the frame to seek to
		ULONG delaytime = 0;

		UPOSITION pos = GetFilter()->m_gifFile->m_frames.GetHeadPosition();
		while (pos)
		{
			GIFFrame* pFrame = (GIFFrame*)GetFilter()->m_gifFile->m_frames.GetNext(pos);

			if (pos == NULL) break;

			delaytime += pFrame->gctrl.DelayTime;
			LONGLONG s = LTIME_SCALE/100 * delaytime;

			if (s >= t)
				break;

			nframe++;
		}
	}
	else if (unit == TimeFormat_frame)
	{
		nframe = t;
	}

//	if (nframe != m_currentFrame)
	{
		GetFilter()->Seek(nframe);
	}
#endif
	return Success;
}

ErrorCode CGIFDecoder::CImages::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
	ASSERT(0);
#if 0
	if (unit == TimeFormat_ref)
	{
		if (pVal == NULL) return E_POINTER;

		ULONG delay = 0;

		UPOSITION pos = GetFilter()->m_gifFile->m_frames.GetHeadPosition();
		while (pos)
		{
			GIFFrame* pFrame = (GIFFrame*)GetFilter()->m_gifFile->m_frames.GetNext(pos);

			delay += pFrame->gctrl.DelayTime;
		}

		*pVal = LTIME_SCALE/100 * delay;
		return S_OK;
	}
	else if (unit == TimeFormat_frame)
	{
		*pVal = GetFilter()->m_gifFile->m_frames.GetCount();
		return S_OK;
	}
	else
#endif
	{
		return Error;
	}
}

static MSWindows::DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
	ErrorCode hr;

	ASSERT(0);
#if 0
	CGIFDecoder::CImages* p = (CGIFDecoder::CImages*)lpParameter;

	UPOSITION pos = p->GetFilter()->m_gifFile->m_frames.GetHeadPosition();
	while (pos)
	{
		GIFFrame* pFrame = (GIFFrame*)p->GetFilter()->m_gifFile->m_frames.GetNext(pos);

		IMediaSample* sample;
		p->m_pAllocator->GetBuffer(0, &sample);
		if (sample)
		{
			p->GetFilter()->m_stream->Seek(pFrame->m_fileOffset, System::IO::STREAM_SEEK_SET);

			LONGLONG tStart = 0;
			LONGLONG tEnd = 0;

			sample->SetTime(&tStart, &tEnd);
			//p->GetFilter()->m_gifFile->m_sample = sample;
	//		ASSERT(0);
#if 0
			p->GetFilter()->m_gifFile->DecodeImage(pFrame, m_imageBits, m_rowbytes, 24, true);
#endif
			{
				LSampleData sampledata;
				sample->LockBits(&sampledata);

				int width = p->GetFilter()->m_gifFile->GetWidth();
				int height = p->GetFilter()->m_gifFile->GetHeight();

				for (int y = 0; y < height; y++)
				{
					uint8* dest = sampledata.idata + sampledata.rowbytes*y;
					uint8* src = p->GetFilter()->m_imageBits + p->GetFilter()->m_rowbytes*y;

					for (int x = 0; x < width; x++)
					{
						dest[0] = src[0];
						dest[1] = src[1];
						dest[2] = src[2];

						dest += 3;
						src += 3;
					}
				}
				sample->UnlockBits();
			}

	#if 0
			p->m_pImage->ReadImage(sample);
	#endif

			p->m_pInputPin->Receive(sample);

			sample->Release();
		}

		p->ConnectedTo()->EndOfStream();
	}
#endif
	return 0;
}

ErrorCode CGIFDecoder::CImages::Run(LONGLONG tStart)
{
	m_pFilter->m_tStart = tStart;

	MSWindows::DWORD threadId;
	ASSERT(0);
#if 0
	/*m_hThread =*/ MSWindows::CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(CGIFDecoder::CImages*)this, 0, &threadId);
#endif

	return 0;
}

}	// Media
}
