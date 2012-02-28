#include "stdafx.h"
#include "LXUI2.h"

#include "LXUITitlebarElement.h"

#include "LXUIWindow.h"
//#include "UIFrameImpl.h"

#include "UIFloatingFrame.h"

namespace System
{
namespace UI
{

extern void CalcBorders(LDraw::RectI* lpClientRect/*, DWORD dwStyle = WS_THICKFRAME | WS_CAPTION, DWORD dwExStyle = 0*/);

#if 0
UIElement* Window::get_Content()
{
	return m_pContent;
}

void Window::set_Content(UIElement* content)
{
	m_pContent = content;
	PropertyChanged(ASTR("Content"));
//	EnsureVisuals();

#if 0
//	DropShadow* p = new DropShadow;
//	{
		m_pBorder = new Border;
		m_pBorder->set_BorderThickness(Thickness(Length(1), Length(1), Length(1), Length(1)));

		/*
		pBorder->m_LeftBrush = new CLLinearGradientBrush(new Color(255, 255, 255), new Color(190, 190, 190), new Point(0, 0), new Point(0, 1));
		pBorder->m_TopBrush = new CLLinearGradientBrush(new Color(255, 255, 255), new Color(190, 190, 190), new Point(0, 0), new Point(1, 0));
		pBorder->m_RightBrush = new CLLinearGradientBrush(new Color(190, 190, 190), new Color(0, 0, 0), new Point(0, 0), new Point(0, 1));
		pBorder->m_BottomBrush = new CLLinearGradientBrush(new Color(190, 190, 190), new Color(0, 0, 0), new Point(0, 0), new Point(1, 0));
		*/
		m_pBorder->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255));
		m_pBorder->m_TopBrush = new SolidColorBrush(Color(255, 255, 255));
		m_pBorder->m_RightBrush = new SolidColorBrush(Color(80, 80, 80));
		m_pBorder->m_BottomBrush = new SolidColorBrush(Color(80, 80, 80));

#if 1

		{
			m_pBorder2 = new Border;
			m_pBorder2->put_Background(new SolidColorBrush(Color(102, 136, 187)));
		//	pBorder2->m_LeftBrush = new SolidColorBrush(new Color(102, 136, 187));
		//	pBorder2->m_TopBrush = new SolidColorBrush(new Color(102, 136, 187));
		//	pBorder2->m_RightBrush = new SolidColorBrush(new Color(102, 136, 187));
		//	pBorder2->m_BottomBrush = new SolidColorBrush(new Color(102, 136, 187));
			m_pBorder2->put_BorderThickness(Thickness(Length(2), Length(2), Length(2), Length(2)));
			{
				DockPanel* pDockPanel = new DockPanel;
				{
					{
						Border* pBorder = new Border;
					//	pBorder->put_BorderThickness(new Thickness(new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute)));
					//	pBorder->put_BackgroundBrush(new SolidColorBrush(new Color(102, 136, 187)));
						{
							DockPanel* pDockPanel2 = new DockPanel;
							{
								{
									m_CloseButton = new Button(new TextString(WSTR("X")));
									pDockPanel2->put_Dock(m_CloseButton, DockPanel::Right);
									pDockPanel2->AddRChild(m_CloseButton);
								}
								{
									m_MinimizeButton = new Button(new TextString(WSTR("-")));
									pDockPanel2->put_Dock(m_MinimizeButton, DockPanel::Right);
									pDockPanel2->AddRChild(m_MinimizeButton);
								}

								{
									CLXUITitlebarElement* pTitlebar = new CLXUITitlebarElement();

									Border* pCanvas = new Border;
									pCanvas->put_BorderThickness(Thickness(Length(2), Length(2), Length(2), Length(2)));
									//pCanvas->put_BackgroundBrush(new SolidColorBrush(new Color(102, 136, 187)));
									{
										//m_Title = new TextString(WSTR(""));
										//m_Title->put_TextFill(new SolidColorBrush(new Color(255, 255, 255)));

										pCanvas->put_Content(m_Title);
									}
									pTitlebar->put_VisualTree(pCanvas);

									pDockPanel2->put_Dock(pTitlebar, DockPanel::Fill);
									pDockPanel2->AddRChild(pTitlebar);
								}
							}
							pBorder->put_Content(pDockPanel2);
						}
						pDockPanel->AddRChild(pBorder);
					}
				}

				{
					SizeBox* p = new SizeBox();

				//	p->put_Height(new Length(16, Length::UnitAbsolute));

					{
						Border* pRect = new Border();
					//	pRect->put_Width(new Length(1, Length::UnitPercentage));
					//	pRect->put_Height(new Length(16, Length::UnitAbsolute));
					//	pRect->put_BackgroundBrush(new SolidColorBrush(new Color(255, 136, 187)));
					//	pRect->put_Content(new TextString(L"Size"));

						p->put_VisualTree(pRect);
					}

					pDockPanel->put_Dock(p, DockPanel::Bottom);

					pDockPanel->AddRChild(p);
				}

				{
					pDockPanel->put_Dock(content, DockPanel::Fill);

					pDockPanel->AddRChild(content);
				}
				m_pBorder2->put_Content(pDockPanel);
			}
			m_pBorder->put_Content(m_pBorder2);
		}
	//	p->put_Content(pBorder);
	//}
#endif

