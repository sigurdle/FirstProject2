#include "stdafx.h"
#include "P2PFrame.h"
#include "../LXUI/TextDocument.h"
//#include <sstream>
#include "../LXUI/http.h"

#pragma comment(lib, "../LXChatter/Debug/LXChatter.lib")

#include "../Browser/Item.h"

namespace System
{

class Downloads;

IItemsContainer* ConnectionsCtl;
Downloads* m_Downloads;

class Networks
{
public:
	IItemsContainer* m_itemContainer;

	Networks()
	{
		TreeControlContainer* tree = new TreeControlContainer;
		m_itemContainer = tree;

//		m_itemContainer->AddField(L"Name");
		m_itemContainer->AddField(L"Clients");
		m_itemContainer->AddField(L"Shared Files");
		m_itemContainer->AddField(L"Data Amount");
	}
};

class Network : public Object, public IItem, public INetworkClient
{
public:
	Network()
	{
		m_clientsUI = new TextString(L"0");
		m_sharedFilesUI = new TextString(L"0");
		m_amountUI = new TextString(L"0");
	}

	INetwork* pP2P;

	TextString* m_clientsUI;
	TextString* m_sharedFilesUI;
	TextString* m_amountUI;

	virtual void OnConnection(IConnection* pSocket);
	virtual void OnCloseConnection(IConnection* pSocket);
	virtual void OnConnectionStatus(IConnection* pSocket, int code);

	virtual void OnNetworkInfo(const NETWORKINFO* info);

	Visual* GetFieldUI(int ind)
	{
		if (ind == 0)
			return m_clientsUI;
		else if (ind == 1)
			return m_sharedFilesUI;
		else if (ind == 2)
			return m_amountUI;
		else
			return NULL;
	}

	FieldData* GetFieldData(int ind)
	{
		return NULL;
	}
};

Networks* m_Networks;
//Network* m_GnutellaNetwork;

class Results : public ISearchHitHandler, public Control//IEventListener
{
public:

	IQuery* m_query;
	IItemsContainer* m_itemContainer;

	Results()
	{
		TreeControlContainer* tree = new TreeControlContainer;
		m_itemContainer = tree;

		m_itemContainer->AddField(L"Filename");
		m_itemContainer->AddField(L"Size");
		m_itemContainer->AddField(L"Speed");
		m_itemContainer->AddField(L"Host");
		m_itemContainer->AddField(L"SHA1 Hash");

	//	tree->m_groupBy.push_back(4);	// SHA1 Hash

	//	dynamic_cast<CEventTargetImpl*>(m_itemContainer)->addEventListener(L"Activate", this, false);
	//	dynamic_cast<CEventTargetImpl*>(m_itemContainer)->addEventListener(L"Activate", this, false);

		DockPanel* panel = new DockPanel;
		{
			{
				Button* pButton = new Button;
				pButton->put_Content(new TextString(OLESTR("More")));
				panel->AddRChild(pButton);
			}
			{
				DockPanel::put_Dock(dynamic_cast<Control*>(m_itemContainer), DockPanel::Fill);
				panel->AddRChild(dynamic_cast<Control*>(m_itemContainer));
			}
		}

		m_nhits = 0;

		set_VisualTree(panel);
	}

	DWORD m_nhits;

	virtual void OnHit(ISearchHit* pHit);

	virtual void handleEvent(Event* evt);
};

class ResultItem : public Object, public IItem, public IEventListener
{
public:
//	DWORD m_IPAddress;
//	WORD m_Port;
	ISearchHit* m_QueryHitData;

	IItemSite* m_site;

	TextString* m_uiFilename;
	TextString* m_uiSize;
	TextString* m_uiHostSpeed;
	TextString* m_uiHost;
	TextString* m_uiSHA1Hash;

	Network* m_network;

	LongLongField* m_size;
	SHA1DigestField* m_sha1;

