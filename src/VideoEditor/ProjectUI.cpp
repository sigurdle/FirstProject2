#include "stdafx.h"
#include "VideoEditor.h"
#include "VideoEditor2.h"
//#include "mmsx.h"
#include "ProjectUI.h"

COLORREF grayColor = RGB(190, 190, 190);
COLORREF lightColor = RGB(255, 255, 255);
COLORREF darkGrayColor = RGB(100, 100, 100);

void FormatTime(char* buf, double ctime, double framerate)
{
	LONG msecs = (LONG)ctime;

	LONG minutes = msecs/(1000*60);
	msecs %= (1000*60);

	LONG seconds = msecs/1000;
	msecs %= 1000;

	LONG frames = (LONG)(((double)msecs*framerate)/(double)1000 + 0.5);

	sprintf(buf, "%.2ld:%.2ld:%.2ld", minutes, seconds, frames);
}

static int m_iconHeight = 18;

#define PANE_LABEL		0
#define PANE_NAME			1
#define PANE_TYPE			2
#define PANE_DURATION	3
#define PANE_SIZE			4
#define PANE_PATHNAME	5
#define PANE_COMMENT		6
#define NUM_COLUMNS		7

// m_dragging values
#define DRAG_SIZEPANE	2
#define DRAG_ORDERPANE	3
#define DRAG_BUTTON		4

/////////////////////////////////////////////////////////////////////////////
// CProjectUI

CProjectUI::CProjectUI()
{
	m_pPrj = NULL;

	m_dragging = FALSE;
	m_whichPane = -1;
#if 0
	m_dropWnd = NULL;
#endif
	m_bWasInside = FALSE;

	m_column[PANE_LABEL].m_bVisible = TRUE;
	m_column[PANE_LABEL].m_width = 16;
	m_column[PANE_LABEL].m_bSizeable = FALSE;

	m_column[PANE_NAME].m_bVisible = TRUE;
	m_column[PANE_NAME].m_width = 100;
	m_column[PANE_NAME].m_bSizeable = TRUE;

	m_column[PANE_TYPE].m_bVisible = TRUE;
	m_column[PANE_TYPE].m_width = 80;
	m_column[PANE_TYPE].m_bSizeable = TRUE;

	m_column[PANE_DURATION].m_bVisible = TRUE;
	m_column[PANE_DURATION].m_width = 60;
	m_column[PANE_DURATION].m_bSizeable = FALSE;//TRUE;

	m_column[PANE_SIZE].m_bVisible = TRUE;
	m_column[PANE_SIZE].m_width = 40;
	m_column[PANE_SIZE].m_bSizeable = TRUE;

	m_column[PANE_PATHNAME].m_bVisible = TRUE;
	m_column[PANE_PATHNAME].m_width = 120;
	m_column[PANE_PATHNAME].m_bSizeable = TRUE;

	m_column[PANE_COMMENT].m_bVisible = FALSE;
	m_column[PANE_COMMENT].m_width = 140;
	m_column[PANE_COMMENT].m_bSizeable = TRUE;

	m_numColumns = NUM_COLUMNS;
}

CProjectUI::~CProjectUI()
{
	m_pPrj = NULL;
}

#if 0
	ON_MESSAGE(WM_USER+0, TWTransferDone)
#endif

/*
#include "..\\twcommon\\twain.h"

#include "dca_glue.h"
#include "dca_acq.h"
#include "captest.h"
*/

