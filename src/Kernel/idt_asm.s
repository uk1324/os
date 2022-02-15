.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

isr0:
    cli
    push 0
    push 1
    jmp isr_common_stub

isr1:
    cli
    push 1
    push 1
    jmp isr_common_stub

isr2:
    cli
    push 2
    push 1
    jmp isr_common_stub

isr3:
    cli
    push 3
    push 1
    jmp isr_common_stub

isr4:
    cli
    push 4
    push 1
    jmp isr_common_stub

isr5:
    cli
    push 5
    push 1
    jmp isr_common_stub

isr6:
    cli
    push 6
    push 1
    jmp isr_common_stub

isr7:
    cli
    push 7
    push 1
    jmp isr_common_stub

isr8:
    cli
    push 8
    jmp isr_common_stub

isr9:
    cli
    push 9
    push 1
    jmp isr_common_stub

isr10:
    cli
    push 10
    jmp isr_common_stub

isr11:
    cli
    push 11
    jmp isr_common_stub

isr12:
    cli
    push 12
    jmp isr_common_stub

isr13:
    cli
    push 13
    jmp isr_common_stub

isr14:
    cli
    push 14
    jmp isr_common_stub

isr15:
    cli
    push 15
    push 1
    jmp isr_common_stub

isr16:
    cli
    push 16
    push 1
    jmp isr_common_stub

isr17:
    cli
    push 17
    push 1
    jmp isr_common_stub

isr18:
    cli
    push 18
    push 1
    jmp isr_common_stub

isr19:
    cli
    push 19
    push 1
    jmp isr_common_stub

isr20:
    cli
    push 20
    push 1
    jmp isr_common_stub

isr21:
    cli
    push 21
    push 1
    jmp isr_common_stub

isr22:
    cli
    push 22
    push 1
    jmp isr_common_stub

isr23:
    cli
    push 23
    push 1
    jmp isr_common_stub

isr24:
    cli
    push 24
    push 1
    jmp isr_common_stub

isr25:
    cli
    push 25
    push 1
    jmp isr_common_stub

isr26:
    cli
    push 26
    push 1
    jmp isr_common_stub

isr27:
    cli
    push 27
    push 1
    jmp isr_common_stub

isr28:
    cli
    push 28
    push 1
    jmp isr_common_stub

isr29:
    cli
    push 29
    push 1
    jmp isr_common_stub

isr30:
    cli
    push 30
    push 1
    jmp isr_common_stub

isr31:
    cli
    push 31
    push 1
    jmp isr_common_stub

.extern handle_interrupt

isr_common_stub:
	cli
    push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

	mov rdi, rsp
	call handle_interrupt

	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax

	add rsp, 16
	iretq

