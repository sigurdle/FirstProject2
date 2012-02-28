// ECSSDocument.cpp : Implementation of CECSSDocument
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ECSSDocument.h"

#include "ECSSViewGroup.h"

#include "LXMLEditorApp.h"

#include "CSSStyleSheetView.h"
#include "CSSSourceView.h"
#include "CSSPropertiesDlg.h"
#include "CSSRuleInspectorDlg.h"

#if 0

void GetParentRuleList(ILCSSRule* rule, ILCSSRuleList* *pVal)
{
	CComPtr<ILCSSRule> parentRule;
	rule->get_parentRule(&parentRule);

	CComQIPtr<ILCSSMediaRule> mediaRule = parentRule;
	if (mediaRule)
	{
		mediaRule->get_cssRules(pVal);
	}
	else
	{
		CComPtr<ILCSSStyleSheet> styleSheet;
		rule->get_parentStyleSheet(&styleSheet);

		styleSheet->get_cssRules(pVal);
	}
}

int GetRuleIndex(ILCSSRuleList* ruleList, ILCSSRule* rule)
{
	long nrules;
	ruleList->get_length(&nrules);
	for (int i = 0; i < nrules; i++)
	{
		CComPtr<ILCSSRule> rule2;
		ruleList->item(i, &rule2);
		if (rule == rule2)
			return i;
	}

	return -1;
}

IUnknown* GetNodeFromOffsets(ILCSSRuleList* rules, long startoffset, long endoffset, long index0, long index1)
{
	long nrules;
	rules->get_length(&nrules);

	for (int i = 0; i < nrules; i++)
	{
		CComPtr<ILCSSRule> node;
		rules->item(i, &node);

		long offset0;
		long offset1;
		node->getTextOffset(index0, &offset0);
		node->getTextOffset(index1, &offset1);

		if ((startoffset >= offset0) && (endoffset <= offset1))
		{
			return node;
		}
	}

	return NULL;
}

IUnknown* GetNodeFromOffsets(ILCSSStyleSheet* styleSheet, long startoffset, long endoffset, long index0, long index1)
{
	CComPtr<ILCSSRuleList> rules;
	styleSheet->get_cssRules(&rules);

	return GetNodeFromOffsets(rules, startoffset, endoffset, index0, index1);
}

void OffsetRuleOffsets(ILCSSRule* rule, int afterOffset, int offset)
{
	for (int i = 0; i < 6; i++)
	{
		long oldoffset;
		rule->getTextOffset(i, &oldoffset);

		if (oldoffset >= afterOffset)
		{
			rule->setTextOffset(i, oldoffset+offset);
		}
	}
}

