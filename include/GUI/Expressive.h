namespace System
{

#ifndef __LERSTAD__

template<class T> T UnboxCast(Object* obj);

template<> inline Object* UnboxCast<Object*>(Object* obj)
{
	return obj;
}

template<> GUIEXT int UnboxCast<int>(Object* obj);
template<> GUIEXT float UnboxCast<float>(Object* obj);
template<> GUIEXT double UnboxCast<double>(Object* obj);

#endif

namespace Expressive
{

//#ifndef __LERSTAD__

inline void __TRACE(bool value)
{
	DebugTrace(value);
}

inline void __TRACE(int value)
{
	DebugTrace(value);
}

inline void __TRACE(unsigned int value)
{
	DebugTrace(value);
}

inline void __TRACE(int64 value)
{
	DebugTrace(value);
}

inline void __TRACE(float value)
{
	DebugTrace(value);
}

inline void __TRACE(double value)
{
	DebugTrace(value);
}

//#endif

#define DEFINE_THIS(x)	static inline const x& _this()	{ return *(x*)&Expressive::_object::get_this();	}
//#define DEFINE_CLASS()	virtual DependencyClass* GetClass()	{return &s_Class;} static DependencyClass s_Class;

class _ClassType;
class Expression;

class GUIEXT EvalContext : public Object
{
public:
	Object* m_this;	//TODO?, have in m_variables
	Object* m_userObject;
	map<String,Object*> m_variables;
};

class ExpTrace
{
public:

	CTOR ExpTrace() : m_parent(NULL), m_exp(NULL)
	{
	}

	CTOR ExpTrace(ExpTrace& parent, Expression* exp) : m_parent(&parent), m_exp(exp)
	{
	}

	ExpTrace* m_parent;
	Expression* m_exp;
};

interface ITraceCallback
{
};

union ExpressionValue
{
	bool boolValue;
	unsigned char ubyteValue;
	int intValue;
	__int64 longValue;
	float floatValue;
	double doubleValue;
};

class GUIEXT Expression : public Object
{
protected:
	CTOR Expression()
	{
	}

	CTOR Expression(Type* pType) : m_pType(pType)
	{
	}

public:

	virtual void OnChildChanged(Expression* child)
	{
	}

	virtual Expression* GetInverseExpression()
	{
		ASSERT(0);
		return NULL;
	}
	virtual bool Set(EvalContext* context, const Variant& value)
	{
		ASSERT(0);
		return false;
	}

	virtual bool Set(EvalContext* context, bool value)
	{
		return Set(context, Variant(value));
	}

	virtual bool Set(EvalContext* context, int value)
	{
		return Set(context, Variant(value));
	}

	virtual bool Set(EvalContext* context, float value)
	{
		return Set(context, Variant(value));
	}

	virtual bool Set(EvalContext* context, double value)
	{
		return Set(context, Variant(value));
	}

	virtual Variant Evaluate(EvalContext* context)
	{
		if (m_pType == typeid(bool))
		{
			return EvaluateBool(context);
		}
		else if (m_pType == typeid(int))
		{
			return EvaluateInt(context);
		}
		else if (m_pType == typeid(unsigned int))
		{
			return EvaluateUInt(context);
		}
		else if (m_pType == typeid(float))
		{
			return EvaluateFloat(context);
		}
		else if (m_pType == typeid(double))
		{
			return EvaluateDouble(context);
		}

		throw new Exception("oops");
	}

	virtual bool EvaluateBool(EvalContext* context)
	{
		return ToBool(Evaluate(context));
	}

	virtual int EvaluateInt(EvalContext* context)
	{
		return ToInt(Evaluate(context));
	}

	virtual int EvaluateUInt(EvalContext* context)
	{
		return ToUInt(Evaluate(context));
	}

	virtual float EvaluateFloat(EvalContext* context)
	{
		return ToFloat(Evaluate(context));
	}

	virtual double EvaluateDouble(EvalContext* context)
	{
		return ToDouble(Evaluate(context));
	}

	virtual ExpressionValue EvaluateValue(EvalContext* context)
	{
		ASSERT(0);
		ExpressionValue value;
		value.boolValue = false;
		return value;
	}

	template<class T> T EvaluateT(EvalContext* context);

#ifndef __LERSTAD__

	template<> bool EvaluateT<bool>(EvalContext* context)
	{
		return EvaluateBool(context);
	}

	template<> unsigned char EvaluateT<unsigned char>(EvalContext* context)
	{
		return (unsigned char)EvaluateInt(context);
	}

	template<> int EvaluateT<int>(EvalContext* context)
	{
		return EvaluateInt(context);
	}

	template<> float EvaluateT<float>(EvalContext* context)
	{
		return EvaluateFloat(context);
	}

	template<> double EvaluateT<double>(EvalContext* context)
	{
		return EvaluateDouble(context);
	}

	template<> long double EvaluateT<long double>(EvalContext* context)
	{
		return EvaluateDouble(context);
	}

#endif

	virtual Kind GetKind()
	{
		return Kind_Unk;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs)
	{
		return stream;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
	}

	virtual Type* GetTypeOf()
	{
		return m_pType;
	}

	Expression* m_parent;

	Type* m_pType;
};

template<class T>
class ConstExpression : public Expression
{
public:

	CTOR ConstExpression(T value) : m_value(value)//, m_object(box_cast(value))
	{
		m_pType = typeid(T);
	}

	virtual bool Set(EvalContext* context, const Variant& value) override
	{
		m_value = value;
		/*
		m_object = value;
#ifndef __LERSTAD__
		m_value = unbox_cast<T>(value);
#endif
		*/
		return true;
	}

	virtual Variant Evaluate(EvalContext* context) override
	{
		return Variant(m_value, m_pType);
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
#ifndef __LERSTAD__
	//	__TRACE(m_value);
#endif
	}

	virtual Kind GetKind() override
	{
		return Kind_CONST;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << m_value;
		return stream;
	}

	T m_value;

	static ConstExpression<bool> True;
	static ConstExpression<bool> False;
};

typedef ConstExpression<bool> BoolConstExpression;
typedef ConstExpression<int> IntConstExpression;
typedef ConstExpression<unsigned int> UnsignedIntConstExpression;
typedef ConstExpression<float> FloatConstExpression;
typedef ConstExpression<double> DoubleConstExpression;

class GUIEXT StringExpression : public Expression
{
public:

	CTOR StringExpression(StringIn str) : Expression(typeid(String)), m_str(str)
	{
	}

	/*
	virtual bool Set(EvalContext* context, Object* value) override
	{
		m_object = value;
#ifndef __LERSTAD__
		m_value = unbox_cast<T>(value);
#endif
		return true;
	}
	*/

	virtual Variant Evaluate(EvalContext* context) override
	{
		return m_str;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_String;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "\"" << m_str << "\"";
		return stream;
	}

	String m_str;
};

class GUIEXT ConditionalExpression : public Expression
{
public:
	CTOR ConditionalExpression(Expression* testExp, Expression* trueExp, Expression* falseExp) :
		m_testExp(testExp),
		m_trueExp(trueExp),
		m_falseExp(falseExp)
	{
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "if ";
		m_testExp->WriteMLString(stream, defs);
		stream << " then ";
		m_trueExp->WriteMLString(stream, defs);
		stream << " else ";
		m_falseExp->WriteMLString(stream, defs);

		return stream;
	}

  	virtual Variant Evaluate(EvalContext* context) override;

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
		m_testExp->TraceCallback(context, ExpTrace(trace, this), callback);
		m_trueExp->TraceCallback(context, ExpTrace(trace, this), callback);
		m_falseExp->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	virtual Kind GetKind() override
	{
		return Kind_Conditional;
	}

	Expression* m_testExp;
	Expression* m_trueExp;
	Expression* m_falseExp;
};

#if 0
class GUIEXT ExpressionExpression : public AExpression
{
public:
	CTOR ExpressionExpression(const lex_loc& loc, AExpression* exp) : AExpression(loc), m_exp(exp)
	{
	}

	/*
	virtual Kind GetKind() override
	{
		return Kind_Typeof;
	}
	*/

	virtual Stream& WriteMLString(Stream& stream, map<Object*,int>& defs) override
	{
		stream << "expof ";
		m_exp->WriteMLString(stream, defs);
		return stream;
	}

	Expression* m_exp;
};
#endif

class GUIEXT UnaryExpression : public Expression
{
public:
	CTOR UnaryExpression(Expression* exp) : m_exp(exp)
	{
	}

	CTOR UnaryExpression(Type* pType, Expression* exp) : Expression(pType), m_exp(exp)
	{
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
		m_exp->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		PrintOp(stream);
		m_exp->WriteMLString(stream, defs);
		return stream;
	}

	virtual void PrintOp(IO::TextWriter& stream) abstract;

protected:

	Expression* m_exp;
};

class GUIEXT BinaryExpression : public Expression
{
public:
	CTOR BinaryExpression(Expression* left, Expression* right) : m_left(left), m_right(right)
	{
	}

	CTOR BinaryExpression(Type* pType, Expression* left, Expression* right) : Expression(pType), m_left(left), m_right(right)
	{
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override;

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs)
	{
		m_left->WriteMLString(stream, defs);
		PrintOp(stream);
		m_right->WriteMLString(stream, defs);
		return stream;
	}

	virtual int GetOperator() abstract;

	virtual void PrintOp(IO::TextWriter& stream) abstract;

protected:

	Expression* m_left;
	Expression* m_right;
};

class GUIEXT MinusUnaryExpression : public UnaryExpression
{
public:
	CTOR MinusUnaryExpression(Expression* exp) : UnaryExpression(exp->m_pType, exp)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "-";
	}

	virtual Expression* GetInverseExpression() override;

	virtual int EvaluateInt(EvalContext* context) override;
	virtual float EvaluateFloat(EvalContext* context) override;
	virtual double EvaluateDouble(EvalContext* context) override;

	virtual bool Set(EvalContext* context, int value) override;
	virtual bool Set(EvalContext* context, float value) override;
	virtual bool Set(EvalContext* context, double value) override;
};

class GUIEXT NotUnaryExpression : public UnaryExpression
{
public:
	CTOR NotUnaryExpression(Expression* exp) : UnaryExpression(typeid(bool), exp)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "!";
	}

	virtual Expression* GetInverseExpression() override;

	virtual bool EvaluateBool(EvalContext* context) override;
	virtual bool Set(EvalContext* context, bool value) override;
};

