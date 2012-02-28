#include "stdafx.h"
#include "LXMLEditor2.h"
#include "SmilTimeGraphView.h"

#include "EXMLViewGroup.h"
#include "EXMLDocument.h"
#include "EXMLLayoutView.h"

//IMPORTEXPORT ILDOMElement* GetElementByTagName(ILDOMNode* parentNode, BSTR tagName, BOOL bDeep = TRUE);
//IMPORTEXPORT ILDOMElement* GetElementByTagNameNS(ILDOMNode* parentNode, BSTR ns, BSTR tagName, BOOL bDeep = TRUE);

//#include "EMediaClipDocument.h"

//#include "..\OleDataObject.h"

#include "TimeListDlg.h"
#include "SMILTimeDlg.h"
#include "SMILTimeGraphOptionsDlg.h"

namespace System
{
namespace LXmlEdit
{

int GetSemicolonOrSpaceSepNumberArray(System::StringW* str, Array<double>& values);
int GetSemicolonSepStringArray(System::StringW* str, Array<System::StringW*>& values);

Web::IElementTime* GetParentTimeContainer(Web::IElementTime* elementTime)
{
	ASSERT(0);
	return NULL;
#if 0
	CComQIPtr<ILDOMElement> element = elementTime;
// Find parent time container
	CComPtr<ILDOMNode> parentNode;
	element->get_parentNode(&parentNode);

	CComQIPtr<ILElementTime> parentTimeContainer;

	while (parentNode)
	{
		parentTimeContainer = parentNode;
		if (parentTimeContainer) break;

		CComPtr<ILDOMNode> parentNode2;
		parentNode->get_parentNode(&parentNode2);
		parentNode = parentNode2;
	}

	return parentTimeContainer;
#endif
}

double GlobalTimeToLocalTime(Web::IElementTime* elementTime, double tau)
{
	Web::IElementTime* parentTimeContainer = GetParentTimeContainer(elementTime);

	if (parentTimeContainer)
	{
		// First get the parents simple time
		double tps = GlobalTimeToLocalTime(parentTimeContainer, tau);

	// Convert from parent simple time to active time
		Web::TimeInterval* interval;
		elementTime->get_currentInterval(&interval);
		if (interval == NULL) return 99999999;	// undefined

		double B = interval->get_resolvedBegin();
		double tau = tps - B;

	// Convert from active time to simple time
		double tsf;
		elementTime->ActiveTimeToSimpleTime(tau, &tsf);

		return tsf;
	}
	else
		return tau;	// simple time is same as active time
}

double LocalTimeToGlobalTime(Web::IElementTime* elementTime, double tsf)
{
// Convert from simple time to active time
	double tau;
	elementTime->SimpleTimeToActiveTime(tsf, &tau);

	Web::IElementTime* parentTimeContainer = GetParentTimeContainer(elementTime);

	if (parentTimeContainer)
	{
	// Convert from active time to parent simple time
		Web::TimeInterval* interval;
		elementTime->get_currentInterval(&interval);
		if (interval == NULL) return 99999999;	// undefined

		double B = interval->get_resolvedBegin();
		double tps = tau + B;

		// Recurse
		return LocalTimeToGlobalTime(parentTimeContainer, tps);
	}
	else
	{
		return tau;
	}
}

System::StringW* GetSpaceSepStringFromNumberArray(double* data, int n)
{
	System::StringW* s;

	ASSERT(0);
#if 0

	for (int i = 0; i < n; i++)
	{
		if (i > 0)
			s += L" ";

		WCHAR str[64];
		swprintf(str, L"%g", data[i]);

		s += str;
	}
#endif
	return s;
}

static LDraw::Sizei IconSize[3] =
{
	LDraw::Sizei(20, 15),
	LDraw::Sizei(40, 30),
	LDraw::Sizei(90, 68),
};

#define TXHEIGHT	17
#define TXINDENT	6

#define PANE_NAME				1
#define PANE_KEYS				2
#define PANE_ATTRIBUTES		3
//#define PANE_BEGIN			(1 | (PANE_ATTRIBUTES<<8))
//#define PANE_END				(2 | (PANE_ATTRIBUTES<<8))
#define PANE_DUR				(1 | (PANE_ATTRIBUTES<<8))
//#define PANE_BEGIN			((PANE_ATTRIBUTES | (1<<8))
//#define PANE_END				((PANE_ATTRIBUTES | (2<<8))
//#define PANE_DUR				((PANE_ATTRIBUTES | (3<<8))
#define PANE_TIMES			4
#define PANE_TIMELINE		5

#include "EXMLDocument.h"

#include "LXMLEditorApp.h"

//double ParseClockValue(const OLECHAR* s);
//_bstr_t stripspaces(BSTR s);

System::StringW* GetElementName(Element* element)
{
	ASSERT(0);
	return NULL;
#if 0
	sysstring tagName = element->get_localName();	// Try local name first
	if (SysStringLen(btagName) == 0)
	{
		SysFreeString(btagName);
		element->get_tagName(&btagName);	// Then try full qualified name
	}
	return _bstr_t(btagName, false);
#endif
}

class CTGElement;
class CTimeElement;

LDraw::Color COLOR_SELECTED(100, 100, 160);
LDraw::Color COLOR_NODE(200, 200, 255);
LDraw::Color COLOR_ANIMATION(200, 200, 200);

// virtual
void CTGElement::Free()
{
// Remove userData
	//r<IUnknown> p;
	m_domElement->setUserData(m_pGraphView->m_userDataKey, NULL);

	delete this;//Release();
}

// virtual
void CTGElement::SetElement(Element* domElement)
{
	ASSERT(domElement);

	m_domElement = domElement;

	//CComPtr<IUnknown> p;
	m_domElement->setUserData(m_pGraphView->m_userDataKey, this);
}

IESelectedElement* CTGElement::ActivateElement(UINT nFlags)
{
//	IEXMLDocument* edocument = m_pGraphView->m_viewGroup->get_eXMLDocument();
	Element* eelement = m_domElement;//edocument->GetEElementFromDOMElement(m_domElement);
	IESelectedElement* selectedElement = m_pGraphView->m_viewGroup->ActivateElement(eelement, nFlags);
	return selectedElement;
}

// virtual
void CTGElement::CalculateSize()
{
	m_itemHeight = TXHEIGHT;

// Calculate Height
	m_height = m_itemHeight;

	if (m_expanded)
	{
		for (int i = 0; i < m_childList.GetSize(); i++)
		{
			CTGNode* pElement = m_childList[i];
			pElement->CalculateSize();

			m_height += pElement->m_height;
		}
	}
}

// virtual
void CTGElement::Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
{
	pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, m_itemHeight, rect.GetWidth(), 1);

	if (nPane == PANE_NAME)
	{
		pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, rect.GetWidth(), m_itemHeight);

		//int paneWidth = rect.Width();

		Element* element = m_domElement;

		System::StringW* tagName = element->get_nodeName();

		LDraw::BBoxi rect2(2, 0, rect.GetWidth()-2, TXHEIGHT);

		if (m_expanded)
		{
			int midx = 6;
			int midy = rect2.GetHeight()/2;

			LDraw::PointI pts[] =
			{
				LDraw::PointI(midx-4, midy-2),
				LDraw::PointI(midx+4, midy-2),
				LDraw::PointI(midx, midy+2)
			};
			
#if 0
			pGraphics->DrawPolygon(&LDraw::Pen(LDraw::Color(0,0,0)), pts, 3);
#endif
		}
		else
		{
			int midy = rect2.GetHeight()/2;

			LDraw::PointI pts[] =
			{
				LDraw::PointI(rect2.left+2, midy-4),
				LDraw::PointI(rect2.left+2, midy+4),
				LDraw::PointI(rect2.left+2+4, midy)
			};

			pGraphics->DrawPolygon(new LDraw::Pen(LDraw::Color(0,0,0)), pts, 3);
		}

		LDraw::Color textColor;

		LDraw::BBoxi trect = rect2;
		trect.left += 14;
		if (m_selected)
		{
			ASSERT(0);
#if 0
			pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color::FromCOLORREF(GetSysColor(COLOR_HIGHLIGHT))), trect.left, trect.top, trect.Width(), trect.Height());
			textColor = LDraw::Color::FromCOLORREF(GetSysColor(COLOR_HIGHLIGHTTEXT));
#endif
		}
		else
		{
		//	ASSERT(0);
			textColor = LDraw::Color(0, 0, 0);//::FromCOLORREF(GetSysColor(COLOR_WINDOWTEXT));
		}
	//	LDraw::FontFamily  fontFamily(L"Times New Roman");
	//	LDraw::Font        font(&fontFamily, trect.Height()-1);//, LDraw::FontStyleRegular, LDraw::UnitPixel);

		pGraphics->DrawString(
			tagName,
			m_pGraphView->GetFont(),
			LDraw::RectF(trect.left, trect.top, trect.GetWidth(), trect.GetHeight()),
		//	&LDraw::StringFormat(),//::GenericTypographic(),
			new LDraw::SolidBrush(textColor));

	//	dc.DrawText(_bstr_t(tagName), tagName.Length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}

	int dsty = m_itemHeight;//TXHEIGHT;
	if (m_expanded)
	{
		for (int pos = 0; pos < m_childList.GetSize(); pos++)
		{
			CTGNode* pElement = m_childList[pos];

			int dstx = 0;//pElement->m_x*secondWidth;
			if (nPane == PANE_NAME)
				dstx = 8;

			pGraphics->TranslateTransform(dstx, dsty);
#if 0
			POINT oldOrg;
			OffsetViewportOrgEx(hDC, dstx, dsty, &oldOrg);
#endif

			pElement->Draw(pGraphics, nPane, LDraw::BBoxi(dstx, 0, rect.right, 0), bSelected);

			pGraphics->TranslateTransform(-dstx, -dsty);
#if 0
			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
#endif

			dsty += pElement->m_height;
		}
	}
}

// virtual
CTGNode* CTGElement::OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
	if (nPane == PANE_NAME)
	{
		if (point.Y < TXHEIGHT)
		{
			if (point.X >= 0 && point.X < 14)
			{
				m_expanded = !m_expanded;
			}

			return this;
		}
	}

	LDraw::PointD pt = point;
	pt.Y -= TXHEIGHT;
	if (nPane == PANE_NAME)
		pt.X -= 8;

	if (m_expanded)
	{
		CTGNode* pNode = OnButtonDownChildren(nPane, pt, nFlags, dragging);
		if (pNode)
			return pNode;
	}

	return NULL;
}

//virtual
void CTGElement::OnButtonDblClk(LDraw::PointD point, long& dragging)
{
	ASSERT(0);
#if 0
	CComPtr<IUIDlgSite> dlgsite;
	m_pGraphView->m_viewGroup->m_views[12]->GetDlgSite(&dlgsite);
	dlgsite->Show(TRUE);

	// Activate the dialogs frame
	UI::Control* hwnd;
	m_pGraphView->m_viewGroup->m_views[12]->get_hwnd(&hwnd);
	while (hwnd)
	{
		if (!(GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD))
			break;
		hwnd = ::GetParent(hwnd);
	}

	SetActiveWindow(hwnd);
#endif
}

// virtual
CTGNode* CTGElement::OnButtonDownChildren(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
#if 0
	if (nPane == PANE_TIMELINE)
	{
		double secondWidth = m_pGraphView->m_secondWidth;

		point.x -= m_x*secondWidth;
		int dy = 0;

		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CTGNode* pElement = (CTGNode*)m_childList.GetNext(pos);

			//LDraw::BBoxi rc(pElement->m_x*secondWidth, dy, (pElement->m_x+pElement->m_width)*secondWidth, dy+pElement->m_height);

			//if (rc.PtInRect(point))
			{
				LDraw::PointD pt = point;
				pt.y -= dy;//rc.top;
				//pt.x -= rc.left;

				CTGNode* p = pElement->OnButtonDown(nPane, pt, nFlags, dragging);
				if (p)
					return p;
			}

			dy += pElement->m_height;
		}
	}
	else
#endif
	{
		int dy = 0;

		ASSERT(0);
#if 0
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CTGNode* pElement = (CTGNode*)m_childList.GetNext(pos);

			LDraw::PointD pt = point;
			pt.y -= dy;

			CTGNode* p = pElement->OnButtonDown(nPane, pt, nFlags, dragging);
			if (p)
				return p;

			dy += pElement->m_height;
		}
#endif
	}

	return NULL;
}

class CNElement :
	public CTGElement
{
public:

/*
	virtual void Draw(HDC hDC, int nPane, LDraw::BBoxi rect, BOOL bSelected)
	{
		int dsty = TXHEIGHT;
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CTGNode* pNode = (CTGNode*)m_childList.GetNext(pos);

			int dstx = 0;//pElement->m_x*secondWidth;

			POINT oldOrg;
			OffsetViewportOrgEx(hDC, dstx, dsty, &oldOrg);

			pNode->Draw(hDC, nPane, textIndent + 1, bSelected);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			dsty += pNode->m_height;
		}
	}
	*/
};

class CNNode :
	public CTGNode
{
public:

	System::StringW* m_name;

	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
	{
		//CDCHandle dc(hDC);

#if 0
		dc.FillSolidRect(0, m_itemHeight, rect.Width(), 1, RGB(255, 255, 255));
#endif

		if (nPane == PANE_NAME)
		{
			int paneWidth = rect.GetWidth();

			LDraw::BBoxi rect2(2, 0, paneWidth-2, TXHEIGHT);

			if (m_expanded)
			{
				int midx = 6;
				int midy = rect2.GetHeight()/2;

				LDraw::PointI pts[] =
				{
					LDraw::PointI(midx-4, midy-2),
					LDraw::PointI(midx+4, midy-2),
					LDraw::PointI(midx, midy+2)
				};

#if 0
				dc.Polygon(pts, 3);
#endif
			}
			else
			{
				int midy = rect2.GetHeight()/2;

				LDraw::PointI pts[] =
				{
					LDraw::PointI(rect2.left+2, midy-4),
					LDraw::PointI(rect2.left+2, midy+4),
					LDraw::PointI(rect2.left+2+4, midy)
				};

#if 0
				dc.Polygon(pts, 3);
#endif
			}

			LDraw::BBoxi trect = rect2;
			trect.left += 14;
			if (m_selected)
			{
#if 0
				dc.FillSolidRect(&trect, GetSysColor(COLOR_HIGHLIGHT));
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
#endif
			}
			else
			{
#if 0
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
#endif
			}
#if 0
			dc.DrawText(m_name, m_name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
#endif
		}
	}

/*
	virtual void Draw(HDC hDC, int nPane, LDraw::BBoxi rect, BOOL bSelected)
	{
		int dsty = TXHEIGHT;
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CTGNode* pNode = (CTGNode*)m_childList.GetNext(pos);

			int dstx = 0;//pElement->m_x*secondWidth;

			POINT oldOrg;
			OffsetViewportOrgEx(hDC, dstx, dsty, &oldOrg);

			pNode->Draw(hDC, nPane, textIndent + 1, bSelected);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			dsty += pNode->m_height;
		}
	}
	*/
};

class CTGEmpty :
	public CTGElement
{
public:

	virtual void Free()
	{
		ASSERT(m_domElement == NULL);
		delete this;//Release();
	}

	virtual void CalculateSize()
	{
		m_itemHeight = TXHEIGHT;
		m_height = m_itemHeight;
	}

	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
	{
		//CDCHandle dc(hDC);

#if 0
		dc.FillSolidRect(0, m_itemHeight, rect.Width(), 1, RGB(255, 255, 255));
#endif

		if (nPane == PANE_NAME)
		{
#if 0
			dc.FillSolidRect(0, 0, rect.Width(), m_itemHeight, RGB(255, 255, 255));
#endif

			LDraw::BBoxi rect2(2, 0, rect.GetWidth()-2, m_itemHeight);

			LDraw::BBoxi trect = rect2;
			trect.left += 14;

			if (m_selected)
			{
#if 0
				dc.FillSolidRect(&trect, GetSysColor(COLOR_HIGHLIGHT));
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
#endif
			}
			else
			{
#if 0
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
#endif
			}

			// Bold
#if 0
			dc.DrawText("...", 3, &trect, DT_VCENTER | DT_SINGLELINE);
			trect.left++;
			dc.DrawText("...", 3, &trect, DT_VCENTER | DT_SINGLELINE);
#endif
		}
	}
};

class CTimeManipulationNode :
	public CTGNode
{
public:

	CTimeManipulationNode()
	{
		//m_height = 60;
		m_expanded = false;
	}

	virtual void CalculateSize()
	{
		m_itemHeight = TXHEIGHT;

		ASSERT(0);
#if 0
		m_width = ((CTimeElement*)m_parent)->m_width;
		m_height = TXHEIGHT;

		if (m_expanded)
		{
			m_height += 50;
		}
#endif
	}

	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
	{
		m_expanded = !m_expanded;
		return this;
	}

	CTimeElement* GetTimeElement()
	{
		return (CTimeElement*)m_parent;
	}

	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected);
//	virtual CTGNode* OnButtonDown(LDraw::PointD point, long& dragging);
//	virtual void OnDrag(LDraw::PointD point, long dragging);
};

class CTimeElement : public CTGElement
{
public:
	Web::SMILTimeList* m_begin;
	double m_duration;

	double m_startx;
	LDraw::PointD m_startpoint;
	LDraw::PointD m_oldpoint;

	double m_x;
	double m_gb;
	double m_width;

	CTimeElement()
	{
		m_x = 0;
		m_width = 0;
	}

	Array<int> m_selectedBeginTimes;
	Array<int> m_selectedEndTimes;

	void DeselectAllBeginTimes()
	{
		m_selectedBeginTimes.RemoveAll();
	}

	void SelectBeginTime(int n)
	{
		for (int i = 0; i < m_selectedBeginTimes.GetSize(); i++)
		{
			if (m_selectedBeginTimes[i] == n)
			{
				return;
			}
		}
		m_selectedBeginTimes.Add(n);
	}

	void DeselectBeginTime(int n)
	{
		for (int i = 0; i < m_selectedBeginTimes.GetSize(); i++)
		{
			if (m_selectedBeginTimes[i] == n)
			{
				m_selectedBeginTimes.RemoveAt(i);
				return;
			}
		}
	}

	bool IsBeginTimeSelected(int n)
	{
		for (int i = 0; i < m_selectedBeginTimes.GetSize(); i++)
		{
			if (m_selectedBeginTimes[i] == n)
			{
				return true;
			}
		}

		return false;
	}

	bool IsEndTimeSelected(int n)
	{
		for (int i = 0; i < m_selectedEndTimes.GetSize(); i++)
		{
			if (m_selectedEndTimes[i] == n)
			{
				return true;
			}
		}

		return false;
	}

	virtual void Deselect()
	{
		DeselectAllBeginTimes();

		CTGElement::Deselect();
	}

	virtual void SetElement(Element* domElement)
	{
		CTGElement::SetElement(domElement);

		Element* element = domElement;

	// Get duration attribute
		System::StringW* dur = element->getAttribute(WSTR("dur"));
		if (dur != NULL)
		{
			System::StringW* sdur = stripspaces(dur);
			m_duration = Web::ParseClockValue(sdur->c_str());
		}
		else
			m_duration = 0;

#if 0
		ILElementTime* timeElement = dynamic_cast<ILElementTime*>(domElement);

		timeElement->get_dur(&m_duration);	// simple duration
#endif

	// Get begin attribute
#if 0
		if (timeElement)
		{
			timeElement->get_begin(&m_begin);
		}
		else
		{
			ASSERT(0);
	#if 0
			m_begin.CoCreateInstance(CLSID_LSMILTimeList);

			BSTR bbeginstr;
			element->getAttribute(L"begin", &bbeginstr);

			_bstr_t beginstr;
			if (bbeginstr)
				beginstr = _bstr_t(bbeginstr, false);
			else
				beginstr = L"0s";

			VARIANT_BOOL success;
			m_begin->parseString(beginstr, &success);
	#endif
		}
#endif

		if (false)
		{
			ASSERT(0);
#if 0
			CComObject<CTimeManipulationNode>* pTimeManip;
			CComObject<CTimeManipulationNode>::CreateInstance(&pTimeManip);
			pTimeManip->AddRef();
			pTimeManip->m_parent = this;
			pTimeManip->m_pGraphView = m_pGraphView;
			m_childList.AddTail(pTimeManip);
#endif
		}
	}

	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);
	virtual void OnButtonDblClk(LDraw::PointD point, long& dragging);
	virtual void OnDrag(LDraw::PointD ptoffset, long dragging);
	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected);

	virtual void CalculateSize()
	{
		m_gb = 0;
		m_x = 0;
		m_width = m_duration;
#if 0
		ILElementTime* elementTime = dynamic_cast<ILElementTime*>(m_domElement);

		ILTimeInterval* interval = elementTime->get_currentInterval();

	//	double simpleDur;
	//	elementTime->get_simpleDur(&simpleDur);

		if (interval)
		{
			interval->get_resolvedBegin(&m_x);

			ILElementTime* parentTimeContainer = GetParentTimeContainer(elementTime);
			if (parentTimeContainer)
				m_gb = LocalTimeToGlobalTime(parentTimeContainer, m_x);
			else
				m_gb = m_x;

			interval->get_resolvedEnd(&m_width);
			m_width -= m_x;
		}
		else
		{
			m_x = 99999999999;	// indefinite ?
			m_width = 0;
		}
#endif
	}
};

class CTimeBlock : public CTimeElement
{
public:
	CTimeBlock()
	{
	}

	virtual void CalculateSize()
	{
		/*
		CComQIPtr<ILElementTime> elementTime = m_domElement;

		CTimeElement::CalculateSize();

		CComPtr<ILTimeInterval> interval;
		elementTime->get_currentInterval(&interval);

	//	double simpleDur;
	//	elementTime->get_simpleDur(&simpleDur);

		if (interval)
		{
			interval->get_resolvedBegin(&m_x);

			m_gb = LocalTimeToGlobal(elementTime, 0);

			interval->get_resolvedEnd(&m_width);
			m_width -= m_x;
		}
		else
		{
			m_x = 99999999999;	// indefinite ?
			m_width = 0;
		}
		*/
		CTimeElement::CalculateSize();

	// Calculate Height
		m_itemHeight = TXHEIGHT;

		m_height = m_itemHeight;

		if (m_expanded)	// ??
		{
			for (int pos = 0; pos < m_childList.GetSize(); pos++)
			{
				CTGNode* pElement = m_childList[pos];
				pElement->CalculateSize();

				m_height += pElement->m_height;
			}
		}
	}

//	virtual void BuildTimeGraph(ILDOMElement* parentElement);
};

