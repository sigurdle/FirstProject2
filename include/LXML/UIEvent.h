#ifndef w3c_UIEvent_h
#define w3c_UIEvent_h

namespace System
{
namespace Web
{

class WEBEXT UIEvent : public Event
{
public:
	CTOR UIEvent();

	IAbstractView* get_view() const;
	void initUIEvent(StringIn typeArg, bool canBubbleArg, bool cancelableArg, IAbstractView* viewArg, int detailArg);
	int get_detail() const;

protected:

	IAbstractView* m_view;
	int m_detail;
};

}	// w3c
}

#endif // w3c_UIEvent_h
