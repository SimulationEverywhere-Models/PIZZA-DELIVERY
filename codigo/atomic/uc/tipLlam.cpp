//#include <stdio.h>
#include "tipllam.h"

// Inicializacion
TipLlam& TipLlam::CrearLlamada(int newIdLlam, int newCalle1, int newCalle2) {
		this->id = newIdLlam;
		this->cal1 = newCalle1;
		this->cal2 = newCalle2;
	
	return *this;
}

/*
TipLlam& TipLlam::CrearLlamadaS(string &texto) {
// en el string vienen los tres int separados por &
// ej: id = 3, calle1 = 5, calle2 = 8 => texto = "3&5&8"

string sTemp;
string sTemp2;
size_t  pos;
int newIdLlam;
int newCalle1;
int newCalle2;

	sTemp = texto;
	pos = sTemp.find("&", 0);					// busca delimitador "&"
	sTemp2 = (sTemp.substr(0, pos));			// obtiene id
	newIdLlam = atoi(sTemp2.c_str());
	sTemp.erase(0, pos + 1);					// saca id del texto
	pos = sTemp.find("&", 0);					// busca delimitador "&"
	sTemp2 = sTemp.substr(0, pos);				// obtiene calle1
	newCalle1 = atoi(sTemp2.c_str());
	sTemp.erase(0, pos + 1);					// saca calle1 del texto
	pos = sTemp.find("&", 0);					// busca delimitador "&"
	sTemp2 = sTemp.substr(0, pos);				// obtiene calle2
	newCalle2 = atoi(sTemp2.c_str());

	this->id = newIdLlam;
	this->cal1 = newCalle1;
	this->cal2 = newCalle2;
	
	return *this;
}
*/

// Funciones de consulta de componentes llamada;
int TipLlam::IdLlam() {
	return this->id;
}

int TipLlam::Calle1() {
	return this->cal1;
}

int TipLlam::Calle2() {
	return this->cal2;
}

/*
string TipLlam::LlamadaStr() {
// devuelve el string con los tres int separados por &
// ej: si id = 3, calle1 = 5, calle2 = 8 => "3&5&8"

string rta;
char c_num[6];

	rta = "";
	itoa(this->id, c_num, 10);
	rta = rta + c_num + "&";
	itoa(this->cal1, c_num, 10);
	rta = rta + c_num + "&";
	itoa(this->cal2, c_num, 10);
	rta = rta + c_num;

	return rta;
}
*/