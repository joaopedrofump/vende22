#include "Table.h"

Table::Table(vector<string> components){
	vector<int> spaces;
	for (size_t i = 0; i < components.size(); i++){
		spaces.push_back((int)components.at(i).length());
	}
	formatTable('_', ' ', spaces);
	formatTable(' ', '|', spaces);
	
	tableStream << " |  ";
	for (int i = 0; i < components.size(); i++){
		tableStream << components.at(i) << "  |  ";
	}
	tableStream << endl;

	formatTable('_', '|', spaces);

	numColumns = (int)components.size();
	numLines = 1;
	columnsWidth = spaces;
	lastLineComponents = components;
	tableVector.push_back(components);
	blocks.push_back(false);
}

Table::Table(vector<string> components, vector<int> spacesForColumn){
		
	formatTable('_', ' ', spacesForColumn);
	formatTable(' ', '|', spacesForColumn);

	tableStream << " |  ";
	for (int i = 0; i < components.size(); i++){
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

Table::Table(vector<vector<string>> tableVector, vector<bool> blocks){



	unsigned int numColumnsV = 0;
	vector<int> columnsSizes;
	for (int i = 0; i < tableVector.size(); i++){
		if (numColumnsV < tableVector.at(i).size()){
			numColumnsV = (int)tableVector.at(i).size();
		}
	}
	for (int j = 0; j < numColumnsV; j++){
		columnsSizes.push_back(0);
	}

	for (int x = 0; x < tableVector.size(); x++){
		for (int y = 0; y < tableVector.at(x).size(); y++){
			if (columnsSizes.at(y) < tableVector.at(x).at(y).length()){
				columnsSizes[y] = (int)tableVector.at(x).at(y).length();
			}
		}
	}

	formatTable('_', ' ', columnsSizes);
	formatTable(' ', '|', columnsSizes);
	
	
	for (size_t x = 0; x < tableVector.size(); x++){

		if (tableVector.at(x).size() < numColumnsV){
			tableVector.at(x).push_back("");
		}
		tableStream << " |  ";
		for (int i = 0; i < numColumnsV; i++){
			tableStream << tableVector.at(x).at(i) << string(columnsSizes.at(i) - tableVector.at(x).at(i).length(), ' ') << "  |  ";
		}
		tableStream << endl;

		if (blocks.at(x)){
			formatTable('_', '|', columnsSizes);
			formatTable(' ', '|', columnsSizes);
		}
	}
	formatTable('_', '|', columnsSizes);
}

void Table::addNewLine(vector<string> components){
	

	if (components.size() < this->numColumns){  //Verifica se vector componentes tem menor número de termos 
		for (int x = (int)components.size(); x < numColumns; x++){  //da tabela original e adiciona nesse caso.
			components.push_back("");
		}
	}

	if (components.size() > this->numColumns){  //Verifica se vector componentes tem maior número de termos 
		for (int x = numColumns; x < components.size(); x++){ //da tabela original e remove-os, nesse caso.
			components.pop_back();
		}
	}

	vector<int> spaces;

	for (int i = 0; i < components.size(); i++){
		if (components.at(i).length() >= this->columnsWidth.at(i)){
			spaces.push_back((int)components.at(i).length());
		}
		else{
			spaces.push_back(columnsWidth.at(i));
		}
	} //Redefine a largura das colunas para a tabela alterada

	stringstream newTable_tmp;
	newTable_tmp << tableStream.str();

	tableStream.str(string());
	tableStream.clear();
	
	Table newTable(lastLineComponents, spaces);

	tableStream << newTable;

	formatTable(' ', '|', spaces);
	
	tableStream << " |  ";
	for (size_t i = 0; i < components.size(); i++){
		tableStream << components.at(i) << string(spaces.at(i) - components.at(i).length(), ' ') << "  |  ";
	}
	tableStream << endl;

	
	formatTable('_', '|', spaces);
	

	numLines++;
	this->lastLineComponents = components;
	tableVector.push_back(components);

	blocks.pop_back();
	blocks.push_back(true);
	blocks.push_back(false);
}

void Table::addDataInSameLine(vector<string> components){

	if (components.size() < this->numColumns){  //Verifica se vector componentes tem menor número de termos 
		for (size_t x = components.size(); x < numColumns; x++){  //da tabela original e adiciona nesse caso.
			components.push_back("");
		}
	}

	if (components.size() > this->numColumns){  //Verifica se vector componentes tem maior número de termos 
		for (int x = numColumns; x < components.size(); x++){ //da tabela original e remove-os, nesse caso.  MELHORAR!!!
			components.pop_back();
		}
	}

	vector<int> spaces;

	for (size_t i = 0; i < components.size(); i++){
		if (components.at(i).length() >= this->columnsWidth.at(i)){
			spaces.push_back((int)components.at(i).length());
		}
		else{
			spaces.push_back(columnsWidth.at(i));
		}
	} //Redefine a largura das colunas para a tabela alterada

	/*unsigned int totalSpace = 0;
	for (int i = 0; i < spaces.size(); i++){
		totalSpace += spaces.at(i);
	}
	
	tableStream << string(4 + 5 * numColumns, '\b'); //Elimina ultima linha de table*/

	tableStream.ignore(4 + 5 * numColumns);

	tableStream << " |  ";
	for (int i = 0; i < components.size(); i++){
		tableStream << components.at(i) << string(spaces.at(i) - components.at(i).length(), ' ') << "  |  ";
	}
	tableStream << endl;


	formatTable('_', '|', spaces);



}

void Table::formatTable(char internalChar, char limitingChar, vector<int> spacesForColumn){
	tableStream << " " << limitingChar;
	for (size_t i = 0; i < spacesForColumn.size(); i++){
		for (int x = 0; x < spacesForColumn.at(i) + 4; x++){
			tableStream << internalChar;
		}
		tableStream << limitingChar;
	}
	tableStream << endl;
}

ostream& operator<<(ostream& out, const Table &tableToShow){

	out << tableToShow.tableStream.str();
	return out;
}