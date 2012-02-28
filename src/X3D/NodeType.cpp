#include "StdAfx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

NodeType::Data* NodeType::s_data = nullptr;

NodeType::NodeType(StringIn nodeName, const Type_Info& classType, X3DFieldDefinition** fields, uint count) :
	m_nodeName(nodeName),
	m_classType(classType)
{
	m_fieldDefinitions = new X3DFieldDefinitions(fields, count);

	Register();
}

FieldType GetFieldTypeOfClass(ClassType* pClass)
{
	struct Test
	{
		FieldType fieldType;
		const Type_Info& typeInfo;
	};

	static Test test[] =
	{
		FieldType_SFBool, typeid(SFBool),
		FieldType_MFBool, typeid(MFBool),
		FieldType_SFInt32, typeid(SFInt32),
		FieldType_MFInt32, typeid(MFInt32),
		FieldType_SFFloat, typeid(SFFloat),
		FieldType_MFFloat, typeid(MFFloat),
		FieldType_SFDouble, typeid(SFDouble),
		FieldType_MFDouble, typeid(MFDouble),
		FieldType_SFVec2f, typeid(SFVec2f),
		FieldType_MFVec2f, typeid(MFVec2f),
		FieldType_SFVec3f, typeid(SFVec3f),
		FieldType_MFVec3f, typeid(MFVec3f),
		FieldType_SFTime, typeid(SFTime),
	//	FieldType_MFTime, typeid(MFTime),
		FieldType_SFRotation, typeid(SFRotation),
		FieldType_MFRotation, typeid(MFRotation),
		FieldType_SFColor, typeid(SFColor),
		FieldType_MFColor, typeid(MFColor),
		FieldType_SFColorRGBA, typeid(SFColorRGBA),
	//	FieldType_MFColorRGBA, typeid(MFColorRGBA),
		FieldType_SFString, typeid(SFString),
		FieldType_MFString, typeid(MFString),
	//	FieldType_SFURL, typeid(SFURL),
		FieldType_MFURL, typeid(MFURL),
		FieldType_SFImage, typeid(SFImage),
	//	FieldType_MFImage, typeid(MFImage),
		FieldType_SFNode, typeid(SFNode),
		FieldType_MFNode, typeid(MFNode),
	};
	uint count = _countof(test);

	for (uint i = 0; i < count; ++i)
	{
		if (pClass->IsDerivedFrom(test[i].typeInfo.GetType()->AsClass()))
		{
			return test[i].fieldType;
		}
	}

	ASSERT(0);
	raise(Exception(L"field of unknown type"));
}

