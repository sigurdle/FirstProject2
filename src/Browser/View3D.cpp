#include "stdafx.h"
#include "Browser.h"
#include "View3D.h"

#include <stdlib.h>	// rand
#include "../include/windows_header.h"

//#include <gl/gl.h>
//#include <gl/glu.h>

//#include "c:/opengl/glsdk/gl/glprocs.h"

#if 0
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#endif

namespace System
{

float PerlinNoise_2D(float x, float y);
float PerlinNoise_3D(float x, float y, float z);

Thread::Thread()
{
	m_hThread = NULL;
	m_threadId = 0;
}

Thread::~Thread()
{
}

void Thread::Wait()
{
	MSWindows::WaitForSingleObject(m_hThread, INFINITE);
	MSWindows::CloseHandle(m_hThread);
	m_hThread = NULL;
}

namespace LDraw
{
extern DrawExt transform_point_t transform_point_unaligned;

LDraw::matrix4f GetOrthoReally2D(double left, double right, double bottom, double top)
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

	return matrix4f(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);

#undef M
}

void Cube(LDraw::Graphics3D* pG, float width, float height, float depth, float dx, float dy, float dz)
{
	ASSERT(0);
#if 0
	int segments = 1;
	for (int i = 0; i < 1; i++)
	{
		pG->glBegin(GL_QUAD_STRIP);

		float y = (i/1.0) * height + dy;
		float sy = height / 1;

		pG->glNormalf(0, 0, 1);

		for (int j = 0; j <= segments; j++)
		{
			float x = ((float)j/segments) * width + dx;
			pG->glVertexf(-width/2 + x, -height/2 + y+sy, depth/2);
			pG->glVertexf(-width/2 + x, -height/2 + y, depth/2);
		}
	
		pG->glNormalf(1, 0, 0);
		for (int j = segments; j >= 0; j--)
		{
			float z = ((float)j/segments) * depth + dz;
			pG->glVertexf(width/2, -height/2 + y+sy, -depth/2 + z);
			pG->glVertexf(width/2, -height/2 + y, -depth/2 + z);
		}

		pG->glNormalf(0, 0, -1);
		for (int j = segments; j >= 0; j--)
		{
			float x = ((float)j/segments) * width + dx;
			pG->glVertexf(-width/2 + x, -height/2 + y+sy, -depth/2);
			pG->glVertexf(-width/2 + x, -height/2 + y, -depth/2);
		}

		pG->glNormalf(-1, 0, 0);
		for (int j = 0; j <= segments; j++)
		{
			float z = ((float)j/segments) * depth + dz;
			pG->glVertexf(-width/2, -height/2 + y+sy, -depth/2 + z);
			pG->glVertexf(-width/2, -height/2 + y, -depth/2 + z);
		}

		pG->glEnd();
	}

	pG->glBegin(GL_QUADS);

	/*
	pG->glNormalf(0, 0, 1);
	pG->glVertexf(-width/2, -height/2, depth/2);
	pG->glVertexf(width/2, -height/2, depth/2);
	pG->glVertexf(width/2, height/2, depth/2);
	pG->glVertexf(-width/2, height/2, depth/2);

	pG->glNormalf(0, 0, -1);
	pG->glVertexf(-width/2, -height/2, -depth/2);
	pG->glVertexf(width/2, -height/2, -depth/2);
	pG->glVertexf(width/2, height/2, -depth/2);
	pG->glVertexf(-width/2, height/2, -depth/2);

	pG->glNormalf(-1, 0, 0);
	pG->glVertexf(-width/2, -height/2, depth/2);
	pG->glVertexf(-width/2, -height/2, -depth/2);
	pG->glVertexf(-width/2, height/2, -depth/2);
	pG->glVertexf(-width/2, height/2, depth/2);

	pG->glNormalf(1, 0, 0);
	pG->glVertexf(width/2, -height/2, depth/2);
	pG->glVertexf(width/2, -height/2, -depth/2);
	pG->glVertexf(width/2, height/2, -depth/2);
	pG->glVertexf(width/2, height/2, depth/2);
	*/

	pG->glNormalf(0, 1, 0);
	pG->glVertexf(-width/2, height/2, depth/2);
	pG->glVertexf(width/2, height/2, depth/2);
	pG->glVertexf(width/2, height/2, -depth/2);
	pG->glVertexf(-width/2, height/2, -depth/2);

	pG->glNormalf(0, -1, 0);
	pG->glVertexf(-width/2, -height/2, depth/2);
	pG->glVertexf(-width/2, -height/2, -depth/2);
	pG->glVertexf(width/2, -height/2, -depth/2);
	pG->glVertexf(width/2, -height/2, depth/2);

	pG->glEnd();
#endif
}

void Circle(LDraw::Graphics3D* pG, float cx, float cy, float radius, int segments = 12);

void Circle(LDraw::Graphics3D* pG, float cx, float cy, float radius, int segments)
{
	ASSERT(0);
#if 0
	pG->glBegin(GL_LINE_STRIP);

	for (int i = 0; i <= segments; i++)
	{
		float angle = (M_PI*2) * i / segments;

		float x = cx + cos(angle)*radius;
		float y = cy + sin(angle)*radius;

		pG->glVertexf(x, y);
	}

	pG->glEnd();
#endif
}

void Cube(LDraw::Graphics3D* pG, float width, float height, float depth, float dx = 0, float dy = 0, float dz = 0);
}

namespace UI
{
namespace Media3D
{

//void ComputeCombinedTransform(Group* pGroup, const LDraw::matrix4f& transform);
//void ApplyBones(Group* pGroup);

bool point_near_line_2d(const LDraw::vector3f& A, const LDraw::vector3f& B, const LDraw::vector3f& P, double* t)
{
	double bboxX1 = MIN(A[0], B[0])-2;
	double bboxY1 = MIN(A[1], B[1])-2;
	double bboxX2 = MAX(A[0], B[0])+2;
	double bboxY2 = MAX(A[1], B[1])+2;

	if (P[0] >= bboxX1 && P[1] >= bboxY1 && P[0] <= bboxX2 && P[1] <= bboxY2)
	{
		double a2 = (P[1]-A[1])*(B[0]-A[0]) - (P[0]-A[0])*(B[1]-A[1]);

		double d1 = (a2*a2)/((B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]));

		if (d1 < 3*3)
		{
		//	hit->element = this;
		//	hit->segment = i-1;

			double L2 = (B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]);
			*t = ((P[0]-A[0])*(B[0]-A[0]) + (P[1]-A[1])*(B[1]-A[1]))/L2;

		//	if (*t >= -0.0001 && *t <= 1.0001)
			{
				return true;
			}
		}
	}

	return false;
}

View3D::View3D(Document3D* document)
{
	m_document = document;
	m_dragging = 0;
	m_shading = Shading_None;

	m_raytracer = new Raytracer;
	m_raytracer->m_view = this;

	m_dragX = 0;
	m_dragY = 0;
	m_dragZ = 0;

	m_transformMode = 1;	// Translate

	m_Camera = NULL;
	/*
	m_orthoView[0] = -1;	// left
	m_orthoView[1] = 1;	// right
	m_orthoView[2] = -1;	// bottom
	m_orthoView[3] = 1;	// top
	*/

	m_orthoOffsetX = 0.0;
	m_orthoOffsetY = 0.0;
	m_orthoScale = 1.0;

	m_renderedBitmap = NULL;

	SetRetainedMode(false);

	AddAccel(UI::Accel(0, 'z', 4/*ID_FILE_OPEN*/));
	AddAccel(UI::Accel(FACCEL_VIRT, VK_TAB, 5/*ID_FILE_OPEN*/));
	AddAccel(UI::Accel(FACCEL_VIRT, VK_ESCAPE, 40));
//		AddAccel(UI::Accel(FACCEL_VIRT, VKEY_F5, ID_DEBUG_GO));
//		AddAccel(UI::Accel(FACCEL_VIRT, VKEY_F10, ID_DEBUG_STEPINTO));
}

#if 0
void View3D::DrawCamera(LDraw::Graphics3D* pG)
{
	LDraw::SizeD actualSize = get_ActualSize();

	double fovy = 45;
	double zNear = 0.5;
//	double zFar = 100.0;
	double zFar = zNear + 1.0;
	double aspect = actualSize.Width / actualSize.Height;

	double ntop = zNear * tan( fovy * M_PI / 360.0 );
	double nbottom = -ntop;
	double nleft = nbottom * aspect;
	double nright = ntop * aspect;

	double ftop = zFar * tan( fovy * M_PI / 360.0 );
	double fbottom = -ftop;
	double fleft = fbottom * aspect;
	double fright = ftop * aspect;

	/*
	ntop = -1+0.001;
	nbottom = 1-0.001;
	nleft = -1+0.001;
	nright = 1-0.001;
	*/
	/*
	nleft = -actualSize.Width/2;
	nright = actualSize.Width/2;
	nbottom = -actualSize.Height/2;
	ntop = actualSize.Height/2;
	*/

	/*
	nleft *= actualSize.Width/2;
	nright *= actualSize.Width/2;
	nbottom *= actualSize.Height/2;
	ntop *= actualSize.Height/2;

	fleft *= actualSize.Width/2;
	fright *= actualSize.Width/2;
	fbottom *= actualSize.Height/2;
	ftop *= actualSize.Height/2;
	*/

//	zFar -= zNear;
//	zNear -= zNear;
	{


		pG->glBegin(GL_LINES);

		pG->glVertexf(nleft, nbottom, -zNear);
		pG->glVertexf(nleft, ntop, -zNear);

		pG->glVertexf(nleft, ntop, -zNear);
		pG->glVertexf(nright, ntop, -zNear);

		pG->glVertexf(nright, ntop, -zNear);
		pG->glVertexf(nright, nbottom, -zNear);

		pG->glVertexf(nright, nbottom, -zNear);
		pG->glVertexf(nleft, nbottom, -zNear);

		pG->glEnd();
	}

	{
		pG->glBegin(GL_LINES);

		pG->glVertexf(nleft, nbottom, -zNear);
		pG->glVertexf(fleft, fbottom, -zFar);

		pG->glVertexf(nleft, ntop, -zNear);
		pG->glVertexf(fleft, ftop, -zFar);

		pG->glVertexf(nright, ntop, -zNear);
		pG->glVertexf(fright, ftop, -zFar);

		pG->glVertexf(nright, nbottom, -zNear);
		pG->glVertexf(fright, fbottom, -zFar);

		pG->glEnd();
	}

	{
		pG->glBegin(GL_LINE_STRIP);

		pG->glVertexf(fleft, fbottom, -zFar);
		pG->glVertexf(fleft, ftop, -zFar);
		pG->glVertexf(fright, ftop, -zFar);
		pG->glVertexf(fright, fbottom, -zFar);
		pG->glVertexf(fleft, fbottom, -zFar);

		pG->glEnd();
	}
}
#endif

View3D::Shading View3D::get_Shading()
{
	return m_shading;
}

void View3D::set_Shading(Shading shading)
{
	m_shading = shading;
	InvalidateRender();
}

void View3D::mousedown(UINT nFlags, LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], LDraw::vector3f mousepos, Object3D* object, vector<SelectedObject*> & selectedObjects)
{
	model *= object->m_transform->m_matrix;

	bool bHit = false;

	if (object->m_bSelected && (m_document->m_objectMode == Mode_Model || m_document->m_objectMode == Mode_Axis))
	{
		LDraw::vector3f obj = LDraw::vector3f(0,0,0).Project(model, proj, viewport);

		if (fabs(mousepos[0] - obj[0]) < 3 && fabs(mousepos[1] - obj[1]) < 3)
		{
			SelectedObject* p = object->m_selectedObject;//new SelectedObject;
		//	p->m_object = object;
			p->m_startTransform = object->m_transform->m_matrix;
			p->m_wtransform = model;
			p->m_z = obj[2];
			p->m_axis = 0;

			selectedObjects.Add(p);

//				m_document->m_selectedObject = shape;
//				m_document->m_selectedObject->m_bSelected = true;
//				m_objectTransform = wtransform;
			bHit = true;
		}
	}

	if (!bHit && object->m_bSelected)
	{
		if (m_transformMode & 4)
		{
			LDraw::vector3f obj = LDraw::vector3f(0,0,0).Project(model, proj, viewport);

			LDraw::vector3f d = mousepos - obj;

			float dist = d[0]*d[0] + d[1]*d[1];// + d[2]*d[2];

			float radius = 50;

		//	if (fabs(dist - radius*radius) < 5*5)
			if (fabs(sqrt(dist) - radius) < 5)
			{
				MessageBeep(-1);
				bHit = true;

				SelectedObject* p = object->m_selectedObject;

				p->m_startTransform = object->m_transform->m_matrix;
				p->m_wtransform = model;

				p->m_axis = 0;
				p->m_axis_t = acos(d[0] / radius);

				selectedObjects.Add(p);
			}
		}
	}

	if (!bHit && object->m_bSelected)
	{
		LDraw::matrix4f model2 = model * LDraw::matrix4f::getTranslate(object->m_selectedObject->m_pivotPoint);

		LDraw::vector3f obj = LDraw::vector3f(0,0,0).Project(model, proj, viewport);

		float scale = 0.05f;
		LDraw::vector3f xaxis = LDraw::vector3f(10*scale, 0, 0).Project(model, proj, viewport);
		LDraw::vector3f yaxis = LDraw::vector3f(0, 10*scale, 0).Project(model, proj, viewport);
		LDraw::vector3f zaxis = LDraw::vector3f(0, 0, 10*scale).Project(model, proj, viewport);

		int axis = 0;

		double t;
		if (point_near_line_2d(obj, xaxis, mousepos, &t))
		{
			axis = 1;
		}
		else if (point_near_line_2d(obj, yaxis, mousepos, &t))
		{
			axis = 2;
		}
		else if (point_near_line_2d(obj, zaxis, mousepos, &t))
		{
			axis = 3;
		}

		if (axis)
		{
			SelectedObject* p = object->m_selectedObject;
		//	p->m_object = object;
			p->m_wtransform = model;

			// ??
			if (m_document->m_objectMode == Mode_Model || m_document->m_objectMode == Mode_Axis)
				p->m_startTransform = object->m_transform->m_matrix;
			else
				p->m_startTransform = LDraw::matrix4f::getIdentity();

			p->m_z = obj[2];

			p->m_axis = axis;
			p->m_axis_t = t;

			selectedObjects.Add(p);
		}
	}

	if (Group* group = dynamic_cast<Group*>(object))
	{
		mousedown(nFlags, model, proj, viewport, mousepos, group, selectedObjects);
	}
	else if (Shape* shape = dynamic_cast<Shape*>(object))
	{
		mousedown(nFlags, model, proj, viewport, mousepos, shape, selectedObjects);
	}
	else if (Camera* shape = dynamic_cast<Camera*>(object))
	{
		mousedown(nFlags, model, proj, viewport, mousepos, shape, selectedObjects);
	}
}