	FieldData* GetFieldData(int ind)
	{
		if (ind == 1)
		{
			return m_size;
		}
		else if (ind == 4)
		{
			return m_sha1;
		}
		else
			return NULL;
	}

	Visual* GetFieldUI(int ind)
	{
		if (ind == 0)
			return m_uiFilename;
		else if (ind == 1)
			return m_uiSize;
		else if (ind == 2)
			return m_uiHostSpeed;
		else if (ind == 3)
			return m_uiHost;
		else if (ind == 4)
			return m_uiSHA1Hash;
		else
			return NULL;
	}

	void handleEvent(Event* evt);

};

class Downloads : public IDownloadHandler
{
public:
	IItemsContainer* m_itemContainer;

	Downloads()
	{
		TreeControlContainer* tree = new TreeControlContainer;
		m_itemContainer = tree;

		m_itemContainer->AddField(L"Filename");
		m_itemContainer->AddField(L"Size");
		m_itemContainer->AddField(L"Speed");
		m_itemContainer->AddField(L"Host");
		m_itemContainer->AddField(L"SHA1 Hash");

		tree->m_groupBy.push_back(4);	// SHA1 Hash

	//	dynamic_cast<CEventTargetImpl*>(m_itemContainer)->addEventListener(L"Activate", this, false);

	//	m_nhits = 0;
	}

	virtual void OnHit(ISearchHit* pHit);
};

class DownloadItem : public ResultItem
{
public:
	//IItemSite* m_site;
	//TextString* m_uiFileName;

	/*
	DWORD m_IPAddress;
	WORD m_Port;

	DWORD m_fileIndex;
	std::string m_fileName;
	*/

	/*
	//ISearchHit* m_QueryHitData;
	LONGLONG m_FileSize;
	BYTE m_digest[20];

	TextString* m_uiFilename;
	*/

	/*
	void Download()
	{
		ByteStreamWriter* file = new ByteStreamWriter(ConvertS2A(m_uiFilename->get_textContent()).c_str());
		pP2P->Download(m_size->m_value, m_sha1->m_buffer, m_Downloads, file);
	}
	*/

#if 0
	FieldData* GetFieldData(int ind)
	{
		return NULL;
	}

