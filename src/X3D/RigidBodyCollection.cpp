#include "stdafx.h"
#include "X3D2.h"
#include "RigidBody.h"
#include "RigidBodyCollection.h"
#include "CollisionSensor.h"
#include "GUI/physics.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(RigidBodyCollection, SFVec3f, gravity, inputOutput, Vec3f(0, -9.8f, 0))
IMP_X3DFIELD0(RigidBodyCollection, TypedMFNode<RigidBody*>, bodies, inputOutput)
IMP_X3DFIELD3(RigidBodyCollection, SFInt32, iterations, inputOutput, 10, 0, INT_MAX)
IMP_X3DFIELD3(RigidBodyCollection, SFFloat, contactSurfaceThickness, inputOutput, 0.0f, 0.0f, FLT_MAX)

NodeType* RigidBodyCollection::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_gravityFieldDef(),
		get_bodiesFieldDef(),
		get_iterationsFieldDef(),
		get_contactSurfaceThicknessFieldDef(),
	};

	static NodeType nodeType(WSTR("RigidBodyCollection"), typeid(RigidBodyCollection), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* RigidBodyCollection::nodeType(GetNodeType());

RigidBodyCollection::RigidBodyCollection() : X3DChildNode(GetNodeType()),
	m_gravity(new SFVec3f(get_gravityFieldDef(), this)),
	m_iterations(new SFInt32(get_iterationsFieldDef(), this)),
	m_contactSurfaceThickness(new SFFloat(get_contactSurfaceThicknessFieldDef(), this)),
	m_collider(new TypedSFNode<CollisionCollection*>(this)),
	m_bodies(new TypedMFNode<RigidBody*>(get_bodiesFieldDef(), this))
{
}

//void RigidBodyCollection::OnTick(double globalTime)
void RigidBodyCollection::UpdatePos()
{
#ifdef NX_PHYSICS_NXPHYSICS
	ASSERT(m_nxScene);

	float timer_fps = 30.0f;

	NxReal myTimestep = 1.0f/timer_fps;

	m_nxScene->simulate(myTimestep);
    m_nxScene->flushStream();

	while (!m_nxScene->checkResults(NX_RIGID_BODY_FINISHED, false))
	{
		// do something useful
	}
	m_nxScene->fetchResults(NX_RIGID_BODY_FINISHED, true);

	MFNode* bodies = getBodiesField();
	for (uint i = 0; i < bodies->get_size(); ++i)
	{
		X3DNode* node = bodies->get1Value(i);
		RigidBody* rigidBody = dynamic_cast<RigidBody*>(node);
		if (rigidBody)
		{
			rigidBody->UpdatePosOrient();
		}
	}
#endif
}

void RigidBodyCollection::addActors()
{
#ifdef NX_PHYSICS_NXPHYSICS
	if (m_nxScene == NULL)
	{
		// Create PhysX scene
		NxSceneDesc sceneDesc;
		sceneDesc.gravity.set(_NxVec3(m_gravity->getValue()));

	//	Gui::gPhysicsSDK->setParameter(NX_SKIN_WIDTH, getContactSurfaceThickness());

		m_nxScene = Gui::gPhysicsSDK->createScene(sceneDesc);

		if (m_nxScene == NULL)
		{
			ASSERT(0);
		//	raise(Exception(L"Can't create scene"));
			return;
		}

		NxReal myTimestep = 1.0f/30.0f;
		int iterations = getIterations();
		m_nxScene->setTiming(myTimestep / iterations, iterations, NX_TIMESTEP_FIXED);
	}

	MFNode* bodies = getBodiesField();
	for (uint i = 0; i < bodies->get_size(); ++i)
	{
		X3DNode* node = bodies->get1Value(i);
		RigidBody* rigidBody = dynamic_cast<RigidBody*>(node);
		if (rigidBody)
		{
			rigidBody->CreateActor(m_nxScene);
		}
	}
#endif
}

}	// x3d
}	// System
