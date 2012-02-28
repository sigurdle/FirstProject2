#include "stdafx.h"
#include "X3D2.h"
#include "MFNode.h"

namespace System
{
namespace x3d
{

MFNode::MFNode(X3DNode* ownerNode) : X3DArrayField(ownerNode)
{
	m_nLights = 0;
	m_nViewpoints = 0;
}

X3DNode* MFNode::get1Value(size_t index)
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
	{
		raise(ArgumentOutOfRangeException());
		return NULL;
	}
}

void MFNode::set1Value(size_t index, X3DNode* newVal)
{
	if (index < m_items.GetSize())
	{
		X3DNode* oldVal = m_items[index];

		if (oldVal != newVal)
		{
			if (oldVal)
			{
				m_nLights -= oldVal->GetLights();
				//m_nViewpoints -= oldVal->m_nViewpoints;

				oldVal->RemoveParent(this);
			}

			m_items[index] = newVal;
			if (newVal)	// Allow NULL node ?
			{
				m_nLights += newVal->GetLights();
				//m_nViewpoints += newVal->m_nViewpoints;

				newVal->m_parents.Add(this);
			}
		}

		getOwnerNode()->OnFieldChanged(this);
	}
	else
	{
		raise(ArgumentOutOfRangeException());
	}
}

void MFNode::append1Value(X3DNode* node)
{
	// TODO ?: add to addChildren

	if (node)	// Allow NULL node ?
	{
		m_nLights += node->GetLights();
		//m_nViewpoints += node->m_nViewpoints;
		node->m_parents.Add(this);
		node->m_ownerLayer = getOwnerNode()->m_ownerLayer;
		getOwnerNode()->m_scene->AddNode(node);
	}
	m_items.push_back(node);

	getOwnerNode()->OnFieldChanged(this);
}

void MFNode::CopyFrom(X3DField* pFrom)
{
	ASSERT(m_items.GetSize() == 0);

	for (size_t i = 0; i < static_cast<MFNode*>(pFrom)->m_items.GetSize(); i++)
	{
		X3DNode* from = dynamic_cast<X3DNode*>(static_cast<MFNode*>(pFrom)->m_items[i]);

		X3DNode* x3dnode;
		if (from->getType())
		{
			x3dnode = from->m_scene->CreateNodeOfType(from->getType());

			X3DNode* node = x3dnode;
			// clone fields
			ASSERT(0);
#if 0
			for (unsigned int i = 0; i < node->m_fields.GetSize(); i++)
			{
				node->getField(i)->CopyFrom(from->getField(i));
			}
#endif
		}
		else	// A prototype instance ?
		{
			// hm, not cloning this .. ??
			x3dnode = (X3DNode*)(from);
		}

		m_items.push_back(x3dnode);
		/*
		CComQIPtr<CFieldValue> pValue = static_cast<MFNode*>(pFrom)->m_items[i];

		CComObject<SFNode>* pSF;
		CComObject<SFNode>::CreateInstance(&pSF);
		pSF->AddRef();	// ??
		pSF->CopyFrom(pValue);
		m_items.Add(_variant_t(pSF->GetUnknown()));
		*/
	}
}

IO::TextWriter& MFNode::WriteValuesToStream(IO::TextWriter& stream)
{
	for (size_t i = 0; i < m_items.size(); ++i)
	{
		//if (i > 0) stream << ',';
		m_items[i]->WriteVRML(stream);
	}

	return stream;
}

}	// x3d
}
