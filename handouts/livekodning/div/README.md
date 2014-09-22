Livekodningen den 19 september som gick ut på att undersöka olika
sätt att returnera två värden från en funktion. 

Följande program går att bygga med make:

* `divArray` skapar en array som fylls av funktionen.

* `divPointer` skickar med pekare till två stackvariabler som skrivs direkt av funktionen

* `divStructStack` definerar en tupel-struct som allokeras på stacken och returneras från funktionen

* `divStructHeap` använder samma tupel-struct men allokerar den på heapen istället

* `divStructModule` använder samma tupel-struct, men kapslar in den i en egen modul (se `tuple.c`)

* `div` är som `divStructModule` men implementerar de förbättringar i användargränssnittet som vi pratade om.