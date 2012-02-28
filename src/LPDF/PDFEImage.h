#ifndef __PDFEIMAGE_H_
#define __PDFEIMAGE_H_

#include "PDFEElement.h"

namespace System
{
namespace PDF
{

class CPDFEImage : 
	public CPDFEElement//Impl<IPDFEImage>
{
public:
	CPDFEImage()
	{
		m_nIndex = 0;
	}

	CPDFCosStream* m_cos;

	int m_nIndex;

	virtual void WriteToStream(std::FILE* fp);

	PDFEType GetType() const
	{
		return kPDFEImage;
	}
};

}
}


#endif //__PDFEIMAGE_H_
