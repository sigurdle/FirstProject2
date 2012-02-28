EXTERN regs:PROC


; volatile registers:
; RCX, RDX, R8, R9, XMM0, XMM1, XMM2, XMM3
; RAX, R10, R11, XMM4, and XMM5 

.code

PUBLIC int64_invoke_function_fastcall64
int64_invoke_function_fastcall64 proc ; rcx=func_address,rdx=args,r8=nargs

;	mov		qword ptr [rsp+32],r9
	mov		qword ptr [rsp+24],r8
	mov		qword ptr [rsp+16],rdx
	mov		qword ptr [rsp+8],rcx

	push	rbp
	mov		rbp,rsp
	push	r12
	
	mov		rsi,rdx			; args	

	mov		r12,r8			; nargs
	shl		r12,3			; make it bytes
	
	mov		rcx,r8			; nargs

	sub		rsp,r12			; allocate stack space
	mov		rdi,rsp			; start of destination stack frame
;	shr		rcx,3			; make it qwords
	rep		movsq			; copy params to real stack

; as integer/pointer
	mov		rcx,qword ptr[rsp+0]
	mov		rdx,qword ptr[rsp+8]
	mov		r8,qword ptr[rsp+16]
	mov		r9,qword ptr[rsp+24]

; as float/double
;	mov		xmm0,rcx
;	mov		xmm1,qword ptr[rbp+16]
;	mov		xmm2,qword ptr[rbp+24]
;	mov		xmm3,qword ptr[rbp+32]

	call	qword ptr[rbp+8+8]

	add		rsp,r12	;	args_bytes
	pop		r12
	pop		rbp
	ret
int64_invoke_function_fastcall64 endp

PUBLIC float_invoke_function_fastcall64
float_invoke_function_fastcall64 proc ; rcx=func_address,rdx=args,r8=nargs

;	mov		qword ptr [rsp+32],r9
	mov		qword ptr [rsp+24],r8
	mov		qword ptr [rsp+16],rdx
	mov		qword ptr [rsp+8],rcx

	push	rbp
	mov		rbp,rsp
	
	mov		rsi,rdx			; args	

	mov		r10,r8			; nargs
	shl		r10,3			; make it bytes
	
	mov		rcx,r8			; nargs

	sub		rsp,r10			; allocate stack space
	mov		rdi,rsp			; start of destination stack frame
;	shr		rcx,3			; make it qwords
	rep		movsq			; copy params to real stack

; as integer/pointer
	mov		rcx,qword ptr[rsp+0]
	mov		rdx,qword ptr[rsp+8]
	mov		r8,qword ptr[rsp+16]
	mov		r9,qword ptr[rsp+24]

; as float/double
;	mov		xmm0,rcx
;	mov		xmm1,qword ptr[rbp+16]
;	mov		xmm2,qword ptr[rbp+24]
;	mov		xmm3,qword ptr[rbp+32]

	call	qword ptr[rbp+8+8]

	add		rsp,r10	;	args_bytes
	pop		rbp
	ret
float_invoke_function_fastcall64 endp

PUBLIC double_invoke_function_fastcall64
double_invoke_function_fastcall64 proc ; rcx=func_address,rdx=args,r8=nargs

;	mov		qword ptr [rsp+32],r9
	mov		qword ptr [rsp+24],r8
	mov		qword ptr [rsp+16],rdx
	mov		qword ptr [rsp+8],rcx

	push	rbp
	mov		rbp,rsp
	
	mov		rsi,rdx			; args	

	mov		r10,r8			; nargs
	shl		r10,3			; make it bytes
	
	mov		rcx,r8			; nargs

	sub		rsp,r10			; allocate stack space
	mov		rdi,rsp			; start of destination stack frame
;	shr		rcx,3			; make it qwords
	rep		movsq			; copy params to real stack

; as integer/pointer
	mov		rcx,qword ptr[rsp+0]
	mov		rdx,qword ptr[rsp+8]
	mov		r8,qword ptr[rsp+16]
	mov		r9,qword ptr[rsp+24]

; as float/double
;	mov		xmm0,rcx
;	mov		xmm1,qword ptr[rbp+16]
;	mov		xmm2,qword ptr[rbp+24]
;	mov		xmm3,qword ptr[rbp+32]

	call	qword ptr[rbp+8+8]

	add		rsp,r10	;	args_bytes
	pop		rbp
	ret
double_invoke_function_fastcall64 endp


