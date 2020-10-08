/**********************************************************************
 * Algoritmo de treinamento back-propagation para redes multicamadas
 **********************************************************************/

#include <iostream>

#include "./components/Rede.h"
#include "./components/Camada.h"
#include "./components/Neuronio.h"
#include "./utils/constants.h"
#include "./utils/Utils.h"

using namespace std;

int main()
{
	int Numero_Camadas;         // N�mero de camadas da rede
	int Numero_Linhas;          // N�mero de linhas de entrada
	int Numero_Linhas_Entrada; // N�mero de colunas de entrada
	int Numero_Linhas_Saida;   // N�mero de colunas da sa�da
	int Numero_Neuronio_Camada[MAXCAM];
	int i;

	time_t inicio, fim;

	double Entrada[MAXNEU];
	double Saida[MAXNEU];

	char Continua = 'r';
	Rede R;
	Utils u;

	Numero_Linhas = NUMLIN;
	Numero_Linhas_Entrada = NUMCOLENT;
	Numero_Linhas_Saida = NUMCOLSAI;

	while (Continua != 'n')
	{
		limpar_tela();

		if (Continua == 'r')
		{
			cout << "\n\nDigite o numero de camadas: ";
			cin >> Numero_Camadas;

			for (i = 0; i < Numero_Camadas; i++)
			{
				cout << "\n\nDigite o numero de neuronios da camada " << i << " : ";
				cin >> Numero_Neuronio_Camada[i];
			}

			// OK
			R.Inicializar_Rede(
					Numero_Camadas,
					Numero_Linhas,
					Numero_Linhas_Entrada,
					Numero_Linhas_Saida,
					Numero_Neuronio_Camada);

			time(&inicio); // tempo inicio
			R.Treinar();
			time(&fim); //tempo fim
		}

		cout << "\n\nDigite as entradas da rede:\n";

		for (i = 0; i < Numero_Linhas_Entrada; i++)
		{
			cout << "\nEntrada " << i << " : ";
			cin >> Entrada[i];
		}

		R.Calcular_Resultado(Entrada, Saida);

		for (i = 1; i <= Numero_Linhas_Saida; i++)
		{
			cout << "\nSaida " << i << " : " << Saida[i];
		}

		cout << endl;
		double total = double(fim - inicio);
		cout << "Tempo de execução: " << fixed << total << " segundos." << endl << endl;

		cout << "\n\nContinua ? (s/n/r)" << endl;
		cin >> Continua;
	}

	return 0;
}