void View3D::mousedown(UINT nFlags, LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], LDraw::vector3f mousepos, Group* group, vector<SelectedObject*> & selectedObjects)
{
#if 0
	_Transform3D* transform = group->get_Transform();
	if (transform)
	{
		LDraw::Matrix4 matrix = transform->get_Value();
	//	float m[16];
	//	matrix.Get(m);

		model = matrix * model;

	//	pG->glMultMatrixf(m);
	//	mousepos = matrix.GetInverse().Transform(mousepos);
	}
#endif

	for (int i = 0; i < group->m_Children->m_items.GetSize(); i++)
	{
		mousedown(nFlags, model, proj, viewport, mousepos, group->m_Children->m_items[i], selectedObjects);
		if (selectedObjects.GetSize() > 0)
			break;
	}

	/*
	if (m_document->m_objectMode == Model)
	{
		LDraw::vector3f obj = LDraw::vector3f(0,0,0).Project(model, proj, viewport);

		if (fabs(mousepos[0] - obj[0]) < 3 && fabs(mousepos[1] - obj[1]) < 3)
		{
			SelectedObject* p = new SelectedObject;
			p->m_object = group;
			p->m_startTransform = group->m_transform;
			p->m_wtransform = model;
			p->m_z = obj[2];
			p->m_axis = 0;

			selectedObjects.Add(p);

//				m_document->m_selectedObject = shape;
//				m_document->m_selectedObject->m_bSelected = true;
//				m_objectTransform = wtransform;
		}
	}
	*/
}

void View3D::hittest(const LDraw::matrix4f& model, const LDraw::matrix4f& proj, const double viewport[4], UI::Media3D::IndexedFaceSet* object, LDraw::vector3f mousepos, vector<int> & arr)
{
	//vector2f mousevec(mousepos.X, mousepos.Y);

	for (int i = 0; i < object->m_points->m_items.GetSize(); i++)
	{
		LDraw::vector3f vec = object->m_points->m_items[i];
		bool bHit = false;

		//LDraw::vector3f vec(ppoint), ppoint->get_Y(), ppoint->get_Z());

		vec = vec.Project(model, proj, viewport);

		if (fabs(mousepos[0] - vec[0]) < 3 && fabs(mousepos[1] - vec[1]) < 3)
		{
			arr.Add(i);
			//arr2.Add(vec[
		}
	}
}

void View3D::mousedown(UINT nFlags, LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], LDraw::vector3f mousepos, Shape* shape, vector<SelectedObject*>& selectedObjects)
{
	if (shape->m_selectedObject && m_document->m_objectMode == Mode_Points)
	{
		IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(shape->m_Geometry);
		if (faceset)
		{
			vector<int> hits;
			hittest(model, proj, viewport, faceset, mousepos, hits);
			if (hits.GetSize())
			{
			//	if (hits.size() > 0)

				shape->m_selectedObject->m_wtransform = model;
				//shape->m_selectedObject->m_geometry = faceset;

				shape->m_selectedObject->m_axis = 0;

				// TODO, not
				shape->m_selectedObject->m_z = 0;
				//LDraw::vector3f obj = LDraw::vector3f(0,0,0).Project(model, proj, viewport);
				//shape->m_selectedObject->m_z = obj[2];

				if (nFlags & 1)	// shift (toggle selected state)
				{
					for (int i = 0; i < hits.size(); i++)
					{
						unsigned int index = hits[i];

						if (shape->m_selectedObject->IsVertexSelected(index))
						{
							shape->m_selectedObject->DeselectVertex(index);
						}
						else
						{
							shape->m_selectedObject->SelectVertex(index);
						}
					}
				}
				else
				{
					shape->m_selectedObject->DeselectAllVertices();

					for (int i = 0; i < hits.size(); i++)
					{
						unsigned int index = hits[i];

						shape->m_selectedObject->SelectVertex(index);
					}
				}

				shape->m_selectedObject->m_pivotPoint = shape->m_selectedObject->CalculateMedian();
				/*

				SelectedObject* p = new SelectedObject;
				p->m_object = shape;
				p->m_wtransform = model;
				p->m_geometry = face;

				// TODO, not
				LDraw::vector3f obj = LDraw::vector3f(0,0,0).Project(model, proj, viewport);
				p->m_z = obj[2];

				for (int i = 0; i < hits.GetSize(); i++)
				{
					p->m_points.Add(hits[i]);
				}
				selectedObjects.Add(p);
				*/
			}
		}
	}
}

