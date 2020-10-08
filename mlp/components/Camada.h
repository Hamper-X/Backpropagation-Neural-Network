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
	int Numero_Neuronios; // N�mero de neur�nios na camada
	int Numero_Pesos;
	double Saida[MAXNEU]; // Sa�da dos neur�nios da camada
	Neuronio N[MAXNEU];	  // Neur�nios da camada

public:
	Camada();
	void Inicializar_Camada(int Numero_Neuronios, int Numero_Pesos); // Atribui o n�mero de neur�nios
	void Treinar_Neuronios(vector<pair<double, double>> &Entrada);	 // Treina os neur�nios com uma entrada
	void Funcao_Ativacao();											 // Joga sa�da linear na funcao de ativacao
	void Retornar_Saida(vector<pair<double, double>> &Linha);							 // Retorna a sa�da dos neur�nios
	void Ajustar_Pesos_Neuronios(double Erros[], vector<pair<double, double>> Entrada);
	void Calcular_Erro_Camada_Saida(double Erros[], vector<double> &Y);
	void Calcular_Erro_Camada(double Erros[]);
	double Somatorio_Erro(double Erros[]);
	void Calcular_Erro_Final(double Erros[], double Y[]);
};