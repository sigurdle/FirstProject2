#include "stdafx.h"
#include "X3D2.h"
#include "IndexedFaceSet.h"

#include "../GUI/CTriangulator.h"

namespace System
{

LFCEXT gm::vector3f proj(gm::vector3f a, gm::vector3f u);

namespace x3d
{

TypedX3DFieldDefinition<MFInt32>* IndexedFaceSet::get_coordIndexFieldDef()
{
	static TypedX3DFieldDefinition<MFInt32> coordIndex("coordIndex", SAIFieldAccess_initializeOnly, offsetof(IndexedFaceSet, m_coordIndex));
	return &coordIndex;
}

TypedX3DFieldDefinition<MFInt32>* IndexedFaceSet::get_texCoordIndexFieldDef()
{
	static TypedX3DFieldDefinition<MFInt32> texCoordIndex("texCoordIndex", SAIFieldAccess_initializeOnly, offsetof(IndexedFaceSet, m_texCoordIndex));
	return &texCoordIndex;
}

TypedX3DFieldDefinition<MFInt32>* IndexedFaceSet::get_normalIndexFieldDef()
{
	static TypedX3DFieldDefinition<MFInt32> normalIndex("normalIndex", SAIFieldAccess_initializeOnly, offsetof(IndexedFaceSet, m_normalIndex));
	return &normalIndex;
}

TypedX3DFieldDefinition<SFBool>* IndexedFaceSet::get_convexFieldDef()
{
	static TypedX3DFieldDefinition<SFBool> convex("convex", SAIFieldAccess_initializeOnly, offsetof(IndexedFaceSet, m_convex), true);
	return &convex;
}

NodeType* IndexedFaceSet::nodeType(GetNodeType());

NodeType* IndexedFaceSet::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_coordIndexFieldDef(),
		get_texCoordIndexFieldDef(),
		get_normalIndexFieldDef(),
		get_convexFieldDef(),
	};

