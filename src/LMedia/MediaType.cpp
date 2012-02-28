#include "stdafx.h"
#include "LMediaImpl.h"

namespace System
{
namespace MediaShow
{

MediaType::MediaType()
{
	m_majortype = GUID_NULL;
	m_subtype = GUID_NULL;
	m_formattype = GUID_NULL;
	m_pbFormat = NULL;
}

MediaType::MediaType(GUID majortype, GUID subtype, GUID formattype, MediaTypeFormat *pbFormat)
{
	m_majortype = majortype;
	m_subtype = subtype;
	m_formattype = formattype;
	m_pbFormat = pbFormat;
}

#if 0
MediaType::MediaType()
{
	m_p = NULL;
}

MediaType::MediaType(const MediaType& other)
{
	m_p = other.m_p;
	if (m_p)
	{
		m_p->AddRef();
	}
}

MediaType::MediaType(_MediaType* p)
{
	m_p = p;
	if (m_p)
	{
		m_p->AddRef();
	}
}

MediaType::~MediaType()
{
	/*
	if (bManaged)
		Delete();
		*/
//	delete pbFormat;
	if (m_p)
	{
		m_p->Release();
	}
}

MediaType& MediaType::operator = (const MediaType& other)
{
	_MediaType* old = m_p;
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
	if (old) old->Release();

	return *this;
	/*
	if (pbFormat)
		delete pbFormat;

	majortype = other.majortype;
	subtype = other.subtype;
	formattype = other.formattype;
	cbFormat = other.cbFormat;
	if (other.pbFormat)
	{
		pbFormat = new uint8[cbFormat];
		memcpy(pbFormat, other.pbFormat, cbFormat);
	}
	else
		pbFormat = NULL;

	return *this;
	*/
}

void MediaType::SetFormat(MediaTypeFormat* pFormat)
{
	//ASSERT(m_pmt);

	if (m_p->m_refcount > 1)
	{
		_MediaType* old = m_p;

		m_p = new _MediaType;
		m_p->AddRef();

		m_p->majortype = old->majortype;
		m_p->subtype = old->subtype;
		m_p->formattype = old->formattype;
		if (old->pbFormat)
		{
			m_p->pbFormat = old->pbFormat->Clone();
		}

		old->Release();
	}

	m_p->pbFormat = pFormat;
	m_p->pbFormat->AddRef();
}

void MediaType::Create(ULONG formatSize/* = 0*/, const void* formatBuffer/* = NULL*/)
{
	ASSERT(0);
	/*
	if (formatSize)
	{
		cbFormat = formatSize;
		pbFormat = new uint8[formatSize];
		if (formatBuffer)
		{
			memcpy(pbFormat, formatBuffer, formatSize);
		}
	}
	*/
}
#endif

ULONG CLEnumMediaTypes::Next(ULONG celt, MediaType **rgelt)
{
	uint n;
	for (n = 0; n < celt; ++n)
	{
		if (m_pos == m_list.GetData() + m_list.GetSize()) break;

		MediaType* pmt = *m_pos++;//(LMediaType*)m_list.GetNext(m_pos);
	//	ASSERT(pmt);
		*rgelt++ = pmt;//LCreateMediaType(pmt);
		/*
		if (*rgelt == NULL)
		{
			break;
		}
		*/
		rgelt++;
	}

	return n;
}

}	// MediaShow
}
