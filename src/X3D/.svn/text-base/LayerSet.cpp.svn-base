#include "stdafx.h"
#include "X3D2.h"
#include "LayerSet.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(LayerSet, TypedMFNode<X3DLayerNode*>, layers, inputOutput)

NodeType* LayerSet::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_layersFieldDef(),
	};

	static NodeType nodeType(WSTR("LayerSet"), typeid(LayerSet), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* LayerSet::nodeType(GetNodeType());

LayerSet::LayerSet() : X3DNode(GetNodeType())
{
}

// virtual
int LayerSet::HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest)
{
	return HitTestChildren(getLayersField(), projection, view, model, vp, type, mousepos, pos, hitTest);
}

// virtual
void LayerSet::DrawGlobalLights(X3DDrawContext* pDC)
{
	DrawGlobalLightsChildren(pDC, getLayersField());
}

// virtual
void LayerSet::Draw(X3DDrawContext* pDC)
{
	DrawChildren(pDC, getLayersField());
}

// virtual
void LayerSet::DrawOverlay(X3DDrawContext* pDC)
{
	DrawOverlayChildren(pDC, getLayersField());
}

}	// x3d
}	// System