void OffsetRuleOffsets(ILCSSStyleSheet* styleSheet, int afterOffset, int offset)
{
	CComPtr<ILCSSRuleList> rules;
	styleSheet->get_cssRules(&rules);

	long nrules;
	rules->get_length(&nrules);

	for (int i = 0; i < nrules; i++)
	{
		CComPtr<ILCSSRule> rule;
		rules->item(i, &rule);

		OffsetRuleOffsets(rule, afterOffset, offset);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CECSSDocument

int CECSSDocument::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CWEUndoManager>::CreateInstance(&m_undoManager);
	if (FAILED(hr)) return hr;
	m_undoManager->AddRef();

	hr = m_textData.CoCreateInstance(CLSID_TextData);
	if (FAILED(hr)) return hr;

	return 0;
}

void CECSSDocument::FinalRelease()
{
	m_curMoniker.Release();
	m_textData.Release();

	if (m_undoManager)
	{
		m_undoManager->Release();
		m_undoManager = NULL;
	}
}

STDMETHODIMP CECSSDocument::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IECSSDocument
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void __stdcall CECSSDocument::OnTextDocumentInsertedText(long offset, long len)
{
	if (m_lockDOM == 0)
	{
		m_lockSource++;

		CComPtr<ITextData> textData;
		get_textData(&textData);

		BSTR data;
		textData->get_data(&data);

		m_styleSheet->set_cssText(data);

		m_lockSource--;
	}

#if 0
	CComPtr<ILDOMDocument> xmldocument;
	get_DOMDocument(&xmldocument);

	CComPtr<ITextData> textData;
	get_textData(&textData);

	for (int i = 0; i < m_bookmarks->m_items.GetSize(); i++)
	{
		// Text inserted before bookmark
		if (offset < m_bookmarks->m_items[i]->m_offset)
		{
			m_bookmarks->m_items[i]->m_offset += len;
		}
		// Text inserted inside bookmark
		else if (offset < m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length)
		{
			m_bookmarks->m_items[i]->m_length += len;
		}
	}

	if (m_lockDOM == 0)
	{
		CComQIPtr<ILDOMAttr> attr = GetNodeFromOffsets(xmldocument, offset, offset, 3, 4);
		if (attr)
		{
			long startTextOffset;
			attr->getTextOffset(3, &startTextOffset);

			long startEndOffset;
			attr->getTextOffset(4, &startEndOffset);

			BSTR data;
			textData->get_data(&data);

			m_lockSource++;

			BSTR battrValue = SysAllocStringLen(&data[startTextOffset], (startEndOffset-startTextOffset)+len);

			attr->put_value(battrValue);

			OffsetNodeOffsets(xmldocument, startTextOffset+1, len);

			SysFreeString(battrValue);

			m_lockSource--;
		}
		else
		{
			m_lockSource++;

			// Find the nearest anccestor element of the inserted text

			ILDOMNode* inNode = GetNodeFromOffsets(xmldocument, FALSE, offset, offset, 0, 8);
			ATLASSERT(inNode);

			CComPtr<ILDOMNode> parentNode;
			inNode->get_parentNode(&parentNode);

			OffsetNodeOffsets(xmldocument, offset+1, len);

			BSTR data;
			textData->get_data(&data);

			long outerStart;
			inNode->getTextOffset(0, &outerStart);

			long outerEnd;
			inNode->getTextOffset(9, &outerEnd);

			OffsetErrors(offset, len);
			RemoveErrorsInRange(outerStart, outerEnd/*-len*/);

		// TODO, I should be able to read from data directly instead of creating a temporay string
			CComBSTR str = SysAllocStringLen(&data[outerStart], outerEnd-outerStart);

			//MessageBox(NULL, _bstr_t(str), "", MB_OK);

			m_addOffset = outerStart;

			CComPtr<ILDOMDocumentFragment> fragment;
			HRESULT hr = xmldocument->parseFragment(str, parentNode, &fragment);

			m_addOffset = 0;

			if (SUCCEEDED(hr))
			{
				OffsetChildNodesOffsets(fragment, 0, outerStart);

				// Validate the parsed nodes
				{
					CComPtr<ILDOMNode> node;
					fragment->get_firstChild(&node);
					while (node)
					{
						CComQIPtr<ILNodeEditVAL> nodeVAL = node;
						if (nodeVAL)
						{
							VARIANT_BOOL bValid;
							nodeVAL->isNodeValid(VARIANT_TRUE, STRICT_VALIDITY_CHECK, &bValid);
						}

						CComPtr<ILDOMNode> nextSibling;
						node->get_nextSibling(&nextSibling);
						node = nextSibling;
					}
				}

				CComPtr<ILDOMNode> replacedChild;
				parentNode->replaceChild(fragment, inNode, &replacedChild);
			}
			else
			{
				CComPtr<ILDOMNotWellformed> nwnode;
				xmldocument->createNotWellformed(str, &nwnode);

				nwnode->setTextOffset(0, 0);
				nwnode->setTextOffset(1, 0);
				nwnode->setTextOffset(2, 0);
				nwnode->setTextOffset(3, str.Length());
				nwnode->setTextOffset(4, str.Length());
				nwnode->setTextOffset(5, str.Length());
				nwnode->setTextOffset(6, str.Length());
				nwnode->setTextOffset(7, str.Length());
				nwnode->setTextOffset(8, str.Length());
				nwnode->setTextOffset(9, str.Length());

			//	OffsetChildNodesOffsets(nwnode, 0, outerStart);
				OffsetNodeOffsets(nwnode, NULL, 0, outerStart);

			//	CComPtr<ILDOMNode> removedChild;
			//	parentNode->removeChild(inNode, &removedChild);
				CComPtr<ILDOMNode> replacedChild;
				parentNode->replaceChild(nwnode, inNode, &replacedChild);
			}

			m_lockSource--;
		}

		Fire_doneParsingDOM();
	}
#endif
}

/*
ILDOMNode* FindCommonContainer(ILDOMNode* node1, ILDOMNode* node2);
ILDOMNode* FindCommonContainerOuter(ILDOMNode* node1, ILDOMNode* node2);
*/

void __stdcall CECSSDocument::OnTextDocumentDeletedText(long offset, long len)
{
	if (m_lockDOM == 0)
	{
		m_lockSource++;

		CComPtr<ITextData> textData;
		get_textData(&textData);

		BSTR data;
		textData->get_data(&data);

		m_styleSheet->set_cssText(data);

		m_lockSource--;
	}

#if 0
	for (int i = m_bookmarks->m_items.GetSize()-1; i >= 0; i--)
	{
		// Text deleted before bookmark
		if (offset+len < m_bookmarks->m_items[i]->m_offset)
		{
			m_bookmarks->m_items[i]->m_offset -= len;
		}
		// Text deleted inside bookmark
		else if (offset+len < m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length)
		{
			m_bookmarks->m_items[i]->m_length -= len;
		}
		// Text deleted partially inside bookmark
		else if (offset < m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length)
		{
			m_bookmarks->m_items[i]->m_length -=
				(m_bookmarks->m_items[i]->m_offset+m_bookmarks->m_items[i]->m_length) - (offset) ;
		}

		if (m_bookmarks->m_items[i]->m_length <= 0)
		{
			m_bookmarks->m_items[i]->Release();
			m_bookmarks->m_items.RemoveAt(i);
		}
	}

	if (m_lockDOM == 0)
	{
		CComQIPtr<ILCSSRule> rule = GetNodeFromOffsets(m_styleSheet, offset, offset+len, 0, 5);

		if (rule)
		{
			long startTextOffset;
			rule->getTextOffset(0, &startTextOffset);

			long startEndOffset;
			rule->getTextOffset(5, &startEndOffset);

			BSTR data;
			textData->get_data(&data);

			m_lockSource++;

			BSTR battrValue = SysAllocStringLen(&data[startTextOffset], (startEndOffset-startTextOffset)-len);

			rule->set_cssText(battrValue);

#if 0
			OffsetNodeOffsets(xmldocument, startTextOffset+1, -len);
#endif

			SysFreeString(battrValue);

			m_lockSource--;
		}
#if 0
		else
		{
			m_lockSource++;

			// Find the nearest ancestor element of the deleted text

			ILDOMNode* startNode = GetNodeFromOffsets(xmldocument, FALSE, offset, offset, 0, 8);
			ILDOMNode* endNode = GetNodeFromOffsets(xmldocument, FALSE, offset+len, offset+len, 0, 8);

			ATLASSERT(startNode);
			ATLASSERT(endNode);

			OffsetNodeOffsets(xmldocument, offset+1, -len);

			CComQIPtr<ILDOMNode> commonContainer = FindCommonContainer(startNode, endNode);

			ATLASSERT(commonContainer);

			long outerStart;
			commonContainer->getTextOffset(0, &outerStart);

			long outerEnd;
			commonContainer->getTextOffset(9, &outerEnd);

			OffsetErrors(offset+1, -len);
			RemoveErrorsInRange(outerStart, outerEnd);

			//outerEnd -= len;	// ? Do this after

			BSTR data;
			textData->get_data(&data);

		// TODO, I should be able to read from data directly instead of creating a temporay string
			CComBSTR str = SysAllocStringLen(&data[outerStart], outerEnd-outerStart);

		//	MessageBox(NULL, _bstr_t(str), "", MB_OK);

			CComPtr<ILDOMNode> parentNode;
			commonContainer->get_parentNode(&parentNode);

			m_addOffset = outerStart;

			CComPtr<ILDOMDocumentFragment> fragment;
			HRESULT hr = xmldocument->parseFragment(str, parentNode, &fragment);

			m_addOffset = 0;

			if (SUCCEEDED(hr))
			{
				OffsetChildNodesOffsets(fragment, 0, outerStart);

				// Validate the parsed nodes
				{
					CComPtr<ILDOMNode> node;
					fragment->get_firstChild(&node);
					while (node)
					{
						CComQIPtr<ILNodeEditVAL> nodeVAL = node;
						if (nodeVAL)
						{
							VARIANT_BOOL bValid;
							nodeVAL->isNodeValid(VARIANT_TRUE, STRICT_VALIDITY_CHECK, &bValid);
						}

						CComPtr<ILDOMNode> nextSibling;
						node->get_nextSibling(&nextSibling);
						node = nextSibling;
					}
				}

				CComPtr<ILDOMNode> replacedChild;
				parentNode->replaceChild(fragment, commonContainer, &replacedChild);
			}
			else
			{
				CComPtr<ILDOMNotWellformed> nwnode;
				xmldocument->createNotWellformed(str, &nwnode);

				nwnode->setTextOffset(0, 0);
				nwnode->setTextOffset(1, 0);
				nwnode->setTextOffset(2, 0);
				nwnode->setTextOffset(3, str.Length());
				nwnode->setTextOffset(4, str.Length());
				nwnode->setTextOffset(5, str.Length());
				nwnode->setTextOffset(6, str.Length());
				nwnode->setTextOffset(7, str.Length());
				nwnode->setTextOffset(8, str.Length());
				nwnode->setTextOffset(9, str.Length());

				OffsetNodeOffsets(nwnode, NULL, 0, outerStart);

			//	CComPtr<ILDOMNode> removedChild;
			//	parentNode->removeChild(inNode, &removedChild);
				CComPtr<ILDOMNode> replacedChild;
				parentNode->replaceChild(nwnode, commonContainer, &replacedChild);

			//	CComPtr<ILDOMNode> removedChild;
			//	parentNode->removeChild(commonContainer, &removedChild);
			}

			m_lockSource--;
		}
#endif

#if 0
		Fire_doneParsingDOM();
#endif
	}
#endif
}

STDMETHODIMP CECSSDocument::handleCSSEvent(/*[in]*/ LCSSObjectType objectType, /*[in]*/ LCSSEventType eventType, /*[in]*/ ILCSSStyleSheet* styleSheet, /*[in]*/ IUnknown* pObject)
{
	if (m_lockSource == 0)
	{
		m_lockDOM++;

		if (objectType == LCSSObject_Rule)
		{
			CComQIPtr<ILCSSRule> rule = pObject;

			if (eventType == LCSSEvent_Insert)
			{
				CComPtr<ILCSSRuleList> ruleList;
				GetParentRuleList(rule, &ruleList);

				int index = GetRuleIndex(ruleList, rule);

				CComBSTR cssText;
				rule->get_cssText(&cssText);

				if (index > 0)	// insert after previous rule
				{
					CComPtr<ILCSSRule> prevRule;
					ruleList->item(index-1, &prevRule);

					long endPreviousTextOffset;
					prevRule->getTextOffset(5, &endPreviousTextOffset);

					OffsetRuleOffsets(rule, 0, -(int)cssText.Length());
					OffsetRuleOffsets(m_styleSheet, endPreviousTextOffset, cssText.Length());

					OffsetRuleOffsets(rule, -(int)cssText.Length(), cssText.Length()+endPreviousTextOffset);

					m_textData->insertText(endPreviousTextOffset, cssText, cssText.Length());
				}
				else	// insert
				{
				}
			}
			else if (eventType == LCSSEvent_Remove)
			{
				long offset0;
				long offset5;
				rule->getTextOffset(0, &offset0);
				rule->getTextOffset(5, &offset5);

				OffsetRuleOffsets(m_styleSheet, offset5, -(offset5-offset0));

				long len = offset5-offset0;
				m_textData->deleteText(offset0, len);
			}
			else
				ATLASSERT(0);
		}

		m_lockDOM--;
	}

	return S_OK;
}

STDMETHODIMP CECSSDocument::ShowViews(IEFrame* frame)
{
	ILXUIMDIFrameElement* frameelement;
	frame->GetMDIFrame(&frameelement);

	CComPtr<ILXUIDocument> appdocument;
	frameelement->get_ownerDocument(&appdocument);

	CDocumentWorkspace* pWorkspace = &static_cast<CLXMLEditorApp*>(m_app.p)->m_cssDocumentWorkspace;

	CComQIPtr<ILXAddin> addin = m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

//	CComPtr<IUIManager> uiManager;
//	addinSite->GetUIManager((IUnknown**)&uiManager);

	CComObject<CECSSViewGroup>* viewGroup;
	CComObject<CECSSViewGroup>::CreateInstance(&viewGroup);
	if (viewGroup)
	{
		viewGroup->AddRef();
		viewGroup->m_pDocument = this;

		m_viewGroups.Add(viewGroup);

		// CSS Definitions
		{
			CComObject<CCSSStyleSheetView>* cssView;
			CComObject<CCSSStyleSheetView>::CreateInstance(&cssView);
			if (cssView)
			{
				cssView->m_viewGroup = viewGroup;
				cssView->m_view = pWorkspace->m_views[0];
			}
		//	viewGroup->m_views.Add(cssView);

			ILXUIElement* e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"vbox", IID_ILXUIElement, (void**)&e);
#if 0
			e->setAttribute(L"style", L"-moz-box-flex: 1;");

			long cookie;
			e->addBehavior(NULL, &CComVariant(cssView->GetUnknown()), &cookie);
#endif

			viewGroup->m_views.Add(e.Detach());
		}

		// Source
		{
			CComObject<CCSSSourceView>* sourceView;
			CComObject<CCSSSourceView>::CreateInstance(&sourceView);
			if (sourceView)
			{
				sourceView->m_viewGroup = viewGroup;
				sourceView->m_view = pWorkspace->m_views[1];
			}
//			viewGroup->m_views.Add(sourceView);

			ILXUIElement* e;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"vbox", IID_ILXUIElement, (void**)&e);
#if 0
			e->setAttribute(L"style", L"-moz-box-flex: 1;");

			long cookie;
			e->addBehavior(NULL, &CComVariant(sourceView->GetUnknown()), &cookie);
#endif
			viewGroup->m_views.Add(e.Detach());
		}

#if 0
	// CSS Properties
		{
			CComObject<CCSSPropertiesDlg>* p;
			CComObject<CCSSPropertiesDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[2];
			}
			viewGroup->m_views.Add(p);
		}

	// Selected CSS Rule(s)
		{
			CComObject<CCSSRuleInspectorDlg>* p;
			CComObject<CCSSRuleInspectorDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_viewGroup = viewGroup;
				p->m_view = pWorkspace->m_views[3];
			}
			viewGroup->m_views.Add(p);
		}