#if 0
void View3D::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		LDraw::SizeD actualSize = get_ActualSize();

		LDraw::matrix4f proj;
		double viewport[4] = {0, 0, actualSize.Width, actualSize.Height};

		LDraw::matrix4f model = LDraw::matrix4f::getIdentity();

		if (m_display == 4)
		{
			double fovy = 45;
			if (m_Camera)
			{
				fovy = m_Camera->get_FieldOfView();
			}

			double zNear = 0.5;
			double zFar = 1000.0;
			double aspect = actualSize.Width / actualSize.Height;

			proj = LDraw::matrix4f::getPerspective(fovy, aspect, zNear, zFar);

			if (m_Camera)
			{
				model *= m_Camera->m_combinedTransform.getInverse();
			}
			else
			{
				LDraw::vector3f norientation = m_document->m_orientation.m_axis;
				norientation.normalize();

				model = LDraw::matrix4f::getRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation[0], -norientation[1], -norientation[2]);
				model *= LDraw::matrix4f::getTranslate(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]);
			}
		}
		else
		{
			/*
			proj = LDraw::GetOrthoReally2D(	m_orthoOffsetX -actualSize.Width/2 / m_orthoScale,
															m_orthoOffsetX + actualSize.Width/2 / m_orthoScale,
															m_orthoOffsetY + -actualSize.Height/2 / m_orthoScale,
															m_orthoOffsetY + actualSize.Height/2 / m_orthoScale);
*/
			proj = LDraw::matrix4f::getOrtho2D(	m_orthoOffsetX -actualSize.Width/2 / m_orthoScale,
															m_orthoOffsetX + actualSize.Width/2 / m_orthoScale,
															m_orthoOffsetY + -actualSize.Height/2 / m_orthoScale,
															m_orthoOffsetY + actualSize.Height/2 / m_orthoScale);

			if (m_display == 1)
			{
				//pG->glRotatef(0, 0, 0, 0);
			}
			else if (m_display == 2)
			{
				model *= LDraw::matrix4f::getRotate(90, 1, 0, 0);
			}
			else if (m_display == 3)
			{
				model *= LDraw::matrix4f::getRotate(90, 0, 1, 0);
			}
		}

		if (*evt->get_type() == L"mousedown")
		{
#if 0
			{
				LDraw::matrix4f m1(0.6, 4.6, 3.8, -5.9, 3.8, -0.6, -0.4, 8.1, 5, 9.7, -6, 8.2, 45, 2, 9.4, -99);
				LDraw::matrix4f m2(6.6, 2.6, -9.8, 7.9, 2.9, -8.5, 7.4, -5.1, 2, 5.3, 6.6, 3.2, 11, 8, 2.4, -25);
				LDraw::matrix4f im2 = m2.getInverse();

				LDraw::matrix4f m = m1 * m2;

				LDraw::matrix4f n = m * im2;



				/*
				LDraw::matrix4f modeli = model->m_matrix.getInverse();
				LDraw::matrix4f m = proj->m_matrix * model->m_matrix;
				LDraw::matrix4f m2 = m * modeli;
				*/

				if (!(n == m1))
				{
					MessageBeep(-1);
				}
			}
#endif

			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = static_cast<UI::MouseEvent*>(evt);
			LDraw::PointD mousepos = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			mousepos.Y = actualSize.Height - mousepos.Y;

			m_startmousepos = mousepos;
			m_oldmousepos = mousepos;

			LDraw::vector3f mousevec;
			mousevec[0] = mousepos.X;
			mousevec[1] = mousepos.Y;
			mousevec[2] = 0;

			/*
			if (m_display == 4)
			{
				LDraw::vector3f norientation = m_document->m_orientation.m_axis;
				norientation.normalize();
				model = LDraw::matrix4f::getRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation[0], -norientation[1], -norientation[2]);
				model = model * LDraw::matrix4f::getTranslate(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]) * *model;
			}
			else
			{
				model = LDraw::matrix4f::getIdentity();
			}
			*/

			/*
		LDraw::vector3f obj = LDraw::vector3f(0,0,0).Project(model, proj, viewport);

				float scale = 0.01f;
			//	float scale = 1;
				LDraw::vector3f xaxis = LDraw::vector3f(10*scale, 0, 0).Project(model, proj, viewport);
				LDraw::vector3f yaxis = LDraw::vector3f(0, 10*scale, 0).Project(model, proj, viewport);
				LDraw::vector3f zaxis = LDraw::vector3f(0, 0, 10*scale).Project(model, proj, viewport);

			//	xaxis[1] = actualSize.Height - xaxis[1];
			//	yaxis[1] = actualSize.Height - yaxis[1];
			//	zaxis[1] = actualSize.Height - zaxis[1];

				int axis = 0;

				double t;
				if (point_near_line_2d(obj, xaxis, mousevec, &t))
				{
					axis = 1;
				}
				else if (point_near_line_2d(obj, yaxis, mousevec, &t))
				{
					axis = 2;
				}
				else if (point_near_line_2d(obj, zaxis, mousevec, &t))
				{
					axis = 3;
				}

				if (axis)
				{
					MessageBeep(-1);
				}

				return;
*/

			//m_document->m_selection.clear();

			UINT nFlags = 0;
			if (mouseEvt->m_bShift) nFlags |= 1;
			if (mouseEvt->m_bCtrl) nFlags |= 2;

			vector<SelectedObject*> selectedObjects;
			mousedown(nFlags, model, proj, viewport, mousevec, m_document->m_object, selectedObjects);

			/*
			if (true)
			{
				for (int i = 0; i < m_document->m_selectedObjects.GetSize(); i++)
				{
					if (m_document->m_selectedObjects[i]->m_object)
					{
						m_document->m_selectedObjects[i]->m_object->m_bSelected = false;
						m_document->m_selectedObjects[i]->m_object->m_selectedObject = NULL;
					}
				}
				m_document->m_selectedObjects.RemoveAll();

				m_document->m_selectedObjects = selectedObjects;
			}
			*/

			if (m_document->m_objectMode == Mode_Model || m_document->m_objectMode == Mode_Axis)
			{
				if (/*m_document->m_*/selectedObjects.GetSize() > 0)
				{
				//	m_document->m_selectedObjects[0]->m_object->m_selectedObject = m_document->m_selectedObjects[0];
				//	m_document->m_selectedObjects[0]->m_object->m_bSelected = true;
					m_document->Invalidate();
					
					m_dragging = 1;
					CaptureMouse();
				}
			}
			else if (m_document->m_objectMode == Mode_Points)
			{
				if (m_document->m_selectedObjects.GetSize() > 0)
				{
					for (int i = 0; i < m_document->m_selectedObjects.GetSize(); i++)
					{
						SelectedObject* pSelectedObject = m_document->m_selectedObjects[i];
						pSelectedObject->m_startVertices = dynamic_cast<IndexedFaceSet*>(dynamic_cast<Shape*>(pSelectedObject->m_object)->get_Geometry())->m_points->m_items;
						pSelectedObject->m_startPivotPoint = pSelectedObject->m_pivotPoint;
					}

				//	m_document->m_selectedObjects[0]->m_object->m_selectedObject = m_document->m_selectedObjects[0];
				//	m_document->m_selectedObjects[0]->m_object->m_bSelected = true;
					m_document->Invalidate();
					
					m_dragging = 1;
					CaptureMouse();
				}

				/*
					m_document->Invalidate();

					m_dragging = 1;
					SetCapture();
				*/
			}
		}
		else if (*evt->get_type() == L"mouseup")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = static_cast<UI::MouseEvent*>(evt);
			LDraw::PointD mousepos = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			mousepos.Y = actualSize.Height - mousepos.Y - 1;

			if (m_dragging)
			{
				m_dragging = 0;
				ReleaseMouseCapture();

				SelectedObject* pSelectedObject = m_document->m_selectedObjects[0];
				Object3D* object = pSelectedObject->m_object;

				if (m_document->m_objectMode == Mode_Axis)
				{
					Shape* pShape = dynamic_cast<Shape*>(object);
					if (pShape)
					{
						IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(pShape->m_Geometry);
						if (faceset)
						{
							faceset->Transform(pShape->m_geometryTransform);
							pShape->m_geometryTransform = LDraw::matrix4f::getIdentity();
						}
					}

					m_document->UpdateScene();
				//	ComputeCombinedTransform(m_document->m_object, LDraw::matrix4f::getIdentity());
				//	ApplyBones(m_document->m_object);
				//	m_document->Invalidate();
				}
			}
		}
		else if (*evt->get_type() == L"mousemove")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = static_cast<UI::MouseEvent*>(evt);
			LDraw::PointD mousepos = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			mousepos.Y = actualSize.Height - mousepos.Y - 1;

			if (m_dragging)
			{
				LDraw::PointD delta = mousepos - m_oldmousepos;

				for (int i = 0; i < m_document->m_selectedObjects.GetSize(); i++)
				{
					SelectedObject* pSelectedObject = m_document->m_selectedObjects[i];

					LDraw::matrix4f model = pSelectedObject->m_wtransform;

					LDraw::vector3f mousevec(mousepos.X, mousepos.Y, pSelectedObject->m_z);
				//	LDraw::vector3f oldmousevec(m_oldmousepos.X, m_oldmousepos.Y, pSelectedObject->m_z);
					LDraw::vector3f startmousevec(m_startmousepos.X, m_startmousepos.Y, pSelectedObject->m_z);

#if 0
					if (false)
					{
						double win[3];
						double obj[3];

						{

							double _model[16];
							_model[0] = ((float*)model)[0];
							_model[1] = ((float*)model)[1];
							_model[2] = ((float*)model)[2];
							_model[3] = ((float*)model)[3];
							_model[4] = ((float*)model)[4];
							_model[5] = ((float*)model)[5];
							_model[6] = ((float*)model)[6];
							_model[7] = ((float*)model)[7];
							_model[8] = ((float*)model)[8];
							_model[9] = ((float*)model)[9];
							_model[10] = ((float*)model)[10];
							_model[11] = ((float*)model)[11];
							_model[12] = ((float*)model)[12];
							_model[13] = ((float*)model)[13];
							_model[14] = ((float*)model)[14];
							_model[15] = ((float*)model)[15];

							double _proj[16];
							_proj[0] = ((float*)proj)[0];
							_proj[1] = ((float*)proj)[1];
							_proj[2] = ((float*)proj)[2];
							_proj[3] = ((float*)proj)[3];
							_proj[4] = ((float*)proj)[4];
							_proj[5] = ((float*)proj)[5];
							_proj[6] = ((float*)proj)[6];
							_proj[7] = ((float*)proj)[7];
							_proj[8] = ((float*)proj)[8];
							_proj[9] = ((float*)proj)[9];
							_proj[10] = ((float*)proj)[10];
							_proj[11] = ((float*)proj)[11];
							_proj[12] = ((float*)proj)[12];
							_proj[13] = ((float*)proj)[13];
							_proj[14] = ((float*)proj)[14];
							_proj[15] = ((float*)proj)[15];

							int _viewport[4];
							_viewport[0] = viewport[0];
							_viewport[1] = viewport[1];
							_viewport[2] = viewport[2];
							_viewport[3] = viewport[3];

							::gluProject(mousevec[0], mousevec[1], mousevec[2], _model, _proj, _viewport, &win[0], &win[1], &win[2]);

							::gluUnProject(win[0], win[1], win[2], _model, _proj, _viewport, &obj[0], &obj[1], &obj[2]);
						}

						LDraw::vector3f mousevec2 = mousevec.Project(model, proj, viewport);

						LDraw::vector3f mousevec3 = mousevec2.UnProject(model, proj, viewport);

						/*
						ASSERT(mousevec3[0] == mousevec[0]);
						ASSERT(mousevec3[1] == mousevec[1]);
						ASSERT(mousevec3[2] == mousevec[2]);
						*/
					}
#endif

					mousevec = mousevec.UnProject(model, proj, viewport);
				//	oldmousevec = oldmousevec.UnProject(model, proj, viewport);
					startmousevec = startmousevec.UnProject(model, proj, viewport);

					/*
					if (PerspectiveCamera* shape = dynamic_cast<PerspectiveCamera*>(pSelectedObject->m_object))
					{
						shape->get_Position()->m_X += mousevec[0] - oldmousevec[0];
						shape->get_Position()->m_Y += mousevec[1] - oldmousevec[1];
						shape->get_Position()->m_Y += mousevec[2] - oldmousevec[2];
					}
					else// if (Group* shape = dynamic_cast<Group*>(pSelectedObject->m_object))
					*/
					{
						Object3D* object = pSelectedObject->m_object;
						LDraw::matrix4f mat;

						if (pSelectedObject->m_axis)
						{
							if (m_transformMode & 1)	// Translate
							{
								m_dragX = 0;
								m_dragY = 0;
								m_dragZ = 0;

								if (pSelectedObject->m_axis == 1)
								{
									double translateX = mousevec[0] - startmousevec[0];
									m_dragX = translateX;

									mat = LDraw::matrix4f::getTranslate(translateX, 0, 0);
								}
								else if (pSelectedObject->m_axis == 2)
								{
									double translateY = mousevec[1] - startmousevec[1];
									m_dragY = translateY;

									mat = LDraw::matrix4f::getTranslate(0, translateY, 0);
								}
								else if (pSelectedObject->m_axis == 3)
								{
									double translateZ = mousevec[2] - startmousevec[2];
									m_dragZ = translateZ;

									mat = LDraw::matrix4f::getTranslate(0, 0, translateZ);
								}
							}
							else	// Scale
							{
								if (pSelectedObject->m_axis == 1)
								{
									double scaleX = (mousevec[0] / startmousevec[0]);

									mat = LDraw::matrix4f::getTranslate(pSelectedObject->m_pivotPoint) *
											LDraw::matrix4f::getScale(scaleX, 1, 1) *
											LDraw::matrix4f::getTranslate(-pSelectedObject->m_pivotPoint);
								}
								else if (pSelectedObject->m_axis == 2)
								{
									double scaleY = mousevec[1] / startmousevec[1];

									mat = LDraw::matrix4f::getTranslate(pSelectedObject->m_pivotPoint) *
											LDraw::matrix4f::getScale(1, scaleY, 1) *
											LDraw::matrix4f::getTranslate(-pSelectedObject->m_pivotPoint);
								}
								else if (pSelectedObject->m_axis == 3)
								{
									double scaleZ = mousevec[2] / startmousevec[2];

									mat = LDraw::matrix4f::getTranslate(pSelectedObject->m_pivotPoint) *
											LDraw::matrix4f::getScale(1, 1, scaleZ) *
											LDraw::matrix4f::getTranslate(-pSelectedObject->m_pivotPoint);
								}
							}
						}
						else
						{
							// Move

						//	LDraw::Matrix4 mat = LDraw::Matrix4::GetTranslate(mousevec[0] - startmousevec[0], mousevec[1] - startmousevec[1], mousevec[2] - startmousevec[2]);
			//				__release<LDraw::Matrix4> mat = LDraw::Matrix4::GetRotate(mousevec[0] - startmousevec[0], 0, 0, 1);
			//				shape->m_transform = *mat * *pSelectedObject->m_startTransform;

							if (m_transformMode & 1)
							{
								m_dragX = mousevec[0] - startmousevec[0];
								m_dragY = mousevec[1] - startmousevec[1];
								m_dragZ = mousevec[2] - startmousevec[2];

								mat = LDraw::matrix4f::getTranslate(mousevec[0] - startmousevec[0], mousevec[1] - startmousevec[1], mousevec[2] - startmousevec[2]);
							}
							else
							{
								// rotate around z axis of current view

								LDraw::vector3f v(0, 0, 1);
							//	v = proj.getInverse().transform(v);
							//	v = proj.transform(v);

								//LDraw::matrix4f view = model;
								//LDraw::matrix4f view = proj * model;

								LDraw::vector3f center = model.transform(LDraw::vector3f(0,0,0));

								//v = proj.transform(v);

								mat = 
									
									model.getInverse() *
									LDraw::matrix4f::getTranslate(center) *
									LDraw::matrix4f::getRotate((mousepos.X - m_startmousepos.X)/5, v) *
									LDraw::matrix4f::getTranslate(-center) *
									model;
							}

							/*
							for (int i = 0; i < shape->m_references.size(); i++)
							{
								Bone* pBone = dynamic_cast<Bone*>(shape->m_references[i]->m_referencing);

								pBone->m_matrixOffset = mat * pBone->m_matrixOffset;
							}
							*/
						}

						if (m_document->m_objectMode == Mode_Model || m_document->m_objectMode == Mode_Axis)
						{
							object->m_transform = new LDraw::Matrix4(pSelectedObject->m_startTransform * mat);

							if (m_document->m_objectMode == Mode_Axis)
							{
								Shape* pShape = dynamic_cast<Shape*>(object);
								if (pShape)
								{
									pShape->m_geometryTransform = mat.getInverse();
								}
								else
								{
									// TODO
									// if group, transform children

								}
							}
						}
						else if (m_document->m_objectMode == Mode_Points)
						{
						//	for (int i = 0; i < m_document->m_selectedObjects.GetSize(); i++)
						//		SelectedObject* pSelectedObject = m_document->m_selectedObjects[i];

							IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(dynamic_cast<Shape*>(pSelectedObject->m_object)->get_Geometry());
							for (int j = 0; j < pSelectedObject->m_points.GetSize(); j++)
							{
								int index = pSelectedObject->m_points[j];

								faceset->m_points->m_items[index] = mat.transform(pSelectedObject->m_startVertices[index]);

							//	__release<LDraw::Matrix4> model = pSelectedObject->m_wtransform;

								/*
							//	LDraw:vector3f 
							//	Proje
								pSelectedObject->m_z = 0;	// TODO

								LDraw::vector3f mousevec(mousepos.X, mousepos.Y, pSelectedObject->m_z);
								LDraw::vector3f oldmousevec(m_oldmousepos.X, m_oldmousepos.Y, pSelectedObject->m_z);
								LDraw::vector3f startmousevec(m_startmousepos.X, m_startmousepos.Y, pSelectedObject->m_z);

								mousevec = mousevec.UnProject(model, proj, viewport);
								oldmousevec = oldmousevec.UnProject(model, proj, viewport);
								startmousevec = startmousevec.UnProject(model, proj, viewport);

								IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(pSelectedObject->m_geometry);
								for (int j = 0; j < pSelectedObject->m_points.GetSize(); j++)
								{
									int index = pSelectedObject->m_points[j];

									faceset->m_points->m_items[index][0] += mousevec[0] - oldmousevec[0];
									faceset->m_points->m_items[index][1] += mousevec[1] - oldmousevec[1];
									faceset->m_points->m_items[index][2] += mousevec[2] - oldmousevec[2];
								}
								*/
							}

							if (m_transformMode & 1)	// Translate
							{
						//		pSelectedObject->m_pivotPoint = pSelectedObject->CalculateMedian();
								pSelectedObject->m_pivotPoint = mat.transform(pSelectedObject->m_startPivotPoint);
							}
						}
					}
				}

				m_document->UpdateScene();
			//	ComputeCombinedTransform(m_document->m_object, LDraw::Matrix4::GetIdentity());
			//	ApplyBones(m_document->m_object);
				m_document->Invalidate();
			}

			m_oldmousepos = mousepos;
		}
		else if (*evt->get_type() == L"contextmenu")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = static_cast<UI::MouseEvent*>(evt);

			UI::CLXUIMenuElement* menu = new UI::CLXUIMenuElement();
		//	menu->SetRParent(m_ctledit);
			menu->SetOwnerWindow(mouseEvt->GetOwnerWindow());

			menu->addEventListener(WSTR("command"), this, false);	// TODO, remove

			menu->AddItem(new UI::TextString(WSTR("Translate")), 6);
			menu->AddItem(new UI::TextString(WSTR("Scale")), 7);
			menu->AddItem(new UI::TextString(WSTR("Rotate")), 8);

			menu->AddItem(new UI::TextString(WSTR("Model")), 9);
			menu->AddItem(new UI::TextString(WSTR("Axis")), 10);
			menu->AddItem(new UI::TextString(WSTR("Points")), 11);
			menu->AddItem(new UI::TextString(WSTR("Edges")), 12);

			menu->AddItem(new UI::TextString(WSTR("Active Object as Camera")), 20);

			menu->GetMenuPopup()->Popup(menu, LDraw::PointI(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));
		}
		else if (*evt->get_type() == L"command")
		{
			CommandInvokeEvent* cmdEvt = static_cast<CommandInvokeEvent*>(evt);

			long param = cmdEvt->get_Command();

			switch (param)
			{
			case 4:
				{
					if (m_shading == Shading_None)
					{
						m_shading = Shading_Flat;
					}
					else if (m_shading == Shading_Flat)
					{
					//	m_shading = Shading_None;
						m_shading = Shading_Raytrace;
					}
					else if (m_shading == Shading_Raytrace)
					{
						if (m_renderedBitmap)
						{
							for (int i = 0; i < m_raytracer->numThreads; i++)
							{
								RaytracerThread* thread = m_raytracer->m_threads[i];

								thread->bQuit = true;
								MSWindows::WaitForSingleObject(thread->m_hThread, INFINITE);
								MSWindows::CloseHandle(thread->m_hThread);
							}
							m_raytracer->numThreads = 0;
							m_raytracer->m_threads.clear();

							delete m_renderedBitmap;
							m_renderedBitmap = NULL;
						}

						m_shading = Shading_None;
					}

					Invalidate();
				}
				break;

			case 5:	// TAB
				{
					if (m_document->m_objectMode == Mode_Model)
						m_document->m_objectMode = Mode_Axis;
					else if (m_document->m_objectMode == Mode_Axis)
						m_document->m_objectMode = Mode_Model;
				//	else if (m_document->m_objectMode == Mode_Points)
				//		m_document->m_objectMode = Mode_Model;
				}
				break;

			case 6:	// Translate
				{
					m_transformMode = 1;
					Invalidate();
				}
				break;

			case 7:	// Scale
				{
					m_transformMode = 2;
					Invalidate();
				}
				break;

			case 8:	// Rotate
				{
					m_transformMode = 4;
					Invalidate();
				}
				break;

			case 9:	// Model
				{
					m_document->m_objectMode = Mode_Model;
					Invalidate();
				}
				break;

			case 10:	// Axis
				{
					m_document->m_objectMode = Mode_Axis;
					Invalidate();
				}
				break;

			case 11:	// Points
				{
					m_document->m_objectMode = Mode_Points;
					Invalidate();
				}
				break;

			case 12:	// Edges
				{
					m_document->m_objectMode = Mode_Edges;
					Invalidate();
				}
				break;

			case 20:	// Object as Camera
				{
					if (m_document->m_selectedObjects.GetSize() > 0)
					{
						m_Camera = dynamic_cast<Camera*>(m_document->m_selectedObjects[0]->m_object);
						Invalidate();
					}
				}
				break;

			case 40:	// Cancel Render
				{
					if (m_renderedBitmap)
					{
						for (int i = 0; i < m_raytracer->numThreads; i++)
						{
							RaytracerThread* thread = m_raytracer->m_threads[i];

							thread->bQuit = true;
							thread->Wait();
						}
						m_raytracer->numThreads = 0;
						m_raytracer->m_threads.clear();

						Invalidate();
					}
				}
				break;
			}

		//	MessageBoxA(NULL, "", "", MB_OK);
		}
	}

	Control::handleEvent(evt);
}
#endif


