#include "Produto.h"
#include "utils.h"

unsigned int Produto::numProdutos;

Produto::Produto(ifstream & in){ // nome ; custo
    string stringTemporaria;
    getline(in, stringTemporaria);
    this->nome = stringTemporaria.substr(0, stringTemporaria.find(';', 0));
    trimString(this->nome);
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    trimString(stringTemporaria);
    this->custo = atof(stringTemporaria.c_str());
    this->active = true;
    this->idProduto = ++Produto::numProdutos;
}

Produto::Produto(string nomeProduto, float custoProduto){
    this->nome = nomeProduto;
    this->custo = custoProduto;
    this->active = true;
    this->idProduto = ++Produto::numProdutos;
}

string Produto::getNome() const {
    return nome;
}

float Produto::getCusto() const {
    return custo;
}

unsigned int Produto::getProdutoId() const {
    
    return this->idProduto;
}

unsigned int Produto::getNumProdutos() {
    
    return Produto::numProdutos;
    
}

void Produto::setNumProdutos(unsigned int numInicial) {
    
    Produto::numProdutos = numInicial;
    
}

bool Produto::getStatus() const {
    
    return this->active;
}

void Produto::setStatus(bool newStatus) {
    
    this->active = newStatus;
}

void Produto::save(ofstream &out) const {
    
   out << *this;
    
}

ostream& operator<<(ostream& out, const Produto & produto){
    
    out << produto.nome << " ; " << produto.custo << endl;
    return out;
}


bool operator<(const Produto &prod1, const Produto &prod2){
    if (prod1.custo < prod2.custo){
        return true;
    }
    else
        return false;
}