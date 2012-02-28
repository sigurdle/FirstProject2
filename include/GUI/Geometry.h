//#include <atlbase.h>

namespace System
{
namespace Gui
{

enum CombineOp
{
	CombineOp_Union,
	CombineOp_Intersect,
	CombineOp_Complement,
	CombineOp_Subtract,
};

class GUIEXT Geometry : public DependencyObject//, public IBitwiseOr
{
protected:

	CTOR Geometry(DependencyClass* depClass);

public:

	// Computed properties
	DEPENDENCY_PROPERTY(float, BoundsLeft)
	DEPENDENCY_PROPERTY(float, BoundsTop)
	DEPENDENCY_PROPERTY(float, BoundsWidth)
	DEPENDENCY_PROPERTY(float, BoundsHeight)

	DEPENDENCY_PROPERTY(float, FillArea)
	DEPENDENCY_PROPERTY(float, ContourLength)

	DEPENDENCY_CLASS_ABSTRACT(Geometry, DependencyObject)

	virtual gm::RectF GetBounds();
	virtual gm::RectF GetBounds(const D2D1_MATRIX_3X2_F& transform);

	virtual D2D1_GEOMETRY_RELATION CompareWithGeometry(Geometry* pgeometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform);
	virtual Geometry* CombineWithGeometry(Geometry* pgeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform);

	virtual bool FillContainsPoint(gm::PointF point);
	virtual bool FillContainsPoint(gm::PointF point, const D2D1_MATRIX_3X2_F& transform);

	virtual void RenderFill(ManagedRenderContext renderContext, Brush* brush);
	virtual void RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width);
	virtual ID2D1Geometry* GetD2DGeometry() = 0;
	virtual HRGN CreateHRGN() = 0;

	virtual Geometry* Widen(float strokeWidth, const D2D1_MATRIX_3X2_F* worldTransform);

	/*
	virtual Object* BitWiseOr(Object* obj)
	{
		ASSERT(0);
		return NULL;
	}
	*/

	// Helpers
	virtual D2D1_GEOMETRY_RELATION CompareWithGeometry(Geometry* geom)
	{
		return CompareWithGeometry(geom, nullptr);
	}

	virtual Geometry* CombineWithGeometry(Geometry* geom, D2D1_COMBINE_MODE combineMode)
	{
		return CombineWithGeometry(geom, combineMode, nullptr);
	}

	virtual Geometry* Widen(float strokeWidth)
	{
		return Widen(strokeWidth, nullptr);
	}

	bool Contains(gm::PointF point)
	{
		return FillContainsPoint(point);
	}

	DEFINE_THIS(_Geometry)
};

class GUIEXT EmptyGeometry : public Geometry
{
public:
	virtual gm::RectF GetBounds() override
	{
		return gm::RectF();
	}

	virtual gm::RectF GetBounds(const D2D1_MATRIX_3X2_F& transform) override
	{
		return gm::RectF();
	}

	virtual D2D1_GEOMETRY_RELATION CompareWithGeometry(Geometry* pgeometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform) override
	{
		return D2D1_GEOMETRY_RELATION_DISJOINT;
	}

	virtual Geometry* CombineWithGeometry(Geometry* pgeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform) override
	{
		if (combineMode == D2D1_COMBINE_MODE_INTERSECT)
		{
			return &empty;
		}
		else // if (combineMode == D2D1_COMBINE_MODE_UNION)
			// D2D1_COMBINE_MODE_XOR
			// D2D1_COMBINE_MODE_EXCLUDE
		{
			return pgeometry;
		}
	}

	virtual bool FillContainsPoint(gm::PointF point) override
	{
		return false;
	}

	virtual bool FillContainsPoint(gm::PointF point, const D2D1_MATRIX_3X2_F& transform) override
	{
		return false;
	}

	virtual void RenderFill(ManagedRenderContext renderContext, Brush* brush) override
	{
	}

	virtual void RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width) override
	{
	}

	virtual ID2D1Geometry* GetD2DGeometry() override
	{
		return nullptr;
	}

	virtual HRGN CreateHRGN() override
	{
		return nullptr;
	}

	virtual Geometry* Widen(float strokeWidth, const D2D1_MATRIX_3X2_F* worldTransform) override
	{
		return &empty;
	}

