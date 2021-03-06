#include "stdafx.h"
#include "LFC.h"
#include "vector.h"

namespace System
{

template class LFCEXT vector<bool>;
template class LFCEXT vector<char>;
template class LFCEXT vector<wchar_t>;
template class LFCEXT vector<signed char>;
template class LFCEXT vector<unsigned char>;
template class LFCEXT vector<short>;
template class LFCEXT vector<unsigned short>;
template class LFCEXT vector<int>;
template class LFCEXT vector<unsigned int>;
template class LFCEXT vector<long>;
template class LFCEXT vector<unsigned long>;
template class LFCEXT vector<float>;
template class LFCEXT vector<double>;
template class LFCEXT vector<long long>;
template class LFCEXT vector<unsigned long long>;

template class LFCEXT vector<String>;
template class LFCEXT vector<Variant>;
template class LFCEXT vector<Object*>;

}	// System
