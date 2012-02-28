#include "stdafx.h"

#if WIN32

/*
#define Array var
#include <windows.h>
#include <psapi.h>
#undef Array
*/
#endif

#include "MailReaderFrame.h"

#include "../LXUI/Socket.h"
#include "../LXUI/TextDocument.h"

#include <time.h>

//#pragma comment(lib, "ws2_32.lib")	// TODO remove

class POP3Client : public AsyncSocket
{
public:
	POP3Client()
	{
//		m_state = STATE_CONNECT;
	}

	/*
	enum State
	{
		STATE_CONNECT,
		STATE_USER,
		STATE_PASS,
		STATE_LIST,
	};

	State m_state;
	std::string m_data;
	*/

	StringA ReadLine()
	{
		StringA str;

		while (1)
		{
			char c;
			Read(&c, 1);
			if (c == '\r')
			{
				char c2;
				Read(&c2, 1);
				if (c2 == '\n')
				{
					break;
				}
				else
				{
					if (str.length() == 512)
						throw -1;
					str += c;

					if (str.length() == 512)
						throw -1;
					str += c2;
				}
			}
			else
			{
				if (str.length() == 512)
					throw -1;
				str += c;
			}
		}

		TRACE("%s\n", str.c_str());
		return str;
	}

#if 0
	virtual void OnConnect()
	{
		TRACE("OnConnect\n");
	}

	virtual void OnClose()
	{
		TRACE("OnClose\n");
	}

	

	virtual void OnRead()
	{
		TRACE("OnRead\n");

		char buf[512];
		int nRead = Receive(buf, 1);
		m_data += buf;

	//	::MessageBox(NULL, buf, NULL, MB_OK);
		for (int i = 0; i < nRead; i++)
		{
			TRACE("%c", buf[i]);
		}

		const char* end = strstr(m_data.c_str(), "\r\n");
		if (end)
		{
			//std::string response = std::string(m_data, end - m_data.c_str());
			//m_response = end + 2;
		}

#if 0
		if (m_state == STATE_CONNECT)
		{
			if (!strncmp(m_response.c_str(), "+OK", 3))
			{
				// The server has greeted us

				// Let's identify ourselves
				m_state = STATE_USER;
				m_response = "";

			}
		}
		else if (m_state == STATE_USER)
		{
			if (!strncmp(m_response.c_str(), "+OK", 3))
			{
				// Username has been accepted

				// Send the password
				m_state = STATE_PASS;
				m_response = "";

		//		char* msg = "PASS 04bi1u6\r\n";
		//		send(m_socket, msg, strlen(msg), 0);
			}
			/*
			else
			{
				char* msg = "QUIT\r\n";
				send(m_socket, msg, strlen(msg), 0);
			}
			*/
		}
		else if (m_state == STATE_PASS)
		{
			if (!strncmp(m_response.c_str(), "+OK", 3))
			{
				// Password has been accepted
				m_state = STATE_LIST;
				m_response = "";
#if 0

				char* msg = "LIST\r\n";
				send(m_socket, msg, strlen(msg), 0);
#endif

			}
			/*
			else
			{
				char* msg = "QUIT\r\n";
				send(m_socket, msg, strlen(msg), 0);
			}
			*/
		}
		/*
		else if (m_state == STATE_LIST)
		{
			if (!strncmp(m_response.c_str(), "+OK", 3))
			{
				if (strstr(m_response.c_str(), "\r\n."))
				{
					char* msg = "QUIT\r\n";
					send(m_socket, msg, strlen(msg), 0);
				}
			}
		}
		else
		{
			char* msg = "QUIT\r\n";
			send(m_socket, msg, strlen(msg), 0);
		}
		*/
#endif
	}

	virtual void OnWrite()
	{
		TRACE("OnWrite\n");

		if (m_state == STATE_USER)
		{
			char* msg = "USER sigler\r\n"
							"PASS 04bi1u6\r\n";

			Send(msg, strlen(msg));
		}
		else if (m_state == STATE_PASS)
		{
			char* msg = "PASS 04bi1u6\r\n";
			Send(msg, strlen(msg));
		}
		else if (m_state == STATE_LIST)
		{
			char* msg = "QUIT\r\n";
			Send(msg, strlen(msg));
		}
#if 0

		char* msg = "LIST\r\n";

		int nSent = send(m_socket, msg, strlen(msg), 0);
#endif
	}
#endif
};

