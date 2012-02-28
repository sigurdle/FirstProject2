#ifndef __LSMILTRANSITIONFACTORY_H_
#define __LSMILTRANSITIONFACTORY_H_

#ifndef LSMILTransitionsExt
#define LSMILTransitionsExt DECLSPEC_DLLIMPORT
#endif

namespace System
{

struct ISMILTransition
{
public:
	virtual ErrorCode Process(double progress,
		gm::RectF rectA, Graphics::Bitmap* pBitmapA,
		gm::RectF rectB, Graphics::Bitmap* pBitmapB,
		gm::RectF rect, Graphics::Bitmap* pBitmap) = 0;
};

class LSMILTransitionsExt SMILTransitionFactory
{
public:
	SMILTransitionFactory();
	virtual ~SMILTransitionFactory();

	virtual ErrorCode FindTransition(StringIn type, StringIn subtype, ISMILTransition* *pVal);
	virtual ErrorCode ProcessTransition(ISMILTransition* transition, long horzRepeat, long vertRepeat, long borderWidth, bool borderColorBlend, double progress, Graphics::Bitmap* srcBitmapA, Graphics::Bitmap* srcBitmapB, Graphics::Bitmap* dstBitmap);
};

}

#endif //__LSMILTRANSITIONFACTORY_H_
