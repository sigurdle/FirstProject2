#include "stdafx.h"

#include "LXML2.h"

#include <functional>

//#include "../include/windows_header.h"

extern DECLSPEC_DLLIMPORT long g_locked;
extern DECLSPEC_DLLIMPORT long g_locked2;

//static Task* m_parentTask;
//static long m_parentSigBit;

//#include "../Draw/Drawing.h"
//#include "../Draw/TTFont.h"

#include "Window.h"
#include "MouseEvent.h"
#include "XMLParser.h"
#include "PTextNode.h"
#include "PWord.h"
#include "CSSStackingContext.h"
#include "PBlockBox.h"
#include "HTMContext.h"

using namespace System;

#if 0
class _FontFamily2 //: public _ObjectImpl
{
public:
//	_FontFamily();
	_FontFamily2(const sysstring& name, FontFamilyCollection* pFontFamilyCollection)
	{
		ASSERT(name.Length() != 0);
		if (name.Length() == 0) THROW(-1);

		m_name = name;

		m_pFamily = pFontFamilyCollection->Find(name);
	}

	/*
	ULONG AddRef()
	{
		m_refcount++;
		return m_refcount;
	}

	ULONG Release()
	{
		m_refcount--;
		if (m_refcount == 0)
		{
			delete this;
			return 0;
		}
		return m_refcount;
	}
	*/

	sysstring m_name;
	Family* m_pFamily;
	//ULONG m_refcount;
};
#endif

namespace System
{
namespace Web
{

class DownloadDocument;


int filecount = 0;

String Navigator::s_userAgent = "Navigator Name TODO";


/*
class DocumentWindow : public Control, public IPersist
{
public:
	Load();
};
*/

//////////////////////////////////////////////////
//////////////////////////////////////////////////

#if 0//_DEBUG
void DebugOutputTypeInfo(IDispatch* pDisp)
{
	ITypeInfo* pTInfo;
	ErrorCode hr = pDisp->GetTypeInfo(0, NULL, &pTInfo);

	TYPEATTR* pType;
	pTInfo->GetTypeAttr(&pType);

	for (int i = 0; i < pType->cFuncs; i++)
	{
		FUNCDESC* pFuncDesc = NULL;
		if (SUCCEEDED(pTInfo->GetFuncDesc(i, &pFuncDesc)))
		{
			BSTR bname;
			UINT pcNames;
			pTInfo->GetNames(pFuncDesc->memid, &bname, 1, &pcNames);
			_bstr_t name = _bstr_t(bname, FALSE);

			ATLTRACE("name(%d): %S\n", pFuncDesc->memid, (BSTR)name);

			pTInfo->ReleaseFuncDesc(pFuncDesc);
		}
	}

	pTInfo->Release();
}
#endif

#if 0
void PrintoutEvents(IUnknown* unk)
{
	TRACE("\nEvents:\n");

	CComQIPtr<IConnectionPointContainer> connectionPtContainer = unk;
	if (connectionPtContainer)
	{
		CArray<IConnectionPoint*,IConnectionPoint*> connectionPoints;

		CComQIPtr<IEnumConnectionPoints> enumcpts;
		connectionPtContainer->EnumConnectionPoints(&enumcpts);
		if (enumcpts)
		{
		// Retrieve all connection points of object
			while (1)
			{
				IConnectionPoint* connectionpt;
				ULONG retrieved;

				enumcpts->Next(1, &connectionpt, &retrieved);
				if (retrieved == 0) break;

				connectionPoints.Add(connectionpt);
			}
		}

		CComQIPtr<IProvideClassInfo2> classinfo = unk;

		if (classinfo)
		{
			//classinfo->GetGUID(GUIDKIND_DEFAULT_SOURCE_DISP_IID
			ITypeInfo* pTInfo;
			ErrorCode hr = classinfo->GetClassInfo(&pTInfo);

		// Needed to retrieve custom properties
			ITypeInfo2* pTInfo2;
			pTInfo->QueryInterface(IID_ITypeInfo2, (void**)&pTInfo2);
			if (pTInfo2) pTInfo2->Release();

			TYPEATTR* pType;
			pTInfo->GetTypeAttr(&pType);

			for (int i = 0; i < pType->cImplTypes; i++)
			{
				HREFTYPE pRefType = NULL;
				if (SUCCEEDED(pTInfo->GetRefTypeOfImplType(i, &pRefType)))
				{
					ITypeInfo* pTIInfo;
					pTInfo->GetRefTypeInfo(pRefType, &pTIInfo);

					TYPEATTR* pType;
					pTIInfo->GetTypeAttr(&pType);

					IConnectionPoint* connpt;
					connectionPtContainer->FindConnectionPoint(pType->guid, &connpt);
					if (connpt)
					{
					//	IID iid;
					//	connectionPoints[i]->GetConnectionInterface(&iid);


						/*
						CActiveXDispEvent* dispevent = new CActiveXDispEvent;
						dispevent->m_iid = pType->guid;
						connectionPoints[i]->Advise(dispevent, &dispevent->m_dwCookie);
						m_pComObject->m_dispEvents.Add(dispevent);
						*/

						for (int i = 0; i < pType->cFuncs; i++)
						{
							FUNCDESC* pFuncDesc = NULL;
							if (SUCCEEDED(pTIInfo->GetFuncDesc(i, &pFuncDesc)))
							{
								BSTR bname;
								UINT pcNames;
								pTIInfo->GetNames(pFuncDesc->memid, &bname, 1, &pcNames);

								TRACE("eventname: %S\n", bname);

								pTInfo->ReleaseFuncDesc(pFuncDesc);
							}
						}
					}

					pTIInfo->Release();
				}
			}

			pTInfo->Release();
		}
	}

	TRACE("\n");
}
#endif

#if 0
void PrintoutImpls(IDispatch* pDisp)
{
	TRACE("\nEvents:\n");

//	CComQIPtr<IProvideClassInfo2> classinfo = unk;

//	if (classinfo)
	{
		ITypeInfo* pTInfo;
		ErrorCode hr = pDisp->GetTypeInfo(0, NULL, &pTInfo);

		TYPEATTR* pType;
		pTInfo->GetTypeAttr(&pType);

		for (int i = 0; i < pType->cImplTypes; i++)
		{
			HREFTYPE pRefType = NULL;
			if (SUCCEEDED(pTInfo->GetRefTypeOfImplType(i, &pRefType)))
			{
				ITypeInfo* pTIInfo;
				pTInfo->GetRefTypeInfo(pRefType, &pTIInfo);

				TYPEATTR* pType;
				pTIInfo->GetTypeAttr(&pType);

				{
				//	IID iid;
				//	connectionPoints[i]->GetConnectionInterface(&iid);


					/*
					CActiveXDispEvent* dispevent = new CActiveXDispEvent;
					dispevent->m_iid = pType->guid;
					connectionPoints[i]->Advise(dispevent, &dispevent->m_dwCookie);
					m_pComObject->m_dispEvents.Add(dispevent);
					*/

					for (int i = 0; i < pType->cFuncs; i++)
					{
						FUNCDESC* pFuncDesc = NULL;
						if (SUCCEEDED(pTIInfo->GetFuncDesc(i, &pFuncDesc)))
						{
							BSTR bname;
							UINT pcNames;
							pTIInfo->GetNames(pFuncDesc->memid, &bname, 1, &pcNames);

							TRACE("eventname: %S\n", bname);

							pTInfo->ReleaseFuncDesc(pFuncDesc);
						}
					}
				}

				pTIInfo->Release();
			}
		}

		pTInfo->Release();
	}

	TRACE("\n");
}
#endif


DWORD WINAPI LayoutThreadProc(void* lpData)
{
	ASSERT(0);

#if 0
	__live_object_ptr<CHTMLWindow> pWindow = (CHTMLWindow*)lpData;


#if WIN32
	MSWindows::SetEvent(((CHTMLWindow*)lpData)->m_hLayoutBeginEvent);
#endif

#if AMIGA
	pWindow->m_layoutSigBit = AllocSignal(-1);
	ASSERT(pWindow->m_layoutSigBit != -1);

	Signal(pWindow->m_parentTask, 1<<pWindow->m_parentSigBit);
#endif

	while (1)
	{
#if WIN32
		MSWindows::WaitForSingleObject(pWindow->m_hLayoutEvent, INFINITE);
#else
		execWait(*(struct ExecBase**)4, 1<<pWindow->m_layoutSigBit);
#endif

		MSWindows::InterlockedIncrement(&g_locked);	// gc woun't happen
		while (g_locked2) MSWindows::Sleep(1);	// Wait until any gc is done

#if 1
		if (pWindow->GetOwnerWindow() && pWindow->m_htmTree)
		{
			TRACE("Layout...");

			//MessageBeep(-1);

			pWindow->m_htmTree->GetCSSPropertiesAndChildren();
			pWindow->m_htmTree->CalculateBoundsAndChildren();
			pWindow->OnSize();

			LDraw::Commands* drawCommands = new LDraw::Commands;
			UI::Graphics* graphics = new UI::Graphics(new LDraw::GraphicsMetafile(drawCommands));
			
#if 0
			pWindow->OpenDrawingContext();
#endif
			//graphics->PushTransform();

			((LDraw::GraphicsMetafile*)graphics->m_p)->m_transform = pWindow->GetWindowToElementTransformMatrix();

			pWindow->OnRenderMy(graphics);

			//graphics->PopTransform();

			pWindow->m_DrawCommands = drawCommands;
			pWindow->InvalidateRender();
#if 0
			pWindow->CloseDrawingContext(graphics);
#endif

#if 0	// Done in CloseDrawingContext
			dynamic_cast<UI::UIElement*>(pWindow->GetRParent())->InvalidateRender();
#endif
			//((CHTMLWindow*)lpData)->RenderChanged();

			/*
		//	if (msg.lParam)
			{
				((CHTMLWindow*)lpData)->Invalidate();
			}
			*/

		//	((CHTMLWindow*)lpData)->m_crit.Unlock();
			TRACE("Done layout\n");
		}
#endif
#if WIN32
		MSWindows::SetEvent(pWindow->m_hLayoutDoneEvent);
#endif

	/*
		if (!((CHTMLWindow*)lpData)->m_bLayoutComplete)
		{
			PostMessage(((CHTMLWindow*)lpData)->m_layoutMessageSink.m_hWnd, WM_USER+100, 0, 0);
		}
		*/
		MSWindows::InterlockedDecrement(&g_locked);
	}
#endif
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
// CHTMLWindow

CHTMLWindow::CHTMLWindow()// : DispatcherObject//(get_Class())
{
	m_nbytes = 0;

//	m_bLayoutComplete = false;

//	m_crit.Init();

//	LDraw::Font* pFont = new LDraw::Font(OLESTR("Times New Roman"), 14);	// TODO remove

#if WIN32

	m_dwLayoutThreadId = 0;
	m_hLayoutThread = INVALID_HANDLE_VALUE;

	if (false)
	{
		m_hLayoutEvent = CreateEvent(NULL, false, false, NULL);
		m_hLayoutBeginEvent = CreateEvent(NULL, false, false, NULL);
		m_hLayoutDoneEvent = CreateEvent(NULL, false, false, NULL);

		m_hLayoutThread = ::CreateThread(NULL, 0, LayoutThreadProc, (void*)this, 0, &m_dwLayoutThreadId);
//	SetThreadPriority(m_hLayoutThread, THREAD_PRIORITY_ABOVE_NORMAL);
//	SetThreadPriority(m_hLayoutThread, THREAD_PRIORITY_BELOW_NORMAL);
//	SetThreadPriority(m_hLayoutThread, THREAD_PRIORITY_LOWEST);
		WaitForSingleObject(m_hLayoutBeginEvent, INFINITE);
	}
#else
	m_hLayoutThread = NULL;
	m_layoutSigBit = -1;
	m_parentTask = FindTask(NULL);
	m_parentSigBit = AllocSignal(-1);
	ASSERT(m_parentSigBit != -1);

	/*
	m_hLayoutThread = (struct Task*)CreateNewProcTags(
		(NP_Entry), (ULONG)LayoutThreadProc,//(ULONG)ThreadEntryPoint,
	//	(NP_Arguments), (ULONG)"Hello there",
	//	(NP_Output), dosOpen(DOSBase, "CON:", MODE_NEWFILE),
		(NP_StackSize), 900000,
		(TAG_END));
		*/

	//Signal(/*((CHTMLWindow*)lpData)->*/::m_parentTask, 1<</*((CHTMLWindow*)lpData)->*/m_parentSigBit);
//	SetSignal(1<<::m_parentSigBit, 1<<::m_parentSigBit);

#if 1
	m_hLayoutThread = (struct Task*)CreateThread(LayoutThreadProc, (void*)this);
	execWait(*(ExecBase**)4, 1<<m_parentSigBit);
#endif
	// TODO, free signal
#endif

	m_bAlt = false;

//	m_lockPaint = 0;

	m_magnify = 1;
	m_currentTranslateX = 0;
	m_currentTranslateY = 0;

//	m_scrollX = NULL;
//	m_scrollY = NULL;
	m_noscroll = false;

//	m_bShowCursor = FALSE;
	m_bShowCursor = true;	// Fix, should blink with a timer

	m_htmTree = NULL;

#if 0
	m_pHTMElement = NULL;
	m_pSVGElement = NULL;
	m_pSMILElement = NULL;
	m_pSMILLayoutElement = NULL;

	m_pFODisplay = NULL;
#endif
//	m_pSMILDisplay = NULL;
//	m_pSVGDisplay = NULL;

	m_pC = NULL;

	m_bShowMarkup = false;

	m_hBrokenImage = NULL;
	/*
	m_lpBmi = NULL;
	m_hBitmap = NULL;
	m_bmBits = NULL;
	*/

#if 0
	m_pFrameSet = NULL;
#endif

#if 0
	m_pOCItemCapture = NULL;
#endif
	m_pElementCapture = NULL;

	m_pHitElement = NULL;
	m_pPElementHover = NULL;
	m_pPElementActive = NULL;
	m_pPElementFocus = NULL;
/*
	CComQIPtr<IActiveScriptSite> site;
	m_scriptSite->QueryInterface(IID_IActiveScriptSite, (void**)&site);
	m_activeScript->SetScriptSite(site);
*/

/*
	m_pVideo = NULL;
	m_frameptr = NULL;
	m_seqdata = NULL;
*/

#if 0
	m_pContainer = new CActiveXContainer;
#endif

/// TODO remove
	m_cursorItem = NULL;
	m_cursorOffset = 0;

	m_dragOverItem = 0;
	m_dragOverOffset = 0;

	m_startSelItem = NULL;
	m_startSelOffset = 0;

	m_endSelItem = NULL;
	m_endSelOffset = 0;
///

	m_curContainer = NULL;
	m_curOffset = -1;
	m_initContainer = NULL;
	m_initOffset = -1;

	m_pSite = NULL;

	m_dragging = 0;

//	m_currentHistory = 0;

#if 0
	m_pHTMLWindowImpl = NULL;
	m_pHTMLDialogImpl = NULL;
#endif

	//crit2.Lock();
	//LDraw::Font font(OLESTR("Arial"), 14/*, LDraw::FontStyleRegular, LDraw::UnitPoint*/);

#if 0
	{
		char* directoryName = "WinHD_C:WINDOWS/FONTS";

		struct FileInfoBlock* fib = (struct FileInfoBlock*)AllocDosObject(DOS_FIB, NULL);
		BPTR lock;

		if (fib != NULL)
		{
			lock = dosLock(DOSBase, const_cast<char*>(directoryName), ACCESS_READ);
			if (lock != NULL)
			{
				Examine(lock, fib);

				char* fullpath = new char[1024];

				while (ExNext(lock, fib) != 0)
				{
					if (fib->fib_DirEntryType > 0)	// directory
					{
						// Maybe recurse ???
					}
					else
					{
						int len = strlen(fib->fib_FileName);
						if (len >= 4 && !stricmp(fib->fib_FileName+len-4, ".ttf"))
						{
							strcpy(fullpath, directoryName);
							AddPart(fullpath, fib->fib_FileName, 1024);

							StringA str = fullpath;

						//	FPrintf(Output(), "%s\n", (long)fullpath);
						//	Delay(50*1);

							ISequentialByteStream* fp = new FileByteStream(fullpath);
							fp->AddRef();

							LType::FontFile* pTTFile = NULL;
							pTTFile = new LType::FontFile();
							pTTFile->Init(fp);

							/*
							struct DosLibrary* m_DOSBase = (struct DosLibrary*)execOpenLibrary(*(ExecBase**)4, "dos.library", 36);
							ASSERT(m_DOSBase != NULL);

							BPTR fp = dosOpen(m_DOSBase, str.c_str(), MODE_OLDFILE);
							if (fp)
							{
								dosClose(m_DOSBase, fp);
							}

							execCloseLibrary(*(ExecBase**)4, (struct Library*)m_DOSBase);
							*/

							fp->Release();

						//	printf("%s\n", fullpath);

					//		AddFile(fullpath);
						}
					}
				}

				delete[] fullpath;

				if (IoErr() != ERROR_NO_MORE_ENTRIES)
				{
					//MessageBox(NULL, "dos Error", "", MB_OK);
				}
				dosUnLock(DOSBase, lock);
			}

			FreeDosObject(DOS_FIB, fib);
		}
	}
#endif

#if 0
	m_pMarkupFont = new LDraw::Font(WSTR("Arial"), 14/*, LDraw::FontStyleRegular, LDraw::UnitPoint*/);
#endif

	m_range = NULL;
}

CHTMLWindow::~CHTMLWindow()
{
//	ASSERT(m_fontDataFiles.GetSize() == 0); TODO have this

	/*
	if (m_pMarkupFont)
	{
		delete m_pMarkupFont;
	}
	*/
}

#if 0
int CHTMLWindow::FinalConstruct()
{
	ErrorCode hr;

#if 0
// I Initialize LDraw here, the assumtion is that LDraw is never used outside a CHTMLWindow
	if (LDrawToken == NULL)
	{
		if (LDraw::LDrawStartup(&LDrawToken, &LDrawStartupInput, NULL) != LDraw::Ok)
		{
			return E_FAIL;
		}
	}
#endif

	m_pMatrix = new CLSVGMatrix;

//	m_eventObj = NULL;
	//m_pScriptDisp = NULL;

#if 0
	m_lpbmi = (LPBITMAPINFO)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));
	if (m_lpbmi == NULL)
		return E_OUTOFMEMORY;
#endif

#if 0	// TODO hm ??
	CComObject<CLHTMLWindow>::CreateInstance(&m_pHTMLWindowImpl);
	m_pHTMLWindowImpl->m_pFrame = this;
#endif

#if 0
	CComObject<CLHTMLDialog>::CreateInstance(&m_pHTMLDialogImpl);
	m_pHTMLDialogImpl->m_pFrame = this;
#endif

	return 0;
}
#endif

bool BarProp::get_visible()
{
	return true;
}

void BarProp::set_visible(bool value)
{
}

BarProp* CHTMLWindow::get_locationbar()
{
	return NULL;
}

BarProp* CHTMLWindow::get_personalbar()
{
	return NULL;
}

BarProp* CHTMLWindow::get_menubar()
{
	return NULL;
}

BarProp* CHTMLWindow::get_statusbar()
{
	return NULL;
}

BarProp* CHTMLWindow::get_toolbar()
{
	return NULL;
}

BarProp* CHTMLWindow::get_scrollbars()
{
	return NULL;
}

#if 0
void CHTMLWindow::FinalRelease()
{
	TRACE("CHTMLWindow::FinalRelease()\n");

	m_pMatrix->Release();
	m_pMatrix = NULL;
}
#endif

void CHTMLWindow::Free()
{
	m_pPElementActive = NULL;
	m_pPElementFocus = NULL;
	m_pPElementHover = NULL;
	m_curContainer = NULL;
	m_initContainer = NULL;

#if 0
	if (m_element)
	{
	//	CComQIPtr<INotifySend> cp = m_element;	// TODO, try m_element instead to see if that works
//		CComQIPtr<INotifySend> cp = m_document;	// TODO, try m_element instead to see if that works
//		ASSERT(cp);
//		cp->Unadvise(this);
		m_element.Release();
	}
#endif

#if 0
	if (m_scrollY)
	{
		ErrorCode hr = IDispEventImpl<2, CHTMLWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_scrollY->m_spUnknown);
		ASSERT(SUCCEEDED(hr));
		m_scrollY->ReleaseAll();
		m_scrollY->Release();
		m_scrollY = NULL;
	}

	if (m_scrollX)
	{
		ErrorCode hr = IDispEventImpl<3, CHTMLWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_scrollX->m_spUnknown);
		ASSERT(SUCCEEDED(hr));
		m_scrollX->ReleaseAll();
		m_scrollX->Release();
		m_scrollX = NULL;
	}
#endif

#if 0
	if (m_range)
	{
#if 0
		CComQIPtr<INotifySend> cp = m_range;
//		DWORD cookie;
		cp->Unadvise(this);
		m_range.Release();
#endif
	}
#endif

#if 0	// Had this ???
	if (m_pFrameSet)	// ???
	{
		m_pFrameSet->Release();
		m_pFrameSet = NULL;
	}
#endif

	if (m_htmTree)	// TODO, rename m_htmTree to something else
	{
	//	CComObject<CPHTMElement>* pTree = m_htmTree;
	//	ILViewNode* pTree = m_htmTree;
		m_htmTree = NULL;
	//	int refcount = pTree->Release();

	//	m_pHTMElement = NULL;
	//	m_pSVGElement = NULL;
	}

#if 0
	if (m_pFODisplay)
	{
//		delete m_pFODisplay;
		m_pFODisplay = NULL;
	}
#endif

	/*
	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
		m_bmBits = NULL;
	}

	if (m_lpBmi)
	{
		GlobalFree(m_lpBmi);
		m_lpBmi = NULL;
	}
	*/

