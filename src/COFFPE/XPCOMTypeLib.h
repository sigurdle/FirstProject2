
/*
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
*/

#ifndef GUID_DEFINED
typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;
#endif

namespace System
{

class IXPTypeLib;

typedef struct _XPIFACEATTR
{
	GUID guid;
	long cFuncs;
}
XPIFACEATTR, *LPXPIFACEATTR;

typedef struct _XPFUNCDESC
{
	System::StringA* name;
}
XPFUNCDESC;

class IXPIFaceInfo
{
public:
	virtual System::StringA* GetName() const = 0;
	virtual System::StringA* GetNamespace() const = 0;
	virtual ErrorCode GetIFaceAttr(XPIFACEATTR* *ppIFaceAttr) = 0;
	virtual ErrorCode ReleaseIFaceAttr(XPIFACEATTR* pIFaceAttr) = 0;
	virtual ErrorCode GetFuncDesc(unsigned long index, XPFUNCDESC* *ppFuncDesc) = 0;
	virtual ErrorCode ReleaseFuncDesc(XPFUNCDESC* pFuncDesc) = 0;
	virtual ErrorCode GetContainingTypeLib(IXPTypeLib* *ppTLib,  unsigned int *pIndex) = 0;
};

class IXPTypeLib
{
public:
	virtual ErrorCode GetIFace(long index, IXPIFaceInfo* *pVal) = 0;
	virtual ErrorCode GetIFaceCount() = 0;
};

ErrorCode XPTypeLibParse(FILE* fp, IXPTypeLib* *pVal);

}
