#include "StdAfx.h"
#include "Comp2.h"
#include "LFC/disasm.h"
#include "cpp_ast.h"
#include "cpp_compile.h"
#include "cpp_translate.h"
#include "codegen.h"
#include "codegen_m68k.h"
//#include "../CodeComp/codegen_x86.h"

#include "codegen_ppc.h"

#include "preprocessor.h"

//#include "link.h"

#include "AOutWrite.h"
#include "COFFWrite.h"

#include <algorithm>

using namespace std;

//#include "../LFC/db.h"

//#include "../include/windows_types.h"

namespace System
{

//void printClass(ClassType* pClass, int levels);

	namespace MSWindows
	{

extern "C"
WINBASEAPI
DWORD
WINAPI
GetTickCount(
    void
    );
	}
}

namespace System
{

//extern "C" void test(int x);

//T_Stm* T_Label(Temp_label* label);

//using namespace cpp;

kwmap kwm;

namespace cpp
{
extern _Ptr<IO::TextWriter> m_outputStream;
extern _Ptr<IO::TextWriter> Log;

namespace ast
{
#include "cpp_parse.tab.h"
int cpp_parse ();

extern YYLTYPE cpp_exp_lloc;
}

int pp_parse ();

}

//namespace compile
//{

//void emit(AS_instr* inst);

// Liveness module


//

//extern "C" int yylex();

//}

struct yy_buffer_state;

yy_buffer_state* pp2__scan_string(const char* str);
void pp2__switch_to_buffer(yy_buffer_state*);
int pp2_lex();

extern "C" int pp2_wrap()
{
	return 1;	// terminate lex scanner
}

extern "C" int cpp_wrap()
{
	return 1;	// terminate lex scanner
}

extern FILE* pp2_in;

PP::CPreprocessor* pPP2;

void pp_error (char const *s)
{
	fprintf (stderr, "%s\n", s);
}

namespace cpp
{

