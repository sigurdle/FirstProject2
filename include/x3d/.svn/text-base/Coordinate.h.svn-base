#ifndef x3d_Coordinate_h
#define x3d_Coordinate_h

namespace System
{
namespace x3d
{

class X3DEXT Coordinate : public X3DCoordinateNode
{
public:
	CTOR Coordinate();

	/*
	MFVec3f* getPoint()	// ??
	{
		return m_point;
	}
	*/

	MFVec3f* getPointField()
	{
		return m_point;
	}

	static NodeType* GetNodeType();

	static X3DFieldDefinition* get_pointFieldDef();

private:

	MFVec3f* m_point;

	static NodeType* nodeType;
};

}	// x3d
}

#endif // x3d_Coordinate_h
