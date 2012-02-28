#ifndef Tiff_h
#define Tiff_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#include "Imaging/DecoderInterface.h"

#ifndef TiffExt
#define TiffExt DECLSPEC_DLLEXPORT
#endif

namespace System
{
namespace Imaging
{
class TIFFFile;
class TIFFImage;
}
}

#include "TIFFFile.h"
#include "TIFFImage.h"

#endif	// Tiff_h