	namespace ast
	{
void cpp_error (char const *s)
{
/*
	PP::macromap::iterator macro = pPP2->m_defines.find("__RPC_USER");	// RPC_ENTRY
	if (macro != pPP2->m_defines.end())
	{
		PP::CDefine* p = (*macro).second;
		p;
	}	
*/

//	TRACE("%s(%d): ", CString(pPP2->m_pFile->m_filepath), pPP2->m_pFile->m_line+1);
//	TRACE("%s\n", s);

	printf("\n");
	printf("%s(%d): ", CString(pPP2->m_pFile->m_filepath), pPP2->m_pFile->m_line+1);
	printf("%s\n", s);
}
	}

namespace ast
{
extern DeclarationList* translation_unit;
}

//_Type* GetType(ast::A_DeclSpecList* declspecList, CGlobal* pGlobal, Scope* pScope);
T_Stm* TransStatement(T_Declarator* frame, ast::A_Stm* pstmt, Scope* pScope, CGlobal* pGlobal, CTSwitch* pInnermostSwitch, Temp_label* break_target);
//CDeclaratorList* SimpleDeclaration(ast::A_SimpleDeclaration* d, CGlobal* pGlobal, Scope* pScope, ClassType* pInnermostClass, ast::A_TemplateParameterList * tp, bool bInsideTemplate);

#if 0
void CompoundStm(ast::A_StmList* stmList, cpp::CGlobal* pGlobal, cpp::Scope* pScope)
{
	ast::A_StmList* slist = stmList;

	while (slist)
	{
		ast::A_Stm* stm = slist->head;

		switch (stm->kind)
		{
		case ast::A_Stm::ast::A_EXP_OR_DECLARATION:
			{
				ASSERT(0);
				printf("exp_or_declaration\n");
			}
			break;

		case ast::A_Stm::ast::A_DECLARATION:
			{
				printf("declaration\n");
				if (stm->declaration->kind == ast::A_Declaration::ast::A_SIMPLE)
				{
					SimpleDeclaration(stm->declaration, pGlobal, pScope, NULL);
				}
				else
					ASSERT(0);
			}
			break;

		case ast::A_Stm::ast::A_EXP:
			{
				printf("exp\n");
			}
			break;

		case ast::A_Stm::ast::A_COMPOUND:
			{
				cpp::Scope* pScope2 = new cpp::Scope;
				pScope2->m_pParentScope = pScope;
				CompoundStm(stm->compound, pGlobal, pScope2);
			}
			break;

		default:
			ASSERT(0);
		}

		slist = slist->tail;
	}
}
#endif

#if 0
void FunBody(cpp::CGlobalast::A_StmList* stmList)
{
	cpp::Scope* pScope = new cpp::Scope;
	CompoundStm(stmList, pScope);
}
#endif

/*
void Save(const PrimitiveType & object)
{
	stream << (uint8)pType->m_type;
}
*/

/*
void Save(const _Type & object, ByteIOStream & stream )
{

	switch (pType->m_type)
	{
	case type_pointer:
		{
			PointerType* pPointerType = (PointerType*)pType;
			map<void*,uint32>::iterator it = objectmap.find(pPointerType->m_pPointerTo);
			if (it != objectmap.end())
			{
				stream << (*it).second;
			}
			else
			{
				objectmap.insert(map<void*,uint32>::value_type((void*)pPointerType, objectmap.size());
				Save(pPointerType->m_pPointerTo, stream);
			}

		}
		break;
	}
}
*/

/*
void Save(const PointerType & object, ByteIOStream & stream)
{

}

void Load(ByteIOStream & stream)
{
}
*/

namespace ast
{
CodeCompExt void Translate(Declaration* d, CGlobal* pGlobal, Scope* pScope, int linkage);
//CodeCompExt Stream& Write(Stream& stream, DeclarationList* declarationList);

CodeCompExt A_ExpOrDecl* PrimList(Expression2List* primlist, Scope* pGlobalScope, Scope* pScope);
Expression2List* flatten_and_reverse(Expression2List* primlist, ast::Expression2List* prev);

extern Expression2List* g_primlist;
extern Expression2List* ptoken;
}

//Type* GetType(ast::A_DeclSpec* declspecList, CGlobal* pGlobal, Scope* pScope);
//Type* GetType(ast::A_DeclSpecList* declspecList, CGlobal* pGlobal, Scope* pScope, ast::A_TemplateParameterList * tp, bool bInsideTemplate/*, Type** templateArgs*/);

vector<T_Declarator*> tglobals;

void AddKeyword(StringIn name, int kw)
{
	kwm.insert(kwmap::value_type(name, kw));
}

namespace ast
{
CGlobal* g_pGlobal;

extern System::Scope* g_pScope;
extern System::Scope* g_pScope2;
//extern System::Scope* g_pScope1;
//extern Scope* g_pLastScope;

extern stack<Scope*> g_scopeStack;
extern stack<Scope*> g_scopeStack2;

CodeCompExt int cpp_exp_parse();

struct yy_buffer_state;

CodeCompExt yy_buffer_state* cpp2__scan_string(const char* str);
CodeCompExt void cpp2_switch_to_buffer(yy_buffer_state*);
CodeCompExt int cpp2_lex();

CodeCompExt int cpp_exp_parse();

Expression* g_exp;
bool is_parse_exp;
bool use_cpp_lex;

CodeCompExt Expression* parse_expression(StringIn str)
{
	is_parse_exp = true;
	use_cpp_lex = true;

	CGlobal* pGlobal = new cpp::CGlobal;
	pGlobal->m_namespace = new Namespace;
	Scope* pGlobalScope = pGlobal->m_namespace->m_pScope;

	ast::g_pGlobal = pGlobal;

	ast::g_pScope = pGlobalScope;
	ast::g_pScope2 = pGlobalScope;

	ast::g_scopeStack.cont.clear();
	ast::g_scopeStack2.cont.clear();

	ast::g_scopeStack.push(pGlobalScope);

//
	yy_buffer_state* state = cpp::ast::cpp2__scan_string(CString(str));
	g_exp = NULL;
	int error = cpp_exp_parse();

	return g_exp;
}

CodeCompExt Expression* parse_expression(CGlobal* pGlobal, StringIn str)
{
	is_parse_exp = true;
	use_cpp_lex = true;

	ASSERT(pGlobal->m_namespace);
	Scope* pGlobalScope = pGlobal->m_namespace->m_pScope;

	ast::g_pGlobal = pGlobal;

	ast::g_pScope = pGlobalScope;
	ast::g_pScope2 = pGlobalScope;

	ast::g_scopeStack.cont.clear();
	ast::g_scopeStack2.cont.clear();

	ast::g_scopeStack.push(pGlobalScope);

//
	yy_buffer_state* state = cpp::ast::cpp2__scan_string(CString(str));
	g_exp = NULL;
	int error = cpp_exp_parse();

	return g_exp;
}

CodeCompExt DeclarationList* parse_translation_unit(CGlobal* pGlobal, StringIn str)
{
	if (m_outputStream == NULL)
	{
		m_outputStream = Std::get_Out();
	}

	is_parse_exp = false;
	use_cpp_lex = true;

	ASSERT(pGlobal->m_namespace);
	Scope* pGlobalScope = pGlobal->m_namespace->m_pScope;

	ast::g_pGlobal = pGlobal;

	ast::g_pScope = pGlobalScope;
	ast::g_pScope2 = pGlobalScope;

	ast::g_scopeStack.cont.clear();
	ast::g_scopeStack2.cont.clear();

	ast::g_scopeStack.push(pGlobalScope);

//
	yy_buffer_state* state = cpp::ast::cpp2__scan_string(CString(str));
	translation_unit = NULL;

	{
		YYLTYPE yyltype;
		yyltype.filename = NULL;
		ast::ptoken = new ast::Expression2List(new ast::Expression2(yyltype, ast::DECLS_TOKEN), NULL);

		// This is all a little weird, and needs to be changed, but since I do some symbol sematic stuff in initial pass, need some hacking

		CGlobal* pGlobal = new CGlobal;
		pGlobal->m_namespace = new Namespace;
		Scope* pGlobalScope = pGlobal->m_namespace->m_pScope;

		ast::g_pGlobal = pGlobal;

		ast::g_pScope = pGlobalScope;
		ast::g_pScope2 = pGlobalScope;
		ast::g_scopeStack.push(pGlobalScope);

		int error = cpp_exp_parse();

		translation_unit = Reverse(translation_unit);
	}

	int default_alignment = 8;

	pGlobal->m_packstack.push(default_alignment);
	ast::Translate(translation_unit, pGlobal, pGlobalScope, nullptr, 1/*C++*/);

	return translation_unit;
}

}

CGlobal::CGlobal() :
	m_sizeofptr(4)
{
}

Declarator* FindVirtualMethodInBases(ClassType* pClass, StringIn methodName, StringIn fullName);
ClassType* InstantiateTemplate(Scope* pOwnerScope, CGlobal* pGlobal, /*Templated*/ClassType* pTemplateClass, const TemplateArgs * pParent);
CodeCompExt void CalcClass(CGlobal* pGlobal, ClassType* pClass, unsigned int alignment);

Declarator* FindVirtualMethod(ClassType* pClass, StringIn methodName, StringIn fullName)
{
	declsmap::iterator it = pClass->m_pScope->m_decls.find(methodName);
	while (it != pClass->m_pScope->m_decls.end() && (it->first == methodName))
	{
		if (it->second->m_pType->get_Kind() == type_function)
		{
			if (it->second->m_virtual)
			{
				IO::StringWriter strbuilder;
				it->second->WriteFunctionIdentity(strbuilder);

				if (strbuilder.str() == fullName)
				{
					it->second->m_pOwnerScope = pClass->m_pScope;	// TODO, not here
					return it->second;
				}
			}
		}

		++it;
	}

	return FindVirtualMethodInBases(pClass, methodName, fullName);
}

Declarator* FindVirtualMethodInBases(ClassType* pClass, StringIn methodName, StringIn fullName)
{
	for (ucount_t i = 0; i < pClass->m_bases.size(); ++i)
	{
		Declarator* pDecl = FindVirtualMethod(pClass->m_bases[i]->m_pClass->AsClass(), methodName, fullName);
		if (pDecl) return pDecl;
	}

	return nullptr;
}

Declarator* FindVirtualMethodInPrimaryBase(ClassType* pClass, StringIn methodName, StringIn fullName);

Declarator* FindVirtualMethodInPrimary(ClassType* pClass, StringIn methodName, StringIn fullName)
{
	declsmap::iterator it = pClass->m_pScope->m_decls.find(methodName);
	while (it != pClass->m_pScope->m_decls.end() && (it->first == methodName))
	{
		if (it->second->m_pType->get_Kind() == type_function)
		{
			if (it->second->m_virtual)
			{
				IO::StringWriter strbuilder;
				it->second->Write(strbuilder);	// TODO WriteFunctionIdentity???

				if (strbuilder.str() == fullName)
				{
					it->second->m_pOwnerScope = pClass->m_pScope;	// TODO, not here
					return it->second;
				}
			}
		}

		++it;
	}

	return FindVirtualMethodInPrimaryBase(pClass, methodName, fullName);
}

Declarator* FindVirtualMethodInPrimaryBase(ClassType* pClass, StringIn methodName, StringIn fullName)
{
	for (ucount_t i = 0; i < pClass->m_bases.size(); ++i)
	{
	// Only check primary class
		if (i == 0)
		{
			Declarator* pDecl = FindVirtualMethodInPrimary(pClass->m_bases[i]->m_pClass->AsClass(), methodName, fullName);
			if (pDecl)
			return pDecl;
		}
	}

	return NULL;
}

/*
CDeclarator* VTableMember;

CDeclarator* GetFirstMember(ClassType* pClass)
{
	if (VTableMember == NULL)
	{
		VTableMember = new CDeclarator;
		VTableMember->m_offset = 0;
		VTableMember->m_pType = new PointerType(Types::type_void);
	}

	ASSERT(pClass);

	if (pClass->m_bVT)
	{
		return VTableMember;
	}

	{
		for (int i = 0; i < pClass->m_bases.GetSize(); i++)
		{
			BaseClass* baseclass = pClass->m_bases[i];

			ClassType* pBase = (ClassType*)baseclass->m_pClass->GetStripped();

			CDeclarator* p = GetFirstMember(pBase);
			if (p) return p;
		}
	}

	{
		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			if (!pMember->m_static)
			{
				if (!pMember->m_typedef)
				{
					if (pMember->m_pType->get_Kind() != type_function)
					{
					//	ASSERT(pMember->m_bitoffset == 0);
					//	ASSERT(pMember->m_bitlength == 0);

						if (pMember->m_pType->GetStripped()->get_Kind() == type_class)
						{
							CDeclarator* p = GetFirstMember(pMember->m_pType->GetClass());
							if (p) return p;
						}
						return pMember;
					}
				}
			}
		}
	}

	return NULL;
}
*/

/*
Type* GetFirstMemberType(Type* pType)
{
	if (pType->get_Kind() == type_array)
	{
		return GetFirstMemberType(((ArrayType*)pType)->get_ElemType());
	}
	else if (pType->get_Kind() == type_class)
	{
		CDeclarator* pFirstMember = GetFirstMember((ClassType*)pType);
		if (pFirstMember)
		{
			return GetFirstMemberType(pFirstMember->m_pType);
		}
		else
			return NULL;
	}
	else if (pType->get_Kind() == type_typedef)
	{
		return GetFirstMemberType(static_cast<Typedef*>(pType)->m_pType);
	}
	else if (pType->get_Kind() == type_cv)
	{
		return GetFirstMemberType(static_cast<ModifierType*>(pType)->get_Type());
	}

	return pType;
}
*/

unsigned int GetAlignment(CGlobal* pGlobal, Type* pType, unsigned int packing)
{
	switch (pType->get_Kind())
	{
	case type_class:
		{
			ClassType* pClassType = static_cast<ClassType*>(pType);

			CalcClass(pGlobal, pClassType, packing/*??*/);

			uint alignment;

			if (pClassType->m_force_alignment)
			{
				alignment = pClassType->m_force_alignment;
			}
			else
			{
				alignment = min(packing, (unsigned int)pClassType->m_alignment);
			//	if (packing == 0)	// ??
			//		alignment = 1;
			}

			ASSERT(alignment > 0);
			if ((int)alignment <= 0) raise(Exception(L"Internal error: alignment <= 0"));

			return alignment;
		}
		break;

	case type_array:
		return GetAlignment(pGlobal, static_cast<ArrayType*>(pType)->get_ElemType(), packing);

	case type_cv:
		return GetAlignment(pGlobal, static_cast<ModifierType*>(pType)->m_pPointerTo, packing);

	case type_typedef:
		return GetAlignment(pGlobal, static_cast<Typedef*>(pType)->m_pType, packing);

	case type_pm:
		return pGlobal->m_sizeofptr*2;	// ??
		break;

	default:
		return min(packing, (unsigned int)pType->get_sizeof(pGlobal->m_sizeofptr));
	}
}

void CalcClass(CGlobal* pGlobal, ClassType* pClass, unsigned int default_alignment);

void CalcClass(CGlobal* pGlobal, Type* pType, unsigned int default_alignment)
{
	switch (pType->get_Kind())
	{
	case type_class:
		CalcClass(pGlobal, static_cast<ClassType*>(pType), default_alignment);
		break;

	case type_typedef:
		CalcClass(pGlobal, static_cast<Typedef*>(pType)->m_pType, default_alignment);
		break;

	case type_array:
		CalcClass(pGlobal, static_cast<ArrayType*>(pType)->m_pElemType, default_alignment);
		break;
	}
}

CodeCompExt void CalcClass(CGlobal* pGlobal, ClassType* pClass, unsigned int default_alignment)
{
	/*
	if (*pClass->m_qname == "LDraw::Rect<float>")
	{
		MessageBeep(-1);
	}
	*/

	/*
	if (pClass->m_name == "Element" || pClass->m_name == "ICSSElementResolver")
	{
	//	__asm int 3
		//MessageBeep(-1);
	}
	*/

	if (pClass->m_pTemplateParams)
	{
		return;
	}

	if (!pClass->m_def)
	{
		VERIFY(pClass->m_bases.GetSize() == 0);
		VERIFY(pClass->m_pScope->m_orderedDecls.GetSize() == 0);
		return;
	}

	if (pClass->m_packing == 0)
	{
		ASSERT(pClass->m_pInstantiatedFromClass);
		pClass->m_packing = pClass->m_pInstantiatedFromClass->m_packing;
#if 0
		VERIFY(pClass->m_packing > 0);
#endif
	}

//	ASSERT(pClass->m_pTemplateParams == 0);

//	ASSERT(pGlobal);

	ASSERT(pClass->m_name == nullptr || !pClass->m_name.Contains(':'));

	if (pClass->m_sizeof != ~0)
		return;

	//Class* pInstantiatedClass = new Class;

	/*
	pInstantiatedClass->m_kwType = pClass->m_kwType;
	pInstantiatedClass->m_name = pClass->m_name;
	pInstantiatedClass->m_qname = pClass->m_qname;
	*/

	/*
	if (pClass->m_alignment)
	{
		alignment = pClass->m_alignment;
	}
	*/

	pClass->m_sizeof = 0;
	pClass->m_rsizeof = 0;

	pClass->m_virtualSize = 0;

	BaseClass** bases = (BaseClass**)_alloca(sizeof(BaseClass*)*pClass->m_bases.size());

	unsigned int alignment = 0;

	bool bVirtualBaseClass = false;
	for (size_t i = 0; i < pClass->m_bases.size(); ++i)
	{
		BaseClass* baseclass = pClass->m_bases[i];

		if (ClassType* pBaseAsClass = baseclass->m_pClass->AsClass())
		{
			if (!pBaseAsClass->m_def)
			{
			//	DebugTrace("TODO: BaseClass (probably template) not def, alignment not calculated, using 4\n");
				++pGlobal->m_errors;

				if (pClass->m_sourcefile)
				{
					Console::get_Out() << pClass->m_sourcefile->ToString() << "(" << pClass->m_line+1 << ")" << " : error C2027 : use of undefined type " << quote(pBaseAsClass->m_qname) << endl;
					Console::get_Out() << '\t' << pBaseAsClass->m_sourcefile->ToString() << "(" << pBaseAsClass->m_line+1 << ")" << " : see declaration of " << quote(pBaseAsClass->m_qname) << endl;
				}
				else
				{
					Console::get_Out() << "(unknown file)" << " : error : undefined baseclass '" << pBaseAsClass->m_qname << "'\n";
					__debugbreak();
				}

				//Console::get_Out() << pClass->m_pInstantiatedFromClass
 

				/*
			//	pBase->GetClass()->m_def = true;
				pBase->GetClass()->m_rsizeof = 4;
				pBase->GetClass()->m_sizeof = 4;
				pBase->GetClass()->m_alignment = 4;
				*/
			}
			else
			{
				CalcClass(pGlobal, pBaseAsClass, default_alignment);
				if (pBaseAsClass->get_sizeof(pGlobal->m_sizeofptr) == ~0)
				{
					if (pClass->m_sourcefile)
					{
					//	Console::get_Out() << pClass->m_sourcefile->ToString() << paren(pClass->m_line+1) << " : error : undefined baseclass '" << pBaseAsClass->m_qname << "'" << endl;

						Console::get_Out() << pClass->m_sourcefile->ToString() << paren(pClass->m_line+1) << " : error C2027: use of undefined type" << '\'' << pBaseAsClass->get_QName() << '\'' << endl;
						Console::get_Out() << '\t' << pBaseAsClass->m_sourcefile->ToString() << paren(pBaseAsClass->m_line+1) << " : see declaration of " << '\t' << pBaseAsClass->get_QName() << '\'' << endl;
					}
					else
					{
						__debugbreak();
						Console::get_Out() << "undefined baseclass '" << pBaseAsClass->m_qname << "'" << endl;
					}
					++pGlobal->m_errors;
				}
			}

			alignment = max(alignment, (unsigned int)pBaseAsClass->m_alignment);

			if (pBaseAsClass->m_bVT)
				bVirtualBaseClass = true;
		}
		else
		{
			__debugbreak();
			Std::get_Out() << "undefined baseclass" << "\n";
			++pGlobal->m_errors;
		}
	}

	// sort base classes, virtual first, non-virtual last
	{
		int j = 0;

		{
			for (ucount_t i = 0; i < pClass->m_bases.size(); ++i)
			{
				BaseClass* baseclass = pClass->m_bases[i];

				ClassType* pBase = (ClassType*)baseclass->m_pClass->GetStripped();

				if (pBase->m_bVT)
				{
					bases[j++] = baseclass;
				}
			}
		}

		{
			for (ucount_t i = 0; i < pClass->m_bases.size(); ++i)
			{
				BaseClass* baseclass = pClass->m_bases[i];

				ClassType* pBase = (ClassType*)baseclass->m_pClass->GetStripped();

				if (!pBase->m_bVT)
				{
					bases[j++] = baseclass;
				}
			}
		}
	}

	// This should probably have been done earlier

	for (ucount_t i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];
		Type* pMemberType = pMember->m_pType;

		if (pMemberType->get_Kind() == type_function)
		{
		//	if (pMemberType->GetFunction()->m_funcspec == 0)
			{
				if (!pMember->get_IsStatic())
				//	pMemberType->GetFunction()->m_funcspec = pGlobal->m_PP->m_options->m_callingConvention;
				//else
					pMemberType->AsFunction()->m_funcspec = CallType_thiscall;
			}
		}
	}

