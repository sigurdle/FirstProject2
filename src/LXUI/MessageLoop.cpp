#include "stdafx.h"

#if AMIGA
#include "../amiga_header.h"
#endif

#if WIN32
#include "../include/windows_header.h"
#endif

#include "LXUI2.h"

extern DECLSPEC_DLLIMPORT long g_locked;
extern DECLSPEC_DLLIMPORT long g_locked2;

namespace System
{
	extern LFCEXT Heap* heap;
}

namespace System
{
namespace UI
{
extern UIEXT __live_object_ptr<LayoutManager> pLayoutManager;
extern UIEXT int g_nWindows;
extern int g_uiLocked;

#if AMIGA
struct MsgPort* pUserPort;
#endif

#if AMIGA

void MessageLoop::AddSignalHandler(uint32 sigmask, ISignalHandler* handler)
{
	SignalHandler* shandler = new SignalHandler;
	shandler->m_sigmask = sigmask;
	shandler->m_handler = handler;
	m_handlers.Add(shandler);

	m_sigmask |= sigmask;
}

#endif

MessageLoop::MessageLoop()
{
#if AMIGA
	m_sigmask = 0;
#endif
}

HANDLE g_hEvent;

/*
DWORD WINAPI MonitorFunc(LPVOID param)
{
	while (1)
	{
		Sleep(1);


		heap->m_crit.Unlock();
	}
}
*/

extern HANDLE g_PresentEvent;

extern list<PresentationSource*> g_windows;

int MessageLoop::Run()
{
	int nRet = 0;

//	CreateThread(/*NULL, 0,*/ MonitorFunc, NULL/*, 0, &threadId*/);

#if WIN32

	g_hEvent = MSWindows::CreateEventW(NULL, false, false, NULL);

//	int nRet = theLoop.Run();
	bool bDone = false;
	while (!bDone)
	{
		MSWindows::MSG msg;

		/*
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			// OnIdle()
		}
		*/

		/*
		DWORD nobj = MsgWaitForMultipleObjects(1, &g_hEvent, FALSE, INFINITE, QS_ALLINPUT);
		if (nobj == WAIT_OBJECT_0)
		{
		}
		else
		*/
		{
			int bRet = MSWindows::GetMessageW(&msg, NULL, 0, 0);

			if (!bRet)
				bDone = true;
		}

		MSWindows::InterlockedIncrement(&g_locked);

		/*
		if (msg.message == WT_PACKET)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				 if (msg.message == WT_PACKET)
				 {
					 GetMessage(&msg, NULL, 0, 0);
					 ASSERT(msg.message == WT_PACKET);
				 }
				 else
					 break;
			}
		}
		else
		*/
		if (msg.message == WM_USER+100)
		{
			while (MSWindows::PeekMessageW(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (msg.message == WM_USER+100)
				{
					MSWindows::GetMessageW(&msg, NULL, 0, 0);
					ASSERT(msg.message == WM_USER+100);
				}
				else
					break;
			}
		}
		else
		{
#if 1
			HwndSource::MyWin* pWindow = NULL;
			if (msg.hwnd) pWindow = (HwndSource::MyWin*)MSWindows::GetPropW(msg.hwnd, L"lxui_window");
			if (pWindow == NULL || !pWindow->pWindow->PreTranslateMessage(&msg))
#endif
				MSWindows::TranslateMessage(&msg);

			MSWindows::DispatchMessageW(&msg);

		}

		if (UI::g_nWindows == 0)
		{
			MSWindows::PostQuitMessage(0);
		}

		if (!MSWindows::PeekMessageW(&msg, NULL, 0, 0, PM_NOREMOVE))	// If there are no new messages in message loop
	//	if (nobj == WAIT_OBJECT_0)
		{
			if (g_PresentEvent == NULL)
			{
				list<PresentationSource*>::iterator it = g_windows.begin();
				while (it != g_windows.end())
				{
					//UI::pLayoutManager->MeasureAll();
					(*it)->MeasureAll();
					++it;
				}

				UI::pLayoutManager->RenderAll();
			}
		}

		MSWindows::InterlockedDecrement(&g_locked);

		//heap->m_crit.Lock();

		ULONG heapsize;
		if (heap->m_toggle == 0)
		{
			heapsize = heap->m_next - heap->m_data;
		}
		else
		{
			heapsize = heap->m_next - (heap->m_data+heap->m_size);
		}

		if (heapsize > heap->m_size*3/5)
		{
		//	MessageBeep(-1);
			//ASSERT(0);

			while (g_locked)
			{
				MSWindows::Sleep(1);
			}

			g_locked2 = true;

			g_uiLocked++;
		//	VERIFY(0);
			gc();
			g_uiLocked--;
#if _DEBUG
			heap->ClearGarbage();
#endif

			g_locked2 = false;
		}

		//heap->m_crit.Unlock();
	}

#elif __APPLE__

	/*
    Boolean	gotEvent;
    EventRecord	event;
        
    gQuitFlag = false;
	
    do
    {
        gotEvent = WaitNextEvent(everyEvent,&event,32767,nil);
        if (gotEvent)
            DoEvent(&event);
    } while (!gQuitFlag);
	 */

//	InstallEventLoopIdleTimer(IdleTimer); // Only available in OSX 10.2

	RunApplicationEventLoop();

#elif AMIGA

	bool bDone = false;
	while (!bDone)
	{
		int nSigMask = execWait(SysBase, m_sigmask | (1<<UI::pUserPort->mp_SigBit));// | CONTROL_C);

#if 0
		if (nSigMask & (1<<nSig))
		{
			if (sr & (1<<15))	// trace exception
			{
			}
			else	// trap0 breakpoint
			{
				uint32 ExceptionAddress = ret_pc-2;

				tybreakpointmap::iterator bi = wndMain->m_ctx->m_breakpoints.find(ExceptionAddress);
				if (bi != wndMain->m_ctx->m_breakpoints.end())
				{
					// Write back the old word so the real instruction can be executed
					uint32 nWritten;
					InstrPlaceholder old_instruction = (*bi).second.m_oldbyte;
					WriteProcessMemory(NULL/*(*pri).second->m_hProcess*/, (LPVOID)ExceptionAddress, &old_instruction, 2, &nWritten);

				// Reset this so the old instruction will be executed
					ret_pc = ExceptionAddress;

					//(*thi).second->m_context.Eip = (DWORD)DebugEv.u.Exception.ExceptionRecord.ExceptionAddress;
				}
			}

			wndMain->OnException();
			//wndMain->m_disassemblyWnd->SetActive((ULONG)ret_pc);
		}
#endif

	//	printf("received signal\n");

		if (nSigMask & (1<<UI::pUserPort->mp_SigBit))
		{
		// As of V39 really is ExtIntuiMessage
			while (struct IntuiMessage* pMsg = (IntuiMessage*)GetMsg(UI::pUserPort))
			{
#if 1
				if (!IsMsgPortEmpty(UI::pUserPort))
				{
					struct IntuiMessage* pNextMsg = (struct IntuiMessage*)UI::pUserPort->mp_MsgList.lh_Head;
					if (pMsg->aos_Class == pNextMsg->aos_Class)
					{
						if (pNextMsg->aos_Class == IDCMP_MOUSEMOVE || pNextMsg->aos_Class == IDCMP_NEWSIZE)
						{
					// Collect sequential
							ReplyMsg((struct Message*)pMsg);
							continue;
						}
					}
				}
#endif

				struct IntuiMessage msg = *pMsg;
				ReplyMsg((struct Message*)pMsg);

				UI::WindowUserData* pUserData = reinterpret_cast<UI::WindowUserData*>(msg.IDCMPWindow->UserData);

				/*bool bDone2 =*/ pUserData->pHandler(&msg, pUserData->pData);
				/*if (bDone2)
					bDone = true;
					*/
				if (UI::g_nWindows == 0)
					bDone = true;

				UI::pLayoutManager->MeasureAll();
				UI::pLayoutManager->RenderAll();
			}

			//UI::pLayoutManager->MeasureAll();
			//UI::pLayoutManager->RenderAll();

			/*
			while (!pLayoutManager->m_windowList.empty())
			{
				NativeWindow* pWindow = pLayoutManager->m_windowList.front();
				pLayoutManager->m_windowList.pop_front();

				if (!pWindow->m_invalidRect.IsEmptyArea())
				{
					pWindow->Render(pWindow->m_invalidRect);
					pWindow->m_invalidRect = LDraw::RectD();	// empty
				}
				pWindow->m_bInvalidated = false;
			}
			*/
		}

		ULONG heapsize;
		if (heap->m_toggle == 0)
		{
			heapsize = heap->m_next - heap->m_data;
		}
		else
		{
			heapsize = heap->m_next - (heap->m_data+heap->m_size);
		}

		if (heapsize > heap->m_size*3/4)
		{
			printf("gc\n");
		//	MessageBeep(-1);
			gc();
#if 0//_DEBUG
			heap->ClearGarbage();
#endif
		}

		for (int i = 0; i < m_handlers.size(); i++)
		{
			if (m_handlers[i]->m_sigmask & nSigMask)
			{
				m_handlers[i]->m_handler->handleSignal(m_handlers[i]->m_sigmask & nSigMask);
			}
		}
	}
#endif

	return nRet;
}

}	// UI
}
