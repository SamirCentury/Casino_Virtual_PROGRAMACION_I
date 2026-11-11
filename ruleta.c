#include "ruleta.h"
#include "main.h"
#include "poker.h"

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
    system("clear || cls");
    printf("\n" T_AMARILLO "╔═════════════════════════════════════════════════╗\n");
    printf("║         " T_ROJO " ♠ ♥ BENVENIDOS AL SALÓN VIP ♦ ♣ " T_AMARILLO "       ║\n");
    printf("║                 " T_VERDE "JUEGO DE LA RULETA" T_AMARILLO "              ║\n");
    printf("╚═════════════════════════════════════════════════╝" T_RESET "\n");
    Sleep(2000);
}

void DibujarPanoRuleta(void) {
    system("clear || cls");
    printf("\n" T_AMARILLO "==========================================================================\n");
    printf(T_VERDE "                         PANEL DE LA RULETA EUROPEA                       \n");
    printf(T_AMARILLO "==========================================================================\n" T_RESET);
    printf("  " T_AMARILLO "+-----+---------------------------------------------------------------+\n");
    printf("  |     | " T_ROJO "[ 3R]" T_BLANCO " [ 6N] " T_ROJO "[ 9R]" T_ROJO " [12R]" T_BLANCO " [15N] " T_ROJO "[18R] " T_ROJO "[21R] " T_BLANCO "[24N] " T_ROJO "[27R] " T_ROJO "[30R] " T_BLANCO "[33N] " T_ROJO "[36R] " T_AMARILLO "|\n");
    printf("  |     |---------------------------------------------------------------|\n");
    printf("  | " T_VERDE "0 V" T_AMARILLO " | " T_BLANCO "[ 2N] " T_ROJO "[ 5R] " T_BLANCO "[ 8N] " T_BLANCO "[11N] " T_ROJO "[14R] " T_BLANCO "[17N] " T_BLANCO "[20N] " T_ROJO "[23R] " T_BLANCO "[26N] " T_BLANCO "[29N] " T_ROJO "[32R] " T_BLANCO "[35N] " T_AMARILLO "|\n");
    printf("  |     |---------------------------------------------------------------|\n");
    printf("  |     | " T_ROJO "[ 1R]" T_BLANCO " [ 4N] " T_ROJO "[ 7R] " T_BLANCO "[10N] " T_BLANCO "[13N] " T_ROJO "[16R] " T_ROJO "[19R] " T_BLANCO "[22N] " T_ROJO "[25R] " T_BLANCO "[28N] " T_BLANCO "[31N] " T_ROJO "[34R] " T_AMARILLO "|\n");
    printf("  " T_AMARILLO "+-----+---------------------------------------------------------------+\n");
    printf("        | " T_CIAN "         1ra DOCENA           " T_AMARILLO "|" T_CIAN "          2da DOCENA           " T_AMARILLO "|" T_CIAN "          3ra DOCENA           " T_AMARILLO "|\n");
    printf("        | " T_BLANCO "           (1 - 12)           " T_AMARILLO "|" T_BLANCO "           (13 - 24)           " T_AMARILLO "|" T_BLANCO "           (25 - 36)           " T_AMARILLO "|\n");
    printf("        " T_AMARILLO "+-------------------------------+-------------------------------+-------------------------------+\n");
    printf("        |    1 - 18     |      PAR      |     ROJO      |     NEGRO     |     IMPAR     |    19 - 36    |\n");
    printf("        " T_AMARILLO "+---------------+---------------+---------------+---------------+---------------+---------------+\n");
    printf("  " T_BLANCO "Referencias: " T_ROJO "[R] = Rojo " T_BLANCO "| " T_BLANCO "[N] = Negro " T_VERDE "| [V] = Verde (0)\n");
    printf(T_AMARILLO "==========================================================================\n" T_RESET);
}

