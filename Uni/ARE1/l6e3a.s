! Scrivere un programma in linguaggio assemblativo 8088 che, preso un
! intero n in memoria, calcola la somma dei primi n interi

_EXIT = 1
_PRINTF = 1


.SECT .TEXT
main:
MOV CX, (n)		! cx = *n
MOV AX, 0		! ax = 0

ciclo:
ADD AX, CX		! ax += cx
LOOP ciclo		! if (cx-- > 0) then goto ciclo
jmp exit		! goto exit

exit:
PUSH 0			! going to exit
PUSH _EXIT
SYS


.SECT .DATA
n: .WORD 6


.SECT .BSS
