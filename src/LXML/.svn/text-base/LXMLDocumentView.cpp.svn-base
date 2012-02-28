#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#if 0

#include "LBoxWindow.h"
#include "LXMLDocumentView.h"

//#include "LHTMLActiveDocument.h"
//#include "LHTMLDocumentView.h"
#if 0
#include "ScriptSite.h"
#endif

#if 0
#include "HTMFrame.h"
#endif

#if 0
#include "PHTMLFrameSetBaseElement.h"
#endif

#if 0
#include "..\OleDataObject.h"
#include "..\Utils\IEnumfe.h"
#endif

//#include "HTMLScriptSite.h"
//#include "LHTMLWindow.h"
//#include "LHTMLDialog.h"

#if 0
#include "FODisplay.h"
#endif

#if 0
#include "LDOMDocumentImpl.h"
#include "LDOMElementImpl.h"

#include "LSVGPoint.h"
#include "LSVGMatrix.h"
#include "LDOMMouseEvent.h"
#include "LSVGZoomEvent.h"
#endif

#include "PTextNode.h"
#include "PWord.h"
#include "CSSStackingContext.h"
#include "PBlockBox.h"
#include "HTMContext.h"

#if 0
#include "LDOMDocumentImpl.h"
#endif

#if 0
#include "PElementBase.h"
#endif

//#include "PSVGElement.h"
#if 0
#include "PSMILElement.h"
#include "PSMILLayoutElement.h"

#include "PHTMLFrameSetElement.h"
#include "PHTMLFrameElement.h"
#include "PHTMLIFrameElement.h"
#include "PHTMLImageElement.h"
#include "PHTMLObjectElement.h"
#include "PHTMLInputElement.h"
#include "PHTMLSelectElement.h"
#include "PHTMLTextAreaElement.h"

//#include "PSVGElement.h"

#include "PSMILElementImpl.h"
#include "PSMILElement.h"
#include "PSMILRootLayoutElement.h"
#include "PSMILTopLayoutElement.h"
#include "PSMILRegionElement.h"
#endif

