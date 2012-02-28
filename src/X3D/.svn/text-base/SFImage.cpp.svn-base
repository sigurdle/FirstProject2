#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFImage::SFImage(X3DNode* ownerNode) : X3DField(ownerNode)
{
	m_width = 0;
	m_height = 0;
	m_components = 0;
	m_data = NULL;
}

SFImage::SFImage(TypedX3DFieldDefinition<SFImage>* fieldDef, X3DNode* ownerNode) : X3DField(fieldDef, ownerNode)
{
}

//void SFImage::setValue(ubyte* data)
void SFImage::setValue(String data)
{
	ASSERT(0);
//	m_data = data;
	getOwnerNode()->OnFieldChanged(this);
}

IO::TextWriter& SFImage::WriteValueToStream(IO::TextWriter& stream)
{
	return stream;
}

// virtual
void SFImage::CopyFrom(X3DField* pFrom)
{
	VERIFY(0);
}

}	// x3d
}
