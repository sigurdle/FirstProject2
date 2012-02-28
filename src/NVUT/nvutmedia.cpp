//----------------------------------------------------------------------------------
// File:   NVUTMedia.cpp
// Email:  sdkfeedback@nvidia.com
// 
// Copyright (c) 2007 NVIDIA Corporation. All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//
//----------------------------------------------------------------------------------

#include <tchar.h>
#include <AtlBase.h>
#include <AtlConv.h>
#include <DXUT.h>
#include <SDKMisc.h>
#include "nvutmedia.h"


HRESULT WINAPI NVUTFindDXSDKMediaFileCch( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename )
{
    HRESULT hr = DXUTFindDXSDKMediaFileCch( strDestPath, cchDest, strFilename );

    if (FAILED(hr))
    {
        WCHAR strFullError[MAX_PATH] = L"The file ";
        StringCchCat( strFullError, MAX_PATH, strFilename );
        StringCchCat( strFullError, MAX_PATH, L" was not found in the search path.\nCannot continue - exiting." );

        MessageBoxW(NULL, strFullError, L"Media file not found", MB_OK);
        exit(0);
    }

    return hr;
}

HRESULT WINAPI NVUTFindDXSDKMediaFileCchT( LPTSTR strDestPath, int cchDest, LPCTSTR strFilename )
{
    HRESULT hr(S_OK);
    USES_CONVERSION;

    CT2W wstrFileName(strFilename);
    LPWSTR wstrDestPath = new WCHAR[cchDest];
    
    hr = NVUTFindDXSDKMediaFileCch(wstrDestPath, cchDest, wstrFileName);
    
    if(!FAILED(hr))
    {
        LPTSTR tstrDestPath = W2T(wstrDestPath);
        _tcsncpy_s(strDestPath, cchDest, tstrDestPath, cchDest);
    }

    delete[] wstrDestPath;

    return hr;
}
