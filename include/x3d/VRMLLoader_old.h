// VRMLLoader.h : Declaration of the CVRMLLoader

#ifndef __VRMLLOADER_H_
#define __VRMLLOADER_H_

#include "resource.h"       // main symbols

#define LXMLEXT __declspec(dllimport)

#include "../LXML/LXML.h"
#include "../LXML/LXML2.h"

class CVRMLLoader :
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CVRMLLoader, &CLSID_VRMLLoader>,
//	public IVRMLLoader,
	public LMedia::BaseFilterImpl
{
public:
	class CInputPin : 
		public LMedia::BasePinImpl
		//public ILMemInputPin
	{
	public:
		CTOR CInputPin() : BasePinImpl(LMedia::LPINDIR_INPUT)
		{
//			m_pFilter = NULL;
		}

//		CVRMLLoader* m_pFilter;

		virtual HRESULT CheckMediaType(const LMedia::MediaType& mt)
		{
			ASSERT(0);
			return E_FAIL;
		}

		inline CVRMLLoader* GetFilter() const
		{
			return (CVRMLLoader*)m_pFilter;
		}

		HRESULT ReceiveConnection(LMedia::IPin* pConnector, LMedia::MediaType* pmt);
	};


	CTOR CVRMLLoader()
	{
		m_pInputPin = new CInputPin;
		m_pInputPin->m_pFilter = this;
		AddPin(m_pInputPin);
	}

	~CVRMLLoader()
	{
	}

	LMedia::ByteStreamWrapper* m_stream;
	CInputPin* m_pInputPin;

/*
DECLARE_REGISTRY_RESOURCEID(IDR_VRMLLOADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVRMLLoader)
	COM_INTERFACE_ENTRY(IVRMLLoader)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
//	COM_INTERFACE_ENTRY(ILMediaSeeking)
//	COM_INTERFACE_ENTRY(ILBasicVideo)
END_COM_MAP()
*/

	CLX3DScene* Load(const sysstring& pathName);
};

#endif //__VRMLLOADER_H_
