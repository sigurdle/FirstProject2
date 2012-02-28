#ifndef __CODEGEN_H_
#define __CODEGEN_H_

//#include <stack>

#include "objectfileparser.h"


#include "LFC/disasm.h"

#include "ir.h"

//#include "a_tree.h"

//namespace cpp
//{

namespace System
{

namespace cpp
{
	class CGlobal;
}

struct AS_instrList;
class CCodeGenerator;
class CFunctionCode;

struct ea
{
public:
	ea(uint8 mode = -1, uint8 reg = -1)
	{
		ASSERT(reg == 255 || reg >= 0);
		ASSERT(reg == 255 || reg < 16);

		m_mode = mode;
		m_reg = reg;

		m_lea = false;
		m_value = 0xcbcbcb;
	}

	uint8 m_mode;
	uint8 m_reg;

	bool m_lea;
	long m_value;
};

class CLabel
{
public:
	CLabel()
	{
		m_pos = -1;
	}

	ULONG m_pos;
	vector<uint32> m_branches;
};

class Temp_temp;
class Temp_label;

class Temp_tempList
{
public:

	Temp_tempList(Temp_temp** _temp, Temp_tempList* _tail)
	{
		ASSERT(_temp);

		head = _temp;
		tail = _tail;
	}

	Temp_temp** head;
	Temp_tempList* tail;
};

class Temp_tempListr
{
public:

	Temp_tempListr(Temp_temp*** _temp, Temp_tempListr* _tail)
	{
		ASSERT(_temp);

		temp = _temp;
		tail = _tail;
	}

	Temp_temp*** temp;
	Temp_tempListr* tail;
};

//#include <strstrea.h>

class x86instr;

class AS_Targets
{
public:
	AS_Targets(Temp_labelList* labels)
	{
		m_labels = labels;
	}

	Temp_labelList* m_labels;
};

class CodeCompExt AS_instr
{
public:
	AS_instr()
	{
//		size = 0;
		assem = NULL;
	}

protected:
	// TODO remove
	int size;

public:
	// TODO remove
	char buffer[16];

	// TODO remove
	int getsize()
	{
		return size;
	}

	// TODO remove
	void putbyte(uint8 byte)
	{
		ASSERT(size < 16);
		buffer[size] = byte;
		size++;
	}

	// TODO remove
	void putbytes(void* pv, int len)
	{
		uint8* pb = (uint8*)pv;
		for (int i = 0; i < len; i++)
		{
			putbyte(*pb++);
		}
	}

	//x86instr* assem;
	MInstruction* assem;

	enum { I_DATA, I_DATA2, I_OPER, I_LABEL, I_MOVE, I_SO, I_LINE, I_LBRAC, I_RBRAC, I_LSYM, I_FUN, I_ALIGN} kind;
	union
	{
		struct
		{
			unsigned int num;
		//	unsigned long value;
		}
		LINE;

		char* filename;

	//	System::CDeclarator* declarator;
		T_Declarator* fun;

		struct
		{
			uint8* buffer;
			long size;
		}
		DATA;

		T_ExpList* explist;

	//	strstream assem;
		struct
		{
		//	char* assem;
			Temp_tempList *dst, *src;
			AS_Targets* jumps;
		}
		OPER;
		struct
		{
		//	char* assem;
			Temp_tempList *dst, *src;
		}
		MOVE;

		struct
		{
		//	char* assem;
			Temp_label* label;
		}
		LABEL;
	};
};

struct CodeCompExt AS_instrList
{
	AS_instrList(AS_instr* _head, AS_instrList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	AS_instr* head;
	AS_instrList* tail;
};

struct CodeCompExt FSymbol
{
	FSymbol()
	{
		Type = 0;
		Desc = 0;
	}
    SHORT   SectionNumber;
    uint16    Type;
    uint8    StorageClass;
	 uint32 Value;
	 uint16 Desc;

// IMAGE_SYMBOL
    union {
	 /*
        BYTE    ShortName[8];
        struct {
            DWORD   Short;     // if 0, use LongName
            DWORD   Long;      // offset into string table
        } Name;
        DWORD   LongName[2];    // PBYTE [2]
		  */
	 char* Name;
    } N;

	// cpp::CDeclarator* m_pDeclarator;
//	 cpp::CDeclarator* m_pDeclarator;
//	 Temp_label* m_tempLabel;
};

struct CodeCompExt FRelocation
{
	FRelocation()
	{
		VirtualAddress = -1;
	//	SymbolTableIndex = 0;
		//Type = 
		tempLabel = NULL;
		Type = 0;
	}