	bool bVirtual = false;

	{
		for (ucount_t i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); ++i)
		{
			Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];
			Type* pMemberType = pMember->m_pType;

			if (pMemberType->get_Kind() == type_function)
			{
				if (pMember->m_virtual)
				{
					bVirtual = true;
					break;
				}
			}
		}
	}

#if 0
	{
		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			if (pMember->m_pType->get_Kind() != type_typedef)
			{
				CalcClass(NULL, pMember->m_pType, default_alignment);
			}
			/*

			Type* pStrippedType = pMember->m_pType->GetStripped();
			if (pStrippedType->get_Kind() == type_class)
			{
				CalcClass(NULL, (ClassType*)pStrippedType, default_alignment);
			}
			*/
		}
	}
#endif

	// Max Alignment of members
	if (pClass->m_force_alignment == 0)
	{
		for (ucount_t i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); ++i)
		{
			Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			Type* pStrippedType = pMember->m_pType->GetStripped();

			if (!pMember->m_static)
			{
				if (!pMember->m_typedef)
				{
					if (pStrippedType->get_Kind() != type_function)
					{
						if (pStrippedType->get_sizeof(pGlobal->m_sizeofptr) == -1)
						{
							CalcClass(pGlobal, pStrippedType, default_alignment);
						}

						int member_size = (int)pStrippedType->get_sizeof(pGlobal->m_sizeofptr);
						if (member_size == 0) member_size = 1;

						if (member_size == -1)
						{
							Console::get_Out() << __FILE__ << "(" << __LINE__ << ")" << " : INTERNAL ERROR : sizeof=-1\n";
							++pGlobal->m_errors;
						}
						else
						{
							unsigned int member_alignment;
							
							if (pMember->m_alignment)
								member_alignment = pMember->m_alignment;
							else
								member_alignment = GetAlignment(pGlobal, pMember->m_pType, pClass->m_packing);

							ASSERT(member_alignment > 0);

							alignment = max(alignment, member_alignment);
						}
					}
				}
			}
		}

		pClass->m_alignment = alignment;
	}
	else
	{
		pClass->m_alignment = pClass->m_force_alignment;
		alignment = pClass->m_alignment;
	}

	if (pClass->m_bases.GetSize() == 0)
	{
		if (bVirtual)
		{
			pClass->m_rsizeof += pGlobal->m_sizeofptr;	// virtual table pointer
			pClass->m_alignment = max((unsigned int)pClass->m_alignment, (unsigned int)pGlobal->m_sizeofptr);
		//	pClass->m_sizeof += 4;	// virtual table pointer
		}
	}
	else
	{
	// if we have a dynamic base class, we share the vptr with it
		if (!bVirtualBaseClass)
		{
			if (bVirtual)
			{
				pClass->m_rsizeof += pGlobal->m_sizeofptr;	// virtual table pointer
				pClass->m_alignment = MAX(pClass->m_alignment, pGlobal->m_sizeofptr);
			//	pClass->m_sizeof += 4;	// virtual table pointer
			}
		}
	}

	{
		// align after vtable pointer
		if (pClass->m_rsizeof > 0)
		{
			if (true)	// vc
			{
				unsigned int align = pClass->m_alignment;
				pClass->m_rsizeof = (pClass->m_rsizeof + align-1) / align * align;
			}
		}
	}

	if (bVirtualBaseClass || bVirtual)
		pClass->m_bVT = true;

