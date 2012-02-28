/*
	RdPSD.cpp
	Copyright (c) 1999 Sigurd Lerstad. All rights reserved.
  
	Read PSD (PhotoShop) files

	History:

	--19 Mar. 1999
		Blending Modes

	--20 Mar. 1999
		Adjustment Layers:
			Invert/Negative
			Threshold
			Posterize
			Brightness/Contrast

	--23 Mar. 1999
		Adjustment Layers:
			Levels
			Color Balance (almost)
			Selective Colors (almost)

	--24 Mar. 1999
		Read Path resources
		Visible/Invisible Layer
		Allocate structures dynamically instead of on stack

	--27 Mar. 1999
		Read last image resource (if there are no layers)
		Read Grayscale/Indexed/Bitmap ImageMode

	--28 Mar. 1999
		Read 16-bit images

  --10 May. 1999
		Adjustment Layer - Channel Mixer

	TODO:

		Adjustment Layers
			(???) Curves
			(???) Hue/Saturation

		Clipping layers

		Blending ranges

  5.0 features

		Text Layer

		Adjustment Layers

		Effect Layers
			Drop Shadow
			Inner Shadow
			Outer Glow
			Inner Glow
			Bevel and Emboss
*/

#include "stdafx.h"

WORD UnpackRowByteRun1(char** pSource, char** pDest, WORD srcBytes, SHORT dstBytes)
{
#define UGetByte(src)	(*src++)
#define UPutByte(dst,c)	(*dst++ = (c))

	register char* source = *pSource;
	register char* dest = *pDest;

	BOOL	error = TRUE;	// Assume error until we make it through the loop

	while (dstBytes > 0)
	{
		if ((srcBytes -= 1) < 0) goto ErrorExit;

		register SHORT	n = UGetByte(source);

		if (n >= 0)
		{
			n += 1;

		 	if ((srcBytes -= n) < 0) goto ErrorExit;
			if ((dstBytes -= n) < 0) goto ErrorExit;

			while (n--)
			{
				UPutByte(dest, UGetByte(source));
			}
		}
		else if (n != -128)
		{
			n = -n + 1;

			if ((srcBytes -= 1) < 0) goto ErrorExit;
			if ((dstBytes -= n) < 0) goto ErrorExit;

			register char c = UGetByte(source);

			while (n--)
			{
				UPutByte(dest, c);
			}
		}
	}

	if (srcBytes != 0) goto ErrorExit;

	error = FALSE;	// Success

ErrorExit:

// Update the pointers
//	*pSource = source;
//	*pDest = dest;

	return error;
}

#include "psd.h"

WORD UnpackRowByteRun1(char** pSource, char** pDest, WORD srcBytes, SHORT dstBytes);

// PSDLayer

