#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

class GUIEXT GeometrySink : public ID2D1SimplifiedGeometrySink
{
public:

	CTOR GeometrySink(PathGeometry* p) : m_path(p)
	{
	}

	ULONG STDMETHODCALLTYPE AddRef() override
	{
		return 1;
	}
	ULONG STDMETHODCALLTYPE Release() override
	{
		return 1;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(const IID& riid, void** ppvObject) override
	{
		if (riid == IID_IUnknown)
		{
			*ppvObject = static_cast<IUnknown*>(this);
		}
		else if (riid == __uuidof(ID2D1SimplifiedGeometrySink))
		{
			*ppvObject = static_cast<ID2D1SimplifiedGeometrySink*>(this);
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}

		AddRef();
		return S_OK;
	}

    STDMETHOD_(void, SetFillMode)(D2D1_FILL_MODE fillMode)
	{
		m_path->set_FillMode((FillMode)fillMode);
	}
    
    STDMETHOD_(void, SetSegmentFlags)(D2D1_PATH_SEGMENT vertexFlags)
	{
	}

    STDMETHOD_(void, BeginFigure)(
        D2D1_POINT_2F startPoint,
        D2D1_FIGURE_BEGIN figureBegin 
		)
	{
		m_figure = new PathFigure();
		m_figure->m_segments.push_back(new LineToPathSegment(cnv(startPoint)));
		m_path->m_figures.push_back(m_figure);
	}
    
    STDMETHOD_(void, AddLines)(
        __in_ecount(pointsCount) CONST D2D1_POINT_2F *points,
        UINT pointsCount 
        )
	{
		while (pointsCount--)
		{
			m_figure->m_segments.push_back(new LineToPathSegment(cnv(*points)));

			++points;
		}
	}
    
    STDMETHOD_(void, AddBeziers)(
        __in_ecount(beziersCount) CONST D2D1_BEZIER_SEGMENT *beziers,
        UINT beziersCount 
        )
	{
		while (beziersCount--)
		{
			m_figure->m_segments.push_back(new CubicBezierToPathSegment(cnv(beziers->point1), cnv(beziers->point2), cnv(beziers->point3)));

			++beziers;
		}
	}
    
    STDMETHOD_(void, EndFigure)(D2D1_FIGURE_END figureEnd)
	{
		m_figure->set_Closed(figureEnd == D2D1_FIGURE_END_CLOSED);
	}
    
    STDMETHOD(Close)()
	{
		return S_OK;
	}

	PathGeometry* m_path;
	PathFigure* m_figure;
};

IMP_DEPENDENCY_PROPERTY(float, Geometry, BoundsLeft, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Geometry, BoundsTop, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Geometry, BoundsWidth, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Geometry, BoundsHeight, 0.0f)

IMP_DEPENDENCY_PROPERTY(float, Geometry, FillArea, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Geometry, ContourLength, 0.0f)

DependencyClass* Geometry::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_BoundsLeftProperty(),
		get_BoundsTopProperty(),
		get_BoundsWidthProperty(),
		get_BoundsHeightProperty(),
		get_FillAreaProperty(),
		get_ContourLengthProperty(),
	};

	return &depclass;
}

Geometry::Geometry(DependencyClass* depClass) : DependencyObject(depClass)
{
}

gm::RectF Geometry::GetBounds()
{
	ID2D1Geometry* pgeometry = GetD2DGeometry();

	D2D1_RECT_F bounds;
	pgeometry->GetBounds(NULL, &bounds);
	return gm::RectF(bounds.left, bounds.top, bounds.right-bounds.left, bounds.bottom-bounds.top);

	/*
	return LDraw::RectF(
		GetPropertyValueFloat(get_BoundsLeftProperty()),
		GetPropertyValueFloat(get_BoundsTopProperty()),
		GetPropertyValueFloat(get_BoundsWidthProperty()),
		GetPropertyValueFloat(get_BoundsHeightProperty())
		);
		*/
}

gm::RectF Geometry::GetBounds(const D2D1_MATRIX_3X2_F& transform)
{
	ID2D1Geometry* geometry = GetD2DGeometry();
	if (geometry == NULL) return gm::RectF();

	D2D_RECT_F bounds;
	geometry->GetBounds(NULL, &bounds);

	return gm::RectF(bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top);
}

bool Geometry::FillContainsPoint(gm::PointF point)
{
	ID2D1Geometry* pgeometry = GetD2DGeometry();
	if (pgeometry == NULL) return false;

	BOOL contains;
	HRESULT hr = pgeometry->FillContainsPoint(D2D1::Point2F(point.X, point.Y), NULL, &contains);
	ASSERT(SUCCEEDED(hr));

	return (contains == TRUE);
}

