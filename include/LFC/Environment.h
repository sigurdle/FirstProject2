namespace System
{

enum EnvironmentVariableTarget
{
	EnvironmentVariableTarget_Process,
	EnvironmentVariableTarget_User,
	EnvironmentVariableTarget_Machine,
};

#undef GetEnvironmentVariable
#undef SetEnvironmentVariable

class LFCEXT Environment
{
public:

	static vector<String> get_CommandLineArgs();
	static uint get_ProcessorCount();
	static uint get_SystemPageSize();
	static String get_UserName();
	static String get_MachineName();
	static bool get_UserInteractive();
	static String get_NewLine();
	static String get_SystemDirectory();
	static size_t get_WorkingSet();
	static uint get_TickCount();
	static String GetEnvironmentVariable(StringIn name);
	static void SetEnvironmentVariable(StringIn name, StringIn value);
	static void SetEnvironmentVariable(StringIn name, StringIn value, EnvironmentVariableTarget target);
	static String ExpandEnvironmentVariables(StringIn name);

	static __declspec(noreturn) void Exit(int exitCode);
	static __declspec(noreturn) void FailFast(StringIn message);

	static bool get_Is64BitOperatingSystem();

#ifdef _M_X64
	static const bool Is64BitProcess = true;
#else
	static const bool Is64BitProcess = false;
#endif

	/*
	ProcessorFeatures get_ProcessorFeatures()
	{
		return s_ProcessorFeatures;
	}
	*/

	/*
	bool constexpr get_Is64BitProcess()
	{
#ifdef _M_X64
		return true;
#else
		return false;
	}
	*/

	static HMODULE m_hKernel32;
	static HMODULE m_hNtdll;

	static void ParseCommandLineArgs(wchar_t* str);

private:

	static vector<String> s_commandLineArgs;

	CTOR Environment();
	Environment& operator = (const Environment&);
};

}	// System
