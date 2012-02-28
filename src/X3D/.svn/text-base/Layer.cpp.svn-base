#include "stdafx.h"
#include "X3D2.h"
#include "Layer.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(Layer, TypedMFNode<X3DChildNode*>, children, inputOutput)

NodeType* Layer::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_childrenFieldDef(),
	};

	static NodeType nodeType(WSTR("Layer"), typeid(Layer), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* Layer::nodeType(GetNodeType());

Layer::Layer() : X3DLayerNode(GetNodeType())
{
}

// virtual
int Layer::HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest)
{
	return HitTestChildren(getChildrenField(), projection, view, model, vp, type, mousepos, pos, hitTest);
}

// virtual
void Layer::DrawGlobalLights(X3DDrawContext* pDC)
{
	DrawGlobalLightsChildren(pDC, getChildrenField());
}

// virtual
void Layer::Draw(X3DDrawContext* pDC)
{
	DrawChildren(pDC, getChildrenField());
}

// virtual
void Layer::DrawOverlay(X3DDrawContext* pDC)
{
	DrawOverlayChildren(pDC, getChildrenField());
}

}
}
