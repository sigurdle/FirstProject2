class CPDFFont
{
public:
	CPDFCosDict* m_cos;

	CPDFFont()
	{
		m_cos = NULL;
	}
};

class CPDFPage
{
protected:
	CPDFEContent* m_pContent;

public:
	CPDFCosDict* m_cos;

	CPDFDoc* m_pDoc;

	CPDFCosStream* m_pCosContents;
	CPDFCosDict* m_pCosResources;

	RectD m_mediaBox;

public:
	CPDFPage()
	{
		m_pDoc = NULL;
		m_cos = NULL;

		m_pCosContents = NULL;
		m_pCosResources = NULL;

		m_pContent = NULL;
	}

	STDMETHODIMP AcquirePDEContent(CPDFEContent* *pVal);
	STDMETHODIMP ReleasePDEContent();
	STDMETHODIMP GetCosResources(CPDFCosDict* *pVal);
	STDMETHODIMP AddCosResource(char* resType, char* resName, CPDFCosObject *resObj);
};

class CPDFDoc
{
public:
	CArray<CPDFPage*,CPDFPage*> m_pages;
	CArray<CPDFFont*,CPDFFont*> m_fonts;

public:
	CPDFCosDoc* m_cos;

	CPDFDoc()
	{
		m_cos = new CPDFCosDoc;
	}

	~CPDFDoc()
	{
		for (int i = 0; i < m_pages.GetSize(); i++)
		{
			delete m_pages[i];
		}
		m_pages.RemoveAll();

		delete m_cos;
		m_cos = NULL;
	}

	CPDFFont* GetOrCreateFont(PDEFontAttrs* fattrs);

	STDMETHODIMP CreatePage(int afterPageNum, RectD mediaBox, CPDFPage* *pVal);
	STDMETHODIMP Create();
	STDMETHODIMP Save(TCHAR* filename);
	STDMETHODIMP SetInfo(BSTR binfoKey, BSTR bvalue);
};
