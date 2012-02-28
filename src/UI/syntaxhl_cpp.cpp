/*
	cpp.c
	Copyright © 1996 BST Software, Sigurd Lerstad. All rights reserved.

	This is the C++ syntax parser for VisualEd
*/

#include "stdafx.h"

#include <stdio.h>
#include <string.h>

#include "syntax.h"

//BSTR* ReadStringTab(char* file);

/* ctype */
#define A	2		/* alpha */
#define N	4		/* numeric */
#define X	8		/* hex */
#define O	16		/* octal */
#define S	32		/* symbol */
#define W	64		/* whitespace */
#define C	128	/* special */

extern UBYTE ctype[];   /* At the end of this file */

#define BegEl	UserData.user0[0]
#define EndEl	UserData.user0[1]

/* Supported elements */
#define EL_WHITESPACE		0
#define EL_IDENTIFIER		1
#define EL_COMMENT         2
#define EL_CPPCOMMENT      3
#define EL_KEYWORD         4
#define EL_CPPKEYWORD      5
#define EL_SYMBOL          6
#define EL_INTEGER         7
#define EL_FLOAT           8
#define EL_OCTAL           9
#define EL_HEX             10
#define EL_STRING          11
#define EL_CHARACTER       12
#define EL_PREPROCESSOR    13
#define EL_ILLEGAL_CHAR    14
#define EL_USERWORD        15

#define EL_MAX             16

#define CONFIGFILE         "syntax/C-C++.config"

#define CLR_WHITE	RGB(255,255,255)
#define CLR_BLACK	RGB(0,0,0)
#define CLR_GREEN	RGB(0,160,0)
#define CLR_BLUE	RGB(0,0,200)
#define CLR_RED	RGB(200,0,0)

// The values here will be overwritten if an option file was found
struct SyntaxElement ElementArray[EL_MAX] =
{
	{CLR_WHITE,CLR_WHITE,	FS_NORMAL,	0},	/* Whitespace */
	{CLR_BLACK,CLR_WHITE,	FS_NORMAL,	0},	/* Identifier */
	{CLR_GREEN,CLR_WHITE,	FSF_ITALIC,	ELFL_ACTIVE},	/* ANSI Comment */
	{CLR_GREEN,CLR_WHITE,	FSF_ITALIC,	ELFL_ACTIVE},	/* CPP Comment */
	{CLR_BLUE,CLR_WHITE,		FSF_BOLD,		ELFL_ACTIVE},	/* Reserved ANSI Word */
	{CLR_BLUE,CLR_WHITE,		FS_NORMAL,	ELFL_ACTIVE},	/* Reserved CPP Word */
	{CLR_BLUE,CLR_WHITE,		FSF_BOLD,		ELFL_ACTIVE},	/* Symbol */
	{CLR_BLACK,CLR_WHITE,	FS_NORMAL,	ELFL_ACTIVE},	/* Integer */
	{CLR_BLACK,CLR_WHITE,	FS_NORMAL,	ELFL_ACTIVE},	/* Float */
	{CLR_BLACK,CLR_WHITE,	FS_NORMAL,	ELFL_ACTIVE},	/* Octal */
	{CLR_BLACK,CLR_WHITE,	FS_NORMAL,	ELFL_ACTIVE},	/* Hex */
	{CLR_BLACK,CLR_WHITE,	FS_NORMAL,	ELFL_ACTIVE},	/* String */
	{CLR_BLACK,CLR_WHITE,	FS_NORMAL,	ELFL_ACTIVE},	/* Character */
	{CLR_GREEN,CLR_WHITE,	FS_NORMAL,	ELFL_ACTIVE},	/* Preprocessor */
	{CLR_BLACK, CLR_RED,		FS_NORMAL,	ELFL_ACTIVE},	/* Illegal Char */
	{CLR_BLUE,CLR_WHITE,		FSF_BOLD,		ELFL_ACTIVE},	/* User word */
};

