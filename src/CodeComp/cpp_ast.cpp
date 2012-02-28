#include "stdafx.h"
#include "Comp2.h"
#include "cpp_ast.h"
#include "cpp_compile.h"
#include "cpp_translate.h"	// TODO, not here ?

#include "preprocessor.h"		// TODO, not here ?

#include "ir.h"	// TODO, not here ?

namespace System
{
//using namespace std;

LFCEXT Type* GetType(ClassType* pClass, StringIn name);

LFCEXT IO::TextWriter& printlevels(IO::TextWriter& fp, int levels);

namespace cpp
{

_Ptr<IO::TextWriter> serror();

void quadruples(T_Exp* exp);
void quadruples(T_Stm* stm);

T_Exp* totemp(T_Exp* exp)
{
	if (exp->kind == T_Exp::T_BINOP)
	{
		Temp_temp** t = new Temp_temp*;
		*t = new Temp_temp;

		T_Exp* eseq = T_ESeq(T_MoveStm(T_Temp(t), exp), T_Temp(t));

		exp->binop.left = totemp(exp->binop.left);
		exp->binop.right = totemp(exp->binop.right);

	//	quadruples(exp->binop.left);
	//	quadruples(exp->binop.right);

		return eseq;
	}
	else if (exp->kind == T_Exp::T_UNOP)
	{
		Temp_temp** t = new Temp_temp*;
		*t = new Temp_temp;

		T_Exp* eseq = T_ESeq(T_MoveStm(T_Temp(t), exp), T_Temp(t));

		quadruples(exp->unop.exp);

		return eseq;
	}
	else if (exp->kind == T_Exp::T_MEM)
	{
		Temp_temp** t = new Temp_temp*;
		*t = new Temp_temp;

		T_Exp* eseq = T_ESeq(T_MoveStm(T_Temp(t), exp), T_Temp(t));

		exp->mem.mem = totemp(exp->mem.mem);

		return eseq;
	}
	else if (exp->kind == T_Exp::T_ADDRESSOF)
	{
		Temp_temp** t = new Temp_temp*;
		*t = new Temp_temp;

		T_Exp* eseq = T_ESeq(T_MoveStm(T_Temp(t), exp), T_Temp(t));

		exp->addressof = totemp(exp->mem.mem);

		return eseq;
	}
}

void quadruples(T_Exp* exp)
{
	if (exp->kind == T_Exp::T_ESEQ)
	{
		quadruples(exp->eseq.s);
		quadruples(exp->eseq.e);
	}
	else if (exp->kind == T_Exp::T_BINOP)
	{
		exp->binop.left = totemp(exp->binop.left);
		exp->binop.right = totemp(exp->binop.right);
	}
	else if (exp->kind == T_Exp::T_UNOP)
	{
		exp->unop.exp = totemp(exp->unop.exp);
	}
	else if (exp->kind == T_Exp::T_MEM)
	{
		exp->mem.mem = totemp(exp->mem.mem);
	}
	else if (exp->kind == T_Exp::T_ADDRESSOF)
	{
		exp->addressof = totemp(exp->addressof);
	}
	else if (exp->kind == T_Exp::T_CALL)
	{
		ArgList* args = exp->call.args;
		//exp->mem.mem = totemp(exp->mem.mem);
		while (args)
		{
			args->head = totemp(args->head);

			args = args->tail;
		}
	}
}

void quadruples(T_Stm* stm)
{
	if (stm->kind == T_Stm::T_SEQ)
	{
		quadruples(stm->seq.left);
		quadruples(stm->seq.right);
	}
	else if (stm->kind == T_Stm::T_MOVE)
	{
		quadruples(stm->move.left);
		quadruples(stm->move.right);
	}
	else if (stm->kind == T_Stm::T_EXP)
	{
		quadruples(stm->exp);
	}
}

void print(T_Stm* s);
void print(T_StmList* slist);

System::Type* TemplateArgs::GetType(System::Type* pType) const
{
	if (pType->get_Kind() == System::type_templatearg)
	{
		System::_TemplateArgType * pTType = (System::_TemplateArgType*)pType;

//		pTType->m_pClass;

	//	ASSERT(m_args);
	//	if (m_args == NULL)
	//		return NULL;

		const TemplateArgs* pArgs = this;

	//	while (pArgs->m_parent)
	//		pArgs = pArgs->m_parent;
	
		while (pArgs->m_pTemplateParams != pTType->m_pClass)
		{
			pArgs = pArgs->m_parent;
		}
		ASSERT(pArgs);

	//	if (pArgs->m_pInstanceArgs->m_pClass->m_pTemplateParams == pTType->m_pClass)
			return pArgs->m_pInstanceArgs->m_items[pTType->m_index]->m_pType;
	//	else
	//		return pTType;

#if 0
		/*
		if (m_args[pTType->m_index]->GetKind() == type_templatearg)
			return m_parent->GetType(m_args[pTType->m_index]);
		else
		*/
		if (pArgs->m_pInstanceArgs->m_items.size())
			return pArgs->m_pInstanceArgs->m_items[pTType->m_index]->m_pType;
		else
			return pTType;

		return m_pInstanceArgs->m_items[pTType->m_index]->m_pType;
		return m_parent->GetType(m_pInstanceArgs->m_items[pTType->m_index]->m_pType);
#endif
	}
	else
	{
		return pType;
	}
}

#if 0

void SetReadOnly(Type* pType)
{
	pType->m_readonly = true;

	switch (pType->get_Kind())
	{
	case type_pointer:
	case type_cv:
		SetReadOnly(pType->GetPointerTo());
		break;

	case type_typedef:
		SetReadOnly(((Typedef*)pType)->m_pType);
		break;

	case type_array:
		SetReadOnly(((ArrayType*)pType)->get_ElemType());
		break;

	case type_class:
		{
			if (((ClassType*)pType)->m_pInstantiatedFromClass)
			{
				SetReadOnly(((ClassType*)pType)->m_pInstantiatedFromClass);
			}
		}
		break;
	}
}
#endif

//FILE* outfile;

Tr_Exp* ConvertExpressionType(Tr_Exp* pExpr, System::Type* p2Type, bool b2Const = false);
extern vector<T_Declarator*> tglobals;
extern map<System::Declarator*, T_Declarator*> labels;

System::PointerType* CreatePointerType(CGlobal* pGlobal, System::Type* pPointerTo)
{
	PointerTypes::iterator it = pGlobal->m_pointer_Types.find(pPointerTo);
	if (it != pGlobal->m_pointer_Types.end())
	{
		return it->second;
	}
	else
	{
		System::PointerType* type = new PointerType(pPointerTo);
		pGlobal->m_pointer_Types.insert(PointerTypes::value_type(pPointerTo, type));

		return type;
	}
}

System::ReferenceType* CreateReferenceType(CGlobal* pGlobal, Type* pPointerTo)
{
	ReferenceTypes::iterator it = pGlobal->m_reference_Types.find(pPointerTo);
	if (it != pGlobal->m_reference_Types.end())
	{
		return it->second;
	}
	else
	{
		System::ReferenceType* type = new ReferenceType(pPointerTo);
		pGlobal->m_reference_Types.insert(ReferenceTypes::value_type(pPointerTo, type));

		return type;
	}
}

System::RValueReferenceType* CreateRValueReferenceType(CGlobal* pGlobal, Type* pPointerTo)
{
	RValueReferenceTypes::iterator it = pGlobal->m_rvalue_reference_Types.find(pPointerTo);
	if (it != pGlobal->m_rvalue_reference_Types.end())
	{
		return it->second;
	}
	else
	{
		System::RValueReferenceType* type = new RValueReferenceType(pPointerTo);
		pGlobal->m_rvalue_reference_Types.insert(RValueReferenceTypes::value_type(pPointerTo, type));

		return type;
	}
}

Declarator* testdecl;
	// TODO

System::ArrayType* newArrayType(CGlobal* pGlobal, System::Type* elemType, int nSize)
{
	System::ArrayOf arrayof;
	arrayof.m_elemType = elemType;
	arrayof.m_nSize = nSize;

	map<ArrayOf, ArrayType*>::iterator it = pGlobal->m_array_Types.find(arrayof);
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

T_Stm* TransStatement(T_Declarator* frame, ast::A_Stm* pstmt, System::Scope* pScope, CGlobal* pGlobal, CTSwitch* pInnermostSwitch, Temp_label* break_target);

_Ptr<IO::TextWriter> Log;

namespace ast
{

Type* GetType(DeclSpecList* declspecList, InitDeclaratorList* declaratorList, CGlobal* pGlobal, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams* tp, int linkage, bool bInsideTemplate);
//Scope* Extract(Declarator* pDeclarator, ast::A_DirectDeclarator* directDeclarator, Type* pType, Scope* pScope, Scope* pTScope, CGlobal* pGlobal);
//Scope* Extract(A_Declarator* a_declarator, Declarator* pDeclarator, Type* pType, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams* tp, CGlobal* pGlobal, bool bInsideTemplate);
Scope* Extract(ast::A_Declarator* a_Declarator, Declarator* pDeclarator, Type* pType, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams * tp, CGlobal* pGlobal, bool bInsideTemplate);

SExp* TransExpression(ast::Expression* exp, CGlobal* pGlobal, Scope* pScope)
{
	switch (exp->GetKind())
	{
		case ast::Expression::A_BOOL:
		{
			ASSERT(typeid(bool).GetType());
			return new SValExp(typeid(bool), exp->u.boolValue);
		}
		break;

		case ast::Expression::A_INT32:
		{
			ASSERT(typeid(int).GetType());

			return new SValExp(typeid(int), exp->u.int32Val);
		}
		break;

		case ast::Expression::A_UINT32:
		{
			ASSERT(typeid(unsigned).GetType());

			return new SValExp(typeid(unsigned int), exp->u.int32Val);
		}
		break;

		case ast::Expression::A_FLOAT:
		{
			return new SFloatExp(typeid(float), exp->u.floatValue);
		}
		break;

		case ast::Expression::A_DOUBLE:
		{
			return new SDoubleExp(typeid(double), exp->u.doubleValue);
		}
		break;

		case ast::Expression::A_CHAR_LITERAL:
		{
			return new SValExp(typeid(char), exp->u.int32Val);
		}
		break;

		case ast::Expression::A_SIZEOF_TYPE:
		{
			ast::SizeofTypeExp* se = dynamic_cast<ast::SizeofTypeExp*>(exp);

			Type* pType = ast::GetType(se->m_typeId->m_declspecList, nullptr, pGlobal, pScope, pScope, NULL, NULL, 0, false/*TODO*/);
			ASSERT(pType);

			Declarator pDeclarator;
			pDeclarator.m_pType = pType;
			ast::Extract(se->m_typeId->m_declarator, &pDeclarator, pType, pScope, pScope, NULL, NULL/*tp*/, pGlobal, false/*TODO*/);

			return new SValExp(typeid(unsigned int), pDeclarator.m_pType->get_sizeof(pGlobal->m_sizeofptr));
		}
		break;

		case ast::Expression::A_UNOP:
		{
			SExp* sexp = TransExpression(exp->unop.exp, pGlobal, pScope);

			if (sexp->GetKind() == SExp::SEXP_INT)
			{
				SValExp* valexp = dynamic_cast<SValExp*>(sexp);

				int value;
				switch (exp->unop.op)
				{
				case '-':
					value =  -valexp->m_val;
					break;

				case '!':
					value =  !valexp->m_val;
					break;

				case '~':
					value =  ~valexp->m_val;
					break;
				
				case '*':	// dereference
					{
						ASSERT(0);
					}
					break;

				case '&':	// take address of
					{
						ASSERT(0);
					}
					break;
				}

				return new SValExp(sexp->GetExpType(), value);
			}
			else
			{
				Console::get_Out() << __FILE__ << "(" << __LINE__ << ")" << "INTERNAL ERROR - Unknown SExp type" << endl;
			}
		}
		break;

		case ast::Expression::A_BINOP:
		{
			switch (exp->binop.op)
			{
			case '::':
				{
					if (exp->binop.left->kind == ast::Expression::A_TEMPLATEID)
					{
						Declarator* pDeclarator;

						ast::Expression* p = exp;
						do
						{
							if (pScope == NULL)
							{
								raise(Exception("undeclared identifier"));
							}

							pDeclarator = pScope->GetDeclarator(p->binop.left->templateid.id);
							if (pDeclarator == NULL)
							{
								break;
							}

							if (NamespaceType* pname = dynamic_cast<NamespaceType*>(pDeclarator->m_pType))
							{
								pScope = pname->m_pScope;
							}

							p = p->binop.right;
						}
						while (p);

						if (pDeclarator == NULL)
						{
							Console::Out << exp->m_filename << paren(exp->m_line_pos+1) << " : error : undeclared identifier '" << String(exp->binop.left->templateid.id) << "'" << "\n";
							//	printf(msg);
						//	printf(msg);
							++pGlobal->m_errors;
						}
						else
						{
							if (pDeclarator->m_localVar == 2)	// enum identifier
							{
								return new SValExp(pDeclarator->m_pType, pDeclarator->m_offset);
							}
							else
							{
								return new SArgExp(pDeclarator);

#if 0
								if (!/*pExpr->m_*/pDeclarator->m_referenced)
								{
									/*pExpr->m_*/pDeclarator->m_referenced = true;
									pGlobal->m_references.Add(/*pExpr->m_*/pDeclarator);
								}

								return DeclaratorExpression(frame, /*pExpr->m_*/pDeclarator);
#endif
							}
						}
					}
					else
						ASSERT(0);
				}
				break;

			default:
				{
					SExp* left = TransExpression(exp->binop.left, pGlobal, pScope);
					SExp* right = TransExpression(exp->binop.right, pGlobal, pScope);

					if (left == nullptr)
					{
						return nullptr;
					}

					if (right == nullptr)
					{
						return nullptr;
					}

					if (left->GetKind() == SExp::SEXP_INT && right->GetKind() == SExp::SEXP_INT)
					{
						SValExp* leftval = dynamic_cast<SValExp*>(left);
						SValExp* rightval = dynamic_cast<SValExp*>(right);

						int value;

						switch (exp->binop.op)
						{
						case '+':
							value = leftval->m_val + rightval->m_val;
							break;

						case '-':
							value = leftval->m_val - rightval->m_val;
							break;

						case '*':
							value = leftval->m_val * rightval->m_val;
							break;

						case '|':
							value = leftval->m_val | rightval->m_val;
							break;

						case '&':
							value = leftval->m_val & rightval->m_val;
							break;

						case '>>':
							value = leftval->m_val >> rightval->m_val;
							break;

						case '<<':
							value = leftval->m_val << rightval->m_val;
							break;

						case '/':
							{
								if (rightval->m_val == 0)
								{
									Console::get_Out() << exp->m_filename << paren(exp->m_line_pos+1) << "Division by zero" << "\n";
									++pGlobal->m_errors;
									value = 0;
								}
								else
								{
									value = leftval->m_val / rightval->m_val;
								}
							}
							break;

						case '%':
							{
								if (rightval->m_val == 0)
								{
									Console::get_Out() << exp->m_filename << paren(exp->m_line_pos+1) << "Division by zero" << "\n";
									++pGlobal->m_errors;
									value = 0;
								}
								else
								{
									value = leftval->m_val % rightval->m_val;
								}
							}
							break;

						default:
							Console::get_Err() << exp->m_filename << paren(exp->m_line_pos+1) << " : INTERNAL ERROR : unknown binop";
							raise(Exception("INTERNAL ERROR : unknown binop"));
						}

						return new SValExp(left->GetExpType(), value);
					}
					else
					{
						return new SBinopExp(left->m_pType, left, right);
					}
				}
			}
		}
		break;

		case ast::Expression::A_CAST:
		{
			ast::CastExpression* castexp = dynamic_cast<ast::CastExpression*>(exp);

			Type* pType = ast::GetType(castexp->m_typeId->m_declspecList, NULL, pGlobal, pScope, pScope, NULL, NULL, 0, false/*TODO*/);
			ASSERT(pType);

			Declarator pDeclarator;
			pDeclarator.m_pType = pType;
			ast::Extract(castexp->m_typeId->m_declarator, &pDeclarator, pType, pScope, pScope, NULL, NULL/*tp*/, pGlobal, false/*TODO*/);

			if (castexp->m_exp)
			{
				SExp* right = TransExpression(castexp->m_exp, pGlobal, pScope);
//				if (right == NULL)
	//				return NULL;
			
			//	right = ConvertExpressionType(right, pDeclarator->m_pType);
			
				return right;
			}
		}
		break;

		case ast::Expression::A_INITCLAUSE:
		{
			InitClauseExp* ic = dynamic_cast<InitClauseExp*>(exp);

			ic->m_args;
			return NULL;
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

class FileLocation
{
public:
	CTOR FileLocation();
	CTOR FileLocation(StringIn filepath, int line);

	friend IO::TextWriter& operator << (IO::TextWriter& stream, const FileLocation& loc);

	String m_filepath;
	int m_line;
};

FileLocation::FileLocation()
{
}

FileLocation::FileLocation(StringIn filepath, int line) : m_filepath(filepath), m_line(line)
{
}

IO::TextWriter& operator << (IO::TextWriter& stream, const FileLocation& loc)
{
	stream << loc.m_filepath << paren(loc.m_line);
	return stream;
}

stack<FileLocation> g_filelocation;
stack<FileLocation> g_reffilelocation;

stack<ClassType*>	g_instantiatedTemplate;
stack<ClassType*>	g_instantiatedClass;

//	extern vector<Scope*> g_scopeStack;

System::Type* GetType(DeclSpecList* declspecList, InitDeclaratorList* declaratorList, CGlobal* pGlobal, System::Scope* pScope, System::Scope* pTScope, System::Declarator* fun, System::TemplateParams* tp, int linkage, bool bInsideTemplate);
CodeCompExt void FunBody(Declarator* pDeclarator, FunDefDecl* d, CGlobal* pGlobal, System::Scope* pScope, int linkage);
//T_Stm* T_Label(Temp_label* label);

//ClassType* InstantiateTemplate(Scope* pOwnerScope, CGlobal* pGlobal, TemplatedClassType* pTemplateClass, const TemplateArgs * templateArgs);

System::Scope* Extract(A_Declarator* a_declarator, System::Declarator* pDeclarator, System::Type* pType, System::Scope* pScope, System::Scope* pTScope, System::Declarator* fun, System::TemplateParams* tp, CGlobal* pGlobal, bool bInsideTemplate);

//TemplatedClassType * CreateClassInstance(CGlobal* pGlobal, ClassType* pTemplateClass, Scope* pScope, A_TemplateArgumentList * params2);
System::ClassType* CreateClassInstance2(CGlobal* pGlobal, ClassType* pTemplateClass, Scope* pScope, /*Scope* pTScope,*/ A_TemplateArgumentList* params2, bool bInsideTemplate);

#if 0
StringA* GetQualifiedName(Scope* pScope)
{
	ASSERT(pScope->m_pParentScope);

	if (pScope->m_pParentScope->m_pParentScope)
		return *(*GetQualifiedName(pScope->m_pParentScope) + "::") + *pScope->m_name;
	else
		return pScope->m_name;
}
#endif

FilePart* SplitPath(CGlobal* pGlobal, char* pathname)
{
	VerifyArgumentNotNull(pGlobal);
	
	if (pathname == NULL) return NULL;
	//VerifyArgumentNotNull(pathname);

	FilePart* lastpart = NULL;

	char* p = pathname;
	const char* partstart = pathname;
	do
	{
		if (*p == '\\')
		{
			*p = '/';
		}

		if (*p == '/' || *p == 0)
		{
			String str = String(string_copy(pathname, p - pathname));
			String partstr = String(string_copy(partstart, p - partstart));

			FilePart* part;

			map<String, FilePart*>::iterator part_it = pGlobal->m_files.find(str);
			if (part_it == pGlobal->m_files.end())
			{
				part = new FilePart;
				part->m_fullname = str;
				part->m_name = partstr;
				pGlobal->m_files.insert(map<String, FilePart*>::value_type(part->m_fullname, part));

				if (lastpart)
				{
					part->m_parent = lastpart;
					part->m_parent_it = lastpart->m_children.m_list.insert(lastpart->m_children.m_list.end(), part);
				}
			}
			else
				part = part_it->second;

			lastpart = part;

			partstart = p+1;

			if (*p == 0)
			{
				break;
			}
		}

		++p;
	}
	while (1);

	return lastpart;
}

Type* LookupTypeName(Scope* pScope, StringIn name)
{
//	ASSERT(name != null);
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

Type* LookupTypeNameRecurse(Scope* pScope, StringIn name)
{
	Type* pType = LookupTypeName(pScope, name);
	if (pType != NULL)
		return pType;

	if (pScope->m_pParentScope)
		return LookupTypeNameRecurse(pScope->m_pParentScope, name);

	return NULL;
}

Scope* LookupScopeNameRecurse(Scope* pScope, StringIn name);

Scope* LookupScopeName(Scope* pScope, StringIn name)
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
			pType = pType->GetStripped();

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
	}
	else
	{
		typemap::iterator type_it = pScope->m_types.find(name);
		if (type_it != pScope->m_types.end())
		{
			Type* pType = (*type_it).second->GetStripped();

			if (pType->get_Kind() == type_class)
			{
				return static_cast<ClassType*>(pType)->m_pScope;
			}
			else if (pType->get_Kind() == type_templatearg)
			{
				return static_cast<_TemplateArgType*>(pType)->m_pScope;
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

Scope* LookupScopeNameRecurse(Scope* pScope, StringIn name)
{
	Scope* pScope2 = LookupScopeName(pScope, name);
	if (pScope2)
		return pScope2;

	ASSERT(pScope->m_pParentScope != pScope);

	if (pScope->m_pParentScope)
		return LookupScopeNameRecurse(pScope->m_pParentScope, name);

	return NULL;
}

Scope* GetNestedScope(CGlobal* pGlobal, Scope* pGlobalScope, Scope* pScope, Expression* exp)
{
	/*
	if (exp->kind == Expression::A_ID)
	{
		Scope* pScope = LookupScopeNameRecurse(pScope, exp->id);
	}
	else
	*/

	/*
	if (exp->kind == Expression::A_TEMPLATEID)
	{
		pScope = LookupScopeNameRecurse(pScope, exp->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		left = exp;
	}
	else
	*/

	ASSERT(pScope != NULL);

	//Type* pType = NULL;

	ASSERT(exp->kind == Expression::A_BINOP);

	if (exp->binop.right)
	{
		Scope* pScope2 = LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);//pScope->GetType(exp->templateid.exp->id);

		if (pScope2 == NULL)
		{
			return NULL;
		}

		if (exp->binop.left->templateid.params)//kind == Expression::A_TEMPLATEID)
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
			pScope2 = LookupScopeName(pScope2, exp->binop.left->templateid.id);

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
		Scope* pScope2 = LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		return pScope2;
	}
}

Type* GetNestedType(CGlobal* pGlobal, Scope* pGlobalScope, Scope* pScope, Expression* exp, bool bInsideTemplate)
{
	/*
	if (exp->kind == Expression::A_ID)
	{
		Scope* pScope = LookupScopeNameRecurse(pScope, exp->id);
	}
	else
	*/

	/*
	if (exp->kind == Expression::A_TEMPLATEID)
	{
		pScope = LookupScopeNameRecurse(pScope, exp->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		left = exp;
	}
	else
	*/

	ASSERT(pScope != NULL);

	Type* pType = NULL;

	ASSERT(exp->kind == Expression::A_BINOP);

	if (exp->binop.right)
	{
		Scope* pScope2 = LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);//pScope->GetType(exp->templateid.exp->id);

		if (pScope2 == NULL)
		{
			return NULL;
		}

		if (pScope2->m_pNamespace->AsClass() && pScope2->m_pNamespace->AsClass()->m_pInstantiatedFromArgs)
		{
			pScope2 = pScope2->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pScope;
		}

		if (exp->binop.left->templateid.params)//kind == Expression::A_TEMPLATEID)
		{
			//TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);
			ClassType* pTType = CreateClassInstance2(pGlobal, pScope2->m_pNamespace->AsClass(), pScope/*pScope2->m_pClass->m_pOwnerScope*//*pScope*/, exp->binop.left->templateid.params, bInsideTemplate);

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
			pScope2 = pTType->m_pScope;
			//pScope2 = pTType->m_pInstantiatedFromArgs->m_pClass->m_pScope;

			if (pScope2 == NULL)
			{
				return NULL;
			}

			pType = pTType;
		}

		exp = exp->binop.right;

		while (exp->binop.right != NULL)
		{
			pScope2 = LookupScopeName(pScope2, exp->binop.left->templateid.id);

			if (pScope2 == NULL)
			{
				return NULL;
			}

			if (exp->binop.left->templateid.params)
			{
//				TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);
				ClassType* pTType = CreateClassInstance2(pGlobal, pScope2->m_pNamespace->AsClass(), pScope, exp->binop.left->templateid.params, bInsideTemplate);

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
				pScope2 = pTType->m_pScope;//InstantiatedFrom->m_pClass->m_pScope;
			//	pScope2 = pTType->m_pInstantiatedFromArgs->m_pClass->m_pScope;

				if (pScope2 == NULL)
				{
					return NULL;
				}

				pType = pTType;
			}

			exp = exp->binop.right;
		}

		pType = LookupTypeName(pScope2, exp->binop.left->templateid.id);
		if (pType == NULL)
		{
			ASSERT(pScope2->m_pNamespace);

			if (pScope2->m_pNamespace->get_Kind() == type_templatearg)
			{
				// Create the type
				Typedef* pTypedef = new Typedef(exp->binop.left->templateid.id, NULL);
				pTypedef->m_typelib = pGlobal->m_typelib;

			//	pTypedef->m_ownerScope = pClassType->m_pScope;
				pTypedef->m_ownerScope = pScope2;//ClassType->m_pScope;

				IO::StringWriter strbuilder;
				pTypedef->Write(strbuilder);
				pTypedef->m_qname = strbuilder.str();

				Declarator* decl = new Declarator;
				decl->m_typedef = true;
				decl->m_pType = pTypedef;
				decl->m_name = exp->binop.left->templateid.id;

				pScope2->m_orderedDecls.push_back(decl);
				pScope2->m_types.insert(typemap::value_type(pTypedef->m_name, pTypedef));

				pType = pTypedef;
			}
			else
			{
				ClassType* pClassType = pScope2->m_pNamespace->AsClass();

				if (pClassType && pClassType->m_HasTemplateArgs)
				{
					// Create the type
					Typedef* pTypedef = new Typedef(exp->binop.left->templateid.id, nullptr);
					pTypedef->m_typelib = pGlobal->m_typelib;

					pTypedef->m_ownerScope = pScope2;//pClassType->m_pScope;

					IO::StringWriter strbuilder;
					pTypedef->Write(strbuilder);
					pTypedef->m_qname = strbuilder.str();

					Declarator* decl = new Declarator;
					decl->m_typedef = true;
					decl->m_pType = pTypedef;
					decl->m_name = exp->binop.left->templateid.id;

				//	pClassType->m_pScope->m_orderedDecls.push_back(decl);
				//	pClassType->m_pScope->m_types.insert(typemap::value_type(pTypedef->m_name, pTypedef));
					pScope2->m_orderedDecls.push_back(decl);
					pScope2->m_types.insert(typemap::value_type(pTypedef->m_name, pTypedef));

					pType = pTypedef;
				}
			}
		}
	}
	else
	{
		if (exp->binop.left->templateid.id == NULL)
			return NULL;

		pType = LookupTypeNameRecurse(pScope, exp->binop.left->templateid.id);
	}

	if (exp->binop.left->templateid.params)//kind == Expression::A_TEMPLATEID)
	{
//		pType = CreateClassInstance(pGlobal, pType->GetClass(), pScope, exp->binop.left->templateid.params);
		pType = CreateClassInstance2(pGlobal, pType->AsClass(), pScope, exp->binop.left->templateid.params, bInsideTemplate);

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

Type* GetNonNestedType(CGlobal* pGlobal, Scope* pGlobalScope, Scope* pScope, Expression* exp, bool bInsideTemplate)
{
	/*
	if (exp->kind == Expression::A_ID)
	{
		Scope* pScope = LookupScopeNameRecurse(pScope, exp->id);
	}
	else
	*/

	/*
	if (exp->kind == Expression::A_TEMPLATEID)
	{
		pScope = LookupScopeNameRecurse(pScope, exp->templateid.id);//pScope->GetType(exp->templateid.exp->id);
		left = exp;
	}
	else
	*/

	ASSERT(pScope != nullptr);

	Type* pType = nullptr;

	ASSERT(exp->kind == Expression::A_BINOP);

	if (exp->binop.right)
	{
		Scope* pScope2 = LookupScopeNameRecurse(pScope, exp->binop.left->templateid.id);

		if (pScope2 == nullptr)
		{
			return nullptr;
		}

		if (pScope2->m_pNamespace->AsClass() && pScope2->m_pNamespace->AsClass()->m_pInstantiatedFromArgs)
		{
			pScope2 = pScope2->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pScope;
		}

		if (exp->binop.left->templateid.params)//kind == Expression::A_TEMPLATEID)
		{
			//TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);
			ClassType* pTType = CreateClassInstance2(pGlobal, pScope2->m_pNamespace->AsClass(), pScope/*pScope2->m_pClass->m_pOwnerScope*//*pScope*/, exp->binop.left->templateid.params, bInsideTemplate);

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
			pScope2 = pTType->m_pScope;
			//pScope2 = pTType->m_pInstantiatedFromArgs->m_pClass->m_pScope;

			if (pScope2 == NULL)
			{
				return NULL;
			}

			pType = pTType;
		}

		exp = exp->binop.right;

		while (exp->binop.right != NULL)
		{
			pScope2 = LookupScopeName(pScope2, exp->binop.left->templateid.id);

			if (pScope2 == NULL)
			{
				return NULL;
			}

			if (exp->binop.left->templateid.params)
			{
//				TemplatedClassType * pTType = CreateClassInstance(pGlobal, pScope2->m_pClass, pScope, exp->binop.left->templateid.params);
				ClassType* pTType = CreateClassInstance2(pGlobal, pScope2->m_pNamespace->AsClass(), pScope, exp->binop.left->templateid.params, bInsideTemplate);

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
				pScope2 = pTType->m_pScope;//InstantiatedFrom->m_pClass->m_pScope;
			//	pScope2 = pTType->m_pInstantiatedFromArgs->m_pClass->m_pScope;

				if (pScope2 == NULL)
				{
					return NULL;
				}

				pType = pTType;
			}

			exp = exp->binop.right;
		}

		pType = LookupTypeName(pScope2, exp->binop.left->templateid.id);
	}
	else
	{
		if (exp->binop.left->templateid.id == NULL)
			return NULL;

		pType = LookupTypeName/*Recurse*/(pScope, exp->binop.left->templateid.id);
	}

	if (exp->binop.left->templateid.params)//kind == Expression::A_TEMPLATEID)
	{
//		pType = CreateClassInstance(pGlobal, pType->GetClass(), pScope, exp->binop.left->templateid.params);
		pType = CreateClassInstance2(pGlobal, pType->AsClass(), pScope, exp->binop.left->templateid.params, bInsideTemplate);

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

long Evaluate(const T_Exp* exp);

ClassType* newInstantiateTemplate(Scope* pOwnerScope, CGlobal* pGlobal, ClassType* pTemplateClass, const TemplateArgs* pParams/*TemplatedClassArgs * pParams*/, int levels);
ClassType* newInstantiateTemplate2(Scope* pOwnerScope, CGlobal* pGlobal, ClassType* pTemplateClass, const TemplateArgs* pParams/*TemplatedClassArgs * pParams*/, map<Type*, Type*> & type2type, int levels);
ClassType* newInstantiateTemplate2(ClassType* const pInstantiatedClass, Scope* pOwnerScope, CGlobal* pGlobal, ClassType* pTemplateClass, const TemplateArgs* pParams, map<Type*, Type*> & _type2type, int levels);

bool ContainsTemplateArg(Type* pType)
{
	switch (pType->get_Kind())
	{
	case type_templatearg:
		{
			return true;
		}
		break;

	case type_typedef:
		{
			Typedef* pTypedef = static_cast<Typedef*>(pType);

			if (pTypedef->m_pType)
			{
				if (ContainsTemplateArg(pTypedef->m_pType))
					return true;
			}

			if (pTypedef->m_ownerScope && pTypedef->m_ownerScope->m_pNamespace && pTypedef->m_ownerScope->m_pNamespace->AsClass())
			{
				return ContainsTemplateArg(pTypedef->m_ownerScope->m_pNamespace->AsClass());
			}
		}
		break;

	case type_pointer:
		{
			return ContainsTemplateArg(static_cast<PointerType*>(pType)->GetPointerTo());
		}
		break;

	case type_reference:
		{
			return ContainsTemplateArg(static_cast<ReferenceType*>(pType)->GetPointerTo());
		}
		break;

	case type_rvalue_reference:
		{
			return ContainsTemplateArg(static_cast<RValueReferenceType*>(pType)->GetPointerTo());
		}
		break;

	case type_class:
		{
			ClassType* pClass = static_cast<ClassType*>(pType);

			if (pClass->m_pTemplateParams)
			{
				return true;
			}

			if (pClass->m_pInstantiatedFromArgs)
			{
				ASSERT(pClass->m_pTemplateParams == NULL);

				for (uint i = 0; i < pClass->m_pInstantiatedFromArgs->m_items.size(); ++i)
				{
					if (pClass->m_pInstantiatedFromArgs->m_items[i]->m_pType)
					{
						if (ContainsTemplateArg(pClass->m_pInstantiatedFromArgs->m_items[i]->m_pType))
						{
							return true;
						}
					}
				}
			}

			if (pClass->m_ownerScope && pClass->m_ownerScope->m_pNamespace && pClass->m_ownerScope->m_pNamespace->AsClass())
			{
				return ContainsTemplateArg(pClass->m_ownerScope->m_pNamespace->AsClass());
			}
		}
		break;
	}

	return false;
}

/*
bool IsTemplated(Class* pClass)
{
	if (pClass->m_pInstantiatedFromArgs)
	{
		for (int i = 0; i < pClass->m_pInstantiatedFromArgs->m_arguments.size(); i++)
		{
			if (ContainsTemplateArg(pTemplateArgType))
			{
				return true;
			}
		}
	}

	return false;
}
*/

ClassType* CreateClassInstance2(CGlobal* pGlobal, ClassType* pTemplateClass, Scope* pScope, /*Scope* pTScope,*/ A_TemplateArgumentList* params2, bool bInsideTemplate)
{

	TemplatedClassArgs* pInstantiatedFromArgs = new TemplatedClassArgs;
#if 0
	pInstantiatedFromArgs->m_pClass = pTemplateClass;
#endif

	TemplateParameterList* params = NULL;//pTemplateClass->GetClass()->m_items;

	A_TemplateArgumentList* typeIds2 = params2;
	/*
	{

		A_TemplateArgumentList* typeIds = params2;
		while (typeIds)
		{
			typeIds2 = new A_TemplateArgumentList(typeIds->head, typeIds2);
			typeIds = typeIds->tail;
		}
	}
	*/

	/*
	{
	int i = 0;
	A_TemplateArgumentList* typeIds = typeIds2;
	while (typeIds)
	{
		A_TemplateArgument* typeId = typeIds->head;

		FormalTemplateArg* param = pTemplateClass->GetClass()->m_pTemplateParams->m_items[i];
		if (param->m_kind == FormalTemplateArg::Param_Type)
		{
		}
		else
			ASSERT(0);
	}
	*/

	bool bWait = false;
	bool hasTemplateArgs = false;

	unsigned int i = 0;
	A_TemplateArgumentList* typeIds = typeIds2;
	for (; typeIds; typeIds = typeIds->tail, ++i)
	{
		A_TemplateArgument* typeId = typeIds->head;

		ASSERT(pTemplateClass->AsClass()->m_pTemplateParams);

		if (i == pTemplateClass->AsClass()->m_pTemplateParams->m_items.size())
		{
			Std::get_Out() << "too many template args" << "\n";
			break;
		}

		FormalTemplateArg* param = pTemplateClass->AsClass()->m_pTemplateParams->m_items[i];

		if (param->m_kind == FormalTemplateArg::Param_Type)
		{
		//	ASSERT(typeid(*typeId->m_pTypeId) == typeid(A_TypeId));
		//	ASSERT(typeid(*typeId->m_pTypeId->declspecList) == typeid(DeclSpecList));

			Type* pTemplateArgType;

			if (typeId->m_pTypeId)
			{
				pTemplateArgType = GetType(typeId->m_pTypeId->m_declspecList, NULL, pGlobal, pScope, pScope, NULL/*fun*/, NULL/*tp*/, 1/*linkage*/, bInsideTemplate);//NULL/*tp*/, false/*bInsideTemplate*/);

				Declarator* pDeclarator = new Declarator;
				pDeclarator->m_pType = pTemplateArgType;
				Extract(typeId->m_pTypeId->m_declarator, pDeclarator, pDeclarator->m_pType, pScope, pScope/*pScope*/, NULL/*fun*/, NULL/*tp*/, pGlobal, bInsideTemplate);
				pTemplateArgType = pDeclarator->m_pType;
				delete pDeclarator;
			}
			else
			{
				ASSERT(typeId->m_pExp);

				SExp* exp = TransExpression(typeId->m_pExp, pGlobal, pScope);
				if (exp == nullptr)
				{
					continue;
					//return NULL;

				//	printf("%s(%d) : TransExpression(typeId->m_pExp) returned NULL at " __FILE__ "%d\n", "unknown file", typeId->m_pExp->m_line_pos);
				//	ASSERT(0);
				//	exp = TransExpression(NULL/*T_Declarator* frame*/, typeId->m_pExp, pGlobal, pScope);
				}
				//ASSERT(exp);

				pTemplateArgType = exp->GetExpType();
			}

			if (ContainsTemplateArg(pTemplateArgType))
			{
				if (!bInsideTemplate)
				{
					ContainsTemplateArg(pTemplateArgType);
					ASSERT(0);
				}

				hasTemplateArgs = true;
				bWait = true;
			}

			/*
			if (pTemplateArgType->GetKind() == type_templatearg)
			{
				bWait = true;

			//	return pTemplateClass;
			}
			*/

			ActualTemplateArg* p = new ActualTemplateArg;
			p->m_pType = pTemplateArgType;

			pInstantiatedFromArgs->m_items.push_back(p);
		}
		else // if (param->m_kind == System::FormalTemplateArg::Param_Value)
		{
			if (typeId->m_pExp == NULL)
			{
				Std::get_Out() << "typeId->m_pExp == NULL" << "\n";
			}
			else
			{
				SExp* sexp = TransExpression(typeId->m_pExp, pGlobal, pScope);
				if (sexp == NULL)
				{
					Std::get_Out() << typeId->m_pExp->m_filename << paren(typeId->m_pExp->m_line_pos+1) << " : error : typeId->m_pExp failed to translate" << "\n";
					++pGlobal->m_errors;
				}
				else
				{
					if (sexp->GetKind() == SExp::SEXP_INT)
					{
						SValExp* valexp = dynamic_cast<SValExp*>(sexp);

						ActualTemplateArg* p = new ActualTemplateArg;
						p->m_pType = NULL;
						p->m_value = valexp->m_val;

						pInstantiatedFromArgs->m_items.push_back(p);
					}
					else
					{
						if (!bInsideTemplate)
						{
							ASSERT(0);
						}

						hasTemplateArgs = true;
						bWait = true;

						ActualTemplateArg* p = new ActualTemplateArg;
						p->m_exp = sexp;

						pInstantiatedFromArgs->m_items.push_back(p);
					}
	#if 0
					else
					{
					//	Tr_Exp* exp = TransExpression(NULL/*T_Declarator* frame*/, typeId->m_pExp, pGlobal, pScope);

						long value = 0;
						else
						{
							value = Evaluate(exp->ex);
							Tr_Exp* exp = TransExpression(NULL/*T_Declarator* frame*/, typeId->m_pExp, pGlobal, pScope);
						}

						TemplatedClassArg* p = new TemplatedClassArg;
						p->m_pType = NULL;
						p->m_value = value;

						pInstantiatedFromArgs->m_items.push_back(p);
					}
	#endif
				}
			}
		}

	}

	// Process the rest of the params, which must have default values
	for (; i < pTemplateClass->AsClass()->m_pTemplateParams->m_items.GetSize(); ++i)
	{
		FormalTemplateArg* param = pTemplateClass->AsClass()->m_pTemplateParams->m_items[i];
		if (param->m_kind == FormalTemplateArg::Param_Type)
		{

		//	TemplatedClassArg* p = new TemplatedClassArg;
		//	p->m_pType = ;

		//	Type* pType = Evaluate(pGlobal, param->m_pType->m_defaultArg);

		//	Type* pType = param->m_pType->m_defaultArg;

			/*
			if (ContainsTemplateArg(param->m_pType->m_defaultArg->m_pType))
			{
				bWait = true;
			}
			*/

			if (true)
			{
				ActualTemplateArg* p = new ActualTemplateArg(*param->u.m_pType->m_defaultArg);
				pInstantiatedFromArgs->m_items.push_back(p);
			}
			else
			{
			/*pTType->m_*/pInstantiatedFromArgs->m_items.push_back(param->u.m_pType->m_defaultArg);
			}
		}
		else if (param->m_kind == FormalTemplateArg::Param_Value)
		{
			ActualTemplateArg* p = new ActualTemplateArg(param->m_defaultArg.int32Val);
		//	//*p = *param->u.m_pType->m_defaultArg;
		//	p->m_value = param->m_defaultArg.int32Val;

			pInstantiatedFromArgs->m_items.push_back(p);
		}
		else
		{
			Std::get_Out() << __FILE__ << "(" << __LINE__ << ")" << " : TODO: FIX BUG\n";
			ASSERT(0);
		}
	}

	if (!bInsideTemplate)
	{
		ASSERT(!bWait);
	}

	if (true)
	{
		/*

		consider this

		template<class TYPE> Rect
		{
			Rect<float> ToFloat();

			TYPE x, y, width, height;
		}

		If we try to instantiate Rect<float> when we first encounter ToFloat() it'll
		miss the x, y, width, height which appear later

		*/

		if (bInsideTemplate)
			bWait = true;
	}

	if (bWait)
	{
		ClassType* p = new ClassType;
		//p->m_ownerDecl = new Declarator(p, "TEST2");
	//	p->m_sourcefile = pTemplateClass->m_sourcefile;
	//	ASSERT(p->m_sourcefile);
		p->m_typelib = pGlobal->m_typelib;
		p->m_kwType = pTemplateClass->m_kwType;
		p->m_sourcefile = pTemplateClass->m_sourcefile;
		p->m_ownerScope = pTemplateClass->m_ownerScope;//pScope;
		p->m_pScope->m_pParentScope = p->m_ownerScope;
		p->m_pTemplateParams = pTemplateClass->m_pTemplateParams;
	//	p->m_filepath = pTemplateClass->m_filepath;
		p->m_packing = pTemplateClass->m_packing;
	//	ASSERT(p->m_packing > 0);
		p->m_HasTemplateArgs = hasTemplateArgs;

		p->m_name = pTemplateClass->m_name;

		p->m_pInstantiatedFromArgs = pInstantiatedFromArgs;
		p->m_pInstantiatedFromClass = pTemplateClass;
#if 0
		ASSERT(p->m_pInstantiatedFromArgs->m_pClass->m_pTemplateParams);
#endif

		if (true)
		{
			IO::StringWriter strbuilder;
			p->Write(strbuilder);
			String str = strbuilder.str();
			p->m_qname = str;
		//	ASSERT(!p->m_readonly);

			map<String,System::NamedType*>::iterator it = pGlobal->m_templateInstances.find(str);
			if (it == pGlobal->m_templateInstances.end())
			{
				pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, p));

				//return (*it).second;
			}
			else
			{
#if 0
				NamedType* pType2 = (*it).second;
				pType2->Equals(*p);
				//ASSERT(0);
#endif
			}
		}

		Declarator* declType = new Declarator();
		declType->m_pType = p;
		p->m_ownerDecl = declType;
		declType->m_typedef = true;

		if (false)
		{
			Declarator* declType = new Declarator;
			declType->m_typedef = true;
			declType->m_pType = p;
			pScope->m_orderedDecls.push_back(declType);
			pScope->m_types.insert(typemap::value_type(p->m_name, p));
		}

		return p;
	}
	else
	{
		TemplateArgs args;
		args.m_pTemplateParams = pTemplateClass->m_pTemplateParams;
		args.m_pInstanceArgs = pInstantiatedFromArgs;
#if 0
		ASSERT(pInstantiatedFrom->m_pClass->m_pTemplateParams);
#endif


		ClassType* p = newInstantiateTemplate(pTemplateClass->m_ownerScope/*pScope*/, pGlobal, pTemplateClass/*pTType->m_pClass*/, &args/*pInstantiatedFrom*//*&templateArgs*//*pTType->m_items.GetData()*/, 0);

		return p;
	}

#if 0
	TemplatedClassType * g = CreateClassInstance(pGlobal, pTemplateClass, pScope, params2);

	TemplateArgs templateArgs;
//	templateArgs.m_args = pTType->m_items.GetData();
	templateArgs.m_pInstanceArgs = ((TemplatedClassType*)g)->m_pInstantiatedFromArgs;
	templateArgs.m_parent = NULL;	// ?

	ClassType* p = InstantiateTemplate(pScope, pGlobal, g/*pTType->m_pClass*/, &templateArgs/*pTType->m_items.GetData()*/);
	print(p);
#endif

}

T_ExpList* ZeroInitialize(Type* pType)
{
	if (pType->get_Kind() == type_class)
	{
		ClassType* pClass = pType->AsClass();

		T_ExpList* texplist = NULL;

		for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
		{
			Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			T_ExpList* k = ZeroInitialize(pMember->m_pType);
			texplist = Join(k, texplist);
		}

		return texplist;
	}
	else if (pType->get_Kind() == type_array)
	{
		T_ExpList* texplist = NULL;

		int nElems = ((ArrayType*)pType)->get_ElemCount();
		ASSERT(nElems >= 0);

		while (nElems--)
		{
			T_ExpList* k = ZeroInitialize(((ArrayType*)pType)->m_pElemType);
			texplist = Join(k, texplist);
		}

		return texplist;
	}
	else
	{
		T_Exp* e = T_ConstExp(0);
		e->m_size = pType->get_sizeof();
		return new T_ExpList(e, NULL);
		/*
		Tr_Exp* tr = Tr_Ex(T_ConstExp(0));
		tr->ex->m_size = pType->get_sizeof();
		ASSERT(tr);

		tr = ConvertExpressionType(tr, pType);

		T_Exp* texp = unEx(tr);

		return new T_ExpList(texp, NULL);
		*/
	}
}

T_ExpList* Initialize(Type* pType, Expression* exp, CGlobal* pGlobal, Scope* pScope)
{
	ASSERT(0);
	return NULL;
#if 0
	if (pType->get_Kind() == type_cv)
	{
		return Initialize(pType->GetPointerTo(), exp, pGlobal, pScope);
	}
	else if (pType->get_Kind() == type_class)
	{
		ClassType* pClass = pType->GetClass();

		ASSERT(exp->GetKind() == Expression::A_INITCLAUSE);
		ast::InitClauseExp* initexp = dynamic_cast<ast::InitClauseExp*>(exp);

		ExpressionList* explist = initexp->m_args;

		T_ExpList* texplist = NULL;

		int n = 0;
		while (explist)
		{
			if (n == pClass->m_pScope->m_orderedDecls.size())
			{
				ASSERT(0);
			}

			Declarator* pMember = pClass->m_pScope->m_orderedDecls[n];

			T_ExpList* k = Initialize(pMember->m_pType, explist->head, pGlobal, pScope);
			texplist = Join(k, texplist);

			explist = explist->tail;
			n++;
		}

		return texplist;
	}
	else if (pType->get_Kind() == type_array)
	{
		ASSERT(exp->GetKind() == Expression::A_INITCLAUSE);
		ast::InitClauseExp* initexp = dynamic_cast<ast::InitClauseExp*>(exp);
		
		ExpressionList* explist = initexp->m_args;

		T_ExpList* texplist = NULL;

		int n = 0;

		while (explist)
		{
			if (((ArrayType*)pType)->get_ElemCount() > 0)
			{
				if (n == ((ArrayType*)pType)->get_ElemCount())
				{
					Std::Out << ("too many initializers\n");
					ASSERT(0);
				}
			}

			T_ExpList* k = Initialize(((ArrayType*)pType)->m_pElemType, explist->head, pGlobal, pScope);
			texplist = Join(k, texplist);

			explist = explist->tail;
			n++;
		}

		if (((ArrayType*)pType)->get_ElemCount() > 0)
		{
			// set rest to zero
			for (uint i = n; i < ((ArrayType*)pType)->get_ElemCount(); ++i)
			{
				T_ExpList* k = ZeroInitialize(((ArrayType*)pType)->m_pElemType);
				texplist = Join(k, texplist);
			}
		}

		return texplist;
	}
	else
	{
		Tr_Exp* tr = TransExpression(NULL, exp, pGlobal, pScope);
		ASSERT(tr);

		tr = ConvertExpressionType(tr, pType);

		T_Exp* texp = unEx(tr);

		return new T_ExpList(texp, NULL);
	}
#endif
}

CDeclaratorList* SimpleDeclaration(A_SimpleDeclaration* d, CGlobal* pGlobal, Scope* pScope, Scope* pTScope, Declarator* fun, ClassType* pInnermostClass, TemplateParams* tp, int linkage, bool bInsideTemplate)
{
	CDeclaratorList* declaratorList = NULL;

	bool bTypedef = false;
	bool bExtern = false;
	bool bVirtual = false;
	bool bStatic = false;
	unsigned int align = 0;

	DeclSpecList* decllist = d->m_declspec;
	while (decllist)
	{
		if (decllist->head == NULL)
		{
			decllist = decllist->tail;
			continue;
		}

		if (decllist->head->GetKind() == A_DeclSpec::A_TYPE_MODIFIER)
		{
			A_DeclSpecModifier* pModifier = (A_DeclSpecModifier*)decllist->head;

			if (pModifier->m_modifier == A_TYPEDEF)
			{
				if (bTypedef)
					Std::Out << ("warn: typedef already specified");

				bTypedef = true;
			}
			else if (pModifier->m_modifier == A_EXTERN)
			{
				if (bExtern)
					Std::Out << ("warn: extern already specified");

				bExtern = true;
			}
			else if (pModifier->m_modifier == A_VIRTUAL)
			{
				if (bVirtual)
					Std::Out << "warn: virtual already specified";

				bVirtual = true;
			}
			else if (pModifier->m_modifier == A_STATIC)
			{
				if (bStatic)
					Std::Out << "warn: static already specified\n";

				bStatic = true;
			}
		}
		else if (decllist->head->GetKind() == A_DeclSpec::A_TYPE_DECLSPECEXT)
		{
			A_DeclSpecExtModifier* declspecext = (A_DeclSpecExtModifier*)decllist->head;

			A_DeclSpecExtList* extlist = declspecext->m_extlist;
			while (extlist)
			{
				if (String(extlist->head->m_id) == "align")
				{
					align = extlist->head->m_arg;
				}
				extlist = extlist->tail;
			}
		}

		decllist = decllist->tail;
	}

	Type* pType = nullptr;
	if (d->m_declspec)	// constructors have NULL
	{
		g_reffilelocation.push(FileLocation(d->m_filename, d->m_line_pos));
		pType = GetType(d->m_declspec, d->m_declaratorList, pGlobal, pScope, pTScope, fun, tp, linkage, bInsideTemplate);
		g_reffilelocation.pop();
	}

	if (pType)
	{
		if (d->m_attributes)
		{
			if (pType->get_Kind() == type_class)
			{
				ClassType* pClass = (ClassType*)pType;

				unsigned int count = Count(d->m_attributes);
				/*
				{
					ExpressionList* explist = d->m_attributes;
					while (explist)
					{
						++count;
						explist = explist->tail;
					}
				}
				*/

				pClass->m_attributeDefs = array<AttributeDef>(new AttributeDef[count], count);

				unsigned int n = 0;
				ExpressionList* explist = d->m_attributes;
				while (explist)
				{
					Expression* exp = explist->head;

					VERIFY(exp->GetKind() == Expression::A_CALL);
					CallExp* callexp = dynamic_cast<CallExp*>(exp);

					Scope* pNameScope = GetNestedScope(pGlobal, nullptr, pClass->m_pScope, callexp->m_left);
					if (pNameScope == nullptr)
						raise(Exception("classname not found"));

					ClassType* pMethodClass = pNameScope->m_pNamespace->AsClass();
					if (pMethodClass == nullptr)
						raise(Exception("name is not a class type"));

					pClass->m_attributeDefs[n].m_pClass = pMethodClass;

					// Find right constructor (TODO)
					Declarator* pCtor = nullptr;
					uint nmethod;
					{
						for (nmethod = 0; nmethod < pMethodClass->m_pScope->m_orderedDecls.size(); nmethod++)
						{
							if (*pMethodClass->m_pScope->m_orderedDecls[nmethod]->m_name == *pMethodClass->m_name)
							{
								pCtor = pMethodClass->m_pScope->m_orderedDecls[nmethod];
								break;
							}
						}
					}
					VERIFY(pCtor);

				//	pClass->m_attributes[n].m_pMethod = pCtor;
					pClass->m_attributeDefs[n].m_method = nmethod;

					pClass->m_attributeDefs[n].m_nargs = Count(callexp->m_args);
					pClass->m_attributeDefs[n].m_args = new AttributeDef::Arg[pClass->m_attributeDefs[n].m_nargs];
					ExpressionList* arglist = callexp->m_args;
					int j = 0;
					while (arglist)
					{
						Expression* arg = arglist->head;

						if (arg->kind == Expression::A_STRING)
						{
							pClass->m_attributeDefs[n].m_args[j].astrVal = arg->templateid.id;
						}
						else// if (arg->kind == Expression::A_BINOP)
						{
							SExp* exp = TransExpression(arg, pGlobal, pScope);
							VERIFY(exp);

							if (exp->m_pType->get_Kind() == type_enum)
							{
								int value = dynamic_cast<SValExp*>(exp)->m_val;
								pClass->m_attributeDefs[n].m_args[j].int32Val = value;
							}
							else if (exp->m_pType->get_Kind() == type_int)
							{
								int value = dynamic_cast<SValExp*>(exp)->m_val;
								pClass->m_attributeDefs[n].m_args[j].int32Val = value;
							}
							else
								VERIFY(0);

						}
						/*
						else
							VERIFY(0);
							*/

						arglist = arglist->tail;
					}

					explist = explist->tail;
					n++;
				}
			}
		}
	}

//	if (pType == NULL)
//		return NULL;

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
			Class* pClass = pType->AsClass();
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
		//	templateArgs.m_count = ((TemplatedClassType*)pType.m_p)->m_items.GetSize(); 
		//	templateArgs.m_args = ((TemplatedClassType*)pType.m_p)->m_items.GetData();
		//	templateArgs.m_pInstanceArgs = NULL;//((TemplatedClassType*)pType.m_p);//->m_items;
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

	InitDeclaratorList* declp = d->m_declaratorList;
	if ((declp != nullptr) || (pType && pType->get_Kind() == type_class && pType->AsClass()->m_name == nullptr))
	{
		if (declp)
		{
			while (declp)
			{
				Declarator* pDeclarator = new Declarator;
				//pDeclarator->line_pos = declp->head->line_pos;

				pDeclarator->m_pType = pType;
				pDeclarator->m_alignment = align;
				pDeclarator->m_static = bStatic;

				if (declp->head)	// TODO, remove
				{
					ASSERT(declp->head);

					if (declp->head->m_declarator)
					{
						pDeclarator->m_sourcefile = pGlobal->AddSourceFile(SplitPath(pGlobal, CString(declp->head->m_declarator->m_filename).Detach()));
						if (pDeclarator->m_sourcefile) pDeclarator->m_sourcefile_it = pDeclarator->m_sourcefile->Add(pDeclarator);
						pDeclarator->m_sourceline = declp->head->m_declarator->m_line_pos;
					}

					Extract(declp->head->m_declarator, pDeclarator, pType, pScope, pTScope, fun, tp, pGlobal, bInsideTemplate);
					ASSERT(pDeclarator->m_pOwnerScope == NULL);

					if (declp->head->m_initializer)
					{
						pDeclarator->m_initVal = TransExpression(declp->head->m_initializer->m_exp, pGlobal, pScope);
					}

					if (pType == NULL)
					{
						if (d->m_declspec != NULL && pDeclarator->m_name.At(0) != '~')
						{
							Std::Out << FileLocation(d->m_filename, d->m_line_pos+1) << " : pType == NULL : ";
							WriteToStream(Std::get_Out(), d->m_declspec);
						//	Std::Out << " ";
							WriteToStream(Std::get_Out(), d->m_declaratorList);
							Std::Out << "\n";
						//	pType = GetType(d->m_declspec, d->m_declaratorList, pGlobal, pScope, pTScope, fun, tp, linkage, bInsideTemplate);
						}
					}

					pDeclarator->m_pOwnerScope = pScope;
					pDeclarator->m_virtual = bVirtual;
					pDeclarator->m_abstract = declp->head->m_initializer != NULL;
					pDeclarator->m_typedef = bTypedef;
					pDeclarator->m_cpp_linkage = linkage == 1;

					if (bTypedef)
					{
						if (pDeclarator->m_pType == NULL)
						{
							++pGlobal->m_errors;
							raise(Exception("FATAL ERROR - pDeclarator->m_pType == NULL"));
						}
						// pDeclarator->m_pType can be null if typename

						//if (pDeclarator->m_pType != NULL)
						{
							if (pDeclarator->m_pType && (pDeclarator->m_pType->get_Kind() == type_class) &&
								((ClassType*)pDeclarator->m_pType)->m_name == nullptr)
							{
								VERIFY(pDeclarator->m_name);

								ClassType* pClassType = ((ClassType*)pDeclarator->m_pType);
								pClassType->m_name = pDeclarator->m_name;

								pDeclarator->m_pType = pClassType;
							}
							else
							{
								/*
								if (*pDeclarator->m_name == "ColumnDefinition")
								{
									MessageBeep(-1);
								}
								*/
								Typedef* pTypedef = new Typedef(pDeclarator->m_name, pDeclarator->m_pType);
								pTypedef->m_typelib = pGlobal->m_typelib;
							//	pTypedef->m_filepath = declp->head->m_declarator->m_filename;
							//	pTypedef->m_sourcefile = pGlobal->AddSourceFile(pTypedef, declp->head->m_declarator->m_filename);	// TODO, doesn't really make any sence, namespaces don't have one place of definition
								pTypedef->m_ownerScope = pScope;

								pDeclarator->m_pType = pTypedef;
							}
						}
					}

					if (pDeclarator->m_pType == NULL)
					{
						++pGlobal->m_errors;
						raise(Exception("fatal error - pDeclarator->m_pType == NULL"));
					}

					if (fun)//pInnermostClass == (ClassType*)1)
					{
						pDeclarator->m_localVar = true;
					}
					else
					{
						pDeclarator->m_localVar = false;

						if (pInnermostClass == NULL)
						{
							if (pDeclarator->m_pType->get_Kind() != type_function)
							{
								T_Declarator* & pBody = labels[pDeclarator];
								if (pBody == NULL)
								{
									pBody = new T_Declarator;
									pBody->m_pDeclarator = pDeclarator;
									tglobals.push_back(pBody);

									pBody->type = T_Declarator::data;

									Temp_label* label;// = labels[pDeclarator];
									label = new Temp_label;

									label->m_defined = true;
									pBody->m_tempLabel = label;

									//pDeclarator->m_defined = true;
								}

								if (declp->head->m_initializer)
								{
									Expression* exp = declp->head->m_initializer->m_exp;

									// TODO, had this
#if 0
									T_ExpList* texplist = Initialize(pDeclarator->m_pType, exp, pGlobal, pScope);
									pBody->m_texplist = Reverse(texplist);
#endif
								}
								else
								{
									pBody->m_texplist = NULL;
								}
							}
						}
					}

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
						/*
						if (*pDeclarator->m_name == "CV_prmode_e")
						{
							MessageBeep(-1);
						}

						if (*pDeclarator->m_name == "size_t")
						{
							MessageBeep(-1);
						}
						*/

						declsmap::iterator decli = pScope->m_decls.find(pDeclarator->m_name);
						if (decli != pScope->m_decls.end())
						{
							Declarator* pFoundDeclarator = (*decli).second;
	#if 0
							if (pFoundDeclarator->m_defined)
							{
								printf("error(%d): '%s' Already declared\n", /*pDeclarator->m_location.m_line*/0, pDeclarator->m_name->c_str());
							}
							else
	#endif
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

										if (pFoundDeclarator->m_defined)
										{
											printf("error(%d): '%s' Already declared\n", /*pDeclarator->m_location.m_line*/0, pDeclarator->m_name->c_str());
										}
									}
									else	// overloaded function
	#endif
									{
									//	pDeclarator->m_pOwnerScope = pScope;
										//CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);

										pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
										pScope->m_orderedDecls.push_back(pDeclarator);

										declaratorList = new CDeclaratorList(pDeclarator, declaratorList);

										if (pInnermostClass == NULL/* && pDeclarator->m_defined*/)
										{
											pGlobal->m_globals.Add(pDeclarator);
										}
									}
								}
								else
								{
									if (! pFoundDeclarator->m_pType->Equals(*pDeclarator->m_pType))
									{
										//ASSERT(pDeclarator->m_sourcefile);
										if (pDeclarator->m_sourcefile)
										{
											serror() << pDeclarator->m_sourcefile->ToString() << paren(pDeclarator->m_sourceline+1);
										}
										serror() << " : warning " << quote(pDeclarator->m_name) << " already declared as something else\n";
										if (pFoundDeclarator->m_sourcefile)
										{
											serror() << "\t" << pFoundDeclarator->m_sourcefile->ToString() << paren(pFoundDeclarator->m_sourceline+1) << "for previous declaration \n";
										}
									}
									else
									{
										// TODO ? (like above)
									}
								}
							}
						}
						else
						{
							/*
							if (bTypedef)
							{
								ASSERT(pDeclarator->m_pType->GetKind() == type_typedef);
							}
							*/

							if (bTypedef)
							{
								/*
								if (pDeclarator->m_name == "base")
								{
									MessageBeep(-1);
								}
								*/

							//	if (pDeclarator->m_name)	// hm..
								{
#if 0
									if (pDeclarator->m_pType->get_Kind() == type_class &&
										((ClassType*)pDeclarator->m_pType)->m_name == NULL)
									{
										ClassType* pClassType = ((ClassType*)pDeclarator->m_pType);
										pClassType->m_name = pDeclarator->m_name;

										pScope->m_types.insert(typemap::value_type(pClassType->m_name, pClassType));

										if (true)
										{
											BufferImp<char> buffer;
											StringBuilder<char> strbuilder(&buffer);
											pClassType->Write(strbuilder);
											StringA* str = buffer.DetachToString();
										//	printf("%s\n", str->c_str());
											pClassType->m_qname = str;
											ASSERT(!pClassType->m_readonly);

											map<System::StringA*,System::NamedType*, Ref_Less<System::StringA> >::iterator it = pGlobal->m_templateInstances.find(str);
											if (it == pGlobal->m_templateInstances.end())
											{
												pGlobal->m_templateInstances.insert(map<System::StringA*,System::NamedType*, Ref_Less<System::StringA> >::value_type(str, pClassType));

												//return (*it).second;
											}
											else
												ASSERT(0);
										}

										//ASSERT(pClass->m_items.size() == 0);
										ASSERT(!ContainsTemplateArg(pClassType));

										ASSERT(pClassType->m_name);
										pGlobal->m_alltypes.push_back(pClassType);
									}
									else
#endif
									{
										NamedType* pTypedef = static_cast<NamedType*>(pDeclarator->m_pType);

#if 0

										Typedef* pTypedef = new Typedef(pDeclarator->m_name, pDeclarator->m_pType);
										pTypedef->m_filepath = declp->head->m_declarator->m_filename;
								//	pTypedef->AddRef();
										pTypedef->m_ownerScope = pScope;

										/*
										if (pScope->m_pParentScope)
											pTypedef->m_qname = *(*GetQualifiedName(pScope) + "::") + *pTypedef->m_name;
										else
											pTypedef->m_qname = pTypedef->m_name;
											*/

								//		printf("typedef %s\n", pTypedef->m_name->c_str());
#endif
										pScope->m_types.insert(typemap::value_type(pTypedef->m_name, pTypedef));

										if (true)
										{
											if (bInsideTemplate)
											{
												if (!ContainsTemplateArg(pTypedef))
												{
													ContainsTemplateArg(pTypedef);
													ASSERT(0);
												}
											}
											else
											{
												if (ContainsTemplateArg(pTypedef))
												{
													ContainsTemplateArg(pTypedef);
													ASSERT(0);
												}
											}

										//	if (!bInsideTemplate)
											if (true)
											{
												IO::StringWriter strbuilder;
												pTypedef->Write(strbuilder);
												String str = strbuilder.str();
											//	printf("%s\n", str->c_str());
												pTypedef->m_qname = str;
											//	ASSERT(!pTypedef->m_readonly);

												map<String,System::NamedType*>::iterator it = pGlobal->m_templateInstances.find(str);
												if (it == pGlobal->m_templateInstances.end())
												{
													pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, pTypedef));

													//return (*it).second;
												}
												else
													ASSERT(0);

												//ASSERT(pClass->m_items.size() == 0);

												ASSERT(pTypedef->m_name);
												if (Typedef* pTDef = dynamic_cast<Typedef*>(pTypedef))
												{
													ASSERT(pTDef->m_pType);
												}
												pGlobal->m_alltypes.push_back(pTypedef);
											}
											/*
											else
											{
												ASSERT(ContainsTemplateArg(pTypedef));
											}
											*/

										//	pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
										}

#if 0
										pDeclarator->m_pType = pTypedef;
#endif
									}
								}
							}

							//pDeclarator->m_pOwnerScope = pScope;
							//CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);
							ASSERT(pScope->m_decls.find(pDeclarator->m_name) == pScope->m_decls.end());
							pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_orderedDecls.push_back(pDeclarator);

							pDeclarator->m_defined = !bExtern && (pDeclarator->m_pType->get_Kind() != type_function);
							//pDeclarator->m_pOwnerScope->m_orderedDecls.push_back(pDeclaratorRef);

							declaratorList = new CDeclaratorList(pDeclarator, declaratorList);

							/*
							if (pDeclarator->m_name == "WriteToStream")
							{
								MessageBeep(-1);
							}
							*/

							if (pInnermostClass == NULL/* && pDeclarator->m_defined*/)
							{
								pGlobal->m_globals.Add(pDeclarator);
							}
						}
					}
					else
					{
						Std::Out << "declarator->name = NULL\n";
					}
				}

				declp = declp->tail;
			}
		}
		else
		{
			// unnamed struct/union

			Declarator* pDeclarator = new Declarator;
			//pDeclarator->line_pos = declp->head->line_pos;
			pDeclarator->m_pType = pType;
			pDeclarator->m_alignment = align;
			pDeclarator->m_static = bStatic;

			pDeclarator->m_pOwnerScope = pScope;
			pScope->m_orderedDecls.push_back(pDeclarator);

			declaratorList = new CDeclaratorList(pDeclarator, declaratorList);
		}
	}
	else// if (declp == NULL && !(pType && pType->get_Kind() == type_class && pType->GetClass()->m_name == NULL))
	{
		if (pType)	// hm.. friend got here
		{
			if (pType->get_Kind() != type_class && pType->get_Kind() != type_enum)
			{
				serror() << d->m_filename << paren(d->m_line_pos+1) << ": ignored when no variable is declared" << "\n";
			}
		}
	}

	return Reverse(declaratorList);
}

long Evaluate(/*CGlobal* pGlobal,*/ const T_Exp* exp)
{
	switch (exp->kind)
	{
	case T_Exp::T_MEM:
		{
			return exp->mem.mem->const_int.int32Val;
		}
		break;

	case T_Exp::T_CONST:
		{
			return exp->const_int.int32Val;
		}
		break;

	case T_Exp::T_UNOP:
		{
			long value = Evaluate(exp->unop.exp);

			switch (exp->unop.op)
			{
			case '-':
				{
					return - value;
				}
				break;

			case '+':
				{
					return value;
				}
				break;

			case '!':
				{
					return ! value;
				}
				break;

			case '~':
				{
					return ~ value;
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;

	case T_Exp::T_BINOP:
		{
			long leftvalue = Evaluate(exp->binop.left);
			long rightvalue = Evaluate(exp->binop.right);
			switch (exp->binop.op)
			{
			case '+':
				{
					return leftvalue + rightvalue;
				}
				break;

			case '-':
				{
					return leftvalue - rightvalue;
				}
				break;

			case '*':
				{
					return leftvalue * rightvalue;
				}
				break;

			case '/':
				{
					if (rightvalue == 0)
					{
						Std::Out << "Division by zero\n";
					//	THROW(-1);
					//	++pGlobal->m_errors;
						return 0;
					}
					return leftvalue / rightvalue;
				}
				break;

			case '%':
				{
					if (rightvalue == 0)
					{
						Std::Out << "Division by zero\n";
					//	++pGlobal->m_errors;
						return 0;
					//	THROW(-1);
					}
					return leftvalue % rightvalue;
				}
				break;

			case '|':
				{
					return leftvalue | rightvalue;
				}
				break;

			case '&':
				{
					return leftvalue & rightvalue;
				}
				break;

			case '^':
				{
					return leftvalue ^ rightvalue;
				}
				break;

			case '>>':
				{
					return leftvalue >> rightvalue;
				}
				break;

			case '<<':
				{
					return leftvalue << rightvalue;
				}
				break;

			case '<':
				{
					return leftvalue < rightvalue;
				}
				break;

			case '>':
				{
					return leftvalue > rightvalue;
				}
				break;

			case '<=':
				{
					return leftvalue <= rightvalue;
				}
				break;

			case '>=':
				{
					return leftvalue >= rightvalue;
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;

	default:
		Std::Out << __FILE__ << "(" << __LINE__ << ")" << " : TODO: FIX BUG\n";
	//	ASSERT(0);
	}

	return 0;
}

#if 0
Type* Evaluate(CGlobal* pGlobal, __live_object_ptr<Type> pMemberType)
{
	if (pMemberType->GetKind() == type_typedef)
	{
		return Evaluate(pGlobal, ((Typedef*)pMemberType.m_p)->m_pType);
	}
	else if (pMemberType->GetKind() == type_array)
	{
		__live_object_ptr<ArrayType> pArray = (ArrayType*)pMemberType.m_p;
	//	pArray->AddRef();

		pArray->m_pElemType = Evaluate(pGlobal, pArray->m_pElemType);
	//	((Type*)pArray->m_pElemType)->AddRef();

		/*
		if (pElemType->m_type == type_class)
		{
			CalcClass(pGlobal, pElemType->GetClass());
		}
		else if (pElemType->m_type == type_templateinst)
		{
			TemplateArgs templateArgs2;
			templateArgs2.m_parent = NULL;
			templateArgs2.m_args = ((TemplatedClassType*)pElemType)->m_items.GetData();
			pElemType = InstantiateTemplate(pGlobal, ((TemplatedClassType*)pElemType)->m_pClass, &templateArgs2);

			pArray->m_pElemType = pElemType;
		}
		*/

	//	pArray->m_sizeof = pArray->m_nSize * pArray->m_pElemType->get_sizeof();

		return pMemberType;
		//return pArray;
	}
	else if (pMemberType->GetKind() == type_class)
	{
#if 0
		CalcClass(pGlobal, pMemberType->GetClass());
#endif
		return pMemberType;
	}
	else if (pMemberType->GetKind() == type_templateinst)
	{
	//	TemplateArgs templateArgs2;
	//	templateArgs2.m_parent = NULL;
	//	templateArgs2.m_count = ((TemplatedClassType*)pMemberType.m_p)->m_items.GetSize();
	//	templateArgs2.m_pInstanceArgs = NULL;//((TemplatedClassType*)pMemberType.m_p);//->m_items.GetData();
		ClassType *pClass = InstantiateTemplate(pGlobal, ((TemplatedClassType*)pMemberType.m_p)/*->m_pClass*/, NULL/*&templateArgs2*/);

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

		return pClass;
	}

	return pMemberType;
}
#endif

//Type* Evaluate(CGlobal* pGlobal, Scope* pOwnerScope, Type* pMemberType, const TemplateArgs * templateArgs, map<Type*, Type*>& type2type);

Type* Evaluate(CGlobal* pGlobal, Scope* pOwnerScope, Type* _pMemberType, const TemplateArgs* templateArgs, map<Type*,Type*>& type2type, int levels)
{
	Type* pMemberType = _pMemberType;
	map<Type*,Type*>::iterator it = type2type.find(pMemberType);
	while (it != type2type.end())
	{
		pMemberType = (*it).second;
		it = type2type.find(pMemberType);
	}

//	pMemberType = templateArgs->GetType(pMemberType);//pTemplateMember->m_pType);

	if (pMemberType == NULL)
	{
		VERIFY(0);
		/*
		printf("oops\n");
	pMemberType = templateArgs->GetType(pTemplateMember->m_pType);//pTemplateMember->m_pType);
		continue;
		*/
	}

	if (pMemberType->get_Kind() == type_enum)
	{
		if (pOwnerScope == NULL)
			return pMemberType;

		const EnumType* pEnumType = (const EnumType*)pMemberType;
		EnumType* pEnumType2 = new EnumType;
		pEnumType2->m_typelib = pGlobal->m_typelib;

		pEnumType2->m_name = pEnumType->m_name;
		pEnumType2->m_sourcefile = pEnumType->m_sourcefile;

		if (pOwnerScope)
			pEnumType2->m_ownerScope = pOwnerScope;
		else
			pEnumType2->m_ownerScope = pEnumType->m_ownerScope;

		pEnumType2->m_deflist.reserve(pEnumType->m_deflist.size());

		for (size_t i = 0; i < pEnumType->m_deflist.size(); ++i)
		{
			pEnumType2->m_deflist.push_back(pEnumType->m_deflist[i]);
		}

		// ??
		IO::StringWriter strbuilder;
		pEnumType2->Write(strbuilder);
		String str = strbuilder.str();
	//	printf("%s\n", str->c_str());
		pEnumType2->m_qname = str;
	//	ASSERT(!pEnumType->m_readonly);

		map<String,System::NamedType*>::iterator it = pGlobal->m_templateInstances.find(str);
		if (it == pGlobal->m_templateInstances.end())
		{
			/*
	if (*str == "vector<double,System::__gc_allocator>")
	{
		MessageBeep(-1);
	}
	*/
			pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, pEnumType2));

			//return (*it).second;
		}
		else
			return (*it).second;

		//ASSERT(0);

		return pEnumType2;
	}
	else if (pMemberType->get_Kind() == type_typedef)
	{
		const Typedef* pMemberTypedef = static_cast<const Typedef*>(pMemberType);

		if (pMemberTypedef->m_pType)
		{
			Typedef* pTypedef = new Typedef;
			pTypedef->m_typelib = pGlobal->m_typelib;

			if (pOwnerScope)
				pTypedef->m_ownerScope = pOwnerScope;
			else
				pTypedef->m_ownerScope = pMemberTypedef->m_ownerScope;

			pTypedef->m_sourcefile = pMemberTypedef->m_sourcefile;

			pTypedef->m_pType = Evaluate(pGlobal, NULL/*pOwnerScope*/, pMemberTypedef->m_pType, templateArgs, type2type, levels);

			pTypedef->m_name = pMemberTypedef->m_name;
		//	pTypedef->m_qname = ((const Typedef*)pMemberType.m_p)->m_qname;

			/*
			if (*pTypedef->m_name == "ColumnDefinition")
			{
				MessageBeep(-1);
			}
			*/

			// ??
			IO::StringWriter strbuilder;
			pTypedef->Write(strbuilder);
			pTypedef->m_qname = strbuilder.str();
			 //= buffer.str();
		//	printf("%s\n", str->c_str());
		//	ASSERT(!pTypedef->m_readonly);
			/*
				if (*str == "System::UI::Grid::ColumnDefinition")
				{
					MessageBeep(-1);
				}
				*/

			map<String,System::NamedType*>::iterator it = pGlobal->m_templateInstances.find(pTypedef->m_qname);
			if (it == pGlobal->m_templateInstances.end())
			{
				pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(pTypedef->m_qname, pTypedef));

				//return (*it).second;
			}
			else
				return (*it).second;

			return pTypedef;
		}
		else
		{
			if (pMemberTypedef->m_ownerScope->m_pNamespace->AsClass() == nullptr)
			{
				// Call Evaluate ??

				Type* pPType = pMemberTypedef->m_ownerScope->m_pNamespace;
				map<Type*,Type*>::iterator it = type2type.find(pPType);
				while (it != type2type.end())
				{
					pPType = (*it).second;
					it = type2type.find(pPType);
				}

				ClassType* parentClass = pPType->AsClass();
				/*
				NamespaceType* pp2 = pMemberTypedef->m_ownerScope->m_pNamespace;

				ClassType* parentClass = newInstantiateTemplate(NULL, pGlobal, pTemplateClass, &args, 0);
				*/
				Type* pType = parentClass->LookupType(pMemberTypedef->m_name);

				if (pType == nullptr)
				{
					ClassType* pTemplateClass = g_instantiatedTemplate.top();
					ClassType* pInstantiatedClass = g_instantiatedClass.top();

					serror() << g_filelocation.top() << ": error C2039: " <<
						quote(pMemberTypedef->m_name) << " : is not a member of" <<
						quote(parentClass->get_QName()) << endl;

					/*
					printf("%s(%d): error C2039: ", g_filelocation.top().m_filepath->c_str(), g_filelocation.top().m_line+1);
					printf("'%s' : is not a member of '%s'\n", pMemberTypedef->m_name->c_str(), parentClass->get_QName()->c_str());
					printf("%s(%d): see declaration of '%s'\n", parentClass->m_filepath->c_str(), parentClass->m_line, parentClass->get_QName()->c_str());
					printf("%s(%d): see reference to class template instantiation '%s' being compiled\n", g_reffilelocation.top().m_filepath->c_str(), g_reffilelocation.top().m_line+1, pInstantiatedClass->get_QName()->c_str());

					printf("\twith\n"
							"[\n");
							*/

					VERIFY(pInstantiatedClass->m_pInstantiatedFromArgs->m_items.size() == pTemplateClass->m_pTemplateParams->m_items.size());
					for (uint i = 0; i < pTemplateClass->m_pTemplateParams->m_items.size(); ++i)
					{
						if (pTemplateClass->m_pTemplateParams->m_items[i]->m_kind == FormalTemplateArg::Param_Type)
						{
							serror() <<
								pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType->m_name <<
								"=" <<
								pInstantiatedClass->m_pInstantiatedFromArgs->m_items[i]->m_pType->ToString();

						}
						else
						{
							// TODO
							ASSERT(0);
						}
					}

					Log << "]" << endl;

					// TODO
					ASSERT(0);
					exit(0);
				}

				return pType;
			}
			else
			{
				ClassType* pp2 = pMemberTypedef->m_ownerScope->m_pNamespace->AsClass();
			//	ASSERT(pp2->m_HasTemplateArgs);

				ClassType* pTemplateClass = pp2->m_pInstantiatedFromClass;
				TemplateArgs args;
			//	args.m_pTemplateParams = pTemplateClass->m_pTemplateParams;
			//	args.m_pInstanceArgs = pp2->m_pInstantiatedFromArgs;

				/*
				args.m_pTemplateParams = templateArgs->m_pTemplateParams;
				args.m_pInstanceArgs = templateArgs->m_pInstanceArgs;
				*/

			//	ASSERT(pInstantiatedFrom->m_pClass->m_pTemplateParams);

				TemplatedClassArgs* instArgs = new  TemplatedClassArgs;

				for (uint i = 0; i < pp2->m_pInstantiatedFromArgs->m_items.size(); ++i)
				{
					Type* pType = pp2->m_pInstantiatedFromArgs->m_items[i]->m_pType;

					map<Type*,Type*>::iterator it = type2type.find(pType);
					while (it != type2type.end())
					{
						pType = (*it).second;
						it = type2type.find(pMemberType);
					}

					TemplatedClassArg* pArg = new TemplatedClassArg;
					pArg->m_pType = pType;

					instArgs->m_items.push_back(pArg);

#if 0
					TemplatedClassArg* pArg = pInstantiatedClass->m_pInstantiatedFromArgs->m_items[i];

					ASSERT(pArg->m_pType);
					Type* pType = Evaluate(pGlobal, NULL/*pOwnerScope*/, pArg->m_pType, pParams, type2type, levels+1);
					ASSERT(pType);
					pInstantiatedClass->m_pInstantiatedFromArgs->m_items[i]->m_pType = pType;//Evaluate(pGlobal, pOwnerScope, pArg->m_pType, pParams, type2type);

					type2type[pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType] = pParams->m_pInstanceArgs->m_items[i]->m_pType;
#endif
				}
				args.m_pTemplateParams = pTemplateClass->m_pTemplateParams;
				args.m_pInstanceArgs = instArgs;//pp2->m_pInstantiatedFromArgs;

				ClassType* parentClass = newInstantiateTemplate(NULL, pGlobal, pTemplateClass, &args, 0);

			//	ClassType* parentClass = newInstantiateTemplate2(NULL, pGlobal, pTemplateClass, &args, type2type, 0);

				//	pTypedef->m_pType = parentClass->LookupType(pMemberTypedef->m_name);
				Type* pType = parentClass->LookupType(pMemberTypedef->m_name);

				if (pType == NULL)
				{
					Std::Out << "type '" << pMemberTypedef->m_name << "' not found\n";
					MessageBeep(-1);
					ASSERT(0);
				}

				return pType;
			}
		}

	}
	else if (pMemberType->get_Kind() == type_pointer)
	{
		PointerType* pPointerType = (PointerType*)pMemberType;

		PointerType* p = CreatePointerType(pGlobal, Evaluate(pGlobal, NULL/*pOwnerScope*/, pPointerType->m_pPointerTo, templateArgs, type2type, levels));
	//	p->m_pPointerTo = ;

		return p;
	}
	else if (pMemberType->get_Kind() == type_reference)
	{
		ReferenceType* pPointerType = (ReferenceType*)pMemberType;

		ReferenceType* p = CreateReferenceType(pGlobal, Evaluate(pGlobal, NULL/*pOwnerScope*/, pPointerType->m_pPointerTo, templateArgs, type2type, levels));

		return p;
	}
	else if (pMemberType->get_Kind() == type_rvalue_reference)
	{
		RValueReferenceType* pPointerType = (RValueReferenceType*)pMemberType;

		RValueReferenceType* p = CreateRValueReferenceType(pGlobal, Evaluate(pGlobal, NULL/*pOwnerScope*/, pPointerType->m_pPointerTo, templateArgs, type2type, levels));

		return p;
	}
	else if (pMemberType->get_Kind() == type_pm)
	{
		PointerMemberType* pPMType = (PointerMemberType*)pMemberType;

		Type* pPointerTo = Evaluate(pGlobal, NULL/*pOwnerScope*/, pPMType->m_pPointerTo, templateArgs, type2type, levels);
		Type* pType2 = Evaluate(pGlobal, NULL/*pOwnerScope*/, pPMType->m_pClass, templateArgs, type2type, levels);

		NamespaceType* pClass2 = dynamic_cast<NamespaceType*>(pType2);
		if (pClass2 == NULL)
		{
			ASSERT(0);
		}

		PointerMemberType* p = new PointerMemberType(pPointerTo, pClass2);
		p->m_sizeof = pPMType->m_sizeof;

	//	PointerType* p = CreatePointerType(pGlobal, Evaluate(pGlobal, NULL/*pOwnerScope*/, pPointerType->m_pPointerTo, templateArgs, type2type, levels));
	//	p->m_pPointerTo = ;

		return p;
	}
	else if (pMemberType->get_Kind() == type_cv)
	{
		ModifierType* pPointerType = (ModifierType*)pMemberType;

		ModifierType* p = new ModifierType;
		p->m_bConst = pPointerType->m_bConst;
		p->m_bVolatile = pPointerType->m_bVolatile;
		p->m_pPointerTo = Evaluate(pGlobal, NULL/*pOwnerScope*/, pPointerType->m_pPointerTo, templateArgs, type2type, levels);

		return p;
	}
	else if (pMemberType->get_Kind() == type_array)
	{
		ArrayType* oldArray = (ArrayType*)pMemberType;

		Type* elemType = Evaluate(pGlobal, NULL/*pOwnerScope*/, oldArray->m_pElemType, templateArgs, type2type, levels);//templateArgs->GetType(pArray->m_pElemType);//pTemplateMember->m_pType);

		ArrayType* array = newArrayType(pGlobal, elemType, oldArray->get_ElemCount());
	//	pArray->AddRef();
	//	pArray->m_nSize = oldArray->m_nSize;
	//	pArray->m_pElemType = 


	//	pArray->m_sizeof = pArray->m_nSize * pArray->m_pElemType->get_sizeof();

		return array;
	}
	else if (pMemberType->get_Kind() == type_function)
	{
		FunctionType* pFunctionType = (FunctionType*)pMemberType;

		FunctionType* p = new FunctionType;
		p->m_bConst = pFunctionType->m_bConst;
		p->m_funcspec = pFunctionType->m_funcspec;
		if (pFunctionType->m_pReturnType)
		{
			p->m_pReturnType = Evaluate(pGlobal, NULL/*pOwnerScope*/, pFunctionType->m_pReturnType, templateArgs, type2type, levels);
		}

		p->m_parameters.m_bVarArg = pFunctionType->m_parameters.m_bVarArg;

		p->m_parameters.m_parameters.reserve(pFunctionType->m_parameters.m_parameters.size());
		for (uint i = 0; i < pFunctionType->m_parameters.m_parameters.size(); ++i)
		{
			FunctionParameters::Param param;

			g_filelocation.push(FileLocation(pFunctionType->m_parameters.m_parameters[i].m_filepath, pFunctionType->m_parameters.m_parameters[i].m_line));
			param.m_pType = Evaluate(pGlobal, NULL/*pOwnerScope*/, pFunctionType->m_parameters.m_parameters[i].m_pType, templateArgs, type2type, levels);
			g_filelocation.pop();

			param.m_name = pFunctionType->m_parameters.m_parameters[i].m_name;
			p->m_parameters.m_parameters.push_back(param);

#if 0
			CDeclarator* pDeclarator = new CDeclarator;

			pDeclarator->m_name = pFunctionType->m_parameters.m_parameters[i]->m_name;
			pDeclarator->m_pType = Evaluate(pGlobal, NULL/*pOwnerScope*/, pFunctionType->m_parameters.m_parameters[i]->m_pType, templateArgs, type2type);
			
			p->m_parameters.m_parameters.push_back(pDeclarator);
#endif
		}

		if (pFunctionType->m_pTemplateParams)
		{
			p->m_pTemplateParams = new TemplateParams;
			for (size_t i = 0; i < pFunctionType->m_pTemplateParams->m_items.size(); ++i)
			{
				System::FormalTemplateArg* param = new System::FormalTemplateArg;
				param->u.m_pType = new _TemplateArgType;
				param->u.m_pType->m_name = pFunctionType->m_pTemplateParams->m_items[i]->u.m_pType->m_name;
				param->u.m_pType->m_index = pFunctionType->m_pTemplateParams->m_items[i]->u.m_pType->m_index;
				param->u.m_pType->m_pClass = pFunctionType->m_pTemplateParams->m_items[i]->u.m_pType->m_pClass;
				if (pFunctionType->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg)
				{
					param->u.m_pType->m_defaultArg = new TemplatedClassArg;
					if (pFunctionType->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg->m_pType)
					{
						param->u.m_pType->m_defaultArg->m_pType = Evaluate(pGlobal, NULL/*pOwnerScope*/, pFunctionType->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg->m_pType, templateArgs, type2type, levels);
					//	SetReadOnly(param->u.m_pType->m_defaultArg->m_pType);
					}
					else
					{
						param->u.m_pType->m_defaultArg->m_value = pFunctionType->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg->m_value;
					}
				}

				p->m_pTemplateParams->m_items.push_back(param);
			}
		}

		return p;
	}
	else if (pMemberType->get_Kind() == type_class)
	{
		// ??
		/*
		if (pMemberType != _pMemberType)
		{
			return pMemberType->GetClass();
		}
		*/

		ClassType* pClass = pMemberType->AsClass();
		/*
		while (pClass->m_pInstantiatedFromArgs)
		{
			pClass = pClass->m_pInstantiatedFromArgs->m_pClass;
		}
		*/

		Scope* pScope = pClass->m_pScope;

	//	if (pScope->m_pClass->m_pTemplateParams == NULL)
	//		return pMemberType;

		while (pScope)
		{
			if (pScope->m_pNamespace && pScope->m_pNamespace->AsClass())
			{
				/*
				if (pScope->m_pClass->m_pInstantiatedFromArgs)
					break;
					*/

				/*
				if (pScope->m_pNamespace->GetClass()->m_pInstantiatedFromArgs)	// ??
					break;
					*/
				if (pScope->m_pNamespace->AsClass()->m_pTemplateParams)
					break;

				/*
				if (ContainsTemplateArg(pScope->m_pNamespace->GetClass()))	// ??
					break;
					*/

				pScope = pScope->m_pNamespace->AsClass()->m_ownerScope;
			}
			else
				pScope = pScope->m_pParentScope;
		}

		if (pScope == NULL)
		{
			/*
			if (_pMemberType->GetClass() == NULL)
			{
				MessageBeep(-1);
			}
			*/
			if (!((ClassType*)pMemberType)->m_def && _pMemberType->AsClass() && ((ClassType*)_pMemberType)->m_def)
			{
				ASSERT(_pMemberType->AsClass());
				ClassType* pClass2 = newInstantiateTemplate2((ClassType*)pMemberType, ((ClassType*)pMemberType)->m_ownerScope/*pOwnerScope*//*pClass3->m_pScope*//*pScope*/, pGlobal, _pMemberType->AsClass(), templateArgs/*&templateArgs2*//*templateArgs*/, type2type, levels);
				return pClass2;
			}
			return pMemberType;
		}
		else
		{
	//				CalcClass(NULL/*pGlobal*/, pMemberType->GetClass());
		//	TemplateArgs templateArgs2;
		//	templateArgs2.m_parent = templateArgs;
	//		templateArgs2.m_args = NULL;//((TemplatedClassType*)pMemberType)->m_items.GetData();

		//	TemplatedClassArgs* p = new TemplatedClassArgs;
		//	p->m_pClass = pClass;
		//	p->m_items

		//	templateArgs2.m_pInstanceArgs = p;//pClass->m_pInstantiatedFromArgs;

			//TemplateArgs templateArgs2;

#if 0
			ClassType* pClass3 = pOwnerScope->m_pClass;//pClass->m_pScope;
			while (pClass3)
			{
				if (pClass3->m_pInstantiatedFromClass == pClass->m_pOwnerScope->m_pClass/*->m_pScope*/)
					break;

				pClass3 = pClass3->m_pOwnerScope->m_pClass;
			}
#endif

			/*
			if (pClass->m_pInstantiatedFromArgs)
			{
				for (int i = 0; i < pClass->m_pInstantiatedFromArgs->m_items.size(); i++)
				{
					TemplatedClassArg* pArg = pClass->m_pInstantiatedFromArgs->m_items[i];

					TemplatedClassArg* pArg2 = new TemplatedClassArg;
					if (pArg->m_pType)
					{
						pArg2->m_pType = Evaluate(pGlobal, pOwnerScope, pArg->m_pType, templateArgs, type2type);

					//	if (pClass->m_pInstantiatedFromArgs->m_pClass->m_pTemplateParams->m_items[i]->m_pType != pArg2->m_pType)
					//		type2type[pClass->m_pInstantiatedFromArgs->m_pClass->m_pTemplateParams->m_items[i]->m_pType] = pArg2->m_pType;//pParams->m_pInstanceArgs->m_items[i]->m_pType;
					}
					else
						;
				}
			}
			*/

		//	templateArgs.m_pTemplateParams = 
			ClassType* pClass2 = newInstantiateTemplate2(pOwnerScope/*pOwnerScope*//*pClass3->m_pScope*//*pScope*/, pGlobal, pClass, templateArgs/*&templateArgs2*//*templateArgs*/, type2type, levels);
#if 0
			TemplatedClassType* p = new TemplatedClassType;
			p->m_pInstantiatedFromArgs = new TemplatedClassArgs;
			p->m_pInstantiatedFromArgs->m_pClass = pMemberType->GetClass();
		//	p->m_items = templateArgs->m_pInstanceArgs->m_items;
			ClassType* pClass2;
			if (pClass/*pMemberType->GetClass()*/->m_items.size())
				pClass2 = InstantiateTemplate(pOwnerScope, pGlobal, p, templateArgs);
			else
				pClass2 = InstantiateTemplate2(pOwnerScope, pGlobal, p, templateArgs);
#endif

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

				return pClass2;
		}
	}
#if 0
	else if (pMemberType->GetKind() == type_templateinst)
	{
		ASSERT(0);

	//	TemplateArgs templateArgs2;
	//	templateArgs2.m_parent = templateArgs;
		//templateArgs2.m_pInstanceArgs = ((TemplatedClassType*)pMemberType.m_p);//->m_items.GetSize();
	//	templateArgs2.m_args = ((TemplatedClassType*)pMemberType.m_p)->m_items.GetData();
		ClassType* pClass = InstantiateTemplate(pOwnerScope, pGlobal, ((TemplatedClassType*)pMemberType)/*->m_pClass*/, templateArgs/*&templateArgs2*/);

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
		if (!strcmp(pType->m_name->c_str(), "red_black_node"))
		{
			MessageBeep(-1);

/*
			if (true)
			{
				StringBuilderA strbuilder;
				pMemberType->Write(strbuilder);
				StringA* str = strbuilder.DetachToString();
				Typedef* pTypedef = new Typedef(str, pType);
				pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
			}
			*/
		}
#endif

		return pClass;
	}
#endif
	else
		return pMemberType;

	ASSERT(0);
}

#if 0
ClassType* InstantiateTemplate3(Scope* pOwnerScope, CGlobal* pGlobal, ClassType* pType2)
{
	if (pType2->m_pOwnerScope)
	{
		if (pType2->m_pOwnerScope->m_pClass)
		{
			ClassType* pClass2 = InstantiateTemplate3(pOwnerScope, pGlobal, pType2->m_pOwnerScope->m_pClass);
		}
	}

	if (pType2->GetKind() == type_templateinst)
	{
		TemplateArgs templateArgs;
	//	templateArgs.m_args = pTType->m_items.GetData();
		templateArgs.m_pInstanceArgs = ((TemplatedClassType*)pType2)->m_pInstantiatedFromArgs;
		templateArgs.m_parent = NULL;	// ?

		return /*pType2 =*/ InstantiateTemplate3(pOwnerScope, pGlobal, (TemplatedClassType*)pType2/*pTType->m_pClass*/, &templateArgs/*pTType->m_items.GetData()*/);
		//pMember->m_pType = pMemberType;
	}
}
#endif

void instant(CGlobal* pGlobal, ClassType* pInstantiatedClass, ClassType* pTemplateClass, const TemplateArgs* pParams, map<Type*, Type*>& type2type, int levels)
{
	for (size_t i = 0; i < pTemplateClass->m_bases.size(); ++i)
	{
		BaseClass* base = pTemplateClass->m_bases[i];
		BaseClass* baseclass = new BaseClass;

		baseclass->m_pClass = (ClassType*)Evaluate(pGlobal, /*NULL*/base->m_pClass->m_ownerScope, base->m_pClass, pParams, type2type, levels+1);
		if (baseclass->m_pClass->get_Kind() != type_class)
		{
			__debugbreak();
			// TODO, bail earlier
			return;
		}
		ASSERT(baseclass->m_pClass->get_Kind() == type_class);

		pInstantiatedClass->m_bases.push_back(baseclass);
	}

	for (size_t i = 0; i < pTemplateClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* pTemplateMember = pTemplateClass->m_pScope->m_orderedDecls[i];

		Declarator* pInstantiatedMember = new Declarator;
		pInstantiatedMember->m_name = pTemplateMember->m_name;
		pInstantiatedMember->m_cpp_linkage = pTemplateMember->m_cpp_linkage;
		pInstantiatedMember->set_Access(pTemplateMember->m_access);

		if (pTemplateMember->m_fwd)
		{
			ClassType* pClass = pTemplateMember->m_pType->AsClass();

			ClassType* pClass2 = new ClassType();
			//pClass2->m_ownerDecl = new Declarator(pClass, "TEST3");
			pClass2->m_typelib = pGlobal->m_typelib;
			pClass2->m_name = pClass->m_name;
			pClass2->m_kwType = pClass->m_kwType;
			pClass2->m_def = false;
			pClass2->m_ownerScope = pInstantiatedClass->m_pScope;
			pClass2->m_pScope->m_pParentScope = pClass2->m_ownerScope;
			pClass2->m_packing = pClass->m_packing;
			ASSERT(pClass2->m_packing > 0);

			ASSERT(pClass->m_sourcefile);
			pClass2->m_sourcefile = pClass->m_sourcefile;

			pClass2->m_ownerDecl = pTemplateMember;
			pInstantiatedMember->m_fwd = true;
			pInstantiatedMember->m_pType = pClass2;
		}
		else
		{
			pInstantiatedMember->m_pType = Evaluate(pGlobal, pTemplateMember->m_typedef? pInstantiatedClass->m_pScope: NULL/*pTemplateClass->m_pScope*/, pTemplateMember->m_pType/*pMemberType*/, pParams/*templateArgs*/, type2type, levels+1);

			if (dynamic_cast<_TemplateArgType*>(pInstantiatedMember->m_pType))
			{
				if (pTemplateMember->m_sourcefile)
				{
					Std::Out << pTemplateMember->m_sourcefile->ToString() << paren(pTemplateMember->m_sourceline+1) << " : INTERNAL ERROR\n";
				}
				Std::Out << __FILE__ << paren(__LINE__) << "\n";
				// Just redo for debugging purposes
				pInstantiatedMember->m_pType = Evaluate(pGlobal, pTemplateMember->m_typedef? pInstantiatedClass->m_pScope: NULL/*pTemplateClass->m_pScope*/, pTemplateMember->m_pType/*pMemberType*/, pParams/*templateArgs*/, type2type, levels+1);
			}
		}

		pInstantiatedMember->m_static = pTemplateMember->m_static;
		pInstantiatedMember->m_typedef = pTemplateMember->m_typedef;
		pInstantiatedMember->m_virtual = pTemplateMember->m_virtual;

		pInstantiatedClass->m_pScope->m_decls.insert(declsmap::value_type(pInstantiatedMember->m_name, pInstantiatedMember));
		pInstantiatedClass->m_pScope->m_orderedDecls.push_back(pInstantiatedMember);

		if (pInstantiatedMember->m_typedef)
		{
			NamedType* pNamedType = (NamedType*)pInstantiatedMember->m_pType;

			if (pNamedType->m_ownerScope != pInstantiatedClass->m_pScope)
			{
				ASSERT(0);//pInstantiatedMember->m_pType = Evaluate(pGlobal, pInstantiatedClass->m_pScope/*pTemplateClass->m_pScope*/, pTemplateMember->m_pType/*pMemberType*/, &args/*pParams*//*templateArgs*/, type2type);
			}

			ASSERT(pNamedType->m_ownerScope == pInstantiatedClass->m_pScope);

			{
				/*
				if (pInstantiatedMember->m_pType->GetKind() == type_class)
				{
					pInstantiatedClass->m_pScope->m_types.insert(typemap::value_type(pInstantiatedMember->m_name, pInstantiatedMember->m_pType->GetClass()));

					//pGlobal->m_alltypes.insert(typemap::value_type(pInstantiatedMember->m_name, pInstantiatedMember->m_pType->GetClass()));
					pGlobal->m_alltypes.push_back(pInstantiatedMember->m_pType->GetClass());
				}
				else
				*/
				{

					ASSERT(pInstantiatedMember->m_pType->get_Kind() == type_class ||
						pInstantiatedMember->m_pType->get_Kind() == type_typedef ||
						pInstantiatedMember->m_pType->get_Kind() == type_enum);

				//	pInstantiatedClass->maptype[(NamedType*)pTemplateMember->m_pType] = (NamedType*)pInstantiatedMember->m_pType;
					if (pTemplateMember->m_pType != pInstantiatedMember->m_pType)
						type2type[pTemplateMember->m_pType] = pInstantiatedMember->m_pType;

					pInstantiatedClass->m_pScope->m_types.insert(typemap::value_type(pInstantiatedMember->m_name/*pNamedType->m_name*/, pNamedType));

					/*
					{
					BufferImp<char> buffer;
					StringBuilderT<char> strbuilder(&buffer);
					pNamedType->Write(strbuilder);
					StringA* str = buffer.DetachToString();
					printf("%s\n", str->c_str());

					#if 1
						map<System::StringA*,System::ClassType*, Ref_Less<System::StringA> >::iterator it = pGlobal->m_templateInstances.find(str);
						if (it == pGlobal->m_templateInstances.end())
						{
					//		return (*it).second;
						pGlobal->m_alltypes.push_back(pNamedType);
						}
					#endif
					}
					*/

					/*
					Typedef* pTypedef = new Typedef(pInstantiatedMember->m_name, pInstantiatedMember->m_pType);
				//	pTypedef->m_pOwnerScope = pInstantiatedClass->m_pScope;
				//	pTypedef->AddRef();
					pInstantiatedClass->m_pScope->m_types.insert(typemap::value_type(pTypedef->m_name, pTypedef));

					pGlobal->m_alltypes.push_back(pTypedef);
					*/

//						pGlobal->m_alltypes.insert(typemap::value_type(pTypedef->m_name, pTypedef));
				}
			}
		}
	}
}

ClassType* newInstantiateTemplate(Scope* pOwnerScope, CGlobal* pGlobal, ClassType* pTemplateClass, const TemplateArgs* pParams, int levels)
{
//	ASSERT(0);

	printlevels(Log, levels);
	Log << "instantiate " << pTemplateClass->m_name << "{";

	ClassType* pDefType2 = NULL;
	TemplateParams* pDefParams = pTemplateClass->m_pTemplateParams;
	Type* pDefType3 = NULL;
	TemplatedClassArg* pDefArg = nullptr;
	/*
	if (*pTemplateClass->m_name == "Vector")
	{
		pDefType2 = ((ClassType*)pTemplateClass->m_pTemplateParams->m_items[1]->u.m_pType->m_defaultArg->m_pType);
		pDefType3 = pTemplateClass->m_pTemplateParams->m_items[1]->u.m_pType;
		pDefArg = pTemplateClass->m_pTemplateParams->m_items[1]->u.m_pType->m_defaultArg;
		StringA* str = pDefType2->m_qname;
		pDefType2->m_readonly = true;

	}
	*/

// class System::stub1<class std::binder1st<class std::mem_fun1_t<int,class System::UI::DependencyObject,class System::Object *> >,void,class System::Object *> `RTTI Type Descriptor' {vtable=0x0136fdd8 _m_data=0x00000000 rawname=0x013e1d28 ".?AV?$stub1@V?$binder1st@V?$mem_fun1_t@HVDependencyObject@UI@System@@PAVObject@3@@std@@@std@@XPAVObject@System@@@System@@" }	System::TypeDescriptor *

	/*
	{
		printlevels(levels);
		for (int i = 0; i < pParams->m_pInstanceArgs->m_items.size(); i++)
		{
			pTemplateClass->m_pTemplateParams->m_items[i]->m_pType
		}
	}
	*/

//	pTemplateClass->m_pInstantiatedFromArgs = pParams;

	ClassType* pInstantiatedClass = new ClassType();
	pInstantiatedClass->m_typelib = pGlobal->m_typelib;

	pInstantiatedClass->m_pInstantiatedFromClass = pTemplateClass;

	if (pOwnerScope == nullptr)
		pOwnerScope = pTemplateClass->m_ownerScope;

	pInstantiatedClass->m_packing = pTemplateClass->m_packing;

//	pInstantiatedClass->m_sourcefile = pTemplateClass->m_sourcefile;
	pInstantiatedClass->m_def = true;
	pInstantiatedClass->m_kwType = pTemplateClass->m_kwType;
	pInstantiatedClass->m_name = pTemplateClass->m_name;	// TODO ??
	pInstantiatedClass->m_sourcefile = pTemplateClass->m_sourcefile;
//	pInstantiatedClass->m_qname = pTemplateClass->m_qname;	// TODO ??
	pInstantiatedClass->m_ownerScope = pOwnerScope;//*/pTemplateClass->m_pOwnerScope;
	pInstantiatedClass->m_pScope->m_pParentScope = pOwnerScope;//pTemplateClass->m_pOwnerScope;
	// TODO
	Declarator* declType = new Declarator(pInstantiatedClass, String());
	declType->m_typedef = true;
//	declType->m_pType = pInstantiatedClass;
	pInstantiatedClass->m_ownerDecl = declType;

	ASSERT(pTemplateClass->m_pTemplateParams);

#if 0
	ASSERT(pParams->m_pInstanceArgs->m_pClass == pTemplateClass);
	ASSERT(pParams->m_pInstanceArgs->m_pClass->m_pTemplateParams);
#endif
	pInstantiatedClass->m_pInstantiatedFromArgs = pParams->m_pInstanceArgs;

//	pInstantiatedClass->m_pInstantiatedFromArgs = pParams;

	map<Type*, Type*> type2type;

	type2type[pTemplateClass] = pInstantiatedClass;

	ASSERT(!pInstantiatedClass->m_name.Contains(':'));

	{
		if (pInstantiatedClass->m_pInstantiatedFromArgs->m_items.size() != pTemplateClass->m_pTemplateParams->m_items.size())
		{
			Std::get_Out() << pTemplateClass->m_sourcefile << paren(pTemplateClass->m_line+1) << " : error : wrong number of template args" << "\n";
			++pGlobal->m_errors;
			return nullptr;
		}

		for (size_t i = 0; i < pInstantiatedClass->m_pInstantiatedFromArgs->m_items.size(); ++i)
		{
			ActualTemplateArg* pArg = pInstantiatedClass->m_pInstantiatedFromArgs->m_items[i];
			FormalTemplateArg* pFormalArg = pTemplateClass->m_pTemplateParams->m_items[i];

			if (pFormalArg->m_kind == FormalTemplateArg::Param_Type)
			{
				if (pArg->m_pType)
				{
					ASSERT(pArg->m_pType);
					Type* pType = Evaluate(pGlobal, NULL/*pOwnerScope*/, pArg->m_pType, pParams, type2type, levels+1);
					ASSERT(pType);
					pInstantiatedClass->m_pInstantiatedFromArgs->m_items[i]->m_pType = pType;//Evaluate(pGlobal, pOwnerScope, pArg->m_pType, pParams, type2type);

					type2type[pFormalArg->u.m_pType] = pParams->m_pInstanceArgs->m_items[i]->m_pType;
				}
				else
				{
					Std::Out << __FILE__ << "(" << __LINE__ << ")" << " : INTERNAL ERROR: TemplatedClassArg* pArg->m_pType = NULL\n";
				}
			}
		}
	}

	/*
	{
		for (int i = 0; i < pParams->m_pInstanceArgs->m_items.size(); i++)
		{
			type2type[pTemplateClass->m_pTemplateParams->m_items[i]->m_pType] = pParams->m_pInstanceArgs->m_items[i]->m_pType;
		}
	}
	*/

	/*
	for (int i = 0; i < pParams->m_pInstanceArgs->m_items.size(); i++)
	{
		if (i > 0) printf(", ");
		printArg(pInstantiatedClass->m_pInstantiatedFromArgs->m_items[i]);
	}
	printf(">\n");
	*/

	/*
	if (*pTemplateClass->m_name == "Vector")
	{
		ClassType* pType2 = ((ClassType*)pTemplateClass->m_pTemplateParams->m_items[1]->m_pType->m_defaultArg->m_pType);

		Type* pTestType3 = pTemplateClass->m_pTemplateParams->m_items[1]->m_pType;
		TemplatedClassArg* pTestDefArg = pTemplateClass->m_pTemplateParams->m_items[1]->m_pType->m_defaultArg;

		StringA* str = pType2->m_qname;
		MessageBeep(-1);
	}
	*/

	if (pTemplateClass->m_pInstantiatedFromArgs)
	{
		ASSERT(0);

		for (size_t i = 0; i < pTemplateClass->m_pInstantiatedFromArgs->m_items.size(); ++i)
		{
			TemplatedClassArg* pArg = pTemplateClass->m_pInstantiatedFromArgs->m_items[i];

			Type* pType = Evaluate(pGlobal, pOwnerScope, pArg->m_pType, pParams, type2type, levels);
		}
	}

	IO::StringWriter strbuilder;
	pInstantiatedClass->Write(strbuilder);
	String str = strbuilder.str();
//	printf("%s\n", str->c_str());
	pInstantiatedClass->m_qname = str;
	/*
	if (*str == "System::vector<System::TemplatedClassArg *,System::__gc_allocator>")
	{
		MessageBeep(-1);
	}
	*/
//	ASSERT(!pInstantiatedClass->m_readonly);

	/*
	if (strstr(str->c_str(), "SVGStringListCommaSeparated") && strstr(str->c_str(), "CXMLAttr2T") && strstr(str->c_str(), "CValueTypeWrapper") && strstr(str->c_str(), "CreateInstanceT"))
	{
		MessageBeep(-1);
	}
	*/

	auto it = pGlobal->m_templateInstances.find(str);
	if (it != pGlobal->m_templateInstances.end())
	{
		Log << "}\n";
		return (ClassType*)it->second;
	}

	ASSERT(pInstantiatedClass->m_def);
	/*
	if (*str == "vector<double,System::__gc_allocator>")
	{
		MessageBeep(-1);
	}
	*/
	pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, pInstantiatedClass));

	ASSERT(pInstantiatedClass->m_pTemplateParams == nullptr);
	if (ContainsTemplateArg(pInstantiatedClass))
	{
	//	ASSERT(!ContainsTemplateArg(pInstantiatedClass));

		Std::Out << __FILE__ "(" << __LINE__ << "): TODO, FIX BUG??\n";
	}
	ASSERT(pInstantiatedClass->m_name);
	/*
									if (pInstantiatedClass->m_qname == "template System::List<class,class>::Enumerator")
									{
										MessageBeep(-1);
									}
									*/

	pGlobal->m_alltypes.push_back(pInstantiatedClass);

	g_instantiatedTemplate.push(pTemplateClass);
	g_instantiatedClass.push(pInstantiatedClass);

/*	
	for (int i = 0; i < pTemplateClass->m_bases.GetSize(); i++)
	{
		BaseClass* base = pTemplateClass->m_bases[i];
		BaseClass* baseclass = new BaseClass;

		baseclass->m_pClass = (ClassType*)Evaluate(pGlobal, base->m_pClass->m_pOwnerScope, base->m_pClass, pParams, type2type);
		ASSERT(baseclass->m_pClass->get_Kind() == type_class);

		pInstantiatedClass->m_bases.push_back(baseclass);
	}
*/
	instant(pGlobal, pInstantiatedClass, pTemplateClass, pParams, type2type, levels);

	g_instantiatedTemplate.pop();
	g_instantiatedClass.pop();

	Log << "}";
	System::printClass(Log, pInstantiatedClass, levels+1);
	Log << "\n";

	return pInstantiatedClass;
}

ClassType* newInstantiateTemplate2(ClassType* const pInstantiatedClass, Scope* pOwnerScope, CGlobal* pGlobal, ClassType* pTemplateClass, const TemplateArgs* pParams, map<Type*, Type*> & _type2type, int levels)
{
	pInstantiatedClass->m_sourcefile = pTemplateClass->m_sourcefile;
	pInstantiatedClass->m_line = pTemplateClass->m_line;

	printlevels(Log, levels);

	if (pOwnerScope == nullptr)
	{
		Log << "ownerScope = nullptr, ";
	}

	Log << "instantiate2" << pTemplateClass->m_name << "{<";

	/*
	if (*pTemplateClass->m_name == "Vector")
	{
		pTemplateClass->m_readonly = true;
		StringA* str = ((ClassType*)pTemplateClass->m_pTemplateParams->m_items[1]->u.m_pType)->m_qname;
		MessageBeep(-1);
	}
	*/

	/*
	for (int i = 0; i < pParams->m_pInstanceArgs->m_items.size(); i++)
	{
		if (i > 0) printf(", ");
		printArg(pParams->m_pInstanceArgs->m_items[i]);
	}
	printf(">");
	*/

	TemplateArgs args;
	args.m_parent = pParams;

	map<Type*, Type*> my_type2type;

	map<Type*, Type*>& type2type = pOwnerScope == NULL? my_type2type: _type2type;

	if (pOwnerScope == nullptr)
	{
		pOwnerScope = pTemplateClass->m_ownerScope;
	}

//	if (pTemplateClass->m_pInstantiatedFromClass)	// ??
	if (pTemplateClass->m_pInstantiatedFromArgs)	// ??
	{
#if 0
		ASSERT(pTemplateClass->m_pInstantiatedFromClass == pTemplateClass->m_pInstantiatedFromArgs->m_pClass);
#endif

	//	pInstantiatedClass = new ClassType;

		pInstantiatedClass->m_pInstantiatedFromClass = pTemplateClass->m_pInstantiatedFromClass;

	//	pInstantiatedClass->m_sourcefile = pTemplateClass->m_sourcefile;

		pInstantiatedClass->m_packing = pTemplateClass->m_packing;

	//	pInstantiatedClass = pTemplateClass;
		pInstantiatedClass->m_pInstantiatedFromArgs = new TemplatedClassArgs;//pTemplateClass->m_pInstantiatedFromArgs;
#if 0
		pInstantiatedClass->m_pInstantiatedFromArgs->m_pClass = pTemplateClass->m_pInstantiatedFromArgs->m_pClass;
#endif

		ASSERT(pTemplateClass->m_pInstantiatedFromArgs->m_items.size() == pTemplateClass->m_pInstantiatedFromClass->m_pTemplateParams->m_items.size());

		type2type[pTemplateClass->m_pInstantiatedFromClass] = pInstantiatedClass;

		for (size_t i = 0; i < pTemplateClass->m_pInstantiatedFromArgs->m_items.size(); ++i)
		{
			if (i > 0) Log << ", ";

			TemplatedClassArg* pArg = pTemplateClass->m_pInstantiatedFromArgs->m_items[i];

			TemplatedClassArg* pArg2 = new TemplatedClassArg;
			if (pArg->m_pType)
			{
				pArg2->m_pType = Evaluate(pGlobal, nullptr/*pOwnerScope*/, pArg->m_pType, pParams, _type2type, levels);

				if (pTemplateClass->m_pInstantiatedFromClass->m_pTemplateParams->m_items[i]->u.m_pType != pArg2->m_pType)
					type2type[pTemplateClass->m_pInstantiatedFromClass->m_pTemplateParams->m_items[i]->u.m_pType] = pArg2->m_pType;//pParams->m_pInstanceArgs->m_items[i]->m_pType;
			}
			else
			{
				pArg2->m_value = pArg->m_value;
			}

			printArg(Log, pArg2, nullptr);

		//	type2type[pArg->m_pType] = pArg2->m_pType;

			ASSERT(pArg2);
		//	ASSERT(pArg2->m_pType);
			pInstantiatedClass->m_pInstantiatedFromArgs->m_items.push_back(pArg2);
		}

		Log << ">";

		args.m_pInstanceArgs = pInstantiatedClass->m_pInstantiatedFromArgs;
		args.m_pTemplateParams = pTemplateClass->m_pInstantiatedFromClass->m_pTemplateParams;

#if 0
		pTemplateClass = pTemplateClass->m_pInstantiatedFromArgs->m_pClass;
#endif

		{
		//	for (int i = 0; i <pTemplateClass->m_pInstantiatedFromArgs->m_pClass->m_items.size(); i++)
			{
//				type2type[pTemplateClass->m_pInstantiatedFromArgs->m_pClass->m_items[i]->m_pType] = pParams->m_pInstanceArgs->m_items[i]->m_pType;
			}
		}
		Log << "\tpTemplateClass->m_pInstantiatedFromArgs";
		Log << "\n";
	}
	else
	{
		//	pInstantiatedClass = new ClassType;

		if (!Log->IsNull())
		{
			for (size_t i = 0; i < pParams->m_pInstanceArgs->m_items.size(); ++i)
			{
				if (i > 0) Log << ", ";
				printArg(Log, pParams->m_pInstanceArgs->m_items[i], nullptr);
			}
			Log << ">";
		}

		pInstantiatedClass->m_packing = pTemplateClass->m_packing;
		pInstantiatedClass->m_pInstantiatedFromClass = pTemplateClass;

		args.m_pInstanceArgs = new TemplatedClassArgs;

		type2type[pTemplateClass] = pInstantiatedClass;

		if (pTemplateClass->m_pTemplateParams)
		{
			Log << "\tpTemplateClass->m_pTemplateParams";
			Log << "\n";

			pInstantiatedClass->m_pTemplateParams = new TemplateParams;

			args.m_pTemplateParams = pTemplateClass/*pInstantiatedClass*/->m_pTemplateParams;

			for (uint i = 0; i < pTemplateClass->m_pTemplateParams->m_items.size(); ++i)
			{
				System::FormalTemplateArg* param = new System::FormalTemplateArg;
				param->u.m_pType = new _TemplateArgType;
				param->u.m_pType->m_name = pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType->m_name;
				param->u.m_pType->m_index = pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType->m_index;
				param->u.m_pType->m_pClass = pInstantiatedClass->m_pTemplateParams;//pTemplateClass->m_pTemplateParams->m_items[i]->m_pType->m_pClass;
				if (pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg)
				{
					param->u.m_pType->m_defaultArg = new TemplatedClassArg;
					if (pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg->m_pType)
					{
						param->u.m_pType->m_defaultArg->m_pType = Evaluate(pGlobal, pOwnerScope, pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg->m_pType, pParams, type2type, levels);
					//	SetReadOnly(param->u.m_pType->m_defaultArg->m_pType);
					}
					else
					{
						param->u.m_pType->m_defaultArg->m_value = pTemplateClass->m_pTemplateParams->m_items[i]->u.m_pType->m_defaultArg->m_value;
					}
				}

				pInstantiatedClass->m_pTemplateParams->m_items.push_back(param);

				{
					TemplatedClassArg* p = new TemplatedClassArg;
					p->m_pType = param->u.m_pType;
					ASSERT(p->m_pType);
					args.m_pInstanceArgs->m_items.push_back(p);
				}
			}
		}
		else
		{
			Log << "\n";
		}
	}

	pInstantiatedClass->m_def = true;
	pInstantiatedClass->m_kwType = pTemplateClass->m_kwType;
	pInstantiatedClass->m_name = pTemplateClass->m_name;
//	pInstantiatedClass->m_pScope->m_name = pInstantiatedClass->m_name;
	pInstantiatedClass->m_ownerScope = pOwnerScope;
	pInstantiatedClass->m_pScope->m_pParentScope = pOwnerScope;

	ASSERT(!pInstantiatedClass->m_name.Contains(':'));

	IO::StringWriter strbuilder;
	pInstantiatedClass->Write(strbuilder);
	String str = strbuilder.str();
//	printf("%s\n", str->c_str());
//	ASSERT(!pInstantiatedClass->m_readonly);
	pInstantiatedClass->m_qname = str;
	/*
	if (*str == "System::vector<System::TemplatedClassArg *,System::__gc_allocator>")
	{
		MessageBeep(-1);
	}
	*/
//	ASSERT(!pInstantiatedClass->m_readonly);

	auto it = pGlobal->m_templateInstances.find(str);
	if (it != pGlobal->m_templateInstances.end())
	{
		Log << "}\n";
		return (ClassType*)(*it).second;
	}

	ASSERT(pInstantiatedClass->m_def);
	/*
	if (*str == "vector<double,System::__gc_allocator>")
	{
		MessageBeep(-1);
	}
	*/
	pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, pInstantiatedClass));

	/*
	if (pTemplateClass->m_pTemplateParams == NULL)
	{
	//	ASSERT(pInstantiatedClass->m_pTemplateParams == 0);
		ASSERT(!ContainsTemplateArg(pInstantiatedClass));
		pGlobal->m_alltypes.push_back(pInstantiatedClass);
	}
	else
	*/
	{
		// hm..
		if (!ContainsTemplateArg(pInstantiatedClass))
		{
			ASSERT(pInstantiatedClass->m_name);
			pGlobal->m_alltypes.push_back(pInstantiatedClass);
		}
	}

	/*
	if (pTemplateClass->m_pInstantiatedFromArgs)
	{
		ASSERT(!ContainsTemplateArg(pInstantiatedClass));

	}
	*/

/*
	for (int i = 0; i < pTemplateClass->m_bases.GetSize(); i++)
	{
		BaseClass* base = pTemplateClass->m_bases[i];
		BaseClass* baseclass = new BaseClass;
		baseclass->m_pClass = (ClassType*)Evaluate(pGlobal, NULL base->m_pClass->m_pOwnerScope, base->m_pClass, &args, type2type);
	
		pInstantiatedClass->m_bases.push_back(baseclass);
	}
*/

	if (pTemplateClass->m_pInstantiatedFromClass)	// ??
	{
		pTemplateClass = pTemplateClass->m_pInstantiatedFromClass;
	}

	instant(pGlobal, pInstantiatedClass, pTemplateClass, &args, type2type, levels);

	if (!Log->IsNull())
	{
		Log << "}";
		printClass(Log, pInstantiatedClass, levels+1);
		Log << "\n";
	}

	/*
	if (strstr(str->c_str(), "FontFamilyStyles"))
	{
		MessageBeep(-1);
	}
	*/

	return pInstantiatedClass;
}

// TODO, remove this function ??
ClassType* newInstantiateTemplate2(Scope* pOwnerScope, CGlobal* pGlobal, ClassType* pTemplateClass, const TemplateArgs* pParams, map<Type*, Type*> & _type2type, int levels)
{
	ClassType* pInstantiatedClass = new ClassType;
	//pInstantiatedClass->m_ownerDecl = new Declarator(pInstantiatedClass, "TEST4");
	pInstantiatedClass->m_typelib = pGlobal->m_typelib;

	ClassType* p = newInstantiateTemplate2(pInstantiatedClass, pOwnerScope, pGlobal, pTemplateClass, pParams, _type2type, levels);

//	ASSERT(p->m_packing > 0);
	return p;
}

Expression2List* flatten_and_reverse(Expression2List* primlist, Expression2List* prev)
{
	while (primlist)
	{
		ASSERT(primlist->head);

		Expression2List* next = primlist->tail;

		/*
		if (primlist->head->m_token == '(')
		{
			YYLTYPE pos;
			pos.first_line = primlist->head->m_primlist->head->m_line_pos;
			pos.filename = primlist->head->m_primlist->head->m_filename;

			prev = flatten_and_reverse(primlist->head->m_primlist, new Expression2List(new A_Exp2(pos, ')'), prev));
		}
		*/

		primlist->tail = prev;
		prev = primlist;
		primlist = next;
	}

	return prev;
}

CodeCompExt void StmList(A_StmList* stmList, Scope* pGlobalScope, Scope* pScope);

CodeCompExt A_Stm* Stm(A_Stm* stm, Scope* pGlobalScope, Scope* pScope)
{
	ASSERT(0);
#if 0
	switch (stm->GetKind())
	{
	case A_Stm::A_IF:
		{
			A_IfStm* ifstm = (A_IfStm*)stm;

			printf("if (");

			ifstm->m_cond = PrimList((Expression2List*)ifstm->m_cond, pGlobalScope, pScope);

			printf(")\n");
			ifstm->m_stm = Stm(ifstm->m_stm, pGlobalScope, pScope);

			if (ifstm->m_elseStm)
			{
				printf("\nelse\n");

				ifstm->m_elseStm = Stm(ifstm->m_elseStm, pGlobalScope, pScope);
			}

			return ifstm;
			//return new A_IfStm(cond, stm, elseStm);
		}
		break;

	case A_Stm::A_LABEL:
		{
			A_LabelStm* labelstm = (A_LabelStm*)stm;

			printf("%s:\n", labelstm->m_name->c_str());

			return Stm(labelstm->m_stm, pGlobalScope, pScope);
		}
		break;

	case A_Stm::A_GOTO:
		{
			A_GotoStm* gotostm = (A_GotoStm*)stm;

			printf("goto %s;\n", gotostm->m_name->c_str());
			return gotostm;
		}
		break;

	case A_Stm::A_WHILE:
		{
			A_WhileStm* whilestm = (A_WhileStm*)stm;

			/*
			printf("while (");
			PrimList(whilestm->m_cond, pGlobalScope, pScope);
			printf(")\n");
			*/

			whilestm->m_cond = PrimList((Expression2List*)whilestm->m_cond, pGlobalScope, pScope);
			whilestm->m_stm = Stm(whilestm->m_stm, pGlobalScope, pScope);

			return whilestm;
		}
		break;

	case A_Stm::A_DOWHILE:
		{
			A_DoWhileStm* dowhilestm = (A_DoWhileStm*)stm;

			printf("do\n");

			dowhilestm->m_stm = Stm(dowhilestm->m_stm, pGlobalScope, pScope),
			dowhilestm->m_exp = PrimList((Expression2List*)dowhilestm->m_exp, pGlobalScope, pScope)->m_exp;

			return dowhilestm;
		}
		break;

	case A_Stm::A_FOR:
		{
			A_ForStm* forstm = (A_ForStm*)stm;
			
			printf("for(;;)\n");

			forstm->m_init = PrimList((Expression2List*)forstm->m_init, pGlobalScope, pScope),
			forstm->m_cond = PrimList((Expression2List*)forstm->m_cond, pGlobalScope, pScope)->m_exp,
			forstm->m_exp = PrimList((Expression2List*)forstm->m_exp, pGlobalScope, pScope)->m_exp,
			forstm->m_stm = Stm(forstm->m_stm, pGlobalScope, pScope);

			return forstm;
		}
		break;

	case A_Stm::A_SWITCH:
		{
			A_SwitchStm* switchstm = (A_SwitchStm*)stm;
			printf("switch()\n");

			switchstm->m_cond = PrimList((Expression2List*)switchstm->m_cond, pGlobalScope, pScope);
			switchstm->m_stm = Stm(switchstm->m_stm, pGlobalScope, pScope);

			return switchstm;
		}
		break;

	case A_Stm::A_COMPOUND:
		{
			A_CompoundStm* compound = (A_CompoundStm*)stm;
			printf("{\n");
			StmList(compound->m_stmList, pGlobalScope, pScope);
			printf("}\n");

			return compound;
		}
		break;

	case A_Stm::A_RETURN:
		{
			A_ReturnStm* returnstm = (A_ReturnStm*)stm;

			printf("return");
			if (returnstm->m_exp)
			{
				printf(" ");
				A_ExpOrDecl* expordecl = PrimList((Expression2List*)returnstm->m_exp, pGlobalScope, pScope);
				ASSERT(expordecl->m_exp);
				returnstm->m_exp = expordecl->m_exp;
			}
			else
			{
				printf(";\n");
			}
			return returnstm;
		}
		break;

	case A_Stm::A_CASE:
		{
			A_CaseStm* casestm = (A_CaseStm*)stm;

			printf("case:\n");

			casestm->m_exp = PrimList((Expression2List*)casestm->m_exp, pGlobalScope, pScope)->m_exp;
			casestm->m_stm = Stm(casestm->m_stm, pGlobalScope, pScope);

			return casestm;
		}
		break;

	case A_Stm::A_DEFAULT:
		{
			A_DefaultStm* defaultstm = (A_DefaultStm*)stm;
			printf("default:\n");
			defaultstm->m_stm = Stm(defaultstm->m_stm, pGlobalScope, pScope);

			return defaultstm;
		}
		break;

	case A_Stm::A_CONTINUE:
		{
			printf("continue\n");
			return stm;
		}
		break;

	case A_Stm::A_BREAK:
		{
			printf("break\n");
			return stm;
		}
		break;

	case A_Stm::A_PRIMLIST:
		{
			A_ExpOrDecl* expordecl = PrimList(((A_PrimListStm*)stm)->m_primlist, pGlobalScope, pScope);
			if (expordecl->m_decl)
				return new A_DeclarationStm(expordecl->m_decl);
			else
				return new A_ExpStm(expordecl->m_exp);
			printf(";\n");
		}
		break;
	}
#endif
	ASSERT(0);
	return NULL;
}

CodeCompExt void StmList(A_StmList* stmList, Scope* pGlobalScope, Scope* pScope)
{
	while (stmList)
	{
		ASSERT(stmList->head);

	//	stmList->head = Stm(stmList->head, pGlobalScope, pScope);

		stmList = stmList->tail;
	}
}

/*
CodeCompExt void FunBody(A_FunDef* fundef, CGlobal* pGlobal, Scope* pScope)
{
	A_StmList* stmList = fundef->m_stmList;

	StmList(stmList, pGlobal->m_pGlobalScope, pScope);
}
*/

//CDeclarator* decl2;

Declarator* FunDef(FunDefDecl* fundef, CGlobal* pGlobal, Scope* pScope, Scope* pTScope, TemplateParams* tp, int linkage, bool bInsideTemplate)
{
	bool bTypedef = false;
	bool bExtern = false;
	bool bVirtual = false;
	bool bStatic = false;

	DeclSpecList* decllist = fundef->m_declspec;
	while (decllist)
	{
		if (decllist->head == NULL)
		{
			decllist = decllist->tail;
			continue;
		}

		if (decllist->head->GetKind() == A_DeclSpec::A_TYPE_MODIFIER)
		{
			A_DeclSpecModifier* pModifier = (A_DeclSpecModifier*)decllist->head;

			if (pModifier->m_modifier == A_TYPEDEF)
			{
				if (bTypedef)
					Std::Out << "warn: typedef already specified";

				bTypedef = true;
			}
			else if (pModifier->m_modifier == A_EXTERN)
			{
				if (bExtern)
					Std::Out << "warn: extern already specified";

				bExtern = true;
			}
			else if (pModifier->m_modifier == A_VIRTUAL)
			{
				if (bVirtual)
					Std::Out << ("warn: virtual already specified");

				bVirtual = true;
			}
			else if (pModifier->m_modifier == A_STATIC)
			{
				if (bStatic)
					Std::Out << ("warn: static already specified\n");

				bStatic = true;
			}
		}

		decllist = decllist->tail;
	}

	Declarator* pDeclarator = new Declarator;

	pDeclarator->m_virtual = bVirtual;
	pDeclarator->m_static = bStatic;
	pDeclarator->m_cpp_linkage = linkage == 1;

	Type* pType = GetType(fundef->m_declspec, NULL, pGlobal, pScope, pTScope, NULL/*fun*/, tp, linkage, bInsideTemplate);///*pTScope*//*pScope*/, tp/*tp*/, false/*bInsideTemplate*/);//NULL;//d->fundef.declspecList
	pDeclarator->m_pType = pType;
	/*if (pType == NULL)
	{
		MessageBeep(-1);
	}
	*/
	Scope* pScope2 = Extract(fundef->m_declarator, pDeclarator, pType, pScope, pTScope, NULL/*fun*/, tp, pGlobal, bInsideTemplate);

//	pGlobal->m_globals.push_back(pDeclarator);

	/*
	if (*pDeclarator->m_name == "getTransformMatrix")
	{
		MessageBeep(-1);
		if (decl2 == NULL)
			decl2 = pDeclarator;
	}
	*/

	ASSERT(pDeclarator->m_pType->get_Kind() == type_function);

	pDeclarator->m_pType->AsFunction()->m_pTemplateParams = tp;

	if (false)
	{
		if (pScope2->m_pNamespace->AsClass())
		{
			pDeclarator = pScope2->m_pNamespace->AsClass()->GetDeclarator(pDeclarator->m_name);
			ASSERT(pDeclarator->m_pType->get_Kind() == type_function);
		}

		ASSERT(pDeclarator->m_name.GetLength());
		ASSERT(pDeclarator->m_pType != NULL);
		pScope->m_orderedDecls.push_back(pDeclarator);

		pDeclarator->m_defined = true;//!bExtern && (pDeclarator->m_pType->GetKind() != type_function);
		pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));

		FunBody(pDeclarator, fundef, pGlobal, pScope2, linkage);
	}
	else
	{
		ASSERT(pDeclarator->m_name.GetLength());
		ASSERT(pDeclarator->m_pType != NULL);
		pScope->m_orderedDecls.push_back(pDeclarator);

		pDeclarator->m_defined = true;//!bExtern && (pDeclarator->m_pType->GetKind() != type_function);
		pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
	}

//	FunBody(fundef, pGlobal, pScope2);
	return pDeclarator;
}

Type* GetType(DeclSpecList* declspecList, InitDeclaratorList* declaratorList, CGlobal* pGlobal, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams* tp, int linkage, bool bInsideTemplate)
{
	DeclSpecList* dlist = NULL;

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
		A_DeclSpec* decl = dlist->head;

		if (decl->GetKind() == A_DeclSpec::A_TYPE_MODIFIER)
		{
			DeclSpecifierKeyword modifier = static_cast<A_DeclSpecModifier*>(decl)->m_modifier;

			if (modifier == A_CONST)
			{
				if (bConst)
					Std::Out << ("warn: const already specified\n");

				bConst = true;
			}
			else if (modifier == A_VOLATILE)
			{
				if (bVolatile)
					Std::Out << ("warn: volatile already specified\n");

				bVolatile = true;
			}
			else if (modifier == A_FRIEND)
			{
				if (bFriend)
					Std::Out << ("warn: friend already specified\n");

				bFriend = true;
			}
		}
		else if (decl->GetKind() == A_DeclSpec::A_TYPE_BASIC)				
		{
			BasicTypeSpecifier basicType = static_cast<A_DeclSpecBasicType*>(decl)->m_basicType;

			if (basicType == A_SIGNED)
			{
				if (sign == 1)
					Std::Out << ("warn: signed already specified");
				else if (sign == 2)
					Std::Out << ("error: unsigned already specified");
				else
					sign = 1;
			}
			else if (basicType == A_UNSIGNED)
			{
				if (sign == 2)
					Std::Out << ("warn: unsigned already specified");
				else if (sign == 1)
					Std::Out << ("error: signed already specified");
				else
					sign = 2;
			}
			else if (basicType == A_SHORT)
			{
				if (size == 1)
					Std::get_Out() << decl->m_filename << paren(decl->m_line_pos+1) << " : error C2632: 'short' followed by 'short' is illegal";
				else if (size == 2)
					Std::get_Out() << decl->m_filename << paren(decl->m_line_pos+1) << " : error C2632: 'long' followed by 'short' is illegal";
				else
					size = 1;
			}
			else if (basicType == A_LONG)
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
			A_DeclSpec* decl = dlist->head;

			switch (decl->GetKind())
			{
			case A_DeclSpec::A_TYPE_NAME:
				{
					A_NameType* pTypeName = static_cast<A_NameType*>(decl);
					
					/*
					if (pTypeName->m_name)
					{
					if (strstr(pDeclarator->m_name->c_str(), "red_black_node"))
					{
					MessageBeep(-1);
					}
					}
					*/
					
					Type* pType2 = GetNestedType(pGlobal, NULL, pTScope, pTypeName->m_name, bInsideTemplate);

					/*
					if (pType2)
					{
						// ??
						if (pType2->get_Kind() == type_class)
						{
							while (pType2->GetClass()->m_pInstantiatedFromClass)
							{
								pType2 = pType2->GetClass()->m_pInstantiatedFromClass;
							}
						}
					}
					*/

					if (pType2 == nullptr)
					{
						Expression* exp = pTypeName->m_name;
						
						String qname;
						
						while (1)
						{
							qname += String(exp->binop.left->templateid.id);
							
							exp = exp->binop.right;
							if (exp == NULL) break;
							
							qname += "::";
						}
						
						serror() << decl->m_filename << paren(decl->m_line_pos+1) << " : undeclared type" << qname << "\n";
						//printf("%s(%d): undeclared type %s\n", decl->m_filename, decl->m_line_pos, qname->c_str());
						
					//	pType2 = GetNestedType(pGlobal, NULL, pScope, pTypeName->m_name);
					//	ASSERT(pType2->GetKind() != type_templateinst);
						
						break;
					}

					if (tp == NULL)
					{
#if 0
						if (pType2->GetKind() == type_templateinst)
						{
							TemplateArgs templateArgs;
						//	templateArgs.m_args = pTType->m_items.GetData();
							templateArgs.m_pInstanceArgs = ((TemplatedClassType*)pType2)->m_pInstantiatedFromArgs;
							templateArgs.m_parent = NULL;	// ?

							pType2 = InstantiateTemplate3(pScope, pGlobal, (TemplatedClassType*)pType2/*pTType->m_pClass*/, &templateArgs/*pTType->m_items.GetData()*/);
							//pMember->m_pType = pMemberType;


						}
#endif
#if 0
						if (pType2->GetKind() == type_templateinst || pType2->GetKind() == type_class)
						{
							pType2 = InstantiateTemplate3(pScope, pGlobal, (TemplatedClassType*)pType2/*pTType->m_pClass*/);
						}
#endif

#if 0
						if (pType2->GetKind() == type_class &&
							pType2->GetClass()->m_items.size())
						{
							pType2 = InstantiateTemplate(pScope, pGlobal, (TemplatedClassType*)pType2/*pTType->m_pClass*/, &templateArgs/*pTType->m_items.GetData()*/);
						}
#endif

					}
					
					if (pType2 == NULL)
					{
					/*
					if (decl->name->kind == Expression::A_ID)
					{
					printf("%s(%d): undeclared type %s\n", decl->m_filename->c_str(), decl->m_line_pos, decl->name->id);
					}
					else
						*/
						//		pType2 = GetNestedType(NULL, pScope, decl->name);
						
						Expression* exp = pTypeName->m_name;
						
						String qname;
						
						while (1)
						{
							qname += String(exp->binop.left->templateid.id);
							
							exp = exp->binop.right;
							if (exp == nullptr) break;
							
							qname += "::";
						}
						
						serror() << decl->m_filename << paren(decl->m_line_pos+1) << " : undeclared type " << qname << "\n";
						
					//	pType2 = GetNestedType(pGlobal, NULL, pScope, pTypeName->m_name);
					//	ASSERT(pType2->GetKind() != type_templateinst);
						
						break;
					}
					
					pType = pType2;
				}
				break;
				
			case A_DeclSpec::A_TYPE_ENUM:
				{
					A_Enum* DeclEnum = static_cast<A_Enum*>(decl);
					
					if (DeclEnum->m_name)
					{
						pType = pScope->GetType(DeclEnum->m_name);
						if (pType != NULL/*i == pScope->m_types.end()*/)
						{
							serror() << DeclEnum->m_filename << paren(DeclEnum->m_line_pos+1) << " : error : already defined enum " << "'" << DeclEnum->m_name << "'" << "\n";
						}
					}
					
					if (pType == nullptr)
					{
						EnumType* pEnum = new EnumType(DeclEnum->m_name);
						if (DeclEnum->m_baseType)
						{
						//	__asm int 3
							pEnum->m_baseType = GetType(DeclEnum->m_baseType, nullptr, pGlobal,
								nullptr, nullptr, nullptr, nullptr, 0, false);	// TODO
						}

						pEnum->m_typelib = pGlobal->m_typelib;
						pEnum->m_ownerScope = pScope;
					//	pEnum->m_filepath = DeclEnum->m_filename;
						pEnum->m_sourcefile = pGlobal->AddSourceFile(SplitPath(pGlobal, CString(DeclEnum->m_filename).Detach()));	// TODO, doesn't really make any sence, namespaces don't have one place of definition
						pEnum->m_sourcefile_it = pEnum->m_sourcefile->Add(pEnum);

						DeclEnum->m_deflist = DeclEnum->m_deflist;
						
						pType = pEnum;
						
						int value = 0;

						for (auto list2 = DeclEnum->m_deflist; list2 != nullptr; list2 = list2->tail)
						{
							if (list2->head->m_exp)
							{
								SExp* exp = TransExpression(list2->head->m_exp, pGlobal, pScope);
								if (exp->GetKind() != SExp::SEXP_INT)
								{
									Std::get_Out() << list2->head->m_exp->m_filename << paren(list2->head->m_exp->m_line_pos+1) << " : error : enum not const" << "\n";
									++pGlobal->m_errors;
								}
								else
								{
									value = dynamic_cast<SValExp*>(exp)->m_val;
								}
							}
							
							//EnumDef* def = new EnumDef(list2->head->m_name, value);
							pEnum->m_deflist.push_back(EnumDef(list2->head->m_name, value));
							
							Declarator* pDeclarator = new Declarator(pEnum, list2->head->m_name);
							pDeclarator->m_sourcefile = pGlobal->AddSourceFile(SplitPath(pGlobal, CString(list2->head->m_filename).Detach()));
							pDeclarator->m_sourcefile_it = pEnum->m_sourcefile->Add(pDeclarator);
							pDeclarator->m_sourceline = list2->head->m_line;
							pDeclarator->m_localVar = 2;	// 2 means enum identifier
							pDeclarator->m_offset = value;	// m_offset is used for value
							
						//	pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_identdecls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							
							++value;
						}
						
						if (DeclEnum->m_name)
						{
							Declarator* pDeclarator = new Declarator(pEnum, pEnum->m_name);
							pDeclarator->m_typedef = true;
						//	pDeclarator->m_name = pEnum->m_name;
						//	pDeclarator->m_pType = pEnum;
							pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_orderedDecls.push_back(pDeclarator);
							
							pScope->m_types.insert(typemap::value_type(pEnum->m_name, pEnum));
							//	pGlobal->m_alltypes.insert(typemap::value_type(pEnum->m_qname, pEnum));
							
#if 0	// ??
							pGlobal->m_types.Add(pEnum);
#endif
							if (true)
							{
								IO::StringWriter strbuilder;
								pEnum->Write(strbuilder);
								String str = strbuilder.str();
							//	printf("%s\n", str->c_str());
								pEnum->m_qname = str;
							//	ASSERT(!pEnum->m_readonly);

								map<String,System::NamedType*>::iterator it = pGlobal->m_templateInstances.find(str);
								if (it == pGlobal->m_templateInstances.end())
								{
									pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, (NamedType*)pEnum));

									//return (*it).second;
								}
								else
									ASSERT(0);
							}
							
							ASSERT(pEnum->m_name);
							pGlobal->m_alltypes.push_back(pEnum);
						}
					}
				}
				break;
				
			case A_DeclSpec::A_TYPE_CLASS:// && !bFriend)	// hm..
				{
					if (!bFriend)
					{
						A_Class* Class = static_cast<A_Class*>(decl);
						
						// TODO, remove these restrictions
						ASSERT(Class->m_head->m_name->kind == Expression::A_BINOP);
						ASSERT(Class->m_head->m_name->binop.left->kind == Expression::A_TEMPLATEID);
						
						Type* pType2;
						
						if (declaratorList == nullptr)
							pType2 = GetNonNestedType(pGlobal, nullptr, pScope, Class->m_head->m_name, bInsideTemplate);
						else
							pType2 = GetNestedType(pGlobal, nullptr, pScope, Class->m_head->m_name, bInsideTemplate);

						if (pType2)
						{
							pType = pType2;
						}
						else
							pType = nullptr;
						
						if (pType != nullptr)
						{
							if (pType->get_Kind() == type_class)
							{
								ClassType* pClass = pType->AsClass();
								
								if (pClass->m_kwType != Class->m_head->m_classKey)
								{
									Std::Out << Class->m_filename << "(" << Class->m_line_pos << ")" << " : warning : " << ClassKeyName(Class->m_head->m_classKey) << " " << CString(Class->m_head->m_name->templateid.id).c_str() << " first seen as " << ClassKeyName((ClassKey)pClass->m_kwType);
									++pGlobal->m_warnings;
								}
							}
							else
							{
								printf("error: '%s %s' already defined as something else\n", ClassKeyName(Class->m_head->m_classKey), CString(Class->m_head->m_name->binop.left->templateid.id).c_str());
							}
						}
						else
						{
							ClassType* pClass = new ClassType();
							pClass->m_typelib = pGlobal->m_typelib;

							pType = pClass;
							pClass->m_pTemplateParams = tp;
							
							pClass->m_ownerScope = pScope;
							if (true)
							{
								pClass->m_pScope->m_pParentScope = pTScope;	// hmm..
							}
							else
							{
								pClass->m_pScope->m_pParentScope = pScope;	// hmm..
							}

							pClass->m_name = Class->m_head->m_name->binop.left->templateid.id;

							if (true)
							{
								IO::StringWriter strbuilder;
								pClass->Write(strbuilder);
								String str = strbuilder.str();
								pClass->m_qname = str;
							//	ASSERT(!pClass->m_readonly);

								auto it = pGlobal->m_templateInstances.find(str);
								if (it == pGlobal->m_templateInstances.end())
								{
									pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, pClass));
								}
								else
									ASSERT(0);

								pGlobal->m_alltypes.push_back(pClass);
							}

							pClass->m_def = false;	// Forward reference
							
							pClass->m_kwType = Class->m_head->m_classKey;
							
							Declarator* pDeclarator = new Declarator;
							pDeclarator->m_typedef = true;
							pDeclarator->m_name = pClass->m_name;
							pDeclarator->m_pType = pClass;
							pDeclarator->m_fwd = true;
							
							pDeclarator->m_sourcefile = pGlobal->AddSourceFile(SplitPath(pGlobal, CString(Class->m_filename).Detach()));
							pDeclarator->m_sourcefile_it = pDeclarator->m_sourcefile->Add(pDeclarator);
							pDeclarator->m_sourceline = Class->m_line_pos;

							pClass->m_sourcefile = pDeclarator->m_sourcefile;
							pClass->m_line = Class->m_line_pos;
							pClass->m_ownerDecl = pDeclarator;

							pClass->m_forwardDeclarations.push_back(pDeclarator);

							pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_orderedDecls.Add(pDeclarator);
							pScope->m_types.insert(typemap::value_type(pClass->m_name, pClass));
						}

					}
				}
				break;
				
			case A_DeclSpec::A_TYPE_CLASSDEF:
				{
					A_ClassDef* CLASSDEF = static_cast<A_ClassDef*>(decl);
					
					if (CLASSDEF->m_head == nullptr)
					{
						ASSERT(0);
					}
					ClassType* pClass = nullptr;
					
					if (CLASSDEF->m_head->m_name != nullptr)
					{
						Type* pType2 = GetNonNestedType(pGlobal, nullptr, pScope, CLASSDEF->m_head->m_name, bInsideTemplate);
						
						if (pType2)
						{
							pType = pType2;
						}
						else
							pType = nullptr;
					}
					else
						pType = nullptr;
					
					if (pType != nullptr)
					{
						if (pType->get_Kind() == type_class)
						{
							pClass = pType->AsClass();

							if (tp)
							{
								ASSERT(pClass->m_pTemplateParams != nullptr);
							}

							pClass->m_pTemplateParams = tp;
							pClass->m_ownerScope = pScope;
							if (true)
							{
								pClass->m_pScope->m_pParentScope = pTScope;	// hmm..
							}
							else
							{
								pClass->m_pScope->m_pParentScope = pScope;	// hmm..
							}

							if (pClass->m_kwType != CLASSDEF->m_head->m_classKey)
							{
								Console::get_Out() << CLASSDEF->m_filename << "(" << CLASSDEF->m_line_pos+1 << ")" << " : warning : " << ClassKeyName(CLASSDEF->m_head->m_classKey) << " " << CLASSDEF->m_head->m_name << " first seen as " << ClassKeyName((ClassKey)pClass->m_kwType) << endl;
								++pGlobal->m_warnings;
							}

							if (pClass->m_def)
							{
								++pGlobal->m_errors;
								Console::get_Out() << CLASSDEF->m_filename << paren(CLASSDEF->m_line_pos+1) << " : error : class '" << CLASSDEF->m_head->m_name << "' already defined" << "\n";
								if (pClass->m_ownerDecl->m_sourcefile)
								{
									Console::Out << pClass->m_ownerDecl->m_sourcefile->ToString() << paren(pClass->m_ownerDecl->m_sourceline+1) << " : prev" << "\n";
								}
							//	CLASSDEF->m_head->line_pos m_filename << CLASSDEF->m_line_pos
							//	raise(Exception(L"TODO msg"));

								ASSERT(pClass->m_packing > 0);
							}
							else
							{
								ASSERT(pClass->m_packing == 0);

								pClass->m_packing = pGlobal->m_packstack.top();
								ASSERT(pClass->m_packing > 0);
							}
						}
						else
						{
							Console::get_Out() << "class already declared as something else" << endl;
						}

						Declarator* pDeclarator = new Declarator(pClass, pClass->m_name);
						pDeclarator->m_typedef = true;
						pDeclarator->m_fwd = false;

						pDeclarator->m_sourcefile = pGlobal->AddSourceFile(SplitPath(pGlobal, CString(CLASSDEF->m_filename).Detach()));
						pDeclarator->m_sourcefile_it = pDeclarator->m_sourcefile->Add(pDeclarator);
						pDeclarator->m_sourceline = CLASSDEF->m_line_pos;

						pClass->m_ownerDecl = pDeclarator;

						pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
						pScope->m_orderedDecls.Add(pDeclarator);
					//		pScope->m_types.insert(typemap::value_type(pClass->m_name, pClass));
					}
					else
					{
						pClass = new ClassType();
						pClass->m_typelib = pGlobal->m_typelib;
						pClass->m_pTemplateParams = tp;
						pClass->m_ownerScope = pScope;
						if (true)
							pClass->m_pScope->m_pParentScope = pTScope;	// hmm..
						else
							pClass->m_pScope->m_pParentScope = pScope;	// hmm..

						pType = pClass;

						for (DeclSpecList* decllist = CLASSDEF->m_head->m_declspecList; decllist != NULL; decllist = decllist->tail)
						{
							if (decllist->head->GetKind() == A_DeclSpec::A_TYPE_DECLSPECEXT)
							{
								A_DeclSpecExtModifier* mod = static_cast<A_DeclSpecExtModifier*>(decllist->head);
								
								for (auto extlist = mod->m_extlist; extlist != nullptr; extlist = extlist->tail)
								{
									A_DeclSpecExt* ext = extlist->head;
									if (ext->m_id == "align")
									{
										pClass->m_force_alignment = ext->m_arg;
									}
								}
							}
						}
						
						pClass->m_kwType = CLASSDEF->m_head->m_classKey;
						
						if (CLASSDEF->m_head->m_name != nullptr)
						{
							pClass->m_name = CLASSDEF->m_head->m_name->binop.left->templateid.id;
						}

						Declarator* pDeclarator = new Declarator(pClass, pClass->m_name);
						pDeclarator->m_typedef = true;
						pDeclarator->m_fwd = false;

						pDeclarator->m_sourcefile = pGlobal->AddSourceFile(SplitPath(pGlobal, CString(CLASSDEF->m_filename).Detach()));
						if (pDeclarator->m_sourcefile)
						{
							pDeclarator->m_sourcefile_it = pDeclarator->m_sourcefile->Add(pDeclarator);
						}
						pDeclarator->m_sourceline = CLASSDEF->m_line_pos;
						pDeclarator->m_sourcecolumn = CLASSDEF->m_column;

						pClass->m_ownerDecl = pDeclarator;

						if (CLASSDEF->m_head->m_name != nullptr)	// ??
						{
							pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
							pScope->m_orderedDecls.Add(pDeclarator);
							pScope->m_types.insert(typemap::value_type(pClass->m_name, pClass));
						}
					}

					pClass->m_packing = pGlobal->m_packstack.top();
					ASSERT(pClass->m_packing > 0);

					// TODO, it may be set when declared
				//	ASSERT(pClass->m_sourcefile == nullptr);
					// TODO, look above, already set in pDeclarator->m_sourcefile
					pClass->m_sourcefile = pGlobal->AddSourceFile(SplitPath(pGlobal, CString(CLASSDEF->m_filename).Detach()));
					pClass->m_sourcefile_it = pClass->m_sourcefile->Add(pClass);
					pClass->m_line = CLASSDEF->m_line_pos;

					pClass->m_def = true;
					
				//	if (pClass->m_pTemplateParams == NULL)
					{
						if (bInsideTemplate)
						{
							ASSERT(ContainsTemplateArg(pClass));
						}
						else
						{
							ASSERT(!ContainsTemplateArg(pClass));
						}

						//if (!bInsideTemplate)
						if (true)
						{
							if (pClass->m_name)
							{
								IO::StringWriter strbuilder;
								pClass->Write(strbuilder);
								String str = strbuilder.str();
							//	printf("%s\n", str->c_str());
								pClass->m_qname = str;
							//	ASSERT(!pClass->m_readonly);
								/*
	if (*str == "System::vector<System::TemplatedClassArg *,System::__gc_allocator>")
	{
		MessageBeep(-1);
	}

			if (*str == "__release<System::LDraw::Matrix4>")
			{
				MessageBeep(-1);
			}
			*/

								auto it = pGlobal->m_templateInstances.find(str);
								if (it == pGlobal->m_templateInstances.end())
								{
									pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(str, pClass));

									/*
									if (pClass->m_qname == "template System::List<class,class>::Enumerator")
									{
										MessageBeep(-1);
									}
									*/
									pGlobal->m_alltypes.push_back(pClass);
								}
								else
								{
									// It could have been forward declared

									// ASSERT(0);
								}

							}

						//	ASSERT(pClass->m_pTemplateParams == NULL);
						}
					}

					for (auto baseList = CLASSDEF->m_baseList; baseList != NULL; baseList = baseList->tail)
					{
						BaseClass* baseClass = new BaseClass;
						
						Type* pType2;
						
#if 0
						if (baseList->head->kind == Expression::A_ID)
						{
							pType2 = pClass->m_pScope->GetType(baseList->head->id);
							baseClass.m_pClass = pType2->GetClass();
						}
						else if (baseList->head->kind == Expression::A_TEMPLATEID)
						{
							//	pType2 = pTScope->GetType(baseList->head->id);
							System::Type pTemplateClass = pClass->m_pScope->GetType(baseList->head->templateid.exp->id);
							ASSERT(pTemplateClass->m_type == type_class);
							
							TemplatedClassType* pTType = new TempatedClass;
							pTType->AddRef();
							
							pTType->m_pClass = pTemplateClass->AsClass();
							pTType->m_pClass->AddRef();
							
							A_TypeIdList* typeIds = baseList->head->templateid.params;
							while (typeIds)
							{
								A_TypeId* typeId = typeIds->head;
								
								System::Type pTemplateArgType = GetType(typeId->declspecList, pGlobal, pClass->m_pScope, tp, bInsideTemplate);
								//pTemplateArgType->
								
								pTType->m_items.Add(pTemplateArgType);
								
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
						pType2 = GetNestedType(pGlobal, NULL, pClass->m_pScope, baseList->head->m_id, bInsideTemplate);
						
						if (pType2 == NULL)
						{
							if (baseList->head->m_id->kind == Expression::A_ID)
							{
								pType2 = pClass->m_pScope/*pTScope*/->GetType(baseList->head->m_id->templateid.id);
								Console::get_Out() << "undeclared base class " << baseList->head->m_id->templateid.id << endl;
							}
							else
							{
								Console::get_Out() << "undeclared base class" << endl;
							}

							ASSERT(0);
							break;
						}
						
						//ASSERT(dynamic_cast<ClassType*>(pType2));
						baseClass->m_pClass = (ClassType*)pType2;	// TODO, wrong, could be _TemplateArg
						ASSERT(baseClass->m_pClass);
						
						pClass->AsClass()->m_bases.push_back(baseClass);
					}
					
					//if (type->kind == A_DeclSpec::A_TYPE_CLASSDEF)
					{
						vector<ast::Declaration*> methods;
						
						AccessSpec accessSpec;
						
						if (CLASSDEF->m_head->m_classKey == ClassKey_class)
							accessSpec = AccessSpec_Protected;//ACCESS_PROTECTED;
						else
							accessSpec = AccessSpec_Public;
						
						A_MemberSpec* member = CLASSDEF->m_memberSpec;
						while (member)
						{
						//	ASSERT(0);
#if 1
							if (member->GetKind() == A_MemberSpec::A_ACCESS_SPEC)
							{
								accessSpec = static_cast<A_MemberAccessSpec*>(member)->m_accessSpec;
								ASSERT(accessSpec != AccessSpec_Unspecified);
							}
							else
							{
								ast::Declaration* d = ((A_MemberDecl*)member)->m_declaration;
								if (d == nullptr)	// TODO remove
								{
									member = member->m_next;
									continue;
								}
								
								if (d->GetKind() == ast::Declaration::A_TEMPLATE)
								{
									bool bInsideTemplate = true;

									TemplateDeclaration* td = static_cast<TemplateDeclaration*>(d);
									
								//	td->m_params = Reverse(td->m_params);

									TemplateParams* tp = new TemplateParams;
								//	if (tp)
								//	{
										Scope* pTScope;
										pTScope = new Scope;
										pTScope->m_pParentScope = pClass->m_pScope;//->m_pParentScope;
									//	pClass->m_pScope->m_pParentScope = pTScope;
										
										//A_TemplateParameterList * tplist = tp;
										
										/*
										// Reverse list
										{
										A_TemplateParameterList * tp2 = tp;
										while (tp2)
										{
										tplist = new A_TemplateParameterList(tp2->head, tplist);
										tp2 = tp2->tail;
										}
										}
										*/
										
										ast::TemplateParameterList* tp2 = td->m_params;

										int index = 0;
										//tp = tplist;
										//A_TemplateParameterList * tp = d->TEMPLATE.params;
										while (tp2)
										{
											if (tp2->head->GetKind() == ast::TemplateParameter::A_ParamType)
											{
												ast::TypeTemplateParameter* typeparam = dynamic_cast<ast::TypeTemplateParameter*>(tp2->head);
												
												System::FormalTemplateArg* param = new System::FormalTemplateArg;
												param->m_kind = System::FormalTemplateArg::Param_Type;
												param->m_index = index;
												
												_TemplateArgType* pType = new _TemplateArgType();

												pType->m_pClass = tp;//pClass;

												//pType->m_kind = _TemplateArgType::Arg_Type;
												pType->m_ownerScope = pTScope;
												pType->m_index = index;
												pType->m_name = typeparam->m_id;
												
												param->u.m_pType = pType;
												
												if (typeparam->m_typeId)
												{
													pType->m_defaultArg = new TemplatedClassArg;
													pType->m_defaultArg->m_pType = GetType(typeparam->m_typeId->m_declspecList, NULL, pGlobal, pClass->m_pScope, pClass->m_pScope, fun, tp, linkage, false/*TODO*/);
												//	SetReadOnly(pType->m_defaultArg->m_pType);

												}
												else
												{
													Std::get_Out() << d->m_filename << paren(d->m_line_pos+1) << " : warning : " << typeparam->m_id << " typeId == NULL" << "\n";
												//	MessageBeep(-1);
												}
												
												tp->m_items.push_back(param);
												
												pTScope->m_types.insert(typemap::value_type(pType->m_name, pType));
											}
											else
											{
												ASSERT(0);	// TODO, just to get here

												ast::DeclaratorTemplateParameter* declparam = (ast::DeclaratorTemplateParameter*)tp2->head;
												
												Declarator* pDeclarator = new Declarator;
												pDeclarator->m_pType = GetType(declparam->m_decls, NULL, pGlobal, pClass->m_pScope, pClass->m_pScope/*pTScope*//*pScope*/, fun, tp, linkage, bInsideTemplate);//NULL;//d->fundef.declspecList
												Extract(declparam->m_declarator, pDeclarator, pDeclarator->m_pType, pClass->m_pScope, pTScope/*pScope*/, fun, tp, pGlobal, bInsideTemplate);
												
												/*
												__live_object_ptr<_TemplateArgType> pArg;
												pArg = new _TemplateArgType();
												pArg->m_kind = _TemplateArgType::Arg_Value;
												pArg->m_pOwnerScope = pTScope;
												pArg->m_index = indexpArg
												++;->m_name = pDeclarator->m_name;
												pArg->m_pTypeOfValue = pDeclarator->m_pType;
												*/
												
												System::FormalTemplateArg* param = new System::FormalTemplateArg;
												param->m_index = index;
												param->m_kind = System::FormalTemplateArg::Param_Value;
												
												param->u.m_pDeclarator = pDeclarator;
												
												tp->m_items.push_back(param);
												
												pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
											}
											
											index++;
											
											tp2 = tp2->tail;
										}
										
								//	}

									if (td->m_decl->GetKind() == ast::Declaration::A_SIMPLE)
									{
										A_SimpleDeclaration* simpleDeclaration = static_cast<A_SimpleDeclaration*>(td->m_decl);
										SimpleDeclaration(simpleDeclaration, pGlobal, pClass->m_pScope, pTScope, fun, pClass, tp, linkage, bInsideTemplate);
									}
									else if (td->m_decl->GetKind() == ast::Declaration::A_FUNDEF)
									{
										Declarator* declarator = FunDef(static_cast<FunDefDecl*>(td->m_decl), pGlobal, pClass->m_pScope, pTScope, tp, linkage, bInsideTemplate);
										
										declarator->set_Access(accessSpec);
#if 0
										A_FunDef* fundef = ;
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
								else if (d->GetKind() == ast::Declaration::A_FUNDEF)
								{
									FunDefDecl* fundef = static_cast<FunDefDecl*>(d);

									Declarator* declarator = FunDef(fundef, pGlobal, pClass->m_pScope, pClass->m_pScope, NULL, linkage, bInsideTemplate);
									declarator->set_Access(accessSpec);
									ASSERT(accessSpec != AccessSpec_Unspecified);
								}
								else if (d->GetKind() == ast::Declaration::A_SIMPLE)
								{
									CDeclaratorList* declaratorList = SimpleDeclaration(static_cast<A_SimpleDeclaration*>(d), pGlobal, /*pTScope*/pClass->m_pScope, pClass->m_pScope, fun, pClass, NULL/*tp*/, linkage, bInsideTemplate);//, bInsideTemplate);
									
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
									  
										 if (pClass->m_kwType == A_CLASSKEY_UNION)
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

										declaratorList->head->set_Access(accessSpec);
										ASSERT(accessSpec != AccessSpec_Unspecified);
										
										ASSERT(declaratorList->head->m_pOwnerScope == pClass->m_pScope);
										//declaratorList->head->m_pOwnerScope = pClass->m_pScope;
										// ??
										//	ASSERT(declaratorRefList->head->m_pDeclarator->m_name.Length());
										//ASSERT(declaratorList->head->m_pType != NULL);
										//pClass->m_pScope->m_orderedDecls.push_back(declaratorList->head);

										if (declaratorList->head->m_name)
										{
											ASSERT(pClass->m_pScope->m_decls.find(declaratorList->head->m_name) != pClass->m_pScope->m_decls.end());
										}
										//pClass->m_pScope->m_decls.insert(declsmap::value_type(declaratorList->head->m_name, declaratorList->head));
										
										declaratorList = declaratorList->tail;
									}
								}
								else
									ASSERT(0);
							}
						
							member = member->m_next;
						}
					
#if 0
						{
							for (int i = 0; i < methods.size(); i++)
							{
								A_Declaration* d = methods[i];
							
							FunBody(NULL/*TODO*/, d, pGlobal, pClass->m_pScope);
								
							}
						}
#endif
					}
				
/*
					if (pClass->m_pTemplateParams)
					{
						MessageBeep(-1);
					}
					*/
#endif
				}
				break;

			case A_DeclSpec::A_DECLTYPE:
				{
					ast::DeclType* pDecltype = static_cast<ast::DeclType*>(decl);

					if (pDecltype->m_exp->GetKind() == Expression::A_NULLPTR)
					{
						pType = Types::get_nullType();
					}
					else
					{
					// TODO

						ASSERT(0);
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
			simpleType = A_INT;
		}
		/*
		else if (simpleType == A___INT8)
		{
			simpleType = A__INT8;
		}
		else if (simpleType == A___INT64)
		{
			simpleType = A__INT64;
		}
		*/

		switch (simpleType)
		{
		case A_VOID:
		{
			if (sign != 0)
			{
				Std::Out << "error: signed/unsigned cannot be specified on void type";
			}

			if (size != 0)
			{
				Std::Out << "error: short/long cannot be specified on void type";
			}

			pType = System::Types::get_void();
		}
		break;

		case A_CHAR:
		{
			if (size != 0)
			{
				printf("error: short/long cannot be specified on char type");
			}

			if (sign == 1)
				pType = System::Types::get_signed_char();
			else if (sign == 2)
				pType = System::Types::get_unsigned_char();
			else
				pType = System::Types::get_char();
		}
		break;
		
		case A_WCHAR_T:
		{
			if (sign != 0)
			{
				Std::Out << "error: signed/unsigned cannot be specified on wchar_t type";
			}

			if (size != 0)
			{
				Std::Out << "error: short/long cannot be specified on wchar_t type";
			}

			if (pGlobal->m_options->m_type_wchar_t)
			{
				pType = System::Types::get_wchar();
			}
			else
			{
				// VC 6.0
				pType = System::Types::get_unsigned_short();
			}
		}
		break;
		
		case A_BOOL:
		{
			if (sign != 0)
			{
				Std::Out << "error: signed/unsigned cannot be specified on bool type";
			}

			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on bool type");
			}

			pType = System::Types::get_bool();
		}
		break;

		case A_INT:
		{
			if (size == 1)	// short
			{
				if (sign == 2)	// unsigned
					pType = &System::Types::type_unsigned_short;
				else
					pType = &System::Types::type_short;
			}
			else if (size == 2)
			{
				if (sign == 2)	// unsigned
					pType = &System::Types::type_unsigned_long;
				else
					pType = &System::Types::type_long;
			}
			else if (size == 3)
			{
				if (sign == 2)	// unsigned
					pType = &System::Types::type_unsigned_long_long;
				else
					pType = &System::Types::type_long_long;
			}
			else
			{
				if (sign == 2)	// unsigned
					pType = &System::Types::type_unsigned_int;
				else
					pType = &System::Types::type_int;
			}
		}
		break;

		case A___INT8:
		{
			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on __int8 type");
			}

			if (sign == 2)
				pType = &System::Types::type_unsigned_char;
			else
				pType = &System::Types::type_signed_char;
		}
		break;

		case A___INT16:
		{
			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on __int16 type");
			}

			if (sign == 2)
				pType = &System::Types::type_unsigned_short;
			else
				pType = &System::Types::type_short;
		}
		break;

		case A___INT32:
		{
			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on __int32 type");
			}

			if (sign == 2)
				pType = &System::Types::type_unsigned_long;
			else
				pType = &System::Types::type_long;
		}
		break;

		case A___INT64:
		{
			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on __int64 type");
			}

			if (sign == 2)
				pType = &System::Types::type_unsigned_long_long;
			else
				pType = &System::Types::type_long_long;
		}
		break;

		case A_FLOAT:
		{
			if (sign != 0)
			{
				Std::Out << ("error: signed/unsigned cannot be specified on float type");
			}

			if (size != 0)
			{
				Std::Out << ("error: short/long cannot be specified on float type");
			}

			pType = System::Types::get_float();
		}
		break;

		case A_DOUBLE:
		{
			if (sign != 0)
			{
				Std::Out << ("error: signed/unsigned cannot be specified on double type");
			}

			if (size == 1)
			{
				Std::Out << ("error: short cannot be specified on double type");
			}
			else if (size == 3)
			{
				Std::Out << ("error: long long cannot be specified on double type");
			}

			if (size == 2)
				pType = System::Types::get_long_double();
			else
				pType = System::Types::get_double();
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

//	ASSERT(pType);
//	if (pType == NULL)
//		return System::Types::type_void;	// ??

	return pType;
}

