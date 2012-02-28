#ifndef __LXImageEditor_h__
#define __LXImageEditor_h__

#ifdef __LERSTAD__
#import "../../Win32/bin/Debug/LXUI.typeinfo"
#else
#include "LXUI/LXUI.h"
#endif

#ifndef ImageEditorExt
#define ImageEditorExt DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace ImageEdit
{

class IImageLayerGroup;

/*   
class
ILXImageApp
{
public:
};
*/  


class	IImageColorDlg
{
public:
};



class	IImageDocument
{
public:
	virtual IImageLayerGroup * GetImageLayerGroup() = 0;
	
};


class	IImageView
{
public:
	virtual /* [helpstring] */ ErrorCode GetDocument( 
		/* [retval][out] */ IImageDocument **pVal) = 0;
		
};


class	IBitmap
{
public:
};

class IImageObject
{
public:
};
     
enum ImageLayerType
{
	LAYERTYPE_UNKNOWN	= 0,
	LAYERTYPE_GROUP	= 1,
	LAYERTYPE_BITMAP	= 2
};

class ImageLayerUnknown : public System::Object
{
public:
	virtual ImageLayerType GetLayerType() = 0;
	virtual System::StringW* GetName() = 0;
};

class CGroupImageObject;    

#if 0
    class
    IImageLayerBitmap : public IImageLayerUnknown
    {
    public:
        virtual /* [helpstring] */ ErrorCode GetGroupObject( 
            /* [retval][out] */ CGroupImageObject **pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetMaskGroupObject( 
            /* [retval][out] */ CGroupImageObject **pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetClipPathGroupObject( 
            /* [retval][out] */ CGroupImageObject **pVal) = 0;
        
    };
#endif

class CImageLayerGroup;
#if 0
    MIDL_INTERFACE("A9DACCBD-9E68-4098-A7C9-AC2A35B5994C")
    IImageLayerGroup : public IImageLayerUnknown
    {
    public:
        virtual /* [helpstring] */ ErrorCode GetSubLayersCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ ErrorCode GetSubLayer( 
            /* [in] */ long index,
            /* [retval][out] */ IImageLayerUnknown **pVal) = 0;
        
    };
#endif

//bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

typedef LDraw::BitmapData ImageDef;

void GetAlphaBounds(ImageDef* image, LDraw::RectI* lprect);

typedef struct tagPFILTERRECORD
{
//	LPPLUGINRECORD	pluginRecord;

	uint32	flags;
	uint32	modified;

	uint16	quality;
	uint16	depth;

	int	sourceWidth;	// Original source width/height, unaffected by sampling
	int	sourceHeight;

	LDraw::RectI uRect;	// Invalid rect, filter this
	LDraw::RectI aRect;	// Alpha bounds
	LDraw::RectI sRect;	// Selection bounds

	uint16 bTransferTo;	// 0 = Image, 1 = Selection
	uint8 bSet;
	uint8 bPaintMethod;

	/*
	WORD				planes;
	WORD				imode;
	*/

	double x_sampling;
	double y_sampling;

	int x, y, z;
	int dx, dy, dz;
	int angle;
	short strength;
	uint8 reserved4;
	uint8 bHasSelectionYet;

	void* global_data;
	void* frame_data;
	uint32	reserved5[2];
	ULONG_PTR	userDat;

//	MMPluginRef	thisPlugin;

	/*
	long		toolID;
	DWORD		reserved6[7];
	*/

	int	inputWidth;	// same as inImage[n]->width
	int	inputHeight;

/* Set these fields in FilterBegin to indicate
that the output image will be larger than the input image.
You should set newwidth and newheight to the size to which you
want the output buffer to be allocated. Set origin to the
place that the point (0,0) in the input should map to in the
new larger output. If you created a 5-pixel drop shadow up
and left, you might set origin to (5, 5).
*/

// Set these in FrameSetup
	int out_newwidth;
	int out_newheight;
	int out_x_origin;
	int out_y_origin;

// In values (read-only)
	int in_output_origin_x;
	int in_output_origin_y;

// origin of original source in input buffer
	int in_pre_effect_source_origin_x;
	int in_pre_effect_source_origin_y;

	/*
	long	totalFrames;
	long	currentFrame;	// Absolute composition frame
	long currentLayerFrame;
	long layerAbsStartFrame;
	long layerStartFrame;

	long	frameRate;

	LONG	startSample;
	LONG	numSamples;
	LPBYTE	waveData;
	long	samplesPerSec;
	BYTE	wBitsPerSample;
	BYTE	nChannels;
	WORD	reserved7;
	long	totalSamples;

	long layerStartSample;
	long layerDurationSamples;
	*/

	ImageDef*	inDepth;
	ImageDef*	outDepth;

	ImageDef*	bgImage;
	ImageDef*	origImage;
	ImageDef*	inImageSel;
	ImageDef*	inImage;
	ImageDef*	outImage;
	ImageDef*	brushImage;
	short			boffset_x;
	short			boffset_y;

//	MMBasicSuite*		basic;
	/*

	ImageDef* inPinImage[4];	// TODO, must be possible with unlimited inputs

	BOOL		(MMAPI *InitQTML)	();
	long		(MMAPI* AddTool)	(MMPluginRef plugin, long id, LPCTSTR name, HINSTANCE hInst, DWORD bmID);
	BOOL		(MMAPI* Abort)		(tagPFILTERRECORD*);

	int numSubPoints;
	int* subPoints;
	int	numPoints;
	CDblPoint* pointData;
	*/
}
PFILTERRECORD, *LPPFILTERRECORD;

class IPaintMethod
{
public:
	virtual LONG FilterRect(LPPFILTERRECORD r) = 0;
};

class CImageView;

class IImageTool
{
public:
	virtual ErrorCode OnLButtonDown(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags) = 0;
	virtual ErrorCode OnLButtonUp(CImageView* pView, LDraw::PointD point, UINT nFlags) = 0;
	virtual ErrorCode OnMouseMove(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags) = 0;
};

#define IDS_PROJNAME                    100
#define IDR_LXIMAGEAPP                  201
#define IDR_MAINFRAME                   210
#define IDC_COLOR_CHANNELSLIDER0        270
#define IDC_COLOR_CHANNELSLIDER1        271
#define IDC_COLOR_CHANNELSLIDER2        272
#define IDC_COMBO1                      305
#define IDC_SWATCH_CHANNELVALUE0        316
#define IDC_SWATCH_CHANNELVALUE1        317
#define IDC_SWATCH_CHANNELVALUE2        318
#define IDC_POSTERIZE_LEVEL             335
#define IDC_LAYER_NAME                  336
#define IDC_BRUSH_SIZE                  337
#define IDC_FEATHER_RADIUS              338
#define IDC_EXPAND_RADIUS               339
#define IDC_CONTRACT_RADIUS             340
#define IDC_DROPSHADOW_ANGLE            341
#define IDC_DROPSHADOW_DISTANCE         342
#define IDC_DROPSHADOW_COLOR            343
#define IDC_DROPSHADOW_SIZE             344
#define IDR_IMAGEVIEW                   348
#define IDD_IMAGECOLORDLG               351
#define IDR_IMAGEDOCUMENT               351
#define IDR_IMAGETOOLS                  352
#define IDR_IMAGECOLORDLG               353
#define IDD_BRUSHTIPSHAPEDLG            353
#define IDD_NEWLAYERDLG                 354
#define IDD_ADJUSTMENTPOSTERIZEDLG      355
#define IDD_FEATHERSELECTIONDLG         356
#define IDD_EXPANDSELECTIONDLG          357
#define IDD_CONTRACTSELECTIONDLG        358
#define IDD_DROPSHADOWDLG               359
#define ID_FILE_CUSTOMIZE               32774
#define ID_VIEW_ZOOMIN                  32776
#define ID_VIEW_ZOOMOUT                 32777
#define ID_FILE_NEW_NEWSITEM            32934
#define ID_FILE_OPENURL                 32936
#define ID_EDIT_OPTIONS                 32949
#define ID_COLOR_INVERT                 33060
#define ID_COLOR_COMPLEMENT             33061
#define ID_LAYER_NEWLAYERGROUP          33096
#define ID_LAYER_DEPTH_ADD              33097
#define ID_LAYER_DEPTH_CLEAR            33098
#define ID_IMAGETOOL_PAINTBRUSH         33099
#define ID_IMAGETOOL_ELLIPSE            33100
#define ID_IMAGETOOL_SELECT             33103
#define ID_LAYER_LAYERMASK_REVEALALL    33106
#define ID_LAYER_LAYERMASK_ENABLE       33107
#define ID_LAYER_LAYERMASK_HIDEALL      33108
#define ID_LAYER_NEWADJUSTMENTLAYER_POSTERIZE 33109
#define ID_IMAGETOOL_RECTANGULARMARQUEE 33110
#define ID_LAYER_NEW_LAYERVIACOPY       33112
#define ID_LAYER_NEW_LAYERVIACUT        33113
#define ID_IMAGETOOL_ELLIPTICALMARQUEE  33114
#define ID_SELECT_ALL                   33116
#define ID_SELECT_DESELECT              33117
#define ID_IMAGETOOL_MAGICWAND          33118
#define ID_SELECT_INVERSE               33120
#define ID_SELECT_FEATHER               33121
#define ID_SELECT_MODIFY_EXPAND         33122
#define ID_SELECT_MODIFY_CONTRACT       33123
#define ID_LAYER_LAYERSTYLE_DROPSHADOW  33124
#define ID_FILE_NEW                     0xE100
#define ID_FILE_OPEN                    0xE101
#define ID_APP_ABOUT                    0xE140
#define ID_APP_EXIT                     0xE141

}
}

#include "ImageApp.h"
#include "ImageView.h"
#include "ImageDocument.h"
#include "ImageLayerBitmap.h"
#include "ImageLayerGroup.h"

#endif
