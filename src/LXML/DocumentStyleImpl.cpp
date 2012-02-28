#include "stdafx.h"
#include "LXML2.h"

#if 0

#include "DocumentStyleImpl.h"

#if WIN32

#include "../include/windows_header.h"

#if 0
#include <shlwapi.h>
#include <shlobj.h>
#endif

#include <stdlib.h>

#endif

namespace System
{
namespace Web
{

void DocumentStyleImpl::loadDefaultStylesheet()
{

//	LCSS::DocumentStyleImpl* documentStyle = dynamic_cast<LCSS::DocumentStyleImpl*>(m_document);
//	if (documentStyle)
	{
#if 0//WIN32
		TCHAR appdata[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, appdata);
#else
		char appdata[MAX_PATH];
		std::strcpy(appdata, "C:\\Documents and Settings\\All Users\\Application Data");
#endif

		CSSStyleSheet* stylesheet = new CSSStyleSheet(NULL/*ownerNode*/, NULL/*ownerRule*/);
		if (stylesheet)
		{
#if WIN32
			char pathname[MAX_PATH];
			_makepath(pathname, NULL, appdata, "LXFramework", NULL);

			char filename[260];

			/*
			if (!wcscmp(taglocalName, OLESTR("nitf")))
			{
				_makepath(filename, NULL, pathname, "nitf.css", NULL);
			}
			else if (!wcscmp(taglocalName, OLESTR("article")))	// DocBook
			{
				_makepath(filename, NULL, pathname, "docbook.css", NULL);
			}
			else if (!wcscmp(taglocalName, OLESTR("stylesheet")))
			{
				_makepath(filename, NULL, pathname, "xslt.css", NULL);
			}
			else if (!wcscmp(taglocalName, OLESTR("html")) ||
				!wcscmp(taglocalName, OLESTR("svg")) ||
				!wcscmp(taglocalName, OLESTR("lxui")))
				*/
			{
				_makepath(filename, NULL, pathname, "html.css", NULL);
			}

			//MessageBox(NULL, filename, "", MB_OK);

			if (stylesheet->load((new System::StringA(string_copy(filename)))->ToStringW()))
#else
			if (stylesheet->load("WinHD_C:/Documents and Settings/All Users/Application Data/LXFramework/html.css"))
#endif
			{
				get_styleSheets()->append(stylesheet);
			}
		}
	}
}

}	// Web
}

#endif