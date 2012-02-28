#ifndef w3c_SVGExternalResourcesRequired_h
#define w3c_SVGExternalResourcesRequired_h

namespace System
{
namespace Web
{

template<class T> class SVGExternalResourcesRequiredImpl :
	public ISVGExternalResourcesRequired
{
public:
	class SVGEXT SVGNonAnimatedBoolean : 
		public ISVGAnimatedBoolean
	{
	public:
		CTOR SVGNonAnimatedBoolean()
		{
		}

		bool get_animVal()
		{
			return get_baseVal();
		}
		bool get_baseVal()
		{
			ASSERT(0);
			return false;
		}
		void set_baseVal(bool newVal)
		{
			ASSERT(0);
		}
	};

	CTOR SVGExternalResourcesRequiredImpl()
	{
		m_externalResourcesRequired = NULL;
	}

	~SVGExternalResourcesRequiredImpl()
	{
		ASSERT(m_externalResourcesRequired == NULL);
	}

	ISVGAnimatedBoolean* get_externalResourcesRequired()
	{
		if (m_externalResourcesRequired == NULL)
		{
			m_externalResourcesRequired = new SVGNonAnimatedBoolean;
		}

		return m_externalResourcesRequired;
	}

	SVGNonAnimatedBoolean* m_externalResourcesRequired;
};

}	// Web
}

#endif // w3c_SVGExternalResourcesRequired_h
