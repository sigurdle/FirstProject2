#ifndef __Quaternion_h__
#define __Quaternion_h__

#ifndef X3DEXT
#define X3DEXT DECLSPEC_DLLIMPORT
#endif

namespace System
{

class Quat4d;

class X3DEXT AxisAngle
{
public:
	// The initial default value of an uninitialized SFRotation field is (0 0 1 0)
	CTOR AxisAngle() : m_axis(0, 0, 1), m_angle(0)
	{
	}

	CTOR AxisAngle(float x, float y, float z, float angle) : m_axis(x, y, z), m_angle(angle)
	{
	}

	CTOR AxisAngle(const gm::vector3f& axis, float angle) : m_axis(axis), m_angle(angle)
	{
	}

	float angleDegrees() const
	{
		return (float)gmDegrees(m_angle);
	}

	AxisAngle& operator = (const AxisAngle& other)
	{
		m_axis = other.m_axis;
		m_angle = other.m_angle;

		return *this;
	}

	Quat4d ToQuat() const;

/** constructor to create sfrotation from euler angles.
   * @param heading rotation about z axis
   * @param attitude rotation about y axis
   * @param bank rotation about x axis
   */
#if 0
   Rotation(double heading,double attitude,double bank)
	{
		double c1 = cos(heading/2);
		double s1 = sin(heading/2);
		double c2 = cos(attitude/2);
		double s2 = sin(attitude/2);
		double c3 = cos(bank/2);
		double s3 = sin(bank/2);
		double c1c2 = c1*c2;
		double s1s2 = s1*s2;
		/*
		angle =c1c2*c3 + s1s2*s3;
		x =c1c2*s3 - s1s2*c3;
		y =c1*s2*c3 + s1*c2*s3;
		z =s1*c2*c3 - c1*s2*s3;
		coding=CODING_QUATERNION;
		*/
   }
#endif

	gm::vector3f m_axis;
	float m_angle;
};

class X3DEXT Quat4d
{
public:
	CTOR Quat4d()
	{
		// TODO, initialize
	}

	CTOR Quat4d(double _x, double _y, double _z, double _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	AxisAngle ToAxisAngle() const;

	void Combine(double heading,double attitude,double bank);

	double x;
	double y;
	double z;
	double w;
};

Quat4d MatrixToQuaternion(const gm::matrix3f& m);
Quat4d EulerToQuaternion(double heading, double attitude, double bank);
void QuaternionToEuler(const Quat4d& q1, double* heading, double* attitude, double* bank);

void slerp(double alpha, const Quat4d *a, const Quat4d *b, Quat4d *q, int spin);

}

#endif // __Quaternion_h__
