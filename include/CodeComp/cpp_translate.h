#pragma once

#include "ir.h"

namespace System
{
namespace cpp
{

class CGlobal;

int not_relop(int relop);

namespace ast
{
class Expression;
}

CodeCompExt Tr_Exp* TransExpression(T_Declarator* frame, ast::Expression* pExpr, CGlobal* pGlobal, System::Scope* pScope);

}
}
