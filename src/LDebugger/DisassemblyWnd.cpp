#include "stdafx.h"
#include "LDebugger.h"

#ifdef AMIGA
#define new DEBUG_NEW
#endif

#if __APPLE__

#include <mach-o/dyld_debug.h>
#include <mach-o/dyld.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>

#endif

#include "DisassemblyWnd.h"
#include "DebugSession.h"

#include "../CodeComp/X86.h"
#include "../CodeComp/x86assem.h"
#include "../CodeComp/m68kassem.h"
//#include "../CodeComp/javadisasm.h"

#if WIN32
//#include <sstream>
#else	// Because of old gcc
//#include <strstream>
#endif

#include "../SWF/ActionNames.h"

namespace System
{
namespace ActionScripting
{


Instruction* disasm(DasmContext* context, void* reserved)
{
	Instruction* instr = new Instruction;
	instr->op = *context->pc++;

	uint16 length;
	if (instr->op >= 0x80)
	{
		length = *context->pc++;
		length |= (*context->pc++)<<8;
	}
	else
	{
		length = 0;
	}

	context->pc += length;

	return instr;
}

}
}

namespace System
{
namespace Debugger
{

void FixPathName(char* dest, int numberOfElements, const char* src);

#if AMIGA
//extern DebuggerCtx* m_ctx;
extern ULONG ret_pc;	// TODO, not here

#endif

void DrawYellowArrow(UI::Graphics* pGraphics, double midy);
void DrawGreenArrow(UI::Graphics* pGraphics, double midy);

void DrawBreakpoint(UI::Graphics* pGraphics, double midy)
{
	LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(190, 10, 10));
	pGraphics->FillEllipse(brush, 1, midy-4, 8, 8);
}

void DrawYellowArrow(UI::Graphics* pGraphics, double midy)
{
	LDraw::PointI pts[] =
	{
		LDraw::PointI(1, midy+2),
		LDraw::PointI(1+5, midy+2),
		LDraw::PointI(1+5, midy+5),

		LDraw::PointI(1+10, midy),

		LDraw::PointI(1+5, midy-5),
		LDraw::PointI(1+5, midy-2),
		LDraw::PointI(1, midy-2),

		// close
		LDraw::PointI(1, midy+2),
	};

//#if _WINDOWS
	LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(255, 255, 0));
	pGraphics->FillPolygon(brush, pts, 7);

	LDraw::Pen* pen = new LDraw::Pen(LDraw::Color(0, 0, 0));
	pGraphics->DrawPolygon(pen, pts, 7);
	/*
#else
	pGraphics->FillPolygon(31, pts, 7);
	pGraphics->DrawPolygon(1, pts, 8);
#endif
	*/
}

void DrawGreenArrow(UI::Graphics* pGraphics, double midy)
{
	LDraw::PointI pts[] =
	{
		LDraw::PointI(1, midy-4),
		LDraw::PointI(1, midy+4),
		LDraw::PointI(1+9, midy),
	};

	LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(0, 190, 50));
	pGraphics->FillPolygon(brush, pts, 3);
//	pGraphics->DrawPolygon(&LDraw::Pen(LDraw::Color(0, 0, 0)), pts, 3);
}

DisassemblyWnd::DisassemblyWnd(DebuggerCtx* ctx)
{
	m_ctx = ctx;

// TODO, subscribe to events

	m_bViewCodeBytes = true;
	m_lenbytes = 0;

	m_lineHeight = 16;
	m_linesOffset = 0;

	m_addr = 0;
	m_buffer = (uint8*)malloc(0x1000);

//	m_dragging = 0;
//	m_penWidth = 10;
//	m_path.AddMove(30, 30);

//	m_path.AddLine(300, 30);
//	m_path.AddLine(300, 250);
	/*
	m_path.AddLine(100, 60);
	m_path.AddLine(120, 70);
	*/
/*
	m_path.AddBezier(
		100, 50,
		200, 200,
		800, 210);
*/

	//set_Background(new UI::SolidColorBrush(new UI::Color(255, 255, 255)));
}

DisassemblyWnd::~DisassemblyWnd()
{
	free(m_buffer);
}

#if 0//_WINDOWS

LRESULT DisassemblyWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	UISetCheck(ID_DISASM_CODEBYTES, m_bViewCodeBytes);

	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_PAGE | SIF_RANGE;
	si.nMin = 0;
	si.nMax = 0x7fffffff;
	si.nPage = 0xfff;
	SetScrollInfo(SB_VERT, &si);
#endif

	return 0;
}

int Disasm(BYTE* buffer, int len)
{
	int fails = 0;

	CX86Context c;
	c.pc = buffer;
	while (c.pc < buffer+len)
	{
		uint8* pc = c.pc;

		x86instr* instr = disasm_x86(&c);
		if (instr == NULL)//c.pc - pc == 0)
		{
			c.pc = pc+1;
			//c.pc++;
			fails++;
		}
	}

	return fails;
}
#endif

void DisassemblyWnd::MakeVisible2(ULONG addr)
{
	if (true)
	{
		m_addr = addr;
		ReadBuffer();
		return;
	}

	if (addr < m_topaddr)	// Scroll up
	{
		m_addr = addr;
		ReadBuffer();
	}
	else if (addr >= m_topaddr+m_lenbytes)	// Scroll down
	{
		// Try some scrolling down before we give up and just set the top address
		int nlines = m_lines.size()-1;
		for (int i = 0; i < nlines; i++)
		{
			ScrollDown(1);
			Line* pBottomLine = m_lines[m_lines.size()-1];
			if (pBottomLine->GetKind() == Line::K_INSTR)
			{
				if (((InstrLine*)pBottomLine)->address == addr)
				{
					return;
				}
			}
		}

		m_addr = addr;
		ReadBuffer();
	}
}

void DisassemblyWnd::MakeVisible(ULONG addr)
{
	MakeVisible2(addr);
	Invalidate();
}

