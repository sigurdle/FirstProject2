//#include "..\UIT\UIT.h"
//#include "..\UIT\UITImpl.h"
#include "edoc.h"

//#define NOT_COMPLETE(ret) MessageBox(NULL, "This feauture is incomplete or not implemented", "LXFramework", MB_OK); return ret;

#if 0
#include "..\StructsD.h"

// Gdiplus ARGB pixel format
typedef struct _ARGBPixel
{
	BYTE blue, green, red, alpha;
}
ARGBPixel;

// Effect Corner Bits
enum {
	bitTop =				0x01,
	bitRight =				0x02,
	bitBottom =				0x04,
	bitLeft =				0x08,
	bitUpperRight =			0x10,
	bitLowerRight =			0x20,
	bitLowerLeft =			0x40,
	bitUpperLeft =			0x80
};
#endif

extern ILXFrameworkApp* gIApp;
//extern ILXFrameworkFrame* gIFrame;

bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

#if 0
class SVGMatrix : public gmMatrix3
{
public:
	SVGMatrix(ILSVGMatrix* matrix)
	{
		*this = matrix;
	}

	SVGMatrix& operator = (ILSVGMatrix* matrix)
	{
		matrix->get_a(&m_[0][0]); matrix->get_b(&m_[0][1]); m_[0][2] = 0;
		matrix->get_c(&m_[1][0]); matrix->get_d(&m_[1][1]); m_[1][2] = 0;
		matrix->get_e(&m_[2][0]); matrix->get_f(&m_[2][1]); m_[2][2] = 1;

		return *this;
	}
};

class SVGPoint : public PointD
{
public:
	SVGPoint()
	{
	}

	SVGPoint(double x, double y) : PointD(x, y)
	{
	}

	SVGPoint(ILSVGPoint* svgPoint)
	{
		*this = svgPoint;
	}

	SVGPoint& operator = (ILSVGPoint* svgPoint)
	{
		svgPoint->get_x(&X);
		svgPoint->get_y(&Y);

		return *this;
	}

	/*
	operator Gdiplus::Point ()
	{
		return Gdiplus::Point((int)X, (int)Y);
	}
	*/

	/*
	operator Gdiplus::PointF ()
	{
		return Gdiplus::PointF((float)X, (float)Y);
	}
	*/

	SVGPoint matrixTransform(ILSVGSVGElement* svgsvgElement, ILSVGMatrix* matrix)
	{
		CComPtr<ILSVGPoint> svgPoint;
		svgsvgElement->createSVGPoint(&svgPoint);
		svgPoint->put_x(X);
		svgPoint->put_y(Y);

		CComPtr<ILSVGPoint> xsvgPoint;
		svgPoint->matrixTransform(matrix, &xsvgPoint);

		return xsvgPoint;
	}

	SVGPoint matrixTransform(SVGMatrix& matrix)
	{
		gmVector2 xpt = matrix.transform(gmVector2(X, Y));
		return SVGPoint(xpt[0], xpt[1]);
	}

	SVGPoint matrixTransform(ILSVGMatrix* matrix)
	{
		return matrixTransform(SVGMatrix(matrix));
	}
};

class SVGRect : public RectD
{
public:
	SVGRect()
	{
	}

	SVGRect(double _X, double _Y, double _Width, double _Height) : RectD(_X, _Y, _Width, _Height)
	{
	}

	SVGRect(ILSVGRect* svgRect)
	{
		*this = svgRect;
	}

	SVGRect& operator = (ILSVGRect* svgRect)
	{
		svgRect->get_x(&X);
		svgRect->get_y(&Y);
		svgRect->get_width(&Width);
		svgRect->get_height(&Height);

		return *this;
	}
};

class CLRGBColor
{
public:
	CComPtr<ILRGBColor> m_rgbColor;

public:
	CLRGBColor()
	{
	}

	CLRGBColor(ILRGBColor* rgbColor)
	{
		m_rgbColor = rgbColor;
	}

	ILRGBColor** operator &()
	{
		ATLASSERT(m_rgbColor==NULL);
		return &m_rgbColor;
	}

	double GetRed()
	{
		CComPtr<ILCSSPrimitiveValue> cssred;
		m_rgbColor->get_red(&cssred);
		double red;
		cssred->getFloatValue(CSS_NUMBER, &red);

		return red;
	}

	double GetGreen()
	{
		CComPtr<ILCSSPrimitiveValue> cssgreen;
		m_rgbColor->get_green(&cssgreen);
		double green;
		cssgreen->getFloatValue(CSS_NUMBER, &green);

		return green;
	}

	double GetBlue()
	{
		CComPtr<ILCSSPrimitiveValue> cssblue;
		m_rgbColor->get_blue(&cssblue);
		double blue;
		cssblue->getFloatValue(CSS_NUMBER, &blue);

		return blue;
	}
};
#endif