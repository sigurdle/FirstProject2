#include "stdafx.h"
#include "HTML2.h"

#if WIN32

#include "icml.h"

#pragma comment(lib, "shlwapi.lib")

//#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "Mscms.lib")

#endif

namespace System
{
namespace gm
{
GfxExt gm::vector2d intersection(const gm::vector2d& A, const vector2d& B, const vector2d& C, const vector2d& D);
GfxExt void GetTransformRectBoundingBox(const matrix3d& mat, const gm::RectD& bounds, gm::RectD* pVal);
GfxExt void GetTransformRectBoundingBox(const matrix3d& mat, const gm::RectF& bounds, gm::RectD* pVal);
}

//namespace Math
//{

HTMLEXT double GetLineAngle(double x1, double y1, double x2, double y2)
{
	double dx = x2-x1;
	double dy = y2-y1;

	double distance2 = sqrt(dx*dx + dy*dy);

	if (distance2 == 0.0) distance2 = 0.00001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	return angle;
}

//}	// Math

}

/*
{
	ASSERT(pVal != NULL);

	LDraw::PointD pts[4] =
	{
		LDraw::PointD(bounds.X, bounds.Y),
		LDraw::PointD(bounds.X+bounds.Width, bounds.Y),
		LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height),
		LDraw::PointD(bounds.X, bounds.Y+bounds.Height),
	};

	double minx = 999999999;
	double miny = 999999999;
	double maxx = -999999999;
	double maxy = -999999999;

	for (int i = 0; i < 4; i++)
	{
		LDraw::PointD xpt = mat.transform(pts[i]);

		if (xpt.X < minx) minx = xpt.X;
		if (xpt.Y < miny) miny = xpt.Y;
		if (xpt.X > maxx) maxx = xpt.X;
		if (xpt.Y > maxy) maxy = xpt.Y;
	}

	pVal->X = minx;
	pVal->Y = miny;
	pVal->Width = maxx-minx;
	pVal->Height = maxy-miny;
}

HTMLEXT void GetTransformRectBoundingBox(const gmMatrix3& mat, const LDraw::RectF& bounds, LDraw::RectD* pVal)
{
	ASSERT(pVal != NULL);

	LDraw::PointD pts[4] =
	{
		LDraw::PointD(bounds.X, bounds.Y),
		LDraw::PointD(bounds.X+bounds.Width, bounds.Y),
		LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height),
		LDraw::PointD(bounds.X, bounds.Y+bounds.Height),
	};

	double minx = 999999999;
	double miny = 999999999;
	double maxx = -999999999;
	double maxy = -999999999;

	for (int i = 0; i < 4; i++)
	{
		LDraw::PointD xpt = mat.transform(pts[i]);

		if (xpt.X < minx) minx = xpt.X;
		if (xpt.Y < miny) miny = xpt.Y;
		if (xpt.X > maxx) maxx = xpt.X;
		if (xpt.Y > maxy) maxy = xpt.Y;
	}

	pVal->X = minx;
	pVal->Y = miny;
	pVal->Width = maxx-minx;
	pVal->Height = maxy-miny;
}
*/

/*
HTMLEXT void CalculateScale(const gmMatrix3& matrix, double* scaleX, double* scaleY)
{
	LDraw::PointD ptxy;
	ptxy.X = 0;
	ptxy.Y = 0;

	LDraw::PointD ptx;
	ptx.X = 1;
	ptx.Y = 0;

	LDraw::PointD pty;
	pty.X = 0;
	pty.Y = 1;

	ptxy = matrix.transform(ptxy);
	ptx = matrix.transform(ptx);
	pty = matrix.transform(pty);

	double dx, dy;

	dx = ptx.X-ptxy.X;
	dy = ptx.Y-ptxy.Y;
	*scaleX = sqrt(dx*dx + dy*dy);

	dx = pty.X-ptxy.X;
	dy = pty.Y-ptxy.Y;
	*scaleY = sqrt(dx*dx + dy*dy);
}
*/