CodeCompExt void FunBody(Declarator* pDeclarator, FunDefDecl* d, CGlobal* pGlobal, Scope* pScope, int linkage)
{

//	T_Frame* frame = new T_Frame;
//	T_Declarator* pDeclarator = new T_Declarator;

	T_Declarator* & pBody = labels[pDeclarator];
	if (pBody == NULL)
	{
		pBody = new T_Declarator;
		pBody->m_pDeclarator = pDeclarator;
		tglobals.push_back(pBody);
	}

	pBody->m_first_line = d->m_body->m_first_line;
	pBody->m_last_line = d->m_body->m_last_line;
	pBody->m_linkage = linkage;

	Temp_label* label;// = labels[pDeclarator];
//	if (label == NULL)
		label = new Temp_label;

	label->m_defined = true;
	pBody->m_tempLabel = label;
	pBody->epilogue_label = new Temp_label;

#if 0
	pDeclarator->m_pBody = new T_Declarator;
	pDeclarator->m_pBody->epilogue_label = new Temp_label;
	pDeclarator->m_pBody->line_pos = d->m_line_pos;
#endif
	//FunBody(d->fundef.stmList);

	Scope* pScope2 = new Scope;
	pScope2->m_pParentScope = pScope;

	FunctionType* pFunction = pDeclarator->m_pType->AsFunction();
	ASSERT(pFunction);
	int stackoffset = 8;
	for (uint i = 0; i < pFunction->m_parameters.m_parameters.size(); ++i)
	{
		ASSERT(0);
#if 0
		CDeclarator* pParamDecl = pFunction->m_parameters.m_parameters[i];

		pParamDecl->m_localVar = true;

		if (pParamDecl->m_reg == -1)
		{
			bool& b = pBody->decls[pParamDecl];
			b = true;

			pParamDecl->m_offset = stackoffset;
			pScope2->m_decls.insert(declsmap::value_type(pParamDecl->m_name, pParamDecl));

			stackoffset += 4;
		}
#endif
	}

	A_StmList* slist = d->m_body->m_stmList;

	T_Stm* pStmt = NULL;
//	for (int i = 0; i < pDeclarator->m_pDeclarator->m_pBody->m_statements.size(); i++)
	while (slist)
	{
		T_Stm* p = TransStatement(pBody, slist->head, /*pDeclarator->m_pDeclarator->m_pBody->m_*/pScope2, pGlobal, NULL/*pInnermostSwitch*/, NULL/*break_target*/);
		if (p)
		{
			if (pStmt)
				pStmt = T_Seq(pStmt, p);
			else
				pStmt = p;
		}

		slist = slist->tail;
	}

	if (pStmt)
	{
		quadruples(pStmt);
		printf("*****\n");
		print(pStmt);
	}

	//pBody->m_statementList = pStmt;

	/*
	if (pStmt)
		pStmt = T_Seq(pStmt, T_Label(pBody->epilogue_label));
	else
		pStmt = T_Label(pBody->epilogue_label);
		*/

//		pStmt = TransStatement(pDeclarator->m_pBody->m_statements[1]);

//	statementList = Canonicalize(IR);
	if (pStmt)
		pBody->m_statementList = linearize(pStmt);
	else
		pBody->m_statementList = NULL;

	printf("********\n");

	print(pBody->m_statementList);

	printf("\n");
}

