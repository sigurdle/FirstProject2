
#ifdef __LERSTAD__
#import "../../Win32/bin/Debug/LXUI.typeinfo"
#else
#include "../LXUI/LXUI.h"
#endif

class ServerTestClass : public System::Object
{
public:
	CTOR ServerTestClass()
	{
		m_str = NULL;
		m_value = 0;
	}

	System::StringW* m_str;
	int m_value;
};