void DisassemblyWnd::SetActive(ULONG addr)
{
	m_active = addr;
	MakeVisible(m_active);
}

LDraw::SizeD DisassemblyWnd::OnMeasure(LDraw::SizeD availSize)
{
	return LDraw::SizeD(2000, m_lines.size()*m_lineHeight);
}

void DisassemblyWnd::OnArrange(LDraw::SizeD finalSize)
{
	if (false)
	{
		if (/*m_pFrame->*/m_ctx)
		{
			int numlines = (finalSize.Height + m_lineHeight-1) / m_lineHeight;

		//	printf("numlines: %d\n", numlines);

			if (numlines > m_lines.size())
			{
				ReadBuffer();
			}
			else if (numlines < m_lines.size())
			{
				m_lines.SetSize(numlines);
			}
		}
	}
}

/*
// TODO, remove
namespace cpp
{
extern CodeCompExt char	xsbuf[128], *xsptr;
extern CodeCompExt char	msbuf[128],	*msptr;
}
*/

void DisassemblyWnd::ReadBuffer()
{
	m_lenbytes = 0;
	m_lines.clear();

	int back = 0;

	int maxlines;
	if (true)
	{
		maxlines = 99999;
	}
	else
	{
		maxlines = (m_computedSize.Height + m_lineHeight-1) / m_lineHeight;
	}

	LPVOID PMAAddress;
	if (m_addr < back)
		PMAAddress = 0;
	else
		PMAAddress = (LPVOID)(m_addr - back);

	ULONG PMASize;

#if WIN32
	if (/*m_pFrame->*/m_ctx->m_cpu == CPU_JAVA_IL)
	{
		javavm::Thread* javaThread = /*m_pFrame->*/m_ctx->m_pJavaVMHost->m_pJavaVM->m_threads[0];

		if (javaThread->m_pFrame == NULL)
			return;

		PMAAddress = javaThread->m_pFrame->m_pCode->code;
		PMASize = javaThread->m_pFrame->m_pCode->code_length;
		//PMASize = numlines * 8;
	}
	else if (/*m_pFrame->*/m_ctx->m_cpu == CPU_FLASH_IL)
	{
		if (m_ctx->m_actionScriptVM == NULL)
			return;

		PMAAddress = m_ctx->m_actionScriptVM->m_pFrame->m_instructionsData;
		PMASize = m_ctx->m_actionScriptVM->m_pFrame->m_instructionsLength;

	}
	else
#endif
#if WIN32
	if (/*m_pFrame->*/m_ctx->m_cpu == CPU_PPC)
	{
		PMASize = maxlines * 4;
	}
	else
#endif
	{
		PMASize = maxlines * 16;
	}

	if (PMASize > 0x1000) PMASize = 0x1000;

	/*m_pFrame->*/m_ctx->ReadBuffer(m_buffer, PMAAddress, PMASize);

	if (/*m_pFrame->*/m_ctx)
	{
#if 0
		int fails[8];

		int ntries = 1;

		for (int i = 0; i < ntries; i++)
		{
			fails[i] = Disasm(m_buffer+i, 0x140);
		}
#endif
		// Use the one with fewest fails
		m_addroffset = 0;
#if 0
		for (i = 1; i < ntries; i++)
		{
			if (fails[i] < fails[m_addroffset])
			{
				m_addroffset = i;
			}
		}
#endif

		if (true)
		{
			m_topaddr = (ULONG)PMAAddress;
		}
		else
		{
		// snap to instruction
		m_topaddr = m_addr + m_addroffset;
		}

	//	m_linesOffset = 0;

		union DisasmContext
		{
			MContext* context;
			X86Context* x86;
			m68kContext* m68k;
			ppcContext* ppc;
			java::javavmContext* java;
			ActionScripting::DasmContext* actionScript;
		}
		c;

		switch (/*m_pFrame->*/m_ctx->m_cpu)
		{
		case CPU_IX86:
			c.x86 = new X86Context;
			break;

		case CPU_M68K:
			c.m68k = new m68kContext;
			break;

		case CPU_PPC:
			c.ppc = new ppcContext;
			break;

		case CPU_JAVA_IL:
			{
			java::javavmContext* pcontext = new java::javavmContext;
			//pcontext->m_pJavaClass = m_pFrame->m_ctx->m_pJavaClass;
			c.java = pcontext;
			}
			break;

		case CPU_FLASH_IL:
			{
				c.actionScript = new ActionScripting::DasmContext;
			}
			break;

		default:
			ASSERT(0);
		}

#if 0
		int nstab = 0;
		DWORD last_fun_address = 0;
		DWORD line_address = 0;
		int start_line = 0;
		int end_line = 0;
#endif

#if 0
		uint32 base;
		if (m_pFrame->m_ctx->m_cpu == CPU_IX86)
		{
			base = m_pFrame->m_ctx->m_pImage->windowsHeader->ImageBase + m_pFrame->m_ctx->m_pImage->SectionHeader[0/*TODO*/].VirtualAddress;
		}
		else
		{
			base = 0;
		}
#endif
//		uint32 PMASize = 0x100;

#if 0
		SourceFile* pCurrentSourceFile = NULL;
#endif

		int last_line = 0;

		uint8* buffer = m_buffer + m_addroffset;
		c.context->pc = buffer;
		while (c.context->pc < m_buffer+PMASize)
		{
			ULONG_PTR instr_address = m_topaddr + c.context->pc - buffer - back;

			if (m_ctx->m_pDebugInfo)
			{
				for (uint i = 0; i < m_ctx->m_pDebugInfo->m_sourceFiles.size(); i++)
				{
					SourceFile* sourceFile = m_ctx->m_pDebugInfo->m_sourceFiles[i];

					for (uint j = 0; j < sourceFile->m_segments.GetSize(); j++)
					{
						SourceFile::Segment& segment = sourceFile->m_segments[j];

						if (segment.m_startAddress <= instr_address &&
							segment.m_endAddress > instr_address)
						{
							TextLines* tdp;

							SourceTextDocument* document = (SourceTextDocument*)sourceFile->m_userdata;
							if (document == NULL)
							{
								char filename[512];
								FixPathName(filename, _countof(filename), sourceFile->m_filename->c_str());

								System::IO::FileByteStream stream(new StringA(string_copy(filename)));
								TextData* textdata = new TextData;
								textdata->ReadFromStream(&stream);
								tdp = new TextLines(textdata);

								document = new SourceTextDocument;
								document->m_tdp = tdp;

								sourceFile->m_userdata = document;

								/*filesmap::iterator fi =*/ m_ctx->m_frame->m_files.insert(filesmap::value_type(new StringA(string_copy(filename)), document));
							}
							else
							{
								tdp = document->m_tdp;
							}

							VERIFY(tdp);

						//	ASSERT(sourceLocation == NULL);

						//	sourceLocation = new SourceLocation;
						//	sourceLocation->file = sourceFile;

							int n;
							for (n = 0; n < sourceFile->m_lines.GetSize(); n++)
							{
								SourceFile::SourceLine& line = sourceFile->m_lines[n];

								if (line.m_address >= instr_address)
									break;
							}
							//n = last_line;

						//	int last_line = 0;

						// Collect the lines that precede the next intruction
							for (; n < sourceFile->m_lines.GetSize(); n++)
							{
								SourceFile::SourceLine& line = sourceFile->m_lines[n];

								// If this line's address is past, we break out and come back
								// to it in the next iteration
								if (line.m_address > instr_address)
									break;

								int lineNumber;
								for (lineNumber = last_line; lineNumber <= line.m_line; lineNumber++)
								{
									TextLine* textline = new TextLine;
									TextLines::Line* pLine = tdp->GetLine(lineNumber);
									textline->str = StringW(true, tdp->m_textData->GetData() + pLine->m_offset, pLine->m_lineLengthR).ToStringA();
									textline->lineNumber = line.m_line;

									m_lines.push_back(textline);
								}

								last_line = lineNumber;
							}
						}
					}
				}
			}

#if 0
			SourceLocation* sloc = m_ctx->FindSourceLocation(instr_address);

			if (sloc)
			{
				SourceEditFrame* sourceEdit = (SourceEditFrame*)sloc->file->m_userdata;

				if (sourceEdit)
				{
					ITextData* tdp = sourceEdit->pEdit->get_TextDocument();

				// Collect the lines that precede the next intruction

					sloc
				}
			}
#endif

#if 0
		//	SourceLocation* location = m_pFrame->m_ctx->FindSourceLocation(instr_address);
			SourceFile* sourceFile = NULL;
		// Find source file that this location belongs to
			for (int i = 0; i < /*m_pFrame->*/m_ctx->m_pDebugInfo->m_sourceFiles.size(); i++)
			{
				// TODO
#if 0
				SourceFile* sourceFile2 = /*m_pFrame->*/m_ctx->m_pDebugInfo->m_sourceFiles[i];
				if (sourceFile2->startAddress <= instr_address &&
					sourceFile2->endAddress > instr_address)
				{
				// TODO..
					ASSERT(sourceFile == NULL);

					sourceFile = sourceFile2;
				}
#endif
			}
#endif

#if 0
			if (sourceFile)
			{
				/*
				if (sourceFile != pCurrentSourceFile)
				{
					pCurrentSourceFile = sourceFile;

					Line* line = new Line;
					line->kind = Line::K_TEXT;
					line->u.text.lineNumber = -1;
					char text[1024];
					sprintf(text, "// %s\n", pCurrentSourceFile->sourceFileName);
					line->u.text.p = strdup(text);
					lines.push_back(line);
					if (lines.size() >= numlines) break;
				}
				*/

				// Collect the lines that precede the next intruction
				while ((nstab < sourceFile->m_stabvec.size()) &&
					line_address <= (instr_address))
				{
					nlist* pSymbol = sourceFile->m_stabvec[nstab];

					if (pSymbol->n_type == N_FUN)
					{
						last_fun_address = sourceFile->startAddress + pSymbol->n_value;
					}
					else if (pSymbol->n_type == N_SLINE)
					{
						int address = last_fun_address + pSymbol->n_value;

						/*
						// If this lines address is past, we break out and come back
						// to it in the next iteration
						if (address > (instr_address))
							break;


						if (address >= instr_
						Line* line = new Line;
						line->kind = Line::K_TEXT;
						line->u.text.lineNumber = i;
						line->u.text.p = sourceFile->sourceLines[i].c_str();
						lines.push_back(line);
						if (lines.size() >= numlines) break;
*/

						if (address < instr_address)
							start_line = pSymbol->n_desc;//end_line;

						// If this lines address is past, we break out and come back
						// to it in the next iteration
						if (address > (instr_address))
							break;

						line_address = address;
						end_line = pSymbol->n_desc;

					}

					nstab++;
				}

				{
					for (int i = start_line; i < end_line; i++)
					{
						if (i >= m_linesOffset)
						{
							Line* line = new Line;
							line->kind = Line::K_TEXT;
							line->u.text.lineNumber = i;
							line->u.text.p = sourceFile->sourceLines[i].c_str();
							m_lines.push_back(line);
							if (m_lines.size() >= numlines) break;
						}
					}
					start_line = end_line;
					if (m_lines.size() >= numlines) break;
				}
			}
#endif

			InstrLine* line = new InstrLine;
		//	line->kind = Line::K_INSTR;
			line->address = instr_address;
			line->cpu.pv = NULL;
			line->nbytes = 0;

			uint8* pc = c.context->pc;

			tybreakpointmap::iterator bi = /*m_pFrame->*/m_ctx->m_breakpoints.find(instr_address/*m_topaddr+pc-m_buffer-back*/);
			if (bi != /*m_pFrame->*/m_ctx->m_breakpoints.end())
			{
				if (/*m_pFrame->*/m_ctx->m_cpu == CPU_IX86)
				{
					*pc = (*bi).second.m_oldbyte.n[0];
#if WIN32
					line->cpu.x86 = disasm_x86(c.x86);
#endif
					if (c.x86->pc - pc == 0)
						c.x86->pc += 1;
				}
				else if (/*m_pFrame->*/m_ctx->m_cpu == CPU_M68K)
				{
					pc[0] = (*bi).second.m_oldbyte.n[0];
					pc[1] = (*bi).second.m_oldbyte.n[1];
					//pc[1] = (*bi).second.m_oldbyte & 0xff;
					line->cpu.m68k = disasm_m68k(c.m68k);

					if (c.m68k->pc - pc == 0)
						c.m68k->pc += 2;
				}
				else if (/*m_pFrame->*/m_ctx->m_cpu == CPU_JAVA_IL)
				{
					pc[0] = (*bi).second.m_oldbyte.n[0];
					line->cpu.java = java::disasm_java(c.java, NULL/*m_pFrame->m_ctx->m_pJavaClass*/);
				}
				else if (m_ctx->m_cpu == CPU_FLASH_IL)
				{
					pc[0] = (*bi).second.m_oldbyte.n[0];
					line->cpu.actionScript = ActionScripting::disasm(c.actionScript, NULL);
				}
				else
					ASSERT(0);

				line->nbytes = c.context->pc - pc;
			}
			else
			{
				switch (/*m_pFrame->*/m_ctx->m_cpu)
				{
#if WIN32
				case CPU_IX86:
					{
						line->cpu.x86 = disasm_x86(c.x86);
						
						if (c.x86->pc - pc == 0)
							c.x86->pc += 1;
					}
					break;
#endif
					
				case CPU_M68K:
					{
						line->cpu.m68k = disasm_m68k(c.m68k);
						
						if (c.m68k->pc - pc == 0)
							c.m68k->pc += 2;
					}
					break;
					
#if WIN32
				case CPU_PPC:
					{
						line->cpu.ppc = disasm_ppc(c.ppc);
						
						if (c.ppc->pc - pc == 0)
							c.ppc->pc += 4;
					}
					break;
					
				case CPU_JAVA_IL:
					{
						line->cpu.java = java::disasm_java(c.java, NULL/*m_pFrame->m_ctx->m_pJavaClass*/);
						
					//	if (c.ppc->pc - pc == 0)
					//		c.ppc->pc += 1;
					}
					break;

				case CPU_FLASH_IL:
					{
						line->cpu.actionScript = ActionScripting::disasm(c.actionScript, NULL);
					}
					break;
#endif		
				default:
					ASSERT(0);
				}

				line->nbytes = c.context->pc - pc;
			}

			/*
			if (pc <= m_buffer+16)
			{
				m_topaddr = m_addr + pc-m_buffer - 16-chosen;
				m_pFrame->m_toplen = c.pc - pc;
			}
			*/

			if (pc >= m_buffer+back)
			{
				/*
				std::stringstream s;
				if (line.u.instr.p)
				{
					s << line.u.instr.p;
				}
				std::string str = s.str().c_str();
				*/

				/*
					LDraw::Graphics graphics(dc);
					graphics.FillEllipse(&LDraw::SolidBrush(LDraw::Color(255, 20, 20)), 2, rc.top+2, 12, rc.Height()-4);
				*/

			//	printf("instr_address: %x\n", instr_address);
				if (/*m_pFrame->*/m_ctx->m_pDebugInfo)
				{
				//	tysymbolmap_address::iterator si = m_pFrame->m_ctx->m_pDebugInfo->symbols.find(instr_address/*m_topaddr + pc - buffer - back*/);
				//	if (si != m_pFrame->m_ctx->m_pDebugInfo->symbols.end())
					DebugSymbol* pDebugSymbol = /*m_pFrame->*/m_ctx->m_pDebugInfo->LookupSymbol(instr_address);
					if (pDebugSymbol)
					{
						TextLine* line = new TextLine;
						//line->kind = Line::K_TEXT;
						line->str = pDebugSymbol->m_name;//->c_str();

						m_lines.Add(line);
						if (m_lines.size() > maxlines) break;
					}
				}

				/*
				CRect rc(18, y, 90, y+16);

				dc.DrawText(straddr, strlen(straddr), &rc, DT_SINGLELINE);
				rc.left = rc.right+4;
				*/

		//		n++;
				m_lines.Add(line);
				if (m_lines.size() >= maxlines) break;
			}
		}
		m_lenbytes = c.context->pc - (m_buffer + m_addroffset);

		if (/*m_pFrame->*/m_ctx->m_cpu == CPU_IX86)
			delete c.x86;
		else if (/*m_pFrame->*/m_ctx->m_cpu == CPU_M68K)
			delete c.m68k;
		else if (/*m_pFrame->*/m_ctx->m_cpu == CPU_PPC)
			delete c.ppc;
	}
}

