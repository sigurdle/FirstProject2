#include "stdafx.h"
#include "LXUI2.h"
#include "TransformCollection.h"

namespace System
{
namespace UI
{

TransformCollection::TransformCollection()
{
//	m_Value = new Matrix;
//	m_pListener = NULL;
}

TransformCollection::~TransformCollection()
{
//	ASSERT(m_pListener == NULL);
}

const Type_Info& TransformCollection::GetItemType() const
{
	return typeid(Transform*);
}

/*
int TransformCollection::FinalConstruct()
{
	//m_Value->AddRef();

	return 0;
}

void TransformCollection::FinalRelease()
{
	for (int i = 0; i < m_items.GetSize(); i++)
	{
//		m_items[i]->Release();
	}
	m_items.RemoveAll();

//	m_Value->Release();
}
*/

void TransformCollection::AddChild(Object* child)
{
	Transform* transform = dynamic_cast<Transform*>(child);
	if (transform == NULL)
		throw std::exception("child is not a Transform");

	Add(transform);
}

void TransformCollection::AddText(StringW* text)
{
	THROW(-1);
}

unsigned int TransformCollection::GetCount()
{
	return m_items.GetSize();
}

Transform*& TransformCollection::Item(unsigned int index)
{
	return m_items[index];
}

Transform* TransformCollection::GetItem(unsigned int index)
{
	return m_items[index];
}

void TransformCollection::Add(Transform* const & element)
{
	ASSERT(0);

#if 0
	_Transform* transform = dynamic_cast<ILXUITransform*>(child);
	if (transform)
	{
		//child->AddRef();
		m_items.Add(transform);

		return S_OK;
	}
	else
		return E_FAIL;
#endif
}

__release<LDraw::Matrix3f> TransformCollection::get_Value()
{
	m_Value = LDraw::Matrix3f::GetIdentity();

	for (unsigned int i = 0; i < m_items.GetSize(); i++)
	{
		Transform* transform = m_items[i];
		__release<LDraw::Matrix3f> value = transform->get_Value();
		m_Value = *value * *m_Value;
	}

	return m_Value;
}

}	// UI
}
