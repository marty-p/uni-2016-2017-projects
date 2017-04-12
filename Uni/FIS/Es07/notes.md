#Set Esercizi 6 - Quiz

_Scadenza 27 marzo 2017, 23:59. Le risposte numeriche approssimate entro il 5% sono considerate corrette._

_La precisione nei risultati è indicata con la virgola mobile (,) invece che col punto (.)._

_abs(num) e pow(num, esp) sono funzioni della console di python relativamente per trovare l'assoluto e la potenza di un numero._


##Domanda 1
Un bimbo di massa m=32kg scende nello scivolo in figura con dislivello totale h=8m.
A che velocità v (in m/s) arriva sull’acqua se parte da fermo e l’attrito è trascurabile?

###Soluzione 1

```
import math
g=9.81
h=8
v=math.sqrt(2*h*g)
```


##Domanda 2
Una pistola a molla spara verso l’alto una freccetta ,che raggiunge un’altezza di 24 m rispetto al punto da cui è stata sparata.
In un secondo sparo, la molla è compressa solo per metà della lunghezza.
Che altezza raggiungerà la freccia in questo caso:
Scegli un'alternativa:

a. impossibile da determinare
b. 12 m
c. 3 m
d. 96 m
e. 24 m
f. 6 m
g. 48 m

###Soluzione 2

```
h1=24
h=0.25*h1
```


##Domanda 3
Il carrello di massa 103 kg di un ottovolante, privo di attrito, arriva in cima alla prima gobba della figura ad altezza h=12 m con velocità v0=18 m/s.
Quanto lavoro svolge la forza di gravità da qui al punto C? (Esprimere il risultato in J)

###Soluzione 3
```
m=103
g=9.81
h=12
L=m*g*h
```


##Domanda 4
Uno sciatore di massa m=70 kg parte da fermo da un’altezza H=16 m rispetto al culmine del trampolino.
Allo stacco dal trampolino, la direzione della sua velocità forma un angolo di 30° con il piano orizzontale.
Si trascuri l’attrito degli sci e la resistenza dell’aria.
Quanto vale l’altezza massima h (in m) raggiunta nel salto rispetto al punto di stacco?

###Soluzione 4

```
import math
sin30=math.sin(math.radians(30))
H=16
h=H*pow(sin30, 2)
```


##Domanda 5
Un blocco di massa m= 0.250 Kg viene lasciato cadere, da un'altezza h, su una molla di costante elastica k = 200 N/m, la quale si comprime di 15  cm.
Dopo la compressione, la molla spinge il blocco verso l'alto e perde il contatto con esso.
Quanto sarà l'altezza massima raggiunta dal blocco dopo la spinta (in metri)?

###Soluzione 5
???

```
m=0.250
k=200
l=0.015
g=9.81
hmax=(m*pow(l,2))/(2*m*g)
```
