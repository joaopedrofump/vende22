/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#include "Vende++.h"
#include <fstream>
#include <iostream>
using namespace std;

string const FILE_SEPRATOR = "------------------------------------------------";
typedef map<unsigned int, Cliente>::const_iterator constIntClient;
typedef map<string, Cliente>::const_iterator constIntClientString;

typedef map<unsigned int, Produto>::const_iterator constIntProduto;
typedef map<string, Produto>::const_iterator constIntProdutoString;

typedef multimap<unsigned int, unsigned int>::const_iterator constIteMMTra;
typedef pair <multimap<unsigned int,unsigned int>::iterator, multimap<unsigned int,unsigned int>::iterator> iteradorPar;

VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){
    
    ifstream inStreamClientes, inStreamProdutos, inStreamTransacoes;
    
    Cliente::setNumClientes(0);
    Produto::setNumProdutos(0);
    
    unsigned int numeroClientes = 0;
    unsigned int numeroProdutos = 0;
    unsigned int numeroTransacoes = 0;
    
    this->loja = loja;
    this->fichClientes = fichClients;
    this->fichProdutos = fichProdutos;
    this->fichTransacoes = fichTransacoes;
    
    inStreamClientes.open(this->fichClientes.c_str());
    if (!inStreamClientes.eof()) {
        inStreamClientes >> numeroClientes;
        inStreamClientes.ignore(1000, '\n');
    }
    
    inStreamProdutos.open(this->fichProdutos.c_str());
    if (!inStreamProdutos.eof()) {
        inStreamProdutos >> numeroProdutos;
        inStreamProdutos.ignore(1000, '\n');
    }
    
    inStreamTransacoes.open(this->fichTransacoes.c_str());
    if (!inStreamTransacoes.eof()) {
        inStreamTransacoes >> numeroTransacoes;
        inStreamTransacoes.ignore(1000, '\n');
    }
    
    
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
        string inactiveProducts; //lê a ultima linha do ficheiro que contém a lista de produtos inactivos
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
        transacaoActual.calculateTotal();
        transacaoActual.setCliente(clienteAtual);
        
        this->transacoes.push_back(transacaoActual);
        
        
    }
    
    for (size_t i = 0; i < this->transacoes.size(); i++) {
        
        for (size_t j = 0; j < this->transacoes.at(i).getProdutosProduto().size(); j++) {
            
            pair<int, int> parTransacaoClienteInt = make_pair(this->transacoes.at(i).getCliente().getId(), transacoes.at(i).getProdutosProduto().at(j).getProdutoId());
            
            this->transacaoIdx.insert(parTransacaoClienteInt);
            
        }
        
    }
    
    preencherMatrizes();
    
    inStreamClientes.close();
    inStreamProdutos.close();
    inStreamTransacoes.close();

}

/*********************************
Gestao de Clientes
********************************/

// lista os cleinets por ordem alfabetica crescente
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

	ss.str("");
	ss << this->clienteIdx.at(nome).getVolCompras();
	str = ss.str();

	mostrarCliente.addNewLine({ "Volume de compras: " , str });

	cout << mostrarCliente;

	Table transacoes({ "Ultimas transacoes:" });
	listarTransacoes(clienteIdx.at(nome).getId());

	return true;

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

	str = this->clientes.at(clientId).getStatus() ? "Activo" : "Inactivo";

	mostrarCliente.addNewLine({ "Estado do Cliente: " , str });


	ss.str("");
	ss << this->clientes.at(clientId).getVolCompras();
	str = ss.str();

	mostrarCliente.addNewLine({ "Volume de compras: " , str });

	cout << mostrarCliente;
	
	Table transacoes({ "Ultimas transacoes:" });
	listarTransacoes(clientId);

	return true;
}

bool VendeMaisMais::encontrarCliente(unsigned int clienteId) {
	//verificar se o cliente existe e se está ativo

	constIntClient iterator = this->clientes.find(clienteId);

	if (iterator == this->clientes.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}
	else if (!this->clientes.at(clienteId).getStatus()) {

		Table clienteNaoEncontrado({ "O cliente encontra-se inativo." });
		cout << clienteNaoEncontrado << endl;

		return false;
	}
	else {
		return true;
	}
}

bool VendeMaisMais::encontrarCliente(string nome) {
	//verificar se o cliente existe e se está ativo

	constIntClientString iterator = this->clienteIdx.find(nome);

	if (iterator == this->clienteIdx.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}
	else if (!this->clienteIdx.at(nome).getStatus()) {

		Table clienteNaoEncontrado({ "O cliente encontra-se inativo." });
		cout << clienteNaoEncontrado << endl;
		return false;
	}
	
    return true;
}

