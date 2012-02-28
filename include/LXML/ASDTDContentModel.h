#ifndef __ASDTDCONTENTMODEL_H_
#define __ASDTDCONTENTMODEL_H_

#include "ASDTDObjectImpl.h"

namespace System
{
namespace Web
{

class CDTDModel;
class CDTDASObjectList;
class CASDTDElement;

class WEBEXT CASDTDContentModel :
	public CASDTDObject, public IASContentModel
{
public:
	CASDTDContentModel();
	~CASDTDContentModel();

// IASObject
	IASObject* cloneASObject(bool deep) const
	{
		ASSERT(0);
		return NULL;
	}

	ASObjectType get_asNodeType() const
	{
		return AS_CONTENTMODEL;
	}

// IASContentModel
	long get_minOccurs() const;
	void set_minOccurs(long newVal);
	long get_maxOccurs() const;
	void set_maxOccurs(long newVal);
	ASContentModelTypeOp get_listOperator() const;
	void set_listOperator(ASContentModelTypeOp newVal);
	IASObjectList* get_subModels();
	void set_subModels(IASObjectList* newVal);
	uint appendsubModel(/*[in]*/ IASObject* newNode);
	IASObject* insertBeforeSubModel(/*[in]*/ IASObject* newObject, /*[in]*/ IASObject* refObject);
	void replacesubModel(/*[in]*/ IASObject* oldNode, /*[in]*/ IASObject* newNode);
	void removeSubModel(/*[in]*/ IASObject* oldObject);

public:

	CASDTDElement* m_ownerElement;

//	CDTDModel* m_pDTDDocument;
	long m_minOccurs;
	long m_maxOccurs;
	ASContentModelTypeOp m_listOperator;

	CDTDASObjectList* m_subModels;
};

}	// w3c
}

#endif // __ASDTDCONTENTMODEL_H_
