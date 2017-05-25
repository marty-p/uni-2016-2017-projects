! Scrivere un programma per 8088 che trovi il massimo valore contenuto nel
! vettore: 2,5,1,7,3,10,12,4

_EXIT = 1
_PRINTF = 1


.SECT .TEXT
main:
MOV CX, 8		! cx = #vec (dimensione vec)
MOV BX, vec		! bx = &vec (address di vec)
MOV DX, (BX)	! dx = &vec[0] (usato come variabile per il "maggiore")
MOV SI, 2		! si = 2 (incrementa di 2 byte, ovvero 1 word)

check:
MOV AX, (BX)(SI)! ax = &vec[si/sizeof(WORD)]
CMP AX, DX		! if ax>dx
JG match		! then goto match
JMP continue	! else goto continue
match:
MOV DX, AX		! dx = ax (nuovo "maggiore")
continue:
ADD SI,2		! si += 2 (2 byte)
LOOP check		! if (--cx > 0) then goto check
jmp exit		! goto exit

exit:
PUSH 0			! going to exit
PUSH _EXIT
SYS


.SECT .DATA
vec: .WORD 2,5,1,7,3,10,12,4
vec_end: .WORD 0


.SECT .BSS
