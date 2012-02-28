#include "stdafx.h"
#include "Browser.h"
#include "View3D.h"

#include "../LXUI/UndoManager.h"

#include "PropertiesWindow.h"

extern "C"
{
	void WINAPI ShowCursor(int);
	void WINAPI SetCursorPos(int, int);
}

namespace System
{
extern __live_object_ptr<UI::ScrollViewer> m_propertyPalette;

namespace UI
{
namespace Media3D
{

void ComputeCombinedTransformChildren(Group* pGroup);
void ApplyBones(Group* pGroup);

Document3D::Document3D()
{
	m_views[0] = NULL;
	m_views[1] = NULL;
	m_views[2] = NULL;
	m_views[3] = NULL;

	m_undoManager = new UndoManager;	// ??

	m_currentTime = 0;

	m_object = NULL;
	m_glState = new LDraw::GLState;
	m_clientState = new LDraw::ClientState;

	m_objectMode = Mode_Model;

	//m_bitmap = LDraw::Bitmap("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.pcx");

	/*
	m_orientation.m_angle = 0;
	m_orientation.m_axis[0] = 0;
	m_orientation.m_axis[1] = 0;
	m_orientation.m_axis[2] = -1;
	*/

	m_orientation.m_angle = 0;
	m_orientation.m_axis[0] = 0;
	m_orientation.m_axis[1] = 0;
	m_orientation.m_axis[2] = -1;

	m_position[0] = 0;
	m_position[1] = 5;
	m_position[2] = 30;
}

void Document3D::ScanLights(Group* pGroup)
{
	for (int i = 0; i < pGroup->m_Children->m_items.GetSize(); i++)
	{
		Object3D* pObject = pGroup->m_Children->m_items[i];
		if (Group* pGroup2 = dynamic_cast<Group*>(pObject))
		{
			ScanLights(pGroup2);
		}
		else if (Light* pLight = dynamic_cast<Light*>(pObject))
		{
			pLight->m_location = pLight->m_combinedTransform.transform(LDraw::vector3f(0, 0, 0));
			m_lights.push_back(pLight);
		}
	}
}

void Document3D::SetCurrentTime(double currentTime)
{
	m_currentTime = currentTime;

	if (true)
	{
		for (int i = 0; i < m_animations.GetSize(); i++)
		{
			Animation* pAnimation = m_animations[i];

			int numKeys = pAnimation->m_keys.GetSize();

			int left;
			for (int nKey = 0; nKey < numKeys; nKey++)
			{
				if (pAnimation->m_keys[nKey]->m_time <= currentTime) left = nKey;
				else if (pAnimation->m_keys[nKey]->m_time > currentTime) break;
			}

			int right = left+1;
			if (left < 0) left = 0;
			if (right > numKeys-1) right = numKeys-1;

			double t;
			if (left != right)
			{
				t = (double)(currentTime - pAnimation->m_keys[left]->m_time) / (pAnimation->m_keys[right]->m_time - pAnimation->m_keys[left]->m_time);
			}
			else	// left = right
			{
				t = 0;
			}

			MatrixAnimation* pMatrixAnimation = (MatrixAnimation*)pAnimation;

			MatrixAnimationKey* pLeftKey = (MatrixAnimationKey*)pAnimation->m_keys[left];
			MatrixAnimationKey* pRightKey = (MatrixAnimationKey*)pAnimation->m_keys[right];

			Group* pGroup = dynamic_cast<Group*>(pAnimation->m_Target);
			if (pGroup)
			{
				float m1[16];
				pLeftKey->m_value->Get(m1);

				float m2[16];
				pRightKey->m_value->Get(m2);

				float m[16];
				for (int i = 0; i < 16; i++)
				{
					m[i] = m1[i] + (m2[i] - m1[i]) * t;
				}

				pGroup->m_transform = new LDraw::Matrix4(m);
			}
		}
	}

	UpdateScene();

	Invalidate();
}

void Document3D::UpdateScene()
{
	m_object->m_combinedTransform = LDraw::matrix4f::getIdentity();	// TODO, need only do this once
	ComputeCombinedTransformChildren(m_object);

	m_lights.clear();
	ScanLights(m_object);

	ApplyBones(m_object);
}

}	// Media3D
}	// UI

namespace LDraw
{
X3DEXT void gluSphere(LDraw::Graphics3D* pG, double radius, int slices, int stacks);
X3DEXT void gluCylinder(LDraw::Graphics3D* pG, double baseRadius, double topRadius, double height, int slices, int stacks);
}

}	// System

#include "Object3D.h"
#include "3DS.h"

