#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

CTOR X3DField::X3DField(const X3DField& other) : m_fieldDef(other.m_fieldDef), m_ownerNode(other.getOwnerNode()), m_inputRoute(nullptr)
{
}

X3DField::X3DField(X3DNode* ownerNode) : m_ownerNode(ownerNode), m_inputRoute(nullptr)
{
}

X3DField::X3DField(X3DFieldDefinition* fieldDef, X3DNode* ownerNode) : m_fieldDef(fieldDef), m_ownerNode(ownerNode), m_inputRoute(nullptr)
{
}

X3DField::~X3DField()
{
}

bool X3DField::isWritable()
{
	return true;
}  

bool X3DField::isReadable()
{
	return true;
}  

String X3DField::getFieldName() const throw()
{
	if (m_fieldDef)
		return m_fieldDef->getName();
	else
		return m_fieldName;
}

X3DEXT bool IsSField(FieldType fieldType)
{
	// TODO: return ((int)fieldType & 1); or not, isn't correct

	switch (fieldType)
	{
	case FieldType_SFBool:
	case FieldType_SFInt32:
	case FieldType_SFColor:
	case FieldType_SFColorRGBA:
	case FieldType_SFFloat:
	case FieldType_SFDouble:
	case FieldType_SFTime:
	case FieldType_SFImage:
	case FieldType_SFVec2f:
	case FieldType_SFVec3f:
	case FieldType_SFVec4f:
	case FieldType_SFNode:
	case FieldType_SFString:
	case FieldType_SFURL:
	case FieldType_SFMatrix4f:
	case FieldType_SFRotation:
		return true;

	case FieldType_MFBool:
	case FieldType_MFInt32:
	case FieldType_MFColor:
	case FieldType_MFColorRGBA:
	case FieldType_MFFloat:
	case FieldType_MFDouble:
	case FieldType_MFTime:
	case FieldType_MFImage:
	case FieldType_MFVec2f:
	case FieldType_MFVec3f:
	case FieldType_MFNode:
	case FieldType_MFString:
	case FieldType_MFURL:
	case FieldType_MFMatrix4f:
		return false;

	default:
		raise(Exception(WSTR("Unknown field type")));
		ASSERT(0);
	}
}

Type* FieldBinding::GetOutputType()
{
	switch (m_field->m_fieldDef->getFieldType())
	{
		case FieldType_SFBool:		return typeid(bool);
		case FieldType_SFInt32:		return typeid(int32);
		case FieldType_SFFloat:		return typeid(float);
		case FieldType_SFDouble:		return typeid(double);

		default:
			ASSERT(0);
	}

	return NULL;
}

int FieldBinding::SetInput(Gui::IBinding* caller, const Variant& value)
{
	Vec3f val = ((SFVec3f*)m_field)->getValue();
	val[0] = ToFloat(value);

	((SFVec3f*)m_field)->setValue(val);

	return 0;
}

}	// x3d
}	// System
