# Microsoft Developer Studio Project File - Name="SQL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SQL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SQL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SQL.mak" CFG="SQL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SQL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SQL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SQL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SQL_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /Zi /O2 /I "c:\program files\gnuwin32\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SQL_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../bin/Release/SQL.dll"

!ELSEIF  "$(CFG)" == "SQL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SQL_EXPORTS" /Yu"stdafx.h" /FD /GZ  /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /Zi /Od /I "c:\program files\gnuwin32\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SQL_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../bin/Debug/SQL.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SQL - Win32 Release"
# Name "SQL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\SQL\db.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\db.h
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\dbimp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\dbimp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\dbsql.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\dbsql.h
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\SQL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\sql.h
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\sql_a.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\sql_a.h
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\sql_lex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\sql_lex.y

!IF  "$(CFG)" == "SQL - Win32 Release"

!ELSEIF  "$(CFG)" == "SQL - Win32 Debug"

# Begin Custom Build
InputDir=\MMStudio\src\SQL
InputPath=..\..\src\SQL\sql_lex.y

"lex.sql_.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"c:\program files\gnuwin32\bin\flex.exe" -i -Psql_ $(InputDir)/sql_lex.y 
	copy /B lex.sql_.c "../../src/SQL 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\sql_parse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\sql_parse.y

!IF  "$(CFG)" == "SQL - Win32 Release"

!ELSEIF  "$(CFG)" == "SQL - Win32 Debug"

# Begin Custom Build
InputPath=..\..\src\SQL\sql_parse.y

BuildCmds= \
	cd "c:\program files\gnuwin32\bin" \
	"c:\program files\gnuwin32\bin\bison.exe" -d -t -r state "c:\mmstudio\src\SQL\sql_parse.y" \
	

"c:\mmstudio\src\SQL\sql_parse.tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"c:\mmstudio\src\SQL\sql_parse.tab.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\SQL\StdAfx.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
