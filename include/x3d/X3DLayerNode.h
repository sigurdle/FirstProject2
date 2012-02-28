namespace System
{
namespace x3d
{

class X3DEXT X3DLayerNode : public X3DNode, public RenderImplImpl
{
public:

	CTOR X3DLayerNode(NodeType* nodeType);

	X3DNODE_ABSTRACT(X3DLayerNode, X3DNode)

	X3DSFIELD(SFBool, isPickable, IsPickable)
#ifndef __LERSTAD__
	X3DSFIELD(TypedSFNode<X3DViewportNode*>, viewport, Viewport)
#else
	void* m_viewport;//X3DSFIELD(SFNode, viewport, Viewport)
#endif

	void InitStacks();

// Bindable nodes stacks
	stack<NavigationInfo*> m_navigationinfoStack;
	stack<X3DViewpointNode*> m_viewpointStack;
	stack<X3DBackgroundNode*> m_backgroundStack;
	stack<Fog*> m_fogStack;
};

}	// x3d
}	// System
