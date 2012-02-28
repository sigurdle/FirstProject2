// XMLSchemaGlobalsCtl.cpp : Implementation of CXMLSchemaGlobalsCtl
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XMLSchemaGlobalsCtl.h"

//#include "XMLSchema.h"
#include "SchemaDiagramView.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CXMLSchemaGlobalsCtl

long CXMLSchemaGlobalsCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//		HRESULT hr;

//		m_horz.CoCreateInstance(CLSID_UIScrollBar);
//		m_horz->put_direction(0);

	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);

//		IDispEventImpl<1, CXMLSchemaGlobalsCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	IDispEventImpl<2, CXMLSchemaGlobalsCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	return 0;
}

long CXMLSchemaGlobalsCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//		IDispEventImpl<1, CXMLSchemaGlobalsCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, CXMLSchemaGlobalsCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

long CXMLSchemaGlobalsCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(m_areaRect);
	return 0;
}

void CXMLSchemaGlobalsCtl::OnSize()
{
	CRect client;
	GetClientRect(&client);

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	int maxy = 0;

	if (m_pSchema)
	{
		CComPtr<IASNamedObjectMap> globalElements;
		m_pSchema->m_asModel->get_elementDeclarations(&globalElements);

		long length;
		globalElements->get_length(&length);

		maxy = length*16;
	}

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right;
	m_areaRect.bottom = client.bottom;

	BOOL bVertSB = FALSE;

	if (maxy > m_areaRect.bottom)
	{
		m_areaRect.right -= sbWidth;
		bVertSB = TRUE;
	}

	if (bVertSB)
	{
		m_vert->SetInfo(0, maxy, m_areaRect.Height());

		m_axvert.MoveWindow(m_areaRect.right, 0, sbWidth, m_areaRect.Height());
		m_axvert.ShowWindow(SW_SHOW);
	}
	else
	{
		m_vert->SetInfo(0, 0, 0);
		m_axvert.ShowWindow(SW_HIDE);
	}
}

LRESULT CXMLSchemaGlobalsCtl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	HWND hwnd = m_hWnd;
	ATLASSERT(::IsWindow(hwnd));

	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);
	ATLASSERT(hDC);

	int state = SaveDC(hDC);

	HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

	IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

	long scrollposY; m_vert->get_pos(&scrollposY);

	POINT oldOrg;
	SetViewportOrgEx(hDC, 0, -scrollposY, &oldOrg);

	if (m_pSchema)
	{
		CComPtr<IASNamedObjectMap> globalElements;
		m_pSchema->m_asModel->get_elementDeclarations(&globalElements);

		long length;
		globalElements->get_length(&length);

		int y = 0;
		for (int i = 0; i < length; i++)
		{
		//	CComPtr<IASNamedObjectMap> globalElements;
		//	m_pSchema->m_asModel->get_elementDeclarations(&globalElements);

			//CSchemaNode* pElement = m_pSchema->m_globalElements[i];
			CComPtr<IASObject> asObject;
			globalElements->item(i, &asObject);

			ASObjectType nodeType;
			asObject->get_asNodeType(&nodeType);

			if (nodeType == AS_INCLUDE)
			{
				CUString tagName = "include";

				TextOut(hDC, 16, y, tagName, tagName.GetLength());
			}
			else if (nodeType == AS_ELEMENT_DECLARATION ||
						nodeType == AS_COMPLEXTYPE_DECLARATION ||
						nodeType == AS_SIMPLETYPE_DECLARATION)
			{
				CUString tagName;

				if (nodeType == AS_ELEMENT_DECLARATION)
					tagName = "element";
				else if (nodeType == AS_COMPLEXTYPE_DECLARATION)
					tagName = "complexType";
				else if (nodeType == AS_SIMPLETYPE_DECLARATION)
					tagName = "simpleType";

				if (nodeType == AS_ELEMENT_DECLARATION ||
					nodeType == AS_COMPLEXTYPE_DECLARATION)
				{
					Draw3DRect(hDC, 0, y, 16, 16, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
					TransparentBlt(hDC, 1, y+1, 14, 14, m_schemaDesignBm, 0, 0, RGB(192, 192, 192));
				}

				CComBSTR name;
				asObject->get_nodeName(&name);

				TextOut(hDC, 16, y, tagName, tagName.GetLength());

				if (name.Length())
				{
					TextOut(hDC, 140, y, _bstr_t(name), name.Length());
				}
			}

			y += 16;
		}
	}

	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	SelectObject(hDC, hOldFont);

	RestoreDC(hDC, state);

	EndPaint(&ps);
#endif
	return 0;
}

long CXMLSchemaGlobalsCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.y += scrollposY;

	if (m_pSchema)
	{
		CComPtr<IASNamedObjectMap> globalElements;
		m_pSchema->m_asModel->get_elementDeclarations(&globalElements);

		long length;
		globalElements->get_length(&length);

		int index = point.y / 16;
		if (index >= 0 && index < length)
		{
			CComPtr<IASObject> asObject;
			globalElements->item(index, &asObject);

			ASObjectType nodeType;
			asObject->get_asNodeType(&nodeType);

			if (nodeType == AS_ELEMENT_DECLARATION ||
				nodeType == AS_COMPLEXTYPE_DECLARATION)
			{
				m_pSchema->m_pWndGraph->m_asGraph->put_asRootObject(asObject);
			}
			else
			{
				m_pSchema->m_pWndGraph->m_asGraph->put_asRootObject(NULL);
			}
		}
	}

	return 0;
}

#include "EXMLDocument.h"

LRESULT CXMLSchemaGlobalsCtl::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.y += scrollposY;

	if (m_pSchema)
	{
		CComPtr<IASNamedObjectMap> globalElements;
		m_pSchema->m_asModel->get_elementDeclarations(&globalElements);

		long length;
		globalElements->get_length(&length);

		int index = point.y / 16;
		if (index >= 0 && index < length)
		{
			CComPtr<IASObject> asObject;
			globalElements->item(index, &asObject);

			ASObjectType nodeType;
			asObject->get_asNodeType(&nodeType);

			if (nodeType == AS_INCLUDE)
			{
				CComQIPtr<IASInclude> include = asObject;

				CComPtr<IASModel> asModel;
				include->get_asModel(&asModel);

				CComQIPtr<IASXMLSchemaModel> asXMLModel = asModel;
				if (asXMLModel)
				{
					CComPtr<ILDOMDocument> xmldocument;
					asXMLModel->get_xmlDocument(&xmldocument);
					if (xmldocument)
					{
						CComBSTR absurl;
						xmldocument->get_url(&absurl);

						CComObject<CEXMLDocument>* pEDocument;
						CComObject<CEXMLDocument>::CreateInstance(&pEDocument);
						pEDocument->AddRef();

						if (SUCCEEDED(pEDocument->LoadDocument(absurl)))
						{
#if 0
						// TODO, have a method for all this
							pEDocument->m_xmldocument = xmldocument;
							pEDocument->m_xmldocument->put_errorHandler(pEDocument);
							pEDocument->m_schemaModel = asXMLModel;
							pEDocument->InitTree();
							pEDocument->SetupEventListener();
							pEDocument->Prepare();

							pEDocument->ShowViews();
#endif
						}
					}
				}
			}
		}
	}

	return 0;
}

void __stdcall CXMLSchemaGlobalsCtl::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

#endif