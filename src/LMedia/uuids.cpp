#define INITGUID

#if WIN32
#include <guiddef.h>
#define LMEDIAEXT __declspec(dllexport)
#else

//#include "../amiga_header.h"

#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif

#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef struct _GUID
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
}
GUID;

#endif

#define LMEDIAEXT
#endif

#include "Luuids.h"
