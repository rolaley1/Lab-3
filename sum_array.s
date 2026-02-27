.section .text
.globl sum_array
sum_array:
    # Inputs:
    #   %rdi = pointer to int array
    #   %rsi = number of integers (long)
    # Output:
    #   %eax = sum (int)

    xor %rax, %rax          # sum = 0 (use 64-bit accumulator)
    xor %rcx, %rcx          # i = 0

.Lloop:
    cmp %rsi, %rcx
    jae .Ldone

    movslq (%rdi,%rcx,4), %rdx   # load int32, sign-extend to 64
    add %rdx, %rax

    inc %rcx
    jmp .Lloop

.Ldone:
    ret