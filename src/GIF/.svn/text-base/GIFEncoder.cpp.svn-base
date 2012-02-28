// GIFEncoder.cpp : Implementation of CGIFEncoder
#include "stdafx.h"
#include "GIF.h"
#include "GIFEncoder.h"

/////////////////////////////////////////////////////////////////////////////
// CGIFEncoder::CInputPin

STDMETHODIMP CGIFEncoder::CInputPin::ReceiveConnection(ILPin* pConnector, ILMediaType* pMediaType)
{
	CLPinImpl::ReceiveConnection(pConnector, pMediaType);

	m_pFilter->m_prevSample = NULL;

	m_videoType = pMediaType;
	if (m_videoType == NULL) return E_NOINTERFACE;

	return S_OK;
}

STDMETHODIMP CGIFEncoder::CInputPin::Receive(ILMediaSample *pSample)
{
//	m_pFilter->m_pSample = static_cast<CVideoSample*>(pSample);

	CComQIPtr<ILVideoSample> videoSample = pSample;
	if (videoSample == NULL) return E_NOINTERFACE;

	if (m_pFilter->m_prevSample == NULL)
	{
		// Allocate space for hash table
		m_pFilter->hash_code = (code_int *)GlobalAlloc(GMEM_ZEROINIT, HSIZE * sizeof(code_int));
		m_pFilter->hash_value = (hash_entry *)GlobalAlloc(GMEM_ZEROINIT, HSIZE * sizeof(hash_entry));

		m_pFilter->PutScreenHeader();

	#if 0
		if (g->totalFrames > 1)	// Anim
		{
			if (bLoop)
			{
				if (loopmode == 0)
				{
					PutLoopBlock(0);
				}
				else
					PutLoopBlock(looptimes);
			}
		}
	#endif
	}

#if 0	// Have this
	if ((g->fileType == 1) || (g->transparentColor != -1))	// Anim or transparency
#endif
		m_pFilter->PutControlBlock(videoSample);

	m_pFilter->PutImageBlock(videoSample, FALSE/*bInterlaced*/);

	m_pFilter->m_prevSample = videoSample;

	return S_OK;
}

