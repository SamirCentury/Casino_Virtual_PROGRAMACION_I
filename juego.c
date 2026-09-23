#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Para que funcione la función esperar en cualquier sistema operativo
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define MAX_STRLEN 256

// Definición de la función esperar (convierte milisegundos)
void esperar(double t) {
#ifdef _WIN32
    Sleep((DWORD)t);
#else
    usleep((useconds_t)(t * 1000));
#endif
}

// Declaraciones adelantadas de las funciones
void tragamonedas(float saldo, bool continuar);
void cartel_tragamonedas();
void apuesta_invalida();
void slots_fortune();
void palanca_01();
void palanca_02();
void girando();
void iniciando(int rueda1, int rueda2, int rueda3);
void jackpot();
void sin_fichas();

int main() {
    // Inicializa la semilla para los números aleatorios reales
    srand((unsigned int)time(NULL)); 
    
    bool continuar = true;
    float saldo = 1000.0f;
    
    tragamonedas(saldo, continuar);
    return 0;
}

void tragamonedas(float saldo, bool continuar) {
    int apuesta;
    int i, s, opcion;
    int rueda1, rueda2, rueda3;
    char textosimbolos[MAX_STRLEN];

    while (saldo > 0 && continuar) {
        printf("\n\n"); 
        cartel_tragamonedas();
        
        printf(" Saldo Actual: [$%.2f]\n", saldo);
        printf(" Ingresa tu apuesta (Minimo $10): \n");
        if (scanf("%i", &apuesta) != 1) {
            // Limpieza de buffer en caso de que ingresen letras
            while (getchar() != '\n');
            continue;
        }

        if (apuesta > saldo || apuesta < 10) {
            apuesta_invalida();
            esperar(1500);
        } else {
            saldo = saldo - apuesta;
            
            // Animación de giro
            for (i = 1; i <= 5; ++i) {
                printf("\n\n");
                slots_fortune();
                if (i % 2 == 0) {
                    palanca_01();
                } else {
                    palanca_02();
                }
                girando();
                esperar(200);
            }

            // Generación aleatoria entre 1 y 4
            rueda1 = (rand() % 4) + 1;
            rueda2 = (rand() % 4) + 1;
            rueda3 = (rand() % 4) + 1;

            printf("\n\n");
            slots_fortune();
            iniciando(rueda1, rueda2, rueda3);

            // ==================== SECCIÓN DE SÍMBOLOS ENCAJADOS ====================
            // Corrección: Usamos strcpy para inicializar la cadena de forma segura en C
            strcpy(textosimbolos, "  Simbolos: ");

            // Concatenar el primer símbolo
            switch (rueda1) {
                case 1: strcat(textosimbolos, "[Crown] "); break;
                case 2: strcat(textosimbolos, "[Diamante] "); break;
                case 3: strcat(textosimbolos, "[Moneda] "); break;
                default: strcat(textosimbolos, "[Espada] "); break;
            }
            // Concatenar el segundo símbolo
            switch (rueda2) {
                case 1: strcat(textosimbolos, "[Crown] "); break;
                case 2: strcat(textosimbolos, "[Diamante] "); break;
                case 3: strcat(textosimbolos, "[Moneda] "); break;
                default: strcat(textosimbolos, "[Espada] "); break;
            }
            // Concatenar el tercer símbolo
            switch (rueda3) {
                case 1: strcat(textosimbolos, "[Crown]"); break;
                case 2: strcat(textosimbolos, "[Diamante]"); break;
                case 3: strcat(textosimbolos, "[Moneda]"); break;
                default: strcat(textosimbolos, "[Espada]"); break;
            }

            // Relleno matemático automático corregido
            while (strlen(textosimbolos) < 67) {
                strcat(textosimbolos, " ");
            }

            printf("      |%s|\n", textosimbolos);
            printf("      |___________________________________________________________________|\n\n");

            // ========================================================================
            // LÓGICA DE PREMIOS
            if (rueda1 == rueda2 && rueda2 == rueda3) {
                if (rueda1 == 1) {
                    jackpot();
                    saldo = saldo + (apuesta * 15);
                    for (s = 1; s <= 12; ++s) {
                        esperar(80);
                    }
                } else {
                    printf("  ¡Felicidades! Consiguiste 3 simbolos iguales. ¡Gran Premio!\n");
                    saldo = saldo + (apuesta * 5);
                    for (s = 1; s <= 5; ++s) {
                        esperar(150);
                    }
                }
            } else if (rueda1 == rueda2 || rueda2 == rueda3 || rueda1 == rueda3) {
                printf("  ¡Bien! 2 simbolos iguales. Duplicas tu apuesta.\n");
                saldo = saldo + (apuesta * 2);
                esperar(200);
            } else {
                printf("  No tuviste suerte esta vez. Los rodillos no coinciden.\n");
                esperar(500);
            }

            printf("==========================================================================\n");
            printf(" Nuevo saldo disponible: $%.2f\n", saldo);
            printf("==========================================================================\n");

            if (saldo >= 10) {
                printf(" 1. Seguir jugando.\n");
                printf(" 2. Volver al menu principal.\n");
                printf(" Seleccione una opcion: \n");
                scanf("%i", &opcion);
                switch (opcion) {
                    case 1:
                        continuar = true;
                        break;
                    case 2:
                        continuar = false;
                        printf(" ¡Gracias por jugar! Te retiras con: $%.2f\n", saldo);
                        while (getchar() != '\n'); // Limpiar buffer
                        getchar(); 
                        break;
                    default:
                        printf(" Opcion invalida, continuando juego por defecto...\n");
                        esperar(1000);
                }
            } else {
                sin_fichas();
                printf("Te has quedado sin saldo suficiente para la apuesta minima ($10).\n");
                printf("Vuelve al menu de inicio para recargar.\n");
                continuar = false;
                while (getchar() != '\n');
                getchar();
            }
        }
    }
}

// --- IMPLEMENTACIÓN DE FUNCIONES DE DISEÑO (Marcadores de posición estables) ---
void cartel_tragamonedas() {
    printf("==========================================================================\n");
    printf("                     🎰 CASINO TRAGAMONEDAS 🎰                            \n");
    printf("==========================================================================\n");
}
void slots_fortune() { printf("      ___________________________________________________________________\n"); }
void palanca_01() { printf("     |   [O]--| \n"); }
void palanca_02() { printf("     |     \\--| \n"); }
void girando() { printf("      |                   [ G I R A N D O ]                               |\n"); }
void iniciando(int r1, int r2, int r3) { printf("      |                     [ %i ]  [ %i ]  [ %i ]                        |\n", r1, r2, r3); }
void jackpot() { printf("  ¡¡¡ JACKPOT !!! ¡Multiplicas x15 tu apuesta!\n"); }
void apuesta_invalida() { printf(" ❌ Apuesta invalida. Debe ser mayor a $10 y menor/igual a tu saldo.\n"); }
void sin_fichas() { printf(" ❌ SIN FICHAS SUFICIENTES \n"); }
