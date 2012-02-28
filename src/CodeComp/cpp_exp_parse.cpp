#include "StdAfx.h"
#include "Comp2.h"
#include "preprocessor.h"
#include "cpp_ast.h"
#include "cpp_compile.h"
#include "cpp_translate.h"	// TODO, not here ?

#include "ir.h"	// TODO, not here ?

namespace System
{
using namespace std;

LFCEXT Type* GetType(ClassType* pClass, StringIn name);

extern PP::CPreprocessor* pPP2;
extern kwmap kwm;

namespace cpp
{

_Ptr<IO::TextWriter> m_outputStream;

_Ptr<IO::TextWriter> serror()
{
	return m_outputStream;
}

namespace ast
{

#include "cpp_exp_parse.tab.h"
#include "cpp_exp_parse.tab.c"

System::TemplateParams* /*Array<System::TemplateParameter*, System::__gc_allocator>*/ templateParams;
extern CGlobal* g_pGlobal;
extern System::Scope* g_pScope;
extern System::Scope* g_pScope2;
//extern System::Scope* g_pScope1;
	//extern Scope* g_pLastScope;

	ClassType* g_pClass;

//System::Scope* g_pScope;

	int cpp_exp_parse();

	extern ast::A_ExpOrDecl* m_g_exp_or_decl;

	extern ast::Expression2List* ptoken;

