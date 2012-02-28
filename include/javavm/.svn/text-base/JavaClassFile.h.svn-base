#ifndef __JavaClassFile_h__
#define __JavaClassFile_h__

#define JAVA_MAGIC	0xCAFEBABE

enum
{
	CONSTANT_Class  = 7,
	CONSTANT_Fieldref =  9,
	CONSTANT_Methodref = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_String = 8,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_Long = 5,
	CONSTANT_Double = 6,
	CONSTANT_NameAndType = 12,
	CONSTANT_Utf8 = 1,
};

// class/interface Access flags
#define ACC_PUBLIC  0x0001  //Declared public; may be accessed from outside its package.  
#define ACC_FINAL  0x0010  //Declared final; no subclasses allowed.  
#define ACC_SUPER  0x0020  //Treat superclass methods specially when invoked by the invokespecial instruction.  
#define ACC_INTERFACE  0x0200  //Is an interface, not a class.  
#define ACC_ABSTRACT  0x0400  //Declared abstract; may not be instantiated.  
#define ACC_INTERFACE_BIT 9
#define ACC_ABSTRACT_BIT 10

// method Access flags
#define ACC_PUBLIC	0x0001//  Declared public; may be accessed from outside its package.  
#define ACC_PRIVATE  0x0002 // Declared private; accessible only within the defining class.  
#define ACC_PROTECTED  0x0004//  Declared protected; may be accessed within subclasses.  
#define ACC_STATIC  0x0008 // Declared static.  
#define ACC_FINAL  0x0010 // Declared final; may not be overridden.  
#define ACC_SYNCHRONIZED  0x0020 // Declared synchronized; invocation is wrapped in a monitor lock.  
#define ACC_NATIVE  0x0100 // Declared native; implemented in a language other than Java.  
#define ACC_ABSTRACT  0x0400//  Declared abstract; no implementation is provided.  
#define ACC_STRICT  0x0800 // Declared strictfp; floating-point mode is FP-strict  

// field Access flags
#define ACC_PUBLIC  0x0001  //Declared public; may be accessed from outside its package.  
#define ACC_PRIVATE  0x0002  //Declared private; usable only within the defining class.  
#define ACC_PROTECTED  0x0004  //Declared protected; may be accessed within subclasses.  
#define ACC_STATIC  0x0008  //Declared static.  
#define ACC_FINAL  0x0010  //Declared final; no further assignment after initialization.  
#define ACC_VOLATILE  0x0040  //Declared volatile; cannot be cached.  
#define ACC_TRANSIENT  0x0080  //Declared transient; not written or read by a persistent object manager.  

namespace System
{

namespace javavm
{

// Opcodes
enum
{
JOP_nop,
JOP_aconst_null,
JOP_iconst_m1,
JOP_iconst_0,
JOP_iconst_1,
JOP_iconst_2,
JOP_iconst_3,
JOP_iconst_4,
JOP_iconst_5,
JOP_lconst_0,
JOP_lconst_1,
JOP_fconst_0,
JOP_fconst_1,
JOP_fconst_2,
JOP_dconst_0,
JOP_dconst_1,
JOP_bipush,
JOP_sipush,
JOP_ldc,
JOP_ldc_w,
JOP_ldc2_w,
JOP_iload,
JOP_lload,
JOP_fload,
JOP_dload,
JOP_aload,
JOP_iload_0,
JOP_iload_1,
JOP_iload_2,
JOP_iload_3,
JOP_lload_0,
JOP_lload_1,
JOP_lload_2,
JOP_lload_3,
JOP_fload_0,
JOP_fload_1,
JOP_fload_2,
JOP_fload_3,
JOP_dload_0,
JOP_dload_1,
JOP_dload_2,
JOP_dload_3,
JOP_aload_0,
JOP_aload_1,
JOP_aload_2,
JOP_aload_3,
JOP_iaload,
JOP_laload,
JOP_faload,
JOP_daload,
JOP_aaload,
JOP_baload,
JOP_caload,
JOP_saload,
JOP_istore,
JOP_lstore,
JOP_fstore,
JOP_dstore,
JOP_astore,
JOP_istore_0,
JOP_istore_1,
JOP_istore_2,
JOP_istore_3,
JOP_lstore_0,
JOP_lstore_1,
JOP_lstore_2,
JOP_lstore_3,
JOP_fstore_0,
JOP_fstore_1,
JOP_fstore_2,
JOP_fstore_3,
JOP_dstore_0,
JOP_dstore_1,
JOP_dstore_2,
JOP_dstore_3,
JOP_astore_0,
JOP_astore_1,
JOP_astore_2,
JOP_astore_3,
JOP_iastore,
JOP_lastore,
JOP_fastore,
JOP_dastore,
JOP_aastore,
JOP_bastore,
JOP_castore,
JOP_sastore,
JOP_pop,
JOP_pop2,
JOP_dup,
JOP_dup_x1,
JOP_dup_x2,
JOP_dup2,
JOP_dup2_x1,
JOP_dup2_x2,
JOP_swap,
JOP_iadd,
JOP_ladd,
JOP_fadd,
JOP_dadd,
JOP_isub,
JOP_lsub,
JOP_fsub,
JOP_dsub,
JOP_imul,
JOP_lmul,
JOP_fmul,
JOP_dmul,
JOP_idiv,
JOP_ldiv,
JOP_fdiv,
JOP_ddiv,
JOP_irem,
JOP_lrem,
JOP_frem,
JOP_drem,
JOP_ineg,
JOP_lneg,
JOP_fneg,
JOP_dneg,
JOP_ishl,
JOP_lshl,
JOP_ishr,
JOP_lshr,
JOP_iushr,
JOP_lushr,
JOP_iand,
JOP_land,
JOP_ior,
JOP_lor,
JOP_ixor,
JOP_lxor,
JOP_iinc,
JOP_i2l,
JOP_i2f,
JOP_i2d,
JOP_l2i,
JOP_l2f,
JOP_l2d,
JOP_f2i,
JOP_f2l,
JOP_f2d,
JOP_d2i,
JOP_d2l,
JOP_d2f,
JOP_i2b,
JOP_i2c,
JOP_i2s,
JOP_lcmp,
JOP_fcmpl,
JOP_fcmpg,
JOP_dcmpl,
JOP_dcmpg,
JOP_ifeq,
JOP_ifne,
JOP_iflt,
JOP_ifge,
JOP_ifgt,
JOP_ifle,
JOP_if_icmpeq,
JOP_if_icmpne,
JOP_if_icmplt,
JOP_if_icmpge,
JOP_if_icmpgt,
JOP_if_icmple,
JOP_if_acmpeq,
JOP_if_acmpne,
JOP_goto,
JOP_jsr,
JOP_ret,
JOP_tableswitch,
JOP_lookupswitch,
JOP_ireturn,
JOP_lreturn,
JOP_freturn,
JOP_dreturn,
JOP_areturn,
JOP_return,
JOP_getstatic,
JOP_putstatic,
JOP_getfield,
JOP_putfield,
JOP_invokevirtual,
JOP_invokespecial,
JOP_invokestatic,
JOP_invokeinterface,
JOP_xxxunusedxxx1,
JOP_new,
JOP_newarray,
JOP_anewarray,
JOP_arraylength,
JOP_athrow,
JOP_checkcast,
JOP_instanceof,
JOP_monitorenter,
JOP_monitorexit,
JOP_wide,
JOP_multianewarray,
JOP_ifnull,
JOP_ifnonnull,
JOP_goto_w,
JOP_jsr_w,
};

}
}

#endif // __JavaClassFile_h__
