#include "stdafx.h"

#if AMIGA
#include "../amiga_header.h"
#include <stdio.h>
#endif

#include <algorithm>

#include "Browser.h"

#define typeof(x)	(typeid(x).GetType())

#include "../LSVG/LSVG.h"
#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/HTML.lib")
#pragma comment(lib, "../../lib/Win32/Debug/LSVG.lib")
#else
//#pragma comment(lib, "../../lib/Win32/Release/HTML.lib")
#endif

/*
namespace System
{
namespace MSWindows
{

typedef struct _SYSTEMTIME {
    uint16 wYear;
    uint16 wMonth;
    uint16 wDayOfWeek;
    uint16 wDay;
    uint16 wHour;
    uint16 wMinute;
    uint16 wSecond;
    uint16 wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

extern "C"
{
	WINBOOL WINAPI FileTimeToSystemTime(const WIN_FILETIME*, SYSTEMTIME*);
	WINBOOL WINAPI SystemTimeToFileTime(const SYSTEMTIME*, WIN_FILETIME*);
	LONG WINAPI CompareFileTime(const WIN_FILETIME *lpFileTime1, const WIN_FILETIME *lpFileTime2);
}
}
}
*/

#if AMIGA
#define WINAPI
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#endif

//typedef void*(*myFxnPtr )( type_info*, int, type_info*, type_info*, int );
//extern "C" void* __RTDynamicCast( void*, int, const type_info&, const type_info&, int );

#include "BrowserFrame.h"

#include "PropertiesWindow.h"

#include "View.h"

#include "ColorPickerRGB.h"

namespace System
{
using namespace ImageEdit;
}

/*
#include <iostream>
#include <algorithm>
*/

#include "HttpServer.h"

#if 0//WIN32
// Just for test purposes
#include <gl/gl.h>
#include <gl/glu.h>

#endif

#if WIN32
#include "HGlobalStream.h"
#endif	// WIN32

#include "../LXUI/UndoManager.h"

#include "OleCompoundFile.h"
#include "SpreadSheet.h"

#if 0//WIN32
#include "../LXMLEditor/Transition.h"
#include "../LXMLEditor/TransitionSettingsDlg.h"
#pragma comment(lib, "../LXMLEditor/Debug/LXMLEditor.lib")

__live_object_ptr<System::LXmlEdit::CTransitions> g_transitions = new System::LXmlEdit::CTransitions;
#endif

#if 0//WIN32
typdef int BOOL;

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#endif

#include "../LFC/RIFF.h"
//#pragma comment(lib, "../LAVI/Debug/LAVI.lib")

#include "wmf.h"
#include "../Draw/BasicCommands.h"

#if WIN32
#include "../SWF/swf.h"
#endif

#include "../LJPEG/JFIF.h"
#pragma comment(lib, "../../lib/Win32/Debug/JFIF")

#if WIN32
#include "../LPDF/LPDF.h"
#pragma comment(lib, "../../lib/Win32/Debug/LPDF.lib")

#include <wia.h>

#include <d3d9.h>
#include <d3dx9.h>

#undef min
#undef max

#pragma comment(lib, "wiaguid.lib")

#include "psd.h"

namespace System
{
void RenderContent(System::PDF::CPDFCosDoc& doc, System::PDF::CPDFCosDict* pResources, System::LDraw::Commands* pCommands);

extern Workbook* m_pWorkbook;
}

#endif

//#include "../Web/parsecolor.h"

#include "../LXUI/Binder.h"

#include "Item.h"

#if 0//WIN32
#include "../LHTML/LHTML.h"
#include "../Web/LDOMElement.h"
#include "../LHTML/LHTMLDocument.h"
#include "../LSVG/LSVG.h"
#include "../LSVG/LSVGDocument.h"
#include "../LSVG/LSVGSVGElement.h"
#include "../LSVG/LSVGEllipseElement.h"

#endif

#if WIN32

#if 0
#include "../LMPEGVideo/LMPEGVideoDecoder.h"
#include "../LMPEGVideo/VideoSequence.h"
#include "../LMPEGVideo/Picture.h"

#include "../LMPEG4/MP4File.h"
#include "../LMPEG4/MP4Track.h"
#endif

#endif

#include "../LMPEG4/LMPEG4.h"

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LMPEGVideo.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LMPEGVideo.lib")
#endif

#if _DEBUG
//#pragma comment(lib, "../LMPEG4/Debug/LMPEG4.lib")
#else
//#pragma comment(lib, "../LMPEG4/ReleaseMinSize/LMPEG4.lib")
#endif

#include "3DS.h"

#include "MusicModule.h"

//#include "IBSPFile.h"

#if 0
#if _DEBUG
#pragma comment(lib, "../LX3D/Debug/LX3D.lib")
#else
#pragma comment(lib, "../LX3D/Release/LX3D.lib")
#endif
#endif

#if WIN32
#include "../LVOC/VOCLoader.h"
#pragma comment(lib, "../../lib/Win32/Debug/LVOC.lib")

#include "dxfile.h"

#endif

#if 0//WIN32
#include "../LXImageEditor/LXImageEditor.h"
#include "../LXImageEditor/ImageView.h"
#include "../LXImageEditor/ImageDocument.h"
#include "../LXImageEditor/ImageLayerGroup.h"

#pragma comment(lib, "../LXImageEditor/Debug/LXImageEditor.lib")

#endif

#include "X3DViewer.h"

namespace System
{
namespace UI
{
extern LDraw::BufferData* g_bufferData;
extern __live_object_ptr<LDraw::GraphicsO::Resources> g_resources;
}
}

namespace System
{
using namespace IO;
using namespace UI;

extern __live_object_ptr<ScrollViewer> m_propertyPalette;

LONGLONG StreamCopy(ISequentialByteStream* dest, ISequentialByteStream* src);

/*
#include "../LMPEGAudio/AudioSequence.h"
#pragma comment(lib, "../LMPEGAudio/Debug/LMPEGAudio.lib");
*/

//#include "swfplayer.h"

template<class T>
struct DirSegment
{
	inline DirSegment()
	{
		prev = NULL;
		next = NULL;
	}

	vector<T> points;
	int down;

	DirSegment* prev;
	DirSegment* next;
};

template<class T> DirSegment<T>* DoSegments(const T* points, int pointcount)
{
	DirSegment<T>* segment;
	DirSegment<T>* firstsegment;

	T start = points[0];
	T end = points[1];

	int dir = end.Y > start.Y;

	start = end;
	int j = 1;

	while (j < pointcount)
	{
		end = points[j+1];

		int dir2 = end.Y > start.Y;
		if (dir2 != dir)
		{
			dir = dir2;
			break;
		}
		j++;
		start = end;
	}

	int i = 1;
	int count = 1;

	j++;
//	start = end;
	firstsegment = new DirSegment<T>;
	segment = firstsegment;
	segment->down = dir;
	firstsegment->points.push_back(start);

	while (i < pointcount+1)
	{
		end = points[j%pointcount];

		int dir2 = end.Y > start.Y;

		if (dir2 != dir)
			break;

		firstsegment->points.push_back(end);
		count++;
		start = end;
		i++;
		j++;
	}


	while (i < pointcount+1)
	{
		dir = !dir;

		DirSegment<T>* nextsegment = new DirSegment<T>;
		nextsegment->down = dir;
		nextsegment->prev = segment;
		segment->next = nextsegment;
		segment = nextsegment;

		segment->points.push_back(start);

		count = 0;

		do
		{
			T end = points[j%pointcount];

			int dir2 = end.Y > start.Y;

			if (dir2 != dir)
				break;

			segment->points.push_back(end);

			start = end;
			i++;
			j++;
			count++;
		}
		while (i < pointcount+1);

	}

	segment->next = firstsegment;
	firstsegment->prev = segment;

	/*
	{
		int n = 0;

		for (int i = 0; i < segments.size(); i += 2)
		{
			int count = segments[i];

			bool b = intersection(m_xpoints[n], m_xpoints[
			ASSERT(b);

			while (count)
			{
				Point& start = m_xpoints[i];
				Point& end = m_xpoints[i+1];

				start.X--;
				end.X--;
			}

			start = end;
		}
	}
	*/

	return firstsegment;
}

TestDraw::TestDraw()
{
	m_brush = new LDraw::SolidBrush(LDraw::Color(255, 0, 0));

	m_dragging = 0;

	m_points.reserve(300);

	/*
	m_points.push_back(LDraw::PointI(20, 10));
	m_points.push_back(LDraw::PointI(24, 10));
	m_points.push_back(LDraw::PointI(70, 30));
	m_points.push_back(LDraw::PointI(40, 70));
	m_points.push_back(LDraw::PointI(20, 80));
	m_points.push_back(LDraw::PointI(10, 50));
*/

	m_points2.push_back(LDraw::PointI(24-1, 10));
	m_points2.push_back(LDraw::PointI(90-1, 10));
	m_points2.push_back(LDraw::PointI(90-1, 80));
	m_points2.push_back(LDraw::PointI(20-1, 80));
	m_points2.push_back(LDraw::PointI(40-1, 70));
	m_points2.push_back(LDraw::PointI(70-1, 30));
}

void TestDraw::OnRender(UI::Graphics* pGraphics)
{
/*	if (m_points.size() > 2)
	{
		__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;

		path->AddMove(LDraw::PointF(m_points[0].X, m_points[0].Y));

		for (int i = 1; i < m_points.size(); i++)
		{
			path->AddLine(LDraw::PointF(m_points[i].X, m_points[i].Y));
		}

		pGraphics->FillPath(m_brush, path);
	}
*/


	pGraphics->FillPolygon(m_brush, m_points.begin(), m_points.size());
//	pGraphics->FillPolygon(new LDraw::SolidBrush(LDraw::Color(0, 255, 0)), m_points2.begin(), m_points2.size());

#if 1
	if (m_points.size() > 2)
	{
		DirSegment<LDraw::PointI>* firstsegment = DoSegments(m_points.begin(), m_points.size());

		DirSegment<LDraw::PointI>* segment = firstsegment;
		while (!segment->down)
		{
			segment = segment->next;
		}

		do
		{
			if (segment->down)
			{
				{
					for (int i = 0; i < segment->points.size(); i++)
					{
						segment->points[i][0]--;
					}
				}

				{
					LDraw::PointI start = segment->points[0];
					LDraw::PointI end = segment->points[1];

					LDraw::PointI instart = segment->prev->points[segment->prev->points.size()-2];
					LDraw::PointI inend = segment->prev->points[segment->prev->points.size()-1];

				//	if (instart.X-inend.X

			//	if (abs(start.X-end.X) >= abs(start.Y-end.Y))
				//		start.Y++;

					LDraw::PointI npt;
					/*
					LDraw::intersection(
						start, end,
						segment->prev->points[segment->prev->points.size()-2], segment->prev->points[segment->prev->points.size()-1], npt);
						*/

					npt = start;
				//	npt[0]--;

					segment->prev->points[segment->prev->points.size()-1] = npt;
					segment->points[0] = npt;
				}

				{
					LDraw::PointI start = segment->points[segment->points.size()-2];
					LDraw::PointI end = segment->points[segment->points.size()-1];

					if (abs(start.X-end.X) >= abs(start.Y-end.Y))
						end.Y--;

					LDraw::PointI npt;
		/*
					LDraw::intersection(
						start, end,
						segment->next->points[0], segment->next->points[1], npt);
		*/
					npt = end;
				//	npt[0]--;

					segment->next->points[0] = npt;
					segment->points[segment->points.size()-1] = npt;
				}
			}

			segment = segment->next;
		}
		while (segment != firstsegment);

		vector<LDraw::PointI> points;
		segment = firstsegment;

		do
		{
			for (int i = 0; i < segment->points.size()-1; i++)
			{
				points.push_back(segment->points[i]);
			}

			segment = segment->next;
		}
		while (segment != firstsegment);

		LDraw::Brush* brush = new LDraw::SolidBrush(LDraw::Color(255, 255, 0));
		pGraphics->FillPolygon(brush, points.begin(), points.size());

		/*

		int x1 = points[0].X*_SubRangeX;
		int y1 = points[0].Y*_SubRangeY;
		int startx = x1;
		int starty = y1;
		int n = 1;

		DirSegment<PointF>* segment2 = segment;
		do
		{
			for (int i = 0; i < segment2->count; i++)
			{
				int x2 = points[n % npoints].X*_SubRangeX;
				int y2 = points[n % npoints].Y*_SubRangeY;

			//	if (y2 > y1)
					AddLine1x1(scanlines, bounds, x1, y1, x2, y2);
			//	else
			//		AddLine1x1(scanlines, bounds, x1-_SubRangeX, y1, x2-_SubRangeX, y2);

				x1 = x2;
				y1 = y2;

				n++;
			}

			segment2 = segment2->next;
		}
		while (segment2 != segment);

		if (n-1 != npoints)
		{
			DirSegment* segment = DoSegments(points, npoints);
		}
		*/
	}
#endif
}

#if 0
void TestDraw::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (evt->get_type() == MouseEvent::mousedown)
		{
			evt->stopPropagation();
			if (!m_dragging)
			{
				MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);
				LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

				m_points.push_back(LDraw::PointI(point.X, point.Y));

				InvalidateRender();

				m_dragging = true;
			}
		}
		else if (evt->get_type() == MouseEvent::mouseup)
		{
			evt->stopPropagation();
			if (m_dragging)
			{
				m_dragging = false;
			}
		}
		else if (evt->get_type() == MouseEvent::mousemove)
		{
			evt->stopPropagation();
			if (m_dragging)
			{
				MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);

				LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

				m_points[m_points.size()-1] = LDraw::PointI(point.X, point.Y);

				InvalidateRender();
			}
		}
	}
}
#endif

#if 0
void ToolListener::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"click")
		{
			m_doc->m_pActiveTool = m_tool;
		}
	}
}
#endif

FileTimeObject::FileTimeObject(const WIN_FILETIME* value)
{
#if WIN32
	MSWindows::SYSTEMTIME systime;
	MSWindows::FileTimeToSystemTime((MSWindows::FILETIME*)value, &systime);
	systime.wMilliseconds = 0;
	systime.wSecond = 0;
	systime.wMinute = 0;
	systime.wHour = 0;
	MSWindows::SystemTimeToFileTime(&systime, (MSWindows::FILETIME*)&m_value);
#else
	ASSERT(0);
#endif
}

bool FileTimeObject::operator < (const IComparable* other) const
{
#if WIN32
	return MSWindows::CompareFileTime((MSWindows::FILETIME*)&m_value, (MSWindows::FILETIME*)&static_cast<const FileTimeObject*>(other)->m_value) < 0;
#else
	VERIFY(0);
	return false;
#endif
}

/*
namespace cpp
{
CodeCompExt int cpp_compile(CGlobal* pGlobal, const char * filepath, char * fileoutpath, int m_exeType);
}
*/

/*
namespace Test2
{
	class te
	{
	public:
	};
}

namespace Test3
{
	namespace Test2
	{
		class te2
		{
		public:
		};
	}

	namespace Test4
	{
		Test2::te2 u;
	}
}
*/

