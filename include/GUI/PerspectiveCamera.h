namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT PerspectiveCamera : public Camera
{
public:

	CTOR PerspectiveCamera();

	virtual D3DXMATRIX GetProjectionMatrixLH(float width, float height, float zNear, float zFar) override;
	virtual D3DXMATRIX GetProjectionMatrixRH(float width, float height, float zNear, float zFar) override;
	virtual D3DXMATRIX GetViewMatrix() override;
	virtual D3DXMATRIX GetViewMatrixI() override;

	void LookAt(gm::vector3f eye, gm::vector3f at, gm::vector3f up);

	DEPENDENCY_CLASS(PerspectiveCamera, Camera)

	DEPENDENCY_PROPERTY(Vector3_F*, Eye)
	DEPENDENCY_PROPERTY(Vector3_F*, At)
	DEPENDENCY_PROPERTY(Vector3_F*, Up)
	DEPENDENCY_PROPERTY(float, FieldOfView)
};

}	// Media3D
}	// Gui
}	// System
