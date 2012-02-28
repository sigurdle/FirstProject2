namespace System
{
namespace x3d
{

class X3DEXT SplinePositionInterpolator : public X3DInterpolatorNode
{
public:
	CTOR SplinePositionInterpolator();

	X3DNODE(SplinePositionInterpolator, X3DInterpolatorNode)

	/*
  SFFloat [in]     set_fraction            (-?,?)
  SFBool  [in,out] closed            FALSE
  MFFloat [in,out] key               []    (-?,?)
  MFVec3f [in,out] keyValue          []    (-?,?)
  MFVec3f [in,out] keyVelocity       []    (-?,?)
  SFNode  [in,out] metadata          NULL  [X3DMetadataObject]
  SFBool  [in,out] normalizeVelocity FALSE
  SFVec3f [out]    value_changed
  */
};

}	// x3d
}	// System
