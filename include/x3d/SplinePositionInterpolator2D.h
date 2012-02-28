namespace System
{
namespace x3d
{

class X3DEXT SplinePositionInterpolator2D : public X3DInterpolatorNode
{
public:
	CTOR SplinePositionInterpolator2D();

	X3DNODE(SplinePositionInterpolator2D, X3DInterpolatorNode)

	/*
  SFFloat [in]     set_fraction            (-?,?)
  SFBool  [in,out] closed            FALSE
  MFFloat [in,out] key               []    (-?,?)
  MFVec2f [in,out] keyValue          []    (-?,?)
  MFVec2f [in,out] keyVelocity       []    (-?,?)
  SFNode  [in,out] metadata          NULL  [X3DMetadataObject]
  SFBool  [in,out] normalizeVelocity FALSE
  SFVec2f [out]    value_changed
  */
};

}	// x3d
}	// System