#if 0
	if (m_pView)
	{
		//... TODO (Detach from cssview)
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////

double CHTMLWindow::GetFinalMagnify()
{
	return m_magnify;
}

#if 0
void __stdcall CHTMLWindow::OnHorzScroll(long code, long pos)
{
	setCurrentTranslate(-pos, m_currentTranslateY);
}

void __stdcall CHTMLWindow::OnVertScroll(long code, long pos)
{
	setCurrentTranslate(m_currentTranslateX, -pos);
}
#endif

void CHTMLWindow::Flow()
{
//	m_lockPaint++;
//	ASSERT(m_lockPaint == 1);

	ASSERT(0);
#if 0

	double cx = m_computedSize.Width;
	double cy = m_computedSize.Height;

	if (m_pC == NULL)
	{
		m_pC = new CHTMFlowBlockContext;
	}
//	pC.m_frameClient = m_client;

#if 0
	if (m_pSMILElement)	// Necessary, so the other code doesn't run
	{
		// TODO ??
	}
	else
#endif
		if (m_htmTree)
	{
#if 0
		m_htmTree->RemoveBoxesAndChildren();
		if (m_htmTree->m_pBox)
		{
			CHTMBlockBox* pBox = m_htmTree->m_pBox;
			m_htmTree->m_pBox = NULL;
			//delete pBox;
			pBox->Release();
		}
#endif
	}

	if (cx > 0 && cy > 0)
	{
#if 0
		if (m_pSMILElement)	// TODO ???
		{
		}
		else
#endif
			if (m_htmTree)
		{
		//	ASSERT(pElement->m_pLocalStackingContext->m_boxList.GetSize() == 0);

		//	m_htmTree->m_computedWidth = /*pElement->m_computedWidth =*/ cx;
			m_htmTree->m_computedHeight = /*pElement->m_computedHeight =*/ cy;
			//m_htmTree->m_computedOverflowX = m_htmTree->m_computedOverflowY = Overflow_scroll;
#if 0
			m_htmTree->m_computedDisplay = Display_block;	// ??
#endif
			m_htmTree->m_computedDisplayModel = DisplayModel_block_inside;

			m_htmTree->m_bVScroll = true;	// Always vertical scrollbar on outer element (TODO unless specified)

			/*
			pC.m_pBlockBox = NULL;
			pC.m_pCurLineBox = NULL;
			pC.m_pPrevLeftFloatBox = NULL;

			pC.m_floatBottom = 0;
			pC.m_curpos.X = pC.m_curpos.Y = 0;
			pC.m_linepos.X = pC.m_linepos.Y = 0;
			pC.m_maxx = 0;
			*/

		//	MessageBeep(-1);
#if 1//WIN32	// TODO, always
			m_htmTree->DistributeWithinBlock(m_pC, m_htmTree/*nearestPositioned*/, m_htmTree/*stackingContext*/, cx);
#endif

#if 0//WIN32
			m_htmTree->PlaceControls(NULL, m_pC);
#endif

		}
#if 0
		else if (m_pFODisplay)
		{
		//	m_pFODisplay->m_pages[0]->m_pElement->m_desiredWidth = cx;//client.right;

#if 0
			m_pFODisplay->m_pages[0]->m_pElement->m_width = m_pFODisplay->m_pages[0]->m_width;
			m_pFODisplay->m_pages[0]->m_pElement->m_height = m_pFODisplay->m_pages[0]->m_height;
#endif

			//m_pFODisplay->m_pages[0]->m_pElement->CalculateDimensions(&pC);

			pC.m_pBlockBox = NULL;
			pC.m_pCurLineBox = NULL;
			pC.m_pPrevLeftFloatBox = NULL;

			pC.m_floatBottom = 0;
			pC.m_curpos.X = pC.m_curpos.Y = 0;
			pC.m_linepos.X = pC.m_linepos.Y = 0;
			pC.m_maxx = 0;

			//m_pFODisplay->m_pages[0]->m_pElement->m_desiredWidth = cx;//client.right;
			m_pFODisplay->m_pages[0]->m_pElement->DistributeWithinBlock(&pC, cx);
		//	ASSERT(m_pFODisplay->m_pages[0]->m_pElement->m_pBox != NULL);

			m_pFODisplay->m_pages[0]->m_pElement->PlaceControls(NULL, &pC);
		}
#endif
	}

//	m_lockPaint--;
#endif
}

gm::SizeD CHTMLWindow::ArrangeOverride(gm::SizeD finalSize)
{
	list<PElementBase*>::iterator it = m_recalcBoundsList.begin();
	while (it != m_recalcBoundsList.end())
	{
		PElementBase* pElement = *it;
		++it;

		pElement->CalculateBoundsAndChildren();
	}

	m_recalcBoundsList.clear();

	/*
	TRACE("OnArrange\n");
	if (m_htmTree)
	{
	//	MessageBeep(-1);
		m_htmTree->GetCSSPropertiesAndChildren();
		m_htmTree->CalculateBoundsAndChildren();
		OnSize();
	}
	return;
	*/
	/*
	if (m_dwLayoutThreadId)
	{
		PostThreadMessage(m_dwLayoutThreadId, WM_QUIT, 0, 0);
		WaitForSingleObject(m_hLayoutThread, INFINITE);
		m_dwLayoutThreadId = 0;
	}
	*/
#if 0
#if WIN32
//	m_bLayoutComplete = false;
	//PostMessage(m_layoutMessageSink.m_hWnd, WM_USER+100, 0, 0);
	if (false)
	{
		SetEvent(m_hLayoutEvent);
//	WaitForSingleObject(m_hLayoutDoneEvent, INFINITE);

	/*
	if (m_htmTree->m_pBox == NULL)
	{
		m_htmTree->m_pBox = m_htmTree->CreateBlockBox();
		m_htmTree->m_pBox->m_innerRect.Width = m_computedSize.Width-16;
		m_htmTree->m_pBox->m_outerRect.Width = m_computedSize.Width-16;
	}
	*/

//	PostMessage(m_layoutMessageSink.m_hWnd, WM_USER+100, 0, 0);
	}
	else
	{
		if (m_htmTree)
		{
			m_htmTree->GetCSSPropertiesAndChildren();
			m_htmTree->CalculateBoundsAndChildren();
			OnSize();

		//	OnRenderMy(pGraphics);
		}
	}
#else

	/*
	m_htmTree->GetCSSPropertiesAndChildren();
	m_htmTree->CalculateBoundsAndChildren();
	OnSize();
	*/

//	if (m_hLayoutThread && m_layoutSigBit != -1)
	{
		Signal(m_hLayoutThread, 1<<m_layoutSigBit);
	}

#endif
#endif
	//Sleep(10);
	//SetEvent(m_hLayoutEvent);

	return finalSize;
}

void CHTMLWindow::OnSize()
{
//	m_crit.Lock();
	/*
	int cx = m_client.Width;
	int cy = m_client.Height;
	*/

	/*
	m_imageRect.left = 0;
	m_imageRect.top = 0;
	m_imageRect.right = cx;
	m_imageRect.bottom = cy;
	*/

	int sbWidth = 0;
	int sbHeight = 0;

	//ASSERT(0);
#if 0	// I Had this
	if (m_pUI)
	{
		if (!m_noscroll)
		{
			if (m_pUI->m_hWnd)	// ??
			{
				if (m_scrollX) sbHeight = 16;
				if (m_scrollY) sbWidth = 16;
			}
		}
	}
#endif

//	m_imageRect.right -= sbWidth;
//	m_imageRect.bottom -= sbHeight;

	if (m_htmTree/* || m_pFODisplay*/)
	{
		/*
		try
		*/
		{
		//	m_bLayoutComplete = true;
			Flow();
		//	Invalidate();
			//MessageBeep(-1);
		}
		/*
		catch(int)
		{
			MSG msg;
			ASSERT(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE));
			;//PostMessage(this->m_layoutMessageSink.m_hWnd, WM_USER+100, 0, 0);
		}
		*/
	}

#if 0	// Had this
	// Set scrollbar sizes
	{
		double magnify = GetFinalMagnify();

		double minx = (-600)*magnify;
		double miny = (-600)*magnify;
		double maxx = (GetSVGWidth()+600)*magnify;
		double maxy = (GetSVGHeight()+600)*magnify;

		if (m_scrollX)
		{
			//sbHeight = 16;
			CRect rcPos = CRect(m_client.left, m_client.top+cy-sbHeight, m_client.left+cx-sbWidth, m_client.top+cy);
			m_scrollX->OnSize(rcPos, rcPos);

			CComQIPtr<IUIScrollBar> scroll = m_scrollX->m_spUnknown;

			double width = maxx-minx;

			if (m_imageRect.Width() > width)
			{
				scroll->SetInfo(
					(minx -(m_imageRect.Width()-width)/2),
					(minx -(m_imageRect.Width()-width)/2),
					m_imageRect.Width());
			}
			else
			{
				scroll->SetInfo(minx, maxx, m_imageRect.Width());
			}
		}

		if (m_scrollY)
		{
			CRect rcPos = CRect(m_client.left + cx-sbWidth, m_client.top, m_client.left + cx, m_client.top + cy-sbHeight);
			m_scrollY->OnSize(rcPos, rcPos);

			CComQIPtr<IUIScrollBar> scroll = m_scrollY->m_spUnknown;

			double height = maxy-miny;

			if (m_imageRect.Height() > height)
			{
				scroll->SetInfo(
					(miny -(m_imageRect.Height()-height)/2),
					(miny -(m_imageRect.Height()-height)/2),
					m_imageRect.Height());
			}
			else
			{
				scroll->SetInfo(miny, maxy, m_imageRect.Height());
			}
		}
	}

	/*
		if (m_bShowRulers)
		{
			m_imageRect.left += 16;
			m_imageRect.top += 16;
		}
	*/
	<ILDOMDocument> document = m_pView->m_document;
		//m_frameElement->get_contentDocument(&document);

	Fire_onresize();
#endif
//	m_crit.Unlock();
}

#if 0
void CHTMLWindow::SetCapture()
{
	ASSERT(0);
#if 0	// Have this ??
	if (m_pUI)
	{
		m_pUI->SetCapture();
	}
	else
	{
		m_pActiveDocument->m_spInPlaceSite->SetCapture(TRUE);
	}
#endif
}


void CHTMLWindow::ReleaseCapture()
{
	ASSERT(0);
#if 0	// Have this
	if (m_pUI)
	{
		::ReleaseCapture();
	}
	else
	{
		m_pActiveDocument->m_spInPlaceSite->SetCapture(FALSE);
	}
#endif
}

void CHTMLWindow::InvalidateRect(LPCRECT lprect)
{
	ASSERT(0);
#if 0	// I had this
	if (m_pUI)
	{
		if (m_pUI->m_hWnd)
		{
			m_pUI->InvalidateRect(lprect);
		}
	}
	else
	{
		if (m_pActiveDocument)	// TODO, should be one or the other
		{
			if (m_pActiveDocument->m_spInPlaceSite)
			{
				m_pActiveDocument->m_spInPlaceSite->InvalidateRect(lprect, TRUE);
			}
		}
	}
#endif
}
#endif

#if 0
void CHTMLWindow::RemovingElement(CPElement* pPElement)
{
	pPElement->RemovedFromDocument();

	if (pPElement == m_pPElementHover)
	{
		m_pPElementHover = NULL;
	}

	UPOSITION pos = pPElement->m_childList.GetHeadPosition();
	while (pos)
	{
		CPElement* p = (CPElement*)pPElement->m_childList.GetNext(pos);
		if (p->m_type == LNODE_ELEMENT)
		{
			RemovingElement(p);
		}
	}
}
#endif

#if 0
// INotifyGet
// TODO remove??
STDMETHODIMP CHTMLWindow::OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
{
	ASSERT(0);
	return Success;
}
#endif

//

#if 0

double CHTMLWindow::GetSVGWidth()
{
#if 0
	if (m_pSVGElement)
	{
		ASSERT(0);
#if 0
		return m_pSVGElement->m_bounds.Width;
#endif
	}
#endif
	/*
	CComQIPtr<ILSVGDocument> svgdoc = m_document;
	if (svgdoc)
	{
		<ILDOMElement> documentElement;
		svgdoc->get_documentElement(&documentElement);

		CComQIPtr<ILSVGSVGElement> svg = documentElement;

		if (svg)
		{
			CComQIPtr<ILSVGAnimatedLength> width;
			svg->get_width(&width);

			CComQIPtr<ILSVGLength> animVal;
			width->get_animVal(&animVal);

			double value;
			animVal->get_value(&value);

			return value;
		}
	}
*/
	return 0;
}

double CHTMLWindow::GetSVGHeight()
{
	if (m_pSVGElement)
	{
		ASSERT(0);
#if 0
		return m_pSVGElement->m_bounds.Height;
#endif
	}

/*
	CComQIPtr<ILSVGDocument> svgdoc = m_document;
	if (svgdoc)
	{
		<ILDOMElement> documentElement;
		svgdoc->get_documentElement(&documentElement);

		CComQIPtr<ILSVGSVGElement> svg = documentElement;
		if (svg)
		{
			CComQIPtr<ILSVGAnimatedLength> height;
			svg->get_height(&height);

			CComQIPtr<ILSVGLength> animVal;
			height->get_animVal(&animVal);

			double value;
			animVal->get_value(&value);

			return value;
		}
	}
	*/
	return 0;
}
#endif

#if 0
void CHTMLWindow::RenderRetained(Gui::ManagedRetainedRenderContext renderContext)
{
	FrameworkElement::RenderRetained(renderContext);
	return;	

#if 0
	if (!m_bRenderValid)
	{
		/*
		if (m_pDrawCommands)
		{
			delete m_pDrawCommands;
		}
		*/

		m_pDrawCommands = LDraw::Commands(new LDraw::_Commands);
		UI::Graphics graphics(new LDraw::GraphicsMetafile(m_pDrawCommands));

		OnRender(&graphics);
		m_bRenderValid = true;
	}

#endif

	ASSERT(0);
#if 0

	m_crit.Lock();

	LDraw::Commands* commands = m_pDrawCommands;	// This AddRefs

	m_crit.Unlock();

	if (commands)
	{
	//	LDraw::Matrix3f oldTransform = pGraphics->GetTransform();
	//	LDraw::Region oldClip;
	//	pGraphics->GetClip(&oldClip);
		pGraphics->PushTransform();
		pGraphics->PushClip();

		pGraphics->RenderCommands(commands);

		pGraphics->PopClip();
		pGraphics->PopTransform();

	//	pGraphics->SetTransform(oldTransform);
	//	pGraphics->SetClip(&oldClip);
	}
#endif
}
#endif

#if 0
void CHTMLWindow::OnRender(UI::Graphics* pGraphics)
{
//	TRACE("OnRender2..\n");

	if (false)
	{
		if (m_DrawCommands)
		{
			pGraphics->RenderCommands(m_DrawCommands);
		}
	}
	else
	{
		if (m_htmTree)
		{
			OnRenderMy(pGraphics);
		}
	}
}
#endif

void CHTMLWindow::OnRenderMy(Gui::RenderContext* pGraphics)
//void CHTMLWindow::Draw(LDraw::Graphics& graphics, const CRect& clip)
{
	TRACE("OnRenderMy..\n");
#if 0
#if 0
	if (m_bLayoutComplete)
	{
	//	MessageBeep(-1);
		m_bLayoutComplete = false;
	//	WaitForSingleObject(m_hLayoutDoneEvent, INFINITE);
	//	SetThreadPriority(m_hLayoutThread, THREAD_PRIORITY_NORMAL);
	//	Invalidate();
	//	PostMessage(NULL, WM_USER+4566, 0, 0);
	//	return;

	//	SetThreadPriority(m_hLayoutThread, THREAD_PRIORITY_LOWEST);
	}
#endif
//	m_crit.Lock();
//	if (!m_crit.Try())
//		return;
		//pGraphics->DrawString("Busy", 

	/*
	if (!m_bLayoutComplete)
	{
		m_crit.Unlock();
		Invalidate();
		PostMessage(NULL, WM_USER+4566, 0, 0);
		return;
	}
	*/

	//LDraw::Region oldclip;
	pGraphics->PushClip();

	{
		LDraw::SolidBrush* bgBrush = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));
		pGraphics->FillRectangle(bgBrush, 0, 0, m_computedSize.Width, m_computedSize.Height);
	}

	UI::Graphics& graphics = *pGraphics;
	if (1)
	{
		graphics.TranslateTransform(m_currentTranslateX, m_currentTranslateY);
	}
	//graphics.TranslateTransform(-scrollposX, -scrollposY);
#if 0
	graphics.TranslateTransform(-clip.left, -clip.top);
#endif
#if 0	// hm.. I'm doing this on the hDC above
	graphics.TranslateTransform(m_client.left, m_client.top);
#endif

#if 0
	graphics.SetTextRenderingHint(LDraw::TextRenderingHintSystemDefault/*TextRenderingHintAntiAliasGridFit*//*TextRenderingHintAntiAlias*/);
#endif
	//graphics.SetTextRenderingHint(LDraw::TextRenderingHintSingleBitPerPixel);
	//graphics.SetTextRenderingHint(LDraw::TextRenderingHintSystemDefault);

	if (m_htmTree)
	{
		CHTMRenderContext pC;
		// Had this ???
		//pC.m_pUI = m_pUI;
		pC.m_pWindow = this;
		pC.m_pGraphics = &graphics;

	//	pC.m_clipBox = clip;
	//	pC.m_clip = LDraw::RectF(float(clip.left), float(clip.top), float(clip.Width()), float(clip.Height()));

		//	pGraphics->GetClipBounds(&pC.m_clip);
		pC.m_clip.X = 0;
		pC.m_clip.Y = 0;
		pC.m_clip.Width = 800;
		pC.m_clip.Height = 800;

		// hDC has been called with SetViewportOrg, so clip is already adjusted
	//	pC.m_clip.Offset(-m_client.left, -m_client.top);

#if 0	// ?????TODO, have this
		pC.m_clipOrig = pC.m_clip;
#endif

		pC.m_hBrokenImage = m_hBrokenImage;

		pC.m_bInSelection = false;
//		pC.m_range = m_range;

#if 0
		pC.m_pStringFormat = LDraw::StringFormat::GenericTypographic();
#endif

		if (m_htmTree->m_pBox)
		{
			PElementBase* pHTMElement = m_htmTree;

			pHTMElement->m_selected = 0;
			pHTMElement->m_pBox->Draw(&pC);
			/*
			if (pHTMElement->m_pStackingContext)
			{
				pHTMElement->m_pStackingContext->Draw(&pC);
			}
			*/
#if 0
			if (m_htmTree->m_pBox)
			{
				m_htmTree->m_pBox->Draw(&pC);

				/*
				if (FALSE)
				{
					// Dim everything
					pC.m_pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(200, 255, 255, 255)), pC.m_clip);

					m_htmTree->m_pBox->DrawOutline(&pC);
				}
				*/
			}
#endif
		}
#if 0
		else if (m_pSVGElement)
		{
//			CLSVGSVGElement* psvgsvgElement = dynamic_cast<CLSVGSVGElement*>(m_pSVGElement->m_pNode);

			double magnify = GetFinalMagnify();

#if 0
			LDraw::GraphicsState state = pC.m_pGraphics->Save();	// TODO, just save matrix, it's probably faster
#endif
			/*
			double currentTranslateX = m_currentTranslateX + psvgsvgElement->m_currentTranslate->m_x;
			double currentTranslateY = m_currentTranslateY + psvgsvgElement->m_currentTranslate->m_y;
			*/
#if 0 // Done in CPSVGSVGElement
			<ILSVGPoint> currentTranslate;
			psvgsvgElement->get_currentTranslate(&currentTranslate);

			double currentScale;
			psvgsvgElement->get_currentScale(&currentScale);

			double x, y;
			currentTranslate->get_x(&x);
			currentTranslate->get_y(&y);
			pC.m_pGraphics->TranslateTransform(x, y);
#endif

#if 0
			CComQIPtr<ILSVGGlyphElement> glyphElement = m_pSVGElement->m_pNode;

			if (glyphElement)	// y is up
			{
				pC.m_pGraphics->ScaleTransform(magnify, -magnify);
			}
			else
#endif
			{
				pC.m_pGraphics->ScaleTransform(magnify/**currentScale*/, magnify/**currentScale*/);
			}

#if 0
			{
				gmMatrix3& matrix = m_pMatrix->m_matrix;

				LDraw::Matrix gdipmatrix(
					(float)matrix[0][0], (float)matrix[0][1],
					(float)matrix[1][0], (float)matrix[1][1],
					(float)matrix[2][0], (float)matrix[2][1]);
				pC.m_pGraphics->MultiplyTransform(&gdipmatrix);
			}
#endif

			m_pSVGElement->Render4(&pC, NULL, pC.m_pGraphics, m_pSVGElement->m_scaleX*magnify, m_pSVGElement->m_scaleY*magnify, FALSE, TRUE);
#if 0

			pC.m_pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);
			m_pSVGElement->RenderSelection(&pC);

			pC.m_pGraphics->Restore(state);
#endif
		}
#endif
#if 0
		else if (m_pSMILLayoutElement)
		{
			double magnify = GetFinalMagnify();

			//LDraw::GraphicsState state = pC.m_pGraphics->Save();	// TODO, just save matrix, it's probably faster

			LDraw::Bitmap* pBitmap = new LDraw::Bitmap(m_client.Width(), m_client.Height());
			if (pBitmap)
			{
				{
					LDraw::Graphics graphics(pBitmap);

					graphics.ScaleTransform(magnify, magnify);
					m_pSMILLayoutElement->Render(pBitmap, &graphics, magnify, magnify);
				//	m_pSVGDisplay->Draw(pC.m_pGraphics);

				//	pC.m_pGraphics->Restore(state);
					pC.m_pGraphics->DrawImage(pBitmap,
						LDraw::Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
						0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(),
						LDraw::UnitPixel);

					m_htmTree->RenderBehavior(pC.m_pGraphics);
				}

				delete pBitmap;
			}
			//m_pSMILDisplay->Draw(pC.m_pGraphics);
		}
		else if (m_pFODisplay)
		{
			int y = 0;

			for (int i = 0; i < m_pFODisplay->m_pages.GetSize(); i++)
			{
				CFOPage* pPage = m_pFODisplay->m_pages[i];
				LDraw::RectF pageRect(0, y, pPage->m_width, pPage->m_height);

				pC.m_pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 255)), pageRect);

				CHTMPElement* pElement = (CHTMPElement*)m_pFODisplay->m_pages[i]->m_pElement->m_childList.GetHead();

				if (pElement->m_pBox)
				{
					pElement->m_pBox->Draw(&pC);
				}

				y += pPage->m_height + 40;
			}
		}
#endif
	} // m_htmTree

	DrawCursor(pGraphics, m_curContainer, m_curOffset);

	pGraphics->PopClip();

//	m_crit.Unlock();

	size_t size = get_VisualChildrenCount();//(*get_rchildList()).get_Size();

	for (int i = 0; i < size; i++)
	{
		UI::Visual* pElement = GetVisualChild(i);//(*get_rchildList())[i];

		pElement->Render(pGraphics);
	}

#endif
	TRACE("done\n");
}

#if 0
void CHTMLWindow::OnPaint(HDC hDC)
{
	{
		//MessageBeep(-1);
	//	ASSERT(m_lockPaint == 0);

		LDraw::Rect client = m_client;

		//if (m_pUI == NULL || m_pUI->m_framesDesign == 0)
		if (TRUE)
		{
#if 0	// I had this
			EnterCriticalSection(&m_pActiveDocument->m_paintCriticalSection);
#endif

			int state = SaveDC(hDC);
			/*
			CRect brect = client;
			brect.InflateRect(1, 1);
			Draw3DRect(hDC, &brect, RGB(0, 0, 0), RGB(255, 255, 255));
	*/

			CRect clip;
			GetClipBox(hDC, &clip);


			/*

			if (m_lpbmi)
			{
			// Allocate a bitmap just the size of the invalid clip rect
				m_lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				m_lpbmi->bmiHeader.biWidth = clip.Width();
				m_lpbmi->bmiHeader.biHeight = -clip.Height();
				m_lpbmi->bmiHeader.biBitCount = 24;
				m_lpbmi->bmiHeader.biPlanes = 1;

				HBITMAP hTBitmap;
				LPBYTE TBits = NULL;

				if (hTBitmap = CreateDIBSection(NULL, m_lpbmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
				{
					long scrollposX; m_horz->get_pos(&scrollposX);
					long scrollposY; m_vert->get_pos(&scrollposY);

					HDC hTDC = CreateCompatibleDC(NULL);
					HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);
					*/

				//	FillSolidRect(hTDC, 0, 0, clip.Width(), clip.Height(), RGB(190, 190, 190));
				//	FillSolidRect(hTDC, 0, 0, clip.Width(), clip.Height(), RGB(255, 255, 255));
#if 0
					FillSolidRect(hDC, &m_client, RGB(255, 255, 255));
#endif
				//	POINT oldOrg;
				//	SetViewportOrgEx(hTDC, -clip.left, -clip.top, &oldOrg);
				//	OffsetViewportOrgEx(hTDC, m_client.left, m_client.top, NULL);

#if 0
					<ILDOMDocument> document = m_pView->m_document;
#endif
					//m_frameElement->get_contentDocument(&document);

	#if 0
					HDC dc = CreateCompatibleDC(NULL);
					HBITMAP hdcOldBitmap = (HBITMAP)SelectObject(dc, m_hBitmap);
	#endif

					//LDraw::Bitmap bgbitmap(m_imageRect.Width(), m_imageRect.Height());
				//	FillSolidRect(dc, 0, 0, m_imageRect.Width(), m_imageRect.Height(), RGB(190, 190, 190));

				//	SetICMMode(hTDC, ICM_ON);

					//LDraw::Graphics graphics(&bgbitmap);
				//	CPoint oldOrg;
				//	OffsetViewportOrgEx(hDC, m_client.left, m_client.top, &oldOrg);

					// Draw scrollbars
					{
						if (m_scrollY)
						{
							ASSERT(0);
#if 0
							if (m_scrollY->m_bWindowless)
							{
								DVASPECTINFO	dv;
								dv.cb = sizeof(dv);
								dv.dwFlags = 0;

								ErrorCode hr = m_scrollY->m_spViewObject->Draw(DVASPECT_CONTENT, -1, &dv, NULL, NULL,
									hDC,
									NULL,//&rectl,
									NULL,//&rectl,
									NULL,//continueDraw,
									0 // value to pass to callback function
									);
							}
#endif
						}

						if (m_scrollX)
						{
							ASSERT(0);
#if 0
							if (m_scrollX->m_bWindowless)
							{
								DVASPECTINFO	dv;
								dv.cb = sizeof(dv);
								dv.dwFlags = 0;

								ErrorCode hr = m_scrollX->m_spViewObject->Draw(DVASPECT_CONTENT, -1, &dv, NULL, NULL,
									hDC,
									NULL,//&rectl,
									NULL,//&rectl,
									NULL,//continueDraw,
									0 // value to pass to callback function
									);
							}
#endif
						}
					}

					if (IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom) > NULLREGION)
					{
#if 0
						OffsetViewportOrgEx(hDC, -clip.left, -clip.top, NULL);
#endif
					//	int success = SetICMMode(hDC, ICM_ON);
					//	ASSERT(success);

						{
							ASSERT(0);
#if 0
							LDraw::Graphics graphics(hDC);
							
							Draw(graphics, clip);
#endif
						}

#if 0	// TODO, have this, but not here
						if (m_dragging == 4)	// Zooming
						{
							long innerWidth;
							long innerHeight;
							get_innerWidth(&innerWidth);
							get_innerHeight(&innerHeight);

							CRect m_areaRect;
							m_areaRect.left = 0;
							m_areaRect.top = 0;
							m_areaRect.right = innerWidth;
							m_areaRect.bottom = innerHeight;

							//IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
							POINT org;
							org.x = m_areaRect.left;// + /*m_offset.x*/-scrollposX;
							org.y = m_areaRect.top;// + /*m_offset.y*/-scrollposY;
							POINT oldOrg;
							OffsetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

							int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

						// Erase old zoomrect
							Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

							SelectObject(hDC, hOldBrush);
							SetROP2(hDC, oldR2);

							SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
						}
#endif
					}

#if 0
					{
						TCHAR buf[64];
						sprintf(buf, "%g, %g", m_currentTranslateX, m_currentTranslateY);
						TextOut(hDC, 0, 0, buf, lstrlen(buf));
					}
#endif
					//SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

					/*
					LDraw::Graphics graphics2(dc);
					graphics2.DrawImage(&bgbitmap, 0, 0);

					BOOL bDither = FALSE;//((DispBitsPixel == 16) && theApp.m_dither16BitDisplay);
					BitBlt(hTDC, 0, 0, m_imageRect.Width(), m_imageRect.Height(), dc, 0, 0, SRCCOPY);
					*/

	#if 0	// I had this ?
					SelectObject(dc, hdcOldBitmap);
					DeleteDC(dc);
	#endif

	#if 0
					CLHTMLDocumentView* pHTMLControl = m_pUI;
					for (int i = 0; i < pHTMLControl->m_editors.GetSize(); i++)
					{
						IHTMLEditorSite* editor = pHTMLControl->m_editors[i];
						CRect rc(0,0,0,0);
						editor->DrawOver(hTDC, rc);
					}
	#endif

	#if 0
					SetViewportOrgEx(hTDC, oldOrg.x, oldOrg.y, NULL);
	#endif

#if 0
					BitBlt(hDC, clip.left, clip.top, clip.Width(), clip.Height(), hTDC, 0, 0, SRCCOPY);
#endif

					/*
					SelectObject(hTDC, hOldBitmap);
					DeleteDC(hTDC);

					DeleteObject(hTBitmap);
				}
			}
			*/
			RestoreDC(hDC, state);

#if 0	// I Had this
			LeaveCriticalSection(&m_pActiveDocument->m_paintCriticalSection);
#endif

#if 0
			if (FALSE)
			{
				<ILSVGSVGElement> svgsvgElement;
				m_pView->m_document->get_documentElement((ILDOMElement**)&svgsvgElement);

				double seconds;
				svgsvgElement->getCurrentTime(&seconds);

				TCHAR buf[64];
				sprintf(buf, "%d", (int)seconds);

				TextOut(hDC, 0, 0, buf, strlen(buf));
			}
#endif

			//if (m_bShowCursor)
		}
		else	// Frames Design mode
		{
			ASSERT(0);
#if 0
			if (m_frameElement)
			{
				CComBSTR scrolling;
				m_frameElement->get_scrolling(&scrolling);

				int nScrolling = 2;	// auto
				if (scrolling.Length())
				{
					if (!wcsicmp(scrolling, L"no"))
						nScrolling = 0;
					else if (!wcsicmp(scrolling, L"yes"))
						nScrolling = 1;
				}

				if (nScrolling)
				{
					COLORREF clr;

					if (nScrolling == 1)
					{
						clr = RGB(0, 0, 0);
					}
					else	// auto
					{
						clr = RGB(180, 180, 180);
					}

					Draw3DRect(hDC, m_client.right-16, m_client.top, m_client.right, m_client.bottom, clr, clr);
					Draw3DRect(hDC, m_client.left, m_client.bottom-16, m_client.right, m_client.bottom, clr, clr);
				}

				CComBSTR src;
				m_frameElement->get_src(&src);

				DrawText(hDC, _bstr_t(src), src.Length(), &m_client, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
#endif
		}
	}
}
#endif

#if 0
void CHTMLWindow::DrawCaret(HDC hDC)
{
;//	DrawCursor(m_curContainer, m_curOffset);
}
#endif

#if 0
//virtual
void CHTMLWindow::SetView(CLHTMLDocumentView* view)
{
	m_pUI = view;

	if (m_pFrameSet)
	{
		m_pFrameSet->SetView(view);
	}
}
#endif

#if 0
void CHTMLWindow::PositionFrames()
{
	// Am I using this???
	ASSERT(0);
#if 0
	if (m_pFrameSet)
	{
		m_pFrameSet->m_client = m_client;
		m_pFrameSet->PositionFrames();
	}
	else
	{
		//HWND hwnd = m_pUI->m_hWnd;

		OnSize();

		<ILDOMDocument> document = m_pView->m_document;
		//m_frameElement->get_contentDocument(&document);

		if (m_hBitmap)
		{
			DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
			m_bmBits = NULL;

			GlobalFree(m_lpBmi);
			m_lpBmi = NULL;
		}

		int width = m_imageRect.Width();
		int height = m_imageRect.Height();

		int rowBytes = ROWBYTES(width, 24);
		int sizeImage = rowBytes*height;

		if (m_lpBmi = (LPBITMAPV4HEADER)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPV4HEADER)))
		{
			m_lpBmi->bV4Size = sizeof(BITMAPV4HEADER);
			m_lpBmi->bV4Width = width;
			m_lpBmi->bV4Height = -height;
			m_lpBmi->bV4Planes = 1;
			m_lpBmi->bV4BitCount = 24;
			m_lpBmi->bV4SizeImage = sizeImage;

			m_hBitmap = ::CreateDIBSection(NULL, (BITMAPINFO*)m_lpBmi, DIB_RGB_COLORS, (void**)&m_bmBits, NULL, 0);
		}
	}
#endif
}
#endif

// Start at common ancestor, and search for either start or end container,
// the one found first is the first

Node* FindCommonAncestor(Node* node1, Node* node2);

/*
ILDOMNode* FindCommonAncestor(ILDOMNode* node1, ILDOMNode* node2)
{
	<ILDOMNode> parentNode1;
	node1->get_parentNode(&parentNode1);

	CArray<ILDOMNode*,ILDOMNode*> arr1;
	CArray<ILDOMNode*,ILDOMNode*> arr2;

	{
		<ILDOMNode> parentNode;
		node1->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr1.Add(parentNode);

			<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	{
		<ILDOMNode> parentNode;
		node2->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr2.Add(parentNode);

			<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	for (int i = 0; i < arr1.GetSize(); i++)
	{
		for (int j = 0; j < arr2.GetSize(); j++)
		{
			if (arr1[i] == arr2[j])
				return arr1[i];
		}
	}

	ASSERT(0);
	return NULL;
}
*/

