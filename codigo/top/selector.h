/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Selector
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#ifndef __SELECTOR_H
#define __SELECTOR_H

#include <iostream>
#include <fstream>
#include "atomic.h"

class Selector : public Atomic {
	public:
		//Constructor
		Selector(const string &name = "Selector");
		~Selector();	
		
	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//puertos de entrada
		const Port &Carga_in;
		const Port &Lista_m1;
		const Port &Lista_m2;
		const Port &Lista_m3;
		const Port &Lista_m4;
		const Port &Esperar_m1;
		const Port &Esperar_m2;
		const Port &Esperar_m3;
		const Port &Esperar_m4;

		//puertos de salida
		Port &Moto_ocupada;
		Port &Moto_libre;
		Port &Sel_out1;
		Port &Sel_out2;
		Port &Sel_out3;
		Port &Sel_out4;

		//variables de estado
		enum Estado {Pasivo, EntregandoM1, EntregandoM2,
					EntregandoM3, EntregandoM4, PasivoM1,
					PasivoM1M2, PasivoM1M2M3, SinMotos,
					ConMotos};
		enum LO{
			L, // Libre
			O  // Ocupada
		};
		enum VF{
			V, // Verdadero
			F  // Falso
		};
					
		Estado estado;
		int entrega;
		LO m1;
		LO m2;
		LO m3;
		LO m4;
		VF aviso;
		VF carga;
		
		// para debug
//		ofstream salida;
};

#endif __SELECTOR_H
