#ifndef __TIPLLAM_H
#define __TIPLLAM_H

#include <string>
using namespace std;

class TipLlam{
	public:
		//Constructor
		TipLlam& CrearLlamada(int newId, int newCalle1, int newCalle2);
//		TipLlam& CrearLlamadaS(string &texto);

		//Funciones consulta
		int IdLlam();
		int Calle1();
		int Calle2();
//		string LlamadaStr();

	private:
		int id;
		int cal1;
		int cal2;		
};

#endif __TIPLLAM_H
