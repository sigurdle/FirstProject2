#include "stdafx.h"
#include "X3D2.h"
#include "Collision.h"

namespace System
{
namespace x3d
{

NodeType* Collision::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput, offsetof(Collision, m_children)),
	//	&X3DFieldDefinition("collide", FieldType_SFBool, SAIFieldAccess_inputOutput, offsetof(Collision, m_collide)),	// ???
		&X3DFieldDefinition("proxy", FieldType_SFNode, SAIFieldAccess_initializeOnly, offsetof(Collision, m_proxy)),
		/*
		MFNode  [in]     addChildren             [X3DChildNode]
		MFNode  [in]     removeChildren          [X3DChildNode]
		SFBool  [in,out] enabled
		MFNode  [in,out] children       []       [X3DChildNode]
		SFNode  [in,out] metadata       NULL     [X3DMetadataObject]
		SFTime  [out]    collideTime
		SFBool  [out]    isActive
		SFVec3f []       bboxCenter     0 0 0    (-8,8)
		SFVec3f []       bboxSize       -1 -1 -1 [0,8) or -1 -1 -1
		SFNode  []       proxy          NULL     [X3DChildNode]
		*/
	};

	static NodeType nodeType(WSTR("Collision"), typeid(Collision), fields, _countof(fields), X3DSensorNode::GetNodeType());
	return &nodeType;
}

Collision::Collision() : X3DSensorNode(GetNodeType())
{
// Cache pointers to relevant fields
//	m_children = static_cast<MFNode*>(getField(WSTR("children")));
}

Collision::~Collision()
{
}

// virtual
void Collision::Draw(X3DDrawContext* pDC)
{
	int nLight = pDC->m_renderContext->m_nLight;

	for (uint i = 0; i < m_children->m_items.GetSize(); ++i)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (uint i = 0; i < m_children->m_items.GetSize(); ++i)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->Draw(pDC);
			}
		}
	}

	for (int i = pDC->m_renderContext->m_nLight; i >= nLight; i--)
	{
	//	pDC->m_pGraphics3D->Disable(GL_LIGHT0+i);
	}
	pDC->m_renderContext->m_nLight = nLight;
}

void Collision::DrawOverlay(X3DDrawContext* pDC)
{
	MFNode* children = static_cast<MFNode*>(m_children);

	int nLight = pDC->m_renderContext->m_nLight;

	for (uint i = 0; i < m_children->m_items.GetSize(); ++i)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (uint i = 0; i < m_children->m_items.GetSize(); ++i)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->DrawOverlay(pDC);
			}
		}
	}

	for (int i = pDC->m_renderContext->m_nLight; i >= nLight; --i)
	{
	//	pDC->m_pGraphics3D->Disable(GL_LIGHT0+i);
	}
	pDC->m_renderContext->m_nLight = nLight;
}

}	// x3d
}
