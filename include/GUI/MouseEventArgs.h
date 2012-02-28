//#ifndef UI_MouseEventArgs_h
//#define UI_MouseEventArgs_h

namespace System
{
namespace Gui
{

enum MouseButtonState
{
	MouseButtonState_Released = 0,
	MouseButtonState_Pressed = 1,
};

class GUIEXT MouseEventArgs : public InputEventArgs
{
public:
	CTOR MouseEventArgs(void* mouseDevice, int timestamp);

	Point GetPosition(UIElement* relativeTo);
	MouseButtonState get_LeftButton() const;
	MouseButtonState get_RightButton() const;
	MouseButtonState get_MiddleButton() const;
	MouseButtonState get_XButton1() const;
	MouseButtonState get_XButton2() const;

	Point GetScreenPosition() const
	{
		return m_screenpos;
	}

	Point GetClientPosition() const
	{
		return m_clientpos;
	}

	virtual void InvokeEventHandler(Object* genericTarget, IFunction* genericHandler);

//private:

	friend class InputManager;
//	friend class WindowBase;	// TODO remove
//	friend class VisualContentSource;	// TODO remove

//	float m_screenX;
//	float m_screenY;
//	float m_windowX;
//	float m_windowY;

	Point m_screenpos;
	Point m_clientpos;

	bool m_leftButton;
	bool m_rightButton;
	bool m_middleButton;
	bool m_XButton1;
	bool m_XButton2;
};

}	// UI
}

//#endif // UI_MouseEventArgs_h
