#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_COLORES 37

const char COLORES[NUM_COLORES] = {
    'V',
    'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R'
};


int MostrarMenuRuleta(void) {
    int opcion;
    printf("\n==========================================\n");
    printf("         MESA DE RULETA EUROPEA           \n");
    printf("==========================================\n");
    printf("1. Apostar a Pleno (Numero exacto)      [35:1]\n");
    printf("2. Apostar a Color (Rojo o Negro)       [1:1]\n");
    printf("3. Apostar Par o Impar                  [Paga 1:1]\n");
    printf("4. Apostar Falta (1-18) / Pasa (19-36)  [Paga 1:1]\n");
    printf("5. Apostar Docenas (1-12, 13-24, 25-36) [Paga 2:1]\n");
    printf("6. Salir de la Ruleta\n");
    printf("==========================================\n");
    printf("Seleccione una opcion (1-6): ");
    scanf("%d", &opcion);
    return opcion;
}

int PedirApuesta(int saldoActual) {
    int monto;
    do {
        printf("Saldo disponible: $%d\n", saldoActual);
        printf("Ingrese monto a apostar: ");
        scanf("%d", &monto);
        if (monto <= 0) {
            printf("Error: La apuesta debe ser mayor a 0.\n");
        } else if (monto > saldoActual) {
            printf("Error: No puedes apostar mas fichas de las que tienes.\n");
        }
    } while (monto <= 0 || monto > saldoActual);
    return monto;
}

int GirarRuleta(void) {
    printf("\nGirando la ruleta...\n");
    return rand() % NUM_COLORES;
}

void JugarPleno(int *saldo) {
    int apuesta = PedirApuesta(*saldo);
    int numeroElegido;

    do {
        printf("Elija un numero (0 al 36): ");
        scanf("%d", &numeroElegido);
        if (numeroElegido < 0 || numeroElegido > 36) {
            printf("Error: Numero fuera de rango\n");
        }
    } while (numeroElegido < 0 || numeroElegido > 36);

    int numeroSalio = GirarRuleta();
    printf("-> Salio el numero: %d (Color: %c)\n", numeroSalio, COLORES[numeroSalio]);

    if (numeroElegido == numeroSalio) {
        int premio = apuesta * 35;
        printf("¡ACERTASTE EL PLENO! Ganaste $%d\n", premio);
        *saldo += premio;
    } else {
        printf("No hubo suerte. Perdiste $%d\n", apuesta);
        *saldo -= apuesta;
    }
}

void JugarColor(int *saldo) {
    int apuesta = PedirApuesta(*saldo);
    char colorElegido;

    do {
        printf("Elija color ('R' para Rojo / 'N' para Negro): ");
        scanf(" %c", &colorElegido);
        if (colorElegido != 'r' && colorElegido != 'R' && colorElegido != 'n' && colorElegido != 'N') {
            printf("Error: Ingrese solo 'R' o 'N'.\n");
        }
    } while (colorElegido != 'r' && colorElegido != 'R' && colorElegido != 'n' && colorElegido != 'N');

    if (colorElegido == 'r') {
        colorElegido = 'R';
    } else if (colorElegido == 'n') {
        colorElegido = 'N';
    }

    int numeroSalio = GirarRuleta();
    char colorSalio = COLORES[numeroSalio];
    printf("-> Salio el numero: %d (COLORRR: %c)\n", numeroSalio, colorSalio);

    // Si sale 0 (Verde) la casa gana y pierdes toda tu apuesta
    if (numeroSalio != 0 && colorElegido == colorSalio) {
        printf("¡ACERTASTE EL COLOR! Ganaste $%d\n", apuesta);
        *saldo += apuesta;
    } else {
        printf("Color incorrecto (o salio el 0). Perdiste $%d\n", apuesta);
        *saldo -= apuesta;
    }
}