	static NodeType nodeType("IndexedFaceSet", typeid(IndexedFaceSet), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

IndexedFaceSet::IndexedFaceSet() : X3DComposedGeometryNode(GetNodeType()),
	m_coordIndex(new MFInt32(get_coordIndexFieldDef(), this)),
	m_normalIndex(new MFInt32(get_normalIndexFieldDef(), this)),
	m_texCoordIndex(new MFInt32(get_texCoordIndexFieldDef(), this)),
	m_convex(new SFBool(get_convexFieldDef(), this)),
	m_bInited(false)
{
}

Coordinate* IndexedFaceSet::getCoord()
{
	return dynamic_cast<Coordinate*>(m_coord->getValue());
}

TextureCoordinate* IndexedFaceSet::getTexCoord()
{
	return dynamic_cast<TextureCoordinate*>(m_texCoord->getValue());
}

int IndexedFaceSet::getCoordIndex1Value(uint n)
{
	return m_coordIndex->get1Value(n);
}

// virtual
bool IndexedFaceSet::Within(const gm::vector3f& start, const gm::vector3f& end, gm::vector3f& plane_normal, gm::vector3f& pt, double& d2)
{
	ASSERT(0);
#if 0
	CArray<LDraw::vector3f,LDraw::vector3f > points;

	<ILCoordinate> coordinate = m_coord->m_value;
	<ILTextureCoordinate> texcoordinate = m_texCoord->m_value;
	if (coordinate)
	{
		MFVec3f* point = static_cast<CLCoordinate*>(coordinate.p)->m_point;

		for (int i = 0; i < point->m_items.GetSize(); i++)
		{
			LDraw::vector3f pt = point->m_items[i];
			points.Add(pt);
		}
	}

	int i = 0;
	while (i < m_coordIndex->m_items.GetSize())
	{
		CArray<LDraw::vector3f, LDraw::vector3f > xyz;

		int j = i;
		while (j < m_coordIndex->m_items.GetSize())
		{
			long index = m_coordIndex->m_items[j];
			if (index == -1)
			{
				j++;
				break;
			}
			xyz.InsertAt(0, points[index]);
			j++;
		}

		ASSERT(xyz.GetSize() >= 3);

		i = j;

		// TODO, check CCW
		LDraw::vector3f a = xyz[2];
		LDraw::vector3f b = xyz[1];
		LDraw::vector3f c = xyz[0];

		plane_normal = cross(a-b, c-b);
		plane_normal.normalize();

		//gmVector3 plane_normal = gmVector3(0, 0, -1);
		double plane_distance = dot(plane_normal, a/*any point on plane will do??*/);

	//	plane_distance = -plane_distance;	// ??

		int pos_class = ClassifyPoint(plane_normal, plane_distance, start);
		int dest_class = ClassifyPoint(plane_normal, plane_distance, end);

		if (pos_class != dest_class)
		{
			LDraw::vector3f ray = start - end;
			double d = dot(plane_normal, ray);
			if (d != 0)
			{
				double t = - (dot(plane_normal, start) + plane_distance ) / d;

			//	end = start + (ray * t);

				pt = start + (ray * t);

				double sum = CalcAngleSum(*(XYZ*)&pt, (XYZ*)xyz.GetData(), xyz.GetSize());
				if (fabs(sum-TWOPI) < 0.00001)
				{
					return TRUE;
				}
			}
		}
	}
#endif
	return false;
}

struct STREAM0_VERTEX
{
	gm::vector3f position;
	gm::vector3f normal;
};

/*
class MyTess : public ID2D1TessellationSink
{
public:
	virtual ULONG __stdcall AddRef() override
	{
		return 1;
	}

	virtual ULONG __stdcall Release() override
	{
		return 1;
	}

	virtual HRESULT __stdcall QueryInterface(const ::IID&, void** ppv ) override
	{
		return 1;
	}

	virtual void __stdcall AddTriangles(const D2D1_TRIANGLE *triangles, UINT trianglesCount) override
	{
		while (trianglesCount--)
		{
			m_points.push_back(proj(Vec3f(triangles->point1.x, triangles->point1.y, 0), plane_normal));
			m_points.push_back(proj(Vec3f(triangles->point2.x, triangles->point2.y, 0), plane_normal));
			m_points.push_back(proj(Vec3f(triangles->point3.x, triangles->point3.y, 0), plane_normal));
		}
	}

	virtual HRESULT __stdcall Close() override
	{
		return S_OK;
	}

	Vec3f plane_normal;

	vector<Vec3f> m_points;
};
*/

#if 0
void TriangulatePolygon(Vec3f* points, uint npoints, ID2D1GeometrySink* sink)
{
//	Vec3f plane_normal = LDraw::cross(points[1] - points[0], points[+] - points[0]);
//	plane_normal.normalize();

	Vec3f screen_plane(0, 0, 1);

	for (int i = 1; i < npoints; ++i)
	{
		Vec3f point = proj(points[i]-points[i-1], screen_plane);

		if (i == 0)
			sink->BeginFigure(D2D1::Point2F(point.x, point.y), D2D1_FIGURE_BEGIN_FILLED);
		else
			sink->AddLine(D2D1::Point2F(point.x, point.y));
	}

	CTriangulator triangulator;
	triangulator.add();


}

void TriangulatePolygon(Vec3f* points, uint npoints, MyTess& tessSink)
{
	Vec3f plane_normal = LDraw::cross(points[1] - points[0], points[+] - points[0]);
	plane_normal.normalize();

	ID2D1PathGeometry* geom;
	GL::Direct10::get_D2DFactory()->CreatePathGeometry(&geom);

	ID2D1GeometrySink* sink;
	geom->Open(&sink);

	TriangulatePolygon(points, npoints, sink);

	sink->Close();

	tessSink.plane_normal = plane_normal;
	geom->Tessellate(NULL, &tessSink);

	geom->Release();
	sink->Release();

}
#endif

// virtual
void IndexedFaceSet::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
//	glFrontFace(GL_CW);	// TODO

//	Graphics::Graphics3D* p3D = pDC->m_pGraphics3D;
//	LDraw::OpenGL_I* pGL = dynamic_cast<LDraw::OpenGL_I*>(p3D->m_pGraphics->m_device);

	if (!m_bInited)
	{
		m_bInited = true;

		Coordinate* coord = getCoord();
		TextureCoordinate* texCoord = getTexCoord();

		Vec3f* points = coord->getPointField()->m_items.begin();
		Vec2f* texpoints = NULL;
		if (texCoord)
		{
			texpoints = texCoord->getPointField()->m_items.begin();
		}

		MFInt32* coordIndex = getCoordIndexField();
		MFInt32* texCoordIndex = getTexCoordIndexField();

		unsigned int coordIndicesCount = coordIndex->m_items.size();
		int32* coordIndices = coordIndex->m_items.begin();
		int32* texCoordIndices = NULL;
		if (texCoordIndex->get_size() == 0)
		{
			texCoordIndices = m_coordIndex->m_items.begin();
		}
		else
		{
			texCoordIndices = texCoordIndex->m_items.begin();
		}

		/*
		{
			uint i = 0;
			while (i < coordIndicesCount)
			{
				++ntriangles;
				i += 3;

				while (coordIndices[i] != -1)
				{
					++ntriangles;
					++i;
				}
				++i;
			}
		}
		*/

		STREAM0_VERTEX* bufferData = new STREAM0_VERTEX[4000];
		Vec2f* texcoords = new Vec2f[4000];

		uint nvertices = 0;

		vector<int> indices;

		uint n = 0;
		while (n < coordIndicesCount)
		{
			CTriangulator triangulator;

			Vec3f a = points[coordIndices[n]];
			Vec3f b = points[coordIndices[n+1]];
			Vec3f c = points[coordIndices[n+2]];

			Vec3f plane_normal = cross(a-b, c-b);
			plane_normal.normalize();

			int mode;

			if (fabs(fabs(plane_normal.x)-1.0f) <= 0.05)
			{
				mode = 1;
			}
			else if (fabs(fabs(plane_normal.y)-1.0f) <= 0.05)
			{
				mode = 2;
			}
			else
			{
				mode = 0;
			}

			int start = n;
			while (n < coordIndicesCount && coordIndices[n] != -1)
			{
				if (mode == 0)
					triangulator.add(points[coordIndices[n]]);
				else if (mode == 1)
					triangulator.add(points[coordIndices[n]].yzx());
				else
					triangulator.add(points[coordIndices[n]].xzy());

				++n;
			}
			++n;

			indices.clear();
			triangulator.triangulate(indices);
			ASSERT((indices.size() % 3) == 0);
			ASSERT(indices.size() >= 3);

			for (uint i = 0; i < indices.size(); ++i)
			{
				int index = indices[i];
				bufferData[nvertices].position = points[coordIndices[start + index]];

				if (texCoord)
				{
					texcoords[nvertices] = texpoints[texCoordIndices[start + index]];
				}

				ASSERT(nvertices < 4000);
				++nvertices;
			}
		}

		m_nvertices = nvertices;
		uint ntriangles = nvertices/3;

	//	STREAM0_VERTEX* bufferData = new STREAM0_VERTEX[m_nvertices];
	//	Vec2f* texcoords = new Vec2f[m_nvertices];

		/*
		ntriangles = 0;
		uint i = 0;
		while (i < coordIndicesCount)
		{
			int first = i;

			bufferData[ntriangles*3+0].position = points[coordIndices[first]];
			bufferData[ntriangles*3+1].position = points[coordIndices[i+1]];
			bufferData[ntriangles*3+2].position = points[coordIndices[i+2]];

			if (texCoord)
			{
				texcoords[ntriangles*3+0] = texpoints[texCoordIndices[first]];
				texcoords[ntriangles*3+1] = texpoints[texCoordIndices[i+1]];
				texcoords[ntriangles*3+2] = texpoints[texCoordIndices[i+2]];
			}

			++ntriangles;
			i += 3;

			// Trianglefan
			while (coordIndices[i] != -1)
			{
				bufferData[ntriangles*3+0].position = points[coordIndices[first]];
				bufferData[ntriangles*3+1].position = points[coordIndices[i-1]];
				bufferData[ntriangles*3+2].position = points[coordIndices[i]];

				if (texCoord)
				{
					texcoords[ntriangles*3+0] = texpoints[texCoordIndices[first]];
					texcoords[ntriangles*3+1] = texpoints[texCoordIndices[i-1]];
					texcoords[ntriangles*3+2] = texpoints[texCoordIndices[i]];
				}

				++ntriangles;
				++i;
			}
			++i;
		}
		*/

		/*
		for (unsigned int i = 0; i < ncoords; i++)
		{
			bufferData[i].position = points[i];
		}
		*/

		for (uint i = 0; i < ntriangles; ++i)
		{
			Vec3f normal = gm::cross(bufferData[i*3+1].position - bufferData[i*3].position, bufferData[i*3+2].position - bufferData[i*3].position);
			normal.normalize();

			bufferData[i*3].normal = normal;
			bufferData[i*3+1].normal = normal;
			bufferData[i*3+2].normal = normal;
		}

		ASSERT(m_nvertices > 0);

//		if (m_nvertices > 0)
		{
			{
				D3D10_BUFFER_DESC bd;
				bd.Usage = D3D10_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(STREAM0_VERTEX)*m_nvertices;
				bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
				bd.CPUAccessFlags = 0;
				bd.MiscFlags = 0;
				D3D10_SUBRESOURCE_DATA InitData;
				InitData.pSysMem = bufferData;
				pDC->m_renderContext->GetRT()->m_d3d10->m_device->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[0]);
			}
			{
				D3D10_BUFFER_DESC bd;
				bd.Usage = D3D10_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(Vec2f)*m_nvertices;
				bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
				bd.CPUAccessFlags = 0;
				bd.MiscFlags = 0;
				D3D10_SUBRESOURCE_DATA InitData;
				InitData.pSysMem = texcoords;
				pDC->m_renderContext->GetRT()->m_d3d10->m_device1->CreateBuffer(&bd, &InitData, &m_d3d10_VertexBuffer[1]);
			}
		}
#if 0
		else
		{
	#if 0
			m_vertexBuffer0 = p3D->CreateVertexBuffer(sizeof(STREAM0_VERTEX)*m_nvertices, bufferData, GL_STATIC_DRAW);
		//	m_vertexBuffer1 = pDC->m_pGraphics3D->CreateVertexBuffer(sizeof(LDraw::vector3f)*m_coord->get_size(), m_normals.begin());
	#endif
			m_vertexBuffer0 = p3D->m_pGraphics->m_bufferData->m_vertexBuffer;
			m_vertexOffsetInBytes = p3D->m_pGraphics->m_bufferData->m_vertexOffsetInBytes;

			p3D->m_pGraphics->m_device->VertexBufferSubData(m_vertexBuffer0, m_vertexOffsetInBytes, sizeof(STREAM0_VERTEX)*m_nvertices, bufferData);

			p3D->m_pGraphics->m_bufferData->m_vertexOffsetInBytes += sizeof(STREAM0_VERTEX)*m_nvertices;

			LDraw::VertexDeclElement elements[64] =
			{
				{"POSITION", 0, 0, LDraw::DECLTYPE_FLOAT3, 0},
				{"NORMAL", 0, 3*4, LDraw::DECLTYPE_FLOAT3, 0},
			//	{"COLOR", 2, 0, LDraw::DECLTYPE_FLOAT3, 0},
			};

			unsigned int nelements = 2;
			m_vertexDeclaration = p3D->CreateVertexDeclaration(elements, nelements);
		}
#endif

		delete[] bufferData;
		delete[] texcoords;
	}

