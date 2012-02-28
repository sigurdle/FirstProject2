#include "stdafx.h"
#include "Browser.h"

#include "OleCompoundFile.h"
#include "SpreadSheet.h"
#include "msodrawing.h"

namespace System
{
using namespace IO;

Workbook* m_pWorkbook;

namespace Excel
{

uint32 defaultColors[56] =
{
0x000000,// 0 0 0 [Black] 
0xFFFFFF, // #FFFFFF 255 255 255 [White] 
0xFF0000,// #FF0000 255 0 0 [Red] 
0x00FF00,// #00FF00 0 255 0 [Green] 
0x0000FF,// #0000FF 0 0 255 [Blue] 
0xFFFF00,// #FFFF00 255 255 0 [Yellow] 
0xFF00FF,// #FF00FF 255 0 255 [Magenta] 
0x00FFFF,// #00FFFF 0 255 255 [Cyan] 
0x800000,// #800000 128 0 0 [Color 9] 
0x008000,// #008000 0 128 0 [Color 10] 
0x000080,// #000080 0 0 128 [Color 11] 
0x808000,// #808000 128 128 0 [Color 12] 
0x800080,// #800080 128 0 128 [Color 13] 
0x008080,// #008080 0 128 128 [Color 14] 
0xC0C0C0,// #C0C0C0 192 192 192 [Color 15] 
0x808080,// #808080 128 128 128 [Color 16] 
0x9999FF,// #9999FF 153 153 255 [Color 17] 
0x993366,// #993366 153 51 102 [Color 18] 
0xFFFFCC,// #FFFFCC 255 255 204 [Color 19] 
0xCCFFFF,// #CCFFFF 204 255 255 [Color 20] 
0x660066,// #660066 102 0 102 [Color 21] 
0xFF8080,// #FF8080 255 128 128 [Color 22] 
0x0066CC,// #0066CC 0 102 204 [Color 23] 
0xCCCCFF,// #CCCCFF 204 204 255 [Color 24] 
0x000080,// #000080 0 0 128 [Color 25] 
0xFF00FF,// #FF00FF 255 0 255 [Color 26] 
0xFFFF00,// #FFFF00 255 255 0 [Color 27] 
0x00FFFF,// #00FFFF 0 255 255 [Color 28] 
0x800080,// #800080 128 0 128 [Color 29] 
0x800000,// #800000 128 0 0 [Color 30] 
0x008080,// #008080 0 128 128 [Color 31] 
0x0000FF,// #0000FF 0 0 255 [Color 32] 
0x00CCFF,// #00CCFF 0 204 255 [Color 33] 
0xCCFFFF,// #CCFFFF 204 255 255 [Color 34] 
0xCCFFCC,// #CCFFCC 204 255 204 [Color 35] 
0xFFFF99,// #FFFF99 255 255 153 [Color 36] 
0x99CCFF,// #99CCFF 153 204 255 [Color 37] 
0xFF99CC,// #FF99CC 255 153 204 [Color 38] 
0xCC99FF,// #CC99FF 204 153 255 [Color 39] 
0xFFCC99,// #FFCC99 255 204 153 [Color 40] 
0x3366FF,// #3366FF 51 102 255 [Color 41] 
0x33CCCC,// #33CCCC 51 204 204 [Color 42] 
0x99CC00,// #99CC00 153 204 0 [Color 43] 
0xFFCC00,// #FFCC00 255 204 0 [Color 44] 
0xFF9900,// #FF9900 255 153 0 [Color 45] 
0xFF6600,// #FF6600 255 102 0 [Color 46] 
0x666699,// #666699 102 102 153 [Color 47] 
0x969696,// #969696 150 150 150 [Color 48] 
0x003366,// #003366 0 51 102 [Color 49] 
0x339966,// #339966 51 153 102 [Color 50] 
0x003300,// #003300 0 51 0 [Color 51] 
0x333300,// #333300 51 51 0 [Color 52] 
0x993300,// #993300 153 51 0 [Color 53] 
0x993366,// #993366 153 51 102 [Color 54] 
0x333399,// #333399 51 51 153 [Color 55] 
0x333333 
};

/*
class Polyline : public Shape
{
public:

};
*/

class RecordsStream : public System::Object, public ISequentialByteStream
{
public:
	RecordsStream()
	{
		m_pos = 0;
		m_size = 0;
	}

