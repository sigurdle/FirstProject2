#pragma once

#include "ASDesignDefinition.h"

class CDTDDesignContentModel :
	public CDTDDesignDefinition
//	public IASDesignDefinition,
//	public IASDesignContentModel,
//	public IASUserDataHandler
{
public:
	IASContentModel* m_asCM;
	CArray<CDTDDesignDefinition*,CDTDDesignDefinition*> m_defs;

	IASDeclaration* m_asElement;
	CDTDDesignContentModel* m_pDesignCM;

	CDTDDesignContentModel()
	{
		m_asCM = NULL;

		m_asElement = NULL;
		m_pDesignCM = NULL;
	}

	virtual void handleEvent(LXUIEvent* evt);

	void SetOptionalUnbounded(IASModel* asModel, bool bOptional, bool bUnbounded);
	void RemoveOptionalUnbounded(IASModel* asModel, bool bOptional, bool bUnbounded);

	virtual void DeselectAll();
	virtual void Build();
	virtual void Setup();

	void DrawExpanded(LDraw::Graphics* pGraphics, int x, int y, BOOL bExpanded);

	bool IsOptional() const
	{
		if (m_asCM)
		{
			long minOccurs = m_asCM->get_minOccurs();

			return (minOccurs == 0);
		}
		else
			return false;
	}

	bool IsUnbounded()
	{
		if (m_asCM)
		{
			long maxOccurs = m_asCM->get_maxOccurs();

			return (maxOccurs == 0xffffffff/*AS_UNBOUNDED*/);
		}
		else
			return false;
	}

	virtual void OnRender3(LDraw::Graphics* pGraphics);
//	virtual void Size(HDC hDC);
	virtual void CalculateBoundsAndChildren(LDraw::SizeD);
	virtual void OnArrange(LDraw::SizeD finalSize);
//	virtual CDTDDesignSchemaNode* OnClick(POINT pt, BOOL bDblClk, bool& bSize);
	void OnButtonDown(CLXUIMouseEvent* evt);

	virtual IASContentModel* Get_asCM()
	{
		return m_asCM;
	}

	virtual void BuildChildren()
	{
		if (m_asElement != NULL)
		{
			if (m_pDesignCM)
				m_pDesignCM->Build();
		}
		else
		{
			for (int i = 0; i < m_defs.GetSize(); i++)
			{
				m_defs[i]->Build();
			}
		}
	}

	virtual void FreeChildren()
	{
		for (int i = 0; i < m_defs.GetSize(); i++)
		{
//			m_defs[i]->Free();
		}
	}

	CDTDDesignDefinition* GetInsertion(POINT point, CDTDDesignDefinition* & pBefore)
	{
		point.y += m_innerRect.top;

		pBefore = NULL;

		for (int i = m_defs.GetSize()-1; i >= 0; i--)
		{
			// Check if we pass on to child definition
			if ((	point.y > m_defs[i]->m_outerRect.top &&
					point.y < m_defs[i]->m_outerRect.bottom))
			{
				if (point.x > m_defs[i]->m_outerRect.left+m_defs[i]->m_width)
				{
					LDraw::Point pt = point;
					pt.X -= m_defs[i]->m_outerRect.left;
					pt.Y -= m_defs[i]->m_outerRect.top;

					CDTDDesignDefinition* p = m_defs[i]->GetInsertion(pt, pBefore);
					if (p)
						return p;
				}
			}

			if (point.y > m_defs[i]->m_outerRect.top)
				break;

			pBefore = m_defs[i];
		}

		if (point.x > 0)
		{
			return this;
		}

		return NULL;
	}

	virtual void OnEditChange(HDC hDC)
	{
		m_bEditChanged = true;
	}

	virtual void EndEdit();

#if 0
// IASUserDataHandler
	STDMETHOD(_handle)(/*[in]*/ _ASUserDataHandleType operation,
                      /*[in]*/ BSTR key, 
                      /*[in]*/ IUnknown* data, 
                      /*[in]*/ IASObject* src, 
                      /*[in]*/ IASObject* dst);
#endif

	IASContentModel* get_asCM()
	{
		return m_asCM;
	}
//	STDMETHOD(SetOptionalUnbounded)(/*[in]*/ VARIANT_BOOL bOptional, /*[in]*/ VARIANT_BOOL bUnbounded);
//	STDMETHOD(RemoveOptionalUnbounded)(/*[in]*/ VARIANT_BOOL bOptional, /*[in]*/ VARIANT_BOOL bUnbounded);
};

