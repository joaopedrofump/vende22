/*

T7G02
Jo�o Pinheiro
Leonardo Teixeira

*/


#include <iostream>
#include <string>
#include <vector>
#include "Cliente.h"

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"
#include "data.h"


int main() {
	string loja, fichClients, fichProdutos, fichTransacoes;
	//
	// pede a informacoo sobre o nome da loja e os 3 ficheiros com
	// informacoo de clientes, produtos e transacoes
	if (!infoInicial(loja, fichClients, fichProdutos, fichTransacoes)) {
		cout << Table({ "N�o foi poss�vel ler todos os ficheiros. Por favor verifique os ficheiros." }) << endl;
		return(1);
	}
	//
	// cria uma loja
	VendeMaisMais supermercado(loja, fichClients, fichProdutos, fichTransacoes);

	//cout << "Informacao da loja '" << loja << " do supermercado Vende++:" << endl;
	//cout << supermercado << endl;  // mostra estatisticas da loja
    opcoesIniciais(supermercado);
    
    
	return 0;

}