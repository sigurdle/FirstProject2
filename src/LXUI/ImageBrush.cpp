#include "stdafx.h"
#include "LXUI2.h"
#include "ImageBrush.h"

namespace System
{
namespace UI
{

DependencyProperty* ImageBrush::s_ImageSourceProperty = RegisterProperty(WSTR("ImageSource"), typeid(IImageSource), typeid(ImageBrush), NULL, PropertyMetaData(None));

ImageBrush::ImageBrush()
{
}

IImageSource* ImageBrush::get_ImageSource()
{
	return dynamic_cast<IImageSource*>(GetValue(get_ImageSourceProperty()));
}

void ImageBrush::set_ImageSource(IImageSource* source)
{
	SetValue(get_ImageSourceProperty(), dynamic_cast<Object*>(source));
}

__release<LDraw::Brush> ImageBrush::CreateBrush(UIElement* pReferencingElement, double scaleX, double scaleY)
{
	IImageSource* source = get_ImageSource();
	if (source)
	{
		LDraw::Bitmap* bitmap = source->GetBitmap();

		ASSERT(0);
	}

	return NULL;
}

}	// UI
}
