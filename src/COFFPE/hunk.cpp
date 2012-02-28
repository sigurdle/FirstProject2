#include "StdAfx.h"

#if 0

#include "hunk.h"
#include <list>

//static struct MinList	HunkList;
//static struct MinList	SymbolList;

typedef std::list<ULONG*> hunklist;
typedef std::list<ULONG*> symbollist;

hunklist HunkList;
symbollist SymbolList;

static FILE	*out;

static char *HunkStr[] =
{
	"UNIT",
	"NAME",
	"CODE",
	"DATA",
	"BSS",
	"RELOC32",
	"RELOC16",
	"RELOC8",
	"EXTERN",
	"SYMBOL",
	"DEBUG",
	"end",			// end
	NULL,			// header
	NULL,			// not defined?
	"OVERLAY",
	"BREAK",
	"DRELOC32",
	"DRELOC16",
	"DRELOC8",
	"LIB",
	"INDEX",
	"RELOC32SHORT",
	"RELRELOC32",
	"ABSRELOC16",
};

char *GetHunkStr(ULONG id)
{
	int	index = (id & ID_MASK)-HUNK_UNIT;

	if ((index >= 0) && (index < 24))
	{
		return HunkStr[index];
	}
	else if (id & HUNKF_ADVISORY)
	{
		return "ADVISORY";
	}
	else
	{
		return NULL;
	}
}

/**************************************************************************************

	pass1 hunk handling

	
**************************************************************************************/

ULONG *pass1_HUNK_X(ULONG hunk_ID, ULONG *hunk_ptr)
{
	ULONG	size = *hunk_ptr++;
	return hunk_ptr+size;
}

typedef unsigned char UBYTE;

ULONG *pass1_EXT(ULONG hunk_ID, ULONG *hunk_ptr)
{
	ULONG ext = *hunk_ptr++;
	ULONG	size;

	while (size = (ext & 0x00ffffff))
	{
		UBYTE	type = ext >> 24;
		ULONG	*label = hunk_ptr;

		hunk_ptr += size;

		if (type > EXT_SYMB)
		{
			fprintf(out, "\t%d %.*s", type, size<<2, label);

			if (type == EXT_DEF)
			{
				ULONG	addr = *hunk_ptr++;
				printf(" at %06X", addr);
			}

			fprintf(out, "\n");
		}

		ext = *hunk_ptr++;
	}

	return hunk_ptr;
}

ULONG *pass1_RELOC(ULONG hunk_ID, ULONG *hunk_ptr)
{
	ULONG	offsets = *hunk_ptr++;

	while (offsets)
	{
	/*	ULONG	hunk_number = * */ hunk_ptr++;
	/*
		ULONG	i;

		for (i = 0; i < offsets; i++)
		{
			hunk_ptr++;
		}
	*/

		hunk_ptr += offsets;

		offsets = *hunk_ptr++;
	}

	return hunk_ptr;
}

struct SymbolNode *FindSymbol(ULONG counter)
{
	return NULL;

#if 0
	struct SymbolNode	*symnode = (struct SymbolNode *)SymbolList.mlh_Head;
	struct Node	*succnode;

	while (succnode = ((struct Node *)symnode)->ln_Succ)
	{
		if (symnode->SymPtr[(*symnode->SymPtr)+1] == counter) return symnode;

		symnode = (struct SymbolNode *)succnode;
	}

	return NULL;
#endif
}

ULONG *pass1_SYMBOL(ULONG hunk_ID, ULONG *hunk_ptr)
{
	ULONG	size = *hunk_ptr++;

	while (size)
	{
#if 0
		struct SymbolNode	*symnode;

		if (symnode = malloc(sizeof(struct SymbolNode)))
		{
			symnode->SymPtr = hunk_ptr-1;
			AddTail((struct List *)&SymbolList, (struct Node *)symnode);
		}
#endif

		hunk_ptr += size;
		hunk_ptr++;

		size = *hunk_ptr++;
	}

	return hunk_ptr;
}

/**************************************************************************************

	pass2 hunk handling

**************************************************************************************/

