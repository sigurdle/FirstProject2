#include "stdafx.h"

#ifdef AMIGA
#define new DEBUG_NEW
#endif

#include "LDebugger.h"
#include "WatchWnd.h"

#include "../CodeComp/cpp_translate.h"

//extern LDraw::Font* font;

#if AMIGA

extern struct Task* task;
extern long debugger_regs[16];

#endif

namespace System
{
namespace cpp
{
namespace ast
{
CodeCompExt A_Exp* parse_expression(StringA* str);
}
}
}

namespace System
{
namespace Debugger
{

#if __APPLE__

BOOL ReadProcessMemory(PlatformProcess task, const void* lpBaseAddress, void* lpBuffer, unsigned long nSize, unsigned long* lpNumberOfBytesRead)
{
	return TRUE;
}

BOOL WriteProcessMemory(PlatformProcess task, void* lpBaseAddress, const void* lpBuffer, unsigned long nSize, unsigned long* lpNumberOfBytesWritten)
{
	return TRUE;
}

#endif

extern Scope* pGlobalScope;

#if WIN32
extern __live_object_ptr<DebugThread> g_pt;
#endif

Scope* FindScope(Scope* pScope, ULONG_PTR find_address);

WatchExpression::WatchExpression(StringA* str)
{
	m_edit = new UI::TextEdit;
	m_edit->set_Text(str->ToStringW());

	m_result = new UI::TextString;

	m_item.m_name = str;

	m_exp = NULL;

// Probably need to do this later, as how it works now, ast tree depends on type info

	/*
	cpp::ast::yy_buffer_state* state = cpp::ast::cpp2__scan_string(str->c_str());
	cpp::ast::g_exp = NULL;
	cpp::ast::cpp_exp_parse();

	m_exp = cpp::ast::g_exp;
	*/
}

/*
WatchExpression& WatchExpression::operator = (StringA* str)
{
	m_item.m_name = str;

	//ASSERT(0);
#if 0

#endif

	return *this;
}
*/

/*
void FunBody(cpp::CDeclarator* pDeclarator, A_Declaration* d, cpp::CGlobal* pGlobal, cpp::Scope* pScope)
{
	ASSERT(0);
}
*/

struct Result
{
	uint8* buf;
	long size;
};

void eval(T_Stm* s, PlatformProcess hProcess)
{
	switch (s->kind)
	{
	case T_Stm::T_CJUMP:
		{
			switch (s->cjump.relop)
			{
			case '<':
				break;
			case '>':
				break;
				
				ASSERT(0);
			}
		}
		break;

	default:
		ASSERT(0);
	}
}


long eval(T_Exp* e, PlatformProcess hProcess)
{
	switch (e->kind)
	{
	case T_Exp::T_MEM:
		{
			//printf("mem(");
			long addr = eval(e->mem.mem, hProcess);
			//printf(")size(%d)", e->mem.size);

			uint8* buf = (uint8*)malloc(e->mem.size);


			MSWindows::DWORD nRead;
			MSWindows::ReadProcessMemory(hProcess, (LPVOID)addr, buf, e->mem.size, &nRead);

			if (e->mem.size == 1)
				return *(char*)buf;
			else if (e->mem.size == 2)
				return *(short*)buf;
			else if (e->mem.size == 4)
				return *(long*)buf;
			/*
			else if (e->mem_size == 8)
				return *(char*)buf;
				*/
			else
				ASSERT(0);
		}
		break;

	case T_Exp::T_CONST:
		{
			//printf("%d", e->const_int.int32);
			return e->const_int.int32;
		}
		break;

	case T_Exp::T_BINOP:
		{
			//printf("binop(");
			long e1 = eval(e->binop.left, hProcess);
			//printf(",");
			long e2 = eval(e->binop.right, hProcess);
			//printf(",");

			switch (e->binop.op)
			{
			case '+':
				{
				//	printf("+)");
					return e1+e2;
				}
				break;

			case '<':
				{
					return e1 < e2;
				}
				break;

			case '>':
				{
					return e1 > e2;
				}
				break;

			case '<=':
				{
					return e1 <= e2;
				}
				break;

			case '>=':
				{
					return e1 >= e2;
				}
				break;

			case '==':
				{
					return e1 == e2;
				}
				break;

			case '!=':
				{
					return e1 != e2;
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;

	case T_Exp::T_TEMP:
		{
			if ((*e->temp)->getn() == 5)
			{
#if WIN32
				return g_pt->m_context.Ebp;
#elif AMIGA
			//	printf("%X", regs[8+5]);
				return debugger_regs[8+5];
#elif __APPLE__
				// TODO
				return 0;
#endif
			}
			else
				ASSERT(0);
		}
		break;

		/*
	case T_Exp::T_ESEQ:
		{
			ATLASSERT(0);
			//e->eseq.
		}
		break;
		*/

	case T_Exp::T_NAME:
		{
		//	printf("%d", e->name.label->m_spOffset);
			return e->name.label->m_spOffset;
		}
		break;

	default:
		ASSERT(0);
	}

	return 0;
}

WatchWnd::WatchWnd()
{
	m_ctx = NULL;

	m_tree = new UI::TreeControl;

	m_tree->AddColumn(new UI::TextString(WSTR("Expression")));
	m_tree->AddColumn(new UI::TextString(WSTR("Result")));

	UI::TreeItemChildren* children = new UI::TreeItemChildren(m_tree);

	m_tree->set_Children(children);

	set_VisualTree(m_tree);
}

void WatchWnd::AddWatchExpression(WatchExpression* exp)
{
	m_watchList.push_back(exp);

	UI::TreeItem* item = new UI::TreeItem(m_tree);
	item->AppendColumnCell(exp->m_edit);
	item->AppendColumnCell(exp->m_result);

	ASSERT(0);
	//m_tree->get_Children()->AddChild(item);

	//AddRChild(exp);
}

void WatchWnd::set_Context(DebuggerCtx* ctx)
{
	m_ctx = ctx;

// TODO, subscribe to events
}

int WatchWnd::DrawItem(UI::Graphics* pGraphics, int x, int y, WatchItem* pItem, PlatformProcess hProcess)
{
//	USES_CONVERSION;

//	CRect client = GetClientRect();

	LDraw::RectD rect(x+14, y, 100-x-14, 16);

//	dc.DrawText(pItem->m_name.c_str(), pItem->m_name.length(), &rect, DT_SINGLELINE);
	pGraphics->DrawString(pItem->m_name, GetFont(), LDraw::PointF(rect.X, rect.Y), new LDraw::SolidBrush(LDraw::Color::Black));
	rect.X = rect.GetRight()+1;
	rect.Width = m_computedSize.Width - rect.X;

	{
		pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(192, 192, 192)), 0, y+17-1, 100, 1);
	}

	if (hProcess)
	{
		if (pItem->m_texp)
		{
#if 1
			System::Type* pType = pItem->m_texp->m_pType;

			BufferImp<char> buffer;
			StringBuilderA valuestr(&buffer);

			if (pType->get_Kind() != type_class)
			{
			//	printf("1\n");
				T_Exp* exp = unEx(pItem->m_texp);
			//	printf("2\n");

				long value = eval(exp, hProcess);

			//	printf("10\n");

				if (pType->get_Kind() == type_char)
				{
					char buf[64];
					sprintf_s(buf, "'%c' %d", value, value);
					valuestr << buf;
				}
				else if (pType->get_Kind() == type_pointer)
				{
					{
						char buf[64];
						sprintf_s(buf, "0x%8.8X", value);
						valuestr << buf;
					}

					if (pType->GetPointerTo()->get_Kind() == type_char)
					{
						char buf[64+1];
						ULONG nRead;
						MSWindows::ReadProcessMemory(hProcess, (LPVOID)value, buf, 64, &nRead);

						buf[64] = 0;

						ASSERT(0);
#if 0

						valuestr += OLESTR(" \"");
						valuestr += ConvertA2S(buf);
						valuestr += OLESTR("\"");
#endif
					}
				}
				else if (pType->get_Kind() == type_bool)
				{
					if (value == 1)			valuestr << "true";
					else if (value == 0)		valuestr << "false";
					else							
					{
						char buf[64];
						sprintf_s(buf, "%d", value);
						valuestr << buf;
					}
				}
				else
				{
					char buf[64];
					sprintf_s(buf, "%d", value);
					valuestr << buf;
				}
			}

			//if (valuestr)
			{
				pGraphics->DrawString(buffer.DetachToString(), GetFont(), LDraw::PointF(rect.X, rect.Y), new LDraw::SolidBrush(LDraw::Color::Black));
			//	dc.DrawText(valuestr, strlen(valuestr), &rect, DT_SINGLELINE);
			}

			if (	pType->get_Kind() == type_class ||
					pType->get_Kind() == type_pointer)
			{
				{
				//	pGraphics->DrawRectangle(&LDraw::Pen(LDraw::Color(90,90,90)), x+2, y+2, 10, 10);
				}

				if (pItem->m_bExpanded)
				{
				//	dc.TextOut(x+3, y, "-");

					y += 16+1;

					for (int i = 0; i < pItem->m_subItems.size(); i++)
					{
						y = DrawItem(pGraphics, x+16, y, pItem->m_subItems[i], hProcess);
					}
				}
				else
				{
				//	dc.TextOut(x+3, y, "+");
					y += 16+1;
				}
			}
			else
			{
				y += 16+1;
			}
#endif
		}
		else
		{
			char* str = "error";
			pGraphics->DrawString(str, std::strlen(str), GetFont(), LDraw::PointF(101, y), new LDraw::SolidBrush(LDraw::Color::Black));

			y += 16+1;
		}
	}
	else
	{
		y += 16+1;
	}

	return y;
}

#if 0
void WatchWnd::OnRender(UI::Graphics* pGraphics)
{
	//printf("WatchWnd::OnRender2\n");
	{
		LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));
		pGraphics->FillRectangle(brush, 0, 0, m_computedSize.Width, m_computedSize.Height);
	}

