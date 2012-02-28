# Microsoft Developer Studio Project File - Name="LXML" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LXML - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LXML.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LXML.mak" CFG="LXML - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LXML - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LXML - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LXML - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "../../Intermediate/Win32/LXML/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /GR /GX /Z7 /Od /I "c:\program files\gnuwin32\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /Zm300 /c
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Debug/LXML.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/LXML/Debug
InputPath=\MMStudio\bin\Win32\Debug\LXML.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Debug/LXML.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"../../bin/Win32/Debug/ParseMap" $(IntDir)/LXML.map "../../bin/Win32/Debug/LXML.typeinfo"

# End Custom Build

!ELSEIF  "$(CFG)" == "LXML - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LXML___Win32_Release"
# PROP BASE Intermediate_Dir "LXML___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "../../Intermediate/Win32/LXML/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O1 /I "c:\program files\gnuwin32\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O1 /I "c:\program files\gnuwin32\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"../bin/Release/LXML.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Release/LXML.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/LXML/Release
InputPath=\MMStudio\bin\Win32\Release\LXML.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Release/LXML.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"../../bin/Win32/Debug/ParseMap" $(IntDir)/LXML.map "../../bin/Win32/Debug/LXML.typeinfo" "../../bin/Win32/Release/LXML.ad"

# End Custom Build

!ENDIF 

# Begin Target

# Name "LXML - Win32 Debug"
# Name "LXML - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "DOM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\LXML\Attr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\Attr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMAttrImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMBuilder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMBuilder.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMCDATASection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMCDATASection.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMCharacterData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMCharacterData.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMComment.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMComment.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocumentEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocumentEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocumentFragment.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocumentFragment.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocumentType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocumentType.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMDocumentViewImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEntity.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEntity.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEntityReference.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEntityReference.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMError.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEventTargetImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMEventTargetImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMGenericDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMGenericDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMGenericElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMGenericElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMImplementation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMImplementation.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMLocator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMLocator.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMMutationEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMMutationEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMMutationEventImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMMutationNameEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMMutationNameEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMNamedNodeMap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMNamedNodeMap.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMNameList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMNameList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMNodeIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMNodeIterator.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMNotWellformed.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMParser.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMProcessingInstruction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMProcessingInstruction.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMProcessingInstructionStylesheet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMProcessingInstructionStylesheet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMRange.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMRange.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DOMUIEventImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\Element.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\Element.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ElementEditASImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ElementEditVALImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ElementEditVALImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDocumentASImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDocumentEditVALImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDOMDocumentHTMLImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDOMDocumentRangeImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDOMDocumentRangeImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDOMDocumentTraversalImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDTDElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDTDElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LDTDNodeImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LinkStyleImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXSLProcessor.cpp

!IF  "$(CFG)" == "LXML - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LXML - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXSLProcessor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXSLTemplate.cpp

!IF  "$(CFG)" == "LXML - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LXML - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXSLTemplate.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\MouseEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\MouseEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\Node.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\Node.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\NodeEditVALImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\NodeEditVALImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\NodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\NodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ScriptSite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ScriptSite.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGZoomEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGZoomEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\Text.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\Text.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\TextEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\TextEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\TimeEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\TimeEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\UIEvent.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\LXML\AnimationElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\AnimationElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\AnimationTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\AnimationTarget.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDAttribute.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDAttribute.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDContentModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDContentModel.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDEntity.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDEntity.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDModel.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDNamedObjectMap.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASDTDObjectImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLComplexTypeDeclaration.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLSchemaComplexContentType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLSchemaElementDefinition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLSchemaElementDefinition.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLSchemaModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLSchemaModel.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLSchemaModelGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ASXMLSchemaModelGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\BooleanValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\clockvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSCharsetRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSCharsetRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSCommentRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSCommentRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSCounter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSCounter.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSFontFaceRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSFontFaceRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSImportRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSImportRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSMediaRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSMediaRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSPrimitiveValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSPrimitiveValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\cssproperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\cssproperty.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSRect.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSRuleList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSRuleList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSSelector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSSelector.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStackingContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStackingContext.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStream.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStyleDeclaration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStyleDeclaration.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStyleRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStyleRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStyleSheet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSStyleSheet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\cssunits.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\cssunits.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSUnknownRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSUnknownRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSValueImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSValueList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\CSSValueList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DocumentASImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DocumentCSSImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DocumentEditVALImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DocumentParser.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DocumentStyleImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DocumentStyleImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DTDDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DTDDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DTDParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\DTDParser.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\EnumerationCalcModeType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\EnumerationCalcModeType.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\HTMContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\HTMContext.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LBoxes.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LBoxWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LBoxWindow.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LElementCSSInlineStyleImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LElementTimeContainerImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LElementTimeImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LElementTimeImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LSVGRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LSVGRect.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LSVGRectImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LViewCSS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LViewCSS.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXML.cpp
# End Source File
# Begin Source File

SOURCE=.\LXML.def
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXML.h

!IF  "$(CFG)" == "LXML - Win32 Debug"

# Begin Custom Build
InputPath=..\..\src\LXML\LXML.h

"../../bin/Win32/Debug/LXML.typeinfo" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"../../bin/Win32/Debug/Test_gc" $(InputPath) "../../bin/Win32/Debug/LXML.typeinfo"

# End Custom Build

!ELSEIF  "$(CFG)" == "LXML - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LXML.rc
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXML2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXML2.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXMLDocumentView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXMLDocumentView.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\LXMLImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\MediaList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\MediaList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\MutationEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\NamedColors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\NamedColors.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\parsecolor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\parsecolor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PBlockBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PBlockBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PElementBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PElementBase.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PElementBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PElementBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PInlineBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PInlineBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PLineBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PLineBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PNode.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PParentBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PParentBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PTextNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PTextNode.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PWord.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PWord.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\RGBColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\RGBColor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SGMLParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SGMLParser.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SMILTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SMILTime.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SMILTimeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SMILTimeList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\StyleSheet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\StyleSheet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\StyleSheetList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\StyleSheetList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGColor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGColorImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGColorImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGColorProfileRule.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGColorProfileRule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGICCColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGICCColor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGNumber.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGNumber.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGNumberList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGNumberList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGNumberValue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGPaint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGPaint.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGPointList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGPointList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGShadowableImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGShadowableImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGShadowElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\SVGShadowElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\ValueType.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\XMLAttr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\XMLAttr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\XMLParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\XMLParser.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\LXML\CSS2PropertiesImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LXML\PImage.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00003.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00008.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00009.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00010.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\hand0.cur
# End Source File
# Begin Source File

SOURCE=.\res\hand2.cur
# End Source File
# Begin Source File

SOURCE=.\res\resize_c.cur
# End Source File
# Begin Source File

SOURCE=.\res\resize_e.cur
# End Source File
# Begin Source File

SOURCE=.\res\resize_n.cur
# End Source File
# Begin Source File

SOURCE=.\res\resize_s.cur
# End Source File
# End Group
# End Target
# End Project
