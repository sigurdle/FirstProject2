#ifndef w3c_DOMDOCUMENTEVENT_h
#define w3c_DOMDOCUMENTEVENT_h

namespace System
{
namespace Web
{

//class Event;

class WEBEXT DocumentEvent
	//public ILDOMDocumentEvent
{
public:
	virtual Event* createEvent(StringIn name);
	virtual IEventListenerGroup* createEventListenerGroup();
};

}	// w3c
}

#endif
