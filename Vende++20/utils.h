#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#ifdef _MSC_VER

#include <Windows.h>

#endif

#include "defs.h"
#include "Table.h"
#include "Data.h"
using namespace std;

void clearScreen();

bool leUnsignedShortInt(unsigned short int &input, unsigned short int min, unsigned short int  max, string mensagemErro = "Input invalido");

void trimString(string &inputString);

bool validateName(string &nome);

<<<<<<< HEAD
bool validateProduct(string &produto);
=======
bool validateProduct(string &nome);
>>>>>>> LEO

void SetCursor(int column, int line);

void ignoreLine(bool ignoreControl = true, string message = "Prima Enter para continuar.");

bool validateInputStream(istream &inStream, string errorMessage);

//void showError(string error);

bool stringVazia(string stringTeste);

<<<<<<< HEAD
bool leVectorInteiros(vector <unsigned int> &resultado, string mensagem, string mensagemErro = "Por favor insira pelo menos um numero inteiro positivo");

bool leDatas(vector<string> &resultado, string mensagem, string mensagemErro = "Formato de Datas Invalido");
=======
bool leVectorInteiros(vector <unsigned int> &resultado,
	string mensagem, string mensagemErro = "Por favor insira pelo menos um numero inteiro positivo");

bool leDatas(vector<string> &resultado, string mensagem, string mensagemErro = "Formato de Datas Invalido");

bool leStringFloat(pair<string, float> &resultado, string mensagem, string mensagemErro = "Input invalido");
>>>>>>> LEO
