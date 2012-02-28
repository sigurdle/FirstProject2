#ifndef __MPEG4_h__
#define __MPEG4_h__

/*
#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LMedia.typeinfo"
#else
#include "LMedia/LMedia.h"
#endif
*/

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/MPEG4VideoDec.typeinfo"
#else
#include "MPEG4VideoDec/MPEG4VideoDec.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/X3D.typeinfo"
#else
#include "X3D/X3D.h"
#endif

#ifndef MPEG4EXT
#define MPEG4EXT DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace MediaShow
{

class IODDecoder
{
public:
};

}	// Media
}

namespace System
{
namespace Mpeg4
{

class Track;
class MP4VSampleDescription;
//class MP4VConfig;
class BaseDescriptor;
//class VideoDec;
class BIFSDec;
class MPEG4Movie;
class Atom;

}
}

#include "MP4File.h"
#include "MPEG4Filter.h"
#include "MP4Track.h"
//#include "VideoDec.h"
#include "SampleDescription.h"
#include "BIFS.h"
#include "BIFSDec.h"

#include "VideoDecoder.h"
#include "BIFSDecoder.h"

#endif // __MPEG4_h__
