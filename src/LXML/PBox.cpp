#include "stdafx.h"
#include "LXML2.h"

#include "PBox.h"
#include "PParentBox.h"

namespace System
{
namespace Web
{

CHTMRenderContext::CHTMRenderContext()
{
//	m_pGraphics = NULL;

//
	m_bInSelection = false;
//#if 0
	m_range = NULL;
//#endif
	m_hBrokenImage = NULL;

	m_pWindow = NULL;

//		m_outerPos.X = 0;
//		m_outerPos.Y = 0;

	m_matrixToView = gm::Matrix3f::GetIdentity();
}

CHTMBoxItem::CHTMBoxItem() : m_refcount(0)
{
	m_type = boxTypeUnknown;
	m_parentBox = NULL;

	m_pStackingContext = NULL;
}

ULONG CHTMBoxItem::AddRef()
{
	return InterlockedIncrement((long*)&m_refcount);
}

ULONG CHTMBoxItem::Release()
{
	long refcount = InterlockedDecrement((long*)&m_refcount);
	ASSERT(refcount >= 0);

	if (refcount == 0)
	{
		delete this;
		return 0;
	}

	return refcount;
}

CHTMBoxItem::~CHTMBoxItem()
{
	ASSERT(m_refcount == 0);

#if 1
	ASSERT(m_parentBox == NULL);
#else
	ASSERT(0);
	if (m_parentBox)
	{
		m_parentBox->RemoveChildBox(this);
		m_parentBox = NULL;
	}
#endif
}

// virtual
void CHTMBoxItem::Destroy()
{
	if (m_parentBox)
	{
		m_parentBox->RemoveChildBox(this);
	}
}

gm::RectF CHTMBoxItem::GetAbsOuterRect()
{
	gm::RectF abspos = m_outerRect;

	CHTMParentBox* pParent = m_parentBox;
	while (pParent)
	{
		abspos.Translate(pParent->m_outerRect.X, pParent->m_outerRect.Y);
		abspos.Translate(pParent->m_innerRect.X, pParent->m_innerRect.Y);

		pParent = pParent->m_parentBox;
	}

	return abspos;
}

}	// Web
}