int SearchForNode(Node* parent, Node* pThis, Node* pNode)
{
	Node* child = parent->get_firstChild();
	while (child)
	{
		if (child == pThis)
			return -1;
		else if (child == pNode)
			return 1;

		int n = SearchForNode(child, pThis, pNode);
		if (n)
			return n;

		child = child->get_nextSibling();
	}
	ASSERT(0);
	return 0;
}

int CompareTreePosition(Node* pThis, Node* pNode)
{
	if (pThis == pNode)
	{
		return 0;	// Equal
	}
	else
	{
		Node* commonAncestor = FindCommonAncestor(pThis, pNode);
		ASSERT(commonAncestor);

		return SearchForNode(commonAncestor, pThis, pNode);
	}
}

#if 0
STDMETHODIMP CHTMLWindow::SVGHitTest(/*[in]*/ ILSVGElement* element, /*[in]*/ long pointerEvents, /*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ bool* pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = false;

	ASSERT(0);
#if 0

	PSVGElement* pSVGElement = (PSVGElement*)CComQIPtr<CLSVGElementImplImpl>(element)->GetNodeOnFrame(m_pView);
	if (pSVGElement)
	{
		if (pSVGElement->m_Content->m_expandedBBox.Contains(x, y))
		{
			BOOL b = pSVGElement->HitTest(x, y, pointerEvents);
			*pVal = b? VARIANT_TRUE: false;
		}

		return Success;
	}
#endif

	return Success;
}

STDMETHODIMP CHTMLWindow::SVGCheckGeometryIntersection(ILSVGElement* element, ILSVGRect* rect, bool* pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	ASSERT(element != NULL);
	if (pVal == NULL) return E_POINTER;
	if (element == NULL) return E_INVALIDARG;

	*pVal = false;

	CLSVGElement* pElement = static_cast<CLSVGElement*>(element);

	RectD rc;
	rect->get_x(&rc.X);
	rect->get_y(&rc.Y);
	rect->get_width(&rc.Width);
	rect->get_height(&rc.Height);

	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pWindow == this)
		{
			HDC hDC = CreateCompatibleDC(NULL);
			{
				LDraw::Graphics graphics(hDC);

				PSVGElement* pSVGElement = (PSVGElement*)pElement->m_pNodes[i];

				LDraw::GraphicsPath graphicsPath;
				pSVGElement->RenderPath(&graphicsPath);

				LDraw::Region region1(&graphicsPath);

				LDraw::Region region2(&graphicsPath);
				region2.Complement(pSVGElement->m_filterRect);

				region1.Intersect(LDraw::RectF(rc.X, rc.Y, rc.Width, rc.Height));
				region2.Intersect(LDraw::RectF(rc.X, rc.Y, rc.Width, rc.Height));

				if (!region1.IsEmpty(&graphics) && !region2.IsEmpty(&graphics))
				{
					*pVal = VARIANT_TRUE;
				}
			}

			DeleteDC(hDC);

			return Success;
		}
	}
#endif

	return Success;
}
#endif

#if 0
STDMETHODIMP CHTMLWindow::setActiveElement(ILDOMElement *element)
{
	ASSERT(0);
#if 0
	<ILDOMElement> activeElement = m_activeElement;

	if (!IsUnknownEqualUnknown(activeElement, element))
	{
		// TODO, better solution ?
		CComQIPtr<ILDOMDocumentEvent> documentEvent;
		if (m_document)
		{
			documentEvent = m_document;
		}
		else
		{
			<ILDOMDocument> document;
			m_frameElement->get_ownerDocument(&document);
			documentEvent = document;
		}

		ASSERT(documentEvent);

		if (documentEvent)
		{
			<ILDOMUIEvent> evt;
			documentEvent->createEvent(L"UIEvents", (ILDOMEvent**)&evt);
			evt->initUIEvent(L"onactivate",
				VARIANT_TRUE,	// bubbles
				VARIANT_TRUE,	// cancelable
				this,	// viewArg
				0		// detail
				);

			ASSERT(evt);
			if (evt)
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = element;//static_cast<IBase*>(this);
				ASSERT(eventTarget);

				bool doDefault;
				eventTarget->dispatchEvent(evt, &doDefault);
			}
		}
	}
#endif
	return Success;
}
#endif

//

#if 0
void ResolveTimeDependenciesOnElement(double currentTime/*ILSVGSVGElement* svgElement*/, ILDOMElement* forElement, ILDOMElement* parent, ILDOMEvent * evt)
{
//	double currentTime;
//	svgElement->getCurrentTime(&currentTime);

	<ILDOMNode> child;
	parent->get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);
		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;

			CComQIPtr<ILElementTime> timeElement = element;
			if (timeElement != NULL)
			{
				<ILSMILTimeList> begin;
				timeElement->get_begin(&begin);

				long length;
				begin->get_length(&length);

				for (long i = 0; i < length; i++)
				{
					CComQIPtr<ILSMILTime> time;
					begin->item(i, &time);

					time->resolveTimeEvent(currentTime, evt);
				}
			}
			else
			{
				ResolveTimeDependenciesOnElement(currentTime/*svgElement*/, forElement, element, evt);
			}
		}

		<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}
#endif

void CHTMLWindow::OnMouseDown(Gui::MouseButtonEventArgs* args)
{
//	UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
	gm::PointF screenpos = args->GetScreenPosition();
	gm::PointF clientpos = args->GetPosition(m_ownerVisual);//ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
//	UI::Point* point = mouseEvt->GetPosition(this);
//	LDraw::PointD screenpt(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
//	LDraw::PointD clientpt(point.X, point.Y);

	ASSERT(0);
	//OnButtonDown(0, screenpos, clientpos, 0, false);
}

void CHTMLWindow::OnMouseUp(Gui::MouseButtonEventArgs* args)
{
//	UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
//	LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
//	UI::Point* point = mouseEvt->GetPosition(this);
//	LDraw::PointD screenpt(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
//	LDraw::PointD clientpt(point.X, point.Y);
	gm::PointF screenpos = args->GetScreenPosition();
	gm::PointF clientpos = args->GetPosition(m_ownerVisual);//ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

	ASSERT(0);
	//OnButtonUp(0, screenpos, clientpos, 0);
}

void CHTMLWindow::OnMouseMove(Gui::MouseEventArgs* args)
{
//	UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
//	LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
//	LDraw::PointD screenpt(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
//	LDraw::PointD clientpt(point.X, point.Y);
	gm::PointF screenpos = args->GetScreenPosition();
	gm::PointF clientpos = args->GetPosition(m_ownerVisual);//ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

	ASSERT(0);
	//OnMouseMove(0, screenpos, clientpos);
}

#if 0
void CHTMLWindow::handleEvent(System::Event* evt)
{
	System::StringW* type = evt->get_type();

	System::EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			evt->stopPropagation();

		}
		else if (*type == L"mouseup")
		{
			evt->stopPropagation();

		}
		else if (*type == L"mousemove")
		{
			evt->stopPropagation();

		}
		else if (*type == L"keydown")
		{
			evt->stopPropagation();
			OnKeyDown(dynamic_cast<UI::KeyEvent*>(evt));
		}
		else if (*type == L"char")
		{
			evt->stopPropagation();
			OnChar(dynamic_cast<UI::CharEvent*>(evt));
		}
	}
}
#endif

void CHTMLWindow::OnButtonDown(UINT nFlags, gm::PointD screenpt, gm::PointD clientpt, int iButton, bool bDblClk/*, CHTMFrameNode** pFrame*/)
{
	//if (m_pView->m_document)
	{
#if 0	// Had this
		if (m_pFrameSet)
		{
			return m_pFrameSet->OnButtonDown(nFlags, clientpt, iButton, bDblClk, pFrame);
		}
		else
#endif
		{
#if 0	// I Had this ???
			if (m_pUI == NULL || m_pUI->m_framesDesign == 0)
#endif
			if (true)
			{
				//<ILDOMDocument> document = m_pView->m_document;
				//m_frameElement->get_contentDocument(&document);

				m_startpt = clientpt;
				m_oldpt = clientpt;
				/*
				point.x -= m_client.left;
				point.y -= m_client.top;
				*/

#if 0
				// Check hit on scrollbars
				{
					COleClientItem* pClientItem = NULL;

					if (m_scrollY)
					{
						if (PtInRect(&m_scrollY->m_rcPos, clientpt))
						{
							pClientItem = m_scrollY;
						}
					}

					if (m_scrollX)
					{
						if (PtInRect(&m_scrollX->m_rcPos, clientpt))
						{
							pClientItem = m_scrollX;
						}
					}

					if (pClientItem &&
						pClientItem->m_spInPlaceObjectWindowless &&
						pClientItem->m_bWindowless)
					{
						WPARAM wparam = 0;
						LPARAM lparam = MAKELPARAM(clientpt.x, clientpt.y);

						LRESULT lresult = 0;

						ErrorCode hr = pClientItem->m_spInPlaceObjectWindowless->OnWindowMessage(WM_LBUTTONDOWN, wparam, lparam, &lresult);
						if (hr == Success)
						{
							m_dragging = 1;
							return 1;
						}
					}
				}
#endif

				if (m_htmTree)
				{
					if (m_htmTree->m_pBox)
					{
						PElementBase* pPElement = NULL;
						m_nhit = m_htmTree->m_pBox->HitTestElementBox(clientpt.X, clientpt.Y, &pPElement);
						if (m_nhit)
						{
							pPElement->OnButtonDown(screenpt, clientpt, m_nhit);

							PElementBase* pAElement = pPElement;

							do
							{
								String tagName = pAElement->m_pNode->get_nodeName();
								if (tagName == L"a")
								{
									break;
								}

								pAElement = pAElement->m_parent;
							}
							while (pAElement);

							DocumentEvent* documentEvent = dynamic_cast<DocumentEvent*>(m_htmTree->m_pNode->get_ownerDocument());

							if (pPElement)
							{
								EventTarget* eventTarget = dynamic_cast<EventTarget*>(pPElement->m_pNode);

								MouseEvent* pEvt;
								pEvt = dynamic_cast<MouseEvent*>(documentEvent->createEvent(WSTR("MouseEvents")));
								pEvt->initMouseEvent(S("mousedown"),
									true,	// canBubbleArg
									true,	// cancelableArg
									this,	// viewArg
									0,	// detailArg
									screenpt.X, screenpt.Y, clientpt.X, clientpt.Y,
									false,//ctrl
									false,//shift
									false,//alt
									false,//meta
									0,	// button
									dynamic_cast<EventTarget*>(m_htmTree->m_pNode)	// relatedTarget
									);
								eventTarget->dispatchEvent(pEvt);

								PNode* pNode = NULL;
								long offset = -1;

								bool bOver = m_htmTree->m_pBox->getPosUnderPoint(clientpt.X, clientpt.Y, &pNode, &offset);
								if (bOver)
								{
									m_initContainer = pNode;
									m_initOffset = offset;
									ASSERT(m_initOffset >= 0);

									m_curContainer = m_initContainer;
									m_curOffset = m_initOffset;
									ASSERT(m_curOffset >= 0);

									if (m_range == nullptr)
									{
										DocumentRangeImplImpl* documentRange = dynamic_cast<DocumentRangeImplImpl*>(m_htmTree->m_pNode->get_ownerDocument());
										if (documentRange)
										{
											m_range = documentRange->createRange();
										}
									}

									if (m_range)
									{
										m_range->setStart(m_initContainer->m_pNode, m_initOffset);
										m_range->setEnd(m_initContainer->m_pNode, m_initOffset);
									}

									m_dragging = 2;

									ASSERT(0);
#if 0
									Invalidate();
#endif
								}
							}

							if (pPElement != m_pPElementActive)
							{
#if 0
								if (m_pPElementActive)
								{
									m_pPElementActive->m_bActive = false;
									CCSSContext csscontext;
									m_pPElementActive->GetCSSProperties(&csscontext);
								}

								m_pPElementActive = pPElement;

								if (m_pPElementActive)
								{
									m_pPElementActive->m_bActive = true;
									CCSSContext csscontext;
									m_pPElementActive->GetCSSProperties(&csscontext);
								}

								Flow();	// hm.. optimize this somehow
#endif

								ASSERT(0);
#if 0
								Invalidate();	// TODO
#endif

#if 0
								if (m_pPElementActive)
								{
									CComQIPtr<ILDOMElement> element = m_pPElementActive->m_pNode;

									CComBSTR href;
									element->getAttribute(L"href", &href);

									TCHAR absurl[2048];
									DWORD len;
									{
										CComBSTR documentUrl;
										m_pView->m_document->get_url(&documentUrl);

										len = sizeof(absurl);
										InternetCombineUrl(_bstr_t(documentUrl), _bstr_t(href), absurl, &len, 0);
									}

									CComObject<COleDataObject>* pDataObject;
									CComObject<COleDataObject>::CreateInstance(&pDataObject);
									if (pDataObject)
									{
										pDataObject->AddRef();

										CMyDropSource*  pDropSource = new CMyDropSource;

										{
											HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, len+1);
											if (hData)
											{
												TCHAR* pData = (TCHAR*)GlobalLock(hData);
												if (pData)
												{
													CopyMemory(pData, absurl, len+1);

													GlobalUnlock(hData);

													STGMEDIUM stgm;
													stgm.tymed = TYMED_HGLOBAL;
													stgm.pUnkForRelease = NULL;
													stgm.hGlobal = hData;

													UINT nClipboardFormat = RegisterClipboardFormat(/*CFSTR_SHELLURL*/CFSTR_INETURL);

													FORMATETC etc = { nClipboardFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
													pDataObject->SetData(&etc, &stgm, TRUE /*fRelese*/);
												}
											}
										}

	#if 0
										{
											HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, len+1);
											if (hData)
											{
												TCHAR* pData = (TCHAR*)GlobalLock(hData);
												if (pData)
												{
													CopyMemory(pData, absurl, len+1);

													GlobalUnlock(hData);

													STGMEDIUM stgm;
													stgm.tymed = TYMED_HGLOBAL;
													stgm.pUnkForRelease = NULL;
													stgm.hGlobal = hData;

													UINT nClipboardFormat = CF_TEXT;

													FORMATETC etc = { nClipboardFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
													pDataObject->SetData(&etc, &stgm, TRUE /*fRelese*/);
												}
											}
										}
	#endif

										DWORD dropEffect = 0;
										if (::DoDragDrop(pDataObject, pDropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect) == DRAGDROP_S_DROP)
										{
											if (dropEffect == DROPEFFECT_NONE)
											{
												GotoLocation(href/*_bstr_t(absurl)*/);
											}
										}

										pDataObject->Release();
									}

									return 0;
								}
#endif
							}
						}

						/*
						if (TRUE)
						{
							m_pHitElement = NULL;
							BOOL b = m_htmTree->m_pBox->OnButtonDown(clientpt, &m_pHitElement);
							if (b)
								return;
						}
						*/

#if 0
						CPNode* pNode = NULL;
						long offset = -1;

						BOOL bOver = m_htmTree->m_pBox->getPosUnderPoint(point.x, point.y, &pNode, &offset);
						if (bOver)
						{
							m_initContainer = pNode;
							m_initOffset = offset;
							ASSERT(m_initOffset >= 0);

							m_curContainer = m_initContainer;
							m_curOffset = m_initOffset;
							ASSERT(m_curOffset >= 0);

							m_range->setStart(m_initContainer->m_pNode, m_initOffset);
							m_range->setEnd(m_initContainer->m_pNode, m_initOffset);

							m_dragging = 2;

							InvalidateRect(NULL);

							return 1;
						}
#endif
					}
#if 0
					else if (m_pSVGElement)
					{
						ASSERT(0);
#if 0
						CComQIPtr<ILDOMDocumentEvent> documentEvent = document;
						ASSERT(documentEvent != NULL);

						CComQIPtr<ILDOMElement> documentElement;
						document->get_documentElement(&documentElement);

#if 0
						CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
#endif

					//	bool editMode;
					//	m_documentContainer->get_editMode(&editMode);

						/*
						<ILSVGMatrix> mat0;
						svgsvgElement->createSVGMatrix(&mat0);

						<ILSVGMatrix> mat1;
						mat0->scale(m_magnify, &mat1);

						<ILSVGMatrix> mat;
						mat1->translate(m_currentTranslateX, m_currentTranslateY, &mat);
						*/

						PElement* pElement = NULL;

						if (m_htmTree->m_pBox)
						{
							pElement = m_htmTree->m_pBox->HitTestElementBox(clientpt.x, clientpt.y);

#if 0
							if (pElement)
							{
								pElement->m_pWindow = this;	// TODO, remove this, should have been done earlier
								pElement->OnButtonDown(point, NULL);

								return TRUE;	// ??
							}
#endif
						}
						else
						{
							ASSERT(0);
#if 0
							pElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));
#endif
						}

						if (pElement == NULL)
						{
							pElement = m_htmTree;//m_pSVGElement;
						}

						if (pElement)
						{
							m_pHitElement = pElement;
							/*
							m_pHitElement = NULL;
							BOOL b = pElement->OnButtonDown(point, &m_pHitElement);
							*/
						// Do something hm.. ??

					/*
					clientX and clientY parameters for mouse events represent viewport
					coordinates for the corresponding 'svg' element.

					relatedNode is the corresponding outermost 'svg' element
					*/

							<ILDOMEventTarget> target = pElement->m_eventTarget;
							ASSERT(target != NULL);
							if (target)
							{
								CComQIPtr<ILDOMEventTarget> relatedTarget;// = svgsvgElement;
								// TODO
#if 0
								ASSERT(relatedTarget != NULL);
#endif

								<ILDOMMouseEvent> mouseevt;

								documentEvent->createEvent(L"MouseEvents", (ILDOMEvent**)&mouseevt);
								mouseevt->initMouseEvent(L"mousedown",
									VARIANT_TRUE,	// bubbles
									VARIANT_TRUE,	// cancelable
									this,	// viewArg
									0,		// detail
									screenpt.x, screenpt.y,	// screen
									clientpt.x, clientpt.y, // client,
									(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
									(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
									(m_bAlt)? VARIANT_TRUE: false,
									0,	// meta
									iButton,
									relatedTarget
									);

								bool doDefault;
								target->dispatchEvent(mouseevt, &doDefault);

								if (doDefault)
								{
									if (nFlags & MK_CONTROL)	// Magnify
									{
										m_zoomRect.left = clientpt.x;
										m_zoomRect.top = clientpt.y;
										m_zoomRect.right = clientpt.x;
										m_zoomRect.bottom = clientpt.y;

										m_dragging = 4;
									}
									else if (m_bAlt)	// Pan
									{
										m_dragging = 3;
									}
									else
									{
										//CComQIPtr<ILSVGTextElement> textElement = pElement->m_pNode;

										if (FALSE)	// Check if over text
										//if (textElement)	// Over Text
										{
											if (m_pPElementFocus)
											{
											// TODO DOMFocusIn
											}

										// Find the character nearest to the mouse pointer
											PointD pt;	// TODO
											pt.X = clientpt.x;
											pt.Y = clientpt.y;

											CPNode* pNode = NULL;
											long offset = -1;

											BOOL bHitText;

											if (m_htmTree->m_pBox)
												bHitText = m_htmTree->m_pBox->getPosUnderPoint(clientpt.x, clientpt.y, &pNode, &offset);
											else
											{
												bHitText = FALSE;
												//ASSERT(0);
#if 0
												bHitText = ((PSVGElement*)pElement)->HitText(svgGetScreenCTM/*2*/((PSVGElement*)pElement), pt, &pNode, &offset);
#endif
											}

											if (bHitText)
											{
												CComQIPtr<ILDOMEventTarget> target;// = svgsvgElement;
												ASSERT(target != NULL);

												CComQIPtr<ILDOMEventTarget> relatedTarget;// = svgsvgElement;

												CComObject<CLDOMMouseEvent>* pEvt;
												CComObject<CLDOMMouseEvent>::CreateInstance(&pEvt);
												if (pEvt)
												{
													pEvt->AddRef();

													pEvt->initMouseEvent(L"select",
														VARIANT_TRUE,	// bubbles
														VARIANT_TRUE,	// cancelable
														this,	// viewArg
														0,		// detail
														screenpt.x, screenpt.y,	// screen
														clientpt.x, clientpt.y, // client,	// TODO
														(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
														(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
														(m_bAlt)? VARIANT_TRUE: false,
														0,	// meta
														iButton,
														relatedTarget
														);

													bool doDefault;
													target->dispatchEvent(pEvt, &doDefault);

													pEvt->Release();

													if (doDefault)
													{
														m_pPElementFocus = pElement;	// The text node has focus
													// TODO DOMFocusIn

														m_initContainer = pNode;
														m_initOffset = offset;
														ASSERT(m_initOffset >= 0);

														m_curContainer = m_initContainer;
														m_curOffset = m_initOffset;
														ASSERT(m_curOffset >= 0);

														m_range->setStart(m_initContainer->m_pNode, m_initOffset);
														m_range->setEnd(m_initContainer->m_pNode, m_initOffset);

														m_dragging = 2;

														InvalidateRect(NULL);
													}
												}
											}
										}
										/* ?????????
										else
										{
											m_dragging = 1;
										}
										*/
									}
								}

								if (m_dragging)
								{
									SetCapture();

									if (m_dragging == 3)
										::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND2)));
								}

								return 1;
							}
						}
#endif
					}
#endif
				} // m_htmTree
			}
			else
			{
				ASSERT(0);
	#if 0
				setActiveElement(m_frameElement);//m_frameElement->setActive();
	#endif
			}
		}
	}

#if 0	// TODO, delete the following
	CComQIPtr<IUIManager> uiManager;
//	m_pUI->get_uiManager(&uiManager);

	CComQIPtr<IDOMDocument> document;
	if (m_documentContainer) m_documentContainer->get_document(&document);

	CComQIPtr<ISVGDocument> svgDocument;

	if (m_pFrameSet)
	{
		return m_pFrameSet->OnButtonDown(nFlags, abspoint, iButton, bDblClk, pFrame);
	}
	else
	{
		*pFrame = this;

		POINT point = abspoint;
		point.x -= m_client.left;
		point.y -= m_client.top;

		bool editMode;
		m_documentContainer->get_editMode(&editMode);

		CComQIPtr<IDOMDocument> document;
		m_documentContainer->get_document(&document);

		CComQIPtr<IDOMDocumentEvent> documentEvent = document;
		ASSERT(documentEvent != NULL);

		CComQIPtr<IDOMElement> documentElement;
		document->get_documentElement(&documentElement);
/*
clientX and clientY parameters for mouse events represent viewport
coordinates for the corresponding 'svg' element.

relatedNode is the corresponding outermost 'svg' element
*/

		CComQIPtr<IDOMEventTarget> relatedTarget = documentElement;
		ASSERT(relatedTarget != NULL);

		CComQIPtr<IDOMMouseEvent> mouseevt;
	
		documentEvent->createEvent(L"MouseEvents", (IDOMEvent**)&mouseevt);
		mouseevt->initMouseEvent(L"mousedown",
			TRUE,	// bubbles
			TRUE,	// cancelable
			this,	// viewArg
			0,		// detail
			point.x, point.y,	// screen
			point.x, point.y, // client,
			(nFlags & MK_CONTROL)? TRUE: FALSE,
			(nFlags & MK_SHIFT)? TRUE: FALSE,
			(nFlags & MK_ALT)? TRUE: FALSE,
			0,	// meta
			0,
			relatedTarget
			);

		BOOL bCancel;

		CComQIPtr<IDOMEvent> evt;

		/*
		CHTMLControl* pHTMLControl = m_pUI;
		for (int i = 0; i < pHTMLControl->m_editors.GetSize(); i++)
		{
			IHTMLEditorSite* editor = pHTMLControl->m_editors[i];
			editor->TranslateEvent(mouseevt, &evt, &bCancel);
			if (bCancel) break;
		}

		if (bCancel) return TRUE;
		*/

		if (m_htmTree)
		{
			if (!editMode)	// Document is 'playing'
			{
				CHTMPElement* pElement = (CHTMPElement*)m_htmTree->m_childList.GetHead();

				if (pElement && pElement->m_pBox)
				{
					BOOL b = pElement->m_pBox->ButtonDown(point);
					return b;
				}

				/*
				long textoffset = -1;
				CPNode* pElement = m_htmTree->GetTextLocationUnderPoint(point, textoffset);

				if (pElement)
				{
					_tagDOMNodeType nodeType;
					pElement->m_pNode->get_nodeType(&nodeType);

					if (nodeType == LNODE_ELEMENT)
					{
						CComQIPtr<IDOMEventTarget> target = pElement->m_pNode;

						BOOL doDefault;
						target->dispatchEvent(mouseevt, &doDefault);
					}
				}
				*/
			}
			else
			{
				if (m_cursorItem)
				{
					if (uiManager)
					{
						uiManager->DeactivateObject(m_cursorItem->m_pNode);
					}
				}

				HideCursor();

				CHTMPElement* pElement = (CHTMPElement*)m_htmTree->m_childList.GetHead();

				if (pElement && pElement->m_pBox)
				{
					BOOL b = pElement->m_pBox->ButtonDown(point);
					return b;
				}

#if 0
				if (CursorPositionFromPoint(point, &m_cursorItem, &m_cursorOffset))
				{
					if (uiManager)
					{
						uiManager->ActivateObject(m_cursorItem->m_pNode);
					}

					InvalidateRect(&m_client);
					m_pUI->UpdateWindow();

					_tagDOMNodeType nodeType;
					m_cursorItem->m_pNode->get_nodeType(&nodeType);

					if (nodeType == NODE_TEXT)
					{
					//	m_dragging = 1;
					//	m_startSelItem = pItem;

					}
					else
					{
						if (m_cursorItem->OnButtonDown(this, point))
						{
						/*
						// Invalidate this view
							OnSize();
							m_pUI->InvalidateRect(&m_client);

						// Invalidate all other views
							if (TRUE)
							{
								m_pDocument->m_pText->CreateHTMLTree();
								m_pDocument->m_pText->UpdateAllViews(m_pUI);
							}
						*/
						}
						else
						{
		#if 0
							CHTMElement* pElement = (CHTMElement*)m_cursorItem->m_pNode;

							CUString str_data = pElement->GetOuterHTML();

							HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, str_data.GetLength() + 1);

							char* p = (char*)GlobalLock(hData);

							CopyMemory(p, (LPCTSTR)str_data, str_data.GetLength()+1);
							p[str_data.GetLength()] = 0;

							GlobalUnlock(hData);

							if (hData)
							{
								COleDataSource source;
								source.CacheGlobalData(RegisterClipboardFormat("MMStudio-HTML"), hData, NULL);

								if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_MOVE)
								{
									CHTMPElement* pPParent = (CHTMPElement*)m_cursorItem->m_parent;
									CHTMElement* pParent = (CHTMElement*)pPParent->m_pNode;

									m_cursorItem = NULL;
									m_cursorOffset = 0;

								// Remove element from DOM
									POSITION pos = pElement->m_pParent->m_childList.Find(pElement);
									pElement->m_pParent->m_childList.RemoveAt(pos);
									delete pElement;

									// Update source
									pParent->SetInnerHTML(pParent->GetInnerHTML());

								// Rebuild the rendering tree
									pPParent->RemoveChildren();
									pPParent->BuildTree(this, pParent);

								// Invalidate this view
									OnSize();
									m_pUI->InvalidateRect(&m_client);

								// Invalidate all other views
									if (TRUE)
									{
										m_pDocument->m_pText->CreateHTMLTree();
										m_pDocument->m_pText->UpdateAllViews(m_pUI);
									}

								}

								m_dragOverItem = NULL;
								m_dragOverOffset = 0;

								source.Empty();

								GlobalFree(hData);
							}
		#endif
						}
					}

		#if 0
					if (FALSE)
					{
						if (m_cursorItem->m_pNode->m_nodeType == TYP_ELEMENT)
						{
							CHTMPElement* pPEl = (CHTMPElement*)m_cursorItem;
							CHTMElement* pEl = (CHTMElement*)m_cursorItem->m_pNode;

							CUString onclick = pEl->GetAttrValue("onclick", "");
							if (!onclick.IsEmpty())
							{
								RunJScriptCode(onclick);
							}
						}
						else
						{
							CHTMPElement* pPA = m_cursorItem->FindParentElement("A");
							if (pPA)
							{
								CHTMElement* pElement = (CHTMElement*)pPA->m_pNode;

								CUString relurl = pElement->GetAttrValue("HREF", "");

								CUString target = pElement->GetAttrValue("TARGET", "");
								if (target.IsEmpty()) target = "_self";	// Default

								if (!relurl.IsEmpty())
								{
									CUString baseurl = m_pDocument->m_url;
									CUString fullurl = CombineURL(baseurl, relurl);

									CHTMFrame2* pTargetFrame = NULL;

									if (!stricmp(target, "_self"))
									{
										pTargetFrame = this;
									}
									else if (!stricmp(target, "_top"))
									{
										pTargetFrame = GetTopFrame();
									}
									else if (!stricmp(target, "_parent"))
									{
										AfxMessageBox("_parent");
									// This isn't correct ?
										pTargetFrame = (CHTMFrame2*)m_pParentFrame;
									}
									else if (!stricmp(target, "_blank"))
									{
										AfxMessageBox("_blank");
										pTargetFrame = NULL;
									}
									else
									{
										AfxMessageBox(target);
										pTargetFrame = NULL;
									}

									if (pTargetFrame)
									{
										ASSERT(pTargetFrame->m_type == 1);

										if (!fullurl.IsEmpty())
										{
										//	AfxMessageBox(fullurl);
											pTargetFrame->GotoLocation(fullurl);
										}
									}
								}
							}
						}
					}
		#endif
				}
#endif

				ShowCursor();
			}

			return 0;
		}
		else if (svgDocument = document)
		{
			CComQIPtr<ISVGPoint> svgpt;
			svgpt.CoCreateInstance(CLSID_SVGPoint);
			svgpt->set_x((float)point.x);
			svgpt->set_y((float)point.y);

			CComQIPtr<ISVGSVGElement> svgsvgElement;
			svgDocument->get_documentElement((IDOMElement**)&svgsvgElement);

			CSvgSvgElement* pSVGElement;
			svgsvgElement->GetNProp(L"pelement", (DWORD*)&pSVGElement);

			CElement* pElement = pSVGElement->GetElementUnderPoint(svgpt);

			if (pElement)
			{
		/*
		clientX and clientY parameters for mouse events represent viewport
		coordinates for the corresponding 'svg' element.

		relatedNode is the corresponding outermost 'svg' element
		*/

				CComQIPtr<IDOMDocumentEvent> documentEvent = svgDocument;

				CComQIPtr<IDOMEventTarget> relatedTarget = svgsvgElement;//m_pDocument->GetSvgElement()->m_domElement;


				CComQIPtr<IDOMEventTarget> target = pElement->m_domElement;

				bool doDefault;
				target->dispatchEvent(mouseevt, &doDefault);
				
				CComQIPtr<ISVGTextContentElement> textContent = target;
				if (textContent)
				{
					CTextContent* pTextContent;
					textContent->GetNProp(L"pelement", (DWORD*)&pTextContent);
					pSVGElement->m_pSelectedTextElement = pTextContent->GetTextElement();

					long charpos = pSVGElement->m_pSelectedTextElement->getCharNumAtPosition(svgpt);
					if (charpos >= 0)
					{
						pSVGElement->m_initSelCharPos = charpos;
						pSVGElement->m_startSelCharPos = charpos;
						pSVGElement->m_endSelCharPos = charpos;

						m_dragging = 1;
					}
					else
					{
						pSVGElement->m_pSelectedTextElement = NULL;
					}
				}
			}
		}
	}