#endif

		pWorkspace->Create(frame, static_cast<CLXMLEditorApp*>(m_app.p), viewGroup);
	}

	UpdateTitles();

#if 0
	CComObject<CECSSViewGroup>* viewGroup;
	CComObject<CECSSViewGroup>::CreateInstance(&viewGroup);
	if (viewGroup)
	{
		viewGroup->AddRef();

#if 0
		pFrame->CreateViewSheet(m_fileTitle, viewGroup, &viewGroup->m_spViewGroupSite);
#endif

		viewGroup->m_pDocument = this;

		//pFrame->QueryInterface(IID_IUnknown, (void**)&viewGroup->m_spFrame);

		CComObject<CCSSStyleSheetView>* cssView;
		CComObject<CCSSStyleSheetView>::CreateInstance(&cssView);
		if (cssView)
		{
			cssView->m_viewGroup = viewGroup;

			//CComPtr<ILStyleSheetList> styleSheetList;
			//documentStyle->get_styleSheets(&styleSheetList);

			uiManager->FindMenu(_Module.GetResourceInstance(), IDR_CSSSTYLESHEETVIEW, &cssView->m_menu);
		//	cssView->m_styleSheet = m_styleSheet;
		//	viewGroup->m_spViewGroupSite->AddPage(cssView, NULL);

			CComPtr<IUIDlgSite> dlgsite;
			static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSite(L"CSS Declarations", cssView, &dlgsite);

			CComQIPtr<IUIDockBar>(viewGroup->m_spViewGroupSite)->DockControlBar(dlgsite, NULL);
		}

		CComObject<CCSSSourceView>* sourceView;
		CComObject<CCSSSourceView>::CreateInstance(&sourceView);
		if (sourceView)
		{
			sourceView->m_viewGroup = viewGroup;

			//CComPtr<ILStyleSheetList> styleSheetList;
			//documentStyle->get_styleSheets(&styleSheetList);

			uiManager->FindMenu(_Module.GetResourceInstance(), IDR_CSSSOURCEVIEW, &sourceView->m_menu);
			//sourceView->m_styleSheet = m_styleSheet;
		//	viewGroup->m_spViewGroupSite->AddPage(sourceView, NULL);

			CComPtr<IUIDlgSite> dlgsite;
			static_cast<CLXMLEditorApp*>(m_app.p)->m_uiManager->CreateDlgSite(L"Source", sourceView, &dlgsite);

			CComQIPtr<IUIDockBar>(viewGroup->m_spViewGroupSite)->DockControlBar(dlgsite, NULL);
		}

		CComQIPtr<IUIMDIFrame> mdiframe = pFrame;

		CComPtr<IUIMDIChild> childFrame;
		mdiframe->CreateChildFrame(viewGroup->m_spViewGroupSite, &childFrame);

		//viewGroup->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);

		//child->UpdateFrameTitle();
	}
