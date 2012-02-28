#include "stdafx.h"
#include "X3D2.h"
#include "Transform2D.h"

namespace System
{
namespace x3d
{

NodeType* Transform2D::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		&X3DFieldDefinition("center", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("children", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("rotationAngle", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("scale", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("scaleOrientation", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("translation", FieldType_SFVec2f, SAIFieldAccess_inputOutput,-1),
		/*
		eventIn MFNode addChildren
		eventIn MFNode removeChildren
		exposedField SFVec2f center 0, 0
		exposedField MFNode children []
		exposedField SFFloat rotationAngle 0.0
		exposedField SFVec2f scale 1, 1
		exposedField SFFloat scaleOrientation 0.0
		exposedField SFVec2f translation 0, 0
		*/
	};

	static NodeType nodeType(WSTR("Transform2D"), typeid(Transform2D), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* Transform2D::nodeType(GetNodeType());

Transform2D::Transform2D() : X3DGroupingNode(GetNodeType())
{
	/*
// Cache pointers to relevant fields
	m_C = static_cast<SFVec2f*>(getField(WSTR("center")));
	m_R = static_cast<SFFloat*>(getField(WSTR("rotationAngle")));
	m_S = static_cast<SFVec2f*>(getField(WSTR("scale")));
	m_SR = static_cast<SFFloat*>(getField(WSTR("scaleOrientation")));
	m_T = static_cast<SFVec2f*>(getField(WSTR("translation")));
	//m_children = static_cast<MFNode*>(getField(WSTR("children")));
*/

// Set defaults
	m_S->m_value[0] = m_S->m_value[1] = 1.0;
}

// virtual
void Transform2D::Draw(X3DDrawContext* pDC)
{
/*		gmMatrix4 P_ = gmMatrix4::translate(m_T[0], m_T[1], m_T[2]) *

						gmMatrix4::translate(m_C[0], m_C[1], m_C[2]) *

						gmMatrix4::rotate(gmDegrees(m_angle), m_R) *

						gmMatrix4::translate(m_SR[0], m_SR[1], m_SR[2]) *
						gmMatrix4::scale(m_S[0], m_S[1], m_S[2]) *
						gmMatrix4::translate(-m_SR[0], -m_SR[1], -m_SR[2]) *

						gmMatrix4::translate(-m_C[0], -m_C[1], -m_C[2]);// * P
*/
	/*
	gmMatrix4 P_ =
		gmMatrix4::translate(-m_C[0], -m_C[1], -m_C[2]) *
		gmMatrix4::translate(-m_SR[0], -m_SR[1], -m_SR[2]) *
		gmMatrix4::scale(m_S[0], m_S[1], m_S[2]) *
		gmMatrix4::translate(m_SR[0], m_SR[1], m_SR[2]) *
		gmMatrix4::rotate(gmDegrees(m_angle), m_R) *
		gmMatrix4::translate(m_C[0], m_C[1], m_C[2]) *
		gmMatrix4::translate(m_T[0], m_T[1], m_T[2])					;

	float m[4][4];
	P_.copyTo(m);
	*/

//	LDraw::Matrix3f oldTransform;

#if 0
	if (pDC->m_pGraphics2D)
	{
		/*oldTransform = */pDC->m_pGraphics2D->PushTransform();

		pDC->m_pGraphics2D->TranslateTransform(m_T->m_value[0], m_T->m_value[1]);
		pDC->m_pGraphics2D->TranslateTransform(m_C->m_value[0], m_C->m_value[1]);
		pDC->m_pGraphics2D->RotateTransform(gmDegrees(m_R->m_value));
		pDC->m_pGraphics2D->RotateTransform(gmDegrees(m_SR->m_value));
		pDC->m_pGraphics2D->ScaleTransform(m_S->m_value[0], m_S->m_value[1]);
		pDC->m_pGraphics2D->RotateTransform(gmDegrees(-m_SR->m_value));
		pDC->m_pGraphics2D->TranslateTransform(-m_C->m_value[0], -m_C->m_value[1]);
	}
#endif

#if 0
	glPushMatrix();

		glTranslate(m_T->m_value);
		glTranslate(m_C->m_value);
		glRotate(gmDegrees(m_R->m_value));
		glRotatef(gmDegrees(m_SR->m_value), 0, 0, 1);
		glScale(m_S->m_value);
		glRotatef(gmDegrees(m_SR->m_value), 0, 0, -1);
		glTranslate(-m_C->m_value);
#endif

		DrawChildren(pDC, getChildrenField());
		/*
	int nLight = pDC->m_nLight;

	int i;

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
		if (render)
		{
			render->PreDraw(pDC);
		}
	}

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
		if (render)
		{
			render->Draw(pDC);
		}
	}

	if (pDC->m_pGraphics3D)
	{
		for (i = pDC->m_nLight; i >= nLight; i--)
		{
			pDC->m_pGraphics3D->glDisable(GL_LIGHT0+i);
		}
		pDC->m_nLight = nLight;
	}
	*/

	pDC->m_renderContext->Pop();

#if 0
	if (pDC->m_pGraphics2D)
	{
		pDC->m_pGraphics2D->PopTransform();//oldTransform);
	}
#endif
#if 0
	glPopMatrix();
#endif
}

}	// x3d
}	// System
