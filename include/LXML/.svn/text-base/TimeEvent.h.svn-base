#ifndef w3c_TimeEvent_h
#define w3c_TimeEvent_h

namespace System
{
namespace Web
{

class WEBEXT TimeEvent : public Event
{
public:
	CTOR TimeEvent();

	int get_detail();
	Web::IAbstractView* get_view();
	void initTimeEvent(StringIn typeArg, Web::IAbstractView* viewArg, int detailArg);

protected:

	Web::IAbstractView* m_view;
	int m_detail;
};

}	// w3c
}

#endif // w3c_TimeEvent_h
