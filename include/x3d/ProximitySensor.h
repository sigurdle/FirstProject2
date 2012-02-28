#ifndef x3d_ProximitySensor_h
#define x3d_ProximitySensor_h

namespace System
{
namespace x3d
{

class X3DEXT ProximitySensor : public X3DEnvironmentalSensorNode
{
public:
	CTOR ProximitySensor();
	~ProximitySensor();

	gm::vector3f getCenter() const
	{
		return m_center->getValue();
	}

	gm::vector3f getSize() const
	{
		return m_size->getValue();
	}

	double getEnterTime() const
	{
		return m_enterTime->getValue();
	}

	double getExitTime() const
	{
		return m_exitTime->getValue();
	}

	static NodeType s_nodeType;

public:

	SFVec3f* m_center;
	SFVec3f* m_size;
	SFTime* m_enterTime;
	SFTime* m_exitTime;
	SFBool* m_isActive;
	SFVec3f* m_centerOfRotation_changed;
	SFRotation* m_orientation_changed;
	SFVec3f* m_position_changed;
};

}	// x3d
}	// System

#endif // x3d_ProximitySensor_h