CodeCompExt void Translate(Declaration* d, cpp::CGlobal* pGlobal, Scope* pScope, Declarator* fun, int linkage)
{
	if (d->GetKind() == Declaration::A_FUNDEF)
	{
		FunDefDecl* fundecl = dynamic_cast<FunDefDecl*>(d);
		FunDef(fundecl, pGlobal, pScope, pScope, NULL, linkage, false);
	}
	else if (d->GetKind() == Declaration::A_TEMPLATE)
	{
		bool bInsideTemplate = true;

		TemplateDeclaration* td = dynamic_cast<TemplateDeclaration*>(d);

		TemplateParams* tp = new TemplateParams;

		Scope* pTScope;
		pTScope = new Scope;
		pTScope->m_pParentScope = pScope;//pClass->m_pScope->m_pParentScope;
		
		ast::TemplateParameterList* tp2 = td->m_params;

		int index = 0;
		while (tp2)
		{
			if (tp2->head->GetKind() == ast::TemplateParameter::A_ParamType)
			{
				ast::TypeTemplateParameter* typeparam = dynamic_cast<ast::TypeTemplateParameter*>(tp2->head);
				
				FormalTemplateArg* param = new FormalTemplateArg;
				param->m_kind = FormalTemplateArg::Param_Type;
				param->m_index = index;
				
				_TemplateArgType* pType = new _TemplateArgType();

				pType->m_pClass = tp;

				pType->m_ownerScope = pTScope;
				pType->m_pScope->m_pParentScope = pTScope;

				pType->m_index = index;
				pType->m_name = typeparam->m_id;
				
				param->u.m_pType = pType;
				
				if (typeparam->m_typeId)
				{
					pType->m_defaultArg = new ActualTemplateArg;
					pType->m_defaultArg->m_pType = GetType(typeparam->m_typeId->m_declspecList, NULL, pGlobal, pScope, pTScope, fun, tp, linkage, bInsideTemplate);
				//	SetReadOnly(pType->m_defaultArg->m_pType);
				}
				else
				{
					pType->m_defaultArg = new ActualTemplateArg;
					pType->m_defaultArg->m_pType = Types::get_void();//typetypeparam->m_typeId->m_declspecList, NULL, pGlobal, pScope, pTScope, fun, tp, linkage, bInsideTemplate);
				//	SetReadOnly(pType->m_defaultArg->m_pType);
				}
				
				tp->m_items.push_back(param);
				
				pTScope->m_types.insert(typemap::value_type(pType->m_name, pType));
			}
			else
			{
				ast::DeclaratorTemplateParameter* declparam = dynamic_cast<ast::DeclaratorTemplateParameter*>(tp2->head);
				
				Declarator* pDeclarator = new Declarator;
				pDeclarator->m_pType = GetType(declparam->m_decls, NULL, pGlobal, /*pClass->m_*/pScope, /*pClass->m_*/pTScope/*pTScope*//*pScope*/, fun, tp, linkage, bInsideTemplate);//NULL;//d->fundef.declspecList
				Extract(declparam->m_declarator, pDeclarator, pDeclarator->m_pType, /*pClass->m_*/pScope, pTScope/*pScope*/, fun, tp, pGlobal, bInsideTemplate);
				
				System::FormalTemplateArg* formalArg = new System::FormalTemplateArg;
				formalArg->m_index = index;
				formalArg->m_kind = System::FormalTemplateArg::Param_Value;
				
				formalArg->u.m_pDeclarator = pDeclarator;
				
				if (declparam->m_defaultValue)
				{
					if (declparam->m_defaultValue->GetKind() == Expression::A_INT32)
					{
						formalArg->m_defaultArg.int32Val = declparam->m_defaultValue->u.int32Val;

					//	pType->m_defaultArg = new TemplatedClassArg;
					//	pType->m_defaultArg->m_pType = parse_GetType(typeparam->m_typeId->m_declspecList, g_pGlobal, g_pScope, g_pScope2);///*pClass->m_pScope*/, NULL/*tp ?*/, true);

					}
					else
						ASSERT(0);
				}

				tp->m_items.push_back(formalArg);
				
				pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
			}
			
			index++;
			
			tp2 = tp2->tail;
		}

		if (td->m_decl->GetKind() == ast::Declaration::A_SIMPLE)
		{
			A_SimpleDeclaration* simpleDeclaration = static_cast<A_SimpleDeclaration*>(td->m_decl);
			SimpleDeclaration(simpleDeclaration, pGlobal, pScope, pTScope, fun, NULL, tp, linkage, bInsideTemplate);
		}
		else
		{
			// TODO fundef
		}
	}
	else if (d->GetKind() == ast::Declaration::A_SIMPLE)
	{
		SimpleDeclaration(static_cast<A_SimpleDeclaration*>(d), pGlobal, pScope, pScope, fun, NULL, NULL, linkage, false/*??*/);
	}
	else if (d->GetKind() == ast::Declaration::A_EXTERN_LINKAGE)
	{
		Translate(static_cast<LinkageDeclaration*>(d)->m_declarationList, pGlobal, pScope, fun, ((LinkageDeclaration*)d)->m_linkage == "\"C++\"");
	}
	else if (d->GetKind() == ast::Declaration::A_NAMESPACE)
	{
		NamespaceDefinition* ns = static_cast<NamespaceDefinition*>(d);
		String name = ns->m_name;

		namespacemap::iterator it = pScope->m_namespaces.find(name);
		if (it != pScope->m_namespaces.end())
		{
			Namespace* pNamespace = (*it).second;

			Translate(ns->m_declarationList, pGlobal, pNamespace->m_pScope, fun, linkage);
		}
		else
		{
			Namespace* pNamespace = new Namespace;
		//	pNamespace->m_sourcefile = pGlobal->m_sourceFiles[d->m_filename];	// TODO, doesn't really make any sence, namespaces don't have one place of definition
			pNamespace->m_name = name;
		//	pNamespace->m_pScope->m_name = pNamespace->m_name;

			pNamespace->m_ownerScope = pScope;
			pNamespace->m_pScope->m_pParentScope = pScope;
			pScope->m_subScopes.push_back(pNamespace->m_pScope);
			pScope->m_namespaces[pNamespace->m_name] = pNamespace;

			Declarator* pdecl = new Declarator;
			pdecl->m_name = name;
			pdecl->m_pType = pNamespace;
			pScope->m_orderedDecls.push_back(pdecl);

			Translate(ns->m_declarationList, pGlobal, pNamespace->m_pScope, fun, linkage);
		}
	}
	else if (d->GetKind() == ast::Declaration::A_USING_DIRECTIVE)
	{
		UsingDirectiveDeclaration* directive = dynamic_cast<UsingDirectiveDeclaration*>(d);

		Scope* pScope2 = GetNestedScope(pGlobal, NULL, pScope, directive->m_name);
		ASSERT(pScope2);
		ASSERT(pScope2->m_pNamespace);
		ASSERT(pScope2->m_pNamespace->get_Kind() == type_namespace);

		ASSERT(pScope2 != pScope);

		pScope->m_using_directives.push_back((Namespace*)pScope2->m_pNamespace);
	}
	else if (d->GetKind() == ast::Declaration::A_IMPORT)
	{
		ImportDeclaration* importdecl = static_cast<ImportDeclaration*>(d);

		// Check that it's not alreay imported
		wchar_t fullpath[512];
		_wfullpath(fullpath, CStringw(importdecl->m_str).c_str(), 512);

		if (pGlobal->m_typestuff == NULL)
		{
			raise(Exception("pGlobal->m_typestuff == NULL"));
		}

		if (pGlobal->m_typestuff->m_typelibs_fullpath.find(fullpath) != pGlobal->m_typestuff->m_typelibs_fullpath.end())
		{
			Std::Out << importdecl->m_filename << paren(importdecl->m_line_pos+1) << " : warning : typelib " << fullpath << "already imported (ignored)\n";
		}
		else
		{
			IO::FileStream file(importdecl->m_str, IO::FileMode_Open, IO::FileAccess_Read);
			TypeArchive ar(TypeArchive::Mode_Load, &file, importdecl->m_str);

			ar.m_typestuff = pGlobal->m_typestuff;
			ar.m_pGlobalNamespace = pGlobal->m_namespace;
			ar.m_bSortedDecls = true;

			ar.m_typelib = new TypeLib;

			pGlobal->m_typestuff->m_typelibs_fullpath.insert(TypeStuff::typelibs::value_type(fullpath, ar.m_typelib));

			ar.ReadHeader();
			ar.MapObject(ar.m_typelib);
			ar.m_typelib->Load(ar);

			for (auto it = ar.m_typelib->m_typesByName.begin(); it != ar.m_typelib->m_typesByName.end(); ++it)
			{
				NamedType* pType = (*it).second;

				ASSERT(pType->m_typelib == ar.m_typelib);

				map<String,System::NamedType*>::iterator it2 = pGlobal->m_templateInstances.find(pType->m_qname);
				if (it2 != pGlobal->m_templateInstances.end())
				{
					Std::get_Out() << d->m_filename << paren(d->m_line_pos+1) << " : warning : " << ar.m_typelib->m_typeinfo_filename << " : " << pType->m_qname << " already found" << "\n";// << " already found " << it->second->m_sourcefile->ToString() << paren(it->second->m_line);
				//	raise(SystemException(str->str()));
				//	MessageBoxA(NULL, pType->m_qname, "", MB_OK);

					++pGlobal->m_warnings;	// ??
				//	++pGlobal->m_errors;
				}
				else
				{
			//	pGlobal->m_alltypes.push_back(pType);
					pGlobal->m_templateInstances.insert(map<String,System::NamedType*>::value_type(pType->m_qname, pType));
				}
			}

		//	file.Close();
		}
	}
	else if (d->GetKind() == ast::Declaration::A_PRAGMA)
	{
		PragmaDeclaration* pragma = static_cast<PragmaDeclaration*>(d);

		String::const_iterator<char> p = pragma->m_str.begin();
		String::const_iterator<char> end = pragma->m_str.end();
		if (p.FirstN(4) == "pack")
		{
			p += 4;
			while (p != end && isspace(*p)) ++p;
			ASSERT(*p == '(');
			++p;
			while (p != end && isspace(*p)) ++p;

			if (p.FirstN(4) == "push")
			{
				p += 4;
				ASSERT(*p == ',');
				++p;
				int pack = getnumber(&p);

				pGlobal->m_packstack.push(pack);

			}
			else if (p.FirstN(3) == "pop")
			{
				p += 3;
				while (p != end && isspace(*p)) ++p;
				ASSERT(*p == ')');
				++p;
				while (p != end && isspace(*p)) ++p;
				ASSERT(p == end);

				pGlobal->m_packstack.pop();

				ASSERT(pGlobal->m_packstack.cont.size() > 0);

			}
			else
				ASSERT(0);
		}
	}
	else if (d->GetKind() == ast::Declaration::A_STATIC_ASSERT)
	{
		__debugbreak();

		StaticAssertDeclaration* staticAssert = static_cast<StaticAssertDeclaration*>(d);

		SExp* sexp = TransExpression(staticAssert->m_exp, pGlobal, pScope);
		SValExp* sval = dynamic_cast<SValExp*>(sexp);
		if (sval == nullptr)
		{
			++pGlobal->m_errors;
			Console::get_Out() << staticAssert->m_exp->m_filename << "(" << staticAssert->m_exp->m_line_pos << ")" << " : static_assert : " << staticAssert->m_message << endl;
		}
		else
		{
			if (!sval->m_val)
			{
				++pGlobal->m_errors;
				Console::get_Out() << staticAssert->m_filename << "(" << staticAssert->m_line_pos << ")" << " : static_assert : " << staticAssert->m_message << endl;
			}
		}
	}
	else
	{
		ASSERT(0);
	}
}

