#include <stdio.h>

#include "constants.h"
#include "Utils.h"

using namespace std;

double Utils::BETA = MI;

void Utils::gotoxy(int x, int y)
{
    // #if defined(__MINGW32__) || defined(_MSC_VER) || defined(_WIN32) || defined(WIN32)
    //     COORD coord;
    //     coord.X = x;
    //     coord.Y = y;
    //     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    // #else
    //     printf("%c[%d;%df", 0x1B, y, x);
    // #endif

    printf("%c[%d;%df", 0x1B, y, x);
}

void Utils::gerarBaseDeDados()
{
    ofstream entrada, saida;
    int a = 0, b = 0, c = 0;
    int n = 10000;

    entrada.open("../database/Entrada.txt");
    saida.open("../database/Saida.txt");
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

void Utils::gerarBaseDeDados2()
{
    ofstream entrada, saida;
    int a = 0, b = 0, c = 0;
    int n = 10000;

    entrada.open("../database/Entrada.txt");
    saida.open("../database/Saida.txt");
    srand(time(NULL));

    for (int x = 0; x < LINHAS; x++)
    {
        a = rand() % 1;
        b = rand() % 1;

        if((a == 0 && b == 0) || (a == 1 && b == 1)) 
			c = 0;
		else
		{
			if((a == 0 && b == 1) || (a == 1 && b == 0)) 
				c = 1;
			else
				cout << "ERRO!" << endl;
		}
			

        entrada << a << " " << b << endl;
        saida << c << endl;
    }

    entrada.close();
    saida.close();
}

void Utils::conferir()
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
            printf("ENTRADAS INCONSISTENTES: linha %d, a = %d, b = %d, c = %d", i, a, b, c);
            i = LINHAS;
        }
    }
}

void Utils::conferir2()
{
    ifstream entrada, saida;
    int a = 0, b = 0, c = 0;

    entrada.open("Entrada.txt");
    saida.open("Saida.txt");

    for (int i = 0; i < LINHAS; i++)
    {
        entrada >> a >> b;
        saida >> c;

        if((a == 0 && b == 0) || (a == 1 && b == 1)) 
			continue;
		else
		{
			if((a == 0 && b == 1) || (a == 1 && b == 0)) 
				continue;
			else
				printf("ENTRADAS INCONSISTENTES: linha %d, a = %d, b = %d, c = %d", i, a, b, c);
		}	                
   }
}
