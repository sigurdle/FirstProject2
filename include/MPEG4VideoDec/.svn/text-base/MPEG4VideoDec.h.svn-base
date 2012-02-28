#ifndef MPEG4VideoDec_h
#define MPEG4VideoDec_h

#ifdef __LERSTAD__
#import "LFC/LFC"
#else
#include "LFC/LFC.h"
#endif

#ifndef MPEG4VideoDecExt
#define MPEG4VideoDecExt DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace Mpeg4
{

MPEG4VideoDecExt int next_start_code(System::IO::CBitStream32* pBitStream);
MPEG4VideoDecExt int user_data(System::IO::CBitStream32* pBitStream, int start_code);

}	// Mpeg4
}

#include "VideoDec.h"

#endif
