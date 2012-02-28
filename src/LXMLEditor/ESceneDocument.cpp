#include "stdafx.h"
#include "LXMLEditor2.h"
#include "ESceneDocument.h"

#include "LXMLEditorApp.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CESceneDocument

STDMETHODIMP CESceneDocument::ShowViews(IEFrame* pFrame)
{
#if 0
	CComPtr<ILXFrameworkFrame> frame;
	static_cast<CLXMLEditorApp*>(m_app.p)->m_spAddinSite->GetFrame(&frame);

	CComPtr<ILXFrameworkApp> app;
	frame->GetApp(&app);

	CComPtr<ILXUIMDIFrameElement> frameelement;
	frame->get_Element(&frameelement);

	CComPtr<ILXUIDocument> appdocument;
	app->get_Document(&appdocument);

//	CComPtr<ILXUIElement> mdiclient;
//	frameelement->getMDIClientElement(&mdiclient);

#if 0
	CComPtr<ILDOMElement> mdiclient = GetElementByTagNameNS(frameelement, L"http://www.lerstad.com/2004/lxui", L"mdiclient", FALSE);

	if (mdiclient)
	{
		CComPtr<ILXUIElement> mdichild;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"mdichild", (ILDOMElement**)&mdichild);

		mdiclient->appendChild(mdichild, NULL);
	}
#endif

	CDocumentWorkspace* pWorkspace = &static_cast<CLXMLEditorApp*>(m_app.p)->m_sceneDocumentWorkspace;

	CComQIPtr<ILXAddin> addin = m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<IUIManager> uiManager;
	addinSite->GetUIManager((IUnknown**)&uiManager);

	CComQIPtr<IUIMDIFrame> mdiframe = pFrame;

	/*
	CComObject<CEXMLViewGroup>* viewGroup;
	CComObject<CEXMLViewGroup>::CreateInstance(&viewGroup);
	if (viewGroup)
	{
		viewGroup->AddRef();
		viewGroup->SetDocument(this);
		*/

	// Create all views

	// 3DView(s)
		{
			CComPtr<ILDOMElement> e;
			appdocument->createElementNS(NULL, L"content", &e);

			CComPtr<IUnknown> old;
			e->setUserData(L"n", /*viewGroup->*/GetUnknown(), NULL, &old);

			VARIANT vFactory;
			V_VT(&vFactory) = VT_UNKNOWN;
			V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;
			V_UNKNOWN(&vFactory)->AddRef();

			long cookie;
			e->addBehavior(L"#factory#scene_3dview", &vFactory, &cookie);

			m_views.Add(e.Detach());
		}

	// SceneGraphDlg
		{
			CComPtr<ILDOMElement> e;
			appdocument->createElementNS(NULL, L"content", &e);

			CComPtr<IUnknown> old;
			e->setUserData(L"n", /*viewGroup->*/GetUnknown(), NULL, &old);

			VARIANT vFactory;
			V_VT(&vFactory) = VT_UNKNOWN;
			V_UNKNOWN(&vFactory) = static_cast<CLXMLEditorApp*>(m_app.p)->m_pElementBehaviorFactory;
			V_UNKNOWN(&vFactory)->AddRef();

			long cookie;
			e->addBehavior(L"#factory#scene_graph", &vFactory, &cookie);

			m_views.Add(e.Detach());
		}

		pWorkspace->Create(pFrame, static_cast<CLXMLEditorApp*>(m_app.p), this/*viewGroup*/);
	//}

//	UpdateTitles();
#endif

	return S_OK;
}

STDMETHODIMP CESceneDocument::Activate()
{
#if 0
	gApp->m_frame->MDIActivate(((CWebXMLViewGroup*)m_viewGroups[0])->m_hWnd);
#endif
	return S_OK;
}

STDMETHODIMP CESceneDocument::CloseDocument()
{

	return S_OK;
}

// CViewGroup
HRESULT CESceneDocument::OnActivate(BOOL bActivate)
{
	if (bActivate)
	{
		CViewGroup::Activate(bActivate);
	}
	else //if (!bActivate)
	{
		CViewGroup::Activate(bActivate);
	}

	return S_OK;
}

// CViewGroup
HRESULT CESceneDocument::OnClose()
{
	return S_OK;
}

// IPersist
STDMETHODIMP CESceneDocument::GetClassID(CLSID __RPC_FAR *pClassID)
{
	if (pClassID == NULL) return E_POINTER;
	*pClassID = CLSID_ESceneDocument;
	return S_OK;
}

STDMETHODIMP CESceneDocument::IsDirty( void)
{
	return E_NOTIMPL;
}

// IPersistMoniker
STDMETHODIMP CESceneDocument::Load(
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode)
{
	HRESULT hr;

	hr = m_scene.CoCreateInstance(CLSID_LX3DScene);

	if (SUCCEEDED(hr))
	{
		/*
		CComQIPtr<IOleObject> spOleObject = m_document;
		if (spOleObject)
		{
			spOleObject->SetClientSite(this);
*/
			CComQIPtr<IPersistMoniker> persistMoniker = m_scene;
			if (persistMoniker)
			{
		//		m_document->put_errorHandler(this);

				hr = persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);
				if (SUCCEEDED(hr))
				{
					LPOLESTR displayName;
					pimkName->GetDisplayName(pibc, NULL, &displayName);
					m_pathName = displayName;
					m_fileTitle = PathFindFileName(m_pathName);
					CoTaskMemFree(displayName);

#if 0
					m_lockSource++;

					Prepare();

					InitTree();

#if 0	// TODO, have this somewhere, but m_app isn't set here yet
					AddRenderBehavior();
#endif

					SetupEventListener();

					Fire_doneParsingDOM();

					m_lockSource--;
#endif

					return S_OK;
				}
			}
		//}
	}

	return E_FAIL;
}

STDMETHODIMP CESceneDocument::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CESceneDocument::SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	return E_NOTIMPL;
}

STDMETHODIMP CESceneDocument::GetCurMoniker( 
      /* [out] */ IMoniker **ppimkName)
{
	return E_NOTIMPL;
}

#endif