class NNTPClient : public AsyncSocket
{
public:

	StringA ReadLine()
	{
		StringA str;

		while (1)
		{
			char c;
			Read(&c, 1);
			if (c == '\r')
			{
				char c2;
				Read(&c2, 1);
				if (c2 == '\n')
				{
					break;
				}
				else
				{
					if (str.length() == 512)
						throw -1;
					str += c;

					if (str.length() == 512)
						throw -1;
					str += c2;
				}
			}
			else
			{
				if (str.length() == 512)
					throw -1;
				str += c;
			}
		}

		TRACE("%s\n", str.c_str());
		return str;
	}

#if 0
	virtual void OnConnect(int nErrorCode)
	{
		TRACE("OnConnect\n");
	}

	virtual void OnClose(int nErrorCode)
	{
		TRACE("OnClose\n");
	}

	virtual void OnReceive(int nErrorCode)
	{
		TRACE("OnRead\n");

		char buf[512];
		int nRead = Receive(buf, 512);

	//	::MessageBox(NULL, buf, NULL, MB_OK);
		for (int i = 0; i < nRead; i++)
		{
			TRACE("%c", buf[i]);
		}
	}

	virtual void OnSend(int nErrorCode)
	{
		TRACE("OnWrite\n");

		char* msg = "LIST\r\n";

		int nSent = send(m_socket, msg, strlen(msg), 0);
	}
#endif
};


void MailAccount::GetNewMail(ITable* pTable)
{
	int port = 110;
	POP3Client* pSocket = new POP3Client;
	pSocket->Create();
	pSocket->Connect(m_server.c_str(), port);

	StringA greeting = pSocket->ReadLine();
	if (strncmp(greeting.c_str(), "+OK", 3))
		throw -1;

	{
		char msg[512];
		sprintf(msg, "USER %s\r\n", m_username.c_str());
		pSocket->Write(msg, strlen(msg));
		StringA response = pSocket->ReadLine();
		if (strncmp(response.c_str(), "+OK", 3))
			throw -1;
	}

	{
		char msg[512];
		sprintf(msg, "PASS %s\r\n", m_password.c_str());
		pSocket->Write(msg, strlen(msg));
		StringA response = pSocket->ReadLine();
		if (strncmp(response.c_str(), "+OK", 3))
			throw -1;
	}

	CArray<int, int> message_numbers;
	{
		char* msg = "LIST\r\n";
		pSocket->Write(msg, strlen(msg));
		StringA response = pSocket->ReadLine();
		if (strncmp(response.c_str(), "+OK", 3))
			throw -1;
		while (1)
		{
			StringA line = pSocket->ReadLine();
			if (!strcmp(line.c_str(), "."))
			{
				break;
			}

			int message_number;
			int message_size;

			sscanf(line.c_str(), "%d %d", &message_number, &message_size);
			message_numbers.Add(message_number);

			TRACE("%s\n", line.c_str());
		}

	//	FILE* fp_text = fopen("C:\\mail_text", "a+b");
	//	FILE* fp_index = fopen("C:\\mail_index", "a+b");

		for (int i = 0; i < message_numbers.size(); i++)
		{
			IRecord* pMessage = pTable->NewRecord();

			pMessage->GetField((int)0)->SetValue((long)0);//m_ID;
			pMessage->GetField(5)->SetValue((long)0);
			pMessage->GetField(6)->SetValue(time(NULL));
			pMessage->GetField(7)->SetValue(m_ID);

			{
				char msg[256];
				sprintf(msg, "RETR %d\r\n", message_numbers[i]);
				TRACE(msg);
				pSocket->Write(msg, strlen(msg));
				StringA response = pSocket->ReadLine();
				if (strncmp(response.c_str(), "+OK", 3))
					throw -1;
			}

			// Read the message
			StringA lines;

			while (1)
			{
				StringA line = pSocket->ReadLine();
				if (!strcmp(line.c_str(), "."))	// Multiline message ends with '.\r\n'
				{
					break;
				}

				lines += line;
				lines += "\r\n";
			}

			const char *p = lines.c_str();

			while (*p)
			{
				if (p[0] == '\r' && p[1] == '\n')	// End of headers
					break;

				// field name
				StringA fieldName;
				while (*p)
				{
					if (isspace(*p) || *p == ':')
						break;

					fieldName += *p;
					p++;
				}
				while (isspace(*p)) p++;
				if (*p++ != ':') throw -1;
				while (isspace(*p)) p++;

				// field body
				StringA fieldBody;
				while (*p)
				{
					if (p[0] == '\r' && p[1] == '\n')
					{
						if (p[2] == '\t' || p[2] == ' ')	// continuation on next line
						{
							p += 3;
						}
						else
						{
							p += 2;
							break;	// End of this field
						}
					}
					else
					{
						fieldBody += *p;
						p++;
					}
				}

				if (!stricmp(fieldName.c_str(), "Subject"))
				{
					pMessage->GetField(1)->SetData(fieldBody.c_str(), fieldBody.length());
				}
				else if (!stricmp(fieldName.c_str(), "From"))
				{
					pMessage->GetField(2)->SetData(fieldBody.c_str(), fieldBody.length());
				}
			}

			pMessage->GetField(3)->SetData(lines.c_str(), p - lines.c_str());

			if (p[0] != '\r' || p[1] != '\n')
				throw -1;
			p += 2;

			pMessage->GetField(4)->SetData(p, lines.length() - (p - lines.c_str()));

			pMessage->Write();

			// The message isn't actually deleted from the server until we issue a QUIT command
			{
				char msg[256];
				sprintf(msg, "DELE %d\r\n", message_numbers[i]);
				TRACE(msg);
				pSocket->Write(msg, strlen(msg));
				StringA response = pSocket->ReadLine();
				if (strncmp(response.c_str(), "+OK", 3))
					throw -1;
			}
		}

		/*
		fclose(fp_index);
		fclose(fp_text);
		*/
	}

	{
		char* msg = "QUIT\r\n";
		pSocket->Write(msg, strlen(msg));
		StringA response = pSocket->ReadLine();
		if (strncmp(response.c_str(), "+OK", 3))
			throw -1;
	}
}

