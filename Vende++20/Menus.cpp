/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#include "Menus.h"

using namespace std;

const string PATH = "/Users/joaofurriel/Documents/Estudo/MIEIC/Ano1/Programação/ProjectoVende++/Vende++20/Vende++20/";

bool infoInicial(string &loja, string &fichClientes, string &fichProdutos, string &fichTransacoes) {
    ifstream inStreamClientes, inStreamProdutos, inStreamTransacoes;
    bool clientesExiste, produtosExiste, transacoesExiste;
    cout << "Introduza o nome da loja" << endl;
     getline(cin, loja);
     cout << "Introduza o nome do ficheiro de clientes" << endl;
     getline(cin, fichClientes);
     cout << "Introduza o nome do ficheiro de produtos" << endl;
     getline(cin, fichProdutos);
     cout << "Introduza o nome do ficheiro de transacoes" << endl;
     getline(cin, fichTransacoes);
    
    /*loja = "Micro-Preço";
    fichClientes = "clientes.txt";
    fichProdutos = "produtos.txt";
    fichTransacoes = "transacoes.txt";*/
    
#ifdef __llvm__
    
    string fichclientes2 = "";
    string fichProdutos2 = "";
    string fichTransacoes2 = "";
    fichclientes2.append(PATH).append(fichClientes);
    fichProdutos2.append(PATH).append(fichProdutos);
    fichTransacoes2.append(PATH).append(fichTransacoes);
    fichClientes = fichclientes2;
    fichProdutos = fichProdutos2;
    fichTransacoes = fichTransacoes2;
#endif
    
    inStreamClientes.open(fichClientes.c_str());
    clientesExiste = inStreamClientes.good();
    inStreamProdutos.open(fichProdutos.c_str());
    produtosExiste = inStreamProdutos.good();
    inStreamTransacoes.open(fichTransacoes.c_str());
    transacoesExiste = inStreamTransacoes.good();
    inStreamClientes.close();
    inStreamProdutos.close();
    inStreamTransacoes.close();
    return clientesExiste && produtosExiste && transacoesExiste;
}

/******************************************
* Menu Inicial
******************************************/

void opcoesIniciais(VendeMaisMais &supermercado) {
    unsigned int opcao;
	
    while ((opcao = menuInicial()))
        switch (opcao) {
            case 1: opcoesGestaoClientes(supermercado);
                break;
            case 2: opcoesGestaoProdutos(supermercado);
                break;
            case 3: opcoesGestaoTransacoes(supermercado);
                break;
            case 4: opcoesRecomendacao(supermercado);
				break;
			case 5:
				break;
        }
    supermercado.saveChanges();
}

unsigned short int menuInicial() {
    unsigned short int opcao = 0;
    bool control = false;
	Table acabarPrograma({ "Tem a certeza que pretende encerrar o programa?" });
    while (!control) {
        mostrarMenuInicial(0);
        control = leUnsignedShortInt(opcao, 0, 4);
    }

	if (opcao == 0 && !confirmar(acabarPrograma.getTableVector(), acabarPrograma.getBlocks(), acabarPrograma.getColumsWidth(), acabarPrograma.getIndentacao())) {
		opcao = 5;
	}
    return opcao;
}

void mostrarMenuInicial(unsigned short int opcaoEscolhida) {
    clearScreen();
    Table menu({ "Menu Inicial" });
    vector<string> menuCabecalho;
    switch (opcaoEscolhida) {
        case 0:
            menuCabecalho = { "1 - Clientes", "2 - Produtos", "3 - Transacoes", "4 - Recomendacoes", "0 - Sair" };
            break;
        case 1:
            menuCabecalho = { "1 - Clientes" + string(14, ' '), "2 - Produtos", "3 - Transacoes", "4 - Recomendacoes", "0 - Sair" };
            break;
        case 2:
            menuCabecalho = { "1 - Clientes", "2 - Produtos" + string(14, ' '), "3 - Transacoes", "4 - Recomendacoes", "0 - Sair" };
            break;
        case 3:
            menuCabecalho = { "1 - Clientes", "2 - Produtos", "3 - Transacoes" + string(21, ' '), "4 - Recomendacoes", "0 - Sair" };
            break;
        default:
            menuCabecalho = { "1 - Clientes", "2 - Produtos", "3 - Transacoes", "4 - Recomendacoes" + string(30, ' '), "0 - Sair" };
            break;
    }
    Table menuOpcoes(menuCabecalho);
    cout << menu << endl;
    cout << menuOpcoes;
}

