
at 0x00

.macro MUL_3 reg_dest reg_src 

    add reg_dest reg_src reg_src
    add reg_dest reg_dest reg_src

.macroend


start:

    jmp main


main:

    wre r0 io1

    MUL_3 r1 r0

    snd r1 io1



    add * r0 r1 $



    hlt