class NewsAccount : public _ObjectImpl, public IItem
{
public:
	NewsAccount()
	{
		m_pSocket = NULL;
	}

	Table m_list;

	StringA m_server;

	void Connect();
	void GetNewsGroups();

	void GetList();
	void Quit();

protected:
	NNTPClient* m_pSocket;
};

void NewsAccount::Quit()
{
	char* request = "QUIT\r\n";
	m_pSocket->Write(request, strlen(request));
	StringA response = m_pSocket->ReadLine();
}

void NewsAccount::GetList()
{
	char* request = "LIST\r\n";
	m_pSocket->Write(request, strlen(request));
	StringA response = m_pSocket->ReadLine();

	while (1)
	{
		StringA line = m_pSocket->ReadLine();
		if (!strcmp(line.c_str(), "."))
		{
			break;
		}

		char group[1024];
		int last;
		int first;
		char p;
		sscanf(line.c_str(), "%s", group, &last, &first, &p);

		TRACE("%s\n", group);

		Record pRecord = m_list.NewRecord();

		pRecord.get_Fields()[1].SetData(group);

		pRecord.Update();
	}
}

void NewsAccount::Connect()
{
	int port = 119;
	m_pSocket = new NNTPClient;
	m_pSocket->Create();
	m_pSocket->Connect(m_server.c_str(), port);

	{
		StringA response = m_pSocket->ReadLine();
	}
};


CDocumentWorkspace m_xmlDocumentWorkspace;

class MailMessage : public CViewGroup
{
public:
	virtual int OnActivate(bool bActive)
	{
		return S_OK;
	}
	virtual int OnClose()
	{
		return S_OK;
	}
};

class TableView : public Control
{
public:
	Table m_table;
	TreeControl* m_list;
	ChildWindowContainer* m_Canvas;

protected:
	virtual void handleEvent(System::Event* evt);

	void OnContextMenu(MouseEvent* evt);
};

