#pragma once

class CASGraphCtl;

class CDTDDesignSchemaNode
//	public IASDesignObject
{
public:
	CDTDDesignSchemaNode()
	{
		m_asObject = NULL;
		m_pParent = NULL;

		m_bExpanded = false;
		m_bSelected = false;
#if 0
		m_outerRect.SetRectEmpty();
		m_innerRect.SetRectEmpty();
#endif
		m_hWndEdit = NULL;
		m_bEditChanged = FALSE;

		m_pCtl = NULL;
	}

	virtual ~CDTDDesignSchemaNode()
	{
	}

	CASGraphCtl* m_pCtl;

	HWND m_hWndEdit;
	BOOL m_bEditChanged;

	IASObject* m_asObject;
	CDTDDesignSchemaNode* m_pParent;

	LDraw::BBox m_innerRect;
	LDraw::BBox m_outerRect;
	
	LDraw::BBox GetAbsInnerRect()
	{
		//CRect abspos = m_innerRect;
		LDraw::BBox abspos = m_outerRect;
	//	abspos.OffsetRect(m_outerRect.left, m_outerRect.top);
	//	abspos.OffsetRect(-m_innerRect.left, -m_innerRect.top);

		CDTDDesignSchemaNode* pParent = m_pParent;
		while (pParent)
		{
			abspos.OffsetRect(pParent->m_outerRect.left, pParent->m_outerRect.top);
			abspos.OffsetRect(-pParent->m_innerRect.left, -pParent->m_innerRect.top);

			pParent = pParent->m_pParent;
		}

		return abspos;
		/*
		CRect rect = m_innerRect;

		CDTDDesignSchemaNode* pParent = this;//m_pParent;
		while (pParent)
		{
			rect.OffsetRect(pParent->m_outerRect.left, pParent->m_outerRect.top);
			pParent = pParent->m_pParent;
		}

		return rect;
		*/
	}

	LDraw::BBox GetAbsOuterRect()
	{
		LDraw::BBox abspos = m_outerRect;

		CDTDDesignSchemaNode* pParent = m_pParent;
		while (pParent)
		{
			abspos.OffsetRect(pParent->m_outerRect.left, pParent->m_outerRect.top);
		//	abspos.OffsetRect(pParent->m_innerRect.left, pParent->m_innerRect.top);

			pParent = pParent->m_pParent;
		}

		return abspos;
	}

	bool m_bExpanded;
	bool m_bSelected;

	virtual void EndEdit()
	{
	}
	virtual void OnEditChange(HDC hDC)
	{
	}

	virtual void DeselectAll()
	{
	}

	virtual CDTDDesignSchemaNode* OnClick(POINT pt, BOOL bDblClk, bool& bSize)
	{
		bSize = false;
		return NULL;
	}

	virtual void BuildChildren()
	{
	}

	virtual void FreeChildren()
	{
	}
};
