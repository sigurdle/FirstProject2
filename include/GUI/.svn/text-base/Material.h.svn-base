namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT Material : public DependencyObject
{
public:

	CTOR Material();

	virtual void Apply(RenderContext* renderContext);

	String m_name;

	String m_textureFilename;
	ID3D10ShaderResourceView* m_pTextureRV10;

	ID3D10EffectTechnique* m_pTechnique;

//	LDraw::vector3f m_ambientColor;	// TODO remove
//	LDraw::vector3f m_diffuseColor;	// TODO remove
//	LDraw::vector3f m_specularColor;	// TODO remove

	DEPENDENCY_PROPERTY(Color*, AmbientColor)
	DEPENDENCY_PROPERTY(Color*, DiffuseColor)
	DEPENDENCY_PROPERTY(Color*, SpecularColor)

	DEPENDENCY_CLASS(Material, DependencyObject)

	int m_shininess;
	float m_alpha;

	bool m_hasSpecular;
};

}	// Media3D
}	// Gui
}	// System
