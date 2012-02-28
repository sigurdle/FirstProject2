/*
 * Structure to describe a specific rendering that our user wants
 * us to maintain.
 */

#if 0

#ifndef ATLTRACENOTIMPL
#define ATLTRACENOTIMPL(funcname)   /*ATLTRACE2(atlTraceNotImpl, 2, _T("ATL: %s not implemented.\n"), funcname);*/ return E_NOTIMPL
#endif


typedef struct tagRENDERING
    {
    FORMATETC       fe;             //The format
    STGMEDIUM       stm;            //The actual data
    LPUNKNOWN       pUnkOrg;        //The real owner
    } RENDERING, *PRENDERING;

class CEnumFormatEtc;

typedef CEnumFormatEtc *PCEnumFormatEtc;

class CEnumFormatEtc : public IEnumFORMATETC
{
    private:
        ULONG           m_cRef;
      //  LPUNKNOWN       m_pUnkRef;
        LPFORMATETC     m_prgfe;
        ULONG           m_iCur;
        ULONG           m_cItems;

    public:
/*
		 CEnumFormatEtc(LPUNKNOWN)
		  {
		  }
        ~CEnumFormatEtc(void)
		  {
		  }

        BOOL Init(PRENDERING)
		  {
		  }

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, void**);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumFORMATETC members
        STDMETHODIMP Next(ULONG, LPFORMATETC, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumFORMATETC **);
		*/

/*
 * CEnumFormatEtc::CEnumFormatEtc
 * CEnumFormatEtc::~CEnumFormatEtc
 *
 * Parameters (Constructor):
 *  pUnkRef         LPUNKNOWN to use for reference counting.
 */

CEnumFormatEtc(LPUNKNOWN pUnkRef)
    {
    m_cRef=0;
  //  m_pUnkRef=pUnkRef;
    m_iCur=0;
    m_cItems=0;
    return;
    }


~CEnumFormatEtc(void)
    {
    if (NULL!=m_prgfe)
        {
        LPMALLOC    pIMalloc;

        if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
            {
            pIMalloc->Free(m_prgfe);
            pIMalloc->Release();
            }
        }

    return;
    }



/*
 * CEnumFormatEtc::Init
 *
 * Purpose:
 *  Copies the FORMATETCs in the data object's listbox into our
 *  own, that is, we make a snapshot for this enumerator.
 *
 * Parameters:
 *  hList           HWND of the listbox containing RENDERINGs
 *
 * Return Value:
 *  BOOL            TRUE if initialization worked,
 *                  FALSE otherwise.
 */
BOOL Init(PRENDERING pren)
    {
    UINT        i, cItems;
    LPMALLOC    pIMalloc;
    PRENDERING  pRen;
    LPFORMATETC pFE;
//    DWORD       cb;

	 pRen = pren;

//    if (NULL==hList)
  //      return FALSE;

    cItems=1;//(UINT)SendMessage(hList, LB_GETCOUNT, 0, 0L);

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return FALSE;

    m_prgfe=(LPFORMATETC)pIMalloc->Alloc(cItems*sizeof(FORMATETC));
    pIMalloc->Release();

    if (NULL!=m_prgfe)
        {
        pFE=m_prgfe;

        for (i=0; i < cItems; i++)
            {
           // cb=SendMessage(hList, LB_GETTEXT, i, (LPARAM)&pRen);

           // if (LB_ERR!=cb)
                {
                //Copy just the FORMATETC
                *pFE++=pRen->fe;
                m_cItems++;
                }
            }
        }

    return TRUE;
    }



/*
 * CEnumFormatEtc::QueryInterface
 * CEnumFormatEtc::AddRef
 * CEnumFormatEtc::Release
 *
 * Purpose:
 *  IUnknown members for CEnumFormatEtc object.  For QueryInterface
 *  we only return out own interfaces and not those of the data
 *  object.  However, since enumerating formats only makes sense
 *  when the data object is around, we insure that it stays as
 *  long as we stay by calling an outer IUnknown for AddRef and
 *  Release.  But since we are not controlled by the lifetime of
 *  the outer object, we still keep our own reference count in
 *  order to free ourselves.
 */

STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
    {
    *ppv=NULL;

    /*
     * Enumerators are separate objects, not the data object, so
     * we only need to support out IUnknown and IEnumFORMATETC
     * interfaces here with no concern for aggregation.
     */
    if (IID_IUnknown==riid || IID_IEnumFORMATETC==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) AddRef(void)
    {
    ++m_cRef;
   // m_pUnkRef->AddRef();
    return m_cRef;
    }

STDMETHODIMP_(ULONG) Release(void)
    {
   // m_pUnkRef->Release();

    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }







/*
 * CEnumFormatEtc::Next
 * CEnumFormatEtc::Skip
 * CEnumFormatEtc::Reset
 * CEnumFormatEtc::Clone
 *
 * Standard enumerator members for IEnumFORMATETC
 */

STDMETHODIMP Next(ULONG cFE, LPFORMATETC pFE
    , ULONG *pulFE)
    {
    ULONG           cReturn=0L;

    if (NULL==m_prgfe)
        return ResultFromScode(S_FALSE);

    if (NULL==pulFE)
        {
        if (1L!=cFE)
            return ResultFromScode(E_POINTER);
        }
    else
        *pulFE=0L;

    if (NULL==pFE || m_iCur >= m_cItems)
        return ResultFromScode(S_FALSE);

    while (m_iCur < m_cItems && cFE > 0)
        {
		 *pFE=m_prgfe[m_iCur++];

//		 TCHAR str[256];
//			wsprintf(str, _T("!Next( %d )"), pFE->cfFormat);
//			MessageBox(NULL, str, _T(""), MB_OK);

		 pFE++;
        cReturn++;
        cFE--;
        }

    if (NULL!=pulFE)
        *pulFE=cReturn;

    return NOERROR;
    }


STDMETHODIMP Skip(ULONG cSkip)
    {
	 MessageBox(NULL, _T("Skip"), _T(""), MB_OK);

	if ((m_iCur+cSkip) >= m_cItems)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }


STDMETHODIMP Reset(void)
    {
//	 MessageBox(NULL, L"Reset", L"", MB_OK);

	m_iCur=0;
    return NOERROR;
    }


STDMETHODIMP Clone(LPENUMFORMATETC *ppEnum)
    {
	 MessageBox(NULL, _T("Clone"), _T(""), MB_OK);

    PCEnumFormatEtc     pNew;
    LPMALLOC            pIMalloc;
    LPFORMATETC         prgfe;
    BOOL                fRet=TRUE;
    ULONG               cb;

    *ppEnum=NULL;

    //Copy the memory for the list.
    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return ResultFromScode(E_OUTOFMEMORY);

    cb=m_cItems*sizeof(FORMATETC);
    prgfe=(LPFORMATETC)pIMalloc->Alloc(cb);

    if (NULL!=prgfe)
        {
        //Copy the formats
        memcpy(prgfe, m_prgfe, (int)cb);

        //Create the clone
        pNew=new CEnumFormatEtc(NULL/*m_pUnkRef*/);

        if (NULL!=pNew)
            {
            pNew->m_iCur=m_iCur;
            pNew->m_prgfe=prgfe;
            pNew->AddRef();
            fRet=TRUE;
            }
        }

    pIMalloc->Release();

    *ppEnum=pNew;
    return fRet ? NOERROR : ResultFromScode(E_OUTOFMEMORY);
    }
};

/*
 * IENUMFE.CPP
 * Data Tranfer Object for Chapter 12
 *
 * IEnumFORMATETC implementation specifically for the Data Tranfer
 * objects.  This enumerator copies the state of the data list in
 * the data object and uses that to maintain what FORMATETCs it
 * knows.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

//#include "stdafx.h"

//#include "ienumfe.h"


extern HINSTANCE g_hInst;



class CMyDataObject : public IDataObject/*Impl<CMyDataObject>*/
{
public:
//	HGLOBAL	m_hGlobal;
//	STGMEDIUM m_stgMedium;
	PRENDERING m_pren;

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppv)
	{
		*ppv=NULL;
		
		if (IID_IUnknown==riid)
			*ppv=this;
		
		if (IID_IDataObject==riid)
			*ppv=this;//m_pIDataObject;
		
		if (NULL!=*ppv)
		{
			((LPUNKNOWN)*ppv)->AddRef();
			return NOERROR;
		}
		
		return ResultFromScode(E_NOINTERFACE);
	}