	DEPENDENCY_CLASS(EmptyGeometry, Geometry)

	static EmptyGeometry empty;

protected:

	CTOR EmptyGeometry();
};


class GUIEXT strokeStyle
{
public:

	CTOR strokeStyle() : m_d2d(nullptr)
	{
	}

#ifndef __LERSTAD__
	CTOR strokeStyle(D2D1_CAP_STYLE startCap, D2D1_CAP_STYLE endCap) : m_d2d(nullptr)
	{
		Graphics::Direct10::get_D2DFactory()->CreateStrokeStyle(
			D2D1::StrokeStyleProperties(startCap, endCap,
			D2D1_CAP_STYLE_ROUND,
              D2D1_LINE_JOIN_ROUND,
              10.0f),
			  nullptr, 0, &m_d2d);
	}
#endif

	CTOR strokeStyle(decltype(nullptr)) : m_d2d(nullptr)
	{
	}

	CTOR strokeStyle(ID2D1StrokeStyle* d2d) : m_d2d(d2d)
	{
	}

	operator ID2D1StrokeStyle* () const
	{
		return m_d2d;
	}

	ComPtr<ID2D1StrokeStyle> m_d2d;
};

class GUIEXT geometry
{
public:

	CTOR geometry() : m_p(nullptr), m_d2d(nullptr)
	{
	}

	CTOR geometry(decltype(nullptr)) : m_p(nullptr), m_d2d(nullptr)
	{
	}

	CTOR geometry(Geometry* p) : m_p(p), m_d2d(nullptr)
	{
	}

	CTOR geometry(ID2D1Geometry* d2d) : m_p(nullptr), m_d2d(d2d)
	{
	}

	CTOR geometry(const geometry& other) :
		m_p(other.m_p),
		m_d2d(other.m_d2d)
	{
	}

	CTOR geometry(gm::RectF rect)
	{
		m_p = nullptr;

#ifndef __LERSTAD__
		D2D1_RECT_F d2d1rect;
		d2d1rect.left = rect.GetLeft();
		d2d1rect.top = rect.GetTop();
		d2d1rect.right = rect.GetRight();
		d2d1rect.bottom = rect.GetBottom();

		ComPtr<ID2D1RectangleGeometry> geometry;
		ThrowHr hr = Graphics::Direct10::get_D2DFactory()->CreateRectangleGeometry(d2d1rect, &geometry);
		m_d2d = std::move(geometry);
#endif
	}

	~geometry()
	{
		m_p = nullptr;
	}

	gm::RectF GetBounds() const
	{
		if (m_d2d != nullptr)
		{
#ifndef __LERSTAD__
			D2D1_RECT_F bounds;
			ThrowHr(m_d2d->GetBounds(nullptr, &bounds));
#endif
			return gm::RectF(
				bounds.left, bounds.top,
				bounds.right-bounds.left, bounds.bottom-bounds.top);
		}
		else if (m_p)
		{
			return m_p->GetBounds();
		}
		else
			return gm::RectF();
	}

	geometry& operator = (const geometry& other)
	{
		m_p = other.m_p;
		m_d2d = other.m_d2d;

		return *this;
	}

#ifndef __LERSTAD__

	/*
	CTOR geometry(geometry&& other)
	{
		m_p = other.m_p;
		m_d2d = other.m_d2d;

		other.m_d2d = nullptr;
		other.m_p = nullptr;
	}
	*/

	template<class T>
	CTOR geometry(ComPtr<T>&& other)
	{
		m_p = nullptr;
		m_d2d.Attach(other.Detach());
	}

	geometry& operator = (geometry&& other)
	{
		m_p = other.m_p;
		m_d2d.Attach(other.m_d2d.Detach());
		other.m_p = nullptr;

		return *this;
	}

#endif

	bool operator ! () const
	{
		return m_p == nullptr && m_d2d == nullptr;
	}

	bool operator == (decltype(nullptr)) const
	{
		return m_p == nullptr && m_d2d == nullptr;
	}

	bool operator != (decltype(nullptr)) const
	{
		return m_p != nullptr || m_d2d != nullptr;
	}

	bool operator == (const geometry& other) const
	{
		if (m_p)
			return m_p == other.m_p;
		else
			return m_d2d == other.m_d2d;
	}

