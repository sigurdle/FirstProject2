#ifndef x3d_Appearance_h
#define x3d_Appearance_h

namespace System
{
namespace x3d
{

class X3DEXT Appearance :
	public X3DAppearanceNode
{
public:
	CTOR Appearance();

	MFNode* get_shadersField()
	{
		return m_shaders;
	}

//	void setTexture(X3DTextureNode* texture);

#ifndef __LERSTAD__
	X3DSFIELD(TypedSFNode<X3DMaterialNode*>, material, Material)
	X3DSFIELD(TypedSFNode<X3DTextureNode*>, texture, Texture)
	X3DSFIELD(TypedSFNode<X3DTextureTransformNode*>, textureTransform, TextureTransform)
#else

	X3DMaterialNode* getMaterial();
	void setMaterial(X3DMaterialNode*);

	SFNode* m_material;
	SFNode* m_texture;
	SFNode* m_textureTransform;
#endif

	X3DNODE(Appearance, X3DAppearanceNode)

private:

//	TypedSFNode<X3DMaterialNode*>* m_material;
//	TypedSFNode<X3DTextureNode*>* m_texture;
//	TypedSFNode<X3DTextureTransformNode*>* m_textureTransform;
	MFNode* m_shaders;

	/*
	SFNode [in,out] fillProperties   NULL [FillProperties]
	SFNode [in,out] lineProperties   NULL [LineProperties]
	SFNode [in,out] material         NULL [X3DMaterialNode]
	SFNode [in,out] texture          NULL [X3DTextureNode]
	SFNode [in,out] textureTransform NULL [X3DTextureTransformNode]
	MFNode [in,out] shaders          []   [X3DShaderNode]
  */
};

}	// x3d
}	// System

#endif // x3d_Appearance_h
