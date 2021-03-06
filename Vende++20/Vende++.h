/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <iomanip>

#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"
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
    multimap<unsigned int, unsigned int> transacaoIdx; // multima para "traduzir" o identificador do cliente nos indices das suas
    // transacoes no vetor de
    // transacoes
    unsigned int obterProdutoRecomendado(Produto &produtoRecomendado, unsigned int idCliente);
    //casos de retorno:
    //0: cliente não comprou nada, recomenda-se o produto mais comprado na loja
    //1: cliente com produtos comprados mas sem nenhuma coincidencia com outros clientes, recomenda-se o produto mais comprado que ele não tenha comprado
    //2: há coincidencias -> dois subcasos:
                            //a) só há um cliente com o numero maximo de coincidencias com ele: sugere-se o produto mais comprado por esse cliente
                            //b) há mais do que um, sugere-se o produto que mais pessoas compraram
    //3: nenhum dos clientes com coincidencias compraram produtos que o cliente alvo ainda não tenha comprado: sugere-se o produto mais comprado da loja embora o cliente alvo já o tenha comprado
    //4: cliente alvo comprou todos os produtos: sugere-se o produto mais comprado da loja embora o cliente alvo já o tenha comprado
    vector <vector <vector <unsigned int>>> matrizes;
    void preencherMatrizes();
    
public:
    VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
    void listarClientesOrdemAlfa(bool onlyActives = false) const;
    void listarProdutos(bool onlyActives = false) const;

	bool mostraInformacaoCliente(string nome);
	bool mostraInformacaoCliente(unsigned int clientId);
	bool eliminarCliente(string nome);
	bool eliminarCliente(unsigned int clientId);


	bool reactivarCliente(string nome);
	bool reactivarCliente(unsigned int clientId);

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
	map<string, Cliente> getMapNametoCliente() const;
	map<unsigned int, Produto> getMapIDtoProduct() const;

    void saveChanges() const;
    unsigned int getMaxClienteId() const;
    vector<string> fazerPublicidade(vector<unsigned int> vetorIdClientes = vector<unsigned int>(0,0));

    friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
    
    void mostrarMatrizes() const;
    Produto obterProdutoMaisVendido(unsigned int clienteId, unsigned int numCoincidencias, bool numCoincidenciasReal) const; //se clienteid for diferente de 0 calcula o produto mais vendido excluindo os que comprou esse cliente
    
    vector<unsigned int> calcularBottomN(unsigned int bottomN = 10);

	void listarRecomendacoes(vector< unsigned int> vetorIdClientes = {});
	bool mostraMensagemRecomendacaoCliente(string nome);
	bool mostraMensagemRecomendacaoCliente(unsigned int clientId);
    
    vector <Transacao> getTransacoes() const;
    map <unsigned int, Cliente> getClientes() const;
    map <unsigned int, Produto> getProdutos() const;
    bool existemProdutosActivos() const;
    bool existemClientesActivos() const;
    bool existemProdutosInactivos() const;
    bool existemClientesInactivos() const;
    void listarClientesOrdemAlfaInactivos() const;
    
       
};
