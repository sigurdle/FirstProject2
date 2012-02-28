namespace System
{
namespace x3d
{

class X3DEXT X3DBackgroundNode : public X3DBindableNode
{
protected:
	CTOR X3DBackgroundNode(NodeType* nodeType);

public:

	X3DSFIELD(SFFloat, transparency, Transparency)
	X3DMFIELD(MFColor, groundColor, GroundColor)
	X3DMFIELD(MFColor, skyColor, SkyColor)
	X3DMFIELD(MFFloat, skyAngle, SkyAngle)
	X3DMFIELD(MFFloat, groundAngle, GroundAngle)

	X3DNODE_ABSTRACT(X3DBackgroundNode, X3DBindableNode)

	void Draw(X3DDrawContext* pDC);

	virtual void OnFieldChanged(X3DField* field) override;

protected:

	virtual void Draw2(X3DDrawContext* pDC) abstract;

	Gui::Media3D::SkySphereShape m_sky;
	Gui::Media3D::SkySphereShape m_ground;

	/*
	MFFloat* m_skyAngle;
	MFColor* m_skyColor;
	MFFloat* m_groundAngle;
	MFColor* m_groundColor;
	SFFloat* m_transparency;
	*/
};

}
}