	//CPaintDC dc(m_hWnd);
	//CFont font = (HFONT)GetStockObject(ANSI_FIXED_FONT);
	//HFONT hOldFont = dc.SelectFont(font);
	//dc.SetBkMode(TRANSPARENT);

	{
	//	Gdiplus::Graphics graphics(dc);
	//	pGraphics->DrawLine(&Gdiplus::Pen(Gdiplus::Color(192, 192, 192)), 100, 0, 100, m_watchList.size()*16);
		pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(192, 192, 192)), 100, 0, 1, m_watchList.size()*16);
	}

	PlatformProcess hProcess = NULL;

#if WIN32

	if (m_pFrame->m_ctx)
	{
		hProcess = MSWindows::OpenProcess(PROCESS_ALL_ACCESS, false, m_pFrame->m_ctx->m_dwProcessId);
	}

#elif AMIGA

	hProcess = task;

#elif __APPLE__

	hProcess = NULL;

#endif

	int y = 0;
	for (int i = 0; i < m_watchList.size(); i++)
	{
		WatchExpression* pItem = m_watchList[i];

		y = DrawItem(pGraphics, 0, y, &pItem->m_item, hProcess);
	}

#if WIN32

	if (hProcess)
		MSWindows::CloseHandle(hProcess);

#endif

