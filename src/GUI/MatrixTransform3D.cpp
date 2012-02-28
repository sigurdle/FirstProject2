#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{


DependencyClass* VisualElement::get_Class()
{
	return nullptr;
}

namespace Media3D
{

DependencyClass* Mesh::get_Class()
{
	return nullptr;
}

DependencyClass* Object3D::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ScaleXProperty(),
		get_ScaleYProperty(),
		get_ScaleZProperty(),
	};
	*/

	return &depclass;
}

//TypedDependencyProperty<float> MatrixTransform3D::ScaleXProperty(&s_Class, WSTR("ScaleX"), 1.0f);

DependencyClass* MatrixTransform3D::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ScaleXProperty(),
		get_ScaleYProperty(),
		get_ScaleZProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* MatrixTransform3D::pClass(get_Class());

MatrixTransform3D::MatrixTransform3D() : Transform3D(get_Class())
{
}

/*
MatrixTransform3D::MatrixTransform3D(const typed<float>& scaleX, const typed<float>& scaleY, const typed<float>& scaleZ) : Transform3D(&s_Class)
{
	SetBinding(this, &ScaleXProperty, scaleX);
	SetBinding(this, &ScaleYProperty, scaleY);
	SetBinding(this, &ScaleZProperty, scaleZ);
}
*/

D3DXMATRIX MatrixTransform3D::GetMatrix()
{
	return m_matrix;
}

}
}
}
