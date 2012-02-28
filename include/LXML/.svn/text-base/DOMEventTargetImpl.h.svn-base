#ifndef __LDOMEVENTTARGETIMPL_H_
#define __LDOMEVENTTARGETIMPL_H_

namespace System
{
namespace Web
{

class WEBEXT CLDOMEventTargetImpl : public IEventTarget
{
public:

	CTOR CLDOMEventTargetImpl();
	~CLDOMEventTargetImpl();

	void addEventListener(StringIn type, Object* listener, bool useCapture);
	void removeEventListener(StringIn type, Object* listener, bool useCapture);

  // Introduced in DOM Level 3:
	void addEventListenerNS(
			StringIn namespaceURI,
			StringIn type,
			Object* listener, 
			bool useCapture, 
			IEventListenerGroup* evtGroup);

	void removeEventListenerNS(
			/*[in]*/ StringIn namespaceURI,
			/*[in]*/ StringIn type,
			/*[in]*/ Object* listener, 
			/*[in]*/ bool useCapture/*, 
			IEventListenerGroup* evtGroup*/)
	{
		ASSERT(0);
	}

	virtual bool willTriggerNS(StringIn namespaceURI, StringIn type);

	virtual bool hasEventListenerNS(StringIn namespaceURI, StringIn type);

///////
	void capturePhase(Event* evt, bool* pdoDefault);
	void bubblePhase(Event* evt, bool* pdoDefault);

	virtual bool dispatchEvent2(Event* evt, bool bCapture);
	virtual EventTarget* GetParentEventTarget();

protected:

	class CListener : public Object
	{
	public:
		CTOR CListener();
		~CListener();

		String m_type;
		Object* m_listener;	// Keep reference
		bool m_useCapture;
	};

	list<CListener*> m_listeners;
};

class WEBEXT EventTarget : public CLDOMEventTargetImpl
{
public:
	~EventTarget();

	virtual bool dispatchEvent(Event* evt);
};

}	// w3c
}

#endif //__LDOMEVENTTARGETIMPL_H_
