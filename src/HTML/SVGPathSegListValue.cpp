#include "stdafx.h"
#include "HTML2.h"

#include "SVGPathSegListValue.h"

namespace System
{
namespace Web
{

SVGPathSegListValue::SVGPathSegListValue()
{
	m_seglist = NULL;
	m_normalizedseglist = NULL;
}

SVGPathSegListValue::~SVGPathSegListValue()
{
}

/*
int SVGPathSegListValue::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<SVGPathSegList>::CreateInstance(&m_seglist);
	if (FAILED(hr)) return hr;
	m_seglist->m_pListener = this;
	m_seglist->AddRef();

	hr = CComObject<SVGPathSegList>::CreateInstance(&m_normalizedseglist);
	if (FAILED(hr)) return hr;
	m_normalizedseglist->m_pListener = this;
	m_normalizedseglist->AddRef();

	return 0;
}

void SVGPathSegListValue::FinalRelease()
{
	if (m_seglist)
	{
		m_seglist->m_pListener = NULL;
		m_seglist->Release();
		m_seglist = NULL;
	}

	if (m_normalizedseglist)
	{
		m_normalizedseglist->m_pListener = NULL;
		m_normalizedseglist->Release();
		m_normalizedseglist = NULL;
	}
}
*/

void SVGPathSegListValue::OnPathSegListChange(SVGPathSegList* pSegList)
{
	if (pSegList == m_seglist)
	{
		// Normalize
		m_normalizedseglist->RemoveAll();
		m_normalizedseglist->NormalizePathSegList(m_seglist);
	}
	else if (pSegList == m_normalizedseglist)
	{
	// Copy the normalized seglist to the the seglist
		m_seglist->RemoveAll();
		m_seglist->AddSegListNoUpdate(m_normalizedseglist);
	}
	else
		ASSERT(0);

//	m_d->OnBaseValChanged();
	if (m_pListener)
		m_pListener->OnChanged(this);
}

SVGPathSegListValue& SVGPathSegListValue::operator = (const SVGPathSegListValue& value)
{
	m_seglist->RemoveAll();
	m_seglist->AddSegListNoUpdate(value.m_seglist);
/*
	m_seglist->ParsePathData((BSTR)(_bstr_t)value);
	*/

	m_normalizedseglist->RemoveAll();
	m_normalizedseglist->NormalizePathSegList(m_seglist);

	return *this;
}

SVGPathSegListValue& SVGPathSegListValue::operator += (const SVGPathSegListValue& value)
{
	ASSERT(0);
	return *this;
}

void SVGPathSegListValue::setStringValue(StringIn str)
{
	m_seglist->RemoveAll();
	m_seglist->ParsePathData(str);

	m_normalizedseglist->RemoveAll();
	m_normalizedseglist->NormalizePathSegList(m_seglist);
}

String SVGPathSegListValue::getStringValue()
{
	return m_seglist->StringFromPathSegList();
}

void SVGPathSegListValue::InterpolateValue(SVGPathSegListValue* a, SVGPathSegListValue* b, double t)
{
	m_seglist->RemoveAll();
	m_seglist->InterpolateValue(a->m_seglist, b->m_seglist, t);

	m_normalizedseglist->RemoveAll();
	m_normalizedseglist->NormalizePathSegList(m_seglist);
}

SVGPathSegList* SVGPathSegListValue::get_pathSegList()
{
	return m_seglist;
}

SVGPathSegList* SVGPathSegListValue::get_normalizedPathSegList()
{
	return m_normalizedseglist;
}

}	// Web
}