D2D1_GEOMETRY_RELATION Geometry::CompareWithGeometry(Geometry* geometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform)
{
	if (geometry == NULL)
	{
		raise(ArgumentNullException_(geometry));
	}

	ID2D1Geometry* d2dgeometry1 = GetD2DGeometry();
	if (d2dgeometry1 == NULL)
	{
		raise(Exception());
	}

	ID2D1Geometry* d2dgeometry2 = geometry->GetD2DGeometry();
	if (d2dgeometry2 == NULL)
	{
		raise(Exception());
	}

	D2D1_GEOMETRY_RELATION relation;
	HRESULT hr = d2dgeometry1->CompareWithGeometry(d2dgeometry2, inputGeometryTransform, &relation);
	if (FAILED(hr))
	{
		raise(Exception());
	}

	return relation;
}

Geometry* Geometry::CombineWithGeometry(Geometry* geometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform)
{
	if (geometry == NULL)
	{
		raise(ArgumentNullException_(geometry));
	}

	ID2D1Geometry* d2dgeometry1 = GetD2DGeometry();
	if (d2dgeometry1 == NULL) return NULL;

	ID2D1Geometry* d2dgeometry2 = geometry->GetD2DGeometry();
	if (d2dgeometry2 == NULL) return NULL;

	if (true)
	{
		ID2D1PathGeometry* pg;
		Graphics::Direct10::s.m_D2DFactory->CreatePathGeometry(&pg);

		ID2D1GeometrySink* psink;
		HRESULT hr = pg->Open(&psink);
		ASSERT(SUCCEEDED(hr));

		hr = d2dgeometry1->CombineWithGeometry(d2dgeometry2, combineMode, inputGeometryTransform, psink);

		psink->Close();
		psink->Release();

		return new PathGeometry(pg);
	}
	else
	{
		GeometrySink sink(new PathGeometry());

		HRESULT hr = d2dgeometry1->CombineWithGeometry(d2dgeometry2, combineMode, inputGeometryTransform, &sink);

		return sink.m_path;
	}
}

Geometry* Geometry::Widen(float strokeWidth, const D2D1_MATRIX_3X2_F* worldTransform)
{
	ID2D1Geometry* geometry = GetD2DGeometry();
	if (geometry == NULL) return NULL;

	GeometrySink sink(new PathGeometry());

	geometry->Widen(strokeWidth, NULL, worldTransform, &sink);

	return sink.m_path;
}

#define IS_NOT_FALSE(x) !!(x)

bool Geometry::FillContainsPoint(gm::PointF point, const D2D1_MATRIX_3X2_F& transform)
{
	ID2D1Geometry* d2dgeometry = GetD2DGeometry();
	if (d2dgeometry == NULL) return false;

	BOOL contains;
	HRESULT hr = d2dgeometry->FillContainsPoint(D2D1::Point2F(point.X, point.Y), transform, &contains);
	ASSERT(SUCCEEDED(hr));

	return IS_NOT_FALSE(contains);
}

void Geometry::RenderFill(ManagedRenderContext renderContext, Brush* brush)
{
	if (brush)
	{
		ID2D1Geometry* pGeometry = GetD2DGeometry();
		if (pGeometry)
		{
			renderContext.m_p->GetRT()->m_spRT->FillGeometry(pGeometry, brush->Create(renderContext.m_p, NULL/*this*/), NULL/*m_opacityMask? m_opacityMask->Create(renderContext, this): NULL*/);
		}
	}
}

void Geometry::RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width)
{
	if (brush)
	{
		ID2D1Geometry* pGeometry = GetD2DGeometry();
		if (pGeometry)
		{
			ID2D1StrokeStyle* strokeStyle = NULL;
			renderContext.m_p->GetRT()->m_spRT->DrawGeometry(pGeometry, brush->Create(renderContext.m_p, NULL/*this*/), width, strokeStyle);
		}
	}
}

void geometry::RenderFill(ManagedRenderContext renderContext, Brush* brush)
{
	if (brush)
	{
		ID2D1Geometry* pGeometry = GetD2DGeometry();
		if (pGeometry)
		{
			renderContext.m_p->GetRT()->m_spRT->FillGeometry(pGeometry, brush->Create(renderContext.m_p, NULL/*this*/), NULL/*m_opacityMask? m_opacityMask->Create(renderContext, this): NULL*/);
		}
	}
}

void geometry::RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width)
{
	if (brush)
	{
		ID2D1Geometry* pGeometry = GetD2DGeometry();
		if (pGeometry)
		{
			ID2D1StrokeStyle* strokeStyle = NULL;
			renderContext.m_p->GetRT()->m_spRT->DrawGeometry(pGeometry, brush->Create(renderContext.m_p, NULL/*this*/), width, strokeStyle);
		}
	}
}

class GUIEXT SVGGeometrySink : public ID2D1GeometrySink
{
public:

	CTOR SVGGeometrySink(const IO::StringWriter& writer) : m_writer(writer)
	{
	}