	if (m_nvertices)
	{
		{
			UINT stride[2] = { sizeof(STREAM0_VERTEX), sizeof(gm::vector2f) };
			UINT offset[2] = {0,0};
			pDC->m_renderContext->GetRT()->m_d3d10->m_device1->IASetVertexBuffers(0, 2, m_d3d10_VertexBuffer, stride, offset);
		}

		if (false)
		{
			bool multisample = true;
			pDC->m_renderContext->GetRT()->m_d3d10->m_device1->RSSetState(Graphics::Direct10::s.m_pRasterizerState[1][getSolid()][multisample]);
		}

	//	ASSERT(m_d3d10_IndexBuffer);
	//	renderContext->GetRT()->m_d3d10->m_device->IASetIndexBuffer(m_d3d10_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		pDC->m_renderContext->GetRT()->m_d3d10->m_device1->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	renderContext->GetRT()->m_d3d10->m_device->DrawIndexed(36, 0/*StartIndexLocation*/, 0/*BaseVertexLocation*/);
		pDC->m_renderContext->GetRT()->m_d3d10->m_device1->Draw(m_nvertices, 0);

		/*
		p3D->SetVertexDeclaration(m_vertexDeclaration);
		p3D->SetVertexBuffer(0, m_vertexBuffer0, m_vertexOffsetInBytes, sizeof(STREAM0_VERTEX));

		p3D->SetPrimitiveTopology(GL_TRIANGLES);
		p3D->Draw(0, m_nvertices);
		*/
	}

