#ifndef LDebugger_h
#define LDebugger_h

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LXUI.typeinfo"
#else
#include "../LXUI/LXUI.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/CodeComp.typeinfo"
#else
#include "../CodeComp/CodeComp.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/javavm.typeinfo"
#else
#include "../javavm/javavm.h"
#endif

#ifdef WIN32
#include "../include/coff.h"
#endif

#include "../include/stab.h"
#include "../Include/AmigaHunkParser.h"

#define DebuggingExt

namespace System
{
namespace Debugger
{

class DebuggerFrame;
class WatchWnd;
class SourceEdit;
class SourceEditFrame;

}	// Debugger
}

namespace System
{
namespace ActionScripting
{

class DasmContext : public MContext
{
public:

};

class Instruction : public MInstruction
{
public:
	uint8 op;
};

Instruction* disasm(DasmContext* context, void* reserved);

}
}

#include "javadisasm.h"
#include "DebuggerFrame.h"
#include "CallStackWnd.h"
#include "WatchWnd.h"
//#include "DebugSession.h"
#include "DisassemblyWnd.h"
#include "SourceEdit.h"
#include "SourceEditFrame.h"

#include "TTDebuggerFrame.h"

class TestingRemote : public System::Object
{
public:
	CTOR TestingRemote();

	virtual int TestMethod(System::StringW* param);
};

#endif	// LDebugger_h
