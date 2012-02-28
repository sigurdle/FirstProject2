#include "stdafx.h"
#include "LXUI2.h"

//#include "../include/windows_header.h"

#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
/*
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef int * LPINT;
typedef BYTE * LPBYTE;
*/
#include "Tablet.h"

namespace System
{
using namespace MSWindows;

namespace UI
{

#ifdef WINTAB
// WinTab

bool g_bCheckedForTablet = false;
bool g_bTabletInstalled = false;
MSWindows::HINSTANCE g_hWinTabLib = NULL;

WTINFO	_WTInfo;
WTOPEN	_WTOpen;
WTCLOSE	_WTClose;
WTENABLE	_WTEnable;
WTPACKET	_WTPacket;
WTQUEUESIZEGET _WTQueueSizeGet;
WTQUEUESIZESET _WTQueueSizeSet;

int g_nTabletMinPressure = 0;
int g_nTabletMaxPressure = 1;
bool t_bTiltSupport = true;	// TRUE if tablet provides tilt and direction information

bool IsTabletInstalled()
{
	struct	tagAXIS TpOri[3];	// The capabilities of tilt (required)
#if 0
	double	dblTpvar;				// A temp for converting fix to double (for example)
#endif

	bool bReturn = true;

//	if (!_WTInfo) return FALSE;
	// check if WinTab available.
/*
	if (_WTInfo(0, 0, NULL)) {
		TRACE("WinTab Services Not Available.");
		bReturn = FALSE;
	}
	*/
	if(bReturn)
	{
	// Get info about pressure
		AXIS	pressureAxis;
		BOOL bPressure = _WTInfo(WTI_DEVICES, DVC_NPRESSURE, &pressureAxis);
		if (bPressure)
		{
			g_nTabletMinPressure = pressureAxis.axMin;
			g_nTabletMaxPressure = pressureAxis.axMax;
			
			/*
			if (pressureAxis.axMin != 0)
			{
				TRACE("axMin != 0, notify author");
			}
			*/
		}
		
		// get info about tilt
		t_bTiltSupport = _WTInfo(WTI_DEVICES, DVC_ORIENTATION, &TpOri) ? true: false;
		if (t_bTiltSupport)
		{
			//JCB
		//	m_strTiltWords = "Tablet supports tilt";
			
			//used for example
#if 0
			// does the tablet support azimuth and altitude
			if (TpOri[0].axResolution && TpOri[1].axResolution) {
				
				// convert azimuth resulution to double
				dblTpvar = FIX_DOUBLE(TpOri[0].axResolution);
				// convert from resolution to radians
				t_dblAziFactor = dblTpvar/(2*pi);  
				
				// convert altitude resolution to double
				dblTpvar = FIX_DOUBLE(TpOri[1].axResolution);
				// scale to arbitrary value to get decent line length
				t_dblAltFactor = dblTpvar/1000; 
				// adjust for maximum value at vertical
				t_dblAltAdjust = (double)TpOri[1].axMax/t_dblAltFactor;
			}
#endif
			//end of used for example
		}
		else
		{  // no so don't do tilt stuff
			t_bTiltSupport = false;
		//	m_strTiltWords = "Tablet does NOT supports tilt!";
		}	//end tilt support
	}	//end does tablet exists
	
	return bReturn;
}

void SetupWinTab()
{
	if (!g_bCheckedForTablet)
	{
		g_bCheckedForTablet = true;

		HINSTANCE hLib = MSWindows::LoadLibraryA("wintab32.dll");
		if (hLib)
		{
			try
			{
				if (! (_WTInfo = (WTINFO)MSWindows::GetProcAddress(hLib, ("WTInfoA")))) throw "WTInfoA";
				if (! (_WTOpen = (WTOPEN)MSWindows::GetProcAddress(hLib, ("WTOpenA")))) throw "WTOpenA";
				if (! (_WTClose = (WTCLOSE)MSWindows::GetProcAddress(hLib, ("WTClose")))) throw "WTClose";
				if (! (_WTEnable = (WTENABLE)MSWindows::GetProcAddress(hLib, ("WTEnable")))) throw "WTEnable";
				if (! (_WTPacket = (WTPACKET)MSWindows::GetProcAddress(hLib, ("WTPacket")))) throw "WTPacket";
				if (! (_WTQueueSizeGet = (WTQUEUESIZEGET)MSWindows::GetProcAddress(hLib, ("WTQueueSizeGet")))) throw "WTQueueSizeGet";
				if (! (_WTQueueSizeSet = (WTQUEUESIZESET)MSWindows::GetProcAddress(hLib, ("WTQueueSizeSet")))) throw "WTQueueSizeSet";
			}
			catch(const char* procname)
			{
				TRACE("WinTab proc '%s' not found\n", procname);

			// It's all or nothing
				_WTInfo = NULL;
				_WTOpen = NULL;
				_WTClose = NULL;
				_WTEnable = NULL;
				_WTPacket = NULL;
				_WTQueueSizeGet = NULL;
				_WTQueueSizeSet = NULL;

				::FreeLibrary(hLib);
				return;
			}

			g_hWinTabLib = hLib;

			if (IsTabletInstalled())
			{
				g_bTabletInstalled = true;

				TRACE("Drawing tablet successfully found\n");
			}
		}
		else
		{
			TRACE("No drawing tablet found\n");
		//	AfxMessageBox("No tablet found");
		}
	}
}

StringA* GetTabletName()
{
	char	chrWName[50] = {0};			// String to hold window name
	_WTInfo(WTI_DEVICES, DVC_NAME, chrWName);
	return new StringA(string_copy(chrWName));
}

#endif // WINTAB

}	// UI
}