namespace System
{
namespace UI
{
namespace Media3D
{

Camera::Camera() : m_Orientation(0, 0, -1, 0/*angle*/)
{
	m_Position = LDraw::vector3f(0, 0, 5);
	m_FieldOfView = 45;

	m_Orthographic = false;
}

/*
Point3D* PerspectiveCamera::get_Position()
{
	return m_Position;
}

void PerspectiveCamera::put_Position(Point3D* position)
{
	m_Position = position;
}
*/

AxisAngle Camera::get_Orientation()
{
	return m_Orientation;
}

void Camera::set_Orientation(const AxisAngle& orientation)
{
	m_Orientation = orientation;
}

double Camera::get_FieldOfView()
{
	return m_FieldOfView;
}

void Camera::set_FieldOfView(double fov)
{
	m_FieldOfView = fov;
}

LDraw::vector3f Camera::get_Position()
{
	return m_Position;
}

void Camera::set_Position(LDraw::vector3f position)
{
	m_Position = position;
}

bool Camera::get_Orthographic()
{
	return m_Orthographic;
}

void Camera::set_Orthographic(bool orthographic)
{
	m_Orthographic = orthographic;
}

void Camera::OnRender(LDraw::Graphics3D* pGraphics3D, int mode, Deformer* pDeformer)
{
}

void Camera::Apply(LDraw::Graphics3D* pGraphics3D, double w, double h)
{
	ASSERT(0);
#if 0

	pGraphics3D->Viewport(0.0, 0.0, w, h);

	pGraphics3D->MatrixMode(GL_PROJECTION);
	pGraphics3D->LoadIdentity();
//		glLoadMatrixd(projm);
//
	double fov;
	fov = get_FieldOfView();
	/*
	{
		fov = 180/4;
	}
	*/

	if (true)
	{
		pGraphics3D->Perspective(fov, (double)w / h, 1.0, 10000.0);
	}
	else
	{
	}

	pGraphics3D->MatrixMode(GL_MODELVIEW);
	pGraphics3D->LoadIdentity();

//	if (m_Camera)
	{
#if 0
		CLSFRotation* orientation = pViewpoint->m_orientation;
		CLSFVec3f* position = pViewpoint->m_position;
		gmVector3t<float> norientation = orientation->m_value.m_v;
		norientation.normalize();

		m_pGraphics3D->glRotatef(gmDegrees(orientation->m_value.m_a), -norientation);
#endif
		LDraw::vector3f position = get_Position();
		pGraphics3D->glTranslate(-position);
	}
	/*
	else
	{
		// TODO
	//	glTranslatef(0, 0, -180);
		//glTranslatef(0, 0, -10);
	}
	*/
#endif
}

Point3DfCollection::Point3DfCollection()
{
}

void Point3DfCollection::AddChild(Object* child)
{
	ASSERT(0);

//	m_items.Add(dynamic_cast<Point3D*>(child));
}

void Point3DfCollection::AddText(StringW* text)
{
}

void Point3DfCollection::append1Value(const float value[3])
{
	m_items.Add(LDraw::vector3f(value[0], value[1], value[2]));
}

IndexedFaceSet::IndexedFaceSet()
{
	m_points = NULL;
//	m_pointIndices = NULL;
//	m_normals = NULL;
//	m_normalIndices = NULL;
	m_texCoords = NULL;
	m_texCoordIndices = NULL;
}

unsigned int IndexedFaceSet::AddVertex(LDraw::vector3f v)
{
	unsigned int n = m_points->m_items.GetSize();
	m_points->m_items.Add(v);
	m_vertexEdges.Add(NULL);
	m_vertexFaces.Add(NULL);
	ASSERT(m_points->m_items.GetSize() == m_vertexEdges.GetSize());
	ASSERT(m_points->m_items.GetSize() == m_vertexFaces.GetSize());
	return n;
}

FaceList* Find(FaceList* facelist, uint nface)
{
	while (facelist)
	{
		if (facelist->nface == nface)
		{
			return facelist;
		}

		facelist = facelist->next;
	}

	return NULL;
}

void IndexedFaceSet::AddFaceEdge(uint nface, DirectedEdge edge)
{
	m_faces[nface].m_edges.Add(edge);
	uint v0 = GetEdgeVertex(edge, 0);
	uint v1 = GetEdgeVertex(edge, 1);

	if (Find(m_vertexFaces[v0], nface) == NULL)
		m_vertexFaces[v0] = new FaceList(nface, m_vertexFaces[v0]);

	if (Find(m_vertexFaces[v1], nface) == NULL)
		m_vertexFaces[v1] = new FaceList(nface, m_vertexFaces[v1]);
}

EdgeList* Find(IndexedFaceSet* faceset, EdgeList* edgelist, uint v0, uint v1)
{
	while (edgelist)
	{
		if (faceset->m_edges[edgelist->edge.GetIndex()].v[0] == v0 &&
			faceset->m_edges[edgelist->edge.GetIndex()].v[1] == v1)
		{
			return edgelist;
		}

		if (faceset->m_edges[edgelist->edge.GetIndex()].v[0] == v1 &&
			faceset->m_edges[edgelist->edge.GetIndex()].v[1] == v0)
		{
			return edgelist;
		}

		edgelist = edgelist->next;
	}

	return NULL;
}

DirectedEdge IndexedFaceSet::AddEdge(uint v0, uint v1)
{
	EdgeList* v0_edges = m_vertexEdges[v0];
//	EdgeList* v1_edges = m_vertexEdges[v1];

	while (v0_edges)
	{
//		if (m_edges[v0_edges->edge.GetIndex()].v[v0_edges->edge.IsBackward()] == v0 && m_edges[v0_edges->edge.GetIndex()].v[!v0_edges->edge.IsBackward()] == v1)
//			return DirectedEdge(v0_edges->edge.GetIndex(), false);

//		if (m_edges[v0_edges->edge.GetIndex()].v[v0_edges->edge.IsBackward()] == v1 && m_edges[v0_edges->edge.GetIndex()].v[!v0_edges->edge.IsBackward()] == v0)
//			return DirectedEdge(v0_edges->edge.GetIndex(), true);

		if (m_edges[v0_edges->edge.GetIndex()].v[0] == v0 && m_edges[v0_edges->edge.GetIndex()].v[1] == v1)
			return DirectedEdge(v0_edges->edge.GetIndex(), false);

		if (m_edges[v0_edges->edge.GetIndex()].v[0] == v1 && m_edges[v0_edges->edge.GetIndex()].v[1] == v0)
			return DirectedEdge(v0_edges->edge.GetIndex(), true);

		v0_edges = v0_edges->next;
	}

	uint k = m_edges.GetSize();
	m_edges.Add(Edge(v0, v1));

	ASSERT(Find(this, m_vertexEdges[v0], v0, v1) == NULL);
	ASSERT(Find(this, m_vertexEdges[v1], v0, v1) == NULL);

	m_vertexEdges[v0] = new EdgeList(DirectedEdge(k, false), m_vertexEdges[v0]);
	m_vertexEdges[v1] = new EdgeList(DirectedEdge(k, true), m_vertexEdges[v1]);

	return DirectedEdge(k, false);
	/*
	unsigned int nedges = m_edges.GetSize();
	Edge* pEdge = m_edges.GetData();

	for (unsigned int k = 0; k < nedges; k++)
	{
		if ((pEdge->v[0] == e0) && (pEdge->v[1] == e1))
		{
			break;
		}

		pEdge++;
	}

	if (k == nedges)
	{
		m_edges.Add(Edge(e0, e1));

		m_vertexEdges[e0] = new EdgeList(k, m_vertexEdges[e0]);
		m_vertexEdges[e1] = new EdgeList(k, m_vertexEdges[e1]);
	}

	return k;
	*/
}

/*
void IndexedFaceSet::BuildEdges()
{
	m_edges.clear();
	m_edges.reserve(64);

	unsigned int npolys = m_pointIndices->m_items.GetSize() / 3;

	for (unsigned int i = 0; i < npolys; i++)
	{
	//	CPolygon* poly = polyArray[i];
		unsigned int npoints = 3;//poly->vindices.GetSize();
		int32* vindex = m_pointIndices->m_items.GetData() + i*3;//->poly->vindices.GetData();

		for (unsigned int j = 1; j < npoints; j++)
		{
			AddEdge(vindex[j-1], vindex[j]);
		}

		AddEdge(vindex[npoints-1], vindex[0]);
	}
}
*/

void IndexedFaceSet::Transform(const LDraw::matrix4f& transformMatrix)
{
	unsigned int count = m_points->m_items.size();
	for (unsigned int i = 0; i < count; i++)
	{
		m_points->m_items[i] = transformMatrix.transform(m_points->m_items[i]);
	}
}

Point3DfCollection* IndexedFaceSet::get_Points()
{
	return m_points;
}

void IndexedFaceSet::set_Points(Point3DfCollection* points)
{
	m_points = points;
}

/*
Int32Collection* IndexedFaceSet::get_PointIndices()
{
	return m_pointIndices;
}

void IndexedFaceSet::set_PointIndices(Int32Collection* pointIndices)
{
	m_pointIndices = pointIndices;
}
*/

/*
Point3DCollection* IndexedFaceSet::get_Normals()
{
	return m_normals;
}

void IndexedFaceSet::set_Normals(Point3DCollection* normals)
{
	m_normals = normals;
}

Int32Collection* IndexedFaceSet::get_NormalIndices()
{
	return m_normalIndices;
}

void IndexedFaceSet::set_NormalIndices(Int32Collection* indices)
{
	m_normalIndices = indices;
}
*/

Point3DfCollection* IndexedFaceSet::get_TexCoords()
{
	return m_texCoords;
}

void IndexedFaceSet::set_TexCoords(Point3DfCollection* texcoords)
{
	m_texCoords = texcoords;
}

UI::Int32Collection* IndexedFaceSet::get_TexCoordIndices()
{
	return m_texCoordIndices;
}

void IndexedFaceSet::set_TexCoordIndices(UI::Int32Collection* indices)
{
	m_texCoordIndices = indices;
}

void IndexedFaceSet::OnRender(Shape* pShape, LDraw::Graphics3D* pG, int mode, Deformer* pDeformer)
{
	ASSERT(0);
#if 0
	//int count = m_pointIndices->m_items.GetSize();

	if (false)	// Using vertex arrays
	{
		/*
		pG->PushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

		pG->EnableClientState(GL_VERTEX_ARRAY);
		pG->EnableClientState(GL_NORMAL_ARRAY);
		pG->EnableClientState(GL_TEXTURE_COORD_ARRAY);

		pG->glVertexPointer(3, GL_FLOAT, 0, m_transformedVertices.GetData());
		pG->glNormalPointer(GL_FLOAT, 0, m_transformedNormals.GetData());
		pG->glTexCoordPointer(3, GL_FLOAT, 0, m_texcoords.GetData());

		pG->glDrawElements(GL_TRIANGLES, m_pointIndices->m_items.GetSize(), GL_UNSIGNED_INT, m_pointIndices->m_items.GetData());

		pG->PopClientAttrib();
		*/
	}
	else
	{
	//	unsigned int nfaces = count / 3;
		unsigned int nfaces = m_faces.GetSize();

		for (unsigned int j = 0; j < nfaces; j++)
		{
			const Face& face = m_faces[j];

			pG->PushAttrib(GL_ENABLE_BIT);

			if (mode != 0)
			{
				if (m_materialFaceIndices.size())
				{
					unsigned int materialIndex = m_materialFaceIndices[j];

					Material* material = pShape->m_materialList[materialIndex];

					pG->Materialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float*)&material->m_diffuseColor);

					if (material->m_textureBitmap)
					{
						if (material->m_texName == 0)
						{
							pG->GenTextures(1, &material->m_texName);

				//							ASSERT(glError == GL_NO_ERROR);

							pG->BindTexture(GL_TEXTURE_2D, material->m_texName);
				//							ASSERT(glGetError() == GL_NO_ERROR);

				#if USE_GL
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (repeatS->m_value)? GL_REPEAT : GL_CLAMP);
							ASSERT(glGetError() == GL_NO_ERROR);

							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (repeatT->m_value)? GL_REPEAT : GL_CLAMP);
							ASSERT(glGetError() == GL_NO_ERROR);

							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							ASSERT(glGetError() == GL_NO_ERROR);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
							ASSERT(glGetError() == GL_NO_ERROR);
				#endif

							pG->TexImage2D(GL_TEXTURE_2D, material->m_textureBitmap);
						}

						if (true)
						{
							pG->BindTexture(GL_TEXTURE_2D, material->m_texName);
							pG->Enable(GL_TEXTURE_2D);
							pG->TexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
						}
					}
				}
			}

