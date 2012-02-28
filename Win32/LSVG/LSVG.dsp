# Microsoft Developer Studio Project File - Name="LSVG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LSVG - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LSVG.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LSVG.mak" CFG="LSVG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LSVG - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LSVG - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LSVG - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "../../Intermediate/Win32/LSVG/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /GR /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /Zm400 /c
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Debug/LSVG.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/LSVG/Debug
InputPath=\MMStudio\bin\Win32\Debug\LSVG.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Debug/LSVG.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ParseMap $(IntDir)/LSVG.map "../../bin/Win32/Debug/LSVG.typeinfo"

# End Custom Build

!ELSEIF  "$(CFG)" == "LSVG - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LSVG___Win32_Release"
# PROP BASE Intermediate_Dir "LSVG___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "../../Intermediate/Win32/LSVG/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O2 /I "..\Include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /Zm400 /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O2 /I "..\Include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /Zm400 /c
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"../bin/Release/LSVG.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Release/LSVG.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/LSVG/Release
InputPath=\MMStudio\bin\Win32\Release\LSVG.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Release/LSVG.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ParseMap $(IntDir)/LSVG.map "../../bin/Win32/Debug/LSVG.typeinfo" "../../bin/Win32/Release/LSVG.ad"

# End Custom Build

!ENDIF 

# Begin Target

# Name "LSVG - Win32 Debug"
# Name "LSVG - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\LSVG\LDOMDocumentSVGAnimationImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\LDOMDocumentSVGFiltersImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\LDOMDocumentSVGImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\LDOMDocumentSVGShapesImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\LDOMDocumentSVGTextFontsImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGImplementation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGImplementation.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\LSVG\LSVG.cpp
# End Source File
# Begin Source File

SOURCE=.\LSVG.def
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\LSVG.h

!IF  "$(CFG)" == "LSVG - Win32 Debug"

# Begin Custom Build
InputPath=..\..\src\LSVG\LSVG.h

"../../bin/Win32/Debug/LSVG.typeinfo" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	Test_gc $(InputPath) "../../bin/Win32/Debug/LSVG.typeinfo"

# End Custom Build

