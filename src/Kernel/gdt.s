.global asm_lgdt
asm_lgdt:
    lgdt [rdi]
    ret

# asm_load_cs(uint16_t);
.global asm_load_cs
asm_load_cs:
    push rdi
    push .next
    retfq
.next:
    ret

# asm_load_ds(uint16_t);
.global asm_load_ds
asm_load_ds:
    mov ds, di
    ret

# asm_load_es(uint16_t);
.global asm_load_es
asm_load_es:
    mov es, di
    ret

# asm_load_fs(uint16_t);
.global asm_load_fs
asm_load_fs:
    mov fs, di
    ret

# asm_load_gs(uint16_t);
.global asm_load_gs
asm_load_gs:
    mov gs, di
    ret

# asm_load_ss(uint16_t);
.global asm_load_ss
asm_load_ss:
    mov ss, di
    ret



# This will set up our new segment registers. We need to do
# something special in order to set CS. We do what is called a
# far jump. A jump that includes a segment as well as an offset.
## This is declared in C as 'extern void gdt_flush();'
#.global gdt_flush     # Allows the C code to link to this
#.extern gp            # Says that '_gp' is in another file
#gdt_flush:
#    lgdt [gp]        # Load the GDT with our '_gp' which is a special pointer
#    mov ax, 0x10      # 0x10 is the offset in the GDT to our data segment
#    mov ds, ax
#    mov es, ax
#    mov fs, ax
#    mov gs, ax
#    mov ss, ax
#    push 0x08
#    mov rax, flush2
#    push rax
#    retf
##    ret
##    jmp 0x08, flush2   # 0x08 is the offset to our code segment: Far jump!
#flush2:
#    ret               # Returns back to the C code!
#
## This will set up our new segment registers. We need to do
## something special in order to set CS. We do what is called a
## far jump. A jump that includes a segment as well as an offset.
## This is declared in C as 'extern void gdt_flush();'
## https://stackoverflow.com/questions/23978486/far-jump-in-gdt-in-bootloader
## https://newbedev.com/assembly-executing-a-long-jump-with-an-offset-with-different-syntax
#.global gdt_flush     # Allows the C code to link to this
#.extern gp            # Says that '_gp' is in another file
#gdt_flush:
#    lgdt [gp]         # Load the GDT with our '_gp' which is a special pointer
#    mov ax, 0x10      # 0x10 is the offset in the GDT to our data segment
#    mov ds, ax
#    mov es, ax
#    mov fs, ax
#    mov gs, ax
#    mov ss, ax
#    jmp 0x08, flush2   # 0x08 is the offset to our code segment: Far jump!
#flush2:
#    ret               # Returns back to the C code!
#
#
## Loads the IDT defined in '_idtp' into the processor.
## This is declared in C as 'extern void idt_load();'
#.global idt_load
#.extern idtp
#idt_load:
#    lidt [idtp]
#    sti
#    ret