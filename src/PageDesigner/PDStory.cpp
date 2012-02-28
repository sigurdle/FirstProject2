#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDStory.h"

#include "ObjectMap.h"
#include "PDDocument.h"
#include "PDLayer.h"
#include "PDObjectGroup.h"
#include "PDContentText.h"	// TODO remove

#include "PDTextRange.h"
#include "PDTextSelection.h"

double ConvertUserUnitToSpecifiedValue(double value, short unitType);

///////////////////////////
// CElement

void CElement::Build()
{
	CComQIPtr<ILDOMElement> element = m_node;

	m_fontFamily = GetAttribute(L"font-family");
	m_fontSize = atof(GetAttribute(L"font-size"));

	m_strokeWidth = atof(GetAttribute(L"stroke-width"));

	CUString fillColor = (BSTR)GetAttribute(L"fill-color");
	int r=0,g=0,b=0;
	sscanf(fillColor, "rgb(%d,%d,%d)", &r, &g, &b);
	m_fillColor = Gdiplus::Color(r,g,b);

	CComPtr<ILDOMNode> child;
	element->get_firstChild(&child);
	while (child)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_TEXT)
		{
			CNode* pText = new CNode(child);

			pText->m_parent = this;
			m_children.Add(pText);
		}
		else if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> subelement = child;

			CElement* pElement = new CElement(subelement);

			pElement->m_story = m_story;
			pElement->m_parent = this;
			m_children.Add(pElement);

			pElement->Build();
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}

_bstr_t CElement::GetAttribute(BSTR attName)
{
	CComQIPtr<ILDOMElement> element = m_node;

	BSTR battvalue;
	element->getAttribute(attName, &battvalue);
	if (battvalue)
	{
		return _bstr_t(battvalue, false);
	}

// Try parent
	if (m_parent)
		return m_parent->GetAttribute(attName);

	return L"";
}

void CElement::SetupFont(CTextContext* pC)
{
	m_pOldFont = pC->m_pFont;
	pC->m_pFont = new Gdiplus::Font(m_fontFamily, m_fontSize);

	m_pOldFillBrush = pC->m_pFillBrush;
	pC->m_pFillBrush = new Gdiplus::SolidBrush(m_fillColor);

	m_pOldStrokePen = pC->m_pStrokePen;
	if (m_strokeWidth > 0)
		pC->m_pStrokePen = new Gdiplus::Pen(m_strokeColor, m_strokeWidth);
	else
		pC->m_pStrokePen = NULL;
}

void CElement::SetdownFont(CTextContext* pC)
{
	delete pC->m_pFont;
	pC->m_pFont = m_pOldFont;
	m_pOldFont = NULL;

	delete pC->m_pFillBrush;
	pC->m_pFillBrush = m_pOldFillBrush;
	m_pOldFillBrush = NULL;

	delete pC->m_pStrokePen;
	pC->m_pStrokePen = m_pOldStrokePen;
	m_pOldStrokePen = NULL;
}

/*
BOOL CElement::DistributeElement(CTextContext* pC)
{
	CComQIPtr<IDOMElement> element = m_node;

	SetupFont(pC);

	CTextContext* pC2 = pC->SetupElement(this);

	for (int i = 0; i < m_children.GetSize(); i++)
	{
		LDOMNodeType nodeType;
		m_children[i]->m_node->get_nodeType(&nodeType);

		if (nodeType == NODE_ELEMENT)
		{
			CElement* pElement = (CElement*)m_children[i];
			CComQIPtr<IDOMElement> element = pElement->m_node;

			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"object"))
			{
				BSTR bstrguid;
				element->getAttribute(L"guid", &bstrguid);
				if (bstrguid)
				{
					GUID guid;
					CLSIDFromString(bstrguid, &guid);
					SysFreeString(bstrguid);

					CComPtr<IPDObject> object;
					m_story->getInlineObjectById(guid, &object);
					if (object)
					{
						BOOL bPlaced;
						bPlaced = pC2->PlaceObject(object);
						if (!bPlaced)
						{
							return FALSE;
						}
					}
				}
			}
			else
			{
				if (!pElement->DistributeElement(pC2))
					return FALSE;
			}
		}
		else if (nodeType == NODE_TEXT)
		{
			CNode* pNode = (CNode*)m_children[i];

			CComQIPtr<IDOMText> textnode = pNode->m_node;

			BSTR bdata;
			textnode->get_data(&bdata);
			_bstr_t data = _bstr_t(bdata, false);

			BSTR p = data;
			int len = data.length();

			int i = 0;
			while (i < len)
			{
				// Place each space
				while (i < len && iswspace(p[i]))
				{
					WCHAR worddata[2] = {p[i], 0};

					BOOL bPlaced = pC2->PlaceWord(pNode, i, worddata); 
					if (!bPlaced)
					{
						return FALSE;
					}

					i++;
				}

				if (i < len)
				{
					// Collect a word and place it
					_bstr_t worddata = L"";
					int start = i;

					while (i < len && !iswspace(p[i]))
					{
						WCHAR c2[2] = {p[i], 0};
						worddata += c2;
						i++;
					}

					BOOL bPlaced;
					bPlaced = pC2->PlaceWord(pNode, start, worddata);
					if (!bPlaced)
					{
						return FALSE;
					}
				}
			}
		}
	}

	pC->SetdownElement(this, pC2);

	SetdownFont(pC);

	return TRUE;
}
*/

BOOL CStoryFlowContext::PlaceWord(CTextContext* pC, CNode* pNode, int i, _bstr_t worddata)
{
	BOOL bPlaced = pC->PlaceWord(pNode, i, worddata);
	if (!bPlaced)
	{
		// The next textbox will begin placing at this position within the DOM document
		m_hitNode = pNode->m_node;
		m_hitOffset = i;
	}
	else
	{
	// Placed the word in textbox

		// If this is the first placed word, set the values for start that the textbox displays
		if (m_pContentText->m_startContainer == NULL)
		{
			m_pContentText->m_startContainer = pNode->m_node;
			m_pContentText->m_startOffset = i;
		}

	// Set new values for end that the textbox displays
		m_pContentText->m_endContainer = pNode->m_node;
		m_pContentText->m_endOffset = i+worddata.length();
	}

	return bPlaced;
}

BOOL CStoryFlowContext::PlaceTextNode(CTextContext* pC2, CNode* pNode)
{
	CComQIPtr<ILDOMText> textnode = pNode->m_node;

	BSTR bdata;
	textnode->get_data(&bdata);
	_bstr_t data = _bstr_t(bdata, false);

	BSTR p = data;
	int len = data.length();
	int i = 0;

	if (pNode->m_node == m_hitNode)
	{
		i += m_hitOffset;

		m_hitNode = NULL;	// Place everything from here on
		m_hitOffset = NULL;
	}
	else if (m_hitNode)
	{
		// We haven't reached where to start placing yet
		return TRUE;
	}

	while (i < len)
	{
		// Place each space
		while (i < len && iswspace(p[i]))
		{
			WCHAR worddata[2] = {p[i], 0};

			BOOL bPlaced = PlaceWord(pC2, pNode, i, worddata); 
			if (!bPlaced)
			{
				return FALSE;
			}

			i++;
		}

		if (i < len)
		{
			// Collect a word and place it
			_bstr_t worddata = L"";
			int start = i;

			while (i < len && !iswspace(p[i]))
			{
				WCHAR c2[2] = {p[i], 0};
				worddata += c2;
				i++;
			}

			BOOL bPlaced;
			bPlaced = PlaceWord(pC2, pNode, start, worddata);
			if (!bPlaced)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CStoryFlowContext::DistributeElement(CElement* pElement, CTextContext* pC)
{
	CComQIPtr<ILDOMElement> element = pElement->m_node;

	pElement->SetupFont(pC);

	CTextContext* pC2 = pC->SetupElement(pElement);

	for (int i = 0; i < pElement->m_children.GetSize(); i++)
	{
		LDOMNodeType nodeType;
		pElement->m_children[i]->m_node->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CElement* pElement2 = (CElement*)pElement->m_children[i];
			CComQIPtr<ILDOMElement> element = pElement2->m_node;

			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"object"))
			{
				/*
				BSTR bstrguid;
				element->getAttribute(L"guid", &bstrguid);
				if (bstrguid)
				{
					GUID guid;
					CLSIDFromString(bstrguid, &guid);
					SysFreeString(bstrguid);

					CComPtr<IPDObject> object;
					m_story->getInlineObjectById(guid, &object);
					if (object)
					{
						BOOL bPlaced;
						bPlaced = pC2->PlaceObject(object);
						if (!bPlaced)
						{
							return FALSE;
						}
					}
				}
				*/
			}
			else
			{
				if (!DistributeElement(pElement2, pC2))
					return FALSE;
			}
		}
		else if (nodeType == LNODE_TEXT)
		{
			CNode* pNode = (CNode*)pElement->m_children[i];

			if (!PlaceTextNode(pC2, pNode))
				return FALSE;
		}
	}

	pC->SetdownElement(pElement, pC2);

	pElement->SetdownFont(pC);

	return TRUE;
}


/////////////////////////
// CPDStory

void CPDStory::DistributeStory()
{
	if (m_pElement)
	{
		CPDObjectTextImpl<IPDObjectText>* pThread;

	// Clear all text threads
		pThread = m_firstTextThread;
		while (pThread)
		{
			pThread->Clear();
			pThread = pThread->m_nextTextThread;
		}

	// If any of the text threads aren't yet placed on a spread, then we skip
	// distributing this story alltogether
		BOOL bAllThreadsOnSpread = TRUE;
		pThread = m_firstTextThread;
		while (pThread)
		{
			if (pThread->m_spread == NULL)
			{
				bAllThreadsOnSpread = FALSE;
				break;
			}

			pThread = pThread->m_nextTextThread;
		}

	// We're ready to distribute the story
		if (bAllThreadsOnSpread && m_firstTextThread)
		{
			HDC hDC = CreateCompatibleDC(NULL);

			CStoryFlowContext* pSC = new CStoryFlowContext;
			pSC->m_pContentText = m_firstTextThread;	// We start in the first text box

			BOOL bPlaced;
			do
			{
				pSC->m_pContentText->m_overflow = VARIANT_FALSE;

				pSC->m_pContentText->m_startContainer = NULL;
				pSC->m_pContentText->m_startOffset = -1;
				pSC->m_pContentText->m_endContainer = NULL;
				pSC->m_pContentText->m_endOffset = -1;

				CTextContext* pC = pSC->m_pContentText->SetupBox(pSC);
				pC->m_pGraphics = new Gdiplus::Graphics(hDC);

				bPlaced = pSC->DistributeElement(m_pElement, pC);

				delete pC->m_pGraphics;
				pSC->m_pContentText->SetdownBox(pC);

				if (!bPlaced)
				{
					pSC->m_pContentText->m_overflow = VARIANT_TRUE;

					// Try next text box
					pSC->m_pContentText = pSC->m_pContentText->m_nextTextThread;
				}

				if (pSC->m_pContentText == NULL)
					break;
			}
			while (!bPlaced);

			DeleteDC(hDC);

			delete pSC;
		}
	}
}

int CPDStory::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CObjectMap>::CreateInstance(&m_textContents);
	if (FAILED(hr)) return hr;
	m_textContents->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_inlineObjects);
	if (FAILED(hr)) return hr;
	m_inlineObjects->AddRef();

#if 0
	hr = m_textdocumentcnt.CoCreateInstance(CLSID_DOMDocumentContainer);
	if (FAILED(hr)) return hr;

	IDispEventImpl<1, CPDStory, &DIID__IDOMDocumentContainerEvents, &LIBID_SVGLib, 1, 0>::DispEventAdvise(m_textdocumentcnt);
#endif
	m_textdocument.CoCreateInstance(CLSID_LDOMDocument);

	{
		VARIANT_BOOL bloaded;

		m_textdocument->loadXML(
			L"<text font-family=\"Arial\" font-size=\"12\"><p tabs=\"20 0 0;30 1 0;50 2 0;60 3 0;90 0 0\" margin-left=\"0\">Dette er paragraf 1, <style fill-color=\"rgb(255,0,0)\">og dette </style>er en test <style font-family=\"Times New Roman\" font-size=\"6\">på noe morsomt</style>, og dette er paragraf 1, og dette er litt mere sånn at det blir noe tekst her</p></text>", &bloaded);
/*
		m_textdocumentcnt->loadXML(
			L"<text font-family=\"Arial\" font-size=\"18\">"
				L"<p>Dette er<style font-family=\"Arial\" font-size=\"12\">paragraf 1</style>, para graf 1, para graf 1</p>"
				L"<p>Paragraf 2, Paragraf 2</p>"
			L"</text>", &bloaded);
*/
		ATLASSERT(bloaded);

		DistributeContentsSpreads();
	}

	hr = ::CoCreateGuid(&m_uniqId);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CPDStory::FinalRelease()
{
	if (m_textContents)
	{
		m_textContents->Release();
		m_textContents = NULL;
	}

#if 0
	if (m_textdocumentcnt)
	{
		IDispEventImpl<1, CPDStory, &DIID__IDOMDocumentContainerEvents, &LIBID_SVGLib, 1, 0>::DispEventUnadvise(m_textdocumentcnt);
		m_textdocumentcnt.Release();
	}
#endif

	if (m_inlineObjects)
	{
		m_inlineObjects->Release();
		m_inlineObjects = NULL;
	}
}

STDMETHODIMP CPDStory::get_textDocument(ILDOMDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_textdocument;
	(*pVal)->AddRef();

#if 0
	CComPtr<IDOMDocument> textdocument;
	m_textdocumentcnt->get_document(&textdocument);

	*pVal = textdocument;
	(*pVal)->AddRef();
#endif

	return S_OK;
}

