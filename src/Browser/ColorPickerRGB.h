#ifndef __ColorPickerRGB_h__
#define __ColorPickerRGB_h__

namespace System
{

class ColorPickerRGB : public UI::Control
{
public:

	CTOR ColorPickerRGB();

	void UpdateControls();

protected:
//	void handleEvent(System::Event* evt);

public:
	UI::ColorSlider* m_slider[3];
	UI::TextEdit* m_edit[3];
};

}

#endif // __ColorPickerRGB_h__
