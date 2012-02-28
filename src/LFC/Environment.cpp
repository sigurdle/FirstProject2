#include "stdafx.h"
#include "LFC.h"

#include <Psapi.h>
/*
#include <atlbase.h>


ATL::CRegKey;
ATL::CRegObject;
*/
namespace System
{

extern SYSTEM_INFO sysinfo;

// static
HMODULE Environment::m_hKernel32;
HMODULE Environment::m_hNtdll;

// static
uint Environment::get_ProcessorCount()
{
	return sysinfo.dwNumberOfProcessors;

	//MS::Win32::RegistryKey key = MS::Win32::Registry::OpenKey(NULL, "");
//	vector<byte> g = key.QueryBinaryValue("test");
}

// static
uint Environment::get_SystemPageSize()
{
	return sysinfo.dwPageSize;
}

// static
String Environment::get_UserName()
{
	WCHAR buffer[256];
	DWORD cb = _countof(buffer);
	BOOL success = ::GetUserNameW(buffer, &cb);
	return buffer;
}

// static
String Environment::get_MachineName()
{
	// On Windows
	// Name changes made by the SetComputerName or SetComputerNameEx functions do not take effect until the user restarts the computer. 

	static WCHAR buffer[64];
	static DWORD nchars = _countof(buffer);
	static ImmutableString<WCHAR> str((::GetComputerNameEx(ComputerNameNetBIOS, buffer, &nchars), buffer));
	
	return &str;
}

// static
bool Environment::get_UserInteractive()
{
	// TODO
	return true;
}

// static
uint Environment::get_TickCount()
{
	return ::GetTickCount();
}

// static
vector<String> Environment::get_CommandLineArgs()
{
	return s_commandLineArgs;
	// TODO
//	ASSERT(0);
	//vector<String> v;
//	return v;
}

// static
String Environment::get_NewLine()
{
#if _WIN32
	static ImmutableString<char> newline("\r\n");
#else
	static ImmutableString<char> newline("\n");
#endif
	return &newline;
}

// static
String Environment::get_SystemDirectory()
{
	static WCHAR buffer[512];
	static ImmutableString<WCHAR> str((::GetSystemDirectory(buffer, _countof(buffer)), buffer));
	return &str;
}

// static
String Environment::GetEnvironmentVariable(StringIn name)
{
	DWORD len = ::GetEnvironmentVariableW(name.c_strw(), nullptr, 0);

	WCHAR* value = new WCHAR[len+1];
	::GetEnvironmentVariableW(name.c_strw(), value, (len+1));
	return String::FromRaw(value, len);
}

// static
void Environment::SetEnvironmentVariable(StringIn name, StringIn value)
{
	::SetEnvironmentVariableW(name.c_strw(), value.c_strw());
}

// static
void Environment::SetEnvironmentVariable(StringIn name, StringIn value, EnvironmentVariableTarget target)
{
	if (target == EnvironmentVariableTarget_Process)
	{
		SetEnvironmentVariable(name, value);
	}
	else
	{
		if (target == EnvironmentVariableTarget_User)
		{
// HKEY_CURRENT_USER\Environment 
			MS::Win32::RegistryKey regKey = MS::Win32::Registry::OpenKey(HKEY_CURRENT_USER, L"Environment");
			regKey.SetStringValue(name, value);
		}
		else
		{
// HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment registry key,
		}

// then broadcast a WM_SETTINGCHANGE message with lParam set to the string "Environment". 
		PostMessageW(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"Environment");
	}
}

// static
String Environment::ExpandEnvironmentVariables(StringIn name)
{
	ASSERT(0);
	return String();
}

size_t Environment::get_WorkingSet()
{
	PROCESS_MEMORY_COUNTERS memcounters;
	BOOL success = GetProcessMemoryInfo(GetCurrentProcess(), &memcounters, sizeof(memcounters));
	ASSERT(success);
	return memcounters.WorkingSetSize;
}

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);

// static
bool Environment::get_Is64BitOperatingSystem()
{
#ifdef _M_X64

	return true;

#else

	// IsWow64Process is not available on all supported versions of Windows.

	static LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(m_hKernel32, "IsWow64Process");

	if (fnIsWow64Process)
	{
		BOOL bIsWow64;
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
		{
			ASSERT(0);
		}

		if (bIsWow64) return true;
	}
	return false;

#endif
}

vector<String> Environment::s_commandLineArgs;

void Environment::ParseCommandLineArgs(wchar_t* str)
{
	wchar_t* p = str;
	while (*p)
	{
		IO::StringWriter s;

		while (*p == ' ' || *p == '\t') ++p;

		if (*p == '\"')
		{
			++p;

			while (*p)
			{
				if (*p == '\"')
				{
					++p;
					break;
				}

				s << *p++;
			}
		}
		else
		{
			while (*p)
			{
				if (*p == ' ' || *p == '\t') break;
				s << *p++;
			}
		}

		s_commandLineArgs.push_back(s);
	}
}

}	// System
