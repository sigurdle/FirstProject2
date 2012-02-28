#include "stdafx.h"
//#include "LXML.h"
#include "LXML2.h"

#include "ASDTDModel.h"
#include "ASDTDContentModel.h"
#include "ASDTDElement.h"
#include "DTDDocument.h"

namespace System
{
namespace Web
{

/*
int CASDTDContentModel::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CDTDASObjectList>::CreateInstance(&m_subModels);
	if (FAILED(hr)) return E_NOINTERFACE;
	m_subModels->AddRef();

	return S_OK;
}

void CASDTDContentModel::FinalRelease()
{
	if (m_subModels)
	{
		m_subModels->Release();
		m_subModels = NULL;
	}
}
*/
CASDTDContentModel::CASDTDContentModel()
{
//	m_pDTDDocument = NULL;

	m_minOccurs = 1;
	m_maxOccurs = 1;
	m_listOperator = AS_NONE;
	m_ownerElement = NULL;

	m_subModels = new CDTDASObjectList;
}

CASDTDContentModel::~CASDTDContentModel()
{
}

long CASDTDContentModel::get_minOccurs() const
{
	return m_minOccurs;
}

void CASDTDContentModel::set_minOccurs(long newVal)
{
	m_minOccurs = newVal;

	for (size_t i = 0; i < m_userdataList.GetSize(); i++)
	{
		if (m_userdataList[i]->m_handler)
			m_userdataList[i]->m_handler->_handle((ASUserDataHandleType)5, m_userdataList[i]->m_key, m_userdataList[i]->m_data, NULL, NULL);
	}

//	m_ownerElement->OnChanged(this);
}

long CASDTDContentModel::get_maxOccurs() const
{
	return m_maxOccurs;
}

void CASDTDContentModel::set_maxOccurs(long newVal)
{
	m_maxOccurs = newVal;

	for (size_t i = 0; i < m_userdataList.GetSize(); i++)
	{
		if (m_userdataList[i]->m_handler)
			m_userdataList[i]->m_handler->_handle((ASUserDataHandleType)5, m_userdataList[i]->m_key, m_userdataList[i]->m_data, NULL, NULL);
	}

//	m_ownerElement->OnChanged(this);
}

ASContentModelTypeOp CASDTDContentModel::get_listOperator() const
{
	return m_listOperator;
}

void CASDTDContentModel::set_listOperator(ASContentModelTypeOp newVal)
{
	m_listOperator = newVal;

	for (size_t i = 0; i < m_userdataList.GetSize(); i++)
	{
		if (m_userdataList[i]->m_handler)
			m_userdataList[i]->m_handler->_handle((ASUserDataHandleType)5, m_userdataList[i]->m_key, m_userdataList[i]->m_data, NULL, NULL);
	}

//	m_ownerElement->OnChanged(this);
}

IASObjectList* CASDTDContentModel::get_subModels()
{
	return m_subModels;
}

void CASDTDContentModel::set_subModels(IASObjectList* newVal)
{
	IASObjectList* subModels = m_subModels;
	if (subModels)
	{
//		subModels->AddRef();
//		m_subModels->Release();
	}

	m_subModels = (CDTDASObjectList*)newVal;
//	if (m_subModels)
//		m_subModels->AddRef();
}

void CASDTDContentModel::replacesubModel(IASObject *oldNode, IASObject *newNode)
{
	if (oldNode == NULL) THROW(-1);
	if (newNode == NULL) THROW(-1);

	for (size_t i = 0; i < m_subModels->m_items.GetSize(); i++)
	{
		if (m_subModels->m_items[i] == oldNode)
		{
			m_subModels->m_items[i] = newNode;
//			newNode->AddRef();

			break;
		}
	}

//	m_ownerElement->OnChanged(this);
}

uint CASDTDContentModel::appendsubModel(IASObject *newNode)
{
	if (newNode == NULL) throw -1;

	return m_subModels->m_items.Add(newNode);
//	newNode->AddRef();

//	m_ownerElement->OnChanged(this);
}

IASObject* CASDTDContentModel::insertBeforeSubModel(/*[in]*/ IASObject* newObject, /*[in]*/ IASObject* refObject)
{
	ASSERT(0);
	return NULL;
}

void CASDTDContentModel::removeSubModel(/*[in]*/ IASObject* oldObject)
{
	ASSERT(0);
}

#if 0
CComBSTR CASDTDContentModel::GetAsText()
{
	CComBSTR text;

	text += OLESTR("(");

	for (int i = 0; i < m_subModels->m_items.GetSize(); i++)
	{
		if (i > 0)
		{
			if (m_listOperator == AS_SEQUENCE)
			{
				text += OLESTR(",");
			}
			else if (m_listOperator == AS_CHOICE)
			{
				text += OLESTR("|");
			}
			else	// AS_ALL (not supported by DTD ?)
			{
				text += OLESTR(",");
			//	ASSERT(0);
			}
		}

		ASObjectType type;
		m_subModels->m_items[i]->get_asNodeType(&type);

		if (type == AS_ELEMENT_DECLARATION)
		{
			CASDTDElement* subElement = (CASDTDElement*)m_subModels->m_items[i];
			text += subElement->m_name;
		}
		else if (type == AS_CONTENTMODEL)
		{
			CASDTDContentModel* subCM = (CASDTDContentModel*)m_subModels->m_items[i];
			if (subCM->m_listOperator == AS_NONE)
			{
				if (subCM->m_subModels->m_items.GetSize() > 0)
				{
					CASDTDElement* subElement = (CASDTDElement*)subCM->m_subModels->m_items[0];
					text += subElement->m_name;

					if (subCM->m_minOccurs == 0 && subCM->m_maxOccurs == 1)
					{
						text += OLESTR("?");
					}
					else if (subCM->m_minOccurs == 0 && subCM->m_maxOccurs > 1)
					{
						text += OLESTR("*");
					}
					else if (subCM->m_minOccurs == 1 && subCM->m_maxOccurs > 1)
					{
						text += OLESTR("+");
					}
				}
			}
			else
			{
				text += subCM->GetAsText();
			}
		}
	}

	text += OLESTR(")");

	if (m_minOccurs == 0 && m_maxOccurs == 1)
	{
		text += OLESTR("?");
	}
	else if (m_minOccurs == 0 && m_maxOccurs > 1)
	{
		text += OLESTR("*");
	}
	else if (m_minOccurs == 1 && m_maxOccurs > 1)
	{
		text += OLESTR("+");
	}

	return text;
}
#endif

}	// Web
}
