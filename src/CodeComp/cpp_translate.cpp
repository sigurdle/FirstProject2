#include "stdafx.h"
#include "Comp2.h"
#include "cpp_translate.h"
#include "cpp_ast.h"
#include "cpp_compile.h"
#include "ir.h"

namespace System
{
using namespace std;

namespace m68kasm
{
	CodeCompExt void /*ast::A_Class* */ Parse(StringIn str);

}

extern Temp_temp* eax;
extern Temp_temp* ecx;
extern Temp_temp* edx;
extern Temp_temp* ebx;
extern Temp_temp* esp;
extern Temp_temp* ebp;

extern Temp_temp* d0;
extern Temp_temp* d1;
extern Temp_temp* d2;
extern Temp_temp* d3;
extern Temp_temp* d4;
extern Temp_temp* d5;
extern Temp_temp* d6;
extern Temp_temp* d7;
extern Temp_temp* a0;
extern Temp_temp* a1;
extern Temp_temp* a2;
extern Temp_temp* a3;
extern Temp_temp* a4;
extern Temp_temp* a5;
extern Temp_temp* a6;
extern Temp_temp* a7;

extern Temp_temp* regs[16];

namespace cpp
{

	Type* LookupTypeName(Scope* pScope, StringA* name);

//	Type* GetType(ast::A_DeclSpec* declspecList, CGlobal* pGlobal, Scope* pScope);
//Type* GetType(ast::A_DeclSpec* declspecList, CGlobal* pGlobal, Scope* pScope);

namespace ast
{
Type* GetType(ast::DeclSpecList* declspecList, ast::InitDeclaratorList* declaratorList, CGlobal* pGlobal, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams * tp, int linkage, bool bInsideTemplate);
//Scope* Extract(CDeclarator* pDeclarator, ast::A_DirectDeclarator* directDeclarator, Type* pType, Scope* pScope, CGlobal* pGlobal);
Scope* Extract(ast::A_Declarator* a_Declarator, Declarator* pDeclarator, Type* pType, Scope* pScope, Scope* pTScope, Declarator* fun, TemplateParams * tp, CGlobal* pGlobal, bool bInsideTemplate);
CDeclaratorList* SimpleDeclaration(ast::A_SimpleDeclaration* d, CGlobal* pGlobal, Scope* pScope, Scope* pTScope, Declarator* fun, ClassType* pInnermostClass, TemplateParams* tp, int linkage, bool bInsideTemplate);
}

void CalcClass(CGlobal* pGlobal, ClassType* pClass, unsigned int alignment);

//CDeclaratorList* SimpleDeclaration(ast::A_SimpleDeclaration* d, CGlobal* pGlobal, Scope* pScope, ClassType* pInnermostClass, Scope* pTScope);//ast::A_TemplateParameterList * tp, bool bInsideTemplate);

Tr_Exp* ConvertExpressionType(Tr_Exp* pExpr, Type* p2Type, bool b2Const = false);

map<Declarator*, T_Declarator*> labels;

extern vector<T_Declarator*> tglobals;

void not_cjump(T_Stm* stm)
{
	ASSERT(stm->kind == T_Stm::T_CJUMP);
	stm->cjump.relop = not_relop(stm->cjump.relop);

	Temp_label* t = stm->cjump.t;
	stm->cjump.t = stm->cjump.f;
	stm->cjump.f = t;
}

/*
class MemberRegs
{
public:
	map<CDeclarator*, Temp_temp**> temp;
};

map<CDeclarator*,MemberRegs*> memberregs;
*/

class t_exp_less
{
public:
	bool operator () (const T_Exp * x, const T_Exp * y) const
	{
		if (x->kind != y->kind) return x->kind < y->kind;

		switch (x->kind)
		{
		case T_Exp::T_MEM:
			{
				return (*this)(x->mem.mem, y->mem.mem);
			}
			break;

		case T_Exp::T_BINOP:
			{
				if (x->binop.op != y->binop.op) return x->binop.op < y->binop.op;
				if ((*this)(x->binop.left, y->binop.left)) return true;
				if ((*this)(x->binop.right, y->binop.right)) return true;
				return false;
			}
			break;

		case T_Exp::T_CONST:
			{
				return x->const_int.int32Val < y->const_int.int32Val;
			}
			break;

		case T_Exp::T_TEMP:
			{
				return x->temp < y->temp;
			}
			break;

		default:
			ASSERT(0);
			return false;
		}
	}
};

map<T_Exp*, Temp_temp**, t_exp_less > membertemp;

Tr_Exp* DeclaratorExpression(T_Declarator* frame, Declarator* pDeclarator)
{
	if (true)	// global
	{
		Tr_Exp* pT;

		pT = Tr_Ex(T_Mem(T_ConstExp(pDeclarator->m_offset), pDeclarator->m_pType->get_sizeof()));
		pT->m_pType = pDeclarator->m_pType;
		pT->ex->m_size = pDeclarator->m_pType->get_sizeof();

		return pT;
	}
	else if (true)	// on stack
	{
		Tr_Exp* pT;

		pT = Tr_Ex(T_Mem(
						T_BinopExp('+',
							T_Temp(&ebp),
						//	T_Temp(&a5),
							T_ConstExp(pDeclarator->m_offset)), pDeclarator->m_pType->get_sizeof()));

		pT->m_pType = pDeclarator->m_pType;
		pT->ex->m_size = pDeclarator->m_pType->get_sizeof();

		return pT;
	}

#if 1
//	te();

	Tr_Exp* pT;

//	ASSERT(0);
//#if 0
	if (pDeclarator->m_pOwnerScope && pDeclarator->m_pOwnerScope->m_pNamespace->AsClass())
	{
		CalcClass(NULL, pDeclarator->m_pOwnerScope->m_pNamespace->AsClass(), 2/*TODO*/);

		pT = Tr_Ex(T_Mem(
					T_BinopExp('+',
						T_Mem(
							T_BinopExp('+', T_Temp(&a5), T_ConstExp(8)), 4),
						T_ConstExp(pDeclarator->m_offset)), pDeclarator->m_pType->get_sizeof()));

		pT->ex->m_size = pDeclarator->m_pType->get_sizeof();
	}
	else if (pDeclarator->m_localVar)//pDeclarator->m_symbolIndex == 0)	// local variable
	{
#if 1
			bool& b = frame->decls[pDeclarator];

		if (!b && pDeclarator->m_pType->get_Kind() == type_long_long)	// TODO, unambiguous, address is not taken etc., don't make this decision here, but earlier
		{
			ASSERT(0);
#if 0
			Temp_temp*& temp = frame->temps[pDeclarator];
			T_Exp*& texp = frame->decls2[pDeclarator];

			if (temp == NULL)
			{
				temp = new Temp_temp*;
				temp->m_second = new Temp_temp;

				temp->m_size = 4;
				temp->m_second->m_size = 4;

				temp->name = strdup(pDeclarator->m_name->c_str());
				temp->m_second->name = (char*)malloc(pDeclarator->m_name->Length()+8);
				strcpy(temp->m_second->name, pDeclarator->m_name->c_str());
				strcat(temp->m_second->name, "_h");

				texp = T_Temp(temp);
				texp->m_size = 8;

				temp->m_exp = texp;
			}

			pT = Tr_Ex(texp);
#endif
		}
		/*
		else if (!b && pDeclarator->m_pType->GetKind() == type_class)	// TODO more
		{
		}
		*/
		else if (!b && pDeclarator->m_pType->get_sizeof() <= 4)
		{
			/*
			T_Exp* texp = T_Temp(strdup(pDeclarator->m_name->c_str()));
			texp->m_size = pDeclarator->m_pType->get_sizeof();;
			pT = Tr_Ex(texp);
			*/

#if 1
			Temp_temp*& temp = frame->temps[pDeclarator];
		//	T_Exp*& texp = frame->decls2[pDeclarator];

			if (temp == NULL)
			{
				temp = new Temp_temp;

				Temp_temp** tempref = &temp;

				(*tempref)->m_size = pDeclarator->m_pType->get_sizeof();

				ASSERT(0);
				//(*tempref)->name = _strdup(pDeclarator->m_name);

			//	texp = T_Temp(tempref);
			//	texp->m_size = pDeclarator->m_pType->get_sizeof();
			//	(*tempref)->m_exp = texp;
			}

			T_Exp* texp = T_Temp(&temp);
			texp->m_size = pDeclarator->m_pType->get_sizeof();;
			pT = Tr_Ex(texp);
#endif
		}
		else
#endif
		{
			if (b == false)
			{
				if (pDeclarator->m_pType->get_Kind() == type_class)
				{
					// TODO, maybe not here ?
					CalcClass(NULL, pDeclarator->m_pType->AsClass(), 2/*TODO*/);
				}

				int _sizeof = pDeclarator->m_pType->get_sizeof();


			//	if (pDeclarator->m_offset == -1)
				{
					frame->m_stackSize += _sizeof;
					pDeclarator->m_offset = -frame->m_stackSize;
				}
				b = true;
			}

		//	Temp_temp* fp = new Temp_temp("ebp");
		//	fp->name = "ebp";
		//	fp->m_n = 5;	// EBP

			pT = Tr_Ex(T_Mem(
						T_BinopExp('+',
						//	T_Temp(ebp),
							T_Temp(&a5),
							T_ConstExp(pDeclarator->m_offset)), pDeclarator->m_pType->get_sizeof()));

			pT->ex->m_size = pDeclarator->m_pType->get_sizeof();

#if 0
			pT = Tr_Ex(T_Mem(
						T_BinopExp('+',
							T_Temp(fp),
							T_Const(- _sizeof - 0/*pDeclarator->m_spOffset*/)), _sizeof));
#endif
		}
	}
	else
	{
		T_Declarator* & label = labels[pDeclarator];
		if (label == NULL)
		{
			label = new T_Declarator;
			label->m_pDeclarator = pDeclarator;
			label->m_tempLabel = new Temp_label;

			tglobals.push_back(label);
		}

		pT = Tr_Ex(T_Mem(T_Name(label->m_tempLabel), pDeclarator->m_pType->get_sizeof()));
		pT->ex->m_size = pDeclarator->m_pType->get_sizeof();
#if 0
#if 0
		FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
		ImageReloc->VirtualAddress = 0;//ftell(fileout);	// Address into the .text section
		ImageReloc->SymbolTableIndex = pDeclarator->m_symbolIndex;
	//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
		ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
#endif

		if (pDeclarator->m_tempLabel == NULL)	// ????
			pDeclarator->m_tempLabel = new Temp_label;

		ASSERT(pDeclarator->m_tempLabel);

		pT =	Tr_Ex(T_Mem(T_Name(pDeclarator->m_tempLabel), pDeclarator->m_pType->get_sizeof()));
	//	ASSERT(0);
#if 0
		T_Exp* pConst = T_Const(0/*pDeclarator->m_spOffset*/);
		//pConst->const_int.reloc = ImageReloc;
		pConst->const_int.reloc = new RelocConst;
		pConst->const_int.reloc->pDeclarator = pDeclarator;
		pConst->const_int.reloc->Type = IMAGE_REL_I386_DIR32;
		pT =	Tr_Ex(T_Mem(pConst, pDeclarator->m_pType->get_sizeof()));
#endif
#endif
	}

	pT->m_pType = pDeclarator->m_pType;

	if (pDeclarator->m_pType->get_Kind() == type_reference)
	{
		pT = Tr_Ex(T_Mem(pT->ex, 4));
		pT->m_pType = pDeclarator->m_pType->GetPointerTo();
	}

	return pT;
#endif
	return NULL;
}

/*
T_Exp* Reduce(T_Exp* e)
{
	
}
*/

#if 0
Tr_Exp* CCompileFile::TransExpression(T_Declarator* frame, CExpression* pExpr, CGlobal* pGlobal, Scope* pScope)
{
	ASSERT(pScope);

//	Scope* pScope = pExpr->m_pScope;

	ASSERT(pExpr->tok.type != CToken::tok_empty);

//#if 0
	pExpr = Reduce2(pExpr, pScope);
//#endif

	ASSERT(pExpr->tok.type != CToken::tok_empty);

	if (pExpr->tok.type == CToken::tok_integer)
	{
		if ((unsigned __int64)pExpr->tok.int32 > 0xFFFFFFFF)
		{
			Tr_Exp* pTExpr = Tr_Ex(T_Const(pExpr->tok.int32));
			pTExpr->m_pType = new cpp::Type(type_int, 4);
			return pTExpr;
		}
		else
		{
			Tr_Exp* pTExpr = Tr_Ex(T_Const(pExpr->tok.int32));
			pTExpr->m_pType = new cpp::Type(type_int, 4);
			return pTExpr;
		}
	}
#if 0
	else if (pExpr->tok.type == CToken::tok_double)
	{
		pExpr->m_pType = new Type(type_double, 8);
	}
#endif
	else if (pExpr->tok.type == CToken::tok_string)
	{
		T_Exp* pConst = T_Const(0);
#if 0
		FRelocation* ImageReloc = new FRelocation;
		ImageReloc->VirtualAddress = 0;
		ImageReloc->SymbolTableIndex = 0;
	//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
		ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;

		ASSERT(0);
#endif
#if 0
		ImageReloc->pExpr = pExpr;
#endif

		Tr_Exp* pTExpr = Tr_Ex(pConst);

		pTExpr->m_pType = new Type(type_pointer, sizeof_pointer);
		pTExpr->m_pType->m_pPointerTo = new Type(type_char, 1);
		pTExpr->m_pType->m_pPointerTo->m_bConst = true;

		CDeclarator* pDeclarator = new CDeclarator;
		pDeclarator->m_pType = pTExpr->m_pType;
		pDeclarator->m_string.data = strdup(pExpr->tok.string);
		pDeclarator->m_string.len = pExpr->tok.stringlen;

		ASSERT(0);
#if 0
		pConst->const_int.reloc = new RelocConst;
		pConst->const_int.reloc->Type = IMAGE_REL_I386_REL32;
		pConst->const_int.reloc->pDeclarator = pDeclarator;
#endif

		//pGlobal->m_strings.push_back(pTExpr->ex);
		pGlobal->m_strings.push_back(pDeclarator);

		return pTExpr;
	}
#if 0
	else if (pExpr->tok.type == CToken::tok_wstring)
	{
		pExpr->m_pType = new Type(type_pointer, sizeof_pointer);
		pExpr->m_pType->m_pPointerTo = new Type(type_wchar, 2);
		pExpr->m_pType->m_pPointerTo->m_bConst = true;

		pGlobal->m_strings.push_back(pExpr);
	}
#endif
	else if (pExpr->tok.type == CToken::tok_ident)
	{
		pExpr->m_pDeclaratorRef = pScope->GetDeclarator(pExpr->tok.ident);
		if (pExpr->m_pDeclaratorRef == NULL)
		{
			char msg[1024];
			sprintf(msg, "'%s' : undeclared identifier", pExpr->tok.ident);
			jerror(msg, pExpr->m_location);
		}
		else
		{
			if (!pExpr->m_pDeclaratorRef->m_pDeclarator->m_referenced)
			{
				pExpr->m_pDeclaratorRef->m_pDeclarator->m_referenced = true;
				pGlobal->m_references.push_back(pExpr->m_pDeclaratorRef);
			}

			return DeclaratorExpression(frame, pExpr->m_pDeclaratorRef->m_pDeclarator);
		}
	}
#if 0
	else if (pExpr->tok.type == CToken::tok_keyword &&
			(pExpr->tok.pkw->n == KW_TRUE || pExpr->tok.pkw->n == KW_FALSE))
	{
		pExpr->m_pType = new Type(type_bool, 1);
	}
#endif
	else if (pExpr->tok.type == CToken::tok_keyword && pExpr->tok.pkw->n == KW_THIS)
	{
		Scope* p = pScope;
		while (p)
		{
			if (p->m_pClass)
			{
				Temp_temp* a5 = new Temp_temp;
				a5->m_an = 8+5;

				Tr_Exp* pT;
				pT	=	Tr_Ex(T_Mem(
							T_Binop('+',
								T_Temp(a5),
								T_Const(8/*-pDeclarator->m_pType->get_sizeof() - pDeclarator->m_spOffset*/)), 4/*pDeclarator->m_pType->get_sizeof()*/));
				pT->m_pType = new Type(type_pointer, sizeof_pointer);
				pT->m_pType->m_pPointerTo = new Type(type_class);
				pT->m_pType->m_pPointerTo->m_pClass = p->m_pClass;

				//pT->m_pType = p->m_pClass->m_pType;

				return pT;
			}

			p = p->m_pParentScope;
		}
		jerror("Use of 'this' in a non-member function is not allowed", pExpr->m_location);
	}
#if 0
	else if (pExpr->tok.type == CToken::tok_keyword && pExpr->tok.pkw->n == KW_NEW)
	{
		ASSERT(pExpr->m_pType != NULL);
	}
	else if (pExpr->tok.type == CToken::tok_keyword && pExpr->tok.pkw->n == KW_DELETE)
	{
		pExpr->right = Reduce(pExpr->right, pScope);
	}
	else if (pExpr->tok.type == CToken::tok_symbol && pExpr->tok.symbol == ',')
	{
		pExpr->left = Reduce(pExpr->left, pScope);
		pExpr->right = Reduce(pExpr->right, pScope);

	// The type and value of the result are the type and value of the right operand
		pExpr->m_pType = pExpr->right->m_pType;
	}
#endif
	else if (pExpr->tok.type == CToken::tok_symbol)
	{
		switch (pExpr->tok.symbol)
		{
#if 0
		case '::':
			{
				CExpression* pMemberExpr = pExpr->right;
				
				Scope* pScope2 = GetNestedScope(pScope, pExpr->left);
				if (pScope2)
				{
					declsmap::iterator decli;
					
					if (pMemberExpr->tok.type == CToken::tok_ident)
					{
						decli = pScope2->m_decls.find(pMemberExpr->tok.ident);
					}
					else if (pMemberExpr->tok.type == CToken::tok_keyword)
					{
						if (pMemberExpr->tok.pkw->n == KW_NEW)
							decli = pScope2->m_decls.find("operator_new");
						else if (pMemberExpr->tok.pkw->n == KW_DELETE)
							decli = pScope2->m_decls.find("operator_delete");
						else
							ASSERT(0);
					}
					else
						ASSERT(0);
					
					if (decli != pScope2->m_decls.end())
					{
						pExpr->m_pDeclaratorRef = (*decli).second;
						pExpr->m_pType = pExpr->m_pDeclaratorRef->m_pDeclarator->m_pType;
					}
					else
					{
						char msg[512];
						if (pMemberExpr->tok.type == CToken::tok_ident)
							sprintf(msg, "'%s' : undeclared identifier", pMemberExpr->tok.ident);
						else if (pMemberExpr->tok.type == CToken::tok_keyword)
							sprintf(msg, "'%s' : undeclared identifier", pMemberExpr->tok.pkw->name);
						else
							sprintf(msg, "undeclared identifier");
						
						pPP->jerror(msg);
					}
				}
				else
				{
					char msg[512];
					sprintf(msg, "'%s' : undeclared identifier", pMemberExpr->tok.ident);
					pPP->jerror(msg);
				}
			}
			break;
#endif

		case 'szof':
			{
				Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
				if (right == NULL)
					return NULL;
				
				return Tr_Ex(T_Const(right->m_pType->get_sizeof()));
			}
			break;
			
		case '(':	// function call
			{
				if (pExpr->left == NULL)
				{
					jerror("left expression = NULL in function call ?", pExpr->m_location);
				}
				else
				{
				/*
				if (pExpr->left->tok.symbol == '::' && pExpr->left->left == NULL)
				{
				printf("");
				}
					*/
					Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
					
					if (left == NULL)
					{
						jerror("left expression = NULL in function call", pExpr->m_location);
					}
					else
					{
						//if (pExpr->
						
						if (left->m_pType)
						{
							Type* pType = left->m_pType->GetType();
							
							if (pType->GetKind() == type_pointer)
							{
								pType = pType->m_pPointerTo->GetType();
								/*
								if (pType->m_pPointerTo->GetKind() == type_function)
								{
								pType = pType->m_pPointerTo;
								}
								*/
							}
							
							if (pType->GetKind() == type_function)//m_pFunction)
							{
								Tr_Exp* tr = NULL;
								
								//						pExpr->m_pDeclarator = pDeclarator;
								
								T_Exp* pCall;
								
								int narg = 0;
								
								if (pType->m_pFunction->m_thiscall)
								{
									//	CExpression* pThis = new CExpression(pScope);
									//	pThis->
									
									Tr_Exp* leftob = TransExpression(frame, pExpr->left->left, pGlobal, pScope);
									Type* pType = new Type(type_pointer, sizeof_pointer);
									pType->m_pPointerTo = leftob->m_pType;
									leftob->m_pType = pType;
									
									tr = Tr_Ex(pCall = T_Call(unEx(left)));
									pCall->call.args = new ExpList(unEx(leftob)->mem, NULL);
									//	pCall->call.args->expr = pExpr->left;
									narg = 1;
								}
								else if (pType->m_pFunction->m_libcall.m_offset != 0)	// libcall
								{
									pExpr->m_pBaseDeclarator = pScope->GetDeclarator(pType->m_pFunction->m_libcall.m_basename.c_str());
									if (pExpr->m_pBaseDeclarator == NULL)
									{
										char msg[512];
										sprintf(msg, "undeclared libcall base '%s'", pType->m_pFunction->m_libcall.m_basename.c_str());
										jerror(msg, pExpr->m_location);
									}
									Temp_temp* temp = new Temp_temp;
									temp->m_an = 8+6;
									tr = Tr_Ex(
										T_ESeq(
										T_Move(T_Temp(temp), unEx(DeclaratorExpression(frame, pExpr->m_pBaseDeclarator->m_pDeclarator))),
										pCall = T_Call(T_Binop('+', T_Temp(temp), T_Const(pType->m_pFunction->m_libcall.m_offset)))
										)
										);
									
									//	pExpr->m_baseOffset = pDeclarator->m_libcall.m_offset;
								}
								else
								{
									//	pExpr->m_pDeclarator = pDeclarator;
									tr = Tr_Ex(pCall = T_Call(unEx(left)));
								}
								
								tr->m_pType = pType->m_pFunction->m_pReturnType;
								//int i = pExpr->m_pDeclarator->m_pFunction->m_parameters.size()-1;
								
								std::vector<CExpression*> args;
								{
									CExpression* pArgExpr = pExpr->right;
									while (pArgExpr)
									{
										ASSERT(pArgExpr->left != NULL);
										
										args.insert(args.begin(), pArgExpr);//->left);
										pArgExpr = pArgExpr->right;
									}
								}
								
								for (; narg < args.size(); narg++)
								{
									CDeclarator* pArgDecl;
									
									if (narg >= pType->m_pFunction->m_parameters.size())
									{
										if (!pType->m_pFunction->m_bVarArg)
										{
											jerror("too many arguments", pExpr->m_location);
											break;
										}
										pArgDecl = NULL;
									}
									else
									{
										pArgDecl = pType->m_pFunction->m_parameters[narg];
									}
									
									CExpression* pArgExpr = args[narg];
									
									Tr_Exp* p;
									
#if 0
									if (pType->m_pFunction->m_libcall.m_offset != 0 &&
										pType->m_pFunction->m_libcall.m_tagcall &&
										narg == pType->m_pFunction->m_parameters.size()-1)
									{
										Temp_temp* a7 = new Temp_temp;
										
										//continue;
										/*
										a7->m_an = 8+7;
										//	p = T_Unop('&', 
										
										  Temp_temp* tt = new Temp_temp;
										  tt->m_an = pArgDecl->m_libcall.m_reg-8;
										  
											 p = Tr_Ex(T_ESeq(T_Move(T_Temp(tt), T_Temp(a7)), T_Const(0)));
										*/
									}
									else
#endif
									{
										p = TransExpression(frame, pArgExpr->left, pGlobal, pScope);
									}
									
									if (p == NULL)
									{
										jerror("function argument failed", pExpr->m_location);
										return NULL;
									}
									
									if (p->m_pType)
									{
										if (pArgDecl)
										{
											pArgExpr->m_pDeclaratorRef = new CDeclaratorReference(pArgDecl);
											
											p = ConvertExpressionType(p, pArgDecl->m_pType);
											
											if (!p->m_pType->IsEqual(pArgDecl->m_pType))
											{
												StringA str0 = p->m_pType->toString();
												StringA str1 = pArgDecl->m_pType->toString();
												
												char msg[1024];
												sprintf(msg, "parameter %d: incompatible types - from '%s' to '%s'",
													//fstr.c_str(),//pExpr->left->tok.ident,
													narg+1,//pDeclarator->m_pFunction->m_parameters.size()-i,
													str0.c_str(), str1.c_str());
												jerror(msg, pExpr->m_location);
											}
										}
									}
									
									//pCall->call.args->expr = pArgExpr;
									
									if (pType->m_pFunction->m_libcall.m_offset != 0 &&
										pType->m_pFunction->m_libcall.m_tagcall &&
										narg == pType->m_pFunction->m_parameters.size()-1)
									{
										pCall->call.args = new ExpList(NULL, pCall->call.args);
										pCall->call.args->reg = - (pArgDecl->m_libcall.m_reg+1);
										
										pCall->call.args = new ExpList(unEx(p), pCall->call.args);
										
										//continue;
										/*
										a7->m_an = 8+7;
										//	p = T_Unop('&', 
										
										  Temp_temp* tt = new Temp_temp;
										  tt->m_an = pArgDecl->m_libcall.m_reg-8;
										  
											 p = Tr_Ex(T_ESeq(T_Move(T_Temp(tt), T_Temp(a7)), T_Const(0)));
										*/
									}
									else
									{
										pCall->call.args = new ExpList(unEx(p), pCall->call.args);
										
										if (pArgDecl)
											pCall->call.args->reg = pArgDecl->m_libcall.m_reg;
									}
						}
						
						if (narg < pType->m_pFunction->m_parameters.size())
						{
							char msg[256];
							if (pExpr->left->tok.type == CToken::tok_ident)
								sprintf(msg, "'%s' : too few parameters", pExpr->left->tok.ident);
							else
								sprintf(msg, "too few parameters");
							
							jerror(msg, pExpr->m_location);
						}
						
						return tr;
					}
					else
					{
						char msg[512];
						
						if (pExpr->left->tok.type == CToken::tok_ident)
							sprintf(msg, "'%s' : not a function", pExpr->left->tok.ident);
						else
							sprintf(msg, "not a function");
						
						jerror(msg, pExpr->m_location);
						
						return NULL;
					}
				}
				else
				{
					char msg[512];
					
					/*
					if (pExpr->left->tok.type == CToken::tok_ident)
					{
					sprintf(msg, "undeclared identifier '%s'", pExpr->left->tok.ident);
					}
					else if (pExpr->left->tok.type == CToken::tok_keyword)
					{
					sprintf(msg, "undeclared identifier '%s'", pExpr->left->tok.pkw->name);
					}
					else
					*/
					{
						sprintf(msg, "left side had no type");
					}
					
					jerror(msg, pExpr->m_location);
				}
			}
		}
	}
	break;
	
	case '->':	// Convert it to (*left).right
		{
#if 0
			pExpr->left = Reduce(pExpr->left, pScope);
			//	pExpr->right = Reduce(pExpr->right, pScope);
			
			//ExpressionType(pExpr->left, pScope);
			
			// First check for operator overloading
			
			if (pExpr->left->m_pType)
			{
				Type* pType = pExpr->left->m_pType->GetType();
				if (pType->GetKind() == type_templateinst)
				{
					printf("");
					pType = InstantiateTemplateType(pType->m_ArgTypes, pType);
					pExpr->left->m_pType = pType;
				}
				
				if (pType->GetKind() == type_class)
				{
					StringA fname = "operator_>-";
					
					CDeclaratorReference* pDeclaratorRef = pType->m_pClass->GetDeclarator(fname.c_str());
					if (pDeclaratorRef)
					{
						// An expression x->m is interpreted as (x.operator->())->m
						
						CExpression* pExpr2 = new CExpression(pScope);
						pExpr2->tok.type = CToken::tok_symbol;
						pExpr2->tok.symbol = '->';
						
						pExpr2->right = new CExpression(pScope);
						pExpr2->right->tok = pExpr->right->tok;
						
						pExpr2->left = new CExpression(pScope);
						pExpr2->left->tok.type = CToken::tok_symbol;
						pExpr2->left->tok.symbol = '(';
						
						pExpr2->left->left = new CExpression(pScope);
						pExpr2->left->left->tok.type = CToken::tok_symbol;
						pExpr2->left->left->tok.symbol = '.';
						
						pExpr2->left->left->left = new CExpression(pScope);
						pExpr2->left->left->left->tok = pExpr->left->tok;
						
						pExpr2->left->left->right = new CExpression(pScope);
						pExpr2->left->left->right->tok.type = CToken::tok_ident;
						pExpr2->left->left->right->tok.ident = "operator_>-";
						//	pExpr2->left->left->m_pDeclarator = pDeclarator;	// TODO
						
						//	pExpr->m_pDeclarator = pDeclarator;
						//	pExpr->m_pType = pDeclarator->m_pType;
						//return pExpr->m_pType;
						
						//Reduce(pExpr
						
						pExpr2 = Reduce(pExpr2, pScope);
						
						delete pExpr;
						pExpr = pExpr2;
						
						return pExpr;
					}
				}
			}
			else
			{
				printf("");
				pExpr->left = Reduce(pExpr->left, pScope);
			}
#endif
			
			CExpression* pExpr2 = ast::A_Binop('.',
				ast::A_Unop('*', pExpr->left),
				pExpr->right);
			
				/*
				CExpression* pDerefExpr = ast::A_Unop(((DWORD)'*'|('U'<<8)), pExpr->left);
				
				  new CExpression;
				  pDerefExpr->tok.type = CToken::tok_symbol;
				  pDerefExpr->tok.symbol = ((DWORD)'*'|('U'<<8));
				  pDerefExpr->right = pExpr->left;
				  
					 pExpr->left = pDerefExpr;
					 pExpr->tok.symbol = '.';
					 
			*/
			
			//	return pExpr;
			return TransExpression(frame, pExpr2, pGlobal, pScope);
		}
		break;
		
	case '.':
		{
			// object.member
			// node->left = object
			// node->right = member
			
			Tr_Exp* tleft = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (tleft == NULL)
				return NULL;
			
			if (tleft->m_pType)
			{
				if (tleft->m_pType->GetType()->GetKind() == type_templateinst)
				{
					ASSERT(0);
#if 0
					printf("");
					pExpr->left->m_pType = InstantiateTemplateType(pExpr->left->m_pType->GetType()->m_ArgTypes, pExpr->left->m_pType->GetType());
#endif
				}
			}
			
			Class* pClass = NULL;
			if (tleft->m_pType == NULL || (pClass = tleft->m_pType->GetClass()) == NULL)
			{
				if (tleft->m_pType)
				{
					StringA strtype = tleft->m_pType->toString();
					StringA strtypeun = tleft->m_pType->GetType()->toString();
					char msg[1024];
					sprintf(msg, "left of '.%s' must have class/struct/union type instead of: %s (%s)", pExpr->right->tok.ident, strtype.c_str(), strtypeun.c_str());
					jerror(msg, pExpr->m_location);
				}
				else
				{
					char msg[1024];
					sprintf(msg, "left of '.%s' must have class/struct/union type", pExpr->right->tok.ident);
					jerror(msg, pExpr->m_location);
				}
			}
			else
			{
				if (pExpr->right && pExpr->right->tok.type != CToken::tok_ident)
				{
					jerror("Expected member name", pExpr->m_location);
				}
				else if (pClass->m_sizeof == -1)
				{
					char msg[1024];
					sprintf(msg, "use of incomplete struct '%s'", pClass->m_name.c_str());
					jerror(msg, pExpr->m_location);
				}
				else
				{
					if (pExpr->right->m_pDeclaratorRef == NULL)
						pExpr->right->m_pDeclaratorRef = pClass->GetDeclarator(pExpr->right->tok.ident);
					
					if (pExpr->right->m_pDeclaratorRef == NULL)
					{
						ASSERT(tleft->m_pType->GetType()->GetKind() == type_class);
						
						char msg[1024];
						sprintf(msg, "'%s' : is not a member of '%s'",
							pExpr->right->tok.ident,
							tleft->m_pType->GetType()->m_pNamedType->m_name.c_str());
						
						jerror(msg, pExpr->m_location);
					}
					else
					{
						if (pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pOwnerScope->m_pClass != pClass)
						{
							ASSERT(0);
#if 0
							// Cast left expression
							CExpression* pExpr2 = new CExpression(pScope);
							pExpr2->tok.type = CToken::tok_symbol;
							pExpr2->tok.symbol = (DWORD)'('|('U'<<8);
							pExpr2->m_pType = new Type(type_class);
							//pExpr2->m_pType->m_pPointerTo = new Type(type_class);
							pExpr2->m_pType->m_pClass = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pOwnerScope->m_pClass;
							
							pExpr2->right = pExpr->left;
							
							pExpr2 = Reduce(pExpr2, pScope);	// hm.. right gets reduced twice
							
							pExpr->left = pExpr2;
							
							pExpr->m_pDeclaratorRef = pExpr->right->m_pDeclaratorRef;
							pExpr->m_pType = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pType->Clone();
							
							//	pExpr2->right = pExpr;
							
							
							//	pExpr2->right = pExpr;
							//	pExpr = pExpr2;
#endif
						}
						else
						{
							T_Exp* left = unEx(tleft);
							
							ASSERT(left->kind == T_Exp::T_MEM);
							left = left->mem;
							
							CDeclarator* pRightDeclarator = pExpr->right->m_pDeclaratorRef->m_pDeclarator;
							
							if (pRightDeclarator->m_pType->GetType()->GetKind() == type_function)
							{
								CDeclarator* pDeclarator = pRightDeclarator;
								
								ASSERT(0);
#if 0
								FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
								ImageReloc->VirtualAddress = 0;//ftell(fileout);	// Address into the .text section
								ImageReloc->SymbolTableIndex = pDeclarator->m_symbolIndex;
								//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
								ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
#endif
		
								ASSERT(0);
								T_Exp* pConst = T_Const(0/*pDeclarator->m_spOffset*/);
#if 0
								pConst->const_int.reloc = ImageReloc;
#endif
								Tr_Exp* pT = Tr_Ex(T_Mem(pConst, pDeclarator->m_pType->get_sizeof()));
								
								pT->m_pType = pDeclarator->m_pType;
								
								return pT;//MessageBeep(-1);
								//return Tr_Exp(T_
							}
							
							Tr_Exp* tr;
							
#if 0
							if (left->kind == T_Exp::T_BINOP &&
								left->binop.right->kind == T_Exp::T_CONST)
							{
								ASSERT(left->binop.op == '+');
								
								left->binop.right->const_int.int32Val += pRightDeclarator->m_spOffset;
								tr = Tr_Ex(T_Mem(left, pRightDeclarator->m_pType->GetType()->get_sizeof()));
							}
							else
#endif
							{
								ASSERT(0);
#if 0
								tr = Tr_Ex(
									T_Mem(
									T_Binop('+', left, T_Const(pRightDeclarator->m_spOffset)), pRightDeclarator->m_pType->GetType()->get_sizeof()));
#endif
							}
							
							//	Tr_Exp* tr = Tr_Ex(
							//		T_Binop('+', unEx(left), T_Const(pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_spOffset)));
							
							/*
							if (tr->ex->mem->binop.left->kind == T_Exp::T_MEM)
							{
							tr->ex->mem->binop.right->const_int.int32Val += tr->ex->mem->binop.left->mem->const_int.int32Val;
							tr->ex->mem->binop.left = tr->ex->mem->binop.left->mem;
							//if (tr->ex->mem->binop.left
							//	tr->ex->mem->binop.right->const_int.int32Val += tr->
							}
							*/
							/*
							if (tr->ex->kind == T_Exp::T_MEM &&
							tr->ex->mem->kind == T_Exp::T_BINOP &&
							tr->ex->mem->binop.op == '+' &&
							tr->ex->mem->binop.right->kind == T_Exp::T_CONST)
							{
							if (tr->ex->mem->binop.left
							//	tr->ex->mem->binop.right->const_int.int32Val += tr->
							}
							*/
							
							pExpr->m_pDeclaratorRef = pExpr->right->m_pDeclaratorRef;
							tr->m_pType = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pType->Clone();
							
							return tr;
						}
				}
			}
		}
	}
	break;
	
	case '.*':
		{
		/*
		The binary operator .* binds its second operand, which shall be of type “pointer to member of T” (where
		T is a completely-defined class type) to its first operand, which shall be of class T or of a class of which T
		is an unambiguous and accessible base class. The result is an object or a function of the type specified by
		the second operand.
			*/
			//		pExpr->right
			ASSERT(0);
			return NULL;
		}
		break;
		
	case '->*':
		{
			ASSERT(0);
			return NULL;
		}
		break;
		
	case ((DWORD)'*'|('U'<<8)):	// Dereference right node
		{
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			if (right == NULL)
				return NULL;
			
			if (right->m_pType == NULL)
			{
				jerror("no type", pExpr->m_location);
			}
			else
			{
				Type* pType = right->m_pType->GetType();
				
				if (pType->GetKind() == type_pointer)
				{
					ASSERT(pType->m_arrayDims.size() == 0);
					pType = pType->m_pPointerTo;
				}
				else if (pType->GetKind() == type_array)
				{
					ASSERT(pType->m_arrayDims.size() > 0);
					pType = pType->m_pPointerTo;
				}
				else
				{
					jerror("illegal indirection", pExpr->m_location);
					//	return NULL;
				}
				
				Tr_Exp* pTExpr;
				pTExpr = Tr_Ex(T_Mem(unEx(right), pType->get_sizeof()));
				pTExpr->m_pType = pType;
				
				return pTExpr;
			}
		}
		break;
		
	case '[':
		{
			// TODO, check operators
			// ??
			/*
			pExpr->left = Reduce(pExpr->left, pScope);
			pExpr->right = Reduce(pExpr->right, pScope);
			*/
			
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (left == NULL)
			{
				return NULL;
			}
			else
			{
				T_Exp* leftx = unEx(left);
				ASSERT(leftx->kind == T_Exp::T_MEM);
				
				int _sizeof = left->m_pType->m_pPointerTo->get_sizeof();
				
				CExpression* r = ast::A_Binop('*',
					pExpr->right,
					ast::A_Const(_sizeof)
					);
				
				r = Reduce2(r, pScope);
				
				Tr_Exp* right = TransExpression(frame, r, pGlobal, pScope);
				
				Tr_Exp* tr = Tr_Ex(T_Mem(T_Binop('+', leftx->mem, unEx(right)), _sizeof));
				tr->m_pType = left->m_pType->m_pPointerTo;
				return tr;
				/*
				CExpression* pExpr2 = ast::A_Unop('*',
				ast::A_Binop('+',
				pExpr->left,
				ast::A_Binop('*',
				pExpr->right,
				ast::A_Const(_sizeof)
				)
				)
				);
				*/
				
				//	pExpr2 = Reduce2(pExpr2, pScope);
				//	return TransExpression(pExpr2, pGlobal, pScope);
				/*
				Tr_Exp* tr = Tr_Ex(
				T_Mem(
				T_Binop('+',
				leftx->mem,
				T_Binop('*',
				unEx(right),
				T_Const(_sizeof)
				)
				),
				_sizeof
				)
				);
				*/
				//	tr->m_pType = left->m_pType->m_pPointerTo;
				
				//	return tr;
			}
			
#if 0
			CExpression* pExpr2 = new CExpression(pScope);
			pExpr2->tok.type = CToken::tok_symbol;
			pExpr2->tok.symbol = (DWORD)'*'|('U'<<8);
			
			pExpr2->right = new CExpression(pScope);
			pExpr2->right->tok.type = CToken::tok_symbol;
			pExpr2->right->tok.symbol = '+';
			pExpr2->right->left = pExpr->left;
			pExpr2->right->right = pExpr->right;
			
			pExpr = Reduce(pExpr2, pScope);
			
			ASSERT(pExpr->m_pType);
			
			// TODO
			//pExpr->m_pType = pExpr->left->m_pType->m_pPointerTo;
			
			/*
			Type* pType = new Type;
			
			  pExpr->m_pType = new Type;
			  pExpr->m_pType->GetKind() = type_pointer;
			  pExpr->m_pType->m_sizeof = sizeof(char*);
			  
				 pExpr->m_pType->m_pPointerTo = new Type;
				 pExpr->m_pType->m_pPointerTo->GetKind() = type_char;
				 pExpr->m_pType->m_pPointerTo->m_sizeof = 1;
				 pExpr->m_pType->m_pPointerTo->m_bConst = true;
			*/
#endif
		}
		break;
		
	case ((DWORD)'&'|('U'<<8)):	// address-of right node
		{
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			
			if (right->ex->kind == T_Exp::T_MEM)
			{
				Tr_Exp* pTExpr = Tr_Ex(right->ex->mem);
				pTExpr->m_pType = new Type(type_pointer, sizeof_pointer);
				pTExpr->m_pType->m_pPointerTo = right->m_pType;
				pTExpr->m_pType->m_lvalue = false;	// & produces an r-value
				
				return pTExpr;
			}
			else if (right->ex->kind == T_Exp::T_CONST)
			{
				jerror("'&' on constant", pExpr->m_location);
			}
			else
			{
				ASSERT(0);
			}
#if 0
			pExpr->right = Reduce(pExpr->right, pScope);
			if (pExpr->right->m_pType)
			{
				if (!pExpr->right->m_pType->m_lvalue)
				{
					pPP->jerror("'&' requires l-value");
				}
				
				pExpr->m_pType = new Type(type_pointer, sizeof_pointer);
				pExpr->m_pType->m_pPointerTo = pExpr->right->m_pType;
				pExpr->m_pType->m_lvalue = false;	// & produces an r-value
			}
			else
			{
				pPP->jerror("unknown expression type");
			}
			
			//	return pExpr->m_pType;
#endif
		}
		break;
		
#if 0
		else if (pExpr->tok.type == CToken::tok_symbol && (pExpr->tok.symbol == ((DWORD)'!'|('U'<<8))))	// ! (unary)
		{
			//ASSERT(pExpr->m_pType != NULL);
			ASSERT(pExpr->left == NULL);
			
			pExpr->right = Reduce(pExpr->right, pScope);
			
			pExpr->m_pType = pExpr->right->m_pType;	// ????
		}
#endif
	case (DWORD)'('|('U'<<8):	// cast
		{
			ASSERT(pExpr->cast.m_pType != NULL);
			ASSERT(pExpr->left == NULL);
			
			if (pExpr->right)
			{
				Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
				if (right == NULL)
					return NULL;
				
				right->m_pType = pExpr->cast.m_pType;
				
				return right;
#if 0
				Type* pType0 = pExpr->m_pType->GetType();
				Type* pType1 = pExpr->right->m_pType->GetType();
				if (pType0->GetKind() == type_pointer && pType1->GetKind() == type_pointer)
				{
					pType0 = pType0->m_pPointerTo->GetType();
					pType1 = pType1->m_pPointerTo->GetType();
				}
				
				if (pType0->GetKind() == type_class && pType1->GetKind() == type_class)
				{
					int offset = pType1->m_pClass->GetOffset(pType0->m_pClass);
					if (offset != -1)
					{
						CExpression* pExpr2 = new CExpression(pScope);
						pExpr2->tok.type = CToken::tok_symbol;
						pExpr2->tok.symbol = '+';
						
						pExpr2->left = pExpr->right;
						
						pExpr2->right = new CExpression(pScope);
						pExpr2->right->tok.type = CToken::tok_integer;
						pExpr2->right->tok.int32 = offset;
						
						pExpr2->right = Reduce(pExpr2->right, pScope);
						
						pExpr2->m_pType = pExpr->m_pType;
						
						pExpr = pExpr2;
					}
					//	printf("");
					//	Get
				}
#endif		
			}
			else
			{
				jerror("no right expression in cast expression", pExpr->m_location);
			}
		}
		break;
		
	case '+=':
	case '-=':
	case '*=':
	case '/=':
	case '%=':
	case '|=':
	case '&=':
	case '^=':
	case '>>=':
	case '<<=':
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok.type = CToken::tok_symbol;
			pExpr2->tok.symbol = '=';
			
			pExpr2->left = pExpr->left;
			
			pExpr2->right = new CExpression;
			pExpr2->right->tok.type = CToken::tok_symbol;
			
			if (pExpr->tok.symbol == '+=')
			{
				pExpr2->right->tok.symbol = '+';
			}
			else if (pExpr->tok.symbol == '-=')
			{
				pExpr2->right->tok.symbol = '-';
			}
			else if (pExpr->tok.symbol == '*=')
			{
				pExpr2->right->tok.symbol = '*';
			}
			else if (pExpr->tok.symbol == '/=')
			{
				pExpr2->right->tok.symbol = '/';
			}
			else if (pExpr->tok.symbol == '%=')
			{
				pExpr2->right->tok.symbol = '%';
			}
			else if (pExpr->tok.symbol == '<<=')
			{
				pExpr2->right->tok.symbol = '<<';
			}
			else if (pExpr->tok.symbol == '>>=')
			{
				pExpr2->right->tok.symbol = '>>';
			}
			else if (pExpr->tok.symbol == '|=')
			{
				pExpr2->right->tok.symbol = '|';
			}
			else if (pExpr->tok.symbol == '&=')
			{
				pExpr2->right->tok.symbol = '&';
			}
			else
				ASSERT(0);
			
			pExpr2->right->right = pExpr->right;
			pExpr2->right->left = pExpr->left;	// Okay to use exact same copy ??
			
			//pExpr = pExpr2;
			
			return TransExpression(frame, pExpr2, pGlobal, pScope);
		}
		break;
		
	case '=':
		{
#if 0	// ??
			//if (pExpr->right->tok.type == CToken::tok_symbol && pExpr->right->tok.symbol == 
			if (pDeclarator->m_pInitializerExpr != NULL)
			{
				initialize(pDeclarator, pDeclarator->m_pInitializerExpr, pCompoundStmt);
			}
#endif
			
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (left == NULL)
			{
				jerror("error in left side of '=' expression", pExpr->m_location);
			}
			else
			{
				
#if 0
				if (pExpr->left->m_pType)
				{
					if (!pExpr->left->m_pType->m_lvalue)
					{
#if 0	// TODO
						pPP->jerror("'=' requires l-value on left side");
#endif
					}
				}
#endif
				
				if (pExpr->right == NULL)
				{
					jerror("error in right side of '=' expression", pExpr->m_location);
				}
				else
				{
					Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
					if (right == NULL)
					{
						jerror("error in right side of '=' expression", pExpr->m_location);
						
						//	ExpressionType(pExpr->right, pScope);
					}
					else
					{
						right = ConvertExpressionType(right, left->m_pType);
						
						if (!right->m_pType->IsEqual(left->m_pType))
						{
#if 0
							// Try operator= overloads
							Type* pType = pExpr->left->m_pType->GetType();
							
							if (pType->GetKind() == type_class)
							{
								for (int i = 0; i < pType->m_pClass->m_pScope->m_orderedDecls.size(); i++)
								{
									CDeclaratorReference* pDeclaratorRef = pType->m_pClass->m_pScope->m_orderedDecls[i];
									if (pDeclaratorRef->m_pDeclarator->m_name == "operator_=")
									{
										if (pDeclaratorRef->m_pDeclarator->m_pType->GetType()->m_pFunction->m_parameters.size() == 1)
										{
											CDeclarator* pParamDeclarator = pDeclaratorRef->m_pDeclarator->m_pType->GetType()->m_pFunction->m_parameters[0];
											//	std::string str0 = pParamDeclarator->m_pType->toString();
											//	printf("operator=(%s)\n", str0.c_str());
											
											/*
											CExpression* pExprRight = new CExpression(pScope);
											pExprRight->m_pType = pExpr->right->m_pType->Clone();
											pExprRight->tok.type = pExpr->right->tok.type;
											pExprRight->tok.int32 = pExpr->right->tok.int32;
											*/
											
											StringA str0 = pExpr->right->m_pType->toString();
											StringA str1 = pParamDeclarator->m_pType->toString();
											
											pExpr->right = ConvertExpressionType(pExpr->right, pParamDeclarator->m_pType);
											
											if (pExpr->right->m_pType->IsEqual(pParamDeclarator->m_pType))
											{
												std::string str = pExpr->right->m_pType->toString();
												
												CExpression* pExpr2 = new CExpression(pScope);
												pExpr2->tok.type = CToken::tok_symbol;
												pExpr2->tok.symbol = '(';
												
												pExpr2->left = new CExpression(pScope);
												pExpr2->left->tok.type = CToken::tok_symbol;
												pExpr2->left->tok.symbol = '.';
												
												pExpr2->left->left = pExpr->left;
												pExpr2->left->right = new CExpression(pScope);
												pExpr2->left->right->tok.type = CToken::tok_ident;
												pExpr2->left->right->tok.ident = strdup("operator_=");
												pExpr2->left->right->m_pDeclaratorRef = pDeclaratorRef;
												
												// function argument
												
												pExpr2->right = new CExpression(pScope);
												pExpr2->right->left = pExpr->right;
												
												delete pExpr;
												pExpr = pExpr2;
												
												pExpr = Reduce(pExpr, pScope);
												return pExpr;
											}
											/*
											else
											{
											
											  char msg[512];
											  sprintf(msg, "cannot convert %s to %s", str0.c_str(), str1.c_str());
											  pPP->jerror(msg);
											  }
											*/
										}
									}
								}
							}
#endif
						}
						
						if (!right->m_pType->IsEqual(left->m_pType))
						{
							//ConvertExpressionType(pExpr->right, pExpr->left->m_pType);
							
							StringA str0 = right->m_pType->toString();
							StringA str1 = left->m_pType->toString();
							
							//	std::string fstr = pExpr->m_pDeclarator->toString();
							
							char msg[1024];
							sprintf(msg, "incompatible types - from '%s' to '%s'",
								//	fstr.c_str(),//pExpr->left->tok.ident,
								//	i+1,//pDeclarator->m_pFunction->m_parameters.size()-i,
								str0.c_str(), str1.c_str());
							jerror(msg, pExpr->m_location);
							
							/*
							printf("***\n");
							printoutall(pExpr->left->m_pType);
							printf("***\n");
							*/
							return NULL;
						}
						else
						{
							Tr_Exp* p = Tr_Nx(T_Move(left->ex, unEx(right)));
							p->m_pType = left->m_pType;
							return p;
						}
					}
				}
			}
		}
		break;
	
	case '^':
	case '|':
	case '&':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '<<':
	case '>>':
		{
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			
			if (left->m_pType && right->m_pType)
			{
				Tr_Exp* tr = Tr_Ex(T_Binop(pExpr->tok.symbol, unEx(left), unEx(right)));
				
				if ((pExpr->tok.symbol == '-') && (
					left->m_pType->GetType()->GetKind() == type_pointer &&
					right->m_pType->GetType()->GetKind() == type_pointer))
				{
					tr->m_pType = new Type(type_int, 4);
				}
				else if ((pExpr->tok.symbol == '+') && (
					left->m_pType->GetType()->GetKind() == type_pointer &&
					right->m_pType->GetType()->GetKind() == type_int))
				{
					tr->m_pType = left->m_pType;
				}
				else if ((pExpr->tok.symbol == '+') && (
					left->m_pType->GetType()->GetKind() == type_int &&
					right->m_pType->GetType()->GetKind() == type_pointer))
				{
					tr->m_pType = right->m_pType;
				}

				else if ((pExpr->tok.symbol == '&') &&
					left->kind == Tr_ex && left->ex->kind == T_Exp::T_CONST &&
					left->ex->const_int.int32Val == 1)
				{
					tr->m_pType = Types::type_bool;
				}
				else if ((pExpr->tok.symbol == '&') &&
					right->kind == Tr_ex && left->ex->kind == T_Exp::T_CONST &&
					right->ex->const_int.int32Val == 1)
				{
					tr->m_pType = Types::type_bool;
				}

				else
				{
					// TODO, check for compatibility
					tr->m_pType = left->m_pType;
				}
				
				return tr;
			}
			else
			{
				jerror("error in expressions", pExpr->m_location);
			}
		}
		break;
		
	case '==':
	case '!=':
	case '>':
	case '<':
	case '>=':
	case '<=':
		{
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (left == NULL)
				return NULL;
			
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			if (right == NULL)
				return right;
			
			//	Temp_label* z = new Temp_label;
			T_Stm* s1 = /*T_Seq(*/T_CJump(pExpr->tok.symbol, unEx(left), unEx(right), NULL, NULL);/*,
									T_Label(z));*/
			
			Tr_Exp* tr = Tr_Cx(new patchList(&s1->cjump.t, NULL), new patchList(&s1->cjump.f, NULL), s1);
			
			//	ASSERT(s1->cjump.t);
			//	ASSERT(s1->cjump.f);
			
			tr->m_pType = new Type(type_bool);
			
			return tr;
#if 0
			pExpr->left = Reduce(pExpr->left, pScope);
			
			if (pExpr->right)
			{
				pExpr->right = Reduce(pExpr->right, pScope);
				
				if (pExpr->left->m_pType && pExpr->right->m_pType)
				{
					pExpr->m_pType = new Type(type_bool);
				}
				else
				{
					if (pExpr->left->m_pType == NULL)
						pPP->jerror("left side of expr had no type");
					
					if (pExpr->right->m_pType == NULL)
						pPP->jerror("right side of expr had no type");
				}
			}
			else
			{
				pPP->jerror("error in right side of expression");
			}
#endif
		}
		break;
		
#if 0
		else if (pExpr->tok.type == CToken::tok_symbol && pExpr->tok.symbol == '?')
		{
			// TODO pExpr->right->left->m_pType IsCompatible pExpr->right->right->m_pType
			if (pExpr->left == NULL)
			{
				pPP->jerror("left=NULL in ?: expression");
			}
			else
			{
				pExpr->left = Reduce(pExpr->left, pScope);
				pExpr->right->left = Reduce(pExpr->right->left, pScope);
				pExpr->right->right = Reduce(pExpr->right->right, pScope);
				
				// TODO, this is just a quick hack (if one of them is a pointer type, choose that one)
				if (pExpr->right->left->m_pType->GetType()->GetKind() == type_pointer)
				{
					pExpr->m_pType = pExpr->right->left->m_pType;
				}
				else
				{
					pExpr->m_pType = pExpr->right->right->m_pType;
				}
			}
		}
#endif
		
	case 'U-':
	case 'U!':
		{
			ASSERT(pExpr->left == NULL);
			ASSERT(pExpr->right != NULL);

			Tr_Exp* tre = TransExpression(frame, pExpr->right, pGlobal, pScope);
			if (tre == NULL)
				return NULL;

			Tr_Exp* tr = Tr_Ex(T_Unop(pExpr->tok.symbol, unEx(tre)));

			return tr;
		}
		break;
		
		default:
			ASSERT(0);
		}
	}