STDMETHODIMP CPDStory::put_textDocument(ILDOMDocument *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDStory::get_textContents(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_textContents;
	(*pVal)->AddRef();
	return S_OK;
}

void CPDStory::DistributeContentsSpreads()
{
	if (m_pElement)
	{
		delete m_pElement;
		m_pElement = NULL;
	}

	ATLASSERT(m_textdocument != NULL);
/*
	CComPtr<IDOMDocument> textdocument;
	m_textdocumentcnt->get_document(&textdocument);
*/
	if (m_textdocument)
	{
		CComPtr<ILDOMElement> documentElement;
		m_textdocument->get_documentElement(&documentElement);

		if (documentElement)
		{
			m_pElement = new CElement(documentElement);
			m_pElement->m_story = this;
			m_pElement->Build();
		}
	}

	DistributeStory();	// ??

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	/*
	if (m_document)	// TODO, document listens to all stories
	{
		m_document->FireOnChanged(NOTIFY_MODIFY, GetUnknown(), IID_IPDStory, DISPID_UNKNOWN);
	}
	*/
}

//////////

#if 0
HRESULT __stdcall CPDStory::cnt_insertedNode(IDOMNode* node)
{
	DistributeContentsSpreads();
	return S_OK;
}

HRESULT __stdcall CPDStory::cnt_beforeRemovedNode(IDOMNode* node)
{
	DistributeContentsSpreads();
	return S_OK;
}

HRESULT __stdcall CPDStory::cnt_afterRemovedNode(IDOMNode* node)
{
	DistributeContentsSpreads();
	return S_OK;
}

HRESULT __stdcall CPDStory::cnt_changedAttribute(IDOMNode* node, BSTR attrName, short changeType, BSTR prevValue)
{
	DistributeContentsSpreads();
	return S_OK;
}

HRESULT __stdcall CPDStory::cnt_changedTextContentNode(IDOMNode* node, BSTR oldvalue)
{
	DistributeContentsSpreads();
	return S_OK;
}

HRESULT __stdcall CPDStory::cnt_setDocument(IDOMDocument* document)
{
	DistributeContentsSpreads();
	return S_OK;
}

HRESULT __stdcall CPDStory::cnt_beforesetDocument()
{
	DistributeContentsSpreads();
	return S_OK;
}
#endif

HRESULT CPDStory::insertNode(IPDObjectText* node, IPDObjectText* before)
{
	if (node == NULL) return E_INVALIDARG;

	CPDObjectTextImpl<IPDObjectText>* pNode = static_cast<CPDObjectTextImpl<IPDObjectText>*>(node);

	node->AddRef();

// Remove first from any previous gradient
	if (pNode->m_story)
	{
		// TODO
		;//pStop->m_parent->removeStop(pStop);
	}

	CPDObjectTextImpl<IPDObjectText>* pBefore = static_cast<CPDObjectTextImpl<IPDObjectText>*>(before);

	CPDObjectTextImpl<IPDObjectText>* pAfter;

	if (pBefore)
		pAfter = pBefore->m_previousTextThread;
	else
		pAfter = m_lastTextThread;

	pNode->m_nextTextThread = pBefore;
	pNode->m_previousTextThread = pAfter;

	if (pAfter == NULL)
		m_firstTextThread = pNode;
	else
		pAfter->m_nextTextThread = pNode;

	if (pBefore == NULL)
		m_lastTextThread = pNode;
	else
		pBefore->m_previousTextThread = pNode;

	pNode->m_story = static_cast<CComObject<CPDStory>*>(this);

	if (pBefore)
	{
		for (int i = 0; i < m_textContents->m_items.GetSize(); i++)
		{
			if (m_textContents->m_items[i] == before)
			{
				m_textContents->m_items.InsertAt(i, node);
				break;
			}
		}
	}
	else
	{
		m_textContents->m_items.Add(node);
	}

	if (m_document)
	{
		m_document->DistributeStories();
	}

	return S_OK;
}

STDMETHODIMP CPDStory::appendTextThread(IPDObjectText *node)
{
	return insertNode(node, NULL);
}

STDMETHODIMP CPDStory::insertTextThreadBefore(IPDObjectText *node, IPDObjectText *before)
{
	return insertNode(node, before);
}

STDMETHODIMP CPDStory::removeTextThread(IPDObjectText *object)
{
	if (object == NULL)
	{
		ATLASSERT(0);
		return E_POINTER;
	}

	for (int i = 0; i < m_textContents->m_items.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_textContents->m_items[i], object))
		{
			CComPtr<IPDObjectText> previousSibling;
			object->get_previousTextThread(&previousSibling);

			CComPtr<IPDObjectText> nextSibling;
			object->get_nextTextThread(&nextSibling);

			if (previousSibling != NULL)
				previousSibling->put_nextTextThread(nextSibling);
			else
				m_firstTextThread = static_cast<CPDObjectTextImpl<IPDObjectText>*>(nextSibling.p);

			if (nextSibling != NULL)
				nextSibling->put_previousTextThread(previousSibling);
			else
				m_lastTextThread = static_cast<CPDObjectTextImpl<IPDObjectText>*>(previousSibling.p);

			object->put_previousTextThread(NULL);
			object->put_nextTextThread(NULL);
			object->put_story(NULL);

/*			{
				CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);
				//pObject->m_parent = NULL;
				pObject->detachFromSpread();
			}
*/
			m_textContents->m_items.RemoveAt(i);
/*
			{
				CComQIPtr<INotifySend> cp = object;
				cp->Unadvise(static_cast<T*>(this));
			}
*/
			//FireOnChanged(NOTIFY_REMOVE, object, DISPID_UNKNOWN);	?????

			int refcount = object->Release();

			if (m_document)
			{
				m_document->DistributeStories();
			}

			return S_OK;
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}

STDMETHODIMP CPDStory::get_firstTextThread(IPDObjectText **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_firstTextThread;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDStory::get_lastTextThread(IPDObjectText **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_lastTextThread;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDStory::get_inlineObjects(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_inlineObjects;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDStory::appendInlineObject(IPDObject *object)
{
	if (object == NULL) return E_INVALIDARG;

	CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);

	ATLASSERT(pObject->m_uniqId != GUID_NULL);

	object->AddRef();
	m_inlineObjects->m_items.Add(object);

	return S_OK;
}

STDMETHODIMP CPDStory::getInlineObjectById(GUID guid, IPDObject **pVal)
{
	if (pVal == NULL) return E_POINTER;

	ATLASSERT(guid != GUID_NULL);

	for (int i = 0; i < m_inlineObjects->m_items.GetSize(); i++)
	{
		CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_inlineObjects->m_items[i]);

		if (pObject->m_uniqId == guid)
		{
			*pVal = pObject;
			(*pVal)->AddRef();
			return S_OK;
		}
	}

	*pVal = NULL;

	return S_OK;
}

#if 0
IDOMElement* FindByTagName(IDOMElement* parent, BSTR tagName, BOOL bDeep = TRUE);

STDMETHODIMP CPDStory::loadXML(/*[in]*/ IDOMNode* node)
{
	CComQIPtr<IDOMElement> element = node;
	if (element)
	{
		{
			BSTR bstrguid;
			element->getAttribute(L"guid", &bstrguid);
			if (bstrguid)
			{
				HRESULT hr = CLSIDFromString(bstrguid, &m_uniqId);
				SysFreeString(bstrguid);

				if (FAILED(hr)) return hr;
			}
			else
			{
				HRESULT hr = ::CoCreateGuid(&m_uniqId);

				if (FAILED(hr)) return hr;
			}
		}

		ATLASSERT(m_textdocumentcnt != NULL);

		CComPtr<IDOMDocument> textdocument;
		m_textdocumentcnt->get_document(&textdocument);
		ATLASSERT(textdocument);

		CComPtr<IDOMElement> textElement = FindByTagName(element, L"text", FALSE);
		if (textElement)
		{
			CComPtr<IDOMElement> documentElement;
			textElement->cloneNode(VARIANT_TRUE, (IDOMNode**)&documentElement);

			textdocument->put_documentElement(documentElement);
		}

		return S_OK;
	}
	else
		return E_FAIL;
}

STDMETHODIMP CPDStory::saveAsXML(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node, BOOL saveId)
{
	CComQIPtr<IDOMElement> element = node;
	if (element)
	{
		//if (saveId)
		{
			LPOLESTR guidstr;
			StringFromCLSID(m_uniqId, &guidstr);
			element->setAttribute(L"guid", guidstr);
			CoTaskMemFree(guidstr);
		}

		// Text Threads
		{
			CComPtr<IDOMElement> elementThreads;
			document->createElement(L"threads", &elementThreads);
			if (elementThreads)
			{
				for (int i = 0; i < m_textContents->m_items.GetSize(); i++)
				{
					CPDObjectTextImpl<IPDObjectText>* pThread = static_cast<CPDObjectTextImpl<IPDObjectText>*>((IPDObjectText*)m_textContents->m_items[i]);
					CComPtr<IDOMElement> elementThread;
					document->createElement(L"thread", &elementThread);
					if (elementThread)
					{
						LPOLESTR guidstr;
						StringFromCLSID(pThread->m_uniqId, &guidstr);
						elementThread->setAttribute(L"guid", guidstr);
						CoTaskMemFree(guidstr);

						elementThreads->appendChild(elementThread, NULL);
					}
				}

				element->appendChild(elementThreads, NULL);
			}
		}

		ATLASSERT(m_textdocumentcnt != NULL);

		CComPtr<IDOMDocument> textdocument;
		m_textdocumentcnt->get_document(&textdocument);

		if (textdocument)
		{
			CComPtr<IDOMElement> documentElement;
			textdocument->get_documentElement(&documentElement);

			if (documentElement)
			{
				CComPtr<IDOMElement> textElement;
				documentElement->cloneNode(VARIANT_TRUE, (IDOMNode**)&textElement);

				element->appendChild(textElement, NULL);
			}
		}

		return S_OK;
	}
	else
		return E_FAIL;
}
#endif

class CTab
{
public:
	float m_pos;
	long m_align;
	long m_leader;

	CTab()
	{
		m_align = tomAlignLeft;
		m_leader = 0;
	}
};

class ATL_NO_VTABLE CPDTextPara : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDTextPara
{
public:
	CPDTextPara()
	{
		m_alignment = tomUndefined;
		m_firstLineIndent = tomUndefined;
		m_leftIndent = tomUndefined;
		m_rightIndent = tomUndefined;

		m_range.Release();
	}

	CArray<CTab,CTab> m_tabs;
	long m_alignment;
	float m_firstLineIndent;
	float m_leftIndent;
	float m_rightIndent;

	void ParseTabString(BSTR str);
	_bstr_t MakeTabString();

	CComPtr<IPDTextRange> m_range;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDTextPara)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDTextPara)
END_COM_MAP()

public:
	STDMETHOD(AddTabEx)(/*[in]*/ float tbPos, /*[in]*/ long tbAlign, /*[in]*/ long tbLeader, /*[out,retval]*/ long *pVal);
	STDMETHOD(get_dropCapChars)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_dropCapChars)(/*[in]*/ long newVal);
	STDMETHOD(get_dropCapLines)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_dropCapLines)(/*[in]*/ long newVal);
	STDMETHOD(SetAlignment)(/*[in]*/ long newVal);
	STDMETHOD(SetTabPos)(/*[in]*/ long iTab, /*[in]*/ float tbPos, /*[out,retval]*/ long* pVal);
	STDMETHOD(GetRange)(/*[out,retval]*/ IPDTextRange* *pVal);
	STDMETHOD(GetLeftIndent)(/*[out,retval]*/ float *pVal);
	STDMETHOD(GetRightIndent)(/*[out,retval]*/ float* pVal);
	STDMETHOD(SetRightIndent)(/*[in]*/ float newVal);
	STDMETHOD(SetIndents)(/*[in]*/ float first, /*[in]*/ float left, /*[in]*/ float right);
	STDMETHOD(GetFirstLineIndent)(/*[out,retval]*/ float* pVal);
	STDMETHOD(GetTab)(/*[in]*/ long iTab, /*[out]*/ float* ptbPos, /*[out]*/ long* ptbAlign, /*[out]*/ long* ptbLeader);
	STDMETHOD(GetTabCount)(/*[out,retval]*/ long* pVal);
	STDMETHOD(DeleteTab)(/*[in]*/ float tbPos);
	STDMETHOD(ClearAllTabs)();
	STDMETHOD(AddTab)(/*[in]*/ float tbPos, /*[in]*/ long tbAlign, /*[in]*/ long tbLeader);
	STDMETHOD(GetAlignment)(/*[out,retval]*/ long* pVal);
};