STDMETHODIMP CGIFEncoder::CInputPin::EndOfStream()
{
	/*
	PutCommentBlock(
		"This GIF file was written with MMStudio\n\r"
		"http://www.lerstad.com/");
		*/

	m_pFilter->WriteB(';');	  // Write the GIF terminator mark

	GlobalFree(m_pFilter->hash_code);
	GlobalFree(m_pFilter->hash_value);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CGIFEncoder

/*
 * Routines to package compressed data bytes into GIF data blocks.
 * A data block consists of a count byte (1..255) and that many data bytes.
 */

void CGIFEncoder::flush_packet ()
/* flush any accumulated data */
{
	if (bytesinpkt > 0)	/* never write zero-length packet */
	{
		packetbuf[0] = (char) bytesinpkt++;
		
		if (Write(packetbuf, bytesinpkt) < bytesinpkt)
			MessageBeep(-1);	// TODO
		
		bytesinpkt = 0;
	}
}


/* Add a character to current packet; flush to disk if necessary */
#define CHAR_OUT(c)  \
	{ packetbuf[++bytesinpkt] = (char) (c);  \
		 if (bytesinpkt >= 255)  \
			flush_packet();  \
	}


/* Routine to convert variable-width codes into a byte stream */

void CGIFEncoder::output (code_int code)
/* Emit a code of n_bits bits */
/* Uses cur_accum and cur_bits to reblock into 8-bit bytes */
{
  cur_accum |= ((INT32) code) << cur_bits;
  cur_bits += n_bits;

  while (cur_bits >= 8)
  {
	 CHAR_OUT(cur_accum & 0xFF);
	 cur_accum >>= 8;
	 cur_bits -= 8;
  }

  /*
	* If the next entry is going to be too big for the code size,
	* then increase it, if possible.  We do this here to ensure
	* that it's done in sync with the decoder's codesize increases.
	*/
  if (free_code > maxcode)
  {
	 n_bits++;
	 if (n_bits == MAX_LZW_BITS)
		maxcode = LZW_TABLE_SIZE; /* free_code will never exceed this */
	 else
		maxcode = MAXCODE(n_bits);
  }
}

/* The LZW algorithm proper */

void CGIFEncoder::clear_hash ()
/* Fill the hash table with empty entries */
{
  /* It's sufficient to zero hash_code[] */
  ZeroMemory(hash_code, HSIZE * sizeof(code_int));
}


void CGIFEncoder::clear_block ()
/* Reset compressor and issue a Clear code */
{
  clear_hash();			/* delete all the symbols */
  free_code = ClearCode + 2;
  output(ClearCode);	/* inform decoder */
  n_bits = init_bits;	/* reset code size */
  maxcode = MAXCODE(n_bits);
}


void CGIFEncoder::compress_init (int i_bits)
/* Initialize LZW compressor */
{
  /* init all the state variables */
  n_bits = init_bits = i_bits;
  maxcode = MAXCODE(n_bits);
  ClearCode = ((code_int) 1 << (i_bits - 1));
  EOFCode = ClearCode + 1;
  free_code = ClearCode + 2;
  first_byte = TRUE;	/* no waiting symbol yet */
  /* init output buffering vars */
  bytesinpkt = 0;
  cur_accum = 0;
  cur_bits = 0;
  /* clear hash table */
  clear_hash();
  /* GIF specifies an initial Clear code */
  output(ClearCode);
}

void CGIFEncoder::compress_byte (int c)
/* Accept and compress one 8-bit byte */
{
  register hash_int i;
  register hash_int disp;
  register hash_entry probe_value;

  if (first_byte) {	/* need to initialize waiting_code */
	 waiting_code = c;
	 first_byte = FALSE;
	 return;
  }

  /* Probe hash table to see if a symbol exists for
	* waiting_code followed by c.
	* If so, replace waiting_code by that symbol and return.
	*/
  i = ((hash_int) c << (MAX_LZW_BITS-8)) + waiting_code;
  /* i is less than twice 2**MAX_LZW_BITS, therefore less than twice HSIZE */
  if (i >= HSIZE)
	 i -= HSIZE;

  probe_value = HASH_ENTRY(waiting_code, c);

  if (hash_code[i] != 0) { /* is first probed slot empty? */
	 if (hash_value[i] == probe_value) {
		waiting_code = hash_code[i];
		return;
	 }
	 if (i == 0)			/* secondary hash (after G. Knott) */
		disp = 1;
	 else
		disp = HSIZE - i;
	 for (;;) {
		i -= disp;
		if (i < 0)
	i += HSIZE;
		if (hash_code[i] == 0)
	break;			/* hit empty slot */
		if (hash_value[i] == probe_value) {
	waiting_code = hash_code[i];
	return;
		}
	 }
  }

  /* here when hashtable[i] is an empty slot; desired symbol not in table */
  output(waiting_code);
  if (free_code < LZW_TABLE_SIZE) {
	 hash_code[i] = free_code++; /* add symbol to hashtable */
	 hash_value[i] = probe_value;
  } else
	 clear_block();
  waiting_code = c;
}


void CGIFEncoder::compress_term ()
/* Clean up at end */
{
  /* Flush out the buffered code */
  if (!first_byte)
	 output(waiting_code);
  /* Send an EOF code */
  output(EOFCode);
  /* Flush the bit-packing buffer */
  if (cur_bits > 0) {
	 CHAR_OUT(cur_accum & 0xFF);
  }
  /* Flush the packet buffer */
  flush_packet();
}

void CGIFEncoder::PutScreenHeader()
{
	long width;
	long height;
	m_pInput->m_videoType->GetWidth(&width);
	m_pInput->m_videoType->GetHeight(&height);

	CComPtr<ILPalette> palette;
	m_pInput->m_videoType->GetPalette(&palette);

	LONG numcolors;
	palette->GetCount(&numcolors);

	m_pInput->m_gsd.gifWidth = (USHORT)width;
	m_pInput->m_gsd.gifHeight = (USHORT)height;

	int bitcount;

	if (numcolors <= 2)			bitcount = 1;
	else if (numcolors <= 4)	bitcount = 2;
	else if (numcolors <= 8)	bitcount = 3;
	else if (numcolors <= 16)	bitcount = 4;
	else if (numcolors <= 32)	bitcount = 5;
	else if (numcolors <= 64)	bitcount = 6;
	else if (numcolors <= 128)	bitcount = 7;
	else								bitcount = 8;

/*	if (g->bmi->bmiHeader.biBitCount == 1)
		InitCodeSize = 2;
	else
*/
		InitCodeSize = 8;// ???bitcount;//8;	// bitcount

	GIFFILEHEADER	gfh;

	gfh.gifSignature[0] = 'G';
	gfh.gifSignature[1] = 'I';
	gfh.gifSignature[2] = 'F';
	gfh.gifVersion[0] = '8';
	gfh.gifVersion[2] = 'a';

#if 0
	if (g->fileType == 1)	// We'll create a GIF Animation
#endif
		gfh.gifVersion[1] = '9';
#if 0
	else
		gfh.gifVersion[1] = '7';
#endif

	Write(&gfh, sizeof(GIFFILEHEADER));

	m_pInput->m_gsd.gifBgColor = 0;	// g->BgIndex
	m_pInput->m_gsd.gifPixelAspect = 0;
	m_pInput->m_gsd.gifGlobalCTableSize = bitcount-1;
	m_pInput->m_gsd.gifColorRes = 8-1;
	m_pInput->m_gsd.gifSortFlag = 0;
	m_pInput->m_gsd.gifGlobalCTable = TRUE;	// Has a global colorpalette
	Write(&m_pInput->m_gsd, sizeof(GIFSCREENDESCR));

// Write the global colortable
	GIFCOLORTRIPLET colortable[256] = {0};

	for (WORD i = 0; i < numcolors; i++)
	{
		OLE_COLOR color;
		palette->Item(i, &color);

		colortable[i].Red = GetRValue(color);//g->pPalette8[i].red;
		colortable[i].Green = GetGValue(color);//g->pPalette8[i].green;
		colortable[i].Blue = GetBValue(color);//g->pPalette8[i].blue;
	}

	Write(colortable, numcolors*sizeof(GIFCOLORTRIPLET));
}

void CGIFEncoder::CalcBounds(ILVideoSample* sample, GIFIMAGEDESCR *gid)
{
	long width;
	long height;
	m_pInput->m_videoType->GetWidth(&width);
	m_pInput->m_videoType->GetHeight(&height);

	WORD	left = 0;
	WORD	top = 0;
//	WORD	width = width;//g->width;//bmi->bmiHeader.biWidth;
//	WORD	height = g->height;//abs(g->bmi->bmiHeader.biHeight);

	if (m_currentFrame > 0)
	{
#if 0
		LONG	right, bottom;

		SHORT	bitcount = 8;//g->bmi->bmiHeader.biBitCount;
		LONG	x, y;

		LPBYTE	bptr0, bptr1;
		LPDWORD	dwptr0, dwptr1;

		LVideoSampleData

		WORD	dwordsPerRow = g->bytesPerRow>>2;



	// Find top edge
		dwptr0 = (LPDWORD)g->prevbits;
		dwptr1 = (LPDWORD)g->bits;

		for (y = 0; y < height; y++)
		{
			for (x = 0; x < dwordsPerRow; x++)
			{
				if (*dwptr0++ != *dwptr1++)
				{
					top = y;
					y = height;
					break;
				}
			}
		}

	// Find bottom edge
		dwptr0 = (LPDWORD)&g->prevbits[g->bytesPerRow*(height-1)+(dwordsPerRow-1)];
		dwptr1 = (LPDWORD)&g->bits[g->bytesPerRow*(height-1)+(dwordsPerRow-1)];

		for (y = height-1; y >= 0; y--)
		{
			for (x = dwordsPerRow-1; x >= 0; x--)
			{
				if (*dwptr0-- != *dwptr1--)
				{
					bottom = y;
					y = -1;
					break;
				}
			}
		}

	  // Find left edge
		for (x = 0; x < width; x++)
		{
			if (bitcount == 8)
			{
				bptr0 = &g->prevbits[x];
				bptr1 = &g->bits[x];
			}
			else if (bitcount == 4)
			{
			}
			else
			{
			}

			for (y = 0; y < height; y++)
			{
				if (*bptr0 != *bptr1)
				{
					left = x;
					x = width;
					break;
				}

				bptr0 += g->bytesPerRow;
				bptr1 += g->bytesPerRow;
			}
		}

	  // Find right edge
		for (x = width-1; x >= 0; x--)
		{
			if (bitcount == 8)
			{
				bptr0 = &g->prevbits[x];
				bptr1 = &g->bits[x];
			}
			else if (bitcount == 4)
			{
			}
			else
			{
			}

			for (y = 0; y < height; y++)
			{
				if (*bptr0 != *bptr1)
				{
					right = x;
					x = -1;
					break;
				}

				bptr0 += g->bytesPerRow;
				bptr1 += g->bytesPerRow;
			}
		}

		width = right-left+1;
		height = bottom-top+1;
#endif
	}

	gid->gifLeft = left;
	gid->gifTop = top;
	gid->gifWidth = width;
	gid->gifHeight = height;
}

void CGIFEncoder::PutImageBlock(ILVideoSample* sample, BYTE bInterlaced)
{
//	GIFOPTIONS*		options = NULL;
//	ANIMOPTIONS*	animoptions = NULL;
//	ASSERT(g->lpVideoOptions);

//	BYTE bInterlaced = FALSE;
/*
	if (g->fileType == 0)
	{
		g->adescrSuite->GetBoolean(g->optionsDescr, 'ilac', &bInterlaced);
	}
	else
	{
		bInterlaced = FALSE;
	}
*/
	ULONG cbWritten;

	BYTE c = 0x2c;
	m_stream->Write(&c, 1, &cbWritten);	// Image separator

	GIFIMAGEDESCR	gid;

	long width;
	long height;
	m_pInput->m_videoType->GetWidth(&width);
	m_pInput->m_videoType->GetHeight(&height);

#if 0	// Had this
	if (m_totalFrames > 1)
	{
		CalcBounds(&gid);
	}
	else
#endif
	{
		gid.gifLeft = 0;
		gid.gifTop = 0;
		gid.gifWidth = (USHORT)width;
		gid.gifHeight = (USHORT)height;
	}

	gid.gifLocalCTableSize = 0;
	gid.gifReserved = 0;
	gid.gifSortFlag = 0;

//	if (g->totalFrames == 1)
		gid.gifInterlaced = bInterlaced;
/*	else
		gid.gifInterlaced = 0;
*/

	gid.gifLocalCTable = FALSE;
	m_stream->Write(&gid, sizeof(GIFIMAGEDESCR), &cbWritten);

// Write Initial Code Size byte
	m_stream->Write(&InitCodeSize, 1, &cbWritten);

// Initialize for LZW compression of image data
	compress_init(InitCodeSize+1);

	SHORT	bitcount = 8;//g->bmi->bmiHeader.biBitCount;
	WORD	pass2_offset, pass3_offset, pass4_offset;

	if (gid.gifInterlaced)
	{
		pass2_offset = (gid.gifHeight+7)/8;
		pass3_offset = pass2_offset+(gid.gifHeight+3)/8;
		pass4_offset = pass3_offset+(gid.gifHeight+1)/4;
	}

#if 0
	if (g->totalFrames == 1)
	{
//		g->ProgressRange(g, 0, gid.gifHeight);
	}
#endif

// Write the image
	for (WORD row = gid.gifTop; row < gid.gifTop+gid.gifHeight; row++)
	{
		WORD	actual_row;

		if (!gid.gifInterlaced)
		{
			actual_row = row;	// For non-interlaced, the rows are one after the other
		}
		else
		{
			WORD	row2 = row-gid.gifTop;

			if (row2 < pass2_offset)								// pass1
				actual_row = row2 << 3;
			else if (row2 < pass3_offset)  						// pass2
				actual_row = ((row2-pass2_offset) << 3)+4;
			else if (row2 < pass4_offset)							// pass3
				actual_row = ((row2-pass3_offset) << 2)+2;
			else															// pass4
				actual_row = ((row2-pass4_offset) << 1)+1;
		}

		LPBYTE ptr;

		LVideoSampleData sampledata;
		sample->LockBits(&sampledata);

		if (sampledata.bitcount == 8)
			ptr = &sampledata.idata[sampledata.rowbytes*actual_row+gid.gifLeft];
		else if (sampledata.bitcount == 4)
			ptr = &sampledata.idata[sampledata.rowbytes*actual_row+(gid.gifLeft>>1)];
		else
			ptr = &sampledata.idata[sampledata.rowbytes*actual_row+(gid.gifLeft>>3)];

		for (WORD col = gid.gifLeft; col < gid.gifLeft+gid.gifWidth; col++)
		{
			BYTE	byt;

			if (bitcount == 8)
			{
				byt = *ptr++;
			}
			else if (bitcount == 4)
			{
				if (col & 1)
				{
					byt = *ptr & 0x0f;
					ptr++;
				}
				else
					byt = *ptr>>4;
			}
			else
			{
				SHORT	bit = 7-(col%8);
				byt = (*ptr & (1<<bit))? 1 : 0;
				if (bit == 0) ptr++;
			}

			compress_byte(byt);
		}

#if 0
		if (g->totalFrames == 1)
		{
			if ((row % 30) == 0)
			{
			//	if (g->Abort(g)) break;
			//	g->DoProgress(g, row-gid.gifTop);
			}
		}
#endif
	}

//Flush LZW mechanism
	compress_term();

	c = 0;
	m_stream->Write(&c, 1, &cbWritten);	// Write a zero-length data block to end the series
}

LONG CGIFEncoder::PutControlBlock(ILVideoSample* sample)
{
	GIFCONTROL	gctrl;
	gctrl.Transparent = 0;// TODO (g->transparentColor != -1)? 1: 0;
	gctrl.UserInput = 0;
	gctrl.Disposal = 1;	// Don't dispose
	gctrl.Reserved = 0;

	double timeStart;
	double timeEnd;
	sample->GetTime(&timeStart, &timeEnd);

	double timeDur = timeEnd-timeStart;

	gctrl.DelayTime = 10;//timeDur*100; // (1/100) of a second to wait
// TODO have this	gctrl.DelayTime = (100*g->rateScale)/g->frameRate; // (1/100) of a second to wait
	gctrl.TransparentIndex = 0;// TODO have this(g->transparentColor != -1)? g->transparentColor: 0;

	WriteB(0x21);								// Extension
	WriteB(0xf9);								// Comment

	WriteB(sizeof(GIFCONTROL));			// Size
	Write(&gctrl, sizeof(GIFCONTROL));	// Data

	WriteB(0);									// Terminator

	return 0;
}

LONG CGIFEncoder::PutLoopBlock(WORD iterations)
{
	GIFLOOP	loop;
	loop.gifLoop = TRUE;
	loop.gifIterations = iterations;

	WriteB(0x21);					// Extension
	WriteB(0xff);					// Application
	WriteB(11);						// Block size
	Write("NETSCAPE2.0", 11);	// Data
	WriteB(3);		  				// Block size
	Write(&loop, 3);				// Data
	WriteB(0);						// Terminator

	return 0;
}

LONG CGIFEncoder::PutCommentBlock(LPTSTR comment)
{
	BYTE	len = (BYTE)lstrlen(comment);

	WriteB(0x21);			// Extension
	WriteB(0xfe);			// Comment
	WriteB(len);			// Size
	Write(comment, len);	// Data
	WriteB(0);	// Terminator

	return 0;
}

#if 0
long CGIFEncoder::VideoQueryCaps(LPFORMATRECORD r)
{
	r->dwSupportedFormats = VCAP_Indexed8;
	return 0;
}

#include "GIFSaveOptionsDlg.h"

long CGIFEncoder::SaveVideoOptions	(LPFORMATRECORD r, LONG, CIUIWnd* hParent)
{
	CGIFSaveOptionsDlg* pDlg = (CGIFSaveOptionsDlg*)sBasic->CreateCmdTarget("IGIFSaveOptionsDlg");

	r->optionsDescr->GetBoolean('ilac', &pDlg->m_bInterlaced);
	r->optionsDescr->GetBoolean('loop', &pDlg->m_bLoop);
//	r->optionsDescr->GetInteger('lmod', &loopmode);
	r->optionsDescr->GetInteger('tims', &pDlg->m_loopTimes);

	if (pDlg->DoModal(hParent, g_hInst, IDD_GIFSAVEOPTIONS))
	{
		r->optionsDescr->PutBoolean('ilac', pDlg->m_bInterlaced);
		r->optionsDescr->PutBoolean('loop', pDlg->m_bLoop);
	//	r->optionsDescr->GetInteger('lmod', &loopmode);
		r->optionsDescr->PutInteger('tims', pDlg->m_loopTimes);
	}

	pDlg->Release();

	return 0;
}

long CGIFEncoder::VideoOptionsText(LPFORMATRECORD r, char* sbuf)
{
	BYTE bInterlaced = FALSE;
	BYTE bLoop = FALSE;
	long loopmode;
	long looptimes;
	
	r->optionsDescr->GetBoolean('ilac', &bInterlaced);
	r->optionsDescr->GetBoolean('loop', &bLoop);
	r->optionsDescr->GetInteger('lmod', &loopmode);
	r->optionsDescr->GetInteger('tims', &looptimes);

	char buf[256];

	sprintf(buf, "Interlaced:\t%s\n\r", bInterlaced? "Yes": "No");
	strcat(sbuf, buf);

	sprintf(buf, "Loop:\t\t%s\n\r", bLoop? "Yes": "No");
	strcat(sbuf, buf);

	sprintf(buf, "Loop times:\t%d\n\r", looptimes);
	strcat(sbuf, buf);

	return 0;
}
#endif

#if 0
LONG CGIFEncoder::Write(LPFORMATRECORD formatRecord)
{
	g = formatRecord;
	ASSERT(g->optionsDescr);

	ClearMembers();

	BYTE bInterlaced = FALSE;
	BYTE bLoop = FALSE;
	long loopmode = 0;
	long looptimes = 2;
	
	if (g->fileType == 0)
	{
		g->optionsDescr->GetBoolean('ilac', &bInterlaced);
	}
	else
	{
		bInterlaced = FALSE;
		g->optionsDescr->GetBoolean('loop', &bLoop);
		g->optionsDescr->GetInteger('lmod', &loopmode);
		g->optionsDescr->GetInteger('tims', &looptimes);
	}

	// Allocate space for hash table
	hash_code = (code_int *)g->basic->AllocBuffer(HSIZE * sizeof(code_int), TRUE);
	hash_value = (hash_entry *)g->basic->AllocBuffer(HSIZE * sizeof(hash_entry), TRUE);

	PutScreenHeader();

	if (g->totalFrames > 1)	// Anim
	{
		if (bLoop)
		{
			if (loopmode == 0)
			{
				PutLoopBlock(0);
			}
			else
				PutLoopBlock(looptimes);
		}
	}

	if (g->totalFrames > 1)	// Anim
	{
		g->ProgressRange(g, 0, g->totalFrames);
	}

	for (LONG i = 0; i < g->totalFrames; i++)
	{
		if ((g->fileType == 1) || (g->transparentColor != -1))	// Anim or transparency
			PutControlBlock();

		PutImageBlock(bInterlaced);

		/*
		if (g->totalFrames > 1)
		{
			if (g->Abort(g)) break;
			g->DoProgress(g, i+1);
			g->NextAnimFrame(g);
		}
		*/
	}


	return 0;
}
#endif
