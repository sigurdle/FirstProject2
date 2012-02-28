namespace System
{
namespace Gui
{

typedef pair<float, ColorF> ColorStop;

class GUIEXT GradientStopCollection : public DependencyObject
{
public:

	CTOR GradientStopCollection();
	CTOR GradientStopCollection(ColorF color1, ColorF color2);

	ColorStop GetAt(uint index)
	{
		return ColorStop(m_offsets[index], m_colors[index]);
	}

	vector<float> m_offsets;
	vector<ColorF> m_colors;

	static DependencyClass* get_Class();
	static DependencyClass* pClass;
};

}	// Gui
}	// System
