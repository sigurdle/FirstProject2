#ifndef Web_SVGAnimatedPathData_h
#define Web_SVGAnimatedPathData_h

namespace System
{
namespace Web
{

template<class T> class SVGAnimatedPathDataImpl :
	public ISVGAnimatedPathData
//	public SVGPathSegListListener
{
public:
	CTOR SVGAnimatedPathDataImpl()
	{
		m_d = NULL;

		NewXMLAttr(&m_d, NULL, WSTR("d"));
		static_cast<T*>(this)->AddXMLAttribute(m_d);
	}

	void FinalRelease()
	{
	//	m_d->m_animated->m_baseVal->m_value->m_seglist->m_pListener = NULL;
	//	m_d->m_animated->m_baseVal->m_value->m_normalizedseglist->m_pListener = NULL;
	}

	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<SVGPathSegListValue> > > >, CValueTypeWrapper<CreateInstanceT<SVGPathSegListValue> > >* m_d;

	/*
	virtual void OnPathSegListChange(SVGPathSegList* pSegList)
	{
		if (pSegList == m_d->m_animated->m_baseVal->m_value->m_seglist)
		{
			// Normalize
			m_d->m_animated->m_baseVal->m_value->m_normalizedseglist->RemoveAll();
			m_d->m_animated->m_baseVal->m_value->m_normalizedseglist->NormalizePathSegList(m_d->m_animated->m_baseVal->m_value->m_seglist);
		}
		else if (pSegList == m_d->m_animated->m_baseVal->m_value->m_normalizedseglist)
		{
		// Copy the normalized seglist to the the seglist
			m_d->m_animated->m_baseVal->m_value->m_seglist->RemoveAll();
			m_d->m_animated->m_baseVal->m_value->m_seglist->AddSegListNoUpdate(m_d->m_animated->m_baseVal->m_value->m_normalizedseglist);
		}
		else
			ATLASSERT(0);

		m_d->OnBaseValChanged();
	}
	*/

//
	SVGPathSegList* get_pathSegList()
	{
		return m_d->m_animated->m_baseVal->m_value->m_seglist;
	}

	SVGPathSegList* get_normalizedPathSegList()
	{
		return m_d->m_animated->m_baseVal->m_value->m_normalizedseglist;
	}

	SVGPathSegList* get_animatedPathSegList()
	{
		return m_d->m_animated->m_animVal->m_value->m_seglist;
	}

	SVGPathSegList* get_animatedNormalizedPathSegList()
	{
		return m_d->m_animated->m_animVal->m_value->m_normalizedseglist;
	}
};

}	// w3c
}

#endif // Web_SVGAnimatedPathData_h
