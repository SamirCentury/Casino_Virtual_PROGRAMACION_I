// (#ifndef, #define, #endif) evitan que el archivo se lea dos veces al compilar
#ifndef RULETA_H
#define RULETA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes globales del juego
#define NUM_COLORES 37 // Total de casillas en la ruleta europea (0 al 36)
#define MIN_APUESTA 500.0f // Monto minimo requerido para participar en la mesa

// El 'extern' avisa que este vector existe, pero que sus datos reales estan en el archivo .c
extern const char COLORES[NUM_COLORES];

// ==========================================
// FUNCIONES DE INTERFAZ Y DISEÑO
// ==========================================
void MostrarBienvenida(void);
void DibujarPanoRuleta(void);
void AnimarGiroRuleta(int numeroSalio, char colorSalio);

// ==========================================
// FUNCIONES DE INGRESO DE DATOS Y VALIDACIONES
// ==========================================
int MostrarMenuRuleta(void);
float PedirApuesta(float saldoActual);
int PedirNumeroPleno(float *saldo);
char PedirColor(float *saldo);
int PedirParidad(float *saldo);
int PedirFaltaPasa(float *saldo);
int PedirDocena(float *saldo);

// ==========================================
// FUNCIONES DE LOGICA PRINCIPAL
// ==========================================
// Calcula los premios o perdidas segun la eleccion del jugador
void ResolverRonda(int tipo, float monto, float *saldo);
// Bucle principal que mantiene el juego funcionando
void JugarRuleta(float *saldo);

#endif // RULETA_H