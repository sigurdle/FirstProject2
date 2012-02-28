#pragma once

#include "ASDesignDefinition.h"

class CDTDDesignContentModel;

class CDTDDesignElementDefinitionRoot :
	public CDTDDesignDefinition
{
public:
//	IASElementDeclaration* m_asElement;
	IASDeclaration* m_asDefinition;
	CDTDDesignContentModel* m_pDesignCM;

	CDTDDesignElementDefinitionRoot()
	{
		m_asDefinition = NULL;
		m_pDesignCM = NULL;
	}

	virtual void Build();
	virtual void Setup()
	{
		// TODO
	}

	virtual void BuildChildren();
	virtual IASContentModel* Get_asCM();
	virtual CDTDDesignDefinition* GetInsertion(LDraw::Point point, CDTDDesignDefinition* & pBefore);

	virtual void DrawDesign(HDC hDC);
	virtual void Size(HDC hDC);
	virtual CDTDDesignSchemaNode* OnClick(POINT pt, BOOL bDblClk, bool& bSize);
};
