En el siguiente archivo se detallan las instrucciones para ejecutar el código escrito en C++, el cual se encuentra en el archivo "main.cpp".

Preparación del entorno:

En primer lugar, es necesario tener un editor de código, de preferencia Visual Studio Code.

Luego, para compilar, se debe instalar la siguiente herramienta del siguiente enlace: https://jmeubank.github.io/tdm-gcc/download/ según el sistema operativo. 
Debe asegurarse de que se haya agregado a las variables de entorno del sistema, para mayor información revisarel siguiente tutorial: https://www.youtube.com/watch?v=yhTw84ivFUk.

Así mismo, en Visual Studio Code, se debn tener instaladas las siguientes extensiones:

    Name: C/C++
    Id: ms-vscode.cpptools
    Description: C/C++ IntelliSense, debugging, and code browsing.
    Version: 1.19.9
    Publisher: Microsoft
    VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools

    Name: C/C++ Compile Run
    Id: danielpinto8zz6.c-cpp-compile-run
    Description: Compile & Run single c/c++ files easly
    Version: 1.0.58
    Publisher: danielpinto8zz6
    VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=danielpinto8zz6.c-cpp-compile-run

Por último, al abrir la carpeta con el archivo, ir a la Terminal en el menú de opciones (en caso de no ver la Terminal, puede abrirla mediante una combinación de teclas (shortcouts), a veces 'Ctrl + ñ').

Como referencia, también puede guiarse del siguiente tutorial: https://www.youtube.com/watch?v=qQT-6WufAEE

Ejecución del código:

Ejecutar el código dando click en el botón "▶" (ubicado en la parte superior derecha del editor).

Al ejecutar el código se sigue el siguiente procedimiento para obtener los resultados esperados:

    1) Se inicializa un generador de números aleatorios para variar el hash cada vez que se crea un nuevo objeto de Hashing Lineal.
       También se crean cadenas para guardar la información sobre el 'exponente', 'costo promedio real', 'costo máximo permitido' y el 'porcentaje de llenado'.
       Asimismo, se definen las variables auxiliares para controlar la ejecución del programa.
    2) Para controlar la ejecución del programa y la variación del exponente, se hace uso de una estructura repetitiva 'do while', donde se comienza con un exponente de 10 hasta que alcance un valor de 24, sumando 1 en cada iteración. Dentro de cada iteración:
        -> Se crea una nueva instancia de la estructura HashingLineal.
        -> Se insertan (2^exponente) elementos en la tabla hash utilizando una función 'insertar_hash'.
        -> Se calcula el promedio del porcentaje de llenado de las páginas.
        -> Se calcula el costo promedio real, mediante la división del costo actual y la cantidad de elementos insertados.
        -> Se concatenan los resultados del costo promedio real, costo máximo permitido y el porcentaje de llenado, en las cadenas creadas en el punto 1).
        -> Finalmente se elimina la estructura de hash para liberar memoria, se incrementa el exponente para la siguiente iteración y se reinician las variables.
    3) Se imprimen los resultados por consola.

Observación: El tiempo de ejecución del código puede variar dependiendo del sistmea operativo y la memoria disponible, en general, puede tomar un tiempo promedio de 7-8 horas en un sistema operativo Windows con 8 GigaBytes de Ram.

Como resultado se muestra:
Una comparación del costo promedio real con el costo máximo, por exponente.
Una comparación del costo promedio real con el promedio del porcentajes de llenado de las páginas, por exponente.

// -------------------------- Código -------------------------- //

Con respecto a las secciones del código, en el documento de 'Informe' se detallan las funciones utilizadas para la inserción del hashing lineal, sin embargo, a continuación, se da un alcance de las líneas donde se encuentra cada parte del código.

Estructura PaginaPrincipal -> 16
Estructura PaginaRebalse -> 23
Estructura HashingLineal -> 29
Método crear_HashingLineal -> 189
Método Expancion_Hash -> 254
Método insertar_hash -> 278
Método main -> 421

Se puede tener acceso al código completo mediante el siguiente repositorio de GitHub: https://github.com/NicolasPCS/DAA-T1