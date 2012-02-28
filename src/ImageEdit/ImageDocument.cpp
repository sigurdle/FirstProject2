#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

ImageDocument::ImageDocument()
{
	m_layers = new List<Element*>;
}

// static
ImageDocument* ImageDocument::FromBitmap(Graphics::Bitmap* bitmap)
{
	ImageDocument* document = new ImageDocument;
	BitmapLayer* layer = new BitmapLayer(document);
	layer->m_name = "Background";
	layer->m_bitmap = bitmap;

	document->m_layers->Add(layer);
	ASSERT(0);
#if 0
	layer->get_PropertyChanged().connect(bind1st_of_3(mem_fun2(&ImageDocument::OnLayerPropertyChanged), document));
#endif

	document->m_size = gm::SizeF(layer->m_bitmap->GetWidth(), layer->m_bitmap->GetHeight());

	return document;
}

#if 0
void ImageDocument::OnLayerPropertyChanged(Object* sender, StringW* propertyName)
{
	list<BitmapEditor*>::iterator it = m_views.begin();
	while (it != m_views.end())
	{
		(*it)->Invalidate();
		++it;
	}
}
#endif

}
}
