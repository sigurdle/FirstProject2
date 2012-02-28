// SceneGraphDlg.cpp : Implementation of CSceneGraphDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#if 0

#include "SceneGraphDlg.h"


#include "ESceneDocument.h"


////////////////////////////////////////////////////////////////////////////
// CSceneGraphDlg

static int m_col0width;

int CSceneGraphDlg::FinalConstruct()
{
	HRESULT hr;

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);

	return S_OK;
}

void CSceneGraphDlg::FinalRelease()
{
	m_vert.Release();
}

LRESULT CSceneGraphDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	{
		CComPtr<ILDOMElement> element;
		m_behaviorSite->GetElement(&element);

		CComPtr<IUnknown> unk;
		element->getUserData(L"n", &unk);
		CComQIPtr<IESceneDocument> document(unk);

		m_pDocument = static_cast<CESceneDocument*>(document.p);
	}

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CSceneGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

void DrawNode(HDC hDC, ILX3DNode* node, int indent, int& y);

// Fields

void DrawSFBool(HDC hDC, ILSFBool* field, int indent, int& y)
{
	if (hDC)
	{
		CDCHandle dc(hDC);

		VARIANT_BOOL value;
		field->getValue(&value);

		CUString str;
		str.Format("%s", value? "TRUE": "FALSE");

		dc.TextOut(m_col0width, y, str, str.GetLength());
	}
}

void DrawSFInt32(HDC hDC, ILSFInt32* field, int indent, int& y)
{
	if (hDC)
	{
		CDCHandle dc(hDC);

		long value;
		field->getValue(&value);

		CUString str;
		str.Format("%d", value);

		dc.TextOut(m_col0width, y, str, str.GetLength());
	}
}

void DrawSFFloat(HDC hDC, ILSFFloat* field, int indent, int& y)
{
	if (hDC)
	{
		CDCHandle dc(hDC);

		float value;
		field->getValue(&value);

		CUString str;
		str.Format("%g", value);

		dc.TextOut(m_col0width, y, str, str.GetLength());
	}
}

void DrawSFVec3f(HDC hDC, ILSFVec3f* field, int indent, int& y)
{
	if (hDC)
	{
		CDCHandle dc(hDC);

		float value[3];
		field->getValue(value);

		CUString str;
		str.Format("%g %g %g", value[0], value[1], value[2]);

		dc.TextOut(m_col0width, y, str, str.GetLength());
	}
}

void DrawSFRotation(HDC hDC, ILSFRotation* field, int indent, int& y)
{
	if (hDC)
	{
		CDCHandle dc(hDC);

		float value[4];
		field->getValue(value);

		CUString str;
		str.Format("%g %g %g %g", value[0], value[1], value[2], value[3]);

		dc.TextOut(m_col0width, y, str, str.GetLength());
	}
}

void DrawMFNode(HDC hDC, ILMFNode* field, int indent, int& y)
{
	y += 17;

	long size;
	field->get_size(&size);

	for (int i = 0; i < size; i++)
	{
		CComPtr<ILX3DNode> node;
		field->get1Value(i, &node);

		DrawNode(hDC, node, indent, y);
	}

	y -= 17;
}

void DrawField(HDC hDC, ILX3DFieldDefinition* fieldDefinition, ILX3DField* field, int indent, int& y)
{
	CComBSTR fieldName;
	fieldDefinition->getName(&fieldName);

	if (hDC)
	{
		CDCHandle dc(hDC);
		dc.TextOut(16+indent*16, y, _bstr_t(fieldName), fieldName.Length());
	}

	FieldType fieldType;
	fieldDefinition->getFieldType(&fieldType);

	switch (fieldType)
	{
	case SFBool:
		{
			DrawSFBool(hDC, CComQIPtr<ILSFBool>(field), indent+1, y);
		}
		break;

	case SFInt32:
		{
			DrawSFInt32(hDC, CComQIPtr<ILSFInt32>(field), indent+1, y);
		}
		break;

	case SFFloat:
		{
			DrawSFFloat(hDC, CComQIPtr<ILSFFloat>(field), indent+1, y);
		}
		break;

	case SFVec3f:
		{
			DrawSFVec3f(hDC, CComQIPtr<ILSFVec3f>(field), indent+1, y);
		}
		break;

	case SFRotation:
		{
			DrawSFRotation(hDC, CComQIPtr<ILSFRotation>(field), indent+1, y);
		}
		break;

	case MFNode:
		{
			DrawMFNode(hDC, CComQIPtr<ILMFNode>(field), indent+1, y);
		}
		break;
	}

	y += 17;
}

// Node

void DrawNode(HDC hDC, ILX3DNode* node, int indent, int& y)
{
	CComBSTR nodeName;
	node->getNodeName(&nodeName);

	if (hDC)
	{
		CDCHandle dc(hDC);
		dc.TextOut(16+indent*16, y, _bstr_t(nodeName), nodeName.Length());
	}
	y += 17;

	CComPtr<ILX3DFieldDefinitions> fieldDefinitions;
	node->getFieldDefinitions(&fieldDefinitions);

	long nfields;
	fieldDefinitions->get_length(&nfields);

	for (int i = 0; i < nfields; i++)
	{
		CComPtr<ILX3DFieldDefinition> fieldDefinition;
		fieldDefinitions->item(i, &fieldDefinition);

		CComBSTR fieldName;
		fieldDefinition->getName(&fieldName);

		CComPtr<ILX3DField> field;
		node->getField(fieldName, &field);

		DrawField(hDC, fieldDefinition, field, indent+1, y);
	}

	/*
	CComPtr<ILX3DField> children;
	node->getField(L"children", &children);
	if (children)
	{
		CComQIPtr<ILMFNode> mfnode = children;
		DrawMFNode(hDC, mfnode, indent+1, y);
	}
	*/
}

LRESULT CSceneGraphDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CComPtr<ILMFNode> rootNodes;
	m_pDocument->m_scene->getRootNodes(&rootNodes);

	long scrollposY; m_vert->get_pos(&scrollposY);

	HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	dc.SetViewportOrg(0, -scrollposY, NULL);

	int y = 0;
	DrawMFNode(dc, rootNodes, 0, y);

	dc.SelectFont(hOldFont);

	return 0;
}

LRESULT CSceneGraphDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	//client.InflateRect(-GetSystemMetrics(SM_CXEDGE),-GetSystemMetrics(SM_CYEDGE));

	m_areaRect = client;
	m_areaRect.right -= 16;	// Make room for scrollbar

	m_col0width = m_areaRect.right-70;

	CComPtr<ILMFNode> rootNodes;
	m_pDocument->m_scene->getRootNodes(&rootNodes);

	int y = 0;
	DrawMFNode(NULL, rootNodes, 0, y);

	m_axvert.MoveWindow(m_areaRect.right, m_areaRect.top, 16, m_areaRect.Height());
	m_vert->SetInfo(0, y, (m_areaRect.Height()));

	return 0;
}

void __stdcall CSceneGraphDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	/*
	if (m_edit)
	{
		CRect wrect;
		::GetWindowRect(m_edit, &wrect);
		ScreenToClient((LPPOINT)&wrect.left);
		ScreenToClient((LPPOINT)&wrect.right);
		::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
	}
	*/

	CRect	rect = m_areaRect;
	m_vert->put_pos(pos);
	//ScrollWindow(0, (oldPos-pos)*16, &rect, &rect);
	Invalidate();
}

#endif