			pG->glBegin(GL_POLYGON);

			bool smoothShading = true;

			if (!smoothShading)	// one normal per face
			{
			//	int normalIndex = m_normalIndices->GetItem(j);
				LDraw::vector3f normal = m_transformedNormals[j];
				pG->glNormal(normal);
			}

	//		for (int i = j*3; i < j*3+3; i++)
			for (unsigned int i = 0; i < face.m_edges.GetSize(); i++)
			{
				unsigned int index = m_edges[face.m_edges[i].GetIndex()].v[face.m_edges[i].IsBackward()];

				//int index = m_pointIndices->GetItem(i);
				LDraw::vector3f vec = m_transformedVertices[index];

				if (smoothShading)
				{
					LDraw::vector3f normal = m_transformedVertexNormals[index];
					pG->glNormal(normal);
				}
				/*
				if (m_normals)
				{
					int normalIndex = m_normalIndices->GetItem(i);
					LDraw::vector3f normal = m_transformedNormals[normalIndex];
					pG->glNormal(normal);
				}
				*/


				if (m_texCoords)
				{
					Int32Collection* texCoordIndices = m_texCoordIndices;//? m_texCoordIndices: m_pointIndices;

					int texcoordIndex = texCoordIndices->GetItem(i);
					LDraw::vector3f texcoord = m_texCoords->m_items[texcoordIndex];
					pG->glTexCoordf(texcoord[0], texcoord[1], texcoord[2]);
				}

				pG->glVertex(vec);
			}

			pG->glEnd();

			pG->PopAttrib();
		}
	}

	/*
	if (m_points && m_pointIndices)
	{

		pG->glBegin(GL_TRIANGLES);

		for (int i = 0; i < count; i++)
		{
			long index = m_pointIndices->GetItem(i);
			Point3D* pPoint = m_points->m_items[index];

			LDraw::vector3f vec = pDeformer->Deform(*pPoint);

			pG->glVertex(vec);
		}

		pG->glEnd();
	}
	*/
#endif
}

BezierPatch::BezierPatch()
{
	m_points = NULL;
}

void BezierPatch::set_Points(Point3DfCollection* points)
{
	m_points = points;
}

void BezierPatch::OnRender(Shape* pShape, LDraw::Graphics3D* pG, Deformer* pDeformer)
{
	ASSERT(0);
#if 0
	float ctrlpoints2[4][4][3];
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ctrlpoints2[i][j][0] = m_points->m_items[i*4+j][0];
				ctrlpoints2[i][j][1] = m_points->m_items[i*4+j][1];
				ctrlpoints2[i][j][2] = m_points->m_items[i*4+j][2];
			}
		}
	}

	float texpts[2][2][2] = {
		{{0,0}, {0,1}},
		{{1,0}, {1,1}}
	};

	int i;

	pG->glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4,
											0.0, 1.0, 12, 4, (float*)&ctrlpoints2[0][0][0]);

	pG->glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2,
											0, 1, 4, 2, (float*)&texpts[0][0][0]);

	pG->Enable(GL_MAP2_TEXTURE_COORD_2);
	pG->Enable(GL_MAP2_VERTEX_3);

//	for (int j = 0; j <= 8; j++)
	{
		for (i = 0; i < 5; i++)
		{
			pG->glBegin(GL_QUAD_STRIP);
			for (int j = 0; j <= 4; j++)
			{
				pG->glEvalCoordf((float)j / 4, (float)i/5.0);
				pG->glEvalCoordf((float)j / 4, (float)(i+1)/5.0);
			}
			pG->glEnd();
		}

		/*
		pG->glBegin(GL_LINES);
		for (i = 0; i <= 20; i++)
		{
			pG->glEvalCoordf((float)j / 8, (float)i/20.0);
		}
		pG->glEnd();
		*/
	}
#endif
}

Sphere::Sphere()
{
	m_Radius = 1;
}

Sphere::~Sphere()
{
}

Box::Box()
{
}

Box::~Box()
{
}

Shape::Shape()
{
	m_Geometry = NULL;
//	m_material = NULL;

	m_geometryTransform = LDraw::matrix4f::getIdentity();

//	m_transform = LDraw::Matrix4::GetIdentity();
}

Shape::~Shape()
{
}

Geometry* Shape::get_Geometry()
{
	return m_Geometry;
}

void Shape::set_Geometry(Geometry* geometry)
{
	m_Geometry = geometry;
}

Material::Material()
{
	m_name = NULL;
	m_textureBitmap = NULL;
	m_texName = 0;
}

void Shape::OnRender(LDraw::Graphics3D* pG, int mode, Deformer* pDeformer)
{
//	pG->glPushAttrib(GL_ENABLE_BIT);

	/*
	if (mode != 0)
	{
		if (m_materialList.size())
		{
			Material* m_material = m_materialList[0];

			pG->glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float*)&m_material->m_diffuseColor);

			if (m_material->m_textureBitmap)
			{
				if (m_material->m_texName == 0)
				{
					pG->glGenTextures(1, &m_material->m_texName);

		//							ASSERT(glError == GL_NO_ERROR);

					pG->glBindTexture(GL_TEXTURE_2D, m_material->m_texName);
		//							ASSERT(glGetError() == GL_NO_ERROR);

		#if USE_GL
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (repeatS->m_value)? GL_REPEAT : GL_CLAMP);
					ASSERT(glGetError() == GL_NO_ERROR);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (repeatT->m_value)? GL_REPEAT : GL_CLAMP);
					ASSERT(glGetError() == GL_NO_ERROR);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					ASSERT(glGetError() == GL_NO_ERROR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					ASSERT(glGetError() == GL_NO_ERROR);
		#endif

					pG->glTexImage2D(GL_TEXTURE_2D, m_material->m_textureBitmap);
				}

				if (true)
				{
					pG->glBindTexture(GL_TEXTURE_2D, m_material->m_texName);
					pG->glEnable(GL_TEXTURE_2D);
					pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				}
			}
		}
	}
	*/

	if (m_Geometry)
	{
		m_Geometry->OnRender(this, pG, mode, pDeformer);
	}

	//pG->glPopAttrib();
}

void Sphere::OnRender(Shape* pShape, LDraw::Graphics3D* pGraphics3D, Deformer* pDeformer)
{
	LDraw::gluSphere(pGraphics3D, m_Radius, 30, 30);
}

double Sphere::get_Radius() const
{
	return m_Radius;
}

void Sphere::set_Radius(double radius)
{
	m_Radius = radius;
}

Object3D::Object3D()
{
	m_name = NULL;
	m_bSelected = false;	// TODO, added data
	m_selectedObject = NULL;	// TODO, added data

	m_transform = LDraw::Matrix4::GetIdentity();
}

DependencyObject* Object3D::GetDependencyParent()
{
	return NULL;
}

DependencyObject* Geometry::GetDependencyParent()
{
	return NULL;
}

class TranslateTransform3D : public Transform3D
{
public:
	TranslateTransform3D();

	double m_OffsetX;
	double m_OffsetY;
	double m_OffsetZ;

	double get_OffsetX();
	void put_OffsetX(double X);

	double get_OffsetY();
	void put_OffsetY(double Y);

	double get_OffsetZ();
	void put_OffsetZ(double Z);

	__release<LDraw::Matrix4> get_Value();
};

TranslateTransform3D::TranslateTransform3D()
{
	m_OffsetX = 0;
	m_OffsetY = 0;
	m_OffsetZ = 0;
}

double TranslateTransform3D::get_OffsetX()
{
	return m_OffsetX;
}

void TranslateTransform3D::put_OffsetX(double X)
{
	m_OffsetX = X;
}

double TranslateTransform3D::get_OffsetY()
{
	return m_OffsetY;
}

void TranslateTransform3D::put_OffsetY(double Y)
{
	m_OffsetY = Y;
}

double TranslateTransform3D::get_OffsetZ()
{
	return m_OffsetZ;
}

void TranslateTransform3D::put_OffsetZ(double Z)
{
	m_OffsetZ = Z;
}

__release<LDraw::Matrix4> TranslateTransform3D::get_Value()
{
	return LDraw::Matrix4::GetTranslate(m_OffsetX, m_OffsetY, m_OffsetZ);
}

class RotateTransform3D : public Transform3D
{
public:
	RotateTransform3D();

	double m_OffsetX;
	double m_OffsetY;
	double m_OffsetZ;

	double get_OffsetX();
	void put_OffsetX(double X);

	double get_OffsetY();
	void put_OffsetY(double Y);

	double get_OffsetZ();
	void put_OffsetZ(double Z);