	return NULL;
	//return pExpr;
}
#endif

Type* GetAbstractType(T_Declarator* frame, CGlobal* pGlobal, Scope* pScope, ast::A_TypeId* typeExp)
{
	Declarator pDeclarator;
	pDeclarator.m_pType = ast::GetType(typeExp->m_declspecList, NULL, pGlobal, pScope, pScope, frame? frame->m_pDeclarator: NULL, NULL, 0, false/*TODO*/);
	ast::Extract(typeExp->m_declarator, &pDeclarator, pDeclarator.m_pType, pScope, pScope, frame? frame->m_pDeclarator: NULL, NULL/*tp*/, pGlobal, false/*TODO*/);
	return pDeclarator.m_pType;
}

Tr_Exp* TransExpression(T_Declarator* frame, ast::Expression* pExpr, CGlobal* pGlobal, Scope* pScope)
{
	ASSERT(pScope);

	switch (pExpr->GetKind())
	{
	case ast::Expression::A_INT32:
	{
	//	ASSERT((ULONGLONG)pExpr->u.int32 > 0xFFFFFFFF)

		/*
		if ((ULONGLONG)pExpr->u.int32 > 0xFFFFFFFF)
		{
			Tr_Exp* pTExpr = Tr_Ex(T_Const64Exp(pExpr->u.int64));
			pTExpr->m_pType = &System::Types::type_long_long;
			return pTExpr;
		}
		else
		*/
		{
			Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(pExpr->u.int32Val));
			pTExpr->m_pType = &System::Types::type_int;
			return pTExpr;
		}
	}
	break;

	case ast::Expression::A_UINT32:
	{
	//	ASSERT((ULONGLONG)pExpr->u.int32 > 0xFFFFFFFF)

		/*
		if ((ULONGLONG)pExpr->u.int32 > 0xFFFFFFFF)
		{
			Tr_Exp* pTExpr = Tr_Ex(T_Const64Exp(pExpr->u.int64));
			pTExpr->m_pType = &System::Types::type_long_long;
			return pTExpr;
		}
		else
		*/
		{
			Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(pExpr->u.int32Val));
			pTExpr->m_pType = &System::Types::type_unsigned_int;
			return pTExpr;
		}
	}
	break;

