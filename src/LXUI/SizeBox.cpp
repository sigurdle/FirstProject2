#include "stdafx.h"
#include "LXUI2.h"
#include "SizeBox.h"

#include "Cursor.h"	// TODO remove

#include "DragContext.h"

#if AMIGA
#include "../amiga_header.h"
#endif

namespace System
{
namespace UI
{

extern UIEXT __live_object_ptr<LayoutManager> pLayoutManager;

#ifdef AMIGA

void DrawRectangle(Graphics* pGraphics, int x, int y, int width, int height);

#endif

//////////////////////////////////////////////////////////////////
// Gripper

Gripper::Gripper()
{
	//m_Content = NULL;

	//ASSERT(0);
#if 0
	{
		DataTemplate* pTemplate = new DataTemplate;
		XmlData::Document* document = new XmlData::Document;
#if WIN32
		StringW* filename = MakeFilePath(_Module, L"../../../Gripper.lxui");
		document->load(filename);

//		document->load(WSTR("C:/Gripper.lxui"));
#else
		document->load(WSTR("WinHD_C:/Gripper.lxui"));
#endif

		pTemplate->Load(document->get_documentElement());
		set_Template(pTemplate);
	}
#endif
}

UIElement* Gripper::get_Content() const
{
	return m_Content;
}

void Gripper::set_Content(UIElement* pContent)
{
	m_Content = pContent;
	//EnsureVisuals();

#if 0
	Border* pBorder0 = new Border;
	pBorder0->put_BorderThickness(Thickness(Length(1), Length(1), Length(1), Length(1)));
	/*
	pBorder0->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255));
	pBorder0->m_TopBrush = new SolidColorBrush(Color(255, 255, 255));
	pBorder0->m_RightBrush = new SolidColorBrush(Color(90, 90, 90));
	pBorder0->m_BottomBrush = new SolidColorBrush(Color(90, 90, 90));
	*/
	{
		Border* pBorder = new Border(Thickness(Length(3), Length(3), Length(3), Length(3)));
		pBorder->put_Background(new LinearGradientBrush(Color(240, 240, 240), Color(180, 180, 180), Point(0, 0), Point(0, 1)));

		{
			DockPanel* pPanel = new DockPanel;
			{
				{
					Border* pRect = new Border;
					pRect->put_BorderThickness(Thickness(Length(1), Length(1), Length(1), Length(1)));
					/*
					pRect->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255));
					pRect->m_TopBrush = new SolidColorBrush(Color(255, 255, 255));
					pRect->m_RightBrush = new SolidColorBrush(Color(90, 90, 90));
					pRect->m_BottomBrush = new SolidColorBrush(Color(90, 90, 90));
					*/
					{
						Border* pRect2 = new Border;
						pRect2->put_BorderThickness(Thickness(Length(1), Length(1), Length(1), Length(1)));
						pRect->put_Content(pRect2);
					}

					pPanel->put_Dock(pRect, DockPanel::Left);
					pPanel->AddRChild(pRect);
				}

				{
					Border* pRect = new Border;
				//	pRect->put_Width(new Length(20, Length::UnitAbsolute));
					pRect->put_BorderThickness(Thickness(Length(1), Length(1), Length(1), Length(1)));
				//	pRect->m_LeftBrush = new SolidColorBrush(new Color(255, 255, 255));
				//	pRect->m_RightBrush = new SolidColorBrush(new Color(90, 90, 90));

				//	pRect->put_Height(new Length(10, Length::UnitAbsolute));
					pPanel->put_Dock(pRect, DockPanel::Left);
					pPanel->AddRChild(pRect);
				}

				{
					pPanel->put_Dock(m_Content, DockPanel::Fill);
					pPanel->AddRChild(m_Content);
				}
			}
			pBorder->put_Content(pPanel);
		}
		pBorder0->put_Content(pBorder);
	}

	put_VisualTree(pBorder0);
#endif
}

#if 0
void Gripper::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);

			long screenX = mouseEvt->get_ScreenX();
			long screenY = mouseEvt->get_ScreenY();

			CDragContext drag;
			drag.m_pBar = m_Content;
			/*
			UIElement* p = dynamic_cast<UIElement*>(m_rparent);
			while (p)
			{
				if (pWindowBase)
				{
					drag.m_pBar =  pWindowBase;
					break;
				}
				p = dynamic_cast<UIElement*>(p->m_rparent);
			}
			*/

			if (drag.m_pBar)
			{
				drag.StartDrag(LDraw::PointI(screenX, screenY));
			}
			/*
			if (m_pOwnerWindow)
			{
				::SendMessage(m_pOwnerWindow->GetHwnd(), WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, MAKELPARAM(screenX, screenY));
			}
			*/
		}
	}
}
#endif

SizeBoxRubber::SizeBoxRubber()
{
}

