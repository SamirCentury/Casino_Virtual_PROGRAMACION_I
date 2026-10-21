#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definimos la estructura basica para cada carta
typedef struct
{
int valor; // 1 (As), 2 al 10, 11(J), 12(Q), 13(K)
int palo; // 0: Corazones, 1: Diamantes, 2: Treboles, 3: Picas

}Carta;

//Arreglo constante global para imprimir el texto del palo segun su indice (0 a 3)
const char *NOMBRES_PALOS[] = {"Corazones", "Diamantes", "Treboles", "Picas"};

const char *NOMBRES_JUGADAS[] = {
    "Carta Alta", "Par", "Doble Par", "Trio",
    "Escalera", "Color", "Full House", "Poker", "Escalera de Color"
};

void InicializarMazo(Carta mazo[]);
void MezclarMazo(Carta mazo[]);
void ImprimirCarta(Carta c);
void MostrarMano(Carta mano[], int cantidad, const char *nombreJugador);
void RepartirMano(Carta mazo[], Carta mano[], int *posicionMazo);
void DescartarJugador(Carta mano[], Carta mazo[], int *posicionMazo);
void DescartarMaquina(Carta mano[], Carta mazo[], int *posicionMazo);
int EvaluarMano(Carta mano[]);
void DeterminarGanador(Carta manoJugador[], Carta manoMaquina[]);
void ReglasDelPoker();
void MenuJuegoPoker(float *saldo);
float RealizarApuesta(float *saldo, float apuestaMinima);
void OrdenarMano(Carta mano[]);
int DesempatarManos(Carta manoJugador[], Carta manoMaquina[]);
void JugarPartidaPoker(float *saldo);
int ObtenerValorVirtual(int);
int ObtenerValorCombinacion(Carta mano[], int);
int LeerEnteroValido(int *num);
int LeerFloatValido(float *num);





int main(void)
{
    srand((unsigned int)time(NULL)); //Inicializamos el azar
    float saldoJugador = 250000.0f;

    MenuJuegoPoker(&saldoJugador);


    return 0;


}
//=============================================================
//   FUNCIONES BASE DEL MAZO
//=============================================================

//Menu completo del poker
void MenuJuegoPoker(float *saldo){
    int opcionSubMenu = 0;
    int leidos = 0;              //Almacena la validacion del scanf (1 si leyo entero, 0 si fallo)

    do{

        printf("\n=======================================\n");
        printf("           SALON DE POKER - CASINO       \n");
        printf("\n=======================================\n");
        printf("Saldo disponible: $%.2f\n",*saldo);
        printf("1. Jugar.\n");
        printf("2. Reglas.\n");
        printf("3. Salir.\n");
        printf("\n=======================================\n");
        printf("Seleccione una opcion: ");

        if(!LeerEnteroValido(&opcionSubMenu)){
            opcionSubMenu = 0; //Forzamos 0 para ir al default del switch
        }

        switch(opcionSubMenu){
        case 1:
            printf("\n[ Ingresando a la mesa de juego...]\n");
            JugarPartidaPoker(saldo);
            break;
        case 2:
            ReglasDelPoker();
            break;
        case 3:
            printf("\nSaliendo del modulo de Poker...\n");
            break;
        default:
            printf("\n[x] Opcion invalida. Por favor, ingrese un numero valido (1, 2 o 3).\n");
            break;

            }
      }while(opcionSubMenu != 3);
}

void ReglasDelPoker(){
    printf("\n=====================================================\n");
    printf("                     REGLAS DEL POKER                  \n");
    printf("\n=====================================================\n");
    printf("1. Cada jugador recibe 5 cartas de un mazo de 52.\n");
    printf("2. Podes cambiar de 0 a 5 cartas en la fase de descarte.\n");
    printf("3. Gana la mano quien forme la combinacion de mayor jerarquia:\n");
    printf("      - Escalera Real      (10, J, Q, K, As del mismo palo)\n");
    printf("      - Escalera de Color  (5 cartas consecutivas del mismo palo)\n");
    printf("      - Poker             (4 cartas con el mismo valor)\n");
    printf("      - Full House        (Un Trio + Un Par)\n");
    printf("      - Color             (5 cartas del mismo palo)\n");
    printf("      - Escalera          (5 cartas de valores consecutivos)\n");
    printf("      - Trio              (3 cartas con el mismo valor)\n");
    printf("      - Doble Par         (Dos pares de cartas iguales)\n");
    printf("      - Par               (Dos cartas con el mismo valor)\n");
    printf("      - Carta Alta        (Valor de la carta mas alta)\n");
    printf("\n=====================================================\n");
    printf("Presiona cualquier tecla para volver al menu...\n");
    getchar();
}