BOOL CloseTwain(HWND hWnd)
{
	int Message = IDOK;

	ASSERT(hWnd);

#if 0
	/* 
	* if the source is enable 
		*/
		if (TWIsDSEnabled())
		{
		//	Message = ::MessageBox (NULL, "Disable and close the Source\n\rand unload and close the Source Manager?",
		//		"Close message", MB_OKCANCEL);
			if (Message == IDOK)
			{
				if (TWDisableDS())
				{
					if (TWCloseDS())
					{
						if (TWCloseDSM(NULL))
						{
						//	CheckSpecialMenu(hWnd, TW_APP_CLOSESM);
						}
					}
				}
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		
		/*
		* if the source is open
		*/
		if (TWIsDSOpen())
		{
		//	Message = ::MessageBox (NULL, "Close the Source and unload \n\rand close the Source Manager?",
		//		"Close message", MB_OKCANCEL);
			if (Message == IDOK)
			{
				if (TWCloseDS())
				{
					if (TWCloseDSM(NULL))
					{
					//	CheckSpecialMenu(hWnd, TW_APP_CLOSESM);
					}
				}
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		
		/*
		* if the source manager is open
		*/
		if (TWIsDSMOpen())
		{
		//	Message = ::MessageBox (NULL, "Unload and close the Source Manager?",
		//		"Close message", MB_OKCANCEL);
			if (Message == IDOK)
			{
				if (TWCloseDSM(NULL))
				{
				//	CheckSpecialMenu(hWnd, TW_APP_CLOSESM);
				}
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		
		/*
		* if nothing is open
		*/
		if (!TWIsDSEnabled() & !TWIsDSOpen() & !TWIsDSMOpen())
		{
			return TRUE;
		}
#endif
		return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CProjectUI drawing

void CProjectUI::DrawColumnHeader(CDC* pDC, CRect& rect, int nColumn)
{
	int x = rect.left+2;
	int y = rect.top+2;

	char* text = NULL;

	switch (nColumn)
	{
	case PANE_NAME:
		{
			x += 14;
			text = "Name";
		}
		break;
		
	case PANE_TYPE:
		{
			text = "Type";
		}
		break;
		
	case PANE_SIZE:
		{
			text = "Size";
		}
		break;
		
	case PANE_DURATION:
		{
			text = "Duration";
		}
		break;
		
	case PANE_PATHNAME:
		{
			text = "Path Name";
		}
		break;
		
	case PANE_COMMENT:
		{
			text = "Comment";
		}
		break;
	}

	if (text) pDC->TextOut(x, y, text);
}

void CProjectUI::DrawColumn(CDC* pDC, CRect& rect, int nColumn)
{
	IProject* pPrj = m_pPrj;
	ASSERT(pPrj);

	pDC->FillSolidRect(&rect, lightColor);

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkColor(lightColor);

	int y = 0;

	y -= 0;//m_vert->GetScrollPos();

#if 0
	IFootage* pParentItem = pPrj->m_footageList;
	void* pos = pParentItem->GetFirstChildPos();

	int nextlevel = 0;

	while (pos)
	{
		int level = nextlevel;
		CI2DFootage* pFootage = (CI2DFootage*)pParentItem->Iterate(&pParentItem, &pos, &nextlevel, FALSE);
		ASSERT(pFootage);

		CString str;

		CRect rc2(rect.left, rect.top+y, rect.right, rect.top + y + m_iconHeight);
		CRect rc(rect.left+2, rect.top+y, rect.right-2, rect.top + y + m_iconHeight);

		switch (nColumn)
		{
		case PANE_NAME:
			{
				if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_FOLDERFOOT))
				{
					BOOL bExpanded = pFootage->IsExpanded();
					TransparentBlt(pDC, rc.left+1+level*15, rc.top+3, 10, 10, &m_expandedBitmap, 10*bExpanded, 0, RGB(255,255,255));
				}

				int kind;

				if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_FOLDERFOOT))
				{
					kind = 5;
				}
				else if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_COMPFOOT))
				{
					CComposition* pComp = ((CCompFootage*)pFootage)->m_pComp;

					kind = 0;
				/*
					if (pComp->GetAbsTotalFrames() == 0)	// Audio Only
						kind = 3;
					else if (pComp->m_pVideo->GetWaveFormat())	// Movie
						kind = 1;
					else if (pComp->GetAbsTotalFrames() > 1)	// Video Only
						kind = 1;
					else		// Still Image
						kind = 4;
				*/
				}
				else if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_VIDEOFOOT))
				{
				/*
					CVideoResource* pVideo = (CVideoResource*)pRes;

					if (pVideo->GetAbsTotalFrames() == 0)	// Audio Only
						kind = 3;
					else if (sVid->HasAudio(pVideo->m_pVideo))	// Movie
						kind = 1;
					else if (pVideo->GetAbsTotalFrames() > 1)	// Video Only
						kind = 1;
					else		// Still Image
						kind = 4;
					*/
					kind = 1;
				}

				TransparentBlt(pDC, rc.left + 14 + level*15, rc.top, 18, 18, &m_footageSymbol, kind*18, 0, RGB(255,255,255));

#if 0
				if (pRes->IsKindOf(RUNTIME_CLASS(CComposition)))
				{
					CComposition* pComp = (CComposition*)pRes;
					str = pComp->GetName();
				}
				else
				{
					str = pRes->GetName();
				}
				
#endif
			//	char name[256];
			//	sLayer->GetLayerTags((MMLayerRef)pFootage->m_targetRef, (LAYER_Name), name, (TAG_DONE));

				CRect rc2(rc.left + 14 + 22 + level*15, rc.top, rc.right, rc.bottom);
				pDC->DrawText(pFootage->GetName(), &rc2, DT_END_ELLIPSIS | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
			}
			break;

			case PANE_TYPE:
				{
					if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_FOLDERFOOT))
					{
						str = "Folder";
					}
					else if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_COMPFOOT))
					{
						CCompFootage* pFoot = (CCompFootage*)TARGETDATA(pFootage->m_targetRef, CLASS_COMPFOOT);
						CIVideo* pVideo = pFoot->GetVideoData();
						CIAVideoFile* pFile = pVideo->GetVideoFile();

						if (!pFile)
						{
							str = "Composition";
						}
						else
						{
							CIFileType* pFileType = pFile->GetFileType();
							if (pFileType)
							{
								str = pFileType->GetDescr();
							}

							if (pVideo->IsNumbered())
							{
								str += " Sequence";
							}
						}
					}

					pDC->DrawText((LPCTSTR)str, &rc, DT_END_ELLIPSIS | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
				}
				break;

			case PANE_DURATION:
				{
					if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_COMPFOOT))
					{
						CCompFootage* pFoot = (CCompFootage*)TARGETDATA(pFootage->m_targetRef, CLASS_COMPFOOT);
						CIVideo* pVideo = pFoot->GetVideoData();
						ASSERT(pVideo);

						double duration = 0;
						if (pVideo->GetTotalFrames() > 1)
						{
							duration = (double)pVideo->GetTotalFrames()*1000 / pFoot->m_pComp->GetFrameRate();
						}

						if (duration > 0)
						{
							char buf[26];
							FormatTime(buf, duration, 30);
							pDC->DrawText(buf, &rc, DT_END_ELLIPSIS | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
						}
					}
				}
				break;

			case PANE_SIZE:
				{
					if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_COMPFOOT))
					{
						CCompFootage* pFoot = (CCompFootage*)TARGETDATA(pFootage->m_targetRef, CLASS_COMPFOOT);
						CIVideo* pVideo = pFoot->GetVideoData();
						ASSERT(pVideo);

						CIAVideoFile* pFile = pVideo->GetVideoFile();
						if (pFile)
						{
							DWORD fileSize = 0;

							pFile->GetFileTags(
								(FILE_FileSize), &fileSize,
								(TAG_DONE));

							str.Format("%d K", fileSize >> 10);
							pDC->DrawText((LPCTSTR)str, &rc, DT_END_ELLIPSIS | DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
						}
					}
				}
				break;

			case PANE_PATHNAME:
				{
					if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_COMPFOOT))
					{
						CCompFootage* pFoot = (CCompFootage*)TARGETDATA(pFootage->m_targetRef, CLASS_COMPFOOT);
						CIVideo* pVideo = pFoot->GetVideoData();
						ASSERT(pVideo);

						if (pVideo->HasFile())
						{
							LPCTSTR pathname = pVideo->GetFileName();
							pDC->DrawText(pathname, &rc, DT_PATH_ELLIPSIS | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
						}
					}
				}
				break;

			case PANE_COMMENT:
				{
#if 0
				str = pRes->m_comment;
				pDC->DrawText((LPCTSTR)str, &rc, DT_END_ELLIPSIS | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
#endif
				}
				break;
		}

		if (pFootage == pPrj->GetActiveRes())
		{
			InvertRect(pDC->m_hDC, rc2);
		}

		y += m_iconHeight;
	}
#endif
}

#define TEXT_LEFT	74

static int m_thumbHeight = 70;
static int m_headerHeight = 16;

static char* ImageModeStr[22] =
{
	NULL,
	"Monochrome",
	"Indexed 16",
	"Indexed 256",
	"Grayscale",
	"Thousands 15",
	"Thousands 16",
	"Millions",
	"Millions + Alpha",
	"Grayscale 16",
	"Millions",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"CMYK",
};

