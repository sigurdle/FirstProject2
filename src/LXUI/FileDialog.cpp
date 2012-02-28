#include "stdafx.h"
#include "LXUI2.h"
#include "FileDialog.h"

#if WIN32

/*
#define Array var
#include <windows.h>
#include <psapi.h>
#undef Array
#endif
*/

#include "../include/windows_header.h"

namespace System
{
namespace MSWindows
{

extern "C"
{

#define WINCOMMDLGAPI DECLSPEC_IMPORT

WINCOMMDLGAPI BOOL APIENTRY GetOpenFileNameA(LPOPENFILENAMEA);
WINCOMMDLGAPI BOOL APIENTRY GetOpenFileNameW(LPOPENFILENAMEW);

}	// extern "C"
}
}

#endif

#if __APPLE__
#define LDraw carbonLDraw
#include <Carbon/Carbon.h>
#undef LDraw
#endif

#if AMIGA

#include "../amiga_header.h"

#endif

namespace System
{

FileDialog::FileDialog(bool bOpen)
{
#if WIN32

	m_szFileName[0] = 0;

	std::memset(&m_ofn, 0, sizeof(m_ofn));
	m_ofn.lStructSize = sizeof(m_ofn);
	m_ofn.hInstance = _Module.GetModuleInstance();
	m_ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING;
	m_ofn.lpstrFile = m_szFileName;
	m_ofn.nMaxFile = sizeof(m_szFileName);

#endif
}

int FileDialog::DoModal(UI::UIElement* owner)
{
#if WIN32

	m_ofn.hwndOwner = dynamic_cast<UI::HwndSource*>(owner->GetOwnerWindow()->m_pSite)->m_hWnd;

	MSWindows::BOOL bRet = MSWindows::GetOpenFileNameA(&m_ofn);
	if (bRet)
	{
		m_files.push_back(new StringA(string_copy(m_szFileName)));
		return IDOK;
	}
	else
		return IDCANCEL;

#elif AMIGA

	int ret;

	FileRequester* fr = (FileRequester*)AllocAslRequestTags(ASL_FileRequest,
		(ASLFR_TitleText), (ULONG)"Open",
		(ASLFR_DoMultiSelect), TRUE,
		(TAG_DONE));
	if (fr)
	{
		if (AslRequestTags(fr, TAG_DONE))
		{
			char pathname[1024];

			for (int i = 0; i < fr->fr_NumArgs; i++)
			{
				NameFromLock(fr->fr_ArgList[i].wa_Lock, pathname, 1024);
				AddPart(pathname, (STRPTR)fr->fr_ArgList[i].wa_Name, 1024);

				m_files.push_back(new StringA(pathname));
			}

			//delete[] pathname;

			ret = IDOK;
		}
		else
			ret = IDCANCEL;

		FreeAslRequest(fr);
	}
	else
		ret = IDABORT;

	return ret;

#elif __APPLE__

	OSStatus status;
	NavDialogCreationOptions myDialogOptions;
	status = NavGetDefaultDialogCreationOptions(&myDialogOptions);
	printf("%d\n", status);

	NavDialogRef dialogRef;
	if (true)	// multiple files
		status = NavCreateGetFileDialog(&myDialogOptions, NULL, NULL, NULL, NULL, NULL, &dialogRef);
	else
		;//NavCreateChooseFileDialog

	printf("%d\n", status);

	status = NavDialogRun(dialogRef);
	//printf("%d\n", status);

	int ret;

	switch (NavDialogGetUserAction(dialogRef))
	{
	case kNavUserActionOpen:
		{
		//	printf("Open\n");

			NavReplyRecord reply;
			NavDialogGetReply(dialogRef, &reply);

			long count;
			AECountItems(&reply.selection, &count);
		//	printf("filecount: %d\n", count);
		//	fflush(stdout);

			for (int i = 0; i < count; i++)
			{
				AEDesc desc;
				AEKeyword keyword;
				OSErr err = AEGetNthDesc(&reply.selection, i+1, typeFSRef, &keyword, &desc);

			//	printf("AEGetNthDesc = %d\n", err);
			//	fflush(stdout);

				FSRef fsRef;
				AEGetDescData(&desc, &fsRef, sizeof(fsRef));

				char filename[1024];
				FSRefMakePath(&fsRef, (UInt8*)filename, 1024);

			//	printf("%s\n", filename);
			//	fflush(stdout);

				AEDisposeDesc(&desc);

				m_files.push_back(filename);
			}

			NavDisposeReply(&reply);

			ret = IDOK;
		}
		break;

	default:
		ret = IDABORT;
	}

	NavDialogDispose(dialogRef);

	//fflush(stdout);

	return ret;

#else

#error "Unknown OS"

#endif
}

}
