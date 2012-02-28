// CSSRuleInspectorDlg.cpp : Implementation of CCSSRuleInspectorDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "CSSRuleInspectorDlg.h"

#include "ECSSViewGroup.h"
#include "ECSSDocument.h"

#include "ControlsWindow.h"

#if 0
/*
#include "CSSStyleRuleDlg.h"
#include "CSSImportRuleDlg.h"
#include "CSSMediaRuleDlg.h"
*/

class CCSSSelectorListData : public CXMLData
{
public:
	CComPtr<ILCSSSelectorList> m_selectorList;

public:
	CCSSSelectorListData(WCHAR* name, WCHAR* defaultv) : CXMLData(name, defaultv)
	{
	}

	virtual void SetValue(BSTR value)
	{
		if (m_reentrancy == 0)
		{
			m_reentrancy++;

			m_selectorList->put_selectorText(value);

			for (int i = 0; i < m_controls.GetSize(); i++)
			{
				m_controls[i]->OnDataValueChanged(this);
			}

			m_controlWindow->OnDataValueChanged(this);

			m_reentrancy--;
		}
	}

	virtual _bstr_t GetValueAsString()
	{
		CComBSTR text;
		m_selectorList->get_selectorText(&text);
		return text;
	}
};

class CCSSRuleHandler : public CControlsHandler
{
public:
	CECSSViewGroup* m_viewGroup;

	CCSSRuleHandler()
	{
	}
};

class CCSSStyleRuleHandler : public CCSSRuleHandler
{
public:

	int m_reentrancy;

	CCSSStyleRuleHandler()
	{
		m_reentrancy = 0;
	}

	virtual void Setup()
	{
		CCSSSelectorListData* data = new CCSSSelectorListData(L"selector", L"");
		m_controlWindow->AddData(data);

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("selector"));
		m_controlWindow->GetControl("selector")->ConnectData(m_controlWindow->GetData(L"selector"));

		{
			m_viewGroup->m_pDocument->m_styleSheet->createSelectorList(&data->m_selectorList);

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				CComBSTR selectorText2;
				styleRule->get_selectorText(&selectorText2);

				CComPtr<ILCSSSelectorList> selectorList2;
				styleRule->get_selectors(&selectorList2);

				long length;
				selectorList2->get_length(&length);
				for (int n = 0; n < length; n++)
				{
					CComPtr<ILCSSSelector> selector;
					selectorList2->item(n, &selector);

					CComBSTR text;
					selector->get_selectorText(&text);

					long length2;
					data->m_selectorList->get_length(&length2);
					for (int n2 = 0; n2 < length2; n2++)
					{
						CComPtr<ILCSSSelector> selector2;
						data->m_selectorList->item(n2, &selector2);

						CComBSTR text2;
						selector2->get_selectorText(&text2);

						if (!wcscmp(text, text2))
							break;
					}

					if (n2 == length2)	// New selector, append
					{
						data->m_selectorList->appendItem(text, NULL);
					}
				}
			}

			m_reentrancy++;
			if (data->m_reentrancy == 0)
			{
				data->m_reentrancy++;

				for (int i = 0; i < data->m_controls.GetSize(); i++)
				{
					data->m_controls[i]->OnDataValueChanged(data);
				}

				data->m_controlWindow->OnDataValueChanged(data);

				data->m_reentrancy--;
			}
			m_reentrancy--;
		}
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}

	void OnDataValueChanged(CXMLData* pData)
	{
		if (m_reentrancy == 0)
		{
			m_reentrancy++;

			_bstr_t selector = pData->GetValueAsString();

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				styleRule->put_selectorText(selector);
			}

			m_reentrancy--;
		}
	}
};

class CCSSImportRuleHandler : public CCSSRuleHandler
{
public:

	int m_reentrancy;

	CCSSImportRuleHandler()
	{
		m_reentrancy = 0;
	}

	virtual void Setup()
	{
#if 0
		CCSSSelectorListData* data = new CCSSSelectorListData(L"selector", L"");
		m_controlWindow->AddData(data);

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("selector"));
		m_controlWindow->GetControl("selector")->ConnectData(m_controlWindow->GetData(L"selector"));

		{
			m_viewGroup->m_pDocument->m_styleSheet->createSelectorList(&data->m_selectorList);

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				CComBSTR selectorText2;
				styleRule->get_selectorText(&selectorText2);

				CComPtr<ILCSSSelectorList> selectorList2;
				styleRule->get_selectors(&selectorList2);

				long length;
				selectorList2->get_length(&length);
				for (int n = 0; n < length; n++)
				{
					CComPtr<ILCSSSelector> selector;
					selectorList2->item(n, &selector);

					CComBSTR text;
					selector->get_selectorText(&text);

					long length2;
					data->m_selectorList->get_length(&length2);
					for (int n2 = 0; n2 < length2; n2++)
					{
						CComPtr<ILCSSSelector> selector2;
						data->m_selectorList->item(n2, &selector2);

						CComBSTR text2;
						selector2->get_selectorText(&text2);

						if (!wcscmp(text, text2))
							break;
					}

					if (n2 == length2)	// New selector, append
					{
						data->m_selectorList->appendItem(text, NULL);
					}
				}
			}

