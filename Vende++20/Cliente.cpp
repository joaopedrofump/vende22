#include "Cliente.h"
#include "utils.h"


unsigned int Cliente::numClientes;

Cliente::Cliente(ifstream &in){
    
    string stringTemporaria;
    getline(in, stringTemporaria);
    
    this->id = atoi(stringTemporaria.substr(0, stringTemporaria.find(';', 0)).c_str());
    
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    
    this->nome = stringTemporaria.substr(0, stringTemporaria.find(';', 0));
    trimString(this->nome);
    
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    
    string dataString = stringTemporaria.substr(0, stringTemporaria.find(';', 0));
    trimString(dataString);
    
    Data dataCartao(dataString);
    this->cartaoCliente = dataCartao;
    
    stringTemporaria = stringTemporaria.substr(stringTemporaria.find(';', 0) + 1);
    
    this->volCompras = atof(stringTemporaria.c_str());
    this->active = true;
    
    numClientes++;
    
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
  
    out << cliente.getId() << " ; ";
    out << cliente.getNome() << " ; ";
    out << cliente.getCartaoCliente() << " ; ";
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
