#ifndef __DTDNAMEDOBJECTMAP_H_
#define __DTDNAMEDOBJECTMAP_H_

namespace System
{
namespace Web
{

class WEBEXT CDTDASNamedObjectMap : public IASNamedObjectMap
{
public:
	/*
	void FinalRelease()
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			m_items[i]->Release();
		}
	}
	*/

	vector<IASObject*> m_items;

	size_t get_length() const
	{
		return m_items.GetSize();
	}

	IASObject* getNamedItem(StringIn name)
	{
		for (unsigned int i = 0; i < m_items.GetSize(); i++)
		{
			String nodename = m_items[i]->get_nodeName();

			if (name == nodename)
			{
				return m_items[i];
			}
		}

		return NULL;
	}

	IASObject* getNamedItemNS(StringIn namespaceURI, StringIn localName)
	{
		ASSERT(0);
#if 0
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			BSTR nodename;
			m_items[i]->get_localName(&nodename);

			if (!wcscmp(name, nodename))
			{
				*pVal = m_items[i];
				(*pVal)->AddRef();
				return S_OK;
			}
		}
#endif

		return NULL;
	}

	IASObject* item(size_t index)
	{
		if (/*index >= 0 && */ index < m_items.GetSize())
		{
			return m_items[index];
		}
		else
			return NULL;
	}

	IASObject* setNamedItem(IASObject* newASObject)
	{
		m_items.Add(newASObject);

		return newASObject;
	}

	IASObject* setNamedItemNS(IASObject* newASObject)
	{
	// Same as above (?)
		m_items.Add(newASObject);

		return newASObject;
	}
};

}	// Web
}

#endif	// __DTDNAMEDOBJECTMAP_H_
