#include <stdio.h> //Nos permite mostrar mensajes y leer datos
#include <stdlib.h> //Nos permite usar algunas funciones generales
#include <time.h> //Nos permite trabajar con el tiempo
#include "blackjack.h" //Incluye las declaraciones de nuestro juego
#include "main.h" //Nos permite usar la estructura Usuario del casino
#include "poker.h"

#define APUESTA_MINIMA_BLACKJACK 5000.0f

// Calcula los puntos de todas las cartas.
//Los Ases valen 1 u 11 segun convenga.

static int CalcularPuntosMano(int cartas[], int cantidad)
{
    int puntos = 0;
    int ases = 0;
    
    // Recorremos todas las cartas de la mano actual
    for (int i = 0; i < cantidad; i++)
    {
        puntos += cartas[i];

        // Si la carta es un As (representado con el valor 1), lo contamos
        if (cartas[i] == 1){
            ases++;
        }
    }

    // intentamos contar un As como 11 sin superar los 21
    while (ases > 0 && puntos + 10 <= 21){
        puntos += 10;
        ases--;
    }
    
    return puntos;

}

// Imprime de forma legible el nombre visual de la carta (As, J, Q, K o numero)
void ImprimirNombreCarta(int carta) {
    if (carta == 1) {
        printf("As");
    } else if (carta == 10) {
        printf("10");
    } else {
        printf("%d", carta);
    }
}

//Muestra reglas del juego
void ReglasBlackjack(void) {

    system("clear || cls");
    
    printf("\n" T_AMARILLO "╔════════════════════════════════════════════════════════════════╗\n");
    printf("║          " T_ROJO "♠ ♥ ♣ ♠" T_AMARILLO " REGLAS DEL BLACKJACK " T_ROJO "♠ ♣ ♦ ♥" T_AMARILLO "                  ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║  " T_CIAN "1." T_BLANCO " El objetivo es llegar a 21 puntos o acercarse.             ║\n");
    printf("║  " T_CIAN "2." T_BLANCO " Cada jugador y el crupier reciben dos cartas iniciales.    ║\n");
    printf("║  " T_CIAN "3." T_BLANCO " Podes pedir otra carta, plantarte o doblar tu apuesta.     ║\n");
    printf("║  " T_CIAN "4." T_BLANCO " Si superas los 21 puntos, perdes la ronda automáticamente. ║\n");
    printf("║  " T_CIAN "5." T_BLANCO " El As vale 11, pero pasa a valer 1 si es necesario.        ║\n");
    printf("║  " T_CIAN "6." T_BLANCO " El crupier está obligado a pedir cartas hasta llegar a 17. ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n" T_RESET);
    
    printf("\n        " T_CIAN ">>>> PRESIONA <<ENTER>> PARA VOLVER AL MENU <<<<\n" T_RESET);
    
    while(getchar() != '\n'); // Limpia búfer
    getchar();
   

    
}

// Genera una carta aleatoria (Valores del 1 al 13, figuras valen 10)
int RepartirCarta(void)
{
    int carta = rand() % 13 + 1;
    
    // J, Q, K valen 10 puntos
    if (carta >= 11){
        carta = 10;
    }

    //El As se representa con el valor 1
    return carta;
    
}

//Calcula los puntos de las cartas de las dos cartas iniciales
int CalcularPuntos(int carta1, int carta2){
    int cartas[2] = {carta1, carta2};

    return CalcularPuntosMano(cartas, 2);

}

