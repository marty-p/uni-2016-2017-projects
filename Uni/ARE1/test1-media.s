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
	MOVB DH,2 !PARI VAR
	MOVB DL,0 !MEDIA VAR
	MOV BX,4(BP)
	MOV CX,6(BP)
	MOV SI,0
	ciclo1:
		!MOVB AL,SL!errore
		MOV AX,SI!fix
		DIVB DH
		CMPB AH,0 !RESTO DIVISIONE
		JE pari
		JMP continua
		pari:
			ADDB DL,(BX)(SI)
		continua:
			INC SI
			LOOP ciclo1
	MOV AX,0!fix
	MOVB AL,DL!fix
	DIVB DH!fix
	MOVB DL,AL!fix
	MOV SP,BP !NON NECESSARIO
	POP BP
	RET

.SECT .DATA
vec: .BYTE 1,2,3,4,5,6
end: .BYTE 0
s_y: .ASCII "MEDIA MAGGIORE DI 10 \0"
s_n: .ASCII "MEDIA NON MAGGIORE DI 10 \0"
s_f: .ASCII "%d \n\0"

.SECT .BSS