	bool operator != (const geometry& other) const
	{
		return !operator==(other);
	}

	bool FillContains(gm::PointF point) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			if (m_p) d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			BOOL contains;
			ThrowHr hr = d2d->FillContainsPoint(cnv(point), nullptr, &contains);
			return !!contains;
		}

		return false;
	}

	bool StrokeContains(gm::PointF point, float strokeWidth) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			BOOL contains;
			ThrowHr hr = d2d->StrokeContainsPoint(cnv(point), strokeWidth, nullptr, nullptr, &contains);
			return !!contains;
		}

		return false;
	}

	D2D1_GEOMETRY_RELATION Compare(const geometry& other) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		D2D1_GEOMETRY_RELATION relation;
		ThrowHr hr = d2d->CompareWithGeometry(other, nullptr, &relation);
		return relation;
	}

	bool Contains(const geometry& other) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			D2D1_GEOMETRY_RELATION relation;
			ThrowHr hr = d2d->CompareWithGeometry(other, nullptr, &relation);
			return relation == D2D1_GEOMETRY_RELATION_CONTAINS;
		}
		else
			return false;//m_p->CompareWithGeometry(other.m_p, nullptr) == D2D1_GEOMETRY_RELATION_CONTAINS;
	}

	bool Overlaps(const geometry& other) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			D2D1_GEOMETRY_RELATION relation;
			ThrowHr hr = d2d->CompareWithGeometry(other, nullptr, &relation);
			return relation == D2D1_GEOMETRY_RELATION_OVERLAP;
		}
		else
			return false;//return m_p->CompareWithGeometry(other, nullptr) == D2D1_GEOMETRY_RELATION_OVERLAP;
	}

	float ComputeArea() const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			float area;
			ThrowHr hr = d2d->ComputeArea(nullptr, &area);

			return area;
		}
		return 0;
	}

	float ComputeArea(float flatteningTolerance) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			float area;
			ThrowHr hr = d2d->ComputeArea(nullptr, flatteningTolerance, &area);

			return area;
		}
		return 0;
	}

	float ComputeLength() const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			float length;
			ThrowHr hr = d2d->ComputeLength(nullptr, &length);

			return length;
		}
		return 0;
	}

	float ComputeLength(float flatteningTolerance) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			float length;
			ThrowHr hr = d2d->ComputeLength(nullptr, flatteningTolerance, &length);

			return length;
		}
		return 0;
	}

	pair<gm::PointF, gm::PointF> ComputePointAtLength(float length) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		D2D1_POINT_2F point;
		D2D1_POINT_2F unitTangentVector;

		ThrowHr hr = d2d->ComputePointAtLength(length, nullptr, &point, &unitTangentVector);
		return pair<gm::PointF, gm::PointF>(cnv(point), cnv(unitTangentVector));
	}

	pair<gm::PointF, gm::PointF> ComputePointAtLength(float length, const D2D1_MATRIX_3X2_F* worldTransform) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		D2D1_POINT_2F point;
		D2D1_POINT_2F unitTangentVector;

		ThrowHr hr = d2d->ComputePointAtLength(length, worldTransform, &point, &unitTangentVector);
		return pair<gm::PointF, gm::PointF>(cnv(point), cnv(unitTangentVector));
	}

	pair<gm::PointF, gm::PointF> ComputePointAtLength(float length, const D2D1_MATRIX_3X2_F& worldTransform) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		D2D1_POINT_2F point;
		D2D1_POINT_2F unitTangentVector;

		ThrowHr hr = d2d->ComputePointAtLength(length, worldTransform, &point, &unitTangentVector);
		return pair<gm::PointF, gm::PointF>(cnv(point), cnv(unitTangentVector));
	}

	geometry Widened(float strokeWidth, strokeStyle style = nullptr) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);
			hr = d2d->Widen(strokeWidth, style, nullptr, geometrySink);
			geometrySink->Close();

			return std::move(pathGeometry);
		}
		else
			;//return m_p->Widen(strokeWidth, nullptr);
		return nullptr;
	}

	geometry Outline() const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);
			hr = d2d->Outline(nullptr, geometrySink);
			geometrySink->Close();

			return std::move(pathGeometry);
		}
		else
			;//return m_p->Widen(strokeWidth, nullptr);
		return nullptr;
	}

	geometry operator | (const geometry& other) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);
			hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_UNION, NULL, geometrySink);
			geometrySink->Close();

			return std::move(pathGeometry);
		}
		else
			return nullptr;//m_p->CombineWithGeometry(other, D2D1_COMBINE_MODE_UNION, NULL);
	}

	geometry operator & (const geometry& other) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);
			hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_INTERSECT, NULL, geometrySink);
			geometrySink->Close();

			return std::move(pathGeometry);
		}
		else
			return nullptr;//m_p->CombineWithGeometry(other, D2D1_COMBINE_MODE_INTERSECT, NULL);
	}

	geometry operator ^ (const geometry& other) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);
			hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_XOR, NULL, geometrySink);
			geometrySink->Close();

			return std::move(pathGeometry);
		}
		else
			return nullptr;//m_p->CombineWithGeometry(other, D2D1_COMBINE_MODE_XOR, NULL);
	}

	geometry operator - (const geometry& other) const
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);
			hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_EXCLUDE, NULL, geometrySink);
			geometrySink->Close();

			return std::move(pathGeometry);
		}
		else
		{
			return nullptr;//m_p->CombineWithGeometry(other, D2D1_COMBINE_MODE_EXCLUDE, NULL);
		}
	}

