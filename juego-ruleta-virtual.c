#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_COLORES 37
#define MIN_APUESTA 500.0f

// Vector de colores oficial de la Ruleta Europea
// Casilla 0: 'V' (Verde) | 18 casillas 'R' (Rojo) | 18 casillas 'N' (Negro)
const char COLORES[NUM_COLORES] = {
    'V',
    'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R'
};

void MostrarBienvenida(void) {
    printf("\n==========================================\n");
    printf("            BIENVENIDOS AL                \n");
    printf("         JUEGO DE LA RULETA               \n");
    printf("==========================================\n");
}

void DibujarPanoRuleta(void) {
    printf("==========================================================================\n");
    printf("                         PANEL DE LA RULETA EUROPEA                       \n");
    printf("==========================================================================\n");
    printf("  +-----+---------------------------------------------------------------+\n");
    printf("  |     | [ 3R] [ 6N] [ 9R] [12R] [15N] [18R] [21R] [24N] [27R] [30R] [33N] [36R] |\n");
    printf("  |     |---------------------------------------------------------------|\n");
    printf("  | 0 V | [ 2N] [ 5R] [ 8N] [11N] [14R] [17N] [20N] [23R] [26N] [29N] [32R] [35N] |\n");
    printf("  |     |---------------------------------------------------------------|\n");
    printf("  |     | [ 1R] [ 4N] [ 7R] [10N] [13N] [16R] [19R] [22N] [25R] [28N] [31N] [34R] |\n");
    printf("  +-----+---------------------------------------------------------------+\n");
    printf("        |          1ra DOCENA           |          2da DOCENA           |          3ra DOCENA           |\n");
    printf("        |            (1 - 12)           |           (13 - 24)           |           (25 - 36)           |\n");
    printf("        +-------------------------------+-------------------------------+-------------------------------+\n");
    printf("        |    1 - 18     |      PAR      |     ROJO      |     NEGRO     |     IMPAR     |    19 - 36    |\n");
    printf("        +---------------+---------------+---------------+---------------+---------------+---------------+\n");
    printf("  Referencias: [R] = Rojo | [N] = Negro | [V] = Verde (0)\n");
    printf("==========================================================================\n");
}

void AnimarGiroRuleta(int numeroSalio, char colorSalio) {
    printf("\n           .---.          \n");
    printf("        .-/     /-.       \n");
    printf("       /   ( o )   /      Girando la rueda y lanzando la bola...\n");
    printf("      |   /     /   |     * clic * * clac * * clic *\n");
    printf("       /   ( o )   /      \n");
    printf("        .-/     /-.       \n");
    printf("           ---            \n");

    printf("\n      +-------------------------------------------+\n");
    printf("      |           ¡LA BOLA SE HA DETENIDO!        |\n");
    printf("      |                                           |\n");
    printf("      |             NUMERO GANADOR: [ %2d ]        |\n", numeroSalio);
    printf("      |                COLOR: [ %c ]                |\n", colorSalio);
    printf("      +-------------------------------------------+\n\n");
}

int MostrarMenuRuleta(void) {
    int opcion;
    do {
        printf("\n==========================================\n");
        printf("         MESA DE RULETA EUROPEA           \n");
        printf("==========================================\n");
        printf("1. Apostar a Pleno (Numero exacto)      [Paga 35:1]\n");
        printf("2. Apostar a Color (Rojo o Negro)       [Paga 1:1]\n");
        printf("3. Apostar Par o Impar                  [Paga 1:1]\n");
        printf("4. Apostar Falta (1-18) / Pasa (19-36)  [Paga 1:1]\n");
        printf("5. Apostar Docenas (1-12, 13-24, 25-36) [Paga 2:1]\n");
        printf("6. Salir de la Ruleta\n");
        printf("==========================================\n");
        printf("Seleccione una opcion (1-6): ");

        // Verifica si scanf no pudo leer un numero
        if (scanf("%d", &opcion) != 1) {
            // Entra aca si pusieron una letra
            printf("Entrada invalida. Por favor, ingrese un numero entre 1 y 6\n");
            while (getchar() != '\n'); // Limpia la letra que rompió el programa
            opcion = 0; // Fuerza a que repita el bucle
        } else if (opcion < 1 || opcion > 6) {
            printf("Ingrese una opcion valida (1 a 6)\n");
        }
    } while (opcion < 1 || opcion > 6);
    return opcion;
}