NodeType::NodeType(StringIn nodeName, const Type_Info& classType, X3DFieldDefinition** fields, uint fieldCount, NodeType* baseType) :
	m_nodeName(nodeName),
	m_classType(classType),
	m_fields(fields),
	m_fieldCount(fieldCount)
{
	ASSERT(baseType != this);

	ClassType* pClassType = dynamic_cast<ClassType*>(m_classType.GetType());
	ASSERT(pClassType);
	pClassType->SetUserData(L"System::x3d::NodeType", this);

	uint i = 0;
	while (i < fieldCount)
	{
		X3DFieldDefinition* f = fields[i];

		if (f->m_offset > 0)
		{
			Declarator* decl = pClassType->GetMemberByOffset(f->m_offset);

			if (decl == NULL)
			{
				ASSERT(0);
				raise(Exception(L"offset not found"));
			}

			Type* pType = decl->get_Type()->GetStripped();
			if (pType->get_Kind() != type_pointer)
			{
				ASSERT(0);
				raise(Exception(L"not a pointer"));
			}

			if (pType->GetPointerTo()->get_Kind() != type_class)
			{
				ASSERT(0);
				raise(Exception(L"not a pointer to class type"));
			}

			ClassType* pType2 = pType->GetPointerTo()->AsClass();

			f->m_fieldType = GetFieldTypeOfClass(pType2);

#if 0
			if (pType2->IsDerivedFrom(typeof(SFBool)->GetClass())
			{
				f->m_fieldType = FieldType_SFBool;
			}
			else if (pType2->IsDerivedFrom(typeof(MFBool)->GetClass())
			{
				f->m_fieldType = FieldType_MFBool;
			}

			else if (pType2->IsDerivedFrom(typeof(SFInt32)->GetClass())
			{
				f->m_fieldType = FieldType_SFInt32;
			}
			else if (pType2->IsDerivedFrom(typeof(MFInt32)->GetClass())
			{
				f->m_fieldType = FieldType_MFInt32;
			}
#endif

#if 0
			ClassType* pFieldType = NULL;
			switch (f->m_fieldType)
			{
			case FieldType_SFBool: pFieldType = typeid(SFBool).GetType()->GetClass(); break;
			case FieldType_MFBool: pFieldType = typeid(MFBool).GetType()->GetClass(); break;

			case FieldType_MFInt32: pFieldType = typeid(MFInt32).GetType()->GetClass(); break;
			case FieldType_SFInt32: pFieldType = typeid(SFInt32).GetType()->GetClass(); break;

			case FieldType_SFFloat: pFieldType = typeid(SFFloat).GetType()->GetClass(); break;
			case FieldType_MFFloat: pFieldType = typeid(MFFloat).GetType()->GetClass(); break;

			case FieldType_SFDouble: pFieldType = typeid(SFDouble).GetType()->GetClass(); break;
			case FieldType_MFDouble: pFieldType = typeid(MFDouble).GetType()->GetClass(); break;

			case FieldType_SFTime: pFieldType = typeid(SFTime).GetType()->GetClass(); break;
		//	case FieldType_MFTime: pFieldType = typeid(MFTime).GetType()->GetClass(); break;

			case FieldType_SFNode: pFieldType = typeid(SFNode).GetType()->GetClass(); break;
			case FieldType_MFNode: pFieldType = typeid(MFNode).GetType()->GetClass(); break;

			case FieldType_SFVec2f: pFieldType = typeid(SFVec2f).GetType()->GetClass(); break;
			case FieldType_MFVec2f: pFieldType = typeid(MFVec2f).GetType()->GetClass(); break;

			}

			if (pFieldType)
			{
				if (!pType2->IsDerivedFrom(pFieldType))
				{
					ASSERT(0);
				}
			}
#endif
		}

		++i;
	}

	if (!nodeName.IsEmpty())
	{
		// Build an array of the nodeType and baseTypes
		NodeType* arr[34];
		uint nclasses = 0;

	//	arr[nclasses++] = this;
		uint nfields = 0;
		NodeType* n = this;

		do
		{
			if (nclasses > 32)
			{
				ASSERT(0);
				raise(Exception(L"Too many baseTypes"));
			}

			arr[nclasses++] = n;
			nfields += n->m_fieldCount;

			n = n->GetBaseNodeType();
		}
		while (n);

		m_fieldDefinitions = new X3DFieldDefinitions(nfields);

		// Add the fields of the nodeTypes, starting with the topmost superclass to the most derived class
		for (uint j = 0; j < nclasses; ++j)
		{
			NodeType* n = arr[nclasses-j-1];

			for (uint i = 0; i < n->m_fieldCount; ++i)
			{
				m_fieldDefinitions->m_items.push_back(n->m_fields[i]);
			}
		}

		if (s_data == NULL) s_data = new Data;

		s_data->m_nodeTypes.push_back(this);
		s_data->m_nodeTypeByName[m_nodeName] = this;
	}
}

NodeType* NodeType::GetBaseNodeType() const
{
	return (NodeType*)GetClassType()->m_bases[0]->m_pClass->AsClass()->GetUserData(L"System::x3d::NodeType");
}

void NodeType::Register()
{
	return;

	ClassType* pClassType = dynamic_cast<ClassType*>(m_classType.GetType());
	ASSERT(pClassType);

	pClassType->SetUserData(L"System::x3d::NodeType", this);

//	TRACE("nodeTypes: %d - ", nodeTypes->m_items.size());
//	TRACE("%S\n", nodeName->c_str());

//	NodeType* pNodeType = new NodeType(get_name(), m_classType);

	uint i = 0;
	uint count = m_fieldDefinitions->get_length();
	while (i < count)
	{
		X3DFieldDefinition* f = m_fieldDefinitions->item(i);

		if (f->m_offset > 0)
		{
			Declarator* decl = pClassType->GetMemberByOffset(f->m_offset);

			if (decl == NULL)
			{
				ASSERT(0);
			}

			Type* pType = decl->get_Type()->GetStripped();
			if (pType->get_Kind() != type_pointer)
			{
				ASSERT(0);
			}

			if (pType->GetPointerTo()->get_Kind() != type_class)
			{
				ASSERT(0);
			}

			ClassType* pType2 = pType->GetPointerTo()->AsClass();

			ClassType* pFieldType = nullptr;
			switch (f->m_fieldType)
			{
			case FieldType_SFBool: pFieldType = typeid(SFBool)->AsClass(); break;
			case FieldType_MFBool: pFieldType = typeid(MFBool)->AsClass(); break;

			case FieldType_MFInt32: pFieldType = typeid(MFInt32)->AsClass(); break;
			case FieldType_SFInt32: pFieldType = typeid(SFInt32)->AsClass(); break;

			case FieldType_SFFloat: pFieldType = typeid(SFFloat)->AsClass(); break;
			case FieldType_MFFloat: pFieldType = typeid(MFFloat)->AsClass(); break;

			case FieldType_SFDouble: pFieldType = typeid(SFDouble)->AsClass(); break;
			case FieldType_MFDouble: pFieldType = typeid(MFDouble)->AsClass(); break;

			case FieldType_SFTime: pFieldType = typeid(SFTime)->AsClass(); break;
		//	case FieldType_MFTime: pFieldType = typeid(MFTime).GetType()->GetClass(); break;

			case FieldType_SFNode: pFieldType = typeid(SFNode)->AsClass(); break;
			case FieldType_MFNode: pFieldType = typeid(MFNode)->AsClass(); break;

			case FieldType_SFVec2f: pFieldType = typeid(SFVec2f)->AsClass(); break;
			case FieldType_MFVec2f: pFieldType = typeid(MFVec2f)->AsClass(); break;

				/*
	FieldType_SFVec2d	= 17,
	FieldType_MFVec2d	= 18,

	FieldType_SFVec3f	= 19,
	FieldType_MFVec3f	= 20,

	FieldType_SFVec3d	= 21,
	FieldType_MFVec3d	= 22,

	FieldType_MFRotation	= 23,
	FieldType_SFRotation	= 24,

	FieldType_MFColor	= 25,
	FieldType_SFColor	= 26,

	FieldType_MFColorRGBA = 27,
	FieldType_SFColorRGBA = 28,

	FieldType_SFImage	= 29,
	FieldType_MFImage	= 30,

	FieldType_SFString = 31,
	FieldType_MFString = 32,

	// ??
	FieldType_SFURL	= 35,
	FieldType_MFURL	= 36,

	FieldType_SFMatrix4f = 37,
	FieldType_MFMatrix4f = 38,

	FieldType_SFMatrix3f = 39,
	FieldType_MFMatrix3f = 40,
	*/
			}

			if (pFieldType)
			{
				if (!pType2->IsDerivedFrom(pFieldType))
				{
					ASSERT(0);
				}
			}
		}

	//	X3DFieldDefinition* pFieldDefinition = new X3DFieldDefinition(f);

#if 0
		if (true)	// Hack
		{
			//while (f->fieldName)
			{
				ASSERT(f->fieldName);
				AddPersistentLiveRoot((void**)&f->fieldName);

				//f++;
			}
		}
#endif

	//	pNodeType->m_fieldDefinitions->m_items.push_back(pFieldDefinition);

		++i;
	}

//	nodeTypes->m_items.Add(pNodeType);
	if (s_data == nullptr) s_data = new Data;

	s_data->m_nodeTypes.push_back(this);
	s_data->m_nodeTypeByName[m_nodeName] = this;
}

X3DNode* NodeType::CreateNode()
{
	Object* obj = newobj(GetClassType());
	return dynamic_cast<X3DNode*>(obj);
}

IO::TextWriter& NodeType::WriteX3DDef(IO::TextWriter& stream)
{
	ClassType* pClass = GetClassType();

	stream << m_nodeName << " : ";
	for (uint i = 0; i < pClass->m_bases.size(); ++i)
	{
		stream << pClass->m_bases[i]->m_pClass->get_Name();
		stream << " ";
	}

	stream << "\n{\n";

	X3DFieldDefinitions* fields = getFieldDefinitions();

	for (uint i = 0; i < fields->get_length(); ++i)
	{
		X3DFieldDefinition* fieldDef = fields->item(i);

		stream << fieldDef->getFieldTypeString() << " ";

		switch (fieldDef->getAccessType())
		{
		case SAIFieldAccess_initializeOnly:	stream << "[]";	break;
		case SAIFieldAccess_inputOnly:	stream << "[in]";	break;
		case SAIFieldAccess_outputOnly:	stream << "[out]";	break;
		case SAIFieldAccess_inputOutput:	stream << "[in,out]";	break;
		}

		stream << " ";
		stream << "\t";
		stream << fieldDef->getName();
		stream << " ";
		stream << "\t";
		fieldDef->WriteDefaultValue(stream);

		stream << "[";
		fieldDef->WriteDomain(stream);
		stream << "]";

		stream << "\n";
	}

	stream << "\n}\n";

	return stream;
}

String NodeType::ToString()
{
	IO::StringWriter str;
	WriteX3DDef(str);
	return str.str();

//	return m_nodeName;
}

// static
NodeType* NodeType::FindByName(StringIn name)
{
	return s_data->m_nodeTypeByName.find(name)->second;
	/*
	// TODO

	for (unsigned int i = 0; i < s_nodeTypes.GetSize(); i++)
	{
		if (s_nodeTypes[i]->get_name() == name)
		{
			return s_nodeTypes[i];
		}
	}
	*/

	return nullptr;
}

}	// x3d
}	// System
