#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

ExpressionBinding::ExpressionBinding(DependencyObject* _this, Expressive::Expression* exp) :
	m_this(_this),
	m_exp(exp)
{
	Expressive::EvalContext evalContext;
	evalContext.m_this = m_this;
	evalContext.m_userObject = this;
	m_exp->TraceCallback(&evalContext, Expressive::ExpTrace(), NULL);
}

Type* ExpressionBinding::GetOutputType()
{
	return m_exp->m_pType;
}

void* ExpressionBinding::Connect(IInputBinding* binding)
{
	if (m_outBinding != NULL)
	{
		ASSERT(0);
	}

	m_outBinding = binding;
	return binding;
}

Variant ExpressionBinding::GetOutput(IBinding* caller)
{
	// hmm

	Expressive::EvalContext evalContext;
	evalContext.m_this = m_this;
//	evalContext.m_templatedOwner = GetTemplatedOwner(m_this);
	return m_exp->Evaluate(&evalContext);
}

int ExpressionBinding::SetOutput(IBinding* caller, const Variant& value)
{
	ASSERT(caller);
	ASSERT(m_outBinding == caller);

	Expressive::EvalContext context;
	context.m_this = m_this;
//	context.m_templatedOwner = GetTemplatedOwner(m_this);
	context.m_userObject = this;
	m_exp->Set(&context, value);
	return 0;
}

int ExpressionBinding::SetOutput(IBinding* caller, float value)
{
	ASSERT(caller);
	ASSERT(m_outBinding == caller);

	Expressive::EvalContext context;
	context.m_this = m_this;
//	context.m_templatedOwner = GetTemplatedOwner(m_this);
	context.m_userObject = this;
	m_exp->Set(&context, value);
	return 0;
}

void ExpressionBinding::ReEval()
{
	if (m_outBinding)
	{
		Expressive::EvalContext context;
		context.m_this = m_this;
//		context.m_templatedOwner = GetTemplatedOwner(m_this);
		context.m_userObject = this;
		Variant value2 = m_exp->Evaluate(&context);

		m_outBinding->SetInput(this, value2);
	}
}

int ExpressionBinding::SetInput(IBinding* caller, const Variant& value)
{
	ASSERT(0);

	ASSERT(caller);
	ASSERT(m_inBindings.find(caller) != m_inBindings.end());

	if (m_outBinding)
	{
		Expressive::EvalContext context;
		context.m_this = m_this;
//		context.m_templatedOwner = GetTemplatedOwner(m_this);
		context.m_userObject = this;
		Variant value2 = m_exp->Evaluate(&context);

		m_outBinding->SetInput(this, value2);
	}

	return 0;
}

}	// Gui
}	// System
