#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_COLORES 37

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
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > 6) {
        printf("Ingrese una opcion valida (1 a 6)\n");
    }
    return opcion;
}

float PedirApuesta(float saldoActual) {
    float monto;
    do {
        printf("Saldo disponible: $%.2f\n", saldoActual);
        printf("Ingrese monto a apostar: ");
        scanf("%f", &monto);
        if (monto <= 0) {
            printf("La apuesta debe ser mayor a 0\n");
        } else if (monto > saldoActual) {
            printf("No puedes apostar mas fichas de las que tienes\n");
        }
    } while (monto <= 0 || monto > saldoActual);
    return monto;
}

int PedirNumeroPleno(float *saldo) {
    int numeroElegido;

    do {
        printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija un numero (0 al 36): ");
        scanf("%d", &numeroElegido);
        if (numeroElegido < 0 || numeroElegido > 36) {
            printf("Numero fuera de rango\n");
        }
    } while (numeroElegido < 0 || numeroElegido > 36);
    return numeroElegido;
}

char PedirColor(float *saldo) {
    char colorElegido;

    do {
        printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija color ('R' para Rojo / 'N' para Negro): ");
        scanf(" %c", &colorElegido);
        if (colorElegido != 'r' && colorElegido != 'R' && colorElegido != 'n' && colorElegido != 'N') {
            printf("Ingrese solo 'R' o 'N'.\n");
        }
    } while (colorElegido != 'r' && colorElegido != 'R' && colorElegido != 'n' && colorElegido != 'N');

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
        printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija paridad (1: Par / 2: Impar): ");
        scanf("%d", &paridadElegida);
        if (paridadElegida != 1 && paridadElegida != 2) {
            printf("Ingrese 1 para Par o 2 para Impar\n");
        }
    } while (paridadElegida != 1 && paridadElegida != 2);
    return paridadElegida;
}

int PedirFaltaPasa(float *saldo) {
    int rangoElegido;

    do {
        printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija rango (1: Falta [1-18] / 2: Pasa [19-36]): ");
        scanf("%d", &rangoElegido);
        if (rangoElegido != 1 && rangoElegido != 2) {
            printf("Ingrese 1 para Falta o 2 para Pasa\n");
        }
    } while (rangoElegido != 1 && rangoElegido != 2);
    return rangoElegido;
}

int PedirDocena(float *saldo) {
    int docenaElegida;

    do {
        printf("Saldo en mesa: $%.2f\n", *saldo);
        printf("Elija la docena (1: 1-12 / 2: 13-24 / 3: 25-36): ");
        scanf("%d", &docenaElegida);
        if (docenaElegida < 1 || docenaElegida > 3) {
            printf("Ingrese un numero entre 1 y 3\n");
        }
    } while (docenaElegida < 1 || docenaElegida > 3);
    return docenaElegida;
}


void ResolverRonda(int tipo, float monto, float *saldo) {
    int numElegido = -1, paridadElegida = 0, rangoElegido = 0, docenaElegida = 0;
    char colElegido = ' ';

    // 1. Capturar pronóstico del jugador
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

    // 2. Giro y resultado
    int numeroSalio = rand() % NUM_COLORES;
    char colSalio = COLORES[numeroSalio];
    AnimarGiroRuleta(numeroSalio, colSalio);

    // 3. Evaluación de premios según la apuesta
    switch (tipo) {
        case 1: // Pleno (35:1)
            if (numElegido == numeroSalio) {
                float premio = monto * 35;
                printf("¡ACERTASTE EL PLENO! Ganaste $%.2f\n", premio);
                *saldo += premio;
            } else {
                printf("No hubo suerte. Perdiste $%.2f\n", monto);
                *saldo -= monto;
            }
            break;

        case 2: // Color (1:1) - Casilla 0 pierde
            if (numeroSalio != 0 && colElegido == colSalio) {
                printf("¡ACERTASTE EL COLOR! Ganaste $%.2f\n", monto);
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
                printf("¡ACERTASTE LA PARIDAD! Ganaste $%.2f\n", monto);
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
                printf("¡ACERTASTE EL RANGO! Ganaste $%.2f\n", monto);
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
                printf("¡ACERTASTE LA DOCENA! Ganaste $%.2f\n", premio);
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

    while (*saldo > 0 && (seguir == 'S' || seguir == 's')) {
        DibujarPanoRuleta();
        int tipo = MostrarMenuRuleta();

        if (tipo == 6) {
            break;
        }

        float monto = PedirApuesta(*saldo);

        ResolverRonda(tipo, monto, saldo);

        if (*saldo > 0) {
            printf("\n¿Desea jugar otra ronda en la Ruleta? (S/N): ");
            scanf(" %c", &seguir);
        } else {
            printf("\nTe quedaste sin fichas en la mesa\n");
            seguir = 'N';
        }
    }

    printf("\n==========================================\n");
    printf(" Te retiras de la Ruleta con: $%.2f\n", (float)*saldo);
    printf("==========================================\n");
}

int main(void) {
    float saldo = 1000.0f; // Saldo de prueba
    srand(time(NULL));

    JugarRuleta(&saldo);

    return 0;
}