#ifndef __WebDocumentImpl_h__
#define __WebDocumentImpl_h__

namespace System
{

class CEDocument// : public _ObjectImpl
{
public:
	System::StringW* m_pathName;
	System::StringW* m_fileTitle;
	long m_modified;

	CTOR CEDocument()
	{
		m_modified = 0;
	}

	//CComQIPtr<ITextData> m_textDocument;

// New
	ErrorCode NewDocument()
	{
	//	m_textDocument->put_data(SysAllocString(L""));
		m_pathName = WSTR("");

		return Success;
	}

// Loading
	ErrorCode LoadDocument(System::StringW* pathName)
	{
		/*
		VARIANT_BOOL success;
		m_textDocument->load(pathName, &success);

		if (!success)
			return E_FAIL;

		m_pathName = pathName;
		m_fileTitle = PathFindFileName(m_pathName);
		*/

		return Success;
	}

#if 0
	HRESULT LoadDocument(IStream* stm)
	{
		/*

		CComQIPtr<IPersistStream> persistStream = m_textDocument;

		HRESULT hr = persistStream->Load(stm);

		if (FAILED(hr))
			return hr;

		m_pathName = L"";//pathName;	// TODO
		m_fileTitle = PathFindFileName(m_pathName);
		*/

		return S_OK;
	}

	STDMETHODIMP LoadDocumentByteArray(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success)
	{
		return 0;//m_textDocument->loadByteArray(dataArray, success);
	}
#endif

// Saving
	ErrorCode SaveDocument(const System::StringW* pathName)
	{
		ErrorCode hr = 0;/*m_textDocument->save(pathName);
		if (SUCCEEDED(hr))
		{
			m_pathName = pathName;
			m_fileTitle = PathFindFileName(m_pathName);
		}
		*/

		return hr;
	}

	ErrorCode Save()
	{
		return SaveDocument(m_pathName);
	}

//
	long  GetModified()
	{
		return m_modified;
	}

//
	IUndoManager* get_undoManager()
	{
		return NULL;
	}

	void ShowViews()
	{
		ASSERT(0);
	}

	System::StringW* get_filePath() const
	{
		return m_pathName;
	}

	void put_filePath(System::StringW* newVal)
	{
		m_pathName = newVal;
	}

	/*
	STDMETHODIMP get_textDocument(ITextData **pVal)
	{
		*pVal = m_textDocument;
		(*pVal)->AddRef();

		return S_OK;
	}

	STDMETHODIMP put_textDocument(ITextData *newVal)
	{
		m_textDocument = newVal;
		return S_OK;
	}
	*/
};

}

#endif // __WebDocumentImpl_h__