void PSDLayer::ReadPSDLayerChannel(long channelID, long imageRowBytes, uint8* imagebits) const
{
//	HRESULT result = S_OK;

//	PSDLayer* psdlayer = this;//&psdfile->layerList[lay];

	int	channels = layerinfo.channels;
	int	laywidth = layerinfo.rect.right - layerinfo.rect.left;
	int	layheight = layerinfo.rect.bottom - layerinfo.rect.top;
	
	int	maskwidth;
	int	maskheight;
	
	TRACE("width: %d, height: %d, channels: %d\n", laywidth, layheight, channels);
	
	//	if (channels == 5)
	{
		maskwidth = layermaskinfo.rect.right - layermaskinfo.rect.left;
		maskheight = layermaskinfo.rect.bottom - layermaskinfo.rect.top;
		TRACE("mwidth: %d, mheight: %d\n", maskwidth, maskheight);
	}

	DWORD offset = m_file->m_layerDataStartPos;
	for (int i = 0; i < m_file->m_layerList.size(); i++)
	{
		if (m_file->m_layerList[i] == this) break;

		for (int ch = 0; ch < m_file->m_layerList[i]->layerinfo.channels; ch++)
		{
			offset += m_file->m_layerList[i]->channelinfo[ch].length;
		}
	}

	int ch;
	for (ch = 0; ch < layerinfo.channels; ch++)
	{
		if (channelinfo[ch].channelID == channelID) break;
		offset += channelinfo[ch].length;
	}

	if (ch >= layerinfo.channels)
		throw -1;

//	LARGE_INTEGER li;
//	li.QuadPart =  offset;
	m_file->m_file->Seek(offset, STREAM_SEEK_SET);

	/*
	for (int ch = 0; ch < channels; ch++)
	{
	*/
		uint32	channelStartPos;
	//	li.QuadPart = 0;
		channelStartPos = m_file->m_file->Seek(0, STREAM_SEEK_CUR);

		WORD compression;
		m_file->m_file->Read(&compression, 2);
		compression = ENDIANWORD(compression);
		
		if ((compression == 0) ||	// No compression
			(compression == 1))	// PackBits compression
		{
			int width;
			int height;
			
			if (channelinfo[ch].channelID >= -1)
			{
				width = laywidth;
				height = layheight;
			}
			else
			{
				TRACE("maskmaskmaskmask\n");
				width = maskwidth;
				height = maskheight;
			}
			
			LPWORD	byteCount;
			
			if (compression == 0)
				byteCount = NULL;
			else
				byteCount = new WORD[height];
			
			if ((compression == 0) || (byteCount))
			{
				if (compression == 1)
					m_file->m_file->Read(byteCount, height*2);
				
				char*	srcbuf = NULL;
				char*	destbuf = NULL;
				int maxcount = width*3;
				
				destbuf = new char[width];
				
				if (compression == 1)
					srcbuf = new char[maxcount];	// Allocate enough for worst case
				
				for (int y = 0; y < height; y++)
				{
					char*	src;
					char*	dest;
					WORD	count;
					
					if (compression == 0)
					{
						count = width;
						src = destbuf;
					}
					else
					{
						src = srcbuf;
						count = ENDIANWORD(byteCount[y]);
						
						if (count > maxcount)	// Reallocate buffer
						{
							maxcount = count;
							
							delete [] srcbuf;
							srcbuf = new char[maxcount];
						}
					}
					
					m_file->m_file->Read(src, count);
					
					src = srcbuf;
					dest = destbuf;
					
					if (compression == 1)
					{
						if (UnpackRowByteRun1(&src, &dest, count, width))
						{
							TRACE("error on line %d\n", y);
	//						result = -1;//FORMAT_CORRUPTED_FILE;
							throw -1;
						}
					}
					
					LPBYTE destptr = NULL;
					int offset;

					int channelID = channelinfo[ch].channelID;
					
					if (channelID >= 0)	// RGB Channels
					{
					//	if (layerType[lay] == 1)
						{
							/*
							if (imode == PixelFormat32bppARGB)
							*/
							{
								offset = 4;
								destptr = imagebits + imageRowBytes*y;// + (channelID+1);
							}
						/*
							else if (imode == IMODE_CMYK)
								offset = 4;
						*/
						//	else
						//		offset = 1;
						}
					}
					else if (channelID == -1)	// Alpha Channel
					{
						//if (imode == PixelFormat32bppARGB)
						{
							offset = 4;
							destptr = imagebits + imageRowBytes*y;
						}
					/*
						if (layerType[lay] == 1)
						{
							IMAGEDATARECORD imagedata;
							r->GetImageDataRecord(layerID[lay], &imagedata);
							
							destptr = imagedata.alphabits + imagedata.alphaRowBytes*y;
							offset = 1;
						}
					*/
					}
					else if (channelinfo[ch].channelID == -2)	// Layer Mask
					{
					//	IMAGEDATARECORD imagedata;
					//	r->GetImageDataRecord(layerMaskID[lay], &imagedata);
						
					//	destptr = imagedata.imagebits + imagedata.imageRowBytes*y;
					//	offset = 1;
					}
					
					if (destptr)
					{
						LPBYTE srcptr = (LPBYTE)destbuf;
						
						for (int x = 0; x < width; x++)
						{
							*destptr = *srcptr;
							destptr += offset;
							srcptr++;
						}
					}
				}
				
				if (destbuf) delete [] destbuf;
				if (srcbuf) delete [] srcbuf;
			}

			if (byteCount) delete[] byteCount;
		}
		else	// Unknown compression
		{
			//sprintf(r->errorMsg, "Unknown compression %d", compression);
		//	result = -1;//PLUGIN_MSG;
			throw -1;
		}

		uint32 channelEndPos = m_file->m_file->Seek(0, STREAM_SEEK_CUR);

		uint32 channelLength = channelEndPos - channelStartPos;

		if (channelLength != channelinfo[ch].length)
		{
		//	strcpy(r->errorMsg, "Channel Size is wrong, file corrupt?");
//			result = -1;//PLUGIN_MSG;
			throw -1;
		}
	//}
}