#if 0
	if (*pClass->m_name == "red_black_node")
	{
		ASSERT(pClass->m_bVT);
	}
#endif

	for (ucount_t i = 0; i < pClass->m_bases.GetSize(); ++i)
	{
		BaseClass* baseclass = bases[i];

		/*
		if (!baseclass->m_pClass->GetClass()->m_def)
		{
			DebugTrace("TODO: BaseClass (probably template) not def, alignment not calculated, using 4\n");

			unsigned int align = 4;//baseclass->m_pClass->GetClass()->m_alignment;
			ASSERT(align > 0);
			pClass->m_rsizeof = (pClass->m_rsizeof + align-1) / align * align;
		}
		else
		*/
		if (baseclass->m_pClass->AsClass()->m_rsizeof > 0)
		{
			unsigned int align = baseclass->m_pClass->AsClass()->m_alignment;
			if (align == 0)
			{
				Console::get_Out() << __FILE__ << "(" << __LINE__ << ")" << " : INTERNAL ERROR" << "\n";
				++pGlobal->m_errors;

				align = 4;
			}
			pClass->m_rsizeof = (pClass->m_rsizeof + align-1) / align * align;
		}
		else
		{
		//	unsigned int align = baseclass->m_pClass->m_alignment;
		//	ASSERT(align > 0);
		//	unsigned ints->m_rsizeof = (pClass->m_rsizeof + align-1) / align * align;

			/*
			if (i > 0)
			;//	pClass->m_rsizeof++;

			if (bVirtualBaseClass)
				;//pClass->m_rsizeof++;
				*/
		}

		baseclass->m_offset = pClass->m_rsizeof;

		/*
		if (i == 0)
		{
			if (baseclass->m_pClass->m_rsizeof > 0)
				pClass->m_rsizeof += baseclass->m_pClass->m_sizeof;
		}
		else
		*/
		{
			if (baseclass->m_pClass->AsClass()->m_rsizeof > 0 || bVirtualBaseClass)
				pClass->m_rsizeof += baseclass->m_pClass->AsClass()->m_sizeof;
		}

		if (i == 0)	// Share virtual table with primary base class
		{
			pClass->m_virtualSize += baseclass->m_pClass->AsClass()->m_virtualSize;
		}
	}

	uint bitsizeof = pClass->m_rsizeof << 3;

	{
		for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); ++i)
		{
			Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			Type* pMemberType = pMember->m_pType;

			if (pMemberType->get_Kind() == type_function)
			{
				IO::StringWriter strbuilder;
				pMember->WriteFunctionIdentity(strbuilder);
				String str = strbuilder.str();

				/*
				if (*pMember->m_name == "set_VisualTree")
				{
					MessageBeep(-1);
				}
				*/

				/*
				if (pClass->m_qname == "System::Gui::Element" && pMember->m_name == "get_id")
				{
					__asm int 3
				}
				*/

				Declarator* pVirtualFunc = FindVirtualMethodInBases(pClass, pMember->m_name, str);
				//if (pVirtualFunc)
				{
					if (pVirtualFunc != NULL || pMember->m_virtual)
					{
						// If not found in any of the primarybase, make an entry for it in the virtual table
					//	if (FindVirtualMethodInPrimaryBase(pClass, pMember->m_name, str) == NULL)

						/*
						if (pMember->m_name == "load")
						{
							MessageBeep(-1);
						}
						*/

						if (pVirtualFunc == NULL)
						{
							if (pMember->m_name.At(0) == '~')	// destructor
							{
								//if (*pClass->m_name == "Object")	// TODO ???
								if (!bVirtualBaseClass)	// ??
								{
									pMember->m_offset = pClass->m_virtualSize;
								//	pClass->m_virtualSize += 4+4;	// two entries
									pClass->m_virtualSize += pGlobal->m_sizeofptr;
								}
							}
							else
							{
								pMember->m_offset = pClass->m_virtualSize;
								pClass->m_virtualSize += pGlobal->m_sizeofptr;

							//	TRACE("%s::%s %d -------- %s\n", pClass->m_name->c_str(), pMember->m_name->c_str(), pMember->m_offset>>2, str->c_str());
							}
						}
						else	// overridden
						{
							pMember->m_offset = pVirtualFunc->m_offset;
							pMember->m_pOverrideClass = pVirtualFunc->GetClass()->AsClass();
						}
					}
				}
			}

			Type* pStrippedType = pMember->m_pType->GetStripped();

			if (!pMember->m_static)
			{
				if (!pMember->m_typedef)
				{
					if (pStrippedType->get_Kind() != type_function)
					{
						if (pStrippedType->get_sizeof(pGlobal->m_sizeofptr) == -1)
						{
							CalcClass(pGlobal, pMember->m_pType, default_alignment);
						}

						uint member_size = pStrippedType->get_sizeof(pGlobal->m_sizeofptr);
					//	if (member_size == 0) member_size = 1;

						if (member_size == ~0)
						{
							//Std::Out << "sizeof(" << pStrippedType->ToString()
							Console::Out << __FILE__ << paren(__LINE__) << " : INTERNAL ERROR, sizeof=-1" << "\n";
						//	Std::Out << pMember->m_sourcefile->ToString() << paren(pMember->m_sourceline+1) << " : INTERNAL ERROR\n";
							Console::Out << pClass->get_QName() << "." << pMember->m_name << "\n\n";

						//	printClass(pClass, 0);
						}
						else
						{
							if (pClass->m_kwType == ClassKey_union)
							{
								ASSERT(member_size != ~0);

								if (member_size == 0) member_size = 1;

								bitsizeof = max(bitsizeof, member_size*8);
							}
							else
							{
								if (pMember->m_bitlength)
								{
									unsigned int member_alignment = pStrippedType->get_sizeof(pGlobal->m_sizeofptr);

									unsigned int byteoffset = (bitsizeof>>3) / member_alignment * member_alignment;

									pMember->m_offset = byteoffset;
									pMember->m_bitoffset = bitsizeof - (byteoffset*8);
									bitsizeof += pMember->m_bitlength;
								}
								else
								{
									unsigned int member_alignment;
									
									if (pMember->m_alignment)
										member_alignment = pMember->m_alignment;
									else
										member_alignment = GetAlignment(pGlobal, pStrippedType, pClass->m_packing);

									ASSERT(member_alignment > 0);

									//member_alignment = MIN(member_alignment, pClass->m_packing);

									ASSERT(member_size != -1);

									//if (firstmembersize == 0) firstmembersize = 1;

									unsigned int alignbits = member_alignment/*MIN(firstmembersize, alignment)*/ *8;

									bitsizeof = (bitsizeof + alignbits-1) / alignbits * alignbits;
									ASSERT((bitsizeof & 7) == 0);
									pMember->m_offset = bitsizeof >> 3;

									bitsizeof += member_size*8;
								}
							}
						}
					}
				}
			}
		}

		pClass->m_rsizeof = (bitsizeof+7)/8;
		pClass->m_sizeof = pClass->m_rsizeof;

		if (pClass->m_sizeof == 0)
		{
			pClass->m_alignment = 1;
			ASSERT(pClass->m_rsizeof == 0);
			pClass->m_sizeof = 1;
		}
		else
		{
			ASSERT(pClass->m_alignment > 0);

			unsigned int align = pClass->m_alignment;//MIN(pClass->m_packing, pClass->m_alignment);//MIN(size, pClass->m_alignment);
			pClass->m_sizeof = (pClass->m_sizeof + align-1) / align * align;
		//	pClass->m_rsizeof = pClass->m_sizeof;
			ASSERT(pClass->m_sizeof > 0);
		}

		/*
		if (*pClass->m_name == "function2" && pClass->m_sizeof == 0)
		{
			MessageBeep(-1);
		}
		*/
	}
}

