#include "stdafx.h"
#include "X3D2.h"
#include "LOD.h"

namespace System
{
namespace x3d
{

//IMP_X3DFIELD0(LOD, MFNode, level, initializeOnly)
IMP_X3DFIELD0(LOD, MFFloat, range, initializeOnly)
IMP_X3DFIELD0(LOD, SFVec3f, center, initializeOnly)

NodeType* LOD::GetNodeType()
{
	static X3DFieldDefinition* LODFields[] =
	{
	//	get_levelFieldDef(),
		get_rangeFieldDef(),
		get_centerFieldDef(),
//		&X3DFieldDefinition(WSTR("center"), FieldType_SFVec3f, SAIFieldAccess_initializeOnly,-1),

		/*
		MFNode  [in]     addChildren             [X3DChildNode]
		MFNode  [in]     removeChildren          [X3DChildNode]
		MFNode  [in,out] children       []       [X3DChildNode]
		SFNode  [in,out] metadata       NULL     [X3DMetadataObject]
		SFVec3f []       bboxCenter     0 0 0    (-8,8)
		SFVec3f []       bboxSize       -1 -1 -1 [0,8) or -1 -1 -1
		SFVec3f []       center         0 0 0    (-8,8)
		MFFloat []       range          []       [0,8) or -1 
		*/
	};

	static NodeType nodeType(WSTR("LOD"), typeid(LOD), LODFields, _countof(LODFields), baseClass::GetNodeType());
	return &nodeType;
}

LOD::LOD() : X3DGroupingNode(GetNodeType())
{
}

void LOD::Draw(X3DDrawContext* pDC)
{
	X3DNode* node = getChildrenField()->m_items[0];

	if (node)
	{
		RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
		if (render)
		{
			render->Draw(pDC);
		}
	}
}

}	// x3d
}
