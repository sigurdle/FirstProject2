/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 07 14:21:52 2003
 */
/* Compiler settings for C:\MMStudio\Extras\PageDesigner\PageDesigner.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __PageDesigner_h__
#define __PageDesigner_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPDUnknown_FWD_DEFINED__
#define __IPDUnknown_FWD_DEFINED__
typedef interface IPDUnknown IPDUnknown;
#endif 	/* __IPDUnknown_FWD_DEFINED__ */


#ifndef __IPDObjectUnknown_FWD_DEFINED__
#define __IPDObjectUnknown_FWD_DEFINED__
typedef interface IPDObjectUnknown IPDObjectUnknown;
#endif 	/* __IPDObjectUnknown_FWD_DEFINED__ */


#ifndef __IPageDesignerFrame_FWD_DEFINED__
#define __IPageDesignerFrame_FWD_DEFINED__
typedef interface IPageDesignerFrame IPageDesignerFrame;
#endif 	/* __IPageDesignerFrame_FWD_DEFINED__ */


#ifndef __IPDDocumentView_FWD_DEFINED__
#define __IPDDocumentView_FWD_DEFINED__
typedef interface IPDDocumentView IPDDocumentView;
#endif 	/* __IPDDocumentView_FWD_DEFINED__ */


#ifndef __IPDLayer_FWD_DEFINED__
#define __IPDLayer_FWD_DEFINED__
typedef interface IPDLayer IPDLayer;
#endif 	/* __IPDLayer_FWD_DEFINED__ */


#ifndef __IPDObject_FWD_DEFINED__
#define __IPDObject_FWD_DEFINED__
typedef interface IPDObject IPDObject;
#endif 	/* __IPDObject_FWD_DEFINED__ */


#ifndef __IPDSpread_FWD_DEFINED__
#define __IPDSpread_FWD_DEFINED__
typedef interface IPDSpread IPDSpread;
#endif 	/* __IPDSpread_FWD_DEFINED__ */


#ifndef __IPDSpreadMaster_FWD_DEFINED__
#define __IPDSpreadMaster_FWD_DEFINED__
typedef interface IPDSpreadMaster IPDSpreadMaster;
#endif 	/* __IPDSpreadMaster_FWD_DEFINED__ */


#ifndef __IPDObjectGroup_FWD_DEFINED__
#define __IPDObjectGroup_FWD_DEFINED__
typedef interface IPDObjectGroup IPDObjectGroup;
#endif 	/* __IPDObjectGroup_FWD_DEFINED__ */


#ifndef __IPDObjectLayerGroup_FWD_DEFINED__
#define __IPDObjectLayerGroup_FWD_DEFINED__
typedef interface IPDObjectLayerGroup IPDObjectLayerGroup;
#endif 	/* __IPDObjectLayerGroup_FWD_DEFINED__ */


#ifndef __IPDObjectFrame_FWD_DEFINED__
#define __IPDObjectFrame_FWD_DEFINED__
typedef interface IPDObjectFrame IPDObjectFrame;
#endif 	/* __IPDObjectFrame_FWD_DEFINED__ */


#ifndef __IPDObjectText_FWD_DEFINED__
#define __IPDObjectText_FWD_DEFINED__
typedef interface IPDObjectText IPDObjectText;
#endif 	/* __IPDObjectText_FWD_DEFINED__ */


#ifndef __IPDContentText_FWD_DEFINED__
#define __IPDContentText_FWD_DEFINED__
typedef interface IPDContentText IPDContentText;
#endif 	/* __IPDContentText_FWD_DEFINED__ */


#ifndef __IPDContentGraphic_FWD_DEFINED__
#define __IPDContentGraphic_FWD_DEFINED__
typedef interface IPDContentGraphic IPDContentGraphic;
#endif 	/* __IPDContentGraphic_FWD_DEFINED__ */


#ifndef __IPDPathText_FWD_DEFINED__
#define __IPDPathText_FWD_DEFINED__
typedef interface IPDPathText IPDPathText;
#endif 	/* __IPDPathText_FWD_DEFINED__ */


#ifndef __IPDImage_FWD_DEFINED__
#define __IPDImage_FWD_DEFINED__
typedef interface IPDImage IPDImage;
#endif 	/* __IPDImage_FWD_DEFINED__ */


#ifndef __IPDMatrix_FWD_DEFINED__
#define __IPDMatrix_FWD_DEFINED__
typedef interface IPDMatrix IPDMatrix;
#endif 	/* __IPDMatrix_FWD_DEFINED__ */


#ifndef __IPDGuide_FWD_DEFINED__
#define __IPDGuide_FWD_DEFINED__
typedef interface IPDGuide IPDGuide;
#endif 	/* __IPDGuide_FWD_DEFINED__ */


#ifndef __IPDGuides_FWD_DEFINED__
#define __IPDGuides_FWD_DEFINED__
typedef interface IPDGuides IPDGuides;
#endif 	/* __IPDGuides_FWD_DEFINED__ */


#ifndef __IPDSwatch_FWD_DEFINED__
#define __IPDSwatch_FWD_DEFINED__
typedef interface IPDSwatch IPDSwatch;
#endif 	/* __IPDSwatch_FWD_DEFINED__ */


#ifndef __IPDSwatchColor_FWD_DEFINED__
#define __IPDSwatchColor_FWD_DEFINED__
typedef interface IPDSwatchColor IPDSwatchColor;
#endif 	/* __IPDSwatchColor_FWD_DEFINED__ */


#ifndef __IPDSwatchTint_FWD_DEFINED__
#define __IPDSwatchTint_FWD_DEFINED__
typedef interface IPDSwatchTint IPDSwatchTint;
#endif 	/* __IPDSwatchTint_FWD_DEFINED__ */


#ifndef __IPDSwatchGradient_FWD_DEFINED__
#define __IPDSwatchGradient_FWD_DEFINED__
typedef interface IPDSwatchGradient IPDSwatchGradient;
#endif 	/* __IPDSwatchGradient_FWD_DEFINED__ */


#ifndef __IPDSwatchPattern_FWD_DEFINED__
#define __IPDSwatchPattern_FWD_DEFINED__
typedef interface IPDSwatchPattern IPDSwatchPattern;
#endif 	/* __IPDSwatchPattern_FWD_DEFINED__ */


#ifndef __IPDSwatches_FWD_DEFINED__
#define __IPDSwatches_FWD_DEFINED__
typedef interface IPDSwatches IPDSwatches;
#endif 	/* __IPDSwatches_FWD_DEFINED__ */


#ifndef __IPDGradient_FWD_DEFINED__
#define __IPDGradient_FWD_DEFINED__
typedef interface IPDGradient IPDGradient;
#endif 	/* __IPDGradient_FWD_DEFINED__ */


#ifndef __IPDGradientStop_FWD_DEFINED__
#define __IPDGradientStop_FWD_DEFINED__
typedef interface IPDGradientStop IPDGradientStop;
#endif 	/* __IPDGradientStop_FWD_DEFINED__ */


#ifndef __IPDBrush_FWD_DEFINED__
#define __IPDBrush_FWD_DEFINED__
typedef interface IPDBrush IPDBrush;
#endif 	/* __IPDBrush_FWD_DEFINED__ */


#ifndef __IPDObjectWithBrush_FWD_DEFINED__
#define __IPDObjectWithBrush_FWD_DEFINED__
typedef interface IPDObjectWithBrush IPDObjectWithBrush;
#endif 	/* __IPDObjectWithBrush_FWD_DEFINED__ */


#ifndef __IPDObjectStroke_FWD_DEFINED__
#define __IPDObjectStroke_FWD_DEFINED__
typedef interface IPDObjectStroke IPDObjectStroke;
#endif 	/* __IPDObjectStroke_FWD_DEFINED__ */


#ifndef __IPDObjectFill_FWD_DEFINED__
#define __IPDObjectFill_FWD_DEFINED__
typedef interface IPDObjectFill IPDObjectFill;
#endif 	/* __IPDObjectFill_FWD_DEFINED__ */


#ifndef __IPDStory_FWD_DEFINED__
#define __IPDStory_FWD_DEFINED__
typedef interface IPDStory IPDStory;
#endif 	/* __IPDStory_FWD_DEFINED__ */


#ifndef __IPDObjectWithChildren_FWD_DEFINED__
#define __IPDObjectWithChildren_FWD_DEFINED__
typedef interface IPDObjectWithChildren IPDObjectWithChildren;
#endif 	/* __IPDObjectWithChildren_FWD_DEFINED__ */


#ifndef __IPDAppearance_FWD_DEFINED__
#define __IPDAppearance_FWD_DEFINED__
typedef interface IPDAppearance IPDAppearance;
#endif 	/* __IPDAppearance_FWD_DEFINED__ */


#ifndef __IPDTextRange_FWD_DEFINED__
#define __IPDTextRange_FWD_DEFINED__
typedef interface IPDTextRange IPDTextRange;
#endif 	/* __IPDTextRange_FWD_DEFINED__ */


#ifndef __IPDTextFont_FWD_DEFINED__
#define __IPDTextFont_FWD_DEFINED__
typedef interface IPDTextFont IPDTextFont;
#endif 	/* __IPDTextFont_FWD_DEFINED__ */


#ifndef __IPDTextPara_FWD_DEFINED__
#define __IPDTextPara_FWD_DEFINED__
typedef interface IPDTextPara IPDTextPara;
#endif 	/* __IPDTextPara_FWD_DEFINED__ */


#ifndef __IPDRenderer_FWD_DEFINED__
#define __IPDRenderer_FWD_DEFINED__
typedef interface IPDRenderer IPDRenderer;
#endif 	/* __IPDRenderer_FWD_DEFINED__ */


#ifndef __IPDFilterPrimitive_FWD_DEFINED__
#define __IPDFilterPrimitive_FWD_DEFINED__
typedef interface IPDFilterPrimitive IPDFilterPrimitive;
#endif 	/* __IPDFilterPrimitive_FWD_DEFINED__ */


#ifndef __IPDSymbol_FWD_DEFINED__
#define __IPDSymbol_FWD_DEFINED__
typedef interface IPDSymbol IPDSymbol;
#endif 	/* __IPDSymbol_FWD_DEFINED__ */


#ifndef __IPDSpreadDocument_FWD_DEFINED__
#define __IPDSpreadDocument_FWD_DEFINED__
typedef interface IPDSpreadDocument IPDSpreadDocument;
#endif 	/* __IPDSpreadDocument_FWD_DEFINED__ */


#ifndef __IArchive_FWD_DEFINED__
#define __IArchive_FWD_DEFINED__
typedef interface IArchive IArchive;
#endif 	/* __IArchive_FWD_DEFINED__ */


#ifndef __IArchiveElement_FWD_DEFINED__
#define __IArchiveElement_FWD_DEFINED__
typedef interface IArchiveElement IArchiveElement;
#endif 	/* __IArchiveElement_FWD_DEFINED__ */


#ifndef __IPageDesignerApp_FWD_DEFINED__
#define __IPageDesignerApp_FWD_DEFINED__
typedef interface IPageDesignerApp IPageDesignerApp;
#endif 	/* __IPageDesignerApp_FWD_DEFINED__ */


#ifndef __DispIPageDesignerFrame_FWD_DEFINED__
#define __DispIPageDesignerFrame_FWD_DEFINED__
typedef interface DispIPageDesignerFrame DispIPageDesignerFrame;
#endif 	/* __DispIPageDesignerFrame_FWD_DEFINED__ */


#ifndef __IObjectMap_FWD_DEFINED__
#define __IObjectMap_FWD_DEFINED__
typedef interface IObjectMap IObjectMap;
#endif 	/* __IObjectMap_FWD_DEFINED__ */


#ifndef __IPDColor_FWD_DEFINED__
#define __IPDColor_FWD_DEFINED__
typedef interface IPDColor IPDColor;
#endif 	/* __IPDColor_FWD_DEFINED__ */


#ifndef __IPluginFilterClass_FWD_DEFINED__
#define __IPluginFilterClass_FWD_DEFINED__
typedef interface IPluginFilterClass IPluginFilterClass;
#endif 	/* __IPluginFilterClass_FWD_DEFINED__ */


#ifndef __IPluginFilter_FWD_DEFINED__
#define __IPluginFilter_FWD_DEFINED__
typedef interface IPluginFilter IPluginFilter;
#endif 	/* __IPluginFilter_FWD_DEFINED__ */


#ifndef __IPDSection_FWD_DEFINED__
#define __IPDSection_FWD_DEFINED__
typedef interface IPDSection IPDSection;
#endif 	/* __IPDSection_FWD_DEFINED__ */


#ifndef __IPDDocumentSettings_FWD_DEFINED__
#define __IPDDocumentSettings_FWD_DEFINED__
typedef interface IPDDocumentSettings IPDDocumentSettings;
#endif 	/* __IPDDocumentSettings_FWD_DEFINED__ */


#ifndef __IPDApplicationSettings_FWD_DEFINED__
#define __IPDApplicationSettings_FWD_DEFINED__
typedef interface IPDApplicationSettings IPDApplicationSettings;
#endif 	/* __IPDApplicationSettings_FWD_DEFINED__ */


#ifndef __IPDBrushSettings_FWD_DEFINED__
#define __IPDBrushSettings_FWD_DEFINED__
typedef interface IPDBrushSettings IPDBrushSettings;
#endif 	/* __IPDBrushSettings_FWD_DEFINED__ */


#ifndef __IPDDocument_FWD_DEFINED__
#define __IPDDocument_FWD_DEFINED__
typedef interface IPDDocument IPDDocument;
#endif 	/* __IPDDocument_FWD_DEFINED__ */


#ifndef __IPDTextSelection_FWD_DEFINED__
#define __IPDTextSelection_FWD_DEFINED__
typedef interface IPDTextSelection IPDTextSelection;
#endif 	/* __IPDTextSelection_FWD_DEFINED__ */


#ifndef __DispIPDDocument_FWD_DEFINED__
#define __DispIPDDocument_FWD_DEFINED__
typedef interface DispIPDDocument DispIPDDocument;
#endif 	/* __DispIPDDocument_FWD_DEFINED__ */


#ifndef __IPDPage_FWD_DEFINED__
#define __IPDPage_FWD_DEFINED__
typedef interface IPDPage IPDPage;
#endif 	/* __IPDPage_FWD_DEFINED__ */


#ifndef __IPDSubPath_FWD_DEFINED__
#define __IPDSubPath_FWD_DEFINED__
typedef interface IPDSubPath IPDSubPath;
#endif 	/* __IPDSubPath_FWD_DEFINED__ */


#ifndef __IPDPath_FWD_DEFINED__
#define __IPDPath_FWD_DEFINED__
typedef interface IPDPath IPDPath;
#endif 	/* __IPDPath_FWD_DEFINED__ */


#ifndef __IPDObjectLocatable_FWD_DEFINED__
#define __IPDObjectLocatable_FWD_DEFINED__
typedef interface IPDObjectLocatable IPDObjectLocatable;
#endif 	/* __IPDObjectLocatable_FWD_DEFINED__ */


#ifndef __IPDObjectTransformable_FWD_DEFINED__
#define __IPDObjectTransformable_FWD_DEFINED__
typedef interface IPDObjectTransformable IPDObjectTransformable;
#endif 	/* __IPDObjectTransformable_FWD_DEFINED__ */


#ifndef __IPDObjectWrappable_FWD_DEFINED__
#define __IPDObjectWrappable_FWD_DEFINED__
typedef interface IPDObjectWrappable IPDObjectWrappable;
#endif 	/* __IPDObjectWrappable_FWD_DEFINED__ */


#ifndef __IPDObjectWithAppearance_FWD_DEFINED__
#define __IPDObjectWithAppearance_FWD_DEFINED__
typedef interface IPDObjectWithAppearance IPDObjectWithAppearance;
#endif 	/* __IPDObjectWithAppearance_FWD_DEFINED__ */


#ifndef __IPDObjectWithAppearanceAndStrokeFill_FWD_DEFINED__
#define __IPDObjectWithAppearanceAndStrokeFill_FWD_DEFINED__
typedef interface IPDObjectWithAppearanceAndStrokeFill IPDObjectWithAppearanceAndStrokeFill;
#endif 	/* __IPDObjectWithAppearanceAndStrokeFill_FWD_DEFINED__ */


#ifndef __IPDObjectWithOpacityMask_FWD_DEFINED__
#define __IPDObjectWithOpacityMask_FWD_DEFINED__
typedef interface IPDObjectWithOpacityMask IPDObjectWithOpacityMask;
#endif 	/* __IPDObjectWithOpacityMask_FWD_DEFINED__ */


#ifndef __IPDOpacityAndBlendMode_FWD_DEFINED__
#define __IPDOpacityAndBlendMode_FWD_DEFINED__
typedef interface IPDOpacityAndBlendMode IPDOpacityAndBlendMode;
#endif 	/* __IPDOpacityAndBlendMode_FWD_DEFINED__ */


#ifndef __IPDTextFrameOptions_FWD_DEFINED__
#define __IPDTextFrameOptions_FWD_DEFINED__
typedef interface IPDTextFrameOptions IPDTextFrameOptions;
#endif 	/* __IPDTextFrameOptions_FWD_DEFINED__ */


#ifndef __IObjectSerializable_FWD_DEFINED__
#define __IObjectSerializable_FWD_DEFINED__
typedef interface IObjectSerializable IObjectSerializable;
#endif 	/* __IObjectSerializable_FWD_DEFINED__ */


#ifndef __IPagesDlg_FWD_DEFINED__
#define __IPagesDlg_FWD_DEFINED__
typedef interface IPagesDlg IPagesDlg;
#endif 	/* __IPagesDlg_FWD_DEFINED__ */


#ifndef __ILayersDlg_FWD_DEFINED__
#define __ILayersDlg_FWD_DEFINED__
typedef interface ILayersDlg ILayersDlg;
#endif 	/* __ILayersDlg_FWD_DEFINED__ */


#ifndef __ITabsDlg_FWD_DEFINED__
#define __ITabsDlg_FWD_DEFINED__
typedef interface ITabsDlg ITabsDlg;
#endif 	/* __ITabsDlg_FWD_DEFINED__ */


#ifndef __ISwatchLibraryDlg_FWD_DEFINED__
#define __ISwatchLibraryDlg_FWD_DEFINED__
typedef interface ISwatchLibraryDlg ISwatchLibraryDlg;
#endif 	/* __ISwatchLibraryDlg_FWD_DEFINED__ */


#ifndef __ILinksDlg_FWD_DEFINED__
#define __ILinksDlg_FWD_DEFINED__
typedef interface ILinksDlg ILinksDlg;
#endif 	/* __ILinksDlg_FWD_DEFINED__ */


#ifndef __ITransparencyDlg_FWD_DEFINED__
#define __ITransparencyDlg_FWD_DEFINED__
typedef interface ITransparencyDlg ITransparencyDlg;
#endif 	/* __ITransparencyDlg_FWD_DEFINED__ */


#ifndef __IFilterGraphDlg_FWD_DEFINED__
#define __IFilterGraphDlg_FWD_DEFINED__
typedef interface IFilterGraphDlg IFilterGraphDlg;
#endif 	/* __IFilterGraphDlg_FWD_DEFINED__ */


#ifndef __IFEGaussianBlur_FWD_DEFINED__
#define __IFEGaussianBlur_FWD_DEFINED__
typedef interface IFEGaussianBlur IFEGaussianBlur;
#endif 	/* __IFEGaussianBlur_FWD_DEFINED__ */


#ifndef __IFEOffset_FWD_DEFINED__
#define __IFEOffset_FWD_DEFINED__
typedef interface IFEOffset IFEOffset;
#endif 	/* __IFEOffset_FWD_DEFINED__ */


#ifndef __IFEComposite_FWD_DEFINED__
#define __IFEComposite_FWD_DEFINED__
typedef interface IFEComposite IFEComposite;
#endif 	/* __IFEComposite_FWD_DEFINED__ */


#ifndef __IPluginFiltersDlg_FWD_DEFINED__
#define __IPluginFiltersDlg_FWD_DEFINED__
typedef interface IPluginFiltersDlg IPluginFiltersDlg;
#endif 	/* __IPluginFiltersDlg_FWD_DEFINED__ */


#ifndef __IStylesDlg_FWD_DEFINED__
#define __IStylesDlg_FWD_DEFINED__
typedef interface IStylesDlg IStylesDlg;
#endif 	/* __IStylesDlg_FWD_DEFINED__ */


#ifndef __IFEFreeTransform_FWD_DEFINED__
#define __IFEFreeTransform_FWD_DEFINED__
typedef interface IFEFreeTransform IFEFreeTransform;
#endif 	/* __IFEFreeTransform_FWD_DEFINED__ */


#ifndef __IAppearanceDlg_FWD_DEFINED__
#define __IAppearanceDlg_FWD_DEFINED__
typedef interface IAppearanceDlg IAppearanceDlg;
#endif 	/* __IAppearanceDlg_FWD_DEFINED__ */


#ifndef __ISymbolsDlg_FWD_DEFINED__
#define __ISymbolsDlg_FWD_DEFINED__
typedef interface ISymbolsDlg ISymbolsDlg;
#endif 	/* __ISymbolsDlg_FWD_DEFINED__ */


#ifndef __IPDObjectSymbolInstance_FWD_DEFINED__
#define __IPDObjectSymbolInstance_FWD_DEFINED__
typedef interface IPDObjectSymbolInstance IPDObjectSymbolInstance;
#endif 	/* __IPDObjectSymbolInstance_FWD_DEFINED__ */


#ifndef __IPDObjectSymbolInstanceSet_FWD_DEFINED__
#define __IPDObjectSymbolInstanceSet_FWD_DEFINED__
typedef interface IPDObjectSymbolInstanceSet IPDObjectSymbolInstanceSet;
#endif 	/* __IPDObjectSymbolInstanceSet_FWD_DEFINED__ */


#ifndef __IPDStrokeSettings_FWD_DEFINED__
#define __IPDStrokeSettings_FWD_DEFINED__
typedef interface IPDStrokeSettings IPDStrokeSettings;
#endif 	/* __IPDStrokeSettings_FWD_DEFINED__ */


#ifndef __IPDObjectSelection_FWD_DEFINED__
#define __IPDObjectSelection_FWD_DEFINED__
typedef interface IPDObjectSelection IPDObjectSelection;
#endif 	/* __IPDObjectSelection_FWD_DEFINED__ */


#ifndef __IPDCustomRenderer_FWD_DEFINED__
#define __IPDCustomRenderer_FWD_DEFINED__
typedef interface IPDCustomRenderer IPDCustomRenderer;
#endif 	/* __IPDCustomRenderer_FWD_DEFINED__ */


#ifndef __ISwatchesDlg_FWD_DEFINED__
#define __ISwatchesDlg_FWD_DEFINED__
typedef interface ISwatchesDlg ISwatchesDlg;
#endif 	/* __ISwatchesDlg_FWD_DEFINED__ */


#ifndef __IGradientDlg_FWD_DEFINED__
#define __IGradientDlg_FWD_DEFINED__
typedef interface IGradientDlg IGradientDlg;
#endif 	/* __IGradientDlg_FWD_DEFINED__ */


#ifndef __INavigatorDlg_FWD_DEFINED__
#define __INavigatorDlg_FWD_DEFINED__
typedef interface INavigatorDlg INavigatorDlg;
#endif 	/* __INavigatorDlg_FWD_DEFINED__ */


#ifndef __IStrokeDlg_FWD_DEFINED__
#define __IStrokeDlg_FWD_DEFINED__
typedef interface IStrokeDlg IStrokeDlg;
#endif 	/* __IStrokeDlg_FWD_DEFINED__ */


#ifndef __ISwatchesList_FWD_DEFINED__
#define __ISwatchesList_FWD_DEFINED__
typedef interface ISwatchesList ISwatchesList;
#endif 	/* __ISwatchesList_FWD_DEFINED__ */


#ifndef __IColorDlg_FWD_DEFINED__
#define __IColorDlg_FWD_DEFINED__
typedef interface IColorDlg IColorDlg;
#endif 	/* __IColorDlg_FWD_DEFINED__ */


#ifndef __IGradientEdit_FWD_DEFINED__
#define __IGradientEdit_FWD_DEFINED__
typedef interface IGradientEdit IGradientEdit;
#endif 	/* __IGradientEdit_FWD_DEFINED__ */


#ifndef __IToolsDlg_FWD_DEFINED__
#define __IToolsDlg_FWD_DEFINED__
typedef interface IToolsDlg IToolsDlg;
#endif 	/* __IToolsDlg_FWD_DEFINED__ */


#ifndef __ITabsControl_FWD_DEFINED__
#define __ITabsControl_FWD_DEFINED__
typedef interface ITabsControl ITabsControl;
#endif 	/* __ITabsControl_FWD_DEFINED__ */


#ifndef __PDObjectFill_FWD_DEFINED__
#define __PDObjectFill_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDObjectFill PDObjectFill;
#else
typedef struct PDObjectFill PDObjectFill;
#endif /* __cplusplus */

#endif 	/* __PDObjectFill_FWD_DEFINED__ */


#ifndef __PDObjectStroke_FWD_DEFINED__
#define __PDObjectStroke_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDObjectStroke PDObjectStroke;
#else
typedef struct PDObjectStroke PDObjectStroke;
#endif /* __cplusplus */

#endif 	/* __PDObjectStroke_FWD_DEFINED__ */


#ifndef __PageDesignerFrame_FWD_DEFINED__
#define __PageDesignerFrame_FWD_DEFINED__

#ifdef __cplusplus
typedef class PageDesignerFrame PageDesignerFrame;
#else
typedef struct PageDesignerFrame PageDesignerFrame;
#endif /* __cplusplus */

#endif 	/* __PageDesignerFrame_FWD_DEFINED__ */


#ifndef __PagesDlg_FWD_DEFINED__
#define __PagesDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class PagesDlg PagesDlg;
#else
typedef struct PagesDlg PagesDlg;
#endif /* __cplusplus */

#endif 	/* __PagesDlg_FWD_DEFINED__ */


#ifndef ___IPDDocumentEvents_FWD_DEFINED__
#define ___IPDDocumentEvents_FWD_DEFINED__
typedef interface _IPDDocumentEvents _IPDDocumentEvents;
#endif 	/* ___IPDDocumentEvents_FWD_DEFINED__ */


#ifndef ___IPDDocumentViewEvents_FWD_DEFINED__
#define ___IPDDocumentViewEvents_FWD_DEFINED__
typedef interface _IPDDocumentViewEvents _IPDDocumentViewEvents;
#endif 	/* ___IPDDocumentViewEvents_FWD_DEFINED__ */


#ifndef ___ILayersDlgEvents_FWD_DEFINED__
#define ___ILayersDlgEvents_FWD_DEFINED__
typedef interface _ILayersDlgEvents _ILayersDlgEvents;
#endif 	/* ___ILayersDlgEvents_FWD_DEFINED__ */


#ifndef __PDDocument_FWD_DEFINED__
#define __PDDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDDocument PDDocument;
#else
typedef struct PDDocument PDDocument;
#endif /* __cplusplus */

#endif 	/* __PDDocument_FWD_DEFINED__ */


#ifndef __PDDocumentView_FWD_DEFINED__
#define __PDDocumentView_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDDocumentView PDDocumentView;
#else
typedef struct PDDocumentView PDDocumentView;
#endif /* __cplusplus */

#endif 	/* __PDDocumentView_FWD_DEFINED__ */


#ifndef __PDMatrix_FWD_DEFINED__
#define __PDMatrix_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDMatrix PDMatrix;
#else
typedef struct PDMatrix PDMatrix;
#endif /* __cplusplus */

#endif 	/* __PDMatrix_FWD_DEFINED__ */


#ifndef __PDGradient_FWD_DEFINED__
#define __PDGradient_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDGradient PDGradient;
#else
typedef struct PDGradient PDGradient;
#endif /* __cplusplus */

#endif 	/* __PDGradient_FWD_DEFINED__ */


#ifndef __LayersDlg_FWD_DEFINED__
#define __LayersDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class LayersDlg LayersDlg;
#else
typedef struct LayersDlg LayersDlg;
#endif /* __cplusplus */

#endif 	/* __LayersDlg_FWD_DEFINED__ */


#ifndef __PDRenderer_FWD_DEFINED__
#define __PDRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDRenderer PDRenderer;
#else
typedef struct PDRenderer PDRenderer;
#endif /* __cplusplus */

#endif 	/* __PDRenderer_FWD_DEFINED__ */


#ifndef ___ISwatchesDlgEvents_FWD_DEFINED__
#define ___ISwatchesDlgEvents_FWD_DEFINED__
typedef interface _ISwatchesDlgEvents _ISwatchesDlgEvents;
#endif 	/* ___ISwatchesDlgEvents_FWD_DEFINED__ */


#ifndef __SwatchesDlg_FWD_DEFINED__
#define __SwatchesDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class SwatchesDlg SwatchesDlg;
#else
typedef struct SwatchesDlg SwatchesDlg;
#endif /* __cplusplus */

#endif 	/* __SwatchesDlg_FWD_DEFINED__ */


#ifndef ___INavigatorDlgEvents_FWD_DEFINED__
#define ___INavigatorDlgEvents_FWD_DEFINED__
typedef interface _INavigatorDlgEvents _INavigatorDlgEvents;
#endif 	/* ___INavigatorDlgEvents_FWD_DEFINED__ */


#ifndef __NavigatorDlg_FWD_DEFINED__
#define __NavigatorDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class NavigatorDlg NavigatorDlg;
#else
typedef struct NavigatorDlg NavigatorDlg;
#endif /* __cplusplus */

#endif 	/* __NavigatorDlg_FWD_DEFINED__ */


#ifndef ___IGradientDlgEvents_FWD_DEFINED__
#define ___IGradientDlgEvents_FWD_DEFINED__
typedef interface _IGradientDlgEvents _IGradientDlgEvents;
#endif 	/* ___IGradientDlgEvents_FWD_DEFINED__ */


#ifndef __GradientDlg_FWD_DEFINED__
#define __GradientDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class GradientDlg GradientDlg;
#else
typedef struct GradientDlg GradientDlg;
#endif /* __cplusplus */

#endif 	/* __GradientDlg_FWD_DEFINED__ */


#ifndef ___IStrokeDlgEvents_FWD_DEFINED__
#define ___IStrokeDlgEvents_FWD_DEFINED__
typedef interface _IStrokeDlgEvents _IStrokeDlgEvents;
#endif 	/* ___IStrokeDlgEvents_FWD_DEFINED__ */


#ifndef __StrokeDlg_FWD_DEFINED__
#define __StrokeDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class StrokeDlg StrokeDlg;
#else
typedef struct StrokeDlg StrokeDlg;
#endif /* __cplusplus */

#endif 	/* __StrokeDlg_FWD_DEFINED__ */


#ifndef ___ISwatchesListEvents_FWD_DEFINED__
#define ___ISwatchesListEvents_FWD_DEFINED__
typedef interface _ISwatchesListEvents _ISwatchesListEvents;
#endif 	/* ___ISwatchesListEvents_FWD_DEFINED__ */


#ifndef __SwatchesList_FWD_DEFINED__
#define __SwatchesList_FWD_DEFINED__

#ifdef __cplusplus
typedef class SwatchesList SwatchesList;
#else
typedef struct SwatchesList SwatchesList;
#endif /* __cplusplus */

#endif 	/* __SwatchesList_FWD_DEFINED__ */


#ifndef ___IColorDlgEvents_FWD_DEFINED__
#define ___IColorDlgEvents_FWD_DEFINED__
typedef interface _IColorDlgEvents _IColorDlgEvents;
#endif 	/* ___IColorDlgEvents_FWD_DEFINED__ */


#ifndef __ColorDlg_FWD_DEFINED__
#define __ColorDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class ColorDlg ColorDlg;
#else
typedef struct ColorDlg ColorDlg;
#endif /* __cplusplus */

#endif 	/* __ColorDlg_FWD_DEFINED__ */


#ifndef ___IGradientEditEvents_FWD_DEFINED__
#define ___IGradientEditEvents_FWD_DEFINED__
typedef interface _IGradientEditEvents _IGradientEditEvents;
#endif 	/* ___IGradientEditEvents_FWD_DEFINED__ */


#ifndef __GradientEdit_FWD_DEFINED__
#define __GradientEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class GradientEdit GradientEdit;
#else
typedef struct GradientEdit GradientEdit;
#endif /* __cplusplus */

#endif 	/* __GradientEdit_FWD_DEFINED__ */


#ifndef ___IToolsDlgEvents_FWD_DEFINED__
#define ___IToolsDlgEvents_FWD_DEFINED__
typedef interface _IToolsDlgEvents _IToolsDlgEvents;
#endif 	/* ___IToolsDlgEvents_FWD_DEFINED__ */


#ifndef __ToolsDlg_FWD_DEFINED__
#define __ToolsDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class ToolsDlg ToolsDlg;
#else
typedef struct ToolsDlg ToolsDlg;
#endif /* __cplusplus */

#endif 	/* __ToolsDlg_FWD_DEFINED__ */


#ifndef ___ITabsControlEvents_FWD_DEFINED__
#define ___ITabsControlEvents_FWD_DEFINED__
typedef interface _ITabsControlEvents _ITabsControlEvents;
#endif 	/* ___ITabsControlEvents_FWD_DEFINED__ */


#ifndef __TabsControl_FWD_DEFINED__
#define __TabsControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TabsControl TabsControl;
#else
typedef struct TabsControl TabsControl;
#endif /* __cplusplus */

#endif 	/* __TabsControl_FWD_DEFINED__ */


#ifndef __TabsDlg_FWD_DEFINED__
#define __TabsDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class TabsDlg TabsDlg;
#else
typedef struct TabsDlg TabsDlg;
#endif /* __cplusplus */

#endif 	/* __TabsDlg_FWD_DEFINED__ */


#ifndef __SwatchLibraryDlg_FWD_DEFINED__
#define __SwatchLibraryDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class SwatchLibraryDlg SwatchLibraryDlg;
#else
typedef struct SwatchLibraryDlg SwatchLibraryDlg;
#endif /* __cplusplus */

#endif 	/* __SwatchLibraryDlg_FWD_DEFINED__ */


#ifndef __LinksDlg_FWD_DEFINED__
#define __LinksDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class LinksDlg LinksDlg;
#else
typedef struct LinksDlg LinksDlg;
#endif /* __cplusplus */

#endif 	/* __LinksDlg_FWD_DEFINED__ */


#ifndef __TransparencyDlg_FWD_DEFINED__
#define __TransparencyDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class TransparencyDlg TransparencyDlg;
#else
typedef struct TransparencyDlg TransparencyDlg;
#endif /* __cplusplus */

#endif 	/* __TransparencyDlg_FWD_DEFINED__ */


#ifndef __FilterGraphDlg_FWD_DEFINED__
#define __FilterGraphDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class FilterGraphDlg FilterGraphDlg;
#else
typedef struct FilterGraphDlg FilterGraphDlg;
#endif /* __cplusplus */

#endif 	/* __FilterGraphDlg_FWD_DEFINED__ */


#ifndef __FEGaussianBlur_FWD_DEFINED__
#define __FEGaussianBlur_FWD_DEFINED__

#ifdef __cplusplus
typedef class FEGaussianBlur FEGaussianBlur;
#else
typedef struct FEGaussianBlur FEGaussianBlur;
#endif /* __cplusplus */

#endif 	/* __FEGaussianBlur_FWD_DEFINED__ */


#ifndef __FEOffset_FWD_DEFINED__
#define __FEOffset_FWD_DEFINED__

#ifdef __cplusplus
typedef class FEOffset FEOffset;
#else
typedef struct FEOffset FEOffset;
#endif /* __cplusplus */

#endif 	/* __FEOffset_FWD_DEFINED__ */


#ifndef __FEComposite_FWD_DEFINED__
#define __FEComposite_FWD_DEFINED__

#ifdef __cplusplus
typedef class FEComposite FEComposite;
#else
typedef struct FEComposite FEComposite;
#endif /* __cplusplus */

#endif 	/* __FEComposite_FWD_DEFINED__ */


#ifndef __PluginFiltersDlg_FWD_DEFINED__
#define __PluginFiltersDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class PluginFiltersDlg PluginFiltersDlg;
#else
typedef struct PluginFiltersDlg PluginFiltersDlg;
#endif /* __cplusplus */

#endif 	/* __PluginFiltersDlg_FWD_DEFINED__ */


#ifndef __StylesDlg_FWD_DEFINED__
#define __StylesDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class StylesDlg StylesDlg;
#else
typedef struct StylesDlg StylesDlg;
#endif /* __cplusplus */

#endif 	/* __StylesDlg_FWD_DEFINED__ */


#ifndef __FEFreeTransform_FWD_DEFINED__
#define __FEFreeTransform_FWD_DEFINED__

#ifdef __cplusplus
typedef class FEFreeTransform FEFreeTransform;
#else
typedef struct FEFreeTransform FEFreeTransform;
#endif /* __cplusplus */

#endif 	/* __FEFreeTransform_FWD_DEFINED__ */


#ifndef __Archive_FWD_DEFINED__
#define __Archive_FWD_DEFINED__

#ifdef __cplusplus
typedef class Archive Archive;
#else
typedef struct Archive Archive;
#endif /* __cplusplus */

#endif 	/* __Archive_FWD_DEFINED__ */


#ifndef __PDObjectLayerGroup_FWD_DEFINED__
#define __PDObjectLayerGroup_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDObjectLayerGroup PDObjectLayerGroup;
#else
typedef struct PDObjectLayerGroup PDObjectLayerGroup;
#endif /* __cplusplus */

#endif 	/* __PDObjectLayerGroup_FWD_DEFINED__ */


#ifndef __PDContentGraphic_FWD_DEFINED__
#define __PDContentGraphic_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDContentGraphic PDContentGraphic;
#else
typedef struct PDContentGraphic PDContentGraphic;
#endif /* __cplusplus */

#endif 	/* __PDContentGraphic_FWD_DEFINED__ */


#ifndef __PDContentText_FWD_DEFINED__
#define __PDContentText_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDContentText PDContentText;
#else
typedef struct PDContentText PDContentText;
#endif /* __cplusplus */

#endif 	/* __PDContentText_FWD_DEFINED__ */


#ifndef __PDObjectFrame_FWD_DEFINED__
#define __PDObjectFrame_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDObjectFrame PDObjectFrame;
#else
typedef struct PDObjectFrame PDObjectFrame;
#endif /* __cplusplus */

#endif 	/* __PDObjectFrame_FWD_DEFINED__ */


#ifndef __PDObjectGroup_FWD_DEFINED__
#define __PDObjectGroup_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDObjectGroup PDObjectGroup;
#else
typedef struct PDObjectGroup PDObjectGroup;
#endif /* __cplusplus */

#endif 	/* __PDObjectGroup_FWD_DEFINED__ */


#ifndef __PDLayer_FWD_DEFINED__
#define __PDLayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDLayer PDLayer;
#else
typedef struct PDLayer PDLayer;
#endif /* __cplusplus */

#endif 	/* __PDLayer_FWD_DEFINED__ */


#ifndef __PDPage_FWD_DEFINED__
#define __PDPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDPage PDPage;
#else
typedef struct PDPage PDPage;
#endif /* __cplusplus */

#endif 	/* __PDPage_FWD_DEFINED__ */


#ifndef __PDSpreadDocument_FWD_DEFINED__
#define __PDSpreadDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDSpreadDocument PDSpreadDocument;
#else
typedef struct PDSpreadDocument PDSpreadDocument;
#endif /* __cplusplus */

#endif 	/* __PDSpreadDocument_FWD_DEFINED__ */


#ifndef __PDSpreadMaster_FWD_DEFINED__
#define __PDSpreadMaster_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDSpreadMaster PDSpreadMaster;
#else
typedef struct PDSpreadMaster PDSpreadMaster;
#endif /* __cplusplus */

#endif 	/* __PDSpreadMaster_FWD_DEFINED__ */


#ifndef __PDAppearance_FWD_DEFINED__
#define __PDAppearance_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDAppearance PDAppearance;
#else
typedef struct PDAppearance PDAppearance;
#endif /* __cplusplus */

#endif 	/* __PDAppearance_FWD_DEFINED__ */


#ifndef __PDFilterPrimitive_FWD_DEFINED__
#define __PDFilterPrimitive_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDFilterPrimitive PDFilterPrimitive;
#else
typedef struct PDFilterPrimitive PDFilterPrimitive;
#endif /* __cplusplus */

#endif 	/* __PDFilterPrimitive_FWD_DEFINED__ */


#ifndef __PDSwatchPattern_FWD_DEFINED__
#define __PDSwatchPattern_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDSwatchPattern PDSwatchPattern;
#else
typedef struct PDSwatchPattern PDSwatchPattern;
#endif /* __cplusplus */

#endif 	/* __PDSwatchPattern_FWD_DEFINED__ */


#ifndef __AppearanceDlg_FWD_DEFINED__
#define __AppearanceDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class AppearanceDlg AppearanceDlg;
#else
typedef struct AppearanceDlg AppearanceDlg;
#endif /* __cplusplus */

#endif 	/* __AppearanceDlg_FWD_DEFINED__ */


#ifndef __PDSwatchColor_FWD_DEFINED__
#define __PDSwatchColor_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDSwatchColor PDSwatchColor;
#else
typedef struct PDSwatchColor PDSwatchColor;
#endif /* __cplusplus */

#endif 	/* __PDSwatchColor_FWD_DEFINED__ */


#ifndef __PDSwatchGradient_FWD_DEFINED__
#define __PDSwatchGradient_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDSwatchGradient PDSwatchGradient;
#else
typedef struct PDSwatchGradient PDSwatchGradient;
#endif /* __cplusplus */

#endif 	/* __PDSwatchGradient_FWD_DEFINED__ */


#ifndef __PDSwatchNone_FWD_DEFINED__
#define __PDSwatchNone_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDSwatchNone PDSwatchNone;
#else
typedef struct PDSwatchNone PDSwatchNone;
#endif /* __cplusplus */

#endif 	/* __PDSwatchNone_FWD_DEFINED__ */


#ifndef __PDGradientStop_FWD_DEFINED__
#define __PDGradientStop_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDGradientStop PDGradientStop;
#else
typedef struct PDGradientStop PDGradientStop;
#endif /* __cplusplus */

#endif 	/* __PDGradientStop_FWD_DEFINED__ */


#ifndef __SymbolsDlg_FWD_DEFINED__
#define __SymbolsDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class SymbolsDlg SymbolsDlg;
#else
typedef struct SymbolsDlg SymbolsDlg;
#endif /* __cplusplus */

#endif 	/* __SymbolsDlg_FWD_DEFINED__ */


#ifndef __PDSymbol_FWD_DEFINED__
#define __PDSymbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDSymbol PDSymbol;
#else
typedef struct PDSymbol PDSymbol;
#endif /* __cplusplus */

#endif 	/* __PDSymbol_FWD_DEFINED__ */


#ifndef __PDObjectSymbolInstance_FWD_DEFINED__
#define __PDObjectSymbolInstance_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDObjectSymbolInstance PDObjectSymbolInstance;
#else
typedef struct PDObjectSymbolInstance PDObjectSymbolInstance;
#endif /* __cplusplus */

#endif 	/* __PDObjectSymbolInstance_FWD_DEFINED__ */


#ifndef __PDObjectSymbolInstanceSet_FWD_DEFINED__
#define __PDObjectSymbolInstanceSet_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDObjectSymbolInstanceSet PDObjectSymbolInstanceSet;
#else
typedef struct PDObjectSymbolInstanceSet PDObjectSymbolInstanceSet;
#endif /* __cplusplus */

#endif 	/* __PDObjectSymbolInstanceSet_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LHTML.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __PAGEDESIGNERLib_LIBRARY_DEFINED__
#define __PAGEDESIGNERLib_LIBRARY_DEFINED__

/* library PAGEDESIGNERLib */
/* [helpstring][version][uuid] */ 















































typedef struct  _BezierPoint
    {
    double x1;
    double y1;
    double x;
    double y;
    double x2;
    double y2;
    }	BezierPoint;

typedef struct  _PointD
    {
    double x;
    double y;
    }	PointD;

typedef _RectD RectD;

typedef 
enum _PDUnit
    {	UNIT_PT	= 1,
	UNIT_PC	= 2,
	UNIT_IN	= 3,
	UNIT_IND	= 4,
	UNIT_MM	= 5,
	UNIT_CM	= 6,
	UNIT_CC	= 7,
	UNIT_NUMBER	= 20
    }	PDUnit;

typedef 
enum _PDObjectType
    {	OBJECT_FRAME	= 1,
	OBJECT_GROUP	= 2,
	OBJECT_LAYERGROUP	= 3,
	OBJECT_SYMBOLINSTANCE	= 4,
	OBJECT_SYMBOLINSTANCESET	= 5,
	CONTENT_GRAPHIC	= 6,
	CONTENT_TEXT	= 7,
	PATH_TEXT	= 8,
	OBJECT_GUIDE	= 15,
	OBJECT_GUIDES	= 16,
	PATH_STROKE	= 20,
	PATH_FILL	= 21
    }	PDObjectType;

typedef 
enum _PDSwatchType
    {	SWATCH_NONE	= 0,
	SWATCH_COLOR	= 1,
	SWATCH_TINT	= 2,
	SWATCH_GRADIENT	= 3,
	SWATCH_PATTERN	= 4
    }	PDSwatchType;

typedef 
enum _PDSwatchBuiltin
    {	SWATCH_CUSTOM	= 0,
	SWATCH_PAPER	= 1,
	SWATCH_BLACK	= 2,
	SWATCH_REGISTRATION	= 3
    }	PDSwatchBuiltin;

typedef 
enum _PDColorType
    {	COLORTYPE_PROCESS	= 1,
	COLORTYPE_SPOT	= 2
    }	PDColorType;

typedef 
enum _PDColorMode
    {	COLORMODE_RGB	= 1,
	COLORMODE_CMYK	= 2,
	COLORMODE_LAB	= 3
    }	PDColorMode;

typedef 
enum _PDBrushType
    {	BRUSH_NONE	= 0,
	BRUSH_COLOR	= 1,
	BRUSH_GRADIENT	= 3,
	BRUSH_PATTERN	= 4
    }	PDBrushType;

typedef 
enum _PDTextWrap
    {	TEXTWRAP_NONE	= 0,
	TEXTWRAP_BBOX	= 1,
	TEXTWRAP_SHAPE	= 2,
	TEXTWRAP_JUMPOBJECT	= 3,
	TEXTWRAP_JUMPCOLUMN	= 4
    }	PDTextWrap;

typedef 
enum _PDPathTextAlign
    {	PATHTEXTALIGN_BASELINE	= 0,
	PATHTEXTALIGN_ASCENDER	= 1,
	PATHTEXTALIGN_DESCENDER	= 2,
	PATHTEXTALIGN_CENTER	= 3
    }	PDPathTextAlign;

typedef 
enum _PDParaAlign
    {	PARAALIGN_LEFT	= 0,
	PARAALIGN_CENTER	= 1,
	PARAALIGN_RIGHT	= 2,
	PARAALIGN_JUSTIFYLEFT	= 3,
	PARAALIGN_JUSTIFYCENTER	= 4,
	PARAALIGN_JUSTIFYRIGHT	= 5,
	PARAALIGN_JUSTIFYALL	= 6
    }	PDParaAlign;

typedef 
enum _PDPathTextAlignToPath
    {	PATHTEXTALIGNTOPATH_CENTER	= 0,
	PATHTEXTALIGNTOPATH_TOP	= 1,
	PATHTEXTALIGNTOPATH_BOTTOM	= 2
    }	PDPathTextAlignToPath;

typedef 
enum _PDGradientType
    {	GRADIENT_LINEAR	= 1,
	GRADIENT_RADIAL	= 2
    }	PDGradientType;





EXTERN_C const IID LIBID_PAGEDESIGNERLib;

#ifndef __IPDUnknown_INTERFACE_DEFINED__
#define __IPDUnknown_INTERFACE_DEFINED__

/* interface IPDUnknown */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPDUnknown;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D5ABEC22-EFB9-11d5-95F0-0002E3045703")
    IPDUnknown : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPDUnknownVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDUnknown __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDUnknown __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDUnknown __RPC_FAR * This);
        
        END_INTERFACE
    } IPDUnknownVtbl;

    interface IPDUnknown
    {
        CONST_VTBL struct IPDUnknownVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDUnknown_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDUnknown_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDUnknown_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPDUnknown_INTERFACE_DEFINED__ */


#ifndef __IPDObjectUnknown_INTERFACE_DEFINED__
#define __IPDObjectUnknown_INTERFACE_DEFINED__

/* interface IPDObjectUnknown */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectUnknown;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E148D301-205A-11d6-95F0-0002E3045703")
    IPDObjectUnknown : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_uniqId( 
            /* [retval][out] */ GUID __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_objectType( 
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_layer( 
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_parent( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_parent( 
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_nextSibling( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_nextSibling( 
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_previousSibling( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_previousSibling( 
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeObject( 
            /* [in] */ IPDObjectUnknown __RPC_FAR *object) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_spread( 
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_spread( 
            /* [in] */ IPDSpread __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_document( 
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_document( 
            /* [in] */ IPDDocument __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectUnknownVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectUnknown __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectUnknown __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectUnknown __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDObjectUnknownVtbl;

    interface IPDObjectUnknown
    {
        CONST_VTBL struct IPDObjectUnknownVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectUnknown_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectUnknown_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectUnknown_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectUnknown_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectUnknown_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectUnknown_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectUnknown_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectUnknown_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectUnknown_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectUnknown_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectUnknown_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectUnknown_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectUnknown_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectUnknown_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectUnknown_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectUnknown_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectUnknown_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_uniqId_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ GUID __RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_uniqId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_objectType_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ PDObjectType __RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_objectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_layer_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_layer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_parent_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_put_parent_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);


void __RPC_STUB IPDObjectUnknown_put_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_nextSibling_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_nextSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_put_nextSibling_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);


void __RPC_STUB IPDObjectUnknown_put_nextSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_previousSibling_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_previousSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_put_previousSibling_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);


void __RPC_STUB IPDObjectUnknown_put_previousSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_removeObject_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [in] */ IPDObjectUnknown __RPC_FAR *object);


void __RPC_STUB IPDObjectUnknown_removeObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_spread_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_spread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_put_spread_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [in] */ IPDSpread __RPC_FAR *newVal);


void __RPC_STUB IPDObjectUnknown_put_spread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_get_document_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectUnknown_get_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectUnknown_put_document_Proxy( 
    IPDObjectUnknown __RPC_FAR * This,
    /* [in] */ IPDDocument __RPC_FAR *newVal);


void __RPC_STUB IPDObjectUnknown_put_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectUnknown_INTERFACE_DEFINED__ */


#ifndef __IPageDesignerFrame_INTERFACE_DEFINED__
#define __IPageDesignerFrame_INTERFACE_DEFINED__

/* interface IPageDesignerFrame */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPageDesignerFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF829B76-4695-46bf-8AA3-6033CA3BFB8D")
    IPageDesignerFrame : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPageDesignerFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPageDesignerFrame __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPageDesignerFrame __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPageDesignerFrame __RPC_FAR * This);
        
        END_INTERFACE
    } IPageDesignerFrameVtbl;

    interface IPageDesignerFrame
    {
        CONST_VTBL struct IPageDesignerFrameVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPageDesignerFrame_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPageDesignerFrame_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPageDesignerFrame_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPageDesignerFrame_INTERFACE_DEFINED__ */


#ifndef __IPDDocumentView_INTERFACE_DEFINED__
#define __IPDDocumentView_INTERFACE_DEFINED__

/* interface IPDDocumentView */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDDocumentView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD53033C-76AC-4b25-901E-40F773ACB0B6")
    IPDDocumentView : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_activeSpread( 
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_activeSpread( 
            /* [in] */ IPDSpread __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setScrollPosXY( 
            /* [in] */ long posx,
            /* [in] */ long posy) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_rulers( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_rulers( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getViewBox( 
            /* [retval][out] */ RECT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setRulerOrigin( 
            /* [in] */ double x,
            /* [in] */ double y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDDocumentViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDDocumentView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDDocumentView __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDDocumentView __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_activeSpread )( 
            IPDDocumentView __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_activeSpread )( 
            IPDDocumentView __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setScrollPosXY )( 
            IPDDocumentView __RPC_FAR * This,
            /* [in] */ long posx,
            /* [in] */ long posy);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rulers )( 
            IPDDocumentView __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rulers )( 
            IPDDocumentView __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getViewBox )( 
            IPDDocumentView __RPC_FAR * This,
            /* [retval][out] */ RECT __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setRulerOrigin )( 
            IPDDocumentView __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y);
        
        END_INTERFACE
    } IPDDocumentViewVtbl;

    interface IPDDocumentView
    {
        CONST_VTBL struct IPDDocumentViewVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDDocumentView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDDocumentView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDDocumentView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDDocumentView_get_activeSpread(This,pVal)	\
    (This)->lpVtbl -> get_activeSpread(This,pVal)

#define IPDDocumentView_put_activeSpread(This,newVal)	\
    (This)->lpVtbl -> put_activeSpread(This,newVal)

#define IPDDocumentView_setScrollPosXY(This,posx,posy)	\
    (This)->lpVtbl -> setScrollPosXY(This,posx,posy)

#define IPDDocumentView_get_rulers(This,pVal)	\
    (This)->lpVtbl -> get_rulers(This,pVal)

#define IPDDocumentView_put_rulers(This,newVal)	\
    (This)->lpVtbl -> put_rulers(This,newVal)

#define IPDDocumentView_getViewBox(This,pVal)	\
    (This)->lpVtbl -> getViewBox(This,pVal)

#define IPDDocumentView_setRulerOrigin(This,x,y)	\
    (This)->lpVtbl -> setRulerOrigin(This,x,y)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentView_get_activeSpread_Proxy( 
    IPDDocumentView __RPC_FAR * This,
    /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocumentView_get_activeSpread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentView_put_activeSpread_Proxy( 
    IPDDocumentView __RPC_FAR * This,
    /* [in] */ IPDSpread __RPC_FAR *newVal);


void __RPC_STUB IPDDocumentView_put_activeSpread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocumentView_setScrollPosXY_Proxy( 
    IPDDocumentView __RPC_FAR * This,
    /* [in] */ long posx,
    /* [in] */ long posy);


void __RPC_STUB IPDDocumentView_setScrollPosXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentView_get_rulers_Proxy( 
    IPDDocumentView __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentView_get_rulers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentView_put_rulers_Proxy( 
    IPDDocumentView __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDDocumentView_put_rulers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocumentView_getViewBox_Proxy( 
    IPDDocumentView __RPC_FAR * This,
    /* [retval][out] */ RECT __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentView_getViewBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocumentView_setRulerOrigin_Proxy( 
    IPDDocumentView __RPC_FAR * This,
    /* [in] */ double x,
    /* [in] */ double y);


void __RPC_STUB IPDDocumentView_setRulerOrigin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDDocumentView_INTERFACE_DEFINED__ */


#ifndef __IPDLayer_INTERFACE_DEFINED__
#define __IPDLayer_INTERFACE_DEFINED__

/* interface IPDLayer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDLayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("319D67B1-B23B-4753-A020-D035E7C15134")
    IPDLayer : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_visible( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_locked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_locked( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_color( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_color( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_uniqId( 
            /* [retval][out] */ GUID __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_nextSibling( 
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_previousSibling( 
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDLayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDLayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDLayer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDLayer __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDLayer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDLayer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_visible )( 
            IPDLayer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_visible )( 
            IPDLayer __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_locked )( 
            IPDLayer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_locked )( 
            IPDLayer __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_color )( 
            IPDLayer __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_color )( 
            IPDLayer __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDLayer __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDLayer __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDLayer __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDLayerVtbl;

    interface IPDLayer
    {
        CONST_VTBL struct IPDLayerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDLayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDLayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDLayer_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDLayer_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDLayer_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#define IPDLayer_get_visible(This,pVal)	\
    (This)->lpVtbl -> get_visible(This,pVal)

#define IPDLayer_put_visible(This,newVal)	\
    (This)->lpVtbl -> put_visible(This,newVal)

#define IPDLayer_get_locked(This,pVal)	\
    (This)->lpVtbl -> get_locked(This,pVal)

#define IPDLayer_put_locked(This,newVal)	\
    (This)->lpVtbl -> put_locked(This,newVal)

#define IPDLayer_get_color(This,pVal)	\
    (This)->lpVtbl -> get_color(This,pVal)

#define IPDLayer_put_color(This,newVal)	\
    (This)->lpVtbl -> put_color(This,newVal)

#define IPDLayer_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDLayer_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDLayer_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDLayer_get_name_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDLayer_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDLayer_put_name_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDLayer_put_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDLayer_get_visible_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDLayer_get_visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDLayer_put_visible_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDLayer_put_visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDLayer_get_locked_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDLayer_get_locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDLayer_put_locked_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDLayer_put_locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDLayer_get_color_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IPDLayer_get_color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDLayer_put_color_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IPDLayer_put_color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDLayer_get_uniqId_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [retval][out] */ GUID __RPC_FAR *pVal);


void __RPC_STUB IPDLayer_get_uniqId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDLayer_get_nextSibling_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDLayer_get_nextSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDLayer_get_previousSibling_Proxy( 
    IPDLayer __RPC_FAR * This,
    /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDLayer_get_previousSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDLayer_INTERFACE_DEFINED__ */


#ifndef __IPDObject_INTERFACE_DEFINED__
#define __IPDObject_INTERFACE_DEFINED__

/* interface IPDObject */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1C7D6CD6-43C5-4122-B0C7-38BA9F8D6FB1")
    IPDObject : public IPDObjectUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstChild( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastChild( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_children( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getScreenCTM( 
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getExpandedBBox( 
            /* [retval][out] */ RectD __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObject __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObject __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObject __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObject __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObject __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObject __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObject __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObject __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDObjectVtbl;

    interface IPDObject
    {
        CONST_VTBL struct IPDObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObject_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObject_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObject_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObject_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObject_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObject_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObject_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObject_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObject_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObject_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObject_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObject_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObject_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObject_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObject_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObject_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObject_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObject_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObject_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObject_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObject_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObject_get_firstChild_Proxy( 
    IPDObject __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObject_get_firstChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObject_get_lastChild_Proxy( 
    IPDObject __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObject_get_lastChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObject_get_children_Proxy( 
    IPDObject __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObject_get_children_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObject_getScreenCTM_Proxy( 
    IPDObject __RPC_FAR * This,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObject_getScreenCTM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObject_clone_Proxy( 
    IPDObject __RPC_FAR * This,
    /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObject_clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObject_getExpandedBBox_Proxy( 
    IPDObject __RPC_FAR * This,
    /* [retval][out] */ RectD __RPC_FAR *pVal);


void __RPC_STUB IPDObject_getExpandedBBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObject_INTERFACE_DEFINED__ */


#ifndef __IPDSpread_INTERFACE_DEFINED__
#define __IPDSpread_INTERFACE_DEFINED__

/* interface IPDSpread */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSpread;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43C3CFD3-DE5D-4142-81B7-FF396991371E")
    IPDSpread : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pages( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_layergroups( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_spine( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_spine( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ownerDocument( 
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_uniqId( 
            /* [retval][out] */ GUID __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getLayerGroupFromLayer( 
            /* [in] */ IPDLayer __RPC_FAR *layer,
            /* [retval][out] */ IPDObjectLayerGroup __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getObjectByUniqId( 
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeLayerGroup( 
            /* [in] */ IPDObjectLayerGroup __RPC_FAR *object) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstLayerGroup( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastLayerGroup( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSpreadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSpread __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSpread __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSpread __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pages )( 
            IPDSpread __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layergroups )( 
            IPDSpread __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spine )( 
            IPDSpread __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spine )( 
            IPDSpread __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerDocument )( 
            IPDSpread __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDSpread __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getLayerGroupFromLayer )( 
            IPDSpread __RPC_FAR * This,
            /* [in] */ IPDLayer __RPC_FAR *layer,
            /* [retval][out] */ IPDObjectLayerGroup __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getObjectByUniqId )( 
            IPDSpread __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeLayerGroup )( 
            IPDSpread __RPC_FAR * This,
            /* [in] */ IPDObjectLayerGroup __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstLayerGroup )( 
            IPDSpread __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastLayerGroup )( 
            IPDSpread __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDSpreadVtbl;

    interface IPDSpread
    {
        CONST_VTBL struct IPDSpreadVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSpread_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSpread_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSpread_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSpread_get_pages(This,pVal)	\
    (This)->lpVtbl -> get_pages(This,pVal)

#define IPDSpread_get_layergroups(This,pVal)	\
    (This)->lpVtbl -> get_layergroups(This,pVal)

#define IPDSpread_get_spine(This,pVal)	\
    (This)->lpVtbl -> get_spine(This,pVal)

#define IPDSpread_put_spine(This,newVal)	\
    (This)->lpVtbl -> put_spine(This,newVal)

#define IPDSpread_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define IPDSpread_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDSpread_getLayerGroupFromLayer(This,layer,pVal)	\
    (This)->lpVtbl -> getLayerGroupFromLayer(This,layer,pVal)

#define IPDSpread_getObjectByUniqId(This,guid,pVal)	\
    (This)->lpVtbl -> getObjectByUniqId(This,guid,pVal)

#define IPDSpread_removeLayerGroup(This,object)	\
    (This)->lpVtbl -> removeLayerGroup(This,object)

#define IPDSpread_get_firstLayerGroup(This,pVal)	\
    (This)->lpVtbl -> get_firstLayerGroup(This,pVal)

#define IPDSpread_get_lastLayerGroup(This,pVal)	\
    (This)->lpVtbl -> get_lastLayerGroup(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpread_get_pages_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSpread_get_pages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpread_get_layergroups_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSpread_get_layergroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpread_get_spine_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDSpread_get_spine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSpread_put_spine_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDSpread_put_spine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpread_get_ownerDocument_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSpread_get_ownerDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpread_get_uniqId_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [retval][out] */ GUID __RPC_FAR *pVal);


void __RPC_STUB IPDSpread_get_uniqId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSpread_getLayerGroupFromLayer_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [in] */ IPDLayer __RPC_FAR *layer,
    /* [retval][out] */ IPDObjectLayerGroup __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSpread_getLayerGroupFromLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSpread_getObjectByUniqId_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [in] */ GUID guid,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSpread_getObjectByUniqId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSpread_removeLayerGroup_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [in] */ IPDObjectLayerGroup __RPC_FAR *object);


void __RPC_STUB IPDSpread_removeLayerGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpread_get_firstLayerGroup_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSpread_get_firstLayerGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpread_get_lastLayerGroup_Proxy( 
    IPDSpread __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSpread_get_lastLayerGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSpread_INTERFACE_DEFINED__ */


#ifndef __IPDSpreadMaster_INTERFACE_DEFINED__
#define __IPDSpreadMaster_INTERFACE_DEFINED__

/* interface IPDSpreadMaster */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSpreadMaster;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("13616A81-E840-11d5-95F0-0002E3045703")
    IPDSpreadMaster : public IPDSpread
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_prefix( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_prefix( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSpreadMasterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSpreadMaster __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSpreadMaster __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pages )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layergroups )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spine )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spine )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerDocument )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getLayerGroupFromLayer )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [in] */ IPDLayer __RPC_FAR *layer,
            /* [retval][out] */ IPDObjectLayerGroup __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getObjectByUniqId )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeLayerGroup )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [in] */ IPDObjectLayerGroup __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstLayerGroup )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastLayerGroup )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_prefix )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_prefix )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDSpreadMaster __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IPDSpreadMasterVtbl;

    interface IPDSpreadMaster
    {
        CONST_VTBL struct IPDSpreadMasterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSpreadMaster_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSpreadMaster_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSpreadMaster_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSpreadMaster_get_pages(This,pVal)	\
    (This)->lpVtbl -> get_pages(This,pVal)

#define IPDSpreadMaster_get_layergroups(This,pVal)	\
    (This)->lpVtbl -> get_layergroups(This,pVal)

#define IPDSpreadMaster_get_spine(This,pVal)	\
    (This)->lpVtbl -> get_spine(This,pVal)

#define IPDSpreadMaster_put_spine(This,newVal)	\
    (This)->lpVtbl -> put_spine(This,newVal)

#define IPDSpreadMaster_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define IPDSpreadMaster_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDSpreadMaster_getLayerGroupFromLayer(This,layer,pVal)	\
    (This)->lpVtbl -> getLayerGroupFromLayer(This,layer,pVal)

#define IPDSpreadMaster_getObjectByUniqId(This,guid,pVal)	\
    (This)->lpVtbl -> getObjectByUniqId(This,guid,pVal)

#define IPDSpreadMaster_removeLayerGroup(This,object)	\
    (This)->lpVtbl -> removeLayerGroup(This,object)

#define IPDSpreadMaster_get_firstLayerGroup(This,pVal)	\
    (This)->lpVtbl -> get_firstLayerGroup(This,pVal)

#define IPDSpreadMaster_get_lastLayerGroup(This,pVal)	\
    (This)->lpVtbl -> get_lastLayerGroup(This,pVal)


#define IPDSpreadMaster_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define IPDSpreadMaster_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define IPDSpreadMaster_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDSpreadMaster_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpreadMaster_get_prefix_Proxy( 
    IPDSpreadMaster __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDSpreadMaster_get_prefix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSpreadMaster_put_prefix_Proxy( 
    IPDSpreadMaster __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDSpreadMaster_put_prefix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpreadMaster_get_name_Proxy( 
    IPDSpreadMaster __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDSpreadMaster_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSpreadMaster_put_name_Proxy( 
    IPDSpreadMaster __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDSpreadMaster_put_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSpreadMaster_INTERFACE_DEFINED__ */


#ifndef __IPDObjectGroup_INTERFACE_DEFINED__
#define __IPDObjectGroup_INTERFACE_DEFINED__

/* interface IPDObjectGroup */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDD26FDA-A724-444d-8B09-953ECD6E15EE")
    IPDObjectGroup : public IPDObject
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendObject( 
            /* [in] */ IPDObject __RPC_FAR *object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertObjectBeforeObject( 
            /* [in] */ IPDObject __RPC_FAR *object,
            /* [in] */ IPDObject __RPC_FAR *before) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_enableBackground( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_enableBackground( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectGroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectGroup __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendObject )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertObjectBeforeObject )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *object,
            /* [in] */ IPDObject __RPC_FAR *before);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_enableBackground )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_enableBackground )( 
            IPDObjectGroup __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IPDObjectGroupVtbl;

    interface IPDObjectGroup
    {
        CONST_VTBL struct IPDObjectGroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectGroup_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectGroup_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectGroup_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectGroup_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectGroup_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectGroup_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectGroup_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectGroup_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectGroup_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectGroup_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectGroup_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectGroup_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectGroup_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectGroup_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectGroup_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectGroup_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectGroup_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectGroup_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectGroup_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectGroup_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectGroup_appendObject(This,object)	\
    (This)->lpVtbl -> appendObject(This,object)

#define IPDObjectGroup_insertObjectBeforeObject(This,object,before)	\
    (This)->lpVtbl -> insertObjectBeforeObject(This,object,before)

#define IPDObjectGroup_get_enableBackground(This,pVal)	\
    (This)->lpVtbl -> get_enableBackground(This,pVal)

#define IPDObjectGroup_put_enableBackground(This,newVal)	\
    (This)->lpVtbl -> put_enableBackground(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectGroup_appendObject_Proxy( 
    IPDObjectGroup __RPC_FAR * This,
    /* [in] */ IPDObject __RPC_FAR *object);


void __RPC_STUB IPDObjectGroup_appendObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectGroup_insertObjectBeforeObject_Proxy( 
    IPDObjectGroup __RPC_FAR * This,
    /* [in] */ IPDObject __RPC_FAR *object,
    /* [in] */ IPDObject __RPC_FAR *before);


void __RPC_STUB IPDObjectGroup_insertObjectBeforeObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectGroup_get_enableBackground_Proxy( 
    IPDObjectGroup __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDObjectGroup_get_enableBackground_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectGroup_put_enableBackground_Proxy( 
    IPDObjectGroup __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDObjectGroup_put_enableBackground_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectGroup_INTERFACE_DEFINED__ */


#ifndef __IPDObjectLayerGroup_INTERFACE_DEFINED__
#define __IPDObjectLayerGroup_INTERFACE_DEFINED__

/* interface IPDObjectLayerGroup */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectLayerGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59FE0761-098C-11d6-95F0-0002E3045703")
    IPDObjectLayerGroup : public IPDObjectGroup
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_guides( 
            /* [retval][out] */ IPDGuides __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectLayerGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectLayerGroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectLayerGroup __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendObject )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertObjectBeforeObject )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *object,
            /* [in] */ IPDObject __RPC_FAR *before);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_enableBackground )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_enableBackground )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_guides )( 
            IPDObjectLayerGroup __RPC_FAR * This,
            /* [retval][out] */ IPDGuides __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDObjectLayerGroupVtbl;

    interface IPDObjectLayerGroup
    {
        CONST_VTBL struct IPDObjectLayerGroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectLayerGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectLayerGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectLayerGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectLayerGroup_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectLayerGroup_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectLayerGroup_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectLayerGroup_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectLayerGroup_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectLayerGroup_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectLayerGroup_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectLayerGroup_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectLayerGroup_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectLayerGroup_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectLayerGroup_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectLayerGroup_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectLayerGroup_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectLayerGroup_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectLayerGroup_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectLayerGroup_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectLayerGroup_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectLayerGroup_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectLayerGroup_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectLayerGroup_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectLayerGroup_appendObject(This,object)	\
    (This)->lpVtbl -> appendObject(This,object)

#define IPDObjectLayerGroup_insertObjectBeforeObject(This,object,before)	\
    (This)->lpVtbl -> insertObjectBeforeObject(This,object,before)

#define IPDObjectLayerGroup_get_enableBackground(This,pVal)	\
    (This)->lpVtbl -> get_enableBackground(This,pVal)

#define IPDObjectLayerGroup_put_enableBackground(This,newVal)	\
    (This)->lpVtbl -> put_enableBackground(This,newVal)


#define IPDObjectLayerGroup_get_guides(This,pVal)	\
    (This)->lpVtbl -> get_guides(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectLayerGroup_get_guides_Proxy( 
    IPDObjectLayerGroup __RPC_FAR * This,
    /* [retval][out] */ IPDGuides __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectLayerGroup_get_guides_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectLayerGroup_INTERFACE_DEFINED__ */


#ifndef __IPDObjectFrame_INTERFACE_DEFINED__
#define __IPDObjectFrame_INTERFACE_DEFINED__

/* interface IPDObjectFrame */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F5428D1-A66F-4119-9545-5BC3FA0440CE")
    IPDObjectFrame : public IPDObject
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_path( 
            /* [retval][out] */ IPDPath __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_path( 
            /* [in] */ IPDPath __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_content( 
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_content( 
            /* [in] */ IPDObject __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pathText( 
            /* [retval][out] */ IPDPathText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pathText( 
            /* [in] */ IPDPathText __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsPointOverStrokeOutline( 
            /* [in] */ PointD pt,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendSubObject( 
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectFrame __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectFrame __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_path )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDPath __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_path )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDPath __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_content )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_content )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pathText )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [retval][out] */ IPDPathText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pathText )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDPathText __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPointOverStrokeOutline )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ PointD pt,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendSubObject )( 
            IPDObjectFrame __RPC_FAR * This,
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object);
        
        END_INTERFACE
    } IPDObjectFrameVtbl;

    interface IPDObjectFrame
    {
        CONST_VTBL struct IPDObjectFrameVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectFrame_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectFrame_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectFrame_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectFrame_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectFrame_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectFrame_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectFrame_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectFrame_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectFrame_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectFrame_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectFrame_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectFrame_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectFrame_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectFrame_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectFrame_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectFrame_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectFrame_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectFrame_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectFrame_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectFrame_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectFrame_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectFrame_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectFrame_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectFrame_get_path(This,pVal)	\
    (This)->lpVtbl -> get_path(This,pVal)

#define IPDObjectFrame_put_path(This,newVal)	\
    (This)->lpVtbl -> put_path(This,newVal)

#define IPDObjectFrame_get_content(This,pVal)	\
    (This)->lpVtbl -> get_content(This,pVal)

#define IPDObjectFrame_put_content(This,newVal)	\
    (This)->lpVtbl -> put_content(This,newVal)

#define IPDObjectFrame_get_pathText(This,pVal)	\
    (This)->lpVtbl -> get_pathText(This,pVal)

#define IPDObjectFrame_put_pathText(This,newVal)	\
    (This)->lpVtbl -> put_pathText(This,newVal)

#define IPDObjectFrame_IsPointOverStrokeOutline(This,pt,pVal)	\
    (This)->lpVtbl -> IsPointOverStrokeOutline(This,pt,pVal)

#define IPDObjectFrame_appendSubObject(This,object)	\
    (This)->lpVtbl -> appendSubObject(This,object)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_get_path_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [retval][out] */ IPDPath __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectFrame_get_path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_put_path_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [in] */ IPDPath __RPC_FAR *newVal);


void __RPC_STUB IPDObjectFrame_put_path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_get_content_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectFrame_get_content_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_put_content_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [in] */ IPDObject __RPC_FAR *newVal);


void __RPC_STUB IPDObjectFrame_put_content_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_get_pathText_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [retval][out] */ IPDPathText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectFrame_get_pathText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_put_pathText_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [in] */ IPDPathText __RPC_FAR *newVal);


void __RPC_STUB IPDObjectFrame_put_pathText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_IsPointOverStrokeOutline_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [in] */ PointD pt,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectFrame_IsPointOverStrokeOutline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectFrame_appendSubObject_Proxy( 
    IPDObjectFrame __RPC_FAR * This,
    /* [in] */ IPDObjectWithBrush __RPC_FAR *object);


void __RPC_STUB IPDObjectFrame_appendSubObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectFrame_INTERFACE_DEFINED__ */


#ifndef __IPDObjectText_INTERFACE_DEFINED__
#define __IPDObjectText_INTERFACE_DEFINED__

/* interface IPDObjectText */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("13352CA8-421C-4414-8214-388E15D0044A")
    IPDObjectText : public IPDObject
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_story( 
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_story( 
            /* [in] */ IPDStory __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_previousTextThread( 
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_previousTextThread( 
            /* [in] */ IPDObjectText __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_nextTextThread( 
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_nextTextThread( 
            /* [in] */ IPDObjectText __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_overflow( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_threadPtIn( 
            /* [retval][out] */ PointD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_threadPtOut( 
            /* [retval][out] */ PointD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getPosUnderPoint( 
            /* [in] */ double x,
            /* [in] */ double y,
            /* [out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pNode,
            /* [out] */ long __RPC_FAR *pOffset,
            /* [retval][out] */ BOOL __RPC_FAR *bHit) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RenderSelection( 
            /* [in] */ HDC hDC,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ ILDOMRange __RPC_FAR *range) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectText __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectText __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_story )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_story )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDStory __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousTextThread )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousTextThread )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextTextThread )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextTextThread )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overflow )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_threadPtIn )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ PointD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_threadPtOut )( 
            IPDObjectText __RPC_FAR * This,
            /* [retval][out] */ PointD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPosUnderPoint )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pNode,
            /* [out] */ long __RPC_FAR *pOffset,
            /* [retval][out] */ BOOL __RPC_FAR *bHit);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderSelection )( 
            IPDObjectText __RPC_FAR * This,
            /* [in] */ HDC hDC,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ ILDOMRange __RPC_FAR *range);
        
        END_INTERFACE
    } IPDObjectTextVtbl;

    interface IPDObjectText
    {
        CONST_VTBL struct IPDObjectTextVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectText_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectText_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectText_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectText_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectText_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectText_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectText_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectText_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectText_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectText_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectText_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectText_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectText_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectText_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectText_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectText_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectText_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectText_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectText_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectText_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectText_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectText_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectText_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectText_get_story(This,pVal)	\
    (This)->lpVtbl -> get_story(This,pVal)

#define IPDObjectText_put_story(This,newVal)	\
    (This)->lpVtbl -> put_story(This,newVal)

#define IPDObjectText_get_previousTextThread(This,pVal)	\
    (This)->lpVtbl -> get_previousTextThread(This,pVal)

#define IPDObjectText_put_previousTextThread(This,newVal)	\
    (This)->lpVtbl -> put_previousTextThread(This,newVal)

#define IPDObjectText_get_nextTextThread(This,pVal)	\
    (This)->lpVtbl -> get_nextTextThread(This,pVal)

#define IPDObjectText_put_nextTextThread(This,newVal)	\
    (This)->lpVtbl -> put_nextTextThread(This,newVal)

#define IPDObjectText_get_overflow(This,pVal)	\
    (This)->lpVtbl -> get_overflow(This,pVal)

#define IPDObjectText_get_threadPtIn(This,pVal)	\
    (This)->lpVtbl -> get_threadPtIn(This,pVal)

#define IPDObjectText_get_threadPtOut(This,pVal)	\
    (This)->lpVtbl -> get_threadPtOut(This,pVal)

#define IPDObjectText_getPosUnderPoint(This,x,y,pNode,pOffset,bHit)	\
    (This)->lpVtbl -> getPosUnderPoint(This,x,y,pNode,pOffset,bHit)

#define IPDObjectText_RenderSelection(This,hDC,matrix,range)	\
    (This)->lpVtbl -> RenderSelection(This,hDC,matrix,range)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectText_get_story_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectText_get_story_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectText_put_story_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [in] */ IPDStory __RPC_FAR *newVal);


void __RPC_STUB IPDObjectText_put_story_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectText_get_previousTextThread_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectText_get_previousTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectText_put_previousTextThread_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [in] */ IPDObjectText __RPC_FAR *newVal);


void __RPC_STUB IPDObjectText_put_previousTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectText_get_nextTextThread_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectText_get_nextTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectText_put_nextTextThread_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [in] */ IPDObjectText __RPC_FAR *newVal);


void __RPC_STUB IPDObjectText_put_nextTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectText_get_overflow_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectText_get_overflow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectText_get_threadPtIn_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [retval][out] */ PointD __RPC_FAR *pVal);


void __RPC_STUB IPDObjectText_get_threadPtIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectText_get_threadPtOut_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [retval][out] */ PointD __RPC_FAR *pVal);


void __RPC_STUB IPDObjectText_get_threadPtOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectText_getPosUnderPoint_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [in] */ double x,
    /* [in] */ double y,
    /* [out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pNode,
    /* [out] */ long __RPC_FAR *pOffset,
    /* [retval][out] */ BOOL __RPC_FAR *bHit);


void __RPC_STUB IPDObjectText_getPosUnderPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectText_RenderSelection_Proxy( 
    IPDObjectText __RPC_FAR * This,
    /* [in] */ HDC hDC,
    /* [in] */ IPDMatrix __RPC_FAR *matrix,
    /* [in] */ ILDOMRange __RPC_FAR *range);


void __RPC_STUB IPDObjectText_RenderSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectText_INTERFACE_DEFINED__ */


#ifndef __IPDContentText_INTERFACE_DEFINED__
#define __IPDContentText_INTERFACE_DEFINED__

/* interface IPDContentText */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDContentText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("131F86E8-2B11-4cb6-9A85-BFA92B5DFD1D")
    IPDContentText : public IPDObjectText
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPDContentTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDContentText __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDContentText __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_story )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_story )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDStory __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousTextThread )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousTextThread )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextTextThread )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextTextThread )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overflow )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_threadPtIn )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ PointD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_threadPtOut )( 
            IPDContentText __RPC_FAR * This,
            /* [retval][out] */ PointD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPosUnderPoint )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pNode,
            /* [out] */ long __RPC_FAR *pOffset,
            /* [retval][out] */ BOOL __RPC_FAR *bHit);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderSelection )( 
            IPDContentText __RPC_FAR * This,
            /* [in] */ HDC hDC,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ ILDOMRange __RPC_FAR *range);
        
        END_INTERFACE
    } IPDContentTextVtbl;

    interface IPDContentText
    {
        CONST_VTBL struct IPDContentTextVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDContentText_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDContentText_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDContentText_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDContentText_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDContentText_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDContentText_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDContentText_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDContentText_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDContentText_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDContentText_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDContentText_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDContentText_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDContentText_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDContentText_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDContentText_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDContentText_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDContentText_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDContentText_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDContentText_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDContentText_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDContentText_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDContentText_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDContentText_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDContentText_get_story(This,pVal)	\
    (This)->lpVtbl -> get_story(This,pVal)

#define IPDContentText_put_story(This,newVal)	\
    (This)->lpVtbl -> put_story(This,newVal)

#define IPDContentText_get_previousTextThread(This,pVal)	\
    (This)->lpVtbl -> get_previousTextThread(This,pVal)

#define IPDContentText_put_previousTextThread(This,newVal)	\
    (This)->lpVtbl -> put_previousTextThread(This,newVal)

#define IPDContentText_get_nextTextThread(This,pVal)	\
    (This)->lpVtbl -> get_nextTextThread(This,pVal)

#define IPDContentText_put_nextTextThread(This,newVal)	\
    (This)->lpVtbl -> put_nextTextThread(This,newVal)

#define IPDContentText_get_overflow(This,pVal)	\
    (This)->lpVtbl -> get_overflow(This,pVal)

#define IPDContentText_get_threadPtIn(This,pVal)	\
    (This)->lpVtbl -> get_threadPtIn(This,pVal)

#define IPDContentText_get_threadPtOut(This,pVal)	\
    (This)->lpVtbl -> get_threadPtOut(This,pVal)

#define IPDContentText_getPosUnderPoint(This,x,y,pNode,pOffset,bHit)	\
    (This)->lpVtbl -> getPosUnderPoint(This,x,y,pNode,pOffset,bHit)

#define IPDContentText_RenderSelection(This,hDC,matrix,range)	\
    (This)->lpVtbl -> RenderSelection(This,hDC,matrix,range)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPDContentText_INTERFACE_DEFINED__ */


#ifndef __IPDContentGraphic_INTERFACE_DEFINED__
#define __IPDContentGraphic_INTERFACE_DEFINED__

/* interface IPDContentGraphic */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDContentGraphic;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("871E5A3C-30C2-4a3a-ACDB-14959C8F1FF7")
    IPDContentGraphic : public IPDObject
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_image( 
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_image( 
            /* [in] */ IPDImage __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_x( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_y( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setxy( 
            /* [in] */ double x,
            /* [in] */ double y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDContentGraphicVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDContentGraphic __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDContentGraphic __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_image )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_image )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ IPDImage __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setxy )( 
            IPDContentGraphic __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y);
        
        END_INTERFACE
    } IPDContentGraphicVtbl;

    interface IPDContentGraphic
    {
        CONST_VTBL struct IPDContentGraphicVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDContentGraphic_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDContentGraphic_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDContentGraphic_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDContentGraphic_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDContentGraphic_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDContentGraphic_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDContentGraphic_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDContentGraphic_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDContentGraphic_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDContentGraphic_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDContentGraphic_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDContentGraphic_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDContentGraphic_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDContentGraphic_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDContentGraphic_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDContentGraphic_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDContentGraphic_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDContentGraphic_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDContentGraphic_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDContentGraphic_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDContentGraphic_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDContentGraphic_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDContentGraphic_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDContentGraphic_get_image(This,pVal)	\
    (This)->lpVtbl -> get_image(This,pVal)

#define IPDContentGraphic_put_image(This,newVal)	\
    (This)->lpVtbl -> put_image(This,newVal)

#define IPDContentGraphic_get_x(This,pVal)	\
    (This)->lpVtbl -> get_x(This,pVal)

#define IPDContentGraphic_get_y(This,pVal)	\
    (This)->lpVtbl -> get_y(This,pVal)

#define IPDContentGraphic_setxy(This,x,y)	\
    (This)->lpVtbl -> setxy(This,x,y)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDContentGraphic_get_image_Proxy( 
    IPDContentGraphic __RPC_FAR * This,
    /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDContentGraphic_get_image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDContentGraphic_put_image_Proxy( 
    IPDContentGraphic __RPC_FAR * This,
    /* [in] */ IPDImage __RPC_FAR *newVal);


void __RPC_STUB IPDContentGraphic_put_image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDContentGraphic_get_x_Proxy( 
    IPDContentGraphic __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDContentGraphic_get_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDContentGraphic_get_y_Proxy( 
    IPDContentGraphic __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDContentGraphic_get_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDContentGraphic_setxy_Proxy( 
    IPDContentGraphic __RPC_FAR * This,
    /* [in] */ double x,
    /* [in] */ double y);


void __RPC_STUB IPDContentGraphic_setxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDContentGraphic_INTERFACE_DEFINED__ */


#ifndef __IPDPathText_INTERFACE_DEFINED__
#define __IPDPathText_INTERFACE_DEFINED__

/* interface IPDPathText */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDPathText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E439A088-E1BE-4c54-8E00-8A089DCAEBA5")
    IPDPathText : public IPDObjectText
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_startOnLength( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_startOnLength( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_endOnLength( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_endOnLength( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pathTextAlign( 
            /* [retval][out] */ PDPathTextAlign __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pathTextAlign( 
            /* [in] */ PDPathTextAlign newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pathTextAlignToPath( 
            /* [retval][out] */ PDPathTextAlignToPath __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pathTextAlignToPath( 
            /* [in] */ PDPathTextAlignToPath newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDPathTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDPathText __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDPathText __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_story )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_story )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDStory __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousTextThread )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousTextThread )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextTextThread )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextTextThread )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_overflow )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_threadPtIn )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ PointD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_threadPtOut )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ PointD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPosUnderPoint )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pNode,
            /* [out] */ long __RPC_FAR *pOffset,
            /* [retval][out] */ BOOL __RPC_FAR *bHit);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderSelection )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ HDC hDC,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ ILDOMRange __RPC_FAR *range);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_startOnLength )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_startOnLength )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_endOnLength )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_endOnLength )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pathTextAlign )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ PDPathTextAlign __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pathTextAlign )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ PDPathTextAlign newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pathTextAlignToPath )( 
            IPDPathText __RPC_FAR * This,
            /* [retval][out] */ PDPathTextAlignToPath __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pathTextAlignToPath )( 
            IPDPathText __RPC_FAR * This,
            /* [in] */ PDPathTextAlignToPath newVal);
        
        END_INTERFACE
    } IPDPathTextVtbl;

    interface IPDPathText
    {
        CONST_VTBL struct IPDPathTextVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDPathText_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDPathText_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDPathText_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDPathText_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDPathText_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDPathText_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDPathText_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDPathText_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDPathText_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDPathText_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDPathText_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDPathText_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDPathText_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDPathText_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDPathText_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDPathText_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDPathText_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDPathText_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDPathText_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDPathText_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDPathText_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDPathText_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDPathText_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDPathText_get_story(This,pVal)	\
    (This)->lpVtbl -> get_story(This,pVal)

#define IPDPathText_put_story(This,newVal)	\
    (This)->lpVtbl -> put_story(This,newVal)

#define IPDPathText_get_previousTextThread(This,pVal)	\
    (This)->lpVtbl -> get_previousTextThread(This,pVal)

#define IPDPathText_put_previousTextThread(This,newVal)	\
    (This)->lpVtbl -> put_previousTextThread(This,newVal)

#define IPDPathText_get_nextTextThread(This,pVal)	\
    (This)->lpVtbl -> get_nextTextThread(This,pVal)

#define IPDPathText_put_nextTextThread(This,newVal)	\
    (This)->lpVtbl -> put_nextTextThread(This,newVal)

#define IPDPathText_get_overflow(This,pVal)	\
    (This)->lpVtbl -> get_overflow(This,pVal)

#define IPDPathText_get_threadPtIn(This,pVal)	\
    (This)->lpVtbl -> get_threadPtIn(This,pVal)

#define IPDPathText_get_threadPtOut(This,pVal)	\
    (This)->lpVtbl -> get_threadPtOut(This,pVal)

#define IPDPathText_getPosUnderPoint(This,x,y,pNode,pOffset,bHit)	\
    (This)->lpVtbl -> getPosUnderPoint(This,x,y,pNode,pOffset,bHit)

#define IPDPathText_RenderSelection(This,hDC,matrix,range)	\
    (This)->lpVtbl -> RenderSelection(This,hDC,matrix,range)


#define IPDPathText_get_startOnLength(This,pVal)	\
    (This)->lpVtbl -> get_startOnLength(This,pVal)

#define IPDPathText_put_startOnLength(This,newVal)	\
    (This)->lpVtbl -> put_startOnLength(This,newVal)

#define IPDPathText_get_endOnLength(This,pVal)	\
    (This)->lpVtbl -> get_endOnLength(This,pVal)

#define IPDPathText_put_endOnLength(This,newVal)	\
    (This)->lpVtbl -> put_endOnLength(This,newVal)

#define IPDPathText_get_pathTextAlign(This,pVal)	\
    (This)->lpVtbl -> get_pathTextAlign(This,pVal)

#define IPDPathText_put_pathTextAlign(This,newVal)	\
    (This)->lpVtbl -> put_pathTextAlign(This,newVal)

#define IPDPathText_get_pathTextAlignToPath(This,pVal)	\
    (This)->lpVtbl -> get_pathTextAlignToPath(This,pVal)

#define IPDPathText_put_pathTextAlignToPath(This,newVal)	\
    (This)->lpVtbl -> put_pathTextAlignToPath(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPathText_get_startOnLength_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPathText_get_startOnLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPathText_put_startOnLength_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDPathText_put_startOnLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPathText_get_endOnLength_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPathText_get_endOnLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPathText_put_endOnLength_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDPathText_put_endOnLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPathText_get_pathTextAlign_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [retval][out] */ PDPathTextAlign __RPC_FAR *pVal);


void __RPC_STUB IPDPathText_get_pathTextAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPathText_put_pathTextAlign_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [in] */ PDPathTextAlign newVal);


void __RPC_STUB IPDPathText_put_pathTextAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPathText_get_pathTextAlignToPath_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [retval][out] */ PDPathTextAlignToPath __RPC_FAR *pVal);


void __RPC_STUB IPDPathText_get_pathTextAlignToPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPathText_put_pathTextAlignToPath_Proxy( 
    IPDPathText __RPC_FAR * This,
    /* [in] */ PDPathTextAlignToPath newVal);


void __RPC_STUB IPDPathText_put_pathTextAlignToPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDPathText_INTERFACE_DEFINED__ */


#ifndef __IPDImage_INTERFACE_DEFINED__
#define __IPDImage_INTERFACE_DEFINED__

/* interface IPDImage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BB7E7829-BA6E-4e0b-A116-A7F5FD0E8978")
    IPDImage : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pathName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pathName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_privateImage( 
            /* [retval][out] */ DWORD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_privateImage( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_width( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_height( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetProp( 
            /* [in] */ BSTR name,
            /* [in] */ DWORD value) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetProp( 
            /* [in] */ BSTR name,
            /* [retval][out] */ DWORD __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDImage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDImage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDImage __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pathName )( 
            IPDImage __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pathName )( 
            IPDImage __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_privateImage )( 
            IPDImage __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_privateImage )( 
            IPDImage __RPC_FAR * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_width )( 
            IPDImage __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_height )( 
            IPDImage __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProp )( 
            IPDImage __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ DWORD value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProp )( 
            IPDImage __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ DWORD __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDImageVtbl;

    interface IPDImage
    {
        CONST_VTBL struct IPDImageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDImage_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDImage_get_pathName(This,pVal)	\
    (This)->lpVtbl -> get_pathName(This,pVal)

#define IPDImage_put_pathName(This,newVal)	\
    (This)->lpVtbl -> put_pathName(This,newVal)

#define IPDImage_get_privateImage(This,pVal)	\
    (This)->lpVtbl -> get_privateImage(This,pVal)

#define IPDImage_put_privateImage(This,newVal)	\
    (This)->lpVtbl -> put_privateImage(This,newVal)

#define IPDImage_get_width(This,pVal)	\
    (This)->lpVtbl -> get_width(This,pVal)

#define IPDImage_get_height(This,pVal)	\
    (This)->lpVtbl -> get_height(This,pVal)

#define IPDImage_SetProp(This,name,value)	\
    (This)->lpVtbl -> SetProp(This,name,value)

#define IPDImage_GetProp(This,name,pVal)	\
    (This)->lpVtbl -> GetProp(This,name,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDImage_get_pathName_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDImage_get_pathName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDImage_put_pathName_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDImage_put_pathName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDImage_get_privateImage_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pVal);


void __RPC_STUB IPDImage_get_privateImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDImage_put_privateImage_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IPDImage_put_privateImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDImage_get_width_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDImage_get_width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDImage_get_height_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDImage_get_height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDImage_SetProp_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ DWORD value);


void __RPC_STUB IPDImage_SetProp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDImage_GetProp_Proxy( 
    IPDImage __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ DWORD __RPC_FAR *pVal);


void __RPC_STUB IPDImage_GetProp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDImage_INTERFACE_DEFINED__ */


#ifndef __IPDMatrix_INTERFACE_DEFINED__
#define __IPDMatrix_INTERFACE_DEFINED__

/* interface IPDMatrix */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDMatrix;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF13193F-AF95-461c-A90A-326B0B17A4C1")
    IPDMatrix : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_a( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_a( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_b( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_b( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_c( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_c( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_d( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_d( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_e( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_e( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_f( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_f( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE translate( 
            /* [in] */ double dx,
            /* [in] */ double dy,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE rotate( 
            /* [in] */ double angle,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE scaleNonUniform( 
            /* [in] */ double sx,
            /* [in] */ double sy,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE transformBezierPoint( 
            /* [in] */ BezierPoint __RPC_FAR *point,
            /* [retval][out] */ BezierPoint __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE inverse( 
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE transformPoint( 
            /* [in] */ PointD __RPC_FAR *point,
            /* [retval][out] */ PointD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setTranslate( 
            /* [in] */ double dx,
            /* [in] */ double dy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setScaleNonUniform( 
            /* [in] */ double sx,
            /* [in] */ double sy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE multiply( 
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getRotation( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE skewX( 
            /* [in] */ double angle,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE skewY( 
            /* [in] */ double angle,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE copyFrom( 
            /* [in] */ IPDMatrix __RPC_FAR *from) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE transpose( 
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setRotate( 
            /* [in] */ double angle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDMatrixVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDMatrix __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDMatrix __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_a )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_a )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_b )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_b )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_c )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_c )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_d )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_d )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_e )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_e )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_f )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_f )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *translate )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double dx,
            /* [in] */ double dy,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *rotate )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double angle,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *scaleNonUniform )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double sx,
            /* [in] */ double sy,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *transformBezierPoint )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ BezierPoint __RPC_FAR *point,
            /* [retval][out] */ BezierPoint __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *inverse )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *transformPoint )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ PointD __RPC_FAR *point,
            /* [retval][out] */ PointD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTranslate )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double dx,
            /* [in] */ double dy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setScaleNonUniform )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double sx,
            /* [in] */ double sy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *multiply )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRotation )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *skewX )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double angle,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *skewY )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double angle,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *copyFrom )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ IPDMatrix __RPC_FAR *from);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *transpose )( 
            IPDMatrix __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setRotate )( 
            IPDMatrix __RPC_FAR * This,
            /* [in] */ double angle);
        
        END_INTERFACE
    } IPDMatrixVtbl;

    interface IPDMatrix
    {
        CONST_VTBL struct IPDMatrixVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDMatrix_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDMatrix_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDMatrix_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDMatrix_get_a(This,pVal)	\
    (This)->lpVtbl -> get_a(This,pVal)

#define IPDMatrix_put_a(This,newVal)	\
    (This)->lpVtbl -> put_a(This,newVal)

#define IPDMatrix_get_b(This,pVal)	\
    (This)->lpVtbl -> get_b(This,pVal)

#define IPDMatrix_put_b(This,newVal)	\
    (This)->lpVtbl -> put_b(This,newVal)

#define IPDMatrix_get_c(This,pVal)	\
    (This)->lpVtbl -> get_c(This,pVal)

#define IPDMatrix_put_c(This,newVal)	\
    (This)->lpVtbl -> put_c(This,newVal)

#define IPDMatrix_get_d(This,pVal)	\
    (This)->lpVtbl -> get_d(This,pVal)

#define IPDMatrix_put_d(This,newVal)	\
    (This)->lpVtbl -> put_d(This,newVal)

#define IPDMatrix_get_e(This,pVal)	\
    (This)->lpVtbl -> get_e(This,pVal)

#define IPDMatrix_put_e(This,newVal)	\
    (This)->lpVtbl -> put_e(This,newVal)

#define IPDMatrix_get_f(This,pVal)	\
    (This)->lpVtbl -> get_f(This,pVal)

#define IPDMatrix_put_f(This,newVal)	\
    (This)->lpVtbl -> put_f(This,newVal)

#define IPDMatrix_translate(This,dx,dy,pVal)	\
    (This)->lpVtbl -> translate(This,dx,dy,pVal)

#define IPDMatrix_rotate(This,angle,pVal)	\
    (This)->lpVtbl -> rotate(This,angle,pVal)

#define IPDMatrix_scaleNonUniform(This,sx,sy,pVal)	\
    (This)->lpVtbl -> scaleNonUniform(This,sx,sy,pVal)

#define IPDMatrix_transformBezierPoint(This,point,pVal)	\
    (This)->lpVtbl -> transformBezierPoint(This,point,pVal)

#define IPDMatrix_inverse(This,pVal)	\
    (This)->lpVtbl -> inverse(This,pVal)

#define IPDMatrix_transformPoint(This,point,pVal)	\
    (This)->lpVtbl -> transformPoint(This,point,pVal)

#define IPDMatrix_setTranslate(This,dx,dy)	\
    (This)->lpVtbl -> setTranslate(This,dx,dy)

#define IPDMatrix_setScaleNonUniform(This,sx,sy)	\
    (This)->lpVtbl -> setScaleNonUniform(This,sx,sy)

#define IPDMatrix_multiply(This,matrix,pVal)	\
    (This)->lpVtbl -> multiply(This,matrix,pVal)

#define IPDMatrix_getRotation(This,pVal)	\
    (This)->lpVtbl -> getRotation(This,pVal)

#define IPDMatrix_skewX(This,angle,pVal)	\
    (This)->lpVtbl -> skewX(This,angle,pVal)

#define IPDMatrix_skewY(This,angle,pVal)	\
    (This)->lpVtbl -> skewY(This,angle,pVal)

#define IPDMatrix_copyFrom(This,from)	\
    (This)->lpVtbl -> copyFrom(This,from)

#define IPDMatrix_transpose(This,pVal)	\
    (This)->lpVtbl -> transpose(This,pVal)

#define IPDMatrix_setRotate(This,angle)	\
    (This)->lpVtbl -> setRotate(This,angle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDMatrix_get_a_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_get_a_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDMatrix_put_a_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDMatrix_put_a_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDMatrix_get_b_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_get_b_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDMatrix_put_b_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDMatrix_put_b_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDMatrix_get_c_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_get_c_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDMatrix_put_c_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDMatrix_put_c_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDMatrix_get_d_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_get_d_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDMatrix_put_d_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDMatrix_put_d_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDMatrix_get_e_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_get_e_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDMatrix_put_e_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDMatrix_put_e_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDMatrix_get_f_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_get_f_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDMatrix_put_f_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDMatrix_put_f_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_translate_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double dx,
    /* [in] */ double dy,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_translate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_rotate_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double angle,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_scaleNonUniform_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double sx,
    /* [in] */ double sy,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_scaleNonUniform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_transformBezierPoint_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ BezierPoint __RPC_FAR *point,
    /* [retval][out] */ BezierPoint __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_transformBezierPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_inverse_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_inverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_transformPoint_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ PointD __RPC_FAR *point,
    /* [retval][out] */ PointD __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_transformPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_setTranslate_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double dx,
    /* [in] */ double dy);


void __RPC_STUB IPDMatrix_setTranslate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_setScaleNonUniform_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double sx,
    /* [in] */ double sy);


void __RPC_STUB IPDMatrix_setScaleNonUniform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_multiply_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ IPDMatrix __RPC_FAR *matrix,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_multiply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_getRotation_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_getRotation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_skewX_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double angle,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_skewX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_skewY_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double angle,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_skewY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_copyFrom_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ IPDMatrix __RPC_FAR *from);


void __RPC_STUB IPDMatrix_copyFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_transpose_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDMatrix_transpose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDMatrix_setRotate_Proxy( 
    IPDMatrix __RPC_FAR * This,
    /* [in] */ double angle);


void __RPC_STUB IPDMatrix_setRotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDMatrix_INTERFACE_DEFINED__ */


#ifndef __IPDGuide_INTERFACE_DEFINED__
#define __IPDGuide_INTERFACE_DEFINED__

/* interface IPDGuide */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDGuide;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("68E597C1-E920-11d5-95F0-0002E3045703")
    IPDGuide : public IPDObjectUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pageIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pageIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_position( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_position( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_direction( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_direction( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ownerSpread( 
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE offsetPosition( 
            /* [in] */ double delta) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDGuideVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDGuide __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDGuide __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pageIndex )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pageIndex )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_position )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_position )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_direction )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_direction )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerSpread )( 
            IPDGuide __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *offsetPosition )( 
            IPDGuide __RPC_FAR * This,
            /* [in] */ double delta);
        
        END_INTERFACE
    } IPDGuideVtbl;

    interface IPDGuide
    {
        CONST_VTBL struct IPDGuideVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDGuide_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDGuide_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDGuide_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDGuide_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDGuide_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDGuide_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDGuide_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDGuide_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDGuide_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDGuide_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDGuide_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDGuide_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDGuide_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDGuide_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDGuide_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDGuide_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDGuide_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDGuide_get_pageIndex(This,pVal)	\
    (This)->lpVtbl -> get_pageIndex(This,pVal)

#define IPDGuide_put_pageIndex(This,newVal)	\
    (This)->lpVtbl -> put_pageIndex(This,newVal)

#define IPDGuide_get_position(This,pVal)	\
    (This)->lpVtbl -> get_position(This,pVal)

#define IPDGuide_put_position(This,newVal)	\
    (This)->lpVtbl -> put_position(This,newVal)

#define IPDGuide_get_direction(This,pVal)	\
    (This)->lpVtbl -> get_direction(This,pVal)

#define IPDGuide_put_direction(This,newVal)	\
    (This)->lpVtbl -> put_direction(This,newVal)

#define IPDGuide_get_ownerSpread(This,pVal)	\
    (This)->lpVtbl -> get_ownerSpread(This,pVal)

#define IPDGuide_offsetPosition(This,delta)	\
    (This)->lpVtbl -> offsetPosition(This,delta)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGuide_get_pageIndex_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDGuide_get_pageIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDGuide_put_pageIndex_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDGuide_put_pageIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGuide_get_position_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDGuide_get_position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDGuide_put_position_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDGuide_put_position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGuide_get_direction_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDGuide_get_direction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDGuide_put_direction_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDGuide_put_direction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGuide_get_ownerSpread_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGuide_get_ownerSpread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGuide_offsetPosition_Proxy( 
    IPDGuide __RPC_FAR * This,
    /* [in] */ double delta);


void __RPC_STUB IPDGuide_offsetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDGuide_INTERFACE_DEFINED__ */


#ifndef __IPDGuides_INTERFACE_DEFINED__
#define __IPDGuides_INTERFACE_DEFINED__

/* interface IPDGuides */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDGuides;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E148D303-205A-11d6-95F0-0002E3045703")
    IPDGuides : public IPDObjectUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createGuide( 
            /* [in] */ long direction,
            /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendGuide( 
            /* [in] */ IPDGuide __RPC_FAR *guide) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE item( 
            /* [in] */ long index,
            /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getGuideUnderPoint( 
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double tolerance,
            /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE deleteAllGuides( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDGuidesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDGuides __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDGuides __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createGuide )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ long direction,
            /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendGuide )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ IPDGuide __RPC_FAR *guide);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPDGuides __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getGuideUnderPoint )( 
            IPDGuides __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double tolerance,
            /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deleteAllGuides )( 
            IPDGuides __RPC_FAR * This);
        
        END_INTERFACE
    } IPDGuidesVtbl;

    interface IPDGuides
    {
        CONST_VTBL struct IPDGuidesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDGuides_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDGuides_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDGuides_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDGuides_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDGuides_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDGuides_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDGuides_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDGuides_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDGuides_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDGuides_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDGuides_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDGuides_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDGuides_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDGuides_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDGuides_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDGuides_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDGuides_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDGuides_createGuide(This,direction,pVal)	\
    (This)->lpVtbl -> createGuide(This,direction,pVal)

#define IPDGuides_appendGuide(This,guide)	\
    (This)->lpVtbl -> appendGuide(This,guide)

#define IPDGuides_get_length(This,pVal)	\
    (This)->lpVtbl -> get_length(This,pVal)

#define IPDGuides_item(This,index,pVal)	\
    (This)->lpVtbl -> item(This,index,pVal)

#define IPDGuides_getGuideUnderPoint(This,x,y,tolerance,pVal)	\
    (This)->lpVtbl -> getGuideUnderPoint(This,x,y,tolerance,pVal)

#define IPDGuides_deleteAllGuides(This)	\
    (This)->lpVtbl -> deleteAllGuides(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGuides_createGuide_Proxy( 
    IPDGuides __RPC_FAR * This,
    /* [in] */ long direction,
    /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGuides_createGuide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGuides_appendGuide_Proxy( 
    IPDGuides __RPC_FAR * This,
    /* [in] */ IPDGuide __RPC_FAR *guide);


void __RPC_STUB IPDGuides_appendGuide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGuides_get_length_Proxy( 
    IPDGuides __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDGuides_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGuides_item_Proxy( 
    IPDGuides __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGuides_item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGuides_getGuideUnderPoint_Proxy( 
    IPDGuides __RPC_FAR * This,
    /* [in] */ double x,
    /* [in] */ double y,
    /* [in] */ double tolerance,
    /* [retval][out] */ IPDGuide __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGuides_getGuideUnderPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGuides_deleteAllGuides_Proxy( 
    IPDGuides __RPC_FAR * This);


void __RPC_STUB IPDGuides_deleteAllGuides_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDGuides_INTERFACE_DEFINED__ */


#ifndef __IPDSwatch_INTERFACE_DEFINED__
#define __IPDSwatch_INTERFACE_DEFINED__

/* interface IPDSwatch */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSwatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7C773A42-86E2-40da-ADB1-A27F1DA4D1E1")
    IPDSwatch : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_swatchType( 
            /* [retval][out] */ PDSwatchType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_parent( 
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_canDelete( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_canEdit( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSwatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSwatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSwatch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSwatch __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatchType )( 
            IPDSwatch __RPC_FAR * This,
            /* [retval][out] */ PDSwatchType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDSwatch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDSwatch __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDSwatch __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDSwatch __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canDelete )( 
            IPDSwatch __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canEdit )( 
            IPDSwatch __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDSwatchVtbl;

    interface IPDSwatch
    {
        CONST_VTBL struct IPDSwatchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSwatch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSwatch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSwatch_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSwatch_get_swatchType(This,pVal)	\
    (This)->lpVtbl -> get_swatchType(This,pVal)

#define IPDSwatch_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDSwatch_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#define IPDSwatch_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDSwatch_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDSwatch_get_canDelete(This,pVal)	\
    (This)->lpVtbl -> get_canDelete(This,pVal)

#define IPDSwatch_get_canEdit(This,pVal)	\
    (This)->lpVtbl -> get_canEdit(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatch_get_swatchType_Proxy( 
    IPDSwatch __RPC_FAR * This,
    /* [retval][out] */ PDSwatchType __RPC_FAR *pVal);


void __RPC_STUB IPDSwatch_get_swatchType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatch_get_name_Proxy( 
    IPDSwatch __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDSwatch_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSwatch_put_name_Proxy( 
    IPDSwatch __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDSwatch_put_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatch_clone_Proxy( 
    IPDSwatch __RPC_FAR * This,
    /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatch_clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatch_get_parent_Proxy( 
    IPDSwatch __RPC_FAR * This,
    /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatch_get_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatch_get_canDelete_Proxy( 
    IPDSwatch __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDSwatch_get_canDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatch_get_canEdit_Proxy( 
    IPDSwatch __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDSwatch_get_canEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSwatch_INTERFACE_DEFINED__ */


#ifndef __IPDSwatchColor_INTERFACE_DEFINED__
#define __IPDSwatchColor_INTERFACE_DEFINED__

/* interface IPDSwatchColor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSwatchColor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E329F433-6771-46b7-A5DA-CC0E7F455CE4")
    IPDSwatchColor : public IPDSwatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_color( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_nameWithColorValue( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_nameWithColorValue( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_colorType( 
            /* [retval][out] */ PDColorType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_colorType( 
            /* [in] */ PDColorType newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSwatchColorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSwatchColor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSwatchColor __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatchType )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ PDSwatchType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canDelete )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canEdit )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_color )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nameWithColorValue )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nameWithColorValue )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_colorType )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [retval][out] */ PDColorType __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_colorType )( 
            IPDSwatchColor __RPC_FAR * This,
            /* [in] */ PDColorType newVal);
        
        END_INTERFACE
    } IPDSwatchColorVtbl;

    interface IPDSwatchColor
    {
        CONST_VTBL struct IPDSwatchColorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSwatchColor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSwatchColor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSwatchColor_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSwatchColor_get_swatchType(This,pVal)	\
    (This)->lpVtbl -> get_swatchType(This,pVal)

#define IPDSwatchColor_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDSwatchColor_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#define IPDSwatchColor_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDSwatchColor_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDSwatchColor_get_canDelete(This,pVal)	\
    (This)->lpVtbl -> get_canDelete(This,pVal)

#define IPDSwatchColor_get_canEdit(This,pVal)	\
    (This)->lpVtbl -> get_canEdit(This,pVal)


#define IPDSwatchColor_get_color(This,pVal)	\
    (This)->lpVtbl -> get_color(This,pVal)

#define IPDSwatchColor_get_nameWithColorValue(This,pVal)	\
    (This)->lpVtbl -> get_nameWithColorValue(This,pVal)

#define IPDSwatchColor_put_nameWithColorValue(This,newVal)	\
    (This)->lpVtbl -> put_nameWithColorValue(This,newVal)

#define IPDSwatchColor_get_colorType(This,pVal)	\
    (This)->lpVtbl -> get_colorType(This,pVal)

#define IPDSwatchColor_put_colorType(This,newVal)	\
    (This)->lpVtbl -> put_colorType(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchColor_get_color_Proxy( 
    IPDSwatchColor __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatchColor_get_color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchColor_get_nameWithColorValue_Proxy( 
    IPDSwatchColor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDSwatchColor_get_nameWithColorValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSwatchColor_put_nameWithColorValue_Proxy( 
    IPDSwatchColor __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDSwatchColor_put_nameWithColorValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchColor_get_colorType_Proxy( 
    IPDSwatchColor __RPC_FAR * This,
    /* [retval][out] */ PDColorType __RPC_FAR *pVal);


void __RPC_STUB IPDSwatchColor_get_colorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSwatchColor_put_colorType_Proxy( 
    IPDSwatchColor __RPC_FAR * This,
    /* [in] */ PDColorType newVal);


void __RPC_STUB IPDSwatchColor_put_colorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSwatchColor_INTERFACE_DEFINED__ */


#ifndef __IPDSwatchTint_INTERFACE_DEFINED__
#define __IPDSwatchTint_INTERFACE_DEFINED__

/* interface IPDSwatchTint */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSwatchTint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("097E1475-C4BC-422e-868F-EEE195576FB5")
    IPDSwatchTint : public IPDSwatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_tint( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_tint( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_swatchColor( 
            /* [retval][out] */ IPDSwatchColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_swatchColor( 
            /* [in] */ IPDSwatchColor __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_finalColor( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSwatchTintVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSwatchTint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSwatchTint __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatchType )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ PDSwatchType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canDelete )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canEdit )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tint )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_tint )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatchColor )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ IPDSwatchColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_swatchColor )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [in] */ IPDSwatchColor __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_finalColor )( 
            IPDSwatchTint __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDSwatchTintVtbl;

    interface IPDSwatchTint
    {
        CONST_VTBL struct IPDSwatchTintVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSwatchTint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSwatchTint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSwatchTint_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSwatchTint_get_swatchType(This,pVal)	\
    (This)->lpVtbl -> get_swatchType(This,pVal)

#define IPDSwatchTint_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDSwatchTint_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#define IPDSwatchTint_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDSwatchTint_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDSwatchTint_get_canDelete(This,pVal)	\
    (This)->lpVtbl -> get_canDelete(This,pVal)

#define IPDSwatchTint_get_canEdit(This,pVal)	\
    (This)->lpVtbl -> get_canEdit(This,pVal)


#define IPDSwatchTint_get_tint(This,pVal)	\
    (This)->lpVtbl -> get_tint(This,pVal)

#define IPDSwatchTint_put_tint(This,newVal)	\
    (This)->lpVtbl -> put_tint(This,newVal)

#define IPDSwatchTint_get_swatchColor(This,pVal)	\
    (This)->lpVtbl -> get_swatchColor(This,pVal)

#define IPDSwatchTint_put_swatchColor(This,newVal)	\
    (This)->lpVtbl -> put_swatchColor(This,newVal)

#define IPDSwatchTint_get_finalColor(This,pVal)	\
    (This)->lpVtbl -> get_finalColor(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchTint_get_tint_Proxy( 
    IPDSwatchTint __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDSwatchTint_get_tint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSwatchTint_put_tint_Proxy( 
    IPDSwatchTint __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDSwatchTint_put_tint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchTint_get_swatchColor_Proxy( 
    IPDSwatchTint __RPC_FAR * This,
    /* [retval][out] */ IPDSwatchColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatchTint_get_swatchColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSwatchTint_put_swatchColor_Proxy( 
    IPDSwatchTint __RPC_FAR * This,
    /* [in] */ IPDSwatchColor __RPC_FAR *newVal);


void __RPC_STUB IPDSwatchTint_put_swatchColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchTint_get_finalColor_Proxy( 
    IPDSwatchTint __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatchTint_get_finalColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSwatchTint_INTERFACE_DEFINED__ */


#ifndef __IPDSwatchGradient_INTERFACE_DEFINED__
#define __IPDSwatchGradient_INTERFACE_DEFINED__

/* interface IPDSwatchGradient */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSwatchGradient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C84E8609-C480-4b3e-8F86-F0DA49475E61")
    IPDSwatchGradient : public IPDSwatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_gradient( 
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_gradient( 
            /* [in] */ IPDGradient __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSwatchGradientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSwatchGradient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSwatchGradient __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatchType )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [retval][out] */ PDSwatchType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canDelete )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canEdit )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gradient )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gradient )( 
            IPDSwatchGradient __RPC_FAR * This,
            /* [in] */ IPDGradient __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDSwatchGradientVtbl;

    interface IPDSwatchGradient
    {
        CONST_VTBL struct IPDSwatchGradientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSwatchGradient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSwatchGradient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSwatchGradient_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSwatchGradient_get_swatchType(This,pVal)	\
    (This)->lpVtbl -> get_swatchType(This,pVal)

#define IPDSwatchGradient_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDSwatchGradient_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#define IPDSwatchGradient_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDSwatchGradient_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDSwatchGradient_get_canDelete(This,pVal)	\
    (This)->lpVtbl -> get_canDelete(This,pVal)

#define IPDSwatchGradient_get_canEdit(This,pVal)	\
    (This)->lpVtbl -> get_canEdit(This,pVal)


#define IPDSwatchGradient_get_gradient(This,pVal)	\
    (This)->lpVtbl -> get_gradient(This,pVal)

#define IPDSwatchGradient_put_gradient(This,newVal)	\
    (This)->lpVtbl -> put_gradient(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchGradient_get_gradient_Proxy( 
    IPDSwatchGradient __RPC_FAR * This,
    /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatchGradient_get_gradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSwatchGradient_put_gradient_Proxy( 
    IPDSwatchGradient __RPC_FAR * This,
    /* [in] */ IPDGradient __RPC_FAR *newVal);


void __RPC_STUB IPDSwatchGradient_put_gradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSwatchGradient_INTERFACE_DEFINED__ */


#ifndef __IPDSwatchPattern_INTERFACE_DEFINED__
#define __IPDSwatchPattern_INTERFACE_DEFINED__

/* interface IPDSwatchPattern */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSwatchPattern;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("99D2DAC7-CE4E-45BD-9C68-981820D3B094")
    IPDSwatchPattern : public IPDSwatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_objectGroup( 
            /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_objectGroup( 
            /* [in] */ IPDObjectGroup __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSwatchPatternVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSwatchPattern __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSwatchPattern __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatchType )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [retval][out] */ PDSwatchType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canDelete )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_canEdit )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectGroup )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_objectGroup )( 
            IPDSwatchPattern __RPC_FAR * This,
            /* [in] */ IPDObjectGroup __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDSwatchPatternVtbl;

    interface IPDSwatchPattern
    {
        CONST_VTBL struct IPDSwatchPatternVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSwatchPattern_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSwatchPattern_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSwatchPattern_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSwatchPattern_get_swatchType(This,pVal)	\
    (This)->lpVtbl -> get_swatchType(This,pVal)

#define IPDSwatchPattern_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDSwatchPattern_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#define IPDSwatchPattern_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDSwatchPattern_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDSwatchPattern_get_canDelete(This,pVal)	\
    (This)->lpVtbl -> get_canDelete(This,pVal)

#define IPDSwatchPattern_get_canEdit(This,pVal)	\
    (This)->lpVtbl -> get_canEdit(This,pVal)


#define IPDSwatchPattern_get_objectGroup(This,pVal)	\
    (This)->lpVtbl -> get_objectGroup(This,pVal)

#define IPDSwatchPattern_put_objectGroup(This,newVal)	\
    (This)->lpVtbl -> put_objectGroup(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatchPattern_get_objectGroup_Proxy( 
    IPDSwatchPattern __RPC_FAR * This,
    /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatchPattern_get_objectGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSwatchPattern_put_objectGroup_Proxy( 
    IPDSwatchPattern __RPC_FAR * This,
    /* [in] */ IPDObjectGroup __RPC_FAR *newVal);


void __RPC_STUB IPDSwatchPattern_put_objectGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSwatchPattern_INTERFACE_DEFINED__ */


#ifndef __IPDSwatches_INTERFACE_DEFINED__
#define __IPDSwatches_INTERFACE_DEFINED__

/* interface IPDSwatches */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSwatches;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F4A86041-ED11-11d5-95F0-0002E3045703")
    IPDSwatches : public IPDUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createSwatchColor( 
            /* [retval][out] */ IPDSwatchColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createSwatchGradient( 
            /* [retval][out] */ IPDSwatchGradient __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createSwatchTint( 
            /* [in] */ IPDSwatchColor __RPC_FAR *swatchColor,
            /* [retval][out] */ IPDSwatchTint __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE item( 
            /* [in] */ long index,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendSwatch( 
            /* [in] */ IPDSwatch __RPC_FAR *swatch) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeSwatch( 
            /* [in] */ IPDSwatch __RPC_FAR *swatch) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstChild( 
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastChild( 
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createSwatchPattern( 
            /* [retval][out] */ IPDSwatchPattern __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSwatchesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSwatches __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSwatches __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSwatches __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createSwatchColor )( 
            IPDSwatches __RPC_FAR * This,
            /* [retval][out] */ IPDSwatchColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createSwatchGradient )( 
            IPDSwatches __RPC_FAR * This,
            /* [retval][out] */ IPDSwatchGradient __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createSwatchTint )( 
            IPDSwatches __RPC_FAR * This,
            /* [in] */ IPDSwatchColor __RPC_FAR *swatchColor,
            /* [retval][out] */ IPDSwatchTint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IPDSwatches __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IPDSwatches __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendSwatch )( 
            IPDSwatches __RPC_FAR * This,
            /* [in] */ IPDSwatch __RPC_FAR *swatch);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeSwatch )( 
            IPDSwatches __RPC_FAR * This,
            /* [in] */ IPDSwatch __RPC_FAR *swatch);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDSwatches __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDSwatches __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createSwatchPattern )( 
            IPDSwatches __RPC_FAR * This,
            /* [retval][out] */ IPDSwatchPattern __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDSwatchesVtbl;

    interface IPDSwatches
    {
        CONST_VTBL struct IPDSwatchesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSwatches_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSwatches_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSwatches_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSwatches_createSwatchColor(This,pVal)	\
    (This)->lpVtbl -> createSwatchColor(This,pVal)

#define IPDSwatches_createSwatchGradient(This,pVal)	\
    (This)->lpVtbl -> createSwatchGradient(This,pVal)

#define IPDSwatches_createSwatchTint(This,swatchColor,pVal)	\
    (This)->lpVtbl -> createSwatchTint(This,swatchColor,pVal)

#define IPDSwatches_get_length(This,pVal)	\
    (This)->lpVtbl -> get_length(This,pVal)

#define IPDSwatches_item(This,index,pVal)	\
    (This)->lpVtbl -> item(This,index,pVal)

#define IPDSwatches_appendSwatch(This,swatch)	\
    (This)->lpVtbl -> appendSwatch(This,swatch)

#define IPDSwatches_removeSwatch(This,swatch)	\
    (This)->lpVtbl -> removeSwatch(This,swatch)

#define IPDSwatches_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDSwatches_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDSwatches_createSwatchPattern(This,pVal)	\
    (This)->lpVtbl -> createSwatchPattern(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatches_createSwatchColor_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [retval][out] */ IPDSwatchColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_createSwatchColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatches_createSwatchGradient_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [retval][out] */ IPDSwatchGradient __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_createSwatchGradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatches_createSwatchTint_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [in] */ IPDSwatchColor __RPC_FAR *swatchColor,
    /* [retval][out] */ IPDSwatchTint __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_createSwatchTint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatches_get_length_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatches_item_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatches_appendSwatch_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [in] */ IPDSwatch __RPC_FAR *swatch);


void __RPC_STUB IPDSwatches_appendSwatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatches_removeSwatch_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [in] */ IPDSwatch __RPC_FAR *swatch);


void __RPC_STUB IPDSwatches_removeSwatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatches_get_firstChild_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_get_firstChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSwatches_get_lastChild_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_get_lastChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSwatches_createSwatchPattern_Proxy( 
    IPDSwatches __RPC_FAR * This,
    /* [retval][out] */ IPDSwatchPattern __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSwatches_createSwatchPattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSwatches_INTERFACE_DEFINED__ */


#ifndef __IPDGradient_INTERFACE_DEFINED__
#define __IPDGradient_INTERFACE_DEFINED__

/* interface IPDGradient */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDGradient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4EC5DBE-5CB5-4aed-AA6A-EFEE6C4079A7")
    IPDGradient : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_stops( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE append( 
            /* [in] */ IPDGradientStop __RPC_FAR *stop) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createStop( 
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeStop( 
            /* [in] */ IPDGradientStop __RPC_FAR *stop) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstChild( 
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastChild( 
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Equals( 
            /* [in] */ IPDGradient __RPC_FAR *gradient,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [retval][out] */ PDGradientType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_type( 
            /* [in] */ PDGradientType newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE copy( 
            /* [in] */ IPDGradient __RPC_FAR *gradient) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDGradientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDGradient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDGradient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDGradient __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stops )( 
            IPDGradient __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *append )( 
            IPDGradient __RPC_FAR * This,
            /* [in] */ IPDGradientStop __RPC_FAR *stop);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createStop )( 
            IPDGradient __RPC_FAR * This,
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeStop )( 
            IPDGradient __RPC_FAR * This,
            /* [in] */ IPDGradientStop __RPC_FAR *stop);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDGradient __RPC_FAR * This,
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDGradient __RPC_FAR * This,
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Equals )( 
            IPDGradient __RPC_FAR * This,
            /* [in] */ IPDGradient __RPC_FAR *gradient,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDGradient __RPC_FAR * This,
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IPDGradient __RPC_FAR * This,
            /* [retval][out] */ PDGradientType __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_type )( 
            IPDGradient __RPC_FAR * This,
            /* [in] */ PDGradientType newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *copy )( 
            IPDGradient __RPC_FAR * This,
            /* [in] */ IPDGradient __RPC_FAR *gradient);
        
        END_INTERFACE
    } IPDGradientVtbl;

    interface IPDGradient
    {
        CONST_VTBL struct IPDGradientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDGradient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDGradient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDGradient_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDGradient_get_stops(This,pVal)	\
    (This)->lpVtbl -> get_stops(This,pVal)

#define IPDGradient_append(This,stop)	\
    (This)->lpVtbl -> append(This,stop)

#define IPDGradient_createStop(This,pVal)	\
    (This)->lpVtbl -> createStop(This,pVal)

#define IPDGradient_removeStop(This,stop)	\
    (This)->lpVtbl -> removeStop(This,stop)

#define IPDGradient_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDGradient_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDGradient_Equals(This,gradient,pVal)	\
    (This)->lpVtbl -> Equals(This,gradient,pVal)

#define IPDGradient_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDGradient_get_type(This,pVal)	\
    (This)->lpVtbl -> get_type(This,pVal)

#define IPDGradient_put_type(This,newVal)	\
    (This)->lpVtbl -> put_type(This,newVal)

#define IPDGradient_copy(This,gradient)	\
    (This)->lpVtbl -> copy(This,gradient)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradient_get_stops_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradient_get_stops_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradient_append_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [in] */ IPDGradientStop __RPC_FAR *stop);


void __RPC_STUB IPDGradient_append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradient_createStop_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradient_createStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradient_removeStop_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [in] */ IPDGradientStop __RPC_FAR *stop);


void __RPC_STUB IPDGradient_removeStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradient_get_firstChild_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradient_get_firstChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradient_get_lastChild_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradient_get_lastChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradient_Equals_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [in] */ IPDGradient __RPC_FAR *gradient,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDGradient_Equals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradient_clone_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradient_clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradient_get_type_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [retval][out] */ PDGradientType __RPC_FAR *pVal);


void __RPC_STUB IPDGradient_get_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDGradient_put_type_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [in] */ PDGradientType newVal);


void __RPC_STUB IPDGradient_put_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradient_copy_Proxy( 
    IPDGradient __RPC_FAR * This,
    /* [in] */ IPDGradient __RPC_FAR *gradient);


void __RPC_STUB IPDGradient_copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDGradient_INTERFACE_DEFINED__ */


#ifndef __IPDGradientStop_INTERFACE_DEFINED__
#define __IPDGradientStop_INTERFACE_DEFINED__

/* interface IPDGradientStop */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDGradientStop;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C2DFC862-2498-42e6-8261-C8D8D47D4827")
    IPDGradientStop : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_middle( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_middle( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_offset( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_offset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_color( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setColorRGB( 
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_parent( 
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_previousSibling( 
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_nextSibling( 
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_swatch( 
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_swatch( 
            /* [in] */ IPDSwatch __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getFinalColor( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDGradientStopVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDGradientStop __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDGradientStop __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDGradientStop __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_middle )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_middle )( 
            IPDGradientStop __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_offset )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_offset )( 
            IPDGradientStop __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_color )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setColorRGB )( 
            IPDGradientStop __RPC_FAR * This,
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatch )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_swatch )( 
            IPDGradientStop __RPC_FAR * This,
            /* [in] */ IPDSwatch __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getFinalColor )( 
            IPDGradientStop __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDGradientStopVtbl;

    interface IPDGradientStop
    {
        CONST_VTBL struct IPDGradientStopVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDGradientStop_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDGradientStop_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDGradientStop_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDGradientStop_get_middle(This,pVal)	\
    (This)->lpVtbl -> get_middle(This,pVal)

#define IPDGradientStop_put_middle(This,newVal)	\
    (This)->lpVtbl -> put_middle(This,newVal)

#define IPDGradientStop_get_offset(This,pVal)	\
    (This)->lpVtbl -> get_offset(This,pVal)

#define IPDGradientStop_put_offset(This,newVal)	\
    (This)->lpVtbl -> put_offset(This,newVal)

#define IPDGradientStop_get_color(This,pVal)	\
    (This)->lpVtbl -> get_color(This,pVal)

#define IPDGradientStop_setColorRGB(This,red,green,blue)	\
    (This)->lpVtbl -> setColorRGB(This,red,green,blue)

#define IPDGradientStop_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDGradientStop_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDGradientStop_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDGradientStop_get_swatch(This,pVal)	\
    (This)->lpVtbl -> get_swatch(This,pVal)

#define IPDGradientStop_put_swatch(This,newVal)	\
    (This)->lpVtbl -> put_swatch(This,newVal)

#define IPDGradientStop_getFinalColor(This,pVal)	\
    (This)->lpVtbl -> getFinalColor(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_get_middle_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_get_middle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_put_middle_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDGradientStop_put_middle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_get_offset_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_get_offset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_put_offset_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDGradientStop_put_offset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_get_color_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_get_color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_setColorRGB_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [in] */ long red,
    /* [in] */ long green,
    /* [in] */ long blue);


void __RPC_STUB IPDGradientStop_setColorRGB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_get_parent_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_get_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_get_previousSibling_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_get_previousSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_get_nextSibling_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ IPDGradientStop __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_get_nextSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_get_swatch_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_get_swatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_put_swatch_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [in] */ IPDSwatch __RPC_FAR *newVal);


void __RPC_STUB IPDGradientStop_put_swatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDGradientStop_getFinalColor_Proxy( 
    IPDGradientStop __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDGradientStop_getFinalColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDGradientStop_INTERFACE_DEFINED__ */


#ifndef __IPDBrush_INTERFACE_DEFINED__
#define __IPDBrush_INTERFACE_DEFINED__

/* interface IPDBrush */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDBrush;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27F17041-EEC5-11d5-95F0-0002E3045703")
    IPDBrush : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_brushType( 
            /* [retval][out] */ PDBrushType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_brushType( 
            /* [in] */ PDBrushType newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_swatch( 
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_swatch( 
            /* [in] */ IPDSwatch __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_gradient( 
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_color( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_colorTint( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_colorTint( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_tintedRGBColor( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setNone( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setGradient( 
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setColor( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_x1( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_x1( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_y1( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_y1( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_x2( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_x2( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_y2( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_y2( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_tintedColor( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEqual( 
            /* [in] */ IPDBrush __RPC_FAR *brush) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setCommon( 
            /* [in] */ IPDBrush __RPC_FAR *brush) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getCommon( 
            /* [in] */ IPDBrush __RPC_FAR *brush) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDBrushVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDBrush __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDBrush __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushType )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ PDBrushType __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushType )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ PDBrushType newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatch )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_swatch )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ IPDSwatch __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gradient )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_color )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_colorTint )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_colorTint )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tintedRGBColor )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setNone )( 
            IPDBrush __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setGradient )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setColor )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x1 )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_x1 )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y1 )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_y1 )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x2 )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_x2 )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y2 )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_y2 )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tintedColor )( 
            IPDBrush __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsEqual )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *brush);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setCommon )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *brush);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCommon )( 
            IPDBrush __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *brush);
        
        END_INTERFACE
    } IPDBrushVtbl;

    interface IPDBrush
    {
        CONST_VTBL struct IPDBrushVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDBrush_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDBrush_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDBrush_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDBrush_get_brushType(This,pVal)	\
    (This)->lpVtbl -> get_brushType(This,pVal)

#define IPDBrush_put_brushType(This,newVal)	\
    (This)->lpVtbl -> put_brushType(This,newVal)

#define IPDBrush_get_swatch(This,pVal)	\
    (This)->lpVtbl -> get_swatch(This,pVal)

#define IPDBrush_put_swatch(This,newVal)	\
    (This)->lpVtbl -> put_swatch(This,newVal)

#define IPDBrush_get_gradient(This,pVal)	\
    (This)->lpVtbl -> get_gradient(This,pVal)

#define IPDBrush_get_color(This,pVal)	\
    (This)->lpVtbl -> get_color(This,pVal)

#define IPDBrush_get_colorTint(This,pVal)	\
    (This)->lpVtbl -> get_colorTint(This,pVal)

#define IPDBrush_put_colorTint(This,newVal)	\
    (This)->lpVtbl -> put_colorTint(This,newVal)

#define IPDBrush_get_tintedRGBColor(This,pVal)	\
    (This)->lpVtbl -> get_tintedRGBColor(This,pVal)

#define IPDBrush_setNone(This)	\
    (This)->lpVtbl -> setNone(This)

#define IPDBrush_setGradient(This,pVal)	\
    (This)->lpVtbl -> setGradient(This,pVal)

#define IPDBrush_setColor(This,pVal)	\
    (This)->lpVtbl -> setColor(This,pVal)

#define IPDBrush_get_x1(This,pVal)	\
    (This)->lpVtbl -> get_x1(This,pVal)

#define IPDBrush_put_x1(This,newVal)	\
    (This)->lpVtbl -> put_x1(This,newVal)

#define IPDBrush_get_y1(This,pVal)	\
    (This)->lpVtbl -> get_y1(This,pVal)

#define IPDBrush_put_y1(This,newVal)	\
    (This)->lpVtbl -> put_y1(This,newVal)

#define IPDBrush_get_x2(This,pVal)	\
    (This)->lpVtbl -> get_x2(This,pVal)

#define IPDBrush_put_x2(This,newVal)	\
    (This)->lpVtbl -> put_x2(This,newVal)

#define IPDBrush_get_y2(This,pVal)	\
    (This)->lpVtbl -> get_y2(This,pVal)

#define IPDBrush_put_y2(This,newVal)	\
    (This)->lpVtbl -> put_y2(This,newVal)

#define IPDBrush_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDBrush_get_tintedColor(This,pVal)	\
    (This)->lpVtbl -> get_tintedColor(This,pVal)

#define IPDBrush_IsEqual(This,brush)	\
    (This)->lpVtbl -> IsEqual(This,brush)

#define IPDBrush_setCommon(This,brush)	\
    (This)->lpVtbl -> setCommon(This,brush)

#define IPDBrush_getCommon(This,brush)	\
    (This)->lpVtbl -> getCommon(This,brush)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_brushType_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ PDBrushType __RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_brushType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrush_put_brushType_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ PDBrushType newVal);


void __RPC_STUB IPDBrush_put_brushType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_swatch_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_swatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrush_put_swatch_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ IPDSwatch __RPC_FAR *newVal);


void __RPC_STUB IPDBrush_put_swatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_gradient_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_gradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_color_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_colorTint_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_colorTint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrush_put_colorTint_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrush_put_colorTint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_tintedRGBColor_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_tintedRGBColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrush_setNone_Proxy( 
    IPDBrush __RPC_FAR * This);


void __RPC_STUB IPDBrush_setNone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrush_setGradient_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_setGradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrush_setColor_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_setColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_x1_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_x1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrush_put_x1_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrush_put_x1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_y1_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_y1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrush_put_y1_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrush_put_y1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_x2_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_x2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrush_put_x2_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrush_put_x2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_y2_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_y2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrush_put_y2_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrush_put_y2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrush_clone_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrush_get_tintedColor_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrush_get_tintedColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrush_IsEqual_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ IPDBrush __RPC_FAR *brush);


void __RPC_STUB IPDBrush_IsEqual_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrush_setCommon_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ IPDBrush __RPC_FAR *brush);


void __RPC_STUB IPDBrush_setCommon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrush_getCommon_Proxy( 
    IPDBrush __RPC_FAR * This,
    /* [in] */ IPDBrush __RPC_FAR *brush);


void __RPC_STUB IPDBrush_getCommon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDBrush_INTERFACE_DEFINED__ */


#ifndef __IPDObjectWithBrush_INTERFACE_DEFINED__
#define __IPDObjectWithBrush_INTERFACE_DEFINED__

/* interface IPDObjectWithBrush */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectWithBrush;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C552AD1F-7EDA-4b23-9439-DED6C0265AD7")
    IPDObjectWithBrush : public IPDObject
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_brush( 
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_brush( 
            /* [in] */ IPDBrush __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectWithBrushVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectWithBrush __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectWithBrush __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brush )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brush )( 
            IPDObjectWithBrush __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDObjectWithBrushVtbl;

    interface IPDObjectWithBrush
    {
        CONST_VTBL struct IPDObjectWithBrushVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectWithBrush_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectWithBrush_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectWithBrush_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectWithBrush_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectWithBrush_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectWithBrush_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectWithBrush_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectWithBrush_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectWithBrush_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectWithBrush_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectWithBrush_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectWithBrush_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectWithBrush_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectWithBrush_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectWithBrush_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectWithBrush_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectWithBrush_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectWithBrush_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectWithBrush_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectWithBrush_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectWithBrush_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectWithBrush_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectWithBrush_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectWithBrush_get_brush(This,pVal)	\
    (This)->lpVtbl -> get_brush(This,pVal)

#define IPDObjectWithBrush_put_brush(This,newVal)	\
    (This)->lpVtbl -> put_brush(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithBrush_get_brush_Proxy( 
    IPDObjectWithBrush __RPC_FAR * This,
    /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithBrush_get_brush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithBrush_put_brush_Proxy( 
    IPDObjectWithBrush __RPC_FAR * This,
    /* [in] */ IPDBrush __RPC_FAR *newVal);


void __RPC_STUB IPDObjectWithBrush_put_brush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectWithBrush_INTERFACE_DEFINED__ */


#ifndef __IPDObjectStroke_INTERFACE_DEFINED__
#define __IPDObjectStroke_INTERFACE_DEFINED__

/* interface IPDObjectStroke */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectStroke;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4835BA71-ED77-4E51-A05E-0AC693849A64")
    IPDObjectStroke : public IPDObjectWithBrush
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectStrokeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectStroke __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectStroke __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brush )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brush )( 
            IPDObjectStroke __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDObjectStrokeVtbl;

    interface IPDObjectStroke
    {
        CONST_VTBL struct IPDObjectStrokeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectStroke_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectStroke_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectStroke_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectStroke_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectStroke_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectStroke_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectStroke_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectStroke_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectStroke_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectStroke_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectStroke_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectStroke_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectStroke_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectStroke_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectStroke_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectStroke_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectStroke_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectStroke_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectStroke_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectStroke_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectStroke_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectStroke_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectStroke_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectStroke_get_brush(This,pVal)	\
    (This)->lpVtbl -> get_brush(This,pVal)

#define IPDObjectStroke_put_brush(This,newVal)	\
    (This)->lpVtbl -> put_brush(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPDObjectStroke_INTERFACE_DEFINED__ */


#ifndef __IPDObjectFill_INTERFACE_DEFINED__
#define __IPDObjectFill_INTERFACE_DEFINED__

/* interface IPDObjectFill */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectFill;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36494C03-75E7-4264-B442-E126171CB20E")
    IPDObjectFill : public IPDObjectWithBrush
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectFillVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectFill __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectFill __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brush )( 
            IPDObjectFill __RPC_FAR * This,
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brush )( 
            IPDObjectFill __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDObjectFillVtbl;

    interface IPDObjectFill
    {
        CONST_VTBL struct IPDObjectFillVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectFill_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectFill_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectFill_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectFill_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectFill_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectFill_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectFill_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectFill_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectFill_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectFill_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectFill_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectFill_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectFill_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectFill_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectFill_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectFill_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectFill_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectFill_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectFill_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectFill_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectFill_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectFill_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectFill_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectFill_get_brush(This,pVal)	\
    (This)->lpVtbl -> get_brush(This,pVal)

#define IPDObjectFill_put_brush(This,newVal)	\
    (This)->lpVtbl -> put_brush(This,newVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPDObjectFill_INTERFACE_DEFINED__ */


#ifndef __IPDStory_INTERFACE_DEFINED__
#define __IPDStory_INTERFACE_DEFINED__

/* interface IPDStory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDStory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A790F0E6-2DE1-4873-8690-0FC6D9F24797")
    IPDStory : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_textDocument( 
            /* [retval][out] */ ILDOMDocument __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_textDocument( 
            /* [in] */ ILDOMDocument __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_textContents( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstTextThread( 
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastTextThread( 
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendTextThread( 
            /* [in] */ IPDObjectText __RPC_FAR *node) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertTextThreadBefore( 
            /* [in] */ IPDObjectText __RPC_FAR *node,
            /* [in] */ IPDObjectText __RPC_FAR *before) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeTextThread( 
            /* [in] */ IPDObjectText __RPC_FAR *node) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_inlineObjects( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendInlineObject( 
            /* [in] */ IPDObject __RPC_FAR *object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getInlineObjectById( 
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTextFont( 
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [retval][out] */ IPDTextFont __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTextFont( 
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [in] */ IPDTextFont __RPC_FAR *textFont) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTextPara( 
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [retval][out] */ IPDTextPara __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTextPara( 
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [in] */ IPDTextPara __RPC_FAR *textPara) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewRange( 
            /* [retval][out] */ IPDTextRange __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetObjectTextFromRangePosition( 
            /* [in] */ ILDOMNode __RPC_FAR *container,
            /* [in] */ long offset,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewSelection( 
            /* [retval][out] */ IPDTextSelection __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDStoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDStory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDStory __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_textDocument )( 
            IPDStory __RPC_FAR * This,
            /* [retval][out] */ ILDOMDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_textDocument )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ ILDOMDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_textContents )( 
            IPDStory __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstTextThread )( 
            IPDStory __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastTextThread )( 
            IPDStory __RPC_FAR * This,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendTextThread )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *node);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertTextThreadBefore )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *node,
            /* [in] */ IPDObjectText __RPC_FAR *before);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeTextThread )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDObjectText __RPC_FAR *node);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_inlineObjects )( 
            IPDStory __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendInlineObject )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getInlineObjectById )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTextFont )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [retval][out] */ IPDTextFont __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTextFont )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [in] */ IPDTextFont __RPC_FAR *textFont);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTextPara )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [retval][out] */ IPDTextPara __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTextPara )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ IPDTextRange __RPC_FAR *range,
            /* [in] */ IPDTextPara __RPC_FAR *textPara);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewRange )( 
            IPDStory __RPC_FAR * This,
            /* [retval][out] */ IPDTextRange __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectTextFromRangePosition )( 
            IPDStory __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *container,
            /* [in] */ long offset,
            /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewSelection )( 
            IPDStory __RPC_FAR * This,
            /* [retval][out] */ IPDTextSelection __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDStoryVtbl;

    interface IPDStory
    {
        CONST_VTBL struct IPDStoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDStory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDStory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDStory_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDStory_get_textDocument(This,pVal)	\
    (This)->lpVtbl -> get_textDocument(This,pVal)

#define IPDStory_put_textDocument(This,newVal)	\
    (This)->lpVtbl -> put_textDocument(This,newVal)

#define IPDStory_get_textContents(This,pVal)	\
    (This)->lpVtbl -> get_textContents(This,pVal)

#define IPDStory_get_firstTextThread(This,pVal)	\
    (This)->lpVtbl -> get_firstTextThread(This,pVal)

#define IPDStory_get_lastTextThread(This,pVal)	\
    (This)->lpVtbl -> get_lastTextThread(This,pVal)

#define IPDStory_appendTextThread(This,node)	\
    (This)->lpVtbl -> appendTextThread(This,node)

#define IPDStory_insertTextThreadBefore(This,node,before)	\
    (This)->lpVtbl -> insertTextThreadBefore(This,node,before)

#define IPDStory_removeTextThread(This,node)	\
    (This)->lpVtbl -> removeTextThread(This,node)

#define IPDStory_get_inlineObjects(This,pVal)	\
    (This)->lpVtbl -> get_inlineObjects(This,pVal)

#define IPDStory_appendInlineObject(This,object)	\
    (This)->lpVtbl -> appendInlineObject(This,object)

#define IPDStory_getInlineObjectById(This,guid,pVal)	\
    (This)->lpVtbl -> getInlineObjectById(This,guid,pVal)

#define IPDStory_GetTextFont(This,range,pVal)	\
    (This)->lpVtbl -> GetTextFont(This,range,pVal)

#define IPDStory_SetTextFont(This,range,textFont)	\
    (This)->lpVtbl -> SetTextFont(This,range,textFont)

#define IPDStory_GetTextPara(This,range,pVal)	\
    (This)->lpVtbl -> GetTextPara(This,range,pVal)

#define IPDStory_SetTextPara(This,range,textPara)	\
    (This)->lpVtbl -> SetTextPara(This,range,textPara)

#define IPDStory_NewRange(This,pVal)	\
    (This)->lpVtbl -> NewRange(This,pVal)

#define IPDStory_GetObjectTextFromRangePosition(This,container,offset,pVal)	\
    (This)->lpVtbl -> GetObjectTextFromRangePosition(This,container,offset,pVal)

#define IPDStory_NewSelection(This,pVal)	\
    (This)->lpVtbl -> NewSelection(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStory_get_textDocument_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [retval][out] */ ILDOMDocument __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_get_textDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDStory_put_textDocument_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ ILDOMDocument __RPC_FAR *newVal);


void __RPC_STUB IPDStory_put_textDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStory_get_textContents_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_get_textContents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStory_get_firstTextThread_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_get_firstTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStory_get_lastTextThread_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_get_lastTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_appendTextThread_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDObjectText __RPC_FAR *node);


void __RPC_STUB IPDStory_appendTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_insertTextThreadBefore_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDObjectText __RPC_FAR *node,
    /* [in] */ IPDObjectText __RPC_FAR *before);


void __RPC_STUB IPDStory_insertTextThreadBefore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_removeTextThread_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDObjectText __RPC_FAR *node);


void __RPC_STUB IPDStory_removeTextThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStory_get_inlineObjects_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_get_inlineObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_appendInlineObject_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDObject __RPC_FAR *object);


void __RPC_STUB IPDStory_appendInlineObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_getInlineObjectById_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ GUID guid,
    /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_getInlineObjectById_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_GetTextFont_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDTextRange __RPC_FAR *range,
    /* [retval][out] */ IPDTextFont __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_GetTextFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_SetTextFont_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDTextRange __RPC_FAR *range,
    /* [in] */ IPDTextFont __RPC_FAR *textFont);


void __RPC_STUB IPDStory_SetTextFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_GetTextPara_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDTextRange __RPC_FAR *range,
    /* [retval][out] */ IPDTextPara __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_GetTextPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_SetTextPara_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ IPDTextRange __RPC_FAR *range,
    /* [in] */ IPDTextPara __RPC_FAR *textPara);


void __RPC_STUB IPDStory_SetTextPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_NewRange_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [retval][out] */ IPDTextRange __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_NewRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_GetObjectTextFromRangePosition_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [in] */ ILDOMNode __RPC_FAR *container,
    /* [in] */ long offset,
    /* [retval][out] */ IPDObjectText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_GetObjectTextFromRangePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStory_NewSelection_Proxy( 
    IPDStory __RPC_FAR * This,
    /* [retval][out] */ IPDTextSelection __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDStory_NewSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDStory_INTERFACE_DEFINED__ */


#ifndef __IPDObjectWithChildren_INTERFACE_DEFINED__
#define __IPDObjectWithChildren_INTERFACE_DEFINED__

/* interface IPDObjectWithChildren */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectWithChildren;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E148D302-205A-11d6-95F0-0002E3045703")
    IPDObjectWithChildren : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_children( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstChild( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastChild( 
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectWithChildrenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectWithChildren __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectWithChildren __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectWithChildren __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectWithChildren __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectWithChildren __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectWithChildren __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDObjectWithChildrenVtbl;

    interface IPDObjectWithChildren
    {
        CONST_VTBL struct IPDObjectWithChildrenVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectWithChildren_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectWithChildren_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectWithChildren_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDObjectWithChildren_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectWithChildren_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectWithChildren_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithChildren_get_children_Proxy( 
    IPDObjectWithChildren __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithChildren_get_children_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithChildren_get_firstChild_Proxy( 
    IPDObjectWithChildren __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithChildren_get_firstChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithChildren_get_lastChild_Proxy( 
    IPDObjectWithChildren __RPC_FAR * This,
    /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithChildren_get_lastChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectWithChildren_INTERFACE_DEFINED__ */


#ifndef __IPDAppearance_INTERFACE_DEFINED__
#define __IPDAppearance_INTERFACE_DEFINED__

/* interface IPDAppearance */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDAppearance;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64FC9301-2874-11d6-95F0-0002E3045703")
    IPDAppearance : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_filterEffects( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstChild( 
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastChild( 
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertEffect( 
            /* [in] */ IPDFilterPrimitive __RPC_FAR *object,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *before) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeEffect( 
            /* [in] */ IPDFilterPrimitive __RPC_FAR *object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEqual( 
            /* [in] */ IPDAppearance __RPC_FAR *appearance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDAppearanceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDAppearance __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDAppearance __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDAppearance __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_filterEffects )( 
            IPDAppearance __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDAppearance __RPC_FAR * This,
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDAppearance __RPC_FAR * This,
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertEffect )( 
            IPDAppearance __RPC_FAR * This,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *object,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *before);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeEffect )( 
            IPDAppearance __RPC_FAR * This,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsEqual )( 
            IPDAppearance __RPC_FAR * This,
            /* [in] */ IPDAppearance __RPC_FAR *appearance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDAppearance __RPC_FAR * This,
            /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDAppearanceVtbl;

    interface IPDAppearance
    {
        CONST_VTBL struct IPDAppearanceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDAppearance_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDAppearance_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDAppearance_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDAppearance_get_filterEffects(This,pVal)	\
    (This)->lpVtbl -> get_filterEffects(This,pVal)

#define IPDAppearance_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDAppearance_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDAppearance_insertEffect(This,object,before)	\
    (This)->lpVtbl -> insertEffect(This,object,before)

#define IPDAppearance_removeEffect(This,object)	\
    (This)->lpVtbl -> removeEffect(This,object)

#define IPDAppearance_IsEqual(This,appearance)	\
    (This)->lpVtbl -> IsEqual(This,appearance)

#define IPDAppearance_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDAppearance_get_filterEffects_Proxy( 
    IPDAppearance __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDAppearance_get_filterEffects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDAppearance_get_firstChild_Proxy( 
    IPDAppearance __RPC_FAR * This,
    /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDAppearance_get_firstChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDAppearance_get_lastChild_Proxy( 
    IPDAppearance __RPC_FAR * This,
    /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDAppearance_get_lastChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDAppearance_insertEffect_Proxy( 
    IPDAppearance __RPC_FAR * This,
    /* [in] */ IPDFilterPrimitive __RPC_FAR *object,
    /* [in] */ IPDFilterPrimitive __RPC_FAR *before);


void __RPC_STUB IPDAppearance_insertEffect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDAppearance_removeEffect_Proxy( 
    IPDAppearance __RPC_FAR * This,
    /* [in] */ IPDFilterPrimitive __RPC_FAR *object);


void __RPC_STUB IPDAppearance_removeEffect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDAppearance_IsEqual_Proxy( 
    IPDAppearance __RPC_FAR * This,
    /* [in] */ IPDAppearance __RPC_FAR *appearance);


void __RPC_STUB IPDAppearance_IsEqual_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDAppearance_clone_Proxy( 
    IPDAppearance __RPC_FAR * This,
    /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDAppearance_clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDAppearance_INTERFACE_DEFINED__ */


#ifndef __IPDTextRange_INTERFACE_DEFINED__
#define __IPDTextRange_INTERFACE_DEFINED__

/* interface IPDTextRange */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDTextRange;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6CF071C1-2712-11d6-95F0-0002E3045703")
    IPDTextRange : public IPDUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDOMRange( 
            /* [retval][out] */ ILDOMRange __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStory( 
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *pDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsCollapsed( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDTextRangeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDTextRange __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDTextRange __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDTextRange __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDOMRange )( 
            IPDTextRange __RPC_FAR * This,
            /* [retval][out] */ ILDOMRange __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStory )( 
            IPDTextRange __RPC_FAR * This,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IPDTextRange __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCollapsed )( 
            IPDTextRange __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDTextRangeVtbl;

    interface IPDTextRange
    {
        CONST_VTBL struct IPDTextRangeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDTextRange_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDTextRange_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDTextRange_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDTextRange_GetDOMRange(This,pVal)	\
    (This)->lpVtbl -> GetDOMRange(This,pVal)

#define IPDTextRange_GetStory(This,pVal)	\
    (This)->lpVtbl -> GetStory(This,pVal)

#define IPDTextRange_Delete(This,Unit,Count,pDelta)	\
    (This)->lpVtbl -> Delete(This,Unit,Count,pDelta)

#define IPDTextRange_IsCollapsed(This,pVal)	\
    (This)->lpVtbl -> IsCollapsed(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextRange_GetDOMRange_Proxy( 
    IPDTextRange __RPC_FAR * This,
    /* [retval][out] */ ILDOMRange __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDTextRange_GetDOMRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextRange_GetStory_Proxy( 
    IPDTextRange __RPC_FAR * This,
    /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDTextRange_GetStory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextRange_Delete_Proxy( 
    IPDTextRange __RPC_FAR * This,
    /* [in] */ long Unit,
    /* [in] */ long Count,
    /* [retval][out] */ long __RPC_FAR *pDelta);


void __RPC_STUB IPDTextRange_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextRange_IsCollapsed_Proxy( 
    IPDTextRange __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDTextRange_IsCollapsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDTextRange_INTERFACE_DEFINED__ */


#ifndef __IPDTextFont_INTERFACE_DEFINED__
#define __IPDTextFont_INTERFACE_DEFINED__

/* interface IPDTextFont */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDTextFont;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("182779E1-22DF-11d6-95F0-0002E3045703")
    IPDTextFont : public IPDUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSize( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineHeight( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSize( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_strokeBrush( 
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_strokeBrush( 
            /* [in] */ IPDBrush __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_fillBrush( 
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_fillBrush( 
            /* [in] */ IPDBrush __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDTextFontVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDTextFont __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDTextFont __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDTextFont __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IPDTextFont __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IPDTextFont __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IPDTextFont __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLineHeight )( 
            IPDTextFont __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSize )( 
            IPDTextFont __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strokeBrush )( 
            IPDTextFont __RPC_FAR * This,
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strokeBrush )( 
            IPDTextFont __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fillBrush )( 
            IPDTextFont __RPC_FAR * This,
            /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_fillBrush )( 
            IPDTextFont __RPC_FAR * This,
            /* [in] */ IPDBrush __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDTextFontVtbl;

    interface IPDTextFont
    {
        CONST_VTBL struct IPDTextFontVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDTextFont_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDTextFont_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDTextFont_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDTextFont_GetName(This,pVal)	\
    (This)->lpVtbl -> GetName(This,pVal)

#define IPDTextFont_GetSize(This,pVal)	\
    (This)->lpVtbl -> GetSize(This,pVal)

#define IPDTextFont_SetName(This,newVal)	\
    (This)->lpVtbl -> SetName(This,newVal)

#define IPDTextFont_GetLineHeight(This,pVal)	\
    (This)->lpVtbl -> GetLineHeight(This,pVal)

#define IPDTextFont_SetSize(This,newVal)	\
    (This)->lpVtbl -> SetSize(This,newVal)

#define IPDTextFont_get_strokeBrush(This,pVal)	\
    (This)->lpVtbl -> get_strokeBrush(This,pVal)

#define IPDTextFont_put_strokeBrush(This,newVal)	\
    (This)->lpVtbl -> put_strokeBrush(This,newVal)

#define IPDTextFont_get_fillBrush(This,pVal)	\
    (This)->lpVtbl -> get_fillBrush(This,pVal)

#define IPDTextFont_put_fillBrush(This,newVal)	\
    (This)->lpVtbl -> put_fillBrush(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextFont_GetName_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDTextFont_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextFont_GetSize_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPDTextFont_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextFont_SetName_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDTextFont_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextFont_GetLineHeight_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPDTextFont_GetLineHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextFont_SetSize_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IPDTextFont_SetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFont_get_strokeBrush_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDTextFont_get_strokeBrush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextFont_put_strokeBrush_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [in] */ IPDBrush __RPC_FAR *newVal);


void __RPC_STUB IPDTextFont_put_strokeBrush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFont_get_fillBrush_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [retval][out] */ IPDBrush __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDTextFont_get_fillBrush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextFont_put_fillBrush_Proxy( 
    IPDTextFont __RPC_FAR * This,
    /* [in] */ IPDBrush __RPC_FAR *newVal);


void __RPC_STUB IPDTextFont_put_fillBrush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDTextFont_INTERFACE_DEFINED__ */


#ifndef __IPDTextPara_INTERFACE_DEFINED__
#define __IPDTextPara_INTERFACE_DEFINED__

/* interface IPDTextPara */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDTextPara;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("182779E2-22DF-11d6-95F0-0002E3045703")
    IPDTextPara : public IPDUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAlignment( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddTab( 
            /* [in] */ float tbPos,
            /* [in] */ long tbAlign,
            /* [in] */ long tbLeader) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearAllTabs( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteTab( 
            /* [in] */ float tbPos) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTabCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTab( 
            /* [in] */ long iTab,
            /* [out] */ float __RPC_FAR *ptbPos,
            /* [out] */ long __RPC_FAR *ptbAlign,
            /* [out] */ long __RPC_FAR *ptbLeader) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFirstLineIndent( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetIndents( 
            /* [in] */ float first,
            /* [in] */ float left,
            /* [in] */ float right) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRightIndent( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRightIndent( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLeftIndent( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRange( 
            /* [retval][out] */ IPDTextRange __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTabPos( 
            /* [in] */ long iTab,
            /* [in] */ float tbPos,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAlignment( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_dropCapLines( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_dropCapLines( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_dropCapChars( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_dropCapChars( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddTabEx( 
            /* [in] */ float tbPos,
            /* [in] */ long tbAlign,
            /* [in] */ long tbLeader,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDTextParaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDTextPara __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDTextPara __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlignment )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTab )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ float tbPos,
            /* [in] */ long tbAlign,
            /* [in] */ long tbLeader);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearAllTabs )( 
            IPDTextPara __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteTab )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ float tbPos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTabCount )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTab )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ long iTab,
            /* [out] */ float __RPC_FAR *ptbPos,
            /* [out] */ long __RPC_FAR *ptbAlign,
            /* [out] */ long __RPC_FAR *ptbLeader);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstLineIndent )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIndents )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ float first,
            /* [in] */ float left,
            /* [in] */ float right);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRightIndent )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightIndent )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftIndent )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRange )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ IPDTextRange __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTabPos )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ long iTab,
            /* [in] */ float tbPos,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlignment )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dropCapLines )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dropCapLines )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dropCapChars )( 
            IPDTextPara __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dropCapChars )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTabEx )( 
            IPDTextPara __RPC_FAR * This,
            /* [in] */ float tbPos,
            /* [in] */ long tbAlign,
            /* [in] */ long tbLeader,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDTextParaVtbl;

    interface IPDTextPara
    {
        CONST_VTBL struct IPDTextParaVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDTextPara_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDTextPara_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDTextPara_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDTextPara_GetAlignment(This,pVal)	\
    (This)->lpVtbl -> GetAlignment(This,pVal)

#define IPDTextPara_AddTab(This,tbPos,tbAlign,tbLeader)	\
    (This)->lpVtbl -> AddTab(This,tbPos,tbAlign,tbLeader)

#define IPDTextPara_ClearAllTabs(This)	\
    (This)->lpVtbl -> ClearAllTabs(This)

#define IPDTextPara_DeleteTab(This,tbPos)	\
    (This)->lpVtbl -> DeleteTab(This,tbPos)

#define IPDTextPara_GetTabCount(This,pVal)	\
    (This)->lpVtbl -> GetTabCount(This,pVal)

#define IPDTextPara_GetTab(This,iTab,ptbPos,ptbAlign,ptbLeader)	\
    (This)->lpVtbl -> GetTab(This,iTab,ptbPos,ptbAlign,ptbLeader)

#define IPDTextPara_GetFirstLineIndent(This,pVal)	\
    (This)->lpVtbl -> GetFirstLineIndent(This,pVal)

#define IPDTextPara_SetIndents(This,first,left,right)	\
    (This)->lpVtbl -> SetIndents(This,first,left,right)

#define IPDTextPara_SetRightIndent(This,newVal)	\
    (This)->lpVtbl -> SetRightIndent(This,newVal)

#define IPDTextPara_GetRightIndent(This,pVal)	\
    (This)->lpVtbl -> GetRightIndent(This,pVal)

#define IPDTextPara_GetLeftIndent(This,pVal)	\
    (This)->lpVtbl -> GetLeftIndent(This,pVal)

#define IPDTextPara_GetRange(This,pVal)	\
    (This)->lpVtbl -> GetRange(This,pVal)

#define IPDTextPara_SetTabPos(This,iTab,tbPos,pVal)	\
    (This)->lpVtbl -> SetTabPos(This,iTab,tbPos,pVal)

#define IPDTextPara_SetAlignment(This,newVal)	\
    (This)->lpVtbl -> SetAlignment(This,newVal)

#define IPDTextPara_get_dropCapLines(This,pVal)	\
    (This)->lpVtbl -> get_dropCapLines(This,pVal)

#define IPDTextPara_put_dropCapLines(This,newVal)	\
    (This)->lpVtbl -> put_dropCapLines(This,newVal)

#define IPDTextPara_get_dropCapChars(This,pVal)	\
    (This)->lpVtbl -> get_dropCapChars(This,pVal)

#define IPDTextPara_put_dropCapChars(This,newVal)	\
    (This)->lpVtbl -> put_dropCapChars(This,newVal)

#define IPDTextPara_AddTabEx(This,tbPos,tbAlign,tbLeader,pVal)	\
    (This)->lpVtbl -> AddTabEx(This,tbPos,tbAlign,tbLeader,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_GetAlignment_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_GetAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_AddTab_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ float tbPos,
    /* [in] */ long tbAlign,
    /* [in] */ long tbLeader);


void __RPC_STUB IPDTextPara_AddTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_ClearAllTabs_Proxy( 
    IPDTextPara __RPC_FAR * This);


void __RPC_STUB IPDTextPara_ClearAllTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_DeleteTab_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ float tbPos);


void __RPC_STUB IPDTextPara_DeleteTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_GetTabCount_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_GetTabCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_GetTab_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ long iTab,
    /* [out] */ float __RPC_FAR *ptbPos,
    /* [out] */ long __RPC_FAR *ptbAlign,
    /* [out] */ long __RPC_FAR *ptbLeader);


void __RPC_STUB IPDTextPara_GetTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_GetFirstLineIndent_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_GetFirstLineIndent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_SetIndents_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ float first,
    /* [in] */ float left,
    /* [in] */ float right);


void __RPC_STUB IPDTextPara_SetIndents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_SetRightIndent_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IPDTextPara_SetRightIndent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_GetRightIndent_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_GetRightIndent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_GetLeftIndent_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_GetLeftIndent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_GetRange_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ IPDTextRange __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_GetRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_SetTabPos_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ long iTab,
    /* [in] */ float tbPos,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_SetTabPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_SetAlignment_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDTextPara_SetAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextPara_get_dropCapLines_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_get_dropCapLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextPara_put_dropCapLines_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDTextPara_put_dropCapLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextPara_get_dropCapChars_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_get_dropCapChars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextPara_put_dropCapChars_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDTextPara_put_dropCapChars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextPara_AddTabEx_Proxy( 
    IPDTextPara __RPC_FAR * This,
    /* [in] */ float tbPos,
    /* [in] */ long tbAlign,
    /* [in] */ long tbLeader,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDTextPara_AddTabEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDTextPara_INTERFACE_DEFINED__ */


#ifndef __IPDRenderer_INTERFACE_DEFINED__
#define __IPDRenderer_INTERFACE_DEFINED__

/* interface IPDRenderer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPDRenderer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F07DD9C5-0D81-4BD7-A5DD-1F1F1000072B")
    IPDRenderer : public IDispatch
    {
    public:
        virtual /* [helpstring][local][id][propget] */ HRESULT STDMETHODCALLTYPE get_targetHDC( 
            /* [retval][out] */ HDC __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][local][id][propput] */ HRESULT STDMETHODCALLTYPE put_targetHDC( 
            /* [in] */ HDC newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenderSpread( 
            /* [in] */ IPDSpread __RPC_FAR *spread,
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double width,
            /* [in] */ double height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenderGuide( 
            /* [in] */ IPDSpread __RPC_FAR *spread,
            /* [in] */ IPDGuide __RPC_FAR *guide,
            /* [in] */ DWORD color,
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double width,
            /* [in] */ double height) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_magnify( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_magnify( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenderSpreadBackground( 
            /* [in] */ IPDSpread __RPC_FAR *ispread) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddCustomRenderer( 
            /* [in] */ IPDCustomRenderer __RPC_FAR *customRenderer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenderObject( 
            /* [in] */ IPDObject __RPC_FAR *object) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDRendererVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDRenderer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDRenderer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPDRenderer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][local][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_targetHDC )( 
            IPDRenderer __RPC_FAR * This,
            /* [retval][out] */ HDC __RPC_FAR *pVal);
        
        /* [helpstring][local][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_targetHDC )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ HDC newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderSpread )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *spread,
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double width,
            /* [in] */ double height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderGuide )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *spread,
            /* [in] */ IPDGuide __RPC_FAR *guide,
            /* [in] */ DWORD color,
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double width,
            /* [in] */ double height);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_magnify )( 
            IPDRenderer __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_magnify )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderSpreadBackground )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *ispread);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddCustomRenderer )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ IPDCustomRenderer __RPC_FAR *customRenderer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderObject )( 
            IPDRenderer __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *object);
        
        END_INTERFACE
    } IPDRendererVtbl;

    interface IPDRenderer
    {
        CONST_VTBL struct IPDRendererVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDRenderer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDRenderer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDRenderer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDRenderer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPDRenderer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPDRenderer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPDRenderer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPDRenderer_get_targetHDC(This,pVal)	\
    (This)->lpVtbl -> get_targetHDC(This,pVal)

#define IPDRenderer_put_targetHDC(This,newVal)	\
    (This)->lpVtbl -> put_targetHDC(This,newVal)

#define IPDRenderer_RenderSpread(This,spread,left,top,width,height)	\
    (This)->lpVtbl -> RenderSpread(This,spread,left,top,width,height)

#define IPDRenderer_RenderGuide(This,spread,guide,color,left,top,width,height)	\
    (This)->lpVtbl -> RenderGuide(This,spread,guide,color,left,top,width,height)

#define IPDRenderer_get_magnify(This,pVal)	\
    (This)->lpVtbl -> get_magnify(This,pVal)

#define IPDRenderer_put_magnify(This,newVal)	\
    (This)->lpVtbl -> put_magnify(This,newVal)

#define IPDRenderer_RenderSpreadBackground(This,ispread)	\
    (This)->lpVtbl -> RenderSpreadBackground(This,ispread)

#define IPDRenderer_AddCustomRenderer(This,customRenderer)	\
    (This)->lpVtbl -> AddCustomRenderer(This,customRenderer)

#define IPDRenderer_RenderObject(This,object)	\
    (This)->lpVtbl -> RenderObject(This,object)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][local][id][propget] */ HRESULT STDMETHODCALLTYPE IPDRenderer_get_targetHDC_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [retval][out] */ HDC __RPC_FAR *pVal);


void __RPC_STUB IPDRenderer_get_targetHDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][local][id][propput] */ HRESULT STDMETHODCALLTYPE IPDRenderer_put_targetHDC_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [in] */ HDC newVal);


void __RPC_STUB IPDRenderer_put_targetHDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDRenderer_RenderSpread_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [in] */ IPDSpread __RPC_FAR *spread,
    /* [in] */ double left,
    /* [in] */ double top,
    /* [in] */ double width,
    /* [in] */ double height);


void __RPC_STUB IPDRenderer_RenderSpread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDRenderer_RenderGuide_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [in] */ IPDSpread __RPC_FAR *spread,
    /* [in] */ IPDGuide __RPC_FAR *guide,
    /* [in] */ DWORD color,
    /* [in] */ double left,
    /* [in] */ double top,
    /* [in] */ double width,
    /* [in] */ double height);


void __RPC_STUB IPDRenderer_RenderGuide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPDRenderer_get_magnify_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDRenderer_get_magnify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPDRenderer_put_magnify_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDRenderer_put_magnify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDRenderer_RenderSpreadBackground_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [in] */ IPDSpread __RPC_FAR *ispread);


void __RPC_STUB IPDRenderer_RenderSpreadBackground_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDRenderer_AddCustomRenderer_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [in] */ IPDCustomRenderer __RPC_FAR *customRenderer);


void __RPC_STUB IPDRenderer_AddCustomRenderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDRenderer_RenderObject_Proxy( 
    IPDRenderer __RPC_FAR * This,
    /* [in] */ IPDObject __RPC_FAR *object);


void __RPC_STUB IPDRenderer_RenderObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDRenderer_INTERFACE_DEFINED__ */


#ifndef __IPDFilterPrimitive_INTERFACE_DEFINED__
#define __IPDFilterPrimitive_INTERFACE_DEFINED__

/* interface IPDFilterPrimitive */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDFilterPrimitive;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74917DB6-0FF9-43cd-897E-13FE1205A4F9")
    IPDFilterPrimitive : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_nextSibling( 
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_nextSibling( 
            /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_previousSibling( 
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_previousSibling( 
            /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_parent( 
            /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_parent( 
            /* [in] */ IPDAppearance __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pluginFilter( 
            /* [retval][out] */ IPluginFilter __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pluginFilter( 
            /* [in] */ IPluginFilter __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetInPin( 
            /* [in] */ long n,
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetInPin( 
            /* [in] */ long n,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetType( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDFilterPrimitiveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDFilterPrimitive __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDFilterPrimitive __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [in] */ IPDAppearance __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pluginFilter )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [retval][out] */ IPluginFilter __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pluginFilter )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [in] */ IPluginFilter __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInPin )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [in] */ long n,
            /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInPin )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [in] */ long n,
            /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IPDFilterPrimitive __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDFilterPrimitiveVtbl;

    interface IPDFilterPrimitive
    {
        CONST_VTBL struct IPDFilterPrimitiveVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDFilterPrimitive_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDFilterPrimitive_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDFilterPrimitive_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDFilterPrimitive_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDFilterPrimitive_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDFilterPrimitive_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDFilterPrimitive_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDFilterPrimitive_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDFilterPrimitive_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDFilterPrimitive_get_pluginFilter(This,pVal)	\
    (This)->lpVtbl -> get_pluginFilter(This,pVal)

#define IPDFilterPrimitive_put_pluginFilter(This,newVal)	\
    (This)->lpVtbl -> put_pluginFilter(This,newVal)

#define IPDFilterPrimitive_GetInPin(This,n,pVal)	\
    (This)->lpVtbl -> GetInPin(This,n,pVal)

#define IPDFilterPrimitive_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDFilterPrimitive_SetInPin(This,n,newVal)	\
    (This)->lpVtbl -> SetInPin(This,n,newVal)

#define IPDFilterPrimitive_GetType(This,pVal)	\
    (This)->lpVtbl -> GetType(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_get_nextSibling_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDFilterPrimitive_get_nextSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_put_nextSibling_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal);


void __RPC_STUB IPDFilterPrimitive_put_nextSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_get_previousSibling_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDFilterPrimitive_get_previousSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_put_previousSibling_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal);


void __RPC_STUB IPDFilterPrimitive_put_previousSibling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_get_parent_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDFilterPrimitive_get_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_put_parent_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [in] */ IPDAppearance __RPC_FAR *newVal);


void __RPC_STUB IPDFilterPrimitive_put_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_get_pluginFilter_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [retval][out] */ IPluginFilter __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDFilterPrimitive_get_pluginFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_put_pluginFilter_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [in] */ IPluginFilter __RPC_FAR *newVal);


void __RPC_STUB IPDFilterPrimitive_put_pluginFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_GetInPin_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [in] */ long n,
    /* [retval][out] */ IPDFilterPrimitive __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDFilterPrimitive_GetInPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_get_name_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDFilterPrimitive_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_SetInPin_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [in] */ long n,
    /* [in] */ IPDFilterPrimitive __RPC_FAR *newVal);


void __RPC_STUB IPDFilterPrimitive_SetInPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDFilterPrimitive_GetType_Proxy( 
    IPDFilterPrimitive __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDFilterPrimitive_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDFilterPrimitive_INTERFACE_DEFINED__ */


#ifndef __IPDSymbol_INTERFACE_DEFINED__
#define __IPDSymbol_INTERFACE_DEFINED__

/* interface IPDSymbol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSymbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E91BB7D-2C21-4D3A-9522-F1290FC23941")
    IPDSymbol : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_symbolObject( 
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_symbolObject( 
            /* [in] */ IPDObject __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSymbol __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSymbol __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSymbol __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_symbolObject )( 
            IPDSymbol __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_symbolObject )( 
            IPDSymbol __RPC_FAR * This,
            /* [in] */ IPDObject __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IPDSymbol __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_name )( 
            IPDSymbol __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IPDSymbolVtbl;

    interface IPDSymbol
    {
        CONST_VTBL struct IPDSymbolVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSymbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSymbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSymbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDSymbol_get_symbolObject(This,pVal)	\
    (This)->lpVtbl -> get_symbolObject(This,pVal)

#define IPDSymbol_put_symbolObject(This,newVal)	\
    (This)->lpVtbl -> put_symbolObject(This,newVal)

#define IPDSymbol_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IPDSymbol_put_name(This,newVal)	\
    (This)->lpVtbl -> put_name(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSymbol_get_symbolObject_Proxy( 
    IPDSymbol __RPC_FAR * This,
    /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDSymbol_get_symbolObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSymbol_put_symbolObject_Proxy( 
    IPDSymbol __RPC_FAR * This,
    /* [in] */ IPDObject __RPC_FAR *newVal);


void __RPC_STUB IPDSymbol_put_symbolObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSymbol_get_name_Proxy( 
    IPDSymbol __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDSymbol_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSymbol_put_name_Proxy( 
    IPDSymbol __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDSymbol_put_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSymbol_INTERFACE_DEFINED__ */


#ifndef __IPDSpreadDocument_INTERFACE_DEFINED__
#define __IPDSpreadDocument_INTERFACE_DEFINED__

/* interface IPDSpreadDocument */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSpreadDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FCE21B23-89A1-4433-8448-F60FB825B5C9")
    IPDSpreadDocument : public IPDSpread
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_keepSpreadTogether( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_keepSpreadTogether( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSpreadDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSpreadDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSpreadDocument __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pages )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layergroups )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spine )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spine )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerDocument )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getLayerGroupFromLayer )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [in] */ IPDLayer __RPC_FAR *layer,
            /* [retval][out] */ IPDObjectLayerGroup __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getObjectByUniqId )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeLayerGroup )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [in] */ IPDObjectLayerGroup __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstLayerGroup )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastLayerGroup )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_keepSpreadTogether )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_keepSpreadTogether )( 
            IPDSpreadDocument __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IPDSpreadDocumentVtbl;

    interface IPDSpreadDocument
    {
        CONST_VTBL struct IPDSpreadDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSpreadDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSpreadDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSpreadDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSpreadDocument_get_pages(This,pVal)	\
    (This)->lpVtbl -> get_pages(This,pVal)

#define IPDSpreadDocument_get_layergroups(This,pVal)	\
    (This)->lpVtbl -> get_layergroups(This,pVal)

#define IPDSpreadDocument_get_spine(This,pVal)	\
    (This)->lpVtbl -> get_spine(This,pVal)

#define IPDSpreadDocument_put_spine(This,newVal)	\
    (This)->lpVtbl -> put_spine(This,newVal)

#define IPDSpreadDocument_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define IPDSpreadDocument_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDSpreadDocument_getLayerGroupFromLayer(This,layer,pVal)	\
    (This)->lpVtbl -> getLayerGroupFromLayer(This,layer,pVal)

#define IPDSpreadDocument_getObjectByUniqId(This,guid,pVal)	\
    (This)->lpVtbl -> getObjectByUniqId(This,guid,pVal)

#define IPDSpreadDocument_removeLayerGroup(This,object)	\
    (This)->lpVtbl -> removeLayerGroup(This,object)

#define IPDSpreadDocument_get_firstLayerGroup(This,pVal)	\
    (This)->lpVtbl -> get_firstLayerGroup(This,pVal)

#define IPDSpreadDocument_get_lastLayerGroup(This,pVal)	\
    (This)->lpVtbl -> get_lastLayerGroup(This,pVal)


#define IPDSpreadDocument_get_keepSpreadTogether(This,pVal)	\
    (This)->lpVtbl -> get_keepSpreadTogether(This,pVal)

#define IPDSpreadDocument_put_keepSpreadTogether(This,newVal)	\
    (This)->lpVtbl -> put_keepSpreadTogether(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSpreadDocument_get_keepSpreadTogether_Proxy( 
    IPDSpreadDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDSpreadDocument_get_keepSpreadTogether_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSpreadDocument_put_keepSpreadTogether_Proxy( 
    IPDSpreadDocument __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDSpreadDocument_put_keepSpreadTogether_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSpreadDocument_INTERFACE_DEFINED__ */


#ifndef __IArchive_INTERFACE_DEFINED__
#define __IArchive_INTERFACE_DEFINED__

/* interface IArchive */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IArchive;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3304AD56-664A-42FD-8FD8-1B0F2363C3D8")
    IArchive : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR pathName,
            /* [in] */ DWORD dwMode,
            /* [in] */ BSTR rootName,
            /* [retval][out] */ IArchiveElement __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MapObject( 
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArchiveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IArchive __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IArchive __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IArchive __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IArchive __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IArchive __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IArchive __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IArchive __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IArchive __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [in] */ DWORD dwMode,
            /* [in] */ BSTR rootName,
            /* [retval][out] */ IArchiveElement __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapObject )( 
            IArchive __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        END_INTERFACE
    } IArchiveVtbl;

    interface IArchive
    {
        CONST_VTBL struct IArchiveVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArchive_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IArchive_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IArchive_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IArchive_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IArchive_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IArchive_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IArchive_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IArchive_Open(This,pathName,dwMode,rootName,pVal)	\
    (This)->lpVtbl -> Open(This,pathName,dwMode,rootName,pVal)

#define IArchive_MapObject(This,pUnk)	\
    (This)->lpVtbl -> MapObject(This,pUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchive_Open_Proxy( 
    IArchive __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [in] */ DWORD dwMode,
    /* [in] */ BSTR rootName,
    /* [retval][out] */ IArchiveElement __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IArchive_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchive_MapObject_Proxy( 
    IArchive __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB IArchive_MapObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IArchive_INTERFACE_DEFINED__ */


#ifndef __IArchiveElement_INTERFACE_DEFINED__
#define __IArchiveElement_INTERFACE_DEFINED__

/* interface IArchiveElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IArchiveElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BFDE0299-C6C5-489b-BF40-F2E08E0CDA06")
    IArchiveElement : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE putAttribute( 
            /* [in] */ BSTR name,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getAttribute( 
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE putElement( 
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE putData( 
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE putObjectMap( 
            /* [in] */ BSTR name,
            /* [in] */ IObjectMap __RPC_FAR *objectmap) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getObjectMap( 
            /* [in] */ BSTR name,
            /* [in] */ IObjectMap __RPC_FAR *objectmap,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getElement( 
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getData( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getAttributeNode( 
            /* [in] */ BSTR name,
            /* [retval][out] */ IArchiveElement __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE serializeElement( 
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE deserializeElement( 
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnk,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE putObject( 
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE deserializeObjectMap( 
            /* [in] */ IObjectMap __RPC_FAR *objectmap,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE serializeObjectMap( 
            /* [in] */ IObjectMap __RPC_FAR *objectmap) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getObject( 
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArchiveElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IArchiveElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IArchiveElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IArchiveElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putAttribute )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putElement )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putData )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putObjectMap )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ IObjectMap __RPC_FAR *objectmap);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getObjectMap )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ IObjectMap __RPC_FAR *objectmap,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getElement )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getData )( 
            IArchiveElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttributeNode )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IArchiveElement __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *serializeElement )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deserializeElement )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ IUnknown __RPC_FAR *pUnk,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putObject )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deserializeObjectMap )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ IObjectMap __RPC_FAR *objectmap,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *serializeObjectMap )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ IObjectMap __RPC_FAR *objectmap);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getObject )( 
            IArchiveElement __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IArchiveElementVtbl;

    interface IArchiveElement
    {
        CONST_VTBL struct IArchiveElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArchiveElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IArchiveElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IArchiveElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IArchiveElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IArchiveElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IArchiveElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IArchiveElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IArchiveElement_putAttribute(This,name,value)	\
    (This)->lpVtbl -> putAttribute(This,name,value)

#define IArchiveElement_getAttribute(This,name,pVal)	\
    (This)->lpVtbl -> getAttribute(This,name,pVal)

#define IArchiveElement_putElement(This,name,pUnk)	\
    (This)->lpVtbl -> putElement(This,name,pUnk)

#define IArchiveElement_putData(This,value)	\
    (This)->lpVtbl -> putData(This,value)

#define IArchiveElement_putObjectMap(This,name,objectmap)	\
    (This)->lpVtbl -> putObjectMap(This,name,objectmap)

#define IArchiveElement_getObjectMap(This,name,objectmap,pUnkExtra)	\
    (This)->lpVtbl -> getObjectMap(This,name,objectmap,pUnkExtra)

#define IArchiveElement_getElement(This,name,pUnkExtra,pVal)	\
    (This)->lpVtbl -> getElement(This,name,pUnkExtra,pVal)

#define IArchiveElement_getData(This,pVal)	\
    (This)->lpVtbl -> getData(This,pVal)

#define IArchiveElement_getAttributeNode(This,name,pVal)	\
    (This)->lpVtbl -> getAttributeNode(This,name,pVal)

#define IArchiveElement_serializeElement(This,name,pUnk)	\
    (This)->lpVtbl -> serializeElement(This,name,pUnk)

#define IArchiveElement_deserializeElement(This,name,pUnk,pUnkExtra)	\
    (This)->lpVtbl -> deserializeElement(This,name,pUnk,pUnkExtra)

#define IArchiveElement_putObject(This,pUnk)	\
    (This)->lpVtbl -> putObject(This,pUnk)

#define IArchiveElement_deserializeObjectMap(This,objectmap,pUnkExtra)	\
    (This)->lpVtbl -> deserializeObjectMap(This,objectmap,pUnkExtra)

#define IArchiveElement_serializeObjectMap(This,objectmap)	\
    (This)->lpVtbl -> serializeObjectMap(This,objectmap)

#define IArchiveElement_getObject(This,pUnkExtra,pVal)	\
    (This)->lpVtbl -> getObject(This,pUnkExtra,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_putAttribute_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ VARIANT value);


void __RPC_STUB IArchiveElement_putAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_getAttribute_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IArchiveElement_getAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_putElement_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB IArchiveElement_putElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_putData_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ VARIANT value);


void __RPC_STUB IArchiveElement_putData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_putObjectMap_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ IObjectMap __RPC_FAR *objectmap);


void __RPC_STUB IArchiveElement_putObjectMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_getObjectMap_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ IObjectMap __RPC_FAR *objectmap,
    /* [in] */ IUnknown __RPC_FAR *pUnkExtra);


void __RPC_STUB IArchiveElement_getObjectMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_getElement_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ IUnknown __RPC_FAR *pUnkExtra,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IArchiveElement_getElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_getData_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IArchiveElement_getData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_getAttributeNode_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ IArchiveElement __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IArchiveElement_getAttributeNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_serializeElement_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB IArchiveElement_serializeElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_deserializeElement_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ IUnknown __RPC_FAR *pUnk,
    /* [in] */ IUnknown __RPC_FAR *pUnkExtra);


void __RPC_STUB IArchiveElement_deserializeElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_putObject_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB IArchiveElement_putObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_deserializeObjectMap_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ IObjectMap __RPC_FAR *objectmap,
    /* [in] */ IUnknown __RPC_FAR *pUnkExtra);


void __RPC_STUB IArchiveElement_deserializeObjectMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_serializeObjectMap_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ IObjectMap __RPC_FAR *objectmap);


void __RPC_STUB IArchiveElement_serializeObjectMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArchiveElement_getObject_Proxy( 
    IArchiveElement __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkExtra,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IArchiveElement_getObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IArchiveElement_INTERFACE_DEFINED__ */


#ifndef __IPageDesignerApp_INTERFACE_DEFINED__
#define __IPageDesignerApp_INTERFACE_DEFINED__

/* interface IPageDesignerApp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPageDesignerApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("14A92517-0DC2-4a19-B2A5-4536BEBD97AC")
    IPageDesignerApp : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_frame( 
            /* [retval][out] */ IPageDesignerFrame __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_uiManager( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [retval][out] */ long __RPC_FAR *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenDocument( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_swatches( 
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_newArtHasBasicAppearance( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_newArtHasBasicAppearance( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strokeOrFill( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_strokeOrFill( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPageDesignerAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPageDesignerApp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPageDesignerApp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_frame )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [retval][out] */ IPageDesignerFrame __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uiManager )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenDocument )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatches )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_newArtHasBasicAppearance )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_newArtHasBasicAppearance )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strokeOrFill )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strokeOrFill )( 
            IPageDesignerApp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IPageDesignerAppVtbl;

    interface IPageDesignerApp
    {
        CONST_VTBL struct IPageDesignerAppVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPageDesignerApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPageDesignerApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPageDesignerApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPageDesignerApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPageDesignerApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPageDesignerApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPageDesignerApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPageDesignerApp_get_frame(This,pVal)	\
    (This)->lpVtbl -> get_frame(This,pVal)

#define IPageDesignerApp_get_uiManager(This,pVal)	\
    (This)->lpVtbl -> get_uiManager(This,pVal)

#define IPageDesignerApp_Run(This,result)	\
    (This)->lpVtbl -> Run(This,result)

#define IPageDesignerApp_OpenDocument(This,pathName,success)	\
    (This)->lpVtbl -> OpenDocument(This,pathName,success)

#define IPageDesignerApp_get_swatches(This,pVal)	\
    (This)->lpVtbl -> get_swatches(This,pVal)

#define IPageDesignerApp_get_newArtHasBasicAppearance(This,pVal)	\
    (This)->lpVtbl -> get_newArtHasBasicAppearance(This,pVal)

#define IPageDesignerApp_put_newArtHasBasicAppearance(This,newVal)	\
    (This)->lpVtbl -> put_newArtHasBasicAppearance(This,newVal)

#define IPageDesignerApp_get_strokeOrFill(This,pVal)	\
    (This)->lpVtbl -> get_strokeOrFill(This,pVal)

#define IPageDesignerApp_put_strokeOrFill(This,newVal)	\
    (This)->lpVtbl -> put_strokeOrFill(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_get_frame_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [retval][out] */ IPageDesignerFrame __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPageDesignerApp_get_frame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_get_uiManager_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPageDesignerApp_get_uiManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_Run_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *result);


void __RPC_STUB IPageDesignerApp_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_OpenDocument_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success);


void __RPC_STUB IPageDesignerApp_OpenDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_get_swatches_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPageDesignerApp_get_swatches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_get_newArtHasBasicAppearance_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPageDesignerApp_get_newArtHasBasicAppearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_put_newArtHasBasicAppearance_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPageDesignerApp_put_newArtHasBasicAppearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_get_strokeOrFill_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPageDesignerApp_get_strokeOrFill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPageDesignerApp_put_strokeOrFill_Proxy( 
    IPageDesignerApp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPageDesignerApp_put_strokeOrFill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPageDesignerApp_INTERFACE_DEFINED__ */


#ifndef __DispIPageDesignerFrame_INTERFACE_DEFINED__
#define __DispIPageDesignerFrame_INTERFACE_DEFINED__

/* interface DispIPageDesignerFrame */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_DispIPageDesignerFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5D42AF42-8C5E-4a26-A6D0-9079E60171DD")
    DispIPageDesignerFrame : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct DispIPageDesignerFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DispIPageDesignerFrame __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DispIPageDesignerFrame __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DispIPageDesignerFrame __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DispIPageDesignerFrame __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DispIPageDesignerFrame __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DispIPageDesignerFrame __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DispIPageDesignerFrame __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DispIPageDesignerFrameVtbl;

    interface DispIPageDesignerFrame
    {
        CONST_VTBL struct DispIPageDesignerFrameVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DispIPageDesignerFrame_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DispIPageDesignerFrame_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DispIPageDesignerFrame_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DispIPageDesignerFrame_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DispIPageDesignerFrame_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DispIPageDesignerFrame_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DispIPageDesignerFrame_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __DispIPageDesignerFrame_INTERFACE_DEFINED__ */


#ifndef __IObjectMap_INTERFACE_DEFINED__
#define __IObjectMap_INTERFACE_DEFINED__

/* interface IObjectMap */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IObjectMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B12CC07A-9D5C-4bf4-8444-66F52AE5F930")
    IObjectMap : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE item( 
            /* [in] */ long index,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IObjectMap __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IObjectMap __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IObjectMap __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IObjectMap __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IObjectMap __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IObjectMapVtbl;

    interface IObjectMap
    {
        CONST_VTBL struct IObjectMapVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IObjectMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IObjectMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IObjectMap_get_length(This,pVal)	\
    (This)->lpVtbl -> get_length(This,pVal)

#define IObjectMap_item(This,index,pVal)	\
    (This)->lpVtbl -> item(This,index,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IObjectMap_get_length_Proxy( 
    IObjectMap __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IObjectMap_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IObjectMap_item_Proxy( 
    IObjectMap __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IObjectMap_item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectMap_INTERFACE_DEFINED__ */


#ifndef __IPDColor_INTERFACE_DEFINED__
#define __IPDColor_INTERFACE_DEFINED__

/* interface IPDColor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDColor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4EC94DD-0D2F-4c7d-A15E-F312A38DA906")
    IPDColor : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_colorMode( 
            /* [retval][out] */ PDColorMode __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_colorMode( 
            /* [in] */ PDColorMode newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE putChannel( 
            /* [in] */ long n,
            /* [in] */ double value) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getChannel( 
            /* [in] */ long n,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setRGB( 
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE clone( 
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE copy( 
            /* [in] */ IPDColor __RPC_FAR *color) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDColorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDColor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDColor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDColor __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_colorMode )( 
            IPDColor __RPC_FAR * This,
            /* [retval][out] */ PDColorMode __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_colorMode )( 
            IPDColor __RPC_FAR * This,
            /* [in] */ PDColorMode newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putChannel )( 
            IPDColor __RPC_FAR * This,
            /* [in] */ long n,
            /* [in] */ double value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getChannel )( 
            IPDColor __RPC_FAR * This,
            /* [in] */ long n,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setRGB )( 
            IPDColor __RPC_FAR * This,
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDColor __RPC_FAR * This,
            /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *copy )( 
            IPDColor __RPC_FAR * This,
            /* [in] */ IPDColor __RPC_FAR *color);
        
        END_INTERFACE
    } IPDColorVtbl;

    interface IPDColor
    {
        CONST_VTBL struct IPDColorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDColor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDColor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDColor_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDColor_get_colorMode(This,pVal)	\
    (This)->lpVtbl -> get_colorMode(This,pVal)

#define IPDColor_put_colorMode(This,newVal)	\
    (This)->lpVtbl -> put_colorMode(This,newVal)

#define IPDColor_putChannel(This,n,value)	\
    (This)->lpVtbl -> putChannel(This,n,value)

#define IPDColor_getChannel(This,n,pVal)	\
    (This)->lpVtbl -> getChannel(This,n,pVal)

#define IPDColor_setRGB(This,red,green,blue)	\
    (This)->lpVtbl -> setRGB(This,red,green,blue)

#define IPDColor_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDColor_copy(This,color)	\
    (This)->lpVtbl -> copy(This,color)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDColor_get_colorMode_Proxy( 
    IPDColor __RPC_FAR * This,
    /* [retval][out] */ PDColorMode __RPC_FAR *pVal);


void __RPC_STUB IPDColor_get_colorMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDColor_put_colorMode_Proxy( 
    IPDColor __RPC_FAR * This,
    /* [in] */ PDColorMode newVal);


void __RPC_STUB IPDColor_put_colorMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDColor_putChannel_Proxy( 
    IPDColor __RPC_FAR * This,
    /* [in] */ long n,
    /* [in] */ double value);


void __RPC_STUB IPDColor_putChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDColor_getChannel_Proxy( 
    IPDColor __RPC_FAR * This,
    /* [in] */ long n,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDColor_getChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDColor_setRGB_Proxy( 
    IPDColor __RPC_FAR * This,
    /* [in] */ long red,
    /* [in] */ long green,
    /* [in] */ long blue);


void __RPC_STUB IPDColor_setRGB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDColor_clone_Proxy( 
    IPDColor __RPC_FAR * This,
    /* [retval][out] */ IPDColor __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDColor_clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDColor_copy_Proxy( 
    IPDColor __RPC_FAR * This,
    /* [in] */ IPDColor __RPC_FAR *color);


void __RPC_STUB IPDColor_copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDColor_INTERFACE_DEFINED__ */


#ifndef __IPluginFilterClass_INTERFACE_DEFINED__
#define __IPluginFilterClass_INTERFACE_DEFINED__

/* interface IPluginFilterClass */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPluginFilterClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5AF8445-22BB-4298-8AC3-53114CA231DC")
    IPluginFilterClass : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginFilterClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPluginFilterClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPluginFilterClass __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPluginFilterClass __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IPluginFilterClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPluginFilterClassVtbl;

    interface IPluginFilterClass
    {
        CONST_VTBL struct IPluginFilterClassVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPluginFilterClass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPluginFilterClass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPluginFilterClass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPluginFilterClass_GetName(This,pVal)	\
    (This)->lpVtbl -> GetName(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilterClass_GetName_Proxy( 
    IPluginFilterClass __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPluginFilterClass_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPluginFilterClass_INTERFACE_DEFINED__ */


#ifndef __IPluginFilter_INTERFACE_DEFINED__
#define __IPluginFilter_INTERFACE_DEFINED__

/* interface IPluginFilter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPluginFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("24F1463B-F0D6-49a7-BBEA-1394795F2DFC")
    IPluginFilter : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetInPinCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetInPinType( 
            /* [in] */ long n,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetResultType( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameSetup( 
            /* [in] */ DWORD filterRecord) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameSetdown( 
            /* [in] */ DWORD filterRecord) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Filter( 
            /* [in] */ DWORD filterRecord) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowOptions( 
            /* [in] */ HWND hParent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPluginFilterClass( 
            /* [in] */ IPluginFilterClass __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPluginFilterClass( 
            /* [retval][out] */ IPluginFilterClass __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPluginFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPluginFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPluginFilter __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInPinCount )( 
            IPluginFilter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInPinType )( 
            IPluginFilter __RPC_FAR * This,
            /* [in] */ long n,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetResultType )( 
            IPluginFilter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IPluginFilter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FrameSetup )( 
            IPluginFilter __RPC_FAR * This,
            /* [in] */ DWORD filterRecord);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FrameSetdown )( 
            IPluginFilter __RPC_FAR * This,
            /* [in] */ DWORD filterRecord);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Filter )( 
            IPluginFilter __RPC_FAR * This,
            /* [in] */ DWORD filterRecord);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowOptions )( 
            IPluginFilter __RPC_FAR * This,
            /* [in] */ HWND hParent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPluginFilterClass )( 
            IPluginFilter __RPC_FAR * This,
            /* [in] */ IPluginFilterClass __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPluginFilterClass )( 
            IPluginFilter __RPC_FAR * This,
            /* [retval][out] */ IPluginFilterClass __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPluginFilterVtbl;

    interface IPluginFilter
    {
        CONST_VTBL struct IPluginFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPluginFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPluginFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPluginFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPluginFilter_GetInPinCount(This,pVal)	\
    (This)->lpVtbl -> GetInPinCount(This,pVal)

#define IPluginFilter_GetInPinType(This,n,pVal)	\
    (This)->lpVtbl -> GetInPinType(This,n,pVal)

#define IPluginFilter_GetResultType(This,pVal)	\
    (This)->lpVtbl -> GetResultType(This,pVal)

#define IPluginFilter_GetName(This,pVal)	\
    (This)->lpVtbl -> GetName(This,pVal)

#define IPluginFilter_FrameSetup(This,filterRecord)	\
    (This)->lpVtbl -> FrameSetup(This,filterRecord)

#define IPluginFilter_FrameSetdown(This,filterRecord)	\
    (This)->lpVtbl -> FrameSetdown(This,filterRecord)

#define IPluginFilter_Filter(This,filterRecord)	\
    (This)->lpVtbl -> Filter(This,filterRecord)

#define IPluginFilter_ShowOptions(This,hParent)	\
    (This)->lpVtbl -> ShowOptions(This,hParent)

#define IPluginFilter_SetPluginFilterClass(This,newVal)	\
    (This)->lpVtbl -> SetPluginFilterClass(This,newVal)

#define IPluginFilter_GetPluginFilterClass(This,pVal)	\
    (This)->lpVtbl -> GetPluginFilterClass(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_GetInPinCount_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPluginFilter_GetInPinCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_GetInPinType_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [in] */ long n,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPluginFilter_GetInPinType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_GetResultType_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPluginFilter_GetResultType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_GetName_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPluginFilter_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_FrameSetup_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [in] */ DWORD filterRecord);


void __RPC_STUB IPluginFilter_FrameSetup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_FrameSetdown_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [in] */ DWORD filterRecord);


void __RPC_STUB IPluginFilter_FrameSetdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_Filter_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [in] */ DWORD filterRecord);


void __RPC_STUB IPluginFilter_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_ShowOptions_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [in] */ HWND hParent);


void __RPC_STUB IPluginFilter_ShowOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_SetPluginFilterClass_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [in] */ IPluginFilterClass __RPC_FAR *newVal);


void __RPC_STUB IPluginFilter_SetPluginFilterClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginFilter_GetPluginFilterClass_Proxy( 
    IPluginFilter __RPC_FAR * This,
    /* [retval][out] */ IPluginFilterClass __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPluginFilter_GetPluginFilterClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPluginFilter_INTERFACE_DEFINED__ */


#ifndef __IPDSection_INTERFACE_DEFINED__
#define __IPDSection_INTERFACE_DEFINED__

/* interface IPDSection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CA96A21-0A9D-11d6-95F0-0002E3045703")
    IPDSection : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pageNumbering( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pageNumbering( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pageNumberingStartAt( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_pageNumberingStartAt( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_style( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_style( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSection __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pageNumbering )( 
            IPDSection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pageNumbering )( 
            IPDSection __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pageNumberingStartAt )( 
            IPDSection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pageNumberingStartAt )( 
            IPDSection __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_style )( 
            IPDSection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_style )( 
            IPDSection __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IPDSectionVtbl;

    interface IPDSection
    {
        CONST_VTBL struct IPDSectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSection_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSection_get_pageNumbering(This,pVal)	\
    (This)->lpVtbl -> get_pageNumbering(This,pVal)

#define IPDSection_put_pageNumbering(This,newVal)	\
    (This)->lpVtbl -> put_pageNumbering(This,newVal)

#define IPDSection_get_pageNumberingStartAt(This,pVal)	\
    (This)->lpVtbl -> get_pageNumberingStartAt(This,pVal)

#define IPDSection_put_pageNumberingStartAt(This,newVal)	\
    (This)->lpVtbl -> put_pageNumberingStartAt(This,newVal)

#define IPDSection_get_style(This,pVal)	\
    (This)->lpVtbl -> get_style(This,pVal)

#define IPDSection_put_style(This,newVal)	\
    (This)->lpVtbl -> put_style(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSection_get_pageNumbering_Proxy( 
    IPDSection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDSection_get_pageNumbering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSection_put_pageNumbering_Proxy( 
    IPDSection __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDSection_put_pageNumbering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSection_get_pageNumberingStartAt_Proxy( 
    IPDSection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDSection_get_pageNumberingStartAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSection_put_pageNumberingStartAt_Proxy( 
    IPDSection __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDSection_put_pageNumberingStartAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSection_get_style_Proxy( 
    IPDSection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDSection_get_style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSection_put_style_Proxy( 
    IPDSection __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDSection_put_style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSection_INTERFACE_DEFINED__ */


#ifndef __IPDDocumentSettings_INTERFACE_DEFINED__
#define __IPDDocumentSettings_INTERFACE_DEFINED__

/* interface IPDDocumentSettings */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDDocumentSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86D802E1-13FF-11d6-95F0-0002E3045703")
    IPDDocumentSettings : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_horizontalGridlineEvery( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_horizontalGridlineEvery( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_verticalGridlineEvery( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_verticalGridlineEvery( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_horizontalGridSubdivisions( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_horizontalGridSubdivisions( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_verticalGridSubdivisions( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_verticalGridSubdivisions( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_horizontalRulerUnits( 
            /* [retval][out] */ PDUnit __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_horizontalRulerUnits( 
            /* [in] */ PDUnit newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_verticalRulerUnits( 
            /* [retval][out] */ PDUnit __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_verticalRulerUnits( 
            /* [in] */ PDUnit newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_transpGridColor0( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_transpGridColor1( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_transpGridSizeX( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_transpGridSizeY( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setTranspGrid( 
            /* [in] */ long transpGridSizeX,
            /* [in] */ long transpGridSizeY,
            /* [in] */ OLE_COLOR transpGridColor0,
            /* [in] */ OLE_COLOR transpGridColor1) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE copyDocumentSettingsFrom( 
            /* [in] */ IPDDocumentSettings __RPC_FAR *other) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_rasterResolution( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_rasterResolution( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDDocumentSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDDocumentSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDDocumentSettings __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_horizontalGridlineEvery )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_horizontalGridlineEvery )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_verticalGridlineEvery )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_verticalGridlineEvery )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_horizontalGridSubdivisions )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_horizontalGridSubdivisions )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_verticalGridSubdivisions )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_verticalGridSubdivisions )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_horizontalRulerUnits )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ PDUnit __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_horizontalRulerUnits )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ PDUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_verticalRulerUnits )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ PDUnit __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_verticalRulerUnits )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ PDUnit newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transpGridColor0 )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transpGridColor1 )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transpGridSizeX )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transpGridSizeY )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTranspGrid )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ long transpGridSizeX,
            /* [in] */ long transpGridSizeY,
            /* [in] */ OLE_COLOR transpGridColor0,
            /* [in] */ OLE_COLOR transpGridColor1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *copyDocumentSettingsFrom )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ IPDDocumentSettings __RPC_FAR *other);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rasterResolution )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rasterResolution )( 
            IPDDocumentSettings __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IPDDocumentSettingsVtbl;

    interface IPDDocumentSettings
    {
        CONST_VTBL struct IPDDocumentSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDDocumentSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDDocumentSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDDocumentSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDDocumentSettings_get_horizontalGridlineEvery(This,pVal)	\
    (This)->lpVtbl -> get_horizontalGridlineEvery(This,pVal)

#define IPDDocumentSettings_put_horizontalGridlineEvery(This,newVal)	\
    (This)->lpVtbl -> put_horizontalGridlineEvery(This,newVal)

#define IPDDocumentSettings_get_verticalGridlineEvery(This,pVal)	\
    (This)->lpVtbl -> get_verticalGridlineEvery(This,pVal)

#define IPDDocumentSettings_put_verticalGridlineEvery(This,newVal)	\
    (This)->lpVtbl -> put_verticalGridlineEvery(This,newVal)

#define IPDDocumentSettings_get_horizontalGridSubdivisions(This,pVal)	\
    (This)->lpVtbl -> get_horizontalGridSubdivisions(This,pVal)

#define IPDDocumentSettings_put_horizontalGridSubdivisions(This,newVal)	\
    (This)->lpVtbl -> put_horizontalGridSubdivisions(This,newVal)

#define IPDDocumentSettings_get_verticalGridSubdivisions(This,pVal)	\
    (This)->lpVtbl -> get_verticalGridSubdivisions(This,pVal)

#define IPDDocumentSettings_put_verticalGridSubdivisions(This,newVal)	\
    (This)->lpVtbl -> put_verticalGridSubdivisions(This,newVal)

#define IPDDocumentSettings_get_horizontalRulerUnits(This,pVal)	\
    (This)->lpVtbl -> get_horizontalRulerUnits(This,pVal)

#define IPDDocumentSettings_put_horizontalRulerUnits(This,newVal)	\
    (This)->lpVtbl -> put_horizontalRulerUnits(This,newVal)

#define IPDDocumentSettings_get_verticalRulerUnits(This,pVal)	\
    (This)->lpVtbl -> get_verticalRulerUnits(This,pVal)

#define IPDDocumentSettings_put_verticalRulerUnits(This,newVal)	\
    (This)->lpVtbl -> put_verticalRulerUnits(This,newVal)

#define IPDDocumentSettings_get_transpGridColor0(This,pVal)	\
    (This)->lpVtbl -> get_transpGridColor0(This,pVal)

#define IPDDocumentSettings_get_transpGridColor1(This,pVal)	\
    (This)->lpVtbl -> get_transpGridColor1(This,pVal)

#define IPDDocumentSettings_get_transpGridSizeX(This,pVal)	\
    (This)->lpVtbl -> get_transpGridSizeX(This,pVal)

#define IPDDocumentSettings_get_transpGridSizeY(This,pVal)	\
    (This)->lpVtbl -> get_transpGridSizeY(This,pVal)

#define IPDDocumentSettings_setTranspGrid(This,transpGridSizeX,transpGridSizeY,transpGridColor0,transpGridColor1)	\
    (This)->lpVtbl -> setTranspGrid(This,transpGridSizeX,transpGridSizeY,transpGridColor0,transpGridColor1)

#define IPDDocumentSettings_copyDocumentSettingsFrom(This,other)	\
    (This)->lpVtbl -> copyDocumentSettingsFrom(This,other)

#define IPDDocumentSettings_get_rasterResolution(This,pVal)	\
    (This)->lpVtbl -> get_rasterResolution(This,pVal)

#define IPDDocumentSettings_put_rasterResolution(This,newVal)	\
    (This)->lpVtbl -> put_rasterResolution(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_horizontalGridlineEvery_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_horizontalGridlineEvery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_put_horizontalGridlineEvery_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDDocumentSettings_put_horizontalGridlineEvery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_verticalGridlineEvery_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_verticalGridlineEvery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_put_verticalGridlineEvery_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDDocumentSettings_put_verticalGridlineEvery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_horizontalGridSubdivisions_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_horizontalGridSubdivisions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_put_horizontalGridSubdivisions_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDDocumentSettings_put_horizontalGridSubdivisions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_verticalGridSubdivisions_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_verticalGridSubdivisions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_put_verticalGridSubdivisions_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDDocumentSettings_put_verticalGridSubdivisions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_horizontalRulerUnits_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ PDUnit __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_horizontalRulerUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_put_horizontalRulerUnits_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ PDUnit newVal);


void __RPC_STUB IPDDocumentSettings_put_horizontalRulerUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_verticalRulerUnits_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ PDUnit __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_verticalRulerUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_put_verticalRulerUnits_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ PDUnit newVal);


void __RPC_STUB IPDDocumentSettings_put_verticalRulerUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_transpGridColor0_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_transpGridColor0_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_transpGridColor1_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_transpGridColor1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_transpGridSizeX_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_transpGridSizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_transpGridSizeY_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_transpGridSizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_setTranspGrid_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ long transpGridSizeX,
    /* [in] */ long transpGridSizeY,
    /* [in] */ OLE_COLOR transpGridColor0,
    /* [in] */ OLE_COLOR transpGridColor1);


void __RPC_STUB IPDDocumentSettings_setTranspGrid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_copyDocumentSettingsFrom_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ IPDDocumentSettings __RPC_FAR *other);


void __RPC_STUB IPDDocumentSettings_copyDocumentSettingsFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_get_rasterResolution_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDDocumentSettings_get_rasterResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocumentSettings_put_rasterResolution_Proxy( 
    IPDDocumentSettings __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDDocumentSettings_put_rasterResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDDocumentSettings_INTERFACE_DEFINED__ */


#ifndef __IPDApplicationSettings_INTERFACE_DEFINED__
#define __IPDApplicationSettings_INTERFACE_DEFINED__

/* interface IPDApplicationSettings */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDApplicationSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3776D1EB-24CD-4ce6-967C-F1615B7EED2C")
    IPDApplicationSettings : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_clipboardSavePNG( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_clipboardSavePNG( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_clipboardSaveJPEG( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_clipboardSaveJPEG( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_clipboardSaveGIF( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_clipboardSaveGIF( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDApplicationSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDApplicationSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDApplicationSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDApplicationSettings __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clipboardSavePNG )( 
            IPDApplicationSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_clipboardSavePNG )( 
            IPDApplicationSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clipboardSaveJPEG )( 
            IPDApplicationSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_clipboardSaveJPEG )( 
            IPDApplicationSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clipboardSaveGIF )( 
            IPDApplicationSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_clipboardSaveGIF )( 
            IPDApplicationSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IPDApplicationSettingsVtbl;

    interface IPDApplicationSettings
    {
        CONST_VTBL struct IPDApplicationSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDApplicationSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDApplicationSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDApplicationSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDApplicationSettings_get_clipboardSavePNG(This,pVal)	\
    (This)->lpVtbl -> get_clipboardSavePNG(This,pVal)

#define IPDApplicationSettings_put_clipboardSavePNG(This,newVal)	\
    (This)->lpVtbl -> put_clipboardSavePNG(This,newVal)

#define IPDApplicationSettings_get_clipboardSaveJPEG(This,pVal)	\
    (This)->lpVtbl -> get_clipboardSaveJPEG(This,pVal)

#define IPDApplicationSettings_put_clipboardSaveJPEG(This,newVal)	\
    (This)->lpVtbl -> put_clipboardSaveJPEG(This,newVal)

#define IPDApplicationSettings_get_clipboardSaveGIF(This,pVal)	\
    (This)->lpVtbl -> get_clipboardSaveGIF(This,pVal)

#define IPDApplicationSettings_put_clipboardSaveGIF(This,newVal)	\
    (This)->lpVtbl -> put_clipboardSaveGIF(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDApplicationSettings_get_clipboardSavePNG_Proxy( 
    IPDApplicationSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDApplicationSettings_get_clipboardSavePNG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDApplicationSettings_put_clipboardSavePNG_Proxy( 
    IPDApplicationSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDApplicationSettings_put_clipboardSavePNG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDApplicationSettings_get_clipboardSaveJPEG_Proxy( 
    IPDApplicationSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDApplicationSettings_get_clipboardSaveJPEG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDApplicationSettings_put_clipboardSaveJPEG_Proxy( 
    IPDApplicationSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDApplicationSettings_put_clipboardSaveJPEG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDApplicationSettings_get_clipboardSaveGIF_Proxy( 
    IPDApplicationSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDApplicationSettings_get_clipboardSaveGIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDApplicationSettings_put_clipboardSaveGIF_Proxy( 
    IPDApplicationSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDApplicationSettings_put_clipboardSaveGIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDApplicationSettings_INTERFACE_DEFINED__ */


#ifndef __IPDBrushSettings_INTERFACE_DEFINED__
#define __IPDBrushSettings_INTERFACE_DEFINED__

/* interface IPDBrushSettings */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDBrushSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BB749961-2623-11d6-95F0-0002E3045703")
    IPDBrushSettings : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_brushWidth( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_brushWidth( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_brushHeight( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_brushHeight( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_brushAngle( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_brushAngle( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_showBrushSize( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_showBrushSize( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getBrushMatrix( 
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDBrushSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDBrushSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDBrushSettings __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushWidth )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushWidth )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushHeight )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushHeight )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_brushAngle )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_brushAngle )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_showBrushSize )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_showBrushSize )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getBrushMatrix )( 
            IPDBrushSettings __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDBrushSettingsVtbl;

    interface IPDBrushSettings
    {
        CONST_VTBL struct IPDBrushSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDBrushSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDBrushSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDBrushSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDBrushSettings_get_brushWidth(This,pVal)	\
    (This)->lpVtbl -> get_brushWidth(This,pVal)

#define IPDBrushSettings_put_brushWidth(This,newVal)	\
    (This)->lpVtbl -> put_brushWidth(This,newVal)

#define IPDBrushSettings_get_brushHeight(This,pVal)	\
    (This)->lpVtbl -> get_brushHeight(This,pVal)

#define IPDBrushSettings_put_brushHeight(This,newVal)	\
    (This)->lpVtbl -> put_brushHeight(This,newVal)

#define IPDBrushSettings_get_brushAngle(This,pVal)	\
    (This)->lpVtbl -> get_brushAngle(This,pVal)

#define IPDBrushSettings_put_brushAngle(This,newVal)	\
    (This)->lpVtbl -> put_brushAngle(This,newVal)

#define IPDBrushSettings_get_showBrushSize(This,pVal)	\
    (This)->lpVtbl -> get_showBrushSize(This,pVal)

#define IPDBrushSettings_put_showBrushSize(This,newVal)	\
    (This)->lpVtbl -> put_showBrushSize(This,newVal)

#define IPDBrushSettings_getBrushMatrix(This,pVal)	\
    (This)->lpVtbl -> getBrushMatrix(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_get_brushWidth_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrushSettings_get_brushWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_put_brushWidth_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrushSettings_put_brushWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_get_brushHeight_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrushSettings_get_brushHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_put_brushHeight_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrushSettings_put_brushHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_get_brushAngle_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDBrushSettings_get_brushAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_put_brushAngle_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDBrushSettings_put_brushAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_get_showBrushSize_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDBrushSettings_get_showBrushSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_put_showBrushSize_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDBrushSettings_put_showBrushSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDBrushSettings_getBrushMatrix_Proxy( 
    IPDBrushSettings __RPC_FAR * This,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDBrushSettings_getBrushMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDBrushSettings_INTERFACE_DEFINED__ */


#ifndef __IPDDocument_INTERFACE_DEFINED__
#define __IPDDocument_INTERFACE_DEFINED__

/* interface IPDDocument */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC7AA05E-34AA-437c-9DC2-971F0F524D18")
    IPDDocument : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_filePath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_filePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_undoManager( 
            /* [retval][out] */ IOleUndoManager __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_spreads( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pages( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pageWidth( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pageHeight( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_facingPages( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_layers( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_masterSpreads( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_masterPages( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_images( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_swatches( 
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_stories( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowViews( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewDocument( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createObjectFrame( 
            /* [retval][out] */ IPDObjectFrame __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createContentGraphic( 
            /* [retval][out] */ IPDContentGraphic __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE loadImage( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createContentText( 
            /* [retval][out] */ IPDContentText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getMasterSpreadByName( 
            /* [in] */ BSTR prefix,
            /* [in] */ BSTR name,
            /* [retval][out] */ IPDSpreadMaster __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getSpreadByUniqId( 
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createObjectGroup( 
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewWindow( 
            /* [retval][out] */ IPDDocumentView __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createStory( 
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendStory( 
            /* [in] */ IPDStory __RPC_FAR *story) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createPathText( 
            /* [retval][out] */ IPDPathText __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertPagesBefore( 
            /* [in] */ long nPages,
            /* [in] */ long nBeforePage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertPagesAfter( 
            /* [in] */ long nPages,
            /* [in] */ long nAfterPage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getStoryById( 
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstSection( 
            /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createSection( 
            /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE deleteLayer( 
            /* [in] */ IPDLayer __RPC_FAR *layer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertLayerBefore( 
            /* [in] */ IPDLayer __RPC_FAR *layer,
            /* [in] */ IPDLayer __RPC_FAR *before) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getLayerByUniqId( 
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_fileTitle( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_fileTitle( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeStory( 
            /* [in] */ IPDStory __RPC_FAR *story) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createImage( 
            /* [in] */ long width,
            /* [in] */ long height,
            /* [in] */ DWORD mode,
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_symbols( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendSymbol( 
            /* [in] */ IPDSymbol __RPC_FAR *symbol) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getSymbolByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ IPDSymbol __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_firstSpread( 
            /* [retval][out] */ IPDSpreadDocument __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lastSpread( 
            /* [retval][out] */ IPDSpreadDocument __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE loadImageFromStream( 
            /* [in] */ IStream __RPC_FAR *stream,
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_showTextThreads( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_showTextThreads( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDDocument __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_filePath )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_filePath )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_undoManager )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IOleUndoManager __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spreads )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pages )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pageWidth )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pageHeight )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_facingPages )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layers )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_masterSpreads )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_masterPages )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_images )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatches )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stories )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowViews )( 
            IPDDocument __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewDocument )( 
            IPDDocument __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createObjectFrame )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDObjectFrame __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createContentGraphic )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDContentGraphic __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadImage )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createContentText )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDContentText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMasterSpreadByName )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ BSTR prefix,
            /* [in] */ BSTR name,
            /* [retval][out] */ IPDSpreadMaster __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSpreadByUniqId )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createObjectGroup )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewWindow )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDDocumentView __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createStory )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendStory )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ IPDStory __RPC_FAR *story);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createPathText )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDPathText __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertPagesBefore )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ long nPages,
            /* [in] */ long nBeforePage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertPagesAfter )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ long nPages,
            /* [in] */ long nAfterPage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getStoryById )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstSection )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createSection )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deleteLayer )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ IPDLayer __RPC_FAR *layer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertLayerBefore )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ IPDLayer __RPC_FAR *layer,
            /* [in] */ IPDLayer __RPC_FAR *before);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getLayerByUniqId )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileTitle )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_fileTitle )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeStory )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ IPDStory __RPC_FAR *story);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createImage )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ long width,
            /* [in] */ long height,
            /* [in] */ DWORD mode,
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_symbols )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendSymbol )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ IPDSymbol __RPC_FAR *symbol);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSymbolByName )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IPDSymbol __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstSpread )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDSpreadDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastSpread )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ IPDSpreadDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadImageFromStream )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ IStream __RPC_FAR *stream,
            /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_showTextThreads )( 
            IPDDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_showTextThreads )( 
            IPDDocument __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IPDDocumentVtbl;

    interface IPDDocument
    {
        CONST_VTBL struct IPDDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDDocument_get_filePath(This,pVal)	\
    (This)->lpVtbl -> get_filePath(This,pVal)

#define IPDDocument_put_filePath(This,newVal)	\
    (This)->lpVtbl -> put_filePath(This,newVal)

#define IPDDocument_get_undoManager(This,pVal)	\
    (This)->lpVtbl -> get_undoManager(This,pVal)

#define IPDDocument_get_spreads(This,pVal)	\
    (This)->lpVtbl -> get_spreads(This,pVal)

#define IPDDocument_get_pages(This,pVal)	\
    (This)->lpVtbl -> get_pages(This,pVal)

#define IPDDocument_get_pageWidth(This,pVal)	\
    (This)->lpVtbl -> get_pageWidth(This,pVal)

#define IPDDocument_get_pageHeight(This,pVal)	\
    (This)->lpVtbl -> get_pageHeight(This,pVal)

#define IPDDocument_get_facingPages(This,pVal)	\
    (This)->lpVtbl -> get_facingPages(This,pVal)

#define IPDDocument_get_layers(This,pVal)	\
    (This)->lpVtbl -> get_layers(This,pVal)

#define IPDDocument_get_masterSpreads(This,pVal)	\
    (This)->lpVtbl -> get_masterSpreads(This,pVal)

#define IPDDocument_get_masterPages(This,pVal)	\
    (This)->lpVtbl -> get_masterPages(This,pVal)

#define IPDDocument_get_images(This,pVal)	\
    (This)->lpVtbl -> get_images(This,pVal)

#define IPDDocument_get_swatches(This,pVal)	\
    (This)->lpVtbl -> get_swatches(This,pVal)

#define IPDDocument_get_stories(This,pVal)	\
    (This)->lpVtbl -> get_stories(This,pVal)

#define IPDDocument_ShowViews(This)	\
    (This)->lpVtbl -> ShowViews(This)

#define IPDDocument_NewDocument(This)	\
    (This)->lpVtbl -> NewDocument(This)

#define IPDDocument_createObjectFrame(This,pVal)	\
    (This)->lpVtbl -> createObjectFrame(This,pVal)

#define IPDDocument_createContentGraphic(This,pVal)	\
    (This)->lpVtbl -> createContentGraphic(This,pVal)

#define IPDDocument_loadImage(This,pathName,pVal)	\
    (This)->lpVtbl -> loadImage(This,pathName,pVal)

#define IPDDocument_createContentText(This,pVal)	\
    (This)->lpVtbl -> createContentText(This,pVal)

#define IPDDocument_getMasterSpreadByName(This,prefix,name,pVal)	\
    (This)->lpVtbl -> getMasterSpreadByName(This,prefix,name,pVal)

#define IPDDocument_getSpreadByUniqId(This,guid,pVal)	\
    (This)->lpVtbl -> getSpreadByUniqId(This,guid,pVal)

#define IPDDocument_createObjectGroup(This,guid,pVal)	\
    (This)->lpVtbl -> createObjectGroup(This,guid,pVal)

#define IPDDocument_NewWindow(This,pVal)	\
    (This)->lpVtbl -> NewWindow(This,pVal)

#define IPDDocument_createStory(This,pVal)	\
    (This)->lpVtbl -> createStory(This,pVal)

#define IPDDocument_appendStory(This,story)	\
    (This)->lpVtbl -> appendStory(This,story)

#define IPDDocument_createPathText(This,pVal)	\
    (This)->lpVtbl -> createPathText(This,pVal)

#define IPDDocument_insertPagesBefore(This,nPages,nBeforePage)	\
    (This)->lpVtbl -> insertPagesBefore(This,nPages,nBeforePage)

#define IPDDocument_insertPagesAfter(This,nPages,nAfterPage)	\
    (This)->lpVtbl -> insertPagesAfter(This,nPages,nAfterPage)

#define IPDDocument_getStoryById(This,guid,pVal)	\
    (This)->lpVtbl -> getStoryById(This,guid,pVal)

#define IPDDocument_get_firstSection(This,pVal)	\
    (This)->lpVtbl -> get_firstSection(This,pVal)

#define IPDDocument_createSection(This,pVal)	\
    (This)->lpVtbl -> createSection(This,pVal)

#define IPDDocument_deleteLayer(This,layer)	\
    (This)->lpVtbl -> deleteLayer(This,layer)

#define IPDDocument_insertLayerBefore(This,layer,before)	\
    (This)->lpVtbl -> insertLayerBefore(This,layer,before)

#define IPDDocument_getLayerByUniqId(This,guid,pVal)	\
    (This)->lpVtbl -> getLayerByUniqId(This,guid,pVal)

#define IPDDocument_get_fileTitle(This,pVal)	\
    (This)->lpVtbl -> get_fileTitle(This,pVal)

#define IPDDocument_put_fileTitle(This,newVal)	\
    (This)->lpVtbl -> put_fileTitle(This,newVal)

#define IPDDocument_removeStory(This,story)	\
    (This)->lpVtbl -> removeStory(This,story)

#define IPDDocument_createImage(This,width,height,mode,pVal)	\
    (This)->lpVtbl -> createImage(This,width,height,mode,pVal)

#define IPDDocument_get_symbols(This,pVal)	\
    (This)->lpVtbl -> get_symbols(This,pVal)

#define IPDDocument_appendSymbol(This,symbol)	\
    (This)->lpVtbl -> appendSymbol(This,symbol)

#define IPDDocument_getSymbolByName(This,name,pVal)	\
    (This)->lpVtbl -> getSymbolByName(This,name,pVal)

#define IPDDocument_get_firstSpread(This,pVal)	\
    (This)->lpVtbl -> get_firstSpread(This,pVal)

#define IPDDocument_get_lastSpread(This,pVal)	\
    (This)->lpVtbl -> get_lastSpread(This,pVal)

#define IPDDocument_loadImageFromStream(This,stream,pVal)	\
    (This)->lpVtbl -> loadImageFromStream(This,stream,pVal)

#define IPDDocument_get_showTextThreads(This,pVal)	\
    (This)->lpVtbl -> get_showTextThreads(This,pVal)

#define IPDDocument_put_showTextThreads(This,newVal)	\
    (This)->lpVtbl -> put_showTextThreads(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_filePath_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_filePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocument_put_filePath_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDDocument_put_filePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_undoManager_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IOleUndoManager __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_undoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_spreads_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_spreads_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_pages_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_pages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_pageWidth_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_pageWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_pageHeight_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_pageHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_facingPages_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_facingPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_layers_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_layers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_masterSpreads_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_masterSpreads_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_masterPages_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_masterPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_images_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_images_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_swatches_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_swatches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_stories_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_stories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_ShowViews_Proxy( 
    IPDDocument __RPC_FAR * This);


void __RPC_STUB IPDDocument_ShowViews_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_NewDocument_Proxy( 
    IPDDocument __RPC_FAR * This);


void __RPC_STUB IPDDocument_NewDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createObjectFrame_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDObjectFrame __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createObjectFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createContentGraphic_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDContentGraphic __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createContentGraphic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_loadImage_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_loadImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createContentText_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDContentText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createContentText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_getMasterSpreadByName_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ BSTR prefix,
    /* [in] */ BSTR name,
    /* [retval][out] */ IPDSpreadMaster __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_getMasterSpreadByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_getSpreadByUniqId_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ GUID guid,
    /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_getSpreadByUniqId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createObjectGroup_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ GUID guid,
    /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createObjectGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_NewWindow_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDDocumentView __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_NewWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createStory_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createStory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_appendStory_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ IPDStory __RPC_FAR *story);


void __RPC_STUB IPDDocument_appendStory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createPathText_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDPathText __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createPathText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_insertPagesBefore_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ long nPages,
    /* [in] */ long nBeforePage);


void __RPC_STUB IPDDocument_insertPagesBefore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_insertPagesAfter_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ long nPages,
    /* [in] */ long nAfterPage);


void __RPC_STUB IPDDocument_insertPagesAfter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_getStoryById_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ GUID guid,
    /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_getStoryById_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_firstSection_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_firstSection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createSection_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createSection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_deleteLayer_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ IPDLayer __RPC_FAR *layer);


void __RPC_STUB IPDDocument_deleteLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_insertLayerBefore_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ IPDLayer __RPC_FAR *layer,
    /* [in] */ IPDLayer __RPC_FAR *before);


void __RPC_STUB IPDDocument_insertLayerBefore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_getLayerByUniqId_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ GUID guid,
    /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_getLayerByUniqId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_fileTitle_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_fileTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocument_put_fileTitle_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPDDocument_put_fileTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_removeStory_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ IPDStory __RPC_FAR *story);


void __RPC_STUB IPDDocument_removeStory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_createImage_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ long width,
    /* [in] */ long height,
    /* [in] */ DWORD mode,
    /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_createImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_symbols_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_symbols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_appendSymbol_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ IPDSymbol __RPC_FAR *symbol);


void __RPC_STUB IPDDocument_appendSymbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_getSymbolByName_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ IPDSymbol __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_getSymbolByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_firstSpread_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDSpreadDocument __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_firstSpread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_lastSpread_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ IPDSpreadDocument __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_lastSpread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDDocument_loadImageFromStream_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ IStream __RPC_FAR *stream,
    /* [retval][out] */ IPDImage __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDDocument_loadImageFromStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDDocument_get_showTextThreads_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDDocument_get_showTextThreads_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDDocument_put_showTextThreads_Proxy( 
    IPDDocument __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDDocument_put_showTextThreads_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDDocument_INTERFACE_DEFINED__ */


#ifndef __IPDTextSelection_INTERFACE_DEFINED__
#define __IPDTextSelection_INTERFACE_DEFINED__

/* interface IPDTextSelection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDTextSelection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDE1F90E-48F6-4803-BFE4-97FFC6674D9B")
    IPDTextSelection : public IPDTextRange
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EndKey( 
            /* [in] */ long Unit,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HomeKey( 
            /* [in] */ long Unit,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveRight( 
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveLeft( 
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveUp( 
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveDown( 
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ ILDOMNode __RPC_FAR *node,
            /* [in] */ long offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveDOM( 
            /* [in] */ ILDOMNode __RPC_FAR *node,
            /* [in] */ long offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TypeText( 
            /* [in] */ BSTR bstr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDTextSelectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDTextSelection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDTextSelection __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDOMRange )( 
            IPDTextSelection __RPC_FAR * This,
            /* [retval][out] */ ILDOMRange __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStory )( 
            IPDTextSelection __RPC_FAR * This,
            /* [retval][out] */ IPDStory __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCollapsed )( 
            IPDTextSelection __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndKey )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HomeKey )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveRight )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveLeft )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveUp )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveDown )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ long Unit,
            /* [in] */ long Count,
            /* [in] */ long Extend,
            /* [retval][out] */ long __RPC_FAR *pDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *node,
            /* [in] */ long offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveDOM )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *node,
            /* [in] */ long offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TypeText )( 
            IPDTextSelection __RPC_FAR * This,
            /* [in] */ BSTR bstr);
        
        END_INTERFACE
    } IPDTextSelectionVtbl;

    interface IPDTextSelection
    {
        CONST_VTBL struct IPDTextSelectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDTextSelection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDTextSelection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDTextSelection_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDTextSelection_GetDOMRange(This,pVal)	\
    (This)->lpVtbl -> GetDOMRange(This,pVal)

#define IPDTextSelection_GetStory(This,pVal)	\
    (This)->lpVtbl -> GetStory(This,pVal)

#define IPDTextSelection_Delete(This,Unit,Count,pDelta)	\
    (This)->lpVtbl -> Delete(This,Unit,Count,pDelta)

#define IPDTextSelection_IsCollapsed(This,pVal)	\
    (This)->lpVtbl -> IsCollapsed(This,pVal)


#define IPDTextSelection_EndKey(This,Unit,Extend,pDelta)	\
    (This)->lpVtbl -> EndKey(This,Unit,Extend,pDelta)

#define IPDTextSelection_HomeKey(This,Unit,Extend,pDelta)	\
    (This)->lpVtbl -> HomeKey(This,Unit,Extend,pDelta)

#define IPDTextSelection_MoveRight(This,Unit,Count,Extend,pDelta)	\
    (This)->lpVtbl -> MoveRight(This,Unit,Count,Extend,pDelta)

#define IPDTextSelection_MoveLeft(This,Unit,Count,Extend,pDelta)	\
    (This)->lpVtbl -> MoveLeft(This,Unit,Count,Extend,pDelta)

#define IPDTextSelection_MoveUp(This,Unit,Count,Extend,pDelta)	\
    (This)->lpVtbl -> MoveUp(This,Unit,Count,Extend,pDelta)

#define IPDTextSelection_MoveDown(This,Unit,Count,Extend,pDelta)	\
    (This)->lpVtbl -> MoveDown(This,Unit,Count,Extend,pDelta)

#define IPDTextSelection_Set(This,node,offset)	\
    (This)->lpVtbl -> Set(This,node,offset)

#define IPDTextSelection_MoveDOM(This,node,offset)	\
    (This)->lpVtbl -> MoveDOM(This,node,offset)

#define IPDTextSelection_TypeText(This,bstr)	\
    (This)->lpVtbl -> TypeText(This,bstr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_EndKey_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ long Unit,
    /* [in] */ long Extend,
    /* [retval][out] */ long __RPC_FAR *pDelta);


void __RPC_STUB IPDTextSelection_EndKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_HomeKey_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ long Unit,
    /* [in] */ long Extend,
    /* [retval][out] */ long __RPC_FAR *pDelta);


void __RPC_STUB IPDTextSelection_HomeKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_MoveRight_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ long Unit,
    /* [in] */ long Count,
    /* [in] */ long Extend,
    /* [retval][out] */ long __RPC_FAR *pDelta);


void __RPC_STUB IPDTextSelection_MoveRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_MoveLeft_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ long Unit,
    /* [in] */ long Count,
    /* [in] */ long Extend,
    /* [retval][out] */ long __RPC_FAR *pDelta);


void __RPC_STUB IPDTextSelection_MoveLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_MoveUp_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ long Unit,
    /* [in] */ long Count,
    /* [in] */ long Extend,
    /* [retval][out] */ long __RPC_FAR *pDelta);


void __RPC_STUB IPDTextSelection_MoveUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_MoveDown_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ long Unit,
    /* [in] */ long Count,
    /* [in] */ long Extend,
    /* [retval][out] */ long __RPC_FAR *pDelta);


void __RPC_STUB IPDTextSelection_MoveDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_Set_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ ILDOMNode __RPC_FAR *node,
    /* [in] */ long offset);


void __RPC_STUB IPDTextSelection_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_MoveDOM_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ ILDOMNode __RPC_FAR *node,
    /* [in] */ long offset);


void __RPC_STUB IPDTextSelection_MoveDOM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextSelection_TypeText_Proxy( 
    IPDTextSelection __RPC_FAR * This,
    /* [in] */ BSTR bstr);


void __RPC_STUB IPDTextSelection_TypeText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDTextSelection_INTERFACE_DEFINED__ */


#ifndef __DispIPDDocument_INTERFACE_DEFINED__
#define __DispIPDDocument_INTERFACE_DEFINED__

/* interface DispIPDDocument */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_DispIPDDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3FAE561-227D-11d6-95F0-0002E3045703")
    DispIPDDocument : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct DispIPDDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DispIPDDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DispIPDDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DispIPDDocument __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DispIPDDocument __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DispIPDDocument __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DispIPDDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DispIPDDocument __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DispIPDDocumentVtbl;

    interface DispIPDDocument
    {
        CONST_VTBL struct DispIPDDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DispIPDDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DispIPDDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DispIPDDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DispIPDDocument_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DispIPDDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DispIPDDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DispIPDDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __DispIPDDocument_INTERFACE_DEFINED__ */


#ifndef __IPDPage_INTERFACE_DEFINED__
#define __IPDPage_INTERFACE_DEFINED__

/* interface IPDPage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDPage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ECA9360F-2E0C-44cd-8FDC-9A0E5E44EEB9")
    IPDPage : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_marginTop( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_marginBottom( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_marginLeft( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_marginRight( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_marginInside( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_marginOutside( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ownerSpread( 
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_baseMaster( 
            /* [retval][out] */ IPDSpreadMaster __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_baseMaster( 
            /* [in] */ IPDSpreadMaster __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_section( 
            /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_section( 
            /* [in] */ IPDSection __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_columnNumber( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_columnNumber( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_columnGutter( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_columnGutter( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setMarginsAndColumns( 
            /* [in] */ double marginTop,
            /* [in] */ double marginBottom,
            /* [in] */ double marginInside,
            /* [in] */ double marginOutside,
            /* [in] */ long columnNumber,
            /* [in] */ double columnGutter) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getPageRect( 
            /* [retval][out] */ RectD __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDPage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDPage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDPage __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginTop )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginBottom )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginLeft )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginRight )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginInside )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_marginOutside )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerSpread )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_baseMaster )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ IPDSpreadMaster __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_baseMaster )( 
            IPDPage __RPC_FAR * This,
            /* [in] */ IPDSpreadMaster __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_section )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_section )( 
            IPDPage __RPC_FAR * This,
            /* [in] */ IPDSection __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_columnNumber )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_columnNumber )( 
            IPDPage __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_columnGutter )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_columnGutter )( 
            IPDPage __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setMarginsAndColumns )( 
            IPDPage __RPC_FAR * This,
            /* [in] */ double marginTop,
            /* [in] */ double marginBottom,
            /* [in] */ double marginInside,
            /* [in] */ double marginOutside,
            /* [in] */ long columnNumber,
            /* [in] */ double columnGutter);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPageRect )( 
            IPDPage __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDPageVtbl;

    interface IPDPage
    {
        CONST_VTBL struct IPDPageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDPage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDPage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDPage_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDPage_get_marginTop(This,pVal)	\
    (This)->lpVtbl -> get_marginTop(This,pVal)

#define IPDPage_get_marginBottom(This,pVal)	\
    (This)->lpVtbl -> get_marginBottom(This,pVal)

#define IPDPage_get_marginLeft(This,pVal)	\
    (This)->lpVtbl -> get_marginLeft(This,pVal)

#define IPDPage_get_marginRight(This,pVal)	\
    (This)->lpVtbl -> get_marginRight(This,pVal)

#define IPDPage_get_marginInside(This,pVal)	\
    (This)->lpVtbl -> get_marginInside(This,pVal)

#define IPDPage_get_marginOutside(This,pVal)	\
    (This)->lpVtbl -> get_marginOutside(This,pVal)

#define IPDPage_get_ownerSpread(This,pVal)	\
    (This)->lpVtbl -> get_ownerSpread(This,pVal)

#define IPDPage_get_baseMaster(This,pVal)	\
    (This)->lpVtbl -> get_baseMaster(This,pVal)

#define IPDPage_put_baseMaster(This,newVal)	\
    (This)->lpVtbl -> put_baseMaster(This,newVal)

#define IPDPage_get_section(This,pVal)	\
    (This)->lpVtbl -> get_section(This,pVal)

#define IPDPage_put_section(This,newVal)	\
    (This)->lpVtbl -> put_section(This,newVal)

#define IPDPage_get_columnNumber(This,pVal)	\
    (This)->lpVtbl -> get_columnNumber(This,pVal)

#define IPDPage_put_columnNumber(This,newVal)	\
    (This)->lpVtbl -> put_columnNumber(This,newVal)

#define IPDPage_get_columnGutter(This,pVal)	\
    (This)->lpVtbl -> get_columnGutter(This,pVal)

#define IPDPage_put_columnGutter(This,newVal)	\
    (This)->lpVtbl -> put_columnGutter(This,newVal)

#define IPDPage_setMarginsAndColumns(This,marginTop,marginBottom,marginInside,marginOutside,columnNumber,columnGutter)	\
    (This)->lpVtbl -> setMarginsAndColumns(This,marginTop,marginBottom,marginInside,marginOutside,columnNumber,columnGutter)

#define IPDPage_getPageRect(This,pVal)	\
    (This)->lpVtbl -> getPageRect(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_marginTop_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_marginTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_marginBottom_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_marginBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_marginLeft_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_marginLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_marginRight_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_marginRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_marginInside_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_marginInside_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_marginOutside_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_marginOutside_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_ownerSpread_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_ownerSpread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_baseMaster_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ IPDSpreadMaster __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_baseMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPage_put_baseMaster_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [in] */ IPDSpreadMaster __RPC_FAR *newVal);


void __RPC_STUB IPDPage_put_baseMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_section_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ IPDSection __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_section_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPage_put_section_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [in] */ IPDSection __RPC_FAR *newVal);


void __RPC_STUB IPDPage_put_section_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_columnNumber_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_columnNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPage_put_columnNumber_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDPage_put_columnNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPage_get_columnGutter_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDPage_get_columnGutter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDPage_put_columnGutter_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDPage_put_columnGutter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPage_setMarginsAndColumns_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [in] */ double marginTop,
    /* [in] */ double marginBottom,
    /* [in] */ double marginInside,
    /* [in] */ double marginOutside,
    /* [in] */ long columnNumber,
    /* [in] */ double columnGutter);


void __RPC_STUB IPDPage_setMarginsAndColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPage_getPageRect_Proxy( 
    IPDPage __RPC_FAR * This,
    /* [retval][out] */ RectD __RPC_FAR *pVal);


void __RPC_STUB IPDPage_getPageRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDPage_INTERFACE_DEFINED__ */


#ifndef __IPDSubPath_INTERFACE_DEFINED__
#define __IPDSubPath_INTERFACE_DEFINED__

/* interface IPDSubPath */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDSubPath;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BE2171BE-E3BD-4c9e-BD2F-747D2EDF0810")
    IPDSubPath : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pointCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_closed( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_closed( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE reverse( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getPoint( 
            /* [in] */ long index,
            /* [retval][out] */ BezierPoint __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setPoint( 
            /* [in] */ long index,
            /* [in] */ BezierPoint __RPC_FAR *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setEllipse( 
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double right,
            /* [in] */ double bottom) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setRectangle( 
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double right,
            /* [in] */ double bottom) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ double dx,
            /* [in] */ double dy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendPoint( 
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertPoint( 
            /* [in] */ long index,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getLength( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getPointOnLength( 
            /* [in] */ double onlength,
            /* [out] */ double __RPC_FAR *px,
            /* [out] */ double __RPC_FAR *py,
            /* [out] */ double __RPC_FAR *angle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setLine( 
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertAnchorPointAt( 
            /* [in] */ long segment,
            /* [in] */ double t) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE deleteAnchorPoint( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendSubPathPoints( 
            /* [in] */ IPDSubPath __RPC_FAR *subpath) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeAllPoints( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDSubPathVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDSubPath __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDSubPath __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pointCount )( 
            IPDSubPath __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_closed )( 
            IPDSubPath __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_closed )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *reverse )( 
            IPDSubPath __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPoint )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ BezierPoint __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setPoint )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ BezierPoint __RPC_FAR *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setEllipse )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double right,
            /* [in] */ double bottom);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setRectangle )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double right,
            /* [in] */ double bottom);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ double dx,
            /* [in] */ double dy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendPoint )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertPoint )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getLength )( 
            IPDSubPath __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPointOnLength )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ double onlength,
            /* [out] */ double __RPC_FAR *px,
            /* [out] */ double __RPC_FAR *py,
            /* [out] */ double __RPC_FAR *angle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setLine )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertAnchorPointAt )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ long segment,
            /* [in] */ double t);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deleteAnchorPoint )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendSubPathPoints )( 
            IPDSubPath __RPC_FAR * This,
            /* [in] */ IPDSubPath __RPC_FAR *subpath);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAllPoints )( 
            IPDSubPath __RPC_FAR * This);
        
        END_INTERFACE
    } IPDSubPathVtbl;

    interface IPDSubPath
    {
        CONST_VTBL struct IPDSubPathVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDSubPath_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDSubPath_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDSubPath_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDSubPath_get_pointCount(This,pVal)	\
    (This)->lpVtbl -> get_pointCount(This,pVal)

#define IPDSubPath_get_closed(This,pVal)	\
    (This)->lpVtbl -> get_closed(This,pVal)

#define IPDSubPath_put_closed(This,newVal)	\
    (This)->lpVtbl -> put_closed(This,newVal)

#define IPDSubPath_reverse(This)	\
    (This)->lpVtbl -> reverse(This)

#define IPDSubPath_getPoint(This,index,pVal)	\
    (This)->lpVtbl -> getPoint(This,index,pVal)

#define IPDSubPath_setPoint(This,index,point)	\
    (This)->lpVtbl -> setPoint(This,index,point)

#define IPDSubPath_setEllipse(This,left,top,right,bottom)	\
    (This)->lpVtbl -> setEllipse(This,left,top,right,bottom)

#define IPDSubPath_setRectangle(This,left,top,right,bottom)	\
    (This)->lpVtbl -> setRectangle(This,left,top,right,bottom)

#define IPDSubPath_Move(This,dx,dy)	\
    (This)->lpVtbl -> Move(This,dx,dy)

#define IPDSubPath_appendPoint(This,x,y,x1,y1,x2,y2,pVal)	\
    (This)->lpVtbl -> appendPoint(This,x,y,x1,y1,x2,y2,pVal)

#define IPDSubPath_insertPoint(This,index,x,y,x1,y1,x2,y2)	\
    (This)->lpVtbl -> insertPoint(This,index,x,y,x1,y1,x2,y2)

#define IPDSubPath_getLength(This,pVal)	\
    (This)->lpVtbl -> getLength(This,pVal)

#define IPDSubPath_getPointOnLength(This,onlength,px,py,angle)	\
    (This)->lpVtbl -> getPointOnLength(This,onlength,px,py,angle)

#define IPDSubPath_setLine(This,x1,y1,x2,y2)	\
    (This)->lpVtbl -> setLine(This,x1,y1,x2,y2)

#define IPDSubPath_insertAnchorPointAt(This,segment,t)	\
    (This)->lpVtbl -> insertAnchorPointAt(This,segment,t)

#define IPDSubPath_deleteAnchorPoint(This,index)	\
    (This)->lpVtbl -> deleteAnchorPoint(This,index)

#define IPDSubPath_appendSubPathPoints(This,subpath)	\
    (This)->lpVtbl -> appendSubPathPoints(This,subpath)

#define IPDSubPath_removeAllPoints(This)	\
    (This)->lpVtbl -> removeAllPoints(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSubPath_get_pointCount_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDSubPath_get_pointCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDSubPath_get_closed_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDSubPath_get_closed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDSubPath_put_closed_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDSubPath_put_closed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_reverse_Proxy( 
    IPDSubPath __RPC_FAR * This);


void __RPC_STUB IPDSubPath_reverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_getPoint_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ BezierPoint __RPC_FAR *pVal);


void __RPC_STUB IPDSubPath_getPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_setPoint_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ BezierPoint __RPC_FAR *point);


void __RPC_STUB IPDSubPath_setPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_setEllipse_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ double left,
    /* [in] */ double top,
    /* [in] */ double right,
    /* [in] */ double bottom);


void __RPC_STUB IPDSubPath_setEllipse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_setRectangle_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ double left,
    /* [in] */ double top,
    /* [in] */ double right,
    /* [in] */ double bottom);


void __RPC_STUB IPDSubPath_setRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_Move_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ double dx,
    /* [in] */ double dy);


void __RPC_STUB IPDSubPath_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_appendPoint_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ double x,
    /* [in] */ double y,
    /* [in] */ double x1,
    /* [in] */ double y1,
    /* [in] */ double x2,
    /* [in] */ double y2,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDSubPath_appendPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_insertPoint_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ double x,
    /* [in] */ double y,
    /* [in] */ double x1,
    /* [in] */ double y1,
    /* [in] */ double x2,
    /* [in] */ double y2);


void __RPC_STUB IPDSubPath_insertPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_getLength_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDSubPath_getLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_getPointOnLength_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ double onlength,
    /* [out] */ double __RPC_FAR *px,
    /* [out] */ double __RPC_FAR *py,
    /* [out] */ double __RPC_FAR *angle);


void __RPC_STUB IPDSubPath_getPointOnLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_setLine_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ double x1,
    /* [in] */ double y1,
    /* [in] */ double x2,
    /* [in] */ double y2);


void __RPC_STUB IPDSubPath_setLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_insertAnchorPointAt_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ long segment,
    /* [in] */ double t);


void __RPC_STUB IPDSubPath_insertAnchorPointAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_deleteAnchorPoint_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB IPDSubPath_deleteAnchorPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_appendSubPathPoints_Proxy( 
    IPDSubPath __RPC_FAR * This,
    /* [in] */ IPDSubPath __RPC_FAR *subpath);


void __RPC_STUB IPDSubPath_appendSubPathPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDSubPath_removeAllPoints_Proxy( 
    IPDSubPath __RPC_FAR * This);


void __RPC_STUB IPDSubPath_removeAllPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDSubPath_INTERFACE_DEFINED__ */


#ifndef __IPDPath_INTERFACE_DEFINED__
#define __IPDPath_INTERFACE_DEFINED__

/* interface IPDPath */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDPath;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("752A4765-EE35-43fb-B4FD-D60D877182CB")
    IPDPath : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pointCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_subPathCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getSubPath( 
            /* [in] */ long index,
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertSubPath( 
            /* [in] */ long index,
            /* [in] */ IPDSubPath __RPC_FAR *subPath) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeSubPath( 
            /* [in] */ IPDSubPath __RPC_FAR *subpath) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeSubPathByIndex( 
            /* [in] */ long index,
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE createSubPath( 
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ double dx,
            /* [in] */ double dy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getPoint( 
            /* [in] */ long index,
            /* [retval][out] */ BezierPoint __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setPoint( 
            /* [in] */ long index,
            /* [in] */ BezierPoint __RPC_FAR *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertPointBefore( 
            /* [in] */ long index,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertPointAfter( 
            /* [in] */ long index,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE calculateBBox( 
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [retval][out] */ RectD __RPC_FAR *bbox) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE offset( 
            /* [in] */ double distance,
            /* [in] */ double tolerance,
            /* [in] */ IPDPath __RPC_FAR *other) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getPointNearPath( 
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ double mousex,
            /* [in] */ double mousey,
            /* [in] */ double tolerance,
            /* [out] */ long __RPC_FAR *segindex,
            /* [out] */ double __RPC_FAR *pt,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getPointNearAnchorPoint( 
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ double mousex,
            /* [in] */ double mousey,
            /* [in] */ double tolerance,
            /* [retval][out] */ long __RPC_FAR *pIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsRectangular( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE insertAnchorPointAt( 
            /* [in] */ long segment,
            /* [in] */ double t) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getSubPathFromIndex( 
            /* [in] */ long index,
            /* [out] */ long __RPC_FAR *pindex,
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *psubpath) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE deleteAnchorPoint( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE splitOnSegment( 
            /* [in] */ long segindex,
            /* [retval][out] */ long __RPC_FAR *pRotateVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE splitOnAnchor( 
            /* [in] */ long index,
            /* [retval][out] */ long __RPC_FAR *pRotateVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeSubPaths( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE transformPoints( 
            /* [in] */ IPDMatrix __RPC_FAR *matrix) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setRectangle( 
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double right,
            /* [in] */ double bottom) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDPathVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDPath __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDPath __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pointCount )( 
            IPDPath __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_subPathCount )( 
            IPDPath __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSubPath )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertSubPath )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ IPDSubPath __RPC_FAR *subPath);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeSubPath )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ IPDSubPath __RPC_FAR *subpath);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeSubPathByIndex )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createSubPath )( 
            IPDPath __RPC_FAR * This,
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ double dx,
            /* [in] */ double dy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPoint )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ BezierPoint __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setPoint )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ BezierPoint __RPC_FAR *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertPointBefore )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertPointAfter )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double x1,
            /* [in] */ double y1,
            /* [in] */ double x2,
            /* [in] */ double y2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *calculateBBox )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [retval][out] */ RectD __RPC_FAR *bbox);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *offset )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ double distance,
            /* [in] */ double tolerance,
            /* [in] */ IPDPath __RPC_FAR *other);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPointNearPath )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ double mousex,
            /* [in] */ double mousey,
            /* [in] */ double tolerance,
            /* [out] */ long __RPC_FAR *segindex,
            /* [out] */ double __RPC_FAR *pt,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPointNearAnchorPoint )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ IPDMatrix __RPC_FAR *matrix,
            /* [in] */ double mousex,
            /* [in] */ double mousey,
            /* [in] */ double tolerance,
            /* [retval][out] */ long __RPC_FAR *pIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsRectangular )( 
            IPDPath __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertAnchorPointAt )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long segment,
            /* [in] */ double t);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSubPathFromIndex )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [out] */ long __RPC_FAR *pindex,
            /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *psubpath);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deleteAnchorPoint )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *splitOnSegment )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long segindex,
            /* [retval][out] */ long __RPC_FAR *pRotateVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *splitOnAnchor )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ long __RPC_FAR *pRotateVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeSubPaths )( 
            IPDPath __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *transformPoints )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ IPDMatrix __RPC_FAR *matrix);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setRectangle )( 
            IPDPath __RPC_FAR * This,
            /* [in] */ double left,
            /* [in] */ double top,
            /* [in] */ double right,
            /* [in] */ double bottom);
        
        END_INTERFACE
    } IPDPathVtbl;

    interface IPDPath
    {
        CONST_VTBL struct IPDPathVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDPath_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDPath_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDPath_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDPath_get_pointCount(This,pVal)	\
    (This)->lpVtbl -> get_pointCount(This,pVal)

#define IPDPath_get_subPathCount(This,pVal)	\
    (This)->lpVtbl -> get_subPathCount(This,pVal)

#define IPDPath_getSubPath(This,index,pVal)	\
    (This)->lpVtbl -> getSubPath(This,index,pVal)

#define IPDPath_insertSubPath(This,index,subPath)	\
    (This)->lpVtbl -> insertSubPath(This,index,subPath)

#define IPDPath_removeSubPath(This,subpath)	\
    (This)->lpVtbl -> removeSubPath(This,subpath)

#define IPDPath_removeSubPathByIndex(This,index,pVal)	\
    (This)->lpVtbl -> removeSubPathByIndex(This,index,pVal)

#define IPDPath_createSubPath(This,pVal)	\
    (This)->lpVtbl -> createSubPath(This,pVal)

#define IPDPath_Move(This,dx,dy)	\
    (This)->lpVtbl -> Move(This,dx,dy)

#define IPDPath_getPoint(This,index,pVal)	\
    (This)->lpVtbl -> getPoint(This,index,pVal)

#define IPDPath_setPoint(This,index,point)	\
    (This)->lpVtbl -> setPoint(This,index,point)

#define IPDPath_insertPointBefore(This,index,x,y,x1,y1,x2,y2)	\
    (This)->lpVtbl -> insertPointBefore(This,index,x,y,x1,y1,x2,y2)

#define IPDPath_insertPointAfter(This,index,x,y,x1,y1,x2,y2)	\
    (This)->lpVtbl -> insertPointAfter(This,index,x,y,x1,y1,x2,y2)

#define IPDPath_calculateBBox(This,matrix,bbox)	\
    (This)->lpVtbl -> calculateBBox(This,matrix,bbox)

#define IPDPath_offset(This,distance,tolerance,other)	\
    (This)->lpVtbl -> offset(This,distance,tolerance,other)

#define IPDPath_getPointNearPath(This,matrix,mousex,mousey,tolerance,segindex,pt,pVal)	\
    (This)->lpVtbl -> getPointNearPath(This,matrix,mousex,mousey,tolerance,segindex,pt,pVal)

#define IPDPath_getPointNearAnchorPoint(This,matrix,mousex,mousey,tolerance,pIndex)	\
    (This)->lpVtbl -> getPointNearAnchorPoint(This,matrix,mousex,mousey,tolerance,pIndex)

#define IPDPath_IsRectangular(This,pVal)	\
    (This)->lpVtbl -> IsRectangular(This,pVal)

#define IPDPath_insertAnchorPointAt(This,segment,t)	\
    (This)->lpVtbl -> insertAnchorPointAt(This,segment,t)

#define IPDPath_getSubPathFromIndex(This,index,pindex,psubpath)	\
    (This)->lpVtbl -> getSubPathFromIndex(This,index,pindex,psubpath)

#define IPDPath_deleteAnchorPoint(This,index)	\
    (This)->lpVtbl -> deleteAnchorPoint(This,index)

#define IPDPath_splitOnSegment(This,segindex,pRotateVal)	\
    (This)->lpVtbl -> splitOnSegment(This,segindex,pRotateVal)

#define IPDPath_splitOnAnchor(This,index,pRotateVal)	\
    (This)->lpVtbl -> splitOnAnchor(This,index,pRotateVal)

#define IPDPath_removeSubPaths(This)	\
    (This)->lpVtbl -> removeSubPaths(This)

#define IPDPath_transformPoints(This,matrix)	\
    (This)->lpVtbl -> transformPoints(This,matrix)

#define IPDPath_setRectangle(This,left,top,right,bottom)	\
    (This)->lpVtbl -> setRectangle(This,left,top,right,bottom)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPath_get_pointCount_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDPath_get_pointCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDPath_get_subPathCount_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDPath_get_subPathCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_getSubPath_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDPath_getSubPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_insertSubPath_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ IPDSubPath __RPC_FAR *subPath);


void __RPC_STUB IPDPath_insertSubPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_removeSubPath_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ IPDSubPath __RPC_FAR *subpath);


void __RPC_STUB IPDPath_removeSubPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_removeSubPathByIndex_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDPath_removeSubPathByIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_createSubPath_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDPath_createSubPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_Move_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ double dx,
    /* [in] */ double dy);


void __RPC_STUB IPDPath_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_getPoint_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ BezierPoint __RPC_FAR *pVal);


void __RPC_STUB IPDPath_getPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_setPoint_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ BezierPoint __RPC_FAR *point);


void __RPC_STUB IPDPath_setPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_insertPointBefore_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ double x,
    /* [in] */ double y,
    /* [in] */ double x1,
    /* [in] */ double y1,
    /* [in] */ double x2,
    /* [in] */ double y2);


void __RPC_STUB IPDPath_insertPointBefore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_insertPointAfter_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ double x,
    /* [in] */ double y,
    /* [in] */ double x1,
    /* [in] */ double y1,
    /* [in] */ double x2,
    /* [in] */ double y2);


void __RPC_STUB IPDPath_insertPointAfter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_calculateBBox_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ IPDMatrix __RPC_FAR *matrix,
    /* [retval][out] */ RectD __RPC_FAR *bbox);


void __RPC_STUB IPDPath_calculateBBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_offset_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ double distance,
    /* [in] */ double tolerance,
    /* [in] */ IPDPath __RPC_FAR *other);


void __RPC_STUB IPDPath_offset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_getPointNearPath_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ IPDMatrix __RPC_FAR *matrix,
    /* [in] */ double mousex,
    /* [in] */ double mousey,
    /* [in] */ double tolerance,
    /* [out] */ long __RPC_FAR *segindex,
    /* [out] */ double __RPC_FAR *pt,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDPath_getPointNearPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_getPointNearAnchorPoint_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ IPDMatrix __RPC_FAR *matrix,
    /* [in] */ double mousex,
    /* [in] */ double mousey,
    /* [in] */ double tolerance,
    /* [retval][out] */ long __RPC_FAR *pIndex);


void __RPC_STUB IPDPath_getPointNearAnchorPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_IsRectangular_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDPath_IsRectangular_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_insertAnchorPointAt_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long segment,
    /* [in] */ double t);


void __RPC_STUB IPDPath_insertAnchorPointAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_getSubPathFromIndex_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [out] */ long __RPC_FAR *pindex,
    /* [retval][out] */ IPDSubPath __RPC_FAR *__RPC_FAR *psubpath);


void __RPC_STUB IPDPath_getSubPathFromIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_deleteAnchorPoint_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB IPDPath_deleteAnchorPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_splitOnSegment_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long segindex,
    /* [retval][out] */ long __RPC_FAR *pRotateVal);


void __RPC_STUB IPDPath_splitOnSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_splitOnAnchor_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ long __RPC_FAR *pRotateVal);


void __RPC_STUB IPDPath_splitOnAnchor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_removeSubPaths_Proxy( 
    IPDPath __RPC_FAR * This);


void __RPC_STUB IPDPath_removeSubPaths_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_transformPoints_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ IPDMatrix __RPC_FAR *matrix);


void __RPC_STUB IPDPath_transformPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDPath_setRectangle_Proxy( 
    IPDPath __RPC_FAR * This,
    /* [in] */ double left,
    /* [in] */ double top,
    /* [in] */ double right,
    /* [in] */ double bottom);


void __RPC_STUB IPDPath_setRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDPath_INTERFACE_DEFINED__ */


#ifndef __IPDObjectLocatable_INTERFACE_DEFINED__
#define __IPDObjectLocatable_INTERFACE_DEFINED__

/* interface IPDObjectLocatable */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectLocatable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("25D89B8E-7E43-4218-AFF5-195B84D9989C")
    IPDObjectLocatable : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_bounds( 
            /* [retval][out] */ RectD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_xbounds( 
            /* [retval][out] */ RectD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ double dx,
            /* [in] */ double dy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ double originx,
            /* [in] */ double originy,
            /* [in] */ double sx,
            /* [in] */ double sy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getScreenBBox( 
            /* [retval][out] */ RectD __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectLocatableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectLocatable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectLocatable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectLocatable __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_bounds )( 
            IPDObjectLocatable __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_xbounds )( 
            IPDObjectLocatable __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IPDObjectLocatable __RPC_FAR * This,
            /* [in] */ double dx,
            /* [in] */ double dy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Scale )( 
            IPDObjectLocatable __RPC_FAR * This,
            /* [in] */ double originx,
            /* [in] */ double originy,
            /* [in] */ double sx,
            /* [in] */ double sy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenBBox )( 
            IPDObjectLocatable __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDObjectLocatableVtbl;

    interface IPDObjectLocatable
    {
        CONST_VTBL struct IPDObjectLocatableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectLocatable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectLocatable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectLocatable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDObjectLocatable_get_bounds(This,pVal)	\
    (This)->lpVtbl -> get_bounds(This,pVal)

#define IPDObjectLocatable_get_xbounds(This,pVal)	\
    (This)->lpVtbl -> get_xbounds(This,pVal)

#define IPDObjectLocatable_Move(This,dx,dy)	\
    (This)->lpVtbl -> Move(This,dx,dy)

#define IPDObjectLocatable_Scale(This,originx,originy,sx,sy)	\
    (This)->lpVtbl -> Scale(This,originx,originy,sx,sy)

#define IPDObjectLocatable_getScreenBBox(This,pVal)	\
    (This)->lpVtbl -> getScreenBBox(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectLocatable_get_bounds_Proxy( 
    IPDObjectLocatable __RPC_FAR * This,
    /* [retval][out] */ RectD __RPC_FAR *pVal);


void __RPC_STUB IPDObjectLocatable_get_bounds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectLocatable_get_xbounds_Proxy( 
    IPDObjectLocatable __RPC_FAR * This,
    /* [retval][out] */ RectD __RPC_FAR *pVal);


void __RPC_STUB IPDObjectLocatable_get_xbounds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectLocatable_Move_Proxy( 
    IPDObjectLocatable __RPC_FAR * This,
    /* [in] */ double dx,
    /* [in] */ double dy);


void __RPC_STUB IPDObjectLocatable_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectLocatable_Scale_Proxy( 
    IPDObjectLocatable __RPC_FAR * This,
    /* [in] */ double originx,
    /* [in] */ double originy,
    /* [in] */ double sx,
    /* [in] */ double sy);


void __RPC_STUB IPDObjectLocatable_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectLocatable_getScreenBBox_Proxy( 
    IPDObjectLocatable __RPC_FAR * This,
    /* [retval][out] */ RectD __RPC_FAR *pVal);


void __RPC_STUB IPDObjectLocatable_getScreenBBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectLocatable_INTERFACE_DEFINED__ */


#ifndef __IPDObjectTransformable_INTERFACE_DEFINED__
#define __IPDObjectTransformable_INTERFACE_DEFINED__

/* interface IPDObjectTransformable */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectTransformable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CA848302-0F5F-11d6-95F0-0002E3045703")
    IPDObjectTransformable : public IPDObjectLocatable
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_transformMatrix( 
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_transformMatrix( 
            /* [in] */ IPDMatrix __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectTransformableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectTransformable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectTransformable __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_bounds )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_xbounds )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [in] */ double dx,
            /* [in] */ double dy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Scale )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [in] */ double originx,
            /* [in] */ double originy,
            /* [in] */ double sx,
            /* [in] */ double sy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenBBox )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transformMatrix )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_transformMatrix )( 
            IPDObjectTransformable __RPC_FAR * This,
            /* [in] */ IPDMatrix __RPC_FAR *newVal);
        
        END_INTERFACE
    } IPDObjectTransformableVtbl;

    interface IPDObjectTransformable
    {
        CONST_VTBL struct IPDObjectTransformableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectTransformable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectTransformable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectTransformable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDObjectTransformable_get_bounds(This,pVal)	\
    (This)->lpVtbl -> get_bounds(This,pVal)

#define IPDObjectTransformable_get_xbounds(This,pVal)	\
    (This)->lpVtbl -> get_xbounds(This,pVal)

#define IPDObjectTransformable_Move(This,dx,dy)	\
    (This)->lpVtbl -> Move(This,dx,dy)

#define IPDObjectTransformable_Scale(This,originx,originy,sx,sy)	\
    (This)->lpVtbl -> Scale(This,originx,originy,sx,sy)

#define IPDObjectTransformable_getScreenBBox(This,pVal)	\
    (This)->lpVtbl -> getScreenBBox(This,pVal)


#define IPDObjectTransformable_get_transformMatrix(This,pVal)	\
    (This)->lpVtbl -> get_transformMatrix(This,pVal)

#define IPDObjectTransformable_put_transformMatrix(This,newVal)	\
    (This)->lpVtbl -> put_transformMatrix(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectTransformable_get_transformMatrix_Proxy( 
    IPDObjectTransformable __RPC_FAR * This,
    /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectTransformable_get_transformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectTransformable_put_transformMatrix_Proxy( 
    IPDObjectTransformable __RPC_FAR * This,
    /* [in] */ IPDMatrix __RPC_FAR *newVal);


void __RPC_STUB IPDObjectTransformable_put_transformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectTransformable_INTERFACE_DEFINED__ */


#ifndef __IPDObjectWrappable_INTERFACE_DEFINED__
#define __IPDObjectWrappable_INTERFACE_DEFINED__

/* interface IPDObjectWrappable */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectWrappable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CA848301-0F5F-11d6-95F0-0002E3045703")
    IPDObjectWrappable : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_textWrap( 
            /* [retval][out] */ PDTextWrap __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_textWrap( 
            /* [in] */ PDTextWrap newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_wrapPath( 
            /* [retval][out] */ IPDPath __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_wrapPath( 
            /* [in] */ IPDPath __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_editedWrapPath( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_editedWrapPath( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_topOffset( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_topOffset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_leftOffset( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_leftOffset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_bottomOffset( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_bottomOffset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_rightOffset( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_rightOffset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsRectangular( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectWrappableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectWrappable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectWrappable __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_textWrap )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ PDTextWrap __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_textWrap )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ PDTextWrap newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_wrapPath )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ IPDPath __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_wrapPath )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ IPDPath __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_editedWrapPath )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_editedWrapPath )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_topOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_topOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_leftOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_leftOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_bottomOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_bottomOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rightOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rightOffset )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsRectangular )( 
            IPDObjectWrappable __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDObjectWrappableVtbl;

    interface IPDObjectWrappable
    {
        CONST_VTBL struct IPDObjectWrappableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectWrappable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectWrappable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectWrappable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDObjectWrappable_get_textWrap(This,pVal)	\
    (This)->lpVtbl -> get_textWrap(This,pVal)

#define IPDObjectWrappable_put_textWrap(This,newVal)	\
    (This)->lpVtbl -> put_textWrap(This,newVal)

#define IPDObjectWrappable_get_wrapPath(This,pVal)	\
    (This)->lpVtbl -> get_wrapPath(This,pVal)

#define IPDObjectWrappable_put_wrapPath(This,newVal)	\
    (This)->lpVtbl -> put_wrapPath(This,newVal)

#define IPDObjectWrappable_get_editedWrapPath(This,pVal)	\
    (This)->lpVtbl -> get_editedWrapPath(This,pVal)

#define IPDObjectWrappable_put_editedWrapPath(This,newVal)	\
    (This)->lpVtbl -> put_editedWrapPath(This,newVal)

#define IPDObjectWrappable_get_topOffset(This,pVal)	\
    (This)->lpVtbl -> get_topOffset(This,pVal)

#define IPDObjectWrappable_put_topOffset(This,newVal)	\
    (This)->lpVtbl -> put_topOffset(This,newVal)

#define IPDObjectWrappable_get_leftOffset(This,pVal)	\
    (This)->lpVtbl -> get_leftOffset(This,pVal)

#define IPDObjectWrappable_put_leftOffset(This,newVal)	\
    (This)->lpVtbl -> put_leftOffset(This,newVal)

#define IPDObjectWrappable_get_bottomOffset(This,pVal)	\
    (This)->lpVtbl -> get_bottomOffset(This,pVal)

#define IPDObjectWrappable_put_bottomOffset(This,newVal)	\
    (This)->lpVtbl -> put_bottomOffset(This,newVal)

#define IPDObjectWrappable_get_rightOffset(This,pVal)	\
    (This)->lpVtbl -> get_rightOffset(This,pVal)

#define IPDObjectWrappable_put_rightOffset(This,newVal)	\
    (This)->lpVtbl -> put_rightOffset(This,newVal)

#define IPDObjectWrappable_IsRectangular(This,pVal)	\
    (This)->lpVtbl -> IsRectangular(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_get_textWrap_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ PDTextWrap __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_get_textWrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_put_textWrap_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [in] */ PDTextWrap newVal);


void __RPC_STUB IPDObjectWrappable_put_textWrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_get_wrapPath_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ IPDPath __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_get_wrapPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_put_wrapPath_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [in] */ IPDPath __RPC_FAR *newVal);


void __RPC_STUB IPDObjectWrappable_put_wrapPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_get_editedWrapPath_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_get_editedWrapPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_put_editedWrapPath_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IPDObjectWrappable_put_editedWrapPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_get_topOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_get_topOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_put_topOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDObjectWrappable_put_topOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_get_leftOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_get_leftOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_put_leftOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDObjectWrappable_put_leftOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_get_bottomOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_get_bottomOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_put_bottomOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDObjectWrappable_put_bottomOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_get_rightOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_get_rightOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_put_rightOffset_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDObjectWrappable_put_rightOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectWrappable_IsRectangular_Proxy( 
    IPDObjectWrappable __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWrappable_IsRectangular_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectWrappable_INTERFACE_DEFINED__ */


#ifndef __IPDObjectWithAppearance_INTERFACE_DEFINED__
#define __IPDObjectWithAppearance_INTERFACE_DEFINED__

/* interface IPDObjectWithAppearance */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectWithAppearance;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1F20717-5556-4974-99DC-398C2AC4B49E")
    IPDObjectWithAppearance : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_appearance( 
            /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_appearance( 
            /* [in] */ IPDAppearance __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_filterRect( 
            /* [retval][out] */ RectD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Render2( 
            /* [in] */ DWORD dwBitmap,
            /* [in] */ DWORD dwGraphics,
            /* [in] */ double scaleX,
            /* [in] */ double scaleY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectWithAppearanceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectWithAppearance __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectWithAppearance __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectWithAppearance __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_appearance )( 
            IPDObjectWithAppearance __RPC_FAR * This,
            /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_appearance )( 
            IPDObjectWithAppearance __RPC_FAR * This,
            /* [in] */ IPDAppearance __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_filterRect )( 
            IPDObjectWithAppearance __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Render2 )( 
            IPDObjectWithAppearance __RPC_FAR * This,
            /* [in] */ DWORD dwBitmap,
            /* [in] */ DWORD dwGraphics,
            /* [in] */ double scaleX,
            /* [in] */ double scaleY);
        
        END_INTERFACE
    } IPDObjectWithAppearanceVtbl;

    interface IPDObjectWithAppearance
    {
        CONST_VTBL struct IPDObjectWithAppearanceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectWithAppearance_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectWithAppearance_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectWithAppearance_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDObjectWithAppearance_get_appearance(This,pVal)	\
    (This)->lpVtbl -> get_appearance(This,pVal)

#define IPDObjectWithAppearance_put_appearance(This,newVal)	\
    (This)->lpVtbl -> put_appearance(This,newVal)

#define IPDObjectWithAppearance_get_filterRect(This,pVal)	\
    (This)->lpVtbl -> get_filterRect(This,pVal)

#define IPDObjectWithAppearance_Render2(This,dwBitmap,dwGraphics,scaleX,scaleY)	\
    (This)->lpVtbl -> Render2(This,dwBitmap,dwGraphics,scaleX,scaleY)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearance_get_appearance_Proxy( 
    IPDObjectWithAppearance __RPC_FAR * This,
    /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithAppearance_get_appearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearance_put_appearance_Proxy( 
    IPDObjectWithAppearance __RPC_FAR * This,
    /* [in] */ IPDAppearance __RPC_FAR *newVal);


void __RPC_STUB IPDObjectWithAppearance_put_appearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearance_get_filterRect_Proxy( 
    IPDObjectWithAppearance __RPC_FAR * This,
    /* [retval][out] */ RectD __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithAppearance_get_filterRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearance_Render2_Proxy( 
    IPDObjectWithAppearance __RPC_FAR * This,
    /* [in] */ DWORD dwBitmap,
    /* [in] */ DWORD dwGraphics,
    /* [in] */ double scaleX,
    /* [in] */ double scaleY);


void __RPC_STUB IPDObjectWithAppearance_Render2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectWithAppearance_INTERFACE_DEFINED__ */


#ifndef __IPDObjectWithAppearanceAndStrokeFill_INTERFACE_DEFINED__
#define __IPDObjectWithAppearanceAndStrokeFill_INTERFACE_DEFINED__

/* interface IPDObjectWithAppearanceAndStrokeFill */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectWithAppearanceAndStrokeFill;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FD56D926-34B6-426c-BB73-70F67CBC3AE2")
    IPDObjectWithAppearanceAndStrokeFill : public IPDObjectWithAppearance
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendSubObject( 
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeSubObject( 
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE copyAppearanceFrom( 
            /* [in] */ VARIANT_BOOL newArtHasBasicAppearance,
            /* [in] */ IPDObjectWithAppearanceAndStrokeFill __RPC_FAR *other) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_subObjects( 
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_activeStroke( 
            /* [retval][out] */ IPDObjectStroke __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_activeStroke( 
            /* [in] */ IPDObjectStroke __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_activeFill( 
            /* [retval][out] */ IPDObjectFill __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_activeFill( 
            /* [in] */ IPDObjectFill __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE removeSubObjects( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectWithAppearanceAndStrokeFillVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_appearance )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [retval][out] */ IPDAppearance __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_appearance )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ IPDAppearance __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_filterRect )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Render2 )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ DWORD dwBitmap,
            /* [in] */ DWORD dwGraphics,
            /* [in] */ double scaleX,
            /* [in] */ double scaleY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendSubObject )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeSubObject )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *copyAppearanceFrom )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newArtHasBasicAppearance,
            /* [in] */ IPDObjectWithAppearanceAndStrokeFill __RPC_FAR *other);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_subObjects )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_activeStroke )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [retval][out] */ IPDObjectStroke __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_activeStroke )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ IPDObjectStroke __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_activeFill )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [retval][out] */ IPDObjectFill __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_activeFill )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
            /* [in] */ IPDObjectFill __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeSubObjects )( 
            IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This);
        
        END_INTERFACE
    } IPDObjectWithAppearanceAndStrokeFillVtbl;

    interface IPDObjectWithAppearanceAndStrokeFill
    {
        CONST_VTBL struct IPDObjectWithAppearanceAndStrokeFillVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectWithAppearanceAndStrokeFill_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectWithAppearanceAndStrokeFill_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectWithAppearanceAndStrokeFill_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDObjectWithAppearanceAndStrokeFill_get_appearance(This,pVal)	\
    (This)->lpVtbl -> get_appearance(This,pVal)

#define IPDObjectWithAppearanceAndStrokeFill_put_appearance(This,newVal)	\
    (This)->lpVtbl -> put_appearance(This,newVal)

#define IPDObjectWithAppearanceAndStrokeFill_get_filterRect(This,pVal)	\
    (This)->lpVtbl -> get_filterRect(This,pVal)

#define IPDObjectWithAppearanceAndStrokeFill_Render2(This,dwBitmap,dwGraphics,scaleX,scaleY)	\
    (This)->lpVtbl -> Render2(This,dwBitmap,dwGraphics,scaleX,scaleY)


#define IPDObjectWithAppearanceAndStrokeFill_appendSubObject(This,object)	\
    (This)->lpVtbl -> appendSubObject(This,object)

#define IPDObjectWithAppearanceAndStrokeFill_removeSubObject(This,object)	\
    (This)->lpVtbl -> removeSubObject(This,object)

#define IPDObjectWithAppearanceAndStrokeFill_copyAppearanceFrom(This,newArtHasBasicAppearance,other)	\
    (This)->lpVtbl -> copyAppearanceFrom(This,newArtHasBasicAppearance,other)

#define IPDObjectWithAppearanceAndStrokeFill_get_subObjects(This,pVal)	\
    (This)->lpVtbl -> get_subObjects(This,pVal)

#define IPDObjectWithAppearanceAndStrokeFill_get_activeStroke(This,pVal)	\
    (This)->lpVtbl -> get_activeStroke(This,pVal)

#define IPDObjectWithAppearanceAndStrokeFill_put_activeStroke(This,newVal)	\
    (This)->lpVtbl -> put_activeStroke(This,newVal)

#define IPDObjectWithAppearanceAndStrokeFill_get_activeFill(This,pVal)	\
    (This)->lpVtbl -> get_activeFill(This,pVal)

#define IPDObjectWithAppearanceAndStrokeFill_put_activeFill(This,newVal)	\
    (This)->lpVtbl -> put_activeFill(This,newVal)

#define IPDObjectWithAppearanceAndStrokeFill_removeSubObjects(This)	\
    (This)->lpVtbl -> removeSubObjects(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_appendSubObject_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [in] */ IPDObjectWithBrush __RPC_FAR *object);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_appendSubObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_removeSubObject_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [in] */ IPDObjectWithBrush __RPC_FAR *object);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_removeSubObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_copyAppearanceFrom_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newArtHasBasicAppearance,
    /* [in] */ IPDObjectWithAppearanceAndStrokeFill __RPC_FAR *other);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_copyAppearanceFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_get_subObjects_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_get_subObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_get_activeStroke_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [retval][out] */ IPDObjectStroke __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_get_activeStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_put_activeStroke_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [in] */ IPDObjectStroke __RPC_FAR *newVal);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_put_activeStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_get_activeFill_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [retval][out] */ IPDObjectFill __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_get_activeFill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_put_activeFill_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This,
    /* [in] */ IPDObjectFill __RPC_FAR *newVal);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_put_activeFill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectWithAppearanceAndStrokeFill_removeSubObjects_Proxy( 
    IPDObjectWithAppearanceAndStrokeFill __RPC_FAR * This);


void __RPC_STUB IPDObjectWithAppearanceAndStrokeFill_removeSubObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectWithAppearanceAndStrokeFill_INTERFACE_DEFINED__ */


#ifndef __IPDObjectWithOpacityMask_INTERFACE_DEFINED__
#define __IPDObjectWithOpacityMask_INTERFACE_DEFINED__

/* interface IPDObjectWithOpacityMask */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectWithOpacityMask;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6694FC1-298E-11d6-95F0-0002E3045703")
    IPDObjectWithOpacityMask : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_opacityMaskGroup( 
            /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_opacityMaskGroup( 
            /* [in] */ IPDObjectGroup __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_opacityMaskClip( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_opacityMaskClip( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_opacityMaskInvert( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_opacityMaskInvert( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_opacityMaskEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_opacityMaskEnabled( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_opacityMaskLinked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_opacityMaskLinked( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectWithOpacityMaskVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectWithOpacityMask __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectWithOpacityMask __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_opacityMaskGroup )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_opacityMaskGroup )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [in] */ IPDObjectGroup __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_opacityMaskClip )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_opacityMaskClip )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_opacityMaskInvert )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_opacityMaskInvert )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_opacityMaskEnabled )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_opacityMaskEnabled )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_opacityMaskLinked )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_opacityMaskLinked )( 
            IPDObjectWithOpacityMask __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IPDObjectWithOpacityMaskVtbl;

    interface IPDObjectWithOpacityMask
    {
        CONST_VTBL struct IPDObjectWithOpacityMaskVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectWithOpacityMask_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectWithOpacityMask_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectWithOpacityMask_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDObjectWithOpacityMask_get_opacityMaskGroup(This,pVal)	\
    (This)->lpVtbl -> get_opacityMaskGroup(This,pVal)

#define IPDObjectWithOpacityMask_put_opacityMaskGroup(This,newVal)	\
    (This)->lpVtbl -> put_opacityMaskGroup(This,newVal)

#define IPDObjectWithOpacityMask_get_opacityMaskClip(This,pVal)	\
    (This)->lpVtbl -> get_opacityMaskClip(This,pVal)

#define IPDObjectWithOpacityMask_put_opacityMaskClip(This,newVal)	\
    (This)->lpVtbl -> put_opacityMaskClip(This,newVal)

#define IPDObjectWithOpacityMask_get_opacityMaskInvert(This,pVal)	\
    (This)->lpVtbl -> get_opacityMaskInvert(This,pVal)

#define IPDObjectWithOpacityMask_put_opacityMaskInvert(This,newVal)	\
    (This)->lpVtbl -> put_opacityMaskInvert(This,newVal)

#define IPDObjectWithOpacityMask_get_opacityMaskEnabled(This,pVal)	\
    (This)->lpVtbl -> get_opacityMaskEnabled(This,pVal)

#define IPDObjectWithOpacityMask_put_opacityMaskEnabled(This,newVal)	\
    (This)->lpVtbl -> put_opacityMaskEnabled(This,newVal)

#define IPDObjectWithOpacityMask_get_opacityMaskLinked(This,pVal)	\
    (This)->lpVtbl -> get_opacityMaskLinked(This,pVal)

#define IPDObjectWithOpacityMask_put_opacityMaskLinked(This,newVal)	\
    (This)->lpVtbl -> put_opacityMaskLinked(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_get_opacityMaskGroup_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [retval][out] */ IPDObjectGroup __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithOpacityMask_get_opacityMaskGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_put_opacityMaskGroup_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [in] */ IPDObjectGroup __RPC_FAR *newVal);


void __RPC_STUB IPDObjectWithOpacityMask_put_opacityMaskGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_get_opacityMaskClip_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithOpacityMask_get_opacityMaskClip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_put_opacityMaskClip_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDObjectWithOpacityMask_put_opacityMaskClip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_get_opacityMaskInvert_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithOpacityMask_get_opacityMaskInvert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_put_opacityMaskInvert_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDObjectWithOpacityMask_put_opacityMaskInvert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_get_opacityMaskEnabled_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithOpacityMask_get_opacityMaskEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_put_opacityMaskEnabled_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDObjectWithOpacityMask_put_opacityMaskEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_get_opacityMaskLinked_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectWithOpacityMask_get_opacityMaskLinked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectWithOpacityMask_put_opacityMaskLinked_Proxy( 
    IPDObjectWithOpacityMask __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDObjectWithOpacityMask_put_opacityMaskLinked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectWithOpacityMask_INTERFACE_DEFINED__ */


#ifndef __IPDOpacityAndBlendMode_INTERFACE_DEFINED__
#define __IPDOpacityAndBlendMode_INTERFACE_DEFINED__

/* interface IPDOpacityAndBlendMode */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDOpacityAndBlendMode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFF1FFE1-3DF0-447b-A763-D578EF9E10BD")
    IPDOpacityAndBlendMode : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_opacity( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_opacity( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_blendmode( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_blendmode( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDOpacityAndBlendModeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDOpacityAndBlendMode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDOpacityAndBlendMode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDOpacityAndBlendMode __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_opacity )( 
            IPDOpacityAndBlendMode __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_opacity )( 
            IPDOpacityAndBlendMode __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_blendmode )( 
            IPDOpacityAndBlendMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_blendmode )( 
            IPDOpacityAndBlendMode __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IPDOpacityAndBlendModeVtbl;

    interface IPDOpacityAndBlendMode
    {
        CONST_VTBL struct IPDOpacityAndBlendModeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDOpacityAndBlendMode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDOpacityAndBlendMode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDOpacityAndBlendMode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDOpacityAndBlendMode_get_opacity(This,pVal)	\
    (This)->lpVtbl -> get_opacity(This,pVal)

#define IPDOpacityAndBlendMode_put_opacity(This,newVal)	\
    (This)->lpVtbl -> put_opacity(This,newVal)

#define IPDOpacityAndBlendMode_get_blendmode(This,pVal)	\
    (This)->lpVtbl -> get_blendmode(This,pVal)

#define IPDOpacityAndBlendMode_put_blendmode(This,newVal)	\
    (This)->lpVtbl -> put_blendmode(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDOpacityAndBlendMode_get_opacity_Proxy( 
    IPDOpacityAndBlendMode __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDOpacityAndBlendMode_get_opacity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDOpacityAndBlendMode_put_opacity_Proxy( 
    IPDOpacityAndBlendMode __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDOpacityAndBlendMode_put_opacity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDOpacityAndBlendMode_get_blendmode_Proxy( 
    IPDOpacityAndBlendMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDOpacityAndBlendMode_get_blendmode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDOpacityAndBlendMode_put_blendmode_Proxy( 
    IPDOpacityAndBlendMode __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDOpacityAndBlendMode_put_blendmode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDOpacityAndBlendMode_INTERFACE_DEFINED__ */


#ifndef __IPDTextFrameOptions_INTERFACE_DEFINED__
#define __IPDTextFrameOptions_INTERFACE_DEFINED__

/* interface IPDTextFrameOptions */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDTextFrameOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9C048B01-10A5-11d6-95F0-0002E3045703")
    IPDTextFrameOptions : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ignoreTextWrap( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ignoreTextWrap( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_columnsNumber( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_columnsGutter( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_insetTop( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_insetTop( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_insetBottom( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_insetBottom( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_insetLeft( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_insetLeft( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_insetRight( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_insetRight( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE copyFrom( 
            /* [in] */ IPDTextFrameOptions __RPC_FAR *other) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_columnsWidth( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_columnsFixedWidth( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setColumns( 
            /* [in] */ long ncolumns,
            /* [in] */ double gutter,
            /* [in] */ double width,
            /* [in] */ VARIANT_BOOL fixedWidth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDTextFrameOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDTextFrameOptions __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDTextFrameOptions __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ignoreTextWrap )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ignoreTextWrap )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_columnsNumber )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_columnsGutter )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_insetTop )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_insetTop )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_insetBottom )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_insetBottom )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_insetLeft )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_insetLeft )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_insetRight )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_insetRight )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *copyFrom )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ IPDTextFrameOptions __RPC_FAR *other);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_columnsWidth )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_columnsFixedWidth )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setColumns )( 
            IPDTextFrameOptions __RPC_FAR * This,
            /* [in] */ long ncolumns,
            /* [in] */ double gutter,
            /* [in] */ double width,
            /* [in] */ VARIANT_BOOL fixedWidth);
        
        END_INTERFACE
    } IPDTextFrameOptionsVtbl;

    interface IPDTextFrameOptions
    {
        CONST_VTBL struct IPDTextFrameOptionsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDTextFrameOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDTextFrameOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDTextFrameOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDTextFrameOptions_get_ignoreTextWrap(This,pVal)	\
    (This)->lpVtbl -> get_ignoreTextWrap(This,pVal)

#define IPDTextFrameOptions_put_ignoreTextWrap(This,newVal)	\
    (This)->lpVtbl -> put_ignoreTextWrap(This,newVal)

#define IPDTextFrameOptions_get_columnsNumber(This,pVal)	\
    (This)->lpVtbl -> get_columnsNumber(This,pVal)

#define IPDTextFrameOptions_get_columnsGutter(This,pVal)	\
    (This)->lpVtbl -> get_columnsGutter(This,pVal)

#define IPDTextFrameOptions_get_insetTop(This,pVal)	\
    (This)->lpVtbl -> get_insetTop(This,pVal)

#define IPDTextFrameOptions_put_insetTop(This,newVal)	\
    (This)->lpVtbl -> put_insetTop(This,newVal)

#define IPDTextFrameOptions_get_insetBottom(This,pVal)	\
    (This)->lpVtbl -> get_insetBottom(This,pVal)

#define IPDTextFrameOptions_put_insetBottom(This,newVal)	\
    (This)->lpVtbl -> put_insetBottom(This,newVal)

#define IPDTextFrameOptions_get_insetLeft(This,pVal)	\
    (This)->lpVtbl -> get_insetLeft(This,pVal)

#define IPDTextFrameOptions_put_insetLeft(This,newVal)	\
    (This)->lpVtbl -> put_insetLeft(This,newVal)

#define IPDTextFrameOptions_get_insetRight(This,pVal)	\
    (This)->lpVtbl -> get_insetRight(This,pVal)

#define IPDTextFrameOptions_put_insetRight(This,newVal)	\
    (This)->lpVtbl -> put_insetRight(This,newVal)

#define IPDTextFrameOptions_copyFrom(This,other)	\
    (This)->lpVtbl -> copyFrom(This,other)

#define IPDTextFrameOptions_get_columnsWidth(This,pVal)	\
    (This)->lpVtbl -> get_columnsWidth(This,pVal)

#define IPDTextFrameOptions_get_columnsFixedWidth(This,pVal)	\
    (This)->lpVtbl -> get_columnsFixedWidth(This,pVal)

#define IPDTextFrameOptions_setColumns(This,ncolumns,gutter,width,fixedWidth)	\
    (This)->lpVtbl -> setColumns(This,ncolumns,gutter,width,fixedWidth)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_ignoreTextWrap_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_ignoreTextWrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_put_ignoreTextWrap_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IPDTextFrameOptions_put_ignoreTextWrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_columnsNumber_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_columnsNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_columnsGutter_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_columnsGutter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_insetTop_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_insetTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_put_insetTop_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDTextFrameOptions_put_insetTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_insetBottom_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_insetBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_put_insetBottom_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDTextFrameOptions_put_insetBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_insetLeft_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_insetLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_put_insetLeft_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDTextFrameOptions_put_insetLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_insetRight_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_insetRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_put_insetRight_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDTextFrameOptions_put_insetRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_copyFrom_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [in] */ IPDTextFrameOptions __RPC_FAR *other);


void __RPC_STUB IPDTextFrameOptions_copyFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_columnsWidth_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_columnsWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_get_columnsFixedWidth_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDTextFrameOptions_get_columnsFixedWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDTextFrameOptions_setColumns_Proxy( 
    IPDTextFrameOptions __RPC_FAR * This,
    /* [in] */ long ncolumns,
    /* [in] */ double gutter,
    /* [in] */ double width,
    /* [in] */ VARIANT_BOOL fixedWidth);


void __RPC_STUB IPDTextFrameOptions_setColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDTextFrameOptions_INTERFACE_DEFINED__ */


#ifndef __IObjectSerializable_INTERFACE_DEFINED__
#define __IObjectSerializable_INTERFACE_DEFINED__

/* interface IObjectSerializable */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IObjectSerializable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86B6103D-F8E6-4e51-8321-40C4373BB664")
    IObjectSerializable : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Serialize( 
            /* [in] */ IArchive __RPC_FAR *ar,
            /* [in] */ IArchiveElement __RPC_FAR *node) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Deserialize( 
            /* [in] */ IArchive __RPC_FAR *ar,
            /* [in] */ IArchiveElement __RPC_FAR *node,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClassID( 
            /* [retval][out] */ CLSID __RPC_FAR *pClassID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectSerializableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IObjectSerializable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IObjectSerializable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IObjectSerializable __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Serialize )( 
            IObjectSerializable __RPC_FAR * This,
            /* [in] */ IArchive __RPC_FAR *ar,
            /* [in] */ IArchiveElement __RPC_FAR *node);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Deserialize )( 
            IObjectSerializable __RPC_FAR * This,
            /* [in] */ IArchive __RPC_FAR *ar,
            /* [in] */ IArchiveElement __RPC_FAR *node,
            /* [in] */ IUnknown __RPC_FAR *pUnkExtra);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassID )( 
            IObjectSerializable __RPC_FAR * This,
            /* [retval][out] */ CLSID __RPC_FAR *pClassID);
        
        END_INTERFACE
    } IObjectSerializableVtbl;

    interface IObjectSerializable
    {
        CONST_VTBL struct IObjectSerializableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectSerializable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IObjectSerializable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IObjectSerializable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IObjectSerializable_Serialize(This,ar,node)	\
    (This)->lpVtbl -> Serialize(This,ar,node)

#define IObjectSerializable_Deserialize(This,ar,node,pUnkExtra)	\
    (This)->lpVtbl -> Deserialize(This,ar,node,pUnkExtra)

#define IObjectSerializable_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IObjectSerializable_Serialize_Proxy( 
    IObjectSerializable __RPC_FAR * This,
    /* [in] */ IArchive __RPC_FAR *ar,
    /* [in] */ IArchiveElement __RPC_FAR *node);


void __RPC_STUB IObjectSerializable_Serialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IObjectSerializable_Deserialize_Proxy( 
    IObjectSerializable __RPC_FAR * This,
    /* [in] */ IArchive __RPC_FAR *ar,
    /* [in] */ IArchiveElement __RPC_FAR *node,
    /* [in] */ IUnknown __RPC_FAR *pUnkExtra);


void __RPC_STUB IObjectSerializable_Deserialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IObjectSerializable_GetClassID_Proxy( 
    IObjectSerializable __RPC_FAR * This,
    /* [retval][out] */ CLSID __RPC_FAR *pClassID);


void __RPC_STUB IObjectSerializable_GetClassID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectSerializable_INTERFACE_DEFINED__ */


#ifndef __IPagesDlg_INTERFACE_DEFINED__
#define __IPagesDlg_INTERFACE_DEFINED__

/* interface IPagesDlg */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPagesDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1AEC8D8-07CC-40a7-95E1-D07941DE9905")
    IPagesDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPagesDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPagesDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPagesDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPagesDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPagesDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPagesDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPagesDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPagesDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IPagesDlgVtbl;

    interface IPagesDlg
    {
        CONST_VTBL struct IPagesDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPagesDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPagesDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPagesDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPagesDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPagesDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPagesDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPagesDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPagesDlg_INTERFACE_DEFINED__ */


#ifndef __ILayersDlg_INTERFACE_DEFINED__
#define __ILayersDlg_INTERFACE_DEFINED__

/* interface ILayersDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILayersDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0E83A5D2-ED2D-487F-B5DE-0C60234831B6")
    ILayersDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILayersDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILayersDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILayersDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILayersDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILayersDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILayersDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILayersDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILayersDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ILayersDlgVtbl;

    interface ILayersDlg
    {
        CONST_VTBL struct ILayersDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILayersDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILayersDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILayersDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILayersDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILayersDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILayersDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILayersDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILayersDlg_INTERFACE_DEFINED__ */


#ifndef __ITabsDlg_INTERFACE_DEFINED__
#define __ITabsDlg_INTERFACE_DEFINED__

/* interface ITabsDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITabsDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A0AD4526-0579-11D6-95F0-0002E3045703")
    ITabsDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITabsDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITabsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITabsDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITabsDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITabsDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITabsDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITabsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITabsDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ITabsDlgVtbl;

    interface ITabsDlg
    {
        CONST_VTBL struct ITabsDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITabsDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITabsDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITabsDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITabsDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITabsDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITabsDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITabsDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITabsDlg_INTERFACE_DEFINED__ */


#ifndef __ISwatchLibraryDlg_INTERFACE_DEFINED__
#define __ISwatchLibraryDlg_INTERFACE_DEFINED__

/* interface ISwatchLibraryDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISwatchLibraryDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0714F6CC-0B72-11D6-95F0-0002E3045703")
    ISwatchLibraryDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISwatchLibraryDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISwatchLibraryDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISwatchLibraryDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISwatchLibraryDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISwatchLibraryDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISwatchLibraryDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISwatchLibraryDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISwatchLibraryDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ISwatchLibraryDlgVtbl;

    interface ISwatchLibraryDlg
    {
        CONST_VTBL struct ISwatchLibraryDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISwatchLibraryDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISwatchLibraryDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISwatchLibraryDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISwatchLibraryDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISwatchLibraryDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISwatchLibraryDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISwatchLibraryDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISwatchLibraryDlg_INTERFACE_DEFINED__ */


#ifndef __ILinksDlg_INTERFACE_DEFINED__
#define __ILinksDlg_INTERFACE_DEFINED__

/* interface ILinksDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILinksDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ABE418A3-26EF-11D6-95F0-0002E3045703")
    ILinksDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILinksDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILinksDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILinksDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILinksDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILinksDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILinksDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILinksDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILinksDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ILinksDlgVtbl;

    interface ILinksDlg
    {
        CONST_VTBL struct ILinksDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILinksDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILinksDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILinksDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILinksDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILinksDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILinksDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILinksDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILinksDlg_INTERFACE_DEFINED__ */


#ifndef __ITransparencyDlg_INTERFACE_DEFINED__
#define __ITransparencyDlg_INTERFACE_DEFINED__

/* interface ITransparencyDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITransparencyDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1A82E863-2969-11D6-95F0-0002E3045703")
    ITransparencyDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITransparencyDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransparencyDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransparencyDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransparencyDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITransparencyDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITransparencyDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITransparencyDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITransparencyDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ITransparencyDlgVtbl;

    interface ITransparencyDlg
    {
        CONST_VTBL struct ITransparencyDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransparencyDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransparencyDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransparencyDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransparencyDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITransparencyDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITransparencyDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITransparencyDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITransparencyDlg_INTERFACE_DEFINED__ */


#ifndef __IFilterGraphDlg_INTERFACE_DEFINED__
#define __IFilterGraphDlg_INTERFACE_DEFINED__

/* interface IFilterGraphDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFilterGraphDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1A82E866-2969-11D6-95F0-0002E3045703")
    IFilterGraphDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFilterGraphDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFilterGraphDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFilterGraphDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFilterGraphDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFilterGraphDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFilterGraphDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFilterGraphDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFilterGraphDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IFilterGraphDlgVtbl;

    interface IFilterGraphDlg
    {
        CONST_VTBL struct IFilterGraphDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterGraphDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterGraphDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterGraphDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterGraphDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFilterGraphDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFilterGraphDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFilterGraphDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFilterGraphDlg_INTERFACE_DEFINED__ */


#ifndef __IFEGaussianBlur_INTERFACE_DEFINED__
#define __IFEGaussianBlur_INTERFACE_DEFINED__

/* interface IFEGaussianBlur */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFEGaussianBlur;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A44E5493-0024-438E-8A46-988C3B6452C6")
    IFEGaussianBlur : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stdDeviationX( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stdDeviationY( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setStdDeviation( 
            /* [in] */ double stdDeviationX,
            /* [in] */ double stdDeviationY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFEGaussianBlurVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFEGaussianBlur __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFEGaussianBlur __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stdDeviationX )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stdDeviationY )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setStdDeviation )( 
            IFEGaussianBlur __RPC_FAR * This,
            /* [in] */ double stdDeviationX,
            /* [in] */ double stdDeviationY);
        
        END_INTERFACE
    } IFEGaussianBlurVtbl;

    interface IFEGaussianBlur
    {
        CONST_VTBL struct IFEGaussianBlurVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFEGaussianBlur_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFEGaussianBlur_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFEGaussianBlur_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFEGaussianBlur_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFEGaussianBlur_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFEGaussianBlur_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFEGaussianBlur_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFEGaussianBlur_get_stdDeviationX(This,pVal)	\
    (This)->lpVtbl -> get_stdDeviationX(This,pVal)

#define IFEGaussianBlur_get_stdDeviationY(This,pVal)	\
    (This)->lpVtbl -> get_stdDeviationY(This,pVal)

#define IFEGaussianBlur_setStdDeviation(This,stdDeviationX,stdDeviationY)	\
    (This)->lpVtbl -> setStdDeviation(This,stdDeviationX,stdDeviationY)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFEGaussianBlur_get_stdDeviationX_Proxy( 
    IFEGaussianBlur __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IFEGaussianBlur_get_stdDeviationX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFEGaussianBlur_get_stdDeviationY_Proxy( 
    IFEGaussianBlur __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IFEGaussianBlur_get_stdDeviationY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFEGaussianBlur_setStdDeviation_Proxy( 
    IFEGaussianBlur __RPC_FAR * This,
    /* [in] */ double stdDeviationX,
    /* [in] */ double stdDeviationY);


void __RPC_STUB IFEGaussianBlur_setStdDeviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFEGaussianBlur_INTERFACE_DEFINED__ */


#ifndef __IFEOffset_INTERFACE_DEFINED__
#define __IFEOffset_INTERFACE_DEFINED__

/* interface IFEOffset */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFEOffset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1BAA0B07-31F0-47A8-AB6F-D7DC8F3158D0")
    IFEOffset : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dx( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dy( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFEOffsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFEOffset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFEOffset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFEOffset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFEOffset __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFEOffset __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFEOffset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFEOffset __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dx )( 
            IFEOffset __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dy )( 
            IFEOffset __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        END_INTERFACE
    } IFEOffsetVtbl;

    interface IFEOffset
    {
        CONST_VTBL struct IFEOffsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFEOffset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFEOffset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFEOffset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFEOffset_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFEOffset_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFEOffset_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFEOffset_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFEOffset_get_dx(This,pVal)	\
    (This)->lpVtbl -> get_dx(This,pVal)

#define IFEOffset_get_dy(This,pVal)	\
    (This)->lpVtbl -> get_dy(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFEOffset_get_dx_Proxy( 
    IFEOffset __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IFEOffset_get_dx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFEOffset_get_dy_Proxy( 
    IFEOffset __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IFEOffset_get_dy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFEOffset_INTERFACE_DEFINED__ */


#ifndef __IFEComposite_INTERFACE_DEFINED__
#define __IFEComposite_INTERFACE_DEFINED__

/* interface IFEComposite */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFEComposite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("22EAB538-05B8-465F-927A-A30F868B0DD7")
    IFEComposite : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_op( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_op( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFECompositeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFEComposite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFEComposite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFEComposite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFEComposite __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFEComposite __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFEComposite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFEComposite __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_op )( 
            IFEComposite __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_op )( 
            IFEComposite __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IFECompositeVtbl;

    interface IFEComposite
    {
        CONST_VTBL struct IFECompositeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFEComposite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFEComposite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFEComposite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFEComposite_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFEComposite_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFEComposite_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFEComposite_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFEComposite_get_op(This,pVal)	\
    (This)->lpVtbl -> get_op(This,pVal)

#define IFEComposite_put_op(This,newVal)	\
    (This)->lpVtbl -> put_op(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFEComposite_get_op_Proxy( 
    IFEComposite __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFEComposite_get_op_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFEComposite_put_op_Proxy( 
    IFEComposite __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IFEComposite_put_op_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFEComposite_INTERFACE_DEFINED__ */


#ifndef __IPluginFiltersDlg_INTERFACE_DEFINED__
#define __IPluginFiltersDlg_INTERFACE_DEFINED__

/* interface IPluginFiltersDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPluginFiltersDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7B420E09-1717-4C01-B149-7B1335179C6E")
    IPluginFiltersDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPluginFiltersDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPluginFiltersDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPluginFiltersDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPluginFiltersDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPluginFiltersDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPluginFiltersDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPluginFiltersDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPluginFiltersDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IPluginFiltersDlgVtbl;

    interface IPluginFiltersDlg
    {
        CONST_VTBL struct IPluginFiltersDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPluginFiltersDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPluginFiltersDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPluginFiltersDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPluginFiltersDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPluginFiltersDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPluginFiltersDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPluginFiltersDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPluginFiltersDlg_INTERFACE_DEFINED__ */


#ifndef __IStylesDlg_INTERFACE_DEFINED__
#define __IStylesDlg_INTERFACE_DEFINED__

/* interface IStylesDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStylesDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43D8CA6D-80F1-4F24-BF79-3DCA18B7DDFE")
    IStylesDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IStylesDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStylesDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStylesDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStylesDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStylesDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStylesDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStylesDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStylesDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IStylesDlgVtbl;

    interface IStylesDlg
    {
        CONST_VTBL struct IStylesDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStylesDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStylesDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStylesDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStylesDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStylesDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStylesDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStylesDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStylesDlg_INTERFACE_DEFINED__ */


#ifndef __IFEFreeTransform_INTERFACE_DEFINED__
#define __IFEFreeTransform_INTERFACE_DEFINED__

/* interface IFEFreeTransform */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFEFreeTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E009C2D-8F80-4F82-A9F7-F3E6AA46BA16")
    IFEFreeTransform : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFEFreeTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFEFreeTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFEFreeTransform __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFEFreeTransform __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFEFreeTransform __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFEFreeTransform __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFEFreeTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFEFreeTransform __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IFEFreeTransformVtbl;

    interface IFEFreeTransform
    {
        CONST_VTBL struct IFEFreeTransformVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFEFreeTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFEFreeTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFEFreeTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFEFreeTransform_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFEFreeTransform_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFEFreeTransform_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFEFreeTransform_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFEFreeTransform_INTERFACE_DEFINED__ */


#ifndef __IAppearanceDlg_INTERFACE_DEFINED__
#define __IAppearanceDlg_INTERFACE_DEFINED__

/* interface IAppearanceDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAppearanceDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1850CF81-92F4-4E0E-AF23-F27864CF0BB7")
    IAppearanceDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAppearanceDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAppearanceDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAppearanceDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAppearanceDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAppearanceDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAppearanceDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAppearanceDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAppearanceDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IAppearanceDlgVtbl;

    interface IAppearanceDlg
    {
        CONST_VTBL struct IAppearanceDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAppearanceDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAppearanceDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAppearanceDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAppearanceDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAppearanceDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAppearanceDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAppearanceDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAppearanceDlg_INTERFACE_DEFINED__ */


#ifndef __ISymbolsDlg_INTERFACE_DEFINED__
#define __ISymbolsDlg_INTERFACE_DEFINED__

/* interface ISymbolsDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISymbolsDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6D6E2F46-79C0-4961-8184-5C66817048F8")
    ISymbolsDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISymbolsDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISymbolsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISymbolsDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISymbolsDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISymbolsDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISymbolsDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISymbolsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISymbolsDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ISymbolsDlgVtbl;

    interface ISymbolsDlg
    {
        CONST_VTBL struct ISymbolsDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISymbolsDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISymbolsDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISymbolsDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISymbolsDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISymbolsDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISymbolsDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISymbolsDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISymbolsDlg_INTERFACE_DEFINED__ */


#ifndef __IPDObjectSymbolInstance_INTERFACE_DEFINED__
#define __IPDObjectSymbolInstance_INTERFACE_DEFINED__

/* interface IPDObjectSymbolInstance */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectSymbolInstance;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E8AA9A08-BD30-441C-86C2-2699C53DAF1E")
    IPDObjectSymbolInstance : public IPDObject
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_symbol( 
            /* [retval][out] */ IPDSymbol __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_symbol( 
            /* [in] */ IPDSymbol __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_x( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_y( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setxy( 
            /* [in] */ double x,
            /* [in] */ double y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectSymbolInstanceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectSymbolInstance __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectSymbolInstance __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_symbol )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ IPDSymbol __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_symbol )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ IPDSymbol __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setxy )( 
            IPDObjectSymbolInstance __RPC_FAR * This,
            /* [in] */ double x,
            /* [in] */ double y);
        
        END_INTERFACE
    } IPDObjectSymbolInstanceVtbl;

    interface IPDObjectSymbolInstance
    {
        CONST_VTBL struct IPDObjectSymbolInstanceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectSymbolInstance_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectSymbolInstance_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectSymbolInstance_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectSymbolInstance_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectSymbolInstance_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectSymbolInstance_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectSymbolInstance_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectSymbolInstance_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectSymbolInstance_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectSymbolInstance_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectSymbolInstance_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectSymbolInstance_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectSymbolInstance_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectSymbolInstance_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectSymbolInstance_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectSymbolInstance_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectSymbolInstance_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectSymbolInstance_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectSymbolInstance_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectSymbolInstance_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectSymbolInstance_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectSymbolInstance_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectSymbolInstance_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#define IPDObjectSymbolInstance_get_symbol(This,pVal)	\
    (This)->lpVtbl -> get_symbol(This,pVal)

#define IPDObjectSymbolInstance_put_symbol(This,newVal)	\
    (This)->lpVtbl -> put_symbol(This,newVal)

#define IPDObjectSymbolInstance_get_x(This,pVal)	\
    (This)->lpVtbl -> get_x(This,pVal)

#define IPDObjectSymbolInstance_get_y(This,pVal)	\
    (This)->lpVtbl -> get_y(This,pVal)

#define IPDObjectSymbolInstance_setxy(This,x,y)	\
    (This)->lpVtbl -> setxy(This,x,y)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectSymbolInstance_get_symbol_Proxy( 
    IPDObjectSymbolInstance __RPC_FAR * This,
    /* [retval][out] */ IPDSymbol __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectSymbolInstance_get_symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDObjectSymbolInstance_put_symbol_Proxy( 
    IPDObjectSymbolInstance __RPC_FAR * This,
    /* [in] */ IPDSymbol __RPC_FAR *newVal);


void __RPC_STUB IPDObjectSymbolInstance_put_symbol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectSymbolInstance_get_x_Proxy( 
    IPDObjectSymbolInstance __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDObjectSymbolInstance_get_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectSymbolInstance_get_y_Proxy( 
    IPDObjectSymbolInstance __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDObjectSymbolInstance_get_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectSymbolInstance_setxy_Proxy( 
    IPDObjectSymbolInstance __RPC_FAR * This,
    /* [in] */ double x,
    /* [in] */ double y);


void __RPC_STUB IPDObjectSymbolInstance_setxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectSymbolInstance_INTERFACE_DEFINED__ */


#ifndef __IPDObjectSymbolInstanceSet_INTERFACE_DEFINED__
#define __IPDObjectSymbolInstanceSet_INTERFACE_DEFINED__

/* interface IPDObjectSymbolInstanceSet */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectSymbolInstanceSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F96B7EA7-1CC3-4B19-8C51-FA15095B1379")
    IPDObjectSymbolInstanceSet : public IPDObject
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectSymbolInstanceSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqId )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ PDObjectType __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_layer )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDLayer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parent )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeObject )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [in] */ IPDObjectUnknown __RPC_FAR *object);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spread )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDSpread __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spread )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [in] */ IPDSpread __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_document )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_document )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [in] */ IPDDocument __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDObjectUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IObjectMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getScreenCTM )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDMatrix __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clone )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ IPDObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getExpandedBBox )( 
            IPDObjectSymbolInstanceSet __RPC_FAR * This,
            /* [retval][out] */ RectD __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDObjectSymbolInstanceSetVtbl;

    interface IPDObjectSymbolInstanceSet
    {
        CONST_VTBL struct IPDObjectSymbolInstanceSetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectSymbolInstanceSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectSymbolInstanceSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectSymbolInstanceSet_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectSymbolInstanceSet_get_uniqId(This,pVal)	\
    (This)->lpVtbl -> get_uniqId(This,pVal)

#define IPDObjectSymbolInstanceSet_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectSymbolInstanceSet_get_layer(This,pVal)	\
    (This)->lpVtbl -> get_layer(This,pVal)

#define IPDObjectSymbolInstanceSet_get_parent(This,pVal)	\
    (This)->lpVtbl -> get_parent(This,pVal)

#define IPDObjectSymbolInstanceSet_put_parent(This,newVal)	\
    (This)->lpVtbl -> put_parent(This,newVal)

#define IPDObjectSymbolInstanceSet_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define IPDObjectSymbolInstanceSet_put_nextSibling(This,newVal)	\
    (This)->lpVtbl -> put_nextSibling(This,newVal)

#define IPDObjectSymbolInstanceSet_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define IPDObjectSymbolInstanceSet_put_previousSibling(This,newVal)	\
    (This)->lpVtbl -> put_previousSibling(This,newVal)

#define IPDObjectSymbolInstanceSet_removeObject(This,object)	\
    (This)->lpVtbl -> removeObject(This,object)

#define IPDObjectSymbolInstanceSet_get_spread(This,pVal)	\
    (This)->lpVtbl -> get_spread(This,pVal)

#define IPDObjectSymbolInstanceSet_put_spread(This,newVal)	\
    (This)->lpVtbl -> put_spread(This,newVal)

#define IPDObjectSymbolInstanceSet_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#define IPDObjectSymbolInstanceSet_put_document(This,newVal)	\
    (This)->lpVtbl -> put_document(This,newVal)


#define IPDObjectSymbolInstanceSet_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define IPDObjectSymbolInstanceSet_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define IPDObjectSymbolInstanceSet_get_children(This,pVal)	\
    (This)->lpVtbl -> get_children(This,pVal)

#define IPDObjectSymbolInstanceSet_getScreenCTM(This,pVal)	\
    (This)->lpVtbl -> getScreenCTM(This,pVal)

#define IPDObjectSymbolInstanceSet_clone(This,pVal)	\
    (This)->lpVtbl -> clone(This,pVal)

#define IPDObjectSymbolInstanceSet_getExpandedBBox(This,pVal)	\
    (This)->lpVtbl -> getExpandedBBox(This,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPDObjectSymbolInstanceSet_INTERFACE_DEFINED__ */


#ifndef __IPDStrokeSettings_INTERFACE_DEFINED__
#define __IPDStrokeSettings_INTERFACE_DEFINED__

/* interface IPDStrokeSettings */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDStrokeSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45587BA3-0C07-4bca-8A9B-C23183211CA3")
    IPDStrokeSettings : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_strokeWeight( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_strokeWeight( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_dashedCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_strokeCap( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_strokeCap( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_strokeJoin( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_strokeJoin( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_strokeMiterLimit( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_strokeMiterLimit( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE setDashedValue( 
            /* [in] */ long index,
            /* [in] */ double value) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE getDashedValue( 
            /* [in] */ long index,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDStrokeSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDStrokeSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDStrokeSettings __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strokeWeight )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strokeWeight )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dashedCount )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strokeCap )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strokeCap )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strokeJoin )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strokeJoin )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strokeMiterLimit )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strokeMiterLimit )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setDashedValue )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ double value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDashedValue )( 
            IPDStrokeSettings __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDStrokeSettingsVtbl;

    interface IPDStrokeSettings
    {
        CONST_VTBL struct IPDStrokeSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDStrokeSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDStrokeSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDStrokeSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDStrokeSettings_get_strokeWeight(This,pVal)	\
    (This)->lpVtbl -> get_strokeWeight(This,pVal)

#define IPDStrokeSettings_put_strokeWeight(This,newVal)	\
    (This)->lpVtbl -> put_strokeWeight(This,newVal)

#define IPDStrokeSettings_get_dashedCount(This,pVal)	\
    (This)->lpVtbl -> get_dashedCount(This,pVal)

#define IPDStrokeSettings_get_strokeCap(This,pVal)	\
    (This)->lpVtbl -> get_strokeCap(This,pVal)

#define IPDStrokeSettings_put_strokeCap(This,newVal)	\
    (This)->lpVtbl -> put_strokeCap(This,newVal)

#define IPDStrokeSettings_get_strokeJoin(This,pVal)	\
    (This)->lpVtbl -> get_strokeJoin(This,pVal)

#define IPDStrokeSettings_put_strokeJoin(This,newVal)	\
    (This)->lpVtbl -> put_strokeJoin(This,newVal)

#define IPDStrokeSettings_get_strokeMiterLimit(This,pVal)	\
    (This)->lpVtbl -> get_strokeMiterLimit(This,pVal)

#define IPDStrokeSettings_put_strokeMiterLimit(This,newVal)	\
    (This)->lpVtbl -> put_strokeMiterLimit(This,newVal)

#define IPDStrokeSettings_setDashedValue(This,index,value)	\
    (This)->lpVtbl -> setDashedValue(This,index,value)

#define IPDStrokeSettings_getDashedValue(This,index,pVal)	\
    (This)->lpVtbl -> getDashedValue(This,index,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_get_strokeWeight_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDStrokeSettings_get_strokeWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_put_strokeWeight_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDStrokeSettings_put_strokeWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_get_dashedCount_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDStrokeSettings_get_dashedCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_get_strokeCap_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDStrokeSettings_get_strokeCap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_put_strokeCap_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDStrokeSettings_put_strokeCap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_get_strokeJoin_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDStrokeSettings_get_strokeJoin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_put_strokeJoin_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPDStrokeSettings_put_strokeJoin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_get_strokeMiterLimit_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDStrokeSettings_get_strokeMiterLimit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_put_strokeMiterLimit_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPDStrokeSettings_put_strokeMiterLimit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_setDashedValue_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ double value);


void __RPC_STUB IPDStrokeSettings_setDashedValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDStrokeSettings_getDashedValue_Proxy( 
    IPDStrokeSettings __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPDStrokeSettings_getDashedValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDStrokeSettings_INTERFACE_DEFINED__ */


#ifndef __IPDObjectSelection_INTERFACE_DEFINED__
#define __IPDObjectSelection_INTERFACE_DEFINED__

/* interface IPDObjectSelection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPDObjectSelection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("862CE21E-00F6-4c40-9474-E4315C0BC83E")
    IPDObjectSelection : public IPDUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_objectType( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetView( 
            /* [retval][out] */ IPDDocumentView __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE appendSubObject( 
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE hasMixedAppearance( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDObjectSelectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDObjectSelection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDObjectSelection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDObjectSelection __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_objectType )( 
            IPDObjectSelection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetView )( 
            IPDObjectSelection __RPC_FAR * This,
            /* [retval][out] */ IPDDocumentView __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendSubObject )( 
            IPDObjectSelection __RPC_FAR * This,
            /* [in] */ IPDObjectWithBrush __RPC_FAR *object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *hasMixedAppearance )( 
            IPDObjectSelection __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPDObjectSelectionVtbl;

    interface IPDObjectSelection
    {
        CONST_VTBL struct IPDObjectSelectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDObjectSelection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDObjectSelection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDObjectSelection_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IPDObjectSelection_get_objectType(This,pVal)	\
    (This)->lpVtbl -> get_objectType(This,pVal)

#define IPDObjectSelection_GetView(This,pVal)	\
    (This)->lpVtbl -> GetView(This,pVal)

#define IPDObjectSelection_appendSubObject(This,object)	\
    (This)->lpVtbl -> appendSubObject(This,object)

#define IPDObjectSelection_hasMixedAppearance(This,pVal)	\
    (This)->lpVtbl -> hasMixedAppearance(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPDObjectSelection_get_objectType_Proxy( 
    IPDObjectSelection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPDObjectSelection_get_objectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectSelection_GetView_Proxy( 
    IPDObjectSelection __RPC_FAR * This,
    /* [retval][out] */ IPDDocumentView __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IPDObjectSelection_GetView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectSelection_appendSubObject_Proxy( 
    IPDObjectSelection __RPC_FAR * This,
    /* [in] */ IPDObjectWithBrush __RPC_FAR *object);


void __RPC_STUB IPDObjectSelection_appendSubObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDObjectSelection_hasMixedAppearance_Proxy( 
    IPDObjectSelection __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IPDObjectSelection_hasMixedAppearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDObjectSelection_INTERFACE_DEFINED__ */


#ifndef __IPDCustomRenderer_INTERFACE_DEFINED__
#define __IPDCustomRenderer_INTERFACE_DEFINED__

/* interface IPDCustomRenderer */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPDCustomRenderer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9C048B02-10A5-11d6-95F0-0002E3045703")
    IPDCustomRenderer : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RenderObject( 
            /* [in] */ IPDRenderer __RPC_FAR *renderer,
            /* [in] */ IPDObject __RPC_FAR *object) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDCustomRendererVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDCustomRenderer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDCustomRenderer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDCustomRenderer __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderObject )( 
            IPDCustomRenderer __RPC_FAR * This,
            /* [in] */ IPDRenderer __RPC_FAR *renderer,
            /* [in] */ IPDObject __RPC_FAR *object);
        
        END_INTERFACE
    } IPDCustomRendererVtbl;

    interface IPDCustomRenderer
    {
        CONST_VTBL struct IPDCustomRendererVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDCustomRenderer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDCustomRenderer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDCustomRenderer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDCustomRenderer_RenderObject(This,renderer,object)	\
    (This)->lpVtbl -> RenderObject(This,renderer,object)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPDCustomRenderer_RenderObject_Proxy( 
    IPDCustomRenderer __RPC_FAR * This,
    /* [in] */ IPDRenderer __RPC_FAR *renderer,
    /* [in] */ IPDObject __RPC_FAR *object);


void __RPC_STUB IPDCustomRenderer_RenderObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDCustomRenderer_INTERFACE_DEFINED__ */


#ifndef __ISwatchesDlg_INTERFACE_DEFINED__
#define __ISwatchesDlg_INTERFACE_DEFINED__

/* interface ISwatchesDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISwatchesDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9DEC5940-E952-11D5-95F0-0002E3045703")
    ISwatchesDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISwatchesDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISwatchesDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISwatchesDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISwatchesDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISwatchesDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISwatchesDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISwatchesDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISwatchesDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ISwatchesDlgVtbl;

    interface ISwatchesDlg
    {
        CONST_VTBL struct ISwatchesDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISwatchesDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISwatchesDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISwatchesDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISwatchesDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISwatchesDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISwatchesDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISwatchesDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISwatchesDlg_INTERFACE_DEFINED__ */


#ifndef __IGradientDlg_INTERFACE_DEFINED__
#define __IGradientDlg_INTERFACE_DEFINED__

/* interface IGradientDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGradientDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A8AD0B32-565D-4DF7-AE32-3EC1D68730CB")
    IGradientDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IGradientDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGradientDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGradientDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGradientDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IGradientDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IGradientDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IGradientDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IGradientDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IGradientDlgVtbl;

    interface IGradientDlg
    {
        CONST_VTBL struct IGradientDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGradientDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGradientDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGradientDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGradientDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGradientDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGradientDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGradientDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGradientDlg_INTERFACE_DEFINED__ */


#ifndef __INavigatorDlg_INTERFACE_DEFINED__
#define __INavigatorDlg_INTERFACE_DEFINED__

/* interface INavigatorDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INavigatorDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9DEC5943-E952-11D5-95F0-0002E3045703")
    INavigatorDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct INavigatorDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INavigatorDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INavigatorDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INavigatorDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INavigatorDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INavigatorDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INavigatorDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INavigatorDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } INavigatorDlgVtbl;

    interface INavigatorDlg
    {
        CONST_VTBL struct INavigatorDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INavigatorDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INavigatorDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INavigatorDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INavigatorDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INavigatorDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INavigatorDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INavigatorDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INavigatorDlg_INTERFACE_DEFINED__ */


#ifndef __IStrokeDlg_INTERFACE_DEFINED__
#define __IStrokeDlg_INTERFACE_DEFINED__

/* interface IStrokeDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStrokeDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC00CE81-ED4C-11D5-95F0-0002E3045703")
    IStrokeDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IStrokeDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStrokeDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStrokeDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStrokeDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStrokeDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStrokeDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStrokeDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStrokeDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IStrokeDlgVtbl;

    interface IStrokeDlg
    {
        CONST_VTBL struct IStrokeDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrokeDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStrokeDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStrokeDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStrokeDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStrokeDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStrokeDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStrokeDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrokeDlg_INTERFACE_DEFINED__ */


#ifndef __ISwatchesList_INTERFACE_DEFINED__
#define __ISwatchesList_INTERFACE_DEFINED__

/* interface ISwatchesList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISwatchesList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B2AE123-EE82-11D5-95F0-0002E3045703")
    ISwatchesList : public IDispatch
    {
    public:
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp __RPC_FAR *pFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp __RPC_FAR *pFont) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long __RPC_FAR *phwnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_swatches( 
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_swatches( 
            /* [in] */ IPDSwatches __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE selectSwatch( 
            /* [in] */ IPDSwatch __RPC_FAR *swatch) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNextSelectedSwatch( 
            /* [in] */ long index,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_multiSelect( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_multiSelect( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_showSwatchNone( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_showSwatchNone( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_showSwatchColor( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_showSwatchColor( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_showSwatchGradient( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_showSwatchGradient( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISwatchesListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISwatchesList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISwatchesList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISwatchesList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Font )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ IFontDisp __RPC_FAR *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Font )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ IFontDisp __RPC_FAR *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Font )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Window )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *phwnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_swatches )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_swatches )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ IPDSwatches __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *selectSwatch )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ IPDSwatch __RPC_FAR *swatch);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getNextSelectedSwatch )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_multiSelect )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_multiSelect )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_showSwatchNone )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_showSwatchNone )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_showSwatchColor )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_showSwatchColor )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_showSwatchGradient )( 
            ISwatchesList __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_showSwatchGradient )( 
            ISwatchesList __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ISwatchesListVtbl;

    interface ISwatchesList
    {
        CONST_VTBL struct ISwatchesListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISwatchesList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISwatchesList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISwatchesList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISwatchesList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISwatchesList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISwatchesList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISwatchesList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISwatchesList_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define ISwatchesList_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define ISwatchesList_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define ISwatchesList_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define ISwatchesList_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define ISwatchesList_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define ISwatchesList_get_swatches(This,pVal)	\
    (This)->lpVtbl -> get_swatches(This,pVal)

#define ISwatchesList_put_swatches(This,newVal)	\
    (This)->lpVtbl -> put_swatches(This,newVal)

#define ISwatchesList_selectSwatch(This,swatch)	\
    (This)->lpVtbl -> selectSwatch(This,swatch)

#define ISwatchesList_getNextSelectedSwatch(This,index,pVal)	\
    (This)->lpVtbl -> getNextSelectedSwatch(This,index,pVal)

#define ISwatchesList_get_multiSelect(This,pVal)	\
    (This)->lpVtbl -> get_multiSelect(This,pVal)

#define ISwatchesList_put_multiSelect(This,newVal)	\
    (This)->lpVtbl -> put_multiSelect(This,newVal)

#define ISwatchesList_get_showSwatchNone(This,pVal)	\
    (This)->lpVtbl -> get_showSwatchNone(This,pVal)

#define ISwatchesList_put_showSwatchNone(This,newVal)	\
    (This)->lpVtbl -> put_showSwatchNone(This,newVal)

#define ISwatchesList_get_showSwatchColor(This,pVal)	\
    (This)->lpVtbl -> get_showSwatchColor(This,pVal)

#define ISwatchesList_put_showSwatchColor(This,newVal)	\
    (This)->lpVtbl -> put_showSwatchColor(This,newVal)

#define ISwatchesList_get_showSwatchGradient(This,pVal)	\
    (This)->lpVtbl -> get_showSwatchGradient(This,pVal)

#define ISwatchesList_put_showSwatchGradient(This,newVal)	\
    (This)->lpVtbl -> put_showSwatchGradient(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propputref] */ HRESULT STDMETHODCALLTYPE ISwatchesList_putref_Font_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ IFontDisp __RPC_FAR *pFont);


void __RPC_STUB ISwatchesList_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ISwatchesList_put_Font_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ IFontDisp __RPC_FAR *pFont);


void __RPC_STUB ISwatchesList_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_Font_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont);


void __RPC_STUB ISwatchesList_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ISwatchesList_put_Enabled_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB ISwatchesList_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_Enabled_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);


void __RPC_STUB ISwatchesList_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_Window_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *phwnd);


void __RPC_STUB ISwatchesList_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_swatches_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ IPDSwatches __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISwatchesList_get_swatches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISwatchesList_put_swatches_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ IPDSwatches __RPC_FAR *newVal);


void __RPC_STUB ISwatchesList_put_swatches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISwatchesList_selectSwatch_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ IPDSwatch __RPC_FAR *swatch);


void __RPC_STUB ISwatchesList_selectSwatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISwatchesList_getNextSelectedSwatch_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ IPDSwatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISwatchesList_getNextSelectedSwatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_multiSelect_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ISwatchesList_get_multiSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISwatchesList_put_multiSelect_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ISwatchesList_put_multiSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_showSwatchNone_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ISwatchesList_get_showSwatchNone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISwatchesList_put_showSwatchNone_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ISwatchesList_put_showSwatchNone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_showSwatchColor_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ISwatchesList_get_showSwatchColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISwatchesList_put_showSwatchColor_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ISwatchesList_put_showSwatchColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISwatchesList_get_showSwatchGradient_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ISwatchesList_get_showSwatchGradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISwatchesList_put_showSwatchGradient_Proxy( 
    ISwatchesList __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ISwatchesList_put_showSwatchGradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISwatchesList_INTERFACE_DEFINED__ */


#ifndef __IColorDlg_INTERFACE_DEFINED__
#define __IColorDlg_INTERFACE_DEFINED__

/* interface IColorDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IColorDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B2AE126-EE82-11D5-95F0-0002E3045703")
    IColorDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IColorDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IColorDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IColorDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IColorDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IColorDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IColorDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IColorDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IColorDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IColorDlgVtbl;

    interface IColorDlg
    {
        CONST_VTBL struct IColorDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColorDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IColorDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IColorDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IColorDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IColorDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IColorDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IColorDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IColorDlg_INTERFACE_DEFINED__ */


#ifndef __IGradientEdit_INTERFACE_DEFINED__
#define __IGradientEdit_INTERFACE_DEFINED__

/* interface IGradientEdit */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGradientEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B2AE129-EE82-11D5-95F0-0002E3045703")
    IGradientEdit : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long __RPC_FAR *phwnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gradient( 
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gradient( 
            /* [in] */ IPDGradient __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGradientEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGradientEdit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGradientEdit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGradientEdit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IGradientEdit __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IGradientEdit __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IGradientEdit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IGradientEdit __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            IGradientEdit __RPC_FAR * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IGradientEdit __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            IGradientEdit __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            IGradientEdit __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Window )( 
            IGradientEdit __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *phwnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gradient )( 
            IGradientEdit __RPC_FAR * This,
            /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gradient )( 
            IGradientEdit __RPC_FAR * This,
            /* [in] */ IPDGradient __RPC_FAR *newVal);
        
        END_INTERFACE
    } IGradientEditVtbl;

    interface IGradientEdit
    {
        CONST_VTBL struct IGradientEditVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGradientEdit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGradientEdit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGradientEdit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGradientEdit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGradientEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGradientEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGradientEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGradientEdit_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IGradientEdit_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IGradientEdit_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IGradientEdit_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IGradientEdit_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IGradientEdit_get_gradient(This,pVal)	\
    (This)->lpVtbl -> get_gradient(This,pVal)

#define IGradientEdit_put_gradient(This,newVal)	\
    (This)->lpVtbl -> put_gradient(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IGradientEdit_put_BackColor_Proxy( 
    IGradientEdit __RPC_FAR * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IGradientEdit_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IGradientEdit_get_BackColor_Proxy( 
    IGradientEdit __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);


void __RPC_STUB IGradientEdit_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IGradientEdit_put_Enabled_Proxy( 
    IGradientEdit __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IGradientEdit_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IGradientEdit_get_Enabled_Proxy( 
    IGradientEdit __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);


void __RPC_STUB IGradientEdit_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IGradientEdit_get_Window_Proxy( 
    IGradientEdit __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *phwnd);


void __RPC_STUB IGradientEdit_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGradientEdit_get_gradient_Proxy( 
    IGradientEdit __RPC_FAR * This,
    /* [retval][out] */ IPDGradient __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IGradientEdit_get_gradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGradientEdit_put_gradient_Proxy( 
    IGradientEdit __RPC_FAR * This,
    /* [in] */ IPDGradient __RPC_FAR *newVal);


void __RPC_STUB IGradientEdit_put_gradient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGradientEdit_INTERFACE_DEFINED__ */


#ifndef __IToolsDlg_INTERFACE_DEFINED__
#define __IToolsDlg_INTERFACE_DEFINED__

/* interface IToolsDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IToolsDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8DE5EE0-F128-11D5-95F0-0002E3045703")
    IToolsDlg : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IToolsDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IToolsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IToolsDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IToolsDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IToolsDlg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IToolsDlg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IToolsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IToolsDlg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IToolsDlgVtbl;

    interface IToolsDlg
    {
        CONST_VTBL struct IToolsDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IToolsDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IToolsDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IToolsDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IToolsDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IToolsDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IToolsDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IToolsDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IToolsDlg_INTERFACE_DEFINED__ */


#ifndef __ITabsControl_INTERFACE_DEFINED__
#define __ITabsControl_INTERFACE_DEFINED__

/* interface ITabsControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITabsControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A0AD4520-0579-11D6-95F0-0002E3045703")
    ITabsControl : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr) = 0;
        
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp __RPC_FAR *pFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp __RPC_FAR *pFont) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ForeColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long __RPC_FAR *phwnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_pageWidth( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_pageWidth( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_textPara( 
            /* [retval][out] */ IPDTextPara __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_textPara( 
            /* [in] */ IPDTextPara __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_selected( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_selected( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tbAlign( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_tbAlign( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITabsControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITabsControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITabsControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITabsControl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Font )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ IFontDisp __RPC_FAR *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Font )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ IFontDisp __RPC_FAR *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Font )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ForeColor )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ForeColor )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Window )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *phwnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pageWidth )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_pageWidth )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_textPara )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ IPDTextPara __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_textPara )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ IPDTextPara __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_selected )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_selected )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tbAlign )( 
            ITabsControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_tbAlign )( 
            ITabsControl __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } ITabsControlVtbl;

    interface ITabsControl
    {
        CONST_VTBL struct ITabsControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITabsControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITabsControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITabsControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITabsControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITabsControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITabsControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITabsControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITabsControl_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define ITabsControl_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define ITabsControl_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define ITabsControl_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define ITabsControl_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define ITabsControl_put_ForeColor(This,clr)	\
    (This)->lpVtbl -> put_ForeColor(This,clr)

#define ITabsControl_get_ForeColor(This,pclr)	\
    (This)->lpVtbl -> get_ForeColor(This,pclr)

#define ITabsControl_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define ITabsControl_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define ITabsControl_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define ITabsControl_get_pageWidth(This,pVal)	\
    (This)->lpVtbl -> get_pageWidth(This,pVal)

#define ITabsControl_put_pageWidth(This,newVal)	\
    (This)->lpVtbl -> put_pageWidth(This,newVal)

#define ITabsControl_get_textPara(This,pVal)	\
    (This)->lpVtbl -> get_textPara(This,pVal)

#define ITabsControl_put_textPara(This,newVal)	\
    (This)->lpVtbl -> put_textPara(This,newVal)

#define ITabsControl_get_selected(This,pVal)	\
    (This)->lpVtbl -> get_selected(This,pVal)

#define ITabsControl_put_selected(This,newVal)	\
    (This)->lpVtbl -> put_selected(This,newVal)

#define ITabsControl_get_tbAlign(This,pVal)	\
    (This)->lpVtbl -> get_tbAlign(This,pVal)

#define ITabsControl_put_tbAlign(This,newVal)	\
    (This)->lpVtbl -> put_tbAlign(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_BackColor_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB ITabsControl_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_BackColor_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);


void __RPC_STUB ITabsControl_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE ITabsControl_putref_Font_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ IFontDisp __RPC_FAR *pFont);


void __RPC_STUB ITabsControl_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_Font_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ IFontDisp __RPC_FAR *pFont);


void __RPC_STUB ITabsControl_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_Font_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont);


void __RPC_STUB ITabsControl_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_ForeColor_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB ITabsControl_put_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_ForeColor_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);


void __RPC_STUB ITabsControl_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_Enabled_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB ITabsControl_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_Enabled_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);


void __RPC_STUB ITabsControl_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_Window_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *phwnd);


void __RPC_STUB ITabsControl_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_pageWidth_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITabsControl_get_pageWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_pageWidth_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ITabsControl_put_pageWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_textPara_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ IPDTextPara __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITabsControl_get_textPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_textPara_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ IPDTextPara __RPC_FAR *newVal);


void __RPC_STUB ITabsControl_put_textPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_selected_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITabsControl_get_selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_selected_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITabsControl_put_selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITabsControl_get_tbAlign_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITabsControl_get_tbAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITabsControl_put_tbAlign_Proxy( 
    ITabsControl __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITabsControl_put_tbAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITabsControl_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PDObjectFill;

#ifdef __cplusplus

class DECLSPEC_UUID("3FA55B07-BD79-4921-AB2A-AB43C4E8BBFF")
PDObjectFill;
#endif

EXTERN_C const CLSID CLSID_PDObjectStroke;

#ifdef __cplusplus

class DECLSPEC_UUID("D7946460-2896-464C-B0C3-46AD463F2B02")
PDObjectStroke;
#endif

EXTERN_C const CLSID CLSID_PageDesignerFrame;

#ifdef __cplusplus

class DECLSPEC_UUID("3C36B546-2087-499d-8EA3-3407F2409074")
PageDesignerFrame;
#endif

EXTERN_C const CLSID CLSID_PagesDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("6F35E638-BCE0-4bad-913B-2B852EFE17CC")
PagesDlg;
#endif

#ifndef ___IPDDocumentEvents_DISPINTERFACE_DEFINED__
#define ___IPDDocumentEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPDDocumentEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPDDocumentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DE1FF938-37EB-49b1-B79A-56C18C22DA59")
    _IPDDocumentEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPDDocumentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IPDDocumentEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IPDDocumentEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IPDDocumentEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IPDDocumentEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IPDDocumentEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IPDDocumentEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IPDDocumentEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IPDDocumentEventsVtbl;

    interface _IPDDocumentEvents
    {
        CONST_VTBL struct _IPDDocumentEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPDDocumentEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPDDocumentEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPDDocumentEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPDDocumentEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPDDocumentEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPDDocumentEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPDDocumentEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPDDocumentEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IPDDocumentViewEvents_DISPINTERFACE_DEFINED__
#define ___IPDDocumentViewEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPDDocumentViewEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPDDocumentViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BCBB2144-04E0-497e-B2A0-5E4CDD83D438")
    _IPDDocumentViewEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPDDocumentViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IPDDocumentViewEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IPDDocumentViewEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IPDDocumentViewEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IPDDocumentViewEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IPDDocumentViewEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IPDDocumentViewEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IPDDocumentViewEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IPDDocumentViewEventsVtbl;

    interface _IPDDocumentViewEvents
    {
        CONST_VTBL struct _IPDDocumentViewEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPDDocumentViewEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPDDocumentViewEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPDDocumentViewEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPDDocumentViewEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPDDocumentViewEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPDDocumentViewEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPDDocumentViewEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPDDocumentViewEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ILayersDlgEvents_DISPINTERFACE_DEFINED__
#define ___ILayersDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILayersDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILayersDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("02373F57-7E5F-4BB9-9DA9-641FABFBCA75")
    _ILayersDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILayersDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ILayersDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ILayersDlgEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ILayersDlgEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ILayersDlgEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ILayersDlgEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ILayersDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ILayersDlgEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ILayersDlgEventsVtbl;

    interface _ILayersDlgEvents
    {
        CONST_VTBL struct _ILayersDlgEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILayersDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ILayersDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ILayersDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ILayersDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ILayersDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ILayersDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ILayersDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILayersDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PDDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("93EE1DB5-F14D-4180-AA89-736D7E3420F7")
PDDocument;
#endif

EXTERN_C const CLSID CLSID_PDDocumentView;

#ifdef __cplusplus

class DECLSPEC_UUID("F1BB0D88-BC4A-4b5c-A5E8-F601494EB863")
PDDocumentView;
#endif

EXTERN_C const CLSID CLSID_PDMatrix;

#ifdef __cplusplus

class DECLSPEC_UUID("7F59907A-D122-4dce-960C-BB01CAE9C32D")
PDMatrix;
#endif

EXTERN_C const CLSID CLSID_PDGradient;

#ifdef __cplusplus

class DECLSPEC_UUID("D5ABEC21-EFB9-11d5-95F0-0002E3045703")
PDGradient;
#endif

EXTERN_C const CLSID CLSID_LayersDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("6627D059-6D6E-4D99-A8CE-CBD4374A2A07")
LayersDlg;
#endif

EXTERN_C const CLSID CLSID_PDRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("CC6AE802-69B8-4DE9-A48C-BFA6EC65F81B")
PDRenderer;
#endif

#ifndef ___ISwatchesDlgEvents_DISPINTERFACE_DEFINED__
#define ___ISwatchesDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISwatchesDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISwatchesDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9DEC5942-E952-11D5-95F0-0002E3045703")
    _ISwatchesDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISwatchesDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ISwatchesDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ISwatchesDlgEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ISwatchesDlgEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ISwatchesDlgEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ISwatchesDlgEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ISwatchesDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ISwatchesDlgEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ISwatchesDlgEventsVtbl;

    interface _ISwatchesDlgEvents
    {
        CONST_VTBL struct _ISwatchesDlgEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISwatchesDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISwatchesDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISwatchesDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISwatchesDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISwatchesDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISwatchesDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISwatchesDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISwatchesDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SwatchesDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("9DEC5941-E952-11D5-95F0-0002E3045703")
SwatchesDlg;
#endif

#ifndef ___INavigatorDlgEvents_DISPINTERFACE_DEFINED__
#define ___INavigatorDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _INavigatorDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__INavigatorDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9DEC5945-E952-11D5-95F0-0002E3045703")
    _INavigatorDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _INavigatorDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _INavigatorDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _INavigatorDlgEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _INavigatorDlgEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _INavigatorDlgEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _INavigatorDlgEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _INavigatorDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _INavigatorDlgEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _INavigatorDlgEventsVtbl;

    interface _INavigatorDlgEvents
    {
        CONST_VTBL struct _INavigatorDlgEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _INavigatorDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _INavigatorDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _INavigatorDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _INavigatorDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _INavigatorDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _INavigatorDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _INavigatorDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___INavigatorDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NavigatorDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("9DEC5944-E952-11D5-95F0-0002E3045703")
NavigatorDlg;
#endif

#ifndef ___IGradientDlgEvents_DISPINTERFACE_DEFINED__
#define ___IGradientDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IGradientDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IGradientDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E0854BEB-09AD-46E6-BD69-DADCE372615F")
    _IGradientDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IGradientDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IGradientDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IGradientDlgEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IGradientDlgEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IGradientDlgEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IGradientDlgEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IGradientDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IGradientDlgEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IGradientDlgEventsVtbl;

    interface _IGradientDlgEvents
    {
        CONST_VTBL struct _IGradientDlgEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGradientDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IGradientDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IGradientDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IGradientDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IGradientDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IGradientDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IGradientDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IGradientDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GradientDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("80A36719-7877-49F1-81A6-5E167C0D75D0")
GradientDlg;
#endif

#ifndef ___IStrokeDlgEvents_DISPINTERFACE_DEFINED__
#define ___IStrokeDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IStrokeDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IStrokeDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CC00CE83-ED4C-11D5-95F0-0002E3045703")
    _IStrokeDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IStrokeDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IStrokeDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IStrokeDlgEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IStrokeDlgEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IStrokeDlgEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IStrokeDlgEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IStrokeDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IStrokeDlgEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IStrokeDlgEventsVtbl;

    interface _IStrokeDlgEvents
    {
        CONST_VTBL struct _IStrokeDlgEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IStrokeDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IStrokeDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IStrokeDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IStrokeDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IStrokeDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IStrokeDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IStrokeDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IStrokeDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_StrokeDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("CC00CE82-ED4C-11D5-95F0-0002E3045703")
StrokeDlg;
#endif

#ifndef ___ISwatchesListEvents_DISPINTERFACE_DEFINED__
#define ___ISwatchesListEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISwatchesListEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISwatchesListEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8B2AE125-EE82-11D5-95F0-0002E3045703")
    _ISwatchesListEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISwatchesListEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ISwatchesListEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ISwatchesListEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ISwatchesListEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ISwatchesListEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ISwatchesListEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ISwatchesListEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ISwatchesListEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ISwatchesListEventsVtbl;

    interface _ISwatchesListEvents
    {
        CONST_VTBL struct _ISwatchesListEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISwatchesListEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISwatchesListEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISwatchesListEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISwatchesListEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISwatchesListEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISwatchesListEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISwatchesListEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISwatchesListEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SwatchesList;

#ifdef __cplusplus

class DECLSPEC_UUID("8B2AE124-EE82-11D5-95F0-0002E3045703")
SwatchesList;
#endif

#ifndef ___IColorDlgEvents_DISPINTERFACE_DEFINED__
#define ___IColorDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IColorDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IColorDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8B2AE128-EE82-11D5-95F0-0002E3045703")
    _IColorDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IColorDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IColorDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IColorDlgEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IColorDlgEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IColorDlgEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IColorDlgEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IColorDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IColorDlgEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IColorDlgEventsVtbl;

    interface _IColorDlgEvents
    {
        CONST_VTBL struct _IColorDlgEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IColorDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IColorDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IColorDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IColorDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IColorDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IColorDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IColorDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IColorDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ColorDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("8B2AE127-EE82-11D5-95F0-0002E3045703")
ColorDlg;
#endif

#ifndef ___IGradientEditEvents_DISPINTERFACE_DEFINED__
#define ___IGradientEditEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IGradientEditEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IGradientEditEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8B2AE12B-EE82-11D5-95F0-0002E3045703")
    _IGradientEditEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IGradientEditEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IGradientEditEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IGradientEditEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IGradientEditEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IGradientEditEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IGradientEditEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IGradientEditEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IGradientEditEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IGradientEditEventsVtbl;

    interface _IGradientEditEvents
    {
        CONST_VTBL struct _IGradientEditEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGradientEditEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IGradientEditEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IGradientEditEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IGradientEditEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IGradientEditEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IGradientEditEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IGradientEditEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IGradientEditEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GradientEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("8B2AE12A-EE82-11D5-95F0-0002E3045703")
GradientEdit;
#endif

#ifndef ___IToolsDlgEvents_DISPINTERFACE_DEFINED__
#define ___IToolsDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IToolsDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IToolsDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C8DE5EE2-F128-11D5-95F0-0002E3045703")
    _IToolsDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IToolsDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IToolsDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IToolsDlgEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IToolsDlgEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IToolsDlgEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IToolsDlgEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IToolsDlgEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IToolsDlgEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IToolsDlgEventsVtbl;

    interface _IToolsDlgEvents
    {
        CONST_VTBL struct _IToolsDlgEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IToolsDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IToolsDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IToolsDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IToolsDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IToolsDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IToolsDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IToolsDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IToolsDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ToolsDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("C8DE5EE1-F128-11D5-95F0-0002E3045703")
ToolsDlg;
#endif

#ifndef ___ITabsControlEvents_DISPINTERFACE_DEFINED__
#define ___ITabsControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITabsControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITabsControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A0AD4522-0579-11D6-95F0-0002E3045703")
    _ITabsControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITabsControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ITabsControlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ITabsControlEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ITabsControlEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ITabsControlEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ITabsControlEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ITabsControlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ITabsControlEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ITabsControlEventsVtbl;

    interface _ITabsControlEvents
    {
        CONST_VTBL struct _ITabsControlEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITabsControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITabsControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITabsControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITabsControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITabsControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITabsControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITabsControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITabsControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TabsControl;

#ifdef __cplusplus

class DECLSPEC_UUID("A0AD4521-0579-11D6-95F0-0002E3045703")
TabsControl;
#endif

EXTERN_C const CLSID CLSID_TabsDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("A0AD4527-0579-11D6-95F0-0002E3045703")
TabsDlg;
#endif

EXTERN_C const CLSID CLSID_SwatchLibraryDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("0714F6CD-0B72-11D6-95F0-0002E3045703")
SwatchLibraryDlg;
#endif

EXTERN_C const CLSID CLSID_LinksDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("ABE418A4-26EF-11D6-95F0-0002E3045703")
LinksDlg;
#endif

EXTERN_C const CLSID CLSID_TransparencyDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("1A82E864-2969-11D6-95F0-0002E3045703")
TransparencyDlg;
#endif

EXTERN_C const CLSID CLSID_FilterGraphDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("1A82E867-2969-11D6-95F0-0002E3045703")
FilterGraphDlg;
#endif

EXTERN_C const CLSID CLSID_FEGaussianBlur;

#ifdef __cplusplus

class DECLSPEC_UUID("92CFFB8E-A5D7-473C-91D4-A87F9A4C1819")
FEGaussianBlur;
#endif

EXTERN_C const CLSID CLSID_FEOffset;

#ifdef __cplusplus

class DECLSPEC_UUID("0C8310D0-FEBA-44D9-B3F5-4EBD7ABF2EA3")
FEOffset;
#endif

EXTERN_C const CLSID CLSID_FEComposite;

#ifdef __cplusplus

class DECLSPEC_UUID("1E714467-0A20-4742-B046-3A8D9CD2EA77")
FEComposite;
#endif

EXTERN_C const CLSID CLSID_PluginFiltersDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("CDDB6068-8FF4-4736-9FC1-662B36D44C0C")
PluginFiltersDlg;
#endif

EXTERN_C const CLSID CLSID_StylesDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("9D0B1DCC-2F88-46B5-A885-E575934E557B")
StylesDlg;
#endif

EXTERN_C const CLSID CLSID_FEFreeTransform;

#ifdef __cplusplus

class DECLSPEC_UUID("41B4488F-F3C5-4FD3-BC8B-6454F5E17144")
FEFreeTransform;
#endif

EXTERN_C const CLSID CLSID_Archive;

#ifdef __cplusplus

class DECLSPEC_UUID("2B326771-4AE4-4B88-90C1-11F3A8F289F8")
Archive;
#endif

EXTERN_C const CLSID CLSID_PDObjectLayerGroup;

#ifdef __cplusplus

class DECLSPEC_UUID("E2146354-81DA-43fa-96F4-F3E5AB57776F")
PDObjectLayerGroup;
#endif

EXTERN_C const CLSID CLSID_PDContentGraphic;

#ifdef __cplusplus

class DECLSPEC_UUID("10637E82-06D1-4292-9A7E-09C1EAA099B9")
PDContentGraphic;
#endif

EXTERN_C const CLSID CLSID_PDContentText;

#ifdef __cplusplus

class DECLSPEC_UUID("2EEF7F4C-9575-4f67-90B9-4EBFD73F424D")
PDContentText;
#endif

EXTERN_C const CLSID CLSID_PDObjectFrame;

#ifdef __cplusplus

class DECLSPEC_UUID("FB40FB8B-201E-490f-A18F-5E46DA62AC21")
PDObjectFrame;
#endif

EXTERN_C const CLSID CLSID_PDObjectGroup;

#ifdef __cplusplus

class DECLSPEC_UUID("7267866F-22B3-4373-BC1E-8841A500266F")
PDObjectGroup;
#endif

EXTERN_C const CLSID CLSID_PDLayer;

#ifdef __cplusplus

class DECLSPEC_UUID("A62D3683-5A0B-453c-B333-41BE0B9DECA0")
PDLayer;
#endif

EXTERN_C const CLSID CLSID_PDPage;

#ifdef __cplusplus

class DECLSPEC_UUID("6DF2BC95-C11E-48d5-AB96-EF2874DBE413")
PDPage;
#endif

EXTERN_C const CLSID CLSID_PDSpreadDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("2EB33C5C-DDEB-4e97-9921-924AB10D5AE4")
PDSpreadDocument;
#endif

EXTERN_C const CLSID CLSID_PDSpreadMaster;

#ifdef __cplusplus

class DECLSPEC_UUID("9346CA50-E61D-44ac-A5AA-B2BCB2265D90")
PDSpreadMaster;
#endif

EXTERN_C const CLSID CLSID_PDAppearance;

#ifdef __cplusplus

class DECLSPEC_UUID("2AF0171F-9304-4ee9-9F8A-922A6F31E4A0")
PDAppearance;
#endif

EXTERN_C const CLSID CLSID_PDFilterPrimitive;

#ifdef __cplusplus

class DECLSPEC_UUID("6394072C-3DE4-4c18-9F55-459E08491271")
PDFilterPrimitive;
#endif

EXTERN_C const CLSID CLSID_PDSwatchPattern;

#ifdef __cplusplus

class DECLSPEC_UUID("BDF3FED4-9E3C-457D-B672-4FAF9B1F4910")
PDSwatchPattern;
#endif

EXTERN_C const CLSID CLSID_AppearanceDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("D584CEF4-1748-406E-AC02-B8189C4C2B04")
AppearanceDlg;
#endif

EXTERN_C const CLSID CLSID_PDSwatchColor;

#ifdef __cplusplus

class DECLSPEC_UUID("4F563EBA-B0B4-484d-98DD-8C4BD3D5B42A")
PDSwatchColor;
#endif

EXTERN_C const CLSID CLSID_PDSwatchGradient;

#ifdef __cplusplus

class DECLSPEC_UUID("B7407AE8-16A3-4d97-B8CC-9E56EFC89AAD")
PDSwatchGradient;
#endif

EXTERN_C const CLSID CLSID_PDSwatchNone;

#ifdef __cplusplus

class DECLSPEC_UUID("0AC04623-BDF9-43e8-B073-1650AD48D863")
PDSwatchNone;
#endif

EXTERN_C const CLSID CLSID_PDGradientStop;

#ifdef __cplusplus

class DECLSPEC_UUID("0E6216BC-1EE9-4758-871F-68B0A34C4147")
PDGradientStop;
#endif

EXTERN_C const CLSID CLSID_SymbolsDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("666F1FC1-E52A-4117-8E98-97375A238F73")
SymbolsDlg;
#endif

EXTERN_C const CLSID CLSID_PDSymbol;

#ifdef __cplusplus

class DECLSPEC_UUID("51498E1E-B85F-4762-8963-7B98E4EBEA12")
PDSymbol;
#endif

EXTERN_C const CLSID CLSID_PDObjectSymbolInstance;

#ifdef __cplusplus

class DECLSPEC_UUID("D95F583F-7C7E-435D-88B5-53E0D5081CFC")
PDObjectSymbolInstance;
#endif

EXTERN_C const CLSID CLSID_PDObjectSymbolInstanceSet;

#ifdef __cplusplus

class DECLSPEC_UUID("1F315214-1C37-40AA-A87B-68F16FF4C7B3")
PDObjectSymbolInstanceSet;
#endif
#endif /* __PAGEDESIGNERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