	return;

	if (!m_bInited)
	{
		m_bInited = true;

		Coordinate* coordinate = dynamic_cast<Coordinate*>(m_coord->m_value);
		Normal* pNormal = dynamic_cast<Normal*>(m_normal->m_value);

		X3DTextureCoordinateNode* texCoordNode = dynamic_cast<X3DTextureCoordinateNode*>(m_texCoord->m_value);

		if (texCoordNode)
		{
			MultiTextureCoordinate* multitexcoordinate = dynamic_cast<MultiTextureCoordinate*>(texCoordNode);
			if (multitexcoordinate)
			{
				for (size_t i = 0; i < multitexcoordinate->get_texCoordField()->m_items.size(); ++i)
				{
					X3DTextureCoordinateNode* texCoordNode = dynamic_cast<X3DTextureCoordinateNode*>(multitexcoordinate->get_texCoordField()->m_items[i]);
					ASSERT(texCoordNode);
					m_texcoordNode.push_back(texCoordNode);
				}
			}
			else
			{
				m_texcoordNode.Add(texCoordNode);
			}
		}

		if (coordinate)
		{
			MFVec3f* point = coordinate->getPointField();

			//MFVec2f* texpoint;

			MFInt32* useTexCoordIndex;

			if (texCoordNode)
			{
			//	if (texcoordinate)
			//		texpoint = dynamic_cast<MFVec2f*>(texcoordinate->m_point);

				if (m_texCoordIndex->m_items.GetSize() > 0)
				{
					if (m_texCoordIndex->m_items.GetSize() != m_coordIndex->m_items.GetSize())
					{
						// TODO, mark this object with some kind of error flag
						// m_bError = TRUE
						return;	// Error
					}
					useTexCoordIndex = m_texCoordIndex;
				}
				else
				{
					useTexCoordIndex = m_coordIndex;
				}
			}

			ASSERT(m_ccw->m_value == true);

			if (m_convex->m_value == true)
			{
				// triangulate (by adding indices, don't add any new points)

				uint32 normalIndexIndex = 0;

				{
					int i = 0;
					while (i < m_coordIndex->m_items.GetSize())
					{
						int j = i;
						int count = 0;
						while (j < m_coordIndex->m_items.GetSize())
						{
							long index = m_coordIndex->m_items[j];
							if (index == -1)
							{
								j++;
								break;
							}

							count++;
							j++;
						}

						// TODO, add warning to some kind of log
						if (count < 3)
						{
						;//	MessageBeep(-1);
						}

						for (int k = 0; k < count-2; k++)
						{
							m_indices.Add(m_coordIndex->m_items[i]);
							m_indices.Add(m_coordIndex->m_items[i+k+1]);
							m_indices.Add(m_coordIndex->m_items[i+k+2]);

							if (texCoordNode)
							{
								/*
								for (int i = 0; i < m_texcoordNode.size(); i++)
									{
										CLTextureCoordinate* texcoordinate = dynamic_cast<CLTextureCoordinate*>(m_texcoordNode[i]);
										if (texcoordinate)
										{
											MFVec2f* texpoint = dynamic_cast<MFVec2f*>(texcoordinate->m_point);
											LDraw::vector2f& texvec = texpoint->m_items[texIndex];

											m_texcoords[i].Add(LDraw::vector3f(texvec[0], texvec[1], 0));
										}
									}
								}
								*/
								m_texcoordIndices.push_back(useTexCoordIndex->m_items[i+k]);
								m_texcoordIndices.push_back(useTexCoordIndex->m_items[i+k+1]);
								m_texcoordIndices.push_back(useTexCoordIndex->m_items[i+k+2]);
							}
						}

						if (pNormal)
						{
							if (m_normalPerVertex->m_value == true)
							{
								for (int k = 0; k < count-2; k++)
								{
									m_normalIndices.Add(m_normalIndex->m_items[i]);
									m_normalIndices.Add(m_normalIndex->m_items[i+k+1]);
									m_normalIndices.Add(m_normalIndex->m_items[i+k+2]);
								}
							}
							else
							{
								ASSERT(0);	// TODO, test this
								for (int k = 0; k < count-2; k++)
								{
									m_normalIndices.push_back(m_normalIndex->m_items[normalIndexIndex]);
									m_normalIndices.push_back(m_normalIndex->m_items[normalIndexIndex]);
									m_normalIndices.push_back(m_normalIndex->m_items[normalIndexIndex]);
								}
							}
						}

						i = j;
						normalIndexIndex++;
					}
				}

				int npoints = point->get_size();

				if (pNormal == NULL)
				{
					struct Face
					{
					//	int a,b,c;
						gm::vector3f normal;
					};

					class FacePtr
					{
					public:
						FacePtr(Face* _pface, FacePtr* _next = nullptr)
						{
							pface = _pface;
							next = _next;
						}
						Face* pface;
						FacePtr* next;
					};

					FacePtr** pointFaces = new FacePtr*[npoints];
					std::memset(pointFaces, 0, sizeof(FacePtr*) * npoints);

					{
						for (int i = 0; i < m_indices.GetSize(); i += 3)
						{
							int c = m_indices[i];
							int b = m_indices[i+1];
							int a = m_indices[i+2];

							Face* pface = new Face;

							{
								gm::vector3f pa = point->m_items[a];
								gm::vector3f pb = point->m_items[b];
								gm::vector3f pc = point->m_items[c];
								pface->normal = gm::cross(pa-pb, pc-pb);
							}

							pointFaces[a] = new FacePtr(pface, pointFaces[a]);
							pointFaces[b] = new FacePtr(pface, pointFaces[b]);
							pointFaces[c] = new FacePtr(pface, pointFaces[c]);

							m_normalIndices.Add(c);
							m_normalIndices.Add(b);
							m_normalIndices.Add(a);
						}
					}

					for (int i = 0; i < npoints; i++)
					{
						/*
						int a = m_coordIndex->m_items[i+2];
						int b = m_coordIndex->m_items[i+1];
						int c = m_coordIndex->m_items[i+0];
						*/

						gm::vector3f avgnormal;
						FacePtr* facep = pointFaces[i];
						while (facep)
						{
							avgnormal += facep->pface->normal;
							facep = facep->next;
						}

						if (avgnormal[0] != 0 || avgnormal[1] != 0 || avgnormal[2] != 0)
						{
							avgnormal.normalize();
						}

						m_normals.Add(avgnormal);
					}

					// TODO, also delete individual faces
					delete[] pointFaces;
				}
				else
				{
					MFVec3f* normalVector = pNormal->getVectorField();
					uint32 nnormals = normalVector->get_size();

					for (int i = 0; i < nnormals; i++)
					{
						m_normals.Add(normalVector->m_items[i]);
					}
				}

				for (int i = 0; i < npoints; i++)
				{
					m_points.Add(point->m_items[i]);
				}
#if 0
				//int i = 0;
				//while (i < m_coordIndex->m_items.GetSize())
				for (int i = 0; i < m_indices.size(); i++)
				{
					//CArray<gmVector3,gmVector3&> vertices;

					/*
					int j = i;
					int count = 0;
					while (j < m_coordIndex->m_items.GetSize())
					{
						long index = m_coordIndex->m_items[j];
						if (index == -1)
						{
							j++;
							break;
						}

						count++;
						//glVertex3(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
					//	vertices.Add(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
						j++;
					}
					//int count = j-i;

				//	ASSERT(count == 3);
				*/

				//	pDC->m_pGraphics3D->glBegin(GL_POLYGON);

					/*
					LDraw::vector3f n = LDraw::cross(a-b, c-b);
					*/

					if (TRUE)
					{
					//	for (int k = count-1; k >= 0; k--)
						for (int k = 0; k < count-2; k++)
						{
							/*
							if (texCoordNode)
							{
								long texIndex = useTexCoordIndex->m_items[i+k];

								for (int i = 0; i < m_texcoordNode.size(); i++)
								{
									CLTextureCoordinate* texcoordinate = dynamic_cast<CLTextureCoordinate*>(m_texcoordNode[i]);
									if (texcoordinate)
									{
										MFVec2f* texpoint = dynamic_cast<MFVec2f*>(texcoordinate->m_point);
										LDraw::vector2f& texvec = texpoint->m_items[texIndex];

										m_texcoords[i].Add(LDraw::vector3f(texvec[0], texvec[1], 0));
									}
								}
							}
							*/

							LDraw::vector3f& v = point->m_items[m_indices[i+k]];
							LDraw::vector3f& n = pointNormals[m_indices[i+k]];

							m_normals.Add(n);
							m_points.Add(v);

						//	m_indices.Add(counter++);
						}
					}
					/*
					else
					{
						for (int k = 0; k < count; k++)
						{
							if (texcoordinate)
							{
								long texIndex = useTexCoordIndex->m_items[i+k];
								LDraw::vector2f& texvec = texpoint->m_items[texIndex];
								pDC->m_pGraphics3D->glTexCoordf(texvec[0], texvec[1]);
							}
							LDraw::vector3f& v = point->m_items[m_coordIndex->m_items[i+k]];
							pDC->m_pGraphics3D->glVertex(v);
						}
					}
					*/

					i = j;

				//	pDC->m_pGraphics3D->glEnd();
				}
#endif
			}
			else
			{
				// TODO, tesselate
				ASSERT(0);
			}
		}
	}

