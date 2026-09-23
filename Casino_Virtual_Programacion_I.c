#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void GestionarSaldo(int*saldo);
void RegistrarJugador(char* usuarioRegistrado, char* contrasenaRegistrado, bool* registrado);
void IniciarSesion(char* usuarioRegistrado, char* contrasenaRegistrado, bool resgitrado, bool* esAdmin, char* usuarioLogueado, bool* loginExitoso);
void MenuAdministrador();
void MenuCasino(char* usuario);
int main(){
    //Variables para las credenciales en la memoria RAM
    char usuarioRegistro[20] = "";
    char contrasenaRegistro[20] = "";
    bool estaRegistrado = false;

    int opcionBienvenida;

    do{
        printf("\n==========================================\n");
        printf("         BIENVENIDO AL CASINO         \n");
        printf("==========================================\n");
        printf("1. Registrarse como nuevo jugador\n");
        printf("2. Iniciar Sesion (Jugadores y Admin)\n");
        printf("3. Salir del programa\n");
        printf("==========================================\n");
        printf("Seleccione una opcion (1-3): ");
        scanf("%d", &opcionBienvenida);

        switch(opcionBienvenida){
            case 1:
                RegistrarJugador(usuarioRegistro, contrasenaRegistro, &estaRegistrado);
                break;
            case 2:{
                bool esAdmin = false;
                bool loginExitoso = false;
                char usuarioLogueado[20] = "";

                IniciarSesion(usuarioRegistro, contrasenaRegistro, estaRegistrado, &esAdmin, usuarioLogueado, &loginExitoso);

                //Si el login fue correcto, derivamos al menu correspondiente
                if(loginExitoso){
                    if(esAdmin){
                        MenuAdministrador();
                    }else{
                        MenuCasino(usuarioLogueado);
                    }
                }
                break;
            }
            case 3:
                printf("\nGracias por usar el sistema del Casino. ¡Hasta luego!\n");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;

        }
    }while(opcionBienvenida != 3);


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
                break;
            default:
                printf("Por favor ingrese una opcion valida. Presiona ENTER\n");
            break;
        }


    }while (opSaldo != 2);

} //Fin de la logica de Cargar Fichas.

//Inicio de la logica del Usuario

//Registro para jugadores
void RegistrarJugador(char* usuarioRegistro, char* contrasenaRegistro, bool* registrado){
    //Declarar variables de registro
    int edad;

    //REGISTRO DE USUARIO

    printf("=== REGISTRO DE NUEVO USUARIO ===\n");

    printf("Ingrese su edad:\n");
    scanf("%d",&edad);

    //Validamos que sea mayor de 17 años
    while((edad<18)||(edad>120)){
        printf("Error. Debe ser mayor de 18 años para registrarse.\n");
        printf("Ingrese su edad nuevamente.\n");
        scanf("%d",&edad);
    }


    //Crear las credenciales
    printf("cree un nombre de usuario (sin espacios):\n");
    scanf(" %s",usuarioRegistro);

    printf("Cree una contraseña (sin espacios):\n");
    scanf(" %s",contrasenaRegistro);

    *registrado = true;
    printf("¡Registro completado con exito!\n");


}
//Fin de la logica de Usuario


//Login Universal

void IniciarSesion(char* usuarioRegistrado, char* contrasenaRegistrado, bool registrado, bool* esAdmin, char* usuarioLogueado, bool* loginExitoso){
    char usuarioIngreso[20];
    char contrasenaIngreso[20];

    printf("\n=== INGRESO AL SISTEMA ===\n");
    printf("Usuario:\n ");
    scanf("%s",usuarioIngreso);
    printf("Contraseña:\n ");
    scanf("%s",contrasenaIngreso);

     // Verificación 1: ¿Es el Administrador? (Entra sin registrarse)
    if (strcmp(usuarioIngreso, "admin") == 0 && strcmp(contrasenaIngreso, "1234") == 0) {
        *esAdmin = true;
        *loginExitoso = true;
        strcpy(usuarioLogueado, "Administrador");
        printf("\n=============================================\n");
        printf("   BIENVENIDO AL SISTEMA - MODO ADMIN\n");
        printf("=============================================\n");
        return;
    }

    // Verificación 2: ¿Es un jugador registrado en la RAM?
    if (registrado && strcmp(usuarioIngreso, usuarioRegistrado) == 0 && strcmp(contrasenaIngreso, contrasenaRegistrado) == 0) {
        *esAdmin = false;
        *loginExitoso = true;
        strcpy(usuarioLogueado, usuarioRegistrado);
        printf("\n=============================================\n");
        printf("   BIENVENIDO AL CASINO: %s\n", usuarioLogueado);
        printf("=============================================\n");
        return;
    }

    //si no es ninguno de los dos
    printf("\n[ERROR] Usuario o contraseña incorrectos, o no registrado.\n");
    *loginExitoso = false;



}
//Interfaz para el administrador
void MenuAdministrador(){
    int opcionAdmin;
    do{
        printf("\n=======================================\n");
        printf("     PANEL DE CONTROL - ADMINISTRADOR    \n");
        printf("=========================================\n");
        printf("1. Ver caja total del casino\n");
        printf("2. Modificar porcentaje de ganar de la Ruleta\n");
        printf("3. Expulsar a un jugador\n");
        printf("4. Cerrar sesion de administrador\n");
        printf("=========================================\n");
        printf("Seleccione una opcion (1-4): ");
        scanf("%d",&opcionAdmin);

        switch(opcionAdmin){
            case 1:
                printf("\[ADMIN] La caja actual tiene: $1.500.000 ARS\n");
                break;
            case 2:
                printf("\n[ADMIN] Modificando probabilidades...Configurado\n");
                break;
            case 3:
                printf("\n[ADMIN] Ingrese el nombre del usuario a banear.\n");
                break;
            case 4:
                printf("\nCerrando el panel de administracion....\n");
                break;
            default:
                printf("opcion no valida.\n");
                break;

        }
    }while(opcionAdmin !=4);
}
//Fin de la logica de Administrador

//Menu del casino
void MenuCasino(char* usuario){
    int opcion;
    int saldo = 0;

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
                printf("Entrando a la Ruleta...�Hagan sus apuestas!\n");
                //Aca va la logica de la ruleta
                break;
            case 2:
                printf("Entrando al BlackJack...�Carta o te plantas?\n");
                //Aca va la logica del BlackJack
                break;
            case 3:
                printf("Entrando al Poker...�Suerte!\n");
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

}
//fin del menuCasino
