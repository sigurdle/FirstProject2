namespace System
{
namespace Gui
{

class GUIEXT ContentElement : public UIElement
{
public:

	CTOR ContentElement();

//	virtual gm::SizeF Arrange(gm::SizeF size) override;
	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	DEPENDENCY_PROPERTY(Object*, Content)

	DEPENDENCY_CLASS(ContentElement, UIElement)

	DEFINE_THIS(_ContentElement)

protected:

//	virtual void RenderRetained(ManagedRetainedRenderContext renderContext);

//	UIElement* m_element;
};

class _ContentElement : public _UIElement
{
public:

};

}
}