bool VendeMaisMais::eliminarCliente(string nome) {

	//verificar se o cliente existe

	constIntClientString iterator = this->clienteIdx.find(nome);

	if (iterator == this->clienteIdx.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}

	//colocar o cliente inactivo nos dois mapas

	if (this->clienteIdx.at(nome).getStatus()) {
		this->clienteIdx.at(nome).setStatus(false);
		this->clientes.at(this->clienteIdx.at(nome).getId()).setStatus(false); 
		
		Table clienteNaoEncontrado({ "Cliente eliminado correctamente." });
		cout << clienteNaoEncontrado << endl;

		this->clientesAlterados = true;
	}

	else {

		Table clienteNaoEncontrado({ "O cliente ja se encontra eliminado." });
		cout << clienteNaoEncontrado << endl;

	}

	return true;
}

bool VendeMaisMais::eliminarCliente(unsigned int clientId) {

	//verificar se o cliente existe

	constIntClient iterator = this->clientes.find(clientId);

	if (iterator == this->clientes.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}

	if (this->clientes.at(clientId).getStatus()) {

		this->clientes.at(clientId).setStatus(false);
		this->clienteIdx.at(this->clientes.at(clientId).getNome()).setStatus(false);

		Table clienteNaoEncontrado({ "Cliente eliminado correctamente." });
		cout << clienteNaoEncontrado << endl;

		this->clientesAlterados = true;


	}
	else {
		Table clienteNaoEncontrado({ "O cliente ja se encontra eliminado." });
		cout << clienteNaoEncontrado << endl;
	}
	return true;
}

