// LXSLProcessor.cpp : Implementation of CLXSLProcessor
#include "stdafx.h"
#include "LXML.h"
#include "LXSLProcessor.h"

#include "LXSLTemplate.h"

/////////////////////////////////////////////////////////////////////////////
// CLXSLProcessor

STDMETHODIMP CLXSLProcessor::get_input(VARIANT *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_input;
	return S_OK;
}

STDMETHODIMP CLXSLProcessor::put_input(VARIANT newVal)
{
	m_input = newVal;
	return S_OK;
}

STDMETHODIMP CLXSLProcessor::get_ownerTemplate(ILXSLTemplate **pVal)
{
	if (pVal == NULL) return E_POINTER;
#if 0
	(*pVal = m_ownerTemplate)->AddRef();
#endif
	return E_FAIL;
	return S_OK;
}

STDMETHODIMP CLXSLProcessor::get_output(VARIANT *pVal)
{
#if 0
	return m_msprocessor->get_output(pVal);
#endif
	return E_FAIL;
}

STDMETHODIMP CLXSLProcessor::put_output(VARIANT newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

#if 0
MSXML2::IXMLDOMNodePtr Build(MSXML2::IXMLDOMDocument2Ptr msdocument, ILDOMNode* node)
{
	LDOMNodeType nodeType;
	node->get_nodeType(&nodeType);

	if (nodeType == LNODE_DOCUMENT)
	{
		MSXML2::IXMLDOMDocument2Ptr msdocument2 = msdocument;//(L"Msxml2.FreeThreadedDOMDocument.4.0");
		//msdocument2->async = VARIANT_FALSE;

		CComPtr<ILDOMNode> child;
		node->get_firstChild(&child);
		while (child)
		{
			MSXML2::IXMLDOMNodePtr mschild = Build(msdocument2, child);
			if (mschild)
			{
				msdocument2->appendChild(mschild);
			}
			else
				;//ASSERT(0);

			CComPtr<ILDOMNode> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}

		return msdocument2;
	}
	else if (nodeType == LNODE_PROCESSING_INSTRUCTION)
	{
		return NULL;

		CComQIPtr<ILDOMProcessingInstruction> pi = node;
		BSTR btarget;
		pi->get_target(&btarget);
		_bstr_t target = _bstr_t(btarget, false);

		BSTR bdata;
		pi->get_data(&bdata);
		_bstr_t data = _bstr_t(bdata, false);

		MSXML2::IXMLDOMProcessingInstructionPtr mspi = msdocument->createProcessingInstruction(target, data);

		return mspi;
	}
	else if (nodeType == LNODE_ELEMENT)
	{
		CComQIPtr<ILDOMElement> element = node;

		BSTR bnamespaceURI;
		element->get_namespaceURI(&bnamespaceURI);
		_bstr_t namespaceURI = _bstr_t(bnamespaceURI, false);

		BSTR btagName;
		element->get_localName(&btagName);	// Try local name first
		if (SysStringLen(btagName) == 0)
		{
			SysFreeString(btagName);
			element->get_tagName(&btagName);	// Then try full qualified name
		}
		_bstr_t tagName = _bstr_t(btagName, false);

		MSXML2::IXMLDOMElementPtr mselement = msdocument->createNode(_variant_t((long)1/*MSXML2::NODE_ELEMENT*/), tagName, namespaceURI);

		CComPtr<ILDOMNode> child;
		node->get_firstChild(&child);
		while (child)
		{
			MSXML2::IXMLDOMNodePtr mschild = Build(msdocument, child);
			if (mschild)
			{
				mselement->appendChild(mschild);
			}
			else
				;//ASSERT(0);

			CComPtr<ILDOMNode> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}

		CComPtr<ILDOMNamedNodeMap> attributes;
		element->get_attributes(&attributes);

		long nattributes;
		attributes->get_length(&nattributes);
		for (int i = 0; i < nattributes; i++)
		{
			CComPtr<ILDOMAttr> attr;
			attributes->item(i, (ILDOMNode**)&attr);

			MSXML2::IXMLDOMAttributePtr msattr = Build(msdocument, attr);

			mselement->attributes->setNamedItem(msattr);
		}

		return mselement;
	}
	else if (nodeType == LNODE_ATTRIBUTE)
	{
		CComQIPtr<ILDOMAttr> attr = node;

		BSTR bname;
		attr->get_name(&bname);
		_bstr_t name = _bstr_t(bname, false);

		BSTR bvalue;
		attr->get_value(&bvalue);
		_bstr_t value = _bstr_t(bvalue, false);

		MSXML2::IXMLDOMAttributePtr msattr = msdocument->createAttribute(name);
		msattr->value = value;

		return msattr;
	}
	else if (nodeType == LNODE_TEXT)
	{
		CComQIPtr<ILDOMText> text = node;
		BSTR bdata;
		text->get_data(&bdata);
		_bstr_t data = _bstr_t(bdata, false);

		MSXML2::IXMLDOMTextPtr mstext = msdocument->createTextNode(data);

		return mstext;
	}
	else if (nodeType == LNODE_COMMENT)
	{
		return NULL;

		CComQIPtr<ILDOMComment> comment = node;
		BSTR bdata;
		comment->get_data(&bdata);
		_bstr_t data = _bstr_t(bdata, false);

		MSXML2::IXMLDOMCommentPtr mscomment = msdocument->createComment(data);

		return mscomment;
	}

	ASSERT(0);
	return NULL;
}
#endif

STDMETHODIMP CLXSLProcessor::transform(bool *pDone)
{
#if 0
	ASSERT(pDone);
	if (pDone == NULL) return E_POINTER;

	CComQIPtr<ILDOMNode> inputNode = m_input;
	if (inputNode)
	{
		MSXML2::IXMLDOMDocument2Ptr msdocument(L"Msxml2.DOMDocument.4.0");
		msdocument->async = VARIANT_FALSE;

		MSXML2::IXMLDOMNodePtr msinputNode = Build(msdocument, inputNode);
		if (msinputNode)
		{
		//	::MessageBox(NULL, msinputNode->xml, "", MB_OK);

			m_msprocessor->input = _variant_t((IDispatch*)msinputNode);
			bool done = m_msprocessor->transform();

			*pDone = done;
		}
	}
#endif
	return S_OK;
}
