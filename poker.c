#include "poker.h"
#include <string.h>
#include <windows.h>


//Arreglo constante global para imprimir el texto del palo segun su indice (0 a 3)
const char *NOMBRES_PALOS[] = {"Corazones", "Diamantes", "Treboles", "Picas"};

const char *NOMBRES_JUGADAS[] = {
    "Carta Alta", "Par", "Doble Par", "Trio",
    "Escalera", "Color", "Full House", "Poker", "Escalera de Color"
};



//=============================================================
//   FUNCIONES BASE DEL MAZO
//=============================================================

//Menu completo del poker
void MenuJuegoPoker(Usuario_t *usuario){
    int opcionSubMenu = 0;
    do{
        system("clear || cls");
        
       // Cabecera estilizada del Salón de Póker (Usando macros de color)
        printf("\n" T_AMARILLO "╔═════════════════════════════════════════════════╗\n");
        printf("║         " T_ROJO " ♠ ♥ SALON DE POKER VIP ♦ ♣ " T_AMARILLO "            ║\n");
        printf("╠═════════════════════════════════════════════════╣" T_RESET "\n");
        printf(T_AMARILLO "║ " T_VERDE "Balance del Jugador : " T_AMARILLO "$%-22.2f " T_AMARILLO "  ║\n", usuario->saldo); 
        printf(T_AMARILLO "╠═════════════════════════════════════════════════╣" T_RESET "\n");
        printf(T_AMARILLO "║                                                 ║\n");
        printf("║   " T_CIAN "[%d]" T_BLANCO " 🎰 ENTRAR A LA MESA (JUGAR)               " T_AMARILLO "║\n", OPC_JUGAR_POKER);
        printf("║   " T_CIAN "[%d]" T_BLANCO " 📜 CONSULTAR REGLAS                       " T_AMARILLO "║\n", OPC_REGLAS_POKER);
        printf("║   " T_CIAN "[%d]" T_ROJO " 🚪 RETIRARSE DEL SALON                    " T_AMARILLO "║\n", OPC_SALIR_MENU_POKER);
        printf("║                                                 ║\n");
        printf("╚═════════════════════════════════════════════════╝" T_RESET "\n");
        printf(" Ingrese su opción: ");

        if(!LeerEnteroValido(&opcionSubMenu)){
            opcionSubMenu = 0; //Forzamos 0 para ir al default del switch
        }

        switch(opcionSubMenu){
        case OPC_JUGAR_POKER:
            JugarPartidaPoker(usuario);
            break;
        case OPC_REGLAS_POKER:
            ReglasDelPoker();
            break;
        case OPC_SALIR_MENU_POKER:
            printf("\n\033[1;32mSaliendo del modulo de Poker...\033[0m\n");
            Sleep(1000);
            break;
        default:
            printf("\n\033[1;31m[X] Opcion invalida. Por favor, ingrese un numero valido (1, 2 o 3).\033[0m\n");
            printf("Presione ENTER para continuar...");
            break;

            }
      }while(opcionSubMenu != OPC_SALIR_MENU_POKER);
}

// ============================================================================
// REGLAS DEL PÓKER (Versión Estilizada Pro con tus Macros)
// ============================================================================
void ReglasDelPoker(){
    system("clear || cls");
    
    printf("\n" T_AMARILLO "╔════════════════════════════════════════════════════════════════╗\n");
    printf("║          " T_ROJO "♥ ♦ ♣ ♠" T_AMARILLO " REGLAS DEL 5 CARD DRAW " T_ROJO "♠ ♣ ♦ ♥" T_AMARILLO "                ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║  " T_CIAN "1." T_BLANCO " Cada jugador recibe 5 cartas de un mazo de 52.             ║\n");
    printf("║  " T_CIAN "2." T_BLANCO " Podes cambiar de 0 a 5 cartas en la fase de descarte.      ║\n");
    printf("║  " T_CIAN "3." T_BLANCO " Gana la mano quien forme la combinacion de mayor jerarquia:║\n");
    printf("║                                                                ║\n");
    printf("║     - " T_VERDE "Escalera Real" T_BLANCO "       (10, J, Q, K, As del mismo palo)     ║\n");
    printf("║     - " T_VERDE "Escalera de Color" T_BLANCO "   (5 cartas consecutivas del mismo)    ║\n");
    printf("║     - " T_VERDE "Poker" T_BLANCO "               (4 cartas con el mismo valor)        ║\n");
    printf("║     - " T_VERDE "Full House" T_BLANCO "          (Un Trio + Un Par)                   ║\n");
    printf("║     - " T_VERDE "Color" T_BLANCO "               (5 cartas del mismo palo)            ║\n");
    printf("║     - " T_VERDE "Escalera" T_BLANCO "           (5 cartas de valores consecutivos)    ║\n");
    printf("║     - " T_VERDE "Trio" T_BLANCO "               (3 cartas con el mismo valor)         ║\n");
    printf("║     - " T_VERDE "Doble Par" T_BLANCO "          (Dos pares de cartas iguales)         ║\n");
    printf("║     - " T_VERDE "Par" T_BLANCO "               (Dos cartas con el mismo valor)        ║\n");
    printf("║     - " T_VERDE "Carta Alta" T_BLANCO "          (Valor de la carta mas alta)         ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n" T_RESET);
    
    printf("\n        " T_CIAN ">>>> PRESIONA <<ENTER>> PARA VOLVER AL MENU <<<<\n" T_RESET);
    
    while(getchar() != '\n'); // Limpia el buffer de forma segura
    getchar(); // Espera a que el usuario presione Enter
}



// Carga las 52 cartas del mazo en orden (4 palos x 13 valores)
void InicializarMazo(Carta_t mazo[]){
    int posicion = 0;

    //Bucle para recorrer los 4 palos
    for (int p=0; p<4; p++){
       //Bucle para recorrer los 13 valores de cada palo
       for(int v=1; v<=13; v++){
            mazo[posicion].palo = p; // Guardamos el palo
            mazo[posicion].valor = v; //Guardamos el valor
            posicion++;               //Avanzamos al siguiente casillero del mazo
        }
    }
}

