/*******************************************************************
*
*  DESCRIPTION: Modelo Moto
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#ifndef __MOTO_H
#define __MOTO_H

#include <iostream>
#include <fstream>
#include <math.h>
#include "atomic.h"
#include "tipLlam.h"

class Moto : public Atomic {
	public:
		//Constructor
		Moto(const string &name = "Moto");
		~Moto();
		
	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

		// funciones propias
		TipLlam& obtenerDato(int idLlam);
		
	private:
		//puertos de entrada
		const Port &Carga_mi;

		//puertos de salida
		Port &Ocupada_mi;
		Port &Libre_mi;
		Port &Entrega_mi;

		//parametros
		int em;
		int cal1_del;
		int cal2_del;
		Time tCuadra;
		Time tToler;
		
		//variables de estado
		enum Estado {Vacia, Cargando, Llena,
					ViajandoIda, ViajandoVuelta};

		Estado estado;
		typedef list<TipLlam> LLamList;
		typedef list<int> DistList;
		
		LLamList entregas;
		DistList distancias;
		int carga_in;
		int carga_out;
		Time vuelta;

		// funciones propias
		int DistanciaDel(int new_e);
		int Distancia();
		void agrega(int new_e, int distancia);
		Time tiempoViaje(int distancia);
		
		//auxiliares
		Time t;
		
		// para debug
//		ofstream salida;		
};

#endif __MOTO_H