class GUIEXT SubtractBinaryExpression : public BinaryExpression
{
public:
	CTOR SubtractBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	CTOR SubtractBinaryExpression(Type* pType, Expression* left, Expression* right) : BinaryExpression(pType, left, right)
	{
	}

	virtual Expression* GetInverseExpression() override;

	virtual int EvaluateInt(EvalContext* context) override;
	virtual float EvaluateFloat(EvalContext* context) override;
	virtual double EvaluateDouble(EvalContext* context) override;

	virtual bool Set(EvalContext* context, int value) override;
	virtual bool Set(EvalContext* context, float value) override;
	virtual bool Set(EvalContext* context, double value) override;

	virtual void PrintOp(IO::TextWriter& stream) override
	{
#ifndef __LERSTAD__
		stream << "-";
#endif
	}

	virtual int GetOperator() override
	{
		return '-';
	}
};

class GUIEXT AddBinaryExpression : public BinaryExpression
{
public:
	CTOR AddBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	CTOR AddBinaryExpression(Type* pType, Expression* left, Expression* right) : BinaryExpression(pType, left, right)
	{
	}

	virtual Expression* GetInverseExpression() override;

//	virtual Variant Evaluate(EvalContext* context) override;
	virtual int EvaluateInt(EvalContext* context) override;
	virtual float EvaluateFloat(EvalContext* context) override;
	virtual double EvaluateDouble(EvalContext* context) override;

	virtual bool Set(EvalContext* context, int value) override;
	virtual bool Set(EvalContext* context, float value) override;
	virtual bool Set(EvalContext* context, double value) override;

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "+";
	}

	virtual int GetOperator() override
	{
		return '+';
	}
};

class GUIEXT MultiplyBinaryExpression : public BinaryExpression
{
public:
	CTOR MultiplyBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	virtual int EvaluateInt(EvalContext* context) override;
	virtual float EvaluateFloat(EvalContext* context) override;
	virtual double EvaluateDouble(EvalContext* context) override;

	virtual bool Set(EvalContext* context, int value) override;
	virtual bool Set(EvalContext* context, float value) override;
	virtual bool Set(EvalContext* context, double value) override;

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "*";
	}

	virtual int GetOperator() override
	{
		return '*';
	}
};

class GUIEXT DivideBinaryExpression : public BinaryExpression
{
public:
	CTOR DivideBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	virtual int EvaluateInt(EvalContext* context) override;
	virtual float EvaluateFloat(EvalContext* context) override;
	virtual double EvaluateDouble(EvalContext* context) override;

	virtual bool Set(EvalContext* context, int value) override;
	virtual bool Set(EvalContext* context, float value) override;
	virtual bool Set(EvalContext* context, double value) override;

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "/";
	}

	virtual int GetOperator() override
	{
		return '/';
	}
};

class GUIEXT ModulusBinaryExpression : public BinaryExpression
{
public:
	CTOR ModulusBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	virtual int EvaluateInt(EvalContext* context) override;

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "%";
	}

	virtual int GetOperator() override
	{
		return '%';
	}
};

