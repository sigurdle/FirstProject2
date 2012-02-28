// IFFDecoder.cpp : Implementation of CIFFDecoder
#include "stdafx.h"
#include "IFF.h"
//#include "IFFDecoder.h"

#include "IFFFormAIFF.h"

namespace System
{
namespace MediaShow
{

/* Double and SANE Floating Point Type Definitions */

#pragma pack(push,1)

typedef struct  IEEE_DBL_struct {
    unsigned long   hi;
    unsigned long   lo;
} IEEE_DBL;

#if 1

// original
typedef struct  SANE_EXT_struct {
    unsigned long   l1;
    unsigned long   l2;
    unsigned short  s1;
} SANE_EXT;
#else
typedef struct  SANE_EXT_struct {
    unsigned short  s1;
    unsigned long   l2;
    unsigned long   l1;
} SANE_EXT;
#endif

#pragma pack(pop)

/****************************************************************************
*
*  Routines to convert between the Apple SANE extended floating point format
*  and the IEEE double precision floating point format.  These routines are
*  called from within the Audio Interchange File Format (AIFF) routines.
*
*****************************************************************************/

/*
*** Apple's 80-bit SANE extended has the following format:

 1       15      1            63
+-+-------------+-+-----------------------------+
|s|       e     |i|            f                |
+-+-------------+-+-----------------------------+
  msb        lsb   msb                       lsb

The value v of the number is determined by these fields as follows:
If 0 <= e < 32767,              then v = (-1)^s * 2^(e-16383) * (i.f).
If e == 32767 and f == 0,       then v = (-1)^s * (infinity), regardless of i.
If e == 32767 and f != 0,       then v is a NaN, regardless of i.

*** IEEE Draft Standard 754 Double Precision has the following format:

MSB
+-+---------+-----------------------------+
|1| 11 Bits |           52 Bits           |
+-+---------+-----------------------------+
 ^     ^                ^
 |     |                |
 Sign  Exponent         Mantissa
*/

/*****************************************************************************
*
*  double_to_extended()
*
*  Purpose:     Convert from IEEE double precision format to SANE extended
*               format.
*
*  Passed:      Pointer to the double precision number and a pointer to what
*               will hold the Apple SANE extended format value.
*
*  Outputs:     The SANE extended format pointer will be filled with the
*               converted value.
*
*  Returned:    Nothing.
*
*****************************************************************************/

void double_to_extended(double  *pd, char    ps[10])
{

#ifdef  MACINTOSH

        x96tox80(pd, (extended *) ps);

#else

register unsigned long  top2bits;

register unsigned short *ps2;
register IEEE_DBL       *p_dbl;
register SANE_EXT       *p_ext;
 
   p_dbl = (IEEE_DBL *) pd;
   p_ext = (SANE_EXT *) ps;
   top2bits = p_dbl->hi & 0xc0000000;
   p_ext->l1 = ((p_dbl->hi >> 4) & 0x3ff0000) | top2bits;
   p_ext->l1 |= ((p_dbl->hi >> 5) & 0x7fff) | 0x8000;
   p_ext->l2 = (p_dbl->hi << 27) & 0xf8000000;
   p_ext->l2 |= ((p_dbl->lo >> 5) & 0x07ffffff);
   ps2 = (unsigned short *) & (p_dbl->lo);
   ps2++;
   p_ext->s1 = (*ps2 << 11) & 0xf800;

#endif

}

/*****************************************************************************
*
*  extended_to_double()
*
*  Purpose:     Convert from SANE extended format to IEEE double precision
*               format.
*
*  Passed:      Pointer to the Apple SANE extended format value and a pointer
*               to what will hold the the IEEE double precision number.
*
*  Outputs:     The IEEE double precision format pointer will be filled with
*               the converted value.
*
*  Returned:    Nothing.
*
*****************************************************************************/

void extended_to_double(char    ps[10], double  *pd)
{

#ifdef  MACINTOSH

   x80tox96((extended *) ps, pd);

#else

register unsigned long  top2bits;

register IEEE_DBL       *p_dbl;
register SANE_EXT       *p_ext;

   p_dbl = (IEEE_DBL *) pd;
   p_ext = (SANE_EXT *) ps;

#if 0
	p_ext->l1 = BigEndian32(p_ext->l1);
	p_ext->l2 = BigEndian32(p_ext->l2);
	p_ext->s1 = BigEndian16(p_ext->s1);
#endif

   top2bits = p_ext->l1 & 0xc0000000;
   p_dbl->hi = ((p_ext->l1 << 4) & 0x3ff00000) | top2bits;
   p_dbl->hi |= (p_ext->l1 << 5) & 0xffff0;
   p_dbl->hi |= (p_ext->l2 >> 27) & 0x1f;
   p_dbl->lo = (p_ext->l2 << 5) & 0xffffffe0;
   p_dbl->lo |= (unsigned long) ((p_ext->s1 >> 11) & 0x1f);

#if 0
	p_dbl->lo = BigEndian32(p_dbl->lo);
	p_dbl->hi = BigEndian32(p_dbl->hi);
#endif

#endif

}

/* *************************** FlipLong() ******************************
 * Converts a long in "Big Endian" format (ie, Motorola 68000) to Intel
 * reverse-byte format, or vice versa if originally in Big Endian.
 ********************************************************************* */

void FlipLong(unsigned char * ptr)
{
   register unsigned char val;

   /* Swap 1st and 4th bytes */
   val = *(ptr);
   *(ptr) = *(ptr+3);
   *(ptr+3) = val;

   /* Swap 2nd and 3rd bytes */
   ptr += 1;
   val = *(ptr);
   *(ptr) = *(ptr+1);
   *(ptr+1) = val;
}

/* ************************* FetchLong() *******************************
 * Fools the compiler into fetching a long from a char array.
 ********************************************************************* */

unsigned long FetchLong(unsigned long * ptr)
{
   return(*ptr);
}


/* ************************* ConvertFloat() *****************************
 * Converts an 80 bit IEEE Standard 754 floating point number to an unsigned
 * long.
 ********************************************************************** */

unsigned long ConvertFloat(unsigned char * buffer)
{
   unsigned long mantissa;
   unsigned long last = 0;
   unsigned char exp;

#if WIN32	//INTEL_CPU
   FlipLong((unsigned char*)(unsigned long *)(buffer+2));
#endif

   mantissa = FetchLong((unsigned long *)(buffer+2));
   exp = 30 - *(buffer+1);
   while (exp--)
   {
     last = mantissa;
     mantissa >>= 1;
   }
   if (last & 0x00000001) mantissa++;
   return(mantissa);
}

////////////////////////////////////////////
// IFFFormAIFF

IFFFormAIFF::IFFFormAIFF()
{
	m_pInputPin = NULL;

	m_bodyPos = 0;
	m_bodySize = 0;

	m_nSamples = 0;
	m_sampleRate = 0;

	m_pInputPin = new CInputPin;
	m_pInputPin->m_pFilter = this;
}

IFFRESULT IFFFormAIFF::ReadAIFFForm()
{
	IFFRESULT	iffresult;

	IFFCHUNK	ck;

	while (m_pInputPin->m_pIFFParser->IFFDescendChunk(&ck) == IFF_OK)
	{
		switch (ck.ckID)
		{
			case ID_COMM:
			{
				CommonHeader *comm = &m_comm;

				if ((iffresult = m_pInputPin->m_pIFFParser->IFFReadChunkBytes(comm, sizeof(CommonHeader))) == sizeof(CommonHeader))
				{
					comm->numChannels = BigEndian16(comm->numChannels);
					comm->numSampleFrames = BigEndian32(comm->numSampleFrames);
					comm->sampleSize = BigEndian16(comm->sampleSize);
					//comm->sampleRate = ENDIANEXTENDED(comm->sampleRate);

					
					/*
				// convert 80bit long double to 64bit double
					char* e10 = comm->sampleRate.v;
					long double Newdbl;
					_asm {
						fld TBYTE PTR e10;
						fstp Newdbl;
					}

					m_sampleRate = Newdbl;
					*/
	
				//	*(unsigned long *)(comm->sampleRate.v+2) = BigEndian32(*(unsigned long *)(comm->sampleRate.v+2));
					//FlipLong((unsigned long *)(buffer+2));

				//	extended_to_double(comm->sampleRate.v, &m_sampleRate);

					m_sampleRate = ConvertFloat((unsigned char*)comm->sampleRate.v);

					if (comm->numChannels > 2)
						iffresult = Error;

					if ((comm->sampleSize != 8) && (comm->sampleSize != 16))
						iffresult = Error;
				}
				else iffresult = IFFERR_READWRITE;
			}
			break;

			case ID_SSND:
			{
				if ((iffresult = m_pInputPin->m_pIFFParser->IFFReadChunkBytes(&m_ssnd, sizeof(SoundDataChunk))) == sizeof(SoundDataChunk))
				{
					m_ssnd.offset = BigEndian32(m_ssnd.offset);
					m_ssnd.blockSize = BigEndian32(m_ssnd.blockSize);

					//m_nSamples = ck.ckSize;

					//	m_svxOffset = g->GetFilePos(g->file);

				// TODO, also look at blockAlign
					int nbytesPerSample = m_comm.numChannels * m_comm.sampleSize / 8;

					ULONGLONG pos;
					pos = m_pInputPin->m_pIFFParser->SetFilePos(0, System::IO::STREAM_SEEK_CUR);

					ULONG count = 0;
					while (count < m_comm.numSampleFrames)
					{
						CAudioChunk* pChunk = new CAudioChunk;

						pChunk->m_soundDataOffset = m_ssnd.offset + pos + count*nbytesPerSample;

						pChunk->m_nSamples = 2000;
						if (count+pChunk->m_nSamples > m_comm.numSampleFrames)
							pChunk->m_nSamples = m_comm.numSampleFrames - count;

						count += pChunk->m_nSamples;

						m_chunks.push_back(pChunk);
					}
				}

			}
			break;
		}

		if (iffresult < 0) break;

		iffresult = m_pInputPin->m_pIFFParser->IFFAscendChunk(&ck);
	}

	return iffresult;
}

ErrorCode IFFFormAIFF::Parse()
{
	IFFRESULT iffresult = ReadAIFFForm();
	//if (iffresult 
	return Success;
}

#if 0
STDMETHODIMP IFFFormAIFF::GetDuration(double* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = (double)m_comm.numSampleFrames / m_sampleRate;
	return Success;
}

STDMETHODIMP IFFFormAIFF::Seek(double seconds)
{
	return Success;
}
#endif

int IFFFormAIFF::GetSamples(LONGLONG *pVal)
{
	if (pVal == NULL) return Error_NullPointerArgument;
	*pVal = m_comm.numSampleFrames;
	return Success;
}

int IFFFormAIFF::GetFormat(MSWindows::WAVEFORMATEX *pVal)
{
	if (pVal == NULL) return Error_NullPointerArgument;

	pVal->wFormatTag = WAVE_FORMAT_PCM;
	pVal->nChannels = m_comm.numChannels;
	pVal->wBitsPerSample = m_comm.sampleSize;
	pVal->nSamplesPerSec = m_sampleRate;
	pVal->nBlockAlign = m_comm.numChannels * m_comm.sampleSize / 8;
	pVal->cbSize = 0;

	return Success;
}

int IFFFormAIFF::GetChunkSize(long nchunk, ULONG* pVal)
{
	ASSERT(0);
#if 0
	if (nchunk < m_chunks.size())
	{
		CAudioChunk* pChunk = (CAudioChunk*)m_chunks.GetAt(m_chunks.FindIndex(nchunk));

	// Number of samples in chunk
		*pVal = pChunk->m_nSamples;

		return Success;
	}
	else
#endif
		return Success_False;
}

int IFFFormAIFF::ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples)
{
	ASSERT(0);
#if 0
	if (nchunk < m_chunks.GetCount())
	{
		CAudioChunk* pChunk = (CAudioChunk*)m_chunks.GetAt(m_chunks.FindIndex(nchunk));

		m_pInputPin->m_pIFFParser->SetFilePos(pChunk->m_soundDataOffset, System::IO::STREAM_SEEK_SET);

		int nBlockAlign = m_comm.numChannels * m_comm.sampleSize / 8;

		DWORD nbytes = nsamples*nBlockAlign;
		m_pInputPin->m_pIFFParser->IFFReadChunkBytes(buffer, nbytes);

		ULONG len = nsamples*m_comm.numChannels;

		if (m_comm.sampleSize <= 8)
		{
		// Make unsigned
			char *p = (char*)buffer;
			//int len = nbytes;

			while (len--)
			{
				*p = *p + 128;
				p++;
			}
		}
		else if (m_comm.sampleSize <= 16)
		{
			short	*p = (short*)buffer;
			//int len = 

			while (len--)
			{
				*p = BigEndian16(*p);
				p++;
			}
		}
	}
#endif
	return Success;
}

}	// MediaShow
}
