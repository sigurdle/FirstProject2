#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

SphereShape::~SphereShape()
{
}

bool SphereShape::IsValid(ImmediateRenderContext* renderContext)
{
	return m_d3d10_VertexBuffer[0] != NULL;
}

/*
 * Convert degrees to radians:
 */
#define DEG_TO_RAD(A)   ((A)*(M_PI/180.0))


#define TXTR_COORD(x,y)    /*if (qobj->TextureFlag)*/ *textureCoord++ = LDraw::vector2f(x,y)

/*
 * Sin and Cos for degree angles:
 */
#define SIND( A )   sin( (A)*(M_PI/180.0) )
#define COSD( A)    cos( (A)*(M_PI/180.0) )

void SphereShape::Create(RenderContext* renderContext, double radius, int slices, int stacks)
{
	m_slices = slices;
	m_stacks = stacks;

	float drho, dtheta;
	float t, ds, dt;
	int imin, imax;
	float nsign;

	__try
	{

	 /*  if (qobj->Orientation==GLU_INSIDE)
		{
		 nsign = -1.0;
	   }
	   else
		*/
		{
		  nsign = 1.0;
	   }
		
	   drho = M_PI / (GLfloat) stacks;
	   dtheta = 2.0f * M_PI_f / (GLfloat) slices;

	#if 0
		if (true)
		{
			/* draw +Z end as a triangle fan */
			pG->glBegin( GL_TRIANGLE_FAN );
			pG->glNormalf( 0.0, 0.0, 1.0 );
			TXTR_COORD(0.5,1.0);
			pG->glVertexf( 0.0, 0.0, nsign * radius );
			for (j=0;j<=slices;j++)
			{
				theta = (j==slices) ? 0.0 : j * dtheta;
				x = -sin(theta) * sin(drho);
				y = cos(theta) * sin(drho);
				z = nsign * cos(drho);
				if (normals)  pG->glNormalf( x*nsign, y*nsign, z*nsign );
				pG->glVertexf( x*radius, y*radius, z*radius );
			}
			pG->glEnd();
		}
	#endif

		ds = 1.0f / slices;
		dt = 1.0f / stacks;
		t = 1.0f;  /* because loop now runs from 0 */

		if (true/*qobj->TextureFlag*/)
		{
			imin = 0;
			imax = stacks;
		}
		else
		{
			imin = 1;
			imax = stacks-1;
		}

		VERTEX_XYZ_NORMAL* vertices = (VERTEX_XYZ_NORMAL*)_malloca((stacks)*(slices+1)*2*sizeof(VERTEX_XYZ_NORMAL));
		VERTEX_XYZ_NORMAL* vertex = vertices;

		gm::vector2f* texCoords = (gm::vector2f*)_malloca((stacks)*(slices+1)*2*sizeof(gm::vector2f));
		gm::vector2f* texCoord = texCoords;

		/* draw intermediate stacks as quad strips */
		for (int i = imin; i < imax; ++i)
		{
			float rho = i * drho;
		//	pG->glBegin( GL_QUAD_STRIP );
			float s = 0.0;

			for (int j = 0; j <= slices; ++j)
			{
				float theta = (j==slices) ? 0.0 : j * dtheta;

				float x, y, z;

				x = -sin(theta) * sin(rho);
				y = cos(theta) * sin(rho);
				z = nsign * cos(rho);
				vertex->normal = gm::vector3f(x*nsign, y*nsign, z*nsign);
				*texCoord++ = gm::vector2f(s,t);
				vertex->position = gm::vector3f(x*radius, y*radius, z*radius);
				++vertex;

				x = -sin(theta) * sin(rho+drho);
				y = cos(theta) * sin(rho+drho);
				z = nsign * cos(rho+drho);
				vertex->normal = gm::vector3f(x*nsign, y*nsign, z*nsign);
				*texCoord++ = gm::vector2f(s, t-dt);
				s += ds;
				vertex->position = gm::vector3f(x*radius, y*radius, z*radius);
				++vertex;
			}

		//	pG->glEnd();
			t -= dt;
		}

	#if 0
		if (true)
		{
			/* draw -Z end as a triangle fan */
			pG->glBegin( GL_TRIANGLE_FAN );
			pG->glNormalf( 0.0, 0.0, -1.0 );
			TXTR_COORD(0.5,0.0);
			pG->glVertexf( 0.0, 0.0, -radius*nsign );
			rho = M_PI - drho;
			s = 1.0;
			t = dt;
			for (j=slices;j>=0;j--)
			{
				theta = (j==slices) ? 0.0 : j * dtheta;
				x = -sin(theta) * sin(rho);
				y = cos(theta) * sin(rho);
				z = nsign * cos(rho);
				if (normals)  pG->glNormalf( x*nsign, y*nsign, z*nsign );
				TXTR_COORD(s,t);
				s -= ds;
				pG->glVertexf( x*radius, y*radius, z*radius );
			}
			pG->glEnd();
		}

		//BuildEdges();
	#endif

		{
		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = (vertex - vertices)*sizeof(VERTEX_XYZ_NORMAL);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[0]);
		}

		{
		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = (texCoord - texCoords)*sizeof(gm::vector2f);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = texCoords;
		renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[1]);
		}

		_freea(vertices);
		_freea(texCoord);
	}
	__except( GetExceptionCode() == STATUS_STACK_OVERFLOW )
	{
		_resetstkoflw();
	}
}

void SphereShape::Draw(ImmediateRenderContext* renderContext)
{
	UINT stride[2] = { sizeof(VERTEX_XYZ_NORMAL), sizeof(gm::vector2f) };
	UINT offset[2] = {0,0};
	renderContext->GetRT()->m_d3d10->m_device->IASetVertexBuffers(0, 2, m_d3d10_VertexBuffer, stride, offset);

	renderContext->GetRT()->m_d3d10->m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	int count = (m_slices+1)*2;
	int start = 0;
	for (uint i = 0; i < m_stacks; ++i)
	{
		renderContext->GetRT()->m_d3d10->m_deviceContext->Draw(count, start);
		start += count;
	}
}

}
}
}