	__release<LDraw::Matrix4> get_Value();
};

RotateTransform3D::RotateTransform3D()
{
	m_OffsetX = 0;
	m_OffsetY = 0;
	m_OffsetZ = 0;
}

double RotateTransform3D::get_OffsetX()
{
	return m_OffsetX;
}

void RotateTransform3D::put_OffsetX(double X)
{
	m_OffsetX = X;
}

double RotateTransform3D::get_OffsetY()
{
	return m_OffsetY;
}

void RotateTransform3D::put_OffsetY(double Y)
{
	m_OffsetY = Y;
}

double RotateTransform3D::get_OffsetZ()
{
	return m_OffsetZ;
}

void RotateTransform3D::put_OffsetZ(double Z)
{
	m_OffsetZ = Z;
}

__release<LDraw::Matrix4> RotateTransform3D::get_Value()
{
	ASSERT(0);
	return NULL;
#if 0

	return
		LDraw::Matrix4::GetRotate(m_OffsetX, 1, 0, 0) *
		LDraw::Matrix4::GetRotate(m_OffsetY, 0, 1, 0) *
		LDraw::Matrix4::GetRotate(m_OffsetZ, 0, 0, 1);
#endif
}

Object3DCollection::Object3DCollection()
{
}

void Object3DCollection::AddChild(Object* child)
{
	Object3D* p = dynamic_cast<Object3D*>(child);
	if (p)
	{
//		p->AddRef();
		m_items.Add(p);
	}
}

void Object3DCollection::AddText(StringW* text)
{
}

Group::Group()
{
//	m_pBone = NULL;
	m_Children = NULL;
//	m_Transform = NULL;
}

Group::~Group()
{
}

Object3DCollection* Group::get_Children()
{
	return m_Children;
}

void Group::set_Children(Object3DCollection* children)
{
	m_Children = children;
}

/*
_Transform3D* Group::get_Transform()
{
	return m_Transform;
}

void Group::put_Transform(_Transform3D* Transform)
{
	m_Transform = Transform;
}
*/

void Group::OnRender(LDraw::Graphics3D* pGraphics, int mode, Deformer* pDeformer)
{
	if (m_Children)
	{
		for (int i = 0; i < m_Children->m_items.GetSize(); i++)
		{
			m_Children->m_items[i]->OnRender(pGraphics, mode, pDeformer);
		}
	}
}

Light::Light()
{
	m_samples = 1;
}

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();

	void OnRender(LDraw::Graphics3D* pGraphics, Deformer* pDeformer);

	float m_ambientIntensity;
	float m_color[3];
	float m_intensity;
	bool m_on;

	LDraw::vector3f m_direction;
};

DirectionalLight::DirectionalLight()
{
	m_ambientIntensity = 0;
	m_color[0] = 1;
	m_color[1] = 0.5;
	m_color[2] = 0;
	m_intensity = 1;
	m_on = true;

	// directional light
	m_direction = LDraw::vector3f(0, 0, 1);

	m_direction = LDraw::vector3f(1, 0, 10);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::OnRender(LDraw::Graphics3D* m_pGraphics3D, Deformer* pDeformer)
{
	ASSERT(0);
#if 0
	if (m_on)
	{
		m_pGraphics3D->PushMatrix();
	//	glTranslated(0, 0, 100);

		float light_position[4];
		m_direction.copyTo(light_position);
		light_position[3] = 0;	// directional

		//light_position[3] = 1;

		float rgba[4] = {m_ambientIntensity, m_ambientIntensity, m_ambientIntensity, 1.0};
		float rgba2[4] = {m_color[0], m_color[1], m_color[2], m_intensity};

		int m_nLight = 1;

		m_pGraphics3D->Enable(GL_LIGHT0+/*pDC->*/m_nLight);
		m_pGraphics3D->Lightfv(GL_LIGHT0+/*pDC->*/m_nLight, GL_POSITION, light_position);
		m_pGraphics3D->Lightfv(GL_LIGHT0+/*pDC->*/m_nLight, GL_AMBIENT, rgba);
		m_pGraphics3D->Lightfv(GL_LIGHT0+/*pDC->*/m_nLight, GL_DIFFUSE, rgba2);
		m_pGraphics3D->Lightfv(GL_LIGHT0+/*pDC->*/m_nLight, GL_SPECULAR , rgba2);

	//	GLfloat light_direction[3];
	//	m_direction.copyTo(light_direction);
	//	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

		/*
		if (true)
		{
			pG->glBegin(GL_LINES);

			pG->glVertexf(light_position[0], light_position[1], light_position[2]);

			pG->glEnd();
		}
		*/

		m_pGraphics3D->PopMatrix();

	//	pDC->m_nLight++;
	}
#endif
}

class Viewport3D : public Control
{
public:
	Viewport3D();

	Camera* get_Camera();
	void put_Camera(Camera* camera);

	Object3D* get_Model();
	void put_Model(Object3D* model);

protected:

	virtual void OnRender(Graphics* pGraphics);

	Camera *m_Camera;
	Object3D *m_Model;
};

Viewport3D::Viewport3D()
{
	m_Camera = NULL;
	m_Model = NULL;
}

Camera* Viewport3D::get_Camera()
{
	return m_Camera;
}

void Viewport3D::put_Camera(Camera* camera)
{
	m_Camera = camera;
}

Object3D* Viewport3D::get_Model()
{
	return m_Model;
}

void Viewport3D::put_Model(Object3D* model)
{
	m_Model = model;
}

void Viewport3D::OnRender(Graphics* pGraphics)
{
#if 0
	LDraw::Graphics3D* m_pGraphics3D = new LDraw::Graphics3D;
	m_pGraphics3D->m_pGraphics = pGraphics;

	LDraw::SizeD actualSize = get_ActualSize();

	double w = actualSize.Width;
	double h = actualSize.Height;

	if (m_Camera)
	{
		m_Camera->Apply(m_pGraphics3D, w, h);

		/*
		m_pGraphics3D->glBegin(GL_TRIANGLES);

		m_pGraphics3D->glVertex(0, 0, 0);
		m_pGraphics3D->glVertex(1, 0, 0);
		m_pGraphics3D->glVertex(1, 1, 0);

		m_pGraphics3D->glEnd();
		*/

		if (m_Model)
		{
			m_Model->OnRender(m_pGraphics3D);
		}
	}
#endif
}

class View3D;

/*
class SelectedGeometry
{
public:
};
*/
void ComputeCombinedTransformChildren(Group* pGroup)
{
	for (int i = 0; i < pGroup->m_Children->m_items.GetSize(); i++)
	{
		Object3D* pObject = pGroup->m_Children->m_items[i];

		if (pObject->m_transform)
			pObject->m_combinedTransform = pGroup->m_combinedTransform * pObject->m_transform->m_matrix;
		else
			pObject->m_combinedTransform = pGroup->m_combinedTransform;

		if (Group* pGroup2 = dynamic_cast<Group*>(pObject))
		{
			ComputeCombinedTransformChildren(pGroup2);
		}
	}
}

void ApplyBone(Bone* pBone, IndexedFaceSet* faceset)
{
	//return;
	LDraw::matrix4f finalMatrix = ((Group*)pBone->m_TransformNode->m_object)->m_combinedTransform * pBone->m_matrixOffset->m_matrix;
//	float fm* = [4][4];
//	finalMatrix.Get((float*)fm);

	LDraw::matrix3f finalMatrix3(	finalMatrix[0][0], finalMatrix[1][0], finalMatrix[2][0],
												finalMatrix[0][1], finalMatrix[1][1], finalMatrix[2][1],
												finalMatrix[0][2], finalMatrix[1][2], finalMatrix[2][2]);

	LDraw::matrix3f finalMatrix3i = finalMatrix3.getInverse();

	for (uint i = 0; i < pBone->m_vertexWeights.GetSize(); i++)
	{
		uint index = pBone->m_vertexWeights[i].m_index;
		float weight = pBone->m_vertexWeights[i].m_weight;

		LDraw::vector3f vec = faceset->get_Points()->m_items[index];
		faceset->m_transformedVertices[index] += finalMatrix.transform(vec) * weight;

		if (true)
		{
			ASSERT(0);
#if 0
			LDraw::vector3f normal = faceset->get_Normals()->m_items[index];
			faceset->m_transformedNormals[index] += (finalMatrix3i * normal) * weight;
#endif
		}
	}
}

void ApplyBones(Group* pGroup)
{
	for (int i = 0; i < pGroup->m_Children->m_items.GetSize(); i++)
	{
		Object3D* pObject = pGroup->m_Children->m_items[i];
		if (Group* pGroup2 = dynamic_cast<Group*>(pObject))
		{

			ApplyBones(pGroup2);
		}
		else if (Shape* pShape = dynamic_cast<Shape*>(pObject))
		{
			IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(pShape->get_Geometry());
			if (faceset)
			{
				Point3DfCollection* points = faceset->get_Points();

				int npoints = points->m_items.GetSize();
				faceset->m_transformedVertices.SetSize(npoints);

				Point3DfCollection* texCoords = faceset->get_TexCoords();
				if (texCoords)
				{
					int count = texCoords->m_items.GetSize();
					faceset->m_texcoords.SetSize(count);

					for (int j = 0; j < count; j++)
					{
						faceset->m_texcoords[j] = texCoords->m_items[j];
					}
				}

				if (faceset->m_Bones.GetSize() == 0)
				{
					/*
					{
						for (int j = 0; j < npoints; j++)
						{
							faceset->m_transformedVertices[j] = points->m_items[j];
						}
					}
					*/
					faceset->m_transformedVertices = points->m_items;

					faceset->m_transformedNormals = faceset->m_faceNormals;
					faceset->m_transformedVertexNormals = faceset->m_vertexNormals;
					/*
					if (faceset->get_Normals())
					{
						int nnormals = faceset->get_Normals()->m_items.GetSize();
						faceset->m_transformedNormals.SetSize(nnormals);

						for (int j = 0; j < nnormals; j++)
						{
							faceset->m_transformedNormals[j] = faceset->get_Normals()->m_items[j];
						}
					}
					*/
				}
				else
				{
					{
						for (int j = 0; j < npoints; j++)
						{
							faceset->m_transformedVertices[j] = LDraw::vector3f(0,0,0);
						}
					}

					ASSERT(0);
#if 0
					if (faceset->get_Normals())
					{
						int nnormals = faceset->get_Normals()->m_items.GetSize();
						faceset->m_transformedNormals.SetSize(nnormals);

						for (int j = 0; j < nnormals; j++)
						{
							faceset->m_transformedNormals[j] = LDraw::vector3f(0,0,0);
						//	faceset->m_transformedNormals[j] = *faceset->get_Normals()->m_items[j];
						//	faceset->m_transformedNormals[j] = faceset->m_transformedNormals[j];
						}
					}
#endif

					for (int i = 0; i < faceset->m_Bones.GetSize(); i++)
					{
						ApplyBone(faceset->m_Bones[i], faceset);
					}
				}
			}
		}
	}
}


ObjectMode Document3D::get_Mode()
{
	return m_objectMode;
}

void Document3D::put_Mode(ObjectMode mode)
{
	m_objectMode = mode;
}

void View3D::BeginMove()
{
	if (m_Camera)
	{
		if (m_Camera->m_transform)
			m_startTransform = m_Camera->m_transform->m_matrix;
		else
			m_startTransform = LDraw::matrix4f::getIdentity();

	}
#if 0
	m_initialPosition = m_position;
	m_initialOrientation = m_orientation;
#endif
}

void View3D::Move(long m_dragging, LDraw::PointI offset)
{
	if (m_dragging == 1)	// change XY position
	{
		if (m_Camera)
		{
			double moveX = (double)offset.X/20;
			double moveY = (double)-offset.Y/20;

			LDraw::matrix4f mat;
			mat = LDraw::matrix4f::getTranslate(moveX, moveY, 0);
			m_Camera->m_transform = new LDraw::Matrix4(m_startTransform * mat);

			m_document->UpdateScene();
			m_document->Invalidate();
		}

#if 0
	//	CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
	//	CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

		if (true)
		{
			double moveX = (double)offset.X/20;
			double moveY = (double)-offset.Y/20;

			LDraw::matrix4f repos = LDraw::matrix4f::getIdentity();

			repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), m_orientation.m_axis);//.getInverse();
			repos *= LDraw::matrix4f::getTranslate(moveX, moveY, 0);
			repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), -m_orientation.m_axis);
		//	repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), m_orientation.m_axis);

			m_position = repos.transform(m_initialPosition);

			/*
			double moveY = 0;//(double)-offset.Y/20;
			double moveX = (double)offset.Y/40;

			m_position[2] += moveX;
			//m_position[1] += moveY;
			*/
		}
		else
		{
			double moveX = (double)offset.X/20;
			double moveY = (double)-offset.Y/20;

			LDraw::matrix4f repos = LDraw::matrix4f::getIdentity();

			repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), -m_orientation.m_axis);
			repos *= LDraw::matrix4f::getTranslate(moveX, moveY, 0);
			repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), -m_orientation.m_axis).getInverse();
		//	repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), m_orientation.m_axis);

			m_position = repos.transform(m_initialPosition);
		}

		Invalidate();
