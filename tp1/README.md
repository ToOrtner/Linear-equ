## Para compilar el programa, desde una consola ejecutar:

```bash
$ sudo apt-get install libgtest-dev
$ sudo apt-get install cmake # install cmake
$ cmake CMakeLists.txt
$ make
```

- libgtest-dev son las librerias de testing.
- cmake para generar el Makefile
- make para compilar y generar los binarios:
    - tp1 el programa
    - seasonTests genera datos para los experimentos
    - elimGaussTests, solveSystemTests para testear el programa

## Para correr el programa, desde la misma consola ejecutar:
```bash
$ ./tp1 input_file.dat output_file method
```

donde:
    input_file.dat es el archivo de entrada, con el formato correspondiente.
    output_file es el archivo donde se guardará el resultado.
    method es:
        0: para ejecutar con el método CMM
        1: para ejecutar con el método WP
        2: para ejecutar con el método WPL


## Para correr los test ejecutar:
```bash
$ ./elimGaussTests
$ ./solveSystemTests
```

Para generar los datos para los experimentos ejecutar:
```bash
$ ./seasonTests
```