//

	geometry& operator |= (const geometry& other)
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			if (m_p) d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			if (other != nullptr)
			{
				ThrowHr hr;

				ComPtr<ID2D1PathGeometry> pathGeometry;
				hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

				ComPtr<ID2D1GeometrySink> geometrySink;
				hr = pathGeometry->Open(&geometrySink);
				hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_UNION, NULL, geometrySink);
				geometrySink->Close();

				m_d2d = std::move(pathGeometry);
			}
		}
		else
		{
			m_d2d = other.m_d2d;
			/*
			if (m_p)
			{
				m_p = m_p->CombineWithGeometry(other, D2D1_COMBINE_MODE_UNION, NULL);
			}
			*/
		}
		return *this;
	}

	geometry& operator &= (const geometry& other)
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			if (m_p) d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			if (other != nullptr)
			{
				ThrowHr hr;

				ComPtr<ID2D1PathGeometry> pathGeometry;
				hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

				ComPtr<ID2D1GeometrySink> geometrySink;
				hr = pathGeometry->Open(&geometrySink);
				hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_INTERSECT, NULL, geometrySink);
				geometrySink->Close();

				m_d2d = std::move(pathGeometry);
			}
			else
			{
				m_d2d = nullptr;
			}
		}
		else
		{
			/*
			if (other.m_p)
			{
				m_p = m_p->CombineWithGeometry(other.m_p, D2D1_COMBINE_MODE_INTERSECT, NULL);
			}
			*/
		}
		return *this;
	}

	geometry& operator ^= (const geometry& other)
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			if (m_p) d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);
			hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_XOR, NULL, geometrySink);
			geometrySink->Close();

			m_d2d = std::move(pathGeometry);
		}
		else
		{
			m_d2d = other.m_d2d;
		//	m_p = m_p->CombineWithGeometry(other, D2D1_COMBINE_MODE_XOR, NULL);
		}

		return *this;
	}

	geometry& operator -= (const geometry& other)
	{
		ID2D1Geometry* d2d = m_d2d;
		if (d2d == nullptr)
		{
			d2d = m_p->GetD2DGeometry();
		}

		if (d2d)
		{
			ThrowHr hr;

			ComPtr<ID2D1PathGeometry> pathGeometry;
			hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);

			ComPtr<ID2D1GeometrySink> geometrySink;
			hr = pathGeometry->Open(&geometrySink);

			hr = d2d->CombineWithGeometry(other, D2D1_COMBINE_MODE_EXCLUDE, NULL, geometrySink);

			geometrySink->Close();

			m_d2d = std::move(pathGeometry);
		}
		/*
		else
		{
			m_p = m_p->CombineWithGeometry(other, D2D1_COMBINE_MODE_EXCLUDE, NULL);
		}
		*/
		return *this;
	}

	/*
	geometry operator ~ () const
	{
		geometry g(*this);
		g.m_inverted = !m_inverted;
		return g;
	}
	*/

	/*
	void CreatePath()
	{
		ComPtr<ID2D1PathGeometry> pathGeometry;
		ThrowHr hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);
		m_d2d.Attach(pathGeometry.Detach());
	}

	ComPtr<ID2D1PathGeometry> AsPath()
	{
		ComPtr<ID2D1PathGeometry> p;
		m_d2d->QueryInterface(&p);
		return p;
	}
	*/

	geometry Transform(const D2D1_MATRIX_3X2_F& transform) const
	{
		ComPtr<ID2D1TransformedGeometry> other;
		Graphics::Direct10::get_D2DFactory()->CreateTransformedGeometry(m_d2d, transform, &other);
		return std::move(other);
	}

	geometry Transform(const D2D1_MATRIX_3X2_F* transform) const
	{
		ComPtr<ID2D1TransformedGeometry> other;
		Graphics::Direct10::get_D2DFactory()->CreateTransformedGeometry(m_d2d, transform, &other);
		return std::move(other);
	}

	D2D1_MATRIX_3X2_F GetTransform() const
	{
#ifndef __LERSTAD__
		ComPtr<ID2D1TransformedGeometry> geom = __dynamic_cast<ComPtr<ID2D1TransformedGeometry> >(m_d2d);
		if (geom)
		{
			D2D1_MATRIX_3X2_F xform;
			geom->GetTransform(&xform);
			return xform;
		}
		return D2D1::IdentityMatrix();
#endif
	}

	HRGN CreateHRGN();

	void RenderFill(ManagedRenderContext renderContext, Brush* brush);
	void RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width);

	operator Geometry* () const
	{
		if (m_p)
		{
			return m_p;
		}
		else
		{
			ASSERT(m_d2d == nullptr);
			return nullptr;
		}
	}

	operator ID2D1Geometry* () const
	{
		if (m_p)
			return m_p->GetD2DGeometry();
		else
			return m_d2d;
	}

	ID2D1Geometry* GetD2DGeometry() const
	{
		if (m_p)
			return m_p->GetD2DGeometry();
		else
			return m_d2d;
	}

	String ToSVGPath() const;

	/*
	pathgeometry AsPath()
	{
		ComPtr<ID2D1PathGeometry> path;
		m_d2d.QueryInterface(&path);
		return std::move(path);
	}
	*/

	static geometry From(gm::RectF rect);
	static geometry From(const vector<gm::PointF>& points);
	static geometry FromSVGPath(StringIn str);

