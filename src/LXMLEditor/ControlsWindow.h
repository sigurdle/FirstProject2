#pragma once

#include "UIControls.h"

namespace System
{

class CControlsContainer :
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CLXUIControl,//CUIDialogImpl<CControlsContainer, CWindowImpl<CControlsContainer>, IControlsWindow>
	public IControlsWindow
{
public:
//	DECLARE_WND_CLASS_EX(NULL, 0/*CS_DBLCLKS*/, COLOR_BTNFACE)

	CControlsContainer()// : m_wndEdit(NULL, this, 1)
	{
		m_pControlsHandler = NULL;
		m_pActiveControl = NULL;
		m_reentrancy = 0;
	}

	class CControlSite :
		public IControlSite	// CControlEventHandler
	{
	public:
		CControlSite()
		{
			m_pContainer = NULL;
			m_pControl = NULL;
		}

		CControl* m_pControl;
		CControlsContainer* m_pContainer;

		virtual IControlsWindow* GetControlWindow()
		{
			return m_pContainer;
		}

		virtual ErrorCode __stdcall Redraw()
		{
			ASSERT(0);
#if 0
			if (m_pContainer->m_hWnd)
			{
				m_pContainer->Invalidate();
			}
#endif
			return Success;
		}

		virtual void OnControlValueChanged(/*CControl* pControl*/)
		{
			for (int i = 0; i < m_pControl->m_dataConnections.GetSize(); i++)
			{
				CDataConnection* pDataConnection = m_pControl->m_dataConnections[i];

				System::StringW* value = m_pControl->GetProperty(pDataConnection->m_propertyName);
				pDataConnection->m_pData->SetValue(value);
			}

			if (m_pContainer->m_pControlsHandler)
			{
				m_pContainer->m_pControlsHandler->OnUIValueChanged(m_pControl);
			}

		//	m_pContainer->OnControlValueChanged(pControl);
		}
	};

	CControl* m_pActiveControl;

	int m_reentrancy;

	Array<CControlSite*> m_controls;

// CXMLControlWindow

	virtual int GetControlsCount()
	{
		return m_controls.GetSize();
	}

	virtual CControl* GetControlByIndex(int index)
	{
		return m_controls[index]->m_pControl;
	}

	virtual void AddData(CXMLData* pData)
	{
		pData->m_controlWindow = this;
		m_attributes.Add(pData);
	}

	virtual void AddControl(CControl* pControl)
	{
		CControlSite* pSite = new CControlSite;
		pSite->m_pControl = pControl;
		pSite->m_pContainer = this;

		pControl->m_pSite = pSite;
		//pControl->m_controlWindow = this;
		m_controls.Add(pSite);
	}

	virtual CControl* GetControl(System::StringW* name)
	{
		for (int i = 0; i < m_controls.GetSize(); i++)
		{
			if (*m_controls[i]->m_pControl->m_name == *name)
			{
				return m_controls[i]->m_pControl;
			}
		}

		return NULL;
	}

	virtual CXMLData* GetData(System::StringW* name)
	{
		for (int i = 0; i < m_attributes.GetSize(); i++)
		{
			if (*m_attributes[i]->m_name == *name)
			{
				return m_attributes[i];
			}
		}

		return NULL;
	}

	void OnDataValueChanged(CXMLData* pData)
	{
		m_pControlsHandler->OnDataValueChanged(pData);
	}

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CControlsContainer)
	COM_INTERFACE_ENTRY(IControlsWindow)
	COM_INTERFACE_ENTRY(IUIDlg)
END_COM_MAP()

BEGIN_MSG_MAP(CControlsContainer)
//	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
//	ALT_MSG_MAP(1)
//		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
END_MSG_MAP()
#endif

	void Redraw();

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
};

}
