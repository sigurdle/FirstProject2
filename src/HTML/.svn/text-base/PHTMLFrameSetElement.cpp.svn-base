#include "stdafx.h"
#include "HTML2.h"

#include "PHTMLFrameSetElement.h"
#include "PHTMLFrameElement.h"
#include "HTMLFrameElement.h"
#include "HTMLFrameSetElement.h"

//#include "PBlockBox.h"

#include "../LXML/HTMContext.h"

//template<class T> int GetCommaSepStringArray(WCHAR* str, CArray<T,T>& values);

namespace System
{

String GetCommaSeperatedString(StringW* str, int index)
{
	String out = NULL;

	ASSERT(0);
#if 0

	int i = 0;

	WCHAR* p = str;
	while (i < index && *p)
	{
		if (*p == L',')
		{
			i++;
		}
		p++;
	}

	while (*p && iswspace(*p)) p++;
	
	while (*p && *p != L',' && !iswspace(*p))
	{
		out += *p++;
	}
#endif
	return out;
}

String SetCommaSeperatedString(String str, StringW* value, int index)
{
	String out = NULL;

	ASSERT(0);
#if 0
	int i = 0;

	WCHAR* p = str;
	while (i < index && *p)
	{
		out += *p;
		if (*p == L',')
		{
			i++;
		}
		p++;
	}

	out += value;

	while (*p && *p != L',') p++;

	while (*p)
	{
		out += *p++;
	}
#endif
	return out;
}

namespace Web
{

PHTMLFrameSetElement::PHTMLFrameSetElement(HTMLFrameSetElement* element) : CHTMFrameNode(element)
{
	m_frameType = 0;

	m_ncols = 0;
	m_nrows = 0;

	m_dragging = 0;
}

PHTMLFrameSetElement::~PHTMLFrameSetElement()
{
	/*
	UPOSITION pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMFrameNode* pFrame = (CHTMFrameNode*)m_frames.GetNext(pos);
		delete pFrame;//pFrame->Release();
	}

	m_frames.RemoveAll();
	*/
}

#if 0
// Called only for the topmost <frameset> element
// virtual
void PHTMLFrameSetElement::PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC)
{
	if (m_pBox)
	{
		Gdiplus::RectF rcf = m_pBox->GetAbsInnerRect();

		m_client = CRect((int)rcf.X, (int)rcf.Y, (int)rcf.GetRight(), (int)rcf.GetBottom());

		PositionFrames(hWndParent);
	}
}
#endif

// virtual
void PHTMLFrameSetElement::BuildRenderableChildren()
{
	CHTMFrameNode::BuildRenderableChildren();	// Call base class first

	PNode** pos = m_rchildList.begin();
	while (pos != m_rchildList.end())
	{
		PElementBase* pElement = (PElementBase*)*pos++;
		if (pElement->m_type == NODE_ELEMENT)
		{
			// Allow all (block-level) elements
			m_frames.Add(pElement);

#if 0
			CComQIPtr<ILDOMElement> element = pElement->m_pNode;

			CComBSTR tagName;
			element->get_localName(&tagName);
			if (tagName.Length() == 0)
			{
				tagName.Empty();
				element->get_tagName(&tagName);
			}

			if (!wcscmp(tagName, L"frameset") ||
				!wcscmp(tagName, L"frame"))
			{
				m_frames.AddTail((CHTMFrameNode*)pElement);
			}
#endif
		}
	}
}

PHTMLFrameElement* PHTMLFrameSetElement::FindFrameByName(StringIn name)
{
	PElementBase** pos = m_frames.begin();
	while (pos != m_frames.end())
	{
		CHTMFrameNode* pFrameNode = (CHTMFrameNode*)*pos++;
		if (pFrameNode->m_frameType == 0)
		{
			PHTMLFrameSetElement* pFrameSetElement = (PHTMLFrameSetElement*)pFrameNode;

			PHTMLFrameElement* pFound = pFrameSetElement->FindFrameByName(name);
			if (pFound) return pFound;
		}
		else
		{
			PHTMLFrameElement* pFrameElement = (PHTMLFrameElement*)pFrameNode;

			String frameName = pFrameElement->GetElement()->get_name();

			if (frameName != NULL)
			{
				if (frameName.CompareNoCase(name) == 0)
				{
					return pFrameElement;
				}
			}
		}
	}

	return NULL;
}

// virtual
void PHTMLFrameSetElement::UIActivate()
{
#if 0
	UPOSITION pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMFrameNode* pFrame = (CHTMFrameNode*)m_frames.GetNext(pos);

		ASSERT(0);
#if 0	// Had this
		pFrame->UIActivate();
#endif
	}
#endif
}

