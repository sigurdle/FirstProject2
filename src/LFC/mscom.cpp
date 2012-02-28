#include "stdafx.h"
#include "LFC.h"
#undef interface
#undef FAR
#undef __RPC_FAR
#undef _INC_WINDOWS

using namespace std;

#include <objbase.h>

#undef REFIID
typedef const IID& REFIID;

#if 0

namespace System
{

class LFCEXT RegKey
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

	bool SetValue(const WCHAR* valueName, StringW* str)
	{
		long error = RegSetValueExW(m_hKey, valueName, 0/*reserved*/, REG_SZ, (uint8*)str->GetData(), str->Length()*2);
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

#endif