// Mezcla las 52 cartas cambiando las posiciones al azar
void MezclarMazo(Carta_t mazo[]){
    for(int i=0; i<52; i++){
            //Genera un indice aleatorio entre 0 y 51
            int r = rand() % 52;


            //Intercambio clasico de variables usando una auxiliar
            Carta_t temp = mazo[i];
            mazo[i] = mazo[r];
            mazo[r] = temp;
        }
}


//Imprime las cartas de la mano indicando el numero de seleccion [1] al [5]
//Impresion de cartas con formato 3D y paño de casino
void MostrarMano(Carta_t mano[], int cantidad, const char *nombreJugador){
    //Palos Unicode con colores reales
    const char *simbolosPalos[] = {"♥", "♦", "♣", "♠"};

    // Encabezado estilizado de la mesa
    printf("\n" T_AMARILLO "═══════════════════════════════════════════════════════════" T_RESET "\n");
    printf("  " T_VERDE "MESA VIP: Mano de %-15s" T_RESET "                 \n", nombreJugador);
    printf(T_AMARILLO "═══════════════════════════════════════════════════════════" T_RESET "\n\n");
    
   // 1. Números de selección (Índices para el descarte)
    for(int i = 0; i < cantidad; i++){
        printf("   " T_CIAN "[%d]" T_RESET "     ", i + 1);
    }
    printf("\n");

    // 2. Borde Superior de la carta (Enmarcado en Amarillo VIP)
    for(int i = 0; i < cantidad; i++) {
        printf(T_AMARILLO "╔═══════╗" T_RESET " ");
    }
    printf("\n");

    // 3. Esquina Superior Izquierda (Número/Figura)
    for(int i = 0; i < cantidad; i++){
        int esRojo = (mano[i].palo == 0 || mano[i].palo == 1);
        char *col = esRojo ? T_ROJO : T_BLANCO;

        char valStr[3];
        if(mano[i].valor == 1) strcpy(valStr, "A ");
        else if(mano[i].valor == 11) strcpy(valStr, "J ");
        else if(mano[i].valor == 12) strcpy(valStr, "Q ");
        else if(mano[i].valor == 13) strcpy(valStr, "K ");
        else sprintf(valStr, "%-2d", mano[i].valor);

        printf(T_AMARILLO "║" T_RESET " %s%-2s" T_RESET "    " T_AMARILLO "║" T_RESET " ", col, valStr);
    }
    printf("\n");

    // 4. Centro de la Carta (Palo unicode gigante)
    for(int i = 0; i < cantidad; i++){
        int esRojo = (mano[i].palo == 0 || mano[i].palo == 1);
        char *col = esRojo ? T_ROJO : T_BLANCO;

        printf(T_AMARILLO "║" T_RESET "   %s%s" T_RESET "   " T_AMARILLO "║" T_RESET " ", col, simbolosPalos[mano[i].palo]);
    }
    printf("\n");

    // 5. Esquina Inferior Derecha (Número/Figura invertido)
    for(int i = 0; i < cantidad; i++){
        int esRojo = (mano[i].palo == 0 || mano[i].palo == 1);
        char *col = esRojo ? T_ROJO : T_BLANCO;

        char valStr[3];
        if(mano[i].valor == 1) strcpy(valStr, " A");
        else if(mano[i].valor == 11) strcpy(valStr, " J");
        else if(mano[i].valor == 12) strcpy(valStr, " Q");
        else if(mano[i].valor == 13) strcpy(valStr, " K");
        else sprintf(valStr, "%2d", mano[i].valor);

        printf(T_AMARILLO "║" T_RESET "    %s%2s" T_RESET " " T_AMARILLO "║" T_RESET " ", col, valStr);
    }
    printf("\n");

    // 6. Borde Inferior de la Carta
    for(int i = 0; i < cantidad; i++) {
        printf(T_AMARILLO "╚═══════╝" T_RESET " ");
    }
    printf("\n" T_AMARILLO "───────────────────────────────────────────────────────────" T_RESET "\n");
}



//Reparte 5 cartas seguidas sacandolas del mazo activo
//Subproceso para repartir 5 cartas a una mano
void RepartirMano(Carta_t mazo[], Carta_t mano[], int *posicionMazo){
    for (int i=0;i<5;i++){
        //Le asignamos la carta actual del mazo a la mano
        mano[i] = mazo[*posicionMazo];

        //Avanzamos el contador del mazo para no repetir cartas
        (*posicionMazo)++;
        }

        //*posicionMazo: es un puntero que lleva la cuenta de cual es la siguiente
        //carta disponible en el mazo (arranca en 0). Cada vez que entregamos una carta
        //incrementamos la posicionpara que la siguiente carta salga de mas abajo
}
//Permite al usuario seleccionar cuantas y cuales cartas reemplazar de su mano
void DescartarJugador(Carta_t mano[], Carta_t mazo[], int *posicionMazo){
    int cantidad, posicionCarta;
    //Arreglo auxiliar para registrar posiciones (0 a 4) ya se marcaron para cambio
    //Inicializado en 0

    int posicionesCambiadas[5] = {0};

    printf("\n" T_CIAN "╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                 🂠 FASE DE DESCARTE Y CAMBIO               ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝" T_RESET "\n");

    do{
        printf(T_BLANCO "¿Cuántas cartas querés cambiar? " T_AMARILLO "(0 a 5)" T_BLANCO ": " T_RESET);

        if(!LeerEnteroValido(&cantidad)){
            cantidad = -1;
        }

        if((cantidad < 0)||(cantidad > 5)){
            printf(T_ROJO "[X] Error: Ingrese un número válido entre 0 y 5." T_RESET "\n");
        }
    }while ((cantidad < 0)||(cantidad > 5));


    if(cantidad == 0){
        printf("\n" T_VERDE "[✔] Decidiste mantener toda tu mano intacta. ¡Buena suerte!" T_RESET "\n");
        Sleep(1000);
        return;
    }

    //Si el usuario elige 5, cambiamos toda la mano de forma automatica de una vez
    if(cantidad == 5){
        for(int i=0; i<5; i++){
            mano[i] = mazo[*posicionMazo];
            (*posicionMazo)++;
        }
        printf("\n" T_VERDE "[✔] ¡Has descartado las 5 cartas! Nuevas cartas repartidas con éxito." T_RESET "\n");
        Sleep(1000);
        return;
    }

    //Preguntamos las posiciones (solo si elige de 1 a 4)
    for (int i=0; i<cantidad; i++){
        do{
            printf(T_BLANCO "Ingrese la posición de la carta " T_CIAN "#%d" T_BLANCO " a cambiar " T_AMARILLO "(1 a 5)" T_BLANCO ": " T_RESET, i + 1);

            if(!LeerEnteroValido(&posicionCarta)){
                posicionCarta = -1;
            }


            if((posicionCarta < 1)||(posicionCarta > 5)){
                printf(T_ROJO "[X] Error: Carta inválida. Elija entre 1 y 5." T_RESET "\n");
            }
             //Validacion: Control de duplicados (verifica si el casillero ya se uso)
             else if(posicionesCambiadas[posicionCarta - 1] == 1){
                printf(T_ROJO "[X] Error: Ya pediste cambiar la carta de la posición %d. Elija otra." T_RESET "\n", posicionCarta);
                posicionCarta = -1; // Forzamos repetir la consulta
             }


        }while((posicionCarta < 1)||(posicionCarta > 5));

        // Marcamos la posicion elegida como ocupada (se resta 1 por el indice 0 de C)
        posicionesCambiadas[posicionCarta - 1] = 1;

        // Reemplazamos la carta actual por la siguiente carta activa del mazo
        mano[posicionCarta - 1] = mazo[*posicionMazo];

        // Incrementamos el puntero global para avanzar a la siguiente carta del mazo
        (*posicionMazo)++;
    }

    printf("\n" T_VERDE "[✔] Cartas reemplazadas con éxito por el crupier." T_RESET "\n");
    Sleep(1000);
}

