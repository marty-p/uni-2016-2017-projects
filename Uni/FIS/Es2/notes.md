#Set Esercizi 2 - Quiz

_Scadenza 17/3/2017, h23:59. Le risposte numeriche approssimate entro il 5% sono considerate corrette._

_La precisione nei risultati è indicata con la virgola mobile (,) invece che col punto (.)._

_abs(num) e pow(num, esp) sono funzioni della console di python relativamente per trovare l'assoluto e la potenza di un numero._

## Info 1
\begin{align}
\overline{v} & = \frac{\Delta x}{\Delta t} = \frac{x_1 - x_0}{t_1 - t_0}
\end{align}

\begin{align}
\overline{a} & = \frac{\text{distanza totale}}{\Delta t}
\end{align}

$\Delta$ (delta maiuscolo) rappresenta un cambio di quantità, esempio: $\Delta x$ significa la differenza fra x finale e x iniziale.

Uno spostamento è negativo quando $\Delta x$ è negativo e positivo se viceversa. Nullo se 0. L'assoluto di $\Delta x$ si chiama **magnitudo**.

$t_0$ equivale al tempo di inizio (solitamente 0s), $t_1$ il tempo totale (quanto è durato per muoversi da $x_0$ a $x_1$).

$x_0$ equivale al punto d'origine nell'asse cartesiano (0m se non specificato), $x_1$ indica la posizione finale.


##Domanda 1
Un'automobile sportiva raggiunge i 100 km/h  in 3,2 secondi. Qual'è la sua accelerazione media espressa in $m/s^2$?

###Soluzione 1
8,6875

Per ottenere la velocità in metri al secondo di 100 km/h, si fa:

$100/3600.*1000=27.777777777777775 \approx 27.8$

Per ottenere l'accelerazione si fa $\Delta v/ \Delta t$, quindi $27.8/3.2=8.6875$

$$a=(v_1-v_0)/(t_1-t_0)=(27.8-0)/(3.2-0)=8.6875$$


##Domanda 2
Una palla è lanciata verso l’alto e ricade sulla mano che l’ha lanciata dopo 9 s. Calcolare l’altezza massima raggiunta (in m).

###Soluzione 2
99,22500000000001

Per la simmetria del moto uniformemente accelerato il tempo impiegato dalla palla per raggiungere la massima altezza H è uguale
a quello necessario per ricadere dall'altezza H sulla mano.

Essendo dunque il tempo totale di 9s (salita + discesa), il tempo impiegato per la sola salita sarà $\frac12 t = 9/2 = 4.5 s$.

Scriviamo adesso le leggi orarie di questo moto:
$y = y_0 + v_0t - \frac12 gt^2$

$v = v_0 - gt$

Per calcolare la velocità iniziale $v_0$ usiamo la seconda equazione.

Nel momento in cui la palla raggiunge la massima altezza la velocità istantanea v è nulla pertanto la seconda equazione può essere scritta come:

$v = v_0 - gt$

$0 = v_0 - gt$

$v_0 = gt = 9.8*4.5=44.1 m/s$

Adesso che conosciamo la velocità iniziale $v_0$ possiamo calcolare l'altezza massima dalla prima equazione:

$y = y_0 + v_0t - \frac12 gt^2 = 0 + 44.1*4.5 - 0.5* (9.8*pow(4.5, 2)) = 99.22500000000001 \approx 99.2 m$


##Domanda 3
Un maratoneta corre alla velocità costante di 15 km/h.
Quando il maratoneta si trova a 7.5 Km dall’arrivo, un uccello inizia a volare alla velocita` costante di 30 km/h dal corridore verso l’arrivo.
Giunto all’arrivo, l’uccello torna indietro fino a raggiungere il corridore, poi torna nuovamente indietro e ripete i suoi viaggi avanti e indietro fino a che il maratoneta finisce la sua corsa.
Quanti km percorre l’uccello?

![pic](http://i.imgur.com/ORrzCo8.png "pic")

Scegli un'alternativa:
1. 30 Km
2. 20 Km
3. 10 Km
4. 15 Km

###Soluzione 3
15 Km (i radio button cambiano di posizione)

Indipendentemente da quante volte l'uccello torni avanti/indietro, il suo moto sarà sempre il doppio di quello del maratoneta.


##Domanda 4
Un aereo sta per compiere la manovra di atterraggio, se arriva al suolo con una velocità di 272 Km/h e si ferma dopo 20 s, quale sarà la sua accelerazione espressa in $m/s^2$?

###Soluzione 4
? m/s^2

Si calcola la velocità in m/s facendo

$v = 272km/h = 272/3600.*1000=75.55555555555556 \approx 75.6 m/s$

$a=(0 - 75.6) / (20. - 0)=-3.78$


##Domanda 5
Un aereo sta compiendo una manovra di atterraggio, se la sua velocità appena tocca terra è v= 306Km/h e si ferma dopo un tempo t=20s, quanto spazio percorrerà dopo aver toccato il suolo?

###Soluzione 5
850 m

$v= 306/3600.*1000=85 m/s$

$a=(0 - 85) / (20. - 0)=-4.25$

$s = 0.5*(at^2) + v_0t+s_0 = 0.5*(-4.25*pow(20, 2)) + 85*20 = 850 m$


##Domanda 6
Un treno sta partendo da una stazione con un'accelerazione di 33 mm/s2, quale sarà la sua velocità, espressa in m/s, dopo un intervallo di tempo t= 10 minuti?

###Soluzione 6
19,8

$t = 10 min = 10*60 = 600 s$

$a = 33 mm = 33/1000. = 0.033 m$

$v=v_0+at = 0+0.033*600=19.8$


##Domanda 7
Una treno sta partendo da una stazione, se la sua accelerazione è 33 $mm/s^2$, che distanza avrà percorso dopo un intervallo di tempo t= 10minuti?

###Soluzione 7
5940

$t = 10 min = 10*60 = 600 s$

$a = 33 mm = 33/1000. = 0.033 m$

$x - x_0 = v_0t + \frac12 (at^2)=0*600 + 0.5*(0.033*pow(600, 2))=5940$

