#include "Menus.h"

const string PATH = "/Users/joaofurriel/Documents/Estudo/MIEIC/Ano1/Programação/ProjectoVende++/Vende++20/Vende++20/";

bool infoInicial(string &loja, string &fichClientes, string &fichProdutos, string &fichTransacoes){
    
    ifstream inStreamClientes, inStreamProdutos, inStreamTransacoes;
    bool clientesExiste, produtosExiste, transacoesExiste;
    
    /*cout << "Introduza o nome da loja" << endl;
     getline(cin, loja);
     
     cout << "Introduza o nome do ficheiro de clientes" << endl;
     getline(cin, fichClientes);
     
     cout << "Introduza o nome do ficheiro de produtos" << endl;
     getline(cin, fichProdutos);
     
     cout << "Introduza o nome do ficheiro de transações" << endl;
     getline(cin, fichTransacoes);*/

    
    loja = "Micro-Preço";
    fichClientes = "clientes.txt";
    fichProdutos = "produtos.txt";
    fichTransacoes = "transacoes.txt";
    
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

void opcoesIniciais(VendeMaisMais &supermercado){
    unsigned int opcao;
    
    while((opcao = menuInicial()))
        switch (opcao){
            case 1: opcoesGestaoClientes(supermercado);
                break;
            case 2: opcoesGestaoProdutos(supermercado);
                break;
            case 3: opcoesGestaoTransacoes(supermercado);
                break;
            case 4: opcoesRecomendacao(supermercado);
                break;
        }
    
    supermercado.saveChanges();
}

unsigned short int menuInicial(){
    unsigned short int opcao;
    
    mostrarMenuInicial(0);
    opcao = leUnsignedShortInt(0, 4);
    
    /*if(opcao == 5)
        return 0;*/
    
    return opcao;
}

void mostrarMenuInicial(unsigned short int opcaoEscolhida){
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
	default:
		menuCabecalho = { "1 - Clientes", "2 - Produtos", "3 - Transacoes", "4 - Recomendacoes", "0 - Sair" };
		break;
	}
	Table menuOpcoes(menuCabecalho);
    cout << menu << endl;
    cout << menuOpcoes;
}

/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int menuGestaoClientes(){
    unsigned short int opcao;
    
    mostrarMenuInicial(1);
    Table menuClientes({ "1 - Listar clientes" });
    menuClientes.addNewLine({ "2 - Ver informacao cliente" });
    menuClientes.addNewLine({ "3 - Adicionar cliente" });
    menuClientes.addNewLine({ "4 - Remover cliente" });
    menuClientes.addNewLine({ "0 - Voltar ao menu inicial" });
    cout << menuClientes;
    
    opcao = leUnsignedShortInt(0, 4);
    
    return opcao;
}


