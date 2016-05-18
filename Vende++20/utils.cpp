#include "utils.h"
#include <sstream>



void clearScreen(){
  
#ifdef __llvm__
    
    system("clear");
    
#elif _MSC_VER
    
    system("cls");
    
#endif
    
}


unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max){

    unsigned short int userSInt;
    
    do {
        //cout << "Por favor introduza um numero entre " << min << " e " << max << endl;
        cin >> userSInt;
        
        if (cin.fail()) {
            
            if (cin.eof()) {
                
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
                
            }
            
            else {
                
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            
        }
        
        else if (userSInt < min || userSInt > max) {
            
            cout << "Invalid Input" << endl;
            
        }
        
        
    }while (userSInt < min || userSInt > max);
    
    return userSInt;

}


void trimString(string &inputString) {
    
    //only for strings bigger than one char
    if (inputString.size() > 1) {
        
        //erase every ' ' char till it finds the fisrt that it is not ' '
        inputString.erase(0, inputString.find_first_not_of(" "));
        
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

void ignoreLine() {
    
    string temp;
    Table tableEnter({ "Press Enter to Continue." });
    cout << tableEnter << endl;
    cin.ignore(10000, '\n');
    getline(cin, temp);
    
}










