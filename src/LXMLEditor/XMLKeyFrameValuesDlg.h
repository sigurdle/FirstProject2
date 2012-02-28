#pragma once

#include "XMLAttribute.h"

#include "XMLAttributesListWnd.h"	// TODO remove

class ATL_NO_VTABLE CXMLKeyFrameValuesDlg :
	public CComObjectRootEx<CComSingleThreadModel>,
	//public CUIDialogImpl<CXMLKeyFrameValuesDlg, CWindowImpl<CXMLKeyFrameValuesDlg>, CControlsContainer>
	public CControlsContainer
{
public:
	DECLARE_WND_CLASS_EX(NULL, 0/*CS_DBLCLKS*/, COLOR_BTNFACE)

	CXMLKeyFrameValuesDlg()// : m_wndEdit(NULL, this, 1)
	{
		m_pControlsHandler = NULL;

		m_viewGroup = NULL;
		//m_hWndEdit = NULL;
	}

	void EndEdit();

	virtual void Redraw()
	{
		if (m_hWnd)
		{
			Invalidate();
		}
	}

	virtual void OnDataValueChanged(CXMLData* pData);
	void UpdateData(CXMLData* pData);

//	virtual void OnControlValueChanged(CControl* pControl);

	virtual HRESULT GetViewGroup(IEXMLViewGroup* *pVal)
	{
		ATLASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
		*pVal = m_viewGroup;
		return S_OK;
	}

	virtual HRESULT SetPathNodeValue(BSTR path, BSTR value);
	virtual HRESULT SetPathNodeValueIfNotExists(BSTR path, BSTR value);
	virtual HRESULT GetPathNodeValue(BSTR path, BSTR* pVal);
	virtual BOOL PathNodeExists(BSTR path);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXMLKeyFrameValuesDlg)
	COM_INTERFACE_ENTRY(IUIDlg)
END_COM_MAP()

BEGIN_MSG_MAP(CXMLKeyFrameValuesDlg)
//	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
//	ALT_MSG_MAP(1)
//		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
	CHAIN_MSG_MAP(CControlsContainer)

END_MSG_MAP()

/*
	LRESULT OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_wndEdit.DefWindowProc(uMsg, wParam, lParam);
	}
*/
//	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
