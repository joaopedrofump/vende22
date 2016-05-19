#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


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

    string getNome() const;
    float getCusto() const;
    unsigned int getProdutoId() const;
    bool getStatus() const;

    void setStatus(bool newStatus);
    static unsigned int getNumProdutos();
    static void setNumProdutos(unsigned int numInicial);

    void save(ofstream &out) const;

	vector<string> toTable() const;
    //int indiceProduto(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos
    friend ostream& operator<<(ostream& out, const Produto & prod); // ostra umproduto
    friend bool operator<(const Produto &prod1, const Produto &prod2); // compara 2 produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
    vector<string> toTable() const;
};
