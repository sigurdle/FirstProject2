#ifndef __LFilterCollection_h
#define __LFilterCollection_h

namespace System
{
namespace MediaShow
{

class CDispLCollection : public Object
{
public:
	CTOR CDispLCollection()
	{
	}

	~CDispLCollection()
	{
		RemoveAll();
	}

	void RemoveAll()
	{
		/*
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			IRefCounted* pref = dynamic_cast<IRefCounted*>(m_items[i]);
			if (pref) pref->Release();
		}
		*/
		m_items.RemoveAll();
	}

	unsigned int get_Count();
	IBaseFilter* Item(unsigned int index);

	vector<IBaseFilter*> m_items;
};

}	// LMediaShow
}

#endif // __LFilterCollection_h
