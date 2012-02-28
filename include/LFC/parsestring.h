#ifndef __PARSESTRING_H_
#define __PARSESTRING_H_

namespace System
{

LFCEXT String stripspaces(StringIn s);
//LFCEXT String stripspaces(System::StringW* s);

LFCEXT size_t GetCommaSepStringArray(StringIn str, vector<String>& values);

template<class ARR_TYPE> LFCEXT size_t GetSpaceSepStringArray(StringIn str, ARR_TYPE& values);

//LFCEXT int GetSpaceSepStringArray(System::StringW* str, vector<System::StringW*>& values);
//LFCEXT int GetSpaceSepStringArray(System::StringW* str, vector<System::StringW*, System::grow_allocator>& values);

LFCEXT size_t GetSemicolonSepStringArray(StringIn str, vector<String>& values);
LFCEXT size_t GetCommaOrSpaceSepStringArray(StringIn str, vector<String>& values);
LFCEXT size_t GetCommaOrSpaceSepNumberArray(StringIn str, vector<double>& values);
LFCEXT size_t GetSemicolonOrSpaceSepNumberArray(StringIn str, vector<double>& values);

}

#endif // __PARSESTRING_H_
