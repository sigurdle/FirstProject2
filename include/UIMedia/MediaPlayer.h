#ifndef __UI_MediaPlayer_h__
#define __UI_MediaPlayer_h__

//#include "resource.h"       // main symbols

//#include "Control.h"

namespace System
{

	/*
namespace Media
{
	class IMediaSeeking;
}
*/

namespace UI
{

class UIMediaExt MediaPlayer : public Control
{
public:
	CTOR MediaPlayer(MediaShow::IMediaSeeking* pMedia, UI::UIElement* pContent);

	void set_Source(System::StringW* newVal);

protected:

	void DoneLoad();

	void OnTimer(UINT);
	void OnPlay(Object* sender, RoutedEventArgs* args);
	void OnPositionValueChanged(Object* sender, RoutedPropertyChangedEventArgs<double>* args);

	bool m_setValue;

//	virtual void handleEvent(System::Event* evt);

#if 0
#if WIN32
	virtual bool ProcessWindowMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ );
#endif
#endif

	System::StringW* m_Source;

	UIElement* m_Content;
	IMediaControl* m_MediaControl;
	MediaShow::IMediaSeeking* m_Seeking;
	Slider* m_Slider;
};

}	// UI
}

#endif //__UI_MediaPlayer_h__