void CProjectUI::DrawFootageInfo(CDC* pDC)
{
	IProject* pPrj = m_pPrj;
	ASSERT(pPrj);

#if 0
	CI2DFootage* pFootage = pPrj->GetActiveRes();
	if (pFootage)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(grayColor);

		// General info
		pDC->TextOut(68, 2, pFootage->GetName());

		{
			int refcount = pFootage->GetLayerRefCount();
			CString str;
			if (refcount == 1)
				str = "Used 1 time";
			else
				str.Format("Used %d times", refcount);

			pDC->TextOut(TEXT_LEFT+100, 2, str);
		}

		if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_FOLDERFOOT))
		{
			int count = pFootage->CountChildren();

			CString str;
			str.Format("%d items", count);

			pDC->TextOut(TEXT_LEFT, 16, str);
		}
		else if (sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_COMPFOOT))
		{
			CCompFootage* pCompFoot = (CCompFootage*)TARGETDATA(pFootage->m_targetRef, CLASS_COMPFOOT);
			CIVideo* pVideo = pCompFoot->GetVideoData();
			ASSERT(pVideo);

			CIAVideoFile* pFile = pVideo->GetVideoFile();

			int x = 2;
			int y = 4;

			CSize	size;
			size.cx = pVideo->GetWidth();
			size.cy = pVideo->GetHeight();

			double framerate = pCompFoot->m_pComp->GetFrameRate();
			double duration;
			
			if (pVideo->GetTotalFrames() > 1)	// Video
			{
				ASSERT(framerate > 0);
				duration = pVideo->GetTotalFrames() * 1000 / framerate;
			}
			else if (pVideo->GetWaveFormat())	// Audio
			{
				duration = (double)pVideo->GetTotalSamples() * 1000 / pVideo->GetWaveFormat()->nSamplesPerSec;
			}
			else	// Still image
				duration = 0;

			int thumbHeight = m_thumbHeight-4-10;

			if ((size.cx > 0) && (size.cy > 0))	// Has video
			{
				COLORREF bkClr = pDC->GetBkColor();
				pDC->Draw3dRect(2, 2, 64+2, m_thumbHeight, RGB(0, 0, 0), RGB(255, 255, 255));
				pDC->SetBkColor(bkClr);

				// Display Video info (codec)
				if (pFile)
				{
					LPCTSTR vcodec = NULL;
					pFile->GetFileTags((FILE_VideoCodecString), &vcodec, (TAG_DONE));

					CString videoinfo = vcodec;
					pDC->TextOut(TEXT_LEFT, 28+10, videoinfo);
				}

#if 0	// Video thumbnail
				FRAMEPTR pos = pVideo->GetFrameList()->GetHeadPosition();
				ASSERT(pos);

				int width = 64;
				int height = (width*pVideo->GetHeight())/pVideo->GetWidth();

				if (height > thumbHeight)
				{
					height = thumbHeight;
					width = (height*pVideo->GetWidth())/pVideo->GetHeight();
				}

				ASSERT(width <= 64);
				ASSERT(height <= thumbHeight);

				int left = (64-width)/2;
				int top = (thumbHeight-height)/2;

				ImageDef* pBigImage;
				
				pBigImage = pVideo->m_layerList->GetImage();

				if (!pBigImage)
				{
					if (pComp->m_framePos)
					{
						CAnimFrame* pFrame = pComp->GetFrameAt(pComp->m_framePos);
						if (pFrame->m_rgbaImage.data) pBigImage = &pFrame->m_rgbaImage;
					}
				}

				if (pBigImage)
				{
					ImageDef smallImage;
					filterAllocImage(&smallImage, width, height, FALSE);

					ScaleImage(pBigImage, &smallImage);

					BITMAPINFO bmi;
					LPBYTE bits;
					HBITMAP hBitmap;

					if (ImageDefToBitmap(&smallImage, &bmi, hBitmap, bits))
					{
						StretchDIBits(pDC->m_hDC,
							x+left, y+top, width, height,
							0, 0, width, height,
							bits, &bmi,
							DIB_RGB_COLORS, SRCCOPY);

						DeleteObject(hBitmap);
					}

					filterFreeImage(&smallImage);
				}
#endif
			}

			if (duration > 0)
			{
				CString str;

				if ((size.cx > 0) && (size.cy > 0))	// Video
				{
					char buf[26];
					FormatTime(buf, duration, framerate);
					
					str.Format("Duration: %s - %.2f (fps)", buf, framerate);
				}
				else	// Only Audio
				{
					str.Format("Duration: %.2f (secs)", duration/1000);
				}

				pDC->TextOut(TEXT_LEFT, 28, str);
			}

			if (pVideo->GetWaveFormat())	// Has Audio
			{
				CString audioformat;
				CString audioinfo;

			// Audio format
				audioformat.Format("%d, %d, %s",
					pVideo->GetWaveFormat()->nSamplesPerSec,
					pVideo->GetWaveFormat()->wBitsPerSample,
					(pVideo->GetWaveFormat()->nChannels == 1)? "mono": "stereo");

			// Audio info (codec)
				if (pFile)
				{
					LPCTSTR acodec = NULL;
					pFile->GetFileTags((FILE_AudioCodecString), &acodec, (TAG_DONE));

					audioinfo = acodec;
				}

				CString full;
				full.Format("%s - %s", audioformat, audioinfo);
				pDC->TextOut(TEXT_LEFT, y+thumbHeight-4, full);

			// Draw Waveform thumbnail
				CDC dc;
				dc.CreateCompatibleDC(NULL);
				CBitmap* pOldBitmap = (CBitmap*)dc.SelectObject(&m_audioBitmap);

				pDC->BitBlt(x, y+thumbHeight, 64, 10, &dc, 0, 0, SRCCOPY);

				dc.SelectObject(pOldBitmap);
			}
		}
	}
#endif
}

