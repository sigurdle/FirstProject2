#ifndef __PDFPDPAGE_H_
#define __PDFPDPAGE_H_

#include "PDFObject.h"

namespace System
{
namespace PDF
{

class CPDFPDDoc;
class CPDFEContent;

class PDFExt CPDFPDPage : 
	public CPDFObject //<IPDFPDPage>
{
public:
	CPDFPDPage()
	{
		m_pDoc = NULL;
		m_pContent = NULL;
	}

	void FinalRelease();

	CPDFPDDoc* GetDoc();
	void ReleasePDEContent();
	CPDFEContent* AcquirePDEContent();
	PDFEType GetType() const
	{
		return kPDFEPage;
	}

public:

	CPDFCosDict* m_cos;

	CPDFEContent* m_pContent;

	CPDFPDDoc* m_pDoc;

	CPDFCosStream* m_pCosContents;
	CPDFCosDict* m_pCosResources;

};

}	// PDF
}

#endif //__PDFPDPAGE_H_
