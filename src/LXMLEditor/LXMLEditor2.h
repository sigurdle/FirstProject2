#include "LXMLEditor.h"

#include "../LXML/LXML2.h"

#if 0
ErrorCode createObjectNS(ILXUIDocument* document, BSTR namespaceURI, BSTR qualifiedName, REFIID riid, void** obp);
#endif

//ILDOMElement* GetElementByTagName(ILDOMNode* parent, BSTR tagName, BOOL bDeep = FALSE);
//ILDOMElement* GetElementByTagNameNS(ILDOMNode* parent, BSTR ns, BSTR tagName, BOOL bDeep = FALSE);

//LDraw::Color FromLDraw::Color(LDraw::Color LDraw::Color);

namespace System
{

void AddCbString(System::UI::Control* hWnd, TCHAR* text, uint dw);
void SetCbCurSel(System::UI::Control* hWnd, uint dw);

}

//#include "..\UIT.h"
#include "..\LXFramework\edoc.h"

namespace System
{

struct
IEDocument
{
	virtual System::StringW* get_filePath() = 0;
	virtual ErrorCode put_filePath(System::StringW* newVal) = 0;
	virtual ErrorCode get_undoManager(IUndoManager* *pVal) = 0;
	virtual ErrorCode NewDocument() = 0;
	//	virtual ErrorCode __stdcall LoadDocumentByteArray([in] SAFEARRAY(char) dataArray, [out,retval] VARIANT_BOOL* success);
	virtual ErrorCode Activate() = 0;
	virtual ErrorCode CloseDocument() = 0;
	virtual ErrorCode GetModified(long* pVal) = 0;
	virtual ErrorCode ShowViews(IEFrame* pFrame) = 0;

#if 0
	virtual ErrorCode __stdcall SetApp(ILXAddin* pAddin) = 0;
#endif
};

}

#include "../UIActiveImpl.h"

namespace System
{

class NamedRGBColor
{
public:
	NamedRGBColor(System::StringW* _name, LDraw::Color _color)
	{
		name = _name;
		color = _color;
	}
	System::StringW* name;
	LDraw::Color color;
};

}

/*
// Gdiplus ARGB pixel format
typedef struct _ARGBPixel
{
	uint8 blue, green, red, alpha;
}
ARGBPixel;
*/

#define NOT_COMPLETE(ret) MessageBoxA(GetMainHwnd(), "This feauture is incomplete or not implemented", "WebEditor", MB_OK); return ret;

namespace System
{

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

class SVGMatrix : public LDraw::matrix3d
{
public:
	SVGMatrix(Web::SVGMatrix* matrix)
	{
		*this = matrix;
	}

	SVGMatrix(LDraw::matrix3d& mat)
	{
		*this = mat;
	}

	SVGMatrix& operator = (LDraw::matrix3d& mat)
	{
		m_[0][0] = mat[0][0];
		m_[0][1] = mat[0][1];
		m_[0][2] = mat[0][2];
		m_[1][0] = mat[1][0];
		m_[1][1] = mat[1][1];
		m_[1][2] = mat[1][2];
		m_[2][0] = mat[2][0];
		m_[2][1] = mat[2][1];
		m_[2][2] = mat[2][2];

		return *this;
	}

	SVGMatrix& operator = (Web::SVGMatrix* matrix)
	{
		ASSERT(0);
#if 0
		matrix->get_a(&m_[0][0]); matrix->get_b(&m_[0][1]); m_[0][2] = 0;
		matrix->get_c(&m_[1][0]); matrix->get_d(&m_[1][1]); m_[1][2] = 0;
		matrix->get_e(&m_[2][0]); matrix->get_f(&m_[2][1]); m_[2][2] = 1;
#endif
		return *this;
	}
};

class SVGPoint : public LDraw::Point<double>
{
public:
	SVGPoint()
	{
	}

	SVGPoint(double x, double y) : LDraw::Point<double>(x, y)
	{
	}

	SVGPoint(LDraw::PointD& point)
	{
		*this = point;
	}

	SVGPoint(Web::SVGPoint* svgPoint)
	{
		*this = svgPoint;
	}

	SVGPoint& operator = (LDraw::PointD& point)
	{
		X = point.X;
		Y = point.Y;

		return *this;
	}

	SVGPoint& operator = (Web::SVGPoint* svgPoint)
	{
		X = svgPoint->get_x();
		Y = svgPoint->get_y();

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

	SVGPoint matrixTransform(Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* matrix)
	{
		ASSERT(0);
		return *this;
#if 0
		CComPtr<ILSVGPoint> svgPoint;
		svgsvgElement->createSVGPoint(&svgPoint);
		svgPoint->put_x(X);
		svgPoint->put_y(Y);

		CComPtr<ILSVGPoint> xsvgPoint;
		svgPoint->matrixTransform(matrix, &xsvgPoint);

		return xsvgPoint;
#endif
	}

	SVGPoint matrixTransform(const LDraw::matrix3d& matrix)
	{
		LDraw::vector2d xpt = matrix.transform(LDraw::vector2d(X, Y));
		return SVGPoint(xpt[0], xpt[1]);
	}

	SVGPoint matrixTransform(Web::SVGMatrix* matrix)
	{
		return matrixTransform(SVGMatrix(matrix));
	}
};

#if 0

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

class SVGLength
{
protected:
	CComPtr<ILSVGLength> m_length;

public:

	SVGLength()
	{
	}

	SVGLength(ILSVGLength* length)
	{
		m_length = length;
	}

	ILSVGLength** operator &()
	{
		ASSERT(m_length==NULL);
		return &m_length;
	}

	ILSVGLength* operator -> ()
	{
		return m_length;
	}

	LSVGLengthType GetUnitType()
	{
		LSVGLengthType unit;
		m_length->get_unitType(&unit);
		return unit;
	}

	double GetValueInSpecifiedUnits()
	{
		double specified;
		m_length->get_valueInSpecifiedUnits(&specified);
		return specified;
	}

	double GetValue()
	{
		double value;
		m_length->get_value(&value);
		return value;
	}
};

class LRGBColor
{
public:
	CComPtr<ILRGBColor> m_rgbColor;

public:
	LRGBColor()
	{
	}

	LRGBColor(ILRGBColor* rgbColor)
	{
		m_rgbColor = rgbColor;
	}

	ILRGBColor** operator &()
	{
		ASSERT(m_rgbColor==NULL);
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

#ifndef __CMPBSTR_H
#define __CMPBSTR_H

inline int bstrlen(WCHAR* p)
{
	if (p == NULL) return 0;
	if (p[0] == 0) return 0;
	return 1;
}

inline int cmpbstr(WCHAR* p1, WCHAR* p2)
{
	if (bstrlen(p1) == 0 && bstrlen(p2) == 0) return 0;
	if (bstrlen(p1) == 0) return -1;	// Not sure
	if (bstrlen(p2) == 0) return 1;	// Not sure

	return wcscmp(p1, p2);
}

#endif	// __CMPBSTR_H

}
