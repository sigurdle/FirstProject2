#ifndef Web_SMILTimeList_h
#define Web_SMILTimeList_h

namespace System
{
namespace Web
{

class WEBEXT SMILTimeList : 
	public CSingleObject,
	public ISVGList,
	protected ISingleObjectListener
{
public:
	CTOR SMILTimeList()
	{
		m_ownerElement = NULL;
	}

	~SMILTimeList();

//	void FinalRelease();

	void RemoveAll();

//	void Sort();
	bool parseString(StringIn str);

//	SMILTimeList& operator = (const SMILTimeList& value);
//	SMILTimeList& operator += (const SMILTimeList& value);

	String getStringValue();
	void setStringValue(StringIn str);
	void InterpolateValue(SMILTimeList* a, SMILTimeList* b, double t);

	unsigned int get_length() const;
	SMILTime* item(unsigned int index) const;

// Extensions
	void clear();
	unsigned int get_numberOfItems() const;
	SMILTime* initialize(SMILTime* newItem);
	SMILTime* insertItemBefore(SMILTime* newItem, unsigned int index);
	SMILTime* replaceItem(SMILTime* newItem, unsigned int index);
	SMILTime* removeItem(unsigned int index);
	SMILTime* appendItem(SMILTime* newItem);

protected:

	virtual void OnChanged(CSingleObject* pObject)
	{
		if (m_pListener)
			m_pListener->OnChanged(this);
	}

public:

	Element* m_ownerElement;

	vector<SMILTime*> m_items;
};

}	// Web
}

#endif // Web_SMILTimeList_h
