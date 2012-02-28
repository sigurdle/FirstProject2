#ifndef PDF_PDFObject_h
#define PDF_PDFObject_h

namespace System
{

class CPDFObject : public System::Object
{
public:

	class CTag
	{
	public:
		uint32 m_tag;
		uint32 m_data;
	};

	vector<CTag> m_tags;

public:
	void AddTag(uint32 tag, uint32 data)
	{
		CTag t;
		t.m_tag = tag;
		t.m_data = data;
		m_tags.Add(t);
	}

	uint32 GetTag(uint32 tag)
	{
		for (unsigned int i = 0; i < m_tags.size(); i++)
		{
			if (m_tags[i].m_tag == tag)
			{
				return m_tags[i].m_data;
			}
		}

		return 0;
	}

	void RemoveTag(uint32 tag)
	{
		for (int i = 0; i < m_tags.GetSize(); i++)
		{
			if (m_tags[i].m_tag == tag)
			{
				m_tags.RemoveAt(i);
				break;
			}
		}
	}
};

}

#endif // PDF_PDFObject_h