	case ast::Expression::A_INT64:
	{
		Tr_Exp* pTExpr = Tr_Ex(T_Const64Exp(pExpr->u.int64Val));
		pTExpr->m_pType = &System::Types::type_long_long;
		return pTExpr;
	}
	break;

	case ast::Expression::A_UINT64:
	{
		Tr_Exp* pTExpr = Tr_Ex(T_Const64Exp(pExpr->u.int64Val));
		pTExpr->m_pType = &System::Types::type_unsigned_long_long;
		return pTExpr;
	}
	break;

	case ast::Expression::A_BOOL:
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(pExpr->u.boolValue));
		pTExpr->m_pType = &System::Types::type_bool;
		return pTExpr;
	}
	break;

	case ast::Expression::A_FLOAT:
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstFloatExp(pExpr->u.float32Val));
		pTExpr->m_pType = &System::Types::type_float;
		return pTExpr;
	}
	break;

	case ast::Expression::A_DOUBLE:
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstDoubleExp(pExpr->u.float64Val));
		pTExpr->m_pType = &System::Types::type_double;
		return pTExpr;
	}
	break;

	case ast::Expression::A_CHAR_LITERAL:
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(pExpr->u.int32Val));
		pTExpr->ex->m_size = 1;	// TODO
		pTExpr->m_pType = &System::Types::type_char;
		return pTExpr;
	}
	break;

	case ast::Expression::A_STRING:
	{
		/*
		CDeclarator* pDeclarator = new CDeclarator;
		pDeclarator->m_tempLabel = new Temp_label;
		pDeclarator->m_string.data = strdup(pExpr->string->c_str());
		pDeclarator->m_string.len = strlen(pExpr->string->c_str())+1;
		*/
		//((ModifierType*)pDeclarator->m_pType->GetPointerTo())->m_bConst = true;

		Temp_label* label = new Temp_label;

		T_Data* data = new T_Data;
		data->m_label = label;
		data->m_data = (uint8*)CString(pExpr->templateid.id).Detach();
		data->m_len = pExpr->templateid.id->GetLength()+1;	// null-terminated
		frame->m_data.push_back(data);

		Tr_Exp* pTExpr = Tr_Ex(T_Name(label));
		// TODO: Array
		pTExpr->m_pType = new PointerType(new ModifierType(&Types::type_char, true, false));
		//pTExpr->m_pType = pDeclarator->m_pType;

		//pGlobal->m_strings.Add(pDeclarator);

		return pTExpr;
	}
	break;
#if 0
	else if (pExpr->tok.type == CToken::tok_wstring)
	{
		pExpr->m_pType = new Type(type_pointer);
		pExpr->m_pType->m_pPointerTo = new Type(type_wchar);
		pExpr->m_pType->m_pPointerTo->m_bConst = true;

		pGlobal->m_strings.push_back(pExpr);
	}
#endif
	case ast::Expression::A_ID:
	{
		ASSERT(0);	// Shouldn't happen
#if 0

		CDeclaratorReference* 
		/*pExpr->m_*/pDeclaratorRef = pScope->GetDeclarator(pExpr->id);

		if (/*pExpr->m_*/pDeclaratorRef == NULL)
		{
			char msg[1024];
			sprintf(msg, "error(%d): '%s' : undeclared identifier\n", pExpr->line_pos, pExpr->id);
		//	printf(msg);
			printf(msg);
		}
		else
		{
			if (pDeclaratorRef->m_pDeclarator->m_localVar == 2)	// enum identifier
			{
				Tr_Exp* pTExpr = Tr_Ex(T_Const(pDeclaratorRef->m_pDeclarator->m_offset));
				pTExpr->m_pType = pDeclaratorRef->m_pDeclarator->m_pType;
				return pTExpr;
			}
			else
			{
				if (!/*pExpr->m_*/pDeclaratorRef->m_pDeclarator->m_referenced)
				{
					/*pExpr->m_*/pDeclaratorRef->m_pDeclarator->m_referenced = true;
					pGlobal->m_references.Add(/*pExpr->m_*/pDeclaratorRef);
				}

				return DeclaratorExpression(frame, /*pExpr->m_*/pDeclaratorRef->m_pDeclarator);
			}
		}
#endif
	}
	break;
#if 0
	else if (pExpr->tok.type == CToken::tok_keyword &&
			(pExpr->tok.pkw->n == KW_TRUE || pExpr->tok.pkw->n == KW_FALSE))
	{
		pExpr->m_pType = new Type(type_bool);
	}
#endif
#if 0
	else if (pExpr->tok.type == CToken::tok_keyword && pExpr->tok.pkw->n == KW_THIS)
	{
		Scope* p = pScope;
		while (p)
		{
			if (p->m_pClass)
			{
				Temp_temp* a5 = new Temp_temp;
				a5->m_an = 8+5;

				Tr_Exp* pT;
				pT	=	Tr_Ex(T_Mem(
							T_Binop('+',
								T_Temp(a5),
								T_Const(8/*-pDeclarator->m_pType->get_sizeof() - pDeclarator->m_spOffset*/)), 4/*pDeclarator->m_pType->get_sizeof()*/));
				pT->m_pType = new Type(type_pointer, sizeof_pointer);
				pT->m_pType->m_pPointerTo = new Type(type_class);
				pT->m_pType->m_pPointerTo->m_pClass = p->m_pClass;

				//pT->m_pType = p->m_pClass->m_pType;

				return pT;
			}

			p = p->m_pParentScope;
		}
		jerror("Use of 'this' in a non-member function is not allowed", pExpr->m_location);
	}
#if 0
	else if (pExpr->tok.type == CToken::tok_keyword && pExpr->tok.pkw->n == KW_NEW)
	{
		ASSERT(pExpr->m_pType != NULL);
	}
	else if (pExpr->tok.type == CToken::tok_keyword && pExpr->tok.pkw->n == KW_DELETE)
	{
		pExpr->right = Reduce(pExpr->right, pScope);
	}
	else if (pExpr->tok.type == CToken::tok_symbol && pExpr->tok.symbol == ',')
	{
		pExpr->left = Reduce(pExpr->left, pScope);
		pExpr->right = Reduce(pExpr->right, pScope);

	// The type and value of the result are the type and value of the right operand
		pExpr->m_pType = pExpr->right->m_pType;
	}