// Carga las 52 cartas del mazo en orden (4 palos x 13 valores)
void InicializarMazo(Carta mazo[]){
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
void MezclarMazo(Carta mazo[]){
    for(int i=0; i<52; i++){
            //Genera un indice aleatorio entre 0 y 51
            int r = rand() % 52;


            //Intercambio clasico de variables usando una auxiliar
            Carta temp = mazo[i];
            mazo[i] = mazo[r];
            mazo[r] = temp;
        }
}

// Muestra una sola carta en pantalla con el formato adecuado (As, J, Q, K)
void ImprimirCarta(Carta c){
    if(c.valor == 1){
        printf("As");
    }else if (c.valor == 11){
        printf("J");
    }else if (c.valor == 12){
        printf("Q");
    }else if (c.valor == 13){
        printf("K");
    }else{
        printf("%d",c.valor); // Para numeros entre 2 y 10
    }

    printf(" de %s",NOMBRES_PALOS[c.palo]);

}

//Imprime las cartas de la mano indicando el numero de seleccion [1] al [5]
void MostrarMano(Carta mano[], int cantidad, const char *nombreJugador){
    printf("\n--- Mano de %s ----\n", nombreJugador);
    for(int i=0; i<cantidad; i++){
        printf("[%d] ", i+1);
        ImprimirCarta(mano[i]);
        printf("\n");
    }
    printf("--------------------------------\n");
}

//Reparte 5 cartas seguidas sacandolas del mazo activo
//Subproceso para repartir 5 cartas a una mano
void RepartirMano(Carta mazo[], Carta mano[], int *posicionMazo){
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
void DescartarJugador(Carta mano[], Carta mazo[], int *posicionMazo){
    int cantidad, posicionCarta;
    int leidos = 0;

    //Arreglo auxiliar para registrar posiciones (0 a 4) ya se marcaron para cambio
    //Inicializado en 0

    int posicionesCambiadas[5] = {0};

    printf("\n==========================================\n");
    printf("                  FASE DE DESCARTE          \n");
    printf("\n==========================================\n");

    do{
        printf("¿Cuantas cartas queres cambiar? (0 a 5): ");

        if(!LeerEnteroValido(&cantidad)){
            cantidad = -1;
        }

        if((cantidad < 0)||(cantidad > 5)){
            printf("[x] Error: Ingrese un numero valido entre 0 y 5.\n");
        }
    }while ((cantidad < 0)||(cantidad > 5));


    if(cantidad == 0){
        printf("Decidiste mantener toda tu mano intacta.\n");
        return;
    }


    //Preguntamos las posiciones
    for (int i=0; i<cantidad; i++){
        do{
            printf("Ingrese la posicion de la carta %d a cambiar (1 a 5): ", i+1);

            if(!LeerEnteroValido(&posicionCarta)){
                posicionCarta = -1;
            }


            if((posicionCarta < 1)||(posicionCarta > 5)){
                printf("[x] Error: Carta invalida. Elija entre 1 y 5.\n");
            }
             //Validacion: Control de duplicados (verifica si el casillero ya se uso)
             else if(posicionesCambiadas[posicionCarta - 1] == 1){
                printf("[x] Error: Ya pediste cambiar la carta de la posicion %d. Elija otra posicion.\n", posicionCarta);
                posicionCarta = -1; // Forzamos repetir la consulta
             }


        }while((posicionCarta < 1)||(posicionCarta > 5));

        // Marcamos la posición elegida como ocupada (se resta 1 por el índice 0 de C)
        posicionesCambiadas[posicionCarta - 1] = 1;

        // Reemplazamos la carta actual por la siguiente carta activa del mazo
        mano[posicionCarta - 1] = mazo[*posicionMazo];

        // Incrementamos el puntero global para avanzar a la siguiente carta del mazo
        (*posicionMazo)++;
    }

    printf("\n[!] Cartas reemplazadas con exito.\n");
}

//Prototipo para la rutina de descarte de la maquina
void DescartarMaquina(Carta mano[], Carta mazo[], int *posicionMazo){
    int repetidas[5] = {0}; //Arreglo auxiliar para marcar que cartas guardar (1=guardar, 0=descartar)
    int descartes = 0;      //Contador de cuantas cartas va a cambiar

    printf("\n[...] La maquina esta analizando su mano para descartar...\n");

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

    printf("-> La maquina descarto y cambio %d carta(s).\n",descartes);
}

//Analiza las 5 cartas de una mano y devuelve un puntaje de 0 a 8 segun la jugada
int EvaluarMano(Carta mano[]){
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
void DeterminarGanador(Carta manoJugador[], Carta manoMaquina[]){
    //Evaluamos los puntajes numericos
    int catJugador = EvaluarMano(manoJugador);
    int catMaquina = EvaluarMano(manoMaquina);

    printf("\n=======================================\n");
    printf("              RESULTADO FINAL            \n");
    printf("\n=======================================\n");

    //Mostramos la mano de la maquina al final para transparencia
    MostrarMano(manoMaquina,5,"Maquina");

    printf("\n -> Tu jugada: %s\n", NOMBRES_JUGADAS[catJugador]);
    printf("-> Jugada de la maquina: %s\n", NOMBRES_JUGADAS[catMaquina]);
    printf("---------------------------------------\n");

    //Comparacion de resultados
    if(catJugador > catMaquina){
        printf("¡FELICITACIONES! GANASTE LA MANO.\n");
    }else if (catMaquina > catJugador){
        printf("LA MAQUINA GANA ESTA MANO.\n");
        //Tienen la misma categoria (ej: Trio vs trio, par vs par)
    }else{
        //Obtenemos el valor de la combinacion principal (ej: 10 para el trio del usuario vs 7 para la maquina)
        int valCombJugador = ObtenerValorCombinacion(manoJugador, catJugador);
        int valCombMaquina = ObtenerValorCombinacion(manoMaquina, catMaquina);

        if(valCombJugador > valCombMaquina){
            printf("¡FELICITACIONES! GANASTE LA MANO POR TENER MEJOR %s.\n",NOMBRES_JUGADAS[catJugador]);
        }else if(valCombMaquina > valCombJugador){
            printf("LA MAQUINA GANA POR TENER MEJOR %s.\n",NOMBRES_JUGADAS[catMaquina]);
        }else{
            //Solo entra aca si la combinacion principal es identica (ej: par de 8 vs par de 8)
            printf("[!] Ambos tienen %s de igual valor. Evaluando desempate por Kicker...\n",NOMBRES_JUGADAS[catJugador]);

            int ganadorDesempate = DesempatarManos(manoJugador, manoMaquina);

            if(ganadorDesempate == 1){
                printf("¡GANASTE EL DESEMPATE POR CARTA MAS ALTA / KICKER\n");
            }else if(ganadorDesempate == 2){
                printf("¡LA MAQUINA GANA EL DESEMPATE POR CARTA MAS ALTA / KICKER\n");
            }else{
                printf("¡EMPATE ABSOLUTO EN LA MESA! Se devuelven las apuestas.\n");
            }
        }
    }

    printf("==========================================\n");
}


//Ordena las 5 cartas de la mano de menor a mayor segun su valor (1 al 13)
// Facilita la comparacion de escaleras y desempatar por carta alta (kicker)
void OrdenarMano(Carta mano[]){
    //Bucle exterior: controla las pasadas necesarias sobre el arreglo
    for (int i = 0; i<4; i++){
        //Bucle interior: compara elementos adyacentes y los intercambia si estan desordenados
        for (int j=0; j<4-i; j++){

            //Si la carta actual tiene un valor mayor que la siguiente...
            if(mano[j].valor > mano[j+1].valor){
                //Intercambio clasico de posiciones utilizando una variable auxiliar "temp"
                Carta temp = mano[j];
                mano[j] = mano[j+1];
                mano[j+1] = temp;
            }
        }
    }
}

//Resuelve un empate cuando ambos jugadores tienen la misma jjugada
//Primero compara el valor de la combinacion (ej: Par de K vs Par de 8)
//y si son iguales, desempata por la carrta mas alta / kicker
int DesempatarManos(Carta manoJugador[], Carta manoMaquina[]){
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
int ObtenerValorCombinacion(Carta mano[], int jerarquia){
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
        //Multiplicamos el par mayor por 1000 para darle prioridad
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
    int leidos = 0;       //Variable para verificar si sacnf leyo un numero valido

    //Validacion previa para verificar si el jugador tiene saldoo suficiente
    if(*saldo < apuestaMinima){
        printf("\n================================================\n");
        printf("       MESA DE POKER - SALDO INSUFICIENTE         \n");
        printf("================================================\n");
        printf(" [!] No tenes el saldo minimo de $%.2f para jugar.\n", apuestaMinima);
        printf("  Tu saldo actual es: $%.2f\n", *saldo);
        printf("================================================\n");
        printf("Presiona ENTER para regresar al menu...");

        //Limpiamos cualquier salto de linea residual en el bufer antes de pausar
        while(getchar() != '\n');
        getchar();

        return 0.0f; //Retorna 0 para indicar que no se pudo iniciar la apuesta
    }

    //Se repite hasta la apuesta sea valida
    do{
        printf("\n================================================\n");
        printf("                     MESA DE APUESTAS             \n");
        printf("================================================\n");
        printf(" Tu saldo disponible: $%.2f\n", *saldo);
        printf(" Apuesta minima     : $%.2f\n", apuestaMinima);
        printf("================================================\n");
        printf("Ingrese el monto a apostar: $");

        if(!LeerFloatValido(&apuesta)){
            apuesta = -1.0f; //fuerza repetir si ingresan letras o caracteres extra
        }

        //Mensajes de error especificos segun la falta cometida
        if(apuesta < apuestaMinima){
            printf("\[x] Error: La apuesta minima permitida es $%.2f\n",apuestaMinima);
        }else if(apuesta > *saldo){
            printf("\[x] Error: No podes apostar mas de lo que tenes ($%.2f)\n",*saldo);
        }

    //El ciclo continua si la apuesta es menor al minimo o mayor al saldo disponible
    }while((apuesta < apuestaMinima)||(apuesta > *saldo));


    //Descuento y confirmacion
    //Restamos el momto apostado directamente en la variable original usando (*saldo)
    *saldo -= apuesta;

    printf("\n[x] Apuesta de $%.2f realizada con exito. Saldo restante: $%.2f\n",apuesta,*saldo);

    return apuesta; //Retornamos el monto apostado para usarlo en la mano actual
}

//Funcion auxiliar para leer un entero limpio de la consola
// Devuelve 1 si la lectura fue perfecta (solo un entero seguido de ENTER).
// Devuelve 0 si ingresaron letras, decimales o texto pegado.

int LeerEnteroValido(int *num) {
    int leidos = scanf("%d", num);
    char charSiguiente;

    if (leidos == 1) {
        charSiguiente = getchar(); // Captura el carácter justo después del número
        if (charSiguiente == '\n') {
            return 1; // Entrada perfecta: Número + ENTER
        } else {
            // Había caracteres extra pegados (ej: "5abc" o "5.5")
            while (getchar() != '\n'); // Limpia el resto de la línea
            return 0;
        }
    } else {
        // Falló completamente la lectura (ej: "abc")
        while (getchar() != '\n'); // Limpia el búfer
        return 0;
    }
}


// Devuelve 1 si se leyó un float limpio seguido de ENTER. Devuelve 0 si había letras o basura.
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
// 3. Reparte las cartas al jugador y a la máquina.
// 4. Ejecuta las fases de descarte interactivo y automático.
// 5. Evalúa las manos, determina al ganador y actualiza el saldo real.
// PARAMETRO: float *saldo -> Puntero al saldo real del usuario.

void JugarPartidaPoker(float *saldo){

    float apuestaMinima = 5000.0f;     //Definimos el costo minimo para poder jugar una mano
    int opcionBucle = 0;               //Almacena la decision del jugador (1 para seguir,2 para salir)

    //Bucle que garantiza que se ejecute la mano al menos una vez al entrar
    do{
        //Definicion del mazo de 52 cartas y las manos de 5 cartas para cada uno
        Carta mazo[52];
        Carta manoJugador[5];
        Carta manoMaquina[5];

        int posicionMazo = 0;           //Indice para saber por qué carta del mazo vamos

        //LLamamos a RealizarApuesta pasandole el puntero del saldo
        //La funcion valida si alcanza el dinero y descuenta el monto apostado
        float montoApostado = RealizarApuesta(saldo, apuestaMinima);

        //Si montoApostado devuelve 0.0, significa que el jugador no tenia saldo
        //suficiente o canceló. Usamos return para abortar la partida e ir al menu

        if(montoApostado == 0.0f){
            return;
        }

        //Se cargan las 52 cartas ordenadas y luego se desordenan de forma aleatoria
        InicializarMazo(mazo);
        MezclarMazo(mazo);

        //Repartimos 5 cartas iniciales a cada participante
        //Pasamos &PosicionMazo por referencia para qye avance progresivamente
        RepartirMano(mazo, manoJugador, &posicionMazo);
        RepartirMano(mazo, manoMaquina, &posicionMazo);

        //Mostramos las cartas iniciales al usuario
        MostrarMano(manoJugador,5, "Jugador");
        int jugadaInicial = EvaluarMano(manoJugador);
        printf("-> Tu jugada: %s\n", NOMBRES_JUGADAS[jugadaInicial]);

        //El usuario elige de 0 a 5 cartas para reponer del mazo
        DescartarJugador(manoJugador, mazo, &posicionMazo);

        //La maquina evalua automaticamente que cartas le conviene cambiar
        DescartarMaquina(manoMaquina, mazo, &posicionMazo);


        //Mostramos la mano definitiva del jugador tras el descarte
        MostrarMano(manoJugador,5, "Jugador (Mano Final)");
        int jugadaFinal = EvaluarMano(manoJugador);
        printf("-> Tu jugada final: %s\n", NOMBRES_JUGADAS[jugadaFinal]);

        //Imprime la mano de la maquina y declara el resultado de la partida
        DeterminarGanador(manoJugador,manoMaquina);

        //Corregido: Logica de cobro alineada con el resultado real
        int catJugador = EvaluarMano(manoJugador);
        int catMaquina = EvaluarMano(manoMaquina);
        int valJugador = ObtenerValorCombinacion(manoJugador, catJugador);
        int valMaquina = ObtenerValorCombinacion(manoMaquina, catMaquina);

        //Resolucion de saldos segun el resultado
        if((catJugador > catMaquina)||(catJugador == catMaquina)&&(valJugador > valMaquina)){
            float premio = montoApostado*2;
            *saldo += premio;
            printf("\n[$$$] ¡Ganaste $%.2f! Tu saldo es: $%.2f\n",premio, *saldo);
        }else if((catMaquina > catJugador)||(catJugador == catMaquina)&&(valMaquina > valJugador)){
            printf("\n[-] Perdiste $%.2f. Tu saldo actual es: $%.2f\n", montoApostado, *saldo);
        }else{
            int desempate = DesempatarManos(manoJugador, manoMaquina);
            if(desempate == 1){
                float premio = montoApostado * 2;
                *saldo += premio;
                printf("\n[$$$] ¡Ganaste el desempate y te llevas $%.2f! Saldo actual: $%.2f\n", premio, *saldo);
            }else if(desempate == 2){
                printf("\n[-] Perdiste el desempate de $%.2f. Saldo actual: $%.2f\n", montoApostado, *saldo);
            }else{
                *saldo += montoApostado;
                printf("\n[=] Empate absoluto. Se te devuelve la apuesta de $%.2f. Saldo actual: $%.2f\n", montoApostado, *saldo);
            }
        }

        //Consulta para continuar o salir de la mesa
        //Verificamos si al jugador le alcanza el saldo para volver a jugar
        if(*saldo >= apuestaMinima){
            do{
                printf("\n¿Quieres jugar otra mano? (1. Si / 2. No): ");

                if(!LeerEnteroValido(&opcionBucle)){
                    opcionBucle = 0;
                }

                if((opcionBucle != 1)&&(opcionBucle != 2)){
                    printf("[X] Error: Ingrese solo 1 para Si o 2 para No.\n");
                }
            }while((opcionBucle != 1)&&(opcionBucle != 2));

        }else{
            //Si el saldo no alcanza, mostramos mensaje y forzamos la salida del ciclo
            printf("\n[!] Tu saldo ($%.2f) es menor a la apuesta minima ($%.2f). Regresando al menu...\n",*saldo,apuestaMinima);
            printf("Presiona ENTER para continuar...");
            getchar();
            opcionBucle = 2; //Rompe la condicion del do-while
        }

    //El ciclo se repite solo si la variable opcionBucle quedo cargada con el numero 1
    }while(opcionBucle == 1);
}
