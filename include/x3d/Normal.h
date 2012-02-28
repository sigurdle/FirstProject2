#ifndef x3d_Normal_h
#define x3d_Normal_h

namespace System
{
namespace x3d
{

class X3DEXT Normal : public X3DNormalNode
{
public:
	CTOR Normal();
	~Normal();

	MFVec3f* getVectorField()
	{
		return m_vector;
	}

	static NodeType* GetNodeType();

private:

	/*
	MFVec3f [in,out] vector [] (-8,8)
  */
	MFVec3f* m_vector;

	static NodeType* nodeType;
};

}	// x3d
}

#endif // x3d_Normal_h
