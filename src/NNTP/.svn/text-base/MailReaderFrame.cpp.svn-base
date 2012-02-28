#include "stdafx.h"
#include "NNTP.h"
//#include "MailReaderFrame.h"

//#include "../LXUI/Socket.h"
//#include "../LXUI/TextDocument.h"

#include <time.h>

//#pragma comment(lib, "ws2_32.lib")	// TODO remove


namespace System
{

namespace POP3
{

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

	String ReadLine()
	{
		String str;

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
					if (str.GetLength() == 512)
						throw -1;
					str += c;

					if (str.GetLength() == 512)
						throw -1;
					str += c2;
				}
			}
			else
			{
				if (str.GetLength() == 512)
					throw -1;
				str += c;
			}
		}

	//	TRACE("%s\n", str.c_str());
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

#if 0
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
#endif

}

namespace NNTP
{

String NNTPClient::ReadLine()
{
	String str;

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
				if (str.GetLength() == 512)
					raise(Exception(L"linelen > 512"));
				str += c;

				if (str.GetLength() == 512)
					raise(Exception(L"linelen > 512"));
				str += c2;
			}
		}
		else
		{
			if (str.GetLength() == 512)
				raise(Exception(L"linelen > 512"));
			str += c;
		}
	}

//	TRACE("%s\n", str.c_str());
	return str;
}

class UUDecode : public Stream
{
public:
	CTOR UUDecode(Stream& stream, bool )
	{
		m_outputPos = 0;
	}

	static bool Marker(Stream& in);

protected:

	void Output(ubyte val)
	{
		m_output[(m_outputPos++) & 3] = val;
	}


	Stream m_in;
	uint m_len;
	ubyte m_output[4];
	uint m_outputPos;
	uint m_readPos;
};

/*
// static
bool UUDecode::Marker(Stream& in)
{
	char buf[5];
	in.Read(buf);
	ASSERT(!strcmp(buf, "begin"));

	char mode[3];
	in.Read(mode);
}
*/

/*
int UUDecode::ReadByte(uint8* pb)
{
	if (m_readPos == m_outputPos)
	{
		if (m_bfinal) return 0;

		ReadGroup();
	}

	*pb = m_outputGroup[(m_readPos++) & 3];
	return 1;
}
*/

bool DecodeLine(const char* line, Stream& outstream)
{
	const char* p = line;

	while (*p)
	{
		char c = *p++;
		uint byteCount;
		if (c == '`')
			return false;//byteCount = 0;
		else
			byteCount = c - 32;

		while (byteCount > 0)
		{
			// Decode each group of 4 characters to 3 bytes
			char group[4];
			group[0] = *p++;
			group[1] = *p++;
			group[2] = *p++;
			group[3] = *p++;

			uint32 decodedBytes = ((group[0]-32)<<18) | ((group[1]-32)<<12) | ((group[2]-32)<<6) | (group[3]-32);

			if (byteCount == 1)
			{
				outstream << (char)(decodedBytes>>24);

				byteCount -= 1;
			}
			else if (byteCount == 2)
			{
				outstream << (char)(decodedBytes>>24);
				outstream << (char)(decodedBytes>>16);

				byteCount -= 2;
			}
			else
			{
				outstream << (char)(decodedBytes>>24);
				outstream << (char)(decodedBytes>>16);
				outstream << (char)(decodedBytes>>8);

				byteCount -= 3;
			}
		}
	}
}

bool inited = 0;
FileStream fs;

char m_buf[1024];
int m_bufpos;

void NNTPClient::OnReceive(int nErrorCode)
{
	switch (m_state)
	{
	case 1:
		{
			if (!fs.IsHandleValid())
			{
				fs = new FileStreamObject("D:\testfile.uuencoded", 2, 0);
			}

		//	int nbytes = 1024 - ((m_bufpos++) & 1023);

			char buf[512];
			int nRead = Receive(buf, 512);

			fs.Write(buf, 512);

			/*
			char line[512];
			char* dst = line;
			while (*src != '\r' || *src != '\n')
			{
				*dst++ = m_buf[(m_bufpos++) & 1023];
			}
			*dst = 0;

			if (!inited)
			{
				inited = true;
			}
			else
			{
				if (!DecodeLine(line, fs))
				{
					m_state = 0;
				}
			}
			*/

		//	Std::Out << buf;
		}
		break;
	}
}

