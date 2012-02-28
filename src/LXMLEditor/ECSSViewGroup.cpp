// ECSSViewGroup.cpp : Implementation of CECSSViewGroup
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ECSSViewGroup.h"

#include "LXMLEditorApp.h"	// TODO remove
#include "ECSSDocument.h"
#include "CSSSourceView.h"

#include "CSSProperty.h"

#if 0
/////////////////////////////////////////////////////////////////////
// CECSSViewGroup

int CECSSViewGroup::FinalConstruct()
{
	HRESULT hr;

	hr = m_currentSelectionStyle.CoCreateInstance(CLSID_LCSSStyleDeclaration);
	if (FAILED(hr)) return hr;

	return 0;
}

void CECSSViewGroup::FinalRelease()
{
}

class ATL_NO_VTABLE CESelectedRule : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IESelectedRule
{
public:
	CESelectedRule()
	{
	}

	CComPtr<ILCSSRule> m_rule;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CESelectedRule)
	COM_INTERFACE_ENTRY(IESelectedRule)
END_COM_MAP()

	STDMETHOD(get_selectedType)(/*[out,retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = 2;
		return S_OK;
	}
	STDMETHOD(get_rule)(/*[out,retval]*/ ILCSSRule* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_rule;
		(*pVal)->AddRef();
		return S_OK;
	}
};

void CECSSViewGroup::SetCurrentSelectionCSSProperties()
{
	m_currentSelectionStyle->set_cssText(L"");

	int i;

	for (i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComQIPtr<IESelectedRule> selectedRule = m_targetElements[i];

		CComPtr<ILCSSRule> rule;
		selectedRule->get_rule(&rule);

		LCSSType cssType;
		rule->get_type(&cssType);
		if (cssType != STYLE_RULE)
		{
			// Not a style rule, leave current selection css properties empty
			return;
		}
	}

	for (i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComQIPtr<IESelectedRule> selectedRule = m_targetElements[i];

		CComPtr<ILCSSRule> rule;
		selectedRule->get_rule(&rule);

		CComQIPtr<ILCSSStyleRule> styleRule = rule;
		ASSERT(styleRule);

		CComPtr<ILCSSStyleDeclaration> style;
		styleRule->get_style(&style);

		long length;
		style->get_length(&length);

		for (int n = 0; n < length; n++)
		{
			CComBSTR propertyName;
			style->item(n, &propertyName);

			CComBSTR value2;
			style->getPropertyValue(propertyName, &value2);

			if (i == 0)
			{
				m_currentSelectionStyle->setProperty(propertyName, value2, NULL);
			}
			else
			{
				CComBSTR value;
				m_currentSelectionStyle->getPropertyValue(propertyName, &value);

				if (cmpbstr(value, value2))	// If different
				{
					m_currentSelectionStyle->setProperty(propertyName, L"", NULL);
				}
			}
		}
	}
}

STDMETHODIMP CECSSViewGroup::ApplyCurrentSelectionCSSStyle()
{
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComQIPtr<IESelectedRule> selectedRule = m_targetElements[i];

		CComPtr<ILCSSRule> rule;
		selectedRule->get_rule(&rule);

		CComQIPtr<ILCSSStyleRule> styleRule = rule;
		ASSERT(styleRule);

		CComPtr<ILCSSStyleDeclaration> style;
		styleRule->get_style(&style);

		long length;
		m_currentSelectionStyle->get_length(&length);

		for (int n = 0; n < length; n++)
		{
			CComBSTR propertyName;
			m_currentSelectionStyle->item(n, &propertyName);

			CComBSTR value2;
			m_currentSelectionStyle->getPropertyValue(propertyName, &value2);

			if ((BSTR)value2 == NULL)
			{
				style->removeProperty(propertyName, NULL);
			}
			else if (value2.Length() == 0)
			{
				// Unchanged
			}
			else
			{
				style->setProperty(propertyName, value2, NULL);
			}
		}
	}

	return S_OK;
}

#if 0
BOOL CECSSViewGroup::SetCurrentSelectionCSSProperty(BSTR propertyName)
{
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComQIPtr<IESelectedRule> selectedRule = m_targetElements[i];

		CComPtr<ILCSSRule> rule;
		selectedRule->get_rule(&rule);

		LCSSType cssType;
		rule->get_type(&cssType);
		if (cssType == STYLE_RULE)
		{
			CComQIPtr<ILCSSStyleRule> styleRule = rule;

			CComPtr<ILCSSStyleDeclaration> style;
			styleRule->get_style(&style);

			CComBSTR value2;
			style->getPropertyValue(propertyName, &value2);

			if (i == 0)	// first element
			{
				if ((BSTR)value2 != NULL)
				{
					m_currentSelectionStyle->setProperty(propertyName, value2, NULL);
				}
			}
			else
			{
				CComBSTR value;
				m_currentSelectionStyle->getPropertyValue(propertyName, &value);
				if (value2.Length() > 0 && (value.Length() != value2.Length() ||
					wcscmp(value, value2)))
				{
				//	m_currentSelectionStyle->removeProperty(pProperty->m_name, NULL);
					m_currentSelectionStyle->setProperty(propertyName, L"", NULL);
					break;
				}
			}
		}
		else	// rule isn't a style rule
		{
			/*
			// Disable style editing all together
			m_currentSelectionStyle->set_cssText(L"");
			*/

			return FALSE;
			/*
			j = g_nCSSProperties;	// skip the rest of the properties
			break;
			*/
		}
	}

	return TRUE;
}
#endif

