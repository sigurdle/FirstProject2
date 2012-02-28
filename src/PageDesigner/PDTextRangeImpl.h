#pragma once

class CPDStory;

HRESULT MoveCursorLeft(ILDOMNode* startContainer, long startOffset, ILDOMNode* *container, long* offset);
HRESULT MoveCursorRight(ILDOMNode* startContainer, long startOffset, ILDOMNode* *container, long* offset);

template <class IBase> class CPDTextRangeImpl : public IBase
{
public:
	CPDTextRangeImpl()
	{
		m_story = NULL;
	}

	CPDStory* m_story;
	CComPtr<ILDOMRange> m_domrange;

	STDMETHODIMP GetDOMRange(ILDOMRange **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_domrange;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP GetStory(IPDStory **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_story;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(IsCollapsed)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return m_domrange->get_collapsed(pVal);
	}
	STDMETHOD(Delete)(/*[in]*/ long Unit, /*[in]*/ long Count, /*[out,retval]*/ long* pDelta)
	{
		if (Count == 0)	// Delete all characters in range
		{
			m_domrange->deleteContents();
		}
		else
		{
			CComPtr<ILDOMNode> m_curContainer;
			long m_curOffset;

			m_domrange->get_startContainer(&m_curContainer);
			m_domrange->get_startOffset(&m_curOffset);

			if (Count > 0)	// Delete
			{
				CComPtr<ILDOMNode> container;
				long offset;
				if (MoveCursorRight(m_curContainer, m_curOffset, &container, &offset) == S_OK)
				{
					m_domrange->setEnd(container, offset);
					m_domrange->deleteContents();

					/*
					m_curContainer = container;
					m_curOffset = offset;
					m_initContainer = container;
					m_initOffset = offset;
					*/
				}
			}
			else	// Backspace
			{
				CComPtr<ILDOMNode> container;
				long offset;
				if (MoveCursorLeft(m_curContainer, m_curOffset, &container, &offset) == S_OK)
				{
					m_domrange->setStart(container, offset);
					m_domrange->deleteContents();
	/*
					m_range->Set(
					m_curContainer = container;
					m_curOffset = offset;
					m_initContainer = container;
					m_initOffset = offset;
					*/
				}
			}
		}

		return S_OK;
	}
};