class CParElement :
	public CTimeBlock
{
public:
	CParElement()
	{
	}

	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
	{
//		CDCHandle dc(hDC);

		if (m_pGraphView->m_pActiveNode == this)
			bSelected = true;

		if (nPane == PANE_TIMELINE)
		{
		//	CComQIPtr<ILDOMElement> element = m_domElement;
		//	CComQIPtr<ILElementTime> elementTime = m_domElement;

	//		CComBSTR tagName;
	//		m_domElement->get_tagName(&tagName);

			double secondWidth = m_pGraphView->m_secondWidth;

			double simpleDuration = m_duration;
#if 0
			elementTime->getSimpleDuration(&simpleDuration);
#endif

			double dstx = m_gb*secondWidth;

			//POINT oldOrg;
			//OffsetViewportOrgEx(hDC, dstx, 0, &oldOrg);

			LDraw::BBoxi trc(dstx, 1, dstx+m_width*secondWidth, TXHEIGHT);
#if 0
			FillSolidRect(hDC, &trc, bSelected? COLOR_SELECTED: COLOR_NODE);
#endif

	//		CBrush brush;
	//		brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
#if 0
			HBRUSH hOldBrush = dc.SelectBrush(brush);
#endif

			// Draw out knob
			{
				LDraw::PointI pts[] =
				{
					LDraw::PointI(trc.right, trc.top),
					LDraw::PointI(trc.right, trc.bottom-1),
					LDraw::PointI(trc.right+TXHEIGHT/2, trc.bottom-1),
					LDraw::PointI(trc.right+TXHEIGHT/2, trc.top+TXHEIGHT/2),
					LDraw::PointI(trc.right, trc.top)
				};

#if 0
				dc.Polygon(pts, 5);
#endif
			}

#if 0
			dc.SelectBrush(hOldBrush);
#endif

			CTimeBlock::Draw(pGraphics, nPane, rect, bSelected);

			{
				// Dim repeats
				LDraw::RectI rc(dstx+simpleDuration*secondWidth, 0, (m_width-simpleDuration)*secondWidth, IconSize[m_pGraphView->m_iconSize].Height);
				LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(127, 255, 255, 255));

				pGraphics->FillRectangle(brush, rc);
			}

		//	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}
		else
		{
			CTimeBlock::Draw(pGraphics, nPane, rect, bSelected);
		}
	}

	virtual void CalculateSize()
	{
		CTimeBlock::CalculateSize();
	}

	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
	{
		ASSERT(0);
#if 0
		if (nPane == PANE_TIMELINE)
		{
			if (point.y < m_itemHeight)
			{
				if (point.y < TXHEIGHT)
				{
					ActivateElement(nFlags);

					return CTimeBlock::OnButtonDown(nPane, point, nFlags, dragging);
				}
				else
				{
					point.y -= TXHEIGHT;

					CTGNode* p = OnButtonDownChildren(nPane, point, nFlags, dragging);
					if (p)
						return p;
				}
			}
		}
#endif
		return CTimeBlock::OnButtonDown(nPane, point, nFlags, dragging);
	}

	virtual void OnDrag(LDraw::PointD point, long dragging)
	{
		CTimeBlock::OnDrag(point, dragging);
	}
};

class CSeqElement :
	public CTimeBlock
{
public:
	CSeqElement()
	{
	}

	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
	{
	//	CDCHandle dc(hDC);
			ASSERT(0);
#if 0
		if (nPane == PANE_TIMELINE)
		{
			CFormatWindow* pWindow = static_cast<CLXMLEditorApp*>(m_pGraphView->m_viewGroup->m_pDocument->m_app.p)->RegisterFormatWindow(L"Source Windows");
			ASSERT(pWindow);

			if (m_pGraphView->m_pActiveNode == this)
				bSelected = TRUE;

			CComQIPtr<ILDOMElement> element = m_domElement;

		//	CComBSTR tagName;
		//	m_domElement->get_tagName(&tagName);

			double secondWidth = m_pGraphView->m_secondWidth;

		//	_bstr_t timeContainer = GetElementTimeContainer(element);

			long ntimes;
			m_begin->get_length(&ntimes);

			//for (unsigned long i = 0; i < ntimes; i++)
			{
				/*
				CComQIPtr<ILSMILTime> time;
				m_begin->item(0, &time);

				VARIANT_BOOL resolved;
				if (time)
					time->get_resolved(&resolved);
				else
					resolved = VARIANT_TRUE;	// hm..

				if (resolved)
				*/
				{
					//CUString str;
					//str.Format("<%S>", (BSTR)tagName);

					int dstx = m_gb*secondWidth;

					//POINT oldOrg;
					//OffsetViewportOrgEx(hDC, dstx, 0, &oldOrg);

					LDraw::BBoxi trc(dstx, 1, dstx+m_width*secondWidth, TXHEIGHT);
#if 0
					FillSolidRect(hDC, &trc, bSelected? COLOR_SELECTED: COLOR_NODE);
#endif
					//SetTextColor(hDC, bSelected? RGB(255, 255, 255): RGB(0,0,0));
					//DrawText(hDC, str, str.GetLength(), &trc, DT_SINGLELINE | DT_END_ELLIPSIS);

					CBrush brush;
					brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
#if 0
					HBRUSH hOldBrush = dc.SelectBrush(brush);
#endif

					// Draw out knob
					{
						POINT pts[] =
						{
							trc.right, trc.top,
							trc.right, trc.bottom-1,
							trc.right+TXHEIGHT/2, trc.bottom-1,
							trc.right+TXHEIGHT/2, trc.top+TXHEIGHT/2,
							trc.right, trc.top
						};

#if 0
						dc.Polygon(pts, 5);
#endif
					}

#if 0
					dc.SelectBrush(hOldBrush);
#endif

					CTimeBlock::Draw(pGraphics, nPane, rect, bSelected);

					//SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

				}
			}
		}
		else
		{
			CTimeBlock::Draw(pGraphics, nPane, rect, bSelected);
		}
#endif
	}

	virtual void CalculateSize()
	{
		CTimeBlock::CalculateSize();
	}

	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
	{
		return CTimeBlock::OnButtonDown(nPane, point, nFlags, dragging);
#if 0
		if (point.y > TXHEIGHT)
		{
			point.y -= TXHEIGHT;

			/*
			CTGNode* p = OnButtonDownChildren(point, dragging);
			if (p)
				return p;
				*/

			double dx = 0;
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CTGNode* pElement = (CTGNode*)m_childList.GetNext(pos);

				dx += pElement->m_x;

				LDraw::BBoxi rc(dx*secondWidth, 0, (dx+pElement->m_width)*secondWidth, pElement->m_height);

				if (rc.PtInRect(point))
				{
					LDraw::PointD pt = point;
					pt.x -= rc.left;

					CTGNode* p = pElement->OnButtonDown(nPane, pt, nFlags, dragging);
					if (p)
						return p;
				}

				dx += pElement->m_width;
			}
		}

		ActivateElement(nFlags);

		dragging = 1;
		return this;
#endif
	}

	/*
	virtual void OnDrag(LDraw::PointD point, long dragging)
	{
		double secondWidth = IconSize[m_pGraphView->m_iconSize].cx / m_pGraphView->m_iconDuration;

		double begin = m_x + point.x/secondWidth;
		if (begin < 0) begin = 0;

		WCHAR buf[64];
		swprintf(buf, L"%gs", begin);

		m_domElement->setAttribute(L"begin", buf);
	}
	*/
};

class CAnimationElement;

class CAnimationValue :
	public CTGNode
{
public:

	CAnimationValue()
	{
		m_height = 60;
		m_nKey = -1;
	}

	int m_nKey;
//	LDraw::PointD m_oldpt;

	CAnimationElement* GetAnimationElement()
	{
		return (CAnimationElement*)m_parent;
	}

	virtual void Draw(MSWindows::HDC hDC, int nPane, LDraw::BBoxi rect, bool bSelected);
	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);
	virtual void OnDrag(LDraw::PointD point, long dragging);
};

class CAnimationVelocity :
	public CTGNode
{
public:

	CAnimationVelocity()
	{
		m_height = 60;
		m_nKey = -1;
	}

	int m_nKey;
//	LDraw::PointD m_oldpt;

	CAnimationElement* GetAnimationElement()
	{
		return (CAnimationElement*)m_parent;
	}

	virtual void Draw(MSWindows::HDC hDC, int nPane, LDraw::BBoxi rect, bool bSelected);
	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);
	virtual void OnDrag(LDraw::PointD point, long dragging);
};

class CAnimationElement :
	public CTimeElement
{
public:

	CAnimationElement()
	{
	}

	double m_startDur;

	CAnimationValue* m_pValueNode;
	CAnimationVelocity* m_pVelocityNode;

	Array<double> m_keyTimes;
	Array<int> m_keys;

	void GetKeys()
	{
		Element* element = dynamic_cast<Element*>(m_domElement);

		m_keys.RemoveAll();

		ASSERT(0);
#if 0

		sysstring bstr_keyTimes;
		element->getAttribute(L"keyTimes", &bstr_keyTimes);
		m_keyTimes.RemoveAll();
		if (bstr_keyTimes)
		{
			GetSemicolonOrSpaceSepNumberArray(bstr_keyTimes, m_keyTimes);
			for (int i = 0; i < m_keyTimes.GetSize(); i++)
			{
				m_keys.Add(i);
			}
		}
		else
		{
			CComBSTR from;
			element->getAttribute(L"from", &from);

			CComBSTR to;
			element->getAttribute(L"to", &to);

			CComBSTR by;
			element->getAttribute(L"by", &by);

			if ((BSTR)from != NULL)
			{
				m_keys.Add(-3);
				m_keyTimes.Add(0);
			}

			if ((BSTR)to != NULL)
			{
				m_keys.Add(-2);
				m_keyTimes.Add(1);
			}
			else if ((BSTR)by != NULL)
			{
				m_keys.Add(-1);
				m_keyTimes.Add(1);
			}
		}

		ASSERT(m_keyTimes.GetSize() == m_keys.GetSize());
#endif
	}

	virtual void BuildTimeGraph(Element* parentElement)
	{
		/*
		m_pValueNode = new CAnimationValue;
		m_pValueNode->m_pGraphView = m_pGraphView;
		AddChildTail(m_pValueNode);

		m_pVelocityNode = new CAnimationVelocity;
		m_pVelocityNode->m_pGraphView = m_pGraphView;
		AddChildTail(m_pVelocityNode);
		*/
	}

	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);
	virtual void OnDrag(LDraw::PointD ptoffset, long dragging);
	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected);

	virtual void CalculateSize()
	{
		ASSERT(0);
#if 0
		/*
		CComQIPtr<ILElementTime> elementTime = m_domElement;

		CComPtr<ILTimeInterval> interval;
		elementTime->get_currentInterval(&interval);

		if (interval)
		{
			interval->get_resolvedBegin(&m_x);	// parent simple time

			CComPtr<ILElementTime> parentTimeContainer = GetParentTimeContainer(elementTime);
			if (parentTimeContainer)
				m_gb = LocalTimeToGlobal(parentTimeContainer, m_x);
			else
				m_gb = 0;

			interval->get_resolvedEnd(&m_width);
			m_width -= m_x;
		}
		else
		{
			m_x = 99999999999;	// indefinite ?
			m_width = 0;
		}
		*/
		CTimeElement::CalculateSize();

		m_itemHeight = TXHEIGHT;
		m_height = m_itemHeight;

		if (m_expanded)
		{
			m_height += 16;

			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CTGNode* pNode = (CTGNode*)m_childList.GetNext(pos);
				pNode->CalculateSize();

				m_height += pNode->m_height;
			}
		}
#endif
	}
};

class CMediaElement :
	public CTimeElement
{
public:

	CMediaElement()
	{
		m_pTransIn = NULL;
		m_pTransOut = NULL;
	//	m_mediaElement = domElement;
		//m_pSrcBitmap = NULL;
	}

	list<CTGNode*> m_nchildList;

	double m_clipBegin;
	double m_startClipBegin;

	Web::SMILMediaElement* m_mediaElement;

	CTransNode* m_pTransIn;
	CTransNode* m_pTransOut;

	virtual void BuildTimeGraph(Element* parentElement)
	{
		m_pTransIn = new CTransNode;
		m_pTransIn->m_parent = this;
		m_pTransIn->m_pGraphView = m_pGraphView;
		m_pTransIn->m_name = WSTR("transIn");
		m_pTransIn->m_itemHeight = TXHEIGHT;
		m_pTransIn->m_height = TXHEIGHT;
		m_nchildList.push_back(m_pTransIn);

		m_pTransOut = new CTransNode;
		m_pTransOut->m_parent = this;
		m_pTransOut->m_pGraphView = m_pGraphView;
		m_pTransOut->m_name = WSTR("transOut");
		m_pTransOut->m_itemHeight = TXHEIGHT;
		m_pTransOut->m_height = TXHEIGHT;
		m_nchildList.push_back(m_pTransOut);

		m_childList.Add(m_pTransIn);
		m_childList.Add(m_pTransOut);

		CTimeElement::BuildTimeGraph(parentElement);
	}

	ErrorCode GetBitmap(LDraw::Bitmap** pVal)
	{
		ErrorCode hr = Success;

		return hr;
	}

	ErrorCode seekElement(double seekTo /*milliseconds*/)
	{
		ErrorCode hr;

		//m_currentTime = seekTo/1000;


		return Success;
	}

#define REMAINDER(t, d) (t - d*floor(t/d))

	ErrorCode LoadFile(LPCWSTR wszFileName)
	{
		ErrorCode hr;

		return hr;
	}

	void LoadMedia()
	{
	}

	virtual void CalculateSize()
	{
		Element* element = m_domElement;
		Web::IElementTime* elementTime = dynamic_cast<Web::IElementTime*>(m_domElement);

		/*
		CComPtr<ILTimeInterval> interval;
		elementTime->get_currentInterval(&interval);

		if (interval)
		{
			interval->get_resolvedBegin(&m_x);

			m_gb = LocalTimeToGlobal(elementTime, 0);

			interval->get_resolvedEnd(&m_width);
			m_width -= m_x;
		}
		else
		{
			m_x = 99999999999;	// indefinite ?
			m_width = 0;
		}
		*/
		CTimeElement::CalculateSize();

		m_clipBegin = 0;
		{
			ASSERT(0);
#if 0
			CComBSTR str;
			element->getAttribute(L"clipBegin", &str);
			if ((BSTR)str != NULL)
			{
				m_clipBegin = atof(_bstr_t(str));
			}
#endif
		}

	//	m_itemHeight = TXHEIGHT;
	//	m_height = /*IconSize[m_pGraphView->m_iconSize].cy +*/ TXHEIGHT;

	// Calculate Height
		m_itemHeight = TXHEIGHT;

		m_height = m_itemHeight;

		if (m_expanded)	// ??
		{
			ASSERT(0);
#if 0
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CTGNode* pElement = (CTGNode*)m_childList.GetNext(pos);
				pElement->CalculateSize();

				m_height += pElement->m_height;
			}
#endif
		}
	}

	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected);
	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);
	virtual void OnButtonDblClk(LDraw::PointD point, long& dragging);
	virtual void OnDrag(LDraw::PointD ptoffset, long dragging);
};

/////////////////////////////////////////////////////////////////////////
// CTimeElement

CTGNode* CTimeElement::OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
	ASSERT(0);
	return NULL;
#if 0
	double secondWidth = m_pGraphView->m_secondWidth;

	CComQIPtr<ILDOMElement> element = m_domElement;
	CComQIPtr<ILElementTime> elementTime = m_domElement;

#if 0
	if (nPane == PANE_BEGIN)
	{
		if (point.y < TXHEIGHT)
		{
			CTimeListDlg dlg;
			dlg.m_title = "begin";
			elementTime->get_begin(&dlg.m_timeList);

			if (dlg.DoModal() == IDOK)
			{
			}

			return this;
		}
	}
	else if (nPane == PANE_END)
	{
		if (point.y < TXHEIGHT)
		{
			CTimeListDlg dlg;
			dlg.m_title = "end";
			elementTime->get_end(&dlg.m_timeList);

			if (dlg.DoModal() == IDOK)
			{
			}

			return this;
		}
	}
	else
#endif
		if (nPane == PANE_TIMES)
	{
		if (point.y < TXHEIGHT)
		{
			CComQIPtr<IESelectedElement> selectedElement = ActivateElement(nFlags);
			if (selectedElement)
			{
				CComQIPtr<ILElementTime> elementTime = m_domElement;

				CComPtr<ILSMILTimeList> beginList;
				elementTime->get_begin(&beginList);

				CComPtr<ILSMILTimeList> endList;
				elementTime->get_end(&endList);

				int x = 0;

				int i;

				long beginLength;
				beginList->get_length(&beginLength);
				for (i = 0; i < beginLength; i++)
				{
					CComPtr<ILSMILTime> stime;
					beginList->item(i, &stime);

					VARIANT_BOOL bResolved;
					stime->get_resolved(&bResolved);

					if (!bResolved)
					{
						int left = x+TXHEIGHT/2;
						int top = 1;
						int bottom = TXHEIGHT;

						x = left;

						if (point.x < x)
						{
							BOOL bSelected = IsBeginTimeSelected(i);

							if (nFlags & MK_SHIFT)
							{
								if (bSelected)
								{
									DeselectBeginTime(i);
								}
								else
								{
									SelectBeginTime(i);

									m_pGraphView->m_mode = 2;
								}
							}
							else
							{
								if (!bSelected)
								{
									DeselectAllBeginTimes();
									SelectBeginTime(i);

									m_pGraphView->m_mode = 2;
								}
							}
						}
					}
				}

				long endLength;
				endList->get_length(&endLength);
				for (i = 0; i < endLength; i++)
				{
					CComPtr<ILSMILTime> stime;
					endList->item(i, &stime);

					VARIANT_BOOL bResolved;
					stime->get_resolved(&bResolved);

					if (!bResolved)
					{
						int right = x;//resolvedOffset*secondWidth;
						int top = 1;
						int bottom = TXHEIGHT;

						x += TXHEIGHT/2+2;
					}
				}
			}

			return this;
		}
	}
	else if (nPane == PANE_TIMELINE)
	{
		if (point.y < TXHEIGHT)
		{
			CComQIPtr<IESelectedElement> selectedElement = ActivateElement(nFlags);
			if (selectedElement)
			{
				CComQIPtr<ILElementTime> elementTime = m_domElement;

				CComPtr<ILSMILTimeList> beginList;
				elementTime->get_begin(&beginList);

				CComPtr<ILSMILTimeList> endList;
				elementTime->get_end(&endList);

				int i;

				long beginLength;
				beginList->get_length(&beginLength);
				for (i = 0; i < beginLength; i++)
				{
					CComPtr<ILSMILTime> stime;
					beginList->item(i, &stime);

					VARIANT_BOOL bResolved;
					stime->get_resolved(&bResolved);

					if (bResolved)
					{
						double resolvedOffset;
						stime->get_resolvedOffset(&resolvedOffset);

						double globalTime;
						CComPtr<ILElementTime> parentTimeContainer = GetParentTimeContainer(elementTime);
						if (parentTimeContainer)
							globalTime = LocalTimeToGlobalTime(parentTimeContainer, resolvedOffset);
						else
							globalTime = resolvedOffset;

						int left = globalTime*secondWidth;
						int top = 1;
						int bottom = TXHEIGHT;

						int x = point.x;

						if ((x >= (left-TXHEIGHT/2)) && (x < left))
						{
							BOOL bSelected = IsBeginTimeSelected(i);
							if (nFlags & MK_SHIFT)
							{
								if (bSelected)
								{
									DeselectBeginTime(i);
								}
								else
								{
									SelectBeginTime(i);

									m_pGraphView->m_mode = 2;

									m_startpoint = point;
									m_oldpoint = point;

									dragging = 1;
								}
							}
							else
							{
								if (!bSelected)
								{
									DeselectAllBeginTimes();
									SelectBeginTime(i);
								}

								m_pGraphView->m_mode = 2;

								m_startpoint = point;
								m_oldpoint = point;

								dragging = 1;
							}
						}
					}
				}
			}

#if 0
			long endLength;
			endList->get_length(&endLength);
			for (i = 0; i < endLength; i++)
			{
				CComPtr<ILSMILTime> stime;
				endList->item(i, &stime);

				VARIANT_BOOL bResolved;
				stime->get_resolved(&bResolved);

				if (bResolved)
				{
					double resolvedOffset;
					stime->get_resolvedOffset(&resolvedOffset);

					int right = resolvedOffset*secondWidth;
					int top = 1;
					int bottom = TXHEIGHT;

					POINT pts[] =
					{
						right, top,
						right, bottom-1,
						right+TXHEIGHT/2, bottom-1,
						right+TXHEIGHT/2, top+TXHEIGHT/2,
						right, top
					};
				}
			}
#endif

#if 0
			ActivateElement(nFlags);

			if (m_parent)
			{
				point.x -= m_x*secondWidth;

				if (point.x >= 0)
				{
					if (point.x < m_width*secondWidth)	// active area
					{
						dragging = 1;

						m_startpoint = point;
						m_startx = m_x;
					}
				}
			}
#endif

			return this;
		}
	}

	return CTGElement::OnButtonDown(nPane, point, nFlags, dragging);
#endif
}

void CTimeElement::OnButtonDblClk(LDraw::PointD point, long& dragging)
{
	ASSERT(0);
#if 0
	if (m_pGraphView->m_mode == 2)
	{
		CComQIPtr<ILElementTime> elementTime = m_domElement;

		CComPtr<ILSMILTimeList> beginList;
		elementTime->get_begin(&beginList);

		CSMILTimeDlg dlg;

		for (int i = 0; i < m_selectedBeginTimes.GetSize(); i++)
		{
			CComPtr<ILSMILTime> stime;
			beginList->item(m_selectedBeginTimes[i], &stime);

			LTimeType type;
			stime->get_timeType(&type);
			if (i == 0)
				dlg.m_type = type;
			else if (dlg.m_type != type)
				dlg.m_type = -1;

			double offset;
			stime->get_offset(&offset);;
			if (i == 0)
				dlg.m_offset = offset;
			else if (dlg.m_offset != offset)
				dlg.m_offset = 999999999;
		}

		if (dlg.DoModal() == IDOK)
		{
			for (int i = 0; i < m_selectedBeginTimes.GetSize(); i++)
			{
				CComPtr<ILSMILTime> stime;
				beginList->item(m_selectedBeginTimes[i], &stime);
			}
		}
	}
#endif
}

