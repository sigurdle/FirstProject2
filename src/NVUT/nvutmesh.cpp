//----------------------------------------------------------------------------------
// File:   NVUTMesh.cpp
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

#include <dxut.h>
#include "SDKmisc.h"
#include <nvutmesh.h>
#pragma warning (disable:4995)
#include <string>

NVUTMesh::NVUTMesh()
{
    CDXUTMesh10();

    m_ppNormalTextures = NULL;
    m_ppNormalSRVs = NULL;
}

HRESULT NVUTMesh::Create( ID3D10Device *pDev10, LPCTSTR szFileName, D3D10_INPUT_ELEMENT_DESC* pLayout, UINT nElements, bool bOptimize)
{
    HRESULT hr;
    V_RETURN(CDXUTMesh10::Create(pDev10, szFileName, pLayout, nElements, bOptimize));

    m_vBox[0] = D3DXVECTOR3(-1, -1, -1);
    m_vBox[1] = D3DXVECTOR3( 1,  1,  1);

    // find bounding box of the mesh we have just loaded
    UINT iPosSemantics = 0;
    for ( ; ; )
    {
        if ( (strcmp(pLayout[iPosSemantics].SemanticName, "POSITION") == 0) || strcmp(pLayout[iPosSemantics].SemanticName, "SV_Position" ) )
        {
            if (pLayout[iPosSemantics].Format != DXGI_FORMAT_R32G32B32_FLOAT)
            {
                MessageBox(NULL, L"Vertices are not in DXGI_FORMAT_R32G32B32_FLOAT format - can not compute bounding box", L"Warning", MB_OK);
                return S_OK;
            }
            break;
        }
        if (++iPosSemantics == nElements)
        {
            MessageBox(NULL, L"\"POSITION\" semantics was not found - can not compute boundingbox.", L"Warning", MB_OK);
            return S_OK;
        }
    }

    ID3DX10MeshBuffer *pVBuffer = NULL;
    V_RETURN(m_pMesh10->GetVertexBuffer(0, &pVBuffer));
    char *pVerts = NULL;
    SIZE_T iSize = 0xffffffff;
    pVBuffer->Map((void **)&pVerts, &iSize);
    m_vBox[0] = D3DXVECTOR3( 1E38f,  1E38f,  1E38f);
    m_vBox[1] = D3DXVECTOR3(-1E38f, -1E38f, -1E38f);
    for (UINT iv = 0; iv < m_dwNumVerts; ++iv)
    {
        D3DXVECTOR3 v = *(D3DVECTOR *)((char *)pVerts + m_uStride * iv);
        m_vBox[0] = D3DXVECTOR3(min(m_vBox[0].x, v.x), min(m_vBox[0].y, v.y), min(m_vBox[0].z, v.z));
        m_vBox[1] = D3DXVECTOR3(max(m_vBox[1].x, v.x), max(m_vBox[1].y, v.y), max(m_vBox[1].z, v.z));
    }
    pVBuffer->Unmap();
    pVBuffer->Release();

    return S_OK;
}

/*
    Do normal mesh loading(our mesh load uses base class first and then calcs bbox), 
    but afterwards load normals based on the file pattern suffix provided.

    With remove all texture filename extensions, add suffix and reattach extensions.  then search for that file.  
    Create Resources and SRVs for each, and add to our list.
*/
HRESULT NVUTMesh::CreateWithNormalMaps(ID3D10Device *pDev10, LPCTSTR szFileName, D3D10_INPUT_ELEMENT_DESC* pLayout, UINT cElements, bool bOptimize, const char*szNormalSuffix)
{
    HRESULT hr;
    V_RETURN(Create(pDev10, szFileName, pLayout, cElements, bOptimize));

    // Set strPath to the path of the mesh file, assuming all normal maps are relative to mesh folder.
    WCHAR        strPath[MAX_PATH];
    DXUTFindDXSDKMediaFileCch( strPath, sizeof(strPath) / sizeof(WCHAR), szFileName );
    WCHAR *pLastBSlash = wcsrchr( strPath, L'\\' );
    if( pLastBSlash )
        *(pLastBSlash + 1) = L'\0';
    else
        *strPath = L'\0';

    // 
    m_ppNormalTextures = new ID3D10Texture2D *[m_dwNumAttr]; 
    ZeroMemory(m_ppNormalTextures,m_dwNumAttr*sizeof(ID3D10Texture2D *));

    m_ppNormalSRVs = new ID3D10ShaderResourceView *[m_dwNumAttr];
    ZeroMemory(m_ppNormalSRVs,m_dwNumAttr*sizeof(ID3D10ShaderResourceView *));

    // Only parse for active attribues
    for(unsigned int iAttrib=0;iAttrib<m_dwNumAttr;iAttrib++)
    {
        if(m_pMats[m_pAttr[iAttrib].AttribId].pTextureFilename)
        {
            ID3D10Resource *pRes = NULL;
            std::string filename = m_pMats[m_pAttr[iAttrib].AttribId].pTextureFilename;

            // Now construct a normals filename implicitly... ugh.
            std::string::size_type pos;
            pos = filename.find_last_of('.');
            if(pos == -1) continue;
            filename.insert(pos,szNormalSuffix);

            WCHAR strTexture[MAX_PATH];
            WCHAR strName[MAX_PATH];
            MultiByteToWideChar( CP_ACP, 0, filename.c_str(), -1, strName, MAX_PATH );
            StringCchCopyW( strTexture, MAX_PATH, strPath );
            StringCchCatW( strTexture, MAX_PATH, strName );

            hr = D3DX10CreateTextureFromFile( pDev10, strTexture, NULL, NULL, &pRes, NULL );
            if( SUCCEEDED(hr) && pRes )
            {
                pRes->QueryInterface( __uuidof( ID3D10Texture2D ), (LPVOID*)&m_ppNormalTextures[iAttrib] );
                D3D10_TEXTURE2D_DESC desc;
                m_ppNormalTextures[iAttrib]->GetDesc( &desc );
                D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
                ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
                SRVDesc.Format = desc.Format;
                SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
                SRVDesc.Texture2D.MipLevels = desc.MipLevels;
                pDev10->CreateShaderResourceView( m_ppNormalTextures[iAttrib], &SRVDesc, &m_ppNormalSRVs[iAttrib] );
                SAFE_RELEASE( pRes );
            }
        }
    }

    return S_OK;
}

