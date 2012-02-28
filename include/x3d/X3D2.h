#ifndef X3DEXT
#define X3DEXT DECLSPEC_DLLEXPORT
#endif

#include "x3d_Core.h"

//#include <D3D10_1.h>
//#include <D3DX10Async.h>

namespace System
{
namespace x3d
{

struct VERTEX_XYZ_NORMAL
{
	Vec3f position;
	Vec3f normal;
};

}	// x3d
}	// System
