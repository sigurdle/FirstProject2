#ifndef w3c_SVGMatrix_h
#define w3c_SVGMatrix_h

namespace System
{
namespace Web
{

interface ISVGMatrixListener
{
	virtual void OnChanged() = 0;
};

class WEBEXT SVGMatrix : public System::Object
{
public:
	CTOR SVGMatrix();
	CTOR SVGMatrix(const gm::matrix3d& m);
	CTOR SVGMatrix(double a, double b, double c, double d, double e, double f);
	~SVGMatrix();

	double get_a() const;
	void set_a(double a);

	double get_b() const;
	void set_b(double b);

	double get_c() const;
	void set_c(double c);

	double get_d() const;
	void set_d(double d);

	double get_e() const;
	void set_e(double e);

	double get_f() const;
	void set_f(double f);

	void assign(double a, double b, double c, double d, double e, double f);

	SVGMatrix* skewY(double angle) const;
	SVGMatrix* skewX(double angle) const;
	SVGMatrix* flipY() const;
	SVGMatrix* flipX() const;
	SVGMatrix* rotateFromVector(double x, double y) const;
	SVGMatrix* rotate(double angle) const;
	SVGMatrix* scaleNonUniform(double scaleFactorX, double scaleFactorY) const;
	SVGMatrix* scale(double scaleFactor) const;
	SVGMatrix* translate(double x, double y) const;
	SVGMatrix* inverse() const;
	SVGMatrix* multiply(SVGMatrix* secondMatrix) const;

	SVGMatrix& operator = (const SVGMatrix& other);

	gm::matrix3d& GetM()
	{
		return m_matrix;
	}

	const gm::matrix3d& GetM() const
	{
		return m_matrix;
	}

	/* ??
	double operator ()(int row, int col) const
	{
		return m_matrix[row][col];
	}
	*/

protected:

	friend class SVGTransform;
	friend class SVGTransformMutable;

	gm::matrix3d m_matrix;
	ISVGMatrixListener* m_owner;

private:

	CTOR SVGMatrix(const SVGMatrix& other)
	{
	}
};

}	// w3c
}

#endif // w3c_SVGMatrix_h
