#ifndef x3d_OrthoViewpoint_h
#define x3d_OrthoViewpoint_h

namespace System
{
namespace x3d
{

class X3DEXT OrthoViewpoint : public X3DViewpointNode
{
public:
	CTOR OrthoViewpoint();

	X3DMFIELD(MFFloat, fieldOfView, FieldOfView)

	X3DNODE(OrthoViewpoint, X3DViewpointNode)

	virtual D3DXMATRIX GetProjectionMatrixLH(float width, float height, float zNear, float zFar) override;
	virtual D3DXMATRIX GetProjectionMatrixRH(float width, float height, float zNear, float zFar) override;
};

}
}

#endif // x3d_OrthoViewpoint_h
