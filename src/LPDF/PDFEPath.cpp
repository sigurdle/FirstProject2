// PDFEPath.cpp : Implementation of CPDFEPath
#include "stdafx.h"
#include "LPDF.h"
#include "PDFEPath.h"

#include "PDFEMatrix.h"
#include "PDFEGraphicState.h"

namespace System
{
namespace PDF
{

/////////////////////////////////////////////////////////////////////////////
// CPDFEPath

//virtual
void CPDFEPath::WriteToStream(std::FILE* fp)
{
	std::fprintf(fp, "q\r\n"); // Save graphics state

#if 0
	if (m_gstate.extGState)
	{
		fprintf(fp, "/GS%d gs\r\n", m_gstate.extGState->m_nIndex);
	}
#endif
	std::fprintf(fp, "%g w\r\n", m_gstate->m_lineWidth);
#if 0
	fprintf(fp, "%g M\r\n", m_gstate.miterLimit);
	//fprintf(fp, "%d j\r\n", m_gstate.lineCap);
	//fprintf(fp, "%d J\r\n", m_gstate.lineJoin);
#endif

//	fprintf(fp, "%.4g %.4g %.4g %.4g %.4g %.4g cm\r\n", m_matrix.a, m_matrix.b, m_matrix.c, m_matrix.d, m_matrix.h, m_matrix.v);
	double a = m_matrix->get_a();
	double b = m_matrix->get_b();
	double c = m_matrix->get_c();
	double d = m_matrix->get_d();
	double e = m_matrix->get_e();
	double f = m_matrix->get_f();
	std::fprintf(fp, "%g %g %g %g %g %g cm\r\n", a, b, c, d, e, f);

#if 0
	fprintf(fp, "%g %g %g RG\r\n", m_gstate.strokeColorSpec.value.color[0], m_gstate.strokeColorSpec.value.color[1], m_gstate.strokeColorSpec.value.color[2]);
	fprintf(fp, "%g %g %g rg\r\n", m_gstate.fillColorSpec.value.color[0], m_gstate.fillColorSpec.value.color[1], m_gstate.fillColorSpec.value.color[2]);
#endif

	for (int i = 0; i < m_segments.GetSize(); i++)
	{
		CPathSegment* pSeg = m_segments[i];

		if (pSeg->segType == kPDFEMoveTo)
		{
			std::fprintf(fp, "%g %g m", pSeg->x1, pSeg->y1);
		}
		else if (pSeg->segType == kPDFELineTo)
		{
			std::fprintf(fp, "%g %g l", pSeg->x1, pSeg->y1);
		}
		else if (pSeg->segType == kPDFECurveTo)
		{
			std::fprintf(fp, "%g %g %g %g %g %g c",
				pSeg->x1, pSeg->y1,
				pSeg->x2, pSeg->y2,
				pSeg->x3, pSeg->y3
				);
		}
		else if (pSeg->segType == kPDFEClosePath)	// close
		{
			std::fprintf(fp, "h");
		}
		else
			ASSERT(0);

		std::fprintf(fp, "\r\n");
	}

	if (m_opFlags & (kPDFEStroke | kPDFEFill))
		std::fprintf(fp, "B");
	else if (m_opFlags & kPDFEFill)
		std::fprintf(fp, "f");
	else if (m_opFlags & kPDFEStroke)
		std::fprintf(fp, "S");

	std::fprintf(fp, "\r\n");
	std::fprintf(fp, "Q\r\n");// Restore graphics state
}

void CPDFEPath::AddSegment(PDFEPathElementType segType, double x1, double y1, double x2, double y2, double x3, double y3)
{
	CPathSegment* pSeg = new CPathSegment;
	pSeg->segType = segType;
	pSeg->x1 = x1;
	pSeg->y1 = y1;
	pSeg->x2 = x2;
	pSeg->y2 = y2;
	pSeg->x3 = x3;
	pSeg->y3 = y3;

	m_segments.Add(pSeg);
}

void CPDFEPath::SetPaintOp(uint32 op)
{
	m_opFlags = op;
}

uint32 CPDFEPath::GetPaintOp()
{
	return m_opFlags;
}

}
}
