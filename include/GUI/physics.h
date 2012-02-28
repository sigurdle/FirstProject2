
#if 1//defined(_M_X64)

//#pragma warning(push)
//#pragma warning(disable : 4635)

#undef new
#include "PxPhysicsAPI.h"
#include <PxRigidBodyExt.h>
#define new _new

//#pragma warning(pop)

#endif

/*
namespace System
{

namespace x3d
{

#ifndef __LERSTAD__

inline physx::PxVec3 _NxVec3(Vec3f v)
{
	return physx::PxVec3(v[0], v[1], v[2]);
}

inline physx::PxQuat _NxQuat(Rotation v)
{
	return physx::PxQuat(v.angleDegrees(), _NxVec3(v.m_axis));
}

inline Vec3f _Vec3f(physx::PxVec3 v)
{
	return Vec3f(v.x, v.y, v.z);
}

#endif

}

}
*/
