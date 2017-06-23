----------------------------------------------------
# Esercitazione 1 - Selection Sort (Iter/Bin)
Si è visto il Selection Sort in maniera iterativa e ricorsiva.

- I computer su Windows non riescono ad ottenere tempi di esecuzione per
N <= 1000 in quanto ci mettono meno di 0.001s
- L'algoritmo scritto in maniera ricorsiva è più performante di quella interattiva
se N <= 10000
- L'algoritmo scritto in maniera interattiva è più performante di quella
ricorsiva se N >= 100000
- Il caso peggiore equivale al tipo INV_ORDINATO, poi QUASI_ORDINATO
(eccetto se N == 500000), CASUALE ed infine ORDINATO

Tempo: O(n2)
Memoria: O(1)

----------------------------------------------------
# Esercitazione 2 - Ricerca Binaria (Iter/Bin)
Si è visto il binary search in maniera iterativa e ricorsiva.

- Nel caso peggiore, la ricerca banale sarà O(N), mentre quella binaria sarà O(log2 N)
- La ricerca banale potrebbe avere una velocità di ricerca migliore di quella binaria
	solo se trovasse un elemento prima di (log2 N) elementi, altrimenti sarà sempre più lenta
	di quella binaria
- La ricerca banale, se non trova elementi, confronta N elementi, mentre
quella binaria rimane sempre (log2 N)

Banale: O(n)
Binaria: O(logn)

----------------------------------------------------
# Esercitazione 3 - Matrici Sparse
Usate per ridurre la grandezza generale di un array quando la quasi totalità dei suoi elementi sono 0.

- Il numero di locazioni usate per allocare una matrice classica è uguale al numero di righe per colonne, quindi O(righe × colonne)
- Il numero di locazioni usate per allocare una matrice sparsa equivalente alla classica è uguale al numero degli elementi utili
(non-zero/non-nulli) moltiplicati per la grandezza della tripla (n × 3) sommando infine l’indice, quindi O((n + 1) × 3)

Si ha quindi un risparmio di memoria usando una matrice sparsa quando gli elementi utili sono inferiori almeno al 32% degli
elementi della matrice. Caso limite:
(32 % elementi utili + 1 indice) × 3 grandezza tripla = 99 % rispetto a matrice classica
Per quanto riguarda la complessità computazionale degli algoritmi di ricerca, abbiamo:
- Per quanto riguarda la matrice classica, si tratta di O(righe × colonne)
- Per quanto riguarda la matrice sparsa, si tratta di O(elementi utili) quindi O(n).
Nota: Le proporzioni sono state fatte in base ad una tripla formata da 3 campi int.

Trasponi: O(Righe x Colonne)
Trasponi Rapida: O(Elementi + Colonne)

----------------------------------------------------
# Esercitazione 4 - Pattern Matching

Col pattern match, cerchiamo un determinato pattern in una determinata stringa.
Il metodo ingenuo può essere quadratico, mentre il KMP è lineare.

L'alg insucc crea una array contenente a quale caso indietro andare in caso il match fallisce. (creata prima di iniziare match)
L'array è in base al numero delle ripetizioni di una data stringa. Solitamente, -1 corrisponde a un no-match (solitamente le prime lettere e quelle dopo ad un "ciclo" di pattern)

