#include "stdafx.h"
#include "UIMedia.h"
#include "MediaPlayer.h"

//#include "Video.h"

namespace System
{
namespace UI
{

MediaPlayer::MediaPlayer(MediaShow::IMediaSeeking* pSeeking, UIElement* pContent)
{
	m_Seeking = pSeeking;
	m_Content = pContent;
	m_MediaControl = dynamic_cast<IMediaControl*>(m_Content);
	m_Slider = new Slider(Orientation_Horizontal);

	m_Slider->get_ValueChanged().connect(bind1st_of_3(mem_fun2(&MediaPlayer::OnPositionValueChanged), this));

	LONGLONG duration;
	m_Seeking->GetDuration(MediaShow::TimeFormat_ref, &duration);
	double m_duration = duration / (double)TIME_SCALE;

//	m_Slider->set_Maximum(0, m_duration+1, 1);
	m_Slider->set_Maximum(m_duration);

	m_Slider->set_Height(16);

	DockPanel* panel = new DockPanel;
	{
		DockPanel* panel2 = new DockPanel;
		{
			{
				Button* button = new Button(new TextString(WSTR(">")));

				button->get_Click().connect(bind1st_of_3(mem_fun2(&MediaPlayer::OnPlay), this));

				DockPanel::SetDock(button, DockPanel::Left);
				panel2->AddChild(button);
			}

			/*
			{
				Button* button = new Button(new TextString(L">"));
				DockPanel::put_Dock(button, DockPanel::Left);
				panel2->AddRChild(button);
			}
			*/

			{
				DockPanel::SetDock(m_Slider, DockPanel::Fill);
				panel2->AddChild(m_Slider);
			}
		}
		DockPanel::SetDock(panel2, DockPanel::Bottom);
		panel->AddChild(panel2);
	}
	{
		DockPanel::SetDock(m_Content, DockPanel::Fill);
		panel->AddChild(m_Content);
	}

	set_VisualTree(panel);

#if 0//WIN32
	Create(NULL, LDraw::RectI(), NULL, WS_POPUP);
	SetTimer(1, 100);
#endif
}

void MediaPlayer::OnTimer(UINT)
{
	MediaShow::IMediaSeeking* seeking = m_Seeking;
	LONGLONG pos;
	seeking->GetCurrentPosition(MediaShow::TimeFormat_ref, &pos);

	m_setValue = true;
	m_Slider->set_Value((double)pos / TIME_SCALE);
	m_setValue = false;
}

void MediaPlayer::OnPositionValueChanged(Object* sender, RoutedPropertyChangedEventArgs<double>* args)
{
	if (!m_setValue)
	{
		MediaShow::IMediaSeeking* seeking = m_Seeking;//dynamic_cast<LMedia::IMediaSeeking*>(m_Video->get_FilterGraph());
		seeking->Seek(MediaShow::TimeFormat_ref, args->get_NewValue() * TIME_SCALE);
	}
}

void MediaPlayer::OnPlay(Object* sender, RoutedEventArgs* args)
{
	if (m_MediaControl->GetState() != MediaControlState_Running)
	{
	//	SetTimer(75, bind1st_of_2(mem_fun(&MediaPlayer::OnTimer), this));
		m_MediaControl->Run();
	}
	else
	{
		VERIFY(0);
		m_MediaControl->Pause();
	}
}

#if 0
// virtual
void MediaPlayer::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"click")
		{
			if (m_MediaControl->GetState() != MediaControlState_Running)
			{
				m_MediaControl->Run();
			}
			else
			{
				m_MediaControl->Pause();
			}

			/*
			UIElement* p = dynamic_cast<UIElement*>(GetRParent());
			while (p)
			{
				IMediaControl* mediaControl = dynamic_cast<IMediaControl*>(p);
				if (mediaControl)
				{
					mediaControl->Run();
					break;
				}
				p = dynamic_cast<UIElement*>(p->GetRParent());
			}
			*/

			/*
			LMedia::ILMediaSeeking* seeking = dynamic_cast<LMedia::ILMediaSeeking*>(m_Video->get_FilterGraph());
			ULONG frame = seeking->GetCurrentPosition(1);

			seeking->Seek(1, frame+1);

			LONGLONG pos = seeking->GetCurrentPosition((DWORD)0);
			double fpos = pos / (double)LTIME_SCALE;
			m_Slider->put_pos(fpos);
			*/
		}
		else if (*evt->get_type() == L"timer")
		{
			evt->stopPropagation();

			MediaShow::IMediaSeeking* seeking = m_Seeking;//dynamic_cast<LMedia::IMediaSeeking*>(m_Video->get_FilterGraph());
			LONGLONG pos;
			seeking->GetCurrentPosition(MediaShow::TimeFormat_ref, &pos);
			double fpos = pos / (double)TIME_SCALE;

			m_Slider->set_Value(fpos);
		}
		else if (*evt->get_type() == L"posChange")
		{
			evt->stopPropagation();
			SliderEvent* sliderEvt = static_cast<SliderEvent*>(evt);

			MediaShow::IMediaSeeking* seeking = m_Seeking;//dynamic_cast<LMedia::IMediaSeeking*>(m_Video->get_FilterGraph());
			seeking->Seek(MediaShow::TimeFormat_ref, sliderEvt->m_pos * TIME_SCALE);

			/*
			{
				UI::Event* evt = new UI::Event;
				evt->initEvent(L"propertychanged", false, false);
				m_Content->dispatchEvent(evt);
			}
			*/
		}
#if 0
		CComPtr<ILDOMEventTarget> target;
		evt->get_target(&target);
		CComQIPtr<ILXUIElement> targetElement = target;