void TableView::OnContextMenu(MouseEvent* evt)
{
	evt->stopPropagation();
//	TextEdit::OnLButtonUp();

	CLXUIMenuElement* menu = new CLXUIMenuElement();
	menu->SetRParent(this);
	menu->SetOwnerWindow(get_OwnerWindow());

	int nfields = m_table.GetFieldCount();
	for (int i = 0; i < nfields; i++)
	{
		menu->AddItem(new TextString(m_table.GetField(i)->GetName()), 100+i);
	}

	/*
	menu->AddSeparator();
	menu->AddItem(new TextString(OLESTR("Insert/Remove Breakpoint")), ID_DEBUG_TOGGLEBREAKPOINT);
	*/

	menu->GetMenuPopup()->Popup(menu, LDraw::Point(evt->get_ScreenX(), evt->get_ScreenY()));
}

void TableView::handleEvent(System::Event* evt)
{
	ASSERT(0);
#if 0
	sysstring type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (type == OLESTR("command"))
		{
			CommandInvokeEvent* cmdEvt = dynamic_cast<CommandInvokeEvent*>(evt);

			int ncolumn = cmdEvt->get_Command() - 100;
			Visual* column = m_list->m_treeHeader->m_columns[ncolumn];
			column->put_Visibility(column->get_Visibility()==Collapsed? Visible: Collapsed);
		}
		else if (type == OLESTR("contextmenu"))
		{
			evt->stopPropagation();
			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			OnContextMenu(mouseEvt);
		}
		else if (type == OLESTR("ItemStateChanging"))
		{
			evt->stopPropagation();

			int index = *dynamic_cast<IntObject*>(dynamic_cast<TreeItem*>(evt->get_target())->m_itemData);

			Record pRecord = m_table[index];

			CViewGroup* pMessage = new MailMessage;

			Field Subject = pRecord.get_Fields()[1];
			Field Headers = pRecord.get_Fields()[3];
			Field Content = pRecord.get_Fields()[4];

			ScrollViewer* pScroller = new ScrollViewer;
			{
				TextEdit* textView = new TextEdit;
				textView->put_textDocument(new TextDocument());
				textView->SetText(
					ConvertA2S((char*)Headers.GetData(), Headers.GetSize()) +
					OLESTR("\n") +
					ConvertA2S((char*)Content.GetData(), Content.GetSize()));

				pScroller->put_Content(textView);
			}
			pScroller->SetOwnerWindow(get_OwnerWindow());	// TODO remove

			pMessage->m_views.Add(pScroller);

			m_xmlDocumentWorkspace.Create(m_Canvas, pMessage);

			for (int i = 0; i < pMessage->m_sheets.GetSize(); i++)
			{
				CViewSheet* pViewSheet = pMessage->m_sheets[i];

				sysstring str;
				try
				{
					str = ConvertA2S((char*)Subject.GetData(), Subject.GetSize());
				}
				catch(int)
				{
					str = OLESTR("(Error)");
				}

				pViewSheet->m_tabElement->set_TextContent(str);
			}
		}
	}
#endif
}

/////////////////////////////////////////////////////////
// MailReaderFrame

