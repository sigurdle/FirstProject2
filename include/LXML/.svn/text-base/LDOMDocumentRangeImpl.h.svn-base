#ifndef __LDOMDOCUMENTRANGEIMPL_H
#define __LDOMDOCUMENTRANGEIMPL_H

#include "DOMRange.h"

namespace System
{
namespace Web
{

class DocumentRangeImplImpl :
	public IDocumentRange
{
public:
	vector<Range*> m_ranges;
};

template<class T> class DocumentRangeImpl :
	public DocumentRangeImplImpl
{
public:
	CTOR DocumentRangeImpl()
	{
	}

	~DocumentRangeImpl()
	{
		for (unsigned int i = 0; i < m_ranges.size(); i++)
		{
			m_ranges[i]->m_pDocumentRange = NULL;
		//	m_ranges[i]->Release();
		}
	}

	/*
	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
		for (int i = 0; i < m_ranges.GetSize(); i++)
		{
			m_ranges[i]->m_pDocumentRange = NULL;
			m_ranges[i]->Release();
		}
		m_ranges.RemoveAll();
	}
	*/

	Range* createRange()
	{
		Range* pRange = new Range;
		pRange->m_pDocumentRange = this;
		m_ranges.Add(pRange);

		return pRange;
	}
};

}	// Web
}

#endif	// __LDOMDOCUMENTRANGEIMPL_H