//	dc.SelectFont(hOldFont);
#if 0
		if (pItem->m_pDeclarator)
		{
			cpp::Type* pType = pItem->m_pDeclarator->m_pType->GetType();
			if (pType->m_type == cpp::type_class)
			{
				dc.TextOut(0, y, "+");

				if (TRUE)
				{
					y += 16;
					cpp::declsmap::iterator decli = pType->m_pClass->m_pScope->m_decls.begin();
					while (decli != pType->m_pClass->m_pScope->m_decls.end())
					{
						cpp::CDeclarator* pMemberDecl = (*decli).second->m_pDeclarator;
						dc.TextOut(10, y, pMemberDecl->m_name.c_str());

						y += 17;
						decli++;
					}
				}
			}

		//	char buf[32];
		//	sTRACE(buf, "%d", pItem->m_value);
		//	dc.TextOut(60, y, buf);

		}
		else
		{
			char* str = "not found";
			dc.TextOut(60, y, str);
		}
#endif
}
#endif

/*
LDraw::SizeD WatchWnd::OnMeasure(LDraw::SizeD viewBox)
{
	// TODO, improve
	return LDraw::SizeD(180, m_watchList.size() * 17);
}
*/

void WatchWnd::ExpandClass(WatchItem* pItem, System::Type* pType, T_Exp* exp)
{
	declsmap::iterator di = pType->GetClass()->m_pScope->m_decls.begin();
	while (di != pType->GetClass()->m_pScope->m_decls.end())
	{
		CDeclarator* pDeclarator = (*di).second;//->m_pDeclarator;

		Tr_Exp* pT;
		pT = Tr_Ex(
			T_Mem(
			T_BinopExp('+', exp, T_ConstExp(pDeclarator->m_offset)), pDeclarator->m_pType->GetType()->get_sizeof()));

		pT->m_pType = pDeclarator->m_pType;

		WatchItem* pSubItem = new WatchItem;
		pSubItem->m_name = pDeclarator->m_name;
		pSubItem->m_texp = pT;

		pItem->m_subItems.Add(pSubItem);

		++di;
	}
}

