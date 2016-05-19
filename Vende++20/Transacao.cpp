#include "Transacao.h"
#include "utils.h"
#include "Data.h"



unsigned int Transacao::getIdCliente() const{
    return idCliente;
}


Transacao::Transacao(ifstream &in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
    string linha;
    string stringTemporaria;
    getline(in, linha);
    
    this->idCliente = atoi(linha.substr(0, linha.find(';', 0)).c_str()); //salva o id do Cliente
    linha = linha.substr(linha.find(';', 0) + 1);	//atualiza a Linha
    
    stringTemporaria = linha.substr(0, linha.find(';', 0));
    trimString(stringTemporaria);
    
    Data dataTemporaria(stringTemporaria);
    this->data = dataTemporaria;  //guarda a data
    
    linha = linha.substr(linha.find(';', 0) + 1);  //atualiza a Linha
    
    vector<string> produtosComprados;
    while (linha.find(',') < (int)linha.length()){ //correr o resto da string
        
        stringTemporaria = linha.substr(0, linha.find(',', 0));
        trimString(stringTemporaria);
        produtosComprados.push_back(stringTemporaria);
        linha = linha.substr(linha.find(',') + 1);
    }
    trimString(linha);
    produtosComprados.push_back(linha);
    this->produtos = produtosComprados;
}

Transacao::Transacao(Cliente clienteAInserir, vector <Produto> produtosTransacao) {
    
    this->clienteTransacao = clienteAInserir;
    this->produtosProduto = produtosTransacao;
    
}

void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
    
    out << *this;
    
}

ostream& operator<<(ostream& out, const Transacao &transacao){
    
    out << transacao.idCliente << " ; " << transacao.data << " ; ";
    for (int x = 0; x < transacao.produtos.size(); x++){
        out << transacao.produtos.at(x);
        if (x < transacao.produtos.size()-1){
            out << ",";
        }
    }
    return out;
}

vector<string> Transacao::getProdutosString() const {
    
    return this->produtos;
    
}

vector<Produto> Transacao::getProdutosProduto() const {
    
    return this->produtosProduto;
    
}

void Transacao::setVectorProdutos(vector <Produto> vectorProdutos) {
    
    this->produtosProduto = vectorProdutos;
    
}

Cliente Transacao::getCliente() {
    
    return this->clienteTransacao;
}

void Transacao::setCliente(Cliente clienteAInserir) {
    
    this->clienteTransacao = clienteAInserir;
}
