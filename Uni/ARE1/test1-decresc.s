!2. Scrivere un programma per il processore Intel 8088 formato dal main e da una funzione decresc che riceve
!come parametri l'indirizzo di un vettore e la sua dimensione. La funzione decresc restituisce 1 se gli
!elementi del vettore sono ordinati in modo decrescente, 0 altrimenti. Se il vettore contiene due valori
!consecutivi uguali allora il vettore non e' ordinato in ordine decrescente. Il main in base al risultato della
!funzione dovra' scrivere sullo standard output "gli elementi sono ordinati in ordine decrescente" / "gli
!elementi non sono ordinati in ordine decrescente".

_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
	!decresc(vec, n)
	PUSH end-vec
	PUSH vec
	CALL decresc

	!check result
	CMPB DH, 1
	JNE n_dec
	!y_dec
		PUSH s_yes
		PUSH _PRINTF
		SYS
		JMP endcheck
	n_dec:
		PUSH s_no
		PUSH _PRINTF
		SYS
		!endcheck
	endcheck:
	!print the array
	MOV BX, vec
	MOV CX, end-vec
	MOV SI, 0
	MOV AX, 0
	stampa:
		MOVB AL, (BX)(SI)
		INC SI
		!printf(s_prf, ax)
		PUSH AX
		PUSH s_prf
		PUSH _PRINTF
		SYS
		LOOP stampa
	!exit(0)
	PUSH 0
	PUSH _EXIT
	SYS

decresc:
	PUSH BP
	MOV BP,SP
	!code
	MOV BX, 4(BP)
	MOV CX, 6(BP)
	DEC CX
	MOV AX, 0
	MOVB DH, 1	!1 y, 0 n
	MOV SI, 0
	ciclo:
		MOVB AL, (BX)(SI)	!al=bx[si]
		INC SI				!si++
		MOVB AH, (BX)(SI)	!ah=bx[si]
		CMPB AL, AH			!if (al<=ah)
		JLE no				!then goto no
		!continue
		LOOP ciclo
		JMP fine
	no:
		MOVB DH, 0
		!fine
	!endcode
	fine:
	MOV SP,BP
	POP BP
	RET


.SECT .DATA
vec: .BYTE 9,8,7,6,5,4,3,2,1
end: .BYTE 0
s_prf: .ASCII "%d \0"
s_yes: .ASCII "gli elementi sono ordinati in ordine decrescente\n\0"
s_no: .ASCII "gli elementi non sono ordinati in ordine decrescente\n\0"


.SECT .BSS
