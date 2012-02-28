#pragma once

//#import "..\LSMILTransitions\LSMILTransitions.tlb" no_namespace, raw_interfaces_only, named_guids

#include "SVGElementsListView.h"

namespace System
{
namespace LXmlEdit
{

class CSVGDefinitionsDlgTBase
{
public:
	CSVGDefinitionsDlgTBase()
	{
	}
};

void DrawPaintNone(MSWindows::HDC hDC, LDraw::BBoxi& rc, LDraw::BBoxi& rc2);

template <class T> class CSVGDefinitionsDlgT :
	public UI::Control,
//	public CUIDialogImpl<T, CWindowImpl<T> >,
	public CSVGDefinitionsDlgTBase
{
public:
	CSVGDefinitionsDlgT()
	{
		m_app = NULL;

		m_progress = 0.5;
	}

	CLXMLEditorApp* m_app;

	int m_type;

	double m_progress;	// For transitions

	CSVGElementListView m_listView;
//	CScrollBar m_sizeGrip;

//	CComPtr<ILSMILTransitionFactory> m_transitionFactory;

	/*
BEGIN_MSG_MAP(CSVGDefinitionsDlgT)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
END_MSG_MAP()
*/

#if 0
	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LDraw::BBoxi rc(0,0,0,0);

		m_listView.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD, 0, 1/*nID*/);

		m_sizeGrip.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);//, , m_hWnd, 1/*NULL, _Module.m_hInst, NULL*/);

		return 0;
	}

	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_listView.DestroyWindow();
		m_sizeGrip.DestroyWindow();
		return 0;
	}

	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LDraw::BBoxi client;
		GetClientRect(&client);

		m_listView.MoveWindow(0, 0, client.right, client.bottom-16);
		m_sizeGrip.MoveWindow(client.right-16, client.bottom-16, 16, 16);

		return 0;
	}
