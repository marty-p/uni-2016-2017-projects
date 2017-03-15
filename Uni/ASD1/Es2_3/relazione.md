| Dim array | numric | Presente | Pos.  | Banale tempo | Banale num elem | Bin. Iter tempo | Bin. Iter num elem | Bin. Rec tempo | Bin. Rec num elem |
| --------- | ------ | -------- | ----- | ------------ | --------------- | --------------- | ------------------ | -------------- | ----------------- |
| 10 | 18 | sì | 1 | 0.0 | 2 | 0.0 | 2 | 0.0 | 2 |
| 10 | 19 | no | -1 | 0.0 | 10 | 0.0 | 3 | 0.0 | 3 |
| 50 | 10 | sì | 1 | 0.0 | 2 | 0.0 | 6 | 0.0 | 6 |
| 50 | 11 | no | -1 | 0.0 | 50 | 0.0 | 6 | 0.0 | 6 |
| 100 | 34 | sì | 1 | 0.0 | 2 | 0.0 | 6 | 0.0 | 6 |
| 100 | 35 | no | -1 | 0.0 | 100 | 0.0 | 7 | 0.0 | 7 |
| 1000 | 54 | sì | 1 | 0.0 | 2 | 0.0 | 10 | 0.0 | 10 |
| 1000 | 55 | no | -1 | 0.0 | 1000 | 0.0 | 10 | 0.0 | 10 |
| 10000 | 6 | sì | 1 | 0.0 | 2 | 0.0 | 12 | 0.0 | 12 |
| 10000 | 7 | no | -1 | 0.0 | 10000 | 0.0 | 13 | 0.0 | 13 |
| 100000 | 9 | sì | 1 | 0.0 | 2 | 0.0 | 17 | 0.0 | 17 |
| 100000 | 10 | no | -1 | 0.0 | 100000 | 0.0 | 17 | 0.0 | 17 |
| 500000 | 9 | sì | 1 | 0.0 | 2 | 0.0 | 19 | 0.0 | 19 |
| 500000 | 10 | no | -1 | 0.001 | 500000 | 0.0 | 19 | 0.0 | 19 |

Possiamo quindi affermare che:

* Nel caso peggiore, la ricerca banale sarà O(N), mentre quella binaria sarà O(log2 N)
* La ricerca banale potrebbe avere una velocità di ricerca migliore di quella binaria
  solo se trovasse un elemento prima di (log2 N) elementi, altrimenti sarà sempre più lenta
  di quella binaria
* La ricerca banale, se non trova elementi, confronta N elementi, mentre
  quella binaria rimane sempre (log2 N)