			m_reentrancy++;
			if (data->m_reentrancy == 0)
			{
				data->m_reentrancy++;

				for (int i = 0; i < data->m_controls.GetSize(); i++)
				{
					data->m_controls[i]->OnDataValueChanged(data);
				}

				data->m_controlWindow->OnDataValueChanged(data);

				data->m_reentrancy--;
			}
			m_reentrancy--;
		}
#endif
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}

	void OnDataValueChanged(CXMLData* pData)
	{
#if 0
		if (m_reentrancy == 0)
		{
			m_reentrancy++;

			_bstr_t selector = pData->GetValueAsString();

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				styleRule->put_selectorText(selector);
			}

			m_reentrancy--;
		}
#endif
	}
};

class CCSSMediaRuleHandler : public CCSSRuleHandler
{
public:

	int m_reentrancy;

	CCSSMediaRuleHandler()
	{
		m_reentrancy = 0;
	}

	virtual void Setup()
	{
#if 0
		CCSSSelectorListData* data = new CCSSSelectorListData(L"selector", L"");
		m_controlWindow->AddData(data);

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("selector"));
		m_controlWindow->GetControl("selector")->ConnectData(m_controlWindow->GetData(L"selector"));

		{
			m_viewGroup->m_pDocument->m_styleSheet->createSelectorList(&data->m_selectorList);

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				CComBSTR selectorText2;
				styleRule->get_selectorText(&selectorText2);

				CComPtr<ILCSSSelectorList> selectorList2;
				styleRule->get_selectors(&selectorList2);

				long length;
				selectorList2->get_length(&length);
				for (int n = 0; n < length; n++)
				{
					CComPtr<ILCSSSelector> selector;
					selectorList2->item(n, &selector);

					CComBSTR text;
					selector->get_selectorText(&text);

					long length2;
					data->m_selectorList->get_length(&length2);
					for (int n2 = 0; n2 < length2; n2++)
					{
						CComPtr<ILCSSSelector> selector2;
						data->m_selectorList->item(n2, &selector2);

						CComBSTR text2;
						selector2->get_selectorText(&text2);

						if (!wcscmp(text, text2))
							break;
					}

					if (n2 == length2)	// New selector, append
					{
						data->m_selectorList->appendItem(text, NULL);
					}
				}
			}

			m_reentrancy++;
			if (data->m_reentrancy == 0)
			{
				data->m_reentrancy++;

				for (int i = 0; i < data->m_controls.GetSize(); i++)
				{
					data->m_controls[i]->OnDataValueChanged(data);
				}

				data->m_controlWindow->OnDataValueChanged(data);

				data->m_reentrancy--;
			}
			m_reentrancy--;
		}
#endif
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}

	void OnDataValueChanged(CXMLData* pData)
	{
#if 0
		if (m_reentrancy == 0)
		{
			m_reentrancy++;

			_bstr_t selector = pData->GetValueAsString();

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				styleRule->put_selectorText(selector);
			}

			m_reentrancy--;
		}
#endif
	}
};

class CCSSColorProfileRuleHandler : public CCSSRuleHandler
{
public:

	int m_reentrancy;

	CCSSColorProfileRuleHandler()
	{
		m_reentrancy = 0;
	}

	virtual void Setup()
	{
	// Data
		//m_controlWindow->AddData(new CXMLStringData(L"@xlink:href", L""));
		//m_controlWindow->AddData(new CXMLStringData(L"@local", L""));
		m_controlWindow->AddData(new CXMLStringData(L"name", L""));
		m_controlWindow->AddData(new CXMLStringData(L"rendering-intent", L"auto"));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("name"));
		m_controlWindow->GetControl("name")->ConnectData(m_controlWindow->GetData(L"name"));