MailReaderFrame::MailReaderFrame()
{
	{
#if 0
		{
			Table accounts;
			accounts.Open("C:\\accounts", "a+b");
			accounts.Append();

			accounts.AddField(OLESTR("ID"), FieldDef::FTyp_Long);
			accounts.AddField(OLESTR("Server"), FieldDef::FTyp_VarString);
			accounts.AddField(OLESTR("Username"), FieldDef::FTyp_VarString);
			accounts.AddField(OLESTR("Password"), FieldDef::FTyp_VarString);

			Record* pRecord = accounts.NewRecord();
			pRecord->m_fields[0]->u.int32 = 1;
			pRecord->m_fields[1]->SetData("pop.bredband.no");
			pRecord->m_fields[2]->SetData("sigler");
			pRecord->m_fields[3]->SetData("04bi1u6");

			pRecord->Write(&accounts);

			accounts.Close();
		}
#endif

#if 0
		{
			Table accounts;
			accounts.Open("C:\\news_accounts", "a+b");
			accounts.Append();

			accounts.AddField(OLESTR("ID"), FieldDef::FTyp_Long);
			accounts.AddField(OLESTR("Server"), FieldDef::FTyp_VarString);
		//	accounts.AddField(OLESTR("Username"), FieldDef::FTyp_VarString);
		//	accounts.AddField(OLESTR("Password"), FieldDef::FTyp_VarString);

			Record* pRecord = accounts.NewRecord();
			pRecord->m_fields[0]->u.int32 = 1;
			pRecord->m_fields[1]->SetData("freetext.usenetserver.com");
		//	pRecord->m_fields[2]->SetData("sigler");
		//	pRecord->m_fields[3]->SetData("04bi1u6");

			pRecord->Write(&accounts);

			accounts.Close();
		}
#endif

#if 0
		{
			Table* pTable = new Table;
			pTable->AddField(OLESTR("ID"), FieldDef::FTyp_Long);
			pTable->AddField(OLESTR("Subject"), FieldDef::FTyp_VarString);
			pTable->AddField(OLESTR("From"), FieldDef::FTyp_VarString);
			pTable->AddField(OLESTR("Headers"), FieldDef::FTyp_VarString);
			pTable->AddField(OLESTR("Content"), FieldDef::FTyp_VarString);
			pTable->AddField(OLESTR("Sent"), FieldDef::FTyp_ShortDate);
			pTable->AddField(OLESTR("Received"), FieldDef::FTyp_ShortDate);
			pTable->AddField(OLESTR("Account"), FieldDef::FTyp_Long);

			pTable->Open("C:\\mail", "a+b");
			pTable->Append();

			Table accounts;
			accounts.Open("C:\\accounts", "rb");

			int count = accounts.GetCount();

			for (int i = 0; i < count; i++)
			{
				Record* pRecord = accounts.GetRecord(i);
				Field* Server = pRecord->m_fields[1];
				Field* Username = pRecord->m_fields[2];
				Field* Password = pRecord->m_fields[3];

				MailAccount account;
				account.m_ID = pRecord->m_fields[0]->u.int32;
				account.m_server = std::string((char*)Server->GetData(), Server->GetSize());
				account.m_username = std::string((char*)Username->GetData(), Username->GetSize());
				account.m_password = std::string((char*)Password->GetData(), Password->GetSize());

				account.GetNewMail(pTable);
			}

			pTable->Close();
		}
#endif

#if 0
		{
			Table accounts;
			accounts.Open("C:\\news_accounts", "rb");

			/*
			int count = accounts.GetCount();

			for (int i = 0; i < count; i++)
			{
			*/
				Record* pRecord = accounts.GetRecord(0);
				Field* Server = pRecord->m_fields[1];
			//	Field* Username = pRecord->m_fields[2];
			//	Field* Password = pRecord->m_fields[3];

				NewsAccount account;
			//	account.m_ID = pRecord->m_fields[0]->u.int32;
				account.m_server = std::string((char*)Server->GetData(), Server->GetSize());
			//	account.m_username = std::string((char*)Username->GetData(), Username->GetSize());
			//	account.m_password = std::string((char*)Password->GetData(), Password->GetSize());

				{
					account.m_list = new Table;
					account.m_list->Open("C:\\newsgroups", "a+b");
					account.m_list->Append();

					account.m_list->AddField(OLESTR("ID"), FieldDef::FTyp_Long);
					account.m_list->AddField(OLESTR("Group"), FieldDef::FTyp_VarString);
				}

				account.Connect();
			//	account.GetList();
				account.Quit();

				{
					account.m_list->Close();
				}
		//	}
		}
#endif
	}

	{
		CView* view = new CView(0, L"Text");
		//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLLAYOUTVIEW, &view->m_menu);
		m_xmlDocumentWorkspace.m_views.Add(view);
	}

	{
		CDocumentSheet* pSheet = new CDocumentSheet;

		pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[0]);
		m_xmlDocumentWorkspace.m_views[0]->m_ownerSheet = pSheet;

		m_xmlDocumentWorkspace.m_documentsSheets.Add(pSheet);
	}

	pCanvas = new ChildWindowContainer;

#if 0
	{
		ITable* m_table = OpenTable("C:\\accounts", "rb");
		ViewTable(m_table);
	}

	{
		ITable* m_table = OpenTable("C:\\news_accounts", "rb");
		ViewTable(m_table);
	}
#endif

