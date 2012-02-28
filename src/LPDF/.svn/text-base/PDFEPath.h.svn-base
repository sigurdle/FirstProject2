#ifndef __PDFEPATH_H_
#define __PDFEPATH_H_

#include "PDFEElement.h"

namespace System
{
namespace PDF
{

class CPDFEPath : public CPDFEElement //<IPDFEPath>
{
public:

	CPDFEPath()
	{
		m_opFlags = 0;
	}

	~CPDFEPath()
	{
		for (int i = 0; i < m_segments.GetSize(); i++)
		{
		//	delete m_segments[i];
		}
		m_segments.RemoveAll();
	}

	class CPathSegment
	{
	public:
		PDFEPathElementType segType;
		double x1, y1, x2, y2, x3, y3;
	};

	vector<CPathSegment*> m_segments;

	uint32 m_opFlags;

	virtual long GetType()
	{
		return 2;
	}

	void SetPaintOp(long opFlags)
	{
		m_opFlags = opFlags;
	}

	/*
	void SetData(long* data, long dataSize)
	{
		ATLASSERT((dataSize % 4) == 0);
		if (m_data)
		{
			m_data = NULL;
			m_dataSize = 0;
		}

		m_data = (long*)malloc(dataSize);
		if (m_data)
		{
			memcpy(m_data, data, dataSize);
			m_dataSize = dataSize;
		}
	}
  */

	virtual void WriteToStream(std::FILE* fp);

// IPDFEPath
public:
	uint32 GetPaintOp();
	void SetPaintOp(uint32 op);
	void AddSegment(PDFEPathElementType segType, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2, /*[in]*/ double x3, /*[in]*/ double y3);
	PDFEType GetType() const
	{
		return kPDFEPath;
	}
};

}
}

#endif //__PDFEPATH_H_
