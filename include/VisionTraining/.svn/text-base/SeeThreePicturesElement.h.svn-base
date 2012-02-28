namespace System
{
namespace VisionTraining
{

class VISIONTRAININGEXT SeeThreePicturesElement : public Gui::FrameworkElement
{
public:
	CTOR SeeThreePicturesElement();

	virtual void Render(Gui::ManagedRenderContext renderContext) override;
	virtual void OnKey(Gui::KeyEventArgs* args) override;

	DEPENDENCY_PROPERTY(float, Dist)
	DEPENDENCY_PROPERTY(float, Delta)
	DEPENDENCY_PROPERTY(Gui::Visual*, Picture)

	static Gui::DependencyClass* get_Class();
	static Gui::DependencyClass* pClass;
};

}
}
