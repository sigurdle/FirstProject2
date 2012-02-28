// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <LFC/LFC.h>

// Windows Header Files:

/*
#include <intsafe.h>
#include <objbase.h>
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <comdef.h>
#include <commdlg.h>
*/
// DirectShow Header Files
#include <dshow.h>
//#include <streams.h>

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

#include <d3d9.h>
#include <vmr9.h>

#define DShowPlayerExt DECLSPEC_DLLEXPORT