class GUIEXT BitwiseOrBinaryExpression : public BinaryExpression
{
public:
	CTOR BitwiseOrBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	virtual int EvaluateInt(EvalContext* context) override;

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "bitor";
	}
};

class GUIEXT BitwiseAndBinaryExpression : public BinaryExpression
{
public:
	CTOR BitwiseAndBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	virtual int EvaluateInt(EvalContext* context) override;
	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "bitand";
	}
};

class GUIEXT BitwiseXorBinaryExpression : public BinaryExpression
{
public:
	CTOR BitwiseXorBinaryExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}

	virtual int EvaluateInt(EvalContext* context) override;
	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "bitxor";
	}
};

class GUIEXT RelationalExpression : public BinaryExpression
{
public:
	CTOR RelationalExpression(Expression* left, Expression* right) : BinaryExpression(typeid(bool), left, right)
	{
	}

	virtual Kind GetKind() override
	{
		return Kind_Relational;
	}
};

class GUIEXT LogicalExpression : public BinaryExpression
{
public:
	CTOR LogicalExpression(Expression* left, Expression* right) : BinaryExpression(left, right)
	{
	}
};

class GUIEXT EQRelationalExpression : public RelationalExpression
{
public:
	CTOR EQRelationalExpression(Expression* left, Expression* right) : RelationalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "=";
	}

	virtual int GetOperator() override
	{
		return '=';
	}

	virtual bool EvaluateBool(EvalContext* context) override;
	virtual bool Set(EvalContext* context, bool value) override;
};

class GUIEXT NEQRelationalExpression : public RelationalExpression
{
public:
	CTOR NEQRelationalExpression(Expression* left, Expression* right) : RelationalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "!=";
	}

	virtual int GetOperator() override
	{
		return '!=';
	}

	virtual bool EvaluateBool(EvalContext* context) override;
	virtual bool Set(EvalContext* context, bool value) override;
};

class GUIEXT LTRelationalExpression : public RelationalExpression
{
public:
	CTOR LTRelationalExpression(Expression* left, Expression* right) : RelationalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "<";
	}

	virtual int GetOperator() override
	{
		return '<';
	}

	virtual bool EvaluateBool(EvalContext* context) override;
	virtual bool Set(EvalContext* context, bool value) override;
};

class GUIEXT LTEQRelationalExpression : public RelationalExpression
{
public:
	CTOR LTEQRelationalExpression(Expression* left, Expression* right) : RelationalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "<=";
	}

	virtual int GetOperator() override
	{
		return '<=';
	}

	virtual bool EvaluateBool(EvalContext* context) override;
};

class GUIEXT GTRelationalExpression : public RelationalExpression
{
public:
	CTOR GTRelationalExpression(Expression* left, Expression* right) : RelationalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << ">";
	}

	virtual int GetOperator() override
	{
		return '>';
	}

	virtual bool EvaluateBool(EvalContext* context) override;
};

class GUIEXT GTEQRelationalExpression : public RelationalExpression
{
public:
	CTOR GTEQRelationalExpression(Expression* left, Expression* right) : RelationalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << ">=";
	}

	virtual int GetOperator() override
	{
		return '>=';
	}

	virtual bool EvaluateBool(EvalContext* context) override;
};

class GUIEXT LogicalOrExpression : public LogicalExpression
{
public:
	CTOR LogicalOrExpression(Expression* left, Expression* right) : LogicalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "or";
	}

	virtual int GetOperator() override
	{
		return '||';
	}

	virtual bool EvaluateBool(EvalContext* context);
//	virtual bool Set(EvalContext* context, Object* objvalue) override;
};

class GUIEXT LogicalAndExpression : public LogicalExpression
{
public:
	CTOR LogicalAndExpression(Expression* left, Expression* right) : LogicalExpression(left, right)
	{
	}

	virtual void PrintOp(IO::TextWriter& stream) override
	{
		stream << "and";
	}

	virtual int GetOperator() override
	{
		return '&&';
	}

	virtual bool EvaluateBool(EvalContext* context) override;
//	virtual bool Set(EvalContext* context, Object* objvalue) override;
};

template<class T>
class GUIEXT PrimitiveCastExpression : public Expression
{
public:

	CTOR PrimitiveCastExpression(Expression* exp) : m_exp(exp)
	{
	}

	virtual Variant Evaluate(EvalContext* context)
	{
		Variant value = m_exp->Evaluate(context);

		return (T)value;

#ifndef __LERSTAD__
		// TODO, one function
	//	return box_cast(UnboxCast<T>(value));
#endif
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
		m_exp->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	Expression* m_exp;
};

class GUIEXT ObjectExpression : public Expression
{
public:
};

class GUIEXT StaticObjectExpression : public ObjectExpression
{
public:

	CTOR StaticObjectExpression() : m_obj(NULL)
	{
	}

	CTOR StaticObjectExpression(Object* obj) : m_obj(obj)
	{
		m_pType = obj->GetType();
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override;

	virtual Variant Evaluate(EvalContext* context)
	{
		return m_obj;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback);

	Object* m_obj;
};

// TODO: ?? Really the same as StaticObjectExpression
class GUIEXT TypeExpression : public Expression
{
public:
	CTOR TypeExpression(Type* pTypeId) : m_pTypeId(pTypeId)
	{
		m_pType = pTypeId->GetType();
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
	}

	virtual Variant Evaluate(EvalContext* context) override
	{
		return m_pTypeId;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << m_pTypeId->ToString();
		return stream;
	}

	Type* m_pTypeId;
};

class GUIEXT ThisExpression : public ObjectExpression
{
protected:
	CTOR ThisExpression()
	{
	}

public:

	virtual Kind GetKind() override
	{
		return Kind_This;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << "this";
		return stream;
	}

	virtual Variant Evaluate(EvalContext* context) override;
	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override;

	static ThisExpression* OfType(ClassType* pType)
	{
		VerifyArgumentNotNull(pType);

		ThisExpression* exp = new ThisExpression;
		exp->m_pType = pType;
		return exp;
	}

	static ThisExpression s_thisExp;	// TODO remove
};

class GUIEXT GetPropertyExpression : public Expression
{
public:

	CTOR GetPropertyExpression(Expression* object);

	Expression* GetObject()
	{
		return m_object;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
		m_object->TraceCallback(context, ExpTrace(trace, this), callback);
	}

protected:

	Expression* m_object;
};

class GUIEXT GetMemberExpression : public Expression
{
public:

	CTOR GetMemberExpression(Expression* object) : m_object(object)
	{
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
		m_object->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	Expression* m_object;
};

class GUIEXT GetMemberByOffsetExpression : public GetMemberExpression
{
public:
	CTOR GetMemberByOffsetExpression(Expression* object, int offset) : GetMemberExpression(object), m_offset(offset)
	{
	}