#endif
}

void CHTMLWindow::OnMouseMove(UINT nFlags, gm::PointD screenpt, gm::PointD clientpt)
{
//	return;

//	if (m_pView->m_document)
	{
		//if (m_pUI == NULL || m_pUI->m_framesDesign == 0)	// TODO, what does this do?
		if (true)
		{
		//	<ILDOMDocument> document = m_pView->m_document;
			//m_frameElement->get_contentDocument(&document);

			/*
			bool editMode;
			m_documentContainer->get_editMode(&editMode);

			CComQIPtr<IDOMDocument> document;
			m_documentContainer->get_document(&document);
	*/
#if 0
			DocumentEvent* documentEvent = dynamic_cast<DocumentEvent*>(m_document);
			ASSERT(documentEvent != NULL);

			CComQIPtr<ILDOMElement> documentElement;
			document->get_documentElement(&documentElement);
#endif
	/*
	clientX and clientY parameters for mouse events represent viewport
	coordinates for the corresponding 'svg' element.

	relatedNode is the corresponding outermost 'svg' element
	*/

#if 0	// TODO, have this, but not here
			if (m_dragging == 3)	// Pan
			{
				CComQIPtr<ILSVGDocument> svgDocument = m_pView->m_document;
				if (svgDocument)
				{
					<ILSVGSVGElement> svgsvgElement;
					svgDocument->get_rootElement(&svgsvgElement);

					<ILSVGPoint> currentTranslate;
					svgsvgElement->get_currentTranslate(&currentTranslate);

					double x, y;
					currentTranslate->get_x(&x);
					currentTranslate->get_y(&y);

					currentTranslate->set_x(x + (clientpt.x - m_oldpt.x));
					currentTranslate->set_y(y + (clientpt.y - m_oldpt.y));

					InvalidateRect(NULL);	// TODO remove
				}
			}
			else if (m_dragging == 4)	// Magnify
			{
				HDC hDC = GetDC();

				int state = SaveDC(hDC);

				long innerWidth;
				long innerHeight;
				get_innerWidth(&innerWidth);
				get_innerHeight(&innerHeight);

				CRect m_areaRect;
				m_areaRect.left = 0;
				m_areaRect.top = 0;
				m_areaRect.right = innerWidth;
				m_areaRect.bottom = innerHeight;

				//IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

				POINT org;
				org.x = m_areaRect.left;// + /*m_offset.x*/-scrollposX;
				org.y = m_areaRect.top;// + /*m_offset.y*/-scrollposY;

				POINT oldOrg;
				OffsetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

			// Erase old zoomrect
				Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

				double aspect = (double)m_areaRect.Height()/m_areaRect.Width();

				m_zoomRect.left = m_startpt.x;
				m_zoomRect.top = m_startpt.y;
				if ((double)abs(clientpt.x-m_startpt.x)/m_areaRect.Width() > (double)abs(clientpt.y-m_startpt.y)/m_areaRect.Height())
				{
					double aspect = (double)m_areaRect.Height()/m_areaRect.Width();
					m_zoomRect.right = clientpt.x;
					m_zoomRect.bottom = m_startpt.y + (clientpt.x-m_startpt.x)*aspect;
				}
				else
				{
					double aspect = (double)m_areaRect.Width()/m_areaRect.Height();
					m_zoomRect.right = m_startpt.x + (clientpt.y-m_startpt.y)*aspect;
					m_zoomRect.bottom = clientpt.y;
				}

			// Draw new zoomrect
				Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

				SelectObject(hDC, hOldBrush);
				SetROP2(hDC, oldR2);

				SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

				RestoreDC(hDC, state);

				ReleaseDC(hDC);
			}
			else
#endif
			{
				if (m_pElementCapture)
				{
					m_pElementCapture->OnMouseMove(screenpt, clientpt, m_nhit);

#if 0
					if (m_pOCItemCapture->m_spInPlaceObjectWindowless && m_pOCItemCapture->m_bWindowless)
					{
						WPARAM wparam = 0;
						LPARAM lparam = MAKELPARAM(point.x, point.y);

						LRESULT lresult = 0;

						ErrorCode hr = m_pOCItemCapture->m_spInPlaceObjectWindowless->OnWindowMessage(WM_MOUSEMOVE, wparam, lparam, &lresult);
						if (hr == Success) return;
					}
#endif
				}
				else
				{
					if (m_htmTree)
					{
						if (m_htmTree->m_pBox)	// CSS box model
						{
							if (m_dragging)
							{
								PNode* pNode = NULL;
								long offset = -1;

								bool bOver = m_htmTree->m_pBox->getPosUnderPoint(clientpt.X, clientpt.Y, &pNode, &offset);
								if (bOver && dynamic_cast<PText*>(pNode))
								{
									PNode* startContainer;
									//<ILDOMNode> startContainer;
									long startOffset;

									PNode* endContainer;
									//<ILDOMNode> endContainer;
									long endOffset;

									if (pNode == m_initContainer)	// start and end share container
									{
										startContainer = pNode;
										endContainer = pNode;

										if (offset < m_initOffset)
										{
											startOffset = offset;
											endOffset = m_initOffset;
										}
										else
										{
											startOffset = m_initOffset;
											endOffset = offset;
										}
									}
									else
									{
										int cmp = CompareTreePosition(pNode->m_pNode, m_initContainer->m_pNode);
										ASSERT(cmp != 0);

										if (cmp == -1)
										{
											startContainer = pNode;
											startOffset = offset;

											endContainer = m_initContainer;
											endOffset = m_initOffset;
										}
										else
										{
											startContainer = m_initContainer;
											startOffset = m_initOffset;

											endContainer = pNode;
											endOffset = offset;
										}
									}

								//	if (pNode == m_initContainer)	// TODO remove
									{
									m_curContainer = pNode;
									m_curOffset = offset;

									if (m_range->get_startContainer() != startContainer->m_pNode ||
										m_range->get_endContainer() != endContainer->m_pNode ||
										m_range->get_startOffset() != startOffset ||
										m_range->get_endOffset() != endOffset)
									{
										m_range->setStart(startContainer->m_pNode, startOffset);
										m_range->setEnd(endContainer->m_pNode, endOffset);

										m_htmTree->GetCSSPropertiesAndChildren();

										Flow();
										ASSERT(0);
#if 0
										Invalidate();
#endif
									}
									}
								}
							}
							else	// dragging == 0
							{
#if 0
								if (m_pPElementHover)
								{
								}

								PElementBase* pPElement = NULL;
								int nhit = m_htmTree->m_pBox->HitTestElementBox(clientpt.X, clientpt.Y, &pPElement);

								if (pPElement != m_pPElementHover)
								{
									if (m_pPElementHover)
									{
										m_pPElementHover->m_bHover = false;
										CCSSContext csscontext;
										m_pPElementHover->GetCSSProperties(&csscontext);
									//	m_pPElementHover->GetCSSPropertiesAndChildren(NULL);
									}

									m_pPElementHover = pPElement;

									if (m_pPElementHover)
									{
									// :hover pseudoclass is true
										m_pPElementHover->m_bHover = true;

										CCSSContext csscontext;
										m_pPElementHover->GetCSSProperties(&csscontext);
										//m_pPElementHover->GetCSSPropertiesAndChildren(NULL);

									}

									//Flow();	// hm.. optimize this somehow
									InvalidateArrange();

									Invalidate();// TODO
								}
#endif
							}
						}
#if 0
						else if (m_pSVGElement)
						{
							if (m_dragging == 2)	// Text selection
							{
								ASSERT(0);	// TODO, make work for both cssboxmodel and svg
								ASSERT(m_pPElementFocus);

#if 0
								CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
#endif

								/*
								<ILSVGMatrix> mat0;
								svgsvgElement->createSVGMatrix(&mat0);

								<ILSVGMatrix> mat1;
								mat0->scale(m_magnify, &mat1);

								<ILSVGMatrix> mat;
								mat1->translate(m_currentTranslateX, m_currentTranslateY, &mat);
								*/

								PointD pt;	// TODO
								pt.X = clientpt.x;
								pt.Y = clientpt.y;

								CPNode* pNode = NULL;
								long offset = -1;
								//PElement* pElement = NULL;
								//HitTestSVGElement(m_pSVGElement, svgsvgElement, mat, point.x, point.y, &pElement, &pNode, &offset);

								ASSERT(0);
#if 0
								((PSVGElement*)m_pPElementFocus)->HitText(svgGetScreenCTM((PSVGElement*)m_pPElementFocus), pt, &pNode, &offset);
#endif

								if (pNode)	// Over Text
								{
									CPNode* startContainer;
									//<ILDOMNode> startContainer;
									long startOffset;

									CPNode* endContainer;
									//<ILDOMNode> endContainer;
									long endOffset;

									if (pNode == m_initContainer)	// start and end share container
									{
										startContainer = pNode;
										endContainer = pNode;

										if (offset < m_initOffset)
										{
											startOffset = offset;
											endOffset = m_initOffset;
										}
										else
										{
											startOffset = m_initOffset;
											endOffset = offset;
										}
									}
									else
									{
										int cmp = CompareTreePosition(pNode->m_pNode, m_initContainer->m_pNode);
										ASSERT(cmp != 0);

										if (cmp == -1)
										{
											startContainer = pNode;
											startOffset = offset;

											endContainer = m_initContainer;
											endOffset = m_initOffset;
										}
										else
										{
											startContainer = m_initContainer;
											startOffset = m_initOffset;

											endContainer = pNode;
											endOffset = offset;
										}
									}

									m_curContainer = pNode;
									m_curOffset = offset;

									m_range->setStart(startContainer->m_pNode, startOffset);
									m_range->setEnd(endContainer->m_pNode, endOffset);

									m_htmTree->CalculateBoundsAndChildren();
									Flow();

									InvalidateRect(NULL);	// TODO, use rect
								}
							}
							else
							{
								CComQIPtr<ILDOMEventTarget> relatedTarget = documentElement;
								ASSERT(relatedTarget != NULL);

								BOOL bHasCapture;
#if 0	// I had this
								if (m_pUI)
									bHasCapture = (::GetCapture() == m_pUI->m_hWnd);
								else if (m_pActiveDocument)
									bHasCapture = (m_pActiveDocument->m_spInPlaceSite->GetCapture() == Success);
								else
#endif
									bHasCapture = FALSE;

					//			CComQIPtr<ILDOMElement> documentElement;
					//			document->get_documentElement(&documentElement);

#if 0
								CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
#endif

								/*
								<ILSVGMatrix> mat0;
								svgsvgElement->createSVGMatrix(&mat0);

								<ILSVGMatrix> mat1;
								mat0->scale(m_magnify, &mat1);

								<ILSVGMatrix> mat;
								mat1->translate(m_currentTranslateX, m_currentTranslateY, &mat);
								*/

								if (!bHasCapture)
								{
									PElement* pPElement;

									if (m_htmTree->m_pBox)
									{
										pPElement = m_htmTree->m_pBox->HitTestElementBox(clientpt.x, clientpt.y);
									}
									else
									{
#if 0
										ASSERT(0);
										pPElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));
#endif
									}

									//PSVGElement* pPElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));

									if (pPElement == NULL)
									{
										pPElement = m_htmTree;///m_pSVGElement;
									}

									if (pPElement != m_pPElementHover)
									{
										if (m_pPElementHover)	// mouseout on previous
										{
											// TODO, check order of hover and mouseout
											m_pPElementHover->m_bHover = false;
											m_pPElementHover->GetCSSPropertiesAndChildren();

											CalcDims(m_pPElementHover);

											m_pPElementHover->RecalculateParentBounds();	// ??

											<ILDOMMouseEvent> mouseevt;
											documentEvent->createEvent(L"MouseEvents", (ILDOMEvent**)&mouseevt);
											mouseevt->initMouseEvent(L"mouseout",
												VARIANT_TRUE,	// bubbles
												VARIANT_TRUE,	// cancelable
												this,	// viewArg
												0,		// detail
												screenpt.x, screenpt.y,	// screen
												clientpt.x, clientpt.y, // client,
												(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
												(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
												(m_bAlt)? VARIANT_TRUE: false,
												0,	// meta
												0,
												relatedTarget
												);

											<ILDOMEventTarget> eventTarget = m_pPElementHover->m_eventTarget;
											bool doDefault;
											eventTarget->dispatchEvent(mouseevt, &doDefault);
										}

										m_pPElementHover = pPElement;

										if (m_pPElementHover)	// mousein on new
										{
											// TODO, check order of hover and mouseover
											m_pPElementHover->m_bHover = true;
											m_pPElementHover->GetCSSPropertiesAndChildren();

											CalcDims(m_pPElementHover);

											m_pPElementHover->RecalculateParentBounds();	// ??

											<ILDOMMouseEvent> mouseevt;
											documentEvent->createEvent(L"MouseEvents", (ILDOMEvent**)&mouseevt);
											mouseevt->initMouseEvent(L"mouseover",
												VARIANT_TRUE,	// bubbles
												VARIANT_TRUE,	// cancelable
												this,	// viewArg
												0,		// detail
												screenpt.x, screenpt.y,	// screen
												clientpt.x, clientpt.y, // client,
												(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
												(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
												(m_bAlt)? VARIANT_TRUE: false,
												0,	// meta
												0,
												relatedTarget
												);

											CComQIPtr<ILDOMEventTarget> eventTarget = m_pPElementHover->m_pNode;
											bool doDefault;
											eventTarget->dispatchEvent(mouseevt, &doDefault);
										}
									}
								}

								ASSERT(m_pPElementHover != NULL);

								<ILDOMMouseEvent> mouseevt;
								documentEvent->createEvent(L"MouseEvents", (ILDOMEvent**)&mouseevt);
								mouseevt->initMouseEvent(L"mousemove",
									VARIANT_TRUE,	// bubbles
									VARIANT_TRUE,	// cancelable
									this,	// viewArg
									0,		// detail
									screenpt.x, screenpt.y,	// screen
									clientpt.x, clientpt.y, // client,
									(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
									(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
									(m_bAlt)? VARIANT_TRUE: false,
									0,	// meta
									0,
									relatedTarget
									);

								CComQIPtr<ILDOMEventTarget> eventTarget = m_pPElementHover->m_pNode;
								bool doDefault;
								eventTarget->dispatchEvent(mouseevt, &doDefault);
							}
						}
#endif
					} // m_htmTree
				}
			}
		}
	}

	m_oldpt = clientpt;
}

void CHTMLWindow::OnButtonUp(UINT nFlags, gm::PointD screenpt, gm::PointD clientpt, int iButton)
{
	//POINT point = abspoint;

//	if (m_pView->m_document)
	{
		/*
		point.x -= m_client.left;
		point.y -= m_client.top;
		*/

		int dragging = m_dragging;
		m_dragging = 0;

		if (dragging)
		{
			m_ownerVisual->ReleaseMouseCapture();
		}

		//if (m_pUI == NULL || m_pUI->m_framesDesign == 0)
		if (true)
		{
#if 0
			CComQIPtr<ILDOMDocumentEvent> documentEvent = m_pView->m_document;
			ASSERT(documentEvent != NULL);
#endif
		/*// ????
			if (m_pHitElement)
			{
				// TODO OnMouseUp
				m_pHitElement = NULL;
			}
			else
			*/
			if (dragging == 3)	// Panning
			{
				// All work is already done
			}
			else if (dragging == 4)	// Zooming
			{
				ASSERT(0);
#if 0
				CLSVGSVGElement* psvgsvgElement = static_cast<CLSVGSVGElement*>(m_pSVGElement->m_pNode);

				double magnify;
				psvgsvgElement->get_currentScale(&magnify);

				double aspect = (double)m_imageRect.Height()/m_imageRect.Width();

				m_zoomRect.NormalizeRect();

				CLSVGZoomEvent* pEvt = new CLSVGZoomEvent;
			//	CComObject<CLSVGZoomEvent>::CreateInstance(&pEvt);
			//	pEvt->AddRef();

				pEvt->initUIEvent(L"SVGZoom", true, false, m_pView, 0);

				double newScale;
				double newTranslateX;
				double newTranslateY;

				CDblRect zoomScreenRect;

				if (m_zoomRect.Width() <= 2 || m_zoomRect.Height() <= 2)
				{
					double x = m_startpt.x;
					double y = m_startpt.y;

					if (!(nFlags & MK_SHIFT))	// Zoom in
					{
						zoomScreenRect = CDblRect(
							x-m_imageRect.Width()/4.0,
							y-m_imageRect.Height()/4.0,
							x+m_imageRect.Width()/4.0,
							y+m_imageRect.Height()/4.0);
					}
					else	// Zoom out
					{
						zoomScreenRect = CDblRect(
							x-m_imageRect.Width(),
							y-m_imageRect.Height(),
							x+m_imageRect.Width(),
							y+m_imageRect.Height());
					}
				}
				else
				{
					zoomScreenRect = CDblRect(m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);
				}

				psvgsvgElement->get_currentScale(&pEvt->m_previousScale);
				psvgsvgElement->m_currentTranslate->get_x(&pEvt->m_previousTranslate->m_x);
				psvgsvgElement->m_currentTranslate->get_y(&pEvt->m_previousTranslate->m_y);

				pEvt->m_zoomRectScreen->m_x = zoomScreenRect.left;
				pEvt->m_zoomRectScreen->m_y = zoomScreenRect.top;
				pEvt->m_zoomRectScreen->m_width = zoomScreenRect.Width();
				pEvt->m_zoomRectScreen->m_height = zoomScreenRect.Height();
				pEvt->m_zoomRectScreen->m_x -= m_currentTranslateX;	// ??
				pEvt->m_zoomRectScreen->m_y -= m_currentTranslateY;	// ??

					//CDblRect zoomdrect;
				double oldmagnify;
				psvgsvgElement->get_currentScale(&oldmagnify);
				oldmagnify *= m_magnify;

				double translateX;
				double translateY;
				psvgsvgElement->m_currentTranslate->get_x(&translateX);
				psvgsvgElement->m_currentTranslate->get_y(&translateY);
				translateX += m_currentTranslateX;
				translateY += m_currentTranslateY;

				CDblRect zoomdrect;
				zoomdrect.left = (zoomScreenRect.left-translateX)/oldmagnify;// + translateX;
				zoomdrect.top = (zoomScreenRect.top-translateY)/oldmagnify;// + translateY;
				zoomdrect.right = (zoomScreenRect.right-translateX)/oldmagnify;// + translateX;
				zoomdrect.bottom = (zoomScreenRect.bottom-translateY)/oldmagnify;// + translateY;

				double width = zoomdrect.right-zoomdrect.left;

			// Set new scale
				newScale = (double)(m_imageRect.Width())/(width);

			// Set new translate XY
				newTranslateX = -zoomdrect.left*newScale;
				newTranslateY = -zoomdrect.top*newScale;
				newTranslateX -= m_currentTranslateX;
				newTranslateY -= m_currentTranslateY;

				pEvt->m_newScale = newScale;
				pEvt->m_newTranslate->m_x = newTranslateX;
				pEvt->m_newTranslate->m_y = newTranslateY;

				CComQIPtr<ILDOMEventTarget> eventTarget = psvgsvgElement;
				ASSERT(eventTarget);

				bool doDefault;
				eventTarget->dispatchEvent(pEvt, &doDefault);
				if (doDefault)
				{
					psvgsvgElement->set_currentScale(pEvt->m_newScale);
					psvgsvgElement->m_currentTranslate->set_x(pEvt->m_newTranslate->m_x);
					psvgsvgElement->m_currentTranslate->set_y(pEvt->m_newTranslate->m_y);

					InvalidateRect(NULL);	// TODO remove
				}

				pEvt->Release();
#endif
			}
			else
			{
				if (m_pElementCapture)
				{
				//	MessageBeep(-1);
					m_pElementCapture->OnButtonUp(screenpt, clientpt, m_nhit);
				}
				else
				{
					if (m_htmTree)
					{
#if 0
						if (FALSE)//(TRUE)	// select event
						{
							CComQIPtr<ILDOMEventTarget> target = m_element;//svgsvgElement;

							CComQIPtr<ILDOMEventTarget> relatedTarget = m_element;//svgsvgElement;

							MouseEvent* pEvt;
						//	CComObject<CLDOMMouseEvent>::CreateInstance(&pEvt);
							if (pEvt)
							{
							//	pEvt->AddRef();

								pEvt->initMouseEvent(L"select",
									VARIANT_TRUE,	// bubbles
									VARIANT_TRUE,	// cancelable
									this,	// viewArg
									0,		// detail
									screenpt.x, screenpt.y,	// screen
									clientpt.x, clientpt.y, // client,	// TODO
									(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
									(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
									(m_bAlt)? VARIANT_TRUE: false,
									0,	// meta
									iButton,
									relatedTarget
									);

								bool doDefault;
								target->dispatchEvent(pEvt, &doDefault);

								pEvt->Release();
							}

							//if (m_pUI)
							//	m_pUI->m_document->Fire_onselect();
						}
#endif
						DocumentEvent* documentEvent = dynamic_cast<DocumentEvent*>(m_htmTree->m_pNode->get_ownerDocument());

						if (m_htmTree->m_pBox)
						{
							if (m_pPElementHover)
							{
								MouseEvent* mouseevt;
								mouseevt = dynamic_cast<MouseEvent*>(documentEvent->createEvent(WSTR("MouseEvents")));
								mouseevt->initMouseEvent(S("mouseup"),
									true,	// bubbles
									true,	// cancelable
									this,	// viewArg
									0,		// detail
									screenpt.X, screenpt.Y,	// screen
									clientpt.X, clientpt.Y, // client,
									/*(nFlags & MK_CONTROL)? true:*/ false,
									/*(nFlags & MK_SHIFT)? true:*/ false,
									/*(m_bAlt)? true:*/ false,
									0,	// meta
									0,
									NULL//relatedTarget
									);

								EventTarget* eventTarget = dynamic_cast<EventTarget*>(m_pPElementHover->m_pNode);
								bool doDefault = eventTarget->dispatchEvent(mouseevt);

								if (doDefault)
								{
									PElementBase* pPAElement = m_pPElementHover;
									do
									{
										System::String tagName = pPAElement->m_pNode->get_nodeName();
										if (tagName == L"a")
										{
											break;
										}

										pPAElement = pPAElement->m_parent;
									}
									while (pPAElement);

									if (pPAElement)
									{
										Web::Element* pAElement = dynamic_cast<Web::Element*>(pPAElement->m_pNode);

										String href = pAElement->getAttribute(S("href"));
										String target = pAElement->getAttribute(S("target"));

										ASSERT(0);
#if 0
										LinkEvent* evt = new LinkEvent;
										evt->InitEvent(WSTR("Link"), true, true);
										evt->m_href = href;
										evt->m_target = target;

										dispatchEvent(evt);
#endif
										/*
										if (m_pSite)
										{
											m_pSite->OnLink(href, target);
										}
										*/
									}
								}
							}
						}
#if 0
						else if (m_pSVGElement)
						{
							ASSERT(0);
#if 0
							CComQIPtr<ILSVGSVGElement> svgsvgElement = m_pSVGElement->m_pNode;

							/*
							<ILSVGMatrix> mat0;
							svgsvgElement->createSVGMatrix(&mat0);

							<ILSVGMatrix> mat1;
							mat0->scale(m_magnify, &mat1);

							<ILSVGMatrix> mat;
							mat1->translate(m_currentTranslateX, m_currentTranslateY, &mat);
							*/

					//		CPElement* pHitElement;
					//		BOOL b = m_pSVGElement->OnButtonDown(point, &pHitElement);
							//CPElement* pHitElement = NULL;
							//HitTestSVGElement(m_pSVGElement, svgsvgElement, mat, point.x, point.y, &pHitElement, NULL/*&pNode*/, NULL/*&offset*/);
							PSVGElement* pHitElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));

							if (pHitElement == NULL)
							{
								pHitElement = m_pSVGElement;	// ??
							}
							/*
							bool editMode;
							m_documentContainer->get_editMode(&editMode);

							*/

							<ILDOMDocument> document = m_pView->m_document;
							//m_frameElement->get_contentDocument(&document);

							CComQIPtr<ILDOMDocumentEvent> documentEvent = document;
							ASSERT(documentEvent != NULL);

							CComQIPtr<ILDOMElement> documentElement;
							document->get_documentElement(&documentElement);
					/*
					clientX and clientY parameters for mouse events represent viewport
					coordinates for the corresponding 'svg' element.

					relatedNode is the corresponding outermost 'svg' element
					*/

							CComQIPtr<ILDOMEventTarget> relatedTarget = documentElement;
							ASSERT(relatedTarget != NULL);

							<ILDOMMouseEvent> mouseevt;

							documentEvent->createEvent(L"MouseEvents", (ILDOMEvent**)&mouseevt);
							mouseevt->initMouseEvent(L"mouseup",
								VARIANT_TRUE,	// bubbles
								VARIANT_TRUE,	// cancelable
								m_pView,	// viewArg
								0,		// detail
								point.x, point.y,	// screen
								point.x, point.y, // client,
								(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
								(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
								(m_bAlt)? VARIANT_TRUE: false,
								0,	// meta
								0,
								relatedTarget
								);

							<ILDOMEventTarget> eventTarget = pHitElement->m_eventTarget;

							bool doDefault;
							eventTarget->dispatchEvent(mouseevt, &doDefault);

							if (doDefault)	// Not abolutely sure about this one, click event is canceled
							{
								if (m_pHitElement == pHitElement)
								{
									<ILDOMMouseEvent> mouseevt;

									documentEvent->createEvent(L"MouseEvents", (ILDOMEvent**)&mouseevt);
									mouseevt->initMouseEvent(L"click",
										VARIANT_TRUE,	// bubbles
										VARIANT_TRUE,	// cancelable
										m_pView,	// viewArg
										0,		// detail
										point.x, point.y,	// screen
										point.x, point.y, // client,
										(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
										(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
										(m_bAlt)? VARIANT_TRUE: false,
										0,	// meta
										0,
										relatedTarget
										);

									CComQIPtr<ILDOMEventTarget> eventTarget = pHitElement->m_pNode;

									bool doDefault;
									eventTarget->dispatchEvent(mouseevt, &doDefault);

									if (doDefault)
									{
										PElement* pPAElement = pHitElement;
										do
										{
											CComBSTR tagName;
											pPAElement->m_pNode->get_nodeName(&tagName);
											if (!tcscmp(tagName, L"a"))
											{
												break;
											}

											pPAElement = pPAElement->m_parent;
										}
										while (pPAElement);

										if (pPAElement)
										{
											ASSERT(0);
#if 0
											CLSVGAElement* psvgElement = static_cast<CLSVGAElement*>(pPAElement->m_pNode);

											CComBSTR url = (BSTR)psvgElement->m_href->m_animated->m_animVal->m_value->m_value;
											CComBSTR target = (BSTR)psvgElement->m_target->m_animated->m_animVal->m_value->m_value;

											if (url.Length())
											{
												WCHAR url2[4096];
												wcscpy(url2, url);

												WCHAR* id = NULL;
												int i = url.Length()-1;
												while (i >= 0)
												{
													if (url2[i] == L'#')
													{
														url2[i] = 0;
														id = &url2[i+1];
														break;
													}
													i--;
												}

												if (FALSE)//id)
												{
		#if 0
													<ILDOMElement> targetElement;
													m_document->getElementById(id, &targetElement);

													CComQIPtr<ILElementTime> elementTime = targetElement;
													if (elementTime)
													{
														double currentTime;
														svgsvgElement->getCurrentTime(&currentTime);

												/*
			1.
			If the target element is active, seek the document time back to the (current)
			begin time of the element. If there are multiple begin times, use the begin
			time that corresponds to the current "begin instance". 

												*/
														ASSERT(0);
			#if 0
														AnimationElementImpl<CLSVGAnimateElement>* pTargetElement = static_cast<CLAnimationElementImpl<CLSVGAnimateElement>*>(elementTime.p);

														pTargetElement->Hyperlink(svgsvgElement, currentTime);
			#endif

														if (pTargetElement->m_pCurrentInterval && pTargetElement->m_pCurrentInterval->m_bActive)
														{
														}
			/*
			2.
			Else if the target element begin time is resolved (i.e., there is any
			resolved time in the list of begin times, or if the begin time was forced
			by an earlier hyperlink or a beginElement() method call), seek the document
			time (forward or back, as needed) to the earliest resolved begin time of the
			target element. Note that the begin time may be resolved as a result of an
			earlier hyperlink, DOM or event activation. Once the begin time is resolved,
			hyperlink traversal always seeks. 
			*/
														else if (FALSE)
														{
														}
			/*
			3.
			Else (animation begin time is unresolved) just resolve the target animation
			begin time at current document time. Disregard the sync-base or event base
			of the animation, and do not "back-propagate" any timing logic to resolve
			the child, but rather treat it as though it were defined with
			begin="indefinite" and just resolve begin time to the current document time.
			*/
														else
														{
															double currentTime;
															svgsvgElement->getCurrentTime(&currentTime);

															pTargetElement->m_activeTime = currentTime;

															bool success;
															pTargetElement->beginElement(&success);
														}
													}
			#endif
												}
												else
												{
													ErrorCode hr;

													<IHlinkFrame> pHlinkFrame;

													CComQIPtr<IOleClientSite> pCS = m_pActiveDocument->m_spClientSite;//m_lpClientSite;
													CComQIPtr<IServiceProvider> pSP = pCS;
													if (pSP)
														pSP->QueryService(SID_SHlinkFrame, IID_IHlinkFrame, (void**)&pHlinkFrame);

													CComQIPtr<IOleDocumentSite> documentSite = pHlinkFrame;

													if (pHlinkFrame == NULL) // Try complicated way
													{
														CComQIPtr<IOleInPlaceSite> pIPS;
														if (m_pUI)
															pIPS = m_pUI->m_spInPlaceSite;//pCS;
														else
															pIPS = m_pActiveDocument->m_spInPlaceSite;//pCS;

														<IOleInPlaceFrame> pIPF;
														<IOleInPlaceUIWindow> pIPUI;
														RECT pos, clip;
														OLEINPLACEFRAMEINFO frameInfo;
														pIPS->GetWindowContext(&pIPF, &pIPUI, &pos, &clip, &frameInfo);
														pIPF->QueryInterface(IID_IHlinkFrame, (void**)&pHlinkFrame);
													}

													<IHlinkBrowseContext> bc = m_pActiveDocument->m_pHBC;
													//hr = HlinkCreateBrowseContext(NULL, IID_IHlinkBrowseContext, (void**)&bc);

													if (TRUE)
													{
														::HlinkSimpleNavigateToString(url, NULL, target, m_pActiveDocument->GetUnknown(), NULL, NULL, 0, 0);
														MessageBeep(-1);
													}
													else
													{
													//	m_pUI->m_document->m_pHBC = bc;

														<IMoniker> moniker;

												//		if (SUCCEEDED(hr))
														{
															<IBindCtx> bindctx;
														//	hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
															hr = CreateBindCtx(0, &bindctx);
															if (SUCCEEDED(hr))
															{
																hr = CreateURLMoniker(/*NULL*/m_pActiveDocument->m_curMoniker, url, &moniker);
															//	ULONG chEaten;
															//	hr = MkParseDisplayNameEx(bindctx, url, &chEaten, &moniker);
																ASSERT(SUCCEEDED(hr));

																/*
																PSTR rgszTypes[3] =
																{
																	"text/html",	// CFSTR_MIME_HTML
																	"image/svg+xml",
																	"text/plain",
																};

																CLSID rgclsID[3];
																rgclsID[0] = CLSID_LHTMLActiveDocument;
																rgclsID[1] = CLSID_LHTMLActiveDocument;
																rgclsID[2] = CLSID_LHTMLActiveDocument;

																hr = RegisterMediaTypeClass(bindctx, 3, rgszTypes, rgclsID, 0);
																*/

																//hr = ::HlinkSimpleNavigateToMoniker(moniker, NULL, NULL, m_pUI->m_document->GetUnknown(), bindctx, NULL/*this*/, 0/*HLNF_INTERNALJUMP*/, 0);
																	
																<IHlink> hlink;

																hr = HlinkCreateFromMoniker(
																	moniker,
																	NULL, // pwzLocation
																	L"test",	// friendlyName
																	this,//&hlsite,
																	1,	// siteData
																	NULL,
																	IID_IHlink,
																	(void**)&hlink);

																hlink->SetTargetFrameName(target);

																//hr = hlink->Navigate(0, bindctx, NULL, bc);
																hr = ::HlinkNavigate(hlink, pHlinkFrame, 0, bindctx, NULL, bc);
															}
														}
													}
												}
											}
#endif
										}
									}
								}
							}

	#if 0
							m_pHitElement = NULL;	// ??
	#endif
#endif
						}
#endif
					} // m_htmTree
				}
			}
		}
	}
}

bool CHTMLWindow::OnSetCursor(gm::PointI point)
{
#if 0
	if (m_dragging)
	{
		if (m_dragging == 3)	// panning
		{
			::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND2)));
			return TRUE;
		}
	}
	else
	{
		bool bCancel = FALSE;

		LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));
		LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

		PElement* pElement = NULL;

		if (m_htmTree->m_pBox)
		{
			pElement = m_htmTree->m_pBox->HitTestElementBox(point.x, point.y);
		}
		else if (m_pSVGElement)
		{
			ASSERT(0);
#if 0
			pElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));
#endif
		}

		if (pElement == NULL)
		{
			pElement = m_htmTree;
		}

		if (pElement)
		{
			CComQIPtr<ILDOMElement> documentElement;
			m_pView->m_document->get_documentElement(&documentElement);

#if 0
			CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
#endif

			/*
			<ILSVGMatrix> mat0;
			svgsvgElement->createSVGMatrix(&mat0);

			<ILSVGMatrix> mat1;
			mat0->scale(m_magnify, &mat1);

			<ILSVGMatrix> mat;
			mat1->translate(m_currentTranslateX, m_currentTranslateY, &mat);
			*/

			if (TRUE)
			{
				CComQIPtr<CLDOMElementImplImpl> elementImpl = pElement->m_pNode;

				for (int i = 0; i < elementImpl->m_behaviors.GetSize(); i++)
				{
					CComQIPtr<ILHTMLPainter> htmlPainter = elementImpl->m_behaviors[i]->m_factory;

					if (htmlPainter)
					{
						/*
						<ILCanvas> canvas;
						canvas.CoCreateInstance(CLSID_LCanvas);

						canvas->SetGdip((long)pC->m_pGraphics);
						*/

						ErrorCode hr = htmlPainter->SetCursor(point);
						if (hr == Success)
							return TRUE;
					}
				}
			}

#if 0
			for (int i = 0; i < m_pSVGElement->m_behaviors.GetSize(); i++)
			{
				CComQIPtr<ILHTMLPainter> painter = m_pSVGElement->m_behaviors[i]->m_p;
				if (painter)
				{
					ErrorCode hr = painter->SetCursor(point);
					if (hr == Success)
						return TRUE;
				}
			}
#endif

			if (TRUE)
			{
#if 0
				if (bCtrl)
				{
					HCURSOR hCursor;
					if (bShift)
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMOUT));
					else
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMIN));

					::SetCursor(hCursor);
					return TRUE;
				}
				else if (m_bAlt)
				{
					HCURSOR hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND0));
					::SetCursor(hCursor);
					return TRUE;
				}