void CalcClass_gcc(CGlobal* pGlobal, ClassType* pClass, unsigned int default_alignment)
{
//	ASSERT(pClass->m_pTemplateParams == 0);

//	ASSERT(pGlobal);

	if (!pClass->m_def)
	{
		ASSERT(pClass->m_bases.GetSize() == 0);
		ASSERT(pClass->m_pScope->m_orderedDecls.GetSize() == 0);
		return;
	}

	ASSERT(pClass->m_def);

	ASSERT(pClass->m_name == nullptr || pClass->m_name.find(':') == String::npos);

	if (pClass->m_sizeof != -1)
		return;

	/*
	if (*pClass->m_name == "SVGLocatableImpl")
	{
		MessageBeep(-1);
	}
	*/

	//Class* pInstantiatedClass = new Class;

	/*
	pInstantiatedClass->m_kwType = pClass->m_kwType;
	pInstantiatedClass->m_name = pClass->m_name;
	pInstantiatedClass->m_qname = pClass->m_qname;
	*/

	pClass->m_sizeof = 0;
	pClass->m_rsizeof = 0;
//	if (
//	pClass->m_alignment = 0;
	pClass->m_virtualSize = 0;

	BaseClass** bases = (BaseClass**)_alloca(sizeof(BaseClass*)*pClass->m_bases.GetSize());

	bool bVirtualBaseClass = false;
	{
		for (size_t i = 0; i < pClass->m_bases.GetSize(); ++i)
		{
			BaseClass* baseclass = pClass->m_bases[i];

			ClassType* pBase = (ClassType*)baseclass->m_pClass->GetStripped();

			if (pBase->get_Kind() == type_class)
			{
				CalcClass(pGlobal, pBase->AsClass(), default_alignment);
			}

			pClass->m_alignment = max(pClass->m_alignment, pBase->m_alignment);

			if (pBase->m_bVT)
				bVirtualBaseClass = true;
		}
	}

	{
		int j = 0;

		{
			for (size_t i = 0; i < pClass->m_bases.GetSize(); ++i)
			{
				BaseClass* baseclass = pClass->m_bases[i];

				ClassType* pBase = (ClassType*)baseclass->m_pClass->GetStripped();

				if (pBase->m_bVT)
				{
					bases[j++] = baseclass;
				}
			}
		}

		{
			for (size_t i = 0; i < pClass->m_bases.GetSize(); ++i)
			{
				BaseClass* baseclass = pClass->m_bases[i];

				ClassType* pBase = (ClassType*)baseclass->m_pClass->GetStripped();

				if (!pBase->m_bVT)
				{
					bases[j++] = baseclass;
				}
			}
		}
	}

	bool bVirtual = false;

	{
		for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); ++i)
		{
			Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];
			Type* pMemberType = pMember->m_pType;

			if (pMemberType->get_Kind() == type_function)
			{
				if (pMember->m_virtual)
				{
					bVirtual = true;
					break;
				}
			}
		}
	}

	// Max Alignment of members
	{
		for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); ++i)
		{
			Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			Type* pStrippedType = pMember->m_pType->GetStripped();

			if (pStrippedType->get_Kind() == type_class)
			{
				CalcClass(pGlobal, (ClassType*)pStrippedType, default_alignment);
			}

			if (!pMember->m_static)
			{
				if (!pMember->m_typedef)
				{
					if (pMember->m_pType->get_Kind() != type_function)
					{
						int member_size = pMember->m_pType->get_sizeof(pGlobal->m_sizeofptr);
						if (member_size == 0) member_size = 1;

						if (member_size == -1)
						{
							printf("oops, sizeof=-1\n");
						}
						else
						{
							unsigned int member_alignment;
							
							if (pMember->m_alignment)
								member_alignment = pMember->m_alignment;
							else
								member_alignment = GetAlignment(pGlobal, pMember->m_pType, pClass->m_packing);

							ASSERT(member_alignment > 0);

							pClass->m_alignment = max((unsigned int)pClass->m_alignment, member_alignment);
						}
					}
				}
			}
		}
	}

	if (pClass->m_bases.GetSize() == 0)
	{
		if (bVirtual)
		{
			pClass->m_rsizeof += pGlobal->m_sizeofptr;	// virtual table pointer
			pClass->m_alignment = MAX(pClass->m_alignment, pGlobal->m_sizeofptr);
		//	pClass->m_sizeof += 4;	// virtual table pointer
		}
	}
	else
	{
	// if we have a dynamic base class, we share the vptr with it
		if (!bVirtualBaseClass)
		{
			if (bVirtual)
			{
				pClass->m_rsizeof += pGlobal->m_sizeofptr;	// virtual table pointer
				pClass->m_alignment = MAX(pClass->m_alignment, pGlobal->m_sizeofptr);
			//	pClass->m_sizeof += 4;	// virtual table pointer
			}
		}
	}

	{
		// align after vtable pointer
		if (pClass->m_rsizeof > 0)
		{
			if (true)	// vc
			{
				unsigned int align = pClass->m_alignment;
				pClass->m_rsizeof = (pClass->m_rsizeof + align-1) / align * align;
			}
		}
	}

	if (bVirtualBaseClass || bVirtual)
		pClass->m_bVT = true;

	for (size_t i = 0; i < pClass->m_bases.GetSize(); ++i)
	{
		BaseClass* baseclass = /*pClass->m_*/bases[i];

		if (baseclass->m_pClass->AsClass()->m_rsizeof > 0)
		{
			unsigned int align = baseclass->m_pClass->AsClass()->m_alignment;
			ASSERT(align > 0);
			pClass->m_rsizeof = (pClass->m_rsizeof + align-1) / align * align;
		}
		else
		{
		//	unsigned int align = baseclass->m_pClass->m_alignment;
		//	ASSERT(align > 0);
		//	unsigned ints->m_rsizeof = (pClass->m_rsizeof + align-1) / align * align;

			/*
			if (i > 0)
			;//	pClass->m_rsizeof++;

			if (bVirtualBaseClass)
				;//pClass->m_rsizeof++;
				*/
		}

		baseclass->m_offset = pClass->m_rsizeof;

		/*
		if (i == 0)
		{
			if (baseclass->m_pClass->m_rsizeof > 0)
				pClass->m_rsizeof += baseclass->m_pClass->m_sizeof;
		}
		else
		*/
		{
			if (baseclass->m_pClass->AsClass()->m_rsizeof > 0 || bVirtualBaseClass)
				pClass->m_rsizeof += baseclass->m_pClass->AsClass()->m_sizeof;
		}

		if (i == 0)	// Share virtual table with primary base class
		{
			pClass->m_virtualSize += baseclass->m_pClass->AsClass()->m_virtualSize;
		}
	}

	int bitsizeof = pClass->m_rsizeof*8;

	{
		for (size_t i = 0; i < pClass->m_pScope->m_orderedDecls.GetSize(); ++i)
		{
			Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			Type* pMemberType = pMember->m_pType;

			if (pMemberType->get_Kind() == type_function)
			{
				IO::StringWriter strbuilder;
				pMember->Write(strbuilder);
				String str = strbuilder.str();

				Declarator* pVirtualFunc = FindVirtualMethodInBases(pClass, pMember->m_name, str);
				//if (pVirtualFunc)
				{
					if (pVirtualFunc != NULL || pMember->m_virtual)
					{
						// If not found in any of the primarybase, make an entry for it in the virtual table
						if (FindVirtualMethodInPrimaryBase(pClass, pMember->m_name, str) == NULL)
						{
							if (pMember->m_name.At(0) == '~')	// destructor
							{
								//if (*pClass->m_name == "Object")	// TODO ???
								if (!bVirtualBaseClass)	// ??
								{
									pMember->m_offset = pClass->m_virtualSize;
									pClass->m_virtualSize += pGlobal->m_sizeofptr*2;	// two entries

								//	TRACE("%s::%s %d -------- %s\n", pClass->m_name->c_str(), pMember->m_name->c_str(), pMember->m_offset>>2, str->c_str());
								}
							}
							else
							{
								pMember->m_offset = pClass->m_virtualSize;
								pClass->m_virtualSize += pGlobal->m_sizeofptr;

							//	TRACE("%s::%s %d -------- %s\n", pClass->m_name->c_str(), pMember->m_name->c_str(), pMember->m_offset>>2, str->c_str());
							}
						}
					}
				}
			}

			Type* pStrippedType = pMember->m_pType->GetStripped();

			if (!pMember->m_static)
			{
				if (!pMember->m_typedef)
				{
					if (pMember->m_pType->get_Kind() != type_function)
					{
						int member_size = pMember->m_pType->get_sizeof(pGlobal->m_sizeofptr);
					//	if (member_size == 0) member_size = 1;

						if (member_size == -1)
						{
							printf("oops, sizeof=-1\n");
						}
						else
						{
							unsigned int member_alignment;
							
							if (pMember->m_alignment)
								member_alignment = pMember->m_alignment;
							else
								member_alignment = GetAlignment(pGlobal, pMember->m_pType, pClass->m_packing);

							ASSERT(member_alignment > 0);

							if (pClass->m_kwType == ClassKey_union)
							{
								ASSERT(member_size != -1);

								if (member_size == 0) member_size = 1;

								bitsizeof = max(bitsizeof, member_size*8);
							}
							else
							{
								if (pMember->m_bitlength)
								{
								//	unsigned int alignbits = member_alignment/*MIN(firstmembersize, alignment)*/ *8;

								//	bitsizeof = (bitsizeof + alignbits-1) / alignbits * alignbits;

								//	member_alignment;

									unsigned int byteoffset = (bitsizeof>>3) / member_alignment * member_alignment;

								//	bitsizeof += pMember->m_bitlength;
								
									pMember->m_offset = byteoffset;
									pMember->m_bitoffset = bitsizeof - (byteoffset*8);
									bitsizeof += pMember->m_bitlength;
									
									/*
									pMember->m_offset = bitsizeof >> 3;
									pMember->m_bitoffset = bitsizeof & 7;
									bitsizeof += pMember->m_bitlength;
									*/
								}
								else
								{
									ASSERT(member_size != -1);

									//if (firstmembersize == 0) firstmembersize = 1;

									unsigned int alignbits = member_alignment/*MIN(firstmembersize, alignment)*/ *8;

									bitsizeof = (bitsizeof + alignbits-1) / alignbits * alignbits;
									ASSERT((bitsizeof & 7) == 0);
									pMember->m_offset = bitsizeof >> 3;

									bitsizeof += member_size*8;
								}
							}
						}
					}
				}
			}
		}

		pClass->m_rsizeof = (bitsizeof+7)/8;
		pClass->m_sizeof = pClass->m_rsizeof;

		if (pClass->m_sizeof == 0)
		{
			pClass->m_alignment = 1;
			ASSERT(pClass->m_rsizeof == 0);
			pClass->m_sizeof = 1;
		}
		else
		{
			unsigned int align = pClass->m_alignment;//MIN(size, pClass->m_alignment);
			pClass->m_sizeof = (pClass->m_sizeof + align-1) / align * align;
		//	pClass->m_rsizeof = pClass->m_sizeof;
			ASSERT(pClass->m_sizeof > 0);
		}
	}
}

