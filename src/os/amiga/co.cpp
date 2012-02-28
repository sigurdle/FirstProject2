#if AMIGA
#define BOOL shortBOOL
#define BYTE signedBYTE
#define WORD signedWORD
#define BSTR amigaBSTR
#define VOID void

#include <dos/dos.h>
#include <proto/dos.h>

#undef BOOL
#undef BYTE
#undef WORD
#undef BSTR
#undef VOID

#ifdef Seek
#define dosSeek Seek
#undef Seek
#endif

#endif // AMIGA

#include <atlbase.h>

EXTERN_C HRESULT OleInitialize(void*)
{
	struct FileInfoBlock* fib = (struct FileInfoBlock*)AllocDosObject(DOS_FIB, NULL);
	if (fib)
	{
		BPTR lock = Lock("ENV:coregistry", ACCESS_READ);
		if (lock)
		{
			Examine(lock, fib);

			while (ExNext(lock, fib))
			{
				if (fib->fib_DirEntryType > 0)	// directory
				{
				}

				fib->fib_FileName;
			}
			if (IoErr() != ERROR_NO_MORE_ENTRIES)
			{
				//MessageBox(NULL, "dos Error", "", MB_OK);
			}

			UnLock(lock);
		}

		FreeDosObject(DOS_FIB, fib);
	}

	return S_OK;
}

void Convert(unsigned long number, int nchars, OLECHAR* buf)
{
	for (int i = nchars-1; i >= 0; i--)
	{
		int v = number&0xf;
		if (v < 10)
			buf[i] = '0'+v;
		else
			buf[i] = 'a'+v-10;

		number >>= 4;
	}
	ATLASSERT(number == 0);
}

/*
The string that the lpsz parameter receives has a format like that of the following sample:

{c200e360-38c5-11ce-ae62-08002b2b79ef} 
 
where the successive fields break the GUID into the form DWORD-WORD-WORD-WORD-WORD.DWORD covering the 128-bit GUID. The string includes enclosing braces, which are an OLE convention.

*/
EXTERN_C int StringFromGUID2(
	REFGUID rguid,  //Interface identifier to be converted
	LPOLESTR lpsz,  //Pointer to the resulting string on return
	int cchMax)       //Character count of string at lpsz
{
	if (cchMax < 36+2+1) return 0;	// Buffer too small

	typedef struct
	{
		DWORD Data1;
		WORD Data2;
		WORD Data3;
		WORD Data4;
		WORD Data5;
		DWORD Data6;
	}
	__GUID;

	__GUID &r = (__GUID&)rguid;

	OLECHAR* p = lpsz;
	*p++ = '{';

	Convert(r.Data1, 8, p);
	p += 8;
	*p++ = '-';

	Convert(r.Data2, 4, p);
	p += 4;
	*p++ = '-';

	Convert(r.Data3, 4, p);
	p += 4;
	*p++ = '-';

	Convert(r.Data4, 4, p);
	p += 4;
	*p++ = '-';

	Convert(r.Data5, 4, p);
	p += 4;

	Convert(r.Data6, 8, p);
	p += 8;

	*p++ = '}';

	*p = 0;	// null-terminate string

	return 36+2+1;
}

EXTERN_C HRESULT StringFromCLSID(
	REFCLSID rclsid, //CLSID to be converted
	LPOLESTR * ppsz)  //Address of output variable that receives a 
                   // pointer to the resulting string
{
	if (ppsz == NULL)
		return E_POINTER;

	int len  = 36+2;
	LPOLESTR buf = (LPOLESTR)CoTaskMemAlloc((len+1)*2);
	if (buf == NULL)
		return E_OUTOFMEMORY;

	HRESULT hr = StringFromGUID2(rclsid, buf, len);
	if (FAILED(hr))
	{
		CoTaskMemFree(buf);
		return hr;
	}

	*ppsz = buf;

	return S_OK;
}

EXTERN_C HRESULT CoGetClassObject(
	REFCLSID rclsid,  //CLSID associated with the class object
	DWORD dwClsContext,
                    //Context for running executable code
	LPVOID pvReserved,
 // COSERVERINFO * pServerInfo,
                    //Pointer to machine on which the object is to 
                    // be instantiated
	REFIID riid,      //Reference to the identifier of the interface
	LPVOID * ppv      //Address of output variable that receives the 
                    // interface pointer requested in riid
)
{
//	StringFromGUID2
	return S_OK;
}

EXTERN_C HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv)
{
	IClassFactory* pCF;
	HRESULT hr = CoGetClassObject(rclsid, dwClsContext, NULL, IID_IClassFactory, (void**)&pCF);
	if (SUCCEEDED(hr))
	{
		hr = pCF->CreateInstance(pUnkOuter, riid, ppv);
		pCF->Release();
	}

	return hr;
}