	virtual Variant Evaluate(EvalContext* context) override;

	int GetOffset() const
	{
		return m_offset;
	}

protected:

	int m_offset;
};

class GUIEXT GetVariableExpression : public Expression
{
public:

	CTOR GetVariableExpression(String varName) : m_varName(varName)
	{
	}

	virtual Variant Evaluate(EvalContext* context) override;

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
		//m_object->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	String m_varName;
};

#if 0
class GUIEXT IDRefExpression : public ObjectExpression
{
public:

	static IDRefExpression* GetIDREF(int id)
	{
		return new IDRefExpression(id);
	}

	/*
	virtual Object* Instantiate(InstantiateContext& context)
	{
		return new StaticObjectExpression(context.defs.find(m_id)->second);
	}
	*/

	virtual Object* Evaluate(EvalContext* context);

	int m_id;

protected:
	CTOR IDRefExpression(int id) : m_id(id)
	{
	}
};
#endif

interface IFunction
{
	virtual const Type_Info& getReturnType() = 0;
	virtual unsigned int getNumArgs() = 0;
};

template<class result_type> interface IFunctionT : public IFunction
{
	typedef result_type result_t;

	virtual const Type_Info& getReturnType() override
	{
		return typeid(result_t);
	}
};

template<class result_type> interface IFunctionT0 : public IFunctionT<result_type>
{
	virtual result_type call() = 0;
//	virtual const Type_Info& arg_type(unsigned int index);

	virtual unsigned int getNumArgs() override
	{
		return 0;
	}
};

template<class result_type, class arg0_type> interface IFunctionT1 : public IFunctionT<result_type>
{
	virtual result_type call(arg0_type) = 0;

	virtual unsigned int getNumArgs() override
	{
		return 1;
	}
};

template<class result_type, class arg0_type, class arg1_type> interface IFunctionT2 : public IFunctionT<result_type>
{
	virtual result_type call(arg0_type, arg1_type) = 0;

	virtual unsigned int getNumArgs() override
	{
		return 2;
	}
};

class GUIEXT FunctionCallExpression : public Expression
{
public:

	CTOR FunctionCallExpression(Declarator* decl) : m_decl(decl)
	{
		ASSERT(decl);
	}

	virtual unsigned GetNumArgs() const = 0;

	virtual Expression* GetArg(uint i)
	{
		return nullptr;
	}

	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs) override
	{
		stream << m_decl->m_name;
		stream << "(";

		uint nargs = GetNumArgs();
		for (uint i = 0; i < nargs; ++i)
		{
			if (i > 0) stream << ", ";
			Expression* arg = GetArg(i);
			arg->WriteMLString(stream, defs);
		}

		stream << ")";
		return stream;
	}

	Declarator* m_decl;
};

class GUIEXT StaticFunctionCallExpression : public Expression
{
public:

	CTOR StaticFunctionCallExpression()
	{
	}

	virtual unsigned int GetNumArgs() const = 0;
};

template<class return_type>
class GUIEXT FunctionCall0Expression : public FunctionCallExpression
{
public:

	CTOR FunctionCall0Expression(Declarator* decl) : FunctionCallExpression(decl)
	{
		m_pType = typeid(return_type);
	}

	virtual Variant Evaluate(EvalContext* context) override
	{
#ifndef __LERSTAD__
		return_type retval = m_decl->invoke_functionA<return_type>(nullptr, 0);
		return retval;
#endif
	}

	virtual unsigned int GetNumArgs() const override
	{
		return 0;
	}
};

template<class return_type, class arg0_type>
class GUIEXT FunctionCall1Expression : public FunctionCallExpression
{
public:

	CTOR FunctionCall1Expression(Declarator* decl, Expression* arg0) :
		FunctionCallExpression(decl),
		m_arg0(arg0)
	{
		m_pType = typeid(return_type);
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	virtual Variant Evaluate(EvalContext* context) override
	{
#ifndef __LERSTAD__
		arg0_type arg0 = m_arg0->EvaluateT<arg0_type>(context);

		return m_decl->invoke_functionA<return_type>(&arg0, sizeof(arg0_type));
#endif
	}

	virtual bool Set(EvalContext* context, const Variant& value) override
	{
#ifndef __LERSTAD__

		FunctionType* pFun = m_decl->m_pType->AsFunction();
		if (m_decl->m_name == "toFloat" &&
			pFun->m_parameters[0].m_pType->get_Kind() == type_int)
		{
			m_arg0->Set(context, value.ToInt());
		}
		else if (m_decl->m_name == "toFloat" &&
			pFun->m_parameters[0].m_pType->get_Kind() == type_double)
		{
			m_arg0->Set(context, value.ToDouble());
		}

		else if (m_decl->m_name == "toDouble" &&
			pFun->m_parameters[0].m_pType->get_Kind() == type_int)
		{
			m_arg0->Set(context, value.ToInt());
		}
		else if (m_decl->m_name == "toDouble" &&
			pFun->m_parameters[0].m_pType->get_Kind() == type_float)
		{
			m_arg0->Set(context, value.ToFloat());
		}

		else if (m_decl->m_name == "cos" &&
			pFun->m_parameters[0].m_pType->get_Kind() == type_float)
		{
			m_arg0->Set(context, acosf(value.ToFloat()));
		}
		else if (m_decl->m_name == "acos" &&
			pFun->m_parameters[0].m_pType->get_Kind() == type_float)
		{
			m_arg0->Set(context, cosf(value.ToFloat()));
		}
		else
		{
			ASSERT(0);
			return false;
		}
#endif

		return true;
	}

	virtual unsigned int GetNumArgs() const override
	{
		return 1;
	}

	virtual Expression* GetArg(uint i) override
	{
		return m_arg0;
	}

	Expression* m_arg0;
};

#ifndef __LERSTAD__

template<class return_type, return_type (*funptr)()>
class GUIEXT StaticFunctionCall0Expression : public StaticFunctionCallExpression
{
public:

	CTOR StaticFunctionCall0Expression()
	{
		m_pType = typeid(return_type);
	}

	virtual Variant Evaluate(EvalContext* context) override
	{
		return funptr();
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
	}

	virtual unsigned int GetNumArgs() const
	{
		return 0;
	}
};

template<class return_type, class arg0_type, return_type (*funptr)(arg0_type)>
class GUIEXT StaticFunctionCall1Expression : public StaticFunctionCallExpression
{
public:

	CTOR StaticFunctionCall1Expression(Expression* arg0) : m_arg0(arg0)
	{
		m_pType = typeid(return_type);
	}