   uint16 Type;

//	RelocConst* pRelocConst;
	ULONG_PTR VirtualAddress;
//   DWORD SymbolTableIndex;
	Temp_label* tempLabel;
};

class CodeCompExt CObjectFile
{
public:
	virtual int AddSymbol(const char* name, FSymbol** ppSymbol) = 0;
//	virtual IMAGE_SYMBOL* GetSymbolRef(int index) = 0;
	virtual int Create(std::FILE* fp, cpp::CGlobal* pGlobal, System::Scope* pGlobalScope, const vector<T_Declarator*>& globals, CFunctionCode* pFunctionCode, int cpu) = 0;
};

class RelativeLabel
{
public:
	RelativeLabel(ULONG_PTR address, Temp_label* label)
	{
		m_address = address;
		m_label = label;
	}
	ULONG_PTR m_address;
	Temp_label* m_label;
};

class CodeCompExt CFunctionCode
{
public:
	CFunctionCode()
	{
		m_pFunc = NULL;
		instrList = NULL;
		instrListTail = NULL;
	}

	~CFunctionCode()
	{
		for (unsigned int i = 0; i < m_ImageRelocation.GetSize(); i++)
		{
			delete m_ImageRelocation[i];
		}
	}

	AS_instrList* instrList;
	AS_instrList* instrListTail;

	void emit(AS_instr* inst);

	int m_spOffset;

	void AddRelocation(FRelocation* pReloc)
	{
		ASSERT(pReloc);
		ASSERT(pReloc->tempLabel);

		/*
		if (pReloc->SymbolTableIndex == -1)
		{
			printf("");
		}
		*/

		m_ImageRelocation.Add(pReloc);
	}

	vector<RelativeLabel> m_labels;

//	int m_numberOfRelocations;
//	IMAGE_RELOCATION* ;
	System::FunctionType* m_pFunc;
//	cpp::CFunctionBody* m_pBody;
	T_StmList* m_pBody;

	CObjectFile* m_ofile;

	vector<FRelocation*> m_ImageRelocation;
};

class CodeCompExt CCodeGenerator
{
public:
	CCodeGenerator()
	{
	//	m_pLabel = NULL;

		m_processor_id = -1;
	}

	int m_processor_id;

	int reg;/*EAX*/

//	int dreg;
//	int areg;

	//BYTE get

	stack<CLabel*> m_labelStack;
//	CLabel* m_pLabel;

//	void branch();
//	void branch_to();

#if 0
	void SetLabelPos(CLabel* pLabel);

	CLabel* PushLabel()
	{
		//ASSERT(m_pLabel == NULL);
		//m_pLabel = new CLabel;
		CLabel* pLabel = new CLabel;
		m_labelStack.push(pLabel);

		return pLabel;
	}
#endif
	void FlushLabel(Temp_label* pLabel);

	std::FILE* m_fileout;

	ULONG GetCounter()
	{
		return std::ftell(m_fileout);
	}

//	virtual int emit_expr(CFunctionCode* pFunc, cpp::CExpression* pExpr, ea *pDestEA, ea *pValue = NULL);//, int mov = TRUE);
//	int emit_expr2(CFunctionCode* pFunc, cpp::CExpression* pExpr, ea *pDestEA);

//	virtual void Function(FILE* fp, CFunctionCode* pFunc);

	virtual void WriteStatement(CFunctionCode* pFunc, T_Stm* pstmt) = 0;
	virtual void Function_Prologue(CFunctionCode* pFunc) = 0;
	virtual void Function_Epilogue(CFunctionCode* pFunc) = 0;

	virtual void WriteStatement2(CFunctionCode* pFun, T_Stm* s)
	{
		ASSERT(0);
	}

};

//CodeCompExt AS_instr* AS_Oper(int n, Temp_tempList* d, Temp_tempList* s, AS_Targets* j = NULL);
//CodeCompExt AS_instr* AS_Move(int n, Temp_tempList* d, Temp_tempList* s);

CodeCompExt AS_instr* AS_Oper(MInstruction* assem, Temp_tempList* d, Temp_tempList* s, AS_Targets* j = NULL);
CodeCompExt AS_instr* AS_Move(MInstruction* assem, Temp_tempList* d, Temp_tempList* s);
CodeCompExt AS_instr* AS_Data(uint8* buffer, long size);
CodeCompExt AS_instr* AS_Data2(T_ExpList* explist);
CodeCompExt AS_instr* AS_Label(Temp_label* label);
CodeCompExt AS_instr* AS_Fun(T_Declarator* declarator);
CodeCompExt AS_instr* AS_Line(int line);
CodeCompExt AS_instr* AS_Source(const char* filename);
CodeCompExt AS_instr* AS_LBrac();
CodeCompExt AS_instr* AS_RBrac();
CodeCompExt AS_instr* AS_LSym(T_Declarator* declarator);
CodeCompExt AS_instr* AS_Align(int nbytes);

//}	// cpp

}

#endif // __CODEGEN_H_
