#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Data.h"
#include "Cliente.h"
#include "Produto.h"

using namespace std;


class Transacao {
 private:
  unsigned int idCliente;
    Data data; // na forma DD/MM/AAAAA
    vector<string> produtos;
    vector<Produto> produtosProduto;
    Cliente clienteTransacao;
    float total;
    

 public:
    Transacao(ifstream & in); // trabsacao na forma de  idCliente ; data ; lista de produtos
    Transacao(Cliente clienteAInserir, vector <Produto> produtosTransacao);
    unsigned int getIdCliente() const;
    void save(ofstream & out) const; // guarda a transacao
    friend ostream& operator<<(ostream& out, const Transacao & trans); // mostra a transacao
    vector<string> getProdutosString() const;
    vector<Produto> getProdutosProduto()const ;
    void setVectorProdutos(vector <Produto> vectorProdutos);
    Cliente getCliente();
    void setCliente(Cliente clienteAInserir);
    float getTotal() const;
    void calculateTotal();
    Data getData() const;
};