	Visual* GetFieldUI(int ind)
	{
		if (ind == 0)
			return m_uiFileName;
		/*
		else if (name == L"Size")
			return m_uiSize;
			*/
		else
			return NULL;
	}
#endif
};

void Results::OnHit(ISearchHit* pHit)
{
	if (m_nhits < 10000)
	{
		ResultItem* hit = new ResultItem;
		hit->m_QueryHitData = pHit;

		hit->m_size = new LongLongField(pHit->get_FileSize());
		hit->m_sha1 = new SHA1DigestField(pHit->get_Sha1Digest());

		hit->m_uiFilename = new TextString(pHit->get_FileName());

		{
			WCHAR buf[64];
			swprintf_s(buf, L"%d Kb", (DWORD)(hit->m_size->m_value >> 10));
			hit->m_uiSize = new TextString(buf);
		}

		{
			DWORD HostSpeed = pHit->get_HostSpeed();
			WCHAR buf[64];
			swprintf_s(buf, L"%d Kb/s", HostSpeed);
			hit->m_uiHostSpeed = new TextString(buf);
		}

		{
			DWORD IPAddress;
			WORD Port;
			pHit->GetHost(&IPAddress, &Port);

			in_addr addr;
			addr.s_addr = IPAddress;
			std::string server = inet_ntoa(addr);

			WCHAR buf[64];
			swprintf_s(buf, L"%S:%d", server.c_str(), Port);

			hit->m_uiHost = new TextString(buf);
		}

		{
			WCHAR buf[40+1];
			WCHAR* p = buf;

			const BYTE* digest = pHit->get_Sha1Digest();

			for (int i = 0; i < 20; i++)
			{
				swprintf(p, L"%2.2x", digest[i]);
				p += 2;
			}

			hit->m_uiSHA1Hash = new TextString(buf);
		}

		hit->m_site = m_itemContainer->AddItem(hit);
		dynamic_cast<EventTargetImpl*>(hit->m_site)->addEventListener(L"Activate", hit, false);

		m_nhits++;
	}
}

void Downloads::OnHit(ISearchHit* pHit)
{
//	if (m_nhits < 10000)
	{
		ResultItem* hit = new ResultItem;
		hit->m_QueryHitData = pHit;

		hit->m_size = new LongLongField(pHit->get_FileSize());
		hit->m_sha1 = new SHA1DigestField(pHit->get_Sha1Digest());

		hit->m_uiFilename = new TextString(pHit->get_FileName());

		{
			WCHAR buf[64];
			swprintf_s(buf, L"%d Kb", (DWORD)(hit->m_size->m_value >> 10));
			hit->m_uiSize = new TextString(buf);
		}

		{
			DWORD HostSpeed = pHit->get_HostSpeed();
			WCHAR buf[64];
			swprintf_s(buf, L"%d Kb/s", HostSpeed);
			hit->m_uiHostSpeed = new TextString(buf);
		}

		{
			DWORD IPAddress;
			WORD Port;
			pHit->GetHost(&IPAddress, &Port);

			in_addr addr;
			addr.s_addr = IPAddress;
			std::string server = inet_ntoa(addr);

			WCHAR buf[64];
			swprintf_s(buf, L"%S:%d", server.c_str(), Port);

			hit->m_uiHost = new TextString(buf);
		}

		{
			WCHAR buf[40+1];
			WCHAR* p = buf;

			const BYTE* digest = pHit->get_Sha1Digest();

			for (int i = 0; i < 20; i++)
			{
				swprintf(p, L"%2.2x", digest[i]);
				p += 2;
			}

			hit->m_uiSHA1Hash = new TextString(buf);
		}

		hit->m_site = m_itemContainer->AddItem(hit);
		dynamic_cast<EventTargetImpl*>(hit->m_site)->addEventListener(L"Activate", hit, false);

	//	m_nhits++;
	}
}

void ResultItem::handleEvent(Event* evt)
{
	sysstring type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
#if 0
		if (type == OLESTR("Activate"))
		{
			evt->stopPropagation();

			IItemSite* itemsite = dynamic_cast<IItemSite*>(evt->get_target());
			SHA1DigestField* sha1 = dynamic_cast<SHA1DigestField*>(itemsite->GetFieldData(4));

			ByteStreamWriter* file = new ByteStreamWriter(ConvertS2A(dynamic_cast<TextString*>(itemsite->GetFieldUI(0))->get_textContent()).c_str());
			pP2P->Download(m_size->m_value, m_sha1->m_buffer, m_Downloads, file);

			/*
			DownloadItem* item = new DownloadItem;
			item->m_uiFilename = new TextString(L"Test");//new TextString(m_uiFilename->get_textContent());
			item->m_site = m_Downloads->m_itemContainer->AddItem(item);

			item->m_uiSize = dynamic_cast<LongLongField*>(itemsite->GetFieldData(1))->m_value;
			memcpy(item->m_digest, sha1->m_buffer, 20);
			*/

		//	item->m_QueryHitData = m_QueryHitData;
			//item->Download();
		}
#endif
	}
}