LRESULT CProjectUI::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC wdc(m_hWnd);
	CDC* pDC = &wdc;

	CFontHandle pOldFont = pDC->GetCurrentFont();
	pDC->SelectFont(m_font);

	CRect client;
	GetClientRect(&client);

	pDC->FillSolidRect(0, 0, client.right, m_thumbHeight, grayColor);
	pDC->Draw3dRect(0, 0, client.right, m_thumbHeight, lightColor, darkGrayColor);
	DrawFootageInfo(pDC);

	{
		CDC	dc;
		dc.CreateCompatibleDC(wdc);
		CBitmapHandle pOldBitmap = dc.SelectBitmap(m_buttonsBitmap);

		for (int n = 0; n < 3; n++)
		{
			int x = n*24;
			int y = client.bottom-16;

			if ((m_dragging == DRAG_BUTTON) && (m_whichButton == n) && m_bWasInside)
			{
				pDC->Draw3dRect(x, y, 24, 16, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));

				pDC->BitBlt(x+2+1, y+2+1, 20, 12, dc, n*20, 0, SRCCOPY);
			}
			else
			{
				pDC->Draw3dRect(x, y, 24, 16, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
				pDC->Draw3dRect(x+1, y+1, 22, 14, lightColor, darkGrayColor);

				pDC->BitBlt(x+2, y+2, 20, 12, dc, n*20, 0, SRCCOPY);
			}
		}

		dc.SelectBitmap(pOldBitmap);
	}

	CPoint org;
	org.x = 0;//-m_horz->GetScrollPos();
	org.y = 0;//-m_horz.GetScrollPos();
	CPoint oldOrg = pDC->SetViewportOrg(org);

	CRect	clip;
	pDC->GetClipBox(&clip);

	CRect	paneRect;
	paneRect.top = m_thumbHeight+m_headerHeight;
	paneRect.bottom = client.bottom-16;
	paneRect.left = 0;

	for (int n = 0; n < m_numColumns; n++)
	{
		if (m_column[n].m_bVisible)
		{
			paneRect.right = paneRect.left + m_column[n].m_width;

			CRect headerRect(paneRect.left, m_thumbHeight, paneRect.right, m_thumbHeight+m_headerHeight);

			pDC->FillSolidRect(&headerRect, grayColor);
			DrawColumnHeader(pDC, headerRect, n);

			pDC->Draw3dRect(headerRect.left, headerRect.top, headerRect.Width(), headerRect.Height(), GetSysColor(COLOR_3DHILIGHT), darkGrayColor);
			pDC->Draw3dRect(headerRect.left+1, headerRect.top+1, headerRect.Width()-2, headerRect.Height()-2, GetSysColor(COLOR_3DHILIGHT), darkGrayColor);

			if (m_column[n].m_bSizeable)
			{
				pDC->Draw3dRect(headerRect.right-6, headerRect.top+2, 4, headerRect.Height()-4, GetSysColor(COLOR_3DHILIGHT), darkGrayColor);
				pDC->Draw3dRect(headerRect.right-5, headerRect.top+3, 2, headerRect.Height()-5, GetSysColor(COLOR_3DHILIGHT), darkGrayColor);
			}

			CRect columnClip;

			if (columnClip.IntersectRect(&clip, &paneRect))
			{
				int state = pDC->SaveDC();

				pDC->IntersectClipRect(&columnClip);

				DrawColumn(pDC, paneRect, n);

				pDC->RestoreDC(state);
			}

		// Dividing line
		//	pDC->MoveTo(paneRect.right-1, paneRect.top);
		//	pDC->LineTo(paneRect.right-1, paneRect.bottom);

			paneRect.left += m_column[n].m_width;
		}
	}

//	pDC->FillSolidRect(paneRect.right, paneRect.top-m_headerHeight, client.right-paneRect.right, paneRect.Height()+m_headerHeight, lightColor);

	pDC->SetViewportOrg(oldOrg);

	pDC->SelectFont(pOldFont);

	return 0;
}

#if 0
BOOL CProjectUI::CanCloseFrame()
{
	int ret = MessageBox(GetMainHwnd(), "You have made changes to this Project\nSave?", "2DAnimator", MB_YESNOCANCEL);

	if (ret == IDCANCEL) return FALSE;

	if (ret == IDYES)
	{
		if (FALSE)	// Try to save
		{
			return FALSE;
		}
	}

	return TRUE;
}
#endif

LRESULT CProjectUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	HINSTANCE hOldInst = AfxGetResourceHandle();
	AfxSetResourceHandle(g_hInst);
	*/

//	DragAcceptFiles(TRUE);

	m_font.CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
//	SetWindowFont(GetHwnd(), &m_font);
//	SendMessage(GetHwnd(), WM_SETFONT, (WPARAM)(HFONT)m_font, 0);

	m_footageSymbol.LoadBitmap(IDB_FOOTAGESYMBOL);
	m_expandedBitmap.LoadBitmap(IDB_EXPANDED);
	m_audioBitmap.LoadBitmap(IDB_AUDIOTHUMB);
	m_buttonsBitmap.LoadMappedBitmap(IDB_PROJECTBUTTONS);

//	AfxSetResourceHandle(hOldInst);

	m_sizeGrip.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD | CCS_NODIVIDER | CCS_NORESIZE | SBARS_SIZEGRIP, 0);

#if 0
	m_horz = (CIUIScrollBar*)sBasic->CreateCmdTarget(IID_UISCROLLBAR);
	m_vert = (CIUIScrollBar*)sBasic->CreateCmdTarget(IID_UISCROLLBAR);
	m_horz->CreateControlTags(this, (CTLSCRL_Dir), 0, (TAG_DONE));
	m_vert->CreateControlTags(this, (CTLSCRL_Dir), 1, (TAG_DONE));
#endif

	SetWindowPos(NULL, 0, 0, 300, 200, SWP_NOZORDER | SWP_NOMOVE);

	return 0;
}

LRESULT CProjectUI::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	m_horz->Release();
	m_vert->Release();
	m_horz = m_vert = NULL;
#endif

	m_font.DeleteObject();

	m_footageSymbol.DeleteObject();
	m_expandedBitmap.DeleteObject();
	m_audioBitmap.DeleteObject();
	m_buttonsBitmap.DeleteObject();

	return 0;
}

LRESULT CProjectUI::OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