	virtual return_type Evaluate(EvalContext* context) override
	{
		arg0_type arg0 = m_arg0->EvaluateT<arg0_type>(context);
		return funptr(arg0);
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	virtual unsigned int GetNumArgs() const
	{
		return 1;
	}

protected:

	Expression* m_arg0;
};

template<class return_type, class arg0_type, class arg1_type, return_type (*funptr)(arg0_type, arg1_type)>
class GUIEXT StaticFunctionCall2Expression : public StaticFunctionCallExpression
{
public:

	CTOR StaticFunctionCall2Expression(Expression* arg0, Expression* arg1) : m_arg0(arg0), m_arg1(arg1)
	{
		m_pType = typeid(return_type);
	}

	virtual return_type Evaluate(EvalContext* context) override
	{
		arg0_type arg0 = m_arg0->EvaluateT<arg0_type>(context);
		arg1_type arg1 = m_arg1->EvaluateT<arg1_type>(context);

		return funptr(arg0, arg1);
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
		m_arg1->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	virtual unsigned int GetNumArgs() const
	{
		return 2;
	}

protected:

	Expression* m_arg0;
	Expression* m_arg1;
};

#endif

/*
template<class arg0_type>
class FunctionCall1Expression : public FunctionCallExpression
{
public:

	CTOR FunctionCall1Expression(IFunction* fun, Expression* arg0) :
		FunctionCallExpression(fun),
		m_arg0(arg0)
	{
	}

	virtual Object* Evaluate(EvalContext* context)
	{
		ASSERT(0);
		return NULL;
	}

	virtual unsigned GetNumArgs() const
	{
		return 1;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	Expression* m_arg0;
};

template<class arg0_type, class arg1_type>
class FunctionCall2Expression : public FunctionCallExpression
{
public:

	CTOR FunctionCall2Expression(IFunction* fun, Expression* arg0, Expression* arg1) :
		FunctionCallExpression(fun),
		m_arg0(arg0),
		m_arg1(arg1)
	{
	}

	virtual Object* Evaluate(EvalContext* context)
	{
		ASSERT(0);
		return nullptr;
	}

	virtual unsigned GetNumArgs() const
	{
		return 2;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
		m_arg1->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	Expression* m_arg0;
	Expression* m_arg1;
};

template<class arg0_type, class arg1_type, class arg2_type>
class FunctionCall3Expression : public FunctionCallExpression
{
public:

	CTOR FunctionCall3Expression(IFunction* fun, Expression* arg0, Expression* arg1, Expression* arg2) :
		FunctionCallExpression(fun),
		m_arg0(arg0),
		m_arg1(arg2),
		m_arg1(arg1)
	{
	}

	virtual Object* Evaluate(EvalContext* context)
	{
		ASSERT(0);
		return NULL;
	}


	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
		m_arg1->TraceCallback(context, ExpTrace(trace, this), callback);
		m_arg2->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	Expression* m_arg0;
	Expression* m_arg1;
	Expression* m_arg2;
};
*/

class GUIEXT MethodCallExpression : public Expression
{
public:

	CTOR MethodCallExpression(Expression* objectExp, Declarator* method) : m_objectExp(objectExp), m_method(method)
	{
	}

	virtual unsigned int GetNumArgs() const = 0;

	Expression* m_objectExp;
	Declarator* m_method;
};

template<class return_type>
class GUIEXT MethodCall0Expression : public MethodCallExpression
{
public:

	CTOR MethodCall0Expression(Expression* objectExp, Declarator* method) : MethodCallExpression(objectExp, method)
	{
	}

	virtual Variant Evaluate(EvalContext* context) override
	{
		Object* obj = m_objectExp->Evaluate(context);

#ifndef __LERSTAD__
		return GetDispatch(obj->GetType())->Invoke<return_type>(obj, m_method, nullptr, 0);
#endif
	}

	virtual bool Set(EvalContext* context, const Variant& objvalue) override
	{
#ifndef __LERSTAD__
		return_type value = (return_type)objvalue;

		if (m_method->m_name == "operator conversion")
		{
			Dispatch* pDispatch = GetDispatch(m_method->GetClass());
			auto it = pDispatch->m_methodnames.find("operator=");
			if (it != pDispatch->m_methodnames.end())
			{
				Declarator* method;
				do
				{
					method = it->second;
					if (method->m_pType->AsFunction()->m_parameters[0].m_pType->GetStripped() == m_method->m_pType->AsFunction()->m_pReturnType->GetStripped())
					{
						break;
					}

					++it;
				}
				while (it->first == "operator=");

				if (it->first == "operator=")
				{
					Object* object = m_objectExp->Evaluate(context);
					ASSERT(object);

					pDispatch->void_Invoke(object, method, &value, sizeof(value));
				}
				else
				{
					ASSERT(0);
					return false;
				}
			}
		}
		else
		{
			ASSERT(0);
			return false;
		}

#endif
		return true;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback) override
	{
		m_objectExp->TraceCallback(context, ExpTrace(trace, this), callback);
	}

	virtual unsigned int GetNumArgs() const override
	{
		return 0;
	}
};

typedef MethodCall0Expression<int> mcall0def0;
typedef MethodCall0Expression<float> mcall0def1;

template<class return_type, class arg0_type>
class MethodCall1Expression : public MethodCallExpression
{
public:

	CTOR MethodCall1Expression(Expression* objectExp, Declarator* method, Expression* arg0) :
		MethodCallExpression(objectExp, method),
		m_arg0(arg0)
	{
		m_pType = typeid(return_type);
	}

	virtual Variant Evaluate(EvalContext* context)
	{
		ASSERT(0);
		return nullptr;
	}

	virtual unsigned GetNumArgs() const
	{
		return 1;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
#ifndef __LERSTAD__
		m_objectExp->TraceCallback(context, ExpTrace(trace, this), callback);
		DebugTrace("." << m_method->get_MethodName() << "(");
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
		DebugTrace(")");
#endif
	}

	Expression* m_arg0;
};

/*
template<class return_type> return_type CallMethod()
{
}
*/

template<class return_type, class arg0_type, class arg1_type>
class MethodCall2Expression : public MethodCallExpression
{
public:

	CTOR MethodCall2Expression(Expression* objectExp, Declarator* method, Expression* arg0, Expression* arg1) :
		MethodCallExpression(objectExp, method),
		m_arg0(arg0),
		m_arg1(arg1)
	{
		m_pType = typeid(return_type);
	}

	virtual bool EvaluateBool(EvalContext* context) override
	{
#ifndef __LERSTAD__
		return EvaluateT<bool>(context);
#endif
	}

	virtual int EvaluateInt(EvalContext* context) override
	{
#ifndef __LERSTAD__
		return EvaluateT<int>(context);
#endif
	}