#endif

				//CPElement* pElement = NULL;
				//HitTestSVGElement(m_pSVGElement, svgsvgElement, mat, point.x, point.y, &pElement, NULL/*&pNode*/, NULL/*&offset*/);
				HCURSOR hCursor = NULL;

				if (pElement->m_pCursorUriElement)
				{
					ASSERT(0);
#if 0
					CLSVGCursorElement* psvgelement = static_cast<CLSVGCursorElement*>(pElement->m_pCursorUriElement->m_pNode);

					hCursor = psvgelement->GetCursor();
#endif
				}
				else
				{
					switch (pElement->m_computedCursor)
					{
					case Cursor_auto:
						{
#if 0
							CComQIPtr<ILSVGTextElement> textElement;
							if (pElement)
								textElement = pElement->m_pNode;
							
							if (textElement)	// Over Text
							{
								hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTTEXTNS));
							}
							else
#endif
							{
								hCursor = ::LoadCursor(NULL, IDC_ARROW);
							}
						}
						break;
						
					case Cursor_crosshair:
						{
							hCursor = ::LoadCursor(NULL, IDC_CROSS);
						}
						break;
					case Cursor_default:
						{
							hCursor = ::LoadCursor(NULL, IDC_ARROW);
						}
						break;
					case Cursor_pointer:
						{
							hCursor = ::LoadCursor(NULL, IDC_HAND);
						}
						break;
					case Cursor_move:
						{
							hCursor = ::LoadCursor(NULL, IDC_SIZEALL);
						}
						break;
					case Cursor_e_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_E));
						}
						break;
					case Cursor_ne_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_NE));
						}
						break;
					case Cursor_nw_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_NW));
						}
						break;
					case Cursor_n_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_N));
						}
						break;
					case Cursor_se_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_SE));
						}
						break;
					case Cursor_sw_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_SW));
						}
						break;
					case Cursor_s_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_S));
						}
						break;
					case Cursor_w_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_W));
						}
						break;
					case Cursor_text:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTTEXTNS));
						}
						break;
					case Cursor_wait:
						{
							hCursor = ::LoadCursor(NULL, IDC_WAIT);
						}
						break;
					case Cursor_help:
						{
							hCursor = ::LoadCursor(NULL, IDC_HELP);
						}
						break;
					case Cursor_progress:
						{
						}
						break;
					case Cursor_copy:
						{
						}
						break;
					case Cursor_alias:
						{
						}
						break;
					case Cursor_context_menu:
						{
						}
						break;
					case Cursor_cell:
						{
						}
						break;
					case Cursor_all_scroll:
						{
						}
						break;
					case Cursor_col_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_COL));
						}
						break;
					case Cursor_row_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_ROW));
						}
						break;
					case Cursor_no_drop:
						{
						}
						break;
					case Cursor_not_allowed:
						{
							hCursor = ::LoadCursor(NULL, IDC_NO);
						}
						break;
					case Cursor_vertical_text:
						{
						}
						break;
					}
				}

				/*
				CComQIPtr<ILSVGTextElement> textElement;
				if (pElement)
					textElement = pElement->m_pNode;

				if (textElement)	// Over Text
				{
					SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTTEXTNS)));
					return TRUE;
				}
				*/

				if (hCursor)
				{
					::SetCursor(hCursor);
					return TRUE;
				}
			}
		}
	}
#endif
	return false;
}

#if WIN32

void CHTMLWindow::OnContextMenu(HWND hWnd, gm::PointD point)
{
#if 0
	CPoint pt = point;
	pt.x -= m_client.left;
	pt.y -= m_client.top;

	if (m_pSVGElement)
	{
		CComQIPtr<ILDOMDocumentEvent> documentEvent = m_pView->m_document;
		ASSERT(documentEvent != NULL);

		CComQIPtr<ILDOMElement> documentElement;
		m_pView->m_document->get_documentElement(&documentElement);

#if 0
		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
#endif

	//	bool editMode;
	//	m_documentContainer->get_editMode(&editMode);

		//<ILSVGMatrix> mat;
		//svgsvgElement->createSVGMatrix(&mat);

//		CPElement* pElement = NULL;
//		HitTestSVGElement(m_pSVGElement, svgsvgElement, mat, pt.x, pt.y, &pElement, NULL, NULL);
		ASSERT(0);
#if 0
		PSVGElement* pElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));

		if (pElement == NULL)
		{
			pElement = m_pSVGElement;
		}

		if (pElement)
		{
		//	m_pHitElement = NULL;
		//	BOOL b = pElement->OnButtonDown(point, &m_pHitElement);
		// Do something hm.. ??

	/*
	clientX and clientY parameters for mouse events represent viewport
	coordinates for the corresponding 'svg' element.

	relatedNode is the corresponding outermost 'svg' element
	*/

			CComQIPtr<ILDOMEventTarget> target = pElement->m_pNode;
			ASSERT(target != NULL);
			if (target)
			{
				CComQIPtr<ILDOMEventTarget> relatedTarget = svgsvgElement;
				ASSERT(relatedTarget != NULL);

				<ILDOMMouseEvent> mouseevt;

				documentEvent->createEvent(L"MouseEvents", (ILDOMEvent**)&mouseevt);
				mouseevt->initMouseEvent(L"contextmenu",
					VARIANT_TRUE,	// bubbles
					VARIANT_TRUE,	// cancelable
					m_pView,	// viewArg
					0,		// detail
					pt.x, pt.y,	// screen
					pt.x, pt.y, // client,	// TODO
					0,//(nFlags & MK_CONTROL)? VARIANT_TRUE: false,
					0,//(nFlags & MK_SHIFT)? VARIANT_TRUE: false,
					(/*m_pUI->*/m_bAlt)? VARIANT_TRUE: false,
					0,	// meta
					0,
					relatedTarget
					);

				bool doDefault;
				target->dispatchEvent(mouseevt, &doDefault);

				if (doDefault)
				{
					HMENU hMenu = ::LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_SVG));

					::TrackPopupMenu(GetSubMenu(hMenu, 0), TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, 0, m_cwnd, NULL);

					::DestroyMenu(hMenu);
				}
			}
		}
#endif
	}

#if 0
	CComObject<CMenuItem>* menu;
	CComObject<CMenuItem>::CreateInstance(&menu);
	if (menu)
	{
		menu->AddRef();

		BOOL b;
		menu->LoadMenu((long)_Module.GetResourceInstance(), IDR_LHTMLVIEW, &b);

		<IMenuItem> subMenu;
		menu->GetSubMenu(0, &subMenu);

		long selectedID;
		subMenu->PopupMenu(this, point, 0, &selectedID);

		menu->Release();
	}
#endif
#endif
}
#endif

#if 0
long CHTMLWindow::SetElement(ILDOMElement* element)
{
	ASSERT(0);
#if 0
	ASSERT(element);	// A CHTMFrame must have a valid document/root element (?)
	if (m_element != element)	// TODO, better comparison ??
	{
		FreeImage();

		m_element = element;

		if (m_element)
		{
			m_element->get_ownerDocument(&m_document);

			CComQIPtr<CLDOMDocumentImplImpl>(m_document)->AddView(this);

			CComQIPtr<INotifySend> cp = m_document;
			ASSERT(cp);
			DWORD cookie;
			cp->Advise(this, &cookie);

			DoneParsing();
		}

		if (m_pUI)
		{
			if (m_pUI->m_hWnd)
			{
				m_pUI->InvalidateRect(NULL, TRUE);
			}
		}
	}
#endif
	return 0;
}
#endif

#if 0
// Setup script, after the document object has been created, but before it is loaded
void CHTMLWindow::PrepareScripting()
{
	ASSERT(0);
#if 0

		/* ?? TODO

		  For each OBJECT element in the document, call this (if not here, then somewhere)

		  hr = m_activeScript = AddTypeLib(
			 REFGUID guidTypeLib,  // CLSID of type library
			 DWORD dwMaj,          // major version number
			 DWORD dwMin,          // minor version number
			 DWORD dwFlags         // option flags
		);

		*/
	}
#endif
}
#endif

#if 0
void AddScriptlet(IActiveScriptParse* activeScript, BSTR id, BSTR event, BSTR code)
{
	BSTR actualScriptletName = NULL;
	EXCEPINFO excepinfo = {0};

	ErrorCode hr = activeScript->AddScriptlet(
		NULL,// address of default name of scriptlet
		code,          // address of scriptlet text
		id, // address of item name
		NULL, // address of subitem name
		event,//L"onmousedown(evt)",// address of event name
		L"",//NULL,// address of end-of-scriptlet delimiter
		0L,// application-defined value for debugging
		0,// starting line of the script
		0,//SCRIPTTEXT_ISVISIBLE ,// ???????DWORD dwFlags,               // scriptlet flags
		&actualScriptletName,             // address of actual name of scriptlet
		&excepinfo        // address of exception information
		);
	if (FAILED(hr))
	{
		MessageBox(NULL, "failed to add scriptlet", "JScript", MB_OK);
	}

	ATLTRACE("\nactualScriptName: %S\n\n", actualScriptletName);
	SysFreeString(actualScriptletName);
}

void AddScriptlets(IActiveScriptParse* activeScript, ILDOMElement* element)
{
	BSTR bid;
	element->getAttribute(L"id", &bid);
	_bstr_t id = _bstr_t(bid, false);

	BSTR bcode;
	_bstr_t code;

	/*
	element->getAttribute(L"onload", &bcode);
	code = _bstr_t(bcode, false);
	if (code.length())
	{
		AddScriptlet(activeScript, id, L"onload", code);
	}
	*/

	element->getAttribute(L"onmousedown", &bcode);
	code = _bstr_t(bcode, false);
	if (code.length()) AddScriptlet(activeScript, id, L"onmousedown", code);

	element->getAttribute(L"onchange", &bcode);
	code = _bstr_t(bcode, false);
	if (code.length()) AddScriptlet(activeScript, id, L"onchange", code);

	element->getAttribute(L"onclick", &bcode);
	code = _bstr_t(bcode, false);
	if (code.length()) AddScriptlet(activeScript, id, L"onclick", code);

	ILDOMNode* child;
	element->get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);
		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> childelement = child;
			AddScriptlets(activeScript, childelement);
		}

		CComQIPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}
#endif

#if 0
void CHTMLWindow::AddNamedElements(IActiveScript* script, ILDOMElement* parent)
{
	CComQIPtr<ILDOMNode> node;
	parent->get_firstChild(&node);
	while (node != NULL)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			BSTR bid;
			element->getAttribute(L"id", &bid);
			_bstr_t id = _bstr_t(bid, false);
			if (id.length() > 0)
			{
				script->AddNamedItem(id, SCRIPTITEM_ISVISIBLE | SCRIPTITEM_ISSOURCE);

				CNamedItem item;
				item.m_name = id;
				CComQIPtr<IDispatch> elementdisp = element;
				item.m_pDisp = elementdisp;
				m_namedItems.Add(item);
			}

			AddNamedElements(script, element);
		}

		CComQIPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}
#endif


//void BuildAnimationListForAllElements(ILDOMElement* element, ILDOMElement* svgElement);

//#include "C:\Program Files\Microsoft Speech SDK 5.1\Include\sapi.h"
//#pragma comment(lib, "C:\\Program Files\\Microsoft Speech SDK 5.1\\Lib\sapi.lib")


	#if 0
					if (!editMode)
					{
						CComQIPtr<IActiveScriptParse> activeScriptParse = m_activeScript;

						AddScriptlets(activeScriptParse, documentElement);

					// window events ?
						AddScriptlet(activeScriptParse, L"globalwindow2", L"onload", L"OnLoad()");

					// force the engine to connect any outbound interfaces to the 
					// host's objects
						ErrorCode hr = m_activeScript->SetScriptState(SCRIPTSTATE_CONNECTED);
						ASSERT(SUCCEEDED(hr));

						// Start playing document
						{
							m_totalIntendedTime = 0;

							LONG uDelay = (LONG)(1000/m_frameRate);

							m_videoTimeID = timeSetEvent(uDelay, 0, (LPTIMECALLBACK)PlaybackProc, (DWORD)this, TIME_PERIODIC);

							if (!m_videoTimeID)
							{
							//	m_bPlaying = FALSE;
							//	UpdateAllViews(NULL);

								MessageBox(NULL, "Video playback Timer could not be created", "", MB_OK);
							}
						}
					}
					else
	#endif

#if 0
void CHTMLWindow::DrawCursor(UI::Graphics* pGraphics, PNode* pItem, int offset, bool bStippled /* = false */)
{
	if (pItem)
	{
		CPTextNodeBase* pTextNode = dynamic_cast<CPTextNodeBase*>(pItem);
		if (pTextNode)
		{
			LDraw::PointD pos;
			double height;
			LDraw::matrix3f mat0;
			bool b = pTextNode->GetCursorPosition(offset, &pos, &height, &mat0);

			LDraw::matrix3f mat = mat0/* *
								gmMatrix3::scale(m_magnify, m_magnify) *
								gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY)*/;

			if (b)
			{
				if (!bStippled)
				{
#if 0
					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

					HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
#endif

					LDraw::vector2f v0 = mat.transform(LDraw::vector2f(pos.X, pos.Y));
					LDraw::vector2f v1 = mat.transform(LDraw::vector2f(pos.X, pos.Y+height));

				//	MoveToEx(hDC, v0[0], v0[1], NULL);
				//	LineTo(hDC, v1[0], v1[1]);

					pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0,0,0), 2), v0[0], v0[1], v1[0], v1[1]);
#if 0
					SelectObject(hDC, hOldPen);
					DeleteObject(hPen);

					SetROP2(hDC, oldR2);
#endif
				}
				else
				{
					ASSERT(0);
#if 0
					RECT frc = {pos.X, pos.Y, pos.X+2, pos.Y+height};
					DrawFocusRect(hDC, &frc);
#endif
				}
			}
			else
			{
#if 0
#ifdef DEBUG
				// Find out where why
				long wordoffset;
				CHTMPCharacterBox* pCharBox = pTextNode->GetWordAtCursorPos(offset, wordoffset);
				ASSERT(0);
#endif
#endif
			}
		}
	}
}
#endif

void CHTMLWindow::ToggleCursor()
{
	m_bShowCursor = !m_bShowCursor;
//	DrawCursor(m_curContainer, m_curOffset);
	ASSERT(0);
#if 0
	Invalidate();
#endif
}

void CHTMLWindow::ShowCursor()
{
	if (!m_bShowCursor)
	{
		ToggleCursor();
	}
}

void CHTMLWindow::HideCursor()
{
	if (m_bShowCursor)
	{
		ToggleCursor();
	}
}

#if 0

void CHTMLWindow::MoveCursorLeft()
{
	ASSERT(0);
#if 0
	if (m_cursorItem)
	{
		if (m_cursorOffset == 0)
		{
			if (m_cursorItem->m_parent)
			{
				CPNode* pPrevNode = m_cursorItem->GetPrevNode();
				if (pPrevNode)
				{
					m_cursorItem = pPrevNode;

					CComQIPtr<ILDOMText> prevText = pPrevNode->m_pNode;
					if (prevText)
					{
						unsigned long textlength;
						prevText->get_dataLength(&textlength);
						m_cursorOffset = textlength;
					}
					else
						m_cursorOffset = 0;
				}
			}
		}
		else
		{
			m_cursorOffset--;
		}
	}
#endif
}

void CHTMLWindow::MoveCursorRight()
{
	ASSERT(0);
#if 0
	if (m_cursorItem)
	{
		CComQIPtr<IDOMText> text = m_cursorItem->m_pNode;

		unsigned long textlength;
		text->get_dataLength(&textlength);

		ASSERT(m_cursorOffset <= textlength);

		if (m_cursorOffset == textlength-1) // hm?? -1 ??
		{
			ASSERT(0);
		/* Have this
			UPOSITION pos = m_cursorItem->m_parent->m_childList.Find(m_cursorItem);
			m_cursorItem->m_parent->m_childList.GetNext(pos);
			m_cursorItem = (CHTMPItem*)m_cursorItem->m_parent->m_childList.GetAt(pos);

			m_cursorOffset = 0;
			*/
		}
		else
		{
			m_cursorOffset++;
		}
	}
#endif
}
#endif


///////////////////////////////////////////////////////////////////

int CompareTreePosition(Node* pThis, Node* pNode);

enum
{
	tomCharacter	= 1,
	tomWord	= 2,
	tomSentence	= 3,
	tomParagraph	= 4,
	tomLine	= 5,
};

Node* RightMost(Node* node, long& offset)
{
	Node* lastChild = node->get_lastChild();

	if (lastChild)
	{
		return RightMost(lastChild, offset);
	}

	CharacterData* text = dynamic_cast<CharacterData*>(node);
	if (text)
	{
		offset = text->get_length();
	}
	else
		ASSERT(0);

	return node;
}

