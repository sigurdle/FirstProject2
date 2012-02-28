#ifndef __MACHO_H_
#define __MACHO_H_

namespace System
{
namespace MachO
{

//typedef unsigned char uint8;
//typedef unsigned short uint16;
//typedef unsigned long uint32;
typedef unsigned long cpu_type_t;
typedef unsigned long cpu_subtype_t;

struct mach_header
{
	unsigned long  magic;      /* Mach magic number identifier */
	cpu_type_t     cputype;    /* cpu specifier */
	cpu_subtype_t  cpusubtype; /* machine specifier */
	unsigned long  filetype;   /* type of file */
	unsigned long  ncmds;      /* number of load commands */
	unsigned long  sizeofcmds; /* size of all load commands */
	unsigned long  flags;      /* flags */
}; 

// The value for the magic field of the mach_header structure is: 


#define MH_MAGIC    0xfeedface  /* the Mach magic number */ 

// The values for the cputype and cpusubtype fields are defined as follows in the header file sys/machine.h: 


/*
#define CPU_TYPE_MC680x0     ((cpu_type_t) 6)
#define CPU_SUBTYPE_MC68030  ((cpu_subtype_t) 1)
#define CPU_SUBTYPE_MC68040  ((cpu_subtype_t) 2) 
*/

#define  MACHO_CPU_TYPE_ANY   -1 
#define  MACHO_CPU_TYPE_VAX   1 
#define  MACHO_CPU_TYPE_MC680x0   6 
#define  MACHO_CPU_TYPE_I386   7 
#define  MACHO_CPU_TYPE_MC98000   10 
#define  MACHO_CPU_TYPE_HPPA   11 
#define  MACHO_CPU_TYPE_MC88000   13 
#define  MACHO_CPU_TYPE_SPARC   14 
#define  MACHO_CPU_TYPE_I860   15 
#define  MACHO_CPU_TYPE_POWERPC   18 
#define  MACHO_CPU_SUBTYPE_MULTIPLE   -1 
#define  MACHO_CPU_SUBTYPE_LITTLE_ENDIAN   0 
#define  MACHO_CPU_SUBTYPE_BIG_ENDIAN   1 
#define  MACHO_CPU_SUBTYPE_VAX_ALL   0 
#define  MACHO_CPU_SUBTYPE_VAX780   1 
#define  MACHO_CPU_SUBTYPE_VAX785   2 
#define  MACHO_CPU_SUBTYPE_VAX750   3 
#define  MACHO_CPU_SUBTYPE_VAX730   4 
#define  MACHO_CPU_SUBTYPE_UVAXI   5 
#define  MACHO_CPU_SUBTYPE_UVAXII   6 
#define  MACHO_CPU_SUBTYPE_VAX8200   7 
#define  MACHO_CPU_SUBTYPE_VAX8500   8 
#define  MACHO_CPU_SUBTYPE_VAX8600   9 
#define  MACHO_CPU_SUBTYPE_VAX8650   10 
#define  MACHO_CPU_SUBTYPE_VAX8800   11 
#define  MACHO_CPU_SUBTYPE_UVAXIII   12 
#define  MACHO_CPU_SUBTYPE_MC680x0_ALL   1 
#define  MACHO_CPU_SUBTYPE_MC68030   1 
#define  MACHO_CPU_SUBTYPE_MC68040   2 
#define  MACHO_CPU_SUBTYPE_MC68030_ONLY   3 
#define  MACHO_CPU_SUBTYPE_I386_ALL   3 
#define  MACHO_CPU_SUBTYPE_386   3 
#define  MACHO_CPU_SUBTYPE_486   4 
#define  MACHO_CPU_SUBTYPE_486SX   4 + 128 
#define  MACHO_CPU_SUBTYPE_586   5 
#define  MACHO_CPU_SUBTYPE_INTEL(f, m)   (f + ((m) << 4) 
#define  MACHO_CPU_SUBTYPE_PENT   MACHO_CPU_SUBTYPE_INTEL(5, 0) 
#define  MACHO_CPU_SUBTYPE_PENTPRO   MACHO_CPU_SUBTYPE_INTEL(6, 1) 
#define  MACHO_CPU_SUBTYPE_PENTII_M3   MACHO_CPU_SUBTYPE_INTEL(6, 3) 
#define  MACHO_CPU_SUBTYPE_PENTII_M5   MACHO_CPU_SUBTYPE_INTEL(6, 5) 
#define  MACHO_CPU_SUBTYPE_INTEL_FAMILY(x)   ((x) & 15) 
#define  MACHO_CPU_SUBTYPE_INTEL_FAMILY_MAX   15 
#define  MACHO_CPU_SUBTYPE_INTEL_MODEL(x)   ((x) >> 4) 
#define  MACHO_CPU_SUBTYPE_INTEL_MODEL_ALL   0 
#define  MACHO_CPU_SUBTYPE_MIPS_ALL   0 
#define  MACHO_CPU_SUBTYPE_MIPS_R2300   1 
#define  MACHO_CPU_SUBTYPE_MIPS_R2600   2 
#define  MACHO_CPU_SUBTYPE_MIPS_R2800   3 
#define  MACHO_CPU_SUBTYPE_MIPS_R2000a   4 
#define  MACHO_CPU_SUBTYPE_MIPS_R2000   5 
#define  MACHO_CPU_SUBTYPE_MIPS_R3000a   6 
#define  MACHO_CPU_SUBTYPE_MIPS_R3000   7 
#define  MACHO_CPU_SUBTYPE_MC98000_ALL   0 
#define  MACHO_CPU_SUBTYPE_MC98601   1 
#define  MACHO_CPU_SUBTYPE_HPPA_ALL   0 
#define  MACHO_CPU_SUBTYPE_HPPA_7100   0 
#define  MACHO_CPU_SUBTYPE_HPPA_7100LC   1 
#define  MACHO_CPU_SUBTYPE_MC88000_ALL   0 
#define  MACHO_CPU_SUBTYPE_MC88100   1 
#define  MACHO_CPU_SUBTYPE_MC88110   2 
#define  MACHO_CPU_SUBTYPE_SPARC_ALL   0 
#define  MACHO_CPU_SUBTYPE_I860_ALL   0 
#define  MACHO_CPU_SUBTYPE_I860_860   1 
#define  MACHO_CPU_SUBTYPE_POWERPC_ALL   0 
#define  MACHO_CPU_SUBTYPE_POWERPC_601   1 
#define  MACHO_CPU_SUBTYPE_POWERPC_602   2 
#define  MACHO_CPU_SUBTYPE_POWERPC_603   3 
#define  MACHO_CPU_SUBTYPE_POWERPC_603e   4 
#define  MACHO_CPU_SUBTYPE_POWERPC_603ev   5 
#define  MACHO_CPU_SUBTYPE_POWERPC_604   6 
#define  MACHO_CPU_SUBTYPE_POWERPC_604e   7 
#define  MACHO_CPU_SUBTYPE_POWERPC_620   8 
#define  MACHO_CPU_SUBTYPE_POWERPC_750   9 
#define  MACHO_CPU_SUBTYPE_POWERPC_7400   10 
#define  MACHO_CPU_SUBTYPE_POWERPC_7450   11 

// The values for the filetype field are defined as follows in the header file sys/loader.h: 


#define MH_OBJECT   0x1    /* relocatable object file */
#define MH_EXECUTE  0x2    /* executable object file */
#define MH_FVMLIB   0x3    /* fixed vm shared library file */
#define MH_CORE     0x4    /* core file */
#define MH_PRELOAD  0x5    /* preloaded executable file */ 

// The following constants are used for the flags field:

#define MH_NOUNDEFS  0x1  /* object file has no undefined references;
can be executed */
#define MH_INCRLINK  0x2  /* object file is the output of an
incremental link against a base file;
can't be link-edited again */ 
#define MH_DYLDLINK     0x4             /* the object file is input for the dynamic linker and can't be staticly link edited again */
#define MH_BINDATLOAD   0x8             /* the object file's undefined references are bound by the dynamic linker when loaded. */
#define MH_PREBOUND     0x10            /* the file has it's dynamic undefined references prebound. */

union lc_str
{
   unsigned long offset;
   char *ptr;
};

struct load_command
{
	unsigned long  cmd;      /* type of load command */
	unsigned long  cmdsize;  /* total size of command in bytes */
}; 

// Constants for the cmd field of the load_command structure are: 


#define LC_SEGMENT     0x1   /* file segment to be mapped */
#define LC_SYMTAB      0x2   /* link-edit stab symbol table info */
#define LC_SYMSEG      0x3   /* link-edit gdb symbol table info(obsolete) */
#define LC_THREAD      0x4   /* thread */
#define LC_UNIXTHREAD  0x5   /* UNIX thread (includes a stack) */
#define LC_LOADFVMLIB  0x6   /* load a fixed VM shared library */
#define LC_IDFVMLIB    0x7   /* fixed VM shared library id */
#define LC_IDENT       0x8   /* object identification information(obsolete) */
#define LC_FVMFILE      0x9   /* fixed VM file inclusion */ 
#define LC_PREPAGE   0xa 
#define LC_DYSYMTAB   0xb 
#define LC_LOAD_DYLIB   0xc 
#define LC_ID_DYLIB   0xd 
#define LC_LOAD_DYLINKER   0xe 
#define LC_ID_DYLINKER   0xf 
#define LC_PREBOUND_DYLIB   0x10 

typedef unsigned long vm_prot_t;

struct segment_command {
	unsigned long  cmd;          /* LC_SEGMENT */
	unsigned long  cmdsize;      /* includes size of section
	structures */
	char           segname[16];  /* segment's name */
	unsigned long  vmaddr;       /* segment's memory address */
	unsigned long  vmsize;       /* segment's memory size */
	unsigned long  fileoff;      /* segment's file offset */
	unsigned long  filesize;     /* amount to map from file */
	vm_prot_t      maxprot;      /* maximum VM protection */
	vm_prot_t      initprot;     /* initial VM protection */
	unsigned long  nsects;       /* number of sections */
	unsigned long  flags;        /* flags */
}; 

/* Constants for the flags field of the segment_command */
#define SG_HIGHVM       0x1     /* the file contents for this segment is for the high part of the VM space, the low part is zero filled (for stacks in core files) */
#define SG_FVMLIB       0x2     /* this segment is the VM that is allocated by a fixed VM library, for overlap checking in the link editor */
#define SG_NORELOC      0x4     /* this segment has nothing that was relocated in it and nothing relocated to it, that is it maybe safely replaced without relocation */

struct section
{
   char sectname[16];
   char segname[16];
   unsigned long addr;
   unsigned long size;
   unsigned long offset;
   unsigned long align;
   unsigned long reloff;
   unsigned long nreloc;
   unsigned long flags;
   unsigned long reserved1;
   unsigned long reserved2;
};

/*
 * The flags field of a section structure is separated into two parts a section
 * type and section attributes.  The section types are mutually exclusive (it
 * can only have one type) but the section attributes are not (it may have more
 * than one attribute).
 */

#define MACHO_SECTION_TYPE               0x000000ff     /* 256 section types */
#define MACHO_SECTION_ATTRIBUTES         0xffffff00     /*  24 section attributes */

/* Constants for the type of a section */
#define MACHO_S_REGULAR         0x0     /* regular section */
#define MACHO_S_ZEROFILL                0x1     /* zero fill on demand section */
#define MACHO_S_CSTRING_LITERALS        0x2     /* section with only literal C strings*/
#define MACHO_S_4BYTE_LITERALS  0x3     /* section with only 4 byte literals */
#define MACHO_S_8BYTE_LITERALS  0x4     /* section with only 8 byte literals */
#define MACHO_S_LITERAL_POINTERS        0x5     /* section with only pointers to */
                                        /*  literals */
/*
 * For the two types of symbol pointers sections and the symbol stubs section
 * they have indirect symbol table entries.  For each of the entries in the
 * section the indirect symbol table entries, in corresponding order in the
 * indirect symbol table, start at the index stored in the reserved1 field
 * of the section structure.  Since the indirect symbol table entries
 * correspond to the entries in the section the number of indirect symbol table
 * entries is inferred from the size of the section divided by the size of the
 * entries in the section.  For symbol pointers sections the size of the entries
 * in the section is 4 bytes and for symbol stubs sections the byte size of the
 * stubs is stored in the reserved2 field of the section structure.
 */
#define MACHO_S_NON_LAZY_SYMBOL_POINTERS        0x6     /* section with only non-lazy
                                                   symbol pointers */
#define MACHO_S_LAZY_SYMBOL_POINTERS            0x7     /* section with only lazy symbol
                                                   pointers */
#define MACHO_S_SYMBOL_STUBS                    0x8     /* section with only symbol
                                                   stubs, byte size of stub in
                                                   the reserved2 field */
#define MACHO_S_MOD_INIT_FUNC_POINTERS  0x9     /* section with only function
                                                   pointers for initialization*/

struct dylinker_command
{
   unsigned long cmd;
   unsigned long cmdsize;
   union lc_str name;
};

struct symtab_command
{
	unsigned long  cmd;      /* LC_SYMTAB */
	unsigned long  cmdsize;  /* sizeof(struct symtab_command) */
	unsigned long  symoff;   /* symbol table offset */
	unsigned long  nsyms;    /* number of symbol table entries */
	unsigned long  stroff;   /* string table offset */
	unsigned long  strsize;  /* string table size in bytes */
}; 

struct MACHO_SYMTAB_NLIST
{
	uint32  strx;
	uint8   type;
	uint8   sect;
	uint16  desc;
	uint32  value;
};

// masks for type
#define MACHO_SYMBOL_N_STAB     0xe0
#define MACHO_SYMBOL_N_PEXT     0x10
#define MACHO_SYMBOL_N_TYPE     0x0e
#define MACHO_SYMBOL_N_EXT      0x01

#define MACHO_SYMBOL_TYPE_N_UNDF        0x00
#define MACHO_SYMBOL_TYPE_N_ABS         0x02
#define MACHO_SYMBOL_TYPE_N_INDR        0x0a
#define MACHO_SYMBOL_TYPE_N_PBUD        0x0c
#define MACHO_SYMBOL_TYPE_N_SECT        0x0e

// n_desc
#define REFERENCE_TYPE_MASK 0xF
#define REFERENCE_FLAG_UNDEFINED_NON_LAZY (0x0)//—This symbol is a reference to an external non-lazy (data) symbol.
#define REFERENCE_FLAG_UNDEFINED_LAZY (0x1)//—This symbol is a reference to an external lazy symbol—that is, to a function call.
#define REFERENCE_FLAG_DEFINED (0x2)//—This symbol is defined in this module.
#define REFERENCE_FLAG_PRIVATE_DEFINED (0x3)//—This symbol is defined in this module and is visible only to modules within this shared library.
#define REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY (0x4)//—This symbol is defined in another module in this file, is a non-lazy (data) symbol, and is visible only to modules within this shared library.
#define REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY (0x5)//—This symbol is defined in another module in this file, is a lazy (function) symbol, and is visible only to modules within this shared library.

// Additionally these bits
#define REFERENCED_DYNAMICALLY (0x10)//—Must be set for any symbol that might be referenced by another image. The strip tool uses this bit to avoid removing symbols that must exist: If the symbol has this bit set, strip does not strip it.
#define N_DESC_DISCARDED (0x20)//—Used by the dynamic linker at runtime. Do not set this bit.
#define N_WEAK_REF (0x40)//—Indicates that this symbol is a weak reference. If the dynamic linker cannot find a definition for this symbol, it sets the address of this symbol to zero. The static linker sets this symbol given the appropriate weak-linking flags.
#define N_WEAK_DEF (0x80)//—Indicates that this symbol is a weak definition. If the static linker or the dynamic linker finds another (non-weak) definition for this symbol, the weak definition is ignored. Only symbols in a coalesced section can be marked as a weak definition

struct dysymtab_command
{
   unsigned long cmd;
   unsigned long cmdsize;
   unsigned long ilocalsym;
   unsigned long nlocalsym;
   unsigned long iextdefsym;
   unsigned long nextdefsym;
   unsigned long iundefsym;
   unsigned long nundefsym;
   unsigned long tocoff;
   unsigned long ntoc;
   unsigned long modtaboff;
   unsigned long nmodtab;
   unsigned long extrefsymoff;
   unsigned long nextrefsyms;
   unsigned long indirectsymoff;
   unsigned long nindirectsyms;
   unsigned long extreloff;
   unsigned long nextrel;
   unsigned long locreloff;
   unsigned long nlocrel;
};

struct MACHO_PPC_THREAD_STATE {
         uint32 srr0;    /* Instruction address register (PC) */
         uint32 srr1;    /* Machine state register (supervisor) */
         uint32 r0;
         uint32 r1;
         uint32 r2;
         uint32 r3;
         uint32 r4;
         uint32 r5;
         uint32 r6;
         uint32 r7;
         uint32 r8;
         uint32 r9;
         uint32 r10;
         uint32 r11;
         uint32 r12;
         uint32 r13;
         uint32 r14;
         uint32 r15;
         uint32 r16;
         uint32 r17;
         uint32 r18;
         uint32 r19;
         uint32 r20;
         uint32 r21;
         uint32 r22;
         uint32 r23;
         uint32 r24;
         uint32 r25;
         uint32 r26;
         uint32 r27;
         uint32 r28;
         uint32 r29;
         uint32 r30;
         uint32 r31;
 