	/*
	ULONG AddRef()
	{
		return _Object::AddRef();
	}

	ULONG Release()
	{
		return _Object::Release();
	}
	*/

	ULONG m_pos;
	ULONG m_size;

	OLE::Stream* m_pStream;

	class Record
	{
	public:
		ULONG m_pos;
		ULONG m_len;
	};

	vector<Record> m_records;

	ULONG Read(void* pv, ULONG pos, ULONG cb)
	{
		int nRecord = 0;//m_records.begin();

		ULONG recordpos = pos;
		while (recordpos >= m_records[nRecord].m_len)
		{
			if (nRecord == m_records.GetSize())
				return 0;

			recordpos -= m_records[nRecord].m_len;
			nRecord++;
		}

		uint8* pb = (uint8*)pv;
		ULONG n = 0;
		while (n < cb)
		{
			if (nRecord == m_records.GetSize())
				return n;

			ULONG count = cb-n;

			if (recordpos + count > m_records[nRecord].m_len)
			{
				count = m_records[nRecord].m_len - recordpos;
			}

			count = m_pStream->Read(pb, m_records[nRecord].m_pos + recordpos, count);

			n += count;
			pb += count;
			recordpos = 0;
			nRecord++;
		}

		return n;
	}

	virtual ULONG Read(void* pv, ULONG cb)
	{
		ULONG n = Read(pv, m_pos, cb);
		m_pos += n;
		return n;
	}

	virtual LONGLONG Seek(LONGLONG offset, IO::SeekOrigin origin)
	{
		if (origin == System::IO::STREAM_SEEK_SET)
		{
			m_pos = offset;
		}
		else if (origin == System::IO::STREAM_SEEK_CUR)
		{
			m_pos += offset;
		}
		else
		{
			ASSERT(0);
			THROW(-1);
		}

		return m_pos;
	}

	virtual LONGLONG GetSize()
	{
		return m_size;
	}

	virtual ISequentialByteStream* Clone() const
	{
		THROW(-1);
		return 0;
	}

