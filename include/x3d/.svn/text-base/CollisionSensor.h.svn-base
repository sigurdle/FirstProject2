namespace System
{
namespace x3d
{

class X3DEXT CollisionCollection : public X3DNode
{
public:

	CTOR CollisionCollection();

};

class X3DEXT CollisionSensor : public X3DSensorNode
{
public:

	CTOR CollisionSensor();

	TypedSFNode<CollisionCollection*>* m_collider;//      NULL [CollisionCollection]
	SFBool* m_enabled; //      TRUE
//	SFNode* m_metadata; //     NULL [X3DMetadataObject]
	MFNode* m_intersections;	//     [X3DNBodyCollidableNode]
	MFNode* m_contacts;  //         [Contact]
	SFBool* m_isActive;

/*
	SFNode [in,out] collider      NULL [CollisionCollection]
	SFBool [in,out] enabled       TRUE
	SFNode [in,out] metadata      NULL [X3DMetadataObject]
	MFNode [out]    intersections	     [X3DNBodyCollidableNode]
	MFNode [out]    contacts           [Contact]
	SFBool [out]    isActive
*/
};

}	// x3d
}	// System
