[TOC]

----------------------------------------------
# Heap con aggiunta e cancellazione
Q: Definire la struttura dati heap, descrivendone le operazioni di inserimento e cancellazione.
Rappresentare graficamente lo heap dopo l'inserimento delle seguenti chiavi,
nell'ordine con cui sono date: 3,7,5,10,11,14,2,1.
Rappresentarlo nuovamente dopo la cancellazione della chiave maggiore.

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
# Alberi AVL
Gli alberi binari di ricerca (ABR) richiedono un tempo in base all'altezza dell'albero, ovvero O(h).
Nel caso peggiore (in alberi molto sbilanciati) richiedono un tempo O(n).

Per risolvere al problema del caso peggiore, sono stati realizzati gli AVL, ovvero
gli alberi bilanciati in altezza dove i sottoalberi sin e dex si differenziano al più di un'unità.
Se l'albero è bilanciato, l'altezza è pari a O(logn) e le operazioni altrettanto. (caso peggiore incluso)

L'AVL avrà come fattore di bilanciamento in valore assoluto v<=1.

Per effettuare il bilanciamento, vengono fatte delle rotazioni.
Esse richiedono tempo O(1).
Le rotazioni semplici vengono fatte o a destra o a sinistra in base all'occorrenza.

Sia l'inserimento che la cancellazione effettuano dei ribilanciamenti
alla fine per risolvere i nodi critici accumulati:
Insert solo 1, Delete un massimo di logn rotazioni.

Search, Insert, Delete O(logn1)
Bilanciamento O(1)

----------------------------------------------
# Grafi

Un grafo può essere:
-non orientato, in cui la coppia di vertici che
rappresentano un lato qualsiasi non è ordinata.
-orientato, in cui un lato è rappresentato da una
coppia ordinata di vertici. In questo caso si parla di coda e testa del
lato.

Un grafo completo è un grafico col numero massimo di lati,
ovvero che ha un lato tra ogni coppia di vertici.
La loro somma equivale a n*(n-1)/2.

Due vertici di un grafo si dicono adiacenti se esiste
un lato che li unisce.

Un lato (V1, V2) (o <V1,V2> o <V2,V1>) si dice
incidente nei vertici V1 e V2.

Si definisce grado di un vertice il numero di lati
che incidono sul vertice.

Nei grafi orientati si distingue tra grado di uscita
(o uscente) e grado di entrata (o entrante).

Un grafo è un sottografo di un altro grafo se gli insiemi di vertici e
lati coincidono o sono un sottoinsieme del secondo grafo.

Un percorso si dice semplice se tutti i vertici sono distinti ad
eccezione, eventualmente, del primo e dell'ultimo.

Un percorso semplice costituisce una maglia o un ciclo se il primo e
l'ultimo vertice coincidono.

Un grafo senza cicli è detto aciclico.

Se esiste un percorso p tra i vertici v e w, si dice che w è
raggiungibile da v tramite p, v -> w, e che i due vertici
v e w sono connessi.

Se esiste un percorso p tra i vertici v e w, si dice che w è
raggiungibile da v tramite p , v -> w.

Un grafo non orientato è connesso se qualsiasi coppia di
suoi vertici è connessa, ovvero se esiste un percorso da
ogni vertice ad ogni altro vertice.

Un grafo orientato è fortemente connesso se per ogni
coppia di vertici esiste un percorso orientato che li unisce.

Si definisce componente (fortemente) connessa di un
grafo un sottografo massimo (fortemente) connesso.

Un albero è un grafo connesso e aciclico.

----------------------------------------------
# Grafi Visita
Q:
Illustrare e formulare gli algoritmi di visita dei grafi.
Inoltre, supponendo che le liste di adiacenza siano organizzate alfabeticamente
determinare gli alberi derivati in ampiezza e in profondità del seguente grafo
(considerare A come vertice iniziale):

