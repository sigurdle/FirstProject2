#ifndef Web_SVGTransform_h
#define Web_SVGTransform_h

namespace System
{
namespace Web
{

/*
interface SVGTransformListener
{
public:
	virtual void OnTransformChange(SVGTransform* pTransform) = 0;
};
*/

class SVGEXT SVGTransform : public Object
{
public:
	CTOR SVGTransform();
	CTOR SVGTransform(const SVGMatrix* matrix);
	~SVGTransform();

	SVGTransformList* get_transformList();

	double get_angle() const;
	SVGMatrix* get_matrix() const;
	SVGTransformType get_type() const;

	virtual void setSkewY(double angle);
	virtual void setSkewX(double angle);
	virtual void setRotate(double angle, double cx, double cy);
	virtual void setScale(double sx, double sy);
	virtual void setTranslate(double tx, double ty);
	virtual void setMatrix(const SVGMatrix* matrix);

	void setStringValue(StringIn str);
	String getStringValue();
	void InterpolateValue(const SVGTransform& a, const SVGTransform& b, double t);

protected:

	void readOnly();

	friend class SVGTransformList;
	friend class SVGTransformListMutable;
	friend class CAttributeTransformType;

	void SetSkewX(double angle);
	void SetSkewY(double angle);
	void SetRotate(double angle, double cx, double cy);
	void SetScale(double sx, double sy);
	void SetTranslate(double tx, double ty);

//	SVGTransformListener* m_pListener;	

	double m_x, m_y;	// General, tx,ty, sx,sy, cx,cy
	double m_angle;
	SVGTransformList* m_owner;
	SVGMatrix* m_matrix;
	SVGTransformType m_type;
};

class SVGEXT SVGTransformMutable : public SVGTransform
{
public:
	virtual void setSkewY(double angle);
	virtual void setSkewX(double angle);
	virtual void setRotate(double angle, double cx, double cy);
	virtual void setScale(double sx, double sy);
	virtual void setTranslate(double tx, double ty);
	virtual void setMatrix(const SVGMatrix* matrix);

private:

	void OnChanged();
};

}	// Web
}

#endif // Web_SVGTransform_h
