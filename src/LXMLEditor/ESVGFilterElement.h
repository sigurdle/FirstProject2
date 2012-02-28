#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CFilterGraphView;

//class CFilterPrimitiveElement;

class CFilterPrimitiveElement : public CESVGElementImpl
{
public:

	long m_type;
	LDraw::RectD m_rect;
	System::StringW* m_name;

	CFilterPrimitiveElement()
	{
		m_rect = LDraw::RectD(0, 0, 92, 22);
	}

// IESVGFilterPrimitiveElement
	ErrorCode get_rect(LDraw::RectD* pVal)
	{
		*pVal = m_rect;
		return Success;
	}

	ErrorCode put_rect(LDraw::RectD newVal)
	{
		m_rect = newVal;
		return Success;
	}

	ErrorCode get_type(long* pVal)
	{
		*pVal = m_type;
		return Success;
	}
};

class CStdFilterPrimitiveElement :
	public CFilterPrimitiveElement
{
public:
	CStdFilterPrimitiveElement()
	{
		m_type = -1;
	}

	System::StringW* m_result;

	System::StringW* get_name()
	{
		return m_name;
	}

	System::StringW* get_resultString()
	{
		return m_result;
	}

	ErrorCode GetInPinCount(long* pVal)
	{
		*pVal = 0;
		return Success;
	}

	CFilterPrimitiveElement* GetInPin(long n)
	{
		ASSERT(0);
		return NULL;
	}

	void SetInPinString(/*[in]*/long npin, /*[in]*/ System::StringW* stringVal)
	{
		ASSERT(0);
	}

	void ClearInPin(/*[in]*/long npin)
	{
		ASSERT(0);
	}
};

class CESVGFilterElement : public CESVGElementImpl
{
public:
	/*
	class CChildren : public C2Obj
	{
	public:
		~CChildren()
		{
			m_childList.RemoveAll(); // Don't delete children in ~C2Obj
		}
	};
	*/

	CESVGFilterElement();

	CFilterGraphView* m_effectsUI;

	CStdFilterPrimitiveElement*	m_cItems[6];
	Array<CFilterPrimitiveElement*> m_items;

	void ShowUI();
	void BuildItems();
};

class CSVGFEElement :
	public CFilterPrimitiveElement
{
public:
	CSVGFEElement()
	{
		m_type = 1;
	}

	System::StringW* get_name()
	{
	ASSERT(0);
#if 0
		if (pVal == NULL) return E_POINTER;
		//*pVal = m_name.copy();

		CComQIPtr<ILSVGElement> element = m_domElement;

		CComBSTR nodeName;
		element->get_nodeName(&nodeName);

		*pVal = nodeName.Detach();
#endif
		return NULL;
	}

	System::StringW* get_resultString()
	{
		ASSERT(0);
#if 0
		if (pVal == NULL) return E_POINTER;

		CComQIPtr<ILSVGElement> element = m_domElement;

		CComBSTR result;
		element->getAttribute(L"result", &result);

		*pVal = result.Detach();
#endif
		return NULL;
	}

	long GetInPinCount()
	{
		ASSERT(0);
#if 0
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		if (m_domElement)
		{
			BSTR btagName;
			m_domElement->get_nodeName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"feMerge"))
			{
				CComPtr<ILDOMNodeList> childNodes;
				m_domElement->get_childNodes(&childNodes);

				long nchildNodes;
				childNodes->get_length(&nchildNodes);

				*pVal = nchildNodes + 1;
			}
			else if (!wcscmp(tagName, L"feComposite"))
			{
				*pVal = 2;
			}
			else if (!wcscmp(tagName, L"feTurbulence"))
			{
				*pVal = 0;
			}
			else
			{
				*pVal = 1;
			}
		}
		else
			*pVal = 0;
#endif
		return 0;
	}

	ErrorCode SetInPinString(/*[in]*/long npin, System::StringW* stringVal)
	{
		ASSERT(0);
#if 0
		CComQIPtr<ILDOMElement> domElement = m_domElement;

		if (domElement)
		{
			// TODO here
			BSTR btagName;
			domElement->get_nodeName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"feMerge"))
			{
				CComPtr<ILDOMNodeList> childNodes;
				domElement->get_childNodes(&childNodes);

				long nchildNodes;
				childNodes->get_length(&nchildNodes);

				if (npin < nchildNodes)
				{
					CComPtr<ILDOMNode> node;
					childNodes->item(npin, &node);

					CComQIPtr<ILDOMElement> mergeNode = node;
					mergeNode->setAttribute(L"in", stringVal);
				}
				else
				{
					CComPtr<ILDOMDocument> domDocument;
					domElement->get_ownerDocument(&domDocument);

					CComPtr<ILDOMElement> mergeNode;
					domDocument->createElementNS(L"http://www.w3.org/2000/svg", L"feMergeNode", &mergeNode);
					if (mergeNode)
					{
						mergeNode->setAttribute(L"in", stringVal);
						domElement->appendChild(mergeNode, NULL);
					}
				}
			}
			else
			{
				BSTR strin;
				if (npin == 0)
					strin = L"in";
				else
					strin = L"in2";

				domElement->setAttribute(strin, stringVal);
			}
		}
