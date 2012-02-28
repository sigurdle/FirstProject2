#ifndef __LHTML2_H_
#define __LHTML2_H_

#ifdef __LERSTAD__
#import "LXML/LXML.h"
#else
#include "LXML/LXML.h"
#endif

#ifdef __LERSTAD__
#import "LMedia/LMedia.h"
#else
#include "LMedia/LMedia.h"
#endif

#ifndef HTMLEXT
#define HTMLEXT DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace Web
{

// Forward Declarations

interface ISVGAnimatedRect;
interface ISVGAnimatedBoolean;
interface ISVGRenderElement;

class HTMLElement;
class HTMLCanvasElement;
class SMILMediaElement;
class SMILRegionElement;

class SVGLength;
class SVGLengthMutable;
class SVGPathSeg;
class SVGPathSegList;
class SVGAnimatedString;
class SVGPointList;
class SVGMatrix;
class SVGStringList;

class PHTMLFrameElement;
class PHTMLFrameSetElement;

}	// Web
}

namespace System
{
namespace Web
{

class HTMLEXT HTMLImplementation : public Object, public IXMLImplementation
{
public:
	virtual Element* CreateElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);
};

enum ParseActionType
{
	ACTION_APPEND_AS_CHILDREN = 1,
	ACTION_REPLACE_CHILDREN = 2,
	ACTION_INSERT_BEFORE = 3,
	ACTION_INSERT_AFTER = 4,
	ACTION_REPLACE = 5
};

enum SVGLengthType
{
	SVG_LENGTHTYPE_UNKNOWN = 0,
	SVG_LENGTHTYPE_NUMBER = 1,
	SVG_LENGTHTYPE_PERCENTAGE = 2,
	SVG_LENGTHTYPE_EMS = 3,
	SVG_LENGTHTYPE_EXS = 4,
	SVG_LENGTHTYPE_PX = 5,
	SVG_LENGTHTYPE_CM = 6,
	SVG_LENGTHTYPE_MM = 7,
	SVG_LENGTHTYPE_IN = 8,
	SVG_LENGTHTYPE_PT = 9,
	SVG_LENGTHTYPE_PC = 10
};

enum SVGTransformType
{
	SVG_TRANSFORM_UNKNOWN = 0,
	SVG_TRANSFORM_MATRIX = 1,
	SVG_TRANSFORM_TRANSLATE = 2,
	SVG_TRANSFORM_SCALE = 3,
	SVG_TRANSFORM_ROTATE = 4,
	SVG_TRANSFORM_SKEWX = 5,
	SVG_TRANSFORM_SKEWY = 6
};

enum SVGPreserveAspectRatioAlignType
{
	SVG_PRESERVEASPECTRATIO_UNKNOWN	= 0,
	SVG_PRESERVEASPECTRATIO_NONE	= 1,
	SVG_PRESERVEASPECTRATIO_XMINYMIN	= 2,
	SVG_PRESERVEASPECTRATIO_XMIDYMIN	= 3,
	SVG_PRESERVEASPECTRATIO_XMAXYMIN	= 4,
	SVG_PRESERVEASPECTRATIO_XMINYMID	= 5,
	SVG_PRESERVEASPECTRATIO_XMIDYMID	= 6,
	SVG_PRESERVEASPECTRATIO_XMAXYMID	= 7,
	SVG_PRESERVEASPECTRATIO_XMINYMAX	= 8,
	SVG_PRESERVEASPECTRATIO_XMIDYMAX	= 9,
	SVG_PRESERVEASPECTRATIO_XMAXYMAX	= 10
};

enum SVGMeetOrSliceType
{
	SVG_MEETORSLICE_UNKNOWN	= 0,
	SVG_MEETORSLICE_MEET	= 1,
	SVG_MEETORSLICE_SLICE	= 2
};

enum SVGUnitType
{
	SVG_UNIT_TYPE_UNKNOWN	= 0,
	SVG_UNIT_TYPE_USERSPACEONUSE	= 1,
	SVG_UNIT_TYPE_OBJECTBOUNDINGBOX	= 2
};

interface IXMLDocumentInMemoryProvider
{
	virtual Document* GetInMemoryDocument(StringIn url) = 0;
};

#if 0
class
ILHTMLActiveView
{
public:
  virtual /* [helpstring][propget] */ ErrorCode get_framesDesign( 
		/* [retval][out] */ bool *pVal) = 0;

  virtual /* [helpstring][propput] */ ErrorCode set_framesDesign( 
		/* [in] */ bool newVal) = 0;

  virtual /* [helpstring] */ ErrorCode GetHTMLWindow( 
		/* [retval][out] */ ILHTMLWindow **pVal) = 0;

};
#endif

interface IHTMLCollection
{
};

interface IHTMLFramesCollection
{
#if 0
  virtual /* [helpstring] */ ErrorCode  item( 
		/* [in] */ VARIANT *pvarIndex,
		/* [retval][out] */ VARIANT *pvarResult) = 0;

