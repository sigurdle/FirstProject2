#ifndef x3d_TextureCoordinateGenerator_h
#define x3d_TextureCoordinateGenerator_h

namespace System
{
namespace x3d
{

class TextureCoordinateGenerator : public X3DTextureCoordinateNode
{
public:
	CTOR TextureCoordinateGenerator();
	~TextureCoordinateGenerator();

	String getMode() const
	{
		return m_mode->getValue();
	}

	static NodeType s_nodeType;

protected:

	SFString* m_mode;
	MFFloat* m_parameter;
};

}	// x3d
}

#endif // x3d_TextureCoordinateGenerator_h