	virtual ULONG Write(const void* pv, ULONG cb)
	{
		THROW(-1);
		return -1;
	}
};

void ReadWorksheet(OLE::Stream* pStream, Sheet* pSheet)
{
	//std::vector<XF*> m_XF;

	//uint8* buffer = new uint8[8224];

	RecordsStream* pDrawingStream = new RecordsStream;
//	pDrawingStream->AddRef();
	pDrawingStream->m_pStream = pStream;

	MSODrawing::DrawingLoader loader;
	loader.m_pContainerStream = pStream;

	RECORDHEADER record;
	ULONG nRead = pStream->Read(&record, sizeof(record));

	while (nRead != 0)
	{
		ULONG pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		switch (record.id)
		{
		case ID_FORMAT:
			{
				if (true)	// BIFF8
				{
				}
				else
				{
				}
			}
			break;

		case ID_XF:
			{
				ASSERT(0);
				//MessageBeep(-1);
				/*
				XF* xf = new XF;
				
				  uint16 ifnt;
				  uint16 ifmt;
				  uint16 type;
				  pStream->Read(&ifnt, 2);
				  pStream->Read(&ifmt, 2);
				  pStream->Read(&type, 2);
				  
					 //	uint16 type;
					 //	pStream->Read(&ifnt, 2);
					 
						
						  if (((type>>2) & 1) == 0)
						  {
						  uint16 iparent = type>>4;
						  if (iparent > 0)
						  {
						  xf->m_pParent = pWorkbook->m_XF[iparent-1];
						  }
						  }
						  
							 pWorkbook->m_XF.Add(xf);
				*/
			}
			break;
			
		case ID_FONT:
			{
				ASSERT(0);
				TRACE("FONT %d\n", record.size);
			}
			break;
			
		case ID_FORMULA:
			{
				TRACE("FORMULA %d\n", record.size);
				
				uint16 rowIndex;
				uint16 colIndex;
				uint16 XFRecord;
				pStream->Read(&rowIndex, 2);
				pStream->Read(&colIndex, 2);
				pStream->Read(&XFRecord, 2);
				
				Row* pRow = pSheet->m_rows[rowIndex];
				if (pRow == NULL)
				{
					pRow = new Row;
					pSheet->m_rows[rowIndex] = pRow;
				}
				
				Column* pColumn = pSheet->m_columns[colIndex];
				if (pColumn == NULL)
				{
					pColumn = new Column;
					pSheet->m_columns[colIndex] = pColumn;
				}
				
				Cell* pCell = new Cell;
				pCell->m_pSheet = pSheet;
				pCell->m_col = colIndex;
				pCell->m_row = rowIndex;
				pCell->m_xfIndex = XFRecord;
				
				pRow->m_cells[colIndex] = pCell;
				
				//	TRACE("%d", XFRecord);
				
				double result;
				pStream->Read(&result, 8);
				
				uint16 flags;
				pStream->Read(&flags, 2);
				
				uint32 reserved;
				pStream->Read(&reserved, 4);
				
				uint16 sz;
				if (false)	// BIFF2
				{
					uint8 _sz;
					pStream->Read(&_sz, 1);
					sz = _sz;
				}
				else
				{
					pStream->Read(&sz, 2);
				}
				
				uint8* tokarray = new uint8[sz];
				pStream->Read(tokarray, sz);
				uint8* tokarray_end = tokarray+sz;
				
				FormulaTokens* pFormula = new FormulaTokens;
				pFormula->data = tokarray;
				pFormula->size = sz;
				pCell->SetFormula(pFormula);
				
			}
			break;
			
		case ID_LABEL:
			{
				ASSERT(0);
			}
			break;
			
		case ID_LABELSST:
			{
				uint16 rowIndex;
				uint16 colIndex;
				pStream->Read(&rowIndex, 2);
				pStream->Read(&colIndex, 2);
				
				uint16 XFRecord;
				pStream->Read(&XFRecord, 2);

				uint32 SSTIndex;
				pStream->Read(&SSTIndex, 4);

				Row* pRow = pSheet->m_rows[rowIndex];
				if (pRow == NULL)
				{
					pRow = new Row;
					pSheet->m_rows[rowIndex] = pRow;
				}
				
				Column* pColumn = pSheet->m_columns[colIndex];
				if (pColumn == NULL)
				{
					pColumn = new Column;
					pSheet->m_columns[colIndex] = pColumn;
				}
				
				Cell* pCell = new Cell;
				pCell->m_pSheet = pSheet;
				pCell->m_col = colIndex;
				pCell->m_row = rowIndex;
				pCell->m_xfIndex = XFRecord;
				
				pRow->m_cells[colIndex] = pCell;

				pCell->m_pStringContent = pSheet->m_pWorkbook->m_sharedStrings[SSTIndex];
			}
			break;
			
		case ID_RK:
			{
				TRACE("RK %d\n", record.size);
				
				uint16 rowIndex;
				uint16 colIndex;
				pStream->Read(&rowIndex, 2);
				pStream->Read(&colIndex, 2);
				
				uint16 XFRecord;
				pStream->Read(&XFRecord, 2);
				
				uint32 rk;
				pStream->Read(&rk, 4);
				
				double value;
				
				if (rk & 2)	// integer
				{
					value = (double)(rk>>2);	// TODO, sign extend
					if (rk & 1) value /= 100;
				}
				else
				{
				}
			}
			break;
			
		case ID_NUMBER:
			{
				TRACE("NUMBER %d\n", record.size);
			}
			break;
			
		case ID_DIMENSIONS:
			{
				TRACE("DIMENSIONS %d\n", record.size);
			}
			break;
			
		case ID_COLINFO:
			{
				uint16 colFirst;
				uint16 colLast;
				uint16 colWidth;
				uint16 iXF;
				pStream->Read(&colFirst, 2);
				pStream->Read(&colLast, 2);
				pStream->Read(&colWidth, 2);
				pStream->Read(&iXF, 2);
				
				for (int i = colFirst; i <= colLast; i++)
				{
					Column* pCol = pSheet->m_columns[i];
					if (pCol == NULL)
					{
						pCol = new Column;
						pSheet->m_columns[i] = pCol;
					}
					
					double colw = colWidth / 256.0;
					colw *= pSheet->m_pWorkbook->m_charWidth;
					colw -= 0.72;
					
					pCol->SetPointWidth(colw);
					double px = pCol->GetPixelWidth();
				}
			}
			break;
			
		case ID_ROW:
			{
				uint16 nrow;
				uint16 colMic;
				uint16 colMac;
				uint16 rowHeight;	// specified in twips (1/20 pt).
				
				pStream->Read(&nrow, 2);
				pStream->Read(&colMic, 2);
				pStream->Read(&colMac, 2);
				pStream->Read(&rowHeight, 2);
				
				nrow &= ~0x8000;	// If this bit is set, standard height, but the height is set also when this bit is set
				
				Row* pRow = pSheet->m_rows[nrow];
				if (pRow == NULL)
				{
					pRow = new Row;
					pSheet->m_rows[nrow] = pRow;
				}
				pRow->SetPointHeight(rowHeight / 20.0);
			}
			break;
			
		case ID_DEFCOLWIDTH:
			{
				TRACE("DEFCOLWIDTH %d\n", record.size);
				
				uint16 colwidth;	// measured in characters
				pStream->Read(&colwidth, 2);
				
				pSheet->m_defColumnWidth = colwidth * pSheet->m_pWorkbook->m_charWidth;
			}
			break;
			
		case ID_STANDARDWIDTH:
			{
				TRACE("ID_STANDARDWIDTH %d\n", record.size);
				
				uint16 colwidth;	// measured in 1/256 characters
				pStream->Read(&colwidth, 2);
				
				pSheet->m_defColumnWidth = colwidth * pSheet->m_pWorkbook->m_charWidth / 256;
			}
			break;
			
		case ID_DEFAULTROWHEIGHT:
			{
				TRACE("DEFAULTROWHEIGHT %d\n", record.size);
			}
			break;
			
		case ID_WINDOW2:
			{
				TRACE("WINDOW2 %d\n", record.size);
			}
			break;
			
		case ID_SST:
			{
				TRACE("SST %d\n", record.size);
			}
			break;
			
		case ID_EXTSST:
			{
				TRACE("EXTSST %d\n", record.size);
			}
			break;
			
		case ID_MSODRAWING:
			{
				TRACE("MSODRAWING %d\n", record.size);
				
				do
				{
					ULONG cur = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
					
					RecordsStream::Record r;
					r.m_pos = cur;
					r.m_len = record.size;
					pDrawingStream->m_records.Add(r);
					pDrawingStream->m_size += record.size;
					
					pStream->Seek(record.size, System::IO::STREAM_SEEK_CUR);
					nRead = pStream->Read(&record, sizeof record);
				}
				while (record.id == ID_CONTINUE);

				continue;
			}
			break;

		case ID_TXO:
			{
				loader.m_posmap[pDrawingStream->m_size] = pos - sizeof record;
			}
			break;

		case ID_OBJ:
			{
				TRACE("OBJ %d\n", record.size);
				
				while (1)
				{
					RECORDHEADER record;
					pStream->Read(&record, sizeof(record));
					
					ULONG pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
					
					if (record.id == 0)
						break;
					
					if (record.id == 0x15)	// ftCmo
					{
						uint16 ot;
						pStream->Read(&ot, 2);
					}
					
					pStream->Seek(pos + record.size, System::IO::STREAM_SEEK_SET);
				}
			}
			break;
			
		case ID_EOF:
			{
				TRACE("EOF %d\n", record.size);
				break;
			}
			break;
			
		default:
			{
				TRACE("0x%x %d\n", record.id, record.size);
			}
		}

		pStream->Seek(pos + record.size, System::IO::STREAM_SEEK_SET);

		nRead = pStream->Read(&record, sizeof record);
	}

	if (pDrawingStream)
	{
		if (pDrawingStream->m_size)
		{
			pSheet->m_pDrawingGroup = new UI::UIElement;

			loader.m_blips = &pSheet->m_pWorkbook->m_blips;

			loader.Drawing(pDrawingStream, pDrawingStream->m_size, pSheet->m_pDrawingGroup);
		}

//		pDrawingStream->Release();
	}
}

void ReadWorkbookGlobals(OLE::Stream* pStream, Workbook* pWorkbook)
{
	RecordsStream* pDrawingStream = new RecordsStream;
//	pDrawingStream->AddRef();
	pDrawingStream->m_pStream = pStream;

	//std::vector<XF*> m_XF;

//	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < pStream->GetSize())//for (int j = 0; j < 3; j++)
	RECORDHEADER record;
	ULONG nRead = pStream->Read(&record, sizeof(record));

	while (nRead != 0)
	{

		ULONG pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.id == ID_BOF)
		{
			ASSERT(0);

		}
		else if (record.id == ID_INTERFACEHDR)
		{
			TRACE("ID_INTERFACEHDR %d\n", record.size);
		}
		else if (record.id == ID_INTERFACEEND)
		{
			TRACE("ID_INTERFACEEND %d\n", record.size);
		}
		else if (record.id == ID_ADDMENU_DELMENU)
		{
			TRACE("ID_ADDMENU_DELMENU %d\n", record.size);
		}
		else if (record.id == ID_WRITEACCESS)
		{
			TRACE("ID_WRITEACCESS %d\n", record.size);
		}
		else if (record.id == ID_CODENAME)
		{
			TRACE("ID_CODENAME %d\n", record.size);
		}
		else if (record.id == ID_DSF)
		{
			TRACE("ID_DSF %d\n", record.size);
		}
		else if (record.id == ID_TABID)
		{
			TRACE("ID_TABID %d\n", record.size);
		}
		else if (record.id == ID_FNGROUPCOUNT)
		{
			TRACE("ID_FNGROUPCOUNT %d\n", record.size);
		}
		else if (record.id == ID_WINDOWPROTECT)
		{
			TRACE("ID_WINDOWPROTECT %d\n", record.size);
		}
		else if (record.id == ID_PROTECT)
		{
			TRACE("ID_PROTECT %d\n", record.size);
		}
		else if (record.id == ID_PASSWORD)
		{
			TRACE("ID_PASSWORD %d\n", record.size);
		}
		else if (record.id == ID_PROT4REV)
		{
			TRACE("ID_PROT4REV %d\n", record.size);
		}
		else if (record.id == ID_PROT4REVPASS)
		{
			TRACE("ID_PROT4REVPASS %d\n", record.size);
		}
		else if (record.id == ID_WINDOW1)
		{
			TRACE("ID_WINDOW1 %d\n", record.size);
		}
		else if (record.id == ID_BOOKBOOL)
		{
			TRACE("ID_BOOKBOOL %d\n", record.size);
		}
		else if (record.id == ID_REFRESHALL)
		{
			TRACE("ID_REFRESHALL %d\n", record.size);
		}
		else if (record.id == ID_STYLE)
		{
			TRACE("ID_STYLE %d\n", record.size);
		}
		else if (record.id == ID_USESELFS)
		{
			TRACE("ID_USESELFS %d\n", record.size);
		}
		else if (record.id == ID_BOUNDSHEET)
		{
			TRACE("ID_BOUNDSHEET Sheet Information %d\n", record.size);
		}
		else if (record.id == ID_COUNTRY)
		{
			TRACE("ID_COUNTRY Sheet Information %d\n", record.size);
		}
		else if (record.id == ID_SST)
		{
			TRACE("ID_SST Shared String Table %d\n", record.size);

			uint32 numberOfStrings;
			pStream->Read(&numberOfStrings, 4);

			uint32 followingStrings;
			pStream->Read(&followingStrings, 4);

			for (int i = 0; i < followingStrings; i++)
			{
				StringEntry* pEntry = new StringEntry;

				uint16 length;
				pStream->Read(&length, 2);

				uint8 flags;
				pStream->Read(&flags, 1);

				uint16 rt = 0;
				if (flags & 8)	// rich text
				{
					pStream->Read(&rt, 2);
				}

				if (flags & 1)	// Wide char
				{
					for (int i = 0; i < length; i++)
					{
						WCHAR ch;
						pStream->Read(&ch, 2);
						pEntry->m_str += ch;
					}
				}
				else	// Byte char
				{
					for (int i = 0; i < length; i++)
					{
						char ch;
						pStream->Read(&ch, 1);
						pEntry->m_str += ch;
					}
				}

				for (int i = 0; i < rt; i++)
				{
					TextRun run;
					pStream->Read(&run.charIndex, 2);

					uint16 ifnt;
					pStream->Read(&ifnt, 2);
					ASSERT(ifnt != 4);
					if (ifnt > 4)	// Skip the fourth index
						ifnt--;

					run.fontIndex = ifnt;

					pEntry->m_textRuns.Add(run);
				}

				pWorkbook->m_sharedStrings.Add(pEntry);
			}
		}
		else if (record.id == ID_EXTSST)
		{
			TRACE("ID_EXTSST %d\n", record.size);

			uint16 n;	// Number of strings in each portion
			pStream->Read(&n, 16);

		}
		else if (record.id == ID_1904_DATE)
		{
			TRACE("ID_1904_DATE %d\n", record.size);
		}
		else if (record.id == ID_BACKUP)
		{
			TRACE("ID_BACKUP %d\n", record.size);
		}
		else if (record.id == ID_HIDEOBJ)
		{
			TRACE("ID_HIDEOBJ %d\n", record.size);
		}
		else if (record.id == ID_PRECISION)
		{
			TRACE("ID_PRECISION %d\n", record.size);
		}
		else if (record.id == ID_FORMAT)
		{
			TRACE("ID_FORMAT %d\n", record.size);

			if (true)	// BIFF8
			{
			}
			else
			{
			}
		}
		else if (record.id == ID_XF)
		{
			//MessageBeep(-1);

			XF* xf = new XF;

			uint16 ifnt;
			uint16 ifmt;
			uint16 type;
			pStream->Read(&ifnt, 2);
			pStream->Read(&ifmt, 2);
			pStream->Read(&type, 2);

			ASSERT(ifnt != 4);
			if (ifnt > 4)	// Skip the fourth index
				ifnt--;

			xf->m_fontIndex = ifnt;

			uint16 flags;
			pStream->Read(&flags, 2);

			xf->m_vertAlign = (flags >> 4) & 7;

			if (((type>>2) & 1) == 0)	// Cell XF
			{
				uint16 iparent = type>>4;
			//	if (iparent > 0)
				{
					xf->m_pParent = pWorkbook->m_XF[iparent];
				}
			}

			pWorkbook->m_XF.Add(xf);
		}
		else if (record.id == ID_FONT)
		{
			TRACE("FONT %d\n", record.size);

			uint16 dyHeight;
			uint16 grbit;
			short colorIndex;
			uint16 boldStyle;
			uint16 sss;	// Superscript/subscript
			uint8 underlineStyle;
			uint8 bFamily;	// Font family, as defined by the Windows API LOGFONT structure
			uint8 bCharSet;
			uint8 reserved;
			uint8 cch;
			WCHAR name[256] = {0};

			pStream->Read(&dyHeight, 2);
			pStream->Read(&grbit, 2);
			pStream->Read(&colorIndex, 2);
			pStream->Read(&boldStyle, 2);
			pStream->Read(&sss, 2);
			pStream->Read(&underlineStyle, 1);
			pStream->Read(&bFamily, 1);
			pStream->Read(&bCharSet, 1);
			pStream->Read(&reserved, 1);
			pStream->Read(&cch, 1);

			/*
enum
{
	FIRST_COLOR_INDEX = 0x8
};

  */
			colorIndex -= 8;//FIRST_COLOR_INDEX;
		//	colorIndex &= (1<<6)-1;

			{
				uint8 flags;
				pStream->Read(&flags, 1);
				if (flags & 1)	// Wide char
				{
					pStream->Read(name, cch<<1);
				}
				else	// Byte char
				{
					for (int i = 0; i < cch; i++)
					{
						pStream->Read(&name[i], 1);
					}
				}
			}

			Font* pFont = new Font;
			pFont->m_ptHeight = dyHeight / 20.0;
			pFont->m_name = new StringW(string_copy(name));
			pFont->m_italic = (grbit>>1) & 1;
			pFont->m_bold = boldStyle > 400;
			pFont->m_colorIndex = colorIndex;

			pWorkbook->m_fonts.Add(pFont);
		}
		else if (record.id == ID_PALETTE)
		{
			TRACE("ID_PALETTE %d\n", record.size);

			uint16 count;
			pStream->Read(&count, 2);

			for (int i = 0; i < count; i++)
			{
				uint8 rgb[4];
				pStream->Read(rgb, 4);

				PaletteEntry entry;// = new PaletteEntry;
				entry.m_rgb = LDraw::Color(rgb[0], rgb[1], rgb[2]);//LDraw::Color::FromCOLORREF(crgb);
				pWorkbook->m_palette[i] = entry;
			}
		}
		else if (record.id == ID_MSODRAWINGGROUP)
		{
			TRACE("MSODRAWINGGROUP %d\n", record.size);

			do
			{
				ULONG cur = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

				RecordsStream::Record r;
				r.m_pos = cur;
				r.m_len = record.size;
				pDrawingStream->m_records.Add(r);
				pDrawingStream->m_size += record.size;

				pStream->Seek(record.size, System::IO::STREAM_SEEK_CUR);
				nRead = pStream->Read(&record, sizeof record);
			}
			while (record.id == ID_CONTINUE);

			continue;
		}
		else if (record.id == ID_EOF)
		{
			TRACE("EOF %d\n", record.size);
			break;
		}
		else
		{
			TRACE("0x%x %d\n", record.id, record.size);
		}

		pStream->Seek(pos + record.size, System::IO::STREAM_SEEK_SET);

		nRead = pStream->Read(&record, sizeof record);
	}