void Results::handleEvent(Event* evt)
{
	sysstring type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == OLESTR("click"))
		{
			evt->stopPropagation();
			m_query->More();
		}
		else if (type == OLESTR("Activate"))
		{
			evt->stopPropagation();

			IItemSite* itemsite = dynamic_cast<IItemSite*>(evt->get_target());

			SHA1DigestField* sha1 = dynamic_cast<SHA1DigestField*>(itemsite->GetFieldData(4));

			std::string filename = ConvertS2A(dynamic_cast<TextString*>(itemsite->GetFieldUI(0))->get_textContent());
			//LPTSTR ext = PathFindExtension(filename.c_str());
			TCHAR filepart[512];
			TCHAR extpart[512];
			_splitpath(filename.c_str(), NULL, NULL, filepart, extpart);

			ByteStreamWriter* file = NULL;
			int n = 0;
			do
			{
				try
				{
					char modifiedfilename[512];

					if (n > 0)
						strcpy(modifiedfilename, filename.c_str());
					else
						sprintf(modifiedfilename, "%s(%d)%s", filepart, n, extpart);

					file = new ByteStreamWriter(modifiedfilename);
				}
				catch(int e)
				{
					if (e == ERROR_SHARING_VIOLATION)
					{
						n++;	// Try again
					}
					else
					{
						// Any other error, we give up
						break;
					}
				}
			}
			while (file == NULL);

			if (file == NULL)
			{
				MessageBox(NULL, "Couldn't create file", "", MB_OK);
			}
			else
			{
				MessageBeep(-1);
				//m_GnutellaNetwork->pP2P->Download(dynamic_cast<LongLongField*>(itemsite->GetFieldData(1))->m_value, sha1->m_buffer, m_Downloads, file);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
// P2PFrame

P2PFrame::P2PFrame()
{
//	std::string filename = DownloadFile("http://www.lerstad.com/");

	put_Width(new Length(400, Length::UnitAbsolute));
	put_Height(new Length(300, Length::UnitAbsolute));

	DockPanel* p = new DockPanel;
	{

		{
			CUIDockBar* pDockbar = new CUIDockBar;
			{
				pDockbar->put_BackgroundBrush(new SolidColorBrush(new Color(236, 233, 216)));
				{
					//Gripper* pGripper = new Gripper;
				//	pGripper->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(255, 0, 0)));
					{
						Toolbar* pToolbar = new Toolbar;
					//	pToolbar->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(0, 255, 0)));

						{

							CLXUIMenuElement* pMenu = new CLXUIMenuElement(new TextString(OLESTR("File")));
							{
								pMenu->AddItem(new TextString(OLESTR("Open")), ID_FILE_OPEN);
								pMenu->AddItem(new TextString(OLESTR("Save")));
								pMenu->AddItem(new TextString(OLESTR("Open Program")), ID_FILE_OPENPROGRAM);
								{
									CLXUIMenuElement* pMenu2 = new CLXUIMenuElement(new TextString(OLESTR("Debug")));
									pMenu2->AddItem(new TextString(OLESTR("Go")), ID_DEBUG_GO);
									pMenu2->AddItem(new TextString(OLESTR("Step Into")), ID_DEBUG_STEPINTO);
									pMenu->AddMenuItem(pMenu2);
								}
								{
									CLXUIMenuElement* pMenu2 = new CLXUIMenuElement(new TextString(OLESTR("Edit")));
									pMenu2->AddItem(new TextString(OLESTR("Cut")), ID_EDIT_CUT);
									pMenu2->AddItem(new TextString(OLESTR("Copy")), ID_EDIT_COPY);
									pMenu2->AddItem(new TextString(OLESTR("Paste")), ID_EDIT_PASTE);
									pMenu->AddMenuItem(pMenu2);
								}
								/*
								{
									CLXUIMenuElement* pMenu2 = new CLXUIMenuElement(new TextString(OLESTR("Prefs2")));
									pMenu2->AddItem(new TextString(OLESTR("Local")));
									pMenu2->AddItem(new TextString(OLESTR("Global")));
									pMenu2->AddItem(new TextString(OLESTR("Something")));
									{
										CLXUIMenuElement* pMenu3 = new CLXUIMenuElement(new TextString(OLESTR("Prefs3")));
										pMenu3->AddItem(new TextString(OLESTR("Local")));
										pMenu3->AddItem(new TextString(OLESTR("Global")));
										pMenu3->AddItem(new TextString(OLESTR("Something")));
										pMenu2->AddMenuItem(pMenu3);
									}

									pMenu->AddMenuItem(pMenu2);
								}
								*/
								pMenu->AddSeparator();
								pMenu->AddItem(new TextString(OLESTR("Exit")), ID_APP_EXIT);
							}
							pToolbar->AddRChild(pMenu);

						}

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(OLESTR("Save")));
							pToolbar->AddRChild(pButton);
						}

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(OLESTR("Exit")));
							pToolbar->AddRChild(pButton);
						}

						/*
						{
							TextString* pText = new TextString(OLESTR("Button0"), font);
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(OLESTR("Button1"), font);
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(OLESTR("Button2"), font);
							pToolbar->AddRChild(pText);
						}
						*/

						//pGripper->put_Content(pToolbar);
						pDockbar->DockControlBar(pToolbar);
					}
					//pDockbar->DockControlBar(pGripper);
				}

				{
				//	Gripper* pGripper = new Gripper;
				//	pGripper->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(255, 0, 0)));
					{
						Toolbar* pToolbar = new Toolbar;
					//	pToolbar->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(0, 255, 0)));

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(OLESTR("Cut")));
							pToolbar->AddRChild(pButton);
						}

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(OLESTR("Copy")));
							pToolbar->AddRChild(pButton);
						}

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(OLESTR("Paste")));
							pToolbar->AddRChild(pButton);
						}


				//		pGripper->put_Content(pToolbar);
						pDockbar->DockControlBar(pToolbar);
					}
				//	pDockbar->DockControlBar(pGripper);
				}

			}
			p->set_Dock(pDockbar, DockPanel::Top);
			p->AddRChild(pDockbar);
		}

		{
			CUIDockBar* pDockbar = new CUIDockBar;
			{
				pDockbar->set_BackgroundBrush(new SolidColorBrush(new Color(236, 233, 216)));
			}
			p->set_Dock(pDockbar, DockPanel::Bottom);
			p->AddRChild(pDockbar);
		}


		pCanvas = new ChildWindowContainer;
		{
			Border* outerBorder = new Border(new Thickness(new Length(4, Length::UnitAbsolute), new Length(4, Length::UnitAbsolute), new Length(4, Length::UnitAbsolute), new Length(4, Length::UnitAbsolute)));
			outerBorder->put_BackgroundBrush(new SolidColorBrush(new Color(255, 255, 255)));
			{
				DockPanel* panel2 = new DockPanel;
				{
					DockPanel* panel = new DockPanel;
					{
						Button* pSearchButton = new Button(new TextString(OLESTR("Search")));
						DockPanel::set_Dock(pSearchButton, DockPanel::Right);
						panel->AddRChild(pSearchButton);
					}

					{
						Border* pBorder = new Border(new Thickness(new Length(1, Length::UnitAbsolute), new Length(1, Length::UnitAbsolute), new Length(1, Length::UnitAbsolute), new Length(1, Length::UnitAbsolute)));
						pBorder->m_LeftBrush = new SolidColorBrush(new Color(0, 0, 0));
						pBorder->m_TopBrush = new SolidColorBrush(new Color(0, 0, 0));
						pBorder->m_RightBrush = new SolidColorBrush(new Color(160, 160, 160));
						pBorder->m_BottomBrush = new SolidColorBrush(new Color(160, 160, 160));
						{
							m_searchEdit = new TextEdit;
						//	m_searchEdit->m_tdp = new TextDocument;
						//	m_searchEdit->SetText(OLESTR(""));
							pBorder->set_Content(m_searchEdit);
						}
						DockPanel::set_Dock(pBorder, DockPanel::Fill);
						panel->AddRChild(pBorder);
					}
					DockPanel::put_Dock(panel, DockPanel::Top);
					panel2->AddRChild(panel);
				}
				{
					Border* pSpacer = new Border;
					DockPanel::set_Dock(pSpacer, DockPanel::Fill);
					panel2->AddRChild(pSpacer);
				}
				outerBorder->put_Content(panel2);
			}
			Border* ctl = outerBorder;


			{
				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//put_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//put_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(new Length(240, Length::UnitAbsolute));
				pWindow->set_Height(new Length(210, Length::UnitAbsolute));

				if (true)
				{
					pWindow->set_Content(ctl);
				}
				else
				{
					ScrollViewer* pScroller = new ScrollViewer;
					{
						pScroller->put_Content(ctl/*m_watchWnd*/);
					}
					pWindow->set_Content(pScroller);
				}

				pWindow->set_TitleText(OLESTR("Search"));

			//	pWindow->SetOwnerWindow(pCanvas->get_OwnerWindow());	// TODO, not here
				pCanvas->AddChild(pWindow);
			}
			if (true)
			{
				ConnectionsCtl = new TreeControlContainer;
			//	ConnectionsCtl->m_treeHeader->AddColumn(new TextString(OLESTR("IP-Address")));
			//	ConnectionsCtl->m_treeHeader->AddColumn(new TextString(OLESTR("Status")));

				ConnectionsCtl->AddField(L"Address");

				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//put_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//put_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(new Length(240, Length::UnitAbsolute));
				pWindow->set_Height(new Length(210, Length::UnitAbsolute));

				pWindow->set_Content(dynamic_cast<Control*>(ConnectionsCtl));

				pWindow->set_TitleText(OLESTR("Connections"));

				pCanvas->AddChild(pWindow);
			}

			if (true)
			{
				m_Downloads = new Downloads;
				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//put_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//put_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(new Length(240, Length::UnitAbsolute));
				pWindow->set_Height(new Length(210, Length::UnitAbsolute));

				pWindow->set_Content(dynamic_cast<Control*>(m_Downloads->m_itemContainer));

				pWindow->set_TitleText(OLESTR("Downloads"));

				pCanvas->AddChild(pWindow);
			}

			if (true)
			{
				m_Networks = new Networks;

				if (false)
				{
					Network* pNetwork = new Network;

					{
						pNetwork->pP2P = new GnutellaNetwork(pNetwork);
						pNetwork->pP2P->Connect();
					}

					m_Networks->m_itemContainer->AddItem(pNetwork);
				}

				if (false)
				{
					Network* pNetwork = new Network;

					{
						pNetwork->pP2P = new Gnutella2Network(pNetwork);
						pNetwork->pP2P->Connect();
					}

					m_Networks->m_itemContainer->AddItem(pNetwork);
				}

				{
					Network* pNetwork = new Network;

					{
						pNetwork->pP2P = new EDonkeyNetwork(pNetwork);
						pNetwork->pP2P->Connect();
					}

					m_Networks->m_itemContainer->AddItem(pNetwork);
				}

				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//put_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//put_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(new Length(240, Length::UnitAbsolute));
				pWindow->set_Height(new Length(210, Length::UnitAbsolute));

				pWindow->set_Content(dynamic_cast<Control*>(m_Networks->m_itemContainer));

				pWindow->set_TitleText(OLESTR("Networks"));

				pCanvas->AddChild(pWindow);
			}
		}
		p->set_Dock(pCanvas, DockPanel::Fill);
		p->AddRChild(pCanvas);
	}
	set_Content(p);
	set_TitleText(WSTR("LP2P"));
}

