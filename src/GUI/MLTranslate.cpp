#include "stdafx.h"
#include "GUI2.h"

#include "CodeComp/ir.h"

#pragma comment(lib, "CodeComp")

namespace System
{

#if 0
bool IsCompatible(Type*, Type* argType)
{
	argType = argType->GetStripped();

	if (arg.IsBool())
	{
		if (argType->get_Kind() == type_bool)
		{
			return true;
		}
	}
	else if (arg.IsInt())
	{
		if (
			/*
			argType->get_Kind() == type_signed_char ||
			argType->get_Kind() == type_unsigned_char ||
			argType->get_Kind() == type_short ||
			argType->get_Kind() == type_unsigned_short ||
			*/
			argType->get_Kind() == type_int ||
			argType->get_Kind() == type_unsigned_int ||
			argType->get_Kind() == type_float ||
			argType->get_Kind() == type_double/* ||

			argType->get_Kind() == type_enum*/)

		{
			return true;
		}
	}
	else if (arg.IsFloat())
	{
		if (
			/*
			argType->get_Kind() == type_signed_char ||
			argType->get_Kind() == type_unsigned_char ||
			argType->get_Kind() == type_short ||
			argType->get_Kind() == type_unsigned_short ||
			argType->get_Kind() == type_int ||
			argType->get_Kind() == type_unsigned_int ||
			*/
			argType->get_Kind() == type_float ||
			argType->get_Kind() == type_double)
		{
			return true;
		}
	}
	else if (arg.IsDouble())
	{
		if (
			/*
			argType->get_Kind() == type_signed_char ||
			argType->get_Kind() == type_unsigned_char ||
			argType->get_Kind() == type_short ||
			argType->get_Kind() == type_unsigned_short ||
			argType->get_Kind() == type_int ||
			argType->get_Kind() == type_unsigned_int ||
			*/
			argType->get_Kind() == type_float ||
			argType->get_Kind() == type_double)
		{
			return true;
		}
	}
#if 0
	else if (arg.kind == VARKIND_STRINGA ||
			arg.kind == VARKIND_STRINGW)
	{
		if (argType->get_Kind() == type_class)
		{
			// TODO
					return true;	// Derived from, ok, continue
		}
		else if (argType->get_Kind() == type_pointer &&
			(argType->GetPointerTo()->GetStripped()->get_Kind() == type_char ||
			argType->GetPointerTo()->GetStripped()->get_Kind() == type_wchar))
		{
			// char* or wchar_t*

			return true;
		}
	}
#endif
	else if (arg.IsString())	// TODO, not like this
	{
		if (argType == typeid(String) || argType == typeid(StringIn))
		{
			return true;
		}
	}
	else if (arg.kind == VARKIND_STRUCT)
	{
		ClassType* pStructType = arg.m_pType->GetClass();

		if (argType->get_Kind() == type_class)
		{
			if (pStructType == argType->GetClass())
			{
				return true;	// match, ok, continue
			}
		}
		else if (argType->get_Kind() == type_reference)
		{
			Type* refType = argType->GetPointerTo()->GetStripped();

			if (refType->get_Kind() == type_class)
			{
				if (pStructType->IsDerivedFrom(refType->GetClass()))
				{
					return true;	// Derived from, ok, continue
				}
			}
		}
	}
	else if (argType->get_Kind() == type_pointer &&
			argType->GetPointerTo()->get_Kind() == type_function)
	{
		if (arg.GetObjectType() == typeid(ScriptFunction))
		{
			return true;
		}
		else
			return false;
	}
	else if (arg.IsObject())
	{
		ClassType* pObjectType = arg.GetObjectType();

		if (argType->get_Kind() == type_pointer)
		{
			Type* pPointerTo = argType->GetPointerTo()->GetStripped();
			if (pPointerTo->get_Kind() == type_class)
			{
				if (pObjectType->IsDerivedFrom(pPointerTo->AsClass()))
				{
					return true;	// Derived from, ok, continue
				}
			}
		}
		else if (argType->get_Kind() == type_reference)	// Treat like pointer
		{
			Type* pPointerTo = argType->GetPointerTo()->GetStripped();
			if (pPointerTo->get_Kind() == type_class)
			{
				if (pObjectType->IsDerivedFrom(pPointerTo->GetClass()))
				{
					return true;	// Derived from, ok, continue
				}
			}
		}
	}
	else if (arg.IsNull())
	{
		if (argType->get_Kind() == type_pointer)
		{
			// by commenting this, we can call a function like
			// func(int* iptr) with a null iptr
			// don't know if a function like above is useful from ecmascript though?

		//	if (pType->GetPointerTo()->get_Kind() == type_class)
			{
				return true;	// ok, continue
			}
		}
	}
	else
	{
		raise(Exception("TODO: conversion not implemented"));
	}

	return false;
}
#endif

namespace Expressive
{

NamedType* GetNamedType(Expression* exp)
{
	NamedType* pType = NULL;

	TypeExpression* texp = dynamic_cast<TypeExpression*>(exp);
	
	return dynamic_cast<NamedType*>(texp->m_pTypeId);
	/*
	while (exp->GetKind() == Kind_Member)
	{
		MemberExpression* mexp = dynamic_cast<MemberExpression*>(exp)->m_id;

		mexp->m_id;

		String name = dynamic_cast<IdExpression*>(exp)->m_id;

		multimap<String, NamedType*>::iterator it = pD->m_namedTypesM.find(name);
		if (it == pD->m_namedTypesM.end())
		{
			return NULL;
		}
		pType = it->second;
	}
	*/
	ASSERT(0);

	return pType;
}

_Ptr<IO::TextWriter> Translator::smsg()
{
	return Std::get_Out();
}

IO::TextWriter& WriteToStream(IO::TextWriter& stream, const lex_loc& loc)
{
	stream << loc.m_filepath << "(" << loc.m_line+1 << "," << loc.m_column+1 << ")";
	return stream;
}

void Translator::Error(IO::TextWriter& stream)
{
	++m_nerrors;
	stream << "\n";
}

Expression* Translator::TranslateExpression(AExpression* exp, ClassType* thisType, IFrameContext* frame, map<String, Expression*>& defs, StringIn defname)
{
	if (exp->GetKind() == Kind_This)
	{
		if (thisType == NULL)
		{
			Error(smsg() << exp->m_loc << "Cannot infer typeof(this) : this = null");
		}
		return ThisExpression::OfType(thisType);
	}
	else if (exp->GetKind() == Kind_ID)
	{
		AIdExpression* idexp = static_cast<AIdExpression*>(exp);

		if (thisType)
		{
			// First try property if in class scope
			Gui::DependencyClass* depclass = Gui::DependencyClass::GetClass(thisType->AsClass());
			if (depclass)
			{
				Gui::DependencyProperty* dp = depclass->GetLocalProperty(idexp->m_id);
				if (dp)
				{
					Expression* texp = new Gui::GetDPByDPExpression(ThisExpression::OfType(thisType), dp);
					texp->m_pType = dp->get_Type().GetType();
					if (texp->m_pType->get_Kind() == type_pointer)
					{
						texp->m_pType = texp->m_pType->GetPointerTo();
					}
					return texp;
				}
			}
		}

		// Then try

		// TODO, return GetVariableExpression ??

		if (frame)
		{
			Variant var = frame->GetVariable(idexp->m_id);
			if (!var.IsUndefined())
			{
				if (var.IsObject())
				{
					return new StaticObjectExpression(var.GetObject());
				}
				else
				{
					switch (var.GetType()->GetStripped()->get_Kind())
					{
					case type_short: 		return new ConstExpression<int>(var.u.int16_val);
					case type_int: 			return new ConstExpression<int>(var.u.int32_val);
					case type_long_long:		return new ConstExpression<int64>(var.u.int64_val);
					case type_float:			return new ConstExpression<float>(var.u.float32_val);
					case type_double:		return new ConstExpression<double>(var.u.float64_val);

					default:
						raise(Exception("TODO: unsupported Variant type"));
					}
				}
			}
		}

		Expression* e = defs.find(idexp->m_id)->second;
		if (e)
		{
			return e;
		}

		auto it = TypeDatabase::pD->m_namedTypesM.find(idexp->m_id);
		if (it != TypeDatabase::pD->m_namedTypesM.end())
		{
			return new TypeExpression(it->second);
		}

		Error(smsg() << exp->m_loc << "unknown variable " << idexp->m_id);
		raise(Exception());
	}
	else if (exp->GetKind() == Kind_Member)
	{
		AMemberExpression* me = static_cast<AMemberExpression*>(exp);

		Expression* tleft = TranslateExpression(me->m_object, thisType, frame, defs);
		if (tleft == nullptr)
			return nullptr;

		if (tleft->m_pType->get_Kind() == type_enum)	// TODO:, really not like this, only if property name happens to be same as enum name --
		{
			EnumDef* pDef = static_cast<EnumType*>(tleft->m_pType)->GetItem(me->m_id);
			if (pDef == nullptr)
			{
			//	StringStream str;
				Error(smsg() << exp->m_loc << me->m_id << " not found in enum " << tleft->m_pType->ToString());
				return nullptr;
				//raise(Exception(str->str()));
			}
			Expression* e = new ConstExpression<int>(pDef->m_value);
			e->m_pType = tleft->m_pType;
			return e;
		}
		else if (tleft->m_pType->get_Kind() != type_class)
		{
			Error(smsg() << exp->m_loc << " left of member not a class");
			raise(Exception());
		}

		TypeExpression* pTypeExpression = dynamic_cast<TypeExpression*>(tleft);
		if (pTypeExpression)
		{
			if (pTypeExpression->m_pTypeId->get_Kind() == type_enum)
			{
				EnumDef* pDef = static_cast<EnumType*>(pTypeExpression->m_pTypeId)->GetItem(me->m_id);
				if (pDef == nullptr)
				{
				//	StringStream str;
					Error(smsg() << exp->m_loc << me->m_id << " not found in enum " << tleft->m_pType->ToString());
					return nullptr;
					//raise(Exception(str->str()));
				}
				Expression* e = new ConstExpression<int>(pDef->m_value);
				e->m_pType = pTypeExpression->m_pTypeId;
				return e;
			}

			NamespaceType* pNamespaceType = dynamic_cast<NamespaceType*>(pTypeExpression->m_pTypeId);
			if (pNamespaceType == NULL)
			{
				raise(Exception("not namespace type"));
			}

			Dispatch* pDispatch = GetDispatch(pNamespaceType);

			if (Property* p = pDispatch->GetProperty(me->m_id))
			{
				Declarator* method = p->get_GetMethod();
				if (true)	// Constant arguments
				{
					Expression* e = new StaticObjectExpression((Object*)method->int32_invoke_function(NULL, 0));
					e->m_pType = method->get_ReturnType()->GetPointerTo();
				//	e->m_pType = e->m_pType->GetPointerTo();
					return e;
				}
				else
				{
					Expression* e = new FunctionCall0Expression<Object*>(method);
					e->m_pType = method->get_ReturnType()->GetPointerTo();
				//	e->m_pType = e->m_pType->GetPointerTo();
					return e;
				}
			}
			else
			{
				auto it = pNamespaceType->m_pScope->m_decls.find(me->m_id);
				if (it != pNamespaceType->m_pScope->m_decls.end())
				{
					return new TypeExpression(it->second->m_pType);
				}
			}
		}

		Gui::DependencyClass* depclass = Gui::DependencyClass::GetClass(tleft->m_pType->AsClass());
		if (depclass)
		{
			Gui::DependencyProperty* dp = depclass->GetLocalProperty(me->m_id);
			if (dp == nullptr)
			{
				IO::StringWriter str;
				str << depclass->GetClassType()->get_QName() << " doesn't have property " << me->m_id;
				raise(Exception(str.str()));
			}

			Expression* texp = new Gui::GetDPByDPExpression(tleft, dp);
			texp->m_pType = dp->get_Type().GetType();
			if (texp->m_pType->get_Kind() == type_pointer)
			{
				texp->m_pType = texp->m_pType->GetPointerTo();
			}
			return texp;
		}
		else
		{
			raise(Exception("oops"));
		}
	}
	else if (exp->GetKind() == Kind_CONST)
	{
		if (AConstExpression<bool>* p = dynamic_cast<AConstExpression<bool>*>(exp))
		{
			return new ConstExpression<bool>(p->m_value);
		}
		else if (AConstExpression<int>* p = dynamic_cast<AConstExpression<int>*>(exp))
		{
			return new ConstExpression<int>(p->m_value);
		}
		else if (AConstExpression<unsigned int>* p = dynamic_cast<AConstExpression<unsigned int>*>(exp))
		{
			return new ConstExpression<int>(p->m_value);
		}
		else if (AConstExpression<float>* p = dynamic_cast<AConstExpression<float>*>(exp))
		{
			return new ConstExpression<float>(p->m_value);
		}
		else if (AConstExpression<double>* p = dynamic_cast<AConstExpression<double>*>(exp))
		{
			return new ConstExpression<double>(p->m_value);
		}
		else
		{
			raise(Exception("TODO: unknown const type"));
		}
	}
	else if (exp->GetKind() == Kind_Relational)
	{
		ARelationalExpression* relexp = dynamic_cast<ARelationalExpression*>(exp);
		Expression* left = TranslateExpression(relexp->m_left, thisType, frame, defs);
		Expression* right = TranslateExpression(relexp->m_right, thisType, frame, defs);

		if (left->m_pType != right->m_pType)
		{
			raise(Exception("binop left/right must be of same type"));
		}

		RelationalExpression* e;

		switch (relexp->GetOperator())
		{
		case '=':
			e = new EQRelationalExpression(left, right);
			break;

		case '!=':
			e = new NEQRelationalExpression(left, right);
			break;

		case '<':
			e = new LTRelationalExpression(left, right);
			break;

		case '>':
			e = new GTRelationalExpression(left, right);
			break;

		case '<=':
			e = new LTEQRelationalExpression(left, right);
			break;

		case '>=':
			e = new GTEQRelationalExpression(left, right);
			break;
		}

		return e;
	}
	else if (exp->GetKind() == Kind_Conditional)
	{
		AConditionalExpression* acond = static_cast<AConditionalExpression*>(exp);

		ConditionalExpression* cond = new ConditionalExpression(
			TranslateExpression(acond->m_testExp, thisType, frame, defs),
			TranslateExpression(acond->m_trueExp, thisType, frame, defs),
			TranslateExpression(acond->m_falseExp, thisType, frame, defs));

		if (cond->m_testExp->m_pType != typeid(bool))
		{
			Error(smsg() << exp->m_loc << "conditional test must be of bool type");
		}

		if (cond->m_trueExp->m_pType != cond->m_falseExp->m_pType)
		{
			Error(smsg() << exp->m_loc << "true/false must be of same type");
		}

		// If the test is a constant, evaluate it now
		if (cond->m_testExp->m_pType == typeid(bool))
		{
			if (cond->m_testExp->GetKind() == Kind_CONST)
			{
				if (unbox_cast<bool>(cond->m_testExp->Evaluate(nullptr)))
				{
					return cond->m_trueExp;
				}
				else
				{
					return cond->m_falseExp;
				}
			}
		}

		cond->m_pType = cond->m_trueExp->m_pType;
		return cond;
	}
	else if (exp->GetKind() == Kind_NEWOBJ)
	{
		ANewObjProperties* anewexp = static_cast<ANewObjProperties*>(exp);

		/*
		Tr_Exp* tleft = TransExpression(newexp->m_left, as_context);
		if (tleft == NULL)
			return NULL;
			*/

		NamedType* pType = GetNamedType(TranslateExpression(anewexp->m_obj, thisType, frame, defs));

		Object* obj;
		obj = newobj(pType->AsClass());

		StaticObjectExpression* objexp = new StaticObjectExpression(obj);

		if (defname != nullptr)
		{
			defs[defname] = objexp;	// TODO
		}

		Gui::DependencyObject* depobj = dynamic_cast<Gui::DependencyObject*>(obj);

		for (auto it = anewexp->m_properties.begin(); it != anewexp->m_properties.end(); ++it)
		{
			AMemberExpression* mexp = dynamic_cast<AMemberExpression*>(it->first);
			if (mexp)
			{
				if (m_extension)
				{
					m_extension->OnExp(objexp, mexp);
				}
			}

			try
			{
				AIdExpression* idexp = dynamic_cast<AIdExpression*>(it->first);
				if (idexp)
				{
					String membername = idexp->m_id;

					Expression* mexp = TranslateExpression(it->second, pType->AsClass(), frame, defs);

					Gui::DependencyProperty* dp = depobj->GetClass()->GetLocalProperty(membername);
					if (dp == NULL)
					{
						IO::StringWriter str;
						str << membername << " not a member of " << depobj->GetClass()->GetClassType()->m_name;
						raise(Exception(str.str()));
					}
					Type* dpType = dp->GetPropertyType();

					if (mexp == nullptr)
					{
						return nullptr;
					}

					// TODO
				//	if (mexp->m_pType != typeid(String))
					/*
					Declarator* converter_method;

					if (!GetConverter(mexp->m_pType, dpType, &converter_method))
					{
						Error(smsg() << it->second->m_loc << "Cannot set " << dp->get_Name() << " : " << mexp->m_pType->ToString() << " to " << dp->get_Type().GetType()->ToString());
					}
					*/

					if (auto str = dynamic_cast<StringExpression*>(mexp))
					{
						Variant value(str->m_str.m_stringObject);//mexp->Evaluate(nullptr), dpType);

						depobj->GetProperty(dp)->SetLocalValue(value);
					}
					else if (mexp->GetKind() == Kind_CONST ||
						dynamic_cast<StaticObjectExpression*>(mexp)/* ||
						dynamic_cast<StringExpression*>(mexp)*/)
					{
						Variant value(mexp->Evaluate(nullptr), dpType);

						depobj->GetProperty(dp)->SetLocalValue(value);
					}
					else
					{
						// ??
						if (dpType->get_Kind() == type_pointer)
						{
							dpType = dpType->GetPointerTo();
						}

						if (!mexp->m_pType->IsOfType(dpType))
						{
							Error(smsg() << it->second->m_loc << "Cannot set " << dp->get_Name() << " : " << mexp->m_pType->ToString() << " to " << dp->get_Type().GetType()->ToString());
						}

						depobj->GetProperty(dp)->SetInputBinding(new Gui::ExpressionBinding(depobj, mexp));
					}
				}
				else if (AMemberExpression* memexp = dynamic_cast<AMemberExpression*>(it->first))
				{
				//	IDictionary* dict = dynamic_cast<IDictionary*>(depobj);
				//	Expression* e = TranslateExpression(it->second, thisType, frame, defs);
				//	StaticObjectExpression* s = dynamic_cast<StaticObjectExpression*>(e);
				//	dict->SetKeyValue(e, e->Evaluate(nullptr));

					AIdExpression* idexp = dynamic_cast<AIdExpression*>(memexp->m_object);
					ASSERT(idexp);
				//	idexp->m_id
					Gui::DependencyProperty* dp = Gui::DependencyClass::FindGlobalProperty(memexp->m_id);

					Expression* mexp = TranslateExpression(it->second, pType->AsClass(), frame, defs);

					Variant value(mexp->Evaluate(nullptr), dp->GetPropertyType());
					depobj->GetProperty(dp)->SetLocalValue(value);

				}
				else
				{
					if (Gui::GroupVisual* group = dynamic_cast<Gui::GroupVisual*>(depobj))
					{
						Expression* e = TranslateExpression(it->second, thisType, frame, defs);
						if (e != nullptr)
						{
							StaticObjectExpression* s = dynamic_cast<StaticObjectExpression*>(e);
							group->AddChild(dynamic_cast<Gui::Visual*>(s->m_obj));
						}
					}
					else if (Gui::Media3D::Group* group = dynamic_cast<Gui::Media3D::Group*>(depobj))
					{
						Expression* e = TranslateExpression(it->second, thisType, frame, defs);
						if (e != nullptr)
						{
							StaticObjectExpression* s = dynamic_cast<StaticObjectExpression*>(e);
							group->AddChild(dynamic_cast<Gui::Media3D::Visual3D*>(s->m_obj));
						}
					}
					else if (Gui::UIElement* group = dynamic_cast<Gui::UIElement*>(depobj))
					{
						Expression* e = TranslateExpression(it->second, thisType, frame, defs);
						if (e != nullptr)
						{
							StaticObjectExpression* s = dynamic_cast<StaticObjectExpression*>(e);
							group->AddChild(dynamic_cast<Gui::Visual*>(s->m_obj));
						}
					}
					else
						ASSERT(0);	// TODO
				}
			}
			catch (Exception* e)
			{
				Std::get_Out() << e->get_Reason() << endl;
			}
		}

		return objexp;
//		return Tr_Ex(new T_ObjectExp(obj));

#if 0
		ArgList* targs = NULL;

		A_ExpList* args = newexp->m_args;
		while (args)
		{
			Tr_Exp* tr = TransExpression(args->head, as_context);

			targs = new ArgList(unEx(tr), targs);

			args = args->tail;
		}

		T_Exp* left = unEx(tleft);

		return Tr_Ex(new T_NewExp(left, targs));
#endif
	}
	else if (ADEFExpression* defexp = dynamic_cast<ADEFExpression*>(exp))
	{
		Expression* e = TranslateExpression(defexp->m_exp, thisType, frame, defs, defexp->m_name);
		return e;
	}
	/*
	else if (AUSEExpression* useexp = dynamic_cast<AUSEExpression*>(exp))
	{
		return defs[useexp->m_name];
	}
	*/
	else if (ATypeofExpression* typeofexp = dynamic_cast<ATypeofExpression*>(exp))
	{
		Expression* texp = TranslateExpression(typeofexp->m_exp, thisType, frame, defs);
		ASSERT(texp->m_pType);
		return new TypeExpression(texp->m_pType);
	}
	else if (AExpressionExpression* expofexp = dynamic_cast<AExpressionExpression*>(exp))
	{
		Expression* texp = new StaticObjectExpression(TranslateExpression(expofexp->m_exp, thisType, frame, defs));
		ASSERT(texp->m_pType);
		return texp;
	}
	else if (ANullExpression* nullexp = dynamic_cast<ANullExpression*>(exp))
	{
		Expression* texp = new StaticObjectExpression();
		texp->m_pType = Types::get_nullType();
		return texp;
	}
	else if (ACallExpression* callexp = dynamic_cast<ACallExpression*>(exp))
	{
		bool bConst = true;
		vector<Expression*> args;
		args.reserve(callexp->m_args.size());
		for (uint i = 0; i < callexp->m_args.size(); ++i)
		{
			Expression* e = TranslateExpression(callexp->m_args[i], thisType, frame, defs);
			args.push_back(e);
			if (e->GetKind() != Kind_CONST)
			{
				bConst = false;
			}
		}

		Declarator* decl = nullptr;

		AMemberExpression* me = dynamic_cast<AMemberExpression*>(callexp->m_name);
		if (me)
		{
			Expression* e = TranslateExpression(me->m_object, thisType, frame, defs);
			TypeExpression* et = dynamic_cast<TypeExpression*>(e);
			NamespaceType* ns = dynamic_cast<NamespaceType*>(et->m_pTypeId);
			auto it = ns->m_pScope->m_decls.find(me->m_id);

			decl = it->second;

			if (decl == nullptr)
			{
				Error(smsg() << me->m_loc << "function '" << me->m_id << "' not found");
				return nullptr;
			}
		}
		else
		{
			AIdExpression* idexp = dynamic_cast<AIdExpression*>(callexp->m_name);
			if (idexp == nullptr)
			{
				Error(smsg() << exp->m_loc << "not identifier");
				return nullptr;
			}

			auto it = TypeDatabase::pD->m_procs.find(idexp->m_id);
			if (it == TypeDatabase::pD->m_procs.end())
			{
				Error(smsg() << exp->m_loc << "function not found");
				return nullptr;
			}

			do
			{
				FunctionType* pFun = it->second->m_decl->m_pType->AsFunction();
				if (pFun->m_parameters.m_parameters.size() == args.size())
				{
					bool exactMatch = true;

					uint i;
					for (i = 0; i < args.size(); ++i)
					{
						if (args[i]->m_pType->GetStripped()->get_Kind() == type_class)
						{
							ClassType* pC = args[i]->m_pType->GetStripped()->AsClass();

							if (pC->m_name == "ValueBinding")
							{
								Gui::IBinding* binding = __dynamic_cast<Gui::IBinding*>(args[i]->Evaluate(NULL));
								args[i] = new Gui::BindingExpression(binding);
							}
							else
							{
								Dispatch* pDispatch = GetDispatch(pC);
								auto it = pDispatch->m_methodnames.find("operator conversion");

							//	multimap<String, Declarator*>::iterator it = pC->m_pScope->m_decls.find("operator conversion");
								if (it != pDispatch->m_methodnames.end())
								{
									Declarator* method;
									do
									{
										method = it->second;
										if (!method->m_pType->AsFunction()->m_pReturnType->IsOfType(pFun->m_parameters[i].m_pType))
										{
											break;
										}
										++it;
									}
									while (it->first == "operator conversion");
								
									if (it->first == "operator conversion")
									{
										break;
									}

									switch (method->m_pType->AsFunction()->m_pReturnType->get_Kind())
									{
									case type_bool:
										args[i] = new MethodCall0Expression<bool>(args[i], method);
										break;

									case type_int:
										args[i] = new MethodCall0Expression<int>(args[i], method);
										break;

									case type_unsigned_int:
										args[i] = new MethodCall0Expression<unsigned int>(args[i], method);
										break;

									case type_float:
										args[i] = new MethodCall0Expression<float>(args[i], method);
										break;

									case type_double:
										args[i] = new MethodCall0Expression<double>(args[i], method);
										break;
									}
									continue;
								}
							}
						}

							/*
						if (pFun->m_parameters[i].m_pType->IsOfType(typeid(IBinding))	// TODO general c++ conversion operator ??
						{
							pFun->m_parameters[i].m_pType
						}
						*/

						if (args[i]->m_pType == pFun->m_parameters[i].m_pType)
						{
							continue;
						}

						exactMatch = false;

						if (!args[i]->m_pType->IsOfType(pFun->m_parameters[i].m_pType))
						{
							break;
						}
					}

					if (exactMatch)
					{
						decl = it->second->m_decl;
						break;
					}

					if (i == args.size())
					{
						if (decl)
						{
							Error(smsg() << exp->m_loc << " : error C001 : " << decl->m_name << " is ambiguous");
							return NULL;
						}
						decl = it->second->m_decl;
					}
				}

				++it;
			}
			while (it->first == idexp->m_id);

			if (decl == nullptr)
			{
				Error(smsg() << idexp->m_loc << " : error : '" << idexp->m_id << "'" << " function with correct arguments not found");
			//	raise(Exception(str->str()));
				return nullptr;
			}
		}

		FunctionType* pFun = decl->m_pType->AsFunction();
		Type* pReturnType = pFun->m_pReturnType->GetStripped();

		if (bConst)
		{
			if (args.size() == 0)
			{
				switch (pReturnType->get_Kind())
				{
				case type_bool:
					return new ConstExpression<bool>(decl->invoke_functionA<bool>(nullptr, 0));
				case type_int:
					return new ConstExpression<int>(decl->invoke_functionA<int>(nullptr, 0));
				case type_unsigned_int:
					return new ConstExpression<unsigned int>(decl->invoke_functionA<unsigned int>(nullptr, 0));
				case type_float:
					return new ConstExpression<float>(decl->invoke_functionA<float>(nullptr, 0));
				case type_double:
					return new ConstExpression<double>(decl->invoke_functionA<double>(nullptr, 0));
				}
			}
			else if (args.size() == 1)
			{
				ASSERT(0);
				/*
				switch (pReturnType->get_Kind())
				{
				case type_int:
					return new ConstExpression<int, float>(it->second->m_decl->m_offset, args[0]);
				case type_float:
					return new ConstExpression<float, float>(it->second->m_decl->m_offset, args[0]);
				case type_double:
					return new ConstExpression<double, float>(it->second->m_decl->m_offset, args[0]);
				}
				*/
			}
		}
		else
		{
			if (args.size() == 0)
			{
				if (pReturnType->get_Kind() == type_int)
					return new FunctionCall0Expression<int>(decl);
				else if (pReturnType->get_Kind() == type_unsigned_int)
					return new FunctionCall0Expression</*unsigned*/ int>(decl);
				else if (pReturnType->get_Kind() == type_float)
					return new FunctionCall0Expression<float>(decl);
				else if (pReturnType->get_Kind() == type_double)
					return new FunctionCall0Expression<double>(decl);
			}
			else if (args.size() == 1)
			{
				if (pFun->m_parameters[0].m_pType->get_Kind() == type_int)
				{
					if (pReturnType->get_Kind() == type_int)
						return new FunctionCall1Expression<int, int>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_float)
						return new FunctionCall1Expression<float, int>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_double)
						return new FunctionCall1Expression<double, int>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_class)
					{
						return new FunctionCall1Expression<String, int>(decl, args[0]);
					}
					else
						raise(Exception("func"));
				}
				else if (pFun->m_parameters[0].m_pType->get_Kind() == type_float)
				{
					if (pReturnType->get_Kind() == type_int)
						return new FunctionCall1Expression<int, float>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_float)
						return new FunctionCall1Expression<float, float>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_double)
						return new FunctionCall1Expression<double, float>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_class)
					{
						return new FunctionCall1Expression<String, float>(decl, args[0]);
					}
					else
						raise(Exception("func"));
				}
				else if (pFun->m_parameters[0].m_pType->get_Kind() == type_double)
				{
					if (pReturnType->get_Kind() == type_int)
						return new FunctionCall1Expression<int, double>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_float)
						return new FunctionCall1Expression<float, double>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_double)
						return new FunctionCall1Expression<double, double>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_class)
					{
						return new FunctionCall1Expression<String, double>(decl, args[0]);
					}
					else
						raise(Exception("func"));
				}
				else if (pFun->m_parameters[0].m_pType->get_Kind() == type_unsigned_char)
				{
					if (pReturnType->get_Kind() == type_int)
						return new FunctionCall1Expression<int, unsigned char>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_float)
						return new FunctionCall1Expression<float, unsigned char>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_double)
						return new FunctionCall1Expression<double, unsigned char>(decl, args[0]);
					else if (pReturnType->get_Kind() == type_class)
					{
						return new FunctionCall1Expression<String, unsigned char>(decl, args[0]);
					}
					else
						raise(Exception("func"));
				}
				else
					ASSERT(0);
			}
			else
				ASSERT(0);
		}
		/*
		else if (callexp->m_args.size() == 2)
		{
			if (pReturnType->get_Kind() == type_int)
				return new FunctionCall2Expression<int>(it->second->m_decl->m_offset, TranslateExpression(callexp->m_args[0], thisType, frame, defs), TranslateExpression(callexp->m_args[1], thisType, frame, defs));
			else if (pReturnType->get_Kind() == type_int)
				return new FunctionCall2Expression<float>(it->second->m_decl->m_offset, TranslateExpression(callexp->m_args[0], thisType, frame, defs), TranslateExpression(callexp->m_args[1], thisType, frame, defs));
			else if (pReturnType->get_Kind() == type_int)
				return new FunctionCall2Expression<double>(it->second->m_decl->m_offset, TranslateExpression(callexp->m_args[0], thisType, frame, defs), TranslateExpression(callexp->m_args[1], thisType, frame, defs));
		}
		*/
		raise(Exception("function ??"));
	}
	else if (ABinaryExpression* abinexp = dynamic_cast<ABinaryExpression*>(exp))
	{
		Expression* left = TranslateExpression(abinexp->m_left, thisType, frame, defs);
		Expression* right = TranslateExpression(abinexp->m_right, thisType, frame, defs);

		switch (abinexp->GetOperator())
		{
		case '%':
			{
				if (!Type::IsInteger(left->m_pType) || !Type::IsInteger(right->m_pType))
				{
					raise(Exception("modulus operator must have integer operands"));
				}
				break;
			}
		}

		if (left->m_pType != right->m_pType)
		{
			raise(Exception("binop left/right must be of same type"));
		}

		BinaryExpression* binexp;

		switch (abinexp->GetOperator())
		{
		case '+':
			binexp = new AddBinaryExpression(left->m_pType, left, right);
			break;

		case '-':
			binexp = new SubtractBinaryExpression(left, right);
			break;

		case '*':
			binexp = new MultiplyBinaryExpression(left, right);
			break;

		case '/':
			binexp = new DivideBinaryExpression(left, right);
			break;

		case '%':
			binexp = new ModulusBinaryExpression(left, right);
			break;
		}

		/*
		if (binexp->m_left->GetKind() == Kind_CONST && binexp->m_right->GetKind() == Kind_CONST)
		{
			return binexp->EvaluateConst();
		}
		*/

		binexp->m_pType = left->m_pType;
		return binexp;
	}
	else if (AUnaryExpression* aunexp = dynamic_cast<AUnaryExpression*>(exp))
	{
		Expression* exp = TranslateExpression(aunexp->m_exp, thisType, frame, defs);
		/*
		if (unexp->m_exp->GetKind() == Kind_CONST)
		{
			return unexp->Evaluate(NULL);
		}
		*/
		UnaryExpression* unexp;
		//switch (aunexp->Get
		unexp = new MinusUnaryExpression(exp);

	//	unexp->m_pType = exp->m_pType;
		return unexp;
	}
	else if (AStringExpression* sexp = dynamic_cast<AStringExpression*>(exp))
	{
		return new StringExpression(sexp->m_str);
	}
	else
	{
		raise(Exception("unknown aexp"));
		//return exp;
	}

	return NULL;
}