	if (pDrawingStream)
	{
		if (pDrawingStream->m_size)
		{
		//	pSheet->m_pDrawingGroup = new UI::UIElement;

			MSODrawing::DrawingLoader loader;
			loader.m_blips = &pWorkbook->m_blips;

			loader.Drawing(pDrawingStream, pDrawingStream->m_size, NULL);
		}

	//	pDrawingStream->Release();
	}

	LDraw::Font* font = pWorkbook->m_fonts[0]->GetFont();

	ASSERT(0);
#if 0
	UI::Graphics graphics(new LDraw::GraphicsO());
	graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);
	pWorkbook->m_charWidth = graphics.MeasureString("0", 1, font);
#endif

	pWorkbook->m_charWidth *= (72 / 96.0);
}

void ReadWorkbook(OLE::Stream* pStream, Workbook* pWorkbook)
{
	/*
	RecordsStream* pDrawingStream = new RecordsStream;
	pDrawingStream->AddRef();
	pDrawingStream->m_pStream = pStream;
	*/

	//std::vector<XF*> m_XF;

//	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < pStream->GetSize())//for (int j = 0; j < 3; j++)
	RECORDHEADER record;
	ULONG nRead = pStream->Read(&record, sizeof(record));

	while (nRead != 0)
	{

		ULONG pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.id == ID_BOF)
		{
			BOF bof;
			pStream->Read(&bof, MIN(sizeof(bof), record.size));

			if (bof.Type == 5)	// Workbook globals
			{
				TRACE("BOF Workbook Globals\n");
				ReadWorkbookGlobals(pStream, pWorkbook);
			}
			else if (bof.Type == 6)
			{
				TRACE("BOF UIElement Basic Module\n");
			}
			else if (bof.Type == 0x10)
			{
				TRACE("BOF Worksheet\n");

				Sheet* pSheet = new Sheet;
				pSheet->m_pWorkbook = pWorkbook;

				ReadWorksheet(pStream, pSheet);

				pWorkbook->m_sheets.Add(pSheet);
			}
			else if (bof.Type == 0x20)
			{
				TRACE("BOF Chart\n");
			}
			else if (bof.Type == 0x40)
			{
				TRACE("BOF BIFF4 MacroSheet\n");
			}
			else if (bof.Type == 0x100)
			{
				TRACE("BOF BIFF4 Workbook Globals\n");
			}
			else
				TRACE("BOF\n");
		}
		else if (record.id == ID_EOF)
		{
			TRACE("EOF %d\n", record.size);
		}
		else
		{
			TRACE("0x%x %d\n", record.id, record.size);
		}

		pStream->Seek(pos + record.size, System::IO::STREAM_SEEK_SET);

		nRead = pStream->Read(&record, sizeof record);
	}

	/*
	if (pDrawingStream)
	{
		if (pDrawingStream->m_size)
		{
		//	pSheet->m_pDrawingGroup = new UI::UIElement;

			MSODrawing::DrawingLoader loader;
			loader.m_blips = &pWorkbook->m_blips;

			loader.Drawing(pDrawingStream, pDrawingStream->m_size, NULL);
		}

		pDrawingStream->Release();
	}

	LDraw::Font font = pWorkbook->m_fonts[0]->GetFont();
	pWorkbook->m_charWidth = Graphics(new LDraw::GraphicsO()).MeasureString("0", 1, &font);
	*/
}

}	// Excel