void Network::OnNetworkInfo(const NETWORKINFO* info)
{
	WCHAR buf[16];

	swprintf_s(buf, L"%ul", (DWORD)(info->NumberOfClients));
	m_clientsUI->put_textContent(buf);

	swprintf_s(buf, L"%ul", (DWORD)(info->NumberOfSharedFiles));
	m_sharedFilesUI->set_textContent(buf);

	if (info->NumberOfKilobytesShared >= 1048576)
	{
		swprintf_s(buf, L"%.2f Gb", (info->NumberOfKilobytesShared / 1048576.0));
	}
	else if (info->NumberOfKilobytesShared >= 1024)
	{
		swprintf_s(buf, L"%.2f Mb", (info->NumberOfKilobytesShared / 1024.0));
	}
	else
	{
		swprintf_s(buf, L"%.2f Kb", (info->NumberOfKilobytesShared));
	}

	m_amountUI->set_textContent(buf);
}

class ConnectionItem : public Object, public IItem
{
public:
	IItemSite* m_site;

	IPField* m_IPAddress;

	FieldData* GetFieldData(int ind)
	{
		if (ind == 0)
			return m_IPAddress;
		else
			ASSERT(0);
		return NULL;
	}

	Visual* GetFieldUI(int ind)
	{
		const char* str = inet_ntoa(*(in_addr*)&m_IPAddress->m_address);

		WCHAR buf[64];
		swprintf(buf, L"%S:%d", str, m_IPAddress->m_port);

		return new TextString(buf);
	}
};