/*
void GetPerspective(LDraw::matrix4f* matrix, double fovy, double aspect, double zNear, double zFar)
{
	// fovy is the angle in the yz plane

	double top = zNear * tan( fovy * M_PI / 360.0 );
	double bottom = -top;

	double left = bottom * aspect;
	double right = top * aspect;

	LDraw::FrustumMatrix(*matrix, left, right, bottom, top, zNear, zFar);
}
*/

#if 0
int gluProject3(const float obj[3], const float proj[16], const double viewport[4], float win[3])
{
	/* matrice de transformation */
	//__declspec(align(16)) float in[4];

	__declspec(align(16)) float out[4];

	/* initilise la matrice et le vecteur a transformer */
	out[0]=obj[0]; out[1]=obj[1]; out[2]=obj[2]; out[3]=1.0;
//	transform_point_unaligned(out,out,model);
	LDraw::transform_point_unaligned(out,out,proj);

	/* d'ou le resultat normalise entre -1 et 1*/
	if (out[3]==0.0f)
		return GL_FALSE;

//	out[0]/=out[3]; out[1]/=out[3]; out[2]/=out[3];

	/* window coordinates */
//	win[0] = viewport[0]+(1+out[0])*viewport[2]/2;
//	win[1] = viewport[1]+(1+out[1])*viewport[3]/2;
	win[0] = viewport[0]+(out[0])*viewport[2]/1;
	win[1] = viewport[1]+(out[1])*viewport[3]/1;

	//	win[1] = viewport[3] - win[1];
		
	/* entre 0 et 1 suivant z */
//	win[2] = (1+out[2])/2;
	win[2] = (out[2]);

	return GL_TRUE;
}
#endif

/*
void fixup(LDraw::vector3f& v)
{
}
*/


LDraw::vector3f SelectedObject::CalculateMedian()
{
	IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(dynamic_cast<Shape*>(m_object)->get_Geometry());

	if (m_points.GetSize() == 1)
	{
		return faceset->m_points->m_items[m_points[0]];
	}
	else if (m_points.GetSize() == 2)
	{
		LDraw::vector3f v0 = faceset->m_points->m_items[m_points[0]];
		LDraw::vector3f v1 = faceset->m_points->m_items[m_points[1]];

		return v0 + (v1 - v0)/2.0f;
	}

	// TODO

	return LDraw::vector3f(0,0,0);
}

void SelectedObject::DeselectAllVertices()
{
	m_vertexSelected.clear();
	m_points.clear();
}

void SelectedObject::SelectVertex(unsigned int index)
{
	if (m_vertexSelected.GetSize() <= index)
	{
		m_vertexSelected.resize(index+1);
	}
	else
	{
		if (m_vertexSelected[index])
			return;
	}

	m_vertexSelected[index] = true;

	// Insert sorted
	{
		int j;
		for (j = 0; j < m_points.GetSize(); j++)
		{
			if (m_points[j] > index)
				break;
		}

		m_points.InsertAt(j, index);
	}
}

void SelectedObject::DeselectVertex(unsigned int index)
{
	if (m_vertexSelected.GetSize() <= index || !m_vertexSelected[index])
		return;

	m_vertexSelected[index] = false;

	int j;
	for (j = 0; j < m_points.GetSize(); j++)
	{
		if (m_points[j] == index)
			break;
	}

	m_points.RemoveAt(j);
}

void View3D::RenderView()
{
	LDraw::SizeD actualSize = get_ActualSize();

	int bitmapWidth = ceil(actualSize.Width);
	int bitmapHeight = ceil(actualSize.Height);

//	if (m_renderedBitmap)
//		return;

	if (m_renderedBitmap == NULL || m_renderedBitmap->GetWidth() != bitmapWidth || m_renderedBitmap->GetHeight() != bitmapHeight)
	{
		if (m_renderedBitmap)
		{
			delete m_renderedBitmap;
		}

		m_renderedBitmap = new LDraw::Bitmap(bitmapWidth, bitmapHeight, LDraw::PixelFormat_t::RGB_24);
	}

	m_raytracer->zNear = 0.5;

	if (m_Camera)
	{
		m_raytracer->m_orthographic = m_Camera->get_Orthographic();

		if (m_raytracer->m_orthographic)
		{
			m_raytracer->left = -1;
			m_raytracer->right = 1;
			m_raytracer->bottom = -1;
			m_raytracer->top = 1;
		}
		else
		{
			double aspect = actualSize.Width / actualSize.Height;

			double fovy = m_Camera->get_FieldOfView();
			m_raytracer->top = m_raytracer->zNear * tan( fovy * M_PI / 360.0 );
			m_raytracer->bottom = -m_raytracer->top;

			m_raytracer->left = m_raytracer->bottom * aspect;
			m_raytracer->right = m_raytracer->top * aspect;
		}
	}
	else
		return;

	if (m_Camera)
	{
		m_raytracer->model = m_Camera->m_combinedTransform.getInverse();
		m_raytracer->modelInverse = m_Camera->m_combinedTransform;
	}

	if (false)
	{
		LDraw::vector3f norientation = m_document->m_orientation.m_axis;
		norientation.normalize();
	//	pG->glRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation);

	//	pG->glTranslatef(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]);

		m_raytracer->model = LDraw::matrix4f::getRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation[0], -norientation[1], -norientation[2]);
		m_raytracer->model *= LDraw::matrix4f::getTranslate(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]);
	}

	m_raytracer->faces.clear();
	buildtris(m_document->m_object, m_raytracer->model, m_raytracer->faces);

	{
		for (int nlight = 0; nlight < m_document->m_lights.size(); nlight++)
		{
			Light* light = m_document->m_lights[nlight];

			light->m_transformedLocation = m_raytracer->model.transform(light->m_location);
		}
	}

	// This is a hack
	m_renderedBitmap->LockBits(NULL, LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite, &m_raytracer->bitmapdata);
	m_renderedBitmap->UnlockBits(&m_raytracer->bitmapdata);

	m_raytracer->numThreads = GetNumberOfProcessors();

	if (m_raytracer->numThreads > bitmapHeight)
		m_raytracer->numThreads = bitmapHeight;

	int height = (bitmapHeight + m_raytracer->numThreads - 1) / m_raytracer->numThreads;

	int y = 0;

	for (unsigned int i = 0; i < m_raytracer->numThreads; i++)
	{
		RaytracerThread* thread = new RaytracerThread;
		thread->m_raytracer = m_raytracer;
		m_raytracer->m_threads.Add(thread);

		thread->vtop = y;
		thread->vbottom = y+height;
		if (thread->vbottom > bitmapHeight) thread->vbottom = bitmapHeight;
		y = thread->vbottom;

		thread->m_hThread = MSWindows::CreateThread(NULL, 0, RaytraceThreadFunc, thread, 0, &thread->m_threadId);
	}

	/*
	LDraw::vector3f xyz[3];

	xyz[0] = LDraw::vector3f(-30, -20, 12);
	xyz[1] = LDraw::vector3f(20, -20, 12);
	xyz[2] = LDraw::vector3f(20, 30, 12);
	*/

}

void View3D::OnRender(UI::Graphics* pGraphics)
{
	ASSERT(0);

#if 0
	LDraw::SizeD actualSize = get_ActualSize();

	if (m_shading == Shading_Raytrace)
	{
		RenderView();

		HANDLE handles[64];
		for (uint i = 0; i < m_raytracer->numThreads; i++)
		{
			handles[i] = m_raytracer->m_threads[i]->m_hThread;
		}

		MSWindows::WaitForMultipleObjects(m_raytracer->numThreads, handles, true, INFINITE);
		m_raytracer->m_threads.clear();
		m_raytracer->numThreads = 0;

		pGraphics->DrawImage(m_renderedBitmap, 0, 0);
		return;
	}

	/*
	{
		pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(160, 160, 160)), 0, 0, actualSize.Width, actualSize.Height);
	}
	*/

//	if (m_display != 4)
//		return;

#if 1
	LDraw::Graphics3DImmediate* pG = new LDraw::Graphics3DImmediate(m_document->m_glState, m_document->m_clientState, dynamic_cast<LDraw::GraphicsO*>(pGraphics->m_p));
//	pG->AddRef();
#else

	LDraw::DisplayList* list = new LDraw::DisplayList;
	LDraw::Graphics3DList* pG = new LDraw::Graphics3DList(m_document->m_glState, m_document->m_clientState, list);
//	pG->AddRef();
#endif

	pG->ClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	pG->Viewport(0, 0, actualSize.Width, actualSize.Height);
	double viewport[4] = {0, 0, actualSize.Width, actualSize.Height};

	pG->MatrixMode(GL_PROJECTION);
	pG->LoadIdentity();

	LDraw::matrix4f proj;
	LDraw::matrix4f model;

	if (m_display == 4)
	{
#if 1
		double fovy = 45;
		double zNear = 0.5;
		double zFar = 1000.0;
		double aspect = actualSize.Width / actualSize.Height;

		if (m_Camera)
		{
			if (!m_Camera->get_Orthographic())
			{
				fovy = m_Camera->get_FieldOfView();
				pG->Perspective(fovy, aspect, zNear, zFar);
				proj = LDraw::matrix4f::getPerspective(fovy, aspect, zNear, zFar);
			}
			else
			{
				double left = -1;
				double right = 1;
				double bottom = -1;
				double top = 1;

				pG->Ortho(left, right, bottom, top, zNear, zFar);
				proj = LDraw::matrix4f::getOrtho(left, right, bottom, top, zNear, zFar);
			}
		}
		else	// hm..
		{
			pG->Perspective(fovy, aspect, zNear, zFar);
			proj = LDraw::matrix4f::getPerspective(fovy, aspect, zNear, zFar);
		}

		pG->MatrixMode(GL_MODELVIEW);
		pG->LoadIdentity();

	//	DrawCamera(pG);

		/*
		if (true)
		{
			pG->glEnable(GL_DEPTH_TEST);
		}
		*/

		if (true)
		{
			if (m_shading != Shading_None)
			{
				pG->Enable(GL_NORMALIZE);
				pG->Enable(GL_LIGHTING);
				pG->Enable(GL_CULL_FACE);
			}

#if 0
			float light_position[4] = { 0, 0, 1, 0/*directional*/};

			float ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
			float position[] = {0,0,20,1};
			float mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1};
			float mat_specular[] = {1.0f,1.0f,1.0f,1.0f};
			float mat_shininess[] = {50.0f};

			pG->glEnable(GL_LIGHT0+0);
			pG->glLightfv(GL_LIGHT0+0, GL_POSITION, light_position);
			pG->glLightfv(GL_LIGHT0+0, GL_AMBIENT, ambient);
			pG->glLightfv(GL_LIGHT0+0, GL_DIFFUSE, mat_diffuse);
			pG->glLightfv(GL_LIGHT0+0, GL_SPECULAR , mat_specular);
#endif
		}

		//pG->glClearDepth(1);
		pG->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT*/);

		//model = LDraw::matrix4f::getIdentity();

		if (m_Camera)
		{
			/*
			LDraw::vector3f norientation = m_Camera->get_Orientation().m_axis;
			norientation.normalize();
			pG->glRotate(gmDegrees(m_Camera->get_Orientation().m_angle), -norientation);
			model = LDraw::matrix4f::getRotate(gmDegrees(m_Camera->get_Orientation().m_angle), -norientation[0], -norientation[1], -norientation[2]);
*/
			pG->MultMatrixf(m_Camera->m_combinedTransform.getInverse());
			model = m_Camera->m_combinedTransform.getInverse();

			/*
			LDraw::vector3f position = m_Camera->get_Position();
			LDraw::vector3f transformed_position = m_Camera->m_combinedTransform.transform(position);

			pG->glTranslatef(-transformed_position[0], -transformed_position[1], -transformed_position[2]);

			model = model * LDraw::matrix4f::getTranslate(-transformed_position[0], -transformed_position[1], -transformed_position[2]);
			*/
		}
		else
		{
			LDraw::vector3f norientation = m_document->m_orientation.m_axis;
			norientation.normalize();
			pG->glRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation);

			pG->glTranslatef(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]);

			model = LDraw::matrix4f::getRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation[0], -norientation[1], -norientation[2]);
			model *= LDraw::matrix4f::getTranslate(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]);
		}

		if (true)
		{
			pG->glBegin(GL_LINES);
			pG->glColorf(0.45f, 0.45f, 0.45f);

			for (int z = -5; z <= 5; z++)
			{
				pG->glVertexf(-5*5, 0, z*5);
				pG->glVertexf(5*5, 0, z*5);
			}

			for (int x = -5; x <= 5; x++)
			{
				pG->glVertexf(x*5, 0, -5*5);
				pG->glVertexf(x*5, 0, 5*5);
			}

			pG->glEnd();
		}

		pG->glColorf(0,0,0);