Expression* Translator::TranslateDList(ADeclarationList* dlist, IFrameContext* frame)
{
	map<String, Expression*> defs;

	Expression* exp = NULL;

	for (size_t i = 0; i < dlist->m_items.size(); ++i)
	{
		ADeclaration* decl = dlist->m_items[i];

		if (AExpressionDeclaration* dexp = dynamic_cast<AExpressionDeclaration*>(decl))
		{
			exp = TranslateExpression(dexp->m_exp, NULL, frame, defs);
		}
		else if (AValDeclaration* valexp = dynamic_cast<AValDeclaration*>(decl))
		{
		//	Expression* typeexp = TranslateExpression(valexp->m_typeexp, NULL, frame, defs);
		//	if (typeexp->m_pType != 
		//	frame.m_variables[valexp->m_id] = frame->GetVariable("TemplatedOwner");	// TODO
		}
	}

	return exp;
}

Expression* Translator::TranslateExpression(AExpression* exp, IFrameContext* frame)
{
	map<String, Expression*> defs;
	return TranslateExpression(exp, NULL, frame, defs);
}

// static
Expression* Translator::Translate(AExpression* exp, IFrameContext* frame, IParserExtension* ext)
{
	Translator tr(ext);
	return tr.TranslateExpression(exp, frame);
}

