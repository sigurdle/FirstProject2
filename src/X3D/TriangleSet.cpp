#include "stdafx.h"
#include "X3D2.h"
#include "TriangleSet.h"
#include "ComposedShader.h"

//#include <windows.h>
//#include <d3d9.h>
//#include <D3dx9math.h>
//#define D3D_MODELVIEW	D3DTS_WORLD

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "Graphics/openglext.h"

namespace System
{
namespace x3d
{

void lglNormal(Graphics::Graphics3D* p, const gm::vector3f& c, const gm::vector3f& b, const gm::vector3f& a);

NodeType* TriangleSet::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
	//	X3DFieldDefinition(WSTR("metadata"), FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	//	X3DFieldDefinition(WSTR("attrib"), FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
	//	X3DFieldDefinition(WSTR("ccw"), FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
		&X3DFieldDefinition("color", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(TriangleSet, m_color)),
		&X3DFieldDefinition("coord", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(TriangleSet, m_coord)),
	//	X3DFieldDefinition(WSTR("colorPerVertex"), FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	//	X3DFieldDefinition(WSTR("normalPerVertex"), FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	//	X3DFieldDefinition(WSTR("solid"), FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
		/*
		MFNode [in,out] attrib          []   [X3DVertexAttributeNode]
		SFNode  [in,out] color           NULL [X3DColorNode]
		SFNode  [in,out] coord           NULL [X3DCoordinateNode]
		SFNode  [in,out] metadata        NULL [X3DMetadataObject]
		SFNode  [in,out] normal          NULL [X3DNormalNode]
		SFNode  [in,out] texCoord        NULL [X3DTextureCoordinateNode]
		SFBool  []       ccw             TRUE
		SFBool  []       colorPerVertex  TRUE
		SFBool  []       normalPerVertex TRUE
		SFBool  []       solid           TRUE
		*/
	};

	static NodeType nodeType(WSTR("TriangleSet"), typeid(TriangleSet), fields, _countof(fields), X3DComposedGeometryNode::GetNodeType());
	return &nodeType;
}

TriangleSet::TriangleSet() : X3DComposedGeometryNode(GetNodeType())
{
}

TriangleSet::~TriangleSet()
{
}

struct STREAM0_VERTEX
{
	gm::vector3f position;
	gm::vector3f normal;
};

void TriangleSet::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	ASSERT(0);
#if 0
	Coordinate* coordinate = dynamic_cast<Coordinate*>(m_coord->getValue());

	LDraw::Graphics3D* p3D = pDC->m_pGraphics3D;
	LDraw::OpenGL_I* pGL = dynamic_cast<LDraw::OpenGL_I*>(p3D->m_pGraphics->m_device);

	if (m_vertexDeclaration == NULL)
	{
		/*
		VERTEX_XYZ_NORMAL vertices[4*4];

		vertices[0].position = LDraw::vector3f(-s[0]/2, -s[1]/2, s[2]/2);
		vertices[0].normal = LDraw::vector3f(0, 0, 1);
		vertices[1].position = LDraw::vector3f(s[0]/2, -s[1]/2, s[2]/2);
		vertices[1].normal = LDraw::vector3f(0, 0, 1);
		vertices[2].position = LDraw::vector3f(s[0]/2, s[1]/2, s[2]/2);
		vertices[2].normal = LDraw::vector3f(0, 0, 1);
		vertices[3].position = LDraw::vector3f(-s[0]/2, s[1]/2, s[2]/2);
		vertices[3].normal = LDraw::vector3f(0, 0, 1);
		*/

		unsigned int ntriangles = coordinate->getPoint()->get_size()/3;
		m_nvertices = ntriangles*3;

		int attribIndex = -1;
		
		if (false && pDC->m_shader)
		{
			attribIndex = pGL->m_glprocs->glGetAttribLocation(dynamic_cast<ComposedShader*>(pDC->m_shader)->GetGLProgram(), "myColor");
			ASSERT(::glGetError() == 0);
		}

		if (attribIndex == -1)
		{
			// TODO
		//	ASSERT(0);
		}
	
		STREAM0_VERTEX* bufferData = new STREAM0_VERTEX[m_nvertices];

		LDraw::vector3f* points = coordinate->getPoint()->m_items.begin();

		for (unsigned int i = 0; i < m_nvertices; i++)
		{
			bufferData[i].position = points[i];
		}

		for (unsigned int i = 0; i < ntriangles; i++)
		{
			LDraw::vector3f normal = LDraw::cross(bufferData[i*3+1].position - bufferData[i*3].position, bufferData[i*3+2].position - bufferData[i*3].position);

			bufferData[i*3].normal = normal;
			bufferData[i*3+1].normal = normal;
			bufferData[i*3+2].normal = normal;
		}

		m_vertexBuffer0 = p3D->CreateVertexBuffer(sizeof(STREAM0_VERTEX)*m_nvertices, bufferData, GL_STATIC_DRAW);
	//	m_vertexBuffer1 = pDC->m_pGraphics3D->CreateVertexBuffer(sizeof(LDraw::vector3f)*m_coord->get_size(), m_normals.begin());

		delete[] bufferData;

		LDraw::VertexDeclElement elements[64] =
		{
			{"POSITION", 0, 0, LDraw::DECLTYPE_FLOAT3, 0},
			{"NORMAL", 0, 3*4, LDraw::DECLTYPE_FLOAT3, 0},
		//	{"COLOR", 2, 0, LDraw::DECLTYPE_FLOAT3, 0},
		};

		int nelements = 2;
		int nstreams = 1;

		if (false)
		{
			// generic per-vertex attributes
			unsigned int nattribs = m_attrib->get_size();
			m_attribBuffer.clear();
			m_attribBuffer.reserve(nattribs);

			for (unsigned int i = 0; i < nattribs; i++)
			{
				X3DVertexAttributeNode* vertexAttrib = dynamic_cast<X3DVertexAttributeNode*>(m_attrib->get1Value(i));

				elements[nelements].stream = nstreams;
				elements[nelements].usage = vertexAttrib->getName()->ToStringA()->c_str();
				elements[nelements].usageIndex = attribIndex;

				if (FloatVertexAttribute* floatVertexAttrib = dynamic_cast<FloatVertexAttribute*>(vertexAttrib))
				{
					switch (floatVertexAttrib->getNumComponents())
					{
					case 1: elements[nelements].type = LDraw::DECLTYPE_FLOAT1; break;
					case 2: elements[nelements].type = LDraw::DECLTYPE_FLOAT2; break;
					case 3: elements[nelements].type = LDraw::DECLTYPE_FLOAT3; break;
					case 4: elements[nelements].type = LDraw::DECLTYPE_FLOAT4; break;

					default:
						// TODO error
						break;
					}

					LDraw::VertexBuffer attribBuffer = p3D->CreateVertexBuffer(sizeof(LDraw::vector3f)*coordinate->getPoint()->get_size(), floatVertexAttrib->get_valueField()->m_items.begin(), GL_STATIC_DRAW);
					m_attribBuffer.push_back(attribBuffer);

				}
				else
					VERIFY(0);

				nelements++;
				nstreams++;
			}
		}

		m_vertexDeclaration = p3D->CreateVertexDeclaration(elements, nelements);
	}

	p3D->SetVertexDeclaration(m_vertexDeclaration);
	p3D->SetVertexBuffer(0, m_vertexBuffer0, 0, sizeof(STREAM0_VERTEX));

	if (false && pDC->m_shader)
	{
		for (int i = 0; i < m_attribBuffer.size(); i++)
		{
			pDC->m_pGraphics3D->SetVertexBuffer(1+i, m_attribBuffer[i], 0, 3*4/*TODO*//*sizeof(LDraw::vector3f)*/);
		}
	}

	p3D->SetPrimitiveTopology(GL_TRIANGLES);
	p3D->Draw(0, m_nvertices);

