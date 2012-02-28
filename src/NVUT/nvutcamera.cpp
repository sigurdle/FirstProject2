//----------------------------------------------------------------------------------
// File:   NVUTCamera.cpp
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
#include <nvutcamera.h>

void NVUTCamera::SetProjParams(FLOAT fFOV, FLOAT fAspect, D3DXMATRIX mView, D3DXVECTOR3 vBBox[2])
{
    D3DXMATRIX mViewInv;
    D3DXMatrixInverse(&mViewInv, NULL, &mView);
    D3DXVECTOR3 vView, vCorner[2], vEye;
    D3DXVECTOR3 vTmp(0, 0, 1);
    D3DXVec3TransformNormal(&vView, &vTmp, &mViewInv);
    vTmp = D3DXVECTOR3(0, 0, 0);
    D3DXVec3TransformCoord(&vEye, &vTmp, &mViewInv);
    D3DXVec3Normalize(&vView, &vView);
    for (int ic = 0; ic < 3; ++ic)
    {
        vCorner[0][ic] = (vView[ic] < 0) ? vBBox[0][ic] : vBBox[1][ic];
        vCorner[1][ic] = (vView[ic] < 0) ? vBBox[1][ic] : vBBox[0][ic];
    }
    vTmp = vCorner[0] - vEye;
    float fFar = max(0.01f, 1.2f * D3DXVec3Dot(&vTmp, &vView));
    vTmp = vCorner[1] - vEye;
    float fNear = max(fFar / 100, D3DXVec3Dot(&vTmp, &vView));
    CModelViewerCamera::SetProjParams(fFOV, fAspect, fNear, fFar);
}
void NVUTCamera::SetProjParams(D3DXMATRIX mView, D3DXVECTOR3 vBBox[2])
{
    // compute projection matrix
    D3DXVECTOR3 BBox[2];
    BBox[0][0] = BBox[0][1] = BBox[0][2] =  1E38f;
    BBox[1][0] = BBox[1][1] = BBox[1][2] = -1E38f;
    for (int i = 0; i < 8; ++i)
    {
        D3DXVECTOR3 v, v1;
        v[0] = vBBox[(i & 1) ? 0 : 1][0];
        v[1] = vBBox[(i & 2) ? 0 : 1][1];
        v[2] = vBBox[(i & 4) ? 0 : 1][2];
        D3DXVec3TransformCoord(&v1, &v, &m_mView);
        for (int j = 0; j < 3; ++j)
        {
            BBox[0][j] = min(BBox[0][j], v1[j]);
            BBox[1][j] = max(BBox[1][j], v1[j]);
        }
    }
    // expand the box a bit
    for (int j = 0; j < 3; ++j)
    {
        BBox[0][j] -= (FLOAT)(abs(BBox[0][j]) * 1e-3);
        BBox[1][j] += (FLOAT)(abs(BBox[1][j]) * 1e-3);
    }
    D3DXMatrixPerspectiveLH(&this->m_mProj, (FLOAT)max(abs(BBox[0][0]), (FLOAT)abs(BBox[1][0])) * 2, (FLOAT)max(abs(BBox[0][1]), (FLOAT)abs(BBox[1][1])) * 2, (FLOAT)max(0.0001, BBox[0][2]), (FLOAT)max(0.0002, BBox[1][2]));
}
