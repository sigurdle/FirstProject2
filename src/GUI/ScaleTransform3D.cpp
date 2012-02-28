#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

IMP_DEPENDENCY_PROPERTY(float, ScaleTransform3D, ScaleX, 1.0f)
IMP_DEPENDENCY_PROPERTY(float, ScaleTransform3D, ScaleY, 1.0f)
IMP_DEPENDENCY_PROPERTY(float, ScaleTransform3D, ScaleZ, 1.0f)

DependencyClass* ScaleTransform3D::get_Class()
{
	static DependencyClass depclass(typeid(ScaleTransform3D), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ScaleXProperty(),
		get_ScaleYProperty(),
		get_ScaleZProperty(),
	};

	return &depclass;
}

DependencyClass* ScaleTransform3D::pClass(get_Class());

ScaleTransform3D::ScaleTransform3D() : Transform3D(get_Class())
{
}

ScaleTransform3D::ScaleTransform3D(typed<float> scaleX, typed<float> scaleY, typed<float> scaleZ) : Transform3D(get_Class())
{
	SetBinding(this, get_ScaleXProperty(), scaleX);
	SetBinding(this, get_ScaleYProperty(), scaleY);
	SetBinding(this, get_ScaleZProperty(), scaleZ);
}

D3DXMATRIX ScaleTransform3D::GetMatrix()
{
	D3DXMATRIX m;
	D3DXMatrixScaling(&m, get_ScaleX(), get_ScaleY(), get_ScaleZ());
	return m;
}

}
}
}
