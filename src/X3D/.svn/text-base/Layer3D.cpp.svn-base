#include "stdafx.h"
#include "X3D2.h"
#include "Layer3D.h"

// MPEG4

namespace System
{
namespace x3d
{

X3DFieldDefinition* Layer3DFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("addChildren", FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("size", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
	/*
	MFNode eventIn addChildren  
	MFNode eventIn removeChildren  
	MFNode exposedField children NULL 
	SFVec2f exposedField size -1,-1 
	SFNode exposedField background NULL 
	SFNode exposedField fog NULL 
	SFNode exposedField navigationInfo NULL 
	SFNode exposedField viewpoint NULL 
	 */
};

NodeType Layer3D::s_nodeType("Layer3D", typeid(Layer3D), Layer3DFields, _countof(Layer3DFields));

Layer3D::Layer3D() : X3DGroupingNode(&s_nodeType)
{
}

// virtual
void Layer3D::Draw(X3DDrawContext* pDC)
{
	DrawChildren(pDC, getChildrenField());
}

}	// x3d
}	// System
