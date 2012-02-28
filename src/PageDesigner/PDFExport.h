#include "PDF.h"

#import "..\LPDF\LPDF.tlb" named_guids

class CPDFExport
{
public:
//	FILE* m_fp;
	CComPtr<IPDDocument> m_pddoc;

	LPDFLib::IPDFPDDocPtr m_pdfdoc;

	CPDFExport()
	{
	}

	void SavePath(LPDFLib::IPDFEPath* pPath, IPDPath* pdpath, IPDMatrix* matpdf, RectD pageRect);
	void SaveObjectFrame(LPDFLib::IPDFEContent* pContent, IPDObjectFrame* pdframe, IPDMatrix* matpdf, RectD pageRect);
	void SaveObjectContentText(LPDFLib::IPDFEContent* pContent, IPDContentText* pdcontentText, IPDMatrix* matpdf, RectD pageRect);
	void SaveObjectGraphic(LPDFLib::IPDFEContent* pContent, IPDContentGraphic* pdgraphic, IPDMatrix* matpdf, RectD pageRect);
	void SaveObjectGroup(LPDFLib::IPDFEContent* pContent, IPDObjectGroup* pdgroup, IPDMatrix* matpdf, RectD pageRect);

	HRESULT Export(TCHAR* pathName, IPDDocument* pddoc);
};