	static CDeclaratorList* SimpleDeclaration(ast::A_SimpleDeclaration* d, CGlobal* pGlobal, Scope* pScope, Declarator* fun, ClassType* pInnermostClass, Scope* pTScope/*ast::A_TemplateParameterList * tp, bool bInsideTemplate*/);

CodeCompExt ast::A_ExpOrDecl* PrimList(ast::Expression2List* primlist, Scope* pGlobalScope, Scope* pScope)
{
//	ptoken = flatten_and_reverse(primlist, NULL);
	ptoken = primlist;

//	g_pLastScope = pGlobalScope;
	g_pScope = pScope;
//	g_pScope1 = pScope;
	g_pScope2 = pScope;
	//g_scopeStack.push_back(pScope);

	m_g_exp_or_decl = NULL;

	int error = cpp_exp_parse();
	ASSERT(error == 0);

	ASSERT((long)m_g_exp_or_decl != 0xcccccccc);

	ast::A_ExpOrDecl* expordecl = m_g_exp_or_decl;

//	ASSERT(g_scopeStack.size() == 1);
//	g_scopeStack.pop();

	return expordecl;
}

static ArrayType* parse_newArrayType(CGlobal* pGlobal, Type* elemType, int nSize)
{
	System::ArrayOf arrayof;
	arrayof.m_elemType = elemType;
	arrayof.m_nSize = nSize;

	map<ArrayOf, ArrayType*, less<ArrayOf>, __gc_allocator>::iterator it = pGlobal->m_array_Types.find(arrayof);
	if (it != pGlobal->m_array_Types.end())
	{
		return (*it).second;
	}
	else
	{
		ArrayType* type = new ArrayType(elemType, nSize);
		pGlobal->m_array_Types.insert(map<ArrayOf, ArrayType*>::value_type(arrayof, type));

		return type;
	}
}

Scope* Extract(Declarator* pDeclarator, ast::A_DirectDeclarator* directDeclarator, Type* pType, Scope* pScope, Scope* pTScope, CGlobal* pGlobal)
{
	ASSERT(pGlobal);

	if (directDeclarator->kind == ast::A_DirectDeclarator::A_DECLARATOR_ID)
	{
		if (directDeclarator->u.declaratorId == NULL)	// TODO, remove this
		{
			return NULL;
		}

//		if (directDeclarator->u.declaratorId->kind == ast::Expression::ast::A_ID)
		ASSERT(directDeclarator->u.declaratorId->kind == ast::Expression::A_BINOP);

		if (directDeclarator->u.declaratorId->kind == ast::Expression::A_BINOP/* && directDeclarator->u.declaratorId->binop.left->kind == ast::Expression::ast::A_TEMPLATEID*/)
		{
			if (directDeclarator->u.declaratorId->binop.right)
			{
				Scope* pScope2 = parse_LookupScopeNameRecurse(pScope, directDeclarator->u.declaratorId->binop.left->templateid.id);
				ASSERT(pScope2);

				ast::Expression* exp = directDeclarator->u.declaratorId->binop.right;
				while (exp->binop.right)
				{
					pScope2 = parse_LookupScopeName(pScope2, exp->binop.left->templateid.id);
					ASSERT(pScope2);

					exp = exp->binop.right;
				}

				if (exp->binop.left->kind == ast::Expression::A_TEMPLATEID)
				{
					declsmap::iterator it = pScope2->m_decls.find(exp->binop.left->templateid.id);
					ASSERT(it != pScope2->m_decls.end());

					pDeclarator->m_name = exp->binop.left->templateid.id;
				}
				else if (exp->binop.left->kind == ast::Expression::A_UNOP)
				{
					VERIFY(exp->binop.left->unop.exp->kind == ast::Expression::A_TEMPLATEID);

				//	StringBuilder strbuilder;
				//	strbuilder << "~" << String(exp->binop.left->unop.exp->templateid.id);

					pDeclarator->m_name = "~" + String(exp->binop.left->unop.exp->templateid.id);//strbuilder.str();//*new StringA("~") + *directDeclarator->u.declaratorId->unop.exp->templateid.id;
				}
				else if (exp->binop.left->kind == ast::Expression::A_OPERATOR)
				{
					switch (exp->binop.left->u._operator)
					{
					case 'new':
						pDeclarator->m_name = "operator_new";
						break;

					case 'del':
						pDeclarator->m_name = "operator_delete";
						break;

					case '+':
						pDeclarator->m_name = "operator_add";
						break;

					case '-':
						pDeclarator->m_name = "operator_minus";
						break;

					case '*':
						pDeclarator->m_name = "operator_mul";
						break;

					case '/':
						pDeclarator->m_name = "operator_divide";
						break;

					case '%':
						pDeclarator->m_name = "operator_remainder";
						break;

					case '|':
						pDeclarator->m_name = "operator_or";
						break;

					case '&':
						pDeclarator->m_name = "operator_and";
						break;

					case '^':
						pDeclarator->m_name = "operator_xor";
						break;

					case '<<':
						pDeclarator->m_name = "operator_lshift";
						break;

					case '>>':
						pDeclarator->m_name = "operator_rshift";
						break;

					case '++':
						pDeclarator->m_name = "operator_increment";
						break;

					case '--':
						pDeclarator->m_name = "operator_decrement";
						break;

					case '->':
						pDeclarator->m_name = "operator_arrow";
						break;

					case '=':
						pDeclarator->m_name = "operator_assign";
						break;

					case '+=':
						pDeclarator->m_name = "operator_plus_assign";
						break;

					case '-=':
						pDeclarator->m_name = "operator_minus_assign";
						break;

					case '*=':
						pDeclarator->m_name = "operator_mul_assign";
						break;

					case '/=':
						pDeclarator->m_name = "operator_divide_assign";
						break;

					case '%=':
						pDeclarator->m_name = "operator_remainder_assign";
						break;

					case '|=':
						pDeclarator->m_name = "operator_or_assign";
						break;

					case '&=':
						pDeclarator->m_name = "operator_and_assign";
						break;

					case '^=':
						pDeclarator->m_name = "operator_xor_assign";
						break;

					case '<<=':
						pDeclarator->m_name = "operator_lshift_assign";
						break;

					case '>>=':
						pDeclarator->m_name = "operator_rshift_assign";
						break;

					case '==':
						pDeclarator->m_name = "operator_equals";
						break;

					case '!=':
						pDeclarator->m_name = "operator_not_equals";
						break;

					case '>':
						pDeclarator->m_name = "operator_gt";
						break;

					case '<':
						pDeclarator->m_name = "operator_lt";
						break;

					case '>=':
						pDeclarator->m_name = "operator_geq";
						break;

					case '<=':
						pDeclarator->m_name = "operator_leq";
						break;

					case '[]':
						pDeclarator->m_name = "operator_array";
						break;

					case '()':
						pDeclarator->m_name = "operator_call";
						break;

					default:
						ASSERT(0);
					}
				}
				else
					ASSERT(0);

				return pScope2;
			}
			else
			{
				ast::Expression* exp = directDeclarator->u.declaratorId;

				if (exp->binop.left->kind == ast::Expression::A_TEMPLATEID)
				{
					pDeclarator->m_name = exp->binop.left->templateid.id;

					/*
					if (pDeclarator->m_name == "vector3d")
					{
						MessageBeep(-1);
					}
					*/
				}
				else if (exp->binop.left->kind == ast::Expression::A_UNOP)
				{
					VERIFY(exp->binop.left->unop.exp->kind == ast::Expression::A_TEMPLATEID);

					pDeclarator->m_name = "~" + String(exp->binop.left->unop.exp->templateid.id);
				}
				else if (exp->binop.left->kind == ast::Expression::A_CONVERSION)
				{
					pDeclarator->m_name = "conversion";
				}
				else if (exp->binop.left->kind == ast::Expression::A_OPERATOR)
				{
					switch (exp->binop.left->u._operator)
					{
					case 'new':
						pDeclarator->m_name = "operator_new";
						break;

					case 'del':
						pDeclarator->m_name = "operator_delete";
						break;

					case '+':
						pDeclarator->m_name = "operator_add";
						break;

					case '-':
						pDeclarator->m_name = "operator_minus";
						break;

					case '*':
						pDeclarator->m_name = "operator_mul";
						break;

					case '/':
						pDeclarator->m_name = "operator_divide";
						break;

					case '%':
						pDeclarator->m_name = "operator_remainder";
						break;

					case '|':
						pDeclarator->m_name = "operator_or";
						break;

					case '&':
						pDeclarator->m_name = "operator_and";
						break;

					case '^':
						pDeclarator->m_name = "operator_xor";
						break;

					case '<<':
						pDeclarator->m_name = "operator_lshift";
						break;

					case '>>':
						pDeclarator->m_name = "operator_rshift";
						break;

					case '++':
						pDeclarator->m_name = "operator_increment";
						break;

					case '--':
						pDeclarator->m_name = "operator_decrement";
						break;

					case '->':
						pDeclarator->m_name = "operator_arrow";
						break;

					case '=':
						pDeclarator->m_name = "operator_assign";
						break;

					case '+=':
						pDeclarator->m_name = "operator_plus_assign";
						break;

					case '-=':
						pDeclarator->m_name = "operator_minus_assign";
						break;

					case '*=':
						pDeclarator->m_name = "operator_mul_assign";
						break;

					case '/=':
						pDeclarator->m_name = "operator_divide_assign";
						break;

					case '%=':
						pDeclarator->m_name = "operator_remainder_assign";
						break;

					case '|=':
						pDeclarator->m_name = "operator_or_assign";
						break;

					case '&=':
						pDeclarator->m_name = "operator_and_assign";
						break;

					case '^=':
						pDeclarator->m_name = "operator_xor_assign";
						break;

					case '<<=':
						pDeclarator->m_name = "operator_lshift_assign";
						break;

					case '>>=':
						pDeclarator->m_name = "operator_rshift_assign";
						break;

					case '==':
						pDeclarator->m_name = "operator_equals";
						break;

					case '!=':
						pDeclarator->m_name = "operator_not_equals";
						break;

					case '>':
						pDeclarator->m_name = "operator_gt";
						break;

					case '<':
						pDeclarator->m_name = "operator_lt";
						break;

					case '>=':
						pDeclarator->m_name = "operator_geq";
						break;

					case '<=':
						pDeclarator->m_name = "operator_leq";
						break;

					case '[]':
						pDeclarator->m_name = "operator_array";
						break;

					case '()':
						pDeclarator->m_name = "operator_call";
						break;

					case '!':
						pDeclarator->m_name = "operator_not";
						break;

					case '~':
						pDeclarator->m_name = "operator_complement";
						break;

					default:
						{
							IO::StringWriter writer;
							writer << __FILE__ << "(" << __LINE__ << ")" << "INTERNAL ERROR : unknown operator";
							raise(Exception(writer.str()));
						}
					}
				}
				else
					VERIFY(0);

				return pScope;
			}
#if 0
			pDeclarator->m_location.m_line = directDeclarator->line_pos;
#endif
		}
#if 0
		else if (directDeclarator->u.declaratorId->kind == ast::Expression::ast::A_UNOP)
		{
			VERIFY(directDeclarator->u.declaratorId->unop.exp->kind == ast::Expression::ast::A_ID);

			BufferImp<char> buffer;
			StringBuilderA strbuilder(&buffer);
			strbuilder << "~" << *directDeclarator->u.declaratorId->unop.exp->templateid.id;

			pDeclarator->m_name = buffer.DetachToString();//*new StringA("~") + *directDeclarator->u.declaratorId->unop.exp->templateid.id;
			return pScope;
		}
		else if (directDeclarator->u.declaratorId->kind == ast::Expression::ast::A_OPERATOR)
		{
			//pDeclarator->m_name = "operator_";

			switch (directDeclarator->u.declaratorId->_operator)
			{
			case 'new':
				pDeclarator->m_name = new StringA("operator_new");
				break;

			case 'del':
				pDeclarator->m_name = new StringA("operator_delete");
				break;

			case '+':
				pDeclarator->m_name = new StringA("operator_add");
				break;

			case '-':
				pDeclarator->m_name = new StringA("operator_minus");
				break;

			case '*':
				pDeclarator->m_name = new StringA("operator_mul");
				break;

			case '/':
				pDeclarator->m_name = new StringA("operator_divide");
				break;

			case '%':
				pDeclarator->m_name = new StringA("operator_remainder");
				break;

			case '|':
				pDeclarator->m_name = new StringA("operator_or");
				break;

			case '&':
				pDeclarator->m_name = new StringA("operator_and");
				break;

			case '^':
				pDeclarator->m_name = new StringA("operator_xor");
				break;

			case '<<':
				pDeclarator->m_name = new StringA("operator_lshift");
				break;

			case '>>':
				pDeclarator->m_name = new StringA("operator_rshift");
				break;

			case '++':
				pDeclarator->m_name = new StringA("operator_increment");
				break;

			case '--':
				pDeclarator->m_name = new StringA("operator_decrement");
				break;

			case '->':
				pDeclarator->m_name = new StringA("operator_arrow");
				break;

			case '=':
				pDeclarator->m_name = new StringA("operator_assign");
				break;

			case '+=':
				pDeclarator->m_name = new StringA("operator_plus_assign");
				break;

			case '-=':
				pDeclarator->m_name = new StringA("operator_minus_assign");
				break;

			case '*=':
				pDeclarator->m_name = new StringA("operator_mul_assign");
				break;

			case '/=':
				pDeclarator->m_name = new StringA("operator_divide_assign");
				break;

			case '%=':
				pDeclarator->m_name = new StringA("operator_remainder_assign");
				break;

			case '|=':
				pDeclarator->m_name = new StringA("operator_or_assign");
				break;

			case '&=':
				pDeclarator->m_name = new StringA("operator_and_assign");
				break;

			case '^=':
				pDeclarator->m_name = new StringA("operator_xor_assign");
				break;

			case '<<=':
				pDeclarator->m_name = new StringA("operator_lshift_assign");
				break;

			case '>>=':
				pDeclarator->m_name = new StringA("operator_rshift_assign");
				break;

			case '==':
				pDeclarator->m_name = new StringA("operator_equals");
				break;

			case '!=':
				pDeclarator->m_name = new StringA("operator_not_equals");
				break;

			case '>':
				pDeclarator->m_name = new StringA("operator_gt");
				break;

			case '<':
				pDeclarator->m_name = new StringA("operator_lt");
				break;

			case '>=':
				pDeclarator->m_name = new StringA("operator_geq");
				break;

			case '<=':
				pDeclarator->m_name = new StringA("operator_leq");
				break;

			case '[]':
				pDeclarator->m_name = new StringA("operator_array");
				break;

			case '()':
				pDeclarator->m_name = new StringA("operator_call");
				break;

			default:
				ASSERT(0);
			}

			return pScope;	// ??
		}
#endif
		else if (directDeclarator->u.declaratorId->kind == ast::Expression::A_CONVERSION)
		{
			ASSERT(0);
#if 0
			CDeclarator* pDecl2 = new CDeclarator;
			pDecl2->m_pType = GetType(directDeclarator->u.declaratorId->conversion->declspecList, pGlobal, pScope, NULL, false);
			directDeclarator->u.declaratorId->conversion->declarator->Extract(pDecl2, pDecl2->m_pType, pScope, pGlobal);

			BufferImp<char> buffer;
			StringBuilderA strbuilder(&buffer);
			strbuilder << "operator_";
			pDecl2->m_pType->Write(strbuilder);
			pDeclarator->m_name = buffer.DetachToString();
#endif
		}
		else if (directDeclarator->u.declaratorId->kind == ast::Expression::A_BINOP)
		{
			// TODO ??
#if 0
			Scope* pScope2 = GetNestedScope(NULL/*pGlobal*/, pScope, directDeclarator->u.declaratorId->binop.left);
			if (pScope2 == NULL)
				return NULL;

			Type* pType = pScope2->GetType(directDeclarator->u.declaratorId->binop.right->id);

			return pScope2;
#endif
		//	ASSERT(0);
		//	return NULL;
		}
		else
			ASSERT(0);
	}
	else if (directDeclarator->kind == ast::A_DirectDeclarator::A_DIRECT_DECLARATOR)
	{
		if (directDeclarator->u.directDeclarator.kind == ast::A_DirectDeclarator::_u::_directDeclarator::A_PAREN)
		{
			FunctionType* pType = new FunctionType;
		//	pType->AddRef();

			pType->m_pReturnType = pDeclarator->m_pType;
			/*
			if (pType->m_pReturnType)
			{
				((Type*)pType->m_pReturnType)->AddRef();
			}
			*/

			ast::DeclSpecList* decls = directDeclarator->u.directDeclarator.decls;
			while (decls)
			{
				if (decls->head->GetKind() == ast::A_DeclSpec::A_TYPE_MODIFIER)
				{
					if (((ast::A_DeclSpecModifier*)decls->head)->m_modifier == ast::A_CONST)
					{
						if (pType->m_bConst)
						{
							Std::Out << ("const already specified\n");
						}
						pType->m_bConst = true;
					}
				}

				decls = decls->tail;
			}

			ast::ParameterDeclarations* paramDecls = directDeclarator->u.directDeclarator.paramDecls;
			ASSERT(paramDecls);

		//	paramDecls->params = Reverse(paramDecls->params);

			pType->m_stackSize = 0;

			ast::A_TypeIdList* params = paramDecls->params;
			while (params)
			{
			//	ASSERT(0);
#if 0
				CDeclarator* pDeclarator = new CDeclarator;
				pDeclarator->m_pType = GetType(params->head->declspecList, pGlobal, pScope, pTScope);//NULL/*tp*/, bInsideTemplate);
				/*
				if (pDeclarator->m_pType == NULL)
				{
					ASSERT(0);
					return NULL;
				}*/

				params->head->declarator->Extract(pDeclarator, pDeclarator->m_pType, pScope, pTScope, pGlobal);
				//pType->m_parameters.m_parameters.InsertAt(0/*pType->m_parameters.begin()*/, pDeclarator);
				pType->m_parameters.m_parameters.push_back(pDeclarator);

				pType->m_stackSize += 4;

#endif
				params = params->tail;
			}

			pType->m_parameters.m_bVarArg = paramDecls->varArgs;

			pDeclarator->m_pType = pType;
			return Extract(pDeclarator, directDeclarator->u.directDeclarator.directDeclarator, pType, pScope, pTScope, pGlobal);
		}
		else if (directDeclarator->u.directDeclarator.kind == ast::A_DirectDeclarator::_u::_directDeclarator::A_ARRAY)	// array
		{
			int nSize;

			if (directDeclarator->u.directDeclarator.array)
			{
				nSize = directDeclarator->u.directDeclarator.array->u.int32;	// TODO
			}
			else
			{
				nSize = 0;//-1;	// empty array at end of struct means 0 size.. hm..
			}

			ArrayType* array = parse_newArrayType(pGlobal, pDeclarator->m_pType, nSize);
			//pArray->AddRef();

			//pArray->m_pElemType = pDeclarator->m_pType;

		//	pArray->m_sizeof = pArray->m_pElemType->get_sizeof() * pArray->m_nSize;

			// TODO
			pDeclarator->m_pType = array;
			if (directDeclarator->u.directDeclarator.directDeclarator)
		//	ASSERT(directDeclarator->u.directDeclarator.directDeclarator);
				return Extract(pDeclarator, directDeclarator->u.directDeclarator.directDeclarator, array, pScope, pTScope, pGlobal);
			else
				return pScope;	// ??
		}
		else
			ASSERT(0);
	}
	else if (directDeclarator->kind == ast::A_DirectDeclarator::A_DECLARATOR)
	{
		return directDeclarator->u.declarator->Extract(pDeclarator, pType, pScope, pTScope, pGlobal);
	}
	else
	{
		ASSERT(0);
	}

	return NULL;
}

Scope* ast::A_Declarator::Extract(Declarator* pDeclarator, Type* pType, Scope* pScope, Scope* pTScope, CGlobal* pGlobal)
{
	ASSERT(pGlobal);

	if (this == NULL)
		return pScope;

//	if (pType == NULL)
//	return NULL;

	if (typeid(*this) == typeid(ast::A_BitfieldDeclarator))//kind == ast::A_Declarator::ast::A_DIRECT_DECLARATOR)
	{
		pDeclarator->m_name = ((ast::A_BitfieldDeclarator*)this)->m_id->binop.left->templateid.id;
		return pScope;
	}
	else if (typeid(*this) == typeid(ast::A_DirectDeclaratorDeclarator))//kind == ast::A_Declarator::ast::A_DIRECT_DECLARATOR)
	{
		return cpp::ast::Extract(pDeclarator, ((ast::A_DirectDeclaratorDeclarator*)this)->m_directDeclarator, pType, pScope, pTScope, pGlobal);
	}
	else if (typeid(*this) == typeid(ast::A_PtrDeclarator))//kind == ast::A_PTR)
	{
		Scope* pScope2 = ((ast::A_PtrDeclarator*)this)->m_declarator->Extract(pDeclarator, pType, pScope, pTScope, pGlobal);
		if (pDeclarator->m_pType->get_Kind() == type_function)
		{
			Type* pType;
			if (((ast::A_PtrDeclarator*)this)->m_type == '*')
				pType = new PointerType(pDeclarator->m_pType->AsFunction()->m_pReturnType);
			else
				pType = new ReferenceType(pDeclarator->m_pType->AsFunction()->m_pReturnType);

			pDeclarator->m_pType->AsFunction()->m_pReturnType = pType;
		}
		else
		{
			if (((ast::A_PtrDeclarator*)this)->m_type == '*')
			{
				PointerTypes::iterator it = pGlobal->m_pointer_Types.find(pDeclarator->m_pType);
				if (it != pGlobal->m_pointer_Types.end())
				{
					pDeclarator->m_pType = (*it).second;
				}
				else
				{
					PointerType* type = new PointerType(pDeclarator->m_pType);;
					pGlobal->m_pointer_Types.insert(PointerTypes::value_type(pDeclarator->m_pType, type));

					pDeclarator->m_pType = type;
				}
			}
			else if (((ast::A_PtrDeclarator*)this)->m_type == '&')
			{
				ReferenceTypes::iterator it = pGlobal->m_reference_Types.find(pDeclarator->m_pType);
				if (it != pGlobal->m_reference_Types.end())
				{
					pDeclarator->m_pType = (*it).second;
				}
				else
				{
					ReferenceType* type = new ReferenceType(pDeclarator->m_pType);;
					pGlobal->m_reference_Types.insert(ReferenceTypes::value_type(pDeclarator->m_pType, type));

					pDeclarator->m_pType = type;
				}
			}
			else if (((ast::A_PtrDeclarator*)this)->m_type == '.*')
			{
				// doesn't matter ?? ideally, we shouldn't even do type semantics here

				PointerTypes::iterator it = pGlobal->m_pointer_Types.find(pDeclarator->m_pType);
				if (it != pGlobal->m_pointer_Types.end())
				{
					pDeclarator->m_pType = (*it).second;
				}
				else
				{
					PointerType* type = new PointerType(pDeclarator->m_pType);;
					pGlobal->m_pointer_Types.insert(PointerTypes::value_type(pDeclarator->m_pType, type));

					pDeclarator->m_pType = type;
				}
			}
			else if (((ast::A_PtrDeclarator*)this)->m_type == 0)	// cc_qualifier
			{
			}
			else
			{
				Std::Out << m_filename << "(" << m_line_pos << ")" << " : INTERNAL ERROR at " << __FILE__ << "(" << __LINE__ << ")" << endl;
				++pGlobal->m_errors;
			}
		}

		return pScope2;
	}
	else
		ASSERT(0);

	return NULL;
}

ClassType* parse_CreateClassInstance(CGlobal* pGlobal, ClassType* pTemplateClass, Scope* pScope, ast::A_TemplateArgumentList * params2)
{
	ASSERT(pTemplateClass->m_pInstantiatedFromArgs == NULL);

	ClassType* pTType = new ClassType;
//	pTType->m_ownerDecl = new Declarator;
	pTType->m_pInstantiatedFromArgs = new TemplatedClassArgs;
	pTType->m_pInstantiatedFromClass = pTemplateClass->AsClass();
#if 0
	pTType->m_pInstantiatedFromArgs->m_pClass = pTemplateClass->GetClass();
#endif

#if 0
	ast::A_TemplateParameterList* params = NULL;//pTemplateClass->GetClass()->m_templateArgs;

	ast::A_TemplateArgumentList* typeIds2 = params2;
	/*
	{

		ast::A_TemplateArgumentList* typeIds = params2;
		while (typeIds)
		{
			typeIds2 = new ast::A_TemplateArgumentList(typeIds->head, typeIds2);
			typeIds = typeIds->tail;
		}
	}
	*/

	int i = 0;
	ast::A_TemplateArgumentList* typeIds = typeIds2;
	while (typeIds)
	{
		ast::A_TemplateArgument* typeId = typeIds->head;

		TemplateParameter* param = pTemplateClass->GetClass()->m_items[i];
		if (param->m_kind == TemplateParameter::Param_Type)
		{
		//	ASSERT(typeid(*typeId->m_pTypeId) == typeid(ast::A_TypeId));
		//	ASSERT(typeid(*typeId->m_pTypeId->declspecList) == typeid(ast::DeclSpecList));

#if 1

			//_TemplateArgType* param
			Type* pTemplateArgType = GetType(typeId->m_pTypeId->declspecList, pGlobal, pScope, pScope);//NULL/*tp*/, false/*bInsideTemplate*/);
			//pTemplateArgType->
			{
				CDeclarator* pDeclarator = new CDeclarator;
				pDeclarator->m_pType = pTemplateArgType;
				/*Scope* p =*/ typeId->m_pTypeId->declarator->Extract(pDeclarator, pDeclarator->m_pType, pScope/*pTScope*//*pScope*/, pGlobal);
				pTemplateArgType = pDeclarator->m_pType;
				delete pDeclarator;
			}

			TemplatedClassArg* p = new TemplatedClassArg;
			p->m_pType = pTemplateArgType;

			pTType->m_pInstantiatedFromArgs->m_templateArgs.push_back(p);
#endif
		}
		else
		{
			Tr_Exp* exp = TransExpression(NULL/*T_Declarator* frame*/, typeId->m_pExp, pGlobal, pScope);
			ASSERT(exp);
			long value = Evaluate(exp->ex);

			TemplatedClassArg* p = new TemplatedClassArg;
			p->m_pType = NULL;
			p->m_value = value;

			pTType->m_pInstantiatedFromArgs->m_templateArgs.push_back(p);
		}

		typeIds = typeIds->tail;
		i++;
	}

	for (; i < pTemplateClass->GetClass()->m_items.GetSize(); i++)
	{
		TemplateParameter* param = pTemplateClass->GetClass()->m_items[i];
		if (param->m_kind == TemplateParameter::Param_Type)
		{
			//__live_object_ptr<Type> pTemplateArgType = 

		//	TemplatedClassArg* p = new TemplatedClassArg;
		//	p->m_pType = ;

			pTType->m_pInstantiatedFromArgs->m_templateArgs.push_back(param->m_pType->m_defaultArg);
		}
		else
		{
			ASSERT(0);
		}
	}
	/*
	while (params)
	{
		ast::A_TemplateParameter* param = params->head;

		Type* pTemplateArgType = GetType(param->typeId->declspecList, pGlobal, pScope, tp, bInsideTemplate);
		pTType->m_templateArgs.InsertAt(0, pTemplateArgType);

		params = params->tail;
	}
	*/

#if 0
	if (!bInsideTemplate)
	{
		TemplateArgs templateArgs;
		templateArgs.m_args = pTType->m_templateArgs.GetData();
		templateArgs.m_parent = NULL;	// ?

		pType2 = InstantiateTemplate(pTType->m_pClass, templateArgs/*pTType->m_templateArgs.GetData()*/);
	}
	else
#endif

#endif
	{
//		pType2 = pTType;
		return pTType;
	}
}

void cpp_exp_error (char const *s)
{
	serror() << String(ast::cpp_exp_lloc.filename) << "(" << (ast::cpp_exp_lloc.first_line+1) << "," << (ast::cpp_exp_lloc.first_column+1) << ")" << " : error : " << s << "\n";
}

Type* parse_LookupTypeName(Scope* pScope, StringIn name)
{
	ASSERT(name.GetLength() > 0);

	if (pScope->m_pNamespace && pScope->m_pNamespace->AsClass())
	{
		Type* pType = System::GetType(pScope->m_pNamespace->AsClass(), name);
		if (pType)
			return pType;
	}
	else
	{
		typemap::const_iterator it = pScope->m_types.find(name);
		if (it != pScope->m_types.end())
		{
			return (*it).second;
		}
	}

	return NULL;
}

Type* parse_LookupTypeNameRecurse(Scope* pScope, StringIn name)
{
	Type* pType = parse_LookupTypeName(pScope, name);
	if (pType != NULL)
		return pType;

	if (pScope->m_pParentScope)
		return parse_LookupTypeNameRecurse(pScope->m_pParentScope, name);

	return NULL;
}

Scope* parse_LookupScopeNameRecurse(Scope* pScope, StringIn name);

Scope* parse_LookupScopeName(Scope* pScope, StringIn name)
{
	ASSERT(pScope != NULL);

	namespacemap::iterator ns_it = pScope->m_namespaces.find(name);
	if (ns_it != pScope->m_namespaces.end())
	{
		return (*ns_it).second->m_pScope;
	}

	/*
	Scope* pScope2 = NULL;
	for (int i = 0; i < pScope->m_using_directives.size(); i++)
	{
		Namespace* pNamespace = pScope->m_using_directives[i];
		Scope* pScope3 = LookupScopeNameRecurse(pNamespace->m_pScope, name);
		if (pScope3)
		{
			if (pScope2)
			{
				printf("ambiguous\n");
			}
			pScope2 = pScope3;
		}
	}
	if (pScope2)
		return pScope2;
		*/

	if (pScope->m_pNamespace && pScope->m_pNamespace->AsClass())
	{
		Type* pType = System::GetType(pScope->m_pNamespace->AsClass(), name);
		if (pType)
		{
			Type* pT = pType;
			pType = pType->GetStripped();
			if (pType)
			{
				if (pType->get_Kind() == type_class)
				{
					return ((ClassType*)pType)->m_pScope;
				}
				/*
				else if (pType->get_Kind() == type_templateinst)	// TODO: Should this happen ??
				{
					return ((ClassType*)pType)->m_pScope;
				}
				*/
			}
			else
			{
				MessageBeep(-1);
			//	printf("(%s)->GetStripped() == NULL at %s(%d)\n", pT->ToString()->begin(), ast::cpp_exp_lloc.filename->begin(), ast::cpp_exp_lloc.first_line);
			}
		}
	}
	else
	{
		typemap::iterator type_it = pScope->m_types.find(name);
		if (type_it != pScope->m_types.end())
		{
			Type* pType = (*type_it).second;

			if (pType == NULL)
			{
				Std::Out << __FILE__ << "(" << __LINE__ << ")" << " : INTERNAL ERROR: pType == NULL for '" << name << "' (contained in pScope->m_types)" << "\n";
			//	raise(Exception(L"INTERNAL ERROR: pType == NULL"));
				return NULL;
			}
			pType = pType->GetStripped();

			if (pType->get_Kind() == type_class)
			{
				return ((ClassType*)pType)->m_pScope;
			}
			/*
			else if (pType->get_Kind() == type_templateinst)	// TODO: Should this happen ??
			{
				// ???
				// partially instantiate here

			//	ClassType* p = InstantiateTemplate(NULL, ((TemplatedClassType*)pType), NULL);
			//	return p->m_pScope;

				return ((ClassType*)pType)->m_pScope;

			//	return ((TemplatedClassType*)pType)->m_pClass->m_pScope;
			}
			*/
		//	else
		//		ASSERT(0);
		}
	}

	return NULL;
}

Scope* parse_LookupScopeNameRecurse(Scope* pScope, StringIn name)
{
	Scope* pScope2 = parse_LookupScopeName(pScope, name);
	if (pScope2)
		return pScope2;

	ASSERT(pScope->m_pParentScope != pScope);

	if (pScope->m_pParentScope)
		return parse_LookupScopeNameRecurse(pScope->m_pParentScope, name);

	return NULL;
}

Scope* parse_GetNestedScope(CGlobal* pGlobal, Scope* pGlobalScope, Scope* pScope, ast::Expression* exp)
{
	/*
	if (exp->kind == ast::Expression::ast::A_ID)
	{
		Scope* pScope = LookupScopeNameRecurse(pScope, exp->id);
	}
	else
	*/

	/*
	if (exp->kind == ast::Expression::ast::A_TEMPLATEID)
	{
		pScope = LookupScopeNameRecurse(pScope, exp->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		left = exp;
	}
	else
	*/

	ASSERT(pScope != NULL);

	//Type* pType = NULL;

	ASSERT(exp->kind == ast::Expression::A_BINOP);

	if (exp->binop.right)
	{
		Scope* pScope2 = parse_LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);//pScope->GetType(exp->templateid.exp->id);

		if (pScope2 == NULL)
		{
			return NULL;
		}

		if (exp->binop.left->templateid.params)//kind == ast::Expression::ast::A_TEMPLATEID)
		{
			ASSERT(0);
#if 0
			TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);

			/*
			if (true)
			{
				StringBuilderA strbuilder;
				pTType->Write(strbuilder);
				StringA* str = strbuilder.DetachToString();
				Typedef* pTypedef = new Typedef(str, pTType);
				//pTypedef->m_pOwnerScope = 
				pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
			}
			*/

			pScope2 = pTType->m_pClass->m_pScope;

			if (pScope2 == NULL)
			{
				return NULL;
			}

			pType = pTType;
#endif
		}

