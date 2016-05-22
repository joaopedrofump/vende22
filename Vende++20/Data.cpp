/*

T7G02
João Pinheiro
Leonardo Teixeira

*/


#include "Data.h"
#include <string>
#include <fstream>
#include <ctime>

//teste branch

// data na forma DD/MM/AAA

Data::Data(bool currentDate) {

	if (currentDate) {

#ifdef __llvm__

		time_t t = time(NULL);
		tm* timePtr = localtime(&t);

		this->dia = timePtr->tm_mday;
		this->mes = (timePtr->tm_mon) + 1;
		this->ano = timePtr->tm_year + 1900;
		this->valid = this->isValid();

#elif _MSC_VER

		time_t t = time(NULL);
		struct tm timeInfo;
		localtime_s(&timeInfo, &t);

		this->dia = timeInfo.tm_mday;
		this->mes = (timeInfo.tm_mon) + 1;
		this->ano = timeInfo.tm_year + 1900;
		this->valid = this->isValid();

#endif

	}

	else {

		this->dia = 0;
		this->mes = 0;
		this->ano = 0;
		this->valid = this->isValid();


	}

}


Data::Data(string dataStr) {

	stringstream dataStream(dataStr);
	char separator1;
	char separator2;

	dataStream >> this->dia;
	dataStream >> separator1;
	dataStream >> this->mes;
	dataStream >> separator2;
	dataStream >> this->ano;

	if (separator1 != '/' || separator2 != '/') {

		valid = false;

	}

	else {

		this->valid = isValid();

	}


}

Data::Data(unsigned int dia, unsigned int mes, unsigned int ano) {

	this->dia = dia;
	this->mes = mes;
	this->ano = ano;

	this->valid = isValid();

}

int Data::getDia() const {
	return dia;
}

int Data::getMes() const {
	return mes;
}

int Data::getAno() const {
	return ano;
}

void Data::setDia(int dia) {

	this->dia = dia;

}

void Data::setMes(int mes) {
	this->mes = mes;
}

void Data::setAno(int ano) {
	this->ano = ano;
}

bool Data::isLeap() const {

	if (this->ano % 400 == 0) {
		return true;
	}

	else {

		if (this->ano % 4 == 0 && this->ano % 100 != 0) {
			return true;
		}

		else {
			return false;
		}
	}
}

int Data::numDays() const {

	switch (this->mes) {
	case 4: case 6: case 9: case 11:
		return 30;
		break;
	case 2:
		if (this->isLeap()) {
			return 29;
		}
		else {
			return 28;

		}
		break;
	default:
		return 31;
		break;
	}
}

bool Data::isValid() {

	if (this->ano < 1900) {
		return false;
	}

	if (this->mes == 0 || this->mes > 12) {

		return false;
	}

	if ((this->dia == 0) || (this->dia  > numDays())) {

		return false;
	}

	return true;


}

bool operator>=(const Data &date1, const Data date2) {

	if (date1.getAno() < date2.getAno()) {

		return false;

	}

	else if (date1.getAno() > date2.getAno()) {

		return true;
	}

	else {


		if (date1.getMes() < date2.getMes()) {

			return false;

		}

		else if (date1.getMes() > date2.getMes()) {

			return true;
		}

		else {


			if (date1.getDia() < date2.getDia()) {

				return false;

			}

			else if (date1.getDia() > date2.getDia()) {

				return true;
			}

			else {


				return true;

			}

		}

	}

}


void Data::save(ofstream &out) const {

	out << this;

}

bool Data::getValid() const {

	return this->valid;

}

ostream& operator<<(ostream& out, const Data &data) {

	if (data.getValid()) {
		out << data.getDia() << "/" << data.getMes() << "/" << data.getAno();
	}

	else {

		out << "Data Inválida";

	}

	return out;
}

string Data::mostrarData() const {

	string finalDate = "";

	if (this->dia < 10) {

		finalDate += '0';
		finalDate.append(to_string(this->dia));
	}

	else {

		finalDate.append(to_string(this->dia));
	}

	finalDate += '/';

	if (this->mes < 10) {

		finalDate += '0';
		finalDate.append(to_string(this->mes));

	}
	else {

		finalDate.append(to_string(this->mes));

	}

	finalDate += '/';

	if (this->ano == 0) {

		finalDate.append("0000");

	}
	else {

		finalDate.append(to_string(this->ano));
	}

	return finalDate;

}

void Data::setCurrentDate() {

#ifdef __llvm__

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);

	this->dia = timePtr->tm_mday;
	this->mes = (timePtr->tm_mon) + 1;
	this->ano = timePtr->tm_year + 1900;

#elif _MSC_VER

	time_t t = time(NULL);
	struct tm timeInfo;
	localtime_s(&timeInfo, &t);

	this->dia = timeInfo.tm_mday;
	this->mes = (timeInfo.tm_mon) + 1;
	this->ano = timeInfo.tm_year + 1900;

#endif

}