#endif
	}
	else if (m_dragging == 2) // change XZ position
	{
		if (m_Camera)
		{
			double moveX = (double)offset.X/20;
			double moveZ = (double)offset.Y/20;

			LDraw::matrix4f mat;
			mat = LDraw::matrix4f::getTranslate(moveX, 0, moveZ);
//			m_Camera->m_transform->m_matrix = m_startTransform * mat;
			m_Camera->m_transform = new LDraw::Matrix4(m_startTransform * mat);

			m_document->UpdateScene();
			m_document->Invalidate();
		}
#if 0
	//	CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
	//	CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

		double moveX = (double)offset.X/20;
		double moveZ = (double)offset.Y/20;

		LDraw::matrix4f repos = LDraw::matrix4f::getIdentity();

		repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), m_orientation.m_axis);//.getInverse();
		repos *= LDraw::matrix4f::getTranslate(moveX, 0, moveZ);
		repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), -m_orientation.m_axis);
	//	repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), m_orientation.m_axis);

		m_position = repos.transform(m_initialPosition);

		Invalidate();
#endif
	}
	else if (m_dragging == 3)
	{

		double r = 600;	// 360
		double rotateY = (double)offset.X*360/r;
		double rotateX = (double)offset.Y*360/r;

		if (m_Camera)
		{
			LDraw::matrix4f start = m_startTransform;

			LDraw::vector3f centerOfRotation(0,0,0);

			LDraw::matrix4f mat;

			mat = start.getInverse();
			mat *= LDraw::matrix4f::getRotate(rotateX, LDraw::vector3f(1,0,0));
			mat *= LDraw::matrix4f::getRotate(rotateY, LDraw::vector3f(0,1,0));
			mat *= start;
		//	mat *= LDraw::matrix4f::getRotate(-rotateX, LDraw::vector3f(1,0,0));
		//	mat *= LDraw::matrix4f::getRotate(-rotateY, LDraw::vector3f(0,1,0));

			/*
			mat *= LDraw::matrix4f::getTranslate(-centerOfRotation[0], -centerOfRotation[1], -centerOfRotation[2]);
			mat *= LDraw::matrix4f::getRotate(rotateX, LDraw::vector3f(1,0,0));
		//	mat *= LDraw::matrix4f::getRotate(rotateY, LDraw::vector3f(0,1,0));
			mat *= LDraw::matrix4f::getTranslate(centerOfRotation[0], centerOfRotation[1], centerOfRotation[2]);
			*/

//			m_Camera->m_transform->m_matrix = m_startTransform * mat;
			m_Camera->m_transform = new LDraw::Matrix4(m_startTransform * mat);

			m_document->UpdateScene();
			m_document->Invalidate();
		}

#if 0
		double r = 600;	// 360

		double rotateY = (double)offset.X*360/r;
		double rotateX = (double)offset.Y*360/r;

	//	CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
	//	CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

		// Orientation
		if (rotateY != 0 || rotateX != 0)
		{
			/*
			float x = m_initialOrientation.m_v[0];
			float y = m_initialOrientation.m_v[1];
			float z = m_initialOrientation.m_v[2];
			float angle = m_initialOrientation.m_a;
			*/

			Quat4d q = m_initialOrientation.AxisAngleToQuaternion(/*x, y, z, angle*/);

			q.CombineQuaternion(/*x, y, z, angle,*/ 0, gmRadians(rotateY), gmRadians(rotateX));

			m_orientation = q.QuaternionToAxisAngle();//Quat4d(x, y, z, angle));

			/*
			orientation->m_value.m_v[0] = x;
			orientation->m_value.m_v[1] = y;
			orientation->m_value.m_v[2] = z;
			orientation->m_value.m_a = angle;
			*/

			m_orientation.m_axis.normalize();
		}

		/*
		// Position
		{
			// Rotate position around centerOfRotation
			matrix4f repos = matrix4f::identity();

			repos *= matrix4f::rotate(gmDegrees(m_orientation.m_a), -m_orientation.m_v);
			repos *= matrix4f::rotate(rotateY, gmVector3(0,1,0));
			repos *= matrix4f::rotate(gmDegrees(m_orientation.m_a), -m_orientation.m_v).inverse();

			m_position = repos.transform(m_initialPosition);
		}
		*/

		// Position
		{
			// Rotate position around centerOfRotation
			LDraw::matrix4f repos = LDraw::matrix4f::getIdentity();

			repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), -m_orientation.m_axis);
			repos *= LDraw::matrix4f::getRotate(rotateX, LDraw::vector3f(1,0,0));
			repos *= LDraw::matrix4f::getRotate(rotateY, LDraw::vector3f(0,1,0));
			repos *= LDraw::matrix4f::getRotate(gmDegrees(m_orientation.m_angle), -m_orientation.m_axis).getInverse();

			//ASSERT(repos.inverse() * repos == matrix4f::identity());

			m_position = repos.transform(m_initialPosition);
		}

		Invalidate();
