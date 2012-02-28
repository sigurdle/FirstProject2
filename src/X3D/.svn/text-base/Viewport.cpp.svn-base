#include "stdafx.h"
#include "X3D2.h"
#include "Viewport.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(Viewport, MFFloat, clipBoundary, inputOutput, vector<float>(0, 1, 0, 1))

NodeType* Viewport::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_clipBoundaryFieldDef(),
	};

	static NodeType nodeType(L"Viewport", typeid(Viewport), fields, _countof(fields), X3DViewportNode::GetNodeType());
	return &nodeType;
}

NodeType* Viewport::nodeType(GetNodeType());

Viewport::Viewport() : X3DViewportNode(GetNodeType())
{
}

BoundingBox Viewport::CalculateBoundingBox(gm::matrix4f& transform)
{
	return BoundingBox();
}

void Viewport::Draw(X3DDrawContext* pDC)
{
	// left/right/bottom/top

	MFFloat* clipBoundary = getClipBoundaryField();

	D3D11_VIEWPORT vp;
	vp.TopLeftX = int(clipBoundary->get1Value(0) * pDC->m_clientWidth);
	vp.TopLeftY = int(clipBoundary->get1Value(3) * pDC->m_clientHeight);
	vp.Width = unsigned int(clipBoundary->get1Value(1) * pDC->m_clientWidth);
	vp.Height = unsigned int(clipBoundary->get1Value(2) * pDC->m_clientHeight);
	vp.MinDepth = 0;
	vp.MaxDepth = 1;

	UINT oldNum = 8;
	D3D11_VIEWPORT oldvp[8];
	pDC->m_renderContext->GetRT()->m_d3d10->m_deviceContext->RSGetViewports(&oldNum, oldvp);

	// 
	pDC->m_renderContext->GetRT()->m_d3d10->m_deviceContext->RSSetViewports(1, &vp);
	DrawChildren(pDC, getChildrenField());

	// Restore viewport
	pDC->m_renderContext->GetRT()->m_d3d10->m_deviceContext->RSSetViewports(oldNum, oldvp);
}

}
}
