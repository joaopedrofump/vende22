/*

T7G02
Jo�o Pinheiro
Leonardo Teixeira

*/


#include "Transacao.h"
#include "utils.h"
#include "Data.h"



unsigned int Transacao::getIdCliente() const {
	return idCliente;
}

Transacao::Transacao(ifstream &in) { // le uma transacao na forma de  idcliente ; data ; lista produtos
	string linha;
	string stringTemporaria;
	getline(in, linha);

	if (linha.size() == 0) {

		this->idCliente = 0;
		return;

	}

	this->idCliente = atoi(linha.substr(0, linha.find(';', 0)).c_str()); //salva o id do Cliente
	linha = linha.substr(linha.find(';', 0) + 1);	//atualiza a Linha

	stringTemporaria = linha.substr(0, linha.find(';', 0));
	trimString(stringTemporaria);

	Data dataTemporaria(stringTemporaria);
	this->data = dataTemporaria;  //guarda a data

	linha = linha.substr(linha.find(';', 0) + 1);  //atualiza a Linha

	vector<string> produtosComprados;
	while (linha.find(',') < (int)linha.length()) { //correr o resto da string

		stringTemporaria = linha.substr(0, linha.find(',', 0));
		validateProduct(stringTemporaria);
		produtosComprados.push_back(stringTemporaria);
		linha = linha.substr(linha.find(',') + 1);
	}
	validateProduct(linha);
	produtosComprados.push_back(linha);
	this->produtos = produtosComprados;
	//this->calculateTotal();

}

Transacao::Transacao(Cliente clienteAInserir, vector <Produto> produtosTransacao) {

	this->clienteTransacao = clienteAInserir;
	this->produtosProduto = produtosTransacao;
	this->data = Data(true);
	this->calculateTotal();

}

void Transacao::save(ofstream & out) const { // transacao guardada como na forma de  idcliente ; data ; lista produtos

	out << *this;

}

ostream& operator<<(ostream& out, const Transacao &transacao) {

	out << transacao.clienteTransacao.getId() << " ; " << transacao.data << " ; ";


	for (size_t i = 0; i < transacao.produtosProduto.size(); i++) {

		out << transacao.produtosProduto.at(i).getNome();
		if (i < transacao.produtosProduto.size() - 1) {
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

Cliente Transacao::getCliente() const {

	return this->clienteTransacao;
}

void Transacao::setCliente(Cliente clienteAInserir) {

	this->clienteTransacao = clienteAInserir;
}

float Transacao::getTotal() const {

	return this->total;

}

Data Transacao::getData() const {
	return this->data;
}

void Transacao::calculateTotal() {

	this->total = 0.0;

	for (size_t i = 0; i < this->produtosProduto.size(); i++) {

		this->total += produtosProduto.at(i).getCusto();

	}

}

vector<string> Transacao::toTable() const {

	vector<string> output;

	stringstream ss;

	ss.str("");
	ss << this->getCliente().getId();
	string str = ss.str();

	output.push_back(str);   //Incluir id do Cliente

	output.push_back(this->getCliente().getNome()); //Incluir nome do Cliente

	output.push_back(this->data.mostrarData());  //Incluir a data da transacao

	ss.str("");
	ss << this->total;
	str = ss.str();

	output.push_back(str);  //Incluir o valor total da transacao

	ss.str("");

	for (size_t i = 0; i < this->produtosProduto.size(); i++) {

		ss << produtosProduto.at(i).getNome();
		if (i != this->produtosProduto.size() - 1) {
			ss << ", ";
		}
	}
	str = ss.str();

	output.push_back(str);

	return output;

}