void WatchWnd::Expand(WatchItem* pItem)
{
	System::Type* pType = pItem->m_texp->m_pType->GetType();
	T_Exp* exp = unEx(pItem->m_texp);

	if (pType->get_Kind() == type_pointer)	// dereference pointer
	{
		pType = pType->GetPointerTo()->GetType();

		if (pType->get_Kind() == type_class)
		{
			ExpandClass(pItem, pType, exp);
		}
		else
		{
			Tr_Exp* pTExpr;
			pTExpr = Tr_Ex(T_Mem(exp, pType->get_sizeof()));
			pTExpr->m_pType = pType;

			WatchItem* pSubItem = new WatchItem;
			pSubItem->m_texp = pTExpr;
			pItem->m_subItems.Add(pSubItem);
		}
	}
	else	// class
	{
		ASSERT(exp->kind == T_Exp::T_MEM);
		exp = exp->mem.mem;

		ExpandClass(pItem, pType, exp);
	}
}

void WatchWnd::OnExpand(WatchItem* pItem)
{
	if (!pItem->m_bExpanded)
	{
		pItem->m_bExpanded = true;
		Expand(pItem);
	}
	else
	{
		pItem->m_bExpanded = false;
		pItem->m_subItems.clear();
	}
}

#if 0
LRESULT WatchWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	if (m_edit.m_hWnd)
	{
		WatchExpression* pItem = m_watchList[m_index];

		char str[1024];
		m_edit.GetWindowText(str, 1023);

		*pItem = str;

		m_edit.DestroyWindow();

		UpdateWatchExpression(pItem);
		Invalidate();
	}
	else
#endif
	{
		CPoint point;
		point.x = (short)LOWORD(lParam);
		point.y = (short)HIWORD(lParam);

		int index = point.y / 17;
		if (index >= 0 && index < m_watchList.size())
		{
			WatchExpression* pItem = m_watchList[index];

			if (point.x < 10)
			{
				cpp::Type* pType = pItem->m_item.m_texp->m_pType->GetType();
				if (	pType->m_type == cpp::type_class ||
						pType->m_type == cpp::type_pointer)
				{
					OnExpand(&pItem->m_item);
					Invalidate();
				}
			}
			else
			{
				m_index = index;

#if 0	// TODO
				m_edit.Create(m_hWnd, CRect(9, m_index*17-1, 100, m_index*17+17), NULL, ES_AUTOHSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE);

				CFont font = (HFONT)GetStockObject(ANSI_FIXED_FONT);
				m_edit.SetFont(font);

				m_edit.SetWindowText(pItem->m_item.m_name.c_str());
				m_edit.SetSel(0, -1);
				m_edit.SetFocus();
#endif
			}
		}
	}

	return 0;
}
#endif

/*
void WatchWnd::UpdateItem(WatchItem* pItem)
{

	for (int i = 0; i < pItem->m_subItems.size(); i++)
	{
	}
}
*/