CodeCompExt void Translate(ast::DeclarationList* declarationList, cpp::CGlobal* pGlobal, Scope* pScope, Declarator* fun, int linkage)
{
	for (ast::DeclarationList* dl = declarationList; dl; dl = dl->tail)
	{
		ast::Declaration* d = dl->head;

		if (d == NULL)
		{
			dl = dl->tail;
			continue;
		}

		Translate(d, pGlobal, pScope, fun, linkage);
	}
#if 0

		if (d->GetKind() == A_Declaration::A_FUNDEF)
		{
			FunDef((A_FunDef*)d, pGlobal, pScope, NULL);
#if 0
			CDeclarator* pDeclarator = new CDeclarator;

			Type* pType = GetType(((A_FunDef*)d)->m_declspec, pGlobal, pScope/*pTScope*//*pScope*/, NULL/*tp*/, false);//NULL;//d->fundef.declspecList
			pDeclarator->m_pType = pType;

			Scope* pScope2 = ((A_FunDef*)d)->m_declarator->Extract(pDeclarator, pType, pScope/*pTScope*//*pScope*/, pGlobal);
			ASSERT(pScope2);

			/*
			ASSERT(pDeclarator->m_name->Length());
			ASSERT(pDeclarator->m_pType != NULL);
			pClass->m_pScope->m_orderedDecls.push_back(pDeclarator);
			*/

			//ASSERT(0);
			FunBody((A_FunDef*)d, pGlobal, pScope2);
#endif

#if 0
			bool bInline = false;
			A_DeclSpec* decllist = d->fundef.declspec;
			while (decllist)
			{
				if (decllist->head->kind == A_DeclSpec::A_DECL_SPEC && decllist->head->keyword == A_INLINE)
				{
					if (bInline)
						printf("warn: inline already specified");

					bInline = true;
				}
				decllist = decllist->tail;
			}

			CDeclarator* pDeclarator = new CDeclarator;
			Type* pType = GetType(d->fundef.declspecList, pGlobal, pScope);
			pDeclarator->m_pType = pType;
			Scope* pScope2 = d->fundef.declarator->Extract(pDeclarator, pType, pScope);
			if (bInline)
				pDeclarator->m_pType->GetType()->GetFunction()->m_funcspec = 5;

			CDeclaratorReference* pDeclaratorRef;

			declsmap::iterator it = pScope->m_decls.find(pDeclarator->m_name);
			if (it == pScope->m_decls.end())
			{
			//	pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclaratorRef));
			}
			else
				pDeclarator = (*it).second->m_pDeclarator;

			pDeclaratorRef = new CDeclaratorReference(pDeclarator);
			pGlobal->m_globals.Add(pDeclaratorRef);

			pDeclaratorRef->m_pDeclarator->m_defined = true;

		//	CDeclaratorReference* pDeclaratorRef = new CDeclaratorReference(pDeclarator);

			FunBody(pDeclarator, d, pGlobal, pScope2);
#endif
		}
		else if (d->GetKind() == A_Declaration::A_TEMPLATE)
		{
			/*
			Scope* pScope2 = T_Scope();
			pScope2->m_pParentScope = pScope;

			A_TemplateParameterList * tp = d->TEMPLATE.params;
			while (tp)
			{
				TemplateArgType * pType = new TemplateArgType();
				pType->m_name = tp->head->id;
				pScope2->m_types.insert(typemap::value_type(pType->m_name, pType));

				tp = tp->tail;
			}
			*/

			A_TemplateDeclaration* td = (A_TemplateDeclaration*)d;
			td->m_params = Reverse(td->m_params);

			if (td->m_decl->GetKind() == A_Declaration::A_SIMPLE)
			{
				SimpleDeclaration((A_SimpleDeclaration*)td->m_decl, pGlobal, pScope, NULL, td->m_params, true);
			}
			else
			{
				// TODO fundef
			}
		}
		else if (d->GetKind() == A_Declaration::A_SIMPLE)
		{
			SimpleDeclaration((A_SimpleDeclaration*)d, pGlobal, pScope, NULL, NULL, false);
		}
		else if (d->GetKind() == A_Declaration::A_EXTERN_LINKAGE)
		{
			Translate(((A_LinkageDeclaration*)d)->m_declarationList, pGlobal, pScope, strcmp(((A_LinkageDeclaration*)d)->m_linkage->c_str(), "\"C++\"")==0);
		}
		else if (d->GetKind() == A_Declaration::A_NAMESPACE)
		{
			StringA* name = ((A_NamespaceDefinition*)d)->m_name;

			namespacemap::iterator it = pScope->m_namespaces.find(name);
			if (it != pScope->m_namespaces.end())
			{
				Namespace* pNamespace = (*it).second;

				Translate(((A_NamespaceDefinition*)d)->m_declarationList, pGlobal, pNamespace->m_pScope, linkage);
			}
			else
			{
				Namespace* pNamespace = new Namespace;
				pNamespace->m_filepath = d->m_filename;	// TODO, doesn't really make any sense, namespaces don't have one place of definition
				pNamespace->m_name = name;
				pNamespace->m_pScope->m_name = pNamespace->m_name;

				pNamespace->m_pScope->m_pParentScope = pScope;
				pScope->m_subScopes.push_back(pNamespace->m_pScope);
				pScope->m_namespaces[pNamespace->m_name] = pNamespace;

				Translate(((A_NamespaceDefinition*)d)->m_declarationList, pGlobal, pNamespace->m_pScope, linkage);
			}
		}
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

		dl = dl->tail;
	}