// Controla el turno del crupier 
int TurnoCrupier(int cartaInicial1, int cartaInicial2){
    int cartas[22];
    int cantidad = 2;
    int puntos;
    
    // Reparte las dos cartas iniciales
    cartas[0] = cartaInicial1;
    cartas[1] = cartaInicial2;
    
    puntos = CalcularPuntosMano(cartas, cantidad);
    
    
    // Limpiamos pantalla y mostramos el inicio del turno del crupier
    system("clear || cls");
    printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
    printf("║             " T_ROJO "♠ ♣ TURNO DEL CRUPIER ♣ ♠" T_AMARILLO "                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n" T_RESET);
    
    printf("\n  " T_BLANCO "El crupier revela su carta oculta..." T_RESET "\n");
  
    // Mostramos las cartas del crupier descubiertas en 3D (esCrupier = 0 porque ya se revelan)
    MostrarCartasBlackJack(cartas, cantidad, "Crupier (Revelado)", 0);
    printf("  " T_CIAN "-> Puntos iniciales del crupier: " T_VERDE "%d" T_RESET "\n", puntos);
    Sleep(3000);
    
    // El crupier pide cartas hasta llegar a 17
    while (puntos < 17 && cantidad < 22) 
    {
        cartas[cantidad] = RepartirCarta();
        cantidad++;
        puntos = CalcularPuntosMano(cartas, cantidad);
        
        // Limpiamos y redibujamos la mano del crupier cada vez que toma una nueva carta
        system("clear || cls");
        printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║             " T_ROJO "♠ ♣ TURNO DEL CRUPIER ♣ ♠" T_AMARILLO "                     ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n" T_RESET);

        printf("\n  " T_BLANCO "El crupier pide carta..." T_RESET "\n");
        MostrarCartasBlackJack(cartas, cantidad, "Crupier (Pidiendo)", 0);
        printf("  " T_CIAN "-> Puntos actuales del crupier: " T_VERDE "%d" T_RESET "\n", puntos);
        Sleep(2500);
        
    }
    
    printf("\n  " T_AMARILLO "[!] El crupier termina con " T_VERDE "%d" T_AMARILLO " puntos." T_RESET "\n", puntos);
    Sleep(3000);
    
    return puntos;
    
    
}

