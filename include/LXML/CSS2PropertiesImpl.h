#ifndef __CSS2PROPERTIESIMPL_H__
#define __CSS2PROPERTIESIMPL_H__

namespace System
{
namespace Web
{

template<class T> class CLCSS2PropertiesImpl :
	public ICSS2Properties
{
public:
#if 0	// TODO
	sysstring get_azimuth)(/*[out, retval]*/ BSTR *pVal)
	{
		return static_cast<T*>(this)->getPropertyValue(OLESTR("azimuth"));
	}

	STDMETHOD(set_azimuth)(/*[in]*/ BSTR newVal)
	{
		return static_cast<T*>(this)->setProperty(OLESTR("azimuth"), newVal, NULL);
	}

	STDMETHOD(get_background)(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHOD(set_background)(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHOD(get_backgroundAttachment)(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHOD(set_backgroundAttachment)(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHOD(get_backgroundColor)(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHOD(set_backgroundColor)(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHOD(get_backgroundImage)(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHOD(set_backgroundImage)(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}

	STDMETHOD(get_backgroundPosition)(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}

	STDMETHOD(set_backgroundPosition)(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}
#endif
};

}
}

#endif // __CSS2PROPERTIESIMPL_H__
