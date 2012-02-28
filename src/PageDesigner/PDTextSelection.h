#pragma once

#include "PDTextRangeImpl.h"

class ATL_NO_VTABLE CPDTextSelection :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDTextRangeImpl<IPDTextSelection>
{
public:
	CPDTextSelection()
	{
		m_curContainer = NULL;
		m_curOffset = 0;

		m_initContainer = NULL;
		m_initOffset = 0;
	}

	int FinalConstruct()
	{
//		HRESULT hr;

//		hr = m_domrange.CoCreateInstance(CLSID_Range);
//		if (FAILED(hr)) return hr;

		return S_OK;
	}

	ILDOMNode* m_curContainer;
	long m_curOffset;

	ILDOMNode* m_initContainer;
	long m_initOffset;

	HRESULT ExtendIt(ILDOMNode* container, long offset, int bShift);

	HRESULT MoveCursorDown(/*[in]*/ ILDOMNode* curContainer, /*[in]*/ long curOffset, /*[out]*/ ILDOMNode* *container, /*[out]*/ long* offset);
	HRESULT MoveCursorUp(/*[in]*/ ILDOMNode* curContainer, /*[in]*/ long curOffset, /*[out]*/ ILDOMNode* *container, /*[out]*/ long* offset);
	HRESULT MoveCursorEnd(/*[in]*/ ILDOMNode* curContainer, /*[in]*/ long curOffset, /*[out]*/ ILDOMNode* *container, /*[out]*/ long* offset);
	HRESULT MoveCursorHome(/*[in]*/ ILDOMNode* curContainer, /*[in]*/ long curOffset, /*[out]*/ ILDOMNode* *container, /*[out]*/ long* offset);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDTextSelection)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDTextRange)
	COM_INTERFACE_ENTRY(IPDTextSelection)
END_COM_MAP()

public:
	STDMETHOD(TypeText)(/*[in]*/ BSTR bstr);
	STDMETHOD(MoveDOM)(/*[in]*/ ILDOMNode* node, /*[in]*/ long offset);
	STDMETHOD(Set)(/*[in]*/ ILDOMNode* node, /*[in]*/ long offset);
	STDMETHOD(MoveDown)(/*[in]*/ long Unit, /*[in]*/ long Count, /*[in]*/ long Extend, /*[out,retval]*/ long* pDelta);
	STDMETHOD(MoveUp)(/*[in]*/ long Unit, /*[in]*/ long Count, /*[in]*/ long Extend, /*[out,retval]*/ long* pDelta);
	STDMETHOD(MoveLeft)(/*[in]*/ long Unit, /*[in]*/ long Count, /*[in]*/ long Extend, /*[out,retval]*/ long* pDelta);
	STDMETHOD(MoveRight)(/*[in]*/ long Unit, /*[in]*/ long Count, /*[in]*/ long Extend, /*[out,retval]*/ long* pDelta);
	STDMETHOD(HomeKey)(/*[in]*/ long Unit, /*[in]*/ long Extend, /*[out,retval]*/ long* pDelta);
	STDMETHOD(EndKey)(/*[in]*/ long Unit, /*[in]*/ long Extend, /*[out,retval]*/ long* pDelta);
	STDMETHOD(Delete)(/*[in]*/ long Unit, /*[in]*/ long Count, /*[out,retval]*/ long* pDelta)
	{
		CPDTextRangeImpl<IPDTextSelection>::Delete(Unit, Count, pDelta);

		CComPtr<ILDOMNode> startContainer;
		long startOffset;
		m_domrange->get_startContainer(&startContainer);
		m_domrange->get_startOffset(&startOffset);

		m_curContainer = startContainer;
		m_curOffset = startOffset;
		m_initContainer = startContainer;
		m_initOffset = startOffset;

		return S_OK;
	}
};