// FLUJO PRINCIPAL DE UNA PARTIDA DE BLACKJACK CON FORMATO VIP
void IniciarPartida(Usuario_t *usuario)
{

    int jugarOtraMano = 1; //Variable de control para el bucle de "volver a jugar"

    do{
        int cartas[22];
        int cantidad = 2;
        int puntos;
        int opcion = 0;
        int PuntosCrupier;
        int resultado = 0;
        float apuesta;
        int puedeDoblar = 1;

        // El usuario realiza su apuesta
        apuesta = RealizarApuesta(
            &(usuario->saldo),
            APUESTA_MINIMA_BLACKJACK
        );
        
        //Si no pudo apostar, vuelve al menu
        if (apuesta == 0.0f){
            return;
        }
        
       system("clear || cls");
        printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║             " T_VERDE " 🪙 MESA DE BLACKJACK: NUEVA PARTIDA 🪙 " T_AMARILLO "        ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n" T_RESET);
        
        //Repartimos dos cartas al jugador
        cartas[0] = RepartirCarta();
        cartas[1] = RepartirCarta();

        //Repartimos 2 cartas al crupier
        int crupierCarta1 = RepartirCarta();
        int crupierCarta2 = RepartirCarta();
        
        // Sumamos el valor de las dos cartas
        puntos = CalcularPuntos(cartas[0], cartas[1]);
        
       // INTEGRACIÓN VISUAL 1: Mostramos la mesa con cartas 3D
        int manoCrupierAux[2] = {crupierCarta1, crupierCarta2};
        MostrarCartasBlackJack(manoCrupierAux, 2, "Crupier (Casa)", 1); // El '1' oculta la 2da carta
        MostrarCartasBlackJack(cartas, cantidad, usuario->usuario, 0);   // El '0' muestra tus cartas boca arriba
        printf("  " T_CIAN "-> Tus puntos actuales : " T_VERDE "%d" T_RESET "\n", puntos);


        if (puntos == 21) {
            printf("\n  " T_VERDE " ¡BLACKJACK! ¡Llegaste a 21 puntos exactos!" T_RESET "\n");
            Sleep(3000);
        }

        // Mientras el jugador no se plante y tenga 21 puntos o menos
        //turno del jugador
        while (puntos < 21 && cantidad < 22)
        {
            printf("\n" T_BLANCO "  [" T_CIAN "1" T_BLANCO "] Pedir otra carta\n");
            printf("  [" T_CIAN "2" T_BLANCO "] Plantarse\n");

            if (puntos >= 10 && puntos <= 11 && puedeDoblar == 1)
            {
                printf("  [" T_CIAN "3" T_BLANCO "] " T_AMARILLO "Doblar apuesta\n" T_RESET);
            }

            printf("Elegi una opcion: ");
            
            if (!LeerEnteroValido(&opcion)) {
                opcion = 0;
                
            }
            
            //Pedir otra carta
            if (opcion == 1)
            {
                //Repartimos una nueva carta
                cartas[cantidad] = RepartirCarta();
                
                // INTEGRACIÓN VISUAL: Limpiamos y redibujamos la mesa actualizada con la nueva carta
                system("clear || cls");
                printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
                printf("║             " T_VERDE " 🪙 MESA DE BLACKJACK: NUEVA PARTIDA 🪙 " T_AMARILLO "   ║\n");
                printf("╚═══════════════════════════════════════════════════════════╝\n" T_RESET);

                MostrarCartasBlackJack(manoCrupierAux, 2, "Crupier (Casa)", 1);
                MostrarCartasBlackJack(cartas, cantidad + 1, usuario->usuario, 0);

                cantidad++;
                puntos = CalcularPuntosMano(cartas, cantidad);
                
                printf("  " T_CIAN "-> Tus puntos actuales: " T_VERDE "%d" T_RESET "\n", puntos);
                
                //Si llegaste exacto a 21, pausamos para que lo disfrutes
                if (puntos == 21) {
                    printf("\n  " T_VERDE "[$$$] ¡Llegaste a 21 puntos exactos!" T_RESET "\n");
                    Sleep(3000);
                }


                //Si con esta carta te pasaste, pausamos para que ver la mano
                if (puntos > 21) {
                    printf("\n  " T_ROJO "[!] ¡Te pasaste de 21 puntos con esta carta!" T_RESET "\n");
                    Sleep(3000);
                }
            }
            else if (opcion == 2)
            {
                printf("\n  " T_VERDE "[✔] Te plantaste con %d puntos." T_RESET "\n", puntos);
                break;
            }
            else if (opcion == 3)
            {
                if (puntos >= 10 && puntos <= 11 && puedeDoblar == 1)
                {
                    //Vereficamos que tenga saldo suficiente 
                    if (usuario->saldo >= apuesta && cajaCasino >= apuesta)
                    {
                        usuario->saldo -= apuesta;
                        apuesta = apuesta * 2;
                        puedeDoblar = 0;

                        printf("\n  " T_AMARILLO "[$$] ¡Apuesta doblada con éxito!" T_RESET "\n");
                        printf("  Nuevo pozo en juego : " T_AMARILLO "$%.2f" T_RESET "\n", apuesta);

                        // Al doblar, recibe una ultima carta 
                        cartas[cantidad] = RepartirCarta();
                        
                        // INTEGRACIÓN VISUAL: Redibujamos la mesa tras doblar
                        system("clear || cls");
                        printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
                        printf("║             " T_VERDE " 🪙 MESA DE BLACKJACK: NUEVA PARTIDA 🪙 " T_AMARILLO "   ║\n");
                        printf("╚═══════════════════════════════════════════════════════════╝\n" T_RESET);

                        cantidad++;
                        puntos = CalcularPuntosMano(cartas, cantidad);
                        
                        printf("  Puntos finales      : " T_VERDE "%d" T_RESET "\n", puntos);
                        
                        //Despues de doblar, termina el turno del jugador
                        break;

                    }
                    else 
                    {
                        printf("\n  " T_ROJO "[X] No tenés saldo suficiente o la banca no puede respadar el doble." T_RESET "\n");
                    }
                }
                else 
                {
                    printf("\n  " T_ROJO "[X] No podés doblar en este momento." T_RESET "\n");
        
                }
            }
            else
            {
                printf("  " T_ROJO "[X] Opción inválida." T_RESET "\n");
            }
        }
        

        //Si el jugador no se paso de 21, juega el crupier
        if(puntos <= 21){
            PuntosCrupier = TurnoCrupier(crupierCarta1, crupierCarta2);
        }else{
            PuntosCrupier = 0; //Se paso, no hace falta que juegue el crupier
        }
        
        // Pantalla final con el resultado de la ronda
        system("clear || cls");
        printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║             🏆 RESULTADO FINAL - BLACKJACK 🏆             ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n" T_RESET);
        
        // Comprobamos el resultado de la partida
        if (puntos > 21)
        {
            printf("  " T_ROJO "[-] Te pasaste de 21. Perdiste la ronda." T_RESET "\n");
            resultado = -1;
            
        } 
        else if (puntos == 21 && cantidad == 2)
        {
           printf("  " T_VERDE "[$$$] ¡BLACKJACK! Llegaste a 21 con dos cartas. ¡Ganaste!" T_RESET "\n");
           resultado = 1;    
        }
        else if (PuntosCrupier > 21)
        {
            printf("  " T_VERDE "[$$$] ¡El crupier se pasó de 21! ¡Ganaste la partida!" T_RESET "\n");
            resultado = 1;
            
        }
        else if (puntos > PuntosCrupier)
        {
            printf("  " T_VERDE "[$$$] ¡Tus puntos superan al crupier! ¡Ganaste!" T_RESET "\n");
            resultado = 1;
        
        } else if (puntos == PuntosCrupier)
        {
            printf("  " T_AMARILLO "[=] La partida terminó en empate." T_RESET "\n");
            resultado = 0;
        } else 
        {
            printf("  " T_ROJO "[-] El crupier ganó la partida." T_RESET "\n");
            resultado = -1;
        }
        

        //Actualizacion contable sincronizadas (Saldo personal, Caja del casino y Ganancia de Admin)
        if(resultado == 1){
            usuario->saldo += apuesta * 2;
            
            ActualizarCajaCasino(&cajaCasino, apuesta, 1);
            usuario->gananciaAdmin -= apuesta;
            
            printf("  " T_VERDE "Premio acreditado : $" T_AMARILLO "%.2f" T_RESET "\n", apuesta * 2);
            
        } else if (resultado == -1) {
            //Control contable para evitar el dpoble conteo del deposito inicial
            if(usuario->dineroDepositado >= apuesta){
                //Si pierde plata de su deposito inicial, la caja NO suma
                //porque ese efectivo ya habia ingresadp al cargar saldo
                usuario->dineroDepositado -= apuesta;
            }else{
                //Si ya gasto su depossito y esta perdiendo ganancias que la casa le pago
                //la caja SI recupera ese efectivo exacto
                float diferenciaGanancia = apuesta - usuario->dineroDepositado;
                usuario->dineroDepositado = 0;
                ActualizarCajaCasino(&cajaCasino, diferenciaGanancia, -1);
            }

            usuario->gananciaAdmin += apuesta;
            
            printf("  " T_ROJO "Fichas perdidas   : $" T_ROJO "%.2f" T_RESET "\n", apuesta);
            
        } else {
            //En caso de empate, devolvemos la apuesta
            usuario->saldo += apuesta;
            printf("  " T_AMARILLO "Se devuelve tu apuesta intacta por empate." T_RESET "\n");
            
        }
        
        printf("  " T_CIAN "Saldo actual      : " T_VERDE "$%.2f" T_RESET "\n", usuario->saldo);
        printf(T_AMARILLO "═══════════════════════════════════════════════════════════" T_RESET "\n");
        

        printf("\n  " T_BLANCO "Presiona ENTER para continuar..." T_RESET);
        fflush(stdin); // Limpia cualquier residuo en el búfer
        getchar();     // Pausa la ejecución hasta que toques la tecla Enter

        //Validacion para preguntar si desea jugar otra mano si le alcanza el saldo de la mesa
        if(usuario->saldo >= APUESTA_MINIMA_BLACKJACK){

            // Limpiamos cualquier residuo en el búfer antes de leer la opción de repetir
            fflush(stdin);


            do{
                printf("\n" T_BLANCO "¿Querés jugar otra mano de BlackJack? (" T_VERDE "1. Sí" T_BLANCO " / " T_ROJO "2. No" T_BLANCO "): " T_RESET);
                if(!LeerEnteroValido(&jugarOtraMano)){
                    jugarOtraMano = 0;
                }
                if(jugarOtraMano !=1 && jugarOtraMano !=2){
                    printf(T_ROJO "[X] Error: Ingrese 1 para Sí o 2 para No." T_RESET "\n");
                }
            }while (jugarOtraMano !=1 && jugarOtraMano !=2);
        }else{
            printf("\n" T_ROJO "[!] Tu saldo es menor a la apuesta mínima. Regresando al menú..." T_RESET "\n");
            printf("\n" T_BLANCO "Presiona ENTER para regresar al menu..." T_RESET "\n");
            getchar();
            jugarOtraMano = 2; //Fuerza la salida al menu principal si se queda sin fondos suficientes
        }

        
    }while(jugarOtraMano == 1);
}


 //Menu principal del Blackjack

