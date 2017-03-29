
| Tipo          	| N     	| Secondi (Interattivo)	| Secondi (Ricorsivo)	|
|---------------	|-------	|-------------------	|-------------------	|
| ORDINATO      	| 100   	| 0.000000          	| 0.000000          	|
| ORDINATO      	| 1000  	| 0.000000          	| 0.000000          	|
| ORDINATO      	| 10000 	| 0.062000          	| 0.062000          	|
| ORDINATO      	| 100000	| 5.195000          	| 5.397000          	|
| ORDINATO      	| 200000	| 20.529000         	| 21.559000          	|
| ORDINATO      	| 500000	| 130.339000         	| 139.487000          	|
| QUASI_ORDINATO	| 100   	| 0.000000          	| 0.000000          	|
| QUASI_ORDINATO	| 1000  	| 0.000000          	| 0.000000          	|
| QUASI_ORDINATO	| 10000 	| 0.062000          	| 0.047000          	|
| QUASI_ORDINATO	| 100000	| 5.210000          	| 5.398000          	|
| QUASI_ORDINATO	| 200000	| 20.530000          	| 21.574000          	|
| QUASI_ORDINATO	| 500000	| 130.365000          	| 138.366000          	|
| INV_ORDINATO  	| 100   	| 0.000000          	| 0.000000          	|
| INV_ORDINATO  	| 1000  	| 0.000000          	| 0.000000          	|
| INV_ORDINATO  	| 10000 	| 0.063000          	| 0.062000          	|
| INV_ORDINATO  	| 100000	| 5.679000          	| 5.709000          	|
| INV_ORDINATO  	| 200000	| 22.323000          	| 23.436000          	|
| INV_ORDINATO  	| 500000	| 140.774000          	| 145.564000          	|
| CASUALE       	| 100   	| 0.000000          	| 0.000000          	|
| CASUALE       	| 1000  	| 0.000000          	| 0.000000          	|
| CASUALE       	| 10000 	| 0.062000          	| 0.047000          	|
| CASUALE       	| 100000	| 5.117000          	| 5.367000          	|
| CASUALE       	| 200000	| 20.436000          	| 21.746000          	|
| CASUALE       	| 500000	| 130.839000          	| 139.059000          	|

Dai risultati ottenuti testando l'algoritmo in uno dei computer del Laboratorio T della facoltà, è risultato che:

* I computer su Windows non riescono ad ottenere tempi di esecuzione per N <= 1000 in quanto ci mettono meno di 0.001s
* L'algoritmo scritto in maniera ricorsiva è più performante di quella interattiva se N <= 10000
* L'algoritmo scritto in maniera interattiva è più performante di quella ricorsiva se N >= 100000
* Il caso peggiore equivale al tipo INV_ORDINATO, poi QUASI_ORDINATO (eccetto se N == 500000), CASUALE ed infine ORDINATO
