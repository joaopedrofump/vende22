#include "Produto.h"
#include "utils.h"


Produto::Produto(ifstream & in){ // nome ; custo
    string stringTemporaria;
    getline(in, stringTemporaria);
    this->nome = stringTemporaria.substr(0, stringTemporaria.find(';', 0));
    trimString(this->nome);
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    trimString(stringTemporaria);
    this->custo = atof(stringTemporaria.c_str());
}

Produto::Produto(string nomeProduto, float custoProduto){
    this->nome = nomeProduto;
    this->custo = custoProduto;
}

string Produto::getNome() const {
    return nome;
}

float Produto::getCusto() const {
    return custo;
}

ostream& operator<<(ostream& out, const Produto & produto){
    
    out << produto.nome << " ; " << produto.custo;
    return out;
}


bool operator<(const Produto &prod1, const Produto &prod2){
    if (prod1.custo < prod2.custo){
        return true;
    }
    else
        return false;
}
