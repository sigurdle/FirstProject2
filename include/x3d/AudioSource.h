#ifndef x3d_AudioSource_h
#define x3d_AudioSource_h

namespace System
{
namespace x3d
{

class X3DEXT AudioSource :
	public X3DSoundSourceNode,
	public X3DUrlObject
{
public:
	CTOR AudioSource();

	X3DMFIELD(MFString, url, Url)
	X3DSFIELD(SFFloat, speed, Speed)
	X3DSFIELD(SFFloat, pitch, Pitch)

	X3DNODE(AudioSource, X3DSoundSourceNode)
};

}	// x3d
}

#endif // x3d_AudioSource_h