bool ObjectDerived(ClassType* pClass)
{
	if (pClass->m_qname == "System::Object")
	{
		return true;
	}

	// Assert that all but the leftmost must NOT be derived from System::Object
	for (uint i = 1; i < pClass->m_bases.size(); ++i)
	{
		ASSERT(!ObjectDerived(pClass->m_bases[i]->m_pClass->AsClass()));
	}

	return ObjectDerived(pClass->m_bases[0]->m_pClass->AsClass());
}

void Validate(ClassType* pClass)
{
	bool bObjectDerived = ObjectDerived(pClass);

	for (uint i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* pMember = pClass->m_pScope->m_orderedDecls[i];

		Type* pStrippedType = pMember->m_pType->GetStripped();

		if (!pMember->m_static)
		{
			if (!pMember->m_typedef)
			{
				if (pMember->m_pType->get_Kind() != type_function)
				{
				}
			}
		}
	}
}

CppSourceFile* CGlobal::AddSourceFile(FilePart* filepart)
{
	if (filepart == NULL) return NULL;

	CppSourceFile*& sourcefile = m_sourceFiles[filepart->m_fullname];
	if (sourcefile == NULL)
	{
		sourcefile = new CppSourceFile;
		sourcefile->m_filepart = filepart;
	}

	return sourcefile;
}

/*
// TODO
ast::Expression* Compiler::parse_expression(StringIn str)
{
	return ast::parse_expression(this, str);
}

asr::DeclarationList* Compiler::parse_translation_unit(StringIn str)
{
	return ast::parse_translation_unit(this, str);
}
*/

Options::Options() :
	m_structMemberAlignment(0),
	m_treatWarningsAsErrors(false),
	m_callingConvention(CallType_cdecl),
	m_type_wchar_t(true)
{
	m_subplatform = m_x86_Pentium_II;
}

int Options::get_StructMemberAlignment() const
{
	if (m_structMemberAlignment == 0)
	{
		if (m_exeType == 0)
			return 2;
		else	// x86/x64
			return 8;
	}
	else
		return m_structMemberAlignment;
}

