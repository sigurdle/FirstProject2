#pragma once

class ATL_NO_VTABLE CServer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ILXServer, &IID_ILXServer, &LIBID_LXWEBSITELib>
{
public:
	CComBSTR m_name;
	CComBSTR m_serverName;
	CComBSTR m_directory;
	CComBSTR m_userName;
	CComBSTR m_password;

	operator = (CServer& server)
	{
		m_name = server.m_name;
		m_serverName = server.m_serverName;
		m_directory = server.m_directory;
		m_userName = server.m_userName;
		m_password = server.m_password;
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServer)
	COM_INTERFACE_ENTRY(ILXServer)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_name.CopyTo(pVal);
	}
	STDMETHOD(get_serverName)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_serverName.CopyTo(pVal);
	}
	STDMETHOD(get_directory)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_directory.CopyTo(pVal);
	}
	STDMETHOD(get_userName)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_userName.CopyTo(pVal);
	}
	STDMETHOD(get_password)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_password.CopyTo(pVal);
	}
};