#endif
#endif
	case ast::Expression::A_UNOP:
	{
		switch (pExpr->unop.op)
		{
		case '++':	// pre-increment
			{
				Tr_Exp* right = TransExpression(frame, pExpr->unop.exp, pGlobal, pScope);
				if (right == NULL)
					return NULL;

				Type* pType = right->m_pType->GetStripped();

				Tr_Exp* pTExpr;
				pTExpr = Tr_Ex(
					T_ESeq(
						T_MoveStm(unEx(right), T_BinopExp('+', unEx(right), T_ConstExp(1))),
						unEx(right))
						);
				pTExpr->m_pType = pType;

				return pTExpr;
			}
			break;

		case '--':	// pre-decrement
			{
				ASSERT(0);
			}
			break;

		case '+':
		case '-':
		case '~':
			{
				Tr_Exp* right = TransExpression(frame, pExpr->unop.exp, pGlobal, pScope);
				if (right == NULL)
					return NULL;

				Type* pType = right->m_pType->GetStripped();

				T_Exp* eright = unEx(right);

				if (eright->kind == T_Exp::T_CONST)
				{
					switch (pExpr->unop.op)
					{
					case '+': break;
					case '-': eright->const_int.int32Val = -(LONGLONG)eright->const_int.int32Val; break;
					case '~': eright->const_int.int32Val = ~eright->const_int.int32Val; break;
					default: ASSERT(0);
					}

					Tr_Exp* pTExpr;
					pTExpr = Tr_Ex(eright);
					pTExpr->m_pType = pType;

					return pTExpr;
				}
				else
				{
					Tr_Exp* pTExpr;
					pTExpr = Tr_Ex(T_UnopExp(pExpr->unop.op, eright));
					pTExpr->m_pType = pType;

					return pTExpr;
				}
			}
			break;

		case '!':
			{
				Tr_Exp* right = TransExpression(frame, pExpr->unop.exp, pGlobal, pScope);
				if (right == NULL)
					return NULL;

				Type* pType = right->m_pType->GetStripped();

				if (right->kind == Tr_Exp::Tr_cx)
				{
					//Tr_Exp* pTExpr;
				//	pTExpr = Tr_Ex(T_UnopExp(pExpr->unop.op, unEx(right)));
				//	pTExpr->m_pType = pType;

					T_Stm* stm = right->cx.stm;
					if (stm->kind == T_Stm::T_SEQ)
					{
						ASSERT(stm->seq.left->kind == T_Stm::T_CJUMP);
						ASSERT(stm->seq.right->seq.right->kind == T_Stm::T_CJUMP);

						not_cjump(stm->seq.left);
						not_cjump(stm->seq.right->seq.right);

					//	stm = T_Seq(T_CJumpStm(not_relop(stm->seq.left->cjump.relop), stm->seq.left->cjump.left, stm->seq.left->cjump.right, stm->seq.left->cjump.f, stm->seq.left->cjump.t),
					//				T_Seq(stm->seq.right->seq.left,
					//					T_CJumpStm(not_relop(stm->seq.right->seq.right->cjump.relop), stm->seq.right->seq.right->cjump.left, stm->seq.right->seq.right->cjump.right, stm->seq.right->seq.right->cjump.f, stm->seq.right->seq.right->cjump.t)));
					}
					else if (stm->seq.left->kind == T_Stm::T_CJUMP)
					{
					//	stm = T_CJumpStm(not_relop(stm->cjump.relop), stm->cjump.left, stm->cjump.right, stm->cjump.f, stm->cjump.t);
						not_cjump(stm);
					}
					else
						ASSERT(0);

					return Tr_Cx(right->cx.falses, right->cx.trues, stm);
				}
				else if (right->kind == Tr_Exp::Tr_ex)
				{
					T_Stm* stm = T_CJumpStm('==', right->ex, T_ConstExp(0), NULL, NULL);
					Tr_Exp* texp = Tr_Cx(new PatchList(stm, NULL), new PatchList(stm, NULL), stm);
					texp->m_pType = pType;

					return texp;
				}
				else
				{
					VERIFY(0);
					return NULL;
				}
			}
			break;

		case '*':	// indirection / dereference
			{
				Tr_Exp* right = TransExpression(frame, pExpr->unop.exp, pGlobal, pScope);
				if (right == NULL)
					return NULL;
				
				if (right->m_pType == NULL)
				{
					printf("no type"/*, pExpr->m_location*/);
					return NULL;
				}
				else
				{
					Type* pType = right->m_pType->GetStripped();
					
					if (pType->get_Kind() == type_pointer)
					{
					//	ASSERT(pType->m_arrayDims.size() == 0);
						pType = pType->GetPointerTo();
					}
					else if (pType->get_Kind() == type_array)
					{
					//	ASSERT(pType->m_arrayDims.size() > 0);
						pType = ((ArrayType*)pType)->m_pElemType;
					}
					else
					{
						Std::Out << "illegal indirection";
						return NULL;
					}

					Tr_Exp* pTExpr;
					pTExpr = Tr_Ex(T_Mem(unEx(right), pType->get_sizeof()));
					pTExpr->m_pType = pType;
					
					return pTExpr;
				}
			}
			break;

		case '&':	// take address of
			{
				Tr_Exp* right = TransExpression(frame, pExpr->unop.exp, pGlobal, pScope);
				
				ASSERT(right->kind == Tr_Exp::Tr_ex);

				if (right->ex->kind == T_Exp::T_MEM)
				{
					Tr_Exp* pTExpr = Tr_Ex(right->ex->mem.mem);
					pTExpr->m_pType = new PointerType(right->m_pType);
					//pTExpr->m_pType->m_pPointerTo = right->m_pType;
				//	ASSERT(0);
#if 0
					pTExpr->m_pType->m_lvalue = false;	// & produces an r-value
#endif
					
					return pTExpr;
				}
				else if (right->ex->kind == T_Exp::T_CONST)
				{
					Std::Out << "'&' on constant"/*, pExpr->m_location*/;
				}
				else if (right->ex->kind == T_Exp::T_TEMP)
				{
					Tr_Exp* pTExpr = Tr_Ex(T_AddressOf(right->ex));
					pTExpr->m_pType = new PointerType(right->m_pType);
					
					return pTExpr;
				}
				else
				{
					ASSERT(0);
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
	break;

	case ast::Expression::A_POSTOP:
	{
		Tr_Exp* texp = TransExpression(frame, pExpr->unop.exp, pGlobal, pScope);
		if (texp == NULL)
			return NULL;

		Tr_Exp* tr = NULL;

		Temp_temp** r = new Temp_temp*;

		if (pExpr->unop.op == '++')
		{
			tr = Tr_Ex(
				T_ESeq(T_MoveStm(T_Temp(r), unEx(texp)),
					T_ESeq(T_MoveStm(unEx(texp), T_BinopExp('+', T_Temp(r), T_ConstExp(1))),
						T_Temp(r))));
		}
		else if (pExpr->unop.op == '--')
		{
			tr = Tr_Ex(
				T_ESeq(T_MoveStm(T_Temp(r), unEx(texp)),
					T_ESeq(T_MoveStm(unEx(texp), T_BinopExp('-', T_Temp(r), T_ConstExp(1))),
						T_Temp(r))));
		}
		else
		{
			ASSERT(0);
		}

		return tr;
	}
	break;

	case ast::Expression::A_BINOP:
	{
		switch (pExpr->binop.op)
		{
		case '::':
			{
				if (pExpr->binop.left->kind == ast::Expression::A_TEMPLATEID)
				{
					/*
					pExpr = pExpr->binop.left;

					if (String(pExpr->templateid.id) == "__d0") return Tr_Ex(T_Temp(&d0), &Types::type_int);
					if (String(pExpr->templateid.id) == "__d1") return Tr_Ex(T_Temp(&d1), &Types::type_int);
					if (String(pExpr->templateid.id) == "__d2") return Tr_Ex(T_Temp(&d2), &Types::type_int);
					if (String(pExpr->templateid.id) == "__d3") return Tr_Ex(T_Temp(&d3), &Types::type_int);
					if (String(pExpr->templateid.id) == "__d4") return Tr_Ex(T_Temp(&d4), &Types::type_int);
					if (String(pExpr->templateid.id) == "__d5") return Tr_Ex(T_Temp(&d5), &Types::type_int);
					if (String(pExpr->templateid.id) == "__d6") return Tr_Ex(T_Temp(&d6), &Types::type_int);
					if (String(pExpr->templateid.id) == "__d7") return Tr_Ex(T_Temp(&d7), &Types::type_int);
					if (String(pExpr->templateid.id) == "__a0") return Tr_Ex(T_Temp(&a0), &Types::type_void);
					if (String(pExpr->templateid.id) == "__a1") return Tr_Ex(T_Temp(&a1), &Types::type_void);
					if (String(pExpr->templateid.id) == "__a2") return Tr_Ex(T_Temp(&a2), &Types::type_void);
					if (String(pExpr->templateid.id) == "__a3") return Tr_Ex(T_Temp(&a3), &Types::type_void);
					if (String(pExpr->templateid.id) == "__a4") return Tr_Ex(T_Temp(&a4), &Types::type_void);
					if (String(pExpr->templateid.id) == "__a5") return Tr_Ex(T_Temp(&a5), &Types::type_void);
					if (String(pExpr->templateid.id) == "__a6") return Tr_Ex(T_Temp(&a6), &Types::type_void);
					if (String(pExpr->templateid.id) == "__a7") return Tr_Ex(T_Temp(&a7), &Types::type_void);
					*/

					Declarator* pDeclarator;

					ast::Expression* p = pExpr;
					do
					{
						if (pScope == NULL)
						{
							raise(Exception("undeclared identifier"));
						}

						pDeclarator = pScope->GetDeclarator(p->binop.left->templateid.id);
						if (pDeclarator)
						{
							if (NamespaceType* pname = dynamic_cast<NamespaceType*>(pDeclarator->m_pType))
							{
								pScope = pname->m_pScope;
							}
						}
						else
							pScope = NULL;

						p = p->binop.right;
					}
					while (p);

					if (/*pExpr->m_*/pDeclarator == NULL)
					{
						char msg[1024];
						sprintf_s(msg, "error(%d): '%s' : undeclared identifier\n", pExpr->m_line_pos, CString(pExpr->templateid.id).c_str());
					//	printf(msg);
						printf(msg);
					}
					else
					{
						if (pDeclarator->m_localVar == 2)	// enum identifier
						{
							Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(pDeclarator->m_offset));
							pTExpr->m_pType = pDeclarator->m_pType;
							return pTExpr;
						}
						else
						{
							if (!/*pExpr->m_*/pDeclarator->m_referenced)
							{
								/*pExpr->m_*/pDeclarator->m_referenced = true;
								pGlobal->m_references.Add(/*pExpr->m_*/pDeclarator);
							}

							return DeclaratorExpression(frame, /*pExpr->m_*/pDeclarator);
						}
					}
				}
				else
					ASSERT(0);
			}
			break;

		case '.':
			{
				// object.member
				// node->left = object
				// node->right = member

				Tr_Exp* tleft = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
				if (tleft == NULL)
					return NULL;
				
				if (tleft->m_pType != NULL)
				{
					/*
					if (tleft->m_pType->GetStripped()->get_Kind() == type_templateinst)
					{
						ASSERT(0);
	#if 0
						printf("");
						pExpr->left->m_pType = InstantiateTemplateType(pExpr->left->m_pType->GetType()->m_ArgTypes, pExpr->left->m_pType->GetType());
	#endif
					}
					*/
				}
				
				ClassType* pClass = nullptr;
				if (tleft->m_pType == nullptr || (pClass = tleft->m_pType->AsClass()) == nullptr)
				{
					if (tleft->m_pType != nullptr)
					{
						String strtype = tleft->m_pType->ToString();
						String strtypeun = tleft->m_pType->GetStripped()->ToString();
						// TODO
#if 0
						char msg[1024];
						sprintf_s(msg, "left of '.%s' must have class/struct/union type instead of: %s (%s)", pExpr->binop.right->templateid.id, strtype->c_str(), strtypeun->c_str());
						printf(msg/*, pExpr->m_location*/);
#endif
					}
					else
					{
						char msg[1024];
						sprintf_s(msg, "left of '.%s' must have class/struct/union type", CString(pExpr->binop.right->templateid.id).c_str());
						printf(msg/*, pExpr->m_location*/);
					}
				}
				else
				{
					CalcClass(NULL, pClass, 2/*TODO*/);

					if (pExpr->binop.right && pExpr->binop.right->binop.left->kind != ast::Expression::A_TEMPLATEID)
					{
						printf("Expected member name"/*, pExpr->m_location*/);
					}
					else if (pClass->m_sizeof == -1)
					{
						// TODO
#if 0
						char msg[1024];
						sprintf_s(msg, "use of incomplete struct '%s'", pClass->m_name->c_str());
						printf(msg/*, pExpr->m_location*/);
#endif
					}
					else
					{
						Declarator* pRightDeclarator = pClass->m_pScope->GetDeclarator(pExpr->binop.right->binop.left->templateid.id);
						if (pRightDeclarator == NULL)
						{
							ASSERT(tleft->m_pType->GetStripped()->get_Kind() == type_class);

							ClassType* pClass = tleft->m_pType->GetStripped()->AsClass();
							
							// TODO, have this
#if 0
							char className[512];

							if (pClass->m_name.GetLength())
							{
								sprintf_s(className, "'%s'", pClass->m_name->c_str());
							}
							else
							{
								strcpy_s(className, "(unnamed)");
							}

							char msg[1024];
							sprintf_s(msg, "'%s' : is not a member of %s",
								pExpr->binop.right->templateid.id->c_str(),
								className);
							
							printf(msg/*, pExpr->m_location*/);
#endif
						}
						else
						{
#if 0
							if (/*pExpr->right->m_*/pDeclaratorRef->m_pDeclarator->m_pOwnerScope->m_pClass != pClass)
							{
								ASSERT(0);
	#if 0
								// Cast left expression
								CExpression* pExpr2 = new CExpression(pScope);
								pExpr2->tok.type = CToken::tok_symbol;
								pExpr2->tok.symbol = (DWORD)'('|('U'<<8);
								pExpr2->m_pType = new Type(type_class);
								//pExpr2->m_pType->m_pPointerTo = new Type(type_class);
								pExpr2->m_pType->m_pClass = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pOwnerScope->m_pClass;
								
								pExpr2->right = pExpr->left;
								
								pExpr2 = Reduce(pExpr2, pScope);	// hm.. right gets reduced twice
								
								pExpr->left = pExpr2;
								
								pExpr->m_pDeclaratorRef = pExpr->right->m_pDeclaratorRef;
								pExpr->m_pType = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pType->Clone();
								
								//	pExpr2->right = pExpr;
								
								
								//	pExpr2->right = pExpr;
								//	pExpr = pExpr2;
	#endif
							}
							else
#endif
							{


								T_Exp* left = unEx(tleft);
								ASSERT(left->kind == T_Exp::T_MEM);
								left = left->mem.mem;

								if (false)
								{
									T_Exp* e = T_Mem(
										T_BinopExp('+', left, T_ConstExp(pRightDeclarator->m_offset)), pRightDeclarator->m_pType->GetStripped()->get_sizeof());

								//	CDeclarator* pDeclarator = pScope->GetDeclarator(pExpr->binop.left->binop.left->templateid.id);

									/*
									MemberRegs* & regs = memberregs[tleft->ex];
									if (regs == NULL)
									{
										regs = new MemberRegs;
									}
									*/
									Temp_temp** & temp = membertemp[e];
									if (temp == NULL)
									{
										temp = new Temp_temp*;
										*temp = new Temp_temp;
									}

									Tr_Exp* pT;
									pT = Tr_Ex(T_Temp(temp));
									pT->m_pType = pRightDeclarator->m_pType;
									return pT;
								}

								{
									if (pRightDeclarator->m_pType->GetStripped()->get_Kind() == type_function)
									{
										T_Declarator* & label = labels[pRightDeclarator];
										if (label == NULL)
										{
											label = new T_Declarator;
											label->m_pDeclarator = pRightDeclarator;
											label->m_tempLabel = new Temp_label;

											tglobals.push_back(label);
										}

										Tr_Exp* pT;
										pT = Tr_Ex(T_Mem(T_Name(label->m_tempLabel), 4/*pRightDeclarator->m_pType->get_sizeof()*/));
										pT->m_pType = pRightDeclarator->m_pType;
										pT->ex->m_size = 4;//pDeclarator->m_pType->get_sizeof();

										return pT;
									}
									else
									{
										Tr_Exp* tr;
									
										tr = Tr_Ex(
											T_Mem(
												T_BinopExp('+', left, T_ConstExp(pRightDeclarator->m_offset)), pRightDeclarator->m_pType->GetStripped()->get_sizeof()));
										
										tr->m_pType = pRightDeclarator->m_pType;
										
										return tr;
									}
								}
							}
						}
					}
				}
			}
			break;

			case '=':
			{
				Tr_Exp* left = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
				if (left == NULL)
				{
					return NULL;
				}
				else
				{
					Tr_Exp* right = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);

					if (right == NULL)
					{
						return NULL;
					}
					else
					{
						right = ConvertExpressionType(right, left->m_pType);

						if (!right->m_pType->Equals(*left->m_pType))
						{
							//ConvertExpressionType(pExpr->right, pExpr->left->m_pType);
							
							String str0 = right->m_pType->ToString();
							String str1 = left->m_pType->ToString();
							
							//	std::string fstr = pExpr->m_pDeclarator->toString();
							
							ASSERT(0);;
#if 0
							char msg[1024];
							sprintf_s(msg, "incompatible types - from '%s' to '%s'",
								//	fstr.c_str(),//pExpr->left->tok.ident,
								//	i+1,//pDeclarator->m_pFunction->m_parameters.size()-i,
								str0->c_str(), str1->c_str());
							printf(msg);//, pExpr->m_location);
#endif						
							/*
							printf("***\n");
							printoutall(pExpr->left->m_pType);
							printf("***\n");
							*/
							return NULL;
						}
						else
						{
							Tr_Exp* p = Tr_Nx(T_MoveStm(unEx(left)/*->ex*/, unEx(right)));
							p->m_pType = left->m_pType;
							return p;
						}
					}
				}
			}
			break;

		case ',':
			{
				Tr_Exp* left = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
				if (left == NULL)
					return NULL;

				Tr_Exp* right = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);
				if (right == NULL)
					return NULL;

				return Tr_Ex(T_ESeq(unNx(left), unEx(right)), right->m_pType);
			}
			break;

		case '[':
			{
				Tr_Exp* left = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
				if (left == NULL)
					return NULL;

				Tr_Exp* right = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);
				if (right == NULL)
					return NULL;

				Tr_Exp* tr;

				T_Exp* eleft = unEx(left);
				T_Exp* eright = unEx(right);

				if (left->m_pType->get_Kind() == type_pointer)
				{
					PointerType* pType = (PointerType*)left->m_pType;

				//	ASSERT(eleft->kind == T_Exp::T_MEM);
				//	eleft = eleft->mem.mem;

					if (eright->kind == T_Exp::T_CONST)
					{
						if (eright->const_int.int32Val == 0)
						{
							tr =
								Tr_Ex(
									T_Mem(
										eleft,
										pType->GetPointerTo()->get_sizeof()
									)
								);
						}
						else
						{
							tr =
								Tr_Ex(
									T_Mem(
										T_BinopExp('+',
											eleft,
											T_ConstExp(eright->const_int.int32Val * pType->GetPointerTo()->get_sizeof())),
										pType->GetPointerTo()->get_sizeof()
									)
								);
						}
					}
					else
					{
						tr =
							Tr_Ex(
								T_Mem(
									T_BinopExp('+', eleft,
										T_BinopExp('*', eright, T_ConstExp(pType->GetPointerTo()->get_sizeof()))
									),
									pType->GetPointerTo()->get_sizeof()
								)
							);
					}

					tr->m_pType = pType->GetPointerTo();
				}
				else
				{
					ASSERT(left->m_pType->get_Kind() == type_array);
					ArrayType* pType = (ArrayType*)left->m_pType;

					ASSERT(eleft->kind == T_Exp::T_MEM);

					eleft = eleft->mem.mem;

					if (eright->kind == T_Exp::T_CONST)
					{
						if (eright->const_int.int32Val == 0)
						{
							tr =
								Tr_Ex(
									T_Mem(
										eleft,
										pType->m_pElemType->get_sizeof()
									)
								);
						}
						else
						{
							tr =
								Tr_Ex(
									T_Mem(
										T_BinopExp('+',
											eleft,
											T_ConstExp(eright->const_int.int32Val * pType->m_pElemType->get_sizeof())),
										pType->m_pElemType->get_sizeof()
									)
								);
						}
					}
					else
					{
						tr =
							Tr_Ex(
								T_Mem(
									T_BinopExp('+', eleft,
										T_BinopExp('*', eright, T_ConstExp(pType->m_pElemType->get_sizeof()))
									),
									pType->m_pElemType->get_sizeof()
								)
							);
					}
					tr->m_pType = pType->m_pElemType;
				}
				return tr;
			}
			break;

		case '^':
		case '|':
		case '&':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '<<':
		case '>>':
			{
				Tr_Exp* left = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);

				if (left == NULL)
				{
					left = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
					ASSERT(0);
					return NULL;
				}

				Tr_Exp* right = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);

				ASSERT(right);
				if (right == NULL)
					return NULL;
				
				if ((left->m_pType->get_Kind() == type_char ||
					left->m_pType->get_Kind() == type_unsigned_char ||
					left->m_pType->get_Kind() == type_short ||
					left->m_pType->get_Kind() == type_unsigned_short ||
					left->m_pType->get_Kind() == type_int ||
					left->m_pType->get_Kind() == type_unsigned_int) &&

					(right->m_pType->get_Kind() == type_char ||
					right->m_pType->get_Kind() == type_unsigned_char ||
					right->m_pType->get_Kind() == type_short ||
					right->m_pType->get_Kind() == type_unsigned_short ||
					right->m_pType->get_Kind() == type_int ||
					right->m_pType->get_Kind() == type_unsigned_int))
				{
					left = ConvertExpressionType(left, Types::get_int());
					right = ConvertExpressionType(right, Types::get_int());
				}

				if (left->m_pType->get_Kind() == type_array)
				{
					left = ConvertExpressionType(left, new PointerType(((ArrayType*)left->m_pType)->m_pElemType));
				}

				if (right->m_pType->get_Kind() == type_array)
				{
					right = ConvertExpressionType(right, new PointerType(((ArrayType*)right->m_pType)->m_pElemType));
				}

				if (left->m_pType != NULL && right->m_pType != NULL)
				{
					Tr_Exp* tr;

					if (pExpr->binop.op == '>>')
					{
						if (left->m_pType->get_Kind() == type_unsigned_char ||
							left->m_pType->get_Kind() == type_unsigned_short ||
							left->m_pType->get_Kind() == type_unsigned_long ||
							left->m_pType->get_Kind() == type_unsigned_int)
						{
							tr = Tr_Ex(T_BinopExp('shr', unEx(left), unEx(right)));
							tr->m_pType = left->m_pType;
						}
						else
						{
							tr = Tr_Ex(T_BinopExp('sar', unEx(left), unEx(right)));
							tr->m_pType = left->m_pType;
						}
					}
					else if ((pExpr->binop.op == '-') && (
						left->m_pType->GetStripped()->get_Kind() == type_pointer &&
						right->m_pType->GetStripped()->get_Kind() == type_pointer))
					{
						tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(left), unEx(right)));
						tr->m_pType = &Types::type_int;
					}
					else if ((pExpr->binop.op == '+') && (
						left->m_pType->GetStripped()->get_Kind() == type_pointer &&
						right->m_pType->GetStripped()->get_Kind() == type_int))
					{
						unsigned int sizeofElement = left->m_pType->GetStripped()->GetPointerTo()->get_sizeof();
						if (sizeofElement == 1)
						{
							tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(left), unEx(right)));
						}
						else
						{
							T_Exp* eright = unEx(right);

							if (eright->kind == T_Exp::T_CONST)
							{
								tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(left), T_ConstExp(eright->const_int.int32Val * sizeofElement)));
							}
							else
							{
								tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(left), T_BinopExp('*', eright, T_ConstExp(sizeofElement))));
							}
						}

						tr->m_pType = left->m_pType;
					}
					else if ((pExpr->binop.op == '+') && (
						left->m_pType->GetStripped()->get_Kind() == type_int &&
						right->m_pType->GetStripped()->get_Kind() == type_pointer))
					{
						unsigned int sizeofElement = left->m_pType->GetStripped()->GetPointerTo()->get_sizeof();

						if (sizeofElement == 1)
						{
							tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(right), unEx(left)));
						}
						else
						{
							tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(right), T_BinopExp('*', unEx(left), T_ConstExp(sizeofElement))));
						}

						tr->m_pType = right->m_pType;
					}

					else if (pExpr->binop.op == '&' &&
						left->kind == Tr_Exp::Tr_ex &&
						left->ex->kind == T_Exp::T_CONST &&
						left->ex->const_int.int32Val == 1)
					{
						tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(left), unEx(right)));
						tr->m_pType = &Types::type_bool;
					}
					else if (pExpr->binop.op == '&' &&
						right->kind == Tr_Exp::Tr_ex &&
						right->ex->kind == T_Exp::T_CONST &&
						right->ex->const_int.int32Val == 1)
					{
						tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(left), unEx(right)));
						tr->m_pType = &Types::type_bool;
					}
					else if (pExpr->binop.op == '/')
					{
						// TODO, udiv / sdiv

						if (left->m_pType->get_Kind() == type_long_long)
						{
							right = ConvertExpressionType(right, &Types::type_long_long);
						}
						else if (right->m_pType->get_Kind() == type_long_long)
						{
							left = ConvertExpressionType(left, &Types::type_long_long);
						}

						tr = Tr_Ex(T_BinopExp('sdiv', unEx(left), unEx(right)));
						tr->m_pType = left->m_pType;
					}
					else if (pExpr->binop.op == '%')
					{
						// TODO, umod / smod

						tr = Tr_Ex(T_BinopExp('smod', unEx(left), unEx(right)));
						tr->m_pType = left->m_pType;
					}
					else
					{
						if (left->m_pType->get_Kind() == type_long_long)
						{
							right = ConvertExpressionType(right, &Types::type_long_long);
						}
						else if (right->m_pType->get_Kind() == type_long_long)
						{
							left = ConvertExpressionType(left, &Types::type_long_long);
						}

						T_Exp* eleft = unEx(left);
						T_Exp* eright = unEx(right);

						if (eleft->kind == T_Exp::T_CONST && eright->kind == T_Exp::T_CONST)
						{
							long value;

							switch (pExpr->binop.op)
							{
							case '+':
								value = eleft->const_int.int32Val + eright->const_int.int32Val;
								break;

							case '-':
								value = eleft->const_int.int32Val - eright->const_int.int32Val;
								break;

							case '*':
								value = eleft->const_int.int32Val * eright->const_int.int32Val;
								break;

							case '/':
								{
									ASSERT(eright->const_int.int32Val != 0);
									value = eleft->const_int.int32Val / eright->const_int.int32Val;
								}
								break;

							case '%':
								{
									ASSERT(eright->const_int.int32Val != 0);
									value = eleft->const_int.int32Val % eright->const_int.int32Val;
								}
								break;

							case '|':
								value = eleft->const_int.int32Val | eright->const_int.int32Val;
								break;

							case '&':
								value = eleft->const_int.int32Val & eright->const_int.int32Val;
								break;

							case '^':
								value = eleft->const_int.int32Val ^ eright->const_int.int32Val;
								break;

							case '<<':
								{
									value = eleft->const_int.int32Val << eright->const_int.int32Val;
								}
								break;

							case '>>':
								{
									// TODO, difference between signed and unsigned
									DebugTraceLn(__FILE__ << paren(__LINE__+1) << " : TODO");

									if (true)
										value = (int32)eleft->const_int.int32Val >> eright->const_int.int32Val;
									else
										value = (uint32)eleft->const_int.int32Val >> eright->const_int.int32Val;
								}
								break;

							default:
								ASSERT(0);
							}

							tr = Tr_Ex(T_ConstExp(value));
							tr->m_pType = left->m_pType;
						}
						else
						{
							// TODO, check for compatibility
							tr = Tr_Ex(T_BinopExp(pExpr->binop.op, eleft, eright));
							tr->m_pType = left->m_pType;
						}
					}

					tr->ex->m_size = tr->m_pType->get_sizeof();
					return tr;
				}
				else
				{
					printf("error in expressions"/*, pExpr->m_location*/);
				}
			}
			break;

		case '&&':
			{
				Tr_Exp* test = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
				if (test == NULL)
					return NULL;

				Tr_Exp* elseexp = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);
				if (elseexp == NULL)
					return NULL;

				// 'outer' true and false labels are unknown at this time

				Temp_label* a_true = new Temp_label;
				Cx a = unCx(test);
				PatchTrue(a.trues, a_true);

				Cx b = unCx(elseexp);

				T_Stm* stm =	T_Seq(a.stm,
										T_Seq(T_Label(a_true),	// if the a cjump succeeds, continue and perform b cjump (both must succeed)
											b.stm));

				return Tr_Cx(
					b.trues,	// a.trues has already been takes care of
					Reverse(a.falses, b.falses),	// join them
					stm);
			}
			break;

		case '||':
			{
				Tr_Exp* test = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
				if (test == NULL)
					return NULL;

				Tr_Exp* elseexp = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);
				if (elseexp == NULL)
					return NULL;

				// 'outer' true and false labels are unknown at this time

				Temp_label* a_false = new Temp_label;
				Cx a = unCx(test);
				PatchFalse(a.falses, a_false);

				Cx b = unCx(elseexp);

				T_Stm* stm =	T_Seq(a.stm,
										T_Seq(T_Label(a_false),	// if the a cjump fails, then perform b
											b.stm));

				Tr_Exp* texp = Tr_Cx(
					Reverse(a.trues, b.trues),	// join them
					b.falses,	// a.falses have already been taken care of
					stm);

				texp->m_pType = &Types::type_bool;
				return texp;

