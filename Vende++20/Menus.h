/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#pragma once

#include <iostream>
#include <fstream>
#include <string>


#include <map>
#include "utils.h"
#include "Vende++.h"

using namespace std;

bool infoInicial(string & loja, string & fichClients, string & fichProdutos, string & fichTransacoes);

void opcoesIniciais(VendeMaisMais & supermercado);

void opcoesGestaoClientes(VendeMaisMais & supermercado);

/*void listarClientesOrdemAlfabetica(VendeMaisMais & supermercado);

void listarProdutos(VendeMaisMais & supermercado);*/

void opcoesGestaoTransacoes(VendeMaisMais & supermercado);

void opcoesRecomendacao(VendeMaisMais & supermercado);

void mostrarMenuInicial(unsigned short int opcaoEscolhida = 0);

void opcoesGestaoProdutos(VendeMaisMais &supermercado);

unsigned short int menuInicial();