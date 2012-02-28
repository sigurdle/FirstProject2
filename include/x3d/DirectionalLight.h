//#ifndef x3d_DirectionalLight_h
//#define x3d_DirectionalLight_h

namespace System
{
namespace x3d
{

class X3DEXT DirectionalLight : 
	public X3DLightNode,
	public RenderImplImpl
{
public:
	CTOR DirectionalLight();
	~DirectionalLight();

	X3DSFIELD(SFVec3f, direction, Direction)

	X3DNODE(DirectionalLight, X3DLightNode)

	virtual void PreDraw(X3DDrawContext* pDC) override;
	virtual void DrawGlobalLights(X3DDrawContext* pDC) override;

protected:

	void SetLight(X3DDrawContext* pDC);
};

}	// x3d
}

//#endif // x3d_DirectionalLight_h
