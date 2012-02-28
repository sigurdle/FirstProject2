#pragma once

#include "PDObjectImpl.h"
#include "PDStory.h"

class CStoryFlowContext;
class CTextContext;

//class CPDStory;

template <class IBase> class ATL_NO_VTABLE CPDObjectTextImpl : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDObjectImpl<IBase>
{
public:
	CPDObjectTextImpl()
	{
		m_story = NULL;
		m_previousTextThread = NULL;
		m_nextTextThread = NULL;

		m_startContainer = NULL;
		m_startOffset = -1;

		m_endContainer = NULL;
		m_endOffset = -1;

		m_overflow = VARIANT_FALSE;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CPDObjectImpl<IBase>::FinalConstruct();
		if (FAILED(hr)) return hr;

		return S_OK;
	}

	void FinalRelease()
	{
		CPDObjectImpl<IBase>::FinalRelease();
	}

	VARIANT_BOOL m_overflow;

	PointD m_threadPtLeft;
	PointD m_threadPtRight;

	CComObject<CPDStory>* m_story;
	CPDObjectTextImpl<IPDObjectText>* m_previousTextThread;
	CPDObjectTextImpl<IPDObjectText>* m_nextTextThread;

// The range of the story that this textobject displayes
	ILDOMNode* m_startContainer;
	long m_startOffset;

	ILDOMNode* m_endContainer;
	long m_endOffset;

	virtual CTextContext* SetupBox(CStoryFlowContext* pSC) = 0;
	virtual void SetdownBox(CTextContext* pC) = 0;
	virtual void Clear() = 0;

// IPDObjectText
public:
	STDMETHODIMP get_story(IPDStory **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_story;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP put_story(IPDStory *newVal)
	{
		m_story = static_cast<CComObject<CPDStory>*>(newVal);
		return S_OK;
	}

	STDMETHODIMP get_previousTextThread(IPDObjectText **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_previousTextThread;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP put_previousTextThread(IPDObjectText *newVal)
	{
		m_previousTextThread = static_cast<CPDObjectTextImpl<IPDObjectText>*>(newVal);
		return S_OK;
	}

	STDMETHODIMP get_nextTextThread(IPDObjectText **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_nextTextThread;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP put_nextTextThread(IPDObjectText *newVal)
	{
		m_nextTextThread = static_cast<CPDObjectTextImpl<IPDObjectText>*>(newVal);
		return S_OK;
	}

	STDMETHODIMP get_overflow(VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_overflow;
		return S_OK;
	}

#if 0
	STDMETHODIMP saveAsXML(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node, BOOL saveId)
	{
		HRESULT hr;
		hr = CPDObjectImpl<IBase>::saveAsXML(document, node, saveId);
		if (FAILED(hr)) return hr;

		return S_OK;
	}

	STDMETHODIMP loadXML(/*[in]*/ IDOMNode* node)
	{
		HRESULT hr;
		hr = CPDObjectImpl<IBase>::loadXML(node);
		if (FAILED(hr)) return hr;

		return S_OK;
	}
#endif

	STDMETHODIMP get_threadPtIn(PointD *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_threadPtLeft;
		return S_OK;
	}

	STDMETHODIMP get_threadPtOut(PointD *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_threadPtRight;
		return S_OK;
	}
};