	ULONG STDMETHODCALLTYPE AddRef() override
	{
		return 1;
	}
	ULONG STDMETHODCALLTYPE Release() override
	{
		return 1;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(const IID& riid, void** ppvObject) override
	{
		if (riid == IID_IUnknown)
		{
			*ppvObject = static_cast<IUnknown*>(this);
		}
		else if (riid == __uuidof(ID2D1SimplifiedGeometrySink))
		{
			*ppvObject = static_cast<ID2D1SimplifiedGeometrySink*>(this);
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}

		AddRef();
		return S_OK;
	}

    STDMETHOD_(void, SetFillMode)(D2D1_FILL_MODE fillMode) override
	{
		//m_path->set_FillMode((FillMode)fillMode);
	}
    
    STDMETHOD_(void, SetSegmentFlags)(D2D1_PATH_SEGMENT vertexFlags) override
	{
	}

    STDMETHOD_(void, BeginFigure)(D2D1_POINT_2F startPoint,D2D1_FIGURE_BEGIN figureBegin) override
	{
		m_writer << "M" << startPoint.x << " " << startPoint.y;

	}

    STDMETHOD_(void, AddQuadraticBezier)(__in CONST D2D1_QUADRATIC_BEZIER_SEGMENT *bezier) override
	{
		ASSERT(0);
	}
    
    STDMETHOD_(void, AddQuadraticBeziers)(
        __in_ecount(beziersCount) CONST D2D1_QUADRATIC_BEZIER_SEGMENT *beziers,
        UINT beziersCount) override
	{
		ASSERT(0);
	}
    
    STDMETHOD_(void, AddArc)(__in CONST D2D1_ARC_SEGMENT *arc) override
	{
		ASSERT(0);
	}

    STDMETHOD_(void, AddLine)(D2D1_POINT_2F point) override
	{
		m_writer << "L";
		m_writer << point.x << " " << point.y;
	}

    STDMETHOD_(void, AddLines)(
        __in_ecount(pointsCount) CONST D2D1_POINT_2F *points,
        UINT pointsCount) override
	{
		m_writer << "L";

		while (pointsCount--)
		{
			m_writer << " " << points->x << " " << points->y;

			++points;
		}
	}

	STDMETHOD_(void, AddBezier)(CONST D2D1_BEZIER_SEGMENT *bezier) override
	{
		m_writer << "C";

		m_writer << bezier->point1.x << " " << bezier->point1.y;
		m_writer << bezier->point2.x << " " << bezier->point2.y;
		m_writer << bezier->point3.x << " " << bezier->point3.y;
	}

	STDMETHOD_(void, AddBeziers)(
		__in_ecount(beziersCount) CONST D2D1_BEZIER_SEGMENT *beziers,
		UINT beziersCount) override
	{
		m_writer << "C";
		while (beziersCount--)
		{
			m_writer << " " << beziers->point1.x << " " << beziers->point1.y;
			m_writer << " " << beziers->point2.x << " " << beziers->point2.y;
			m_writer << " " << beziers->point3.x << " " << beziers->point3.y;

			++beziers;
		}
	}
    
    STDMETHOD_(void, EndFigure)(D2D1_FIGURE_END figureEnd) override
	{
		if (	figureEnd == D2D1_FIGURE_END_CLOSED)
		{
			m_writer << "z";
		}
	}
    
    STDMETHOD(Close)() override
	{
		return S_OK;
	}

	IO::StringWriter m_writer;
};

String geometry::ToSVGPath() const
{
	ComPtr<ID2D1PathGeometry> pathGeometry;
	m_d2d->QueryInterface(&pathGeometry);

	IO::StringWriter str;
	SVGGeometrySink sink(str);
	pathGeometry->Stream(&sink);

	return str.str();
}

// static
geometry geometry::From(const vector<gm::PointF>& points)
{
	ThrowHr hr;

	ComPtr<ID2D1PathGeometry> pathGeometry;
	hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

	ComPtr<ID2D1GeometrySink> geometrySink;
	hr = pathGeometry->Open(&geometrySink);
	if (points.size())
	{
		geometrySink->BeginFigure(cnv(points[0]), D2D1_FIGURE_BEGIN_HOLLOW);
		geometrySink->AddLines((D2D1_POINT_2F*)points.cbegin()+1, (UINT)points.size()-1);
		geometrySink->EndFigure(D2D1_FIGURE_END_OPEN);
	}
	geometrySink->Close();

	return std::move(pathGeometry);
}

/////////////////////////////////
// EmptyGeometry

EmptyGeometry EmptyGeometry::empty;

DependencyClass* EmptyGeometry::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());
	return &depclass;
}

EmptyGeometry::EmptyGeometry() : Geometry(get_Class())
{
}

}	// Gui
}	// System
