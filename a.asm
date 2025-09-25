.include "function.asm"


at 0x0000
start:

    jmp main

main:

    Create_Array 0x00, #10, #10
    cal Sum_Array

    mov r3, 0xff00

    hlt

    