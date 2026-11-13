# Casino Virtual - Programación I

Proyecto final desarrollado en lenguaje C que simula un casino virtual con los juegos de Blackjack, Póker y Ruleta.

## Archivos del proyecto final

Para compilar la versión final se utilizan únicamente los archivos del commit **"Proyecto Finalizado"**:
* `main.c` y `main.h`
* `ruleta.c` y `ruleta.h`
* `póker.c` y `póker.h`
* `blackjack.c` y `blackjack.h`


> **Nota:** Los demás archivos `.c` del repositorio corresponden a versiones anteriores o archivos independientes y no deben incluirse al compilar (no utilizar `gcc *.c`).

## Instrucciones de compilación y ejecución

Desde **Git Bash** o una terminal ubicada en la carpeta del proyecto, ejecuta:

```bash
gcc main.c ruleta.c póker.c blackjack.c -o juego.exe && ./juego.exe
```
