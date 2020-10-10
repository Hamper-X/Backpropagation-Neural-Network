
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fstream>

#include "Rede.h"
#include "../utils/Utils.h"

using namespace std;

Rede::Rede() {}

/*********************************************************
  Inicializa todas as vari�veis da rede, inclusive a
  leitura das entradas e sa�das da rede
 *********************************************************/
void Rede ::Inicializar_Rede(int Numero_Camadas, int Numero_Linhas_Entrada,
                             int Numero_Linhas_Saida)
{
    int i, j, a, b;
    FILE *Entrada, *Saida;

    this->Numero_Camadas = Numero_Camadas;
    this->Numero_Linhas_Entrada = Numero_Linhas_Entrada;
    this->Numero_Linhas_Saida = Numero_Linhas_Saida;

    Entrada = fopen("../database/Entrada.txt", "r");
    Saida = fopen("../database/Saida.txt", "r");

    for (i = 0; i < Numero_Linhas_Entrada; i++)
    {
        fread(&a, sizeof(double), 1, Entrada);
        fread(&b, sizeof(double), 1, Entrada);
        entrada.push_back(make_pair(a, b));
    }

    for (i = 0; i < Numero_Linhas_Entrada; i++)
    {
        fread(&a, sizeof(double), 1, Saida);
        saida.push_back(a);
    }

    fclose(Entrada);
    fclose(Saida);
    //camada intermediária padrão
    C[0].Inicializar_Camada(2); // OK

    // Camadas intermediárias
    for (i = 1; i < Numero_Camadas; i++)
        C[i].Inicializar_Camada(2);

    //C[i].Inicializar_Camada(Numero_Neuronio_Camada[i], (Numero_Neuronio_Camada[i - 1] + 1));
}

/*********************************************************
  Calcula a resposta da rede para uma certa entrada,
  retornando a sa�da
 *********************************************************/
void Rede ::Calcular_Resultado(vector<pair<double, double>> &Entrada, vector<double> &Saida)
{
    int i, j;
    vector<pair<double, double>> saidaAux;
    int Camada_Saida = Numero_Camadas - 1;

    for (i = 0; i < Numero_Camadas; i++)
    {
        C[i].Treinar_Neuronios(Entrada);
        C[i].Funcao_Ativacao();
        C[i].Retornar_Saida(saidaAux);

        for (j = 0; j < NUMNEU; j++)
            Entrada[j] = saidaAux[j];
    }

    for (int i = 0; i < C[Camada_Saida].Numero_Neuronios; i++)
        Saida[i] = C[Camada_Saida].N[i].Somatorio(Entrada[i]);
}

/*********************************************************
  Algoritmmo de Treinamento Back Propagation
 *********************************************************/
void Rede ::Treinar()
{
    int i, j, Linha_Escolhida, Iteracoes, Camada_Saida;
    int p, q;
    vector<pair<double, double>> Vetor_Saida;
    double Erros[NUMNEU], Marcados[NUMIN], Somatorio_Erro, Maior;
    long Contador;
    char Sair;

    /* Inicializando vari�veis ???*/
    Sair = 0;
    Contador = 0;
    Maior = 1;
    Camada_Saida = Numero_Camadas - 1;

    do
    {
        Linha_Escolhida = rand() % NUMIN;

        j = 0;
        while (Marcados[Linha_Escolhida] == 1)
        {
            Linha_Escolhida++;
            j++;

            if (Linha_Escolhida == NUMIN)
                Linha_Escolhida = 0;

            if (j == NUMIN)
                for (i = 0; i < NUMIN; i++)
                    Marcados[i] = 0;
        }

        Marcados[Linha_Escolhida] = 1;
        Contador++;

        // FEED-FORWARD
        // Treinar neuronios da primeira camada
        C[0].Treinar_Neuronios(entrada);  //OK
        C[0].Funcao_Ativacao();           //OK
        C[0].Retornar_Saida(Vetor_Saida); //paraleizado

        for (i = 1; i < Numero_Camadas; i++)
        {
            C[i].Treinar_Neuronios(Vetor_Saida); //paraleizado
            C[i].Funcao_Ativacao();              //paraleizado
            C[i].Retornar_Saida(Vetor_Saida);    //paraleizado
        }

        // BACK-PROPAGATION -> OK DUVIDOSO
        /* Ajustando pesos da camada de sa�da */
        C[Camada_Saida].Calcular_Erro_Camada_Saida(Erros, saida);    //paraleizado
        C[Camada_Saida - 1].Retornar_Saida(Vetor_Saida);             //paraleizado
        C[Camada_Saida].Ajustar_Pesos_Neuronios(Erros, Vetor_Saida); //paraleizado

        /* Ajustando pesos das camadas intermedi�rias */
        for (i = Camada_Saida - 1; i > 0; i--)
        {
            C[i].Calcular_Erro_Camada(Erros);             //paraleizado
            C[i - 1].Retornar_Saida(Vetor_Saida);         //paraleizado
            C[i].Ajustar_Pesos_Neuronios(Erros, entrada); //paraleizado
        }

        /* Ajustando pesos da primeira camada */
        C[0].Calcular_Erro_Camada(Erros);             //paraleizado
        C[0].Ajustar_Pesos_Neuronios(Erros, entrada); //paraleizado

        /* Calculando o erro global */
        C[Camada_Saida].Calcular_Erro_Final(Erros, saida); //paraleizado
        //printf("xoreiiii");

        // FÓRMULA
        Somatorio_Erro = 0;
        for (i = 0; i < NUMNEU; i++)
            Somatorio_Erro += pow(Erros[i], 2);

        Somatorio_Erro /= 2;

        /* Verificando condi��es */
        // REMOVER BIAS DINÂMICO
        if (Somatorio_Erro < Maior)
        {
            Utils::gotoxy(1, 10);
            cout << "\n\nErro = " << Somatorio_Erro << "   ";
            Maior = Somatorio_Erro;
        }

        /* Exibi��o na tela */
        if (Contador % 10000 == 0)
        {
            Utils::gotoxy(1, 10);
            cout << "\nIteracoes = " << Contador;
            cout << "\n\nBeta = " << Utils::BETA << "  ";
        }

        /* Op��o de escape */
        if (Contador % ITERACOES == 0) //falta 1 zero
        {
            cout << "\nRede treinada!" << endl;
            cout << "Pressione 'y' para sair do treinamento ou qualquer outro botão para continuar. " << endl;
            // cin.clear();
            // cin.ignore(256, '\n');
            cin >> Sair;
            limpar_tela();
            Utils::gotoxy(1, 10);
        }

    } while (Sair != 'y');
}