namespace LXML
{

void LXUIEXT CalcDims(CPElementBase* pElement);

///////////////////////////////////////////////////////////
// CXMLDocumentView

CFontDataFile* CXMLDocumentView::AddFontDataFile(const sysstring& url)
{
	for (int i = 0; i < m_fontDataFiles.GetSize(); i++)
	{
		if (!wcscmp(m_fontDataFiles[i]->m_url.c_str(), url.c_str()))
		{
			return m_fontDataFiles[i];
		}
	}

	CFontDataFile* pFontDataFile = new CFontDataFile;
	pFontDataFile->m_url = url;

	m_fontDataFiles.Add(pFontDataFile);

	return pFontDataFile;
}

LSVG::CPSVGElementImpl* FindFontFace(CPElementBase* pElement, BSTR fontFamily)
{
	ASSERT(0);
#if 0
	UPOSITION pos = pElement->m_childList.GetHeadPosition();
	while (pos)
	{
		CPElementBase* pElement2 = (CPElementBase*)pElement->m_childList.GetNext(pos);
		if (pElement2->m_type == LNODE_ELEMENT)	// element node
		{
			ASSERT(0);
#if 0
			CComQIPtr<ILSVGFontFaceElement> fontface = pElement2->m_pNode;
			if (fontface)
			{
				CComBSTR fontFamily2;
				fontface->getAttribute(L"font-family", &fontFamily2);

				if (fontFamily2.Length() && !wcsicmp(fontFamily2, fontFamily))
				{
					return (CPSVGElementImpl*)pElement2;
				}
			}

			CPSVGElementImpl* pFontFace = FindFontFace(pElement2, fontFamily);
			if (pFontFace)
				return pFontFace;
#endif
		}
	}
#endif

	return NULL;
}

CFontFamilyDef* CXMLDocumentView::AddFontFamily(const sysstring& family)
{
	USES_CONVERSION;

	for (int i = 0; i < m_fontFamilies.GetSize(); i++)
	{
		if (!wcscmp(m_fontFamilies[i]->m_name, family.c_str()))
		{
			m_fontFamilies[i]->m_refcount++;
			return m_fontFamilies[i];
		}
	}

	CFontFamilyDef* pFontFamilyDef = new CFontFamilyDef;
	pFontFamilyDef->m_pView = this;
	pFontFamilyDef->m_refcount = 1;
	wcscpy(pFontFamilyDef->m_name, family.c_str());

	{
//		MessageBeep(-1);	// TODO
#if 0
	// Stuff if the font is an SVG Font
		CPSVGElementImpl* pFontFace = FindFontFace(m_htmTree, pFontFamilyDef->m_name);
		if (pFontFace)
		{
			CComQIPtr<ILSVGFontElement> fontElement = pFontFace->m_parent->m_pNode;
			if (fontElement)
			{
				pFontFamilyDef->m_pSVGFontElement = (CPSVGFontElement*)pFontFace->m_parent;
			}
			else
			{
				CPSVGElementImpl* pFontFaceSrc = (CPSVGElementImpl*)pFontFace->GetElementByTagNameNS(OLESTR("http://www.w3.org/2000/svg"), OLESTR("font-face-src"), FALSE);
				if (pFontFaceSrc)
				{
					CPSVGElementImpl* pFontFaceUri = (CPSVGElementImpl*)pFontFaceSrc->GetElementByTagNameNS(L"http://www.w3.org/2000/svg", L"font-face-uri", FALSE);
					if (pFontFaceUri)
					{
						CComQIPtr<ILSVGElement> element = pFontFaceUri->m_pNode;

						CComBSTR href;
						element->getAttributeNS(OLESTR("http://www.w3.org/1999/xlink"), OLESTR("href"), &href);

						if (href.Length())
						{
							TCHAR result[2048];

							Document* ownerDocument;
							element->get_ownerDocument(&ownerDocument);

							CComBSTR documentUrl;
							ownerDocument->get_url(&documentUrl);

							DWORD resultLen = sizeof(result);
							InternetCombineUrl(W2A(documentUrl), W2A(href), result, &resultLen, 0);

							TCHAR* id = NULL;
							int i = resultLen-1;
							while (i >= 0)
							{
								if (result[i] == '#')
								{
									id = &result[i+1];
									result[i] = 0;
									break;
								}

								i--;
							}

							if (id)	// Must point to a <font> element in the external file
							{
								CFontDataFile* pFontDataFile = AddFontDataFile(A2W(result));
								if (pFontDataFile->m_pWindow == NULL)
								{
									pFontDataFile->m_pWindow = new CHTMLWindow;
									//pFontDataFile->m_pWindow->AddRef();

									CComPtr<ILSVGDocument> svgDocument;
									svgDocument.CoCreateInstance(CLSID_LSVGDocument);

									svgDocument->set_errorHandler(m_pActiveDocument->m_errorHandler);

									bool bsuccess;
									svgDocument->load(pFontDataFile->m_url, &bsuccess);

									pFontDataFile->m_pWindow->SetDocument(svgDocument);
								}

								if (pFontDataFile->m_pWindow->m_htmTree)
								{
									CPElement* pPElement = pFontDataFile->m_pWindow->m_htmTree->GetElementById(A2W(id));
									if (pPElement)
									{
										CComQIPtr<ILSVGFontElement> fontElement = pPElement->m_pNode;
										if (fontElement)
										{
											pFontFamilyDef->m_pSVGFontElement = (CPSVGFontElement*)pPElement;
										}
									}
								}
							}
						}
					}
				}
			}
		}
#endif
	}

	m_fontFamilies.Add(pFontFamilyDef);

	return pFontFamilyDef;
}

void CXMLDocumentView::ReleaseFontFamilyDef(CFontFamilyDef* pFontFamilyDef)
{
	for (int i = 0; i < m_fontFamilies.GetSize(); i++)
	{
		if (m_fontFamilies[i] == pFontFamilyDef)
		{
			pFontFamilyDef->m_refcount--;
			if (pFontFamilyDef->m_refcount == 0)
			{
				delete pFontFamilyDef;
				m_fontFamilies.RemoveAt(i);
			}
			return;
		}
	}

	ASSERT(0);
}

CFontDef* CXMLDocumentView::AddFontDef(const sysstring& family, double size, int weight, int style)
{
	CFontFamilyDef* pFontFamilyDef = AddFontFamily(family);

	ASSERT(pFontFamilyDef);

	for (int i = 0; i < m_fonts.GetSize(); i++)
	{
		if (m_fonts[i]->m_size == size &&
			m_fonts[i]->m_weight == weight &&
			m_fonts[i]->m_style == style &&
			m_fonts[i]->m_pFamily == pFontFamilyDef)
		{
			pFontFamilyDef->m_refcount--;

			m_fonts[i]->m_refcount++;
			return m_fonts[i];
		}
	}

	CFontDef* pFontDef = new CFontDef;
//	pFontDef->m_pFrame = this;
	pFontDef->m_refcount = 1;

	pFontDef->m_pFamily = pFontFamilyDef;
	//pFontDef->m_pFamily->m_refcount++;

	pFontDef->m_size = size;
	pFontDef->m_weight = weight;
	pFontDef->m_style = style;

	m_fonts.Add(pFontDef);

	return pFontDef;
}

void CXMLDocumentView::ReleaseFontDef(CFontDef* pFontDef)
{
	for (int i = 0; i < m_fonts.GetSize(); i++)
	{
		if (m_fonts[i] == pFontDef)
		{
			pFontDef->m_refcount--;
			if (pFontDef->m_refcount == 0)
			{
				ReleaseFontFamilyDef(pFontDef->m_pFamily);

				delete pFontDef;
				m_fonts.RemoveAt(i);
			}
			return;
		}
	}

	ASSERT(0);
}

#if 0
STDMETHODIMP CXMLDocumentView::GetViewNode(/*[in]*/ ILDOMNode* node, /*[out, retval]*/ ILViewNode* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComQIPtr<CLDOMNodeImplImpl> nodeImpl(node);
	if (nodeImpl == NULL) return E_INVALIDARG;

	CPNode* pPNode = nodeImpl->GetNodeOnFrame(this);

	ASSERT(CComQIPtr<ILViewNode>(pPNode));

	*pVal = pPNode;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

#include "LDOMElement.h"

STDMETHODIMP CXMLDocumentView::GetAnonymousNode(/*[in]*/ ILDOMElement* element, /*[out, retval]*/ ILDOMNode* *pVal)
{
	CComQIPtr<CLDOMElementImplImpl> nodeImpl(element);
	if (nodeImpl == NULL) return E_INVALIDARG;

	CPElement* pPElement = (CPElement*)nodeImpl->GetNodeOnFrame(this);

	*pVal = pPElement->m_bindNode;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}
#endif

////////////////////////////////////////////////////////////////////////////////////
// CFontDataFile

CFontDataFile::CFontDataFile()
{
	m_pWindow = NULL;
}

CFontDataFile::~CFontDataFile()
{
	if (m_pWindow)
	{
//		m_pWindow->Release();
		m_pWindow = NULL;
	}
}

/////////////////////////////////////
// CFontFamilyDef

CFontFamilyDef::CFontFamilyDef()
{
	m_refcount = 0;
	m_pView = NULL;
	m_pSVGFontElement = NULL;
}

////////////////////////////////////////////////////////////////////////////////////
// CFontDef

CFontDef::CFontDef()
{
	m_refcount = 0;
//	m_pFrame = NULL;

	m_pFamily = NULL;

#if 0
	m_hFont = NULL;
	m_hFontHinted = NULL;
#endif
	m_gdipFont = NULL;
//	m_pSVGFontElement = NULL;
}

CFontDef::~CFontDef()
{
#if 0
	if (m_hFont)
	{
		DeleteObject(m_hFont);
	}

	if (m_hFontHinted)
	{
		DeleteObject(m_hFontHinted);
	}
#endif

	if (m_gdipFont)
	{
		delete m_gdipFont;
	}
}

#if 0
HFONT CFontDef::GetHFONT()
{
	USES_CONVERSION;

	if (m_hFont == NULL)
	{
		LOGFONT lf = {0};
	//	lf.lfHeight = -(int)(m_size/*+0.5*/);//-ConvertUserUnitToSpecifiedValue(m_size, CSS_PT);//(long)-m_size;
		lf.lfHeight = -(int)2048;	// Unhinted
		lf.lfWeight = m_weight;
		lf.lfItalic = m_style != FontStyle_normal;
		strcpy(lf.lfFaceName, W2A(m_pFamily->m_name));

		m_hFont = CreateFontIndirect(&lf);

	//
		HDC hDC = CreateCompatibleDC(NULL);
		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

		GetTextMetrics(hDC, &m_tm);

		m_descent = m_tm.tmDescent;

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
	}

	return m_hFont;
}

HFONT CFontDef::GetHintedHFONT()
{
	USES_CONVERSION;

	if (m_hFontHinted == NULL)
	{
		LOGFONT lf = {0};
		lf.lfHeight = -(int)(m_size/*+0.5*/);//-ConvertUserUnitToSpecifiedValue(m_size, CSS_PT);//(long)-m_size;
	//	lf.lfHeight = -(int)2048;	// Unhinted
		lf.lfWeight = m_weight;
		lf.lfItalic = m_style != FontStyle_normal;
		strcpy(lf.lfFaceName, W2A(m_pFamily->m_name));

		m_hFontHinted = CreateFontIndirect(&lf);

	//
		HDC hDC = CreateCompatibleDC(NULL);
		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFontHinted);

		GetTextMetrics(hDC, &m_tm);

		m_descent = m_tm.tmDescent;

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
	}

	return m_hFontHinted;
}
#endif

LDraw::Font* CFontDef::GetGdipFont()
{
	USES_CONVERSION;

	if (m_gdipFont == NULL)
	{
#if 0
		LOGFONTW lf = {0};
		lf.lfHeight = (long)-m_size;
		lf.lfWeight = m_weight;
		lf.lfItalic = m_style != FontStyle_normal;
		wcscpy(lf.lfFaceName, /*W2A*/(m_pFamily->m_name));

		HDC hDC = CreateCompatibleDC(NULL);

		m_gdipFont = new Gdiplus::Font(hDC, &lf);

		if (m_weight > 400)
		{
			ASSERT(m_gdipFont->GetStyle() & Gdiplus::FontStyleBold);
		}

		DeleteDC(hDC);
#endif

		int style = 0;

#if 0
		if (m_weight >= 600)
			style |= Gdiplus::FontStyleBold;

		if (m_style != FontStyle_normal)
			style |= Gdiplus::FontStyleItalic;

		m_gdipFont = new Gdiplus::Font(m_pFamily->m_name, m_size, style, Gdiplus::UnitPixel);
#endif
		m_gdipFont = new LDraw::Font(m_size);
		m_gdipFont->LoadFile("c:/windows/fonts/cour.ttf");
	}

	return m_gdipFont;
}

////////////////////////////////////////////////////////////////////////////////////

#if 0
void CHTMLDocumentView::Free()
{
// hmm.. maybe view should be on FrameElement instead ??
	if (m_document)
	{
		CComQIPtr<CLDOMDocumentImplImpl>(m_document)->RemoveView(this);

#if 0
		CComQIPtr<INotifySend> cp = m_document;	// TODO, try m_element instead to see if that works
		ASSERT(cp);
		cp->Unadvise(this);
#endif
	}
}

CPElement* CXMLDocumentView::CreateElement(ILDOMElement* element)
{
	CPElement* pElement2 = NULL;

	CComBSTR namespaceURI;
	element->get_namespaceURI(&namespaceURI);

	CComBSTR tagName;
	element->get_localName(&tagName);	// Try local name first
	if (tagName.Length() == 0)
	{
		element->get_tagName(&tagName);	// Then try full qualified name
	}

	/*
	if (namespaceURI.Length() && !wcscmp(namespaceURI, L"http://www.w3.org/2000/svg") &&
		!wcscmp(tagName, L"svg"))
	{
		CComObject<CPSVGSVGElement>* pElement;
		CComObject<CPSVGSVGElement>::CreateInstance(&pElement);
		pElement->AddRef();
		pItem = pElement;
	}
	*/
#if 0	// Moved this to LMathML project
	else if (namespaceURI.Length() && !wcscmp(namespaceURI, L"http://www.w3.org/1998/Math/MathML") &&
		!wcscmp(tagName, OLESTR("math")))
	{
		CComObject<CPMathMLMathElement>* pElement;
		CComObject<CPMathMLMathElement>::CreateInstance(&pElement);
		pElement->AddRef();
		pElement2 = pElement;
	}
#endif
#if 0
	if (namespaceURI.Length() && (
			!wcscmp(namespaceURI, L"http://www.w3.org/2001/SMIL20/Language") ||
			!wcscmp(namespaceURI, L"http://www.w3.org/2000/SMIL20/CR/Language")))
	{
		if (!wcscmp(tagName, L"root-layout"))
		{
			CComObject<CPSMILRootLayoutElement>* pElement;
			CComObject<CPSMILRootLayoutElement>::CreateInstance(&pElement);
			pElement->AddRef();
			pElement2 = pElement;
		}
		else if (!wcscmp(tagName, L"topLayout"))
		{
			CComObject<CPSMILTopLayoutElement>* pElement;
			CComObject<CPSMILTopLayoutElement>::CreateInstance(&pElement);
			pElement->AddRef();
			pElement2 = pElement;
		}
		else if (!wcscmp(tagName, L"region"))
		{
			CComObject<CPSMILRegionElement>* pElement;
			CComObject<CPSMILRegionElement>::CreateInstance(&pElement);
			pElement->AddRef();
			pElement2 = pElement;
		}
	//
		else	// Generic/Unknown smil element
		{
			CComObject<CPSMILElement>* pElement;
			CComObject<CPSMILElement>::CreateInstance(&pElement);
			pElement->AddRef();
			pElement2 = pElement;
		}
	}
	else
#endif
	{
#if 0
		if (namespaceURI.Length())
		{
			// (X)HTML elements
			if (!wcscmp(namespaceURI, L"http://www.w3.org/1999/xhtml"))
			{
			//	bool isXML;
			//	m_document->get_isXML(&isXML);

				if (!wcscmp(tagName, L"script"))
				{
					return NULL;//pItem = new CHTMPTable(node);
				}
				else if (!wcscmp(tagName, L"img"))
				{
					CComObject<CHTMPImg>* pElement;
					CComObject<CHTMPImg>::CreateInstance(&pElement);
					pElement->AddRef();
					pElement2 = pElement;
				}
				else if (!wcscmp(tagName, L"frame"))
				{
					CComObject<CPHTMLFrameElement>* pElement;
					CComObject<CPHTMLFrameElement>::CreateInstance(&pElement);
					pElement->AddRef();
					pElement2 = pElement;
				}
				else if (!wcscmp(tagName, L"frameset"))
				{
					CComObject<CPHTMLFrameSetElement>* pElement;
					CComObject<CPHTMLFrameSetElement>::CreateInstance(&pElement);
					pElement->AddRef();
					pElement2 = pElement;
				}
				else if (!wcscmp(tagName, L"iframe"))
				{
					CComObject<CPHTMLIFrameElement>* pElement;
					CComObject<CPHTMLIFrameElement>::CreateInstance(&pElement);
					pElement->AddRef();
					pElement2 = pElement;
				}
				else if (!wcscmp(tagName, L"object"))
				{
					CComObject<CPHTMLObjectElement>* pElement;
					CComObject<CPHTMLObjectElement>::CreateInstance(&pElement);
					pElement->AddRef();
					pElement2 = pElement;
				}
#if 0
				else if (!wcscmp(tagName, L"applet"))
				{
				//	pItem = new CHTMPApplet(element);
				}
				else if (!wcscmp(tagName, L"embed"))
				{
				//	pItem = new CHTMPEmbed(element);
				}

				else if (!wcscmp(tagName, L"input"))
				{
				//	pItem = new CHTMPInput(element);
				}

				else if (!wcscmp(tagName, L"textarea"))
				{
					// Don't recurse into this
				//	pItem = new CHTMPTextArea(element);
					//pItem->m_pFrame = pFrame;
					//return pItem;
				}

				else if (!wcscmp(tagName, L"select"))
				{
					// Don't recurse into this
				//	pItem = new CHTMPSelect(element);
					//pItem->m_pFrame = pFrame;
					//return pItem;
				}

				else if (!wcscmp(tagName, L"option"))
				{
					return NULL;
				}
#endif
			}
			else if (!wcscmp(namespaceURI, L"urn:schemas-microsoft-com:time"))
			{
				/*
				if (!wcsicmp(tagName, L"seq"))			pItem = new CHTMPElement(element);
				else if (!wcsicmp(tagName, L"par"))		pItem = new CHTMPElement(element);
				*/
			}
			else if (!wcscmp(namespaceURI, L"http://www.w3.org/1999/XSL/Transform"))
			{
				/*
				if (!wcsicmp(tagName, L"template"))	pItem = new CPXSLTTemplateElement(element);
				else if (!wcsicmp(tagName, L"for-each"))	pItem = new CPXSLTForEachElement(element);
				else if (!wcsicmp(tagName, L"apply-templates"))	pItem = new CPXSLTApplyTemplatesElement(element);
				*/
			}
		}
#endif

		CComQIPtr<CLDOMDocumentImplImpl> documentImpl(m_document);

		for (int i = 0; i < documentImpl->m_implementation->m_implList.GetSize(); i++)
		{
			CComPtr<IUnknown> unk;
			documentImpl->m_implementation->m_implList[i]->CreateViewElement(element, this, &unk);
			if (unk)
			{
				CComQIPtr<ILViewNode> viewNode(unk);
				pElement2 = static_cast<CPElement*>(viewNode.Detach());
				ASSERT(pElement2);
				break;
			}
		}

		if (!pElement2)	// Unknown tag, create a default element
		{
			ASSERT(0);
#if 0
			CComObject<CPHTMElement>* pElement;
			CComObject<CPHTMElement>::CreateInstance(&pElement);
			pElement->AddRef();
			pElement2 = pElement;
#endif
		}
	}

	if (pElement2)
	{
		pElement2->m_pNode = element;

		CComQIPtr<ILDOMEventTarget> eventTarget = element;
		pElement2->m_eventTarget = eventTarget;

		pElement2->m_pView = this;
#if 0
		pElement2->m_pWindow = this;
#endif

		pElement2->CreateBehaviors();	// ???
	}

	return pElement2;
}


#if 0
// INotifyGet
STDMETHODIMP CHTMLDocumentView::OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
{
	if (type == (NotifyType)-1) return S_OK;	// Hack

	if (targetObject == m_pWindow->m_range)
	{
		m_pWindow->InvalidateRect(NULL);

#if 0
		m_pUI->m_document->Fire_onselect();
#endif
	}
	else if (m_pWindow->m_pFrameSet == NULL) // ???// if (m_htmTree || m_pFODisplay)
	{
		m_pWindow->m_lockPaint++;

		CComQIPtr<ILDOMNode> targetNode = targetObject;
		if (targetNode)
		{
			LDOMNodeType nodeType;
			targetNode->get_nodeType(&nodeType);
			
			if ((nodeType == LNODE_TEXT/* || nodeType == LNODE_CDATA_SECTION*/) &&
				(type == NOTIFY_MODIFY))
			{
				CComQIPtr<ILDOMCharacterData> charData = targetNode;

				CPTextNode* pText = (CPTextNode*)CComQIPtr<CLDOMNodeImplImpl>(charData)->GetNodeOnFrame(this);
				if (pText)
				{
					pText->OnTextContentChanged();

					{
						HDC hDC = CreateCompatibleDC(NULL);
						{
							Gdiplus::Graphics graphics(hDC);

							CHTMCalcContext pC;
							// I had this ???
							//pC.m_pUI = m_pWindow->m_pUI;
							pC.m_pGraphics = &graphics;

							pC.m_pStringFormat = Gdiplus::StringFormat::GenericTypographic();

							graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault/*TextRenderingHintAntiAliasGridFit*//*TextRenderingHintAntiAlias*/);	// ??

							pText->CalculateDimensions(&pC);
						}
						DeleteDC(hDC);
					}

				// TODO, have common code for both svg and css box model
					if (m_pWindow->m_pSVGElement == NULL)
					{
						CPElement* pParent = pText->m_parent;

						pParent->RemoveBoxes();

						while (pParent)
						{
							if (pParent->m_computedDisplayRole == DisplayRole_table_cell)
							{
								pParent->CalculateMinMaxDimensions();
							}

							pParent = pParent->m_parent;
						}
					}
					else
					{
						ASSERT(0);
#if 0
						CPElement* pParent = pText->m_parent;

						while (pParent)
						{
							CComQIPtr<ILSVGTextElement> textElement = pParent->m_pNode;
							if (textElement)
							{
								CPSVGTextElement* pSVGTextElement = (CPSVGTextElement*)pParent;
								pSVGTextElement->CalculateBounds();

								pSVGTextElement->m_parent->RecalculateParentBounds();

								break;
							}

							pParent = pParent->m_parent;
						}
#endif
					}
				}
			}
			else
			{
				if (TRUE)
				{
					m_pWindow->m_curContainer = NULL;	// hm..
					if (m_pWindow->m_range)
					{
						m_pWindow->m_range->setStart(NULL, -1);
						m_pWindow->m_range->setEnd(NULL, -1);
					}
				}

				CComQIPtr<ILDOMElement> element = targetNode;

				CComPtr<ILDOMNode> parentNode;
				targetNode->get_parentNode(&parentNode);

				if (element && type == NOTIFY_ADD)
				{
					CComQIPtr<ILDOMDocument> document = parentNode;

					if (document)
					{
						CPElement* pPElement = CreateElement(element);
						if (pPElement)
						{
							CComQIPtr<CLDOMElementImplImpl>(element)->m_pNodes.Add(pPElement);
							pPElement->BuildChildren();

							m_pRootElement = pPElement;

							ASSERT(0);
#if 0
							m_pWindow->m_pSVGElement = (CPSVGElementImpl*)m_pWindow->m_htmTree;
							m_pWindow->m_pSVGElement->CreateBehaviors();	// TODO, don't do this here

							pPElement->GetCSSPropertiesAndChildren();
							pPElement->SetValuesFromAttributes();	// ??
							m_pWindow->CalcDims(pPElement);

							m_pWindow->m_element = element;
#endif
						}
					}
					else
					{
						CPElement* pParentElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(this);

						if (pParentElement)
						{
							CPElement* pPElement = CreateElement(element);
							if (pPElement)
							{
								CComQIPtr<CLDOMElementImplImpl>(element)->m_pNodes.Add(pPElement);
								pPElement->m_parent = pParentElement;
								pPElement->BuildChildren();

								UPOSITION pos = pParentElement->m_childList.GetHeadPosition();

								CComPtr<ILDOMNode> child;
								parentNode->get_firstChild(&child);

								while (child)
								{
									if (child == targetNode)
										break;

									if (pos)
									{
										UPOSITION pos2 = pos;
										CPNode* pChild = (CPNode*)pParentElement->m_childList.GetNext(pos2);
										ASSERT(pChild->m_pNode != element);
										if (pChild->m_pNode == child)
										{
											pos = pos2;	// Okay, advance pos
										}
									}

									CComPtr<ILDOMNode> nextSibling;
									child->get_nextSibling(&nextSibling);
									child = nextSibling;
								}

								if (pos)
									pParentElement->m_childList.InsertBefore(pos, pPElement);
								else
									pParentElement->m_childList.AddTail(pPElement);

								pParentElement->BuildRenderChildren();

								pPElement->GetCSSPropertiesAndChildren();
								pPElement->SetValuesFromAttributes();	// ??
								CalcDims(pPElement);

								// ??
								pPElement->CalculateBoundsAndChildren();
								pPElement->m_parent->RecalculateParentBounds();

								if (CComQIPtr<ILSVGElement>(pPElement->m_pNode) != NULL)	// TODO remove
								{
									ASSERT(0);
#if 0
									gmMatrix3 ctm = ((CPSVGElementImpl*)pPElement)->GetScreenCTM();

									RectD xrect;
									GetTransformRectBoundingBox(ctm.inverse(), ((CPSVGElementImpl*)pPElement)->m_expandedBBox, &xrect);

									CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));
									m_pWindow->InvalidateRect(&rect);
#endif
								}
							}
						}
					}
				}
				else if (element && type == NOTIFY_REMOVE)
				{
					CComQIPtr<ILDOMDocument> document = parentNode;
					if (document)
					{
						m_pRootElement->Release();
						m_pRootElement = NULL;
						m_pWindow->m_pSVGElement = NULL;

						m_pWindow->m_element = NULL;
					}
					else
					{
						CPElement* pParentElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(this);

						if (pParentElement)
						{
							CPElement* pPElement = NULL;

							for (int i = 0; i < CComQIPtr<CLDOMElementImplImpl>(targetNode)->m_pNodes.GetSize(); i++)
							{
								if (CComQIPtr<CLDOMElementImplImpl>(targetNode)->m_pNodes[i]->m_pView == this)
								{
									pPElement = (CPElement*)CComQIPtr<CLDOMElementImplImpl>(targetNode)->m_pNodes[i];
									break;
								}
							}

							if (pPElement)
							{
								if (CComQIPtr<ILSVGElement>(pPElement->m_pNode) != NULL)	// TODO remove
								{
									ASSERT(0);
#if 0
									gmMatrix3 ctm = ((CPSVGElementImpl*)pPElement)->GetScreenCTM();

									RectD xrect;
									GetTransformRectBoundingBox(ctm.inverse(), ((CPSVGElementImpl*)pPElement)->m_expandedBBox, &xrect);

									CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));
									m_pWindow->InvalidateRect(&rect);
#endif
								}

								UPOSITION pos;
								
								pos = pParentElement->m_childList.Find(pPElement);
								pParentElement->m_childList.RemoveAt(pos);

								if (CComQIPtr<ILSVGElement>(pParentElement->m_pNode) != NULL)
								{
									ASSERT(0);
#if 0
									pos = ((CPSVGElementImpl*)pParentElement)->m_childListRender.Find(pPElement);
									if (pos)
									{
										((CPSVGElementImpl*)pParentElement)->m_childListRender.RemoveAt(pos);
									}
#endif
								}

								m_pWindow->RemovingElement(pPElement);
								pPElement->Release();

								pParentElement->RecalculateParentBounds();
							}
						}
					}
				}
				else// if (element)
				{
// TODO, improve this a lot, inserting a text node currently triggers this one

					
					CComQIPtr<ILDOMDocument> document = parentNode;
					if (document)
					{
						/*
						if (type == NOTIFY_REMOVE)
						{
							m_htmTree->Release();
							m_htmTree = NULL;
							m_pSVGElement = NULL;

							m_element = NULL;
						}
						else
						{
						}
						*/
					}
					else
					{
				//		CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(element)->GetNodeOnFrame(this);
						CPElement* pParentElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(this);

				//		pPElement->SetValuesFromAttributes();
				//		CalcDims(pPElement);

						if (pParentElement)
						{
							//pParentNode->RemoveBoxes();
							pParentElement->RemoveChildren();
							pParentElement->BuildChildren();

							pParentElement->GetCSSPropertiesAndChildren();
							pParentElement->SetValuesFromAttributes();	// ??
							CalcDims(pParentElement);
						}
					}
	//#endif
				}
			}
		}