#if 0
				Temp_temp* r = new Temp_temp;

				Cx a = unCx(test);
				T_Exp* b = T_ConstExp(1);
				T_Exp* c = unEx(elseexp);

				Temp_label* t = new Temp_label;
				Temp_label* f = new Temp_label;
				Temp_label* join = new Temp_label;

				doPatch(a.trues, t);
				doPatch(a.falses, f);

				T_Exp* e = T_ESeq(
									T_Seq(a.stm,
										T_Seq(T_Label(t),
											T_Seq(T_MoveStm(T_Temp(r), b),
												T_Seq(T_JumpStm(T_Name(join), new Temp_labelList(join, NULL)),
													T_Seq(T_Label(f),
														T_Seq(T_MoveStm(T_Temp(r), c),
															T_Seq(T_JumpStm(T_Name(join), new Temp_labelList(join, NULL)),
																T_Label(join)	))))))), T_Temp(r));

				return Tr_Ex(e);
#endif
			}
			break;

		case '==':
		case '!=':
		case '<':
		case '>':
		case '<=':
		case '>=':
			{
				Tr_Exp* tr;

				if (true)
				{
					Tr_Exp* left = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
					if (left == NULL)
						return NULL;
					
					Tr_Exp* right = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);
					if (right == NULL)
						return right;
					
					//	Temp_label* z = new Temp_label;
					T_Stm* s1 = /*T_Seq(*/T_CJumpStm(pExpr->binop.op, unEx(left), unEx(right), NULL, NULL);/*,
											T_Label(z));*/
					
					tr = Tr_Cx(new PatchList(s1/*->cjump.t*/, NULL), new PatchList(s1/*->cjump.f*/, NULL), s1);
					
					//	ASSERT(s1->cjump.t);
					//	ASSERT(s1->cjump.f);
				}
				else
				{
					Tr_Exp* left = TransExpression(frame, pExpr->binop.left, pGlobal, pScope);
					if (left == NULL) return NULL;

					Tr_Exp* right = TransExpression(frame, pExpr->binop.right, pGlobal, pScope);
					if (right == NULL) return NULL;

					tr = Tr_Ex(T_BinopExp(pExpr->binop.op, unEx(left), unEx(right)));
				}
				
				tr->m_pType = &Types::type_bool;
				
				return tr;
			}
			break;

		default:
			ASSERT(0);
		}
	}
	break;

	case ast::Expression::A_CAST:
	{
	//	ASSERT(pExpr->cast.m_pType != NULL);
	//	ASSERT(pExpr->left == NULL);

		ast::CastExpression* castexp = dynamic_cast<ast::CastExpression*>(pExpr);

		Type* pType = ast::GetType(castexp->m_typeId->m_declspecList, NULL, pGlobal, pScope, pScope, frame? frame->m_pDeclarator: NULL, NULL, 0, false/*TODO*/);
		ASSERT(pType);

		Declarator* pDeclarator = new Declarator;
		pDeclarator->m_pType = pType;
		ast::Extract(castexp->m_typeId->m_declarator, pDeclarator, pType, pScope, pScope, frame? frame->m_pDeclarator: NULL, NULL/*tp*/, pGlobal, false/*TODO*/);

		if (castexp->m_exp)
		{
			Tr_Exp* right = TransExpression(frame, castexp->m_exp, pGlobal, pScope);
			if (right == NULL)
				return NULL;
			
			right = ConvertExpressionType(right, pDeclarator->m_pType);
			
			return right;
		}
	}
	break;

	case ast::Expression::A_CALL:
	{
		ast::CallExp* callexp = dynamic_cast<ast::CallExp*>(pExpr);
		if (callexp->m_left == NULL)
		{
			Std::Out << ("left expression = NULL in function call ?"/*, pExpr->m_location*/);
			return NULL;
		}
		else
		{
			if (callexp->m_left->kind == ast::Expression::A_BINOP && callexp->m_left->binop.left->kind == ast::Expression::A_TEMPLATEID)
			{
				if (String(callexp->m_left->binop.left->templateid.id) == "__is_class")
				{
					if (callexp->m_args == NULL ||
						callexp->m_args->tail != NULL ||
						callexp->m_args->head->GetKind() != ast::Expression::A_TYPE)
					{
						Std::Out << "__is_class expects one type argument";
						return NULL;
					}

					Type* pType = GetAbstractType(frame, pGlobal, pScope, static_cast<ast::TypeExp*>(callexp->m_args->head)->m_typeId);

					Tr_Exp* tr = Tr_Ex(T_ConstExp(pType->get_Kind() == type_class && pType->AsClass()->GetClassKey() != ClassKey_union));
					tr->m_pType = &Types::type_bool;
					return tr;
				}
				else if (String(callexp->m_left->binop.left->templateid.id) == "__is_enum")
				{
					if (callexp->m_args == NULL ||
						callexp->m_args->tail != NULL ||
						callexp->m_args->head->GetKind() != ast::Expression::A_TYPE)
					{
						Std::Out << "__is_enum expects one type argument";
						return NULL;
					}

					Type* pType = GetAbstractType(frame, pGlobal, pScope, static_cast<ast::TypeExp*>(callexp->m_args->head)->m_typeId);

					Tr_Exp* tr = Tr_Ex(T_ConstExp(pType->get_Kind() == type_enum));
					tr->m_pType = &Types::type_bool;
					return tr;
				}
				else if (String(callexp->m_left->binop.left->templateid.id) == "__is_union")
				{
					if (callexp->m_args == NULL ||
						callexp->m_args->tail != NULL ||
						callexp->m_args->head->GetKind() != ast::Expression::A_TYPE)
					{
						Std::Out << "__is_union expects one type argument";
						return NULL;
					}

					Type* pType = GetAbstractType(frame, pGlobal, pScope, static_cast<ast::TypeExp*>(callexp->m_args->head)->m_typeId);

					Tr_Exp* tr = Tr_Ex(T_ConstExp(pType->get_Kind() == type_class && pType->AsClass()->GetClassKey() == ClassKey_union));
					tr->m_pType = &Types::type_bool;
					return tr;
				}
				else if (String(callexp->m_left->binop.left->templateid.id) == "__is_empty")
				{
					VERIFY(0);
				}
				else if (String(callexp->m_left->binop.left->templateid.id) == "__is_polymorphic")
				{
					if (callexp->m_args == nullptr ||
						callexp->m_args->tail != nullptr ||
						callexp->m_args->head->GetKind() != ast::Expression::A_TYPE)
					{
						Std::Out << "__is_polymorphic expects one type argument";
						return NULL;
					}

					Type* pType = GetAbstractType(frame, pGlobal, pScope, static_cast<ast::TypeExp*>(callexp->m_args->head)->m_typeId);

					Tr_Exp* tr = Tr_Ex(T_ConstExp(pType->get_Kind() == type_class && pType->AsClass()->IsPolymorphic()));
					tr->m_pType = &Types::type_bool;
					return tr;
				}
			}

			/*
			if (pExpr->left->tok.symbol == '::' && pExpr->left->left == NULL)
			{
			printf("");
			}
				*/
			Tr_Exp* obj;
			Tr_Exp* left;

			if (callexp->m_left->kind == ast::Expression::A_BINOP && callexp->m_left->binop.op == '.')
			{
				Tr_Exp* o = TransExpression(frame, callexp->m_left->binop.left, pGlobal, pScope);
				ASSERT(o->ex->kind == T_Exp::T_MEM);

				obj = Tr_Ex(o->ex->mem.mem);
				obj->m_pType = new PointerType(o->m_pType);

				left = TransExpression(frame, callexp->m_left, pGlobal, pScope);
			}
			else
			{

				obj = NULL;
				left = TransExpression(frame, callexp->m_left, pGlobal, pScope);
			}
			
			if (left == NULL)
			{
				Std::Out << ("left expression = NULL in function call"/*, pExpr->m_location*/);
			}
			else
			{
				if (left->m_pType != NULL)
				{
					Type* pType = left->m_pType->GetStripped();
					
					if (pType->get_Kind() == type_pointer)
					{
						pType = pType->GetPointerTo()->GetStripped();
					}
					
					if (pType->get_Kind() == type_function)//m_pFunction)
					{
						Tr_Exp* tr = NULL;
						
						//						pExpr->m_pDeclarator = pDeclarator;
						
						T_Exp* pCall;
						
						size_t narg = 0;
						
#if 0
						if (pType->GetFunction()->m_thiscall)
						{
							ASSERT(0);
	#if 0
							//	CExpression* pThis = new CExpression(pScope);
							//	pThis->
							
							Tr_Exp* leftob = TransExpression(frame, pExpr->left->left, pGlobal, pScope);
							Type* pType = new Type(type_pointer, sizeof_pointer);
							pType->m_pPointerTo = leftob->m_pType;
							leftob->m_pType = pType;
							
							tr = Tr_Ex(pCall = T_Call(unEx(left)));
							pCall->call.args = new ExpList(unEx(leftob)->mem, NULL);
							//	pCall->call.args->expr = pExpr->left;
							narg = 1;
	#endif
						}
						else if (true || pType->GetFunction()->m_libcall.m_offset != 0)	// libcall
						{
							/*
							pExpr->m_pBaseDeclarator = pScope->GetDeclarator(pType->m_pFunction->m_libcall.m_basename.c_str());
							if (pExpr->m_pBaseDeclarator == NULL)
							{
								char msg[512];
								sprintf(msg, "undeclared libcall base '%s'", pType->m_pFunction->m_libcall.m_basename.c_str());
								jerror(msg, pExpr->m_location);
							}
							*/
						//	Temp_temp* temp = new Temp_temp;
						//	temp->m_an = 8+6;
							/*
							tr = Tr_Ex(
								T_ESeq(
								T_Move(T_Temp(a6), unEx(DeclaratorExpression(frame, pExpr->m_pBaseDeclarator->m_pDeclarator))),
								pCall = T_Call(T_Binop('+', T_Temp(a6), T_Const(pType->m_pFunction->m_libcall.m_offset)))
								)
								);
								*/

							tr = Tr_Ex(pCall = T_Call(unEx(left)));

							/*
							tr = Tr_Ex(
								//T_ESeq(
								//T_Move(T_Temp(a6), unEx(DeclaratorExpression(frame, pExpr->m_pBaseDeclarator->m_pDeclarator))),
								pCall = T_Call(T_BinopExp('+', T_Temp(a6), T_ConstExp(pType->GetFunction()->m_libcall.m_offset)))
								//)
								);
								*/
							
							//	pExpr->m_baseOffset = pDeclarator->m_libcall.m_offset;
						}
						else
#endif
						{
							//	pExpr->m_pDeclarator = pDeclarator;
							tr = Tr_Ex(pCall = T_Call(unEx(left)));
						}
						
						tr->m_pType = pType->AsFunction()->m_pReturnType;
						//int i = pExpr->m_pDeclarator->m_pFunction->m_parameters.size()-1;
						
						vector<ast::ExpressionList*> args;
						for (ast::ExpressionList* pArgExpr = callexp->m_args; pArgExpr != nullptr; pArgExpr = pArgExpr->tail)
						{
							ASSERT(pArgExpr->head != nullptr);
							args.push_back(pArgExpr);
						}

						if (obj)
						{
							pCall->call.args = new ArgList(unEx(obj), pCall->call.args);
						}
						
						for (; narg < args.size(); ++narg)
						{
							//CDeclarator* pArgDecl;
							FunctionParameters::Param* pArgDecl = nullptr;
							
							if (narg >= pType->AsFunction()->m_parameters.size())
							{
								if (!pType->AsFunction()->m_parameters.m_bVarArg)
								{
									Std::Out << ("too many arguments"/*, pExpr->m_location*/);
									break;
								}
								pArgDecl = NULL;
							}
							else
							{
								pArgDecl = &pType->AsFunction()->m_parameters[narg];
							}
							
							ast::ExpressionList* pArgExpr = args[narg];
							
							Tr_Exp* p;
							
	#if 0
							if (pType->m_pFunction->m_libcall.m_offset != 0 &&
								pType->m_pFunction->m_libcall.m_tagcall &&
								narg == pType->m_pFunction->m_parameters.size()-1)
							{
								Temp_temp* a7 = new Temp_temp;
								
								//continue;
								/*
								a7->m_an = 8+7;
								//	p = T_Unop('&', 
								
								  Temp_temp* tt = new Temp_temp;
								  tt->m_an = pArgDecl->m_libcall.m_reg-8;
								  
									 p = Tr_Ex(T_ESeq(T_Move(T_Temp(tt), T_Temp(a7)), T_Const(0)));
								*/
							}
							else
	#endif
							{
								p = TransExpression(frame, pArgExpr->head, pGlobal, pScope);
							}
							
							if (p == nullptr)
							{
								Std::Out << ("function argument failed"/*, pExpr->m_location*/);
								return NULL;
							}
							
							if (p->m_pType != nullptr)
							{
								if (pArgDecl)
								{
									if (pArgDecl->m_pType->get_Kind() == type_reference)
									{
										/*
										ASSERT(p->ex->kind == T_Exp::T_MEM);

										Tr_Exp* p2 = Tr_Ex(p->ex->mem.mem, new ReferenceType(p->m_pType));
										//p2->m_pType = ;
										p = p2;
										*/
										Tr_Exp* p2 = Tr_Ex(T_AddressOf(p->ex), new ReferenceType(p->m_pType));
										p = p2;
									}

									p = ConvertExpressionType(p, pArgDecl->m_pType);
									
									if (!p->m_pType->Equals(*pArgDecl->m_pType))
									{
										String str0 = p->m_pType->ToString();
										String str1 = pArgDecl->m_pType->ToString();
										
										ASSERT(0);
#if 0
										char msg[1024];
										sprintf_s(msg, "parameter %d: incompatible types - from '%s' to '%s'",
											//fstr.c_str(),//pExpr->left->tok.ident,
											narg+1,//pDeclarator->m_pFunction->m_parameters.size()-i,
											str0->c_str(), str1->c_str());
										printf(msg/*, pExpr->m_location*/);
#endif
									}
								}
							}
							
							//pCall->call.args->expr = pArgExpr;
							
#if 0
							if (pType->GetFunction()->m_libcall.m_offset != 0 &&
								pType->GetFunction()->m_libcall.m_tagcall &&
								narg == pType->GetFunction()->m_parameters.m_parameters.GetSize()-1)
							{
								ASSERT(0);
#if 0
								pCall->call.args = new ArgList(NULL, pCall->call.args);
								pCall->call.args->reg = - (pArgDecl->m_libcall.m_reg+1);
								
								pCall->call.args = new ExpList(unEx(p), pCall->call.args);
#endif
								//continue;
								/*
								a7->m_an = 8+7;
								//	p = T_Unop('&', 
								
								  Temp_temp* tt = new Temp_temp;
								  tt->m_an = pArgDecl->m_libcall.m_reg-8;
								  
									 p = Tr_Ex(T_ESeq(T_Move(T_Temp(tt), T_Temp(a7)), T_Const(0)));
							*/
							}
							else
#endif
							{
								pCall->call.args = new ArgList(unEx(p), pCall->call.args);
								if (pArgDecl && pArgDecl->m_reg >= 0)
								{
									ASSERT(pArgDecl->m_reg >= 0);
									pCall->call.args->reg = &regs[pArgDecl->m_reg];
								}
								/*
								if (narg == 0)
									pCall->call.args->reg = a6;
								else if (narg == 1)
									pCall->call.args->reg = a0;
								else if (narg == 2)
									pCall->call.args->reg = d0;
									*/
									
							//	ASSERT(0);
#if 0
								if (pArgDecl)
									pCall->call.args->reg = pArgDecl->m_libcall.m_reg;
#endif
							}
						}

						if (narg < pType->AsFunction()->m_parameters.m_parameters.GetSize())
						{
							char msg[256];
							/*if (pExpr->call.left->kind == ast::Expression::ast::A_ID)
								sprintf(msg, "'%s' : too few parameters", pExpr->call.left->templateid.id);
							else
							*/
								sprintf_s(msg, "too few parameters");
						
								Std::Out << (msg/*, pExpr->m_location*/);
						}
					
						return tr;
					}
					else
					{
						char msg[512];
					
						if (callexp->m_left->kind == ast::Expression::A_ID)
							sprintf_s(msg, "'%s' : not a function", callexp->m_left->templateid.id);
						else
							sprintf_s(msg, "not a function");
					
						Std::Out << (msg/*, pExpr->m_location*/);
					
						return nullptr;
					}
				}
				else
				{
					char msg[512];
				
					/*
					if (pExpr->left->tok.type == CToken::tok_ident)
					{
					sprintf(msg, "undeclared identifier '%s'", pExpr->left->tok.ident);
					}
					else if (pExpr->left->tok.type == CToken::tok_keyword)
					{
					sprintf(msg, "undeclared identifier '%s'", pExpr->left->tok.pkw->name);
					}
					else
					*/
					{
						sprintf_s(msg, "left side had no type");
					}
				
					Std::Out << (msg/*, pExpr->m_location*/);
				}
			}
		}
	}
	break;

	case ast::Expression::A_SIZEOF_TYPE:
		{
			ast::SizeofTypeExp* sizeofExp = dynamic_cast<ast::SizeofTypeExp*>(pExpr);

			Declarator declarator;
			declarator.m_pType = ast::GetType(sizeofExp->m_typeId->m_declspecList, nullptr, pGlobal, pScope, pScope, frame? frame->m_pDeclarator: nullptr, nullptr, 0, false/*TODO*/);
			ast::Extract(sizeofExp->m_typeId->m_declarator, &declarator, declarator.m_pType, pScope, pScope, frame? frame->m_pDeclarator: nullptr, nullptr/*tp*/, pGlobal, false/*TODO*/);

			Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(declarator.m_pType->get_sizeof()));
			pTExpr->m_pType = &System::Types::type_unsigned_int;
			return pTExpr;
		}
		break;

	default:
		ASSERT(0);
	}