static BSTR KeywordsTab[] =
{
	L"break",
	L"case",
	L"char",
	L"chip",
	L"const",
	L"continue",
	L"default",
	L"do",
	L"double",
	L"else",
	L"enum",
	L"extern",
	L"far",
	L"float",
	L"for",
	L"goto",
	L"huge",
	L"if",
	L"int",
	L"long",
	L"near",
	L"register",
	L"return",
	L"short",
	L"signed",
	L"sizeof",
	L"static",
	L"struct",
	L"switch",
	L"typedef",
	L"union",
	L"unsigned",
	L"void",
	L"volatile",
	L"while",
};

#define KEYWORDSCOUNT	(sizeof(KeywordsTab)/sizeof(BSTR))

/*
static BSTR HighCPPTab[] =
{
	L"catch",
	L"class",
	L"delete",
	L"friend",
	L"inline",
	L"new",
	L"operator",
	L"private",
	L"protected",
	L"public",
	L"this",
	L"throw",
	L"try",
	L"virtual",
}
*/

//static BSTR  *UserTab;

/*************************************************************************************

   Compares s1 with s2 (s2 is s2len in length), exact match returns TRUE

*************************************************************************************/

/*************************************************************************************

   Searches an array for a string

*************************************************************************************/

static UWORD SearchArray(BSTR array[], int arrcount, BSTR find, UWORD len)
{
   if (array)
   {
      int high = arrcount-1;//((ULONG)array[-1])-1;
      int  low = 0;
      int  mid;

      while (low <= high)
      {
         BOOL  result;

         int mid = (low+high)/2;
         result = wcsncmp(array[mid], find, len);

         if (result < 0)
            low = mid+1;
         else if (result > 0)
            high = mid-1;
         else
            return (UWORD)mid;
      }
   }

   return (UWORD)~0;
}

static UBYTE ElementFlags[EL_MAX] =
{
	0,				/* Whitespace */
	SCF_HOLE,	/* Identifier */
	0,				/* ANSI Comment */
	0,				/* CPP Comment */
	SCF_HOLE,	/* Reserved ANSI Word */
	SCF_HOLE,	/* Reserved CPP Word */
	SCF_HOLE,	/* Symbol */
	SCF_HOLE,	/* Integer */
	SCF_HOLE,	/* Float */
	SCF_HOLE,	/* Octal */
	SCF_HOLE,	/* Hex */
	0,				/* String */
	0,				/* Character */
	0,				/* Preprocessor */
	SCF_HOLE,	/* Illegal Char */
	0,				/* User word */
};

/*************************************************************************************


*************************************************************************************/

