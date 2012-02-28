# Microsoft Developer Studio Project File - Name="LPDF" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LPDF - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LPDF.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LPDF.mak" CFG="LPDF - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LPDF - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LPDF - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LPDF - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "../../Intermediate/Win32/LPDF/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Debug/LPDF.dll"

!ELSEIF  "$(CFG)" == "LPDF - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LPDF___Win32_Release"
# PROP BASE Intermediate_Dir "LPDF___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "../../Intermediate/Win32/LPDF/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"../bin/Release/LPDF.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Release/LPDF.dll"

!ENDIF 

# Begin Target

# Name "LPDF - Win32 Debug"
# Name "LPDF - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Cos"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosArray.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosBoolean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosBoolean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosDict.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosDict.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosDoc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosDoc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosInteger.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosName.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosObj.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosReal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosReal.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosStream.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFCosString.h
# End Source File
# End Group
# Begin Group "PD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\LPDF\PDFPDDoc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFPDDoc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFPDPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFPDPage.h
# End Source File
# End Group
# Begin Group "PDE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEColorSpace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEColorSpace.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEContent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEContent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEExtGState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEExtGState.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEGraphicState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEGraphicState.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEImage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEPath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEPath.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEText.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\PDFEText.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\LPDF\LPDF.cpp
# End Source File
# Begin Source File

SOURCE=.\LPDF.def
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\LPDF.h
# End Source File
# Begin Source File

SOURCE=.\LPDF.rc
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\LPDF\PDFObject.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LPDF\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\PDFCosDoc.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEColorSpace.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEContent.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEExtGState.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEGraphicState.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEImage.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEMatrix.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEPath.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFEText.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFPDDoc.rgs
# End Source File
# Begin Source File

SOURCE=.\PDFPDPage.rgs
# End Source File
# End Group
# End Target
# End Project
