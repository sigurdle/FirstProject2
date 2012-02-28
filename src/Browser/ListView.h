#ifndef __ListView_h__
#define __ListView_h__

namespace System
{

class ViewOfCollection;

class ListView : public UI::Control
{
public:
	CTOR ListView(System::Property* pProperty, System::Object* itemVisual)
	{
		m_view = NULL;
		m_pProperty = pProperty;
		m_itemVisual = itemVisual;
	}

//	void handleEvent(System::Event* evt);

	ViewOfCollection* m_view;
	System::Property* m_pProperty;
	System::Object* m_itemVisual;
};

}

#endif // __ListView_h__
