	.text
	.globl	bitrev
	.type	bitrev, @function

bitrev:
        movq $0x3333333333333333, %rsi
		andq %rdi, %rsi
		xorq %rsi, %rdi
		rorq $2, %rdi
		rolq $2, %rsi
		orq %rsi, %rdi

		movq $0x5555555555555555, %rsi
		andq %rdi, %rsi
		xorq %rsi, %rdi
		rorq $1, %rdi
		rolq $1, %rsi
		orq %rsi, %rdi

		movq %rdi, %rax

		rolq $32, %rax
		rolb $4, %al
		rolw $8, %ax
		rolb $4, %al
		roll $16, %eax

		rolb $4, %al
		rolw $8, %ax
		rolb $4, %al

		rolb $4, %dil
		rolw $8, %di
		rolb $4, %dil
		roll $16, %edi

		rolb $4, %dil
		rolw $8, %di
		rolb $4, %dil
		rolq $32, %rdi

		orq %rdi, %rax

	ret

	.size	bitrev, .-bitrev
