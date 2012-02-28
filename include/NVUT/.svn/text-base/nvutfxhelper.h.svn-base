//----------------------------------------------------------------------------------
// File:   NVUTFXHelper.h
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

#pragma once
#ifndef NVUTFXHELPER_H
#define NVUTFXHELPER_H

#include <windows.h>
#include <strsafe.h>

#define __TSTR_LENGTH 1024
static TCHAR __tstr[__TSTR_LENGTH];


#define V_GET_TECHNIQUE( pEffect, pEffectPathTstr, pEffTech, pTechniqueNameStr ) pEffTech = pEffect->GetTechniqueByName(pTechniqueNameStr); \
    if( !pEffTech || !pEffTech->IsValid() ) \
    {\
        StringCbPrintf(__tstr, __TSTR_LENGTH, TEXT("Failed Getting Technique: \"%hs\" in effect file %s."), pTechniqueNameStr, pEffectPathTstr) ;\
        MessageBox(NULL, __tstr, TEXT("Direct3D 10 Effect Init Error - Bad Technique"), MB_ABORTRETRYIGNORE|MB_ICONWARNING);\
        hr = E_FAIL;\
    }

#define V_GET_TECHNIQUE_RET( pEffect, pEffectPathTstr, pEffTech, pTechniqueNameStr ) V_GET_TECHNIQUE(pEffect, pEffectPathTstr, pEffTech, pTechniqueNameStr )\
    if( FAILED(hr) )\
        return hr;

#define V_GET_TECHNIQUE_RETBOOL( pEffect, pEffectPathTstr, pEffTech, pTechniqueNameStr ) V_GET_TECHNIQUE(pEffect, pEffectPathTstr, pEffTech, pTechniqueNameStr )\
    if( FAILED(hr) )\
        return false;


#define V_GET_PASS( pTechnique, pEffectPathTstr, pPass, pPassNameStr ) pPass = pTechnique->GetPassByName(pPassNameStr); \
    if( !pPass || !pPass->IsValid() ) \
    {\
        D3D10_TECHNIQUE_DESC techDesc;\
        pTechnique->GetDesc(&techDesc);\
        StringCbPrintf(__tstr, __TSTR_LENGTH, TEXT("Failed Getting Pass \"%hs\" from technique %hs, in effect file  %s."), pPassNameStr, techDesc.Name, pEffectPathTstr);\
        MessageBox(NULL, __tstr, TEXT("Direct3D 10 Effect Init Error - Bad Pass"), MB_ABORTRETRYIGNORE|MB_ICONWARNING);\
        hr = E_FAIL;\
    }

#define V_GET_PASS_RET( pTechnique, pEffectPathTstr, pPass, pPassNameStr ) V_GET_PASS(pTechnique, pEffectPathTstr, pPass, pPassNameStr)\
    if( FAILED(hr) )\
        return hr;

#define V_GET_PASS_RETBOOL( pTechnique, pEffectPathTstr, pPass, pPassNameStr ) V_GET_PASS(pTechnique, pEffectPathTstr, pPass, pPassNameStr)\
    if( FAILED(hr) )\
        return false;


#define V_GET_VARIABLE( pEffect, pEffectPathTstr, pEffVar, pVarNameStr, asVariable ) pEffVar = pEffect->GetVariableByName(pVarNameStr)->asVariable(); \
    if( !pEffVar || !pEffVar->IsValid() ) \
    {\
        StringCbPrintf(__tstr, __TSTR_LENGTH, TEXT("Failed Getting Variable \"%hs\" in effect file %s."), pVarNameStr, pEffectPathTstr);\
        MessageBox(NULL, __tstr, TEXT("Direct3D 10 Effect Init Error - Bad Variable"), MB_ABORTRETRYIGNORE|MB_ICONWARNING);\
        hr = E_FAIL;\
    }

#define V_GET_VARIABLE_RET( pEffect, pEffectPathTstr, pEffVar, pVarNameStr, asVariable ) V_GET_VARIABLE(pEffect, pEffectPathTstr, pEffVar, pVarNameStr, asVariable )\
    if( FAILED(hr) )\
        return hr;

#define V_GET_VARIABLE_RETBOOL( pEffect, pEffectPathTstr, pEffVar, pVarNameStr, asVariable ) V_GET_VARIABLE(pEffect, pEffectPathTstr, pEffVar, pVarNameStr, asVariable )\
    if( FAILED(hr) )\
        return false;

#endif // NVUTFXHELPER_H
