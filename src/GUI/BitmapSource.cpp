#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(int, BitmapSource, Width, 0)
IMP_DEPENDENCY_PROPERTY(int, BitmapSource, Height, 0)

DependencyClass* BitmapSource::get_Class()
{
	static DependencyClass depclass(typeid(BitmapSource), baseClass::get_Class());
//	static int added = addroot(&depclass);

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

BitmapSource::BitmapSource() : DependencyObject(get_Class())
{
}

BitmapSource::BitmapSource(Graphics::Bitmap* bitmap) : DependencyObject(get_Class())
{
	m_bitmap = bitmap;
}

}	// Gui
}	// System
