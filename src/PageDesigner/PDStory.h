#pragma once

class CPDDocument;
class CObjectMap;
class CPDContentText;
class CNode;
class CElement;
class CPDStory;
template <class IBase> class CPDObjectTextImpl;

class CTextContext
{
public:
	Gdiplus::Graphics* m_pGraphics;

	Gdiplus::Font* m_pFont;
	Gdiplus::Brush* m_pFillBrush;
	Gdiplus::Pen* m_pStrokePen;
//	CComPtr<IPDBrush> m_fillBrush;
//	CComPtr<IPDBrush> m_strokeBrush;

	CTextContext()
	{
		m_pGraphics = NULL;
		m_pFont = NULL;
		m_pFillBrush = NULL;
		m_pStrokePen = NULL;
	}

	virtual CTextContext* SetupElement(CElement* pElement) = 0;
	virtual void SetdownElement(CElement* pElement, CTextContext* _pC) = 0;
	virtual BOOL PlaceWord(CNode* node, int start, _bstr_t data) = 0;
	virtual BOOL PlaceObject(IPDObject* object) = 0;
};

class CStoryFlowContext
{
public:
	CPDObjectTextImpl<IPDObjectText>* m_pContentText;

	ILDOMNode* m_hitNode;
	long m_hitOffset;

	BOOL PlaceWord(CTextContext* pC, CNode* pNode, int i, _bstr_t worddata);
	BOOL PlaceTextNode(CTextContext* pC, CNode* pNode);
	BOOL DistributeElement(CElement* pElement, CTextContext* pC);

	CStoryFlowContext()
	{
		m_pContentText = NULL;
		m_hitNode = NULL;
		m_hitOffset = 0;
	}
};

class CNode
{
public:
	ILDOMNode* m_node;
	CElement* m_parent;

	CNode(ILDOMNode* node)
	{
		m_node = node;
		m_parent = NULL;
	}

	virtual ~CNode()
	{
	}

	virtual CNode* FindNode(ILDOMNode* node)
	{
		if (m_node == node) return this;
		return NULL;
	}
};

class CElement : public CNode
{
public:
	CArray<CNode*,CNode*> m_children;

	CPDStory* m_story;

	_bstr_t m_fontFamily;
	double m_fontSize;
	Gdiplus::Color m_strokeColor;
	Gdiplus::Color m_fillColor;
	double m_strokeWidth;

	Gdiplus::Font* m_pOldFont;
	Gdiplus::Brush* m_pOldFillBrush;
	Gdiplus::Pen* m_pOldStrokePen;

	CElement(ILDOMNode* node) : CNode(node)
	{
		m_story = NULL;

		m_fontFamily = L"";
		m_fontSize = 0;

		m_strokeWidth = 0;
		m_fillColor = Gdiplus::Color(255, 0,0,0);
		m_strokeColor = Gdiplus::Color(255, 255,0,0);

		m_pOldFont = NULL;
		m_pOldFillBrush = NULL;
		m_pOldStrokePen = NULL;
	}

	virtual ~CElement()
	{
		for (int i = m_children.GetSize()-1; i >= 0; i--)
		{
			delete m_children[i];
			m_children.RemoveAt(i);
		}
	}

	void Build();

	virtual CNode* FindNode(ILDOMNode* node)
	{
		if (m_node == node) return this;

		for (int i = 0; i < m_children.GetSize(); i++)
		{
			CNode* pNode = m_children[i]->FindNode(node);
			if (pNode)
				return pNode;
		}

		return NULL;
	}

	_bstr_t GetAttribute(BSTR attName);
	void SetupFont(CTextContext* pContext);
	void SetdownFont(CTextContext* pContext);
//	BOOL DistributeElement(CTextContext* pContext);
};

class CPDTextFont;
class CPDTextPara;

class ATL_NO_VTABLE CPDStory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDStory,
	public CNotifySendImpl<CPDStory>
//	public IDispEventImpl<1, CPDStory, &DIID__IDOMDocumentContainerEvents, &LIBID_SVGLib, 1, 0>
{
public:
	CPDStory()
	{
		m_document = NULL;
		m_textContents = NULL;

		m_firstTextThread = NULL;
		m_lastTextThread = NULL;

		m_pElement = NULL;

		m_inlineObjects = NULL;

		m_uniqId = GUID_NULL;
	}

	~CPDStory()
	{
		if (m_pElement)
		{
			delete m_pElement;
			m_pElement = NULL;
		}
	}

	int FinalConstruct();
	void FinalRelease();

	CPDDocument* m_document;

	GUID m_uniqId;

	CComObject<CObjectMap>* m_inlineObjects;

	CComPtr<ILDOMDocument> m_textdocument;

//	CComPtr<IDOMDocumentContainer> m_textdocumentcnt;

	CComObject<CObjectMap>* m_textContents;
	CPDObjectTextImpl<IPDObjectText>* m_firstTextThread;
	CPDObjectTextImpl<IPDObjectText>* m_lastTextThread;

	CElement* m_pElement;

	void DistributeStory();
	void DistributeContentsSpreads();
	HRESULT insertNode(IPDObjectText* node, IPDObjectText* before);

	BOOL _extractFont(ILDOMRange* m_range, CPDTextFont* pTextFont, ILDOMNode* node, /*IDOMNode* parent,*/ int& hitStart);
	BOOL _extractPara(ILDOMRange* m_range, CPDTextPara* pTextPara, ILDOMNode* node, /*IDOMNode* parent,*/ int& hitStart);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDStory)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDStory)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

