#ifndef __PDFETEXT_H_
#define __PDFETEXT_H_

#include "PDFEElement.h"

namespace System
{
namespace PDF
{

class CPDFEText : 
	public CPDFEElement//<IPDFEText>
{
public:
	CPDFEText()
	{
	}

	virtual void WriteToStream(std::FILE* fp);

// IPDFEText
public:
	PDFEType GetType() const
	{
		return kPDFEText;
	}
};

}
}

#endif //__PDFETEXT_H_