#endif
	}
	else
	{
		pG->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT*/);

		if (m_shading != Shading_None)
		{
			pG->Enable(GL_NORMALIZE);
			pG->Enable(GL_LIGHTING);
			pG->Enable(GL_CULL_FACE);
		}
		else
		{
			pG->Disable(GL_NORMALIZE);
			pG->Disable(GL_LIGHTING);
			pG->Disable(GL_DEPTH_TEST);
		}

			/*
			if (m_display == 1)
			{
				//pG->glRotatef(0, 0, 0, 0);
			}
			else if (m_display == 2)
			{
				proj = *LDraw::Matrix4::GetRotate(90, 1, 0, 0) * *proj;
			}
			else if (m_display == 3)
			{
				proj = *LDraw::Matrix4::GetRotate(90, 0, 1, 0) * *proj;
			}
			*/

		OrthoReally2D(pG, m_orthoOffsetX*m_orthoScale + -actualSize.Width/2,
								m_orthoOffsetX*m_orthoScale + actualSize.Width/2,
								m_orthoOffsetY*m_orthoScale + -actualSize.Height/2,
								m_orthoOffsetY*m_orthoScale + actualSize.Height/2);

		proj = LDraw::GetOrthoReally2D(	m_orthoOffsetX -actualSize.Width/2 / m_orthoScale,
													m_orthoOffsetX + actualSize.Width/2 / m_orthoScale,
													m_orthoOffsetY + -actualSize.Height/2 / m_orthoScale,
													m_orthoOffsetY + actualSize.Height/2 / m_orthoScale);

		pG->MatrixMode(GL_MODELVIEW);
		pG->LoadIdentity();

		model = LDraw::matrix4f::getIdentity();

		if (true)
		{
			double left = -actualSize.Width/2 + m_orthoOffsetX*m_orthoScale;
			double right = actualSize.Width/2 + m_orthoOffsetX*m_orthoScale;
			double bottom = -actualSize.Height/2 + m_orthoOffsetY*m_orthoScale;
			double top = actualSize.Height/2 + m_orthoOffsetY*m_orthoScale;

			pG->glBegin(GL_LINES);
			pG->glColorf(0.45f, 0.45f, 0.45f);

			double spacing = 10 * m_orthoScale;

			{
				int n;
				int x;
				
				n = left / spacing;
				x = 0;
				for (x = 0; x >= n; x--)
				{
					pG->glVertexf(x*spacing, top, 0);
					pG->glVertexf(x*spacing, bottom, 0);
				}

				n = right / spacing;
				x = 0;
				for (x = 0; x <= n; x++)
				{
					pG->glVertexf(x*spacing, top, 0);
					pG->glVertexf(x*spacing, bottom, 0);
				}
			}

			{
				int n;
				int y;
				
				n = bottom / spacing;
				y = 0;
				for (y = 0; y >= n; y--)
				{
					pG->glVertexf(left, y*spacing, 0);
					pG->glVertexf(right, y*spacing, 0);
				}

				n = top / spacing;
				y = 0;
				for (y = 0; y <= n; y++)
				{
					pG->glVertexf(left, y*spacing, 0);
					pG->glVertexf(right, y*spacing, 0);
				}
			}

			{
				switch (m_display)
				{
					case 1:	// front
					{
						// x
						pG->glColorf(1, 0, 0);
						pG->glVertexf(left, 0, 0);
						pG->glVertexf(right, 0, 0);

						// y
						pG->glColorf(0, 1, 0);
						pG->glVertexf(0, bottom, 0);
						pG->glVertexf(0, top, 0);
					}
					break;

					case 2:	// top
					{
						// x
						pG->glColorf(1, 0, 0);
						pG->glVertexf(left, 0, 0);
						pG->glVertexf(right, 0, 0);

						// z
						pG->glColorf(0, 0, 1);
						pG->glVertexf(0, bottom, 0);
						pG->glVertexf(0, top, 0);
					}
					break;

					case 3:	// left
					{
						// z
						pG->glColorf(0, 0, 1);
						pG->glVertexf(left, 0, 0);
						pG->glVertexf(right, 0, 0);

						// y
						pG->glColorf(0, 1, 0);
						pG->glVertexf(0, bottom, 0);
						pG->glVertexf(0, top, 0);
					}
					break;
				}
			}

			pG->glEnd();

			pG->glColorf(0.0f, 0.0f, 0.0f);
		}

		pG->MatrixMode(GL_PROJECTION);
		pG->LoadIdentity();

		OrthoReally2D(pG, m_orthoOffsetX + -actualSize.Width/2 / m_orthoScale,
								m_orthoOffsetX + actualSize.Width/2 / m_orthoScale,
								m_orthoOffsetY + -actualSize.Height/2 / m_orthoScale,
								m_orthoOffsetY + actualSize.Height/2 / m_orthoScale);

		pG->MatrixMode(GL_MODELVIEW);

		if (m_display == 1)
		{
			//pG->glRotatef(0, 0, 0, 0);
		}
		else if (m_display == 2)
		{
			pG->glRotatef(90, 1, 0, 0);
			model *= LDraw::matrix4f::getRotate(90, LDraw::vector3f(1, 0, 0));
		}
		else if (m_display == 3)
		{
			pG->glRotatef(90, 0, 1, 0);
			model *= LDraw::matrix4f::getRotate(90, LDraw::vector3f(0, 1, 0));
		}

		/*
		if (false)
		{
			pG->glPushMatrix();
			{
				pG->glTranslatef(m_document->m_position[0], m_document->m_position[1], m_document->m_position[2]);

				LDraw::vector3f norientation = m_document->m_orientation.m_axis;
				norientation.normalize();
				pG->glRotate(gmDegrees(m_document->m_orientation.m_angle), norientation);
			}

			DrawCamera(pG);

			pG->glPopMatrix();
		}
		*/
	}

	if (m_shading != Shading_None)
	{
		pG->Enable(GL_DEPTH_TEST);
	}

	if (m_shading != Shading_None)
	{
		for (int i = 0; i < m_document->m_lights.GetSize(); i++)
		{
			Light* light = m_document->m_lights[i];

			//float light_position[4] = { light->m_transformedLocation[0], light->m_transformedLocation[1], light->m_transformedLocation[2], 1/*positional*/};
			float light_position[4] = { light->m_location[0], light->m_location[1], light->m_location[2], 1/*positional*/};

			float ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
			float position[] = {0,0,20,1};
			float mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1};
			float mat_specular[] = {1.0f,1.0f,1.0f,1.0f};
			float mat_shininess[] = {50.0f};

			pG->Enable(GL_LIGHT0+i);
			pG->Lightfv(GL_LIGHT0+i, GL_POSITION, light_position);
			pG->Lightfv(GL_LIGHT0+i, GL_AMBIENT, ambient);
			pG->Lightfv(GL_LIGHT0+i, GL_DIFFUSE, mat_diffuse);
			pG->Lightfv(GL_LIGHT0+i, GL_SPECULAR , mat_specular);
		}
	}

	if (m_shading == None)
	{
	//	pG->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

//	pG->glEnable(GL_COLOR_MATERIAL);

	Deformer* pDeformer = new IdentityDeformer;

#if 0
	if (false && m_display == 4)
	{
		LDraw::vector3f o = LDraw::vector3f(0,0,0);

		LDraw::vector3f win2 = o.Project(model, proj, viewport);

		double win[3];
		double obj[3];

		/*
		LDraw::matrix4f m2 = LDraw::matrix4f::getRotate(45, LDraw::vector3f(1, 0, 0));
		m2 *= LDraw::matrix4f::getRotate(20, LDraw::vector3f(0, 1, 0));
		m2 *= LDraw::matrix4f::getTranslate(20, -30, 60);
		m2 *= LDraw::matrix4f::getScale(11, -20, 10);

		LDraw::matrix4f iproj = proj.getInverse();
//		LDraw::matrix4f iproj = proj.getInverse();

		LDraw::matrix4f m = m2 * proj;

		LDraw::matrix4f m3 = m * iproj;

		//ASSERT(m3.FuzzyEquals(m2));
		*/

		{

			double _model[16];
			_model[0] = ((float*)model)[0];
			_model[1] = ((float*)model)[1];
			_model[2] = ((float*)model)[2];
			_model[3] = ((float*)model)[3];
			_model[4] = ((float*)model)[4];
			_model[5] = ((float*)model)[5];
			_model[6] = ((float*)model)[6];
			_model[7] = ((float*)model)[7];
			_model[8] = ((float*)model)[8];
			_model[9] = ((float*)model)[9];
			_model[10] = ((float*)model)[10];
			_model[11] = ((float*)model)[11];
			_model[12] = ((float*)model)[12];
			_model[13] = ((float*)model)[13];
			_model[14] = ((float*)model)[14];
			_model[15] = ((float*)model)[15];

			double _proj[16];
			_proj[0] = ((float*)proj)[0];
			_proj[1] = ((float*)proj)[1];
			_proj[2] = ((float*)proj)[2];
			_proj[3] = ((float*)proj)[3];
			_proj[4] = ((float*)proj)[4];
			_proj[5] = ((float*)proj)[5];
			_proj[6] = ((float*)proj)[6];
			_proj[7] = ((float*)proj)[7];
			_proj[8] = ((float*)proj)[8];
			_proj[9] = ((float*)proj)[9];
			_proj[10] = ((float*)proj)[10];
			_proj[11] = ((float*)proj)[11];
			_proj[12] = ((float*)proj)[12];
			_proj[13] = ((float*)proj)[13];
			_proj[14] = ((float*)proj)[14];
			_proj[15] = ((float*)proj)[15];

			int _viewport[4];
			_viewport[0] = viewport[0];
			_viewport[1] = viewport[1];
			_viewport[2] = viewport[2];
			_viewport[3] = viewport[3];

			::gluProject(o[0], o[1], o[2], _model, _proj, _viewport, &win[0], &win[1], &win[2]);

			::gluUnProject(win[0], win[1], win[2], _model, _proj, _viewport, &obj[0], &obj[1], &obj[2]);
		}


		LDraw::vector3f obj2 = win2.UnProject(model, proj, viewport);
	}
#endif

	if (false)
	{
	//	pG->MatrixMode(GL_MODELVIEW);
	//	pG->LoadIdentity();
		pG->PushMatrix();

		{
			pG->PushMatrix();
			pG->glRotatef(45, 0, 0, 1);
		//	pG->glRotatef(23.5, 0, 0, 1);
		//	pG->glTranslatef(0, 5, 0);
			pG->glTranslatef(0, 0, 0);

			/*
			LDraw::matrix4f m(
			1, 0, 0, 0,
		   0, 1, 0, 20,
		   0, 0, 1, 0,
		   0, 0, 0, 1);
			*/

		//	LDraw::matrix4f m = LDraw::matrix4f::getTranslate(20, 0, 0);
		//	m *= LDraw::matrix4f::getScale(0.4, 0.4, 0.4);
		//	m *= LDraw::matrix4f::getRotate(45, LDraw::vector3f(0, 0, 1));

			//pG->glRotatef(45, 0, 0, 1);
			//pG->glMultMatrixf(m);

			LDraw::Cube(pG, 5, 5, 5,
				0, 0, 0);
			pG->PopMatrix();
		}
		pG->PopMatrix();
	}

	if (true)
	{
#if 1
		RenderObject(model, proj, viewport, m_document->m_object, pG, pDeformer);
	//	m_document->m_object->OnRender(pG);
#endif
	}

	//if (m_display == 4)
	{
		/*
		if (m_document->m_list)
		{
			pG->CallList(m_document->m_list);
		}
		*/
	}

#if 0
	pG->glBegin(GL_LINES);

	int i;
	for (i = 0; i < m_document->m_geometry->m_points.size()-1; i++)
	{
		pG->glVertex(m_document->m_geometry->m_points[i]);
		pG->glVertex(m_document->m_geometry->m_points[i+1]);
	}
	pG->glVertex(m_document->m_geometry->m_points[i]);
	pG->glVertex(m_document->m_geometry->m_points[0]);

	pG->glEnd();
#endif

	/*
	pG->glBegin(GL_LINES);

		pG->glColorf(1, 0, 0);
		pG->glVertexf(-90, 90, 0);

		pG->glColorf(0, 1, 0);
		pG->glVertexf(-90, 0, 45);

		pG->glColorf(0, 1, 0);
		pG->glVertexf(-90, 0, 45);

		pG->glColorf(0, 0, 1);
		pG->glVertexf(90, 0, 0);

		pG->glColorf(0, 0, 1);
		pG->glVertexf(90, 0, 0);

		pG->glColorf(1, 0, 0);
		pG->glVertexf(-90, 90, 0);

	pG->glEnd();
	*/

	/*
	pG->glBegin(GL_TRIANGLES);

		pG->glColorf(1, 0, 0);
		pG->glVertexf(-90, 90, 0);

		pG->glColorf(0, 1, 0);
		pG->glVertexf(-90, 0, 45);

		pG->glColorf(0, 0, 1);
		pG->glVertexf(90, 0, 0);

	pG->glEnd();
	*/

	/*
	pG->glBegin(GL_LINES);

		pG->glVertexf(-50, 0, 0);
		pG->glVertexf(50, 0, 0);

	pG->glEnd();
	*/

#if 0
	pG->m_stream << uint16(0);

	dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands.AddCommand(new LDraw::Render3DCommand(m_document->m_glState, list));
#endif

//	pG->Release();
	pG->ReleaseGraphics();

#if 0
	if (false)
	{
		double viewport[4] = {0, 0, actualSize.Width, actualSize.Height};

		double fovy = 45;
		double zNear = 0.5;
		double zFar = 1000.0;
		double aspect = actualSize.Width / actualSize.Height;

		LDraw::matrix4f proj;
		LDraw::matrix4f model;

#if 0
		if (m_display == 4)
		{
			proj = GetPerspective(fovy, aspect, zNear, zFar);

			{
				LDraw::vector3f norientation = m_document->m_orientation.m_axis;
				norientation.normalize();
			//	pG->glRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation);

			//	pG->glTranslatef(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]);

				model = LDraw::Matrix4::GetRotate(gmDegrees(m_document->m_orientation.m_angle), -norientation[0], -norientation[1], -norientation[2]);
				model = *LDraw::Matrix4::GetTranslate(-m_document->m_position[0], -m_document->m_position[1], -m_document->m_position[2]) * *model;
			}
		}
		else
#endif
		{
			model = LDraw::matrix4f::getIdentity();
			proj = LDraw::matrix4f::getIdentity();

			/*
			if (m_display == 1)
			{
				//pG->glRotatef(0, 0, 0, 0);
			}
			else if (m_display == 2)
			{
				proj = *LDraw::Matrix4::GetRotate(90, 1, 0, 0) * *proj;
			}
			else if (m_display == 3)
			{
				proj = *LDraw::Matrix4::GetRotate(90, 0, 1, 0) * *proj;
			}
			*/

		//	m_orthoOffsetX = -actualSize.Width/2;
		//	m_orthoOffsetY = -actualSize.Height/2;

			proj = LDraw::GetOrthoReally2D(	m_orthoOffsetX,
														m_orthoOffsetX + actualSize.Width,
														m_orthoOffsetY,
														m_orthoOffsetY + actualSize.Height);

			model = LDraw::matrix4f::getRotate(45, LDraw::vector3f(1, 0, 0));

			/*
			proj = LDraw::GetOrthoReally2D(	m_orthoOffsetX -actualSize.Width/2,
												m_orthoOffsetX + actualSize.Width/2,
												m_orthoOffsetY -actualSize.Height/2,
												m_orthoOffsetY + actualSize.Height/2);
*/
			/*
			proj = *LDraw::Matrix4::GetOrtho2D(	m_orthoOffsetX -actualSize.Width/2 / m_orthoScale,
																	m_orthoOffsetX + actualSize.Width/2 / m_orthoScale,
																	m_orthoOffsetY + -actualSize.Height/2 / m_orthoScale,
																	m_orthoOffsetY + actualSize.Height/2 / m_orthoScale) * *proj;
*/
			/*
			proj = LDraw::Matrix4::GetOrtho2D(	m_orthoOffsetX -actualSize.Width/2 / m_orthoScale,
																	m_orthoOffsetX + actualSize.Width/2 / m_orthoScale,
																	m_orthoOffsetY + -actualSize.Height/2 / m_orthoScale,
																	m_orthoOffsetY + actualSize.Height/2 / m_orthoScale);
*/
	}

	//	pG->gluPerspective(fovy, aspect, zNear, zFar);

		LDraw::vector3f obj2 = LDraw::vector3f(0,0,0);

		LDraw::vector3f obj = obj2.Project(model, proj, viewport);

		double win[3];
		//double obj[3];

		{

			double _model[16];
			_model[0] = ((float*)model)[0];
			_model[1] = ((float*)model)[1];
			_model[2] = ((float*)model)[2];
			_model[3] = ((float*)model)[3];
			_model[4] = ((float*)model)[4];
			_model[5] = ((float*)model)[5];
			_model[6] = ((float*)model)[6];
			_model[7] = ((float*)model)[7];
			_model[8] = ((float*)model)[8];
			_model[9] = ((float*)model)[9];
			_model[10] = ((float*)model)[10];
			_model[11] = ((float*)model)[11];
			_model[12] = ((float*)model)[12];
			_model[13] = ((float*)model)[13];
			_model[14] = ((float*)model)[14];
			_model[15] = ((float*)model)[15];

			double _proj[16];
			_proj[0] = ((float*)proj)[0];
			_proj[1] = ((float*)proj)[1];
			_proj[2] = ((float*)proj)[2];
			_proj[3] = ((float*)proj)[3];
			_proj[4] = ((float*)proj)[4];
			_proj[5] = ((float*)proj)[5];
			_proj[6] = ((float*)proj)[6];
			_proj[7] = ((float*)proj)[7];
			_proj[8] = ((float*)proj)[8];
			_proj[9] = ((float*)proj)[9];
			_proj[10] = ((float*)proj)[10];
			_proj[11] = ((float*)proj)[11];
			_proj[12] = ((float*)proj)[12];
			_proj[13] = ((float*)proj)[13];
			_proj[14] = ((float*)proj)[14];
			_proj[15] = ((float*)proj)[15];

			int _viewport[4];
			_viewport[0] = viewport[0];
			_viewport[1] = viewport[1];
			_viewport[2] = viewport[2];
			_viewport[3] = viewport[3];

			::gluProject(obj2[0], obj2[1], obj2[2], _model, _proj, _viewport, &win[0], &win[1], &win[2]);
		}

		float scale = 3.0f;
	//	float scale = 1;
		LDraw::vector3f xaxis = LDraw::vector3f(10*scale, 0, 0).Project(model, proj, viewport);
		LDraw::vector3f yaxis = LDraw::vector3f(0, 10*scale, 0).Project(model, proj, viewport);
		LDraw::vector3f zaxis = LDraw::vector3f(0, 0, 10*scale).Project(model, proj, viewport);

		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(255, 0, 0), 2), obj[0], actualSize.Height-obj[1], (xaxis)[0], actualSize.Height-(xaxis)[1]);
		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0, 255, 0), 2), obj[0], actualSize.Height-obj[1], (yaxis)[0], actualSize.Height-(yaxis)[1]);
		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0, 0, 255), 2), obj[0], actualSize.Height-obj[1], (zaxis)[0], actualSize.Height-(zaxis)[1]);

		{
			LDraw::Font* font = GetFont();
			LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));

			char buf[32];

			sprintf(buf, "X:%.2f", obj[0]);
			pGraphics->DrawString(new StringA(buf), font, LDraw::PointF(20, actualSize.Height - font->GetSize()), brush);

			sprintf(buf, "Y:%.2f", obj[1]);
			pGraphics->DrawString(new StringA(buf), font, LDraw::PointF(100, actualSize.Height - font->GetSize()), brush);

			sprintf(buf, "Z:%.2f", obj[2]);
			pGraphics->DrawString(new StringA(buf), font, LDraw::PointF(180, actualSize.Height - font->GetSize()), brush);
		}
	//	pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(255, 0, 0), 2), obj[0], obj[1], (xaxis)[0], (xaxis)[1]);
	//	pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0, 255, 0), 2), obj[0], obj[1], (yaxis)[0], (yaxis)[1]);
	//	pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0, 0, 255), 2), obj[0], obj[1], (zaxis)[0], (zaxis)[1]);