// static
Expression* Translator::Translate(ADeclarationList* dlist, IFrameContext* frame, IParserExtension* ext)
{
	Translator tr(ext);
	return tr.TranslateDList(dlist, frame);
}

/*
Expression* TranslateExpression(AExpression* exp, ClassType* thisType, IFrameContext* frame)
{
	map<String, Expression*> defs;
	return TranslateExpression(exp, thisType, frame, defs);
}
*/

/////////////////////////////////////


/*
NamedType* Parser::ReadNamedType()
{
	NamedType* pType = NULL;

	String name = readidentifier();

	multimap<String, NamedType*>::iterator it = pD->m_namedTypesM.find(name);
	if (it == pD->m_namedTypesM.end())
	{
		return NULL;
	}
	pType = it->second;

	while (IsSymbol('.'))
	{
		lex();

		NamespaceType* pNamespaceType = dynamic_cast<NamespaceType*>(pType);
		if (pNamespaceType == NULL)
		{
			return NULL;
		}

		String name = readidentifier();
		multimap<String, Declarator*>::iterator it = pNamespaceType->m_pScope->m_decls.find(name);
		if (it == pNamespaceType->m_pScope->m_decls.end())
		{
			return NULL;
		}

		pType = dynamic_cast<NamedType*>(it->second->m_pType);
	}

	return pType;
}

Object* Parser::LoadObject()
{
	NamedType* pType = ReadNamedType();
	if (pType == NULL)
	{
		return NULL;
	}

	return LoadObjectContent(pType);
}
*/