#endif

	return S_OK;
}

STDMETHODIMP CECSSDocument::Activate()
{
	return E_NOTIMPL;
}

STDMETHODIMP CECSSDocument::CloseDocument()
{
	return E_NOTIMPL;
}

// IPersist
STDMETHODIMP CECSSDocument::GetClassID(CLSID __RPC_FAR *pClassID)
{
	if (pClassID == NULL) return E_POINTER;
	*pClassID = GetObjectCLSID();
	return S_OK;
}

STDMETHODIMP CECSSDocument::IsDirty()
{
	return E_NOTIMPL;
}

// IPersistMoniker
STDMETHODIMP CECSSDocument::Load(
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode)
{
	m_curMoniker = pimkName;

			LPOLESTR displayName;
			pimkName->GetDisplayName(pibc, NULL, &displayName);
			m_pathName = displayName;
			m_fileTitle = PathFindFileName(m_pathName);
			CoTaskMemFree(displayName);

	HRESULT hr = S_OK;

	m_styleSheet.CoCreateInstance(CLSID_LCSSStyleSheet);

	CComQIPtr<IPersistMoniker> persistMoniker = m_textData;
	hr = persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);

	hr = m_styleSheet->ParseFromTextData(m_textData);

// TODO, I don't removeHandler/unadvise yet
	m_styleSheet->addHandler(this);
	IDispEventImpl<1, CECSSDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>::DispEventAdvise(m_textData);

	return hr;
}

