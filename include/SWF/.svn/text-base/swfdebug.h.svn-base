//#undef new

/*
namespace std
{
#include <wchar.h>
#include <stdlib.h>

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
}

// Hack
typedef int mbstate_t;
#include <xlocinfo.h>
*/

#include <string>
#include <sstream>

#include "ActionNames.h"

namespace System
{
namespace SWF
{

using namespace ActionScripting;

class SWFExt VM2
{
public:

	class StkElt
	{
	public:

		enum Kind
		{
			KIND_STRING,
			KIND_INT,
			KIND_FLOAT,
		}
		m_kind;

		CTOR StkElt(const std::string& str) : m_kind(KIND_STRING), m_str(str)
		{
		}

		CTOR StkElt(int32 val) : m_kind(KIND_INT)
		{
			u.m_intVal = val;
		}

		CTOR StkElt(float val) : m_kind(KIND_FLOAT)
		{
			u.m_floatVal = val;
		}

		int toInt()
		{
			switch (m_kind)
			{
			case KIND_INT:
				return u.m_intVal;

			default:
				VERIFY(0);
			}
			return -1;
		}

		std::string str()
		{
			if (m_str.length() == 0)
			{
				switch (m_kind)
				{
				case KIND_INT:
					{
						std::stringstream stream;
						stream << u.m_intVal;
						m_str = stream.str();
					}
					break;

				case KIND_FLOAT:
					{
						std::stringstream stream;
						stream << u.m_floatVal;
						m_str = stream.str();
					}
					break;
				}
			}

			return m_str;
		}

		union
		{
			int m_intVal;
			float m_floatVal;
		}
		u;

		std::string m_str;
	};

	class ActionContext : public System::Object
	{
	public:
		vector<StkElt> m_constantPool;

	//	map<System::StringA*, ActionScriptFunction*, Ref_Less<System::StringA> > m_funmap;
	};

	class StackFrame
	{
	public:
		ActionContext* m_pContext;
		uint8* m_instructionsData;
		unsigned int m_instructionsLength;
	};

	class LineNumber
	{
	public:

		CTOR LineNumber(uint16 _pc, uint16 _line)
		{
			pc = _pc;
			line = _line;
		}

		uint16 pc;
		uint16 line;
	};

	CTOR VM2()
	{
		m_nlines = 0;
	}

	bool next();

	vector<LineNumber> lines;

	uint8* pc;
	unsigned int m_startpc;
	unsigned int m_nlines;

	//ULONG length;

	std::stringstream m_str;

	typedef void (VM2::*tyasfunc)(ULONG length);

	static tyasfunc asfuncs[256];

	StackFrame* m_pFrame;
	int level;

//	std::vector<StkElt> m_stack;
//	void push(StkElt value);
//	StkElt pop();

	vector<StkElt> m_stack;
	void push(StkElt value);
	StkElt pop();

	void as_notimpl(ULONG length);
	void as_If(ULONG length);
	void as_ConstantPool(ULONG length);
	void as_Push(ULONG length);
	void as_Pop(ULONG length);
	void as_CallFunction(ULONG length);
	void as_CallMethod(ULONG length);
	void as_GetVariable(ULONG length);
	void as_SetVariable(ULONG length);
	void as_GetMember(ULONG length);
	void as_SetMember(ULONG length);
	void as_With(ULONG length);
	void as_DefineFunction(ULONG length);
	void as_Add2(ULONG length);
	void as_NextFrame(ULONG length);
	void as_Play(ULONG length);
	void as_SetTarget(ULONG length);
};

}
}
