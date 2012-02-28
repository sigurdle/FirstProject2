#ifndef Web_ProcessingInstructionStylesheet_h
#define Web_ProcessingInstructionStylesheet_h

#include "Node.h"
#include "DOMEventTargetImpl.h"
#include "LinkStyleImpl.h"

namespace System
{
namespace Web
{

class WEBEXT CPIAttr : public Object
{
public:
	String m_name;
	String m_value;
};

class WEBEXT CPIAttributes
{
public:
	~CPIAttributes();

	void RemoveAll();

	CPIAttr* GetAttr(StringIn name);
	String GetAttrValue(StringIn name);

	vector<CPIAttr*> m_items;
};

class WEBEXT ProcessingInstructionStylesheet : 
	public ChildNode,
	public EventTarget,
	public LinkStyleExternalImpl//<ProcessingInstructionStylesheet>,

//	CNotifyGetImpl<ProcessingInstructionStylesheet>,
//	CNotifySendImpl<ProcessingInstructionStylesheet>
{
public:
	CTOR ProcessingInstructionStylesheet();

	void LoadStyleSheet();

// EventTarget
	virtual bool dispatchEvent2(Event* evt, /*[in]*/ bool bCapture);
#if 0
	{
		CComBSTR type;
		evt->get_type(&type);

		LDOMEventPhaseType phase;
		evt->get_eventPhase(&phase);
		if (phase == AT_TARGET)
		{
		// This element is added to the document tree
			if (!wcscmp(type, OLESTR("DOMNodeInsertedIntoDocument")))
			{
				LoadStyleSheet();

				if (m_styleSheet)
				{
					CComQIPtr<ILDocumentStyle, &IID_ILDocumentStyle> documentStyle = m_ownerDocument;
					if (documentStyle)
					{
						CComPtr<ILStyleSheetList> styleSheetList;
						documentStyle->get_styleSheets(&styleSheetList);

						styleSheetList->append(m_styleSheet);
					}
				}
			}
		// This element is removed from the document tree
			else if (!wcscmp(type, OLESTR("DOMNodeRemovedFromDocument")))
			{
				if (m_styleSheet)
				{
					ATLASSERT(0);
					// TODO remove stylesheet from document
				}
			}
		}

		return CLDOMEventTargetImpl<ProcessingInstructionStylesheet>::dispatchEvent2(evt, bCapture, doDefault);
	}
#endif

	String get_data() const;
	void set_data(StringIn data);
	String get_target() const;
	virtual NodeType get_nodeType() const;
	virtual Node* cloneNodeExport(Document* ownerDocument, bool deep) const;

protected:

	String m_target;

/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, Object* targetObject, Object* immtargetObject, long dispID)
	{
		LoadStyleSheet();

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
*/

	String m_data;
	CPIAttributes m_attributes;
};

}	// Web
}

#endif // Web_ProcessingInstructionStylesheet_h
