namespace System
{

template<class T>
class _HiddenAddRefRelease : public T
{
private:
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
};

template<class T> class ComPtr;

template<class T>
class ComPtrBase
{
public:

	typedef T _PtrClass;

	CTOR ComPtrBase() : p(nullptr)
	{
	}

	CTOR ComPtrBase(decltype(nullptr)) : p(nullptr)
	{
	}

	CTOR ComPtrBase(ComPtrBase&& other) : p(other.p)
	{
		other.p = nullptr;
	}

	CTOR ComPtrBase(T* p2) : p(p2)
	{
		if (p) p->AddRef();
	}

	~ComPtrBase()
	{
		if (p)
		{
			p->Release();
		}
	}

	void Release()
	{
		T* pTemp = p;
		if (pTemp)
		{
			p = nullptr;
			pTemp->Release();
		}
	}

	void Attach(T* p2) throw()
	{
		if (p) p->Release();
		p = p2;
	}

	T* Detach() throw()
	{
		T* p2 = p;
		p = nullptr;
		return p2;
	}

	bool operator ! () const throw()
	{
		return p == nullptr;
	}

	bool operator == (decltype(nullptr)) const throw()
	{
		return p == nullptr;
	}

	bool operator == (const T* p2) const throw()
	{
		return p == p2;
	}

	bool operator != (const T* p2) const throw()
	{
		return p != p2;
	}

	bool operator < (const T* p2) const throw()
	{
		return p < p2;
	}

	T& operator*() const throw()
	{
		ASSERT(p != nullptr);
		return *p;
	}

	//The assert on operator& usually indicates a bug.  If this is really
	//what is needed, however, use AddressOf() or take the address of the p member explicitly.
	T** operator&() throw()
	{
		ASSERT(p == nullptr);
		/*
		if (p)
		{
			p->Release();
			p = nullptr;
		}
		*/
		return &p;
	}

	_HiddenAddRefRelease<T>* operator -> () const throw()
	{
		ASSERT(p);
		return static_cast<_HiddenAddRefRelease<T>*>(p);
	}

	operator T* () const throw()
	{
		return p;
	}

	T* get() const throw()
	{
		return p;
	}

	T** AddressOf() throw()
	{
		return &p;
	}

	void** VoidAddressOf() throw()
	{
		return (void**)&p;
	}

	bool IsEqualObject(IUnknown* pOther) const throw()
	{
		if (p == nullptr)
		{
			return pOther == nullptr;
		}
		else if (pOther == nullptr)
		{
			return false;
		}

		ComPtr<IUnknown> unk0;
		p->QueryInterface(__uuidof(IUnknown), (void**)&unk0);

		ComPtr<IUnknown> unk1;
		pOther->QueryInterface(__uuidof(IUnknown), (void**)&unk1);

		return unk0 == unk1;
	}

	template<class T2> HRESULT QueryInterface(T2** p2) const throw()
	{
		HRESULT hr = p->QueryInterface(__uuidof(T2), reinterpret_cast<void**>(p2));
		return hr;
	}

#ifndef __LERSTAD__
	HRESULT CoCreateInstance(__in const ::IID& rclsid, __in_opt IUnknown* pUnkOuter = nullptr, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER)
	{
		if (p != nullptr) raise(SystemException(S("CoCreateInstance() : ComPtr.p != nullptr")));

		return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(T), reinterpret_cast<void**>(&p));
	}

	HRESULT CoCreateInstance(LPCOLESTR clsidstr, __in_opt IUnknown* pUnkOuter = nullptr, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER)
	{
		CLSID clsid;
		HRESULT hr = ::CLSIDFromString(clsidstr, &clsid);
		if (FAILED(hr)) return hr;
		return CoCreateInstance(clsid, pUnkOuter, dwClsContext);
	}

	HRESULT CoCreateInstance(const String& str, __in_opt IUnknown* pUnkOuter = nullptr, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER)
	{
		CLSID clsid;
		HRESULT hr = ::CLSIDFromString(str.c_strw_flen<64>(), &clsid);
		if (FAILED(hr)) return hr;
		return CoCreateInstance(clsid, pUnkOuter, dwClsContext);
	}
#endif

public:

