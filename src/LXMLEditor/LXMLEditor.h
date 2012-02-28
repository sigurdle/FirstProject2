#ifndef __LXMLEditor_h__
#define __LXMLEditor_h__

#ifndef LXMLEDITEXT
#define LXMLEDITEXT DECLSPEC_DLLIMPORT
#endif

#include "../LXML/LXML.h"
#include "../LSVG/LSVG.h"
//#include "../LX3D/LX3D.h"

class IEFrame
{
//	virtual ErrorCode __stdcall GetMDIFrame(ILXUIMDIFrameElement* *pVal) = 0;
};

namespace System
{
namespace LXmlEdit
{

// Forward Declarations

class CLXMLEditorApp;
class CEXMLDocument;
class CEXMLViewGroup;
class Element;
class CESVGElementImpl;
class CESVGPathElement;
class IWEUndoManager;
class IESelectedElement;
class ILXMLEditorApp;
class ISVGToolFactory;
class ISVGTool;
class ISVGView;

class SVGMouse
{
	long nFlags;
	long ptx;
	long pty;
	double wptx;
	double wpty;
};

class _SVGHitData
{
	long hit;
	long anchor;
	long segment;
	long ctl;
	double t;
	long selectedKeyFrameIndex;
	Element *element;
	IESelectedElement *selectedElement;
};
   
class ILXMLEditorPluginClass : public System::Object
    {
    public:
        virtual ILXMLEditorApp * GetApp() = 0;
        virtual System::StringW* GetName() = 0;
        
    };
    
    
    class
ILXMLEditorPlugin : public System::Object
    {
    public:
        virtual ILXMLEditorPluginClass* GetSite() = 0;
        
        virtual /* [helpstring] */ ErrorCode SetSite( 
            /* [in] */ ILXMLEditorPluginClass *pSite) = 0;
        
    };
    
    
    class
ILXMLEditorApp : public System::Object
    {
    public:
        virtual /* [helpstring][id] */ ErrorCode OpenDocument( 
			  /* [in] */ System::StringW* pathName,
            /* [retval][out] */ System::Object **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ ErrorCode get_tabSize( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode GetActiveTool( 
            /* [in] */ bool bSelection,
            /* [retval][out] */ ISVGTool **pVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode SetActiveToolByID( 
            /* [in] */ long toolID) = 0;
        
        virtual /* [helpstring] */ ErrorCode AddTool( 
            /* [in] */ ILXMLEditorPluginClass *self,
            /* [in] */ ISVGToolFactory *factory,
            /* [in] */ System::Object *pToolDlg,
            /* [in] */ long toolId,
            /* [in] */ System::StringW* name,
            /* [in] */ System::StringW* imageFilename) = 0;
        
        virtual /* [helpstring] */ ErrorCode RemoveTool( 
            /* [in] */ ILXMLEditorPluginClass *self,
            /* [in] */ long toolId) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetToolID( 
            /* [in] */ ISVGTool *tool,
            /* [retval][out] */ long *pVal) = 0;
        
    };
    

    
    class
    IESVGSimpleShapeElement
    {
    public:
        virtual /* [helpstring] */ ErrorCode DrawPathSegList( 
			  /* [in] */ Web::SVGPathElement *pathElement,
			  /* [in] */ Web::SVGPathSegList *seglist) = 0;
        
    };
    

	 class CSubPath;
    
    class IESVGPath : public System::Object
    {
    public:
        virtual /* [helpstring] */ ErrorCode GetSubPathCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetSubPath( 
            /* [in] */ long index,
            /* [retval][out] */ CSubPath **pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetPathSegList( 
		  /* [retval][out] */ Web::SVGPathSegList **pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetSubPathFromIndex( 
            /* [in] */ long index,
            /* [out] */ long *pindex,
            /* [retval][out] */ CSubPath **psubpath) = 0;
        
        virtual /* [helpstring] */ ErrorCode AppendPath( 
            /* [in] */ CSubPath *path) = 0;
        
        virtual /* [helpstring] */ ErrorCode InsertSubPathBefore( 
            /* [in] */ CSubPath *path,
            /* [in] */ long index) = 0;
        
        virtual /* [helpstring] */ ErrorCode getPointNearPath( 
		  /* [in] */ Web::SVGMatrix *matrix,
            /* [in] */ double mousex,
            /* [in] */ double mousey,
            /* [in] */ double tolerance,
            /* [out] */ long *segindex,
            /* [out] */ double *pt,
            /* [retval][out] */ bool *pVal) = 0;
        
    };
    

    
    class
    IESelectedUnknown
    {
    public:
        virtual /* [helpstring][propget] */ ErrorCode get_selectedType( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
    
   class
    IESelectedRule : public IESelectedUnknown
    {
    public:
        virtual /* [helpstring][propget] */ ErrorCode get_rule( 
			  /* [retval][out] */ Web::CSSRule **pVal) = 0;
        
    };
    
    
    class
    IESelectedElement : public IESelectedUnknown
    {
    public:
        virtual /* [helpstring][propget] */ ErrorCode get_eElement( 
			  /* [retval][out] */ Element **pVal) = 0;
        
        virtual /* [helpstring][propput] */ ErrorCode put_eElement( 
		  /* [in] */ Element *newVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode HitTest( 
            /* [in] */ ISVGView *view,
            /* [in] */ Web::SVGSVGElement *svgsvgElement,
            /* [in] */ Web::SVGMatrix *ctm,
            /* [in] */ double ptx,
            /* [in] */ double pty,
            /* [in] */ long tool,
            /* [in] */ _SVGHitData *hit) = 0;
        
        virtual void Move( 
            /* [in] */ ISVGView *view,
            /* [in] */ double dx,
            /* [in] */ double dy) = 0;
        
        virtual Web::SVGMatrix* GetScreenCTM( 
            /* [in] */ ISVGView *view) = 0;
        
        virtual Web::ISVGRect* GetRBBox( 
            /* [in] */ ISVGView *view) = 0;
        
        virtual Web::ISVGRect* GetScreenBBox( 
            /* [in] */ ISVGView *view) = 0;
        
        virtual ErrorCode DeleteSelection( void) = 0;
        
    };
    
    
    class
    IESelectedAnimationElement : public IESelectedElement
    {
    public:
        virtual /* [helpstring] */ ErrorCode GetSelectedKeyTimesCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetKeyTimeSelected( 
            /* [in] */ long index,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode IsKeyTimeSelected( 
            /* [in] */ long index,
            /* [retval][out] */ bool *pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode SelectKeyTime( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpstring] */ ErrorCode DeselectKeyTime( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpstring] */ ErrorCode DeselectAllKeyTimes( void) = 0;
        
    };
    
    
    class
IESelectedSVGPoints : public System::Object
    {
    public:
        virtual bool IsAnchorSelected( 
            /* [in] */ uint index) = 0;
        
        virtual /* [helpstring] */ ErrorCode SelectAnchor( 
            /* [in] */ uint index) = 0;
        
        virtual /* [helpstring] */ ErrorCode DeselectAnchor( 
            /* [in] */ uint index) = 0;
        
        virtual /* [helpstring] */ ErrorCode IsSegmentSelected( 
            /* [in] */ uint index,
            /* [retval][out] */ bool *pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode SelectSegment( 
            /* [in] */ uint index) = 0;
        
        virtual /* [helpstring] */ ErrorCode DeselectSegment( 
            /* [in] */ uint index) = 0;
        
        virtual /* [helpstring] */ void DeselectAllPoints() = 0;
        
        virtual /* [helpstring] */ ErrorCode DeleteSelection() = 0;
        
    };
    
    
    class
    IESelectedSVGPolyElement : public IESelectedElement
    {
    public:
    };
    
    
    class
    IESelectedSVGPathElement : public IESelectedElement
    {
    public:
    };
    
    
    class ITextBookmark
    {
    public:
        virtual long get_offset() = 0;
        virtual uint get_length() = 0;
    };
    
    
    class
ITextBookmarkList : public System::Object
    {
    public:
        virtual /* [helpstring][propget] */ ErrorCode get_length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode item( 
            /* [in] */ long index,
            /* [retval][out] */ ITextBookmark **pVal) = 0;
        
    };
    

   
    class
ISVGView : public System::Object
    {
    public:
        virtual /* [helpstring] */ ErrorCode HitTest( 
            /* [in] */ Element *element,
            /* [in] */ double ptx,
            /* [in] */ double pty,
            /* [in] */ long options,
            /* [out][in] */ _SVGHitData *hitdata) = 0;
        
        virtual CEXMLViewGroup* GetViewGroup() = 0;
        
        virtual Web::CLHTMLWindow* GetHTMLWindow() = 0;
        
        virtual Element* GetEElement() = 0;
        
        virtual /* [helpstring] */ ErrorCode GetSVGSVGElement( 
		  /* [retval][out] */ Web::SVGSVGElement **pVal) = 0;
        
        virtual Web::SVGMatrix * GetViewMatrix() = 0;
        
    };
    

    
    class
    ISVGToolFactory
    {
    public:
        virtual /* [helpstring] */ ErrorCode FindTool( 
            /* [in] */ long toolId,
            /* [out] */ System::Object **dlg,
            /* [retval][out] */ ISVGTool **pVal) = 0;
        
    };
    
    
    class
    ISVGTool 
    {
    public:
        virtual /* [helpstring] */ ErrorCode OnButtonDown( 
            /* [in] */ ISVGView *view,
            /* [in] */ SVGMouse *mouse,
            /* [retval][out] */ long *pdragging) = 0;
        
        virtual /* [helpstring] */ ErrorCode OnButtonUp( 
            /* [in] */ ISVGView *view,
            /* [in] */ SVGMouse *mouse) = 0;
        
        virtual /* [helpstring] */ ErrorCode OnMouseMove( 
            /* [in] */ ISVGView *view,
            /* [in] */ SVGMouse *mouse) = 0;
        
        virtual /* [helpstring] */ ErrorCode OnSetCursor( 
            /* [in] */ ISVGView *view,
            /* [in] */ SVGMouse *mouse) = 0;
        
        virtual /* [helpstring] */ ErrorCode Paint( 
            /* [in] */ ISVGView *view,
            /* [in] */ long dragging,
            UI::Graphics* pGraphics) = 0;
        
        virtual /* [helpstring] */ ErrorCode OnActivate( 
            /* [in] */ ILXMLEditorApp *app) = 0;
        
        virtual /* [helpstring] */ ErrorCode OnDeactivate( 
            /* [in] */ ILXMLEditorApp *app) = 0;
        
        virtual /* [helpstring] */ ErrorCode Options( 
			UI::Control* hParent) = 0;
        
    };
    
    
    class
IHTMLFramesDesignView : public System::Object
    {
    public:
        virtual /* [helpstring][id][propget] */ ErrorCode get_document( 
            /* [retval][out] */ CEXMLDocument **pVal) = 0;
        
    };
    
    
    
    class
IEColorSite //: public System::Object
    {
    public:
        virtual /* [helpstring] */ ErrorCode SetRGBColorValue( 
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue) = 0;
        
    };
    

    
    class IEColorPicker
    {
    public:
        virtual /* [helpstring] */ ErrorCode GetSite( 
            /* [retval][out] */ IEColorSite **pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode SetSite( 
            /* [in] */ IEColorSite *newVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode SetRGBColorValue( 
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue) = 0;
        
    };
    

    
    
   
    class
ISmilRegionsView : public System::Object
    {
    public:
        virtual /* [helpstring][id][propget] */ ErrorCode get_document( 
            /* [retval][out] */ CEXMLDocument **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ ErrorCode put_document( 
            /* [in] */ CEXMLDocument *newVal) = 0;
        
    };
    
    class
IXMLSchemaView : public System::Object
    {
    public:
        virtual /* [helpstring][id][propget] */ ErrorCode get_document( 
            /* [retval][out] */ CEXMLDocument **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ ErrorCode put_document( 
            /* [in] */ CEXMLDocument *newVal) = 0;
        
    };
    
#if 0    
    class
IEditFilterGraph : public System::Object
    {
    public:
        virtual /* [helpstring][id][propget] */ ErrorCode get_activeElement( 
            /* [retval][out] */ Element **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ ErrorCode put_activeElement( 
            /* [in] */ Element *newVal) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode DeleteSelectedPrimitive( void) = 0;
        
    };
    
    class
    ISVGGradientEditCtl : public _ObjectImpl
    {
    public:
        virtual /* [id][propput] */ ErrorCode put_BackColor( 
            /* [in] */ LDraw::Color clr) = 0;
        
        virtual /* [id][propget] */ ErrorCode get_BackColor( 
            /* [retval][out] */ LDraw::Color *pclr) = 0;
        
        virtual /* [id][propput] */ ErrorCode put_Enabled( 
            /* [in] */ bool vbool) = 0;
        
        virtual /* [id][propget] */ ErrorCode get_Enabled( 
            /* [retval][out] */ bool *pbool) = 0;
        
        virtual /* [id][propget] */ ErrorCode get_Window( 
            /* [retval][out] */ long *phwnd) = 0;
        
        virtual /* [helpstring][id] */ ErrorCode SetSVGElement( 
            /* [in] */ _ObjectImpl *element) = 0;
        
        virtual /* [helpstring][id][propget] */ ErrorCode get_canEditStops( 
            /* [retval][out] */ bool *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ ErrorCode put_canEditStops( 
            /* [in] */ bool newVal) = 0;
        
    };
#endif    
    class
    IECSSSelection
    {
    public:
        virtual /* [helpstring] */ ErrorCode GetCurrentSelectionCSSStyle( 
			  Web::CSSStyleDeclaration **pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode ApplyCurrentSelectionCSSStyle( void) = 0;
        
    };
    

    
}	// LXmlEdit
}

#endif