//Prototipo para la rutina de descarte de la maquina
void DescartarMaquina(Carta_t mano[], Carta_t mazo[], int *posicionMazo){
    int repetidas[5] = {0}; //Arreglo auxiliar para marcar que cartas guardar (1=guardar, 0=descartar)
    int descartes = 0;      //Contador de cuantas cartas va a cambiar

    printf("\n" T_AMARILLO "[...] La máquina está analizando su mano para descartar..." T_RESET "\n");
    Sleep(2000);

    //Evaluacion de cartas repetidas
    //Comparamos cada carta de la mano contra todas las demas

    for (int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            //Si no es la misma carta en la misma posicion, pero tienen el mismo valor
            if ((i != j)&&(mano[i].valor == mano[j].valor)){
                repetidas[i] = 1; //Marcamos para no descartar esta carta porque forma un juego (Par/Pierna)
            }
        }
    }

    // Proceso de reemplazo de cartas sueltas
    for (int i=0; i<5; i++){
        //Si la carta i no se marco como repetida (repetidas[i] == 0, se descarta
        if (repetidas[i] == 0){
            mano[i] = mazo[*posicionMazo];  //Reemplazamos por la carta actual disponible del mazo
            (*posicionMazo)++;              //Avanzamos el contador general del mazo
            descartes++;                    //Contamos un descarte realizado
        }
    }

    printf(T_CIAN "-> La máquina descartó y cambió %d carta(s)." T_RESET "\n", descartes);
    Sleep(2000);
}

//Analiza las 5 cartas de una mano y devuelve un puntaje de 0 a 8 segun la jugada
int EvaluarMano(Carta_t mano[]){
    int valores[14] = {0};   //Arreglo contador de frecuencias para los valores (1 al 13)
    int palos[4] = {0};      //Arreglo contador de frecuencias para los palos (0 al 3)


    //Contamos cuantas cartas de cada valor y de cada palo hay en la mano
    for (int i=0; i<5; i++){
        valores[mano[i].valor]++;
        palos[mano[i].palo]++;
    }

    //Verificamos si hay COLOR (las 5 cartas son del mismo palo)
    int esColor = 0;
    for (int p=0; p<4; p++){
        if(palos[p] == 5){
            esColor = 1;
        }
    }

    //Verificamos si hay ESCALERA (5 valores consecutivos)
    int esEscalera = 0;
    for(int v=1; v <= 9; v++){
        if((valores[v] == 1)&& (valores[v+1] == 1) && (valores[v+2] == 1) && (valores[v+3] == 1) && (valores[v+4] == 1)){
            esEscalera = 1;
        }
    }

    //Caso especial de Escalera Real/Alta (10, J, Q, K, As)
    if((valores[10] == 1) && (valores[11] == 1) && (valores[12] == 1) && (valores[13] == 1) && (valores[1] == 1)){
        esEscalera = 1;
    }

    //Si combina Escalera y Color es la jugada mas alta
    if(esEscalera && esColor) return 8; //Escalera de color

    //Contamos pares,trios y pokers analizando las frecuencias de valores
    int pares = 0;
    int trios = 0;
    int pokers = 0;

    for(int v=1; v<=13; v++){
        if(valores[v] == 2) pares++;
        if(valores[v] == 3) trios++;
        if(valores[v] == 4) pokers++;
    }

    //Retornamos la jerarquia obtenida
    if(pokers == 1) return 7;                            //poker
    if((trios == 1) && (pares == 1)) return 6;           //Full House
    if(esColor) return 5;                                //Color
    if (esEscalera) return 4;                            //Escalera
    if (trios == 1) return 3;                            //Trio
    if (pares == 2) return 2;                            //Doble Par
    if (pares == 1) return 1;                            //Par

    return 0; //Carta Alta (sin combinacion)
}

