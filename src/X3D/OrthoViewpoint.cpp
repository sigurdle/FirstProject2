#include "stdafx.h"
#include "X3D2.h"
#include "OrthoViewpoint.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(OrthoViewpoint, MFFloat, fieldOfView, inputOutput, vector<float>(-1, -1, 1, 1))

NodeType* OrthoViewpoint::GetNodeType()
{
	static X3DFieldDefinition* OrthoViewpointFields[] =
	{
		get_fieldOfViewFieldDef()
	};

	static NodeType nodeType(WSTR("OrthoViewpoint"), typeid(OrthoViewpoint), OrthoViewpointFields, _countof(OrthoViewpointFields), X3DViewpointNode::GetNodeType());
	return &nodeType;
}

NodeType* OrthoViewpoint::nodeType(GetNodeType());

OrthoViewpoint::OrthoViewpoint() : X3DViewpointNode(GetNodeType()),
	m_fieldOfView(new MFFloat(get_fieldOfViewFieldDef(), this/*, -1,-1, 1, 1*/))
{
}

D3DXMATRIX OrthoViewpoint::GetProjectionMatrixLH(float width, float height, float zNear, float zFar)
{
	// TODO

	D3DXMATRIX m;
	D3DXMatrixOrthoLH(&m, width, height, zNear, zFar);
	return m;
}

D3DXMATRIX OrthoViewpoint::GetProjectionMatrixRH(float width, float height, float zNear, float zFar)
{
	// TODO

	D3DXMATRIX m;
	D3DXMatrixOrthoRH(&m, width, height, zNear, zFar);
	return m;
}

}	// x3d
}
