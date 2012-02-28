// SBDestination.h: interface for the CSBDestination class.
//
//////////////////////////////////////////////////////////////////////
//
// Copyright 1998 Scott D. Killen
//
//////////////////////////////////////////////////////////////////////

#ifndef __SBDESTINATION_H__
#define __SBDESTINATION_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BrowseForFolder.h"

class CSBDestination : public CBrowseForFolder  
{
public:
//	CSBDestination(const HWND hParent = NULL, const int nTitleID = 0);
	CSBDestination() : CBrowseForFolder(NULL, NULL, NULL)
	{
	}

	~CSBDestination();

	void SetInitialSelection(LPCTSTR strPath);

	void OnInit() const;
	void OnSelChanged(const LPITEMIDLIST pidl) const;

private:
	TCHAR m_strInitialSelection[1024];
};

#endif // __SBDESTINATION_H__
