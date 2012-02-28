namespace System
{
namespace VisionTraining
{

class VISIONTRAININGEXT JumpDuctionElement : public Gui::FrameworkElement
{
public:
	CTOR JumpDuctionElement();

	virtual void Render(Gui::ManagedRenderContext renderContext) override;
	virtual void OnKey(Gui::KeyEventArgs* args) override;

	DEPENDENCY_PROPERTY(float, InDist)
	DEPENDENCY_PROPERTY(float, OutDist)
	DEPENDENCY_PROPERTY(bool, InMode)
	DEPENDENCY_PROPERTY(float, Delta)
	DEPENDENCY_PROPERTY(Gui::Color*, LeftEyeColor)
	DEPENDENCY_PROPERTY(Gui::Color*, RightEyeColor)
	DEPENDENCY_PROPERTY(float, Darken)

	static Gui::DependencyClass* get_Class();
	static Gui::DependencyClass* pClass;

private:

	Gui::Brush* m_leftEyeBrush;
	Gui::Brush* m_rightEyeBrush;
	Gui::Brush* m_mixEyeBrush;
};

}
}