STDMETHODIMP CECSSViewGroup::GetSelectedCount(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_targetElements.GetSize();
	return S_OK;
}

STDMETHODIMP CECSSViewGroup::GetSelectedElement(ILCSSRule* rule, IESelectedRule* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		IESelectedRule* pSelectedRule = m_targetElements[i];

		CComPtr<ILCSSRule> rule2;
		pSelectedRule->get_rule(&rule2);

		if (rule == rule2)
		{
			*pVal = pSelectedRule;
			(*pVal)->AddRef();
		}
	}

	return S_OK;
}

void CECSSViewGroup::RemoveElementAsTarget(IESelectedRule* pElement)
{
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		if (m_targetElements[i] == pElement)
		{
			m_targetElements[i]->Release();
			m_targetElements.RemoveAt(i);
			return;
		}
	}
	ASSERT(0);
}

STDMETHODIMP CECSSViewGroup::ActivateElement(/*[in]*/ ILCSSRule* rule, /*[in]*/ long nFlags, /*[out,retval]*/ IESelectedRule* *pVal)
{
	if (pVal)
	{
		*pVal = NULL;
	}

	CComPtr<IESelectedRule> selectedRule;
	GetSelectedElement(rule, &selectedRule);

	Fire_SelectionChanging();

	if (nFlags & MK_SHIFT)
	{
		if (rule)
		{
			if (selectedRule)	// Already selected, unselect
			{
				RemoveElementAsTarget(selectedRule);
				m_pActiveElement = NULL;
			}
			else 	// Previously not selected, select
			{
				ASSERT(0);
#if 0
				CComObject<CESelectedRule>* pSelected;
				CComObject<CESelectedRule>::CreateInstance(&pSelected);
				pSelected->AddRef();
				pSelected->m_rule = rule;

				m_targetElements.Add(pSelected);

				selectedRule = pSelected;
				m_pActiveElement = selectedRule;
#endif
			}
		}
	}
	else
	{
		if (selectedRule == NULL)
		{
		//	DeselectAll();
		// Deselect all previously selected
			for (int i = 0; i < m_targetElements.GetSize(); i++)
			{
				m_targetElements[i]->Release();
			}
			m_targetElements.RemoveAll();

			if (rule)
			{
				ASSERT(0);
#if 0
				CComObject<CESelectedRule>* pSelected;
				CComObject<CESelectedRule>::CreateInstance(&pSelected);
				pSelected->AddRef();
				pSelected->m_rule = rule;

				m_targetElements.Add(pSelected);

				selectedRule = pSelected;
#endif
			}
		}
		//else Previously selected

		m_pActiveElement = selectedRule;
	}

	//if (m_pActiveElement/*rule*/)
	// SetCurrentSelectionCSSStyle
	{

		SetCurrentSelectionCSSProperties();

#if 0
		for (int j = 0; j < g_nCSSProperties; j++)
		{
			CSSProperty* pProperty = &CSSProperties[j];

			if (pProperty->m_initialCSS != NULL)
			{
				if (!SetCurrentSelectionCSSProperty(pProperty->m_name))
				{
					// Disable style editing all together
					m_currentSelectionStyle->set_cssText(L"");
					//j = g_nCSSProperties;
					break;
				}
			}
		}
#endif

#if 0
			SetCurrentSelectionColor();	// ??
#endif
	}

	for (int i = 0; i < m_views.GetSize(); i++)
	{
		CComQIPtr<ICSSSourceView> sourceView = m_views[i];
		if (sourceView)
		{
#if 0
			if (((CCSSSourceView*)sourceView.p)->m_bSelectingElement == 0)
			{
				((CCSSSourceView*)sourceView.p)->SetRange(range);
			}
#endif
		}
	}

	Fire_SelectionChanged();
	Fire_ColorChanged();	// ???

	if (pVal)
	{
		*pVal = selectedRule;
		if (*pVal) (*pVal)->AddRef();
	}

	return S_OK;
}

STDMETHODIMP CECSSViewGroup::get_eDocument(/*[out,retval]*/ IEDocument* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pDocument;
	(*pVal)->AddRef();
	return S_OK;
}

