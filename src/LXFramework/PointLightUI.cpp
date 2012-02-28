// PointLightUI.cpp : Implementation of CPointLightUI

#include "stdafx.h"
#include "LXFramework.h"
#include "PointLightUI.h"

/////////////////////////////////////////////////////////////////////////////
// CPointLightUI

#include <math.h>

#define DEFAULT_VEC                         {0.00, 0.00, 1.00}      // Default start vector
#define DEFAULT_DIFFUSE                     RGB( 100,  100, 100)      // Default diffuse color
#define DEFAULT_AMBIENT                     RGB( 20,  20,  20)      // Default ambient color
#define DEFAULT_LIGHT                       RGB(200, 200, 200)      // Default light color
#define DEFAULT_START_BACKGROUND_COLOR      RGB(  0,   0,   0)      // Default gradient background start color
#define DEFAULT_END_BACKGROUND_COLOR        RGB(140,   0, 120)      // Default gradient background end color
#define DEFAULT_SPEC_EXP                    25.0                    // Default specular intensity

COLORREF
	m_clrDiffuse,           // Ball diffusion color (self color)
	m_clrAmbient,           // Ambient (background) color
	m_clrLight,             // Color of light
	m_clrBackgroundStart,   // Background color gradient start
	m_clrBackgroundEnd;     // Background color gradient end

double m_dSpecularExponent;    // Specularity effect intensity

double m_dSensitivity = 20.0;

BOOL m_bFrontVector = FALSE;

// Calculate lightning effect for specific pixel on ball's surface
COLORREF CPointLightUI::CalcLight (gmVector3& dVec, double dx, double dy, double dz)
{
	m_clrDiffuse = DEFAULT_DIFFUSE;
	m_clrAmbient = DEFAULT_AMBIENT;
	m_clrLight = DEFAULT_LIGHT;
	
	m_dSpecularExponent = DEFAULT_SPEC_EXP;
	
	double NL = dx * dVec[0] + dy * dVec[1] + dz * dVec[2], 
		RV = 2.0 * NL,
		rx = dVec[0] - (dx * RV),
		ry = dVec[1] - (dy * RV),
		rz = dVec[2] - (dz * RV);
	
	if (NL < 0.0)   // Diffuse coefficient
		NL = 0.0;
	
	RV = max (0.0, -rz);
	RV = double(pow (RV, m_dSpecularExponent));
	
	int r = int (	double(GetRValue(m_clrDiffuse)) * NL +  // Diffuse
						double(GetRValue(m_clrLight)) * RV +    // Specular
						double(GetRValue(m_clrAmbient)));       // Ambient
		
	int g = int (	double(GetGValue(m_clrDiffuse)) * NL +  // Diffuse
						double(GetGValue(m_clrLight)) * RV +    // Specular
						double(GetGValue(m_clrAmbient)));       // Ambient    
		
	int b = int (  double(GetBValue(m_clrDiffuse)) * NL +  // Diffuse
						double(GetBValue(m_clrLight)) * RV +    // Specular
						double(GetBValue(m_clrAmbient)));       // Ambient
	
	r = min (255, r);   // Cutoff highlight
	g = min (255, g);
	b = min (255, b);

	return RGB(BYTE(r),BYTE(g),BYTE(b));
}

#define EPS                                 1.0e-6                  // Epsilon

#if 0
// Normalize a vector to unit size
BOOL CPointLightUI::Normalize ()
{
    double Norm = m_dVec[0] * m_dVec[0] + m_dVec[1] * m_dVec[1] + m_dVec[2] * m_dVec[2];

    if (Norm > EPS) {
        Norm = sqrt (Norm);
        m_dVec[0] /= Norm;
        m_dVec[1] /= Norm;
        m_dVec[2] /= Norm;
        return TRUE;
    } else {    // Reset to default vector
        double DefaultVec[3] = DEFAULT_VEC;
        for (int i=0; i<3; i++) 
            m_dVec[i] = DefaultVec[i];
        return FALSE;
    }
}
#endif

