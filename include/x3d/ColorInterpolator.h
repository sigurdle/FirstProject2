#ifndef x3d_ColorInterpolator_h
#define x3d_ColorInterpolator_h

namespace System
{
namespace x3d
{

class X3DEXT ColorInterpolator :
	public X3DInterpolatorNode	// X3DChildNode / X3DNode
{
public:
	CTOR ColorInterpolator();

	virtual void OnFieldChanged(X3DField* pField) override;

	X3DNODE(ColorInterpolator, X3DInterpolatorNode)

	static TypedX3DFieldDefinition<MFColor>* get_keyValueFieldDef();
	static TypedX3DFieldDefinition<SFColor>* get_valueChangedFieldDef();

private:

	MFColor* m_keyValue;
	SFColor* m_valueChanged;
};

}	// x3d
}	// System

#endif // x3d_ColorInterpolator_h
