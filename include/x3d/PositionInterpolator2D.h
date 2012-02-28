#ifndef x3d_PositionInterpolator2D_h
#define x3d_PositionInterpolator2D_h

namespace System
{
namespace x3d
{

class X3DEXT PositionInterpolator2D :
	public X3DInterpolatorNode
{
public:
	CTOR PositionInterpolator2D();
	~PositionInterpolator2D();

	virtual MFVec2f* get_keyValueField() const
	{
		return m_keyValue;
	}

	virtual SFVec2f* get_valueChangedField() const
	{
		return m_valueChanged;
	}

	virtual void OnFieldChanged(X3DField* pField) override;

	static NodeType* GetNodeType();

protected:

	MFVec2f* m_keyValue;
	SFVec2f* m_valueChanged;

	static NodeType* nodeType;
};

}	// x3d
}	// System

#endif // x3d_PositionInterpolator2D_h