	put_VisualTree(m_pBorder);

#if 0
	DockPanel* pDockPanel = new DockPanel;
	{
		{
			CLXUITitlebarElement* p = new CLXUITitlebarElement;
			p->put_Height(new Length(16, Length::UnitAbsolute));

			{
				CLXUICanvas* pCanvas = new CLXUICanvas;
				pCanvas->put_Width(new Length(1, Length::UnitPercentage));
				pCanvas->put_Height(new Length(1, Length::UnitPercentage));

				{
					CLXUIRectangle* pRect = new CLXUIRectangle();
					pRect->put_RectangleWidth(new Length(1, Length::UnitPercentage));
					pRect->put_RectangleHeight(new Length(1, Length::UnitPercentage));
					pRect->put_Fill(new SolidColorBrush(new Color(102, 136, 187)));

					pCanvas->AddRChild(pRect);
				}
				{
					m_Title = new TextString(WSTR(""));

					pCanvas->AddRChild(m_Title);
				}
				p->put_VisualTree(pCanvas);
			}
/*
			{
				CLXUIRectangle* pRect = new CLXUIRectangle();
				pRect->m_computedLeft = 0;
				pRect->m_computedTop = 0;
				pRect->put_RectangleWidth(new Length(1, UnitPercentage));
				pRect->put_RectangleHeight(new Length(16, UnitAbsolute));
				pRect->put_Fill(new CLSolidColorBrush(new CLColor(102, 136, 187)));

				p->put_VisualTree(pRect);
			//	p->appendChild(pRect);
			}
			*/

			pDockPanel->put_Dock(p, DockPanel::Top);
			pDockPanel->AddRChild(p);
		}

		{
			SizeBox* p = new SizeBox;
			p->put_Height(new Length(16, Length::UnitAbsolute));

			{
				CLXUICanvas* pCanvas = new CLXUICanvas;
				pCanvas->put_Width(new Length(1, Length::UnitPercentage));
				pCanvas->put_Height(new Length(1, Length::UnitPercentage));

				{
					CLXUIRectangle* pRect = new CLXUIRectangle();
					pRect->put_RectangleWidth(new Length(1, Length::UnitPercentage));
					pRect->put_RectangleHeight(new Length(1, Length::UnitPercentage));
					pRect->put_Fill(new SolidColorBrush(new Color(102, 136, 187)));

					pCanvas->AddRChild(pRect);
				}
				{
				//	m_Title = new TextString(WSTR(""), font);
					/*
					pRect->m_computedLeft = 0;
					pRect->m_computedTop = 0;
					pRect->put_RectangleWidth(new Length(1, UnitPercentage));
					pRect->put_RectangleHeight(new Length(16, UnitAbsolute));
					pRect->put_Fill(new CLSolidColorBrush(new CLColor(102, 136, 187)));
					*/

				//	pCanvas->appendChild(m_Title);
				}
				p->put_VisualTree(pCanvas);
			}
/*
			{
				CLXUIRectangle* pRect = new CLXUIRectangle();
				pRect->m_computedLeft = 0;
				pRect->m_computedTop = 0;
				pRect->put_RectangleWidth(new Length(1, UnitPercentage));
				pRect->put_RectangleHeight(new Length(16, UnitAbsolute));
				pRect->put_Fill(new CLSolidColorBrush(new CLColor(102, 136, 187)));

				p->put_VisualTree(pRect);
			//	p->appendChild(pRect);
			}
			*/

			pDockPanel->put_Dock(p, DockPanel::Bottom);
			pDockPanel->AddRChild(p);
		}

		pDockPanel->put_Dock(pContent, DockPanel::Fill);
		pDockPanel->AddRChild(pContent);
	}
	pDockPanel->SetOwnerWindow(this);
	put_VisualTree(pDockPanel);
#endif
#endif
}
#endif

//////////////////////////////////////////////////////////////////////
// CLXUIWindow

CLXUIWindow::CLXUIWindow()
{
	m_closed = true;
//	m_Resources = NULL;
}

bool CLXUIWindow::CanDock(UIElement* pVisual)
{
	return true;
}

void CLXUIWindow::DrawFocusRect(MSWindows::HDC hDC, LDraw::RectI rectDragHorz, LDraw::RectI rectFrameDragHorz)
{
	CalcBorders(&rectFrameDragHorz);
}