#if 0
void CProjectUI::OnScroll(UINT nSBCode, UINT nPos, CIUIScrollBar* pScrollBar)
{
	if (pScrollBar->TOP() == m_horz)
	{
		SCROLLINFO	sif = {0};
		sif.cbSize = sizeof(sif);
		pScrollBar->GetScrollInfo(&sif, SIF_PAGE|SIF_RANGE);
		
		int minr = sif.nMin;
		int page = sif.nPage;
		int maxr = pScrollBar->GetScrollLimit();//sif.nMax;
		int oldPos = pScrollBar->GetScrollPos();
		int pos;
		
		switch (nSBCode)
		{
		case SB_LINEUP:			pos = oldPos-m_iconHeight;	break;
		case SB_LINEDOWN:			pos = oldPos+m_iconHeight;	break;
		case SB_PAGEUP:			pos = oldPos-page;	break;
		case SB_PAGEDOWN:			pos = oldPos+page;	break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:	pos = nPos; break;
		}
		
		if (nSBCode != SB_ENDSCROLL)
		{
			if (pos < minr) pos = minr;
			else if (pos > maxr) pos = maxr;
			
			CRect	client;
			GetClientRect(&client);
			
			CRect rect(0, m_thumbHeight,
				client.Width() - GetSystemMetrics(SM_CXVSCROLL), client.bottom-16);
			
			pScrollBar->SetScrollPos(pos, (nSBCode != SB_THUMBTRACK));
			ScrollWindow(GetHwnd(), oldPos-pos, 0, &rect, &rect);
		}
	}
	else if (pScrollBar->TOP() == m_vert->TOP())
	{
		SCROLLINFO	sif = {0};
		sif.cbSize = sizeof(sif);
		pScrollBar->GetScrollInfo(&sif, SIF_PAGE|SIF_RANGE);
		
		int minr = sif.nMin;
		int page = sif.nPage;
		int maxr = pScrollBar->GetScrollLimit();//sif.nMax;
		int oldPos = pScrollBar->GetScrollPos();
		int pos;
		
		switch (nSBCode)
		{
		case SB_LINEUP:			pos = oldPos-m_iconHeight;	break;
		case SB_LINEDOWN:			pos = oldPos+m_iconHeight;	break;
		case SB_PAGEUP:			pos = oldPos-page;	break;
		case SB_PAGEDOWN:			pos = oldPos+page;	break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:	pos = nPos; break;
		}
		
		if (nSBCode != SB_ENDSCROLL)
		{
			if (pos < minr) pos = minr;
			else if (pos > maxr) pos = maxr;
			
			CRect	client;
			GetClientRect(&client);
			CRect rect(0, m_thumbHeight+m_headerHeight,
				client.Width() - GetSystemMetrics(SM_CXVSCROLL), client.bottom-16);
			
			pScrollBar->SetScrollPos(pos, (nSBCode != SB_THUMBTRACK));
			ScrollWindow(GetHwnd(), 0, oldPos-pos, &rect, &rect);
		}
	}
}
#endif

LRESULT CProjectUI::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	Invalidate();

	return 0;
}

void CProjectUI::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int top = m_thumbHeight+m_headerHeight;

	int cx = client.Width();
	int cy = client.Height();

	int	sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int	sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	m_sizeGrip.MoveWindow(cx-sbWidth, cy-sbHeight-2, sbWidth, sbHeight+2, TRUE);

#if 0
	m_horz->MoveWindow(24*3, cy-16, cx-24*3-sbWidth, 16);
	m_vert->MoveWindow(cx-sbWidth, top, sbWidth, cy-top-16);
#endif

	ResetVScrollSize();
	ResetHScrollSize();
}

void CProjectUI::ResetVScrollSize()
{
	ASSERT(m_pPrj);
	if (!m_hWnd) return;

	CRect client;
	GetClientRect(&client);

	int top = m_thumbHeight+m_headerHeight;

	int numItems = 0;
#if 0
	IFootage* pParentItem = (CIFootage*)m_pPrj->m_footageList;
	void* pos = pParentItem->GetFirstChildPos();
	int	nextlevel = 0;
	while (pos)
	{
		int level = nextlevel;
		CI2DFootage* pRes = (CI2DFootage*)pParentItem->Iterate(&pParentItem, &pos, &nextlevel, FALSE);
		numItems++;
	}
#endif
	int range = numItems*m_iconHeight;

#if 0
	m_vert->TOP()->SetControlTags(
		(CTLSCRL_Min), 0,
		(CTLSCRL_Max), range,
		(CTLSCRL_Visible), client.Height()-top-16,
		(TAG_DONE));
#endif
}

void CProjectUI::ResetHScrollSize()
{
	CRect client;
	GetClientRect(&client);

	int nWidth = 0;

	for (int n = 0; n < m_numColumns; n++)
	{
		if (m_column[n].m_bVisible)
		{
			nWidth += m_column[n].m_width;
		}
	}

	int range = nWidth;

/*
	SCROLLINFO info;
	info.fMask = SIF_PAGE|SIF_RANGE|SIF_DISABLENOSCROLL;
	info.nMin = 0;
	info.nMax = range;
	info.nPage = client.Width();

	m_horz.SetScrollInfo(&info, TRUE);
*/
#if 0
	m_horz->TOP()->SetControlTags(
		(CTLSCRL_Min), 0,
		(CTLSCRL_Max), range,
		(CTLSCRL_Visible), client.Width(),
		(TAG_DONE));
#endif
}

