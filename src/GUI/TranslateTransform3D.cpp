#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

IMP_DEPENDENCY_PROPERTY(float, TranslateTransform3D, TranslateX, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, TranslateTransform3D, TranslateY, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, TranslateTransform3D, TranslateZ, 0.0f)

DependencyClass* TranslateTransform3D::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_TranslateXProperty(),
		get_TranslateYProperty(),
		get_TranslateZProperty(),
	};

	return &depclass;
}

DependencyClass* TranslateTransform3D::pClass(get_Class());

TranslateTransform3D::TranslateTransform3D() : Transform3D(get_Class())
{
}

TranslateTransform3D::TranslateTransform3D(typed<float> translateX, typed<float> translateY, typed<float> translateZ) : Transform3D(get_Class())
{
	SetBinding(this, get_TranslateXProperty(), translateX);
	SetBinding(this, get_TranslateYProperty(), translateY);
	SetBinding(this, get_TranslateZProperty(), translateZ);
}

D3DXMATRIX TranslateTransform3D::GetMatrix()
{
	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, get_TranslateX(), get_TranslateY(), get_TranslateZ());
	return m;
}

}	// Media3D
}	// Gui
}	// System