int GetSepStringArray(CUString str, CArray <CUString,CUString>& values, WCHAR sep)
{
	int len = str.GetLength();
	LPCTSTR p = str;
	int i = 0;

	while (i < len)
	{
		CUString str_value;
		while ((i < len) && (p[i] != sep))
		{
			str_value += CUString(p[i]);
			i++;
		}

		while (i < len && p[i] == ' ') i++;	// Skip spaces

		if (p[i] == sep) i++;

		while (i < len && p[i] == ' ') i++;	// Skip spaces

		str_value.TrimLeft();
		str_value.TrimRight();

		values.Add(str_value);
	}

	return values.GetSize();
}

void ParseTabString(BSTR str, CArray<CTab,CTab>& tabs)
{
	tabs.RemoveAll();

	CArray<CUString,CUString> tabsarr;
	GetSepStringArray(CUString(str), tabsarr, L';');

	for (int i = 0; i < tabsarr.GetSize(); i++)
	{
		CTab tab;
		sscanf(tabsarr[i], "%f %ld %ld", &tab.m_pos, &tab.m_align, &tab.m_leader);
		tabs.Add(tab);
	}
}

_bstr_t CPDTextPara::MakeTabString()
{
	_bstr_t str = L"";

	for (int i = 0; i < m_tabs.GetSize(); i++)
	{
		WCHAR buf[64];
		swprintf(buf, L"%g %d %d", m_tabs[i].m_pos, m_tabs[i].m_align, m_tabs[i].m_leader);

		if (i > 0) str += L";";
		str += buf;
	}

	return str;
}

STDMETHODIMP CPDTextPara::SetTabPos(long iTab, float tbPos, long *pVal)
{
	CTab tab = m_tabs[iTab];

	m_tabs.RemoveAt(iTab);

// Reinsert sorted on pos
	for (int i = 0; i < m_tabs.GetSize(); i++)
	{
		if (tbPos < m_tabs[i].m_pos)
			break;
	}

	tab.m_pos = tbPos;
	m_tabs.InsertAt(i, tab);
	if (pVal) *pVal = i;

	return S_OK;
}

STDMETHODIMP CPDTextPara::AddTab(float tbPos, long tbAlign, long tbLeader)
{
	return AddTabEx(tbPos, tbAlign, tbLeader, NULL);
}


STDMETHODIMP CPDTextPara::AddTabEx(float tbPos, long tbAlign, long tbLeader, long *pVal)
{
// Insert sorted on pos
	for (int i = 0; i < m_tabs.GetSize(); i++)
	{
		if (tbPos < m_tabs[i].m_pos)
			break;
	}

	CTab tab;
	tab.m_pos = tbPos;
	tab.m_align = tbAlign;
	tab.m_leader = tbLeader;
	m_tabs.InsertAt(i, tab);

	if (pVal) *pVal = i;

	return S_OK;
}

