#ifndef x3d_X3DGroupingNode_h
#define x3d_X3DGroupingNode_h

namespace System
{
namespace x3d
{

class X3DEXT X3DGroupingNode : public X3DChildNode, public X3DBoundedObject
{
public:
	CTOR X3DGroupingNode(NodeType* nodeType);

	/*
	virtual MFNode* get_children()
	{
		return m_children;
	}
	*/

#ifndef __LERSTAD__
	X3DMFIELD(TypedMFNode<X3DChildNode*>, children, Children)
#else
	X3DMFIELD(MFNode, children, Children)
#endif
	X3DSFIELD_OVERRIDE(SFVec3f, bboxCenter, BBoxCenter)
	X3DSFIELD_OVERRIDE(SFVec3f, bboxSize, BBoxSize)

	X3DNODE_ABSTRACT(X3DGroupingNode, X3DChildNode)

	virtual uint32 GetLights() override
	{
		return m_children->GetLights();
	}

	virtual BoundingBox CalculateBoundingBox(gm::matrix4f& transform) override;

	virtual void addActors() override;
	virtual void UpdatePos() override;

protected:

	MFNode* m_addChildren;
	MFNode* m_removeChildren;

//public:	// TODO
//	MFNode* m_children;
};

}	// x3d
}	// System

#endif // x3d_X3DGroupingNode_h
