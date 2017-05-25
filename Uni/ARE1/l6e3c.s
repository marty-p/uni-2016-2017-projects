! 3) Scrivere un programma in linguaggio assemblativo 8088 che mette nel in
! una variabile cresc 1 se gli elementi sono ordinati in modo strettamente
! crescente, 0 altrimenti

! pseudo-code:
! cx=#vec
! bx=vec
! si=0
! al=ah=0
! while (--cx)
!	al=bx[si]
!	si++
!	ah=bx[si]
!	if al>=ah then
!		cresc=0
!		break
!	end


_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
MOV CX, endvec-vec	! cx = #vec
DEC CX				! cx--
MOV BX, vec			! bx = &vec
MOV SI, 0			! si = 0 (first pos)
MOV AX, 0			! ax=al=ah = 0

ciclo:
MOVB AL, (BX)(SI)	! ax += bx[si]
ADD SI, 1			! si++
MOVB AH, (BX)(SI)	! ax += bx[si]
CMPB AL,AH
JGE then
LOOP ciclo		! if (cx-- > 0) then goto ciclo
JMP exit		! goto exit

then:
MOV (cresc), 0

exit:
! print the res
PUSH (cresc) ! deve essere 2 byte
PUSH s
PUSH _PRINTF
SYS
! going to exit
PUSH 0
PUSH _EXIT
SYS


.SECT .DATA
s: .ASCII "%d\0"
cresc: .WORD 1	! cresc = 1 by default
vec: .BYTE 2,4,6,8,10,11
endvec: .BYTE 0


.SECT .BSS