		exp = exp->binop.right;

		while (exp->binop.right != NULL)
		{
			pScope2 = parse_LookupScopeName(pScope2, exp->binop.left->templateid.id);

			if (pScope2 == NULL)
			{
				return NULL;
			}

			if (exp->binop.left->templateid.params)
			{
				ASSERT(0);
#if 0
				TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);

				/*
				if (true)
				{
					StringBuilderA strbuilder;
					pTType->Write(strbuilder);
					StringA* str = strbuilder.DetachToString();
					Typedef* pTypedef = new Typedef(str, pTType);
					pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
				}
				*/

				pScope2 = pTType->m_pClass->m_pScope;

				if (pScope2 == NULL)
				{
					return NULL;
				}

				pType = pTType;
#endif
			}

			exp = exp->binop.right;
		}

		return pScope2;
	}
	else
	{
		if (exp->binop.left->templateid.id == NULL)
			return NULL;

	//	pType = LookupTypeNameRecurse(pScope, exp->binop.left->templateid.id);
		Scope* pScope2 = parse_LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		return pScope2;
	}
}

Type* parse_GetNestedType(CGlobal* pGlobal, Scope* pGlobalScope, Scope* pScope, ast::Expression* exp)
{
	/*
	if (exp->kind == ast::Expression::ast::A_ID)
	{
		Scope* pScope = LookupScopeNameRecurse(pScope, exp->id);
	}
	else
	*/

	/*
	if (exp->kind == ast::Expression::ast::A_TEMPLATEID)
	{
		pScope = LookupScopeNameRecurse(pScope, exp->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		left = exp;
	}
	else
	*/

	ASSERT(pScope != NULL);

	Type* pType = NULL;

	ASSERT(exp->kind == ast::Expression::A_BINOP);

	if (exp->binop.right)
	{
		Scope* pScope2 = parse_LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);//pScope->GetType(exp->templateid.exp->id);

		if (pScope2 == NULL)
		{
			return NULL;
		}

		if (exp->binop.left->templateid.params)//kind == ast::Expression::ast::A_TEMPLATEID)
		{
			/*Templated*/ClassType* pTType = parse_CreateClassInstance(pGlobal, pScope2->m_pNamespace->AsClass(), pScope, exp->binop.left->templateid.params);

			/*
			if (true)
			{
				StringBuilderA strbuilder;
				pTType->Write(strbuilder);
				StringA* str = strbuilder.DetachToString();
				Typedef* pTypedef = new Typedef(str, pTType);
				//pTypedef->m_pOwnerScope = 
				pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
			}
			*/

			// ??
			pScope2 = pTType->m_pInstantiatedFromClass->m_pScope;

			if (pScope2 == NULL)
			{
				return NULL;
			}

			pType = pTType;
		}

		exp = exp->binop.right;

		while (exp->binop.right != NULL)
		{
			pScope2 = parse_LookupScopeName(pScope2, exp->binop.left->templateid.id);

			if (pScope2 == NULL)
			{
				return NULL;
			}

			if (exp->binop.left->templateid.params)
			{
				// TODO, check if this is correct
				MessageBeep(-1);
				//ASSERT(0);
#if 0
				TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);

				/*
				if (true)
				{
					StringBuilderA strbuilder;
					pTType->Write(strbuilder);
					StringA* str = strbuilder.DetachToString();
					Typedef* pTypedef = new Typedef(str, pTType);
					pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
				}
				*/

				// ??
				pScope2 = pTType->m_pInstantiatedFromArgs->m_pClass->m_pScope;

				if (pScope2 == NULL)
				{
					return NULL;
				}

				pType = pTType;
#endif
			}

			exp = exp->binop.right;
		}

		pType = parse_LookupTypeName(pScope2, exp->binop.left->templateid.id);
	}
	else
	{
		if (exp->binop.left->templateid.id == NULL)
			return NULL;

		pType = parse_LookupTypeNameRecurse(pScope, exp->binop.left->templateid.id);
	}

	if (exp->binop.left->templateid.params)//kind == ast::Expression::ast::A_TEMPLATEID)
	{
		pType = parse_CreateClassInstance(pGlobal, pType->AsClass(), pScope, exp->binop.left->templateid.params);

		/*
		if (true)
		{
			StringBuilderA strbuilder;
			pType->Write(strbuilder);
			StringA* str = strbuilder.DetachToString();
			Typedef* pTypedef = new Typedef(str, pType);
			pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
		}
		*/
	}

	return pType;
}

