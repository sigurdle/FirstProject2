#ifndef __HttpHeaders_h__
#define __HttpHeaders_h__

namespace System
{
namespace Net
{

class NETEXT HttpHeaders //: public System::Object
{
public:

	void AddHeader(StringIn header, StringIn value);
	void AddHeaders(StringIn lines);
	String GetHeaderValue(StringIn name, int index = 0) const;

	String GetAllHeaders()
	{
		return m_all;
	}

	String m_all;

protected:

	typedef multimap<String, String> tyheadermap;
	tyheadermap m_headerlines;
};

}
}

#endif // __HttpHeaders_h__