Node* PreviousTextOrNonEmptyElement(Node* node)
{
	bool hasChildNodes;
	NodeType nodeType;

	Node* previousSibling = node->get_previousSibling();

	if (previousSibling)
	{
		nodeType = previousSibling->get_nodeType();
		hasChildNodes = previousSibling->hasChildNodes();
	}

	while (previousSibling && (nodeType == NODE_ELEMENT && !hasChildNodes))
	{
		previousSibling = previousSibling->get_previousSibling();

		if (previousSibling)
		{
			nodeType = previousSibling->get_nodeType();
			hasChildNodes = previousSibling->hasChildNodes();
		}
	}

	if (previousSibling)
		return previousSibling;
	else
		return NULL;
}

ErrorCode MoveCursorLeft(Node* startContainer, Node* topMostParent, long startOffset, Node* *container, long* offset)
{
	if (startOffset > 0)	// Moving within the same text node
	{
		*container = startContainer;
		*offset = startOffset-1;

		return Success;
	}
	else
	{
		Node* node;
		node = startContainer;

		Node* previousSibling = PreviousTextOrNonEmptyElement(node);

		while (previousSibling == NULL)
		{
			node = node->get_parentNode();
			if (node == topMostParent) break;

			previousSibling = PreviousTextOrNonEmptyElement(node);
		}

		if (previousSibling)
		{
			node = RightMost(previousSibling, startOffset);

			*container = node;
			*offset = startOffset-1;

			return Success;
		}
	}

	return Success_False;
}

Node* LeftMost(Node* node, int& offset)
{
	Node* firstChild = node->get_firstChild();

	if (firstChild)
	{
		return LeftMost(firstChild, offset);
	}

	CharacterData* text = dynamic_cast<CharacterData*>(node);
	if (text)
	{
		offset = 0;
	}
	else
		ASSERT(0);

	return node;
}

Node* NextTextOrNonEmptyElement(Node* node)
{
	bool hasChildNodes;
	NodeType nodeType;

	Node* nextSibling = node->get_nextSibling();

	if (nextSibling)
	{
		nodeType = nextSibling->get_nodeType();
		hasChildNodes = nextSibling->hasChildNodes();
	}

	while (nextSibling && (nodeType == NODE_ELEMENT && !hasChildNodes))
	{
		nextSibling = nextSibling->get_nextSibling();

		if (nextSibling)
		{
			nodeType = nextSibling->get_nodeType();
			hasChildNodes = nextSibling->hasChildNodes();
		}
	}

	if (nextSibling)
		return nextSibling;
	else
		return NULL;
}

ErrorCode MoveCursorRight(Node* startContainer, Node* topMostParent, int startOffset, Node** container, int* offset)
{
	CharacterData* text = dynamic_cast<CharacterData*>(startContainer);
	String data = text->get_data();

	if (startOffset < data.GetLength())
	{
		*container = startContainer;
		*offset = startOffset+1;

		return Success;
	}
	else
	{
		Node* node;
		node = startContainer;

		Node* nextSibling = NextTextOrNonEmptyElement(node);

		while (nextSibling == NULL)
		{
			node = node->get_parentNode();
			if (node == topMostParent) break;

			nextSibling = NextTextOrNonEmptyElement(node);
		}

		if (nextSibling)
		{
			node = LeftMost(nextSibling, startOffset);

			*container = node;
			*offset = startOffset+1;

			return Success;
		}
	}

	return Success_False;
}

void CHTMLWindow::ExtendIt(Node* container, int offset, int bShift)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;

// Dectivate previous range
//	uiManager->DeactivateObject(m_range);

	if (bShift)
	{
		Node* startContainer;
		int startOffset;

		Node* endContainer;
		int endOffset;

		if (container == m_initContainer->m_pNode)	// start and end share container
		{
			startContainer = container;
			endContainer = container;

			if (offset < m_initOffset)
			{
				startOffset = offset;
				endOffset = m_initOffset;
			}
			else
			{
				startOffset = m_initOffset;
				endOffset = offset;
			}
		}
		else
		{
			int cmp = CompareTreePosition(container, m_initContainer->m_pNode);
			ASSERT(cmp != 0);

			if (cmp == -1)
			{
				startContainer = container;
				startOffset = offset;

				endContainer = m_initContainer->m_pNode;
				endOffset = m_initOffset;
			}
			else
			{
				startContainer = m_initContainer->m_pNode;
				startOffset = m_initOffset;

				endContainer = container;
				endOffset = offset;
			}
		}

		m_range->setStart(startContainer, startOffset);
		m_range->setEnd(endContainer, endOffset);
	}
	else
	{
		m_initContainer = container->m_pNode;//m_htmTree->FindDOMElement(container);
		m_initOffset = offset;

		m_range->setStart(container, offset);
		m_range->setEnd(container, offset);
	}

	m_curContainer = container->m_pNode;//m_htmTree->FindDOMElement(container);
	m_curOffset = offset;
	ASSERT(m_curOffset >= 0);

	// Activate new range
//	uiManager->ActivateObject(GetUnknown(), m_range);
}

void CHTMLWindow::TypeText(StringIn str)
{
	if (m_range)
	{
		Node* startContainer = m_range->get_startContainer();
		int startOffset = m_range->get_startOffset();

		Text* text = dynamic_cast<Text*>(startContainer);
		if (text)
		{
			text->insertData(startOffset, str);

			MoveRight(tomCharacter, 1, 0, NULL);
		}
		else
			THROW(-1);
	}
	else
		THROW(-1);
}

#if 0
ErrorCode GetTopMostTextContentElement(ILDOMNode* node, ILDOMNode* *pVal)
{
	<ILDOMNode> node2 = node;
	while (node2)
	{
		<ILDOMNode> parentNode;
		node2->get_parentNode(&parentNode);

		ASSERT(0);

#if 0
		CComQIPtr<ILSVGTextContentElement> textContent = parentNode;
		if (textContent == NULL)
		{
			break;
		}
#endif

		node2 = parentNode;
	}

	ASSERT(node2);

	*pVal = node2;
	(*pVal)->AddRef();
	return Success;
}
#endif

ErrorCode CHTMLWindow::Delete(/*[in]*/ long Unit, /*[in]*/ long Count, /*[out,retval]*/ long* pDelta)
{
//	CPDTextRangeImpl<IPDTextSelection>::Delete(Unit, Count, pDelta);
	{
		if (Count == 0)	// Delete all characters in range
		{
			m_range->deleteContents();
		}
		else
		{
			Node* m_curContainer;
			long m_curOffset;

			m_curContainer = m_range->get_startContainer();
			m_curOffset = m_range->get_startOffset();
			ASSERT(m_curOffset >= 0);

			if (Count > 0)	// Delete
			{
				Node* topMost = m_htmTree->m_pNode;
				//GetTopMostTextContentElement(m_curContainer, &topMost);

				Node* container;
				int offset;
				if (MoveCursorRight(m_curContainer, topMost, m_curOffset, &container, &offset) == Success)
				{
					m_range->setEnd(container, offset);
					m_range->deleteContents();

					/*
					m_curContainer = container;
					m_curOffset = offset;
					m_initContainer = container;
					m_initOffset = offset;
					*/
				}
			}
			else	// Backspace
			{
				Node* topMost = m_htmTree->m_pNode;
			//	<ILDOMNode> topMost;
			//	GetTopMostTextContentElement(m_curContainer, &topMost);

				Node* container;
				long offset;
				if (MoveCursorLeft(m_curContainer, topMost, m_curOffset, &container, &offset) == Success)
				{
					m_range->setStart(container, offset);
					m_range->deleteContents();
	/*
					m_range->Set(
					m_curContainer = container;
					m_curOffset = offset;
					m_initContainer = container;
					m_initOffset = offset;
					*/
				}
			}
		}
	}

	ChildNode* startContainer = dynamic_cast<ChildNode*>(m_range->get_startContainer());
	int startOffset = m_range->get_startOffset();
	m_curContainer = startContainer->m_pNode;
	m_curOffset = startOffset;
	ASSERT(m_curOffset >= 0);

	m_initContainer = startContainer->m_pNode;//m_htmTree->FindDOMElement(startContainer);
	m_initOffset = startOffset;
	ASSERT(m_initOffset >= 0);

	return Success;
}

ErrorCode CHTMLWindow::MoveRight(long Unit, long Count, long Extend, long *pDelta)
{
	Node* topMost = m_htmTree->m_pNode;
	//GetTopMostTextContentElement(m_curContainer->m_pNode, &topMost);

	Node* container;
	int offset;
	if (MoveCursorRight(m_curContainer->m_pNode, topMost, m_curOffset, &container, &offset) == Success)
	{
		ExtendIt(container, offset, Extend);

		int wordOffset;
		CHTMPCharacterBox* pWord = dynamic_cast<PText*>(m_curContainer)->GetWordAtCursorPos(m_curOffset, wordOffset);
		scrollIntoView(pWord);
	}

	return Success;
}

ErrorCode CHTMLWindow::MoveLeft(long Unit, long Count, long Extend, long *pDelta)
{
	Node* topMost = m_htmTree->m_pNode;
//	Node* topMost;
//	GetTopMostTextContentElement(m_curContainer->m_pNode, &topMost);

	Node* container;
	long offset;
	if (MoveCursorLeft(m_curContainer->m_pNode, topMost, m_curOffset, &container, &offset) == Success)
	{
		ExtendIt(container, offset, Extend);
	}

	return Success;
}

#if 0
void InsertFocusElement(ILDOMElement* element, CUPtrList& list)
{
	list.AddTail(element);
}

void BuildFocusList(ILDOMElement* element, CUPtrList& list)
{
	<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element2 = node;
		if (element2)
		{
			CComBSTR tagName;
			element2->get_tagName(&tagName);

			if (!tcscmp(tagName, L"a"))
			{
				InsertFocusElement(element2, list);
			}

			BuildFocusList(element2, list);
		}

		<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}
#endif

#if 0

#include <ocidl.h>

HDC CHTMLWindow::GetDC()
{
	ASSERT(0);
	return NULL;
#if 0	// Had this
	if (m_pUI)
	{
		return m_pUI->GetDC();
	}
	else
	{
		ASSERT(m_pActiveDocument->m_hWnd == NULL);

//		CRect rect = m_imageRect;
//		rect.OffsetRect(m_pActiveDocument->m_rcPos.left, m_pActiveDocument->m_rcPos.top);

		HDC hDC;
		ErrorCode hr = m_pActiveDocument->m_spInPlaceSite->GetDC(NULL/*&rect*/, OLEDC_NODRAW, &hDC);
		if (FAILED(hr))
		{
//			if (hr == OLE_E_NESTEDPAINT)
			{
				ASSERT(0);
			}
		}

		ASSERT(hDC);

		OffsetViewportOrgEx(hDC, m_pActiveDocument->m_rcPos.left, m_pActiveDocument->m_rcPos.top, NULL);

		return hDC;
	}
#endif
}

void CHTMLWindow::ReleaseDC(HDC hDC)
{
	ASSERT(0);
#if 0	// Had this
	if (m_pUI)
	{
		m_pUI->ReleaseDC(hDC);
	}
	else
	{
		m_pActiveDocument->m_spInPlaceSite->ReleaseDC(hDC);
	}
#endif
}

void CHTMLWindow::ScreenToClient(CPoint* ppoint)
{
	ASSERT(0);
#if 0	// Had this
	if (m_pUI)
	{
		m_pUI->ScreenToClient(ppoint);
	}
	else
	{
		HWND hwnd;
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);

		::ScreenToClient(hwnd, ppoint);

		ppoint->x -= m_pActiveDocument->m_rcPos.left;
		ppoint->y -= m_pActiveDocument->m_rcPos.top;
	}
#endif
}
#endif

///////////////////////////////////////////////////////////////////

void CHTMLWindow::OnKeyDown(Gui::RoutedEventArgs* evt)
{
#if 0
#if WIN32
	long nKey = evt->vk;
#if 0
	if (nKey == VK_DELETE)
		virtKey = DOM_VK_DELETE;

	CComQIPtr<ILDOMDocumentEvent> documentEvent = m_pView->m_document;
	ASSERT(documentEvent != NULL);

	CComQIPtr<ILDOMElement> documentElement;
	m_pView->m_document->get_documentElement(&documentElement);

	CComQIPtr<ILDOMEventTarget> relatedTarget = documentElement;
	ASSERT(relatedTarget != NULL);

	<ILTextEvent> textevt;

	documentEvent->createEvent(L"TextEvent", (ILDOMEvent**)&textevt);
	textevt->initTextEvent(
		L"keydown",	// typeArg
		VARIANT_TRUE,	// canBubbleArg
		VARIANT_TRUE,	// cancelableArg
		this,	// viewArg
		0,		// detailArg
		NULL,	// outputStringArg
		nKey,	// keyValArg
		virtKey,	// virtKeyValArg
		false,	// visibleOutputGeneratedArg
		false	// numPadArg
		);
	textevt->initModifier(DOM_VK_LEFT_ALT, m_bAlt);

	bool doDefault = VARIANT_TRUE;
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
	if (svgsvgElement)
	{
		CComQIPtr<ILDOMEventTarget> eventTarget = svgsvgElement;

		eventTarget->dispatchEvent(textevt, &doDefault);
	}
#endif
#endif

//	if (doDefault)
	{
#if WIN32
		LONG bCtrl = (MSWindows::GetAsyncKeyState(VK_CONTROL) & (1<<15));
		LONG bShift = (MSWindows::GetAsyncKeyState(VK_SHIFT) & (1<<15));
#endif

#if 0
		if (svgsvgElement)
		{
			//if (m_bAlt)
			{
				CPoint point;
				GetCursorPos(&point);
				ScreenToClient(&point);

				OnSetCursor(/*HTCLIENT, 0,*/ point);
			}
		}
		else
#endif
		{
		//	HideCursor();

#if 0
			if (nKey == VK_TAB)
			{
				Element> documentElement;
				m_pView->m_document->get_documentElement(&documentElement);

				CUPtrList list;
				BuildFocusList(documentElement, list);

				PElement* pElement = NULL;

				if (m_pPElementFocus)
				{
					UPOSITION pos = list.Find(m_pPElementFocus->m_pNode);
					ASSERT(pos);

					if (!bShift)
					{
						list.GetNext(pos);
						if (pos == NULL)	// Wrap to beginning
						{
							pos = list.GetHeadPosition();
						}
					}
					else
					{
						list.GetPrev(pos);

						if (pos == NULL)	// Wrap to end
						{
							pos = list.GetTailPosition();
						}
					}

					if (pos)
					{
						ILDOMElement* element = (ILDOMElement*)list.GetAt(pos);

						pElement = (CPElement*)m_htmTree->FindDOMElement(element);
					}
				}
				else
				{
					// First
					if (!list.IsEmpty())
					{
						pElement = (CPElement*)m_htmTree->FindDOMElement((ILDOMNode*)list.GetHead());
					}
				}

				if (m_pPElementFocus != pElement)
				{
					if (m_pPElementFocus)
					{
						m_pPElementFocus->m_bFocus = false;
						m_pPElementFocus->m_bActive = false;
						m_pPElementFocus->GetCSSPropertiesAndChildren();
					}

					m_pPElementFocus = pElement;

					if (m_pPElementFocus)
					{
						m_pPElementFocus->m_bFocus = true;
						m_pPElementFocus->m_bActive = true;
						m_pPElementFocus->GetCSSPropertiesAndChildren();

						scrollIntoView(m_pPElementFocus);
					}

					Flow();	// hm.. optimize this somehow

					InvalidateRect(NULL);	// TODO ?
				}
			}
			else if (nKey == VK_RETURN)
			{
				if (m_pPElementFocus)
				{
					CComQIPtr<ILDOMElement> element = m_pPElementFocus->m_pNode;

					CComBSTR href;
					element->getAttribute(L"href", &href);

					TCHAR absurl[2048];
					{
						CComBSTR documentUrl;
						m_pView->m_document->get_url(&documentUrl);

						DWORD resultLen = sizeof(absurl);
						InternetCombineUrl(_bstr_t(documentUrl), _bstr_t(href), absurl, &resultLen, 0);
					}

					GotoLocation(_bstr_t(absurl));
				}
			}
			else
#endif
			{
				if (m_curContainer)
				{
					switch (nKey)
					{
					case VK_LEFT:
						{
							MoveLeft(bCtrl? tomWord: tomCharacter, 1, bShift, NULL);
						}
						break;

					case VK_RIGHT:
						{
							MoveRight(bCtrl? tomWord: tomCharacter, 1, bShift, NULL);
						}
						break;

					case VK_BACK:
					case VK_DELETE:
						{
							bool bCollapsed = m_range->get_collapsed();
							if (bCollapsed)
							{
								if (nKey == VK_BACK)
								{
									Delete(tomCharacter, -1, NULL);
								}
								else
								{
									Delete(tomCharacter, 1, NULL);
								}

							//	m_pUI->Invalidate();	// TODO remove
							}
							else
							{
								Delete(tomCharacter, 0, NULL);
								//ClearSelection();
							}
						}
						break;
			#if 0
					case VK_UP:
					case VK_DOWN:
					case VK_HOME:
					case VK_END:
					case VK_PRIOR:
					case VK_NEXT:
						{
							/*
							if (bShift)
							{
								if (m_initSel == -1)	// Starting new selection
								{
									m_initSel = m_offset;
								}
							}
							else
							{
								ClearSelectionAndInvalidate();
							}
				*/
							switch (nKey)
							{
							case VK_LEFT:	MoveCursorLeft(); break;
							case VK_RIGHT:	MoveCursorRight(); break;
						//	case VK_UP:		MoveCursorUp(); break;
						//	case VK_DOWN:	MoveCursorDown(); break;
						//	case VK_HOME:	MoveCursorBegLine(); break;
						//	case VK_END:	MoveCursorEndLine(); break;
						//	case VK_PRIOR:	MoveCursorPageUp(); break;
						//	case VK_NEXT:	MoveCursorPageDown(); break;
							}
				/*
							if (bShift)
							{
								SetSelectionAndInvalidate(m_initSel, m_offset);
							}
							*/
						}
						break;

					case VK_BACK:
						{
							MoveCursorLeft();
						}
						// Fall through

					case VK_DELETE:
						{
							PText* pPText = (PText*)m_cursorItem;

							CComQIPtr<ILDOMText> text = pPText->m_pNode;
							ASSERT(text);

							// Update DOM and Source
							text->deleteData(m_cursorOffset, 1);

							if (pPText->m_text.GetLength() == 1)
							{
							// Delete the current item
								POSITION thispos = pPText->m_parent->m_childList.Find(pPText);
								POSITION nextpos = thispos;
								pPText->m_parent->m_childList.GetNext(nextpos);
								PText* pPNextText = (PText*)pPText->m_parent->m_childList.GetAt(nextpos);

								m_cursorItem = pPNextText;
								m_cursorOffset = 0;//pPNextText->m_text.GetLength();

								((CHTMPElement*)pPNextText->m_parent)->MoveTextOffsets(thispos, -1);

								// Remove and delete this item
								pPNextText->m_parent->m_childList.RemoveAt(thispos);
								delete pPText;
							}
							else if (m_cursorOffset == pPText->m_text.GetLength())
							{
							// Join this item with next

							// Update Render
								POSITION thispos = pPText->m_parent->m_childList.Find(pPText);
								POSITION nextpos = thispos;
								pPText->m_parent->m_childList.GetNext(nextpos);
								PText* pPNextText = (PText*)pPText->m_parent->m_childList.GetAt(nextpos);

							//	m_cursorItem = pPNextText;
							//	m_cursorOffset = pPText->m_text.GetLength();

								pPText->m_text += pPNextText->m_text;

								// Remove and delete next item
								pPText->m_parent->m_childList.RemoveAt(nextpos);
								delete pPNextText;

								((CHTMPElement*)pPText->m_parent)->MoveTextOffsets(thispos, -1);
							}
							else	// In the middle of a word
							{
								POSITION thispos = pPText->m_parent->m_childList.Find(pPText);

							//	m_cursorOffset--;
								pPText->m_text.Delete(m_cursorOffset, 1);

								((CHTMPElement*)pPText->m_parent)->MoveTextOffsets(thispos, -1);
							}
						}
						break;
				#endif

					default:
						return;
					}
				}
			}

		//	ScrollIntoView(m_line, m_col);

		//	ShowCursor();
			Invalidate();
		}
	}
#endif
#endif
}

void CHTMLWindow::OnKeyUp(int nKey, int lKeyData)
{
#if 0
	{
		long virtKey = 0;
		if (nKey == VK_DELETE)
			virtKey = DOM_VK_DELETE;

		CComQIPtr<ILDOMDocumentEvent> documentEvent = m_pView->m_document;
		ASSERT(documentEvent != NULL);

		CComQIPtr<ILDOMElement> documentElement;
		m_pView->m_document->get_documentElement(&documentElement);

		CComQIPtr<ILDOMEventTarget> relatedTarget = documentElement;
		ASSERT(relatedTarget != NULL);

		<ILTextEvent> textevt;
	
		documentEvent->createEvent(L"TextEvent", (ILDOMEvent**)&textevt);
		textevt->initTextEvent(
			L"keyup",	// typeArg
			VARIANT_TRUE,	// canBubbleArg
			VARIANT_TRUE,	// cancelableArg
			this,	// viewArg
			0,		// detailArg
			NULL,	// outputStringArg
			nKey,	// keyValArg
			virtKey,	// virtKeyValArg
			false,	// visibleOutputGeneratedArg
			false	// numPadArg
			);
		textevt->initModifier(DOM_VK_LEFT_ALT, m_bAlt);

		ASSERT(0);
#if 0
		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
		if (svgsvgElement)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = svgsvgElement;

			bool doDefault;
			eventTarget->dispatchEvent(textevt, &doDefault);

			if (doDefault)
			{
				if (svgsvgElement)
				{
					//if (m_bAlt)
					{
						CPoint point;
						GetCursorPos(&point);
						ScreenToClient(&point);

						OnSetCursor(/*HTCLIENT, 0,*/ point);
					}
				}
			}
		}
#endif
	}
#endif
}

void CHTMLWindow::OnChar(Gui::RoutedEventArgs* evt)
{
#if 0
#if 0
	if (nKey == 8) return;
	if (nKey == '\r') nKey = '\n';
#endif

	WCHAR c2[2] = {evt->cCharCode, 0};
	TypeText(new StringW(string_copy(c2)));

#if 0
	if (m_cursorItem)
	{
		PText* pPText = (PText*)m_cursorItem;

		if (nKey == '\n')
		{
#if 0
// Hard RETURN, Put 
			CHTMPElement* pPParent = (CHTMPElement*)m_cursorItem->m_parent;
			CHTMElement* pParent = (CHTMElement*)pPParent->m_pNode;

			CHTMText* pText = (CHTMText*)pPText->m_pNode;

			int len = pText->m_text.GetLength();

		// Split the Text
			CHTMText* pNewText = new CHTMText;
			pNewText->m_HTM = m_pDocument;
			pNewText->m_text = pText->m_text.Right(len - pPText->m_charOffset);

			pText->m_text = pText->m_text.Left(pPText->m_charOffset);

		// Create a new P tag
			CHTMElement* pTag = m_pDocument->createElement("P");

			if (!stricmp(pParent->m_tagName, "P"))
			{
				POSITION pos = pParent->m_pParent->m_childList.Find(pParent);
				pParent->m_pParent->m_childList.InsertAfter(pos, pTag);
				pTag->m_pParent = pParent->m_pParent;
			}
			else
			{
				POSITION pos = pText->m_pParent->m_childList.Find(pText);
				pText->m_pParent->m_childList.InsertAfter(pos, pTag);
				pTag->m_pParent = pText->m_pParent;
			}

		// Add the right side of the split text to the new P tag
			pTag->m_childList.AddTail(pNewText);
			pNewText->m_pParent = pTag;

			pTag->m_pParent->m_pPElement->m_childList.RemoveAll();	// TODO, free also
			pTag->m_pParent->m_pPElement->BuildTree(this, pTag->m_pParent);
#endif
		}
		else
		{
#if 0
			if (nKey == ' ')	// Space
			{
				if (m_cursorOffset > 0)
				{
					CHTMText* pText = (CHTMText*)pPText->m_pNode;

					int len = pPText->m_text.GetLength();
					int rightlen = len-m_cursorOffset;

					if (rightlen > 0)
					{
						if (rightlen < len)
						{
						// Update DOM and Source
							pText->InsertChar(pPText->m_charOffset+m_cursorOffset, nKey, TRUE /* Update source */);

						// Update render
							PText* pPNewText = new PText;
							pPNewText->m_pNode = pPText->m_pNode;
							pPNewText->m_pFrame = this;
							pPNewText->m_charOffset = pPText->m_charOffset+m_cursorOffset+1;

							pPNewText->m_text = pPText->m_text.Right(rightlen);
							pPText->m_text = pPText->m_text.Left(m_cursorOffset);

							POSITION pos = pPText->m_parent->m_childList.Find(pPText);

							((CHTMPElement*)pPText->m_parent)->MoveTextOffsets(pos, 1);

							pPText->m_parent->m_childList.InsertAfter(pos, pPNewText);
							pPNewText->m_parent = pPText->m_parent;

						// Position the cursor at the beginning of the newly created item
							m_cursorItem = pPNewText;
							m_cursorOffset = 0;
						}
						else
						{
							m_cursorOffset++;
						}
					}
				}
			}
			else
#endif
			{
				CComQIPtr<ILDOMText> text = pPText->m_pNode;
				ASSERT(text);

				WCHAR data[2] = {nKey, 0};
				text->insertData(m_cursorOffset, data);

				m_cursorOffset++;
			}
		}

		OnSize();
		m_pUI->InvalidateRect(&m_client, TRUE);

		ShowCursor();
	}
#endif
#endif
}

bool CHTMLWindow::CursorPositionFromPoint(gm::PointI point, PNode** pItem, long* offset)
{
	PElementBase* pHTMElement = m_htmTree;

	if (pHTMElement->m_pBox)
	{
		return pHTMElement->m_pBox->getPosUnderPoint(point.X, point.Y, pItem, offset);
	}
	else
	{
		*pItem = NULL;
		return false;
	}
}

#if 0//WIN32

DWORD CHTMLWindow::OnDragOver(LPDATAOBJECT pDataObject, DWORD dwKeyState, POINTL abspoint)
{
	ASSERT(0);	// I Had this
#if 0
	POINT point;
	point.x = abspoint.x;
	point.y = abspoint.y;
	m_pUI->ScreenToClient(&point);

	point.x -= m_client.left;
	point.y -= m_client.top;

	CHTMPItem* pItem = NULL;
	int offset = 0;

// Erase previous cursor
	DrawCursor(m_dragOverItem, m_dragOverOffset, TRUE);

//	BOOL bOver = m_htmTree->m_pBox->getPosUnderPoint(point.x, point.y, &m_dragOverItem, &m_dragOverOffset);

	if (CursorPositionFromPoint(point, &m_dragOverItem, &m_dragOverOffset))
	{
	}

// Draw new cursor
	DrawCursor(m_dragOverItem, m_dragOverOffset, TRUE);
#endif

	if (dwKeyState & MK_CONTROL)
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_MOVE;
}

