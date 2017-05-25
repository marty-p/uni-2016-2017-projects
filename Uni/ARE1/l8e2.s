!2. Scrivere un programma in linguaggio assemblativo 8088 con il main e una
!funzione. La funzione deve verificare se una stringa e' palindroma. Il main
!deve scrivere sullo standard output se la stringa e' o non e' palindroma.

! pseudo-code:
! a=10
! printf("%d", square(a))


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
	MOVB DL, 1		!dl=1 (match flag)
	MOV DI, 4(BP)	!1arg lunghezza
	MOV BX, 6(BP)	!2arg array1
	SUB DI, 2		!?
	ciclo:
		CMP BX, DI		!if (bx>=di)
		JGE fine		!then goto fine
		MOVB AL, (BX)	!al=*bx
		MOVB AH, (DI)	!ah=*di
		ADD BX, 1		!bx++
		SUB DI, 1		!di--
		CMPB AL, AH		!if (al!=ah)
		JNE no			!then goto no
		JMP ciclo		!goto ciclo
		no:
			MOVB DL, 0
			JMP ciclo
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

