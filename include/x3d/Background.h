#ifndef x3d_Background_h
#define x3d_Background_h

namespace System
{
namespace x3d
{

/// This represents an X3D background node.
/**
Background uses six static images to compose the backdrop of an X3D Scene.
*/
class X3DEXT Background : public X3DBackgroundNode
{
public:
	CTOR Background();

	X3DMFIELD(MFString, frontUrl, FrontUrl)
	X3DMFIELD(MFString, backUrl, BackUrl)
	X3DMFIELD(MFString, leftUrl, LeftUrl)
	X3DMFIELD(MFString, rightUrl, RightUrl)
	X3DMFIELD(MFString, topUrl, TopUrl)
	X3DMFIELD(MFString, bottomUrl, BottomUrl)

	/// <returns>The X3D NodeType</returns>
	X3DNODE(Background, X3DBackgroundNode)

protected:

	virtual void Draw2(X3DDrawContext* pDC) override;

private:

	Graphics::Bitmap* m_bitmap[6];
	ID3D10Buffer* m_vertexBuffer[6];
};

}	// x3d
}	// System

#endif // x3d_Background_h
