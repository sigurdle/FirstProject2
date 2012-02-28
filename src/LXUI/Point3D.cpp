#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{
namespace Media3D
{

double Point3D::get_X() const
{
	return X;
}

void Point3D::set_X(double x)
{
	X = x;
}

double Point3D::get_Y() const
{
	return Y;
}

void Point3D::set_Y(double y)
{
	Y = y;
}

double Point3D::get_Z() const
{
	return Z;
}

void Point3D::set_Z(double z)
{
	Z = z;
}

}	// Media3D
}	// UI
}
