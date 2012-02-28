namespace System
{
namespace Gui
{

class GUIEXT GradientBrush : public Brush
{
public:

	ID2D1GradientStopCollection* GetD2D1StopCollection(RenderContext* renderContext);

	DEPENDENCY_PROPERTY(GradientStopCollection*, Stops)

	DEPENDENCY_CLASS_ABSTRACT(GradientBrush, Brush)
//	static DependencyClass* get_Class();
//	static DependencyClass* pClass;

protected:

	CTOR GradientBrush(DependencyClass* depClass);

private:

	ID2D1GradientStopCollection* m_spGradientStopCollection;
};

}	// Gui
}	// System
