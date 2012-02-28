#ifndef Web_Event_h
#define Web_Event_h

namespace System
{
namespace Web
{

enum DOMEventPhaseType
{
	UNKNOWN_PHASE = 0,
	CAPTURING_PHASE = 1,
	AT_TARGET = 2,
	BUBBLING_PHASE = 3
};

class WEBEXT Event : public Object
{
public:
	CTOR Event();
	virtual ~Event();

	void initEvent(StringIn eventTypeArg, bool canBubbleArg, bool cancelableArg);

	EventTarget* get_currentTarget();
	void set_currentTarget(EventTarget* newVal);
	EventTarget* get_target();
	void set_target(EventTarget* newVal);
	DOMEventPhaseType get_eventPhase();
	String get_type();
	void set_eventPhase(DOMEventPhaseType newVal);
	void stopPropagation();
	void preventDefault();
	bool get_cancelable();
	bool get_bubbles();
	bool isDefaultPrevented();
	bool isPropagationStopped();

protected:

	friend class EventTarget;
	friend class CLDOMEventTargetImpl;

	String m_namespaceURI;
	String m_type;
	EventTarget* m_target;
	DOMEventPhaseType m_eventPhase;
	bool m_bStopPropagation;
	bool m_bPreventDefault;
	bool m_cancelable;
	bool m_bubbles;
};

}	// Web
}	// System

#endif // Web_Event_h