static UWORD ParseWord(BSTR textData, UWORD col, UWORD linelength, UBYTE *el)
{
	UBYTE		*_ctype = ctype;
	WCHAR*	c = &textData[col];
	UBYTE		ctyp = ctype[*c];
	UWORD		wordlen;
	WCHAR*	p;
	UBYTE		element;

	ATLASSERT(*c < 256);

	p = c+1;

	if (_ctype[*c] & N)	/* It's a number of some kind */
	{
		if ((*c == '0') && ((*p == 'x') || (*p == 'X')))	/* Hexadecimal */
		{
			p++;	/* Skip the x */
			while (_ctype[*p] & X) p++;

			element = EL_HEX;
		}
		else if ((*c == '0') && (_ctype[*p] & N)) /* Octal */
		{
			while (_ctype[*p] & O) p++;

			element = EL_OCTAL;
		}
		else	/* Either integer or float */
		{
		/* TODO: interpret e (exponent) */

			while (_ctype[*p] & N) p++;

			if (*p == '.')	/* Float number, the decimal part comes now */
			{
				p++;
				while (_ctype[*p] & N) p++;

				element = EL_FLOAT;
			}
			else
				element = EL_INTEGER;
		}

	/* Check for l/u modifiers after numbers */
	/* NOTE: float cannot have unsigned modifier */
		if ((*p == 'l') || (*p == 'L'))
		{
			p++;
			if ((element != EL_FLOAT) &&	((*p == 'u') || (*p == 'U'))) p++;
		}
		else if ((element != EL_FLOAT) && ((*p == 'u') || (*p == 'U')))
		{
			p++;
			if ((*p == 'l') || (*p == 'L')) p++;
		}

		wordlen = p-c;

	/* Check if the following char makes this number illegal */
		if (_ctype[*p] & A) element = EL_ILLEGAL_CHAR;

	/* If this element isn't active set it to ANYTEXT */
		if (!(ElementArray[element].Flags & ELFL_ACTIVE)) element = EL_IDENTIFIER;
	}
	else
	{
		while ((_ctype[*p] & ctyp)) p++;

		wordlen = p-c;

		if (ctyp & W)
		{
		/* Always active */
			element = EL_WHITESPACE;
		}
		else if (ctyp & S)
		{
			if (ElementArray[EL_SYMBOL].Flags & ELFL_ACTIVE)
				element = EL_SYMBOL;
			else
				element = EL_IDENTIFIER;
		}
		else if (ctyp & A)
		{
			if ((ElementArray[EL_KEYWORD].Flags & ELFL_ACTIVE) && (SearchArray(KeywordsTab, KEYWORDSCOUNT, c, wordlen) != (UWORD)~0))
			{
				element = EL_KEYWORD;
			}
		/*
			else if ((ElementArray[EL_CPPKEYWORD].Flags & ELFL_ACTIVE) && (SearchArray(HighCPPTab, c, wordlen) != (UWORD)~0))
			{
				element = EL_CPPKEYWORD;
			}
			else if ((ElementArray[EL_USERWORD].Flags & ELFL_ACTIVE) &&
						(SearchArray(UserTab, c, wordlen) != (UWORD)~0))
			{
				element = EL_USERWORD;
			}
		*/
			else
			{
				element = EL_IDENTIFIER;
			}
		}
		else
		{
			if (ElementArray[EL_ILLEGAL_CHAR].Flags & ELFL_ACTIVE)
				element = EL_ILLEGAL_CHAR;
			else
				element = EL_IDENTIFIER;
		}
	}

	*el = element;

	return wordlen;
}

BOOL LoadSyntax(STRPTR filename)
{
/*
   BPTR fh;

   if (fh = Open(filename, MODE_OLDFILE))
   {
      Read(fh, ElementArray, sizeof(struct SyntaxElement)*EL_MAX);
   }
*/
   return TRUE;
}

BOOL SaveSyntax(STRPTR filename)
{
/*   BPTR fh;

	if (fh = Open(filename, MODE_NEWFILE))
	{
		Write(fh, ElementArray, sizeof(struct SyntaxElement)*EL_MAX);
	}
*/
	return TRUE;
}

/***************************************************************************************



***************************************************************************************/

struct SyntaxData *LIBGetSyntaxData
(
	struct SyntaxHandle *handle
)
{
	static struct SyntaxData	SyntaxData;

/* Sample source: No tabs in here please */
	static char* SampleStrings[] =
	{
		"/* C/C++ sample source */",
		"",
		"#include <stdio.h>",
		"",
		"void main(int argc, char *argv[])",
		"{",
		"   char *test = new char[60];",
		"",
		"// Numerical syntax elements",
		"   printf(\"int %d, float %f\\n\", 5, 5.0);",
		"   printf(\"hex %x, octal %o\\n\", 0x5, 05);",
		"   printf(\"char %c, illegal %d\\n\", 'a', 0xg);",
		"",
		"   delete test;",
		"}",
		NULL
	};

   static char* ElementStrings[] =
   {
      "White Space",
      "Identifier",
      "ANSI Comment",
      "CPP Comment",
      "Reserved ANSI Word",
      "Reserved CPP Word",
      "Symbol",
      "Integer",
      "Float",
      "Octal",
      "Hex",
      "String",
      "Character",
      "Preprocessor",
      "Illegal Char",
      "User Word",
      NULL
   };

	SyntaxData.Version = SYNTAX_VERSION;
//	SyntaxData.VerString = "C/C++ syntax © 2000 Sigurd Lerstad";
//	SyntaxData.ConfigFile = CONFIGFILE;

	SyntaxData.NumElements = EL_MAX;
	SyntaxData.ElementArray = ElementArray;
	SyntaxData.ElementStrings = ElementStrings;
	SyntaxData.SampleStrings = SampleStrings;

	return &SyntaxData;
}