PUBLIC void_invoke_function_stdcall
void_invoke_function_stdcall proc ; (ULONG_PTR func, const void* args, uint32 sz)
	int 3
	ret
void_invoke_function_stdcall endp

PUBLIC void_invoke_function_cdecl
void_invoke_function_cdecl proc	; (ULONG_PTR func, const void* args, uint32 sz)
	int 3
	ret
void_invoke_function_cdecl endp

PUBLIC int32_invoke_function_stdcall
int32_invoke_function_stdcall proc ; (ULONG_PTR func, const void* args, uint32 sz)
	int 3
int32_invoke_function_stdcall endp

PUBLIC pointer_invoke_function_stdcall
pointer_invoke_function_stdcall proc
	int 3
pointer_invoke_function_stdcall endp

pointer_invoke_function_cdecl proc
	int 3
pointer_invoke_function_cdecl endp

PUBLIC int32_invoke_function_cdecl
int32_invoke_function_cdecl proc
	int 3
int32_invoke_function_cdecl endp

PUBLIC float_invoke_function_cdecl
float_invoke_function_cdecl proc
	int 3
float_invoke_function_cdecl endp

PUBLIC float_invoke_function_stdcall
float_invoke_function_stdcall proc
	int 3
float_invoke_function_stdcall endp

PUBLIC double_invoke_function_cdecl
double_invoke_function_cdecl proc
	int 3
double_invoke_function_cdecl endp

PUBLIC double_invoke_function_stdcall
double_invoke_function_stdcall proc
	int 3
double_invoke_function_stdcall endp

PUBLIC struct_invoke_function_cdecl
struct_invoke_function_cdecl proc
	int 3
struct_invoke_function_cdecl endp

PUBLIC struct_invoke_function_stdcall
struct_invoke_function_stdcall proc
	int 3
struct_invoke_function_stdcall endp

PUBLIC struct_invoke_method32
struct_invoke_method32 proc
	int 3
struct_invoke_method32 endp

PUBLIC void_invoke_method32
void_invoke_method32 proc ; rcx=func_address,rdx=args,r8=args_bytes

	mov		qword ptr [rsp+32],r9
	mov		qword ptr [rsp+24],r8
	mov		qword ptr [rsp+16],rdx
	mov		qword ptr [rsp+8],rcx

	push	rbp
	mov		rbp,rsp
	
	mov		rsi,rdx			; get buffer	
	sub		rsp,r8			; allocate stack space
	mov		rdi,rsp			; start of destination stack frame
	shr		rcx,3			; make it qwords
	rep		movsd			; copy params to real stack

; integer/pointer
	mov		rcx,qword ptr[rbp+8]
	mov		rdx,qword ptr[rbp+16]
	mov		r8,qword ptr[rbp+24]
	mov		r9,qword ptr[rbp+32]

; float/double
;	mov		xmm0,rcx
;	mov		xmm1,qword ptr[rbp+16]
;	mov		xmm2,qword ptr[rbp+24]
;	mov		xmm3,qword ptr[rbp+32]

	call	qword ptr[rbp+8]

	add		rsp,qword ptr [rbp+24]	;	args_bytes
	pop		rbp
	ret
void_invoke_method32 endp

PUBLIC int32_invoke_method32
int32_invoke_method32 proc
	int 3
int32_invoke_method32 endp

PUBLIC int64_invoke_method32
int64_invoke_method32 proc
	int 3
int64_invoke_method32 endp

PUBLIC float_invoke_method32
float_invoke_method32 proc
	int 3
float_invoke_method32 endp

PUBLIC double_invoke_method32
double_invoke_method32 proc
	int 3
double_invoke_method32 endp

saveregs proc

	mov qword ptr[regs+0],rax
	mov qword ptr[regs+8],rcx
	mov qword ptr[regs+16],rdx
	mov qword ptr[regs+24],rbx
	mov qword ptr[regs+32],rsi
	mov qword ptr[regs+40],rdi
	mov qword ptr[regs+48],rbp
	mov qword ptr[regs+56],rsp

	mov qword ptr[regs+64],r8
	mov qword ptr[regs+72],r9
	mov qword ptr[regs+80],r10
	mov qword ptr[regs+88],r11
	mov qword ptr[regs+96],r12
	mov qword ptr[regs+104],r13
	mov qword ptr[regs+112],r14
	mov qword ptr[regs+120],r15

	ret

saveregs endp

end