// ============================================================================
// ANIMACIÓN DE GIRO PARA LA RULETA
// ============================================================================
void AnimarGiroRuleta(int numeroSalio, char colorSalio) {
    // Efecto visual de giro rápido (simulando la bola saltando por los casilleros)
    for (int i = 0; i < 18; i++) {
        system("clear || cls");
        int tempNum = rand() % 37;
        char tempCol = COLORES[tempNum];
        
        printf("\n" T_AMARILLO "╔═════════════════════════════════════════════════╗\n");
        printf("║         " T_CIAN " 🎰 GIRANDO LA RULETA VIP 🎰 " T_AMARILLO "            ║\n");
        printf("╠═════════════════════════════════════════════════╣\n");
        printf("║                                                 ║\n");
        printf("               Buscando la suerte...               \n");
        printf("                  [ " T_BLANCO "%2d" T_AMARILLO " (%c) ]                   \n", tempNum, tempCol);
        printf("║                                                 ║\n");
        printf("╚═════════════════════════════════════════════════╝\n" T_RESET);
        
        // El tiempo de pausa va aumentando levemente para simular que la bola frena
        Sleep(80 + (i * 15)); 
    }

    // Pantalla final con el resultado ganador enmarcado y colores oficiales
    system("clear || cls");
    
    char *colorTexto = (colorSalio == 'R') ? T_ROJO : ((colorSalio == 'N') ? T_BLANCO : T_VERDE);
    // Nota: si T_VERdes fue un typo, usamos T_VERDE abajo de forma segura:
    // (Usamos T_VERDE para verde, T_ROJO para rojo, T_BLANCO para negro)
    
    printf("\n" T_AMARILLO "╔═════════════════════════════════════════════════╗\n");
    printf("║         " T_VERDE " ✔ ¡LA BOLA SE HA DETENIDO! ✔ " T_AMARILLO "          ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║       NÚMERO GANADOR : " T_CIAN "[ %2d ]" T_AMARILLO "                     \n", numeroSalio);
    
    // Mostramos el color con su respectivo tinte
    if (colorSalio == 'R') {
        printf("        COLOR          : " T_ROJO "[ R - ROJO ]" T_AMARILLO "                \n");
    } else if (colorSalio == 'N') {
        printf("        COLOR          : " T_BLANCO "[ N - NEGRO ]" T_AMARILLO "               \n");
    } else {
        printf("        COLOR          : " T_VERDE "[ V - VERDE ]" T_AMARILLO "              \n");
    }
    
    printf("║                                                 ║\n");
    printf("╚═════════════════════════════════════════════════╝\n" T_RESET);
    
    Sleep(1500); // Pausa para que el usuario asimile el resultado
}

int MostrarMenuRuleta(void) {
    int opcion;
    do {
       printf("\n" T_AMARILLO "╔════════════════════════════════════════════════════════════════╗\n");
        printf("║                 " T_VERDE "MESA DE RULETA EUROPEA VIP" T_AMARILLO "                     ║\n");
        printf("╠════════════════════════════════════════════════════════════════╣\n");
        printf("║ " T_CIAN "[%d]" T_BLANCO " Apostar a Pleno (Numero exacto)      " T_AMARILLO "[Paga 35:1]           ║\n", OPC_APOSTAR_PLENO);
        printf("║ " T_CIAN "[%d]" T_BLANCO " Apostar a Color (Rojo o Negro)       " T_AMARILLO "[Paga 1:1]            ║\n", OPC_APOSTAR_COLOR);
        printf("║ " T_CIAN "[%d]" T_BLANCO " Apostar Par o Impar                  " T_AMARILLO "[Paga 1:1]            ║\n", OPC_APOSTAR_PARIDAD);
        printf("║ " T_CIAN "[%d]" T_BLANCO " Apostar Falta (1-18) / Pasa (19-36)  " T_AMARILLO "[Paga 1:1]            ║\n", OPC_APOSTAR_FALTA);
        printf("║ " T_CIAN "[%d]" T_BLANCO " Apostar Docenas (1-12, 13-24, 25-36) " T_AMARILLO "[Paga 2:1]            ║\n", OPC_APOSTAR_DOCENA);
        printf("║ " T_CIAN "[%d]" T_ROJO " Salir de la Ruleta                                         " T_AMARILLO "║\n", OPC_SALIR_MENU_RULETA);
        printf("╚════════════════════════════════════════════════════════════════╝\n" T_RESET);
        printf(" Seleccione una opcion (%d-%d): ", OPC_APOSTAR_PLENO, OPC_SALIR_MENU_RULETA);

        // Verifica si scanf no pudo leer un numero
       if(!LeerEnteroValido(&opcion)){
        opcion = 0; //Fuerza un valor inválido para repetir el bucle
        printf(T_ROJO "[X] Error: Ingrese un numero entero valido." T_RESET "\n");
        Sleep(1500);
       }else if(opcion < OPC_APOSTAR_PLENO || opcion > OPC_SALIR_MENU_RULETA){
        printf(T_ROJO "[X] Error: Ingrese una opcion entre %d y %d." T_RESET "\n", OPC_APOSTAR_PLENO, OPC_SALIR_MENU_RULETA);
        Sleep(1500);
       }

    } while (opcion < OPC_APOSTAR_PLENO || opcion > OPC_SALIR_MENU_RULETA);
    return opcion;
}