#if 0	// Not needed on SVG??
		Flow();
#endif

		m_pWindow->m_lockPaint--;

		// Fix selection range
		if (m_pWindow->m_range)
		{
			CComPtr<ILDOMNode> startContainer;
			m_pWindow->m_range->get_startContainer(&startContainer);

			CComPtr<ILDOMNode> endContainer;
			m_pWindow->m_range->get_endContainer(&endContainer);

			//m_startContainer = m_htmTree->FindDOMElement(startContainer);
			//m_endContainer = m_htmTree->FindDOMElement(endContainer);

			//m_curContainer = m_htmTree->FindDOMElement(endContainer);	// ??
			//m_initContainer = m_htmTree->FindDOMElement(endContainer);	// ??

			//m_startContainer = 

		//	m_range->get_startOffset(&m_startOffset);
		//	m_range->get_endOffset(&m_endOffset);
		}

	}
	else if (m_pWindow->m_pFrameSet)
	{
		ASSERT(0);
#if 0
		m_pWindow->m_pFrameSet->PositionFrames();
#endif
	}

//	InvalidateRect(NULL);

	//FireOnChanged(type, targetObject, dispID);
	return S_OK;
}
#endif

HRESULT CXMLDocumentView::SetDocument(ILDOMDocument* document)
{
	m_document = document;
#if 0
	m_pDocument = static_cast<CLXUIDocument*>(document);
#endif

	CComPtr<ILDOMElement> documentElement;
	m_document->get_documentElement(&documentElement);

	ASSERT(documentElement);	// TODO

	if (documentElement)
	{
		m_pRootElement = CreateElement(documentElement);
		if (m_pRootElement)
		{
#if 0
			CPLXUILXUIElement* pLXUIElement = (CPLXUILXUIElement*)m_pRootElement;

			pLXUIElement->EnableShellOpen(m_pDocument->m_pszExeName);
#endif

			CComQIPtr<CLDOMElementImplImpl>(documentElement)->m_pNodes.Add(m_pRootElement);

			m_pRootElement->BuildChildren();
			m_pRootElement->GetCSSPropertiesAndChildren();
			m_pRootElement->BuildRenderChildren();
			CalcDims(m_pRootElement);	// ??
			m_pRootElement->CalculateBoundsAndChildren();

#if 0
			((CPLXUIElementImpl*)m_pRootElement)->ShowAndChildren();
#endif
		}
	}
	return S_OK;
}

