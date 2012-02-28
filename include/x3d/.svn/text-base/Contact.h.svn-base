namespace System
{
namespace x3d
{

class X3DEXT Contact : public X3DNode
{
public:

	CTOR Contact();

	static NodeType* GetNodeType();

	MFString* m_appliedParameters;	//        "BOUNCE" []
	TypedSFNode<RigidBody*>* m_body1;	//                    NULL     [RigidBody]
	TypedSFNode<RigidBody*>* m_body2;	//                    NULL     [RigidBody]
	SFFloat* m_bounce;	//                   0        [0,1]
	SFVec3f* m_contactNormal;	//            0 1 0    (-?,?)
	SFFloat* m_depth;	//                    0        (-?,?)
	SFVec2f* m_frictionCoefficients;	//     0 0      [0,?)
	SFVec3f* m_frictionDirection;	//        0 1 0    (-?,?)
	TypedSFNode<X3DNBodyCollidableNode*>* m_geometry1;	//                NULL     [X3DNBodyCollidableNode]
	TypedSFNode<X3DNBodyCollidableNode*>* m_geometry2;	//                NULL     [X3DNBodyCollidableNode]
	SFFloat* m_minbounceSpeed;	//           0        [0,?)
	SFVec3f* m_position;	//                 0 0 0    (-?,?)
	SFVec2f* m_slipCoefficients;	//         0 0      (-?,?)
	SFFloat* m_softnessConstantForceMix;	// 0.0001   [0,1]
	SFFloat* m_softnessErrorCorrection;	//  0.8      [0,1]
	SFVec2f* m_surfaceSpeed;	//             0 0      (-?,?)

	/*
  MFString [in,out] appliedParameters        "BOUNCE" []
  SFNode   [in,out] body1                    NULL     [RigidBody]
  SFNode   [in,out] body2                    NULL     [RigidBody]
  SFFloat  [in,out] bounce                   0        [0,1]
  SFVec3f  [in,out] contactNormal            0 1 0    (-?,?)
  SFFloat  [in,out] depth                    0        (-?,?)
  SFVec2f  [in,out] frictionCoefficients     0 0      [0,?)
  SFVec3f  [in,out] frictionDirection        0 1 0    (-?,?)
  SFNode   [in,out] geometry1                NULL     [X3DNBodyCollidableNode]
  SFNode   [in,out] geometry2                NULL     [X3DNBodyCollidableNode]
  SFNode   [in,out] metadata                 NULL     [X3DMetadataObject]
  SFFloat  [in,out] minbounceSpeed           0        [0,?)
  SFVec3f  [in,out] position                 0 0 0    (-?,?)
  SFVec2f  [in,out] slipCoefficients         0 0      (-?,?)
  SFFloat  [in,out] softnessConstantForceMix 0.0001   [0,1]
  SFFloat  [in,out] softnessErrorCorrection  0.8      [0,1]
  SFVec2f  [in,out] surfaceSpeed             0 0      (-?,?)
	  */

private:

	static NodeType* nodeType;
};

}
}