	T* p;
};

template<class T>
class ComPtr : public ComPtrBase<T>
{
public:

	CTOR ComPtr() : ComPtrBase()
	{
	}

	CTOR ComPtr(decltype(nullptr)) : ComPtrBase(nullptr)
	{
	}

#ifndef __LERSTAD__
	template<class T2> CTOR ComPtr(const ComPtr<T2>& other) : ComPtrBase(other.get())
	{
	}
#endif

	CTOR ComPtr(const ComPtr& other) : ComPtrBase(other.get())
	{
	}

	CTOR ComPtr(ComPtr&& other) : ComPtrBase(other)
	{
	}

	CTOR ComPtr(T* p2) : ComPtrBase(p2)
	{
	}

#ifndef __LERSTAD__

	template<class T2> ComPtr& operator = (T2* p2) throw()
	{
		if (p2) p2->AddRef();
		if (p) p->Release();
		p = p2;
		return *this;
	}

	template<class T2> ComPtr& operator = (const ComPtr<T2>& other)  throw()
	{
		if (other.p != nullptr) other.p->AddRef();
		if (p) p->Release();
		p = other.p;
		return *this;
	}

	template<class T2> ComPtr& operator = (ComPtr<T2>&& other)  throw()
	{
		if (p != other.p)
		{
			if (p) p->Release();

			p = other.p;
			other.p = nullptr;
		}

		return *this;
	}

	template<class T2> bool operator == (const ComPtr<T2>& other) const  throw()
	{
		return p == other.p;
	}

#endif

	ComPtr& operator = (decltype(nullptr)) throw()
	{
		if (p)
		{
			p->Release();
			p = nullptr;
		}
		return *this;
	}

	ComPtr& operator = (const ComPtr& other) throw()
	{
		if (other.get() != nullptr) other.get()->AddRef();
		if (p) p->Release();
		p = other.get();
		return *this;
	}
};

#ifndef __LERSTAD__
// specialiation
template<> class ComPtr<IDispatch> : public ComPtrBase<IDispatch>
{
public:

	CTOR ComPtr() : ComPtrBase()
	{
	}

	CTOR ComPtr(decltype(nullptr)) : ComPtrBase(nullptr)
	{
	}

	template<class T2> CTOR ComPtr(const ComPtr<T2>& other) : ComPtrBase(other.get())
	{
	}

	CTOR ComPtr(const ComPtr<IDispatch>& other) : ComPtrBase(other.get())
	{
	}

	CTOR ComPtr(ComPtr&& other) : ComPtrBase(other)
	{
	}

	CTOR ComPtr(IDispatch* p2) : ComPtrBase(p2)
	{
	}

	_Check_return_ HRESULT GetIDOfName(_In_z_ LPCOLESTR lpsz, _Out_ DISPID* pdispid) const throw()
	{
		return p->GetIDsOfNames(IID_NULL, const_cast<LPOLESTR*>(&lpsz), 1, LOCALE_USER_DEFAULT, pdispid);
	}

	// Invoke a method by DISPID with no parameters
	_Check_return_ HRESULT Invoke0(_In_ DISPID dispid, _Out_opt_ VARIANT* pvarRet = nullptr) const throw()
	{
		DISPPARAMS dispparams = { NULL, NULL, 0, 0};
		return p->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, pvarRet, nullptr, nullptr);
	}
	// Invoke a method by name with no parameters
	_Check_return_ HRESULT Invoke0(_In_z_ LPCOLESTR lpszName, _Out_opt_ VARIANT* pvarRet = nullptr) const throw()
	{
		HRESULT hr;
		DISPID dispid;
		hr = GetIDOfName(lpszName, &dispid);
		if (SUCCEEDED(hr))
			hr = Invoke0(dispid, pvarRet);
		return hr;
	}

};
#endif

template<class T, class T2> T __dynamic_cast(const ComPtr<T2>& ptr)
{
#ifndef __LERSTAD__
	T p;
	HRESULT hr = ptr.QueryInterface(&p);
	if (FAILED(hr)) return nullptr;
	return p;
#endif
}

}	// System
