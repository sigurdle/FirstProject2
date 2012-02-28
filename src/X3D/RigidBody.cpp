#include "stdafx.h"
#include "X3D2.h"
#include "RigidBody.h"
#include "Shape.h"
#include "CollidableShape.h"
#include "GUI/physics.h"
#include "pxutils.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(RigidBody, SFBool, enabled, Enabled)
IMP_X3DFIELD0(RigidBody, SFVec3f, linearVelocity, LinearVelocity)

NodeType* RigidBody::GetNodeType()
{
	static X3DFieldDefinition angularDampingFactor("angularDampingFactor", SAIFieldAccess_inputOutput, offsetof(RigidBody, m_angularDampingFactor));
	static X3DFieldDefinition geometry("geometry", SAIFieldAccess_inputOutput, offsetof(RigidBody, m_geometry));
	static X3DFieldDefinition mass("mass", SAIFieldAccess_inputOutput, offsetof(RigidBody, m_mass));
	static X3DFieldDefinition position("position", SAIFieldAccess_inputOutput, offsetof(RigidBody, m_position));
	static X3DFieldDefinition orientation("orientation", SAIFieldAccess_inputOutput, offsetof(RigidBody, m_orientation));
	static X3DFieldDefinition angularVelocity("angularVelocity", SAIFieldAccess_inputOutput, offsetof(RigidBody, m_angularVelocity));
//	static X3DFieldDefinition linearVelocity("linearVelocity",  SAIFieldAccess_inputOutput, offsetof(RigidBody, m_linearVelocity));
	static X3DFieldDefinition fixed("fixed",  SAIFieldAccess_inputOutput, offsetof(RigidBody, m_fixed));

	static X3DFieldDefinition* fields[] =
	{
		&angularDampingFactor,
		&geometry,
		&mass,
		&position,
		&orientation,
		&angularVelocity,
		//&linearVelocity,
		get_enabledFieldDef(),
		get_linearVelocityFieldDef(),
		&fixed,
	};

	static NodeType nodeType("RigidBody", typeid(thisClass), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* RigidBody::nodeType(GetNodeType());

RigidBody::RigidBody() : X3DNode(GetNodeType()),
	m_mass(new SFFloat(this, 1.0f))
{
}

void RigidBody::OnFieldChanged(X3DField* field)
{
#if defined(PX_PHYSICS_NXPHYSICS_API)

	if (field == m_position || field == m_orientation)
	{
		// TODO, cache
		m_globalPoseValid = false;

		if (m_actor)
		{

			physx::PxTransform pose(
				_NxVec3(m_position->getValue()),
				_NxQuat(m_orientation->getValue()));

			m_actor->setGlobalPose(pose);
			m_globalPoseValid = true;
		}
	}
	else if (field == m_fixed)
	{
		if (m_actor)
		{
			// TODO
			ASSERT(0);
		}
	}
#endif
	X3DNode::OnFieldChanged(field);
}

void RigidBody::UpdatePosOrient()
{
#if defined(PX_PHYSICS_NXPHYSICS_API)

	physx::PxTransform pose = m_actor->getGlobalPose();

//	physx::PxVec3 pos = m_actor->getGlobalPosition();
//	m_actor->getGlobalOrientationQuat().getAngleAxis(angle, axis);

	float angleRadians;
	physx::PxVec3 axis;
	pose.q.toRadiansAndUnitAxis(angleRadians, axis);

	setPosition(_Vec3f(pose.p));
	setOrientation(Rotation(_Vec3f(axis), angleRadians));

	// TODO, should not be necessary, the above is enough

	MFNode* geometry = getGeometryField();
	for (size_t i = 0; i < geometry->m_items.size(); ++i)
	{
		X3DNode* node = geometry->get1Value(i);

		X3DNBodyCollidableNode* cnode = dynamic_cast<X3DNBodyCollidableNode*>(node);

		cnode->setTranslation(getPosition());
		cnode->setRotation(getOrientation());
	}

	// TODO, not here
	m_scene->Invalidate();
#endif
}

void RigidBody::CreateActor(physx::PxScene* nxScene)
{
#if defined(PX_PHYSICS_NXPHYSICS_API)

	physx::PxTransform pose(_NxVec3(getPosition()), _NxQuat(getOrientation()));

	physx::PxRigidDynamic* actor = Gui::gPhysics->createRigidDynamic(pose);
	ASSERT(m_actor);

	MFNode* geometry = getGeometryField();
	for (size_t i = 0; i < geometry->m_items.size(); ++i)
	{
		X3DNode* node = geometry->get1Value(i);

	//	X3DNBodyCollidableNode* cnode = dynamic_cast<X3DNBodyCollidableNode*>(node);
		CollidableShape* cnode = dynamic_cast<CollidableShape*>(node);
		Shape* shape = cnode->getShape();
		shape->AddShapeDesc(actor);
	}

	float density = 10.0f;
	physx::PxRigidBodyExt::updateMassAndInertia(*actor, density);

// There are two ways to implement fixed bodies in PhysX SDK, either as static or kinematic actors, I've chosen
	// kinematic actors since they can be turned into dynamic actors

//	if (!getFixed())	// Static actor
	{
//		actorDesc.body = &bodyDesc;

//		bodyDesc.angularVelocity = ;
//		bodyDesc.linearVelocity = ;
//	bodyDesc.mass = getMass();

		actor->setAngularVelocity(_NxVec3(getAngularVelocity()));
		actor->setLinearVelocity(_NxVec3(getLinearVelocity()));
	}

	if (getFixed())	// Kinetic actor
	{
		actor->setRigidDynamicFlag(physx::PxRigidDynamicFlag::eKINEMATIC, true);

		//bodyDesc.flags |= NX_BF_KINEMATIC;//NxActor::raiseBodyFlag(NX_BF_KINEMATIC)

		// TODO
		//actor->setKinematicTarget(position);
	}

//	actorDesc.density = 10.0f;
//	actorDesc.globalPose.t = _NxVec3(getPosition());

//	m_actor = nxScene->createActor(actorDesc);
#endif
}

}	// x3d
}	// System
