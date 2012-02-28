#include "stdafx.h"
#include "LFC.h"

namespace System
{

String SByteObject::ToString()
{
	return String::FromNumber(GetValue());
}

SByteObject SByteObject::s_values[256];

}	// System
