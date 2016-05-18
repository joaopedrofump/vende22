# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Data {
 private:
    int dia;
    int mes;
    int ano;
    bool valid;
    bool isLeap() const;
    int numDays() const;
    bool isValid();
    
 public:
    Data(bool currentDate = false);
    Data(string data); // data na forma DD/MM/AAAA
    Data(unsigned int dia, unsigned int mes, unsigned int ano);
    int getDia() const;
    int getMes() const;
    int getAno() const;
    bool getValid() const;
    void setDia(int dia);
    void setMes(int mes);
    void setAno(int ano);
    void save(ofstream &out) const;
    friend bool operator>=(const Data &date1, const Data date2);
    friend ostream& operator<<(ostream& out, const Data & data);
    string mostrarData() const;
    void setCurrentDate();
};


