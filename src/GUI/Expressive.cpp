#include "stdafx.h"
#include "GUI2.h"

namespace System
{

template<> GUIEXT int UnboxCast<int>(Object* obj)
{
	if (FloatObject* p = dynamic_cast<FloatObject*>(obj))
	{
		return int(p->GetValue());
	}
	else if (DoubleObject* p = dynamic_cast<DoubleObject*>(obj))
	{
		return int(p->GetValue());
	}
	else if (IntObject* p = dynamic_cast<IntObject*>(obj))
	{
		return p->GetValue();
	}
	else
	{
		ASSERT(0);
		return 0;
	}
}

template<> GUIEXT float UnboxCast<float>(Object* obj)
{
	if (FloatObject* p = dynamic_cast<FloatObject*>(obj))
	{
		return p->GetValue();
	}
	else if (DoubleObject* p = dynamic_cast<DoubleObject*>(obj))
	{
		return float(p->GetValue());
	}
	else if (IntObject* p = dynamic_cast<IntObject*>(obj))
	{
		return float(p->GetValue());
	}
	else
	{
		ASSERT(0);
		return 0;
	}
}

template<> GUIEXT double UnboxCast<double>(Object* obj)
{
	if (FloatObject* p = dynamic_cast<FloatObject*>(obj))
	{
		return p->GetValue();
	}
	else if (DoubleObject* p = dynamic_cast<DoubleObject*>(obj))
	{
		return p->GetValue();
	}
	else if (IntObject* p = dynamic_cast<IntObject*>(obj))
	{
		return double(p->GetValue());
	}
	else
	{
		ASSERT(0);
		return 0;
	}
}

namespace Expressive
{

_object::_object(const expression& exp) : expression(exp)
{
	if (exp.m_p == nullptr)
	{
		ASSERT(0);
	}

//	ASSERT((int)p != 0xcccccccc);
}

_object::~_object()
{
}

Expression* MinusUnaryExpression::GetInverseExpression()
{
	return m_exp;
}

/*
Object* MinusUnaryExpression::Evaluate(EvalContext* context)
{
	Object* exp = m_exp->Evaluate(context);

	if (exp->GetType() == typeid(DoubleObject).GetType())
	{
		return DoubleObject::GetObject(-static_cast<DoubleObject*>(exp)->GetValue());
	}
	else if (exp->GetType() == typeid(FloatObject).GetType())
	{
		return FloatObject::GetObject(-static_cast<FloatObject*>(exp)->GetValue());
	}
	else if (exp->GetType() == typeid(IntObject).GetType())
	{
		return IntObject::GetObject(-static_cast<IntObject*>(exp)->GetValue());
	}

	return NULL;
}
*/

int MinusUnaryExpression::EvaluateInt(EvalContext* context)
{
	ASSERT(m_pType == typeid(int));
	return - m_exp->EvaluateInt(context);
}

float MinusUnaryExpression::EvaluateFloat(EvalContext* context)
{
	ASSERT(m_pType == typeid(float));
	return - m_exp->EvaluateFloat(context);
}

double MinusUnaryExpression::EvaluateDouble(EvalContext* context)
{
	ASSERT(m_pType == typeid(double));
	return - m_exp->EvaluateDouble(context);
}

Expression* NotUnaryExpression::GetInverseExpression()
{
	return m_exp;
}

bool NotUnaryExpression::EvaluateBool(EvalContext* context)
{
	return !m_exp->EvaluateBool(context);
}

void BinaryExpression::TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
{
//	TRACE("(");
	m_left->TraceCallback(context, ExpTrace(trace, this), callback);
//	PrintOp(Std::get_Out());
	m_right->TraceCallback(context, ExpTrace(trace, this), callback);
//	TRACE(")");
}

Expression* AddBinaryExpression::GetInverseExpression()
{
	ASSERT(0);
	return NULL;
}

bool EQRelationalExpression::Set(EvalContext* context, bool value)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		bool value2 = (value == m_left->EvaluateBool(nullptr));
		m_right->Set(context, value2);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		bool value2 = (value == m_right->EvaluateBool(nullptr));
		m_left->Set(context, value2);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool NEQRelationalExpression::Set(EvalContext* context, bool value)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		bool value2 = value != m_left->EvaluateBool(nullptr);
		m_right->Set(context, value2);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		bool value2 = value != m_right->EvaluateBool(nullptr);
		m_left->Set(context, value2);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool LTRelationalExpression::Set(EvalContext* context, bool value)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		m_right->Set(context, value < m_left->EvaluateBool(nullptr));
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		m_left->Set(context, value < m_right->EvaluateBool(nullptr));
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool NotUnaryExpression::Set(EvalContext* context, bool value)
{
	m_exp->Set(context, !value);
	return true;
}

bool MinusUnaryExpression::Set(EvalContext* context, int value)
{
	m_exp->Set(context, -value);
	return true;
}

bool MinusUnaryExpression::Set(EvalContext* context, float value)
{
	m_exp->Set(context, -value);
	return true;
}

bool MinusUnaryExpression::Set(EvalContext* context, double value)
{
	m_exp->Set(context, -value);
	return true;
}

bool AddBinaryExpression::Set(EvalContext* context, int value)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		int value2 = value - m_left->EvaluateT<int>(nullptr);
		m_right->Set(context, value2);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		int value2 = value - m_right->EvaluateT<int>(nullptr);
		m_left->Set(context, value2);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool AddBinaryExpression::Set(EvalContext* context, float value)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		float value2 = value - m_left->EvaluateT<float>(nullptr);
		m_right->Set(context, value2);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		float value2 = value - m_right->EvaluateT<float>(nullptr);
		m_left->Set(context, value2);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool AddBinaryExpression::Set(EvalContext* context, double value)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		double value2 = value - m_left->EvaluateT<double>(nullptr);
		m_right->Set(context, value2);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		double value2 = value - m_right->EvaluateT<double>(nullptr);
		m_left->Set(context, value2);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool SubtractBinaryExpression::Set(EvalContext* context, int value)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		int newvalue = -value + m_left->EvaluateInt(nullptr);
		m_right->Set(context, newvalue);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		int newvalue = value + m_right->EvaluateInt(nullptr);
		m_left->Set(context, newvalue);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool SubtractBinaryExpression::Set(EvalContext* context, float objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		float value = -objvalue + m_left->EvaluateFloat(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		float value = objvalue + m_right->EvaluateFloat(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool SubtractBinaryExpression::Set(EvalContext* context, double objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		double value = -objvalue + m_left->EvaluateDouble(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		double value = objvalue + m_right->EvaluateDouble(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool MultiplyBinaryExpression::Set(EvalContext* context, int objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		int value = objvalue / m_left->EvaluateT<int>(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		int value = objvalue / m_right->EvaluateT<int>(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool MultiplyBinaryExpression::Set(EvalContext* context, float objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		float value = objvalue / m_left->EvaluateT<float>(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		float value = objvalue / m_right->EvaluateT<float>(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool MultiplyBinaryExpression::Set(EvalContext* context, double objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		double value = objvalue / m_left->EvaluateT<double>(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		double value = objvalue / m_right->EvaluateT<double>(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool DivideBinaryExpression::Set(EvalContext* context, int objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		int value = objvalue / m_left->EvaluateT<int>(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		int value = objvalue * m_right->EvaluateT<int>(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool DivideBinaryExpression::Set(EvalContext* context, float objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		float value = objvalue / m_left->EvaluateT<float>(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		float value = objvalue * m_right->EvaluateT<float>(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

bool DivideBinaryExpression::Set(EvalContext* context, double objvalue)
{
	if (m_left->GetKind() == Kind_CONST)
	{
		double value = objvalue / m_left->EvaluateT<double>(nullptr);
		m_right->Set(context, value);
	}
	else if (m_right->GetKind() == Kind_CONST)
	{
		double value = objvalue * m_right->EvaluateT<double>(nullptr);
		m_left->Set(context, value);
	}
	else
	{
		// TODO must use constraints
		ASSERT(0);
		return false;
	}

	return true;
}

void StaticObjectExpression::TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
{
	/*
	if (m_obj)
	{
		DebugTrace("obj" << paren(m_obj->GetType()->get_QName()));//  m_obj);
	}
	else
	{
		DebugTrace("obj(null)");
	}
	*/
}

void ThisExpression::TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
{
//	DebugTrace("this");
}

int AddBinaryExpression::EvaluateInt(EvalContext* context)
{
	ASSERT(m_pType == typeid(int));
	return m_left->EvaluateT<int>(context) + m_right->EvaluateT<int>(context);
}

float AddBinaryExpression::EvaluateFloat(EvalContext* context)
{
	ASSERT(m_pType == typeid(float));
	return m_left->EvaluateT<float>(context) + m_right->EvaluateT<float>(context);
}

double AddBinaryExpression::EvaluateDouble(EvalContext* context)
{
	ASSERT(m_pType == typeid(double));
	return m_left->EvaluateT<double>(context) + m_right->EvaluateT<double>(context);
}

int SubtractBinaryExpression::EvaluateInt(EvalContext* context)
{
	ASSERT(m_pType == typeid(int));

	int left = m_left->EvaluateInt(context);
	int right = m_right->EvaluateInt(context);
	return left - right;
}

float SubtractBinaryExpression::EvaluateFloat(EvalContext* context)
{
	ASSERT(m_pType == typeid(float));

	float left = m_left->EvaluateFloat(context);
	float right = m_right->EvaluateFloat(context);
	return left - right;
}

double SubtractBinaryExpression::EvaluateDouble(EvalContext* context)
{
	ASSERT(m_pType == typeid(double));

	double left = m_left->EvaluateDouble(context);
	double right = m_right->EvaluateDouble(context);
	return left - right;
}

Expression* SubtractBinaryExpression::GetInverseExpression()
{
	ASSERT(0);
	return NULL;
}

int MultiplyBinaryExpression::EvaluateInt(EvalContext* context)
{
	return m_left->EvaluateInt(context) * m_right->EvaluateInt(context);
}

float MultiplyBinaryExpression::EvaluateFloat(EvalContext* context)
{
	return m_left->EvaluateFloat(context) * m_right->EvaluateFloat(context);
}

double MultiplyBinaryExpression::EvaluateDouble(EvalContext* context)
{
	return m_left->EvaluateDouble(context) * m_right->EvaluateDouble(context);
}

int DivideBinaryExpression::EvaluateInt(EvalContext* context)
{
	int right = m_right->EvaluateInt(context);
	if (right == 0)
	{
		raise(SystemException("Divide by zero"));
	}
	return m_left->EvaluateInt(context) / right;
}

float DivideBinaryExpression::EvaluateFloat(EvalContext* context)
{
	float right = m_right->EvaluateFloat(context);
	if (right == 0)
	{
		raise(SystemException("Divide by zero"));
	}
	return m_left->EvaluateFloat(context) / right;
}

double DivideBinaryExpression::EvaluateDouble(EvalContext* context)
{
	double right = m_right->EvaluateDouble(context);
	if (right == 0)
	{
		raise(SystemException("Divide by zero"));
	}
	return m_left->EvaluateDouble(context) / right;
}

int ModulusBinaryExpression::EvaluateInt(EvalContext* context)
{
	int right = m_right->EvaluateInt(context);
	if (right == 0)
	{
		raise(SystemException("Divide by zero"));
	}

	return m_left->EvaluateInt(context) % right;
}

int BitwiseOrBinaryExpression::EvaluateInt(EvalContext* context)
{
	int left = m_left->EvaluateInt(context);
	int right = m_right->EvaluateInt(context);

	return left | right;
}

int BitwiseAndBinaryExpression::EvaluateInt(EvalContext* context)
{
	int left = m_left->EvaluateInt(context);
	int right = m_right->EvaluateInt(context);

	return left & right;
}

int BitwiseXorBinaryExpression::EvaluateInt(EvalContext* context)
{
	int left = m_left->EvaluateInt(context);
	int right = m_right->EvaluateInt(context);

	return left ^ right;
}

bool EQRelationalExpression::EvaluateBool(EvalContext* context)
{
	Variant left = m_left->Evaluate(context);
	Variant right = m_right->Evaluate(context);

	return left == right;
}

bool NEQRelationalExpression::EvaluateBool(EvalContext* context)
{
	Variant left = m_left->Evaluate(context);
	Variant right = m_right->Evaluate(context);

	return left != right;
}

bool LTRelationalExpression::EvaluateBool(EvalContext* context)
{
	Variant left = m_left->Evaluate(context);
	Variant right = m_right->Evaluate(context);

	return left < right;
}

bool LTEQRelationalExpression::EvaluateBool(EvalContext* context)
{
	Variant left = m_left->Evaluate(context);
	Variant right = m_right->Evaluate(context);

	return left <= right;
}

bool GTRelationalExpression::EvaluateBool(EvalContext* context)
{
	Variant left = m_left->Evaluate(context);
	Variant right = m_right->Evaluate(context);

	return left > right;
}

bool GTEQRelationalExpression::EvaluateBool(EvalContext* context)
{
	Variant left = m_left->Evaluate(context);
	Variant right = m_right->Evaluate(context);

	return left >= right;
}

bool LogicalOrExpression::EvaluateBool(EvalContext* context)
{
	bool left = m_left->EvaluateBool(context);
	bool right = m_right->EvaluateBool(context);

	return left || right;
}

bool LogicalAndExpression::EvaluateBool(EvalContext* context)
{
	bool left = m_left->EvaluateBool(context);
	bool right = m_right->EvaluateBool(context);

	return left && right;
}

Variant ConditionalExpression::Evaluate(EvalContext* context)
{
	bool test = m_testExp->EvaluateBool(context);

	if (test)
		return m_trueExp->Evaluate(context);
	else
		return m_falseExp->Evaluate(context);
}

IO::TextWriter& StaticObjectExpression::WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs)
{
	if (Gui::DependencyObject* depobj = dynamic_cast<Gui::DependencyObject*>(m_obj))
	{
		depobj->WriteMLString(stream, defs);
	}
	else
	{
		stream << "(object)";
	}

	return stream;
}

#if 0
Object* FunctionCall0Expression::Evaluate(EvalContext* context)
{
	/*
	IFunctionT1<float, DependencyObject*>* function = dynamic_cast<IFunctionT1<float, DependencyObject*>*>(m_function);
	ASSERT(function);
	return box_cast(function->call(context->m_this));
	*/

	ASSERT(0);
	return NULL;
}
#endif

/*
Object* IDRefExpression::Evaluate(EvalContext* context)
{
	return context->m_defs.find(m_id)->second;
}
*/

Variant GetMemberByOffsetExpression::Evaluate(EvalContext* context)
{
	ASSERT(0);
	return nullptr;
}

Variant ThisExpression::Evaluate(EvalContext* context)
{
	return context->m_this;
}

GetPropertyExpression::GetPropertyExpression(Expression* object) : m_object(object)
{
	if (object == nullptr)
	{
		ASSERT(0);
	}

	ASSERT((int)m_object != 0xcccccccc);
}

ThisExpression ThisExpression::s_thisExp;

//AThisExpression AThisExpression::s_thisExp;

_object _object::s_this(&ThisExpression::s_thisExp);

const _object& _object::get_this()
{
	s_this.m_p = &ThisExpression::s_thisExp;	// In case ctor not yet called
	return s_this;
}

Variant GetVariableExpression::Evaluate(EvalContext* context)
{
	auto it = context->m_variables.find(m_varName);
	if (it != context->m_variables.end())
	{
		return it->second;
	}
	else
		return nullptr;
}

ConstExpression<bool> ConstExpression<bool>::True(true);
ConstExpression<bool> ConstExpression<bool>::False(false);

}	// Expressive
}	// System