BOOL CHTMLWindow::OnDrop(LPDATAOBJECT hDataObject, DWORD dropEffect, POINTL point)
{
#if 0
// Erase dragover cursor
	DrawCursor(m_dragOverItem, m_dragOverOffset, TRUE);

	COleDataObjectWrapper dataObject;
	dataObject.Attach(hDataObject);

	HGLOBAL hData;

	BOOL success = FALSE;

	if (hData = dataObject.GetGlobalData(CF_HDROP))
	{
		DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
		if (dp)
		{
			WCHAR wfilename[512];
			if (dp->fWide)
			{
				WCHAR* p = (WCHAR*)(dp+1);

				int i = 0;
				while (*p)
				{
					wfilename[i++] = *p++;
				}
				wfilename[i] = 0;
			}
			else
			{
				char* p = (char*)(dp+1);

				int i = 0;
				while (*p)
				{
					wfilename[i++] = *p++;
				}
				wfilename[i] = 0;
			}

			int width = 64;
			int height = 64;

#if 0			// TODO, get size of image
			{
				CIVideo* pVideo = (CIVideo*)sBasic->CreateCmdTarget(IID_AVIDEO);
				ASSERT(pVideo);

				if (pVideo->ImportVideoTags((IV_FileName), (LPCTSTR)filename, (TAG_DONE)) == 0)
				{
					width = pVideo->GetWidth();
					height = pVideo->GetHeight();
				}

				pVideo->Release();
				pVideo = NULL;
			}
#endif

#if 0
			<ILHTMLImageElement> img;
			m_pView->m_document->createElementNS(L"http://www.w3.org/1999/xhtml", L"img", (ILDOMElement**)&img);
			if (img)
			{
				img->set_src(wfilename/*_bstr_t(filename)*/);

				/*
				if (width > 0)
				{
					char buf[64];

					wsprintf(buf, "%d", width);
					img->setAttribute(L"width", _bstr_t(buf));

					sprintf(buf, "%d", height);
					img->setAttribute(L"height", _bstr_t(buf));
				}
				*/

				PText* pPText = (PText*)m_dragOverItem;

				CComQIPtr<ILDOMText> text = pPText->m_pNode;

				CComQIPtr<ILDOMNode> parentNode;
				text->get_parentNode(&parentNode);

			// Split the text in two at offset where we want to insert the new element
			// TODO, check for offset=0 and offset=right of text
				CComQIPtr<ILDOMText> rightText;
				text->splitText(m_dragOverOffset, &rightText);

				parentNode->insertBefore(img, _variant_t(rightText), NULL);
			}
#endif
		}

		GlobalUnlock(hData);

		success = TRUE;
	}
	else if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("MMStudio-HTML")))
	{
#if 0
		char* p = (char*)GlobalLock(hData);
		if (p)
		{
			CHTMDoc* pDoc = new CHTMDoc;
			pDoc->m_pText = new CHTMDocument;
			pDoc->m_pText->m_textData = p;
			pDoc->m_pText->m_textLen = lstrlen(p);
			pDoc->parseText();

			PText* pPText = (PText*)m_dragOverItem;
			CHTMPElement* pPParent = (CHTMPElement*)pPText->m_parent;
			CHTMElement* pParent = (CHTMElement*)pPParent->m_pNode;

			CHTMElement* pImg = pDoc->m_documentElement;

		// Inserting in middle of text, split text in two and insert the IMG inbetween
			CHTMText* pText = (CHTMText*)pPText->m_pNode;

			int len = pText->m_text.GetLength();
		// Create right text node
			CHTMText* pRightText = m_pDocument->createTextNode(pText->m_text.Right(len - (pPText->m_charOffset + m_dragOverOffset)));

		// Set new text of left text node
			pText->m_text = pText->m_text.Left(pPText->m_charOffset + m_dragOverOffset);

		// Insert IMG, then new text node after the left text node
			POSITION pos = pText->m_pParent->m_childList.Find(pText);
			ASSERT(pos);

			pos = pText->m_pParent->m_childList.InsertAfter(pos, pImg);
			pImg->m_pParent = pText->m_pParent;

			pText->m_pParent->m_childList.InsertAfter(pos, pRightText);
			pRightText->m_pParent = pText->m_pParent;

		// Update source
			pParent->SetInnerHTML(pParent->GetInnerHTML());

		// Rebuild the rendering tree
			pPParent->RemoveChildren();
			pPParent->BuildTree(this, pParent);

		// Invalidate this view
			OnSize();
			m_pUI->InvalidateRect(&m_client);

		// Invalidate all other views
			if (TRUE)
			{
				m_pDocument->m_pText->CreateHTMLTree();
				m_pDocument->m_pText->UpdateAllViews(m_pUI);
			}

			pDoc->m_pText->m_textData = NULL;
			delete pDoc->m_pText;

			pDoc->m_documentElement = NULL;
			delete pDoc;
		}

		GlobalUnlock(hData);

		success = TRUE;
#endif
	}
	else if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("Xmill.ASPath")))
	{
		WCHAR* xml = (WCHAR*)GlobalLock(hData);
		if (xml)
		{
			PText* pPText = (PText*)m_dragOverItem;
			CComQIPtr<ILDOMText> text = pPText->m_pNode;
			CComQIPtr<ILDOMNode> parentNode;
			text->get_parentNode(&parentNode);

		//
#if 0
			CComQIPtr<ILDOMElement> parentElement = parentNode;
			BSTR bnodeName;

			BSTR bnamespaceURI;
			parentElement->get_namespaceURI(&bnamespaceURI);
			_bstr_t namespaceURI = _bstr_t(bnamespaceURI, false);

			BSTR btagName;
			parentElement->get_localName(&btagName);	// Try local name first
			if (SysStringLen(btagName) == 0)
			{
				SysFreeString(btagName);
				parentElement->get_tagName(&btagName);	// Then try full qualified name
			}
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!tcscmp(namespaceURI, L"http://www.w3.org/1999/XSL/Transform") && !wcsicmp(tagName, L"for-each"))
			{
			}
#endif

		//
			<ILDOMDocument> document;
			document.CoCreateInstance(CLSID_LDOMDocument);
			bool bsuccess;
			document->loadXML(xml, &bsuccess);

			GlobalUnlock(xml);

			<ILDOMElement> element;

			CComQIPtr<ILDOMElement> node;
			document->get_documentElement(&node);
			while (node)
			{
				BSTR bnodeName;
				node->get_nodeName(&bnodeName);
				_bstr_t nodeName = _bstr_t(bnodeName, false);

				<ILDOMElement> element2;
				m_pView->m_document->createElementNS(L"http://www.w3.org/1999/XSL/Transform", L"xsl:for-each", &element2);
				if (element2)
				{
					element2->setAttribute(L"select", nodeName);

					if (element) element2->appendChild(element, NULL);
					element = element2;
				}

				<ILDOMNode> firstChild;
				node->get_firstChild(&firstChild);
				node = firstChild;
			}

			if (element)
			{
			// Split the text in two at offset where we want to insert the new element
			// TODO, check for offset=0 and offset=right of text
				<ILDOMText> rightText;
				text->splitText(m_dragOverOffset, &rightText);

				parentNode->insertBefore(element, _variant_t(rightText), NULL);

				success = TRUE;
			}
		}
	}

	m_dragOverItem = NULL;
	m_dragOverOffset = -1;

	return success;
#endif
	return 0;
}

#endif // WIN32

#if 0
STDMETHODIMP CHTMLWindow::GetMatrix(/*[out,retval]*/ ILSVGMatrix* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pMatrix;
	(*pVal)->AddRef();
	return Success;
}

STDMETHODIMP CHTMLWindow::SetMatrix(/*[in]*/ ILSVGMatrix* matrix)
{
	m_pMatrix->m_matrix = static_cast<CLSVGMatrix*>(matrix)->m_matrix;

	MessageBeep(-1);
#if 0	// Had this
	m_pUI->Invalidate();
#endif

	return Success;
}
#endif

double CHTMLWindow::get_magnify()
{
	return m_magnify;
}

void CHTMLWindow::set_magnify(double newVal)
{
	newVal = MAX(newVal, 0.0001);
	newVal = MIN(newVal, 99999);

	if (m_magnify != newVal)
	{
		m_magnify = newVal;
		OnSize();	// ??
/*
		PositionFrames();
		*/
#if 0	// I Had this
		if (m_pUI)
		{
			m_pUI->InvalidateRect(&m_client);
		}
#endif

		ASSERT(0);
#if 0
		Fire_onzoom();
#endif
	}
}

double CHTMLWindow::get_currentTranslateX()
{
	return m_currentTranslateX;
}

double CHTMLWindow::get_currentTranslateY()
{
	return m_currentTranslateY;
}

void CHTMLWindow::setCurrentTranslate(double x, double y)
{
	if (m_currentTranslateX != x || m_currentTranslateY != y)
	{
		double dx = x - m_currentTranslateX;
		double dy = y - m_currentTranslateY;

		m_currentTranslateX = x;
		m_currentTranslateY = y;

		//OnSize();	// ??
#if 0
		if (m_scrollX)
		{
			CComQIPtr<IUIScrollBar> scroll = m_scrollX->m_spUnknown;
			scroll->set_pos(-m_currentTranslateX);
		}

		if (m_scrollY)
		{
#if 0
			CComQIPtr<IUIScrollBar> scroll = m_scrollY->m_spUnknown;
			scroll->set_pos(-m_currentTranslateY);
#endif
		}
#endif
/*
	PositionFrames();
	*/
		ASSERT(0);
#if 0	// Had this
		if (m_pUI)
		{
			if (TRUE)
			{
				CRect rect = m_imageRect;
				rect.OffsetRect(m_client.left, m_client.top);

				m_pUI->ScrollWindow(int(dx), int(dy), &rect, &rect);
			}
			else
			{
				m_pUI->InvalidateRect(&m_client);
			}
		}
#endif

		ASSERT(0);
#if 0
		Fire_onscroll();
#endif
	}
}

#if 0
STDMETHODIMP CHTMLWindow::GetOleView(/*[out,retval]*/ ILHTMLActiveView* *pVal)
{
	ASSERT(0);
#if 0	// I Had this
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pUI;
	if (*pVal) (*pVal)->AddRef();
#endif
	return Success;
}
#endif

#if 0
BEGIN_CMD_MAP(CHTMLWindow)
/*
	CMD_HANDLER(ID_VIEW_WORDWRAP, OnViewWordWrap)
	CMD_UPDATE(ID_VIEW_WORDWRAP, OnViewWordWrapUpdate)
	CMD_HANDLER(ID_VIEW_LINENUMBERS, OnViewLineNumbers)
	CMD_UPDATE(ID_VIEW_LINENUMBERS, OnViewLineNumbersUpdate)
	*/
END_CMD_MAP()
#endif

///////////////////////////////////////////////////

#if 0
//////////////////////////
/// IBindStatusCallback

STDMETHODIMP CHTMLWindow::OnStartBinding( 
													/* [in] */ DWORD dwReserved,
													/* [in] */ IBinding __RPC_FAR *pib)
{
	return Success;
}

STDMETHODIMP CHTMLWindow::GetPriority(/* [out] */ LONG __RPC_FAR *pnPriority)
{
	return Success;
}

STDMETHODIMP CHTMLWindow::OnLowResource(/* [in] */ DWORD reserved)
{
	return Success;
}

STDMETHODIMP CHTMLWindow::OnProgress( 
											  /* [in] */ ULONG ulProgress,
											  /* [in] */ ULONG ulProgressMax,
											  /* [in] */ ULONG ulStatusCode,
											  /* [in] */ LPCWSTR szStatusText)
{
	return Success;
}

STDMETHODIMP CHTMLWindow::OnStopBinding( 
												  /* [in] */ ErrorCode hresult,
												  /* [unique][in] */ LPCWSTR szError)
{
	return Success;
}

STDMETHODIMP CHTMLWindow::GetBindInfo( 
												/* [out] */ DWORD __RPC_FAR *grfBINDF,
												/* [unique][out][in] */ BINDINFO __RPC_FAR *pbindinfo)
{
	DWORD cbSize = pbindinfo->cbSize;        
	memset(pbindinfo,0,cbSize);
	pbindinfo->cbSize = cbSize;

//	*grfBINDF = 0;
	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

//	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

	return Success;
}

STDMETHODIMP CHTMLWindow::OnDataAvailable( 
													 /* [in] */ DWORD grfBSCF,
													 /* [in] */ DWORD dwSize,
													 /* [in] */ FORMATETC __RPC_FAR *pformatetc,
													 /* [in] */ STGMEDIUM __RPC_FAR *pstgmed)
{
#if 0
	m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + dwSize);
	if (m_bufferdata)
	{
		ULONG dwRead;
		pstgmed->pstm->Read(m_bufferdata+m_bufferlen, dwSize, &dwRead);

		//ASSERT(dwRead == dwSize);

		m_bufferlen += dwRead;

		return Success;
	}
	else
	{
		return E_OUTOFMEMORY;
	}
#endif
	return Success;
}

STDMETHODIMP CHTMLWindow::OnObjectAvailable( 
														/* [in] */ REFIID riid,
														/* [iid_is][in] */ IUnknown __RPC_FAR *punk)
{
	ErrorCode hr;

	m_spUnknown = punk;

	m_spOleObject = m_spUnknown;
	m_spOleDocument = m_spUnknown;

	hr = m_spOleObject->SetClientSite(this);
	hr = m_spOleObject->Advise(this, &m_dwAdvise);

//	hr = OleRun(m_spUnknown);

	CRect rc(0,0,300,300);
	//GetClientRect(&rc);
	hr = m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, m_pUI->m_hWnd, &rc);

	return Success;
}
#endif

////////////

#if 0
#include "DOMParser.h"
#include "LDOMNamedNodeMap.h"

long CHTMLWindow::GotoLocation(BSTR url)
{
	ASSERT(0);
#if 0
	//FreeImage();

	{
		ErrorCode hr;

		<IHlinkFrame> pHlinkFrame;

		CComQIPtr<IOleClientSite> pCS = m_pUI->m_document->m_spClientSite;//m_lpClientSite;
		CComQIPtr<IServiceProvider> pSP = pCS;
		if (pSP)
			pSP->QueryService(SID_SHlinkFrame, IID_IHlinkFrame, (void**)&pHlinkFrame);
		
		if (pHlinkFrame == NULL) // Try complicated way
		{
			CComQIPtr<IOleInPlaceSite> pIPS = m_pUI->m_spInPlaceSite;//pCS;

			<IOleInPlaceFrame> pIPF;
			<IOleInPlaceUIWindow> pIPUI;
			RECT pos, clip;
			OLEINPLACEFRAMEINFO frameInfo;
			pIPS->GetWindowContext(&pIPF, &pIPUI, &pos, &clip, &frameInfo);
			pIPF->QueryInterface(IID_IHlinkFrame, (void**)&pHlinkFrame);
		}

		<IHlinkBrowseContext> bc;
		hr = HlinkCreateBrowseContext(NULL, IID_IHlinkBrowseContext, (void**)&bc);

	//	m_pUI->m_document->m_pHBC = bc;

		<IMoniker> moniker;

//		if (SUCCEEDED(hr))
		{
			<IBindCtx> bindctx;
			hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
		//hr = CreateBindCtx(0, &bindctx);
			if (SUCCEEDED(hr))
			{
			hr = CreateURLMoniker(/*NULL*/m_pUI->m_document->m_curMoniker, url, &moniker);
		//	ULONG chEaten;
		//	hr = MkParseDisplayNameEx(bindctx, url, &chEaten, &moniker);
			ASSERT(SUCCEEDED(hr));

			PSTR rgszTypes[3] =
			{
				"text/html",	// CFSTR_MIME_HTML
				"image/svg+xml",
				"text/plain",
			};

			CLSID rgclsID[3];
			rgclsID[0] = CLSID_LHTMLActiveDocument;
			rgclsID[1] = CLSID_LHTMLActiveDocument;
			rgclsID[2] = CLSID_LHTMLActiveDocument;

			hr = RegisterMediaTypeClass(bindctx, 3, rgszTypes, rgclsID, 0);

			//hr = ::HlinkSimpleNavigateToMoniker(moniker, NULL, NULL, m_pUI->m_document->GetUnknown(), bindctx, NULL/*this*/, 0/*HLNF_INTERNALJUMP*/, 0);
				
				<IHlink> hlink;

				hr = HlinkCreateFromMoniker(
					moniker,
					NULL, // pwzLocation
					L"test",	// friendlyName
					this,//&hlsite,
					1,	// siteData
					NULL,
					IID_IHlink,
					(void**)&hlink);

				hr = hlink->Navigate(0, bindctx, NULL, bc);
				//hr = ::HlinkNavigatehlink, pHlinkFrame, 0, bindctx, NULL, bc);
			}
		}
	}
#if 0
	<ILDOMImplementation> impl;
	impl.CoCreateInstance(CLSID_LDOMImplementation);

	<ILDOMBuilder> builder;
	impl->createDOMBuilder(1, NULL, &builder);

	<ILDOMDocument> document;
	builder->parseURI(url, &document);

	if (document)
	{
	// Look for xsl-stylesheet
		<ILDOMNode> child;
		document->get_firstChild(&child);
		while (child)
		{
			CComQIPtr<ILDOMProcessingInstruction> pi = child;
			if (pi)
			{
				BSTR btarget;
				pi->get_target(&btarget);
				_bstr_t target = _bstr_t(btarget, false);

				if (!tcscmp(target, L"stylesheet"))
				{
					BSTR bdata;
					pi->get_data(&bdata);
					_bstr_t data = _bstr_t(bdata, false);

					NamedNodeMap* attributes;
				//	CComObject<CLDOMNamedNodeMap>::CreateInstance(&attributes);
					if (attributes)
					{
						attributes->AddRef();

						CDOMParser parser;
						parser.m_textData = data;
						parser.m_textLen = data.length();
						parser.m_document = document;

						parser.ParseAttributes(NULL, attributes);

						<ILDOMAttr> hrefNode;
						attributes->getNamedItem(L"href", (ILDOMNode**)&hrefNode);
						if (hrefNode)
						{
							BSTR bhref;
							hrefNode->get_value(&bhref);
							_bstr_t href = _bstr_t(bhref, false);

							if (href.length())
							{
								<ILDOMDocument> xslDocument;
								bool bsuccess;

							// TODO, some monikers, some services already defined for this ??
								CComQIPtr<IXMLDocumentInMemoryProvider> imp = m_pUI->m_document->m_spClientSite;
								if (imp)
								{
									imp->GetInMemoryDocument(href, &xslDocument);
									if (xslDocument)
										bsuccess = VARIANT_TRUE;
								}

								if (xslDocument == NULL)
								{
									xslDocument.CoCreateInstance(CLSID_LDOMDocument);
									xslDocument->load(href, &bsuccess);
								}

								if (bsuccess)
								{
									<ILXSLTemplate> xslTemplate;
									xslTemplate.CoCreateInstance(CLSID_LXSLTemplate);
									if (xslTemplate)
									{
										xslTemplate->putref_stylesheet(xslDocument);

										<ILXSLProcessor> xslProcessor;

										xslTemplate->createProcessor(&xslProcessor);

										<ILDOMElement> documentElement;
										m_document->get_documentElement(&documentElement);

										xslProcessor->set_input(_variant_t((IUnknown*)m_document));
										bool done;
										xslProcessor->transform(&done);
										if (done)
										{
											_variant_t output;
											xslProcessor->get_output(&output);

											_bstr_t bstrOutput = output;

										//	::MessageBox(NULL, bstrOutput, "", MB_OK);
										//	bool bsuccess;
										//	m_document->loadXML(bstrOutput, &bsuccess);

											<ITextData> textData;
											textData.CoCreateInstance(CLSID_TextData);
											textData->set_data(bstrOutput.copy());

											m_document.Release();
											builder->parseTextData(textData, &m_document);
										}
									}
								}
							}
						}

						attributes->Release();
					}
					break;
				}
			}

			<ILDOMNode> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}

		/*
		if (m_document)
			m_document->get_documentElement(&m_element);
			*/
		SetDocument(document);
	}
#endif
	//DoneParsing();
#endif

	return 0;
}
#endif

#if 0
STDMETHODIMP CHTMLWindow::svgGetRBBox(/*[in]*/ILSVGElement* element, /*[out,retval]*/ ILSVGRect** pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	ASSERT(0);

#if 0
	CComQIPtr<CLSVGElementImplImpl> pElement = element;

	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pView == m_pView)
		{
			PSVGElement* pSVGElement = (PSVGElement*)pElement->m_pNodes[i];

			CLSVGRect* pRect = new CLSVGRect;
		
			if (pRect)
			{
				RectD bounds = pSVGElement->m_bounds;

				pRect->m_x = bounds.X;
				pRect->m_y = bounds.Y;
				pRect->m_width = bounds.Width;
				pRect->m_height = bounds.Height;

				(*pVal = pRect)->AddRef();
			}

			return Success;
		}
	}
#endif

	ASSERT(0);
	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetBBox(/*[in]*/ILSVGElement* element, /*[out,retval]*/ ILSVGRect** pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CComQIPtr<CLSVGElementImplImpl> pElement = element;

	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pWindow == this)
		{
			PSVGElement* pSVGElement = (PSVGElement*)pElement->m_pNodes[i];

			CLSVGRect* pRect = new CLSVGRect;
			if (pRect)
			{
				RectD xbounds = pSVGElement->m_xbounds;

				pRect->m_x = xbounds.X;
				pRect->m_y = xbounds.Y;
				pRect->m_width = xbounds.Width;
				pRect->m_height = xbounds.Height;

				(*pVal = pRect)->AddRef();
			}

			return Success;
		}
	}
#endif

	ASSERT(0);
	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetScreenBBox(/*[in]*/ ILSVGElement *element, /*[out,retval]*/ ILSVGRect **pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	ASSERT(0);
#if 0

	*pVal =  NULL;

	PSVGElement* pSVGElement = (PSVGElement*)CComQIPtr<CLSVGElementImplImpl>(element)->GetNodeOnFrame(m_pView);

	if (pSVGElement)
	{
		CLSVGRect* psvgRect = new CLSVGRect;
		if (psvgRect)
		{

			RectD bbox = pSVGElement->GetScreenBBox();

			psvgRect->m_x = bbox.X;
			psvgRect->m_y = bbox.Y;
			psvgRect->m_width = bbox.Width;
			psvgRect->m_height = bbox.Height;

			*pVal = psvgRect;
		}
		return Success;
	}
#endif

	ASSERT(0);
	return Success;
}
#endif

gm::matrix3f CHTMLWindow::GetViewMatrix()
{
	gm::matrix3f mat;
	mat = /*m_pMatrix->m_matrix * */
			gm::matrix3f::getScale(m_magnify, m_magnify) *
			gm::matrix3f::getTranslate(m_currentTranslateX, m_currentTranslateY);

	return mat;
}

gm::matrix3f CHTMLWindow::svgGetScreenCTM(PElementBase/*PSVGElement*/ * pSVGElement)
{
	ASSERT(0);
	gm::matrix3f matrix;// Had this = pSVGElement->GetScreenCTM();
#if 0

//#if 0	// Decided to not have this ?
	matrix = matrix * GetViewMatrix();
	/*
	matrix = matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
	matrix = matrix * m_pMatrix->m_matrix;
//#endif
*/
#endif
	return matrix;
}

#if 0

