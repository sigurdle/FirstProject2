namespace System
{
namespace Gui
{

class GUIEXT Color : public DependencyObject
{
public:
	CTOR Color();
	CTOR Color(float r, float g, float b);
	CTOR Color(ColorF color);

	DEPENDENCY_PROPERTY(float, Red)
	DEPENDENCY_PROPERTY(float, Green)
	DEPENDENCY_PROPERTY(float, Blue)
//	DEPENDENCY_PROPERTY(float, Alpha)
/*
	// Computed
	TypedDependencyProperty<float> HueProperty;
	TypedDependencyProperty<float> LuminanceProperty;
	TypedDependencyProperty<float> SaturationProperty;
	*/

	Color* operator *(float mul)
	{
		return new Color(get_Red() * mul, get_Green() * mul, get_Blue() * mul);
	}

	Color* operator * (Color& other)
	{
		return new Color(get_Red() * other.get_Red(), get_Green() * other.get_Green(), get_Blue() * other.get_Blue());
	}

	Color* operator + (Color& other)
	{
		return new Color(get_Red() + other.get_Red(), get_Green() + other.get_Green(), get_Blue() + other.get_Blue());
	}

	Color* operator - (Color& other)
	{
		return new Color(get_Red() - other.get_Red(), get_Green() - other.get_Green(), get_Blue() - other.get_Blue());
	}

	Vec3f getVec3f()
	{
		return Vec3f(get_Red(), get_Green(), get_Blue());
	}

	static Color* get_BlackColor();
	static Color* get_WhiteColor();
	static Color* get_GrayColor();
	static Color* get_LightGrayColor();
	static Color* get_DarkGrayColor();

	static Color* get_RedColor();
	static Color* get_GreenColor();
	static Color* get_BlueColor();
	static Color* get_CyanColor();
	static Color* get_MagentaColor();
	static Color* get_YellowColor();

	/// Darks

	/*
	static Color* get_DarkRedColor();
	static Color* get_DarkGreenColor();
	static Color* get_DarkBlueColor();
	static Color* get_DarkCyanColor();
	static Color* get_DarkMagentaColor();
	static Color* get_DarkYellowColor();
*/

	DEPENDENCY_CLASS(Color, DependencyObject)
};

}	// Gui
}	// System
