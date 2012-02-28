//
// Copyright (c) 2001, Sigurd Lerstad. All rights reserved
//

#include "stdafx.h"
#include "LXMLEditor.h"
#include "HTMDocumentFrames.h"

/*
#include "FrameUI.h"

#include "HTMSourceUI.h"
#include "HTMLayoutUI.h"
#include "HTMPreviewUI.h"
#include "HTMElementUI.h"
#include "HTMTimelineUI.h"
#include "HTMFramesDesignUI.h"
*/

#if 0
CUString GetCommaSeperatedString(LPCSTR str, int index)
{
	CUString out;

	int i = 0;

	LPCTSTR p = str;
	while (*p)
	{
		if (*p == ',')
		{
			i++;
		}
		else
		{
			if (i == index)
				out += CUString(*p);
		}

		p++;
	}

	out.TrimLeft();
	out.TrimRight();

	return out;
}

CHTMDesignFrameSet::~CHTMDesignFrameSet()
{
	UPOSITION pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMDesignFrameNode* pFrame = (CHTMDesignFrameNode*)m_frames.GetNext(pos);
		delete pFrame;
	}

	m_frames.RemoveAll();
}

CHTMDesignFrame::CHTMDesignFrame()
{
	m_type = 1;

//	m_pDocument	= NULL;

//	m_htmTree = NULL;

	m_pFrameSet = NULL;
}

CHTMDesignFrame::~CHTMDesignFrame()
{
}

void CHTMDesignFrameSet::CreateFrames(ILDOMElement* pFrameSetElement)
{
	BSTR bcols; pFrameSetElement->getAttribute(L"cols", &bcols);
	BSTR brows; pFrameSetElement->getAttribute(L"rows", &brows);

	m_cols = bcols;
	m_rows = brows;

	SysFreeString(bcols);
	SysFreeString(brows);

	CComQIPtr<ILDOMElement> pElement;
	pFrameSetElement->get_firstChild((ILDOMNode**)&pElement);

	while (pElement != NULL)
	{
		LDOMNodeType nodeType;
		pElement->get_nodeType(&nodeType);

		if (nodeType == NODE_ELEMENT)
		{
			BSTR tagName;
			pElement->get_tagName(&tagName);

			if (!wcscmp(tagName, L"frameset"))
			{
				CHTMDesignFrameSet* pFrameSet = new CHTMDesignFrameSet;
				pFrameSet->m_pElement = pElement;
				pFrameSet->m_pDocument = m_pDocument;
			//	m_pParentFrame

			//	pFrameSet->m_pUI = m_pUI;
				pFrameSet->m_pParentFrame/*Set*/ = this;
				m_frames.AddTail(pFrameSet);

				pFrameSet->CreateFrames(pElement);	// Recurse
			}
			else if (!wcscmp(tagName, L"frame"))
			{
				CHTMDesignFrame* pFrame = new CHTMDesignFrame;
				pFrame->m_pDocument = m_pDocument;
				pFrame->m_pElement = pElement;

				BSTR name; pElement->getAttribute(L"name", &name);
				BSTR src; pElement->getAttribute(L"src", &src);
				pFrame->m_name = CUString(name);
				pFrame->m_src = CUString(src);

				SysFreeString(name);
				SysFreeString(src);

				pFrame->m_pParentFrame/*Set*/ = this;
				m_frames.AddTail(pFrame);

				/*
			// hmm..
				CHTMDoc* pDoc = new CHTMDoc;
				pDoc->m_pText = new CHTMDocument;
				pDoc->m_pText->m_pHTMDoc = pDoc;
				pFrame->m_pDocument = pDoc;
			// ..

				TCHAR dir[512];
				TCHAR path[512];
				_splitpath(m_pDocument->m_url, dir, path, NULL, NULL);

				CUString fullurl;
				_makepath(fullurl.GetBuffer(512), dir, path, pFrame->m_src, NULL);
				fullurl.ReleaseBuffer();

				pFrame->GotoLocation(fullurl);
			*/
			}

			SysFreeString(tagName);
		}

		CComQIPtr<ILDOMElement> nextSibling;
		pElement->get_nextSibling((ILDOMNode**)&nextSibling);
		pElement = nextSibling;
	}
}

