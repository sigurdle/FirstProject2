#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#if 0
#if 0

#include "XMLKeyFrameValuesDlg.h"

//void SetPathNodeValue(ILDOMElement* contextElement, BSTR path, BSTR value);

#include "..\LHTML\WCharString.h"

void GetPathNode(ILDOMElement* contextElement, BSTR path, ILDOMNode* *pVal)
{
	*pVal = NULL;

	WCHAR* p = path;

	//while (*p)
	{
		BOOL bAttribute = FALSE;
		if (*p == L'@')
		{
			bAttribute = TRUE;
			p++;
		}
	
		CWCharString part = L"";
	// Get part
		while (*p && *p != '/')
		{
			part += *p++;
		}

		CComPtr<ILDOMNode> node;

		if (bAttribute)
		{
			CComPtr<ILDOMAttr> attrNode;
			contextElement->getAttributeNode(part, &attrNode);

			node = attrNode;

			*pVal = node;
			if (*pVal) (*pVal)->AddRef();
		}
		else
		{
			ILDOMElement* childElement = GetElementByTagName(contextElement, part, FALSE);

			if (childElement)
			{
				if (*p == '/')	// Recurse
				{
					p++;

					GetPathNode(childElement, p, &node);
				}
				else
				{
					*pVal = childElement;
					(*pVal)->AddRef();
				}
			}
		}
	}
}

void SetPathNodeValue(ILDOMElement* contextElement, BSTR path, BSTR value)
{
	WCHAR* p = path;

	BOOL bAttribute = FALSE;
	if (*p == L'@')
	{
		bAttribute = TRUE;
		p++;
	}

	CWCharString part = L"";
// Get part
	while (*p && *p != '/')
	{
		part += *p++;
	}

	CComPtr<ILDOMNode> node;

	if (bAttribute)
	{
		if (value != NULL)
			contextElement->setAttribute(part, value);
		else
			contextElement->removeAttribute(part);
	}
	else
	{
		if (value != NULL)
		{
			CComPtr<ILDOMElement> element = GetElementByTagName(contextElement, part, FALSE);
			if (element == NULL)
			{
				CComPtr<ILDOMDocument> ownerDocument;
				contextElement->get_ownerDocument(&ownerDocument);

				ownerDocument->createElement(part, &element);

				contextElement->appendChild(element, NULL);
			}

			if (*p == '/')	// Recurse
			{
				p++;

				SetPathNodeValue(element, p, value);
			}
			else
			{
				element->put_TextContent(value);
			}
		}
		else
		{
			CComPtr<ILDOMElement> element = GetElementByTagName(contextElement, part, FALSE);
			if (element)
			{
				if (*p == '/')	// Recurse
				{
					p++;

					SetPathNodeValue(element, p, value);
				}
				else
				{
					element->put_TextContent(NULL);
				}

				CComPtr<ILDOMNode> child;
				element->get_firstChild(&child);
				if (child == NULL)	// No children, remove the element
				{
					contextElement->removeChild(element, NULL);
				}
			}
		}
	}
}

HRESULT GetPathNodeValue(ILDOMElement* element, BSTR path, BSTR* pVal)
{
	CComPtr<ILDOMNode> node;
	::GetPathNode(element, path, &node);

	if (node)
	{
		CComQIPtr<ILDOMAttr> attr = node;
		if (attr)
		{
			CComBSTR value;
			attr->get_value(&value);

			*pVal = value.Detach();
			return S_OK;
		}
		else
		{
			CComBSTR value;
			node->get_textContent(&value);

			*pVal = value.Detach();
			return S_OK;
		}
	}

	*pVal = NULL;
	return S_OK;
}
#endif

////////////////////////////////////////////////////////////////////
// CXMLKeyFrameValuesDlg

// virtual
BOOL CXMLKeyFrameValuesDlg::PathNodeExists(BSTR path)
{
	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

#if 0
	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<ILDOMNode> node;
		::GetPathNode(domElement, path, &node);

		if (node == NULL)
		{
			return FALSE;
		}
	}
#endif

	return TRUE;
}

