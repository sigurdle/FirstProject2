#ifndef __System_Event_h__
#define __System_Event_h__

namespace System
{

#if 0
class LFCEXT Event : public Object
{
public:
	CTOR Event();
	~Event();

	EventTargetImpl* get_currentTarget() const;
	void set_currentTarget(EventTargetImpl* newVal);
	EventTargetImpl* get_target() const;
	void set_target(EventTargetImpl* newVal);
	EventPhaseType get_eventPhase() const;
	void stopPropagation();
	void preventDefault();
	void InitEvent(StringW* eventTypeArg, bool canBubbleArg, bool cancelableArg);
	bool get_cancelable() const;
	bool get_bubbles() const;
	StringW* get_type() const;
	bool isDefaultPrevented() const;
	bool isPropagationStopped() const;

protected:

	friend class EventTargetImpl;

	StringW* m_type;
	StringW* m_namespaceURI;
	EventTargetImpl* m_target;
	EventTargetImpl* m_currentTarget;
	EventPhaseType m_eventPhase;

	bool m_bPreventDefault : 1;
	bool m_cancelable : 1;
	bool m_bubbles : 1;
	bool m_bStopPropagation : 1;
};
#endif

}	// System

#endif // __System_Event_h__
