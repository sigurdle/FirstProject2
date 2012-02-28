# Microsoft Developer Studio Project File - Name="SWF" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SWF - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWF.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWF.mak" CFG="SWF - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWF - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SWF - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWF - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "../../Intermediate/Win32/SWF/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWF_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O2 /I "../../include/SWF" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWF_EXPORTS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /map /debug /machine:I386 /out:"../../bin/Win32/Release/SWF.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/SWF/Release
InputPath=\MMStudio\bin\Win32\Release\SWF.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Release/SWF.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ParseMap $(IntDir)/SWF.map "../../bin/Win32/Debug/SWF.typeinfo" "../../bin/Win32/Release/SWF.ad"

# End Custom Build

!ELSEIF  "$(CFG)" == "SWF - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "../../Intermediate/Win32/SWF/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWF_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../include/SWF" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWF_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Debug/SWF.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/SWF/Debug
InputPath=\MMStudio\bin\Win32\Debug\SWF.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Debug/SWF.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ParseMap $(IntDir)/SWF.map "../../bin/Win32/Debug/SWF.typeinfo"

# End Custom Build

!ENDIF 

# Begin Target

# Name "SWF - Win32 Release"
# Name "SWF - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\SWF\ActionNames.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SWF\Movie.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\swf\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\swf\SWF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SWF\swfdebug.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SWF\swfdecoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SWF\swfencoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SWF\swfplayer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\SWF\_Movie.h
# End Source File
# Begin Source File

SOURCE=..\..\include\SWF\ActionNames.h
# End Source File
# Begin Source File

SOURCE=..\..\include\SWF\Movie.h
# End Source File
# Begin Source File

SOURCE=..\..\include\swf\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\include\SWF\swf.h

!IF  "$(CFG)" == "SWF - Win32 Release"

!ELSEIF  "$(CFG)" == "SWF - Win32 Debug"

# Begin Custom Build
InputPath=..\..\include\SWF\swf.h

"../../bin/Win32/Debug/SWF.typeinfo" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	Test_gc $(InputPath) "../../bin/Win32/Debug/SWF.typeinfo"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\include\SWF\swfdebug.h
# End Source File
# Begin Source File

SOURCE=..\..\include\SWF\swfdecoder.h
# End Source File
# Begin Source File

SOURCE=..\..\include\SWF\swfencoder.h
# End Source File
# Begin Source File

SOURCE=..\..\include\SWF\swfplayer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
