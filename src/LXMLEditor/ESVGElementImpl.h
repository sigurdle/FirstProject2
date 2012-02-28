#pragma once

#include "EElementImpl.h"

namespace System
{
namespace LXmlEdit
{

struct IESVGDrawOutline
{
public:
	virtual void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix) = 0;
};

class CESVGElementImpl : public Element
{
public:
	Web::SVGTransform* GetMatrixTransform()
	{
		ASSERT(0);
#if 0
		LSVG::ILSVGTransformable* transformable = dynamic_cast<LSVG::ILSVGTransformable*>(m_domElement);

		if (transformable)
		{
			LSVG::CLSVGAnimatedTransformList* animtransformlist = transformable->get_transform();
			LSVG::SVGTransformList* basetransformlist = animtransformlist->get_baseVal();

			long numberOfItems = basetransformlist->get_numberOfItems();
			if (numberOfItems > 0)
			{
				for (int i = numberOfItems-1; i >= numberOfItems-1; i--)
				{
					LSVG::SVGTransform* transform = basetransformlist->getItem(i);

					LSVGTransformType type = transform->get_type();

					if (type == SVG_TRANSFORM_MATRIX)
					{
						return transform;
					}
				}
			}

		// Create new 'matrix' transform
			LSVG::SVGMatrix* matrix = new LSVG::SVGMatrix;
			
			LSVG::SVGTransform* transform = basetransformlist->createSVGTransformFromMatrix(matrix);
			basetransformlist->appendItem(transform);

			return transform;
		}
#endif
		return NULL;
	}
	
	Web::SVGMatrix* m_initialMatrix;
};

class CESVGElement :
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CESVGElementImpl
{
public:

	/*
BEGIN_COM_MAP(CESVGElement)
	COM_INTERFACE_ENTRY(IENode)
	COM_INTERFACE_ENTRY(IEElement)
	COM_INTERFACE_ENTRY(IESVGElement)
END_COM_MAP()
*/
};

}	// LXmlEdit
}
