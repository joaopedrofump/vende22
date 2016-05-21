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

<<<<<<< HEAD
VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes) {

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
		transacaoActual.calculateTotal();

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

=======
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
        
<<<<<<< HEAD
=======
        //cout << "teste" << endl;
        
>>>>>>> LEO
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
    
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
}

/*********************************
Gestao de Clientes
********************************/

// lista os cleinets por ordem alfabetica crescente
<<<<<<< HEAD
void VendeMaisMais::listarClientesOrdemAlfa(bool onlyActives) const {

	constIntClientString iteClienteIdx;

	Table clientsTable({ "ID", "Nome do Cliente", "Cartao de Cliente", "Volume de Compras" , "Status" });

	if (onlyActives) {

		bool firstActive = false;
		for (iteClienteIdx = this->clienteIdx.begin(); iteClienteIdx != this->clienteIdx.end(); iteClienteIdx++) {
			if (iteClienteIdx->second.getStatus() && !firstActive) {

				clientsTable.addNewLine(iteClienteIdx->second.toTable());
				firstActive = true;
				continue;
			}

			if (iteClienteIdx->second.getStatus() && firstActive) {

				clientsTable.addDataInSameLine(iteClienteIdx->second.toTable()); //addDataInSameLine
			}
		}
	}

	else {
		for (iteClienteIdx = this->clienteIdx.begin(); iteClienteIdx != this->clienteIdx.end(); iteClienteIdx++) {

			if (iteClienteIdx == this->clienteIdx.begin()) {

				clientsTable.addNewLine(iteClienteIdx->second.toTable());
			}
			else {

				clientsTable.addDataInSameLine(iteClienteIdx->second.toTable()); //addDataInSameLine
			}
		}
	}
	
	cout << clientsTable << endl;

}

