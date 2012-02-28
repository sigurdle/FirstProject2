#ifndef __stab_h_
#define __stab_h_

namespace System
{

#define N_GSYM 0x20  //     Global symbol; see See Global Variables.

/*
`0x22     N_FNAME'
     Function name (for BSD Fortran); see See Procedures.
*/

#define N_FUN 0x24    // Function name (see Procedures.) or text segment variable (see Statics.).

/*
`0x26 N_STSYM'
     Data segment file-scope variable; see See Statics.

`0x28 N_LCSYM'
     BSS segment file-scope variable; see See Statics.

`0x2a N_MAIN'
     Name of main routine; see See Main Program.

`0x2c N_ROSYM'
     Variable in `.rodata' section; see See Statics.

`0x30     N_PC'
     Global symbol (for Pascal); see See N_PC.

`0x32     N_NSYMS'
     Number of symbols (according to Ultrix V4.0); see See N_NSYMS.

`0x34     N_NOMAP'
     No DST map; see See N_NOMAP.

`0x38 N_OBJ'
     Object file (Solaris2).

`0x3c N_OPT'
     Debugger options (Solaris2).
*/

#define N_RSYM 0x40     //     Register variable; see See Register Variables.

/*
`0x42     N_M2C'
     Modula-2 compilation unit; see See N_M2C.
*/

#define N_SLINE 0x44    //     Line number in text segment; see See Line Numbers.

/*
`0x46     N_DSLINE'
     Line number in data segment; see See Line Numbers.

`0x48     N_BSLINE'
     Line number in bss segment; see See Line Numbers.

`0x48     N_BROWS'
     Sun source code browser, path to `.cb' file; see See N_BROWS.

`0x4a     N_DEFD'
     GNU Modula2 definition module dependency; see See N_DEFD.

`0x4c N_FLINE'
     Function start/body/end line numbers (Solaris2).

`0x50     N_EHDECL'
     GNU C++ exception variable; see See N_EHDECL.

`0x50     N_MOD2'
     Modula2 info "for imc" (according to Ultrix V4.0); see 
See N_MOD2.

`0x54     N_CATCH'
     GNU C++ `catch' clause; see See N_CATCH.

`0x60     N_SSYM'
     Structure of union element; see See N_SSYM.

`0x62 N_ENDM'
     Last stab for module (Solaris2).
*/

#define N_SO	0x64  // Path and name of source file; see See Source Files.
#define N_LSYM	0x80	// Stack variable (see Stack Variables.) or type (see Typedefs.).
#define N_BINCL 0x82  // Beginning of an include file (Sun only); see See Include Files.
#define N_SOL 0x84  //   Name of include file; see See Include Files.
#define N_PSYM 0xa0  //  Parameter variable; see See Parameters.
#define N_EINCL 0xa2    //     End of an include file; see See Include Files.

/*
`0xa4     N_ENTRY'
     Alternate entry point; see See Alternate Entry Points.
	  */

#define N_LBRAC 0xc0   // Beginning of a lexical block; see See Block Structure.

	  /*
`0xc2     N_EXCL'
     Place holder for a deleted include file; see See Include Files.

`0xc4     N_SCOPE'
     Modula2 scope information (Sun linker); see See N_SCOPE.
*/

#define N_RBRAC 0xe0  //  End of a lexical block; see See Block Structure.

/*
`0xe2     N_BCOMM'
     Begin named common block; see See Common Blocks.

`0xe4     N_ECOMM'
     End named common block; see See Common Blocks.

`0xe8     N_ECOML'
     Member of a common block; see See Common Blocks.

`0xea N_WITH'
     Pascal `with' statement: type,,0,0,offset (Solaris2).

`0xf0     N_NBTEXT'
     Gould non-base registers; see See Gould.

`0xf2     N_NBDATA'
     Gould non-base registers; see See Gould.

`0xf4     N_NBBSS'
     Gould non-base registers; see See Gould.

`0xf6     N_NBSTS'
     Gould non-base registers; see See Gould.

`0xf8     N_NBLCS'
     Gould non-base registers; see See Gould.
*/

struct nlist {
        union {
                char    *n_name;
                long    n_strx;
        } n_un;

#define N_UNDF	0x00		/* undefined */
#define N_ABS	0x02		/* absolute address */
#define N_TEXT	0x04		/* text segment */
#define N_DATA	0x06		/* data segment */
#define N_BSS	0x08		/* bss segment */
#define N_INDR	0x0a		/* alias definition */
#define N_SIZE	0x0c		/* pseudo type, defines a symbol's size */
#define N_COMM	0x12		/* common reference */

/* These appear as input to LD, in a .o file.  */
#define N_SETA	0x14		/* absolute set element symbol */
#define N_SETT	0x16		/* text set element symbol */
#define N_SETD	0x18		/* data set element symbol */
#define N_SETB	0x1a		/* bss set element symbol */

/* This is output from LD.  */
#define N_SETV	0x1c		/* set vector symbol */

//
#define N_FN	0x1e		/* file name (N_EXT on) */
#define N_WARN	0x1e		/* warning message (N_EXT off) */

#define N_EXT	0x01		/* external (global) bit, OR'ed in */
#define N_TYPE	0x1e		/* mask for all the type bits */

        unsigned char   n_type;

        char            n_other;
        short           n_desc;
        unsigned long   n_value;
};

#define N_STAB		0x0e0	/* mask for debugger symbols -- stab(5) */


//#include "../CodeComp/debug.h"

class StabDebugInfo : public DebugInfo
{
public:
	CTOR StabDebugInfo();
	~StabDebugInfo();

	virtual void FromStab(uint32 offaddr, nlist* stab, int nstabs, System::IDebugInfoReceiver* pReceiver);

	System::Scope* m_pGlobalScope;

	virtual System::Scope* GetScope()
	{
		return m_pGlobalScope;
	}

	virtual ULONG Release()
	{
		// TODO
		return 1;
	}

	virtual int Parse(ObjectFileParser* pImage, IDebugInfoReceiver* receiver, ULONG_PTR dwData);

protected:

	void stab_lsym(const char* p, System::Scope* pScope);

	System::Type* get_type(const char* &p, StringIn name);
	System::Type* get_type2(const char* &p, StringIn name, int file_num, int type_num);

	System::IDebugInfoReceiver* m_pReceiver;
	vector<System::Type*> m_types;
};

}	// System

#endif // __stab_h_