protected:

	Geometry* m_p;
	ComPtr<ID2D1Geometry> m_d2d;
//	bool m_inverted;
};

class GUIEXT pathgeometry : public geometry
{
public:

	CTOR pathgeometry()
	{
	}

	CTOR pathgeometry(ID2D1PathGeometry* p) : geometry(p)
	{
	}

	void Create()
	{
		ComPtr<ID2D1PathGeometry> pathGeometry;
		ThrowHr hr = Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pathGeometry);
		m_d2d.Attach(pathGeometry.Detach());
	}

	ComPtr<ID2D1GeometrySink> OpenSink()
	{
		ComPtr<ID2D1GeometrySink> geometrySink;
		ThrowHr hr = ((ID2D1PathGeometry*)m_d2d.p)->Open(&geometrySink);
		return geometrySink;
	}

	pathgeometry& operator = (ID2D1PathGeometry* d2d)
	{
		m_p = nullptr;
		m_d2d = d2d;
		return *this;
	}

	operator ID2D1PathGeometry* () const
	{
		return (ID2D1PathGeometry*)m_d2d.p;
	}

	ID2D1PathGeometry* operator -> ()
	{
		return (ID2D1PathGeometry*)m_d2d.p;
	}
};

/*
class transformedgeometry
{
};
*/

class _Geometry : public _DependencyObject
{
public:
	CTOR _Geometry(const Expressive::expression& exp) : _DependencyObject(exp)
	{
	}

	Expressive::typed_expression<bool> fillContainsPoint(Expressive::typed_expression<float> x, Expressive::typed_expression<float> y) const
	{
		return new Expressive::MethodCall2Expression<bool, float, float>(*this, GetDispatch(typeid(Geometry).GetType()->AsClass())->GetMethod("FillContainsPoint"), x, y);
	}
};

}	// Gui
}	// System