void CTimeElement::OnDrag(LDraw::PointD point, long dragging)
{
	ASSERT(0);
#if 0
	double secondWidth = m_pGraphView->m_secondWidth;

	if (dragging == 1)
	{
		/*
		double begin = m_startx + (ptoffset.x)/secondWidth;
		m_startx = begin;
	//	if (begin < 0) begin = 0;
	*/

		LDraw::PointD ptoffset;
		ptoffset.X = point.X - m_oldpoint.X;

		CComQIPtr<ILElementTime> elementTime = m_domElement;

		CComPtr<ILSMILTimeList> beginList;
		elementTime->get_begin(&beginList);

		CComPtr<ILSMILTimeList> endList;
		elementTime->get_end(&endList);

		int i;

		long beginLength;
		beginList->get_length(&beginLength);
		for (i = 0; i < beginLength; i++)
		{
			if (IsBeginTimeSelected(i))
			{
				CComPtr<ILSMILTime> stime;
				beginList->item(i, &stime);

				double offset;
				stime->get_offset(&offset);

				CComPtr<ILElementTime> parentTimeContainer = GetParentTimeContainer(elementTime);

				// Convert local time to global time
				double globalOffset = LocalTimeToGlobalTime(parentTimeContainer, offset);

				// move it
				globalOffset += ptoffset.x/secondWidth;

				// convert global time to local time
				offset = GlobalTimeToLocalTime(parentTimeContainer, globalOffset);

				// update it with new value
				stime->put_offset(offset);
			}
		}

		m_oldpoint = point;
	}
#endif
}

