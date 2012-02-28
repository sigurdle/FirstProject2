#include "stdafx.h"
#include "X3D2.h"
#include "Box.h"
#include "GUI/physics.h"

namespace System
{
namespace x3d
{
#if 0
X3DFieldDefinition Box::Fields[] =
{
	X3DFieldDefinition(WSTR("metadata"), FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Box, m_metadata)),

	X3DFieldDefinition("size", FieldType_SFVec3f, SAIFieldAccess_initializeOnly, offsetof(Box, m_size)),
/*
SFVec3f [] size 2 2 2 (0,8)
*/
};

NodeType Box::s_nodeType("Box", typeid(Box), Fields, _countof(Fields));
#endif

TypedX3DFieldDefinition<SFVec3f>* Box::get_sizeFieldDef()
{
	static TypedX3DFieldDefinition<SFVec3f> size("size", SAIFieldAccess_initializeOnly, offsetof(Box, m_size), Vec3f(2,2,2));
	return &size;
}

NodeType* Box::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_sizeFieldDef(),
	};

	static NodeType nodeType("Box", typeid(Box), fields, _countof(fields), X3DGeometryNode::GetNodeType());
	return &nodeType;
}

NodeType* Box::nodeType(GetNodeType());

Box::Box() : X3DGeometryNode(GetNodeType()), m_size(new SFVec3f(get_sizeFieldDef(), this, Vec3f(2,2,2)))
{
//	m_vertexBuffer = NULL;

//	m_size = NULL;

// Cache pointers to relevant fields
//	m_size = static_cast<SFVec3f*>(getField(WSTR("size")));
	ASSERT(m_size);

// Set defaults
//	m_size->m_value[0] = m_size->m_value[1] = m_size->m_value[2] = 2;
}

Vec3f Box::getSize3f()
{
	return getSize();
}

void Box::setSize3f(Vec3f size)
{
	setSize(size);
}

void Box::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	if (!m_shape.IsValid(pDC->m_renderContext))
	{
		m_shape.Create(pDC->m_renderContext, getSize());
	}

	m_shape.Draw(pDC->m_renderContext);


	/*
    // Obtain the technique
	ID3D10EffectTechnique* g_pTechnique;
    g_pTechnique = g_pEffect->GetTechniqueByName("Render");
	*/