#endif
}

/*
CodeCompExt void Write(A_Declarator* declarator);
CodeCompExt void Write(ast::Declaration* d);
CodeCompExt void Write(ast::DeclarationList* declarationList);
CodeCompExt void Write(A_StmList* stmList);
CodeCompExt void Write(Expression* exp);
CodeCompExt void Write(ExpressionList* exp);
CodeCompExt void Write(DeclSpecList* declspecList);
CodeCompExt void Write(A_TypeId* typeId);
*/

Expression* A_CastExp(A_TypeId* typeId, Expression* exp)
{
#if 0	// TODO, have this
	ASSERT(typeId);
	ASSERT(exp);
#endif

	CastExpression* p = new CastExpression;
	p->kind = Expression::A_CAST;
	p->m_typeId = typeId;
	p->m_exp = exp;

	return p;
}

NewExp::NewExp(ExpressionList* placement, A_TypeId* typeId, ExpressionList* init)
{
	kind = Expression::A_NEW;
	m_new_placement = placement;
	m_typeId = typeId;
	m_args = init;
}

#if 0
Expression* A_CallExp(const YYLTYPE& pos, Expression* f, ExpressionList* args)
{
#if 0	// TODO, have this
	ASSERT(f);
#endif

	Expression* p = new Expression;
	p->kind = Expression::A_CALL;
	p->m_line_pos = pos.first_line;

	p->call.left = f;
	p->call.args = Reverse(args);

	return p;
}
#endif