#if 0

///.. this shouldn't be possible, CHTMFrame is connected
// to a HTMLFrameElement, not a ILDOMDocument, rename to SetHTMLFrameElement() ?
long CHTMLDocumentView::SetDocument(ILDOMDocument* document)
{
	/*
/////// hmmm...
	CComPtr<ILDOMDocument> document;
	m_frameElement->get_contentDocument(&document);
	*/

	if (m_document != document)	// TODO, better comparison ??
	{
		//ASSERT(0);
#if 0
		FreeImage();
#endif

		m_document = document;

		CComQIPtr<CLDOMDocumentImplImpl> documentImpl(m_document);
		
		documentImpl->AddView(this);

#if 0	// Experimental, remove this
		CComQIPtr<INotifySend> cp = m_document;
		ASSERT(cp);
		DWORD cookie;
		cp->Advise(this, &cookie);
#endif

#if 0	// Had this
		m_document->get_documentElement(&m_pWindow->m_element);
#endif

	//
		DoneParsing();
	}
	return 0;
}
#endif

void CHTMLDocumentView::DoneParsing()
{
#if 0	// Had this ??
	m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);
	ASSERT(m_cwnd.m_hWnd);
#endif

	/*
	if (m_timerWnd.m_hWnd == NULL)
	{
		m_timerWnd.m_pFrame = this;
		m_timerWnd.Create(NULL, CRect(0,0,0,0), NULL, WS_DISABLED, 0, 0, NULL);
	}
	*/

	bool editMode = VARIANT_FALSE;
	//m_documentContainer->get_editMode(&editMode);

	if (m_document)
	{
		CComPtr<ILDOMElement> documentElement;
		m_document->get_documentElement(&documentElement);

		if (TRUE)	// if (m_element)
		{
			{
				CComPtr<ILDOMNode> parentNode;
				documentElement->get_parentNode(&parentNode);
				ASSERT(parentNode == m_document);
			}

#if 0
			if (m_range == NULL)	// TODO, somewhere else
			{
				CComQIPtr<ILDOMDocumentRange> documentRange = m_document;
				if (documentRange)
				{
					documentRange->createRange(&m_range);
					CComQIPtr<INotifySend> cp = m_range;
					DWORD cookie;
					cp->Advise(this, &cookie);
				}
			}
#endif

			BSTR bnsURI;
			documentElement/*m_element*/->get_namespaceURI(&bnsURI);
			_bstr_t nsURI = _bstr_t(bnsURI, false);

			BSTR btagName;
			documentElement/*m_element*/->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"svg"))
			{
				ASSERT(0);
#if 0
				CComObject<CPSVGSVGElement>* pSVGSVGElement = (CComObject<CPSVGSVGElement>*)m_pView->CreateElement(documentElement);
				/*
				CComObject<CPSVGSVGElement>* pSVGSVGElement;
				CComObject<CPSVGSVGElement>::CreateInstance(&pSVGSVGElement);
				*/
				if (pSVGSVGElement)
				{
					//pSVGSVGElement->AddRef();

				//	pSVGSVGElement->m_pNode = documentElement;
					pSVGSVGElement->m_pWindow = this;

					CComQIPtr<CLDOMElementImplImpl>(documentElement)->m_pNodes.Add(pSVGSVGElement);

					pSVGSVGElement->BuildChildren();

					//m_pSVGElement = pSVGSVGElement;
					m_htmTree = pSVGSVGElement;//m_pSVGElement;

					m_pSVGElement = (CPSVGElementImpl*)m_htmTree->FindDOMElement(m_element);
					ASSERT(m_pSVGElement);
					m_pSVGElement->CreateBehaviors();	// TODO, don't do this here

					m_htmTree->GetCSSPropertiesAndChildren();

					m_htmTree->BuildRenderChildren();
					
					m_htmTree->SetValuesFromAttributes();	// ??

					//m_htmTree->CalculateDimensions(NULL);
					CalcDims(m_htmTree);

					// Create scrollbars
					//if (m_pUI->m_hWnd)
					if (m_pUI)
					{
						// vertical
						{
							CComPtr<IUIScrollBar> scroll;
							scroll.CoCreateInstance(CLSID_UIScrollBar);
							scroll->set_direction(1);

							CComObject<CCoClientObject>::CreateInstance(&m_scrollY);
							m_scrollY->AddRef();
							m_scrollY->m_spUnknown = scroll;
							m_scrollY->m_hWnd = m_pUI->m_hWnd;
							m_scrollY->m_pWindow = this;

							m_scrollY->Connect(FALSE, NULL);
							m_scrollY->ActivateAx();

							IDispEventImpl<2, CHTMLWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_scrollY->m_spUnknown);
						}

						// horizontal
						{
							CComPtr<IUIScrollBar> scroll;
							scroll.CoCreateInstance(CLSID_UIScrollBar);
							scroll->set_direction(0);

							CComObject<CCoClientObject>::CreateInstance(&m_scrollX);
							m_scrollX->AddRef();
							m_scrollX->m_spUnknown = scroll;
							m_scrollX->m_hWnd = m_pUI->m_hWnd;
							m_scrollX->m_pWindow = this;

							m_scrollX->Connect(FALSE, NULL);
							m_scrollX->ActivateAx();

							IDispEventImpl<3, CHTMLWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_scrollX->m_spUnknown);
						}
					}

				}

			//	m_pSVGDisplay->Run();