CodeCompExt int cpp_compile(CGlobal* pGlobal, StringIn filepath, StringIn fileoutpath, Options* options)
{
	VerifyArgumentNotNull(options);

	int errors = 1;	// Assume error at this point

	Namespace* pGlobalNamespace = new Namespace;

//	pGlobal->m_typelibs.push_back(pGlobal->m_typelib);

	//CGlobal* pGlobal = new CGlobal;
	//Scope* pGlobalScope = new Scope;	// Global scope
	Scope* pGlobalScope = pGlobalNamespace->m_pScope;

	pGlobal->m_namespace = pGlobalNamespace;

	m_outputStream = Std::get_Out();//new FileStream(GetStdHandle(STD_OUTPUT_HANDLE));
//	m_outputStream = DebugStream::get_Out();//new FileStream(GetStdHandle(STD_OUTPUT_HANDLE));
//	m_outputStream = new FileStream(GetStdHandle(STD_OUTPUT_HANDLE));
#if 1
	Log = &IO::NullTextWriter::writer;
#endif

	PP::CFile* pFile = new PP::CFile;
	if (pFile->open(filepath))
	{
		pPP2 = new PP::CPreprocessor(pFile, options);
		pPP2->m_msgStream = Std::get_Out();

		pPP2->m_includeFiles.push_back(PP::IncludeFile(pFile->m_filepath, pFile->m_filetime));

		pGlobal->m_PP = pPP2;

		pPP2->Define("__LERSTAD__", 1);
		pPP2->Define("__cplusplus", 1);

		if (options->m_exeType == 1)
		{
		//	pGlobal->m_type_wchar_t = true;

			pPP2->Define("AMIGA", 1);
			pPP2->Define("_STDCALL_SUPPORTED");
		}
		else if (options->m_exeType == 2)
		{
		//	pGlobal->m_type_wchar_t = true;

			if (options->m_x64)
			{
				Std::Out << "compiling for x64" << endl;

				pPP2->Define("_M_X64", 1);
				pPP2->Define("_M_AMD64", 1);
				pPP2->Define("_WIN64", 1);
				pPP2->Define("_INTEGRAL_MAX_BITS", 64);

				pGlobal->m_sizeofptr = 8;
			}
			else
			{
				Std::Out << "compiling for Intel x86" << endl;

				pPP2->Define("_M_IX86", options->m_subplatform);
				pPP2->Define("_INTEGRAL_MAX_BITS", 32);

				pGlobal->m_sizeofptr = 4;
			}

			pPP2->Define("_WIN32");
			pPP2->Define("_STDCALL_SUPPORTED");
		//	pPP2->Define("_MSC_VER", 1);	// TODO remove??
		}
		else if (options->m_exeType == 3)
		{
		//	pGlobal->m_type_wchar_t = true;

			pPP2->Define("MAC");
		}
		else
			ASSERT(0);

		if (options->m_defines.GetLength())
		{
			size_t start = 0;
			do
			{
				size_t end = options->m_defines.find(';', start);
				pPP2->Define(options->m_defines.SubString(start, (end == String::npos)? String::npos: end-start));

				if (end == String::npos) break;

				start = end+1;
			}
			while (1);
		}

		if (options->m_includeDirs.GetLength())
		{
			size_t start = 0;
			do
			{
				size_t end = options->m_includeDirs.find(';', start);
				pPP2->m_includeDirs.push_back(options->m_includeDirs.SubString(start, (end == String::npos)? String::npos: end-start));

				if (end == String::npos) break;

				start = end+1;
			}
			while (1);
		}

/*
		pp2_in = pFile->m_fp;	// TODO
		pp_parse ();

		if (pp_file)
		{
			PP_process(pp_file);
		}
*/

		AddKeyword("auto", ast::AUTO_KW);
		AddKeyword("bool", ast::BOOL_KW);
		AddKeyword("break", ast::BREAK_KW);
		AddKeyword("case", ast::CASE_KW);
		AddKeyword("char", ast::CHAR_KW);
		AddKeyword("class", ast::CLASS_KW);
		AddKeyword("const", ast::CONST_KW);
		AddKeyword("continue", ast::CONTINUE_KW);
		AddKeyword("decltype", ast::DECLTYPE_KW);
		AddKeyword("delete", ast::DELETE_KW);
		AddKeyword("do", ast::DO_KW);
		AddKeyword("double", ast::DOUBLE_KW);
		AddKeyword("else", ast::ELSE_KW);
		AddKeyword("enum", ast::ENUM_KW);
		AddKeyword("explicit", ast::EXPLICIT_KW);
		AddKeyword("export", ast::EXPORT_KW);
		AddKeyword("extern", ast::EXTERN_KW);
		AddKeyword("false", ast::FALSE_KW);
		AddKeyword("float", ast::FLOAT_KW);
		AddKeyword("friend", ast::FRIEND_KW);
		AddKeyword("if", ast::IF_KW);
		AddKeyword("int", ast::INT_KW);
		AddKeyword("interface", ast::INTERFACE_KW);
		AddKeyword("namespace", ast::NAMESPACE_KW);
		AddKeyword("nullptr", ast::NULLPTR_KW);
		AddKeyword("long", ast::LONG_KW);
		AddKeyword("signed", ast::SIGNED_KW);
		AddKeyword("unsigned", ast::UNSIGNED_KW);
		AddKeyword("volatile", ast::VOLATILE_KW);
		AddKeyword("static", ast::STATIC_KW);
		AddKeyword("register", ast::REGISTER_KW);
		AddKeyword("void", ast::VOID_KW);
		AddKeyword("operator", ast::OPERATOR_KW);
		AddKeyword("struct", ast::STRUCT_KW);
		AddKeyword("union", ast::UNION_KW);
		AddKeyword("using", ast::USING_KW);
		AddKeyword("typedef", ast::TYPEDEF_KW);
		AddKeyword("typename", ast::TYPENAME_KW);
		AddKeyword("inline", ast::INLINE_KW);
		AddKeyword("virtual", ast::VIRTUAL_KW);
		AddKeyword("return", ast::RETURN_KW);
		AddKeyword("public", ast::PUBLIC_KW);
		AddKeyword("protected", ast::PROTECTED_KW);
		AddKeyword("private", ast::PRIVATE_KW);
		AddKeyword("short", ast::SHORT_KW);
		AddKeyword("sizeof", ast::SIZEOF_KW);
		AddKeyword("this", ast::THIS_KW);
		AddKeyword("true", ast::TRUE_KW);
		AddKeyword("typeid", ast::TYPEID_KW);
		AddKeyword("while", ast::WHILE_KW);
		AddKeyword("for", ast::FOR_KW);
		AddKeyword("switch", ast::SWITCH_KW);
		AddKeyword("default", ast::DEFAULT_KW);
		AddKeyword("goto", ast::GOTO_KW);
		AddKeyword("try", ast::TRY_KW);
		AddKeyword("throw", ast::THROW_KW);
		AddKeyword("catch", ast::CATCH_KW);
		AddKeyword("dynamic_cast", ast::DYNAMIC_CAST_KW);
		AddKeyword("reinterpret_cast", ast::REINTERPRET_CAST_KW);
		AddKeyword("static_assert", ast::STATIC_ASSERT_KW);
		AddKeyword("static_cast", ast::STATIC_CAST_KW);
		AddKeyword("const_cast", ast::CONST_CAST_KW);
		AddKeyword("new", ast::NEW_KW);
		AddKeyword("wchar_t", ast::WCHAR_T_KW);
		AddKeyword("template", ast::TEMPLATE_KW);
		AddKeyword("__attribute__", ast::ATTRIBUTE_KW);
	//	AddKeyword("__chip", ast::__CHIP_KW);
		AddKeyword("__int8", ast::__INT8_KW);
		AddKeyword("__int16", ast::__INT16_KW);
		AddKeyword("__int32", ast::__INT32_KW);
		AddKeyword("__int64", ast::__INT64_KW);
		AddKeyword("__int128", ast::__INT128_KW);
		AddKeyword("__cdecl", ast::__CDECL_KW);
		AddKeyword("__stdcall", ast::__STDCALL_KW);
		AddKeyword("__fastcall", ast::__FASTCALL_KW);
		AddKeyword("__declspec", ast::__DECLSPEC_KW);
		AddKeyword("__asm", ast::__ASM_KW);
	//	AddKeyword("__saveds", ast::__SAVEDS_KW);
		//AddKeyword("__interrupt", ast::__INTERRUPT_KW);

		uint32 s = GetTickCount();
		try
		{
			int error = cpp::ast::cpp_parse();

			if (error != 0)
			{
				Std::get_Err() << endl;
				Std::get_Err() << String(ast::cpp_lloc.filename) << paren(ast::cpp_lloc.first_line+1) << " : error : bison error code " << error << endl;
				return error;
			}
		}
		_catch (Exception, e)
		{
			Std::get_Err() << e->get_Reason() << endl;
			return -1;
		}

		uint32 t = GetTickCount() - s;

		Std::get_Out() << "cpp_parse took " << (float)t/1000 << "s\n";

//#if 0	// TODO Have this
//		cpp::Translate(cpp::translation_unit, pGlobal, pScope, 1/*C++*/);
//#endif

		ast::ptoken = ast::g_primlist;
		ast::ptoken = ast::flatten_and_reverse(ast::ptoken, NULL);

		YYLTYPE yyltype;
		yyltype.filename = NULL;
		ast::ptoken = new ast::Expression2List(new ast::Expression2(yyltype, ast::DECLS_TOKEN), ast::ptoken);

		unsigned int default_alignment;
		if (options->m_exeType == 1)	// amiga/m68k
			default_alignment = 2;
		else if (options->m_exeType == 2)	// win32
			default_alignment = 8;

		try
		{
			{
				CGlobal* pGlobal2 = new CGlobal;
				pGlobal2->m_options = pGlobal->m_options;
				pGlobal2->m_errors = pPP2->m_errors;
				pGlobal2->m_warnings = pPP2->m_warnings;
				pGlobal2->m_namespace = new Namespace;
				Scope* pGlobalScope = pGlobal2->m_namespace->m_pScope;

				ast::g_pGlobal = pGlobal2;

				ast::g_pScope = pGlobalScope;
				ast::g_pScope2 = pGlobalScope;

				ast::g_scopeStack.push(pGlobalScope);

				ast::is_parse_exp = false;
				ast::use_cpp_lex = false;

				int nerror = ast::cpp_exp_parse();
				if (nerror != 0)
				{
				//	Std::get_Err() << "\n";
				//	Std::get_Err() << String(ast::cpp_exp_lloc.filename) << paren(ast::cpp_exp_lloc.first_line+1) << " : error : bison code " << nerror << "\n";
					return nerror;
				}

				cpp::ast::translation_unit = Reverse(cpp::ast::translation_unit);
			}

			pGlobal->m_packstack.push(default_alignment);

			ast::Translate(cpp::ast::translation_unit, pGlobal, pGlobalScope, NULL, 1/*C++*/);

			for (size_t i = 0; i < pGlobal->m_alltypes.size(); ++i)
			{
				NamedType* pType = pGlobal->m_alltypes[i];

				if (pType->get_Kind() == type_class)
				{
					ClassType* pClass = (ClassType*)pType;

					if (pClass->m_pTemplateParams == NULL)
					{
						if (pClass->m_qname.LeftOf(9) != "template ")	// TODO, hacky
						{
							CalcClass(pGlobal, pClass, default_alignment);
						}
					}
				}
			}

			String depname = FilePath(fileoutpath).WithExt("dep").ToString();
			IO::StreamWriter ifp(new IO::FileStream(depname, IO::FileMode_Create, IO::FileAccess_Write));
			for (size_t i = 0; i < pPP2->m_includeFiles.size(); ++i)
			{
				PP::IncludeFile& ifile = pPP2->m_includeFiles[i];
				ifp << ifile.m_filename;// << " " << ifile.m_filetime;
				ifp << "\n";
			}

			Std::Out << filepath << " - " << pGlobal->m_errors << " error(s), " << pGlobal->m_warnings << " warning(s)";
			Std::Out << "\n";

			if (pGlobal->m_errors > 0)
			{
				return -1;
			}
		}
		_catch (Exception, e)
		{
			Std::get_Err() << e->get_Reason() << endl;
			return -1;
		}

#if 1
		if (false)
		{
			/*
			fprintf(stdout, "**********************************\n");
			fprintf(stdout, "**********************************\n");
			*/

		//	outfile = stdout;
			//outfile = fopen(fileoutpath, "w");

			IO::StreamWriter fp;//(fileoutpath, "w");;

			ast::WriteToStream(fp, cpp::ast::translation_unit);

		//	fclose(outfile);
		}
#endif

#if 0
		while (ptoken)
		{
			ast::A_ExpOrDecl* expordecl = PrimList(ptoken, pGlobal->m_pGlobalScope, pScope);
			
			ast::A_Declaration* d = expordecl->m_decl;

			if (d->GetKind() == ast::A_Declaration::ast::A_TEMPLATE)
			{
				ast::A_TemplateDeclaration* td = (ast::A_TemplateDeclaration*)d;
			//	td->m_params = Reverse(td->m_params);

				Scope* pTScope;
				pTScope = new Scope;
				pTScope->m_pParentScope = pScope;//pClass->m_pScope->m_pParentScope;
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
						pClass->m_templateParams.push_back(param);
#endif
						
						pTScope->m_types.insert(typemap::value_type(pType->m_name, pType));
					}
					else
					{
						ast::A_DeclaratorTemplateParameter* declparam = (ast::A_DeclaratorTemplateParameter*)tp->head;
						
						CDeclarator* pDeclarator = new CDeclarator;
						pDeclarator->m_pType = GetType(declparam->m_decls, pGlobal, pScope/*pClass->m_pScope*/ /*pTScope*//*pScope*/, NULL/*tp*/, true);//NULL;//d->fundef.declspecList
						declparam->m_declarator->Extract(pDeclarator, pDeclarator->m_pType, pScope/*pClass->m_pScope*/ /*pTScope*//*pScope*/, pGlobal);
						
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
						pClass->m_templateParams.push_back(param);
#endif
						
						pScope->m_decls.insert(declsmap::value_type(pDeclarator->m_name, pDeclarator));
					}
					
					index++;
					
					tp = tp->tail;
				}

				ast::A_ExpOrDecl* expordecl = PrimList(ptoken, pGlobal->m_pGlobalScope, pTScope);
				
				td->m_decl = expordecl->m_decl;

				if (td->m_decl->GetKind() == ast::A_Declaration::ast::A_SIMPLE)
				{
					SimpleDeclaration((ast::A_SimpleDeclaration*)td->m_decl, pGlobal, pScope, NULL, td->m_params, true);
				}
				else
				{
					// TODO fundef
				}

			}
			else
			{
				Translate(d, pGlobal, pScope, 1/*C++*/);
			}
		}
