#ifndef x3d_PixelTexture_h
#define x3d_PixelTexture_h

namespace System
{
namespace x3d
{

class X3DEXT PixelTexture : public X3DTexture2DNode
{
public:
	CTOR PixelTexture();

	X3DSFIELD(SFImage, image, Image)
	X3DSFIELD(SFBool, repeatT, RepeatT)
	X3DSFIELD(SFBool, repeatS, RepeatS)
#ifndef __LERSTAD__
	X3DSFIELD(TypedSFNode<TextureProperties*>, textureProperties, TextureProperties)
#else
	X3DField* m_textureProperties;
#endif

	X3DNODE(PixelTexture, X3DTexture2DNode)

/*
	SFImage [in,out] image             0 0 0
	SFNode  [in,out] metadata          NULL  [X3DMetadataObject]
	SFBool  []       repeatS           TRUE
	SFBool  []       repeatT           TRUE
	SFNode  []       textureProperties NULL  [TextureProperties]
*/

//	TypedSFNode<TextureProperties*>* m_textureProperties;

};

}	// x3d
}	// System

#endif // x3d_PixelTexture_h
