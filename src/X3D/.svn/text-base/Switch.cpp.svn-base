#include "stdafx.h"
#include "X3D2.h"
#include "Switch.h"

namespace System
{
namespace x3d
{

void DrawChildren(X3DDrawContext* pDC, MFNode* children);
void DrawOverlayChildren(X3DDrawContext* pDC, MFNode* children);
void DrawGlobalLightsChildren(X3DDrawContext* pDC, MFNode* children);

IMP_X3DFIELD3(Switch, SFInt32, whichChoice, inputOutput, -1, -1, INT_MAX)

NodeType* Switch::GetNodeType()
{
	static X3DFieldDefinition* SwitchFields[] =
	{
		get_whichChoiceFieldDef(),
//		&X3DFieldDefinition(WSTR("children"), FieldType_MFNode, SAIFieldAccess_inputOutput,-1),	// "choice" for old VRML
		/*
		MFNode  [in]     addChildren             [X3DChildNode]
		MFNode  [in]     removeChildren          [X3DChildNode]
		MFNode  [in,out] children       []       [X3DChildNode]
		SFInt32 [in,out] whichChoice    -1       [-1,8)
		SFVec3f []       bboxCenter     0 0 0    (-8,8)
		SFVec3f []       bboxSize       -1 -1 -1 (0,8) or -1 -1 -1
		*/
	};

	static NodeType nodeType(WSTR("Switch"), typeid(Switch), SwitchFields, _countof(SwitchFields), baseClass::GetNodeType());
	return &nodeType;
}

Switch::Switch() : X3DGroupingNode(GetNodeType())
{
}

// virtual
void Switch::Draw(X3DDrawContext* pDC)
{
	int whichChoice = m_whichChoice->getValue();

	if (whichChoice >= 0 && whichChoice < getChildrenField()->get_size())
	{
		int nLight = pDC->m_renderContext->m_nLight;

		X3DNode* node = getChildrenField()->get1Value(whichChoice);
		ASSERT(node);

		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}

		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->Draw(pDC);
			}
		}

		for (int i = pDC->m_renderContext->m_nLight; i >= nLight; i--)
		{
		//	pDC->m_pGraphics3D->Disable(GL_LIGHT0+i);
		}
		pDC->m_renderContext->m_nLight = nLight;
	}
}

}	// x3d
}