//		pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(0, 0, 0)), 0, 0, 10, 10);
	}
#endif

	if (m_display != 4)
	{
		LDraw::Font* font = GetFont();

		LDraw::Color xcolor;
		LDraw::Color ycolor;

		static __live_object_ptr<StringA> X_str = ASTR("X");
		static __live_object_ptr<StringA> Y_str = ASTR("Y");
		static __live_object_ptr<StringA> Z_str = ASTR("Z");

		StringA* xstring;
		StringA* ystring;

		switch (m_display)
		{
		case 1:
			{
				xcolor = LDraw::Color(255, 0, 0);
				ycolor = LDraw::Color(0, 255, 0);
				xstring = X_str;
				ystring = Y_str;
			}
			break;

		case 2:
			{
				xcolor = LDraw::Color(255, 0, 0);
				ycolor = LDraw::Color(0, 0, 255);
				xstring = X_str;
				ystring = Z_str;
			}
			break;

		case 3:
			{
				xcolor = LDraw::Color(0, 0, 255);
				ycolor = LDraw::Color(0, 255, 0);
				xstring = Z_str;
				ystring = Y_str;
			}
			break;
		}

		// shadow
	//	LDraw::Matrix transform = pGraphics->GetTransform();
	//	LDraw::PointF point = transform.Transform(LDraw::PointF(0, 0));
	//	pGraphics->TranslateTransform(point.X - (int)point.X, point.Y - (int)point.Y);

		pGraphics->TranslateTransform(2.5, -4.5);

		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0,0,0), 1), 2, (int)actualSize.Height - 1, 2+12, (int)actualSize.Height - 1);
		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0,0,0), 1), 1, (int)actualSize.Height - 1, 1, (int)actualSize.Height - 1 - 12);

		pGraphics->DrawString(xstring, font, LDraw::PointF(font->GetSize(), actualSize.Height - font->GetSize()), new LDraw::SolidBrush(LDraw::Color(0,0,0)));
		pGraphics->DrawString(ystring, font, LDraw::PointF(0, actualSize.Height - font->GetSize()*2), new LDraw::SolidBrush(LDraw::Color(0,0,0)));

		// colored
		pGraphics->TranslateTransform(-1,-1);
		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(xcolor), 1), 2, (int)actualSize.Height - 1, 2+12, (int)actualSize.Height - 1);
		pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(ycolor), 1), 1, (int)actualSize.Height - 1, 1, (int)actualSize.Height - 1 - 12);

		pGraphics->DrawString(xstring, font, LDraw::PointF(font->GetSize(), actualSize.Height - font->GetSize()), new LDraw::SolidBrush(xcolor));
		pGraphics->DrawString(ystring, font, LDraw::PointF(0, actualSize.Height - font->GetSize()*2), new LDraw::SolidBrush(ycolor));
	}

	if (m_dragging)
	{
		LDraw::Font* font = GetFont();
		LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));

		char buf[32];

		std::sprintf(buf, "X:%.2f", m_dragX);
		pGraphics->DrawString(new StringA(string_copy(buf)), font, LDraw::PointF(20, actualSize.Height - font->GetSize()), brush);

		std::sprintf(buf, "Y:%.2f", m_dragY);
		pGraphics->DrawString(new StringA(string_copy(buf)), font, LDraw::PointF(100, actualSize.Height - font->GetSize()), brush);

		std::sprintf(buf, "Z:%.2f", m_dragZ);
		pGraphics->DrawString(new StringA(string_copy(buf)), font, LDraw::PointF(180, actualSize.Height - font->GetSize()), brush);
	}

	ASSERT(m_document->m_glState->m_modelviewMatrixStack.size() == 0);
	ASSERT(m_document->m_glState->m_projectionMatrixStack.size() == 0);
	ASSERT(m_document->m_glState->m_enableMaskStack.size() == 0);
//	ASSERT(pG->m_attribMaskStack.size() == 0);
#endif
}