La loro rappresentazione può avvenire tramite
-matrici di adiacenza (spazio O(n^2))
-liste di adiacenza (concatenate o sequenziali) (spazio O(n+l)
-multiliste di adiacenza

La loro visita può avvenire tramite:
-generica
ogni nodo viene scelto marcato la prima volta e si continua
a visitare i successivi, dopodiché si ritorna ai vertici precedenti fino a finire.

-profondità
La ricerca in profondità è simile alla visita preorder di un albero.
Si parte da un vertice v, visitandolo.
Si visita il primo vertice non visitato w adiacente a v.
Si salva la posizione corrente nella lista di adiacenza di v
ponendola nello stack. Si prosegue sino a raggiungere un nodo per il quale tutti i vertici
adiacenti sono stati visitati
(Si risale il cammino sino al primo nodo che ammette un vertice non ancora
visitato e si ricomincia seguendo un nuovo cammino con lo stesso criterio.)
L’attraversamento termina quando tutti i percorsi ignorati nella
visita sono stati considerati (quando lo stack è vuoto).

-ampiezza
La ricerca in ampiezza è simile alla visita per livello di
un albero.
Si visita il nodo di partenza v. Si visitano tutti i nodi adiacenti a v.
Si visitano tutti i nodi non visitati adiacenti al primo
vertice nella lista di adiacenza di v e così via sino a
quando tutti i vertici del grafo sono stati considerati.
Quando si visita un vertice, lo si pone in una coda.
Quando si esamina la sua lista di adiacenza, lo si elimina
dalla coda.

----------------------------------------------
# Grafi percorso minimo
Q: Illustrare e formulare l'algoritmo di Dijkstra.
Si esegua l'algoritmo per calcolare il percorso minimo dal nodo 0
a ciascuno dei restanti nodi del seguente grafo orientato:

Si utilizza tale algoritmo per risolvere il problema del percorso minimo
fornendo un percorso da x a y di peso minimo.

Il valore verrà preso visitando in profondità dal nodo 0 tutti i nodi
prelevando il percorso minimo.

percorso_min O(n^2)
rappresentato da una matrice di adiacenza p
genera il vettore d che contiene il peso del percorso minimo dal vertice v a tutti gli altri
genera il vettore u che contiene il percorso minimo

----------------------------------------------
# Hash buono e metodi
Q: Quando un algoritmo di hashing è considerato buono e spiegane i metodi

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

----------------------------------------------
# Quicksort
Q: Illustrare e formulare l'algoritmo di ordinamento quicksort.
Dimostrare, inoltre, che tale algoritmo è quadratico nel caso più sfavorevole.

Il quicksort ha come caso medio O(nlogn).
Come caso peggiore O(n^2) negli array ordinati o inversamente ordinati.
In quanto il pivot si ferma sempre al primo (o all'ultimo se inversamente ordinato) rompendo
così il bilanciamento.

## Metodologia Divide et Impera
Dividi: L'algoritmo viene suddiviso in due sottoarray attraverso un elemento chiamato perno (pivot).
$$A[primo..q-1] e A[q+1..ultimo]$$
Verranno effettuati degli scambi affinché ogni elemento della prima lista sarà minore del perno,
e ogni elemento della seconda sarà maggiore del perno (sebbene non perfettamente ordinati).

Conquista: I due sottoarray vengono ordinati ricorsivamente
Combina: I sottoarray vengono infine ordinati reciprocamente.

La funzione del pivot si basa sul valore di q.

La complessità del mergesort è descritta dalla seguente relazione
di ricorrenza:
$$T(n) <= cn + T(j) + T(n-j-1) con T(0) = 0$$

## Ordinamento veloce

O(n)

```
algoritmo quickSort(array A, indici u e v)
	if (u = v) then return
	q = Perno(A, u, v)
	if (u < q) then quickSort(A, u, q – 1)
	if (q < v) then quickSort(A, q + 1, v)
```

----------------------------------------------
# Mergesort
Q: Illustrare e formulare l'algoritmo di ordinamento mergesort.
Dimostrare che tale algoritmo di ordinamento è ottimo.

## Perché ottimo
È un algoritmo ottimo in quanto richiede O(nlogn) nel caso medio.

La complessità del mergesort è descritta dalla seguente relazione
di ricorrenza:
$$T(n) <= cn + 2T(n/2) con T(0) = 0$$

## Spiegazione dell'algoritmo
Siano date n liste ordinate, ciascuna di lunghezza 1.
Fondere le liste a coppie per ottenere n/2 liste
ordinate di dimensione 2.
Fondere le n/2 liste a coppie e così via sino ad
ottenere un’unica lista.

## Fusione
Q: Illustrare e formulare l’algoritmo di ordinamento per fusione (versione ricorsiva).
L'Ordinamento per fusione sussiste in:
Suddividere l’insieme in piccoli gruppetti.
Ordinare i gruppetti separatamente (con un metodo qualsiasi).
Prendere il primo ed il secondo gruppetto e fonderli per formare un
nuovo gruppo ordinato.
Ripetere l’operazione con tutti gli altri gruppetti presi a coppie,
fino ad ottenere un numero di gruppi ordinati pari a metà dei
gruppetti originari.
Fondere i nuovi gruppi a coppie e procedere similmente sino ad
ottenere due gruppi ordinati contenenti ciascuno metà degli
elementi, che vengono ora fusi per ottenere l’ordinamento.
Il cuore del metodo di ordinamento è la fusione.

O(n)

```
algoritmo mergesort(array lista, indici lower e upper)
	// ordina la lista lista[lower],..., lista[upper]
	if (lower = upper) then return
	medium = (lower + upper)/2
	mergesort(lista, lower, medium)
	mergesort(lista, medium+1, upper)
	merge(lista, lower, medium, upper)
```

# Heapsort
L’algoritmo heapsort
È una variazione dell’algoritmo di Selezione in cui la
ricerca dell’elemento massimo è facilitata
dall’utilizzo di una opportuna struttura dati
La struttura dati è l’heap
In uno heap l’elemento massimo può essere
acceduto in tempo costante.

## Ordinamento mediante heap
Gli n elementi da ordinare vengono inseriti in un
heap inizialmente vuoto, lista. Gli elementi vengono estratti dall’heap, uno alla
volta ed inseriti in fondo alla sequenza
Ad ogni passo si estrae il massimo, lista[1]
Lo si alloca in fondo alla sequenza
Si adatta l’albero binario per ottenere l’heap, ridotto di 1 elemento.

Si genera la permutazione lista[1] <= lista[2] <= ... <= lista[n].

La complessità dello heapsort è O(nlogn)