void MenuJuegoBlackjack(Usuario_t *usuario) {

     int opcion = 0;
        

     do 
     {
         //Mostramos las opciones del menu
        system("clear || cls");
        printf("\n" T_AMARILLO "╔═════════════════════════════════════════════════╗\n");
        printf("║         " T_ROJO " ♠ ♥ SALON DE BLACKJACK VIP ♦ ♣ " T_AMARILLO "        ║\n");
        printf("╠═════════════════════════════════════════════════╣\n");
        printf(T_AMARILLO "║ " T_VERDE "Balance del Jugador : " T_AMARILLO "$%-22.2f " T_AMARILLO "  ║\n", usuario->saldo); 
        printf("╠═════════════════════════════════════════════════╣\n");
        printf("║                                                 ║\n");
        printf("║   " T_CIAN "[%d]" T_BLANCO " 🎰 ENTRAR A LA MESA (JUGAR)               " T_AMARILLO "║\n", OPC_JUGAR_BLACKJACK);
        printf("║   " T_CIAN "[%d]" T_BLANCO " 📜 CONSULTAR REGLAS                       " T_AMARILLO "║\n", OPC_REGLAS_BLACKJACK);
        printf("║   " T_CIAN "[%d]" T_ROJO " 🚪 RETIRARSE DEL SALON                    " T_AMARILLO "║\n", OPC_SALIR_MENU_BLACKJACK);
        printf("║                                                 ║\n");
        printf("╚═════════════════════════════════════════════════╝" T_RESET "\n");
        printf(" Ingrese su opción: ");

         if (!LeerEnteroValido(&opcion)){
             opcion = 0;
        }



         switch (opcion)
         {
            case OPC_JUGAR_BLACKJACK:
                // Iniciamos una nueva partida
                IniciarPartida(usuario);
                break;
            case OPC_REGLAS_BLACKJACK: 
                // Mostrar las reglas del juego 
                 ReglasBlackjack();
                break;
            case OPC_SALIR_MENU_BLACKJACK:
                printf("\n" T_VERDE "Saliendo del módulo de BlackJack..." T_RESET "\n");
                Sleep(1000);
                break;

            default:
                printf("\n" T_ROJO "[X] Opción inválida. Intente nuevamente." T_RESET "\n");
                Sleep(1500);

        }

    } while (opcion != OPC_SALIR_MENU_BLACKJACK);
    
}

