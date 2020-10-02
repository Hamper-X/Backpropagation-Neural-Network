#pragma once

#include "Camada.h"
#include "../utils/constants.h"

class Rede
{
	private:
		int Numero_Camadas;         // N�mero de camadas da rede
		int Numero_Linhas;          // N�mero de linhas de entrada
		int Numero_Colunas_Entrada; // N�mero de colunas de entrada
		int Numero_Colunas_Saida;   // N�mero de colunas da sa�da

		Camada C[MAXCAM];         // Camadas da rede
		double X[MAXLIN][MAXCOL]; // Matriz de entrada da rede
		double Y[MAXLIN][MAXCOL]; // Matriz de sa�da da rede

	public:
        Rede();
		void Inicializar_Rede(int, int, int, int, int Numero_Neuronio_Camada[]); // Inicializa os valores das vari�veis
		void Treinar();                                                          // Treina toda a rede
		void Calcular_Resultado(double Entrada[], double Saida[]);
};