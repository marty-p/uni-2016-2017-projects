[TOC]

----------------------------------------------
# Heap con aggiunta e cancellazione
Lo heap è un albero binario completo massimo o minimo (ma ci baseremo su quello massimo).

## Aggiunta
Per aggiungere un elemento, inseriamo il nuovo elemento n alla fine dell'array e poi controlliamo
i suoi predecessori, fino alla radice, se siano più grandi di n in posizione di n/2.
Se sì, si scambiano di posto, altrimenti ci si ferma.

## Cancellazione
Per eliminare un elemento, spostiamo l'elemento da eliminare con l'ultimo dell'array e poi lo togliamo.
L'elemento spostato verrà poiriordinato ricontrollando i suoi successori, fino alla fine,
se siano più piccoli di n in posizione di 2n e 2n+1.
Se sì, si scambiano di posto, altrimenti ci si ferma.

----------------------------------------------
# Alberi VLA

----------------------------------------------
# Grafi

----------------------------------------------
# Hash buono e metodi
Un algoritmo di hashing viene considerato buono quando:
- Il numero di incidenze risulta minimizzato
- La tabella risulta riempita in modo uniforme. (uniformità semplice)
- Deve essere facile da calcolare. (tempo `O(1)`)

L'uniformità semplice richiede che ogni elemento della tabella abbia la stessa probabilità
di essere riempita delle altre. (ovvero $\frac{1}{m}$

## Divisione
La funzione di hashing `h(k)` restituisce il risultato di `k mod m`, dove m è solitamente
un numero non troppo vicino ai multipli del 2.

## Moltiplicazione
La funzione di hashing `h(k)` prende un numero A tra 0 e 1 (solitamente $\approx(\sqrt{5}-1)/2$ ovvero 0.618)
e un numero m solitamente $2^p$ dove p, non essendo un valore critico, può essere un valore a scelta.
Dopodiché, ritorna il risultato di $\lfloor m \times (kA - \lfloor k A \rfloor)\rfloor$.

Note: per $\lfloor qualcosa \rfloor$ si intende il valore intero non decimale di un numero
($\lfloor 12.34 \rfloor = 12$)

## Ripiegamento (Folding)
La funzione di hashing `h(k)` divide il numero k in n cifre e le somma insieme.
Dopodiché, ritorna la somma modulata ad m dove m è la dimensione della tabella.

$$(\sum k_i) \mod m$$

Esempio:
$$
\\k = 013402122
\\k_2 = 013, k_1 = 402, k_0 = 122
\\\sum k_i = 013 + 402 + 122 = 537
\\h(k) = 537 \% m
$$