	virtual ULONG STDMETHODCALLTYPE AddRef( void)
	{
	//	MessageBox(NULL, L"q2", L"", MB_OK);
		return 0;
	}
	
	virtual ULONG STDMETHODCALLTYPE Release( void)
	{
	//	MessageBox(NULL, L"q3", L"", MB_OK);
		return 0;
	}

	STDMETHOD(GetData)(FORMATETC *lpFormatEtc, STGMEDIUM *lpStgMedium)
	{
//			TCHAR name[256] = {0};
//			GetClipboardFormatName(lpFormatEtc->cfFormat, name, sizeof(name));
//			TCHAR str[256];
//			wsprintf(str, _T("%u GetData(%s)"), lpFormatEtc->cfFormat, name);

		if (lpFormatEtc->cfFormat == m_pren->fe.cfFormat &&
			lpFormatEtc->tymed == m_pren->fe.tymed)
		{
		//	MessageBox(NULL, "wer", "", MB_OK);
			*lpStgMedium=m_pren->stm;
		    AddRef();
			 return NOERROR;
		}

		return DATA_E_FORMATETC;
	}
	STDMETHOD(GetDataHere)(FORMATETC* /* pformatetc */, STGMEDIUM* /* pmedium */)
	{
//		MessageBox(NULL, _T("GetDataHere()"), _T(""), MB_OK);
		ATLTRACENOTIMPL(_T("IDataObjectImpl::GetDataHere"));
	}
	STDMETHOD(QueryGetData)(FORMATETC* pFE)
	{
//		TCHAR name[256] = {0};
//		GetClipboardFormatName(pFE->cfFormat, name, sizeof(name));
//		TCHAR str[256];
//		wsprintf(str, _T("QueryGetData(%s, %d, %d)"), name, pFE->tymed, pFE->dwAspect);
//		MessageBox(NULL, str, _T(""), MB_OK);

		PRENDERING	pRen = m_pren;
		
		if (pFE->cfFormat==pRen->fe.cfFormat
			&& (pFE->tymed & pRen->fe.tymed)
			&& pFE->dwAspect==pRen->fe.dwAspect)
		{
			return NOERROR;
		}
		
		return ResultFromScode(S_FALSE);
	}
	STDMETHOD(GetCanonicalFormatEtc)(FORMATETC* /* pformatectIn */,FORMATETC* /* pformatetcOut */)
	{
		MessageBox(NULL, _T("GetCanonicalFormatEtc()"), _T(""), MB_OK);
		ATLTRACENOTIMPL(_T("IDataObjectImpl::GetCanonicalFormatEtc"));
	}
	STDMETHOD(SetData)(FORMATETC* pFE, STGMEDIUM* pSTM, BOOL  fRelease)
	{
		//	MessageBox(NULL, L"SetData", L"", MB_OK);
		
		//We have to remain responsible for the data.
		if (!fRelease)
			return ResultFromScode(E_FAIL);
		
		//	ATLTRACENOTIMPL(_T("IDataObjectImpl::SetData"));
		
		//		m_stgMedium = *pmedium;
		
		PRENDERING prn=new RENDERING;
		
		if (NULL==prn)
			return ResultFromScode(E_OUTOFMEMORY);
		
		prn->fe=*pFE;
		prn->stm=*pSTM;
		prn->pUnkOrg=pSTM->pUnkForRelease;
		prn->stm.pUnkForRelease=this;
		
		m_pren = prn;
		
		return 0;
	}
	STDMETHOD(EnumFormatEtc)(DWORD dwDir, IEnumFORMATETC** ppEnum)
	{
	//	MessageBox(NULL, L"EnumFormatsETc()", L"", MB_OK);

		PCEnumFormatEtc     pEnum;
		
		*ppEnum=NULL;
		
		/*
		* From an external point of view there are no SET formats,
		* because we want to allow the user of this component object
		* to be able to stuff ANY format in via Set.  Only external
		* users will call EnumFormatEtc and they can only Get.
		*/
		
		switch (dwDir)
		{
		case DATADIR_GET:
			pEnum=new CEnumFormatEtc(NULL/*m_pUnkOuter*/);
			break;
			
		case DATADIR_SET:
		default:
			pEnum=NULL;
			break;
		}
		
		if (NULL==pEnum)
			return ResultFromScode(E_FAIL);
		else
		{
			//Let the enumerator copy our format list.
			if (!pEnum->Init(m_pren/*m_pObj->m_hList*/))
			{
            delete pEnum;
            return ResultFromScode(E_FAIL);
			}
			
			pEnum->AddRef();
		}
		
		*ppEnum=pEnum;
		return NOERROR;

		ATLTRACENOTIMPL(_T("IDataObjectImpl::EnumFormatEtc"));
	}
	STDMETHOD(DAdvise)(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink,
		DWORD *pdwConnection)
	{
				MessageBox(NULL, _T("DAdvise()"), _T(""), MB_OK);

	/*
		ATLTRACE2(atlTraceControls,2,_T("IDataObjectImpl::DAdvise\n"));
		T* pT = static_cast<T*>(this);
		HRESULT hr = S_OK;
		if (pT->m_spDataAdviseHolder == NULL)
			hr = CreateDataAdviseHolder(&pT->m_spDataAdviseHolder);

		if (hr == S_OK)
			hr = pT->m_spDataAdviseHolder->Advise((IDataObject*)this, pformatetc, advf, pAdvSink, pdwConnection);

		return hr;*/
		return 0;
	}
	STDMETHOD(DUnadvise)(DWORD dwConnection)
	{
				MessageBox(NULL, _T("DUnadvise()"), _T(""), MB_OK);

	/*
		ATLTRACE2(atlTraceControls,2,_T("IDataObjectImpl::DUnadvise\n"));
		T* pT = static_cast<T*>(this);
		HRESULT hr = S_OK;
		if (pT->m_spDataAdviseHolder == NULL)
			hr = OLE_E_NOCONNECTION;
		else
			hr = pT->m_spDataAdviseHolder->Unadvise(dwConnection);
		return hr;
	*/
		return 0;
	}
	STDMETHOD(EnumDAdvise)(IEnumSTATDATA **ppenumAdvise)
	{
		MessageBox(NULL, _T("EnumAdvise()"), _T(""), MB_OK);

/*
		ATLTRACE2(atlTraceControls,2,_T("IDataObjectImpl::EnumDAdvise\n"));
		T* pT = static_cast<T*>(this);
		HRESULT hr = E_FAIL;
		if (pT->m_spDataAdviseHolder != NULL)
			hr = pT->m_spDataAdviseHolder->EnumAdvise(ppenumAdvise);
		return hr;
	*/
		return 0;
	}
};

class CMyDropSource : public IDropSource
{
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppv)
	{
		*ppv=NULL;
		
		if (IID_IUnknown==riid)
			*ppv=this;
		
		if (IID_IDropSource==riid)
			*ppv=this;//m_pIDataObject;
		
		if (NULL!=*ppv)
		{
			((LPUNKNOWN)*ppv)->AddRef();
			return NOERROR;
		}

		return 0;
	}
		
	virtual ULONG STDMETHODCALLTYPE AddRef( void)
	{
		return 1;
	//	delete this;
	}
	
	virtual ULONG STDMETHODCALLTYPE Release( void)
	{
		return 0;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryContinueDrag( 
		/* [in] */ BOOL fEscapePressed,
		/* [in] */ DWORD grfKeyState)
	{
		if (!(grfKeyState & MK_LBUTTON))
		{
		//	MessageBox(L"C", L"", MB_OK);
			return DRAGDROP_S_DROP/*CANCEL*/;
		}

		return S_OK;
	}
		
		virtual HRESULT STDMETHODCALLTYPE GiveFeedback( 
		/* [in] */ DWORD dwEffect)
	{
			return DRAGDROP_S_USEDEFAULTCURSORS;
	}
};

#endif