void JugarParidad(int *saldo) {
    int apuesta = PedirApuesta(*saldo);
    int paridadElegida;

    do {
        printf("Elija paridad (1: Par / 2: Impar): ");
        scanf("%d", &paridadElegida);
        if (paridadElegida != 1 && paridadElegida != 2) {
            printf("Error: Ingrese 1 para Par o 2 para Impar.\n");
        }
    } while (paridadElegida != 1 && paridadElegida != 2);

    int numeroSalio = GirarRuleta();
    printf("-> Salio el numero: %d (Color: %c)\n", numeroSalio, COLORES[numeroSalio]);

    if (numeroSalio != 0 && ((paridadElegida == 1 && numeroSalio % 2 == 0) || (paridadElegida == 2 && numeroSalio % 2 != 0))) {
        printf("¡ACERTASTE LA PARIDAD! Ganaste $%d\n", apuesta);
        *saldo += apuesta;
    } else {
        printf("Paridad incorrecta (o salio el 0). Perdiste $%d\n", apuesta);
        *saldo -= apuesta;
    }
}

void JugarFaltaPasa(int *saldo) {
    int apuesta = PedirApuesta(*saldo);
    int rangoElegido;

    do {
        printf("Elija rango (1: Falta [1-18] / 2: Pasa [19-36]): ");
        scanf("%d", &rangoElegido);
        if (rangoElegido != 1 && rangoElegido != 2) {
            printf("Error: Ingrese 1 para Falta o 2 para Pasa.\n");
        }
    } while (rangoElegido != 1 && rangoElegido != 2);

    int numeroSalio = GirarRuleta();
    printf("-> Salio el numero: %d (Color: %c)\n", numeroSalio, COLORES[numeroSalio]);

    if (numeroSalio != 0 && ((rangoElegido == 1 && numeroSalio >= 1 && numeroSalio <= 18) || (rangoElegido == 2 && numeroSalio >= 19 && numeroSalio <= 36))) {
        printf("¡ACERTASTE EL RANGO! Ganaste $%d\n", apuesta);
        *saldo += apuesta;
    } else {
        printf("Rango incorrecto (o salio el 0). Perdiste $%d\n", apuesta);
        *saldo -= apuesta;
    }
}

void JugarDocenas(int *saldo) {
    int apuesta = PedirApuesta(*saldo);
    int docenaElegida;

    do {
        printf("Elija la docena (1: 1-12 / 2: 13-24 / 3: 25-36): ");
        scanf("%d", &docenaElegida);
        if (docenaElegida < 1 || docenaElegida > 3) {
            printf("Error: Ingrese un numero entre 1 y 3.\n");
        }
    } while (docenaElegida < 1 || docenaElegida > 3);

    int numeroSalio = GirarRuleta();
    printf("-> Salio el numero: %d (Color: %c)\n", numeroSalio, COLORES[numeroSalio]);

    if (numeroSalio != 0 && ((docenaElegida == 1 && numeroSalio >= 1 && numeroSalio <= 12) || (docenaElegida == 2 && numeroSalio >= 13 && numeroSalio <= 24) || (docenaElegida == 3 && numeroSalio >= 25 && numeroSalio <= 36))) {
        int premio = apuesta * 2;
        printf("¡ACERTASTE LA DOCENA! Ganaste $%d\n", premio);
        *saldo += premio;
    } else {
        printf("Docena incorrecta (o salio el 0). Perdiste $%d\n", apuesta);
        *saldo -= apuesta;
    }
}


int main(void) {
    int saldo = 1000; // Saldo de prueba
    int opcion;
    srand(time(NULL));

    do {
        if (saldo <= 0) {
            printf("\nTe has quedado sin fichas en la mesa.\n");
            break;
        }

        opcion = MostrarMenuRuleta();

        switch (opcion) {
            case 1:
                JugarPleno(&saldo);
                break;
            case 2:
                JugarColor(&saldo);
                break;
            case 3:
                JugarParidad(&saldo);
                break;
            case 4:
                JugarFaltaPasa(&saldo);
                break;
            case 5:
                JugarDocenas(&saldo);
                break;
            case 6:
                printf("Saliendo de la Ruleta. Te retiras con: $%d\n", saldo);
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}