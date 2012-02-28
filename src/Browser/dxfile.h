#ifndef __dxfile_h__
#define __dxfile_h__

#include "Object3D.h"

namespace System
{
namespace DX
{
class Instance;
class Template;
class Member;
class Dimension;

class DataType
{
public:

	DataType()
	{
		m_sizeof = 0;
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
		array;
	};
};

class Member
{
public:
	Member();

	DataType* m_dataType;
	System::StringA* m_name;
	uint m_offset;
};

/*
Member* Member_Array(DataType* datatype)
{
	return NULL;
}
*/

class Template
{
public:
	Template()
	{
		m_name = NULL;
	}

	System::StringA* GetName();

	System::StringA* m_name;
	vector<Member*> m_members;
	map<System::StringA*, Member*, Ref_Less<System::StringA> > m_membersByName;

	uint m_sizeof;
};

class xfileparser
{
public:
	map<System::StringA*, Template*, Ref_Less<System::StringA> > m_templates;
	vector<Member*> m_members;

	vector<Instance*> m_objects;

	int ParseX(System::IO::ISequentialByteStream* stream);

	void AddTemplate(Template* pTemplate);

};
}	// DX

namespace UI
{
namespace Media3D
{

void convert(Document3D* document, const vector<DX::Instance*>& objects, UI::Media3D::Object3DCollection* children);

}
}

}	// System

#endif // __dxfile_h__
