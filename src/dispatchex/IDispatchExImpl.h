// Copyright © 1998-99 the e-comm group, inc.
//
// IDispatchExImpl.h: This class implements the IDispatchEx
// interface for an object. This interface allows for dynamic
// property and function composition. NOTE: To disable the use
// of ITypeInfo for IDispatchEx inheritance, define the macro
// IDISPATCHEX_NO_TYPEINFO
//
// $Author: Graf $
// $Date: 3/18/99 10:02a $
// $Revision: 9 $
// $Archive: /e-comm group/Components/TestDispatchEx/IDispatchExImpl.h $

#ifndef _DISPATCH_EX_DATA_H
#define _DISPATCH_EX_DATA_H

#if _WINDOWS
// For critical section locking
#include "CScopeSingleLock.h"
// Class that holds the dynamic dispatch info
#include "CDynamicDispatchEntry.h"
// Support for smart class factory
#include "CDispatchExClassFactory.h"
#endif	// _WINDOWS

// Determine if the user of this class has specified a start value for
// DISPIDs
#ifndef DISPID_START
// Default to starting at zero
#define DISPID_START 0
#endif


template<class DERIVED_CLASS,class BASE_ITF,const IID* BASE_IID,
	const GUID* BASE_LIBID = &CComModule::m_libid,WORD wMajor = 1,
	WORD wMinor = 0>
class ATL_NO_VTABLE IDispatchExImpl : public BASE_ITF
{
#if _WINDOWS
	// typedefs for easier reading
	typedef IDispatchExImpl<DERIVED_CLASS,BASE_ITF,BASE_IID,BASE_LIBID,wMajor,wMinor> __this;
	typedef CUMap<CUString,LPCTSTR,CDynamicDispatchEntry*,CDynamicDispatchEntry*&> CMapNameToEntry;
	typedef CUMap<DISPID,DISPID,CDynamicDispatchEntry*,CDynamicDispatchEntry*&> CMapDispIDToEntry;

	// For multi-threaded safety
	CComAutoCriticalSection m_csAccessSync;
	// For looking up information
	CMapDispIDToEntry m_mapDispIDToEntry;
	CMapNameToEntry m_mapNameToEntry;
	// For caseless lookups
	CMapNameToEntry m_mapCaselessNameToEntry;
	// The current dispid to add entries at
	DISPID m_dispidNext;
#ifndef IDISPATCHEX_NO_TYPEINFO
	// Holds the parents ITypeInfo
	ITypeInfo* m_pTypeInfo;
#endif

	// Helpers

	/***************************************************************************
	* Function:	IDispatchExImpl::GetEntryByName()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<BSTR> bstrName - the name of the entry to find
	*			<DWORD> dwGrfDex - the flags describing the comparison operator
	* Returns:	<CDynamicDispatchEntry*> the entry that was found or NULL
	* Purpose:	Finds an entry by name and case sensitivity
	***************************************************************************/