#if 0
BEGIN_SINK_MAP(CPDStory)
   SINK_ENTRY_EX(1, DIID__IDOMDocumentContainerEvents, /*dispid*/1, cnt_insertedNode)
   SINK_ENTRY_EX(1, DIID__IDOMDocumentContainerEvents, /*dispid*/2, cnt_beforeRemovedNode)
   SINK_ENTRY_EX(1, DIID__IDOMDocumentContainerEvents, /*dispid*/3, cnt_afterRemovedNode)
   SINK_ENTRY_EX(1, DIID__IDOMDocumentContainerEvents, /*dispid*/4, cnt_changedAttribute)
   SINK_ENTRY_EX(1, DIID__IDOMDocumentContainerEvents, /*dispid*/5, cnt_changedTextContentNode)
   SINK_ENTRY_EX(1, DIID__IDOMDocumentContainerEvents, /*dispid*/6, cnt_setDocument)
   SINK_ENTRY_EX(1, DIID__IDOMDocumentContainerEvents, /*dispid*/7, cnt_beforesetDocument)
END_SINK_MAP()

	HRESULT __stdcall cnt_insertedNode(IDOMNode* node);
	HRESULT __stdcall cnt_beforeRemovedNode(IDOMNode* node);
	HRESULT __stdcall cnt_afterRemovedNode(IDOMNode* node);
	HRESULT __stdcall cnt_changedAttribute(IDOMNode* node, BSTR attrName, short changeType, BSTR prevValue);
	HRESULT __stdcall cnt_changedTextContentNode(IDOMNode* node, BSTR oldvalue);
	HRESULT __stdcall cnt_setDocument(IDOMDocument* document);
	HRESULT __stdcall cnt_beforesetDocument();
#endif

// IPDStory
public:
	STDMETHOD(NewSelection)(/*[out,retval]*/ IPDTextSelection* *pVal);

	STDMETHOD(GetObjectTextFromRangePosition)(/*[in]*/ ILDOMNode* container, /*[in]*/ long offset, /*[out,retval]*/ IPDObjectText* *pVal);
	STDMETHOD(NewRange)(/*[out,retval]*/ IPDTextRange* *pVal);
	STDMETHOD(SetTextPara)(/*[in]*/ IPDTextRange* range, /*[in]*/ IPDTextPara* textPara);
	STDMETHOD(GetTextPara)(/*[in]*/ IPDTextRange* range, /*[out,retval]*/ IPDTextPara* *pVal);
	STDMETHOD(SetTextFont)(/*[in]*/ IPDTextRange* range, /*[in]*/ IPDTextFont* textFont);
	STDMETHOD(GetTextFont)(/*[in]*/ IPDTextRange* range, /*[out,retval]*/ IPDTextFont* *pVal);
	STDMETHOD(getInlineObjectById)(/*[in]*/ GUID guid, /*[out,retval]*/ IPDObject* *pVal);
	STDMETHOD(appendInlineObject)(/*[in]*/ IPDObject* object);
	STDMETHOD(get_inlineObjects)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(removeTextThread)(/*[in]*/ IPDObjectText* node);
	STDMETHOD(insertTextThreadBefore)(/*[in]*/ IPDObjectText* node, /*[in]*/ IPDObjectText* before);
	STDMETHOD(get_lastTextThread)(/*[out, retval]*/ IPDObjectText* *pVal);
	STDMETHOD(get_firstTextThread)(/*[out, retval]*/ IPDObjectText* *pVal);
	STDMETHOD(appendTextThread)(/*[in]*/ IPDObjectText* node);
	STDMETHOD(get_textContents)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(get_textDocument)(/*[out, retval]*/ ILDOMDocument* *pVal);
	STDMETHOD(put_textDocument)(/*[in]*/ ILDOMDocument* newVal);
//	STDMETHOD(loadXML)(/*[in]*/ ILDOMNode* node);
//	STDMETHOD(saveAsXML)(/*[in]*/ ILDOMDocument* document, /*[in]*/ ILDOMNode* node, BOOL saveId);
};
