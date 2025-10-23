

.include "c.asm"

.glob some_label

at 0x00

.glob MUL_3


.macrostart MUL_3 reg_dest reg_src 

    add reg_dest reg_src reg_src
    add reg_dest reg_dest reg_src

.macroend



start:

    jmp main


main:

    wre r0, io1

    MUL_3 r1, r0

    snd r1 io1

    "string" label:



