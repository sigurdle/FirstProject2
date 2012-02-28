#include "stdafx.h"
#include "X3D2.h"
#include "Appearance.h"

namespace System
{
namespace x3d
{

#if 0
X3DFieldDefinition Appearance::Fields[] =
{
	X3DFieldDefinition(WSTR("metadata"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_metadata)),

	X3DFieldDefinition(WSTR("material"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_material)),
	X3DFieldDefinition(WSTR("texture"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_texture)),
	X3DFieldDefinition(WSTR("textureTransform"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_textureTransform)),
	X3DFieldDefinition(WSTR("shaders"), FieldType_MFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_shaders)),
	/*
	SFNode [in,out] fillProperties   NULL [FillProperties]
	SFNode [in,out] lineProperties   NULL [LineProperties]
	SFNode [in,out] material         NULL [X3DMaterialNode]
	SFNode [in,out] texture          NULL [X3DTextureNode]
	SFNode [in,out] textureTransform NULL [X3DTextureTransformNode]
	MFNode [in,out] shaders          []   [X3DShaderNode]
	*/
};

NodeType Appearance::nodeType(WSTR("Appearance"), typeid(Appearance), Fields, _countof(Fields));

#endif

IMP_X3DFIELD0(Appearance, TypedSFNode<X3DMaterialNode*>, material, inputOutput)
IMP_X3DFIELD0(Appearance, TypedSFNode<X3DTextureNode*>, texture, inputOutput)
IMP_X3DFIELD0(Appearance, TypedSFNode<X3DTextureTransformNode*>, textureTransform, inputOutput)

NodeType* Appearance::nodeType(GetNodeType());

NodeType* Appearance::GetNodeType()
{
//	static X3DFieldDefinition material(WSTR("material"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_material));
//	static X3DFieldDefinition texture(WSTR("texture"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_texture));
//	static X3DFieldDefinition textureTransform(WSTR("textureTransform"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_textureTransform));
	static X3DFieldDefinition shaders("shaders", FieldType_MFNode, SAIFieldAccess_inputOutput, offsetof(Appearance, m_shaders));

	static X3DFieldDefinition* fields[] =
	{
		get_materialFieldDef(),
		get_textureFieldDef(),
		get_textureTransformFieldDef(),
		&shaders,
		/*
		SFNode [in,out] fillProperties   NULL [FillProperties]
		SFNode [in,out] lineProperties   NULL [LineProperties]
		SFNode [in,out] material         NULL [X3DMaterialNode]
		SFNode [in,out] texture          NULL [X3DTextureNode]
		SFNode [in,out] textureTransform NULL [X3DTextureTransformNode]
		MFNode [in,out] shaders          []   [X3DShaderNode]
		*/
	};

	static NodeType nodeType(WSTR("Appearance"), typeid(Appearance), fields, _countof(fields), X3DAppearanceNode::GetNodeType());
	return &nodeType;
}

Appearance::Appearance() : X3DAppearanceNode(GetNodeType()),
	m_material(new TypedSFNode<X3DMaterialNode*>(this)),
	m_texture(new TypedSFNode<X3DTextureNode*>(this)),
	m_textureTransform(new TypedSFNode<X3DTextureTransformNode*>(this)),
	m_shaders(new MFNode(this))
{
}


}	// x3d
}	// System
