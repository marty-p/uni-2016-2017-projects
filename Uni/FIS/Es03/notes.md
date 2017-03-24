#Set Esercizi 3 - Quiz

_Scadenza 24 marzo 2017, 12:00. Le risposte numeriche approssimate entro il 5% sono considerate corrette._

_La precisione nei risultati è indicata con la virgola mobile (,) invece che col punto (.)._

_abs(num) e pow(num, esp) sono funzioni della console di python relativamente per trovare l'assoluto e la potenza di un numero._


##Domanda 1
Un punto materiale si muove di moto circolare uniforme. Per compiere un giro completo impiega $t$ secondi. Qual è la sua velocità angolare?

###Soluzione 1
17,4 rad/s (t cambia ogni volta)

```
t=0.33
pi=3.14
w=(pi*2)/t
```

$$\frac{2\pi}{t}$$


##Domanda 2
Dall'estremità sinistra di un edificio alto h si lancia verso sinistra una palla che cade a terra dopo 1.50 s alla distanza d=25m dalla base del palazzo,
arrivandovi con direzione che forma un angolo di 60° rispetto al piano orizzontale.
Quanto vale h?
Scegli un'alternativa:

a. h=64.6 m
b. h=24.7 cm
c. h=11.03 m
d. h=32.3 m

###Soluzione 2
32.3 m


##Domanda 3
Una freccetta è tirata orizzontalmente in direzione del centro del bersaglio P con velocità iniziale 30 m/s.
Dopo un tempo  di 5,0 s essa colpisce il punto Q sul bordo del bersaglio, posto verticalmente sotto il punto P.
Qual è la distanza PQ espressa in m?

###Soluzione 3
41,209 (t cambia ogni volta)

```
v0=30
q=90
t=2.9
g=9.8
h=0.5*g*pow(t, 2)
```

$$h=\frac12g \times t^2$$


##Domanda 4
Un treno affrontando una curva rallenta passando da 92,1 Km/h a 47,9 Km/h nei 6,5s impiegati a completare la curva.
Il raggio della curva è 150 m.
Calcolare l'accelerazione trasversale, espressa in $m/s^2$, nel momento in cui v=47,9 Km/h, assumendo che in questo momento continui a decelerare.

###Soluzione 4
-0,92 (v1 v2 t cambiano ogni volta)

```
v1=84.1
v2=47.5
t=7.8
v1=v1/3600*1000
v2=v2/3600*1000
at=(v2-v1)/t
```

$$at = \frac{\Delta v}{t}$$


##Domanda 5
Una palla viene lanciata contro un muro con velocità iniziale 6,3 m/s con un angolo di 45° rispetto all'orizzontale.
Il muro si trova alla distanza 5,1 m dal punto di lancio.
Per quanto tempo la palla rimane in aria prima di colpire la parete?

###Soluzione 5
1,1448395504925055

```
import math
v=6.3
d=5.1
c=math.cos(math.radians(45))
t=d/(v*c)
```

$$t = \frac{d}{v_0 \times cos(45)}$$


##Domanda 6
Si consideri un sasso lanciato in una certa direzione, sia vy = 6,4 m/s la componente verticale e vx = 5,0 m/s
la componente orizzontale della velocità.
Quanto vale la gittata del lancio (espressa in metri)?

###Soluzione 6
(vy e vx cambiano)

```
vx=7.5
vy=4.9
g=9.8
L=(vx*vy)/g*2
```

$$L = 2\frac{v_x*v_y}{g}$$


##Domanda 7
Un treno affrontando una curva rallenta passando da 90 Km/h a 47,9 Km/h nei 15 s impiegati a completare la curva.
Il raggio della curva è 166,4 m. Calcolare l'accelerazione centripeta, espressa in $m/s^2$, nel momento in cui v=47,9 Km/h, assumendo che in questo momento continui a decelerare.

###Soluzione 7
1,9554689991344358 (v2 e r variano)

```
v1=90
v2=47.5
t=15
r=154.1
v1=v1/3600*1000
v2=v2/3600*1000
ac=pow(v2-v1, 2)/r
```

$$ac = \frac{\Delta v ^2}{r}$$


##Domanda 8
La figura mostra una nave di pirati ormeggiata a 569,2 m di distanza dal porto.
Un cannone, posto a protezione del porto, puo' sparare la palla per colpire la nave con un angolo di 27° (63°).
Qual è la velocità, in m/ s, con cui la palla viene sparata dal cannone?

###Soluzione 8
83.03604608463861

```
import math
R=569.2
theta0=27
g=9.8
v0=math.sqrt(R*g/(math.sin(math.radians(theta0*2))))
```

$$\sqrt{\frac{Rg}{sin(2\theta _0)}}$$
























