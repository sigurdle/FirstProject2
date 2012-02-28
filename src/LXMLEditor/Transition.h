#pragma once

#ifndef LXMLEDITEXT
#define LXMLEDITEXT DECLSPEC_DLLEXPORT
#endif

namespace System
{
namespace LXmlEdit
{

class CTransition;

class LXMLEDITEXT CSMILTransition : public System::Object
{
public:
	CTOR CSMILTransition(System::StringW* type, System::StringW* subtype, uint8 arrowFlags);

	System::StringW* m_type;
	System::StringW* m_subtype;
	CTransition* m_pTransition;
	uint8 m_arrowFlags;
};

class LXMLEDITEXT CTransition : public System::Object
{
public:
	CTOR CTransition(System::StringW* name, uint8 bitCorners, uint8 flags);
	void AddMapping(CSMILTransition* pMapping);

	void Settings(MSWindows::HWND hWnd);

	System::StringW* m_name;
	Array<CSMILTransition*> m_mapping;
	uint8 m_bitCorners;
	uint8 m_flags;
};

class LXMLEDITEXT CTransitions : public System::Object
{
public:
	CTOR CTransitions();

	Array<CTransition*> m_items;

	CSMILTransition* FindMapping(System::StringW* type, System::StringW* subtype);
};

}	// LXmlEdit
}
