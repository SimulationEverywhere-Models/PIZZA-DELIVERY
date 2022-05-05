/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Cocina
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#ifndef __COCINA_H
#define __COCINA_H

#include <iostream>
#include <fstream>
#include "atomic.h"

class Cocina : public Atomic {
	public:
		//Constructor
		Cocina(const string &name = "Cocina");
		~Cocina();
		
	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//puertos de entrada
		const Port &Recibe_pedido;

		//puertos de salida
		Port &Ocupada_c;
		Port &Lista_c;
		Port &Sale_pedido;

		//parametros
		int pm;
		int coc_min;
		int coc_max;
		
		//variables de estado
		enum Estado {Vacia, Cocinando, Avisando, Llena};
		enum VF{
			V, // Verdadero
			F  // Falso
		};
        typedef list<int> IdLLamList;
		typedef list<Time> TimeList;

		Estado estado;
		int p;
		VF aviso;
		IdLLamList pedidos;
		TimeList tcoc;

		// funciones propias
		Time tiempoCoccion();
		void agrega(int new_p, Time t_coc);

		// para debug
//		ofstream salida;		
};

#endif __COCINA_H
