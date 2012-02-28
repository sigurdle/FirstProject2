#ifndef __UI_Media3D_View3D_h__
#define __UI_Media3D_View3D_h__

#include "Object3D.h"

namespace System
{

class Thread : public Object
{
public:

	CTOR Thread();
	~Thread();

	virtual ULONG Run() = 0;

	void Wait();

public:

	HANDLE m_hThread;
	MSWindows::DWORD m_threadId;
};

namespace LDraw
{
X3DEXT void gluSphere(LDraw::Graphics3D* pG, double radius, int slices, int stacks);
X3DEXT void gluCylinder(LDraw::Graphics3D* pG, double baseRadius, double topRadius, double height, int slices, int stacks);
}

namespace UI
{
namespace Media3D
{

class Raytracer;
class View3D;

class RaytracerThread : public Thread
{
public:
	CTOR RaytracerThread()
	{
		m_raytracer = NULL;
		bQuit = false;
	}

	virtual ULONG Run();

	//View3D* view;
	int vtop;
	int vbottom;
	bool bQuit;

	Raytracer* m_raytracer;
};

class Raytracer : public Object
{
public:

	CTOR Raytracer()
	{
		m_view = NULL;
		numThreads = 0;
		m_threads.reserve(16);
	}

	struct Face
	{
		LDraw::vector3f tri[3];
		LDraw::vector3f normal[3];
		LDraw::vector3f texcoord[3];
		LDraw::vector3f plane_normal;
		float plane_distance;
		int i1, i2;
	//	unsigned int material;
		Material* material;
	};

	LDraw::vector4f Raytrace(LDraw::vector3f start, LDraw::vector3f ray, float rindex, int depth) const;

	double top;
	double bottom;

	double left;
	double right;

	double zNear;

	bool m_orthographic;

	LDraw::BitmapData bitmapdata;

	unsigned int numThreads;

	vector<RaytracerThread*> m_threads;

	View3D* m_view;

	vector<Face> faces;
	LDraw::matrix4f model;
	LDraw::matrix4f modelInverse;
};

class SelectedObject : public Object
{
public:
	CTOR SelectedObject()
	{
		m_object = NULL;
	}

	Object3D* m_object;
	LDraw::matrix4f m_wtransform;

	LDraw::matrix4f m_startTransform;

	float m_z;

	int m_axis;
	double m_axis_t;

	LDraw::vector3f m_startPivotPoint;
	LDraw::vector3f m_pivotPoint;

	void SelectVertex(unsigned int index);
	void DeselectVertex(unsigned int index);
	void DeselectAllVertices();

	inline bool IsVertexSelected(unsigned int index) const
	{
		return (m_vertexSelected.GetSize() > index) && m_vertexSelected[index];
	}

	LDraw::vector3f CalculateMedian();

//	Geometry* m_geometry;
	vector<int> m_points;
	vector<bool> m_vertexSelected;

	vector<LDraw::vector3f> m_startVertices;
};

class View3D : public Control
	//public IEventListener	// TODO remove ??
{
public:

	CTOR View3D(Document3D* document);

	//void DrawCamera(LDraw::Graphics3D* pG);

	void RenderObject(LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], Camera* object, LDraw::Graphics3D* pG, Deformer* pDeformer);

	void RenderObject(LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], Object3D* object, LDraw::Graphics3D* pG, Deformer* pDeformer);

	void OnRender(UI::Graphics* pGraphics);

	void RenderView();

	Raytracer* m_raytracer;
	
	//DWORD RaytraceThread(int top, int bottom);

	void hittest(const LDraw::matrix4f& model, const LDraw::matrix4f& proj, const double viewport[4], UI::Media3D::IndexedFaceSet* object, LDraw::vector3f mousepos, vector<int> & arr);

//	LDraw::Matrix4 m_objectTransform;

	void mousedown(UINT nFlags, LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], LDraw::vector3f mousepos, Object3D* object, vector<SelectedObject*>& selectedObjects);

	void mousedown(UINT nFlags, LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], LDraw::vector3f mousepos, Group* group, vector<SelectedObject*>& selectedObjects);

	void mousedown(UINT nFlags, LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], LDraw::vector3f mousepos, Camera* shape, vector<SelectedObject*>& selectedObjects)
	{
#if 0
	//	if (fabs(mousepos[0] - shape->get_Position()->get_X()) < 3 && fabs(mousepos[1] - shape->get_Position()->get_Y()) < 3)
		if (fabs(mousepos[0] - 0) < 3 && fabs(mousepos[1] - 0) < 3 && fabs(mousepos[2] - 0) < 3)
		{
			SelectedObject* p = new SelectedObject;
			p->m_object = shape;
			p->m_wtransform = wtransform;

			m_document->m_selectedObjects.push_back(p);
		}
#endif
	}

	void Move(long dragging, LDraw::PointI offset);
	void BeginMove();

	void mousedown(UINT nFlags, LDraw::matrix4f model, const LDraw::matrix4f& proj, const double viewport[4], LDraw::vector3f mousepos, Shape* shape, vector<SelectedObject*> & selectedObjects);

	//void handleEvent(System::Event* evt);

	enum Shading
	{
		Shading_None,
		Shading_Flat,
		Shading_Smooth,
		Shading_Raytrace,
	};

	Shading get_Shading();
	void set_Shading(Shading shading);

	double m_orthoOffsetX;
	double m_orthoOffsetY;
	double m_orthoScale;

	Camera* m_Camera;

	LDraw::PointD m_startmousepos;
	LDraw::PointD m_oldmousepos;

	LDraw::Bitmap* m_renderedBitmap;

	Document3D* m_document;

	Shading m_shading;

	int m_transformMode;

	int m_display;

	int m_dragging;

	int m_n;

	float m_dragX;
	float m_dragY;
	float m_dragZ;

	LDraw::matrix4f m_startTransform;
	LDraw::vector3f m_initialPosition;
	AxisAngle m_initialOrientation;
};

class TimelineView : public UI::Control
{
public:
	CTOR TimelineView();

protected:

//	virtual void handleEvent(System::Event* evt);

public:
	Document3D* m_document;
};

class X3DViewer2 : public UI::Control
{
public:
	CTOR X3DViewer2();

	void set_Content(View3D* Content);

protected:
//	virtual void handleEvent(System::Event* evt);

private:

	long m_xoffset;
	long m_yoffset;

	double m_width;
	double m_scale;

public:
	//Document3D* m_document;

	DeltaMoveButton* m_button[3];

	View3D* m_Content;
};

}	// Media3D
}	// UI
}	// System

#endif // __UI_Media3D_View3D_h__