// Overridden to bind the normal map SRV if we have one...
void NVUTMesh::Render( ID3D10Device *pDev )
{
    if( m_pMesh10 && m_ppTexture && m_ppSRV )
    {
        for( DWORD subset = 0; subset < m_dwNumAttr; ++subset )
        {
            pDev->PSSetShaderResources( 0, 1, &m_ppSRV[subset] );
            if(m_ppNormalSRVs != NULL) pDev->PSSetShaderResources( 1, 1, &m_ppNormalSRVs[subset] );
            m_pMesh10->DrawSubset( subset );
        }
    }
}

// NOTE, these functions are NOT virtual, so calling into base class will not call back into us.  didn't want to change the 
//  class interface.  expanded functions and code copied from sdkmesh_old.cpp
void NVUTMesh::Render( ID3D10Device *pDev, 
                 ID3D10EffectTechnique *pTechnique, 
                 ID3D10EffectShaderResourceVariable* ptxDiffuse,
                 ID3D10EffectVectorVariable* pvDiffuse, 
                 ID3D10EffectVectorVariable* pvSpecular, 
                 DWORD dwSubset,
                 ID3D10EffectShaderResourceVariable* ptxNormal)
{
    if( !m_pMesh10 )
        return;

    // Draw
    D3D10_TECHNIQUE_DESC techDesc;
    pTechnique->GetDesc( &techDesc );

    for( UINT p = 0; p < techDesc.Passes; ++p )
    {
        DWORD subSetStart = 0;
        DWORD subSetEnd = m_dwNumAttr;

        // If we only want a specific subset, then set range appropriately.
        if( (DWORD)-1 != dwSubset )
        {
            subSetStart = dwSubset;
            subSetEnd = dwSubset+1;
        }

        for( DWORD subset = 0; subset < m_dwNumAttr; ++subset )
        {
            if( m_ppTexture && m_ppSRV[subset] && ptxDiffuse )
                ptxDiffuse->SetResource( m_ppSRV[subset] );

            if( m_ppNormalTextures && m_ppNormalSRVs[subset] && ptxNormal )
                ptxNormal->SetResource( m_ppNormalSRVs[subset] );

            
            if( m_pMats )
            {
                int iMat = m_pAttr[ subset ].AttribId;
                D3DXVECTOR4 v4Diff( m_pMats[iMat].MatD3D.Diffuse.r, 
                                    m_pMats[iMat].MatD3D.Diffuse.g, 
                                    m_pMats[iMat].MatD3D.Diffuse.b, 
                                    m_pMats[iMat].MatD3D.Diffuse.a );
                D3DXVECTOR4 v4Spec( m_pMats[iMat].MatD3D.Specular.r, 
                                    m_pMats[iMat].MatD3D.Specular.g, 
                                    m_pMats[iMat].MatD3D.Specular.b, 
                                    m_pMats[iMat].MatD3D.Specular.a );
                if(pvDiffuse)
                    pvDiffuse->SetFloatVector( (float*)&v4Diff );
                if(pvSpecular)
                    pvSpecular->SetFloatVector( (float*)&v4Spec );
            }

            pTechnique->GetPassByIndex( p )->Apply(0);

            m_pMesh10->DrawSubset( subset );
        }
    }
}

void NVUTMesh::RenderInstanced( ID3D10Device *pDev, 
                          ID3D10EffectTechnique *pTechnique, 
                          UINT uiInstanceCount,
                          ID3D10EffectShaderResourceVariable* ptxDiffuse,
                          ID3D10EffectVectorVariable* pvDiffuse, 
                          ID3D10EffectVectorVariable* pvSpecular )
{
    CDXUTMesh10::RenderInstanced( pDev, pTechnique, uiInstanceCount,ptxDiffuse,pvDiffuse, pvSpecular );
}

// Need to overload to release out normals and SRVs
void NVUTMesh::Destroy()
{
    if(m_ppNormalTextures)
    {
        for(unsigned int i=0;i<m_dwNumAttr;i++)
        {
            SAFE_RELEASE(m_ppNormalTextures[i]);
            SAFE_RELEASE(m_ppNormalSRVs[i]);
        }
    }

    delete [] m_ppNormalTextures;
    delete [] m_ppNormalSRVs;

    CDXUTMesh10::Destroy();
}