void DisassemblyWnd::ScrollUp(int nlines)
{
	for (int i = 0; i < nlines; i++)
	{
		/*
		if (m_linesOffset > 0)
		{
			m_linesOffset--;
			ReadBuffer();
		}
		else
		*/
		if (m_lines[0]->GetKind() == Line::K_TEXT)
		{
			m_linesOffset = ((TextLine*)m_lines[0])->lineNumber-1;
			ReadBuffer();
		}
		else //if (m_lines[0]->kind == Line::K_INSTR)
		{
			ULONG refAddress;
			refAddress = ((InstrLine*)m_lines[0])->address;
			ASSERT(m_addr == refAddress);

			ULONG addr = m_addr-1;
			int nbytes = 0;
			do
			{
				m_addr -= 1;
				ReadBuffer();

				InstrLine* topLine = (InstrLine*)m_lines[0];
				if (topLine->address + topLine->nbytes == refAddress)
				{
					// Remember the instruction with the maximum length
					if (topLine->nbytes > nbytes)
					{
						nbytes = topLine->nbytes;
						addr = m_addr;
					}
				}

				// instructions woun't go above 24 bytes, so stop backtracking
				if (refAddress - topLine->address + topLine->nbytes > 24)
				{
					break;
				}
			}
			while (1);

			if (m_addr != addr)
			{
				m_addr = addr;
				ReadBuffer();
			}
		}
#if 0
		else
		{
			ASSERT(0);
		//	ATLASSERT(m_linesOffset > 0);
		//	m_linesOffset--;
		}
#endif
	}
}