// virtual
HRESULT CXMLKeyFrameValuesDlg::SetPathNodeValue(BSTR path, BSTR value)
{
	//CComPtr<IESelectedAnimationElement> selectedElement;

	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

	//	::SetPathNodeValue(domElement, path, value);

		CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

		//if (wcscmp(attributeName, 
		if (selectedAnimationElement)//TRUE)	// TODO
		{
			//CComQIPtr<ILSMILAnimationTarget> animationTarget = animationTarget;

			CComQIPtr<ILAnimateXXX> animateXXX = domElement;

			long ncount;
			selectedAnimationElement->GetSelectedKeyTimesCount(&ncount);

			for (int i = 0; i < ncount; i++)
			{
				long keyFrame;
				selectedAnimationElement->GetKeyTimeSelected(i, &keyFrame);

				CComPtr<ILSMILAttributeValue> attributeValue;
				animateXXX->GetValue(keyFrame, &attributeValue);

				attributeValue->setStringValue(value);
			}
		}
	}

	return S_OK;
}

HRESULT CXMLKeyFrameValuesDlg::SetPathNodeValueIfNotExists(BSTR path, BSTR value)
{
#if 0
	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<ILDOMNode> node;
		::GetPathNode(domElement, path, &node);

		if (node == NULL)
		{
			::SetPathNodeValue(domElement, path, value);
		}
	}
#endif

	return S_OK;
}

HRESULT CXMLKeyFrameValuesDlg::GetPathNodeValue(BSTR path, BSTR* pVal)
{
#if 0
	CComPtr<IESelectedAnimationElement> selectedElement;

	long ncount;
	selectedElement->GetSelectedKeyTimesCount(&ncount);

	CComBSTR value;

	for (int i = 0; i < ncount; i++)
	{
		long keyFrame;
		selectedElement->GetKeyTimeSelected(i, &keyFrame);

		ILSMILAnimationTarget* animationTarget;

		CComPtr<ILAnimateXXXElement> animateXXX;

		//CComPtr<ILSMILXMLAttr> attr;
		//animationTarget->animatableXMLAttrItemByName(L"", &attribute);

		CComPtr<ILSMILAttributeValue> attributeValue;
		animateXXX->GetValue(keyFrame, &attributeValue);

		CComBSTR value2;
		attributeValue->getStringValue(&value2);

		if (i == 0)
		{
			value = value2;
		}
		else if (wcscmp(value, value2))
		{
			value.Empty();
			break;
		}
	}
#endif

	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComBSTR attributeName;
		domElement->getAttribute(L"attributeName", &attributeName);

		CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

		//if (wcscmp(attributeName, 
		if (selectedAnimationElement)//TRUE)	// TODO
		{
			//CComQIPtr<ILSMILAnimationTarget> animationTarget = animationTarget;

			CComQIPtr<ILAnimateXXX> animateXXX = domElement;

			long ncount;
			selectedAnimationElement->GetSelectedKeyTimesCount(&ncount);

			CComBSTR value;

			for (int i = 0; i < ncount; i++)
			{
				long keyFrame;
				selectedAnimationElement->GetKeyTimeSelected(i, &keyFrame);

				//CComPtr<ILSMILXMLAttr> attr;
				//animationTarget->animatableXMLAttrItemByName(L"", &attribute);

				CComPtr<ILSMILAttributeValue> attributeValue;
				animateXXX->GetValue(keyFrame, &attributeValue);

				CComBSTR value2;
				if (attributeValue)
					attributeValue->getStringValue(&value2);

				if (i == 0)
				{
					value = value2;
				}
				else if (cmpbstr(value, value2))
				{
					value.Empty();
					break;
				}
			}

			*pVal = value.Detach();
			return S_OK;
		}

/*
		CComBSTR value2;
		::GetPathNodeValue(domElement, path, &value2);

		if (i == 0)
		{
			value = value2;
		}
		else if (wcscmp(value, value2))
		{
			value.Empty();
			break;
		}
		*/
	}


	return S_OK;
}

