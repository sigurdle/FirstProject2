#ifndef w3c_MouseEvent_h
#define w3c_MouseEvent_h

namespace System
{
namespace Web
{

class WEBEXT MouseEvent : public UIEvent
{
public:
	CTOR MouseEvent();
	~MouseEvent();

	int get_screenX() const;
	int get_screenY() const;

	int get_clientX() const;
	int get_clientY() const;

	bool get_ctrlKey() const;
	bool get_shiftKey() const;
	bool get_altKey() const;
	bool get_metaKey() const;
	int get_button() const;

	EventTarget* get_relatedTarget() const;

	void initMouseEvent(StringIn typeArg, bool canBubbleArg, bool cancelableArg, IAbstractView* viewArg, int detailArg, int screenXArg, int screenYArg, int clientXArg, int clientYArg, bool ctrlKeyArg, bool shiftKeyArg, bool altKeyArg, bool metaKeyArg, unsigned short buttonArg, EventTarget* relatedTargetArg);

protected:

	EventTarget* m_relatedTarget;
	int m_screenX;
	int m_screenY;
	int m_clientX;
	int m_clientY;
	bool m_ctrlKey;
	bool m_shiftKey;
	bool m_altKey;
	int m_button;
};

}	// w3c
}

#endif // w3c_MouseEvent_h
