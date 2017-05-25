! Scrivere un programma in linguaggio assemblativo 8088 che calcola la
! somma degli elementi di un vettore vec memorizzato in memoria
! principale.

_EXIT = 1
_PRINTF = 1


.SECT .TEXT
main:
MOV CX, endvec-vec	! cx = #vec
MOV BX, vec			! bx = &vec
MOV SI, 0			! si = 0 (first pos)
MOV AX, 0			! ax = 0 (entrambi al e ah a 0)

ciclo:
ADDB AL, (BX)(SI)	! ax += bx[si]
ADD SI, 1			! si++
LOOP ciclo		! if (cx-- > 0) then goto ciclo
jmp exit		! goto exit

exit:
PUSH 0			! going to exit
PUSH _EXIT
SYS


.SECT .DATA
vec: .BYTE 2,4,6,8,10,12		! res: 42 (0x2a)
endvec: .BYTE 0

.SECT .BSS
