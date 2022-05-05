/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Entrega
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#ifndef __ENTREGA_H
#define __ENTREGA_H

#include <iostream>
#include <fstream>
#include "atomic.h"

class Entrega : public Atomic {
	public:
		//Constructor
		Entrega(const string &name = "Entrega");
		~Entrega();
		
	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//puertos de entrada
		const Port &Ent_in;
		const Port &Esperar_ent;
		const Port &Lista_ent;

		//puertos de salida
		Port &Ent_out;
		Port &Parar_ent;
		Port &Libre_ent;

		//parametros
		Time tEmpaq;
		int k;
		
		//variables de estado
		enum Estado {Vacia, Empaquetando, Avisando, Pasivo, Lleno, PasivoLleno};
		enum VF{
			V, // Verdadero
			F  // Falso
		};
        typedef list<int> IdLLamList;

		Estado estado;
		int p;
		VF aviso;
		IdLLamList le;

		Time t;
		
		// para debug
//		ofstream salida;		
};

#endif __ENTREGA_H
