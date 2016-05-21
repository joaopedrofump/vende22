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

bool validateProduct(string &nome);

void SetCursor(int column, int line);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
void ignoreLine(bool ignoreControl = true, string message = "Prima Enter para continuar.");

bool validateInputStream(istream &inStream, string errorMessage);

<<<<<<< HEAD
//void showError(string error);

bool stringVazia(string stringTeste);

bool leVectorInteiros(vector <unsigned int> &resultado, 
					  string mensagem, string mensagemErro = "Por favor insira pelo menos um numero inteiro positivo");

bool leDatas(vector<string> &resultado, string mensagem, string mensagemErro = "Formato de Datas Invalido");

bool leStringFloat(pair<string, float> &resultado, string mensagem, string mensagemErro = "Input invalido");
=======
void showError(string error);

bool stringVazia(string stringTeste);

vector <unsigned int> leVectorInteiros(string mensagem, string mensagemErro = "Por favor insira pelo menos um numero inteiro positivo");
=======
void ignoreLine(bool ignoreControl = true, string message = "Press Enter to Continue.");

bool stringVazia(string stringTeste);

void formatTableShow(char internalChar, char limitingChar, vector<int> spacesForColumn, unsigned int indentacaoFT, ostream& out);
>>>>>>> LEO
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