#endif
	void AddItems()
	{
		ASSERT(0);
#if 0
		if (m_type == 0)	// Swatches
		{
			// Add solidColors
			{
				CComPtr<ILDOMNodeList> nodeList;
				m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"solidColor", &nodeList);
				if (nodeList)
				{
					long length;
					nodeList->get_length(&length);

					for (int i = 0; i < length; i++)
					{
						CComPtr<ILSVGElement> element;

						nodeList->item(i, (ILDOMNode**)&element);

						/*
						CComQIPtr<ILDOMEventTarget> eventTarget = element;
						eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
						*/

						CComBSTR id;
						element->getAttribute(L"id", &id);

						m_listView.AddItem((DWORD)element.p, id);
					}
				}
			}

			// Add linearGradients
			{
				CComPtr<ILDOMNodeList> nodeList;
				m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"linearGradient", &nodeList);
				if (nodeList)
				{
					long length;
					nodeList->get_length(&length);

					for (int i = 0; i < length; i++)
					{
						CComPtr<ILSVGElement> element;

						nodeList->item(i, (ILDOMNode**)&element);

						/*
						CComQIPtr<ILDOMEventTarget> eventTarget = element;
						eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
						*/

						CComBSTR id;
						element->getAttribute(L"id", &id);

						m_listView.AddItem((DWORD)element.p, id);
					}
				}
			}

			// Add radialGradients
			{
				CComPtr<ILDOMNodeList> nodeList;
				m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"radialGradient", &nodeList);
				if (nodeList)
				{
					long length;
					nodeList->get_length(&length);

					for (int i = 0; i < length; i++)
					{
						CComPtr<ILSVGElement> element;
						nodeList->item(i, (ILDOMNode**)&element);

						/*
						CComQIPtr<ILDOMEventTarget> eventTarget = element;
						eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
						*/

						CComBSTR id;
						element->getAttribute(L"id", &id);

						m_listView.AddItem((DWORD)element.p, id);
					}
				}
			}

			// Add patterns
			{
				CComPtr<ILDOMNodeList> nodeList;
				m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"pattern", &nodeList);
				if (nodeList)
				{
					long length;
					nodeList->get_length(&length);

					for (int i = 0; i < length; i++)
					{
						CComPtr<ILSVGElement> element;
						nodeList->item(i, (ILDOMNode**)&element);

						/*
						CComQIPtr<ILDOMEventTarget> eventTarget = element;
						eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
						*/

						CComBSTR id;
						element->getAttribute(L"id", &id);

						m_listView.AddItem((DWORD)element.p, id);
					}
				}
			}
		}
		else if (m_type == 1)	// Filters
		{
			CComPtr<ILDOMNodeList> nodeList;
			m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"filter", &nodeList);
			if (nodeList)
			{
				long length;
				nodeList->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<ILSVGElement> element;
					nodeList->item(i, (ILDOMNode**)&element);

					/*
					CComQIPtr<ILDOMEventTarget> eventTarget = element;
					eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
					*/
					CComBSTR id;
					element->getAttribute(L"id", &id);

					m_listView.AddItem((DWORD)element.p, id);
				}
			}
		}
		else if (m_type == 2)	// Symbols
		{
			CComPtr<ILDOMNodeList> nodeList;
			m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"symbol", &nodeList);
			if (nodeList)
			{
				long length;
				nodeList->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<ILSVGElement> element;
					nodeList->item(i, (ILDOMNode**)&element);

					/*
					CComQIPtr<ILDOMEventTarget> eventTarget = element;
					eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
					*/

					m_listView.AddItem((DWORD)element.p);
				}
			}
		}
		else if (m_type == 3)	// Masks
		{
			CComPtr<ILDOMNodeList> nodeList;
			m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"mask", &nodeList);
			if (nodeList)
			{
				long length;
				nodeList->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<ILSVGElement> element;
					nodeList->item(i, (ILDOMNode**)&element);

					/*
					CComQIPtr<ILDOMEventTarget> eventTarget = element;
					eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
					*/

					CComBSTR id;
					element->getAttribute(L"id", &id);

					m_listView.AddItem((DWORD)element.p, id);
				}
			}
		}
		else if (m_type == 4)	// ClipPaths
		{
			CComPtr<ILDOMNodeList> nodeList;
			m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2000/svg", L"clipPath", &nodeList);
			if (nodeList)
			{
				long length;
				nodeList->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<ILSVGElement> element;
					nodeList->item(i, (ILDOMNode**)&element);

					/*
					CComQIPtr<ILDOMEventTarget> eventTarget = element;
					eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
					*/

					CComBSTR id;
					element->getAttribute(L"id", &id);

					m_listView.AddItem((DWORD)element.p, id);
				}
			}
		}
		else if (m_type == 5)	// Markers
		{
		}
		else if (m_type == 6)	// SMIL Transitions
		{
			CComPtr<ILDOMNodeList> nodeList;
			m_listView.m_xmlDocument->getElementsByTagNameNS(L"http://www.w3.org/2001/SMIL20/Language", L"transition", &nodeList);
			if (nodeList)
			{
				long length;
				nodeList->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<ILSVGElement> element;
					nodeList->item(i, (ILDOMNode**)&element);

					/*
					CComQIPtr<ILDOMEventTarget> eventTarget = element;
					eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
					*/

					CComBSTR id;
					element->getAttribute(L"id", &id);

					m_listView.AddItem((DWORD)element.p, id);
				}
			}
		}
