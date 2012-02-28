#ifndef __PDFEGRAPHICSTATE_H_
#define __PDFEGRAPHICSTATE_H_

#include "PDFObject.h"

namespace System
{
namespace PDF
{

class CPDFEExtGState;

class CPDFEGraphicState : public System::Object//IPDFEGraphicState
{
public:
	CPDFEGraphicState()
	{
	}

	CPDFEExtGState* get_extGState();
	void set_extGState(CPDFEExtGState* newVal);
	double get_miterLimit();
	void set_miterLimit(double newVal);
	long get_lineJoin();
	void set_lineJoin(long newVal);
	long get_lineCap();
	void set_lineCap(long newVal);
	double get_lineWidth() const
	{
		return m_lineWidth;
	}

	void set_lineWidth(double newVal);

public:

	double m_lineWidth;
	CPDFEExtGState* m_extGState;
};

}
}

#endif //__PDFEGRAPHICSTATE_H_
