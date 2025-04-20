main
% Multiplication operation
	addi r12,r0,2
	addi r11,r0,3
	mul r10,r12,r11
	sw -12(r14),r10
% add operation
	addi r12,r0,1
	lw r11,-12(r14)
	add r10,r12,r11
	sw -16(r14),r10
% assignment operation
	lw r12,-16(r14)
	sw -4(r14),r12
% assignment operation
	sub r12,r12,r12
	addi r12,r12,10
	sw 0(r14),r12
% add operation
	lw r12,-4(r14)
	addi r11,r0,10
	add r10,r12,r11
	sw -20(r14),r10
% Greater than operation compare
	lw r12,0(r14)
	lw r11,-20(r14)
	cgt r10,r12,r11
	sw -24(r14),r10
	lw r12,-24(r14)
% if statement
	bz r12,endif0
% add operation
	lw r11,0(r14)
	addi r10,r0,1
	add r9,r11,r10
	sw -28(r14),r9
% assignment operation
	lw r11,-28(r14)
	sw 0(r14),r11
endif0	nop
% assignment operation
	sub r12,r12,r12
	addi r12,r12,9
	sw -8(r14),r12
% while loop
gowhile0	nop
% Less than or equal to operation compare
	lw r12,-8(r14)
	addi r11,r0,10
	cle r10,r12,r11
	sw -32(r14),r10
	lw r12,-32(r14)
	bz r12,endwhile0
% write Statement
	lw r11,-8(r14)
	sw -40(r14),r15
	addi r14,r14,-44
	sw -8(r14),r11
	addi r11,r0,buf
	sw -12(r14),r11
	jl r15,intstr
	sw -8(r14), r13
	jl r15, putstr
	subi r14,r14,-44
	lw r15,-40(r14)
% add operation
	lw r11,-8(r14)
	addi r10,r0,1
	add r9,r11,r10
	sw -36(r14),r9
% assignment operation
	lw r11,-36(r14)
	sw -8(r14),r11
	j gowhile0
endwhile0	nop
% read
	addi r12,r0,buf
	sw -8(r14),r12
	sw -40(r14),r15
	addi r11,r0,10
	putc r11
	addi r11,r0,63
	putc r11
	addi r11,r0,58
	putc r11
	jl r15,getstr
	lw r15,-40(r14)
	sw -40(r14),r15
	jl r15,strint
	lw r15,-40(r14)
	sw 0(r14),r13
% write Statement
	lw r12,0(r14)
	sw -40(r14),r15
	addi r14,r14,-44
	sw -8(r14),r12
	addi r12,r0,buf
	sw -12(r14),r12
	jl r15,intstr
	sw -8(r14), r13
	jl r15, putstr
	subi r14,r14,-44
	lw r15,-40(r14)
	jr r15
% Program start
	entry
	addi r14,r0,topaddr
	sub r0,r0,r0
	subi r14,r14,4
MAIN
	jl r15,main
	hlt
	% buffer for output
buf	res 20