#if 0
	else if (pExpr->tok.type == CToken::tok_symbol)
	{
		switch (pExpr->tok.symbol)
		{
#if 0
		case '::':
			{
				CExpression* pMemberExpr = pExpr->right;
				
				Scope* pScope2 = GetNestedScope(pScope, pExpr->left);
				if (pScope2)
				{
					declsmap::iterator decli;
					
					if (pMemberExpr->tok.type == CToken::tok_ident)
					{
						decli = pScope2->m_decls.find(pMemberExpr->tok.ident);
					}
					else if (pMemberExpr->tok.type == CToken::tok_keyword)
					{
						if (pMemberExpr->tok.pkw->n == KW_NEW)
							decli = pScope2->m_decls.find("operator_new");
						else if (pMemberExpr->tok.pkw->n == KW_DELETE)
							decli = pScope2->m_decls.find("operator_delete");
						else
							ASSERT(0);
					}
					else
						ASSERT(0);
					
					if (decli != pScope2->m_decls.end())
					{
						pExpr->m_pDeclaratorRef = (*decli).second;
						pExpr->m_pType = pExpr->m_pDeclaratorRef->m_pDeclarator->m_pType;
					}
					else
					{
						char msg[512];
						if (pMemberExpr->tok.type == CToken::tok_ident)
							sprintf(msg, "'%s' : undeclared identifier", pMemberExpr->tok.ident);
						else if (pMemberExpr->tok.type == CToken::tok_keyword)
							sprintf(msg, "'%s' : undeclared identifier", pMemberExpr->tok.pkw->name);
						else
							sprintf(msg, "undeclared identifier");
						
						pPP->jerror(msg);
					}
				}
				else
				{
					char msg[512];
					sprintf(msg, "'%s' : undeclared identifier", pMemberExpr->tok.ident);
					pPP->jerror(msg);
				}
			}
			break;
#endif

		case 'szof':
			{
				Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
				if (right == NULL)
					return NULL;
				
				return Tr_Ex(T_Const(right->m_pType->get_sizeof()));
			}
			break;
			
		case '(':	// function call
			{
				if (pExpr->left == NULL)
				{
					jerror("left expression = NULL in function call ?", pExpr->m_location);
				}
				else
				{
				/*
				if (pExpr->left->tok.symbol == '::' && pExpr->left->left == NULL)
				{
				printf("");
				}
					*/
					Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
					
					if (left == NULL)
					{
						jerror("left expression = NULL in function call", pExpr->m_location);
					}
					else
					{
						//if (pExpr->
						
						if (left->m_pType)
						{
							Type* pType = left->m_pType->GetType();
							
							if (pType->GetKind() == type_pointer)
							{
								pType = pType->m_pPointerTo->GetType();
								/*
								if (pType->m_pPointerTo->GetKind() == type_function)
								{
								pType = pType->m_pPointerTo;
								}
								*/
							}
							
							if (pType->GetKind() == type_function)//m_pFunction)
							{
								Tr_Exp* tr = NULL;
								
								//						pExpr->m_pDeclarator = pDeclarator;
								
								T_Exp* pCall;
								
								int narg = 0;
								
								if (pType->m_pFunction->m_thiscall)
								{
									//	CExpression* pThis = new CExpression(pScope);
									//	pThis->
									
									Tr_Exp* leftob = TransExpression(frame, pExpr->left->left, pGlobal, pScope);
									Type* pType = new Type(type_pointer, sizeof_pointer);
									pType->m_pPointerTo = leftob->m_pType;
									leftob->m_pType = pType;
									
									tr = Tr_Ex(pCall = T_Call(unEx(left)));
									pCall->call.args = new ExpList(unEx(leftob)->mem, NULL);
									//	pCall->call.args->expr = pExpr->left;
									narg = 1;
								}
								else if (pType->m_pFunction->m_libcall.m_offset != 0)	// libcall
								{
									pExpr->m_pBaseDeclarator = pScope->GetDeclarator(pType->m_pFunction->m_libcall.m_basename.c_str());
									if (pExpr->m_pBaseDeclarator == NULL)
									{
										char msg[512];
										sprintf(msg, "undeclared libcall base '%s'", pType->m_pFunction->m_libcall.m_basename.c_str());
										jerror(msg, pExpr->m_location);
									}
									Temp_temp* temp = new Temp_temp;
									temp->m_an = 8+6;
									tr = Tr_Ex(
										T_ESeq(
										T_Move(T_Temp(temp), unEx(DeclaratorExpression(frame, pExpr->m_pBaseDeclarator->m_pDeclarator))),
										pCall = T_Call(T_Binop('+', T_Temp(temp), T_Const(pType->m_pFunction->m_libcall.m_offset)))
										)
										);
									
									//	pExpr->m_baseOffset = pDeclarator->m_libcall.m_offset;
								}
								else
								{
									//	pExpr->m_pDeclarator = pDeclarator;
									tr = Tr_Ex(pCall = T_Call(unEx(left)));
								}
								
								tr->m_pType = pType->m_pFunction->m_pReturnType;
								//int i = pExpr->m_pDeclarator->m_pFunction->m_parameters.size()-1;
								
								std::vector<CExpression*> args;
								{
									CExpression* pArgExpr = pExpr->right;
									while (pArgExpr)
									{
										ASSERT(pArgExpr->left != NULL);
										
										args.insert(args.begin(), pArgExpr);//->left);
										pArgExpr = pArgExpr->right;
									}
								}
								
								for (; narg < args.size(); narg++)
								{
									CDeclarator* pArgDecl;
									
									if (narg >= pType->m_pFunction->m_parameters.size())
									{
										if (!pType->m_pFunction->m_bVarArg)
										{
											jerror("too many arguments", pExpr->m_location);
											break;
										}
										pArgDecl = NULL;
									}
									else
									{
										pArgDecl = pType->m_pFunction->m_parameters[narg];
									}
									
									CExpression* pArgExpr = args[narg];
									
									Tr_Exp* p;
									
#if 0
									if (pType->m_pFunction->m_libcall.m_offset != 0 &&
										pType->m_pFunction->m_libcall.m_tagcall &&
										narg == pType->m_pFunction->m_parameters.size()-1)
									{
										Temp_temp* a7 = new Temp_temp;
										
										//continue;
										/*
										a7->m_an = 8+7;
										//	p = T_Unop('&', 
										
										  Temp_temp* tt = new Temp_temp;
										  tt->m_an = pArgDecl->m_libcall.m_reg-8;
										  
											 p = Tr_Ex(T_ESeq(T_Move(T_Temp(tt), T_Temp(a7)), T_Const(0)));
										*/
									}
									else
#endif
									{
										p = TransExpression(frame, pArgExpr->left, pGlobal, pScope);
									}
									
									if (p == NULL)
									{
										jerror("function argument failed", pExpr->m_location);
										return NULL;
									}
									
									if (p->m_pType)
									{
										if (pArgDecl)
										{
											pArgExpr->m_pDeclaratorRef = new CDeclaratorReference(pArgDecl);
											
											p = ConvertExpressionType(p, pArgDecl->m_pType);
											
											if (!p->m_pType->IsEqual(pArgDecl->m_pType))
											{
												StringA str0 = p->m_pType->toString();
												StringA str1 = pArgDecl->m_pType->toString();
												
												char msg[1024];
												sprintf(msg, "parameter %d: incompatible types - from '%s' to '%s'",
													//fstr.c_str(),//pExpr->left->tok.ident,
													narg+1,//pDeclarator->m_pFunction->m_parameters.size()-i,
													str0.c_str(), str1.c_str());
												jerror(msg, pExpr->m_location);
											}
										}
									}
									
									//pCall->call.args->expr = pArgExpr;
									
									if (pType->m_pFunction->m_libcall.m_offset != 0 &&
										pType->m_pFunction->m_libcall.m_tagcall &&
										narg == pType->m_pFunction->m_parameters.size()-1)
									{
										pCall->call.args = new ExpList(NULL, pCall->call.args);
										pCall->call.args->reg = - (pArgDecl->m_libcall.m_reg+1);
										
										pCall->call.args = new ExpList(unEx(p), pCall->call.args);
										
										//continue;
										/*
										a7->m_an = 8+7;
										//	p = T_Unop('&', 
										
										  Temp_temp* tt = new Temp_temp;
										  tt->m_an = pArgDecl->m_libcall.m_reg-8;
										  
											 p = Tr_Ex(T_ESeq(T_Move(T_Temp(tt), T_Temp(a7)), T_Const(0)));
										*/
									}
									else
									{
										pCall->call.args = new ExpList(unEx(p), pCall->call.args);
										
										if (pArgDecl)
											pCall->call.args->reg = pArgDecl->m_libcall.m_reg;
									}
						}
						
						if (narg < pType->m_pFunction->m_parameters.size())
						{
							char msg[256];
							if (pExpr->left->tok.type == CToken::tok_ident)
								sprintf(msg, "'%s' : too few parameters", pExpr->left->tok.ident);
							else
								sprintf(msg, "too few parameters");
							
							jerror(msg, pExpr->m_location);
						}
						
						return tr;
					}
					else
					{
						char msg[512];
						
						if (pExpr->left->tok.type == CToken::tok_ident)
							sprintf(msg, "'%s' : not a function", pExpr->left->tok.ident);
						else
							sprintf(msg, "not a function");
						
						jerror(msg, pExpr->m_location);
						
						return NULL;
					}
				}
				else
				{
					char msg[512];
					
					/*
					if (pExpr->left->tok.type == CToken::tok_ident)
					{
					sprintf(msg, "undeclared identifier '%s'", pExpr->left->tok.ident);
					}
					else if (pExpr->left->tok.type == CToken::tok_keyword)
					{
					sprintf(msg, "undeclared identifier '%s'", pExpr->left->tok.pkw->name);
					}
					else
					*/
					{
						sprintf(msg, "left side had no type");
					}
					
					jerror(msg, pExpr->m_location);
				}
			}
		}
	}
	break;
	
	case '->':	// Convert it to (*left).right
		{
#if 0
			pExpr->left = Reduce(pExpr->left, pScope);
			//	pExpr->right = Reduce(pExpr->right, pScope);
			
			//ExpressionType(pExpr->left, pScope);
			
			// First check for operator overloading
			
			if (pExpr->left->m_pType)
			{
				Type* pType = pExpr->left->m_pType->GetType();
				if (pType->GetKind() == type_templateinst)
				{
					printf("");
					pType = InstantiateTemplateType(pType->m_ArgTypes, pType);
					pExpr->left->m_pType = pType;
				}
				
				if (pType->GetKind() == type_class)
				{
					StringA fname = "operator_>-";
					
					CDeclaratorReference* pDeclaratorRef = pType->m_pClass->GetDeclarator(fname.c_str());
					if (pDeclaratorRef)
					{
						// An expression x->m is interpreted as (x.operator->())->m
						
						CExpression* pExpr2 = new CExpression(pScope);
						pExpr2->tok.type = CToken::tok_symbol;
						pExpr2->tok.symbol = '->';
						
						pExpr2->right = new CExpression(pScope);
						pExpr2->right->tok = pExpr->right->tok;
						
						pExpr2->left = new CExpression(pScope);
						pExpr2->left->tok.type = CToken::tok_symbol;
						pExpr2->left->tok.symbol = '(';
						
						pExpr2->left->left = new CExpression(pScope);
						pExpr2->left->left->tok.type = CToken::tok_symbol;
						pExpr2->left->left->tok.symbol = '.';
						
						pExpr2->left->left->left = new CExpression(pScope);
						pExpr2->left->left->left->tok = pExpr->left->tok;
						
						pExpr2->left->left->right = new CExpression(pScope);
						pExpr2->left->left->right->tok.type = CToken::tok_ident;
						pExpr2->left->left->right->tok.ident = "operator_>-";
						//	pExpr2->left->left->m_pDeclarator = pDeclarator;	// TODO
						
						//	pExpr->m_pDeclarator = pDeclarator;
						//	pExpr->m_pType = pDeclarator->m_pType;
						//return pExpr->m_pType;
						
						//Reduce(pExpr
						
						pExpr2 = Reduce(pExpr2, pScope);
						
						delete pExpr;
						pExpr = pExpr2;
						
						return pExpr;
					}
				}
			}
			else
			{
				printf("");
				pExpr->left = Reduce(pExpr->left, pScope);
			}
#endif
			
			CExpression* pExpr2 = ast::A_Binop('.',
				ast::A_Unop('*', pExpr->left),
				pExpr->right);
			
				/*
				CExpression* pDerefExpr = ast::A_Unop(((DWORD)'*'|('U'<<8)), pExpr->left);
				
				  new CExpression;
				  pDerefExpr->tok.type = CToken::tok_symbol;
				  pDerefExpr->tok.symbol = ((DWORD)'*'|('U'<<8));
				  pDerefExpr->right = pExpr->left;
				  
					 pExpr->left = pDerefExpr;
					 pExpr->tok.symbol = '.';
					 
			*/
			
			//	return pExpr;
			return TransExpression(frame, pExpr2, pGlobal, pScope);
		}
		break;
		
	case '.':
		{
			// object.member
			// node->left = object
			// node->right = member
			
			Tr_Exp* tleft = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (tleft == NULL)
				return NULL;
			
			if (tleft->m_pType)
			{
				if (tleft->m_pType->GetType()->GetKind() == type_templateinst)
				{
					ASSERT(0);
#if 0
					printf("");
					pExpr->left->m_pType = InstantiateTemplateType(pExpr->left->m_pType->GetType()->m_ArgTypes, pExpr->left->m_pType->GetType());
#endif
				}
			}
			
			Class* pClass = NULL;
			if (tleft->m_pType == NULL || (pClass = tleft->m_pType->GetClass()) == NULL)
			{
				if (tleft->m_pType)
				{
					StringA strtype = tleft->m_pType->toString();
					StringA strtypeun = tleft->m_pType->GetType()->toString();
					char msg[1024];
					sprintf(msg, "left of '.%s' must have class/struct/union type instead of: %s (%s)", pExpr->right->tok.ident, strtype.c_str(), strtypeun.c_str());
					jerror(msg, pExpr->m_location);
				}
				else
				{
					char msg[1024];
					sprintf(msg, "left of '.%s' must have class/struct/union type", pExpr->right->tok.ident);
					jerror(msg, pExpr->m_location);
				}
			}
			else
			{
				if (pExpr->right && pExpr->right->tok.type != CToken::tok_ident)
				{
					jerror("Expected member name", pExpr->m_location);
				}
				else if (pClass->m_sizeof == -1)
				{
					char msg[1024];
					sprintf(msg, "use of incomplete struct '%s'", pClass->m_name.c_str());
					jerror(msg, pExpr->m_location);
				}
				else
				{
					if (pExpr->right->m_pDeclaratorRef == NULL)
						pExpr->right->m_pDeclaratorRef = pClass->GetDeclarator(pExpr->right->tok.ident);
					
					if (pExpr->right->m_pDeclaratorRef == NULL)
					{
						ASSERT(tleft->m_pType->GetType()->GetKind() == type_class);
						
						char msg[1024];
						sprintf(msg, "'%s' : is not a member of '%s'",
							pExpr->right->tok.ident,
							tleft->m_pType->GetType()->m_pNamedType->m_name.c_str());
						
						jerror(msg, pExpr->m_location);
					}
					else
					{
						if (pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pOwnerScope->m_pClass != pClass)
						{
							ASSERT(0);
#if 0
							// Cast left expression
							CExpression* pExpr2 = new CExpression(pScope);
							pExpr2->tok.type = CToken::tok_symbol;
							pExpr2->tok.symbol = (DWORD)'('|('U'<<8);
							pExpr2->m_pType = new Type(type_class);
							//pExpr2->m_pType->m_pPointerTo = new Type(type_class);
							pExpr2->m_pType->m_pClass = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pOwnerScope->m_pClass;
							
							pExpr2->right = pExpr->left;
							
							pExpr2 = Reduce(pExpr2, pScope);	// hm.. right gets reduced twice
							
							pExpr->left = pExpr2;
							
							pExpr->m_pDeclaratorRef = pExpr->right->m_pDeclaratorRef;
							pExpr->m_pType = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pType->Clone();
							
							//	pExpr2->right = pExpr;
							
							
							//	pExpr2->right = pExpr;
							//	pExpr = pExpr2;
#endif
						}
						else
						{
							T_Exp* left = unEx(tleft);
							
							ASSERT(left->kind == T_Exp::T_MEM);
							left = left->mem;
							
							CDeclarator* pRightDeclarator = pExpr->right->m_pDeclaratorRef->m_pDeclarator;
							
							if (pRightDeclarator->m_pType->GetType()->GetKind() == type_function)
							{
								CDeclarator* pDeclarator = pRightDeclarator;
								
								ASSERT(0);
#if 0
								FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
								ImageReloc->VirtualAddress = 0;//ftell(fileout);	// Address into the .text section
								ImageReloc->SymbolTableIndex = pDeclarator->m_symbolIndex;
								//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
								ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
#endif
		
								ASSERT(0);
								T_Exp* pConst = T_Const(0/*pDeclarator->m_spOffset*/);
#if 0
								pConst->const_int.reloc = ImageReloc;
#endif
								Tr_Exp* pT = Tr_Ex(T_Mem(pConst, pDeclarator->m_pType->get_sizeof()));
								
								pT->m_pType = pDeclarator->m_pType;
								
								return pT;//MessageBeep(-1);
								//return Tr_Exp(T_
							}
							
							Tr_Exp* tr;
							
#if 0
							if (left->kind == T_Exp::T_BINOP &&
								left->binop.right->kind == T_Exp::T_CONST)
							{
								ASSERT(left->binop.op == '+');
								
								left->binop.right->const_int.int32Val += pRightDeclarator->m_spOffset;
								tr = Tr_Ex(T_Mem(left, pRightDeclarator->m_pType->GetType()->get_sizeof()));
							}
							else
#endif
							{
								ASSERT(0);
								tr = Tr_Ex(
									T_Mem(
									T_Binop('+', left, T_Const(0/*pRightDeclarator->m_spOffset*/)), pRightDeclarator->m_pType->GetType()->get_sizeof()));
							}
							
							//	Tr_Exp* tr = Tr_Ex(
							//		T_Binop('+', unEx(left), T_Const(pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_spOffset)));
							
							/*
							if (tr->ex->mem->binop.left->kind == T_Exp::T_MEM)
							{
							tr->ex->mem->binop.right->const_int.int32Val += tr->ex->mem->binop.left->mem->const_int.int32Val;
							tr->ex->mem->binop.left = tr->ex->mem->binop.left->mem;
							//if (tr->ex->mem->binop.left
							//	tr->ex->mem->binop.right->const_int.int32Val += tr->
							}
							*/
							/*
							if (tr->ex->kind == T_Exp::T_MEM &&
							tr->ex->mem->kind == T_Exp::T_BINOP &&
							tr->ex->mem->binop.op == '+' &&
							tr->ex->mem->binop.right->kind == T_Exp::T_CONST)
							{
							if (tr->ex->mem->binop.left
							//	tr->ex->mem->binop.right->const_int.int32Val += tr->
							}
							*/
							
							pExpr->m_pDeclaratorRef = pExpr->right->m_pDeclaratorRef;
							tr->m_pType = pExpr->right->m_pDeclaratorRef->m_pDeclarator->m_pType->Clone();
							
							return tr;
						}
				}
			}
		}
	}
	break;
	
	case '.*':
		{
		/*
		The binary operator .* binds its second operand, which shall be of type “pointer to member of T” (where
		T is a completely-defined class type) to its first operand, which shall be of class T or of a class of which T
		is an unambiguous and accessible base class. The result is an object or a function of the type specified by
		the second operand.
			*/
			//		pExpr->right
			ASSERT(0);
			return NULL;
		}
		break;
		
	case '->*':
		{
			ASSERT(0);
			return NULL;
		}
		break;
		
	case ((DWORD)'*'|('U'<<8)):	// Dereference right node
		{
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			if (right == NULL)
				return NULL;
			
			if (right->m_pType == NULL)
			{
				jerror("no type", pExpr->m_location);
			}
			else
			{
				Type* pType = right->m_pType->GetType();
				
				if (pType->GetKind() == type_pointer)
				{
					ASSERT(pType->m_arrayDims.size() == 0);
					pType = pType->m_pPointerTo;
				}
				else if (pType->GetKind() == type_array)
				{
					ASSERT(pType->m_arrayDims.size() > 0);
					pType = pType->m_pPointerTo;
				}
				else
				{
					jerror("illegal indirection", pExpr->m_location);
					//	return NULL;
				}
				
				Tr_Exp* pTExpr;
				pTExpr = Tr_Ex(T_Mem(unEx(right), pType->get_sizeof()));
				pTExpr->m_pType = pType;
				
				return pTExpr;
			}
		}
		break;
		
	case '[':
		{
			// TODO, check operators
			// ??
			/*
			pExpr->left = Reduce(pExpr->left, pScope);
			pExpr->right = Reduce(pExpr->right, pScope);
			*/
			
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (left == NULL)
			{
				return NULL;
			}
			else
			{
				T_Exp* leftx = unEx(left);
				ASSERT(leftx->kind == T_Exp::T_MEM);
				
				int _sizeof = left->m_pType->m_pPointerTo->get_sizeof();
				
				CExpression* r = ast::A_Binop('*',
					pExpr->right,
					ast::A_Const(_sizeof)
					);
				
				r = Reduce2(r, pScope);
				
				Tr_Exp* right = TransExpression(frame, r, pGlobal, pScope);
				
				Tr_Exp* tr = Tr_Ex(T_Mem(T_Binop('+', leftx->mem, unEx(right)), _sizeof));
				tr->m_pType = left->m_pType->m_pPointerTo;
				return tr;
				/*
				CExpression* pExpr2 = ast::A_Unop('*',
				ast::A_Binop('+',
				pExpr->left,
				ast::A_Binop('*',
				pExpr->right,
				ast::A_Const(_sizeof)
				)
				)
				);
				*/
				
				//	pExpr2 = Reduce2(pExpr2, pScope);
				//	return TransExpression(pExpr2, pGlobal, pScope);
				/*
				Tr_Exp* tr = Tr_Ex(
				T_Mem(
				T_Binop('+',
				leftx->mem,
				T_Binop('*',
				unEx(right),
				T_Const(_sizeof)
				)
				),
				_sizeof
				)
				);
				*/
				//	tr->m_pType = left->m_pType->m_pPointerTo;
				
				//	return tr;
			}
			
#if 0
			CExpression* pExpr2 = new CExpression(pScope);
			pExpr2->tok.type = CToken::tok_symbol;
			pExpr2->tok.symbol = (DWORD)'*'|('U'<<8);
			
			pExpr2->right = new CExpression(pScope);
			pExpr2->right->tok.type = CToken::tok_symbol;
			pExpr2->right->tok.symbol = '+';
			pExpr2->right->left = pExpr->left;
			pExpr2->right->right = pExpr->right;
			
			pExpr = Reduce(pExpr2, pScope);
			
			ASSERT(pExpr->m_pType);
			
			// TODO
			//pExpr->m_pType = pExpr->left->m_pType->m_pPointerTo;
			
			/*
			Type* pType = new Type;
			
			  pExpr->m_pType = new Type;
			  pExpr->m_pType->GetKind() = type_pointer;
			  pExpr->m_pType->m_sizeof = sizeof(char*);
			  
				 pExpr->m_pType->m_pPointerTo = new Type;
				 pExpr->m_pType->m_pPointerTo->GetKind() = type_char;
				 pExpr->m_pType->m_pPointerTo->m_sizeof = 1;
				 pExpr->m_pType->m_pPointerTo->m_bConst = true;
			*/
#endif
		}
		break;
		
	case ((DWORD)'&'|('U'<<8)):	// address-of right node
		{
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			
			if (right->ex->kind == T_Exp::T_MEM)
			{
				Tr_Exp* pTExpr = Tr_Ex(right->ex->mem);
				pTExpr->m_pType = new Type(type_pointer, sizeof_pointer);
				pTExpr->m_pType->m_pPointerTo = right->m_pType;
				pTExpr->m_pType->m_lvalue = false;	// & produces an r-value
				
				return pTExpr;
			}
			else if (right->ex->kind == T_Exp::T_CONST)
			{
				jerror("'&' on constant", pExpr->m_location);
			}
			else
			{
				ASSERT(0);
			}
#if 0
			pExpr->right = Reduce(pExpr->right, pScope);
			if (pExpr->right->m_pType)
			{
				if (!pExpr->right->m_pType->m_lvalue)
				{
					pPP->jerror("'&' requires l-value");
				}
				
				pExpr->m_pType = new Type(type_pointer, sizeof_pointer);
				pExpr->m_pType->m_pPointerTo = pExpr->right->m_pType;
				pExpr->m_pType->m_lvalue = false;	// & produces an r-value
			}
			else
			{
				pPP->jerror("unknown expression type");
			}
			
			//	return pExpr->m_pType;
#endif
		}
		break;
		
#if 0
		else if (pExpr->tok.type == CToken::tok_symbol && (pExpr->tok.symbol == ((DWORD)'!'|('U'<<8))))	// ! (unary)
		{
			//ASSERT(pExpr->m_pType != NULL);
			ASSERT(pExpr->left == NULL);
			
			pExpr->right = Reduce(pExpr->right, pScope);
			
			pExpr->m_pType = pExpr->right->m_pType;	// ????
		}
#endif
	case (DWORD)'('|('U'<<8):	// cast
		{
			ASSERT(pExpr->cast.m_pType != NULL);
			ASSERT(pExpr->left == NULL);
			
			if (pExpr->right)
			{
				Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
				if (right == NULL)
					return NULL;
				
				right->m_pType = pExpr->cast.m_pType;
				
				return right;
#if 0
				Type* pType0 = pExpr->m_pType->GetType();
				Type* pType1 = pExpr->right->m_pType->GetType();
				if (pType0->GetKind() == type_pointer && pType1->GetKind() == type_pointer)
				{
					pType0 = pType0->m_pPointerTo->GetType();
					pType1 = pType1->m_pPointerTo->GetType();
				}
				
				if (pType0->GetKind() == type_class && pType1->GetKind() == type_class)
				{
					int offset = pType1->m_pClass->GetOffset(pType0->m_pClass);
					if (offset != -1)
					{
						CExpression* pExpr2 = new CExpression(pScope);
						pExpr2->tok.type = CToken::tok_symbol;
						pExpr2->tok.symbol = '+';
						
						pExpr2->left = pExpr->right;
						
						pExpr2->right = new CExpression(pScope);
						pExpr2->right->tok.type = CToken::tok_integer;
						pExpr2->right->tok.int32 = offset;
						
						pExpr2->right = Reduce(pExpr2->right, pScope);
						
						pExpr2->m_pType = pExpr->m_pType;
						
						pExpr = pExpr2;
					}
					//	printf("");
					//	Get
				}
#endif		
			}
			else
			{
				jerror("no right expression in cast expression", pExpr->m_location);
			}
		}
		break;
		
	case '+=':
	case '-=':
	case '*=':
	case '/=':
	case '%=':
	case '|=':
	case '&=':
	case '^=':
	case '>>=':
	case '<<=':
		{
			CExpression* pExpr2 = new CExpression;
			pExpr2->tok.type = CToken::tok_symbol;
			pExpr2->tok.symbol = '=';
			
			pExpr2->left = pExpr->left;
			
			pExpr2->right = new CExpression;
			pExpr2->right->tok.type = CToken::tok_symbol;
			
			if (pExpr->tok.symbol == '+=')
			{
				pExpr2->right->tok.symbol = '+';
			}
			else if (pExpr->tok.symbol == '-=')
			{
				pExpr2->right->tok.symbol = '-';
			}
			else if (pExpr->tok.symbol == '*=')
			{
				pExpr2->right->tok.symbol = '*';
			}
			else if (pExpr->tok.symbol == '/=')
			{
				pExpr2->right->tok.symbol = '/';
			}
			else if (pExpr->tok.symbol == '%=')
			{
				pExpr2->right->tok.symbol = '%';
			}
			else if (pExpr->tok.symbol == '<<=')
			{
				pExpr2->right->tok.symbol = '<<';
			}
			else if (pExpr->tok.symbol == '>>=')
			{
				pExpr2->right->tok.symbol = '>>';
			}
			else if (pExpr->tok.symbol == '|=')
			{
				pExpr2->right->tok.symbol = '|';
			}
			else if (pExpr->tok.symbol == '&=')
			{
				pExpr2->right->tok.symbol = '&';
			}
			else
				ASSERT(0);
			
			pExpr2->right->right = pExpr->right;
			pExpr2->right->left = pExpr->left;	// Okay to use exact same copy ??
			
			//pExpr = pExpr2;
			
			return TransExpression(frame, pExpr2, pGlobal, pScope);
		}
		break;
		
	case '=':
		{
#if 0	// ??
			//if (pExpr->right->tok.type == CToken::tok_symbol && pExpr->right->tok.symbol == 
			if (pDeclarator->m_pInitializerExpr != NULL)
			{
				initialize(pDeclarator, pDeclarator->m_pInitializerExpr, pCompoundStmt);
			}
#endif
			
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (left == NULL)
			{
				jerror("error in left side of '=' expression", pExpr->m_location);
			}
			else
			{
				
#if 0
				if (pExpr->left->m_pType)
				{
					if (!pExpr->left->m_pType->m_lvalue)
					{
#if 0	// TODO
						pPP->jerror("'=' requires l-value on left side");
#endif
					}
				}
#endif
				
				if (pExpr->right == NULL)
				{
					jerror("error in right side of '=' expression", pExpr->m_location);
				}
				else
				{
					Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
					if (right == NULL)
					{
						jerror("error in right side of '=' expression", pExpr->m_location);
						
						//	ExpressionType(pExpr->right, pScope);
					}
					else
					{
						right = ConvertExpressionType(right, left->m_pType);
						
						if (!right->m_pType->IsEqual(left->m_pType))
						{
#if 0
							// Try operator= overloads
							Type* pType = pExpr->left->m_pType->GetType();
							
							if (pType->GetKind() == type_class)
							{
								for (int i = 0; i < pType->m_pClass->m_pScope->m_orderedDecls.size(); i++)
								{
									CDeclaratorReference* pDeclaratorRef = pType->m_pClass->m_pScope->m_orderedDecls[i];
									if (pDeclaratorRef->m_pDeclarator->m_name == "operator_=")
									{
										if (pDeclaratorRef->m_pDeclarator->m_pType->GetType()->m_pFunction->m_parameters.size() == 1)
										{
											CDeclarator* pParamDeclarator = pDeclaratorRef->m_pDeclarator->m_pType->GetType()->m_pFunction->m_parameters[0];
											//	std::string str0 = pParamDeclarator->m_pType->toString();
											//	printf("operator=(%s)\n", str0.c_str());
											
											/*
											CExpression* pExprRight = new CExpression(pScope);
											pExprRight->m_pType = pExpr->right->m_pType->Clone();
											pExprRight->tok.type = pExpr->right->tok.type;
											pExprRight->tok.int32 = pExpr->right->tok.int32;
											*/
											
											StringA str0 = pExpr->right->m_pType->toString();
											StringA str1 = pParamDeclarator->m_pType->toString();
											
											pExpr->right = ConvertExpressionType(pExpr->right, pParamDeclarator->m_pType);
											
											if (pExpr->right->m_pType->IsEqual(pParamDeclarator->m_pType))
											{
												std::string str = pExpr->right->m_pType->toString();
												
												CExpression* pExpr2 = new CExpression(pScope);
												pExpr2->tok.type = CToken::tok_symbol;
												pExpr2->tok.symbol = '(';
												
												pExpr2->left = new CExpression(pScope);
												pExpr2->left->tok.type = CToken::tok_symbol;
												pExpr2->left->tok.symbol = '.';
												
												pExpr2->left->left = pExpr->left;
												pExpr2->left->right = new CExpression(pScope);
												pExpr2->left->right->tok.type = CToken::tok_ident;
												pExpr2->left->right->tok.ident = strdup("operator_=");
												pExpr2->left->right->m_pDeclaratorRef = pDeclaratorRef;
												
												// function argument
												
												pExpr2->right = new CExpression(pScope);
												pExpr2->right->left = pExpr->right;
												
												delete pExpr;
												pExpr = pExpr2;
												
												pExpr = Reduce(pExpr, pScope);
												return pExpr;
											}
											/*
											else
											{
											
											  char msg[512];
											  sprintf(msg, "cannot convert %s to %s", str0.c_str(), str1.c_str());
											  pPP->jerror(msg);
											  }
											*/
										}
									}
								}
							}
#endif
						}
						
						if (!right->m_pType->IsEqual(left->m_pType))
						{
							//ConvertExpressionType(pExpr->right, pExpr->left->m_pType);
							
							StringA str0 = right->m_pType->toString();
							StringA str1 = left->m_pType->toString();
							
							//	std::string fstr = pExpr->m_pDeclarator->toString();
							
							char msg[1024];
							sprintf(msg, "incompatible types - from '%s' to '%s'",
								//	fstr.c_str(),//pExpr->left->tok.ident,
								//	i+1,//pDeclarator->m_pFunction->m_parameters.size()-i,
								str0.c_str(), str1.c_str());
							jerror(msg, pExpr->m_location);
							
							/*
							printf("***\n");
							printoutall(pExpr->left->m_pType);
							printf("***\n");
							*/
							return NULL;
						}
						else
						{
							Tr_Exp* p = Tr_Nx(T_Move(left->ex, unEx(right)));
							p->m_pType = left->m_pType;
							return p;
						}
					}
				}
			}
		}
		break;
	
	case '^':
	case '|':
	case '&':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '<<':
	case '>>':
		{
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			
			if (left->m_pType && right->m_pType)
			{
				Tr_Exp* tr = Tr_Ex(T_Binop(pExpr->tok.symbol, unEx(left), unEx(right)));
				
				if ((pExpr->tok.symbol == '-') && (
					left->m_pType->GetType()->GetKind() == type_pointer &&
					right->m_pType->GetType()->GetKind() == type_pointer))
				{
					tr->m_pType = new Type(type_int, 4);
				}
				else if ((pExpr->tok.symbol == '+') && (
					left->m_pType->GetType()->GetKind() == type_pointer &&
					right->m_pType->GetType()->GetKind() == type_int))
				{
					tr->m_pType = left->m_pType;
				}
				else if ((pExpr->tok.symbol == '+') && (
					left->m_pType->GetType()->GetKind() == type_int &&
					right->m_pType->GetType()->GetKind() == type_pointer))
				{
					tr->m_pType = right->m_pType;
				}
				else
				{
					// TODO, check for compatibility
					tr->m_pType = left->m_pType;
				}
				
				return tr;
			}
			else
			{
				jerror("error in expressions", pExpr->m_location);
			}
		}
		break;
		
	case '==':
	case '!=':
	case '>':
	case '<':
	case '>=':
	case '<=':
		{
			Tr_Exp* left = TransExpression(frame, pExpr->left, pGlobal, pScope);
			if (left == NULL)
				return NULL;
			
			Tr_Exp* right = TransExpression(frame, pExpr->right, pGlobal, pScope);
			if (right == NULL)
				return right;
			
			//	Temp_label* z = new Temp_label;
			T_Stm* s1 = /*T_Seq(*/T_CJump(pExpr->tok.symbol, unEx(left), unEx(right), NULL, NULL);/*,
									T_Label(z));*/
			
			Tr_Exp* tr = Tr_Cx(new patchList(&s1->cjump.t, NULL), new patchList(&s1->cjump.f, NULL), s1);
			
			//	ASSERT(s1->cjump.t);
			//	ASSERT(s1->cjump.f);
			
			tr->m_pType = new Type(type_bool);
			
			return tr;
#if 0
			pExpr->left = Reduce(pExpr->left, pScope);
			
			if (pExpr->right)
			{
				pExpr->right = Reduce(pExpr->right, pScope);
				
				if (pExpr->left->m_pType && pExpr->right->m_pType)
				{
					pExpr->m_pType = new Type(type_bool);
				}
				else
				{
					if (pExpr->left->m_pType == NULL)
						pPP->jerror("left side of expr had no type");
					
					if (pExpr->right->m_pType == NULL)
						pPP->jerror("right side of expr had no type");
				}
			}
			else
			{
				pPP->jerror("error in right side of expression");
			}
#endif
		}
		break;
		
#if 0
		else if (pExpr->tok.type == CToken::tok_symbol && pExpr->tok.symbol == '?')
		{
			// TODO pExpr->right->left->m_pType IsCompatible pExpr->right->right->m_pType
			if (pExpr->left == NULL)
			{
				pPP->jerror("left=NULL in ?: expression");
			}
			else
			{
				pExpr->left = Reduce(pExpr->left, pScope);
				pExpr->right->left = Reduce(pExpr->right->left, pScope);
				pExpr->right->right = Reduce(pExpr->right->right, pScope);
				
				// TODO, this is just a quick hack (if one of them is a pointer type, choose that one)
				if (pExpr->right->left->m_pType->GetType()->GetKind() == type_pointer)
				{
					pExpr->m_pType = pExpr->right->left->m_pType;
				}
				else
				{
					pExpr->m_pType = pExpr->right->right->m_pType;
				}
			}
		}
#endif
		
	case 'U-':
	case 'U!':
		{
			ASSERT(pExpr->left == NULL);
			ASSERT(pExpr->right != NULL);

			Tr_Exp* tre = TransExpression(frame, pExpr->right, pGlobal, pScope);
			if (tre == NULL)
				return NULL;

			Tr_Exp* tr = Tr_Ex(T_Unop(pExpr->tok.symbol, unEx(tre)));

			return tr;
		}
		break;
		
		default:
			ASSERT(0);
		}
	}