Type* parse_GetType(CGlobal* pGlobal, Scope* pGlobalScope, Scope* pScope, ast::Expression* exp)
{
	/*
	if (exp->kind == ast::Expression::ast::A_ID)
	{
		Scope* pScope = LookupScopeNameRecurse(pScope, exp->id);
	}
	else
	*/

	/*
	if (exp->kind == ast::Expression::ast::A_TEMPLATEID)
	{
		pScope = LookupScopeNameRecurse(pScope, exp->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		left = exp;
	}
	else
	*/

	ASSERT(pScope != NULL);

	Type* pType = NULL;

	ASSERT(exp->kind == ast::Expression::A_BINOP);

	if (exp->binop.right)
	{
		Scope* pScope2 = parse_LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);//pScope->GetType(exp->templateid.exp->id);

		if (pScope2 == NULL)
		{
			return NULL;
		}

		if (exp->binop.left->templateid.params)//kind == ast::Expression::ast::A_TEMPLATEID)
		{
			/*Templated*/ClassType* pTType = parse_CreateClassInstance(pGlobal, pScope2->m_pNamespace->AsClass(), pScope, exp->binop.left->templateid.params);

			/*
			if (true)
			{
				StringBuilderA strbuilder;
				pTType->Write(strbuilder);
				StringA* str = strbuilder.DetachToString();
				Typedef* pTypedef = new Typedef(str, pTType);
				//pTypedef->m_pOwnerScope = 
				pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
			}
			*/

			// ??
		//	pScope2 = pTType->m_pInstantiatedFromArgs->m_pClass->m_pScope;
			pScope2 = pTType->m_pInstantiatedFromClass->m_pScope;

			if (pScope2 == NULL)
			{
				return NULL;
			}

			pType = pTType;
		}

		exp = exp->binop.right;

		while (exp->binop.right != NULL)
		{
			pScope2 = parse_LookupScopeName(pScope2, exp->binop.left->templateid.id);

			if (pScope2 == NULL)
			{
				return NULL;
			}

			if (exp->binop.left->templateid.params)
			{
				ASSERT(0);
#if 0
				TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);

				/*
				if (true)
				{
					StringBuilderA strbuilder;
					pTType->Write(strbuilder);
					StringA* str = strbuilder.DetachToString();
					Typedef* pTypedef = new Typedef(str, pTType);
					pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
				}
				*/

				// ??
				pScope2 = pTType->m_pInstantiatedFromArgs->m_pClass->m_pScope;

				if (pScope2 == NULL)
				{
					return NULL;
				}

				pType = pTType;
#endif
			}

			exp = exp->binop.right;
		}

		pType = parse_LookupTypeName(pScope2, exp->binop.left->templateid.id);
	}
	else
	{
		if (exp->binop.left->templateid.id == NULL)
			return NULL;

		pType = parse_LookupTypeName(pScope, exp->binop.left->templateid.id);
	}

	if (exp->binop.left->templateid.params)//kind == ast::Expression::ast::A_TEMPLATEID)
	{
		pType = parse_CreateClassInstance(pGlobal, pType->AsClass(), pScope, exp->binop.left->templateid.params);

		/*
		if (true)
		{
			StringBuilderA strbuilder;
			pType->Write(strbuilder);
			StringA* str = strbuilder.DetachToString();
			Typedef* pTypedef = new Typedef(str, pType);
			pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
		}
		*/
	}

	return pType;
}

map<ast::A_ClassHead*, Type*> class2type;

