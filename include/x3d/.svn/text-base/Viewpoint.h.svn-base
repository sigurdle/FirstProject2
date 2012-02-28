#ifndef x3d_Viewpoint_h
#define x3d_Viewpoint_h

namespace System
{
namespace x3d
{

class X3DEXT Viewpoint : public X3DViewpointNode
{
public:
	CTOR Viewpoint();

	X3DSFIELD(SFFloat, fieldOfView, FieldOfView)

	virtual D3DXMATRIX GetProjectionMatrixLH(float width, float height, float zNear, float zFar) override;
	virtual D3DXMATRIX GetProjectionMatrixRH(float width, float height, float zNear, float zFar) override;

	X3DNODE(Viewpoint, X3DViewpointNode)

	virtual void DrawOverlay(X3DDrawContext* pDC) override;

protected:

	friend class COGLSceneRenderer;
};

}	// x3d
}	// System

#endif // x3d_Viewpoint_h