// PSDFile

///////////////////
// Read Header
void PSDFile::ReadPSDHeader()
{
	m_file->Read(&m_hdr, sizeof(PSDHEADER));

// Check if this is a PSD image
	if (m_hdr.signature != PSD_SIG)
	{
		throw -1;
	}

	m_hdr.version = ENDIANWORD(m_hdr.version);
	m_hdr.channels = ENDIANWORD(m_hdr.channels);
	m_hdr.rows = ENDIANLONG(m_hdr.rows);
	m_hdr.cols = ENDIANLONG(m_hdr.cols);
	m_hdr.depth = ENDIANWORD(m_hdr.depth);
	m_hdr.mode = ENDIANWORD(m_hdr.mode);

// Check if we support version number
	if (m_hdr.version != 1)
	{
		//sprintf(r->errorMsg, "Unsupported version: %d", hdr->version);
		throw -1;//result = -1;//PLUGIN_MSG;
		//goto cleanup;
	}

	if ((m_hdr.depth != 1) && (m_hdr.depth != 8) && (m_hdr.depth != 16))
	{
		//sprintf(r->errorMsg, "Unsupported depth: %d", hdr->depth);
		throw -1;//result = -1;//PLUGIN_MSG;
		//goto cleanup;
	}

	/*
	if ((hdr->mode != MODE_RGB)		&&
		(hdr->mode != MODE_Grayscale)	&&
		(hdr->mode != MODE_Duotone)	&&
		(hdr->mode != MODE_Bitmap)		&&
		(hdr->mode != MODE_Indexed)	&&
		(hdr->mode != MODE_CMYK))
	{
		switch (hdr->mode)
		{
	//	case MODE_CMYK:	strcpy(r->errorMsg, "Currently unsupported CMYK Imagemode");
	//	break;
		case MODE_Multi:	strcpy(r->errorMsg, "Currently unsupported MultiChannel Imagemode");
		break;
		case MODE_Lab:		strcpy(r->errorMsg, "Currently unsupported Lab Imagemode");
		break;
		default:				sprintf(r->errorMsg, "Unsupported Imagemode %d", hdr->mode);
		}

		result = PLUGIN_MSG;
		goto cleanup;
	}
	*/
}

///////////////////
// Read Color table
//
// CTableLength = returns number of colors
//
void PSDFile::ReadColorTable(DWORD* CTableLength, LPBYTE colortable)
{
	DWORD ctableLength;

	m_file->Read(&ctableLength, 4);

	ctableLength = ENDIANLONG(ctableLength);

	if (ctableLength > 0)
	{
		m_file->Read(colortable, ctableLength);
	}

	*CTableLength = ctableLength;
}

/////////////////
// Skip Resources
void PSDFile::SkipPSDResources()
{
	uint32 imgresLength;

	m_file->Read(&imgresLength, 4);

	imgresLength = ENDIANLONG(imgresLength);

	if (imgresLength > 0)
	{
		m_file->Seek(imgresLength, STREAM_SEEK_CUR);
	}
}

