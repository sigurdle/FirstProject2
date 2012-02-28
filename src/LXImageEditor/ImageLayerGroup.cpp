#include "stdafx.h"
#include "LXImageEditor.h"

#include "ImageLayerGroup.h"

namespace System
{
namespace ImageEdit
{

uint CImageLayerGroup::GetSubLayersCount()
{
	return m_subLayers.GetSize();
}

ImageLayerUnknown* CImageLayerGroup::GetSubLayer(uint index)
{
	if (index < m_subLayers.GetSize())
	{
		return m_subLayers[index];
	}
	return NULL;
}

StringW* CImageLayerGroup::GetName()
{
	return NULL;
}

}
}
