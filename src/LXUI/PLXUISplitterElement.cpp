#include "stdafx.h"
#include "LXUI2.h"

#if 0

#include "PLXUISplitterElement.h"

#include "LXUIBoxWindow.h"

//////////////////////////////////////////////////////////////////////////////
// CPLXUISplitterElement

// virtual
BOOL CPLXUISplitterElement::OnButtonDown(POINT point, CPElement* *pVal)
{
	m_pWindow->m_pElementCapture = this;
	return TRUE;
}

// virtual
void CPLXUISplitterElement::OnMouseMove(POINT point)
{
	//m_pNode->
	/*
	UPOSITION pos = m_rparent->m_rchildList.Find(this);

	UPOSITION posprev = pos;
	m_rparent->m_rchildList.GetPrev(posprev);
	*/
}

#endif