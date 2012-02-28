#include "stdafx.h"
#include "GUI2.h"

//#include "../include/windows_header.h"

//#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
/*
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef int * LPINT;
typedef BYTE * LPBYTE;
*/
#include "Tablet.h"

namespace System
{
//using namespace MSWindows;

namespace Gui
{

//#ifdef WINTAB
// WinTab

bool g_bCheckedForTablet = false;
bool g_bTabletInstalled = false;
HINSTANCE g_hWinTabLib = nullptr;

WTINFOA	_WTInfoA;
WTINFOW	_WTInfoW;

WTOPENA	_WTOpenA;
WTOPENW	_WTOpenW;

WTCLOSE	_WTClose;
WTENABLE	_WTEnable;
WTPACKET	_WTPacket;
WTOVERLAP	_WTOverlap;
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
		BOOL bPressure = _WTInfoW(WTI_DEVICES, DVC_NPRESSURE, &pressureAxis);
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
		t_bTiltSupport = _WTInfoW(WTI_DEVICES, DVC_ORIENTATION, &TpOri) ? true: false;
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

		HINSTANCE hLib = LoadLibraryW(L"wintab32.dll");
		if (hLib)
		{
			try
			{
				_WTInfoA = (WTINFOA)GetProcAddress(hLib, "WTInfoA");
				_WTOpenA = (WTOPENA)GetProcAddress(hLib, "WTOpenA");

				if (! (_WTInfoW = (WTINFOW)GetProcAddress(hLib, "WTInfoW"))) throw "WTInfoW";
				if (! (_WTOpenW = (WTOPENW)GetProcAddress(hLib, "WTOpenW"))) throw "WTOpenW";

				if (! (_WTClose = (WTCLOSE)GetProcAddress(hLib, "WTClose"))) throw "WTClose";
				if (! (_WTEnable = (WTENABLE)GetProcAddress(hLib, "WTEnable"))) throw "WTEnable";
				if (! (_WTPacket = (WTPACKET)GetProcAddress(hLib, "WTPacket"))) throw "WTPacket";
				if (! (_WTOverlap = (WTOVERLAP)GetProcAddress(hLib, "WTOverlap"))) throw "WTOverlap";
				if (! (_WTQueueSizeGet = (WTQUEUESIZEGET)GetProcAddress(hLib, "WTQueueSizeGet"))) throw "WTQueueSizeGet";
				if (! (_WTQueueSizeSet = (WTQUEUESIZESET)GetProcAddress(hLib, "WTQueueSizeSet"))) throw "WTQueueSizeSet";

				g_hWinTabLib = hLib;

				if (IsTabletInstalled())
				{
					g_bTabletInstalled = true;

					DebugTrace("Drawing tablet successfully found" << endl);
				}
			}
			catch(const char* procname)
			{
				DebugTraceLn("WinTab proc '" << procname << "' not found");

			// It's all or nothing
				_WTInfoW = nullptr;
				_WTOpenW = nullptr;
				_WTInfoA = nullptr;
				_WTOpenA = nullptr;
				_WTClose = nullptr;
				_WTEnable = nullptr;
				_WTPacket = nullptr;
				_WTQueueSizeGet = nullptr;
				_WTQueueSizeSet = nullptr;

				::FreeLibrary(hLib);
			}
		}
		else
		{
			DebugTraceLn("No drawing tablet found");
		}
	}
}

String GetTabletName()
{
	WCHAR chrWName[50] = {0};			// String to hold window name
	_WTInfoW(WTI_DEVICES, DVC_NAME, chrWName);
	return String(string_copy(chrWName));
}

//#endif // WINTAB

}	// Gui
}
