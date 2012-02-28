#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

NodeType* FloatVertexAttribute::nodeType(GetNodeType());

NodeType* FloatVertexAttribute::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		&X3DFieldDefinition("value", FieldType_MFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("name", FieldType_SFString, SAIFieldAccess_initializeOnly,-1),
		&X3DFieldDefinition("numComponents", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	/*
		SFNode   [in,out] metadata      NULL [X3DMetadataObject]

		MFFloat  [in,out] value  		  []   (-?,?)
		SFString []       name          ""
		SFInt32  []       numComponents 4    [1..4]
	*/
	};

	static NodeType nodeType("FloatVertexAttribute", typeid(FloatVertexAttribute), fields, _countof(fields), X3DVertexAttributeNode::GetNodeType());
	return &nodeType;
}

FloatVertexAttribute::FloatVertexAttribute() : X3DVertexAttributeNode(GetNodeType()),
	m_numComponents(new SFInt32(NULL, this, 4))
{
}

float FloatVertexAttribute::getFloat(unsigned int index) const
{
	int numComponents = m_numComponents->getValue();
	return m_value->get1Value(numComponents*index);
}

void FloatVertexAttribute::setFloat(unsigned int index, float value)
{
	int numComponents = m_numComponents->getValue();
	return m_value->set1Value(numComponents*index, value);
}

gm::vector2f FloatVertexAttribute::getVec2(unsigned int index) const
{
	int numComponents = m_numComponents->getValue();

	switch (numComponents)
	{
	case 1:
		return gm::vector2f(
			m_value->get1Value(numComponents*index),
			0);

	default:
		return gm::vector2f(
			m_value->get1Value(numComponents*index),
			m_value->get1Value(numComponents*index+1));
	}
}

void FloatVertexAttribute::setVec2(unsigned int index, gm::vector2f value)
{
	int numComponents = m_numComponents->getValue();

	// TODO, speed this up
	m_value->set1Value(numComponents*index, value[0]);
	m_value->set1Value(numComponents*index+1, value[1]);
}

gm::vector3f FloatVertexAttribute::getVec3(unsigned int index) const
{
	int numComponents = m_numComponents->getValue();

	switch (numComponents)
	{
	case 1:
		return gm::vector3f(
			m_value->get1Value(numComponents*index),
			0,
			0);

	case 2:
		return gm::vector3f(
			m_value->get1Value(numComponents*index),
			m_value->get1Value(numComponents*index+1),
			0);

	default:
		return gm::vector3f(
			m_value->get1Value(numComponents*index),
			m_value->get1Value(numComponents*index+1),
			m_value->get1Value(numComponents*index+2));
	}
}

gm::vector4f FloatVertexAttribute::getVec4(unsigned int index) const
{
	int numComponents = m_numComponents->getValue();

	switch (numComponents)
	{
	case 1:
		return gm::vector4f(
			m_value->get1Value(numComponents*index),
			0,
			0,
			1);

	case 2:
		return gm::vector4f(
			m_value->get1Value(numComponents*index),
			m_value->get1Value(numComponents*index+1),
			0,
			1);

	case 3:
		return gm::vector4f(
			m_value->get1Value(numComponents*index),
			m_value->get1Value(numComponents*index+1),
			m_value->get1Value(numComponents*index+2),
			1);

	default:
		return gm::vector4f(
			m_value->get1Value(numComponents*index),
			m_value->get1Value(numComponents*index+1),
			m_value->get1Value(numComponents*index+2),
			m_value->get1Value(numComponents*index+3));
	}
}

void FloatVertexAttribute::setValue(unsigned int index, float value)
{
	m_value->set1Value(index, value);
}

}	// x3d
}	// System