CodeCompExt Expression* A_TemplateId(System::StringA* id, A_TemplateArgumentList* params)
{
	Expression* p = new Expression;
	p->kind = Expression::A_TEMPLATEID;

	p->templateid.id = id;
	p->templateid.params = Reverse(params);

	return p;
}

Expression* A_BinopExp(const YYLTYPE& pos, int op, Expression* left, Expression* right)
{
	// TODO, have this
#if 0
	ASSERT(left != NULL);
	ASSERT(right != NULL);
#endif

	Expression* p = new Expression(pos);
	p->kind = Expression::A_BINOP;

	p->binop.op = op;
	p->binop.left = left;
	p->binop.right = right;

	return p;
}

Expression* A_UnopExp(const YYLTYPE& pos, int op, Expression* exp)
{
#if 0	// TODO, have this
	ASSERT(exp != NULL);
#endif

	Expression* p = new Expression;
	p->kind = Expression::A_UNOP;
	p->m_line_pos = pos.first_line;
	p->unop.op = op;
	p->unop.exp = exp;

	return p;
}

CodeCompExt Expression* A_PostopExp(const YYLTYPE& pos, Expression* exp, int op)
{
	Expression* p = new Expression(pos);
	p->kind = Expression::A_POSTOP;
	p->unop.op = op;
	p->unop.exp = exp;

	return p;
}