void CTimeElement::Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
{
//	CDCHandle dc(hDC);

	Element* element = m_domElement;

#if 0
	if (nPane == PANE_BEGIN)
	{
		CComBSTR begin;
		element->getAttribute(L"begin", &begin);

		LDraw::BBoxi trect(2, 0, 45-2, TXHEIGHT);
		dc.DrawText(_bstr_t(begin), begin.Length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
	else if (nPane == PANE_END)
	{
		CComBSTR end;
		element->getAttribute(L"end", &end);

		LDraw::BBoxi trect(2, 0, 45-2, TXHEIGHT);
		dc.DrawText(_bstr_t(end), end.Length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
	else
#endif
		if (nPane == PANE_DUR)
	{
#if 0
		CComBSTR dur;
		element->getAttribute(L"dur", &dur);

		LDraw::BBoxi trect(2, 0, 45-2, TXHEIGHT);
		dc.DrawText(_bstr_t(dur), dur.Length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
#endif
	}
	else if (nPane == PANE_TIMES)
	{
#if 0
		CComQIPtr<ILElementTime> elementTime = m_domElement;

		CComPtr<ILSMILTimeList> beginList;
		elementTime->get_begin(&beginList);

		CComPtr<ILSMILTimeList> endList;
		elementTime->get_end(&endList);

#if 0
		HBRUSH hOldBrush = dc.GetCurrentBrush();
#endif

		CBrush brush;
		brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

		CBrush selectedBrush;
		selectedBrush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

		int x = 0;

		int i;

		long beginLength;
		beginList->get_length(&beginLength);
		for (i = 0; i < beginLength; i++)
		{
			CComPtr<ILSMILTime> stime;
			beginList->item(i, &stime);

			VARIANT_BOOL bResolved;
			stime->get_resolved(&bResolved);

			if (!bResolved)
			{
				//double resolvedOffset;
				//stime->get_resolvedOffset(&resolvedOffset);

				int left = x+TXHEIGHT/2;//resolvedOffset*secondWidth;
				int top = 1;
				int bottom = TXHEIGHT;

				POINT pts[] =
				{
					left-1, top,
					left-1, bottom-1,
					left-1-TXHEIGHT/2, bottom-1,
					left-1-TXHEIGHT/2, top+TXHEIGHT/2,
					left-1, top
				};

#if 0
				if (IsBeginTimeSelected(i))
					dc.SelectBrush(selectedBrush);
				else
					dc.SelectBrush(brush);

				dc.Polygon(pts, 5);
#endif

				x = left;
			}
		}

		long endLength;
		endList->get_length(&endLength);
		for (i = 0; i < endLength; i++)
		{
			CComPtr<ILSMILTime> stime;
			endList->item(i, &stime);

			VARIANT_BOOL bResolved;
			stime->get_resolved(&bResolved);

			if (!bResolved)
			{
			//	double resolvedOffset;
			//	stime->get_resolvedOffset(&resolvedOffset);

				int right = x;//resolvedOffset*secondWidth;
				int top = 1;
				int bottom = TXHEIGHT;

				POINT pts[] =
				{
					right, top,
					right, bottom-1,
					right+TXHEIGHT/2, bottom-1,
					right+TXHEIGHT/2, top+TXHEIGHT/2,
					right, top
				};

#if 0
				if (IsEndTimeSelected(i))
					dc.SelectBrush(selectedBrush);
				else
					dc.SelectBrush(brush);

				dc.Polygon(pts, 5);
#endif

				x += TXHEIGHT/2+2;
			}
		}

#if 0
		dc.SelectBrush(hOldBrush);
#endif
#endif
	}
	else if (nPane == PANE_TIMELINE)
	{
#if 0
		double secondWidth = m_pGraphView->m_secondWidth;

		CComQIPtr<ILElementTime> elementTime = m_domElement;

		CComPtr<ILSMILTimeList> beginList;
		elementTime->get_begin(&beginList);

		CComPtr<ILSMILTimeList> endList;
		elementTime->get_end(&endList);

#if 0
		HBRUSH hOldBrush = dc.GetCurrentBrush();
#endif

		CBrush brush;
		brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

		CBrush selectedBrush;
		selectedBrush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

		int i;

		long beginLength;
		beginList->get_length(&beginLength);
		for (i = 0; i < beginLength; i++)
		{
			CComPtr<ILSMILTime> stime;
			beginList->item(i, &stime);

			VARIANT_BOOL bResolved;
			stime->get_resolved(&bResolved);

			if (bResolved)
			{
				double resolvedOffset;
				stime->get_resolvedOffset(&resolvedOffset);

				double globalTime;
				CComPtr<ILElementTime> parentTimeContainer = GetParentTimeContainer(elementTime);
				if (parentTimeContainer)
					globalTime = LocalTimeToGlobalTime(parentTimeContainer, resolvedOffset);
				else
					globalTime = resolvedOffset;

				int left = globalTime*secondWidth;
				int top = 1;
				int bottom = TXHEIGHT;

				POINT pts[] =
				{
					left-1, top,
					left-1, bottom-1,
					left-1-TXHEIGHT/2, bottom-1,
					left-1-TXHEIGHT/2, top+TXHEIGHT/2,
					left-1, top
				};

#if 0
				if (IsBeginTimeSelected(i))
					dc.SelectBrush(selectedBrush);
				else
					dc.SelectBrush(brush);

				dc.Polygon(pts, 5);
#endif
			}
		}

		long endLength;
		endList->get_length(&endLength);
		for (i = 0; i < endLength; i++)
		{
			CComPtr<ILSMILTime> stime;
			endList->item(i, &stime);

			VARIANT_BOOL bResolved;
			stime->get_resolved(&bResolved);

			if (bResolved)
			{
				double resolvedOffset;
				stime->get_resolvedOffset(&resolvedOffset);

				int right = resolvedOffset*secondWidth;
				int top = 1;
				int bottom = TXHEIGHT;

				POINT pts[] =
				{
					right, top,
					right, bottom-1,
					right+TXHEIGHT/2, bottom-1,
					right+TXHEIGHT/2, top+TXHEIGHT/2,
					right, top
				};

				if (IsEndTimeSelected(i))
					;//dc.SelectBrush(selectedBrush);
				else
					;//dc.SelectBrush(brush);

#if 0
				dc.Polygon(pts, 5);
#endif
			}
		}

#if 0
		dc.SelectBrush(hOldBrush);
#endif
#endif
	}

	CTGElement::Draw(pGraphics, nPane, rect, bSelected);
}

/////////////////////////////////////////////////////////////////////////
// CMediaElement

CTGNode* CMediaElement::OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
	ASSERT(0);
#if 0
	double secondWidth = m_pGraphView->m_secondWidth;

	CComQIPtr<ILDOMElement> element = m_domElement;
	CComQIPtr<ILElementTime> elementTime = m_domElement;

	if (nPane == PANE_TIMELINE)
	{
		if (point.Y < m_itemHeight)
		{
			return CTimeElement::OnButtonDown(nPane, point, nFlags, dragging);
#if 0
			ActivateElement(nFlags);

			point.x -= m_x*secondWidth;

			ATLTRACE("x: %d\n", point.x);

			//double t = point.x * secondWidth;

			if (point.x >= -m_clipBegin*secondWidth)
			{
				if (point.x < -TXHEIGHT/2)	// clipBegin area
				{
				}
				else if (point.x < 0)	// in knob
				{
					dragging = 2;
				}
				else if (point.x < m_width*secondWidth)	// active area
				{
					MessageBeep(-1);
					dragging = 1;
				}
				else
				{
				}
			}

			m_startx = m_x;
			m_startClipBegin = m_clipBegin;

			return this;
#endif
		}
		else
		{
			return CTimeElement::OnButtonDown(nPane, point, nFlags, dragging);
		}
	}
	else
#endif
	{
		return CTimeElement::OnButtonDown(nPane, point, nFlags, dragging);
	}
}

void CMediaElement::OnButtonDblClk(LDraw::PointD point, long& dragging)
{
	CTimeElement::OnButtonDblClk(point, dragging);
#if 0
	CComObject<CEMediaClipDocument>* pMediaDocument;
	CComObject<CEMediaClipDocument>::CreateInstance(&pMediaDocument);
	if (pMediaDocument)
	{
		pMediaDocument->AddRef();

		pMediaDocument->SetMediaElement(m_domElement);

		pMediaDocument->ShowViews(NULL/*TODO*/);
	}
#endif
}

void CMediaElement::OnDrag(LDraw::PointD ptoffset, long dragging)
{
	double secondWidth = m_pGraphView->m_secondWidth;

	if (dragging == 2)	// In
	{
		double begin = m_startx + (ptoffset.X)/secondWidth;
		m_startx = begin;
		double clipBegin = m_startClipBegin + (ptoffset.X)/secondWidth;
		m_startClipBegin = clipBegin;

		double dur = m_width + (ptoffset.X)/secondWidth;

		ASSERT(0);
#if 0
		{
			WCHAR buf[64];
			swprintf(buf, L"%g", clipBegin);
			m_domElement->setAttribute(L"clipBegin", _bstr_t(buf));
		}

		{
			WCHAR buf[64];
			swprintf(buf, L"%fs", begin);
			m_domElement->setAttribute(L"begin", _bstr_t(buf));
		}

		{
			WCHAR buf[64];
			swprintf(buf, L"%fs", dur);
			m_domElement->setAttribute(L"dur", _bstr_t(buf));
		}
#endif
	}
	/*
	else if (dragging == 3)	// Out
	{
	}
	*/
	else
	{
		CTimeElement::OnDrag(ptoffset, dragging);
	}
}

void CMediaElement::Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
{
	ASSERT(0);
#if 0
	//CDCHandle dc(hDC);

	if (m_pGraphView->m_pActiveNode == this)
		bSelected = TRUE;

	CComQIPtr<ILDOMElement> element = m_domElement;
	CComQIPtr<ILElementTime> elementTime = m_domElement;

	if (nPane == PANE_TIMELINE)
	{
		double intrinsicDur = 0;

		CComQIPtr<ILSVGVideoElement> video = element;
		if (video)
		{
			video->getIntrinsicDuration(&intrinsicDur);
		}

		CComBSTR tagName;
		m_domElement->get_tagName(&tagName);

	//	CComBSTR src = L"test";
		//element->get_src(&src);

		/*
		long ntimes;
		m_begin->get_length(&ntimes);
		*/

		double secondWidth = m_pGraphView->m_secondWidth;

		{
#if 0
			TCHAR tsrc[256];
			strcpy(tsrc, _bstr_t(src));
			LPTSTR filename = PathFindFileName(tsrc);
			//DrawText(hDC, filename, strlen(filename), &trc, DT_VCENTER | DT_SINGLELINE);

			//CUString str;
			//str.Format("<%S src=\"%s\">", (BSTR)tagName, filename); 
#endif
			LDraw::PointD oldOrg;
#if 0
			dc.OffsetViewportOrg(m_gb*secondWidth, 0, &oldOrg);
#endif

			LDraw::BBoxi cliprc(-m_clipBegin*secondWidth, 1, intrinsicDur*secondWidth, TXHEIGHT);
#if 0
			dc.FillSolidRect(&cliprc, RGB(255, 255, 204));
#endif

			LDraw::BBoxi trc(0, 1, m_width*secondWidth, TXHEIGHT);
#if 0
			dc.FillSolidRect(&trc, bSelected? COLOR_SELECTED: COLOR_NODE);
#endif

			CBrush brush;
			brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
#if 0
			HBRUSH hOldBrush = dc.SelectBrush(brush);
#endif

			// Draw in knob
			{
				POINT pts[] =
				{
					trc.left-1, trc.top,
					trc.left-1, trc.bottom-1,
					trc.left-1-TXHEIGHT/2, trc.bottom-1,
					trc.left-1-TXHEIGHT/2, trc.top+TXHEIGHT/2,
					trc.left-1, trc.top
				};

#if 0
				dc.Polygon(pts, 5);
#endif
			}

			// Draw out knob
			{
				POINT pts[] =
				{
					trc.right, trc.top,
					trc.right, trc.bottom-1,
					trc.right+TXHEIGHT/2, trc.bottom-1,
					trc.right+TXHEIGHT/2, trc.top+TXHEIGHT/2,
					trc.right, trc.top
				};

#if 0
				dc.Polygon(pts, 5);
#endif
			}

#if 0
			dc.SelectBrush(hOldBrush);

			dc.SetViewportOrg(oldOrg.x, oldOrg.y);
#endif
		}

		CTimeElement::Draw(pGraphics, nPane, rect, bSelected);

		/*
		double repeatCount;
		m_mediaElement->get_repeatCount(&repeatCount);
		*/

		double simpleDuration;
		elementTime->getSimpleDuration(&simpleDuration);

		//double resolvedOffset = 0;
		//time->get_resolvedOffset(&resolvedOffset);

#if 0
		int dsty = TXHEIGHT;
		int dstx = /*resolvedOffset* */ secondWidth;
		int dstwidth = m_width/*m_duration*/ *secondWidth;

		int state = SaveDC(hDC);
		IntersectClipRect(hDC, dstx, dsty, dstx+dstwidth, dsty+m_height);

		POINT oldOrg;
		OffsetViewportOrgEx(hDC, dstx, dsty, &oldOrg);

		LDraw::BBoxi clipRect;
		GetClipBox(hDC, &clipRect);

		if (FALSE)
		{
			UI::Graphics graphics(hDC);

			int nframes = (m_width/*m_duration*/ *secondWidth + IconSize[m_pGraphView->m_iconSize].cx-1) / IconSize[m_pGraphView->m_iconSize].cx;

			int x = 0;
			for (int n = 0; n < nframes; n++)
			{
				LDraw::BBoxi rc(x, 0, x+IconSize[m_pGraphView->m_iconSize].cx, IconSize[m_pGraphView->m_iconSize].cy);

				double at = n* (m_pGraphView->m_iconDuration);	// activeDuration
				int st = REMAINDER(at, simpleDuration);

				LDraw::BBoxi iRect;
				if (IntersectRect(&iRect, &clipRect, &rc))
				{
					//Draw3DRect(hDC, &rc, RGB(0, 0, 0), RGB(0, 0, 0));

					BOOL bShowFrame;

					switch (m_pGraphView->m_trackFormat)
					{
					case 0:		bShowFrame = TRUE;
						break;
					case 1:		bShowFrame = (n == 0 || n == nframes-1);
						break;
					case 2:		bShowFrame = (n == 0);
						break;
					case 3:		bShowFrame = FALSE;
						break;
					}

					if (bShowFrame)
					{
						seekElement(st*1000);

						LDraw::Bitmap* pBitmap;
						GetBitmap(&pBitmap);

						LDraw::RectI gdiprc(x, 0, IconSize[m_pGraphView->m_iconSize].cx, IconSize[m_pGraphView->m_iconSize].cy);

						graphics.DrawImage(pBitmap,
							gdiprc,
							0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(),
							LDraw::UnitPixel);
					}
					else
					{
						FillSolidRect(hDC, &rc, RGB(198, 233, 176));
					}
				}

				x += IconSize[m_pGraphView->m_iconSize].cx;
			}

			{
				// Dim repeats
				LDraw::RectI rc(simpleDuration*secondWidth, 0, (m_width-simpleDuration)*secondWidth, IconSize[m_pGraphView->m_iconSize].cy);
				LDraw::SolidBrush brush(LDraw::Color(127, 255, 255, 255));

				graphics.FillRectangle(&brush, rc);
			}
		}
#endif

		//SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		//RestoreDC(hDC, state);

	#if 0
		if (!m_pVideo) return;

		int imageHeight;
		int waveHeight;

		if (m_pVideo->GetTotalFrames() > 0 && m_pVideo->GetWaveFormat())
		{
			imageHeight = dstheight/2;
			waveHeight = dstheight/2;
		}
		else if (m_pVideo->GetTotalFrames() > 0)
		{
			imageHeight = dstheight;
			waveHeight = 0;
		}
		else if (m_pVideo->GetWaveFormat())
		{
			waveHeight = dstheight;
			imageHeight = 0;
		}

		int offsety = 0;

		if (m_pVideo->GetTotalFrames() > 0)
		{
			ImageDef* pSrcImage = m_pVideo->GetFrameImage(m_frameptr);

			ASSERT(pSrcImage);

			int width = pSrcImage->width;
			int height = pSrcImage->height;

			HBITMAP	hBitmap = NULL;
			LPBYTE	bits = NULL;
			LPBITMAPV4HEADER	bmi = NULL;
			int rowBytes = BYTESPERROW(width, 24);
			int sizeImage = rowBytes*height;

			if (bmi = (LPBITMAPV4HEADER)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPV4HEADER)))
			{
				bmi->bV4Size = sizeof(BITMAPV4HEADER);
				bmi->bV4Width = width;
				bmi->bV4Height = height;
				bmi->bV4Planes = 1;
				bmi->bV4BitCount = 24;
				bmi->bV4SizeImage = sizeImage;
				int rowbytes = ROWBYTES(width, 24);

				hBitmap = ::CreateDIBSection(NULL, (BITMAPINFO*)bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
				
				if (hBitmap)
				{
					HDC tdc = CreateCompatibleDC(NULL);
					HBITMAP hOldBitmap = (HBITMAP)SelectObject(tdc, hBitmap);

				// Copy the background first, so transparent areas show through
				//	BitBlt(tdc, 0, 0, width, height, m_hDC, dstx, dsty, SRCCOPY);

					for (int y = 0; y < height; y++)
					{
						RGBTRIPLE* pdst = (RGBTRIPLE*)(bits + rowbytes*(height-y-1));
						PixelDef* src = (PixelDef*)(pSrcImage->data + pSrcImage->rowbytes*y);
						
						for (int x = 0; x < width; x++)
						{
							BYTE alpha = src->alpha;
					
							pdst->rgbtRed = pdst->rgbtRed + ((((short)src->red - pdst->rgbtRed) * alpha + 127) >> 8);
							pdst->rgbtGreen = pdst->rgbtGreen + ((((short)src->green - pdst->rgbtGreen) * alpha + 127) >> 8);
							pdst->rgbtBlue = pdst->rgbtBlue + ((((short)src->blue - pdst->rgbtBlue) * alpha + 127) >> 8);

							pdst++;
							src++;
						}
					}

					int oldBltMode = SetStretchBltMode(hDC, HALFTONE);

					StretchDIBits(
						hDC,

						dstx, dsty, dstwidth, imageHeight,
						0, 0, width, height,

						bits, (LPBITMAPINFO)bmi,
						DIB_RGB_COLORS, SRCCOPY);

					SetStretchBltMode(hDC, oldBltMode);

					SelectObject(tdc, hOldBitmap);
					DeleteDC(tdc);

					DeleteObject(hBitmap);
				}

				GlobalFree(bmi);
			}

			offsety += imageHeight;
		}

		if (m_pVideo->GetWaveFormat() != NULL)
		{
			POINT oldOrg;
			OffsetViewportOrgEx(hDC, 0, dsty+offsety, &oldOrg);

			LPWAVEFORMATEX waveFmt = m_pVideo->GetWaveFormat();
			LPSTR waveData =  m_pVideo->GetWaveData();
			int numSamples = m_pVideo->GetTotalSamples();

			DrawWaveForm2(
				waveFmt, waveData, numSamples,
				0, numSamples,
				hDC,
				dstx, dstwidth, waveHeight);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}
	#endif
	}
	else
	{
		CTimeElement::Draw(pGraphics, nPane, rect, bSelected);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////
// CAnimationElement

CTGNode* CAnimationElement::OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMElement> element = m_domElement;
	CComQIPtr<ILElementTime> elementTime = m_domElement;

	if (nPane == PANE_TIMELINE)
	{
		double secondWidth = m_pGraphView->m_secondWidth;

		CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = ActivateElement(nFlags);
		if (selectedAnimationElement)
		{
			if (point.y < m_itemHeight)
			{
#if 0	// changing dur attribute TODO, this is common for all timed elements
				LDraw::PointD pt = point;
				pt.x -= m_x*secondWidth;

				if (pt.x > m_width*secondWidth)
				{
					if (pt.x < m_width*secondWidth+TXHEIGHT/2)
					{
						m_startpoint = point;
						m_startDur = m_width;
						dragging = 3;
						return this;
					}
				}
#endif

				return CTimeElement::OnButtonDown(nPane, point, nFlags, dragging);
			}
			else if (m_expanded && point.y < TXHEIGHT+16)
			{
				m_pGraphView->m_mode = 1;

				point.y -= TXHEIGHT;

				point.y -= 16;

				CTGNode* p = OnButtonDownChildren(nPane, point, nFlags, dragging);
				if (p)
					return p;

			// Try keyframes
				GetKeys();

				LDraw::BBoxi rc(0, TXHEIGHT, m_width*secondWidth, TXHEIGHT+16);

				int i;
				for (i = 0; i < m_keyTimes.GetSize(); i++)
				{
					/*
					double t = m_keyTimes[i]*m_width;

					double st;
					elementTime->ActiveTimeToSimpleTime(t, &st);
					if (m_keyTimes[i] >= 1) st += m_width;

					int x = rc.left + st*secondWidth;
					*/
					double t = m_keyTimes[i]*m_width;

					double st;
					/*
					elementTime->ActiveTimeToSimpleTime(t, &st);
					if (m_keyTimes[i] >= 1) st += m_width;
					*/
					{

						/*
						double tau;
						elementTime->SimpleTimeToActiveTime(t, &tau);
						double B = m_x;
						//tps = tau + B;
						st = tau + B;
						*/

						st = LocalTimeToGlobalTime(elementTime, t);
					}

					int x = rc.left + st*secondWidth;

					if (abs(x-point.x) < 4)
					{
						m_startpoint = point;
						break;
					}
				}

				if (i < m_keyTimes.GetSize())
				{
					VARIANT_BOOL bSelected;
					selectedAnimationElement->IsKeyTimeSelected(m_keys[i], &bSelected);

					if (nFlags & MK_SHIFT)
					{
						if (bSelected)
						{
							selectedAnimationElement->DeselectKeyTime(m_keys[i]);
						}
						else
						{
							selectedAnimationElement->SelectKeyTime(m_keys[i]);
							dragging = 2;
						}
					}
					else
					{
						if (!bSelected)
						{
							selectedAnimationElement->DeselectAllKeyTimes();
							selectedAnimationElement->SelectKeyTime(m_keys[i]);
						}

						dragging = 2;
					}
				}
				else
				{
					if (!(nFlags & MK_SHIFT))
					{
						selectedAnimationElement->DeselectAllKeyTimes();
					}
				}

				m_oldpoint = point;
				return this;
			}
		}

		return CTimeElement::OnButtonDown(nPane, point, nFlags, dragging);
	}
	else if (nPane == PANE_KEYS)
	{
		if (m_expanded)
		{
			double currentTime;// = m_pGraphView->GetCurrentTime();
		//	elementTime->get_activeTime(&currentTime);
			elementTime->get_simpleTime(&currentTime);

			double dur;
			elementTime->getSimpleDuration(&dur);

			double tprev;
			double tnext;
			double tat;
			BOOL bPrev = FALSE;
			BOOL bNext = FALSE;
			BOOL bAt = FALSE;

			for (int i = 0; i < m_keyTimes.GetSize(); i++)
			{
				double t = m_keyTimes[i]*dur;//m_width;

				double st;
				elementTime->ActiveTimeToSimpleTime(t, &st);
				if (m_keyTimes[i] >= 1) st += dur;//m_width;

				if (st < currentTime)
				{
					bPrev = TRUE;
					tprev = st;
				}
				else if (st > currentTime)
				{
					bNext = TRUE;
					tnext = st;
					break;
				}
				else if (st == currentTime)
				{
					bAt = TRUE;
					tat = st;//currentTime;
				}
			}

			int paneWidth = 60;//m_pGraphView->m_panes[nPane]->m_width;

			int midx = paneWidth/2;

			LDraw::BBoxi prevrc(midx-10-4, TXHEIGHT+2, midx-10, TXHEIGHT+14);
			LDraw::BBoxi nextrc(midx+10, TXHEIGHT+2, midx+10+4, TXHEIGHT+14);
			LDraw::BBoxi atrc(midx-6, TXHEIGHT+2, midx+6, TXHEIGHT+14);

			if (prevrc.PtInRect(point))
			{
				if (bPrev)
				{
					m_pGraphView->SetCurrentTime(tprev);
				}
			}
			else if (nextrc.PtInRect(point))
			{
				if (bNext)
				{
					double tps;

					{
						double simpleTime = tnext;
					//	elementTime->get_simpleTime(&simpleTime);
						double tau;
						elementTime->SimpleTimeToActiveTime(simpleTime, &tau);

						double B = m_x;
						tps = tau + B;
					}

					m_pGraphView->SetCurrentTime(tps);
				}
			}
			else if (atrc.PtInRect(point))
			{
				if (bAt)
				{
					//m_pGraphView->SetCurrentTime(tat);
				}
				else
				{
				}
			}

			return this;
		}
	}
	else
		return CTimeElement::OnButtonDown(nPane, point, nFlags, dragging);
#endif
	return NULL;
}

void CAnimationElement::OnDrag(LDraw::PointD point, long dragging)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMElement> element = m_domElement;

	double secondWidth = m_pGraphView->m_secondWidth;

	LDraw::PointD ptoffset;
	ptoffset.x = point.x - m_oldpoint.x;

	if (dragging == 3)	// dur
	{
		// TODO, this is common for all timed elements
		double dur = m_startDur + (ptoffset.x)/secondWidth;
		m_startDur = dur;
		if (dur < 0) dur = 0;

		{
			WCHAR buf[64];
			swprintf(buf, L"%f", dur);
			element->setAttribute(L"dur", _bstr_t(buf));
		}
	}
	else if (dragging == 2)	// Dragging selected keyTime(s)
	{
		CComPtr<IEXMLDocument> edocument;
		m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

		Element* eelement = m_domElement;
	//	edocument->GetEElementFromDOMElement(m_domElement, &eelement);

		ILElementTime* elementTime = dynamic_cast<ILElementTime*>(m_domElement);

		IESelectedElement* selectedElement = m_pGraphView->m_viewGroup->GetSelectedElement(eelement);

		IESelectedAnimationElement* selectedAnimationElement = dynamic_cast<IESelectedAnimationElement*>(selectedElement);
		ASSERT(selectedAnimationElement);

	//
		CComBSTR bstr_keyTimes;
		element->getAttribute(L"keyTimes", &bstr_keyTimes);
		if ((BSTR)bstr_keyTimes)
		{
			GetKeys();

			for (int i = 0; i < m_keyTimes.GetSize(); i++)
			{
				VARIANT_BOOL bSelected;
				selectedAnimationElement->IsKeyTimeSelected(m_keys[i], &bSelected);

				if (bSelected)
				{
					// Convert keyframe local time to global time
					double t = m_keyTimes[i]*m_width;

					double st;
					/*
					elementTime->ActiveTimeToSimpleTime(t, &st);
					if (m_keyTimes[i] >= 1) st += m_width;
					*/
					{
						/*
						double tau;
						elementTime->SimpleTimeToActiveTime(t, &tau);

						double B = m_x;
						//tps = tau + B;
						st = tau;// + B;
						*/
						st = LocalTimeToGlobalTime(elementTime, t);
					}

					double x = /*rc.left +*/ st;//*secondWidth;

					x += ptoffset.x/secondWidth;

				// Convert to local time
					double lt;
					//elementTime->ActiveTimeToSimpleTime(x, &lt);
					lt = GlobalTimeToLocalTime(elementTime, x);

					m_keyTimes[i] = lt/m_width;

					/*
					double t = point.x / secondWidth;

					double st;
					elementTime->ActiveTimeToSimpleTime(t, &st);
					//if (m_keyTimes[i] >= 1) st += m_width;

					double offset = (ptoffset.x/secondWidth)/m_width;
					m_keyTimes[i] += offset;
					*/


				//	if (keyTimes[i] < 
				}
			}



			element->setAttribute(L"keyTimes", GetSpaceSepStringFromNumberArray(m_keyTimes.GetData(), m_keyTimes.GetSize()));

			m_oldpoint = point;
		}
	}
	else
	{
		CTimeElement::OnDrag(point, dragging);
	}
#endif
}

void CAnimationElement::Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
{
	ASSERT(0);
#if 0
//	CDCHandle dc(hDC);

	if (m_pGraphView->m_pActiveNode == this)
		bSelected = TRUE;

	CComQIPtr<ILDOMElement> element = m_domElement;
	CComQIPtr<ILAnimationElement> animation = m_domElement;
	CComQIPtr<ILElementTime> elementTime = m_domElement;
	CComQIPtr<ILAnimateXXX> animateXXX = element;

	GetKeys();

	if (nPane == PANE_TIMELINE)
	{
		sysstring tagName = m_domElement->get_nodeName();

		if (animateXXX)	// ???
		{
			double secondWidth = m_pGraphView->m_secondWidth;

			for (long i = 0; i < 1/*ntimes*/; i++)
			{
				LDraw::PointD oldOrg;
#if 0
				dc.OffsetViewportOrg(m_gb*secondWidth, 0, &oldOrg);
#endif

				CComPtr<IEXMLDocument> edocument;
				m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

				CComPtr<IEElement> eelement;
				edocument->GetEElementFromDOMElement(element, &eelement);
				ASSERT(eelement);

				CComPtr<IESelectedElement> selectedElement;
				m_pGraphView->m_viewGroup->GetSelectedElement(eelement, &selectedElement);

				CComQIPtr<IESelectedAnimationElement> selectedAnimationElement(selectedElement);

				LDraw::BBoxi trc(0, 1, m_width*secondWidth, TXHEIGHT);
#if 0
				FillSolidRect(hDC, &trc, bSelected? COLOR_SELECTED: COLOR_NODE);
#endif

				CBrush brush;
				brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
#if 0
				HBRUSH hOldBrush = dc.SelectBrush(brush);
#endif

				// Draw out knob
				{
					POINT pts[] =
					{
						trc.right, trc.top,
						trc.right, trc.bottom-1,
						trc.right+TXHEIGHT/2, trc.bottom-1,
						trc.right+TXHEIGHT/2, trc.top+TXHEIGHT/2,
						trc.right, trc.top
					};

#if 0
					dc.Polygon(pts, 5);
#endif
				}

#if 0
				dc.SelectBrush(hOldBrush);
#endif

				if (m_expanded)
				{
					LDraw::BBoxi rc(0, TXHEIGHT, m_width*secondWidth, TXHEIGHT+16);
#if 0
					FillSolidRect(hDC, &rc, COLOR_ANIMATION);
#endif

					for (int i = 0; i < m_keyTimes.GetSize(); i++)
					{
						double t = m_keyTimes[i]*m_width;

						double st;
						/*
						elementTime->ActiveTimeToSimpleTime(t, &st);
						if (m_keyTimes[i] >= 1) st += m_width;
						*/
						{
							double tau;
							elementTime->SimpleTimeToActiveTime(t, &tau);

							//double B = m_x;
							//tps = tau + B;
							//st = tau + B;

							st = tau;
						}

						int x = rc.left + st*secondWidth;

						VARIANT_BOOL bSelected;
						if (selectedAnimationElement)
							selectedAnimationElement->IsKeyTimeSelected(m_keys[i], &bSelected);
						else
							bSelected = VARIANT_FALSE;

#if 0
						Rectangle(hDC, x-3, rc.top+3, x+4, rc.top+3+7);
						if (bSelected)
							FillSolidRect(hDC, x-2, rc.top+4, 6, 6, RGB(0, 0, 0));
#endif
					}
				}

				double simpleDuration;
				elementTime->getSimpleDuration(&simpleDuration);

				{
					{
						// Dim repeats
						LDraw::RectI rc(simpleDuration*secondWidth, 0, (m_width-simpleDuration)*secondWidth, IconSize[m_pGraphView->m_iconSize].cy);
						LDraw::SolidBrush brush(LDraw::Color(127, 255, 255, 255));

						pGraphics->FillRectangle(&brush, rc);
					}
				}

#if 0
				dc.SetViewportOrg(oldOrg.x, oldOrg.y);
#endif
			}
		}
	}
	else if (nPane == PANE_KEYS)
	{
		int paneWidth = rect.Width();

		{
			static WCHAR* AttributeTypeIdent[] =
			{
				L"auto",
				L"css",
				L"xml",
			};

			LAttributeType attributeType;
			animation->get_attributeType(&attributeType);

			CComBSTR attributeName;
			animation->get_attributeName(&attributeName);

			CUString str;
			str.Format("%S:%S", AttributeTypeIdent[attributeType], (BSTR)attributeName);

			LDraw::BBoxi trc(4, 0, paneWidth-2, TXHEIGHT);
#if 0
			DrawText(hDC, str, str.GetLength(), &trc, DT_SINGLELINE | DT_END_ELLIPSIS);
#endif
		}

		if (m_expanded)
		{
			double currentTime;//m_pGraphView->GetCurrentTime();
			elementTime->get_activeTime(&currentTime);

			BOOL bPrev = FALSE;
			BOOL bNext = FALSE;
			BOOL bAt = FALSE;

			for (int i = 0; i < m_keyTimes.GetSize(); i++)
			{
			//	double t = m_keyTimes[i]*m_width;
				double t = m_keyTimes[i]*m_width;

				double st;
				elementTime->ActiveTimeToSimpleTime(t, &st);
				if (m_keyTimes[i] >= 1) st += m_width;

				if (st < currentTime)
					bPrev = TRUE;
				else if (st > currentTime)
					bNext = TRUE;
				else if (st == currentTime)
					bAt = TRUE;
			}

			int midx = paneWidth/2;

			CBrush brush;
			brush.CreateSolidBrush(RGB(0,0,0));
#if 0
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, brush);
#endif

			if (bPrev)
			{
				POINT pts[] =
				{
					midx-10, TXHEIGHT+4,
					midx-10, TXHEIGHT+12,
					midx-10-4, TXHEIGHT+8
				};

#if 0
				Polygon(hDC, pts, 3);
#endif
			}

			if (bNext)
			{
				POINT pts[] =
				{
					midx+10, TXHEIGHT+4,
					midx+10, TXHEIGHT+12,
					midx+10+4, TXHEIGHT+8
				};

#if 0
				Polygon(hDC, pts, 3);
#endif
			}

#if 0
			SelectObject(hDC, hOldBrush);

			dc.Draw3dRect(midx-6, TXHEIGHT+2, 13, 13, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
#endif
			if (bAt)
			{
				CPen pen;
				pen.CreatePen(PS_SOLID, 2, RGB(0,0,0));
#if 0
				HPEN hOldPen = dc.SelectPen(pen);

				dc.MoveTo(midx-4, TXHEIGHT+3+5);
				dc.LineTo(midx-1, TXHEIGHT+3+8);
				dc.LineTo(midx+5, TXHEIGHT+3+2);

				dc.SelectPen(hOldPen);
#endif
			}
		}
	}

	CTimeElement::Draw(pGraphics, nPane, rect, bSelected);
#endif
}

/////////////////////////////////////////////////////////////////////////

#define REMAINDER(t, d) (t - d*floor(t/d))

//virtual
void CTimeManipulationNode::Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
{
	double secondWidth = m_pGraphView->m_secondWidth;

	int m_width = GetTimeElement()->m_width;

	LDraw::BBoxi trc(1/*+textIndent*TXINDENT*/, 1, m_width*secondWidth, TXHEIGHT);
#if 0
	FillSolidRect(hDC, &trc, bSelected? COLOR_SELECTED: COLOR_NODE);
#endif

	if (m_expanded)
	{
		int ymid = TXHEIGHT/2;
		int xmid = 1+4;
		int length = 8;

		LDraw::PointI pts[3] =
		{
			LDraw::PointI(xmid-length/2, ymid-length/4),
			LDraw::PointI(xmid+length/2, ymid-length/4),
			LDraw::PointI(xmid, ymid+length/4),
		};

#if 0
		Polygon(hDC, pts, 3);
#endif
	}
	else
	{
		int ymid = TXHEIGHT/2;
		int length = 8;

		LDraw::PointI pts[3] =
		{
			LDraw::PointI(2, ymid-length/2),
			LDraw::PointI(2, ymid+length/2),
			LDraw::PointI(2+length/2, ymid),
		};

#if 0
		Polygon(hDC, pts, 3);
#endif
	}

	System::StringW* str = WSTR("Time Manipulation");
	trc.left += 12;
	ASSERT(0);
#if 0
#if 0
	SetTextColor(hDC, bSelected? RGB(255, 255, 255): RGB(0,0,0));
	DrawText(hDC, str, str.GetLength(), &trc, DT_SINGLELINE | DT_END_ELLIPSIS);
#endif

	if (m_expanded)
	{
#if 0
		Rectangle(hDC, 0, TXHEIGHT+1, m_width*secondWidth, m_height);
#endif

		CTimeElement* pTimeElement = GetTimeElement();

		CComQIPtr<ILElementTime> elementTime = pTimeElement->m_domElement;

		double tspeed;
		elementTime->get_speed(&tspeed);

		double taccelerate;
		elementTime->get_accelerate(&taccelerate);

		double tdecelerate;
		elementTime->get_decelerate(&tdecelerate);

		VARIANT_BOOL autoReverse;
		elementTime->get_autoReverse(&autoReverse);

		double parent_speed = 1;
		double AD;
		elementTime->getActiveDuration(&AD);//= m_AD;//m_dur;// ? AD=Active Duration?

	//	CComPtr<ILTimeInterval>

		int height = m_height - (TXHEIGHT+2+1);

		int widthPixels = m_width * secondWidth;

		for (int x = 0; x < widthPixels; x++)
		{
			//double tps;	// parent simple time
			double m_tau = x/secondWidth;	// active time
			//m_tau = tps - m_pCurrentInterval->m_begin;

			double speed = tspeed;
			double acc = taccelerate;
			double dec = tdecelerate;

			if (acc+dec > 1)	// Ignore both attributes
			{
				acc = 0;
				dec = 0;
			}
			//if (speed == 0) speed = 0 ??

			double taf;

			if (speed > 0) // i.e. if the local speed is forwards 
				taf = m_tau * speed;
			else //  i.e. if the local speed is backwards 
				taf = AD - m_tau * fabs(speed);

			//Let dur be the value of the simple duration as defined by the Timing and Synchronization model.
			// This is the actual simple duration, and not simply the dur attribute.
			//This value does not account for the effect of any time manipulations.
			double dur;// = m_dur;
			elementTime->get_dur(&dur);

			if (dur < 0) dur = 99999999;	// indefinite (Is this correct?)

			// pThis->m_simpleDur has accounted for autoReverse
			double dur_;// = m_simpleDur;
			elementTime->getSimpleDuration(&dur_);

			double tsu = REMAINDER(taf, dur_);

		// Account for autoReverse behavior.
			double tsu_;

			if (autoReverse != VARIANT_TRUE)
			{
				tsu_ = tsu;
			}
			else
			{
				if (tsu < dur)
					tsu_ = tsu;
				else
					//tsu_ = /*dur - (tsu - dur) =*/ 2*dur - tsu;
					tsu_ = 2*dur - tsu;
			}

		// Calculate filtered time (tsf)

		// Account for acceleration/deceleration
			double tsf;

			double dacc = acc*dur;
			double ddec = dec*dur;

			double r = 1 / (1 - acc/2 - dec/2);

			if (tsu_ < dacc)
			{
				double rt = r * (tsu_ / dacc);

				tsf = tsu_ * rt / 2;
			}
			else if (tsu_ > (dur - ddec))
			{
				double rt = r * (dur - tsu_) / ddec;

				double tdec =  tsu_ - (dur - ddec);
				double pd =  tdec / ddec;

				tsf = r * (dur - dacc / 2 - ddec + tdec * (2 - pd) / 2);
			}
			else
			{
				tsf = r * (tsu_ - dacc / 2);
			}

			double m_tsf = tsf;

			int y = height - (m_tsf/dur * height);

			y += TXHEIGHT+1+1;

#if 0
			if (x == 0)
				MoveToEx(hDC, x, y, NULL);
			else
				LineTo(hDC, x, y);
#endif
			//SetPixelV(hDC, x, TXHEIGHT + y, RGB(0,0,0));
		}
	}
#endif
}

/////////////////////////////////////////////////////////////////////////
// CAnimationValue

// virtual
void CAnimationValue::Draw(MSWindows::HDC hDC, int nPane, LDraw::BBoxi rect, bool bSelected)
{
	ASSERT(0);
#if 0
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	CPen selectedPen;
	selectedPen.CreatePen(PS_SOLID, 1, RGB(0, 60, 200));

	HPEN hOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);

	CAnimationElement* pAnimationElement = GetAnimationElement();

	double secondWidth = m_pGraphView->m_secondWidth;

	//CComQIPtr<ILDOMElement> element = pAnimationm_domElement;
	//CComQIPtr<ILAnimationElement> animation = m_domElement;
	CComQIPtr<ILElementAnimate> elementAnimate = pAnimationElement->m_domElement;
	CComQIPtr<ILAnimateXXX> animateXXX = pAnimationElement->m_domElement;

	CComPtr<IEXMLDocument> edocument;
	m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

	CComPtr<IEElement> eelement;
	edocument->GetEElementFromDOMElement(pAnimationElement->m_domElement, &eelement);
	ASSERT(eelement);

	CComPtr<IESelectedElement> selectedElement;
	m_pGraphView->m_viewGroup->GetSelectedElement(eelement, &selectedElement);

	CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

	if (animateXXX)
	{
		long nkeys;
		animateXXX->GetNValues(&nkeys);

		Rectangle(hDC, 0, 0, GetAnimationElement()->m_width*secondWidth, m_height);

		double scaleX = pAnimationElement->m_width*secondWidth;

		LCalcModeType calcMode;
		elementAnimate->get_calcMode(&calcMode);

		for (int i = 0; i < nkeys; i++)
		{
			int x0 = 0 + pAnimationElement->m_keyTimes[i]*scaleX;

			CComPtr<ILSMILAttributeValue> value;
			animateXXX->GetValue(i, &value);

			CComPtr<ILCSSValue> cssvalue;
			value->getObject((IUnknown**)&cssvalue);
			if (cssvalue)
			{
				CComQIPtr<ILCSSPrimitiveValue> cssprimitive = cssvalue;

				double fvalue;
				cssprimitive->getFloatValue(CSS_NUMBER, &fvalue);

				double minValue = 0;
				double maxValue = 1;

				int y0 = 2 + (m_height-2) - fvalue * (m_height-4);

				SelectObject(hDC, selectedPen);
				Rectangle(hDC, x0-2, y0-2, x0+3, y0+3);

				SelectObject(hDC, pen);

				VARIANT_BOOL bSelected;
				if (selectedAnimationElement)
					selectedAnimationElement->IsKeyTimeSelected(i, &bSelected);
				else
					bSelected = VARIANT_FALSE;

				if (i < nkeys-1)
				{
					VARIANT_BOOL bSelected1;
					if (selectedAnimationElement)
						selectedAnimationElement->IsKeyTimeSelected(i+1, &bSelected1);
					else
						bSelected1 = VARIANT_FALSE;

					int x3 = 0 + pAnimationElement->m_keyTimes[i+1]*scaleX;

					CComPtr<ILSMILAttributeValue> value1;
					animateXXX->GetValue(i+1, &value1);

					CComPtr<ILCSSValue> cssvalue1;
					value1->getObject((IUnknown**)&cssvalue1);
					CComQIPtr<ILCSSPrimitiveValue> cssprimitive1 = cssvalue1;

					double fvalue1;
					cssprimitive1->getFloatValue(CSS_NUMBER, &fvalue1);

					int y3 = 2 + (m_height-2) - fvalue1 * (m_height-4);

					if (calcMode == CALCMODE_DISCRETE)
					{
						MoveToEx(hDC, x0, y0, NULL);
						LineTo(hDC, x3, y0);
					}
					else if (calcMode == CALCMODE_LINEAR)
					{
						MoveToEx(hDC, x0, y0, NULL);
						LineTo(hDC, x3, y3);
					}
					else if (calcMode == CALCMODE_SPLINE)
					{
						CComPtr<ILKeySpline> keySpline;
						animateXXX->GetKeySpline(i, &keySpline);

						if (keySpline)
						{
							MoveToEx(hDC, x0, y0, NULL);

							double x1, y1, x2, y2;
							keySpline->get_x1(&x1);
							keySpline->get_y1(&y1);
							keySpline->get_x2(&x2);
							keySpline->get_y2(&y2);

							/*
							int x1 = x0 + fx1*(x3-x0);
							int y1 = y0 + fy1*(y3-y0);

							int x2 = x0 + (fx2)*(x3-x0);
							int y2 = y0 + (fy2)*(y3-y0);
							*/

							for (double it = 0; it <= 1; it += 0.01)
							{
								double ot;

								{
									double x0 = 0;
									double y0 = 0;
									double x3 = 1;
									double y3 = 1;

									for (double t = 0; t < 1; t += 0.001)
									{
										double cx = 3 * (x1 - x0);
										double cy = 3 * (y1 - y0);
										double bx = 3 * (x2 - x1) - cx;
										double by = 3 * (y2 - y1) - cy;
										double ax = x3 - x0 - cx - bx;
										double ay = y3 - y0 - cy - by;

										double xt = ax * t*t*t + bx * t*t + cx * t + x0;
										double yt = ay * t*t*t + by * t*t + cy * t + y0;

										if (xt >= it)
										{
											ot = yt;
											break;
										}
									}
								}

								double _fvalue = fvalue + (fvalue1 - fvalue)*ot;

								int y = 2 + (m_height-2) - _fvalue * (m_height-4);
						
								LineTo(hDC, x0 + it * (x3-x0), y);
							}
						}
					}
				}
			}
		}
	}

	SelectObject(hDC, hOldPen);
#endif
}

// virtual
CTGNode* CAnimationValue::OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
	ASSERT(0);
#if 0
	dragging = 1;

	CAnimationElement* pAnimationElement = GetAnimationElement();

	double secondWidth = m_pGraphView->m_secondWidth;

	CComQIPtr<ILElementAnimate> elementAnimate = pAnimationElement->m_domElement;
	CComQIPtr<ILAnimateXXX> animateXXX = pAnimationElement->m_domElement;

	CComPtr<IEXMLDocument> edocument;
	m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

	CComPtr<IEElement> eelement;
	edocument->GetEElementFromDOMElement(pAnimationElement->m_domElement, &eelement);
	ASSERT(eelement);

	CComPtr<IESelectedElement> selectedElement;
	m_pGraphView->m_viewGroup->GetSelectedElement(eelement, &selectedElement);

	CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

	long nkeys;
	animateXXX->GetNValues(&nkeys);

	double scaleX = pAnimationElement->m_width*secondWidth;

	LCalcModeType calcMode;
	elementAnimate->get_calcMode(&calcMode);

	for (int i = 0; i < nkeys; i++)
	{
		int x0 = 0 + pAnimationElement->m_keyTimes[i]*scaleX;

		CComPtr<ILSMILAttributeValue> value;
		animateXXX->GetValue(i, &value);

		CComPtr<ILCSSValue> cssvalue;
		value->getObject((IUnknown**)&cssvalue);
		CComQIPtr<ILCSSPrimitiveValue> cssprimitive = cssvalue;

		double fvalue;
		cssprimitive->getFloatValue(CSS_NUMBER, &fvalue);

		double minValue = 0;
		double maxValue = 1;

		int y0 = 2 + (m_height-2) - fvalue * (m_height-4);

		VARIANT_BOOL bSelected;
		if (selectedAnimationElement)
			selectedAnimationElement->IsKeyTimeSelected(i, &bSelected);
		else
			bSelected = VARIANT_FALSE;

		if (i < nkeys-1)
		{
			VARIANT_BOOL bSelected1;
			if (selectedAnimationElement)
				selectedAnimationElement->IsKeyTimeSelected(i+1, &bSelected1);
			else
				bSelected1 = VARIANT_FALSE;

			int x3 = 0 + pAnimationElement->m_keyTimes[i+1]*scaleX;

			CComPtr<ILSMILAttributeValue> value1;
			animateXXX->GetValue(i+1, &value1);

			CComPtr<ILCSSValue> cssvalue1;
			value1->getObject((IUnknown**)&cssvalue1);
			CComQIPtr<ILCSSPrimitiveValue> cssprimitive1 = cssvalue1;

			double fvalue1;
			cssprimitive1->getFloatValue(CSS_NUMBER, &fvalue1);

			int y3 = 2 + (m_height-2) - fvalue1 * (m_height-4);

			if (calcMode == CALCMODE_DISCRETE)
			{
			}
			else if (calcMode == CALCMODE_LINEAR)
			{
			}
			else if (calcMode == CALCMODE_SPLINE)
			{
				CComPtr<ILKeySpline> keySpline;
				animateXXX->GetKeySpline(i, &keySpline);

				if (keySpline)
				{
					double fx1, fy1, fx2, fy2;
					keySpline->get_x1(&fx1);
					keySpline->get_y1(&fy1);
					keySpline->get_x2(&fx2);
					keySpline->get_y2(&fy2);

					int x1 = x0 + fx1*(x3-x0);
					int y1 = y0 + fy1*(y3-y0);

					int x2 = x0 + (fx2)*(x3-x0);
					int y2 = y0 + (fy2)*(y3-y0);

					if (abs(point.x-x1) < 3 && abs(point.y-y1) < 3)
					{
						m_nKey = i;
						dragging = 2;
					}
					else if (abs(point.x-x2) < 3 && abs(point.y-y2) < 3)
					{
						m_nKey = i;
						dragging = 3;
					}
				}
			}
		}
	}
#endif
	return this;
}

// virtual
void CAnimationValue::OnDrag(LDraw::PointD point, long dragging)
{
	ASSERT(0);
#if 0
	CAnimationElement* pAnimationElement = GetAnimationElement();

	if (dragging == 1)
	{
		int yoffset = -point.y;// - m_oldpt.y;
		//m_oldpt = point;

		CComQIPtr<ILAnimateXXX> animateXXX = pAnimationElement->m_domElement;

		CComPtr<IEXMLDocument> edocument;
		m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

		CComPtr<IEElement> eelement;
		edocument->GetEElementFromDOMElement(pAnimationElement->m_domElement, &eelement);
		ASSERT(eelement);

		CComPtr<IESelectedElement> selectedElement;
		m_pGraphView->m_viewGroup->GetSelectedElement(eelement, &selectedElement);

		CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
		ASSERT(selectedAnimationElement);

		long nselectedKeys;
		selectedAnimationElement->GetSelectedKeyTimesCount(&nselectedKeys);

		double foffset = (double)yoffset / (m_height-4);

		for (int i = 0; i < nselectedKeys; i++)
		{
			long nkey;
			selectedAnimationElement->GetKeyTimeSelected(i, &nkey);

			CComPtr<ILSMILAttributeValue> value;
			animateXXX->GetValue(nkey, &value);

			CComPtr<ILCSSValue> cssvalue;
			value->getObject((IUnknown**)&cssvalue);

			CComQIPtr<ILCSSPrimitiveValue> cssprimitive = cssvalue;

			double fvalue;
			cssprimitive->getFloatValue(CSS_NUMBER, &fvalue);

			fvalue += foffset;

			cssprimitive->setFloatValue(CSS_NUMBER, fvalue);
		}
	}
	else
	{
#if 0
		CComPtr<ILKeySpline> keySpline;
		animateXXX->GetKeySpline(m_nKey, &keySpline);

		if (keySpline)
		{
			double fx1, fy1, fx2, fy2;
			keySpline->get_x1(&fx1);
			keySpline->get_y1(&fy1);
			keySpline->get_x2(&fx2);
			keySpline->get_y2(&fy2);

			int x1 = x0 + fx1*(x3-x0);
			int y1 = y0 + fy1*(y3-y0);

			int x2 = x0 + (fx2)*(x3-x0);
			int y2 = y0 + (fy2)*(y3-y0);

			double fx1 = (-x0 + x1)/(x3-x0);

			if (dragging == 2)
			{
			}
			else if (dragging == 3)
			{
			}
		}
#endif
	}
#endif
}

/////////////////////////////////////////////////////////////////////////
// CAnimationVelocity

// virtual
void CAnimationVelocity::Draw(MSWindows::HDC hDC, int nPane, LDraw::BBoxi rect, bool bSelected)
{
	ASSERT(0);
#if 0
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	CPen selectedPen;
	selectedPen.CreatePen(PS_SOLID, 1, RGB(0, 60, 200));

	HPEN hOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);

	CAnimationElement* pAnimationElement = GetAnimationElement();

	double secondWidth = m_pGraphView->m_secondWidth;

	//CComQIPtr<ILDOMElement> element = pAnimationm_domElement;
	//CComQIPtr<ILAnimationElement> animation = m_domElement;
	//CComQIPtr<ILElementTime> elementTime = m_domElement;

	CComQIPtr<ILElementAnimate> elementAnimate = pAnimationElement->m_domElement;
	CComQIPtr<ILAnimateXXX> animateXXX = pAnimationElement->m_domElement;

	if (animateXXX)
	{
		CComPtr<IEXMLDocument> edocument;
		m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

		CComPtr<IEElement> eelement;
		edocument->GetEElementFromDOMElement(pAnimationElement->m_domElement, &eelement);
		ASSERT(eelement);

		CComPtr<IESelectedElement> selectedElement;
		m_pGraphView->m_viewGroup->GetSelectedElement(eelement, &selectedElement);

		CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

		long nkeys;
		animateXXX->GetNValues(&nkeys);

		Rectangle(hDC, 0, 0, GetAnimationElement()->m_width*secondWidth, m_height);

		double scaleX = pAnimationElement->m_width*secondWidth;

		LCalcModeType calcMode;
		elementAnimate->get_calcMode(&calcMode);

		for (int i = 0; i < nkeys; i++)
		{
			int x0 = 0 + pAnimationElement->m_keyTimes[i]*scaleX;

			CComPtr<ILSMILAttributeValue> value;
			animateXXX->GetValue(i, &value);

			CComPtr<ILCSSValue> cssvalue;
			value->getObject((IUnknown**)&cssvalue);

			if (cssvalue)
			{
				CComQIPtr<ILCSSPrimitiveValue> cssprimitive = cssvalue;

				double fvalue;
				cssprimitive->getFloatValue(CSS_NUMBER, &fvalue);

				double minValue = 0;
				double maxValue = 1;

				int y0 = 2 + (m_height-2) - fvalue * (m_height-4);

				SelectObject(hDC, selectedPen);
				Rectangle(hDC, x0-2, y0-2, x0+3, y0+3);

				SelectObject(hDC, pen);

				VARIANT_BOOL bSelected;
				if (selectedAnimationElement)
					selectedAnimationElement->IsKeyTimeSelected(i, &bSelected);
				else
					bSelected = VARIANT_FALSE;

				if (i < nkeys-1)
				{
					VARIANT_BOOL bSelected1;
					if (selectedAnimationElement)
						selectedAnimationElement->IsKeyTimeSelected(i+1, &bSelected1);
					else
						bSelected1 = VARIANT_FALSE;

					int x3 = 0 + pAnimationElement->m_keyTimes[i+1]*scaleX;

					CComPtr<ILSMILAttributeValue> value1;
					animateXXX->GetValue(i+1, &value1);

					CComPtr<ILCSSValue> cssvalue1;
					value1->getObject((IUnknown**)&cssvalue1);
					CComQIPtr<ILCSSPrimitiveValue> cssprimitive1 = cssvalue1;

					double fvalue1;
					cssprimitive1->getFloatValue(CSS_NUMBER, &fvalue1);

					int y3 = 2 + (m_height-2) - fvalue1 * (m_height-4);

					if (calcMode == CALCMODE_DISCRETE)
					{
						MoveToEx(hDC, x0, y0, NULL);
						LineTo(hDC, x3, y0);
					}
					else if (calcMode == CALCMODE_LINEAR)
					{
						MoveToEx(hDC, x0, y0, NULL);
						LineTo(hDC, x3, y3);
					}
					else if (calcMode == CALCMODE_SPLINE)
					{
						CComPtr<ILKeySpline> keySpline;
						animateXXX->GetKeySpline(i, &keySpline);

						if (keySpline)
						{
							double fx1, fy1, fx2, fy2;
							keySpline->get_x1(&fx1);
							keySpline->get_y1(&fy1);
							keySpline->get_x2(&fx2);
							keySpline->get_y2(&fy2);

							int x1 = x0 + fx1*(x3-x0);
							int y1 = y0 + fy1*(y3-y0);

							int x2 = x0 + (fx2)*(x3-x0);
							int y2 = y0 + (fy2)*(y3-y0);

							POINT pts[4] =
							{
								x0, y0,
								x1, y1,
								x2, y2,
								x3, y3,
							};

							PolyBezier(hDC, pts, 4);

							SelectObject(hDC, selectedPen);

							// Draw control points
							if (bSelected || bSelected1)
							{
								Ellipse(hDC, x1-2, y1-2, x1+2, y1+2);
								MoveToEx(hDC, x0, y0, NULL);
								LineTo(hDC, x1, y1);
							}

							if (bSelected || bSelected1)
							{
								Ellipse(hDC, x2-2, y2-2, x2+2, y2+2);
								MoveToEx(hDC, x3, y3, NULL);
								LineTo(hDC, x2, y2);
							}
						}
					}
				}
			}
		}
	}

	SelectObject(hDC, hOldPen);
#endif
}

