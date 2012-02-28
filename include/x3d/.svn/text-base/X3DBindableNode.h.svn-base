namespace System
{
namespace x3d
{

class X3DEXT X3DBindableNode : public X3DChildNode
{
protected:
	CTOR X3DBindableNode(NodeType* nodeType);

public:

	X3DSFIELD(SFBool, set_bind, SetBind)
	X3DSFIELD(SFBool, isBound, IsBound)
	X3DSFIELD(SFTime, bindTime, BindTime)

	X3DNODE_ABSTRACT(X3DBindableNode, X3DChildNode)

protected:

/*
	SFBool [in]     set_bind
	SFTime [out]    bindTime
	SFBool [out]    isBound
*/

	friend class X3DScene;
	friend class X3DLayerNode;

//	SFBool* m_set_bind;
//	SFBool* m_isBound;
//	SFTime* m_bindTime;
};

}	// x3d
}	// System