void CHTMDesignFrameSet::PositionFrames(int spacing)
{
	int nframes = m_frames.GetCount();

	if (spacing == -1)
		spacing = 8;

	int totalspacing = (nframes-1)*spacing;

	UPOSITION pos;
	int nframe;

	CArray<int,int> frameSize;
	int nFramesAnySize = 0;
	int totalSize = 0;

	nframe = 0;
	pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMDesignFrame* pFrame = (CHTMDesignFrame*)m_frames.GetNext(pos);

		CUString str_framesize;

		if (!m_cols.IsEmpty())	// Columns
		{
			str_framesize = GetCommaSeperatedString(m_cols, nframe);
		}
		else	// Rows
		{
			str_framesize = GetCommaSeperatedString(m_rows, nframe);
		}

		if (str_framesize.IsEmpty()) str_framesize = "*";

		int size;

		if (((LPCTSTR)str_framesize)[str_framesize.GetLength()-1] == '%')
		{
			int size_pcnt = atol(str_framesize);

			if (!m_cols.IsEmpty())
				size = (m_client.Width() * size_pcnt) / 100;
			else
				size = (m_client.Height() * size_pcnt) / 100;
		}
		else if (((LPCTSTR)str_framesize)[0] != '*')
		{
			size = atol(str_framesize);
		}
		else
		{
			size = 0;
			nFramesAnySize++;
		}

		totalSize += size;
		frameSize.Add(size);

		nframe++;
	}

	nframe = 0;
	pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMDesignFrame* pFrame = (CHTMDesignFrame*)m_frames.GetNext(pos);

		if (frameSize[nframe] == 0)
		{
			if (!m_cols.IsEmpty())
			{
				frameSize[nframe] = (m_client.Width()-totalSize) /  nFramesAnySize;
			}
			else
			{
				frameSize[nframe] = (m_client.Height()-totalSize) /  nFramesAnySize;
			}

			if (frameSize[nframe] < 0) frameSize[nframe] = 0;
		}

		nframe++;
	}

	int offset = 0;

	nframe = 0;
	pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMDesignFrame* pFrame = (CHTMDesignFrame*)m_frames.GetNext(pos);

		int left, top;
		int width, height;

		if (!m_cols.IsEmpty())	// Columns
		{
			left = m_client.left + offset;
			top = m_client.top;
			width = frameSize[nframe];//(m_client.Width()-totalspacing)/nframes;
			height = m_client.Height();
		}
		else	// Rows
		{
			left = m_client.left;
			top = m_client.top + offset;
			width = m_client.Width();
			height = frameSize[nframe];//(m_client.Height()-totalspacing)/nframes;
		}

		pFrame->m_client.SetRect(left, top, left+width, top+height);
		pFrame->PositionFrames(spacing);

		if (!m_cols.IsEmpty())	// Columns
			offset += width+spacing;
		else	// Rows
			offset += height+spacing;

		nframe++;
	}
}

void CHTMDesignFrame::PositionFrames(int spacing)
{
//	OnSize();
}

void CHTMDesignFrameSet::OnPaint(HDC hDC)
{
	CRect clip;
	GetClipBox(hDC, &clip);

	UPOSITION pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMDesignFrameNode* pFrame = (CHTMDesignFrameNode*)m_frames.GetNext(pos);

		CRect irect;
		if (IntersectRect(&irect, &clip, &pFrame->m_client))
		{
			int state = SaveDC(hDC);
			IntersectClipRect(hDC, pFrame->m_client.left, pFrame->m_client.top, pFrame->m_client.right, pFrame->m_client.bottom);

			pFrame->OnPaint(hDC);

			RestoreDC(hDC, state);
		}
	}
}

void CHTMDesignFrame::OnPaint(HDC hDC)
{
	if (m_pFrameSet)
	{
		m_pFrameSet->OnPaint(hDC);
	}
	else
	{
		CRect client = m_client;
		Rectangle(hDC, client.left, client.top, client.right, client.bottom);
		TextOut(hDC, client.left+4, client.top+4, m_src, m_src.GetLength());
	}
}


BOOL CHTMDesignFrame::OnButtonDown(UINT nFlags, POINT abspoint, int iButton, BOOL bDblClk, CHTMDesignFrame** pFrame)
{
	if (m_pFrameSet)
	{
		return m_pFrameSet->OnButtonDown(nFlags, abspoint, iButton, bDblClk, pFrame);
	}
	else
	{
		return FALSE;
	}
}

BOOL CHTMDesignFrameSet::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk, CHTMDesignFrame** pOnFrame)
{
	ASSERT(this);
	ASSERT(m_type == 0);

	UPOSITION pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMDesignFrame* pFrame = (CHTMDesignFrame*)m_frames.GetNext(pos);

		if (pFrame->m_type == 1)
		{
			if (PtInRect(&pFrame->m_client, point))
			{
				BOOL bHandled = pFrame->OnButtonDown(nFlags, point, 0, bDblClk, pOnFrame);

				*pOnFrame = pFrame;
				return TRUE;//if (bHandled) return TRUE;
			}
		}

		if (!m_cols.IsEmpty())
		{
			if ((point.x > pFrame->m_client.left-8) && (point.x < pFrame->m_client.left))
			{
				*pOnFrame = pFrame;
				return TRUE;
			}
		}
		else
		{
			if ((point.y > pFrame->m_client.top-8) && (point.y < pFrame->m_client.top))
			{
				*pOnFrame = pFrame;
				return TRUE;
			}
		}

		if (pFrame->m_type == 0)
		{
			CHTMDesignFrameSet* pFrameSet = (CHTMDesignFrameSet*)pFrame;

			pFrameSet->OnButtonDown(nFlags, point, iButton, bDblClk, pOnFrame);	// Recurse

			if (*pOnFrame) return TRUE;
		}
	}

	return FALSE;//NULL;
}

#endif