void NNTPClient::OnSend(int nErrorCode)
{
	/*
	TRACE("OnWrite\n");

	char* msg = "LIST\r\n";

	int nSent = send(m_socket, msg, strlen(msg), 0);
	*/
}

NewsAccount::NewsAccount()
{
	m_pSocket = NULL;
	m_port = 119;

	// TODO remove
	m_server = "news.teranews.com";
	m_username = "sigler@teranews.com";
	m_password = "sokrates";
}

String NewsAccount::Connect()
{
	m_pSocket = new NNTPClient;
	m_pSocket->Create();
	if (m_pSocket->Connect(CString(m_server).c_str(), m_port))
	{
		m_response = m_pSocket->ReadLine();
	}
	else
	{
		m_response = "Failed to connect to server '" + m_server +"'";
	}

	return m_response;
}

void NewsAccount::SetAuthInfo(StringIn username, StringIn password)
{
	m_username = username;
	m_password = password;
}

void NewsAccount::Authenticate()
{
	m_pSocket->Write("AUTHINFO USER ");
	m_pSocket->Write(m_username);
	m_pSocket->Write("\r\n");
	m_response = m_pSocket->ReadLine();

	/*

When authorization is required, the server will send a 480
    response requesting authorization from the client. The
    client must enter AUTHINFO USER followed by the username.
    Once sent, the server will cache the username and may send
    a 381 response requesting the password associated with that
    username. Should the server request a password using the 381
    respose, the client must enter AUTHINFO PASS followed by
    a password and the server will then check the authentication
    database to see if the username/password combination is valid.
    If the combination is valid 

 or if no password is required,
    the server will return a 281 response. The client should then
    retry the original command to which the server responded with
    the 480 response. The command should then be processed by
    the server normally. If the combination is not valid, the server
    will return a 502 response.
*/

	if (m_response.LeftOf(3) == "381")
	{
		m_pSocket->Write("AUTHINFO PASS ");
		m_pSocket->Write(m_password);
		m_pSocket->Write("\r\n");

		m_response = m_pSocket->ReadLine();
	}
}

String NewsAccount::Quit()
{
	m_pSocket->Write("QUIT\r\n");
	m_response = m_pSocket->ReadLine();
	return m_response;
}

String NewsAccount::GetArticle(int n)
{
	StringStream stream;
	stream << "ARTICLE " << n << "\r\n";

	m_pSocket->m_state = 1;
	m_pSocket->Write(stream->str());

//	m_response = m_pSocket->ReadLine();

	/*
	if (m_response.LeftOf(3) == "480")
	{
		Authenticate();

		m_pSocket->Write(stream->str());

		m_response = m_pSocket->ReadLine();
	}
	*/

	return null;
}

String NewsAccount::SetGroup(StringIn name)
{
	m_pSocket->Write("GROUP ");
	m_pSocket->Write(name);
	m_pSocket->Write("\r\n");

	m_response = m_pSocket->ReadLine();
	if (m_response.LeftOf(3) == "480")
	{
		Authenticate();

		m_pSocket->Write("GROUP ");
		m_pSocket->Write(name);
		m_pSocket->Write("\r\n");

		m_response = m_pSocket->ReadLine();
	}

	return m_response;
	/*
	if (m_response.LeftOf(3) != "215")
	{
		return m_response;
	}
	*/
}

String NewsAccount::GetList()
{
	m_pSocket->Write("LIST\r\n");
	m_response = m_pSocket->ReadLine();
	if (m_response.LeftOf(3) == "480")
	{
		Authenticate();

		m_pSocket->Write("LIST\r\n");
		m_response = m_pSocket->ReadLine();
	}

	if (m_response.LeftOf(3) != "215")
	{
		return m_response;
	}

	while (1)
	{
		String line = m_pSocket->ReadLine();
		if (line == ".")
		{
			break;
		}

		char name[1024];
		int last;
		int first;
		char p;
		sscanf(CString(line).c_str(), "%s %d %d %c", name, &last, &first, &p);

		NewsGroup* group = new NewsGroup;

		group->m_name = name;
		group->m_first = first;
		group->m_last = last;
		group->m_postingAllowed = (p == 'y');

		Std::Out << group << "\n";

		/*
		Record pRecord = m_list.NewRecord();

		pRecord.get_Fields()[1].SetData(group);

		pRecord.Update();
		*/
	}

	return null;
}

#if 0
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

#endif

}	// NNTP
}	// System
