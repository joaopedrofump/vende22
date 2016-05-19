#include "Table.h"

Table::Table(vector<string> components) {
    vector<int> spaces;
    for (size_t i = 0; i < components.size(); i++) {
        spaces.push_back((int)components.at(i).length());
    }
    formatTable('_', ' ', spaces);
    formatTable(' ', '|', spaces);
    tableStream << " |  ";
    for (int i = 0; i < components.size(); i++) {
        tableStream << components.at(i) << "  |  ";
    }
    tableStream << endl;
    formatTable('_', '|', spaces);
    numColumns = (int)components.size();
    numLines = 1;
    columnsWidth = spaces;
    lastLineComponents = components;
    tableVector.push_back(components);
    blocks.push_back(true);
}
Table::Table(vector<string> components, vector<int> spacesForColumn) {
    formatTable('_', ' ', spacesForColumn);
    formatTable(' ', '|', spacesForColumn);
    tableStream << " |  ";
    for (int i = 0; i < components.size(); i++) {
        tableStream << components.at(i) << string(spacesForColumn.at(i) - components.at(i).length(), ' ') << "  |  ";
    }
    tableStream << endl;
    formatTable('_', '|', spacesForColumn);
    numColumns = (int)components.size();
    numLines = 1;
    columnsWidth = spacesForColumn;
    lastLineComponents = components;
    tableVector.push_back(components);
}


Table::Table(vector<vector<string>> tableVector, vector<bool> blocks, vector<int> spacesForColumn) {
    
    unsigned int numColumnsV = 0;
    vector<int> columnsSizes;
    for (size_t i = 0; i < tableVector.size(); i++) {
        if (numColumnsV < tableVector.at(i).size()) {
            numColumnsV = (int)tableVector.at(i).size();
        }
    }
    for (int j = 0; j < numColumnsV; j++) {
        columnsSizes.push_back(0);
    }
    formatTable('_', ' ', spacesForColumn);
    formatTable(' ', '|', spacesForColumn);
    for (int x = 0; x < tableVector.size(); x++) {
        if (tableVector.at(x).size() < numColumnsV) {
            tableVector.at(x).push_back("");
        }
        tableStream << " |  ";
        for (int i = 0; i < numColumnsV; i++) {
            tableStream << tableVector.at(x).at(i) << string(spacesForColumn.at(i) - tableVector.at(x).at(i).length(), ' ') << "  |  ";
        }
        tableStream << endl;
        if (blocks.at(x)) {
            formatTable('_', '|', spacesForColumn);
            formatTable(' ', '|', spacesForColumn);
            /*if (x < tableVector.size() - 1){
             formatTable(' ', '|', spacesForColumn);
             }*/
        }
    }
    
    this->blocks = blocks;
    this->tableVector = tableVector;
    this->columnsWidth = spacesForColumn;
    this->numColumns = numColumnsV;
    this->numLines = (int)tableVector.size();
    this->lastLineComponents = tableVector.at(tableVector.size() - 1);
}


void Table::addNewLine(vector<string> components) {
    if (components.size() < this->numColumns) {  //Verifica se vector componentes tem menor número de termos
        for (size_t x = components.size(); x < numColumns; x++) {  //da tabela original e adiciona nesse caso.
            components.push_back("");
        }
    }
    if (components.size() > this->numColumns) {  //Verifica se vector componentes tem maior número de termos
        for (int x = numColumns; x < components.size(); x++) { //da tabela original e remove-os, nesse caso.
            components.pop_back();
        }
    }
    vector<int> spaces;
    for (size_t i = 0; i < components.size(); i++) {
        if (components.at(i).length() >= this->columnsWidth.at(i)) {
            spaces.push_back((int)components.at(i).length());
        }
        else {
            spaces.push_back(columnsWidth.at(i));
        }
    } //Redefine a largura das colunas para a tabela alterada
    tableStream.str(string());
    tableStream.clear();
    Table newTable(this->tableVector, this->blocks, spaces); //Reconstroi a tabela anterior com a largura das colunas redefinida
    tableStream << newTable;
    tableStream << " |  ";
    for (int i = 0; i < components.size(); i++) {
        tableStream << components.at(i) << string(spaces.at(i) - components.at(i).length(), ' ') << "  |  ";
    }
    tableStream << endl;
    formatTable('_', '|', spaces);
    numLines++;
    this->lastLineComponents = components;
    this->tableVector.push_back(components);
    this->columnsWidth = spaces;
    this->blocks.push_back(true);
}
void Table::addDataInSameLine(vector<string> components) {
    if (components.size() < this->numColumns) {  //Verifica se vector componentes tem menor número de termos
        for (size_t x = components.size(); x < numColumns; x++) {  //da tabela original e adiciona nesse caso.
            components.push_back("");
        }
    }
    if (components.size() > this->numColumns) {  //Verifica se vector componentes tem maior número de termos
        for (int x = numColumns; x < components.size(); x++) { //da tabela original e remove-os, nesse caso.  MELHORAR!!!
            components.pop_back();
        }
    }
    vector<int> spaces;
    for (size_t i = 0; i < components.size(); i++) {
        if (components.at(i).length() >= this->columnsWidth.at(i)) {
            spaces.push_back((int)components.at(i).length());
        }
        else {
            spaces.push_back(columnsWidth.at(i));
        }
    } //Redefine a largura das colunas para a tabela alterada
    tableStream.str(string());
    tableStream.clear();
    tableVector.push_back(components);
    blocks.pop_back();
    blocks.push_back(false);
    blocks.push_back(true); //concatena a penultima linha com a última
    Table newTable(this->tableVector, this->blocks, spaces); //Reconstroi a tabela anterior com a largura das colunas redefinida
    tableStream << newTable;
    /*tableStream << " |  ";
     for (int i = 0; i < components.size(); i++){
     tableStream << components.at(i) << string(spaces.at(i) - components.at(i).length(), ' ') << "  |  ";
     }
     tableStream << endl;
     formatTable('_', '|', spaces);*/
}
void Table::formatTable(char internalChar, char limitingChar, vector<int> spacesForColumn) {
    tableStream << " " << limitingChar;
    for (size_t i = 0; i < spacesForColumn.size(); i++) {
        for (int x = 0; x < spacesForColumn.at(i) + 4; x++) {
            tableStream << internalChar;
        }
        tableStream << limitingChar;
    }
    tableStream << endl;
}
ostream& operator<<(ostream& out, const Table &tableToShow) {
    out << tableToShow.tableStream.str();
    return out;
}
