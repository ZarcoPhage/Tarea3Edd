Tarea 3 - Problema 1: CacheDiccionario
=============================================
--------------------------------------------------------------------
REQUERIMENTOS DEL AMBIENTE PARA COMPILAR
--------------------------------------------------------------------
- Sistema operativo: Linux, distribución preferiblemente basada en Debian
- Compilador g++

--------------------------------------------------------------------
COMPILACIÓN
--------------------------------------------------------------------
- Comando de compilacion:
  $ g++ main.cpp -o test -Wall

- genera el archivo 'test' en el directorio Tarea3Edd/problema1
--------------------------------------------------------------------
EJECUCIÓN
--------------------------------------------------------------------
- luego de compilar el código main.cpp, ejecutar el comando:
  $ ./test
--------------------------------------------------------------------
CONSIDERACIONES AL MOMENTO DE COMPILAR
--------------------------------------------------------------------
Esta aplicación fue desarrollada ocupando sistema Linux:
  Parrot OS 5.0 (Electro Ara)
  Kernel Linux 5.16.0-12parrot1-amd64

Compilado a través de:
  g++ 10.2.1 20210110

Los accesos a la HashTable del diccionario solo se cuentan en el caso de las consultas

El archivo main.cpp es un código de prueba, para ocuparlo, ejecutar e ingresar los comandos:

$ insert <termino> <significado> 
    - para insertar termino en el diccionario (LEER COMENTARIOS DE FUNCIONES AL INTERIOR DEL ARCHIVO 'cache-diccionario.cpp')
    - imprime la tabla posterior a la insercion con formato:
        - para la primera línea:
            $ <consultas totales> : <significados conocidos> : <significados desconocidos> : <limpiezas totales> : <significados encontrados> : <significados no encontrados> : <accesos totales>
        - para cada ranura:    
            $ <numero de ranura> : <termino> : <significado> : <significado vacio> : <estado> : <consultas>

            *significado vacio : booleano que indica si el significado de un término se haya vacío
            *estado: valor que indica si la ranura está vacia (-1), borrada (-2) u ocupada (-3)
            *consultas : cantidad de consultas

$ query <termino>
    - para consultar por un termino al diccionario
$ END
    - para terminar de ocupar el diccionario e imprimir en pantalla la tabla correspondiente    