//IMPRESION VISUAL VIP DE CARTAS PARA BLACKJACK (Cartas 3D en linea)

void MostrarCartasBlackJack(int cartas[], int cantidad, const char *nombreJugador, int esCrupier){
    const char *simbolosPalos[] = {"♥", "♦", "♣", "♠"};

    printf("\n" T_AMARILLO "═══════════════════════════════════════════════════════════" T_RESET "\n");
    printf("  " T_VERDE "MESA VIP: %-15s" T_RESET "\n", nombreJugador);
    printf(T_AMARILLO "═══════════════════════════════════════════════════════════" T_RESET "\n\n");

    //1. Borde Superior de las cartas 
    for(int i=0; i < cantidad; i++){
        printf(T_AMARILLO "╔═══════╗" T_RESET " ");
    }
    printf("\n");

    // 2. Esquina Superior Izquierda (Número / Figura / Oculta)
    for(int i = 0; i < cantidad; i++){
        if (esCrupier && i == 1) { // Carta oculta del crupier
            printf(T_AMARILLO "║" T_ROJO " 🂠 ░░  " T_AMARILLO "║" T_RESET " ");
        } else {
            char valStr[3];
            if(cartas[i] == 1) strcpy(valStr, "A ");
            else if(cartas[i] == 10) strcpy(valStr, "10"); // J, Q, K y 10
            else sprintf(valStr, "%-2d", cartas[i]);

            printf(T_AMARILLO "║" T_RESET " " T_BLANCO "%-2s" T_RESET "    " T_AMARILLO "║" T_RESET " ", valStr);
        }
    }
    printf("\n");

    // 3. Centro de la Carta (Simbolo de palo o trama oculta)
    for(int i = 0; i < cantidad; i++){
        if (esCrupier && i == 1) {
            printf(T_AMARILLO "║" T_ROJO " ░░░░░ " T_AMARILLO "║" T_RESET " ");
        } else {
            // Asignamos palo visual aleatorio para la animación (o fijo según carta)
            printf(T_AMARILLO "║" T_RESET "   " T_ROJO "♥" T_RESET "   " T_AMARILLO "║" T_RESET " ");
        }
    }
    printf("\n");

    // 4. Esquina Inferior Derecha (Número invertido)
    for(int i = 0; i < cantidad; i++){
        if (esCrupier && i == 1) {
            printf(T_AMARILLO "║" T_ROJO "  ░░ 🂠 " T_AMARILLO "║" T_RESET " ");
        } else {
            char valStr[3];
            if(cartas[i] == 1) strcpy(valStr, " A");
            else if(cartas[i] == 10) strcpy(valStr, "10");
            else sprintf(valStr, "%2d", cartas[i]);

            printf(T_AMARILLO "║" T_RESET "    " T_BLANCO "%2s" T_RESET " " T_AMARILLO "║" T_RESET " ", valStr);
        }
    }
    printf("\n");

    // 5. Borde Inferior de la Carta
    for(int i = 0; i < cantidad; i++) {
        printf(T_AMARILLO "╚═══════╝" T_RESET " ");
    }
    printf("\n" T_AMARILLO "───────────────────────────────────────────────────────────" T_RESET "\n");
}