// virtual
CTGNode* CAnimationVelocity::OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
	ASSERT(0);
#if 0
	dragging = 1;

	CAnimationElement* pAnimationElement = GetAnimationElement();

	double secondWidth = m_pGraphView->m_secondWidth;

	CComQIPtr<ILElementAnimate> elementAnimate = pAnimationElement->m_domElement;
	CComQIPtr<ILAnimateXXX> animateXXX = pAnimationElement->m_domElement;

	CComPtr<IEXMLDocument> edocument;
	m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

	CComPtr<IEElement> eelement;
	edocument->GetEElementFromDOMElement(pAnimationElement->m_domElement, &eelement);
	ASSERT(eelement);

	CComPtr<IESelectedElement> selectedElement;
	m_pGraphView->m_viewGroup->GetSelectedElement(eelement, &selectedElement);

	CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

	long nkeys;
	animateXXX->GetNValues(&nkeys);

	double scaleX = pAnimationElement->m_width*secondWidth;

	LCalcModeType calcMode;
	elementAnimate->get_calcMode(&calcMode);

	for (int i = 0; i < nkeys; i++)
	{
		int x0 = 0 + pAnimationElement->m_keyTimes[i]*scaleX;

		CComPtr<ILSMILAttributeValue> value;
		animateXXX->GetValue(i, &value);

		CComPtr<ILCSSValue> cssvalue;
		value->getObject((IUnknown**)&cssvalue);
		CComQIPtr<ILCSSPrimitiveValue> cssprimitive = cssvalue;

		double fvalue;
		cssprimitive->getFloatValue(CSS_NUMBER, &fvalue);

		double minValue = 0;
		double maxValue = 1;

		int y0 = 2 + (m_height-2) - fvalue * (m_height-4);

		VARIANT_BOOL bSelected;
		if (selectedAnimationElement)
			selectedAnimationElement->IsKeyTimeSelected(i, &bSelected);
		else
			bSelected = VARIANT_FALSE;

		if (i < nkeys-1)
		{
			VARIANT_BOOL bSelected1;
			if (selectedAnimationElement)
				selectedAnimationElement->IsKeyTimeSelected(i+1, &bSelected1);
			else
				bSelected1 = VARIANT_FALSE;

			int x3 = 0 + pAnimationElement->m_keyTimes[i+1]*scaleX;

			CComPtr<ILSMILAttributeValue> value1;
			animateXXX->GetValue(i+1, &value1);

			CComPtr<ILCSSValue> cssvalue1;
			value1->getObject((IUnknown**)&cssvalue1);
			CComQIPtr<ILCSSPrimitiveValue> cssprimitive1 = cssvalue1;

			double fvalue1;
			cssprimitive1->getFloatValue(CSS_NUMBER, &fvalue1);

			int y3 = 2 + (m_height-2) - fvalue1 * (m_height-4);

			if (calcMode == CALCMODE_DISCRETE)
			{
			}
			else if (calcMode == CALCMODE_LINEAR)
			{
			}
			else if (calcMode == CALCMODE_SPLINE)
			{
				CComPtr<ILKeySpline> keySpline;
				animateXXX->GetKeySpline(i, &keySpline);

				if (keySpline)
				{
					double fx1, fy1, fx2, fy2;
					keySpline->get_x1(&fx1);
					keySpline->get_y1(&fy1);
					keySpline->get_x2(&fx2);
					keySpline->get_y2(&fy2);

					int x1 = x0 + fx1*(x3-x0);
					int y1 = y0 + fy1*(y3-y0);

					int x2 = x0 + (fx2)*(x3-x0);
					int y2 = y0 + (fy2)*(y3-y0);

					if (abs(point.x-x1) < 3 && abs(point.y-y1) < 3)
					{
						m_nKey = i;
						dragging = 2;
					}
					else if (abs(point.x-x2) < 3 && abs(point.y-y2) < 3)
					{
						m_nKey = i;
						dragging = 3;
					}
				}
			}
		}
	}
#endif
	return this;
}

// virtual
void CAnimationVelocity::OnDrag(LDraw::PointD point, long dragging)
{
	ASSERT(0);
#if 0
	CAnimationElement* pAnimationElement = GetAnimationElement();

	if (dragging == 1)
	{
		int yoffset = -point.y;// - m_oldpt.y;
		//m_oldpt = point;

		CComQIPtr<ILAnimateXXX> animateXXX = pAnimationElement->m_domElement;

		CComPtr<IEXMLDocument> edocument;
		m_pGraphView->m_viewGroup->get_eXMLDocument(&edocument);

		CComPtr<IEElement> eelement;
		edocument->GetEElementFromDOMElement(pAnimationElement->m_domElement, &eelement);
		ASSERT(eelement);

		CComPtr<IESelectedElement> selectedElement;
		m_pGraphView->m_viewGroup->GetSelectedElement(eelement, &selectedElement);

		CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;
		ASSERT(selectedAnimationElement);

		long nselectedKeys;
		selectedAnimationElement->GetSelectedKeyTimesCount(&nselectedKeys);

		double foffset = (double)yoffset / (m_height-4);

		for (int i = 0; i < nselectedKeys; i++)
		{
			long nkey;
			selectedAnimationElement->GetKeyTimeSelected(i, &nkey);

			CComPtr<ILSMILAttributeValue> value;
			animateXXX->GetValue(nkey, &value);

			CComPtr<ILCSSValue> cssvalue;
			value->getObject((IUnknown**)&cssvalue);

			CComQIPtr<ILCSSPrimitiveValue> cssprimitive = cssvalue;

			double fvalue;
			cssprimitive->getFloatValue(CSS_NUMBER, &fvalue);

			fvalue += foffset;

			cssprimitive->setFloatValue(CSS_NUMBER, fvalue);
		}
	}
	else
	{
#if 0
		CComPtr<ILKeySpline> keySpline;
		animateXXX->GetKeySpline(m_nKey, &keySpline);

		if (keySpline)
		{
			double fx1, fy1, fx2, fy2;
			keySpline->get_x1(&fx1);
			keySpline->get_y1(&fy1);
			keySpline->get_x2(&fx2);
			keySpline->get_y2(&fy2);

			int x1 = x0 + fx1*(x3-x0);
			int y1 = y0 + fy1*(y3-y0);

			int x2 = x0 + (fx2)*(x3-x0);
			int y2 = y0 + (fy2)*(y3-y0);

			double fx1 = (-x0 + x1)/(x3-x0);

			if (dragging == 2)
			{
			}
			else if (dragging == 3)
			{
			}
		}
#endif
	}
#endif
}