		if (!wcscmp(type, L"mousedown"))
		{
			m_xoffset = 0;
			m_yoffset = 0;

			CComBSTR id;
			targetElement->get_ID(&id);

			if (!wcscmp(id, L"1"))
			{
				m_dragging = 1;
			}
			else if (!wcscmp(id, L"2"))
			{
				m_dragging = 2;
			}
			else if (!wcscmp(id, L"3"))
			{
				m_dragging = 3;
			}

			if (m_dragging)
			{
				CComQIPtr<ILViewNode> v(m_VisualTree);
				CLDependencyObjectImpl* pViewport = static_cast<CLDependencyObjectImpl*>(v.p)->GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"X3DViewport", TRUE);
				ATLASSERT(pViewport);
				if (pViewport)
				{
					//static_cast<CLXUIX3DViewport*>(pViewport)->m_sceneRenderer->BeginMove();
				}
			}
		}
		else if (!wcscmp(type, L"DragDelta"))
		{
			_variant_t HorizontalChange = GetProperty(evt, L"HorizontalChange");
			_variant_t VerticalChange = GetProperty(evt, L"VerticalChange");

			m_xoffset += (double)HorizontalChange;
			m_yoffset += (double)VerticalChange;

			{
				CComQIPtr<ILViewNode> v(m_VisualTree);
				CLDependencyObjectImpl* pViewport = static_cast<CLDependencyObjectImpl*>(v.p)->GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"X3DViewport", TRUE);
				ASSERT(pViewport);
				if (pViewport)
				{
				//	static_cast<CLXUIX3DViewport*>(pViewport)->m_sceneRenderer->Move(m_dragging, CPoint(m_xoffset, m_yoffset));
				}
			}

		//	RecalculateParentBounds();
		}
#endif
	}
}
#endif

#if 0//WIN32

bool MediaPlayer::ProcessWindowMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
{
	if (uMsg == WM_TIMER)
	{
		__live_object_ptr<System::Event> evt = new System::Event;
		evt->InitEvent(WSTR("timer"), false, false);
		dispatchEvent(evt);
		return true;
	}

	return false;
}
#endif

void MediaPlayer::DoneLoad()
{
#if 0
	CComQIPtr<ILViewNode> v(m_VisualTree);
	CComQIPtr<ILXUIVideo> pVideo = (CPNode*)static_cast<CLDependencyObjectImpl*>(v.p)->GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"Video", TRUE);
	ATLASSERT(pVideo);
	if (pVideo)
	{
		pVideo->put_Source(m_Source);

		CComQIPtr<ILMediaSeeking> seeking = static_cast<CLXUIVideo*>(pVideo.p)->m_filterGraph;
		LONGLONG duration;
		seeking->GetDuration(&duration);
		double m_duration = duration / (double)LTIME_SCALE;

		{
			CComQIPtr<ILViewNode> v(m_VisualTree);
			CComQIPtr<ILXUITextBox> pText = (CPNode*)static_cast<CLDependencyObjectImpl*>(v.p)->GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"TextBox", TRUE);
			ATLASSERT(pText);
			if (pText)
			{
				WCHAR buf[16];
				swprintf(buf, L"%g seconds", m_duration);

				pText->put_textContent(buf);
			}
		}

		static_cast<CLXUIVideo*>(pVideo.p)->m_filterGraph->Run();
	}
#endif
}

#if 0
STDMETHODIMP MediaPlayer::get_Source(/*[out,retval]*/ BSTR *pVal)
{
	return m_Source.CopyTo(pVal);
}
#endif

void MediaPlayer::set_Source(StringW* newVal)
{
	m_Source = newVal;

	ASSERT(0);

#if 0
	m_Video->put_Source(m_Source);

	LMedia::IMediaSeeking* seeking = dynamic_cast<LMedia::IMediaSeeking*>(m_Video->get_FilterGraph());
	LONGLONG duration;
	seeking->GetDuration(LMedia::TimeFormat_ref, &duration);
	double m_duration = duration / (double)LTIME_SCALE;

	m_Slider->SetInfo(0, m_duration+1, 1);
#endif
}

}	// UI
}
