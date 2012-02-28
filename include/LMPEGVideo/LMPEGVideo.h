#ifndef MPEGVideo_h
#define MPEGVideo_h

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LMedia.typeinfo"
#else
#include "LMedia/LMedia.h"
#endif

#ifndef MpegVideoExt
#define MpegVideoExt DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace MediaShow
{

// Forward declarations

class MpegVideoSequence;
class PictureDecoder;

}
}

#include "MPEG/MPEGBitStream.h"
#include "VideoSequence.h"
#include "Picture.h"
#include "VideoSequence.h"
#include "MPEGVideoDecoder.h"

#endif // MPEGVideo_h
