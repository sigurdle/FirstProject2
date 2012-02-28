#include "lfc/lfc.h"
#include "lfc/xmldata.h"
#include "lxui/lxui.h"
#include "Browser/Browser.h"
#include "lmedia/lmedia.h"
#include "lx3d/lx3d.h"
#include "lmpegvideo/VideoSequence.h"
#include "lmpegvideo/Picture.h"
#include "lmpegvideo/LMPEGVideoDecoder.h"

#include "LXImageEditor/LXImageEditor.h"
//#include "LXImageEditor/ImageApp.h"
//#include "LXImageEditor/ImageView.h"
//#include "LXImageEditor/ImageDocument.h"
//#include "LXImageEditor/ImageLayerBitmap.h"
#include "LDebugger/TTDebuggerFrame.h"
#include "LDebugger/mainfrm.h"
#include "LDebugger/DisassemblyWnd.h"
#include "LDebugger/CallStackWnd.h"
#include "LDebugger/WatchWnd.h"
#include "LDebugger/SourceEditFrame.h"

#include "LXMLEditor/LXMLEditor.h"
#include "LXMLEditor/Transition.h"
#include "LXMLEditor/LXMLEditorApp.h"

#include "LXML/LXML.h"
#include "LXML/HTMContext.h"
#include "LHTML/LHTML.h"
#include "LSVG/LSVG.h"

#include "LJPEG/JFIF.h"
#include "PNG/PNGFormat.h"
#include "TIFF/TIFF.h"

#if 0
template<class T, class A = int> class list// : public list_base
{
public:

	typedef T value_type;

	class list_node //: public list_node_base
	{
	public:
		/*
		CTOR list_node(const value_type & value) : m_value(value)
		{
		}
		*/

		value_type m_value;
	};

	< list(const list<T>& other)
	{
	}

};

class test
{
	list<int> k;

	list<int> j;
};
#endif

/*
template<class T3, class T5> class pair
{
};

template<class T3> class nclass
{
	template<class u, class v>
	< pair(const pair<u,v> & other) : first(other.first), second(other.second)
	{
	}

};
*/

/*
class k
{
	typedef int typ;

	void fun(typ param);
};

void k::fun(typ param)
{
}
*/

#if 0
template<class T> class base
{
//	T x;

	class inner_0
	{
		T y;
	};

	class inner_1 : public inner_0
	{
	};

	inner_0 x;
};

template<class T2> class derived : public base<T2>
{
	T2 y;
};

class test
{
	derived<int> y;
};
#endif

#if 0
template<class T3> class mclass
{
	T3 z;
};

template<class T1, class T2> class kclass
{
	T1 y;
	mclass<nclass<T2> > x;
};

template<class T> class Array
{
public:

	class inner
	{
		T x;
	};


	/*
	template<class Y, class T2 = T> class Sub
	{
		T2 a;
		Y b;
	};
	*/

/*
	template<class Y = T> double get(const T* x)
	{
	}
*/

//	inner m_elem2;

//	kclass<double, T> y;

//	T x;
};

/*
class test
{
	Array<int> m_arr;
};
*/

class test2
{
//	Array<int> m_a;
//	Array<int>::Sub<double> m_b;
	Array<int>::inner m_c;
};
#endif