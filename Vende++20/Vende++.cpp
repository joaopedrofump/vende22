#include "Vende++.h"
#include <fstream>
#include <iostream>
using namespace std;

string const FILE_SEPRATOR = "------------------------------------------------";
typedef map<unsigned int, Cliente>::const_iterator constIntClient;
typedef map<string, Cliente>::const_iterator constIntClientString;

VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){
    
    ifstream inStreamClientes, inStreamProdutos, inStreamTransacoes;
    
    Cliente::setNumClientes(0);
    
    unsigned int numeroClientes;
    unsigned int numeroProdutos;
    unsigned int numeroTransacoes;
    
    this->loja = loja;
    this->fichClientes = fichClients;
    this->fichProdutos = fichProdutos;
    this->fichTransacoes = fichTransacoes;
    
    
    inStreamClientes.open(this->fichClientes.c_str());
    inStreamClientes >> numeroClientes;
    //inStreamClientes.ignore(1000, '\n');
    
    inStreamProdutos.open(this->fichProdutos.c_str());
    inStreamProdutos >> numeroProdutos;
    inStreamProdutos.ignore(1000, '\n');
    
    inStreamTransacoes.open(this->fichTransacoes.c_str());
    inStreamTransacoes >> numeroTransacoes;
    inStreamTransacoes.ignore(1000, '\n');
    
    //ler todos
    
    for (int i = 0; i < numeroClientes; i++) {
        
        Cliente clienteActual(inStreamClientes);
        pair<unsigned int, Cliente> parClienteIdActual = make_pair(clienteActual.getId(), clienteActual);
        pair<string, Cliente> parNomeIdActual = make_pair(clienteActual.getNome(), clienteActual);
        this->clientes.insert(parClienteIdActual);
        this->clienteIdx.insert(parNomeIdActual);
        
        
    }
    
    this->maxClientesId = Cliente::getNumClientes();
    
    //ler inactivos
    
    if (!inStreamClientes.eof()) {
        
        unsigned int clientId;
        string inactiveClients; //lê a ultima linha do ficheiro que contém a lista de clientes inactivos
        getline(inStreamClientes, inactiveClients);
        getline(inStreamClientes, inactiveClients);
        stringstream inactiveClientsStream(inactiveClients);
        
        while (!inactiveClientsStream.eof()) {
            
            inactiveClientsStream >> clientId;
            
            if (inactiveClientsStream.fail()) {
                
                break;
                
            }
            
            this->clientes.at(clientId).setStatus(false);
            this->clienteIdx.at(this->clientes.at(clientId).getNome()).setStatus(false);
            
        }
        
    }
    
    for (int i = 0; i < numeroProdutos; i++) {
        
        Produto produtoActual(inStreamProdutos);
        this->produtos.push_back(produtoActual);
    }
    
    for (int i = 0; i < numeroTransacoes; i++) {
        
        Transacao transacaoActual(inStreamTransacoes);
        this->transacoes.push_back(transacaoActual);
    }
    
    inStreamClientes.close();
    inStreamProdutos.close();
    inStreamTransacoes.close();
    
}

/*********************************
 Gestao de Clientes
 ********************************/

// lista os cleinets por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const{
    
    constIntClientString iteClienteIdx;
    
    for (iteClienteIdx = this->clienteIdx.begin(); iteClienteIdx != this->clienteIdx.end(); iteClienteIdx++) {
        
        cout << iteClienteIdx->first << endl;
        
    }
    
}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome){
    
    constIntClientString iterator = this->clienteIdx.find(nome);
    
    if (iterator == this->clienteIdx.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return;
        
    }
    
    
    cout << "***************************************************" << endl;
    cout << "Id de Cliente: " << this->clienteIdx.at(nome).getId() << endl;
    cout << "Nome do Cliente: " << this->clienteIdx.at(nome).getNome() << endl;
    cout << "Cartão de Cliente: " << this->clienteIdx.at(nome).getCartaoCliente().mostrarData() << endl;
    
    string status;
    
    status =  this->clienteIdx.at(nome).getStatus() ? "Activo" : "Inactivo";
    
    cout << "Estado do Cliente: " << status << endl;
    
}

void VendeMaisMais::mostraInformacaoCliente(unsigned int clientId) {
    
    constIntClient iterator = this->clientes.find(clientId);
    
    if (iterator == this->clientes.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return;
    }
    
    cout << "***************************************************" << endl;
    cout << "Id de Cliente: " << this->clientes.at(clientId).getId() << endl;
    cout << "Nome do Cliente: " << this->clientes.at(clientId).getNome() << endl;
    cout << "Cartão de Cliente: " << this->clientes.at(clientId).getCartaoCliente().mostrarData() << endl;
    
    string status;
    
    status =  this->clientes.at(clientId).getStatus() ? "Activo" : "Inactivo";
    
    cout << "Estado do Cliente: " << status << endl;
    
}

