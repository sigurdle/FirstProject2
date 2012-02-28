#include "stdafx.h"
#include "X3D2.h"
#include "Anchor.h"

namespace System
{
namespace x3d
{

void DrawChildren(X3DDrawContext* pDC, MFNode* children);

NodeType* Anchor::nodeType(GetNodeType());

NodeType* Anchor::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		&X3DFieldDefinition("description", FieldType_SFString, SAIFieldAccess_inputOutput, -1),//offsetof(Anchor, m_description),
		&X3DFieldDefinition("parameter", FieldType_MFString, SAIFieldAccess_inputOutput, -1),//offsetof(Anchor, m_parameter),
		&X3DFieldDefinition("url", FieldType_MFString, SAIFieldAccess_inputOutput, offsetof(Anchor, m_url)),
	};

	static NodeType nodeType("Anchor", typeid(Anchor), fields, _countof(fields), X3DGroupingNode::GetNodeType());
	return &nodeType;
}

Anchor::Anchor() : X3DGroupingNode(GetNodeType())
{
}

Anchor::~Anchor()
{
}

// virtual
void Anchor::Draw(X3DDrawContext* pDC)
{
	/*
	int nLight = pDC->m_nLight;
	int nNames = pDC->m_namedNodes.GetSize();

	int i;

	for (i = 0; i < m_children->m_items.GetSize(); i++)
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

	for (i = 0; i < m_children->m_items.GetSize(); i++)
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

	for (i = pDC->m_namedNodes.GetSize(); i >= nNames; i--)
	{
//		glPopName();
	}
	for (i = pDC->m_nLight; i >= nLight; i--)
	{
		pDC->m_pGraphics3D->glDisable(GL_LIGHT0+i);
	}
	pDC->m_nLight = nLight;
	*/
}

void Anchor::DrawOverlay(X3DDrawContext* pDC)
{
	MFNode* children = static_cast<MFNode*>(getChildrenField());

	int nLight = pDC->m_renderContext->m_nLight;

	for (size_t i = 0; i < getChildrenField()->m_items.GetSize(); ++i)
	{
		X3DNode* node = getChildrenField()->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (size_t i = 0; i < getChildrenField()->m_items.GetSize(); ++i)
	{
		X3DNode* node = getChildrenField()->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->DrawOverlay(pDC);
			}
		}
	}

	for (int i = pDC->m_renderContext->m_nLight; i >= nLight; i--)
	{
	//	pDC->m_pGraphics3D->Disable(GL_LIGHT0+i);
	}
	pDC->m_renderContext->m_nLight = nLight;
}

}	// x3d
}	// System
