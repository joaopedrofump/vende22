#include "Menus.h"

using namespace std;

const string PATH = "/Users/joaofurriel/Documents/Estudo/MIEIC/Ano1/Programação/ProjectoVende++/Vende++20/Vende++20/";

bool infoInicial(string &loja, string &fichClientes, string &fichProdutos, string &fichTransacoes) {

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
		}

	supermercado.saveChanges();
}

unsigned short int menuInicial() {
	unsigned short int opcao;
	bool control = false;

	while (!control) {
		mostrarMenuInicial(0);
		control = leUnsignedShortInt(opcao, 0, 4);
	}

	/*if(opcao == 5)
	return 0;*/

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
unsigned short int menuGestaoClientes() {
	unsigned short int opcao;
	bool control = false;
	do {


		mostrarMenuInicial(1);
		Table menuClientes({ "1 - Listar clientes" });
		menuClientes.addNewLine({ "2 - Ver informacao cliente" });
		menuClientes.addNewLine({ "3 - Adicionar cliente" });
		menuClientes.addNewLine({ "4 - Remover cliente" });
		menuClientes.addNewLine({ "0 - Voltar ao menu inicial" });
		cout << menuClientes;

		control = leUnsignedShortInt(opcao, 0, 4);
	} while (!control);

	return opcao;
}


void opcoesGestaoClientes(VendeMaisMais &supermercado) {
	unsigned int opcao;
	string nome;
	unsigned int idCliente;

	while ((opcao = menuGestaoClientes())) {
		bool control = false;
		unsigned int iterador = 0;
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
				Table introIdNome({ "Introduza o ID ou o NOME do cliente." });
				cout << introIdNome << endl;
				getline(cin, nome);
				if (stringVazia(nome)) {
					break;
				}

				trimString(nome);
				if (isdigit(nome.at(0))) {

					idCliente = stoi(nome);
					clearScreen();
					mostrarMenuInicial(0);
					control = supermercado.mostraInformacaoCliente(idCliente);
					ignoreLine(false);

				}
				else {
					clearScreen();
					mostrarMenuInicial(0);
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
				getline(cin, nome);

				if (stringVazia(nome)) {
					break;
				}

				trimString(nome);
				control = validateName(nome);
				ignoreLine(false, "Cliente adicionado com sucesso");


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
				getline(cin, nome);
				if (stringVazia(nome)) {
					break;
				}

				trimString(nome);
				if (isdigit(nome.at(0))) {

					idCliente = stoi(nome);
					control = supermercado.eliminarCliente(idCliente);

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

unsigned short int menuGestaoProdutos() {

	unsigned short int opcao;
	bool control = false;
	do {
		mostrarMenuInicial(2);
		Table menuProdutos({ "1 - Listar produtos" }, 17);
		menuProdutos.addNewLine({ "2 - Adicionar produto" });
		menuProdutos.addNewLine({ "3 - Remover produto" });
		menuProdutos.addNewLine({ "0 - Voltar ao menu inicial" });
		cout << menuProdutos;

		control = leUnsignedShortInt(opcao, 0, 3);

	} while (!control);

	return opcao;
}


void opcoesGestaoProdutos(VendeMaisMais &supermercado) {

	unsigned int opcao;

	while ((opcao = menuGestaoProdutos())) {

		string input;
		unsigned int idProduto;
		string nomeProduto;
		float custoProduto;
		unsigned int iterador = 0;
		bool control = false;
		bool sairDoSwitch = false;
		pair<string, float> pairNomeCusto;
		vector<unsigned int> vectorInteiros;

		switch (opcao) {

		case 1:     // ============== MOSTRAR PRODUTOS ============
			clearScreen();
			mostrarMenuInicial(0);
			supermercado.listarProdutos();
			ignoreLine();
			break;

		case 2:     // ============== ADICIONAR PRODUTO ===========
			while (!control) {
				clearScreen();
				mostrarMenuInicial(0);
				control = leStringFloat(pairNomeCusto, "Introduza o nome seguido do custo do produto.");

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

			supermercado.adicionarProduto(pairNomeCusto.first, pairNomeCusto.second);

			ignoreLine(false);

			break;
		case 3:    // ================ ELIMINAR PRODUTO ===========

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
				supermercado.eliminarProduto(vectorInteiros.at(i));
			}

			ignoreLine(false);

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
		unsigned int iterador = 0;
		switch (opcao) {
		case 1:      //    =============== REGISTRAR COMPRA ==============
			do {
				clearScreen();
				mostrarMenuInicial(0);
				supermercado.listarClientesOrdemAlfa(true); //Mostra clientes e seus respetivos ids

				Table introIdNome({ "Introduza o ID do cliente." });
				cout << introIdNome << endl;
				if (iterador == 0)
					cin.ignore();
				iterador++;
				getline(cin, input);

				if (stringVazia(input)) {
					//cin.ignore();
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

			supermercado.registarTransacao(idClienteOuProduto, vetorIdProdutos);

			supermercado.saveChanges();
			break;
		case 2:      //  =========== LISTAR TODAS AS TRANSACOES ===========
			clearScreen();
			mostrarMenuInicial(0);
			cin.ignore();
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
				if (iterador == 0)
					cin.ignore();
				iterador++;
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
				if (iterador == 0)
					cin.ignore();
				iterador++;
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
				if (iterador == 0)
					cin.ignore();
				iterador++;
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
		mostrarMenuInicial(3);
		Table menuProdutos({ "1 - Listar sugestoes para todos os clientes" }, 34);
		menuProdutos.addNewLine({ "2 - Listar sugestao de produto para um cliente" });
		menuProdutos.addNewLine({ "3 - Listar clientes adicionados recentemente" });
		menuProdutos.addNewLine({ "0 - Voltar ao menu inicial" });

		cout << menuProdutos;

		control = leUnsignedShortInt(opcao, 0, 5);
	} while (!control);

	return opcao;
}

void opcoesRecomendacao(VendeMaisMais & supermercado) {
	unsigned int opcao;

	while ((opcao = menuRecomendacao()))
		switch (opcao) {
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