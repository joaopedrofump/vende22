#include "Table.h"

Table::Table(vector<string> components, unsigned int indentacao) {
   
	vector<int> spaces;
    for (size_t i = 0; i < components.size(); i++) {
        spaces.push_back((int)components.at(i).length());
    }
    formatTable('_', ' ', spaces, indentacao);
    formatTable(' ', '|', spaces, indentacao);
    tableStream << string(indentacao, ' ') << " |  ";
    for (int i = 0; i < components.size(); i++) {
        tableStream << components.at(i) << "  |  ";
    }
    tableStream << endl;
    formatTable('_', '|', spaces, indentacao);
    numColumns = (int)components.size();
    numLines = 1;
    columnsWidth = spaces;
    lastLineComponents = components;
    tableVector.push_back(components);
    blocks.push_back(true);

	indent = indentacao;
}

Table::Table(vector<string> components, vector<int> spacesForColumn, unsigned int indentacao) {
    formatTable('_', ' ', spacesForColumn, indentacao);
    formatTable(' ', '|', spacesForColumn, indentacao);
    tableStream << string(indentacao, ' ') << " |  ";
    for (int i = 0; i < components.size(); i++) {
        tableStream << components.at(i) << string(spacesForColumn.at(i) - components.at(i).length(), ' ') << "  |  ";
    }
    tableStream << endl;
    formatTable('_', '|', spacesForColumn, indentacao);
    numColumns = (int)components.size();
    numLines = 1;
    columnsWidth = spacesForColumn;
    lastLineComponents = components;
    tableVector.push_back(components);

	this->indent = indentacao;
}

Table::Table(vector<vector<string>> tableVector, vector<bool> blocks, vector<int> spacesForColumn, unsigned int indentacao) {
    
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
    formatTable('_', ' ', spacesForColumn, indentacao);
    formatTable(' ', '|', spacesForColumn, indentacao);
    for (int x = 0; x < tableVector.size(); x++) {
        if (tableVector.at(x).size() < numColumnsV) {
            tableVector.at(x).push_back("");
        }

        tableStream << string(indentacao, ' ') << " |  ";

        for (int i = 0; i < numColumnsV; i++) {

			int dif = spacesForColumn.at(i) - tableVector.at(x).at(i).length(); //espaços a mais
			string temporario;
			if (dif > 0) {
				temporario = string(spacesForColumn.at(i) - tableVector.at(x).at(i).length(), ' ');
			}
			else {
				temporario = string(tableVector.at(x).at(i).length() - spacesForColumn.at(i), ' ');
			}

			tableStream << tableVector.at(x).at(i) << temporario << "  |  ";
        }
        tableStream << endl;

        if (blocks.at(x)) {
            formatTable('_', '|', spacesForColumn, indentacao);
            //formatTable(' ', '|', spacesForColumn, indentacao);
            if (x < tableVector.size() - 1){
				//formatTable('_', '|', spacesForColumn, indentacao);
				formatTable(' ', '|', spacesForColumn, indentacao);
             }
        }
    }
    
    this->blocks = blocks;
    this->tableVector = tableVector;
    this->columnsWidth = spacesForColumn;
    this->numColumns = numColumnsV;
    this->numLines = (int)tableVector.size();
    this->lastLineComponents = tableVector.at(tableVector.size() - 1);
	this->indent = indentacao;
}

void Table::addNewLine(vector<string> components) {
    if (components.size() < this->numColumns) {  //Verifica se vector componentes tem menor nœmero de termos
        for (size_t x = components.size(); x < numColumns; x++) {  //da tabela original e adiciona nesse caso.
            components.push_back("");
        }
    }
    if (components.size() > this->numColumns) {  //Verifica se vector componentes tem maior nœmero de termos
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
    Table newTable(this->tableVector, this->blocks, spaces, this->indent); //Reconstroi a tabela anterior com a largura das colunas redefinida
    tableStream << newTable;
	formatTable(' ', '|', spaces, this->indent);
    tableStream << string(this->indent, ' ') << " |  ";
    for (int i = 0; i < components.size(); i++) {
        tableStream << components.at(i) << string(spaces.at(i) - components.at(i).length(), ' ') << "  |  ";
    }
    tableStream << endl;
	formatTable('_', '|', spaces, this->indent);
    numLines++;
    this->lastLineComponents = components;
    this->tableVector.push_back(components);
    this->columnsWidth = spaces;
    this->blocks.push_back(true);
}

void Table::addDataInSameLine(vector<string> components) {
    if (components.size() < this->numColumns) {  //Verifica se vector componentes tem menor nœmero de termos
        for (size_t x = components.size(); x < numColumns; x++) {  //da tabela original e adiciona nesse caso.
            components.push_back("");
        }
    }
    if (components.size() > this->numColumns) {  //Verifica se vector componentes tem maior nœmero de termos
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
    blocks.push_back(true); //concatena a penultima linha com a œltima

    Table newTable(this->tableVector, this->blocks, spaces); //Reconstroi a tabela anterior com a largura das colunas redefinida
    tableStream << newTable;
    /*tableStream << " |  ";
     for (int i = 0; i < components.size(); i++){
     tableStream << components.at(i) << string(spaces.at(i) - components.at(i).length(), ' ') << "  |  ";
     }
     tableStream << endl;
     formatTable('_', '|', spaces);*/
	this->columnsWidth = spaces;
}

void Table::formatTable(char internalChar, char limitingChar, vector<int> spacesForColumn, unsigned int indentacaoFT) {
    tableStream << string(indentacaoFT, ' ') << " " << limitingChar;
    for (size_t i = 0; i < spacesForColumn.size(); i++) {
        for (int x = 0; x < spacesForColumn.at(i) + 4; x++) {
            tableStream << internalChar;
        }
        tableStream << limitingChar;
    }
    tableStream << endl;
}


vector<int> Table::getColumsWidth() const {
	return columnsWidth;
}

unsigned int Table::getIndentacao() const {
	return indent;
}

ostream& operator<<(ostream& out, const Table &tableToShow) {
    out << tableToShow.tableStream.str();
	//formatTableShow('_', '|', tableToShow.getColumsWidth(), tableToShow.getIndentacao(), out);
    return out;
}