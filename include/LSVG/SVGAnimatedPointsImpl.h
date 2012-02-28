
#if 0
#ifndef __SVGAnimatedPointsImpl_h__
#define __SVGAnimatedPointsImpl_h__

namespace System
{
namespace Web
{

template <class T> class SVGAnimatedPointsImpl :
//	public ILSVGAnimatedPoints,
	public ISingleObjectListener
{
public:
	CTOR SVGAnimatedPointsImpl()
	{
		m_points = NULL;
		m_animatedPoints = NULL;

//		m_pAttr = NULL;

		/*
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_points, NULL, WSTR("points")));

		m_points->m_animated->m_baseVal->m_value->m_pListener = this;
		*/
	}

	~SVGAnimatedPointsImpl()
	{
		//m_points->m_animated->m_baseVal->m_value->m_pListener = NULL;
	}

	/*
	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
	}
	*/

	virtual void OnChanged(CSingleObject* pPointList)
	{
		ASSERT(0);
	//	m_points->m_animated->m_pAttr->OnBaseValChanged();
		//m_pAttr->OnBaseValChanged();
	}

//	CATXMLAttr* m_pAttr;

//	CValueTypeWrapper<CreateInstance<SVGPointList> > >* m_baseVal;
//	CValueTypeWrapper<CreateInstance<SVGPointList> > >* m_animVal;

//	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<SVGPointList> > > >, CValueTypeWrapper<CreateInstanceT<SVGPointList> > >* m_points;

	SVGPointListMutable* m_points;
	SVGPointList* m_animatedPoints;

	ISVGPointList* get_points()
	{
		return m_points;
		//return m_points->m_animated->m_baseVal->m_value;
	}

	ISVGPointList* get_animatedPoints()
	{
		return m_animatedPoints;
		//return m_points->m_animated->m_animVal->m_value;
	}
};

}	// w3c
}

#endif // __SVGAnimatedPointsImpl_h__

#endif
