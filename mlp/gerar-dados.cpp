#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fstream>

#define LINHAS 100000

using namespace std;

void gerarBaseDeDados()
{
    ofstream entrada, saida;
    int a = 0, b = 0, c = 0;
    int n = 10000;

    entrada.open("Entrada.txt");
    saida.open("Saida.txt");
    srand(time(NULL));

    for (int x = 0; x < LINHAS; x++)
    {
        a = rand() % n;
        b = rand() % n;
        c = a + b;
        entrada << a << " " << b << endl;
        saida << c << endl;
    }

    entrada.close();
    saida.close();
}

void conferir()
{
    ifstream entrada, saida;
    int a = 0, b = 0, c = 0;

    entrada.open("Entrada.txt");
    saida.open("Saida.txt");

    for (int i = 0; i < LINHAS; i++)
    {
        entrada >> a >> b;
        saida >> c;
                
        if (a + b != c)
        {
            printf("ENTRADAS INCONSISTENTES: linha %d, a = %d, b = %d, c = %d", &i, &a, &b, &c);
            i = LINHAS;
        }
    }
}

int main()
{
    //gerarBaseDeDados();
    conferir();
    return 0;
}