#include "stdafx.h"
#include "X3D2.h"
#include "Script.h"

namespace System
{
namespace x3d
{

NodeType* Script::GetNodeType()
{
	static X3DFieldDefinition url("url", FieldType_MFString, SAIFieldAccess_inputOutput, offsetof(Script, m_url));
	static X3DFieldDefinition directOutput("directOutput", FieldType_SFBool, SAIFieldAccess_initializeOnly, offsetof(Script, m_directOutput));
	static X3DFieldDefinition mustEvaluate("mustEvaluate", FieldType_SFBool, SAIFieldAccess_initializeOnly, offsetof(Script, m_mustEvaluate));

	static X3DFieldDefinition* ScriptFields[] =
	{
		&url,
		&directOutput,
		&mustEvaluate,
		/*
		MFString  [in,out] url          []
		SFBool    []       directOutput FALSE
		SFBool    []       mustEvaluate FALSE
		# And any number of:
		fieldType []       fieldName
		fieldType [in]     fieldName
		fieldType [out]    fieldName
		fieldType [in,out] fieldName
	  */
	};

	static NodeType nodeType("Script", typeid(Script), ScriptFields, _countof(ScriptFields), X3DScriptNode::GetNodeType());
	return &nodeType;
}

Script::Script() : X3DScriptNode(GetNodeType())
{
}

uint Script::getFieldCount()
{
	return X3DNode::getFieldCount() + m_addfields.size();
}

void Script::AddField(X3DField* field)
{
	m_addfields.push_back(field);
}

X3DField* Script::getField(uint index)
{
	uint bcount = X3DNode::getFieldCount();
	if (index < bcount)
	{
		return X3DNode::getField(index);
	}

	index -= bcount;
	if (index >= m_addfields.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	return m_addfields[index];
}

X3DField* Script::getField(StringIn name)
{
	X3DField* field = X3DNode::getField(name);
	if (field)
	{
		return field;
	}

	for (uint i = 0; i < m_addfields.size(); ++i)
	{
		if (m_addfields[i]->m_fieldName == name)
			return m_addfields[i];
	}

	return NULL;
}

bool Script::LoadScript()
{
	uint size = m_url->get_size();
	for (uint i = 0; i < size; ++i)
	{
		String str = m_url->get1Value(i);

		if (str.LeftOf(11) == "ecmascript:")
		{
			return true;
		}
		else
		{
			if (str.RightOf(6) == ".class")
			{
				return true;
			}
			else if (str.RightOf(6) == ".js")
			{
				return true;
			}
		}
	}

	return false;
}

}
}
