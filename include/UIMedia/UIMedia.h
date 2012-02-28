#ifndef UIMedia_h
#define UIMedia_h

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LXUI.typeinfo"
#else
#include "../LXUI/LXUI.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LMedia.typeinfo"
#else
#include "../LMedia/LMedia.h"
#endif

#ifndef UIMediaExt
#define UIMediaExt DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace UI
{

class MediaElement;
class MediaPlayer;

}
}

#include "MediaElement.h"
#include "MediaPlayer.h"

#endif // UIMedia_h
