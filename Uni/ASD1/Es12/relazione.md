Confronti:

- Il selectsort effettua un numero di confronti e scambi equivalente per ogni tipologia di array per lo stesso input pari a $\approx\frac{(n-0.5)^2}{2}$ e $n-1$.
- L'insertsort effettua un numero di confronti uguali a quelli del selectsort in array inversamente ordinati per lo stesso input.
- L'insertsort effettua lo stesso numero di confronti e scambi in array ordinati per lo stesso input pari ad $n-1$.
- Il quicksort effettua un numero di scambi uguali a quelli del selectsort in array ordinati e inversamente ordinati.

- Il mergesort è l'algoritmo che ha meno confronti, eccetto per l'insertsort in array ordinati.
- Il selectsort è l'algoritmo che ha meno scambi.

- Il selectsort ha il numero di confronti più alto, eccetto per il quicksort in array ordinati o inversamente ordinati.
- L'insertsort ha il numero di scambi più alto, eccetto negli array ordinati, susseguito poi dall'heapsort.

Tempo:

- Il selectsort è l'algoritmo che impiega mediamente più tempo di tutti gli altri algoritmi per ogni tipologia di array.
- L'insertsort è l'algoritmo che impiega più tempo di tutti gli altri in array inversamente ordinati, seguito da selectsort e quicksort.
- Il quicksort è il secondo algoritmo che impiega più tempo di tutti gli altri in array ordinati, preceduto dal selectsort.
- L'insertsort è il secondo algoritmo che impiega più tempo di tutti gli altri in array casuali, preceduto dal selectsort.
- Il mergesort è l'algoritmo che impiega mediamente meno tempo di tutti gli altri, seguito dallo heapsort.

Ottimizzando:

- Applicando il flag `-O3` è possibile ottenere risultati molto più ottimizzati, tra le quali:

	- Il mergesort il doppio più veloce dell'heapsort in array ordinati
	- L'heapsort il doppio più veloce dell'heapsort in array inversamente ordinati

