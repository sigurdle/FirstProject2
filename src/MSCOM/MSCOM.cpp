// MSCOM.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "../LFC/LFC.h"
#undef interface
#undef FAR
#undef __RPC_FAR
#undef _INC_WINDOWS

#include <windows.h>
#include <objbase.h>

#pragma comment(lib, "../LFC/Debug/LFC.lib")

HINSTANCE g_hInstance;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		g_hInstance = (HINSTANCE)hModule;

		System::InitTypes();
	}

    return TRUE;
}

#undef REFIID
typedef const IID& REFIID;

namespace System
{

class RegKey
{
public:
	CTOR RegKey(HKEY hkey) : m_hKey(hkey)
	{
	}

	~RegKey()
	{
		if (m_hKey)
		{
			RegCloseKey(m_hKey);
		}
	}

	RegKey OpenKey(const char* subkey, REGSAM samDesired = KEY_ALL_ACCESS)
	{
		HKEY hkey;
		RegOpenKeyExA(m_hKey, subkey, 0/*options reserved*/, samDesired, &hkey);
		return RegKey(hkey);
	}

	RegKey CreateKey(const char* subkey, REGSAM samDesired = KEY_ALL_ACCESS)
	{
		HKEY hkey;
		DWORD dwDisposition;
		RegCreateKeyExA(m_hKey, subkey, 0/*options reserved*/, NULL/*class?*/, REG_OPTION_NON_VOLATILE, samDesired, NULL, &hkey, &dwDisposition);
		return RegKey(hkey);
	}

	bool SetValue(const char* valueName)
	{
		long error = RegSetValueExA(m_hKey, valueName, 0/*reserved*/, REG_NONE, NULL, 0);
		if (error == 0)
			return true;
		else
			return false;
	}

	bool SetValue(const char* valueName, DWORD value)
	{
		long error = RegSetValueExA(m_hKey, valueName, 0/*reserved*/, REG_DWORD, (uint8*)&value, 4);
		if (error == 0)
			return true;
		else
			return false;
	}

	bool SetValue(const char* valueName, const uint8* data, uint nbytes)
	{
		long error = RegSetValueExA(m_hKey, valueName, 0/*reserved*/, REG_BINARY, data, nbytes);
		if (error == 0)
			return true;
		else
			return false;
	}

	bool SetValue(const char* valueName, StringA* str)
	{
		long error = RegSetValueExA(m_hKey, valueName, 0/*reserved*/, REG_SZ, (uint8*)str->GetData(), str->Length());
		if (error == 0)
			return true;
		else
			return false;
	}

	bool SetValue(const char* valueName, const char* str)
	{
		long error = RegSetValueExA(m_hKey, valueName, 0/*reserved*/, REG_SZ, (uint8*)str, strlen(str));
		if (error == 0)
			return true;
		else
			return false;
	}

	bool SetValue(const WCHAR* valueName, StringW* str)
	{
		long error = RegSetValueExW(m_hKey, valueName, 0/*reserved*/, REG_SZ, (uint8*)str->GetData(), str->Length()*2);
		if (error == 0)
			return true;
		else
			return false;
	}

	bool DeleteKey(const char* subkey)
	{
		long error = RegDeleteKey(m_hKey, subkey);
		if (error == 0)
			return true;
		else
			return false;
	}

	operator HKEY () const
	{
		return m_hKey;
	}

private:

	HKEY m_hKey;
};

void RegisterCoClass()
{
}

class TypeInfo : public Object, public ITypeInfo2 // ITypeInfo
{
public:
	CTOR TypeInfo()
	{
		m_refcount = 0;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		*ppvObject = NULL;

		if (riid == IID_IUnknown)
		{
			AddRef();
			*ppvObject = static_cast<IUnknown*>(this);;
			return S_OK;
		}
		else if (riid == IID_ITypeInfo)
		{
			AddRef();
			*ppvObject = static_cast<ITypeInfo*>(this);
			return S_OK;
		}
		else if (riid == IID_ITypeInfo2)
		{
			AddRef();
			*ppvObject = static_cast<ITypeInfo2*>(this);
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		++m_refcount;
		return m_refcount;
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		if (--m_refcount == 0)
		{
			delete this;
			return 0;
		}

		return m_refcount;
	}

	ClassType* m_pClass;
	long m_refcount;

        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetTypeAttr( 
            /* [out] */ TYPEATTR __RPC_FAR *__RPC_FAR *ppTypeAttr)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE GetTypeComp( 
            /* [out] */ ITypeComp __RPC_FAR *__RPC_FAR *ppTComp)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetFuncDesc( 
            /* [in] */ UINT index,
            /* [out] */ FUNCDESC __RPC_FAR *__RPC_FAR *ppFuncDesc)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetVarDesc( 
            /* [in] */ UINT index,
            /* [out] */ VARDESC __RPC_FAR *__RPC_FAR *ppVarDesc)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetNames( 
            /* [in] */ MEMBERID memid,
            /* [length_is][size_is][out] */ BSTR __RPC_FAR *rgBstrNames,
            /* [in] */ UINT cMaxNames,
            /* [out] */ UINT __RPC_FAR *pcNames)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE GetRefTypeOfImplType( 
            /* [in] */ UINT index,
            /* [out] */ HREFTYPE __RPC_FAR *pRefType)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE GetImplTypeFlags( 
            /* [in] */ UINT index,
            /* [out] */ INT __RPC_FAR *pImplTypeFlags)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [size_is][out] */ MEMBERID __RPC_FAR *pMemId)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke( 
            /* [in] */ PVOID pvInstance,
            /* [in] */ MEMBERID memid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetDocumentation( 
            /* [in] */ MEMBERID memid,
            /* [out] */ BSTR __RPC_FAR *pBstrName,
            /* [out] */ BSTR __RPC_FAR *pBstrDocString,
            /* [out] */ DWORD __RPC_FAR *pdwHelpContext,
            /* [out] */ BSTR __RPC_FAR *pBstrHelpFile)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetDllEntry( 
            /* [in] */ MEMBERID memid,
            /* [in] */ INVOKEKIND invKind,
            /* [out] */ BSTR __RPC_FAR *pBstrDllName,
            /* [out] */ BSTR __RPC_FAR *pBstrName,
            /* [out] */ WORD __RPC_FAR *pwOrdinal)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE GetRefTypeInfo( 
            /* [in] */ HREFTYPE hRefType,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE AddressOfMember( 
            /* [in] */ MEMBERID memid,
            /* [in] */ INVOKEKIND invKind,
            /* [out] */ PVOID __RPC_FAR *ppv)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ PVOID __RPC_FAR *ppvObj)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE GetMops( 
            /* [in] */ MEMBERID memid,
            /* [out] */ BSTR __RPC_FAR *pBstrMops)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetContainingTypeLib( 
            /* [out] */ ITypeLib __RPC_FAR *__RPC_FAR *ppTLib,
            /* [out] */ UINT __RPC_FAR *pIndex)
	  {
		  return E_NOTIMPL;
	  }
        
        virtual /* [local] */ void STDMETHODCALLTYPE ReleaseTypeAttr( 
            /* [in] */ TYPEATTR __RPC_FAR *pTypeAttr)
	  {
	  }
        
        virtual /* [local] */ void STDMETHODCALLTYPE ReleaseFuncDesc( 
            /* [in] */ FUNCDESC __RPC_FAR *pFuncDesc)
        	  {
	  }

        virtual /* [local] */ void STDMETHODCALLTYPE ReleaseVarDesc( 
            /* [in] */ VARDESC __RPC_FAR *pVarDesc)
	  {
	  }


	// ITypeInfo2

     virtual HRESULT STDMETHODCALLTYPE GetTypeKind( 
         /* [out] */ TYPEKIND __RPC_FAR *pTypeKind)
	  {
			  if (pTypeKind == NULL) return E_POINTER;

			if (m_pClass->m_kwType == CLASSKEY_INTERFACE)
			{
				*pTypeKind = TKIND_INTERFACE;
			}
			else if (m_pClass->m_kwType == CLASSKEY_STRUCT)
			{
				*pTypeKind = TKIND_RECORD;
			}
			else if (m_pClass->m_kwType == CLASSKEY_UNION)
			{
				*pTypeKind = TKIND_UNION;
			}
			else if (m_pClass->m_kwType == CLASSKEY_CLASS)
			{
				*pTypeKind = TKIND_COCLASS;
			}
			else
				return E_FAIL;

			return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetTypeFlags( 
         /* [out] */ ULONG __RPC_FAR *pTypeFlags)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetFuncIndexOfMemId( 
         /* [in] */ MEMBERID memid,
         /* [in] */ INVOKEKIND invKind,
         /* [out] */ UINT __RPC_FAR *pFuncIndex)
     	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetVarIndexOfMemId( 
         /* [in] */ MEMBERID memid,
         /* [out] */ UINT __RPC_FAR *pVarIndex)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetCustData( 
         /* [in] */ REFGUID guid,
         /* [out] */ VARIANT __RPC_FAR *pVarVal)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetFuncCustData( 
         /* [in] */ UINT index,
         /* [in] */ REFGUID guid,
         /* [out] */ VARIANT __RPC_FAR *pVarVal)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetParamCustData( 
         /* [in] */ UINT indexFunc,
         /* [in] */ UINT indexParam,
         /* [in] */ REFGUID guid,
         /* [out] */ VARIANT __RPC_FAR *pVarVal)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetVarCustData( 
         /* [in] */ UINT index,
         /* [in] */ REFGUID guid,
         /* [out] */ VARIANT __RPC_FAR *pVarVal)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetImplTypeCustData( 
         /* [in] */ UINT index,
         /* [in] */ REFGUID guid,
         /* [out] */ VARIANT __RPC_FAR *pVarVal)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetDocumentation2( 
         /* [in] */ MEMBERID memid,
         /* [in] */ LCID lcid,
         /* [out] */ BSTR __RPC_FAR *pbstrHelpString,
         /* [out] */ DWORD __RPC_FAR *pdwHelpStringContext,
         /* [out] */ BSTR __RPC_FAR *pbstrHelpStringDll)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetAllCustData( 
         /* [out] */ CUSTDATA __RPC_FAR *pCustData)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetAllFuncCustData( 
         /* [in] */ UINT index,
         /* [out] */ CUSTDATA __RPC_FAR *pCustData)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetAllParamCustData( 
         /* [in] */ UINT indexFunc,
         /* [in] */ UINT indexParam,
         /* [out] */ CUSTDATA __RPC_FAR *pCustData)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetAllVarCustData( 
         /* [in] */ UINT index,
         /* [out] */ CUSTDATA __RPC_FAR *pCustData)
	  {
		  return E_NOTIMPL;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetAllImplTypeCustData( 
         /* [in] */ UINT index,
         /* [out] */ CUSTDATA __RPC_FAR *pCustData)
	  {
		  return E_NOTIMPL;
	  }

};

}

using System::RegKey;

namespace System
{
ITypeInfo* GetTypeInfo(ClassType* pType)
{
	return NULL;
}
}

class ClassFactory : public System::Object, public IClassFactory
{
public:
	CTOR ClassFactory() : m_refcount(0)
	{
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (&riid == NULL) return E_INVALIDARG;
		if (ppvObject == NULL) return E_INVALIDARG;

		*ppvObject = NULL;

		if (riid == IID_IUnknown)
		{
			*ppvObject = static_cast<IUnknown*>(this);
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IClassFactory)
		{
			*ppvObject = static_cast<IClassFactory*>(this);
			AddRef();
			return S_OK;
		}

		return E_NOINTERFACE;
	}
	
	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		++m_refcount;
		return m_refcount;
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		if (--m_refcount == 0)
		{
			delete this;
			return 0;
		}
		
		return m_refcount;
	}

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
      /* [unique][in] */ IUnknown __RPC_FAR *pUnkOuter,
      /* [in] */ REFIID riid,
      /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
		
		virtual /* [local] */ HRESULT STDMETHODCALLTYPE LockServer( 
      /* [in] */ BOOL fLock)
	{
		return S_OK;
	}

	long m_refcount;
};

namespace System
{

class Instance : public System::Object, public IDispatch
{
public:
	Instance(Object* object) : m_refcount(0)
	{
		m_object = object;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (&riid == NULL) return E_INVALIDARG;
		if (ppvObject == NULL) return E_INVALIDARG;

		*ppvObject = NULL;

		if (riid == IID_IUnknown)
		{
			*ppvObject = static_cast<IUnknown*>(this);
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IDispatch)
		{
			*ppvObject = static_cast<IDispatch*>(this);
			AddRef();
			return S_OK;
		}

		return E_NOINTERFACE;
	}
     
	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		++m_refcount;
		return m_refcount;
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		if (--m_refcount == 0)
		{
		  delete this;
		  return 0;
		}

