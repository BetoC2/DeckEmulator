# Deck Emulator 

## Funcionamiento

Comenzamos el código declarando funciones de diferentes tipos: 
1. Para cargar la baraja de forma aleatoria
2. Pull para robar en la parte superior de la carta
3. Bottom para regresarla en la parte inferior
4. Discard para descartar la carta
5. Guardar para guardar el par de cartas 
6. Cargar para volver a cargar las cartas que se han guardado con anterioridad.
7. E imprimir cuyo principal objetivo es mostrar en pantalla en pantalla el estado de la baraja y cual es la carta que se tiene en la mano, incluso mostrando el número 10 en lugar de su representación que en este caso es D

Seguimos con la función crear_baraja en la cual empiezan las cartas, pues recibe de argumento Target char de tipo apuntador dónde ese guarda la cadena "DJQKA", se declara una variable de tipo entero llamada random, si Target es menor que 5 se activa un ciclo while dónde random se evalúa con el valor de 5, se hace un ciclo de tipo burbuja para aumentarse con i++, esto permite guardar en otro apuntador las cartas en un orden aleatorio.


Brincamos a la función pull, pues empezamos con entradas de texto donde nos explica cada uno de los casos del switch.

- Caso t: la carta se cambia hacia la parte superior 
- Caso b: la carta se cambia hacia la parte inferior 
- Caso d: se activa la función discard para descartar una carta
- Caso s: funciona para guardar las cartas 
- Caso l: funciona para cargar las cartas guardadas 
- Y por default nos lanza un "no le sabe" cuando el usuario no llama ninguna de las anteriores.

Para antes de esto se declara una variable de tipo char input con valor de 255 y otra llamada opción con valor de "x" y por último un ciclo while para pedirle al usuario una d ellas opciones anteriores.
Después siguen las funciones bottom, discard, cargar, guardar cómo ya se explicaron anteriormente, pero lo interesante aquí es que las funciones cargar y guardar se utilizaron las funciones fread, fwrite, fclose y fopen, se creó un archivo donde al abrirse lee y guarda las cartas dentro de la función guardar, después con fread y fopen abre ese archivo para cargar las cartas en la función cargar.

A su vez estas funciones permiten “encriptar” los datos necesarios para cargar y guardar partida con únicamente 3 bytes de memoria, esto se hace guardando la baraja en un unsigned short con un peso de 2 bytes, haciendo que cada digito de este represente una de las cartas, siendo 0 un espacio vació, 1 el 10, 2 la J, 3 la Q, etc. A su vez en otra variable de tipo char se guarda igualmente en un dígito la carta que se tenía en la mano y en otro el número de cartas que se poseían al momento de guardar.
Por último, tenemos el main dónde básicamente carga todo lo anterior, con salidas de pantalla las cuales explican para que funciona cada uno de los casos del switch:

- Caso p: tomar la carta
- Caso t: mandar la carta a la parte superior
- Caso s: para guardar la partida
- Caso l: para cargar la partida
- Y por último el caso e, dónde finaliza el programa.

## Precauciones 

Solo se puede tener una partida en memoria, en caso de que se haga una nueva se sobreescribirá la partida anterior.

Evite cargar una partida si no existe una ateriormente.
