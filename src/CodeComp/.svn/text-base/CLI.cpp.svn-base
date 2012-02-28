#include "stdafx.h"
#include "CLI.h"

namespace System
{
namespace CLI
{

///////////////////////////
// MethodState

void MethodState::push(Operand value)
{
	m_operands.Add(value);
}

Operand MethodState::pop()
{
	int size = m_operands.GetSize();
	if (size <= 0) THROW(-1);
	Operand elt = m_operands[m_operands.GetSize()-1];
	m_operands.RemoveAt(m_operands.GetSize()-1);
	return elt;
}

Thread::tyfunc Thread::funcs[256] =
{
	NULL
};

int Thread::next_instruction()
{
	return (this->*funcs[*pc])(this);
}

}
}