void DisassemblyWnd::ScrollDown(int nlines)
{
	if (nlines > 0)
	{
		for (int i = 0; i < nlines; i++)
		{
			if (m_lines[0]->GetKind() == Line::K_INSTR)
			{
				m_addr = m_topaddr + ((InstrLine*)m_lines[0])->nbytes;
				m_linesOffset = 0;
				ReadBuffer();
			}
			else
			{
				m_linesOffset = ((TextLine*)m_lines[0])->lineNumber+1;
				ReadBuffer();
			}
		}
	}
}

#if 0//_WINDOWS
LRESULT DisassemblyWnd::OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	int nScrollCode = (int) LOWORD(wParam); // scroll bar value 
	int nPos = (short int) HIWORD(wParam);  // scroll box position 
	HWND hwndScrollBar = (HWND) lParam;      // handle to scroll bar 

	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_TRACKPOS;
	GetScrollInfo(SB_VERT, &si);

	switch (nScrollCode)
	{
	case SB_THUMBTRACK:
		{
			si.fMask = SIF_POS;
			si.nPos = si.nTrackPos;
			SetScrollInfo(SB_VERT, &si);
			m_addr = /*0x7fffffff /*/ si.nPos;
			ReadBuffer();

			Invalidate();
		}
		break;
	}