void CXMLKeyFrameValuesDlg::UpdateData(CXMLData* pData)
{
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		CComBSTR value;
		GetPathNodeValue(pData->m_name, &value);

#if 0
		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			CComBSTR value2 = pData->GetDataValue(domElement);

			if (i == 0)
			{
				value = value2;
			}
			else if (wcscmp(value, value2))
			{
				value.Empty();
				break;
			}
		}
#endif

		pData->SetValue(value);

		m_reentrancy--;
	}
}

// virtual
void CXMLKeyFrameValuesDlg::OnDataValueChanged(CXMLData* pData)
{
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

		_bstr_t value = pData->GetValueAsString();

		if (value.length())
			SetPathNodeValue(pData->m_name, value);
		else
			SetPathNodeValue(pData->m_name, NULL);

		m_reentrancy--;
	}
}

#if 0
//virtual
void CXMLKeyFrameValuesDlg::OnControlValueChanged(CControl* pControl)
{
	for (int i = 0; i < pControl->m_dataConnections.GetSize(); i++)
	{
		CDataConnection* pDataConnection = pControl->m_dataConnections[i];

		_bstr_t value = pControl->GetProperty(pDataConnection->m_propertyName);
		pDataConnection->m_pData->SetValue(value);
	}

	if (m_pControlsHandler)
	{
		m_pControlsHandler->OnUIValueChanged(pControl);
	}
}

LRESULT CXMLKeyFrameValuesDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	dc.SetBkMode(TRANSPARENT);

	CRect client;
	GetClientRect(&client);

	int y = 0;

	for (int i = 0; i < m_controls.GetSize(); i++)
	{
		CControl* pControl = m_controls[i];

		if (pControl->m_bVisible)
		{
		//	CXMLAttribute* pAttr = pControl->m_pAttr;

			CRect itemrect(0, y, client.right, y+pControl->m_height);

			CRect trect = itemrect;
			trect.right = 80;

			dc.DrawText(pControl->m_name, pControl->m_name.GetLength(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

			CRect vrect = itemrect;
			vrect.left = 82;

			pControl->Draw(dc.m_hDC, vrect);

			y += pControl->m_height;
			y += 1;	// Spacing
		}
	}

	dc.SelectFont(hOldFont);

	return 0;
}

LRESULT CXMLKeyFrameValuesDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_pActiveControl)
	{
		m_pActiveControl->Deactivate();
	}

	CRect m_areaRect;
	GetClientRect(&m_areaRect);

	int m_splitx = 82;

	long scrollposY = 0;

	int y = 0;

	int top;

	for (int i = 0; i < m_controls.GetSize(); i++)
	{
		CXMLControl* pControl = m_controls[i];

		if (pControl->m_bVisible)
		{
			top = y;

			y += pControl->m_height;

			if (point.y < y)
			{
				break;
			}

			y += 1;	// Spacing
		}
	}

	if (i < m_controls.GetSize())
	{
		CXMLControl* pControl = m_controls[i];

		if (point.x >= 82)
		{
			int rctop = m_areaRect.top + top - scrollposY;
			CRect rect(m_splitx, rctop, m_areaRect.right, rctop + pControl->m_height);

			if (pControl->m_bEnabled)
			{
				m_pActiveControl = pControl;

				CPoint pt = point;
				pt.x -= rect.left;
				pt.y -= rect.top;

				BOOL bDoDrag = pControl->Activate(m_hWnd, pt, rect);

				if (bDoDrag)
				{
					SetCapture();

					MSG msg;
					while (GetMessage(&msg, NULL, 0, 0))
					{
						TranslateMessage(&msg);

						switch (msg.message)
						{
						case WM_MOUSEMOVE:
							{
								pt.x = (short)LOWORD(msg.lParam);
								pt.y = (short)HIWORD(msg.lParam);
								pt.x -= rect.left;
								pt.y -= rect.top;

								m_pActiveControl->DoDrag(pt, rect);
							}
							break;

						case WM_LBUTTONUP:
							{
								bDoDrag = FALSE;
							}
							break;

						default:
							DispatchMessage(&msg);
						}

						if (!bDoDrag)
							break;
					}

					ReleaseCapture();
				}
			}
		}
	}

	return 0;
}

void CXMLKeyFrameValuesDlg::EndEdit()
{
}
#endif

#endif