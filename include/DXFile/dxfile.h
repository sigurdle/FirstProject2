#ifndef __dxfile_h__
#define __dxfile_h__

#ifndef DXFILEXT
#define DXFILEXT DECLSPEC_DLLIMPORT
#endif

/*
//#include "Object3D.h"

#include "LFC/LFC.h"
#include "Graphics/Graphics.h"
#include "GUI/GUI.h"
*/

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "Graphics/Graphics.h"
#else
#include "Graphics/Graphics.h"
#endif

#ifdef __LERSTAD__
#import "GUI/GUI.h"
#else
#include "GUI/GUI.h"
#endif

namespace System
{

interface Interface
{
protected:
	virtual ~Interface()
	{
	}
};

namespace DX
{
class Instance;
class Template;
class Member;
class Dimension;

class DataType
{
public:

	CTOR DataType() : m_sizeof(0)
	{
	}

	enum
	{
		vector,
		Primitive,
		Name,
	}
	type;

	uint m_sizeof;

	union
	{
		int primitive;
		struct
		{
			System::StringA* name;
			Template* pResolved;
		}
		template_name;

		struct
		{
			DataType* type;
			Dimension* dim;
		}
		array_;
	};
};

class Member
{
public:
	CTOR Member();

	DataType* m_dataType;
	String m_name;
	uint m_offset;
};

/*
Member* Member_Array(DataType* datatype)
{
	return NULL;
}
*/

class Template : public Object
{
public:
	CTOR Template()
	{
		m_name = nullptr;
	}

	String GetName();

	String m_name;
	vector<Member*> m_members;
	map<String, Member*> m_membersByName;

	uint m_sizeof;
};

class DXFILEXT xfileparser : public Object
{
public:
	int ParseX(IO::Stream* stream);

	void AddTemplate(Template* pTemplate);

	map<String, Template*> m_templates;
	vector<Member*> m_members;

	vector<Instance*> m_objects;
};

}	// DX

namespace Gui
{
namespace Media3D
{
DXFILEXT void convert(Document3D* document, const vector<DX::Instance*>& objects, Group* children);
}
}

}	// System

#endif // __dxfile_h__