void PSDFile::ParsePSDLayers()
{
	long result = 0;

	if (m_hdr.depth != 8)
	{
		//strcpy(r->errorMsg, "Doesn't support multiple layers with depth != 8");
		throw -1;
	}

	m_file->Read(&m_layerinfoLength, 4);
	m_layerinfoLength = ENDIANLONG(m_layerinfoLength);

	m_layerinfoStartPos = m_file->Seek(0, STREAM_SEEK_CUR);

/*
	numLayers:
	If <0, then number of layers is absolute value, and the first alpha
	channel contains the transparency data for the merged result.
*/

	m_file->Read(&m_numLayers, 2);
	m_numLayers = ENDIANWORD(m_numLayers);

	int numChannels = 0;

	int numLayers = m_numLayers;

	if (numLayers < 0)
	{
		numLayers = -numLayers;
	}

	TRACE("numLayers: %d\n", numLayers);

	/*
	if (numLayers > 512)	// Sensitive max limit
	{
	//	strcpy(r->errorMsg, "Too many layers\nNotify author");
	//	return PLUGIN_MSG;
		numLayers = 512;
	}
	*/

	//m_layerList = (PSDLAYER*)r->basic->AllocBuffer(sizeof(PSDLAYER)*numLayers, TRUE);
/*
	psdfile->layerinfo = (LAYERINFO*)r->buffer->AllocBuffer(sizeof(LAYERINFO)*numLayers, TRUE);
	psdfile->layerinfo2 = (LAYERINFO2*)r->buffer->AllocBuffer(sizeof(LAYERINFO2)*numLayers, TRUE);
	psdfile->layermaskinfo = (LAYERMASKINFO*)r->buffer->AllocBuffer(sizeof(LAYERMASKINFO)*numLayers, TRUE);
	psdfile->channelinfo = (CHANNELINFO (*)[8])r->buffer->AllocBuffer(sizeof(CHANNELINFO)*numLayers, TRUE);
	psdfile->layernames = (char (*)[256])r->buffer->AllocBuffer(256*numLayers, TRUE);
*/

/*
	psdfile->layerinfo = new LAYERINFO[numLayers];
	psdfile->layerinfo2 = new LAYERINFO2[numLayers];
	psdfile->layermaskinfo = new LAYERMASKINFO[numLayers];
	psdfile->channelinfo = new CHANNELINFO[numLayers][8];
	psdfile->layernames = new char[numLayers][256];
*/

/*
	DWORD*	layerID = new DWORD[numLayers];	// Layer id's
	DWORD*	layerMaskID = new DWORD[numLayers];	// Layer id's
	BYTE*		layerType = new BYTE[numLayers];	// Layer types

	ZeroMemory(layerID, numLayers*sizeof(DWORD));
	ZeroMemory(layerMaskID, numLayers*sizeof(DWORD));
	ZeroMemory(layerType, numLayers*sizeof(BYTE));
*/

	int lay;

	for (lay = 0; lay < numLayers; lay++)
	{
		TRACE("Layerinfo: %d\n", lay);
		
		PSDLayer* psdlayer = new PSDLayer;
		psdlayer->m_file = this;
		m_layerList.push_back(psdlayer);

		m_file->Read(&psdlayer->layerinfo, sizeof(LAYERINFO));
		
		psdlayer->layerinfo.rect.left = ENDIANLONG(psdlayer->layerinfo.rect.left);
		psdlayer->layerinfo.rect.top = ENDIANLONG(psdlayer->layerinfo.rect.top);
		psdlayer->layerinfo.rect.right = ENDIANLONG(psdlayer->layerinfo.rect.right);
		psdlayer->layerinfo.rect.bottom = ENDIANLONG(psdlayer->layerinfo.rect.bottom);
		psdlayer->layerinfo.channels = ENDIANWORD(psdlayer->layerinfo.channels);
		
		TRACE("\tchannels: %d\n", psdlayer->layerinfo.channels);
		TRACE("\t");
		
		numChannels += psdlayer->layerinfo.channels;
		
		for (int ch = 0; ch < psdlayer->layerinfo.channels; ch++)
		{
			m_file->Read(&psdlayer->channelinfo[ch], sizeof(CHANNELINFO));
			
			psdlayer->channelinfo[ch].channelID = ENDIANWORD(psdlayer->channelinfo[ch].channelID);
			psdlayer->channelinfo[ch].length = ENDIANLONG(psdlayer->channelinfo[ch].length);

			TRACE("%d, ", psdlayer->channelinfo[ch].channelID);
		}

		TRACE("\n");

		m_file->Read(&psdlayer->layerinfo2, sizeof(LAYERINFO2));

		if (psdlayer->layerinfo2.signature != ID_8BIM)
		{
			//strcpy(r->errorMsg, "Wrong layer signature");
			//result = -1;
			throw -1;
		}

	//	TRACE("\tFlags: %d\n", psdfile->layerinfo2[lay].flags);
	//	TRACE("\tClipping: %d\n", psdfile->layerinfo2[lay].clipping);

		psdlayer->layerinfo2.extra = ENDIANLONG(psdlayer->layerinfo2.extra);

		uint32 startPos = m_file->Seek(0, STREAM_SEEK_CUR);

// Layer mask data info
		uint32 layermaskdatasize;
		m_file->Read(&layermaskdatasize, 4);
		layermaskdatasize = ENDIANLONG(layermaskdatasize);
	//	size += 4;

		if (layermaskdatasize > 0)
		{
			// should be 20 bytes
			TRACE("\tLayermaskdatasize:\n", layermaskdatasize);
			if (layermaskdatasize != 20) TRACE("layermaskdatasize != 20\n");
			m_file->Read(&psdlayer->layermaskinfo, sizeof(LAYERMASKINFO));
		//	size += sizeof(LAYERMASKINFO);

			psdlayer->layermaskinfo.rect.left = ENDIANLONG(psdlayer->layermaskinfo.rect.left);
			psdlayer->layermaskinfo.rect.top = ENDIANLONG(psdlayer->layermaskinfo.rect.top);
			psdlayer->layermaskinfo.rect.right = ENDIANLONG(psdlayer->layermaskinfo.rect.right);
			psdlayer->layermaskinfo.rect.bottom = ENDIANLONG(psdlayer->layermaskinfo.rect.bottom);
			
			//	str.Format("flags: %d", layermaskinfo[lay].flags);
			
			m_file->Seek(layermaskdatasize-sizeof(LAYERMASKINFO), STREAM_SEEK_CUR);
			//r->SetFilePos(r->file, layermaskdatasize-sizeof(LAYERMASKINFO), FILE_CURRENT);
			//	size += layermaskdatasize-sizeof(LAYERMASKINFO);
		}
		
		// Layer blending range info, currently skip this
		DWORD	layerblendingsize;
		m_file->Read(&layerblendingsize, 4);
		layerblendingsize = ENDIANLONG(layerblendingsize);
		//	size += 4;

		if (layerblendingsize > 0) TRACE("\tblending %d\n", layerblendingsize);
		m_file->Seek(layerblendingsize, STREAM_SEEK_CUR);
		//	size += layerblendingsize;
		
		uint8	layerNameLength;
		m_file->Read(&layerNameLength, 1);
		//	size += 1;
		
		m_file->Read(psdlayer->layername, layerNameLength);
		psdlayer->layername[layerNameLength] = '\0';	// Null terminate
		//	size += layerNameLength;
		
		uint16 rlength = ((layerNameLength+4)/4)*4;

		m_file->Seek(rlength-layerNameLength-1, STREAM_SEEK_CUR);
	//	size += rlength-layerNameLength-1;
		
		// Skip remaining extra stuff
		uint32 endPos = m_file->Seek(0, STREAM_SEEK_CUR);
		
		uint32 readLength = endPos-startPos;
		uint32 extraSize = psdlayer->layerinfo2.extra - readLength;
		
		if (extraSize < 0)
		{
			//strcpy(r->errorMsg, "PSD: extraSize < 0, something wrong with the file?");
			throw -1;//return -1;//PLUGIN_MSG;
		}
		else if (extraSize > 0)	// Adjustment layer (?)
		{
			//li.QuadPart = extraSize;
			m_file->Seek(extraSize, STREAM_SEEK_CUR);
			// HandleAdjustmentLayer();
		}
		
		// Add the layer
		
		BOOL hasalpha = FALSE;
		BOOL haslayermask = FALSE;
		
		/*
		{
			for (int ch = 0; ch < psdfile->layerinfo[lay].channels; ch++)
			{
				if (psdfile->channelinfo[lay][ch].channelID == -1) hasalpha = TRUE;
				else if (psdfile->channelinfo[lay][ch].channelID == -2) haslayermask = TRUE;
			}
			
			//	if (layerinfo[lay].channels >= 5) haslayermask = TRUE;
		}
		*/
		
	}

	//m_layerDataStartPos = r->GetFilePos(r->file);
	m_layerDataStartPos = m_file->Seek(0, STREAM_SEEK_CUR);

	DWORD offset = 0;

	for (lay = 0; lay < numLayers; lay++)
	{
		for (int ch = 0; ch < m_layerList[lay]->layerinfo.channels; ch++)
		{
			offset += m_layerList[lay]->channelinfo[ch].length;
		}
	}

	m_file->Seek(offset, STREAM_SEEK_CUR);

	uint32 layerinfoEndPos = m_file->Seek(0, STREAM_SEEK_CUR);

// Align on word
	if (layerinfoEndPos & 1)
	{
		m_file->Seek(1, STREAM_SEEK_CUR);
		layerinfoEndPos++;
	}

#if 0
	if (m_layerinfoLength != (layerinfoEndPos - m_layerinfoStartPos))
	{
		/*
		sprintf(r->errorMsg,
			"Layerinfo length is wrong size should be: %d, is: %d, file corrupt?",
			psdfile->layerinfoLength, layerinfoEndPos-psdfile->layerinfoStartPos);
			*/
		//result = -1;//PLUGIN_MSG;
		throw -1;//return result;
	}
#endif

// Global Info
	uint32 globalinfosize;
	m_file->Read(&globalinfosize, 4);
	globalinfosize = ENDIANLONG(globalinfosize);

	if (globalinfosize > 0)
	{
		if (globalinfosize == sizeof(GLOBALLAYERMASKINFO))
		{
			GLOBALLAYERMASKINFO	globallayerinfo;
			m_file->Read(&globallayerinfo, sizeof(GLOBALLAYERMASKINFO));

			globallayerinfo.overlayColorSpace = ENDIANWORD(globallayerinfo.overlayColorSpace);
			globallayerinfo.opacity = ENDIANWORD(globallayerinfo.opacity);

			TRACE("opacity: %d\n", globallayerinfo.opacity);
			TRACE("kind: %d\n", globallayerinfo.kind);
		}
		else
		{
			TRACE("globalinfosize diff %d, %d\n", globalinfosize, sizeof(GLOBALLAYERMASKINFO));
			m_file->Seek(globalinfosize, STREAM_SEEK_CUR);
		}
	}
}