namespace UI
{
UIEXT IDirect3DDevice9* GetD3DDevice9();	// The one and only

namespace Media3D
{

IndexedFaceSet* CatmullClarkSubdivide(IndexedFaceSet* faceset)
{
	IndexedFaceSet* faceset2 = new IndexedFaceSet;
	UI::Media3D::Point3DfCollection* points2 = new UI::Media3D::Point3DfCollection;

	faceset2->m_points = points2;

	// Add the original points
	{
		for (uint i = 0; i < faceset->m_points->m_items.GetSize(); i++)
		{
			faceset2->AddVertex(faceset->m_points->m_items[i]);
		}
	}

	// Use this to keep track of vertex index that I add for each edge
	vector<uint> edgevertex;
	edgevertex.resize(faceset->m_edges.GetSize());	// Initialized to 0 means edge point not yet added

	vector<uint> facevertex;
	facevertex.resize(faceset->m_faces.GetSize());

	uint nfaces = faceset->m_faces.GetSize();
	{
		for (uint nface = 0; nface < nfaces; nface++)
		{
			const Face& face = faceset->m_faces[nface];

			// Calculate face point as centroid
			LDraw::vector3f center(0,0,0);

			{
				for (uint nedge = 0; nedge < face.m_edges.GetSize(); nedge++)
				{
					uint nvertex = faceset->m_edges[face.m_edges[nedge].GetIndex()].v[face.m_edges[nedge].IsBackward()];

					center += faceset->m_points->m_items[nvertex];
				}
			}

			center /= (int)face.m_edges.GetSize();

			uint ncenter = faceset2->AddVertex(center);
			facevertex[nface] = ncenter;
		}
	}

	{
		// Add a new point on each edge
		for (uint nedge = 0; nedge < faceset->m_edges.GetSize(); nedge++)
		{
			edgevertex[nedge] = faceset2->AddVertex(LDraw::vector3f());
		}
	}

	{
		for (uint nface = 0; nface < nfaces; nface++)
		{
			const Face& face = faceset->m_faces[nface];

			// There are the same number of new faces as there are old edges
			{
				for (uint nfaceedge = 0; nfaceedge < face.m_edges.GetSize(); nfaceedge++)
				{
					uint nedge0 = face.m_edges[nfaceedge].GetIndex();
					bool nedge0_forward = !face.m_edges[nfaceedge].IsBackward();
					uint nedge1 = face.m_edges[(nfaceedge+1) % face.m_edges.GetSize()].GetIndex();

					uint nface2 = faceset2->m_faces.GetSize();
					faceset2->m_faces.Add(Face());
					faceset2->m_materialFaceIndices.Add(faceset->m_materialFaceIndices[nface]);

					uint ncenter = facevertex[nface];
					uint nvertex0 = edgevertex[nedge0];
					uint nvertex1 = faceset->m_edges[nedge0].v[nedge0_forward];
					uint nvertex2 = edgevertex[nedge1];

					faceset2->AddFaceEdge(nface2, faceset2->AddEdge(ncenter, nvertex0));
					faceset2->AddFaceEdge(nface2, faceset2->AddEdge(nvertex0, nvertex1));
					faceset2->AddFaceEdge(nface2, faceset2->AddEdge(nvertex1, nvertex2));
					faceset2->AddFaceEdge(nface2, faceset2->AddEdge(nvertex2, ncenter));
				}
			}
		}
	}

	if (true)
	{
		for (uint i = 0; i < faceset->m_edges.GetSize(); i++)
		{
			uint nvertex = edgevertex[i];

			EdgeList* edgelist = faceset2->m_vertexEdges[nvertex];

			LDraw::vector3f v(0,0,0);

			uint nedges = 0;
			while (edgelist)
			{
				v += faceset2->m_points->m_items[faceset2->m_edges[edgelist->edge.GetIndex()].v[!edgelist->edge.IsBackward()]];

				nedges++;
				edgelist = edgelist->next;
			}
		//	ASSERT(count == 4);

			v /= (int)nedges;
			faceset2->m_points->m_items[nvertex] = v;
		}

		// for each original point
		{
			for (uint P = 0; P < faceset->m_points->m_items.GetSize(); P++)
			{
				// average of face point of all faces touching P

				LDraw::vector3f F(0,0,0);

				uint nfaces = 0;
				FaceList* faces = faceset->m_vertexFaces[P];
				while (faces)
				{
					uint nface = faces->nface;
					F += faceset2->m_points->m_items[facevertex[nface]];

					nfaces++;
					faces = faces->next;
				}

			//	ASSERT(nfaces == 4 || nfaces == 3);
				F /= (int)nfaces;

				// average of edge midpoint of all edges touching P

				LDraw::vector3f R(0,0,0);

				uint nedges = 0;
				EdgeList* edges = faceset->m_vertexEdges[P];
				while (edges)
				{
					uint nedge = edges->edge.GetIndex();
					R += (faceset->m_points->m_items[faceset->m_edges[nedge].v[0]] + faceset->m_points->m_items[faceset->m_edges[nedge].v[1]]) / 2;

					nedges++;
					edges = edges->next;
				}

			//	ASSERT(nedges == 4 || nedges == 3);
				R /= (int)nedges;

				VERIFY(nedges == nfaces);

				int n = nfaces;

				faceset2->m_points->m_items[P] = (F + R*2 + faceset->m_points->m_items[P]*(n - 3)) / n;
			}
		}
	}

	return faceset2;
}

void convert(x3d::MFNode* nodes, Media3D::Object3DCollection* destchildren)
{
	unsigned int size = nodes->get_size();

	for (unsigned int i = 0; i < size; i++)
	{
		x3d::X3DNode* node = nodes->get1Value(i);

		StringW* typeName = node->getTypeName();

		if (*typeName == L"Transform")
		{
			x3d::Transform* ob = static_cast<x3d::Transform*>(node);

			LDraw::matrix4f m = ob->GetTransform();

			Media3D::Group* mob = new Media3D::Group;
			Media3D::Object3DCollection* mobchildren = new Media3D::Object3DCollection;
			mob->set_Children(mobchildren);
			mob->m_transform = new LDraw::Matrix4(m);

			x3d::MFNode* children = ob->get_children();

			convert(children, mobchildren);

			destchildren->AddChild(mob);
		}
		else if (*typeName == L"Group")
		{
			x3d::Group* ob = static_cast<x3d::Group*>(node);

			x3d::MFNode* children = ob->get_children();

			Media3D::Group* mob = new Media3D::Group;
			Media3D::Object3DCollection* mobchildren = new Media3D::Object3DCollection;
			mob->set_Children(mobchildren);

			convert(children, mobchildren);

			destchildren->AddChild(mob);
		}
		else if (*typeName == L"Shape")
		{
			x3d::Shape* ob = static_cast<x3d::Shape*>(node);

			Media3D::Shape* mob = new Media3D::Shape;

			x3d::X3DAppearanceNode* appearanceNode = ob->getAppearance();
			x3d::X3DGeometryNode* geometryNode = ob->getGeometry();

			if (appearanceNode)
			{
				// TODO
				x3d::Appearance* appearance = static_cast<x3d::Appearance*>(appearanceNode);

				x3d::X3DMaterialNode* materialNode = materialNode = appearance->getMaterial();

				if (materialNode)
				{
					x3d::Material* material = static_cast<x3d::Material*>(materialNode);

					Media3D::Material* mmaterial = new Media3D::Material;
					mob->m_materialList.push_back(mmaterial);

					LDraw::vector3f diffuseColor = material->getDiffuseColor();
					LDraw::vector3f specularColor = material->getSpecularColor();
					float transparency = material->getTransparency();

					mmaterial->m_diffuseColor = LDraw::vector4f(diffuseColor, 1);
					mmaterial->m_specularColor = LDraw::vector4f(specularColor, 1);
				}
			}

			if (geometryNode)
			{
				StringW* typeName = geometryNode->getTypeName();

				if (*typeName == L"IndexedFaceSet")
				{
					x3d::IndexedFaceSet* faceset = static_cast<x3d::IndexedFaceSet*>(geometryNode);

					IndexedFaceSet* mfaceset = new IndexedFaceSet;
					Point3DfCollection* points = new Point3DfCollection;
				//	Int32Collection* pointindices = new Int32Collection;
					mfaceset->set_Points(points);
				//	mfaceset->set_PointIndices(pointindices);

					x3d::Coordinate* coord = faceset->getCoord();
					x3d::MFVec3f* point = coord->getPoint();

					{
						unsigned int count = point->get_size();

						mfaceset->m_points->m_items.reserve(count);
						mfaceset->m_vertexEdges.reserve(count);
						mfaceset->m_vertexFaces.reserve(count);

						for (unsigned int i = 0; i < count; i++)
						{
							LDraw::vector3f p = point->get1Value(i);
							mfaceset->AddVertex(p);
						}
					}
					mfaceset->m_vertexEdges.resize(points->m_items.GetSize());

					{
						unsigned int count = faceset->getCoordIndexSize();
						unsigned int i = 0;
						while (i < count)
						{
							uint nface = mfaceset->m_faces.size();
							mfaceset->m_faces.push_back(Media3D::Face());

						//	Media3D::Face newface;
						//	mfaceset->m_faces.push_back(newface);
						//	Media3D::Face& face = mfaceset->m_faces[mfaceset->m_faces.size()-1];
							mfaceset->m_materialFaceIndices.push_back(0);	// Face uses material #0

							int v0 = faceset->getCoordIndex1Value(i);
							if (v0 == -1)
							{
								VERIFY(0);
								throw -1;
							}
							i++;

							int vi0 = v0;
							while (i < count)
							{
								int vi1 = faceset->getCoordIndex1Value(i);
								i++;
								if (vi1 == -1)
								{
									break;
								}

							//	Media3D::DirectedEdge nedge = mfaceset->AddEdge(vi0, vi1);
							//	face.m_edges.push_back(nedge);
								mfaceset->AddFaceEdge(nface, mfaceset->AddEdge(vi0, vi1));

								vi0 = vi1;
							}

							VERIFY(vi0 != v0);
							mfaceset->AddFaceEdge(nface, mfaceset->AddEdge(vi0, v0));//face.m_edges.push_back(nedge);
						}
					}

					if (true)
					{
					//	mfaceset = CatmullClarkSubdivide(mfaceset);
					//	mfaceset = CatmullClarkSubdivide(mfaceset);
					}

					/*
					// Obsolote ??
					{
						unsigned int count = faceset->getCoordIndexSize();
						unsigned int i = 0;
						while (i < count)
						{
							int v = faceset->getCoordIndex1Value(i);
							i++;
							if (v == -1)
							{
							//	mfaceset->m_materialFaceIndices.push_back(0);	// Face uses material #0
								continue;
							}
							pointindices->append1Value(v);
						}
					}
					*/

				//	mfaceset->BuildEdges();

					if (true)
					{
						// Calculate face normals
					//	Int32Collection* normalIndices = new Int32Collection;
					//	Media3D::Point3DCollection* normals = new Media3D::Point3DCollection;

						uint nfaces = mfaceset->m_faces.GetSize();

						mfaceset->m_faceNormals.reserve(nfaces);

						for (uint i = 0; i < nfaces; i++)
						{
							const Media3D::Face& face = mfaceset->m_faces[i];

							uint index0 = mfaceset->m_edges[face.m_edges[0].GetIndex()].v[face.m_edges[0].IsBackward()];
							uint index1 = mfaceset->m_edges[face.m_edges[1].GetIndex()].v[face.m_edges[1].IsBackward()];
							uint index2 = mfaceset->m_edges[face.m_edges[2].GetIndex()].v[face.m_edges[2].IsBackward()];
					//		int index1 = pointindices->GetItem(i*3+1);
					//		int index2 = pointindices->GetItem(i*3+2);

							LDraw::vector3f v0 = mfaceset->m_points->m_items[index0];
							LDraw::vector3f v1 = mfaceset->m_points->m_items[index1];
							LDraw::vector3f v2 = mfaceset->m_points->m_items[index2];

							LDraw::vector3f normal = LDraw::cross(v1-v0, v2-v0);
							normal.normalize();

						//	normalIndices->append1Value(i);
							mfaceset->m_faceNormals.Add(normal);
						}

					//	mfaceset->set_Normals(normals);
					//	mfaceset->set_NormalIndices(normalIndices);

						// Vertex normals as average of normal of adjacent faces
						{
							mfaceset->m_vertexNormals.reserve(mfaceset->m_points->m_items.GetSize());
							for (uint i = 0; i < mfaceset->m_points->m_items.GetSize(); i++)
							{
								FaceList* facelist = mfaceset->m_vertexFaces[i];

								LDraw::vector3f normal(0,0,0);

								uint nfaces = 0;
								while (facelist)
								{
									normal += mfaceset->m_faceNormals[facelist->nface];

									++nfaces;
									facelist = facelist->next;
								}

								normal /= (int)nfaces;

								mfaceset->m_vertexNormals.Add(normal);
							}
						}

						mob->set_Geometry(mfaceset);


						/*
						Int32Collection* normalIndices = new Int32Collection;
						Media3D::Point3DCollection* normals = new Media3D::Point3DCollection;

						unsigned int count = pointindices->m_items.size()/3;

						for (int i = 0; i < count; i++)
						{
							int index0 = pointindices->GetItem(i*3+0);
							int index1 = pointindices->GetItem(i*3+1);
							int index2 = pointindices->GetItem(i*3+2);

							LDraw::vector3f v0 = points->m_items[index0];
							LDraw::vector3f v1 = points->m_items[index1];
							LDraw::vector3f v2 = points->m_items[index2];

							LDraw::vector3f normal = LDraw::cross(v1-v0, v2-v0);
							normal.normalize();

							normalIndices->append1Value(i);
							normals->append1Value(normal);
						}

						mfaceset->set_Normals(normals);
						mfaceset->set_NormalIndices(normalIndices);
						*/
					}
				}
			}

			destchildren->AddChild(mob);
		}
		else if (*typeName == L"PointLight")
		{
			x3d::PointLight* ob = static_cast<x3d::PointLight*>(node);

			LDraw::vector3f location = ob->getLocation();
			LDraw::vector3f color = ob->getColor();
			float intensity = ob->getIntensity();
			float radius = ob->getRadius();

			Light* mob = new Media3D::Light;
			mob->m_location = location;
			mob->m_color = color;
			mob->m_intensity = intensity;
			mob->m_radius = radius;

			destchildren->AddChild(mob);
		}
		else if (*typeName == L"Viewpoint")
		{
			x3d::Viewpoint* viewpoint = static_cast<x3d::Viewpoint*>(node);

			LDraw::vector3f position = viewpoint->getPosition();
			AxisAngle orientation = viewpoint->getOrientation();
			float fov = viewpoint->getFieldOfView();

			Media3D::Camera* pCamera = new Media3D::Camera;
			pCamera->set_FieldOfView(fov * 180 / M_PI);
			pCamera->set_Orientation(orientation);
			pCamera->set_Position(position);

			destchildren->AddChild(pCamera);
		}
		else if (*typeName == L"OrthoViewpoint")
		{
			x3d::OrthoViewpoint* viewpoint = static_cast<x3d::OrthoViewpoint*>(node);

			LDraw::vector3f position = viewpoint->getPosition();
			AxisAngle orientation = viewpoint->getOrientation();

			Media3D::Camera* pCamera = new Media3D::Camera;
			pCamera->set_Orthographic(true);
			pCamera->set_Orientation(orientation);
			pCamera->set_Position(position);

			destchildren->AddChild(pCamera);
		}
	}
}

}	// Media3D
}	// UI

////////////////////////////////////////
// MetafileVisual

void MetafileVisual::OnRender(UI::Graphics* pGraphics)
{
	LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
	//pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

	if (true)
	{
		pGraphics->ScaleTransform(m_computedSize.Width / m_originalRect.Width, m_computedSize.Height / m_originalRect.Height);
		pGraphics->TranslateTransform(-m_originalRect.X, -m_originalRect.Y);

	//	pGraphics->ScaleTransform(1/20.0, 1/20.0);

		pGraphics->RenderCommands(m_commands);
	}

	pGraphics->SetSmoothingMode(oldSmoothingMode);
}

const char* GetExtension(const char* filename)
{
	const char* p = filename + std::strlen(filename)-1;

	while (p >= filename)
	{
		if (*p == '.')
		{
			return p+1;
		}
		--p;
	}

	return NULL;
}

//int g_nframe = 0;


bool PakFile::Open(const char* filename)
{
	m_fp = std::fopen(filename, "rb");
	if (m_fp)
	{
		std::fread(&m_header, sizeof(m_header), 1, m_fp);

		std::fseek(m_fp, m_header.diroffset, SEEK_SET);

		m_entries = new pakentry[m_header.dirsize];

		m_nentries = m_header.dirsize / sizeof(pakentry);
		std::fread(m_entries, m_header.dirsize, 1, m_fp);

		for (int i = 0; i < m_nentries; i++)
		{
			const char* ext = GetExtension(m_entries[i].filename);
			if (_stricmp(ext, "lmp") == 0)
			{
				MessageBeep(-1);
			}

			TRACE("%s - %d\n", m_entries[i].filename, m_entries[i].size);
		}

		return true;
	}
	else
		return false;
}

int ReadLine(IO::ISequentialByteStream* stream, char* buffer)
{
	int linelen = 0;
	while (1)
	{
		char c;
		if (stream->Read(&c, 1) != 1)
		{
			buffer[linelen] = 0;
			return -1;
		}

		if (c == '\r')
			continue;

		if (c == '\n')
			break;

		buffer[linelen++] = c;
	}

	buffer[linelen] = 0;

	return 0;
}

/*
class Tokenizer
{
public:
	int adv();

	char token[1024];
	IO::ISequentialByteStream* m_stream;
};

int Tokenizer::adv()
{
	char c;
	if (m_stream->Read(&c, 1) != 1)
		return -1;

	if (isalpha(c))
	{
	}
	else if (issymbol(c))
	{
	}
	else if (isdigit(c) || c == '-')
	{
	}

	return 0;
}
*/

void Q3Model::LoadAnimation(IO::ISequentialByteStream* stream)
{
	/*
	Tokenizer tokenizer;
	tokenizer.m_stream = stream;
	tokenizer.adv();

	tokenizer.token;
	*/
}



///////////////////////////////////////////
// BrowserFrame

RoutedUICommand* BrowserFrame::s_SetToolCommand = new RoutedUICommand;
RoutedUICommand* BrowserFrame::s_ImportFromWIACommand = new RoutedUICommand;
RoutedUICommand* BrowserFrame::s_LayerAddMaskCommand = new RoutedUICommand;

BrowserFrame::BrowserFrame()
{
	VERIFY(sizeof(Object) == typeid(Object).GetType()->get_sizeof());
	VERIFY(sizeof(StringW) == typeid(StringW).GetType()->get_sizeof());
	VERIFY(sizeof(StringA) == typeid(StringA).GetType()->get_sizeof());
	VERIFY(sizeof(DependencyObject) == typeid(DependencyObject).GetType()->get_sizeof());
	VERIFY(sizeof(Media::Animatable) == typeid(Media::Animatable).GetType()->get_sizeof());
	VERIFY(sizeof(Visual) == typeid(Visual).GetType()->get_sizeof());
	VERIFY(sizeof(UIElement) == typeid(UIElement).GetType()->get_sizeof());
	VERIFY(sizeof(FrameworkElement) == typeid(FrameworkElement).GetType()->get_sizeof());
	VERIFY(sizeof(TextString) == typeid(TextString).GetType()->get_sizeof());
	VERIFY(sizeof(Control) == typeid(Control).GetType()->get_sizeof());
	VERIFY(sizeof(Decorator) == typeid(Decorator).GetType()->get_sizeof());
	VERIFY(sizeof(Border) == typeid(Border).GetType()->get_sizeof());
	VERIFY(sizeof(ChildWindow) == typeid(ChildWindow).GetType()->get_sizeof());
	VERIFY(sizeof(ChildWindowContainer) == typeid(ChildWindowContainer).GetType()->get_sizeof());
	VERIFY(sizeof(CLXUITitlebarElement) == typeid(CLXUITitlebarElement).GetType()->get_sizeof());

	VERIFY(sizeof(BrowserFrame) == typeid(BrowserFrame).GetType()->get_sizeof());
	VERIFY(sizeof(BSPViewer) == typeid(BSPViewer).GetType()->get_sizeof());

	VERIFY(sizeof(w3c::Node) == typeid(w3c::Node).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::Attr) == typeid(w3c::Attr).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::Text) == typeid(w3c::Text).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::Comment) == typeid(w3c::Comment).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::CDATASection) == typeid(w3c::CDATASection).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::Element) == typeid(w3c::Element).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::Document) == typeid(w3c::Document).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::DocumentType) == typeid(w3c::DocumentType).GetType()->get_sizeof());

	VERIFY(sizeof(w3c::SVGLength) == typeid(w3c::SVGLength).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGAnimatedLength) == typeid(w3c::SVGAnimatedLength).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGPoint) == typeid(w3c::SVGPoint).GetType()->get_sizeof());

	VERIFY(sizeof(w3c::HTMLElement) == typeid(w3c::HTMLElement).GetType()->get_sizeof());

	int size0 = sizeof(w3c::HTMLLinkElement);
	ClassType* pType = (ClassType*)typeid(w3c::HTMLLinkElement).GetType();
	int size1 = typeid(w3c::HTMLLinkElement).GetType()->get_sizeof();
