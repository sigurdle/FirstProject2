// SBDestination.cpp: implementation of the CSBDestination class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBDestination.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
CSBDestination::CSBDestination(const HWND hParent, const int nTitleID)
	: CBrowseForFolder(hParent, NULL, nTitleID)
{

}
*/

CSBDestination::~CSBDestination()
{

}

void CSBDestination::SetInitialSelection(LPCTSTR strPath)
{
	lstrcpy(m_strInitialSelection, strPath);
}

void CSBDestination::OnInit() const
{
	SetSelection(m_strInitialSelection);
	SetStatusText(m_strInitialSelection);
}

void CSBDestination::OnSelChanged(const LPITEMIDLIST pidl) const
{
	TCHAR strBuffer[1024];
	SHGetPathFromIDList(pidl, strBuffer);

	SetStatusText(strBuffer);
}