float PedirApuesta(float saldoActual) {
    float monto;
    do {
        printf("Saldo disponible: $%.2f\n", saldoActual);
        printf("Ingrese monto a apostar (minimo $%0.2f): ", MIN_APUESTA);
        
        if (scanf("%f", &monto) != 1) {
            printf("Entrada invalida\n");
            while (getchar() != '\n'); // Limpia la letra que rompio el programa
            monto = 0; 
        }
        else if (monto < MIN_APUESTA) {
            printf("La apuesta debe ser mayor o igual a $%0.2f\n", MIN_APUESTA);
        }
        else if (monto > saldoActual) {
            printf("No puedes apostar mas fichas de las que tienes\n");
        }

    } while (monto < MIN_APUESTA || monto > saldoActual);
    return monto;
}

int PedirNumeroPleno(float *saldo) {
    int numeroElegido;

    do {
        printf("Elija un numero (0 al 36): ");

        if (scanf("%d", &numeroElegido) != 1) {
            printf("Entrada invalida. Por favor, ingrese un numero\n");
            while (getchar() != '\n'); // Limpia la letra que rompio el programa
            numeroElegido = -1; 
        }
        else if (numeroElegido < 0 || numeroElegido > 36) {
            printf("Numero fuera de rango\n");
        }
    } while (numeroElegido < 0 || numeroElegido > 36);

    return numeroElegido;
}

char PedirColor(float *saldo) {
    char colorElegido;

    do {
        //printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija color ('R' para Rojo / 'N' para Negro): ");
        scanf(" %c", &colorElegido);

        // Verifica que el usuario ingrese R o N (mayuscula o minuscula)
        if (colorElegido != 'r' && colorElegido != 'R' && colorElegido != 'n' && colorElegido != 'N') {
            printf("Ingrese solo 'R' o 'N'.\n");
        }
    } while (colorElegido != 'r' && colorElegido != 'R' && colorElegido != 'n' && colorElegido != 'N');

    // Estandariza a mayusculas para facilitar las comprobaciones
    if (colorElegido == 'r') {
        colorElegido = 'R';
    } else if (colorElegido == 'n') {
        colorElegido = 'N';
    }
    return colorElegido;
}

int PedirParidad(float *saldo) {
    int paridadElegida;

    do {
        //printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija paridad (1: Par / 2: Impar): ");
        
        if (scanf("%d", &paridadElegida) != 1) {
            printf("Entrada invalida. Por favor, ingrese un numero\n");
            while (getchar() != '\n'); // Limpia la letra que rompio el programa
            paridadElegida = 0; 
        }
        else if (paridadElegida != 1 && paridadElegida != 2) {
            printf("Ingrese 1 para Par o 2 para Impar\n");
        }
    } while (paridadElegida != 1 && paridadElegida != 2);
    return paridadElegida;
}

int PedirFaltaPasa(float *saldo) {
    int rangoElegido;

    do {
        //printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija rango (1: Falta [1-18] / 2: Pasa [19-36]): ");
        if (scanf("%d", &rangoElegido) != 1) {
            printf("Entrada invalida. Por favor, ingrese un numero\n");
            while (getchar() != '\n'); // Limpia la letra que rompio el programa
            rangoElegido = 0;
        }
        else if (rangoElegido != 1 && rangoElegido != 2) {
            printf("Ingrese 1 para Falta o 2 para Pasa\n");
        }
    } while (rangoElegido != 1 && rangoElegido != 2);
    return rangoElegido;
}

int PedirDocena(float *saldo) {
    int docenaElegida;

    do {
        //printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija la docena (1: 1-12 / 2: 13-24 / 3: 25-36): ");
        if (scanf("%d", &docenaElegida) != 1) {
            printf("Entrada invalida. Por favor, ingrese un numero\n");
            while (getchar() != '\n'); // Limpia la letra que rompio el programa
            docenaElegida = 0;
        }
        else if (docenaElegida < 1 || docenaElegida > 3) {
            printf("Ingrese un numero entre 1 y 3\n");
        }
    } while (docenaElegida < 1 || docenaElegida > 3);
    return docenaElegida;
}