void Network::OnConnection(IConnection* pConnection)
{
	ConnectionItem* item = new ConnectionItem;
	IPv4 v4 = pConnection->get_Address();
	item->m_IPAddress = new IPField(v4.IPAddress, v4.Port);

	pConnection->m_userdata = dynamic_cast<Object*>(item);
	item->m_site = ConnectionsCtl->AddItem(item);

	/*
	TreeItem* item = new TreeItem(ConnectionsCtl);
	item->AppendColumnCell(new TextString(pSocket->get_Name().c_str()));
	item->AppendColumnCell(new TextString(L"Connecting"));
	ConnectionsCtl->get_Children()->AppendItem(item);
	ConnectionsCtl->get_Children()->InvalidateMeasure();	// TODO remove

	pConnection->m_userdata = item;
	*/
	//pSocket->m_user.insert(tyusermap::value_type(L"P2PFrame", item));
}

void Network::OnCloseConnection(IConnection* pConnection)
{
//	tyusermap::iterator it = pSocket->m_user.find(L"P2PFrame");
//	ASSERT(it != pSocket->m_user.end());
//	TreeItem* item = dynamic_cast<TreeItem*>((*it).second);
	ConnectionItem* item = dynamic_cast<ConnectionItem*>(pConnection->m_userdata);
	ConnectionsCtl->RemoveItem(item->m_site);
}

