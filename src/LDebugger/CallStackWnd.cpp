#include "stdafx.h"

#ifdef AMIGA
#define new DEBUG_NEW
#endif

#include "LDebugger.h"
#include "CallStackWnd.h"

//#include "mainfrm.h"
#include "DisassemblyWnd.h"
#include "DebugSession.h"

namespace System
{
namespace Debugger
{

#if _WINDOWS
extern __live_object_ptr<DebugThread> g_pt;
#endif

//extern LDraw::Font* font;

void DrawYellowArrow(UI::Graphics* pGraphics, double midy);
void DrawGreenArrow(UI::Graphics* pGraphics, double midy);

CallStackWnd::CallStackWnd()
{
	m_ctx = NULL;
	m_selected = -1;
}

void CallStackWnd::set_Context(DebuggerCtx* ctx)
{
	m_ctx = ctx;
	// TODO, subscribe to events
}

void CallStackWnd::Update()
{
	m_callstack.clear();

	m_selected = 0;

#if WIN32
	if (m_ctx->m_pJavaVMHost)
	{
		javavm::Frame* pFrame = m_ctx->m_pJavaVMHost->m_pJavaVM->m_threads[0]->m_pFrame;
		while (pFrame && pFrame->m_pMethod)
		{
			DebugFrame* pDebugFrame = new DebugFrame;
			pDebugFrame->m_eip = 0;//(ULONG)frame.Ret_Addr;
			pDebugFrame->m_str = pFrame->m_pMethod->GetName()->ToStringW();
			m_callstack.Add(pDebugFrame);

			pFrame = pFrame->m_pCaller;
		}
	}

	else if (m_ctx && m_ctx->m_pDebugProcess && !m_ctx->m_pDebugProcess->m_bRunning)
	{
		HANDLE hProcess = MSWindows::OpenProcess(PROCESS_ALL_ACCESS, false, m_ctx->m_dwProcessId);
		if (hProcess)
		{
			int n = 0;
		//	DWORD eip = g_pt->m_context.Eip;
		//	DWORD ebp = g_pt->m_context.Ebp;

			STACK_FRAME frame;
			frame.Ebp = (STACK_FRAME*)g_pt->m_context.Ebp;
			frame.Ret_Addr = (uint8*)g_pt->m_context.Eip;

			while (frame.Ebp)
			{
				BufferImp<WCHAR> buffer;
				StringBuilderW sstream(&buffer);

				for (int i = 0; i < m_ctx->m_modules.size(); i++)
				{
					DebugModule* pModule = m_ctx->m_modules[i];

					if ((ULONG)frame.Ret_Addr >= pModule->m_base && (ULONG)frame.Ret_Addr < pModule->m_base + pModule->m_size)
					{
						sstream << *pModule->m_name;

						tysymbolmap_address::iterator psymi = NULL;
						tysymbolmap_address::iterator symi = pModule->m_symbols.begin();
						while (symi != pModule->m_symbols.end())
						{
							if ((*symi).first > (ULONG)frame.Ret_Addr)
							{
								break;
							}
							psymi = symi;
							++symi;
						}

						if (psymi != NULL)
						{
							WCHAR s[512];
							swprintf_s(s, L"%S + %X", (*psymi).second->m_name->c_str(), frame.Ret_Addr - (*psymi).first);
							sstream << s;
						}
						
						break;
					}
				}

				StringW* str;

				if (buffer.m_len == 0)
				{
					WCHAR buf[64];
					swprintf_s(buf, L"%X", frame.Ret_Addr);
					str = new StringW(string_copy(buf));
				}
				else
				{
					str = buffer.DetachToString();
				}

				/*
				for (i = 0; i < m_pFrame->m_ctx->sourceFiles.size(); i++)
				{
					SourceFile* sourceFile = m_pFrame->m_ctx->sourceFiles[i];

					if (eip >= sourceFile->startAddress &&
						eip < sourceFile->endAddress)
					{
					//	sprintf(str, "%s() - %X", sourceFile->sourceFileName, eip);
					//	break;
					}
				}
				*/

				DebugFrame* pDebugFrame = new DebugFrame;
				pDebugFrame->m_eip = (ULONG)frame.Ret_Addr;
				pDebugFrame->m_str = str;
				m_callstack.Add(pDebugFrame);

			//	if (frame.Ebp == NULL)
			//		break;

				MSWindows::DWORD nRead;
				MSWindows::ReadProcessMemory(hProcess, frame.Ebp, &frame, 8, &nRead);
				if (nRead == 0)
					break;

				//frame eip = oldeip;
				n++;
			}
			//while (n < 20);

			MSWindows::CloseHandle(hProcess);
		}
	}
#endif // WIN32

	Invalidate();
}

void CallStackWnd::OnRender(UI::Graphics* pGraphics)
{
//	HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(ANSI_FIXED_FONT));

	{
		LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));
		pGraphics->FillRectangle(brush, 0, 0, m_computedSize.Width, m_computedSize.Height);
	}