LONG InitCPPSyntax(struct SyntaxHandle *handle)
{
	/* Doesn't 'require' any of these */
/*
   HighCTab = ReadStringTab("c:\\syntax\\highlight_C.dat");
  	HighCPPTab = ReadStringTab("c:\\syntax\\highlight_CPP.dat");
   UserTab = ReadStringTab("c:\\syntax\\highlight_user.dat");
*/
	return 0;
}

/**************************************************************************************

   Update all the attr-codes of this line, and if necessary following lines.
   (there are no more lines if line->Succ == NULL)

   returns the number of lines changes were made in.

   ParseLines() parses folded lines, but they should not be included in the
   returned number of lines that have been parsed, because this value
   is later used to know the number of lines to visually print in VisualEd,
   and as folded lines are hidden they should not be printed.

**************************************************************************************/

#if 0
UWORD ParseCPPLines
(
	struct SyntaxHandle *handle, 
	LineDef** lines,
	BSTR textData,
	UWORD startoffset,
	UWORD maxlength,
	CArray <SyntaxChunk, SyntaxChunk>& SyntaxArr
)
{
	SyntaxArr.SetSize(maxlength);	// hm.. TODO, add instead
	SyntaxChunk* syntax = SyntaxArr.GetData();
	int ChunkUsed = 0;

	int pos = 0;
	while (pos < maxlength)
	{
		if (textData[pos] == L'<')
		{
			while 
		}
	}

	SyntaxArr.SetSize(ChunkUsed);

	return 0;
}
#endif