#endif
	}

	long OnDrawItem()
	{
					ATLASSERT(0);
#if 0
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;

		HDC hDC = lpdis->hDC;
		LDraw::BBoxi& rc = *(LDraw::BBoxi*)&lpdis->rcItem;

		int x2 = rc.left;
		int y2 = rc.top;
		int twidth = rc.Width();
		int theight = rc.Height();

		CSVGListViewItem* pItem = (CSVGListViewItem*)lpdis->itemData;

		ILDOMElement* element = (ILDOMElement*)pItem->m_element;

		if (pItem->m_thumbnailBitmap)
		{
			BITMAP bm;
			::GetObject(pItem->m_thumbnailBitmap, sizeof(bm), &bm);

			if (twidth != bm.bmWidth || theight != bm.bmHeight)
			{
				DeleteObject(pItem->m_thumbnailBitmap);
				pItem->m_thumbnailBitmap = NULL;
			}
		}

		if (element)
		{
			if (pItem->m_thumbnailBitmap == NULL)
			{
				CComBSTR tagName;
				element->get_tagName(&tagName);

				if (!wcscmp(tagName, L"filter"))
				{
					CComPtr<IUnknown> spUnknown;
					HRESULT hr = CoCreateInstance(CLSID_LHTMLActiveDocument, NULL, CLSCTX_ALL, IID_IUnknown, (void**)&spUnknown);

					CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = spUnknown;

					CComQIPtr<IOleDocument> oleDocument = spUnknown;

					CComPtr<IOleDocumentView> oleView;

					oleDocument->CreateView(NULL,// *pIPSite,
						NULL,///* [unique][in] */ IStream __RPC_FAR *pstm,
						0,///* [in] */ DWORD dwReserved,
						&oleView);

					CComQIPtr<ILHTMLActiveView> htmlView = oleView;

					LDraw::BBoxi rect(0, 0, twidth, theight);
					oleView->SetRect(&rect);

					LSVG::SVGDocument* svgDocument;
					svgDocument.CoCreateInstance(CLSID_LSVGDocument);

					VARIANT_BOOL bsuccess;
					svgDocument->loadXML(L"<svg/>", &bsuccess);

					CComPtr<ILDOMElement> documentElement;
					svgDocument->get_documentElement(&documentElement);

					_bstr_t id;
					if (pItem->m_element)
					{
						BSTR bid;
						element->getAttribute(L"id", &bid);
						id = _bstr_t(bid, false);

						CComPtr<ILSVGFilterElement> filterElement;
						svgDocument->importNode(element, VARIANT_TRUE, (ILDOMNode**)&filterElement);
						documentElement->appendChild(filterElement, NULL);
					}

					CComPtr<ILSVGRectElement> testElement;
					svgDocument->createElement(L"rect", (ILDOMElement**)&testElement);
					if (testElement)
					{
						long x = (twidth)*1/5;
						long y = (theight)*1/5;
						long width = twidth-x-x;
						long height = theight-y-y;
						long rx = width/5;
						long ry = height/5;

						testElement->setAttribute(L"x", _bstr_t(_variant_t(x)));
						testElement->setAttribute(L"y", _bstr_t(_variant_t(y)));
						testElement->setAttribute(L"width", _bstr_t(_variant_t(width)));
						testElement->setAttribute(L"height", _bstr_t(_variant_t(height)));
						testElement->setAttribute(L"rx", _bstr_t(_variant_t(rx)));
						testElement->setAttribute(L"ry", _bstr_t(_variant_t(ry)));

						_bstr_t style;
						if (pItem->m_element)
						{
							style = L"fill:#0000ff; stroke:none; filter:url(#" + id + L")";
						}
						else
						{
							style = L"fill:#ffffff; stroke:#000000; stroke-width:1;";
						}

						testElement->setAttribute(L"style", style);

						documentElement->appendChild(testElement, NULL);
					}

					htmlActiveDoc->SetDocument(svgDocument);

					CComPtr<ILHTMLWindow> window;
					htmlView->GetHTMLWindow(&window);

					BITMAPINFO bmi = {0};
					bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					bmi.bmiHeader.biWidth = twidth;
					bmi.bmiHeader.biHeight = -theight;
					bmi.bmiHeader.biBitCount = 24;
					bmi.bmiHeader.biPlanes = 1;

					HBITMAP hTBitmap;
					LPBYTE TBits = NULL;

					if (hTBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
					{
						HDC hTDC = CreateCompatibleDC(NULL);
						HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

						FillSolidRect(hTDC, 0, 0, twidth, theight, RGB(255, 255, 255));

						window->DrawToHdc(hTDC, testElement, 1);

						BitBlt(hDC, x2, y2, twidth, theight, hTDC, 0, 0, SRCCOPY);

						SelectObject(hTDC, hOldBitmap);
						DeleteDC(hTDC);

						pItem->m_thumbnailBitmap = hTBitmap;
					}
				}
				else if (!wcscmp(tagName, L"solidColor") ||
					!wcscmp(tagName, L"linearGradient") ||
					!wcscmp(tagName, L"radialGradient") ||
					!wcscmp(tagName, L"pattern"))
				{
					BSTR bid;
					element->getAttribute(L"id", &bid);
					_bstr_t id = _bstr_t(bid, false);

					CComPtr<IUnknown> spUnknown;
					HRESULT hr = CoCreateInstance(CLSID_LHTMLActiveDocument, NULL, CLSCTX_ALL, IID_IUnknown, (void**)&spUnknown);

					CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = spUnknown;

					CComQIPtr<IOleDocument> oleDocument = spUnknown;

					CComPtr<IOleDocumentView> oleView;

					oleDocument->CreateView(NULL,// *pIPSite,
						NULL,///* [unique][in] */ IStream __RPC_FAR *pstm,
						0,///* [in] */ DWORD dwReserved,
						&oleView);

					CComQIPtr<ILHTMLActiveView> htmlView = oleView;

					LDraw::BBoxi rect(0, 0, twidth, theight);
					oleView->SetRect(&rect);

					LSVG::SVGDocument* svgDocument;
					svgDocument.CoCreateInstance(CLSID_LSVGDocument);

					VARIANT_BOOL bsuccess;
					svgDocument->loadXML(L"<svg/>", &bsuccess);

					CComPtr<ILDOMElement> documentElement;
					svgDocument->get_documentElement(&documentElement);

					CComPtr<ILSVGElement> swatchElement;
					svgDocument->importNode(element, VARIANT_TRUE, (ILDOMNode**)&swatchElement);
					documentElement->appendChild(swatchElement, NULL);

					CComPtr<ILSVGRectElement> rectElement;
					svgDocument->createElement(L"rect", (ILDOMElement**)&rectElement);

					rectElement->setAttribute(L"x", L"-1");
					rectElement->setAttribute(L"y", L"-1");
					rectElement->setAttribute(L"width", _bstr_t(_variant_t(long(twidth+2))));
					rectElement->setAttribute(L"height", _bstr_t(_variant_t(long(theight+2))));

					_bstr_t style;
					style = L"stroke:none; fill:url(#" + id + L")";
					rectElement->setAttribute(L"style", style);

					documentElement->appendChild(rectElement, NULL);

					htmlActiveDoc->SetDocument(svgDocument);

					CComPtr<ILHTMLWindow> window;
					htmlView->GetHTMLWindow(&window);

					BITMAPINFO bmi = {0};
					bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					bmi.bmiHeader.biWidth = twidth;
					bmi.bmiHeader.biHeight = -theight;
					bmi.bmiHeader.biBitCount = 24;
					bmi.bmiHeader.biPlanes = 1;

					HBITMAP hTBitmap;
					LPBYTE TBits = NULL;

					if (hTBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
					{
						HDC hTDC = CreateCompatibleDC(NULL);
						HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

						FillSolidRect(hTDC, 0, 0, twidth, theight, RGB(255, 255, 255));

						window->DrawToHdc(hTDC, rectElement, 1);

						BitBlt(hDC, x2, y2, twidth, theight, hTDC, 0, 0, SRCCOPY);

						SelectObject(hTDC, hOldBitmap);
						DeleteDC(hTDC);

						pItem->m_thumbnailBitmap = hTBitmap;
					}
				}
				else if (!wcscmp(tagName, L"transition"))
				{
					if (m_transitionFactory == NULL)
					{
						m_transitionFactory.CoCreateInstance(CLSID_LSMILTransitionFactory);
					}

					if (m_transitionFactory)
					{
						CComQIPtr<ILSMILTransitionElement> transitionElement = element;
						if (transitionElement)
						{
							LTransitionDirection direction;
							long horzRepeat;
							long vertRepeat;
							CComBSTR type;
							CComBSTR subtype;

							transitionElement->get_direction(&direction);
							transitionElement->get_horzRepeat(&horzRepeat);
							transitionElement->get_vertRepeat(&vertRepeat);
							transitionElement->getAttribute(L"type", &type);
							transitionElement->getAttribute(L"subtype", &subtype);

							if (type != NULL)
							{
								Gdiplus::Rect mediaRect(0, 0, twidth, theight);

								Gdiplus::Bitmap* pBitmapA;
								Gdiplus::Bitmap* pBitmapB;
								double progress;

								if (direction == TRANSITION_DIRECTION_FORWARD)
								{
									pBitmapA = new Gdiplus::Bitmap((HINSTANCE)_Module.GetResourceInstance(), (const WCHAR*)MAKEINTRESOURCE(IDB_BITMAPA));
									pBitmapB = new Gdiplus::Bitmap((HINSTANCE)_Module.GetResourceInstance(), (const WCHAR*)MAKEINTRESOURCE(IDB_BITMAPB));
									progress = m_progress;
								}
								else
								{
									pBitmapB = new Gdiplus::Bitmap((HINSTANCE)_Module.GetResourceInstance(), (const WCHAR*)MAKEINTRESOURCE(IDB_BITMAPA));
									pBitmapA = new Gdiplus::Bitmap((HINSTANCE)_Module.GetResourceInstance(), (const WCHAR*)MAKEINTRESOURCE(IDB_BITMAPB));
									progress = 1-m_progress;
								}

								Gdiplus::Bitmap* pResultBitmap = new Gdiplus::Bitmap((int)mediaRect.Width, (int)mediaRect.Height);
								if (pResultBitmap)
								{
									{
										_RectD rectA;
										rectA.X = 0;
										rectA.Y = 0;
										rectA.Width = pBitmapA->GetWidth();
										rectA.Height = pBitmapA->GetHeight();

										_RectD rectB;
										rectB.X = 0;
										rectB.Y = 0;
										rectB.Width = pBitmapB->GetWidth();
										rectB.Height = pBitmapB->GetHeight();

										_RectD rect;
										rect.X = 0;
										rect.Y = 0;
										rect.Width = mediaRect.Width;
										rect.Height = mediaRect.Height;

										CComPtr<ILSMILTransition> transition;
										m_transitionFactory->FindTransition(type, subtype, &transition);
										if (transition)
										{
											m_transitionFactory->ProcessTransition(transition,
												horzRepeat, vertRepeat,
												NULL, NULL,
												progress,
												rectA, (long)pBitmapA,
												rectB, (long)pBitmapB,
												rect, (long)pResultBitmap);
										}
									}

									{
										BITMAPINFO bmi = {0};
										bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
										bmi.bmiHeader.biWidth = twidth;
										bmi.bmiHeader.biHeight = -theight;
										bmi.bmiHeader.biBitCount = 24;
										bmi.bmiHeader.biPlanes = 1;

										HBITMAP hTBitmap;
										LPBYTE TBits = NULL;

										if (hTBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
										{
											HDC hTDC = CreateCompatibleDC(NULL);
											HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

											//FillSolidRect(hTDC, 0, 0, twidth, theight, RGB(255, 255, 255));

											//window->DrawToHdc(hTDC, rectElement, 1);

											{
												Gdiplus::Graphics graphics(hTDC);

												graphics.DrawImage(pResultBitmap,
													Gdiplus::Rect(0, 0, twidth, theight),
													0, 0, pResultBitmap->GetWidth(), pResultBitmap->GetHeight(),
													Gdiplus::UnitPixel,
													NULL);
											}

											//BitBlt(hDC, x2, y2, twidth, theight, hTDC, 0, 0, SRCCOPY);

											SelectObject(hTDC, hOldBitmap);
											DeleteDC(hTDC);

											pItem->m_thumbnailBitmap = hTBitmap;
										}
									}

									delete pResultBitmap;
								}

								delete pBitmapA;
								delete pBitmapB;
							}
						}
					}
				}
			}

			if (pItem->m_thumbnailBitmap)
			{
				HDC hTDC = CreateCompatibleDC(NULL);
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, pItem->m_thumbnailBitmap);

				BitBlt(hDC, x2, y2, twidth, theight, hTDC, 0, 0, SRCCOPY);

				SelectObject(hTDC, hOldBitmap);
				DeleteDC(hTDC);
			}
		}
		else
		{
			if (!wcscmp(pItem->m_name, L"[none]"))
			{
				DrawPaintNone(hDC, rc, LDraw::BBoxi(0,0,0,0));
			}
			else
			{
			}
		}
#endif

		return 0;
	}
};

}	// LXmlEdit
}
