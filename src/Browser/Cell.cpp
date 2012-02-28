#include "stdafx.h"
#include "Browser.h"
#include "SpreadSheet.h"

namespace System
{

void Cell::Evaluate()
{
	stack<double> stack;

	uint8* p = m_formula->data;
	while (p < m_formula->data + m_formula->size)
	{
		uint8 tokid = *p++;
		if (tokid == Excel::ptgInt)
		{
			uint16 value;
			value = *p++;
			value |= (*p++)<<8;

			stack.push(value);

		}
		else if (tokid == Excel::ptgNumber)
		{
			uint8 bytes[8];
			bytes[0] = *p++;
			bytes[1] = *p++;
			bytes[2] = *p++;
			bytes[3] = *p++;
			bytes[4] = *p++;
			bytes[5] = *p++;
			bytes[6] = *p++;
			bytes[7] = *p++;

			double value;
			value = *(double*)&bytes;

			TRACE("%f ", value);
		}
		else if (tokid == Excel::ptgAdd)
		{
		//	TRACE("+ ");

			double tok1 = stack.top();
			stack.pop();

			double tok2 = stack.top();
			stack.pop();

			stack.push(tok2 + tok1);
		}
		else if (tokid == Excel::ptgSub)
		{
			TRACE("- ");
		}
		else if (tokid == Excel::ptgMul)
		{
			//TRACE("* ");

			double tok1 = stack.top();
			stack.pop();

			double tok2 = stack.top();
			stack.pop();

			stack.push(tok2 * tok1);
		//	list.push_back(tok1 + "*" + tok2);
		}
		else if (tokid == Excel::ptgParen)
		{
			/*
			StringA tok = stack.top();
			stack.pop();

			stack.push("(" + tok + ")");

			TRACE(") ");
			*/
		}
		else if (tokid == Excel::ptgAttr)
		{
			uint8 flag = *p++;
			uint16 number = *p++;
			number |= (*p++)<<8;

			if (flag & 0x04)
			{
				number++;
				number <<= 1;
				while (number--)
				{
					p++;
				}
			}
			else if (flag & 0x10)
			{
				ASSERT(0);
			}
		}
		else if (tokid == Excel::ptgRefV)
		{
			if (true)	// BIFF8
			{
				uint16 row = *p++;
				row |= (*p++)<<8;

				uint16 col = *p++;
				col |= (*p++)<<8;

				int fcolRelative = col & 0x4000;
				int frowRelative = col & 0x8000;

				col &= 255;	// The column is in the 8 lower bits

				if (fcolRelative) col += m_col;
				if (frowRelative) row += m_row;

				Row* pRow = m_pSheet->m_rows[row];
				if (pRow)
				{
					Cell* pCell = pRow->m_cells[col];
					if (pCell)
					{
						stack.push(pCell->GetValue());
					}
					else
						stack.push(0);
				}
				else
					stack.push(0);
			}
			else
			{
				ASSERT(0);
			}
		}
		else
			ASSERT(0);
	}

	m_value = stack.top();
	stack.pop();

	ASSERT(stack.size() == 0);

	m_bValidValue = true;
}

void Cell::SetFormula(Excel::FormulaTokens* formula)
{
			ASSERT(0);
#if 0
	m_formula = formula;

	stack<StringA> stack;

	uint8* p = m_formula->data;
	while (p < m_formula->data + m_formula->size)
	{
		uint8 tokid = *p++;
		if (tokid == Excel::ptgInt)
		{
			uint16 value;
			value = *p++;
			value |= (*p++)<<8;

			char buf[16];
			sprintf(buf, "%d", value);

			stack.push(buf);

			TRACE("%d ", value);
		}
		else if (tokid == Excel::ptgNumber)
		{
			uint8 bytes[8];
			bytes[0] = *p++;
			bytes[1] = *p++;
			bytes[2] = *p++;
			bytes[3] = *p++;
			bytes[4] = *p++;
			bytes[5] = *p++;
			bytes[6] = *p++;
			bytes[7] = *p++;

			double value;
			value = *(double*)&bytes;

			TRACE("%f ", value);
		}
		else if (tokid == Excel::ptgAdd)
		{
			StringA tok1 = stack.top();
			stack.pop();

			StringA tok2 = stack.top();
			stack.pop();

			stack.push(tok2 + "+" + tok1);
		}
		else if (tokid == Excel::ptgSub)
		{
			TRACE("- ");
		}
		else if (tokid == Excel::ptgMul)
		{
			//TRACE("* ");

			StringA tok1 = stack.top();
			stack.pop();

			StringA tok2 = stack.top();
			stack.pop();

			stack.push(tok2 + "*" + tok1);
		//	list.push_back(tok1 + "*" + tok2);
		}
		else if (tokid == Excel::ptgParen)
		{
			StringA tok = stack.top();
			stack.pop();

			stack.push("(" + tok + ")");
		}
		else if (tokid == Excel::ptgAttr)
		{
			uint8 flag = *p++;
			uint16 number = *p++;
			number |= (*p++)<<8;

			if (flag & 0x04)
			{
				number++;
				number <<= 1;
				while (number--)
				{
					p++;
				}
			}
			else if (flag & 0x10)
			{
				ASSERT(0);
			}
		}
		else if (tokid == Excel::ptgRefV)
		{
			if (true)	// BIFF8
			{
				uint16 row = *p++;
				row |= (*p++)<<8;

				uint16 col = *p++;
				col |= (*p++)<<8;

				int fcolRelative = col & 0x4000;
				int frowRelative = col & 0x8000;

				col &= 255;	// The column is in the 8 lower bits

				if (fcolRelative) col += m_col;
				if (frowRelative) row += m_row;

				char buf[64];
				sprintf(buf, "%c%d", 'A' + col, row+1);

				stack.push(buf);

				CellRef cellref;
				cellref.row = row;
				cellref.col = col;
				m_dependencies.Add(cellref);
			}
			else
			{
				ASSERT(0);
			}
		}
		else
			ASSERT(0);
	}

	StringA value = stack.top();
	stack.pop();
	ASSERT(stack.size() == 0);

	m_stringValue = "=";
	m_stringValue += value;
#endif
}

}