#endif
	}
}

Display2::Display2(UI::Media3D::Group* visual)
{
	m_item = NULL;
	m_document = NULL;
	root = visual;

	m_tree = new UI::TreeControl;

	m_tree->AddColumn(new UI::TextString(WSTR("Element")));
//		m_tree->AddColumn(new UI::TextString(WSTR("Last Event")));

	BuildChildren(m_tree, root, m_tree);

	set_VisualTree(m_tree);
}

void Display2::BuildChildren(UI::TreeControl* tree, UI::Media3D::Group* visual, ITreeParent* parent)
{
	UI::TreeItemChildren* children = NULL;

	/*
	UI::IVisualChild* child = visual->get_VisualTree();
	if (child)
	{
		children = new UI::TreeItemChildren(tree);

		UI::TreeItem* item = new UI::TreeItem(tree);
		Item* item2 = new Item;
		item2->m_treeItem = item;
		item->m_userdata = item2;
		item2->m_Visual = dynamic_cast<UIElement*>(child);

		item->AppendColumnCell(new UI::TextString(WSTR("VisualTree")));
		item->AppendColumnCell(item2->m_eventCtl);

		BuildChildren(tree, dynamic_cast<UIElement*>(child), item);

		children->AppendItem(item);
	}
	else
	*/
	if (visual->m_Children)
	{
		for (int i = 0; i < visual->m_Children->m_items.GetSize(); i++)
		{
			if (children == NULL)
				children = new UI::TreeItemChildren(tree);

			UI::Media3D::Object3D* child = visual->m_Children->m_items[i];

			UI::TreeItem* item = new UI::TreeItem(tree);
			Item* item2 = new Item;
			item2->m_treeItem = item;
			item->m_userdata = item2;
			item2->m_Visual = child;

		//	EventTargetImpl* target = dynamic_cast<EventTargetImpl*>(child);
		//	target->addEventListener(sysstring(), item2, false);

			StringA* classname = child->GetType()->m_qname;
			/*
			{
				void* vtable = *(void**)child;
				rti* p3 = ((rti**)vtable)[-1];

				int count = p3->m_classHierarchyDescriptor->count;
				BaseClassDescriptor** table = p3->m_classHierarchyDescriptor->m_baseClassArray;

				type_info* ti = (type_info*)table[0]->typedesc;
				classname = ti->name() + strlen("class ");
			}
			*/

			item->AppendColumnCell(new UI::TextString(classname->ToStringW()));
		//	item->AppendColumnCell(item2->m_eventCtl);

			UI::Media3D::Group* pChildGroup = dynamic_cast<UI::Media3D::Group*>(child);
			if (pChildGroup)
				BuildChildren(tree, pChildGroup, item);

			children->AppendItem(item);
		}
	}

	if (children)
		parent->set_Children(children);
}

LDraw::SizeD Display2::OnMeasure(LDraw::SizeD availSize)
{
	return Control::MeasureOverride(availSize);
}

#if 0
void Display2::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"command")
		{
			CommandInvokeEvent* cmdEvt = static_cast<CommandInvokeEvent*>(evt);

			long param = cmdEvt->get_Command();

			ClassType* pDerived = (ClassType*)param;

			void* p = newobj(pDerived);
			ObjectAction* pCmd = (ObjectAction*)DynamicCast(p, pDerived, typeid(ObjectAction).GetType()->GetClass());

			pCmd->Do(m_item->m_Visual);
#if 0
			if (true)
			{
				UI::TreeControl* m_tree = new UI::TreeControl;

				m_tree->AddColumn(new UI::TextString(WSTR("Name")));
				m_tree->AddColumn(new UI::TextString(WSTR("Value")));

				Properties* properties = new Properties;
				properties->CreateRows(m_item->m_Visual, m_tree/*, m_tree*/);
				properties->ExpandRows(m_tree/*, m_tree*/);

				m_tree->put_Children(properties);

				m_propertyPalette->put_Content(m_tree);
			}
#endif
		}
		else if (*evt->get_type() == L"ActivateItem")	// 
		{
			evt->stopPropagation();
			
			UI::TreeItem* item = dynamic_cast<UI::TreeItem*>(evt->get_target());

			m_item = dynamic_cast<Item*>(item->m_userdata);

			if (true)
			{
				PropertiesWindow* properties = new PropertiesWindow(m_item->m_Visual);
				m_propertyPalette->set_Content(properties);

				for (int i = 0; i < m_document->m_selectedObjects.GetSize(); i++)
				{
					m_document->m_selectedObjects[i]->m_object->m_bSelected = false;
				}
				m_document->m_selectedObjects.RemoveAll();

				SelectedObject* pSelectedObject = new SelectedObject;
				pSelectedObject->m_object = m_item->m_Visual;
				pSelectedObject->m_object->m_bSelected = true;
				pSelectedObject->m_object->m_selectedObject = pSelectedObject;

				m_document->m_selectedObjects.Add(pSelectedObject);

				m_document->Invalidate();


#if 0
				UI::TreeControl* m_tree = new UI::TreeControl;

				m_tree->AddColumn(new UI::TextString(WSTR("Name")));
				m_tree->AddColumn(new UI::TextString(WSTR("Value")));

				Properties* properties = new Properties;
				properties->CreateRows(m_item->m_Visual, m_tree/*, m_tree*/);
				properties->ExpandRows(m_tree/*, m_tree*/);

				m_tree->put_Children(properties);

				m_propertyPalette->put_Content(m_tree);
#endif
			}
		}
		else if (*evt->get_type() == L"contextmenu")	// ItemStateChanging
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			UI::TreeItem* item;
			UI::UIElement* target = dynamic_cast<UI::UIElement*>(evt->get_target());
			while (target)
			{
				item = dynamic_cast<UI::TreeItem*>(target);
				if (item) break;

				target = dynamic_cast<UI::UIElement*>(target->GetRParent());
			}

			m_item = dynamic_cast<Item*>(item->m_userdata);

			CLXUIMenuElement* menu = new CLXUIMenuElement();
			menu->SetRParent(this);
			menu->SetOwnerWindow(GetOwnerWindow());

			ClassType* pType = typeid(UI::ObjectAction).GetType()->GetClass();//pD->LookupNamedType(ASTR("UI::ObjectAction"))->GetClass();

			vector<ClassType*> list;
			GetDerived(pType, list);

			for (int i = 0; i < list.GetSize(); i++)
			{
				ClassType* pDerived = list[i];
				if (pDerived->m_derived.GetSize() == 0)
				{
					menu->AddItem(new TextString(pDerived->get_Name()->ToStringW()), (long)pDerived);
				}
			}
			/*
			{
				menu->AddItem(new TextString(WSTR("Undo")), 100);
				menu->AddItem(new TextString(WSTR("Redo")), 101);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Cut")), 102);
				menu->AddItem(new TextString(WSTR("Copy")), 103);
				menu->AddItem(new TextString(WSTR("Paste")), 104);
				menu->AddItem(new TextString(WSTR("Delete")), 105);
				menu->AddItem(new TextString(WSTR("Trim")), 106);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("View All")), 114);
				menu->AddItem(new TextString(WSTR("View Selection")), 115);
				menu->AddItem(new TextString(WSTR("Zoom In")), 116);
				menu->AddItem(new TextString(WSTR("Zoom Out")), 117);
				menu->AddItem(new TextString(WSTR("1:1")), 118);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Mute")), 120);
				menu->AddItem(new TextString(WSTR("Insert Silence")), 121);
				menu->AddItem(new TextString(WSTR("Reverse")), 122);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Play / Stop")), 130);
				menu->AddItem(new TextString(WSTR("Controls")), 131);
			}
			*/

			/*
			menu->AddSeparator();
			menu->AddItem(new TextString(WSTR("Insert/Remove Breakpoint")), ID_DEBUG_TOGGLEBREAKPOINT);
			*/

			menu->GetMenuPopup()->Popup(menu, LDraw::PointI(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));
		}
	}
}
#endif

