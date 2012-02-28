#include "stdafx.h"
#include "LXUI2.h"
#include "LXUITitlebarElement.h"
#include "ChildWindow.h"
#include "Canvas.h"

#include <cfloat>

#if AMIGA
#include "../amiga_header.h"
#endif

namespace System
{
namespace UI
{

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> TitlebarStyle;

CLXUITitlebarElement::CLXUITitlebarElement()
{
	if (TitlebarStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../TitlebarStyle.lxui");
		document->load(filename);

		Type* returnType;
		TitlebarStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));

		/*
		ButtonStyle->Load(document->get_documentElement());
		*/
	}

	set_Style(TitlebarStyle);

	/*
	ApplyStyle(get_Style(), this);

	InitScript();
	*/
}

#if AMIGA

/*
void DrawRectangle(struct RastPort* rp, int x, int y, int width, int height)
{

}
*/

void DrawRectangle(Graphics* pGraphics, int x, int y, int width, int height)
{
	pGraphics->SetCompositingMode(LDraw::CompositingModeBitwiseXor);
	LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color::White);

	// top
	pGraphics->FillRectangle(brush, x, y, width, 1);
	// bottom
	pGraphics->FillRectangle(brush, x, y+height-1, width, 1);

	// left
	pGraphics->FillRectangle(brush, x, y+1, 2, height-2);
	// right
	pGraphics->FillRectangle(brush, x+width-2, y+1, 2, height-2);
}

#endif

// virtual
void CLXUITitlebarElement::OnMouseDown(MouseButtonEventArgs* args)
{
//	MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

//	Point clientposition = args->GetPosition(this);
	double screenX = args->GetScreenPosition().X;
	double screenY = args->GetScreenPosition().Y;

//	evt->stopPropagation();	// ??

//	TCHAR t[256];
//	GetWindowText(m_hWndParent, t, 256);

#if _WINDOWS
//	ReleaseCapture();	// ?? Just in case

#if 0
	RECT wrect;
	GetWindowRect(m_pOwnerWindow->GetHwnd(), &wrect);

	if (true)
	{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);

			switch (msg.message)
			{
			case WM_LBUTTONUP:
				{
					break;
				}
				break;

			case WM_MOUSEMOVE:
				{
					POINT point;
					point.x = (short)LOWORD(msg.lParam);
					point.y = (short)HIWORD(msg.lParam);

					ClientToScreen(m_pOwnerWindow->GetHwnd(), &point);

					MoveWindow(m_pOwnerWindow->GetHwnd(), point.x, point.y, wrect.right-wrect.left, wrect.bottom-wrect.top, TRUE);
				}
				break;

			default:
				DispatchMessage(&msg);
			}
		}
	}
	else
#endif

	if (false)
	{
		m_oldx = args->GetScreenPosition().X;
		m_oldy = args->GetScreenPosition().Y;

		CaptureMouse();
		m_dragging = true;
		return;
	}

	VisualContentSource* ownerWindow = GetOwnerWindow();
	HwndSource* pOwnerWindow = dynamic_cast<HwndSource*>(ownerWindow->m_pSite);
	if (pOwnerWindow)
	{
		MSWindows::Hwnd hwnd = pOwnerWindow->GetHwnd();
		hwnd.SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MSWindows::MakeLPARAM(screenX, screenY));
	}