//Compara los puntajes de ambas manos e imprime el resultado final
void DeterminarGanador(Carta_t manoJugador[], Carta_t manoMaquina[]){
    //Evaluamos los puntajes numericos
    int catJugador = EvaluarMano(manoJugador);
    int catMaquina = EvaluarMano(manoMaquina);

    printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                🏆 RESULTADO FINAL - SHOWDOWN              ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝" T_RESET "\n");

    //Mostramos la mano de la maquina al final para transparencia
    MostrarMano(manoMaquina,5,"Maquina");

    printf("\n  " T_CIAN "-> Tu jugada           : " T_AMARILLO "%s" T_RESET "\n", NOMBRES_JUGADAS[catJugador]);
    printf("  " T_CIAN "-> Jugada de la máquina : " T_AMARILLO "%s" T_RESET "\n", NOMBRES_JUGADAS[catMaquina]);
    printf(T_AMARILLO "───────────────────────────────────────────────────────────" T_RESET "\n");

    //Comparacion de resultados
    if(catJugador > catMaquina){
        printf("  " T_VERDE "¡FELICITACIONES! GANASTE LA MANO DE POKER. 🏆" T_RESET "\n");
    }else if (catMaquina > catJugador){
        printf("  " T_ROJO "LA MÁQUINA GANA ESTA MANO." T_RESET "\n");
        //Tienen la misma categoria (ej: Trio vs trio, par vs par)
    }else{
        //Obtenemos el valor de la combinacion principal (ej: 10 para el trio del usuario vs 7 para la maquina)
        int valCombJugador = ObtenerValorCombinacion(manoJugador, catJugador);
        int valCombMaquina = ObtenerValorCombinacion(manoMaquina, catMaquina);

        if(valCombJugador > valCombMaquina){
            printf("  " T_VERDE "¡FELICITACIONES! GANASTE POR TENER MEJOR %s. 🏆" T_RESET "\n", NOMBRES_JUGADAS[catJugador]);
        }else if(valCombMaquina > valCombJugador){
            printf("  " T_ROJO "LA MÁQUINA GANA POR TENER MEJOR %s." T_RESET "\n", NOMBRES_JUGADAS[catMaquina]);
        }else{
            //Solo entra aca si la combinacion principal es identica (ej: par de 8 vs par de 8)
           printf("  " T_AMARILLO "[!] Ambos tienen %s de igual valor. Evaluando desempate por Kicker..." T_RESET "\n", NOMBRES_JUGADAS[catJugador]);
            int ganadorDesempate = DesempatarManos(manoJugador, manoMaquina);

            if(ganadorDesempate == 1){
                printf("  " T_VERDE "¡GANASTE EL DESEMPATE POR CARTA MÁS ALTA / KICKER! 🏆" T_RESET "\n");
            }else if(ganadorDesempate == 2){
                printf("  " T_ROJO "LA MÁQUINA GANA EL DESEMPATE POR CARTA MÁS ALTA / KICKER." T_RESET "\n");
            }else{
                printf("  " T_AMARILLO "¡EMPATE ABSOLUTO EN LA MESA! Se devuelven las apuestas." T_RESET "\n");
            }
        }
    }
    printf(T_AMARILLO "═══════════════════════════════════════════════════════════" T_RESET "\n");
}


//Ordena las 5 cartas de la mano de menor a mayor segun su valor (1 al 13)
// Facilita la comparacion de escaleras y desempatar por carta alta (kicker)
void OrdenarMano(Carta_t mano[]){
    //Bucle exterior: controla las pasadas necesarias sobre el arreglo
    for (int i = 0; i<4; i++){
        //Bucle interior: compara elementos adyacentes y los intercambia si estan desordenados
        for (int j=0; j<4-i; j++){

            //Si la carta actual tiene un valor mayor que la siguiente...
            if(mano[j].valor > mano[j+1].valor){
                //Intercambio clasico de posiciones utilizando una variable auxiliar "temp"
                Carta_t temp = mano[j];
                mano[j] = mano[j+1];
                mano[j+1] = temp;
            }
        }
    }
}

//Resuelve un empate cuando ambos jugadores tienen la misma jjugada
//Primero compara el valor de la combinacion (ej: Par de K vs Par de 8)
//y si son iguales, desempata por la carrta mas alta / kicker
int DesempatarManos(Carta_t manoJugador[], Carta_t manoMaquina[]){
    //Antes de comparar, ordenamos ambas manos de menor a mayor (valores 1 al 13)
    OrdenarMano(manoJugador);
    OrdenarMano(manoMaquina);

    //Guardamos la categoria numerica de la  jugada (4 = escalera, 8 = escalera de color, etc)
    int categoria = EvaluarMano(manoJugador);

    //Desempate de escaleras
    if((categoria == 4)||(categoria == 8)){

        //Verificamos si alguna es la Escalera Real/Alta al As (10, J, Q, K, As)
        //Al ordenar de menor a mayor, el As queda en el indice0 (valor 1) y el K en el 4 (valor 13)
        int esAsAltaJugador = ((manoJugador[0].valor == 1)&&(manoJugador[4].valor == 13));
        int esAsAltaMaquina = ((manoMaquina[0].valor == 1)&&(manoMaquina[4].valor == 13));

        //Si el jugador tiene escalera al As y la maquina no, gana el jugador
        if((esAsAltaJugador)&&(!esAsAltaMaquina))return 1;
        //Si la maquina tiene escalera al As y el jugador no, gana la maquina
        if((!esAsAltaJugador)&&(esAsAltaJugador)) return 2;

        //Si son escaleras normales (ej: 3-4-5-6-7 vs 5-6-7-8-9), la carta mas alta
        //siempre queda en el ultimo indice (posicion 4) tras ordenar.
        if(manoJugador[4].valor > manoMaquina[4].valor) return 1;
        if(manoMaquina[4].valor > manoJugador[4].valor) return 2;

        return 0; // si llegan aca, las dos escaleras terminan en el mismo numereo

    }

    //Desempate de jugadas con pares, trios o poker
    if((categoria == 1)||(categoria == 3)||(categoria == 6)||(categoria == 7)){
        int valJugador = ObtenerValorCombinacion(manoJugador, categoria);
        int valMaquina = ObtenerValorCombinacion(manoMaquina, categoria);

        //Si una combinacion es mas alta que la otra (ej: Par de 10 vs Par de 8), gana directo
        if(valJugador > valMaquina) return 1;
        if(valMaquina > valJugador) return 2;


        //Si las combinaciones son iguales (ej: Par de 8 vs Par de 8), pasa al desempate por kickers
    }



    //Caso general: Carta Alta, pares, trios, poker, color, etc
    //Compara desde la carta mas alta (posicion 4) hacia la mas baja (posicion 0)
    //Tratamos es As (valor 1) como el valor mas alto dell juego (valor 14 virtual)



    // Recorremos las 5 cartas desde la posicion mas alta (indice 4) hacia la mas baja (indice 0).
    // Como la mano ya esta ordenada de menor a mayor, este bucle nos permite comparar
    // primero los kickers / cartas mas altas para resolver el desempate.
    for (int i = 4;i>=0; i--){ //Recorre la mano de derecha a izquierda (de la carta mas alta a la mas baja)
        //Asignamos un valor "virtual" del 14 al As (valor == 1) para que supere al K (valor 13)
        int vJugador = ObtenerValorVirtual(manoJugador[i].valor);
        int vMaquina = ObtenerValorVirtual(manoMaquina[i].valor);


        //Comparamos carta por carta de mayor a menor jerarquia (kicker)
        if(vJugador > vMaquina) return 1; //La carta del jugador es mas alta
        if(vMaquina > vJugador) return 2; //La carta de la maquina es mas alta

    }

    //Si recorrio las 5 cartas y toodas son identicas en valor, es un empate absoluto
    return 0;
}