STDMETHODIMP CPDTextPara::ClearAllTabs()
{
	m_tabs.RemoveAll();
	return S_OK;
}

STDMETHODIMP CPDTextPara::DeleteTab(float tbPos)
{
	if (tbPos < 0) return E_INVALIDARG;

	for (int i = 0; i < m_tabs.GetSize(); i++)
	{
		if (tbPos == m_tabs[i].m_pos)
		{
			m_tabs.RemoveAt(i);
			return S_OK;
		}
	}

	return S_OK;
}

STDMETHODIMP CPDTextPara::GetTabCount(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_tabs.GetSize();
	return S_OK;
}

STDMETHODIMP CPDTextPara::GetTab(long iTab, float *ptbPos, long *ptbAlign, long *ptbLeader)
{
	if (iTab >= 0 && iTab < m_tabs.GetSize())
	{
		if (ptbPos) *ptbPos = m_tabs[iTab].m_pos;
		if (ptbAlign) *ptbAlign = m_tabs[iTab].m_align;
		if (ptbLeader) *ptbLeader = m_tabs[iTab].m_leader;

		return S_OK;
	}
	else
		return S_FALSE;
}

STDMETHODIMP CPDTextPara::GetAlignment(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_alignment;
	return S_OK;
}

STDMETHODIMP CPDTextPara::SetAlignment(long newVal)
{
	m_alignment = newVal;
	return S_OK;
}

STDMETHODIMP CPDTextPara::GetFirstLineIndent(float *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_firstLineIndent;
	return S_OK;
}

STDMETHODIMP CPDTextPara::SetIndents(float first, float left, float right)
{
	m_firstLineIndent = first;
	m_leftIndent = left;
	m_rightIndent = right;
	return S_OK;
}

STDMETHODIMP CPDTextPara::SetRightIndent(float newVal)
{
	m_rightIndent = newVal;
	return S_OK;
}

STDMETHODIMP CPDTextPara::GetRightIndent(float *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_rightIndent;
	return S_OK;
}

STDMETHODIMP CPDTextPara::GetLeftIndent(float *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_leftIndent;
	return S_OK;
}

STDMETHODIMP CPDTextPara::GetRange(IPDTextRange **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_range;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

class ATL_NO_VTABLE CPDTextFont : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDTextFont,
	public CNotifySendImpl<CPDTextFont>,
	public CPDObjectWithAppearanceAndStrokeFillImpl<CPDTextFont>
{
public:
	CPDTextFont()
	{
		m_size = tomUndefined;
		m_lineHeight = tomUndefined;


		m_matrix = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CComObject<CObjectMap>::CreateInstance(&m_subObjects);
		if (FAILED(hr)) return hr;
		m_subObjects->AddRef();

		return 0;
	}

	void FinalRelease()
	{
		if (m_subObjects)
		{
			m_subObjects->Release();
			m_subObjects = NULL;
		}
	}

	_bstr_t m_name;
	float m_size;
	float m_lineHeight;

	CComObject<CObjectMap>* m_subObjects;

// Need the following because of IPDObjectWithAppearance (TODO, remove)
	double m_scaleX, m_scaleY;
	double m_opacity;
	RectD m_filterRect;
	CComObject<CPDMatrix>* m_matrix;
//

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDTextFont)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDTextFont)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearance)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearanceAndStrokeFill)
END_COM_MAP()

public:
	STDMETHOD(removeSubObjects)();
	STDMETHOD(get_activeFill)(/*[out, retval]*/ IPDObjectFill* *pVal);
	STDMETHOD(put_activeFill)(/*[in]*/ IPDObjectFill* newVal);
	STDMETHOD(get_activeStroke)(/*[out, retval]*/ IPDObjectStroke* *pVal);
	STDMETHOD(put_activeStroke)(/*[in]*/ IPDObjectStroke* newVal);
	STDMETHOD(get_fillBrush)(/*[out, retval]*/ IPDBrush* *pVal);
	STDMETHOD(put_fillBrush)(/*[in]*/ IPDBrush* newVal);
	STDMETHOD(get_strokeBrush)(/*[out, retval]*/ IPDBrush* *pVal);
	STDMETHOD(put_strokeBrush)(/*[in]*/ IPDBrush* newVal);
	STDMETHOD(get_fill)(/*[out, retval]*/ IPDObjectFill* *pVal);
	STDMETHOD(put_fill)(/*[in]*/ IPDObjectFill* newVal);
	STDMETHOD(get_stroke)(/*[out, retval]*/ IPDObjectStroke* *pVal);
	STDMETHOD(put_stroke)(/*[in]*/ IPDObjectStroke* newVal);
	STDMETHOD(SetName)(/*[in]*/ BSTR newVal);
	STDMETHOD(GetName)(BSTR* pVal);
	STDMETHOD(GetSize)(float* pVal);
	STDMETHOD(SetSize)(/*[in]*/ float newVal);
	STDMETHOD(GetLineHeight)(/*[out,retval]*/ float* pVal);
// IPDObjectWithAppearance
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY)
	{
		return E_FAIL;
	}
// IPDObjectWithAppearanceAndStrokeFill
	STDMETHOD(get_subObjects)(/*[out, retval]*/ IObjectMap* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_subObjects;
		(*pVal)->AddRef();
		return S_OK;
	}
};

STDMETHODIMP CPDTextFont::GetName(BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_name.copy();
	return S_OK;
}

STDMETHODIMP CPDTextFont::SetName(BSTR newVal)
{
	m_name = newVal;
	return S_OK;
}

STDMETHODIMP CPDTextFont::GetSize(float* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_size;
	return S_OK;
}

STDMETHODIMP CPDTextFont::SetSize(float newVal)
{
	m_size = newVal;
	return S_OK;
}

STDMETHODIMP CPDTextFont::GetLineHeight(float *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_lineHeight;
	return S_OK;
}

// TODO, pass a default value if attribute not set
static _bstr_t _GetAttribute(ILDOMNode* node, BSTR attName)
{
	CComQIPtr<ILDOMElement> element = node;
	if (element)
	{
		BSTR battvalue;
		element->getAttribute(attName, &battvalue);
		if (battvalue)
		{
			return _bstr_t(battvalue, false);
		}

	// Try parent
		CComPtr<ILDOMNode> parentNode;
		element->get_parentNode(&parentNode);
		if (parentNode)
		{
			return _GetAttribute(parentNode, attName);
		}
	}

	return L"";
}

#include "PDColor.h"
#include "PDObjectStroke.h"
#include "PDObjectFill.h"

