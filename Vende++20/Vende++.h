#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

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

	bool mostraInformacaoCliente(string nome);
	bool mostraInformacaoCliente(unsigned int clientId);
	bool eliminarCliente(string nome);
	bool eliminarCliente(unsigned int clientId);

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
	map<unsigned int, Cliente> getMapIDtoCliente() const;
	map<string, Cliente> VendeMaisMais::getMapNametoCliente() const;

	void saveChanges() const;
	unsigned int getMaxClienteId() const;
	friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
};