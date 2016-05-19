#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

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

void ignoreLine(string message = "Prima Enter para continuar.", bool ignoreControl = true);

bool validateInputStream(istream &inStream, string errorMessage);

void showError(string error);

bool stringVazia(string stringTeste);