LONG pass2_HUNK_X(ULONG hunk_ID, ULONG *hunk_ptr)
{
	fprintf(out, "\n\t;%s\n\n", GetHunkStr(hunk_ID));

	return 0;
}

LONG pass2_UNITNAME(ULONG hunk_ID, ULONG *hunk_ptr)
{
	ULONG	len = *hunk_ptr++;

	fprintf(out, "\n\t;%s: %.*s\n\n", GetHunkStr(hunk_ID), len<<2, hunk_ptr);

	return 0;
}

#if 0
LONG pass2_CODE(ULONG hunk_ID, ULONG *hunk_ptr)
{
	char	tabs[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

	ULONG	hunk_size = *hunk_ptr++;	// HUNK longsize
	ULONG	hunk_bytesize = hunk_size<<2;

	fprintf(out, "\n\t;%s", GetHunkStr(hunk_ID));

	if (hunk_ID & HUNKF_CHIP)
		fprintf(out, " CHIP");
	else if (hunk_ID & HUNKF_FAST)
		fprintf(out, " FAST");

	fprintf(out, ": %ld bytes\n\n", hunk_bytesize);

	int counter = 0L;	// Program counter
	UBYTE* stream = (UBYTE *)hunk_ptr;

	while (counter < hunk_bytesize)
	{
		struct SymbolNode	*symnode;

		xsptr = xsbuf;
		msptr = msbuf;

		symnode = FindSymbol(counter);

		if (!args.nopc) xsptr += sprintf(xsptr, "%06lX", counter);

		opcode = fetch_w();								// Get the next opcode from the stream
		(CodeMapFunc[(opcode & 0xF000)>>12])();	// and decode it

		if (args.nopc)
		{
			if (symnode) fprintf(out, "%.*s:\n", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
			fprintf(out, "\t%s\n", msbuf);
		}
		else
		{
			UWORD	tlen = 5-((xsptr-xsbuf)/8);
			if (symnode) fprintf(out, "\t\t\t\t\t%.*s:\n", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
			fprintf(out, "%s%.*s\t%s\n", xsbuf, tlen, tabs, msbuf);
		}

		if (CheckSignal(SIGBREAKF_CTRL_C))
		{
			hunk_ptr = NULL;
			hunk_size = 0L;

			counter = 0L;
			hunk_bytesize = 0L;	// Quit this loop
		}
	}

	if (!hunk_ptr)
		return 1;
	else
		return 0;
}
#endif

LONG pass2_DATA(ULONG hunk_ID, ULONG *hunk_ptr)
{
	ULONG	size = *hunk_ptr++;

	fprintf(out, "\n\t;%s: %ld bytes\n\n", GetHunkStr(hunk_ID), size<<2);

	return 0;
}

LONG pass2_BSS(ULONG hunk_ID, ULONG *hunk_ptr)
{
	ULONG	size = *hunk_ptr++;
//	struct SymbolNode	*symnode;

	fprintf(out, "\n\t;BSS: %ld bytes\n\n", size<<2);

#if 0
	symnode = FindSymbol(counter);
#endif

	fprintf(out, "\tds.l\t%ld", size<<2);

	return 0;
}



LONG Pass1(struct HUNK_Header	*header, ULONG *hunk_ptr, ULONG size)
{
	LONG	error = 0;

	ULONG	totalhunks;
	ULONG	hunksofar = 0L;

	if (header)
		totalhunks = header->num_hunks;
	else
		totalhunks = 1;

	while (hunksofar < totalhunks)
	{
		ULONG	*hunk_start = hunk_ptr;
		ULONG	hunk_ID = *hunk_ptr++;

		switch (hunk_ID & ID_MASK)
		{
			case HUNK_DREL8:
			case HUNK_DREL16:
			case HUNK_DREL32:
			case HUNK_RELOC8:
			case HUNK_RELOC16:
			case HUNK_RELOC32:
				hunk_ptr = pass1_RELOC(hunk_ID, hunk_ptr);
				break;

			case HUNK_EXT:
				hunk_ptr = pass1_EXT(hunk_ID, hunk_ptr);
				break;

			case HUNK_SYMBOL:
				hunk_ptr = pass1_SYMBOL(hunk_ID, hunk_ptr);
				break;

			case HUNK_UNIT:
			case HUNK_NAME:
			case HUNK_CODE:
			case HUNK_DATA:
			case HUNK_BSS:
			case HUNK_DEBUG:
				hunk_ptr = pass1_HUNK_X(hunk_ID, hunk_ptr);
				break;

			case HUNK_END:
				hunksofar++;
				break;

			default:
				if (hunk_ID & HUNKF_ADVISORY)	// Can be skipped
				{
					hunk_ptr = pass1_HUNK_X(hunk_ID, hunk_ptr);
				}
				else
				{
					fprintf(stderr, "Hunk not recognized: %8lX", hunk_ID & ID_MASK);
					hunk_ptr = NULL;	// End this loop
					error = 1;
				}
		}

		if (!hunk_ptr/* ||
			CheckSignal(SIGBREAKF_CTRL_C)*/)	// Abort?
		{
			hunksofar = totalhunks;	// End this loop
		}
		else
		{
			ATLASSERT(0);
#if 0
			struct HunkNode	*hunk;

			if (hunk = malloc(sizeof(struct HunkNode)))
			{
				hunk->Hunk_ptr = hunk_start;
				AddTail((struct List *)&HunkList, (struct Node *)hunk);
			}
#endif
		}
	}

	return error;
}

void Pass2(void)
{
	hunklist::iterator hunki = HunkList.begin();
	//struct Node			*succnode;

	while (hunki != HunkList.end())//succnode = ((struct Node *)hunk)->ln_Succ)
	{
		ULONG	*hunk_ptr = *hunki;//hunk->Hunk_ptr;
		ULONG	hunk_ID = *hunk_ptr++;
		LONG	abort;

		switch (hunk_ID & ID_MASK)
		{
			case HUNK_UNIT:
			case HUNK_NAME:
				abort = pass2_UNITNAME(hunk_ID, hunk_ptr);
				break;

			case HUNK_CODE:
				abort = 0;//pass2_CODE(hunk_ID, hunk_ptr);
				break;

			case HUNK_DATA:
				abort = pass2_DATA(hunk_ID, hunk_ptr);
				break;

			case HUNK_BSS:
				abort = pass2_BSS(hunk_ID, hunk_ptr);
				break;

			case HUNK_END:
				fprintf(out, "\n\t;Hunk-End\n\n");
				break;

			default:
				abort = pass2_HUNK_X(hunk_ID, hunk_ptr);
		}

		if (abort) break;
	//	hunk = (struct HunkNode *)succnode;
		hunki++;
	}
}

#if 0
int dasm()
{
	FILE	*fp;
	UBYTE	*buf = NULL;
	ULONG	filesize = 0L;

	if (!args.file) return 1;

	if (fp = fopen(args.file, "r"))
	{
		fseek(fp, 0, 2);
		filesize = ftell(fp);
		rewind(fp);

		if (buf = malloc(filesize))
		{
			fread(buf, filesize, 1, fp);
		}
		else
		{
			fprintf(stderr, "Not enough memory.\n");
		}

		fclose(fp);
	}
	else
	{
		fprintf(stderr, "Couldn't open file.\n");
	}

	if (buf)
	{
		struct HUNK_Header	*header = NULL;
		ULONG	*hunk_ptr = (ULONG *)buf;

		out = NULL;
		if (args.to) out = fopen(args.to, "w");
		if (!out) out = stdout;

		fprintf(out, ";$VER: " PROGNAME " " VERSTRING " " __AMIGADATE__ "\n\n");
		fprintf(out, ";Disassembled file: %s\n", FilePart(args.file));
		fprintf(out, ";Filesize in bytes: %ld\n", filesize);

		if (*hunk_ptr == HUNK_HEADER)	// It's a load module
		{
			header = (struct HUNK_Header *)buf;

			hunk_ptr = (ULONG *)(buf+sizeof(struct HUNK_Header));
			hunk_ptr += header->num_hunks;
		}

		NewList((struct List *)&HunkList);
		NewList((struct List *)&SymbolList);

		if (Pass1(header, hunk_ptr) == 0) Pass2();

		if (out != stdout) fclose(out);

		free(buf);
	}

	return 0L;
}
#endif
#endif