namespace OLE
{


Stream* Storage::OpenStream(DIRENTRY* direntry)
{
	Stream* pStream = new Stream;
	pStream->m_pStorage = this;

	pStream->m_size = direntry->StreamSize;

	int ind = direntry->FirstSID;
	while (ind != -2)
	{
		pStream->m_sectors.Add(ind);
		ind = m_pSID[ind];
	}

	return pStream;
}

struct Token
{
	enum
	{
		K_INTEGER,
		K_NUMBER,
		K_UNOP,
		K_ADD,
		K_MUL,
	}
	kind;

	union
	{
		int integer;
		double number;
		char unop;
		char binop;
	}
	u;
};

void Storage::Open(ISequentialByteStream* byteStream)
{
	m_data = byteStream;

	HEADER header;
	m_data->Read(&header, sizeof(header));

	uint32 SID[109];

	m_data->Read(SID, 109*4);

	uint32 SectorSize = 1<<header.SecSize;

	m_pSID = new uint32[(header.NumSectors<<header.SecSize) >> 2];

	{
		for (int i = 0; i < header.NumSectors; i++)
		{
			ULONGLONG fileOffset = 512 + SID[i] * SectorSize;
		//	uint8* sectorData = new uint8[SectorSize];

			m_data->Seek(fileOffset, System::IO::STREAM_SEEK_SET);
			m_data->Read(m_pSID + ((i<<header.SecSize)>>2), SectorSize);
			//m_pSID = (uint32*)sectorData;
			/*
			for (int i = 0; i < 64; i++)
			{
				TRACE("%d\n", *pSID);
				pSID++;
			}
			*/
		}
	}

	Stream* pStream = new Stream;
	pStream->m_pStorage = this;

	int ind = header.FirstSID;
	while (ind != -2)
	{
		pStream->m_sectors.Add(ind);
		ind = m_pSID[ind];
	}

	ULONG count = header.NumSectors * 2;

	for (int i = 1; i < 2; i++)
	{
		/*
		ULONGLONG fileOffset = 512 + header.FirstSID * SectorSize;
		uint8* sectorData = new uint8[SectorSize];

		m_data->Seek(fileOffset, System::IO::STREAM_SEEK_SET);
		m_data->Read(sectorData, SectorSize);
		*/

		DIRENTRY direntry;// = (DIRENTRY*)sectorData;
		pStream->Read(&direntry, i*128, 128);

		//for (int i = 0; i < 2; i++)
		{
			TRACE("%S Type: %d Size: %d Left: %d Right: %d Root: %d\n", direntry.Name, direntry.NodeType, direntry.StreamSize, direntry.LeftChildDID, direntry.RightChildDID, direntry.RootNodeDID);
		//	direntry++;
		}

		Stream* pStream = OpenStream(&direntry);

		m_pWorkbook = new Workbook;
		Excel::ReadWorkbook(pStream, m_pWorkbook);

		/*
		uint32* pSID = (uint32*)sectorData;
		while (*pSID != -2)
		{
			TRACE("%d\n", *pSID);
			pSID++;
		}
		*/
	}
}

}	// OLE

Workbook::Workbook()
{
	m_charWidth = 10.0;
	m_palette.SetSize(56);
	for (int i = 0; i < 56; i++)
	{
		uint32 rgb = Excel::defaultColors[i];
		m_palette[i].m_rgb = LDraw::Color(rgb>>16, (rgb>>8) & 0xFF, rgb & 0xFF);
	}
}

}
