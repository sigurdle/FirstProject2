#ifndef __Browser_h__
#define __Browser_h__

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LX3D.typeinfo"
#else
#include "../LX3D/X3D.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/UIMedia.typeinfo"
#else
#include "../UIMedia/UIMedia.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LXML.typeinfo"
#else
#include "../LXML/LXML.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/HTML.typeinfo"
#else
#include "../HTML/HTML.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LSVG.typeinfo"
#else
#include "../LSVG/LSVG.h"
#endif

/*
#if WIN32
	#ifdef __LERSTAD__
//		#import "../../Win32/bin/Debug/LX3D.typeinfo"
	#else
		#include "../LX3D/LX3D.h"
	#endif
#endif
*/

namespace System
{

// TODO, not here
class TextRun
{
public:
	uint16 charIndex;
	uint16 fontIndex;
};

class IViewOf
{
public:
	//virtual const type_info& GetType() = 0;
	virtual System::Object* get_Viewable() = 0;
	virtual void set_Viewable(System::Object* pViewable) = 0;
};

class TwoViews
{
public:
	CTOR TwoViews()
	{
		smallView = NULL;
		largerView = NULL;
	}
//	IViewOf* smallView;
//	IViewOf* largerView;
	UI::FrameworkElement* smallView;
	UI::FrameworkElement* largerView;
};

TwoViews CreateView(System::Property* pProperty, /*cpp::Type* pReturnType,*/ System::Object* obj, UI::TreeControl* tree);

class IComparable
{
public:
	virtual bool operator < (const IComparable* other) const = 0;
//	virtual bool operator == (const IComparable* other) const = 0;
};

class Comparable
{
public:
	CTOR Comparable(IComparable* p)
	{
		m_p = p;
	}

	IComparable* m_p;

	bool operator < (const Comparable& other) const
	{
		return *m_p < other.m_p;
	}
	/*
	bool operator == (const Comparable& other) const
	{
		return *m_p == other.m_p;
	}
	*/
};

class LongLongObject : public IComparable
{
public:
	CTOR LongLongObject(LONGLONG value)
	{
		m_value = value;
	}

	LONGLONG m_value;

	bool operator < (const IComparable* other) const
	{
		return m_value < static_cast<const LongLongObject*>(other)->m_value;
	}
/*
	bool operator == (const IComparable* other) const
	{
		return m_value == static_cast<const LongLongObject*>(other)->m_value;
	}
	*/
};

//
//  File System time stamps are represented with the following structure:
//

struct WIN_FILETIME
{
	uint32 dwLowDateTime;
	uint32 dwHighDateTime;
};

class FileTimeObject : public IComparable
{
public:
	CTOR FileTimeObject(const WIN_FILETIME* value);

	WIN_FILETIME m_value;

	bool operator < (const IComparable* other) const;

	/*
	bool operator == (const IComparable* other) const
	{
		return CompareFileTime(&m_value, &static_cast<const FileTimeObject*>(other)->m_value) == 0;
	}
	*/
};

namespace UI
{
class DeltaMoveButton : public Control
{
public:
	CTOR DeltaMoveButton();
	
protected:
//	virtual void handleEvent(System::Event* evt);

private:
	int m_dragging;
	LDraw::PointI m_oldpt;
};

/*
class DeltaChangeEvent : public System::Event
{
public:
	double deltaX;
	double deltaY;
};
*/

}	// UI

void GetDerived(System::ClassType* pType, vector<System::ClassType*>& arr);

}

#include "BrowserFrame.h"
#include "Histogram.h"
#include "View.h"
#include "ViewOfCollection.h"
#include "PropertiesTable.h"
#include "PropertiesWindow.h"
#include "Properties.h"
#include "WaveformElement.h"
#include "MusicModule.h"
#include "X3DViewer.h"
#include "View3D.h"
#include "Object3D.h"
#include "ColorPickerRGB.h"
#include "ListView.h"

#include "IBSPFile.h"
#include "BSPViewer.h"

#endif // __Browser_h__
