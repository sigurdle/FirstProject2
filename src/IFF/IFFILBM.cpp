#include "stdafx.h"
#include "IFF.h"
#include "IFFILBM.h"

namespace System
{
namespace MediaShow
{

bool UnpackRowByteRun1(char** pSource, char** pDest, /*WORD srcBytes,*/ int dstBytes);
void PlanarToChunkyScanline(uint8* bits, uint8 bitcount, int width, uint8* planes[], uint8 nplanes, uint32 camg, ColorRegister *colors);

IFFRESULT CIFFILBM::BMHDChunk(IFFCHUNK* ck)
{
	TRACE("BMHD\n");

	IFFRESULT iffresult;

	BitMapHeader *bmhd = &m_bmhd;

	if (ck->ckSize != sizeof(BitMapHeader))
	{
		return IFFERR_CORRUPTED;
	}

	if ((iffresult = m_pIFFParser->IFFReadChunkBytes(bmhd, sizeof(BitMapHeader))) == sizeof(BitMapHeader))
	{
		bmhd->bmh_Width = BigEndian16(bmhd->bmh_Width);
		bmhd->bmh_Height = BigEndian16(bmhd->bmh_Height);
		bmhd->bmh_Left = BigEndian16(bmhd->bmh_Left);
		bmhd->bmh_Top = BigEndian16(bmhd->bmh_Top);
		bmhd->bmh_TransparentColor = BigEndian16(bmhd->bmh_TransparentColor);
		bmhd->bmh_PageWidth = BigEndian16(bmhd->bmh_PageWidth);
		bmhd->bmh_PageHeight = BigEndian16(bmhd->bmh_PageHeight);

		m_planeSize = RowBytes(bmhd->bmh_Width)*bmhd->bmh_Height;

#if 0
		if (m_currentFrame == 0)	// We've already read the first frame
		{
			sprintf(g->szVideoInfo, "%d planes ", bmhd->bmh_Planes);
		}
#endif
	}
	else
		return IFFERR_READWRITE;
/*
}
else
{
	if (bmhd->bmh_Masking == mskHasTransparentColor)
	{
#if 0
		transparentColor = bmhd->bmh_TransparentColor;
#endif
	}
	*/

	return IFF_OK;
}

IFFRESULT CIFFILBM::CAMGChunk(IFFCHUNK* ck)
{
	if ((m_pIFFParser->IFFReadChunkBytes(&m_camg, sizeof(m_camg))) == sizeof(m_camg))
	{
		m_camg = BigEndian32(m_camg);
	}
	else
		return IFFERR_READWRITE;

	return IFF_OK;
}

IFFRESULT CIFFILBM::CMAPChunk(IFFCHUNK* ck)
{
	if (m_pIFFParser->IFFReadChunkBytes(m_colors, ck->ckSize) != ck->ckSize)
		return IFFERR_READWRITE;

	return IFF_OK;
}

IFFRESULT CIFFILBM::BODYChunk(IFFCHUNK* ck)
{
//	IFFRESULT iffresult;

	uint32 camg = m_camg;
	BitMapHeader* bmhd = &m_bmhd;

//	SHORT	imode;
	uint16 numcolors;

	/*
	if (m_PBM)
	{
		ASSERT(0);
		//imode = IMODE_INDEXED8;
		//numcolors = 1<<bmhd->bmh_Planes;
	}
	else
	*/
	{
		if (camg & AMIGA_HAM)
			numcolors = 0;
		else if (bmhd->bmh_Planes == 24)
			numcolors = 0;
		else if (camg & AMIGA_EHB)
			numcolors = 32;
		else
			numcolors = 1<<bmhd->bmh_Planes;

#if 0
		if (camg & AMIGA_HAM)
		{
			if (bmhd->bmh_Planes == 6)	// HAM6
				imode = IMODE_RGB15;
			else								// HAM8
				imode = IMODE_BGR8;
		}
		else
		{
			if (bmhd->bmh_Planes == 1)
				imode = IMODE_MONO;
			else if (bmhd->bmh_Planes <= 4)
				imode = IMODE_INDEXED4;
			else if (bmhd->bmh_Planes <= 8)
				imode = IMODE_INDEXED8;
			else if (bmhd->bmh_Planes <= 24)
				imode = IMODE_BGR8;
		}
#endif
	}

	m_numcolors = numcolors;

#if 0
	g->mode = imode;
	g->width = bmhd->bmh_Width;
	g->height = bmhd->bmh_Height;
	g->totalFrames = -1;
#endif

	return IFF_OK;
}

IFFRESULT CIFFILBM::ReadBODY(ULONG ckSize)
{
	IFFRESULT iffresult = IFF_OK;	// Assume success

	BitMapHeader* bmhd = &m_bmhd;
	uint32 camg = m_camg;

	int width = bmhd->bmh_Width;
	int rows = bmhd->bmh_Height;
//	BYTE	bitcount = 8;//GetBitCount(r->mode);
	int srcBytesPerRow;
	uint8 nPlanes;

	int row;
	uint8 plane;

#if 0
	if (m_PBM)
	{
		srcBytesPerRow = width+(width & 1);
		nPlanes = 1;
	}
	else
#endif
	{
		srcBytesPerRow = RowBytes(width);

		nPlanes = bmhd->bmh_Planes;
		if (bmhd->bmh_Masking == mskHasMask) nPlanes++;
	}

// Do we support this compression method?
	if (bmhd->bmh_Compression > cmpByteRun1) return IFFERR_COMPRESS;

	uint8* ckdata = NULL;	// Buffer holding the body chunk data
	uint8* planeptr = NULL;	// Buffer containing planeptrs for one scanline

// Allocate mem and read in the entire body data
	ckdata = new uint8[ckSize];
	if (ckdata == NULL) return IFFERR_MEMORY;

	if (m_pIFFParser->IFFReadChunkBytes(ckdata, ckSize) != ckSize)
	{
		//GlobalFree(ckdata);
		//return IFFERR_READWRITE;
	// Continue anyway, the file is damaged, but we can restore the beginning of the image
	}

#if 0	// ???
	if (!m_doAnim && !m_PBM)
	{
		if (!(planeptr = (LPBYTE)GlobalAlloc(0, srcBytesPerRow*nPlanes)))
		{
			GlobalFree(ckdata);
			return IFFERR_MEMORY;
		}
	}
#endif

	uint8* ptr = ckdata;
	uint8* planes[24+8+1];

	if (true);//!m_PBM)
	{
#if 0
		if (!m_doAnim)
		{
			for (plane = 0; plane < nPlanes; plane++)
			{
				planes[plane] = planeptr+srcBytesPerRow*plane;
			}
		}
		else	// Read into the planes0, as we have to store this for later
#endif
		{
			//ASSERT(seqdata);

			for (plane = 0; plane < nPlanes; plane++)
			{
				planes[plane] = m_planes0[plane];
			}
		}
	}

// Process all the rows
	for (row = 0; row < rows; row++)
	{
		int nplanes = nPlanes;

		// Process all the planes (1 if PBM IBM DeluxePaint format)
		for (plane = 0; plane < nplanes; plane++)
		{
			uint8* dest;

			/*
			if (m_PBM)
				;//dest = bmbits;
			else
			*/
			dest = planes[plane];

			if (bmhd->bmh_Compression == cmpNone)
			{
				memcpy(dest, ptr, srcBytesPerRow);
				ptr += srcBytesPerRow;
			}
			else if (bmhd->bmh_Compression == cmpByteRun1)
			{
				if (UnpackRowByteRun1((char **)&ptr, (char** )&dest, srcBytesPerRow))
				{
				// Error, end loop
					plane = nPlanes;
					row = rows;

					iffresult = IFFERR_CORRUPTED;
				}
			}
		}

		if (iffresult == 0)
		{
#if 0
			if (!m_doAnim)
			{
				/*
				if (!m_PBM)
				{
					::PlanarToChunky(bmbits, bitcount, width, planes, bmhd->bmh_Planes, camg, m_colors);
				}
				*/
			}
			else
#endif
			{
				for (uint8 i = 0; i < bmhd->bmh_Planes; i++)
				{
					planes[i] += srcBytesPerRow;
				}
			}
		}

		//bmbits += pBitmapSample->bytesPerRow;
	}

//	if (m_doAnim)
	{
//		CopyMemory(m_planes1[0], m_planes0[0], m_planeSize*bmhd->bmh_Planes);
	}

	if (planeptr) delete[] planeptr;
	if (ckdata) delete[] ckdata;

	return iffresult;
}

void CIFFILBM::PlanarToChunky(uint8 **planes, IMediaSample* sample)
{
// Convert from planar to chunky

	uint8** cPlanes = planes;//m_cPlanes2;
	ASSERT(cPlanes);
	BitMapHeader* bmhd = &m_bmhd;

	LSampleData sampledata;
	if (sample->LockBits(&sampledata) >= 0)
	{
		for (int row = 0; row < bmhd->bmh_Height; row++)
		{
			uint8* bmbits = (uint8*)sampledata.idata + sampledata.rowbytes*row;
			uint8* planes[33];

			for (int i = 0; i < bmhd->bmh_Planes; i++)
			{
				planes[i] = cPlanes[i]+RowBytes(bmhd->bmh_Width)*row;
			}

			PlanarToChunkyScanline(bmbits, sampledata.bitcount,
				bmhd->bmh_Width, planes, bmhd->bmh_Planes, m_camg, m_colors);
		}

		sample->UnlockBits();
	}
	else
	{
#ifdef _DEBUG
		ASSERT(0);
		//MessageBeep(-1);
#endif
	}
}

}	// MediaShow
}