namespace System
{
HTMLEXT uint8 linear_to_sRGB[256];
HTMLEXT uint8 sRGB_to_linear[256];

void build_sRGBLuts()
{
	int i;

				/*
Any values greater than 1.0 or less than 0.0 are clipped to 1.0 and 0.0 respectively.

The linear RGB values are transformed to nonlinear sR'G'B' values as follows: 

If  R,G, B £ 0.0031308

R’sRGB = 12.92 ´ R

G’sRGB = 12.92 ´ G

B’sRGB = 12.92 ´ B

 

else if  R,G, B > 0.0031308

R’sRGB = 1.055 ´ R(1.0/2.4) – 0.055

G’sRGB = 1.055 ´ G(1.0/2.4) – 0.055

B’sRGB = 1.055 ´ B(1.0/2.4) – 0.055

The nonlinear sR’G’B’ values are then converted into 8 bit integers by:

R8bit = round(255.0 ´ R’sRGB)

G8bit = round(255.0 ´ G’sRGB)

B8bit = round(255.0 ´ B’sRGB)

*/
	for (i = 0; i < 256; i++)
	{
		double v = i/255.0;
		double sv;

		if (v <= 0.0031308)
			sv = 12.92 * v;
		else
			sv = 1.055 * pow(v, (1.0/2.4)) - 0.055;

		linear_to_sRGB[i] = (uint8)(sv*255.0+0.5);
	}

/*
The nonlinear sR'G'B' values are transformed to linear R,G, B values by: 

If  R’sRGB,G’sRGB, B’sRGB £ 0.04045

R =  R’sRGB ¤ 12.92

G =  G’sRGB ¤ 12.92

B =  B’sRGB ¤ 12.92

 

else if  R’sRGB,G’sRGB, B’sRGB > 0.04045

R = ((R’sRGB + 0.055) / 1.055)2.4

G = ((G’sRGB + 0.055) / 1.055)2.4

B = ((B’sRGB + 0.055) / 1.055)2.4

*/

	for (i = 0; i < 256; i++)
	{
		double sv = i/255.0;
		double v;

		if (sv <= 0.04045)
			v = sv / 12.92;
		else
			v = pow((sv + 0.055) / 1.055, 2.4);

		sRGB_to_linear[i] = (uint8)(v*255.0+0.5);
	}
}

/*
{
	gmVector2 P;

	double r = ((A[1]-C[1])*(D[0]-C[0])-(A[0]-C[0])*(D[1]-C[1])) /
					((B[0]-A[0])*(D[1]-C[1])-(B[1]-A[1])*(D[0]-C[0]));

	P[0] = A[0]+r*(B[0]-A[0]);
	P[1] = A[1]+r*(B[1]-A[1]);

	return P;
}*/

typedef void* HPROFILE;

HTMLEXT HPROFILE Get_sRGBProfile()
{
	static HPROFILE g_sRGBProfile = NULL;

	if (g_sRGBProfile == NULL)
	{
		ASSERT(0);
#if 0

		TCHAR colorDir[512];
		DWORD sizeOfColorDir = sizeof(colorDir);
		GetColorDirectory(NULL, colorDir, &sizeOfColorDir);

		TCHAR filename[512];
		_makepath(filename, NULL, colorDir, "sRGB Color Space Profile.icm", NULL);

		PROFILE profile;
		profile.dwType = PROFILE_FILENAME;
		profile.pProfileData = filename;
		profile.cbDataSize = strlen(filename)+1;

		g_sRGBProfile = ::OpenColorProfile(&profile, PROFILE_READ, FILE_SHARE_READ, OPEN_EXISTING);

		BOOL bValid;
		IsColorProfileValid(g_sRGBProfile, &bValid);
		ASSERT(bValid);
#endif
	}

	return g_sRGBProfile;
}
}

namespace System
{
namespace Web
{

HTMLEXT void CalculateScaleXY(const gm::matrix3d& matrix, double* scaleX, double* scaleY)
{
	// TODO, just transform 1,1 ??

	gm::PointD ptxy;
	ptxy.X = 0;
	ptxy.Y = 0;

	gm::PointD ptx;
	ptx.X = 1;
	ptx.Y = 0;

	gm::PointD pty;
	pty.X = 0;
	pty.Y = 1;

	ptxy = matrix.transform(ptxy);
	ptx = matrix.transform(ptx);
	pty = matrix.transform(pty);

	double dx, dy;

	// TODO, no need to sqrt ?

	dx = ptx.X-ptxy.X;
	dy = ptx.Y-ptxy.Y;
	*scaleX = sqrt(dx*dx + dy*dy);

	dx = pty.X-ptxy.X;
	dy = pty.Y-ptxy.Y;
	*scaleY = sqrt(dx*dx + dy*dy);
}

HTMLEXT void CalculateScaleXY(const gm::Matrix3d* matrix, double* scaleX, double* scaleY)
{
	CalculateScaleXY(matrix->m_matrix, scaleX, scaleY);
}

CPreferences::CPreferences()
{
	m_bLoaded = false;

	m_systemLanguage = WSTR("en");
	m_systemAudioDesc = false;
	m_systemCaptions = false;
	m_systemBitrate = 64000;
	m_systemOverdubOrSubtitle = 1;	// subtitle
	m_bKnownOS = true;
	m_bKnownCPU = true;
}

CPreferences::~CPreferences()
{
}

ErrorCode CPreferences::ForceReload()
{
	m_bLoaded = false;
	return LoadIfNotLoaded();
}

ErrorCode CPreferences::LoadIfNotLoaded()
{
	ASSERT(0);
#if 0
	if (!m_bLoaded)
	{
		m_bLoaded = TRUE;

		CRegKey key;
		if (key.Open(HKEY_CURRENT_USER, "Software\\LXFramework") == ERROR_SUCCESS)
		{
			CRegKey k;
			if (k.Open(key, "Viewer") == ERROR_SUCCESS)
			{
				DWORD dwCount;

				dwCount = 256;
				k.QueryValue(m_systemLanguage.GetBuffer(dwCount), "systemLanguage", &dwCount);
				m_systemLanguage.ReleaseBuffer();

				k.QueryValue(m_systemBitrate, "systemBitrate");

				k.QueryValue(m_systemCaptions, "systemCaptions");
				k.QueryValue(m_systemAudioDesc, "systemAudioDesc");
				k.QueryValue(m_systemOverdubOrSubtitle, "systemOverdubOrSubtitle");

				return S_OK;
			}
		}

		return S_FALSE;
	}
#endif
	return Success;
}

ErrorCode CPreferences::Save()
{
	ASSERT(0);
#if 0
	CRegKey key;
	if (key.Open(HKEY_CURRENT_USER, "Software\\LXFramework") == ERROR_SUCCESS)
	{
		CRegKey k;
		if (k.Create(key, "Viewer") == ERROR_SUCCESS)
		{
			k.SetValue(ConvertS2A(m_systemLanguage).c_str(), "systemLanguage");
			k.SetValue(m_systemBitrate, "systemBitrate");
			k.SetValue(m_systemCaptions, "systemCaptions");
			k.SetValue(m_systemAudioDesc, "systemAudioDesc");
			k.SetValue(m_systemOverdubOrSubtitle, "systemOverdubOrSubtitle");

			return S_OK;
		}
	}
#endif

	return Error_Failed;
}

}	// Web

}	// System
