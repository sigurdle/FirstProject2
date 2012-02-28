// PDFEColorSpace.h : Declaration of the CPDFEColorSpace

#ifndef __PDFECOLORSPACE_H_
#define __PDFECOLORSPACE_H_

#include "PDFObject.h"

namespace System
{
namespace PDF
{

class CPDFEColorSpace : 
	public CPDFObject//<IPDFEColorSpace>
{
public:
	CPDFEColorSpace()
	{
	}

// IPDFEColorSpace
public:
	PDFEType GetType() const
	{
		return kPDFEColorSpace;
	}
};

}
}

#endif //__PDFECOLORSPACE_H_
