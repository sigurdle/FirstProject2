// LScopeFilter.cpp : Implementation of CLScopeFilter
#include "stdafx.h"
#include "LScope.h"
#include "LScopeFilter.h"

/////////////////////////////////////////////////////////////////////////////
// CLScopeWindow

LRESULT CLScopeWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(this);

	for (int x = 0; x < 
	dc.MoveTo(

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CLScopeFilter

STDMETHODIMP CLScopeFilter::CInputPin::Receive(ILMediaSample *pSample)
{
	ULONG ActualDataLength = pSample->GetActualDataLength();



	return 0;
}
