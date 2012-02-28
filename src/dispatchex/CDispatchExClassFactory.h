// Copyright © 1998-99 the e-comm group, inc.
//
// CDispatchExClassFactory.h: This file contains the class definition and
// implementation of an ATL derived class factory used with implementations
// of the IDispatcheExImpl class. When it creates a new object it calls the
// TypeInfoInit() method on it so that the type information can be pre-loaded.
//
// $Author: Graf $
// $Date: 3/11/99 11:52p $
// $Revision: 2 $
// $Archive: /e-comm group/Components/TestDispatchEx/CDispatchExClassFactory.h $

#ifndef _DISPATCH_EX_CLASS_FACTORY_H
#define _DISPATCH_EX_CLASS_FACTORY_H

template <class CLASS_TO_CREATE>
class CComDispatchExClassFactory : public CComClassFactory
{
public:
// IClassFactory

	/***************************************************************************
	* Function:	CComDispatchExClassFactory::CreateInstance()
	* Author:	Joe Graf
	* Date:		2/15/99
	* Args:		<LPUNKNOWN> pUnkOuter - not supported
	*			<REFIID> riid - the interface that the caller wants
	*			<void**> ppvObj - the pointer that recieves the interface ptr
	* Returns:	<HRESULT> Standard COM codes
	* Purpose:	Creates a new IDispatchEx derived object and calls the
	*			TypeInfoInit() method on it before returning the pointer
	***************************************************************************/

	STDMETHOD(CreateInstance)(LPUNKNOWN pUnkOuter,REFIID riid,void** ppvObj)
	{
		HRESULT hr = S_OK;
		if( ppvObj != NULL )
		{
			*ppvObj = NULL;
			// Aggregation is not supported for IDispatchEx
			if( pUnkOuter == NULL )
			{
				CComObject<CLASS_TO_CREATE>* pObject = NULL;
				// There is not a match so we need to create a new one
				hr = CComObject<CLASS_TO_CREATE>::CreateInstance(&pObject);
				if( SUCCEEDED(hr) )
				{
#ifndef IDISPATCHEX_NO_TYPEINFO
					// Before going any further we need to let the
					// IDispatchExImpl class load any derived class'
					// type infomation
					hr = pObject->TypeInfoInit();
#endif
					if( SUCCEEDED(hr) )
					{
						// Now we need to get the correct interface pointer
						hr = pObject->QueryInterface(riid,ppvObj);
					}
				}
				else
				{
					// Failed to create
					hr = E_FAIL;
				}
			}
			else
			{
				// Tell them no
				hr = CLASS_E_NOAGGREGATION;
			}
		}
		else
		{
			// Bogus pointer
			hr = E_POINTER;
		}
		return hr;
	}
};

// The macro for class definition
#define DECLARE_CLASSFACTORY_DISPATCHEX(obj) DECLARE_CLASSFACTORY_EX(CComDispatchExClassFactory<obj>)

#endif

