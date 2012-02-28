namespace System
{
namespace Gui
{

/*
class GUIEXT Number : public DependencyObject
{
public:
	DEPENDENCY_PROPERTY(float, Value)

	static DependencyClass* get_Class();
	static DependencyClass* pClass;
	typedef DependencyObject baseClass;
};

class DashPattern
{
public:
	vector<float>

};

class GUIEXT DashPatterns
{
public:
	DashPattern* get_Dash();

};
*/

class GUIEXT StrokeStyle : public DependencyObject
{
public:
	CTOR StrokeStyle();

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyValue, bool handled) override;

	DEPENDENCY_PROPERTY(CapStyle, StartCap)
	DEPENDENCY_PROPERTY(CapStyle, EndCap)
	DEPENDENCY_PROPERTY(CapStyle, DashCap)
	DEPENDENCY_PROPERTY(float, DashOffset)
	DEPENDENCY_PROPERTY(LineJoinStyle, LineJoin)
	DEPENDENCY_PROPERTY(float, MiterLimit)
	DEPENDENCY_PROPERTY(DashStyle, DashPattern)

	DEPENDENCY_CLASS(StrokeStyle, DependencyObject)

	ID2D1StrokeStyle* GetD2D1(Graphics::RenderTarget* rt);

private:

	ID2D1StrokeStyle* m_d2d1strokeStyle;
};

}	// Gui
}	// System
