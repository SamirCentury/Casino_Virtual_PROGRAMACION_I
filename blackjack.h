#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdbool.h>
#include "poker.h"
#include "main.h"

// Variable global externa de la caja del casino
extern float cajaCasino;

// Permiten asociar nombres legibles a las opciones del menú del juego poker
typedef enum{
    OPC_JUGAR_BLACKJACK = 1,
    OPC_REGLAS_BLACKJACK,
    OPC_SALIR_MENU_BLACKJACK
} OpcionesBlackjack;

// Controla el menu principal del Blackjack
void MenuJuegoBlackjack(Usuario_t *usuario);

// Muestra las reglas del juego
void ReglasBlackjack(void);

//Muestra valores como As y 10
void ImprimirNombreCarta(int carta);

// Devuelve el valor aleatorio de una carta
int RepartirCarta(void);

//Suma los valores de dos cartas
int CalcularPuntos(int carta1, int carta2);

//inicia una partida y reparte las primeras cartas
void IniciarPartida(Usuario_t *usuario);

// Controla el turno de la computadora
int TurnoCrupier(int cartaInicial1, int cartaInicial2);

//Grafico de cartas
void MostrarCartasBlackJack(int cartas[], int cantidad, const char *nombreJugador, int esCrupier);







#endif