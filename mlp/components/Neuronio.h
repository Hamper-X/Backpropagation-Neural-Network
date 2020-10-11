#pragma once

#include <math.h>
#include <time.h>
#include <vector>

#include "../utils/constants.h"

using namespace std;
class Neuronio
{
	private:
		int Numero_Pesos; // N�mero de pesos do neur�nio
		double W[NUMPES]; // Vetor de pesos

	public:
		Neuronio();
		void Inicializar_Neuronio(int Numero_Pesos);                     // Inicia os valores dos pesos
		void Ajustar_Peso(double Entrada, double Erro, int Indice_Peso); // Ajusta os valores dos pesos
		double Somatorio(double *Entrada);// ANTIGO PAR 2 POS. Retorna os pesos e quantos s�o 
		double Erro_Peso(double Erro, int Indice_Peso);
};