//----------------------------------------------------------------------------------
// File:   NVUTVertexShader.cpp
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

#include "DXUT.h"
#include "NVUTVertexShader.h"

NVUTVertexShader::NVUTVertexShader():NVUTShader()
{
    m_pVS = NULL;
    m_pInputLayout = NULL;
    m_VertexSize = 0;
    m_pIEDLayout = NULL;
}

NVUTVertexShader::~NVUTVertexShader()
{
}

HRESULT NVUTVertexShader::CreateFromFile(ID3D10Device* pd3dDevice, LPCWSTR pSrcFile, CONST D3D10_SHADER_MACRO* pDefines, 
                                         LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2)
{
    HRESULT hr;
    NVUTVertexShader::CustomIncludeInterface includeInterface;

    // Inherited compile and reflect
    V(CompileShader(pd3dDevice,pSrcFile,pDefines,pFunctionName,pProfile,Flags1,Flags2));

    V(pd3dDevice->CreateVertexShader(m_pShaderByteCode->GetBufferPointer(),m_pShaderByteCode->GetBufferSize(),&m_pVS));


    D3D10_SHADER_DESC sdesc;
    m_pReflectedShader->GetDesc(&sdesc);

    // InputLayout

    // Count real elements, so we don't allocate space for a system value
    m_NumIEDElements = 0;
    for(int iInputParam=0;iInputParam<(int)sdesc.InputParameters;iInputParam++)
    {
        D3D10_SIGNATURE_PARAMETER_DESC pdesc;
        m_pReflectedShader->GetInputParameterDesc(iInputParam,&pdesc);

        if(pdesc.SystemValueType == D3D10_NAME_UNDEFINED && pdesc.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
            m_NumIEDElements++;
    }

    m_pIEDLayout = new D3D10_INPUT_ELEMENT_DESC[m_NumIEDElements];

    // Parse Vertex Shader and generate the Input layout
    int ByteOffset = 0;
    int iLayoutSlot = 0;
    for(int iInputParam=0;iInputParam<(int)sdesc.InputParameters;iInputParam++)
    {
        D3D10_SIGNATURE_PARAMETER_DESC pdesc;
        m_pReflectedShader->GetInputParameterDesc(iInputParam,&pdesc);
        if(pdesc.SystemValueType == D3D10_NAME_UNDEFINED && pdesc.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
        {
            m_pIEDLayout[iLayoutSlot].SemanticName = pdesc.SemanticName;
            m_pIEDLayout[iLayoutSlot].SemanticIndex = pdesc.SemanticIndex;
            m_pIEDLayout[iLayoutSlot].AlignedByteOffset = ByteOffset; // $ Keep this before incrementing ByteOffset!!!

            const unsigned char parity_array[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
            switch(parity_array[pdesc.Mask])
            {
            default:
            case 0:
                assert(0);
            case 1:
                m_pIEDLayout[iLayoutSlot].Format = DXGI_FORMAT_R32_FLOAT;
                ByteOffset += 4;
                break;

            case 2:
                m_pIEDLayout[iLayoutSlot].Format = DXGI_FORMAT_R32G32_FLOAT;
                ByteOffset += 8;
                break;

            case 3:
                m_pIEDLayout[iLayoutSlot].Format = DXGI_FORMAT_R32G32B32_FLOAT;
                ByteOffset += 12;
                break;

            case 4:
                m_pIEDLayout[iLayoutSlot].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                ByteOffset += 16;
                break;
            }

            m_pIEDLayout[iLayoutSlot].InputSlot = 0;
            m_pIEDLayout[iLayoutSlot].InstanceDataStepRate = 0;
            m_pIEDLayout[iLayoutSlot].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
            iLayoutSlot++;
        }
    }
    V(pd3dDevice->CreateInputLayout(m_pIEDLayout,m_NumIEDElements,m_pShaderByteCode->GetBufferPointer(),m_pShaderByteCode->GetBufferSize(),&m_pInputLayout));
    m_VertexSize = ByteOffset;


#ifndef _DEBUG
    // Not in DEBUG then release the Blobs
    SAFE_RELEASE(m_pCompileErrors);
    SAFE_RELEASE(m_pShaderByteCode);
#endif

    return hr;
}

void NVUTVertexShader::Release()
{
    NVUTShader::Release();
    SAFE_RELEASE(m_pVS);
    SAFE_RELEASE(m_pInputLayout);
    SAFE_DELETE_ARRAY(m_pIEDLayout);
}