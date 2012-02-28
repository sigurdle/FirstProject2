// ECSSViewGroup.h : Declaration of the CECSSViewGroup

#ifndef __ECSSVIEWGROUP_H_
#define __ECSSVIEWGROUP_H_

#include "resource.h"       // main symbols

#include "LXMLEditorApp.h"	// TODO Remove

namespace System
{
namespace LXmlEdit
{

class CECSSDocument;

class CECSSViewGroup : 
public UI::CViewGroup,
	public IECSSSelection,
//	public IUIActivatable,
public UI::ProcessTargetCommands	// ILDOMEventListener
//	public ILDOMEventListener,
//	public CProxy_IEXMLViewGroupEvents< CECSSViewGroup >,
//	public IConnectionPointContainerImpl<CECSSViewGroup>
{
public:
	CECSSViewGroup()
	{
		m_pDocument = NULL;
		m_pActiveElement = NULL;
	}

	~CECSSViewGroup()
	{
		TRACE("~CECSSViewGroup\n");
	}

	int FinalConstruct();
	void FinalRelease();

	IESelectedRule* m_pActiveElement;
	Array<IESelectedRule*> m_targetElements;

protected:
	Web::CSSStyleDeclaration* m_currentSelectionStyle;

public:
	CECSSDocument* m_pDocument;

//	CComQIPtr<ILDOMElement> m_outerElement;
//	CComPtr<ITextBookmark> m_outerElementTextBookmark;

	void SetCurrentSelectionCSSProperties();
	//BOOL SetCurrentSelectionCSSProperty(BSTR propertyName);

	void RemoveElementAsTarget(IESelectedRule* pElement);

	void UpdateTitles(int n);

// CViewGroup
	int OnActivate(bool bActive);
	int OnClose();

DECLARE_CMD_MAP(CECSSViewGroup)

	long OnWindowNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// IECSSViewGroup
public:
	ErrorCode get_eDocument(/*[out,retval]*/ IEDocument* *pVal);

	ErrorCode ActivateElement(/*[in]*/ Web::CSSRule* element, /*[in]*/ long nFlags, /*[out,retval]*/ IESelectedRule* *pVal);
	ErrorCode GetSelectedElement(Web::CSSRule* element, IESelectedRule* *pVal);
	ErrorCode GetSelectedCount(long* pVal);

//	IECSSSelection
	ErrorCode GetCurrentSelectionCSSStyle(Web::ICSSStyleDeclaration* *pVal);
	ErrorCode ApplyCurrentSelectionCSSStyle();

// IUIActivatable
//	ErrorCode(OnActivate)(IUIActiveManager *uiManager);
//	ErrorCode(OnDeactivate)(IUIActiveManager *uiManager);
// ICommandTarget
//	ErrorCode(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

}	// LXmlEdit
}

#endif //__ECSSVIEWGROUP_H_