/******************************************
 * Gestao de Clientes
 ******************************************/

unsigned short int menuGestaoClientes() {
    unsigned short int opcao;
    bool control = false;
    do {
        mostrarMenuInicial(1);
        Table menuClientes({ "1 - Listar clientes" });
        menuClientes.addNewLine({ "2 - Ver informacao cliente" });
        menuClientes.addNewLine({ "3 - Adicionar cliente" });
		menuClientes.addNewLine({ "4 - Reativar cliente" });
        menuClientes.addNewLine({ "5 - Remover cliente" });
        menuClientes.addNewLine({ "0 - Voltar ao menu inicial" });
        cout << menuClientes;
        control = leUnsignedShortInt(opcao, 0, 5);
    } while (!control);
    return opcao;
}

void opcoesGestaoClientes(VendeMaisMais &supermercado) {
    unsigned int opcao;
    
    while ((opcao = menuGestaoClientes())) {
		string input;
		unsigned int idCliente;
        bool control = false;
		bool sairDoSwitch = false;

		stringstream ss;
		string str;
		Table mostrarCliente({ "Informacao" , "Dados" });
		Table confirmarAdicionar({ "Tem a certeza que pretende adicionar o cliente?" });
		Table confirmarEliminar({ "Tem a certeza que pretende eliminar o cliente?" });
		Table confirmarReativar({ "Tem a certeza que pretende eliminar o cliente?" });
		Data hoje(true);

        switch (opcao) {
            case 1:           //=========== MOSTRAR CLIENTES ==============
                clearScreen();
                mostrarMenuInicial(0);
                supermercado.listarClientesOrdemAlfa();
                ignoreLine(false);
                break;
            case 2:          //============ MOSTRAR UM CLIENTE ============
                do {
                    clearScreen();
                    mostrarMenuInicial(0);
					supermercado.listarClientesOrdemAlfa();
                    Table introIdNome({ "Introduza o ID ou o NOME do cliente." });
                    cout << introIdNome << endl;
                    getline(cin, input);
                    if (stringVazia(input)) {
                        break;
                    }
                    trimString(input);
                    if (isdigit(input.at(0))) {
                        idCliente = stoi(input);
                        clearScreen();
                        mostrarMenuInicial(0);
                        control = supermercado.mostraInformacaoCliente(idCliente);
                        ignoreLine(false);
                    }
                    else {
                        clearScreen();
                        mostrarMenuInicial(0);
                        control = supermercado.mostraInformacaoCliente(input);
                        ignoreLine(false);
                    }
                } while (!control);
                break;
            case 3:            //=========== ADICIONAR CLIENTE ================
                do {
                    clearScreen();
                    mostrarMenuInicial(0);
                    Table introIdNome({ "Introduza NOME do cliente." });
                    cout << introIdNome << endl;
                    getline(cin, input);
                    if (stringVazia(input)) {
						sairDoSwitch = true;
                        break;
                    }
                    trimString(input);
                    control = validateName(input);
                    //ignoreLine(false, "Cliente adicionado com sucesso");
                } while (!control);
				if (sairDoSwitch) break;  //Teclar enter apenas, cancela a operacao
				

				//Mostrar resumo da operacao
				
				ss << Cliente::getNumClientes() + 1;
				str = ss.str();

				mostrarCliente.addNewLine({ "Id de Cliente: " , str });  // Mostra o id

				ss.str("");
				ss << input;
				str = ss.str();

				mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

				ss.str("");
				ss << hoje.mostrarData();
				str = ss.str();


				mostrarCliente.addNewLine({ "Cartao de Cliente: " , str });

				clearScreen();
				mostrarMenuInicial(0);

				
				cout << confirmarAdicionar;

				if (!confirmar(mostrarCliente.getTableVector(), mostrarCliente.getBlocks(), mostrarCliente.getColumsWidth(), mostrarCliente.getIndentacao())) {
					break;
				}
				ignoreLine(false, "Cliente adicionado com sucesso");
                supermercado.adicionarCliente(input);
                supermercado.saveChanges();
                break;
            case 5:            //============  ELIMINAR CLIENTES ================
                do {
                    clearScreen();
                    mostrarMenuInicial(0);
					supermercado.listarClientesOrdemAlfa(true);
                    Table introIdNome({ "Introduza o ID ou o NOME do cliente a eliminar." });
                    cout << introIdNome << endl;
                    getline(cin, input);
                    if (stringVazia(input)) {
                        break;
                    }
                    trimString(input);
                    if (isdigit(input.at(0))) { // ELIMINAR PELO ID
                        idCliente = stoi(input);
                        control = supermercado.eliminarCliente(idCliente);

						//Mostrar resumo da operacao

						ss << idCliente;
						str = ss.str();

						mostrarCliente.addNewLine({ "Id de Cliente: " , str });  // Mostra o id

						ss.str("");
						ss << supermercado.getMapIDtoCliente().at(idCliente);
						str = ss.str();

						mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

						ss.str("");
						ss << hoje.mostrarData();
						str = ss.str();


						mostrarCliente.addNewLine({ "Cartao de Cliente: " , str });

						clearScreen();
						mostrarMenuInicial(0);

						
						cout << confirmarEliminar;

						if (!confirmar(mostrarCliente.getTableVector(), mostrarCliente.getBlocks(), mostrarCliente.getColumsWidth(), mostrarCliente.getIndentacao())) {
							break;
						}
						ignoreLine(false, "Cliente eliminado com sucesso");
                    }
                    else {   // ELIMINAR PELO NOME
                        control = supermercado.eliminarCliente(input);

						//Mostrar resumo da operacao

						ss << supermercado.getMapNametoCliente().at(input);
						str = ss.str();

						mostrarCliente.addNewLine({ "Id de Cliente: " , str });  // Mostra o id

						ss.str("");
						ss << input;
						str = ss.str();

						mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

						ss.str("");
						ss << hoje.mostrarData();
						str = ss.str();


						mostrarCliente.addNewLine({ "Cartao de Cliente: " , str });

						clearScreen();
						mostrarMenuInicial(0);


						cout << confirmarEliminar;

						if (!confirmar(mostrarCliente.getTableVector(), mostrarCliente.getBlocks(), mostrarCliente.getColumsWidth(), mostrarCliente.getIndentacao())) {
							break;
						}
						ignoreLine(false, "Cliente eliminado com sucesso");
                    }
                } while (!control);
                supermercado.saveChanges();
                break;
			case 4:  //================ REATIVAR CLIENTE ==================
				do {
					clearScreen();
					mostrarMenuInicial(0);
					supermercado.listarClientesOrdemAlfa();
					Table introIdNome({ "Introduza o ID ou o NOME do cliente." });
					cout << introIdNome << endl;
					getline(cin, input);
					if (stringVazia(input)) {
						break;
					}
					trimString(input);
					if (isdigit(input.at(0))) { //  REATIVAR PELO ID
						idCliente = stoi(input);
						clearScreen();
						mostrarMenuInicial(0);
						control = supermercado.reactivarCliente(idCliente);
						
						//Mostrar resumo da operacao

						ss << idCliente;
						str = ss.str();

						mostrarCliente.addNewLine({ "Id de Cliente: " , str });  // Mostra o id

						ss.str("");
						ss << supermercado.getMapIDtoCliente().at(idCliente);
						str = ss.str();

						mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

						ss.str("");
						ss << hoje.mostrarData();
						str = ss.str();


						mostrarCliente.addNewLine({ "Cartao de Cliente: " , str });

						clearScreen();
						mostrarMenuInicial(0);


						cout << confirmarReativar;

						if (!confirmar(mostrarCliente.getTableVector(), mostrarCliente.getBlocks(), mostrarCliente.getColumsWidth(), mostrarCliente.getIndentacao())) {
							break;
						}
						ignoreLine(false, "Cliente reativado com sucesso");
					}
					else {  //  REATIVAR PELO NOME
						clearScreen();
						mostrarMenuInicial(0);
						control = supermercado.reactivarCliente(input);
						
						//Mostrar resumo da operacao

						ss << supermercado.getMapNametoCliente().at(input);
						str = ss.str();

						mostrarCliente.addNewLine({ "Id de Cliente: " , str });  // Mostra o id

						ss.str("");
						ss << input;
						str = ss.str();

						mostrarCliente.addNewLine({ "Nome do Cliente: " , str }); // Mostra o Nome

						ss.str("");
						ss << hoje.mostrarData();
						str = ss.str();


						mostrarCliente.addNewLine({ "Cartao de Cliente: " , str });

						clearScreen();
						mostrarMenuInicial(0);


						cout << confirmarReativar;

						if (!confirmar(mostrarCliente.getTableVector(), mostrarCliente.getBlocks(), mostrarCliente.getColumsWidth(), mostrarCliente.getIndentacao())) {
							break;
						}
						ignoreLine(false, "Cliente reativado com sucesso");
					}
				} while (!control);
				break;
            case 0:
                break;
        }
    }
}

