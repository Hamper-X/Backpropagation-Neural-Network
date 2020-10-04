#include <utility>
#include "Camada.h"

/*********************** CLASSE CAMADA ****************************/

Camada::Camada() {}

/*********************************************************
  Inicializa o Numero de Neuronios e o Numero de Pesos
  e invoca a inicializa��o dos neur�nios
 *********************************************************/
void Camada ::Inicializar_Camada(int Numero_Neuronios, int Numero_Pesos)
{
	int i;

	this->Numero_Neuronios = Numero_Neuronios;
	this->Numero_Pesos = Numero_Pesos;

	for (i = 0; i < Numero_Neuronios; i++)
		N[i].Inicializar_Neuronio(Numero_Pesos);
}

/*********************************************************
  Calcula os erros da camada de sa�da com base na sa�da
  desejada Y, retornando os erros
 *********************************************************/
void Camada ::Calcular_Erro_Final(double Erros[], double Y[])
{
	int i;

	//#pragma omp parallel for private(i)
	for (i = 0; i < Numero_Neuronios; i++)
		Erros[i] = (Y[i] - Saida[i]);
}

/*********************************************************
  Dispara o somat�rio de um neur�nio para uma certa entrada
  armazenando a sua sa�da
 *********************************************************/
void Camada ::Treinar_Neuronios(vector <pair <double, double>>Entrada[])
{
	//#pragma omp parallel for schedule(dynamic,100)
	for (int i = 0; i < Numero_Neuronios; i++)
		Saida[i] = N[i].Somatorio(Entrada);
}

/*********************************************************
  Calcula os erros da camada de sa�da com base na sa�da
  desejada Y, retornando os erros
 *********************************************************/
void Camada ::Calcular_Erro_Camada_Saida(double Erros[], double Y[])
{
	int i;
	//#pragma omp parallel for private(i) schedule(dynamic)
	for (i = 0; i < Numero_Neuronios; i++)
		Erros[i] = (Y[i] - Saida[i]) * Saida[i] * (1 - Saida[i]);
}

/*********************************************************
  Calcula os erros da camada escondida com base no erro
  da camada da frente, retornando os erros
 *********************************************************/
void Camada ::Calcular_Erro_Camada(double Erros[])
{
	int i;

	//#pragma omp parallel for private(i) schedule(dynamic)
	for (i = 0; i < Numero_Neuronios; i++)
		Erros[i] = Saida[i] * (1 - Saida[i]) * Erros[i];
}

/*********************************************************
  Ajusta os pesos dos neur�nios da camada de acordo com os
  erros da camada da frente, e retorna o som�r�rio de erros
  da pr�pria camada
 *********************************************************/
void Camada ::Ajustar_Pesos_Neuronios(double Erros[], double Entrada[])
{
	int i, j;
	double Temp, Erro_Aux[MAXNEU];

	/* C�lculo do Somat�rio que ser� usado para o c�lculo do erro
	   da camada anterior */

	//#pragma omp parallel for private(i, j) schedule(dynamic) reduction (+:Temp)
	//#pragma omp parallel for private(i, j) schedule(dynamic)
	for (i = 1; i < Numero_Pesos; i++)
	{
		Temp = 0;
		for (j = 0; j < Numero_Neuronios; j++)
		{
			Temp += N[j].Erro_Peso(Erros[j], i);
		}
		Erro_Aux[i - 1] = Temp;
	}

	/* Ajusta os pesos de cada neur�nio  de acordo com o erro
	   da camada da frente e a sa�da da pr�pria camada */

	for (i = 0; i < Numero_Neuronios; i++)
		for (j = 0; j < Numero_Pesos; j++)
			N[i].Ajustar_Peso(Entrada[j], Erros[i], j);

	/* Atribui o vetor de erros calculado, para o vetor erro
	   que ser� retornado */

	for (i = 0; i < (Numero_Pesos - 1); i++)
		Erros[i] = Erro_Aux[i];
}

/*********************************************************
  Atualiza a sa�da da camada passando-a por uma fun��o
  de ativa��o
 *********************************************************/
void Camada ::Funcao_Ativacao()
{
	int i;

	//#pragma omp parallel for private(i)
	for (i = 0; i < Numero_Neuronios; i++)
		Saida[i] = 1 / (1 + exp(-Saida[i]));
}

/*********************************************************
  Retorna a Sa�da da Camada
 *********************************************************/
void Camada ::Retornar_Saida(double Linha[])
{
	int i;

	Linha[0] = 1;
	//#pragma omp parallel for private(i)
	for (i = 1; i <= Numero_Neuronios; i++)
		Linha[i] = Saida[i - 1];
}