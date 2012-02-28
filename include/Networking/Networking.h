#ifndef Networking_h
#define Networking_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifndef NETEXT
#define NETEXT DECLSPEC_DLLIMPORT
#endif

#include "Socket.h"
#include "http.h"
#include "Binder.h"

#endif // Networking_h
