#pragma once

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "constants.h"

class Utils
{
    const int LINHAS = 10000;
    public:        
        static double BETA; // Fator de ajuste das correcoes
        static void gotoxy(int x, int y);
        static void gotoxyWin(int x, int y);
        void gerarBaseDeDados();
        void gerarBaseDeDados2();
        void conferir();
        void conferir2();
};