// CViewGroup
HRESULT CECSSViewGroup::OnActivate(BOOL bActivate)
{
	CComQIPtr<IUIActiveManager> uiManager = m_pDocument->m_app;

	if (bActivate)
	{
		uiManager->ActivateObject(NULL, m_pDocument->GetUnknown());
		uiManager->ActivateObject(m_pDocument->GetUnknown(), GetUnknown());

//		static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_cssPropertiesBar->Show(TRUE);

		CViewGroup::Activate(bActivate);
	}
	else
	{
		CViewGroup::Activate(bActivate);

//		static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_cssPropertiesBar->Show(FALSE);

		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(m_pDocument->GetUnknown());
	}

	return S_OK;
}

HRESULT CECSSViewGroup::OnClose()
{
	return S_OK;
}

#if 0
LRESULT CECSSViewGroup::OnMDIActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwndChildDeact = (HWND) wParam;        // child being deactivated 
	HWND hwndChildAct = (HWND) lParam;          // child being activated 

	HWND hwnd;
	get_hwnd(&hwnd);

	BOOL bActivate = (hwnd == hwndChildAct);

	CComQIPtr<IUIManager> uiManager = gIFrame;

	if (bActivate)
	{
		/*
		CComPtr<IDocumentsClass> documentsClass;
		m_pDocument->GetDocumentsClass(&documentsClass);
		*/
		//uiManager->ActivateObject(documentsClass, m_pDocument->GetUnknown());
		uiManager->ActivateObject(m_pDocument->GetUnknown(), GetUnknown());
//		uiManager->ActivateObject(m_viewGroup->GetUnknown(), GetUnknown());
	}

	CUIMDIChildImpl<CECSSViewGroup>::OnMDIActivate(uMsg, wParam, lParam, bHandled);

	if (!bActivate)
	{
//		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(m_pDocument->GetUnknown());
	}

	return 0;
}

LRESULT CECSSViewGroup::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	if (m_pDocument->m_viewGroups.GetSize() == 1)
	{
		CUString msg;
		_bstr_t pathName;

		if (m_pDocument->m_pathName.length())
			pathName = m_pDocument->m_pathName;
		else
			pathName = m_pDocument->m_fileTitle;

		msg.Format("Save changes to %S?", (BSTR)pathName);

		int id = ::MessageBox(GetMainHwnd(), msg, "WebEditor", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (id == IDCANCEL) return 0;

		if (id == IDYES)
		{
			// TODO save
		}
	}
#endif

	LRESULT lResult;
	bHandled = baseClass::ProcessWindowMessage(m_hWnd, uMsg, wParam, lParam, lResult);
	return lResult;
}
#endif

void CECSSViewGroup::UpdateTitles(int n)
{
	WCHAR str[512];
	if (n == -1)
		swprintf(str, L"%s", (BSTR)m_pDocument->m_fileTitle);
	else
		swprintf(str, L"%s:%d", (BSTR)m_pDocument->m_fileTitle, n);

	if (m_pDocument->m_modified)
		wcscat(str, L" *");

	for (int i = 0; i < m_sheets.GetSize(); i++)
	{
		CViewSheet* pViewSheet = m_sheets[i];

		ILXUIElement* parentNode;
		pViewSheet->m_sheet->get_parentNode(&parentNode);

		pViewSheet->m_tabElement->put_TextContent(str);
	}

#if 0
	CUString title;
	title = (BSTR)m_pDocument->m_fileTitle;
	if (m_pDocument->m_modified)
		title += " *";
	SetWindowText(title);
#endif
}

// IUIActivatable
STDMETHODIMP CECSSViewGroup::OnActivate(IUIActiveManager *uiManager)
{
#if 0	// TODO remove this
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<IEElement> eelement;
		m_targetElements[i]->get_eElement(&eelement);

		uiManager->ActivateObject(GetUnknown(), eelement);
	}
#endif

	return S_OK;
}

STDMETHODIMP CECSSViewGroup::OnDeactivate(IUIActiveManager *uiManager)
{
	return S_OK;
}

//	IECSSSelection
STDMETHODIMP CECSSViewGroup::GetCurrentSelectionCSSStyle(ILCSSStyleDeclaration* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = m_currentSelectionStyle;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

BEGIN_CMD_MAP(CECSSViewGroup)
// Window
	CMD_HANDLER(ID_WINDOW_NEW, OnWindowNew)
END_CMD_MAP()

#if 0
// ICommandTarget
STDMETHODIMP CECSSViewGroup::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try document
	CComQIPtr<ICommandTarget> target = m_pDocument->GetUnknown();
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}
#endif

LRESULT CECSSViewGroup::OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComQIPtr<ILXAddin> addin = m_pDocument->m_app;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CComQIPtr<IEFrame> eframe = lxframe;

	m_pDocument->ShowViews(eframe);
#endif

	return 0;
}

#endif