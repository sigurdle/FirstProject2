namespace System
{
namespace x3d
{

class X3DEXT SplineScalarInterpolator : public X3DInterpolatorNode
{
public:
	CTOR SplineScalarInterpolator();

	X3DNODE(SplineScalarInterpolator, X3DInterpolatorNode)

	X3DSFIELD(SFBool, closed, Closed)
	X3DSFIELD(SFBool, normalizeVelocity, NormalizeVelocity)
	X3DSFIELD(SFFloat, value_changed, ValueChanged)
	X3DMFIELD(MFFloat, keyValue, KeyValue)
	X3DMFIELD(MFFloat, keyVelocity, KeyVelocity)

	virtual void OnFieldChanged(X3DField* pField) override;

	/*
  SFFloat [in]     set_fraction            (-?,?)
  SFBool  [in,out] closed            FALSE
  MFFloat [in,out] key               []    (-?,?)
  MFFloat [in,out] keyValue          []    (-?,?)
  MFFloat [in,out] keyVelocity       []    (-?,?)
  SFNode  [in,out] metadata          NULL  [X3DMetadataObject]
  SFBool  [in,out] normalizeVelocity FALSE
  SFFloat [out]    value_changed
  */
};

}	// x3d
}	// System