  virtual /* [helpstring][propget] */ ErrorCode get_length( 
		/* [retval][out] */ long *pVal) = 0;
#endif   
};

// TODO remove
interface IHTMLWindow : public IHTMLFramesCollection
{
	virtual Document* get_document() = 0;
	virtual Event* get_event() = 0;
	virtual IHTMLWindow* get_parent() = 0;
	virtual IHTMLFramesCollection* get_frames() = 0;
	virtual String get_status() = 0;
	virtual void set_status(StringIn v) = 0;
	virtual bool get_closed() = 0;

#if 0
  virtual ErrorCode  setTimeout( 
		/* [in] */ VARIANT *expression,
		/* [in] */ long msec,
		/* [in][optional] */ VARIANT *language,
		/* [out][retval] */ long *timerID) = 0;
#endif   
  virtual ErrorCode  clearTimeout( 
		/* [in] */ long timerID) = 0;
#if 0  
  virtual ErrorCode  setInterval( 
		/* [in] */ VARIANT *expression,
		/* [in] */ long msec,
		/* [in][optional] */ VARIANT *language,
		/* [out][retval] */ long *timerID) = 0;
#endif   
  virtual ErrorCode clearInterval( 
		/* [in] */ long timerID) = 0;

  virtual ErrorCode alert(StringIn message) = 0;

  virtual ErrorCode confirm(StringIn message,
		/* [out][retval] */ bool *confirmed) = 0;
#if 0  
  virtual ErrorCode prompt(const sysstring& message, const sysstring& defstr,
		/* [out][retval] */ VARIANT *textdata) = 0;
#endif   
  virtual /* [helpstring] */ ErrorCode open(StringIn url, StringIn name, StringIn features,
		/* [in] */ bool replace,
		/* [retval][out] */ IHTMLWindow **pomWindowResult) = 0;
#if 0  
  virtual /* [helpstring] */ ErrorCode showModalDialog(const sysstring& dialog,
		/* [optional][in] */ VARIANT *varArgIn,
		/* [optional][in] */ VARIANT *varOptions,
		/* [out][retval] */ VARIANT *varArgOut) = 0;
#endif   
  virtual /* [helpstring][propget] */ ErrorCode get_innerWidth( 
		/* [retval][out] */ long *pVal) = 0;

  virtual /* [helpstring][propget] */ ErrorCode get_innerHeight( 
		/* [retval][out] */ long *pVal) = 0;

  virtual /* [helpstring] */ ErrorCode captureMouse( 
		/* [in] */ bool bCapture) = 0;

};

interface IHTMLDialog
{
#if 0
  virtual /* [helpstring][id][propget] */ ErrorCode  get_dialogArguments( 
		/* [retval][out] */ VARIANT *pVal) = 0;

  virtual /* [helpstring][id][propput] */ ErrorCode  set_dialogArguments( 
		/* [in] */ VARIANT newVal) = 0;