BOOL CPDStory::_extractFont(ILDOMRange* m_range, CPDTextFont* pTextFont, ILDOMNode* node, /*IDOMNode* parent,*/ int& hitStart)
{
	CComPtr<ILDOMNode> m_startContainer;
	long m_startOffset;
	m_range->get_startContainer(&m_startContainer);
	m_range->get_startOffset(&m_startOffset);

	CComPtr<ILDOMNode> m_endContainer;
	long m_endOffset;
	m_range->get_endContainer(&m_endContainer);
	m_range->get_endOffset(&m_endOffset);

	CComPtr<ILDOMDocument> document;
	node->get_ownerDocument(&document);

	CComPtr<ILDOMNodeList> childNodes;
	node->get_childNodes(&childNodes);

	long nChildNodes;
	childNodes->get_length(&nChildNodes);

	int startOffset;
	int endOffset;

	if (node == m_startContainer)
	{
		hitStart = TRUE;
		startOffset = m_startOffset;
	}
	else
		startOffset = 0;

	if (node == m_endContainer)
	{
		endOffset = m_endOffset;
	}
	else
	{
		endOffset = nChildNodes;
	}

	for (int nchild = startOffset; nchild < endOffset; nchild++)
	{
		CComPtr<ILDOMNode> child;
		childNodes->item(nchild, &child);

		CComQIPtr<ILDOMCharacterData> text = child;
		if (text)
		{
			if (child == m_startContainer)
			{
				hitStart = TRUE;
			}

			if (child == m_endContainer)
			{
				return FALSE;
			}
		}
		else
		{
			CComQIPtr<ILDOMElement> element = child;

			BOOL bContinue = _extractFont(m_range, pTextFont, element, hitStart);

			if (hitStart)
			{
				if (pTextFont->m_name.length())
				{
					_bstr_t fontname = _GetAttribute(element, L"font-family");
					if (wcscmp(fontname, pTextFont->m_name)) pTextFont->m_name = L"";
				}

				if (pTextFont->m_size != tomUndefined)
				{
					_bstr_t fontsize = _GetAttribute(element, L"font-size");
					if (atof(fontsize) != pTextFont->m_size) pTextFont->m_size = tomUndefined;
				}

				{
					Gdiplus::Font font(pTextFont->m_name, pTextFont->m_size);
					Gdiplus::FontFamily fontFamily;
					font.GetFamily(&fontFamily);
					int lineSpacing = fontFamily.GetLineSpacing(Gdiplus::FontStyleRegular);
					float lineSpacingPixel = font.GetSize() * lineSpacing / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

					pTextFont->m_lineHeight = ConvertUserUnitToSpecifiedValue(lineSpacingPixel, UNIT_PT);
					/*
					if (pTextFont->m_lineHeight != tomUndefined)
					{
					}
					*/
				}

				if (pTextFont->m_appearance != NULL)
				{
					_bstr_t fillColor = _GetAttribute(element, L"fill-color");
					int r=0,g=0,b=0;
					sscanf(fillColor, "rgb(%d,%d,%d)", &r,&g,&b);

					CComObject<CPDBrush>* brush;
					CComObject<CPDBrush>::CreateInstance(&brush);
					brush->AddRef();
					CComPtr<IPDColor> color;
					brush->setColor(&color);
					color->setRGB(r,g,b);

					CPDObjectFill* p = (CPDObjectFill*)(IPDObjectFill*)pTextFont->m_subObjects->m_items[0];
					if (p->m_brush->IsEqual(brush) == S_FALSE)
					{
						pTextFont->m_subObjects->m_items.RemoveAll();	// TODO also release
						pTextFont->m_appearance->Release();
						pTextFont->m_appearance = NULL;
					}
				}
			}

			if (hitStart)
			{
			}

			if (!bContinue)
				return FALSE;
		}
	}

	if (node == m_endContainer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPDStory::_extractPara(ILDOMRange* m_range, CPDTextPara* pTextPara, ILDOMNode* node, /*IDOMNode* parent,*/ int& hitStart)
{
	CComPtr<ILDOMNode> m_startContainer;
	long m_startOffset;
	m_range->get_startContainer(&m_startContainer);
	m_range->get_startOffset(&m_startOffset);

	CComPtr<ILDOMNode> m_endContainer;
	long m_endOffset;
	m_range->get_endContainer(&m_endContainer);
	m_range->get_endOffset(&m_endOffset);

	CComPtr<ILDOMDocument> document;
	node->get_ownerDocument(&document);

	CComPtr<ILDOMNodeList> childNodes;
	node->get_childNodes(&childNodes);

	long nChildNodes;
	childNodes->get_length(&nChildNodes);

	int startOffset;
	int endOffset;

	if (node == m_startContainer)
	{
		hitStart = TRUE;
		startOffset = m_startOffset;
	}
	else
		startOffset = 0;

	if (node == m_endContainer)
	{
		endOffset = m_endOffset;
	}
	else
	{
		endOffset = nChildNodes;
	}

	for (int nchild = startOffset; nchild < endOffset; nchild++)
	{
		CComPtr<ILDOMNode> child;
		childNodes->item(nchild, &child);

		CComQIPtr<ILDOMCharacterData> text = child;
		if (text)
		{
			if (child == m_startContainer)
			{
				hitStart = TRUE;
			}

			if (child == m_endContainer)
			{
				return FALSE;
			}
		}
		else
		{
			CComQIPtr<ILDOMElement> element = child;

			BOOL bContinue = _extractPara(m_range, pTextPara, element, hitStart);

			if (hitStart)
			{
			//	ATLASSERT(0);
				/*
				if (pTextFont->m_name.length())
				{
					_bstr_t fontname = _GetAttribute(element, L"font-family");
					if (wcscmp(fontname, pTextFont->m_name)) pTextFont->m_name = L"";
				}

				if (pTextFont->m_size != tomUndefined)
				{
					_bstr_t fontsize = _GetAttribute(element, L"font-size");
					if (atof(fontsize) != pTextFont->m_size) pTextFont->m_size = tomUndefined;
				}
				*/
			}

			if (hitStart)
			{
			}

			if (!bContinue)
				return FALSE;
		}
	}

	if (node == m_endContainer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL _setFont(ILDOMNode* m_startContainer, long m_startOffset, ILDOMNode* m_endContainer, long m_endOffset, ILDOMRange* m_range, CPDTextFont* pTextFont, ILDOMNode* node, /*IDOMNode* parent,*/ int& hitStart)
{
	CComPtr<ILDOMDocument> document;
	node->get_ownerDocument(&document);

	CComPtr<ILDOMNodeList> childNodes;
	node->get_childNodes(&childNodes);

	long nChildNodes;
	childNodes->get_length(&nChildNodes);

	int startOffset;
	int endOffset;

	if (node == m_startContainer)
	{
		hitStart = TRUE;
		startOffset = m_startOffset;
	}
	else
		startOffset = 0;

	if (node == m_endContainer)
	{
		endOffset = m_endOffset;
	}
	else
	{
		endOffset = nChildNodes;
	}

	for (int nchild = startOffset; nchild < endOffset; nchild++)
	{
		CComPtr<ILDOMNode> child;
		childNodes->item(nchild, &child);

		CComQIPtr<ILDOMText> text = child;
		if (text)
		{
			CComPtr<ILDOMNode> before;
			if (text == m_endContainer)
			{
				CComPtr<ILDOMText> newText;
				text->splitText(m_endOffset, &newText);

				before = newText;
			}
			else
			{
				child->get_nextSibling(&before);
			}

			if (text == m_startContainer)
			{
				hitStart = TRUE;
			}

			if (hitStart)
			{
				CComPtr<ILDOMElement> styleElement;
				document->createElement(L"style", &styleElement);

				if (pTextFont->m_name.length())
				{
					styleElement->setAttribute(L"font-family", pTextFont->m_name);
				}

				if (pTextFont->m_size != tomUndefined)
				{
					WCHAR buf[64];
					swprintf(buf, L"%g", pTextFont->m_size);
					styleElement->setAttribute(L"font-size", buf);
				}

				CComPtr<ILDOMText> newText;
				text->splitText(m_startOffset, &newText);

				styleElement->appendChild(newText, NULL);

				//parent = styleElement;

				//if (before)
					node->insertBefore(styleElement, before, NULL);
				//else
				//	node->appendChild(styleElement, NULL);

				if (text == m_startContainer)
				{
					m_range->setStart(newText, 0);
				}

				if (text == m_endContainer)
				{
					int len = m_endOffset;
					if (text == m_startContainer) len -= m_startOffset;

					m_range->setEnd(newText, len);
				}
			}

			if (child == m_endContainer)
			{
				return FALSE;
			}
		}
		else
		{
			CComQIPtr<ILDOMElement> element = child;

			//CComPtr<IDOMElement> newElement;
			//element->cloneNode(VARIANT_FALSE, (IDOMNode**)&newElement);

			BOOL bContinue = _setFont(m_startContainer, m_startOffset, m_endContainer, m_endOffset, m_range, pTextFont, element, /*newElement,*/ hitStart);

			/*
			if (hitStart)
			{
				// Remove the attributes that have been set
				if (pTextFont->m_name.length()) element->removeAttribute("font-family");
				if (pTextFont->m_size != tomUndefined) element->removeAttribute("font-size");

				VARIANT_BOOL bHasAttributes;
				element->hasAttributes(&bHasAttributes);
				if (!bHasAttributes)	// No more attributes on element Remove the element altogether
				{
					ATLASSERT(0);
				}
			}

			if (hitStart)
			{
				//parent->appendChild(newElement, NULL);
			}
			*/

			if (!bContinue)
				return FALSE;
		}
	}

	if (node == m_endContainer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL _setPara(ILDOMNode* m_startContainer, ILDOMNode* m_endContainer, /*IRange* m_range,*/ CPDTextPara* pTextPara, ILDOMNode* node, /*IDOMNode* parent,*/ int& hitStart)
{
	CComPtr<ILDOMDocument> document;
	node->get_ownerDocument(&document);

	CComPtr<ILDOMNodeList> childNodes;
	node->get_childNodes(&childNodes);

	long nChildNodes;
	childNodes->get_length(&nChildNodes);

	int startOffset;
	int endOffset;

	/*
	if (node == m_startContainer)
	{
		hitStart = TRUE;
		startOffset = m_startOffset;
	}
	else
		*/
		startOffset = 0;

	/*
	if (node == m_endContainer)
	{
		endOffset = m_endOffset;
	}
	else
		*/
	{
		endOffset = nChildNodes;
	}

	for (int nchild = startOffset; nchild < endOffset; nchild++)
	{
		CComPtr<ILDOMNode> child;
		childNodes->item(nchild, &child);

		CComQIPtr<ILDOMText> text = child;
		if (text)
		{
		}
		else
		{
			CComQIPtr<ILDOMElement> element = child;

			if (child == m_startContainer)
			{
				hitStart = TRUE;
			}

			if (hitStart)
			{
				BSTR btagName;
				element->get_tagName(&btagName);
				_bstr_t tagName = _bstr_t(btagName, false);

				if (!wcscmp(tagName, L"p"))
				{
					WCHAR buf[64];

					if (pTextPara->m_leftIndent != tomUndefined)
					{
						swprintf(buf, L"%g", pTextPara->m_leftIndent);
						element->setAttribute(L"margin-left", buf);
					}

					if (pTextPara->m_rightIndent != tomUndefined)
					{
						swprintf(buf, L"%g", pTextPara->m_rightIndent);
						element->setAttribute(L"margin-right", buf);
					}

					if (pTextPara->m_firstLineIndent != tomUndefined)
					{
						swprintf(buf, L"%g", pTextPara->m_firstLineIndent);
						element->setAttribute(L"text-indent", buf);
					}

					if (pTextPara->m_tabs.GetSize() > 0)
					{
					}
					else
					{
						element->removeAttribute(L"tabs");
					}
				}
			}

			BOOL bContinue = _setPara(m_startContainer, /*m_startOffset,*/ m_endContainer, /*m_endOffset, m_range,*/ pTextPara, element, /*newElement,*/ hitStart);

			if (child == m_endContainer)
			{
				return FALSE;
			}

			if (!bContinue)
				return FALSE;
		}
	}

	/*
	if (node == m_endContainer)
	{
		return FALSE;
	}
	*/

	return TRUE;
}

STDMETHODIMP CPDStory::SetTextFont(IPDTextRange *range, IPDTextFont *textFont)
{
	CComPtr<ILDOMRange> domrange;
	range->GetDOMRange(&domrange);

	CComPtr<ILDOMNode> commonAncestor;
	domrange->get_commonAncestorContainer(&commonAncestor);

	CComPtr<ILDOMNode> startContainer;
	long startOffset;
	domrange->get_startContainer(&startContainer);
	domrange->get_startOffset(&startOffset);

	CComPtr<ILDOMNode> endContainer;
	long endOffset;
	domrange->get_endContainer(&endContainer);
	domrange->get_endOffset(&endOffset);

	int hitStart = 0;
	_setFont(startContainer, startOffset, endContainer, endOffset, domrange, static_cast<CPDTextFont*>(textFont), commonAncestor, hitStart);
	
	return S_OK;
}

STDMETHODIMP CPDStory::GetTextFont(IPDTextRange *range, IPDTextFont **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDTextFont>* pTextFont;
	CComObject<CPDTextFont>::CreateInstance(&pTextFont);
	if (pTextFont)
	{
		pTextFont->AddRef();

		CComPtr<ILDOMRange> domrange;
		range->GetDOMRange(&domrange);

		CComPtr<ILDOMNode> commonAncestor;
		domrange->get_commonAncestorContainer(&commonAncestor);

		_bstr_t fontname = _GetAttribute(commonAncestor, L"font-family");
		pTextFont->m_name = fontname;

		_bstr_t fontsize = _GetAttribute(commonAncestor, L"font-size");
		pTextFont->m_size = atof(fontsize);

		{
			{
				Gdiplus::Font font(pTextFont->m_name, pTextFont->m_size);
				Gdiplus::FontFamily fontFamily;
				font.GetFamily(&fontFamily);
				int lineSpacing = fontFamily.GetLineSpacing(Gdiplus::FontStyleRegular);
				float lineSpacingPixel = pTextFont->m_size/*font.GetSize()*/ * lineSpacing / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

				UINT descent = fontFamily.GetCellDescent(Gdiplus::FontStyleRegular);
				float descentPixel = font.GetSize() * descent / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

			//	pTextFont->m_lineHeight = ConvertUserUnitToSpecifiedValue(lineSpacingPixel, UNIT_PT);
				pTextFont->m_lineHeight = lineSpacingPixel;

				pTextFont->m_lineHeight = pTextFont->m_size*120/100;
				/*
				if (pTextFont->m_lineHeight != tomUndefined)
				{
				}
				*/
			}

		//	if (pTextFont->m_appearance != NULL)
			{
				CComObject<CPDAppearance>::CreateInstance(&pTextFont->m_appearance);
				pTextFont->m_appearance->AddRef();

				CComObject<CPDObjectFill>* fill;
				CComObject<CPDObjectFill>::CreateInstance(&fill);
				fill->AddRef();
				pTextFont->m_subObjects->m_items.Add((IPDObjectFill*)fill);

				{
					CPDObjectFill* p = (CPDObjectFill*)(IPDObjectFill*)pTextFont->m_subObjects->m_items[0];

					_bstr_t fillColor = _GetAttribute(commonAncestor, L"fill-color");
					int r=0,g=0,b=0;
					sscanf(fillColor, "rgb(%d,%d,%d)", &r,&g,&b);

					CComObject<CPDBrush>* brush = p->m_brush;
					//CComObject<CPDBrush>::CreateInstance(&brush);
					//brush->AddRef();
					CComPtr<IPDColor> color;
					brush->setColor(&color);
					color->setRGB(r,g,b);

					/*
					if (p->m_brush->IsEqual(brush) == S_FALSE)
					{
						pTextFont->m_appearance->Release();
						pTextFont->m_appearance = NULL;
					}
					*/
				}
			}
		}

		int hitStart = 0;
		_extractFont(domrange, pTextFont, commonAncestor, hitStart);

		*pVal = pTextFont;
		return S_OK;
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDStory::GetTextPara(IPDTextRange *range, IPDTextPara **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDTextPara>* pTextPara;
	CComObject<CPDTextPara>::CreateInstance(&pTextPara);
	if (pTextPara)
	{
		pTextPara->AddRef();

		pTextPara->m_range = range;

		CComPtr<ILDOMRange> domrange;
		range->GetDOMRange(&domrange);

		CComPtr<ILDOMNode> commonAncestor;
		domrange->get_commonAncestorContainer(&commonAncestor);

		_bstr_t _bstr;

		_bstr = _GetAttribute(commonAncestor, L"margin-left");
		pTextPara->m_leftIndent = atof(_bstr);

		_bstr = _GetAttribute(commonAncestor, L"margin-right");
		pTextPara->m_rightIndent = atof(_bstr);

		_bstr = _GetAttribute(commonAncestor, L"text-indent");
		pTextPara->m_firstLineIndent = atof(_bstr);

		_bstr = _GetAttribute(commonAncestor, L"text-align");
		pTextPara->m_alignment = atof(_bstr);

		_bstr_t tabstr = _GetAttribute(commonAncestor, L"tabs");
		if (tabstr.length()) ParseTabString(tabstr, pTextPara->m_tabs);

		int hitStart = 0;
		_extractPara(domrange, pTextPara, commonAncestor, hitStart);

		*pVal = pTextPara;
		return S_OK;
	}
	else
		*pVal = NULL;

	return S_OK;
}

ILDOMNode* FindCommonAncestor(ILDOMNode* node1, ILDOMNode* node2)
{
	CComPtr<ILDOMNode> parentNode1;
	node1->get_parentNode(&parentNode1);

	CArray<ILDOMNode*,ILDOMNode*> arr1;
	CArray<ILDOMNode*,ILDOMNode*> arr2;

	{
		CComPtr<ILDOMNode> parentNode;
		node1->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr1.Add(parentNode);

			CComPtr<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	{
		CComPtr<ILDOMNode> parentNode;
		node2->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr2.Add(parentNode);

			CComPtr<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	for (int i = 0; i < arr1.GetSize(); i++)
	{
		for (int j = 0; j < arr2.GetSize(); j++)
		{
			if (arr1[i] == arr2[j])
				return arr1[i];
		}
	}

	ATLASSERT(0);
	return NULL;
}

STDMETHODIMP CPDStory::SetTextPara(IPDTextRange *range, IPDTextPara *textPara)
{
	CComPtr<ILDOMRange> domrange;
	range->GetDOMRange(&domrange);

	CComPtr<ILDOMNode> commonAncestor;
	domrange->get_commonAncestorContainer(&commonAncestor);

	CComPtr<ILDOMNode> startContainer;
//	long startOffset;
	domrange->get_startContainer(&startContainer);
//	domrange->get_startOffset(&startOffset);

	CComPtr<ILDOMNode> endContainer;
//	long endOffset;
	domrange->get_endContainer(&endContainer);
//	domrange->get_endOffset(&endOffset);

	CComPtr<ILDOMNode> startp = startContainer;
	while (startp != NULL)
	{
		CComQIPtr<ILDOMElement> element = startp;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);
			if (!wcscmp(tagName, L"p"))
			{
				break;
			}
		}

		CComPtr<ILDOMNode> parentNode;
		startp->get_parentNode(&parentNode);
		startp = parentNode;
	}
	ATLASSERT(startp != NULL);

	CComPtr<ILDOMNode> endp = endContainer;
	while (endp != NULL)
	{
		CComQIPtr<ILDOMElement> element = endp;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);
			if (!wcscmp(tagName, L"p"))
			{
				break;
			}
		}

		CComPtr<ILDOMNode> parentNode;
		endp->get_parentNode(&parentNode);
		endp = parentNode;
	}
	ATLASSERT(endp != NULL);

	int hitStart = 0;	// Start with hit ?
	_setPara(startp, /*startOffset,*/ endp, /*endOffset,*/
		/*domrange,*/
		static_cast<CPDTextPara*>(textPara),
		FindCommonAncestor(startp, endp),
		hitStart);

	return S_OK;
}

STDMETHODIMP CPDStory::NewRange(IPDTextRange **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDTextRange>* pRange;
	CComObject<CPDTextRange>::CreateInstance(&pRange);
	if (pRange)
	{
		pRange->m_story = this;
		(*pVal = pRange)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDStory::NewSelection(IPDTextSelection **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDTextSelection>* pRange;
	CComObject<CPDTextSelection>::CreateInstance(&pRange);
	if (pRange)
	{
		pRange->m_story = this;
		(*pVal = pRange)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDTextPara::get_dropCapLines(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextPara::put_dropCapLines(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextPara::get_dropCapChars(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextPara::put_dropCapChars(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

int CompareTreePosition(ILDOMNode* pThis, ILDOMNode* pNode);

STDMETHODIMP CPDStory::GetObjectTextFromRangePosition(ILDOMNode *container, long offset, IPDObjectText **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CPDObjectTextImpl<IPDObjectText>* textThread = m_firstTextThread;
	while (textThread)
	{
		// Check if container/offset is between m_start(end)Container/m_start(end)Offset of textThread
		if (textThread->m_startContainer)
		{
			ATLASSERT(textThread->m_endContainer);

			int startcmp = CompareTreePosition(textThread->m_startContainer, container);
			if (startcmp < 0 || (startcmp == 0 && textThread->m_startOffset <= offset))
			{
				int endcmp = CompareTreePosition(textThread->m_endContainer, container);
				if (endcmp > 0 || (endcmp == 0 && textThread->m_endOffset >= offset))
				{
					*pVal = textThread;
					(*pVal)->AddRef();
					return S_OK;
				}
			}
		}

		textThread = textThread->m_nextTextThread;
	}

	*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDTextFont::get_stroke(IPDObjectStroke **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::put_stroke(IPDObjectStroke *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::get_fill(IPDObjectFill **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::put_fill(IPDObjectFill *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::get_strokeBrush(IPDBrush **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::put_strokeBrush(IPDBrush *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::get_fillBrush(IPDBrush **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::put_fillBrush(IPDBrush *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::get_activeStroke(IPDObjectStroke **pVal)
{
	*pVal = NULL;
	return S_OK;

	*pVal = (IPDObjectStroke*)m_subObjects->m_items[1];
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDTextFont::put_activeStroke(IPDObjectStroke *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::get_activeFill(IPDObjectFill **pVal)
{
	*pVal = (IPDObjectFill*)m_subObjects->m_items[0];
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDTextFont::put_activeFill(IPDObjectFill *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDTextFont::removeSubObjects()
{
	// TODO: Add your implementation code here

	return S_OK;
}