void opcoesGestaoClientes(VendeMaisMais &supermercado){
    unsigned int opcao;
    string nome;
    unsigned int idCliente;
    while((opcao = menuGestaoClientes())) {
		bool control = false;
		
        switch (opcao){
            case 1:           //=========== MOSTRAR CLIENTES ==============
                clearScreen();
                mostrarMenuInicial(0);
                supermercado.listarClientesOrdemAlfa();
                ignoreLine();
                break;
			case 2:          //============ MOSTRAR UM CLIENTE ============
				do {
					clearScreen();
					mostrarMenuInicial(0);
					Table introIdNome({ "Introduza o ID ou o NOME do cliente." });
					cout << introIdNome << endl;
					cin.ignore();
					getline(cin, nome);
					if (stringVazia(nome)) {
						//cin.ignore();
						break;
					}

					trimString(nome);
					if (isdigit(nome.at(0))) {

						idCliente = stoi(nome);
						control = supermercado.mostraInformacaoCliente(idCliente);
						ignoreLine(false);

					}
					else {
						control = supermercado.mostraInformacaoCliente(nome);
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
					cin.ignore();
					getline(cin, nome);
					if (stringVazia(nome)) {
						//cin.ignore();
						break;
					}

					trimString(nome);
					control = validateName(nome);
					ignoreLine("Cliente adicionado com sucesso", false);


				} while (!control);
				supermercado.adicionarCliente(nome);
				supermercado.saveChanges();
				break;
			case 4:            //============  ELIMINAR CLIENTES ================
				do {
					clearScreen();
					mostrarMenuInicial(0);
					Table introIdNome({ "Introduza o ID ou o NOME do cliente a eliminar." });
					cout << introIdNome << endl;
					cin.ignore();
					getline(cin, nome);
					if (stringVazia(nome)) {
						//cin.ignore();
						break;
					}

					trimString(nome);
					if (isdigit(nome.at(0))) {

						idCliente = stoi(nome);
						control = supermercado.eliminarCliente(idCliente);
						;
						ignoreLine(false);

					}
					else {
						control = supermercado.eliminarCliente(nome);
						ignoreLine(false);
					}

				} while (!control);
				supermercado.saveChanges();
				break;
            case 0:
                break;
        }
        
        //break;
    }
}

/******************************************
* Gestao de Produtos
******************************************/

unsigned short int menuGestaoProdutos(){
    unsigned short int opcao;
    
	mostrarMenuInicial(2);
    Table menuProdutos({ "1 - Listar produtos" }, 17);
    menuProdutos.addNewLine({ "2 - Adicionar produto" });
    menuProdutos.addNewLine({ "3 - Remover produto" });
    menuProdutos.addNewLine({ "0 - Voltar ao menu inicial" });
    cout << menuProdutos;
    
    opcao = leUnsignedShortInt(0, 3);
    
        
    return opcao;
}


void opcoesGestaoProdutos(VendeMaisMais &supermercado){
    unsigned int opcao;
    string nome;
    float custo;
    
    while ((opcao = menuGestaoProdutos()))
        switch (opcao){
            case 1:     // ============== MOSTRAR PRODUTOS ============
                clearScreen();
				mostrarMenuInicial(0);
				supermercado.listarProdutos();
				ignoreLine();
				break;
            case 2:    // =============== ADICIONAR PRODUTO ===========
                cout << "Qual o nome do produto: ";
				cin.ignore();
                getline(cin, nome);
                cout << "Qual o custo do produto: ";
                cin >> custo;
                supermercado.adicionarProduto(nome, custo);
				supermercado.saveChanges();
                break;
            case 3:    // ================ ELIMINAR PRODUTO ===========
				cout << "Qual o nome do produto: ";
				cin.ignore();
				getline(cin, nome);
                supermercado.eliminarProduto(nome);
				supermercado.saveChanges();
                break;
				//NAO TA BEM
            case 4:
                break;
        }


	/*unsigned int opcao;
	string nome;

	while ((opcao = menuGestaoClientes())) {
		switch (opcao) {
		case 1:
			
		case 2:
			cout << "Qual o nome do cliente: ";
			getline(cin, nome);
			supermercado.mostraInformacaoCliente(nome);
			//system("pause");
			break;
		case 3:
			cout << "Qual o nome do cliente: ";
			getline(cin, nome);
			supermercado.adicionarCliente(nome);
			break;
		case 0:
			break;
		}

		//break;
	}*/

}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuGestaoTransacoes(){
    return 0;// TESTE
}

void opcoesGestaoTransacoes(VendeMaisMais & supermercado){
    unsigned int opcao;
    
    while((opcao = menuGestaoTransacoes()))
        switch (opcao){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuRecomendacao(){
    return 0; // TESTE
}

void opcoesRecomendacao(VendeMaisMais & supermercado){
    unsigned int opcao;
    
    while((opcao = menuRecomendacao()))
        switch (opcao){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    
}

/******************************************
 * Menu Inicial
 ******************************************/