/******************************************
 * Gestao de Produtos
 ******************************************/

unsigned short int menuGestaoProdutos() {
    unsigned short int opcao;
    bool control = false;
    do {
        mostrarMenuInicial(2);
        Table menuProdutos({ "1 - Listar produtos" }, 17);
        menuProdutos.addNewLine({ "2 - Adicionar produto" });
        menuProdutos.addNewLine({ "3 - Reativar produto" });
		menuProdutos.addNewLine({ "4 - Remover produto" });
        menuProdutos.addNewLine({ "0 - Voltar ao menu inicial" });
        cout << menuProdutos;
        control = leUnsignedShortInt(opcao, 0, 4);
    } while (!control);
    return opcao;
}

void opcoesGestaoProdutos(VendeMaisMais &supermercado) {
    unsigned int opcao;
    while ((opcao = menuGestaoProdutos())) {
        string input;
        string nomeProduto;
        bool control = false;
        bool sairDoSwitch = false;
        pair<string, float> pairNomeCusto;
        vector<unsigned int> vectorInteiros;

		stringstream ss;
		string str;
		Table mostrarProduto({ "Informacao" , "Dados" });
		Table mostrarProdutos({ "Nome", "Custo" });

		Table confirmarAdicionar({ "Tem a certeza que pretende adicionar o produto?" });
		Table confirmarEliminar({ "Tem a certeza que pretende eliminar o(s) produto(s)?" });
		Table confirmarReativar({ "Tem a certeza que pretende reativar o(s) produto(s)?" });
        switch (opcao) {
            case 1:     // ============== MOSTRAR PRODUTOS ============
                clearScreen();
                mostrarMenuInicial(0);
                supermercado.listarProdutos();
                ignoreLine(false);
                break;
            case 2:     // ============== ADICIONAR PRODUTO ===========
                while (!control) {
                    clearScreen();
                    mostrarMenuInicial(0);
                    control = leStringFloat(pairNomeCusto, "Introduza o nome seguido do custo do produto. (Ex: produto 1.30)");
                    if (!control) {
                        cin.get();
                        continue;
                    }
                    if (pairNomeCusto.first == "" && pairNomeCusto.second == 0.0) {
                        sairDoSwitch = true;
                        break;
                    }
                }
                if (sairDoSwitch) break;  //Teclar enter apenas, cancela a operacao

				//================================================
				//Mostrar resumo da operacao
				//================================================
				ss << pairNomeCusto.first;
				str = ss.str();

				mostrarProduto.addNewLine({ "Nome do produto: " , str });  // Mostra o nome do produto

				ss.str("");
				ss << pairNomeCusto.second;
				str = ss.str();

				mostrarProduto.addNewLine({ "Custo do produto: " , str }); // Mostra o custo


				clearScreen();
				mostrarMenuInicial(0);


				cout << confirmarAdicionar;

				if (!confirmar(mostrarProduto.getTableVector(), mostrarProduto.getBlocks(), mostrarProduto.getColumsWidth(), mostrarProduto.getIndentacao())) {
					break;
				}
				ignoreLine(false, "Produto adicionado com sucesso");

                supermercado.adicionarProduto(pairNomeCusto.first, pairNomeCusto.second);
				supermercado.saveChanges();

                break;
            case 4:    // ================ ELIMINAR PRODUTO ===========
                while (!control) {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarProdutos(true);
                    control = leVectorInteiros(vectorInteiros, "Introduza os ID's dos produtos a eliminar.");
                    if (!control) {
                        cin.get();
                        continue;
                    }
                    if (vectorInteiros.size() == 0) {
                        sairDoSwitch = true;
                        break;
                    }
                }
                if (sairDoSwitch) break;  //Teclar enter apenas, cancela a operacao

                for (size_t i = 0; i < vectorInteiros.size(); i++) {

					//================================================
					//Mostrar resumo da operacao
					//================================================
					if (vectorInteiros.size() == 1) {
						ss.str("");
						ss << supermercado.getMapIDtoProduct().at(vectorInteiros.at(i)).getNome();
						str = ss.str();

						mostrarProduto.addNewLine({ "Nome do produto: " , str });  // Mostra o nome do produto

						ss.str("");
						ss << supermercado.getMapIDtoProduct().at(vectorInteiros.at(i)).getCusto();
						str = ss.str();

						mostrarProduto.addNewLine({ "Custo do produto: " , str }); // Mostra o custo

						clearScreen();
						mostrarMenuInicial(0);
				
						cout << confirmarEliminar;

					}
					else {

						mostrarProdutos.addNewLine({ supermercado.getMapIDtoProduct().at(vectorInteiros.at(i)).getNome() , to_string(vectorInteiros.at(i)) });  // Mostra o produto
						
						clearScreen();
						mostrarMenuInicial(0);

						cout << confirmarEliminar;

						
					}		
                }

				if (vectorInteiros.size() == 1) {
					if (!confirmar(mostrarProduto.getTableVector(), mostrarProduto.getBlocks(), mostrarProduto.getColumsWidth(), mostrarProduto.getIndentacao())) {
						break;
					}
				}
				else {
					if (!confirmar(mostrarProdutos.getTableVector(), mostrarProdutos.getBlocks(), mostrarProdutos.getColumsWidth(), mostrarProdutos.getIndentacao())) {
						break;
					}
				}
					
				ignoreLine(false, "Produto(s) eliminado(s) com sucesso");
				
				for (size_t i = 0; i < vectorInteiros.size(); i++) {
					supermercado.eliminarProduto(vectorInteiros.at(i));
				}
					
                break;

			case 3:    // ================ REATIVAR PRODUTO ===========
				while (!control) {
					clearScreen();
					mostrarMenuInicial(0);
					supermercado.listarProdutos();
					control = leVectorInteiros(vectorInteiros, "Introduza os ID's dos produtos a reativar.");
					if (!control) {
						cin.get();
						continue;
					}
					if (vectorInteiros.size() == 0) {
						sairDoSwitch = true;
						break;
					}
				}
				if (sairDoSwitch) break;  //Teclar enter apenas, cancela a operacao

				for (size_t i = 0; i < vectorInteiros.size(); i++) {

					//================================================
					//Mostrar resumo da operacao
					//================================================
					if (vectorInteiros.size() == 1) {
						ss.str("");
						ss << supermercado.getMapIDtoProduct().at(vectorInteiros.at(i)).getNome();
						str = ss.str();

						mostrarProduto.addNewLine({ "Nome do produto: " , str });  // Mostra o nome do produto

						ss.str("");
						ss << supermercado.getMapIDtoProduct().at(vectorInteiros.at(i)).getCusto();
						str = ss.str();

						mostrarProduto.addNewLine({ "Custo do produto: " , str }); // Mostra o custo

						clearScreen();
						mostrarMenuInicial(0);

						cout << confirmarReativar;

					}
					else {

						mostrarProdutos.addNewLine({ supermercado.getMapIDtoProduct().at(vectorInteiros.at(i)).getNome() , to_string(vectorInteiros.at(i)) });  // Mostra o produto

						clearScreen();
						mostrarMenuInicial(0);

						cout << confirmarReativar;


					}
				}
				if (vectorInteiros.size() == 1) {
					if (!confirmar(mostrarProduto.getTableVector(), mostrarProduto.getBlocks(), mostrarProduto.getColumsWidth(), mostrarProduto.getIndentacao())) {
						break;
					}
				}
				else {
					if (!confirmar(mostrarProdutos.getTableVector(), mostrarProdutos.getBlocks(), mostrarProdutos.getColumsWidth(), mostrarProdutos.getIndentacao())) {
						break;
					}
				}

				ignoreLine(false, "Produto(s) reativado(s) com sucesso");

				for (size_t i = 0; i < vectorInteiros.size(); i++) {
					supermercado.reactivarProduto(vectorInteiros.at(i));
				}

				break;
        }
    }
}

