#pragma once

#if 0

class CEnumFormat : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public IEnumFORMATETC
{
public:
	CEnumFormat()
	{
		m_iCur = 0;
		m_dwRef = 0;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (riid == IID_IUnknown)
		{
			*ppvObject = reinterpret_cast<void*>(static_cast<IUnknown*>(this));
		}
		else if (riid == IID_IEnumFORMATETC)
		{
			*ppvObject = reinterpret_cast<void*>(static_cast<IEnumFORMATETC*>(this));
		}
		else
			return E_NOINTERFACE;
		
		AddRef();
		return S_OK;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef( void)
	{
		m_dwRef++;
		return m_dwRef;
	}

	virtual ULONG STDMETHODCALLTYPE Release( void)
	{
		m_dwRef--;
		if (m_dwRef == 0)
		{
			delete this;
			return 0;
		}
		return m_dwRef;
	}

	ULONG m_dwRef;

	int m_iCur;
	CArray<FORMATETC,FORMATETC> m_items;

	/*
BEGIN_COM_MAP(CEnumFormat)
	COM_INTERFACE_ENTRY(IEnumFORMATETC)
END_COM_MAP()
*/

	STDMETHODIMP Next(ULONG cFE, LPFORMATETC pFE, ULONG *pulFE)
	{
		 ULONG           cReturn=0L;
		 
		 /*if (NULL==m_prgfe)
			 return ResultFromScode(S_FALSE);
			 */
		 
		 if (pulFE == NULL)
		 {
			 if (1L!=cFE)
				 return ResultFromScode(E_POINTER);
		 }
		 else
			 *pulFE=0L;
		 
		 if (NULL==pFE || m_iCur >= m_items.GetSize()/*m_cItems*/)
			 return ResultFromScode(S_FALSE);
		 
		 while (m_iCur < m_items.GetSize()/*m_cItems*/ && cFE > 0)
		 {
			 *pFE=m_items[m_iCur++];
			 
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

		 /*
		if ((m_iCur+cSkip) >= m_cItems)
			  return ResultFromScode(S_FALSE);

		 m_iCur+=cSkip;
		 */
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

#if 0
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
#endif
		 return S_OK;
	};
};

//#include <atlctl.h>

class COleDataObject : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public IDataObject
//	public IDataObjectImpl
{
public:
	COleDataObject()
	{
		m_dwRef = 0;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (riid == IID_IUnknown)
		{
			*ppvObject = reinterpret_cast<void*>(static_cast<IUnknown*>(this));
		}
		else if (riid == IID_IDataObject)
		{
			*ppvObject = reinterpret_cast<void*>(static_cast<IDataObject*>(this));
		}
		else
			return E_NOINTERFACE;
		
		AddRef();
		return S_OK;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef( void)
	{
		m_dwRef++;
		return m_dwRef;
	}

	virtual ULONG STDMETHODCALLTYPE Release( void)
	{
		m_dwRef--;
		if (m_dwRef == 0)
		{
			delete this;
			return 0;
		}
		return m_dwRef;
	}

	ULONG m_dwRef;

	IDataAdviseHolder*	m_spDataAdviseHolder;

typedef struct tagRENDERING
    {
    FORMATETC       fe;             //The format
    STGMEDIUM       stm;            //The actual data
    LPUNKNOWN       pUnkOrg;        //The real owner
}
RENDERING, *PRENDERING;

	CArray<RENDERING,RENDERING> m_items;

	/*
BEGIN_COM_MAP(COleDataObject)
	COM_INTERFACE_ENTRY(IDataObject)
END_COM_MAP()
*/

	STDMETHODIMP DAdvise(LPFORMATETC pFormatetc, 
												 DWORD advf,
												 LPADVISESINK pAdvSink, 
												 LPDWORD pdwConnection)
	{
		//		  MessageBox(NULL, "IDataObject::DAdvise", "", MB_OK);
		
// if no DataAdviseHolder has been created, then create one.
		if(m_spDataAdviseHolder == NULL)
			CreateDataAdviseHolder(&m_spDataAdviseHolder);
		
		if(m_spDataAdviseHolder)
		{
			// pass on to the DataAdviseHolder
			return m_spDataAdviseHolder->Advise(this, pFormatetc, advf, pAdvSink, pdwConnection);
		}
		
		return E_FAIL;
	}
	STDMETHODIMP DUnadvise(DWORD)
	{
		MessageBox(NULL, "IDataObject::DUnadvise", "", MB_OK);
		return E_NOTIMPL;
	}
	STDMETHODIMP EnumDAdvise(LPENUMSTATDATA*)
	{
		MessageBox(NULL, "IDataObject::EnumDAdvise", "", MB_OK);
		return E_NOTIMPL;
	}

	STDMETHODIMP EnumFormatEtc(DWORD dwDirection, LPENUMFORMATETC* ppenumFormatetc)
	{
		CEnumFormat* pEnum = new CEnumFormat;
		//CComObject<CEnumFormat>::CreateInstance(&pEnum);
		if (pEnum)
		{
			for (int i = 0; i < m_items.GetSize(); i++)
			{
				pEnum->m_items.Add(m_items[i].fe);
			}

			*ppenumFormatetc = pEnum;
			(*ppenumFormatetc)->AddRef();

			return S_OK;
		}

		//		return OleRegEnumFormatEtc(CLSID_PDDocument, dwDirection, ppenumFormatetc);
				//MessageBox(NULL, "IDataObject::EnumFormatEtc", "", MB_OK);
		return E_FAIL;
	}

	STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC)
	{
		MessageBox(NULL, "IDataObject::GetCanonicalFormatEtc", "", MB_OK);
		return E_NOTIMPL;
	}

	STDMETHODIMP GetData(FORMATETC* pFormatetc, STGMEDIUM* pMedium)
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (	(m_items[i].fe.cfFormat == pFormatetc->cfFormat) &&
					(m_items[i].fe.tymed == pFormatetc->tymed))
			{
				*pMedium = m_items[i].stm;
				AddRef();
				//if (pMedium->tymed == TYMED_ISTORAGE)
				//	pMedium->pstg->AddRef();
				return S_OK;
			}
		}

		/*
		if (pFormatetc->cfFormat == CF_TEXT && pFormatetc->tymed == TYMED_HGLOBAL)
		{
			pMedium->tymed = TYMED_HGLOBAL;
			
			CUString str = "Dette er en test";
			pMedium->hGlobal = (HGLOBAL)GlobalAlloc(GMEM_MOVEABLE, str.GetLength()+1);
			if (pMedium->hGlobal)
			{
				char* p = (char*)GlobalLock(pMedium->hGlobal);
				if (p)
				{
					strcpy(p, str);
					GlobalUnlock(pMedium->hGlobal);
				}
			}
			
			return S_OK;
		}
		else
		{
			//MessageBox(NULL, "IDataObject::GetData", "", MB_OK);
		}
		*/

		return DV_E_FORMATETC;
	}

	STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM)
	{
		MessageBox(NULL, "IDataObject::GetDataHere", "", MB_OK);
		return E_NOTIMPL;
	}

	STDMETHODIMP QueryGetData(LPFORMATETC pFE)
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (	(pFE->cfFormat == m_items[i].fe.cfFormat) &&
					(pFE->tymed & m_items[i].fe.tymed) &&
					(pFE->dwAspect == m_items[i].fe.dwAspect))
			{
				return S_OK;
			}
		}

		return DV_E_FORMATETC;
	}

	STDMETHODIMP SetData(LPFORMATETC pEtc, LPSTGMEDIUM pMed, BOOL)
	{
		RENDERING r;
		r.fe = *pEtc;
		r.stm = *pMed;
		r.stm.pUnkForRelease = this;
		m_items.Add(r);
		//MessageBox(NULL, "IDataObject::SetData", "", MB_OK);
		return S_OK;
	}
};

#endif