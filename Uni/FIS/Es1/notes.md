#Set Esercizi 1 - scadenza 9 marzo Quiz

_Scadenza 9/3/2017, h23:59. Le risposte numeriche approssimate entro il 5% sono considerate corrette._

_La precisione nei risultati è indicata con la virgola mobile (,) invece che col punto (.)._

_abs(num) e pow(num, esp) sono funzioni della console di python relativamente per trovare l'assoluto e la potenza di un numero._


##Suggerimento 1
Enrico Fermi osservò una volta che la durata normale di una lezione (50 minuti) è molto vicina a un microsecolo.


##Domanda 1
La pressione nelle unità SI si misura in $Pa=N/m^2$, dove N è l'unità della forza.
Nelle unità anglosassoni invece per la pressione si usa il PSI (Pound per square inch).
Sapendo che la forza peso di 1 pound equivale a circa 4.45 N e che $1in = 2.54 cm$, calcolare a quanti PSI corrisponde la pressione di $6*10^5Pa$.

###Soluzione 1
87 o 87,0226426 o 87,02264267811522 o (se si usano i pound per N arrotondati) 86,98786516853933

La formula del PSI:
$$1\,\text{PSI} = \frac{4.4482216152605\,\mathrm N}{(0.0254\,\mathrm m)^2} \approx 6894.75729\,\mathrm{Pa}$$

La formula del PSI arrotondando i pound per N per 3 cifre significative: (non la userò)
$$1\,\text{PSI} = \frac{4.45\,\mathrm N}{(0.0254\,\mathrm m)^2} \approx 6897.51379502759\,\mathrm{Pa}$$

In poche parole, per convertire 600000 Pa in PSI basta fare $1/6894.75729*600000=87.02264267811522$.

**Info sulle varie conversioni:**

* 1 pound = 4.4482216152605 N
* 1 N = 1/4.4482216152605 = 0.2248089430997105 pound (inutile per l'esercizio)
* 1 pound = 4.45 N (arrotondato)
* 1 N = 1/4.45 = 0.2247191011235955 pound (arrotondato) (inutile per l'esercizio)
* 1 in = 2.54 cm
* 1 cm = 1/2.54 = 0.39370078740157477 in (inutile per l'esercizio)

Il fattore di conversione si ottiene semplicemente facendo $N/m^2$, ma utilizzando la relativa conversione pound/inches:
$$4.4482216152605/pow(0.0254, 2)=6894.757293168361$$

_Nota: pow(0.0254, 2) ovvero $0.0254^2=0.00064516$_


##Domanda 2
Un corridore percorre un giro della pista di atletica (400 m di lunghezza) in 1 minuto e 5 secondi.
Calcolare la sua velocità media in Km/h.

###Soluzione 2
22 (2 cifre significative) o 22,14 (4 cifre significative) o 22,153846153846157 (17 cifre significative)

Per ottenere tale risultato basta:

1. Convertire 1m5s in secondi ($1*60+5=65$) e dividere 400m per il risultato ($400/65.=6.15$) per ottenere i m/s
2. Moltiplicare il risultato per il numero di secondi in un'ora ($60*60=3600$) così facendo si otterranno i m/h ($6.15*3600=22140$)
3. Dividere il risultato per il numero di km in un metro ($1km=1000m$) così facendo si otterranno i km/h ($22140/1000=22.14$)


##Domanda 3
Quanto dura un microsecolo in minuti?

###Soluzione 3
52,56

Un microsecolo equivale a 1 milionesimo di un secolo.

Basta quindi fare $100*365*24*60/1000000.0=52.56$ per sapere i minuti di un secolo. (approssimare a 53m è quasi sbagliato)

Extra:
Per avere il valore in secondi si farà quindi $100*365*24*60*60/1000000.0=3153.6$ (approssimare a 3154s è quasi sbagliato)


##Domanda 4
Quale è in percentuale l'approssimazione dell'affermazione di Fermi?
Si usi la formula:
$$\text{approx. percentuale} = \left(\frac{\text{valore vero - valore approx.}}{\text{valore vero}}\right) \times 100$$

###Soluzione 4
4,9

Basta prendere il risultato della soluzione 3, sottrargli 50 del suggerimento 1, dividere per il risultato della soluzione 3 e moltiplicare per 100.
$$\text{4,9} = \left(\frac{\text{52,56 - 50}}{\text{52,56}}\right) \times 100$$

quindi:
$$abs(52.56-50)/52.56*100=4,87 \approx 4,9$$

_Nota: Nella sottrazione bisogna prendere il valore assoluto, quindi se fosse stato $50-52.56=-2.56$, si sarebbe preso comunque 2.56_

_Nota2: Se si fosse preso 53 come valore vero, avrebbe dato 6, quindi errato; Se non si fosse approssimato 4.87 in 4.9, sarebbe stato considerato quasi sbagliato._

_Nota3: $abs(52.56 - 50) = |52.56 - 50|$_
