#include "stdafx.h"
#include "ASEditCtlsMod.h"
#include "ASGraphCtl.h"

#include "ASDesignDefinition.h"
#include "ASDesignAttribute.h"

void CDTDDesignDefinition::DrawAttributes(HDC hDC)
{
	ATLASSERT(0);
#if 0
	if (m_attributes.GetSize() > 0)
	{
		Ellipse(hDC, 20, -20, 60, 20);
	}

	if (m_bAttributesExpanded)
	{
		int x = 80;
		int y = 100+40;

		int width = max(m_width-80, 800);

		for (int i = 0; i < m_attributes.GetSize(); i++)
		{
			CComPtr<IASAttributeDeclaration> asAttr = m_attributes[i]->m_asAttr;

			sysstring nodeName = asAttr->get_nodeName();

			CRect itemrect(x, y, x+width, y+160);

			Rectangle(hDC, itemrect.left, itemrect.top, itemrect.right, itemrect.bottom);

			CRect trect = itemrect;
			trect.left += 20;
			trect.InflateRect(-10, -10);

			DrawText(hDC, _bstr_t(nodeName), nodeName.Length(), &trect, DT_SINGLELINE | DT_VCENTER);

			y += 160+20;
		}
	}
#endif
}

void CDTDDesignDefinition::BuildAttributes()
{
	ATLTRACE("TODO BuildAttributes\n");
#if 0
	{
		ATLASSERT(0);
#if 0
		for (int i = 0; i < m_attributes.GetSize(); i++)
		{
			m_attributes[i]->Release();
		}
#endif
		m_attributes.RemoveAll();
	}
	ATLASSERT(m_asObject);

	IASNamedObjectMap* attributes;

	IASElementDeclaration* element = dynamic_cast<IASElementDeclaration*>(m_asObject);
	if (element)
	{
		element->get_ASAttributeDecls(&attributes);
	}
	else
	{
		CComQIPtr<IASComplexTypeDeclaration> type = m_asObject;
		if (type)
		{
			type->get_ASAttributeDecls(&attributes);
		}
	}

	if (attributes)
	{
		long nattributes;
		attributes->get_length(&nattributes);

		for (int i = 0; i < nattributes; i++)
		{
			CComPtr<IASAttributeDeclaration> asAttr;
			attributes->item(i, (IASObject**)&asAttr);

			CComBSTR nodeName;
			asAttr->get_nodeName(&nodeName);

			CComObject<CASAttribute>* pASAttr;
			CComObject<CASAttribute>::CreateInstance(&pASAttr);
			pASAttr->AddRef();

			pASAttr->m_asObject = asAttr;
			pASAttr->m_asAttr = asAttr;
			m_attributes.Add(pASAttr);
		}
	}
#endif
}