Type* parse_GetType(ast::DeclSpecList* declspecList, CGlobal* pGlobal, Scope* pScope, Scope* pTScope/*ast::A_TemplateParameterList * tp, bool bInsideTemplate*//*, Type** templateArgs*/)
{
	ast::DeclSpecList* dlist = NULL;

	Type* pType = NULL;

	int simpleType = -1;
	char sign = 0;
	char size = 0;
	bool bConst = false;
	bool bVolatile = false;
	bool bFriend = false;

	dlist = declspecList;
	while (dlist)
	{
		ast::A_DeclSpec* decl = dlist->head;

		if (decl->GetKind() == ast::A_DeclSpec::A_TYPE_MODIFIER)
		{
			ast::DeclSpecifierKeyword modifier = ((ast::A_DeclSpecModifier*)decl)->m_modifier;

			if (modifier == ast::A_CONST)
			{
				if (bConst)
					Std::Out << ("warn: const already specified\n");

				bConst = true;
			}
			else if (modifier == ast::A_VOLATILE)
			{
				if (bVolatile)
					Std::Out << ("warn: volatile already specified\n");

				bVolatile = true;
			}
			else if (modifier == ast::A_FRIEND)
			{
				if (bFriend)
					Std::Out << ("warn: friend already specified\n");

				bFriend = true;
			}
		}
		else if (decl->GetKind() == ast::A_DeclSpec::A_TYPE_BASIC)				
		{
			ast::BasicTypeSpecifier basicType = ((ast::A_DeclSpecBasicType*)decl)->m_basicType;

			if (basicType == ast::A_SIGNED)
			{
				if (sign == 1)
					Std::Out << ("warn: signed already specified");
				else if (sign == 2)
					Std::Out << ("error: unsigned already specified");
				else
					sign = 1;
			}
			else if (basicType == ast::A_UNSIGNED)
			{
				if (sign == 2)
					Std::Out << ("warn: unsigned already specified");
				else if (sign == 1)
					Std::Out << ("error: signed already specified");
				else
					sign = 2;
			}
			else if (basicType == ast::A_SHORT)
			{
				if (size == 1)
					Std::Out << ("warn: short already specified");
				else if (size == 2)
					Std::Out << ("error: long already specified");
				else
					size = 1;
			}
			else if (basicType == ast::A_LONG)
			{
				if (size == 1)
				{
					Std::Out << ("error: short already specified");
				}
				else if (size == 3)
				{
					Std::Out << ("error: long long already specified");
				}
				else
				{
					if (size == 2)
						size = 3;
					else
						size = 2;
				}
			}
			else
			{
				if (simpleType != -1)
				{
					Std::Out << ("error: type already specified\n");
				}
				simpleType = basicType;
			}
		}

		dlist = dlist->tail;
	}

	if (simpleType == -1 && sign == 0 && size == 0)
	{
		dlist = declspecList;
		while (dlist)
		{
			ast::A_DeclSpec* decl = dlist->head;

			switch (decl->GetKind())
			{
			case ast::A_DeclSpec::A_TYPE_NAME:
				{
					ast::A_NameType* pTypeName = static_cast<ast::A_NameType*>(decl);
					
					Type* pType2 = parse_GetNestedType(pGlobal, NULL, pTScope, pTypeName->m_name);
					
					if (pType2 == NULL)
					{
						ast::Expression* exp = pTypeName->m_name;
						
						String qname;
						
						while (1)
						{
							qname += String(exp->binop.left->templateid.id);
							
							exp = exp->binop.right;
							if (exp == NULL) break;
							
							qname += "::";
						}
						
						serror() << decl->m_filename << paren(decl->m_line_pos+1) << " : undeclared type " << qname << "\n";
						
						pType2 = parse_GetNestedType(pGlobal, NULL, pScope, pTypeName->m_name);
						
						break;
					}
					
					pType = pType2;
				}
				break;
				
			case ast::A_DeclSpec::A_TYPE_ENUM:
				{
					ast::A_Enum* DeclEnum = static_cast<ast::A_Enum*>(decl);
					
					if (DeclEnum->m_name)
					{
						pType = pScope->GetType(DeclEnum->m_name);
						if (pType != NULL)
						{
							Std::Out << DeclEnum->m_filename << "(" << DeclEnum->m_line_pos << "," << DeclEnum->m_column << ")" << " : error : already defined enum '" << DeclEnum->m_name << "'\n";
						}
					}
					
					if (pType == NULL)
					{
						EnumType* pEnum = new EnumType(DeclEnum->m_name);
						pEnum->m_ownerScope = pScope;
						
						DeclEnum->m_deflist = Reverse(DeclEnum->m_deflist);
						
						pType = pEnum;
						
						int value = 0;

						for (auto list2 = DeclEnum->m_deflist; list2 != NULL; list2 = list2->tail)
						{
							if (list2->head->m_exp)
							{
								// TODO
#if 0
								Tr_Exp* exp = TransExpression(NULL/*T_Declarator* frame*/, list2->head->m_exp, pGlobal, pScope);
								if (exp)
									value = Evaluate(exp->ex);//->const_int.int32;
								else
									;
#endif
							}
							
							pEnum->m_deflist.push_back(EnumDef(list2->head->m_name, value));
							
							Declarator* pDeclarator = new Declarator;
							pDeclarator->m_localVar = 2;	// 2 means enum identifier
							pDeclarator->m_name = list2->head->m_name;
							pDeclarator->m_pType = pEnum;
							pDeclarator->m_offset = value;	// m_offset is used for value
							
							pScope->m_identdecls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							
							++value;
						}
						
						if (DeclEnum->m_name)
						{
							Declarator* pDeclarator = new Declarator(pEnum, pEnum->m_name);
							pDeclarator->m_typedef = true;
							pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_orderedDecls.Add(pDeclarator);
							
							pScope->m_types.insert(typemap::value_type(pEnum->m_name, pEnum));
							//	pGlobal->m_alltypes.insert(typemap::value_type(pEnum->m_qname, pEnum));
							
#if 0	// ??
							pGlobal->m_types.Add(pEnum);
#endif
							
							pGlobal->m_alltypes.push_back(pEnum);
						}
					}
				}
				break;
				
			case ast::A_DeclSpec::A_TYPE_CLASS:// && !bFriend)	// hm..
				{
					ast::A_Class* pClass = static_cast<ast::A_Class*>(decl);

					pType = class2type[pClass->m_head];
					ASSERT(pType);

					if (!bFriend)
					{
#if 0
						ast::A_Class* Class = (ast::A_Class*)decl;
						
						// TODO, remove these restrictions
						ASSERT(Class->m_head->m_name->kind == ast::Expression::ast::A_BINOP);
						ASSERT(Class->m_head->m_name->binop.left->kind == ast::Expression::ast::A_TEMPLATEID);
						
						Type* pType2 = GetNestedType(pGlobal, NULL, pScope, Class->m_name);
						
						//	typemap::iterator it = pScope->m_types.find(Class->m_name->binop.left->templateid.id);
						//	if (it != pScope->m_types.end())
						if (pType2)
						{
							pType = pType2;
							//pType = (*it).second;//pScope->GetType(decl->CLASSDEF.head->name);
						}
						else
							pType = NULL;
						
						if (pType != NULL)
						{
							if (pType->GetKind() == type_class)
							{
								ClassType* pClass = pType->GetClass();
								
								if (pClass->m_kwType != Class->m_classKey)
								{
									printf("'%s %s' first seen as %s\n", ClassKeyName(Class->m_classKey), Class->m_name->templateid.id->c_str(), ClassKeyName((ClassKey)pClass->m_kwType));
								}
							}
							else
							{
								printf("error: '%s %s' already defined as something else\n", ClassKeyName(Class->m_classKey), Class->m_name->binop.left->templateid.id->c_str());
							}
							
							//	pType->AddRef();
						}
						else
						{
							ClassType* pClass = new ClassType;
							pType = pClass;
							//		pType->m_type = type_class;
							//		pType->m_pClass = new Class;
							//pClass->AddRef();
							
							pClass->m_pOwnerScope = pScope;
							pClass->m_pScope->m_pParentScope = pScope;	// hmm..
							pClass->m_name = Class->m_name->binop.left->templateid.id;
							
							pClass->m_def = false;	// Forward reference
							
							//ASSERT(0);
#if 0
							pClass->m_location.m_line = type->CLASSDEF.head->line_pos;
#endif
							pClass->m_kwType = Class->m_classKey;
							
							pClass->m_pScope->m_name = pClass->m_name;
							
							//pClass->m_qname = GetQualifiedName(pClass->m_pScope);
							
							CDeclarator* pDeclarator = new CDeclarator;
							pDeclarator->m_typedef = true;
							pDeclarator->m_name = pClass->m_name;
							pDeclarator->m_pType = pClass;
							
							//CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);
							pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_orderedDecls.Add(pDeclarator);
							pScope->m_types.insert(typemap::value_type(pClass->m_name, pClass));
						}
#endif
					}
				}
				break;
				
			case ast::A_DeclSpec::A_TYPE_CLASSDEF:
				{
					ast::A_ClassDef* CLASSDEF = static_cast<ast::A_ClassDef*>(decl);
					
					if (CLASSDEF->m_head == nullptr)
					{
						ASSERT(0);
					}

					pType = class2type[CLASSDEF->m_head];
					ASSERT(pType);

#if 0
					ASSERT(g_pClass);
					ClassType* pClass = g_pClass;
					g_pClass = NULL;
					//ASSERT(0);
					
#if 0
					/*
					if (decl->CLASSDEF.head && decl->CLASSDEF.head->name)
					{
					if (!strcmp(decl->CLASSDEF.head->name, "_Brush"))
					{
					MessageBeep(-1);
					}
					}
					*/
					
					if (CLASSDEF->m_head->m_name != NULL)
					{
						//typemap::iterator it = pScope->m_types.find(CLASSDEF->m_head->m_name);
						
						Type* pType2 = GetNestedType(pGlobal, NULL, pScope, CLASSDEF->m_head->m_name);
						
						//if (it != pScope->m_types.end())
						if (pType2)
						{
							pType = pType2;//(*it).second;//pScope->GetType(decl->CLASSDEF.head->name);
						}
						else
							pType = NULL;//System::Type();
					}
					else
						pType = NULL;//System::Type();
					
			//		ClassType* pClass = NULL;
					
					if (pType != NULL)
					{
						if (pType->GetKind() == type_class)
						{
							pClass = pType->GetClass();
							//	pClass->AddRef();
							
							if (pClass->m_kwType != CLASSDEF->m_head->m_classKey)
							{
								printf("'%s ()' first seen as %s\n", ClassKeyName(CLASSDEF->m_head->m_classKey), /*CLASSDEF->m_head->m_name->c_str(),*/ ClassKeyName((ClassKey)pClass->m_kwType));
							}
							else
							{
								if (pClass->m_sizeof != -1)
								{
									printf("class '' already defined\n"/*, CLASSDEF->m_head->m_name->c_str()*/);
								}
							}
						}
						else
						{
							printf("Already declared as something else");
						}
					}
					else
					{
						pClass = new ClassType;
						pType = pClass;
						//		pType->m_type = type_class;
						//		pType->m_pClass = new Class;
						//	pClass->AddRef();
						
						pClass->m_pOwnerScope = pScope;
						pClass->m_pScope->m_pParentScope = pScope;	// hmm..
						//ASSERT(0);
#if 0
						pClass->m_location.m_line = type->CLASSDEF.head->line_pos;
#endif
						pClass->m_kwType = CLASSDEF->m_head->m_classKey;
						
						if (CLASSDEF->m_head->m_name != NULL)
						{
						/*
						if (!strcmp(CLASSDEF->m_head->m_name->c_str(), "GraphicsBase"))
						{
						MessageBeep(-1);
						}
							*/
							
							pClass->m_name = CLASSDEF->m_head->m_name->binop.left->templateid.id;
							pClass->m_pScope->m_name = pClass->m_name;
							//	pType->m_pNamedType->m_name = type->CLASSDEF.head->name;
							
							//	pClass->m_qname = GetQualifiedName(pClass->m_pScope);
							
							CDeclarator* pDeclarator = new CDeclarator;
							pDeclarator->m_typedef = true;
							pDeclarator->m_name = pClass->m_name;
							pDeclarator->m_pType = pClass;
							
							//	CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);
							pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_orderedDecls.Add(pDeclarator);
							pScope->m_types.insert(typemap::value_type(pClass->m_name, pClass));
							
							//	pGlobal->m_alltypes.insert(typemap::value_type(pClass->m_qname, pClass));
							//	pGlobal->m_types.Add(pClass);
						}
					}
					
					pClass->m_def = true;
					
					/*
					if (decl->CLASSDEF.head->name)
					{
					typemap::iterator i = pScope->m_types.find(decl->CLASSDEF.head->name);
					if (i != pScope->m_types.end())
					{
					}
					else
					{
					
					  //	pScope->m_types.insert(typemap::value_type(pEnum->m_name, pType));
					  }
					  }
					*/
					
					pClass->m_items = templateParams;
					templateParams.clear();

					if (pTScope)
					{
						pClass->m_pScope->m_pParentScope = pTScope;
					}
#endif

#if 0
					ASSERT(tp == NULL);
					if (tp)
					{
						Scope* pTScope;
						pTScope = new Scope;
						pTScope->m_pParentScope = pClass->m_pScope->m_pParentScope;
						pClass->m_pScope->m_pParentScope = pTScope;
						
						//ast::A_TemplateParameterList * tplist = tp;
						
						/*
						// Reverse list
						{
						ast::A_TemplateParameterList * tp2 = tp;
						while (tp2)
						{
						tplist = new ast::A_TemplateParameterList(tp2->head, tplist);
						tp2 = tp2->tail;
						}
						}
						*/
						
						int index = 0;
						//tp = tplist;
						//ast::A_TemplateParameterList * tp = d->TEMPLATE.params;
						while (tp)
						{
							if (tp->head->GetKind() == ast::A_TemplateParameter::ast::A_ParamType)
							{
								ast::A_TypeTemplateParameter* typeparam = (ast::A_TypeTemplateParameter*)tp->head;
								
								TemplateParameter* param = new TemplateParameter;
								param->m_kind = TemplateParameter::Param_Type;
								param->m_index = index;
								
								_TemplateArgType* pType = new _TemplateArgType();
								//pType->m_kind = _TemplateArgType::Arg_Type;
								pType->m_pOwnerScope = pTScope;
								pType->m_index = index;
								pType->m_name = typeparam->m_id;
								
								param->m_pType = pType;
								
								if (typeparam->m_typeId)
								{
									pType->m_defaultArg = new TemplatedClassArg;
									pType->m_defaultArg->m_pType = GetType(typeparam->m_typeId->declspecList, pGlobal, pClass->m_pScope, NULL/*tp ?*/, true);
								}
								
								pClass->m_items.push_back(param);
								
								pTScope->m_types.insert(typemap::value_type(pType->m_name, pType));
							}
							else
							{
								ast::A_DeclaratorTemplateParameter* declparam = (ast::A_DeclaratorTemplateParameter*)tp->head;
								
								CDeclarator* pDeclarator = new CDeclarator;
								pDeclarator->m_pType = GetType(declparam->m_decls, pGlobal, pClass->m_pScope/*pTScope*//*pScope*/, NULL/*tp*/, true);//NULL;//d->fundef.declspecList
								declparam->m_declarator->Extract(pDeclarator, pDeclarator->m_pType, pClass->m_pScope/*pTScope*//*pScope*/, pGlobal);
								
								/*
								__live_object_ptr<_TemplateArgType> pArg;
								pArg = new _TemplateArgType();
								pArg->m_kind = _TemplateArgType::Arg_Value;
								pArg->m_pOwnerScope = pTScope;
								pArg->m_index = index++;
								pArg->m_name = pDeclarator->m_name;
								pArg->m_pTypeOfValue = pDeclarator->m_pType;
								*/
								
								TemplateParameter* param = new TemplateParameter;
								param->m_index = index;
								param->m_kind = TemplateParameter::Param_Value;
								
								param->m_pDeclarator = pDeclarator;
								
								pClass->m_items.push_back(param);
								
								pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							}
							
							index++;
							
							tp = tp->tail;
						}
						
						if (*pClass->m_name == "StringT")
						{
							ASSERT(pClass->m_items.size() == 2);
						}
						
					}
#endif
					//	else
					//		pTScope = pClass->m_pScope;
					
					//	pClass->m_sizeof = 0;
					/*
					if (CLASSDEF->m_head->m_name && !strcmp(CLASSDEF->m_head->m_name->c_str(), "EventTargetImpl"))
					{
					MessageBeep(-1);
					}
					*/
					
					ast::A_BaseSpecifierList* baseList = CLASSDEF->m_baseList;
					while (baseList)
					{
						BaseClass* baseClass = new BaseClass;
						
						Type* pType2;
						
#if 0
						if (baseList->head->kind == ast::Expression::ast::A_ID)
						{
							pType2 = pClass->m_pScope->GetType(baseList->head->id);
							baseClass.m_pClass = pType2->GetClass();
						}
						else if (baseList->head->kind == ast::Expression::ast::A_TEMPLATEID)
						{
							//	pType2 = pTScope->GetType(baseList->head->id);
							System::Type pTemplateClass = pClass->m_pScope->GetType(baseList->head->templateid.exp->id);
							ASSERT(pTemplateClass->m_type == type_class);
							
							TemplatedClassType* pTType = new TempatedClass;
							pTType->AddRef();
							
							pTType->m_pClass = pTemplateClass->GetClass();
							pTType->m_pClass->AddRef();
							
							ast::A_TypeIdList* typeIds = baseList->head->templateid.params;
							while (typeIds)
							{
								ast::A_TypeId* typeId = typeIds->head;
								
								System::Type pTemplateArgType = GetType(typeId->declspecList, pGlobal, pClass->m_pScope, tp, bInsideTemplate);
								//pTemplateArgType->
								
								pTType->m_templateArgs.Add(pTemplateArgType);
								
								typeIds = typeIds->tail;
							}
							
							pType2 = pTType;
							
							baseClass.m_pClass = pTType;
						}
						else
						{
							Scope* pScope2 = GetNestedScope(NULL/*pGlobal*/, pClass->m_pScope/*pTScope*/, baseList->head->binop.left);
							if (pScope2 == NULL)
							{
								printf("undeclared base class %s\n", baseList->head->binop.right->id);
								//exit(1);
								break;
							}
							
							pType2 = pScope2->GetType(baseList->head->binop.right->id);
							
							baseClass.m_pClass = pType2->GetClass();
						}
#endif
						pType2 = GetNestedType(pGlobal, NULL, pClass->m_pScope, baseList->head);
						
						if (pType2 == NULL)
						{
							if (baseList->head->kind == ast::Expression::ast::A_ID)
							{
								pType2 = pClass->m_pScope/*pTScope*/->GetType(baseList->head->templateid.id);
								printf("undeclared base class %s\n", baseList->head->templateid.id->c_str());
							}
							else
								printf("undeclared base class\n");
							//exit(1);
							ASSERT(0);
							break;
						}
						
						baseClass->m_pClass = (ClassType*)pType2;
						ASSERT(baseClass->m_pClass);
						/*
						if (pType2->m_type != type_class)
						{
						printf("base class is not a class\n");
						//exit(1);
						break;
						}
						*/
						
						{
							//	baseClass.m_offset = pClass->get_sizeof();
							//	pClass->m_sizeof += baseClass.m_pClass->get_sizeof();
						}
						
						pClass->GetClass()->m_bases.push_back(baseClass);
						
						baseList = baseList->tail;
					}
					
#if 0
					//if (type->kind == ast::A_DeclSpec::ast::A_TYPE_CLASSDEF)
					{
						Array<ast::A_Declaration*> methods;
						
						ast::A_AccessSpec accessSpec;
						
						if (CLASSDEF->m_head->m_classKey == CLASSKEY_CLASS)
							accessSpec = ast::A_ACCESS_PROTECTED;
						else
							accessSpec = ast::A_ACCESS_PUBLIC;
						
						ast::A_MemberSpec* member = CLASSDEF->m_memberSpec;
						while (member)
						{
						//	ASSERT(0);
#if 1
							if (member->GetKind() == ast::A_MemberSpec::ast::A_ACCESS_SPEC)
							{
								accessSpec = ((ast::A_MemberAccessSpec*)member)->m_accessSpec;
							}
							else
							{
								ast::A_Declaration* d = ((ast::A_MemberDecl*)member)->m_declaration;
								if (d == NULL)	// TODO remove
								{
									member = member->m_next;
									continue;
								}
								
#if 0
								if (d->GetKind() == ast::A_Declaration::ast::A_TEMPLATE)
								{
									ast::A_TemplateDeclaration* td = (ast::A_TemplateDeclaration*)d;
									
									td->m_params = Reverse(td->m_params);
									
									if (td->m_decl->GetKind() == ast::A_Declaration::ast::A_SIMPLE)
									{
										SimpleDeclaration((ast::A_SimpleDeclaration*)td->m_decl, pGlobal, pClass->m_pScope/*pTScope*/, NULL, td->m_params, true);
									}
									else if (td->m_decl->GetKind() == ast::A_Declaration::ast::A_FUNDEF)
									{
										FunDef((ast::A_FunDef*)td->m_decl, pGlobal, pClass->m_pScope, td->m_params);
										
#if 0
										ast::A_FunDef* fundef = ;
										CDeclarator* pDeclarator = new CDeclarator;
										Type* pType = GetType(fundef->m_declspec, pGlobal, pClass->m_pScope/*pTScope*//*pScope*/, td->m_params/*tp*/, bInsideTemplate);//NULL;//d->fundef.declspecList
										pDeclarator->m_pType = pType;
										Scope* p = fundef->m_declarator->Extract(pDeclarator, pType, pClass->m_pScope/*pTScope*//*pScope*/, pGlobal);
										
										ASSERT(pDeclarator->m_name->Length());
										ASSERT(pDeclarator->m_pType != NULL);
										pClass->m_pScope->m_orderedDecls.push_back(pDeclarator);
										
										FunBody(fundef, pGlobal, pClass->m_pScope);
#endif
									}
									else
										ASSERT(0);
								}
								else
#endif
									if (d->GetKind() == ast::A_Declaration::ast::A_FUNDEF)
								{
									ast::A_FunDef* fundef = (ast::A_FunDef*)d;
									FunDef(fundef, pGlobal, pClass->m_pScope, pTScope);
									
#if 0
									CDeclarator* pDeclarator = new CDeclarator;
									Type* pType = GetType(fundef->m_declspec, pGlobal, pClass->m_pScope/*pTScope*//*pScope*/, NULL/*tp*/, bInsideTemplate);//NULL;//d->fundef.declspecList
									pDeclarator->m_pType = pType;
									Scope* p = fundef->m_declarator->Extract(pDeclarator, pType, pClass->m_pScope/*pTScope*//*pScope*/, pGlobal);
									
									ASSERT(pDeclarator->m_name->Length());
									ASSERT(pDeclarator->m_pType != NULL);
									pClass->m_pScope->m_orderedDecls.push_back(pDeclarator);
									
									FunBody(fundef, pGlobal, pClass->m_pScope);
									
									methods.Add(d);
#endif
								}
								else if (d->GetKind() == ast::A_Declaration::ast::A_SIMPLE)
								{
									CDeclaratorList* declaratorList = SimpleDeclaration((ast::A_SimpleDeclaration*)d, pGlobal, /*pTScope*/pClass->m_pScope, pClass, pTScope);//, bInsideTemplate);
									
									while (declaratorList)
									{
									/*
									if (declaratorRefList->head->m_pDeclarator->m_pType->m_type != type_function)
									{
									if (true)	// instantiating or not inside template
									{
									int _sizeof;
									
									  if (declaratorRefList->head->m_pDeclarator->m_pType->m_type == type_templatearg)
									  _sizeof = templateArgs[((TemplateArgType*)declaratorRefList->head->m_pDeclarator->m_pType)->m_index]->get_sizeof();
									  else
									  _sizeof = declaratorRefList->head->m_pDeclarator->m_pType->get_sizeof();
									  
										 if (pClass->m_kwType == ast::A_CLASSKEY_UNION)
										 {
										 declaratorRefList->head->m_pDeclarator->m_offset = 0;
										 if (_sizeof > pClass->m_sizeof)
										 pClass->m_sizeof = _sizeof;
										 }
										 else
										 {
										 declaratorRefList->head->m_pDeclarator->m_offset = pClass->m_sizeof;
										 pClass->m_sizeof += _sizeof;
										 }
										 }
										 }
										*/
										
										// ??
										//	ASSERT(declaratorRefList->head->m_pDeclarator->m_name.Length());
										ASSERT(declaratorList->head->m_pType != NULL);
										pClass->m_pScope->m_orderedDecls.push_back(declaratorList->head);
										
										//	ASSERT(pClass->m_pScope->m_decls.find(declaratorList->head->m_name) == pClass->m_pScope->m_decls.end());
										pClass->m_pScope->m_decls.insert(declsmap::value_type(declaratorList->head->m_name, declaratorList->head));
										
										declaratorList = declaratorList->tail;
									}
								}
								else
									ASSERT(0);
							}
						
							member = member->m_next;
#endif
						}
					
#if 0
						{
							for (int i = 0; i < methods.size(); i++)
							{
								ast::A_Declaration* d = methods[i];
							
							FunBody(NULL/*TODO*/, d, pGlobal, pClass->m_pScope);
								
							}
						}
#endif
					}
#endif
				
				// TODO, add it ?
					pGlobal->m_alltypes.push_back(pClass);
#if 0
					if (!bInsideTemplate)
					{
						CalcClass(pGlobal, pClass);
						
						//	if (pClass->m_qname)
						{
							//		ASSERT(pClass->m_qname);
							//	pGlobal->m_alltypes.insert(typemap::value_type(pClass->m_qname, pClass));
							//	pGlobal->m_types.Add(pClass);
							
							pGlobal->m_alltypes.push_back(pClass);
						}
					}
#endif
#endif
				}
				break;

			case ast::A_DeclSpec::A_DECLTYPE:
				{
					ast::DeclType* pDecltype = static_cast<ast::DeclType*>(decl);

					// TODO
					if (pDecltype->m_exp->GetKind() == Expression::A_NULLPTR)
					{
						pType = Types::get_nullType();
					}
					else
					{
						VERIFY(0);
					}
				}
				break;
			}

			dlist = dlist->tail;
		}
	}
	else
	{
		if (simpleType == -1 && (size != 0 || sign != 0))	// If only size or sign is specified, default to int of that size or sign
		{
			simpleType = ast::A_INT;
		}
		/*
		else if (simpleType == ast::A___INT64)
		{
			simpleType = ast::A_INT;
			size = 3;
		}
		*/

		switch (simpleType)
		{
		case ast::A_VOID:
		{
			if (sign != 0)
			{
				Console::Out << ("error: signed/unsigned cannot be specified on void type");
			}

			if (size != 0)
			{
				Console::Out << ("error: short/long cannot be specified on void type");
			}

			pType = System::Types::get_void();
		}
		break;

		case ast::A_CHAR:
		{
			if (size != 0)
			{
				Console::Out << ("error: short/long cannot be specified on char type");
			}

			if (sign == 1)
				pType = &System::Types::type_signed_char;
			else if (sign == 2)
				pType = &System::Types::type_unsigned_char;
			else
				pType = &System::Types::type_char;
		}
		break;

		case ast::A_WCHAR_T:
		{
			if (sign != 0)
			{
				Console::Out << ("error: signed/unsigned cannot be specified on wchar_t type");
			}

			if (size != 0)
			{
				Console::Out << ("error: short/long cannot be specified on wchar_t type");
			}

			if (!pGlobal->m_options->m_type_wchar_t)
			{
				// VC 6.0
				pType = Types::get_unsigned_short();
			}
			else
			{
				pType = Types::get_wchar();
			}
		}
		break;

		case ast::A_BOOL:
		{
			if (sign != 0)
			{
				Std::Out << ("error: signed/unsigned cannot be specified on bool type");
			}

			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on bool type");
			}

			pType = &System::Types::type_bool;
		}
		break;

		case ast::A_INT:
		{
			if (size == 1)	// short
			{
				if (sign == 2)	// unsigned
					pType = Types::get_unsigned_short();
				else
					pType = Types::get_short();
			}
			else if (size == 2)
			{
				if (sign == 2)	// unsigned
					pType = Types::get_unsigned_long();
				else
					pType = Types::get_long();
			}
			else if (size == 3)
			{
				if (sign == 2)	// unsigned
					pType = Types::get_unsigned_long_long();
				else
					pType = Types::get_long_long();
			}
			else
			{
				if (sign == 2)	// unsigned
					pType = Types::get_unsigned_int();
				else
					pType = Types::get_int();
			}
		}
		break;

		case ast::A___INT8:
		{
			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on __int8 type");
			}

			if (sign == 2)
				pType = Types::get_unsigned_char();
			else
				pType = Types::get_signed_char();
		}
		break;

		case ast::A___INT16:
		{
			if (size != 0)
			{
				Console::Out << ("error: short/long cannot be specified on __int16 type");
			}

			if (sign == 2)
				pType = Types::get_unsigned_short();
			else
				pType = Types::get_short();
		}
		break;

		case ast::A___INT32:
		{
			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on __int32 type");
			}

			if (sign == 2)
				pType = Types::get_unsigned_long();
			else
				pType = Types::get_long();
		}
		break;

		case ast::A___INT64:
		{
			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on __int64 type");
			}

			if (sign == 2)
				pType = Types::get_unsigned_long_long();
			else
				pType = Types::get_long_long();
		}
		break;

		case ast::A_FLOAT:
		{
			if (sign != 0)
			{
				Std::Out << ("error: signed/unsigned cannot be specified on float type");
			}

			if (size != 0)
			{
				Console::Out << ("error: short/long cannot be specified on float type");
			}

			pType = Types::get_float();
		}
		break;

		case ast::A_DOUBLE:
		{
			if (sign != 0)
			{
				Console::Out << ("error: signed/unsigned cannot be specified on double type");
			}

			if (size == 1)
			{
				Console::Out << ("error: short cannot be specified on double type");
			}
			else if (size == 3)
			{
				Console::Out << ("error: long long cannot be specified on double type");
			}

			if (size == 2)
				pType = &System::Types::type_long_double;
			else
				pType = &System::Types::type_double;
		}
		break;

		default:
			ASSERT(0);
		}

		/*
//		((CVType*)pType)->m_bConst = bConst;
//		((CVType*)pType)->m_bVolatile = bVolatile;
		if (bConst || bVolatile)
		{
			pType = System::ModifierType(bConst, bVolatile, pType);
	//		ModifierType* pModifierType = new ModifierType(bConst, bVolatile, pType);
		//	pModifierType->m_bConst = bConst;
		//	pModifierType->m_bVolatile = bVolatile;

	//		pType = pModifierType;
		}
		*/
	}

	if (bConst || bVolatile)
	{
		pType = new ModifierType(pType, bConst, bVolatile);
	}

