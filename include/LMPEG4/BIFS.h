#ifndef __BIFS_H__
#define __BIFS_H__

namespace System
{
namespace Mpeg4
{

class BIFSConfiguration
{
public:
	int nodeIDbits; //The number of bits used to encode the nodeIDs.
	int routeIDbits; //The number of bits used to encode the routeIDs.
	int PROTOIDbits; //The number of bits used to encode the PROTO. This value is in used only
	//if the data for the structure was transmitted by BIFSv2Config
	bool randomAccess;// The randomAccess boolean is set in the BIFSConfig to distinguish
	//between BIFS-Anim elementary streams in which support random access
	//at any intra frame, and those where random access may not be possible
	//at all intra frames. In the latter case, greater compression efficiency may
	//be achieved because a given intra frame may re-use quantization settings
	//and statistics from the previous intra frame.

	//AnimationMask animMask; The AnimationMask used for BIFS-Anim

	bool use3DmeshCoding;
};

}	// Mpeg4
}

#endif // __BIFS_H__