void CLXUIWindow::DockControlBar(UIElement* pBar, LDraw::RectI* lpRect)
{
	ASSERT(0);
#if 0
	if (pBar->m_pDockParent == this)
	{
		CUIFloatingFrame* pFrame = dynamic_cast<CUIFloatingFrame*>(pBar->GetParent());
		pFrame->SetWindowRect(lpRect->X, lpRect->Y, lpRect->Width, lpRect->Height);//, SWP_NOZORDER | SWP_NOSIZE);
	}
	else
	{
		CUIFloatingFrame* pFrame = new CUIFloatingFrame;

		if (pBar->m_pDockParent != NULL)
		{
			pBar->m_pDockParent->RemoveControlBar(pBar);
		}

		if (pBar->GetRParent())
		{
			pBar->GetRParent()->RemoveRChild(pBar);
		}

		AddRChild(pFrame);
		pFrame->put_Content(pBar);

		pBar->m_pDockParent = this;

		pFrame->Show();

		pFrame->SetWindowRect(lpRect->X, lpRect->Y, lpRect->Width+100, lpRect->Height+100);
		pFrame->Arrange(LDraw::SizeD(lpRect->Width, lpRect->Height));
	}
#endif
}

void CLXUIWindow::RemoveControlBar(UIElement* pBar)
{
	CUIFloatingFrame* pFrame = dynamic_cast<CUIFloatingFrame*>(pBar->GetParent());
	if (pFrame)
	{
		pBar->GetRParent()->RemoveRChild(pBar);	// ??
		ASSERT(0);
#if 0
		pFrame->DestroyWindow();
#endif
	}
}

#if 0

#if _WINDOWS

LRESULT CLXUIWindow::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	BOOL bActive = wParam;

	if (TRUE/*(GetStyle() & MFS_SYNCACTIVE) == 0*/)
	{
		/*
		if (afxData.bSmCaption)
			return Default();
			*/

		if (pData->m_bActive != bActive)
		{
			pData->m_bActive = bActive;
			SendMessage(hWnd, WM_NCPAINT, 0, 0);
		}
	}
	/*
	else if (m_nFlags & WF_KEEPMINIACTIVE)
	{
		return FALSE;
	}*/
	return TRUE;
#endif

//	CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMElementImplImpl>(m_element)->m_pNodes[0];

	bool bActive = (bool)wParam;

	if (FALSE)	// Stay active
		bActive = TRUE;

	// but do not stay active if the window is disabled
	if (!IsWindowEnabled())
		bActive = FALSE;

	if (m_bFocus != bActive)
	{
		m_bFocus = bActive;
#if 0
		GetCSSPropertiesAndChildren();
		((CLXUIDocumentView*)m_pView)->CalcDims(this);
#endif

		// ??
	//	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	//	SendMessage(WM_NCPAINT);
	}

	return TRUE;
//	return DefWindowProc(uMsg, bActive, 0/*lParam*/);
}

LRESULT CLXUIWindow::OnEnterSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<ILDOMElement> element(m_pNode);

	if (m_nHitTest == HTCAPTION)
	{
//		element->setAttribute(L"dragging", L"true");
	}
	else if (m_nHitTest >= HTSIZEFIRST && m_nHitTest <= HTSIZELAST)
	{
//		element->setAttribute(L"sizing", L"true");
	}

	return 0;
}

LRESULT CLXUIWindow::OnExitSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_nHitTest == HTCAPTION)
	{
//		element->removeAttribute(L"dragging");
	}
	else if (m_nHitTest >= HTSIZEFIRST && m_nHitTest <= HTSIZELAST)
	{
//		element->removeAttribute(L"sizing");
	}

	return 0;
}
#endif // _WINDOWS
#endif

#if 0
STDMETHODIMP CLXUIWindow::CreateInParent(ULONG_PTR hwnd)
{
	CRect rect(0, 0, 0, 0);//m_computedLeft, m_computedTop, m_computedLeft+m_computedWidth, m_computedTop+m_computedHeight);

#if 0
	Create((HWND)hwnd, rect, NULL, WS_CHILD | WS_VISIBLE, 0/*WS_EX_TRANSPARENT*/);
#endif

	return S_OK;
//	return baseClass::Show();
}
#endif

void CLXUIWindow::close()
{
	if (!m_closed)
	{
		m_closed = true;
	}
}

/*
bool CLXUIWindow::get_closed()
{
	return m_closed;
}
*/

int CLXUIWindow::doModal()
{
	// TODO: Add your implementation code here

	return 0;
}

#if 0
CLXUIElementImpl* CLXUIWindow::get_Resources()
{
	return m_Resources;
}

void CLXUIWindow::put_Resources(CLXUIElementImpl *newVal)
{
	m_Resources = newVal;
}
#endif

}	// UI
}
