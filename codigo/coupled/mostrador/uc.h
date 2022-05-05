/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Unidad de Control
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#ifndef __UC_H
#define __UC_H

#include <iostream>
#include <fstream>
#include "atomic.h"
#include "tipLlam.h"

class UC : public Atomic {
	public:
		//Constructor
		UC(const string &name = "UC");
		~UC();
		
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
		const Port &Atiende_uc;
		const Port &Cerrar_uc;
		const Port &Abrir_uc;
		const Port &Recibe_ent_uc;
		const Port &Lleno_ent_uc;
		const Port &Lista_ent_uc;
		const Port &Moto_ocupada_uc;
		const Port &Moto_libre_uc;
		const Port &Lleno_p;
		const Port &Lista_p_uc;

		//puertos de salida
		Port &Ocupado_uc;
		Port &Libre_uc;
		Port &Ll_error_uc;
		Port &Encolar_p;
		Port &Ocupada_ent_uc;
		Port &Libre_uc_ent;
		Port &Dist_out_uc;
		Port &Lista_ll_uc;
		Port &Cerrado_uc;

		//parametros
		Time tRecepcion;
		Time tEnvio;
		
		//variables de estado
		enum Estado {Cerrado, Abriendo, Abierta,
		            Cerrando, ProcesandoMoto, Atendiendo,
					ListaEntregas, ListoPedidos, Derivando,
		            EnCocina, Error, RecibeEntrega, Entregando,
					PasivoEntrega, LlenoEntregas, LlenoPedidos,
					EnDistribuidor, CerradoConPedidos,
					CerrandoConPedidos};
		enum VF{
			V, // Verdadero
			F  // Falso
		};
		enum LO{
			L, // Libre
			O  // Ocupada
		};

		Estado estado;
		VF ab;
		TipLlam pedido;
		TipLlam entrega;
		int cant_p;
		LO moto;
		int lista;
		Time t;

		// para debug
//		ofstream salida;		
};

#endif __UC_H