/******************************************
 * Gestao de Transacoes
 ******************************************/

unsigned short int menuGestaoTransacoes() {
    unsigned short int opcao;
    bool control = false;
    do {
        mostrarMenuInicial(3);
        Table menuProdutos({ "1 - Registar compra" }, 34);
        menuProdutos.addNewLine({ "2 - Listar todas as transacoes" });
        menuProdutos.addNewLine({ "3 - Listar transacoes de um cliente" });
        menuProdutos.addNewLine({ "4 - Listar transacoes por data(s)" });
        menuProdutos.addNewLine({ "5 - Listar transacoes por produto" });
        menuProdutos.addNewLine({ "0 - Voltar ao menu inicial" });
        cout << menuProdutos;
        control = leUnsignedShortInt(opcao, 0, 5);
    } while (!control);
    return opcao;
}

void opcoesGestaoTransacoes(VendeMaisMais & supermercado) {
    unsigned int opcao;
    while ((opcao = menuGestaoTransacoes())) {
        string nome;
        string input;
        unsigned int idClienteOuProduto = 0;
        bool sairDoSwitch = false;
        bool control = false;
        vector<unsigned int> vetorIdProdutos;
        vector<string> vetorStringDatas;
        bool controlAux = false;

		stringstream ss;
		string str;
		Table mostrarCliente({ "Informacao" , "Dados" });
		Table mostrarTransacao({ "ID do produto", "Nome do produto", "Custo" });

		Table confirmarTransacao({ "Tem a certeza que pretende realizar a transacao?" });

		float total = 0;

        switch (opcao) {
            case 1:      //    =============== REGISTRAR COMPRA ==============
                do {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarClientesOrdemAlfa(true); //Mostra clientes e seus respetivos ids
                    Table introIdNome({ "Introduza o ID do cliente." });
                    cout << introIdNome << endl;
                    getline(cin, input);
                    if (stringVazia(input)) {
                        sairDoSwitch = true;
                        break;
                    }
                    trimString(input);
                    if (isdigit(input.at(0))) {
                        idClienteOuProduto = stoi(input);
                        control = supermercado.encontrarCliente(idClienteOuProduto);
                        if (!control) ignoreLine(false);
                    }
                    else {
                        Table erro({ "Esse input nao corresponde a um ID" });
                        cout << erro;
                        //if (!control) break;
                        ignoreLine(false);
                    }
                } while (!control);
                if (sairDoSwitch) break;
                while (!controlAux) {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarProdutos(true);
                    controlAux = leVectorInteiros(vetorIdProdutos, "Introduza os ID's dos produtos a comprar (Ex: 1 3 6)");
                    if (!controlAux) {
                        cin.get();
                    }
                }

				//================================================
				//      Mostrar resumo da operacao
				//================================================

				ss.str("");
				ss << idClienteOuProduto;
				str = ss.str();

				mostrarCliente.addNewLine({ "ID do cliente: " , str });  // Mostra o ID do cliente

				ss.str("");
				ss << supermercado.getMapIDtoCliente().at(idClienteOuProduto).getNome();
				str = ss.str();

				mostrarCliente.addNewLine({ "Nome do cliente: " , str }); // Mostra o nome do cliente

				
				for (size_t i = 0; i < vetorIdProdutos.size(); i++) {
					
					
					if (i == 0) {

						ss.str("");
						ss << setw(7) << fixed << setprecision(2) << right << supermercado.getMapIDtoProduct().at(vetorIdProdutos.at(i)).getCusto();
						str = ss.str();

						mostrarTransacao.addNewLine({ to_string(vetorIdProdutos.at(i)) , 
							supermercado.getMapIDtoProduct().at(vetorIdProdutos.at(i)).getNome(), 
							str });

						total += supermercado.getMapIDtoProduct().at(vetorIdProdutos.at(i)).getCusto();
					}
					else {
						ss.str("");
						ss << setw(7) << fixed << setprecision(2) << right << supermercado.getMapIDtoProduct().at(vetorIdProdutos.at(i)).getCusto();
						str = ss.str();
	
						mostrarTransacao.addDataInSameLine({ to_string(vetorIdProdutos.at(i)) ,
							supermercado.getMapIDtoProduct().at(vetorIdProdutos.at(i)).getNome(),
							str });

						total += supermercado.getMapIDtoProduct().at(vetorIdProdutos.at(i)).getCusto();
					}
				}

				ss.str("");
				ss << setw(7) << fixed << setprecision(2) << right << total;
				str = ss.str();
				
				mostrarTransacao.addNewLine({ "Total: ", to_string(vetorIdProdutos.size()) + " produto(s)" , str });


				clearScreen();
				mostrarMenuInicial(0);


				cout << confirmarTransacao << mostrarCliente;

				if (!confirmar(mostrarTransacao.getTableVector(), mostrarTransacao.getBlocks(), mostrarTransacao.getColumsWidth(), mostrarTransacao.getIndentacao())) {
					break;
				}
				ignoreLine(false, "Transacao efetuada com sucesso");

                supermercado.registarTransacao(idClienteOuProduto, vetorIdProdutos);
                supermercado.saveChanges();
                break;
            case 2:      //  =========== LISTAR TODAS AS TRANSACOES ===========
                clearScreen();
                mostrarMenuInicial(0);
                supermercado.listarTransacoes();
                ignoreLine(false);
                break;
            case 3:      // ============ LISTAR TRANSACOES DE UM CLIENTE ======
                do {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarClientesOrdemAlfa();
                    Table introIdNome({ "Introduza o ID ou o NOME do cliente." });
                    cout << introIdNome << endl;
                    getline(cin, input);
                    if (stringVazia(input)) {
                        //cin.ignore();
                        sairDoSwitch = true;
                        break;
                    }
                    trimString(input);
                    if (isdigit(input.at(0))) {
                        idClienteOuProduto = stoi(input);
                        clearScreen();
                        mostrarMenuInicial(0);
                        control = supermercado.encontrarCliente(idClienteOuProduto);
                        if (!control) continue; //Se o cliente nao existir
                        supermercado.listarTransacoes(idClienteOuProduto);
                        //ignoreLine(false);
                    }
                    else {
                        clearScreen();
                        mostrarMenuInicial(0);
                        control = supermercado.encontrarCliente(input);
                        if (!control) continue; //Se o cliente nao existir
                        idClienteOuProduto = supermercado.getMapNametoCliente().at(input).getId();
                        supermercado.listarTransacoes(idClienteOuProduto);
                        //controlAux = true;
                        //ignoreLine(false);
                    }
                } while (!control);
                if (sairDoSwitch) break;  //Teclar enter apenas, cancela a operacao
                ignoreLine(false);
                break;
            case 4:      // ============ LISTAR TRANSACOES NUMA DATA ==========
                while (!controlAux) {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarTransacoes();
                    controlAux = leDatas(vetorStringDatas, "Introduza uma data.");
                    if (!controlAux) {
                        cin.get();
                        continue;
                    }
                    if (vetorStringDatas.size() == 0) {
                        //cin.ignore();
                        sairDoSwitch = true;
                        break;
                    }
                }
                if (sairDoSwitch) break;  //Teclar enter apenas, cancela a operacao
                if (vetorStringDatas.size() == 2) {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarTransacoes(vetorStringDatas.at(0), vetorStringDatas.at(1), false);
                }
                else {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarTransacoes(vetorStringDatas.at(0));
                }
                ignoreLine(false);
                break;
            case 5:
                do {
                    clearScreen();
                    mostrarMenuInicial(0);
                    supermercado.listarProdutos();
                    Table introIdNome({ "Introduza o ID ou o NOME do produto." });
                    cout << introIdNome << endl;                    
                    getline(cin, input);
                    if (stringVazia(input)) {
                        sairDoSwitch = true;
                        break;
                    }
                    trimString(input);
                    if (isdigit(input.at(0))) {
                        idClienteOuProduto = stoi(input);
                        clearScreen();
                        mostrarMenuInicial(0);
                        control = supermercado.encontrarProduto(idClienteOuProduto);
                        if (!control) continue; //Se o produto nao existir
                        supermercado.listarTransacoesProduto(idClienteOuProduto);
                        //ignoreLine(false);
                    }
                    else {
                        clearScreen();
                        mostrarMenuInicial(0);
                        control = supermercado.encontrarProduto(input);
                        if (!control) continue; //Se o cliente nao existir
                        idClienteOuProduto = supermercado.getMapNametoCliente().at(input).getId();
                        supermercado.listarTransacoes(idClienteOuProduto);
                        //controlAux = true;
                        //ignoreLine(false);
                    }
                } while (!control);
                if (sairDoSwitch) break;  //Teclar enter apenas, cancela a operacao
                ignoreLine(false);
                break;
        }
    }
}

