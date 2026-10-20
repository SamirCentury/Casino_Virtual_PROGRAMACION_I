#ifndef POKER_H
#define POKER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// ============================================================================
// ESTRUCTURAS Y CONSTANTES GLOBALES
// ============================================================================
// Declaración adelantada para que poker.h reconozca la estructura Usuario de TRAGAMONEDAS.h
typedef struct Usuario{
    char usuario[50];  //Cadena de caracteres para el nombre de usuario
    char clave[50];    //Cadena de caracteres para la contrase�a
    int edad;          //Edad del usuario
    float saldo;       //Diinero disponible en la cuenta
    bool activo;       //Bandera: true = casillero ocupado, false = casillero libre
    bool continuar;   //Bandera para controlar el flujo de los juegos (true = seguir jugando, false = salir)
    float gananciaAdmin; //Rendimiento comercial: cuanto le gano/perdio el casino al usuario
}Usuario;

typedef struct {
    int valor; // 1 (As), 2 al 10, 11 (J), 12 (Q), 13 (K)
    int palo;  // 0: Corazones, 1: Diamantes, 2: Treboles, 3: Picas
} Carta;

// Variable global externa de la caja del casino
extern float cajaCasino;

// Arreglos globales de texto (definidos externamente en poker.c)
extern const char *NOMBRES_PALOS[];
extern const char *NOMBRES_JUGADAS[];

// Permiten asociar nombres legibles a las opciones del menú del juego poker
typedef enum{
    OPC_JUGAR_POKER = 1,
    OPC_REGLAS_POKER,
    OPC_SALIR_MENU_POKER
} OpcionesPoker;

// ============================================================================
// PROTOTIPOS DE FUNCIONES - FLUJO DE JUEGO Y MEN�S
// ============================================================================

void MenuJuegoPoker(Usuario  *usuario);
void ReglasDelPoker(void);
void JugarPartidaPoker(Usuario *usuario);
float RealizarApuesta(float *saldo, float apuestaMinima);

// ============================================================================
// PROTOTIPOS DE FUNCIONES - GESTI�N DEL MAZO Y CARTAS
// ============================================================================

void InicializarMazo(Carta mazo[]);
void MezclarMazo(Carta mazo[]);
void ImprimirCarta(Carta c);
void MostrarMano(Carta mano[], int cantidad, const char *nombreJugador);
void RepartirMano(Carta mazo[], Carta mano[], int *posicionMazo);

// ============================================================================
// PROTOTIPOS DE FUNCIONES - L�GICA Y EVALUACI�N DE MANOS
// ============================================================================

void DescartarJugador(Carta mano[], Carta mazo[], int *posicionMazo);
void DescartarMaquina(Carta mano[], Carta mazo[], int *posicionMazo);
int EvaluarMano(Carta mano[]);
void DeterminarGanador(Carta manoJugador[], Carta manoMaquina[]);
void OrdenarMano(Carta mano[]);
int DesempatarManos(Carta manoJugador[], Carta manoMaquina[]);
int ObtenerValorVirtual(int valor);
int ObtenerValorCombinacion(Carta mano[], int jerarquia);
void ActualizarCajaCasino(float *cajaCasa, float montoApostado, int resultado);

// ============================================================================
// PROTOTIPOS DE FUNCIONES - VALIDACI�N DE ENTRADAS
// ============================================================================

int LeerEnteroValido(int *num);
int LeerFloatValido(float *num);

// ============================================================================
// GRAFICOS DE CARTAS
// ============================================================================
void AnimacionApuesta(int montoApuesta);
void AnimacionMezclando();
void AnimacionBienvenida();
#endif // POKER_H
