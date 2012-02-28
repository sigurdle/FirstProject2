#ifndef Web_SVGStringList_h
#define Web_SVGStringList_h

namespace System
{
namespace Web
{

/*
class CLSVGStringListListener
{
public:
	virtual void OnNumberListChange(CLSVGStringList* pSegList) = 0;
};
*/

class HTMLEXT SVGStringList : 
	public CSingleObject,
	public ISVGStringList
{
public:
	CTOR SVGStringList();
	~SVGStringList();

//	void FinalRelease();

	void RemoveAll();

	void CopyFrom(SVGStringList* value);
	void Add(SVGStringList* value);
	void InterpolateValue(SVGStringList* a, SVGStringList* b, double t);

	unsigned int get_numberOfItems() const;
	void clear();
	String appendItem(StringIn newItem);
	String removeItem(unsigned int index);
	String replaceItem(StringIn newItem, unsigned int index);
	String insertItemBefore(StringIn newItem, unsigned int index);
	String getItem(unsigned int index);
	String initialize(StringIn newItem);

public:

//	CLSVGStringListListener* m_pListener;

//	int m_bLockUpdate;
//	int m_nChanges;

//	CArray<CAdapt<CComBSTR>, CAdapt<CComBSTR> > m_items;
	vector<String> m_items;
};

class HTMLEXT SVGStringListCommaSeparated :
	public SVGStringList
{
public:
	String getStringValue();
	void setStringValue(StringIn str);

	void operator = (SVGStringListCommaSeparated* value)
	{
		SVGStringList::CopyFrom(value);
	}
	void operator += (SVGStringListCommaSeparated* value)
	{
		SVGStringList::Add(value);
	}
	void InterpolateValue(SVGStringListCommaSeparated* a, SVGStringListCommaSeparated* b, double t)
	{
		ASSERT(0);
	}
};

class HTMLEXT SVGStringListSemicolonSeparated :
	public SVGStringList
{
public:
	String getStringValue();
	void setStringValue(StringIn str);

	void operator = (SVGStringListSemicolonSeparated* value)
	{
		SVGStringList::CopyFrom(value);
	}
	void operator += (SVGStringListSemicolonSeparated* value)
	{
		SVGStringList::Add(value);
	}
	void InterpolateValue(SVGStringListSemicolonSeparated* a, SVGStringListSemicolonSeparated* b, double t)
	{
		ASSERT(0);
	}
};

class HTMLEXT SVGStringListSpaceSeparated :
	public SVGStringList
{
public:
	String getStringValue();
	void setStringValue(StringIn str);

	void operator = (SVGStringListSpaceSeparated* value)
	{
		SVGStringList::CopyFrom(value);
	}
	void operator += (SVGStringListSpaceSeparated* value)
	{
		SVGStringList::Add(value);
	}
	void InterpolateValue(SVGStringListSpaceSeparated* a, SVGStringListSpaceSeparated* b, double t)
	{
		ASSERT(0);
	}
};

}	// Web
}

#endif // Web_SVGStringList_h
