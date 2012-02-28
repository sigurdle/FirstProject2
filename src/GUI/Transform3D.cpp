#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

DependencyClass* Transform3D::get_Class()
{
	static DependencyClass depclass(typeid(Transform3D), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_BoundsLeftProperty(),
		get_BoundsTopProperty(),
		get_BoundsWidthProperty(),
		get_BoundsHeightProperty(),
		get_FillAreaProperty(),
		get_ContourLengthProperty(),
	};
	*/

	return &depclass;
}

Transform3D::Transform3D(DependencyClass* depClass) : GeneralTransform3D(depClass)
{
}

D3DXVECTOR4 Transform3D::Transform(D3DXVECTOR3 v)
{
	D3DXVECTOR4 xv;
	D3DXVec3Transform(&xv, &v, &GetMatrix());
	return xv;
}

}	// Media3D
}	// Gui
}	// System