//Devuelve el valor "virtual" del As (14) o el valor normal (2 al 13)
//Ayuda a comparar correctamente jerarquias donde el As es la carta mas fuerte
int ObtenerValorVirtual(int valor){
   if(valor == 1){
        return 14; // Si es un As, le asignamos jerarquia 14(Supera al K que vale 13)
   }else{
        return valor; //Para cualquier otra carta (2 al 13), mantiene su valor original
   }
}

//Busca el valor numerico de la combinacion principal (Par, Trio, Poker)
//asignando peso alto al As (14) para comparar combinaciones correctamente
int ObtenerValorCombinacion(Carta_t mano[], int jerarquia){
    int valores[14] = {0};

    //Contamos cuantas cartas hay de cada valor
    for (int i=0;i<5;i++){
        valores[mano[i].valor]++;
    }

    //Caso 1. Poker (4 cartas iguales)
    if(jerarquia == 7){
        for(int i=1; i<=13; i++){
            if(valores[i] == 4) return ObtenerValorVirtual(i);
        }
    }

    //Caso 2. Trio (3 cartas iguales)
    if((jerarquia == 3)||(jerarquia == 6)){ //Trio o Full House
        for(int i=1;i<=13;i++){
            if(valores[i] == 3) return ObtenerValorVirtual(i);
        }
    }

    //Doble Par: Par mayor * 100 + par menor

    if(jerarquia == 2){
        //Variables para guardar el valor de cada uno de los 2 pares encontrados
        int par1 = 0, par2 = 0;

        //Recorremos los valores posibles de las cartas (del 1 al 13: As al Rey)
        for(int i=1; i<=13;i++){

            //Si "valores[i] == 2", significa que tenemos un par de ese valor
            if(valores[i] == 2){

                //convertimos el valor (si es 1/As pasa a valer 14 para la jerarquia)
                int vVirtual = ObtenerValorVirtual(i);

                //Si es el primer par que encontramos, lo guardamos en par1
                if(par1 == 0){
                    par1 = vVirtual;
                //Si par1 ya tenia valor, este segundo par lo guardamosen par2
                }else{
                    par2 = vVirtual;
                }
            }
        }

        //Una vez identificados los 2 pares, comparamos cual es el mas alto:
        //Multiplicamos el par mayor por 100 para darle prioridad
        //Ej: par de ases (14) y par de 2 (2) -> (14*100) + 2= 1402
        if(par1 > par2){
            return (par1*100) + par2;
        }else{
            return (par2*100) + par1;
        }
    }

    //Caso 3. Par simple (2 cartas iguales)
    if(jerarquia == 1){
        for(int i=1; i<=13; i++){
            if(valores[i] == 2) return ObtenerValorVirtual(i);
        }
    }

    return 0;
}

//Funcion para validar e ingresar la apuesta del jugador
//Recibe el puntero al saldo real del jugador (*saldo) y la apuesta minima requerida
//Devuelve el monto final apostado (o 0.0f si no tiene saldo suficiente)