  virtual /* [helpstring][id][propget] */ ErrorCode  get_returnValue( 
		/* [retval][out] */ VARIANT *pVal) = 0;

  virtual /* [helpstring][id][propput] */ ErrorCode  set_returnValue( 
		/* [in] */ VARIANT newVal) = 0;

  virtual /* [helpstring][id][propget] */ ErrorCode  get_dialogLeft( 
		/* [retval][out] */ VARIANT *pVal) = 0;

  virtual /* [helpstring][id][propput] */ ErrorCode  set_dialogLeft( 
		/* [in] */ VARIANT newVal) = 0;

  virtual /* [helpstring][id][propget] */ ErrorCode  get_dialogTop( 
		/* [retval][out] */ VARIANT *pVal) = 0;

  virtual /* [helpstring][id][propput] */ ErrorCode  set_dialogTop( 
		/* [in] */ VARIANT newVal) = 0;

  virtual /* [helpstring][id][propget] */ ErrorCode  get_dialogWidth( 
		/* [retval][out] */ VARIANT *pVal) = 0;

  virtual /* [helpstring][id][propput] */ ErrorCode  set_dialogWidth( 
		/* [in] */ VARIANT newVal) = 0;

  virtual /* [helpstring][id][propget] */ ErrorCode  get_dialogHeight( 
		/* [retval][out] */ VARIANT *pVal) = 0;

