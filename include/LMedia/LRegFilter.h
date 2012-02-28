#ifndef __RegFilter_h_
#define __RegFilter_h_

namespace System
{
namespace MediaShow
{

class FilterGraph;

class CLRegPin
{
public:
	PIN_DIRECTION m_dir;
	bool m_bZero;
	bool m_bMany;
	String m_name;
	vector<CLRegMediaType*> m_mediaTypes;
};

class CDispLRegFilter : public System::Object
{
public:
	CTOR CDispLRegFilter();

	String get_Name() const;

	ErrorCode BuildRegFilter(XmlData::Element* element);

public:

	String m_Name;
//	CLSID m_clsid;
	String m_Src;

	vector<CLRegPin*> m_RegPins;
};

}	// MediaShow
}

#endif // __RegFilter_h_