// mostra a informacao individual de um cliente
bool VendeMaisMais::mostraInformacaoCliente(string nome) {

	constIntClientString iterator = this->clienteIdx.find(nome);

	if (iterator == this->clienteIdx.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}

	stringstream ss;
	ss << this->clienteIdx.at(nome).getId();
	string str = ss.str();

	Table mostrarCliente({ "Id de Cliente: " , str });  // Mostra o id

	ss.str("");
	ss << this->clienteIdx.at(nome).getNome();
	str = ss.str();

	mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

	ss.str("");
	ss << this->clienteIdx.at(nome).getCartaoCliente().mostrarData();
	str = ss.str();

	mostrarCliente.addNewLine({ "Cartao de Cliente: " , str });

	str = this->clienteIdx.at(nome).getStatus() ? "Activo" : "Inactivo";


	mostrarCliente.addNewLine({ "Estado do Cliente: " , str });

	cout << mostrarCliente;

=======
void VendeMaisMais::listarClientesOrdemAlfa() const{
    
    constIntClientString iteClienteIdx;
    
<<<<<<< HEAD
    Table clientsTable({ "ID", "Nome do Cliente", "Cartao de Cliente", "Volume de Compras" });
=======
    Table clientsTable({ "ID", "Nome do Cliente", "Cartao de Cliente", "Volume de Compras" , "Status"});
>>>>>>> LEO
    
    for (iteClienteIdx = this->clienteIdx.begin(); iteClienteIdx != this->clienteIdx.end(); iteClienteIdx++) {
        
        if (iteClienteIdx == this->clienteIdx.begin()) {
            clientsTable.addNewLine(iteClienteIdx->second.toTable());
        }
        else {
            clientsTable.addDataInSameLine(iteClienteIdx->second.toTable()); //addDataInSameLine
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
    
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
	return true;

	/*
	cout << "***************************************************" << endl;
	cout << "Id de Cliente: " << this->clienteIdx.at(nome).getId() << endl;
	cout << "Nome do Cliente: " << this->clienteIdx.at(nome).getNome() << endl;
	cout << "Cartão de Cliente: " << this->clienteIdx.at(nome).getCartaoCliente().mostrarData() << endl;

	string status;

	status = this->clienteIdx.at(nome).getStatus() ? "Activo" : "Inactivo";

	cout << "Estado do Cliente: " << status << endl;
	return true;
	*/
}

bool VendeMaisMais::mostraInformacaoCliente(unsigned int clientId) {

	constIntClient iterator = this->clientes.find(clientId);

	if (iterator == this->clientes.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;
	}

	stringstream ss;
	ss << this->clientes.at(clientId).getId();
	string str = ss.str();

	Table mostrarCliente({ "Id de Cliente: " , str });  // Mostra o id

	ss.str("");
	ss << this->clientes.at(clientId).getNome();
	str = ss.str();

	mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

	ss.str("");
	ss << this->clientes.at(clientId).getCartaoCliente().mostrarData();
	str = ss.str();

	mostrarCliente.addNewLine({ "Cartao de Cliente: " , str });

<<<<<<< HEAD
	str = this->clientes.at(clientId).getStatus() ? "Activo" : "Inactivo";


	mostrarCliente.addNewLine({ "Estado do Cliente: " , str });

=======
    str =  this->clientes.at(clientId).getStatus() ? "Activo" : "Inactivo";
    
<<<<<<< HEAD
    cout << "Estado do Cliente: " << status << endl;
    return true;
=======
	mostrarCliente.addNewLine({ "Estado do Cliente: " , str });
>>>>>>> LEO
    
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
	cout << mostrarCliente;

	return true;
}

bool VendeMaisMais::encontrarCliente(unsigned int clienteId) {
	constIntClient iterator = this->clientes.find(clienteId);

	if (iterator == this->clientes.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}
	else if (!this->clientes.at(clienteId).getStatus()) {

		cout << "O cliente encontra-se inativo." << endl;
		return false;
	}
	else{
		return true;
	}
}

bool VendeMaisMais::encontrarCliente(string nome) {
	//verificar se o cliente existe

	constIntClientString iterator = this->clienteIdx.find(nome);

	if (iterator == this->clienteIdx.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}
} 

bool VendeMaisMais::eliminarCliente(string nome) {

	//verificar se o cliente existe

	constIntClientString iterator = this->clienteIdx.find(nome);

	if (iterator == this->clienteIdx.end()) {

		cout << "O cliente não foi encontrado." << endl;
		return false;

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

	return true;
}

bool VendeMaisMais::eliminarCliente(unsigned int clientId) {

	//verificar se o cliente existe

	constIntClient iterator = this->clientes.find(clientId);

	if (iterator == this->clientes.end()) {

		cout << "O cliente não foi encontrado." << endl;
		return false;

	}

	if (this->clientes.at(clientId).getStatus()) {

		this->clientes.at(clientId).setStatus(false);
		this->clienteIdx.at(this->clientes.at(clientId).getNome()).setStatus(false);
		cout << "Cliente eliminado correctamente" << endl;
		this->clientesAlterados = true;


	}
	else {
		cout << "O cliente já se encontra eliminado." << endl;
	}
	return true;
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


	}
	else {
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

		this->clientesAlterados = true;

	}

	else {

		cout << "Cliente não inserido" << endl;
	}

}

unsigned int VendeMaisMais::getMaxClienteId() const {

	return this->maxClientesId;

}

map<unsigned int, Cliente> VendeMaisMais::getMapIDtoCliente() const {
	return clientes;
}

map<string, Cliente> VendeMaisMais::getMapNametoCliente() const {
	return clienteIdx;
}


/*********************************
Gestao de Produtos
********************************/

// lisat os produto por ordem alfabetica crescente
<<<<<<< HEAD
void VendeMaisMais::listarProdutos(bool onlyActives) const {

=======
void VendeMaisMais::listarProdutos() const{
    
<<<<<<< HEAD
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
=======
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
	constIntProdutoString iteProdutoIdx;

	Table productsTable({ "ID", "Nome do Produto", "Custo", "Status " });

	if (onlyActives) {

		bool firstActive = false;
		for (iteProdutoIdx = this->produtoIdx.begin(); iteProdutoIdx != this->produtoIdx.end(); iteProdutoIdx++) {
			if (iteProdutoIdx->second.getStatus() && !firstActive) {

				productsTable.addNewLine(iteProdutoIdx->second.toTable());
				firstActive = true;
				continue;
			}

			if (iteProdutoIdx->second.getStatus() && firstActive) {

				productsTable.addDataInSameLine(iteProdutoIdx->second.toTable()); //addDataInSameLine
			}
		}
	}
	else{
		for (iteProdutoIdx = this->produtoIdx.begin(); iteProdutoIdx != this->produtoIdx.end(); iteProdutoIdx++) {
			if (iteProdutoIdx == this->produtoIdx.begin()) {
				productsTable.addNewLine(iteProdutoIdx->second.toTable());
			}
			else {
				productsTable.addDataInSameLine(iteProdutoIdx->second.toTable()); //AddDataInSameLine
			}
		}
	}

	cout << productsTable << endl;
<<<<<<< HEAD


=======
>>>>>>> LEO
    
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
}

void VendeMaisMais::adicionarProduto(string nomeProduto, float custoProduto) {
	Produto novoProduto(nomeProduto, custoProduto);
	pair<unsigned int, Produto> parIntProdutoNovo = make_pair(novoProduto.getProdutoId(), novoProduto);
	pair<string, Produto> parStringProdutoNovo = make_pair(novoProduto.getNome(), novoProduto);
	this->produtos.insert(parIntProdutoNovo);
	this->produtoIdx.insert(parStringProdutoNovo);
	produtosAlterados = true;
	this->maxProdutcId = Produto::getNumProdutos();

}

bool VendeMaisMais::eliminarProduto(string nome) {

	//verificar se o produto existe

	constIntProdutoString iterator = this->produtoIdx.find(nome);

	if (iterator == this->produtoIdx.end()) {

		cout << "O produto não foi encontrado." << endl;
		return false;

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

	return true;
}

bool VendeMaisMais::eliminarProduto(unsigned int produtoId) {

	//verificar se o cliente existe

	constIntProduto iterator = this->produtos.find(produtoId);

	if (iterator == this->produtos.end()) {

		cout << "O produto não foi encontrado." << endl;
		return false;

	}

	if (this->produtos.at(produtoId).getStatus()) {

		this->produtos.at(produtoId).setStatus(false);
		this->produtoIdx.at(this->produtos.at(produtoId).getNome()).setStatus(false);
		cout << "Produto eliminado correctamente" << endl;
		this->produtosAlterados = true;


	}
	else {
		cout << "O produto já se encontra eliminado." << endl;
	}

	return true;
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


	}
	else {
		cout << "O produto já se encontra activo." << endl;
	}

}

bool VendeMaisMais::encontrarProduto(string nome) {
	//verificar se o produto existe

	constIntProdutoString iterator = this->produtoIdx.find(nome);

	if (iterator == this->produtoIdx.end()) {

		Table produtoNaoEncontrado({ "O produto nao foi encontrado." });
		cout << produtoNaoEncontrado << endl;
		ignoreLine(false);
		return false;

	}
}

bool VendeMaisMais::encontrarProduto(unsigned int produtoId) {
	constIntProduto iterator = this->produtos.find(produtoId);

	if (iterator == this->produtos.end()) {

		Table produtoNaoEncontrado({ "O produto nao foi encontrado." });
		cout << produtoNaoEncontrado << endl;
		ignoreLine(false);
		return false;

	}
	else if (!this->produtos.at(produtoId).getStatus()) {

		cout << "O produto encontra-se inativo." << endl;
		return false;
	}
	else {
		return true;
	}
}

unsigned int VendeMaisMais::getMaxProductId() const {

	return this->maxProdutcId;

}

<<<<<<< HEAD

/*********************************
Gestao de Transacoes
********************************/

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

		Table erroProdutoNaoEncontrado({ "Nao foi possivel registar a transacao: nenhum dos produtos foi encontrado." });
		cout << erroProdutoNaoEncontrado << endl;
		ignoreLine(false);
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

=======
<<<<<<< HEAD
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
    
    
=======
map<unsigned int, Cliente> VendeMaisMais::getMapIDtoCliente() const {
	return this->clientes;
>>>>>>> LEO
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
}

void VendeMaisMais::listarTransacoes() const {


	Table clientsTable({ "ID", "Nome do Cliente", "Data da compra", "Total", "Produtos comprados" });

	for (size_t i = this->transacoes.size(); i >= 1; i--) {

		if (i == this->transacoes.size()) {
			clientsTable.addNewLine(transacoes.at(i - 1).toTable());
		}
		else {
			clientsTable.addDataInSameLine(transacoes.at(i - 1).toTable());
		}

	}
	cout << clientsTable;
}

void VendeMaisMais::listarTransacoes(unsigned int clienteId) {

	Table clientsTable({ "ID", "Nome do Cliente", "Data da compra", "Total", "Produtos comprados" });

	constIntClient iteradorClientes = this->clientes.find(clienteId);

	if (iteradorClientes == this->clientes.end()) {

		ignoreLine(false, "O cliente nao foi encontrado");
		return;

	}

	bool primeiraVez = false;

	for (size_t i = this->transacoes.size(); i >= 1; i--) {

		if (this->transacoes.at(i - 1).getCliente().getId() == iteradorClientes->first) {

			if (!primeiraVez) {
				clientsTable.addNewLine(transacoes.at(i - 1).toTable());
				primeiraVez = true;
			}
			else {
				clientsTable.addDataInSameLine(transacoes.at(i - 1).toTable());
			}

		}

	}
	cout << clientsTable;

}

void VendeMaisMais::listarTransacoes(string data1, string data2, bool dataUnica) {

	data2 = dataUnica ? data1 : data2;

	Data dataMenor(data1);
	Data dataMaior(data2);

	if (!(dataMaior >= dataMenor)) {

		Data dataTemp;
		dataTemp = dataMaior;
		dataMaior = dataMenor;
		dataMenor = dataTemp;

	}

	Table clientsTable({ "ID", "Nome do Cliente", "Data da compra", "Total", "Produtos comprados" });

	vector<vector<string>> vetorTabela = { { "ID", "Nome do Cliente", "Data da compra", "Total", "Produtos comprados" } };

	bool primeiraVez = false;

	for (size_t i = this->transacoes.size(); i >= 1; i--) {

		if (transacoes.at(i - 1).getData() >= dataMenor && dataMaior >= transacoes.at(i - 1).getData()) {

			if (!primeiraVez) {
				clientsTable.addNewLine(transacoes.at(i - 1).toTable());
				primeiraVez = true;
			}
			else {
				clientsTable.addDataInSameLine(transacoes.at(i - 1).toTable());
			}

		}

	}
	if (clientsTable.getTableVector() == vetorTabela) {
		Table erro({ "Nao existem transacoes na(s) data(s) indicadas." });
		cout << erro;
	}
	else
		cout << clientsTable;

}

void VendeMaisMais::listarTransacoesProduto(unsigned int idProduto) {


	constIntProduto iteradorProduto = this->produtos.find(idProduto);

	if (iteradorProduto == this->produtos.end()) {

		ignoreLine(false, "O produto nao foi encontrado.");
		return;

	}

	Table clientsTable({ "ID", "Nome do Cliente", "Data da compra", "Total", "Produtos comprados" });

	vector<vector<string>> vetorTabela = { { "ID", "Nome do Cliente", "Data da compra", "Total", "Produtos comprados" } };

	bool primeiraVez = false;

	for (size_t i = transacoes.size(); i >= 1; i--) {


		for (size_t j = 0; j < transacoes.at(i - 1).getProdutosProduto().size(); j++) {

			if (idProduto == transacoes.at(i - 1).getProdutosProduto().at(j).getProdutoId()) {

				//cout << this->transacoes.at(i - 1) << endl;

				if (!primeiraVez) {
					clientsTable.addNewLine(transacoes.at(i - 1).toTable());
					primeiraVez = true;
				}
				else {
					clientsTable.addDataInSameLine(transacoes.at(i - 1).toTable());
				}

			}


		}

	}

	if (clientsTable.getTableVector() == vetorTabela) {
		Table erro({ "Nao existem transacoes com o(s) produto(s) indicado(s)." });
		cout << erro;
	}
	else
		cout << clientsTable;

}

/*********************************
Preservar Informacao
********************************/

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada

<<<<<<< HEAD
void VendeMaisMais::saveChanges() const {

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


=======
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
    
    
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
}

/*********************************
Mostrar Loja
********************************/

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado) {

	// A IMPLEMENTAR 
	return out; // TESTE

}