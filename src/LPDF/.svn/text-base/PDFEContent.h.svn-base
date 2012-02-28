#ifndef __PDFECONTENT_H_
#define __PDFECONTENT_H_

#include "PDFObject.h"

namespace System
{
namespace PDF
{

class CPDFPDPage;
class CPDFEElement;

class PDFExt CPDFEContent : public CPDFObject //<IPDFEContent>
{
public:
	CTOR CPDFEContent()
	{
		m_pPage = NULL;
	}

	void WriteToStream(std::FILE* fp);

	int FindDictObject(CPDFCosDict* pXObjectDict, CPDFCosObj* pObject);

	void UpdateResources(CPDFCosDict* pCosResources, CPDFEElement* element);

	void UpdateResources(CPDFCosDict* pCosResources)
	{
		for (int i = 0; i < m_elements.GetSize(); i++)
		{
			UpdateResources(pCosResources, m_elements[i]);
		}
	}

	void AddElem(long addAfterIndex, CPDFEElement* pdeElement);
	uint GetNumElems();
	PDFEType GetType() const
	{
		return kPDFEContent;
	}

public:

	CPDFPDPage* m_pPage;
	vector<CPDFEElement*> m_elements;
};

}	// PDF
}

#endif //__PDFECONTENT_H_
