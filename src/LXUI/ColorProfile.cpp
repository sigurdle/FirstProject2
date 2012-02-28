#include "stdafx.h"
#include "LXUI2.h"

#include "ColorProfile.h"

using namespace System;

// Calculates fixed poit from floating point.
#define __FXPTMANTISSA(d, f)  ( (DWORD)d << f )
#define __FXPTFRACTION(d, f)  ( (DWORD)ldexp((d - (DWORD)d), f) )
#define __FXPT32(d, f)      ( __FXPTMANTISSA(d, f) | __FXPTFRACTION(d, f) )

#define __FXPT2DOT30(d)   __FXPT32(d, 30)
#define __FXPT16DOT16(d)  __FXPT32(d, 16)

#if 0//_WINDOWS
UIEXT HPROFILE Get_sRGBProfile()
{
	static HPROFILE g_sRGBProfile = NULL;

	if (g_sRGBProfile == NULL)
	{
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
	}

	return g_sRGBProfile;
}
#endif

HTRANSFORM CColorProfile::GetProfile2sRGB()
{
#if 0
	if (m_hTransform == NULL)
	{
		HPROFILE sRGBProfile = Get_sRGBProfile();

		m_hTransform = ::CreateColorTransform(&m_lcs, sRGBProfile, NULL, 0);
	}
#endif

	return m_hTransform;
}

void CColorProfile::LoadURL(StringA* absurl)
{
#if 0

#if _WINDOWS
	USES_CONVERSION;

	m_lcs.lcsSignature = LCS_SIGNATURE;
	m_lcs.lcsVersion = 0x400;
	m_lcs.lcsSize = sizeof(m_lcs);
	m_lcs.lcsCSType = LCS_CALIBRATED_RGB;
	m_lcs.lcsEndpoints.ciexyzRed.ciexyzX = __FXPT2DOT30(1);//(.64);
	m_lcs.lcsEndpoints.ciexyzRed.ciexyzY = __FXPT2DOT30(0);//(.33);
	m_lcs.lcsEndpoints.ciexyzRed.ciexyzZ = __FXPT2DOT30(0);//(.03);
	m_lcs.lcsEndpoints.ciexyzGreen.ciexyzX = __FXPT2DOT30(0);//(.3);
	m_lcs.lcsEndpoints.ciexyzGreen.ciexyzY = __FXPT2DOT30(1);//(.6);
	m_lcs.lcsEndpoints.ciexyzGreen.ciexyzZ = __FXPT2DOT30(0);//(.1);
	m_lcs.lcsEndpoints.ciexyzBlue.ciexyzX   =   __FXPT2DOT30(0);//(  .15);
	m_lcs.lcsEndpoints.ciexyzBlue.ciexyzY = __FXPT2DOT30(0);//(.06);
	m_lcs.lcsEndpoints.ciexyzBlue.ciexyzZ = __FXPT2DOT30(1);//(.79);
	m_lcs.lcsGammaRed = __FXPT16DOT16(1);//(0.45);
	m_lcs.lcsGammaGreen = __FXPT16DOT16(1);//(0.45);
	m_lcs.lcsGammaBlue = __FXPT16DOT16(1);//(0.45);

	ASSERT(0);
#if 0
	HRESULT hr = ::URLDownloadToCacheFile(NULL, W2A(absurl), m_lcs.lcsFilename, MAX_PATH, 0, NULL);
	if (SUCCEEDED(hr))
	{
		/*
		PROFILE profile;
		profile.dwType = PROFILE_FILENAME;
		profile.pProfileData = filename;
		profile.cbDataSize = (_tcslen(filename)+1)*sizeof(TCHAR);

		m_hProfile = ::OpenColorProfile(&profile, PROFILE_READ, FILE_SHARE_READ, OPEN_EXISTING);
		*/
	}
#endif
#endif
#endif
}
