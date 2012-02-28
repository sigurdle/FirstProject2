namespace System
{
namespace Style
{

class CSSEXT SelectorList : public Object
{
public:
	CTOR SelectorList();

	void ParseSelectorText();

	String get_selectorText();
	void set_selectorText(StringIn selectorText);

	size_t get_length() const
	{
		return m_items.GetSize();
	}

	Selector* item(size_t index)
	{
		if (index >= m_items.GetSize())
		{
			raise(ArgumentOutOfRangeException());
		}

		return m_items[index];
	}

	void deleteItem(size_t index)
	{
		VERIFY(0);
	}

	size_t appendItem(StringIn selectorText);

public:

	ICSSStyleRule* m_ownerRule;
	String m_selectorText;
	vector<Selector*> m_items;
	bool m_bCSSTextUpdated;
};

}	// Style
}	// System