float PedirApuesta(float saldoActual) {
    float monto;

    // Protección de la caja del casino
    if (cajaCasino <= 0.0f) {
        system("clear || cls");
        printf("\n" T_ROJO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║         [!] MESA DE RULETA CERRADA TEMPORALMENTE          ║\n");
        printf("╠═══════════════════════════════════════════════════════════╣\n");
        printf("  La banca del casino se encuentra sin fondos (Caja: $%.2f)  \n", cajaCasino);
        printf("  No hay respaldo para pagar premios en este momento.       \n");
        printf("╚═══════════════════════════════════════════════════════════╝" T_RESET "\n");
        printf("Presione ENTER para regresar al menú...");
        while(getchar() != '\n');
        getchar();
        return 0.0f;
    }

    do {
       
        system("clear || cls");
        printf("\n" T_AMARILLO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║               " T_VERDE "  🪙 MESA DE APUESTAS DE RULETA 🪙 " T_AMARILLO "           ║\n");
        printf("╠═══════════════════════════════════════════════════════════╣\n");
        printf("  " T_VERDE " 💵 Saldo Disponible : " T_AMARILLO "$%-22.2f " T_AMARILLO "            \n", saldoActual);
        printf("  " T_CIAN " 📌 Apuesta Mínima   : " T_AMARILLO "$%-22.2f " T_AMARILLO "            \n", MIN_APUESTA);
        printf("╚═══════════════════════════════════════════════════════════╝\n");
        printf(" " T_BLANCO "Ingrese monto a apostar: " T_VERDE "$" T_RESET);

        if (!LeerFloatValido(&monto)){
            monto = -1.0f; // Fuerza repetir si ingresan letras o caracteres extra
            printf("\n" T_ROJO "[X] Error: Ingrese un numero valido." T_RESET "\n");
            Sleep(1500);
        }
        else if (monto < MIN_APUESTA) {
           printf("\n" T_ROJO "[X] La apuesta debe ser mayor o igual a $%0.2f" T_RESET "\n", MIN_APUESTA);
            Sleep(1500);
        }
        else if (monto > saldoActual) {
            printf("\n" T_ROJO "[X] No puedes apostar mas fichas de las que tienes." T_RESET "\n");
            Sleep(1500);
        }

    } while (monto < MIN_APUESTA || monto > saldoActual);
    return monto;

}

int PedirNumeroPleno(float *saldo) {
    int numeroElegido = -1;

    do {
        
        printf(T_BLANCO "Elija un numero " T_AMARILLO "(0 al 36)" T_BLANCO ": " T_RESET);

        if (!LeerEnteroValido(&numeroElegido)){
            numeroElegido = -1;
           printf(T_ROJO "[X] Error: Ingrese un numero valido." T_RESET "\n");
        }
        else if (numeroElegido < 0 || numeroElegido > 36) {
           printf(T_ROJO "[X] Error: Numero fuera de rango (0-36)." T_RESET "\n"); 
        }
    } while (numeroElegido < 0 || numeroElegido > 36);

    return numeroElegido;
}

char PedirColor(float *saldo) {
    char colorElegido;
    int entradaValida = 0;

    do {
        printf(T_BLANCO "Elija color " T_AMARILLO "('R' para Rojo / 'N' para Negro)" T_BLANCO ": " T_RESET);
        
        // Leemos el carácter de forma segura dejando un espacio antes del %c para limpiar espacios residuales
        if (scanf(" %c", &colorElegido) != 1) {
            printf(T_ROJO "[X] Error de lectura." T_RESET "\n");
            while (getchar() != '\n'); // Limpia el búfer
            continue;
        }
        // Verifica que el usuario ingrese R o N (mayuscula o minuscula)
        if (colorElegido == 'r' || colorElegido == 'R' || colorElegido == 'n' || colorElegido == 'N') {
            entradaValida = 1;
        }else{
            printf(T_ROJO "[X] Error: Ingrese solo 'R' o 'N'." T_RESET "\n");
            entradaValida = 0;
        }

        //Limpiamos cualquier caracter sobrante que haya quedado en la linea (por si escribieron una palabra entera como "ROJO")
        while (getchar() != '\n');
    } while (!entradaValida);

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
        printf(T_BLANCO "Elija paridad " T_AMARILLO "(1: Par / 2: Impar)" T_BLANCO ": " T_RESET);

        if (!LeerEnteroValido(&paridadElegida)){
            paridadElegida = 0;
            printf(T_ROJO "[X] Error: Ingrese un numero valido." T_RESET "\n");
        }
        else if (paridadElegida != 1 && paridadElegida != 2) {
            printf(T_ROJO "[X] Error: Ingrese 1 para Par o 2 para Impar" T_RESET "\n");
        }
    } while (paridadElegida != 1 && paridadElegida != 2);
    return paridadElegida;
}

int PedirFaltaPasa(float *saldo) {
    int rangoElegido;

    do {
        //printf("Saldo en mesa: $%.2f\n", *saldo);
       printf(T_BLANCO "Elija rango " T_AMARILLO "(1: Falta [1-18] / 2: Pasa [19-36])" T_BLANCO ": " T_RESET);
        if (!LeerEnteroValido(&rangoElegido)){
            printf(T_ROJO "[X] Error: Ingrese un numero valido." T_RESET "\n");
            rangoElegido = 0;
        }
        else if (rangoElegido != 1 && rangoElegido != 2) {
            printf(T_ROJO "[X] Error: Ingrese 1 para Falta o 2 para Pasa" T_RESET "\n");
        }
    } while (rangoElegido != 1 && rangoElegido != 2);
    return rangoElegido;
}

int PedirDocena(float *saldo) {
    int docenaElegida;

    do {
        //printf("Saldo en mesa: $%.2f\n", *saldo);
        printf(T_BLANCO "Elija la docena " T_AMARILLO "(1: 1-12 / 2: 13-24 / 3: 25-36)" T_BLANCO ": " T_RESET);
        if (!LeerEnteroValido(&docenaElegida)){
            printf(T_ROJO "[X] Error: Ingrese un numero valido." T_RESET "\n");
            docenaElegida = 0;
        }
        else if (docenaElegida < 1 || docenaElegida > 3) {
            printf(T_ROJO "[X] Error: Ingrese un numero entre 1 y 3" T_RESET "\n");
        }
    } while (docenaElegida < 1 || docenaElegida > 3);
    return docenaElegida;
}


void ResolverRonda(int tipo, Usuario_t *usuario) {
    // Variables para guardar lo que eligio el usuario segun el tipo de apuesta
    int numElegido = -1, paridadElegida = 0, rangoElegido = 0, docenaElegida = 0;
    char colElegido = ' ';

    // 1. Llama a la funcion correspondiente para pedirle el pronostico al jugador
    switch (tipo) {
        case OPC_APOSTAR_PLENO:
            numElegido = PedirNumeroPleno(&(usuario->saldo));
            break;
        case OPC_APOSTAR_COLOR:
            colElegido = PedirColor(&(usuario->saldo));
            break;
        case OPC_APOSTAR_PARIDAD:
            paridadElegida = PedirParidad(&(usuario->saldo));
            break;
        case OPC_APOSTAR_FALTA:
            rangoElegido = PedirFaltaPasa(&(usuario->saldo));
            break;
        case OPC_APOSTAR_DOCENA:
            docenaElegida = PedirDocena(&(usuario->saldo));
            break;
    }

    // 2. Una vez que ya eligió a qué apuesta, le pedimos el monto con su saldo actual actualizado
    float monto = PedirApuesta(usuario->saldo);

    //Si la funcion de apuesta devolvio 0.0 (porque la caja estaba en cero), salimos 
    if(monto == 0.0f){
        return;
    }

    //Blindaje contable: verificar respaldo para el premio 
    float maxPremio = 0.0f;
    if(tipo == OPC_APOSTAR_PLENO){
        maxPremio = monto * 35.0f; //el pleno paga 35:1
    }else if(tipo == OPC_APOSTAR_DOCENA){
        maxPremio = monto * 2.0f;  //las docenas pagan 2:1
    }else{
        maxPremio = monto * 1.0f; //color, paridad y falta/pasa pagan 1:1
    }

    if (cajaCasino < maxPremio) {
        system("clear || cls");
        printf("\n" T_ROJO "╔═══════════════════════════════════════════════════════════╗\n");
        printf("║         [!] BANCA SIN ESPALDA PARA ESTE PREMIO [!]        ║\n");
        printf("╠═══════════════════════════════════════════════════════════╣\n");
        printf("  Premio potencial requerido : " T_AMARILLO "$%.2f\n" T_RESET, maxPremio);
        printf("\n" T_ROJO "  La banca no puede respaldar un premio tan alto." T_RESET "\n");
        printf("\n" T_ROJO "╚═══════════════════════════════════════════════════════════╝" T_RESET "\n");
        printf("Presiona ENTER para regresar al menú de la ruleta...");
        while(getchar() != '\n');
        getchar();
        return; // Aborta la ronda de forma segura sin tocar el saldo del usuario
    }

    // 3. Descontamos el monto apostado del saldo del usuario antes de girar
    usuario->saldo -= monto;

    // 4. Genera el numero ganador al azar y busca de que color es
    int numeroSalio = rand() % NUM_COLORES;
    char colSalio = COLORES[numeroSalio];
    AnimarGiroRuleta(numeroSalio, colSalio);

    int ganoRonda = 0; //1 si gana, -1 si pierde
    float premioObtenido = 0.0f;


    // 5. Evalua si el jugador gano o perdio segun el tipo de apuesta que hizo
    switch (tipo) {
        case OPC_APOSTAR_PLENO: // Pleno (35:1)
            if (numElegido == numeroSalio) {
                premioObtenido = monto * 35;
                printf(T_VERDE "¡ACERTASTE EL PLENO! Ganaste $%2.2f" T_RESET "\n", premioObtenido);
                usuario->saldo += (monto + premioObtenido); //Devuelve la apuesta + premio
                ganoRonda = 1;
            } else {
                printf(T_ROJO "No hubo suerte. Perdiste $%2.2f" T_RESET "\n", monto);
                ganoRonda = -1;
            }
            break;

        case OPC_APOSTAR_COLOR: // Color (1:1) - Casilla 0 pierde
            if (numeroSalio != 0 && colElegido == colSalio) {
                premioObtenido = monto;
                printf(T_VERDE "¡ACERTASTE EL COLOR! Ganaste $%2.2f" T_RESET "\n", monto);
                usuario->saldo += (monto + premioObtenido);
                ganoRonda = 1;
            } else {
                printf(T_ROJO "Color incorrecto (o salió el 0). Perdiste $%2.2f" T_RESET "\n", monto);
                ganoRonda = -1;
            }
            break;

        case OPC_APOSTAR_PARIDAD: // Par / Impar (1:1) - Casilla 0 pierde
            if (numeroSalio != 0 && (
                (paridadElegida == 1 && numeroSalio % 2 == 0) ||
                (paridadElegida == 2 && numeroSalio % 2 != 0))) {
                premioObtenido = monto;
                printf(T_VERDE "¡ACERTASTE LA PARIDAD! Ganaste $%2.2f" T_RESET "\n", monto);
                usuario->saldo += (monto + premioObtenido);
                ganoRonda = 1;
            } else {
                printf(T_ROJO "Paridad incorrecta (o salió el 0). Perdiste $%2.2f" T_RESET "\n", monto);
                ganoRonda = -1;
            }
            break;

        case OPC_APOSTAR_FALTA: // Falta (1-18) / Pasa (19-36) (1:1) - Casilla 0 pierde
            if (numeroSalio != 0 && (
                (rangoElegido == 1 && numeroSalio >= 1 && numeroSalio <= 18) ||
                (rangoElegido == 2 && numeroSalio >= 19 && numeroSalio <= 36))) {
                premioObtenido = monto;
                printf(T_VERDE "¡ACERTASTE EL RANGO! Ganaste $%2.2f" T_RESET "\n", monto);
                usuario->saldo += (monto + premioObtenido);
                ganoRonda = 1;
            } else {
                printf(T_ROJO "Rango incorrecto (o salió el 0). Perdiste $%2.2f" T_RESET "\n", monto);
                ganoRonda = -1;
            }
            break;

        case OPC_APOSTAR_DOCENA: // Docenas (2:1) - Casilla 0 pierde
            if (numeroSalio != 0 && (
                (docenaElegida == 1 && numeroSalio >= 1 && numeroSalio <= 12) ||
                (docenaElegida == 2 && numeroSalio >= 13 && numeroSalio <= 24) ||
                (docenaElegida == 3 && numeroSalio >= 25 && numeroSalio <= 36))) {
                premioObtenido = monto * 2;
                printf(T_VERDE "¡ACERTASTE LA DOCENA! Ganaste $%2.2f" T_RESET "\n", premioObtenido);
                usuario->saldo += (monto + premioObtenido); //devuelve la apuesta original + el premio de la casa 
                ganoRonda = 1;
            } else {
                printf(T_ROJO "Docena incorrecta (o salió el 0). Perdiste $%2.2f" T_RESET "\n", monto);
                ganoRonda = -1;
            }
            break;
    }

    //Actualizacion contable sincronizada con la cja del casino y auditoria del admin
    if(ganoRonda == 1){
        //La casa paga el premio neto
        ActualizarCajaCasino(&cajaCasino, premioObtenido, 1);
        usuario->gananciaAdmin -= premioObtenido; //El casino pierde ante el usuario
    }else{
        //Control contable 
        if(usuario->dineroDepositado >= monto){
            //Si pierde plata de su deposito inicial, la caja NOsuma
            //porque ese efectivo ya habia ingresado al cargar saldo
            usuario->dineroDepositado -= monto;
        }else{
            //Si ya gasto su deposito y esta perdiendo ganancias que la casa le pago
            //la caja SI recupera ese efectivo exacto de la ganancia
            float diferenciaGanancia = monto - usuario->dineroDepositado;
            usuario->dineroDepositado = 0;
            ActualizarCajaCasino(&cajaCasino, diferenciaGanancia, -1);
        }

        usuario->gananciaAdmin += monto; //El casino gana ante el usuario
    }

    printf("\n  " T_BLANCO "Presiona ENTER para continuar..." T_RESET);
    while(getchar() != '\n');
    getchar();
}

void JugarRuleta(Usuario_t *usuario) {

    char seguir = 'S';

    MostrarBienvenida();

    // El juego continua mientras el jugador tenga el saldo minimo y quiera seguir
    while (usuario->saldo >= MIN_APUESTA && (seguir == 'S' || seguir == 's')) {
        DibujarPanoRuleta();
        int tipo = MostrarMenuRuleta();

        if (tipo == OPC_SALIR_MENU_RULETA) { 
            break;
        }

        ResolverRonda(tipo, usuario);

        // Si le queda dinero suficiente, le pregunta si quiere otra ronda
        if (usuario->saldo >= MIN_APUESTA) {
            do {
                printf("\n" T_BLANCO "¿Desea jugar otra ronda en la Ruleta? (" T_VERDE "S" T_BLANCO "/" T_ROJO "N" T_BLANCO "): " T_RESET);
                scanf(" %c", &seguir);
                
                // Avisa si pone cualquier otra letra que no sea S o N
                if (seguir != 's' && seguir != 'S' && seguir != 'n' && seguir != 'N') {
                    printf(T_ROJO "Opcion invalida. Ingrese 'S' para si, o 'N' para no." T_RESET "\n");
                }
            } while (seguir != 's' && seguir != 'S' && seguir != 'n' && seguir != 'N');
            
        } else {
            // Si el saldo baja del minimo, lo echa de la mesa
            printf("\n" T_ROJO "Te quedaste sin fichas suficientes en la mesa." T_RESET "\n");
            seguir = 'N';
        }
    }

    // --- PAUSA Y MENSAJE DE DESPEDIDA AGREGADOS ---
    printf("\n" T_AMARILLO "==========================================\n");
    printf(" Te retiras de la Ruleta con: $" T_VERDE "%.2f\n", usuario->saldo);
    printf(T_AMARILLO "==========================================\n" T_RESET);
    Sleep(2000);
}
