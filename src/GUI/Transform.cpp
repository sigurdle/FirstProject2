#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* Transform::get_Class()
{
	static DependencyClass depclass(typeid(Transform), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_TranslateXProperty(),
		get_TranslateYProperty(),
	};
	*/

	return &depclass;
}

//DependencyClass* Transform::pClass(get_Class());

Transform::Transform(DependencyClass* depClass) : GeneralTransform(depClass)
{
}

gm::matrix3f Transform::get_InverseMatrix()
{
	return get_Matrix().getInverse();
}

gm::PointF Transform::TransformPoint(gm::PointF point)
{
	return get_Matrix().transform(point);
}

void Transform::TransformPoints(gm::PointF* destPoints, const gm::PointF* points, unsigned int count)
{
	gm::matrix3f m = get_Matrix();

	while (count--)
	{
		*destPoints++ = m.transform(*points++);
	}
}

gm::PointF Transform::InverseTransformPoint(gm::PointF point)
{
	return get_InverseMatrix().transform(point);
}

void Transform::InverseTransformPoints(gm::PointF* destPoints, const gm::PointF* points, unsigned int count)
{
	gm::matrix3f m = get_InverseMatrix();

	while (count--)
	{
		*destPoints++ = m.transform(*points++);
	}
}

}	// Gui
}	// System
