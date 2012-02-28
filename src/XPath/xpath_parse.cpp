#include "stdafx.h"
#include "XPath.h"

namespace System
{
namespace XPath
{
using namespace std;

System::ImmutableString<wchar_t> star_str(L"*");

#include "xpath_parse.tab.c"

}	// XPath
}
