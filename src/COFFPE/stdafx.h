#if !defined(AFX_STDAFX_H__EEA90BF5_0154_48A6_B246_2B1F23ECDB9D__INCLUDED_)
#define AFX_STDAFX_H__EEA90BF5_0154_48A6_B246_2B1F23ECDB9D__INCLUDED_

#include "../LFC/LFC.h"

/*
#include <string>
#include <list>
#include <vector>
#include <map>
*/

char fget8(FILE* fp);
short fget16(FILE* fp);
long fget32(FILE* fp);

/* Swap between intel and motorola */
#define ENDIANWORD(x)	((WORD)((((WORD)(x) & 0x00ff)<<8) |    (((WORD)(x) & 0xff00)>>8)))

#define ENDIANLONG(x)	((((DWORD)(x) & 0x000000ff)<<24) |   (((DWORD)(x) & 0x0000ff00)<<8) |     (((DWORD)(x) & 0x00ff0000)>>8) |     (((DWORD)(x) & 0xff000000)>>24))


//#define BigEndian16(x)	ENDIANWORD(x)
//#define BigEndian32(x)	ENDIANLONG(x)
//#define LE16(x) (x)
//#define LE32(x) (x)

#endif // !defined(AFX_STDAFX_H__EEA90BF5_0154_48A6_B246_2B1F23ECDB9D__INCLUDED_)
