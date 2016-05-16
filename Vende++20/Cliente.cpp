#include "Cliente.h"


unsigned int Cliente::numClientes;

Cliente::Cliente(ifstream &in){
    
    string dataString;
    in >> this->id;
    in.ignore();
    getline(in, this->nome);
    getline(in, dataString);
    in >> this->volCompras;
    in.ignore();
    this->active = true;
    Data dataCartao(dataString);
    this->cartaoCliente = dataCartao;
    this->numClientes++;
}

Cliente::Cliente(string nome) {
    
    this->id = ++numClientes;
    this->nome = nome;
    this->volCompras = 0.0;
    this->cartaoCliente = Data(true);
    this->active = true;
    
    
}


string Cliente::getNome() const{
    
  return nome;

}

unsigned int Cliente::getId() const{
    
  return id;

}

float Cliente::getVolCompras() const{
    
  return volCompras;

}

Data Cliente::getCartaoCliente() const {
    
    return this->cartaoCliente;
}

void Cliente::setStatus(bool status) {
    
    this->active = status;
    
}

bool Cliente::getStatus() const {
    
    return this->active;
    
}

void Cliente::save(ofstream &out) const{

    out << *this;
    

}

ostream& operator<<(ostream& out, const Cliente &cliente){
  
    out << cliente.getId() << endl;
    out << cliente.getNome() << endl;
    out << cliente.getCartaoCliente() << endl;
    out << cliente.getVolCompras() << endl;

    return out;
}


bool operator<(const Cliente &cliente1, const Cliente &cliente2){
  
    if (cliente1.getVolCompras() < cliente2.getVolCompras()) {
        
        return true;
        
    }
    
    else {
        
        return true;
    }
    
}

unsigned int Cliente::getNumClientes() {
    
    return numClientes;
    
}

void Cliente::setNumClientes(unsigned int primeiro) {
    
    //numClientes = primeiro;
    
}

vector<string> Cliente::toTable(){
    vector<string> output;
    
    stringstream ss;
    ss << id;
    string str = ss.str();
    
    output.push_back(str);
    
    output.push_back(nome);
    
    ss.str("");
    ss << cartaoCliente;
    str = ss.str();
    output.push_back(str);
    
    ss.str("");
    ss << volCompras;
    str = ss.str();
    output.push_back(str);
    
    return output;
}