#.global idt_load
#.extern idtp
#idt_load:
#    lidt [idtp]
#    ret
# 		
# .global isr0
# .global isr1
# .global isr2
# .global isr3
# .global isr4
# .global isr5
# .global isr6
# .global isr7
# .global isr8
# .global isr9
# .global isr10
# .global isr11
# .global isr12
# .global isr13
# .global isr14
# .global isr15
# .global isr16
# .global isr17
# .global isr18
# .global isr19
# .global isr20
# .global isr21
# .global isr22
# .global isr23
# .global isr24
# .global isr25
# .global isr26
# .global isr27
# .global isr28
# .global isr29
# .global isr30
# .global isr31
# 
# isr0:
#     cli
#     push 0
#     push 1
#     jmp isr_common_stub
# 
# isr1:
#     cli
#     push 1
#     push 1
#     jmp isr_common_stub
# 
# isr2:
#     cli
#     push 2
#     push 1
#     jmp isr_common_stub
# 
# isr3:
#     cli
#     push 3
#     push 1
#     jmp isr_common_stub
# 
# isr4:
#     cli
#     push 4
#     push 1
#     jmp isr_common_stub
# 
# isr5:
#     cli
#     push 5
#     push 1
#     jmp isr_common_stub
# 
# isr6:
#     cli
#     push 6
#     push 1
#     jmp isr_common_stub
# 
# isr7:
#     cli
#     push 7
#     push 1
#     jmp isr_common_stub
# 
# isr8:
#     cli
#     push 8
#     jmp isr_common_stub
# 
# isr9:
#     cli
#     push 9
#     push 1
#     jmp isr_common_stub
# 
# isr10:
#     cli
#     push 10
#     jmp isr_common_stub
# 
# isr11:
#     cli
#     push 11
#     jmp isr_common_stub
# 
# isr12:
#     cli
#     push 12
#     jmp isr_common_stub
# 
# isr13:
#     cli
#     push 13
#     jmp isr_common_stub
# 
# isr14:
#     cli
#     push 14
#     jmp isr_common_stub
# 
# isr15:
#     cli
#     push 15
#     push 1
#     jmp isr_common_stub
# 
# isr16:
#     cli
#     push 16
#     push 1
#     jmp isr_common_stub
# 
# isr17:
#     cli
#     push 17
#     push 1
#     jmp isr_common_stub
# 
# isr18:
#     cli
#     push 18
#     push 1
#     jmp isr_common_stub
# 
# isr19:
#     cli
#     push 19
#     push 1
#     jmp isr_common_stub
# 
# isr20:
#     cli
#     push 20
#     push 1
#     jmp isr_common_stub
# 
# isr21:
#     cli
#     push 21
#     push 1
#     jmp isr_common_stub
# 
# isr22:
#     cli
#     push 22
#     push 1
#     jmp isr_common_stub
# 
# isr23:
#     cli
#     push 23
#     push 1
#     jmp isr_common_stub
# 
# isr24:
#     cli
#     push 24
#     push 1
#     jmp isr_common_stub
# 
# isr25:
#     cli
#     push 25
#     push 1
#     jmp isr_common_stub
# 
# isr26:
#     cli
#     push 26
#     push 1
#     jmp isr_common_stub
# 
# isr27:
#     cli
#     push 27
#     push 1
#     jmp isr_common_stub
# 
# isr28:
#     cli
#     push 28
#     push 1
#     jmp isr_common_stub
# 
# isr29:
#     cli
#     push 29
#     push 1
#     jmp isr_common_stub
# 
# isr30:
#     cli
#     push 30
#     push 1
#     jmp isr_common_stub
# 
# isr31:
#     cli
#     push 31
#     push 1
#     jmp isr_common_stub
# 
# .extern fault_handler
# 
# # Remove later
# .global isr_common_stub
# 
# isr_common_stub:
#     pusha
#     push ds
#     push es
#     push fs
#     push gs
#     mov ax, 0x10   
#     mov ds, ax
#     mov es, ax
#     mov fs, ax
#     mov gs, ax
#     mov eax, esp  
#     push eax
# #    mov eax, fault_handler
# #    call eax
#     call fault_handler
#     pop eax
#     pop gs
#     pop fs
#     pop es
#     pop ds
#     popa
#     add esp, 8     
#     iret        
# 
# #/*.extern exception_handler
# #
# #.macro isr_err_stub number
# #    isr_stub_\number:
# #        pushad
# #        mov eax, \number
# #        push eax
# #        call exception_handler
# #        popad
#        iret
#.endm
#
#.macro isr_no_err_stub number
#    isr_stub_\number:
#        pushad
#        mov eax, \number
#        push eax
#        call exception_handler
#        popad
#        iret
#.endm
#
#.section .text
#
#isr_no_err_stub 0
#isr_no_err_stub 1
#isr_no_err_stub 2
#isr_no_err_stub 3
#isr_no_err_stub 4
#isr_no_err_stub 5
#isr_no_err_stub 6
#isr_no_err_stub 7
#isr_err_stub    8
#isr_no_err_stub 9
#isr_err_stub    10
#isr_err_stub    11
#isr_err_stub    12
#isr_err_stub    13
#isr_err_stub    14
#isr_no_err_stub 15
#isr_no_err_stub 16
#isr_err_stub    17
#isr_no_err_stub 18
#isr_no_err_stub 19
#isr_no_err_stub 20
#isr_no_err_stub 21
#isr_no_err_stub 22
#isr_no_err_stub 23
#isr_no_err_stub 24
#isr_no_err_stub 25
#isr_no_err_stub 26
#isr_no_err_stub 27
#isr_no_err_stub 28
#isr_no_err_stub 29
#isr_err_stub    30
#isr_no_err_stub 31
#
#.data 
#
#.global isr_stub_table
#isr_stub_table:
#.long isr_stub_0
#.long isr_stub_1
#.long isr_stub_2
#.long isr_stub_3
#.long isr_stub_4
#.long isr_stub_5
#.long isr_stub_6
#.long isr_stub_7
#.long isr_stub_8
#.long isr_stub_9
#.long isr_stub_10
#.long isr_stub_11
#.long isr_stub_12
#.long isr_stub_13
#.long isr_stub_14
#.long isr_stub_15
#.long isr_stub_16
#.long isr_stub_17
#.long isr_stub_18
#.long isr_stub_19
#.long isr_stub_20
#.long isr_stub_21
#.long isr_stub_22
#.long isr_stub_23
#.long isr_stub_24
#.long isr_stub_25
#.long isr_stub_26
#.long isr_stub_27
#.long isr_stub_28
#.long isr_stub_29
#.long isr_stub_30
#.long isr_stub_31
#*/
#
#
## In just a few pages in this tutorial, we will add our Interrupt
## Service Routines (ISRs) right here!
#.global _isr0
#.global _isr1
#.global _isr2
#.global _isr3
#.global _isr4
#.global _isr5
#.global _isr6
#.global _isr7
#.global _isr8
#.global _isr9
#.global _isr10
#.global _isr11
#.global _isr12
#.global _isr13
#.global _isr14
#.global _isr15
#.global _isr16
#.global _isr17
#.global _isr18
#.global _isr19
#.global _isr20
#.global _isr21
#.global _isr22
#.global _isr23
#.global _isr24
#.global _isr25
#.global _isr26
#.global _isr27
#.global _isr28
#.global _isr29
#.global _isr30
#.global _isr31
#
##  0: Divide By Zero Exception
#_isr0:
#    cli
#    push 0    # A normal ISR stub that pops a dummy error code to keep a
#                   # uniform stack frame
#    push  0
#    jmp isr_common_stub
#
##  1: Debug Exception
#_isr1:
#    cli
#    push   0
#    push  1
#    jmp isr_common_stub
#    
#_isr2:
#    cli
#    push  0
#    push  2
#    jmp isr_common_stub
#
#_isr3:
#    cli
#    push  0
#    push  3
#    jmp isr_common_stub
#
#_isr4:
#    cli
#    push  0
#    push  4
#    jmp isr_common_stub
#
#_isr5:
#    cli
#    push  0
#    push  5
#    jmp isr_common_stub
#
#_isr6:
#    cli
#    push  0
#    push  6
#    jmp isr_common_stub
#
#_isr7:
#    cli
#    push  0
#    push  7
#    jmp isr_common_stub
#
##  8: Double Fault Exception (With Error Code!)
#_isr8:
#    cli
#    push  8        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr9:
#    cli
#    push  0
#    push  9     # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr10:
#    cli
#    push  10        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub  
#
#_isr11:
#    cli
#    push  11        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr12:
#    cli
#    push  12        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr13:
#    cli
#    push  13        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#
#_isr14:
#    cli
#    push  14        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#
#_isr15:
#    cli
#    push  0
#    push  15        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr16:
#    cli
#    push  0
#    push  16        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#
#_isr17:
#    cli
#    push  0
#    push  17        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr18:
#    cli
#    push  0
#    push  18        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr19:
#    cli
#    push  0
#    push  19        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#
#_isr20:
#    cli
#    push  0
#    push  20        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr21:
#    cli
#    push  0
#    push  21        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr22:
#    cli
#    push  0
#    push  22        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr23:
#    cli
#    push  0
#    push  23        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr24:
#    cli
#    push  0
#    push  24        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr25:
#    cli
#    push  0
#    push  25        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr26:
#    cli
#    push  0
#    push  26        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr27:
#    cli
#    push  0
#    push  27        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr28:
#    cli
#    push  0
#    push  28        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr29:
#    cli
#    push  0
#    push  29        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr30:
#    cli
#    push  0
#    push  30        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
#
#_isr31:
#    cli
#    push  0
#    push  31        # Note that we DON'T push a value on the stack in this one!
#                   # It pushes one already! Use this type of stub for exceptions
#                   # that pop error codes!
#    jmp isr_common_stub
## We call a C function in here. We need to let the assembler know
## that '_fault_handler' exists in another file
#.extern fault_handler
#
#
## This is our common ISR stub. It saves the processor state, sets
## up for kernel mode segments, calls the C-level fault handler,
## and finally restores the stack frame.
#isr_common_stub:
#    pusha
#    push ds
#    push es
#    push fs
#    push gs
#    mov ax, 0x10   # Load the Kernel Data Segment descriptor!
#    mov ds, ax
#    mov es, ax
#    mov fs, ax
#    mov gs, ax
#    mov eax, esp   # Push us the stack
#    push eax
#    mov eax, fault_handler
#    call eax       # A special call, preserves the 'eip' register
##    call fault_handler
#    pop eax
#    pop gs
#    pop fs
#    pop es
#    pop ds
#    popa
#    add esp, 8     # Cleans up the pushed error code and pushed ISR number
#    iret           # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!