#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <iomanip>

#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"
#include "defs.h"
#include "Table.h"


using namespace std;

class VendeMaisMais {

private:
<<<<<<< HEAD
    string loja; // nome da loja
    
    // nome dos ficheiros de clientes, produtos e transacoes
    string fichClientes, fichProdutos, fichTransacoes;
    bool transacoesAlterdas; // flag que fica a true se for preciso guardar no final as transacoes
    bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clienets
    bool produtosAlterados;
    unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identiicador
    unsigned int maxProdutcId;
    map<unsigned int, Cliente> clientes;// mapa que guarda a informacao dos clientes existentes
    map<string, Cliente> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
    
    //vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
    vector<Transacao> transacoes; // vetor que guarda a informacao das ttransacoes efetuadas
    
    map<unsigned int, Produto> produtos;
    map<string, Produto> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
    multimap<unsigned int, unsigned int> transacaoIdx; // multima para "traduzir" o identificador do cliente nos indices das suas
    // transacoes no vetor de
    // transacoes
    unsigned int obterProdutoRecomendado(Produto &produtoRecomendado, unsigned int idCliente);
    //casos de retorno:
    //0: cliente não comprou nada, recomenda-se o produto mais comprado na loja
    //1: cliente com produtos comprados mas sem nenhuma coincidencia com outros clientes
    vector <vector <vector <unsigned int>>> matrizes;
    
    
    
public:
    VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
    void listarClientesOrdemAlfa() const;
    void listarProdutos() const;
=======
	string loja; // nome da loja

				 // nome dos ficheiros de clientes, produtos e transacoes
	string fichClientes, fichProdutos, fichTransacoes;
	bool transacoesAlterdas; // flag que fica a true se for preciso guardar no final as transacoes
	bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clienets
	bool produtosAlterados;
	unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identiicador
	unsigned int maxProdutcId;
	map<unsigned int, Cliente> clientes;// mapa que guarda a informacao dos clientes existentes
	map<string, Cliente> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes

									  //vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
	vector<Transacao> transacoes; // vetor que guarda a informacao das ttransacoes efetuadas

	map<unsigned int, Produto> produtos;
	map<string, Produto> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
	multimap<int, int> transacaoIdx; // multima para "traduzir" o identificador do cliente nos indices das suas
									 // transacoes no vetor de
									 // transacoes

public:
	VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
	void listarClientesOrdemAlfa(bool onlyActives = false) const;
	void listarProdutos(bool onlyActives = false) const;
>>>>>>> LEO

	bool mostraInformacaoCliente(string nome);
	bool mostraInformacaoCliente(unsigned int clientId);
	bool eliminarCliente(string nome);
	bool eliminarCliente(unsigned int clientId);

<<<<<<< HEAD
    void reactivarCliente(string nome);
    void reactivarCliente(unsigned int clientId);
    bool eliminarProduto(string nome);
    bool eliminarProduto(unsigned int produtoId);
    void reactivarProduto(string nome);
    void reactivarProduto(unsigned int produtoId);
    void adicionarCliente(string nome);
    void adicionarProduto(string nomeProduto, float custoProduto);
    
    void listarTransacoes() const;
    void listarTransacoes(unsigned int clienteId);
    void listarTransacoes(string data1, string data2="", bool dataUnica=true);
    void listarTransacoesProduto(unsigned int idProduto);

    void registarTransacao(unsigned int idCliente, vector <unsigned int> produtos);

    unsigned int getMaxProductId() const;
=======
	void reactivarCliente(string nome);
	void reactivarCliente(unsigned int clientId);

	bool encontrarCliente(unsigned int clienteId);
	bool encontrarCliente(string nome);

	bool eliminarProduto(string nome);
	bool eliminarProduto(unsigned int produtoId);
	void reactivarProduto(string nome);
	void reactivarProduto(unsigned int produtoId);
	void adicionarCliente(string nome);
	void adicionarProduto(string nomeProduto, float custoProduto);

	bool encontrarProduto(unsigned int clienteId);
	bool encontrarProduto(string nome);

	void registarTransacao(unsigned int idCliente, vector <unsigned int> produtos);
	void listarTransacoes() const;
	void listarTransacoes(unsigned int clienteId);
	void listarTransacoes(string data1, string data2 = "", bool dataUnica = true);
	void listarTransacoesProduto(unsigned int idProduto);

	unsigned int getMaxProductId() const;
>>>>>>> LEO
	map<unsigned int, Cliente> getMapIDtoCliente() const;
	map<string, Cliente> VendeMaisMais::getMapNametoCliente() const;

<<<<<<< HEAD
    void saveChanges() const;
    unsigned int getMaxClienteId() const;
    vector<string> fazerPublicidade(vector<unsigned int> vetorIdClientes);
    friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
    
    void mostrarMatrizes() const;
    Produto obterProdutoMaisVendido(unsigned int clienteId, unsigned int numCoincidencias, bool numCoincidenciasReal) const; //se clienteid for diferente de 0 calcula o produto mais vendido excluindo os que comprou esse cliente
    vector<unsigned int> calcularBottomN(unsigned int bottomN = 10) const;
   
};
=======
	void saveChanges() const;
	unsigned int getMaxClienteId() const;
	friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
};
>>>>>>> LEO