Ingenuo: O(n×m)
insucc: O(n) = O(#pat)
match: O(m) = O(#stringa)
match+insucc: O(n + m)

(Knuth, Morris and Pratt)

----------------------------------------------------
# Esercitazione 5 - Stack e Queue

È rappresentato solitamente come una lista ordinata.
La funzione Pop ritorna l'elemento rimosso dalla lista.

## Stack
Lo stack (pila) è un LIFO (last in, first out).

## Queue
Il queue (coda) è un FIFO (first in, first out).

Una coda è una lista ordinata in cui l’inserimento e la cancellazione avvengono in una posizione
predeterminata: gli inserimenti avvengono ad un estremo e le cancellazioni avvengono all’estremo
opposto.
Una coda è una lista ordinata in cui l’inserimento e la cancellazione avvengono in una posizione
predeterminata: gli inserimenti avvengono ad un estremo e le cancellazioni avvengono all’estremo
opposto

Una coda implementa una lista di tipo “first in, first out” (FIFO)
- viene cancellato l’elemento che per più tempo è rimasto nell’insieme
- una coda possiede una testa (davanti) e una coda (dietro)
- quando si aggiunge un elemento, viene inserito in fondo alla coda
- quando si rimuove un elemento, viene estratto quello in testa

L'implementazione banale della coda aumenta l'indice fino a raggiungere il massimo.
Con l'implementazione ciclica, questo problema si risolve, modulando per #lista.

----------------------------------------------------
# Esercitazione 6 - Liste concatenate e Fusione
Accesso dinamico e sequenziale con tutte le operazioni come O(n)

----------------------------------------------------
# Esercitazione 7 - Alberi, Heap e Coda con Priorità

## Alberi
- Nodo: rappresenta sia le informazioni che i rami di collegamento con i sottoalberi;
- Grado di un nodo: numerodi rami del nodo (quanti in un albero binario?);
- Grado di un albero: massimo valore dei gradi di ciascun nodo;
- Foglia: nodo avente grado nullo;
- Padre: nodo avente grado non nullo e padre delle radici dei suoi sottoalberi;
- Fratelli: nodi aventi lo stesso padre;
- Antenati di un nodo: nodi che si trovano nel percorso dalla radice al nodo;
- Discendenti di un nodo: nodi che si trovano nei sottoalberi del nodo di cui è radice;
- Livello di un nodo: è pari al livello del padre aumentato di 1 (la radice ha livello 1);
- Altezza (o profondità) di un albero: livello massimo di un nodo dell’albero.
- Albero pieno: Un albero binario di profondità k si dice pieno quando è costituito da (2^k)-1 nodi.
- Albero completo: Un albero binario di profondità k e n nodi si dice
	completo se i suoi nodi corrispondono ai nodi da 1 a n dell'albero pieno.

## Heap
- Heap massimo: un albero binario completo di n elementi organizzati in modo
	che il valore in un nodo qualsiasi sia maggiore o uguale a quelli contenuti nei figli.
- Heap minimo: un albero binario completo di n elementi organizzati in modo che
	il valore in un nodo qualsiasi sia minore o uguale a quelli contenuti nei figli.

## Coda con Priorità
Le code di priorità rappresentano una delle applicazioni più efficienti della struttura dati Heap;
- Una coda con priorità è una struttura dati utilizzata per mantenere un insieme di elementi
	a ciascuno dei quali è associato un valore chiamato chiave e una priorità (che ne
	determina la posizione);
- Si possono rappresentare in modi differenti;
- Essendo l’heap un albero binario completo, si può rappresentare utilizzando un array,
	strutturato come spiegato nella slide precedente.

O(1) e O(n) per aggiunta, cancellazione su coda non ordinata
O(n) e O(1) per aggiunta, cancellazione su coda ordinata

----------------------------------------------------
# Esercitazione 8 - Alberi (in generale)

## ABR
Definiamo un albero binario di ricerca come un albero binario con le seguenti caratteristiche:
- le chiavi sono uniche;
- le chiavi del sottoalbero sinistro non vuoto sono più piccole della chiave della radice;
- le chiavi del sottoalbero destro non vuoto sono più grandi della chiave della radice;
- I sottoalberi sinistro e destro sono anch’essi alberi binari di ricerca.

Un albero binario di ricerca è rappresentato mediante nodi collegati
tramite puntatori:
- ogni nodo contiene un campo chiave;
- ogni nodo ha un riferimentoal suo figlio sinistro, destro e al padre.

## ABR ricerca
Se la radice è NULL, la ricerca non ha successo.
Altrimenti, si confronta la chiave da ricercare con la chiave della radice:
- se i due valori sono uguali, la ricerca termina con successo;
- se la chiave è minore della chiave della radice, allora si effettua la
	ricerca nel sottoalbero sinistro della radice;
- se la chiave è maggiore della chiave della radice, allora si effettua la
	ricerca nel sottoalbero destro della radice.

Ricerca: O(h)

## ABR successore/predecessore
Per cercare il successore di un nodo dato si procede come segue:
- se il nodo ha un figlio destro, il successore è il minimo del suo sottoalbero destro;
- se il nodo non ha un figlio destro, si risale l’albero finché il nodo di
	provenienza sta a sinistra (il nodo cercato risulta essere il massimo
	del sottoalbero sinistro con il suo successore come radice).
Per cercare il predecessore di un nodo dato, si procede simmetricamente.

## ABR cancellazione per copiatura
Per cancellare un nodo da un ABR, si devono prevedere tre differenti casi:
- cancellazione di un nodo di grado 0 (foglia): si imposta a NULL il
	campo figlio (sx o dx, a seconda del caso) del padre del nodo
	cancellato;
- cancellazione di un nodo di grado 1: si collega il sottoalbero del
	nodo da cancellare con il campo figlio del padre;
- cancellazione di un nodo di grado 2: si sostituisce il nodo da
	cancellare con l’elemento più piccolo del suo sottoalbero destro
	(oppure con il più grande del suo sottoalbero sinistro), infine si
	cancella anche tale nodo.

## visite in profondità
Le visite in profondità permettono di visitare i nodi una sola volta durante
l’attraversamento e sono:
- Inorder (SVD);
- Preorder (VSD);
- Postorder (SDV).

----------------------------------------------------
# Esercitazione 9 - Grafi
Un grafo è una struttura dati composta da:
- Un insieme finito e non vuoto di nodi, N(G);
- Un insieme finito ed, eventualmente, vuoto di lati (archi), L(G).

Altro:
- Un grafo non orientato è un grafo in cui la coppia di vertici che
rappresentano un lato qualsiasi non è ordinata.
- Un grafo orientato è un grafo in cui un lato è rappresentato da una
coppia ordinata di vertici. In questo caso si parla di coda e testa del
lato.

## grafi, adiacenze
- Due vertici di un grafo si dicono adiacenti se esiste un lato che li unisce.

## grafi, incidenze
- Un lato (V1, V2) (o <V1,V2> o <V2,V1>) si dice incidente nei vertici V1 e V2.

## grafi, liste di adiacenza
- Si usa un array di puntatori a nodo per
rappresentare gli id dei nodi del grafo;
- Per ogni vertice si costruisce una lista
concatenata contenente i lati in uscita
dal nodo;
- Gli elementi dell’array sono i puntatori
alle teste delle liste di adiacenze.

## visita in profondità (DFS)
Dobbiamo utilizzare una struttura dati ausiliaria: stack (solo idealmente)
- Quando visitiamo un nodo lo mettiamo nello stack (push) e visitiamo
ricorsivamente il primo nodo adiacente non ancora visitato;
- Dopo che abbiamo visitato tutte le adiacenze di un nodo, lo togliamo dallo stack
(pop).

- NB#1: non c’è bisogno di implementare lo stack perché lo simuliamo con una serie di
chiamate ricorsive.
- NB#2: abbiamo necessità di un array ”visitato” dove teniamo traccia di quali nodi abbiamo
già visitato.

## visita in ampiezza (BFS)
Dobbiamo utilizzare una struttura dati ausiliaria: coda (reale)
- Quando visitiamo un nodo lo inseriamo nella coda (push) e visitiamo tutta la sua
lista di adiacenze;
- Quando abbiamo visitato tutta la sua lista di adiacenze lo eliminiamo dalla coda
(pop).

Dobbiamo utilizzare una struttura dati ausiliaria: coda (reale)
- Quando visitiamo un nodo lo inseriamo nella coda (push) e visitiamo tutta la sua lista di
adiacenze;
- Quando abbiamo visitato tutta la sua lista di adiacenze lo eliminiamo dalla coda (pop).
- NB#1: possiamo (dobbiamo) riciclare TUTTA l’implementazione della struttura dati Coda
dall’esercitazione 5.
- NB#2: abbiamo necessità di un array ”visitato” dove teniamo traccia di quali nodi abbiamo
già visitato.

----------------------------------------------------
# Esercitazione 10 - Hash Table
Una hash table è una struttura dati astratta che mette in corrispondenza
una certa chiave con un dato valore. L’idea è semplice.
Definiamo:
- U = universo di tutte le possibili chiavi;
- T = tabella hash;
- m = dimensione della tabella T;
- n = numero di elementi effettivi da memorizzare in T;
- k = una generica chiave;
- h(k) = il risultato dell’applicazione di una certa funzione h ad un certo valore (chiave) k.

La regola generale delle hash table è la seguente: T[ h(k) ] = k .

## funzione hash
Una funzione hash (h) è una funzione che, data una certa chiave k
appartenente all’universo U, restituisce la posizione h(k) della tabella in cui
l’elemento con chiave k viene memorizzato

Il problema è che la dimensione della tabella T (denominata con m) non
potrà, per ovvi motivi, essere grande quanto l’intero universo U.

Questo fenomenoviene chiamato collisione.

## gestione delle collisioni
Impossibile scegliere una funzione hash perfetta

Utilizzare una “buona” funzione hash, per minimizzare il numero delle
collisioni, e gestirle se si presentano:
- Liste di collisione: una generica locazione T[i] della tabella non
contiene più un unico valore bensì il puntatore alla lista di elementi
collidenti in i.
- Indirizzamento aperto: se una cella è già occupata si cerca la prima
cella libera. Tutti gli elementi sono memorizzati nella tabella.

## lista delle collisioni
- Tutti gli elementi collidenti in una data posizione i vengono inseriti nella
stessa posizione della tabella, in una lista concatenata.
- La locazione T[i] della tabella non contiene più un unico valore bensì il
puntatore alla lista di elementi collidenti in i.

----------------------------------------------------
# Esercitazione 11 - Algoritmi di ordinamento

## SelectionSort
L'algoritmo seleziona di volta in volta il numero minore nella sequenza di partenza e
lo sposta nella sequenza ordinata; di fatto la sequenza viene suddivisa in due parti:
la sottosequenza ordinata, che occupa le prime posizioni dell'array, e la sottosequenza
da ordinare, che costituisce la parte restante dell'array.

Dovendo ordinare un array A di lunghezza n, si fa scorrere l'indice i da 1 a n-1
ripetendo i seguenti passi:
- si cerca il più piccolo elemento della sottosequenza A[i..n];
- si scambia questo elemento con l'elemento i-esimo.

Memoria O(1)
Tempo O(n2)

## InsertionSort
- Si considera un elemento alla volta da sinistra a destra.
- Si inserisce ciascun elemento al proprio posto tra quelli già considerati,
mantenendoli ordinati.
- L’elemento considerato viene inserito nel posto rimasto vacante in
seguito allo spostamento di un posto a destra degli elementi più
grandi.
- Complessità nel caso peggiore: O(n2) ma mediamente O(n log n).

Memoria O(1)
Tempo Omega(n) O(n+d), Theta(n2)

## QuickSort
Si basa sulla metodologia Dividi et Impera:
- Dividi: L’array A[p…u] viene “partizionato” (tramite spostamenti di
	elementi) in un elemento A[q] (detto perno) e due sottoarray A[p…q-1]
	e A[q+1…u] in cui ogni elemento di A[p…q-1] è minore di A[q] e ogni
	elementodi A[q+1…u] è maggiore di A[q].
- Conquista: i due sottoarray A[p…q-1] e A[q+1…u] vengono ordinati
	ricorsivamente con quicksort.
- Combina: i sottoarray vengono ordinati anche reciprocamente, quindi
	non è necessaria alcuna combinazione.A[p…u] è già ordinato.
- Complessità nel caso peggiore: O(n2) ma mediamente O(n log n).

Memoria O(1)
Tempo O(nlogn), Theta(n2)

----------------------------------------------------
# Esercitazione 12 - Algoritmi di ordinamento p2
- Esistono diversi algoritmi di ordinamento con complessità pari a O(n log n) dove
	n è il numero di elementi da ordinare.
- La scelta dell’algoritmo più appropriato a una data applicazione dipende da
	diversi fattori, come il numero di elementi da ordinare o il livello di ordinamento
	iniziale degli elementi.
- La complessità di un algoritmo di ordinamento, anche di quello “ottimo”, non
	può mai essere inferiore a O(n log n).

## Merge sort
Fonde due liste ordinate: lista[i],..., lista[m] e lista[m+1],..., lista[n] per ottenere una
sola lista ordinata ordinata[i],..., ordinata[n] utilizzando un array ausiliario ordinata
precedentemente allocato.
- Si suddivide la lista in piccoli gruppi;
- Si ordinano i gruppi separatamente ;
- Si fondono i gruppi a due a due in un unico gruppo ordinato;
- Si ripete nuovamente la fusione a due a due sui nuovi gruppi appena formati.
Il cuore dell’algoritmo è la funzione di fusione.
La complessità computazionale è O(n log n).

Memoria O(n)
Tempo O(nlogn)

### fusione
Fonde due liste ordinate: lista[i],..., lista[m] e lista[m+1],..., lista[n] per ottenere una sola lista
ordinata ordinata[i],..., ordinata[n] utilizzando un array ausiliario ordinata precedentemente
allocato.

## Heap sort
È una variazione del Selection sort in cui si ricerca l’elemento massimo invece che
l’elemento minimo e l’ordinamento viene effettuato a partire dall’ultimo elemento
(e non dal primo). Per trovare l’elemento massimo, ad ogni iterazione, viene
utilizzato uno Heap come struttura di appoggio.
- Si “trasforma” l’insieme di elementi da ordinare in uno heap (tramite una fuzione
	chiamata “adatta”);
- Si sfrutta la proprietà dello Heap per cui la radice contiene sempre il valore
	massimo;
- Si estraggono uno alla volta i valori dallo Heap e si mettono in fondo alla
	sequenza;
- Dopo ogni estrazione si richiama la funzione adatta per ripristinare lo heap.
	La complessità computazionale è O(n log n).

Memoria O(1)
Tempo O(nlogn)

### adatta
Gli n elementi da ordinare vengono inseriti in un heap inizialmente vuoto.
- Gli elementi vengono estratti dall’heap, uno alla volta ed inseriti in fondo alla sequenza.
- Per costruire uno heap da un array di n elementi si utilizza l’algoritmo adatta, inserendo
	ogni elemento dell’array e risistemando gli elementi fuori posto.

# Teoria
## Costo delle operazioni degli ABR
- Gli alberi binari di ricerca sono strutture di dati sulle
	quali vengono realizzate molte delle operazioni definite
	sugli insiemi dinamici.
- Tutte le operazioni richiedono un tempo proporzionale
	all’altezza h dell’albero O(h). Nel caso peggiore (alberi molto sbilanciati e profondi)
	richiedono un tempo O(n). E’ importante che l’albero sia bilanciato, in modo da non
	ricondurci ad una catena lineare.
- Gli alberi binari di ricerca sono strutture di dati sulle
quali vengono realizzate molte delle operazioni definite
sugli insiemi dinamici.
- Tutte le operazioni richiedono un tempo proporzionale
	all’altezza h dell’albero O(h). Nel caso peggiore (alberi molto sbilanciati e profondi)
	richiedono un tempo O(n). E’ importante che l’albero sia bilanciato, in modo da non
	ricondurci ad una catena lineare

Quindi:
- Se l’albero è bilanciato, l’altezza dell’albero è pari a O(logn)
	- le operazioni sono eseguite nel caso peggiore con un tempo O(logn).
- Si può dimostrare che l’altezza di un albero binario di
	ricerca costruito in modo casuale è O(logn).
- Nella pratica non si può garantire che gli alberi binari di
	ricerca siano sempre bilanciati!
- Ci sono varianti che danno questa garanzia
	- le prestazioni nel caso peggiore per le operazioni sono O(logn).

## Gli alberi AVL
- Un albero è bilanciato in altezza se le altezze dei
	sottoalberi sinistro e destro di ogni nodo
	differiscono di al più un’unità.
- Gli alberi binari di ricerca bilanciati in altezza
	sono detti alberi AVL.
- Il fattore di bilanciamento (v) di un nodo v è definito come
	- (v) = altezza del sottoalbero sin di v - altezza del sottoalbero des di v
- Un albero binario di ricerca è un albero AVL se ogni nodo
	v ha fattore di bilanciamento in valore assoluto = 1.
- Si può dimostrare che un albero AVL con n nodi
	ha altezza O(logn).

### Implementazioni delle operazioni
- L’operazione Search procede come in un ABR.
- Ma inserimenti e cancellazioni potrebbero sbilanciare l’albero.
- Il bilanciamento viene mantenuto tramite opportune rotazioni

## Problema del percorso minimo
Sia G un grafo orientato pesato
- ad ogni lato a è associato un peso intero positivo p_{a}
- Ai percorsi (orientati) nel grafo è assegnato un peso, dato
	dalla somma dei pesi degli archi che lo compongono.
- Dati due nodi x e y, il problema del percorso minimo
	consiste nel fornire un percorso da x a y di peso minimo.
- Se tutti i lati sono pesati 1, il problema si risolve con una
	visita in ampiezza.

## Radix sort
Vengono riordinati dalla cifra meno significativa
