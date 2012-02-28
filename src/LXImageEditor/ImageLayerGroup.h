#ifndef __IMAGELAYERGROUP_H_
#define __IMAGELAYERGROUP_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace ImageEdit
{

class CImageLayerGroup : public System::Object/*: 
	public IImageLayerGroup*/
{
public:
	CTOR CImageLayerGroup()
	{
		m_parentGroup = NULL;
		m_document = NULL;
	}

	IImageLayerGroup* m_parentGroup;
	IImageDocument* m_document;

	vector<ImageLayerUnknown*> m_subLayers;

// IImageLayerGroup
public:
	System::StringW* GetName();
	ImageLayerUnknown* GetSubLayer(uint index);
	uint GetSubLayersCount();
	ImageLayerType GetLayerType()
	{
		return LAYERTYPE_GROUP;
	}
};

}	// ImageEdit
}

#endif //__IMAGELAYERGROUP_H_
