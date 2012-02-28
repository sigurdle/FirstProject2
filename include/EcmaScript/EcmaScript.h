#ifndef EcmaScript_h
#define EcmaScript_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "CodeComp/CodeComp.h"
#else
#include "CodeComp/CodeComp.h"
#endif

/*
#ifdef __LERSTAD__
#import "ActionScript2/ActionScript2.h"
#else
#include "ActionScript2/ActionScript2.h"	// TODO remove
#endif
*/

/*
#ifdef __LERSTAD__
#import "JSVM/JSVM.h"
#else
#include "JSVM/JSVM.h"	// TODO remove
#endif
*/

#ifndef ECMAEXT
#define ECMAEXT DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace ecma
{

class ECMAEXT ScriptCode
{
public:
	void AddText(StringIn code);

	vector<uint8> m_code;

//	JSVM::ActionContext* m_as_context;
//	JSVM::StackFrame* m_root;

	ConstantPool* m_as_context;
//	ActionScripting::StackFrame* m_root;
};

// translate

}

}

#include "ecmascript_ast.h"

#include "GenActionScript2.h"

#endif	// EcmaScript
