#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFETurbulenceElement.h"
#include "SVGFETurbulenceElement.h"

namespace System
{
namespace Web
{

PSVGFETurbulenceElement::PSVGFETurbulenceElement(SVGFETurbulenceElement* element) : PSVGFEElement(element)
{
}

#if 0

class CTurbulence : public CI2DEffectImpl
{
protected:
	CIParam* paramID[6];

	StitchInfo stitch;

	signed uLatticeSelector[BSize + BSize + 2];
	double fGradient[4][BSize + BSize + 2][2];

	void init(long lSeed);

	double noise2(int nColorChannel, double vec[2], StitchInfo *pStitchInfo);

	double turbulence(int nColorChannel, double *point, double fBaseFreqX, double fBaseFreqY,
          int nNumOctaves, BOOL bFractalSum, BOOL bDoStitching,
          double fTileX, double fTileY, double fTileWidth, double fTileHeight);

public:
	IMETHOD DWORD GetVideoFlags();
	IMETHOD long OnAddParams(CI2DLayer* m_pLayer, LPPFILTERRECORD r);
	IMETHOD long FilterRect(CI2DLayer* m_pLayer, LPPFILTERRECORD r);
	IMETHOD long FrameSetup(CI2DLayer* m_pLayer, LPPFILTERRECORD r);
	IMETHOD long FrameSetdown(CI2DLayer* m_pLayer, LPPFILTERRECORD r);
	IMETHOD BOOL HasImage() { return TRUE; }
};
#endif

/* Produces results in the range [1, 2**31 - 2].
Algorithm is: r = (a * r) mod m
where a = 16807 and m = 2**31 - 1 = 2147483647
See [Park & Miller], CACM vol. 31 no. 10 p. 1195, Oct. 1988
To test: the algorithm should produce the result 1043618065
as the 10,000th generated number if the original seed is 1.
*/
#define RAND_m 2147483647 /* 2**31 - 1 */
#define RAND_a 16807 /* 7**5; primitive root of m */
#define RAND_q 127773 /* m / a */
#define RAND_r 2836 /* m % a */

long setup_seed(long lSeed)
{
  if (lSeed <= 0) lSeed = -(lSeed % (RAND_m - 1)) + 1;
  if (lSeed > RAND_m - 1) lSeed = RAND_m - 1;
  return lSeed;
}

long random(long lSeed)
{
  long result;
  result = RAND_a * (lSeed % RAND_q) - RAND_r * (lSeed / RAND_q);
  if (result <= 0) result += RAND_m;
  return result;
}

void PSVGFETurbulenceElement::init(long lSeed)
{
  double s;
  int i, j, k;
  lSeed = setup_seed(lSeed);
  for(k = 0; k < 4; k++)
  {
    for(i = 0; i < BSize; i++)
    {
      uLatticeSelector[i] = i;
      for (j = 0; j < 2; j++)
        fGradient[k][i][j] = (double)(((lSeed = random(lSeed)) % (BSize + BSize)) - BSize) / BSize;
      s = double(sqrt(fGradient[k][i][0] * fGradient[k][i][0] + fGradient[k][i][1] * fGradient[k][i][1]));
      fGradient[k][i][0] /= s;
      fGradient[k][i][1] /= s;
    }
  }
  while(--i)
  {
    k = uLatticeSelector[i];
    uLatticeSelector[i] = uLatticeSelector[j = (lSeed = random(lSeed)) % BSize];
    uLatticeSelector[j] = k;
  }
  for(i = 0; i < BSize + 2; i++)
  {
    uLatticeSelector[BSize + i] = uLatticeSelector[i];
    for(k = 0; k < 4; k++)
      for(j = 0; j < 2; j++)
        fGradient[k][BSize + i][j] = fGradient[k][i][j];
  }
}

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )

double PSVGFETurbulenceElement::noise2(int nColorChannel, double vec[2], StitchInfo *pStitchInfo)
{
  int bx0, bx1, by0, by1, b00, b10, b01, b11;
  double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
  int i, j;
  t = vec[0] + PerlinN;
  bx0 = (int)t;
  bx1 = bx0+1;
  rx0 = t - (int)t;
  rx1 = rx0 - 1.0f;
  t = vec[1] + PerlinN;
  by0 = (int)t;
  by1 = by0+1;
  ry0 = t - (int)t;
  ry1 = ry0 - 1.0f;

  // If stitching, adjust lattice points accordingly.
  if(pStitchInfo != NULL)
  {
    if(bx0 >= pStitchInfo->nWrapX)
      bx0 -= pStitchInfo->nWidth;
    if(bx1 >= pStitchInfo->nWrapX)
      bx1 -= pStitchInfo->nWidth;
    if(by0 >= pStitchInfo->nWrapY)
      by0 -= pStitchInfo->nHeight;
    if(by1 >= pStitchInfo->nWrapY)
      by1 -= pStitchInfo->nHeight;
  }

  bx0 &= BM;
  bx1 &= BM;
  by0 &= BM;
  by1 &= BM;

  i = uLatticeSelector[bx0];
  j = uLatticeSelector[bx1];
  b00 = uLatticeSelector[i + by0];
  b10 = uLatticeSelector[j + by0];
  b01 = uLatticeSelector[i + by1];
  b11 = uLatticeSelector[j + by1];
  sx = double(s_curve(rx0));
  sy = double(s_curve(ry0));
  q = fGradient[nColorChannel][b00]; u = rx0 * q[0] + ry0 * q[1];
  q = fGradient[nColorChannel][b10]; v = rx1 * q[0] + ry0 * q[1];
  a = lerp(sx, u, v);
  q = fGradient[nColorChannel][b01]; u = rx0 * q[0] + ry1 * q[1];
  q = fGradient[nColorChannel][b11]; v = rx1 * q[0] + ry1 * q[1];
  b = lerp(sx, u, v);
  return lerp(sy, a, b);
}

double PSVGFETurbulenceElement::turbulence(int nColorChannel, double *point, double fBaseFreqX, double fBaseFreqY,
          int nNumOctaves, bool bFractalSum, bool bDoStitching,
          double fTileX, double fTileY, double fTileWidth, double fTileHeight)
{
  StitchInfo *pStitchInfo = NULL; // Not stitching when NULL.

  // Adjust the base frequencies if necessary for stitching.
  if (bDoStitching)
  {
    // When stitching tiled turbulence, the frequencies must be adjusted
    // so that the tile borders will be continuous.
    double fLoFreq = double(floor(fTileWidth * fBaseFreqX)) / fTileWidth;
    double fHiFreq = double(ceil(fTileWidth * fBaseFreqX)) / fTileWidth;
    if(fBaseFreqX / fLoFreq < fHiFreq / fBaseFreqX)
      fBaseFreqX = fLoFreq;
    else
      fBaseFreqX = fHiFreq;

    fLoFreq = double(floor(fTileHeight * fBaseFreqX)) / fTileHeight;
    fHiFreq = double(ceil(fTileHeight * fBaseFreqX)) / fTileHeight;
    if (fBaseFreqY / fLoFreq < fHiFreq / fBaseFreqY)
      fBaseFreqY = fLoFreq;
    else
      fBaseFreqY = fHiFreq;

    // Set up initial stitch values.
    pStitchInfo = &stitch;
    stitch.nWidth = int(fTileWidth * fBaseFreqX + 0.5f);
    stitch.nWrapX = fTileX * fBaseFreqX + PerlinN + stitch.nWidth;
    stitch.nHeight = int(fTileHeight * fBaseFreqY + 0.5f);
    stitch.nWrapY = fTileY * fBaseFreqY + PerlinN + stitch.nHeight;
  }

  double fSum = 0.0f;
  double vec[2];
  vec[0] = point[0] * fBaseFreqX;
  vec[1] = point[1] * fBaseFreqY;
  double ratio = 1;
  for (int nOctave = 0; nOctave < nNumOctaves; nOctave++)
  {
    if(bFractalSum)
      fSum += double(noise2(nColorChannel, vec, pStitchInfo) / ratio);
    else
      fSum += double(fabs(noise2(nColorChannel, vec, pStitchInfo)) / ratio);

    vec[0] *= 2;
    vec[1] *= 2;
    ratio *= 2;

    if (pStitchInfo != NULL)
    {
      // Update stitch values. Subtracting PerlinN before the multiplication and
      // adding it afterward simplifies to subtracting it once.
      stitch.nWidth *= 2;
      stitch.nWrapX = 2 * stitch.nWrapX - PerlinN;
      stitch.nHeight *= 2;
      stitch.nWrapY = 2 * stitch.nWrapY - PerlinN;
    }
  }
  return fSum;
}

// virtual
int PSVGFETurbulenceElement::GetInCount()
{
	return 0;
}

//virtual
Gui::CEffect* PSVGFETurbulenceElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGFETurbulenceElement* psvgElement = static_cast<CLSVGFETurbulenceElement*>(m_pNode);

