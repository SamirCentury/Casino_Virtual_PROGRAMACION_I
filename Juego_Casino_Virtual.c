#include <stdio.h>
#include <stdbool.h>
void GestionarSaldo(int*saldo);
int main(){
    int opcion;
    int saldo = 0;
    bool continuar = true;


    do{
        //Mostrar el cartel de opciones
        printf("==========================================\n");
        printf("         BIENVENIDO AL CASINO             \n");
        printf("==========================================\n");
        printf("  === MENU GENERAL DEL CASINO ===\n");
        printf(" Saldo actual: $%d\n",saldo);
        printf("1. Jugar a la Ruleta\n");
        printf("2. Jugar al BlackJack\n");
        printf("3. Jugar al Poker\n");
        printf("4. Ver Saldo / Cargar Credito\n");
        printf("5. Salir del Casino\n");
        printf("==========================================\n");
        printf("Seleccione una opcion (1-5):");
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                printf("Entrando a la Ruleta...¡Hagan sus apuestas!\n");
                //Aca va la logica de la ruleta
                break;
            case 2:
                printf("Entrando al BlackJack...¿Carta o te plantas?\n");
                //Aca va la logica del BlackJack
                break;
            case 3:
                printf("Entrando al Poker...¡Suerte!\n");
                printf("\n");
                //Aca va la logica del poker
                if(saldo>=100){
                    //AnimacionBienvenida;
                    //MenuJuego(saldo); //pasamos el saldo global al menu
                }else{
                    printf("Saldo insuficiente. Tenes $%d\n",saldo,". Necesitas al menos $100 para jugar.");
                    printf("Por favor, carga credito (opcion 4)\n");
                }
                break;
            case 4:
                GestionarSaldo(&saldo);
                break;
            case 5:
                printf("Gracias por visitarnos. Te retiras con: $%d\n",saldo);
                printf("¡Vuelva pronto!\n");
                bool continuar = false;
                break;
            default:
                printf("Opcion no valida. Intente de nuevo");
                break;

                }
        }while(opcion!=5);


return 0;
}

//Inicio de la logica de Cargar Saldo/Fichas
void RealizarApuesta(int*saldo){
    int apuesta;
    printf("=====================================\n");
    printf("Tus fichas: %d\n",saldo);
    printf("=====================================\n");

    //Bucle de validacion
    do{
        printf("Ingresa el monto a apostar para esta mano\n");
        scanf("%d",&apuesta);

        if(apuesta <= 0){
            printf("La apuesta debe ser mayor a 0.\n");
        }

        if(apuesta > *saldo){
            printf("No podes apostar mas fichas de las que tenes.\n");
        }
    }while((apuesta<=0)||(apuesta>0));

    //El jugador pone su apuesta y  la casa pone el mismo en el pozo

    *saldo = *saldo - apuesta;
    int pozo = apuesta*2;

    printf("\n");
    printf("¡Apuesta aceptada!\n");
    printf("Apostaste: $%d\n",apuesta);
    printf("La casa igualo tu apuesta con: $%d\n",apuesta);
    printf("Pozo total en la mesa: $%d\n",pozo);
    printf("==============================================\n");
    printf("\n");


}

//funcion para consultar y recargar fichas/creditos
void GestionarSaldo(int*saldo){
    int opSaldo;
    int recarga = 0;

    do{
        printf("=======================================\n");
        printf("     GESTION DE SALDO Y CREDITO        \n");
        printf("=======================================\n");
        printf("Tu saldo disponible es: $%d\n",*saldo);
        printf("\n");
        printf("1. Cargar Credito\n");
        printf("2. Volver al Menu Principal\n");
        printf("=======================================\n");
        printf("Seleccione una opcion: %d\n",opSaldo);
        scanf("%d",&opSaldo);

        switch(opSaldo)
        {
            case 1:
                while(recarga < 100)
                    {
                        printf("Ingresa el monto a cargar (Minimo $100):\n");
                        scanf("%d",&recarga);
                        if (recarga < 100)
                            {
                            printf("La carga minima debe ser de al menos $100.\n");
                            }
                    }

               *saldo = *saldo + recarga;
               printf("");
               printf("¡Carga exitosa! Tu nuevo saldo es: $%d\n",*saldo);
               break;
            case 2:
                printf("Volviendo al menu principal...\n");
            default:
                printf("Por favor ingrese una opcion valida. Presiona ENTER\n");
            break;
        }


    }while (opSaldo != 2);

} //Fin de la logica de Cargar Fichas.
