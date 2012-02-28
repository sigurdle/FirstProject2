#include "stdafx.h"
#include "LXMLEditor2.h"
#include "Transition.h"

namespace System
{
namespace LXmlEdit
{

CSMILTransition::CSMILTransition(System::StringW* type, System::StringW* subtype, uint8 arrowFlags)
{
	m_type = type;
	m_subtype = subtype;
	m_arrowFlags = arrowFlags;

	m_pTransition = NULL;
}

CTransition::CTransition(System::StringW* name, uint8 bitCorners, uint8 flags)
{
	m_name = name;
	m_bitCorners = bitCorners;
	m_flags = flags;
}

void CTransition::AddMapping(CSMILTransition* pMapping)
{
	pMapping->m_pTransition = this;
	m_mapping.Add(pMapping);
}

CTransitions::CTransitions()
{
	CTransition* pTransition;

	{
		pTransition = new CTransition(WSTR("barnDoorWipe"), bitRight|bitLeft|bitTop|bitBottom|bitLowerLeft|bitUpperRight|bitUpperLeft|bitLowerRight, 1);
			pTransition->AddMapping(new CSMILTransition(WSTR("barnDoorWipe"), WSTR("vertical"), bitRight|bitLeft));
			pTransition->AddMapping(new CSMILTransition(WSTR("barnDoorWipe"), WSTR("horizontal"), bitTop|bitBottom));
			pTransition->AddMapping(new CSMILTransition(WSTR("barnDoorWipe"), WSTR("diagonalBottomLeft"), bitLowerLeft|bitUpperRight));
			pTransition->AddMapping(new CSMILTransition(WSTR("barnDoorWipe"), WSTR("diagonalTopLeft"), bitUpperLeft|bitLowerRight));
		m_items.Add(pTransition);
	}

	{
		pTransition = new CTransition(WSTR("inset"), bitLowerLeft|bitUpperRight|bitUpperLeft|bitLowerRight, 0);
			pTransition->AddMapping(new CSMILTransition(WSTR("boxWipe"), WSTR("topLeft"), bitUpperLeft));
			pTransition->AddMapping(new CSMILTransition(WSTR("boxWipe"), WSTR("topRight"), bitUpperRight));
			pTransition->AddMapping(new CSMILTransition(WSTR("boxWipe"), WSTR("bottomRight"), bitLowerRight));
			pTransition->AddMapping(new CSMILTransition(WSTR("boxWipe"), WSTR("bottomLeft"), bitLowerLeft));
		m_items.Add(pTransition);
	}

	{
		pTransition = new CTransition(WSTR("pushWipe"), bitLeft|bitTop|bitRight|bitBottom, 0);
			pTransition->AddMapping(new CSMILTransition(WSTR("pushWipe"), WSTR("fromLeft"), bitLeft));
			pTransition->AddMapping(new CSMILTransition(WSTR("pushWipe"), WSTR("fromTop"), bitTop));
			pTransition->AddMapping(new CSMILTransition(WSTR("pushWipe"), WSTR("fromRight"), bitRight));
			pTransition->AddMapping(new CSMILTransition(WSTR("pushWipe"), WSTR("fromBottom"), bitBottom));
		m_items.Add(pTransition);
	}

	{
		pTransition = new CTransition(WSTR("clockWipe"), bitLeft|bitTop|bitRight|bitBottom, 0);
			pTransition->AddMapping(new CSMILTransition(WSTR("clockWipe"), WSTR("clockwiseTwelve"), bitTop));
			pTransition->AddMapping(new CSMILTransition(WSTR("clockWipe"), WSTR("clockwiseThree"), bitRight));
			pTransition->AddMapping(new CSMILTransition(WSTR("clockWipe"), WSTR("clockwiseSix"), bitBottom));
			pTransition->AddMapping(new CSMILTransition(WSTR("clockWipe"), WSTR("clockwiseNine"), bitLeft));
		m_items.Add(pTransition);
	}
}

CSMILTransition* CTransitions::FindMapping(System::StringW* type, System::StringW* subtype)
{
	if (type == NULL) return NULL;
	if (subtype == NULL) return NULL;	// ??

	long index = -1;
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		for (int nmap = 0; nmap < m_items[i]->m_mapping.GetSize(); nmap++)
		{
			if (*type == *m_items[i]->m_mapping[nmap]->m_type && subtype == m_items[i]->m_mapping[nmap]->m_subtype)
			{
				return m_items[i]->m_mapping[nmap];
			}
		}
	}

	return NULL;
}

}	// LXMLEdit
}