#endif
		return Success;
	}

	ErrorCode ClearInPin(/*[in]*/long npin)
	{
		ASSERT(0);
#if 0
		CComQIPtr<ILDOMElement> domElement = m_domElement;

		BSTR btagName;
		domElement->get_nodeName(&btagName);
		_bstr_t tagName = _bstr_t(btagName, false);

		if (!wcscmp(tagName, L"feMerge"))
		{
			CComPtr<ILDOMNodeList> childNodes;
			domElement->get_childNodes(&childNodes);

			long nchildNodes;
			childNodes->get_length(&nchildNodes);

			if (npin < nchildNodes)
			{
				CComPtr<ILDOMNode> node;
				childNodes->item(npin, &node);
			
				domElement->removeChild(node, NULL);
			}
		}
		else
		{
			BSTR strin;
			if (npin == 0)
				strin = L"in";
			else
				strin = L"in2";

			domElement->removeAttribute(strin);
		}
#endif
		return Success;
	}

#if 0
	ErrorCode SetInPin(/*[in]*/long i, /*[in]*/ IESVGFilterPrimitiveElement* newVal)
	{

		return S_OK;
	}
#endif

	ErrorCode GetInPin(/*[in]*/long npin, /*[out,retval]*/ CFilterPrimitiveElement* *pVal)
	{
		ASSERT(0);
#if 0
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		IEElement* parentNode = get_parentNode();

		CESVGFilterElement* pFilter = static_cast<CESVGFilterElement*>(parentNode);

		LSVG::SVGElement* domElement = m_domElement;

		sysstring tagName = domElement->get_nodeName();

		BSTR binstr;

		if (!wcscmp(tagName, L"feMerge"))
		{
			CComPtr<ILDOMNodeList> childNodes;
			domElement->get_childNodes(&childNodes);

			long nchildNodes;
			childNodes->get_length(&nchildNodes);
			if (npin < nchildNodes)
			{
				CComPtr<ILDOMNode> node;
				childNodes->item(npin, &node);

				CComQIPtr<ILDOMElement> mergeNode = node;
				mergeNode->getAttribute(L"in", &binstr);
			}
			else
			{
				binstr = NULL;
			}
		}
		else
		{
			if (npin == 0)
				domElement->getAttribute(L"in", &binstr);
			else
				domElement->getAttribute(L"in2", &binstr);
		}

		_bstr_t instr = _bstr_t(binstr, false);

		if (instr.length() == 0) return NULL;

		if (!wcscmp(instr, L"SourceGraphic"))
		{
			(*pVal = pFilter->m_cItems[0])->AddRef();
		}
		else if (!wcscmp(instr, L"SourceAlpha"))
		{
			(*pVal = pFilter->m_cItems[1])->AddRef();
		}
		else if (!wcscmp(instr, L"BackgroundGraphic"))
		{
			(*pVal = pFilter->m_cItems[2])->AddRef();
		}
		else if (!wcscmp(instr, L"BackgroundAlpha"))
		{
			(*pVal = pFilter->m_cItems[3])->AddRef();
		}
		else
		{
			CComPtr<ILDOMNode> prevNode;
			domElement->get_previousSibling(&prevNode);

			while (prevNode != NULL)
			{
				CComQIPtr<ILSVGElement> prevElement = prevNode;
				if (prevElement)
				{
					CComPtr<IEElement> eElement;
					m_pDocument->GetEElementFromDOMElement(prevElement, &eElement);

					CFilterPrimitiveElement* pPrev = dynamic_cast<CFilterPrimitiveElement*>(eElement);
					if (pPrev)
					{
						CComBSTR result;
						prevElement->getAttribute(L"result", &result);

						if (result.Length() > 0)
						{
							if (!wcscmp(instr, result))
							{
								(*pVal = pPrev)->AddRef();
								return S_OK;
							}
						}
					}
				}

				CComPtr<ILDOMNode> previousSibling;
				prevNode->get_previousSibling(&previousSibling);
				prevNode = previousSibling;
			}

			*pVal = NULL;
			return S_OK;
		}
#endif
		return Success;
	}
};

}	// LXmlEdit
}
