!1. Scrivere un programma in linguaggio assemblativo 8088 con il main e una
!funzione diff. La funzione deve restituire la differenza fra gli elementi in
!posizione pari con quelli in posizione dispari di un vettore passato in input.
!Il main scrive il risultato sullo standard output usando una stringa del tipo
!"la differenza e' x". Il vettore ha dimensione pari.

_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	! controlla vettori
	MOV AX, 0
	PUSH vec
	PUSH end-vec
	CALL diff			!diff(#vec, &vec)

	! going to print
	PUSH AX
	PUSH s
	PUSH _PRINTF		!printf(s, AX)
	SYS

	! going to exit
	exit:
		PUSH 0
		PUSH _EXIT
		SYS				!exit(0)

diff:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOV CX, 4(BP)	!1arg lunghezza
	MOV BX, 6(BP)	!2arg array1
	MOV DI, 0		!counter pari
	MOV SI, 1		!counter dispari
	ciclo:
		ADDB AL, (BX)(DI)	!al+=bx[0]
		ADDB AH, (BX)(SI)	!ah+=bx[1]
		ADD DI, 2			!di+=2
		ADD SI, 2			!si+=2
		DEC CX				!--cx (double dec for this func)
		LOOP ciclo			!if (--cx) then goto ciclo
	SUBB AL, AH				!al-=ah
	MOVB AH, 0				!ah=0
	!end
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
vec: .BYTE 30,3,10,7,1,10,8,1
end: .BYTE 0
s: .ASCII "la differenza e' %d \0"


.SECT .BSS
v3: .SPACE 4

