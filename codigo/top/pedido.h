/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Pedido
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#ifndef __PEDIDO_H
#define __PEDIDO_H

#include <iostream>
#include <fstream>
#include "atomic.h"

class Pedido : public Atomic {
	public:
		//Constructor
		Pedido(const string &name = "Pedido");
		~Pedido();
		
	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//puertos de entrada
		const Port &Pedido_in;
		const Port &Esperar_p;
		const Port &Listo_p;

		//puertos de salida
		Port &Pedido_out;
		Port &Parar_p;
		Port &Libre_p;

		//parametros
		Time tEnvio;
		int k;
		
		//variables de estado
		enum Estado {Vacia, Entregando, Avisando, Pasivo, Lleno, PasivoLleno};
		enum VF{
			V, // Verdadero
			F  // Falso
		};
        typedef list<int> IdLLamList;

		Estado estado;
		int p;
		VF aviso;
		IdLLamList lp;

		Time t;
		
		// para debug
		ofstream salida;		
};

#endif __PEDIDO_H