//	if (pType == NULL)
//		return System::Types::type_void;	// ??

	return pType;
}

static CDeclaratorList* SimpleDeclaration(/*ast::ExpressionList* attribute_spec,*/ ast::A_SimpleDeclaration* d, CGlobal* pGlobal, Scope* pScope, ClassType* pInnermostClass, Scope* pTScope/*ast::A_TemplateParameterList * tp, bool bInsideTemplate*/)
{
	CDeclaratorList* declaratorList = nullptr;

	bool bTypedef = false;
	bool bExtern = false;
	bool bVirtual = false;
	bool bStatic = false;

	ast::DeclSpecList* decllist = d->m_declspec;
	while (decllist)
	{
		if (decllist->head == nullptr)
		{
			decllist = decllist->tail;
			continue;
		}

		if (decllist->head->GetKind() == ast::A_DeclSpec::A_TYPE_MODIFIER)
		{
			ast::A_DeclSpecModifier* pModifier = (ast::A_DeclSpecModifier*)decllist->head;

			if (pModifier->m_modifier == ast::A_TYPEDEF)
			{
				if (bTypedef)
					Console::Out << ("warn: typedef already specified");

				bTypedef = true;
			}
			else if (pModifier->m_modifier == ast::A_EXTERN)
			{
				if (bExtern)
					Console::Out << ("warn: extern already specified");

				bExtern = true;
			}
			else if (pModifier->m_modifier == ast::A_VIRTUAL)
			{
				if (bVirtual)
					Console::Out << ("warn: virtual already specified");

				bVirtual = true;
			}
			else if (pModifier->m_modifier == ast::A_STATIC)
			{
				if (bStatic)
					Console::Out << ("warn: static already specified\n");

				bStatic = true;
			}
		}

		decllist = decllist->tail;
	}

	Type* pType = parse_GetType(d->m_declspec, pGlobal, pScope, pTScope/*tp, bInsideTemplate*/);

	if (pType == nullptr)
		return nullptr;

#if 0
	if (pType->get_Kind() == type_class)
	{
		ClassType* pClassType = (ClassType*)pType;

		if (attribute_spec)
		{
			unsigned int count = 0;
			{
				ExpressionList* explist = attribute_spec;
				while (explist)
				{
					++count;
					explist = explist->tail;
				}
			}

			pClassType->m_attributes = array<AttributeDef>(new AttributeDef[count], count);

			unsigned int n = 0;
			ExpressionList* explist = attribute_spec;
			while (explist)
			{
				Expression* exp = attribute_spec->head;

				VERIFY(exp->kind == Expression::A_CALL);

				ClassType* pMethodClass = 

				pClassType->m_attributes[n].m_pClass

				explist = explist->tail;
				n++;
			}
		}
	}
#endif

#if 0
	if (!bInsideTemplate)
	{
#if 0
		if (pType->m_type == type_class)
		{
			/*
			TemplateArgs templateArgs;
			templateArgs.m_args = NULL;
			templateArgs.m_parent = NULL;	// ?&

			Class* pClass = InstantiateTemplate(pGlobal, pType->GetClass(), &templateArgs);
			*/
			Class* pClass = pType->GetClass();
			CalcClass(pGlobal, pClass);

		//	pGlobal->m_alltypes.insert(typemap::value_type(pClass->m_qname, pClass));
		//	pGlobal->m_types.Add(pClass);

			pType = pClass;
		}
		else
#endif
			if (pType->GetKind() == type_templateinst)
		{
		//	TemplateArgs templateArgs;
		//	templateArgs.m_count = ((TemplatedClassType*)pType.m_p)->m_templateArgs.GetSize(); 
		//	templateArgs.m_args = ((TemplatedClassType*)pType.m_p)->m_templateArgs.GetData();
		//	templateArgs.m_pTemplated = NULL;//((TemplatedClassType*)pType.m_p);//->m_templateArgs;
		//	templateArgs.m_parent = NULL;	// ?

			ClassType* pClass = InstantiateTemplate(pGlobal, ((TemplatedClassType*)pType)/*->m_pClass*/, NULL/*&templateArgs*/);

			if (true)
			{
			//	pGlobal->m_alltypes.push_back(pClass);

				/*
				StringBuilderA strbuilder;
				pClass->Write(strbuilder);
				StringA* str = strbuilder.DetachToString();
				Typedef* pTypedef = new Typedef(new StringA(""), pClass);
				pTypedef->m_qname = str;
				pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_qname, pTypedef));
				*/
			}

#if 0
			pGlobal->m_alltypes.insert(typemap::value_type(pClass->m_qname, pClass));
			pGlobal->m_types.Add(pClass);
#endif

			pType = pClass;
		}
	}
#endif
	// TODO
	//pGlobal->m_types.push_back(typemap::value_type(pClass->m_qname, pClass));

	/*
	if (pType == NULL)
	{
		pType = GetType(d->simple.declspecList, pGlobal, pScope);
		ASSERT(pType);
	}
	*/

	ast::InitDeclaratorList* declp = d->m_declaratorList;
	if (declp == NULL)
	{
		if (pType->get_Kind() != type_class && pType->get_Kind() != type_enum)
		{
			Std::Out << ("ignored when no variable is declared\n");
		}
	}
	else
	{
		while (declp)
		{
			Declarator* pDeclarator = new Declarator;
			//pDeclarator->line_pos = declp->head->line_pos;
			pDeclarator->m_pType = pType;
			pDeclarator->m_static = bStatic;

			if (pInnermostClass == (ClassType*)1)
			{
				pDeclarator->m_localVar = true;
			}
			else
			{
				pDeclarator->m_localVar = false;
			}

			if (declp->head)	// TODO, remove
			{
				ASSERT(declp->head);

				declp->head->m_declarator->Extract(pDeclarator, pType, pScope, pTScope, pGlobal);

				/*
				if (pDeclarator->m_name == "vector3d")
				{
					MessageBeep(-1);
				}
				*/

				pDeclarator->m_virtual = bVirtual;
				pDeclarator->m_typedef = bTypedef;

				if (bTypedef)
				{
					ASSERT(pDeclarator->m_name);

					Typedef* pTypedef = new Typedef(pDeclarator->m_name, pDeclarator->m_pType);
					pTypedef->m_ownerScope = pScope;

					pDeclarator->m_pType = pTypedef;
				}

				ASSERT(pDeclarator->m_pType != nullptr);

			//	nontypedef_declarator(pDeclarator);

				/*
				if (bTypedef)
				{
					typemap::iterator i = pScope->m_types.find(pDeclarator->m_name);
					if (i != pScope->m_types.end())
					{
						Type* pType2 = (*i).second;
						if (pType2 != pDeclarator->m_pType)	// If these are the same it means e.g 'typedef struct x { ... } x;
						{
							printf("'%s' Type already defined\n", pDeclarator->m_name.c_str());
						}
					}
					else
					{
						Typedef* pTypedef = new Typedef(pDeclarator->m_name, pDeclarator->m_pType);
						pTypedef->AddRef();

						pScope->m_types.insert(typemap::value_type(pDeclarator->m_name, pTypedef));
					}
				}
				else
				*/
				if (pDeclarator->m_name)
				{
					declsmap::iterator decli = pScope->m_decls.find(pDeclarator->m_name);
					if (decli != pScope->m_decls.end())
					{
						if ((*decli).second->m_defined)
						{
						//	MessageBeep(-1);
							//printf("error(%d): '%s' Already declared\n", /*pDeclarator->m_location.m_line*/0, pDeclarator->m_name->c_str());
						}
						else
						{
							if (pDeclarator->m_pType->get_Kind() == type_function)
							{
#if 0
								__live_object_ptr<FunctionType> pFun1 = (*decli).second->m_pType->GetFunction();
								__live_object_ptr<FunctionType> pFun2 = pDeclarator->m_pType->GetFunction();

								__live_object_ptr<StringA> str1 = *pFun1->m_parameters.ToString() + (pFun1->m_bConst? "const": "");
								__live_object_ptr<StringA> str2 = *pFun2->m_parameters.ToString() + (pFun2->m_bConst? "const": "");
								if (*str1 == *str2)
								{
								//	StringA str1 = (*decli).second->m_pDeclarator->m_pType->ToString();
								//	StringA str2 = pDeclarator->m_pType->ToString();

									printf("%s(%d): '%s' method already declared\n", declp->head->m_filename? declp->head->m_filename->c_str(): "(null)", declp->head->m_line_pos, pDeclarator->m_name->c_str());

									//(*decli).second->m_pDeclarator->m_pType->GetFunction()->Equals(*pDeclarator->m_pType->GetFunction());
								}
								else	// overloaded function
#endif
								{
									//CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);
									declaratorList = new CDeclaratorList(pDeclarator, declaratorList);
								}
							}
							else
							{
								Type* pType = (*decli).second->m_pType;

								if (pType->get_Kind() != pDeclarator->m_pType->get_Kind())
								{
								//	serror() << pDeclarator->m_sourcefile->ToString() << paren(pDeclarator->m_sourceline+1);
								//	serror() << "'" << pDeclarator->m_name << "' Already declared as something else\n";
									//ASSERT(0);
								}
								else
								{
									if (pType->get_Kind() == type_typedef)
									{
										if (((Typedef*)pType)->m_pType != ((Typedef*)pDeclarator->m_pType)->m_pType)
										{
										//	serror() << pDeclarator->m_sourcefile->ToString() << paren(pDeclarator->m_sourceline+1);
										//	serror() << "'" << pDeclarator->m_name << "' Already declared as something else\n";
										//	ASSERT(0);
										}
									}
									else
									{
									//	ASSERT(0);
									}
								}

								/*
								if (! pType->Equals(*pDeclarator->m_pType))
								{
									printf("'%s' Already declared as something else\n", pDeclarator->m_name->c_str());
								}
								else
								{
									// TODO ? (like above)
								}
								*/
							}
						}
					}
					else
					{
						//CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);
						pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));

						pDeclarator->m_defined = !bExtern && (pDeclarator->m_pType->get_Kind() != type_function);
						//pDeclarator->m_pOwnerScope->m_orderedDecls.push_back(pDeclaratorRef);

						declaratorList = new CDeclaratorList(pDeclarator, declaratorList);

						if (pInnermostClass == NULL && pDeclarator->m_defined)
						{
							pGlobal->m_globals.Add(pDeclarator);
						}

						if (pDeclarator->m_typedef)
						{

							/*
							if (pScope->m_pParentScope)
								pTypedef->m_qname = *(*GetQualifiedName(pScope) + "::") + *pTypedef->m_name;
							else
								pTypedef->m_qname = pTypedef->m_name;
								*/

					//		printf("typedef %s\n", pTypedef->m_name->c_str());

							pScope->m_types.insert(typemap::value_type(pDeclarator->m_name, (NamedType*)pDeclarator->m_pType));

							if (true)
							{
								pGlobal->m_alltypes.push_back((NamedType*)pDeclarator->m_pType);

							//	pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
							}
						}
					}
				}
				else
				{
					Std::Out << ("declarator->name = NULL\n");
				}
			}

			declp = declp->tail;
		}
	}

	return declaratorList;
}