#if 1

	Database db("C:\\db", "rb");

	{
		Table m_table = db.GetTable(OLESTR("classes"));
		ViewTable(m_table);
	}

	{
		Table m_table = db.GetTable(OLESTR("classbases"));
		ViewTable(m_table);
	}

	{
		Table table;
		table = db.Execute("SELECT ID, Derived, Base, Name FROM classes, classbases WHERE Name=\"AsyncIAdviseSink2\" AND ID=Derived");

	//	ITable* table = Execute("DELETE FROM classes WHERE Name=\"test\"");

		if (table != NULL)
		{
			ViewTable(table);
		}
	}

#endif

#if 0
	{
		Table* m_table = new Table;
		m_table->Open("C:\\mail", "rb");
		ViewTable(m_table);
	}

	{
		Table* m_table = new Table;
		m_table->Open("C:\\newsgroups", "rb");
		ViewTable(m_table);
	}
#endif

#if 0
	{
		m_text = new TextEdit;
		m_text->set_textDocument(new TextDocument());

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(new Length(200, Length::UnitAbsolute));
		pWindow->set_Height(new Length(200, Length::UnitAbsolute));

		ScrollViewer* pScroller = new ScrollViewer;
		{
			pScroller->set_Content(m_text);
		}
		pWindow->set_Content(pScroller);
		pWindow->set_TitleText(OLESTR("www.bredband.no"));
		pCanvas->AddChild(pWindow);
	}
#endif

	set_Width(Length(1300));
	set_Height(Length(1000));
	set_Content(pCanvas);
}

void MailReaderFrame::ViewTable(Table pTable)
{
	ASSERT(0);
#if 0
	TableView* pTableView = new TableView;
	pTableView->m_list = new TreeControl;
	pTableView->m_table = pTable;
	pTableView->m_Canvas = pCanvas;

	int nfields = pTable.GetFieldCount();
	for (int i = 0; i < nfields; i++)
	{
		pTableView->m_list->m_treeHeader->AddColumn(new TextString(pTable.GetField(i)->GetName()));
	}

	try
	{
		int count = pTable.GetCount();

		for (int i = 0; i < count; i++)
		{
			Record pRecord = pTable[i];
			TreeItem* item = new TreeItem(pTableView->m_list);
			item->m_itemData = new IntObject(i);

			for (int f = 0; f < nfields; f++)
			{
				Field pField = pRecord[f];

				if (pField.GetDef()->GetType() == FTyp_VarString)
				{

					sysstring str;

					try
					{
						str = pField.GetStringA().ToStringW();
					}
					catch(int)
					{
						str = OLESTR("(Error)");
					}

					item->AppendColumnCell(new TextString(str));
				//	item->AppendColumnCell(new TextEdit(ConvertA2S((char*)pField->GetData(), pField->GetSize())));
				}
				else if (pField.GetDef()->GetType() == FTyp_Long)
				{
					OLECHAR buf[16];
					swprintf(buf, OLESTR("%d"), (long)pField.GetValue());
					item->AppendColumnCell(new TextEdit(buf));
				}
				else if (pField.GetDef()->GetType() == FTyp_ShortDate)
				{
					time_t tim = (long)pField.GetValue();
					tm* t = localtime((time_t*)&tim);
					if (t)
					{
						char buf[256];
						strftime(buf, 256, "%c", t);
						//swprintf(buf, OLESTR("%d"), pField->u.int32);
						item->AppendColumnCell(new TextString(ConvertA2S(buf, strlen(buf))));
					}
					else
						item->AppendColumnCell(new TextString(OLESTR("")));
				}
			}

			pTableView->m_list->get_Children()->AppendItem(item);
		}
	}
	catch(int)
	{
		char msg[256];
#if 0
		sprintf(msg, "Error reading database %s", pTable->get_filename().c_str());
#endif
		MessageBox(NULL/*GetHwnd()*/, msg, "", MB_OK);
	}

	{
		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(200, Length::UnitAbsolute));
		pWindow->put_Height(Length(200, Length::UnitAbsolute));

		ScrollViewer* pScroller = new ScrollViewer;
		{
			pScroller->put_Content(pTableView->m_list);
		}
		pTableView->put_VisualTree(pScroller);

		pWindow->put_Content(pTableView);
		pWindow->put_TitleText(OLESTR("www.bredband.no"));
		pCanvas->AddChild(pWindow);
	}
#endif
}

void MailReaderFrame::handleEvent(System::Event* evt)
{
	sysstring type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
	}
}