STDMETHODIMP CECSSDocument::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CECSSDocument::SaveCompleted(
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	return E_NOTIMPL;
}

STDMETHODIMP CECSSDocument::GetCurMoniker(/*[out]*/ IMoniker **ppimkName)
{
	if (ppimkName == NULL) return E_POINTER;
	*ppimkName = m_curMoniker;
	if (*ppimkName) (*ppimkName)->AddRef();
	return S_OK;
}

void CECSSDocument::UpdateTitles()
{
	for (int i = 0; i < m_viewGroups.GetSize(); i++)
	{
		m_viewGroups[i]->UpdateTitles(m_viewGroups.GetSize()==1? -1: i);
	}
}

BEGIN_CMD_MAP(CECSSDocument)
// Edit
	CMD_HANDLER(ID_EDIT_UNDO, OnEditUndo)
	CMD_UPDATE(ID_EDIT_UNDO, OnEditUndoUpdate)
	CMD_HANDLER(ID_EDIT_REDO, OnEditRedo)
	CMD_UPDATE(ID_EDIT_REDO, OnEditRedoUpdate)
END_CMD_MAP()

LRESULT CECSSDocument::OnEditUndo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->UndoTo(NULL);
	return 0;
}

LRESULT CECSSDocument::OnEditRedo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->RedoTo(NULL);
	return 0;
}

void CECSSDocument::OnEditUndoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	HRESULT hr = m_undoManager->GetLastUndoDescription(&bdescription);
	if (hr == S_OK)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Undo");
	}

	pCmdUI->Enable(bEnable);
}

void CECSSDocument::OnEditRedoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	HRESULT hr = m_undoManager->GetLastRedoDescription(&bdescription);
	if (hr == S_OK)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Redo");
	}

	pCmdUI->Enable(bEnable);
}

#endif