	/*
	pDC->m_pGraphics3D->EnableClientState(GL_VERTEX_ARRAY);
	pDC->m_pGraphics3D->glVertexPointer(3, GL_FLOAT, 0, m_points.begin());

	pDC->m_pGraphics3D->EnableClientState(GL_NORMAL_ARRAY);
	pDC->m_pGraphics3D->glNormalPointer(GL_FLOAT, 0, m_normals.begin());
	*/

	/*
	for (int i = 0; 
	if (m_texcoords.size())
	{
		pDC->m_pGraphics3D->EnableClientState(GL_TEXTURE_COORD_ARRAY);
		pDC->m_pGraphics3D->glTexCoordPointer(3, GL_FLOAT, 0, m_texcoords.begin());
	}
	else
	{
		pDC->m_pGraphics3D->DisableClientState(GL_TEXTURE_COORD_ARRAY);
		pDC->m_pGraphics3D->glTexCoordPointer(3, GL_FLOAT, 0, NULL);
	}
	*/

	//pDC->m_pGraphics3D->glCullFace(GL_BACK);
	if (m_solid->getValue() == false)
	{
//		pDC->m_pGraphics3D->Disable(GL_CULL_FACE);
	}
	else
	{
	//	pDC->m_pGraphics3D->Enable(GL_CULL_FACE);
	}

