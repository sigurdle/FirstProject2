#ifndef SYNTAX_H
#define SYNTAX_H
/*
**
** $VER: syntax.h (31.5.96)
**
** Copyright © 1996 BST Software, Sigurd Lerstad.
** All rights reserved.
**
** Syntax interface version 0, subject to change.
**
*/

#pragma pack(push, 1)

typedef BYTE	UBYTE;
typedef WORD	UWORD;
typedef void*	APTR;
typedef unsigned char* STRPTR;

#define FS_NORMAL			0
#define FSF_ITALIC		1
#define FSF_BOLD			2
#define FSF_UNDERLINE	4

#define SYNTAX_VERSION   0

struct SyntaxData
{
	UWORD Version;		/* Interface version, SYNTAX_VERSION */
	UWORD Flags;

	STRPTR	VerString;

	STRPTR   ConfigFile; /* Name of configfile that syntaxer loads on startup */

	UWORD		reserved0;
	UWORD    NumFunctions;		/* Number of functions */
	STRPTR	*FunctionNames;	/* Descriptive function names */

	UWORD		reserved1;
	UWORD    NumElements;
	char*   *ElementStrings;
	char*   *SampleStrings;
	struct SyntaxElement *ElementArray;

	ULONG	reserved2[8];
};

/* Flags */

#define MAX_ELEMENTS	64

struct SyntaxElement
{
	COLORREF  FgColor;
	COLORREF  BgColor;
//	UBYTE Style;   /* Bold/Italic/Underlined? */
//	UBYTE Flags;
};

struct LineDef
{
	DWORD m_offset;
	DWORD m_ckOffset;
	DWORD	m_lineLength;
	DWORD m_lineLengthR;
};

/* SyntaxElement Flags */
#define ELFL_ACTIVE			1 	/* If this is set, the element is active
											Note that element 0 is always activate
										*/
#define ELFL_INTERACTIVE	2	/* If this is set, this element is interactive,
										*/
#define ELFL_SHADOW			4
#define ELFL_FRAME			8
#define ELFL_RECESSED		16

/* The parser returns an array of these for each line parsed
	the total length field of all the syntaxchunks for a line MUST be
	equal to line->LineLen

	(e.g) if a line is 20 chars long, and there is e.g two different
	elements on that line:
	syntaxchunk[0].length = 5;
	syntaxchunk[1].length = 15;

	total = 20

	if the linelen = 0, then line->Syntax is expected to be NULL (no syntax array)

*/

struct SyntaxChunk
{
	WORD	Length;
	BYTE	Element;
	BYTE	Flags;
};	// 4 bytes

/* SyntaxChunk flags */
#define SCF_HOLE			0x1	/* If this is set, VisualEd will assume that this
											syntaxchunk only contains non whitespace characters
											(that is no spaces or tabs).
											You as a syntaxparser should set this bit in those
											cases as output will speed up.
										*/

#define SCF_HIDDEN		0x2	/* If this is set, VisualEd will not display this
											syntaxchunk in the editor window, syntaxparsers
											that only do highlighting will not use this,
											see the amigaguide.syntax for example of usage
										*/

#define SCF_EXTENDED		0x4	/* There's an additional SyntaxChunkExt with this
											syntaxchunk
										*/

struct SyntaxChunkExt
{
	UBYTE	Flags;
	UBYTE	Style;
	BYTE	FgColor;
	BYTE	BgColor;
	union
	{
		struct TextFont	*extFont;
		struct Image		*extImage;
	}
	extdata;
};

#define ExtFont	extdata.extFont
#define ExtImage	extdata.extImage

/* Flags */
#define SEF_TEXT		0x1
#define SEF_IMAGE		0x2

/* This is the LineNode structure */

struct LineNode
{
/* This structure is READ-ONLY for syntaxparsers, unless stated otherwise */

/* Standard Node structure */
	struct LineNode	*Succ;
	struct LineNode	*Pred;
	UBYTE		reserved0;	/* type Future */
   UBYTE		reserved1;	/* pri Future */
	STRPTR	TextBuf;

	UWORD    BufSize;		/* Bytes allocated for TextBuf
									this may be zero, even if TextBuf is pointing
									to something, (e.g) if wordwrap is on, TextBuf
									may be pointing at some index into another lines TextBuf
									*/

	UWORD    LineLen;		/* Characters len */
	UWORD		VirtualLen;	/* Virtual len with tabs extended */

/* Fold info */
   UWORD Folded;  /* Folded level, none of the fold information below is valid
                     if this is 0 */

   UBYTE FoldIs;  /* 0=this is a line within a fold, FoldLine isn't valid
                     1=this is the beginning line of fold,
                        FoldLine is pointing to last fold line+1
                     2=this is the end of the fold
                        FoldLine is pointing to first fold line
                  */

   UBYTE FoldHdrCol; /* Column where the fold header title starts */

   struct LineNode *FoldLine;  /* Depending on FoldIs */

/* These are for syntaxparsers to use */
	UBYTE    Adjust;			/* Future */
	UBYTE		EndParagraph;	/* Future */

	UWORD		Height;			/* Height of this line */

   UWORD    ChunkUsed;		/* Set by syntaxparser to tell VisualEd how many
   									syntaxchunks it has used */
   UWORD    ChunkExtUsed;	/* Set by syntaxparser to tell VisualEd how many
   									syntaxchunks it has used */
	struct SyntaxChunk		*Syntax;
	struct SyntaxChunkExt	*SyntaxExt;

/* These are for syntax parsers to modify at will
	Intended usage is to (e.g)
#define mydat0	UserData.user0[0];

Or you could allocate a buffer on UserData.user3 and then free it when
FreePrivateData() is called
*/
	union
	{
		UBYTE	user0[4];
		UWORD	user1[2];
		ULONG	user2;
		APTR	user3;
	}
	UserData;

/* Might be extended */
};

/* Adjust */
#define ADJUST_LEFT     0
#define ADJUST_RIGHT    1
#define ADJUST_CENTER   2
#define ADJUST_FULL     3

/* FoldIs values */
#define FOLD_BEG  1
#define FOLD_END  2

#define IP_VERSION	0

struct InteractivePacket
{
	UWORD	ip_Version;
	UWORD	ip_pad;

	struct LineNode		*ip_LineNode;
	struct SyntaxChunk	*ip_SyntaxChunk;

	ULONG	reserved[4];

/* Might be extended */
};

/*
	Interface function prototypes
*/

void						ReleaseSyntax(struct SyntaxHandle *handle);

struct SyntaxData*	GetSyntaxData(struct SyntaxHandle *handle);

//UWORD						ParseCPPLines(struct SyntaxHandle *handle, struct LineNode *linenode, UWORD startLine, UWORD maxlines);


LONG InitCPPSyntax(struct SyntaxHandle *handle);

UWORD ParseCPPLines
(
	struct SyntaxHandle *handle, 
	LineDef** lines,
	BSTR textData,
	UWORD startoffset,
	UWORD maxlength,
	CArray <SyntaxChunk, SyntaxChunk>& SyntaxArr
);

UWORD						CallSyntax(struct SyntaxHandle *handle, struct MinList *linelist, UWORD n);
UWORD						CallInteractive(struct SyntaxHandle *handle, struct LineNode *linenode, struct SyntaxChunk *syntax);

void						FreePrivateData(struct SyntaxHandle *handle, struct LineNode *linenode);
BOOL						IsChar(struct SyntaxHandle *handle, char ch);

#pragma pack(pop)

#endif