#if 0
void PHTMLFrameSetElement::CreateFrames(ILHTMLFrameSetElement* pFrameSetElement, CPHTMLFrameElement* parentFrame)
{
	//m_frameSetElement = pFrameSetElement;

	CComPtr<ILDOMNode> child;
	pFrameSetElement->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<ILHTMLElement> pElement = child;
		if (pElement)
		{
/*
		LDOMNodeType nodeType;
		pElement->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
*/			
			CComBSTR tagName;
			pElement->get_tagName(&tagName);

			if (!wcscmp(tagName, L"frameset"))
			{
				CComQIPtr<ILHTMLFrameSetElement> frameSetElement = pElement;

				CComObject<PHTMLFrameSetElement>* pFrameSet;
				CComObject<PHTMLFrameSetElement>::CreateInstance(&pFrameSet);// = new PHTMLFrameSetElement2;

			//	pFrameSet->m_pUI = m_pUI;
				ASSERT(0);
#if 0	// Had this
				pFrameSet->m_pParentFrame = parentFrame;
				pFrameSet->m_pParentFrameSet = this;
				m_frames.AddTail(pFrameSet);
#endif

				pFrameSet->CreateFrames(frameSetElement, parentFrame);	// Recurse
			}
			else if (!wcscmp(tagName, L"frame"))
			{
				ASSERT(0);
#if 0	// Had this
				CComQIPtr<ILHTMLFrameElement> frameElement = pElement;

				CComObject<CHTMFrame>* pFrame;
				CComObject<CHTMFrame>::CreateInstance(&pFrame);
				pFrame->AddRef();
#endif

				ASSERT(0);
#if 0	// Have this
				{
					CComPtr<IHlinkFrame> pHlinkFrame;

					CComQIPtr<IOleClientSite> pCS = m_pUI->m_document->m_spClientSite;//m_lpClientSite;
					CComQIPtr<IServiceProvider> pSP = pCS;
					if (pSP)
						pSP->QueryService(SID_SHlinkFrame, IID_IHlinkFrame, (void**)&pHlinkFrame);
				
					pHlinkFrame->GetBrowseContext(&pFrame->m_pHBC);
				}
#endif

				ASSERT(0);
#if 0	// Have this
				pFrame->m_frameElement = frameElement;
			//	pFrame->m_pUI = m_pUI;
				pFrame->m_pParentFrame = parentFrame;
				pFrame->m_pParentFrameSet = this;

				m_frames.AddTail(pFrame);

				pFrame->CreateObject();
#endif

#if 0
			// TODO, have pFrame->SetFrameElement()
				if (m_pUI->m_framesDesign == 0)
				{
					CComPtr<ILDOMDocument> document;
					frameElement->get_contentDocument(&document);	// This will load the document
#endif

			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}
#endif

//void PHTMLFrameSetElement::PositionFrames(HWND hWndParent)
// virtual
void PHTMLFrameSetElement::DistributeBlockChildren(CHTMFlowBlockContext* pC, double oparentwidth)
{
	ASSERT(0);
#if 0
	if (m_pBox == NULL)
	{
		m_pBox = CreateBlockBox();	// Principal box
	}
	ASSERT(pC->m_pBlockBox == NULL);
	pC->m_pBlockBox = m_pBox;

	m_pBox->m_outerRect.X = 0;
	m_pBox->m_outerRect.Y = 0;

	m_pBox->m_innerRect.Width = m_computedWidth;//oparentwidth;
	m_pBox->m_innerRect.Height = m_computedHeight;

	//QIPtr<ILHTMLFrameSetElement> frameSetElement = m_pNode;

#define GetLast(x) (x->c_str())[x->Length()-1];

	String cols;
	String rows;
	cols = m_pElement->getAttribute(WSTR("cols"));
	rows = m_pElement->getAttribute(WSTR("rows"));

	int nframes = m_frames.size();

	m_framespacing = 2;
	String spacing = m_pElement->getAttribute(WSTR("framespacing"));
	if (spacing->Length())
	{
		m_framespacing = str2int(spacing->c_str());
	}

	m_frameborder = true;
	String frameborder = m_pElement->getAttribute(WSTR("frameborder"));
	if (frameborder->Length())
	{
		if (frameborder == L"0" || frameborder.CompareNoCase(L"no") == 0)
		{
			m_frameborder = false;
		}
	}

	vector<String> colString;
	vector<String> rowString;

	if (cols.GetLength())
	{
		GetCommaSepStringArray(cols, colString);
	}

	if (rows.GetLength())
	{
		GetCommaSepStringArray(rows, rowString);
	}

	if (colString.GetSize() == 0) colString.Add(WSTR("100%"));
	if (rowString.GetSize() == 0) rowString.Add(WSTR("100%"));

	m_ncols = colString.GetSize();
	m_nrows = rowString.GetSize();

//	int totalspacing = (nframes-1)*spacing;

//	double availWidth = m_client.Width();
	double availWidth = m_pBox->m_innerRect.Width;
	availWidth -= (m_ncols-1)*m_framespacing;
	if (m_frameborder) availWidth -= m_ncols*2;

//	double availHeight = m_client.Height();
	double availHeight = m_pBox->m_innerRect.Height;
	availHeight -= (m_nrows-1)*m_framespacing;
	if (m_frameborder) availHeight -= m_nrows*2;

	m_colWidth.RemoveAll();
	m_rowHeight.RemoveAll();

// Calculate column widths
	{
		int nRelative = 0;
		double total = 0;

		for (int n = 0; n < m_ncols; n++)
		{
			double size = 0;

			int value = str2int(colString[n]->c_str());
			WCHAR c = GetLast(colString[n]);

			if (c == L'*')	// relative
			{
				nRelative++;
			}
			else if (c == L'%')	// percentage
			{
				size = (double)(availWidth * value)/100;// + 0.5;
			}
			else	//pixel
			{
				size = value;
			}

			m_colWidth.Add(size);

			total += size;
		}

		availWidth -= total;

		for (int n = 0; n < m_ncols; n++)
		{
			int value = str2int(colString[n]->c_str());
			ASSERT(0);
#if 0
			WCHAR c = GetLast(colString[n]);

			if (c == L'*')	// relative
			{
				if (value < 1) value = 1;
				m_colWidth[n] = (double)(availWidth) * value / nRelative;// + 0.5;

				total += m_colWidth[n];
			}
#endif
		}
	}

// Calculate row heights
	{
		int nRelative = 0;
		double total = 0;

		for (int n = 0; n < m_nrows; n++)
		{
			double size = 0;

			int value = str2int(rowString[n]->c_str());
			WCHAR c = GetLast(rowString[n]);

			if (c == L'*')	// relative
			{
				nRelative++;
			}
			else if (c == L'%')	// percentage
			{
				size = (double)(availHeight * value)/100;// + 0.5;
			}
			else	//pixel
			{
				size = value;
			}

			m_rowHeight.Add(size);

			total += size;
		}

		availHeight -= total;

		for (int n = 0; n < m_nrows; n++)
		{
			int value = str2int(rowString[n]->c_str());
			ASSERT(0);
#if 0
			WCHAR c = GetLast(rowString[n]);

			if (c == L'*')	// relative
			{
				if (value < 1) value = 1;
				m_rowHeight[n] = (double)(availHeight) * value / nRelative + 0.5;

				total += m_rowHeight[n];
			}
#endif
		}
	}

	double y = 0;//m_client.top;
	if (m_frameborder) y++;

	for (int nrow = 0; nrow < m_nrows; nrow++)
	{
		double x = 0;//m_client.left;
		if (m_frameborder) x++;

		for (int ncol = 0; ncol < m_ncols; ncol++)
		{
			int i = nrow*m_ncols + ncol;
		//	std::vector<CPElementBase*>::iterator pos = m_frames.FindIndex(i);
		//	if (pos)
			if (i < m_frames.size())
			{
				//CHTMFrameNode* pFrame = (CHTMFrameNode*)m_frames.GetAt(pos);
			//	CPElement* pFrame = (CPElement*)m_frames.GetAt(pos);
				PElementBase* pFrame = m_frames[i];

				double width = m_colWidth[ncol];
				double height = m_rowHeight[nrow];
				if (height < -1) height = -1;
				//Gdiplus::RectF rect(x, y, , );

				CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;

#if 0
				double old = pFrame->m_specifiedHeight;
				pFrame->m_specifiedHeight = height;
#endif
				pFrame->m_computedHeight = height;
			//	pFrame->m_pBox->m_outerRect.X = 0;
			//	pFrame->m_pBox->m_outerRect.Y = 0;

				pFrame->DistributeWithinBlock(pC, pFrame/*nearest positioned ancestor*/, pFrame/*stackingContext*/, width);
#if 0
				pFrame->m_specifiedHeight = old;
#endif
				ASSERT(pC->m_pBlockBox);

				pFrame->m_pBox->m_outerRect.X = x;
				pFrame->m_pBox->m_outerRect.Y = y;

				m_pBox->AddChildBox(pFrame->m_pBox);

				((PHTMLFrameElement*)pFrame)->Set();

#if 0
				pFrame->m_client.SetRect(x, y, x+m_colWidth[ncol], y+m_rowHeight[nrow]);

				pFrame->PositionFrames(hWndParent);	// Recurse
#endif

			}

			x += m_colWidth[ncol];
			x += m_framespacing;
		}

		y += m_rowHeight[nrow];
		y += m_framespacing;
	}

	m_pBox->m_outerRect = m_pBox->m_innerRect;
#endif
}

//void PHTMLFrameSetElement::OnPaint(HDC hDC)
// virtual
void PHTMLFrameSetElement::Draw(CHTMRenderContext* pC)
{
//	CComQIPtr<ILHTMLFrameSetElement> frameSetElement = m_pNode;

#if 0
	CRect clip;
	GetClipBox(hDC, &clip);
#endif

	ASSERT(0);
#if 0

	ASSERT(m_pBox);
	gm::RectF client = m_pBox->GetAbsInnerRect();

	Graphics::Color bordercolor;
	bordercolor = GetElement()->get_borderColorRGBValue();

	LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(255, 0, 0));

	{
		double x = client.X;
		if (m_frameborder) x++;

		for (int n = 0; n < m_ncols-1; n++)
		{
			x += m_colWidth[n];

			ASSERT(0);
#if 0
			pC->m_pGraphics->FillRectangle(brush, (float)x, (float)client.Y, (float)m_framespacing, (float)client.Height);
#endif

			x += m_framespacing;
		}
	}

	{
		double y = client.Y;
		if (m_frameborder) y++;

		for (int n = 0; n < m_nrows-1; n++)
		{
			y += m_rowHeight[n];

			ASSERT(0);
#if 0
			pC->m_pGraphics->FillRectangle(brush, (float)client.X, (float)y, (float)client.Width, (float)m_framespacing);
#endif
			y += m_framespacing;
		}
	}

	/*
	UPOSITION pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMFrameNode* pFrame = (CHTMFrameNode*)m_frames.GetNext(pos);

		CRect irect;
		if (IntersectRect(&irect, &clip, &pFrame->m_client))
		{
			CRect brect = pFrame->m_client;
			brect.InflateRect(1, 1);
			Draw3DRect(hDC, &brect, RGB(0, 0, 0), RGB(255, 255, 255));

			int state = SaveDC(hDC);
			IntersectClipRect(hDC, pFrame->m_client.left, pFrame->m_client.top, pFrame->m_client.right, pFrame->m_client.bottom);

			pFrame->OnPaint(hDC);

			RestoreDC(hDC, state);
		}
	}
	*/
#endif
}

//virtual
bool PHTMLFrameSetElement::OnButtonDown(UINT nFlags, gm::PointI point, int iButton, bool bDblClk, CHTMFrameNode** pOnFrame)
{
#if 0
	ASSERT(this);
	ASSERT(m_frameType == 0);

	m_oldpt = point;

	UPOSITION pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMFrameNode* pFrame = (CHTMFrameNode*)m_frames.GetNext(pos);

		if (pFrame->m_frameType == 1)
		{
			if (PtInRect(&pFrame->m_client, point))
			{
				return pFrame->OnButtonDown(nFlags, point, 0, bDblClk, pOnFrame);
			}
		}
	}

	// Check for resizing of column
	{
		int x = m_client.left;
		if (m_frameborder) x++;

		if (point.x > x)
		{
			for (int n = 0; n < m_ncols-1; n++)
			{
				x += m_colWidth[n];
				x += m_framespacing;

				if (point.x < x)
				{
					*pOnFrame = this;
					ASSERT(0);
#if 0
					m_pParentFrame->setActiveElement(m_frameSetElement);
#endif
					m_dragging = n+1;

					return m_dragging;
				}
			}
		}
	}

	// Check for resizing of row
	{
		int y = m_client.top;
		if (m_frameborder) y++;

		if (point.y > y)
		{
			for (int n = 0; n < m_nrows-1; n++)
			{
				y += m_rowHeight[n];
				y += m_framespacing;

				if (point.y < y)
				{
					*pOnFrame = this;
					ASSERT(0);
#if 0
					m_pParentFrame->setActiveElement(m_frameSetElement);
#endif

					m_dragging = -(n+1);

					return m_dragging;
				}
			}
		}
	}

	pos = m_frames.GetHeadPosition();
	while (pos)
	{
		CHTMFrameNode* pFrame = (CHTMFrameNode*)m_frames.GetNext(pos);

		if (pFrame->m_frameType == 0)
		{
			PHTMLFrameSetElement* pFrameSet = (PHTMLFrameSetElement*)pFrame;

			int dragging = pFrameSet->OnButtonDown(nFlags, point, iButton, bDblClk, pOnFrame);	// Recurse
			if (dragging) return dragging;
		}
	}
#endif

	return 0;
}

//virtual
void PHTMLFrameSetElement::OnButtonUp(UINT nFlags, gm::PointI point, int iButton)
{
	if (m_dragging)
	{
		m_dragging = 0;
	}
}

//virtual
void PHTMLFrameSetElement::OnMouseMove(UINT nFlags, gm::PointI point)
{
#if 0
	CComQIPtr<ILHTMLFrameSetElement> frameSetElement = m_pNode;

	ASSERT(this);
	ASSERT(m_frameType == 0);

	if (m_dragging)	// Resizing frames
	{
		WCHAR buf[64];

		if (m_dragging  > 0)	// resizing column
		{
			int diffx = point.x-m_oldpt.x;
			if (diffx)
			{
				int n = m_dragging-1;

				CComBSTR cols;
				frameSetElement->getAttribute(L"cols", &cols);

				long size = m_colWidth[n] + diffx;
				swprintf(buf, L"%d", size);
				cols = SetCommaSeperatedString(cols, buf, n);

				if (n < m_ncols-1)
				{
					long size = m_colWidth[n+1] - diffx;
					swprintf(buf, L"%d", size);
					cols = SetCommaSeperatedString(cols, buf, n+1);
				}

				frameSetElement->set_cols(cols);
			}
		}
		else if (m_dragging < 0)	// resizing row
		{
			int diffy = point.y-m_oldpt.y;
			if (diffy)
			{
				int n = -(m_dragging+1);

				CComBSTR rows;
				frameSetElement->getAttribute(L"rows", &rows);

				long size = m_rowHeight[n] + diffy;
				swprintf(buf, L"%d", size);
				rows = SetCommaSeperatedString(rows, buf, n);

				if (n < m_nrows-1)
				{
					long size = m_rowHeight[n+1] - diffy;
					swprintf(buf, L"%d", size);
					rows = SetCommaSeperatedString(rows, buf, n+1);
				}

				frameSetElement->set_rows(rows);
			}
		}

	//	PositionFrames();	// TODO remove
	//	m_pUI->InvalidateRect(NULL, TRUE);	// TODO remove
	}
	else
	{
		UPOSITION pos = m_frames.GetHeadPosition();
		while (pos)
		{
			CHTMFrameNode* pFrame = (CHTMFrameNode*)m_frames.GetNext(pos);

		// TODO, always must be in client
			if (pFrame->m_frameType == 1)
			{
				if (PtInRect(&pFrame->m_client, point))
				{
					pFrame->OnMouseMove(nFlags, point);
				}
			}
			else if (pFrame->m_frameType == 0)
			{
				PHTMLFrameSetElement* pFrameSet = (PHTMLFrameSetElement*)pFrame;

				pFrameSet->OnMouseMove(nFlags, point);	// Recurse
			}
		}
	}

	m_oldpt = point;
#endif
}

}	// Web
}
