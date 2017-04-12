#Set Esercizi 4 - Quiz

_Scadenza 27 marzo 2017, 23:59. Le risposte numeriche approssimate entro il 5% sono considerate corrette._

_La precisione nei risultati è indicata con la virgola mobile (,) invece che col punto (.)._

_abs(num) e pow(num, esp) sono funzioni della console di python relativamente per trovare l'assoluto e la potenza di un numero._


##Domanda 1
NON CONSIDERATO NEL PUNTEGGIO FINALE.
Si consideri un sistema di due blocchi connessi con una fune attraverso una carrucola.
Il blocco A può scorrere su un piano inclinato di un angolo 30°, massa del blocco a è 18,9 Kg; il coefficiente di attrito dinamico tra il blocco e il piano è 0,2.
Il blocco B invece è appeso e può muoversi verticalmente.
Se il blocco A scende sul piano con velocità costante, quanto sarà la massa del blocco B (espressa in Kg)?
###Soluzione 1


##Domanda 2
Qual è la massima accelerazione possibile di un corridore se il coefficiente di attrito statico tra le sue scarpe e il suolo è di 0,85?

###Soluzione 2

```
import math
cad=0.85
sen30=math.cos(math.radians(30))
cos30=math.cos(math.radians(30))
mA=1
mB=mA*(sen30-cad*cos30)
```

mB=mA*(sen30°-coeff.attr.din*cos30°)

##Domanda 3
Il coefficiente di attrito statico tra il teflon e le uova strappazzate è di 0.04.
Qual è il più piccolo angolo, rispetto all'orizzontale, che fa uscire le uova da una padella con il fondo in teflon?
Scegli una o più alternative:

a. 3.2°
b. 4.0°
c. 2.3°
d. 0.2°

###Soluzione 3
2.3°


##Domanda 4
Un blocco di massa 23,0 Kg è inizialmente fermo su un piano orizzontale.
Se viene applicata una forza di intensità F =470,8 N che forma un angolo di 45° con l'orizzontale, qual è l'intensità dell'accelerazione del blocco se il coefficiente di attrito dinamico è 0,3?
(Si suppone che la forza di attrito statico sia piu' piccola della forza che mette in moto il blocco)

###Soluzione 4

```
import math
m=23.0
F=470.8
cad=0.3
cos45=math.cos(math.radians(45))
mg=1
T=(F*cos45-cad*mg)/m
```

x=(F*cos45°-coeff.attr.din.*mg)/m


##Domanda 5
Un aereo vola lungo una circonferenza orizzontale alla velocità di 137,8 m/s.
Le ali dell'aereo sono inclinate di 45°.
Si determini il raggio della circonferenza percorsa dall'aereo espressa in metri.
Si supponga che la forza centripeta sia dovuta esclusivamente alla forza esercitata perpendicolarmente alla superficie dell'aereo.

###Soluzione 5
1935,66

```
import math
v=139.1
tan45=math.tan(math.radians(45))
g=9.81
a=(v**2)/(g*tan45)
```


##Domanda 6
Una ruota panoramica di un parco i divertimenti ha un diametro di 17,7 m e compie 2,2 giri al minuto attorno al suo asse orizzontale.
Quanto vale la forza agente sul passeggero di massa 57,7 Kg seduto nel punto più alto della ruota?

###Soluzione 6

```
import math
d=17.7
m=57.7
v=2.2
pi2=3.14*2
F=(v*pi2/60)**2
```
F=m*(g-(v*pi2/60)*d/2)


##Domanda 7
Una ruota panoramica di un parco i divertimenti ha un diametro di 16,5 m e compie 2 giri al minuto attorno al suo asse orizzontale.
Quanto vale la forza agente sul passeggero di massa 52,6 Kg seduto nel punto più basso della ruota?

###Soluzione 7

```
import math
d=16.9
m=68.6
t=3/60.
pi2=3.14*2
w=pi2/t
F=(w*pi2/60)**2
```