  virtual /* [helpstring][id][propput] */ ErrorCode  set_dialogHeight( 
		/* [in] */ VARIANT newVal) = 0;
#endif
};

interface IMarkupPointer
{
	virtual Document* get_OwningDoc() = 0;
};

interface ISMILElementLayout
{
	virtual int get_width() = 0;
	virtual void set_width(int newVal) = 0;
	virtual int get_height() = 0;
	virtual void set_height(int newVal) = 0;
};

enum ShowBackgroundType
{
	SHOWBACKGROUND_ALWAYS	= 0,
	SHOWBACKGROUND_WHEN_ACTIVE	= 1
};

enum TransitionDirection
{
	TRANSITION_DIRECTION_FORWARD	= 0,
	TRANSITION_DIRECTION_REVERSE	= 1
};

interface ISVGExternalResourcesRequired
{
	virtual ISVGAnimatedBoolean* get_externalResourcesRequired() = 0;
};

interface ISVGPreserveAspectRatio
{
	virtual SVGPreserveAspectRatioAlignType get_align() = 0;
	virtual void set_align(SVGPreserveAspectRatioAlignType newVal) = 0;
	virtual SVGMeetOrSliceType get_meetOrSlice() = 0;
	virtual void set_meetOrSlice(SVGMeetOrSliceType newVal) = 0;
};

interface ISVGAnimatedPreserveAspectRatio
{
	virtual ISVGPreserveAspectRatio* get_baseVal() = 0;
	virtual ISVGPreserveAspectRatio* get_animVal() = 0;
};

interface ISVGAnimatedBoolean
{
	virtual bool get_baseVal() = 0;
	virtual void set_baseVal(bool newVal) = 0;
	virtual bool get_animVal() = 0;
};

interface ISVGAnimatedRect
{
	virtual ISVGRect* get_baseVal() = 0;
	virtual ISVGRect* get_animVal() = 0;
};

interface ISVGAnimatedInteger
{
	virtual int get_baseVal() const = 0;
	virtual void set_baseVal(int newVal) = 0;
	virtual int get_animVal() const = 0;
};

interface ISVGAnimatedEnumeration
{
	virtual int get_baseVal() = 0;
	virtual void set_baseVal(int newVal) = 0;
	virtual int get_animVal() = 0;
};

interface ISVGAnimatedNumber
{
	virtual double get_baseVal() const = 0;
	virtual void set_baseVal(double newVal) = 0;
	virtual double get_animVal() const = 0;
};

interface ISVGAnimatedNumberList
{
	virtual ISVGNumberList* get_baseVal() = 0;
	virtual ISVGNumberList* get_animVal() = 0;
};

interface ISVGLength
{
	virtual String get_valueAsString() = 0;
	virtual void set_valueAsString(StringIn newVal) = 0;
	virtual double get_valueInSpecifiedUnits() = 0;
	virtual void set_valueInSpecifiedUnits(double newVal) = 0;
	virtual double get_value() = 0;
	virtual void set_value(double newVal) = 0;
	virtual SVGLengthType get_unitType() const = 0;
	virtual void convertToSpecifiedUnits(SVGLengthType unitType) = 0;
	virtual void newValueSpecifiedUnits(SVGLengthType unitType, double valueInSpecifiedUnits) = 0;
};

interface ISVGAnimatedLength
{
	virtual ISVGLength* get_baseVal() = 0;
	virtual ISVGLength* get_animVal() = 0;
};

interface ISVGLengthList : public ISVGList
{
};

interface ISVGAnimatedLengthList
{
	virtual ISVGLengthList* get_baseVal() = 0;
	virtual ISVGLengthList* get_animVal() = 0;
};
 
interface ISVGAnimatedPoints
{
	virtual SVGPointList* get_points() = 0;
	virtual SVGPointList* get_animatedPoints() = 0;
};

interface ISVGRenderElement
{
};

interface ISVGFEElement
{
};

interface ISVGFitToViewBox
{
	virtual ISVGAnimatedRect* get_viewBox() = 0;
	virtual ISVGAnimatedPreserveAspectRatio* get_preserveAspectRatio() = 0;
	virtual Attr* get_viewBoxAttr() = 0;
	virtual Attr* get_preserveAspectRatioAttr() = 0;
};

interface ISVGLangSpace
{
	virtual String get_xmllang() = 0;

#if 0
        virtual /* [helpstring][propget] */ ErrorCode get_xmllang( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ ErrorCode set_xmllang( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ ErrorCode get_xmlspace( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ ErrorCode set_xmlspace( 
            /* [in] */ BSTR newVal) = 0;
#endif
};
    
interface ISVGTests
{
	virtual SVGStringList* get_requiredFeatures() = 0;
#if 0
  virtual /* [helpstring][propget] */ ErrorCode get_requiredExtensions( 
      /* [retval][out] */ ISVGStringList **pVal) = 0;
  
  virtual /* [helpstring][propget] */ ErrorCode get_systemLanguage( 
      /* [retval][out] */ ISVGStringList **pVal) = 0;
#endif        
  virtual bool hasExtension(StringIn extension) = 0;
#if 0  
  virtual /* [helpstring][propget] */ ErrorCode get_systemBitrate( 
      /* [retval][out] */ long *pVal) = 0;
  
  virtual /* [helpstring][propput] */ ErrorCode set_systemBitrate( 
      /* [in] */ long newVal) = 0;
  
  virtual /* [helpstring][propget] */ ErrorCode get_systemCaptions( 
      /* [retval][out] */ bool *pVal) = 0;
  
  virtual /* [helpstring][propput] */ ErrorCode set_systemCaptions( 
      /* [in] */ bool newVal) = 0;
  
  virtual /* [helpstring][propget] */ ErrorCode get_systemAudioDesc( 
      /* [retval][out] */ bool *pVal) = 0;
  
  virtual /* [helpstring][propput] */ ErrorCode set_systemAudioDesc( 
      /* [in] */ bool newVal) = 0;
  
  virtual /* [helpstring][propget] */ ErrorCode get_systemOverdubOrSubtitle( 
      /* [retval][out] */ BSTR *pVal) = 0;
  
  virtual /* [helpstring][propput] */ ErrorCode set_systemOverdubOrSubtitle( 
      /* [in] */ BSTR newVal) = 0;
#endif
};

interface ISVGCoordinate
{
	virtual SVGLength* get_x() = 0;
	virtual SVGLength* get_y() = 0;
};

enum SVGAnimateMotionRotateType
{
	SVG_ROTATE_UNKNOWN	= 0,
	SVG_ROTATE_AUTO	= 1,
	SVG_ROTATE_AUTO_REVERSE	= 2,
	SVG_ROTATE_ANGLE	= 3
};

interface ISVGURIReference
{
	virtual ISVGAnimatedString* get_href() = 0;
};

enum SVGPathSegType
{
	PATHSEG_UNKNOWN	= 0,
	PATHSEG_CLOSEPATH	= 1,
	PATHSEG_MOVETO_ABS	= 2,
	PATHSEG_MOVETO_REL	= 3,
	PATHSEG_LINETO_ABS	= 4,
	PATHSEG_LINETO_REL	= 5,
	PATHSEG_CURVETO_CUBIC_ABS	= 6,
	PATHSEG_CURVETO_CUBIC_REL	= 7,
	PATHSEG_CURVETO_QUADRATIC_ABS	= 8,
	PATHSEG_CURVETO_QUADRATIC_REL	= 9,
	PATHSEG_ARC_ABS	= 10,
	PATHSEG_ARC_REL	= 11,
	PATHSEG_LINETO_HORIZONTAL_ABS	= 12,
	PATHSEG_LINETO_HORIZONTAL_REL	= 13,
	PATHSEG_LINETO_VERTICAL_ABS	= 14,
	PATHSEG_LINETO_VERTICAL_REL	= 15,
	PATHSEG_CURVETO_CUBIC_SMOOTH_ABS	= 16,
	PATHSEG_CURVETO_CUBIC_SMOOTH_REL	= 17,
	PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS	= 18,
	PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL	= 19
};

#if 0
    class
    ISVGPathSegListValue
    {
    public:
        virtual /* [helpstring][propget] */ ErrorCode  get_pathSegList( 
            /* [retval][out] */ ISVGPathSegList **pVal) = 0;
        
        virtual /* [helpstring][propget] */ ErrorCode  get_normalizedPathSegList( 
            /* [retval][out] */ ISVGPathSegList **pVal) = 0;
    };
#endif

#if 0
    class ISVGPathSegList : public ISVGList
    {
    public:
        virtual /* [helpstring] */ ErrorCode  initialize( 
            /* [in] */ ILSVGPathSeg *newItem,
            /* [retval][out] */ ILSVGPathSeg **ppResult) = 0;
        
        virtual /* [helpstring] */ ErrorCode  getItem( 
            /* [in] */ long index,
            /* [retval][out] */ ILSVGPathSeg **ppResult) = 0;
        
        virtual /* [helpstring] */ ErrorCode  insertItemBefore( 
            /* [in] */ ILSVGPathSeg *newItem,
            /* [in] */ long index,
            /* [retval][out] */ ILSVGPathSeg **ppResult) = 0;
        
        virtual /* [helpstring] */ ErrorCode  replaceItem( 
            /* [in] */ ILSVGPathSeg *newItem,
            /* [in] */ long index,
            /* [retval][out] */ ILSVGPathSeg **ppResult) = 0;
        
        virtual /* [helpstring] */ ErrorCode  removeItem( 
            /* [in] */ long index,
            /* [retval][out] */ ILSVGPathSeg **ppResult) = 0;
        
        virtual /* [helpstring] */ ErrorCode  appendItem( 
            /* [in] */ ILSVGPathSeg *newItem,
            /* [retval][out] */ ILSVGPathSeg **ppResult) = 0;
        
        virtual /* [helpstring] */ ErrorCode  AddEllipse( 
            /* [in] */ double cx,
            /* [in] */ double cy,
            /* [in] */ double rx,
            /* [in] */ double ry) = 0;
        
        virtual /* [helpstring] */ ErrorCode  AddRect( 
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double width,
            /* [in] */ double height) = 0;
        
        virtual /* [helpstring] */ ErrorCode  AddRoundRect( 
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double width,
            /* [in] */ double height,
            /* [in] */ double rx,
            /* [in] */ double ry) = 0;
        
        virtual /* [helpstring] */ ErrorCode  AddLine( 
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2) = 0;
        
        virtual /* [helpstring] */ ErrorCode  AddMoveTo( 
            /* [in] */ double x,
            /* [in] */ double y) = 0;
        
        virtual /* [helpstring] */ ErrorCode  AddLineTo( 
            /* [in] */ double x,
            /* [in] */ double y) = 0;
        
        virtual /* [helpstring] */ ErrorCode  AddCloseFigure( void) = 0;
        
        virtual /* [helpstring] */ ErrorCode  LockUpdate( void) = 0;
        
        virtual /* [helpstring] */ ErrorCode  UnlockUpdate( void) = 0;
        
        virtual /* [helpstring] */ ErrorCode  matrixTransform( 
            LSVG::SVGMatrix *matrix) = 0;
        
        virtual /* [helpstring] */ ErrorCode  Offset( 
            /* [in] */ double dx,
            /* [in] */ double dy) = 0;
    };
#endif        

	interface ISVGAnimatedPathData
   {
#if 0
        virtual /* [helpstring][propget] */ ErrorCode  get_pathSegList( 
            /* [retval][out] */ ILSVGPathSegList **pVal) = 0;
        
        virtual /* [helpstring][propget] */ ErrorCode  get_normalizedPathSegList( 
            /* [retval][out] */ ILSVGPathSegList **pVal) = 0;
        
        virtual /* [helpstring][propget] */ ErrorCode  get_animatedPathSegList( 
            /* [retval][out] */ ILSVGPathSegList **pVal) = 0;
        
        virtual /* [helpstring][propget] */ ErrorCode  get_animatedNormalizedPathSegList( 
            /* [retval][out] */ ILSVGPathSegList **pVal) = 0;
#endif
        
    };
    
enum SVGMarkerUnitType
{
	SVG_MARKERUNITS_UNKNOWN	= 0,
	SVG_MARKERUNITS_USERSPACEONUSE	= 1,
	SVG_MARKERUNITS_STROKEWIDTH	= 2
};

enum SVGMarkerOrientationType
{
	SVG_MARKER_ORIENT_UNKNOWN	= 0,
	SVG_MARKER_ORIENT_AUTO	= 1,
	SVG_MARKER_ORIENT_ANGLE	= 2
};

interface ISVGGlyphAttributes
{
	virtual SVGPathSegList* get_pathSegList() = 0;
	virtual SVGPathSegList* get_normalizedPathSegList() = 0;
};

interface ISVGPathSegListListener
{
	virtual void OnPathSegListChange(SVGPathSegList* pSegList) = 0;
};

enum SVGSpreadMethodType
{
	SVG_SPREADMETHOD_UNKNOWN	= 0,
	SVG_SPREADMETHOD_PAD	= 1,
	SVG_SPREADMETHOD_REFLECT	= 2,
	SVG_SPREADMETHOD_REPEAT	= 3
};

interface ISVGStringList : public ISVGList
{
#if 0
        virtual /* [helpstring][id] */ ErrorCode  initialize( 
            /* [in] */ BSTR newItem,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode  getItem( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode  insertItemBefore( 
            /* [in] */ BSTR newItem,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode  replaceItem( 
            /* [in] */ BSTR newItem,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode  removeItem( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode  appendItem( 
            /* [in] */ BSTR newItem,
            /* [retval][out] */ BSTR *pVal) = 0;
#endif   
};

interface IASComplexTypeDeclaration : public IASDataTypeDeclaration
{
	virtual IASNamedObjectMap* get_ASAttributeDecls() = 0;
	virtual /* [helpstring] */ ErrorCode  addASAttributeDecl( 
		/* [in] */ IASAttributeDeclaration *attributeDecl) = 0;

	virtual /* [helpstring] */ ErrorCode  removeASAttributeDecl( 
		/* [in] */ IASAttributeDeclaration *attributeDecl,
		/* [retval][out] */ IASAttributeDeclaration **pVal) = 0;
};

interface IASInclude : public IASObject
{
#if 0
virtual /* [helpstring][propget] */ ErrorCode  get_location( 
/* [retval][out] */ BSTR *pVal) = 0;

virtual /* [helpstring][propput] */ ErrorCode  set_location( 
/* [in] */ BSTR newVal) = 0;

virtual /* [helpstring][propget] */ ErrorCode  get_abslocation( 
/* [retval][out] */ BSTR *pVal) = 0;

virtual /* [helpstring][propget] */ ErrorCode  get_asModel( 
/* [retval][out] */ IASModel **pVal) = 0;
#endif   
};

interface IASXMLSchemaModel : public IASModel
{
virtual /* [helpstring][propget] */ ErrorCode  get_xmlDocument( 
   /* [retval][out] */ Document **pVal) = 0;

virtual /* [helpstring][propput] */ ErrorCode  set_xmlDocument( 
   /* [in] */ Document *newVal) = 0;

};

interface IASXDRSchemaModel : public IASModel
{
};

}
}

#include "LengthValue.h"
#include "ColorValue.h"
#include "LengthValue.h"
#include "LongValue.h"
#include "SMILFitValue.h"
#include "SVGAnimatedEnumerationT.h"
#include "MediaSource.h"
#include "SVGStringList.h"
#include "SVGTestsImpl.h"
#include "SVGStylableImpl.h"
#include "SVGPathSeg.h"
#include "SVGPathSegList.h"

#include "HTMLDocument.h"
#include "HTMLElement.h"
#include "HTMLGenericElement.h"
#include "HTMLBodyElement.h"
#include "HTMLAnchorElement.h"
#include "HTMLParagraphElement.h"
#include "HTMLLinkElement.h"
#include "HTMLStyleElement.h"
#include "HTMLImageElement.h"
#include "HTMLFrameElement.h"
#include "HTMLFrameSetElement.h"

#include "PHTMLElement.h"
#include "PHTMLImageElement.h"
#include "PHTMLFrameElement.h"
#include "PHTMLFrameSetElement.h"

#include "SMILElementLayoutImpl.h"
#include "SMILElement.h"
#include "SMILAnimationElement.h"
#include "SMILRootLayoutElement.h"
#include "SMILTopLayoutElement.h"
//#include "SMILLayoutElement.h"
#include "SMILRegionElement.h"
#include "SMILAnimateElement.h"
#include "SMILTransitionElement.h"
#include "SMILParElement.h"
#include "SMILSeqElement.h"

// SVG
//#include "SVGElementImpl.h"
#include "SVGStylableImpl.h"
//#include "SVGTestsImpl.h"
#include "SVGLength.h"
#include "StringValue.h"
#include "LongValue.h"
#include "SVGAnimatedString.h"
#include "SVGAnimatedEnumerationT.h"
#include "SVGEnumerationUnitTypeValue.h"
#include "SVGOptionalTwoNumbersValue.h"
#include "SVGNumberOrPercentageValue.h"
#include "SVGPathSegList.h"
#include "SVGPathSegListValue.h"

namespace System
{
namespace Web
{

HTMLEXT void CalculateScaleXY(const gm::matrix3d& matrix, double* scaleX, double* scaleY);
HTMLEXT void CalculateScaleXY(const gm::Matrix3d* matrix, double* scaleX, double* scaleY);

class HTMLEXT CPreferences
{
public:
	CTOR CPreferences();
	~CPreferences();

	String m_systemLanguage;
	uint32 m_systemAudioDesc;
	uint32 m_systemCaptions;
	uint32 m_systemBitrate;
	uint32 m_systemOverdubOrSubtitle;	// 0=overdub,1=subtitle
	uint32 m_bKnownOS;
	uint32 m_bKnownCPU;

	ErrorCode ForceReload();
	ErrorCode LoadIfNotLoaded();
	ErrorCode Save();

protected:

	bool m_bLoaded;
};

extern HTMLEXT CPreferences g_preferences;

}	// Web
}	// System

#endif
