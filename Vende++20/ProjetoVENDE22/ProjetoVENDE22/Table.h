#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


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
	void formatTable(char internalChar, char limitingChar, vector<int> spacesForColumn);

public:
	stringstream tableStream;

	Table(vector<string> components);
	Table(vector<string> components, vector<int> spacesForColumn);
    Table(vector<vector<string>> tableVector, vector<bool> blocks, vector<int> spacesForColumn);

    void addNewLine(vector<string> components);
	void addDataInSameLine(vector<string> components);

	void adjustColumnsSize(vector<int> spaspacesForColumn);

	friend ostream& operator<<(ostream& out, const Table &table);
	
};