	ASSERT(0);
#if 0
	if (true)
	{
		pDC->m_pGraphics3D->PushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

		pDC->m_pGraphics3D->EnableClientState(GL_VERTEX_ARRAY);
		pDC->m_pGraphics3D->EnableClientState(GL_NORMAL_ARRAY);
	//	pDC->m_pGraphics3D->EnableClientState(GL_TEXTURE_COORD_ARRAY);

		pDC->m_pGraphics3D->VertexPointer(0, 3, GL_FLOAT, 0, m_points.GetData());
		pDC->m_pGraphics3D->NormalPointer(0, GL_FLOAT, 0, m_normals.GetData());
	//	pDC->m_pGraphics3D->glTexCoordPointer(3, GL_FLOAT, 0, m_texcoords.begin());

		pDC->m_pGraphics3D->DrawElements(GL_TRIANGLES, m_indices.GetSize(), GL_UNSIGNED_INT, m_indices.GetData());

		pDC->m_pGraphics3D->PopClientAttrib();
	}
	else
	//pDC->m_pGraphics3D->glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, m_indices.begin());
	{
		pDC->m_pGraphics3D->glBegin(GL_TRIANGLES);

		for (int i = 0; i < m_indices.GetSize(); i++)
		{
			int index = m_indices[i];
			int normalIndex = m_normalIndices[i];

			const LDraw::vector3f& normal = m_normals[normalIndex];
			const LDraw::vector3f& v = m_points[index];

			pDC->m_pGraphics3D->glNormal(normal);
			{
				/*
				for (int n = 0; n < 8; n++)
				{
					if (m_texcoords[n].size() > 0)
					{
						pDC->m_pGraphics3D->glMultiTexCoordf(GL_TEXTURE0 + n, m_texcoords[n][index][0], m_texcoords[n][index][1]);
					}
				}
				*/
				for (int n = 0; n < m_texcoordNode.GetSize(); n++)
				{
					X3DTextureCoordinateNode* texCoordNode = m_texcoordNode[n];

					TextureCoordinate* texcoordinate = dynamic_cast<TextureCoordinate*>(texCoordNode);
					if (texcoordinate)
					{
#if 1
						int index = m_texcoordIndices[i];

					//	const LDraw::vector2f& texcoord = m_texcoords[n][index];
						const LDraw::vector2f& texcoord = texcoordinate->m_point->m_items[index];
						pDC->m_pGraphics3D->glMultiTexCoordf(GL_TEXTURE0 + n, texcoord[0], texcoord[1]);
#endif
					}
					else if (TextureCoordinateGenerator* texgen = dynamic_cast<TextureCoordinateGenerator*>(texCoordNode))
					{
						if (*texgen->getMode() == L"SPHERE")
						{
							float matrix[16];
							pDC->m_pGraphics3D->GetFloatv(GL_MODELVIEW_MATRIX, matrix);

							LDraw::matrix3f modelview(matrix[0], matrix[4], matrix[8],
														matrix[1], matrix[5], matrix[9],
														matrix[2], matrix[6], matrix[10]);
							LDraw::matrix3f modelviewi = modelview.getInverse();

							LDraw::vector3f u = v * modelview;
							//u[2] = 0;
							if (u[0] != 0 || u[1] != 0 || u[2] != 0)
							{
								u.normalize();
							}

							LDraw::vector3f _normal = modelviewi * normal;
						//	if (m_enable.m_normalize)
							{
								if (_normal[0] != 0 || _normal[1] != 0 || _normal[2] != 0)
								{
									_normal.normalize();
								}
							}
							//LDraw::vector3f _normalT(_normal[2], _normal[1], _normal[0]);

							LDraw::vector3f r = u - 2*LDraw::dot(_normal, u)*_normal;

							float m = 2 * sqrt(r[0]*r[0] + r[1]*r[1] + (r[2] + 1) * (r[2] + 1));

							float s = r[0] / m + 0.5;
							float t = r[1] / m + 0.5;

							pDC->m_pGraphics3D->glMultiTexCoordf(GL_TEXTURE0 + n, s, t);
						}
						else
						{
							ASSERT(0);
						}

					//	MFVec2f* texpoint = dynamic_cast<MFVec2f*>(texcoordinate->m_point);
					//	LDraw::vector2f& texvec = texpoint->m_items[texIndex];
					//	m_texcoords[0].Add(LDraw::vector3f(texvec[0], 1 - texvec[1], 0));
					}
					else
						ASSERT(0);
				}
			}

			pDC->m_pGraphics3D->glVertex(v);
		}

		pDC->m_pGraphics3D->glEnd();
	}
#endif

//	EnableClientState(
}

