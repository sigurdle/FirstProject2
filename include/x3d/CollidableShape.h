namespace System
{
namespace x3d
{

class X3DEXT CollidableShape : public X3DNBodyCollidableNode, public RenderImplImpl
{
public:

	CTOR CollidableShape();

	virtual void Draw(X3DDrawContext* pDC) override;
//	virtual void UpdatePos() override;
//	virtual void addActors(NxScene* nxScene, D3DXMATRIX model) override;

	Shape* getShape();

	X3DNODE(CollidableShape, X3DNBodyCollidableNode)

private:

	TypedSFNode<Shape*>* m_shape;
	/*
	SFBool     [in,out] enabled     TRUE
	SFNode     [in,out] metadata    NULL     [X3DMetadataObject]
	SFRotation [in,out] rotation    0 0 1 0  [0,1]
	SFVec3f    [in,out] translation 0 0 0    (-?,?)
	SFVec3f    []       bboxCenter  0 0 0    (-?,?)
	SFVec3f    []       bboxSize    -1 -1 -1 [0,?) or -1 -1 -1
	SFNode     []       shape       NULL     [Shape]
	*/
};

}	// x3d
}	// System