	for (int i = 0; i < m_callstack.size(); i++)
	{
		DebugFrame* pDebugFrame = m_callstack[i];

	//	if (m_pFrame->m_Eip >= line->u.instr.address && m_pFrame->m_Eip < line->u.instr.address+line->u.instr.nbytes)
	//	{
	//	}
		if (i == 0)
		{
			DrawYellowArrow(pGraphics, i*16 + 8);
		}

		if (m_selected == i)
		{
			if (i != 0)
			{
				DrawGreenArrow(pGraphics, i*16 + 8);
			}
		}

		pGraphics->DrawString(pDebugFrame->m_str, GetFont(), LDraw::PointF(14, i*16), new LDraw::SolidBrush(LDraw::Color::Black));
	}

//	dc.SelectFont(hOldFont);

#if 0
	if (g_pt)
	{
		if (m_pFrame->m_ctx && m_pFrame->m_ctx->m_pDebugProcess && !m_pFrame->m_ctx->m_pDebugProcess->m_bRunning)
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pFrame->m_dwProcessId);

			int n = 0;
		//	DWORD eip = g_pt->m_context.Eip;
		//	DWORD ebp = g_pt->m_context.Ebp;

			STACK_FRAME frame;
			frame.Ebp = (STACK_FRAME*)g_pt->m_context.Ebp;
			frame.Ret_Addr = (PBYTE)g_pt->m_context.Eip;

			while (frame.Ebp)
			{
				StringA str = "";
				for (int i = 0; i < m_pFrame->m_ctx->m_modules.size(); i++)
				{
					DebugModule* pModule = m_pFrame->m_ctx->m_modules[i];

					if ((ULONG)frame.Ret_Addr >= pModule->base && (ULONG)frame.Ret_Addr < pModule->base + pModule->size)
					{
						str = pModule->name.c_str();

						tysymbolmap::iterator psymi = NULL;
						tysymbolmap::iterator symi = pModule->symbols.begin();
						while (symi != pModule->symbols.end())
						{
							if ((*symi).first > (ULONG)frame.Ret_Addr)
							{
								break;
							}
							psymi = symi;
							symi++;
						}

						if (psymi != NULL)
						{
							char s[512];
							sprintf(s, "%s + %X", (*psymi).second->m_name.c_str(), frame.Ret_Addr - (*psymi).first);
							str += s;
						}
						
						break;
					}
				}

				if (str.length()==0)
				{
					char buf[64];
					sprintf(buf, "%X", frame.Ret_Addr);
					str = buf;
				}		

				/*
				for (i = 0; i < m_pFrame->m_ctx->sourceFiles.size(); i++)
				{
					SourceFile* sourceFile = m_pFrame->m_ctx->sourceFiles[i];

					if (eip >= sourceFile->startAddress &&
						eip < sourceFile->endAddress)
					{
					//	sprintf(str, "%s() - %X", sourceFile->sourceFileName, eip);
					//	break;
					}
				}
				*/

				dc.TextOut(10, n*16, str.c_str());

			//	if (frame.Ebp == NULL)
			//		break;

				DWORD nRead;
				ReadProcessMemory(hProcess, frame.Ebp, &frame, 8, &nRead);
				if (nRead == 0)
					break;

				//frame eip = oldeip;
				n++;
			}
			//while (n < 20);

			CloseHandle(hProcess);
		}
	}
#endif
}

LDraw::SizeD CallStackWnd::OnMeasure(LDraw::SizeD availSize)
{
	return LDraw::SizeD(500, 120);//m_callstack.size() * 16;

//	Control::CalculateBoundsAndChildren(LDraw::SizeD(m_computedWidth, m_computedHeight));
}

#if 0
LRESULT CallStackWnd::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	int index = point.y / 16;
	if (index >= 0 && index < m_callstack.size())
	{
		m_selected = index;
		DebugFrame* pDebugFrame = m_callstack[index];

		SourceLocation* pLocation = m_pFrame->m_ctx->FindSourceLocation(pDebugFrame->m_eip);
		if (pLocation)
		{
		//	MDIChildWnd* pMDIChild = ctx->frame->OpenFile(pLocation->file->sourceFileName);
		//	pMDIChild->ShowWindow(SW_SHOW);
			m_pFrame->SendMessage(WM_USER+2, pLocation->line, (LPARAM)strdup(pLocation->file->sourceFileName.c_str()));

		//	ATLTRACE("source file: %s # %d\n", pLocation->file->sourceFileName, pLocation->line);
		//	ctx->frame->m_disassemblyWnd.m_linesOffset = pLocation->line;

			//pLocation
			delete pLocation;
		}
		else
		{
			m_pFrame->m_disassemblyWnd->SetActive(pDebugFrame->m_eip);
		}

		Invalidate();
	}

	return 0;
}
#endif

}
}
