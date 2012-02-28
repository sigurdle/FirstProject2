#include "stdafx.h"
#include "SQL.h"
#include "sql_a.h"

namespace System
{
namespace sql
{
namespace ast
{

SelectStm::SelectStm(IdList* columns, IdList* from, Exp* whereCriteria)
{
	m_columns = columns;
	m_from = from;
	m_whereCriteria = whereCriteria;
}

DeleteStm::DeleteStm(const char* from, Exp* whereCriteria)
{
	m_from = from;
	m_whereCriteria = whereCriteria;
}

Exp* sql_A_Id(const char* name)
{
	Exp* p = new Exp;
	p->kind = Exp::K_ID;
	p->u.ID.name = _strdup(name);
	return p;
}

Exp* sql_A_Const(long int32)
{
	Exp* p = new Exp;
	p->kind = Exp::K_CONST_INT32;
	p->u.int32 = int32;
	return p;
}

/*
sql_A_Exp* sql_A_Const(const char* string)
{
	sql_A_Exp* p = new sql_A_Exp;
	p->kind = sql_A_Exp::K_CONST_STRING;
	p->u.STRING.p = strdup(string);
	p->u.STRING.len = strlen(string);
	return p;
}
*/

Exp* sql_A_Unop(int op, Exp* node)
{
	Exp* p = new Exp;
	p->kind = Exp::K_UNOP;
	p->u.UNOP.op = op;
	p->u.UNOP.node = node;

	return p;
}

Exp* sql_A_Binop(int op, Exp* left, Exp* right)
{
	Exp* p = new Exp;
	p->kind = Exp::K_BINOP;
	p->u.BINOP.op = op;
	p->u.BINOP.left = left;
	p->u.BINOP.right = right;

	return p;
}

}	// ast
}	// sql
}	// System
