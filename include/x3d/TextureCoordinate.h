#ifndef x3d_TextureCoordinate_h
#define x3d_TextureCoordinate_h

namespace System
{
namespace x3d
{

class X3DEXT TextureCoordinate : public X3DTextureCoordinateNode
{
public:
	CTOR TextureCoordinate();

	MFVec2f* getPointField()
	{
		return m_point;
	}

	static NodeType* GetNodeType();

public:

	MFVec2f* m_point;

	static NodeType* nodeType;

	/*
		MFVec2f [in,out] point [NULL] (-8,8)
  */

};

}	// x3d
}

#endif // x3d_TextureCoordinate_h