	long nNumOctaves = (long)psvgElement->m_numOctaves->m_animated->m_animVal->m_value.m_value;
	double fBaseFreqX = psvgElement->m_baseFrequency->m_animated->m_animVal->m_value.m_value[0];
	double fBaseFreqY = psvgElement->m_baseFrequency->m_animated->m_animVal->m_value.m_value[1];
	long bDoStitching = FALSE;
	long lSeed = 0;	// default is 0
	long bFractalSum = TRUE;//FALSE;

	init(lSeed);

	LDraw::BitmapData dstdata;
	outImage->LockBits(
		&LDraw::Rect(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite,
		PixelFormat32bppARGB, &dstdata);

	int width = dstdata.Width;
	int height = dstdata.Height;

	double fTileX = 0;
	double fTileY = 0;
	double fTileWidth = width;
	double fTileHeight = height;

	for (int ch = 0; ch < 4; ch++)
	{
		for (int y = 0; y < height; y++)
		{
			ARGBPixel* out = (ARGBPixel*)((BYTE*)dstdata.Scan0 + dstdata.Stride*y);

			for (int x = 0; x < width; x++)
			{
				double point[2];
				point[0] = x;
				point[1] = y;

				double turbFunctionResult;

				turbFunctionResult = 
					turbulence(ch, point, fBaseFreqX, fBaseFreqY,
					nNumOctaves, bFractalSum, bDoStitching,
					fTileX, fTileY, fTileWidth, fTileHeight);

				long value;

				if (bFractalSum)
				{
					value = ((turbFunctionResult * 255) + 255) / 2;
				}
				else
				{
					value = (turbFunctionResult * 255);
				}

				if (value < 0) value = 0;
				else if (value > 255) value = 255;

				switch (ch)
				{
				case 0: out->red = value;		break;
				case 1: out->green = value;	break;
				case 2: out->blue = value;		break;
				case 3: out->alpha = value;	break;
				}
/*
				if (ch == 3)
				{
				// Un - premultiply destination
					if (out->alpha > 0)
					{
						out->red = ((int)out->red * 255) / out->alpha;
						out->green = ((int)out->green * 255) / out->alpha;
						out->blue = ((int)out->blue * 255) / out->alpha;
					}
				}
*/
				out++;
			}
		}
	}

	outImage->UnlockBits(&dstdata);
#endif
	return 0;
}

#if 0

LONG CTurbulence::FilterRect(CI2DLayer* m_pLayer, LPPFILTERRECORD r)
{
	LONG err = 0;

   long nNumOctaves;
	long lBaseFreqX;
	long lBaseFreqY;
	long bDoStitching;
	long lSeed;
	long bFractalSum;

	paramID[0]->GetParamTags(PARAM_SLIDER_Value, &lBaseFreqX, TAG_DONE);
	paramID[1]->GetParamTags(PARAM_SLIDER_Value, &lBaseFreqY, TAG_DONE);
	paramID[2]->GetParamTags(PARAM_SLIDER_Value, &nNumOctaves, TAG_DONE);
	paramID[3]->GetParamTags(PARAM_SLIDER_Value, &lSeed, TAG_DONE);
	paramID[4]->GetParamTags(PARAM_POPUP_Value, &bDoStitching, TAG_DONE);
	paramID[5]->GetParamTags(PARAM_POPUP_Value, &bFractalSum, TAG_DONE);

	double fBaseFreqX = (lBaseFreqX/65536.0)/100.0;
	double fBaseFreqY = (lBaseFreqY/65536.0)/100.0;
	nNumOctaves >>= 16;
	lSeed >>= 16;

	init(lSeed);

	int width = r->inImage->width;
	int height = r->inImage->height;

	double fTileX = 0;
	double fTileY = 0;
	double fTileWidth = width;
	double fTileHeight = height;

	for (int ch = 0; ch < 4; ch++)
	{
		for (int y = 0; y < height; y++)
		{
			PixelDef* out = (PixelDef*)(r->outImage->data + r->outImage->rowbytes*y);

			for (int x = 0; x < width; x++)
			{
				double point[2];
				point[0] = x;
				point[1] = y;

				double turbFunctionResult;

				turbFunctionResult = 
					turbulence(ch, point, fBaseFreqX, fBaseFreqY,
					nNumOctaves, bFractalSum, bDoStitching,
					fTileX, fTileY, fTileWidth, fTileHeight);

				long value;

				if (bFractalSum)
				{
					value = ((turbFunctionResult * 255) + 255) / 2;
				}
				else
				{
					value = (turbFunctionResult * 255);
				}

				if (value < 0) value = 0;
				else if (value > 255) value = 255;

				switch (ch)
				{
				case 0: out->red = value;		break;
				case 1: out->green = value;	break;
				case 2: out->blue = value;		break;
				case 3: out->alpha = value;	break;
				}
/*
				if (ch == 3)
				{
				// Un - premultiply destination
					if (out->alpha > 0)
					{
						out->red = ((int)out->red * 255) / out->alpha;
						out->green = ((int)out->green * 255) / out->alpha;
						out->blue = ((int)out->blue * 255) / out->alpha;
					}
				}
*/
				out++;
			}
		}
	}

	return 0;
}

LONG CTurbulence::OnAddParams(CI2DLayer* m_pLayer, LPPFILTERRECORD r)
{
	CIParam* id;

	id = paramID[0] = m_pLayer->AddParamTags(PARAM_SLIDER, -1,
		(PARAM_Name),					("BaseFreq X"),
		(PARAM_UniqID),				1,
		(PARAM_SLIDER_Value),		1<<16,
		(PARAM_SLIDER_MinValue),	1<<16,
		(PARAM_SLIDER_MaxValue),	100<<16,
	//	(PARAM_SLIDER_ScaleValue),	100<<16,
		(PARAM_SLIDER_Precision),	2,
		(TAG_DONE));
	if (id == 0) return 1;

	id = paramID[1] = m_pLayer->AddParamTags(PARAM_SLIDER, -1,
		(PARAM_Name),					("BaseFreq Y"),
		(PARAM_UniqID),				2,
		(PARAM_SLIDER_Value),		1<<16,
		(PARAM_SLIDER_MinValue),	1<<16,
		(PARAM_SLIDER_MaxValue),	100<<16,
	//	(PARAM_SLIDER_ScaleValue),	100<<16,
		(PARAM_SLIDER_Precision),	2,
		(TAG_DONE));
	if (id == 0) return 1;

	id = paramID[2] = m_pLayer->AddParamTags(PARAM_SLIDER, -1,
		(PARAM_Name),					("Octaves"),
		(PARAM_UniqID),				3,
		(PARAM_SLIDER_Value),		1<<16,
		(PARAM_SLIDER_MinValue),	0<<16,
		(PARAM_SLIDER_MaxValue),	10<<16,
		(TAG_DONE));
	if (id == 0) return 1;

	id = paramID[3] = m_pLayer->AddParamTags(PARAM_SLIDER, -1,
		(PARAM_Name),					("Seed"),
		(PARAM_UniqID),				4,
		(PARAM_SLIDER_Value),		0<<16,
		(PARAM_SLIDER_MinValue),	0<<16,
		(PARAM_SLIDER_MaxValue),	100<<16,
		(PARAM_SLIDER_Precision),	2,
		(TAG_DONE));
	if (id == 0) return 1;


	id = paramID[4] = m_pLayer->AddParamTags(PARAM_POPUP, -1,
		(PARAM_Name),					("Stitch Tiles"),
		(PARAM_UniqID),				5,
		(PARAM_POPUP_ChoiceString),"No Stitch|Stitch",
		(PARAM_POPUP_NumChoices),	2,
		(PARAM_POPUP_Value),			1,
		(TAG_DONE));
	if (id == 0) return 1;

	id = paramID[5] = m_pLayer->AddParamTags(PARAM_POPUP, -1,
		(PARAM_Name),					("Type"),
		(PARAM_UniqID),				6,
		(PARAM_POPUP_ChoiceString),"Turbulence|Fractal Noise",
		(PARAM_POPUP_NumChoices),	2,
		(PARAM_POPUP_Value),			1,
		(TAG_DONE));
	if (id == 0) return 1;

	return 0;
}

#endif

}	// LSVG
}
