!2. Scrivere un programma in linguaggio assemblativo 8088 con il main e una
!funzione. La funzione deve verificare se una stringa e' palindroma. Il main
!deve scrivere sullo standard output se la stringa e' o non e' palindroma.


_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	! controlla vettori
	PUSH s			!arg2 &s
	PUSH s_end-s	!arg1 #s
	CALL pal		!pal(#s, &s)

	CMPB DL, 1
	JE si_pal
	JMP no_pal
	no_pal:
		PUSH pal_no
		PUSH _PRINTF
		SYS
		JMP exit
	si_pal:
		PUSH pal_yes
		PUSH _PRINTF
		SYS
		!JMP exit
	! going to exit
	exit:
		PUSH 0
		PUSH _EXIT
		SYS				!exit(0)

pal:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOVB DL, 1		!dl=1 (match flag, 1 y 0 n)
	MOV CX, 4(BP)	!1arg lunghezza
	MOV BX, 6(BP)	!2arg array1
	DEC CX			!decrement due to EOS
	MOV SI, 0		!si=0
	MOV DI, CX		!di=cx
	DEC DI			!decrement due to n-1
	!begin ottimizzare n/2 (fixa anche le lunghezze dispari)
	MOVB AL, CL		!al=cl
	MOVB DH, 2		!dh=2
	DIVB DH			!al/=dh
	MOVB CL, AL		!cl=al
	!end ottimizzare n/2
	ciclo:
		MOVB AL, (BX)(SI)	!al=*bx
		MOVB AH, (BX)(DI)	!ah=*di
		CMPB AL, AH		!if (al!=ah)
		JNE no			!then goto fine
		ADD SI, 1		!si++
		SUB DI, 1		!di--
		LOOP ciclo		!goto ciclo
		JMP fine
		no:
			MOVB DL, 0
			JMP fine
	!end
	fine:
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
	s: .ASCII "itropicimammamiciporti\0"
	s_end: .BYTE 0
	pal_yes: .ASCII "la stringa e' palindroma\0"
	pal_no: .ASCII "la stringa non e' palindroma\0"


.SECT .BSS

