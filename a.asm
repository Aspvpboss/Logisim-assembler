


add
add
add
add

.include "c.asm"

<<<<<<< HEAD
add
add
add
add

some_label:

.glob some_label

=======
>>>>>>> e60f5a8a53fac5a789fe331f9df59be2f0905ca1
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



