#if AMIGA

// These must be at the beginning, because of naming conflicts with windows

#define BOOL shortBOOL
#define BYTE signedBYTE
#define WORD signedWORD
#define BSTR amigaBSTR
#define VOID void

#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/intuition.h>

#ifdef Enable
#define execEnable Enable
#undef Enable
#endif

#ifdef AddTail
#define execAddTail AddTail
#undef AddTail
#endif

#ifdef AddHead
#define execAddHead AddHead
#undef AddHead
#endif

#ifdef Insert
#define execInsert Insert
#undef Insert
#endif

#ifdef Remove
#define execRemove Remove
#undef Remove
#endif

#undef BOOL
#undef BYTE
#undef WORD
#undef BSTR
#undef VOID

#endif // AMIGA

#include <atlbase.h>

#if AMIGA
EXTERN_C BOOL MessageBeep(UINT uType)
{
	return TRUE;	// Success
}

EXTERN_C int MessageBoxA(
    IN HWND hWnd,
    IN LPCSTR lpText,
    IN LPCSTR lpCaption,
    IN UINT uType)
{
	struct EasyStruct es =
	{
		sizeof(es),	// es_StructSize
		0,	//es_Flags
		(UBYTE*)lpCaption, // es_Title;
		(UBYTE*)lpText//es_TextFormat
	};

	switch (uType & MB_TYPEMASK)
	{
	case MB_OK:
		es.es_GadgetFormat = (UBYTE*)"OK";
		break;

	case MB_OKCANCEL:
		es.es_GadgetFormat = (UBYTE*)"OK|Cancel";
		break;

	case MB_ABORTRETRYIGNORE:
		es.es_GadgetFormat = (UBYTE*)"Abort|Retry|Ignore";
		break;

	case MB_YESNOCANCEL:
		es.es_GadgetFormat = (UBYTE*)"Yes|No|Cancel";
		break;

	case MB_YESNO:
		es.es_GadgetFormat = (UBYTE*)"Yes|No";
		break;

	case MB_RETRYCANCEL:
		es.es_GadgetFormat = (UBYTE*)"Retry|Cancel";
		break;

	case MB_CANCELTRYCONTINUE:
		es.es_GadgetFormat = (UBYTE*)"Cancel|Try|Continue";
		break;

	default:
		ATLASSERT(0);
	}

	int num = EasyRequestArgs(NULL/*Window*/, &es, NULL/*idcmp_ptr*/, NULL);

	switch (uType & MB_TYPEMASK)
	{
	case MB_OK:
		return IDOK;

	case MB_OKCANCEL:
		if (num == 0)
			return IDOK;
		else
			return IDCANCEL;

	case MB_ABORTRETRYIGNORE:
		if (num == 0)
			return IDABORT;
		else if (num == 1)
			return IDRETRY;
		else
			return IDIGNORE;

	case MB_YESNOCANCEL:
		if (num == 0)
			return IDYES;
		else if (num == 1)
			return IDNO;
		else
			return IDCANCEL;

	case MB_YESNO:
		if (num == 0)
			return IDYES;
		else
			return IDNO;

	default:
		ATLASSERT(0);
		return -1;
	}
}

#endif // AMIGA