#if 0
Object* Parser::LoadObjectContent(NamedType* pType)
{
	ClassType* pClassType = pType->GetStripped()->GetClass();

	Object* obj = newobj(pClassType);
	EatChar('{');

	ASSERT(0);
#if 0

	DependencyObject* depobj = dynamic_cast<DependencyObject*>(obj);

	while (!IsSymbol('}'))
	{
		String membername = readidentifier();

		if (IsSymbol('{'))
		{
			multimap<String, NamedType*>::iterator it = pD->m_namedTypesM.find(membername);
			if (it == pD->m_namedTypesM.end())
			{
				ASSERT(0);
				return NULL;
			}
			NamedType* pType = it->second;

			Object* child = LoadObjectContent(pType);

			if (GroupVisual* g = dynamic_cast<GroupVisual*>(obj))
			{
				g->AddChild(dynamic_cast<Visual*>(child));
			}
			else
				ASSERT(0);
		}
		else
		{
			Expression* exp = ParseExpression();

			DependencyProperty* dp = depobj->GetClass()->GetLocalProperty(membername);
			//DependencyProperty* dp = DependencyClass::FindGlobalProperty(membername);
			ASSERT(dp);

			depobj->GetProperty(dp)->SetInputBinding(new ExpressionBinding(depobj, exp));
		}
#if 0
		switch (dp->get_Type().GetType()->get_Kind())
		{
			case type_int:
				{
					int value = dynamic_cast<Expressive::ConstExpression<int>*>(exp)->m_value;

					depobj->SetPropertyValue(dp, value);
				}
				break;

			case type_float:
				{
				//	float value = (float)getfnumber();
				//	float value = dynamic_cast<Expressive::ConstExpression<float>*>(exp)->m_value;
				//	float value = dynamic_cast<Expressive::ConstExpression<int>*>(exp)->m_value;
				//	depobj->SetPropertyValue(dp, value);

					depobj->GetProperty(dp)->SetInputBinding(new ExpressionBinding(exp));
				}
				break;

				/*
			case type_double:
				{
					double value = getfnumber();
					depobj->SetPropertyValue(dp, value);
				}
				break;
				*/

			default:
				{
					Object* value = LoadObject();

					depobj->SetPropertyValue(dp, value);
				}
		}
#endif
	}
#endif

	EatChar('}');

	return obj;
}
#endif

// static
Object* Translator::FromFile(StringIn filename)
{
	IO::FileStream file(filename, IO::FileMode_Open, IO::FileAccess_Read);
	IO::StreamReader reader(&file);
	Lexer lexer(filename, &reader);
	Parser parser(&lexer);

	AExpression* exp = parser.ParseExpression();

	FrameContext frame;
	Translator translator(NULL);
	Expression* texp = translator.TranslateExpression(exp, &frame);
	if (translator.m_nerrors)
	{
		return nullptr;
	}

	return dynamic_cast<StaticObjectExpression*>(texp)->m_obj;
	//return dynamic_cast<T_ObjectExp*>(texp->ex)->m_object;
}

/*
// static
Object* Parser::FromString(StringIn str)
{
	
	StringStream stream(str);
	Lexer lexer(stream);
	Parser parser(&lexer);

	Expression* exp = parser.ParseExpression();

	Expression* texp = TranslateExpression(exp, NULL);

	return dynamic_cast<StaticObjectExpression*>(texp)->m_obj;
}
*/

}	// Expressive
}	// System