// X3DBoundedImplImpl
BoundingBox IndexedFaceSet::CalculateBoundingBox(gm::matrix4f& transform)
{
//	if (!m_computedBBoxValid)
	{
		m_computedBBoxValid = true;

		Coordinate* coord = getCoord();
		TextureCoordinate* texCoord = getTexCoord();

		uint count = coord->getPointField()->get_size();

		Vec3f* points = coord->getPointField()->m_items.begin();
		if (count > 0)
		{
			MFInt32* coordIndex = getCoordIndexField();

			Vec3f pt = transform.transform(points[0]);

			Vec3f minV(pt);
			Vec3f maxV(pt);

			for (uint i = 0; i < count; ++i)
			{
				Vec3f pt = transform.transform(*points);

				minV[0] = MIN(minV[0], pt[0]);
				minV[1] = MIN(minV[1], pt[1]);
				minV[2] = MIN(minV[2], pt[2]);

				maxV[0] = MAX(maxV[0], pt[0]);
				maxV[1] = MAX(maxV[1], pt[1]);
				maxV[2] = MAX(maxV[2], pt[2]);

				++points;
			}

			Vec3f center = (maxV - minV);
			Vec3f size = minV + (center)/2;

			return BoundingBox(center, size);
		}
	}

	return BoundingBox(Vec3f(0,0,0), Vec3f(-1,-1,-1));
}

}	// x3d
}	// System
