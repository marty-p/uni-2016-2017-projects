!Scrivere un programma in linguaggio assemblativo 8088 che verifica se due
!vettori di interi memorizzati in memoria principale sono identici.

! pseudo-code:
! a=10
! printf("%d", square(a))


_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	! controlla vettori
	PUSH vec1
	PUSH vec2
	PUSH vec2-vec1
	CALL compare

	! stampa res
	CMPB (flag), 0
	JNE diversi
	JMP uguali
	diversi:
		PUSH s2
		PUSH _PRINTF
		SYS
		JMP exit
	uguali:
		PUSH s1
		PUSH _PRINTF
		SYS

	! going to exit
	exit:
		PUSH 0
		PUSH _EXIT
		SYS

compare:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOV CX, 4(BP)	!1arg lunghezza
	MOV DI, 6(BP)	!2arg array1
	MOV SI, 8(BP)	!3arg array2
	MOV BX, 0
	ciclo:
		MOVB AL, (BX)(DI)
		MOVB AH, (BX)(SI)
		CMPB AL, AH
		JE continue
		MOVB (flag), 1
	continue:
		ADD BX, 1
		LOOP ciclo		!if (--cx) then goto ciclo
	!end
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
	s1: .ASCII "gli array sono uguali\0"
	s2: .ASCII "gli array sono diversi\0"
	!s: .ASCII "%d = %d \n \0"
	flag: .BYTE 0
	vec1: .BYTE 1,2,3,4
	vec2: .BYTE 1,2,3,5


.SECT .BSS

