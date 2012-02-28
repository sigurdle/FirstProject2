#ifndef __Web_StyleSheetList_h__
#define __Web_StyleSheetList_h__

namespace System
{
namespace Web
{

class WEBEXT StyleSheetList :
	public Object,
	public Style::IStyleSheetList
//	protected CNotifyGetImpl<StyleSheetList>,
//	protected CNotifySendImpl<StyleSheetList>
{
public:
	CTOR StyleSheetList();
	~StyleSheetList();

#if 0
	void FinalRelease()
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			INotifySend* cp = dynamic_cast<INotifySend*>(m_items[i]);
//			cp->Unadvise(this);

		//	int refcount = m_items[i]->Release();
		}
		m_items.RemoveAll();
	}
#endif

	void append(Style::IStyleSheet* stylesheet);
	Style::IStyleSheet* item(size_t index) override;
	size_t get_length() override;

	vector<Style::IStyleSheet*> m_items;

// IHTMLStyleSheetsCollection
/*
	STDMETHOD(get_length)(LONG * p)
	{
		if (p == NULL) return E_POINTER;
		*p = m_items.GetSize();
		return S_OK;
	}
	STDMETHOD(get__newEnum)(IUnknown * * p)
	{
		if (p == NULL)
			return E_POINTER;

		return E_NOTIMPL;
	}
	STDMETHOD(item)(VARIANT * pvarIndex, VARIANT * pvarResult)
	{
		if (pvarResult == NULL) return E_POINTER;

		//if (pvarIndex.vt == VT_LONG)
		//{
		//	return item(pvarIndex
		return E_NOTIMPL;
	}
*/
};

}	// Web
}

#endif // __Web_StyleSheetList_h__