// This differs from glOrtho2D in that it completely discards the z value
void OrthoReally2D(LDraw::Graphics3D* pG, double left, double right, double bottom, double top)
{
	double tx = - (right + left) / (right - left);
	double ty = - (top + bottom) / (top - bottom);
	double tz = 0;//- (zFar + zNear) / (zFar - zNear);

#define M(row,col) m[col*4+row]

	float m[16];

	M(0,0) = 2 / (right-left); M(0,1) = 0;						M(0,2) = 0;									M(0,3) =	tx;
	M(1,0) = 0;						M(1,1) = 2 / (top-bottom);	M(1,2) =  0;								M(1,3) =	ty;
	M(2,0) = 0;						M(2,1) = 0;						M(2,2) = 0/*-2 / (zFar - zNear)*/;	M(2,3) = tz,
	M(3,0) = 0;						M(3,1) = 0;						M(3,2) = 0;									M(3,3) = 1;

#undef M

#if 0
	float m[16] = {	2 / (right-left), 0,						0,							tx,
						0,						2 / (top-bottom), 0,							ty,
						0,						0,						0/*-2 / (zFar - zNear)*/, tz,
						0,						0,						0,							1};
#endif
	pG->MultMatrixf(m);


}

__release<LDraw::Matrix4> GetOrthoReally2D(double left, double right, double bottom, double top)
{
	double tx = - (right + left) / (right - left);
	double ty = - (top + bottom) / (top - bottom);
	double tz = 0;//- (zFar + zNear) / (zFar - zNear);

#define M(row,col) m[col*4+row]

	float m[16];

	M(0,0) = 2 / (right-left); M(0,1) = 0;						M(0,2) = 0;									M(0,3) =	tx;
	M(1,0) = 0;						M(1,1) = 2 / (top-bottom);	M(1,2) =  0;								M(1,3) =	ty;
	M(2,0) = 0;						M(2,1) = 0;						M(2,2) = 0/*-2 / (zFar - zNear)*/;	M(2,3) = tz,
	M(3,0) = 0;						M(3,1) = 0;						M(3,2) = 0;									M(3,3) = 1;

#undef M

	return new LDraw::Matrix4(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);

#if 0
	float mat[16] = {	2 / (right-left), 0,						0,							tx,
						0,						2 / (top-bottom), 0,							ty,
						0,						0,						0/*-2 / (zFar - zNear)*/, tz,
						0,						0,						0,							1};

	return new LDraw::Matrix4(mat);
#endif
}

__release<LDraw::Matrix4> GetPerspective(double fovy, double aspect, double zNear, double zFar)
{
	// fovy is the angle in the yz plane

	double top = zNear * tan( fovy * M_PI / 360.0 );
	double bottom = -top;

	double left = bottom * aspect;
	double right = top * aspect;

	return LDraw::Matrix4::GetFrustum(left, right, bottom, top, zNear, zFar);
}

class View3DTool : public System::Object
{
public:

	virtual void mousedown(View3D* view, LDraw::vector3f mousepos)
	{
	}

	virtual void mouseup(View3D* view)
	{
	}

	virtual void mousemove(View3D* view, LDraw::vector3f mousepos)
	{
	}
};

TimelineView::TimelineView()
{
	m_document = NULL;

	ScrollBar* p = new ScrollBar(Orientation_Horizontal);
	ASSERT(0);
#if 0
	p->SetInfo(0, 10, 1);
#endif

	set_VisualTree(p);
}

#if 0
void TimelineView::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"scroll")
		{
			SliderEvent* posEvt = (SliderEvent*)evt;
			m_document->SetCurrentTime(posEvt->m_pos);
		}
	}
}
#endif

X3DViewer2::X3DViewer2()
{
	m_Content = NULL;
//	m_document = NULL;
	m_button[0] = NULL;
	m_button[1] = NULL;
	m_button[2] = NULL;
}

void X3DViewer2::set_Content(View3D* Content)
{
	m_Content = Content;
	/*
	CLVRMLLoader* pLoader = new CLVRMLLoader;

	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/RedSphereBlueBox.wrl"));
	*/
//	pScene = pLoader->Load(WSTR("C:/Files/VRML/z_wing.wrl"));

//	CLXUIBorder* pBorder = new CLXUIBorder;
//	pBorder->put_BorderThickness(new CLXUIThickness(new Length(3, Length::UnitAbsolute), new Length(3, Length::UnitAbsolute), new Length(3, Length::UnitAbsolute), new Length(3, Length::UnitAbsolute)));

	Border* pBorder = new Border(new Thickness(1));
	{
		DockPanel* pPanel = new DockPanel;
		{
			m_button[0] = new DeltaMoveButton;
			m_button[0]->set_VisualTree(new TextString(WSTR("Examine")));
			pPanel->AddChild(m_button[0]);
		}
		{
			m_button[1] = new DeltaMoveButton;
			m_button[1]->set_VisualTree(new TextString(WSTR("Slide")));
			pPanel->AddChild(m_button[1]);
		}
		{
			m_button[2] = new DeltaMoveButton;
			m_button[2]->set_VisualTree(new TextString(WSTR("Walk")));
			pPanel->AddChild(m_button[2]);
		}

		{
			DockPanel::SetDock(m_Content, DockPanel::Fill);
			pPanel->AddChild(m_Content);
		}

		pBorder->set_Child(pPanel);
	}

	set_VisualTree(pBorder);
}

#if 0
void X3DViewer2::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			evt->stopPropagation();

			m_xoffset = 0;
			m_yoffset = 0;
			m_scale = m_Content->m_orthoScale;

			//LDraw::SizeD actualSize = m_Content->get_ActualSize();
			m_width = 1 / m_Content->m_orthoScale;

			m_Content->BeginMove();
		}
		else if (*type == L"deltaChange")
		{
			evt->stopPropagation();

			DeltaChangeEvent* deltaEvt = dynamic_cast<DeltaChangeEvent*>(evt);

			m_xoffset += deltaEvt->deltaX;
			m_yoffset += deltaEvt->deltaY;

			if (evt->get_target() == m_button[0])
			{
				m_Content->Move(3/*m_dragging*/, LDraw::PointI(m_xoffset, m_yoffset));
			}
			else if (evt->get_target() == m_button[1])	// slide (Move)
			{
				if (m_Content->m_display == 4)
				{
					m_Content->Move(1/*m_dragging*/, LDraw::PointI(m_xoffset, m_yoffset));
				}
				else
				{
					m_Content->m_orthoOffsetX -= deltaEvt->deltaX / m_Content->m_orthoScale;
					m_Content->m_orthoOffsetY += deltaEvt->deltaY / m_Content->m_orthoScale;

					m_Content->InvalidateRender();
				}
			}
			else if (evt->get_target() == m_button[2])	// Walk (Zoom)
			{
				if (m_Content->m_display == 4)
				{
					m_Content->Move(2/*m_dragging*/, LDraw::PointI(m_xoffset, m_yoffset));
				}
				else
				{
					m_width -= (deltaEvt->deltaX / 200.0) / m_Content->m_orthoScale;

					if (m_width < 1.0/2000) m_width = 1.0/2000;
					else if (m_width > 2000) m_width = 2000;

					m_Content->m_orthoScale = 1 / m_width;

					m_Content->InvalidateRender();
				}
			}
		}
	}
}
#endif

#if 0
void Document3D::MakeList()
{
	if (m_list)
	{
		m_list->Release();
	}

	m_list = new LDraw::DisplayList;
	m_list->AddRef();
	LDraw::Graphics3DList* pG = new LDraw::Graphics3DList(m_glState, m_list);

	if (false)
	{
	pG->glBegin(GL_LINES);

		for (int z = -15; z < -5; z++)
		{
			pG->glVertexf(-5*5, 0, z*5);
			pG->glVertexf(5*5, 0, z*5);
		}

		for (int x = -5; x < 5; x++)
		{
			pG->glVertexf(x*5, 0, -5*5);
			pG->glVertexf(x*5, 0, -15*5);
		}

	pG->glEnd();
	}

#if 0
	if (false)
	{
		pG->glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, (float*)&ctrlpoints[0][0]);
		pG->glEnable(GL_MAP1_VERTEX_3);

		{
			pG->glBegin(GL_LINE_STRIP);

			for (int i = 0; i <= 20; i++)
			{
				pG->glEvalCoordf((float)i / 20);
			}

			pG->glEnd();
		}
	}