STDMETHODIMP CHTMLWindow::svgGetScreenCTM(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	PSVGElement* pSVGElement = (PSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(m_pView);

	if (pSVGElement)
	{
		CLSVGMatrix* pMatrix = new CLSVGMatrix;
		if (pMatrix)
		{
			pMatrix->AddRef();

			pMatrix->m_matrix = svgGetScreenCTM(pSVGElement);//pSVGElement->GetScreenCTM/*2*/();

			//pMatrix->m_matrix = pMatrix->m_matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
			*pVal = pMatrix;
		}
	}

	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetScreenCTM2(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(0);
#if 0
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	PSVGElement* pSVGElement = (PSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(m_pView);

	if (pSVGElement)
	{
		CLSVGMatrix* pMatrix = new CLSVGMatrix;
		if (pMatrix)
		{

			pMatrix->m_matrix = pSVGElement->GetScreenCTM2();

			// ??
			//pMatrix->m_matrix = pMatrix->m_matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
			pMatrix->m_matrix = pMatrix->m_matrix * GetViewMatrix();

			*pVal = pMatrix;
		}
	}
#endif

	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetScreenNCTM(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(0);
	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetScreenNCTM2(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	PSVGElement* pSVGElement = (PSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(m_pView);

	if (pSVGElement)
	{
		CLSVGMatrix* pMatrix = new CLSVGMatrix;
		if (pMatrix)
		{

			ASSERT(0);
#if 0
			pMatrix->m_matrix = pSVGElement->GetScreenCTM2();

			/*
			// ??
			//pMatrix->m_matrix = pMatrix->m_matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
			pMatrix->m_matrix = pMatrix->m_matrix * GetViewMatrix();
			*/
#endif

			*pVal = pMatrix;
		}
	}

	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetViewTransformMatrix(/*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(0);
	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetElementViewBoxMatrix(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	PSVGElement* pSVGElement = (PSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(m_pView);

	if (pSVGElement)
	{
		CComObject<CLSVGMatrix>* pMatrix;
		CComObject<CLSVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->AddRef();
			ASSERT(0);
#if 0
			pMatrix->m_matrix = pSVGElement->GetViewBoxMatrix();
#endif
			*pVal = pMatrix;
		}
	}

	return Success;
}
#endif

#if 0
STDMETHODIMP CHTMLWindow::get_selection(ILDOMRange **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_range;
	if (*pVal) (*pVal)->AddRef();
	return Success;
}
#endif

double CHTMLWindow::get_contentWidth()
{
	VERIFY(0);
//	*pVal = GetSVGWidth();
	return 0;
}

double CHTMLWindow::get_contentHeight()
{
	VERIFY(0);
//	*pVal = GetSVGHeight();
	return 0;
}

void CHTMLWindow::ZoomToRect(double x, double y, double width, double height, bool bAnimate)
{
	ASSERT(0);
#if 0
	double oldmagnify;
	double translateX;
	double translateY;
	get_magnify(&oldmagnify);
	get_currentTranslateX(&translateX);
	get_currentTranslateY(&translateY);

	long innerWidth;
	long innerHeight;
	get_innerWidth(&innerWidth);
	get_innerHeight(&innerHeight);

	CRect m_areaRect;
	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = innerWidth;
	m_areaRect.bottom = innerHeight;

	CDblRect zoomRect;
	zoomRect.left = x;
	zoomRect.top = y;
	zoomRect.right = x+width;
	zoomRect.bottom = y+height;

// Convert screen rectangle to viewport
	CDblRect zoomdrect;
	zoomdrect.left = (zoomRect.left-translateX)/oldmagnify;// + translateX;
	zoomdrect.top = (zoomRect.top-translateY)/oldmagnify;// + translateY;
	zoomdrect.right = (zoomRect.right-translateX)/oldmagnify;// + translateX;
	zoomdrect.bottom = (zoomRect.bottom-translateY)/oldmagnify;// + translateY;

// Set new scale
	double magnify = oldmagnify * (double)(m_areaRect.Width())/zoomRect.Width();

// Set new translate XY
	double cx = zoomdrect.left*magnify;//*magnify - translateX;
	double cy = zoomdrect.top*magnify;//*magnify - translateY;

	if (bAnimate)
	{
		ASSERT(0);
#if 0	// Had this
		if (m_pUI)
		{
			HWND hWnd = m_pUI->m_hWnd;
			if (hWnd)
			{
				HDC hDC = ::GetDC(hWnd);
				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

				HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

				CDblRect imageRect;
				imageRect.left = m_areaRect.left;
				imageRect.top = m_areaRect.top;
				imageRect.right = m_areaRect.right;
				imageRect.bottom = m_areaRect.bottom;

				CDblRect fromrect;
				CDblRect torect;

				if (magnify > oldmagnify) // Zoom in
				{
					fromrect = zoomRect;
					torect = imageRect;
				}
				else
				{
					fromrect = imageRect;
					//torect = zoomRect;
/*
					torect.left = imageRect.left*magnify/oldmagnify + translateX;
					torect.top = imageRect.top*magnify/oldmagnify + translateY;
					torect.right = imageRect.right*magnify/oldmagnify + translateX;
					torect.bottom = imageRect.bottom*magnify/oldmagnify + translateY;
*/
					torect.left = (imageRect.left-translateX)*magnify/oldmagnify - cx;
					torect.top = (imageRect.top-translateY)*magnify/oldmagnify - cy;
					torect.right = (imageRect.right-translateX)*magnify/oldmagnify - cx;
					torect.bottom = (imageRect.bottom-translateY)*magnify/oldmagnify - cy;

/*
					torect.left *= magnify/oldmagnify;
					torect.top *= magnify/oldmagnify;
					torect.right *= magnify/oldmagnify;
					torect.bottom *= magnify/oldmagnify;
*/
		//			ASSERT(0);
				}

				int atotal = 40;

				CRect rect;

				for (int i = 0; i <= atotal; i++)
				{
					if (i > 0)	// Erase previous rectangle
						Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

					rect.left = fromrect.left + (torect.left - fromrect.left)*i/atotal;
					rect.top = fromrect.top + (torect.top - fromrect.top)*i/atotal;
					rect.right = fromrect.right + (torect.right - fromrect.right)*i/atotal;
					rect.bottom = fromrect.bottom + (torect.bottom - fromrect.bottom)*i/atotal;

				// Draw rectangle
					Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

				//	Sleep(0);
				}

			// Erase last rect
				Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

				SelectObject(hDC, hOldBrush);
				SetROP2(hDC, oldR2);
				::ReleaseDC(hWnd, hDC);
			}
		}
#endif
	}

	set_magnify(magnify);
	setCurrentTranslate(-cx, -cy);
#endif
}

#if 0
STDMETHODIMP CHTMLWindow::setInnerSize(/*[in]*/ long width, /*[in]*/ long height)
{
	m_imageRect.right = width;
	m_imageRect.bottom = height;

	Flow();

	return Success;
}
#endif

void CHTMLWindow::DrawToBuffer(/*[in]*/ long width, /*[in]*/ long height, /*[in]*/ long rowbytes, /*[in]*/ long pixelFormat, /*[in]*/ void* buffer)
{
	VERIFY(0);
}

#if 0
STDMETHODIMP CHTMLWindow::DrawToHdc(HDC hDC, ILDOMElement *element, double magnify)
{
	if (m_htmTree)
	{
	// TODO
		PSVGElement* pSVGElement = (PSVGElement*)m_htmTree->FindDOMElement(element);

		LDraw::Graphics graphics(hDC);

		CHTMRenderContext rcontext;

		ASSERT(0);
#if 0

		rcontext.m_clip = pSVGElement->m_expandedBBox;

		//LDraw::GraphicsState state = graphics.Save();	// TODO, just save matrix, it's probably faster

		graphics.ScaleTransform(float(magnify), float(magnify));
		pSVGElement->Render(&rcontext, &graphics, magnify, magnify);
	//	pSVGElement->Render2(&graphics, magnify, magnify);
#endif

		//graphics.Restore(state);
	}
	else
		ASSERT(0);

	return Success;
}

void CHTMLWindow::DrawToHdc4(HDC hDC, ILDOMElement *element, double magnify)
{
	if (m_htmTree)
	{
// TODO
		PSVGElement* pSVGElement = (PSVGElement*)m_htmTree->FindDOMElement(element);
		if (pSVGElement)
		{
			LDraw::Graphics graphics(hDC);

			CHTMRenderContext rcontext;
			ASSERT(0);
#if 0
		// TODO, is this correct, or should it be m_bounds ?
			rcontext.m_clip = LDraw::RectF(0, 0, pSVGElement->m_bounds.Width, pSVGElement->m_bounds.Height);//m_expandedBBox;

		//	LDraw::GraphicsState state = graphics.Save();	// TODO, just save matrix, it's probably faster

			graphics.ScaleTransform(float(magnify), float(magnify));
			pSVGElement->Render4(&rcontext, NULL, &graphics, magnify, magnify, FALSE, FALSE);
#endif
		//	graphics.Restore(state);
		}
	}
	else
		ASSERT(0);

}
#endif

#if 0
STDMETHODIMP CHTMLWindow::svgDrawElementToBuffer(/*[in]*/ ILSVGElement* element, /*[in]*/ ILSVGMatrix* pmatrix, /*[in]*/ long width, /*[in]*/ long height, /*[in]*/ long rowbytes, /*[in]*/ long pixelFormat, /*[in]*/ void* buffer)
{
	if (m_htmTree)
	{
// TODO
		PSVGElement* pSVGElement = (PSVGElement*)m_htmTree->FindDOMElement(element);
		if (pSVGElement)
		{
			LDraw::Bitmap bitmap(width, height, rowbytes, pixelFormat, (LPBYTE)buffer);
			{
				LDraw::Graphics graphics(&bitmap);

				CHTMRenderContext rcontext;
			// TODO, is this correct, or should it be m_bounds ?
			//	rcontext.m_clip = LDraw::RectF(0, 0, pSVGElement->m_bounds.Width, pSVGElement->m_bounds.Height);//m_expandedBBox;
				rcontext.m_clip = LDraw::RectF(0, 0, width, height);

				//LDraw::GraphicsState state = graphics.Save();	// TODO, just save matrix, it's probably faster

				Matrix matrix = static_cast<CLSVGMatrix*>(pmatrix)->m_matrix;

				LDraw::Matrix gdipmatrix;
				matrix.GetGdipMatrix(gdipmatrix);
				graphics.SetTransform(&gdipmatrix);

				double scaleX, scaleY;
				CalculateScaleXY(matrix, &scaleX, &scaleY);

				ASSERT(0);
#if 0

				//graphics.ScaleTransform(float(magnify), float(magnify));
				pSVGElement->Render4(&rcontext, NULL, &graphics, scaleX, scaleY, FALSE, FALSE);
#endif
				//graphics.Restore(state);
			}
		}
	}
	else
		ASSERT(0);

	return Success;
}
#endif

bool CHTMLWindow::get_noscroll()
{
	return m_noscroll;
}

void CHTMLWindow::set_noscroll(bool newVal)
{
	m_noscroll = newVal;
}

#if 0
STDMETHODIMP CHTMLWindow::LocateCursor(ILDOMNode *container, long offset)
{
	m_curContainer = m_htmTree->FindDOMElement(container);
	m_curOffset = offset;
	ASSERT(m_curOffset >= 0);

	if (m_range)
	{
		m_range->setStart(container, offset);
		m_range->setEnd(container, offset);
	}

	ASSERT(0);
#if 0	// TODO have this
	if (m_pUI)
	{
		if (m_pUI->m_hWnd)
		{
			CRect rect = m_imageRect;
			rect.OffsetRect(m_client.left, m_client.top);
			m_pUI->InvalidateRect(&rect);
		}
	}
#endif

	return Success;
}
#endif

#if 0
STDMETHODIMP CHTMLWindow::svgGetPositionOfGlyph(ILSVGTextContentElement *element, long glyphnum, ILSVGPoint **pVal)
{
	ASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;
	
	CPSVGElement* pSVGElement = (CPSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(m_pView);

	if (pSVGElement)
	{
/*
	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pWindow == this)
		{
			CPSVGTextContentElement* pSVGElement = (CPSVGTextContentElement*)pElement->m_pNodes[i];
			*/

			CGlyph* pGlyph = pSVGElement->GetGlyphAtIndex(glyphnum);

			CComObject<CLSVGPoint>* pPoint;
			CComObject<CLSVGPoint>::CreateInstance(&pPoint);
			if (pPoint)
			{
				pPoint->AddRef();

				pPoint->m_x = pGlyph->m_position.X;
				pPoint->m_y = pGlyph->m_position.Y;

				*pVal = pPoint;
			}
//		}
	}
#endif

	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetGlyphSegList(ILSVGTextContentElement *element, long glyphnum, ILSVGPathSegList **pVal)
{
	// TODO: Add your implementation code here

	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetNumberOfGlyphs(ILSVGTextContentElement *element, long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	ASSERT(0);
#if 0

	CPSVGElement* pSVGElement = (CPSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(m_pView);
//	CLSVGTextElement* pElement = static_cast<CLSVGTextElement*>(element);

//	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
//	{
//		if (pElement->m_pNodes[i]->m_pWindow == this)
		if (pSVGElement)
		{
			//CPSVGTextContentElement* pSVGElement = (CPSVGTextContentElement*)pElement->m_pNodes[i];

			*pVal = pSVGElement->GetNumberOfGlyphs();
		}
//	}
#endif

	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetGlyphTextContentElement(ILSVGTextContentElement *element, long glyphnum, ILSVGTextContentElement **pVal)
{
	// TODO: Add your implementation code here

	return Success;
}

STDMETHODIMP CHTMLWindow::svgAddGlyphToSegList(ILSVGTextContentElement *element, long glyphnum, ILSVGPathSegList *seglist)
{
	ASSERT(0);
#if 0
//	CLSVGTextElement* pElement = static_cast<CLSVGTextElement*>(element);

	CPSVGElement* pSVGElement = (CPSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(m_pView);

//	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
//	{
//		if (pElement->m_pNodes[i]->m_pWindow == this)
		if (pSVGElement)
		{
			//CPSVGTextContentElement* pSVGElement = (CPSVGTextContentElement*)pElement->m_pNodes[i];

			CGlyph* pGlyph = pSVGElement->GetGlyphAtIndex(glyphnum);
			if (pGlyph)
			{
				if (pGlyph->m_seglist)
				{
					static_cast<CLSVGPathSegList*>(seglist)->AddSegList(pGlyph->m_seglist);
				}
			}
		}
	//}
#endif

	return Success;
}

STDMETHODIMP CHTMLWindow::svgGetFilterRegion(ILSVGElement *element, ILSVGRect **pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CComQIPtr<CLSVGElementImplImpl> pElement(element);

	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pWindow == this)
		{
			PSVGElement* pSVGElement = (PSVGElement*)pElement->m_pNodes[i];

			CComObject<CLSVGRect>* psvgRect;
			CComObject<CLSVGRect>::CreateInstance(&psvgRect);
			if (psvgRect)
			{
				psvgRect->AddRef();

				RectD bbox = pSVGElement->m_filterRect;

				psvgRect->m_x = bbox.X;
				psvgRect->m_y = bbox.Y;
				psvgRect->m_width = bbox.Width;
				psvgRect->m_height = bbox.Height;

				*pVal = psvgRect;
			}

			return Success;
		}
	}

	ASSERT(0);
#endif

	return Success;
}
#endif

bool CHTMLWindow::get_showMarkup()
{
	return m_bShowMarkup;
}

void CHTMLWindow::set_showMarkup(bool newVal)
{
	ASSERT(0);
#if 0
	if (m_bShowMarkup != newVal)
	{
		m_bShowMarkup = newVal;

		CalcDims(m_htmTree);

		ASSERT(0);
#if 0	// Had this
		if (m_pUI)
		{
			Flow();

			if (m_pUI->m_hWnd)
			{
				m_pUI->Invalidate();
			}
		}
#endif
	}
#endif

}

void CHTMLWindow::scrollIntoView(CHTMBoxItem* pBox)
{
// Find the nearest parent block box with scrollbars
	CHTMBoxItem* pBox2 = pBox->m_parentBox;
	while (pBox2)
	{
	//	rc.Offset(pBox2->m_outerRect.X, pBox2->m_outerRect.Y);

		if (pBox2->m_type == boxTypeBlock)
		{
			CHTMBlockBox* pBlockBox = (CHTMBlockBox*)pBox2;

			gm::RectF rc2 = pBlockBox->GetAbsOuterRect();

			gm::RectF rc = pBox->GetAbsOuterRect();
			rc.Translate(-rc2.X, -rc2.Y);

			if (pBlockBox->m_scrollY)
			{
				Gui::ScrollBar* scrollY = dynamic_cast<Gui::ScrollBar*>(pBlockBox->m_scrollY->GetVisualTree());

				double scrollposY = scrollY->get_Value();

				if (rc.GetBottom() > pBlockBox->m_innerRect.Height+scrollposY)
				{
				// scroll down
					scrollposY += rc.GetBottom()-(pBlockBox->m_innerRect.Height+scrollposY);

					scrollY->set_Value(scrollposY);//pBlockBox->m_pElement->m_scrollY->OnScroll(0, scrollposY);
				}
				else if (rc.GetTop() < scrollposY)
				{
				// scroll up
					scrollposY += rc.GetTop() - scrollposY;

					if (scrollposY < 0) scrollposY = 0;

					scrollY->set_Value(scrollposY);
				}
			}
		}

		pBox2 = pBox2->m_parentBox;
	}
}

void CHTMLWindow::scrollIntoView(PElementBase *pElement)
{
	if (pElement->m_boxList.GetSize() > 0)
	{
		CHTMBoxItem* pBox = pElement->m_boxList[0];

		//LDraw::RectF rc = pBox->m_outerRect;

	// Find the nearest parent block box with scrollbars
		CHTMBoxItem* pBox2 = pBox->m_parentBox;
		while (pBox2)
		{
		//	rc.Offset(pBox2->m_outerRect.X, pBox2->m_outerRect.Y);

			if (pBox2->m_type == boxTypeBlock)
			{
				CHTMBlockBox* pBlockBox = (CHTMBlockBox*)pBox2;

				gm::RectF rc2 = pBlockBox->GetAbsOuterRect();

				gm::RectF rc = pBox->GetAbsOuterRect();
				rc.Translate(-rc2.X, -rc2.Y);

				TRACE("TODO\n");
#if 0
				if (pBlockBox->m_pElement->m_scrollY)
				{
					ASSERT(0);
					CComQIPtr<IUIScrollBar> scrollY = pBlockBox->m_pElement->m_scrollY->m_spUnknown;

					long scrollposY;
					scrollY->get_pos(&scrollposY);

					if (rc.GetBottom() > pBlockBox->m_innerRect.Height+scrollposY)
					{
					// scroll down
						scrollposY += rc.GetBottom()-(pBlockBox->m_innerRect.Height+scrollposY);

						pBlockBox->m_pElement->m_scrollY->OnScroll(0, scrollposY);
					}
					else if (rc.GetTop() < scrollposY)
					{
					// scroll up
						scrollposY += rc.GetTop() - scrollposY;

						if (scrollposY < 0) scrollposY = 0;

						pBlockBox->m_pElement->m_scrollY->OnScroll(0, scrollposY);
					}
				}
#endif
			}

			pBox2 = pBox2->m_parentBox;
		}

		//LDraw::RectF rc = pBox->GetAbsOuterRect();
	}
}

#if 0
STDMETHODIMP CHTMLWindow::scrollIntoView(ILDOMElement *element)
{
	CPElement* pElement = (CPElement*)m_htmTree->FindDOMElement(element);
	if (pElement)
	{
		scrollIntoView(pElement);
	}

	return Success;
}
#endif

#define BufSize	8192
#define BufMask	0x1FFF

class ParserThread : public IO::Stream// : public IGetByte
{
public:
	CTOR ParserThread()
	{
		m_document = NULL;
		m_window = NULL;

		n = 0;
		/*
		m_bytepos = 0;
		m_nstacked = 0;
		*/
	}

	Document* m_document;
	CHTMLWindow* m_window;

	_Ptr<IO::Stream> m_stream;

	/*
	ULONGLONG m_bytepos;
	int m_nstacked;
	uint8 m_oldc[BufSize];

	virtual ULONG getbyte(uint8* pv);
	*/

	ULONG n;

	virtual size_t Read(void* pv, size_t cb) override
	{
		n += cb;
		/*
		if (n > 16)
		{
			if (m_window->m_htmTree == NULL)
			{
				Element* documentElement = m_window->m_document->get_documentElement();
				if (documentElement)
				{
					m_window->m_htmTree = (LXML::CPElement*)documentElement->m_pNode;
					m_window->m_htmTree->m_pWindow = m_window;
				}
			}

			m_window->OnArrange(m_window->get_ActualSize());
		//	m_window->InvalidateRender();
			//Sleep(0);
			n = 0;
		}
		*/

		return m_stream->Read(pv, cb);
	}

	virtual size_t Write(const void* pv, size_t cb) override
	{
		ASSERT(0);
		return 0;
	}

	virtual uint64 Seek(int64 move, IO::SeekOrigin origin) override
	{
		ASSERT(0);
		return 0;
	}

	virtual uint64 GetPosition() override
	{
		ASSERT(0);
		return 0;
	}

	virtual uint64 GetSize() override
	{
		return ~0;
	}
};

//int countBytes = 0;

/*
class BlockingStream : public ISequentialByteStream
{
public:

	ULONG Read(void* pv, ULONG cb)
	{
	}

	ISequentialByteStream* stream;

	int getbyte(uint8* pb)
	{
		ULONG nRead = m_window->m_stream->Read(&m_oldc[m_bytepos & BufMask], cb);

		//m_bytepos += nRead;

		if (nRead == 0)
		{
		}
	}
};
*/

#if 0
ULONG ParserThread::getbyte(uint8* pv)
{
	if ((m_bytepos & BufMask) >= 64)
	{
		if (m_window->m_htmTree == NULL)
		{
			if (m_window->m_document->get_documentElement())
			{
				m_window->m_htmTree = (LXML::PElement*)m_window->m_document->get_documentElement()->m_pNode;
				m_window->m_htmTree->m_pWindow = m_window;
			}
		}

		if (m_window->m_htmTree)
		{
#if 0
			m_downloader->m_crit.Lock();

			m_downloader->m_htmTree->GetCSSPropertiesAndChildren();
			m_downloader->m_htmTree->CalculateBoundsAndChildren();
		//	m_downloader->m_htmTree->m_bArrangeValid = true;

			m_downloader->m_crit.Unlock();
#endif

		//	m_downloader->Flow();
		//	m_downloader->InvalidateMeasure();


			if (!m_window->m_htmTree->m_bArrangeValid)
			{
#if 0
				m_window->InvalidateArrange();
				m_window->Invalidate();
#endif
				m_window->m_bLayoutComplete = false;
#if WIN32
				PostMessage(m_window->m_layoutMessageSink.m_hWnd, WM_USER+100, 0, true);
				WaitForSingleObject(m_window->m_hLayoutDoneEvent, INFINITE);
#else
				ASSERT(0);
#endif
			//	Sleep(1);
			}
		//	Sleep(1);
			//::InvalidateRect(m_downloader->m_pOwnerWindow->m_hWnd, NULL);

#if WIN32
		//	MessageBeep(-1);
		//	PostMessage(m_downloader->m_layoutMessageSink.m_hWnd, WM_USER+100, 0, 0);
		//	Sleep(0);
#endif
		}
	}

	if (m_nstacked > 0)
	{
		m_nstacked--;
		*pv = m_oldc[(m_bytepos++) & BufMask];
		return 1;
	}

	if (m_window->m_stream == NULL)
	{
#if WIN32
		// Wait 10 minutes for more data to be available before we give up
		DWORD nObject = WaitForSingleObject(m_window->m_hEvent, 10 * 60 * 1000);
		if (nObject != WAIT_OBJECT_0)
		{
			return 0;
		}
#endif
	}

	uint8* pb = (uint8*)pv;

	int cb = MIN(BufSize, BufSize-(m_bytepos & BufMask));

//	ASSERT(cb == 4096);
//	ASSERT((m_bytepos & 0xFFF) == 0);

	while (1)
	{
		ULONG nRead = m_window->m_stream->Read(&m_oldc[m_bytepos & BufMask], cb);

		//m_bytepos += nRead;

		if (nRead == 0)
		{
			if (m_window->m_bEOF)
				return 0;

	#if WIN32
			// Wait 10 minutes for more data to be available before we give up
			DWORD nObject = WaitForSingleObject(m_window->m_hEvent, 10 * 60 * 1000);
			if (nObject != WAIT_OBJECT_0)
			{
				// TODO
				ASSERT(0);
				return 0;
			}
	#endif
			nRead = m_window->m_stream->Read(&m_oldc[m_bytepos & BufMask], cb);
			if (nRead == 0)
				return 0;
		}
		/*
		if (nRead < cb)
		{
		}
		*/
		m_nstacked = nRead-1;

		*pb = m_oldc[(m_bytepos++) & BufMask];
		return 1;
	}

#if 0
	ULONG n = 0;
	while (n < cb)
	{
		ULONG toRead = cb-n;
		ULONG nRead = m_window->m_stream->Read(pb, toRead);
		n += nRead;

		if (nRead < toRead)
		{
			if (m_window->m_bEOF)
				return n;

#if WIN32
			// Wait 10 minutes for more data to be available before we give up
			DWORD nObject = WaitForSingleObject(m_window->m_hEvent, 10 * 60 * 1000);
			if (nObject != WAIT_OBJECT_0)
			{
				return n;
			}
#endif
		}
	}

	countBytes += n;

	return n;
#endif
}
#endif

/*
ErrorCode CHTMLWindow::OnProgress(HttpRequest* request)
{
//	m_stream = request->GetContentStream();
	return Success;
}
*/

ErrorCode CHTMLWindow::OnDataAvailable(size_t cbSize, IO::Stream* stream)
{
	//TRACE("OnDataAvailable(%d)\n", cbSize);
	return Success;
#if 0
	m_stream = stream;
#if WIN32
	SetEvent(m_hEvent);
#endif
#endif

	m_nbytes += cbSize;

#if 0
	ProgressEvent* evt = new ProgressEvent;
	evt->m_progress = (double)m_nbytes / stream->GetSize();
#endif
	ASSERT(0);
#if 0
	dispatchEvent(evt);
#endif

	return Success;
}

ErrorCode CHTMLWindow::OnDone()
{
//	m_bEOF = true;

#if 0
#if WIN32
	SetEvent(m_hEvent);
#endif
#endif
	return Success;
}

DWORD WINAPI ParseDocumentProc(void* lpData)
{
	ParserThread* p = (ParserThread*)lpData;

	Net::UrlBinding* binding = new Net::UrlBinding;
	ASSERT(0);
#if 0
	p->m_stream = binding->BindToObject(p->m_document->get_url(), p->m_window);
#endif

	XMLParser parser;
	parser.m_document = p->m_document;
//	parser.m_errorHandler = m_errorHandler;
	parser.load(p);

//	p->m_document->load(p);

//	p->m_window->m_htmTree->GetCSSPropertiesAndChildren();
//	p->m_window->m_htmTree->CalculateBoundsAndChildren();

	Element* documentElement = p->m_window->m_document->get_documentElement();
	if (documentElement)
	{
		p->m_window->m_htmTree = (PElementBase*)documentElement->m_pNode;
		p->m_window->m_htmTree->m_pWindow = p->m_window;
	}

//	p->m_window->OnArrange(p->m_window->get_ActualSize());
//	p->m_window->Invalidate();

	return 0;
		if (p->m_window->m_htmTree == NULL)
		{
			if (p->m_window->m_document->get_documentElement())
			{
				p->m_window->m_htmTree = (PElementBase*)p->m_window->m_document->get_documentElement()->m_pNode;
				p->m_window->m_htmTree->m_pWindow = p->m_window;
			}
		}

		if (p->m_window->m_htmTree)
		{
			if (!p->m_window->m_htmTree->m_bArrangeValid)
			{
//				p->m_window->m_bLayoutComplete = false;
#if 0
				PostMessage(p->m_window->m_layoutMessageSink.m_hWnd, WM_USER+100, 0, true);
#endif
			}
		}

		/*

		if (p->m_window->m_htmTree)
		{
		//	p->m_downloader->m_htmTree->m_bArrangeValid = false;
		//	p->m_downloader->m_crit.Lock();
			p->m_window->m_htmTree->GetCSSPropertiesAndChildren();
			p->m_window->m_htmTree->CalculateBoundsAndChildren();
			p->m_window->OnSize();

		//	p->m_downloader->m_crit.Unlock();

		//	m_downloader->Flow();
			p->m_window->InvalidateMeasure();
			p->m_window->InvalidateArrange();
			p->m_window->Invalidate();
			//::InvalidateRect(m_downloader->m_pOwnerWindow->m_hWnd, NULL);

		}
		*/

	return 0;
}

Document* CHTMLWindow::get_document()
{
	return m_document;
}

ImmutableString<WCHAR> screen_str(L"screen");

String CHTMLWindow::get_mediaMode()
{
	return &screen_str;
}

ICSSStyleDeclaration* CHTMLWindow::getComputedStyle(Web::Element* elt, StringIn pseudoElt)
{
	// TODO
	ASSERT(0);
	return NULL;
}

ILocation* CHTMLWindow::get_location()
{
	ASSERT(0);
	return NULL;
}

History* CHTMLWindow::get_history()
{
	ASSERT(0);
	return NULL;
}

class TimeManager
{
public:

	void OnTimer(UINT);

	double m_fps;
	double m_curTime;
	CHTMLWindow* m_pWindow;
};

void TimeManager::OnTimer(UINT)
{
	m_curTime += 1.0/m_fps;

	for (unsigned int i = 0; i < m_pWindow->m_timelines.size(); i++)
	{
		ElementTime* timeline = m_pWindow->m_timelines[i];

		timeline->Seek(m_curTime);
	}

	for (unsigned int i = 0; i < m_pWindow->m_document->m_animatedElements.size(); i++)
	{
		Element* element = m_pWindow->m_document->m_animatedElements[i];

		NamedNodeMap* attributes = element->get_attributes();
		unsigned int nattributes = attributes->get_length();
		for (unsigned int n = 0; n < nattributes; n++)
		{
			Attr* attr = static_cast<Attr*>(attributes->item(n));

			if (attr->m_animations.size())
			{
		//		Object* baseValObject = (attr->get_ownerElement()->*attr->m_owner->GetBaseValObject)();
				Object* baseValObject = attr->m_owner->GetBaseValAsObject();

				Object* currentValue = baseValObject;

				list<ElementAnimation*, __gc_allocator>::iterator it = attr->m_animations.begin();
				while (it != attr->m_animations.end())
				{
					ElementAnimation* animation = *it;
					++it;

					currentValue = animation->GetValueObject(currentValue, baseValObject);

					//	Object* currentValue = baseVal;
				}

			//	(attr->get_ownerElement()->*attr->m_callbacks->SetAnimValObject)(currentValue);
				attr->m_owner->SetAnimValAsObject(currentValue);
			}
		}
	}
}

void CHTMLWindow::Load(StringIn uri)
{
	ParserThread* parserThread = new ParserThread;
	parserThread->m_window = this;
	parserThread->m_document = new GenericDocument;//LHTML::CLHTMLDocument;
	parserThread->m_document->m_uri = uri;

	parserThread->m_document->loadDefaultStylesheet();
//	dynamic_cast<DocumentStyleImpl*>(parserThread->m_document)->loadDefaultStylesheet();
	m_document = parserThread->m_document;
	m_document->m_pWindow = this;

//	m_bEOF = false;
//	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

#if 0//WIN32
	DWORD threadId;
	HANDLE hThread = CreateThread(NULL, 0, ParseDocumentProc, (LPVOID)parserThread, 0, &threadId);
//	SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);
#else
//	CreateThread(ParseDocumentProc, parserThread);
	ParseDocumentProc(parserThread);
#endif

	TimeManager* timeManager = new TimeManager;
	timeManager->m_fps = 25;
	timeManager->m_pWindow = this;

	ASSERT(0);

	//UI::SetTimer(1000/timeManager->m_fps, std::bind1st(std::mem_fun1(&TimeManager::OnTimer), timeManager));
}

void CHTMLWindow::alert(StringIn str)
{
	MessageBoxW(NULL, CStringw(str), L"js", MB_OK);
}

void CHTMLWindow::addEventListener(StringIn type, Object* listener, bool useCapture)
{
	ASSERT(0);
}

void CHTMLWindow::removeEventListener(StringIn type, Object* listener, bool useCapture)
{
	ASSERT(0);
}

bool CHTMLWindow::dispatchEvent(Event* evt)
{
	ASSERT(0);
	return false;
}

void CHTMLWindow::addEventListenerNS(StringIn namespaceURI, StringIn type, Object* listener, bool useCapture, IEventListenerGroup* evtGroup)
{
	ASSERT(0);
}

void CHTMLWindow::removeEventListenerNS(StringIn namespaceURI, StringIn type, Object* listener, bool useCapture)
{
	ASSERT(0);
}

bool CHTMLWindow::willTriggerNS(StringIn namespaceURI, StringIn type)
{
	ASSERT(0);
	return false;
}

bool CHTMLWindow::hasEventListenerNS(StringIn namespaceURI, StringIn type)
{
	ASSERT(0);
	return false;
}

}	// Web
}
