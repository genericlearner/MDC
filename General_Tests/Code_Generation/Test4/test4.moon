f1
% Multiplication operation
	lw r12,0(r14)
	addi r11,r0,2
	mul r10,r12,r11
	sw -4(r14),r10
	lw r12,-4(r14)
	sw -8(r14),r12
	jr r15
main
% assignment operation
	sub r12,r12,r12
	addi r12,r12,5
	sw 0(r14),r12
% assignment operation
	sub r12,r12,r12
	addi r12,r12,2
	sw -4(r14),r12
% assignment operation
	sub r12,r12,r12
	addi r12,r12,1
	sw -8(r14),r12
% Function call tof1
	% Parameter 1
	lw r12,0(r14)
	sw -36(r14),r12
	% Save return address
	sw -32(r14),r15
	% Create new stack frame
	addi r14,r14,-36
	% Call function
	jl r15,f1
	% Restore original stack frame
	subi r14,r14,-36
	% Restore return address
	lw r15,-32(r14)
	% Handle return value
	lw r12,-44(r14)
	sw -16(r14),r12
% Multiplication operation
	lw r12,-8(r14)
	lw r11,-4(r14)
	mul r10,r12,r11
	sw -20(r14),r10
% add operation
	lw r12,-16(r14)
	lw r11,-20(r14)
	add r10,r12,r11
	sw -24(r14),r10
% Subtraction operation
	lw r12,-24(r14)
	addi r11,r0,5
	sub r10,r12,r11
	sw -28(r14),r10
% write Statement
	lw r12,-28(r14)
	sw -32(r14),r15
	addi r14,r14,-36
	sw -8(r14),r12
	addi r12,r0,buf
	sw -12(r14),r12
	jl r15,intstr
	sw -8(r14), r13
	jl r15, putstr
	subi r14,r14,-36
	lw r15,-32(r14)
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
