// NITFTopicsDlg.cpp : Implementation of CNITFTopicsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "NITFTopicsDlg.h"

//LXMLEXT ILDOMElement* GetElementByTagName(ILDOMNode* parentNode, BSTR tagName, BOOL bDeep = TRUE);
//LXMLEXT ILDOMElement* GetElementByTagNameNS(ILDOMNode* parentNode, BSTR ns, BSTR tagName, BOOL bDeep = TRUE);

#if 0

/////////////////////////////////////////////////////////////////////////////
// CNITFTopicsDlg

#define PANE_NAME			0

class CSubject
{
public:
	_bstr_t m_name;
};

void CNITFTopicsDlg::AddSubjects(ILDOMElement* documentElement, IUITreeItem* parentItem, int topicType, int matchSubject, int matchSubjectMatter)
{
	CComPtr<ILDOMNode> node;
	documentElement->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"Topic"))
			{
				BSTR bduid;
				element->getAttribute(L"Duid", &bduid);
				_bstr_t duid = _bstr_t(bduid, false);

				WCHAR* p = (BSTR)duid;
				p += 2;

				char buf[4];

				buf[0] = *p++;
				buf[1] = *p++;
				buf[2] = 0;
				int subject = atol(buf);

				buf[0] = *p++;
				buf[1] = *p++;
				buf[2] = *p++;
				buf[3] = 0;
				int subjectMatter = atol(buf);

				buf[0] = *p++;
				buf[1] = *p++;
				buf[2] = *p++;
				buf[3] = 0;
				int subjectDetail = atol(buf);

				if ((topicType == 0 && subject != 0 && subjectMatter == 0 && subjectDetail == 0) ||
					(topicType == 1 && subject == matchSubject && subjectMatter != 0 && subjectDetail == 0) ||
					(topicType == 2 && subject == matchSubject && subjectMatter == matchSubjectMatter && subjectDetail != 0))
				{
					ILDOMElement* description = GetElementByTagNameNS(element, NULL, L"Description", FALSE);

					BSTR bvariant;
					description->getAttribute(L"Variant", &bvariant);
					_bstr_t variant = _bstr_t(bvariant, false);

					if (!wcscmp(variant, L"Name"))
					{
						BSTR bname;
						description->get_textContent(&bname);
						_bstr_t name = _bstr_t(bname, false);

						CSubject* pSubject = new CSubject;
						pSubject->m_name = name;

						CComPtr<IUITreeItem> newItem;
						m_subjectsTreeCtl->InsertItem((DWORD)pSubject, parentItem, NULL, NULL, -1/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

						if (topicType == 0)
							AddSubjects(documentElement, newItem, 1, subject, 0);
						else if (topicType == 1)
							AddSubjects(documentElement, newItem, 2, subject, subjectMatter);
					}
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}

LRESULT CNITFTopicsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetDlgControl(IDC_NITF_SUBJECTS, IID_IUITreeControl, (void**)&m_subjectsTreeCtl);

	m_subjectsTreeCtl->SetSite(this);

	m_subjectsTreeCtl->InsertColumn(PANE_NAME, L"Name", 120, TRUE, TRUE, NULL);

	CComPtr<ILDOMDocument> document;
	document.CoCreateInstance(CLSID_LDOMDocument);
	if (document)
	{
		VARIANT_BOOL success;
		document->load(_variant_t(L"C:\\iptc-subjectcode.xml"), &success);
		if (success)
		{
			CComPtr<ILDOMElement> documentElement;
			document->get_documentElement(&documentElement);

			if (documentElement)
			{
				AddSubjects(documentElement, NULL,
					0,
					0, 0);
			}
		}
	}

	return 0;
}

STDMETHODIMP CNITFTopicsDlg::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
{
	*pVal = NULL;

	CSubject* pSubject = (CSubject*)itemdata;

	switch (column)
	{
	case PANE_NAME:
		{
			*pVal = pSubject->m_name.copy();
		}
		break;
	}

	return S_OK;
}

#endif