void CTGElement::BuildTimeGraph(Element* parentElement)
{
//	ASSERT(m_domElement != NULL);

	Node* child = parentElement->get_firstChild();

	while (child != NULL)
	{
		Web::NodeType nodeType = child->get_nodeType();

		if (nodeType == Web::NODE_ELEMENT)
		{
			Element* element = dynamic_cast<Element*>(child);

			System::StringW* timeContainer = element->getAttribute(WSTR("timeContainer"));
			/*
			CComQIPtr<ILElementTimeContainer> timeContainerElement = child;
			if (timeContainerElement)
				timeContainerElement->get_timeContainer(&timeContainer);
			else
				timeContainer = L"none";
				*/

			System::StringW* namespaceURI = element->get_namespaceURI();//GetElementNamespaceURI(element);
			System::StringW* tagName = element->get_nodeName();
		//	_bstr_t timeContainer = GetElementTimeContainer(element);

			CTGElement* pElement = m_pGraphView->CreateTGElement(element);
			if (pElement)
			{
				AddChildTail(pElement);

				pElement->BuildTimeGraph(pElement->m_domElement);
			}
		}

		child = child->get_nextSibling();
	}

	if (true)
	{
		CTGEmpty* p = new CTGEmpty;
		p->m_pGraphView = m_pGraphView;
		AddChildTail(p);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// CTransNode

// virtual
void CTransNode::Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected)
{
	ASSERT(0);
#if 0
	//CDCHandle dc(hDC);

#if 0
	dc.FillSolidRect(0, m_itemHeight, rect.Width(), 1, RGB(255, 255, 255));
#endif

	if (nPane == PANE_NAME)
	{
		int paneWidth = rect.Width();

		LDraw::BBoxi rect2(2, 0, paneWidth-2, TXHEIGHT);

		if (m_expanded)
		{
			int midx = 6;
			int midy = rect2.Height()/2;

			POINT pts[] =
			{
				midx-4, midy-2,
				midx+4, midy-2,
				midx, midy+2
			};

#if 0
			dc.Polygon(pts, 3);
#endif
		}
		else
		{
			int midy = rect2.Height()/2;

			POINT pts[] =
			{
				rect2.left+2, midy-4,
				rect2.left+2, midy+4,
				rect2.left+2+4, midy
			};

#if 0
			dc.Polygon(pts, 3);
#endif
		}

		LDraw::BBoxi trect = rect2;
		trect.left += 14;
		if (m_selected)
		{
#if 0
			dc.FillSolidRect(&trect, GetSysColor(COLOR_HIGHLIGHT));
			dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
#endif
		}
		else
		{
#if 0
			dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
#endif
		}
#if 0
		dc.DrawText(m_name, m_name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
#endif

		if (m_expanded)
		{
			CTimeElement* pTimeElement = (CTimeElement*)m_parent;

			CComQIPtr<ILSMILMediaElement> mediaElement = pTimeElement->m_domElement;
			if (mediaElement)
			{
				CComPtr<ILSVGStringList> trans;
				if (!wcscmp(m_name, L"transIn"))
					mediaElement->get_transIn(&trans);
				else
					mediaElement->get_transOut(&trans);

				long numberOfItems;
				trans->get_numberOfItems(&numberOfItems);

				int dy = TXHEIGHT;

				for (int i = 0; i < numberOfItems; i++)
				{
					CComBSTR transitionId;
					trans->getItem(i, &transitionId);

					LDraw::BBoxi trect2;
					trect2.left = trect.left+6;
					trect2.top = dy;
					trect2.right = trect.right;
					trect2.bottom = dy+TXHEIGHT;

#if 0
					if (m_childSelectedIndex == i)
					{
						dc.FillSolidRect(&trect2, GetSysColor(COLOR_HIGHLIGHT));
						dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
					}
					else
					{
						dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
					}

					dc.DrawText(_bstr_t(transitionId), transitionId.Length(), &trect2, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
#endif

					dy += TXHEIGHT;
				}
			}
		}
	}
	else if (nPane == PANE_TIMELINE)
	{
		CComPtr<ILDOMDocument> document;
		m_pGraphView->m_viewGroup->m_pDocument->get_DOMDocument(&document);

		double secondWidth = m_pGraphView->m_secondWidth;

		if (m_expanded)
		{
			CTimeElement* pTimeElement = (CTimeElement*)m_parent;

			CComQIPtr<ILSMILMediaElement> mediaElement = pTimeElement->m_domElement;
			if (mediaElement)
			{
				CComPtr<ILSVGStringList> trans;
				if (!wcscmp(m_name, L"transIn"))
					mediaElement->get_transIn(&trans);
				else
					mediaElement->get_transOut(&trans);

				long numberOfItems;
				trans->get_numberOfItems(&numberOfItems);

				int dy = TXHEIGHT;

				for (int i = 0; i < numberOfItems; i++)
				{
					CComBSTR transitionId;
					trans->getItem(i, &transitionId);

					CComPtr<ILDOMElement> element;
					document->getElementById(transitionId, &element);
					CComQIPtr<ILSMILTransitionElement> transitionElement = element;
					if (transitionElement)
					{
						double dur;
						transitionElement->get_dur(&dur);

						LDraw::BBoxi trc;
						if (!wcscmp(m_name, L"transIn"))
							trc = LDraw::BBoxi(pTimeElement->m_x*secondWidth, dy+1, (pTimeElement->m_x+dur)*secondWidth, dy+TXHEIGHT);
						else
							trc = LDraw::BBoxi((pTimeElement->m_x+pTimeElement->m_width-dur)*secondWidth, dy+1, (pTimeElement->m_x+pTimeElement->m_width)*secondWidth, dy+TXHEIGHT);

#if 0
						dc.FillSolidRect(&trc, RGB(100, 200, 100));
#endif

						CBrush brush;
						brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
#if 0
						HBRUSH hOldBrush = dc.SelectBrush(brush);
#endif

						// Draw out knob
						if (!wcscmp(m_name, L"transIn"))
						{
							POINT pts[] =
							{
								trc.right, trc.top,
								trc.right, trc.bottom-1,
								trc.right+TXHEIGHT/2, trc.bottom-1,
								trc.right+TXHEIGHT/2, trc.top+TXHEIGHT/2,
								trc.right, trc.top
							};

#if 0
							dc.Polygon(pts, 5);
#endif
						}
						else
						{
							POINT pts[] =
							{
								trc.left-1, trc.top,
								trc.left-1, trc.bottom-1,
								trc.left-1-TXHEIGHT/2, trc.bottom-1,
								trc.left-1-TXHEIGHT/2, trc.top+TXHEIGHT/2,
								trc.left-1, trc.top
							};

#if 0
							dc.Polygon(pts, 5);
#endif
						}

#if 0
						dc.SelectBrush(hOldBrush);
#endif
					}

					dy += TXHEIGHT;
				}
			}
		}
	}
#endif
}

// virtual
void CTransNode::CalculateSize()
{
	ASSERT(0);
#if 0
	m_itemHeight = TXHEIGHT;
	m_height = TXHEIGHT;

	if (m_expanded)
	{
		CComQIPtr<ILSMILMediaElement> mediaElement = m_parent->m_domElement;
		if (mediaElement)
		{
			CComPtr<ILSVGStringList> trans;
			if (!wcscmp(m_name, L"transIn"))
				mediaElement->get_transIn(&trans);
			else
				mediaElement->get_transOut(&trans);

			long numberOfItems;
			trans->get_numberOfItems(&numberOfItems);

			m_height += numberOfItems*TXHEIGHT;
		}
	}
#endif
}

// virtual
CTGNode* CTransNode::OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
{
	if (nPane == PANE_NAME)
	{
		if (point.Y < m_height)
		{
			if (point.Y < TXHEIGHT)
			{
				if (point.X >= 0 && point.X < 14)
				{
					m_expanded = !m_expanded;
				}
			}
			else
			{
				m_childSelectedIndex = (point.Y-TXHEIGHT)/TXHEIGHT;
				m_pGraphView->m_mode = 3;
			}

			return this;
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CSmilTimeGraphView

CSmilTimeGraphView::CSmilTimeGraphView()
{
	m_body = NULL;
//	m_hSmallFont = NULL;

	m_dragging = 0;

	m_mode = 0;

	m_pActiveNode = NULL;

	m_iconSize = 1;
	m_trackFormat = 3;

	m_iconDuration = 6;
//	m_compDuration = 3600;	// 1 hour
//	m_compDuration = 600;	// 10 minutes
	m_compDuration = 300;	// 5 minutes
	m_secondWidth = 5;
	//IconSize[m_iconSize].cx / m_iconDuration

	m_viewGroup = NULL;

	m_userDataKey = WSTR("TimeGraph");

	m_panes.Add(new CPane(this, WSTR("Name"), 110));
	m_panes.Add(new CPane(this, WSTR("Keys"), 60));

	m_panes.Add(new CPane(this, NULL, 135));
//	hr = m_panes[PANE_ATTRIBUTES-1]->m_horz.CoCreateInstance(CLSID_UIScrollBar);
//	if (FAILED(hr)) return hr;
//	m_panes[PANE_ATTRIBUTES-1]->m_horz->put_direction(0);
	{
		//m_panes[PANE_ATTRIBUTES-1]->m_subpanes.push_back(new CPane(this, "begin", 45));
		//m_panes[PANE_ATTRIBUTES-1]->m_subpanes.push_back(new CPane(this, "end", 45));
		m_panes[PANE_ATTRIBUTES-1]->m_subpanes.Add(new CPane(this, WSTR("dur"), 45));
		m_panes[PANE_ATTRIBUTES-1]->m_subpanes.Add(new CPane(this, WSTR("min"), 45));
		m_panes[PANE_ATTRIBUTES-1]->m_subpanes.Add(new CPane(this, WSTR("max"), 45));
//		m_panes[PANE_ATTRIBUTES]->m_subpanes.push_back(new CPane("clipBegin", 45));
//		m_panes[PANE_ATTRIBUTES]->m_subpanes.push_back(new CPane("clipEnd", 45));
	}

	m_panes.Add(new CPane(this, WSTR("Times"), 80));

	{
		m_panes.Add(new CPane(this, NULL, -1));

	//	hr = m_panes[PANE_TIMELINE-1]->m_horz.CoCreateInstance(CLSID_UIScrollBar);
	//	if (FAILED(hr)) return hr;

	//	hr = m_panes[PANE_TIMELINE-1]->m_slider.CoCreateInstance(CLSID_UISlider);
	//	if (FAILED(hr)) return hr;

		m_panes[PANE_TIMELINE-1]->m_scrollbarLeft = 50;
	//	m_panes[PANE_TIMELINE-1]->m_horz->put_direction(0);
	}
}

#if 0
int CSmilTimeGraphView::FinalConstruct()
{
	ErrorCode hr;

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);

	GUID guid;
	::CoCreateGuid(&guid);

	LPOLESTR guidstr;
	StringFromCLSID(guid, &guidstr);
	m_userDataKey = guidstr;
	CoTaskMemFree(guidstr);

	m_panes.push_back(new CPane(this, "Name", 110));
	m_panes.push_back(new CPane(this, "Keys", 60));

	m_panes.push_back(new CPane(this, NULL, 135));
	hr = m_panes[PANE_ATTRIBUTES-1]->m_horz.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_panes[PANE_ATTRIBUTES-1]->m_horz->put_direction(0);
	{
		//m_panes[PANE_ATTRIBUTES-1]->m_subpanes.push_back(new CPane(this, "begin", 45));
		//m_panes[PANE_ATTRIBUTES-1]->m_subpanes.push_back(new CPane(this, "end", 45));
		m_panes[PANE_ATTRIBUTES-1]->m_subpanes.push_back(new CPane(this, "dur", 45));
		m_panes[PANE_ATTRIBUTES-1]->m_subpanes.push_back(new CPane(this, "min", 45));
		m_panes[PANE_ATTRIBUTES-1]->m_subpanes.push_back(new CPane(this, "max", 45));
//		m_panes[PANE_ATTRIBUTES]->m_subpanes.push_back(new CPane("clipBegin", 45));
//		m_panes[PANE_ATTRIBUTES]->m_subpanes.push_back(new CPane("clipEnd", 45));
	}

	m_panes.push_back(new CPane(this, "Times", 80));

	{
		m_panes.push_back(new CPane(this, NULL, -1));

		hr = m_panes[PANE_TIMELINE-1]->m_horz.CoCreateInstance(CLSID_UIScrollBar);
		if (FAILED(hr)) return hr;

		hr = m_panes[PANE_TIMELINE-1]->m_slider.CoCreateInstance(CLSID_UISlider);
		if (FAILED(hr)) return hr;

		m_panes[PANE_TIMELINE-1]->m_scrollbarLeft = 50;
		m_panes[PANE_TIMELINE-1]->m_horz->put_direction(0);
	}

	return S_OK;
}

void CSmilTimeGraphView::FinalRelease()
{
	m_viewGroup = NULL;
//	m_document.Release();
}
#endif

CTGElement* CSmilTimeGraphView::CreateTGElement(Element* element)
{
#if 0
	CComBSTR timeContainer;
	CComQIPtr<ILElementTimeContainer> timeContainerElement = element;
	if (timeContainerElement)
		timeContainerElement->get_timeContainer(&timeContainer);
	else
		timeContainer = L"none";
#endif
	System::StringW* timeContainer = element->getAttribute(WSTR("timeContainer"));

	System::StringW* namespaceURI = element->get_namespaceURI();
	System::StringW* tagName = element->get_nodeName();//GetElementName(element);
//	_bstr_t timeContainer = GetElementTimeContainer(element);

	CTGElement* p = NULL;

#if 0
	CComQIPtr<ILElementTime> elementTime = element;
	if (elementTime && (
		
		/*
		!wcscmp(tagName, L"div") ||
		!wcscmp(tagName, L"p") ||
		*/

		!wcscmp(tagName, L"img") ||
		!wcscmp(tagName, L"video") ||
		!wcscmp(tagName, L"audio") ||
		!wcscmp(tagName, L"animation") ||
		!wcscmp(tagName, L"ref")))
	{
		CComObject<CMediaElement>* pElement;
		CComObject<CMediaElement>::CreateInstance(&pElement);
		pElement->AddRef();
		pElement->m_pGraphView = this;
		pElement->SetElement(element);

		p = pElement;
		//AddChildTail(pElement);
		//pElement->BuildTimeGraph(pElement->m_domElement);
	}
	else
#endif
		if (timeContainer && !wcscmp(timeContainer->c_str(), L"par"))
	{
		CParElement* pElement = new CParElement;
		pElement->m_pGraphView = this;
		pElement->SetElement(element);

		p = pElement;
	}
	else if (timeContainer && !wcscmp(timeContainer->c_str(), L"seq"))
	{
		CSeqElement* pElement = new CSeqElement;
		pElement->m_pGraphView = this;
		pElement->SetElement(element);

		p = pElement;
	}
	else if (
		!wcscmp(tagName->c_str(), L"animate") ||
		!wcscmp(tagName->c_str(), L"set") ||
		!wcscmp(tagName->c_str(), L"animateColor") ||
		!wcscmp(tagName->c_str(), L"animateMotion") ||
		!wcscmp(tagName->c_str(), L"animateTransform") ||
		!wcscmp(tagName->c_str(), L"transitionFilter"))
	{
		CAnimationElement* pElement = new CAnimationElement;
		pElement->m_pGraphView = this;
		pElement->SetElement(element);

		p = pElement;
		//AddChildTail(pElement);
		//pElement->BuildTimeGraph(pElement->m_domElement);
	}
	else
	{
		CNElement* pElement = new CNElement;
		pElement->m_pGraphView = this;
		pElement->SetElement(element);

		p = pElement;
	}

	return p;
}

CEXMLViewGroup* CSmilTimeGraphView::get_viewGroup()
{
	return m_viewGroup;
}

#if 0
ErrorCode CSmilTimeGraphView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
	CComPtr<IEXMLDocument> edocument;
	m_viewGroup->get_eXMLDocument(&edocument);

	CComQIPtr<IUIActiveManager> uiManager = m_viewGroup->m_pDocument->m_app;
	if (bActivate)
	{
//		uiManager->ActivateObject(m_viewGroup->GetUnknown(), GetUnknown());
	}
	else
	{
//		uiManager->DeactivateObject(GetUnknown());
	}

	return S_OK;
}
#endif

#define LEFT_EDGE 8

double CSmilTimeGraphView::GetCurrentTime()
{
	return 0;
#if 0
	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);

	CComPtr<ILDOMDocument> domdocument;
	document->get_DOMDocument(&domdocument);

	double currentTime;

	CComQIPtr<ILSVGDocument> svgdocument = domdocument;
	CComQIPtr<ILElementTime> elementTime = domdocument;
	if (svgdocument)
	{
		CComPtr<ILSVGSVGElement> svgsvgElement;
		svgdocument->get_rootElement(&svgsvgElement);

		if (svgsvgElement)
		{
			svgsvgElement->getCurrentTime(&currentTime);
		}
	}
	else if (elementTime)
	{
		elementTime->get_activeTime(&currentTime);
		//currentTime /= 1000;
	}

	return currentTime;
#endif
}

void CSmilTimeGraphView::SetCurrentTime(double currentTime)
{
	Web::IElementTime* elementTime = dynamic_cast<Web::IElementTime*>(m_viewGroup->m_layoutView->m_viewDocument);

	/*
	if (svgdocument)
	{
		CComPtr<ILSVGSVGElement> svgsvgElement;
		svgdocument->get_rootElement(&svgsvgElement);

		svgsvgElement->setCurrentTime(currentTime);
	}
	else
	*/
	if (elementTime)
	{
		elementTime->seekElement(currentTime*1000);
	}

	if (m_body)
	{
		m_body->CalculateSize();	// hm... currentInterval on elements can have changed
	}

	Invalidate();
}

void CSmilTimeGraphView::DrawPanes(UI::Graphics* pGraphics, LDraw::BBoxi client, int parentPane, Array<CPane*>& panes)
{
#if 0
	CDCHandle dc(hDC);
#endif

	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	int x = 0;
	for (int nPane = 0; nPane < panes.size(); nPane++)
	{
		CPane* pane = panes[nPane];

		LDraw::BBoxi paneRect(x, 0, x+pane->m_width, client.bottom);

	//	LDraw::GraphicsState state = pGraphics->Save();

		if (true)//dc.IntersectClipRect(&paneRect) > NULLREGION)
		{
#if 0
			dc.OffsetViewportOrg(paneRect.left, paneRect.top, NULL);
#endif

			long scrollposX = 0;
#if 0
			if (pane->m_horz)
			{
				pane->m_horz->get_pos(&scrollposX);
			}
#endif

			if (pane->m_subpanes.size())
			{
#if 0
				dc.OffsetViewportOrg(-scrollposX, 0, NULL);
				DrawPanes(dc.m_hDC, paneRect, (nPane+1) | ((parentPane)<<8), pane->m_subpanes);
#endif
			}
			else
			{
				LDraw::BBoxi headerRect(0, 0, pane->m_width, 22);
				LDraw::BBoxi footerRect(0, client.bottom-16-1, pane->m_width, client.bottom);

			// Draw pane header
				if (((nPane+1) | ((parentPane)<<8)) == PANE_TIMELINE)
				{
#if 0
					LDraw::BBoxi rc = headerRect;
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
					rc.InflateRect(-1,-1);
					dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));

					dc.OffsetViewportOrg(LEFT_EDGE/*-scrollposX*/, 0, NULL);
					DrawSecondTicks(dc.m_hDC);
					dc.OffsetViewportOrg(-(LEFT_EDGE/*-scrollposX*/), 0, NULL);
#endif
				}
				else
				{
#if 0
					LDraw::BBoxi rc = headerRect;
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
					rc.InflateRect(-1,-1);
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
					rc.InflateRect(-1,-1);
					dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));

					dc.DrawText(pane->m_name, pane->m_name.GetLength(), &rc, DT_SINGLELINE | DT_VCENTER);
#endif
				}

				// Draw pane footer
				{
					//ASSERT(0);
#if 0
					LDraw::BBoxi rc = footerRect;
					pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color::FromCOLORREF(GetSysColor(COLOR_3DDKSHADOW))), rc.left, rc.top, rc.Width(), 1);
					rc.top++;
					pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color::FromCOLORREF(GetSysColor(COLOR_BTNFACE))), rc.left, rc.top, rc.Width(), rc.Height());
#endif
				}

				LDraw::BBoxi paneContentsRect(0, 22, paneRect.GetWidth()-1, paneRect.bottom-16-1);

#if 0
				LDraw::GraphicsState state2 = pGraphics->Save();
#endif

				if (true)//dc.IntersectClipRect(&paneContentsRect) > NULLREGION)
				{
					pGraphics->TranslateTransform(0, 22-scrollposY);
					pGraphics->TranslateTransform(-scrollposX, 0);

#if 0
					dc.OffsetViewportOrg(0, 22-scrollposY, NULL);
					dc.OffsetViewportOrg(-scrollposX, 0, NULL);
#endif

					if (((nPane+1) | (parentPane<<8)) == PANE_TIMELINE)
					{
#if 0
						dc.OffsetViewportOrg(LEFT_EDGE, 0, NULL);
#endif
					}

				// Draw pane contents
					m_body->Draw(pGraphics, (nPane+1) | ((parentPane)<<8), LDraw::BBoxi(0, 0, paneContentsRect.right, 0), false);
				}
				
			//	pGraphics->Restore(state2);

				if (((nPane+1) | ((parentPane)<<8)) == PANE_TIMELINE)
				{
					// Draw timeline zoom control
					/*
					{
						dc.Draw3dRect(paneContentsRect.left, paneRect.bottom-16, 30, 16, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
					}
					*/

				// Draw currentTime marker
					long scrollposX = 0;
				//	pane->m_horz->get_pos(&scrollposX);
#if 0
					dc.OffsetViewportOrg(LEFT_EDGE-scrollposX, 0, NULL);
#endif

					double currentTime = GetCurrentTime();

					double x = currentTime*m_secondWidth;

#if 0
					dc.MoveTo(x, 0);
					dc.LineTo(x, client.bottom-16-1);
#endif
				}
			}
		}

	//	pGraphics->Restore(state);

		x += pane->m_width;

		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0,0,0)), x-1, 0, x-1, client.bottom);
	}
}

//LRESULT CSmilTimeGraphView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
void CSmilTimeGraphView::OnRender(UI::Graphics* pGraphics)
{
	//CPaintDC dc(m_hWnd);
	//HDC hDC = dc.m_hDC;

	CEXMLDocument* document = m_viewGroup->get_eXMLDocument();

//	CComPtr<ILDOMDocument> domdocument;
//	document->get_DOMDocument(&domdocument);

//	LDraw::BBoxi client;
//	GetClientRect(&client);

	pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(230, 230, 230)), 0, 0, m_computedSize.Width, m_computedSize.Height/*GetSysColor(COLOR_3DLIGHT)*/);

	if (m_body)
	{
#if 0
		HFONT hOldFont = dc.SelectFont(m_hSmallFont);
#endif

#if 0
		dc.SetBkMode(TRANSPARENT);
#endif

		LDraw::BBoxi client;
		client.left = 0;
		client.top = 0;
		client.right = m_computedSize.Width;
		client.bottom = m_computedSize.Height;
		LDraw::BBoxi panesRect = client;
		panesRect.right -= 16;	// Vertical scrollbar

		DrawPanes(pGraphics, panesRect, 0, m_panes);

#if 0
		dc.SelectFont(hOldFont);
#endif

	//	dc.RestoreDC(state);
	}
}

void CSmilTimeGraphView::DrawSecondTicks(UI::Graphics* pGraphics)
{
#if 0
	LDraw::BBoxi m_tracksRect;
	GetClientRect(&m_tracksRect);

	int m_fnumHeight = 22;

//	long scrollposX; m_horz->get_pos(&scrollposX);
//	long scrollposY; m_vert->get_pos(&scrollposY);

	CComQIPtr<IEXMLDocument> svgdocument = m_viewGroup->m_pDocument;
	CEXMLDocument* pDocument = static_cast<CEXMLDocument*>(svgdocument.p);

	CComPtr<ILDOMDocument> doc;
	svgdocument->get_DOMDocument(&doc);

	//CComQIPtr<ILTimeHTMLDocument> htmldoc = doc;
	//if (htmldoc)
	{
		//CComQIPtr<ISVGSVGElement> svg;
		//svgdoc->get_documentElement((IDOMElement**)&svg);
		//if (svg)
		{
			HFONT hOldFont = (HFONT)SelectObject(hDC, m_hSmallFont);
			HPEN hOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);
			HBRUSH hOldBrush = (HBRUSH)GetCurrentObject(hDC, OBJ_BRUSH);
			int oldMode = SetBkMode(hDC, TRANSPARENT);

			HPEN redPen = CreatePen(PS_SOLID, 1, RGB(220, 0, 0));
			HPEN whitePen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
			HPEN grayPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE));
			HBRUSH grayBrush = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
			HBRUSH blueBrush = CreateSolidBrush(RGB(20, 200, 255));

		//	int totalFrames = 800;//pComp->GetAbsTotalFrames();
			double currentTime = 0;
