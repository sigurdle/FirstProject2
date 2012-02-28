#include "stdafx.h"
#include "Browser.h"
#include "View.h"
//#include "ViewOfCollection.h"
//#include "PropertiesTable.h"

namespace System
{
using namespace UI;

ViewOfCollection::ViewOfCollection()
{
	m_pCollection = NULL;
	m_ti = NULL;
	m_table = NULL;
	m_pSelectedItem = NULL;

	//m_pDir = pDir;
	//Refresh();
}

void ViewOfCollection::Refresh(IObjectCollection* pCollection)
{
	m_pCollection = pCollection;

	/*
	void* vtable = *(void**)pDir;
	rti* p3 = ((rti**)vtable)[-1];

	int count = p3->m_classHierarchyDescriptor->count;
	BaseClassDescriptor** table = p3->m_classHierarchyDescriptor->m_baseClassArray;

	type_info* ti = (type_info*)table[0]->typedesc;
	*/

//	UI::ScrollViewer* pScroller = new UI::ScrollViewer;

	m_table = new PropertiesTable(/*ti,*/ m_pCollection);

	set_VisualTree(m_table);
}

#if 0
void ViewOfCollection::handleEvent(System::Event* evt)
{
#if WIN32
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
	//	if (evt->get_type() == OLESTR("ItemStateChanging"))
		if (*evt->get_type() == L"ActivateItem")
		{
			evt->stopPropagation();

		//	UI::MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
		//	LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			/*
			UI::TreeItem* item;
			UI::Visual* target = dynamic_cast<UI::Visual*>(evt->get_target());
			while (target)
			{
				item = dynamic_cast<UI::TreeItem*>(target);
				if (item) break;

				target = dynamic_cast<UI::Visual*>(target->GetRParent());
			}
			*/

			m_pSelectedItem = dynamic_cast<UI::TreeItem*>(evt->get_target());

			IDocument* pFile = dynamic_cast<IDocument*>(m_pSelectedItem->m_userdata);
			if (pFile)
			{
				pFile->Open(m_table, m_pSelectedItem);
			}
		}

#if 0
		if (evt->get_type() == OLESTR("ItemStateChanging"))
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			m_pSelectedItem = static_cast<UI::TreeItem*>(evt->get_target());

			void* vobject = m_pSelectedItem->m_userdata;
			if (vobject == NULL) return;

			StringA classname;
			Object* obj;

			void* vtable = *(void**)vobject;
			rti* p3 = ((rti**)vtable)[-1];

			int count = p3->m_classHierarchyDescriptor->count;
			BaseClassDescriptor** table = p3->m_classHierarchyDescriptor->m_baseClassArray;

			Type_Info* ti = (Type_Info*)table[0]->typedesc;
			classname = ti->name() + strlen("class ");

			if (classname == "FileObject")
			{
				FileObject* pFile = dynamic_cast<FileObject*>(m_pSelectedItem->m_userdata);

				if (pFile->m_FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (m_pSelectedItem->get_Children() == NULL)
					{
						DirectoryObject* pDir = new DirectoryObject();//m_pDir->m_dirName + "/" + pFile->get_Name());
						pDir->SetDir(pFile);

						pFile->m_views.push_back(pDir);

						//UI::TreeItemChildren* treechildren = new UI::TreeItemChildren(m_pTree);
						m_table->Build(pDir, m_pSelectedItem);	// TODO, only refresh current item

						/*
						ViewOfCollection* ctl = new ViewOfCollection(pDir);
						ctl->m_pCanvas = m_pCanvas;

						pView = ctl;

						if (pView)
						{
							if (true)
							{
							//	ctl->put_Width(200);
							//	ctl->put_Height(200);
								ctl->Measure(LDraw::SizeD(0,0));
								ctl->InvalidateMeasure();
								m_pSelectedItem->put_Children(ctl);
								//item->Expand();
							}
							else
							{
								ChildWindow* pWindow = new ChildWindow;
								pWindow->put_Width(Length(200, Length::UnitAbsolute));
								pWindow->put_Height(Length(200, Length::UnitAbsolute));

								pWindow->put_Content(dynamic_cast<Control*>(pView));//pScroller);
								//	pWindow->put_Content(m_callStackWnd);

								pWindow->put_TitleText(ConvertA2S(pDir->m_dirName));

						//	IVisualParent* pParent = GetRParent();
								m_m_pWindowContainer->AddChild(pWindow);
							}
						}
							*/
					}
				}
				else
				{
				}
			}
#if 0
			{

				{
					CLXUIMenuElement* menu = new CLXUIMenuElement();
					menu->SetRParent(this);

					menu->SetOwnerWindow(get_OwnerWindow());

#if 0
					cpp::Type* pType = pD->LookupNamedType("FileObject");	// TODO

					std::map<StringA, cpp::Type*>::iterator it = pD->m_namedTypes.begin();
					while (it != pD->m_namedTypes.end())
					{
						cpp::Type* pType2 = (*it).second;
						ASSERT(pType2);

						if (pType2->m_type == cpp::type_class)
						{
							Dispatch2 dispatch(pType2);
							propertymap_t properties;

							GetProperties(dispatch, properties);

							std::map<StringA, Property*>::iterator it = properties.begin();
							while (it != properties.end())
							{
								Property* property = (*it).second;
								if (property->put_decl)
								{
									if (property->put_decl->m_pType->m_pFunction->m_parameters.size() == 1)
									{
										cpp::Type* arg = property->put_decl->m_pType->m_pFunction->m_parameters[0]->m_pType;
										if (arg)
										{
											if (arg->m_type == cpp::type_pointer)
											{
												if (arg->m_pPointerTo->m_type == cpp::type_class)
												{
													if (pType->m_pClass->IsOfType(arg->m_pPointerTo->m_pClass))
													{
														//cpp::Class* pClass = arg->m_pPointerTo->m_pClass;
														menu->AddItem(new TextString(ConvertA2S(pType2->m_pClass->m_name)), (long)property->put_decl);
													}
												}
											}
										}
									}
								}
								it++;
							}

						}

						it++;
					}
#endif

					cpp::Type* pType = pD->LookupNamedType("IViewOf");

					int count = pType->m_pClass->m_derived.size();
					for (int i = 0; i < count; i++)
					{
						cpp::Class* pClass = pType->m_pClass->m_derived[i];
						cpp::Scope* pScope = pD->LookupProc(pClass->m_name + "::GetType");

						if (pScope)
						{
							DWORD func = pScope->m_startAddress;
							Type_Info* ti;
							//typedef static Type_Info* (*f)();
							__asm
							{
								push eax
								call func
								mov ti,eax
								pop eax
							}

							menu->AddItem(new TextString(ConvertA2S(pClass->m_name)), (long)pClass);
						}
					}

					menu->GetMenuPopup()->Popup(menu, LDraw::Point(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));
				}
			}
#endif
		}
#endif
		else
			if (*evt->get_type() == *WSTR("groupby"))
		{
			m_table->Build(m_pCollection, m_table->m_pTree);
		}
		else if (*evt->get_type() == L"contextmenu")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			//m_groupBy.push_back(1);
			//Refresh(m_pCollection);
			/*
			CLXUIMenuElement* menu = new CLXUIMenuElement();
		//	menu->SetRParent(m_ctledit);
			menu->SetOwnerWindow(mouseEvt->GetOwnerWindow());

			menu->addEventListener(L"command", this, false);

			menu->AddItem(new TextString(L"Display As Table"), 100);

			menu->GetMenuPopup()->Popup(menu, LDraw::Point(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));
			*/
		}
		else if (*evt->get_type() == L"command")
		{
			evt->stopPropagation();
			CommandInvokeEvent* cmdEvt = dynamic_cast<CommandInvokeEvent*>(evt);

			ClassType* pClass = (ClassType*)cmdEvt->get_Command();

			//FileObject* pFile = m_pSelectedFile;//m_pDir->m_files[m_selection];//new FileObject(m_pDir->m_dirName + "\\" + m_pDir->m_files[m_selection].name);
			Object* pViewable = dynamic_cast<Object*>(m_pSelectedItem->m_userdata);

			void* obj = newobj(pClass);
			if (obj)
			{
				ASSERT(0);
				IViewOf* pView = NULL;//(IViewOf*)__RTDynamicCast(obj, 0, (void*)pClass->m_pTypeInfo/*pD->LookupSymbol(DecorateName(pClass->m_name))*/, (void*)&typeid(IViewOf), 0);
				if (pView)
				{
					Dispatch* dispatch = GetDispatch(pClass);

					dispatch->void_Invoke(obj, dispatch->GetMethod(ASTR("set_Viewable")), &pViewable, 4);

					if (pView)
					{
						ASSERT(0);
#if 0
						m_views.Add(pView);
#endif

						/*
						ChildWindow* pWindow = new ChildWindow;
						pWindow->put_Width(Length(200, Length::UnitAbsolute));
						pWindow->put_Height(Length(200, Length::UnitAbsolute));

						//pWindow->put_Content(dynamic_cast<Control*>(pView));

						pWindow->put_TitleText(OLESTR("Test"));
						*/

						/*
						if (false)
							m_m_pWindowContainer->AddChild(pWindow);
						else
						*/
						Control* pControl = dynamic_cast<Control*>(pView);
						if (pControl)
						{
								//m_pSelectedItem->put_Children(pWindow);
							m_pSelectedItem->set_Children(pControl);
						}
						else
						{
							MessageBoxA(NULL, "Not a control", "", MB_OK);
						}
					}
				}
				else
				{
					MessageBoxA(NULL, "failed to get IViewOf interface", "", MB_OK);
				}
			}
#if 0
			if (n == 0)
			{
#if 0
				ViewOfBitmap* ctl = new ViewOfBitmap(pFile);
				//ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
#endif
				// Group by viewable
				//pFile

				UI::ChildWindowContainer* pGroupCanvas = new UI::ChildWindowContainer;

				for (int i = 0; i < m_views.size(); i++)
				{
					IViewOf* pView = m_views[i];

				//* pViewable = m_groups[pView->get_Viewable()];

					if (pView->get_Viewable() == pFile)
					{

						ChildWindow* pFrame;
						IVisualParent* p = dynamic_cast<Control*>(pView)->GetRParent();
						while (p)
						{
							pFrame = dynamic_cast<ChildWindow*>(p);
							if (pFrame) break;

							p = dynamic_cast<IVisualParent*>(dynamic_cast<IVisualChild*>(p)->GetRParent());
						}

						pFrame->GetRParent()->RemoveRChild(pFrame);
						pGroum_pWindowContainer->AddChild(pFrame);
					}
				}

				ChildWindow* pWindow = new ChildWindow;
				pWindow->put_Width(Length(200, Length::UnitAbsolute));
				pWindow->put_Height(Length(200, Length::UnitAbsolute));

				pWindow->put_Content(pGroupCanvas);

				m_m_pWindowContainer->AddChild(pWindow);
			}
			else if (n == 1)
			{
				ViewOfMedia* ctl = new ViewOfMedia(pFile);
			//	ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
			}
			else if (n == 2)
			{
				FilterGraphObject* ctl = new FilterGraphObject(pFile);//MPEGFrames
				ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
			}
			else if (n == 3)
			{
				Filmstrip* ctl = new Filmstrip(pFile);//MPEGFrames
				//ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
			}
			else if (n == 4)
			{
				TextEditView* ctl = new TextEditView(pFile);//MPEGFrames
				//ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
			}
			else if (n == 5)
			{
				ZipArchiveView* ctl = new ZipArchiveView(pFile);//MPEGFrames
				//ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
			}
			else if (n == 6)
			{
				WaveformView* ctl = new WaveformView(pFile);
				ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
			}
			else if (n == 7)
			{
				MusicModuleView* ctl = new MusicModuleView(pFile);
				ctl->m_pCanvas = m_pCanvas;
				pView = ctl;
			}
#endif
		}
	}
#else
	ASSERT(0);
#endif
}
#endif

void FileObject::Open(PropertiesTable* table, TreeItem* item)
{
	if (m_FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (item->get_Children() == NULL)
		{
			ASSERT(0);
			DirectoryObject* pDir = NULL;//new DirectoryObject();//m_pDir->m_dirName + "/" + pFile->get_Name());
			pDir->SetDir(this);

			m_views.Add(pDir);

			//UI::TreeItemChildren* treechildren = new UI::TreeItemChildren(m_pTree);
			table->Build(pDir, item);	// TODO, only refresh current item
		}
	}
	else
	{
	}
}

}
