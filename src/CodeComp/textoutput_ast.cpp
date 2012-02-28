#include "stdafx.h"
#include "cpp_ast.h"

namespace System
{
namespace cpp
{
namespace ast
{

CodeCompExt IO::TextWriter& WriteId(IO::TextWriter& stream, Expression* name)
{
	while (name)
	{
		ASSERT(name->GetKind() == Expression::A_BINOP);

		if (name->binop.left)
		{
			if (name->binop.left->GetKind() == Expression::A_CONVERSION)
			{
				stream << "operator ";

				ConversionExp* cexp = dynamic_cast<ConversionExp*>(name->binop.left);

				WriteToStream(stream, cexp->m_typeId);
			}
			else if (name->binop.left->GetKind() == Expression::A_TEMPLATEID)
			{
				stream << String(name->binop.left->templateid.id);

				A_TemplateArgumentList* arglist = name->binop.left->templateid.params;
				if (arglist)
				{
					stream << "<";

					while (arglist)
					{
						A_TemplateArgument* arg = arglist->head;

						if (arg->m_pTypeId)
						{
							WriteToStream(stream, arg->m_pTypeId->m_declspecList);
							if (arg->m_pTypeId->m_declarator) WriteToStream(stream, arg->m_pTypeId->m_declarator);

						//	Write(arg->m_decl);
						}
						else
						{
							WriteToStream(stream, arg->m_pExp);
						}

						arglist = arglist->tail;
						if (arglist) stream << ",";
					}

					stream << ">";
				}
			}
			else if (name->binop.left->GetKind() == Expression::A_UNOP)
			{
				stream << "~" << String(name->binop.left->unop.exp->templateid.id);
			}
			else if (name->binop.left->GetKind() == Expression::A_OPERATOR)
			{
				stream << "operator ";
				switch (name->binop.left->u._operator)
				{
				case 'new':	stream << "new"; break;
				case 'del':	stream << "delete"; break;
				case '=':	stream << "="; break;
				case '+':	stream << "+"; break;
				case '-':	stream << "-"; break;
				case '*':	stream << "*"; break;
				case '/':	stream << "/"; break;
				case '%':	stream << "%"; break;
				case '|':	stream << "|"; break;
				case '^':	stream << "^"; break;
				case '&':	stream << "&"; break;
				case '+=':	stream << "+="; break;
				case '-=':	stream << "-="; break;
				case '*=':	stream << "*="; break;
				case '/=':	stream << "/="; break;
				case '%=':	stream << "%="; break;
				case '|=':	stream << "|="; break;
				case '^=':	stream << "^="; break;
				case '&=':	stream << "&="; break;
				case '==':	stream << "=="; break;
				case '!=':	stream << "!="; break;
				case '<':	stream << "<"; break;
				case '>':	stream << ">"; break;
				case '<=':	stream << "<="; break;
				case '>=':	stream << ">="; break;
				case '<<':	stream << "<<"; break;
				case '>>':	stream << ">>"; break;
				case '<<=':	stream << "<<="; break;
				case '>>=':	stream << ">>="; break;
				case '()':	stream << "()"; break;
				case '[]':	stream << "[]"; break;
				case '++':	stream << "++"; break;
				case '--':	stream << "--"; break;
				case '->':	stream << "->"; break;

				default: ASSERT(0);
				}
			}
			else
				ASSERT(0);
		}

		name = name->binop.right;
		if (name)
		{
			stream << "::";
		}
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, BasicTypeSpecifier type)
{
	switch (type)
	{
	case A_VOID: stream << "void"; break;
	case A_CHAR: stream << "char"; break;
	case A_WCHAR_T: stream << "wchar_t"; break;
	case A_BOOL: stream << "bool"; break;
	case A_SHORT: stream << "short"; break;
	case A_INT: stream << "int"; break;
	case A___INT8: stream << "__int8"; break;
	case A___INT16: stream << "__int16"; break;
	case A___INT32: stream << "__int32"; break;
	case A___INT64: stream << "__int64"; break;
	case A_LONG: stream << "long"; break;
	case A_SIGNED: stream << "signed"; break;
	case A_UNSIGNED: stream << "unsigned"; break;
	case A_FLOAT: stream << "float"; break;
	case A_DOUBLE: stream << "double"; break;
	case A___FLOAT32: stream << "__float32"; break;
	case A___FLOAT64: stream << "__float64"; break;
	default:
		ASSERT(0);
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_DeclSpecExtList* declspecExtList)
{
	while (declspecExtList)
	{
		stream << String(declspecExtList->head->m_id);
		if (declspecExtList->head->m_id == "align")
		{
			stream << "(" << declspecExtList->head->m_arg << ")";
		}

		declspecExtList = declspecExtList->tail;
		if (declspecExtList) stream << " ";
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, DeclSpecList* declspecList)
{
	while (declspecList)
	{
		switch (declspecList->head->GetKind())
		{
		case A_DeclSpec::A_TYPE_CLASS:
			{
				A_Class* type = static_cast<A_Class*>(declspecList->head);

				stream << type->m_head->m_classKey << " ";
				WriteId(stream, type->m_head->m_name);
			}
			break;

		case A_DeclSpec::A_TYPE_CLASSDEF:
			{
				A_ClassDef* type = static_cast<A_ClassDef*>(declspecList->head);

				stream << type->m_head->m_classKey << " ";

				DeclSpecList* declextlist = type->m_head->m_declspecList;
				while (declextlist)
				{
					A_DeclSpecExtModifier* ext = (A_DeclSpecExtModifier*)declextlist->head;

					stream << "__declspec(";
					WriteToStream(stream, ext->m_extlist);
					stream << ") ";

					declextlist = declextlist->tail;
				}

				WriteId(stream, type->m_head->m_name);

				A_BaseSpecifierList* baseList = type->m_baseList;
				if (baseList)
				{
					stream << " : ";

					do
					{
						if (baseList->head->m_virtualpos == 1)
							stream << "virtual ";

						if (baseList->head->m_accessSpec != AccessSpec_Unspecified)
						{
							switch (baseList->head->m_accessSpec)
							{
							case AccessSpec_Private: stream << "private "; break;
							case AccessSpec_Protected: stream << "protected "; break;
							case AccessSpec_Public: stream << "public "; break;
							}
						}

						if (baseList->head->m_virtualpos == 2)
							stream << "virtual ";

						WriteId(stream, baseList->head->m_id);

						baseList = baseList->tail;
						if (baseList) stream << ",";
					}
					while (baseList);
				}

				stream << "\n{\n";

				A_MemberSpec* memberSpec = type->m_memberSpec;
				while (memberSpec)
				{
					switch (memberSpec->GetKind())
					{
					case A_MemberSpec::A_ACCESS_SPEC:
						{
							A_MemberAccessSpec* accessSpec = static_cast<A_MemberAccessSpec*>(memberSpec);

							switch (accessSpec->m_accessSpec)
							{
							case AccessSpec_Private: stream << "private:\n"; break;
							case AccessSpec_Protected: stream << "protected:\n"; break;
							case AccessSpec_Public: stream << "public:\n"; break;
							default: ASSERT(0);
							}
						}
						break;

					case A_MemberSpec::A_MEMBER_DECL:
						{
							A_MemberDecl* memberdecl = (A_MemberDecl*)memberSpec;

							WriteToStream(stream, memberdecl->m_declaration);

							if (memberdecl->m_declaration->GetKind() == ast::Declaration::A_SIMPLE)
							{
								stream << ";\n";
							}
						}
						break;
					}

					memberSpec = memberSpec->m_next;
				}

				stream << "}\n";
			}
			break;

		case A_DeclSpec::A_TYPE_ENUM:
			{
				A_Enum* pEnum = (A_Enum*)declspecList->head;

				stream << "enum";
				if (pEnum->m_name)
				{
					stream << " " << String(pEnum->m_name);
				}
				stream << "\n{\n";

				EnumDefList* deflist = pEnum->m_deflist;
				while (deflist)
				{
					stream << String(deflist->head->m_name);
					if (deflist->head->m_exp)
					{
						stream << " = ";
						WriteToStream(stream, deflist->head->m_exp);
					}

					stream << ",\n";
					deflist = deflist->tail;
				}

				stream << "}\n";
			}
			break;

		case A_DeclSpec::A_TYPE_NAME:
			{
				A_NameType* type = (A_NameType*)declspecList->head;
				Expression* name = type->m_name;

				WriteId(stream, name);
			}
			break;

		case A_DeclSpec::A_TYPE_MODIFIER:
			{
				A_DeclSpecModifier* type = (A_DeclSpecModifier*)declspecList->head;

				switch (type->m_modifier)
				{
				case A_CONST: stream << "const"; break;
				case A_VOLATILE: stream << "volatile"; break;
				case A_TYPEDEF: stream << "typedef"; break;
				case A_EXTERN: stream << "extern"; break;
				case A_STATIC: stream << "static"; break;
				case A_INLINE: stream << "inline"; break;
				case A_VIRTUAL: stream << "virtual"; break;
				case A_FRIEND: stream << "friend"; break;
				case A_AUTO: stream << "auto"; break;
				case A_REGISTER: stream << "register"; break;
				case A_MUTABLE: stream << "mutable"; break;
				case A_EXPLICIT: stream << "explicit"; break;
				case A_CONSTEXPR: stream << "constexpr"; break;
				default:
					ASSERT(0);
				}
			}
			break;

		case A_DeclSpec::A_TYPE_BASIC:
			{
				A_DeclSpecBasicType* type = (A_DeclSpecBasicType*)declspecList->head;

				WriteToStream(stream, type->m_basicType);
			}
			break;

		case A_DeclSpec::A_TYPE_DECLSPECEXT:
			{
				A_DeclSpecExtModifier* type = (A_DeclSpecExtModifier*)declspecList->head;

				stream << "__declspec(";
				WriteToStream(stream, type->m_extlist);
				stream << ")";
			}
			break;

		default:
			ASSERT(0);
		}

		stream << " ";
		declspecList = declspecList->tail;
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_DirectDeclarator* directDeclarator)
{
//	fflush(outfile);

	if (directDeclarator->kind == A_DirectDeclarator::A_DECLARATOR_ID)
	{
		WriteId(stream, directDeclarator->u.declaratorId);
	}
	else if (directDeclarator->kind == A_DirectDeclarator::A_DIRECT_DECLARATOR)
	{
		if (directDeclarator->u.directDeclarator.directDeclarator)
		{
			WriteToStream(stream, directDeclarator->u.directDeclarator.directDeclarator);
		}

		switch (directDeclarator->u.directDeclarator.kind)
		{
		case A_DirectDeclarator::_u::_directDeclarator::A_PAREN:
			{
				stream << "(";

				A_TypeIdList* paramlist = directDeclarator->u.directDeclarator.paramDecls->params;

				while (paramlist)
				{
					A_TypeId* type = paramlist->head;

					WriteToStream(stream, type->m_declspecList);
					if (type->m_declarator) WriteToStream(stream, type->m_declarator);
					if (type->m_def)
					{
						stream << "=";
						WriteToStream(stream, type->m_def);
					}

					paramlist = paramlist->tail;
					if (paramlist) stream << ",";
				}

				if (directDeclarator->u.directDeclarator.paramDecls->varArgs)
				{
					stream << ", ...";
				}

				stream << ")";

				WriteToStream(stream, directDeclarator->u.directDeclarator.decls);
			}
			break;

		case A_DirectDeclarator::_u::_directDeclarator::A_ARRAY:
			{
				stream << "[";

				if (directDeclarator->u.directDeclarator.array)
				{
					WriteToStream(stream, directDeclarator->u.directDeclarator.array);
				}

				stream << "]";
			}
			break;

		default:
			ASSERT(0);
		}
	}
	else if (directDeclarator->kind == A_DirectDeclarator::A_DECLARATOR)
	{
		stream << "(";
		WriteToStream(stream, directDeclarator->u.declarator);
		stream << ")";
	}
	else
		ASSERT(0);

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, InitDeclarator* initDeclarator)
{
	WriteToStream(stream, initDeclarator->m_declarator);
	if (initDeclarator->m_initializer)
	{
		if (initDeclarator->m_initializer->m_exp)
		{
			stream << "=";
			WriteToStream(stream, initDeclarator->m_initializer->m_exp);
		}
		else
		{
			stream << "(";
			WriteToStream(stream, initDeclarator->m_initializer->m_expList);
			stream << ")";
		}
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_Declarator* declarator)
{
	if (typeid(*declarator) == typeid(A_BitfieldDeclarator))
	{
		A_BitfieldDeclarator* d = (A_BitfieldDeclarator*)declarator;

		WriteId(stream, d->m_id);
		stream << ":";
		WriteToStream(stream, d->m_exp);
	}
	else if (typeid(*declarator) == typeid(A_DirectDeclaratorDeclarator))
	{
		A_DirectDeclaratorDeclarator* d = (A_DirectDeclaratorDeclarator*)declarator;

		WriteToStream(stream, d->m_directDeclarator);
	}
	else if (typeid(*declarator) == typeid(A_PtrDeclarator))
	{
		A_PtrDeclarator* ptr = (A_PtrDeclarator*)declarator;

		if (ptr->m_id)
		{
			WriteId(stream, ptr->m_id);
		}

		if (ptr->m_type == '*')
		{
			stream << "*";
			if (ptr->m_declarator) WriteToStream(stream, ptr->m_declarator);
		}
		else if (ptr->m_type == '&')
		{
			stream << "&";
			if (ptr->m_declarator) WriteToStream(stream, ptr->m_declarator);
		}
		else if (ptr->m_type == '&&')
		{
			stream << "&&";
			if (ptr->m_declarator) WriteToStream(stream, ptr->m_declarator);
		}
		else if (ptr->m_type == 's')
		{
			stream << "__stdcall ";
			if (ptr->m_declarator) WriteToStream(stream, ptr->m_declarator);
		}
		else if (ptr->m_type == 'c')
		{
			stream << "__cdecl ";
			if (ptr->m_declarator) WriteToStream(stream, ptr->m_declarator);
		}
		else if (ptr->m_type == 'f')
		{
			stream << "__fastcall ";
			if (ptr->m_declarator) WriteToStream(stream, ptr->m_declarator);
		}
		else
			ASSERT(0);
	}
	else
		ASSERT(0);

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, ExpressionList* exp)
{
	while (exp)
	{
		WriteToStream(stream, exp->head);

		exp = exp->tail;
		if (exp) stream << ",";
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, Expression* exp)
{
	if (exp == NULL)
	{
		stream << "(null)";
		return stream;
	}

	switch (exp->GetKind())
	{
	case Expression::A_TYPE:
		{
			stream << "TODO";
		}
		break;

	case Expression::A_THROW:
		{
			ThrowExp* throwExp = dynamic_cast<ThrowExp*>(exp);
			stream << "throw";
			if (throwExp->m_exp)
			{
				stream << " ";
				WriteToStream(stream, throwExp->m_exp);
			}
		}
		break;

	case Expression::A_NEW:
		{
			NewExp* newexp = dynamic_cast<NewExp*>(exp);

			stream << "new ";

			if (exp->m_new_placement)
			{
				stream << "(";
				WriteToStream(stream, exp->m_new_placement);
				stream << ")";
			}

			WriteToStream(stream, newexp->m_typeId);
			if (newexp->m_args)
			{
				stream << "(";
				WriteToStream(stream, newexp->m_args);
				stream << ")";
			}
		}
		break;

	case Expression::A_DELETE:
		{
			stream << "delete ";
			WriteToStream(stream, exp->unop.exp);
		}
		break;

	case Expression::A_THIS:
		{
			stream << "this";
		}
		break;

	case Expression::A_SIZEOF:
		{
			stream << "sizeof ";
			ASSERT(0);
			//WriteToStream(stream, exp->cast.exp);
		}
		break;

	case Expression::A_SIZEOF_TYPE:
		{
			stream << "sizeof(";
			ASSERT(0);
		//	WriteToStream(stream, exp->cast.typeId);
			stream << ")";
		}
		break;

	case Expression::A_INITCLAUSE:
		{
			stream << "{";
			ASSERT(0);
			/*
			if (exp->call.args)
			{
				WriteToStream(stream, exp->call.args);
			}
			*/

			stream << "}";
		}
		break;

	case Expression::A_CAST:
		{
			ASSERT(0);
			stream << "(";
			stream << "(";
		//	WriteToStream(stream, exp->cast.typeId);
			stream << ")";
		//	WriteToStream(stream, exp->cast.exp);
			stream << ")";
		}
		break;

	case Expression::A_STATIC_CAST:
		{
			ASSERT(0);
			stream << "static_cast<";
		//	WriteToStream(stream, exp->cast.typeId);
			stream << ">";
			stream << "(";
		//	WriteToStream(stream, exp->cast.exp);
			stream << ")";
		}
		break;

	case Expression::A_DYNAMIC_CAST:
		{
			ASSERT(0);
			stream << "dynamic_cast<";
		//	WriteToStream(stream, exp->cast.typeId);
			stream << ">";
			stream << "(";
		//	WriteToStream(stream, exp->cast.exp);
			stream << ")";
		}
		break;

	case Expression::A_CONST_CAST:
		{
			ASSERT(0);
			stream << "const_cast<";
		//	WriteToStream(stream, exp->cast.typeId);
			stream << ">";
			stream << "(";
		//	WriteToStream(stream, exp->cast.exp);
			stream << ")";
		}
		break;

	case Expression::A_REINTERPRET_CAST:
		{
			ASSERT(0);
			stream << "reinterpret_cast<";
		//	WriteToStream(stream, exp->cast.typeId);
			stream << ">";
			stream << "(";
		//	WriteToStream(stream, exp->cast.exp);
			stream << ")";
		}
		break;

	case Expression::A_TYPEID:
		{
			stream << "typeid(";
			ASSERT(0);

			/*
			if (exp->cast.typeId)
				WriteToStream(stream, exp->cast.typeId);
			else
				WriteToStream(stream, exp->cast.exp);
*/
			stream << ")";
		}
		break;

	case Expression::A_STRING:
		{
			int len = exp->templateid.id->GetLength32();

			stream << "\"";

			for (int i = 0; i < len; ++i)
			{
				char c = exp->templateid.id->data()[i];

				if (c == '\n')	stream << "\\n";
				else if (c == '\r')	stream << "\\r";
				else if (c == '\t')	stream << "\\t";
				else if (c == '\"')	stream << "\\\"";
				else if (c == '\\')	stream << "\\";
				else if (c == '\0')	stream << "\\0";
				else stream << c;
			}

			stream << "\"";
		}
		break;

	case Expression::A_CHAR_LITERAL:
		{
			//int len = exp->templateid.id->Length();

			stream << "'";

			uint32 value = exp->u.int32;

			if (value)
			{
				do
				{
					char c = value & 0xff;
					value >>= 8;

					if (c == '\n')	stream << "\\n";
					else if (c == '\r')	stream << "\\r";
					else if (c == '\t')	stream << "\\t";
					else if (c == '\'')	stream << "\\'";
					else if (c == '\\')	stream << "\\";
					else if (c == '\0')	stream << "\\0";
					else stream << c;
				}
				while (value);
			}
			else
			{
				stream << "\\0";
			}

			stream << "'";
		}
		break;

	case Expression::A_TEMPLATEID:
		{
			stream << String(exp->templateid.id);
		}
		break;

	case Expression::A_CALL:
		{
			CallExp* callexp = dynamic_cast<CallExp*>(exp);
			WriteToStream(stream, callexp->m_left);
			stream << "(";
			WriteToStream(stream, callexp->m_args);

			/*
			while (expl)
			{
				Write(expl->head);
				expl = expl->tail;
				if (expl) fprintf(outfile, ",");
			}
			*/
			stream << ")";
		}
		break;

	case Expression::A_INIT:
		{
			InitExp* initexp = dynamic_cast<InitExp*>(exp);

			WriteId(stream, initexp->m_left);
			stream << "(";
			WriteToStream(stream, initexp->m_args);
			stream << ")";
		}
		break;

	case Expression::A_INITBASIC:
		{
			InitBasicExp* initexp = dynamic_cast<InitBasicExp*>(exp);
			WriteToStream(stream, /*(A_BasicTypeSpecifier)*/initexp->m_type);
			stream << "(";
			WriteToStream(stream, initexp->m_args);
			stream << ")";
		}
		break;

	case Expression::A_BOOL:
		{
			if (exp->u.boolValue)
				stream << "true";
			else
				stream << "false";
		}
		break;

	case Expression::A_INT32:
		{
			stream << (int32)exp->u.int32;
		}
		break;

	case Expression::A_FLOAT:
		{
			stream << exp->u.floatValue;
		}
		break;

	case Expression::A_DOUBLE:
		{
			stream << exp->u.doubleValue;
		}
		break;

	case Expression::A_POSTOP:
		{
			stream << "(";
			WriteToStream(stream, exp->unop.exp);

			switch (exp->unop.op)
			{
			case '++': stream << "++"; break;
			case '--': stream << "--"; break;
			default: ASSERT(0);
			}
			stream << ")";
		}
		break;

	case Expression::A_UNOP:
		{
			stream << "(";
			switch (exp->unop.op)
			{
			case '!': stream << "!"; break;
			case '-': stream << "-"; break;
			case '+': stream << "+"; break;
			case '*': stream << "*"; break;
			case '&': stream << "&"; break;
			case '~': stream << "~"; break;
			case '++': stream << "++"; break;
			case '--': stream << "--"; break;
			case '::': stream << "::"; break;
			default: ASSERT(0);
			}
			WriteToStream(stream, exp->unop.exp);
			stream << ")";
		}
		break;

	case Expression::A_BINOP:
		{
			stream << "(";
			if (exp->binop.op == '::')
			{
				WriteId(stream, exp);
			}
			else if (exp->binop.op == '[')
			{
				WriteToStream(stream, exp->binop.left);
				stream << "[";
				WriteToStream(stream, exp->binop.right);
				stream << "]";
			}
			else if (exp->binop.op == '.')
			{
				WriteToStream(stream, exp->binop.left);
				stream << ".";
				WriteId(stream, exp->binop.right);
			}
			else if (exp->binop.op == '->')
			{
				WriteToStream(stream, exp->binop.left);
				stream << "->";
				WriteId(stream, exp->binop.right);
			}
			else if (exp->binop.op == '?')
			{
				ASSERT(exp->binop.right->GetKind() == Expression::A_BINOP);
				ASSERT(exp->binop.right->binop.op == ':');

				WriteToStream(stream, exp->binop.left);
				stream << "?";
				WriteToStream(stream, exp->binop.right->binop.left);
				stream << ":";
				WriteToStream(stream, exp->binop.right->binop.right);
			}
			else
			{
				WriteToStream(stream, exp->binop.left);

				switch (exp->binop.op)
				{
				case '+': stream << "+"; break;
				case '-': stream << "-"; break;
				case '*': stream << "*"; break;
				case '/': stream << "/"; break;
				case '%': stream << "%"; break;
				case '|': stream << "|"; break;
				case '&': stream << "&"; break;
				case '^': stream << "^"; break;
				case '==': stream << "=="; break;
				case '!=': stream << "!="; break;
				case '<': stream << "<"; break;
				case '>': stream << ">"; break;
				case '<=': stream << "<="; break;
				case '>=': stream << ">="; break;
				case '<<': stream << "<<"; break;
				case '>>': stream << ">>"; break;
				case '||': stream << "||"; break;
				case '&&': stream << "&&"; break;

				case '=': stream << "="; break;
				case '+=': stream << "+="; break;
				case '-=': stream << "-="; break;
				case '*=': stream << "*="; break;
				case '/=': stream << "/="; break;
				case '%=': stream << "%="; break;
				case '|=': stream << "|="; break;
				case '&=': stream << "&="; break;
				case '^=': stream << "^="; break;
				case '<<=': stream << "<<="; break;
				case '>>=': stream << ">>="; break;
				case ',':	stream << ",";	break;

				default: ASSERT(0);
				}
				WriteToStream(stream, exp->binop.right);
			}

			stream << ")";
		}
		break;

	default:
		ASSERT(0);
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, Condition* cond)
{
	if (cond->m_declspecList)
	{
		WriteToStream(stream, cond->m_declspecList);
		WriteToStream(stream, cond->m_declarator);
	}

	WriteToStream(stream, cond->m_exp);

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_Stm* stm)
{
	if (stm == NULL)
	{
		stream << ";";
		return stream;
	}

	switch (stm->GetKind())
	{
	case A_Stm::A_COMPOUND:
		{
			CompoundStm* compoundstm = static_cast<CompoundStm*>(stm);

			stream << "{\n";
			WriteToStream(stream, compoundstm->m_stmList);
			stream << "}\n";
		}
		break;

	case A_Stm::A_DECLARATION:
		{
			A_DeclarationStm* declstm = (A_DeclarationStm*)stm;

			WriteToStream(stream, declstm->m_declaration);
			stream << ";\n";
		}
		break;

	case A_Stm::A_EXP:
		{
			A_ExpStm* expstm = (A_ExpStm*)stm;

			WriteToStream(stream, expstm->m_exp);

			stream << ";\n";
		}
		break;

	case A_Stm::A_IF:
		{
			IfStm* ifstm = static_cast<IfStm*>(stm);

			stream << "if (";

			Condition* cond = (Condition*)ifstm->m_cond;

			WriteToStream(stream, cond);

			stream << ")\n";

			WriteToStream(stream, ifstm->m_stm);

			if (ifstm->m_elseStm)
			{
				stream << "else\n";
				WriteToStream(stream, ifstm->m_elseStm);
			}
		}
		break;

	case A_Stm::A_RETURN:
		{
			ReturnStm* returnstm = static_cast<ReturnStm*>(stm);

			stream << "return";
			if (returnstm->m_exp)
			{
				stream << " ";
				WriteToStream(stream, (Expression*)returnstm->m_exp);
			}
			stream << ";\n";
		}
		break;

	case A_Stm::A_WHILE:
		{
			WhileStm* whilestm = static_cast<WhileStm*>(stm);

			stream << "while (";

			Condition* cond = (Condition*)whilestm->m_cond;

			WriteToStream(stream, cond);

			stream << ")\n";

			WriteToStream(stream, whilestm->m_stm);
		}
		break;

	case A_Stm::A_DOWHILE:
		{
			DoWhileStm* dowhilestm = static_cast<DoWhileStm*>(stm);

			stream << "do\n";
			WriteToStream(stream, dowhilestm->m_stm);
			stream << "\nwhile ";
			stream << "(";
			WriteToStream(stream, (Expression*)dowhilestm->m_exp);
			stream << ");\n";
		}
		break;

	case A_Stm::A_FOR:
		{
			ForStm* forstm = static_cast<ForStm*>(stm);

			A_ExpOrDecl* init = (A_ExpOrDecl*)forstm->m_init;

			stream << "for (";
			if (init)
			{
				if (init->m_exp)
					WriteToStream(stream, init->m_exp);
				else
					WriteToStream(stream, init->m_decl);
			}

			stream << ";";

			if (forstm->m_cond)
			{
				WriteToStream(stream, (Expression*)forstm->m_cond);
			}

			stream << ";";

			if (forstm->m_exp)
			{
				WriteToStream(stream, (Expression*)forstm->m_exp);
			}

			stream << ")\n";
			WriteToStream(stream, forstm->m_stm);
		}
		break;

	case A_Stm::A_LABEL:
		{
			LabelStm* labelstm = static_cast<LabelStm*>(stm);

			stream << String(labelstm->m_name) << ":\n";
			WriteToStream(stream, labelstm->m_stm);
		}
		break;

	case A_Stm::A_SWITCH:
		{
			SwitchStm* switchstm = static_cast<SwitchStm*>(stm);

			stream << "switch(";

			Condition* cond = (Condition*)switchstm->m_cond;

			WriteToStream(stream, cond);

			stream << ")\n";

			WriteToStream(stream, switchstm->m_stm);
		}
		break;

	case A_Stm::A_CASE:
		{
			CaseStm* casestm = static_cast<CaseStm*>(stm);

			stream << "case ";
			WriteToStream(stream, (Expression*)casestm->m_exp);
			stream << ":\n";
			WriteToStream(stream, casestm->m_stm);
		}
		break;

	case A_Stm::A_DEFAULT:
		{
			DefaultStm* defaultstm = static_cast<DefaultStm*>(stm);

			stream << "default:\n";
			WriteToStream(stream, defaultstm->m_stm);
		}
		break;

	case A_Stm::A_GOTO:
		{
			GotoStm* gotostm = static_cast<GotoStm*>(stm);

			stream << "goto " << gotostm->m_name << ";\n";
		}
		break;

	case A_Stm::A_BREAK:
		{
			stream << "break;\n";
		}
		break;

	case A_Stm::A_CONTINUE:
		{
			stream << "continue;\n";
		}
		break;

	default:
		ASSERT(0);
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_StmList* stmList)
{
	while (stmList)
	{
		WriteToStream(stream, stmList->head);
		stmList = stmList->tail;
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, FunDefDecl* fundef)
{
	WriteToStream(stream, fundef->m_declspec);
	WriteToStream(stream, fundef->m_declarator);

	if (fundef->m_ctor_initializer)
	{
		stream << ":";

		ExpressionList* expList = fundef->m_ctor_initializer;
		while (expList)
		{
			ASSERT(0);
			/*
			WriteId(stream, expList->head->call.left);
			stream << "(";
			WriteToStream(stream, expList->head->call.args);
			stream << ")";
			*/

			expList = expList->tail;
			if (expList) stream << ",";
		}
	}

	stream << "\n";
	stream << "{\n";
	WriteToStream(stream, fundef->m_body->m_stmList);
	stream << "}\n";

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_TypeId* typeId)
{
	WriteToStream(stream, typeId->m_declspecList);
	if (typeId->m_declarator) WriteToStream(stream, typeId->m_declarator);
	//if (typeId->m_def) Write(typeId->m_def);	// hm..

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, InitDeclaratorList* dlist)
{
	while (dlist)
	{
		if (dlist->head)	// TODO remove
			WriteToStream(stream, dlist->head);

		dlist = dlist->tail;
		if (dlist) stream << ",";
	}

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_SimpleDeclaration* simple)
{
	WriteToStream(stream, simple->m_declspec);
	InitDeclaratorList* dlist = simple->m_declaratorList;
//		fprintf(outfile, ";\n");
	WriteToStream(stream, dlist);

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, ast::Declaration* d)
{
	if (d->GetKind() == ast::Declaration::A_FUNDEF)
	{
		FunDefDecl* fundef = (FunDefDecl*)d;

		WriteToStream(stream, fundef);
	}
	else if (d->GetKind() == ast::Declaration::A_TEMPLATE)
	{
		TemplateDeclaration* td = (TemplateDeclaration*)d;

		stream << "template<";

		ast::TemplateParameterList* paramlist = td->m_params;
		while (paramlist)
		{
			ast::TemplateParameter* param = paramlist->head;

			switch (param->GetKind())
			{
			case ast::TemplateParameter::A_ParamType:
				{
					ast::TypeTemplateParameter* typeparam = (ast::TypeTemplateParameter*)param;

					stream << "class " << typeparam->m_id;

					if (typeparam->m_typeId)
					{
						stream << "=";
						WriteToStream(stream, typeparam->m_typeId);
					}
				}
				break;

			case ast::TemplateParameter::A_ParamDeclarator:
				{
					ast::DeclaratorTemplateParameter* declparam = (ast::DeclaratorTemplateParameter*)param;

					WriteToStream(stream, declparam->m_decls);
					if (declparam->m_declarator) WriteToStream(stream, declparam->m_declarator);
				}
				break;

			default:
				ASSERT(0);
			}

			paramlist = paramlist->tail;
			if (paramlist) stream << ",";
		}

		stream << "> ";

		if (td->m_decl->GetKind() == ast::Declaration::A_SIMPLE)
		{
			WriteToStream(stream, static_cast<A_SimpleDeclaration*>(td->m_decl));
			stream << ";\n";
		}
		else if (td->m_decl->GetKind() == ast::Declaration::A_FUNDEF)
		{
			WriteToStream(stream, static_cast<FunDefDecl*>(td->m_decl));
		}
		else
			ASSERT(0);
	}
	else if (d->GetKind() == ast::Declaration::A_SIMPLE)
	{
		A_SimpleDeclaration* simple = static_cast<A_SimpleDeclaration*>(d);

		WriteToStream(stream, simple);
	//	fprintf(outfile, ";\n");
	}
	else if (d->GetKind() == ast::Declaration::A_EXTERN_LINKAGE)
	{
		LinkageDeclaration* ld = static_cast<LinkageDeclaration*>(d);

		stream << "extern " << doublequote(ld->m_linkage) << "\n" << "{" << "\n";

		WriteToStream(stream, ld->m_declarationList);

		stream << "}\n";
	}
	else if (d->GetKind() == Declaration::A_NAMESPACE)
	{
		NamespaceDefinition* nsd = static_cast<NamespaceDefinition*>(d);

		stream << "namespace " << nsd->m_name << "\n{\n";

		WriteToStream(stream, nsd->m_declarationList);

		stream << "}\n";
	}
#if 0
	else if (d->GetKind() == A_Declaration::A_USING_DIRECTIVE)
	{
		A_UsingDirectiveDeclaration* directive = (A_UsingDirectiveDeclaration*)d;

		Scope* pScope2 = GetNestedScope(pGlobal, NULL, pScope, directive->m_name);
		ASSERT(pScope2);
		ASSERT(pScope2->m_pNamespace);

		ASSERT(pScope2 != pScope);

		pScope->m_using_directives.push_back(pScope2->m_pNamespace);
	}
	else
	{
		ASSERT(0);
	}
#endif

	return stream;
}

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, ast::DeclarationList* declarationList)
{
//	declarationList = Reverse(declarationList);	// TODO, not here

	ast::DeclarationList* dl = declarationList;
	while (dl)
	{
		ast::Declaration* d = dl->head;

		if (d == NULL)
		{
			dl = dl->tail;
			continue;
		}

		WriteToStream(stream, d);
		if (d->GetKind() == ast::Declaration::A_SIMPLE)
		{
			stream << ";\n";
		}

		dl = dl->tail;
	}

	return stream;
}

}	// ast
}	// cpp
}	// System
