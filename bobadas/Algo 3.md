# Ejercicio 1
Imposible un algoritmo "común" que lo resuelva. Recurro al backtracking. 
- entrada: n y m.  Una lista de n velocidades de arqueólogos. Otra de m velocidades de caníbales.
- salida: T tiempo mínimo en el que se puede cruzar el puente. 
CruzarPuente:
    Si es posible cruzar arqueólogos. Vuelve el mas rapido. 
    Sino cruzar canibal y arqueólogo. Vuelve arqueólogo 
    Sino 2 canibal. Vuelve arqueologo. ESTO ESTA MAL

La restricción consta en elegir los mas rápidos. 
CruzarPuente(posta) n, m, v, w
    A = vacio
    C = vacio
Si no se muere nadie(v, w, a, c) :
   cruzar a+a c+a c+c (ir por las tres) De los disponibles elegir rápidos
Sino murió nadie(v, w, a, c) 
   Acum += tiempo de la pareja
   Volver arqueologo rapido o canibal rapido (ir por ambas) 
   Llamada recursiva 
Sino devolver - 1

Notas: para elegír rapido el mínimo estaría bueno una lista enlazada ordenada para sacarlo en o(1). Un heap creo que da mejor por menor complejidad de inserción. Se puede usar la implementación en arreglo. 
# Ejercicio 2
El de los pesos.  Tenemos potencias de 3. 
  - entrada: P el peso de la llave que estaba en la izquierda. 
  -	 Salida: pesos en la izquierda y derecha. 
 