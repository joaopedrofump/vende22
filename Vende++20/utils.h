#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

#ifdef _MSC_VER

#include <Windows.h>

#endif

#include "defs.h"
#include "Table.h"
using namespace std;

void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);

void trimString(string &inputString);

bool validateName(string &nome);

void SetCursor(int column, int line);

void ignoreLine(bool ignoreControl = true, string message = "Prima Enter para continuar.");

bool validateInputStream(istream &inStream, string errorMessage);

void showError(string error);

bool stringVazia(string stringTeste);

vector <unsigned int> leVectorInteiros(string mensagem, string mensagemErro = "Por favor insira pelo menos um numero inteiro positivo");
