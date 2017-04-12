#Set Esercizi 6 - Quiz

_Scadenza 03 aprile 2017, 12:00. Le risposte numeriche approssimate entro il 5% sono considerate corrette._

_La precisione nei risultati è indicata con la virgola mobile (,) invece che col punto (.)._

_abs(num) e pow(num, esp) sono funzioni della console di python relativamente per trovare l'assoluto e la potenza di un numero._


##Domanda 1
Una pallina di massa m appesa ad un filo di massa trascurabile oscilla come un pendolo con periodo T=1,3 s.
Quanto vale la lunghezza del filo in m?

###Soluzione 1
0,42

```
import math
g=9.81
pi2=3.14*2
T=1.3
v=g*pow(T/pi2, 2)
```


##Domanda 2
Un bambino si dondola sull’altalena, oscillando alla frequenza propria del sistema.
Se un secondo bambino si aggiunge e l’altalena oscilla con i bambini seduti assieme, rispetto alla frequenza iniziale, la nuova frequenza propria di oscillazione sarà:

Scegli un'alternativa:

1. minore
2. uguale
3. maggiore

###Soluzione 2
uguale


##Domanda 3
Il periodo con cui un pendolo oscilla all'equatore ($g_{eq}$=9,78 $m/s^2$) è T= 5,0 s, quale sarà il periodo se lo trasportiamo al polo sud ($g_{sud}$=9,83 $m/s^2$) ?


###Soluzione 3
4,98

```
import math
geq=9.78
gsud=9.83
T=5.0
T1=T*math.sqrt(geq/gsud)
```


##Domanda 4
Una grande fionda viene allungata di x = 4,7 m in modo da lanciare un proiettile di m = 274 g a una velocità sufficiente per sfuggire alla Terra (vfuga = 11,2 Km/s).
Qual è la costante elastica della fionda se tutta l'energia potenziale viene convertita in energia cinetica? Si esprima il risultato in MN/m, dove M=mega=$10^6$

###Soluzione 4

```
x=3.2
m=285
vfuga=11.2
k=(m*pow(vfuga, 2))/pow(x, 2)
```
```
x=3.2
m=285
v=11.2
k = (m*(v**2))/(x**2)
1.5*m*(v**2) = 1.5*k*(x**2)
```


##Domanda 5
Un blocco è posto su un pistone che si sta muovendo verticalmente con moto armonico semplice di periodo 8,9 s.
Quale deve essere l’ampiezza del moto, in cm, perchè il pistone e il blocco non stiano uniti? 

###Soluzione 5
???

```
import math
g=9.81
pi=3.14
A=2
T=(1/(pi*2))*math.sqrt(g/A)
```


##Domanda 6
Un blocco è posto su un pistone che si sta muovendo verticalmente con moto armonico semplice di ampiezza 2 cm.
Qual è la frequenza massima dell'oscillazione per cui il blocco e il pistone rimarranno in contatto continuamente?

###Soluzione 6
???

```
g=9.81
pi=3.14
T=8.9
A=(g*pow(T, 2))/2*pow(pi, 2)
```
