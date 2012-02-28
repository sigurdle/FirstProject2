#ifndef __LXMLDOCUMENTVIEW_H
#define __LXMLDOCUMENTVIEW_H

#if 0

namespace LXML
{

class CPElementBase;
class CPSVGFontElement;
class CHTMLWindow;
class CXMLDocumentView;

class WEBEXT CFontDataFile
{
public:
	CTOR CFontDataFile();
	~CFontDataFile();

	sysstring m_url;

	CHTMLWindow* m_pWindow;	// Need CSS stuff, so the document isn't enough
};

class WEBEXT CFontFamilyDef
{
public:
	CTOR CFontFamilyDef();

	WCHAR m_name[64];
	int m_refcount;
	CXMLDocumentView* m_pView;

	CFontDataFile* m_dataFile;
	CPSVGFontElement* m_pSVGFontElement;	// SVG Font
};

class CPSVGFontElement;

class WEBEXT CFontDef
{
protected:
	int m_refcount;

#if _WINDOWS
//	HFONT m_hFont;
//	HFONT m_hFontHinted;
	LDraw::Font* m_gdipFont;
#endif

//	CHTMLWindow* m_pWindow; (Obtain through m_pFamily instead)

public:
//	CPSVGFontElement* m_pSVGFontElement;	// SVG Font

#if _WINDOWS
	CFontFamilyDef* m_pFamily;
#endif
	double m_size;
	int m_weight;
	int m_style;

	double m_descent;
#if _WINDOWS
	TEXTMETRIC m_tm;
#endif

	CFontDef();
	~CFontDef();

	int AddRef()
	{
		m_refcount++;
		return m_refcount;
	}

#if _WINDOWS
//	HFONT GetHFONT();
//	HFONT GetHintedHFONT();
	LDraw::Font* GetGdipFont();
#endif

	friend CXMLDocumentView;
};

class WEBEXT CXMLDocumentView :
	public IUnknown//ILPresentation//CLDOMViewCSSImpl<CXMLDocumentView>
{
public:
	CTOR CXMLDocumentView()
	{
		m_pRootElement = NULL;
	}

	~CXMLDocumentView()
	{
		ASSERT(m_fonts.GetSize() == 0);
		ASSERT(m_fontFamilies.GetSize() == 0);
	}

#if 0
	CComPtr<ILDOMDocument> m_document;
#endif
	CPElementBase* m_pRootElement;

protected:
	CArray<CFontDataFile*,CFontDataFile*> m_fontDataFiles;
	CArray<CFontFamilyDef*,CFontFamilyDef*> m_fontFamilies;
	CArray<CFontDef*,CFontDef*> m_fonts;

public:
	CFontDataFile* AddFontDataFile(const sysstring& url);
	CFontFamilyDef* AddFontFamily(const sysstring& family);
	CFontDef* AddFontDef(const sysstring& family, double size, int weight, int style);

	void ReleaseFontDef(CFontDef* pFontDef);
	void ReleaseFontFamilyDef(CFontFamilyDef* pFontFamilyDef);

#if 0
	virtual CPElement* CreateElement(ILDOMElement* element);
	virtual HRESULT SetDocument(ILDOMDocument* pDocument);
#endif

#if 0
	STDMETHOD(GetViewNode)(/*[in]*/ ILDOMNode* node, /*[out, retval]*/ ILViewNode* *pVal);
	STDMETHOD(GetAnonymousNode)(/*[in]*/ ILDOMElement* element, /*[out, retval]*/ ILDOMNode* *pVal);
#endif
};

#if 0
class WEBEXT CHTMLDocumentView :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CXMLDocumentView/*,
	public CNotifyGetImpl<CHTMLDocumentView>*/
{
public:
//	virtual CPElement* CreateElement(ILDOMElement* element);

#if 0
	virtual HRESULT SetDocument(ILDOMDocument* pDocument);
#endif

	void DoneParsing();

	CHTMLDocumentView()
	{
		m_pWindow = NULL;
	}

	CHTMLWindow* m_pWindow;	// TODO remove

	/*
	void CalcDims(CPElement* pNode);
	*/

	void Free();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHTMLDocumentView)
	//COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(ILPresentation)
END_COM_MAP()

/*
// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID);
	*/
};
#endif

}	// LXML

#endif

#endif