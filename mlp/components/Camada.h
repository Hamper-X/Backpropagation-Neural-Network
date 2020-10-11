#pragma once

#include <math.h>
#include <time.h>
#include <utility>
#include <vector>

#include "../utils/constants.h"
#include "Neuronio.h"

using namespace std;

class Camada
{
private:
	int Numero_Pesos;
	double Saida[NUMNEU]; // Sa�da dos neur�nios da camada

public:
	int Numero_Neuronios; // N�mero de neur�nios na camada
	Neuronio N[NUMNEU];	  // Neur�nios da camada
	Camada();
	void Inicializar_Camada(int Numero_Neuronios); // Atribui o n�mero de neur�nios
	void Treinar_Neuronios(double *Entrada, int linha_escolhida);	 // Treina os neur�nios com uma entrada
	void Funcao_Ativacao();											 // Joga sa�da linear na funcao de ativacao
	void Retornar_Saida(double Linha[][2]);							 // Retorna a sa�da dos neur�nios
	void Ajustar_Pesos_Neuronios(double *Erros, double Entrada[][2]);
	void Calcular_Erro_Camada_Saida(double *Erros, double *Y, int linha_escolhida);
	void Calcular_Erro_Camada(double *Erros);
	double Somatorio_Erro(double *Erros);
	void Calcular_Erro_Final(double *Erros, double *Y);
};