#endif
	return 0;
}
#endif // _WINDOWS

//extern LDraw::Font* font;

#if 0
// virtual
void DisassemblyWnd::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*type == *WSTR("mousedown"))
		{
#if 0
			//OnLButtonDown(dynamic_cast<CLXUIMouseEvent*>(evt));
			CLXUIMouseEvent* mouseevt = dynamic_cast<CLXUIMouseEvent*>(evt);

			Point* point = mouseevt->GetPosition(this);
			m_oldPoint.X = point->get_X();
			m_oldPoint.Y = point->get_Y();

			if (TRUE)
			{
				m_path.AddMove(LDraw::PointF(point->get_X(), point->get_Y()));
				m_dragging = true;
			}
			else
			{
				m_npt = -1;
				for (int i = 0; i < m_path.m_points.size(); i++)
				{
					LDraw::PointF point = m_path.m_points[i];

					if (fabs(m_oldPoint.X - point.X) < 4 && fabs(m_oldPoint.Y - point.Y) < 4)
					{
						m_npt = i;
						break;
					}
				}

				if (m_npt >= 0)
				{
					m_dragging = true;
				}
			}
#endif
		}
		else if (*type == *WSTR("mouseup"))
		{
			//OnLButtonUp(dynamic_cast<CLXUIMouseEvent*>(evt));
		//	m_dragging = false;
		}
		else if (*type == *WSTR("mousemove"))
		{
#if 0
			CLXUIMouseEvent* mouseevt = dynamic_cast<CLXUIMouseEvent*>(evt);
			//OnMouseMove(dynamic_cast<CLXUIMouseEvent*>(evt));
			if (m_dragging)
			{
				Point* point = mouseevt->GetPosition(this);

				if (point->get_X() != m_oldPoint.X || point->get_Y() != m_oldPoint.Y)
				{
				//m_points.push_back(LDraw::PointI(point->get_X(), point->get_Y()));
					if (TRUE)
					{
						m_path.AddLine(LDraw::PointF(point->get_X(), point->get_Y()));
					}
					else
					{
						m_path.m_points[m_npt].X = point->get_X();
						m_path.m_points[m_npt].Y = point->get_Y();
					}

					m_oldPoint.X = point->get_X();
					m_oldPoint.Y = point->get_Y();

					Length* width = new Length(0, Length::UnitAbsolute);
					Length* height = new Length(0, Length::UnitAbsolute);
					printf("Here\n");
					Invalidate();
				}

			//	m_penWidth = point->get_X() / 5;
			}
#endif
		}
	}
}
#endif

void DisassemblyWnd::OnRender(UI::Graphics* pGraphics)
{
	/*
	return;

	printf("DisassemblyWnd::OnRender2()\n");
	fflush(stdout);
	*/

//	CRect client;
//	client = GetClientRect();

	{
		LDraw::SolidBrush* bgbrush = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));
		pGraphics->FillRectangle(bgbrush, 0, 0, m_computedSize.Width, m_computedSize.Height);
	}

#if _WINDOWS
	if (false)
#else
	if (false)
#endif
	{
//	CPaintDC dc(m_hWnd);
//	CDCHandle dc(pGraphics->GetHDC());

//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, client.Width(), client.Height());

//	pGraphics->RotateTransform(10);

	/*
	LDraw::GraphicsPath path;
//	path.AddRoundRect(40, 40, 120, 40, 10, 10);

	path.AddMove(100, 100);
	path.AddLine(600, 120);
	path.AddLine(550, 500);
	path.AddLine(400, 300);
	path.AddLine(500, 200);
//	path.AddLine(300, 250);
//	path.AddLine(50, 250);
	//path.CloseFigure();
*/
	/*
	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 255)), 0, 0, 60, 60);
	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 255, 0)), 60, 0, 60, 60);
	*/

//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 0, 0)), 3, 5, 7, 1);
//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), 4.f, 1.f, 6.f, 4.0f);

	LDraw::Pen* pen = new LDraw::Pen(LDraw::Color(255, 0, 0), 5.f);
//	pen.SetTransform(gmMatrix3::rotate(45) * gmMatrix3::scale(1, 3));

	//pGraphics->SetClip(LDraw::RectF(10, 10, 200, 200), LDraw::CombineModeReplace);

	/*
	LDraw::GraphicsPath clip;
	clip.AddMove(20, 20);
	clip.AddLine(400, 60);
	clip.AddLine(200, 200);
	clip.AddLine(100, 210);

	pGraphics->DrawPath(&pen, &clip);

	pGraphics->SetClip(&clip, LDraw::CombineModeReplace);
	*/

//#if 0
#if 0
	pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(60, 200, 60)), &m_path);
	float dashPattern[] = {4, 2 };
	pen.SetDashPattern(dashPattern, 2);
	pGraphics->DrawPath(&pen, &m_path);
	//pGraphics->FillPolygon(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), m_points.begin(), m_points.size());
