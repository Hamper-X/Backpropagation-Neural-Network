#pragma once

// Caso o SO seja windows
#if defined(__MINGW32__) || defined(_MSC_VER) || defined(_WIN32) || defined(WIN32)
#define limpar_input() fflush(stdin)
#define limpar_tela() system("cls")
#include <windows.h>
// Caso o SO seja Linux
#else
#define limpar_input() __fpurge(stdin)
#define limpar_tela() system("clear")
#endif

/************************* DEFINICOES ********************************/
// #define MAXCAM 5   // N�mero m�ximo de camadas
// #define NUMNEU 100 // N�mero m�ximo de neur�nios
// #define MAXPES 100 // N�mero m�ximo de pesos
// #define MAXLIN 100 // N�mero m�ximo de linhas
// #define MAXCOL 20  // N�mero m�ximo de colunas

// #define NUMIN  1000 // Numero maximo de entradas

// #define NUMLIN 10000   // N�mero de Linhas da Matriz de Entrada
// #define NUMCOLENT 8 // N�mero de Colunas da Matriz de Entrada
// #define NUMCOLSAI 5 // N�mero de Colunas de Saida
// #define NUMITE 1    // Numero de Iteracoes

#define NUMCAM 3   // N�mero m�ximo de camadas
#define NUMNEU 2 // N�mero m�ximo de neur�nios
#define NUMPES 2 // N�mero m�ximo de pesos

#define NUMIN 10000 // Numero maximo de entradas

#define NUMITE 1    // Numero de Iteracoes
#define ESC 27

#ifdef  test
#define ITERACOES 1000000
#else
#define ITERACOES 10000000
#endif

#define MI 0.6
#define TOLERANCIA 0.00001 // N�mero de erros consecutivos