#include "stdafx.h"
#include "LXUI2.h"

#include "../CodeComp/ir.h"

#include "ActionScript.h"

#include "ecmascript_ast.h"

namespace System
{
namespace ecma
{
//#include "lex.ecmascript.h"
#include "ecmascript_parse.tab.h"

extern	A_ElemList* g_program;

	int ecmascriptparse();

struct yy_buffer_state;
yy_buffer_state* ecmascript_scan_string( const char *yy_str );

T_StmList* translate(A_ElemList* elems, ActionScripting::ActionContext*, map<StringA*, uint16, Ref_Less<StringA> > & pool);
void munch(T_StmList* stms, vector<as_instr*> & instrs, ActionScripting::ActionContext*, map<StringA*, uint16, Ref_Less<StringA> > & pool);
}

void ScriptCode::AddText(StringW* code)
{
	StringA* adata = code->ToStringA();

	const char* command = adata->c_str();
	ecma::yy_buffer_state* state = ecma::ecmascript_scan_string(command);
//	g_stm = NULL;
	int error = ecma::ecmascriptparse();
	ASSERT(error == 0);
	ecma::A_ElemList* sourceElems = ecma::g_program;//ecma::ecmascript_lval.elem_list;

	ASSERT(sourceElems);

	m_as_context = new ActionScripting::ActionContext;

	map<StringA*, uint16, Ref_Less<StringA> > pool;

	T_StmList* slist = ecma::translate(sourceElems, m_as_context, pool);
//	ecma::munch(sourceElems);

//	CTStatement* pStmt;
//	T_stmList* slist = /*pDeclarator->m_statementList =*/ linearize(pStmt);

	vector<ecma::as_instr*> instrs;

	ecma::munch(slist, instrs, m_as_context, pool);

	m_code.clear();

	//vector<uint8> data;
	for (int i = 0; i < instrs.size(); i++)
	{
		for (int j = 0; j < instrs[i]->data.size(); j++)
			m_code.push_back(instrs[i]->data[j]);
	}
}

namespace UI
{

Script::Script()
{
	m_root = NULL;
	m_as_context = NULL;
}

uint8* Script::GetCodeData()
{
	return m_code.begin();
}

ULONG Script::GetCodeLength()
{
	return m_code.size();
}

void Script::AddChild(System::Object* child)
{
	throw std::exception("child object not supported");
}

void Script::AddText(System::StringW* text)
{
	set_Code(text);
}

void Script::set_Code(StringW* code)
{
	StringA* adata = code->ToStringA();

	const char* command = adata->c_str();
	ecma::yy_buffer_state* state = ecma::ecmascript_scan_string(command);
//	g_stm = NULL;
	ecma::ecmascriptparse();
	ecma::A_ElemList* sourceElems = ecma::g_program;//ecma::ecmascript_lval.elem_list;

	ASSERT(sourceElems);

	m_as_context = new ActionScripting::ActionContext;

	map<StringA*, uint16, Ref_Less<StringA> > pool;

	T_StmList* slist = ecma::translate(sourceElems, m_as_context, pool);
//	ecma::munch(sourceElems);

//	CTStatement* pStmt;
//	T_stmList* slist = /*pDeclarator->m_statementList =*/ linearize(pStmt);

	vector<ecma::as_instr*> instrs;

	ecma::munch(slist, instrs, m_as_context, pool);

	m_code.clear();

	//vector<uint8> data;
	for (int i = 0; i < instrs.size(); i++)
	{
		for (int j = 0; j < instrs[i]->data.size(); j++)
			m_code.push_back(instrs[i]->data[j]);
	}
}

}	// UI
}
