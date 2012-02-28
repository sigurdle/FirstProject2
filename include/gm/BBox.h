/*
#ifndef _D2DBASETYPES_INCLUDED

typedef struct D2D_RECT_F
{
    FLOAT left;
    FLOAT top;
    FLOAT right;
    FLOAT bottom;

} D2D_RECT_F;

#endif
*/

namespace System
{
namespace gm
{

template<class TYPE> class BBox
{
public:
	inline CTOR BBox() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline CTOR BBox(const BBox& other) throw()
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
	}

	inline CTOR BBox(TYPE _left, TYPE _top, TYPE _right, TYPE _bottom) throw()
	{
		left = _left;
		top = _top;
		right = _right;
		bottom = _bottom;
	}

	inline CTOR BBox(const Point<TYPE>& topleft, const Point<TYPE>& bottomright) throw()
	{
		left = topleft.X;
		top = topleft.Y;
		right = bottomright.X;
		bottom = bottomright.Y;
	}

	inline CTOR BBox(const Rect<TYPE>& rect) throw()
	{
		left = rect.GetLeft();
		top = rect.GetTop();
		right = rect.GetRight();
		bottom = rect.GetBottom();
	}

	inline operator Rect<TYPE> () const throw()
	{
		return Rect<TYPE>(left, top, right-left, bottom-top);
	}

	static void Intersect(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MIN(a.right, b.right);
		c.bottom = MIN(a.bottom, b.bottom);
		c.left = MAX(a.left, b.left);
		c.top = MAX(a.top, b.top);
	}

	static void Union(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MAX(a.right, b.right);
		c.bottom = MAX(a.bottom, b.bottom);
		c.left = MIN(a.left, b.left);
		c.top = MIN(a.top, b.top);
	}

	inline TYPE GetLeft() const throw()
	{
		return left;
	}

	inline TYPE GetTop() const throw()
	{
		return top;
	}

	inline TYPE GetRight() const throw()
	{
		return right;
	}

	inline TYPE GetBottom() const throw()
	{
		return bottom;
	}

	inline TYPE GetWidth() const throw()
	{
		return right-left;
	}

	inline TYPE GetHeight() const throw()
	{
		return bottom-top;
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(right-left, bottom-top);
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(left, top);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(right, bottom);
	}

	void Normalize()
	{
		if (right < left)
		{
			TYPE t = left;
			left = right;
			right = t;
		}

		if (bottom < top)
		{
			TYPE t = top;
			top = bottom;
			bottom = t;
		}
	}

	bool Contains(TYPE x, TYPE y) const
	{
		return x >= left && y >= top && x < right && y < bottom;
	}

	bool Contains(const Point<TYPE>& pt) const
	{
		return pt.X >= left && pt.Y >= top && pt.X < right && pt.Y < bottom;
	}

	bool IntersectsWith(const BBox<TYPE>& rect) const
	{
		return (left < rect.right &&
			top < rect.bottom &&
			right > rect.left &&
			bottom > rect.top);
	}

	inline void SetEmpty() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline void SetBBox(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	inline void Inflate(TYPE dx, TYPE dy) throw()
	{
		left -= dx;
		right += dx;
		top -= dy;
		bottom += dy;
	}

	inline void Inflate(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left -= l;
		right += r;
		top -= t;
		bottom += b;
	}

	/*
	inline void Offset(TYPE dx, TYPE dy)
	{
		left += dx;
		top += dy;
		right += dx;
		bottom += dy;
	}
	*/

	BBox& operator +=(const Point<TYPE> pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;

		return *this;
	}

	BBox& operator -=(const Point<TYPE> pt) throw()
	{
		left -= pt.X;
		top -= pt.Y;
		right -= pt.X;
		bottom -= pt.Y;

		return *this;
	}

	BBox& operator *=(TYPE rhs) throw()
	{
		left *= rhs;
		top *= rhs;
		right *= rhs;
		bottom *= rhs;

		return *this;
	}

	BBox<double> operator +(const Point<double> pt) const throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		left += dx;
		top += dy;
		right += dx;
		bottom += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;
	}

	inline bool IsEmptyArea() const throw()
	{
		return (right <= left) || (bottom <= top);
	}

	TYPE Area() const throw()
	{
		return GetWidth() * GetHeight();
	}

	TYPE Circumference() const throw()
	{
		return GetWidth()*2 + GetHeight()*2;
	}

	bool Union(const BBox<TYPE> *lprcSrc1, const BBox<TYPE> *lprcSrc2);

