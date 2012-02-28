#ifndef Tablet_h
#define Tablet_h

//namespace System
//{
//namespace MSWindows
//{
#include "WinTab/include/wintab.h"

extern "C"
{
typedef UINT (API *WTINFOA)(UINT, UINT, LPVOID);
typedef UINT (API *WTINFOW)(UINT, UINT, LPVOID);

typedef HCTX (API *WTOPENA)(HWND, LPLOGCONTEXTA, BOOL);
typedef HCTX (API *WTOPENW)(HWND, LPLOGCONTEXTW, BOOL);

typedef BOOL (API *WTCLOSE)(HCTX);
typedef BOOL (API *WTENABLE)(HCTX, BOOL);
typedef BOOL (API *WTOVERLAP)(HCTX, BOOL);
typedef BOOL (API *WTPACKET)(HCTX, UINT, LPVOID);
typedef int (API *WTQUEUESIZEGET)(HCTX);
typedef BOOL (API *WTQUEUESIZESET)(HCTX, int);
}

//}
//}

namespace System
{
namespace Gui
{

extern WTINFOW _WTInfoW;
extern WTOPENW _WTOpenW;
extern WTCLOSE _WTClose;
extern WTENABLE _WTEnable;
extern WTPACKET _WTPacket;
extern WTOVERLAP _WTOverlap;
extern WTQUEUESIZEGET _WTQueueSizeGet;
extern WTQUEUESIZESET _WTQueueSizeSet;

void SetupWinTab();
}
}

#endif // Tablet_h
