#pragma once

#include "resource.h"

#include "../Browser/Item.h"
#include "../LFC/db.h"

namespace System
{

class MailAccount : public System::Object, public IItem
{
public:
	void GetNewMail(ITable* pTable);

	long m_ID;
	System::StringA* m_server;
	System::StringA* m_username;
	System::StringA* m_password;

	virtual FieldData* GetFieldData(int ind)
	{
/*		switch (ind)
		{
		case 0:
			return new IntegerField;
		}
		*/
		return NULL;
	}

	virtual UI::UIElement* GetFieldUI(int ind)
	{
		return NULL;
	}
};

class MailReaderFrame : public CLXUIWindow
{
public:
	MailReaderFrame();

//	TreeControl* m_list;
//	CUIEdit* m_text;

	ChildWindowContainer* pCanvas;

	void ViewTable(Table pTable);

protected:
	virtual void handleEvent(System::Event* evt);
};

}
