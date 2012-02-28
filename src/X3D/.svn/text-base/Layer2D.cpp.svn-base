#include "stdafx.h"
#include "X3D2.h"
#include "Layer2D.h"

// MPEG4

namespace System
{
namespace x3d
{

X3DFieldDefinition* Layer2DFields[] =
{
	&X3DFieldDefinition("addChildren", FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	/*
	???
	*/
};

NodeType Layer2D::s_nodeType("Layer2D", typeid(Layer2D), Layer2DFields, _countof(Layer2DFields));

Layer2D::Layer2D() : X3DGroupingNode(&s_nodeType)
{
}

// virtual
void Layer2D::Draw(X3DDrawContext* pDC)
{
	DrawChildren(pDC, getChildrenField());
}

}	// x3d
}	// System
