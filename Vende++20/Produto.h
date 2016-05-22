/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

class Produto {
private:
	string nome;
	float custo;
	static unsigned int numProdutos;
	bool active;
	unsigned int idProduto;

public:

    Produto(ifstream &in);
    Produto(string nomeProduto, float custoProduto);
    Produto(){};
	string getNome() const;
	float getCusto() const;
	unsigned int getProdutoId() const;
	bool getStatus() const;

	void setStatus(bool newStatus);
	static unsigned int getNumProdutos();
	static void setNumProdutos(unsigned int numInicial);

	void save(ofstream &out) const;

	vector<string> toTable() const;
    
    friend ostream& operator<<(ostream& out, const Produto & prod); // ostra umproduto
    friend bool operator<(const Produto &prod1, const Produto &prod2); // compara 2 produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
};

