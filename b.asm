inc
add
sub
lrs

nand
or
xor

ldi
rtr
lod
str 
rpc
pcr

snd
sdi
rec 
wre 

jmp
jif
cal
cif
hlt

r0 r7

0xff

#10
#0b01011111
#0x00ff

10 
0b0101
0xff

label:

label
Inline_Macro_Name

Macro_Name r0 r2 r3 r7 r8 r9



.include "a.asm"
.extern "a.asm"



//vorp

.glob label
.glob MUL_3
.glob some_label

.inline_macro Inline_Macro_Name stuffstuffstuf


.macrostart Macro_Name arg1 arg2 arg3 

add arg1 arg2 arg3 arg4
add arg2 arg3 arg1

.macroend