LRESULT CProjectUI::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;
	int nButton = 0;
	BOOL bDblClk = FALSE;

	IProject* pPrj = m_pPrj;
	ASSERT(pPrj);

	CRect client;
	GetClientRect(&client);

	if (!m_dragging)
	{
		EndEdit();

		if (point.y > (client.bottom - 16))
		{
			m_dragging = DRAG_BUTTON;

			m_bWasInside = FALSE;
			m_whichButton = point.x/24;

			CRect client;
			GetClientRect(&client);

			m_buttonRect.SetRect(m_whichButton*24, client.bottom-16, m_whichButton*24+23, client.bottom);
		}
		else if (point.y < 20/*m_thumbHeight*/)
		{
#if 0
			IFootage* pRes = pPrj->GetActiveRes();
			if (pRes)
			{
				CIMenuItem*	pMenu = (CIMenuItem*)sBasic->CreateCmdTarget(IID_MENUITEM);

				CArray <CI2DLayer*, CI2DLayer*> arr;

				int i = 0;
				void* pos = pRes->GetFirstAttachedLayerPos();
				
				while (pos)
				{
					CI2DLayer* pLayer = (CI2DLayer*)pRes->GetNextAttachedLayer(&pos)->TOP();
					CComposition* pComp = (CComposition*)pLayer->GetComposition();

					CString str;
					str.Format("%s in %s", pLayer->GetName(), pComp->m_pFootage->GetName());

					UINT nFlags = 0;
					pMenu->AppendItem(nFlags, i+1, str);
					
					arr.Add(pLayer);
				}

				CPoint pt(64, 16);
				ClientToScreen(&pt);

				int id = pMenu->PopupMenu(this, pt,
					TPM_LEFTBUTTON | TPM_RIGHTBUTTON | /*TPM_NONOTIFY |*/ TPM_RETURNCMD);
				pMenu->Release();

				if (id > 0)
				{
					CComposition* pComp = (CComposition*)(arr[id-1]->GetComposition())->TOP();
					pComp->ShowViews();
				}
			}
#endif
		}
		else if (point.y < m_thumbHeight + m_headerHeight)
		{
			if (nButton == 0)
			{
				int x = 0;

				for (int i = 0; i < m_numColumns; i++)
				{
					if (m_column[i].m_bVisible)
					{
						x += m_column[i].m_width;

						if (m_column[i].m_bSizeable)
						{
							if (abs(point.x-(x-4)) < 4)
							{
								m_dragging = DRAG_SIZEPANE;
								m_whichPane = i;
								break;
							}
						}
					}
				}
			}
			else if (nButton == 1)
			{
#if 0
				CMenu	menu;
				menu.LoadMenu(IDR_FOOTAGEPANE);

				CPoint pt = point;
				ClientToScreen(&pt);

				menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
					pt.x, pt.y, AfxGetMainWnd());
#endif
			}
		}
		else
		{
			if (bDblClk)	// Double-click, open (composition) views
			{
#if 0
				if (pPrj->GetActiveRes())
				{
					if (pPrj->GetActiveRes() &&
						sBasic->IsTargetKindOf(pPrj->GetActiveRes()->m_targetRef, CLASS_COMPFOOT))
					{
						CCompFootage* pFootage = (CCompFootage*)TARGETDATA(pPrj->GetActiveRes()->m_targetRef, CLASS_COMPFOOT);
						CComposition* pComp = pFootage->m_pComp;
						ASSERT(pComp);
						
					//	if (pComp->GetAbsTotalFrames() > 0)
						{
							pComp->ShowViews();
						}
					}
				}
#endif
			}
			else
			{
				int pane = -1;
				int left = 0;
				int i;

				for (i = 0; i < m_numColumns; i++)
				{
					if (m_column[i].m_bVisible)
					{
						left += m_column[i].m_width;
						
						if (point.x < left)
						{
							pane = i;
							break;
						}
					}
				}
				
				IFootage* pRes = NULL;
#if 0
				pRes = GetFootageUnderPoint(point);
				CPoint pt = point;
				pt.y -= m_thumbHeight + m_headerHeight;
				pt.y += m_vert->GetScrollPos();
				int index = pt.y/m_iconHeight;
				
				if (nButton == 0)
				{
					if (pane == PANE_NAME && pt.x < left-m_column[PANE_NAME].m_width+14)
					{
						if (pRes && sBasic->IsTargetKindOf(pRes->m_targetRef, CLASS_FOLDERFOOT))
						{
							pRes->SetExpanded(!pRes->IsExpanded());
							InvalidateRect(NULL, TRUE);
						}
					}
					else
					{
						if (pRes != pPrj->GetActiveRes())
						{
							if (pRes)
							{
								ASSERT(sBasic->IsTargetKindOf(pRes->m_targetRef, "2dfootage"));

								CIObjectReference*	pRef = (CIObjectReference*)sBasic->CreateCmdTarget(IID_OBJECTREFERENCE);
								pRef->PutReference(pRes->GetObject(), pPrj->m_footageList->GetObject());
								
								CIActionDescriptor* pDescr = (CIActionDescriptor*)sBasic->CreateCmdTarget(IID_ACTIONDESCRIPTOR);
								pDescr->PutReference('ref ', pRef);
								
								pPrj->DispatchAction(kEventSetActiveFootage, 1, 1, pDescr);
								
								pDescr->Release();
							}
							else
							{
								pPrj->DispatchAction(kEventSetActiveFootage, 1, 1, NULL);
							}
						}
						
						if (pPrj->GetActiveRes())
						{
							if (pane == PANE_COMMENT)
							{
							/*
							CRect client;
							GetClientRect(&client);
							
							  int top = m_thumbHeight + m_headerHeight + index*m_iconHeight;
							  left -= m_column[PANE_COMMENT].m_width;
							  
								 CRect rect(left, top+3, client.right-16, top+m_iconHeight-2);
								 m_edit.Create(WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, rect, this, 1);
								 m_edit.SetFont(&m_font);
								 m_edit.SetWindowText(pDoc->m_pPrj->GetActiveRes()->m_comment);
								 m_edit.SetSel(0, -1);
								 m_edit.SetFocus();
								*/
							}
							else
							{
								COleDataSource source;
								UINT nFormat = RegisterClipboardFormat("MMStudio-Footage");
							
								HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, 4);
							  
								CI2DFootage** pData = (CI2DFootage**)GlobalLock(hData);
								*pData = pPrj->GetActiveRes();
								 
								GlobalUnlock(hData);

								source.CacheGlobalData(nFormat, hData, NULL);

								if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
								{
								}

								source.Empty();
											
								GlobalFree(hData);
							}
						}
					}
				}
#endif
			}
		}
	}

	if (m_dragging)
	{
		SetCapture();
#if 0
		OnMouseMove(nFlags, point);
#endif
	}

	return 0;
}

LRESULT CProjectUI::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	IProject* pPrj = m_pPrj;
	ASSERT(pPrj);

	if (m_dragging)
	{
		ReleaseCapture();

		int dragging = m_dragging;
		m_dragging = 0;

		if (dragging == DRAG_BUTTON)
		{
			if (m_buttonRect.PtInRect(point))
			{
				InvalidateRect(m_buttonRect, TRUE);
				UpdateWindow();

#if 0
				switch (m_whichButton)
				{
				case 0:	// New Folder
					{
						pPrj->DispatchAction(kEventNewFolder, 1, 1, NULL);
					}
					break;

				case 1:	// New Composition
					{
						pPrj->DispatchAction(kEventNewComposition, 1, 1, NULL);
					}
					break;

				case 2:	// Delete Footage
					{
						pPrj->DispatchAction(kEventDeleteFootage, 1, 1, NULL);
					}
					break;
				}
#endif
			}
		}
		else if (dragging == DRAG_SIZEPANE)
		{
			InvalidateRect(NULL, TRUE);
		}
		else if (dragging == DRAG_ORDERPANE)
		{
			InvalidateRect(NULL, TRUE);
		}
	}

	return 0;
}

LRESULT CProjectUI::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

//	CMovieDoc* pDoc = (CMovieDoc*)GetDocument();
//	ASSERT(pDoc);

	if (m_dragging)
	{
		if (m_dragging == DRAG_BUTTON)
		{
			BOOL bInside = m_buttonRect.PtInRect(point);

			if (bInside != m_bWasInside)
			{
				m_bWasInside = bInside;
				InvalidateRect(&m_buttonRect, TRUE);
			}
		}
		else if (m_dragging == DRAG_SIZEPANE)
		{
			int x = 0;
			for (int i = 0; i < m_whichPane; i++)
			{
				if (m_column[i].m_bVisible)
				{
					x += m_column[i].m_width;
				}
			}

			int newwidth = point.x+3 - x;
			if (newwidth < 20) newwidth = 20;
			else if (newwidth > 320) newwidth = 320;

			if (m_column[m_whichPane].m_width != newwidth)
			{
				m_column[m_whichPane].m_width = newwidth;

				CRect client; GetClientRect(&client);
				OnSize();
				CRect rc(0, m_thumbHeight, client.right, m_thumbHeight+m_headerHeight);
				InvalidateRect(&rc, TRUE);
			}
		}
	}

	return 0;
}

IFootage* CProjectUI::GetFootageUnderPoint(CPoint point)
{
	IProject* pPrj = m_pPrj;
	ASSERT(pPrj);

	CPoint pt = point;
	pt.y -= m_thumbHeight + m_headerHeight;
	pt.y += 0;//m_vert->GetScrollPos();
	int index = pt.y/m_iconHeight;

	IFootage* pRes = NULL;

#if 0
	int i = 0;

	CIFootage* pParentItem = (CIFootage*)pPrj->m_footageList;
	void* pos = pParentItem->GetFirstChildPos();
	int	nextlevel = 0;

	while (pos)
	{
		C2DFootage* pFoot = (C2DFootage*)pParentItem->Iterate(&pParentItem, &pos, &nextlevel, FALSE);
		ASSERT(pFoot);

		if (index == i)
		{
			pRes = pFoot;
			break;
		}

		i++;
	}
#endif

	return pRes;
}

LRESULT CProjectUI::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	if (nHitTest == HTCLIENT)
	{
		CPoint	point;
		::GetCursorPos(&point);
		ScreenToClient(&point);

		if ((point.y >= m_thumbHeight) && (point.y < m_thumbHeight + m_headerHeight))
		{
			int x = 0;

			for (int n = 0; n < m_numColumns; n++)
			{
				if (m_column[n].m_bVisible)
				{
					x += m_column[n].m_width;

					if (m_column[n].m_bSizeable)
					{
						if (abs(point.x-(x-4)) < 4)
						{
							::SetCursor(AfxGetApp()->LoadCursor(IDC_SMALL_SIZEWE));
							return TRUE;
						}
					}
				}
			}
		}
	}
#endif
	return FALSE;
}

LRESULT CProjectUI::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CPoint winpoint = point;
	ScreenToClient(&winpoint);

	if (winpoint.y < 20)
	{
	}
	else if (winpoint.y < m_thumbHeight + m_headerHeight)
	{
#if 0
		CIMenuItem* pMenu = (CIMenuItem*)sBasic->CreateCmdTarget(IID_MENUITEM);

		pMenu->LoadMenu(g_hInst, IDR_PROJECTPANES);
		pMenu->GetSubMenu(0)->PopupMenu(this, point, 0);
		pMenu->Release();
#endif
		return 0;
	}
	else if (winpoint.y > m_thumbHeight)
	{
#if 0
		CIMenuItem* pMenu = (CIMenuItem*)sBasic->CreateCmdTarget(IID_MENUITEM);

		pMenu->LoadMenu(g_hInst, IDR_FOOTAGEPOPUP);
		pMenu->GetSubMenu(0)->PopupMenu(this, point, 0);
		pMenu->Release();
#endif

		return 0;
	}

	return 0;
}

void CProjectUI::EndEdit()
{
	if (m_edit.m_hWnd)
	{
	/*
		CMovieDoc* pDoc = (CMovieDoc*)GetDocument();

		if (pDoc->m_pPrj->GetActiveRes())
		{
			CString str;
			m_edit.GetWindowText(str);
			
			CActionDescriptor* pDescr = new CActionDescriptor;
			pDescr->PutString(keyName, str);
			pDoc->m_pPrj->GetActiveRes()->DispatchAction(kEventSetFootageComment, 1, 1, pDescr);
		}
	*/
		
		m_edit.DestroyWindow();
	}
}

#if 0
DROPEFFECT CProjectUI::OnDragEnter(LPDATAOBJECT lpDataObject, DWORD dwKeyState, POINT point)
{
	return DROPEFFECT_MOVE;
}

DROPEFFECT CProjectUI::OnDragOver(LPDATAOBJECT lpDataObject, DWORD dwKeyState, POINT point) 
{
	return DROPEFFECT_MOVE;
}

