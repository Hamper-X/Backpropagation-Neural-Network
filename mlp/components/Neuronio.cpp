#include "Neuronio.h"
#include "../utils/Utils.h"

/*********************** CLASSE NEURONIO ****************************/

Neuronio::Neuronio(){}

/*********************************************************
  Inicializa o N�mero de Pesos e tamb�m os valores
  iniciais dos pesos
 *********************************************************/
void Neuronio ::Inicializar_Neuronio(int Numero_Pesos)
{
	int i, p, q;

	this->Numero_Pesos = Numero_Pesos;

	srand(time(NULL));
	#pragma omp parallel for private(i) schedule(dynamic,100)
	for (i = 0; i < Numero_Pesos; i++)
	{
		p = (rand() % 11) / 10.0;
		q = (rand() % 3) - 1;
		W[i] = (double)(p * q);
	}
}

/*********************************************************
  Multilica o Erro da sa�da de um neur�nio por um Peso de
  Indice_Peso
 *********************************************************/
double Neuronio ::Erro_Peso(double Erro, int Indice_Peso)
{
	return (Erro * W[Indice_Peso]);
}

/*********************************************************
  Dada uma entrada, retorna a sa�da do neur�nio
  multiplicando-a pelos pesos
 *********************************************************/
double Neuronio ::Somatorio(double Entrada[])
{
	double Soma = 0;
	#pragma omp simd reduction(+:Soma)
	for (int i = 0; i < Numero_Pesos; i++)
		Soma += (Entrada[i] * W[i]);

	return Soma;
}

/*********************************************************
  Dado o erro da camada da frente, a sa�da do neur�nio,
  e Indice do Peso, calcula-se o novo peso
 *********************************************************/
void Neuronio ::Ajustar_Peso(double Entrada, double Erro, int Indice_Peso)
{
	W[Indice_Peso] += Utils::BETA * Erro * Entrada;
}