#endif
			}
			else if (!wcscmp(tagName, L"smil"))
			{
				ASSERT(0);
#if 0
				ASSERT(m_pSMILElement == NULL);

				CComObject<CPSMILElement>* pSMILElement = (CComObject<CPSMILElement>*)m_pView->CreateElement(documentElement);
				//CComObject<CPSMILElement>* pSMILElement;
				CComObject<CPSMILElement>::CreateInstance(&m_pSMILElement);
				if (pSMILElement)
				{
					m_pSMILElement = pSMILElement;
					m_htmTree = m_pSMILElement;
					//m_pSMILElement->AddRef();

					//m_pSMILElement->m_pNode = documentElement;
					//m_pSMILElement->m_pWindow = this;
					CComQIPtr<CLDOMElementImplImpl>(documentElement)->m_pNodes.Add(m_pSMILElement);	// TODO, not here

					m_pSMILElement->BuildChildren();

					m_pSMILElement->CreateBehaviors();

					m_htmTree->GetCSSPropertiesAndChildren();

					m_pSMILLayoutElement = NULL;

					CPElement* pHead = m_pSMILElement->GetElementByTagNameNS(L"http://www.w3.org/2001/SMIL20/Language", L"head", FALSE);
					if (pHead)
					{
						CPElement* pLayout = pHead->GetElementByTagNameNS(L"http://www.w3.org/2001/SMIL20/Language", L"layout", FALSE);
						if (pLayout)
						{
							m_pSMILLayoutElement = (CPSMILLayoutElement*)pLayout->GetElementByTagNameNS(L"http://www.w3.org/2001/SMIL20/Language", L"root-layout", FALSE);
						}
					}

// ?? getCSSProperties
					m_htmTree->CalculateDimensions(NULL);
//
				}

				/*
				m_pSMILDisplay = new CSMILDisplay;
				m_pSMILDisplay->m_pFrame = this;
				m_pSMILDisplay->Build(m_element);

				m_pSMILDisplay->Run();
				*/
				/*
				// Start playing document
				{
					m_totalIntendedTime = 0;

					LONG uDelay = (LONG)(1000/m_frameRate);

					m_videoTimeID = timeSetEvent(uDelay, 0, (LPTIMECALLBACK)PlaybackProc, (DWORD)this, TIME_PERIODIC);

					if (!m_videoTimeID)
					{
					//	m_bPlaying = FALSE;
					//	UpdateAllViews(NULL);

						MessageBox(NULL, "Video playback Timer could not be created", "", MB_OK);
					}
				}
				*/
#endif
			}
			else if (!wcscmp(nsURI, L"http://www.w3.org/1999/XSL/Format"))
			{
				ASSERT(0);
#if 0
				m_pFODisplay = new CFODisplay;
				m_pFODisplay->m_pFrame = this;

				m_pFODisplay->Build(m_element);

				/*
				CFOPage* pFOPage = new CFOPage;
				pFOPage->m_width = 100;
				pFOPage->m_height = 100;

				m_pFODisplay->m_pages.Add(pFOPage);
				*/
#endif
			}
			else
			{
				ASSERT(0);
#if 0
	#if 0
				if (!editMode)
				{
					HRESULT hr = m_activeScript->AddNamedItem(L"globalwindow2", SCRIPTITEM_ISVISIBLE | SCRIPTITEM_ISSOURCE);
					ASSERT(SUCCEEDED(hr));

					AddNamedElements(m_activeScript, documentElement);
				}
	#endif

				/*
				bool isXML;
				m_document->get_isXML(&isXML);

				CComQIPtr<ILHTMLElement> pFrameSetElement = FindByTagName(m_element, L"frameset", isXML, FALSE);
				*/
				CComQIPtr<ILHTMLFrameSetElement> frameSetElement;

				CComQIPtr<ILHTMLDocument> htmlDocument = m_document;
				if (htmlDocument)
				{
					CComPtr<ILHTMLElement> element;
					htmlDocument->get_body(&element);

					frameSetElement = element;
				}

				if (frameSetElement)
				{
					ASSERT(0);
#if 0
					CComObject<CPHTMLFrameSetElement>::CreateInstance(&m_pFrameSet);
					m_pFrameSet->AddRef();

#if 0	// Had this ???
					m_pFrameSet->m_pUI = m_pUI;
#endif
				//	m_pFrameSet->m_pParentFrame = this;
					m_pFrameSet->m_pParentWindow = this;
					ASSERT(0);
#if 0
					m_pFrameSet->CreateFrames(frameSetElement, m_pFrame/*this*/ );
#endif
#endif
				}
				else
				{
					//m_lockPaint++;
					{
						//if (m_htmTree == NULL)	// ??
						{
						//	delete m_htmTree;
						//	m_htmTree = NULL;

							CComQIPtr<ILDOMDocument> document = m_document;
							if (document)
							{
								if (documentElement != NULL)
								{
									m_pRootElement = (CComObject<CPHTMElement>*)CreateElement(documentElement/*m_element*/);
									if (m_pRootElement)
									{
										CComQIPtr<CLDOMElementImplImpl>(documentElement/*m_element*/)->m_pNodes.Add(m_pRootElement/*m_htmTree*/);

										//m_htmTree->m_computedDisplay = Display_block;	// hm..
										m_pRootElement->BuildChildren();
										//m_htmTree->m_computedDisplay = Display_block;	// hm..
										m_pRootElement->BuildRenderChildren();

										m_pRootElement->GetCSSPropertiesAndChildren();	// ??

										/*
										{
											CUString msg;
											msg.Format("%d", end-start);
											MessageBox(NULL, msg, "", MB_OK);
										}
										*/

#if 0
										m_htmTree->CreateBehaviors();	// TODO, don't do this here
#endif

										CalcDims(m_pRootElement);

									//	ATLTRACE("fontFamilies: %d\nfonts: %d\n", m_gdipFontFamilies.GetSize(), m_gdipFonts.GetSize());
									}
								}
							}
						}
					}
				}

			//	m_lockPaint--;

				//m_spScriptSite->m_pFire_onload();
	#if 0
				m_pHTMLWindowImpl->Fire_onload();
	#endif
#endif
			}

#if 0
			Flow();	// call this here ??
#endif
		}
	}

#if 0
	m_pRootElement = m_htmTree;
#endif

	if (FALSE)
	{
#if 0
		CComPtr<ISpVoice> voiceText;
		voiceText.CoCreateInstance(CLSID_SpVoice);

	//	voiceText->Register ("", "Demo Application", NULL, IID_IVTxtNotifySink, NULL, NULL);

	//Applications have to call Register so the voice text knows the name of the application and to what audio device the speech will be played, since some applications will be telephone aware. Also, an application can provide a notification sink so that it's alerted when speaking starts or stops, but this isn't necessary.

//The next step is to send out text to be spoken.

		voiceText->Speak (L"Hello world.", 0, NULL);

		//Finally, when the application is finished using voice text it releases the object.
#endif
	}
}
#endif

}	// LXML
#endif