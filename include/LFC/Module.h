namespace System
{

/** @addtogroup LFC
@{
*/

class LFCEXT CompoundMemoryAddressRange
{
public:
	// TODO
};

class LFCEXT MemoryAddressRange
{
public:
	CTOR MemoryAddressRange(ULONG_PTR _start, ULONG_PTR _end) : start(_start), end(_end)
	{
	}

//	CompoundMemoryAddressRange operator | ()

	ULONG_PTR start;
	ULONG_PTR end;
};

/// The Module class represents a module (.dll or .exe on Windows).
/**
There is one global Module variable for each module called _Module;
*/
class LFCEXT Module : public Object
{
public:
	CTOR Module();
	CTOR Module(HMODULE hModule);
	~Module();

	void Init(HMODULE hModule);

	String GetFullPath() const throw()
	{
		return m_fullpath;
	}

	String get_Name();
	String get_Path();

	MemoryAddressRange get_Address() const
	{
		return MemoryAddressRange((ULONG_PTR)m_hModule, (ULONG_PTR)m_hModule + m_sizeOfImage);
	}

	virtual String ToString() override;

#if _WIN32

	virtual BOOL DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved = NULL);

	BOOL DisableThreadLibraryCalls()
	{
		return ::DisableThreadLibraryCalls(m_hModule);
	}

	FARPROC GetProcAddress(__in LPCSTR lpProcName)
	{
		return ::GetProcAddress(m_hModule, lpProcName);
	}

	HMODULE GetHandle() const throw()
	{
		return m_hModule;
	}

	void SetHandle(HMODULE hModule);

	bool operator == (decltype(nullptr)) const throw()
	{
		return m_hModule == nullptr;
	}

	bool operator != (decltype(nullptr)) const throw()
	{
		return m_hModule != nullptr;
	}

	HINSTANCE GetModuleInstance() const throw()
	{
		return GetHandle();
	}

	void SetInstance(HINSTANCE hInstance)
	{
		SetHandle(hInstance);
	}

	static Module* FromHandle(HMODULE hModule);

#endif

	virtual BOOL ProcessAttach();
	virtual BOOL Term();

	typedef void (*proctype)();

	void AddProc(StringIn name, proctype);
	proctype GetProc(StringIn name);

	/**
	Checks if an address is contained within the address space of this module.
	@param address The address to check for
	@return <code>true</code> if address is contained within the address space of this module,
	<code>false</code> otherwise.
	*/
	bool Contains(ULONG_PTR address) const
	{
		return address >= (ULONG_PTR)m_hModule && address < (ULONG_PTR)m_hModule+m_sizeOfImage;
	}

	/**
	Checks if an address is within the managed garbage collected Heap
	@param address The address to check for
	@return <code>true</code> if address is within the managed garbage collected Heap,
	<code>false</code> otherwise.
	*/
	static bool WithinManaged(ULONG_PTR address);
//	static void BuildRanges();

	uint64 get_LoadTypesTime() const
	{
		return m_loadTypesTime;
	}

	/**
	Finds the Module that contains a specific address
	@param address The address to check for
	@return Module, or <code>nullptr</code> if no such module exists.
	*/
	static Module* FromAddress(const void* address);

	static Module* FindModule(StringIn name);
	static Module* Load(StringIn filename);
	static List<Module*>* get_Loaded();
	static List<String>* get_All();

	struct Data
	{
		vector<Declarator*> m_allfunctions;
	}
	*_p;

private:

	CTOR Module(const Module& other);	// copy constructor
	Module& operator = (const Module& other);	// assignment
//	Module& operator = (HMODULE hModule);	// assignment

	void LoadTypes(HMODULE hModule);

	/*
	class PrivateData
	{
	public:
		map<String, proctype> m_procs;
	};
	*/
#ifdef _WIN32
	HMODULE m_hModule;
#else
	void* m_hModule;
#endif

	ULONG_PTR m_sizeOfImage;

	void* m_user;

	TypeLib* m_typelib;

	String m_fullpath;
	String m_name;
	map<String, proctype> m_procs;
//	PrivateData* m_private;

	uint64 m_loadTypesTime;

	class StaticPrivate
	{
	public:
		CriticalSection critsec;

		map<String, Module*> s_Modules;
		map<HMODULE, Module*> s_HModules;
		List<Module*> s_modules;
	};

	static StaticPrivate* sdata;

	/*
	static map<String, Module*>* s_Modules;
	static map<HMODULE, Module*>* s_HModules;
	static List<Module*>* s_modules;
	*/

//	static vector<MemoryAddressRange> s_ranges;
//	static bool m_managedfirst;
};

/** @} */

}	// System
