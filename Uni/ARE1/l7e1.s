!Scrivere un programma in linguaggio assemblativo 8088 che, preso un
!numero a in memoria, calcola il quadrato del numero facendo uso di una
!subroutine "square" che ha come unico argomento il numero a. Il risultato
!deve essere stampato sullo standard output

! pseudo-code:
! a=10
! printf("%d", square(a))


_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
! calcola quadrato
PUSH (a)
CALL square

! print the res
PUSH AX ! ritorno di square
PUSH (a) ! deve essere 2 byte
PUSH s
PUSH _PRINTF
SYS

! going to exit
PUSH 0
PUSH _EXIT
SYS

square:
PUSH BP !obbligatorio
MOV BP, SP !obbligatorio
MOV AX, 4(BP) !4 e' il primo arg (6 il secondo, ecc)
MUL AX !ax*ax
POP BP !obbligatorio
RET !obbligatorio


.SECT .DATA
s: .ASCII "square di %d: %d\0"
a: .WORD 3


.SECT .BSS