#if 0
	if (m_coord)
	{
		pDC->m_pGraphics3D->PushAttrib(GL_ENABLE_BIT);

		if (m_color)
		{
			pDC->m_pGraphics3D->Enable(GL_COLOR_MATERIAL);
			pDC->m_pGraphics3D->ColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		}

		if (m_solid->m_value == false)
		{
			pDC->m_pGraphics3D->Disable(GL_CULL_FACE);
		}
		else
		{
			pDC->m_pGraphics3D->Enable(GL_CULL_FACE);
		}

		// The x3d spec says that incomplete triangles are ignored, OpenGL does this automatically, so I don't need to check it
		pDC->m_pGraphics3D->glBegin(GL_TRIANGLES);

		Coordinate* pCoord = static_cast<Coordinate*>(m_coord->m_value);
		Color* pColor = static_cast<Color*>(m_color->m_value);

		MFVec3f* point = pCoord->getPoint();
		MFColor* color = pColor->m_color;
		int ncolors = color->m_items.GetSize();

		for (int i = 0; i < point->m_items.GetSize(); i += 3)
		{
			lglNormal(pDC->m_pGraphics3D, point->m_items[i+0], point->m_items[i+1], point->m_items[i+2]);

			if (m_colorPerVertex->m_value && i+2 < ncolors)
			{
				pDC->m_pGraphics3D->glColorf(color->m_items[i][0], color->m_items[i][1], color->m_items[i][2]);
				pDC->m_pGraphics3D->glVertexf(point->m_items[i][0], point->m_items[i][1], point->m_items[i][2]);

				pDC->m_pGraphics3D->glColorf(color->m_items[i+1][0], color->m_items[i+1][1], color->m_items[i+1][2]);
				pDC->m_pGraphics3D->glVertexf(point->m_items[i+1][0], point->m_items[i+1][1], point->m_items[i+1][2]);

				pDC->m_pGraphics3D->glColorf(color->m_items[i+2][0], color->m_items[i+2][1], color->m_items[i+2][2]);
				pDC->m_pGraphics3D->glVertexf(point->m_items[i+2][0], point->m_items[i+2][1], point->m_items[i+2][2]);
			}
			else
			{
				pDC->m_pGraphics3D->glVertexf(point->m_items[i][0], point->m_items[i][1], point->m_items[i][2]);
				pDC->m_pGraphics3D->glVertexf(point->m_items[i+1][0], point->m_items[i+1][1], point->m_items[i+1][2]);
				pDC->m_pGraphics3D->glVertexf(point->m_items[i+2][0], point->m_items[i+2][1], point->m_items[i+2][2]);
			}
		}

		pDC->m_pGraphics3D->glEnd();

		pDC->m_pGraphics3D->PopAttrib();
	}
#endif
#endif
}

}	// x3d
}
