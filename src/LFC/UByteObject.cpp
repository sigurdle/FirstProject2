#include "stdafx.h"
#include "LFC.h"

namespace System
{

String UByteObject::ToString()
{
	return String::FromNumber(GetValue());
}

UByteObject UByteObject::s_values[256];

}	// System
