#ifndef Web_Window_h
#define Web_Window_h

//#include "PNode.h"
//#include "PElementBase.h"

namespace System
{
namespace Web
{

interface IPersistControl
{
	virtual void Load(StringIn uri) = 0;
};

/*
class ProgressEvent : public System::Event
{
public:
	double m_progress;
};

class WEBEXT LinkEvent : public System::Event
{
public:
	System::StringW* m_href;
	System::StringW* m_target;
};
*/

class PElementBase;

class CHTMLWindowSite
{
public:
	virtual ErrorCode OnLink(StringIn href, StringIn target) = 0;
};

class MessageSink

#if _WIN32
 : public MSWindows::WindowImpl//<MessageSink>
#endif
{
};

class WEBEXT ConnectionWindow : public Gui::Control
{
public:
	CTOR ConnectionWindow();

//	UI::DockPanel* m_Panel;
};

class WEBEXT Navigator : public Object
{
//interface NavigatorID
	String get_appName();
	String get_appVersion();
	String get_platform()
	{
#ifndef __LERSTAD__
		static ImmutableString<char> str("Win32");
#endif
		return &str; 
		//"MacIntel", "Win32", "FreeBSD i386", "WebTV OS".
	}

	String get_userAgent()
	{
		return s_userAgent;
	}

// interface NavigatorOnLine;
	bool get_onLine();

//	interface NavigatorContentUtils;
// interface NavigatorStorageUtils;

	static void SetUserAgentName(StringIn userAgent);
	static String s_userAgent;
};

class WEBEXT History : public Object
{
public:
	int get_length();

	void go(int delta);
	void go();
	void back();
	void forward();
	void pushState(Object* data, StringIn title);
	void pushState(Object* data, StringIn title, StringIn url);
	void clearState();

protected:

	vector<Object*> m_items;
	CHTMLWindow* m_pWindow;	// Or browsing context
};

interface ILocation
{
	virtual ILocation& operator = (StringIn href) = 0;

	virtual String get_href() = 0;
	virtual void set_href(StringIn href) = 0;

	 /*
    // pieces of the URI, per the generic URI syntax
    attribute dom::DOMString hash;
    attribute dom::DOMString host;
    attribute dom::DOMString hostname;
    attribute dom::DOMString pathname;
    attribute dom::DOMString port;
    attribute dom::DOMString protocol;
    attribute dom::DOMString search;

    void assign(in dom::DOMString url);
    void replace(in dom::DOMString url);
    void reload();

    dom::DOMString toString();
	 */
};

class WEBEXT BarProp : public Object
{
public:

//	CTOR BarProp(

	virtual bool get_visible();
	virtual void set_visible(bool value);

//	CHTMLWindow* 
};

interface IWindow : public IViewCSS	// IAbstractView
{
	virtual ILocation* get_location() = 0;

