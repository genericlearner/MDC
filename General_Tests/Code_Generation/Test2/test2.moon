f2
% write Statement
	addi r12,r0,37
	sw 0(r14),r15
	addi r14,r14,-4
	sw -8(r14),r12
	addi r12,r0,buf
	sw -12(r14),r12
	jl r15,intstr
	sw -8(r14), r13
	jl r15, putstr
	subi r14,r14,-4
	lw r15,0(r14)
	jr r15
f1
% write Statement
	addi r12,r0,13
	sw 0(r14),r15
	addi r14,r14,-4
	sw -8(r14),r12
	addi r12,r0,buf
	sw -12(r14),r12
	jl r15,intstr
	sw -8(r14), r13
	jl r15, putstr
	subi r14,r14,-4
	lw r15,0(r14)
% Function call tof2
	% Save return address
	sw 0(r14),r15
	% Create new stack frame
	addi r14,r14,-4
	% Call function
	jl r15,f2
	% Restore original stack frame
	subi r14,r14,-4
	% Restore return address
	lw r15,0(r14)
	jr r15
countDown
% write Statement
	lw r12,0(r14)
	sw -12(r14),r15
	addi r14,r14,-16
	sw -8(r14),r12
	addi r12,r0,buf
	sw -12(r14),r12
	jl r15,intstr
	sw -8(r14), r13
	jl r15, putstr
	subi r14,r14,-16
	lw r15,-12(r14)
% Greater than operation compare
	lw r12,0(r14)
	addi r11,r0,0
	cgt r10,r12,r11
	sw -4(r14),r10
	lw r12,-4(r14)
%ifelse statment
	bz r12,else0
% Subtraction operation
	lw r11,0(r14)
	addi r10,r0,1
	sub r9,r11,r10
	sw -8(r14),r9
% Function call tocountDown
	% Parameter 1
	lw r11,-8(r14)
	sw -16(r14),r11
	% Save return address
	sw -12(r14),r15
	% Create new stack frame
	addi r14,r14,-16
	% Call function
	jl r15,countDown
	% Restore original stack frame
	subi r14,r14,-16
	% Restore return address
	lw r15,-12(r14)
	j endif0
else0	nop
endif0	nop
	jr r15
main
% read
	addi r12,r0,buf
	sw -8(r14),r12
	sw -24(r14),r15
	addi r11,r0,10
	putc r11
	addi r11,r0,63
	putc r11
	addi r11,r0,58
	putc r11
	jl r15,getstr
	lw r15,-24(r14)
	sw -24(r14),r15
	jl r15,strint
	lw r15,-24(r14)
	sw 0(r14),r13
% equal operation compare
	lw r12,0(r14)
	addi r11,r0,0
	ceq r10,r12,r11
	sw -8(r14),r10
	lw r12,-8(r14)
%ifelse statment
	bz r12,else1
% Function call tocountDown
	% Parameter 1
	addi r11,r0,5
	sw -28(r14),r11
	% Save return address
	sw -24(r14),r15
	% Create new stack frame
	addi r14,r14,-28
	% Call function
	jl r15,countDown
	% Restore original stack frame
	subi r14,r14,-28
	% Restore return address
	lw r15,-24(r14)
	j endif1
else1	nop
% equal operation compare
	lw r11,0(r14)
	addi r10,r0,1
	ceq r9,r11,r10
	sw -12(r14),r9
	lw r11,-12(r14)
%ifelse statment
	bz r11,else2
% Function call tof1
	% Save return address
	sw -24(r14),r15
	% Create new stack frame
	addi r14,r14,-28
	% Call function
	jl r15,f1
	% Restore original stack frame
	subi r14,r14,-28
	% Restore return address
	lw r15,-24(r14)
	j endif2
else2	nop
% Function call tof2
	% Save return address
	sw -24(r14),r15
	% Create new stack frame
	addi r14,r14,-28
	% Call function
	jl r15,f2
	% Restore original stack frame
	subi r14,r14,-28
	% Restore return address
	lw r15,-24(r14)
endif2	nop
endif1	nop
% assignment operation
	sub r12,r12,r12
	addi r12,r12,0
	sw -4(r14),r12
% while loop
gowhile0	nop
% Less than or equal to operation compare
	lw r12,-4(r14)
	addi r11,r0,5
	cle r10,r12,r11
	sw -16(r14),r10
	lw r12,-16(r14)
	bz r12,endwhile0
% write Statement
	lw r11,-4(r14)
	sw -24(r14),r15
	addi r14,r14,-28
	sw -8(r14),r11
	addi r11,r0,buf
	sw -12(r14),r11
	jl r15,intstr
	sw -8(r14), r13
	jl r15, putstr
	subi r14,r14,-28
	lw r15,-24(r14)
% add operation
	lw r11,-4(r14)
	addi r10,r0,1
	add r9,r11,r10
	sw -20(r14),r9
% assignment operation
	lw r11,-20(r14)
	sw -4(r14),r11
	j gowhile0
endwhile0	nop
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