         uint32 cr;      /* Condition register */
         uint32 xer;     /* User's integer exception register */
         uint32 lr;      /* Link register */
         uint32 ctr;     /* Count register */
         uint32 mq;      /* MQ register (601 only) */
 
        uint32 vrsave;  /* Vector Save Register */
};

#define FLAVOR_PPC_THREAD_STATE         1
#define FLAVOR_PPC_FLOAT_STATE          2
#define FLAVOR_PPC_EXCEPTION_STATE      3
#define FLAVOR_PPC_VECTOR_STATE         4
#define FLAVOR_THREAD_STATE_NONE        7
 
 struct MACHO_I386_THREAD_STATE {
         uint32  eax;
         uint32  ebx;
         uint32  ecx;
         uint32  edx;
         uint32  edi;
         uint32  esi;
         uint32  ebp;
         uint32  esp;
         uint32  ss;
         uint32  eflags;
         uint32  eip;
         uint32  cs;
         uint32  ds;
         uint32  es;
         uint32  fs;
         uint32  gs;
};

#define i386_NEW_THREAD_STATE   1       /* used to be i386_THREAD_STATE */
#define i386_FLOAT_STATE        2
#define i386_ISA_PORT_MAP_STATE 3
#define i386_V86_ASSIST_STATE   4
#define i386_REGS_SEGS_STATE    5
#define THREAD_SYSCALL_STATE    6
#define THREAD_STATE_NONE       7
#define i386_SAVED_STATE        8

struct thread_command
{
   unsigned long cmd;
   unsigned long cmdsize;
   unsigned long flavor;
   unsigned long count;
   /* struct cpu_thread_state state;*/
};

#if 0
struct nlist {
union {
char      *n_name;   /* for use when in-core */
long       n_strx;   /* index into file string table */
} n_un;
unsigned char  n_type;   /* type flag; see below */
unsigned char  n_sect;   /* section number or NO_SECT */
short          n_desc;   /* see the header file stab.h */
unsigned       n_value;  /* value of this symbol table entry
(or stab offset) */
}; 
#endif

}	// MachO
}

#endif // __MACHO_H_
