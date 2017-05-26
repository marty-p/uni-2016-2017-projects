!3. Scrivere un programma per il processore 8088 con il main e una funzione
!reverse. La funzione reverse deve invertire gli elementi di un vettore
!passato in input. Il main deve poi stampare il vettore.

_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	! controlla vettori
	MOV AX, 0
	PUSH vec
	PUSH end-vec
	CALL reverse			!reverse(#vec, &vec)

	! going to print
	MOV BX, vec
	MOV CX, end-vec
	MOV SI, 0
	ciclop:
		MOVB AL, (BX)(SI)
		PUSH AX
		PUSH s
		PUSH _PRINTF		!printf(s, AX)
		SYS
		INC SI
		LOOP ciclop

	! REVERSE AGAIN
	reverse_again:
		PUSH snl
		PUSH _PRINTF		!printf(snl)
		SYS

		MOV AX, 0
		PUSH vec
		PUSH end-vec
		CALL reverse			!reverse(#vec, &vec)

		! going to print
		MOV BX, vec
		MOV CX, end-vec
		MOV SI, 0
		ciclop2:
			MOVB AL, (BX)(SI)
			PUSH AX
			PUSH s
			PUSH _PRINTF		!printf(s, AX)
			SYS
			INC SI
			LOOP ciclop2

	! going to exit
	exit:
		PUSH 0
		PUSH _EXIT
		SYS				!exit(0)

reverse:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOV CX, 4(BP)	!1arg lunghezza
	MOV BX, 6(BP)	!2arg array1
	MOV SI, 0		!si inizia da [0]
	MOV AX, 0
	ciclo1:
		MOVB AL, (BX)(SI)	!al=bx[si]
		PUSH AX				!stack++=ax
		INC SI
		LOOP ciclo1
	MOV CX, 4(BP)	!1arg lunghezza
	MOV SI, 0		!si inizia da [0]
	ciclo2:
		POP AX				!ax=stack--
		MOVB (BX)(SI), AL	!bx[si]=al
		INC SI
		LOOP ciclo2
	!end
	MOV SP, BP !quasi obbligatorio
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
vec: .BYTE 1,3,5,7
end: .BYTE 0
s: .ASCII "%d \0"
snl: .ASCII "\n\0"


.SECT .BSS

