#ifndef __PDF_h__
#define __PDF_h__

#include "../../include/Draw/Draw.h"

#ifndef PDFExt
#define PDFExt	DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace PDF
{

// Forward Declarations

class CPDFCosObj;
class CPDFCosDict;
class CPDFCosDoc;
class IPDFPDPage;
class IPDFEMatrix;
class IPDFEImage;
class IPDFEPath;
class IPDFEContent;
class IPDFEGraphicState;

enum PDFEPathElementType
{
	kPDFEMoveTo	= 0,
	kPDFELineTo	= kPDFEMoveTo + 1,
	kPDFECurveTo	= kPDFELineTo + 1,
	kPDFECurveToV	= kPDFECurveTo + 1,
	kPDFECurveToY	= kPDFECurveToV + 1,
	kPDFERect	= kPDFECurveToY + 1,
	kPDFEClosePath	= kPDFERect + 1,
	kPDFEPathLastType	= kPDFEClosePath + 1
};

enum PDFEPathOpFlags
{
	kPDFEInvisible	= 0,
	kPDFEStroke	= 0x1,
	kPDFEFill	= 0x2,
	kPDFEEoFill	= 0x4
};

enum PDFEType
{
	kPDFEContent	= 0,
	kPDFEText	= kPDFEContent + 1,
	kPDFEPath	= kPDFEText + 1,
	kPDFEImage	= kPDFEPath + 1,
	kPDFEForm	= kPDFEImage + 1,
	kPDFEPS	= kPDFEForm + 1,
	kPDFEXObject	= kPDFEPS + 1,
	kPDFEClip	= kPDFEXObject + 1,
	kPDFEFont	= kPDFEClip + 1,
	kPDFEColorSpace	= kPDFEFont + 1,
	kPDFEExtGState	= kPDFEColorSpace + 1,
	kPDFEPlace	= kPDFEExtGState + 1,
	kPDFEContainer	= kPDFEPlace + 1,
	kPDFSysFont	= kPDFEContainer + 1,
	kPDFEPattern	= kPDFSysFont + 1,
	kPDFEDeviceNColors	= kPDFEPattern + 1,
	kPDFEShading	= kPDFEDeviceNColors + 1,
	kPDFEGroup	= kPDFEShading + 1,
	kPDFEUnknown	= kPDFEGroup + 1,
	kPDFEBeginContainer	= kPDFEUnknown + 1,
	kPDFEEndContainer	= kPDFEBeginContainer + 1,
	kPDFEBeginGroup	= kPDFEEndContainer + 1,
	kPDFEEndGroup	= kPDFEBeginGroup + 1,
	kPDFEXGroup	= kPDFEEndGroup + 1,
	kPDFESoftMask	= kPDFEXGroup + 1,
	kPDFSysEncoding	= kPDFESoftMask + 1,
	kPDFEDoc	= kPDFSysEncoding + 1,
	kPDFEPage	= kPDFEDoc + 1,
	kPDFELastType	= kPDFEPage + 1
};

}	// PDF
}

#include "PDFCosReal.h"
#include "PDFCosString.h"
#include "PDFCosName.h"
#include "PDFCosStream.h"
#include "PDFCosInteger.h"
#include "PDFCosArray.h"
#include "PDFCosDict.h"
#include "PDFCosBoolean.h"
#include "PDFCosDoc.h"
#include "PDFPDDoc.h"

#endif // __PDF_h__

