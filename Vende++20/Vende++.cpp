#include "Vende++.h"
#include <fstream>
#include <iostream>
using namespace std;

string const FILE_SEPRATOR = "------------------------------------------------";
typedef map<unsigned int, Cliente>::const_iterator constIntClient;
typedef map<string, Cliente>::const_iterator constIntClientString;

typedef map<unsigned int, Produto>::const_iterator constIntProduto;
typedef map<string, Produto>::const_iterator constIntProdutoString;

typedef map<unsigned int, unsigned int>::const_iterator constIteMMTra;

VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){
    
    ifstream inStreamClientes, inStreamProdutos, inStreamTransacoes;
    
    Cliente::setNumClientes(0);
    Produto::setNumProdutos(0);
    
    unsigned int numeroClientes;
    unsigned int numeroProdutos;
    unsigned int numeroTransacoes;
    
    this->loja = loja;
    this->fichClientes = fichClients;
    this->fichProdutos = fichProdutos;
    this->fichTransacoes = fichTransacoes;
    
    
    inStreamClientes.open(this->fichClientes.c_str());
    inStreamClientes >> numeroClientes;
    inStreamClientes.ignore(1000, '\n');
    
    inStreamProdutos.open(this->fichProdutos.c_str());
    inStreamProdutos >> numeroProdutos;
    inStreamProdutos.ignore(1000, '\n');
    
    inStreamTransacoes.open(this->fichTransacoes.c_str());
    inStreamTransacoes >> numeroTransacoes;
    inStreamTransacoes.ignore(1000, '\n');
    
    //ler todos os clientes
    
    for (int i = 0; i < numeroClientes; i++) {
        
        Cliente clienteActual(inStreamClientes);
        
        if (clienteActual.getId() == 0) {
            continue;
        }
        
        pair<unsigned int, Cliente> parClienteIdActual = make_pair(clienteActual.getId(), clienteActual);
        pair<string, Cliente> parNomeIdActual = make_pair(clienteActual.getNome(), clienteActual);
        this->clientes.insert(parClienteIdActual);
        this->clienteIdx.insert(parNomeIdActual);
        
        
    }
    
    this->maxClientesId = Cliente::getNumClientes();
    
    //ler clientes inactivos
    
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
    
    //ler todos os produtos
    
    for (int i = 0; i < numeroProdutos; i++) {
        
        Produto produtoActual(inStreamProdutos);
        
        if (produtoActual.getProdutoId() == 0) {
            continue;
        }
        
        pair<unsigned int, Produto> parIntProdutoActual = make_pair(produtoActual.getProdutoId(), produtoActual);
        pair<string, Produto> parStringProdutoActual = make_pair(produtoActual.getNome(), produtoActual);
        this->produtos.insert(parIntProdutoActual);
        this->produtoIdx.insert(parStringProdutoActual);
    }
    
    this->maxProdutcId = Produto::getNumProdutos();
    
    //ler produtos inactivos
    
    if (!inStreamProdutos.eof()) {
        
        unsigned int produtoId;
        string inactiveProducts; //lê a ultima linha do ficheiro que contém a lista de clientes inactivos
        getline(inStreamProdutos, inactiveProducts);
        getline(inStreamProdutos, inactiveProducts);
        stringstream inactiveProductsStream(inactiveProducts);
        
        while (!inactiveProductsStream.eof()) {
            
            inactiveProductsStream >> produtoId;
            
            if (inactiveProductsStream.fail()) {
                
                break;
                
            }
            
            this->produtos.at(produtoId).setStatus(false);
            this->produtoIdx.at(this->produtos.at(produtoId).getNome()).setStatus(false);
            
        }
        
    }
    
    for (int i = 0; i < numeroTransacoes; i++) {
        
        Transacao transacaoActual(inStreamTransacoes);
        
        if (transacaoActual.getIdCliente() == 0) {
            continue;
        }
        
        vector <Produto> produtosActuais;
        Cliente clienteAtual(this->clientes.at(transacaoActual.getIdCliente()));
        
        for (size_t j = 0; j < transacaoActual.getProdutosString().size(); j++) {
            
            produtosActuais.push_back(this->produtoIdx.at(transacaoActual.getProdutosString().at(j)));
            
        }
        
        transacaoActual.setVectorProdutos(produtosActuais);
        transacaoActual.setCliente(clienteAtual);
        
        this->transacoes.push_back(transacaoActual);
        
        
    }
    
    for (size_t i = 0; i < this->transacoes.size(); i++) {
        
        for (size_t j = 0; j < this->transacoes.at(i).getProdutosProduto().size(); j++) {
            
            pair<int, int> parTransacaoClienteInt = make_pair(this->transacoes.at(i).getCliente().getId(), transacoes.at(i).getProdutosProduto().at(j).getProdutoId());
            
            this->transacaoIdx.insert(parTransacaoClienteInt);
            
        }
        
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
    
    Table clientsTable({ "ID", "Nome do Cliente", "Cartao de Cliente", "Volume de Compras" });
    
    for (iteClienteIdx = this->clienteIdx.begin(); iteClienteIdx != this->clienteIdx.end(); iteClienteIdx++) {
        
        if (iteClienteIdx == this->clienteIdx.begin()) {
            clientsTable.addNewLine(iteClienteIdx->second.toTable());
        }
        else {
            clientsTable.addNewLine(iteClienteIdx->second.toTable()); //AddDataInSameLine
        }
        
    }
    cout << clientsTable << endl;
    
}

// mostra a informacao individual de um cliente
bool VendeMaisMais::mostraInformacaoCliente(string nome){
    
    constIntClientString iterator = this->clienteIdx.find(nome);
    
    if (iterator == this->clienteIdx.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return false;
        
    }
    
    
    cout << "***************************************************" << endl;
    cout << "Id de Cliente: " << this->clienteIdx.at(nome).getId() << endl;
    cout << "Nome do Cliente: " << this->clienteIdx.at(nome).getNome() << endl;
    cout << "Cartão de Cliente: " << this->clienteIdx.at(nome).getCartaoCliente().mostrarData() << endl;
    
    string status;
    
    status =  this->clienteIdx.at(nome).getStatus() ? "Activo" : "Inactivo";
    
    cout << "Estado do Cliente: " << status << endl;
    return true;
    
}

bool VendeMaisMais::mostraInformacaoCliente(unsigned int clientId) {
    
    constIntClient iterator = this->clientes.find(clientId);
    
    if (iterator == this->clientes.end()) {
        
        cout << "O cliente não foi encontrado." << endl;
        return false;
    }
    
    cout << "***************************************************" << endl;
    cout << "Id de Cliente: " << this->clientes.at(clientId).getId() << endl;
    cout << "Nome do Cliente: " << this->clientes.at(clientId).getNome() << endl;
    cout << "Cartão de Cliente: " << this->clientes.at(clientId).getCartaoCliente().mostrarData() << endl;
    
    string status;
    
    status =  this->clientes.at(clientId).getStatus() ? "Activo" : "Inactivo";
    
    cout << "Estado do Cliente: " << status << endl;
    return true;
    
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

unsigned int VendeMaisMais::getMaxClienteId() const{
    
    return this->maxClientesId;
    
}


/*********************************
 Gestao de Produtos
 ********************************/

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{
    
    constIntProdutoString iteProdutoIdx;
    
    Table productsTable({ "Nome do Produto", "Custo", "Status"});
    
    for (iteProdutoIdx = this->produtoIdx.begin(); iteProdutoIdx != this->produtoIdx.end(); iteProdutoIdx++) {
        
        if (iteProdutoIdx == this->produtoIdx.begin()) {
            productsTable.addNewLine(iteProdutoIdx->second.toTable());
        }
        else {
            productsTable.addDataInSameLine(iteProdutoIdx->second.toTable()); //AddDataInSameLine
        }
        
    }
    cout << productsTable << endl;
    
}

void VendeMaisMais::adicionarProduto(string nomeProduto, float custoProduto){
    Produto novoProduto(nomeProduto, custoProduto);
    pair<unsigned int, Produto> parIntProdutoNovo = make_pair(novoProduto.getProdutoId(), novoProduto);
    pair<string, Produto> parStringProdutoNovo = make_pair(novoProduto.getNome(), novoProduto);
    this->produtos.insert(parIntProdutoNovo);
    this->produtoIdx.insert(parStringProdutoNovo);
    produtosAlterados = true;
    this->maxProdutcId = Produto::getNumProdutos();
    
}

void VendeMaisMais::eliminarProduto(string nome) {
    
    //verificar se o produto existe
    
    constIntProdutoString iterator = this->produtoIdx.find(nome);
    
    if (iterator == this->produtoIdx.end()) {
        
        cout << "O produto não foi encontrado." << endl;
        return;
        
    }
    
    //colocar o produto inactivo nos dois mapas
    
    if (this->produtoIdx.at(nome).getStatus()) {
        this->produtoIdx.at(nome).setStatus(false);
        this->produtos.at(this->produtoIdx.at(nome).getProdutoId()).setStatus(false);
        cout << "Produto eliminado correctamente" << endl;
        this->produtosAlterados = true;
    }
    
    else {
        
        cout << "O produto já se encontra eliminado." << endl;
        
    }
    
}

void VendeMaisMais::eliminarProduto(unsigned int produtoId) {
    
    //verificar se o cliente existe
    
    constIntProduto iterator = this->produtos.find(produtoId);
    
    if (iterator == this->produtos.end()) {
        
        cout << "O produto não foi encontrado." << endl;
        return;
        
    }
    
    if (this->produtos.at(produtoId).getStatus()) {
        
        this->produtos.at(produtoId).setStatus(false);
        this->produtoIdx.at(this->produtos.at(produtoId).getNome()).setStatus(false);
        cout << "Produto eliminado correctamente" << endl;
        this->produtosAlterados = true;
        
        
    } else {
        cout << "O produto já se encontra eliminado." << endl;
    }
    
}

void VendeMaisMais::reactivarProduto(string nome) {
    
    //verificar se o produto existe
    
    constIntProdutoString iterator = this->produtoIdx.find(nome);
    
    if (iterator == this->produtoIdx.end()) {
        
        cout << "O produto não foi encontrado." << endl;
        return;
        
    }
    
    //colocar o produto inactivo nos dois mapas
    
    if (!this->produtoIdx.at(nome).getStatus()) {
        this->produtoIdx.at(nome).setStatus(true);
        this->produtos.at(this->produtoIdx.at(nome).getProdutoId()).setStatus(true);
        cout << "Produto reactivado correctamente" << endl;
        this->produtosAlterados = true;
    }
    
    else {
        
        cout << "O produto já se encontra activo." << endl;
        
    }
    
}

void VendeMaisMais::reactivarProduto(unsigned int produtoId) {
    
    //verificar se o cliente existe
    
    constIntProduto iterator = this->produtos.find(produtoId);
    
    if (iterator == this->produtos.end()) {
        
        cout << "O produto não foi encontrado." << endl;
        return;
        
    }
    
    if (!this->produtos.at(produtoId).getStatus()) {
        
        this->produtos.at(produtoId).setStatus(true);
        this->produtoIdx.at(this->produtos.at(produtoId).getNome()).setStatus(true);
        cout << "Produto reactivado correctamente" << endl;
        this->produtosAlterados = true;
        
        
    } else {
        cout << "O produto já se encontra activo." << endl;
    }
    
}

unsigned int VendeMaisMais::getMaxProductId() const {
    
    return this->maxProdutcId;
    
}

void VendeMaisMais::registarTransacao(unsigned int idCliente, vector <unsigned int> produtos) {
    
    
    constIntClient iteradorClientes = this->clientes.find(idCliente);
    
    if (iteradorClientes == this->clientes.end()) {
        
        cout << "Nao foi possivel registar a transacao: o Cliente não foi encontrado." << endl;
        return;
        
    }
    
    Cliente clienteTransacao(iteradorClientes->second);
    
    vector <Produto> produtosTransacao;
    
    for (size_t i = 0; i < produtos.size(); i++) {
        
        constIntProduto iteradorProdutos = this->produtos.find(produtos.at(i));
        
        if (iteradorProdutos != this->produtos.end() && this->produtos.at(produtos.at(i)).getStatus()) {
            
            produtosTransacao.push_back(this->produtos.at(produtos.at(i)));
            
        }
        
    }
    
    if (produtosTransacao.size() == 0) {
        
        cout << "Nao foi possivel registar a transacao: nenhum dos produtos foi encontrado." << endl;
        return;
        
    }
    
    
    Transacao transacaoInserir(clienteTransacao, produtosTransacao);
    
    this->transacoes.push_back(transacaoInserir);
    
    for (size_t i = 0; i < transacaoInserir.getProdutosProduto().size(); i++) {
        
        pair<int, int> parTransacaoClienteInt = make_pair(transacaoInserir.getCliente().getId(), transacaoInserir.getProdutosProduto().at(i).getProdutoId());
        
        this->transacaoIdx.insert(parTransacaoClienteInt);
        
    }
    
    this->clientes.at(idCliente).acrescentarCompras(transacaoInserir.getTotal());
    this->clienteIdx.at(clientes.at(idCliente).getNome()).acrescentarCompras(transacaoInserir.getTotal());
    
    
}



/*********************************
 Preservar Informacao
 ********************************/

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada

void VendeMaisMais::saveChanges() const{
    
    ofstream outClientes(this->fichClientes);
    ofstream outProducts(this->fichProdutos);
    ofstream outTransacoes(this->fichTransacoes);
    
    //escrever todos os clientes
    outClientes << this->clientes.size() << endl;
    
    constIntClient iterator;
    
    for (iterator = this->clientes.begin(); iterator != this->clientes.end(); iterator++) {
        
        iterator->second.save(outClientes);
    
        
    }
    //escrever o numero dos clientes inactivos
    outClientes << FILE_SEPRATOR << endl;
    
    for (iterator = this->clientes.begin(); iterator != this->clientes.end(); iterator++) {
        
        if (!iterator->second.getStatus()) {
            
            outClientes << iterator->first;
            outClientes << " ";
            
        }
        
    }
    
    //escrever todos os produtos
    outProducts << this->produtos.size() << endl;
    
    constIntProduto iteratorProduto;
    
    for (iteratorProduto = this->produtos.begin(); iteratorProduto != this->produtos.end(); iteratorProduto++) {
        
        iteratorProduto->second.save(outProducts);
        
        
    }
    //escrever o numero dos clientes inactivos
    outProducts << FILE_SEPRATOR << endl;
    
    for (iteratorProduto = this->produtos.begin(); iteratorProduto != this->produtos.end(); iteratorProduto++) {
        
        if (!iteratorProduto->second.getStatus()) {
            
            outProducts << iteratorProduto->first;
            outProducts << " ";
            
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