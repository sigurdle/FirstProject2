#include "stdafx.h"
#include "X3D2.h"
#include "Billboard.h"

namespace System
{
namespace x3d
{

NodeType* Billboard::nodeType(GetNodeType());

TypedX3DFieldDefinition<SFVec3f>* Billboard::get_axisOfRotationFieldDef()
{
	static TypedX3DFieldDefinition<SFVec3f> axisOfRotation("axisOfRotation", SAIFieldAccess_inputOutput, offsetof(Billboard, m_axisOfRotation), Vec3f(0, 1, 0));
	return &axisOfRotation;
}

NodeType* Billboard::GetNodeType()
{
	static X3DFieldDefinition* BillboardFields[] =
	{
		get_axisOfRotationFieldDef()
	};

	static NodeType nodeType("Billboard", typeid(Billboard), BillboardFields, _countof(BillboardFields), X3DGroupingNode::GetNodeType());
	return &nodeType;
}

Billboard::Billboard() : X3DGroupingNode(GetNodeType()),
	m_axisOfRotation(new SFVec3f(get_axisOfRotationFieldDef(), this))
{
}

	//-----------------------------------------------------------------------------
// Name: buildAxisAlignedBBMatrix()
// Desc: 
//-----------------------------------------------------------------------------
void buildAxisAlignedBBMatrix( float m[16], float x, float y, float z )
{
    float pi    = 3.141592654f;
    float theta = -180 * atan2f(m[8], m[10]) / pi;
    float d     = x*x + y*y + z*z;
    float ct    = cosf(gmRadians(theta));
    float st    = sinf(gmRadians(theta));

    // Normalize
    if( d > 0 )
    {
	    d = 1/d;
	    x *= d;
	    y *= d;
	    z *= d;
    }

    // Clear out the view matrix passed in
    m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
    m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
    m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

    //---------------------------------------------
    // R = uu' + cos(theta)*(I-uu') + sin(theta)*S
    //
    // S =  0  -z   y    u' = (x, y, z)
    //	    z   0  -x
    //	   -y   x   0
    //---------------------------------------------

     m[0] = x*x + ct*(1-x*x) + st*0;
     m[4] = x*y + ct*(0-x*y) + st*-z;
     m[8] = x*z + ct*(0-x*z) + st*y;

     m[1] = y*x + ct*(0-y*x) + st*z;
     m[5] = y*y + ct*(1-y*y) + st*0;
     m[9] = y*z + ct*(0-y*z) + st*-x;

     m[2] = z*x + ct*(0-z*x) + st*-y;
     m[6] = z*y + ct*(0-z*y) + st*x;
     m[10]= z*z + ct*(1-z*z) + st*0;
}

void Billboard::Draw(X3DDrawContext* pDC)
{
	ASSERT(0);
#if 0
	pDC->m_pGraphics3D->PushMatrix();

	{
		gm::vector3f axisOfRotation = m_axisOfRotation->m_value;

		float mat[16];
		pDC->m_pGraphics3D->GetFloatv(GL_MODELVIEW_MATRIX, mat);
		buildAxisAlignedBBMatrix(mat, axisOfRotation[0], axisOfRotation[1], axisOfRotation[2]);
		pDC->m_pGraphics3D->MultMatrixf( mat );
	}

	DrawChildren(pDC, getChildrenField());

	/*
	int nLight = pDC->m_nLight;

	int i;

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		X3DNode* node = m_children->m_items[i];

		if (node)
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
			if (render)
			{
				render->Draw(pDC);
			}
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
	pDC->m_pGraphics3D->PopMatrix();
#endif
}

}	// x3d
}	// System
