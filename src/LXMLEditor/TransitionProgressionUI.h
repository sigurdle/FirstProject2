#ifndef __TRANSITIONPROGRESSIONUI_H_
#define __TRANSITIONPROGRESSIONUI_H_

namespace System
{
namespace LXmlEdit
{

class CTransitionProgressionUI;

class LXMLEDITEXT CTransitionProgressionUI : public UI::Control
{
public:
	CTransitionProgressionUI();
	~CTransitionProgressionUI();

	class Image : public UI::Control
	{
	public:
		Image(CTransitionProgressionUI* pUI)
		{
			m_pUI = pUI;
		}

		CTransitionProgressionUI* m_pUI;

		virtual void OnRender(UI::Graphics* pGraphics);
	};

	Image* m_image;
	System::StringW* m_type;
	System::StringW* m_subtype;
	long m_horzRepeat;
	long m_vertRepeat;
	
	LDraw::BBoxi m_previewRect;

	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/

	double get_progress() const;
	void set_progress(double newVal);
	bool get_reverse() const;
	void set_reverse(bool newVal);

	void SetTransition(System::StringW* type, System::StringW* subtype, long horzRepeat, long vertRepeat, long borderWidth, LDraw::Color borderColor);

	LDraw::Bitmap* m_bitmap[2];

protected:

	void handleEvent(System::Event* evt);

	friend class Image;

//	virtual void OnRender(UI::Graphics* pGraphics);

	UI::HorizontalSlider* m_progressCtrl;
	double m_progress;
	bool m_reverse;
};

}	// LXmlEdit
}

#endif //__TRANSITIONPROGRESSIONUI_H_
