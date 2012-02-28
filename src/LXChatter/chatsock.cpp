// chatsock.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "LXChatter.h"
#include "LXChatter2.h"

#include "chatsock.h"
#include "chatdoc.h"

#include <stddef.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CChatSocket, CSocket)

CChatSocket::CChatSocket(CChatDoc* pDoc)
{
	m_pDoc = pDoc;
}

void CChatSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);

#if 0
	m_pDoc->ProcessPendingRead();
#endif
}