#if 0
UWORD ParseCPPLines
(
	struct SyntaxHandle *handle, 
	LineDef** lines,
	BSTR textData,
	UWORD startoffset,
	UWORD maxlength,
	CArray <SyntaxChunk, SyntaxChunk>& SyntaxArr
)
{
	SyntaxArr.SetSize(maxlength);	// hm.. TODO, add instead
	SyntaxChunk* syntax = SyntaxArr.GetData();
	int ChunkUsed = 0;

	UWORD	parsedlength = 0;
	BOOL	donext;

	int nline = 0;

	if (maxlength == 0) return 0;

	int offset = 0;

	do
	{
	//	register UWORD	len = linenode->LineLen;
		UBYTE	el = 0;
		BOOL	cont = FALSE;

		if (offset == 0)	/* If first line in the doc */
			el = 0;
		else
		{
//			while (!prevline->IsParsed
			el = 0;//syntax[-1].Element;
		}
	//	linenode->BegEl = el;		/* Attr at beginning of line taken from the previous line's EndAttr */

	//	if (linenode->Syntax) free(linenode->Syntax);
	//	linenode->Syntax = (SyntaxChunk*)malloc(sizeof(struct SyntaxChunk)*(linenode->LineLen+1));

		lines[nline]->m_ckOffset = ChunkUsed;

		syntax->Length = 0;
		syntax->Element = el;
		syntax->Flags = ElementFlags[el];

		ChunkUsed += 1;

		int linelen = lines[nline]->m_lineLength;

		WCHAR* lineData = &textData[offset];

		UWORD	col = 0;

		while (col < linelen)
		{
			WCHAR *c = &lineData[col];
			UWORD	ellen = 1;	/* Assume */
			UBYTE	sel = 255;
			BOOL	off = FALSE;

			if (!(ctype[*c] & C))
			{
				if (el == 0) ellen = ParseWord(lineData, col, linelen, &sel);
			}
			else
			{
				if (c[0] == '/')  /* This could be the start of a comment */
	         {
	            if ((el == 0) || (el == EL_PREPROCESSOR))   /* Can have comments on same line as preprocessor */
	            {
	               if (c[1] == '/')	/* CPP comment, set rest of line to that */
	               {
	                  el = EL_CPPCOMMENT;
							ellen = linelen-col;
	               }
	               else if (c[1] == '*')	/* ANSI comment */
	               {
	                  el = EL_COMMENT;
							ellen = 2;
	               }
	               else
	               {
	                  if (el != EL_PREPROCESSOR)	/* If it wasn't a comment and we're not */
	                     sel = EL_SYMBOL;			/* in preprocessor make it a symbol */
	               }
	            }
	         }
	         else if (c[0] == '*')   /* This could be the end of a comment */
	         {
	            if ((el == EL_COMMENT) && (c[1] == '/'))
	            {
	               off = TRUE;
						el = 0;
						ellen = 2;
	            }
	            else
	            {
	               if (el == 0) /* It was just a normal symbol */
	               {
							sel = EL_SYMBOL;
	               }
	            }
	         }
	         else if (c[0] == '\"')  /* Either beginning or ending a string quote */
	         {
	            if (el == 0) /* Beginning */
	            {
	               el = EL_STRING;
	            }
	            else if (el == EL_STRING)   // Maybe it's ending */
	            {
					/* Here we check if it's a \", then we check if it's a \\" */
						if (((col > 0) && (c[-1] != '\\')) ||	/* it's not a '\"' */
							 ((col > 1) && (c[-2] == '\\')))		/* it's a '\\"' */
						{
							off = TRUE;
							el = 0;
						}
	            }
	         }
	         else if (c[0] == '\'')  /* Either beginning or ending a char quote */
	         {
	            if (el == 0) /* Beginning */
	            {
	               el = EL_CHARACTER;
	            }
	            else if (el == EL_CHARACTER)   /* Maybe it's ending */
	            {
					/* Here we check if it's a \', then we check if it's a \\' */
						if (((col > 0) && (c[-1] != '\\')) ||	/* it's not a \' */
							 ((col > 1) && (c[-2] == '\\')))		/* it's a \\' */
						{
							off = TRUE;
							el = 0;
						}
	            }
	         }
	         else if (c[0] == '#')   /* If first non-blank char on line, this is preprocessor statement */
	         {
	            if (el == 0)
	            {
	               /* TODO: Check if first non-blank */
	               el = EL_PREPROCESSOR;
	            }
	         }
	         else if (c[0] == '\\')  /* If last on line, this is a continuation on the next line */
	         {
	            if ((col == linelen-1) &&   /* last on line */
	                (el != EL_CPPCOMMENT))
	            {
	               if (el) cont = TRUE;  /* Only need to continue if there was some previous el */
	            }
	         }
			}

			if (sel == 255) sel = el;

			if (off) syntax->Length += ellen;

		/* If the element has changed goto next syntax chunk */
			if (sel != syntax->Element)
			{
			// Only create new if the previous syntax chunk contains something
			// if not, just overwrite that one
				if (syntax->Length > 0)
				{
					ChunkUsed++;
					syntax++;
				}

				syntax->Length = 0;
				syntax->Element = sel;
				syntax->Flags = ElementFlags[sel];
			}

			if (!off) syntax->Length += ellen;

		//	CString msg;
		//	msg.Format("%d", syntax->Length);
		//	AfxMessageBox(msg/*(LPCTSTR)(&lineData[col])*/);

			col += ellen;
      }

//		msg.Format("%d, %d, %d", linelen, offset, maxlength);
//		AfxMessageBox(msg);

		offset += linelen+1;

		syntax++;	// Always new on each line

		nline++;
#if 0
		linenode->Syntax = realloc(linenode->Syntax, linenode->ChunkUsed*sizeof(struct SyntaxChunk));

   /* numlines is used later to know the number of lines to visually update
		folded lines shouldn't be included in this count */
      if (!linenode->Folded) parsedlines++;

	/* Set this line's EndEl */
      if ((el == EL_COMMENT) || cont) /* This continues over several lines */
         linenode->EndEl= el;
      else
         linenode->EndEl = 0;

      donext = FALSE;   /* Assume that we're not gonna parse the next line */

		if (--maxlines)
		{
	   /* Check if Next line is candidate for scanning
	 	  	First check if there IS a next line */
	      if ((nextline = linenode->Succ)->Succ)
	      {
	         /* If the next line's BegEl is different than the line we just
	         	parsed's EndAttr then parse the next one too */
	         if (nextline->BegEl != linenode->EndEl)
	         {
	            linenode = nextline;
	            donext = TRUE;
	         }
	      }
		}
#endif
   }
	while (offset < maxlength/*-1*/);
//   while (donext);

	SyntaxArr.SetSize(ChunkUsed);

   return parsedlength;     /* Number of lines that were parsed */
}