#endif

	m_object->OnRender(pG);

#if 0
	if (true)
	{
		uint program = pG->m_state->CreateProgram();

		LDraw::Program* pProgram = pG->m_state->GetProgram(program);

		pProgram->m_fragment = myshader;

		pG->UseProgram(program);
	}

	if (true)
	{
		{
			unsigned int m_texName;
			pG->glGenTextures(1, &m_texName);

//							ASSERT(glError == GL_NO_ERROR);

			pG->glBindTexture(GL_TEXTURE_2D, m_texName);
//							ASSERT(glGetError() == GL_NO_ERROR);

#if USE_GL
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (repeatS->m_value)? GL_REPEAT : GL_CLAMP);
			ASSERT(glGetError() == GL_NO_ERROR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (repeatT->m_value)? GL_REPEAT : GL_CLAMP);
			ASSERT(glGetError() == GL_NO_ERROR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			ASSERT(glGetError() == GL_NO_ERROR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			ASSERT(glGetError() == GL_NO_ERROR);
#endif
			pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);

			pG->glTexImage2D(GL_TEXTURE_2D, &m_bitmap);

			pG->glEnable(GL_TEXTURE_2D);

		}

		int i;

		pG->glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4,
												0.0, 1.0, 12, 4, (float*)&ctrlpoints2[0][0][0]);

		pG->glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2,
												0, 1, 4, 2, (float*)&texpts[0][0][0]);

		pG->glEnable(GL_MAP2_TEXTURE_COORD_2);
		pG->glEnable(GL_MAP2_VERTEX_3);

	//	for (int j = 0; j <= 8; j++)
		{
			for (i = 0; i < 5; i++)
			{
				pG->glBegin(GL_QUAD_STRIP);
				for (int j = 0; j <= 4; j++)
				{
					pG->glEvalCoordf((float)j / 4, (float)i/5.0);
					pG->glEvalCoordf((float)j / 4, (float)(i+1)/5.0);
				}
				pG->glEnd();
			}

			/*
			pG->glBegin(GL_LINES);
			for (i = 0; i <= 20; i++)
			{
				pG->glEvalCoordf((float)j / 8, (float)i/20.0);
			}
			pG->glEnd();
			*/
		}

#if 0
		for (int j = 0; j <= 12; j++)
		{
		//	pG->glBegin(GL_LINE_STRIP);
			pG->glBegin(GL_LINES);
			for (i = 0; i <= 12; i++)
			{
				pG->glEvalCoordf((float)i / 12, (float)j/12.0);
			}
			pG->glEnd();

			/*
			pG->glBegin(GL_LINE_STRIP);
			for (i = 0; i <= 20; i++)
			{
				pG->glEvalCoordf((float)j / 8, (float)i/20.0);
			}
			pG->glEnd();
			*/
		}
#endif
	}
#endif

	pG->m_p << uint16(0);
	pG->Release();
}
#endif

void Document3D::Invalidate()
{
//	MakeList();

	if (m_views[0])
	{
		m_views[0]->InvalidateRender();
		m_views[1]->InvalidateRender();
		m_views[2]->InvalidateRender();
	}

	if (m_views[3])
	{
		m_views[3]->InvalidateRender();
	}
}

class DeleteObject : public ObjectAction
{
public:
	DeleteObject();

	typedef UI::Media3D::Object3D* TargetType;

	void Do(void* p);
};

DeleteObject::DeleteObject()
{
}

void DeleteObject::Do(void* p)
{
}

class Subdivide : public ObjectAction
{
public:
	Subdivide();

	typedef UI::Media3D::Object3D* TargetType;

	void Do(void* p);

	void Do(UI::Media3D::IndexedFaceSet* faceset);
};

Subdivide::Subdivide()
{
}

void Subdivide::Do(UI::Media3D::IndexedFaceSet* faceset)
{
	Int32Collection* pNewIndices = new Int32Collection;
	UI::Media3D::Point3DCollection* pNewPoints = new UI::Media3D::Point3DCollection;

	int n = 0;

#if 0
	for (int i = 0; i < faceset->m_pointIndices->m_items.GetSize(); i += 3)
	{
		int a = faceset->m_pointIndices->m_items[i];
		int b = faceset->m_pointIndices->m_items[i+1];
		int c = faceset->m_pointIndices->m_items[i+2];

		LDraw::vector3f v0 = faceset->m_points->m_items[a];
		LDraw::vector3f v2 = faceset->m_points->m_items[b];
		LDraw::vector3f v4 = faceset->m_points->m_items[c];

		LDraw::vector3f v1 = v0 + (v2 - v0) / 2;
		LDraw::vector3f v3 = v2 + (v4 - v2) / 2;
		LDraw::vector3f v5 = v4 + (v0 - v4) / 2;

		/*
		UI::Media3D::Point3D* p0 = new UI::Media3D::Point3D(v0);
		UI::Media3D::Point3D* p1 = new UI::Media3D::Point3D(v1);
		UI::Media3D::Point3D* p2 = new UI::Media3D::Point3D(v2);
		UI::Media3D::Point3D* p3 = new UI::Media3D::Point3D(v3);
		UI::Media3D::Point3D* p4 = new UI::Media3D::Point3D(v4);
		UI::Media3D::Point3D* p5 = new UI::Media3D::Point3D(v5);
		*/

		pNewPoints->m_items.Add(v0);
		pNewPoints->m_items.Add(v1);
		pNewPoints->m_items.Add(v2);
		pNewPoints->m_items.Add(v3);
		pNewPoints->m_items.Add(v4);
		pNewPoints->m_items.Add(v5);

		pNewIndices->m_items.Add(n);
		pNewIndices->m_items.Add(n+1);
		pNewIndices->m_items.Add(n+5);

		pNewIndices->m_items.Add(n+1);
		pNewIndices->m_items.Add(n+2);
		pNewIndices->m_items.Add(n+3);

		pNewIndices->m_items.Add(n+3);
		pNewIndices->m_items.Add(n+4);
		pNewIndices->m_items.Add(n+5);

		pNewIndices->m_items.Add(n+1);
		pNewIndices->m_items.Add(n+3);
		pNewIndices->m_items.Add(n+5);

		n += 12;
	}

	faceset->set_Points(pNewPoints);
#endif
	ASSERT(0);
//	faceset->set_PointIndices(pNewIndices);
}

void Subdivide::Do(void* p)
{
	UI::Media3D::Object3D* p2 = (UI::Media3D::Object3D*)p;
	UI::Media3D::Shape* shape = dynamic_cast<UI::Media3D::Shape*>(p2);

	UI::Media3D::IndexedFaceSet* faceset = dynamic_cast<UI::Media3D::IndexedFaceSet*>(shape->get_Geometry());

	if (faceset)
	{
		Do(faceset);
	}
}

unsigned int Light::get_Samples()
{
	return m_samples;
}

void Light::set_Samples(unsigned int samples)
{
	m_samples = samples;
}

}	// Media3D
}	// UI

namespace UI
{
DeltaMoveButton::DeltaMoveButton()
{
	m_dragging = 0;
}

#if 0
void DeltaMoveButton::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			MouseEvent* mouseevt = dynamic_cast<MouseEvent*>(evt);
			CaptureMouse();

			m_oldpt.X = mouseevt->get_ScreenX();
			m_oldpt.Y = mouseevt->get_ScreenY();

			m_dragging = 1;
#if 0//WIN32
			ShowCursor(false);
#endif
		}
		else if (*type == L"mouseup")
		{
			ReleaseMouseCapture();
			m_dragging = 0;
#if 0//WIN32
			ShowCursor(true);
#endif
		}
		else if (*type == L"mousemove")
		{
			MouseEvent* mouseevt = dynamic_cast<MouseEvent*>(evt);
			if (m_dragging)
			{
				SetCursorPos(m_oldpt.X, m_oldpt.Y);

				LDraw::PointI pt;
				pt.X = mouseevt->get_ScreenX();
				pt.Y = mouseevt->get_ScreenY();

			//	printf("current mouse pos(%d, %d)\n", pt.X, pt.Y);

				DeltaChangeEvent* deltaEvt = new DeltaChangeEvent;
				deltaEvt->InitEvent(WSTR("deltaChange"), true, true);
				deltaEvt->deltaX = pt.X - m_oldpt.X;
				deltaEvt->deltaY = pt.Y - m_oldpt.Y;

				//m_oldpt = pt;

				dispatchEvent(deltaEvt);
			}
		}
	}
}
#endif

}	// UI
}	// System