static void parse_Translate(ast::Declaration* d, CGlobal* pGlobal, Scope* pScope, Scope* pTScope, int linkage)
{
	if (d->GetKind() == ast::Declaration::A_FUNDEF)
	{
	}
#if 0
	else if (d->GetKind() == ast::Declaration::A_TEMPLATE)
	{
		/*
		Scope* pScope2 = T_Scope();
		pScope2->m_pParentScope = pScope;

		ast::A_TemplateParameterList * tp = d->TEMPLATE.params;
		while (tp)
		{
			TemplateArgType * pType = new TemplateArgType();
			pType->m_name = tp->head->id;
			pScope2->m_types.insert(typemap::value_type(pType->m_name, pType));

			tp = tp->tail;
		}
		*/

		ast::A_TemplateDeclaration* td = (ast::A_TemplateDeclaration*)d;
		td->m_params = Reverse(td->m_params);

		if (td->m_decl->GetKind() == ast::A_Declaration::ast::A_SIMPLE)
		{
			SimpleDeclaration((ast::A_SimpleDeclaration*)td->m_decl, pGlobal, pScope, NULL, td->m_params, true);
		}
		else
		{
			// TODO fundef
		}
	}
#endif
	else if (d->GetKind() == ast::Declaration::A_SIMPLE)
	{
		SimpleDeclaration((ast::A_SimpleDeclaration*)d, pGlobal, pScope, NULL, pTScope/*NULL, false*/);
	}
	else if (d->GetKind() == ast::Declaration::A_NAMESPACE)
	{
		String name = static_cast<ast::NamespaceDefinition*>(d)->m_name;

		namespacemap::iterator it = pScope->m_namespaces.find(name);
		if (it != pScope->m_namespaces.end())
		{
			Namespace* pNamespace = (*it).second;

			g_pScope = pNamespace->m_pScope;
	//		g_pScope1 = g_pScope;
			g_pScope2 = g_pScope;
//			g_pLastScope = g_pScope;

		//	Translate(((ast::A_NamespaceDefinition*)d)->m_declarationList, pGlobal, pNamespace->m_pScope, linkage);
		}
		else
		{
			Namespace* pNamespace = new Namespace;
			pNamespace->m_name = name;
		//	pNamespace->m_pScope->m_name = pNamespace->m_name;

			pNamespace->m_pScope->m_pParentScope = pScope;
			pScope->m_subScopes.push_back(pNamespace->m_pScope);
			pScope->m_namespaces[pNamespace->m_name] = pNamespace;

			g_pScope = pNamespace->m_pScope;
//			g_pScope1 = g_pScope;
			g_pScope2 = g_pScope;
//			g_pLastScope = g_pScope;

		//	Translate(((ast::A_NamespaceDefinition*)d)->m_declarationList, pGlobal, pNamespace->m_pScope, linkage);
		}
	}
	else
	{
		ASSERT(0);
	}
}

void Do(ast::ExpressionList* attribute_spec, ast::Declaration* d)
{
	//ast::A_Declaration* d = expordecl->m_decl;

	d->m_attributes = attribute_spec;

#if 0
	if (d->GetKind() == ast::A_Declaration::ast::A_TEMPLATE)
	{
		ast::A_TemplateDeclaration* td = (ast::A_TemplateDeclaration*)d;
	//	td->m_params = Reverse(td->m_params);

		Scope* pTScope;
		pTScope = new Scope;
		pTScope->m_pParentScope = g_pScope;//pClass->m_pScope->m_pParentScope;
#if 0
		pClass->m_pScope->m_pParentScope = pTScope;
#endif
		
		//ast::A_TemplateParameterList * tplist = tp;
		
		/*
		// Reverse list
		{
		ast::A_TemplateParameterList * tp2 = tp;
		while (tp2)
		{
		tplist = new ast::A_TemplateParameterList(tp2->head, tplist);
		tp2 = tp2->tail;
		}
		}
		*/
		
		int index = 0;
		ast::A_TemplateParameterList* tp = td->m_params;
		//ast::A_TemplateParameterList * tp = d->TEMPLATE.params;
		while (tp)
		{
			if (tp->head->GetKind() == ast::A_TemplateParameter::ast::A_ParamType)
			{
				ast::A_TypeTemplateParameter* typeparam = (ast::A_TypeTemplateParameter*)tp->head;
				
				TemplateParameter* param = new TemplateParameter;
				param->m_kind = TemplateParameter::Param_Type;
				param->m_index = index;
				
				_TemplateArgType* pType = new _TemplateArgType();
				//pType->m_kind = _TemplateArgType::Arg_Type;
				pType->m_pOwnerScope = pTScope;
				pType->m_index = index;
				pType->m_name = typeparam->m_id;
				
				param->m_pType = pType;
				
				if (typeparam->m_typeId)
				{
					ASSERT(0);
#if 0
					pType->m_defaultArg = new TemplatedClassArg;
					pType->m_defaultArg->m_pType = GetType(typeparam->m_typeId->declspecList, pGlobal, pClass->m_pScope, NULL/*tp ?*/, true);
#endif
				}
				
#if 0
				pClass->m_items.push_back(param);
#endif
				
				pTScope->m_types.insert(typemap::value_type(pType->m_name, pType));
			}
			else
			{
				ast::A_DeclaratorTemplateParameter* declparam = (ast::A_DeclaratorTemplateParameter*)tp->head;
				
				CDeclarator* pDeclarator = new CDeclarator;
				pDeclarator->m_pType = GetType(declparam->m_decls, g_pGlobal, g_pScope/*pClass->m_pScope*/ /*pTScope*//*pScope*/, NULL/*tp*/, true);//NULL;//d->fundef.declspecList
				declparam->m_declarator->Extract(pDeclarator, pDeclarator->m_pType, g_pScope/*pClass->m_pScope*/ /*pTScope*//*pScope*/, g_pGlobal);
				
				/*
				__live_object_ptr<_TemplateArgType> pArg;
				pArg = new _TemplateArgType();
				pArg->m_kind = _TemplateArgType::Arg_Value;
				pArg->m_pOwnerScope = pTScope;
				pArg->m_index = index++;
				pArg->m_name = pDeclarator->m_name;
				pArg->m_pTypeOfValue = pDeclarator->m_pType;
				*/
				
				TemplateParameter* param = new TemplateParameter;
				param->m_index = index;
				param->m_kind = TemplateParameter::Param_Value;
				
				param->m_pDeclarator = pDeclarator;
				
#if 0
				pClass->m_items.push_back(param);
#endif
				
				g_pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
			}
			
			index++;
			
			tp = tp->tail;
		}

		ast::A_ExpOrDecl* expordecl = PrimList(ptoken, g_pGlobal->m_pGlobalScope, pTScope);
		
		td->m_decl = expordecl->m_decl;

		if (td->m_decl->GetKind() == ast::A_Declaration::ast::A_SIMPLE)
		{
			SimpleDeclaration((ast::A_SimpleDeclaration*)td->m_decl, g_pGlobal, g_pScope, NULL, td->m_params, true);
		}
		else
		{
			// TODO fundef
		}

	}
	else
#endif
	{
		parse_Translate(d, g_pGlobal, g_pScope, g_pScope2, 1/*C++*/);
	}
}

void Do(ast::A_ClassDef* CLASSDEF)
{
	ast::A_BaseSpecifierList* baseList = CLASSDEF->m_baseList;
	while (baseList)
	{
		BaseClass* baseClass = new BaseClass;
		
		Type* pType2;
		
#if 0
		if (baseList->head->kind == ast::Expression::ast::A_ID)
		{
			pType2 = pClass->m_pScope->GetType(baseList->head->id);
			baseClass.m_pClass = pType2->GetClass();
		}
		else if (baseList->head->kind == ast::Expression::ast::A_TEMPLATEID)
		{
			//	pType2 = pTScope->GetType(baseList->head->id);
			System::Type pTemplateClass = pClass->m_pScope->GetType(baseList->head->templateid.exp->id);
			ASSERT(pTemplateClass->m_type == type_class);
			
			TemplatedClassType* pTType = new TempatedClass;
			pTType->AddRef();
			
			pTType->m_pClass = pTemplateClass->GetClass();
			pTType->m_pClass->AddRef();
			
			ast::A_TypeIdList* typeIds = baseList->head->templateid.params;
			while (typeIds)
			{
				ast::A_TypeId* typeId = typeIds->head;
				
				System::Type pTemplateArgType = GetType(typeId->declspecList, pGlobal, pClass->m_pScope, tp, bInsideTemplate);
				//pTemplateArgType->
				
				pTType->m_templateArgs.Add(pTemplateArgType);
				
				typeIds = typeIds->tail;
			}
			
			pType2 = pTType;
			
			baseClass.m_pClass = pTType;
		}
		else
		{
			Scope* pScope2 = GetNestedScope(NULL/*pGlobal*/, pClass->m_pScope/*pTScope*/, baseList->head->binop.left);
			if (pScope2 == NULL)
			{
				printf("undeclared base class %s\n", baseList->head->binop.right->id);
				//exit(1);
				break;
			}
			
			pType2 = pScope2->GetType(baseList->head->binop.right->id);
			
			baseClass.m_pClass = pType2->GetClass();
		}
#endif
		pType2 = parse_GetNestedType(g_pGlobal, NULL, g_pClass->m_pScope, baseList->head->m_id);
		
		if (pType2 == NULL)
		{
			if (baseList->head->m_id->kind == ast::Expression::A_ID)
			{
				pType2 = g_pClass->m_pScope/*pTScope*/->GetType(baseList->head->m_id->templateid.id);
				Std::Out << "undeclared base class " << CString(baseList->head->m_id->templateid.id).c_str() << "\n";
			}
			else
				Std::Out << ("undeclared base class\n");
			//exit(1);
			ASSERT(0);
			break;
		}
		
		baseClass->m_pClass = (ClassType*)pType2;
		ASSERT(baseClass->m_pClass);
		/*
		if (pType2->m_type != type_class)
		{
		printf("base class is not a class\n");
		//exit(1);
		break;
		}
		*/
		
		{
			//	baseClass.m_offset = pClass->get_sizeof();
			//	pClass->m_sizeof += baseClass.m_pClass->get_sizeof();
		}
		
		g_pClass->AsClass()->m_bases.push_back(baseClass);
		
		baseList = baseList->tail;
	}
}

