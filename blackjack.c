#include <stdio.h>
#include <stdlib.h>
//-----------------REPARTO DE CARTAS--------------------------
int SacarCarta()
{
    return rand() % 11 + 1;
}
//------------------MANERAS DE GANARR---------------------
void MostrarGanador(int jugador, int crupier)
{
    if (jugador > 21)
    {
        printf("GANA EL CRUPIER\n");
    }
    else if (crupier > 21)
    {
        printf("GANA EL JUGADOR\n");
    }
    else if (jugador > crupier)
    {
        printf("GANA EL JUGADOR\n");
    }
    else if (crupier > jugador)
    {
        printf("GANA EL CRUPIER\n");
    }
    else
    {
        printf("EMPATE\n");
    }
}

int main()
{
    int op, opc;
    int jugador, crupier;

    do
    {
        printf("\n----- BLACKJACK -----\n");
        printf("1. Menu\n");
        printf("2. Reglas\n");
        printf("3. Jugar\n");
        printf("4. Salir\n");

        scanf("%d", &op);

        if (op == 2)
        {
            printf("\nREGLAS:\n");
            printf("1. Debes acercarte a 21.\n");
            printf("2. Si te pasas pierdes.\n");
            printf("3. El crupier roba hasta 17.\n");
            printf("4. Gana quien tenga mas puntos.\n");
        }

    } while (op == 1 || op == 2);

    switch (op)
    {
        case 3:

            jugador = 0;
            crupier = 0;

            jugador = jugador + SacarCarta();
            jugador = jugador + SacarCarta();

            crupier = crupier + SacarCarta();
            crupier = crupier + SacarCarta();

            printf("\nTus puntos: %d\n", jugador);
            printf("Puntos del crupier: %d\n", crupier);

            while (jugador < 21)
            {
                printf("\n1. Pedir carta\n");
                printf("2. Plantarse\n");

                scanf("%d", &opc);

                switch opc {

                    case 1:
                        jugador = jugador + SacarCarta();
                        printf("Ahora tienes %d puntos\n", jugador);
                    case 2:
                        aux_valor = jugador;
                }


            }

            while (crupier < 17)
            {
                crupier = crupier + SacarCarta();
            }

            printf("\nJugador: %d\n", jugador);
            printf("Crupier: %d\n", crupier);

            MostrarGanador(jugador, crupier);

            break;

        case 4:
            printf("Gracias por jugar\n");
            break;

        default:
            printf("Opcion invalida\n");
    }

    return 0;
}
