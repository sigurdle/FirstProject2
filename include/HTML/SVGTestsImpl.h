#ifndef __SVGTESTSIMPL_H__
#define __SVGTESTSIMPL_H__

#include "SVGStringList.h"

namespace System
{
namespace Web
{

template <class T> class SVGTestsImpl :
	public ISVGTests
{
public:
	CTOR SVGTestsImpl()
	{
		m_systemLanguage = NULL;
		m_requiredExtensions = NULL;
		m_requiredFeatures = NULL;

		/*
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_systemLanguage, NULL, WSTR("systemLanguage")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_requiredExtensions, NULL, WSTR("requiredExtensions")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_requiredFeatures, NULL, WSTR("requiredFeatures")));
		*/
	}

	SVGStringList* m_systemLanguage;
	SVGStringList* m_requiredExtensions;
	SVGStringList* m_requiredFeatures;

	/*
	CXMLAttr2T<CreateInstanceT<w3c::CValueTypeWrapper<CreateInstanceT<SVGStringListCommaSeparated> > > >* m_systemLanguage;
	CXMLAttr2T<CreateInstanceT<w3c::CValueTypeWrapper<CreateInstanceT<SVGStringListSpaceSeparated> > > >* m_requiredExtensions;
	CXMLAttr2T<CreateInstanceT<w3c::CValueTypeWrapper<CreateInstanceT<SVGStringListSpaceSeparated> > > >* m_requiredFeatures;
	*/
//	CComObject<CXMLAttr2T<CComObjectCreateInstance<CLSVGStringList> > >* m_systemLanguage;

	SVGStringList* get_requiredFeatures()
	{
		return m_requiredFeatures;
	}

	SVGStringList* get_requiredExtensions()
	{
		return m_requiredExtensions;
	}

	SVGStringList* get_systemLanguage()
	{
		return m_systemLanguage;
	}

// Returns true if the user agent supports the given extension, specified by a URI
	bool hasExtension(StringIn extension)
	{
		// I don't support any extensions yet
		return false;
	}

	long get_systemBitrate()
	{
		String str = static_cast<T*>(this)->getAttribute(WSTR("systemBitrate"));
		if (str)
		{
			ASSERT(0);
			return 0;
			//return str2int(str->c_str());
		}
		else
			return 0;	// This will make this element available for any user set connection speed >= 0
	}
	void set_systemBitrate(long newVal)
	{
		THROW(-1);
	}

	bool get_systemCaptions()
	{
		String str = static_cast<T*>(this)->getAttribute(WSTR("systemCaptions"));

		if (str == L"on")
			return true;
		else
			return false;
	}

	void set_systemCaptions(bool newVal)
	{
		THROW(-1);
	}

	bool get_systemAudioDesc()
	{
		String str = static_cast<T*>(this)->getAttribute(WSTR("systemAudioDesc"));

		if (str == L"on")
			return true;
		else
			return false;
	}
	void set_systemAudioDesc(bool newVal)
	{
		THROW(-1);
	}

	String get_systemOverdubOrSubtitle()
	{
		return static_cast<T*>(this)->getAttribute(WSTR("systemOverdubOrSubtitle"));
	}
	void set_systemOverdubOrSubtitle(String newVal)
	{
		static_cast<T*>(this)->setAttribute(WSTR("systemOverdubOrSubtitle"), newVal);
	}
};

}	// Web
}

#endif // __SVGTESTSIMPL_H__