CodeCompExt Expression* A_OperatorExp(const YYLTYPE& pos, int op)
{
	Expression* p = new Expression(pos);
	p->kind = Expression::A_OPERATOR;
	p->u._operator = op;

	return p;
}

IfStm::IfStm(Expression2List* cond, A_Stm* stm, A_Stm* elseStm)
{
	m_cond = cond;
	m_stm = stm;
	m_elseStm = elseStm;
}

IfStm::IfStm(Condition* cond, A_Stm* stm, A_Stm* elseStm)
{
	ASSERT(cond);
	ASSERT(stm);

	m_cond = cond;
	m_stm = stm;
	m_elseStm = elseStm;
}

SwitchStm::SwitchStm(Expression2List* cond, A_Stm* stm)
{
	m_cond = cond;
	m_stm = stm;
}

SwitchStm::SwitchStm(Condition* cond, A_Stm* stm)
{
	ASSERT(cond);
	ASSERT(stm);

	m_cond = cond;
	m_stm = stm;
}

WhileStm::WhileStm(const YYLTYPE& first_pos, const YYLTYPE& last_pos, Condition* cond, A_Stm* stm)
{
	ASSERT(cond);
//	ASSERT(cond->m_decl || cond->m_exp);
	ASSERT(stm);

	m_cond = cond;
	m_stm = stm;

	m_last_line = stm->m_last_line;
}

WhileStm::WhileStm(Expression2List* cond, A_Stm* stm)
{
	ASSERT(cond);
	ASSERT(stm);

	m_cond = cond;
	m_stm = stm;
}

DoWhileStm::DoWhileStm(A_Stm* stm, Expression2List* exp)
{
	ASSERT(stm);
	ASSERT(exp);

	m_stm = stm;
	m_exp = exp;
}

DoWhileStm::DoWhileStm(A_Stm* stm, Expression* exp)
{
	ASSERT(stm);
	ASSERT(exp);

	m_stm = stm;
	m_exp = exp;
}

ReturnStm::ReturnStm()
{
	m_exp = NULL;
}

ReturnStm::ReturnStm(Expression2List* exp)
{
	m_exp = exp;
}

ReturnStm::ReturnStm(Expression* exp)
{
	m_exp = exp;
}

A_DeclarationStm::A_DeclarationStm(ast::Declaration* declaration)
{
//	A_Stm* p = new A_Stm;
//	p->kind = A_Stm::A_DECLARATION;
//	p->declaration = declaration;
//	return p;
	m_declaration = declaration;
}

A_ExpStm::A_ExpStm(Expression* exp)
{
	m_exp = exp;
}

CompoundStm::CompoundStm(const YYLTYPE& first_pos, const YYLTYPE& last_pos, A_StmList* stmList)
{
	m_first_line = first_pos.first_line;
	m_last_line = last_pos.first_line;
	m_stmList = stmList;
}

/*
A_Declarator* A_DirectDeclaratorDeclarator(const YYLTYPE & pos, A_DirectDeclarator* directDeclarator)
{
	//ASSERT(directDeclarator);
	A_Declarator* p = new A_Declarator;
	p->m_filename = pos.filename;
	p->line_pos = pos.first_line;

	p->kind = A_Declarator::A_DIRECT_DECLARATOR;
	p->directDeclarator = directDeclarator;

	return p;
}
*/

A_DirectDeclarator* A_DirectDeclaratorId(const YYLTYPE& pos, Expression* id)
{
	A_DirectDeclarator* p = new A_DirectDeclarator;
	p->kind = A_DirectDeclarator::A_DECLARATOR_ID;
	p->u.declaratorId = id;
	p->line_pos = pos.first_line;

	return p;
}

A_DirectDeclarator* A_DirectDeclaratorParen(A_DirectDeclarator* directDeclarator, ParameterDeclarations* paramDecls, DeclSpecList * decls)
{
	A_DirectDeclarator* p = new A_DirectDeclarator;
	p->kind = A_DirectDeclarator::A_DIRECT_DECLARATOR;
	p->u.directDeclarator.kind = A_DirectDeclarator::_u::_directDeclarator::A_PAREN;
	p->u.directDeclarator.directDeclarator = directDeclarator;
	p->u.directDeclarator.paramDecls = paramDecls;
	p->u.directDeclarator.decls = decls;

	return p;
}

A_DirectDeclarator* A_DirectDeclaratorArray(A_DirectDeclarator* directDeclarator, Expression* exp)
{
	A_DirectDeclarator* p = new A_DirectDeclarator;
	p->kind = A_DirectDeclarator::A_DIRECT_DECLARATOR;
	p->u.directDeclarator.kind = A_DirectDeclarator::_u::_directDeclarator::A_ARRAY;
	p->u.directDeclarator.directDeclarator = directDeclarator;
	p->u.directDeclarator.array = exp;

	return p;
}

A_DirectDeclarator* A_DeclaratorDirectDeclarator(const YYLTYPE& pos, A_Declarator* declarator)
{
	A_DirectDeclarator* p = new A_DirectDeclarator;
	p->kind = A_DirectDeclarator::A_DECLARATOR;
	p->u.declarator = declarator;
	return p;
}

/*
A_Declarator* A_PtrDeclarator(int type, A_Declarator* declarator)
{
//	ASSERT(declarator);

	A_Declarator* p = new A_Declarator;
	p->kind = A_Declarator::A_PTR;
	p->ptr.type = type;
	p->ptr.declarator = declarator;
	return p;
}
*/

LinkageDeclaration::LinkageDeclaration(const YYLTYPE& pos, StringIn linkage, ast::DeclarationList* declarationList) : Declaration(pos)
{
	m_linkage = linkage;
	m_declarationList = Reverse(declarationList);
}

NamespaceDefinition::NamespaceDefinition(const YYLTYPE& pos, StringIn name, ast::DeclarationList* declarationList) : Declaration(pos)
{
	m_name = name;
	m_declarationList = Reverse(declarationList);
}

#if 0
DeclSpecList* merge(A_DeclSpec* a, A_DeclSpec* b)
{
	if (a)
	{
		DeclSpecList* _a = a;

		while (_a->tail)
		{
			_a = _a->tail;
		}

		_a->tail = b;

		return a;
	}
	else
	{
		return b;
	}
}
#endif

