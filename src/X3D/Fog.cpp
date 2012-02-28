#include "stdafx.h"
#include "X3D2.h"
#include "Fog.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(Fog, SFColor, color, inputOutput)
IMP_X3DFIELD0(Fog, SFString, fogType, inputOutput)
IMP_X3DFIELD3(Fog, SFFloat, visibilityRange, inputOutput, 0, 0, FLT_MAX)

NodeType* Fog::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_colorFieldDef(),
		get_fogTypeFieldDef(),
		get_visibilityRangeFieldDef(),
		/*
		SFBool   [in]     set_bind
		SFColor  [in,out] color           1 1 1    [0,1]
		SFString [in,out] fogType         "LINEAR" ["LINEAR"|"EXPONENTIAL"]
		SFNode   [in,out] metadata        NULL     [X3DMetadataObject]
		SFFloat  [in,out] visibilityRange 0        [0,8)
		SFTime   [out]    bindTime
		SFBool   [out]    isBound
		*/
	};

	static NodeType nodeType(WSTR("Fog"), typeid(Fog), fields, _countof(fields), X3DBindableNode::GetNodeType());
	return &nodeType;
}

NodeType* Fog::nodeType(GetNodeType());

Fog::Fog() : X3DBindableNode(GetNodeType())
{
// Cache pointers to relevant fields
//	m_color = static_cast<SFColor*>(getField(WSTR("color")));
//	m_visibilityRange = static_cast<SFFloat*>(getField(WSTR("visibilityRange")));

// Set defaults
	m_color->m_value = gm::vector3f(1, 1, 1);
	m_visibilityRange->m_value = 0;
}

void Fog::Apply(X3DDrawContext* pDC)
{
	ASSERT(0);
#if 0
	Graphics::Graphics3D* pG = pDC->m_pGraphics3D;

//	pG->glPushAttrib(GL_ENABLE_BIT);

	pG->Enable(GL_FOG);

	float color[4];
	color[0] = m_color->m_value[0];
	color[1] = m_color->m_value[1];
	color[2] = m_color->m_value[2];
	color[3] = 1.0f;

	pG->Fogfv(GL_FOG_COLOR, color);

	pG->Fogf(GL_FOG_DENSITY, 1 / m_visibilityRange->m_value);
#endif
//	pG->glPopAttrib();

}

}	// x3d
}
