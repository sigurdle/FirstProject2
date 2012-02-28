#ifndef __LDTDELEMENT_H
#define __LDTDELEMENT_H

//#include "LDTDNodeImpl.h"
//#include "LDOMEventTargetImpl.h"

namespace System
{
namespace Web
{

class CASDTDElement;
class CDTDParser;
class CCPChoiceSeq;

class WEBEXT CLDTDElement
//	public CDTDObjectImpl,
//	public EventTarget,
//	public ILDTDElement
{
public:
	CLDTDElement();
	~CLDTDElement();

	CDTDParser* m_pDTDDocument;

	String m_ns;
	String m_name;

	CCPChoiceSeq* m_pCPChoiceSeq;
	ASContentModelType m_contentType;
//	bool m_isPCDataOnly;

#if 0
	CASDTDElement* m_pASElement;
#endif

	/*
BEGIN_COM_MAP(CLDTDElement)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDTDObject)
	COM_INTERFACE_ENTRY(ILDTDElement)
	COM_INTERFACE_ENTRY(ILDOMEventTarget)
	COM_INTERFACE_ENTRY(CLDOMNodeImplImpl)
END_COM_MAP()
*/

public:
	String get_name() const;
	void set_name(StringIn newVal);
//	LDOMNodeType get_nodeType() const;
};

}	// w3c
}

#endif