#endif

		errors = 0;
	}
	else
	{
		errors += 1;
		Std::get_Err() << "Failed to open file";
		return -1;
	}

#if 0
	if (true)	// Browse info/database
	{
		Database db("C:\\db", "a+b");

		Table tableClasses;
		try
		{
			tableClasses = db.NewTable(OLESTR("classes"));
			tableClasses.AddField(OLESTR("ID"), FTyp_Long);
			tableClasses.AddField(OLESTR("Name"), FTyp_VarString);
		}
		catch(int)
		{
			tableClasses = db.GetTable(OLESTR("classes"));
		}

		Table tableClassBases;
		try
		{
			tableClassBases = db.NewTable(OLESTR("classbases"));
			tableClassBases.AddField(OLESTR("Derived"), FTyp_Long);
			tableClassBases.AddField(OLESTR("Base"), FTyp_Long);
		}
		catch(int)
		{
			tableClassBases = db.GetTable(OLESTR("classbases"));
		}

		//	accounts->AddField(OLESTR("Username"), FieldDef::FTyp_VarString);
		//	accounts->AddField(OLESTR("Password"), FieldDef::FTyp_VarString);

			/*
			IRecord* pRecord = accounts.NewRecord();
			pRecord->GetField((int)0)->SetValue(1);
			pRecord->GetField(1)->SetData("pop.bredband.no");
			pRecord->m_fields[2]->SetData("sigler");
			pRecord->m_fields[3]->SetData("04bi1u6");

			pRecord->Write(&accounts);
			*/

		long ntypes = pScope->GetTypeCount();
		_Type** types = new _Type*[ntypes];
		pScope->GetTypes(types);

		long n = 0;
		for (int i = 0; i < ntypes; i++)
		{
			_Type* pType = types[i];

			pType->GetClass()->m_id = ++n;
			Record pRecord = tableClasses.NewRecord();
			pRecord[OLESTR("ID")].SetValue((long)pType->m_pClass->m_id);
			pRecord[OLESTR("Name")].SetData(pType->m_pClass->m_name);

			for (int i = 0; i < pType->m_pClass->m_bases.size(); i++)
			{
				cpp::CBaseClass& base = pType->m_pClass->m_bases[i];

				Record pRecord = tableClassBases.NewRecord();
				pRecord[OLESTR("Derived")].SetValue((long)pType->m_pClass->m_id);
				pRecord[OLESTR("Base")].SetValue((long)base.m_pClass->m_id);

				pRecord.Update();
			}

			pRecord.Update();
		}
		delete[] types;

		tableClassBases.Close();
		tableClasses.Close();
	}
#endif

#if 1
	// Had codgen here 
#endif

	return errors;
}

/*
int Compiler::Compile(StringIn filepath, StringIn fileoutpath, int exeType)
{
	return cpp_compile(this, filepath, fileoutpath, exeType);
}
*/

}	// cpp
}	// System