void ResolverRonda(int tipo, float monto, float *saldo) {
    // Variables para guardar lo que eligio el usuario segun el tipo de apuesta
    int numElegido = -1, paridadElegida = 0, rangoElegido = 0, docenaElegida = 0;
    char colElegido = ' ';

    // 1. Llama a la funcion correspondiente para pedirle el pronostico al jugador
    switch (tipo) {
        case 1:
            numElegido = PedirNumeroPleno(saldo);
            break;
        case 2:
            colElegido = PedirColor(saldo);
            break;
        case 3:
            paridadElegida = PedirParidad(saldo);
            break;
        case 4:
            rangoElegido = PedirFaltaPasa(saldo);
            break;
        case 5:
            docenaElegida = PedirDocena(saldo);
            break;
    }

    // 2. Genera el numero ganador al azar y busca de que color es
    int numeroSalio = rand() % NUM_COLORES;
    char colSalio = COLORES[numeroSalio];
    AnimarGiroRuleta(numeroSalio, colSalio);

    // 3. Evalua si el jugador gano o perdio segun el tipo de apuesta que hizo
    switch (tipo) {
        case 1: // Pleno (35:1)
            if (numElegido == numeroSalio) {
                float premio = monto * 35;
                printf("ACERTASTE EL PLENO! Ganaste $%.2f\n", premio);
                *saldo += premio;
            } else {
                printf("No hubo suerte. Perdiste $%.2f\n", monto);
                *saldo -= monto;
            }
            break;

        case 2: // Color (1:1) - Casilla 0 pierde
            if (numeroSalio != 0 && colElegido == colSalio) {
                printf("ACERTASTE EL COLOR! Ganaste $%.2f\n", monto);
                *saldo += monto;
            } else {
                printf("Color incorrecto (o salio el 0). Perdiste $%.2f\n", monto);
                *saldo -= monto;
            }
            break;

        case 3: // Par / Impar (1:1) - Casilla 0 pierde
            if (numeroSalio != 0 && (
                (paridadElegida == 1 && numeroSalio % 2 == 0) ||
                (paridadElegida == 2 && numeroSalio % 2 != 0))) {
                printf("ACERTASTE LA PARIDAD! Ganaste $%.2f\n", monto);
                *saldo += monto;
            } else {
                printf("Paridad incorrecta (o salio el 0). Perdiste $%.2f\n", monto);
                *saldo -= monto;
            }
            break;

        case 4: // Falta (1-18) / Pasa (19-36) (1:1) - Casilla 0 pierde
            if (numeroSalio != 0 && (
                (rangoElegido == 1 && numeroSalio >= 1 && numeroSalio <= 18) ||
                (rangoElegido == 2 && numeroSalio >= 19 && numeroSalio <= 36))) {
                printf("ACERTASTE EL RANGO! Ganaste $%.2f\n", monto);
                *saldo += monto;
            } else {
                printf("Rango incorrecto (o salio el 0). Perdiste $%.2f\n", monto);
                *saldo -= monto;
            }
            break;

        case 5: // Docenas (2:1) - Casilla 0 pierde
            if (numeroSalio != 0 && (
                (docenaElegida == 1 && numeroSalio >= 1 && numeroSalio <= 12) ||
                (docenaElegida == 2 && numeroSalio >= 13 && numeroSalio <= 24) ||
                (docenaElegida == 3 && numeroSalio >= 25 && numeroSalio <= 36))) {
                float premio = monto * 2;
                printf("ACERTASTE LA DOCENA! Ganaste $%.2f\n", premio);
                *saldo += premio;
            } else {
                printf("Docena incorrecta (o salio el 0). Perdiste $%.2f\n", monto);
                *saldo -= monto;
            }
            break;
    }
}

void JugarRuleta(float *saldo) {

    char seguir = 'S';

    MostrarBienvenida();

    // El juego continua mientras el jugador tenga el saldo minimo y quiera seguir
    while (*saldo >= MIN_APUESTA && (seguir == 'S' || seguir == 's')) {
        DibujarPanoRuleta();
        int tipo = MostrarMenuRuleta();

        if (tipo == 6) { // Opcion 6 es para salir del juego
            break;
        }

        float monto = PedirApuesta(*saldo);

        ResolverRonda(tipo, monto, saldo);

        // Si le queda dinero suficiente, le pregunta si quiere otra ronda
        if (*saldo >= MIN_APUESTA) {
            do {
                printf("\nDesea jugar otra ronda en la Ruleta? (S/N): ");
                scanf(" %c", &seguir);
                
                // Avisa si pone cualquier otra letra que no sea S o N
                if (seguir != 's' && seguir != 'S' && seguir != 'n' && seguir != 'N') {
                    printf("Opcion invalida. Ingrese 'S' para si, o 'N' para no.\n");
                }
            } while (seguir != 's' && seguir != 'S' && seguir != 'n' && seguir != 'N');
            
        } else {
            // Si el saldo baja del minimo, lo echa de la mesa
            printf("\nTe quedaste sin fichas suficientes en la mesa\n");
            seguir = 'N';
        }
    }

    printf("\n==========================================\n");
    printf(" Te retiras de la Ruleta con: $%.2f\n", *saldo);
    printf("==========================================\n");
}

int main(void) {
    float saldo = 2000.0f; // Saldo de prueba
    srand((unsigned int)time(NULL));

    JugarRuleta(&saldo); // Llama a la funcion principal que arranca el juego

    return 0;
}