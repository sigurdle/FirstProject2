#if 0
class CXPathNSResolver :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILXPathNSResolver
{
public:

	CComQIPtr<ILDOMNode> m_nodeResolver;

BEGIN_COM_MAP(CXPathNSResolver)
	COM_INTERFACE_ENTRY(ILXPathNSResolver)
END_COM_MAP()

public:
	STDMETHOD(lookupNamespaceURI)(BSTR prefix, BSTR* pVal);
};
#endif