	bool Equals(const BBox<TYPE>& other) const throw()
	{
		return
			left == other.left &&
			top == other.top &&
			right == other.right &&
			bottom == other.bottom;
	}

	BBox& operator = (const Rect<TYPE>& rect) throw()
	{
		left = rect.X;
		top = rect.Y;
		right = rect.GetRight();
		bottom = rect.GetBottom();

		return *this;
	}

	inline bool operator == (const BBox& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const BBox& other) const
	{
		return !Equals(other);
	}

	TYPE left, top, right, bottom;
};

template<> class BBox<double>
{
public:

	typedef double TYPE;

	inline CTOR BBox() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline CTOR BBox(const BBox& other) throw()
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
	}

	inline CTOR BBox(TYPE _left, TYPE _top, TYPE _right, TYPE _bottom) throw()
	{
		left = _left;
		top = _top;
		right = _right;
		bottom = _bottom;
	}

	inline CTOR BBox(const Point<TYPE>& topleft, const Point<TYPE>& bottomright) throw()
	{
		left = topleft.X;
		top = topleft.Y;
		right = bottomright.X;
		bottom = bottomright.Y;
	}

	inline CTOR BBox(const Rect<TYPE>& rect) throw()
	{
		left = rect.GetLeft();
		top = rect.GetTop();
		right = rect.GetRight();
		bottom = rect.GetBottom();
	}

	inline operator Rect<TYPE> () const throw()
	{
		return Rect<TYPE>(left, top, right-left, bottom-top);
	}

	static void Intersect(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MIN(a.right, b.right);
		c.bottom = MIN(a.bottom, b.bottom);
		c.left = MAX(a.left, b.left);
		c.top = MAX(a.top, b.top);
	}

	static void Union(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MAX(a.right, b.right);
		c.bottom = MAX(a.bottom, b.bottom);
		c.left = MIN(a.left, b.left);
		c.top = MIN(a.top, b.top);
	}

	inline TYPE GetLeft() const throw()
	{
		return left;
	}

	inline TYPE GetTop() const throw()
	{
		return top;
	}

	inline TYPE GetRight() const throw()
	{
		return right;
	}

	inline TYPE GetBottom() const throw()
	{
		return bottom;
	}

	inline TYPE GetWidth() const throw()
	{
		return right-left;
	}

	inline TYPE GetHeight() const throw()
	{
		return bottom-top;
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(right-left, bottom-top);
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(left, top);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(right, bottom);
	}

	void Normalize()
	{
		if (right < left)
		{
			TYPE t = left;
			left = right;
			right = t;
		}

		if (bottom < top)
		{
			TYPE t = top;
			top = bottom;
			bottom = t;
		}
	}

	bool Contains(TYPE x, TYPE y) const
	{
		return x >= left && y >= top && x < right && y < bottom;
	}

	bool Contains(const Point<TYPE>& pt) const
	{
		return pt.X >= left && pt.Y >= top && pt.X < right && pt.Y < bottom;
	}

	bool IntersectsWith(const BBox<TYPE>& rect) const
	{
		return (left < rect.right &&
			top < rect.bottom &&
			right > rect.left &&
			bottom > rect.top);
	}

