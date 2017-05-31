_EXIT=1
_PRINTF =127

.SECT .TEXT
main:
	PUSH end-vec
	PUSH vec
	CALL media

	MOVB DH,0
	PUSH DX
	PUSH s_f
	PUSH _PRINTF
	SYS

	CMP DX,10
	JG maggiore1

	PUSH s_n
	PUSH _PRINTF
	SYS
	JMP esci

	maggiore1:
		PUSH s_y
		PUSH _PRINTF
		SYS

	esci:
		PUSH 0
		PUSH _EXIT
		SYS

media:
	PUSH BP
	MOV BP,SP
	MOVB DL,0 !MEDIA VAR
	MOVB DH,0 !MEDIA CNT
	MOV BX,4(BP) !ARRAY
	MOV CX,6(BP) !#ARRAY
	MOV SI,0
	ciclo1:
		ADDB DL,(BX)(SI)	!dl+=bx[si]
		INCB DH				!dh++
		ADD SI, 2			!si+=2
		SUB CX, 2			!cx-=2
		CMP CX, 0
		JG ciclo1
	MOV AX,0		!ax=0
	MOVB AL,DL		!al=dl
	DIVB DH			!al/=dh
	MOVB DL,AL		!dl=al
	MOV SP,BP !NON NECESSARIO
	POP BP
	RET

.SECT .DATA
vec: .BYTE 6,0,6,0,6
end: .BYTE 0
s_y: .ASCII "MEDIA MAGGIORE DI 10 \0"
s_n: .ASCII "MEDIA NON MAGGIORE DI 10 \0"
s_f: .ASCII "%d \n\0"

.SECT .BSS
