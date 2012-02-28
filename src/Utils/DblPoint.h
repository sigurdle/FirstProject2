#pragma once

#define _AFXWIN_INLINE	inline

typedef struct tagDblPOINT
{
	double x;
	double y;
}
DblPOINT;

class CDblPoint : public DblPOINT
{
public:
// Constructors

	// create an uninitialized point
	CDblPoint() {};
	// create from two values
	CDblPoint(double initX, double initY) { x = initX; y = initY; }
	CDblPoint(int initX, int initY) { x = initX; y = initY; }
	// create from another point
	CDblPoint(DblPOINT initPt) { x = initPt.x; y = initPt.y; };
	CDblPoint(POINT initPt) { x = initPt.x; y = initPt.y; };

// Operations

// translate the point
	void Offset(double xOffset, double yOffset) { x += xOffset; y += yOffset; }
	void Offset(DblPOINT point)					 { x += point.x; y += point.y; }

	BOOL operator==(DblPOINT point) const	{ return (x == point.x && y == point.y); }
	BOOL operator!=(DblPOINT point) const	{ return (x != point.x || y != point.y); }
	void operator+=(DblPOINT point)			{ x += point.x; y += point.y; }
	void operator-=(DblPOINT point)			{ x -= point.x; y -= point.y; }
	void operator*=(double v)					{ x *= v, y *= v; }
	void operator/=(double v)					{ x /= v, y /= v; }

// Operators returning CDblPoint values
	CDblPoint operator-() const				{ return CDblPoint(-x, -y); }
	CDblPoint operator+(DblPOINT point) const { return CDblPoint(x + point.x, y + point.y); }
	CDblPoint operator*(DblPOINT point)	const { return CDblPoint(x * point.x, y * point.y); }
	CDblPoint operator/(DblPOINT point)	const { return CDblPoint(x / point.x, y / point.y); }
	CDblPoint operator*(double v)			const { return CDblPoint(x * v, y * v); }
	CDblPoint operator/(double v)			const { return CDblPoint(x / v, y / v); }
	CDblPoint operator=(POINT pt)			const { return CDblPoint(pt.x, pt.y); }
};

inline CDblPoint operator-(DblPOINT& p1, DblPOINT& p2)
{
	return CDblPoint(p1.x - p2.x, p1.y - p2.y);
}

inline CDblPoint operator+(DblPOINT& p1, DblPOINT& p2)
{
	return CDblPoint(p1.x + p2.x, p1.y + p2.y);
}