UBYTE ctype[256] =
{
   0, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   W, // TAB
   0, //		// Newline (treat as end of string)
   1, //
   1, //
   1, // 
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   W, //
   S, // !
   C, // "
   C, // #
   1, // $
   S, // %
   S, // &
   C, // '
   S, // (
   S, // )
   C, // *
   S, // +
   S, // ,
   S, // -
   S, // .
   C, // /
   N|A|X|O,  // 0
   N|A|X|O,  // 1
   N|A|X|O,  // 2
   N|A|X|O,  // 3
   N|A|X|O,  // 4
   N|A|X|O,  // 5
   N|A|X|O,  // 6
   N|A|X|O,  // 7
   N|A|X,  // 8
   N|A|X,  // 9
   S, // :
   S, // ;
   S, // <
   S, // =
   S, // >
   S, // ?
   1, // @
   A|X, // A
   A|X, // B
   A|X, // C
   A|X, // D
   A|X, // E
   A|X, // F
   A, // G
   A, // H
   A, // I
   A, // J
   A, // K
   A, // L
   A, // M
   A, // N
   A, // O
   A, // P
   A, // Q
   A, // R
   A, // S
   A, // T
   A, // U
   A, // V
   A, // W
   A, // X
   A, // Y
   A, // Z
   S, // [
   C, //
   S, // ]
   S, // ^
   A, // _
   1, // `
   A|X,  // a
   A|X,  // b
   A|X,  // c
   A|X,  // d
   A|X,  // e
   A|X,  // f
   A,  // g
   A,  // h
   A,  // i
   A,  // j
   A,  // k
   A,  // l
   A,  // m
   A,  // n
   A,  // o
   A,  // p
   A,  // q
   A,  // r
   A,  // s
   A,  // t
   A,  // u
   A,  // v
   A,  // w
   A,  // x
   A,  // y
   A,  // z
   S, // {
   S, // |
   S, // }
   S, // ~
   1, // 
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //
   1, //  
   1, // ¡
   1, // ¢
   1, // £
   1, // ¤
   1, // ¥
   1, // ¦
   1, // §
   1, // ¨
   1, // ©
   1, // ª
   1, // «
   1, // ¬
   1, // ­
   1, // ®
   1, // ¯
   1, // °
   1, // ±
   1, // ²
   1, // ³
   1, // ´
   1, // µ
   1, // ¶
   1, // ·
   1, // ¸
   1, // ¹
   1, // º
   1, // »
   1, // ¼
   1, // ½
   1, // ¾
   1, // ¿
   1, // À
   1, // Á
   1, // Â
   1, // Ã
   1, // Ä
   1, // Å
   1, // Æ
   1, // Ç
   1, // È
   1, // É
   1, // Ê
   1, // Ë
   1, // Ì
   1, // Í
   1, // Î
   1, // Ï
   1, // Ð
   1, // Ñ
   1, // Ò
   1, // Ó
   1, // Ô
   1, // Õ
   1, // Ö
   1, // ×
   1, // Ø
   1, // Ù
   1, // Ú
   1, // Û
   1, // Ü
   1, // Ý
   1, // Þ
   1, // ß
   A, // à
   A, // á
   A, // â
   A, // ã
   A, // ä
   A, // å
   1, // æ
   A, // ç
   1, // è
   1, // é
   1, // ê
   1, // ë
   1, // ì
   1, // í
   1, // î
   1, // 
   1, // ð
   1, // ñ
   1, // ò
   1, // ó
   1, // ô
   1, // õ
   1, // ö
   1, // ÷
   A, // ø
   1, // ù
   1, // ú
   1, // û
   1, // ü
   1, // ý
   1, // þ
   1, // ÿ
};
#endif