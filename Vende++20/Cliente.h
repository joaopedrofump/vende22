/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Data.h"

using namespace std;

class Cliente {

private:

	unsigned int id;
	string nome;
	Data cartaoCliente;
	float volCompras;
	bool active;
	static unsigned int numClientes;

public:

	Cliente(ifstream & in);
	Cliente(string nome);
	Cliente() {};
	string getNome() const;
	unsigned int getId() const;
	float getVolCompras() const;
	Data getCartaoCliente() const;
	void setStatus(bool status);
	static unsigned int getNumClientes();
	static void setNumClientes(unsigned int primeiro);
	bool getStatus() const;
	void save(ofstream & out) const;
	friend ostream& operator<<(ostream& out, const Cliente & cli);  // mostra informacao do cliente no ecra

	friend bool operator<(const Cliente &cli1, const Cliente &cli2); // compara 2 clientes (1 cleinte e menor que outro se o seu nome for "alfabeticamente" inferior)

	vector<string> toTable() const;
	void acrescentarCompras(float total);

};