void VendeMaisMais::eliminarCliente(string nome) {
    
    //verificar se o cliente existe
    
    constIntClientString iterator = this->clienteIdx.find(nome);
    
    if (iterator == this->clienteIdx.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return;
        
    }
    
    //colocar o cliente inactivo nos dois mapas
    
    if (this->clienteIdx.at(nome).getStatus()) {
        this->clienteIdx.at(nome).setStatus(false);
        this->clientes.at(this->clienteIdx.at(nome).getId()).setStatus(false);
        cout << "Cliente eliminado correctamente" << endl;
        this->clientesAlterados = true;
    }
    
    else {
        
        cout << "O cliente já se encontra eliminado." << endl;
        
    }
    
}

void VendeMaisMais::eliminarCliente(unsigned int clientId) {
    
    //verificar se o cliente existe
    
    constIntClient iterator = this->clientes.find(clientId);
    
    if (iterator == this->clientes.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return;
        
    }
    
    if (this->clientes.at(clientId).getStatus()) {
        
        this->clientes.at(clientId).setStatus(false);
        this->clienteIdx.at(this->clientes.at(clientId).getNome()).setStatus(false);
        cout << "Cliente eliminado correctamente" << endl;
        this->clientesAlterados = true;

        
    } else {
        cout << "O cliente já se encontra eliminado." << endl;
    }
    
}

void VendeMaisMais::reactivarCliente(string nome) {
    
    //verificar se o cliente existe
    
    constIntClientString iterator = this->clienteIdx.find(nome);
    
    if (iterator == this->clienteIdx.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return;
        
    }
    
    //colocar o cliente inactivo nos dois mapas
    
    if (!this->clienteIdx.at(nome).getStatus()) {
        this->clienteIdx.at(nome).setStatus(true);
        this->clientes.at(this->clienteIdx.at(nome).getId()).setStatus(true);
        cout << "Cliente eliminado correctamente" << endl;
        this->clientesAlterados = true;

    }
    
    else {
        
        cout << "O cliente já se encontra activo." << endl;
        
    }
    
}

void VendeMaisMais::reactivarCliente(unsigned int clientId) {
    
    //verificar se o cliente existe
    
    constIntClient iterator = this->clientes.find(clientId);
    
    if (iterator == this->clientes.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return;
        
    }
    
    if (!this->clientes.at(clientId).getStatus()) {
        
        this->clientes.at(clientId).setStatus(true);
        this->clienteIdx.at(this->clientes.at(clientId).getNome()).setStatus(true);
        cout << "Cliente eliminado correctamente" << endl;
        this->clientesAlterados = true;

        
    } else {
        cout << "O cliente já se encontra activo." << endl;
    }
    
}

void VendeMaisMais::adicionarCliente(string nome) {
    
    if (validateName(nome)) {
        
        Cliente novoCliente(nome);
        pair<unsigned int, Cliente> parNovoCliente = make_pair(novoCliente.getId(), novoCliente);
        pair<string, Cliente> parNovoClienteString = make_pair(novoCliente.getNome(), novoCliente);
        
        this->clientes.insert(parNovoCliente);
        this->clienteIdx.insert(parNovoClienteString);
        this->maxClientesId = Cliente::getNumClientes();
        
    }
    
    else {
        
        cout << "Cliente não inserido" << endl;
    }
    
}

unsigned int VendeMaisMais::getMaxClienteId(){
    
    return this->maxClientesId;
    
}


/*********************************
 Gestao de Produtos
 ********************************/

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{
    
    // A IMPLEMENTAR
    
}

void VendeMaisMais::adicionarProduto(string nomeProduto, float custoProduto){
    Produto novoProduto(nomeProduto, custoProduto);
    produtos.push_back(novoProduto);
    produtosAlterados = true;
    saveChanges();
}


/*********************************
 Preservar Informacao
 ********************************/

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada

void VendeMaisMais::saveChanges() const{
    
    ofstream outClientes(this->fichClientes);
    ofstream outTransacoes(this->fichTransacoes);
    
    outClientes << this->clientes.size() << endl;
    
    constIntClient iterator;
    
    for (iterator = this->clientes.begin(); iterator != this->clientes.end(); iterator++) {
        
        iterator->second.save(outClientes);
    
        
    }
    
    outClientes << FILE_SEPRATOR << endl;
    
    for (iterator = this->clientes.begin(); iterator != this->clientes.end(); iterator++) {
        
        if (!iterator->second.getStatus()) {
            
            outClientes << iterator->first;
            
            if (iterator->first != this->maxClientesId) {
                
                outClientes << " ";
                
            }
            
        }
        
    }
    
    outTransacoes << this->transacoes.size() << endl;
    
    for (size_t i = 0; i < this->transacoes.size(); i++) {
        
        transacoes.at(i).save(outTransacoes);
        
        if (i < transacoes.size() - 1) {
            
            outTransacoes << endl;
            
        }
        
    }
    
    outClientes.close();
    outTransacoes.close();
    
    
}

/*********************************
 Mostrar Loja
 ********************************/  

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){
    
    // A IMPLEMENTAR 
    return out; // TESTE
    
}