#if 0
void SizeBoxRubber::handleEvent(Event* evt)
{
	ASSERT(0);
#if 0
	sysstring type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == WSTR("mousedown"))
		{
			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			long screenX = mouseEvt->get_ScreenX();
			long screenY = mouseEvt->get_ScreenY();

			Point* pClientPt = ScreenToClient(screenX, screenY);

			CDragContext drag;
			drag.m_pBar = NULL;
			UIElement* p = dynamic_cast<UIElement*>(GetRParent());
			while (p)
			{
				CUIFrameImpl* pWindowBase = dynamic_cast<CUIFrameImpl*>(p);
				if (pWindowBase)
				{
					drag.m_pBar = pWindowBase->m_pContent;
					break;
				}
				p = dynamic_cast<UIElement*>(p->GetRParent());
			}

			if (drag.m_pBar)
			{
#if WIN32
				if (pClientPt->get_Y() < 16)
				{
					drag.StartDrag(LDraw::PointI(screenX, screenY));
				}
				else
				{
					drag.StartResize(HTRIGHT, LDraw::PointI(screenX, screenY));
				}
#endif
			}
			/*
			if (m_pOwnerWindow)
			{
				::SendMessage(m_pOwnerWindow->GetHwnd(), WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, MAKELPARAM(screenX, screenY));
			}
			*/
		}
	}
#endif
}
#endif

SizeBox::SizeBox()
{
#if 0//WIN32
	set_Cursor(new Cursor(MSWindows::LoadCursorA(NULL, _IDC_SIZENWSE)));
#endif
}

SizeBox::~SizeBox()
{
}

LDraw::SizeD SizeBox::OnMeasure(LDraw::SizeD availSize)
{
	return LDraw::SizeD(16, 16);
}

#if 0
// virtual
void SizeBox::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);

			long screenX = mouseEvt->get_ScreenX();
			long screenY = mouseEvt->get_ScreenY();

			evt->stopPropagation();	// ??

#if WIN32

			CUIFrameImpl* pOwnerWindow = dynamic_cast<CUIFrameImpl*>(GetOwnerWindow()->m_pSite);
			if (pOwnerWindow)
			{
				MSWindows::Hwnd hwnd = pOwnerWindow->GetHwnd();
				hwnd.SendMessage(WM_NCLBUTTONDOWN, HTSIZE, MSWindows::MakeLPARAM(screenX, screenY));
			}

#if 0
		//	WindowBase* pOwnerWindow = get_OwnerWindow();
		//	CUIFrameImpl* pFrame = dynamic_cast<CUIFrameImpl*>(pOwnerWindow->m_pSite);
			FrameWindow* pFrame = NULL;
			UIElement* pVisual = dynamic_cast<UIElement*>(GetRParent());
			while (pVisual)
			{
				pFrame = dynamic_cast<FrameWindow*>(pVisual);
				if (pFrame)
					break;
				pVisual = dynamic_cast<UIElement*>(pVisual->GetRParent());
			}
			
		//	HWND hwnd = pOwnerWindow->GetHwnd();
			SetCapture();

			POINT oldpoint;
			oldpoint.x = screenX;
			oldpoint.y = screenY;

			double sx = -pFrame->m_computedSize.Width + screenX;
			double sy = -pFrame->m_computedSize.Height + screenY;

			bool bDone = false;
			MSG msg;
			while (GetMessageA(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);

				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					{
						POINT point;
						GetCursorPos(&point);

						double width = point.x - sx;
						double height = point.y - sy;

						pFrame->set_Width(new Length(width));
						pFrame->set_Height(new Length(height));

					//	TRACE("%f, %f\n", width, height);
#if 0
						::SetWindowPos(pFrame->m_hWnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
#endif

					//	pOwnerWindow->InvalidateMeasure();
					//	pOwnerWindow->Measure(LDraw::SizeD(0, 0));
					//	pOwnerWindow->Arrange(LDraw::SizeD(width, height));
						pFrame->InvalidateMeasure();
						pLayoutManager->MeasureAll();
						//pOwnerWindow->InvalidateArrange();
						pLayoutManager->RenderAll();
						/*
						if (!pFrame->m_invalidRect.IsEmptyArea())
						{
							pFrame->Render(pFrame->m_invalidRect);
							pFrame->m_invalidRect = LDraw::RectD();	// empty
						}
						*/

						oldpoint = point;
					}
					break;

				case WM_LBUTTONUP:
					{
						bDone = true;
					}
					break;

				case WM_CAPTURECHANGED:
					{
					}
					break;

				default:
					DispatchMessageA(&msg);
				}

				if (bDone)
					break;
			}

			ReleaseCapture();
			/*
			if (m_pOwnerWindow)
			{
				::SendMessage(m_pOwnerWindow->GetHwnd(), WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, MAKELPARAM(screenX, screenY));
			}
			*/
#endif
#elif AMIGA

			printf("TODO\n");
