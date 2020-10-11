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
	int Numero_Neuronio_Camada[NUMNEU];
	int i;

	time_t inicio, fim;

	double Entrada [NUMIN][2];
	double Saida[NUMIN];

	char Continua = 'r';
	Rede R;
	Utils u;

	Numero_Linhas_Entrada = NUMIN;
	Numero_Linhas_Saida = NUMIN;
	
	while (Continua != 'n')
	{
		limpar_tela();

		if (Continua == 'r')
		{
			// cout << "\n\nDigite o numero de camadas: ";
			// cin >> Numero_Camadas;
			Numero_Camadas = NUMCAM;
			
			// OK
			R.Inicializar_Rede(
					Numero_Camadas,
					Numero_Linhas_Entrada,
					Numero_Linhas_Saida);

			time(&inicio); // tempo inicio
			R.Treinar();
			time(&fim); //tempo fim
		}

		cout << "\n\nDigite as entradas da rede:\n";

		int a, b;
		for (i = 0; i < NUMIN; i++)
		{
			cout << "\nEntrada " << i << " : ";
			cin >> a >> b; 
			Entrada[i][0] = a;
			Entrada[i][1] = b;
		}

		R.Calcular_Resultado(Entrada, Saida);

		for (i = 1; i <= 3; i++)
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
