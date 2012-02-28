#include "stdafx.h"
#include "X3D2.h"
#include "PixelTexture.h"

namespace System
{
namespace x3d
{

NodeType* PixelTexture::GetNodeType()
{
	static X3DFieldDefinition image("image", FieldType_SFImage, SAIFieldAccess_inputOutput, offsetof(PixelTexture, m_image));
	static TypedX3DFieldDefinition<SFBool> repeatS("repeatS", SAIFieldAccess_initializeOnly, offsetof(PixelTexture, m_repeatS), true);
	static TypedX3DFieldDefinition<SFBool> repeatT("repeatT", SAIFieldAccess_initializeOnly, offsetof(PixelTexture, m_repeatT), true);

	static X3DFieldDefinition* PixelTextureFields[] =
	{
		&image,
		&repeatS,
		&repeatT,
		/*
		SFImage [in,out] image   0 0 0
		SFBool  []       repeatS TRUE
		SFBool  []       repeatT TRUE
	  */
	};

	static NodeType nodeType(WSTR("PixelTexture"), typeid(PixelTexture), PixelTextureFields, _countof(PixelTextureFields), X3DTexture2DNode::GetNodeType());
	return &nodeType;
}

PixelTexture::PixelTexture() : X3DTexture2DNode(GetNodeType())
{
	/*
// Cache pointers to relevant fields
	m_ambientIntensity = static_cast<SFFloat*>(getField(L"ambientIntensity"));
	m_diffuseColor = static_cast<SFColor*>(getField(L"diffuseColor"));
	m_emissiveColor = static_cast<SFColor*>(getField(L"emissiveColor"));
	m_shininess = static_cast<SFFloat*>(getField(L"shininess"));
	m_specularColor = static_cast<SFColor*>(getField(L"specularColor"));
	m_transparency = static_cast<SFFloat*>(getField(L"transparency"));

	m_ambientIntensity->m_v = 0.2;
	m_diffuseColor->m_v[0] = 0.8; m_diffuseColor->m_v[1] = 0.8; m_diffuseColor->m_v[2] = 0.8;
	m_emissiveColor->m_v[0] = 0; m_emissiveColor->m_v[1] = 0; m_emissiveColor->m_v[2] = 0;
	m_shininess->m_v = 0.2;
	m_specularColor->m_v[0] = 0; m_specularColor->m_v[1] = 0; m_specularColor->m_v[2] = 0;
	m_transparency->m_v = 0;
	*/
}

}	// x3d
}
