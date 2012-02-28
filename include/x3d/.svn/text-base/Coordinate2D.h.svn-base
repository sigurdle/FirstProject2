#ifndef x3d_Coordinate2D_h
#define x3d_Coordinate2D_h

namespace System
{
namespace x3d
{

class X3DEXT Coordinate2D :
	public X3DCoordinateNode
{
public:
	CTOR Coordinate2D();
	~Coordinate2D();

	MFVec2f* getPoint();

	static NodeType s_nodeType;

	static X3DFieldDefinition* get_pointFieldDef();

protected:

	/*
		MFVec2f [in,out] point [NULL] (-8,8)
  */

	MFVec2f* m_point;
};

}	// x3d
}

#endif // x3d_Coordinate2D_h
