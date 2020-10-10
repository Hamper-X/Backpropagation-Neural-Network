#pragma once

#include <utility>
#include <vector>

#include "Camada.h"
#include "../utils/constants.h"

class Rede
{
private:
	int Numero_Camadas;		   // N�mero de camadas da rede
	int Numero_Linhas;		   // N�mero de linhas de entrada
	int Numero_Linhas_Entrada; // N�mero de colunas de entrada
	int Numero_Linhas_Saida;   // N�mero de colunas da sa�da

	Camada C[NUMCAM]; // Camadas da rede

	vector<pair<double, double>> entrada; // vetor com os pares de entrada
	vector<double> saida;				  //vetor de saidas

public:
	Rede();
	void Inicializar_Rede(int, int, int); // Inicializa os valores das vari�veis
	void Treinar();															 // Treina toda a rede
	void Calcular_Resultado(vector<pair<double, double>> &Entrada, vector<double> &Saida);
};