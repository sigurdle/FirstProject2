#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

LDraw::PointD Transform::TransformPoint(LDraw::PointD point)
{
	return get_Value()->Transform(point);
}

void Transform::TransformPoints(LDraw::PointD* dstpoints, const LDraw::PointD* srcpoints, unsigned int count)
{
	__release<LDraw::Matrix3f> matrix = get_Value();

	for (unsigned int i = 0; i < count; i++)
	{
		dstpoints[i] = matrix->Transform(srcpoints[i]);
	}
}

}	// UI
}
