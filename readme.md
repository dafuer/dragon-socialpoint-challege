Social Point Challenge:
=======================

A dragon flies in a series of one-fifth circular arcs (72°), and with a free choice of a clockwise or an anti-clockwise arc for each step. One of the 70932 possible closed paths of 25 arcs starting northward is the 
following one:

(image)

Given that the dragon starts facing North, how many journeys of 120 arcs in 
length can it take to return, after the final arc, to its starting position?

Rules:

* Any arc may be traversed multiple times.

* In each step, the direction change must be exactly +/- 72º

* Both the starting and the end direction must be north.

* All arcs must have the same radius



Solución:
---------

Solución propuesta mediante backtracking que no es capaz de llegar a resolver el problema: ineficiente :(


Compilacion:
------------

```
gcc dragon.c -o dragon -lm
```


Ejemplo uso 25 pasos:
---------------------

```
 $ ./dragon 25
 Number of posible solutions: 70932
```


