#ifndef __LSVGMISSINGGLYPHELEMENT_H_
#define __LSVGMISSINGGLYPHELEMENT_H_

//#include "resource.h"       // main symbols

#include "SVGGlyphAttributesImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGMissingGlyphElement : 
	public SVGElement,
	public SVGStylableImpl<SVGMissingGlyphElement>,
//	public ElementEditASImpl<SVGMissingGlyphElement>,
	public ElementEditVALImpl<SVGMissingGlyphElement>,
	public SMILAnimationTargetImpl<SVGMissingGlyphElement>,
	public SVGGlyphAttributesImpl,

	public CNotifyGetImpl<SVGMissingGlyphElement>,
	public CNotifySendImpl<SVGMissingGlyphElement>,
	public ISVGPathSegListListener
{
public:
	CTOR SVGMissingGlyphElement() : SVGElement(new PSVGElement(this))
	{
		NewNXMLAttr(&m_d, NULL, WSTR("d"));
		AddXMLAttribute(m_d);

		m_d->m_value->m_value->m_seglist->m_pListener = this;
		m_d->m_value->m_value->m_normalizedseglist->m_pListener = this;

		AddXMLAttribute(NewXMLAttr(&m_horiz_adv_x, NULL, WSTR("horiz-adv-x")));
	}

	~SVGMissingGlyphElement()
	{
		m_d->m_value->m_value->m_seglist->m_pListener = NULL;
		m_d->m_value->m_value->m_normalizedseglist->m_pListener = NULL;
	}

	virtual void OnPathSegListChange(SVGPathSegList* pSegList)
	{
		if (pSegList == m_d->m_value->m_value->m_seglist)
		{
			m_d->OnBaseValChanged();
		}
		else if (pSegList == m_d->m_value->m_value->m_normalizedseglist)
		{
		// Copy the normalized seglist to the the seglist
			m_d->m_value->m_value->m_seglist->RemoveAll();
			m_d->m_value->m_value->m_seglist->AddSegListNoUpdate(m_d->m_value->m_value->m_normalizedseglist);

			m_d->OnBaseValChanged();
		}
	}

// EventTarget
	virtual ErrorCode dispatchEvent2(Event * evt, /*[in]*/ bool bCapture, /*[out,retval]*/ bool * doDefault);


};

}	// LSVG
}

#endif //__LSVGMISSINGGLYPHELEMENT_H_