#if 0
	LDraw::vector3f s = m_size->m_value;

	if (true)
	{
		if (m_vertexBuffer == NULL)
		{
			VERTEX_XYZ_NORMAL vertices[4*4];

			vertices[0].position = LDraw::vector3f(-s[0]/2, -s[1]/2, s[2]/2);
			vertices[0].normal = LDraw::vector3f(0, 0, 1);
			vertices[1].position = LDraw::vector3f(s[0]/2, -s[1]/2, s[2]/2);
			vertices[1].normal = LDraw::vector3f(0, 0, 1);
			vertices[2].position = LDraw::vector3f(s[0]/2, s[1]/2, s[2]/2);
			vertices[2].normal = LDraw::vector3f(0, 0, 1);
			vertices[3].position = LDraw::vector3f(-s[0]/2, s[1]/2, s[2]/2);
			vertices[3].normal = LDraw::vector3f(0, 0, 1);

			m_vertexBuffer = pDC->m_pGraphics3D->CreateVertexBuffer(sizeof(VERTEX_XYZ_NORMAL)*4*4, vertices, GL_STATIC_DRAW);

		//	pDC->m_pGraphics3D->BindBuffer(GL_ARRAY_BUFFER, m_buffer);
		//	pDC->m_pGraphics3D->BufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_XYZ_NORMAL)*4*4, vertices, 0);

			LDraw::VertexDeclElement elements[] =
			{
				{"POSITION", 0, 0, LDraw::DECLTYPE_FLOAT3, 0},
				{"NORMAL", 0, 3*4, LDraw::DECLTYPE_FLOAT3, 0},
			};

			m_vertexDeclaration = pDC->m_pGraphics3D->CreateVertexDeclaration(elements, 2);
		}

		pDC->m_pGraphics3D->SetVertexDeclaration(m_vertexDeclaration);

		pDC->m_pGraphics3D->SetVertexBuffer(0, m_vertexBuffer, 0, sizeof(VERTEX_XYZ_NORMAL));
	//	pDC->m_pGraphics3D->InterleavedArrays(GL_N3F_V3F, 0, NULL);
		pDC->m_pGraphics3D->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//	pDC->m_pGraphics3D->DrawArrays(GL_TRIANGLE_FAN, 4, 4);
	//	pDC->m_pGraphics3D->DrawArrays(GL_TRIANGLE_FAN, 8, 4);
	//	pDC->m_pGraphics3D->DrawArrays(GL_TRIANGLE_FAN, 12, 4);
	}
	else
	{
#if 0
		pDC->m_pGraphics3D->glBegin(GL_QUADS);

		// front (cw)
		/*
		glVertex3d(-m_boxSize[0]/2, -m_boxSize[1]/2, m_boxSize[2]/2);
		glVertex3d(m_boxSize[0]/2, -m_boxSize[1]/2, m_boxSize[2]/2);
		glVertex3d(m_boxSize[0]/2, m_boxSize[1]/2, m_boxSize[2]/2);
		glVertex3d(-m_boxSize[0]/2, m_boxSize[1]/2, m_boxSize[2]/2);
		*/

		// front (ccw)

		/*
		lglNormal(pDC->m_pGraphics,	vector3f(-s[0]/2, -s[1]/2, s[2]/2),
						vector3f(s[0]/2, -s[1]/2, s[2]/2),
						vector3f(s[0]/2, s[1]/2, s[2]/2));
						*/
		pDC->m_pGraphics3D->glNormalf(0, 0, 1);

		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, -s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 0);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, -s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(0, 1);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, s[1]/2, s[2]/2);

		/*
		lglNormal(pDC->m_pGraphics,	vector3f(-s[0]/2, -s[1]/2, s[2]/2),
						vector3f(-s[0]/2, s[1]/2, s[2]/2),
						vector3f(s[0]/2, s[1]/2, s[2]/2));

		pDC->m_pGraphics3D->glTexCoord(0, 0);
		pDC->m_pGraphics3D->glVertex(-s[0]/2, -s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoord(1, 0);
		pDC->m_pGraphics3D->glVertex(-s[0]/2, s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoord(1, 1);
		pDC->m_pGraphics3D->glVertex(s[0]/2, s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoord(0, 1);
		pDC->m_pGraphics3D->glVertex(s[0]/2, -s[1]/2, s[2]/2);
		*/

		// back (ccw)
		pDC->m_pGraphics3D->glNormalf(0, 0, -1);
	/*
		lglNormal(pDC->m_pGraphics, LDraw::vector3f(-s[0]/2, -s[1]/2, -s[2]/2),
						LDraw::vector3f(-s[0]/2, s[1]/2, -s[2]/2),
						LDraw::vector3f(s[0]/2, s[1]/2, -s[2]/2));
	*/
		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, -s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(0, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, -s[1]/2, -s[2]/2);

		// left side
		/*
		lglNormal(pDC->m_pGraphics,	LDraw::vector3f(-s[0]/2, -s[1]/2, s[2]/2),
						LDraw::vector3f(-s[0]/2, -s[1]/2, -s[2]/2),
						LDraw::vector3f(-s[0]/2, s[1]/2, -s[2]/2));
						*/
		pDC->m_pGraphics3D->glNormalf(-1, 0, 0);

		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, -s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(0, 1);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, -s[1]/2, s[2]/2);

		// right side
		/*
		lglNormal(pDC->m_pGraphics,	LDraw::vector3f(s[0]/2, -s[1]/2, s[2]/2),
						LDraw::vector3f(s[0]/2, -s[1]/2, -s[2]/2),
						LDraw::vector3f(s[0]/2, s[1]/2, -s[2]/2));
						*/
		pDC->m_pGraphics3D->glNormalf(1, 0, 0);

		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, -s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 0);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, -s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(0, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, s[1]/2, s[2]/2);

		// top side
		/*
		lglNormal(pDC->m_pGraphics,	LDraw::vector3f(-s[0]/2, -s[1]/2, -s[2]/2),
						LDraw::vector3f(-s[0]/2, -s[1]/2, s[2]/2),
						LDraw::vector3f(s[0]/2, -s[1]/2, s[2]/2));
						*/
		pDC->m_pGraphics3D->glNormalf(0, -1, 0);

		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, -s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, -s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, -s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(0, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, -s[1]/2, -s[2]/2);

		// bottom side
		/*
		lglNormal(pDC->m_pGraphics,	LDraw::vector3f(-s[0]/2, s[1]/2, -s[2]/2),
						LDraw::vector3f(-s[0]/2, s[1]/2, s[2]/2),
						LDraw::vector3f(s[0]/2, s[1]/2, s[2]/2));
						*/
		pDC->m_pGraphics3D->glNormalf(0, 1, 0);

		pDC->m_pGraphics3D->glTexCoordf(0, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 0);
		pDC->m_pGraphics3D->glVertexf(-s[0]/2, s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(1, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, s[1]/2, s[2]/2);

		pDC->m_pGraphics3D->glTexCoordf(0, 1);
		pDC->m_pGraphics3D->glVertexf(s[0]/2, s[1]/2, -s[2]/2);

		pDC->m_pGraphics3D->glEnd();
#endif
	}
#endif
}

// X3DBoundedImplImpl
BoundingBox Box::CalculateBoundingBox(gm::matrix4f& transform)
{
	m_computedBBoxValid = true;
//	m_computedBBoxSize = getSize();

	return BoundingBox(Vec3f(0,0,0), getSize());

	/*
	m_boxCenter[0] = 0;
	m_boxCenter[1] = 0;
	m_boxCenter[2] = 0;
	*/
}

void Box::AddShapeDesc(physx::PxRigidActor* actor)
{
	Vec3f size = getSize();

#if defined(PX_PHYSICS_NXPHYSICS_API)
	physx::PxMaterial* mMaterial;
	mMaterial = Gui::gPhysics->createMaterial(0.5f, 0.5f, 0.1f);    //static friction, dynamic friction, restitution

	physx::PxBoxGeometry geometry(size[0]*0.5f, size[1]*0.5f, size[1]*0.5f);
	actor->createShape(geometry, *mMaterial);

#if 0
	physx::PxRigidBodyExt::updateMassAndInertia(actor, sphereDensity);
#endif
#endif
}

}	// x3d
}	// System
