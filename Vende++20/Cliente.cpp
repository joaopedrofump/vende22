#include "Cliente.h"
#include "utils.h"


unsigned int Cliente::numClientes;

//============== CONSTRUTORES ============

Cliente::Cliente(ifstream &in){
    
    string stringTemporaria;
    getline(in, stringTemporaria);
    
    if (stringTemporaria.size() == 0) {
        
        this->id = 0;
        return;
        
    }
    
    this->id = atoi(stringTemporaria.substr(0, stringTemporaria.find(';', 0)).c_str());
    
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    
    this->nome = stringTemporaria.substr(0, stringTemporaria.find(';', 0));
    
    validateName(this->nome);
    
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    
    string dataString = stringTemporaria.substr(0, stringTemporaria.find(';', 0));
    trimString(dataString);
    
    Data dataCartao(dataString);
    this->cartaoCliente = dataCartao;
    
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    
    this->volCompras = atof(stringTemporaria.c_str());
    this->active = true;
    
    if (numClientes < this->id) {
        
        numClientes = this->id;
    }
}

Cliente::Cliente(string nome) {

	this->id = ++numClientes;
	this->nome = nome;
	this->volCompras = 0.0;
	this->cartaoCliente = Data(true);
	this->active = true;


}

// ============= GETTERS =================

string Cliente::getNome() const {

	return nome;

}

unsigned int Cliente::getId() const {

	return id;

}

float Cliente::getVolCompras() const {

	return volCompras;

}

Data Cliente::getCartaoCliente() const {

	return this->cartaoCliente;
}

bool Cliente::getStatus() const {

	return this->active;

}

unsigned int Cliente::getNumClientes() {

	return numClientes;

}

// ============= SETTERS =================

void Cliente::setStatus(bool status) {

	this->active = status;

}

void Cliente::setNumClientes(unsigned int primeiro) {

	numClientes = primeiro;

}


void Cliente::save(ofstream &out) const {

	out << *this;


}

ostream& operator<<(ostream& out, const Cliente &cliente) {

	out << cliente.getId() << " ; ";
	out << cliente.getNome() << " ; ";
	out << cliente.getCartaoCliente() << " ; ";
	out << cliente.getVolCompras() << endl;

	return out;
}

bool operator<(const Cliente &cliente1, const Cliente &cliente2) {

	if (cliente1.getVolCompras() < cliente2.getVolCompras()) {

		return true;

	}

	else {

		return true;
	}

}



vector<string> Cliente::toTable() const {
	vector<string> output;

	stringstream ss;
	ss << id;
	string str = ss.str();

	output.push_back(str);

	output.push_back(nome);

	output.push_back(cartaoCliente.mostrarData());

	ss.str("");
	ss << volCompras;
	str = ss.str();
	output.push_back(str);

	if (this->active)
		output.push_back("ATIVO");
	else
		output.push_back("INATIVO");

	return output;
}

void Cliente::acrescentarCompras(float total) {

	this->volCompras += total;

}
