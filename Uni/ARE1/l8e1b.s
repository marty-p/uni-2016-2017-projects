!Scrivere un programma in linguaggio assemblativo 8088 che utilizza una
!funzione per azzerare tutti gli elementi negativi di un vettore contenuto in
!memoria. Il vettore al termine dovra' essere stampato sullo standard
!output dal main.

! pseudo-code:
! a=10
! printf("%d", square(a))


_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	! controlla vettori
	PUSH vec		!arg2 &vec
	PUSH endvec-vec	!arg1 #vec
	CALL reset		!reset(#vec, &rec)

	MOV BX, vec
	MOV CX, endvec-vec
	MOV AX, 0
	stampa:
		MOVB AL, (BX)	!al=*bx
		INC BX			!bx++
		PUSH AX
		PUSH s
		PUSH _PRINTF
		SYS				!printf(s, ax)
		LOOP stampa

	! going to exit
	exit:
		PUSH 0
		PUSH _EXIT
		SYS				!exit(0)

reset:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOV CX, 4(BP)	!1arg lunghezza
	MOV BX, 6(BP)	!2arg array1
	ciclo:
		MOVB AL, (BX)		!al=*bx
		CMPB AL, 0			!if al<0
		JL azzera			!then goto azzera
		JMP continua		!goto continua
		azzera:
			MOVB (BX), 0	!*bx=0
		continua:
			INC BX			!bx++
			LOOP ciclo		!if (--cx) then goto ciclo
	!end
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
	s: .ASCII "%d \0"
	vec: .BYTE 1,2,-3,4,-5,6
	endvec: .BYTE 0


.SECT .BSS