	inline void SetEmpty() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline void SetBBox(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	inline void Inflate(TYPE dx, TYPE dy) throw()
	{
		left -= dx;
		right += dx;
		top -= dy;
		bottom += dy;
	}

	inline void Inflate(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left -= l;
		right += r;
		top -= t;
		bottom += b;
	}

	BBox& operator +=(const Point<TYPE> pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;

		return *this;
	}

	BBox& operator -=(const Point<TYPE> pt) throw()
	{
		left -= pt.X;
		top -= pt.Y;
		right -= pt.X;
		bottom -= pt.Y;

		return *this;
	}

	BBox& operator *=(TYPE rhs) throw()
	{
		left *= rhs;
		top *= rhs;
		right *= rhs;
		bottom *= rhs;

		return *this;
	}

	BBox& operator /=(TYPE rhs) throw()
	{
		double res = 1.0 / rhs;

		left *= res;
		top *= res;
		right *= res;
		bottom *= res;

		return *this;
	}

	BBox<double> operator +(const Point<int> pt) const throw()
	{
		return BBox<double>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<double> operator +(const Point<long long> pt) const throw()
	{
		return BBox<double>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<double> operator +(const Point<float> pt) const throw()
	{
		return BBox<double>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<double> operator +(const Point<double> pt) const throw()
	{
		return BBox<double>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<double> operator -(const Point<int> pt) const throw()
	{
		return BBox<double>(left - pt.X, top - pt.Y, right - pt.X, bottom - pt.Y);
	}

	BBox<double> operator -(const Point<long long> pt) const throw()
	{
		return BBox<double>(left - pt.X, top - pt.Y, right - pt.X, bottom - pt.Y);
	}

	BBox<double> operator -(const Point<float> pt) const throw()
	{
		return BBox<double>(left - pt.X, top - pt.Y, right - pt.X, bottom - pt.Y);
	}

	BBox<double> operator -(const Point<double> pt) const throw()
	{
		return BBox<double>(left - pt.X, top - pt.Y, right - pt.X, bottom - pt.Y);
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		left += dx;
		top += dy;
		right += dx;
		bottom += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;
	}

	inline bool IsEmptyArea() const throw()
	{
		return (right <= left) || (bottom <= top);
	}

	TYPE Area() const throw()
	{
		return GetWidth() * GetHeight();
	}

	TYPE Circumference() const throw()
	{
		return GetWidth()*2 + GetHeight()*2;
	}

	bool Union(const BBox<TYPE> *lprcSrc1, const BBox<TYPE> *lprcSrc2);

	bool Equals(const BBox<TYPE>& other) const throw()
	{
		return
			left == other.left &&
			top == other.top &&
			right == other.right &&
			bottom == other.bottom;
	}

	BBox& operator = (const Rect<TYPE>& rect) throw()
	{
		left = rect.X;
		top = rect.Y;
		right = rect.GetRight();
		bottom = rect.GetBottom();

		return *this;
	}

	inline bool operator == (const BBox& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const BBox& other) const
	{
		return !Equals(other);
	}

	TYPE left, top, right, bottom;
};

template<> class BBox<float>
{
public:

	typedef float TYPE;

	inline CTOR BBox() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline CTOR BBox(const BBox& other) throw()
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
	}

	inline CTOR BBox(TYPE _left, TYPE _top, TYPE _right, TYPE _bottom) throw()
	{
		left = _left;
		top = _top;
		right = _right;
		bottom = _bottom;
	}

	inline CTOR BBox(const Point<TYPE>& topleft, const Point<TYPE>& bottomright) throw()
	{
		left = topleft.X;
		top = topleft.Y;
		right = bottomright.X;
		bottom = bottomright.Y;
	}

	inline CTOR BBox(const Rect<TYPE>& rect) throw()
	{
		left = rect.GetLeft();
		top = rect.GetTop();
		right = rect.GetRight();
		bottom = rect.GetBottom();
	}

	inline operator Rect<TYPE> () const throw()
	{
		return Rect<TYPE>(left, top, right-left, bottom-top);
	}

#ifdef _D2DBASETYPES_INCLUDED
	inline operator D2D_RECT_F () const throw()
	{
		return *(D2D_RECT_F*)this;		// same layout
	}
#endif

	static void Intersect(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MIN(a.right, b.right);
		c.bottom = MIN(a.bottom, b.bottom);
		c.left = MAX(a.left, b.left);
		c.top = MAX(a.top, b.top);
	}

	static void Union(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MAX(a.right, b.right);
		c.bottom = MAX(a.bottom, b.bottom);
		c.left = MIN(a.left, b.left);
		c.top = MIN(a.top, b.top);
	}

	inline TYPE GetLeft() const throw()
	{
		return left;
	}

	inline TYPE GetTop() const throw()
	{
		return top;
	}

	inline TYPE GetRight() const throw()
	{
		return right;
	}

	inline TYPE GetBottom() const throw()
	{
		return bottom;
	}

	inline TYPE GetWidth() const throw()
	{
		return right-left;
	}

	inline TYPE GetHeight() const throw()
	{
		return bottom-top;
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(right-left, bottom-top);
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(left, top);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(right, bottom);
	}

	void Normalize()
	{
		if (right < left)
		{
			TYPE t = left;
			left = right;
			right = t;
		}

		if (bottom < top)
		{
			TYPE t = top;
			top = bottom;
			bottom = t;
		}
	}

	bool Contains(TYPE x, TYPE y) const throw()
	{
		return x >= left && y >= top && x < right && y < bottom;
	}

	bool Contains(const Point<TYPE>& pt) const throw()
	{
		return pt.X >= left && pt.Y >= top && pt.X < right && pt.Y < bottom;
	}

	bool IntersectsWith(const BBox<TYPE>& rect) const
	{
		return (left < rect.right &&
			top < rect.bottom &&
			right > rect.left &&
			bottom > rect.top);
	}

	inline void SetEmpty() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline void SetBBox(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	inline void Inflate(TYPE dx, TYPE dy) throw()
	{
		left -= dx;
		right += dx;
		top -= dy;
		bottom += dy;
	}

	inline void Inflate(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left -= l;
		right += r;
		top -= t;
		bottom += b;
	}

	BBox& operator +=(const Point<TYPE> pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;

		return *this;
	}

	BBox& operator -=(const Point<TYPE> pt) throw()
	{
		left -= pt.X;
		top -= pt.Y;
		right -= pt.X;
		bottom -= pt.Y;

		return *this;
	}

	BBox& operator *=(float rhs) throw()
	{
		left *= rhs;
		top *= rhs;
		right *= rhs;
		bottom *= rhs;

		return *this;
	}

	BBox& operator /=(float rhs) throw()
	{
		float res = 1.0f / rhs;

		left *= res;
		top *= res;
		right *= res;
		bottom *= res;

		return *this;
	}

	BBox<double> operator +(const Point<double> pt) const throw()
	{
		return BBox<double>(	left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		left += dx;
		top += dy;
		right += dx;
		bottom += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;
	}

	inline bool IsEmptyArea() const throw()
	{
		return (right <= left) || (bottom <= top);
	}

	TYPE Area() const throw()
	{
		return GetWidth() * GetHeight();
	}

	TYPE Circumference() const throw()
	{
		return GetWidth()*2 + GetHeight()*2;
	}

	bool Union(const BBox<TYPE> *lprcSrc1, const BBox<TYPE> *lprcSrc2);

	bool Equals(const BBox<TYPE>& other) const throw()
	{
		return
			left == other.left &&
			top == other.top &&
			right == other.right &&
			bottom == other.bottom;
	}

	BBox& operator = (const Rect<TYPE>& rect) throw()
	{
		left = rect.X;
		top = rect.Y;
		right = rect.GetRight();
		bottom = rect.GetBottom();

		return *this;
	}

	inline bool operator == (const BBox& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const BBox& other) const
	{
		return !Equals(other);
	}

	TYPE left, top, right, bottom;
};

template<> class BBox<int>
{
public:

	typedef int TYPE;

	inline CTOR BBox() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline CTOR BBox(const BBox& other) throw()
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
	}

	inline CTOR BBox(TYPE _left, TYPE _top, TYPE _right, TYPE _bottom) throw()
	{
		left = _left;
		top = _top;
		right = _right;
		bottom = _bottom;
	}

	inline CTOR BBox(const Point<TYPE>& topleft, const Point<TYPE>& bottomright) throw()
	{
		left = topleft.X;
		top = topleft.Y;
		right = bottomright.X;
		bottom = bottomright.Y;
	}

	inline CTOR BBox(const Rect<TYPE>& rect) throw()
	{
		left = rect.GetLeft();
		top = rect.GetTop();
		right = rect.GetRight();
		bottom = rect.GetBottom();
	}

	inline operator Rect<TYPE> () const throw()
	{
		return Rect<TYPE>(left, top, right-left, bottom-top);
	}

	inline operator RECT () const throw()
	{
		return *(RECT*)this;		// same layout
	}

	static void Intersect(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MIN(a.right, b.right);
		c.bottom = MIN(a.bottom, b.bottom);
		c.left = MAX(a.left, b.left);
		c.top = MAX(a.top, b.top);
	}

	static void Union(BBox<TYPE>& c,
		const BBox<TYPE>& a,
		const BBox<TYPE>& b)
	{
		c.right = MAX(a.right, b.right);
		c.bottom = MAX(a.bottom, b.bottom);
		c.left = MIN(a.left, b.left);
		c.top = MIN(a.top, b.top);
	}

	inline TYPE GetLeft() const throw()
	{
		return left;
	}

	inline TYPE GetTop() const throw()
	{
		return top;
	}

	inline TYPE GetRight() const throw()
	{
		return right;
	}

	inline TYPE GetBottom() const throw()
	{
		return bottom;
	}

	inline TYPE GetWidth() const throw()
	{
		return right-left;
	}

	inline TYPE GetHeight() const throw()
	{
		return bottom-top;
	}

	inline Size<TYPE> GetSize() const throw()
	{
		return Size<TYPE>(right-left, bottom-top);
	}

	inline Point<TYPE> GetTopLeft() const throw()
	{
		return Point<TYPE>(left, top);
	}

	inline Point<TYPE> GetBottomRight() const throw()
	{
		return Point<TYPE>(right, bottom);
	}

	void Normalize() throw()
	{
		if (right < left)
		{
			TYPE t = left;
			left = right;
			right = t;
		}

		if (bottom < top)
		{
			TYPE t = top;
			top = bottom;
			bottom = t;
		}
	}

	bool Contains(TYPE x, TYPE y) const throw()
	{
		return x >= left && y >= top && x < right && y < bottom;
	}

	bool Contains(const Point<TYPE>& pt) const
	{
		return pt.X >= left && pt.Y >= top && pt.X < right && pt.Y < bottom;
	}

	bool IntersectsWith(const BBox<TYPE>& rect) const throw()
	{
		return (left < rect.right &&
			top < rect.bottom &&
			right > rect.left &&
			bottom > rect.top);
	}

	inline void SetEmpty() throw()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	inline void SetBBox(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	inline void Inflate(TYPE dx, TYPE dy) throw()
	{
		left -= dx;
		right += dx;
		top -= dy;
		bottom += dy;
	}

	inline void Inflate(TYPE l, TYPE t, TYPE r, TYPE b) throw()
	{
		left -= l;
		right += r;
		top -= t;
		bottom += b;
	}

	BBox& operator +=(const Point<TYPE> pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;

		return *this;
	}

	BBox& operator -=(const Point<TYPE> pt) throw()
	{
		left -= pt.X;
		top -= pt.Y;
		right -= pt.X;
		bottom -= pt.Y;

		return *this;
	}

	BBox& operator *=(int rhs) throw()
	{
		left *= rhs;
		top *= rhs;
		right *= rhs;
		bottom *= rhs;

		return *this;
	}

	BBox& operator *=(float rhs) throw()
	{
		left = int(left*rhs);
		top = int(top*rhs);
		right = int(right*rhs);
		bottom = int(bottom*rhs);

		return *this;
	}

	BBox& operator *=(double rhs) throw()
	{
		left = int(left*rhs);
		top = int(top*rhs);
		right = int(right*rhs);
		bottom = int(bottom*rhs);

		return *this;
	}

	BBox& operator /=(double rhs) throw()
	{
		double res = 1.0 / rhs;

		left = int(left*res);
		top = int(top*res);
		right = int(right*res);
		bottom = int(bottom*res);

		return *this;
	}

	BBox<int> operator +(const Point<int> pt) const throw()
	{
		return BBox<int>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<long long> operator +(const Point<long long> pt) const throw()
	{
		return BBox<long long>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<float> operator +(const Point<float> pt) const throw()
	{
		return BBox<float>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<double> operator +(const Point<double> pt) const throw()
	{
		return BBox<double>(left + pt.X, top + pt.Y, right + pt.X, bottom + pt.Y);
	}

	BBox<double> operator -(const Point<double> pt) const throw()
	{
		return BBox<double>(left - pt.X, top - pt.Y, right - pt.X, bottom - pt.Y);
	}

	inline void Translate(TYPE dx, TYPE dy) throw()
	{
		left += dx;
		top += dy;
		right += dx;
		bottom += dy;
	}

	inline void Translate(const Point<TYPE>& pt) throw()
	{
		left += pt.X;
		top += pt.Y;
		right += pt.X;
		bottom += pt.Y;
	}

	inline bool IsEmptyArea() const throw()
	{
		return (right <= left) || (bottom <= top);
	}

	TYPE Area() const throw()
	{
		return GetWidth() * GetHeight();
	}

	TYPE Circumference() const throw()
	{
		return GetWidth()*2 + GetHeight()*2;
	}

	bool Union(const BBox<TYPE> *lprcSrc1, const BBox<TYPE> *lprcSrc2);

	bool Equals(const BBox<TYPE>& other) const throw()
	{
		return
			left == other.left &&
			top == other.top &&
			right == other.right &&
			bottom == other.bottom;
	}

	BBox& operator = (const Rect<TYPE>& rect) throw()
	{
		left = rect.X;
		top = rect.Y;
		right = rect.GetRight();
		bottom = rect.GetBottom();

		return *this;
	}

	inline bool operator == (const BBox& other) const throw()
	{
		return Equals(other);
	}

	inline bool operator != (const BBox& other) const throw()
	{
		return !Equals(other);
	}

	TYPE left, top, right, bottom;
};

typedef BBox<int> BBoxi;
typedef BBox<float> BBoxF;
typedef BBox<float> BBoxf;
typedef BBox<double> BBoxD;
typedef BBox<double> BBoxd;

}	// gm
}	// System
