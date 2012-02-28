// a.out

#ifndef __A_OUT_H_
#define __A_OUT_H_

//#pragma pack(push,1)

struct exec {
        unsigned long   a_midmag;
        unsigned long   a_text;
        unsigned long   a_data;
        unsigned long   a_bss;
        unsigned long   a_syms;
        unsigned long   a_entry;
        unsigned long   a_trsize;
        unsigned long   a_drsize;
};

#define N_GETMAGIC(x) (BigEndian32((x)->a_midmag) & 0xffff)

#define _MAGIC(b)   ((((4*b)+0)*b)+7)
#define A_MAGIC     _MAGIC(8)   /* 68020 */
#define I_MAGIC     _MAGIC(11)  /* intel 386 */
#define J_MAGIC     _MAGIC(12)  /* intel 960 */
#define K_MAGIC     _MAGIC(13)  /* sparc */
#define V_MAGIC     _MAGIC(16)  /* mips 3000 */
#define X_MAGIC     _MAGIC(17)  /* att dsp 3210 */
#define M_MAGIC     _MAGIC(18)  /* mips 4000 */
#define D_MAGIC     _MAGIC(19)  /* amd 29000 */
#define E_MAGIC     _MAGIC(20)  /* arm 7-something */
#define Q_MAGIC     _MAGIC(21)  /* powerpc */
#define N_MAGIC     _MAGIC(22)  /* mips 4000-le */
#define L_MAGIC     _MAGIC(23)  /* dec alpha */

struct relocation_info {
        int             r_address;
        unsigned int    
                        r_pcrel : 1,
                        r_length : 2,
                        r_extern : 1,
                        r_baserel : 1,
                        r_jmptable : 1,
                        r_relative : 1,
                        r_copy : 1,
											r_symbolnum : 24;
};

//#pragma pack(pop)


#endif // __A_OUT_H_
