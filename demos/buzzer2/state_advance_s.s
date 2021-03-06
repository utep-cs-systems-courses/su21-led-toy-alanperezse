	.arch msp430g2553
	.p2align 1,0

	.data
	.extern super
	.extern size
	.extern sequence
	.extern play_silence
	.extern lengthen
	.extern play_note
	.global state_advance

jt:
	.word case0
	.word case1
	
	.text	

state_advance:
	sub #2, r1
	mov #0, 0(r1)		;move = 0

	mov &super, r12
	add r12, r12		;r12 = 2 * super

	cmp #2, sequence(r12)
	jge default		;if seq[super] >= 2

	mov sequence(r12), r12
	add r12, r12			;r12 = seq[super]
	mov jt(r12), r0		;use jump table
case0:
	call #play_silence
	mov r12, 0(r1)		;move = play_sil
	jmp esac
case1:
	call #lengthen
	mov r12, 0(r1)		;move = lengthen
	jmp esac
default:
	mov sequence(r12), r12
	call #play_note
	mov r12, 0(r1)		;move = play_note
	jmp esac
esac:
	cmp #0, 0(r1)
	jz out			;if move == 0
	add #1, &super		;else super += 1
	
	cmp &size, &super
	jl out			;if super < size
	mov #0, &super		;else reset
out:
	add #2, r1
	pop r0
