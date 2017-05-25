!Scrivere un programma in linguaggio assemblativo 8088 che calcola il
!fattoriale di un numero n salvato in memoria. Il risultato deve essere
!stampato sullo standard output

! pseudo-code:
! a=10
! printf("%d", square(a))


_EXIT = 1
_PRINTF = 127


.SECT .TEXT
main:
! calcola fattoriale
PUSH (a)
CALL fact

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

fact:
PUSH BP !obbligatorio
MOV BP, SP !obbligatorio
!begin
MOV AX, 1		!ax=1
MOV CX, 4(BP)	!4 e' il primo arg (6 il secondo, ecc)
ciclo:
MUL CX			!ax*cx
LOOP ciclo		!if (--cx) then goto ciclo
!end
POP BP !obbligatorio
RET !obbligatorio


.SECT .DATA
s: .ASCII "fact di %d: %d\0"
a: .WORD 5


.SECT .BSS