#if 0
			htmldoc->getCurrentTime(&currentTime);
#endif

			int visibleSeconds = m_tracksRect.Width()/m_secondWidth;

		//	if (totalFrames == 0) totalFrames = 1;
		//	if (visibleFrames > totalFrames) visibleFrames = totalFrames;

		// Draw Global view
		#if 0
			{
				LDraw::PointD oldOrg = pDC->SetViewportOrg(LDraw::PointD(m_tracksRect.left, 0));

				pDC->FillSolidRect(0, 0, m_tracksRect.Width(), 9, GetSysColor(COLOR_APPWORKSPACE));

				int startX, endX, curX;
				GetGlobalMarkerCoordinates(curX, startX, endX);

				LDraw::BBoxi	areaRect(startX, 0, endX, 10);

				pDC->SelectObject(&grayBrush);
				pDC->RoundRect(startX-6, 0, startX+5, 9, 10, 5);
				pDC->RoundRect(endX-5, 0, endX+6, 9, 10, 5);
				pDC->FillSolidRect(&areaRect, RGB(255, 255, 255));

				pDC->MoveTo(startX+1, 0);
				pDC->LineTo(startX+1, 9);
				pDC->MoveTo(endX-1, 0);
				pDC->LineTo(endX-1, 9);

				pDC->SetPixelV(startX-3, 3, RGB(20, 20, 20));
				pDC->SetPixelV(startX-3, 4, RGB(20, 20, 20));
				pDC->SetPixelV(endX+3, 3, RGB(20, 20, 20));
				pDC->SetPixelV(endX+3, 4, RGB(20, 20, 20));

			// Dividing line
				pDC->MoveTo(0, 9);
				pDC->LineTo(m_tracksRect.Width(), 9);

				POINT pt[5] =
				{
					curX-3, 0,
					curX+3, 0,
					curX+3, 2,
					curX, 9,
					curX-3, 2,
				};

				pDC->SelectObject(&blueBrush);
				pDC->Polygon(pt, 5);

				pDC->SelectObject(&whitePen);
				pDC->MoveTo(curX+2, 1);
				pDC->LineTo(curX-2, 1);
				pDC->LineTo(curX, 7);

				pDC->SetPixelV(curX, 2, RGB(0, 0, 0));
			//	pDC->SetPixelV(curX, 3, RGB(0, 0, 0));

				pDC->SetViewportOrg(oldOrg);
			}
		#endif
		#if 0
			int curFrameX = GetLocalFrameCoordinate(currentFrame);

			// Current Frame
			{
				LDraw::PointD oldOrg = pDC->SetViewportOrg(LDraw::PointD(m_tracksRect.left, 10));

				pDC->FillSolidRect(0, 0, m_tracksRect.Width(), 22, RGB(200, 200, 200));

				pDC->SelectObject(&whitePen);
				pDC->MoveTo(0, 1);
				pDC->LineTo(m_tracksRect.Width(), 1);
				pDC->SelectObject(&grayPen);
				pDC->MoveTo(0, 2);
				pDC->LineTo(m_tracksRect.Width(), 2);
				pDC->SelectStockObject(BLACK_PEN);
				pDC->MoveTo(0, 3);
				pDC->LineTo(m_tracksRect.Width(), 3);

				DrawFrameMarker(pDC->m_hDC, curFrameX, 0);

				pDC->SetViewportOrg(oldOrg);
			}
		#endif

		// Draw Numbers
			{
				//POINT oldOrg;
				//SetViewportOrgEx(hDC, m_tracksRect.left, 0, &oldOrg);

			//	FillSolidRect(hDC, 0, 0, m_tracksRect.Width(), 22, GetSysColor(COLOR_BTNFACE));
			//	Draw3DRect(hDC, -1, 0, m_tracksRect.Width()+2, 22, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));

				double ievery = 40/m_secondWidth;	// Ideal every

				int every = 0;	// Actual every

				int c = 1;

				while (every == 0)
				{
					if (ievery <= 1)			every = 1;
					else if (ievery <= 2)	every = 2;
					else if (ievery <= 4)	every = 4;
					else if (ievery <= 5)	every = 5;
					else if (ievery <= 10)	every = 10;
					else if (ievery <= 15)	every = 15;
					else if (ievery <= 20)	every = 20;
					else if (ievery <= 25)	every = 25;
					else if (ievery <= 50)	every = 50;

					if (every != 0)
					{
						every *= c;
						break;
					}

					c = c*100;
					ievery /= 100;
				}

				int width = m_secondWidth*every;
				int total = (m_tracksRect.Width()+width-1)/width;

				SelectObject(hDC, GetStockObject(BLACK_PEN));

				float second = 0;// TODO scrollposX*secondWidth;

				int y = 2;
				double x = 0;//LEFT_EDGE;

				for (int i = 0; i < total; i++)
				{
					MoveToEx(hDC, x, 0, NULL);
					LineTo(hDC, x, 4);

					char buf[64];

					LONG msecs = (second * 1000);// / pComp->GetFrameRate();

					LONG minutes = msecs/(1000*60);
					msecs %= (1000*60);

					LONG seconds = msecs/1000;
					msecs %= 1000;

				//	LONG frames = (LONG)(((double)msecs*pComp->GetFrameRate())/(double)1000 + 0.5);
						
					int len = sprintf(buf, "%.2ld:%.2ld", minutes, seconds);

					TextOut(hDC, x, y, buf, len);

					second += every;

					x += width;
				}

			//	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			}

			SelectObject(hDC, hOldBrush);
			SelectObject(hDC, hOldPen);
			SelectObject(hDC, hOldFont);
			SetBkMode(hDC, oldMode);

			DeleteObject(redPen);
			DeleteObject(whitePen);
			DeleteObject(grayPen);
			DeleteObject(grayBrush);
			DeleteObject(blueBrush);
		}
	}
#endif
}

void CSmilTimeGraphView::handleEvent(System::Event* evt)
{
	System::StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

		//	UI::Point point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			point.X -= 4;
			point.Y -= 44;

			OnLButtonDown(0, point);
		}
		else if (*type == L"mouseup")
		{
			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
		//	mouseEvt->get_clientX(&clientX);
		//	mouseEvt->get_clientY(&clientY);

			point.X -= 4;
			point.Y -= 44;

			OnLButtonUp(point);
		}
	}
}

void CSmilTimeGraphView::OnLButtonDown(LDraw::PointD point, UINT nFlags, int parentPane, Array<CPane*>& panes)
{
	LDraw::BBoxi client;
	client.left = 0;
	client.top = 0;
	client.right = m_computedSize.Width;
	client.bottom = m_computedSize.Height;
	//GetClientRect(&client);

	if (point.Y < 22)
	{
		int x = 0;
		int nPane;
		for (nPane = 0; nPane < panes.size(); nPane++)
		{
			x += panes[nPane]->m_width;

			if (m_nPane < panes.size()-1 && abs(point.X-x) < 4)
			{
				m_dragging = -2;
				break;
			}
			if (point.X < x)
			{
				/*
				if (panes[m_nPane]->m_subpanes.size())
				{
					LDraw::PointD pt = point;
					pt.x -= panes[m_nPane]->m_client.left;

					OnLButtonDown(pt, panes[m_nPane]->m_subpanes);
				}
				*/

				m_dragging = -1;
				break;
			}
		}

		m_nPane = (nPane+1) | (parentPane<<8);

		if (m_dragging == -2)
		{
			m_oldwidth = panes[nPane]->m_width;
			SetCapture();
		}
		else if (m_dragging == -1)
		{
			LDraw::PointD pt = point;
			pt.X -= panes[nPane]->m_client.X;
			pt.X -= LEFT_EDGE;

			double currentTime = pt.X / m_secondWidth;
			if (currentTime < 0) currentTime = 0;

			SetCurrentTime(currentTime);

			SetCapture();
		}
	}
	else
	{
		long scrollposY = 0;// m_vert->get_pos(&scrollposY);

		//m_paneLeft = 0;
		int x = 0;
		int nPane;
		for (nPane = 0; nPane < panes.size(); nPane++)
		{
			x += panes[nPane]->m_width;

			if (point.X < x)
			{
				break;
			}

			//m_paneLeft += panes[nPane]->m_width;
		}

		LDraw::PointD pt = point;
		pt.X -= panes[nPane]->m_client.X;
		//paneLeft += panes[nPane]->m_client.left;

#if 0
		if (panes[nPane]->m_horz)
		{
			long scrollposX;
			panes[nPane]->m_horz->get_pos(&scrollposX);
			pt.x += scrollposX;
		}
#endif
		if (panes[nPane]->m_subpanes.size())
		{
			OnLButtonDown(pt, nFlags, nPane, panes[nPane]->m_subpanes);
		}
		else
		{
			m_nPane = (nPane+1) | ((parentPane)<<8);

			if (point.Y < client.bottom-16-1)
			{
				pt.Y += scrollposY;
				pt.Y -= 22;

				if (((nPane+1) | (parentPane<<8)) == PANE_TIMELINE)
				{
					pt.X -= LEFT_EDGE;
				}

				if (m_body)
				{
					ASSERT(m_dragging == 0);

					if (m_pActiveNode)
					{
						m_pActiveNode->Deselect();
					}

					m_pActiveNode = m_body->OnButtonDown((nPane+1) | (parentPane<<8), pt, nFlags, m_dragging);
					m_viewGroup->m_pActiveTimeGraphNode = m_pActiveNode;
					if (m_pActiveNode)
					{
						if (m_pActiveNode->m_type == 1)
						{
							m_viewGroup->m_pActiveTimeGraphElement = (CTGElement*)m_pActiveNode;
						}
						/*	// TODO It should be set to the nearest time parent of m_pActiveElement
						else
							m_viewGroup->m_pActiveTimeElement = NULL;
							*/
					}
					else
					{
						m_viewGroup->m_pActiveTimeGraphElement = NULL;
					}

					if (m_pActiveNode)
					{
						m_pActiveNode->m_selected = true;
					}

					m_body->CalculateSize();

#if 0
					ResetVScrollBar();
#endif
					Invalidate();

					if (m_dragging)
					{
						ASSERT(m_pActiveNode);
					//	m_dragging = 1;
						SetCapture();

		#if 0
						CComObject<COleDataObject>* pDataObject;
						CComObject<COleDataObject>::CreateInstance(&pDataObject);
						if (pDataObject)
						{
							pDataObject->AddRef();

							CMyDropSource*  pDropSource = new CMyDropSource;

							CComBSTR xmltext;
							
							//xmltext = L"<svg>";

							//for (int i = 0; i < m_selectedItems.GetSize(); i++)
							{
								CComPtr<ILDOMElement> element = m_pActiveElement->m_domElement;

								CComBSTR xmltext2;
								domdocument->saveXML(element, &xmltext2);

								xmltext += xmltext2;
							}

							//xmltext += L"</svg>";

							HGLOBAL hData = GlobalAlloc(GMEM_SHARE, (xmltext.Length()+1)*2);
							if (hData)
							{
								WCHAR* pData = (WCHAR*)GlobalLock(hData);
								if (pData)
								{
									CopyMemory(pData, (BSTR)xmltext, (xmltext.Length()+1)*2);

									GlobalUnlock(pData);

									STGMEDIUM stgm;
									stgm.tymed = TYMED_HGLOBAL;
									stgm.pUnkForRelease = NULL;
									stgm.hGlobal = hData;

									FORMATETC etc = { CF_UNICODETEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
									pDataObject->SetData(&etc, &stgm, FALSE/*TRUE*/ /*fRelese*/);

									DWORD dropEffect = 0;
									if (::DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY/* | DROPEFFECT_MOVE*/, &dropEffect) == DRAGDROP_S_DROP)
									{
									}
								}

								GlobalFree(hData);
							}

							pDataObject->Release();
						}
		#endif
					}
					else
					{
						if (m_pActiveNode == NULL)
						{
							m_viewGroup->ActivateElement(NULL, 0);
						}
					}
				}
			}
			else
			{
				if ((nPane+1) == PANE_TIMELINE)
				{
					/*
					int x = pt.x;

					double tx = x/40.0;

					double viewAll = panes[nPane]->m_client.Width() / m_compDuration;
					double viewMax = 100;

					double range = viewMax - viewAll;

					m_secondWidth = viewAll + tx*range;

					OnSize();
					Invalidate();
					*/
				}
			}
		}
	}
}

void CSmilTimeGraphView::OnMouseMove(LDraw::PointD point, UINT nFlags, int nPane, Array<CPane*>& panes)
{
	ASSERT(0);
#if 0
	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);

	CComPtr<ILDOMDocument> domdocument;
	document->get_DOMDocument(&domdocument);

	if ((nPane>>8) != 0)
	{
		nPane >>= 8;

		LDraw::PointD pt = point;
		pt.x -= panes[nPane-1]->m_client.left;
		OnMouseMove(pt, nFlags, nPane, panes[nPane-1]->m_subpanes);
	}
	else
	{
		if (m_dragging == -2)	// resizing pane
		{
			int width = m_oldwidth + (point.x-m_oldpoint.x);
			m_oldwidth = width;

			if (width < 2) width = 2;

			if (width != panes[nPane]->m_width)
			{
				m_panes[m_nPane]->m_width = width;
				InvalidateRect(NULL);
			}
		}
		else
		{
			LDraw::PointD pt = point;
			pt.x -= m_panes[nPane-1]->m_client.left;

			if (panes[nPane-1]->m_horz)
			{
				long scrollposX;
				m_panes[nPane-1]->m_horz->get_pos(&scrollposX);

				pt.x += scrollposX;
			}

			if (m_dragging == -1)	// setting currentTime
			{
				pt.x -= LEFT_EDGE;

				double currentTime = pt.x / m_secondWidth;
				if (currentTime < 0) currentTime = 0;

				CComQIPtr<ILSVGDocument> svgdocument = domdocument;
				CComQIPtr<ILElementTime> elementTime = domdocument;
				if (svgdocument)
				{
					CComPtr<ILSVGSVGElement> svgsvgElement;
					svgdocument->get_rootElement(&svgsvgElement);

					svgsvgElement->setCurrentTime(currentTime);
				}
				else if (elementTime)
				{
					elementTime->seekElement(currentTime*1000);
				}

				if (m_body)
				{
					m_body->CalculateSize();	// hm... currentInterval on elements can have changed
				}

				InvalidateRect(NULL);
			}
			else if (m_pActiveNode)
			{
				pt.x -= LEFT_EDGE;	// TODO, not always

				m_pActiveNode->OnDrag(pt/*m_point - m_oldpoint*/, m_dragging);

				InvalidateRect(NULL);
			}
		}
	}
#endif
}

long CSmilTimeGraphView::OnLButtonDown(UINT nFlags, LDraw::PointD point)
{
	if (!m_dragging)
	{
		m_oldpoint = point;
		m_startpoint = point;

//		m_paneLeft = 0;
		OnLButtonDown(point, nFlags, 0, m_panes);
	}

	return 0;
}

long CSmilTimeGraphView::OnLButtonDblClk()
{
	ASSERT(0);
#if 0
	LDraw::PointD point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_pActiveNode)
	{
		m_pActiveNode->OnButtonDblClk(point, m_dragging);
	}
#endif
	return 0;
}

long CSmilTimeGraphView::OnLButtonUp(LDraw::PointD point)
{
	ASSERT(0);
#if 0
	if (m_dragging)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

			/*
		if (m_pActiveElement)
		{
			CComPtr<IEElement> eelement;
			edocument->GetEElementFromDOMElement(m_pActiveElement->m_domElement, &eelement);

			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->ActivateElement(eelement, 0, &selectedElement);
		}
		else
			m_viewGroup->ActivateElement(NULL, 0, NULL);
			*/

		ReleaseCapture();
		m_dragging = 0;
		//m_pActiveElement = NULL;

		OnSize();
	}
#endif
	return 0;
}

long CSmilTimeGraphView::OnMouseMove()
{
	ASSERT(0);
#if 0
	LDraw::PointD point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	m_point = point;

	long scrollposY; m_vert->get_pos(&scrollposY);

	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);

	CComPtr<ILDOMDocument> domdocument;
	document->get_DOMDocument(&domdocument);

	if (m_dragging)
	{
		OnMouseMove(point, nFlags, m_nPane, m_panes);
	}

	m_oldpoint = point;
#endif
	return 0;
}

#if 0
LRESULT CSmilTimeGraphView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nHittest = LOWORD(lParam);  // hit-test code 

	if (nHittest == HTCLIENT)
	{
		LDraw::PointD point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (point.y < 22)
		{
			int x = 0;
			for (int i = 0; i < m_panes.size()-1; i++)
			{
				x += m_panes[i]->m_width;
				if (abs(point.x-x) < 4)
				{
					::SetCursor(LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZECOLUMN)));
					return TRUE;
				}
			}
		}
	}

	bHandled = FALSE;

	return 0;
}
#endif

long CSmilTimeGraphView::OnContextMenu()
{
	ASSERT(0);
#if 0
	LDraw::PointD point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CComPtr<IMenuItem> menu0;

	if (m_pActiveNode)
	{
		//CComBSTR 
	}
	else
	{
		m_menuButton.m_menu->GetSubMenu(0, &menu0);
	}

	if (menu0)
	{
		long selectedID;
		menu0->PopupMenu(this, point, 0, &selectedID);
	}
#endif

	return 0;
}

void CSmilTimeGraphView::BuildTree()
{
	CEXMLDocument* pDocument = m_viewGroup->m_pDocument;

	Element* documentElement = pDocument->get_documentElement();
	if (documentElement)
	{
	// TODO here (more unified solution)

#if 0
		ILDOMElement* body;
		body = GetElementByTagName(documentElement, L"body", FALSE);
		if (body)
		{
			CComQIPtr<ILElementTime> timeElement = body;
			if (timeElement)
			{
				CComObject<CSeqElement>* p;
				CComObject<CSeqElement>::CreateInstance(&p);
				p->AddRef();
				m_body = p;

				m_body->m_pGraphView = this;
				m_body->SetElement(body);
			}
		}
		else
#endif
		{
			Element* timeContainer = documentElement;

			if (timeContainer)
			{
				CParElement* p = new CParElement;
				m_body = p;

				m_body->m_pGraphView = this;
				m_body->SetElement(documentElement);
			}
		}

		if (m_body)
		{
			m_body->BuildTimeGraph(m_body->m_domElement);
			m_body->CalculateSize();
		}
	}
}

#if 0
LRESULT CSmilTimeGraphView::OnCreate()
{
	CComPtr<ILDOMElement> element;
	m_behaviorSite->GetElement(&element);

	CComQIPtr<ILDOMEventTarget>(element)->addEventListener(L"mousedown", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
	CComQIPtr<ILDOMEventTarget>(element)->addEventListener(L"mouseup", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);

	/*
	{
		CComPtr<ILDOMElement> element;
		m_behaviorSite->GetElement(&element);

		CComPtr<IUnknown> unk;
		element->getUserData(L"n", &unk);
		CComQIPtr<IEXMLViewGroup> viewGroup(unk);

		m_viewGroup = static_cast<CEXMLViewGroup*>(viewGroup.p);
	}
	*/
	ASSERT(m_viewGroup);

#if 0
	LDraw::BBoxi rc(0,0,0,0);
	IUnknown* p;

	for (int i = 0; i < m_panes.size(); i++)
	{
		if (m_panes[i]->m_horz)
		{
			m_panes[i]->m_axhorz.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
			m_panes[i]->m_axhorz.AttachControl(m_panes[i]->m_horz, &p);
			((IDispEventImpl<1, CPane, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>*)m_panes[i])->DispEventAdvise(m_panes[i]->m_horz);
		}

		if (m_panes[i]->m_slider)
		{
			m_panes[i]->m_axslider.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
			m_panes[i]->m_axslider.AttachControl(m_panes[i]->m_slider, &p);
			((IDispEventImpl<2, CPane, &DIID__IUISliderEvents, &LIBID_UILib, 1, 0>*)m_panes[i])->DispEventAdvise(m_panes[i]->m_slider);
		}
	}

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CSmilTimeGraphView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);
#endif

//	m_hSmallFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
	m_hSmallFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	ErrorCode hr = IDispEventImpl<3, CSmilTimeGraphView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->m_pDocument->GetUnknown());
	ASSERT(SUCCEEDED(hr));

#if 0
	CComQIPtr<ILXAddin> addin = m_viewGroup->m_pDocument->m_app;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	ASSERT(0);
	CComPtr<IUIManager> uiManager;
	addinSite->GetUIManager((IUnknown**)&uiManager);
#endif

#if 0
	uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SMILTIMEGRAPHPOPUP, &m_menuButton.m_menu);
	m_menuButton.m_target = this;
#endif

#if 0
	m_menuButton.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
#endif

	BuildTree();

#if 0
	::RegisterDragDrop(m_hWnd, (IDropTarget*)this);
#endif

	return 0;
}

LRESULT CSmilTimeGraphView::OnDestroy()
{
#if 0
	RevokeDragDrop(m_hWnd);
#endif

	IDispEventImpl<1, CSmilTimeGraphView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
//	IDispEventImpl<2, CSmilTimeGraphView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	ErrorCode hr = IDispEventImpl<3, CSmilTimeGraphView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->m_pDocument->GetUnknown());
	ASSERT(SUCCEEDED(hr));

	if (m_hSmallFont)
	{
		DeleteObject(m_hSmallFont);
		m_hSmallFont = NULL;
	}

	return 0;
}

long CSmilTimeGraphView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL);

	LDraw::BBoxi client;
	GetClientRect(&client);

	m_menuButton.MoveWindow(client.right-16, 0, 16, 16);

	return 0;
}
#endif