// Rotate our vector around the X and Y axis
void CPointLightUI::RotateByXandY (double XRot, double YRot)
{   // Angles are in radians
	
	if (XRot == 0.0 && YRot == 0.0)
		return;
	
//	double length = m_dVec.length();

	double cx = cos(XRot);
	double sx = sin(XRot);
	double cy = cos(YRot);
	double sy = sin(YRot);
	
	double dx = m_dVec[0] * cy + m_dVec[1] * sx * sy + m_dVec[2] * cx * sy;
	double dy = m_dVec[1] * cx - m_dVec[2] * sx;
	double dz = -m_dVec[0] * sy + m_dVec[1] * sx * cy + m_dVec[2] * cx * cy;
	
	if (!m_bFrontVector || dz >= 0.0)  // Vector is bounds free
	{
		m_dVec[0] = dx;// * length;
		m_dVec[1] = dy;// * length;
		m_dVec[2] = dz;// * length;
	//	Normalize ();
	}
	else    // Otherwise, do not allow Z to be negative (light shines from behind)
	{
		m_dVec[0] = dx;
		m_dVec[1] = dy;
		m_dVec[2] = 0.0;
#if 0
		Normalize();
#endif
	}
}

HRESULT CPointLightUI::OnDraw(ATL_DRAWINFO& di)
{
	HDC hDC = di.hdcDraw;

//	RECT& rc = *(RECT*)di.prcBounds;

	int m_iWidth = 60;
	int m_iHeight = 60;
	int m_iRadius = 30;
	int m_iXCenter = m_iWidth/2;
	int m_iYCenter = m_iHeight/2;
	int m_iSqrRadius = m_iRadius * m_iRadius;

	gmVector3 dVec = m_dVec;
	dVec.normalize();

	for (int x=0; x<m_iWidth; x++)  // Scan all columns
	{
		for (int y=0; y<m_iHeight; y++)   // Scan all rows
		{
			int xf = x-m_iXCenter;  // Find distance from center
			int yf = y-m_iYCenter;

			if (xf*xf + yf*yf <= m_iSqrRadius)    // Point on ball surface
			{
				double vx = double(xf) / double(m_iRadius);
				double vy = double(yf) / double(m_iRadius);
				double vz = sqrt (1.0 - vx*vx - vy*vy);     // Find ball's normal

				SetPixelV (hDC, x, y, CalcLight(dVec, vx,vy,vz));
			}
			else
			{
				SetPixelV (hDC, x, y, RGB(0,0,0));
			}
		}
	}

	/*
	char buf[256];
	sprintf(buf, "%.2f, %.2f, %.2f", m_dVec[0], m_dVec[1], m_dVec[2]);
	TextOut(hDC, m_iWidth, 0, buf, strlen(buf));
	*/

	return S_OK;
}

LRESULT CPointLightUI::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!m_dragging)
	{
		m_spInPlaceSite->SetCapture(TRUE);
		m_dragging = 1;

		m_iLastMouse = point;

		OnMouseMove(point);
	}

	return 0;
}

LRESULT CPointLightUI::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_spInPlaceSite->SetCapture(FALSE);
		m_dragging = 0;

		Fire_OnChangedLast(m_dVec[0], m_dVec[1], m_dVec[2]);
	}
	return 0;
}

void CPointLightUI::OnMouseMove(CPoint point)
{
	if (m_dragging)
	{
		RotateByXandY (
			-double(point.y - m_iLastMouse.y) / m_dSensitivity,
			double(point.x - m_iLastMouse.x) / m_dSensitivity);
		
		m_iLastMouse = point;

		m_spInPlaceSite->InvalidateRect(NULL, TRUE);

		Fire_OnChanged(m_dVec[0], m_dVec[1], m_dVec[2]);
	}
}

LRESULT CPointLightUI::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnMouseMove(point);

	return 0;
}

STDMETHODIMP CPointLightUI::SetXYZ(double x, double y, double z)
{
	m_dVec[0] = x;
	m_dVec[1] = y;
	m_dVec[2] = z;
//	Normalize();

	m_spInPlaceSite->InvalidateRect(NULL, TRUE);

	return S_OK;
}

STDMETHODIMP CPointLightUI::get_x(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dVec[0];
	return S_OK;
}

STDMETHODIMP CPointLightUI::get_y(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dVec[1];
	return S_OK;
}

STDMETHODIMP CPointLightUI::get_z(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dVec[2];
	return S_OK;
}