	virtual float EvaluateFloat(EvalContext* context) override
	{
#ifndef __LERSTAD__
		return EvaluateT<float>(context);
#endif
	}

	template<class K> K EvaluateT(EvalContext* context)
	{
		Object* object = m_objectExp->Evaluate(context);
		ASSERT(object);

#ifndef __LERSTAD__
		arg0_type arg0 = m_arg0->EvaluateT<arg0_type>(context);
		arg1_type arg1 = m_arg1->EvaluateT<arg1_type>(context);
#endif

		// TODO, not 100% correct, align etc

		uint8 args[64];
		uint8* p = args;

#ifndef __LERSTAD__
		*(arg0_type*)p = arg0;
		p += sizeof(arg0_type);

		*(arg1_type*)p = arg1;
		p += sizeof(arg1_type);

		K value = GetDispatch(object->GetType()->AsClass())->Invoke<K>(object, m_method, args, p - args)/* & 1*/;
#endif
		return value;
	}

	virtual unsigned GetNumArgs() const
	{
		return 2;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
#ifndef __LERSTAD__
		m_objectExp->TraceCallback(context, ExpTrace(trace, this), callback);
	//	TRACE(".%s(", CString(m_method->get_MethodName());
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
	//	TRACE(",");
		m_arg1->TraceCallback(context, ExpTrace(trace, this), callback);
	//	TRACE(")");
#endif
	}

	Expression* m_arg0;
	Expression* m_arg1;
};

template<class arg0_type, class arg1_type, class arg2_type>
class MethodCall3Expression : public MethodCallExpression
{
public:

	CTOR MethodCall3Expression(Expression* objectExp, Declarator* method, Expression* arg0, Expression* arg1, Expression* arg2) :
		MethodCallExpression(objectExp, method),
		m_arg0(arg0),
		m_arg1(arg1),
		m_arg2(arg2)
	{
	}

	virtual Variant Evaluate(EvalContext* context)
	{
		ASSERT(0);
		return nullptr;
	}

	virtual unsigned GetNumArgs() const
	{
		return 3;
	}

	virtual void TraceCallback(EvalContext* context, ExpTrace& trace, ITraceCallback* callback)
	{
#ifndef __LERSTAD__
		m_objectExp->TraceCallback(context, ExpTrace(trace, this), callback);
		DebugTrace(".(");
		m_arg0->TraceCallback(context, ExpTrace(trace, this), callback);
		DebugTrace(",");
		m_arg1->TraceCallback(context, ExpTrace(trace, this), callback);
		DebugTrace(",");
		m_arg2->TraceCallback(context, ExpTrace(trace, this), callback);
		DebugTrace(")");
#endif
	}

	Expression* m_arg0;
	Expression* m_arg1;
	Expression* m_arg2;
};

///////////////////////////////////////

template<class type_type>
class type
{
public:
	typedef type_type typ;
};

class GUIEXT expression
{
public:

	virtual ~expression()
	{
	}

	CTOR expression(Expression* p) : m_p(p)
	{
	}

	/*
	CTOR expression(bool value) : m_p(new ConstExpression<bool>(value))
	{
	}

	CTOR expression(int value) : m_p(new ConstExpression<int>(value))
	{
	}

	CTOR expression(float value) : m_p(new ConstExpression<float>(value))
	{
	}

	CTOR expression(double value) : m_p(new ConstExpression<double>(value))
	{
	}
*/
	CTOR expression(Object* value) : m_p(new StaticObjectExpression(value))
	{
	}
/*
	expression operator - () const	// unary minus
	{
		return new MinusUnaryExpression(m_p);
	}

	expression operator ! () const
	{
		return new NotUnaryExpression(m_p);
	}

	expression operator + (const expression& right) const
	{
		return new PlusBinaryExpression(m_p, right.m_p);
	}

	expression operator - (const expression& right) const
	{
		return new MinusBinaryExpression(m_p, right.m_p);
	}

	expression operator * (const expression& right) const
	{
		return new MultiplyBinaryExpression(m_p, right.m_p);
	}

	expression operator / (const expression& right) const
	{
		return new DivideBinaryExpression(m_p, right.m_p);
	}

#ifndef __LERSTAD__
	expression operator % (const expression& right) const
	{
		return new ModulusBinaryExpression(m_p, right.m_p);
	}

#endif

// Bitwise
	expression operator | (const expression& right) const
	{
		return new BitwiseOrBinaryExpression(m_p, right.m_p);
	}

	expression operator & (const expression& right) const
	{
		return new BitwiseAndBinaryExpression(m_p, right.m_p);
	}

	expression operator ^ (const expression& right) const
	{
		return new BitwiseXorBinaryExpression(m_p, right.m_p);
	}

// Compare

	expression operator == (const expression& right) const
	{
		return new EQBinaryExpression(m_p, right.m_p);
	}

	expression operator != (const expression& right) const
	{
		return new NEQBinaryExpression(m_p, right.m_p);
	}

	expression operator < (const expression& right) const
	{
		return new LTBinaryExpression(m_p, right.m_p);
	}

	expression operator > (const expression& right) const
	{
		return new GTBinaryExpression(m_p, right.m_p);
	}

	expression operator <= (const expression& right) const
	{
		return new LTEQBinaryExpression(m_p, right.m_p);
	}

	expression operator >= (const expression& right) const
	{
		return new GTEQBinaryExpression(m_p, right.m_p);
	}

// Logical
#ifndef __LERSTAD__
	expression operator || (const expression& right) const
	{
		return new LogicalOrBinaryExpression(m_p, right.m_p);
	}

	expression operator && (const expression& right) const
	{
		return new LogicalAndBinaryExpression(m_p, right.m_p);
	}
#endif
	*/

	operator Expression* () const
	{
		return m_p;
	}

	Expression* m_p;
};

template<class exp_type> class typed_expression;

template<class T, class T2> typed_expression<T> cast(const typed_expression<T2>& value);

#ifndef __LERSTAD__

template<> typed_expression<float> cast<float>(const typed_expression<float>& value);
template<> typed_expression<float> cast<float>(const typed_expression<double>& value);

#endif

template<class exp_type>
class typed_expression : public expression
{
public:

	typedef type<exp_type> type_t;

	/*
	CTOR typed_expression(const expression& exp) : expression(exp.m_p)
	{
	}
	*/

	CTOR typed_expression(Expression* p) : expression(p)
	{
	}

	CTOR typed_expression(bool value) : expression(new ConstExpression<exp_type>(value))
	{
	}

	CTOR typed_expression(int value) : expression(new ConstExpression<exp_type>(value))
	{
	}

	CTOR typed_expression(float value) : expression(new ConstExpression<exp_type>(value))
	{
	}

