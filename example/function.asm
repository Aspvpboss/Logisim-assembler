
.glob Sum_Array
.glob Create_Array

at 0x0f00

.macro Create_Array immediate_pointer, value, length
    mov r0, #0

    loop_macro:

        mov [immediate_pointer, r0], value
        cmp value, length
        jif >= macro_ret
        add r0, r0, #1
        jmp

    macro_ret:

        mov r0, immediate_pointer 
        mov r1, length
        ret
.macroend

Sum_Array:

    ; r0 pointer to array 
    ; r1 length of array  
    ; r3 will contain sum

    mov r2, #0
    mov r3, #0
    mov r4, #0

    for_loop:

        mov r4, [r0, r2]
        add r3, r3, r4
        add r2, r2, #1
        cmp r2, r1
        jif >= function_ret

        add r2, r2, #1

        jmp for_loop

    function_ret:
        ret



