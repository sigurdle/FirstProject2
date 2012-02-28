#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

NodeType* ScreenGroup::nodeType(GetNodeType());

NodeType* ScreenGroup::GetNodeType()
{
#if 0
	static X3DFieldDefinition* BillboardFields[] =
	{
		get_axisOfRotationFieldDef()
	/*
		MFNode  [in]     addChildren             [X3DChildNode]
		MFNode  [in]     removeChildren          [X3DChildNode]
		SFVec3f [in,out] axisOfRotation 0 1 0    (-8,8)
		MFNode  [in,out] children       []       [X3DChildNode]
		SFVec3f []       bboxCenter     0 0 0    (-8,8)
		SFVec3f []       bboxSize       -1 -1 -1 (0,8) or -1 -1 -1
	*/
	};
#endif

	static NodeType nodeType(WSTR("ScreenGroup"), typeid(ScreenGroup), NULL, 0, X3DGroupingNode::GetNodeType());
	return &nodeType;
}

ScreenGroup::ScreenGroup() : X3DGroupingNode(GetNodeType())
{
}

void ScreenGroup::Draw(X3DDrawContext* pDC)
{
	D3DXMATRIX modelViewProjection = pDC->m_renderContext->modelViewProjectionMatrix();

	float scaleX = modelViewProjection._11;
	float scaleY = modelViewProjection._22;
	float scaleZ = modelViewProjection._33;

	// / w ??

	modelViewProjection._11 = 1;
	modelViewProjection._22 = 1;
	modelViewProjection._33 = 1;

	/*
	pDC->m_renderContext->PushMatrix();

	{
		LDraw::vector3f axisOfRotation = m_axisOfRotation->m_value;

		float mat[16];
		pDC->m_pGraphics3D->GetFloatv(GL_MODELVIEW_MATRIX, mat);
		buildAxisAlignedBBMatrix(mat, axisOfRotation[0], axisOfRotation[1], axisOfRotation[2]);
		pDC->m_pGraphics3D->MultMatrixf( mat );
	}

	DrawChildren(pDC, get_children());

	pDC->m_pGraphics3D->PopMatrix();
	*/
}

}	// x3d
}