bool VendeMaisMais::reactivarCliente(string nome) {

	//verificar se o cliente existe

	constIntClientString iterator = this->clienteIdx.find(nome);

	if (iterator == this->clienteIdx.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}

	//colocar o cliente inactivo nos dois mapas

	if (!this->clienteIdx.at(nome).getStatus()) {
		this->clienteIdx.at(nome).setStatus(true);
		this->clientes.at(this->clienteIdx.at(nome).getId()).setStatus(true);

		Table clienteNaoEncontrado({ "Cliente reativado correctamente." });
		cout << clienteNaoEncontrado << endl;

		this->clientesAlterados = true;
	}

	else {

		Table clienteNaoEncontrado({ "O cliente ja se encontra activo." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}

	return true;

}

bool VendeMaisMais::reactivarCliente(unsigned int clientId) {

	//verificar se o cliente existe

	constIntClient iterator = this->clientes.find(clientId);

	if (iterator == this->clientes.end()) {

		Table clienteNaoEncontrado({ "O cliente nao foi encontrado." });
		cout << clienteNaoEncontrado << endl;
		return false;

	}

	if (!this->clientes.at(clientId).getStatus()) {

		this->clientes.at(clientId).setStatus(true);
		this->clienteIdx.at(this->clientes.at(clientId).getNome()).setStatus(true);

		Table clienteNaoEncontrado({ "Cliente reativado correctamente." });
		cout << clienteNaoEncontrado << endl;

		this->clientesAlterados = true;


	}
	else {
		Table clienteNaoEncontrado({ "O cliente ja se encontra activo." });
		cout << clienteNaoEncontrado << endl;
		return false;
	}

	return true;
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

map<unsigned int, Produto> VendeMaisMais::getMapIDtoProduct() const {
	return this->produtos;
}


/*********************************
Gestao de Produtos
********************************/

// lisat os produto por ordem alfabetica crescente

void VendeMaisMais::listarProdutos(bool onlyActives) const {

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
	else {
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
    
    return true;
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


}

/*********************************
 Recomendações
 ********************************/

// ================ CALCULAR RECOMENDAÇOES =======================

unsigned int VendeMaisMais::obterProdutoRecomendado(Produto &produtoRecomendado, unsigned int idCliente) {
    
    constIteMMTra iteradorMM;
    iteradorPar iterador = this->transacaoIdx.equal_range(idCliente);
    vector<unsigned int> linhaClienteAlvo; //linha do cliente alvo na matriz
    
    //calcular matriz
    vector <vector <unsigned int>> matriz;
    
    for (constIntClient i = this->clientes.begin(); i != this->clientes.end(); i++) {
        
        //não colocar o cliente alvo na matriz
        
        vector <unsigned int> linhaActual;
        
        linhaActual.push_back(i->first); //primeiro elemento de cada linha é o id de cada cliente
        
        //inicializar com 0s o resto da linha
        for (constIntProduto itePro = this->produtos.begin(); itePro != this->produtos.end(); itePro++) {
            
            linhaActual.push_back(0);
            
        }
        
        
        //preencher o resto do vector de int com o numero de vezes que o cliente comprou cada produto
       
            
        iterador = this->transacaoIdx.equal_range(i->first); //obter os produtos comprados pelo cliente
        
        for (iteradorMM = iterador.first; iteradorMM != iterador.second; iteradorMM++) {
            
            if (this->produtos.at(iteradorMM->second).getStatus()) {
                
                linhaActual.at(iteradorMM->second)++;
                
            }
            
        }
        
        if (i->first == idCliente) {
            
            linhaClienteAlvo = linhaActual;
            
        }
        
        matriz.push_back(linhaActual);
    }
    
     //grava no vector de matrizes que pertence a classe
    
    //juntar a cada vector da matriz no final, o número de coincidencias desse cliente com o cliente alvo para depois contabilizar apenas os que tiverem o numero maximo de coincidencias
    
    unsigned int numeroMaximoCoincidencias = 0;
    
    for (size_t i = 0; i < matriz.size(); i++) {
        
        unsigned int numeroMaximoCoincidenciasActual = 0;
        
        if (matriz.at(i).at(0) == idCliente) {
            
            continue;
            
        }
        
        for (size_t j = 1; j < matriz.at(i).size(); j++) {
            
            if (linhaClienteAlvo.at(j) > 0 && matriz.at(i).at(j) > 0) {
                
                numeroMaximoCoincidenciasActual++;
                
            }
            
        }
        
        matriz.at(i).push_back(numeroMaximoCoincidenciasActual);
        
        numeroMaximoCoincidencias = numeroMaximoCoincidenciasActual > numeroMaximoCoincidencias ? numeroMaximoCoincidenciasActual : numeroMaximoCoincidencias;
        
    }
    
    this->matrizes.push_back(matriz);
    
    
    //preencher um vetor de inteiros com o numero de coincidencias de cada cliente
    
    vector<unsigned int> vetorCoincidencias;
    
    for (size_t i = 0; i < matriz.size(); i++) {
        
        bool insere = true;
        
        if (matriz.at(i).at(0) == idCliente) {
            
            continue;
            
        }
        
        for (size_t j = 0; j < vetorCoincidencias.size(); j++) {
            
            if (matriz.at(i).at(matriz.at(i).size() - 1) == vetorCoincidencias.at(j)) {
                
                insere = false;
                
            }
            
        }
        
        if (insere) {
            vetorCoincidencias.push_back(matriz.at(i).at(matriz.at(i).size() - 1));
        }
  
    }
    
    sort(vetorCoincidencias.begin(), vetorCoincidencias.end());
    reverse(vetorCoincidencias.begin(), vetorCoincidencias.end());
    
    bool flagNumeroCoincidenciasReal; //flag que controla se realmente o numero de coincidencias é zero ou se nenhum dos clientes com coincidencias compraram produtos que o cliente alvo ainda não tenha comprado
    
    flagNumeroCoincidenciasReal = vetorCoincidencias.at(0) ? true : false;
    
    
    //descobrir o número maximo de coincidencias para escolher clientes (para o caso de não haver nenhum cliente com o número máximo de coincidencias com pelo menos um produto comprado além das coincidencias)
    
    
    bool sairFor2 = false;
    
    for (size_t h = 0; h < vetorCoincidencias.size(); h++) {
        
        numeroMaximoCoincidencias = vetorCoincidencias.at(h);
        
        if (numeroMaximoCoincidencias == 0) {
            break;
            
        }
        
        bool sairFor = false;
        
        for (size_t i = 0; i < matriz.size(); i++) {
            
            
            if (matriz.at(i).at(0) == idCliente || ((matriz.at(i).at(matriz.at(i).size() - 1)) != numeroMaximoCoincidencias)) {
                
                continue;
                
            }
            
            for (size_t j = 1; j < matriz.at(i).size()-1; j++) {
                
                if (linhaClienteAlvo.at(j) > 0) {
                    
                    continue;
                    
                }
                
                if (matriz.at(i).at(j) > 0) {
                    
                    sairFor = true;
                    sairFor2 = true;
                    break;
                    
                }
                
            }
            
            if (sairFor) {
                break;
            }
            
        }
        
        if (sairFor2) {
            break;
        }
        
    }

    //cout << numeroMaximoCoincidencias << endl;
    
    if (numeroMaximoCoincidencias == 0) {
        
        iteradorMM = this->transacaoIdx.find(idCliente);
        
        if (iteradorMM == this->transacaoIdx.end()) {
            
            produtoRecomendado = obterProdutoMaisVendido(idCliente, numeroMaximoCoincidencias, flagNumeroCoincidenciasReal); //cliente nao comprou nada
            return 0;
            
        }
        
        else {
            
            produtoRecomendado = obterProdutoMaisVendido(idCliente, numeroMaximoCoincidencias, flagNumeroCoincidenciasReal);
            
            if (flagNumeroCoincidenciasReal) {
                
                bool comprouTodosProdutos = true;
                
                for (size_t i = 1; i < linhaClienteAlvo.size(); i++) {
                    
                    if (linhaClienteAlvo.at(i) == 0 && this->produtos.at((int)i).getStatus()) {
                        
                        comprouTodosProdutos = false;
                        break;
                        
                    }
                    
                }
                
                if (comprouTodosProdutos) {
                    
                    return 4; //cliente comprou todos os produtos
                    
                }
                
                return 3; //nenhum dos clientes com coincidencias compraram produtos que o cliente alvo ainda não tenha comprado
            }
            return 1; //cliente comprou mas nao ha ninguem que tenha comprado o mesmo
        }
        
        
    }
    
    else { //ha coincidencias
        
        produtoRecomendado = obterProdutoMaisVendido(idCliente, numeroMaximoCoincidencias, flagNumeroCoincidenciasReal);
        return 2;
        
    }
    
    return 5;
}

Produto VendeMaisMais::obterProdutoMaisVendido(unsigned int clienteId, unsigned int numCoincidencias, bool numCoincidenciasReal) const {
    
    vector <unsigned int> totalProdutos(this->produtos.size()+1, 0);
    unsigned int idProdutoMaisMais = 1; //id do produto mais comprado
    unsigned int numClientsSemelhantes = 0;
    
    if (numCoincidencias == 0) {
            
        for (size_t i = 0; i < matrizes.at(clienteId-1).size(); i++) {
            
            if (matrizes.at(clienteId-1).at(i).at(0) == clienteId) {
                continue;
            }
            
            for (size_t j = 1; j < matrizes.at(clienteId-1).at(0).size()-1; j++) {
                
                if (matrizes.at(clienteId-1).at(i).at(j) > 0) {
                    
                    totalProdutos.at(j)++;
                    
                }
                
            }
            
        }
        
        for (size_t i = 2; i < totalProdutos.size(); i++) {
            
            if (totalProdutos.at(i) > totalProdutos.at(idProdutoMaisMais)) {
                
                idProdutoMaisMais = (int)i;
                
            }
            
        }
        
    }
    
    else {
        
        vector<unsigned int> linhaCliente;
        
        for (size_t i = 0; i < matrizes.at(clienteId-1).size(); i++) {
            
            if (matrizes.at(clienteId-1).at(i).at(0) != clienteId && matrizes.at(clienteId-1).at(i).at(matrizes.at(clienteId-1).at(i).size()-1) == numCoincidencias)
                
            {
                
                numClientsSemelhantes++; //calcular se há mais do que um cliente semelhante
                
            }
        }
        
        //obter linha do cliente alvo para comparar com as outras
        for (size_t i = 0; i < matrizes.at(clienteId-1).size(); i++) {
            
            if (matrizes.at(clienteId-1).at(i).at(0) == clienteId) {
                
                linhaCliente = matrizes.at(clienteId-1).at(i);
                
            }
            
        }
        
        for (size_t i = 0; i < matrizes.at(clienteId-1).size(); i++) {
            
            if (matrizes.at(clienteId-1).at(i).at(0) == clienteId || matrizes.at(clienteId-1).at(i).at(matrizes.at(clienteId-1).at(i).size()-1) != numCoincidencias)
                
            {
                
                continue;
                
            }
            
            
            
            for (size_t j = 1; j < matrizes.at(clienteId-1).at(i).size()-2; j++) {
                
                if (linhaCliente.at(j) > 0) {
                    
                    continue;
                    
                }
                
                if (numClientsSemelhantes < 2) {
                    totalProdutos.at(j) += matrizes.at(clienteId-1).at(i).at(j);
                }
                
                else {
                    
                    if (matrizes.at(clienteId-1).at(i).at(j) > 0) {
                        
                        totalProdutos.at(j)++;
                        
                    }
                    
                    
                }
                
            }
            
        }
        

        for (size_t i = 1; i < totalProdutos.size(); i++) {
            
            if (totalProdutos.at(i) > totalProdutos.at(idProdutoMaisMais)) {
                
                idProdutoMaisMais = (int)i;
                
            }
            
        }
        
    }
    
    return this->produtos.at(idProdutoMaisMais);
 
}

vector<string> VendeMaisMais::fazerPublicidade(vector<unsigned int> vetorIdClientes) {
    
    this->preencherMatrizes();
    vector<string> resultado;
    vector<unsigned int> idsClientesAUsar;
    
    //preencher o vetor de clientes a usar para fazer publicidade, se entrar vazio nesta função faz-se para todos, se entrar com alguns ids, faz-se so para esses
    
    if (vetorIdClientes.size() > 0) {
        
        for (size_t j = 0; j < vetorIdClientes.size(); j++) {
            
            for (constIntClient iteradorClientes = this->clientes.begin(); iteradorClientes != this->clientes.end(); iteradorClientes++) {
                
                if (iteradorClientes->first == vetorIdClientes.at(j)) {
                    
                    idsClientesAUsar.push_back(iteradorClientes->first);
                }
                
            }
            
        }
    }
    
    else {
            
        for (constIntClient iteradorClientes = this->clientes.begin(); iteradorClientes != this->clientes.end(); iteradorClientes++) {
            
            idsClientesAUsar.push_back(iteradorClientes->first);
        }
        
    }
    
    for (size_t i = 0; i < idsClientesAUsar.size(); i++) {
        
            Produto produtoAtual;
            unsigned int caso = this->obterProdutoRecomendado(produtoAtual, idsClientesAUsar.at(i));
            string mensagem;
            
            switch (caso) {
                case 0:
                    mensagem = "Caro(a) " + this->clientes.at(idsClientesAUsar.at(i)).getNome() + ", ainda nao efectuou nenhuma compra no nosso supermercado, considere comprar o nosso produto mais popular: " + produtoAtual.getNome();
                    
                    break;
                    
                case 1:
                    mensagem = "Caro(a) " + this->clientes.at(idsClientesAUsar.at(i)).getNome()  + ", sugerimos que considere a possibilidade de comprar " + produtoAtual.getNome();
                    
                    break;
                    
                case 2:
                    mensagem = "Caro(a) " + this->clientes.at(idsClientesAUsar.at(i)).getNome()  + ", sugerimos que considere a possibilidade de comprar " + produtoAtual.getNome();
                    
                    break;
                    
                case 3:
                    mensagem = "Caro(a) " + this->clientes.at(idsClientesAUsar.at(i)).getNome() + ", verificamos que é o cliente com mais produtos comprados. Considere comprar novamente o nosso produto mais popular: " + produtoAtual.getNome();
                    break;
                    
                case 4:
                    mensagem = "Caro(a) " + this->clientes.at(idsClientesAUsar.at(i)).getNome() + ", PARABENS, comprou todos os produtos. Considere comprar novamente o produto mais popular: " + produtoAtual.getNome() + " com 15 % de desconto.";
                    break;
            }
                        
            resultado.push_back(mensagem);
        
        }

    return resultado;
    
}

void VendeMaisMais::mostrarMatrizes() const {
    
    
    cout << endl;
    
    for (size_t h = 0; h < this->matrizes.size(); h++) {
        
        cout  << "c" << " " ;
        
        for (constIntProduto p = this->produtos.begin(); p != this->produtos.end(); p++) {
            
            cout << setw(2) << right << p->first << " ";
            
        }
        
        cout  << "coinc" << " " ;
        
        cout << endl;
        
        for (size_t i = 0; i < this->matrizes.at(h).size(); i++) {
            
            for (size_t j = 0; j < this->matrizes.at(h).at(i).size(); j++) {
                
                cout << setw(2) << left << this->matrizes.at(h).at(i).at(j) << " ";
                
            }
            
            cout << endl;
        }
        
        cout << endl << endl;
        
    }
    
}

vector<unsigned int> VendeMaisMais::calcularBottomN(unsigned int bottomN) {
    
    this->preencherMatrizes();
    if (bottomN > this->matrizes.at(0).size()) {
        
        bottomN = (unsigned int)this->matrizes.at(0).size();
        
    }
    
    vector<unsigned int> resultado(bottomN,0); //vetor resultado
    multimap <unsigned int, unsigned int> mapaClientesNumeroTransacoes;
    
    vector<int> comprasCadaCliente(this->matrizes.at(0).size()+1, 0); //vetor com tamanho = numero de clientes em que cada elemento é o numero de compras de cada cliente
    
    for (size_t i = 0; i < matrizes.at(0).size(); i++) {   //iterar nas linhas da matriz (escolhi a 0 porque so vou usar as primeiras colunas-n)
        
        for (size_t j = 1; j < matrizes.at(0).at(i).size()-1; j++) { //iterar nas colunas
            
            if (matrizes.at(0).at(i).at(j) > 0) {
                
                comprasCadaCliente.at(i)++;
                
            }
            
        }
        
        pair<unsigned int, unsigned int> parTransacoesCliente = make_pair(comprasCadaCliente.at(i), matrizes.at(0).at(i).at(0));
        
        mapaClientesNumeroTransacoes.insert(parTransacoesCliente);
        
    }
    
    
    multimap<unsigned int, unsigned int>::const_iterator iteradorMapa = mapaClientesNumeroTransacoes.begin();
    
    for (int i = 0; i < resultado.size(); i++) {
        
        resultado.at(i) = iteradorMapa->second;
        iteradorMapa++;
        
    }
    
    return resultado;
    
}

void VendeMaisMais::preencherMatrizes() {
    
    for (constIntClient iteradorCliente = this->clientes.begin(); iteradorCliente != this->clientes.end(); iteradorCliente++) {
        
        Produto produtoAtual;
        obterProdutoRecomendado(produtoAtual, iteradorCliente->first);
    }

}

// ================ MOSTRAR RECOMENDAÇOES =======================

void VendeMaisMais::listarRecomendacoes(vector<unsigned int> vetorIdClientes) {

    preencherMatrizes();
    
    vector<string> vetorPublicidade = fazerPublicidade(vetorIdClientes);
    

	if (vetorIdClientes.size() == 0) {
		Table tabelaMensagens({ "ID", "Nome", "Mensagem" });

		constIntClient iteradorMapaIds = clientes.begin();

		tabelaMensagens.addNewLine({ to_string(clientes.begin()->second.getId()), clientes.begin()->second.getNome(), vetorPublicidade.at(0) });
		for (size_t i = 1; i < vetorPublicidade.size(); i++) {

			iteradorMapaIds++;
			tabelaMensagens.addDataInSameLine({ to_string(iteradorMapaIds->second.getId()), iteradorMapaIds->second.getNome(), vetorPublicidade.at(i) });

		}
		cout << tabelaMensagens;
	}
	else if(vetorIdClientes.size() == 1) {

		stringstream ss;
		ss << this->clientes.at(vetorIdClientes.at(0)).getId();
		string str = ss.str();

		Table mostrarCliente({ "Id de Cliente: " , str });  // Mostra o id

		ss.str("");
		ss << this->clientes.at(vetorIdClientes.at(0)).getNome();
		str = ss.str();

		mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

		cout << mostrarCliente;


		Table tabelaMensagens({ vetorPublicidade.at(0) });

		for (size_t i = 1; i < vetorPublicidade.size(); i++) {

			tabelaMensagens.addDataInSameLine({ vetorPublicidade.at(i) });

		}
		cout << tabelaMensagens;
	}

	else {
		Table tabelaMensagens({ "ID", "Nome", "Mensagem" });

		tabelaMensagens.addNewLine({ to_string(vetorIdClientes.at(0)), clientes.at(vetorIdClientes.at(0)).getNome(), vetorPublicidade.at(0) });
		for (size_t i = 1; i < vetorPublicidade.size(); i++) {

			tabelaMensagens.addDataInSameLine({ to_string(vetorIdClientes.at(i)), clientes.at(vetorIdClientes.at(i)).getNome(), vetorPublicidade.at(i) });

		}
		cout << tabelaMensagens;
	}
}

bool VendeMaisMais::mostraMensagemRecomendacaoCliente(string nome) {

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

	cout << mostrarCliente;

	listarRecomendacoes({ this->clienteIdx.at(nome).getId() });

	return true;

}

bool VendeMaisMais::mostraMensagemRecomendacaoCliente(unsigned int clientId) {

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
	
	listarRecomendacoes({ clientId });

	return true;
}