void View3D::RenderObject(LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], Camera* object, LDraw::Graphics3D* pG, Deformer* pDeformer)
{
	ASSERT(0);
#if 0
	pG->PushMatrix();
	{
		LDraw::vector3f position = object->get_Position();

		pG->glTranslatef(position[0], position[1], position[2]);

		/*
		LDraw::vector3f norientation = object->get_Orientation().m_axis;
		norientation.normalize();
		pG->glRotate(gmDegrees(object->get_Orientation().m_angle), norientation);
		*/
	}

	LDraw::SizeD actualSize = get_ActualSize();

	double fovy = object->get_FieldOfView();
	double zNear = 0.5;
	double zFar = zNear + 2.0;
	double aspect = actualSize.Width / actualSize.Height;

	double ntop = zNear * tan( fovy * M_PI / 360.0 );
	double nbottom = -ntop;
	double nleft = nbottom * aspect;
	double nright = ntop * aspect;

	double ftop = zFar * tan( fovy * M_PI / 360.0 );
	double fbottom = -ftop;
	double fleft = fbottom * aspect;
	double fright = ftop * aspect;

	/*
	ntop = -1+0.001;
	nbottom = 1-0.001;
	nleft = -1+0.001;
	nright = 1-0.001;
	*/
	/*
	nleft = -actualSize.Width/2;
	nright = actualSize.Width/2;
	nbottom = -actualSize.Height/2;
	ntop = actualSize.Height/2;
	*/

	/*
	nleft *= actualSize.Width/2;
	nright *= actualSize.Width/2;
	nbottom *= actualSize.Height/2;
	ntop *= actualSize.Height/2;

	fleft *= actualSize.Width/2;
	fright *= actualSize.Width/2;
	fbottom *= actualSize.Height/2;
	ftop *= actualSize.Height/2;
	*/

//	zFar -= zNear;
//	zNear -= zNear;
	{
		pG->glBegin(GL_LINE_STRIP);

			pG->glVertexf(nleft, nbottom, -zNear);
			pG->glVertexf(nleft, ntop, -zNear);
			pG->glVertexf(nright, ntop, -zNear);
			pG->glVertexf(nright, nbottom, -zNear);
			pG->glVertexf(nleft, nbottom, -zNear);

		pG->glEnd();
	}

	{
		pG->glBegin(GL_LINES);

			pG->glVertexf(nleft, nbottom, -zNear);
			pG->glVertexf(fleft, fbottom, -zFar);

			pG->glVertexf(nleft, ntop, -zNear);
			pG->glVertexf(fleft, ftop, -zFar);

			pG->glVertexf(nright, ntop, -zNear);
			pG->glVertexf(fright, ftop, -zFar);

			pG->glVertexf(nright, nbottom, -zNear);
			pG->glVertexf(fright, fbottom, -zFar);

		pG->glEnd();
	}

	{
		pG->glBegin(GL_LINE_STRIP);

			pG->glVertexf(fleft, fbottom, -zFar);
			pG->glVertexf(fleft, ftop, -zFar);
			pG->glVertexf(fright, ftop, -zFar);
			pG->glVertexf(fright, fbottom, -zFar);
			pG->glVertexf(fleft, fbottom, -zFar);

		pG->glEnd();
	}

	pG->PopMatrix();
#endif
}

void Light::OnRender(LDraw::Graphics3D* pGraphics, int mode, Deformer* pDeformer)
{
}

