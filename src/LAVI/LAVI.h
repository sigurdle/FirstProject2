#ifndef __LAVI_h__
#define __LAVI_h__

//#include "../LMPEG4/LMPEG4.h"	// TODO, have video in separate dll
//#include "../LMPEG4/VideoDec.h"

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/MPEG4VideoDec.typeinfo"
#else
#include "../MPEG4VideoDec/MPEG4VideoDec.h"
#endif

#include "vfw.h"
#include "LAVISplitter.h"

#endif
