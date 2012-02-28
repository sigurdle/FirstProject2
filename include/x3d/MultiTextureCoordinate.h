#ifndef x3d_MultiTextureCoordinate_h
#define x3d_MultiTextureCoordinate_h

namespace System
{
namespace x3d
{

class X3DEXT MultiTextureCoordinate : public X3DTextureCoordinateNode
{
public:
	CTOR MultiTextureCoordinate();
	~MultiTextureCoordinate();

	MFNode* get_texCoordField() const
	{
		return m_texCoord;
	}

	static NodeType s_nodeType;

private:

/*
	MFNode [in,out] texCoord NULL [X3DTextureCoordinateNode]
*/

	MFNode* m_texCoord;
};

}	// x3d
}

#endif // x3d_MultiTextureCoordinate_h
