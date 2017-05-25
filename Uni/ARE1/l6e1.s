! Scrivere un programma per 8088 che presi i dati a = 5, b = 7, c = 10 in
! memoria calcola l'espressione (a + 3) * b / c e salva il risultato in una
! variabile d
! res: d=5

_EXIT = 1
_PRINTF = 1

.SECT .TEXT
main:
MOV AX, 0		! ax(al/ah) = 0
MOVB AL, (a)	! al  = *a
ADDB AL, 3		! al += 3
MULB (b)		! al *= *b
DIVB (c)		! al /= *c
MOVB (d), AL	! *d = al
PUSH 0			! going to exit
PUSH _EXIT
SYS

.SECT .DATA
a: .BYTE 5		! a = 5
b: .BYTE 7		! b = 7
c: .BYTE 10		! c = 10

.SECT .BSS
d: .SPACE 1		! d