void Do_TParam(ast::TemplateParameter* tp, ast::Expression* initexp)
{
	if (tp->GetKind() == ast::TemplateParameter::A_ParamType)
	{
		ast::TypeTemplateParameter* typeparam = static_cast<ast::TypeTemplateParameter*>(tp);

		FormalTemplateArg* param = new FormalTemplateArg;
		param->m_kind = FormalTemplateArg::Param_Type;

		_TemplateArgType* pType = new _TemplateArgType();
		pType->m_ownerScope = g_pScope2;
		pType->m_name = typeparam->m_id;
		
		param->u.m_pType = pType;
		
		if (typeparam->m_typeId)
		{
			pType->m_defaultArg = new TemplatedClassArg;
			pType->m_defaultArg->m_pType = parse_GetType(typeparam->m_typeId->m_declspecList, g_pGlobal, g_pScope, g_pScope2);///*pClass->m_pScope*/, NULL/*tp ?*/, true);
		}
		
		templateParams->m_items.push_back(param);

		g_pScope2->m_types.insert(typemap::value_type(pType->m_name, pType));
	}
	else if (tp->GetKind() == ast::TemplateParameter::A_ParamDeclarator)
	{
		ast::DeclaratorTemplateParameter* declparam = static_cast<ast::DeclaratorTemplateParameter*>(tp);

		declparam->m_defaultValue = initexp;

		Declarator* pDeclarator = new Declarator;
		pDeclarator->m_pType = parse_GetType(declparam->m_decls, g_pGlobal, g_pScope, g_pScope2);///*pClass->m_pScope*/ /*pTScope*//*pScope*/, NULL/*tp*/, true);//NULL;//d->fundef.declspecList
		declparam->m_declarator->Extract(pDeclarator, pDeclarator->m_pType, g_pScope, g_pScope2 /*pClass->m_pScope*/ /*pTScope*//*pScope*/, g_pGlobal);
		
		FormalTemplateArg* formalArg = new FormalTemplateArg;
	//	param->m_index = index;
		formalArg->m_kind = FormalTemplateArg::Param_Value;
		
		formalArg->u.m_pDeclarator = pDeclarator;

		if (initexp)
		{
			if (initexp->GetKind() == Expression::A_INT32)
			{
				formalArg->m_defaultArg.int32Val = initexp->u.int32Val;

			//	pType->m_defaultArg = new TemplatedClassArg;
			//	pType->m_defaultArg->m_pType = parse_GetType(typeparam->m_typeId->m_declspecList, g_pGlobal, g_pScope, g_pScope2);///*pClass->m_pScope*/, NULL/*tp ?*/, true);

			}
			else
				ASSERT(0);
		}

		templateParams->m_items.push_back(formalArg);
		
		g_pScope2->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
	}
	else
		ASSERT(0);
}

void DoTp(ast::TemplateDeclaration* td)
{
	ASSERT(templateParams == NULL);

	templateParams = NULL;//.clear();
	templateParams = new TemplateParams;

	Scope* pTScope;
	pTScope = new Scope;
	pTScope->m_pParentScope = g_pScope;//pClass->m_pScope->m_pParentScope;
//	pTScope->m_name = new StringA("Template");

	//td->m_params = Reverse(td->m_params);

#if 0
	int index = 0;
	//tp = tplist;
	ast::A_TemplateParameterList * tp = td->m_params;
	while (tp)
	{
		if (tp->head->GetKind() == ast::A_TemplateParameter::ast::A_ParamType)
		{
			ast::A_TypeTemplateParameter* typeparam = (ast::A_TypeTemplateParameter*)tp->head;

			TemplateParameter* param = new TemplateParameter;
			param->m_kind = TemplateParameter::Param_Type;
			param->m_index = index;

			_TemplateArgType* pType = new _TemplateArgType();
			//pType->m_kind = _TemplateArgType::Arg_Type;
			pType->m_pOwnerScope = pTScope;
			pType->m_index = index;
			pType->m_name = typeparam->m_id;
			
			param->m_pType = pType;
			
			if (typeparam->m_typeId)
			{
				pType->m_defaultArg = new TemplatedClassArg;
				pType->m_defaultArg->m_pType = GetType(typeparam->m_typeId->declspecList, g_pGlobal, g_pScope, g_pScope2);///*pClass->m_pScope*/, NULL/*tp ?*/, true);
			}
			
			/*pClass->m_*/templateParams.push_back(param);

			pTScope->m_types.insert(typemap::value_type(pType->m_name, pType));
		}
		else
		{
			ast::A_DeclaratorTemplateParameter* declparam = (ast::A_DeclaratorTemplateParameter*)tp->head;
			
			CDeclarator* pDeclarator = new CDeclarator;
			pDeclarator->m_pType = GetType(declparam->m_decls, g_pGlobal, g_pScope, g_pScope2);///*pClass->m_pScope*/ /*pTScope*//*pScope*/, NULL/*tp*/, true);//NULL;//d->fundef.declspecList
			declparam->m_declarator->Extract(pDeclarator, pDeclarator->m_pType, g_pScope, g_pScope2 /*pClass->m_pScope*/ /*pTScope*//*pScope*/, g_pGlobal);
			
			TemplateParameter* param = new TemplateParameter;
			param->m_index = index;
			param->m_kind = TemplateParameter::Param_Value;
			
			param->m_pDeclarator = pDeclarator;
		
#if 1
			/*pClass->m_*/ templateParams.push_back(param);
#endif
			
			pTScope /* g_pScope*/ ->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
		}
		
		index++;
		
		tp = tp->tail;
	}
#endif

	//pTScope->m_name = new StringA("Template");

//	g_pScope = pTScope;
//	g_pScope1 = pTScope;
	g_pScope2 = pTScope;
//	g_pLastScope = pTScope;
}

#if 0
void Do_elaborated_class(ast::A_Class* elaborated_class)
{
	ast::A_ClassHead* head = elaborated_class->m_head;

	Type* pType = NULL;

	if (head->m_name != NULL)
	{
		//typemap::iterator it = pScope->m_types.find(CLASSDEF->m_head->m_name);
		
		Type* pType2 = parse_GetNestedType(g_pGlobal, NULL, g_pScope, head->m_name);
		
		//if (it != pScope->m_types.end())
		if (pType2)
		{
			pType = pType2;//(*it).second;//pScope->GetType(decl->CLASSDEF.head->name);
			class2type[head] = pType;
		}
		else
			pType = NULL;//System::Type();
	}
	else
		pType = NULL;//System::Type();
	
	ClassType* pClass = NULL;
	
	if (pType != NULL)
	{
		if (pType->GetKind() == type_class)
		{
			pClass = pType->GetClass();
			//	pClass->AddRef();
			
			if (pClass->m_kwType != head->m_classKey)
			{
				printf("'%s ()' first seen as %s\n", ClassKeyName(head->m_classKey), /*CLASSDEF->m_head->m_name->c_str(),*/ ClassKeyName((ClassKey)pClass->m_kwType));
			}
			else
			{
				if (pClass->m_sizeof != -1)
				{
					printf("class '' already defined\n"/*, CLASSDEF->m_head->m_name->c_str()*/);
				}
			}
		}
		else
		{
			printf("Already declared as something else");
		}
	}
	else
	{
		pClass = new ClassType;
		pType = pClass;
		//		pType->m_type = type_class;
		//		pType->m_pClass = new Class;
		//	pClass->AddRef();

		class2type[head] = pType;
		
		pClass->m_pOwnerScope = g_pScope;
		//pClass->m_pScope->m_pParentScope = g_pScope;	// hmm..

		pClass->m_pScope->m_pParentScope = g_pScope2;

		//ASSERT(0);
#if 0
		pClass->m_location.m_line = type->CLASSDEF.head->line_pos;
#endif
		pClass->m_kwType = head->m_classKey;
		
		if (head->m_name != NULL)
		{
		
			pClass->m_name = head->m_name->binop.left->templateid.id;
			pClass->m_pScope->m_name = pClass->m_name;
			//	pType->m_pNamedType->m_name = type->CLASSDEF.head->name;
			
			//	pClass->m_qname = GetQualifiedName(pClass->m_pScope);
			
			CDeclarator* pDeclarator = new CDeclarator;
			pDeclarator->m_typedef = true;
			pDeclarator->m_name = pClass->m_name;
			pDeclarator->m_pType = pClass;
			
			ASSERT(g_pScope != pClass->m_pScope);

			//	CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);
			g_pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
			g_pScope->m_orderedDecls.Add(pDeclarator);
			g_pScope->m_types.insert(typemap::value_type(pClass->m_name, pClass));
			
			//	pGlobal->m_alltypes.insert(typemap::value_type(pClass->m_qname, pClass));
			//	pGlobal->m_types.Add(pClass);
		}
	}
	
	pClass->m_def = true;

#if 0
	g_pClass = pClass;
#endif

	pClass->m_pTemplateParams = templateParams;
	templateParams = NULL;//.clear();
}
#endif

void Do_class_specifier_head(ast::A_ClassHead* head)
{
	Type* pType = nullptr;

	if (head->m_name != nullptr)
	{
		//typemap::iterator it = pScope->m_types.find(CLASSDEF->m_head->m_name);
		
		Type* pType2 = parse_GetType(g_pGlobal, nullptr, g_pScope, head->m_name);
		
		//if (it != pScope->m_types.end())
		if (pType2)
		{
			pType = pType2;//(*it).second;//pScope->GetType(decl->CLASSDEF.head->name);
			class2type[head] = pType;
		}
		else
			pType = nullptr;
	}
	else
		pType = nullptr;
	
	ClassType* pClass = nullptr;
	
	if (pType != nullptr)
	{
		if (pType->get_Kind() == type_class)
		{
			pClass = pType->AsClass();
			
			if (pClass->m_kwType != head->m_classKey)
			{
				Console::get_Out() << head->m_filename << paren(head->m_line_pos+1) << " : warning C4099 : " << ClassKeyName(head->m_classKey) << " first seen as " << ClassKeyName((ClassKey)pClass->m_kwType) << "\n";
			}
			else
			{
				if (pClass->m_sizeof != -1)
				{
					Console::get_Out() << ("class '' already defined\n"/*, CLASSDEF->m_head->m_name->c_str()*/);
				}
			}
		}
		else
		{
			Console::get_Out() << "Already declared as something else" << "\n";
		}
	}
	else
	{
		pClass = new ClassType();
		pType = pClass;

		class2type[head] = pType;
		
		pClass->m_ownerScope = g_pScope;
		pClass->m_pScope->m_pParentScope = g_pScope2;
		pClass->m_kwType = head->m_classKey;
		
		if (head->m_name != NULL)
		{
			pClass->m_name = head->m_name->binop.left->templateid.id;

			Declarator* pDeclarator = new Declarator(pClass, pClass->m_name);
			pDeclarator->m_typedef = true;
			pClass->m_ownerDecl = pDeclarator;
			
			ASSERT(g_pScope != pClass->m_pScope);

			g_pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
			g_pScope->m_orderedDecls.Add(pDeclarator);
			g_pScope->m_types.insert(typemap::value_type(pClass->m_name, pClass));
		}
	}
	
	pClass->m_def = true;

	g_pClass = pClass;
	
	pClass->m_pTemplateParams = templateParams;
	templateParams = NULL;//.clear();
}

void DoImport(StringA* filename)
{
	IO::FileStream file(filename, IO::FileMode_Open, IO::FileAccess_Read);
	TypeArchive ar(TypeArchive::Mode_Load, &file, filename);

	ar.m_typestuff = new TypeStuff;
	ar.m_bSortedDecls = true;
	ar.m_pGlobalNamespace = g_pGlobal->m_namespace;

	ar.m_typelib = new TypeLib;
	//ar.m_typelib->m_typelib = new TypeLib;
	ar.ReadHeader();
	ar.MapObject(ar.m_typelib);
	ar.m_typelib->Load(ar);

#if 0
	ar >> ar.m_typelib;
//	pGlobal->m_typelibs.Add(ar.typelib);

	uint ntypelibs;
	ar >> ntypelibs;
	{
		for (uint i = 0; i < ntypelibs; i++)
		{
			TypeLib* typelib;
			ar >> typelib;
		}
	}

	Namespace* globalNamespace;
	ar >> globalNamespace;

	int ntypes;
	ar >> ntypes;

	for (int i = 0; i < ntypes; i++)
	{
		NamedType* pType;
		ar >> pType;

		ASSERT(pType->m_ownerScope->m_decls.find(pType->m_name) != pType->m_ownerScope->m_decls.end());

	//	g_pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
	//	g_pScope->m_orderedDecls.Add(pDeclarator);
	//	g_pScope->m_types.insert(typemap::value_type(pType->m_name, pType));

	}

	{
		for (int i = 0; i < ntypes; i++)
		{
			ULONG_PTR address;
			ar >> address;
		}
	}
#endif

	/*
	{
		int indefines;
		ar >> indefines;

		for (int i = 0; i < indefines; i++)
		{
			CDefine* pDefine;
			ar >> pDefine;
		}
	}

	{
		int outdefines;
		ar >> outdefines;

		for (int i = 0; i < outdefines; i++)
		{
			CDefine* pDefine;
			ar >> pDefine;
		}
	}
	*/

//	file.Close();
}

}	// ast
}	// cpp
}	// System