TemplateDeclaration::TemplateDeclaration(const YYLTYPE& pos, TemplateParameterList * params, ast::Declaration * decl) : Declaration(pos)
{
	m_params = params;
	m_decl = decl;
}

A_SimpleDeclaration::A_SimpleDeclaration(const YYLTYPE& pos, DeclSpecList* declspec, InitDeclaratorList* declaratorList) : Declaration(pos)
{
	m_declspec = declspec;
	m_declaratorList = declaratorList;
}

FunDefDecl::FunDefDecl(const YYLTYPE& pos, DeclSpecList* declspecList, A_Declarator* declarator, ExpressionList* ctor_initializer, CompoundStm* body) : Declaration(pos)
{
	m_declspec = declspecList;
	m_declarator = declarator;
	m_ctor_initializer = ctor_initializer;
	m_body = body;
}

Declaration* A_Declaration2(ast::Declaration* d1, ast::Declaration* d2)
{
	ASSERT(0);
	return NULL;
#if 0
	A_Declaration* p = new A_Declaration;
	p->kind = A_Declaration::A_DECLARATION2;
	p->declaration2.d1 = d1;
	p->declaration2.d2 = d2;

	return p;
#endif
}

Expression* A_IdExp(System::StringA* id)
{
	Expression* p = new Expression;
	p->kind = Expression::A_ID;
	p->templateid.id = id;
	p->m_line_pos = -1;

	return p;
}

Expression* A_IdExp(YYLTYPE& pos, System::StringA* id)
{
	Expression* p = new Expression;
	p->kind = Expression::A_ID;
	p->templateid.id = id;
	p->m_line_pos = pos.first_line;

	return p;
}

Expression* A_Int32Exp(int32 num)
{
	Expression* p = new Expression;
	p->kind = Expression::A_INT32;
	p->u.int32 = num;

	return p;
}

Expression* A_DoubleExp(double value)
{
	Expression* p = new Expression;
	p->kind = Expression::A_DOUBLE;
	p->u.doubleValue = value;

	return p;
}

Expression* A_BoolExp(bool boolValue)
{
	Expression* p = new Expression;
	p->kind = Expression::A_BOOL;
	p->u.boolValue = boolValue;

	return p;
}

Expression* A_StringExp(StringA* string)
{
	Expression* p = new Expression;
	p->kind = Expression::A_STRING;
	p->templateid.id = string;

	return p;
}

Expression* A_LStringExp(StringA* string)
{
	Expression* p = new Expression;
	p->kind = Expression::A_LSTRING;
	p->templateid.id = string;

	return p;
}

Expression* A_ThisExp()
{
	Expression* p = new Expression;
	p->kind = Expression::A_THIS;

	return p;
}

A_DeclSpecModifier::A_DeclSpecModifier(const YYLTYPE& pos, DeclSpecifierKeyword modifier) : A_DeclSpec(pos)
{
	m_modifier = modifier;
}

A_DeclSpecBasicType::A_DeclSpecBasicType(const YYLTYPE& pos, BasicTypeSpecifier type) : A_DeclSpec(pos)
{
	m_basicType = type;
}

A_NameType::A_NameType(const YYLTYPE& pos, Expression* name) : A_DeclSpec(pos),
	m_name(name)
{
}

A_Enum::A_Enum(const YYLTYPE& pos, String name, DeclSpecList* baseType, EnumDefList* deflist) : A_DeclSpec(pos),
	m_name(name),
	m_baseType(baseType),
	m_deflist(deflist)
{
}

EnumDefinition::EnumDefinition(const YYLTYPE& first_pos, String name, Expression* exp) :
	m_filename(first_pos.filename),
	m_line(first_pos.first_line),
	m_column(first_pos.first_column)
{
	ASSERT(name);
	m_name = name;
	m_exp = exp;
}

A_Class::A_Class(const YYLTYPE& pos, A_ClassHead* head) : A_DeclSpec(pos),
	m_head(head)
{
}

A_ClassDef::A_ClassDef(const YYLTYPE& pos, A_ClassHead* head, A_BaseSpecifierList* baseList, A_MemberSpec* memberSpec) : A_DeclSpec(pos),
	m_head(head),
	m_baseList(baseList),
	m_memberSpec(memberSpec)
{
//	ASSERT(pos.filename);
}

A_MemberDecl::A_MemberDecl(ast::Declaration* declaration, A_MemberSpec* next) : A_MemberSpec(next),
	m_declaration(declaration)
{
}

A_MemberAccessSpec::A_MemberAccessSpec(AccessSpec accessSpec, A_MemberSpec* next)
{
	ASSERT(accessSpec != AccessSpec_Unspecified);

	m_accessSpec = accessSpec;
	m_next = next;
}

String GetOperatorName(uint32 op)
{
	switch (op)
	{
	case 'new':
		return "operator new";

	case 'new[':
		return "operator new[]";

	case 'del':
		return "operator delete";

	case 'del[':
		return "operator delete[]";

	case '+':
		return &operator_plus;

	case '-':
		return &operator_minus;

	case '*':
		return S("operator*");

	case '/':
		return S("operator/");

	case '%':
		return S("operator%");

	case '!':
		return S("operator!");

	case '~':
		return S("operator~");

	case '|':
		return S("operator|");

	case '&':
		return S("operator&");

	case '^':
		return S("operator^");

	case '<<':
		return S("operator<<");

	case '>>':
		return S("operator>>");

	case '++':
		return S("operator++");

	case '--':
		return S("operator--");

	case '->':
		return S("operator->");

	case '=':
		return &operator_assign;

	case '+=':
		return &operator_plus_assign;

	case '-=':
		return &operator_minus_assign;

	case '*=':
		return S("operator*=");

	case '/=':
		return S("operator/=");

	case '%=':
		return S("operator%=");

	case '|=':
		return &operator_or_assign;

	case '&=':
		return &operator_and_assign;

	case '^=':
		return &operator_xor_assign;

	case '<<=':
		return S("operator<<=");

	case '>>=':
		return S("operator>>=");

	case '==':
		return &operator_eq;

	case '!=':
		return &operator_neq;

	case '>':
		return &operator_gt;

	case '<':
		return &operator_lt;

	case '>=':
		return &operator_geq;

	case '<=':
		return &operator_leq;

	case '[]':
		return S("operator[]");

	case '()':
		return S("operator()");

	default:
		ASSERT(0);
		return nullptr;
	}
}

//Type* GetType(A_DeclSpec* declspecList, CGlobal* pGlobal, Scope* pScope);

Scope* Extract(Declarator* pDeclarator, A_DirectDeclarator* directDeclarator, Type* pType, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams* tp, CGlobal* pGlobal, bool bInsideTemplate)
{
	ASSERT(pGlobal);

	if (directDeclarator->kind == A_DirectDeclarator::A_DECLARATOR_ID)
	{
		if (directDeclarator->u.declaratorId == nullptr)	// TODO, remove this
		{
			return NULL;
		}

//		if (directDeclarator->u.declaratorId->kind == Expression::A_ID)
		ASSERT(directDeclarator->u.declaratorId->kind == Expression::A_BINOP);

		if (directDeclarator->u.declaratorId->kind == Expression::A_BINOP/* && directDeclarator->u.declaratorId->binop.left->kind == Expression::A_TEMPLATEID*/)
		{
			if (directDeclarator->u.declaratorId->binop.right)
			{
				Scope* pScope2 = LookupScopeNameRecurse(pScope, directDeclarator->u.declaratorId->binop.left->templateid.id);
				ASSERT(pScope2);

				Expression* exp = directDeclarator->u.declaratorId->binop.right;
				while (exp->binop.right)
				{
					pScope2 = LookupScopeName(pScope2, exp->binop.left->templateid.id);
					ASSERT(pScope2);

					exp = exp->binop.right;
				}

				if (exp->binop.left->kind == Expression::A_TEMPLATEID)
				{
					declsmap::iterator it = pScope2->m_decls.find(exp->binop.left->templateid.id);
				//	ASSERT(it != pScope2->m_decls.end());

					pDeclarator->m_name = exp->binop.left->templateid.id;
				}
				else if (exp->binop.left->kind == Expression::A_UNOP)
				{
					VERIFY(exp->binop.left->unop.exp->kind == Expression::A_TEMPLATEID);

					pDeclarator->m_name = "~" + String(exp->binop.left->unop.exp->templateid.id);

				//	pDeclarator->m_name = buffer.DetachToString();//*new StringA("~") + *directDeclarator->u.declaratorId->unop.exp->templateid.id;
				}
				else if (exp->binop.left->kind == Expression::A_CONVERSION)
				{
					ConversionExp* convexp = dynamic_cast<ConversionExp*>(exp->binop.left);

					pDeclarator->m_name = S("operator conversion");
					pDeclarator->m_pType->AsFunction()->m_pReturnType = GetType(convexp->m_typeId->m_declspecList, nullptr/*convexp->m_typeId->declarator*/, pGlobal, pScope, pTScope, fun, tp, 1, bInsideTemplate);
				}
				else if (exp->binop.left->kind == Expression::A_OPERATOR)
				{
					pDeclarator->m_name = GetOperatorName(exp->binop.left->u._operator);
				}
				else
					ASSERT(0);

				return pScope2;
			}
			else
			{
				Expression* exp = directDeclarator->u.declaratorId;

				if (exp->binop.left->kind == Expression::A_TEMPLATEID)
				{
					pDeclarator->m_name = exp->binop.left->templateid.id;
				}
				else if (exp->binop.left->kind == Expression::A_UNOP)
				{
					VERIFY(exp->binop.left->unop.exp->kind == Expression::A_TEMPLATEID);

					pDeclarator->m_name = "~" + String(exp->binop.left->unop.exp->templateid.id);
				}
				else if (exp->binop.left->kind == Expression::A_CONVERSION)
				{
					ConversionExp* convexp = dynamic_cast<ConversionExp*>(exp->binop.left);

					pDeclarator->m_name = S("operator conversion");
					pDeclarator->m_pType->AsFunction()->m_pReturnType = GetType(convexp->m_typeId->m_declspecList, NULL/*convexp->m_typeId->declarator*/, pGlobal, pScope, pTScope, fun, tp, 1, bInsideTemplate);
				}
				else if (exp->binop.left->kind == Expression::A_OPERATOR)
				{
					pDeclarator->m_name = GetOperatorName(exp->binop.left->u._operator);
				}
				else
					ASSERT(0);

				return pScope;
			}
#if 0
			pDeclarator->m_location.m_line = directDeclarator->line_pos;
#endif
		}
#if 0
		else if (directDeclarator->u.declaratorId->kind == Expression::A_UNOP)
		{
			VERIFY(directDeclarator->u.declaratorId->unop.exp->kind == Expression::A_ID);

			BufferImp<char> buffer;
			StringBuilderA strbuilder(&buffer);
			strbuilder << "~" << *directDeclarator->u.declaratorId->unop.exp->templateid.id;

			pDeclarator->m_name = buffer.DetachToString();//*new StringA("~") + *directDeclarator->u.declaratorId->unop.exp->templateid.id;
			return pScope;
		}
		else if (directDeclarator->u.declaratorId->kind == Expression::A_OPERATOR)
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
		else if (directDeclarator->u.declaratorId->kind == Expression::A_CONVERSION)
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
		else if (directDeclarator->u.declaratorId->kind == Expression::A_BINOP)
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
	else if (directDeclarator->kind == A_DirectDeclarator::A_DIRECT_DECLARATOR)
	{
		if (directDeclarator->u.directDeclarator.kind == A_DirectDeclarator::_u::_directDeclarator::A_PAREN)
		{
			FunctionType* pType = new FunctionType;

			pType->m_funcspec = pGlobal->m_options->m_callingConvention;

			pType->m_pReturnType = pDeclarator->m_pType;

			DeclSpecList* decls = directDeclarator->u.directDeclarator.decls;
			while (decls)
			{
				if (decls->head->GetKind() == A_DeclSpec::A_TYPE_MODIFIER)
				{
					if (((A_DeclSpecModifier*)decls->head)->m_modifier == A_CONST)
					{
						if (pType->m_bConst)
						{
							Std::get_Out() << decls->head->m_filename << "(" << decls->head->m_line_pos << "," << decls->head->m_column << ")" << " : error : const already specified\n";
						}
						pType->m_bConst = true;
					}
				}

				decls = decls->tail;
			}

			ParameterDeclarations* paramDecls = directDeclarator->u.directDeclarator.paramDecls;
			ASSERT(paramDecls);

		//	paramDecls->params = Reverse(paramDecls->params);

			pType->m_stackSize = 0;

			pDeclarator->m_pType = pType;
			Scope* pFunScope = Extract(pDeclarator, directDeclarator->u.directDeclarator.directDeclarator, pType, pScope, pTScope, fun, tp, pGlobal, bInsideTemplate);
			if (pTScope != pScope)
				pTScope->m_pParentScope = pFunScope;
			else
				pTScope = pFunScope;

			A_TypeIdList* params = paramDecls->params;
			while (params)
			{
			//	ASSERT(0);
#if 1
				Declarator* pDeclarator = new Declarator;
				pDeclarator->m_pType = GetType(params->head->m_declspecList, NULL, pGlobal, pFunScope, pTScope, fun, tp, 0, bInsideTemplate);//, pTScope);//NULL/*tp*/, bInsideTemplate);

				// TODO
				pDeclarator->m_access;

				/*
				if (pDeclarator->m_pType == NULL)
				{
					ASSERT(0);
					return NULL;
				}*/

				Extract(params->head->m_declarator, pDeclarator, pDeclarator->m_pType, pScope, pTScope, fun, tp, pGlobal, bInsideTemplate);
				//pType->m_parameters.m_parameters.InsertAt(0/*pType->m_parameters.begin()*/, pDeclarator);

				DeclSpecList* decllist = params->head->m_declspecList;
				while (decllist)
				{
					if (decllist->head->GetKind() == A_DeclSpec::A_TYPE_DECLSPECEXT)
					{
						A_DeclSpecExtModifier* mod = (A_DeclSpecExtModifier*)decllist->head;
						
						A_DeclSpecExtList* extlist = mod->m_extlist;
						while (extlist)
						{
							A_DeclSpecExt* ext = extlist->head;

							ASSERT(0);
#if 0
							if (*ext->m_id == "d0") pDeclarator->m_reg = 0;
							else if (*ext->m_id == "d1") pDeclarator->m_reg = 1;
							else if (*ext->m_id == "d2") pDeclarator->m_reg = 2;
							else if (*ext->m_id == "d3") pDeclarator->m_reg = 3;
							else if (*ext->m_id == "d4") pDeclarator->m_reg = 4;
							else if (*ext->m_id == "d5") pDeclarator->m_reg = 5;
							else if (*ext->m_id == "d6") pDeclarator->m_reg = 6;
							else if (*ext->m_id == "d7") pDeclarator->m_reg = 7;
							else if (*ext->m_id == "a0") pDeclarator->m_reg = 8;
							else if (*ext->m_id == "a1") pDeclarator->m_reg = 9;
							else if (*ext->m_id == "a2") pDeclarator->m_reg = 10;
							else if (*ext->m_id == "a3") pDeclarator->m_reg = 11;
							else if (*ext->m_id == "a4") pDeclarator->m_reg = 12;
							else if (*ext->m_id == "a5") pDeclarator->m_reg = 13;
							else if (*ext->m_id == "a6") pDeclarator->m_reg = 14;
							else if (*ext->m_id == "a7") pDeclarator->m_reg = 15;
#endif
							extlist = extlist->tail;
						}
					}

					decllist = decllist->tail;
				}

				FunctionParameters::Param param(pDeclarator->m_pType);
				param.m_name = pDeclarator->m_name;

				if (params->head->m_declarator)
				{
					param.m_filepath = params->head->m_declarator->m_filename;
					param.m_line = params->head->m_declarator->m_line_pos;
				}

				pType->m_parameters.m_parameters.push_back(param);

				pType->m_stackSize += 4;

#endif
				params = params->tail;
			}

			pType->m_parameters.m_bVarArg = paramDecls->varArgs;

			return pFunScope;
		}
		else if (directDeclarator->u.directDeclarator.kind == A_DirectDeclarator::_u::_directDeclarator::A_ARRAY)	// array
		{
			int nSize;

			if (directDeclarator->u.directDeclarator.array)
			{
				SExp* exp = TransExpression(directDeclarator->u.directDeclarator.array, pGlobal, pScope);
				if (exp == NULL)
				{
					exp = TransExpression(directDeclarator->u.directDeclarator.array, pGlobal, pScope);

					Std::get_Out() << endl << directDeclarator->u.directDeclarator.array->m_filename << paren(directDeclarator->u.directDeclarator.array->m_line_pos+1) << " : error : INTERNAL ERROR exp = NULL" << endl;
					++pGlobal->m_errors;
					raise(Exception("error"));
				}

				if (!Type::IsInteger(exp->m_pType))
				{
					Std::get_Out() << directDeclarator->u.directDeclarator.array->m_filename << paren(directDeclarator->u.directDeclarator.array->m_line_pos+1) << " : error : array bounds not const int" << endl;
					++pGlobal->m_errors;
				}

				if (exp->GetKind() == SExp::SEXP_INT)
				{
					nSize = dynamic_cast<SValExp*>(exp)->m_val;
				}
				else
				{
					Std::get_Out() << __FILE__ << "(" << __LINE__ << ")" << " INTERNAL warning" << endl;
					nSize = 0;	// TODO
				}

#if 0
				Tr_Exp* exp = TransExpression(NULL/*T_Declarator* frame*/, directDeclarator->u.directDeclarator.array, pGlobal, pScope);
				ASSERT(exp);
				nSize = Evaluate(exp->ex);
#endif
			}
			else
			{
				nSize = 0;//-1;	// empty array at end of struct means 0 size.. hm..
			}

			ArrayType* parray = newArrayType(pGlobal, pDeclarator->m_pType, nSize);

			// TODO
			pDeclarator->m_pType = parray;

			if (directDeclarator->u.directDeclarator.directDeclarator)
			{
				Scope* pScopeRet = Extract(pDeclarator, directDeclarator->u.directDeclarator.directDeclarator, parray, pScope, pTScope, fun, tp, pGlobal, bInsideTemplate);
				return pScopeRet;
			}
			else
			{
				return pScope;	// ??
			}
		}
		else
			ASSERT(0);
	}
	else if (directDeclarator->kind == A_DirectDeclarator::A_DECLARATOR)
	{
		return Extract(directDeclarator->u.declarator, pDeclarator, pType, pScope, pTScope, fun, tp, pGlobal, bInsideTemplate);
	}
	else
	{
		ASSERT(0);
	}

	return NULL;
}

Scope* Extract(A_Declarator* a_declarator, Declarator* pDeclarator, Type* pType, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams* tp, CGlobal* pGlobal, bool bInsideTemplate)
{
	ASSERT(pGlobal);

	if (a_declarator == NULL)
		return pScope;

	if (typeid(*a_declarator) == typeid(A_BitfieldDeclarator))//kind == A_Declarator::A_DIRECT_DECLARATOR)
	{
		A_BitfieldDeclarator* d = (A_BitfieldDeclarator*)a_declarator;

		pDeclarator->m_name = d->m_id->binop.left->templateid.id;
		ASSERT(d->m_exp->GetKind() == Expression::A_INT32);
		int length = d->m_exp->u.int32;
		ASSERT(length >= 1 && length <= 32);
		pDeclarator->m_bitlength = length;

		return pScope;
	}
	else if (typeid(*a_declarator) == typeid(A_DirectDeclaratorDeclarator))//kind == A_Declarator::A_DIRECT_DECLARATOR)
	{
		return Extract(pDeclarator, ((A_DirectDeclaratorDeclarator*)a_declarator)->m_directDeclarator, pType, pScope, pTScope, fun, tp, pGlobal, bInsideTemplate);
	}
	else if (typeid(*a_declarator) == typeid(A_PtrDeclarator))//kind == A_PTR)
	{
		A_PtrDeclarator* ptrdeclarator = (A_PtrDeclarator*)a_declarator;

		if (ptrdeclarator->m_type == '*')
		{
			pDeclarator->m_pType = CreatePointerType(pGlobal, pDeclarator->m_pType);
		}
		else if (ptrdeclarator->m_type == '&')
		{
			pDeclarator->m_pType = CreateReferenceType(pGlobal, pDeclarator->m_pType);
		}
		else if (ptrdeclarator->m_type == '&&')
		{
			pDeclarator->m_pType = CreateRValueReferenceType(pGlobal, pDeclarator->m_pType);
		}
		else if (ptrdeclarator->m_type == '.*')
		{
			Scope* pScope3 = GetNestedScope(pGlobal, nullptr/*pGlobalScope*/, pScope, ptrdeclarator->m_id);
			// TODO, if pScope3 == NULL
			ASSERT(pScope3);
			ASSERT(pScope3->m_pNamespace);

			PointerMemberType* p = new PointerMemberType(pDeclarator->m_pType, pScope3->m_pNamespace);
			p->m_sizeof = 8;

			pDeclarator->m_pType = p;

		//	MessageBeep(-1);
		//	pDeclarator->m_pType = new PointerMFType(pDeclarator->m_pType);
		}
		else if (ptrdeclarator->m_type == 'c')	// cdecl
		{
			;//MessageBeep(-1);
		}
		else if (ptrdeclarator->m_type == 's')	// stdcall
		{
			;//MessageBeep(-1);
		}
		else if (ptrdeclarator->m_type == 'f')	// fastcall
		{
			;//MessageBeep(-1);
		}
		else
			ASSERT(0);

		Scope* pScope2 = Extract(ptrdeclarator->m_declarator, pDeclarator, pDeclarator->m_pType, pScope, pTScope, fun, tp, pGlobal, bInsideTemplate);

		if (pDeclarator->m_pType->get_Kind() == type_function)
		{
			if (ptrdeclarator->m_type == '.*')
			{
				// hm...

				ASSERT(0);

				Scope* pScope3 = GetNestedScope(pGlobal, nullptr/*pGlobalScope*/, pScope, ptrdeclarator->m_id);
			// TODO, if pScope3 == NULL
				ASSERT(pScope3);
				ASSERT(pScope3->m_pNamespace->AsClass());

				PointerMemberType* p = new PointerMemberType(pDeclarator->m_pType, pScope3->m_pNamespace->AsClass());
				p->m_sizeof = 16;
				pDeclarator->m_pType = p;
			}
			else if (ptrdeclarator->m_type == 'c')	// cdecl
			{
				pDeclarator->m_pType->AsFunction()->m_funcspec = CallType_cdecl;
			}
			else if (ptrdeclarator->m_type == 's')	// stdcall
			{
				pDeclarator->m_pType->AsFunction()->m_funcspec = CallType_stdcall;
			}
			else if (ptrdeclarator->m_type == 'f')	// fastcall
			{
				pDeclarator->m_pType->AsFunction()->m_funcspec = CallType_fastcall;
			}
		}
		else if (pDeclarator->m_pType->get_Kind() == type_pointer &&
					pDeclarator->m_pType->GetPointerTo()->get_Kind() == type_function)
		{
			if (ptrdeclarator->m_type == 'c')	// cdecl
			{
				pDeclarator->m_pType->GetPointerTo()->AsFunction()->m_funcspec = CallType_cdecl;
			}
			else if (ptrdeclarator->m_type == 's')	// stdcall
			{
				pDeclarator->m_pType->GetPointerTo()->AsFunction()->m_funcspec = CallType_stdcall;
			}
			else if (ptrdeclarator->m_type == 'f')	// fastcall
			{
				pDeclarator->m_pType->GetPointerTo()->AsFunction()->m_funcspec = CallType_fastcall;
			}
		}
		else
		{
			// Only legal on functions
			if (ptrdeclarator->m_type == 's')	// stdcall
			{
				ASSERT(0);
			}
			else if (ptrdeclarator->m_type == 'c')	// cdecl
			{
				ASSERT(0);
			}
			else if (ptrdeclarator->m_type == 'f')	// fastcall
			{
				ASSERT(0);
			}
		}

#if 0
		if (pDeclarator->m_pType->get_Kind() == type_function)
		{
			Type* pType;
			if (((A_PtrDeclarator*)a_declarator)->m_type == '*')
				pType = CreatePointerType(pGlobal, pDeclarator->m_pType->GetFunction()->m_pReturnType);
			else
				pType = CreateReferenceType(pGlobal, pDeclarator->m_pType->GetFunction()->m_pReturnType);

			pDeclarator->m_pType->GetFunction()->m_pReturnType = pType;
		}
		/*
		else if (pDeclarator->m_pType->get_Kind() == type_array)
		{
			Type* pType;
			if (((A_PtrDeclarator*)a_declarator)->m_type == '*')
				pType = CreatePointerType(pGlobal, ((ArrayType*)pDeclarator->m_pType)->m_pElemType);
			else
				pType = CreateReferenceType(pGlobal, ((ArrayType*)pDeclarator->m_pType)->m_pElemType);

			pDeclarator->m_pType = newArrayType(pGlobal, pType, ((ArrayType*)pDeclarator->m_pType)->get_ElemCount());

			//((ArrayType*)pDeclarator->m_pType)->m_pElemType = pType;
		}
		*/
		else
		{
			if (((A_PtrDeclarator*)a_declarator)->m_type == '*')
			{
				pDeclarator->m_pType = CreatePointerType(pGlobal, pDeclarator->m_pType);
			}
			else if (((A_PtrDeclarator*)a_declarator)->m_type == '&')
			{
				pDeclarator->m_pType = CreateReferenceType(pGlobal, pDeclarator->m_pType);
			}
			else if (((A_PtrDeclarator*)a_declarator)->m_type == 0)	// cc_qualifier
			{
			}
			else
				ASSERT(0);
		}
#endif

		return pScope2;
	}
	else
		ASSERT(0);

	return NULL;
}

UsingDirectiveDeclaration::UsingDirectiveDeclaration(const YYLTYPE& pos, Expression* name) : Declaration(pos)
{
	m_name = name;
}

CaseStm::CaseStm(Expression2List* exp, A_Stm* stm)
{
	m_exp = exp;
	m_stm = stm;
}

CaseStm::CaseStm(Expression* exp, A_Stm* stm)
{
	m_exp = exp;
	m_stm = stm;
}

DefaultStm::DefaultStm(A_Stm* stm)
{
	m_stm = stm;
}

/*
CodeCompExt int MemAlloc<Expression>::m_count = 0;
CodeCompExt Expression* MemAlloc<Expression>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<ExpressionList>::m_count = 0;
CodeCompExt ExpressionList* MemAlloc<ExpressionList>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_Stm>::m_count = 0;
CodeCompExt A_Stm* MemAlloc<A_Stm>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_StmList>::m_count = 0;
CodeCompExt A_StmList* MemAlloc<A_StmList>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_MemberSpec>::m_count = 0;
CodeCompExt A_MemberSpec* MemAlloc<A_MemberSpec>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_DeclSpec>::m_count = 0;
CodeCompExt A_DeclSpec* MemAlloc<A_DeclSpec>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_Declaration>::m_count = 0;
CodeCompExt A_Declaration* MemAlloc<A_Declaration>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_Declarator>::m_count = 0;
CodeCompExt A_Declarator* MemAlloc<A_Declarator>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_DirectDeclarator>::m_count = 0;
CodeCompExt A_DirectDeclarator* MemAlloc<A_DirectDeclarator>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_TypeIdList>::m_count = 0;
CodeCompExt A_TypeIdList* MemAlloc<A_TypeIdList>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_ParameterDeclarations>::m_count = 0;
CodeCompExt A_ParameterDeclarations* MemAlloc<A_ParameterDeclarations>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_DeclaratorList>::m_count = 0;
CodeCompExt A_DeclaratorList* MemAlloc<A_DeclaratorList>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<DeclSpecList>::m_count = 0;
CodeCompExt DeclSpecList* MemAlloc<DeclSpecList>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_TypeId>::m_count = 0;
CodeCompExt A_TypeId* MemAlloc<A_TypeId>::m_curbuffer = NULL;

CodeCompExt int MemAlloc<A_DeclarationList>::m_count = 0;
CodeCompExt A_DeclarationList* MemAlloc<A_DeclarationList>::m_curbuffer = NULL;
*/

}	// ast
}	// cpp
}	// System