#if 0
		//	CUIFrameImpl* pOwnerWindow = dynamic_cast<CUIFrameImpl*>(get_OwnerWindow());
			WindowBase* pOwnerWindow = get_OwnerWindow();
			CUIFrameImpl* pFrame = dynamic_cast<CUIFrameImpl*>(pOwnerWindow->m_pSite);

			LDraw::Rect rect;
			pOwnerWindow->m_pSite->GetWindowRect(&rect);

			struct Window* pWindow = pFrame->GetHwnd();
			struct RastPort* rp = &pWindow->WScreen->RastPort;
			LDraw::PointI oldpoint(-rect.Width + screenX, -rect.Height + screenY);
		//	oldpoint.X = screenX;
		//	oldpoint.Y = screenY;

			// Draw initial
			if (p96GetBitMapAttr(rp->BitMap, P96BMA_ISP96))
			{
				LDraw::Bitmap bitmap(rp->BitMap);
				{
					LDraw::Graphics graphics(&bitmap);
					DrawRectangle(&graphics, rect.X, rect.Y, rect.Width, rect.Height);
				}
			}

			struct MsgPort* UserPort = pWindow->UserPort;
			bool bDone = false;
			while (!bDone)
			{
				int nSigMask = Wait(1<<UserPort->mp_SigBit);// | CONTROL_C);

				if (nSigMask & (1<<UserPort->mp_SigBit))
				{
				// As of V39 really is ExtIntuiMessage
					while (struct IntuiMessage* pMsg = (IntuiMessage*)GetMsg(UserPort))
					{
						if (!IsMsgPortEmpty(pUserPort))
						{
							struct IntuiMessage* pNextMsg = (struct IntuiMessage*)pUserPort->mp_MsgList.lh_Head;
							if (pMsg->Class == pNextMsg->Class)
							{
								if (pNextMsg->Class == IDCMP_MOUSEMOVE/* || pNextMsg->Class == IDCMP_NEWSIZE*/)
								{
							// Collect sequential
									ReplyMsg((struct Message*)pMsg);
									continue;
								}
							}
						}

						struct IntuiMessage msg = *pMsg;
						ReplyMsg((struct Message*)pMsg);

						if (msg.Class == IDCMP_MOUSEMOVE)
						{
							LDraw::PointI point(msg.IDCMPWindow->MouseX + msg.IDCMPWindow->LeftEdge, msg.IDCMPWindow->MouseY + msg.IDCMPWindow->TopEdge);

							if (p96GetBitMapAttr(rp->BitMap, P96BMA_ISP96))
							{
								LDraw::Bitmap bitmap(rp->BitMap);
								{
									// Erase previous
									LDraw::Graphics graphics(&bitmap);
									DrawRectangle(&graphics, rect.X, rect.Y, rect.Width, rect.Height);

									// Move and redraw
									point = LDraw::PointI(pWindow->MouseX + pWindow->LeftEdge, pWindow->MouseY + pWindow->TopEdge);

									rect.Width = point.X - oldpoint.X;
									rect.Height = point.Y - oldpoint.Y;

									DrawRectangle(&graphics, rect.X, rect.Y, rect.Width, rect.Height);
								}
							}

							/*
							m_pOwnerWindow->put_Width(new Length(m_pOwnerWindow->m_computedWidth + point.X - oldpoint.X, Length::UnitAbsolute));
							m_pOwnerWindow->put_Height(new Length(m_pOwnerWindow->m_computedHeight + point.Y - oldpoint.Y, Length::UnitAbsolute));

							m_pOwnerWindow->Measure(LDraw::SizeD(0, 0));
							m_pOwnerWindow->Arrange(LDraw::SizeD(m_pOwnerWindow->m_desiredWidth, m_pOwnerWindow->m_desiredHeight));
							*/

							//oldpoint = point;
						}
						else if (msg.Class == IDCMP_MOUSEBUTTONS)
						{
							bDone = true;
						}
						else
						{
							WindowUserData* pUserData = reinterpret_cast<WindowUserData*>(msg.IDCMPWindow->UserData);
							pUserData->pHandler(&msg, pUserData->pData);
						}
					}
				}
			}

		// Erase last
			if (p96GetBitMapAttr(rp->BitMap, P96BMA_ISP96))
			{
				LDraw::Bitmap bitmap(rp->BitMap);
				{
					LDraw::Graphics graphics(&bitmap);
					DrawRectangle(&graphics, rect.X, rect.Y, rect.Width, rect.Height);
				}
			}

			if (!pFrame->m_windowRect.Equals(rect))
			{
				pOwnerWindow->put_Width(new Length(rect.Width, Length::UnitAbsolute));
				pOwnerWindow->put_Height(new Length(rect.Height, Length::UnitAbsolute));

				pOwnerWindow->InvalidateMeasure();
			//	pOwnerWindow->Measure(LDraw::SizeD(0, 0));
			//	pOwnerWindow->Arrange(pOwnerWindow->m_desiredSize);

				pFrame->SetWindowRect(rect.X, rect.Y, rect.Width, rect.Height);
			//	m_pOwnerWindow->Render();
			}

#endif
		//	m_pOwnerWindow->Render();
#endif
		}
	}
}
#endif

}	// UI
}
