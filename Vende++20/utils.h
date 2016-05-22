/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#ifdef _MSC_VER

#include <Windows.h>

#endif

#include <map>
#include "Table.h"
#include "Data.h"
using namespace std;

void clearScreen();

void trimString(string &inputString);

bool validateName(string &nome);

bool validateProduct(string &nome);

void SetCursor(int column, int line);

void ignoreLine(bool ignoreControl = true, string message = "Prima Enter para continuar.");

bool validateInputStream(istream &inStream, string errorMessage);

bool stringVazia(string stringTeste);

bool leUnsignedShortInt(unsigned short int &input, unsigned short int min, unsigned short int  max, string mensagemErro = "Input invalido");

bool leUnsignedInt(unsigned int &input, unsigned int min, unsigned int  max, string mensagemErro = "Input invalido");

bool leVectorInteiros(vector <unsigned int> &resultado,
	string mensagem, string mensagemErro = "Por favor insira pelo menos um numero inteiro positivo");

bool leDatas(vector<string> &resultado, string mensagem, string mensagemErro = "Formato de Datas Invalido");

bool leStringFloat(pair<string, float> &resultado, string mensagem, string mensagemErro = "Input invalido");

bool confirmar(vector<vector<string>> mensagemConfirmacao, vector<bool> blocks, vector<int> spacesForColumn, unsigned int indentacao);
