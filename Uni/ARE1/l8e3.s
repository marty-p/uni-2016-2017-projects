!3. Dati due vettori di interi mettere su un terzo la somma degli elementi
!corrispondenti dei primi due. I vettori hanno tutti la stessa lunghezza.
!Usare una funzione per fare la somma dei vettori e il main per stampare a
!video il terzo dopo l'elaborazione.


_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	! controlla vettori
	PUSH v1				!arg4
	PUSH v2				!arg3
	PUSH v3				!arg2
	PUSH v2-v1			!arg1
	CALL sum_vec		!sum_vec(#v1, &v1, &v2, &v3)

	MOV AX, 0			!ax=ah=al=0
	MOV CX, v2-v1		!cx=#v3
	MOV BX, v3			!bx=&v3
	stampa:
		MOVB AL, (BX)
		PUSH AX
		PUSH s
		PUSH _PRINTF
		SYS				!printf(s, AL)
		INC BX			!bx++
		LOOP stampa		!if (--cx) then goto stampa
	! going to exit
	exit:
		PUSH 0
		PUSH _EXIT
		SYS				!exit(0)

sum_vec:
	PUSH BP !obbligatorio
	MOV BP, SP !obbligatorio
	!begin
	MOV CX, 4(BP)	!1arg lunghezza
	MOV SI, 6(BP)	!2arg array3
	MOV DI, 8(BP)	!3arg array2
	MOV BX, 10(BP)	!4arg array1
	ciclo:
		MOVB AL, (BX)	!al=*bx
		MOVB AH, (DI)	!ah=*di
		ADDB AL, AH		!al+=ah
		MOVB (SI), AL	!*si=al
		INC BX			!bx++
		INC DI			!di++
		INC SI			!si++
		LOOP ciclo		!if (--cx) then goto ciclo
	!end
	POP BP !obbligatorio
	RET !obbligatorio


.SECT .DATA
v1: .BYTE 1,2,3,4
v2: .BYTE 5,6,7,8
s: .ASCII "%d \0"


.SECT .BSS
v3: .SPACE 4