void View3D::RenderObject(LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], Object3D* object, LDraw::Graphics3D* pG, Deformer* pDeformer)
{
	ASSERT(0);
#if 0
	//pG->m_matrix[0] = pG->m_matrix[0];

	if (Group* group = dynamic_cast<Group*>(object))
	{
		/*
		_Transform3D* transform = group->get_Transform();
		if (transform)
		{
			LDraw::Matrix4 matrix = transform->get_Value();
			float m[16];
			matrix.Get(m);

			pG->glMultMatrixf(m);

			model = matrix * model;
		}
		*/
		{
		//	group->m_transform = LDraw::Matrix4::GetIdentity();

		//	float m[16];
			/* = {1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1};
								*/


			//group->m_transform->Get(m);

			/*
			ASSERT(m[0] == 1);
			ASSERT(m[1] == 0);
			ASSERT(m[2] == 0);
			ASSERT(m[3] == 0);

			ASSERT(m[4] == 0);
			ASSERT(m[5] == 1);
			ASSERT(m[6] == 0);
			ASSERT(m[7] == 0);

			ASSERT(m[8] == 0);
			ASSERT(m[9] == 0);
			ASSERT(m[10] == 1);
			ASSERT(m[11] == 0);

			ASSERT(m[12] == 0);
			ASSERT(m[13] == 0);
			ASSERT(m[14] == 0);
			ASSERT(m[15] == 1);
			*/

			pG->PushMatrix();
			pG->MultMatrixf((float*)group->m_transform->m_matrix);
			LDraw::matrix4f model2 = model * group->m_transform->m_matrix;

			for (int i = 0; i < group->m_Children->m_items.GetSize(); i++)
			{
				RenderObject(model2, proj, viewport, group->m_Children->m_items[i], pG, pDeformer);
			}
			pG->PopMatrix();
		}

		{
		//	float m[16];
		//	pG->glGetFloatv(GL_MODELVIEW_MATRIX, m);

		//	LDraw::Matrix4 model(m);

			for (int i = 0; i < group->m_references.GetSize(); i++)
			{
				Reference* pRef = group->m_references[i];
				Bone* pBone = dynamic_cast<Bone*>(pRef->m_referencing);
				if (pBone)
				{
					pG->PushMatrix();
					pG->PushAttrib(GL_ENABLE_BIT);
					pG->Disable(GL_DEPTH_TEST);
					pG->Disable(GL_LIGHTING);

					pG->LoadIdentity();

				//	LDraw::Matrix4 finalMatrix = pBone->m_matrixOffset * group->m_combinedTransform;

					LDraw::matrix4f model_1 = model;
					LDraw::matrix4f model_2 = model * group->m_transform->m_matrix;

				//	model_1 = pBone->m_matrixOffset.GetInverse() * model_1;
				//	model_2 = pBone->m_matrixOffset.GetInverse() * model_2;

					LDraw::vector3f v0 = model_1.transform(LDraw::vector3f(0,0,0));
					LDraw::vector3f v1 = model_2.transform(LDraw::vector3f(0,0,0));

				//	LDraw::vector3f v0 = group->m_parentCombinedTransform.Transform(LDraw::vector3f(0,0,0));
				//	LDraw::vector3f v1 = group->m_combinedTransform.Transform(LDraw::vector3f(0,0,0));

					//LDraw::vector3f v = model.Transform(LDraw::vector3f(0,0,0));

					pG->glColorf(1, 0, 0);
					pG->glBegin(GL_LINES);
						pG->glVertex(v0);
						pG->glVertex(v1);
					pG->glEnd();

					/*
					float matrixoffset[16];
					pBone->m_matrixOffset.Get(matrixoffset);

					pG->glMultMatrixf(matrixoffset);

					gluSphere(pG, 5, 20, 20);
					*/

					pG->PopAttrib();
					pG->PopMatrix();
				}
			}
		}

	}
	else if (Light* shape = dynamic_cast<Light*>(object))
	{
		if (true)
		{
		LDraw::matrix4f model2 = model * object->m_transform->m_matrix;

		LDraw::SizeD actualSize = get_ActualSize();

		pG->PushMatrix();
		pG->LoadIdentity();

		pG->MatrixMode(GL_PROJECTION);
		pG->PushMatrix();
		pG->LoadIdentity();

		pG->Ortho2D(	0*m_orthoOffsetX/m_orthoScale,
					0*m_orthoOffsetX/m_orthoScale + actualSize.Width/* / m_orthoScale*/,
					
					0*m_orthoOffsetY/m_orthoScale/* / m_orthoScale*/,
					0*m_orthoOffsetY/m_orthoScale + actualSize.Height
					);

		pG->MatrixMode(GL_MODELVIEW);
	//	pG->glPushMatrix();
	//	pG->glLoadIdentity();

#if 0
		pG->gluOrtho2D(	0*m_orthoOffsetX/m_orthoScale - actualSize.Width/2,
					0*m_orthoOffsetX/m_orthoScale + actualSize.Width/2/* / m_orthoScale*/,
					
					0*m_orthoOffsetY/m_orthoScale - actualSize.Height/2/* / m_orthoScale*/,
					0*m_orthoOffsetY/m_orthoScale + actualSize.Height/2
					);
#endif

		LDraw::vector3f c = LDraw::vector3f(0,0,0).Project(model2, proj, viewport);

		pG->PushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
		pG->Disable(GL_LIGHTING);
		if (shape->m_bSelected)
			pG->glColorf(1.0f, 0.6f, 1.0f);
	
		//	pG->glPushMatrix();
	//	pG->glTranslatef(c[0], c[1], 0);
	//	Cube(pG, 5, 5, 5);
	//	pG->glPopMatrix();
	
		LDraw::Circle(pG, c[0], c[1], 8);

		pG->PopAttrib();

		shape->OnRender(pG, m_shading, pDeformer);

		pG->PopMatrix();
		pG->MatrixMode(GL_PROJECTION);
		pG->PopMatrix();
		pG->MatrixMode(GL_MODELVIEW);

		//pG->glPopMatrix();
		}
	}
	else if (Camera* shape = dynamic_cast<Camera*>(object))
	{
		pG->PushMatrix();
		pG->MultMatrixf(object->m_transform->m_matrix);

		RenderObject(model * shape->m_transform->m_matrix, proj, viewport, shape, pG, pDeformer);

		pG->PopMatrix();
	}
	else if (Shape* shape = dynamic_cast<Shape*>(object))
	{
		pG->PushMatrix();
		pG->MultMatrixf(object->m_transform->m_matrix);
	//	model = *object->m_transform * *model;
	//	ASSERT(!model->m_matrix.isSingular());

		pG->MultMatrixf(shape->m_geometryTransform);

		LDraw::matrix4f model2 = model * object->m_transform->m_matrix;

		if (m_shading != Shading_None)
		{
			if (false)
			{
				pG->PushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);

				pG->Disable(GL_LIGHTING);
				pG->Enable(GL_STENCIL_TEST);
				pG->Enable(GL_DEPTH_TEST);
				pG->ColorMask(true, true, true, true);

				// outline
				pG->StencilFunc(GL_ALWAYS, 1, 1);
				pG->StencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
			//	pG->glColorMask(false, false, false, false);
				pG->glColorf(0, 0, 0);
				pG->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				shape->OnRender(pG, m_shading, pDeformer);

				// fill
				pG->StencilFunc(GL_EQUAL, 0, 1);
				pG->StencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
				pG->glColorf(0.5f, 0.5f, 0.5f);
				pG->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				shape->OnRender(pG, m_shading, pDeformer);

				// outline
				pG->StencilFunc(GL_ALWAYS, 0, 1);
				pG->StencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
				//pG->glColorf(0, 0, 0);
				pG->ColorMask(false, false, false, false);
				pG->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				shape->OnRender(pG, m_shading, pDeformer);

				// revert
				pG->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				pG->ColorMask(true, true, true, true);
				pG->Disable(GL_STENCIL_TEST);

				pG->PopAttrib();
			}
#if 0
			else if (true)
			{
				pG->Disable(GL_LIGHTING);
				pG->Enable(GL_STENCIL_TEST);
				pG->Enable(GL_DEPTH_TEST);

				// outline
				pG->StencilFunc(GL_ALWAYS, 0, 1);
				pG->StencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
				pG->glColorf(0, 0, 0);

				pG->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				shape->OnRender(pG);

				// fill
				pG->StencilFunc(GL_EQUAL, 0, 1);
				pG->StencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
				pG->glColorf(0.6, 0.6, 0.6);

				pG->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				shape->OnRender(pG, pDeformer);

				// outline
				pG->StencilFunc(GL_ALWAYS, 0, 1);
				pG->StencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
				pG->glColorf(0, 0, 0);

				pG->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				shape->OnRender(pG, pDeformer);

				pG->Disable(GL_STENCIL_TEST);
				pG->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				//pG->
			}
			else
			{
				pG->Disable(GL_LIGHTING);
				 pG->glColorf(.7f, .7f, .7f);

				 pG->Enable(GL_STENCIL_TEST);
				 pG->StencilFunc(GL_ALWAYS, 0, 0); /* clear stencil for this object */

				 //glCallList(dlist); /* draw filled object in depth buffer */
				 pG->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				shape->OnRender(pG, pDeformer);

				 pG->lEnable(GL_LIGHTING);
				// if(tex2d)
				//	glEnable(GL_TEXTURE_2D);

				 pG->ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); /* turn off color */
				 pG->Disable(GL_DEPTH_TEST); /* turn off depth */
				 pG->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				 pG->StencilFunc(GL_ALWAYS, 1, 1);
				 pG->StencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

				 //glCallList(dlist); /* draw lines into stencil buffer */
				shape->OnRender(pG);

				 pG->StencilFunc(GL_EQUAL, 1 , 1);
				 pG->Enable(GL_DEPTH_TEST);
				 pG->DepthFunc(GL_LEQUAL);
				 pG->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				 pG->ColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

				 //glCallList(dlist); /* use lines in stencil to stencil out solid pgons */
				shape->OnRender(pG);

				 /* clean up state */
				 pG->Disable(GL_STENCIL_TEST);
				 pG->DepthFunc(GL_LESS);
			}
#endif
			else
			{
			//	pG->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				shape->OnRender(pG, m_shading, pDeformer);
			//	pG->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
		else
		{
			pG->PushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);

			if (shape->m_bSelected && m_document->m_objectMode == Mode_Model)
			{
				pG->Disable(GL_LIGHTING);
				pG->glColorf(1.0f, 0.6f, 1.0f);
			}

			if (true)
			{

				IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(shape->get_Geometry());

				if (faceset)
				{
					pG->glBegin(GL_LINES);

					uint nedges = faceset->m_edges.GetSize();

					for (uint i = 0; i < nedges; i++)
					{
						const Edge& edge = faceset->m_edges[i];

						LDraw::vector3f v0 = faceset->m_transformedVertices[edge.v[0]];
						LDraw::vector3f v1 = faceset->m_transformedVertices[edge.v[1]];

						if (shape->m_bSelected)
						{
							if (shape->m_selectedObject->IsVertexSelected(edge.v[0]))
								pG->glColorf(1,1,0);
							else
								pG->glColorf(0,0,0);
						}

						pG->glVertex(v0);

						if (shape->m_bSelected)
						{
							if (shape->m_selectedObject->IsVertexSelected(edge.v[1]))
								pG->glColorf(1,1,0);
							else
								pG->glColorf(0,0,0);
						}

						pG->glVertex(v1);
					}

					pG->glEnd();
				}
			}
			else
			{
				pG->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				shape->OnRender(pG, m_shading, pDeformer);
				pG->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			pG->PopAttrib();
		}

		if (shape->m_bSelected)
		{
			// Draw face normals

			IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(shape->get_Geometry());
			if (faceset)
			{
			//	Int32Collection* pointindices = faceset->get_PointIndices();
				//Int32Collection* normalindices = faceset->get_NormalIndices();
				Point3DfCollection* points = faceset->get_Points();
			//	Point3DCollection* normals = faceset->get_Normals();

				unsigned int nfaces = faceset->m_faces.GetSize();//normals->m_items.size();

				float length = 0.2f;

				pG->PushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
				pG->Disable(GL_LIGHTING);
				pG->glColorf(0.5f, 0.5f, 1.0f);

				for (int i = 0; i < nfaces; i++)
				{
					const Face& face = faceset->m_faces[i];

				//	int index0 = pointindices->GetItem(i*3+0);
				//	int index1 = pointindices->GetItem(i*3+1);
				//	int index2 = pointindices->GetItem(i*3+2);
					uint index0 = faceset->m_edges[face.m_edges[0].GetIndex()].v[face.m_edges[0].IsBackward()];
					uint index1 = faceset->m_edges[face.m_edges[1].GetIndex()].v[face.m_edges[1].IsBackward()];
					uint index2 = faceset->m_edges[face.m_edges[2].GetIndex()].v[face.m_edges[2].IsBackward()];

					LDraw::vector3f v0 = points->m_items[index0];
					LDraw::vector3f v1 = points->m_items[index1];
					LDraw::vector3f v2 = points->m_items[index2];
					LDraw::vector3f normal = faceset->m_faceNormals[i];

					// TODO, calculate triangle median

					LDraw::vector3f c = v0 + ((v1+(v2-v1)/2)-v0)/2;

					pG->glBegin(GL_LINES);
						pG->glVertex(c);
						pG->glVertex(c + normal*length);
					pG->glEnd();
				}

				pG->PopAttrib();
			}
		}

		if (m_document->m_objectMode == Mode_Points && shape->m_bSelected)
		{
			IndexedFaceSet* faceset = dynamic_cast<IndexedFaceSet*>(shape->get_Geometry());
			if (faceset)
			{
				Point3DfCollection* points = faceset->get_Points();

				pG->PushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);

				LDraw::SizeD actualSize = get_ActualSize();

			//	float projm[16];
			//	pG->glGetFloatv(GL_PROJECTION_MATRIX, projm);

				pG->Disable(GL_DEPTH_TEST);

				pG->MatrixMode(GL_PROJECTION);
				pG->PushMatrix();
				pG->LoadIdentity();

			//	pG->glOrtho(-actualSize.left
				pG->Ortho2D(	0*m_orthoOffsetX/m_orthoScale,
							0*m_orthoOffsetX/m_orthoScale + actualSize.Width/* / m_orthoScale*/,
							
							0*m_orthoOffsetY/m_orthoScale/* / m_orthoScale*/,
							0*m_orthoOffsetY/m_orthoScale + actualSize.Height
							);

				pG->MatrixMode(GL_MODELVIEW);
				pG->PushMatrix();
				pG->LoadIdentity();

				pG->Disable(GL_LIGHTING);

				pG->glBegin(GL_QUADS);

			//	LDraw::Matrix4 model = LDraw::Matrix4::GetIdentity();

				unsigned int npoints = points->GetCount();

				for (unsigned int i = 0; i < npoints; i++)
				{
					//int index = shape->m_selectedObject->m_points[i];

					LDraw::vector3f v = points->GetItem(i);
					v = v.Project(model2, proj, viewport);

					if (shape->m_selectedObject->m_vertexSelected.GetSize() > i && shape->m_selectedObject->m_vertexSelected[i])
						pG->glColorf(1.0f, 1.0f, 0.0f);
					else
						pG->glColorf(0.9f, 0.4f, 0.9f);

					pG->glVertexf(v[0]-1, v[1]-1, 0);
					pG->glVertexf(v[0]+2, v[1]-1, 0);
					pG->glVertexf(v[0]+2, v[1]+2, 0);
					pG->glVertexf(v[0]-1, v[1]+2, 0);
				}

				/*
				for (int i = 0; i < shape->m_selectedObject->m_points.GetSize(); i++)
				{
					int index = shape->m_selectedObject->m_points[i];

					LDraw::vector3f v = points->m_items[index];
					v = v.Project(model, proj, viewport);

					pG->glVertexf(v[0]-3, v[1]-3, 0);
					pG->glVertexf(v[0]+3, v[1]-3, 0);
					pG->glVertexf(v[0]+3, v[1]+3, 0);
					pG->glVertexf(v[0]-3, v[1]+3, 0);
				}
				*/

				pG->glEnd();

				pG->PopMatrix();

				pG->MatrixMode(GL_PROJECTION);
				pG->PopMatrix();

				pG->MatrixMode(GL_MODELVIEW);

				pG->PopAttrib();
			}
		}

		pG->PopMatrix();
	}

	{
		Object3D* shape = object;

		if (shape->m_bSelected)
		{
			pG->PushMatrix();
			pG->MultMatrixf(object->m_transform->m_matrix);
			pG->glTranslate(shape->m_selectedObject->m_pivotPoint);

			pG->PushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LINE_BIT);

			float scale = 0.05f;	// TODO, calculate this based on zoom

			float len = 10;

			uint32 mask[32] =
			{
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
				0xaaaaaaaa,
				0x55555555,
			};

			pG->Disable(GL_LIGHTING);
			pG->LineStipple(1, 0xaaaa);

			pG->PolygonStipple((uint8*)mask);

			if (true)
			{
				pG->glColorf(1.0, 0, 0);	// red
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
					{
						pG->Disable(GL_DEPTH_TEST);
						pG->Enable(GL_LINE_STIPPLE);
						pG->Enable(GL_POLYGON_STIPPLE);
					}
					else
					{
						pG->Enable(GL_DEPTH_TEST);
						pG->Disable(GL_LINE_STIPPLE);
						pG->Disable(GL_POLYGON_STIPPLE);
					}

					pG->glBegin(GL_LINES);
						pG->glVertexf(0, 0, 0);
						pG->glVertexf(len*scale, 0, 0);
					pG->glEnd();

					if (m_transformMode & 1)	// Translate
					{
						pG->PushMatrix();
						pG->glTranslatef(len*scale, 0, 0);
						pG->glRotatef(90, 0, 1, 0);
						LDraw::gluCylinder(pG, 1.5*scale/*base*/, 0/*top*/, 5*scale/*height*/, 8, 8);
						pG->PopMatrix();
					}

					if (m_transformMode & 2)	// Scale
					{
						pG->PushMatrix();
						pG->glTranslatef(len*scale, 0, 0);
						pG->glRotatef(90, 0, 1, 0);
						LDraw::Cube(pG, 1*scale, 1*scale, 1*scale);
						pG->PopMatrix();
					}
				}
			}

			if (true)
			{
				pG->glColorf(0.0, 1.0, 0);	// blue
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
					{
						pG->Disable(GL_DEPTH_TEST);
						pG->Enable(GL_LINE_STIPPLE);
						pG->Enable(GL_POLYGON_STIPPLE);
					}
					else
					{
						pG->Enable(GL_DEPTH_TEST);
						pG->Disable(GL_LINE_STIPPLE);
						pG->Disable(GL_POLYGON_STIPPLE);
					}

					pG->glBegin(GL_LINES);
						pG->glVertexf(0, 0, 0);
						pG->glVertexf(0, len*scale, 0);
					pG->glEnd();

					if (m_transformMode & 1)	// Translate
					{
						pG->PushMatrix();
						pG->glTranslatef(0, len*scale, 0);
						pG->glRotatef(-90, 1, 0, 0);
						LDraw::gluCylinder(pG, 1.5*scale/*base*/, 0/*top*/, 5*scale/*height*/, 8, 8);
						pG->PopMatrix();
					}

					if (m_transformMode & 2)	// Scale
					{
						pG->PushMatrix();
						pG->glTranslatef(0, len*scale, 0);
						pG->glRotatef(-90, 1, 0, 0);
						LDraw::Cube(pG, 1*scale, 1*scale, 1*scale);
						pG->PopMatrix();
					}
				}
			}

			if (true)
			{
				pG->glColorf(0, 0, 1.0);	// green
				
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
					{
						pG->Disable(GL_DEPTH_TEST);
						pG->Enable(GL_LINE_STIPPLE);
						pG->Enable(GL_POLYGON_STIPPLE);
					}
					else
					{
						pG->Enable(GL_DEPTH_TEST);
						pG->Disable(GL_LINE_STIPPLE);
						pG->Disable(GL_POLYGON_STIPPLE);
					}
					pG->glBegin(GL_LINES);
						pG->glVertexf(0, 0, 0);
						pG->glVertexf(0, 0, len*scale);
					pG->glEnd();

					if (m_transformMode & 1)	// Translate
					{
						pG->PushMatrix();
						pG->glTranslatef(0, 0, len*scale);
					//	pG->glRotatef(-90, 1, 0, 0);
						LDraw::gluCylinder(pG, 1.5*scale/*base*/, 0/*top*/, 5*scale/*height*/, 8, 8);
						pG->PopMatrix();
					}

					if (m_transformMode & 2)	// Scale
					{
						pG->PushMatrix();
						pG->glTranslatef(0, 0, len*scale);
					//	pG->glRotatef(-90, 1, 0, 0);
						LDraw::Cube(pG, 1*scale, 1*scale, 1*scale);
						pG->PopMatrix();
					}
				}
			}

			pG->PopMatrix();

			if (m_transformMode & 4)	// Rotate
			{
				LDraw::SizeD actualSize = get_ActualSize();

				pG->glColorf(1.0, 1.0, 1.0);

				pG->MatrixMode(GL_PROJECTION);
				pG->PushMatrix();
				pG->LoadIdentity();

				pG->Ortho2D(	0*m_orthoOffsetX/m_orthoScale,
							0*m_orthoOffsetX/m_orthoScale + actualSize.Width/* / m_orthoScale*/,
							
							0*m_orthoOffsetY/m_orthoScale/* / m_orthoScale*/,
							0*m_orthoOffsetY/m_orthoScale + actualSize.Height
							);

				pG->MatrixMode(GL_MODELVIEW);
				pG->PushMatrix();
				pG->LoadIdentity();

				LDraw::matrix4f model2 = model * object->m_transform->m_matrix;

				LDraw::vector3f c = LDraw::vector3f(0,0,0).Project(model2, proj, viewport);

				LDraw::Circle(pG, c[0], c[1], 50, 64);

				pG->PopMatrix();
				pG->MatrixMode(GL_PROJECTION);
				pG->PopMatrix();
				pG->MatrixMode(GL_MODELVIEW);
			}

		//	pG->glColorf(0,0,0);
		//	pG->glDisable(GL_LINE_STIPPLE);

			pG->PopAttrib();
		}
	}
#endif
}

TexturePreview::TexturePreview()
{
	m_texture = NULL;
	m_bitmap = NULL;
}

void TexturePreview::OnRender(Graphics* graphics)
{
	LDraw::SizeD actualSize = get_ActualSize();

	uint bitmapWidth = ceil(actualSize.Width);
	uint bitmapHeight = ceil(actualSize.Height);

	if (m_bitmap == NULL || m_bitmap->GetWidth() != bitmapWidth || m_bitmap->GetHeight() != bitmapHeight)
	{
		if (m_bitmap)
		{
			delete m_bitmap;
		}

		m_bitmap = new LDraw::Bitmap(bitmapWidth, bitmapHeight, LDraw::PixelFormat_t::RGB_24);

		LDraw::BitmapData bitmapdata;
		m_bitmap->LockBits(NULL, LDraw::ImageLockModeWrite, &bitmapdata);

		for (uint y = 0; y < bitmapHeight; y++)
		{
			LDraw::PixelRGB_24* p = (LDraw::PixelRGB_24*)(bitmapdata.Scan0 + bitmapdata.Stride*y);

			for (uint x = 0; x < bitmapWidth; x++)
			{
			//	float fv = PerlinNoise_2D((float)x / bitmapWidth * 10, (float)y / bitmapHeight * 10);
				float fv = PerlinNoise_2D((float)((int)x-90) / 20, (float)((int)y-40) / 20);
			//	fv += 0.5;
				fv /= 2.0f;
				fv += 0.4f;
				if (fv < 0) fv = 0;
				else if (fv > 1) fv = 1;
				uint8 v = fv*255;

				p->r = v;
				p->g = v;
				p->b = v;

				++p;
			}
		}

		m_bitmap->UnlockBits(&bitmapdata);
	}

	graphics->DrawImage(m_bitmap, 0, 0);
}

}	// Media3D
}	// UI
}	// System
