#include "utils.h"
#include <sstream>




void clearScreen() {

#ifdef __llvm__

	system("clear");

#elif _MSC_VER

	system("cls");

#endif

}




void trimString(string &inputString) {
	

	//only for strings bigger than one char
	if (inputString.size() > 1) {

		//erase every ' ' char till it finds the fisrt that it is not ' '
		inputString.erase(0, inputString.find_first_not_of(" "));

		if (inputString == "")
			return;

		//while the last char is empty, it will be removed from the string
		while (inputString.at(inputString.size() - 1) == ' ') {

			inputString.pop_back();

		}
	}
}

bool validateName(string &nome) {

	trimString(nome);

	stringstream nomeStream(nome); //stringStream que contém o nome do cliente
	vector<string> nomes; //vector com a lista de nomes do cliente

						  //verificar se contém digitos

	for (size_t i = 0; i < nome.size(); i++) {

		if (isdigit((int)nome.at(i))) {

			cout << "O nome não pode conter digitos, apenas letras." << endl;
			return false;

		}

	}

	//preencher o vector com os nomes

	while (!nomeStream.eof()) {
		string nomeActual;
		getline(nomeStream, nomeActual, ' ');
		nomes.push_back(nomeActual);


	}

	//verificar se tem pelo menos dois nomes

	if (nomes.size() < 2) {

		cout << "O nome do cliente tem de ser constituído por pelo menos dois nomes" << endl;
		return false;

	}

	//verificar que cada nome tem pelo menos 3 letras

	for (size_t i = 0; i < nomes.size(); i++) {

		if (nomes.at(i).size() < 2) {

			cout << "Cada nome tem de conter pelo menos duas letras." << endl;
			return false;

		}
	}

	nome.at(0) = (char)toupper(nome.at(0));



	for (size_t i = 0; i < nome.size() - 1; i++) {

		if (nome.at(i) == ' ') {

			nome.at(i + 1) = toupper(nome.at(i + 1));

		}


	}

	return true;


}

bool validateProduct(string &nome) {


	trimString(nome);

	stringstream nomeStream(nome); //stringStream que contém o nome do cliente
	vector<string> nomes; //vector com a lista de nomes do cliente

						  //verificar se contém digitos

						  //preencher o vector com os nomes

	while (!nomeStream.eof()) {
		string nomeActual;
		getline(nomeStream, nomeActual, ' ');
		nomes.push_back(nomeActual);

	}

	//verificar que cada nome tem pelo menos 2 letras

	for (size_t i = 0; i < nomes.size(); i++) {

		if (nomes.at(i).size() < 2) {

			cout << "Cada produto tem de conter pelo menos duas letras." << endl;
			return false;

		}
	}

	nome.at(0) = (char)toupper(nome.at(0));



	for (size_t i = 0; i < nome.size() - 1; i++) {

		if (nome.at(i) == ' ') {

			nome.at(i + 1) = toupper(nome.at(i + 1));

		}


	}

	return true;


}

void SetCursor(int column, int line)

{

#ifdef _MSC_VER
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
		);

#endif
}

int GetCursorX()
{

#ifdef _MSC_VER
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	COORD                      result;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo))
		return -1;


	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);

	return SBInfo.dwCursorPosition.X;
#endif

	return 1;
}

int GetCursorY()
{

#ifdef _MSC_VER
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	COORD                      result;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo))
		return -1;


	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);

	return SBInfo.dwCursorPosition.Y;

#endif

	return 1;
}

void ignoreLine(bool ignoreControl, string message) {

	string temp;
	Table tableEnter({ message });
	cout << tableEnter << endl;
	if (ignoreControl) {

		cin.ignore(1000, '\n');

	}
	getline(cin, temp);

}

bool validateInputStream(istream &inStream, string errorMessage) {


	bool validInput = true;

	if (inStream.fail()) {

		inStream.clear();
		inStream.ignore(1000, '\n');
		ignoreLine(false);
		validInput = false;

	}


	return validInput;

}


bool stringVazia(string stringTeste) {

	if (stringTeste.size() == 0) {

		return true;

	}

	return false;

}

