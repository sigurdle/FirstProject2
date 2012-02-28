// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "GUI")

namespace System
{

Module _Module;

extern "C"
{

class type_info
{
public:
	virtual ~type_info()
	{
	}

	void *_m_data;
	char _m_d_name[1];
};

BOOL WINAPI RawDllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		try
		{
			LoadTypes(&_Module, hModule);
		}
		catch (Exception* e)
		{
			DebugTrace(e->get_Reason() << "\n");
			return FALSE;
		}

		((type_info*)&typeid(Gui::Color*))->_m_data = new PointerType(typeof(Gui::Color)->GetClass());
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HINSTANCE, DWORD, LPVOID) = RawDllMain;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	return _Module.DllMain(hModule, ul_reason_for_call, lpReserved);
}

}	// extern "C"
}	// System
