#pragma once

class COleServerItem
{
public:

	CComPtr<IOleObject> m_spOleObject;

	void CopyToClipboard()
	{
		CComObject<COleDataObject>* dataObject;
		CComObject<COleDataObject>::CreateInstance(&dataObject);
		dataObject->AddRef();

		GetClipboardData(dataObject, FALSE, NULL, NULL);

		::OleSetClipboard(dataObject);
	}

	void COleServerItem::GetClipboardData(COleDataObject* pDataSource,
		BOOL bIncludeLink, LPPOINT lpOffset, LPSIZE lpSize)
	{
		STGMEDIUM stgMedium;

		// add CF_EMBEDDEDOBJECT by creating memory storage copy of the object
		GetEmbedSourceData(&stgMedium);
		{
			FORMATETC etc = {(CLIPFORMAT)_oleData.cfEmbedSource, NULL, DVASPECT_CONTENT, -1, TYMED_ISTORAGE};
			pDataSource->SetData(&etc, &stgMedium, TRUE);
		}

		{
			CUString str = "Dette er en test";
			stgMedium.hGlobal = (HGLOBAL)GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, str.GetLength()+1);
			if (stgMedium.hGlobal)
			{
				char* p = (char*)GlobalLock(stgMedium.hGlobal);
				if (p)
				{
					strcpy(p, str);
					GlobalUnlock(stgMedium.hGlobal);
				}
			}

			stgMedium.tymed = TYMED_HGLOBAL;
			stgMedium.pUnkForRelease = NULL;
			FORMATETC etc = {(CLIPFORMAT)CF_TEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
			pDataSource->SetData(&etc/*(CLIPFORMAT)_oleData.cfObjectDescriptor*/, &stgMedium, TRUE);
		}

		// add CF_OBJECTDESCRIPTOR
		GetObjectDescriptorData(NULL/*lpOffset*/, NULL/*lpSize*/, &stgMedium);
		{
			FORMATETC etc = {(CLIPFORMAT)_oleData.cfObjectDescriptor, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
			pDataSource->SetData(&etc/*(CLIPFORMAT)_oleData.cfObjectDescriptor*/, &stgMedium, TRUE);
		}
	}

	void COleServerItem::GetEmbedSourceData(LPSTGMEDIUM lpStgMedium)
	{
		//ASSERT_VALID(this);
		//ASSERT(AfxIsValidAddress(lpStgMedium, sizeof(STGMEDIUM)));

		LPLOCKBYTES lpLockBytes;
		SCODE sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
		if (sc != S_OK)
			;//AfxThrowOleException(sc);
		ASSERT(lpLockBytes != NULL);

		LPSTORAGE lpStorage;
		sc = ::StgCreateDocfileOnILockBytes(lpLockBytes,
			STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 0, &lpStorage);
		if (sc != S_OK)
		{
			VERIFY(lpLockBytes->Release() == 0);
			//AfxThrowOleException(sc);
		}
		ASSERT(lpStorage != NULL);

		LPOLESTR usertype;
		m_spOleObject->GetUserType(USERCLASSTYPE_FULL, &usertype);

//Now save the data to the storage.
		//WriteClassStg(lpStorage, CLSID_PDDocument);
		//WriteFmtUserTypeStg(lpStorage, CF_TEXT, usertype);          

		/*
		// setup for save copy as
		COleServerDoc* pDoc = GetDocument();
		pDoc->m_bSameAsLoad = FALSE;
		pDoc->m_bRemember = FALSE;

		TRY
		{
			OnSaveEmbedding(lpStorage);
			pDoc->CommitItems(FALSE);
		}
		CATCH_ALL(e)
		{
			// release storage and lock bytes
			VERIFY(lpStorage->Release() == 0);
			VERIFY(lpLockBytes->Release() == 0);
			pDoc->m_bSameAsLoad = TRUE;
			pDoc->m_bRemember = TRUE;
			THROW_LAST();
		}
		END_CATCH_ALL
		*/

		//pDoc->m_bSameAsLoad = TRUE;
		//pDoc->m_bRemember = TRUE;
		lpLockBytes->Release();

		// add it to the data source
		lpStgMedium->tymed = TYMED_ISTORAGE;
		lpStgMedium->pstg = lpStorage;
		lpStgMedium->pUnkForRelease = NULL;
	}

	void COleServerItem::GetObjectDescriptorData(
		LPPOINT lpOffset, LPSIZE lpSize, LPSTGMEDIUM lpStgMedium)
	{
		/*
		ASSERT_VALID(this);
		ASSERT(AfxIsValidAddress(lpStgMedium, sizeof(STGMEDIUM)));
		ASSERT(lpOffset == NULL ||
			AfxIsValidAddress(lpOffset, sizeof(POINT), FALSE));
			*/

		LPOLEOBJECT lpOleObject = m_spOleObject;//GetOleObject();
		ASSERT(lpOleObject != NULL);

		// get the object descriptor for the IOleObject
		POINTL pointl = { 0, 0 };
		if (lpOffset != NULL)
		{
			CSize ptOffset(lpOffset->x, lpOffset->y);
			((CDC*)NULL)->DPtoHIMETRIC(&ptOffset);
			pointl.x = ptOffset.cx;
			pointl.y = ptOffset.cy;
		}
		SIZEL sizel;
		if (lpSize != NULL)
		{
			sizel.cx = lpSize->cx;
			sizel.cy = lpSize->cy;
			((CDC*)NULL)->DPtoHIMETRIC(&sizel);
		}
		else
		{
			sizel.cx = 0;
			sizel.cy = 0;
		}

	//	AddRef();
		//InterlockedIncrement(&m_dwRef);  // protect against destruction during this call
		HGLOBAL hGlobal = _AfxOleGetObjectDescriptorData(
			lpOleObject, NULL, DVASPECT_CONTENT, pointl, &sizel);
		//InterlockedDecrement(&m_dwRef);
	//	Release();

		if (hGlobal == NULL)
			;//AfxThrowMemoryException();

		// setup the STGMEDIUM
		lpStgMedium->tymed = TYMED_HGLOBAL;
		lpStgMedium->hGlobal = hGlobal;
		lpStgMedium->pUnkForRelease = NULL;
	}

};
