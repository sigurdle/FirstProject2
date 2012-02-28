#ifndef Web_HTMLTableElement_h
#define Web_HTMLTableElement_h

namespace System
{
namespace Web
{

class HTMLTableElement : 
	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLTableElement>,
//	public CLElementEditASImpl<HTMLTableElement>,
	public ElementEditVALImpl<HTMLTableElement>,
	public SMILAnimationTargetImpl<HTMLTableElement>,

	protected CNotifyGetImpl<HTMLTableElement>,
	protected CNotifySendImpl<HTMLTableElement>
{
public:
	CTOR HTMLTableElement(NamedNodeMap* attributes);
	~HTMLTableElement();

	long get_cellSpacing();
	void set_cellSpacing(long newVal);
	long get_cellPadding();
	void set_cellPadding(long newVal);
	long get_border();
	void set_border(long newVal);

	Attr* get_cellSpacingAttr()
	{
		return m_cellSpacingAttr;
	}

	Attr* get_cellPaddingAttr()
	{
		return m_cellPaddingAttr;
	}

	Attr* get_borderAttr()
	{
		return m_borderAttr;
	}

public:

	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<LongValue> > > >, CValueTypeWrapper<CreateInstanceT<LongValue> > >* m_pcellspacing;

protected:

	Attr* m_cellSpacingAttr;
	Attr* m_cellPaddingAttr;
	Attr* m_borderAttr;
};

}	// Web
}

#endif // Web_HTMLTableElement_h
