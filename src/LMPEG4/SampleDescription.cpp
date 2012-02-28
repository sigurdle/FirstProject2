#include "stdafx.h"
#include "LMPEG4.h"
#include "SampleDescription.h"

namespace System
{
namespace Mpeg4
{

DecoderSpecificInfo::~DecoderSpecificInfo()
{
}

/*
CSLConfigDescriptor::CSLConfigDescriptor()
{
}
*/

ESDescriptor::ESDescriptor()
{
	m_ES_ID = 0;
	m_dependsOn_ES_ID = 0;

	m_URLstring = NULL;
}

ESDescriptor::~ESDescriptor()
{
	if (m_URLstring)
	{
		delete m_URLstring;
		m_URLstring = NULL;
	}
}

}	// Mpeg4
}