float RealizarApuesta(float *saldo, float apuestaMinima){
    float apuesta = 0.0f; //Variable para almacenar el monto digitado


    // Validacion previa: Si la caja del casino está en negativo o en cero, la casa no puede igualar
    if(cajaCasino <= 0.0f){
        system("clear || cls");
        printf("\n" T_ROJO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║         [!] MESA VIP CERRADA TEMPORALMENTE                ║\n");
        printf("╠═══════════════════════════════════════════════════════════╣\n");
        printf("  La banca del casino se encuentra sin fondos   \n", cajaCasino);
        printf("  No hay respaldo para igualar apuestas en este momento.     \n");
        printf("╚═══════════════════════════════════════════════════════════╝" T_RESET "\n");
        printf("Presione ENTER para regresar al menú...");

        while(getchar() != '\n');
        getchar();
        return 0.0f; // Aborta la partida
    }


    //Validacion previa para verificar si el jugador tiene saldoo suficiente
    if(*saldo < apuestaMinima){
        printf("\n" T_ROJO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║         [!] SALDO INSUFICIENTE PARA ENTRAR A MESA         ║\n");
        printf("╠═══════════════════════════════════════════════════════════╣" T_RESET "\n");
        printf("  Monto Mínimo Requerido : " T_AMARILLO "$%.2f" T_RESET "\n", apuestaMinima);
        printf("  Tu Saldo Actual        : " T_ROJO "$%.2f" T_RESET "\n", *saldo);
        printf(T_ROJO "╚═══════════════════════════════════════════════════════════╝" T_RESET "\n");
        printf("Presione ENTER para regresar al menú...");

        //Limpiamos cualquier salto de linea residual en el bufer antes de pausar
        while(getchar() != '\n');
        getchar();

        return 0.0f; //Retorna 0 para indicar que no se pudo iniciar la apuesta
    }

    //Se repite hasta la apuesta sea valida
    do{
        system("clear || cls");
        printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║               " T_VERDE "  🪙 MESA DE APUESTAS DE POKER 🪙  " T_RESET T_AMARILLO "           ║\n");
        printf("╠═══════════════════════════════════════════════════════════╣" T_RESET "\n");
        printf(T_AMARILLO "║ " T_VERDE " 💵 Saldo Disponible : " T_AMARILLO "$%-22.2f " T_AMARILLO "           ║\n", *saldo);
        printf(T_AMARILLO "║ " T_CIAN " 📌 Apuesta Mínima   : " T_AMARILLO "$%-22.2f " T_AMARILLO "           ║\n", apuestaMinima);
        printf(T_AMARILLO "╚═══════════════════════════════════════════════════════════╝" T_RESET "\n");
        printf(" " T_BLANCO "Ingrese el monto a apostar: " T_VERDE "$" T_RESET);

        if(!LeerFloatValido(&apuesta)){
            apuesta = -1.0f; //fuerza repetir si ingresan letras o caracteres extra
        }

        //Mensajes de error especificos segun la falta cometida
        if(apuesta < apuestaMinima){
            printf("\n" T_ROJO "[x] Error: La apuesta minima permitida es $%.2f" T_RESET "\n",apuestaMinima);
            Sleep(2000);
        }else if(apuesta > *saldo){
            printf("\n" T_ROJO "[x] Error: No podes apostar mas de lo que tenes ($%.2f)" T_RESET "\n",*saldo);
            Sleep(2000);
        }

    //El ciclo continua si la apuesta es menor al minimo o mayor al saldo disponible
    }while((apuesta < apuestaMinima)||(apuesta > *saldo));


    //Descuento y confirmacion
    //Restamos el momto apostado directamente en la variable original usando (*saldo)
    *saldo -= apuesta;

    printf("\n" T_VERDE "[✔] Apuesta de $%.2f realizada con exito. Saldo restante: $%.2f" T_RESET "\n",apuesta,*saldo);
    Sleep(2000);

    return apuesta; //Retornamos el monto apostado para usarlo en la mano actual
}

//Funcion auxiliar para leer un entero limpio de la consola
// Devuelve 1 si la lectura fue perfecta (solo un entero seguido de ENTER).
// Devuelve 0 si ingresaron letras, decimales o texto pegado.

int LeerEnteroValido(int *num) {
    int leidos = scanf("%d", num);
    char charSiguiente;

    if (leidos == 1) {
        charSiguiente = getchar(); // Captura el caracter justo despues del numero
        if (charSiguiente == '\n') {
            return 1; // Entrada perfecta: Numero + ENTER
        } else {
            //si  Habia caracteres extra pegados (ej: "5abc" o "5.5")
            while (getchar() != '\n'); // Limpia el resto de la linea
            return 0;
        }
    } else {
        // Fallo completamente la lectura (ej: "abc")
        while (getchar() != '\n'); // Limpia el bufer
        return 0;
    }
}


// Devuelve 1 si se leyo un float limpio seguido de ENTER. Devuelve 0 si hab�a letras o basura.
int LeerFloatValido(float *num) {
    int leidos = scanf("%f", num);
    char charSiguiente;

    if (leidos == 1) {
        charSiguiente = getchar();
        if (charSiguiente == '\n') {
            return 1;
        } else {
            while (getchar() != '\n');
            return 0;
        }
    } else {
        while (getchar() != '\n');
        return 0;
    }
}




//==================================================================
//Coordina todo el fllujo de una mano completa del Poker
// 1. Cobra la apuesta inicial
// 2. Inicializa y mezcla el mazo de cartas
// 3. Reparte las cartas al jugador y a la m�quina.
// 4. Ejecuta las fases de descarte interactivo y autom�tico.
// 5. Evalua las manos, determina al ganador y actualiza el saldo real.
// PARAMETRO: float *saldo -> Puntero al saldo real del usuario.

void JugarPartidaPoker(Usuario_t *usuario){

    float apuestaMinima = 5000.0f;     //Definimos el costo minimo para poder jugar una mano
    int opcionBucle = 0;               //Almacena la decision del jugador (1 para seguir,2 para salir)

    //Bucle que garantiza que se ejecute la mano al menos una vez al entrar
    do{
        //Definicion del mazo de 52 cartas y las manos de 5 cartas para cada uno
        Carta_t mazo[52];
        Carta_t manoJugador[5];
        Carta_t manoMaquina[5];

        int posicionMazo = 0;           //Indice para saber por qu� carta del mazo vamos

        //LLamamos a RealizarApuesta pasandole el puntero del saldo
        //La funcion valida si alcanza el dinero y descuenta el monto apostado
        //Llamamos a la apuesta enviando la direccion del saldo del usuario
        float montoApostado = RealizarApuesta(&(usuario->saldo), apuestaMinima);

        //Si montoApostado devuelve 0.0, significa que el jugador no tenia saldo
        //suficiente o cancela. Usamos return para abortar la partida e ir al menu

        if(montoApostado == 0.0f){
            return;
        }

        // ==========================================
        // 2. ANIMACIÓN DE APUESTA CONFIRMADA
        // ==========================================
        // (Si tu función RealizarApuesta ya imprime su propio cartel, podés 
        //  llamar a la animación general aquí pasándole el monto entero)
        AnimacionApuesta((int)montoApostado);

        //Se cargan las 52 cartas ordenadas y luego se desordenan de forma aleatoria
        InicializarMazo(mazo);
        MezclarMazo(mazo);

        //Repartimos 5 cartas iniciales a cada participante
        //Pasamos &PosicionMazo por referencia para qye avance progresivamente
        RepartirMano(mazo, manoJugador, &posicionMazo);
        RepartirMano(mazo, manoMaquina, &posicionMazo);

        // ==========================================
        // 3. ANIMACIÓN DE MEZCLADO EN CASCADA
        // ==========================================
        AnimacionMezclando();

        //Limpiamos la pantalla para mostrar la mesa limpia con tu mano inicial
        system("clear || cls");
        //Mostramos las cartas iniciales al usuario
        MostrarMano(manoJugador,5, "Jugador");
        int jugadaInicial = EvaluarMano(manoJugador);
        printf("  " T_CIAN "-> Tu jugada actual: " T_AMARILLO "%s" T_RESET "\n", NOMBRES_JUGADAS[jugadaInicial]);

        //El usuario elige de 0 a 5 cartas para reponer del mazo
        DescartarJugador(manoJugador, mazo, &posicionMazo);

        //La maquina evalua automaticamente que cartas le conviene cambiar
        DescartarMaquina(manoMaquina, mazo, &posicionMazo);

        //Limpiamos la pantalla para mostrar la mesa limpia con tu mano inicial
        system("clear || cls");
        //Mostramos la mano definitiva del jugador tras el descarte
        MostrarMano(manoJugador,5, "Jugador (Mano Final)");
        int jugadaFinal = EvaluarMano(manoJugador);
        printf("  " T_CIAN "-> Tu jugada final  : " T_AMARILLO "%s" T_RESET "\n", NOMBRES_JUGADAS[jugadaFinal]);

        // Pausa breve para dar suspenso antes de ver las cartas de la casa
        printf("\n  " T_BLANCO "Presiona ENTER para ver el resultado de la Casa..." T_RESET);
        fflush(stdin);
        getchar();

        //Imprime la mano de la maquina y declara el resultado de la partida
        DeterminarGanador(manoJugador,manoMaquina);

        //Corregido: Logica de cobro alineada con el resultado real
        int catJugador = EvaluarMano(manoJugador);
        int catMaquina = EvaluarMano(manoMaquina);
        int valJugador = ObtenerValorCombinacion(manoJugador, catJugador);
        int valMaquina = ObtenerValorCombinacion(manoMaquina, catMaquina);

        //Resolucion de saldos segun el resultado
        if((catJugador > catMaquina) || ((catJugador == catMaquina) && (valJugador > valMaquina))){
            float premio = montoApostado*2;
            usuario->saldo += premio; //Actualizamos el saldo del usuario sumando el premio ganado
            printf("\n  " T_VERDE "[$$$] ¡Ganaste $%.2f! Tu saldo actual es: $%.2f" T_RESET "\n", premio, usuario->saldo);

            //La casa paga (actualiza caja del casino)
            ActualizarCajaCasino(&cajaCasino, montoApostado, 1);
            
            //Auditoria comercial individual: el casino pierde frrente a este usuario
            //El casino pierde unicamente el monto de la apuesta en esta mano
            usuario->gananciaAdmin -= montoApostado;
            
        }else if((catMaquina > catJugador) || ((catJugador == catMaquina) && (valMaquina > valJugador))){
            printf("\n  " T_ROJO "[-] Perdiste $%.2f. Tu saldo actual es: $%.2f" T_RESET "\n", montoApostado, usuario->saldo);

           //Controlc contable en derrota Poker
           if(usuario->dineroDepositado >= montoApostado){
                usuario->dineroDepositado -= montoApostado;
           }else{
                float diferenciaGanancia = montoApostado - usuario->dineroDepositado;
                usuario->dineroDepositado = 0;
                ActualizarCajaCasino(&cajaCasino, diferenciaGanancia, -1);
           }

           //Auditoria comercial: el casino gana frente a este usuario
           usuario->gananciaAdmin += montoApostado;

        }else{
            int desempate = DesempatarManos(manoJugador, manoMaquina);

            if(desempate == 1){
                //El jugador gana el desempate
                float premio = montoApostado * 2;
                usuario->saldo += premio;
                printf("\n  " T_VERDE "[$$$] ¡Ganaste el desempate y te llevás $%.2f! Saldo actual: $%.2f" T_RESET "\n", premio, usuario->saldo);

                ActualizarCajaCasino(&cajaCasino, montoApostado, 1);
                usuario->gananciaAdmin -= montoApostado;

            }else if(desempate == 2){
                //La maquina gana el desempate
                printf("\n  " T_ROJO "[-] Perdiste el desempate de $%.2f. Saldo actual: $%.2f" T_RESET "\n", montoApostado, usuario->saldo);

                // CONTROL CONTABLE EN DESEMPATE PERDIDO
                if (usuario->dineroDepositado >= montoApostado) {
                    usuario->dineroDepositado -= montoApostado;
                } else {
                    float diferenciaGanancia = montoApostado - usuario->dineroDepositado;
                    usuario->dineroDepositado = 0;
                    ActualizarCajaCasino(&cajaCasino, diferenciaGanancia, -1);
                }
                
                usuario->gananciaAdmin += montoApostado;
                
            }else{
                //Empate absoluto: se devuelve la apuesta intacta
                usuario->saldo += montoApostado;
                printf("\n  " T_AMARILLO "[=] Empate absoluto. Se te devuelve la apuesta de $%.2f. Saldo actual: $%.2f" T_RESET "\n", montoApostado, usuario->saldo);

                //En empate la caja no cambia, pero cuenta cmo partida jugada y empate
                ActualizarCajaCasino(&cajaCasino, montoApostado, 0);
            }
        }

        //Consulta para continuar o salir de la mesa
        //Verificamos si al jugador le alcanza el saldo para volver a jugar
        if(usuario->saldo >= apuestaMinima){
            do{
                printf("\n" T_BLANCO "¿Querés jugar otra mano? (" T_VERDE "1. Sí" T_BLANCO " / " T_ROJO "2. No" T_BLANCO "): " T_RESET);

                if(!LeerEnteroValido(&opcionBucle)){
                    opcionBucle = 0;
                }

                if((opcionBucle != 1)&&(opcionBucle != 2)){
                    printf(T_ROJO "[X] Error: Ingrese solo 1 para Sí o 2 para No." T_RESET "\n");
                }
            }while((opcionBucle != 1)&&(opcionBucle != 2));

        }else{
            //Si el saldo no alcanza, mostramos mensaje y forzamos la salida del ciclo
            printf("\n" T_ROJO "[!] Tu saldo ($%.2f) es menor a la apuesta mínima ($%.2f). Regresando al menú..." T_RESET "\n", usuario->saldo, apuestaMinima);
            printf("Presiona ENTER para continuar...");
            getchar();
            opcionBucle = 2; //Rompe la condicion del do-while
        }

    //El ciclo se repite solo si la variable opcionBucle quedo cargada con el numero 1
    }while(opcionBucle == 1);
}

// ============================================================================
// 1. ANIMACIÓN DE BIENVENIDA VIP (Alineación Milimétrica Perfecta)
// ============================================================================
void AnimacionBienvenida() {
    for (int i = 0; i < 3; i++) {
        system("clear || cls");
        
        printf("\n");
        printf("  " T_AMARILLO "╔═════════════════════════════════════════════════╗\n");
        printf("  ║    " T_ROJO "♥ " T_BLANCO "♦ " T_VERDE "♣ " T_CIAN "♠" T_AMARILLO "  CASINO GANO - SALÓN VIP  " T_CIAN "♠ " T_VERDE "♣ " T_BLANCO "♦ " T_ROJO "♥    " T_AMARILLO "║\n");
        printf("  ╠═════════════════════════════════════════════════╣\n");
        printf("  ║                                                 ║\n");
        printf("  ║       " T_BLANCO "╔═══════╗         ╔═══════╗" T_AMARILLO "               ║\n");
        printf("  ║       " T_BLANCO "║ " T_ROJO "As ♥  " T_BLANCO "║         ║ " T_CIAN "K ♠  " T_BLANCO " ║" T_AMARILLO "               ║\n");
        printf("  ║       " T_BLANCO "║   ♥   ║         ║   ♠   ║" T_AMARILLO "               ║\n");
        printf("  ║       " T_BLANCO "║  As ♥ ║         ║  K ♠  ║" T_AMARILLO "               ║\n");
        printf("  ║       " T_BLANCO "╚═══════╝         ╚═══════╝" T_AMARILLO "               ║\n");
        printf("  ║                                                 ║\n");
        printf("  ╚═════════════════════════════════════════════════╝\n" T_RESET);
        
        if (i % 2 == 0) {
            printf("\n        " T_VERDE "   >>>> 🪙 PREPARANDO MESA Y FICHAS VIP... <<<<  " T_RESET "\n");
        } else {
            printf("\n        " T_CIAN "   >>>> 🪙 PREPARANDO MESA Y FICHAS VIP... <<<<  " T_RESET "\n");
        }
        
        Sleep(1000); 
    }
}

// ============================================================================
// 2. ANIMACIÓN DE MEZCLADO EN CASCADA
// ============================================================================
void AnimacionMezclando() {
    system("clear || cls");
    printf("\n" T_CIAN "          [ CRUPIER BARAJANDO EL MAZO EN CASCADA ]" T_RESET "\n\n");
    printf("        " T_AMARILLO "╔═══════╗                   ╔═══════╗\n");
    printf("        ║" T_ROJO "░░░░░░░" T_AMARILLO "║                   ║" T_CIAN "░░░░░░░" T_AMARILLO "║\n");
    printf("        ║" T_ROJO "░░ 🂠 ░░" T_AMARILLO "║                   ║" T_CIAN "░░ 🂠 ░░" T_AMARILLO "║\n");
    printf("        ║" T_ROJO "░░░░░░░" T_AMARILLO "║                   ║" T_CIAN "░░░░░░░" T_AMARILLO "║\n");
    printf("        ╚═══════╝                   ╚═══════╝" T_RESET "\n");
    Sleep(1000);

    system("clear || cls");
    printf("\n" T_CIAN "          [ CRUPIER BARAJANDO EL MAZO EN CASCADA ]" T_RESET "\n\n");
    printf("              " T_AMARILLO "╔═══════╗       ╔═══════╗\n");
    printf("              ║" T_ROJO "░░░░░░░" T_AMARILLO "║       ║" T_CIAN "░░░░░░░" T_AMARILLO "║\n");
    printf("              ║" T_ROJO "░░ 🂠 ░░" T_AMARILLO "║       ║" T_CIAN "░░ 🂠 ░░" T_AMARILLO "║\n");
    printf("              ║" T_ROJO "░░░░░░░" T_AMARILLO "║       ║" T_CIAN "░░░░░░░" T_AMARILLO "║\n");
    printf("              ╚═══════╝       ╚═══════╝\n");
    printf("                      " T_AMARILLO "\\\\     //\n");
    printf("                       \\\\   //" T_RESET "\n");
    Sleep(1100);

    system("clear || cls");
}


// ============================================================================
// PANTALLA DE APUESTA PRO: MARCOS DOBLES Y EFECTO FICHAS EN MESA
// ============================================================================
void AnimacionApuesta(int montoApuesta) {
    system("clear || cls");
    
    printf("\n");
    printf("  " T_AMARILLO "╔═════════════════════════════════════════════════════════╗\n");
    printf("  ║   " T_ROJO " [!] MESA DE POKER: APUESTA CONFIRMADA [!] " T_AMARILLO "           ║\n");
    printf("  ╠═════════════════════════════════════════════════════════╣\n");
    printf("  ║                                                         ║\n");
    printf("      " T_VERDE "Jugador ingresa " T_BLANCO ":  " T_AMARILLO "[ 🪙  $%d.00 ]" T_BLANCO "                       \n", montoApuesta);
    printf("      " T_VERDE "Casa iguala     " T_BLANCO ":  " T_AMARILLO "[ 🪙  $%d.00 ]" T_BLANCO "                       \n", montoApuesta);
    printf("      " T_BLANCO "───────────────────────────────────────────────────    \n");
    printf("      " T_CIAN "POZO EN MESA    " T_BLANCO ":  " T_VERDE " 💵  $%d.00 TOTAL " T_BLANCO "                  \n", montoApuesta * 2);
    printf("  ║                                                         ║\n");
    printf("  ╚═════════════════════════════════════════════════════════╝\n\n" T_RESET);
    
    printf("        " T_CIAN ">>>> PRESIONA <<ENTER>> PARA REPARTIR <<<<\n" T_RESET);
    
    fflush(stdin);
    getchar(); 
}
 
//Funcion para actualizar la caja de la casa segun el resultado de la partida
//resultado: -1 (pierde jugador / gana casa), 1 (gana jugador / paga casa), 0 (empate)
void ActualizarCajaCasino(float *cajaCasa, float montoApostado, int resultado){
    if(resultado == -1){
        //El jugador pierde: el casino gana y acumula el monto apostado
        *cajaCasa += montoApostado;
    }else if (resultado == 1){
        //El jugador gana: el casino debe pagar el premio (resta de la caja)
        *cajaCasa -= montoApostado;
    }
    //Si resultado == 0, la caja queda intacta porque se devuelve el dinero
}