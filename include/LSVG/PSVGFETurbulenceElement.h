#ifndef w3c_PSVGFETurbulenceElement_h
#define w3c_PSVGFETurbulenceElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGFETurbulenceElement : public PSVGFEElement
{
public:
	CTOR PSVGFETurbulenceElement(SVGFETurbulenceElement* element);

struct StitchInfo
{
  int nWidth; // How much to subtract to wrap for stitching.
  int nHeight;
  int nWrapX; // Minimum value to wrap.
  int nWrapY;
};

#define BSize 0x100
#define BM 0xff
#define PerlinN 0x1000
#define NP 12 /* 2^PerlinN */
#define NM 0xfff

	StitchInfo stitch;

	signed uLatticeSelector[BSize + BSize + 2];
	double fGradient[4][BSize + BSize + 2][2];

	void init(long lSeed);

	double noise2(int nColorChannel, double vec[2], StitchInfo *pStitchInfo);

	double turbulence(int nColorChannel, double *point, double fBaseFreqX, double fBaseFreqY,
          int nNumOctaves, bool bFractalSum, bool bDoStitching,
          double fTileX, double fTileY, double fTileWidth, double fTileHeight);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// w3c
}

#endif // w3c_PSVGFETurbulenceElement_h
