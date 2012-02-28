#include "stdafx.h"
#include "XPath.h"

#include "XPathSetSnapshot.h"

namespace System
{
namespace XPath
{

void CXPathSetSnapshot::FinalRelease()
{
	/*
	for (int i = 0; i < nodeTab.GetSize(); i++)
	{
;//		nodeTab[i]->Release();
	}
	*/
}

void CXPathSetSnapshot::SetSize(int n)
{
	/*
	for (int i = n; i < nodeTab.GetSize(); i++)
	{
	;//	nodeTab[i]->Release();
	}

	nodeTab.SetSize(n);
	*/
}

uint CXPathSetSnapshot::get_length() const
{
	VERIFY(0);
	return 0;
}

/*
ErrorCode CXPathSetSnapshot::item(long index, Web::Node* *pVal)
{
	return S_OK;
}
*/

}	// XPath
}
