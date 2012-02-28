#ifndef __PDFPDDOC_H_
#define __PDFPDDOC_H_

//#include "resource.h"       // main symbols

#ifndef PDFExt
#define PDFExt	DECLSPEC_DLLIMPORT
#endif

#include "PDFObject.h"

//class CPDFCosDoc;

namespace System
{
namespace PDF
{

class CPDFPDPage;
class CPDFEMatrix;
class CPDFEImage;
class CPDFEPath;

class PDFExt CPDFPDDoc : public CPDFObject
{
public:
	CTOR CPDFPDDoc();

	CPDFEPath* CreatePath();
	CPDFCosDoc* GetCosDoc();
	void SetCosDoc(CPDFCosDoc* cos);

	CPDFEImage* CreateImageFromCosObj(/*[in]*/ CPDFCosStream* imageObj, /*[in]*/ CPDFEMatrix* matrix);
	CPDFEMatrix* CreateMatrix();
	void Save(System::StringA* pathName);
	void SetInfo(System::StringA* binfoKey, /*[in]*/ System::StringA* bvalue);
	CPDFPDPage* CreatePage(long afterPageNum, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	ErrorCode Create();
	PDFEType GetType() const
	{
		return kPDFEDoc;
	}

	void Read(System::StringA* filename);

public:

	CPDFCosDoc* m_cos;

	vector<CPDFPDPage*> m_pages;
	//CArray<CPDFFont*,CPDFFont*> m_fonts;
};

}	// PDF
}
#endif //__PDFPDDOC_H_
