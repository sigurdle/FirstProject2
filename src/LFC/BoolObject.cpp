#include "stdafx.h"
#include "LFC.h"

namespace System
{

String BoolObject::ToString()
{
	return GetValue()? S("true"): S("false");
}

BoolObject BoolObject::s_values[2];

}	// System