bool leUnsignedShortInt(unsigned short int &input, unsigned short int min, unsigned short int  max, string mensagemErro) {

	/*string inputUser;
	unsigned short int userSInt;
	bool inputValido = false;

	do {
		//cout << "Por favor introduza um numero entre " << min << " e " << max << endl;
		getline(cin, inputUser);
		if (inputUser == "")
		{
			return true;
		}
		if (cin.fail()) {

			if (cin.eof()) {

				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}

			else {

				Table invalidInput({ "Invalid Input" });
				cout << invalidInput << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}

		}

		else if (userSInt < min || userSInt > max) {

			Table invalidInput({ "Invalid Input" });
			cout << invalidInput << endl;

		}
		else {
			inputValido = true;
		}


	} while (userSInt < min || userSInt > max);

	input = userSInt;
	return inputValido;*/






	string inputUser;
	bool resultadoBool = false;

	Table tabelaMensagemErro({ mensagemErro });
	
	getline(cin, inputUser);
	stringstream inteirosStream(inputUser);
	trimString(inputUser);

	if (inputUser.size() == 0) {

		input = 0;
		return true;

	}

	while (!inteirosStream.eof()) {

		unsigned short int currentInt;
		inteirosStream >> currentInt;

		if (inteirosStream.fail()) {

			inteirosStream.clear();
			inteirosStream.ignore(1);


		}

		else {

			input = currentInt;
			resultadoBool = true;
			break;

		}


	}

	if (!resultadoBool) {

		cout << tabelaMensagemErro << endl;


	}

	return resultadoBool;




}

bool leVectorInteiros(vector <unsigned int> &resultado, string mensagem, string mensagemErro) {

	string inteiros;
	bool resultadoBool = false;

	Table tabelaMensagem({ mensagem });
	Table tabelaMensagemErro({ mensagemErro });
	cout << tabelaMensagem << endl;
	getline(cin, inteiros);
	stringstream inteirosStream(inteiros);
	trimString(inteiros);

	if (inteiros.size() == 0) {

		return true;

	}

	while (!inteirosStream.eof()) {

		unsigned int currentInt;
		inteirosStream >> currentInt;

		if (inteirosStream.fail()) {

			inteirosStream.clear();
			inteirosStream.ignore(1);


		}

		else {

			resultado.push_back(currentInt);
			resultadoBool = true;

		}


	}

	if (!resultadoBool) {

		cout << tabelaMensagemErro << endl;


	}

	return resultadoBool;

}

bool leDatas(vector<string> &resultado, string mensagem, string mensagemErro) {


	string datas;
	bool resultadoBool = false;



	Table tabelaMensagem({ mensagem });
	Table tabelaMensagemErro({ mensagemErro });
	cout << tabelaMensagem << endl;
	getline(cin, datas);
	stringstream datasStream(datas);
	trimString(datas);

	if (datas.size() == 0) {

		return true;

	}

	while (!datasStream.eof()) {

		string currentData;
		getline(datasStream, currentData, ' ');

		Data currentDataData(currentData);
		if (currentDataData.getValid()) {

			resultado.push_back(currentData);
			resultadoBool = true;

		}

		if (resultado.size() == 2) {

			resultadoBool = true;

		}



	}

	if (!resultadoBool) {

		cout << tabelaMensagemErro << endl;


	}



	return resultadoBool;

}

bool leStringFloat(pair<string, float> &resultado, string mensagem, string mensagemErro) {

	string input;
	bool resultadoBool = false;
	bool nomeOk = false;

	Table tabelaMensagem({ mensagem });
	Table tabelaMensagemErro({ mensagemErro });
	cout << tabelaMensagem << endl;
	getline(cin, input);
	stringstream inputStream(input);
	trimString(input);

	if (input.size() == 0) {

		return true;

	}

	while (!inputStream.eof()) {

		do {
			string strAtual;
			inputStream >> strAtual;

			if (inputStream.fail()) {

				inputStream.clear();
				inputStream.ignore(1);


			}

			else {
				nomeOk = validateProduct(strAtual);
				resultado.first = strAtual;
			}
		} while (!nomeOk);

		do {
			float floatAtual;
			inputStream >> floatAtual;

			if (inputStream.fail()) {

				inputStream.clear();
				inputStream.ignore(1);


			}

			else {

				resultado.second = floatAtual;
				resultadoBool = true;

			}
		} while (!resultadoBool && !inputStream.eof());

	}

	if (!resultadoBool) {

		cout << tabelaMensagemErro << endl;


	}

	return resultadoBool;

}