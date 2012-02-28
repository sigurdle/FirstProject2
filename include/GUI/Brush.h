namespace System
{
namespace Gui
{

class GUIEXT Brush : public DependencyObject
{
public:

	virtual ID2D1Brush* Create(RenderContext* renderContext, Visual* refVisual) = 0;
	virtual ID2D1Brush* GetBrush() = 0;

	virtual bool IsFullyOpaque()
	{
		return false;
	}

	DEPENDENCY_CLASS_ABSTRACT(Brush, DependencyObject)

	DEPENDENCY_PROPERTY(float, BrushOpacity)

protected:

	CTOR Brush(DependencyClass* depClass);
	CTOR Brush(DependencyClass* depClass, float opacity);
};

}	// Gui
}	// System