void Network::OnConnectionStatus(IConnection* pSocket, int code)
{
	/*
	sysstring text;
	if (code == 200)
		text = "OK";
	else
		text " "Failed

	TreeItem* item = dynamic_cast<TreeItem*>(pSocket->m_userdata);
	dynamic_cast<TextString*>(item->GetRChildList()[1])->put_textContent
	*/
}

void P2PFrame::handleEvent(Event* evt)
{
	sysstring type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == OLESTR("click"))
		{
			evt->stopPropagation();

			Results* pResults = new Results;

			sysstring searchString = m_searchEdit->GetText();

			// TODO, search on all networks

			for (int i = 0; i < m_Networks->m_itemContainer->GetCount(); i++)
			{
				Network* pNetwork = dynamic_cast<Network*>(m_Networks->m_itemContainer->GetItem(i));

				pResults->m_query = pNetwork->pP2P->Search(searchString, static_cast<ISearchHitHandler*>(pResults));
			//	m_GnutellaNetwork->pP2P->Search(searchString, static_cast<ISearchHitHandler*>(pResults));
			}

		//	TreeControlContainer* container = new TreeControlContainer;
		//	pResults->m_itemContainer = container;

			ChildWindow* pWindow = new ChildWindow;
			pWindow->put_Width(new Length(300, Length::UnitAbsolute));
			pWindow->put_Height(new Length(300, Length::UnitAbsolute));

			pWindow->put_Content(pResults);
			pWindow->put_TitleText(searchString);
			pCanvas->AddChild(pWindow);
		}
		else if (type == OLESTR("keydown"))
		{

#if 0
			printf("Step Into\n");
			OnDebugStepInto();
			return;
#endif
		}
		else if (type == OLESTR("mousedown"))
		{
		//	OnDebugStepInto();
		}
	}

	CLXUIWindow::handleEvent(evt);
}

}
