#ifndef __PDFEMATRIX_H_
#define __PDFEMATRIX_H_

//#include "../Draw/LDraw.h"

namespace System
{
namespace PDF
{

class CPDFEMatrix : public System::Object
	//public IPDFEMatrix
{
public:
	CPDFEMatrix()
	{
		m_matrix = LDraw::matrix3f::getIdentity();
	}

	double get_f();
	void set_f(/*[in]*/ double newVal);
	double get_e();
	void set_e(/*[in]*/ double newVal);
	double get_d();
	void set_d(/*[in]*/ double newVal);
	double get_c();
	void set_c(/*[in]*/ double newVal);
	double get_b();
	void set_b(/*[in]*/ double newVal);
	double get_a();
	void set_a(/*[in]*/ double newVal);

public:

	LDraw::matrix3f m_matrix;
};

}
}

#endif //__PDFEMATRIX_H_