#elif AMIGA

	NativeWindow* pOwnerWindow = dynamic_cast<NativeWindow*>(get_OwnerWindow()->m_pSite);
	if (pOwnerWindow)
	{
		LDraw::RectI rect;
		pOwnerWindow->GetWindowRect(&rect);

		struct Window* pWindow = pOwnerWindow->GetHwnd();
		LDraw::PointI oldpoint;
		oldpoint.X = screenX - rect.X;
		oldpoint.Y = screenY - rect.Y;

		LDraw::PointI point = LDraw::PointI(pWindow->MouseX + pWindow->LeftEdge, pWindow->MouseY + pWindow->TopEdge);
		int left;
		int top;
		left = point.X - oldpoint.X;
		top = point.Y - oldpoint.Y;

	//	LockLayerInfo(&pWindow->WScreen->LayerInfo);

		struct RastPort* rp = &pWindow->WScreen->RastPort;

		/*
		if (p96GetBitMapAttr(rp->BitMap, P96BMA_ISP96))
		{
			printf("p96\n");
		}
		*/

		AreaInfo areainfo;
		TmpRas tmpras;
		rp->AreaInfo = &areainfo;
		rp->TmpRas = &tmpras;

		InitTmpRas(&tmpras, (uint8*)execAllocMem(SysBase, 8000, MEMF_CHIP), 8000);
		InitArea(&areainfo, new uint8[(8+1)*5], 8+1);

		LDraw::GraphicsRP* pGraphicsRP = new LDraw::GraphicsRP(pWindow->WScreen->ViewPort.ColorMap, rp);
		Graphics* pGraphics = new Graphics(pGraphicsRP);

	//	SetDrMd(rp, COMPLEMENT);
		// Draw initial
		if (false)
		{
#if 0
			if (p96GetBitMapAttr(rp->BitMap, P96BMA_ISP96))
			{
				LDraw::Bitmap bitmap(rp->BitMap);
				{
					Graphics graphics(new LDraw::GraphicsO(&bitmap));
					DrawRectangle(&graphics, left, top, rect.Width, rect.Height);
				}
			}
#endif
		}
		DrawRectangle(pGraphics, left, top, rect.Width, rect.Height);

#if 0
		LDraw::Bitmap* pBitmap = NULL;
#endif
	//	LDraw::Bitmap* pTempBitmap = new Bitmap(rect.Width, rect.Height);
		struct MsgPort* UserPort = pWindow->UserPort;
		bool bDone = false;
		while (!bDone)
		{
			int nSigMask = execWait(SysBase, 1<<UserPort->mp_SigBit);// | CONTROL_C);

			if (nSigMask & (1<<UserPort->mp_SigBit))
			{
			// As of V39 really is ExtIntuiMessage
				while (struct IntuiMessage* pMsg = (IntuiMessage*)GetMsg(UserPort))
				{
					if (!IsMsgPortEmpty(pUserPort))
					{
						struct IntuiMessage* pNextMsg = (struct IntuiMessage*)pUserPort->mp_MsgList.lh_Head;
						if (pMsg->aos_Class == pNextMsg->aos_Class)
						{
							if (pNextMsg->aos_Class == IDCMP_MOUSEMOVE/* || pNextMsg->Class == IDCMP_NEWSIZE*/)
							{
						// Collect sequential
								ReplyMsg((struct Message*)pMsg);
								continue;
							}
						}
					}

					struct IntuiMessage msg = *pMsg;
					ReplyMsg((struct Message*)pMsg);

					if (msg.aos_Class == IDCMP_MOUSEMOVE)
					{
						if (false)
						{
#if 0
							if (p96GetBitMapAttr(rp->BitMap, P96BMA_ISP96))
							{
								LDraw::Bitmap bitmap(rp->BitMap);
								{
									Graphics graphics(new LDraw::GraphicsO(&bitmap));

									// Restore previous
									DrawRectangle(&graphics, left, top, rect.Width, rect.Height);
#if 0
									if (pBitmap)
									{
										//graphics.DrawImage(pBitmap, left, top);

										bitmap.CopyBitmapData(left, top, pBitmap, 0, 0, rect.Width, rect.Height);
										/*
										for (int y = 0; y < rect.Height; y++)
										{
											uint32* src = (uint32*)((uint8*)pBitmap->m_bitmapData + pBitmap->m_rowBytes * y);
											uint32* dst = (uint32*)((uint8*)bitmap.m_bitmapData + bitmap.m_rowBytes * (y+top) + (left)*4);

											for (int x = 0; x < rect.Width; x++)
											{
												*dst++ = *src++;
											}
										}
										*/
									}
									else
									{
										pBitmap = new LDraw::Bitmap(rect.Width, rect.Height);
									}
#endif
									// Move and redraw
									point = LDraw::PointI(pWindow->MouseX + pWindow->LeftEdge, pWindow->MouseY + pWindow->TopEdge);

									left = point.X - oldpoint.X;
									top = point.Y - oldpoint.Y;
									DrawRectangle(&graphics, left, top, rect.Width, rect.Height);
#if 0

								//	pBitmap = bitmap.Clone(LDraw::RectI(left, top, rect.Width, rect.Height));
									pBitmap->CopyBitmapData(0, 0, &bitmap, left, top, rect.Width, rect.Height);
#endif

									/*
									LDraw::Bitmap windowBitmap(m_pOwnerWindow->m_pBitmap);
									graphics.DrawImage(&windowBitmap, left, top);
									*/
									/*
									LDraw::SolidBrush brush(LDraw::Color(60, 60, 100, 190));
									graphics.FillRectangle(&brush, left, top, rect.Width, rect.Height);
									*/
								}
							}
#endif
						}
						else
						{
							// Restore previous
							DrawRectangle(pGraphics, left, top, rect.Width, rect.Height);

							// Move and redraw
							point = LDraw::PointI(pWindow->MouseX + pWindow->LeftEdge, pWindow->MouseY + pWindow->TopEdge);

							left = point.X - oldpoint.X;
							top = point.Y - oldpoint.Y;
							DrawRectangle(pGraphics, left, top, rect.Width, rect.Height);
						}
					}
					else if (msg.aos_Class == IDCMP_MOUSEBUTTONS)
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

		if (false)
		{
#if 0
			if (p96GetBitMapAttr(rp->BitMap, P96BMA_ISP96))
			{
				LDraw::Bitmap* bitmap = new LDraw::Bitmap(rp->BitMap);
				{
					Graphics graphics(new LDraw::GraphicsO(&bitmap));

					// Restore previous
					DrawRectangle(&graphics, left, top, rect.Width, rect.Height);
					/*
					if (pBitmap)
					{
						bitmap.CopyBitmapData(left, top, pBitmap, 0, 0, rect.Width, rect.Height);
					}
					*/
				}
			}
#endif
		}

		// Restore previous
		DrawRectangle(pGraphics, left, top, rect.Width, rect.Height);

	//	UnlockLayerInfo(&pWindow->WScreen->LayerInfo);

		//delete pTempBitmap;

		rp->AreaInfo = NULL;
		rp->TmpRas = NULL;

#if 0
		if (pBitmap)
		{
			delete pBitmap;
		}
#endif
		if (pOwnerWindow->m_windowRect.X != left || pOwnerWindow->m_windowRect.Y != top)
		{
			pOwnerWindow->SetWindowRect(left, top, rect.Width, rect.Height);
		}
	}
#endif
}

// virtual
void CLXUITitlebarElement::OnMouseUp(MouseButtonEventArgs* args)
{
	m_dragging = 0;
	ReleaseMouseCapture();
}

// virtual
void CLXUITitlebarElement::OnMouseMove(MouseEventArgs* args)
{
	if (m_dragging)
	{
		long dx = args->GetScreenPosition().X - m_oldx;
		long dy = args->GetScreenPosition().Y - m_oldy;

//				printf("Mover\n");

		UIElement* window = NULL;

		{
			Visual* pParent = GetRParent();
			while (pParent)
			{
				window = dynamic_cast<ChildWindow*>(pParent);
				if (window)
				{
					break;
				}

				pParent = pParent->GetRParent();
			}
		}

		if (window)
		{
		//	UIElement* parent = (UIElement*)window->GetRParent()->GetRParent();

			double left = Canvas::GetLeft(window);//window->m_computedLeft;
			if (_isnan(left)) left = 0;
			double top = Canvas::GetTop(window);//window->m_computedLeft;
			if (_isnan(top)) top = 0;

			Canvas::SetLeft(window, left + dx);
			Canvas::SetTop(window, top + dy);

		//	window->SetPosition(Canvas::GetLeft(window)->get_Value(), Canvas::GetTop(window)->get_Value());
		}

		m_oldx = args->GetScreenPosition().X;
		m_oldy = args->GetScreenPosition().Y;
	}
}

#if 0
// virtual
void CLXUITitlebarElement::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
		}
	}
}
#endif

}	// UI
}
