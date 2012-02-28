
namespace System
{

#if 0
class MailAccount : public Object
{
public:
	void GetNewMail(ITable* pTable);

	long m_ID;
	String m_server;
	String m_username;
	String m_password;

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

#endif

namespace NNTP
{

class NNTPEXT NNTPClient : public AsyncSocket
{
public:

	String ReadLine();

	void Write(StringIn str)
	{
		AsyncSocket::Write(CString(str).c_str(), str.GetLength());
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
#endif
	virtual void OnReceive(int nErrorCode) override;
	virtual void OnSend(int nErrorCode) override;

	int m_state;
};

class NNTPEXT NewsGroup : public DispatcherObject
{
public:

	String get_Name()
	{
		return m_name;
	}

	int get_First()
	{
		return m_first;
	}

	int get_Last()
	{
		return m_last;
	}

	bool get_PostingAllowed()
	{
		return m_postingAllowed;
	}

	virtual String ToString() override
	{
		StringStream str;
		str << m_name << " " << m_first << " " << m_last << " " << m_postingAllowed;
		return str;
	}

	String m_name;
	int m_first;
	int m_last;
	bool m_postingAllowed;
};

class NNTPEXT NewsAccount : public DispatcherObject
{
public:
	CTOR NewsAccount();

	void set_Server(StringIn server)
	{
		m_server = server;
	}

	int get_Port()
	{
		return m_port;
	}

	void set_Port(int port)
	{
		m_port = port;
	}

	String get_Response()
	{
		return m_response;
	}

	void SetAuthInfo(StringIn username, StringIn password);
	String Connect();

	String GetList();
	String SetGroup(StringIn name);
	String GetArticle(int n);
	String Quit();

	NewsGroup* FindNewsGroup(StringIn name);
	IEnumerable<NewsGroup*> FindNewsGroups(StringIn name);

	List<NewsGroup*>& get_NewsGroups()
	{
		return m_newsgroups;
	}

	List<NewsGroup*> m_newsgroups;
	map<String, NewsGroup*> m_newsgroupsByFullName;
	multimap<String, NewsGroup*> m_newsgroupsByPartName;

protected:

	void Authenticate();

//	Table m_list;

	NNTPClient* m_pSocket;
	String m_response;
	String m_group;

	String m_username;
	String m_password;

	String m_server;
	int m_port;
};

}	// NNTP
}	// System
