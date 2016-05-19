#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.h"


using namespace std;


class Table {
private:
	//stringstream tableStream;
	vector<vector<string>> tableVector;
	vector<bool> blocks; //FALSE se a linha está colada à de cima, TRUE se são linhas separadas

	unsigned int numColumns;
	unsigned int numLines;
	vector<int> columnsWidth;
	vector<string> lastLineComponents;
	unsigned int indent;

	

public:
	stringstream tableStream;

	Table(vector<string> components, unsigned int indentacao = 0);
	Table(vector<string> components, vector<int> spacesForColumn, unsigned int indentacao = 0);
    Table(vector<vector<string>> tableVector, vector<bool> blocks, vector<int> spacesForColumn, unsigned int indentacao = 0);
	//Table(unsigned int indentacao = 0);

	void formatTable(char internalChar, char limitingChar, vector<int> spacesForColumn, unsigned int indentacaoFT = 0);
	
	vector<int> getColumsWidth() const;
	unsigned int getIndentacao() const;

    void addNewLine(vector<string> components);
	void addDataInSameLine(vector<string> components);

	void adjustColumnsSize(vector<int> spaspacesForColumn);

	friend ostream& operator<<(ostream& out, const Table &table);
	
};