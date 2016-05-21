#include <iostream>
#include <string>
#include <vector>
#include "Cliente.h"

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"
#include "data.h"


int main(){
    string loja, fichClients, fichProdutos, fichTransacoes;
    //
    // pede a informacoo sobre o nome da loja e os 3 ficheiros com
    // informacoo de clientes, produtos e transacoes
    if(!infoInicial(loja, fichClients, fichProdutos, fichTransacoes)) {
        return(1);
    }
    //
    // cria uma loja
    VendeMaisMais supermercado(loja, fichClients, fichProdutos, fichTransacoes);
    

    cout << "Informacao da loja '" << loja << " do supermercado Vende++:" << endl;
<<<<<<< HEAD
    cout << supermercado << endl;  // mostra estatisticas da loja
    opcoesIniciais(supermercado);

  
=======
    cout << supermercado << endl;  // mostra estatisticas da loja
    //opcoesIniciais(supermercado);

    vector<unsigned int> vetorTeste;
    vetorTeste = leVectorInteiros("Introduza os ids");
    
    for (size_t i = 0; i < vetorTeste.size(); i++) {
        
        cout << vetorTeste.at(i) << endl;
        
    }
    
    
    
    
    supermercado.saveChanges();
    
    
<<<<<<< HEAD
=======
    cout << "Informacao da loja " << loja << " do supermercado Vende++:" << endl;
    cout << supermercado << endl;  // mostra estatisticas da loja
    opcoesIniciais(supermercado);
>>>>>>> LEO
>>>>>>> baaf46f1abea6b3e8fa5a002698c729e585053de
    return 0;
}