	virtual BarProp* get_locationbar() = 0;
	virtual BarProp* get_menubar() = 0;
	virtual BarProp* get_personalbar() = 0;
	virtual BarProp* get_scrollbars() = 0;
	virtual BarProp* get_statusbar() = 0;
	virtual BarProp* get_toolbar() = 0;
};

/*
class WEBEXT Clock : public Object
{
public:
	ElementTime* m_elementTime;
};

class WEBEXT ClockGroup : public Clock
{
public:
};

class WEBEXT AnimationClock : public Clock
{
public:

	GetElementTime()
};
*/

class WEBEXT CHTMLWindow : public DispatcherObject,//Gui::FrameworkElement,
	public IWindow,
	public IEventTarget
//	public IPersistControl,
//	public IDownloadCallback
//	public IBindCallback

//	public CMessageMap,

#if 0	// Had this ??
	public CLDOMViewCSSImpl<CXMLDocumentView>
#endif

//////////////////

//	public IBindHost,
//	public IHttpNegotiate,
//
{
public:
	CTOR CHTMLWindow();
	~CHTMLWindow();

	// IAbstractView
	virtual Document* get_document() override;
	virtual String get_mediaMode() override;

	// IViewCSS
	virtual ICSSStyleDeclaration* getComputedStyle(Web::Element* elt, StringIn pseudoElt) override;

	// IWindow
	virtual ILocation* get_location() override;
	virtual History* get_history();

	virtual BarProp* get_locationbar() override;
	virtual BarProp* get_menubar() override;
	virtual BarProp* get_personalbar() override;
	virtual BarProp* get_scrollbars() override;
	virtual BarProp* get_statusbar() override;
	virtual BarProp* get_toolbar() override;

	virtual Navigator* get_navigator()
	{
		return &m_navigator;
	}

	Navigator m_navigator;

	void alert(StringIn str);

	virtual void Load(StringIn uri);

//	virtual ErrorCode OnProgress(HttpRequest* request);
	virtual ErrorCode OnObjectAvailable(Object* /*object*/, StringIn url)
	{
	//	Load(url);
		return Success;
	}

	virtual ErrorCode OnDataAvailable(size_t cbSize, IO::Stream* stream);
	virtual ErrorCode OnDone();

// IEventTarget
	virtual void addEventListener(StringIn type, Object* listener, bool useCapture);
	virtual void removeEventListener(StringIn type, Object* listener, bool useCapture);
	virtual bool dispatchEvent(Event* evt);
	virtual void addEventListenerNS(StringIn namespaceURI, StringIn type, Object* listener, bool useCapture, IEventListenerGroup* evtGroup);
	virtual void removeEventListenerNS(StringIn namespaceURI, StringIn type, Object* listener, bool useCapture);
	virtual bool willTriggerNS(StringIn namespaceURI, StringIn type);
	virtual bool hasEventListenerNS(StringIn namespaceURI, StringIn type);

	/*
	void AddColorProfileElement(BSTR name, ILSVGColorProfileElement* element)
	{
		CColorProfile* pColorProfile = new CColorProfile;
		pColorProfile->m_name = name;
		pColorProfile->m_element = element;

		m_colorProfiles.Add(pColorProfile);
	}
	*/

	CColorProfile* GetColorProfileByName(StringIn name);
#if 0
	{
		for (int i = 0; i < m_colorProfiles.GetSize(); i++)
		{
			if (!wcscmp(m_colorProfiles[i]->m_name, name))
			{
				return m_colorProfiles[i];
			}
		}

		return NULL;
	}
#endif

#if 0
	void ScreenToClient(CPoint* ppoint);
	HDC GetDC();
	void ReleaseDC(HDC hDC);
#endif

#if 0
	void InvalidateRect(LPCRECT rect);
	void SetCapture();
	void ReleaseCapture();
#endif

//	ErrorCode HitTestSVGElement(PSVGElement* pElement, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* matrix, double mousex, double mousey, CPElement* *pVal, PNode **pNode, long *pOffset);

//	void svgGetScreenCTM(PSVGElement* pSVGElement, ILSVGMatrix* *pVal);
	gm::matrix3f svgGetScreenCTM(PElementBase/*Web::PSVGElement*/ * pSVGElement);

	void Flow();

	void Free();

	void ShowCursor();
	void HideCursor();
	void ToggleCursor();
	void DrawCursor(Gui::RenderContext* pGraphics, PNode* pItem, int offset, bool bStippled = false);

//	void MoveCursorLeft();
//	void MoveCursorRight();

	gm::matrix3f GetViewMatrix();

	long GotoLocation(StringIn url);	// TODO, am I using this?

#if 0
	long SetElement(ILDOMElement* pElement);
#endif

	long SetURLHistory();	// TODO, am I using this?

	void OnSize();

#if 0
	void RemovingElement(PElement* pPElement);
#endif

#if 0
	void PrepareScripting();
	void AddNamedElements(IActiveScript* script, ILDOMElement* parent);
#endif

	virtual void OnButtonDown(UINT nFlags, gm::PointD screenpt, gm::PointD clientpt, int iButton, bool bDblClk/*, CHTMFrameNode** pFrame*/);
	virtual void OnMouseMove(UINT nFlags, gm::PointD screenpt, gm::PointD clienpt);
	virtual void OnButtonUp(UINT nFlags, gm::PointD screenpt, gm::PointD clientpt, int iButton);

	virtual void OnContextMenu(HWND hWnd, gm::PointD point);

	bool OnSetCursor(gm::PointI point);

	bool CursorPositionFromPoint(gm::PointI point, PNode** pItem, long* offset);

//	virtual void handleEvent(System::Event* evt);

	virtual void OnMouseDown(Gui::MouseButtonEventArgs* args);
	virtual void OnMouseUp(Gui::MouseButtonEventArgs* args);
	virtual void OnMouseMove(Gui::MouseEventArgs* args);

	virtual void OnRenderMy(Gui::RenderContext* pGraphics);
	virtual gm::SizeD ArrangeOverride(gm::SizeD finalSize);
	void OnRender(Gui::RenderContext* pGraphics);

//	virtual void RenderRetained(Gui::ManagedRetainedRenderContext renderContext) override;

	//
//	virtual void DrawCaret(HDC hDC);

#if 0
	virtual void PositionFrames();
#endif

	void OnKeyDown(Gui::RoutedEventArgs* evt);
	void OnKeyUp(int nKey, int lKeyData);
	void OnChar(Gui::RoutedEventArgs* evt);
#if 0//_WINDOWS
	DWORD OnDragOver(LPDATAOBJECT pDataObject, DWORD dwKeyState, POINTL point);
	BOOL OnDrop(LPDATAOBJECT pDataObject, DWORD dropEffect, POINTL point);
#endif

	void ExtendIt(Node* container, int offset, int bShift);

	void TypeText(StringIn text);
	ErrorCode Delete(/*[in]*/ long Unit, /*[in]*/ long Count, /*[out,retval]*/ long* pDelta);
	ErrorCode MoveRight(long Unit, long Count, long Extend, long *pDelta);
	ErrorCode MoveLeft(long Unit, long Count, long Extend, long *pDelta);

#if 0
// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID);
#endif

/////////

	void scrollIntoView(PElementBase *pElement);
	void scrollIntoView(CHTMBoxItem* pBox);

	bool get_showMarkup();
	void set_showMarkup(bool newVal);
#if 0
	STDMETHOD(scrollIntoView)(ILDOMElement* element);
#endif
//	STDMETHOD(svgGetFilterRegion)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGRect* *pVal);
//	STDMETHOD(svgAddGlyphToSegList)(/*[in]*/ ILSVGTextContentElement* element, /*[in]*/ long glyphnum, /*[in]*/ ILSVGPathSegList* seglist);
//	STDMETHOD(svgGetGlyphTextContentElement)(/*[in]*/ ILSVGTextContentElement* element, /*[in]*/ long glyphnum, /*[out,retval]*/ ILSVGTextContentElement* *pVal);
//	STDMETHOD(svgGetNumberOfGlyphs)(/*[in]*/ ILSVGTextContentElement* element, /*[out,retval]*/ long* pVal);
//	STDMETHOD(svgGetGlyphSegList)(/*[in]*/ ILSVGTextContentElement* element, /*[in]*/ long glyphnum, /*[out,retval]*/ ILSVGPathSegList* *pVal);
//	STDMETHOD(svgGetPositionOfGlyph)(/*[in]*/ ILSVGTextContentElement* element, /*[in]*/ long glyphnum, /*[out,retval]*/ ILSVGPoint* *pVal);
#if 0
	STDMETHOD(LocateCursor)(/*[in]*/ ILDOMNode* container, /*[in]*/ long offset);
#endif
	bool get_noscroll();
	void set_noscroll(bool newVal);

// Extensions
	double get_magnify();
	void set_magnify(double newVal);
	double get_currentTranslateX();
	double get_currentTranslateY();
	double get_contentHeight();
	double get_contentWidth();
//	STDMETHOD(setInnerSize)(/*[in]*/ long width, /*[in]*/ long height);
	void DrawToBuffer(/*[in]*/ long width, /*[in]*/ long height, /*[in]*/ long rowbytes, /*[in]*/ long pixelFormat, /*[in]*/ void* buffer);
//	STDMETHOD(svgDrawElementToBuffer)(/*[in]*/ ILSVGElement* element, /*[in]*/ ILSVGMatrix* matrix, /*[in]*/ long width, /*[in]*/ long height, /*[in]*/ long rowbytes, /*[in]*/ long pixelFormat, /*[in]*/ void* buffer);
	void ZoomToRect(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height, /*[in]*/ bool bAnimate);
//	STDMETHOD(svgGetBBox)(/*[in]*/ILSVGElement* element, /*[out,retval]*/ ILSVGRect** pVal);
//	STDMETHOD(svgGetRBBox)(/*[in]*/ILSVGElement* element, /*[out,retval]*/ ILSVGRect** pVal);
//	STDMETHOD(svgGetScreenCTM)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal);
//	STDMETHOD(svgGetScreenCTM2)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal);
//	STDMETHOD(svgGetScreenNCTM)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal);
//	STDMETHOD(svgGetScreenNCTM2)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal);
//	STDMETHOD(svgGetViewTransformMatrix)(/*[out,retval]*/ ILSVGMatrix* *pVal);
//	STDMETHOD(svgGetElementViewBoxMatrix)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal);
//	STDMETHOD(svgGetScreenBBox)(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGRect* *pVal);
//	STDMETHOD(SVGHitTest)(/*[in]*/ ILSVGElement* element, /*[in]*/ long pointerEvents, /*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ bool* pVal);
//	STDMETHOD(SVGCheckGeometryIntersection)(ILSVGElement* element, ILSVGRect* rect, bool* pVal);
#if 0
	STDMETHOD(setActiveElement)(ILDOMElement* element);
#endif

//	STDMETHOD(GetMatrix)(/*[out,retval]*/ ILSVGMatrix* *pVal);
//	STDMETHOD(SetMatrix)(/*[in]*/ ILSVGMatrix* matrix);
	void setCurrentTranslate(/*[in]*/ double x, /*[in]*/ double y);

#if 0
	STDMETHOD(get_selection)(/*[out, retval]*/ ILDOMRange* *pVal);
#endif

//	STDMETHOD(GetOleView)(/*[out,retval]*/ ILHTMLActiveView* *pVal);
#if 0
	STDMETHOD(DrawToHdc)(/*[in]*/ HDC hDC, /*[in]*/ ILDOMElement* element, /*[in]*/ double magnify);
	STDMETHOD(DrawToHdc4)(/*[in]*/ HDC hDC, /*[in]*/ ILDOMElement* element, /*[in]*/ double magnify);
#endif

#if 0
	CLHTMLDocumentView* m_pUI;
	CLHTMLActiveDocument* m_pActiveDocument;
#endif

	double GetFinalMagnify();

	Gui::UIElement* m_ownerVisual;

	Document* m_document;
	History* m_history;

	CHTMFlowBlockContext* m_pC;

//	MessageSink m_layoutMessageSink;

#if WIN32
	HANDLE m_hLayoutEvent;
#else
	long m_layoutSigBit;
#endif
#if WIN32
	HANDLE m_hLayoutBeginEvent;
#else
	long m_parentSigBit;
#endif
#if WIN32
	HANDLE m_hLayoutDoneEvent;
#else
	Task* m_parentTask;
#endif
#if WIN32
	HANDLE m_hLayoutThread;
#else
	struct Task* m_hLayoutThread;
#endif
	DWORD m_dwLayoutThreadId;
	//bool m_bLayoutComplete;
	CriticalSection m_crit;

	LONGLONG m_nbytes;

//	bool m_bEOF;
	//HANDLE m_hEvent;
	//ISequentialByteStream* m_stream;

	CHTMLWindowSite* m_pSite;

//	LDraw::RectI m_client;

	bool m_bAlt;
	gm::RectI m_zoomRect;

	gm::PointD m_startpt;
	gm::PointD m_oldpt;

#if 0
	CPHTMLFrameElement* m_pFrame;	// ??
#endif

	bool m_bShowCursor;

//	int m_lockPaint;

	PNode* m_initContainer;
	long m_initOffset;

	PNode* m_curContainer;
	long m_curOffset;

/////// TODO remove (or not)???
	PNode* m_cursorItem;
	long m_cursorOffset;

	PNode* m_dragOverItem;
	long m_dragOverOffset;

	PNode* m_startSelItem;
	long m_startSelOffset;

	PNode* m_endSelItem;
	long m_endSelOffset;

	// TODO ??
	JSVM::StackFrame* m_pScriptGlobal;

#if 0
	CComPtr<ILDOMElement> m_activeElement;	// TODO? Remove this, use below instead?
#endif
	PElementBase* m_pPElementActive;	// Could there be many of these?
	PElementBase* m_pPElementFocus;	// Only one of this
	PElementBase* m_pPElementHover;	// Only one of this

	PElementBase* m_pHitElement;	// Can I Use some of the above

//////////

	vector<ElementTime*> m_timelines;

	double m_magnify;
	double m_currentTranslateX;
	double m_currentTranslateY;

//	Web::CLSVGMatrix* m_pMatrix;

#if 0 //_WINDOWS
	LPBITMAPINFO m_lpbmi;
#endif

	Range* m_range;
	int m_dragging;
	bool m_bShowMarkup;

#if 0
	LDraw::Font* m_pMarkupFont;
#endif
	vector<CColorProfile*> m_colorProfiles;

#if 0
	CComObject<CHTMLScriptSite>* m_spScriptSite;
	CComObject<CLHTMLWindow>* m_pHTMLWindowImpl;
#endif
//	CComObject<CLHTMLDialog>* m_pHTMLDialogImpl;

#if 0
	IUnknown* m_pContainer;
#endif

// Reference back to frame that contains this UI frame

#if 0
	CComPtr<ILDOMElement> m_element;	// The outer element in the document
#endif

#if 0
	ILDOMEvent* m_eventObj;
#endif

#if 0
	COleClientItem* m_pOCItemCapture;	// ActiveX object that has mouse capture
#endif

	list<PElementBase*> m_recalcBoundsList;

	int m_nhit;

	PElementBase* m_pElementCapture;	// Element with capture

#if 0
// content is HTML frameset document
	CPHTMLFrameSetElement* m_pFrameSet;
#endif

// content is xml/html
// Generic pointer to root CPElement for all xml document types
	PElementBase* m_htmTree;

// document is XML/(X)HTML styled with CSS
#if 0
	CHTMPElement* m_pHTMElement;
#endif

	/*
// document is SVG
	Web::PSVGElement* m_pSVGElement;
	*/


#if 0
// document is SMIL
	CPSMILElement* m_pSMILElement;
	CPSMILLayoutElement* m_pSMILLayoutElement;

// document is XSL-FO
	CFODisplay* m_pFODisplay;
#endif

#if 0
//
	CComObject<CCoClientObject>* m_scrollX;
	CComObject<CCoClientObject>* m_scrollY;
#endif

	bool m_noscroll;

	Graphics::Bitmap* m_hBrokenImage;	// TODO, Image not bitmap

//	CStatusBarCtrl	m_sizeGrip;

//	CArray<CHistoryEntry*,CHistoryEntry*>	m_history;
//	int m_currentHistory;

};

}	// Web
}	// System

#endif	// Web_Window_h
