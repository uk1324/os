# This will set up our new segment registers. We need to do
# something special in order to set CS. We do what is called a
# far jump. A jump that includes a segment as well as an offset.
# This is declared in C as 'extern void gdt_flush();'
.global gdt_flush     # Allows the C code to link to this
.extern gp            # Says that '_gp' is in another file
gdt_flush:
    lgdt [gp]        # Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      # 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08, flush2   # 0x08 is the offset to our code segment: Far jump!
flush2:
    ret               # Returns back to the C code!

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