//	VERIFY(sizeof(w3c::HTMLLinkElement) == typeid(w3c::HTMLLinkElement).GetType()->get_sizeof());
//	VERIFY(sizeof(w3c::HTMLImageElement) == typeid(w3c::HTMLImageElement).GetType()->get_sizeof());

	VERIFY(sizeof(w3c::SVGElement) == typeid(w3c::SVGElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGTransformableElement) == typeid(w3c::SVGTransformableElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGEllipseElement) == typeid(w3c::SVGEllipseElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGCircleElement) == typeid(w3c::SVGCircleElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGPolylineElement) == typeid(w3c::SVGPolylineElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGPolygonElement) == typeid(w3c::SVGPolygonElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGSVGElement) == typeid(w3c::SVGSVGElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGSwitchElement) == typeid(w3c::SVGSwitchElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::SVGFilterElement) == typeid(w3c::SVGFilterElement).GetType()->get_sizeof());

	VERIFY(sizeof(w3c::CHTMLWindow) == typeid(w3c::CHTMLWindow).GetType()->get_sizeof());

	VERIFY(sizeof(w3c::PSVGSVGElement) == typeid(w3c::PSVGSVGElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::PSVGShapeElement) == typeid(w3c::PSVGShapeElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::PSVGPolygonElement) == typeid(w3c::PSVGPolygonElement).GetType()->get_sizeof());
	VERIFY(sizeof(w3c::PSVGEllipseElement) == typeid(w3c::PSVGEllipseElement).GetType()->get_sizeof());

	VERIFY(sizeof(queue<SongPosition>) == typeid(queue<SongPosition>).GetType()->get_sizeof());

	VERIFY(sizeof(MusicModuleView) == typeid(MusicModuleView).GetType()->get_sizeof());
	VERIFY(sizeof(PatternView) == typeid(PatternView).GetType()->get_sizeof());
	VERIFY(sizeof(ScopeView) == typeid(ScopeView).GetType()->get_sizeof());
	VERIFY(sizeof(InstrumentsView) == typeid(InstrumentsView).GetType()->get_sizeof());

	VERIFY(sizeof(ImageEdit::Element) == typeid(ImageEdit::Element).GetType()->get_sizeof());
	VERIFY(sizeof(ImageEdit::Group) == typeid(ImageEdit::Group).GetType()->get_sizeof());
	VERIFY(sizeof(ImageEdit::BitmapLayer) == typeid(ImageEdit::BitmapLayer).GetType()->get_sizeof());
	VERIFY(sizeof(ImageEdit::BitmapEditor) == typeid(ImageEdit::BitmapEditor).GetType()->get_sizeof());

	if (true)
	{
		int whatmode = 7;

		if (whatmode == 0)
		{
			BitmapVisual* ctl = new BitmapVisual;

			LinearGradientBrush* brush = new LinearGradientBrush(Color::FromArgb(255, 0, 0, 0), Color::FromArgb(0, 0, 0, 0), Point(0, 0), Point(1, 1));

			ctl->set_OpacityMask(brush);

			//ctl->m_bitmap =  LDraw::Bitmap(L"C:\\Documents and Settings\\Sigurd Lerstad\\My Documents\\My Pictures\\test.tif");
			Imaging::BitmapLoader loader;
			loader.Load(ASTR("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.jpg"));
			ctl->set_Bitmap(loader.GetBitmap());// LDraw::Bitmap(WSTR("C:\\Documents and Settings\\Sigurd Lerstad\\My Documents\\My Pictures\\test.gif"));

			set_Content(ctl);
		}
		else if (whatmode == 1)
		{
			BSPViewer* viewer = new BSPViewer;

			{
				std::FILE* fp = std::fopen("C:/files/Quake2Maps/palette.lmp", "rb");
				if (fp)
				{
					std::fread(palette, 256*3, 1, fp);
					std::fclose(fp);
				}
				else
					VERIFY(0);
			}

			PakFile* pakfile = new PakFile;
			pakfile->Open("C:/Program Files/Q2Demo/baseq2/pak0.pak");

			//std::FILE* fp = std::fopen("C:\\Files\\Quake2Maps\\1\\1\\maps\\1.bsp", "rb");

		//	char* filename = "C:\\Files\\Quake2Maps\\666mines\\maps\\666mines.bsp";
		//	char* filename = "C:\\Files\\Quake2Maps\\actone\\maps\\actone.bsp";

		//	char* filename = "C:\\Files\\Quake2Maps\\187city\\187city\\maps\\187city.bsp";

			char* filename = "C:\\Files\\Quake2Maps\\actone\\maps\\actone.bsp";

			filename = "C:/DevDownloads/Graphics/Gl_BspLoader2/BspLoader2/maps/ugptestmap.bsp";

			ZIP::Archive* archive = new ZIP::Archive;

			archive->Open(new FileByteStream(WSTR("C:\\Files\\Quake3Maps\\simp4\\simp4.pk3")));
			ZIP::File* file = archive->FindFile(ASTR("maps/Simp4.bsp"));

		//	archive->Open(new FileByteStream(WSTR("C:\\Files\\Quake3Maps\\halctf1\\halctf1.pk3")));
		//	ZIP::File* file = archive->FindFile(ASTR("maps/halctf1.bsp"));

		//	archive->Open(new FileByteStream(WSTR("C:\\Files\\Quake3Maps\\test.zip")));
		//	ZIP::File* file = archive->FindFile(ASTR("todo_new.wri"));
		//	archive->Open(new FileByteStream(WSTR("C:\\Program Files\\Java\\jdk1.6.0_06\\jre\\lib\\rt.jar")));
		//	ZIP::File* file = archive->FindFile(ASTR("META-INF/MANIFEST.MF"));

			IO::ISequentialByteStream* fp = file->GetStream();

			fp = new FileByteStream(new StringA(string_copy(filename)));

		//	std::FILE* fp = std::fopen(filename, "rb");

			if (fp)
			{
			//	std::fseek(fp, 0, SEEK_END);
				long size = fp->GetSize();//std::ftell(fp);
			//	std::rewind(fp);

				BSPFile* bspfile = new BSPFile;
				strcpy_s(bspfile->m_filename, filename);

				bspfile->m_buffer = new char[size];
				ULONG nRead = fp->Read(bspfile->m_buffer, size);
				ASSERT(nRead == size);

				bsp_header& header = bspfile->header();
			//	std::fread(&header, sizeof(bsp_header), 1, fp);

				if (header.version == 38)
				{
					bspfile->m_nplanes = header.lump[1].length / sizeof(bsp_plane);
					bspfile->m_planes = (bsp_plane*)(bspfile->m_buffer + bspfile->header().lump[1].offset);

					bspfile->m_nvertices = header.lump[2].length / sizeof(LDraw::vector3f);
					bspfile->m_vertices = (LDraw::vector3f*)(bspfile->m_buffer + bspfile->header().lump[2].offset);

					bspfile->m_nnodes = header.lump[4].length / sizeof(bsp_node);
					bspfile->m_nodes = (bsp_node*)(bspfile->m_buffer + bspfile->header().lump[4].offset);

					bspfile->m_ntexinfos = header.lump[5].length / sizeof(bsp_texinfo);
					bspfile->m_texinfos = (bsp_texinfo*)(bspfile->m_buffer + bspfile->header().lump[5].offset);

					bspfile->m_nfaces = header.lump[6].length / sizeof(bsp_face);
					bspfile->m_faces = (bsp_face*)(bspfile->m_buffer + bspfile->header().lump[6].offset);

					bspfile->m_lightmapssize = header.lump[7].length;
					bspfile->m_lightmaps = (uint8*)(bspfile->m_buffer + bspfile->header().lump[7].offset);

					bspfile->m_nleaves = header.lump[8].length / sizeof(bsp_leaf);
					bspfile->m_leaves = (bsp_leaf*)(bspfile->m_buffer + bspfile->header().lump[8].offset);

					bspfile->m_nleaffaces = header.lump[9].length / sizeof(uint16);
					bspfile->m_leaffaces = (uint16*)(bspfile->m_buffer + bspfile->header().lump[9].offset);

					bspfile->m_nedges = header.lump[11].length / sizeof(bsp_edge);
					bspfile->m_edges = (bsp_edge*)(bspfile->m_buffer + bspfile->header().lump[11].offset);

					bspfile->m_nfaceedges = header.lump[12].length / sizeof(uint32);
					bspfile->m_faceedges = (uint32*)(bspfile->m_buffer + bspfile->header().lump[12].offset);
				}
				else if (header.version == 46)
				{
					bsp_header& header = bspfile->header();

					if (header.lump[1].length % sizeof(bsp_texinfo_v3) != 0) throw std::exception("Corrupt file");
					bspfile->m_ntexinfos = header.lump[1].length / sizeof(bsp_texinfo_v3);
					bspfile->m_texinfos_v3 = (bsp_texinfo_v3*)(bspfile->m_buffer + header.lump[1].offset);

					if (header.lump[2].length % sizeof(bsp_plane_v3) != 0) throw std::exception("Corrupt file");
					bspfile->m_nplanes = header.lump[2].length / sizeof(bsp_plane_v3);
					bspfile->m_planes_v3 = (bsp_plane_v3*)(bspfile->m_buffer + header.lump[2].offset);

					if (header.lump[10].length % sizeof(bsp_vertex_v3) != 0) throw std::exception("Corrupt file");
					bspfile->m_nvertices = header.lump[10].length / sizeof(bsp_vertex_v3);
					bspfile->m_vertices_v3 = (bsp_vertex_v3*)(bspfile->m_buffer + header.lump[10].offset);

					if (header.lump[13].length % sizeof(bsp_face_v3) != 0) throw std::exception("Corrupt file");
					bspfile->m_nfaces = header.lump[13].length / sizeof(bsp_face_v3);
					bspfile->m_faces_v3 = (bsp_face_v3*)(bspfile->m_buffer + header.lump[13].offset);

					if (header.lump[3].length % sizeof(bsp_node_v3) != 0) throw std::exception("Corrupt file");
					bspfile->m_nnodes = header.lump[3].length / sizeof(bsp_node_v3);
					bspfile->m_nodes_v3 = (bsp_node_v3*)(bspfile->m_buffer + header.lump[3].offset);

					if (header.lump[4].length % sizeof(bsp_leaf_v3) != 0) throw std::exception("Corrupt file");
					bspfile->m_nleaves = header.lump[4].length / sizeof(bsp_leaf_v3);
					bspfile->m_leaves_v3 = (bsp_leaf_v3*)(bspfile->m_buffer + header.lump[4].offset);

					if (header.lump[5].length % sizeof(uint32) != 0) throw std::exception("Corrupt file");
					bspfile->m_nleaffaces = header.lump[5].length / sizeof(uint32);
					bspfile->m_leaffaces_v3 = (uint32*)(bspfile->m_buffer + header.lump[5].offset);

					if (header.lump[11].length % sizeof(int32) != 0) throw std::exception("Corrupt file");
					bspfile->m_nmeshverts = header.lump[11].length / sizeof(int32);
					bspfile->m_meshverts = (int32*)(bspfile->m_buffer + header.lump[11].offset);

					if (header.lump[14].length % sizeof(bsp_lightmap) != 0) throw std::exception("Corrupt file");
					bspfile->m_nlightmaps = header.lump[14].length / sizeof(bsp_lightmap);
					bspfile->m_lightmaps_v3 = (bsp_lightmap*)(bspfile->m_buffer + header.lump[14].offset);
				}
				else
					ASSERT(0);

				//fp->;

				viewer->set_Map(bspfile);
			}

			if (false)
			{
				viewer->m_model = new Q3Model;

				ZIP::Archive* archive = new ZIP::Archive;

				if (true)
				{
					archive->Open(new FileByteStream(WSTR("C:/Files/Quake3Maps/Q3A_model_pack1/Downloads/MOH/q3mdl-alien3/md3_alien3.pk3")));

					IO::ISequentialByteStream* fp = archive->FindFile(ASTR("models/players/alien3/head.md3"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_head = new MD3Model;
						viewer->m_model->m_head->Load(fp);
					}

					fp = archive->FindFile(ASTR("models/players/alien3/upper.md3"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_upper = new MD3Model;
						viewer->m_model->m_upper->Load(fp);
					}

					fp = archive->FindFile(ASTR("models/players/alien3/lower.md3"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_lower = new MD3Model;
						viewer->m_model->m_lower->Load(fp);
					}

					fp = archive->FindFile(ASTR("models/players/alien3/head_default.skin"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_head->LoadSkin(fp, viewer->m_model, archive);
					}

					fp = archive->FindFile(ASTR("models/players/alien3/upper_default.skin"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_upper->LoadSkin(fp, viewer->m_model, archive);
					}

					fp = archive->FindFile(ASTR("models/players/alien3/lower_default.skin"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_lower->LoadSkin(fp, viewer->m_model, archive);
					}

					fp = archive->FindFile(ASTR("models/players/alien3/animation.cfg"))->GetStream();
					if (fp)
					{
						viewer->m_model->LoadAnimation(fp);
					}
				}
				else
				{
					archive->Open(new FileByteStream(WSTR("C:/Files/Quake3Maps/Q3A_model_pack1/Downloads/MOH/q3mdl-animal/md3-animal.pk3")));

					IO::ISequentialByteStream* fp = archive->FindFile(ASTR("models/players/animal/head.md3"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_head = new MD3Model;
						viewer->m_model->m_head->Load(fp);
					}

					fp = archive->FindFile(ASTR("models/players/animal/upper.md3"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_upper = new MD3Model;
						viewer->m_model->m_upper->Load(fp);
					}

					fp = archive->FindFile(ASTR("models/players/animal/lower.md3"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_lower = new MD3Model;
						viewer->m_model->m_lower->Load(fp);
					}

					fp = archive->FindFile(ASTR("models/players/animal/head_default.skin"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_head->LoadSkin(fp, viewer->m_model, archive);
					}

					fp = archive->FindFile(ASTR("models/players/animal/upper_default.skin"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_upper->LoadSkin(fp, viewer->m_model, archive);
					}

					fp = archive->FindFile(ASTR("models/players/animal/lower_default.skin"))->GetStream();
					if (fp)
					{
						viewer->m_model->m_lower->LoadSkin(fp, viewer->m_model, archive);
					}

					fp = archive->FindFile(ASTR("models/players/animal/animation.cfg"))->GetStream();
					if (fp)
					{
						viewer->m_model->LoadAnimation(fp);
					}
				}
			}

		//	LinearGradientBrush* brush = new LinearGradientBrush(new Color(0, 0, 0, 255), new Color(0, 0, 0, 0), Point(0, 0), Point(1, 1));
		//	viewer->set_OpacityMask(brush);

			set_Content(viewer);
		}
		else if (whatmode == 2)
		{
			x3d::VRMLLoader* pLoader = new x3d::VRMLLoader;
	//		x3d::Scene* pScene = pLoader->Load(WSTR("C:/mmstudio/Scenes/test2.wrl"));
	//		x3d::Scene* pScene = pLoader->Load(WSTR("C:/Files/VRML/RedSphereBlueBox.x3dv"));
			x3d::Scene* pScene = pLoader->Load(WSTR("C:/Files/VRML/test_shading.wrl"));

		//	X3DViewer* v = new X3DViewer;
		//	v->m_pWindow->m_pControl->SetScene(pScene);
			x3d::COGLSceneRenderer* pViewer = new x3d::COGLSceneRenderer;
			pViewer->SetScene(pScene);

			set_Content(pViewer);
		}
		else if (whatmode == 3)
		{
			UI::DockPanel* pPanel = new UI::DockPanel;

			UI::CUIDockBar* pDockbar = new UI::CUIDockBar;
			pPanel->get_Children()->Add(pDockbar);

			m_pWindowContainer = new ChildWindowContainer;
			UI::DockPanel::SetDock(m_pWindowContainer, UI::DockPanel::Fill);
			pPanel->get_Children()->Add(m_pWindowContainer);

			{
				UI::ChildWindow* child = new UI::ChildWindow;
				child->set_Title(WSTR("Title"));

				w3c::CHTMLWindow* pBrowser = new w3c::CHTMLWindow;
			//	pBrowser->Load(WSTR("c:/mmstudio/help/side3.html"));
				pBrowser->Load(WSTR("c:/mmstudio/help/svg_test.html"));

				child->set_Width(400);
				child->set_Height(400);

				child->set_Content(pBrowser);

				m_pWindowContainer->get_Items()->Add(child);
			}

			set_Content(pPanel);
		}
		else if (whatmode == 4)
		{
		//	pMusicModule->Load(WSTR("C:/files/mods/SOUL-O-M.MOD"));
		//	pMusicModule->Load(WSTR("C:/files/mods/4mat_2/mod.electric-revenge"));
		//	MusicModule* pMusicModule = MusicModuleReader(WSTR("C:/files/mods/battle.mod")).m_pModule;
		//	MusicModule* pMusicModule = MusicModuleReader(WSTR("C:/Files/MODS/4mat_4/mod.waterfall")).m_pModule;
			MusicModule* pMusicModule = MusicModuleReader(WSTR("C:/Files/MODS/test2.mod")).m_pModule;

			MusicModuleView* pView = new MusicModuleView;
			pView->SetModule(pMusicModule);

			set_Content(pView);
		}
		else if (whatmode == 5)
		{
		//	UI::MediaElement* video = NULL;
		//	video = new UI::MediaElement;

			UI::MediaElement* video = NULL;
			video = new UI::MediaElement;

		//	video->set_Source(WSTR("C:/files/mpeg_video2/susi_015.m2v.mpeg"));
			video->set_Source(WSTR("K:/eMule/Incoming/Natalie Imbruglia - Torn.mpg"));
		//	video->set_Source(WSTR("K:/eMule/Incoming/Femjoy - Susanna - Climbing.mpg"));

			// TODO, audio doesn't work
		//	video->set_Source(WSTR("K:/eMule/Incoming/Angela gets fucked Part 1 (RealButts).mpg"));

		//	video->set_Source(WSTR("K:/eMule/Incoming/Femjoy Holy Nature.mpg"));

		//	video->set_Source(WSTR("K:/Files/IFF-ANIM/STEELWOM.ANI"));

		//	video->set_Source(WSTR("K:/Files/IFFANIM/Voyager/Voyager.sndanim"));

			UI::MediaPlayer* ctl = new UI::MediaPlayer(dynamic_cast<MediaShow::IMediaSeeking*>(video->get_FilterGraph()), video);

			set_Content(ctl);
		}
		else if (whatmode == 6)
		{
			CoInitialize(NULL);

			IWiaDevMgr* pWiaDevMgr = NULL;
			IWiaDevMgr2* pWiaDevMgr2 = NULL;

			HRESULT hr;

			if (false)
			{
	//XP or earlier:
				hr = CoCreateInstance(CLSID_WiaDevMgr, NULL, CLSCTX_LOCAL_SERVER, IID_IWiaDevMgr, (void**)&pWiaDevMgr);
			}
			else
			{
	        //Vista or later:
				hr = CoCreateInstance(CLSID_WiaDevMgr2, NULL, CLSCTX_LOCAL_SERVER, IID_IWiaDevMgr2, (void**)&pWiaDevMgr2); 
			}

			IEnumWIA_DEV_INFO* pEnum;
			hr = pWiaDevMgr2->EnumDeviceInfo(0, &pEnum);

			if (SUCCEEDED(hr))
			{
				pEnum->Reset();

				BSTR deviceID;

				IWiaPropertyStorage* elt;
				ULONG fetched;
				while (pEnum->Next(1, &elt, &fetched) == S_OK)
				{
					/*
					ULONG count;
					elt->GetCount(&count);

					PROPID props[1] =
					{
						WIA_DIP_DEV_ID
						//WIA_DPS_DEVICE_ID
					};
					LPWSTR names[1] = {0};

				//	hr = elt->ReadPropertyNames(1, props, names);
*/

					PROPSPEC propspec[2];

					propspec[0].ulKind = PRSPEC_PROPID;
					propspec[0].propid = WIA_DIP_DEV_ID;

					propspec[1].ulKind = PRSPEC_PROPID;
					propspec[1].propid = WIA_DIP_DEV_NAME;

					PROPVARIANT propvar[2] = {0};

					hr = elt->ReadMultiple(2, propspec, propvar);

					if (propvar[0].vt == VT_BSTR)
					{
						TRACE("%S\n", propvar[0].bstrVal);
					}
					if (propvar[1].vt == VT_BSTR)
					{
						TRACE("%S\n", propvar[1].bstrVal);
					}


					deviceID = SysAllocString(propvar[0].bstrVal);

					//CoTaskMemFree(names[0]);
					FreePropVariantArray(2, propvar);

					elt->Release();
				}

				pEnum->Release();

				IWiaItem2* pWiaItem2;
			//	pWiaDevMgr2->GetImageDlg(0, deviceID, GetHwnd(), NULL, NULL, 
				pWiaDevMgr2->CreateDevice(0, deviceID, &pWiaItem2);

				IWiaItem2* pWiaChildItem2;
				LONG numFiles = 0;
				BSTR* files = NULL;
				hr = pWiaItem2->DeviceDlg(0, NULL, SysAllocString(L"C:\\mmstudio"), SysAllocString(L"test"), &numFiles, &files, &pWiaChildItem2);
			//	hr = pWiaItem2->DeviceDlg(0, NULL, NULL, NULL, NULL, NULL, &pWiaChildItem2);

				if (pWiaChildItem2)
				{
					LONG lItemType = 0;
					hr = pWiaChildItem2->GetItemType(&lItemType);

					IWiaTransfer* pWiaTransfer = NULL;
					hr = pWiaChildItem2->QueryInterface(IID_IWiaTransfer,(void**)&pWiaTransfer);

					if (pWiaTransfer)
					{
						WiaTransferCallback* pCallback = new WiaTransferCallback(this);
						pCallback->AddRef();

						if (lItemType & WiaItemTypeTransfer)
						{
							if (lItemType & WiaItemTypeFile )
							{
								pWiaTransfer->Download(0, pCallback);
							}
						}

						pWiaTransfer->Release();
					}

					pWiaChildItem2->Release();
				}
			//	IEnumWiaItem2* pEnumWiaItem2;
			//	pWiaItem2->EnumChildItems(&pEnumWiaItem2);
			}
		}
		else if (whatmode == 7)
		{
			CoInitialize(NULL);

			UI::DockPanel* panel = new UI::DockPanel;
			{
				UI::DockPanel* menubar = new UI::DockPanel;
				UI::DockPanel::SetDock(menubar, DockPanel::Top);

				UI::MenuItem* menu0 = new UI::MenuItem(WSTR("File"));
				{
					UI::MenuItem* submenu0 = new UI::MenuItem(WSTR("Open"), ApplicationCommands::get_Open());
					menu0->get_Items()->Add(submenu0);
				}

				UI::MenuItem* menu1 = new UI::MenuItem(WSTR("Import"));
				EnumWIADevices(menu1);

				/*
				UI::MenuItem* menu2 = new UI::MenuItem(WSTR("Layer"));
				{
					UI::MenuItem* submenu0 = new UI::MenuItem(WSTR("Add Mask"), s_LayerAddMaskCommand);
					menu1->get_Items()->Add(submenu0);
				}
				*/

				menubar->AddChild(menu0);
				menubar->AddChild(menu1);

				panel->AddChild(menubar);
			}

			{
				vector<ClassType*> toolTypes;
				GetDerived((ClassType*)typeid(ImageTool).GetType(), toolTypes);

				StackPanel* toolPanel = new StackPanel;
				panel->AddChild(toolPanel);

				for (int i = 0; i < toolTypes.size(); i++)
				{
					if (toolTypes[i]->m_derived.size() == 0)
					{
						Object* tool = newobj(toolTypes[i]);

						Button* button = new Button(toolTypes[i]->m_name->ToStringW());
						button->set_Command(s_SetToolCommand);
						button->set_CommandParameter(tool);

						if (toolTypes[i] == typeid(MoveTool).GetType())
						{
							m_activeTool = dynamic_cast<ImageTool*>(tool);
						}

						toolPanel->AddChild(button);
					}
				}
			}

			m_pWindowContainer = new UI::ChildWindowContainer;
		//	BitmapEditor* visual = new BitmapEditor;
		//	visual->m_bitmap = NULL;

			panel->AddChild(m_pWindowContainer);

			get_CommandBindings()->Add(new UI::CommandBinding(ApplicationCommands::get_Open(), bind1st_of_3(mem_fun2(&BrowserFrame::OnFileOpen), this), bind1st_of_3(mem_fun2(&BrowserFrame::OnCanFileOpen), this)));

			get_CommandBindings()->Add(new UI::CommandBinding(s_ImportFromWIACommand, bind1st_of_3(mem_fun2(&BrowserFrame::OnImportFromWIA), this), bind1st_of_3(mem_fun2(&BrowserFrame::OnCanFileOpen), this)));

			get_CommandBindings()->Add(new UI::CommandBinding(s_SetToolCommand, bind1st_of_3(mem_fun2(&BrowserFrame::OnSetTool), this), bind1st_of_3(mem_fun2(&BrowserFrame::OnCanSetTool), this)));

			set_Content(panel);
		}

		set_Width(800);
		set_Height(660);
	}
	else
	{
	//new Mpeg4::MP4VConfig;

	m_edit = NULL;
	m_spreadSheetCtl = NULL;

#if WIN32

//	LDraw::_TextureBrush* p;
//	LDraw::TextureBrush tbrush;
//	LDraw::Brush brush(tbrush);

#if 0
	if (false)
	{
		TypeArchive ar(TypeArchive::Mode_Load, new FileByteStream(ASTR("C:/test.typeinfo"), FileMode_Read));
	//	ar.m_bIsStoring = false;

		int ntypes;
		ar >> ntypes;

		for (int i = 0; i < ntypes; i++)
		{
			NamedType* pType;
			ar >> pType;

			TRACE("%s\n", pType->m_qname->c_str());

			NamedType * pType2 = pD->LookupNamedType(pType->m_qname);
			if (pType2)
			{
				if (!pType2->Equals(*pType))
				{
					//pType2->Equals(*pType);

					//MessageBoxA(NULL, pType2->m_name.c_str(), "", MB_OK);
				}
			}
		}
	}
#endif

#if 0
	if (true)
	{
		CGlobal* pGlobal = new CGlobal;

		cpp::cpp_compile(pGlobal, "C:/test.cpp", "C:/test.o", 2);

		TypeArchive ar(TypeArchive::Mode_Store, new FileByteStream(StringA("C:/test.typeinfo"), FileMode_Write));

		ar << (int)pGlobal->m_alltypes.size();

		typemap::iterator it = pGlobal->m_alltypes.begin();
		while (it != pGlobal->m_alltypes.end())
		{
			ar << (*it).second;

			++it;
		}

		delete pGlobal;
	}
#endif

#if 0
	if (false)
	{
		// Write bootstrap

		ByteIOStream ar(new FileByteStream(StringA("C:/bootstrap.typeinfo"), FileMode_Write));

		ar.m_bIsStoring = true;

		if (true)
		{
			Class* pClass0 = pD->LookupNamedType("Class")->GetClass();
		//	ar << pClass0;
			ar.MapClass(pClass0);
			pClass0->Store(ar);

			/*
			Class* pClass1 = pD->LookupNamedType("PrimitiveType")->GetClass();
			ar << pClass1;

			Class* pClass2 = pD->LookupNamedType("CFunction")->GetClass();
			ar << pClass2;

			Class* pClass3 = pD->LookupNamedType("_Object")->GetClass();
			ar << pClass3;

			Class* pClass4 = pD->LookupNamedType("IRefCounted")->GetClass();
			ar << pClass4;

			Class* pClass5 = pD->LookupNamedType("_ObjectImpl")->GetClass();
			ar << pClass5;

			Class* pClass6 = pD->LookupNamedType("_Type")->GetClass();
			ar << pClass6;

			Class* pClass7 = pD->LookupNamedType("NamedType")->GetClass();
			ar << pClass7;

			Class* pClass8 = pD->LookupNamedType("CVType")->GetClass();
			ar << pClass8;

			Class* pClass9 = pD->LookupNamedType("ISerializable")->GetClass();
			ar << pClass9;

			Class* pClass10 = pD->LookupNamedType("PointerType")->GetClass();
			ar << pClass10;

			Class* pClass11 = pD->LookupNamedType("ModifierType")->GetClass();
			ar << pClass11;

			Class* pClass12 = pD->LookupNamedType("EnumType")->GetClass();
			ar << pClass12;
			*/
		}
		else
		{
			Class* pClass0 = pD->LookupNamedType("CVType")->GetClass();
			ar.MapClass(pClass0);

			Class* pClass1 = pD->LookupNamedType("PrimitiveType")->GetClass();
			ar.MapClass(pClass1);

			Class* pClass2 = pD->LookupNamedType("CFunction")->GetClass();
			ar.MapClass(pClass2);

			Class* pClass3 = pD->LookupNamedType("_Object")->GetClass();
			ar.MapClass(pClass3);

			Class* pClass4 = pD->LookupNamedType("IRefCounted")->GetClass();
			ar.MapClass(pClass4);

			Class* pClass5 = pD->LookupNamedType("_ObjectImpl")->GetClass();
			ar.MapClass(pClass5);

			Class* pClass6 = pD->LookupNamedType("_Type")->GetClass();
			ar.MapClass(pClass6);

			Class* pClass7 = pD->LookupNamedType("NamedType")->GetClass();
			ar.MapClass(pClass7);

			Class* pClass8 = pD->LookupNamedType("Class")->GetClass();
			ar.MapClass(pClass8);

			Class* pClass9 = pD->LookupNamedType("ISerializable")->GetClass();
			ar.MapClass(pClass9);

			Class* pClass10 = pD->LookupNamedType("PointerType")->GetClass();
			ar.MapClass(pClass10);

			Class* pClass11 = pD->LookupNamedType("ModifierType")->GetClass();
			ar.MapClass(pClass11);

			Class* pClass12 = pD->LookupNamedType("EnumType")->GetClass();
			ar.MapClass(pClass12);

			pClass9->Store(ar);
			pClass3->Store(ar);
			pClass5->Store(ar);

			pClass0->Store(ar);
			pClass1->Store(ar);
			pClass2->Store(ar);
			pClass4->Store(ar);
			pClass6->Store(ar);
			pClass7->Store(ar);
			pClass8->Store(ar);
			pClass10->Store(ar);
			pClass11->Store(ar);
			pClass12->Store(ar);
		}
	}

	if (false)
	{
		ByteIOStream ar(new FileByteStream(StringA("C:/bootstrap.typeinfo"), FileMode_Read));
		ar.m_bIsStoring = false;

		if (false)
		{
			for (int i = 0; i < 12; i++)
			{
				Class* pClass;
				ar >> pClass;
			}
		}
		else
		{
			Class* pClass0 = new Class;
			ar.MapClass(pClass0);

			/*
			Class* pClass1 = new Class;
			ar.MapClass(pClass1);

			Class* pClass2 = new Class;
			ar.MapClass(pClass2);

			Class* pClass3 = new Class;
			ar.MapClass(pClass3);

			Class* pClass4 = new Class;
			ar.MapClass(pClass4);

			Class* pClass5 = new Class;
			ar.MapClass(pClass5);

			Class* pClass6 = new Class;
			ar.MapClass(pClass6);

			Class* pClass7 = new Class;
			ar.MapClass(pClass7);

			Class* pClass8 = new Class;
			ar.MapClass(pClass8);

			Class* pClass9 = new Class;
			ar.MapClass(pClass9);

			Class* pClass10 = new Class;
			ar.MapClass(pClass10);

			Class* pClass11 = new Class;
			ar.MapClass(pClass11);

			Class* pClass12 = new Class;
			ar.MapClass(pClass12);
			*/

			pClass0->Load(ar);
			TRACE("%s\n", pClass0->m_qname.c_str());

			/*
			pClass1->Load(ar);
			TRACE("%s\n", pClass1->m_qname.c_str());

			pClass2->Load(ar);
			TRACE("%s\n", pClass2->m_qname.c_str());

			pClass3->Load(ar);
			TRACE("%s\n", pClass3->m_qname.c_str());

			pClass4->Load(ar);
			TRACE("%s\n", pClass4->m_qname.c_str());

			pClass5->Load(ar);
			TRACE("%s\n", pClass5->m_qname.c_str());

			pClass6->Load(ar);
			TRACE("%s\n", pClass6->m_qname.c_str());

			pClass7->Load(ar);
			TRACE("%s\n", pClass7->m_qname.c_str());

			pClass8->Load(ar);
			TRACE("%s\n", pClass8->m_qname.c_str());

			pClass9->Load(ar);
			TRACE("%s\n", pClass9->m_qname.c_str());

			pClass10->Load(ar);
			TRACE("%s\n", pClass10->m_qname.c_str());

			pClass11->Load(ar);
			TRACE("%s\n", pClass11->m_qname.c_str());

			pClass12->Load(ar);
			TRACE("%s\n", pClass12->m_qname.c_str());
			*/
		}
	}
#endif

#endif

	/*
	{
		list<int> mylist;

		mylist.push_back(0);
		mylist.push_back(1);
		mylist.push_back(2);

		list<int>::iterator it = mylist.begin();

		while (it != mylist.end())
		{
			TRACE("%d\n", (*it));

			++it;

		}
	}
	*/


	{
		//mymap[7] = 8;

	//	print(0, mymap.root);


	}

	UI::DockPanel* pPanel = new UI::DockPanel;

	UI::CUIDockBar* pDockbar = new UI::CUIDockBar;

	pPanel->AddChild(pDockbar);


	m_pWindowContainer = new ChildWindowContainer;

#if 0
//	const char* url = "http://www.lerstad.com";


	{
		/*
		const char* p = url;

		std::string scheme;
		std::string server;
		std::string port;

		std::string part;

		while (isalnum(*p))
		{
			if (*p == ':')
			{
				scheme = 
				break;
			}

			part += *p;
			p++;
		}
		*/
	}

#if 0
	if (false)
	{
		DocumentFrame* pBrowser = new DocumentFrame;
		Binding* binder = new Binding;
		binder->BindToObject(WSTR("http://www.w3.org"), pBrowser);
//		binder->BindToObject(WSTR("c:\\mmstudio\\help\\w3.html"), pBrowser);

		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(new Length(500, Length::UnitAbsolute));
		pWindow->put_Height(new Length(300, Length::UnitAbsolute));

		pWindow->put_Content(pBrowser);
		m_pWindowContainer->AddChild(pWindow);

		put_Width(new Length(400, Length::UnitAbsolute));
		put_Height(new Length(300, Length::UnitAbsolute));
	}
#endif

#endif

#if 0
	if (false)
	{
		ImageEdit::CImageDocument* doc = new ImageEdit::CImageDocument;
	//	doc->Load(WSTR("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\test.pcx"));
		doc->Load(WSTR("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.jpg"));

		UI::ToolBar* toolbar = new UI::ToolBar;
		{
			//ClassType* pType = pD->LookupNamedType(new StringA("ImageEdit::IImageTool"))->GetClass();
			ClassType* pType = typeid(ImageEdit::IImageTool).GetType()->GetClass();

			vector<ClassType*> list;
			GetDerived(pType, list);

			for (int i = 0; i < list.GetSize(); i++)
			{
				ClassType* pDerived = list[i];
				if (pDerived->m_derived.GetSize() == 0)
				{
					ImageEdit::IImageTool *pTool = (ImageEdit::IImageTool*)DynamicCast(newobj(pDerived), pDerived, pType);

					//Image* image = new Image(new UI::FileImageSource(WSTR("C:/move.png")));
					UI::TextString* visual = new UI::TextString(pDerived->get_Name()->ToStringW());
					Button* pButton = new Button(visual);

					ToolListener* pTL = new ToolListener;
					pTL->m_doc = doc;
					pTL->m_tool = pTool;

					ASSERT(0);
					//pButton->addEventListener(WSTR("click"), pTL, false);

					toolbar->AddRChild(pButton);
				}
			}

			/*
			{
				Image* image = new Image(new UI::FileImageSource(WSTR("C:/move.png")));
				toolbar->AddRChild(new Button(image));
			}

			{
				Image* image = new Image(new UI::FileImageSource(WSTR("C:/magicwand.png")));
				toolbar->AddRChild(new Button(image));
			}
			*/
		}
	//	DockControlBar(toolbar, &LDraw::Rect(0, 0, 40, 40));
		pDockbar->DockControlBar(toolbar);

		ImageEdit::CImageView* view = new ImageEdit::CImageView;
		view->m_document = doc;
		view->m_pActiveLayer = new ImageEdit::CPImageLayerUnknown;
		view->m_pActiveLayer->m_pView = view;
		view->m_pActiveLayer->m_layerUnknown = doc->m_imageLayerGroup->m_subLayers[0];

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(500);
		pWindow->set_Height(300);

		if (true)
		{
		//	EditTransform* pScroller = new EditTransform;
			ScrollViewer* pScroller = new ScrollViewer;
			{
				pScroller->set_Content(view);
			}
			pWindow->set_Content(pScroller);
		}
		else
		{
			pWindow->set_Content(view);
		}

	//	pWindow->put_Content(view);

		m_pWindowContainer->AddChild(pWindow);

		set_Width(400);
		set_Height(300);
	}
#endif

#if 0
	/*
#if WIN32
	if (false)
	{
		SWF::Encoder* pEncoder = new SWF::Encoder;

		ByteStreamWriter* pStream = new ByteStreamWriter("C:/files/SWF/writertest.swf");

		pEncoder->m_stream = pStream;
		pEncoder->m_stream->AddRef();

		SWF::Movie movie;
		movie.New();
		movie.SetFrameSize(320, 200);

		pEncoder->WriteHeader();
		pEncoder->WriteMovieHeader(&movie);

		SWF::ShapeCharacter shape(new SWF::ShapeCharacter::_ShapeCharacter);

		shape.get_p()->m_fillStyles.push_back(SWF::FillStyle(SWF::RGBAColor(0, 0, 0, 255)));
		shape.MoveTo(0, 0);

		pEncoder->DefineShape(3, shape);

		pEncoder->Close();
	}
#endif
	*/

#if WIN32
	if (false)
	{
		PDF::CPDFPDDoc doc;

		doc.Create();
		doc.CreatePage(-1, 0, 0, 400, 400);
		doc.Save("C:/files/PDF/test.pdf");
	}
#endif

#endif

#if WIN32
	if (false)
	{
		MetafileVisual* ctl = new MetafileVisual;
	//	ctl->m_commands = LDraw::Commands;
		ctl->m_originalRect = LDraw::RectD(0, 800, 800, -800);

		PDF::CPDFPDDoc doc;
	//	doc.Read("C:/files/PDF/test.pdf");
	//	doc.Read("C:/fileformatspecs/idl-wsdl.pdf");

	//	doc.Read("c:/devdownloads/ISO_IEC_10021-6_1996_Amd_1_1998_PDF_version_(en)_CPDF.PDF");

		doc.Read(ASTR("C:\\FileFormatSpecs\\575943\\ISO_IEC_14496-1_2001_PDF_version_(en)_034903_CPDF_2.pdf"));

	//	doc.Read("C:\\idl_encrypted.pdf");

		PDF::CPDFCosDict* pCatalog = doc.GetCosDoc()->GetCatalog();
		PDF::CPDFCosDict* pPages = dynamic_cast<PDF::CPDFCosDict*>(pCatalog->CosDictGet(ASTR("Pages")));
		if (pPages)
		{
			PDF::CPDFCosArray* pKids = dynamic_cast<PDF::CPDFCosArray*>(pPages->CosDictGet(ASTR("Kids")));

			PDF::CPDFCosDict* pPage = dynamic_cast<PDF::CPDFCosDict*>(pKids->GetItem(0));

			PDF::CPDFCosDict* pResources = dynamic_cast<PDF::CPDFCosDict*>(pPage->CosDictGet(ASTR("Resources")));

			PDF::CPDFCosObj* pContents = pPage->CosDictGet(ASTR("Contents"));

			ByteStreamWriter* file = new ByteStreamWriter(ASTR("c:/stream_temp"));
		//	file->AddRef();

			TRY
			{

				PDF::CPDFCosArray* pContentsArray = dynamic_cast<PDF::CPDFCosArray*>(pContents);
				if (pContentsArray)
				{
					for (int i = 0; i < pContentsArray->GetLength(); i++)
					{
						PDF::CPDFCosStream* pContent = dynamic_cast<PDF::CPDFCosStream*>(pContentsArray->GetItem(i));

						System::IO::ISequentialByteStream* pStream = pContent->OpenStream();
						StreamCopy(file, pStream);
					}
				}
				else
				{
					PDF::CPDFCosStream* pContent = dynamic_cast<PDF::CPDFCosStream*>(pContents);

					System::IO::ISequentialByteStream* pStream = pContent->OpenStream();
					StreamCopy(file, pStream);
				}
			}
			CATCH(int)
			{
				file->Close();
			//	exit(1);
				throw -1;
			}

			file->Close();

			std::FILE* fp2 = std::fopen("c:/stream_temp", "rb");

			PDF::CPDFCosDoc doc;
			doc.m_fp = fp2;

			RenderContent(doc, pResources, ctl->m_commands);

			std::fclose(fp2);
		}

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(600);
		pWindow->set_Height(500);

	//	ScrollViewer* pScroller = new ScrollViewer;
		{
	//		pScroller->put_Content(ctl);
		}
		pWindow->set_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}

#endif

#if 0
#if 0

	if (false)
	{
		SWF::Player* swf = new SWF::Player;
	//	swf->m_stream = new FileByteStream("C:/flashsaver/numanuma.swf");
	//	swf->m_stream = new FileByteStream("C:/flashsaver/768x150_aqualand_master.swf");
	//	swf->m_stream = new FileByteStream("C:/flashsaver/vg_180x60.swf");
	//	swf->m_decoder = new LSWF::Decoder(new LSWF::FormatStream(new FileByteStream("D:/flashsaver/gauge.swf")));
		FileByteStream* file;
		TRY
		{

#if WIN32
		file = new FileByteStream("C:/lm_test.swf");
	//	file = new FileByteStream("C:/test2.swf");
		//file = new FileByteStream("C:/files/swf/test2.swf");
	//	file = new FileByteStream("C:/files/SWF/writertest.swf");

#else
		file = new FileByteStream("WinHD_C:/test.swf");
#endif
		}
		CATCH(int)
		{
			printf("Failed to open file");
			file = NULL;
		}

		if (file)
		{
			//try
			{
				swf->m_decoder = new SWF::Decoder(new SWF::FormatStream(file));

				SWF::Movie movie;
				movie.New();

				swf->m_decoder->ReadHeader();
				swf->m_decoder->ReadMovieHeader(&movie);

				swf->SetMovie(movie);
				swf->Play();
			}
			/*
			catch(int)
			{
				printf("Failed to parse swf");
			}
			*/

			{
				ChildWindow* pWindow = new ChildWindow;
				pWindow->put_Width(Length(600));
				pWindow->put_Height(Length(500));

				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->put_Content(swf);
				}
				pWindow->put_Content(pScroller);
				//	pWindow->put_Content(m_callStackWnd);

				pWindow->put_TitleText(WSTR("SWF"));

				m_pWindowContainer->AddChild(pWindow);
			}
		}
	}
#endif

#if 0
	{
		FileByteStream stream;

		LMedia::MPEG4Movie* pMovie = new LMedia::MPEG4Movie;
#if WIN32
		stream.Open("C:/files/mpeg4/LuckyStr1948_2_256kb.mp4");
		HRESULT hr = pMovie->ReadFile(&stream, 0, 0xfffffffffff);
#else
		stream.Open("WinHD_C:/files/mpeg4/LuckyStr1948_2_256kb.mp4");
		HRESULT hr = pMovie->ReadFile(&stream, 0, 0xfffffffffffLL);
#endif

		for (int i = 0; i < pMovie->m_tracks.GetSize(); i++)
		{
			LMedia::CTrack* track = pMovie->m_tracks[i];
			if (track->m_decoder)
			{
				track->m_decoder->m_stream->Seek(track->m_samples[0].m_fileOffset, STREAM_SEEK_SET);
				LMedia::CBitStream bitstream(track->m_decoder->m_stream);
				LMedia::CBitStream* pBitStream = &bitstream;
				bitstream.m_bitstreamSize = track->m_samples[0].m_fileSize*8;

				int start_code = LMedia::next_start_code(pBitStream);

				if (start_code == 0x1b6)	// vop_start_code (Video Object Plane)
				{
					LMedia::CVideoObjectPlane* vop = track->m_decoder->ReadFrame(pBitStream);
				}
			}
		}

		printf("hr=%d\n", hr);
	}
#endif

	#endif

#if WIN32
	//Loader* ploader = NULL;
	if (false)
	{
		MetafileVisual* ctl = new MetafileVisual;

	//	FileByteStream data("C:/files/wmf/acordfrm.wmf");

	//	FileByteStream data("C:\\Program Files\\Microsoft Office\\CLIPART\\PUB60COR\\J0185828.WMF");

		FileByteStream data(ASTR("C:/files/emf/path.emf"));
	//	FileByteStream data("C:/test.emf");

		wmf::MetafileLoader* loader = new wmf::MetafileLoader;
		//loader.pCommands = new LDraw::Commands;
		loader->Load(&data);
		ctl->m_commands = loader->pCommands;

	//	ploader = loader;

		loader->GetRect(&ctl->m_originalRect);

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(200);
		pWindow->set_Height(200);

	//	ScrollViewer* pScroller = new ScrollViewer;
		{
	//		pScroller->put_Content(ctl);
		}
		pWindow->set_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);

	}
#endif

#if WIN32

	if (false)
	{
		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(300);
		pWindow->set_Height(300);

			EditTransform* pEdit = new EditTransform;

			pEdit->m_ChildTransform = new LDraw::Matrix3f(LDraw::matrix3f::getScale(1, 1) * LDraw::matrix3f::getRotate(90) * LDraw::matrix3f::getTranslate(80, 0));
			pEdit->m_childrenTransformMatrix = pEdit->m_ChildTransform;


			{
				UI::ScrollBar* ctl = new UI::ScrollBar(UI::Orientation_Horizontal);
				ASSERT(0);
				//ctl->SetInfo(0, 10, 1);

				pEdit->set_Content(ctl);
			}
			pWindow->set_Content(pEdit);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

#if 0

#if WIN32
	if (false)
	{
		EditAffineTransformImage* ctl = new EditAffineTransformImage;
		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(300));
		pWindow->put_Height(Length(300));

		if (true)
		{
			EditTransform* pScroller = new EditTransform;
			{
				pScroller->put_Content(ctl);
			}
			pWindow->put_Content(pScroller);
		}
		else
		{
			pWindow->put_Content(ctl);
		}

		pWindow->put_TitleText(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

#endif

#if 1
	if (false)
	{
	#if 1
		FileByteStream data(WSTR("C:/files/excel/Book2.xls"));

		OLE::Storage stg;
		stg.Open(&data);
	#endif

		Workbook* pWorkbook = m_pWorkbook;

		for (int i = 0; i < 1/*pWorkbook->m_sheets.size()*/; i++)
		{
			Sheet* pSheet = pWorkbook->m_sheets[i];
			/*
			{
				for (int i = 0; i < 10; i++)
				{
					pSheet->m_columns.push_back(new Column());
				}

				for (i = 0; i < 10; i++)
				{
					Row* pRow = new Row();
					pSheet->m_rows.push_back(pRow);

					for (int j = 0; j < 10; j++)
					{
						pRow->m_cells[j] = new Cell;
					}
				}
			}
			*/

			UI::DockPanel* panel = new UI::DockPanel;

			m_edit = new UI::TextEdit;
			panel->AddChild(m_edit);

			SpreadSheetControl* ctl = new SpreadSheetControl;
			ctl->m_pSheet = pSheet;
			//ctl->m_pFrame = this;
			m_spreadSheetCtl = ctl;

			panel->AddChild(ctl);

			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(500);
			pWindow->set_Height(500);

		//	ScrollViewer* pScroller = new ScrollViewer;
			{
		//		pScroller->put_Content(ctl);
			}
			pWindow->set_Content(panel);//pScroller);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->set_Title(WSTR("Test"));

			m_pWindowContainer->AddChild(pWindow);
		}
	}
#endif

	EditLines* editctl = NULL;
	if (false)
	{
		if (true)
		{
			editctl = new EditLines;
			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(500);
			pWindow->set_Height(500);

			ScrollViewer* pScroller = new ScrollViewer;
			{
				pScroller->set_Content(editctl);
			}
			pWindow->set_Content(pScroller);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->set_Title(WSTR("Test"));

			m_pWindowContainer->AddChild(pWindow);
		}

		if (true)
		{
			ColorPickerRGB* ctl = new ColorPickerRGB;
			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(200);
			pWindow->set_Height(200);

		//	ScrollViewer* pScroller = new ScrollViewer;
			{
		//		pScroller->put_Content(ctl);
			}
			pWindow->set_Content(ctl);//pScroller);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->set_Title(WSTR("RGB"));

			m_pWindowContainer->AddChild(pWindow);
		}
	}

#if 0
	if (false)
	{
		DecodeDVD();
	}

#if WIN32
	if (false)
	{
		LMedia::JPEGEncoder enc;

		const int width = 64;
		const int height = 32;

		uint8 image[width*height];
		memset(image, 0, width*height);
		/*
		image[0*width+4] = 255;
		image[1*width+4] = 255;
		image[2*width+4] = 255;
		image[3*width+4] = 255;
		*/

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				image[y*width + x] = (x) * 255 * y * 255 / width / height;
			}
		}

		ISequentialByteStream* stream = new ByteStreamWriter("C:/test.jpg");
		stream->AddRef();

		enc.EncodeImage(stream, image, width, height, width);

		stream->Release();
	}
#endif

#if WIN32
	if (false)
	{
			LONGLONG m_freq;
			QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);

				LDraw::Bitmap bitmap(512, 512, RGBAP_32);

				LDraw::GraphicsO* graphicsO = new LDraw::GraphicsO(&bitmap);
				graphicsO->SetDepthBuffer(new uint8[4*512*512]);

				LDraw::GLState serverState = new LDraw::_GLState;
				LDraw::ClientState* clientState = new LDraw::ClientState;

				LDraw::Graphics3DImmediate* pG = new LDraw::Graphics3DImmediate(serverState, clientState, graphicsO);

				pG->glViewport(0, 0, 512, 512);

				pG->glMatrixMode(GL_PROJECTION);
				pG->glLoadIdentity();
				pG->glOrtho(-256, 256, -256, 256, -1, 1);

				pG->glMatrixMode(GL_MODELVIEW);
				pG->glLoadIdentity();

			//	pG->glEnable(GL_DEPTH_TEST);

				int nlines = 8000;

				LONGLONG startCounter;
				QueryPerformanceCounter((LARGE_INTEGER*)&startCounter);

				for (int i = 0; i < nlines; i++)
				{
					pG->glBegin(GL_TRIANGLES);

					pG->glVertexf(-256, -256, 0);
					pG->glVertexf(256, -256, 0);
					pG->glVertexf(256, 256, 0);

					pG->glEnd();
				}

				LONGLONG endCounter;
				QueryPerformanceCounter((LARGE_INTEGER*)&endCounter);

				double dur = (double)(endCounter - startCounter) / m_freq;

				char buf[256];
				sprintf(buf, "triangles per second: %f\n", nlines / dur);
				MessageBox(NULL, buf, "", MB_OK);
	}
#endif

#if 0//WIN32
	if (true)
	{
		Gdiplus::GdiplusStartupInput in;
		ULONG_PTR token;
		Gdiplus::GdiplusStartup(&token, &in, NULL);
	}
#endif

#if 0
	if (true)
	{
		int nlines = 60000;

		if (true)
		{
#define TEST	1

			LONGLONG m_freq;
			QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
			

			Gdiplus::Bitmap bitmap(512, 512);
			{
				Gdiplus::Graphics graphics(&bitmap);
			//	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

				Gdiplus::GraphicsPath path;
				path.AddLine(0, 0, 512, 512);
				path.AddLine(512, 512, 512, 0);
				path.AddLine(512, 0, 0, 512);
				path.AddLine(0, 512, 0, 0);

				Gdiplus::Pen pen(Gdiplus::Color(0,0,0), 8);

				Gdiplus::Font font(L"Courier New", 14, 0, Gdiplus::UnitPixel);
				Gdiplus::SolidBrush brush(Gdiplus::Color(0,0,0));

				LONGLONG startCounter;
				QueryPerformanceCounter((LARGE_INTEGER*)&startCounter);

				for (int i = 0; i < nlines; i++)
				{
#if TEST == 0
					graphics.DrawPath(&pen, &path);
#elif TEST == 1
					graphics.DrawString(L"Hello there, how are you?", 25, &font, Gdiplus::PointF(50, 50), &brush);
#endif
				}
				graphics.Flush(Gdiplus::FlushIntentionSync);

				LONGLONG endCounter;
				QueryPerformanceCounter((LARGE_INTEGER*)&endCounter);

				double dur = (double)(endCounter - startCounter) / m_freq;

				char buf[256];
				sprintf(buf, "lines per second: %f\n", nlines / dur);
				MessageBox(NULL, buf, "Gdiplus", MB_OK);
			}

		}

		if (true)
		{
			LONGLONG m_freq;
			QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
			
			LDraw::Bitmap bitmap(512, 512, RGB_32);
			{
				LDraw::Graphics graphics(new LDraw::GraphicsO(&bitmap));

			//	graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

				LDraw::GraphicsPathF path;
				path.AddMove(0, 0);
				path.AddLine(512, 512);
				path.AddLine(512, 0);
				path.AddLine(0, 512);
				path.AddLine(0, 0);
				LDraw::Pen pen(LDraw::Color(0,0,0), 8);

				LDraw::Font font(L"Courier New", 14/*, Gdiplus::UnitPixel*/);
				LDraw::SolidBrush brush(LDraw::Color(0,0,0));

				LONGLONG startCounter;
				QueryPerformanceCounter((LARGE_INTEGER*)&startCounter);

				for (int i = 0; i < nlines; i++)
				{
#if TEST == 0
					graphics.DrawPath(&pen, &path);
#elif TEST == 1
					graphics.DrawString(L"Hello there, how are you?", 25, &font, LDraw::PointF(50, 50), &brush);
#endif
				}

				LONGLONG endCounter;
				QueryPerformanceCounter((LARGE_INTEGER*)&endCounter);

				double dur = (double)(endCounter - startCounter) / m_freq;

				char buf[256];
				sprintf(buf, "lines per second: %f\n", nlines / dur);
				MessageBox(NULL, buf, "LDraw", MB_OK);
			}

		}
	}
#endif
#endif

#if 0//WIN32
	if (false)
	{
		LXmlEdit::CTransition* pTransition = g_transitions->m_items[0];
		LXmlEdit::CSMILTransition* pMapping = pTransition->m_mapping[0];
		LXmlEdit::CTransitionSettingsDlg* dlg = new LXmlEdit::CTransitionSettingsDlg(pMapping);
		dlg->Init();

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(new Length(300));
		pWindow->set_Height(new Length(300));

		pWindow->set_Content(dlg);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_TitleText(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

#if 0

	if (false)
	{
#if 0
		LDrawTest* ctl = new LDrawTest;

		ctl->m_bitmap = LDraw::Bitmap(WSTR("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\sunset.pcx"));

		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(300));
		pWindow->put_Height(Length(300));

		pWindow->put_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->put_TitleText(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
#endif
	}

#if WIN32
	if (false)
	{
		HTTPListenerSocket* pSocket = new HTTPListenerSocket;
		pSocket->Create(80);
		pSocket->Listen();
	}
#endif

#endif

#if WIN32
	if (false)
	{
		//DirectoryObject* pDir = new DirectoryObject("C:\\Documents and Settings\\Sigurd Lerstad\\My Documents\\My Pictures");
	//	DirectoryObject* pDir = new DirectoryObject("C:/files/mpeg_video2");
	//	DirectoryObject* pDir = new DirectoryObject("C:/fileformatspecs");
	//	DirectoryObject* pDir = new DirectoryObject("C:/files/mods");
#if WIN32
	//	DirectoryObject* pDir = new DirectoryObject("C:/files/sounds/voc");
		FileObject* pFile = new FileObject;
		pFile->m_Fullname = ASTR("C:/files");
		ASSERT(0);
		DirectoryObject* pDir = NULL;//new DirectoryObject();//"C:/files");
		pDir->set_Viewable(pFile);
	//	DirectoryObject* pDir = new DirectoryObject("/");	// root
#else
		DirectoryObject* pDir = new DirectoryObject("WinHD_C:/files");
	//	DirectoryObject* pDir = new DirectoryObject("/");	// root
#endif

		UI::ScrollViewer* pScroller = new UI::ScrollViewer;

		ViewOfCollection* ctl = new ViewOfCollection();

		ctl->set_Viewable(pDir);

		pScroller->set_Content(ctl);

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(200);
		pWindow->set_Height(200);

		pWindow->set_Content(pScroller);
		//	pWindow->put_Content(m_callStackWnd);

	//	ctl->m_pCanvas = pCanvas;

		pWindow->set_Title(pDir->m_dirName->ToStringW());

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

#if 0

	if (false)
	{
		ThumbnailViewer* ctl = new ThumbnailViewer;

		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(200));
		pWindow->put_Height(Length(200));

		pWindow->put_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->put_TitleText(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}

	if (false)
	{
		DisplacementMap* map = new DisplacementMap;

		map->m_in1 = video;
		map->m_in2 = video;

		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(200));
		pWindow->put_Height(Length(200));

		pWindow->put_Content(map);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->put_TitleText(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}

#endif

#if WIN32
	UI::Media3D::Group* group;

	if (true)
	{
		UI::Grid* panel = new UI::Grid;

		UI::Media3D::Document3D* document3d = new UI::Media3D::Document3D;
		{
			DX::xfileparser standard_templates;
			{
				FileByteStream* stream = new FileByteStream(WSTR("C:/standard_templates.x"));
				standard_templates.ParseX(stream);
				stream->Close();
			}

			if (false)
			{
			//	UI::Media3D::C3DSLoader* loader = new UI::Media3D::C3DSLoader;
			//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/tiny.x"));
			//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/spaceship 2.x"));
			//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/airplane 2.x"));
			//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/tiger.x"));

				FileByteStream* stream = new FileByteStream(WSTR("C:/MMStudio/Scenes/Test.x"));

				DX::xfileparser parser;
				parser.m_templates = standard_templates.m_templates;
				parser.ParseX(stream);
				stream->Close();

			//	Convert(parse.m_objects);

				group = new UI::Media3D::Group;
				UI::Media3D::Object3DCollection* children = new UI::Media3D::Object3DCollection;

				UI::Media3D::convert(document3d, parser.m_objects, children);

				for (int i = 0; i < document3d->m_references.size(); i++)
				{
					document3d->m_references[i]->m_object = document3d->m_namedObjects[document3d->m_references[i]->m_name];
					document3d->m_references[i]->m_object->m_references.Add(document3d->m_references[i]);
				}

				group->m_Children = children;
				document3d->m_object = group;

				document3d->SetCurrentTime(0);
			}
#if 1
			else if (false)
			{
				UI::Media3D::C3DSLoader loader;// = new UI::Media3D::C3DSLoader;
				FileByteStream stream(WSTR("c:/mmstudio/scenes/test.3ds"));

				group = new UI::Media3D::Group;
				UI::Media3D::Object3DCollection* children = new UI::Media3D::Object3DCollection;
				group->m_Children = children;

				loader.LoadInto(&stream, group);

				document3d->m_object = group;

				document3d->SetCurrentTime(0);
			}
			else if (true)
			{
				x3d::VRMLLoader loader;
				x3d::Scene* x3dscene = loader.Load(WSTR("C:/mmstudio/scenes/test2.wrl"));
				if (x3dscene)
				{
					x3d::MFNode* rootNodes = x3dscene->getRootNodes();

					group = new UI::Media3D::Group;
					UI::Media3D::Object3DCollection* children = new UI::Media3D::Object3DCollection;
					group->m_Children = children;

					Media3D::convert(rootNodes, children);

					document3d->m_object = group;

					document3d->SetCurrentTime(0);
				}
			}
#endif
			else
			{
				ASSERT(0);
#if 0
				XmlData::Document* document = new XmlData::Document;
				document->load(WSTR("C:\\object3d.lxui"));

				const cpp::_Type* pReturnType;
				void* object = CreateElement(pD->LookupNamedType("UI::Media3D::Object3D"), document->get_documentElement(), &pReturnType);

				document3d->m_object = (UI::Media3D::Group*)DynamicCast(object, pReturnType, typeid(UI::Media3D::Object3D));

				group = document3d->m_object;
#endif
			}

		//	document3d->MakeList();
		}

		{
			UI::Media3D::X3DViewer2* ctl = new UI::Media3D::X3DViewer2;
			//ctl->m_document = document3d;
			{
				UI::Media3D::View3D* view0 = new UI::Media3D::View3D(document3d);
				view0->m_display = 1;
				document3d->m_views[0] = view0;
				ctl->set_Content(view0);
			}

			Grid::SetColumn(ctl, 0);
			Grid::SetRow(ctl, 0);

			panel->AddChild(ctl);
		}

		{
			UI::Media3D::X3DViewer2* ctl = new UI::Media3D::X3DViewer2;
			//ctl->m_document = document3d;
			{
				UI::Media3D::View3D* view1 = new UI::Media3D::View3D(document3d);
				view1->m_display = 2;
				document3d->m_views[1] = view1;
				ctl->set_Content(view1);
			}

			Grid::SetColumn(ctl, 1);
			Grid::SetRow(ctl, 0);

			panel->AddChild(ctl);
		}

		{
			UI::Media3D::X3DViewer2* ctl = new UI::Media3D::X3DViewer2;
			//ctl->m_document = document3d;
			{
				UI::Media3D::View3D* view2 = new UI::Media3D::View3D(document3d);
				view2->m_display = 3;
				document3d->m_views[2] = view2;
				ctl->set_Content(view2);
			}
			Grid::SetColumn(ctl, 0);
			Grid::SetRow(ctl, 1);

			panel->AddChild(ctl);
		}

		{
			UI::Media3D::X3DViewer2* ctl = new UI::Media3D::X3DViewer2;
			//ctl->m_document = document3d;
			{
				UI::Media3D::View3D* view3 = new UI::Media3D::View3D(document3d);
				view3->m_display = 4;
				document3d->m_views[3] = view3;
				ctl->set_Content(view3);
			}
			Grid::SetColumn(ctl, 1);
			Grid::SetRow(ctl, 1);

			panel->AddChild(ctl);
		}

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(200);
		pWindow->set_Height(200);

		pWindow->set_Content(panel);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);

		if (true)
		{
			UI::Media3D::Display2* ctl = new UI::Media3D::Display2(group);
			ctl->m_document = document3d;

			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(200);
			pWindow->set_Height(200);

			ScrollViewer* pScroller = new ScrollViewer;
			{
				pScroller->set_Content(ctl);
			}
		//	UI::MediaPlayer* ctl = new UI::MediaPlayer(dynamic_cast<LMedia::IMediaSeeking*>(video->get_FilterGraph()), video);

			pWindow->set_Content(pScroller);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->set_Title(WSTR("Display Tree"));

			m_pWindowContainer->AddChild(pWindow);

#if 1
			if (true)
			{
				ChildWindow* pWindow = new ChildWindow;
				pWindow->set_Width(200);
				pWindow->set_Height(200);

				ScrollViewer* pScroller = new ScrollViewer;
				m_propertyPalette = pScroller;//new Properties;
				//pScroller->put_Content(m_propertyPalette);

				pWindow->set_Content(pScroller);

				pWindow->set_Title(WSTR("Properties"));

				m_pWindowContainer->AddChild(pWindow);
			}
#endif
		}

		if (true)
		{
			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(200);
			pWindow->set_Height(200);

			UI::Media3D::TimelineView* p = new UI::Media3D::TimelineView;
			p->m_document = document3d;

		//	ScrollViewer* pScroller = new ScrollViewer;
		//	pScroller->put_Content(p);

			pWindow->set_Content(p);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->set_Title(WSTR("Timeline"));

			m_pWindowContainer->AddChild(pWindow);
		}

		if (true)
		{
			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(200);
			pWindow->set_Height(200);

			UI::Media3D::TexturePreview* p = new UI::Media3D::TexturePreview;
			//p->m_document = document3d;

		//	ScrollViewer* pScroller = new ScrollViewer;
		//	pScroller->put_Content(p);

			pWindow->set_Content(p);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->set_Title(WSTR("Texture"));

			m_pWindowContainer->AddChild(pWindow);
		}

#if 0
		if (true)
		{
			ChildWindow* pWindow = new ChildWindow;
			pWindow->put_Width(new Length(200));
			pWindow->put_Height(new Length(200));

			PropertiesWindow* p = new PropertiesWindow(document3d);
			ScrollViewer* pScroller = new ScrollViewer;
			pScroller->put_Content(p);

			pWindow->put_Content(pScroller);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->put_TitleText(WSTR("Document"));

			m_pWindowContainer->AddChild(pWindow);
		}
#endif
	}
#endif

#if 0

#if WIN32
	if (true)
	{
			ChildWindow* pWindow = new ChildWindow;
			pWindow->put_Width(Length(200));
			pWindow->put_Height(Length(200));

			OpenGLControl* p = new OpenGLControl;

			pWindow->put_Content(p);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->put_TitleText(WSTR("Document"));

			m_pWindowContainer->AddChild(pWindow);
		
	}
#endif

#if 1
	if (false)
	{
		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(600));
		pWindow->put_Height(Length(400));

		ShooterControl* v = new ShooterControl;
		pWindow->put_Content(v);

		pWindow->put_TitleText(WSTR("Shooter"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

#endif

#if WIN32
	if (false)
	{
		x3d::VRMLLoader* pLoader = new x3d::VRMLLoader;
#if WIN32
	//	x3d::Scene* pScene = pLoader->Load(WSTR("C:/Files/VRML/test.wrl"));

	//	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/ColorInterpolator.x3dv"));

	//	x3d::Scene* pScene = pLoader->Load(WSTR("C:/Files/VRML/RedSphereBlueBox.x3dv"));
		x3d::Scene* pScene = pLoader->Load(WSTR("C:/mmstudio/Scenes/test2.wrl"));
	//	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/Prototype.x3dv"));

	//	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/marvin_001.wrl"));
	//	x3d::Scene* pScene = pLoader->Load(WSTR("C:/Files/VRML/002/hiro_002b.wrl"));

	//	CLX3DScene* pScene = pLoader->Load(WSTR("http://www.cis.upenn.edu/~beitler/vrml/human/hiro/002/hiro_002b.wrl"));

	//	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/kandelaber.wrl"));
	//	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/venus.wrl"));
	//	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/chamber.wrl"));
#else
	//	CLX3DScene* pScene = pLoader->Load(WSTR("WinHD_C:Files/VRML/test.wrl"));
#endif
		//CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/Prototype.x3dv"));

		X3DViewer* v = new X3DViewer;
		v->m_pWindow->m_pControl->SetScene(pScene);

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(600);
		pWindow->set_Height(500);

		pWindow->set_Content(v);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);

		v->m_pWindow->m_pControl->Run();

		if (false)
		{
			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(200);
			pWindow->set_Height(200);

			PropertiesWindow* p = new PropertiesWindow(v->m_pWindow->m_pControl);
			ScrollViewer* pScroller = new ScrollViewer;
			pScroller->set_Content(p);

			pWindow->set_Content(pScroller);
			//	pWindow->put_Content(m_callStackWnd);

			pWindow->set_Title(WSTR("Document"));

			m_pWindowContainer->AddChild(pWindow);
		}

	}
#endif

#if WIN32
	if (false)
	{
		X3DViewer* v = new X3DViewer;
		v->m_pWindow->set_Src(WSTR("C:/files/mpeg4/kangaroo.mp4"));

	//	v->m_pWindow->put_Src(WSTR("C:/files/mpeg4/DuckandC1951_256kb.mp4"));

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(200);
		pWindow->set_Height(200);

	//	ScrollViewer* pScroller = new ScrollViewer;
		{
	//		pScroller->put_Content(ctl);
		}
		UI::MediaPlayer* ctl = new UI::MediaPlayer(dynamic_cast<MediaShow::IMediaSeeking*>(v->m_pWindow->m_filterGraph), v);
		pWindow->set_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

#if 0

#if 0
	if (true)
	{
		Web::DTDDocument* dtd = new Web::DTDDocument;
		dtd->Load(L"http://www.w3.org/TR/html4/strict.dtd");
	}
#endif
#endif

#if WIN32
	if (false)
	{
		w3c::SVGSVGElement* p = new w3c::SVGSVGElement;

		w3c::CHTMLWindow* pBrowser = new w3c::CHTMLWindow;
//		LSVG::CLSVGDocument* doc = new LSVG::CLSVGDocument;

		/*
		Web::CLDOMElement* root = new Web::CLDOMElement;
		root->put_ownerDocument(doc);

		root->AddRChild(doc->createTextNode(L"Dette er en liten test saann at det staar noe her"));
		doc->AddRChild(root);
		*/

		/*
		LCSS::CLCSSStyleSheet* stylesheet = new LCSS::CLCSSStyleSheet;
		stylesheet->put_cssText(
			WSTR("em { font-size: 20px; color: red;}\n")
			WSTR("frameset { display: block;}\n")
			WSTR("frame { display: block; background-color: red }\n")
			);
			*/

		/*
		{
			std::string filename = DownloadFile("http://www.w3.org/TR/html4/strict.dtd");

			CDTDDocument
		}
		*/

	//	std::string filename = DownloadFile("http://www.lerstad.com/index.html");

		//"http://www.w3.org/TR/html4/strict.dtd"

	//	doc->loadXML(WSTR("<p>This is a <em>test</em> to see</p>"));
		//doc->load(WSTR("c:/mmstudio/help/filtest.html"));
	//	doc->load(WSTR("c:/mmstudio/help/side3.html"));
#if 0
		LHTML::CLHTMLDocument* doc = new LHTML::CLHTMLDocument;
		doc->loadDefaultStylesheet();
		doc->load(WSTR("http://www.lerstad.com/side3.html"));
	//	doc->load(WSTR("http://www.w3.org/"));
		doc->m_pWindow = pBrowser;

		if (doc->get_documentElement())
		{
			pBrowser->m_htmTree = (Web::CPElement*)doc->get_documentElement()->m_pNode;
			pBrowser->m_htmTree->m_pWindow = pBrowser;
#if 0	// Should be done in controls OnArrange
			pBrowser->m_htmTree->GetCSSPropertiesAndChildren();
			pBrowser->m_htmTree->CalculateBoundsAndChildren();
#endif
		}
		else
		{
			MessageBox(NULL, "Failed to load xml", "", MB_OK);
		}
#else
	//	pBrowser->Load(WSTR("http://www.lerstad.com/side3.html"));

#if WIN32
	//	pBrowser->Load(WSTR("http://www.w3.org/"));
	//	pBrowser->Load(WSTR("http://www.w3.org/Graphics/SVG/"));

		if (0)
		{
			pBrowser->Load(WSTR("c:/mmstudio/help/side3.html"));
		}
		else
		{
			pBrowser->Load(WSTR("c:/mmstudio/help/svg_test.html"));
		}

	//	pBrowser->Load(WSTR("c:/mmstudio/help/position.html"));
	//	pBrowser->Load(WSTR("c:/mmstudio/help/utf8.html"));
	//	pBrowser->Load(WSTR("c:/mmstudio/help/textselect_test.html"));

		//	pBrowser->Load(WSTR("c:/test_html_sgml.html"));
#else
		pBrowser->Load(WSTR("WinHD_C:/mmstudio/help/side3.html"));

#endif

#endif

		//doc->get_styleSheets()->append(stylesheet);
		//doc->loadDefaultStylesheet();

	//	pBrowser->m_imageRect = CRect(0, 0, 400, 400);

	//	pBrowser->Flow();
#if 0
		LSVG::SVGSVGElement* svg = new LSVG::SVGSVGElement;
		svg->put_ownerDocument(doc);
		svg->setAttribute(L"width", L"100");
		svg->setAttribute(L"height", L"100");

		LSVG::CLSVGEllipseElement* ellipse = new LSVG::CLSVGEllipseElement;
		ellipse->put_ownerDocument(doc);

		ellipse->setAttribute(WSTR("transform"), WSTR("translate(50, 50) rotate(45)"));
		ellipse->setAttribute(WSTR("fill"), WSTR("red"));
		ellipse->setAttribute(WSTR("cx"), WSTR("50"));
		ellipse->setAttribute(WSTR("cy"), WSTR("50"));
		ellipse->setAttribute(WSTR("rx"), WSTR("30"));
		ellipse->setAttribute(WSTR("ry"), WSTR("20"));
//		ellipse->m_pElement->m_rparent = svg->m_pElement;
		svg->AddRChild(ellipse);

		svg->m_pElement->GetCSSPropertiesAndChildren();
		svg->m_pElement->CalculateBoundsAndChildren();

//		ellipse->m_pElement->GetCSSPropertiesAndChildren();
//		ellipse->m_pElement->CalculateBoundsAndChildren();

		doc->AddRChild(svg);

	//	pBrowser->m_pDocument = svgdoc;
		pBrowser->m_htmTree = svg->m_pElement;
		pBrowser->m_pSVGElement = svg->m_pElement;
#endif

#if 1
		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(500);
		pWindow->set_Height(400);

		pWindow->set_Content(pBrowser);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
#endif
	}
#endif

#if 0
//	put_Width(Length(1380, Length::UnitAbsolute));
//	put_Height(Length(900, Length::UnitAbsolute));

#if 0
	if (true)
	{
	//	UI::Visual visual;
	//	const type_info &ti = typeid(visual);

		StringA dname = DecorateName("UI::LinearGradientBrush");

		DWORD address = pD->LookupSymbol(dname/*"??_R0?AVLinearGradientBrush@UI@@@8"*//*"UI::Visual `RTTI Type Descriptor'"*/);

	//	DWORD address = pD->LookupSymbol("??_R0?AVVisual@UI@@@8"/*"UI::Visual `RTTI Type Descriptor'"*/);
		type_info* ti2 = (type_info*)address;

		const char* name = ti2->name();

		char undecoratedName[8000];
		UnDecorateSymbolName("??_R0?AVVisual@UI@@@8"/*"?get_Viewable@TextEditView@@UAEPAV_Object@@XZ"*/, undecoratedName, 8000, UNDNAME_COMPLETE);

		TRACE("%s\n", undecoratedName);
	}
#endif

	if (true)
	{

	}

	if (false)
	{
		/*
		DataTemplate* pTemplate = new DataTemplate;
		{
			XmlData::Document* document = new XmlData::Document;
			document->load(WSTR("C:\\ChildWindow.lxui"));

			pTemplate->Load(document->get_documentElement());
		}
		*/

		XmlData::Document* document = new XmlData::Document;
		document->load(WSTR("C:\\test.lxui"));

		XmlData::Element* element = document->get_documentElement();
		/*
		{
			Dispatch2* p = GetDispatch(pD->LookupNamedType("TestObjectKK"));
		}
		*/

		const cpp::_Type* pReturnType;
		void* object = CreateElement(pD->LookupNamedType("UI::Visual"), element, &pReturnType);

		UI::Visual* pVisual = (UI::Visual*)DynamicCast(object, pReturnType, typeid(UI::Visual));
//		UI::Visual* pVisual = static_cast<UI::Visual*>((_Object*)object);

		{
			ChildWindow* pWindow = new ChildWindow;
			pWindow->put_Width(Length(200));
			pWindow->put_Height(Length(200));

			pWindow->put_Content(pVisual);

			pWindow->put_TitleText(WSTR("Test"));

			/*
			if (true)
			{
				const cpp::_Type* pRealType;
				UI::Visual* pVisualTree = (UI::Visual*)DynamicCast(pTemplate->m_RootNode->Create(pWindow, &pRealType), pTemplate->m_RootNode->m_pType, pD->LookupNamedType("UI::Visual"));

				pWindow->put_VisualTree(pVisualTree);
			}
			*/
		//	pWindow->put_ControlTemplate(pTemplate);

			m_pWindowContainer->AddChild(pWindow);
		}
	}

#if 0
	if (false)
	{
		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(200));
		pWindow->put_Height(Length(200));

		TextEdit* edit = new TextEdit;

		UI::Binding* pBinding = new UI::Binding;

		{
			Dispatch2 d(pD->LookupNamedType(typeid(*video).name() + 6));
			std::map<StringA, Property*> properties;
			GetProperties(d, properties);
			pBinding->sourceObject = video;
			pBinding->sourceProperty = properties["CurrentTime"];

			EventTargetImpl* eventTarget = dynamic_cast<EventTargetImpl*>(pBinding->sourceObject);
			eventTarget->addEventListener(L"propertychanged", pBinding, false);
		}

		{
			Dispatch2 d(pD->LookupNamedType(typeid(*edit).name() + 6));
			std::map<StringA, Property*> properties;
			GetProperties(d, properties);
			pBinding->targetObject = edit;
			pBinding->targetProperty = properties["Text"];

			EventTargetImpl* eventTarget = dynamic_cast<EventTargetImpl*>(pBinding->targetObject);
			eventTarget->addEventListener(L"propertychanged", pBinding, false);
		}

	//	pBinding->SourceChanged();

		pWindow->put_Content(edit);

		pWindow->put_TitleText(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

	if (false)
	{
		HueSaturate* pHueSaturate = new HueSaturate;
		pHueSaturate->SetRParent(m_pWindowContainer);
		m_pWindowContainer->m_Filter = pHueSaturate;
	}

	if (false)
	{
		Display* disp;
		disp->get_test();

		SelectTool* p = new SelectTool;
	//	p->put_VisualTree(pCanvas);
		p->m_Content = m_pWindowContainer;
		//p->AddRChild(pCanvas);
		p->put_VisualTree(m_pWindowContainer);

		put_Content(p);
	}
	else
	{

		UI::DockPanel::put_Dock(m_pWindowContainer, UI::DockPanel::Fill);
		pPanel->AddRChild(m_pWindowContainer);

		put_Content(pPanel);
	}

#endif

	if (false)
	{
		Display* ctl = new Display(editctl);
	//	UI::Media3D::Display2* ctl = new UI::Media3D::Display2(group);

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(200);
		pWindow->set_Height(200);

		ScrollViewer* pScroller = new ScrollViewer;
		{
			pScroller->set_Content(ctl);
		}
	//	UI::MediaPlayer* ctl = new UI::MediaPlayer(dynamic_cast<LMedia::IMediaSeeking*>(video->get_FilterGraph()), video);

		pWindow->set_Content(pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Display Tree"));

		m_pWindowContainer->AddChild(pWindow);

		if (true)
		{
			ChildWindow* pWindow = new ChildWindow;
			pWindow->set_Width(200);
			pWindow->set_Height(200);

			ScrollViewer* pScroller = new ScrollViewer;
			m_propertyPalette = pScroller;//new Properties;
			//pScroller->put_Content(m_propertyPalette);

			pWindow->set_Content(pScroller);

			pWindow->set_Title(WSTR("Properties"));

			m_pWindowContainer->AddChild(pWindow);
		}
	}

//	AddEventHandler(WSTR("mousedown"), OnMouseDown);

//#if AMIGA
	if (false)
	{
		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(200);
		pWindow->set_Height(200);

	//	TextEdit* pScroller = new TextEdit();//ScrollViewer;
		TestDraw* pScroller = new TestDraw();//ScrollViewer;
		{
	//		pScroller->put_Content(ctl);
		}

		pWindow->set_Content(pScroller);
		//	pWindow->put_Content(m_callStackWnd);

	//	ctl->m_pCanvas = pCanvas;

		pWindow->set_Title(WSTR("Testing"));

		m_pWindowContainer->AddChild(pWindow);
	}
//#endif

#if WIN32
	if (true)
	{
		UI::MediaElement* video = NULL;
		video = new UI::MediaElement;

		/*
		AdjustLevels* pAdjustLevels = new AdjustLevels;
		video->m_Filter = pAdjustLevels;
		pAdjustLevels->SetRParent(video);
		*/

		/*
		Brightness* pBrightness = new Brightness;
		video->m_Filter = pBrightness;
		pBrightness->SetRParent(video);
		*/
		/*
		MinimumEffect* pEffect = new MinimumEffect;
		video->m_Filter = pEffect;
		pEffect->SetRParent(video);
		*/
		/*
		PosterizeEffect* pEffect = new PosterizeEffect;
		video->m_Filter = pEffect;
		pEffect->SetRParent(video);
		*/

		/*
		{
			HueSaturate* pHueSaturate = new HueSaturate;
			pHueSaturate->SetRParent(video->m_Filter);
			video->m_Filter = pHueSaturate;
		}
		*/

		/*
		Histogram* pHistogram = new Histogram;
		video->m_Filter = pHistogram;
		pHistogram->SetRParent(video);
		*/

	//	video->set_Source(L"C:/Files/PNG/test.png");

	//	video->set_Source(L"C:/PappaDVD/VTS_01_1.mpg");

	//	video->set_Source(L"C:\\Files\\IFF-ANIM\\STEELWOM.ANI");

	//	video->set_Source(L"C:\\Documents and Settings\\Sigurd Lerstad\\My Documents\\My Pictures\\roterendeprikkmagi.gif");

	//	video->set_Source(WSTR("C:/files/mpeg4/LuckyStr1948_2_256kb.mp4"));
		video->set_Source(WSTR("C:/files/mpeg4/Airheads2001_256kb.mp4"));
	//	video->set_Source(WSTR("C:/files/mpeg4/Walk2001_256kb.mp4"));

		// mp4
//		ctl->set_Source(WSTR("C:/Program Files/overnet/incoming/X Playboy - Carrie Westcott & Shae Marks.mpg"));

	//	ctl->set_Source(WSTR("C:/Documents and Settings/Sigurd Lerstad/My Documents/eDonkey2000 Downloads/Family.Guy.S04E09.PDTV.XviD-TV.avi"));

#if WIN32

	//	video->set_Source(WSTR("C:/Documents and Settings/Sigurd Lerstad/My Documents/eDonkey2000 Downloads/Annie Lennox - Eurythmics - Sweet Dreams.mpg"));
	//	video->set_Source(WSTR("E:/eDonkey2000 Downloads/Natalie Imbruglia -- Torn.mpg"));

	//	video->set_Source(WSTR("C:/files/mpeg_video2/susi_015.m2v.mpeg"));

	//	video->set_Source(WSTR("C:/program files/overnet/incoming/Karaoke vcd - Shakira - Whenever, Wherever.mpeg"));

	//	video->set_Source(WSTR("C:/Documents and Settings/All Users/Documents/My Pictures/Sample Pictures/Sunset.jpg"));

	//	video->set_Source(WSTR("c:/VTS_01_0.mpg"));

	//	video->set_Source(WSTR("d:/video_ts/VTS_01_0.VOB"));
		//video->set_Source(WSTR("d:/video_ts/video_ts.vob"));

		//video->set_Source(WSTR("C:/test.jpg"));
	//	video->set_Source(WSTR("C:/Sunset.jpg"));

	//	video->set_Source(WSTR("C:/Movies/iffanim/Voyager/Voyager.sndanim"));
	//	video->set_Source(WSTR("C:/Files/IFF-ANIM/EntTorp/EntTorp.sndanim"));
	//	video->set_Source(WSTR("C:/Files/IFF-ANIM/wtx/WTX.sndanim"));
	//	video->set_Source(WSTR("C:/movies/mpeg_video2/susi_015.m2v.mpeg"));
	//	ctl->set_Source(WSTR("C:\\Program Files\\eDonkey2000\\temp\\2.young.to.fall.in.love.pornolation.b.[shareprovider.com].mpg\\1.1.part"));
	//	video->set_Source(WSTR("C:\\Program Files\\Overnet\\incoming\\RealButts - Angela.mpg"));
	//	video->set_Source(WSTR("C:/program files/overnet/incoming/big naturals - house wife.mpg"));
#else
	//	video->set_Source(WSTR("WinHD_C:/Documents and Settings/Sigurd Lerstad/My Documents/eDonkey2000 Downloads/Natalie Imbruglia -- Torn.mpg"));
	//	video->set_Source(WSTR("WinHD_C:/Files/IFF-ANIM/EntTorp/EntTorp.sndanim"));
	//	video->set_Source(WSTR("WinHD_C:/Documents and Settings/Sigurd Lerstad/My Documents/eDonkey2000 Downloads/Natalie Imbruglia -- Torn.mpg"));
	//	video->set_Source(WSTR("WinHD_C:/Movies/iffanim/Voyager/Voyager.sndanim"));
		video->set_Source(WSTR("WinHD_C:/movies/mpeg_video2/susi_015.m2v.mpeg"));
	//	video->put_Source(WSTR("WinHD_C:/program files/overnet/incoming/big naturals - house wife.mpg"));
#endif

	//	ctl->set_Source(WSTR("C:/movies/mpeg_video2/tens_015.m2v.mpeg"));
	//	ctl->set_Source(WSTR("C:/movies/mpeg_video2/100b_015.m2v.mpeg"));

	//	ctl->set_Source(WSTR("C:/movies/mpeg_audio3/CLASSIC2.MP3"));

	//	ctl->set_Source(WSTR("C:/program files/overnet/incoming/RealButts - Angela.mpg"));
	//	ctl->set_Source(WSTR("C:/program files/overnet/incoming/xxxJill Kelly - Anal  playboy pamela anderson.mpg"));

	//	ctl->set_Source(WSTR("C:/music/Dido - White Flag..mpg"));
	//	ctl->set_Source(WSTR("C:/music/Karaoke - Lemon Tree.mpg"));

		//ctl->set_Source(WSTR("C:/program files/overnet/incoming/Ben Moody featuring Anastacia - Everything burns.avi"));

	//	video->set_Source(WSTR("C:/files/divx/BatmanBegins_1.avi"));

	//	video->set_Source(WSTR("C:/files/cinepak/GE_RA_cinematic_trailer_cinepack_hi.avi"));

	//	video->set_Source(WSTR("C:/files/MSVideo1/1699.avi"));

	//	video->set_Source(WSTR("C:/files/mpeg4/karate.mp4"));

#if 0
		TreeControlContainer* ctl2 = new TreeControlContainer;
		ctl2->AddField(WSTR("Display #"));
		ctl2->AddField(WSTR("Encoded #"));
		ctl2->AddField(WSTR("Type"));
		ctl2->AddField(WSTR("Group"));

		LMedia::FilterGraph* filterGraph = ctl->m_Video->get_FilterGraph();
		for (int i = 0; i < filterGraph->m_Filters->m_items.size(); i++)
		{
			LMedia::ILBaseFilter* mediaFilter = filterGraph->m_Filters->m_items[i];
			LMedia::CLMPEGVideoDecoder* mpeg = dynamic_cast<LMedia::CLMPEGVideoDecoder*>(mediaFilter);
			if (mpeg)
			{
				UPOSITION pos = mpeg->m_pVideo->m_pictures.GetHeadPosition();
				for (int i = 0; i < mpeg->m_pVideo->m_pictures.GetCount(); i++)
				{
					LMedia::Picture* pic = (LMedia::Picture*)mpeg->m_pVideo->m_pictures.GetNext(pos);

					MpegFrameItem* item = new MpegFrameItem;

					item->m_displayNr = new LongLongField(pic->m_temporal_reference_abs);
					item->m_encodedNr = new LongLongField(i);
					item->m_type = new IntegerField(pic->m_picture_coding_type);
					item->m_groupIndex = new IntegerField(pic->m_iGroup);

					ctl2->AddItem(item);
				}

				ChildWindow* pWindow = new ChildWindow;
				pWindow->put_Width(new Length(200, Length::UnitAbsolute));
				pWindow->put_Height(new Length(200, Length::UnitAbsolute));

			//	ScrollViewer* pScroller = new ScrollViewer;
				{
			//		pScroller->put_Content(ctl);
				}
				pWindow->put_Content(ctl2);//pScroller);
				//	pWindow->put_Content(m_callStackWnd);

				pWindow->put_TitleText(WSTR("Test"));

				m_pWindowContainer->AddChild(pWindow);

			}
		}
#endif

	//	ctl->put_Source(WSTR("C:/movies/mpeg_video1/evert.mpeg"));
	//	ctl->put_Source(WSTR("C:/movies/mpeg_video1/red.mpeg"));
	//	ctl->put_Source(WSTR("C:/movies/mpeg_video1/torus3.mpeg"));

	//	ctl->put_Source(WSTR("C:/movies/mpeg_audio2/music064.mp2"));
	//	ctl->put_Source(WSTR("C:/movies/mpeg_audio2/sync-064.mp2"));

	//	ctl->put_Source(WSTR("C:/movies/mpeg_audio2/1kz-064.mp2"));

	//	X3DViewer* ctl = new X3DViewer;
	//EditAffineTransformImage* ctl = new EditAffineTransformImage;
//		Control* ctl = pBrowser;
//		LayersComposition* ctl = new LayersComposition;

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(200);
		pWindow->set_Height(200);

	//	ScrollViewer* pScroller = new ScrollViewer;
		{
	//		pScroller->put_Content(ctl);
		}
		UI::MediaPlayer* ctl = new UI::MediaPlayer(dynamic_cast<MediaShow::IMediaSeeking*>(video->get_FilterGraph()), video);

		pWindow->set_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

	if (false)
	{
		BitmapVisual* ctl = new BitmapVisual;

		//ctl->m_bitmap =  LDraw::Bitmap(L"C:\\Documents and Settings\\Sigurd Lerstad\\My Documents\\My Pictures\\test.tif");
		Imaging::BitmapLoader loader;
		loader.Load(ASTR("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.jpg"));
		ctl->set_Bitmap(loader.GetBitmap());// LDraw::Bitmap(WSTR("C:\\Documents and Settings\\Sigurd Lerstad\\My Documents\\My Pictures\\test.gif"));
		//ctl->m_bitmap = LDraw::Bitmap(L"C:/files/IFF-ILBM/Colourfa.ham6");

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(400);
		pWindow->set_Height(400);

	//	ScrollViewer* pScroller = new ScrollViewer;
		{
	//		pScroller->put_Content(ctl);
		}
		pWindow->set_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}

#if WIN32
	if (false)
	{
		MusicModule* pMusic = MusicModuleReader(WSTR("C:/Files/MODS/4mat_4/mod.waterfall")).m_pModule;

		MusicModuleView* ctl = new MusicModuleView;
		ctl->m_pCanvas = m_pWindowContainer;
		ctl->SetModule(pMusic);

		ChildWindow* pWindow = new ChildWindow;
		pWindow->set_Width(400);
		pWindow->set_Height(400);

	//	ScrollViewer* pScroller = new ScrollViewer;
		{
	//		pScroller->put_Content(ctl);
		}
		pWindow->set_Content(ctl);//pScroller);
		//	pWindow->put_Content(m_callStackWnd);

		pWindow->set_Title(WSTR("Test"));

		m_pWindowContainer->AddChild(pWindow);
	}
#endif

#if 0
	if (false)
	{
		Remoting::ServerInfo* server = new Remoting::ServerInfo;

		server->m_socket = new Remoting::WindowClientSocket;
		server->m_socket->Socket();
		server->m_socket->Connect("localhost", 500);

//		ClassType* pType = server->GetClass(new StringA("ServerTestClass"));
		RemoteTestClass* obj = (RemoteTestClass*)server->CreateObject(static_cast<ClassType*>(typeof(RemoteTestClass)));

		obj->set_value(4);

//		socket->CreateObject("");
	}
#endif

	set_Title(WSTR("Browser"));

#if WIN32
	set_Width(800);
	set_Height(660);
#else
	set_Width(500);
	set_Height(450);
#endif

	UI::DockPanel::SetDock(m_pWindowContainer, UI::DockPanel::Fill);
	pPanel->AddChild(m_pWindowContainer);

	set_Content(pPanel);

	}
}

void BrowserFrame::OnImportFromWIA(Object* sender, UI::ExecutedRoutedEventArgs* args)
{
	WIADevice* device = dynamic_cast<WIADevice*>(args->get_Parameter());

	IWiaItem2* pWiaItem2;
	//	pWiaDevMgr2->GetImageDlg(0, deviceID, GetHwnd(), NULL, NULL, 
	m_pWiaDevMgr2->CreateDevice(0, device->m_deviceID, &pWiaItem2);

	HRESULT hr;

	IWiaItem2* pWiaChildItem2;
	LONG numFiles = 0;
	BSTR* files = NULL;
	hr = pWiaItem2->DeviceDlg(0, NULL, SysAllocString(L"C:\\mmstudio"), SysAllocString(L"test"), &numFiles, &files, &pWiaChildItem2);
	//	hr = pWiaItem2->DeviceDlg(0, NULL, NULL, NULL, NULL, NULL, &pWiaChildItem2);

	if (pWiaChildItem2)
	{
		LONG lItemType = 0;
		hr = pWiaChildItem2->GetItemType(&lItemType);

		IWiaTransfer* pWiaTransfer = NULL;
		hr = pWiaChildItem2->QueryInterface(IID_IWiaTransfer,(void**)&pWiaTransfer);

		if (pWiaTransfer)
		{
		//	BitmapLayer* layer = new BitmapLayer;
		//	layer->m_name = WSTR("Background");

			WiaTransferCallback* pCallback = new WiaTransferCallback(this);
			pCallback->AddRef();

			if (lItemType & WiaItemTypeTransfer)
			{
				if (lItemType & WiaItemTypeFile )
				{
					pWiaTransfer->Download(0, pCallback);
				}
			}

			pWiaTransfer->Release();
		}

		pWiaChildItem2->Release();
	}
}

void BrowserFrame::EnumWIADevices(UI::MenuItem* menuitem)
{
	HRESULT hr;

	if (false)
	{
//XP or earlier:
		hr = CoCreateInstance(CLSID_WiaDevMgr, NULL, CLSCTX_LOCAL_SERVER, IID_IWiaDevMgr, (void**)&m_pWiaDevMgr);
	}
	else
	{
    //Vista or later:
		hr = CoCreateInstance(CLSID_WiaDevMgr2, NULL, CLSCTX_LOCAL_SERVER, IID_IWiaDevMgr2, (void**)&m_pWiaDevMgr2); 
	}

	IEnumWIA_DEV_INFO* pEnum;
	hr = m_pWiaDevMgr2->EnumDeviceInfo(0, &pEnum);

	if (SUCCEEDED(hr))
	{
		pEnum->Reset();

		IWiaPropertyStorage* elt;
		ULONG fetched;
		while (pEnum->Next(1, &elt, &fetched) == S_OK)
		{
			/*
			ULONG count;
			elt->GetCount(&count);

			PROPID props[1] =
			{
				WIA_DIP_DEV_ID
				//WIA_DPS_DEVICE_ID
			};
			LPWSTR names[1] = {0};

		//	hr = elt->ReadPropertyNames(1, props, names);
*/

			PROPSPEC propspec[2];

			propspec[0].ulKind = PRSPEC_PROPID;
			propspec[0].propid = WIA_DIP_DEV_ID;

			propspec[1].ulKind = PRSPEC_PROPID;
			propspec[1].propid = WIA_DIP_DEV_NAME;

			PROPVARIANT propvar[2] = {0};

			hr = elt->ReadMultiple(2, propspec, propvar);

			/*
			if (propvar[0].vt == VT_BSTR)
			{
				TRACE("%S\n", propvar[0].bstrVal);
			}
			if (propvar[1].vt == VT_BSTR)
			{
				TRACE("%S\n", propvar[1].bstrVal);
			}
			*/

			BSTR deviceID = SysAllocString(propvar[0].bstrVal);

			WIADevice* device = new WIADevice(deviceID);
			MenuItem* subMenuItem = new MenuItem(new StringW(string_copy(propvar[1].bstrVal)), s_ImportFromWIACommand, device);
			menuitem->get_Items()->Add(subMenuItem);

			//CoTaskMemFree(names[0]);
			FreePropVariantArray(2, propvar);

			elt->Release();
		}

		pEnum->Release();
	}
}

#if 0
void BrowserFrame::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() == System::CAPTURING_PHASE)
	{
		/*
		if (evt->get_type() == WSTR("mousedown"))

		{
			close();
		}
		*/
#if 0
		if (evt->get_type() == WSTR("changed"))
		{
			//m_ctl->m_pSheet->m_rows[m_ctl->m_nrow]->m_cells[m_ctl->m_ncol]->m_stringValue = m_edit->get_Text();
			m_spreadSheetCtl->Invalidate();
			return;
		}
#endif
	}

	CLXUIWindow::handleEvent(evt);
}
#endif

void BrowserFrame::set_ActiveTool(ImageTool* activeTool)
{
	m_activeTool = activeTool;
	PropertyChanged(this, WSTR("ActiveTool"));
}

void BrowserFrame::OnTransferBitmap(LDraw::Bitmap* bitmap)
{
	m_imageDocument = ImageDocument::FromBitmap(bitmap);
}

void BrowserFrame::OnTransferDone()
{
	ShowImageDocument(m_imageDocument);
}

void BrowserFrame::ShowImageDocument(ImageDocument* document)
{
	{
		ListBox* layersView = new ListBox;
		for (int i = 0; i < document->m_layers->get_Count(); i++)
		{
			layersView->get_Items()->Add(document->m_layers->get_Item(i));
		}

		Window* window = new Window;
		window->set_Content(layersView);
		window->Show();
	}

	{
		BitmapEditor* editor = new BitmapEditor;
		editor->m_frame = this;
		get_PropertyChanged().connect(bind1st_of_3(mem_fun2(&BitmapEditor::OnFramePropertyChanged), editor));
		editor->m_document = document;
	//	editor->m_activeLayer = document->m_layers->get_Item(0);
		document->m_views.push_back(editor);

		ScrollViewer* scroller = new ScrollViewer;
		scroller->set_Content(editor);

		ChildWindow* pChildFrame = new ChildWindow;
		pChildFrame->set_Title(document->get_FilePath());
		pChildFrame->set_Content(scroller);
		pChildFrame->set_Width(400);
		pChildFrame->set_Height(300);

		m_pWindowContainer->get_Items()->Add(pChildFrame);
	}
}

void BrowserFrame::OnFileOpen(Object* sender, UI::ExecutedRoutedEventArgs* args)
{
	FileDialog dlg(true);

	if (dlg.DoModal(this) == IDOK)
	{
		IO::FileByteStream file(dlg.GetFileName());
		if (file.GetLastStatus() == 0)
		{
			Imaging::BitmapLoader bitmaploader;
			bitmaploader.Load(&file);

			if (bitmaploader.GetBitmap())
			{
				ImageDocument* document = ImageDocument::FromBitmap(bitmaploader.GetBitmap());

				document->m_filepath = dlg.GetFileName()->ToStringW();

				ShowImageDocument(document);
			}
			else
			{
				PSDParser parser(NULL);
				int ret = parser.Load(&file);
				if (ret == 0)
				{
					try
					{
						PSDHEADER fileInfo;
						parser.GetFileInfo(&fileInfo);

						ImageDocument* document = new ImageDocument;
						document->m_filepath = dlg.GetFileName()->ToStringW();
						document->m_size = LDraw::SizeD(fileInfo.cols, fileInfo.rows);

						int nlayers = parser.GetNumLayers();
						for (int nlayer = 0; nlayer < nlayers; nlayer++)
						{
							PSDLayer* psdlayer = dynamic_cast<PSDLayer*>(parser.GetNLayer(nlayer));

							LAYERINFO layerInfo;
							psdlayer->GetLayerInfo(&layerInfo);

							LAYERINFO2 layerInfo2;
							psdlayer->GetLayerInfo2(&layerInfo2);

							Element* layer = NULL;

							if (psdlayer->m_key == ADJUST_BRIGHTNESS)
							{
								AdjustmentLayer* layer2 = new AdjustmentLayer(document);

								BrightnessContrastAdjustment* adjustment = new BrightnessContrastAdjustment;

								adjustment->m_brightness = (double)psdlayer->m_brightness.brightness / (255*0x6400/100);
								adjustment->m_contrast = (double)psdlayer->m_brightness.contrast / 0x6400;

								adjustment->get_PropertyChanged().connect(bind1st_of_3(mem_fun2(&AdjustmentLayer::OnAdjustmentPropertyChanged), layer2));
								layer2->m_adjustment = adjustment;

								layer = layer2;
							}
							else
							{
								BitmapLayer* layer2 = new BitmapLayer(document);

								layer2->m_x = layerInfo.rect.left;
								layer2->m_y = layerInfo.rect.top;

								layer2->CreateA8R8G8B8(layerInfo.rect.GetWidth(), layerInfo.rect.GetHeight());

								D3DLOCKED_RECT locked_rect;
								layer2->m_bitmap->m_d3dTexture->LockRect(0, &locked_rect, NULL/*&rect*/, 0);

								if (layerInfo.channels == 3)
								{
									psdlayer->ReadPSDLayerChannel(0, locked_rect.Pitch, 4, (uint8*)locked_rect.pBits+2);
									psdlayer->ReadPSDLayerChannel(1, locked_rect.Pitch, 4, (uint8*)locked_rect.pBits+1);
									psdlayer->ReadPSDLayerChannel(2, locked_rect.Pitch, 4, (uint8*)locked_rect.pBits+0);
									FillAlpha(layerInfo.rect.GetWidth(), layerInfo.rect.GetHeight(), locked_rect.Pitch, (uint8*)locked_rect.pBits, 255);
								}
								else if (layerInfo.channels == 4)
								{
									psdlayer->ReadPSDLayerChannel(-1, locked_rect.Pitch, 4, (uint8*)locked_rect.pBits+3);
									psdlayer->ReadPSDLayerChannel(0, locked_rect.Pitch, 4, (uint8*)locked_rect.pBits+2);
									psdlayer->ReadPSDLayerChannel(1, locked_rect.Pitch, 4, (uint8*)locked_rect.pBits+1);
									psdlayer->ReadPSDLayerChannel(2, locked_rect.Pitch, 4, (uint8*)locked_rect.pBits+0);

									Premultiply(layerInfo.rect.GetWidth(), layerInfo.rect.GetHeight(), locked_rect.Pitch, (uint8*)locked_rect.pBits);
								}

								layer2->m_bitmap->m_d3dTexture->UnlockRect(0);

								layer = layer2;
							}

							layer->m_name = psdlayer->GetName()->ToStringW();
							layer->m_visible = !((layerInfo2.flags >> LAYERFLAG_HIDDEN_BIT) & 1);
							layer->m_opacity = layerInfo2.opacity / 255.0;
							layer->m_blendMode = layerInfo2.blend;

							document->m_layers->Add(layer);
							layer->get_PropertyChanged().connect(bind1st_of_3(mem_fun2(&ImageDocument::OnLayerPropertyChanged), document));
						}

						ShowImageDocument(document);
					}
					catch (Exception* e)
					{
						MessageBoxW(NULL, e->get_Reason()->c_str(), L"", MB_OK);
					}

				}
			}

			file.Close();
		}
		else
		{
			MessageBoxW(NULL, L"Couldn't open file", L"", MB_OK);
		}
	}
}

void BrowserFrame::OnCanFileOpen(Object* sender, UI::CanExecuteRoutedEventArgs* args)
{
}

void BrowserFrame::OnSetTool(Object* sender, UI::ExecutedRoutedEventArgs* args)
{
	ImageTool* tool = dynamic_cast<ImageTool*>(args->get_Parameter());
	ASSERT(tool);
	set_ActiveTool(tool);
}

void BrowserFrame::OnCanSetTool(Object* sender, UI::CanExecuteRoutedEventArgs* args)
{
}

}	// System
