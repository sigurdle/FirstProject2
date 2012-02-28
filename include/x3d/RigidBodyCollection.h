namespace System
{
namespace x3d
{

class X3DEXT RigidBodyCollection : public X3DChildNode
{
public:

	CTOR RigidBodyCollection();

	X3DSFIELD(SFBool, enabled, Enabled)
	X3DSFIELD(SFBool, autoDisable, AutoDisable)
	X3DSFIELD(SFVec3f, gravity, Gravity)
	X3DSFIELD(SFInt32, iterations, Iterations)
	X3DSFIELD(SFFloat, contactSurfaceThickness, ContactSurfaceThickness)
#ifndef __LERSTAD__
	X3DMFIELD(TypedMFNode<RigidBody*>, bodies, Bodies)
#else
	X3DMFIELD(MFNode, bodies, Bodies)
#endif

	X3DNODE(RigidBodyCollection, X3DChildNode)

	virtual void addActors() override;
	virtual void UpdatePos() override;

	physx::PxScene* getNxScene()
	{
		return m_nxScene;
	}

	TypedMFNode<Contact*>* m_set_contacts;	//            []       [Contact] 
//	SFBool* m_autoDisable;	//             FALSE
//	TypedMFNode<RigidBody*>* m_bodies;	//                  []       [RigidBody]
	SFFloat* m_constantForceMix;	//        0.0001   [0,?)
//	SFFloat* m_contactSurfaceThickness;	// 0        [0,?)
	SFFloat* m_disableAngularSpeed;	//     0        [0,?)
	SFFloat* m_disableLinearSpeed;	//      0        [0,?)
	SFFloat* m_disableTime;	//             0        [0,?)
//	SFBool* m_enabled;	//                 TRUE
	SFFloat* m_errorCorrection;	//         0.8      [0,1]
//	SFVec3f* m_gravity;	//                 0 -9.8 0
//	SFInt32* m_iterations;	//              10	    [0,?)
	TypedMFNode<X3DRigidJointNode*>* m_joints;	//                  []       [X3DRigidJointNode]
	SFFloat* m_maxCorrectionSpeed;	//      -1       [0,?) or -1
	SFBool* m_preferAccuracy;	//          FALSE
	TypedSFNode<CollisionCollection*>* m_collider;	//                NULL     [CollisionCollection]

/*
	MFNode  [in]     set_contacts            []       [Contact] 
	SFBool  [in,out] autoDisable             FALSE
	MFNode  [in,out] bodies                  []       [RigidBody]
	SFFloat [in,out] constantForceMix        0.0001   [0,?)
	SFFloat [in,out] contactSurfaceThickness 0        [0,?)
	SFFloat [in,out] disableAngularSpeed     0        [0,?)
	SFFloat [in,out] disableLinearSpeed      0        [0,?)
	SFFloat [in,out] disableTime             0        [0,?)
	SFBool  [in,out] enabled                 TRUE
	SFFloat [in,out] errorCorrection         0.8      [0,1]
	SFVec3f [in,out] gravity                 0 -9.8 0
	SFInt32 [in,out] iterations              10	    [0,?)
	MFNode  [in,out] joints                  []       [X3DRigidJointNode]
	SFFloat [in,out] maxCorrectionSpeed      -1       [0,?) or -1
	SFNode  [in,out] metadata                NULL     [X3DMetadataObject]
	SFBool  [in,out] preferAccuracy          FALSE
	SFNode  []       collider                NULL     [CollisionCollection]
	*/

protected:

	physx::PxScene* m_nxScene;
};

}	// x3d
}	// System
