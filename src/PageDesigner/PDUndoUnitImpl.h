#pragma once

class ATL_NO_VTABLE CPDUndoUnitImpl : public IOleUndoUnit
{
public:
	CPDUndoUnitImpl()
	{
		m_bRedo = false;
	}

	bool m_bRedo;

public:
	STDMETHOD(GetUnitType)(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID)
	{
		*pClsid = GUID_NULL;//CLSID_WEUndoMoveObjects;
		*plID = 0;

		return S_OK;
	}

	STDMETHOD(OnNextAdd)(void)
	{
		return S_OK;
	}
};
