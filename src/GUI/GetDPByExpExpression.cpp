#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

Variant GetDPByExpExpression::Evaluate(Expressive::EvalContext* context)
{
	Object* obj = m_object->Evaluate(context);
	DependencyObject* depObj = dynamic_cast<DependencyObject*>(obj);
	if (depObj == NULL)
	{
		VERIFY(0);
	}
	Variant propertyRef = m_exp->Evaluate(context);

	PropertyValue* pProperty;

	if (propertyRef.IsString())
		pProperty = depObj->GetProperty(depObj->GetClass()->GetLocalProperty(propertyRef.ToString()));
	else if (propertyRef.IsInt())
		pProperty = depObj->GetProperty(depObj->GetClass()->GetLocalProperty((int)propertyRef));
	else
		throw new Exception("property not found");

	return pProperty->GetComputedValue();
}

bool GetDPByExpExpression::Set(Expressive::EvalContext* context, Variant value)
{
	Object* obj = m_object->Evaluate(context);
	DependencyObject* depObj = dynamic_cast<DependencyObject*>(obj);
	if (depObj == NULL)
	{
		VERIFY(0);
	}
	Variant propertyRef = m_exp->Evaluate(context);

	PropertyValue* pProperty;

	if (propertyRef.IsString())
		pProperty = depObj->GetProperty(depObj->GetClass()->GetLocalProperty(propertyRef.ToString()));
	else if (propertyRef.IsInt())
		pProperty = depObj->GetProperty(depObj->GetClass()->GetLocalProperty(int(propertyRef)));
	else
		raise(Exception("property not found"));

	pProperty->UpdateValue(value);
	return true;
}

void GetDPByExpExpression::TraceCallback(Expressive::EvalContext* context, Expressive::ExpTrace& trace, Expressive::ITraceCallback* callback)
{
	m_object->TraceCallback(context, Expressive::ExpTrace(trace, this), callback);
	DebugTrace(".getPropertyByExp(");
	m_exp->TraceCallback(context, Expressive::ExpTrace(trace, this), callback);
	DebugTrace(")");
}

}	// Gui
}	// System