#endif

	/*
	LDraw::Pen pen2(LDraw::Color(60, 60, 190), 1.f);
	pGraphics->DrawLine(&pen2, m_path.m_points[0], m_path.m_points[1]);
	pGraphics->DrawLine(&pen2, m_path.m_points[3], m_path.m_points[2]);
	*/

//#endif

#if 0
	LDraw::SolidBrush brush2(LDraw::Color(200, 160, 20));
	pGraphics->FillEllipse(&brush2, m_path.m_points[0] - LDraw::PointF(3, 3), LDraw::SizeF(6, 6));
	pGraphics->FillEllipse(&brush2, m_path.m_points[1] - LDraw::PointF(3, 3), LDraw::SizeF(6, 6));
	pGraphics->FillEllipse(&brush2, m_path.m_points[2] - LDraw::PointF(3, 3), LDraw::SizeF(6, 6));
	pGraphics->FillEllipse(&brush2, m_path.m_points[3] - LDraw::PointF(3, 3), LDraw::SizeF(6, 6));
#endif
//	pGraphics->DrawString("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26, font, LDraw::PointF(5, 14), &LDraw::SolidBrush(LDraw::Color::Black));
//	pGraphics->DrawString("abcdefghijklmnopqrstuvwxyz", 26, font, LDraw::PointF(5, 14), &LDraw::SolidBrush(LDraw::Color::Black));
	//pGraphics->DrawString("How", 3, font, LDraw::PointF(20, 60+font->GetSize()), &LDraw::SolidBrush(LDraw::Color::Black));

	{
	//	LDraw::SolidBrush brush(LDraw::Color::Red);
	//	pGraphics->FillRectangle(&brush, -10, -10, m_computedWidth+40, m_computedHeight+20);

	//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Red), -10, -10, m_computedWidth+40, m_computedHeight+20);
	}

//	pGraphics->ScaleTransform(5, 5);
//	pGraphics->FillEllipse(&LDraw::SolidBrush(LDraw::Color::Blue), 0, 0, m_computedWidth, m_computedHeight);
//	pGraphics->DrawString("Disassembly", 11, font, LDraw::PointF(5, 14), &LDraw::SolidBrush(LDraw::Color::Black));

#if 0
	CDCHandle dc = m_pOwnerWindow->m_hdc;

	dc.FillSolidRect(0, 0, 600, 600, RGB(255, 0, 0));

	gmMatrix3 transform = gmMatrix3::scale(10, 10);

	{
		for (int y = -9; y < 1; y++)
		{
		//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Blue), 5*24, (14+y)*24, 10*25, (1.f/24)*24);
			dc.FillSolidRect(5*24, (14+y)*24, 10*25, (1.f/24)*24, RGB(190, 190, 255));
		}
	}

	{
		for (int x = 0; x < 10; x++)
		{
		//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Blue), (5+x)*24, (14-10)*24, (1.f/24)*24, 10*24);
			dc.FillSolidRect((5+x)*24, (14-10)*24, (1.f/24)*24, 10*24, RGB(190, 190, 255));
		}
	}

	LDraw::DrawString(dc, "ABCDEF", 6, font, LDraw::PointF(5, 14), transform);
#endif

	//ReleaseDC(NULL, hDC);

//	pGraphics->DrawString("Y", 1, font, LDraw::PointF(5, 14), &LDraw::SolidBrush(LDraw::Color::Black));
//	return;
/*
	LDraw::PointI points[] =
	{
		LDraw::PointI(10, 10),
		LDraw::PointI(50, 15),
		LDraw::PointI(55, 50),
		LDraw::PointI(40, 30),
	};

	pGraphics->FillPolygon(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), points, 4);
*/

#if 0
#if AMIGA
#if 0

	LDraw::GraphicsPath path(Gdiplus::FillModeAlternate);

	path.AddMove(LDraw::PointF(10, 98));
	path.AddBezier(LDraw::PointF(50, 10), KDraw::PointF(90, 10), Gdiplus::PointF(130, 100));
//	path.AddLine(Gdiplus::PointF(110, 100));
	path.CloseFigure();

	pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(0, 180, 0)), &path);
#endif

#else
	LDraw::GraphicsPath path(Gdiplus::FillModeAlternate);

	path.AddBezier(LDraw::PointF(10, 100), LDraw::PointF(50, 10), Gdiplus::PointF(90, 10), Gdiplus::PointF(130, 100));
	path.CloseFigure();

	pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(0, 180, 0)), &path);

	double mx[4] =
	{
		9999999,
		9999999,
		-9999999,
		-9999999,
	};

	CalcCurveBBox(
		10, 98,
		50, 10,
		90, 10,
		130, 100, mx);

	pGraphics->DrawRectangle(&LDraw::Pen(LDraw::Color::Blue), float(mx[0]), float(mx[1]), float(mx[2]-mx[0]), float(mx[3]-mx[1]));

#endif
#endif

	/*
	Gdiplus::Point points[] =
	{
		Gdiplus::Point(0, 0),
		Gdiplus::Point(10, 100),
		Gdiplus::Point(20, 20),
		Gdiplus::Point(30, 100),
		Gdiplus::Point(40, 0),
		Gdiplus::Point(50, 100),
		Gdiplus::Point(60, 0),
	};

	pGraphics->FillPolygon(&Gdiplus::SolidBrush(Gdiplus::Color(0, 180, 0)), points, 7);
	*/

