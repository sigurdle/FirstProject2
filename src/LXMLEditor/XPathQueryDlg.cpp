// XPathQueryDlg.cpp : Implementation of CXPathQueryDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "XPathQueryDlg.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CXPathQueryDlg

long CXPathQueryDlg::OnEvaluate(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	::SendMessage(GetDlgItem(IDC_XPATH_RESULT), LB_RESETCONTENT, 0, 0);

	TCHAR str_expr[1024];
	GetDlgItemText(IDC_XPATH_EXPR, str_expr, sizeof(str_expr));

	CComPtr<ILDOMDocument> document;
	m_document->get_DOMDocument(&document);

	CComQIPtr<ILXPathEvaluator> xpathEvaluator = document;
	if (xpathEvaluator)
	{
		CComPtr<ILXPathExpression> xpathExpression;
		xpathEvaluator->createExpression(_bstr_t(str_expr), NULL, &xpathExpression);
		if (xpathExpression)
		{
			CComPtr<ILXPathResult> xpathResult;
			xpathExpression->evaluate(document/*node*/, ANY_TYPE, NULL, &xpathResult);

			if (xpathResult)
			{
				long nnodes;
				xpathResult->get_snapshotLength(&nnodes);

				for (int n = 0; n < nnodes; n++)
				{
					CComPtr<ILDOMNode> node;
					xpathResult->snapshotItem(n, &node);

					CComBSTR nodeName;
					node->get_nodeName(&nodeName);

					::SendMessage(GetDlgItem(IDC_XPATH_RESULT), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)_bstr_t(nodeName));
				}
			}
		}
	}
#endif
	return 0;
}

}	// LXmlEdit
}