BOOL CProjectUI::OnDrop(LPDATAOBJECT lpDataObject, DROPEFFECT dropEffect, POINT point) 
{
	COleDataObject dataobject;
	dataobject.Attach(lpDataObject, FALSE);
	COleDataObject* pDataObject = &dataobject;

	CMMProject* pPrj = m_pPrj;
	ASSERT(pPrj);

	UINT nFormat = RegisterClipboardFormat("MMStudio-Footage");

	if (pDataObject->IsDataAvailable(nFormat))	// Dragged Footage
	{
		HGLOBAL hData = pDataObject->GetGlobalData(nFormat);

		C2DFootage** pData = (C2DFootage**)GlobalLock(hData);
		C2DFootage* pRes = *pData;

		GlobalUnlock(hData);

		C2DFootage* pFootage = GetFootageUnderPoint(point);
		if (!pFootage)
		{
			pFootage = (C2DFootage*)pPrj->m_footageList;
		}

		if (pFootage && sBasic->IsTargetKindOf(pFootage->m_targetRef, CLASS_FOLDERFOOT))
		{
			if (!pRes->IsDescendant(pFootage))
			{
				CIActionDescriptor* pDescr = (CIActionDescriptor*)sBasic->CreateCmdTarget(IID_ACTIONDESCRIPTOR);

				if (pFootage->TOP() != pPrj->m_footageList->TOP())
				{
					CIObjectReference* pRef = (CIObjectReference*)sBasic->CreateCmdTarget(IID_OBJECTREFERENCE);
					pRef->PutReference(pFootage->GetObject(), pPrj->m_footageList->GetObject());

					pDescr->PutReference('ref ', pRef);

					pPrj->DispatchAction(kEventArrangeFootage, 1, 1, pDescr);

				//	sBasic->DestroyCmdTarget(pRef); ???
				}
				else
				{
					pPrj->DispatchAction(kEventArrangeFootage, 1, 1, pDescr);
				}

				pDescr->Release();

				return TRUE;
			}
		}
	}

	return FALSE;
}

void CProjectUI::OnDropFiles(HDROP hDropInfo) 
{
//	POINT pt;
//	BOOL bInClientArea = DragQueryPoint(hDropInfo, &pt);

	int count = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

//	CString msg;
//	msg.Format("%d", count);
//	AfxMessageBox(msg);

	for (int i = 0; i < count; i++)
	{
		TCHAR pathname[512];
		::DragQueryFile(hDropInfo, i, pathname, sizeof(pathname));

		m_pPrj->ImportFootage(pathname);
	}

	::DragFinish(hDropInfo);
}
#endif

BEGIN_CMD_MAP(CProjectUI)
/*
	CMD_HANDLER(&ID_FILES_HOMEPAGE, OnFileSetasHomepage)
	CMD_UPDATE(&ID_FILES_HOMEPAGE, OnFileSetasHomepageUpdate)
	CMD_HANDLER(&ID_FILES_NEWFOLDER, OnFileNewFolder)
*/
END_CMD_MAP()

LRESULT CProjectUI::OnFootagepaneName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
{
	m_column[PANE_NAME].m_bVisible = !m_column[PANE_NAME].m_bVisible;
	ResetHScrollSize();
	Invalidate();

	return 0;
}

LRESULT CProjectUI::OnFootagepaneDuration(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
{
	m_column[PANE_DURATION].m_bVisible = !m_column[PANE_DURATION].m_bVisible;
	ResetHScrollSize();
	Invalidate();

	return 0;
}

LRESULT CProjectUI::OnFootagepanePathname(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
{
	m_column[PANE_PATHNAME].m_bVisible = !m_column[PANE_PATHNAME].m_bVisible;
	ResetHScrollSize();
	Invalidate();

	return 0;
}

LRESULT CProjectUI::OnFootagepaneSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
{
	m_column[PANE_SIZE].m_bVisible = !m_column[PANE_SIZE].m_bVisible;
	ResetHScrollSize();
	Invalidate();

	return 0;
}

LRESULT CProjectUI::OnFootagepaneType(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
{
	m_column[PANE_TYPE].m_bVisible = !m_column[PANE_TYPE].m_bVisible;
	ResetHScrollSize();
	Invalidate();

	return 0;
}

LRESULT CProjectUI::OnFootagepaneComment(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
{
	m_column[PANE_COMMENT].m_bVisible = !m_column[PANE_COMMENT].m_bVisible;
	ResetHScrollSize();
	Invalidate();

	return 0;
}

void CProjectUI::OnUpdateFootagepaneName(long iid, IUICmdUpdate* pCmdUI) 
{
	pCmdUI->SetCheck(m_column[PANE_NAME].m_bVisible);
}

void CProjectUI::OnUpdateFootagepaneType(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_column[PANE_TYPE].m_bVisible);
}

void CProjectUI::OnUpdateFootagepaneDuration(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_column[PANE_DURATION].m_bVisible);
}

void CProjectUI::OnUpdateFootagepaneSize(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_column[PANE_SIZE].m_bVisible);
}

void CProjectUI::OnUpdateFootagepanePathname(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_column[PANE_PATHNAME].m_bVisible);
}

void CProjectUI::OnUpdateFootagepaneComment(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_column[PANE_COMMENT].m_bVisible);
}

#if 0
BOOL CProjectUI::OnCmdMsg(UINT nID, CICmdUIUpdate* pCmdUI)
{
	BOOL bHandled = TRUE;

	if (!pCmdUI)
	{
		switch (nID)
		{
		case ID_FOOTAGEPANE_NAME:
			OnFootagepaneName();
			break;
			
		case ID_FOOTAGEPANE_TYPE:
			OnFootagepaneType();
			break;
			
		case ID_FOOTAGEPANE_DURATION:
			OnFootagepaneDuration();
			break;
			
		case ID_FOOTAGEPANE_SIZE:
			OnFootagepaneSize();
			break;
			
		case ID_FOOTAGEPANE_PATHNAME:
			OnFootagepanePathname();
			break;
			
		case ID_FOOTAGEPANE_COMMENT:
			OnFootagepaneComment();
			break;
			
		default:
			bHandled = FALSE;
		}
	}
	else
	{
		switch (nID)
		{
		case ID_FOOTAGEPANE_NAME:
			OnUpdateFootagepaneName(pCmdUI);
			break;
			
		case ID_FOOTAGEPANE_TYPE:
			OnUpdateFootagepaneType(pCmdUI);
			break;
			
		case ID_FOOTAGEPANE_DURATION:
			OnUpdateFootagepaneDuration(pCmdUI);
			break;
			
		case ID_FOOTAGEPANE_SIZE:
			OnUpdateFootagepaneSize(pCmdUI);
			break;
			
		case ID_FOOTAGEPANE_PATHNAME:
			OnUpdateFootagepanePathname(pCmdUI);
			break;
			
		case ID_FOOTAGEPANE_COMMENT:
			OnUpdateFootagepaneComment(pCmdUI);
			break;

		default:
			bHandled = FALSE;
		}
	}

	if (!bHandled)	// Try project
	{
		bHandled = m_pPrj->TOP()->OnCmdMsg(nID, pCmdUI);
	}

	if (!bHandled)
	{
		bHandled = SUB()->OnCmdMsg(nID, pCmdUI);
	}

	return bHandled;
}
#endif