void PSDFile::Load(ISequentialByteStream* file)
{
	long result = 0;

	m_file = file;

// Header
	ReadPSDHeader();

// Color table
	ReadColorTable(&m_ctableLength, (LPBYTE)m_colortable);

//	LARGE_INTEGER li;
//	li.QuadPart = 0;

// Get resources file offset, read resources later, but for now, Skip resources
	m_resOffset = m_file->Seek(0, STREAM_SEEK_CUR);
	/*result =*/ SkipPSDResources();
	//if (FAILED(result)) throw -1;//return result;

// Layer/Mask
	m_file->Read(&m_layermaskLength, 4);

	m_layermaskLength = ENDIANLONG(m_layermaskLength);
	m_layermaskStartPos = m_file->Seek(0, STREAM_SEEK_CUR);

	if (m_layermaskLength > 0)
	{
		ParsePSDLayers();
	}

// Image resource

#if 0
	if (r->GetFilePos(r->file) < r->fileSize)
	{
		psdfile->bHasMergedImage = TRUE;
	}
#endif

}

/*
void FreePSDFile(PSDFILE* psdfile, LPFORMATRECORD r)
{
	if (psdfile)
	{
		if (psdfile->layerList) r->basic->FreeBuffer(psdfile->layerList);

		r->basic->FreeBuffer(psdfile);
	}
}
*/
