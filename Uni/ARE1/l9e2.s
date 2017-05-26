!Scrivere un programma in linguaggio assemblativo 8088 con il main e una
!funzione min_max. La funzione deve calcolare la differenza fra il valore
!massimo e il valore minimo di un vettore in input. Il main scrive il risultato
!sullo standard output usando una stringa del tipo "la differenza fra
!massimo e minimo e' x".

_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	! controlla vettori
	MOV AX, 0
	PUSH vec
	PUSH end-vec
	CALL diff_minmax			!diff_minmax(#vec, &vec)

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

diff_minmax:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOV CX, 4(BP)	!1arg lunghezza
	MOV BX, 6(BP)	!2arg array1
	MOV SI, 1		!si inizia da [1]
	MOVB AH, (BX)	!ah=bx[0] (min)
	MOVB AL, (BX)	!al=bx[0] (max)
	DEC CX			!--cx (for i=1)
	ciclo:
		MOVB DL, (BX)(SI)	!dl=bx[si]
		CMPB DL, AH
		JL new_min
		CMPB DL, AL
		JG new_max
	continua:
		INC SI				!si++
		LOOP ciclo			!if (--cx) then goto ciclo
		JMP fine
	new_min:
		MOVB AH, (BX)(SI)
		JMP continua
	new_max:
		MOVB AL, (BX)(SI)
		JMP continua
	fine:
		SUBB AL, AH			!al=al-ah
		MOVB AH, 0			!ah=0
	!end
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
vec: .BYTE 4,3,5,7,1,10,8
end: .BYTE 0
s: .ASCII "la differenza fra massimo e minimo e' %d \0"


.SECT .BSS

