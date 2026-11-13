# Lab_C_GRUPO-14 - Simulador Artemis: Reingreso y Amerizaje

Trabajo Practico Integrador Final - Algoritmos y Estructuras de Datos
UTN Facultad Regional Resistencia - Ingenieria en Sistemas de Informacion

## Integrantes

Comision: K1.1

| Integrante | Modulo a cargo |
|---|---|
| Pelozo, Angel Esteban | Preparacion del repositorio, Makefile y validaciones |
| Frettis, Andres | Cabeceras, interfaz, reglas y reporte |
| Mendez, Thiago | Funciones fisicas y pruebas |
| Noguera Vega, Juan Sebastian | Logica de las etapas de la mision |
| Alegre Prieto, Elias | Menu principal, calculadora y README |

## Escenario asignado

**Situacion-Problema 4: Reingreso atmosferico, frenado aerodinamico y amerizaje**
(Trabajo, Energia e Impacto). Modulo de tripulacion Orion de 10.400 kg que reingresa
a 11.000 m/s desde 120.000 m, abre paracaidas a 2.500 m con 25 m/s y amerriza a 8 m/s.

## Funcionamiento

El programa se ejecuta por consola y ofrece un menu principal:

1. **Iniciar mision:** simulacion por turnos en 3 fases (reingreso, frenado, amerizaje).
2. **Calculadora de analisis:** responde los puntos a, b, c y d de la consigna con los
   datos de la consigna o con datos ingresados por el usuario.
3. **Reglas del juego.**
4. **Ver historial de misiones:** muestra el reporte de todas las misiones jugadas.
0. **Salir.**

El historial de misiones se guarda en una **lista enlazada** (`NodoMision`): cada mision
jugada agrega un nodo con `malloc` y al salir del programa se libera la memoria con `free`.
El reporte recorre la lista con una funcion recursiva.

### Calculos fisicos

- Energia cinetica: `Ec = 1/2 * m * v^2`
- Trabajo de rozamiento (trabajo-energia): `W_roz = (Ec_f - Ec_i) + m*g*(h_f - h_i)`
- Desaceleracion media: `a = |v_f - v_i| / dt`, y en multiplos de g: `a / g`
- Fuerza promedio de amerizaje: `F_prom = Ec / d + m*g`
- Ventana de reingreso: `5,5 <= gamma <= 7,0` grados. Si `gamma > 7,0` la desaceleracion es
  excesiva; si `gamma < 5,5` hay rebote atmosferico.

Valor de gravedad utilizado: **g = 9,81 m/s2** (la consigna no lo define para este escenario).

### Resultados con los datos de la consigna

| Calculo | Resultado |
|---|---|
| W_roz | -6,412 x 10^11 J |
| Desaceleracion media | 27,44 m/s2 (2,80 g) |
| F_prom | 323.891 N (3,17 veces el peso) |

## Estructura del proyecto

```
include/   cabeceras (.h): artemis.h, Interfaz.h, fisica.h, validaciones.h, calculadora.h
src/       codigo fuente (.c): main.c, artemis.c, Interfaz.c, fisica.c, validaciones.c, calculadora.c,
           interfaz_grafica.c (ventana opcional con raylib, programa aparte)
tests/     pruebas: test_fisica.c, test_validaciones.c
Makefile   compilacion
```

| Modulo | Responsabilidad |
|---|---|
| `main.c` | Solo `main()` y el menu principal |
| `artemis.h` / `artemis.c` | Constantes, tipos (`Mision`, `NodoMision`) y logica de la mision |
| `Interfaz.h` / `Interfaz.c` | Reglas y reporte del historial |
| `fisica.h` / `fisica.c` | Calculos fisicos puros (sin `printf` ni `scanf`) |
| `validaciones.h` / `validaciones.c` | Lectura segura de enteros, reales y opciones |
| `calculadora.h` / `calculadora.c` | Calculadora de analisis (puntos a, b, c y d) |

## Compilacion y ejecucion

Con `make` (requiere gcc):

```
make
./artemis
```

Pruebas (cada una tiene su propio `main`):

```
make test                 # pruebas de fisica   -> ./test_fisica
make test_validaciones    # pruebas de entradas -> ./test_validaciones
make clean                # borra objetos y ejecutables
```

Sin `make`, a mano:

```
gcc -Wall -Iinclude src/*.c -o artemis -lm
./artemis
```

En Windows (MinGW) el ejecutable se llama `artemis.exe`. El enlace con `-lm` es necesario
porque `fisica.c` usa `math.h` (`pow`, `fabs`).

## Interfaz grafica (opcional)

Ademas de la consola, el proyecto incluye una ventana de telemetria hecha con **raylib**
(`src/interfaz_grafica.c`). Es un programa aparte: muestra los datos de la mision y una
animacion de la nave. El juego sigue funcionando completo por consola si la ventana no existe.

Como se comunican: al terminar una mision, `jugar_mision` escribe el archivo
`datos_mision.txt` (masa, v_inicial, v_final, gamma, profundidad, v_impacto, delta_t). La ventana
lo lee cada 0,5 s, calcula con las funciones de `fisica.c`, muestra los resultados y borra el archivo.

Para usarla (requiere raylib instalada):

```
make grafica      # genera interfaz_grafica(.exe)
make              # genera artemis(.exe)
```

Ejecutar `artemis.exe` desde la misma carpeta: al iniciar la primera mision abre la ventana.

## Validaciones

Funciones disponibles: `leer_entero`, `leer_real`, `leer_opcion` y `esperar_enter`.
Toda entrada del usuario se lee con `fgets` y se convierte con `sscanf`, verificando su
retorno. Si el dato no es un numero o esta fuera de rango, se informa el error y se vuelve a
pedir, por lo que el programa no se cierra ni entra en un bucle infinito.

## Registro de uso de Inteligencia Artificial

| Herramienta | Para que se uso | Consultas principales | Como se valido |
|---|---|---|---|
| Claude (Anthropic) | Planificacion del proyecto, integracion de la ventana grafica con el juego, reparto de tareas, borrador de `main.c`, `calculadora.c`, `Makefile` y README, explicacion de Git/GitHub y revision del estado del repositorio | Arquitectura modular segun el material de la catedra; menu con do-while y switch; calculadora de los puntos a-d; como subir commits a una rama y abrir un Pull Request | Se compilo con `gcc -Wall -Wextra`, se probo con entradas validas e invalidas y se comparo con calculos hechos a mano |
| ChatGPT (OpenAI), utilizado por Juan Sebastian Noguera Vega | Revision e integracion de la logica de mision, correccion de cabeceras y funciones duplicadas, creacion de validaciones y ayuda con GitHub | Como conectar ejecutarMision con jugar_mision; corregir errores de compilacion; validar entradas; actualizar ramas e integrar cambios | Se compilo el ZIP con gcc -Wall y se ejecutaron pruebas de fisica y misiones con angulos de 4 grados, 6 grados y 8 grados, comprobando los resultados y el historial |

> Completar: cada integrante agrega aqui sus propias consultas a IA y como valido el resultado.
