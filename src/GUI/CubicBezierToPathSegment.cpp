#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, CubicBezierToPathSegment, X1, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, CubicBezierToPathSegment, Y1, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, CubicBezierToPathSegment, X2, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, CubicBezierToPathSegment, Y2, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, CubicBezierToPathSegment, X3, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, CubicBezierToPathSegment, Y3, 0.0f)

DependencyClass* CubicBezierToPathSegment::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_X1Property(),
		get_Y1Property(),
		get_X2Property(),
		get_Y2Property(),
		get_X3Property(),
		get_Y3Property(),
	};

	return &depclass;
}

DependencyClass* CubicBezierToPathSegment::pClass(get_Class());

CubicBezierToPathSegment::CubicBezierToPathSegment() : PathSegment(get_Class())
{
}

CubicBezierToPathSegment::CubicBezierToPathSegment(gm::PointF point1, gm::PointF point2, gm::PointF point3) : PathSegment(get_Class())
{
	set_X1(point1.X);
	set_Y1(point1.Y);

	set_X2(point2.X);
	set_Y2(point2.Y);

	set_X3(point3.X);
	set_Y3(point3.Y);
}

void CubicBezierToPathSegment::Sink(ID2D1GeometrySink* pGeometrySink)
{
	pGeometrySink->AddBezier(
		D2D1::BezierSegment(
		cnv(gm::PointF(get_X1(), get_Y1())),
		cnv(gm::PointF(get_X2(), get_Y2())),
		cnv(gm::PointF(get_X3(), get_Y3()))));
}

}	// Gui
}	// System
