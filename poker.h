#ifndef POKER_H
#define POKER_H

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>



typedef struct {
    int valor; // 1 (As), 2 al 10, 11 (J), 12 (Q), 13 (K)
    int palo;  // 0: Corazones, 1: Diamantes, 2: Treboles, 3: Picas
} Carta_t;

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
} OpcionesPoker_t;

// ============================================================================
// PROTOTIPOS DE FUNCIONES - FLUJO DE JUEGO Y MENUS
// ============================================================================

void MenuJuegoPoker(Usuario_t  *usuario);
void ReglasDelPoker(void);
void JugarPartidaPoker(Usuario_t *usuario);
float RealizarApuesta(float *saldo, float apuestaMinima);

// ============================================================================
// PROTOTIPOS DE FUNCIONES - GESTION DEL MAZO Y CARTAS
// ============================================================================

void InicializarMazo(Carta_t mazo[]);
void MezclarMazo(Carta_t mazo[]);
void MostrarMano(Carta_t mano[], int cantidad, const char *nombreJugador);
void RepartirMano(Carta_t mazo[], Carta_t mano[], int *posicionMazo);

// ============================================================================
// PROTOTIPOS DE FUNCIONES - LOGICA Y EVALUACION DE MANOS
// ============================================================================

void DescartarJugador(Carta_t mano[], Carta_t mazo[], int *posicionMazo);
void DescartarMaquina(Carta_t mano[], Carta_t mazo[], int *posicionMazo);
int EvaluarMano(Carta_t mano[]);
void DeterminarGanador(Carta_t manoJugador[], Carta_t manoMaquina[]);
void OrdenarMano(Carta_t mano[]);
int DesempatarManos(Carta_t manoJugador[], Carta_t manoMaquina[]);
int ObtenerValorVirtual(int valor);
int ObtenerValorCombinacion(Carta_t mano[], int jerarquia);
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
