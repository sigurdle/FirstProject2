#ifndef __EXMLVIEWGROUP_H_
#define __EXMLVIEWGROUP_H_

#include "resource.h"       // main symbols

#include "LXMLEditorApp.h"	// TODO Remove

namespace System
{
class CEDocument;

namespace LXmlEdit
{

class CEXMLLayoutView;
class CEXMLDocument;

class CTGNode;
class CTGElement;
class CElement;

class CEXMLViewGroup : 

	public UI::CViewGroup,

#if 0
	public ILElementBehaviorFactory,
#endif

//	public IEViewGroup,
	public IECSSSelection,
#if 0
	public IUIActivatable,
#endif
	public UI::ProcessTargetCommands	// ILDOMEventListener
{
public:
	CTOR CEXMLViewGroup();

	~CEXMLViewGroup()
	{
		TRACE("~CEXMLViewGroup\n");
	}

	int FinalConstruct();
	void FinalRelease();

	CEXMLDocument* m_pDocument;

	Web::Element* m_outerElement;
	ITextBookmark* m_outerElementTextBookmark;

	CEXMLLayoutView* m_layoutView;

// protected: TODO
	Array<IESelectedElement*> m_targetElements;
	IESelectedElement* m_pActiveElement;

//	IEElement* m_svgActiveContainer;
	CTGNode* m_pActiveTimeGraphNode;
	CTGElement* m_pActiveTimeGraphElement;
	CElement* m_pActiveSelection;

	System::StringW* m_colorEditing;

	double m_currentSelectionColorRed;
	double m_currentSelectionColorGreen;
	double m_currentSelectionColorBlue;
	double m_currentSelectionColorAlpha;

protected:

	Web::CSSStyleDeclaration* m_currentSelectionStyle;

public:
	Element* m_activeReferenceElement;	// (for example an <ellipse> that has a mask or clip-path
	Element* m_activeReferencedElement; // (for example a <mask> or <clipPath>

	ErrorCode ReferenceBack();

	void Close();

	void DragOut(UI::CView* view, UI::CUIDockBar* dockBar);

	void SetDocument(CEXMLDocument* pDocument);
//	void UpdateFrameTitle();

	void UpdateTitles(int n);

	// Am I using this??
	void GetCompoundPathTargetElements(Array<CESVGPathElement*>& layers);

	void SetCurrentSelectionCSSStyle();
	bool SetCurrentSelectionCSSProperty(System::StringW* propertyName);

	void ApplyCurrentSelectionCSSProperty(System::StringW* propertyName);

	void SetCurrentSelectionColor();
	void ApplyCurrentSelectionColor();

// CViewGroup
	virtual int OnGroupActivate(bool bActive);
	virtual int OnGroupClose();

protected:
	void RemoveElementAsTarget(IESelectedElement* pElement);
	void AddElementAsTarget(IESelectedElement* pElement);
	void DeselectElement(IESelectedElement* pElement);
	void DeselectAll();
	void ApplyCurrentSelectionColorToSelectedElements();

public:

DECLARE_CMD_MAP(CEXMLViewGroup)

	long OnWindowNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSelectBack(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnDeselectAll(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnInsertForeignObject(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFilePlace(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSmilInsertVideo(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertVideo(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertAudio(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewViewport(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewSwitch(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnObjectGroup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectUngroup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnObjectGroupUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnObjectUngroupUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnObjectCompoundPathMake(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectCompoundPathRelease(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnObjectCompoundPathMakeUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnObjectCompoundPathReleaseUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnObjectTransformClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectTransformConsolidate(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnObjectTransformClearUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnObjectTransformConsolidateUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnObjectArrangeFront(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectArrangeForward(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectArrangeBack(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectArrangeBackward(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnObjectArrangeHigherUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnObjectArrangeLowerUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnNewWindowOnActiveElement(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnWindowSplit(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// IEXMLViewGroup
public:
	CEDocument* get_eDocument();
	CEXMLDocument* get_eXMLDocument();
	IESelectedElement* GetSelectedElementN(long n);
	long GetSelectedCount() const;
	IESelectedElement* ActivateElement(Element* element, long nFlags);
	ErrorCode GetActiveSelectedElement(/*[out,retval]*/ IESelectedElement* *pVal);
	ErrorCode GetSelectedElement(Element* pElement, IESelectedElement* *pVal);

//	STDMETHOD(setRGBAValue)(long red, long green, long blue, long alpha);

//	IECSSSelection
	ErrorCode GetCurrentSelectionCSSStyle(Web::CSSStyleDeclaration* *pVal);
	ErrorCode ApplyCurrentSelectionCSSStyle();

// ILDOMEventListener
	void handleEvent(System::Event* evt);

// IUIActivatable
//	STDMETHOD(OnActivate)(IUIActiveManager *uiManager);
//	STDMETHOD(OnDeactivate)(IUIActiveManager *uiManager);
// ICommandTarget
//	STDMETHOD(OnCmdMsg)(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled);

// ILElementBehaviorFactory
//	STDMETHOD(FindBehavior)(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILElementBehaviorSite* pSite, ILElementBehavior** ppBehavior);
};

}	// LXmlEdit
}

#endif // __EXMLVIEWGROUP_H_
