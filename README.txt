Tarea 3
=============================================
--------------------------------------------------------------------
IMPORTANTE
--------------------------------------------------------------------
- leer archivos README.txt correspondientes a cada problema:
    Tarea3Edd/problema1/README.txt
    Tarea3Edd/problema2/README.txt

- los requerimentos, instrucciones de compilación y ejecución correspondientes se hayan en los archivos mencionados anteriormente

--------------------------------------------------------------------
REQUERIMENTOS DEL AMBIENTE PARA COMPILAR
--------------------------------------------------------------------
- Sistema operativo: Linux, distribución preferiblemente basada en Debian
- Compilador g++

--------------------------------------------------------------------
COMPILACIÓN
--------------------------------------------------------------------
* problema 1:
    - moverse al directorio Tarea3Edd/problema1

    - Comando de compilacion problema 1:
        $ g++ main.cpp -o test - Wall

    - genera el archivo 'test' en el directorio mencionado
*  problema 2:
    - moverse al directorio Tarea3Edd/problema2/datasets

    - Comando de compilacion problema 2:
        $ g++ -g main.cpp graphs.cpp -o main -Wall

    - genera el archivo 'main' en el directorio mencionado
--------------------------------------------------------------------
EJECUCIÓN
--------------------------------------------------------------------
- luego de compilar el código main.cpp, ejecutar el comando:
    - para ejecutar problema1:
        $ ./test
    - para ejecutar problema2:
        $ ./main
--------------------------------------------------------------------
CONSIDERACIONES AL MOMENTO DE COMPILAR
--------------------------------------------------------------------
Esta aplicación fue desarrollada ocupando sistema Linux:
  Parrot OS 5.0 (Electro Ara)
  Kernel Linux 5.16.0-12parrot1-amd64

Compilado a través de:
  g++ 10.2.1 20210110

Si se desea chequear fugas de memoria, usar la herramienta Valgrind y el ejecutable generado después
de compilar