namespace System
{
namespace Gui
{

class GUIEXT Popup : public FrameworkElement
{
public:

	CTOR Popup();

	DEPENDENCY_CLASS(Popup, FrameworkElement)

	DEPENDENCY_PROPERTY_RW(UIElement*, Child)
	DEPENDENCY_PROPERTY_RW(bool, IsOpen)
	DEPENDENCY_PROPERTY_RW(bool, StaysOpen)
	DEPENDENCY_PROPERTY_RW(PopupAnimation, PopupAnimation)

protected:

	class PopupWindow : public PlatformWindowSite
	{
	public:
		CTOR PopupWindow(Popup* owner) : m_owner(owner)
		{
		}

		inline Popup* get_Owner() const throw()
		{
			return m_owner;
		}

		virtual gm::RectI GetRect() override;
		virtual void OnWindowPosChanged(float left, float top) override;
		virtual void OnWindowSizeChanged(float width, float height) override;
		virtual void OnLostMouseCapture(PlatformWindowProxy) override;

		virtual void SetActive(bool) override
		{
		}

		virtual void set_State(int) override
		{
		}

		virtual void set_InSizeMove(bool) override
		{
		}

		virtual UIElement* GetRootWindow() override
		{
			return m_owner;
		}

		virtual UIElement* GetRootElement() override
		{
			return m_owner->get_Child();
		}

		virtual bool get_CanMinimize() override
		{
			return false;
		}

		virtual bool get_CanMaximize() override
		{
			return false;
		}

		virtual bool get_Topmost() override
		{
			return false;
		}

		virtual geometry get_Clip() override
		{
			return nullptr;
		}

		virtual String get_RT() override
		{
			return S("Direct3D");
		}

		virtual String get_TitleText() override
		{
			return nullptr;
		}

		virtual Window* get_Owner() override
		{
			return nullptr;
		}

		virtual float GetOpacity() override
		{
			return m_owner->get_Opacity();
		}

		Popup* m_owner;
		gm::RectI m_windowRect;
	};

	void OpenIt(gm::PointI mousepos);

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;
	virtual void OnMouseButtonDown(MouseButtonEventArgs* args) override;

	PopupWindow* m_window;
};

}	// Gui
}	// System