		m_controlWindow->AddControl(new CXMLControlPopup("rendering-intent", L"auto|perceptual|relative-colorimetric|saturation|absolute-colorimetric"));
		m_controlWindow->GetControl("rendering-intent")->ConnectData(m_controlWindow->GetData(L"rendering-intent"));

#if 0
		CCSSSelectorListData* data = new CCSSSelectorListData(L"selector", L"");
		m_controlWindow->AddData(data);

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("selector"));
		m_controlWindow->GetControl("selector")->ConnectData(m_controlWindow->GetData(L"selector"));

		{
			m_viewGroup->m_pDocument->m_styleSheet->createSelectorList(&data->m_selectorList);

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				CComBSTR selectorText2;
				styleRule->get_selectorText(&selectorText2);

				CComPtr<ILCSSSelectorList> selectorList2;
				styleRule->get_selectors(&selectorList2);

				long length;
				selectorList2->get_length(&length);
				for (int n = 0; n < length; n++)
				{
					CComPtr<ILCSSSelector> selector;
					selectorList2->item(n, &selector);

					CComBSTR text;
					selector->get_selectorText(&text);

					long length2;
					data->m_selectorList->get_length(&length2);
					for (int n2 = 0; n2 < length2; n2++)
					{
						CComPtr<ILCSSSelector> selector2;
						data->m_selectorList->item(n2, &selector2);

						CComBSTR text2;
						selector2->get_selectorText(&text2);

						if (!wcscmp(text, text2))
							break;
					}

					if (n2 == length2)	// New selector, append
					{
						data->m_selectorList->appendItem(text, NULL);
					}
				}
			}

			m_reentrancy++;
			if (data->m_reentrancy == 0)
			{
				data->m_reentrancy++;

				for (int i = 0; i < data->m_controls.GetSize(); i++)
				{
					data->m_controls[i]->OnDataValueChanged(data);
				}

				data->m_controlWindow->OnDataValueChanged(data);

				data->m_reentrancy--;
			}
			m_reentrancy--;
		}
#endif
	}

	virtual void OnUIValueChanged(CControl* pControl)
	{
	}

	void OnDataValueChanged(CXMLData* pData)
	{
#if 0
		if (m_reentrancy == 0)
		{
			m_reentrancy++;

			_bstr_t selector = pData->GetValueAsString();

			long ncount;
			m_viewGroup->GetSelectedCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];

				CComPtr<ILCSSRule> rule;
				selectedRule->get_rule(&rule);

				CComQIPtr<ILCSSStyleRule> styleRule = rule;

				styleRule->put_selectorText(selector);
			}

			m_reentrancy--;
		}
#endif
	}
};

////////////////////////////////////////////////////////////////////////////
// CCSSRuleInspectorDlg

int CCSSRuleInspectorDlg::FinalConstruct()
{
	return 0;
}

void CCSSRuleInspectorDlg::FinalRelease()
{
}

LRESULT CCSSRuleInspectorDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(m_viewGroup);
	IDispEventImpl<1, CCSSRuleInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());

	OnViewGroupSelectionChanged();

	return 0;
}

LRESULT CCSSRuleInspectorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CCSSRuleInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());

	return 0;
}

LRESULT CCSSRuleInspectorDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	return 0;
}

void CCSSRuleInspectorDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	if (m_controlWindow)
	{
		HWND hwnd;
		m_controlWindow->get_hwnd(&hwnd);
		::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);
	}
}

void __stdcall CCSSRuleInspectorDlg::OnViewGroupSelectionChanging()
{
}

void __stdcall CCSSRuleInspectorDlg::OnViewGroupSelectionChanged()
{
	ASSERT(m_viewGroup);

	if (m_controlWindow)
	{
		m_controlWindow->DestroyWindow();
		m_controlWindow.Release();
	}

	{
		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		LCSSType ruleType = UNKNOWN_RULE;

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedRule> selectedRule = m_viewGroup->m_targetElements[i];
		//	m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<ILCSSRule> rule;
			selectedRule->get_rule(&rule);

			LCSSType ruleType2;
			rule->get_type(&ruleType2);

			if (i == 0)
			{
				ruleType = ruleType2;
			}
			else if (ruleType != ruleType2)
			{
				ruleType = UNKNOWN_RULE;
				break;
			}
		}

		if (ruleType != UNKNOWN_RULE)
		{
			CComObject<CControlsContainer>* p;
			CComObject<CControlsContainer>::CreateInstance(&p);
			if (p)
			{
				m_controlWindow = p;

				CCSSRuleHandler* handler = NULL;

				if (ruleType == STYLE_RULE)
				{
					CCSSStyleRuleHandler* h = new CCSSStyleRuleHandler();
					handler = h;
				}
				else if (ruleType == IMPORT_RULE)
				{
					CCSSImportRuleHandler* h = new CCSSImportRuleHandler();
					handler = h;
				}
				else if (ruleType == MEDIA_RULE)
				{
					CCSSMediaRuleHandler* h = new CCSSMediaRuleHandler();
					handler = h;
				}
				else if (ruleType == COLOR_PROFILE_RULE)
				{
					CCSSColorProfileRuleHandler* h = new CCSSColorProfileRuleHandler();
					handler = h;
				}

				if (handler)
				{
					handler->m_viewGroup = m_viewGroup;

					p->m_pControlsHandler = handler;

					m_controlWindow->Create(m_hWnd);
					m_controlWindow->ShowWindow(SW_SHOW);

					OnSize();

					if (m_controlWindow->m_pControlsHandler)
					{
						m_controlWindow->m_pControlsHandler->Setup();
					}
				}
			}
		}
		else
		{
		}
	}
}

#endif