void WatchWnd::UpdateWatchExpression(WatchExpression* pItem, PlatformProcess hProcess)
{
	pItem->m_exp = cpp::ast::parse_expression(pItem->m_item.m_name);

	if (pItem->m_exp)
	{
		Scope* pScope = FindScope(pGlobalScope, m_ctx->GetEip());

		CGlobal* pGlobal = new CGlobal;

		pItem->m_item.m_texp = cpp::TransExpression(NULL/*T_Declarator* frame*/, pItem->m_exp, pGlobal, pScope);

		if (hProcess)
		{
			if (pItem->m_item.m_texp)
			{
				System::Type* pType = pItem->m_item.m_texp->m_pType;

				BufferImp<char> buffer;
				StringBuilderA valuestr(&buffer);

				if (pType->get_Kind() != type_class)
				{
				//	printf("1\n");
					T_Exp* exp = unEx(pItem->m_item.m_texp);
				//	printf("2\n");

					long value = eval(exp, hProcess);

				//	printf("10\n");

					if (pType->get_Kind() == type_char)
					{
						char buf[64];
						sprintf_s(buf, "'%c' %d", value, value);
						valuestr << buf;
					}
					else if (pType->get_Kind() == type_pointer)
					{
						{
							char buf[64];
							sprintf_s(buf, "0x%8.8X", value);
							valuestr << buf;
						}

						if (pType->GetPointerTo()->get_Kind() == type_char)
						{
							char buf[64+1];
							ULONG nRead;
							MSWindows::ReadProcessMemory(hProcess, (LPVOID)value, buf, 64, &nRead);

							buf[64] = 0;

							ASSERT(0);
	#if 0

							valuestr += OLESTR(" \"");
							valuestr += ConvertA2S(buf);
							valuestr += OLESTR("\"");
	#endif
						}
					}
					else if (pType->get_Kind() == type_bool)
					{
						if (value == 1)			valuestr << "true";
						else if (value == 0)		valuestr << "false";
						else							
						{
							char buf[64];
							sprintf_s(buf, "%d", value);
							valuestr << buf;
						}
					}
					else
					{
						char buf[64];
						sprintf_s(buf, "%d", value);
						valuestr << buf;
					}
				}

				//if (valuestr)
				{
				//	pGraphics->DrawString(buffer.DetachToString(), GetFont(), LDraw::PointF(rect.X, rect.Y), new LDraw::SolidBrush(LDraw::Color::Black));
					pItem->m_result->set_TextContent(buffer.DetachToString()->ToStringW());
				}
			}
			else
			{
				pItem->m_result->set_TextContent(WSTR("error"));
			}
		}
	}
	else
	{
		pItem->m_item.m_texp = NULL;
		pItem->m_result->set_TextContent(WSTR("error"));
	}
}

void WatchWnd::Update()
{
	PlatformProcess hProcess = NULL;

#if WIN32

	if (m_ctx)
	{
		hProcess = MSWindows::OpenProcess(PROCESS_ALL_ACCESS, false, m_ctx->m_dwProcessId);
	}

#elif AMIGA

	hProcess = task;

#elif __APPLE__

	hProcess = NULL;

#endif

//	TRACE("1\n");
	if (pGlobalScope)
	{
//	TRACE("2\n");
		for (int i = 0; i < m_watchList.size(); i++)
		{
			WatchExpression* pItem = m_watchList[i];

			UpdateWatchExpression(pItem, hProcess);
		}
	}

#if WIN32

	if (hProcess)
		MSWindows::CloseHandle(hProcess);

#endif

	Invalidate();

#if 0
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pFrame->m_ctx->dwProcessId);
	if (hProcess)
	{
		for (int i = 0; i < m_watchList.size(); i++)
		{
			WatchItem* pItem = m_watchList[i];
		//	pItem->m_pDeclarator = NULL;

			cpp::CGlobal* pGlobal = new cpp::CGlobal;
			pItem->m_texp = TransExpression(NULL/*T_Declarator* frame*/, pItem->m_exp, pGlobal, pGlobalScope);

#if 0
			for (int i = 0; i < m_pFrame->m_ctx->sourceFiles.size(); i++)
			{
				SourceFile* sourceFile = m_pFrame->m_ctx->sourceFiles[i];

				cpp::declsmap::iterator decli = pGlobalScope->m_decls.find(pItem->m_name);
				if (decli != pGlobalScope->m_decls.end())
				{
					pItem->m_pDeclarator = (*decli).second->m_pDeclarator;

					/*
					DWORD nRead;
					long value;
					ReadProcessMemory(hProcess, (LPVOID)(g_pt->m_context.Ebp + pDecl->m_offset),&value, 4, &nRead);

					pItem->m_value = value;
					*/
				}
			}
#endif
		}

		CloseHandle(hProcess);
	}
#endif
}

}
}