#endif

	return NULL;
	//return pExpr;
}

Tr_Exp* ConvertExpressionType(Tr_Exp* pExpr, Type* p2Type, bool b2Const)
{
	ASSERT(pExpr);

	/*
	// not sure..
	if (pExpr->m_pType == NULL)
	{
		pExpr->m_pType = p2Type;
		return pExpr;
	}
	else if (p2Type == NULL)
	{
		return pExpr;
	}
	*/

	ASSERT(p2Type != NULL);
	ASSERT(pExpr->m_pType != NULL);

	if (p2Type->get_Kind() == type_typedef)
	{
		return ConvertExpressionType(pExpr, ((Typedef*)p2Type)->/*m_pDeclarator->*/m_pType);
	}

	// ??
	if (p2Type->get_Kind() == type_cv)
	{
		if (((_CVType*)p2Type)->m_bConst) b2Const = true;
		return ConvertExpressionType(pExpr, p2Type->GetPointerTo(), b2Const);
	}

//#if 0	// TODO, have this
	while (pExpr->m_pType->get_Kind() == type_typedef || pExpr->m_pType->get_Kind() == type_cv)
	{
		if (pExpr->m_pType->get_Kind() == type_typedef)
			pExpr->m_pType = ((Typedef*)pExpr->m_pType)->/*m_pDeclarator->*/m_pType;
		else
			pExpr->m_pType = pExpr->m_pType->GetPointerTo();
	}
//#endif

#if 0
	// lvalue-to-rvalue conversion,
//	if (!p2Type->m_lvalue)
	{
		ASSERT(0);
		if (pExpr->m_pType->m_lvalue)
		{
			pExpr->m_pType->m_lvalue = 0;
		}
	}
#endif

#if 0
	ASSERT(0);
	// TODO: Move m_lvalue to Tr_Exp ?
	ASSERT(!pExpr->m_pType->m_lvalue);	// r-value
#endif

// vector-to-pointer conversion
	if (p2Type->get_Kind() == type_pointer)
	{
		if (pExpr->m_pType->get_Kind() == type_array)
		{
			Type* pType = new PointerType(((ArrayType*)pExpr->m_pType)->m_pElemType);
			//pType->m_pPointerTo = ;

			ASSERT(pExpr->ex->kind == T_Exp::T_MEM);
			pExpr = Tr_Ex(pExpr->ex->mem.mem);

		//	if (p2Type->m_pPointerTo->IsEqual(pExpr->m_pType->m_pType))
			{

				pExpr->m_pType = pType;
			}
		}
	}

	// integral promotion

	bool bPromoted = false;

	if (p2Type->get_Kind() == type_short || p2Type->get_Kind() == type_unsigned_short)
	{
		if (pExpr->m_pType->get_Kind() == type_bool ||
			pExpr->m_pType->get_Kind() == type_char ||
			pExpr->m_pType->get_Kind() == type_signed_char ||
			pExpr->m_pType->get_Kind() == type_unsigned_char)
		{
			if (p2Type->get_Kind() == type_short)
			{
				Tr_Exp* tr = Tr_Ex(T_UnopExp('se', unEx(pExpr)));
				tr->ex->m_size = p2Type->get_sizeof();
				tr->m_pType = p2Type;
				return tr;
			}
			else
			{
				Tr_Exp* tr = Tr_Ex(T_UnopExp('ze', unEx(pExpr)));
				tr->ex->m_size = p2Type->get_sizeof();
				tr->m_pType = p2Type;
				return tr;
			}
		}
	}
	if (p2Type->get_Kind() == type_int || p2Type->get_Kind() == type_unsigned_int)
	{
		if (pExpr->m_pType->get_Kind() == type_bool ||
			pExpr->m_pType->get_Kind() == type_char ||
			pExpr->m_pType->get_Kind() == type_signed_char ||
			pExpr->m_pType->get_Kind() == type_unsigned_char ||
			pExpr->m_pType->get_Kind() == type_short ||
			pExpr->m_pType->get_Kind() == type_unsigned_short)
		{
			if (p2Type->get_Kind() == type_int)
			{
				Tr_Exp* tr = Tr_Ex(T_UnopExp('se', unEx(pExpr)));
				tr->ex->m_size = p2Type->get_sizeof();
				tr->m_pType = p2Type;
				return tr;
			}
			else
			{
				Tr_Exp* tr = Tr_Ex(T_UnopExp('ze', unEx(pExpr)));
				tr->ex->m_size = p2Type->get_sizeof();
				tr->m_pType = p2Type;
				return tr;
			}
#if 0
			Tr_Exp* pExpr2 = new CExpression(pExpr->m_pScope);
			pExpr2->tok.type = CToken::tok_symbol;
			pExpr2->tok.symbol = (DWORD)'('|('U'<<8);
			pExpr2->right = pExpr;
			pExpr2->m_pType = p2Type;

			pExpr = pExpr2;
			//pExpr->m_pType = new Type(p2Type->GetKind(), p2Type->m_sizeof);
			/*
			pExpr->m_pType->GetKind() = p2Type->GetKind();
			pExpr->m_pType->m_sizeof = p2Type->m_sizeof;
			*/
#endif
			bPromoted = true;
		}
	}
	else if (p2Type->get_Kind() == type_long_long || p2Type->get_Kind() == type_unsigned_long_long)
	{
		if (pExpr->m_pType->get_Kind() == type_char ||
			pExpr->m_pType->get_Kind() == type_signed_char ||
			pExpr->m_pType->get_Kind() == type_unsigned_char ||
			pExpr->m_pType->get_Kind() == type_short ||
			pExpr->m_pType->get_Kind() == type_unsigned_short ||

			pExpr->m_pType->get_Kind() == type_int ||
			pExpr->m_pType->get_Kind() == type_unsigned_int)
		{
			if (p2Type->get_Kind() == type_long_long)
			{
				if (pExpr->kind == Tr_Exp::Tr_ex && pExpr->ex->kind == T_Exp::T_CONST)
				{
					pExpr->ex->m_size = p2Type->get_sizeof();
					//pExpr->ex->const_int.int32Val = (__int64)pExpr->ex->const_int.int32Val;
					pExpr->m_pType = p2Type;
					return pExpr;
				}
				else
				{
					Tr_Exp* tr = Tr_Ex(T_UnopExp('se', unEx(pExpr)));
					tr->ex->m_size = p2Type->get_sizeof();
					tr->m_pType = p2Type;
					return tr;
				}
			}
			else
			{
				Tr_Exp* tr = Tr_Ex(T_UnopExp('ze', unEx(pExpr)));
				tr->ex->m_size = p2Type->get_sizeof();
				tr->m_pType = p2Type;
				return tr;
			}

			//pExpr->m_pType = p2Type;
#if 0
			pExpr->m_pType->GetKind() = p2Type->GetKind();
			pExpr->m_pType->m_sizeof = p2Type->m_sizeof;
#endif
			bPromoted = true;
		}
	}

	// bool -> int
	if (p2Type->get_Kind() == type_int)
	{
		if (pExpr->m_pType->get_Kind() == type_bool)
		{
			pExpr->m_pType = p2Type;
#if 0
			pExpr->m_pType->GetKind() = type_int;
			pExpr->m_pType->m_sizeof = 4;
#endif
			bPromoted = true;
		}
	}

	if (!bPromoted)
	{
		// integral conversion
		if (p2Type->get_Kind() == type_char ||
			p2Type->get_Kind() == type_signed_char ||
			p2Type->get_Kind() == type_unsigned_char ||
			p2Type->get_Kind() == type_short ||
			p2Type->get_Kind() == type_long ||
			p2Type->get_Kind() == type_int ||
			p2Type->get_Kind() == type_unsigned_short ||
			p2Type->get_Kind() == type_unsigned_long ||
			p2Type->get_Kind() == type_unsigned_int)
		{
			if (pExpr->m_pType->get_Kind() == type_char ||
				pExpr->m_pType->get_Kind() == type_signed_char ||
				pExpr->m_pType->get_Kind() == type_unsigned_char ||
				pExpr->m_pType->get_Kind() == type_short ||
				pExpr->m_pType->get_Kind() == type_long ||
				pExpr->m_pType->get_Kind() == type_int ||
				pExpr->m_pType->get_Kind() == type_unsigned_short ||
				pExpr->m_pType->get_Kind() == type_unsigned_long ||
				pExpr->m_pType->get_Kind() == type_unsigned_int ||
				pExpr->m_pType->get_Kind() == type_long_long ||
				pExpr->m_pType->get_Kind() == type_unsigned_long_long)
			{
				if (p2Type->get_Kind() != pExpr->m_pType->get_Kind())
				{
					// truncate

					if (pExpr->kind == Tr_Exp::Tr_ex && pExpr->ex->kind == T_Exp::T_CONST)
					{
						pExpr->ex->m_size = p2Type->get_sizeof();
						pExpr->m_pType = p2Type;
						return pExpr;
					}
					else
					{
						Tr_Exp* tr = Tr_Ex(T_UnopExp('trun', unEx(pExpr)));
						tr->m_pType = p2Type;
						tr->ex->m_size = tr->m_pType->get_sizeof();
						return tr;
					}
				}

			//	pExpr->m_pType = p2Type;
#if 0
				CExpression* pExpr2 = new CExpression(pExpr->m_pScope);
				pExpr2->tok.type = CToken::tok_symbol;
				pExpr2->tok.symbol = (DWORD)'('|('U'<<8);
				pExpr2->right = pExpr;
				pExpr2->m_pType = p2Type;

				pExpr = pExpr2;
#endif
				/*
				pExpr->m_pType = new Type(p2Type->GetKind(), p2Type->m_sizeof);
			//	pExpr->m_pType->GetKind() = p2Type->GetKind();
			//	pExpr->m_pType->m_sizeof = p2Type->m_sizeof;
				pExpr->m_pType->m_bConst = p2Type->m_bConst;
				*/
			}
		}
		else if (p2Type->get_Kind() == type_bool)
		{
			if (pExpr->m_pType->get_Kind() == type_int)
			{
				printf("forcing value to bool 'true' or 'false' (performance warning)\n");//, pExpr->m_location);

				Cx cx = unCx(pExpr);

				/*
				T_Stm* s = T_CJumpStm('!=', unEx(pExpr), T_ConstExp(0), NULL, NULL);
				*/
				Tr_Exp* texp = Tr_Cx(cx.trues, cx.falses, cx.stm);
				texp->m_pType = &Types::type_bool;

				return texp;

			//	pExpr->m_pType->GetKind() = type_bool;
			//	pExpr->m_pType->m_sizeof = 1;
			}
		}
	}

	// pointer conversions

	// null-pointer
	if (p2Type->get_Kind() == type_pointer)
	{
		if (pExpr->m_pType->get_Kind() == type_int)
		{
			ASSERT(pExpr->kind == Tr_Exp::Tr_ex);
			ASSERT(pExpr->ex->kind == T_Exp::T_CONST);

			if (pExpr->ex->const_int.int32Val == 0)
			{
				pExpr->m_pType = new PointerType(p2Type->GetPointerTo());
#if 0
				pExpr->m_pType->GetKind() = type_pointer;
				pExpr->m_pType->m_pPointerTo = p2Type->m_pPointerTo->Clone();
				pExpr->m_pType->m_sizeof = sizeof_pointer;
#endif
			}
		}
	}

	// T* -> void*
	if (p2Type->get_Kind() == type_pointer && p2Type->GetPointerTo() != NULL && p2Type->GetPointerTo()->get_Kind() == type_void)
	{
		if (pExpr->m_pType->get_Kind() == type_pointer)
		{
			const Type* pPointerTo = pExpr->m_pType->GetPointerTo()->GetStripped();

			if (pPointerTo->get_Kind() != type_void)	// Already the same
			{
				((PointerType*)pExpr->m_pType)->m_pPointerTo = Types::get_void();
				//pExpr->m_pType = p2Type;
//				ASSERT(0);
#if 0
				/*
				if (pExpr->m_pType->m_pPointerTo->m_pClass)
				{
					delete pExpr->m_pType->m_pPointerTo->m_pClass;
					pExpr->m_pType->m_pPointerTo->m_pClass = NULL;
				}
				pExpr->m_pType->m_pPointerTo->GetKind() = type_void;
				pExpr->m_pType->m_pPointerTo->m_sizeof = -1;
				*/

				CExpression* pExpr2 = new CExpression(pExpr->m_pScope);
				pExpr2->tok.type = CToken::tok_symbol;
				pExpr2->tok.symbol = (DWORD)'('|('U'<<8);
				pExpr2->right = pExpr;
				pExpr2->m_pType = p2Type;

				if (p2Type->m_bConst != b2Const)
				{
					printf("");
				}

				pExpr = pExpr2;

				/*
				pExpr->m_pType = new Type(type_pointer);
				pExpr->m_pType->m_sizeof = sizeof(void*);
				pExpr->m_pType->m_pPointerTo = new Type(type_void);
				pExpr->m_pType->m_pPointerTo->m_sizeof = -1;
				*/

#if 0	// TODO, have this
				pExpr->m_pType->m_pPointerTo = new Type(type_void);
				pExpr->m_pType->m_pPointerTo->m_sizeof = -1;
#endif
#endif
			}
		}
	}

	// qualifications conversion
	if (p2Type->get_Kind() == type_pointer && pExpr->m_pType->get_Kind() == type_pointer)
	{
		if (p2Type->GetPointerTo()->IsConst())
		{
			((PointerType*)pExpr->m_pType)->m_pPointerTo = pExpr->m_pType->GetPointerTo()->Clone();
	//		ASSERT(0);
#if 0
			((PointerType*)pExpr->m_pType)->m_pPointerTo->m_bConst = true;
#endif
		}

		if (p2Type->GetPointerTo()->IsVolatile())
		{
			((PointerType*)pExpr->m_pType)->m_pPointerTo = pExpr->m_pType->GetPointerTo()->Clone();
			ASSERT(0);
#if 0
			pExpr->m_pType->GetPointerTo()->m_bVolatile = true;
#endif
		}

#if 0
		if (p2Type->m_pPointerTo->IsEqual(pExpr->m_pType->m_pPointerTo))//, FALSE/*bCheckQualification*/))
		{
		}
#endif
	}

	return pExpr;
}

void SetLineNumber(T_Stm* stm, int ln);

void SetLineNumber(T_Exp* exp, int ln)
{
	if (exp->kind == T_Exp::T_ESEQ)
	{
		SetLineNumber(exp->eseq.s, ln);
		SetLineNumber(exp->eseq.e, ln);
	}
	else if (exp->kind == T_Exp::T_BINOP)
	{
		SetLineNumber(exp->binop.left, ln);
		SetLineNumber(exp->binop.right, ln);
	}
}

