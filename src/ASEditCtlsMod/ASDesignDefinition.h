#pragma once

#include "ASDesignObject.h"

class CASAttribute;

class ATL_NO_VTABLE CDTDDesignDefinition :
	public CDTDDesignSchemaNode,
	public CLXUIControl
{
public:
	int m_width;

	CDTDDesignDefinition()
	{
		m_width = 0;

		m_bAttributesExpanded = false;
	}

	bool m_bAttributesExpanded;

	CArray<CASAttribute*,CASAttribute*> m_attributes;

	void BuildAttributes();

	virtual void Build() = 0;
	virtual void Setup() = 0;
#if 0
	virtual void DrawDesign(HDC hDC) = 0;
	virtual void Size(HDC hDC) = 0;
#endif

	virtual IASContentModel* Get_asCM() = 0;
	virtual CDTDDesignDefinition* GetInsertion(LDraw::Point point, CDTDDesignDefinition* & pBefore)
	{
		return NULL;
	}

	void DrawAttributes(HDC hDC);
};

extern COLORREF selectedColor;

class CASDesignEmptyObject : public CDTDDesignDefinition
{
public:
	virtual IASContentModel* Get_asCM()
	{
		return NULL;
	}

	virtual void Build()
	{
	}
	virtual void Setup()
	{
	}
	virtual void OnRender2(LDraw::Graphics* pGraphics)
	{
#if 0
		CBrush brush;
		if (m_bSelected)
			brush.CreateSolidBrush(selectedColor);
		else
			brush.CreateSolidBrush(RGB(255, 255, 255));

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, brush);

		Rectangle(hDC, m_innerRect.left, m_innerRect.top, m_innerRect.right, m_innerRect.bottom);

		brush.DeleteObject();
		SelectObject(hDC, hOldBrush);
#endif
	}
	virtual void CalculateBoundsAndChildren(LDraw::SizeD)
//	virtual void Size(HDC hDC)
	{
		m_width = 16;
		m_innerRect.SetRect(0, 0, m_width, 12);
		m_desiredSize.Width = m_innerRect.Width();
		m_desiredSize.Height = m_innerRect.Height();
	}
};