//	pGraphics->TranslateTransform(40, 100);

//	Gdiplus::DrawString(pGraphics, L"Abc, hello", 10, font, Gdiplus::PointF(40, 100), &Gdiplus::SolidBrush(Gdiplus::Color::Black));
	/*
	Gdiplus::GraphicsPath* path = font->GetGlyph(20);
	if (path)
	{
		pGraphics->FillPath(&Gdiplus::SolidBrush(Gdiplus::Color::Black), path);
		delete path;
	}
	*/
//	pGraphics->DrawPath(&Gdiplus::Pen(Gdiplus::Color::Black), path);

//	CFont font = (HFONT)GetStockObject(ANSI_FIXED_FONT);
//	HFONT hOldFont = dc.SelectFont(font);
//	LOGFONT lf;
//	font.GetLogFont(&lf);

//	m_lineHeight = dc.GetDeviceCaps(LOGPIXELSY) * lf.lfHeight / 72;
	}
	else
	{
		LDraw::Font* pFont = GetFont();

#if WIN32
	if (/*m_pFrame->*/m_ctx /*&& m_pFrame->m_ctx->m_dwProcessId*/)
#endif
	{
#if WIN32
		;//EnterCriticalSection(&m_pFrame->m_bufferCS);
#endif

		int back = 0;

		int y = 0;

		uint8* buffer = m_buffer + m_addroffset;

		int nlines = m_lines.size();

		uint32 eip = m_ctx->GetEip();
	//	if (nlines > 3) nlines = 3;	// TODO remove

		LDraw::SolidBrush* grayBrush = new LDraw::SolidBrush(LDraw::Color(140,140,140));

		for (int i = 0; i < nlines/*-m_linesOffset*/; i++)
		{
			Line* line = m_lines[i/*+m_linesOffset*/];

			if (line->GetKind() == Line::K_INSTR)
			{
				InstrLine* instrline = (InstrLine*)line;

				char straddr[8+1];
				sprintf_s(straddr, "%8.8X", instrline->address);

#if 0
				StringA* strbytes;//[512+1];
				if (m_bViewCodeBytes)
				{
					//char* p = strbytes;
					uint8* pc = (-m_topaddr + buffer + back + line->u.instr.address);
					uint8* pc2 = pc;
					while (pc2 < pc+line->u.instr.nbytes)
					{
						char buf[64];
						sprintf(buf, "%2.2X", *pc2);
						ASSERT(0);
						strbytes += buf;
						pc2++;
					}
					//*p = 0;
				}
#endif

				StringA* strdasm = NULL;

				if (instrline->cpu.pv)
				{
#if WIN32
					if (/*m_pFrame->*/m_ctx->m_cpu == CPU_IX86)
					{
						strdasm = toString(instrline->cpu.x86);
					}
					else
#endif
					if (/*m_pFrame->*/m_ctx->m_cpu == CPU_M68K)
					{
						strdasm = toString(instrline->cpu.m68k);
					}
#if WIN32
					else if (/*m_pFrame->*/m_ctx->m_cpu == CPU_PPC)
					{
						strdasm = toString(instrline->cpu.ppc);
					}
					else if (/*m_pFrame->*/m_ctx->m_cpu == CPU_JAVA_IL)
					{
						strdasm = java::toString(/*m_pFrame->*/m_ctx->m_pJavaVMHost->m_pJavaVM->m_threads[0]->m_pFrame->m_pMethod->m_pOwnerClass, instrline->cpu.java);
					}
					else if (m_ctx->m_cpu == CPU_FLASH_IL)
					{
						strdasm = new StringA(true, SWF::ActionNames[instrline->cpu.actionScript->op]);
					}
#endif
					else
						ASSERT(0);
				}

				//LDraw::RectD rc(14, y, 90, y+m_lineHeight);
				double x = 14;

#if 1
				pGraphics->DrawString(straddr, std::strlen(straddr), pFont, LDraw::PointF(x, y), grayBrush);
#endif
				int codebytesX = x;

				if (m_bViewCodeBytes)
				{
					//rc.Width = rc.left + 160;

					x += 160;//rc.right+4;
				}

				// TODO, first check for int 3
				//ASSERT(0);
				tybreakpointmap::iterator bi = /*m_pFrame->*/m_ctx->m_breakpoints.find(instrline->address);
				if (bi != /*m_pFrame->*/m_ctx->m_breakpoints.end())
				{
				//	Gdiplus::Graphics graphics(dc);

#if 0
					DrawBreakpoint(pGraphics, y+m_lineHeight/2);
#endif
				}

				if (eip >= instrline->address && eip < instrline->address+instrline->nbytes)
				{
					int off = eip - instrline->address;

					int midy = y + m_lineHeight/2;

					DrawYellowArrow(pGraphics, midy);

					if (m_bViewCodeBytes)
					{
#if 0
						CSize size;
						dc.GetTextExtent(strbytes, off*2, &size);

						graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 0)),
							codebytesX + size.cx, rc.top+1, 1, rc.Height()-2);
#endif
					}
				}
#if WIN32
				else if (m_active >= instrline->address && m_active < instrline->address+instrline->nbytes)
				{
					int off = m_ctx->GetEip() - instrline->address;

				//	Gdiplus::Graphics graphics(dc);

					int midy = y + m_lineHeight/2;

					DrawGreenArrow(pGraphics, midy);

#if 0
					if (m_bViewCodeBytes)
					{
						CSize size;
						dc.GetTextExtent(strbytes, off*2, &size);

						graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(0, 190, 0)),
							codebytesX + size.cx, rc.top+1, 1, rc.Height()-2);
					}
#endif
				}
#endif

			//	x = m_computedSize.Width-4;

