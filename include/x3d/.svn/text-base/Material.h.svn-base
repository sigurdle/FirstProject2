#ifndef x3d_Material_h
#define x3d_Material_h

namespace System
{
namespace x3d
{

class X3DEXT Material : 
	public X3DMaterialNode
{
public:
	CTOR Material();

	Vec3f getDiffuseColor();
	void setDiffuseColor(Vec3f value);

	Vec3f getSpecularColor();
	void setSpecularColor(Vec3f value);

	Vec3f getEmissiveColor();
	float getShininess();
	float getTransparency();
	float getAmbientIntensity();

	virtual int ApplyMaterial(X3DDrawContext* pDC) override;

	X3DNODE(Material, X3DMaterialNode)

	static TypedX3DFieldDefinition<SFFloat>* get_ambientIntensityFieldDef();
	static TypedX3DFieldDefinition<SFColor>* get_diffuseColorFieldDef();
	static TypedX3DFieldDefinition<SFColor>* get_emissiveColorFieldDef();
	static TypedX3DFieldDefinition<SFFloat>* get_shininessFieldDef();
	static TypedX3DFieldDefinition<SFColor>* get_specularColorFieldDef();
	static TypedX3DFieldDefinition<SFFloat>* get_transparencyFieldDef();

private:

	SFFloat* m_ambientIntensity;
	SFColor* m_diffuseColor;
	SFColor* m_emissiveColor;
	SFFloat* m_shininess;
	SFColor* m_specularColor;
	SFFloat* m_transparency;

	/*
	SFFloat [in,out] ambientIntensity 0.2         [0,1]
	SFColor [in,out] diffuseColor     0.8 0.8 0.8 [0,1]
	SFColor [in,out] emissiveColor    0 0 0       [0,1]
	SFFloat [in,out] shininess        0.2         [0,1]
	SFColor [in,out] specularColor    0 0 0       [0,1]
	SFFloat [in,out] transparency     0           [0,1]
  */
};

}	// x3d
}

#endif // x3d_Material_h
