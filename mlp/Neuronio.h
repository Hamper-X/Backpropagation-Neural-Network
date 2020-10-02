#pragma once

#include <math.h>
#include <time.h>

#include "constants.h"

class Neuronio
{
	private:
		int Numero_Pesos; // N�mero de pesos do neur�nio
		double W[MAXPES]; // Vetor de pesos

	public:
		Neuronio();
		void Inicializar_Neuronio(int Numero_Pesos);                     // Inicia os valores dos pesos
		void Ajustar_Peso(double Entrada, double Erro, int Indice_Peso); // Ajusta os valores dos pesos
		double Somatorio(double Entrada[]);                              // Retorna os pesos e quantos s�o
		double Erro_Peso(double Erro, int Indice_Peso);
};