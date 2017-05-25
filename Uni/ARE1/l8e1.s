!1. Scrivere un programma in linguaggio assemblativo 8088 che utilizza una
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
	PUSH vec
	PUSH endvec-vec
	CALL reset

	MOV BX, vec
	MOV CX, endvec-vec
	MOV AX, 0
	stampa:
		MOVB AL, (BX)
		INC BX
		PUSH AX
		PUSH s
		PUSH _PRINTF
		SYS
		LOOP stampa

	! going to exit
	exit:
		PUSH 0
		PUSH _EXIT
		SYS

reset:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOV CX, 4(BP)	!1arg lunghezza
	MOV DI, 6(BP)	!2arg array1
	MOV BX, 0
	ciclo:
		MOVB (BX)(DI), 0
		ADD BX, 1
		LOOP ciclo		!if (--cx) then goto ciclo
	!end
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
	s: .ASCII "%d \0"
	vec: .BYTE 1,2,3,4
	endvec: .BYTE 0


.SECT .BSS

