.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15
.global irq16
.global irq17
.global irq18
.global irq19
.global irq20
.global irq21
.global irq22
.global irq23
.global irq24
.global irq25
.global irq26
.global irq27
.global irq28
.global irq29
.global irq30
.global irq31

irq0:
    cli
    push 0
    push 32    
    jmp irq_common_stub

irq1:
    cli
    push 1
    push 33    
    jmp irq_common_stub

irq2:
    cli
    push 2
    push 34  
    jmp irq_common_stub

irq3:
    cli
    push 3
    push 35
    jmp irq_common_stub

irq4:
    cli
    push 4
    push 36    
    jmp irq_common_stub

irq5:
    cli
    push 5
    push 37    
    jmp irq_common_stub

irq6:
    cli
    push 6
    push 38    
    jmp irq_common_stub

irq7:
    cli
    push 7
    push 39    
    jmp irq_common_stub

irq8:
    cli
    push 8
    push 40    
    jmp irq_common_stub

irq9:
    cli
    push 9
    push 41    
    jmp irq_common_stub

irq10:
    cli
    push 10
    push 42    
    jmp irq_common_stub

irq11:
    cli
    push 11
    push 43    
    jmp irq_common_stub

irq12:
    cli
    push 12
    push 44    
    jmp irq_common_stub

irq13:
    cli
    push 13
    push 45    
    jmp irq_common_stub

irq14:
    cli
    push 14
    push 46    
    jmp irq_common_stub

irq15:
    cli
    push 15
    push 47    
    jmp irq_common_stub

.extern irq_handler

irq_common_stub:
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
#    mov eax, _irq_handler
#    call eax
    call irq_handler
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret