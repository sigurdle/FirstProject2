#include "StdAfx.h"
#include "X3D2.h"
#include "Quaternion.h"

namespace System
{

AxisAngle Quat4d::ToAxisAngle() const
{
	if (w > 1)
	{
	//	w = 1;
	//	ASSERT(0);
	}

	double s = sqrt(1-w*w);
	if (fabs(s) < 0.00001) s=1;

	return AxisAngle(
		x / s,
		y / s,
		z / s,
		2 * acos(w));
}

Quat4d AxisAngle::ToQuat() const
{
	double s = sin(m_angle/2);
	return Quat4d(
		m_axis[0] * s,
		m_axis[1] * s,
		m_axis[2] * s,
		cos(m_angle/2));
}

Quat4d EulerToQuaternion(double heading, double attitude, double bank)
{
	double c1 = cos(heading/2);
	double s1 = sin(heading/2);
	double c2 = cos(attitude/2);
	double s2 = sin(attitude/2);
	double c3 = cos(bank/2);
	double s3 = sin(bank/2);
	double c1c2 = c1*c2;
	double s1s2 = s1*s2;

	return Quat4d(
		c1c2*s3 - s1s2*c3,
		c1*s2*c3 + s1*c2*s3,
		s1*c2*c3 - c1*s2*s3,
		c1c2*c3 + s1s2*s3);
}

void QuaternionToEuler(const Quat4d& q1, double* heading, double* attitude, double* bank)
{
	double sqw = q1.w*q1.w;
	double sqx = q1.x*q1.x;
	double sqy = q1.y*q1.y;
	double sqz = q1.z*q1.z;
	*heading = atan2(2.0 * (q1.x*q1.y + q1.z*q1.w),(sqx - sqy - sqz + sqw));
	*bank = atan2(2.0 * (q1.y*q1.z + q1.x*q1.w),(-sqx - sqy + sqz + sqw));
	*attitude = asin(-2.0 * (q1.x*q1.z - q1.y*q1.w));
}

/** combine a rotation expressed as euler angle with current rotation.
   * first convert both values to quaternions then combine and convert back to
   * axis angle. Theory about these conversions shown here:
   * http://www.euclideanspace.com/maths/geometry/rotations/conversions/index.htm
   * @param heading angle about x axis
   * @param attitude angle about y axis
   * @param bank angle about z axis
   * */
void Quat4d::Combine(/*float& x, float& y, float& z, float& angle,*/ double heading, double attitude, double bank)
{
	// first calculate quaternion qb from heading, attitude and bank
	/*
	double c1 = cos(heading/2);
	double s1 = sin(heading/2);
	double c2 = cos(attitude/2);
	double s2 = sin(attitude/2);
	double c3 = cos(bank/2);
	double s3 = sin(bank/2);
	double c1c2 = c1*c2;
	double s1s2 = s1*s2;
	double qbw =c1c2*c3 + s1s2*s3;
	double qbx =c1c2*s3 - s1s2*c3;
	double qby =c1*s2*c3 + s1*c2*s3;
	double qbz =s1*c2*c3 - c1*s2*s3;
	*/
	Quat4d qb;
	/*
	float qbw;
	float qbx;
	float qby;
	float qbz;
	*/
	qb = EulerToQuaternion(heading, attitude, bank);//, &qbx, &qby, &qbz, &qbw);

	// then convert axis-angle to quaternion if required
	//toQuaternion();
	float qax = x;
	float qay = y;
	float qaz = z;
	float qaw = w;
	// now multiply the quaternions
	w = qaw*qb.w - qax*qb.x - qay*qb.y - qaz*qb.z ;
	x = qax*qb.w + qaw*qb.x + qay*qb.z - qaz*qb.y;
	y = qaw*qb.y - qax*qb.z + qay*qb.w + qaz*qb.x;
	z = qaw*qb.z + qax*qb.y - qay*qb.x + qaz*qb.w;
}

typedef Quat4d	Quaternion;		/* quaternion type */
//	double w, x, y, z;
//} Quaternion;

#define EPSILON 1.0E-6 			/* a tiny number */

void slerp(double alpha, const Quaternion *a, const Quaternion *b, Quaternion *q, int spin)
#if 0
	 alpha;			/* interpolation parameter (0 to 1) */
	Quaternion *a, *b;		/* start and end unit quaternions */
	Quaternion *q;			/* output interpolated quaternion */
	int spin;			/* number of extra spin rotations */
#endif
{
	double beta;			/* complementary interp parameter */
	double theta;			/* angle between A and B */
	double sin_t, cos_t;		/* sine, cosine of theta */
	double phi;			/* theta plus spins */
	bool bflip;			/* use negation of B? */

	/* cosine theta = dot product of A and B */
	cos_t = a->x*b->x + a->y*b->y + a->z*b->z + a->w*b->w;

	/* if B is on opposite hemisphere from A, use -B instead */
 	if (cos_t < 0.0)
	{
		cos_t = -cos_t;
		bflip = true;
	}
	else
	{
		bflip = false;
	}

	/* if B is (within precision limits) the same as A,
	 * just linear interpolate between A and B.
	 * Can't do spins, since we don't know what direction to spin.
	 */
	if (1.0 - cos_t < EPSILON) {
		beta = 1.0 - alpha;
 	} else {				/* normal case */
 		theta = acos(cos_t);
 		phi = theta + spin * M_PI;
 		sin_t = sin(theta);
 		beta = sin(theta - alpha*phi) / sin_t;
 		alpha = sin(alpha*phi) / sin_t;
 	}

	if (bflip)
		alpha = -alpha;

	/* interpolate */
 	q->x = beta*a->x + alpha*b->x;
 	q->y = beta*a->y + alpha*b->y;
 	q->z = beta*a->z + alpha*b->z;
 	q->w = beta*a->w + alpha*b->w;
}

Quat4d MatrixToQuaternion(const gm::matrix3f& m)
{
	Quat4d q;
	double m00 = m[0][0];
	double m01 = m[0][1];
	double m02 = m[0][2];
	double m10 = m[1][0];
	double m11 = m[1][1];
	double m12 = m[1][2];
	double m20 = m[2][0];
	double m21 = m[2][1];
	double m22 = m[2][2];

	q.w = sqrt(1.0 + m00 + m11 + m22) / 2.0;
	ASSERT(q.w != 0);

	q.x = (m21 - m12) / (4.0 * q.w);
	q.y = (m02 - m20) / (4.0 * q.w);
	q.z = (m10 - m01) / (4.0 * q.w);

	return q;
}

}
