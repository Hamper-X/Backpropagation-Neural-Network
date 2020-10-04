
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
void Rede ::Inicializar_Rede(int Numero_Camadas, int Numero_Linhas,
                             int Numero_Linhas_Entrada, int Numero_Linhas_Saida, int Numero_Neuronio_Camada[])
{
    int i, j, a, b;
    FILE *Entrada, *Saida;

    this->Numero_Camadas = Numero_Camadas;
    this->Numero_Linhas = Numero_Linhas;
    this->Numero_Linhas_Entrada = Numero_Linhas_Entrada;
    this->Numero_Linhas_Saida = Numero_Linhas_Saida;

    Entrada = fopen("../database/Entrada.txt", "rb");
    Saida = fopen("../database/Saida.txt", "rb");

    for (i = 0; i < Numero_Linhas; i++)
    {        

        fread(&a, sizeof(double), 1, Entrada);
        fread(&b, sizeof(double), 1, Entrada);
        entrada.push_back(make_pair(a, b));
    }

    for (i = 0; i < Numero_Linhas; i++)
    {
        fread(&a, sizeof(double), 1, Saida);
        saida.push_back(a);
    }

    fclose(Entrada);
    fclose(Saida);

    //camada intermediária padrão
    C[0].Inicializar_Camada(Numero_Neuronio_Camada[0], Numero_Linhas_Entrada);

    // Camadas intermediárias
    for (i = 1; i < Numero_Camadas; i++)
        C[i].Inicializar_Camada(Numero_Neuronio_Camada[i], (Numero_Neuronio_Camada[i - 1] + 1));
}

/*********************************************************
  Calcula a resposta da rede para uma certa entrada,
  retornando a sa�da
 *********************************************************/
void Rede ::Calcular_Resultado(double Entrada[], double Saida[])
{
    int i, j;

    for (i = 0; i < Numero_Camadas; i++)
    {
        C[i].Treinar_Neuronios(Entrada);
        C[i].Funcao_Ativacao();
        C[i].Retornar_Saida(Saida);

        for (j = 0; j < MAXNEU; j++)
            Entrada[j] = Saida[j];
    }
}

/*********************************************************
  Algoritmmo de Treinamento Back Propagation
 *********************************************************/
void Rede ::Treinar()
{
    int i, j, Linha_Escolhida, Iteracoes, Camada_Saida, Marcados[MAXLIN];
    int p, q;
    double Vetor_Saida[MAXNEU], Erros[MAXNEU], Somatorio_Erro, Maior;
    long Contador, Dinamico;
    char Sair;

/* Inicializando vari�veis */
#pragma omp parallel for private(i)
    for (i = 0; i < MAXLIN; i++)
        Marcados[i] = 0;

    Dinamico = 0;
    Sair = 0;
    Contador = 0;
    Maior = 1;
    Iteracoes = 0;
    Camada_Saida = Numero_Camadas - 1;

    do
    {
        Linha_Escolhida = rand() % NUMLIN;

        j = 0;
        while (Marcados[Linha_Escolhida] == 1)
        {
            Linha_Escolhida++;
            j++;

            if (Linha_Escolhida == NUMLIN)
                Linha_Escolhida = 0;

            if (j == NUMLIN)
                for (i = 0; i < MAXLIN; i++)
                    Marcados[i] = 0;
        }

        Marcados[Linha_Escolhida] = 1;
        Contador++;

        // FEED-FORWARD
        C[0].Treinar_Neuronios(entrada[Linha_Escolhida]); //paraleizado
        C[0].Funcao_Ativacao();                     //paraleizado
        C[0].Retornar_Saida(Vetor_Saida);           //paraleizado

        for (i = 1; i < Numero_Camadas; i++)
        {
            C[i].Treinar_Neuronios(Vetor_Saida); //paraleizado
            C[i].Funcao_Ativacao();              //paraleizado
            C[i].Retornar_Saida(Vetor_Saida);    //paraleizado
        }

        // BACK-PROPAGATION
        /* Ajustando pesos da camada de sa�da */
        C[Camada_Saida].Calcular_Erro_Camada_Saida(Erros, Y[Linha_Escolhida]); //paraleizado
        C[Camada_Saida - 1].Retornar_Saida(Vetor_Saida);                       //paraleizado
        C[Camada_Saida].Ajustar_Pesos_Neuronios(Erros, Vetor_Saida);           //paraleizado

        /* Ajustando pesos das camadas intermedi�rias */
        for (i = Camada_Saida - 1; i > 0; i--)
        {
            C[i].Calcular_Erro_Camada(Erros);                        //paraleizado
            C[i - 1].Retornar_Saida(Vetor_Saida);                    //paraleizado
            C[i].Ajustar_Pesos_Neuronios(Erros, X[Linha_Escolhida]); //paraleizado
        }

        /* Ajustando pesos da primeira camada */
        C[0].Calcular_Erro_Camada(Erros);                        //paraleizado
        C[0].Ajustar_Pesos_Neuronios(Erros, X[Linha_Escolhida]); //paraleizado

        /* Calculando o erro global */
        C[Camada_Saida].Calcular_Erro_Final(Erros, Y[Linha_Escolhida]); //paraleizado

        Somatorio_Erro = 0;
        for (i = 0; i < Numero_Linhas_Saida; i++)
            Somatorio_Erro += pow(Erros[i], 2);

        Somatorio_Erro /= 2;

        /* Verificando condi��es */
        if (Somatorio_Erro < Maior)
        {
            Dinamico = 0;
            Utils::gotoxy(1, 10);
            cout << "\n\nErro = " << Somatorio_Erro << "   ";
            Maior = Somatorio_Erro;
        }
        else
            Dinamico++;

        if (Somatorio_Erro <= TOLERANCIA)
            Iteracoes++;
        else
            Iteracoes = 0;

        /* Beta din�mico */
        if (Dinamico == 200000)
        {
            Dinamico = 0;
            p = rand() % 6;
            q = rand() % 3;
            Utils::BETA += (p / 10.0) * (q - 1);
        }

        if (Dinamico == 50000)
            Utils::BETA = MI;

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

    } while (Iteracoes < NUMITE && Sair != 'y');
}