void CSmilTimeGraphView::OnSize()
{
	ASSERT(0);
#if 0
	LDraw::BBoxi client;
	GetClientRect(&client);

	int width = 0;
	for (int i = 0; i < m_panes.size()-1; i++)
	{
		width += m_panes[i]->m_width;
	}

	m_panes[i]->m_width = client.right - width - 16;

	int left = 0;
	for (i = 0; i < m_panes.size(); i++)
	{
		m_panes[i]->m_client.SetRect(left, 0, left+m_panes[i]->m_width-1, client.bottom-16-1);

		if (m_panes[i]->m_axhorz.m_hWnd)
		{
			if ((i+1) == PANE_TIMELINE)
			{
				m_panes[i]->m_subwidth = m_compDuration * m_secondWidth;
			}
			else
			{
				m_panes[i]->m_subwidth = 0;
				if (m_panes[i]->m_subpanes.size())
				{
					for (int j = 0; j < m_panes[i]->m_subpanes.size(); j++)
					{
						m_panes[i]->m_subwidth += m_panes[i]->m_subpanes[j]->m_width;
					}
				}
			}

			m_panes[i]->m_axhorz.MoveWindow(left+m_panes[i]->m_scrollbarLeft, client.bottom-16, m_panes[i]->m_width-m_panes[i]->m_scrollbarLeft, 16, TRUE);

			m_panes[i]->m_horz->SetInfo(0, m_panes[i]->m_subwidth, m_panes[i]->m_client.Width());
		}

		if (m_panes[i]->m_axslider.m_hWnd)
		{
			m_panes[i]->m_axslider.MoveWindow(left, client.bottom-16, m_panes[i]->m_scrollbarLeft, 16, TRUE);
		}

		left += m_panes[i]->m_width;
	}

#if 0
	m_axvert.MoveWindow(client.right-16, 22, 16, client.bottom-16-22, TRUE);
#endif

	ResetVScrollBar();
#endif
}

#if 0
void CSmilTimeGraphView::ResetVScrollBar()
{
	LDraw::BBoxi client;
	GetClientRect(&client);

	int maxy = 0;
	if (m_body)
	{
		maxy = m_body->m_height;
	}

	m_vert->SetInfo(0, maxy, client.bottom-22-16-1);
}

void __stdcall CSmilTimeGraphView::CPane::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	LDraw::BBoxi	rect = m_client;

	m_horz->put_pos(pos);

#if 0
	m_pGraphView->ScrollWindow(oldPos-pos, 0, &rect, &rect);
#endif
}

void __stdcall CSmilTimeGraphView::CPane::OnSliderPos(long code, long pos)
{
	double tx = pos/100.0;

	int minWidth = m_client.Width();
	int maxWidth = m_pGraphView->m_compDuration*100;

	//int range = maxWidth-minWidth;

//	int width = minWidth + tx*range;
//	int width = minWidth*(1/(1-tx));

	m_pGraphView->m_secondWidth = ((double)maxWidth/minWidth) - ((double)maxWidth/minWidth -1) * pow(1-tx, 0.1);//m_pGraphView->m_compDuration;

	/*
	double viewAll = m_client.Width() / m_pGraphView->m_compDuration;
	double viewMax = 100;

	double range = viewMax - viewAll;

	m_pGraphView->m_secondWidth = viewAll + tx*range;
	*/

	m_pGraphView->OnSize();

	m_pGraphView->InvalidateRect(NULL);
}

void __stdcall CSmilTimeGraphView::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_vert->put_pos(pos);

	LDraw::BBoxi	rect;
	GetClientRect(&rect);
	rect.top = 22;
	rect.bottom -= 16+1;

#if 0
	ScrollWindow(0, oldPos-pos, &rect, &rect);
#endif
}

#if 0
ErrorCode __stdcall CSmilTimeGraphView::OnActivatedObject(IUnknown* object)
{
	CComQIPtr<IWebElement> element;
	CComQIPtr<IDOMNode> domelement;

	if (element = object)
	{
		InvalidateRect(NULL, TRUE);
	}
	else if (domelement = object)
	{
		CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

		CElement* pPElement = pDocument->m_pTree->FindDOMElement(domelement);
		if (pPElement)
		{
			pDocument->SetTargetElement(pPElement, 0);

		/*
			CComQIPtr<IUIContextManager> uiManager;
			gApp->get_uiManager(&uiManager);

			IUnknown* unk;
			pPElement->QueryInterface(IID_IUnknown, (void**)&unk);

			uiManager->ActivateObject(unk);
			//unk->Release();
		*/
		}
	}

	return S_OK;
}

ErrorCode __stdcall CSmilTimeGraphView::OnDeactivatedObject(IUnknown* object)
{
	CComQIPtr<IWebElement> element;
	CComQIPtr<IDOMNode> domelement;

	if (element = object)
	{
		InvalidateRect(NULL, TRUE);
	}
	else if (domelement = object)
	{
		CComQIPtr<IUIContextManager> uiManager;
		gApp->get_uiManager(&uiManager);

		CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);
		CElement* pPElement = pDocument->m_pTree->FindDOMElement(domelement);
		if (pPElement)
		{
			IUnknown* unk;
			pPElement->QueryInterface(IID_IUnknown, (void**)&unk);

			uiManager->ActivateObject(unk);
			//unk->Release();
		}
	}
	return S_OK;
}
#endif

void __stdcall CSmilTimeGraphView::OnDOMEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

	/*
	if (!wcscmp(type, L"DOMNodeRemoved") ||
		!wcscmp(type, L"DOMNodeRemovedFromDocument"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		if (m_pActiveSelection)
		{
			ASSERT(m_pActiveSelection->m_eElement);
			CComPtr<ILDOMNode> node2;
			m_pActiveSelection->m_eElement->get_domNode(&node2);
			if (node2 == node)
			{
				m_pActiveSelection = NULL;
			}
		}
	}
	*/

	if (!wcscmp(type, L"DOMNodeInserted"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;
	
		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComPtr<ILDOMNode> parentNode;
		node->get_parentNode(&parentNode);

		CComPtr<IUnknown> p;
		parentNode->getUserData(m_userDataKey, &p);
		CTGElement* pParent = (CTGElement*)p.p;
		if (pParent)
		{
			CComQIPtr<ILDOMElement> element = node;
			if (element)
			{
				CTGElement* pElement = CreateTGElement(element);
				if (pElement)
				{
					pElement->m_parent = pParent;
					pElement->BuildTimeGraph(pElement->m_domElement);

					UPOSITION pos = pParent->m_childList.GetHeadPosition();

					CComPtr<ILDOMNode> child;
					parentNode->get_firstChild(&child);

					while (child)
					{
						if (child == node)
							break;

						if (pos)
						{
							UPOSITION pos2 = pos;
							CTGElement* pChild = (CTGElement*)pParent->m_childList.GetNext(pos2);
							if (pChild->m_domElement == child)
							{
								pos = pos2;	// Okay, advance pos
							}
						}

						CComPtr<ILDOMNode> sibling;
						child->get_nextSibling(&sibling);
						child = sibling;
/*
						CComPtr<ILDOMNode> nextSibling;
						child->get_nextSibling(&nextSibling);
						child = nextSibling;
						*/
					}

					if (pos)
						pParent->m_childList.InsertBefore(pos, pElement);
					else
						pParent->m_childList.AddTail(pElement);
				}
			}

#if 0	// Had this
			if (m_hWnd)
			{
				OnSize();
			}
#endif
		}
	}
	else if (!wcscmp(type, L"DOMNodeRemoved"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComPtr<IUnknown> p;
		node->getUserData(m_userDataKey, &p);
		CTGElement* pElement = (CTGElement*)p.p;
		if (pElement)
		{
			UPOSITION pos = pElement->m_parent->m_childList.Find(pElement);
			ASSERT(pos);
			pElement->m_parent->m_childList.RemoveAt(pos);

			pElement->Release();

#if 0	// Had this
			if (m_hWnd)
			{
				OnSize();
			}
#endif
		}
	}

	if (m_body)
	{
		m_body->CalculateSize();	// hm... currentInterval on elements can have changed
	}

	InvalidateRect(NULL);
}

ErrorCode CSmilTimeGraphView::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

ErrorCode CSmilTimeGraphView::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;

#if 0
// Call base
	CComQIPtr<IDropTarget> basetarget = m_puiwnd;
	return basetarget->DragOver(grfKeyState, pt, pdwEffect);
#endif

	return S_OK;
}

ErrorCode CSmilTimeGraphView::DragLeave()
{
	return S_OK;
}

ErrorCode CSmilTimeGraphView::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

#if 0
	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	POINT pt = point;
	pt.x -= m_offset.x;
	pt.y -= m_offset.y;
	pt.x += scrollposX;
	pt.y += scrollposY;

	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CComQIPtr<IDOMDocument> doc = pDocument->GetDOMDocument();
	
	CComQIPtr<ISVGDocument> svgdoc = doc;
	if (svgdoc)
	{
		CComQIPtr<ISVGSVGElement> svg;
		svgdoc->get_documentElement((IDOMElement**)&svg);

		if (svg)
		{
			COleDataObject dataObject;
			dataObject.Attach(pDataObject);

			HGLOBAL hData;

			if (hData = dataObject.GetGlobalData(CF_HDROP))
			{
				DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
				if (dp)
				{
					char* p = (char*)(dp+1);

					int i = 0;
					TCHAR filename[512];
					while (*p)
					{
						filename[i++] = *p++;
					}
					filename[i] = 0;

					CComQIPtr<ISVGImageElement> image;
					pDocument->GetDOMDocument()->createElement(L"image", (IDOMElement**)&image);
					image->setAttribute(L"xlink:href", _bstr_t(filename));

					// x
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_x(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(pt.x);
					}

					// y
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_y(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(pt.y);
					}

					// width
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_width(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(200);
					}

					// height
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_height(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(200);
					}

					svg->appendChild(image, NULL);

					GlobalUnlock(hData);
				}

				*pdwEffect = DROPEFFECT_COPY;
			}
		}
	}

	if (*pdwEffect == DROPEFFECT_NONE)
	{
	// Call base
		CComQIPtr<IDropTarget> basetarget = m_puiwnd;
		return basetarget->Drop(pDataObject, grfKeyState, ptl, pdwEffect);
	}
#endif

	return S_OK;
}

#if 0
// ICommandTarget
ErrorCode CSmilTimeGraphView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try viewgroup
	CComQIPtr<ICommandTarget> target = m_viewGroup;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CSmilTimeGraphView)
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditClear)

	CMD_HANDLER(ID_TIMEGRAPH_OPTIONS, OnTimeGraphOptions)

	CMD_HANDLER(ID_INSERT_TIMELINE_SEQUENCE, OnInsertTimelineSequence)
	CMD_HANDLER(ID_INSERT_TIMELINE_PARALELL, OnInsertTimelineParalell)

	CMD_HANDLER(ID_ANIMATION_BEGIN, OnElementTimeBegin)
	CMD_HANDLER(ID_ANIMATION_END, OnElementTimeEnd)
	CMD_HANDLER(ID_ANIMATION_ADDBEGINTIME, OnAddBeginTime)
	CMD_HANDLER(ID_ANIMATION_ADDENDTIME, OnAddEndTime)
	CMD_HANDLER(ID_ANIMATION_ADDKEYFRAME, OnAnimationAddKeyframe)

/*
	CMD_HANDLER(&ID_EDIT_CUT, OnEditCut)
	CMD_UPDATE(&ID_EDIT_CUT, OnEditCutCopyUpdate)
	CMD_HANDLER(&ID_EDIT_COPY, OnEditCopy)
	CMD_UPDATE(&ID_EDIT_COPY, OnEditCutCopyUpdate)
	CMD_HANDLER(&ID_EDIT_PASTE, OnEditPaste)
	CMD_UPDATE(&ID_EDIT_PASTE, OnEditPasteUpdate)

	CMD_HANDLER(&ID_OBJECT_GROUP, OnObjectGroup)
	CMD_UPDATE(&ID_OBJECT_GROUP, OnObjectGroupUpdate)
	CMD_HANDLER(&ID_OBJECT_UNGROUP, OnObjectUngroup)
	CMD_UPDATE(&ID_OBJECT_UNGROUP, OnObjectUngroupUpdate)

	CMD_HANDLER(&ID_EDIT_DELETE, OnEditDelete)
	CMD_UPDATE(&ID_EDIT_DELETE, OnEditDeleteUpdate)

	CMD_HANDLER(&ID_VIEW_ZOOMIN, OnViewZoomin)
	CMD_HANDLER(&ID_VIEW_ZOOMOUT, OnViewZoomout)
	CMD_HANDLER(&ID_VIEW_ACTUALSIZE, OnViewActualSize)
*/
END_CMD_MAP()
#endif

long CSmilTimeGraphView::OnEditClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_mode == 0)	// element(s)
	{
	}
	else if (m_mode == 1)	// keyframes(s)
	{
		for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
		{
			CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = m_viewGroup->m_targetElements[i];
			if (selectedAnimationElement)
			{
				CComPtr<IEElement> eElement;
				selectedAnimationElement->get_eElement(&eElement);

				CComPtr<ILDOMElement> element;
				eElement->get_domElement(&element);

				CComQIPtr<ILAnimateXXX> animateXXX = element;
				if (animateXXX)
				{
					long count;
					selectedAnimationElement->GetSelectedKeyTimesCount(&count);

					for (int i = count-1; i >= 0; i--)
					{
						long index;
						selectedAnimationElement->GetKeyTimeSelected(i, &index);

						animateXXX->RemoveKeyTime(index);
					}

					selectedAnimationElement->DeselectAllKeyTimes();
				}
			}
		}
	}
	else if (m_mode == 2)	// begin/end time(s)
	{
		for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
		{
			CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = m_viewGroup->m_targetElements[i];
			if (selectedAnimationElement)
			{
				CComPtr<IEElement> eElement;
				selectedAnimationElement->get_eElement(&eElement);

				CComPtr<ILDOMElement> element;
				eElement->get_domElement(&element);

				CComQIPtr<ILElementTime> elementTime = element;
				if (elementTime)
				{
					CComPtr<IUnknown> p;
					element->getUserData(m_userDataKey, &p);
					CTimeElement* pTimeElement = static_cast<CTimeElement*>(p.p);

					CComPtr<ILSMILTimeList> beginList;
					elementTime->get_begin(&beginList);

					long count;

					count = pTimeElement->m_selectedBeginTimes.GetSize();

					for (int i = count-1; i >= 0; i--)
					{
						long index = pTimeElement->m_selectedBeginTimes[i];

						beginList->removeItem(index, NULL);
					}

					pTimeElement->m_selectedBeginTimes.RemoveAll();
				}
			}
		}
	}
	else if (m_mode == 3)	// trans
	{
		CTransNode* pTransNode = (CTransNode*)m_viewGroup->m_pActiveTimeGraphElement;
		ASSERT(pTransNode->m_type == -1);

		if (pTransNode->m_childSelectedIndex >= 0)
		{
			CComQIPtr<ILSMILMediaElement> mediaElement = pTransNode->m_parent->m_domElement;
			ASSERT(mediaElement);

			CComPtr<ILSVGStringList> transList;
			if (!wcscmp(pTransNode->m_name, L"transIn"))
			{
				mediaElement->get_transIn(&transList);
			}
			else if (!wcscmp(pTransNode->m_name, L"transOut"))
			{
				mediaElement->get_transOut(&transList);
			}

			transList->removeItem(pTransNode->m_childSelectedIndex, NULL);
		}
	}
#endif
	return 0;
}

/*
#include "ElementTimeDlg.h"

LRESULT CSmilTimeGraphView::OnTimeAttributes(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled)
{
	long nselected;
	m_viewGroup->GetSelectedCount(&nselected);
	for (int i = 0; i < nselected; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILElementTime> elementTime = domElement;
		if (elementTime == NULL)
		{
			return 0;
		}
	}

	CElementTimeDlg dlg;
	dlg.m_viewGroup = m_viewGroup;

	if (dlg.DoModal() == IDOK)
	{
	}

	return 0;
}

void CSmilTimeGraphView::OnTimeAttributesUpdate(long id, IUICmdUpdate* pCmdUI)
{
	long nselected;
	m_viewGroup->GetSelectedCount(&nselected);
	for (int i = 0; i < nselected; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILElementTime> elementTime = domElement;
		if (elementTime == NULL)
		{
			pCmdUI->Enable(FALSE);
			return;
		}
	}

	pCmdUI->Enable(TRUE);
}
*/

#include "TimeListDlg.h"

long CSmilTimeGraphView::OnElementTimeBegin(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	std::vector<ILElementTime*> list;

	long nselected;
	m_viewGroup->GetSelectedCount(&nselected);
	for (int i = 0; i < nselected; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILElementTime> elementTime = domElement;
		if (elementTime == NULL)
		{
			list.clear();
			break;
		}
		list.push_back(elementTime);

	}

	if (list.size())
	{
		CTimeListDlg dlg;

		if (dlg.DoModal() == IDOK)
		{
		}
	}
#endif
	return 0;
}

long CSmilTimeGraphView::OnElementTimeEnd(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	CTimeListDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
	}

	return 0;
}

long CSmilTimeGraphView::OnAddBeginTime(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);

	CComPtr<ILDOMDocument> domdocument;
	document->get_DOMDocument(&domdocument);

//	double currentTime;

	CComQIPtr<ILSVGDocument> svgdocument = domdocument;
	if (svgdocument)
	{
		CComPtr<ILSVGSVGElement> svgsvgElement;
		svgdocument->get_rootElement(&svgsvgElement);

		CComPtr<IESelectedElement> selectedElement = m_viewGroup->m_pActiveElement;
		if (selectedElement)
		{
			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> element;
			eElement->get_domElement(&element);

			CComQIPtr<ILElementTime> elementTime = element;
			if (elementTime)
			{
				CSMILTimeDlg dlg;
				dlg.m_type = 1;
				dlg.m_offset = GetCurrentTime();

				if (dlg.DoModal() == IDOK)
				{
					CComPtr<ILSMILTime> stime;
					svgsvgElement->createSMILTime(&stime);

					if (dlg.m_type == 0)
					{
						stime->setTimeIndefinite();
					}
					else if (dlg.m_type == 1)
					{
						stime->setTimeOffset(dlg.m_offset);
					}

					CComPtr<ILSMILTimeList> timeList;
					elementTime->get_begin(&timeList);

					timeList->appendItem(stime, NULL);
				}
			}
		}
	}
#endif
	return 0;
}

long CSmilTimeGraphView::OnAddEndTime(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	return 0;
}

long CSmilTimeGraphView::OnAnimationAddKeyframe(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);

	CComPtr<ILDOMDocument> domdocument;
	document->get_DOMDocument(&domdocument);

	double currentTime = 0;

	CComQIPtr<ILSVGDocument> svgdocument = domdocument;
	if (svgdocument)
	{
		CComPtr<ILSVGSVGElement> svgsvgElement;
		svgdocument->get_rootElement(&svgsvgElement);

		if (svgsvgElement)
		{
			svgsvgElement->getCurrentTime(&currentTime);
		}
	}

	for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
	{
		CComPtr<IESelectedElement> selectedElement = m_viewGroup->m_targetElements[i];

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILAnimationElement> animationElement = element;
		if (animationElement)
		{
			double simpleDur;
			animationElement->getSimpleDuration(&simpleDur);

			CComQIPtr<IEAnimationElement> eAnimationElement = eElement;

			CComQIPtr<ILAnimateXXX> animateXXX = animationElement;

			CComPtr<ILSMILAttributeValue> attribute;
			animateXXX->GetCurrentValue(&attribute);

			CComBSTR str;
			attribute->getStringValue(&str);

	//		CComPtr<ILDOMElement> targetElement;
	//		animationElement->get_targetElement(&targetElement);

			double keyTime = currentTime/simpleDur;

			long keyindex;
			animateXXX->InsertKeyTimeValue(keyTime, str, &keyindex);
		}
	}
#endif
	return 0;
}

long CSmilTimeGraphView::OnInsertTimelineSequence(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_viewGroup->m_pActiveTimeGraphElement && m_viewGroup->m_pActiveTimeGraphElement->m_parent)
	{
		//CComPtr<IEElement> eActiveElement;
		//m_pActiveElement->get_eElement(&eActiveElement);

		//CComPtr<ILDOMElement> activeElement = ((CTGElement*)m_pActiveElement)->m_domElement;
		//eActiveElement->get_domElement(&activeElement);

	// TODO
		CComQIPtr<ILElementTime> parentTimeContainer = m_viewGroup->m_pActiveTimeGraphElement->m_parent->m_domElement;

		if (parentTimeContainer)
		{
			double simpleTime;
			parentTimeContainer->get_simpleTime(&simpleTime);

			CComPtr<ILDOMDocument> document;
			m_viewGroup->m_pDocument->get_DOMDocument(&document);

			CComPtr<ILDOMElement> element;
			document->createElement(L"seq", &element);
			if (element)
			{
				WCHAR begin[64];
				swprintf(begin, L"%g", simpleTime);
				element->setAttribute(L"begin", begin);
				element->setAttribute(L"dur", L"60");	// TODO

				m_viewGroup->m_pActiveTimeGraphElement->m_parent->m_domElement->insertBefore(element, CComVariant(m_viewGroup->m_pActiveTimeGraphElement->m_domElement), NULL);
			}
		}
	}
#endif
	return 0;
}

long CSmilTimeGraphView::OnInsertTimelineParalell(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_viewGroup->m_pActiveTimeGraphElement && m_viewGroup->m_pActiveTimeGraphElement->m_parent)
	{
		//CComPtr<IEElement> eActiveElement;
		//m_pActiveElement->get_eElement(&eActiveElement);

		//CComPtr<ILDOMElement> activeElement = ((CTGElement*)m_pActiveElement)->m_domElement;
		//eActiveElement->get_domElement(&activeElement);

	// TODO
		CComQIPtr<ILElementTime> parentTimeContainer = m_viewGroup->m_pActiveTimeGraphElement->m_parent->m_domElement;

		if (parentTimeContainer)
		{
			double simpleTime;
			parentTimeContainer->get_simpleTime(&simpleTime);

			CComPtr<ILDOMDocument> document;
			m_viewGroup->m_pDocument->get_DOMDocument(&document);

			CComPtr<ILDOMElement> element;
			document->createElement(L"par", &element);
			if (element)
			{
				WCHAR begin[64];
				swprintf(begin, L"%g", simpleTime);
				element->setAttribute(L"begin", begin);
				element->setAttribute(L"dur", L"60");	// TODO

				m_viewGroup->m_pActiveTimeGraphElement->m_parent->m_domElement->insertBefore(element, CComVariant(m_viewGroup->m_pActiveTimeGraphElement->m_domElement), NULL);
			}
		}
	}
#endif
	return 0;
}

long CSmilTimeGraphView::OnTimeGraphOptions(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	CSMILTimeGraphOptionsDlg dlg;
	dlg.m_iconSize = m_iconSize;
	dlg.m_trackFormat = m_trackFormat;

	if (dlg.DoModal() == IDOK)
	{
		m_iconSize = dlg.m_iconSize;
		m_trackFormat = dlg.m_trackFormat;

		m_body->CalculateSize();

		OnSize();

		Invalidate();
	}

	return 0;
}

}	// LXmlEdit
}