!ELSEIF  "$(CFG)" == "LSVG - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LSVG.rc
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\LSVG2.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGAElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGAElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGAltGlyphElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGAltGlyphElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGBasicShape.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGCircleElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGCircleElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGClipPathElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGClipPathElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGColorProfileElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGColorProfileElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGEllipseElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGEllipseElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEBlendElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEBlendElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEColorMatrixElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEColorMatrixElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEComponentTransferElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEComponentTransferElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFECompositeElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFECompositeElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEConvolveMatrixElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEConvolveMatrixElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEDiffuseLightingElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEDisplacementMapElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEDisplacementMapElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEFloodElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEFloodElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEGaussianBlurElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEGaussianBlurElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEImageElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEImageElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFELightingElementImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEMorphologyElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEMorphologyElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEOffsetElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEOffsetElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFEPointLightElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFESpecularLightingElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFESpecularLightingElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFETurbulenceElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFETurbulenceElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFilterElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFilterElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFlowRegionElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFlowRegionElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFlowTextElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFlowTextElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFontElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGFontElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGForeignObjectElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGForeignObjectElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGGElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGGElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGGlyphElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGGlyphElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGGradientElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGGradientElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGImageElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGImageElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGLinearGradientElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGLinearGradientElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGLineElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGLineElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGMarkerElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGMarkerElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGMaskElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGMaskElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPathElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPathElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPatternElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPatternElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPolygonElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPolygonElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPolylineElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGPolylineElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGRadialGradientElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGRadialGradientElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGRectElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGRectElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSolidColorElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSolidColorElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSVGElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSVGElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSwitchElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSwitchElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSymbolElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGSymbolElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextContentElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextContentElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextPathElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextPathElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextPositioningElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTextPositioningElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTRefElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTRefElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTSpanElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGTSpanElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGUseElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGUseElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGVideoElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\PSVGVideoElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAltGlyphDefElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAltGlyphElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAltGlyphElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAngle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAngle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimateColorElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedAngle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedAngle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedBoolean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedBoolean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedInteger.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedLength.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedLength.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedLengthList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedLengthList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedNumber.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedNumber.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedNumberList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedNumberList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedNumberT.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedPathDataImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedPointsImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedPreserveAspectRatio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedRectT.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedTransformList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimatedTransformList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimateElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimateElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimateMotionElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimateMotionElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimateTransformElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimateTransformElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAnimationElementImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAudioElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGAudioElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGCircleElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGCircleElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGClipPathElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGClipPathElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGColorProfileElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGColorProfileElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGComponentTransferFunctionElementImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGComponentTransferFunctionElementImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGCursorElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGCursorElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGDefsElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGDefsElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGDescElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGDescElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGElementInstance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGElementInstance.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGElementInstanceList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGElementInstanceList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEllipseElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEllipseElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationBlendModeTypeValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationBlendModeTypeValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationChannelSelectorValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationChannelSelectorValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationColorMatrixTypeValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationColorMatrixTypeValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationComponentTransferTypeValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationComponentTransferTypeValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationCompositeOperatorValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationCompositeOperatorValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationMarkerOrientationTypeValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationMarkerOrientationTypeValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationMarkerUnitTypeValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationMarkerUnitTypeValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationMorphologyOperatorValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationMorphologyOperatorValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationSpreadMethodTypeValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGEnumerationSpreadMethodTypeValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGExtensionDefsElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGExtensionDefsElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGExternalResourcesRequiredImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEBlendElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEBlendElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEColorMatrixElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEColorMatrixElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEComponentTransferElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEComponentTransferElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFECompositeElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFECompositeElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEConvolveMatrixElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEConvolveMatrixElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEDiffuseLightingElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEDiffuseLightingElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEDisplacementMapElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEDisplacementMapElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEDistantLightElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEDistantLightElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEFloodElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEFloodElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEFuncAElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEFuncBElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEFuncGElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEFuncRElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEGaussianBlurElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEGaussianBlurElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEImageElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEImageElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEMergeElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEMergeElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEMergeNodeElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEMergeNodeElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEMorphologyElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEMorphologyElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEOffsetElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEOffsetElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEPointLightElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFEPointLightElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFESpecularLightingElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFESpecularLightingElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFESpotLightElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFESpotLightElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFETileElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFETileElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFETurbulenceElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFETurbulenceElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFilterElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFilterElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFilterPrimitiveStandardAttributesImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFitToViewBoxImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFlowDivElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFlowTextElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFontElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFontElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFontFaceElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGFontFaceElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGForeignObjectElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGForeignObjectElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGenericElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGenericElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGlyphAttributesImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGlyphElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGlyphElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGlyphRefElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGlyphRefElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGGradientElementImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGHKernElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGImageElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGImageElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLangSpaceImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLengthList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLengthList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLinearGradientElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLinearGradientElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLineElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLineElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLocatableImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGLocatableImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMarkerElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMarkerElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMaskElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMaskElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMetadataElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMetadataElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMissingGlyphElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGMissingGlyphElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGParElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPathElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPathElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPatternElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPatternElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPolygonElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPolygonElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPolylineElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPolylineElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPreserveAspectRatio.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGPreserveAspectRatio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGRadialGradientElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGRadialGradientElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGRectElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGRectElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGScriptElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGScriptElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSeqElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSetElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSetElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGStopElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGStopElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGStyleElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGStyleElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSVGElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSVGElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSwitchElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSwitchElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSymbolElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGSymbolElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTextContentElementImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTextElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTextElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTextPathElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTextPathElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTextPositioningElementImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTitleElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTitleElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTransform.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTransformableImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTransformList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTransformList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTRefElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTRefElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTSpanElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGTSpanElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGURIReferenceImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGUseElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGUseElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGVideoElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGVideoElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGViewElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGViewElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LSVG\SVGVKernElement.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\LHTML\icm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\LSVGDocument.rgs
# End Source File
# Begin Source File

SOURCE=.\LSVGImplementation.rgs
# End Source File
# End Group
# End Target
# End Project