		return m_refcount;
	}

  virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( 
      /* [out] */ UINT __RPC_FAR *pctinfo);

  virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( 
      /* [in] */ UINT iTInfo,
      /* [in] */ LCID lcid,
      /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
  
  virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
      /* [in] */ REFIID riid,
      /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
      /* [in] */ UINT cNames,
      /* [in] */ LCID lcid,
      /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
  
  virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke( 
      /* [in] */ DISPID dispIdMember,
      /* [in] */ REFIID riid,
      /* [in] */ LCID lcid,
      /* [in] */ WORD wFlags,
      /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
      /* [out] */ VARIANT __RPC_FAR *pVarResult,
      /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
      /* [out] */ UINT __RPC_FAR *puArgErr);

	Object* m_object;
	long m_refcount;
};

HRESULT STDMETHODCALLTYPE Instance::GetTypeInfoCount( 
/* [out] */ UINT __RPC_FAR *pctinfo)
{
	if (pctinfo == NULL) return E_INVALIDARG;
	*pctinfo = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Instance::GetTypeInfo( 
/* [in] */ UINT iTInfo,
/* [in] */ LCID lcid,
/* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE Instance::GetIDsOfNames( 
/* [in] */ REFIID riid,
/* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
/* [in] */ UINT cNames,
/* [in] */ LCID lcid,
/* [size_is][out] */ DISPID __RPC_FAR *rgDispId)
{
	// riid reserved for future use, must be IID_NULL

	if (rgszNames == NULL) return E_INVALIDARG;
	if (rgDispId == NULL) return E_INVALIDARG;

	ClassType* pType = m_object->GetType();
	Dispatch* pDispatch = GetDispatch(pType);

	HRESULT hr = S_OK;

	for (UINT i = 0; i < cNames; i++)
	{
		char aname2[256];
		sprintf(aname2, "%S", rgszNames[i]);
		StringA aname(true, aname2);

		map<StringA*, DispMember, Ref_Less<StringA>, __gc_allocator>::iterator it = pDispatch->m_dispmembersByName.find(&aname);
		if (it == pDispatch->m_dispmembersByName.end())
		{
			rgDispId[i] = DISPID_UNKNOWN;
			hr = DISP_E_UNKNOWNNAME;	// One or more unknown members
		}
		else
		{
			rgDispId[i] = (*it).second.m_dispID;
		}
	}

	return hr;

//	ITypeInfo* typeinfo = System::GetTypeInfo(System::GetType(m_object)->GetClass());

//	return DispGetIDsOfNames(typeinfo, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE Instance::Invoke( 
/* [in] */ DISPID dispIdMember,
/* [in] */ REFIID riid,
/* [in] */ LCID lcid,
/* [in] */ WORD wFlags,
/* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
/* [out] */ VARIANT __RPC_FAR *pVarResult,
/* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
/* [out] */ UINT __RPC_FAR *puArgErr)
{
	if (pDispParams == NULL) return E_INVALIDARG;
	if (dispIdMember < 1) return DISP_E_MEMBERNOTFOUND;

	ClassType* pType = m_object->GetType();
	Dispatch* pDispatch = GetDispatch(pType);

	if (wFlags == DISPATCH_METHOD)
	{
		Method* method = pDispatch->m_dispmembers[dispIdMember]->second.m_method;

		uint8 argsdata[256];
		uint8* p = argsdata;

		for (int i = 0; i < pDispParams->cArgs; i++)
		{
			VARIANTARG& arg = pDispParams->rgvarg[i];

			*(StringW**)p = new StringW(string_copy(arg.bstrVal, SysStringLen(arg.bstrVal)));
			p += sizeof(StringW*);
		}

		long result = pDispatch->Invoke(m_object, method, argsdata, p - argsdata);

		Type* returnType = method->get_ReturnType();
		if (returnType && returnType != Types::type_void)
		{
			if (pVarResult)
			{
				switch (returnType->get_Kind())
				{
				case type_int:
				{
					pVarResult->vt = VT_INT;
					pVarResult->intVal = result;
				}
				break;

				case type_double:
				{
					pVarResult->vt = VT_R8;
				}
				break;
			}
		}
	}
	else
	{
		return E_FAIL;
	}
}

}

HRESULT STDMETHODCALLTYPE ClassFactory::CreateInstance( 
      /* [unique][in] */ IUnknown __RPC_FAR *pUnkOuter,
      /* [in] */ REFIID riid,
      /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (&riid == NULL) return E_INVALIDARG;
	if (ppvObject == NULL) return E_INVALIDARG;
	*ppvObject = NULL;

	if (pUnkOuter)
	{
		return CLASS_E_NOAGGREGATION;
	}

	System::ClassType* pType = System::pD->LookupNamedType(ASTR("Lerstad::Test"))->GetClass();

	System::Object* obj = System::newobj(pType);

	System::Instance* p = new System::Instance(obj);
	return p->QueryInterface(riid, ppvObject);
}

STDAPI DllGetClassObject(
  REFCLSID rclsid,  //CLSID for the class object
  REFIID riid,      //Reference to the identifier of the interface 
                    // that communicates with the class object
  LPVOID * ppv      //Address of output variable that receives the 
                    // interface pointer requested in riid
)
{
//	MessageBox(NULL, "", "", MB_OK);

	ClassFactory* factory = new ClassFactory;
	return factory->QueryInterface(riid, ppv);
}

STDAPI DllCanUnloadNow()
{
	return S_FALSE;
}

STDAPI DllRegisterServer(void)
{
	RegKey key(HKEY_CLASSES_ROOT);

	{
		RegKey progID = key.CreateKey("Lerstad.Test");

		RegKey clsid = progID.CreateKey("CLSID");
		clsid.SetValue(NULL, "{BC1F82BD-A863-450a-9BA5-75D028682B52}");
	}

	{
		RegKey clsid = key.OpenKey("CLSID");
		RegKey myclsid = clsid.CreateKey("{BC1F82BD-A863-450a-9BA5-75D028682B52}");
		myclsid.SetValue(NULL, "LerstadTest");

		// InProcServer subkey
		RegKey InProcServer = myclsid.CreateKey("InProcServer32");
		char modulename[512];
		GetModuleFileName(g_hInstance, modulename, 512);
		char entry[512];
	//	sprintf(entry, "%s /Automation", modulename);
		sprintf(entry, "%s", modulename);
		InProcServer.SetValue(NULL, entry);

		// ProgID
		RegKey ProgID = myclsid.CreateKey("ProgID");
		ProgID.SetValue(NULL, "Lerstad.Test.1");

		// VersionIndependentProgID
		RegKey VersionIndependentProgID = myclsid.CreateKey("VersionIndependentProgID");
		VersionIndependentProgID.SetValue(NULL, "Lerstad.Test");

		// Programmable subkey
		RegKey Programmable = myclsid.CreateKey("Programmable");
	}

	return S_OK;
}

STDAPI DllUnregisterServer(void)
{
	return S_OK;
}