/******************************************
 * Gestao de Recomendacao
 ******************************************/

unsigned short int menuRecomendacao() {
    unsigned short int opcao;
    bool control = false;
    do {
        mostrarMenuInicial(4);
        Table menuProdutos({ "1 - Listar sugestoes para todos os clientes" }, 53);
        menuProdutos.addNewLine({ "2 - Mostrar sugestao de produto para um cliente" });
        menuProdutos.addNewLine({ "3 - Listar sugestoes para os N piores clientes" });
        menuProdutos.addNewLine({ "0 - Voltar ao menu inicial" });
        cout << menuProdutos;
        control = leUnsignedShortInt(opcao, 0, 3);
    } while (!control);
    return opcao;
}

void opcoesRecomendacao(VendeMaisMais & supermercado) {
    unsigned int opcao;
	
	while ((opcao = menuRecomendacao())) {
		string input;
		unsigned int idCliente;
		bool control = false;
		switch (opcao) {
		case 1:  //================== LISTAR TODAS AS RECOMENDACOES ============
			clearScreen();
			mostrarMenuInicial(0);
			supermercado.listarRecomendacoes();
			ignoreLine(false);
			break;
		case 2: //================== MOSTRAR RECOMENDACAO DE UM CLIENTE ========
			do {
				clearScreen();
				mostrarMenuInicial(0);
				supermercado.listarClientesOrdemAlfa();
				Table introIdNome({ "Introduza o ID ou o NOME do cliente." });
				cout << introIdNome << endl;
				getline(cin, input);
				if (stringVazia(input)) {
					break;
				}
				trimString(input);
				if (isdigit(input.at(0))) {
					idCliente = stoi(input);
					clearScreen();
					mostrarMenuInicial(0);
					control = supermercado.mostraMensagemRecomendacaoCliente(idCliente);
					ignoreLine(false);
				}
				else {
					clearScreen();
					mostrarMenuInicial(0);
					control = supermercado.mostraMensagemRecomendacaoCliente(input);
					ignoreLine(false);
				}
			} while (!control);
			break;
		case 3:  //================== MOSTRAR RECOMENDACAO DOS N PIORES CLIENTES ========
			do {
				clearScreen();
				mostrarMenuInicial(0);
				supermercado.listarClientesOrdemAlfa();
				Table introN({ "Introduza N para mostrar as recomendacoes dos N piores clientes." });
				cout << introN << endl;
				getline(cin, input);
				if (stringVazia(input)) {
					break;
				}
				trimString(input);

				//control = leUnsignedInt(idCliente, 1, supermercado.getMapIDtoCliente().size(), "Numero de clientes invalido");//idCLiente = N

				

				if (isdigit(input.at(0))) {
					idCliente = stoi(input);
					clearScreen();
					mostrarMenuInicial(0);
					supermercado.listarRecomendacoes(supermercado.calcularBottomN(idCliente));
					control = true;
					ignoreLine(false);
				}
				else {
	
					Table erro({ "Valor invalido" });
					cout << erro;
					control = false;
					ignoreLine(false);
				}
			} while (!control);

			break;
		}
	}
}
