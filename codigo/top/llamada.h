/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Llamadas
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#ifndef __LLAMADA_H
#define __LLAMADA_H

#include <iostream>
#include <fstream>
#include "atomic.h"

class Llamada : public Atomic {
	public:
		//Constructor
		Llamada(const string &name = "Llamada");
		~Llamada();	
		
	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//puertos de entrada
		const Port &Llamada_in;
		const Port &Lista_ll;
		const Port &Parar_ll;
		const Port &Esperar;
		const Port &Libre;

		//puertos de salida
		Port &Ocupado;
		Port &No_atiende;
		Port &Recibe_ll;

		//parametros
		Time tNoAtiende;
		
		//variables de estado
		enum Estado {Cerrado, CerradoSinRecibir, CerradoOcupado,
		             Recibiendo, Mandando, Pasivo, AbiertoSinRecibir,
		             AbiertoOcupado, CerradoConLLamada};
		Estado estado;
		int ll;
		Time t;
		
		// para debug
// 		ofstream salida;
};

#endif __LLAMADA_H
