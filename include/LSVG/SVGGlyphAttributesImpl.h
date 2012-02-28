#pragma once

namespace System
{
namespace Web
{

class SVGEXT SVGGlyphAttributesImpl : public ISVGGlyphAttributes
{
public:
	CTOR SVGGlyphAttributesImpl()
	{
		m_d = NULL;
		m_horiz_adv_x = NULL;
	}

	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGPathSegListValue> > > >* m_d;
	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<LongValue> > >* m_horiz_adv_x;

	SVGPathSegList* get_pathSegList()
	{
		return m_d->m_value->m_value->m_seglist;
	}

	SVGPathSegList* get_normalizedPathSegList()
	{
		return m_d->m_value->m_value->m_normalizedseglist;
	}
};

}	// w3c
}