void SetLineNumber(T_Stm* stm, int ln)
{
	if (stm->m_line_pos == -1)
	{
		stm->m_line_pos = ln;

		if (stm->kind == T_Stm::T_SEQ)
		{
//			SetLineNumber(stm->seq.left, ln);
//			SetLineNumber(stm->seq.right, stm->seq.left->m_line_pos);
		}
		else if (stm->kind == T_Stm::T_CJUMP)
		{
		//	SetLineNumber(stm->cjump.left, ln);
		//	SetLineNumber(stm->cjump.right, ln);
		}
		else if (stm->kind == T_Stm::T_JUMP)
		{
		//	SetLineNumber(stm->jump.exp, ln);
		}
		else if (stm->kind == T_Stm::T_EXP)
		{
			SetLineNumber(stm->exp, ln);
		}
	}
}

T_Stm* TransStatement(T_Declarator* frame, ast::A_Stm* stm, Scope* pScope, CGlobal* pGlobal, CTSwitch* pInnermostSwitch, Temp_label* break_target)
{
	if (stm == NULL)
	{
		return T_ExpStm(T_ConstExp(0));
	}

	switch (stm->GetKind())
	{
	case ast::A_Stm::A_IF:
		{
			ast::IfStm* ifstm = (ast::IfStm*)stm;

			ast::Condition* cond = (ast::Condition*)ifstm->m_cond;

			Tr_Exp* test = TransExpression(frame, cond->m_exp, pGlobal, pScope);
			if (test == NULL)
				return NULL;

			Cx cx = unCx(test);

			Temp_label* t = new Temp_label;//cx.stm->cjump.t;
			Temp_label* f = new Temp_label;//cx.stm->cjump.f;
			Temp_label* endif = new Temp_label;

			PatchTrue(cx.trues, t);
			PatchFalse(cx.falses, f);

			Scope* pIfScope = new Scope;
			pIfScope->m_pParentScope = pScope;

			T_Stm* tsub = TransStatement(frame, ifstm->m_stm, pIfScope, pGlobal, pInnermostSwitch, break_target);

			T_Stm* telse = TransStatement(frame, ifstm->m_elseStm, pIfScope, pGlobal, pInnermostSwitch, break_target);

			T_Stm* ts = T_Seq(cx.stm,
								T_Seq(
									T_Label(t),
										T_Seq(tsub,
											T_Seq(T_JumpStm(T_Name(endif), new Temp_labelList(endif, NULL)),
												T_Seq(T_Label(f),
													T_Seq(telse,
														T_Seq(T_JumpStm(T_Name(endif), new Temp_labelList(endif, NULL)),
															T_Label(endif))))))));

		//	cx.stm->m_line_pos = cond->m_exp->m_line_pos;
		//	ts->m_line_pos = cond->m_exp->m_line_pos;
			SetLineNumber(cx.stm, cond->m_exp->m_line_pos);
			//SetLineNumber(ts, cond->m_exp->m_line_pos);

//			ts->seq->right->m_line_pos = ts->m_line_pos;
//			ts->seq->right->right->m_line_pos = ts->m_line_pos;

			return ts;
		}
		break;

	case ast::A_Stm::A_DOWHILE:
		{
			ast::DoWhileStm* dowhilestm = (ast::DoWhileStm*)stm;

			Tr_Exp* test = TransExpression(frame, (ast::Expression*)dowhilestm->m_exp, pGlobal, pScope);
			if (test == NULL)
				return NULL;

			Cx cx = unCx(test);

			Temp_label* t = new Temp_label;
			Temp_label* f = new Temp_label;
			//Temp_label* endif = new Temp_label;

			PatchTrue(cx.trues, t);
			PatchFalse(cx.falses, f);

			T_Stm* tsub = TransStatement(frame, dowhilestm->m_stm, pScope, pGlobal, pInnermostSwitch, f);

			T_Stm* ts = T_Seq(T_Label(t),
								T_Seq(tsub,
									T_Seq(cx.stm,
										T_Label(f))));

			SetLineNumber(cx.stm, ((ast::Expression*)dowhilestm->m_exp)->m_line_pos);

			return ts;
		}
		break;

	case ast::A_Stm::A_WHILE:
		{
			ast::WhileStm* whilestm = static_cast<ast::WhileStm*>(stm);

			ast::Condition* cond = (ast::Condition*)whilestm->m_cond;

			Tr_Exp* test = TransExpression(frame, cond->m_exp, pGlobal, pScope);
			if (test == NULL)
				return NULL;

			Cx cx = unCx(test);

			Temp_label* top = new Temp_label;
			Temp_label* t = new Temp_label;
			Temp_label* f = new Temp_label;

			PatchTrue(cx.trues, t);
			PatchFalse(cx.falses, f);

			T_Stm* tsub = TransStatement(frame, whilestm->m_stm, pScope, pGlobal, pInnermostSwitch, f);

			T_Stm* ts = T_Seq(T_Label(top),
								T_Seq(cx.stm,
									T_Seq(T_Label(t),
										T_Seq(tsub,
											T_Seq(T_JumpStm(T_Name(top), new Temp_labelList(top, NULL), whilestm->m_last_line),
												T_Label(f, whilestm->m_last_line))))));

			SetLineNumber(cx.stm, cond->m_exp->m_line_pos);

			return ts;
		}
		break;

	case ast::A_Stm::A_FOR:
		{
			ast::ForStm* forstm = (ast::ForStm*)stm;

			// TODO init

			ASSERT(((ast::A_ExpOrDecl*)forstm->m_init)->m_exp);

			Tr_Exp* init = TransExpression(frame, ((ast::A_ExpOrDecl*)forstm->m_init)->m_exp, pGlobal, pScope);
			if (init == NULL)
				return NULL;

			Tr_Exp* test = TransExpression(frame, (ast::Expression*)forstm->m_cond, pGlobal, pScope);
			if (test == NULL)
				return NULL;

			Tr_Exp* adv = TransExpression(frame, (ast::Expression*)forstm->m_exp, pGlobal, pScope);
			if (adv == NULL)
				return NULL;

			Cx cx = unCx(test);

			Temp_label* top = new Temp_label;
			Temp_label* contlabel = new Temp_label;
			Temp_label* t = new Temp_label;
			Temp_label* f = new Temp_label;

			PatchTrue(cx.trues, t);
			PatchFalse(cx.falses, f);

			T_Stm* tsub = TransStatement(frame, forstm->m_stm, pScope, pGlobal, pInnermostSwitch, f);

			T_Stm* ts = T_Seq(unNx(init),
								T_Seq(T_Label(top),
									T_Seq(cx.stm,
										T_Seq(T_Label(t),
											T_Seq(tsub,
												T_Seq(T_Label(contlabel),
													T_Seq(unNx(adv),
														T_Seq(T_JumpStm(T_Name(top), new Temp_labelList(top, NULL)),
															T_Label(f, forstm->m_last_line)))))))));

			SetLineNumber(cx.stm, forstm->m_line_pos);

			return ts;
		}
		break;

	case ast::A_Stm::A_RETURN:
		{
			printf("ast::A_RETURN TODO\n");
		//	ASSERT(0);
		}
		break;

	case ast::A_Stm::A_BREAK:
		{
			// TODO
			ASSERT(0);
		}
		break;

	case ast::A_Stm::A_CONTINUE:
		{
			// TODO
			ASSERT(0);
		}
		break;

	case ast::A_Stm::A_GOTO:
		{
			ast::GotoStm* gotostm = (ast::GotoStm*)stm;

			LabelRef*& labelref = frame->m_labels[gotostm->m_name];
			if (labelref == NULL)
			{
				labelref = new LabelRef;
				labelref->m_label = new Temp_label;
			}

			T_Stm* stm = T_JumpStm(T_Name(labelref->m_label), new Temp_labelList(labelref->m_label, NULL));

			return stm;
		}
		break;

	case ast::A_Stm::A_LABEL:
		{
			ast::LabelStm* labelstm = (ast::LabelStm*)stm;

			LabelRef*& labelref = frame->m_labels[labelstm->m_name];
			if (labelref == NULL)
			{
				labelref = new LabelRef;
				labelref->m_label = new Temp_label;
			}

			T_Stm* stm = TransStatement(frame, labelstm->m_stm, pScope, pGlobal, pInnermostSwitch, break_target);

			return T_Seq(T_Label(labelref->m_label), stm);
		}
		break;

	case ast::A_Stm::A_DECLARATION:
		{
			ast::A_DeclarationStm* declstm = (ast::A_DeclarationStm*)stm;

			if (declstm->m_declaration)
			{
				if (declstm->m_declaration->GetKind() == ast::Declaration::A_SIMPLE)
				{
					CDeclaratorList* declaratorList = ast::SimpleDeclaration((ast::A_SimpleDeclaration*)declstm->m_declaration, pGlobal, pScope, pScope, frame->m_pDeclarator, NULL, NULL, -1/*linkage*/, false);

					T_Declarator* declarator = new T_Declarator;
					declarator->m_pDeclarator = declaratorList->head;

					return T_LSym(declarator);
				}
				else if (declstm->m_declaration->GetKind() == ast::Declaration::A_ASM)
				{
					ast::AsmDefinition* asmdef = dynamic_cast<ast::AsmDefinition*>(declstm->m_declaration);

#if WIN32
					m68kasm::Parse(asmdef->m_str);
#else
					ASSERT(0);
#endif
				}
				else
					ASSERT(0);
			}
			else
			{
				MessageBeep(-1);	// TODO: ASSERT(0);
			}
			return NULL;//T_Expr(T_Const(0));
		}
		break;

	case ast::A_Stm::A_COMPOUND:
		{
			ast::CompoundStm* compoundstm = static_cast<ast::CompoundStm*>(stm);

			Scope* pScope2 = new Scope;
			pScope2->m_pParentScope = pScope;

			ast::A_StmList* slist = compoundstm->m_stmList;

			T_Stm* pStmt = T_LBrac();
		//	for (int i = 0; i < pDeclarator->m_pDeclarator->m_pBody->m_statements.size(); i++)
			while (slist)
			{
				T_Stm* p = TransStatement(frame, slist->head, /*pDeclarator->m_pDeclarator->m_pBody->m_*/pScope2, pGlobal, NULL/*pInnermostSwitch*/, NULL/*break_target*/);
				if (p)
				{
					if (pStmt)
						pStmt = T_Seq(pStmt, p);
					else
						pStmt = p;
				}

				slist = slist->tail;
			}

			pStmt = T_Seq(pStmt, T_RBrac());

			return pStmt;
		}
		break;

	case ast::A_Stm::A_EXP:
		{
			ast::A_ExpStm* expstm = (ast::A_ExpStm*)stm;

			Tr_Exp* tr = TransExpression(frame, expstm->m_exp, pGlobal, pScope);

			if (tr == NULL)
				return NULL;

			T_Stm* t = unNx(tr);
			SetLineNumber(t, expstm->m_exp->m_line_pos);

			return t;
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

#if 0
T_Stm* CCompileFile::TransStatement(T_Declarator* frame, CStatement* pstmt, cpp::Scope* pScope, cpp::CGlobal* pGlobal, CTSwitch* pInnermostSwitch, Temp_label* break_target)
{
	ASSERT(pstmt);

	switch (pstmt->GetKind())
	{
		case cpp::CStatement::STMT_RETURN:
		{
			cpp::CReturnStatement* preturnstmt = (cpp::CReturnStatement*)pstmt;

			if (preturnstmt->m_expr)
			{
				Temp_temp* temp = new Temp_temp;
				temp->m_dn = 0;	// d0

				// TODO, jump to epilogue
				preturnstmt->m_expr = Reduce2(preturnstmt->m_expr, pScope);
				return T_Seq(
							T_Move(T_Temp(temp), unEx(TransExpression(frame, preturnstmt->m_expr, pGlobal, pScope))),
							T_Jump(T_Name(frame->epilogue_label)));
			}
			else
			{
				return T_Jump(T_Name(frame->epilogue_label));
			}

	#if 0
			{
				// huh ???
				CLabel* else_label = new CLabel;
				m_labelStack.push(else_label);

				if (emit_expr(pFunc, preturnstmt->m_expr, &ea(0,0)/*d0*/) == 2)
				{
				//	emit_op(JOP_iconst_1);
				//	emit_op(JOP_goto);
				//	fput16(fileout, 0);

				//	branch_to();
				//	emit_op(JOP_iconst_0);
				}

				//putc(0xC3, fileout);	// RET (near return)

			// Jump to epilogue
				if (m_processor_id == 1)
				{
				}
				else	// x86
				{
					putc(0xEB, fileout);	// jmp short
					putc(0, fileout);	// 8-bit offset
				}
			}
			else
			{
				if (m_processor_id == 1)
				{
				}
				else	// x86
				{
					putc(0xC3, fileout);	// RET (near return)
				}
			}
	#endif
		}
		break;

		case cpp::CStatement::STMT_IF:
		{
			cpp::CIfStatement* pIfStmt = (cpp::CIfStatement*)pstmt;
			pIfStmt->m_testexpr = Reduce2(pIfStmt->m_testexpr, pScope);

			Tr_Exp* ttest = TransExpression(frame, pIfStmt->m_testexpr, pGlobal, pIfStmt->m_pIfScope);
			if (ttest == NULL)
				return NULL;

			Cx cx = unCx(ttest);

			ASSERT(cx.stm->kind == T_Stm::T_CJUMP);

			Temp_label* t = new Temp_label;//cx.stm->cjump.t;
			Temp_label* f = new Temp_label;//cx.stm->cjump.f;
			Temp_label* endif = new Temp_label;

			doPatch(cx.trues, t);
			doPatch(cx.falses, f);

			T_Stm* tsub = TransStatement(frame, pIfStmt->m_substmt, pIfStmt->m_pIfScope, pGlobal, pInnermostSwitch, break_target);

			if (tsub == NULL)
				tsub = T_Expr(T_Const(0));

			T_Stm* telse = NULL;

			if (pIfStmt->m_elsestmt)
				telse = TransStatement(frame, pIfStmt->m_elsestmt, pIfStmt->m_pIfScope, pGlobal, pInnermostSwitch, break_target);

			if (telse == NULL)
				telse = T_Expr(T_Const(0));

			T_Stm* ts = T_Seq(cx.stm, T_Seq(
											T_Label(t),	T_Seq(
											tsub, T_Seq(
											T_Jump(T_Name(endif)), T_Seq(
											T_Label(f), T_Seq(
											telse, T_Label(endif)))))));

			return ts;

	#if 0
			CLabel* else_label = new CLabel;
			m_labelStack.push(else_label);
			if (emit_expr(pFunc, pIfStmt->m_testexpr, NULL) != 2)
			{
				printf("Expected boolean expression\n");
			}
			m_labelStack.pop();
			WriteStatement(pFunc, pIfStmt->m_substmt);

			CLabel* end_label = new CLabel;
			((CCodeGen68*)this)->bcc(0);	// unconditional branch
			end_label->m_branches.push_back(ftell(fileout));
			fput16(fileout, 0);
			
			else_label->m_pos = GetCounter();
			FlushLabel(else_label);

			if (pIfStmt->m_elsestmt)
			{
				WriteStatement(pFunc, pIfStmt->m_elsestmt);
			}
			end_label->m_pos = GetCounter();
			FlushLabel(end_label);
	#endif
		}
		break;

		case cpp::CStatement::STMT_WHILE:
		{
			cpp::CWhileStatement* pWhileStmt = (cpp::CWhileStatement*)pstmt;

			pWhileStmt->m_testexpr = Reduce2(pWhileStmt->m_testexpr, pScope);
			Tr_Exp* ttest = TransExpression(frame, pWhileStmt->m_testexpr, pGlobal, pScope);

			Cx cx = unCx(ttest);

			Temp_label* while_label = new Temp_label;
			Temp_label* while_label2 = new Temp_label;
			Temp_label* wend_label = new Temp_label;

			T_Stm* stm = TransStatement(frame, pWhileStmt->m_substmt, pScope/*TODO pWhileStmt->pScope*/, pGlobal, pInnermostSwitch, wend_label);

			doPatch(cx.trues, while_label2);
			doPatch(cx.falses, wend_label);

			T_Stm* s = T_Seq(T_Label(while_label), T_Seq(
											cx.stm, T_Seq(
											T_Label(while_label2), T_Seq(
											stm, T_Seq(
											T_Jump(T_Name(while_label)),
											T_Label(wend_label))))));

			return s;

	#if 0
			CLabel* pWhileLabel = new CLabel;
			pWhileLabel->m_pos = GetCounter();

			CLabel* pEndLabel = new CLabel;
			m_labelStack.push(pEndLabel);
			if (emit_expr(pFunc, pWhileStmt->m_testexpr, NULL) != 2)
			{
				printf("Expected boolean expression\n");
			}
			WriteStatement(pFunc, pWhileStmt->m_substmt);

			((CCodeGen68*)this)->bcc(0);	// unconditional branch
			fput16(fileout, (int)pWhileLabel->m_pos - (int)GetCounter());

			pEndLabel->m_pos = GetCounter();
			FlushLabel(pEndLabel);
			m_labelStack.pop();
			delete pEndLabel;
	#endif
	#if 0
			((CCodeGen68*)this)->bcc(0);	// unconditional branch
			end_label->m_branches.push_back(ftell(fileout));
			fput16(fileout, 0);
			
			set_label(else_label);

			if (pIfStmt->m_elsestmt)
			{
			//	branch();
				WriteStatement(pFunc, pIfStmt->m_elsestmt);
			//	branch_to();
			}
			set_label(end_label);
	#endif
		}
		break;

		case cpp::CStatement::STMT_EXPRESSION:
		{
			cpp::CExpressionStatement* pExprStmt = (cpp::CExpressionStatement*)pstmt;

			ASSERT(pExprStmt->m_pExpr);

			pExprStmt->m_pExpr = Reduce2(pExprStmt->m_pExpr, pScope);
			
			Tr_Exp* tr = TransExpression(frame, pExprStmt->m_pExpr, pGlobal, pScope);
			if (tr == NULL)
				return NULL;

			return unNx(tr);
		}
		break;

		case cpp::CStatement::STMT_COMPOUND:
		{
			cpp::CCompoundStatement* pCompoundStmt = (cpp::CCompoundStatement*)pstmt;


		//	pFunc->m_spOffset = pCompoundStmt->m_pBlock->m_pScope->m_spOffset;

			T_Stm* pT = NULL;
			for (int i = 0; i < pCompoundStmt->m_pBlock->m_statements.size(); i++)
			{
				T_Stm* stm = TransStatement(frame, pCompoundStmt->m_pBlock->m_statements[i], pCompoundStmt->m_pBlock->m_pScope, pGlobal, pInnermostSwitch, break_target);

			//	WriteStatement(pFunc, pCompoundStmt->m_pBlock->m_statements[i]);
				if (stm)
				{
					if (pT == NULL)
						pT = stm;
					else
						pT = T_Seq(pT, stm);
				}
			}

			return pT;
			//pFunc->m_spOffset += 
		}
		break;

		case cpp::CStatement::STMT_ZERO:
		{
			cpp::CZeroStatement* pZeroStmt = (cpp::CZeroStatement*)pstmt;

			T_Stm* s = new T_Stm;
			s->kind = T_Stm::T_ZERO;
			s->zero.m_spOffset = pZeroStmt->m_spOffset;
			s->zero.m_length = pZeroStmt->m_length;

			return s;
		}
		break;

	case cpp::CStatement::STMT_SWITCH:
		{
			cpp::CSwitchStatement* pSwitchStmt = (cpp::CSwitchStatement*)pstmt;

			pSwitchStmt->m_testexpr = Reduce2(pSwitchStmt->m_testexpr, pScope);
			Tr_Exp* ttest = TransExpression(frame, pSwitchStmt->m_testexpr, pGlobal, pScope);
		// Evaluate ttest to int
			ttest = ConvertExpressionType(ttest, new Type(type_int, 4));

			Temp_label* switch_end_label = new Temp_label;

		//	T_Expr(Tr_Cx(ttest

			// Evaluate the condition once
			Temp_temp* condition_temp = new Temp_temp;
			T_Stm* init_stm = T_Move(T_Temp(condition_temp), unEx(ttest));

			CTSwitch tswitch;
			T_Stm* stm = TransStatement(frame, pSwitchStmt->m_statement, pScope, pGlobal, &tswitch, switch_end_label);

			ASSERT(stm);

			if (tswitch.default_stm)
			{
				stm = T_Seq(T_Jump(T_Name(tswitch.default_stm->label)), stm);
			}
			else
			{
				stm = T_Seq(T_Jump(T_Name(switch_end_label)), stm);
			}

			CTCaseList* tcase = tswitch.tcaseList;
			while (tcase)
			{
				Temp_label* t = tcase->head->label;//new Temp_label;
				Temp_label* f = new Temp_label;	// TODO

				// currently reversed true and false

				stm = T_Seq(T_CJump('!=',
												T_Temp(condition_temp), T_Const(tcase->head->m_value),
												f/*t*/, t/*f*/), stm);

//				T_Label(t);
				//s = T_Seq(ts, s);

				tcase = tcase->tail;
			}

			//stm = T_Seq(stm, stm2);

			return T_Seq(
				init_stm, T_Seq(
				stm,
				T_Label(switch_end_label)));
		}
		break;

	case cpp::CStatement::STMT_CASE:
		{
			cpp::CCaseStatement* pCaseStmt = (cpp::CCaseStatement*)pstmt;

			//T_Exp* 
			if (pInnermostSwitch == NULL)
			{
				jerror("Illegal case", pstmt->m_location);
				return NULL;
			}
			else
			{
				CTCase* pCase = new CTCase;
				pCase->label = new Temp_label;

				T_Stm* s = TransStatement(frame, pCaseStmt->m_statement, pScope, pGlobal, pInnermostSwitch, break_target);
				if (s == NULL)
					return NULL;

				pCase->stm = T_Seq(
					T_Label(pCase->label),
					s);

				pCase->m_value = pCaseStmt->m_value;

				pInnermostSwitch->tcaseList = new CTCaseList(pCase, pInnermostSwitch->tcaseList);
				return pCase->stm;
			}
		}
		break;

	case cpp::CStatement::STMT_DEFAULT:
		{
			cpp::CLabelStatement* pLabelStmt = (cpp::CLabelStatement*)pstmt;

			if (pInnermostSwitch == NULL)
			{
				jerror("Illegal default", pstmt->m_location);
				return NULL;
			}
			else
			{
				if (pInnermostSwitch->default_stm != NULL)
				{
					jerror("default label already specified", pstmt->m_location);
				}
				else
				{
					pInnermostSwitch->default_stm = new CTLabelStatement;
					pInnermostSwitch->default_stm->label = new Temp_label;

					pInnermostSwitch->default_stm->stm = T_Seq(
						T_Label(pInnermostSwitch->default_stm->label),
						TransStatement(frame, pLabelStmt->m_statement, pScope, pGlobal, pInnermostSwitch, break_target));

					return pInnermostSwitch->default_stm->stm;
				}
			}
		}
		break;

	case cpp::CStatement::STMT_BREAK:
		{
			if (break_target == NULL)
			{
				jerror("illegal break", pstmt->m_location);
				return NULL;
			}
			else
				return T_Jump(T_Name(break_target));
		}
		break;

	default:
		ASSERT(0);
	}

	ASSERT(0);
	return NULL;
}
#endif

}	// cpp
}	// System
