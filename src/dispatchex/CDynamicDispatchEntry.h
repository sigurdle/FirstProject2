// Copyright © 1998-99 the e-comm group, inc.
//
// CDynamicDispatchEntry.h: This class is used to house a dynamically
// added entry to an IDispatchEx interface implementation.
//
// $Author: Graf $
// $Date: 3/18/99 8:06a $
// $Revision: 2 $
// $Archive: /e-comm group/Components/TestDispatchEx/CDynamicDispatchEntry.h $

#ifndef _DYNAMIC_DISPATCH_ENTITY_H
#define _DYNAMIC_DISPATCH_ENTITY_H


class CDynamicDispatchEntry
{
	// For determing the type and state of the entry
	bool m_bUseTypeInfo;
	bool m_bIsDeleted;
	// Holds the data at this entry
	CComVariant m_vtVar;
	// This is the name of the entry as the script engine sees it
	CComBSTR m_bstrName;
	// The dispid of the entry as returned to the engine
	DISPID m_dispid;

public:
	// Default constructor
	CDynamicDispatchEntry() : m_bUseTypeInfo(false), m_bIsDeleted(true),
		m_dispid(-1) {}
	// An empty entry (same as deleted)
	CDynamicDispatchEntry(BSTR bstrName,DISPID dispid) : m_bUseTypeInfo(false),
		 m_bIsDeleted(true), m_dispid(dispid), m_bstrName(bstrName) {}
	// A completely specified entry
	CDynamicDispatchEntry(BSTR bstrName,DISPID dispid,VARIANT vtVar,
		bool bIsFunc = false) : m_bUseTypeInfo(bIsFunc), m_bIsDeleted(false),
		m_dispid(dispid), m_bstrName(bstrName), m_vtVar(vtVar) {}

	// Default destructor
	virtual ~CDynamicDispatchEntry() {}

// Attributes
	inline CComBSTR& GetName(void) { return m_bstrName; }
	inline DISPID GetDispID(void) { return m_dispid; }
	inline bool IsDeleted(void) { return m_bIsDeleted; }
	inline bool UseTypeInfo(void) { return m_bUseTypeInfo; }
	inline HRESULT GetVar(VARIANT* pvtDest)
	{
		// Copy our variant into the dest
		return VariantCopy(pvtDest,&m_vtVar);
	}
	inline HRESULT SetVar(VARIANT* pvtSrc)
	{
		// If we are setting this prop, it must not be deleted
		m_bIsDeleted = false;
		// Clear out whatever was already there
		HRESULT hr = VariantClear(&m_vtVar);
		if( SUCCEEDED(hr) )
		{
			// Copy their variant into our variant
			hr = VariantCopy(&m_vtVar,pvtSrc);
		}
		return hr;
	}

// Operations
	inline HRESULT MarkDeleted(void)
	{
		HRESULT hr = S_FALSE;
		// Determine if this is a function provided by an
		// ancestor dispatch class
		if( m_bUseTypeInfo == false )
		{
			// Clear the member
			m_vtVar.Clear();
			// Set the state to deleted
			m_bIsDeleted = true;
			// Indicate success
			hr = S_OK;
		}
		return hr;
	}
};

#endif