#if 1
				if (strdasm)
				{
					pGraphics->DrawString(strdasm, pFont, LDraw::PointF(x, y), grayBrush);
				}
#endif
			}
			else
			{
				TextLine* textline = (TextLine*)line;
#if 0//_WINDOWS
				CRect rc(0, y, 32, y+16);
			//	dc.SetTextColor(RGB(0,0,0));

				char nlinestr[16];
				sprintf(nlinestr, "%d", line->u.text.lineNumber+1);
			//	dc.DrawText(nlinestr, strlen(nlinestr), &rc, DT_SINGLELINE | DT_RIGHT);

				rc.left = rc.right+4;
				rc.right = client.right;
			//	dc.DrawText(line->u.text.p, strlen(line->u.text.p), &rc, DT_EXPANDTABS);
#else
				LDraw::RectD rc(0, y, 32, 16);
				LDraw::SolidBrush* blackBrush = new LDraw::SolidBrush(LDraw::Color::Black);
				pGraphics->DrawString(textline->str, pFont, LDraw::PointF(rc.X, rc.Y), blackBrush);
#endif
			}

			y += m_lineHeight;
		}

#if _WINDOWS
		;//LeaveCriticalSection(&m_pFrame->m_bufferCS);
#endif
	}
	}

}

#if 0//_WINDOWS
/*
LRESULT DisassemblyWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client = GetClientRect();
	OnSize(client.Width(), client.Height());
	return 0;
}
*/

#if 0
LRESULT DisassemblyWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);


	return 0;
}
#endif

LRESULT DisassemblyWnd::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CMenu menu;
	menu.LoadMenu(IDR_DISASM);
	menu.GetSubMenu(0).TrackPopupMenu(0, point.x, point.y, m_hWnd);
#endif
	return 0;
}

LRESULT DisassemblyWnd::OnToggleBreakpoint(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pFrame->m_dwProcessId);//m_ctx->GetProcessById(m_dwProcessId);

	BYTE instruction;
	ULONG nRead;
	ReadProcessMemory(hProcess, (LPVOID)m_topaddr, &instruction, 1, &nRead);

	ASSERT(lines[0]->kind == Line::K_INSTR);

	m_pFrame->m_breakpoints.insert(tybreakpointmap::value_type(m_topaddr, Breakpoint(instruction/*, lines[0]->u.instr.nbytes*/)));

	instruction = 0xCC;	// int 3

	ULONG nWritten;
	WriteProcessMemory(hProcess, (LPVOID)m_topaddr, &instruction, 1, &nWritten);

	CloseHandle(hProcess);
#endif

	ASSERT(m_lines[0]->kind == Line::K_INSTR);

	m_pFrame->m_ctx->AddBreakpoint(m_topaddr);

	ReadBuffer();
	Invalidate();

	return 0;
}

#if 0

		if (stab != NULL)
		{
			char* sourceFileName = NULL;
			for (int i = 0; i < nstabs; i++)
			{
			//	nlist* n = (nlist*)p;
				filepointer<nlist> pSymbol = stab + i;//(ObjectSymbol*)p;
				if (pSymbol->n_type == N_SO)
				{
					char* name = stabstr + pSymbol->n_un.n_strx;
				// If it ends with a slash, it's the directory where it was compiled, so keep searching
					if (name[strlen(name)-1] != '/')
					{
						sourceFileName = name;
						break;
					}
				}
			}

			std::vector<StringA> lines;
			if (sourceFileName)
			{
				FILE* sfp = fopen(sourceFileName, "r");

				StringA str;

				while (!feof(sfp))
				{
					int c = fgetc(sfp);

					str += c;

					if (c == '\n')
					{
						lines.push_back(str);
						str = "";
					}
				}
				if (str.length())
					lines.push_back(str);

				fclose(sfp);
			}

			int nstab = 0;

			CX86Context c;
			c.pc = code;
			DWORD last_fun_address = 0;
			DWORD line_address = 0;
			int start_line = 0;
			int end_line = 0;

			DWORD base = windowsHeader.ImageBase + SectionHeader[0/*TODO*/].VirtualAddress;
			while (c.pc < code+40)
			{
				// Collect the lines that precede the next intruction
				while ((nstab < nstabs) &&
					line_address <= (c.pc - code + base))
				{
					filepointer<nlist> pSymbol = stab + nstab;

					if (pSymbol->n_type == N_FUN)
					{
						last_fun_address = pSymbol->n_value;
					}
					else if (pSymbol->n_type == N_SLINE)
					{
						int address = last_fun_address + pSymbol->n_value;

						// If this lines address is past, we break out and come back
						// to it in the next iteration
						if (address > (c.pc - code + base))
							break;

						line_address = address;
						end_line = pSymbol->n_desc;
					}

					nstab++;
				}

				{
					for (int i = start_line; i < end_line; i++)
					{
						printf("%5.d: %s", i+1, lines[i].c_str());
					}
					start_line = end_line;
				}

				printf("%6.6x ", c.pc - code + base);

				BYTE* p = c.pc;

				printf("%x\t", *p);
				disasm_x86(&c);

				printf("\n");
			}

#endif

LRESULT DisassemblyWnd::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nVirtKey = (int) wParam;    // virtual-key code 
	int lKeyData = lParam;          // key data 

	switch (nVirtKey)
	{
	case VK_UP:
		{
			ScrollUp(1);
		}
		break;

	case VK_DOWN:
		{
			ScrollDown(1);
		}
		break;

	case VK_PRIOR:
		{
			ScrollUp(20);
		}
		break;

	case VK_NEXT:
		{
			ScrollDown(20);
		}
		break;
	}

	Invalidate();

	return 0;
}

LRESULT DisassemblyWnd::OnViewCodeBytes(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bViewCodeBytes = !m_bViewCodeBytes;
//	UISetCheck(ID_DISASM_CODEBYTES, m_bViewCodeBytes);
	Invalidate();
	return 0;
}

#endif // _WINDOWS

}
}