	CDynamicDispatchEntry* GetEntryByName(BSTR bstrName,
		DWORD dwGrfDex = fdexNameCaseInsensitive)
	{
		CDynamicDispatchEntry* pEntry = NULL;
		// Determine the type of comparison to use
		if( dwGrfDex & fdexNameCaseSensitive )
		{
			// Get the pointer to the entry
			m_mapNameToEntry.Lookup(CUString(bstrName),pEntry);
		}
		else
		{
			// Make a copy of the string
			CUString strTemp(bstrName);
			// Convert to a consistent case
			strTemp.MakeLower();
			// Get the pointer to the entry
			m_mapCaselessNameToEntry.Lookup(strTemp,pEntry);
		}
		return pEntry;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::CreateNewEntry()
	* Author:	Joe Graf
	* Date:		2/12/99
	*			2/15/99 JG - Added support for type info members
	* Args:		<BSTR> bstrName - the name of the entry to find
	*			<DISPID*> pDispID - the out parameter of the dispid
	*			<VARIANT> vtVal - the starting value of the property
	*			<bool> bTypeInfo - whether this method is contained in the
	*			type info or our map
	*			<bool> bUseInDispid - forces the use of the passed in dispid
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Creates a new dispatch entry
	***************************************************************************/

	HRESULT CreateNewEntry(BSTR bstrName,DISPID* pDispID,VARIANT vtVal,
		bool bTypeInfo = false,bool bUseInDispid = false)
	{
		// Default to failure
		HRESULT hr = E_OUTOFMEMORY;
		// Determine if the passed in dispid should be used
		if( bUseInDispid == true )
		{
			// Copy the dispid
			m_dispidNext = *pDispID;
		}
		CDynamicDispatchEntry* pEntry = NULL;
		// Try to allocate a new entry
		ATLTRY(pEntry = new CDynamicDispatchEntry(bstrName,m_dispidNext,
			vtVal,bTypeInfo));
		if( pEntry != NULL )
		{
			// Add the new entry to the dispid map
			m_mapDispIDToEntry.SetAt(pEntry->GetDispID(),pEntry);
			// Add it to the case sensitive map
			m_mapNameToEntry.SetAt(CUString(bstrName),pEntry);
			// Copy the string for caseless comparison
			CUString strCopy(bstrName);
			// Change the case
			strCopy.MakeLower();
			// Add to the caseless map
			m_mapCaselessNameToEntry.SetAt(strCopy,pEntry);
			// Copy the outbound dispid
			*pDispID = pEntry->GetDispID();
			// Increment the next dispid. This is done here to prevent holes
			// in the dispid range on failed creates
			m_dispidNext = (m_dispidNext < 0) ? 0 : m_dispidNext + 1;
			// Tell the caller that everything worked
			hr = S_OK;
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetStartDispID()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DISPID*> pDispID - the out parameter that gets the dispid
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Returns the first dispid in the map. This will look for the first
	*			not deleted entry and return that dispid.
	***************************************************************************/

	HRESULT GetStartDispID(DISPID* pDispID)
	{
		// Default to no entries available
		HRESULT hr = S_FALSE;
		// Get the first map position
		UPOSITION pos = m_mapDispIDToEntry.GetStartPosition();
		bool bDone = false;
		// There are entries and we are not done looking
		while( pos != NULL && bDone == false )
		{
			DISPID dispid = -1;
			CDynamicDispatchEntry* pEntry = NULL;
			// Get the next entry in the map class
			m_mapDispIDToEntry.GetNextAssoc(pos,dispid,pEntry);
			// Determine if this item is not deleted
			if( pEntry->IsDeleted() == false )
			{
				// No need to look further
				bDone = true;
				// Return the dispid
				*pDispID = dispid;
				// Change the HRESULT to S_OK so that the caller does not
				// think that we have no members
				hr = S_OK;
			}
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetNextDispID()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DISPID> dispid - the current dispid to search from
	*			<DISPID*> pDispID - the out parameter that gets the dispid
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Returns the nextt dispid in the map. This will look for the first
	*			not deleted entry and return that dispid.
	***************************************************************************/

	HRESULT GetNextDispID(DISPID dispid,DISPID* pDispID)
	{
		// Default to no entries available
		HRESULT hr = S_FALSE;
		bool bDone = false;
		// Search until we have no more entries or found the next item
		while( bDone == false )
		{
			// Move to what we think is the next dispid
			dispid++;
			// For fetching from the map class
			CDynamicDispatchEntry* pEntry = NULL;
			// Get the next entry in the map class
			if( m_mapDispIDToEntry.Lookup(dispid,pEntry) == TRUE )
			{
				// Determine if this item is not deleted
				if( pEntry->IsDeleted() == false )
				{
					// No need to look further
					bDone = true;
					// Return the dispid
					*pDispID = dispid;
					// Change the HRESULT to S_OK so that the caller does not
					// think that we have no members
					hr = S_OK;
				}
			}
			else
			{
				// There are no more entries in the map class
				bDone = true;
			}
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetVariantByDispID()
	* Author:	Joe Graf
	* Date:		2/12/99
	*			2/15/99 JG - Added the TypeInfo support
	* Args:		<DISPID> dispid - the current dispid to search for
	*			<VARIANT*> pvtResult - the variant that holds the out value
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Copies the variant held at the specified dispid
	***************************************************************************/

	HRESULT GetVariantByDispID(DISPID dispid,VARIANT* pvtResult)
	{
		// Clear the destination variant
		HRESULT hr = VariantClear(pvtResult);
		if( SUCCEEDED(hr) )
		{
			// Holds the entry object
			CDynamicDispatchEntry* pEntry = NULL;
			// Look for the entry corresponding to this dispatch
			if( m_mapDispIDToEntry.Lookup(dispid,pEntry) == TRUE )
			{
				_ASSERTE(AfxIsValidAddress(pEntry,sizeof(CDynamicDispatchEntry)));
				// Only do the copy if this is a dynamic property
				if( pEntry->UseTypeInfo() == false )
				{
					// Copy the VARIANT from the entry
					hr = pEntry->GetVar(pvtResult);
				}
				else
				{
					// Tell the caller that this dispid is TypeInfo based
					hr = S_FALSE;
				}
			}
			else
			{
				// Unable to find the specified entry
				hr = DISP_E_MEMBERNOTFOUND;
			}
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::SetVariantByDispID()
	* Author:	Joe Graf
	* Date:		2/12/99
	*			2/15/99 JG - Added the TypeInfo support
	* Args:		<DISPID> dispid - the current dispid to search for
	*			<VARIANT*> pvtResult - the variant that we are to copy
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Copies the variant passed in to the entry mapped to the dispid
	***************************************************************************/

	HRESULT SetVariantByDispID(DISPID dispid,VARIANT* pvtResult)
	{
		// Holds the entry object
		CDynamicDispatchEntry* pEntry = NULL;
		// Default to unable to find the specified entry
		HRESULT hr = DISP_E_MEMBERNOTFOUND;
		// Look for the entry corresponding to this dispatch
		if( m_mapDispIDToEntry.Lookup(dispid,pEntry) == TRUE )
		{
			_ASSERTE(AfxIsValidAddress(pEntry,sizeof(CDynamicDispatchEntry)));
			// Only do the copy if this is a dynamic property
			if( pEntry->UseTypeInfo() == false )
			{
				// Set the VARIANT in the entry
				hr = pEntry->SetVar(pvtResult);
			}
			else
			{
				// Tell the caller that this dispid is TypeInfo based
				hr = S_FALSE;
			}
		}
		return hr;
	}

#ifndef IDISPATCHEX_NO_TYPEINFO
	/***************************************************************************
	* Function:	IDispatchExImpl::AddTypeInfoDispIDs()
	* Author:	Joe Graf
	* Date:		2/15/99
	* Args:		None
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Uses the TypeInfo interface to add any members that the derived
	*			class needs to expose.
	***************************************************************************/

	HRESULT AddTypeInfoDispIDs(void)
	{
		TYPEATTR* pta = NULL;
		// Did you call TypeInfoInit() first?
		_ASSERTE(m_pTypeInfo != NULL);
		// Determine the number of methods in the object
		HRESULT hr = m_pTypeInfo->GetTypeAttr(&pta);
		if( SUCCEEDED(hr) )
		{
			// Loop through getting the information on each member
			for( UINT nIndex = 0;
				nIndex < pta->cFuncs && SUCCEEDED(hr); nIndex++ )
			{
				FUNCDESC* pfd = NULL;
				// Get the function description for this member
				hr = m_pTypeInfo->GetFuncDesc(nIndex,&pfd);
				if( SUCCEEDED(hr) )
				{
					CComBSTR bstrName;
					// Determine the name of this member
					hr = m_pTypeInfo->GetDocumentation(pfd->memid,
						&bstrName,NULL,NULL,NULL);
					if( SUCCEEDED(hr) )
					{
						// For fetching from the map class
						CDynamicDispatchEntry* pEntry = NULL;
						// Look to see if we have already added an entry for
						// the dispid. This happens since get/put properties
						// share the same id.
						if( m_mapDispIDToEntry.Lookup(pfd->memid,pEntry)
							== FALSE )
						{
							// Add the member to our dispatch maps
							hr = CreateNewEntry(bstrName,&pfd->memid,
								CComVariant(),true,true);
						}
					}
					// Release the memory alloced on our behalf
					m_pTypeInfo->ReleaseFuncDesc(pfd);
				}
			}
			// Release the memory alloced on our behalf
			m_pTypeInfo->ReleaseTypeAttr(pta);
		}
		return hr;
	}
#endif

	/***************************************************************************
	* Function:	IDispatchExImpl::InvokeByDispID()
	* Author:	Joe Graf
	* Date:		2/15/99
	* Args:		<DISPID> dispid - the dispid of the entry to invoke
	*			<LCID> lcid - the locale id
	*			<WORD> wFlags - calling flags
	*			<DISPPARAMS*> pDispParams - the dispparams of the method
	*			<VARIANT*> pvtResult - the variant holding the result
	*			<EXCEPINFO*> pExcepInfo - the exception info pointer
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Invokes the LPDISPATCH held in the dispid passed in
	***************************************************************************/

	HRESULT InvokeByDispID(DISPID dispid,LCID lcid,WORD wFlags,
		DISPPARAMS* pDispParams,VARIANT* pvtResult,EXCEPINFO* pExcepInfo)
	{
		HRESULT hr = DISP_E_MEMBERNOTFOUND;
		// Find the entry that corresponds to this name
		CDynamicDispatchEntry* pEntry = NULL;
		// Look up the entry in the dispid map
		if( m_mapDispIDToEntry.Lookup(dispid,pEntry) == TRUE )
		{
			_ASSERTE(AfxIsValidAddress(pEntry,
				sizeof(CDynamicDispatchEntry)));
			CComVariant vtDisp;
			// Get the variant that holds the dispatch
			hr = pEntry->GetVar(&vtDisp);
			if( SUCCEEDED(hr) )
			{
				// Check to see that the item is not deleted
				if( pEntry->IsDeleted() == false )
				{
					UINT nErrArg = 0;
					// Determine if this is an exposed method or a
					// dynamically added property/method
					if( pEntry->UseTypeInfo() == false )
					{
						// Call the Zeroth member of the dispatch object
						// This should be the only function contained in
						// the dispatch object
						hr = vtDisp.pdispVal->Invoke(0,IID_NULL,lcid,wFlags,
							pDispParams,pvtResult,pExcepInfo,&nErrArg);
					}
					else
					{
						// This should be forwarded to the TypeInfo
						hr = S_FALSE;
					}
				}
				else
				{
					// Can't invoke one that was deleted
					hr = DISP_E_MEMBERNOTFOUND;
				}
			}
		}
		return hr;
	}

protected:
// These two methods allow for access to the members via name
// Add entries into your IDL if you want this functionality

#ifndef IDISPATCHEX_NO_TYPEINFO
	/***************************************************************************
	* Function:	IDispatchExImpl::Get()
	* Author:	Joe Graf
	* Date:		2/17/99
	* Args:		<BSTR> bstrVarName - the name of the variable to fetch
	*			<VARIANT*> pvtVar - the object that will get the data
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Retrieves the variable by name. This is an optional method of
	*			getting properties.
	***************************************************************************/

	STDMETHOD(Get)(BSTR bstrVarName,VARIANT* pvtVar)
	{
		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		// Serialize access, since another thread might try to modify members at
		// the same time we are accessing them
		CScopeSingleLock sl(&m_csAccessSync);
		HRESULT hr = S_OK;
		// Get the entry of the specified named var
		CDynamicDispatchEntry* pEntry = GetEntryByName(bstrVarName);
		if( pEntry != NULL )
		{
			// Check to see if this is an ITypeInfo member
			if( pEntry->UseTypeInfo() == false )
			{
				// Copy the variant
				hr = pEntry->GetVar(pvtVar);
			}
			else
			{
				// Did you call TypeInfoInit() first?
				_ASSERTE(m_pTypeInfo != NULL);
				// Build the params that we want to use
				DISPPARAMS dispparams = { NULL,NULL,0,0 };
				// Forward to the type info
				hr = m_pTypeInfo->Invoke(this,pEntry->GetDispID(),
					DISPATCH_PROPERTYGET | DISPATCH_METHOD,&dispparams,pvtVar,
					NULL,NULL);
			}
		}
		else
		{
			// Clear the variable
			hr = VariantClear(pvtVar);
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::Set()
	* Author:	Joe Graf
	* Date:		2/17/99
	* Args:		<BSTR> bstrVarName - the name of the variable to fetch
	*			<VARIANT> vtVar - the object that will get the data
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Sets the variable by name. This is an optional method of
	*			setting properties. NOTE: This must be declared as propertyput
	*			in the IDL file or the typeinfo won't process it.
	***************************************************************************/

	STDMETHOD(Set)(BSTR bstrVarName,VARIANT vtVar)
	{
		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		// Serialize access, since another thread might try to modify members at
		// the same time we are accessing them
		CScopeSingleLock sl(&m_csAccessSync);
		HRESULT hr = E_INVALIDARG;
		// Get the entry of the specified named var
		CDynamicDispatchEntry* pEntry = GetEntryByName(bstrVarName);
		if( pEntry != NULL )
		{
			// Check to see if this is an ITypeInfo member
			if( pEntry->UseTypeInfo() == false )
			{
				// Copy the variant
				hr = pEntry->SetVar(&vtVar);
			}
			else
			{
				// Did you call TypeInfoInit() first?
				_ASSERTE(m_pTypeInfo != NULL);
				// Named var of type put
				DISPID dispid = DISPID_PROPERTYPUT;
				// Build the params that we want to use
				DISPPARAMS dispparams = { &vtVar,&dispid,1,1 };
				// Forward to the type info
				hr = m_pTypeInfo->Invoke(this,pEntry->GetDispID(),
					DISPATCH_PROPERTYPUT | DISPATCH_PROPERTYPUTREF,&dispparams,
					NULL,NULL,NULL);
			}
		}
		return hr;
	}
#endif

public:

#ifndef IDISPATCHEX_NO_TYPEINFO
// This is the class factory that calls the TypeInfoInit() method
DECLARE_CLASSFACTORY_DISPATCHEX(DERIVED_CLASS)

	// Default constructor
	IDispatchExImpl() : m_dispidNext(DISPID_START), m_pTypeInfo(NULL) {}
#else
	// Default constructor
	IDispatchExImpl() : m_dispidNext(DISPID_START) {}
#endif

	/***************************************************************************
	* Function:	IDispatchExImpl::~IDispatchExImpl()
	* Author:	Joe Graf
	* Date:		2/13/99
	* Args:		None
	* Returns:	None
	* Purpose:	Deletes any allocated dispatch entry objects
	***************************************************************************/

	virtual ~IDispatchExImpl()
	{
		// Need to iterate through the dispid map and delete the Entry pointers
		UPOSITION pos = m_mapDispIDToEntry.GetStartPosition();
		// While there are items in the map
		while( pos != NULL )
		{
			// Holds each map entry
			DISPID dispid = 0;
			CDynamicDispatchEntry* pEntry = NULL;
			// Get the item from the map
			m_mapDispIDToEntry.GetNextAssoc(pos,dispid,pEntry);
			_ASSERTE(AfxIsValidAddress(pEntry,sizeof(CDynamicDispatchEntry)));
			// Delete the item
			delete pEntry;
		}
#ifndef IDISPATCHEX_NO_TYPEINFO
		// Release the ITypeInfo object if alloced
		if( m_pTypeInfo != NULL )
		{
			m_pTypeInfo->Release();
		}
#endif
	}

// IDispatch
	/***************************************************************************
	* Function:	IDispatchExImpl::GetTypeInfoCount()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<UINT*> pnTypeInfoCount - always set to one
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Tells the caller the number of type info interfaces that we
	*			support.
	***************************************************************************/

	STDMETHOD(GetTypeInfoCount)(UINT* pnTypeInfoCount)
	{
		// This call is inherently thread safe so no synchronization is needed
		// Validate the pointer passed in
		HRESULT hr = AfxIsValidAddress(pnTypeInfoCount,sizeof(UINT)) == TRUE ? S_OK : E_INVALIDARG;
		if( SUCCEEDED(hr) )
		{
#ifndef IDISPATCHEX_NO_TYPEINFO
			// We only return type info for the derived class
			*pnTypeInfoCount = 1;
#else
			// The use wants no type info support
			*pnTypeInfoCount = 0;
#endif
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetTypeInfo()
	* Author:	Joe Graf
	* Date:		2/15/99
	* Args:		<UINT> nTypeInfoIndex - must be 1
	*			<LCID> ignored
	*			<ITypeInfo**> ppTypeInfo - the pointer that gets a copy of ours
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	This method returns a pointer to the derived class' type info
	***************************************************************************/

	STDMETHOD(GetTypeInfo)(UINT nTypeInfoIndex,LCID,ITypeInfo** ppTypeInfo)
	{
		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		// This call is inherently thread safe so no synchronization is needed
		// Validate the pointer passed in
		HRESULT hr = AfxIsValidAddress(ppTypeInfo,sizeof(ITypeInfo*)) == TRUE &&
			nTypeInfoIndex == 1 ? S_OK : E_INVALIDARG;
		if( SUCCEEDED(hr) )
		{
#ifndef IDISPATCHEX_NO_TYPEINFO
			// Did you call TypeInfoInit() first?
			_ASSERTE(m_pTypeInfo != NULL);
			// Copy our interface pointer
			*ppTypeInfo = m_pTypeInfo;
			// AddRef on behalf of the caller
			m_pTypeInfo->AddRef();
#else
			// Not supported
			*ppTypeInfo = NULL;
#endif
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetIDsOfNames()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<REFIID> reserved, so ignored
	*			<LPOLESTR*> szNameArray - the array of names to map to DISPIDs
	*			<UINT> nNames - the number of names in the array
	*			<LCID> lcid - the locale indicator to look up the names for
	*			<DISPID*> parrDispIDs - the array of DISPIDs to fill in
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Determines the DISPID of each named property or method.
	***************************************************************************/

	STDMETHOD(GetIDsOfNames)(REFIID,LPOLESTR* szNameArray,UINT nNames,LCID,
		DISPID* parrDispIDs)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);
		// Validate the pointers passed in
		HRESULT hr = AfxIsValidAddress(szNameArray,
			sizeof(LPOLESTR) * nNames) == TRUE && AfxIsValidAddress(szNameArray,
			sizeof(DISPID) * nNames) == TRUE ? S_OK : E_INVALIDARG;
		if( SUCCEEDED(hr) )
		{
			// Loop through the arrays letting GetDispID do the work
			for( UINT nIndex = 0; nIndex < nNames && SUCCEEDED(hr);
				nIndex++ )
			{
				// Pass the call on to GetDispID
				// Since the caller is using IDispatch to get the ID and
				// not the Ex version to get it, assume case insensitivity
				hr = GetDispID(szNameArray[nIndex],fdexNameCaseInsensitive,
					&parrDispIDs[nIndex]);
			}
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::Invoke()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DISPID> dispid - the dispid of the entry to invoke
	*			<REFIID> ignored
	*			<LCID> lcid - the locale id
	*			<WORD> wFlags - calling flags
	*			<DISPPARAMS*> pDispParams - the dispparams of the method
	*			<VARIANT*> pvtResult - the variant holding the result
	*			<EXCEPINFO*> pExcepInfo - the exception info pointer
	*			<UINT*> pnArgErr - the number of arguments that had errors
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Calls the method of a dispatch id
	***************************************************************************/

	STDMETHOD(Invoke)(DISPID dispIdMember,REFIID,LCID lcid,WORD wFlags,
		DISPPARAMS* pDispParams,VARIANT* pVarResult,EXCEPINFO* pExcepInfo,
		UINT* pnArgErr)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);
		// Zero the returned errors if requested
		if( pnArgErr != NULL )
		{
			// Zero it out
			*pnArgErr = 0;
		}
		return InvokeEx(dispIdMember,lcid,wFlags,pDispParams,pVarResult,
			pExcepInfo,NULL);
	}

// IDispatchEx
	/***************************************************************************
	* Function:	IDispatchExImpl::DeleteMemberByDispID()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DISPID> dispid - the dispid to delete from the dynamic props
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Deletes a property/method from the dynamic list
	***************************************************************************/

	STDMETHOD(DeleteMemberByDispID)(DISPID dispid)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);

		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		HRESULT hr = S_OK;
		CDynamicDispatchEntry* pEntry = NULL;
		// Get the pointer to the entry
		if( m_mapDispIDToEntry.Lookup(dispid,pEntry) == TRUE )
		{
			_ASSERTE(AfxIsValidAddress(pEntry,sizeof(CDynamicDispatchEntry)));
			// Mark the object as deleted
			hr = pEntry->MarkDeleted();
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::DeleteMemberByName()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<BSTR> bstrName - the name of the entry to delete
	*			<DWORD> dwGrfDex - the flags describing the comparison operator
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Deletes a property/method from the dynamic list
	***************************************************************************/

	STDMETHOD(DeleteMemberByName)(BSTR bstrName,DWORD dwGrfDex)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);

		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		HRESULT hr = S_OK;
		// Get a pointer to the entry if valid
		CDynamicDispatchEntry* pEntry = GetEntryByName(bstrName,dwGrfDex);
		if( pEntry != NULL )
		{
			_ASSERTE(AfxIsValidAddress(pEntry,sizeof(CDynamicDispatchEntry)));
			// Mark as deleted
			hr = pEntry->MarkDeleted();
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetDispID()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<BSTR> bstrName - the name of the entry to get the dispid of
	*			<DWORD> dwGrfDex - the flags describing the comparison operator
	*			<DISPID*> pDispID - the out param of the dispid
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Returns the DISPID of a given named entry
	***************************************************************************/

	STDMETHOD(GetDispID)(BSTR bstrName,DWORD dwGrfDex,
		DISPID* pDispID)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);

		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		// Validate the pointers passed in
		HRESULT hr = AfxIsValidAddress(pDispID,sizeof(DISPID)) == TRUE ?
			S_OK : E_INVALIDARG;
		if( SUCCEEDED(hr) )
		{
			// Find the entry that corresponds to this name
			CDynamicDispatchEntry* pEntry = GetEntryByName(bstrName,dwGrfDex);
			if( pEntry != NULL )
			{
				_ASSERTE(AfxIsValidAddress(pEntry,
					sizeof(CDynamicDispatchEntry)));
				// Check to see if this item was deleted or if it should be
				// added if it was
				if( pEntry->IsDeleted() == false ||
					(pEntry->IsDeleted() == true && dwGrfDex & fdexNameEnsure) )
				{
					// Set the out parameter to this entry's dispid
					*pDispID = pEntry->GetDispID();
				}
				else
				{
					// Tell the caller that the member was deleted
					hr = DISP_E_UNKNOWNNAME;
				}
			}
			else
			{
				// The entry was not found, so we need to check if we are
				// supposed to automatically add it
				if( dwGrfDex & fdexNameEnsure )
				{
					// We need to create a new entry
					hr = CreateNewEntry(bstrName,pDispID,CComVariant());
				}
				else
				{
					// The item was not found
					hr = DISP_E_UNKNOWNNAME;
				}
			}
		}
		// If can't find the dispid set the outgoing var
		if( FAILED(hr) )
		{
			// Set the dispid to Unknown
			*pDispID = DISPID_UNKNOWN;
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetMemberName()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DISPID> dispid - the dispid to get the name of
	*			<BSTR*> pbstrName - receives the name of the entry
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Returns the name of a given dispid entry
	***************************************************************************/

	STDMETHOD(GetMemberName)(DISPID dispid,BSTR* pbstrName)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);

		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		// Validate the pointers passed in
		HRESULT hr = AfxIsValidAddress(pbstrName,sizeof(BSTR)) == TRUE ?
			S_OK : E_INVALIDARG;
		if( SUCCEEDED(hr) )
		{
			// Find the entry that corresponds to this name
			CDynamicDispatchEntry* pEntry = NULL;
			// Look up the entry in the dispid map
			if( m_mapDispIDToEntry.Lookup(dispid,pEntry) == TRUE )
			{
				_ASSERTE(AfxIsValidAddress(pEntry,
					sizeof(CDynamicDispatchEntry)));
				// Make sure this was not deleted
				if( pEntry->IsDeleted() == false )
				{
					// Copy the name of the entry
					*pbstrName = pEntry->GetName().Copy();
				}
				else
				{
					// Indicate that we do not know what is going on
					hr = DISP_E_MEMBERNOTFOUND;
				}
			}
			else
			{
				// Indicate that we do not know what is going on
				hr = DISP_E_MEMBERNOTFOUND;
			}
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetMemberProperties()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DISPID> dispid - the dispid to get the name of
	*			<DWORD> dwGrfDex - the fetch flags (ignored)
	*			<BSTR*> pbstrName - receives the name of the entry
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Returns the name of a given dispid entry
	***************************************************************************/

	STDMETHOD(GetMemberProperties)(DISPID dispid,DWORD,DWORD* pdwGrfDex)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);

		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		// Validate the pointers passed in
		HRESULT hr = AfxIsValidAddress(pdwGrfDex,sizeof(DWORD)) == TRUE ?
			S_OK : E_INVALIDARG;
		if( SUCCEEDED(hr) )
		{
			// Set the flags to "can do everything"
			*pdwGrfDex = grfdexPropCanAll;
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetNameSpaceParent()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<IUnknown**> ignored
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Not supported
	***************************************************************************/

	STDMETHOD(GetNameSpaceParent)(IUnknown**)
	{
		return E_NOTIMPL;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::GetNextDispID()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DWORD> dwGrfDex - the flags to fetch with
	*			<DISPID> dispid - the dispid the caller is currently on
	*			<DISPID*> pdispid - the out parameter for the next ID
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Returns the next dispid in the list
	***************************************************************************/

	STDMETHOD(GetNextDispID)(DWORD dwGrfDex,DISPID dispid,DISPID* pDispID)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time
		CScopeSingleLock sl(&m_csAccessSync);

		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		// Validate the pointers passed in
		HRESULT hr = AfxIsValidAddress(pDispID,sizeof(DISPID)) == TRUE ?
			S_OK : E_INVALIDARG;
		if( SUCCEEDED(hr) )
		{
			// We need to check for the request of the first DISPID
			if( dispid != DISPID_STARTENUM )
			{
				// Get the next dispid
				hr = GetNextDispID(dispid,pDispID);
			}
			else
			{
				// Find the first dispid in the map
				hr = GetStartDispID(pDispID);
			}
		}
		return hr;
	}

	/***************************************************************************
	* Function:	IDispatchExImpl::InvokeEx()
	* Author:	Joe Graf
	* Date:		2/12/99
	* Args:		<DISPID> dispid - the dispid of the entry to invoke
	*			<LCID> lcid - the locale id
	*			<WORD> wFlags - calling flags
	*			<DISPPARAMS*> pDispParams - the dispparams of the method
	*			<VARIANT*> pvtResult - the variant holding the result
	*			<EXCEPINFO*> pExcepInfo - the exception info pointer
	*			<IServiceProvider*> ignored
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Processes the callers request to execute a method. This can be
	*			a property get/put or a function call.
	***************************************************************************/

	STDMETHOD(InvokeEx)(DISPID dispid,LCID lcid,WORD wFlags,
		DISPPARAMS* pDispParams,VARIANT* pvtResult,EXCEPINFO* pExcepInfo,
		IServiceProvider*)
	{
		// Serialize access, since another thread might try to modify members at
		// the same time we are accessing them
		CScopeSingleLock sl(&m_csAccessSync);

		if (m_pTypeInfo == NULL)
		{
			TypeInfoInit();
		}

		HRESULT hr = E_FAIL;
		// Check to see if we are retrieving a property
		if( wFlags & DISPATCH_PROPERTYGET )
		{
			// Validate that they passed in a valid variant for results
			// and have no parameters assigned to the "Get"
			if( pvtResult != NULL &&
				(pDispParams == NULL || pDispParams->cArgs == 0) )
			{
				// Do the "Get" with the specified ID
				hr = GetVariantByDispID(dispid,pvtResult);
			}
			else
			{
				// They passed in bogus stuff
				hr = E_INVALIDARG;
			}
		}
		// Check to see if we are setting a property
		if( wFlags & (DISPATCH_PROPERTYPUT | DISPATCH_PROPERTYPUTREF) )
		{
			// Validate that params passed in
			if( pDispParams != NULL && (pDispParams->cArgs == 1 ||
				(pDispParams->cNamedArgs == 1 &&
				pDispParams->rgdispidNamedArgs[0] == DISPID_PROPERTYPUT)) )
			{
				// Set the new value to the variant in the first index
				hr = SetVariantByDispID(dispid,&pDispParams->rgvarg[0]);
			}
			else
			{
				// They parameter is not optional
				hr = DISP_E_PARAMNOTOPTIONAL;
			}
		}
		// Finally, check to see if we are invoking a function
		if( wFlags & DISPATCH_METHOD )
		{
			// Inovke the LPDISPATCH hou
			hr = InvokeByDispID(dispid,lcid,wFlags,pDispParams,pvtResult,
				pExcepInfo);
		}
		// Check to see if this dispid is in the typeinfo object
		if( hr == S_FALSE )
		{
#ifndef IDISPATCHEX_NO_TYPEINFO
			// Did you call TypeInfoInit() first?
			_ASSERTE(m_pTypeInfo != NULL);
			UINT nErrArg = 0;
			// Forward to the type info
			hr = m_pTypeInfo->Invoke(this,dispid,wFlags,
				pDispParams,pvtResult,pExcepInfo,&nErrArg);
#else
			// Something in the dynamic dispatch entries has gone very wrong
			_ASSERT(false);
#endif
		}
		return hr;
	}

#ifndef IDISPATCHEX_NO_TYPEINFO
	/***************************************************************************
	* Function:	IDispatchExImpl::TypeInfoInit()
	* Author:	Joe Graf
	* Date:		2/15/99
	* Args:		None
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Any derived class may have some automation compatible methods
	*			that it wants exposed. This method loads the type lib of the
	*			derived class and adds those members to the dispatch maps.
	***************************************************************************/

	HRESULT TypeInfoInit(void)
	{
		HRESULT hr = S_OK;
		// Only do this if our pointer is invalid
		if( m_pTypeInfo == NULL )
		{
			// Temporary lib object
			ITypeLib* pTypeLib = NULL;
			// Read the registered type library information for the COM
			// object that this implementation lives in
			hr = LoadRegTypeLib(*BASE_LIBID,wMajor,wMinor,LOCALE_SYSTEM_DEFAULT,
				&pTypeLib);
			if( SUCCEEDED(hr) )
			{
				// Get the type info for the specific interface
				hr = pTypeLib->GetTypeInfoOfGuid(*BASE_IID,&m_pTypeInfo);
				if( SUCCEEDED(hr) )
				{
					// We need to determine which dispids the interface already
					// uses to prevent collisions when dynamic properties are
					// added to the object
					hr = AddTypeInfoDispIDs();
				}
				// Let go of the type lib object
				pTypeLib->Release();
			}
		}
		return hr;
	}
#endif
#endif	// _WINDOWS
};

#endif