	CTOR typed_expression(double value) : expression(new ConstExpression<exp_type>(value))
	{
	}

	// TODO?? Cast ??

#ifndef __LERSTAD__
	CTOR typed_expression(const typed_expression<int>& value) : expression(cast<exp_type>(value))
	{
	}

	CTOR typed_expression(const typed_expression<float>& value) : expression(cast<exp_type>(value))
	{
	}

	CTOR typed_expression(const typed_expression<double>& value) : expression(cast<exp_type>(value))
	{
	}

	/*
	CTOR typed_expression(const typed_expression<StringW>* value) : expression(cast<exp_type>(value))
	{
	}
	*/
#endif

	/*
#ifndef __LERSTAD__
	CTOR typed_expression(typename type_t::typ value) : expression(new ConstExpression<typename type_t::typ>(value))
	{
	}
#endif
	*/

	CTOR typed_expression(Object* value) : expression(new StaticObjectExpression(value))
	{
	}

	/*
	CTOR typed_expression(IBinding* value) : expression(new BindingExpression(value))
	{
	}
	*/

	typed_expression operator - () const	// unary minus
	{
		return new MinusUnaryExpression(typeid(exp_type), m_p);
	}

	typed_expression operator ! () const
	{
		return new NotUnaryExpression(m_p);
	}

	typed_expression operator + (const typed_expression& right) const
	{
		return new AddBinaryExpression(typeid(exp_type), m_p, right.m_p);
	}

	typed_expression operator - (const typed_expression& right) const
	{
		return new SubtractBinaryExpression(typeid(exp_type), m_p, right.m_p);
	}

	/*
	template<class right_type>
	typed_expression<exp_type> operator * (const typed_expression<right_type>& right) const
	{
		return new MultiplyBinaryExpression(m_p, right.m_p);
	}
	*/

	typed_expression operator / (const typed_expression& right) const
	{
		return new DivideBinaryExpression(m_p, right.m_p);
	}

#ifndef __LERSTAD__
	typed_expression operator % (const typed_expression& right) const
	{
		return new ModulusBinaryExpression(m_p, right.m_p);
	}

#endif

// Bitwise
	typed_expression operator | (const typed_expression& right) const
	{
		return new BitwiseOrBinaryExpression(m_p, right.m_p);
	}

	typed_expression operator & (const typed_expression& right) const
	{
		return new BitwiseAndBinaryExpression(m_p, right.m_p);
	}

	typed_expression operator ^ (const typed_expression& right) const
	{
		return new BitwiseXorBinaryExpression(m_p, right.m_p);
	}

// Compare

	typed_expression<bool> operator == (const typed_expression& right) const
	{
		return new EQRelationalExpression(m_p, right.m_p);
	}

	typed_expression<bool> operator != (const typed_expression& right) const
	{
		return new NEQRelationalExpression(m_p, right.m_p);
	}

	typed_expression<bool> operator < (const typed_expression& right) const
	{
		return new LTRelationalExpression(m_p, right.m_p);
	}

	typed_expression<bool> operator > (const typed_expression& right) const
	{
		return new GTRelationalExpression(m_p, right.m_p);
	}

	typed_expression<bool> operator <= (const typed_expression& right) const
	{
		return new LTEQRelationalExpression(m_p, right.m_p);
	}

	typed_expression<bool> operator >= (const typed_expression& right) const
	{
		return new GTEQRelationalExpression(m_p, right.m_p);
	}

// Logical
#ifndef __LERSTAD__
	typed_expression<bool> operator || (const typed_expression& right) const
	{
		return new LogicalOrExpression(m_p, right.m_p);
	}

	typed_expression<bool> operator && (const typed_expression& right) const
	{
		return new LogicalAndExpression(m_p, right.m_p);
	}

	friend typed_expression operator * (const typed_expression& left, const typed_expression& right)
	{
		return new MultiplyBinaryExpression(left.m_p, right.m_p);
	}

	/*
	friend typed_expression<exp_type> operator * (const typed_expression<exp_type>& left, const typed_expression<double>& right)
	{
		return new MultiplyBinaryExpression(left.m_p, right.m_p);
	}
	*/
#endif
};

#ifndef __LERSTAD__

template<> inline typed_expression<float> cast<float>(const typed_expression<float>& value)
{
	return value.m_p;
}

template<> inline typed_expression<double> cast<double>(const typed_expression<double>& value)
{
	return value.m_p;
}

template<> inline typed_expression<float> cast<float>(const typed_expression<double>& value)
{
	// TODO, warning, loss of precision

	return new PrimitiveCastExpression<float>(value.m_p);
}

template<> inline typed_expression<double> cast<double>(const typed_expression<float>& value)
{
	return new PrimitiveCastExpression<double>(value.m_p);
}

#endif

/*
template<class left_type>
typed_expression<left_type> operator * (const typed_expression<left_type>& left, const typed_expression<left_type>& right)
{
	return new MultiplyBinaryExpression(left.m_p, right.m_p);
}
*/

template<class result_type>
class function
{
public:

	CTOR function(IFunction* p) : m_p(p)
	{
	}

	virtual unsigned getNumArgs() const = 0;

	IFunction* m_p;
};

template<class result_type>
class function0 : public function<result_type>
{
public:

	typedef result_type result_t;

	CTOR function0(IFunction* p) : function<result_type>(p)
	{
	}

#ifndef __LERSTAD__
	typed_expression<result_type> operator () () const
	{
		return typed_expression<result_type>(new FunctionCall0Expression(m_p));
	}
#endif

	virtual unsigned getNumArgs() const
	{
		return 0;
	}
};

template<class result_type, class arg0_type>
class function1 : public function<result_type>
{
public:

	typedef result_type result_t;
	typedef arg0_type arg0_t;

	CTOR function1(IFunction* p) : function<result_type>(p)
	{
	}

#ifndef __LERSTAD__
	typed_expression<result_type> operator () (arg0_type arg0) const
	{
		return typed_expression<result_type>(new FunctionCall1Expression(m_p, arg0.m_p));
	}
#endif

	virtual unsigned getNumArgs() const
	{
		return 1;
	}
};

template<class result_type, class arg0_type, class arg1_type>
class function2 : public function<result_type>
{
public:

	typedef result_type result_t;
	typedef arg0_type arg0_t;
	typedef arg1_type arg1_t;

	CTOR function2(IFunction* p) : function<result_type>(p)
	{
	}

#ifndef __LERSTAD__
	typed_expression<result_type> operator () (arg0_type arg0, arg1_type arg1) const
	{
		return typed_expression<result_type>(new FunctionCall2Expression(m_p, arg0.m_p, arg1.m_p));
	}
#endif

	virtual unsigned getNumArgs() const
	{
		return 2;
	}
};

template<class result_type>
class method
{
public:

	CTOR method(Declarator* p) : m_p(p)
	{
	}

	virtual unsigned getNumArgs() const = 0;

	Declarator* m_p;
};

template<class result_type>
class method0 : public method<result_type>
{
public:

	typedef result_type result_t;

	CTOR method0(Declarator* p) : method<result_type>(p)
	{
	}

#ifndef __LERSTAD__
	typed_expression<result_type> operator () () const
	{
		return typed_expression<result_type>(new MethodCall0Expression(m_p));
	}
#endif

	virtual unsigned getNumArgs() const
	{
		return 0;
	}
};

template<class result_type, class arg0_type>
class GUIEXT method1 : public method<result_type>
{
public:

	typedef result_type result_t;
	typedef arg0_type arg0_t;

	CTOR method1(Declarator* p) : method<result_type>(p)
	{
	}

#ifndef __LERSTAD__
	typed_expression<result_type> operator () (arg0_type arg0) const
	{
		return typed_expression<result_type>(new MethodCall1Expression(m_p, arg0.m_p));
	}
#endif

	virtual unsigned getNumArgs() const
	{
		return 1;
	}
};

template<class result_type>
class methodcall : public typed_expression<result_type>
{
public:

	CTOR methodcall(MethodCallExpression* p) : typed_expression<result_type>(p)
	{
	}

	virtual unsigned getNumArgs() const = 0;
};

template<class result_type>
class methodcall0 : public methodcall<result_type>
{
public:

	typedef result_type result_t;

	CTOR methodcall0(MethodCallExpression* p) : methodcall<result_type>(p)
	{
	}

#ifndef __LERSTAD__
	typed_expression<result_type> operator () () const
	{
		return typed_expression<result_type>(new MethodCall0Expression(m_p));
	}
#endif

	virtual unsigned getNumArgs() const
	{
		return 0;
	}
};

template<class result_type, class arg0_type>
class GUIEXT methodcall1 : public method<result_type>
{
public:

	typedef result_type result_t;
	typedef arg0_type arg0_t;

	CTOR methodcall1(Declarator* p) : methodcall<result_type>(p)
	{
	}

#ifndef __LERSTAD__
	typed_expression<result_type> operator () (arg0_type arg0) const
	{
		return typed_expression<result_type>(new MethodCall1Expression(m_p, arg0.m_p));
	}
#endif

	virtual unsigned getNumArgs() const
	{
		return 1;
	}
};

class GUIEXT statement
{
public:
	CTOR statement()
	{
	}

	virtual ~statement()
	{
	}
};

class GUIEXT expressionStatement : public statement
{
public:
	CTOR expressionStatement(const expression& exp)
	{
	}
};

class GUIEXT var
{
public:
	CTOR var(int n)
	{
	}
};

class GUIEXT _object : public expression
{
public:

	CTOR _object(const expression& exp);
	virtual ~_object();

//	virtual int get_sizeof() const = 0;

	operator Expression* () const
	{
		return (Expression*)m_p;
	}

	// TODO
	typed_expression<float> getMember(int offset) const
	{
		return new GetMemberByOffsetExpression(m_p, offset);
	}

#if 0
	expression getProperty(const expression& exp) const
	{
		ASSERT(0);
		//return new GetDPPropertyByExpExpression(m_p, exp.m_p);
		return NULL;
	}
#endif

	static const _object& get_this();

	static _object s_this;
};

class GUIEXT _Object : public _object
{
public:

	CTOR _Object(const expression& exp) : _object(exp)
	{
	}

	methodcall0<_ClassType*> GetType() const
	{
		return new MethodCall0Expression<float>(_this(), GetDispatch(typeid(Object).GetType()->AsClass())->GetMethod("GetType"));
	}

	DEFINE_THIS(_Object)
};

class GUIEXT _ClassType : public _Object
{
public:
	CTOR _ClassType(ObjectExpression* p) : _Object(p)
	{
	}

	typed_expression<int> getSizeof() const
	{
		ASSERT(0);
		return typed_expression<int>(0);
	}
};

class GUIEXT If : public statement
{
public:

	CTOR If(Expression* testExp, Expression* trueExp, Expression* falseExp) :
		m_p(new ConditionalExpression(testExp, trueExp, falseExp))
	{
	}

	operator ConditionalExpression* ()
	{
		return m_p;
	}

	ConditionalExpression* m_p;
};

#if 0
class GUIEXT Math
{
public:

	// cos
	static typed_expression<float> sin(const typed_expression<float>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<float, float, ::sinf>(exp);
#endif
	}

	static typed_expression<double> sin(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::sin>(exp);
#endif
	}

	// sin
	static typed_expression<float> cos(const typed_expression<float>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<float, float, ::cosf>(exp);
#endif
	}

	static typed_expression<double> cos(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::cos>(exp);
#endif
	}

// acos
	static typed_expression<double> acos(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::acos>(exp);
#endif
	}

	static typed_expression<float> acos(const typed_expression<float>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<float, float, ::acosf>(exp);
#endif
	}

// asin
	static typed_expression<double> asin(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::asin>(exp);
#endif
	}

	static typed_expression<float> asin(const typed_expression<float>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<float, float, ::asinf>(exp);
#endif
	}

/// atan

	static typed_expression<float> atan(const typed_expression<float>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<float, float, ::atanf>(exp);
#endif
	}

	static typed_expression<double> atan(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::atan>(exp);
#endif
	}

// sqrt
	static typed_expression<double> sqrt(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::sqrt>(exp);
#endif
	}

// pow
	static typed_expression<double> pow(const typed_expression<double>& x, const typed_expression<double>& y)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall2Expression<double, double, double, ::pow>(x, y);
#endif
	}

// floor

	static typed_expression<double> floor(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::floor>(exp);
#endif
	}

// ceil

	static typed_expression<double> ceil(const typed_expression<double>& exp)
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall1Expression<double, double, ::ceil>(exp);
#endif
	}

	// rand

	static typed_expression<int> rand()
	{
#ifndef __LERSTAD__
		return new StaticFunctionCall0Expression<int, ::rand>();
#endif
	}

	static const int randMax = RAND_MAX;

private:

	CTOR Math();
};
#endif

#if 0
template<class result_type, class arg0_type>
class ExpressionFunctionT1 : public Object, public IFunctionT1<result_type, arg0_type>
{
public:

	CTOR ExpressionFunctionT1(expression exp) : m_exp(exp.m_p)
	{
	}

	result_type call(arg0_type arg0)
	{
		EvalContext evalContext;
		evalContext.m_this = arg0;
		Object* result = m_exp->Evaluate(&evalContext);
		return unbox_cast<result_type>(result);
	}

	Expression* m_exp;
};
#endif

}	// Expressive
}	// System
