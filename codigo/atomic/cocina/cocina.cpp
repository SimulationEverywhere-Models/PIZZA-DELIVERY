/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Cocina
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#include <stdlib.h>		// rnd
#include <time.h>		// rnd
#include "cocina.h"
#include "message.h"    // InternalMessage ....
#include "mainsimu.h"   // class MainSimulator
#include "strutil.h"    // str2float( ... )

// public functions
// Constructor
Cocina::Cocina(const string &name) : Atomic(name),
		//puertos de entrada
		Recibe_pedido(addInputPort("Recibe_pedido")),
		
		//puertos de salida
		Ocupada_c(addOutputPort("Ocupada_c")),
		Lista_c(addOutputPort("Lista_c")),
		Sale_pedido(addOutputPort("Sale_pedido"))
{
}

// Inicializacion
Model &Cocina::initFunction(){

	//carga variables estado
	this->estado = Vacia;
	this->p = 0;
	this->aviso = F;
	this->pedidos.erase(pedidos.begin(), pedidos.end());
	this->tcoc.erase(tcoc.begin(), tcoc.end());

	//carga parametros
	int v_pm = str2Int(MainSimulator::Instance().getParameter( description(), "PM" ));
	this->pm = v_pm;
	int v_min = str2Int(MainSimulator::Instance().getParameter( description(), "COC_MIN" ));
	this->coc_min = v_min;
	int v_max = str2Int(MainSimulator::Instance().getParameter( description(), "COC_MAX" ));
	this->coc_max = v_max;

	passivate();
	
// debug
//  this->salida.open(MainSimulator::Instance().getParameter(description(), "archivo").c_str(), ios::in);
//  salida << "pm " << v_pm << endl;
//  salida << "coc_min " << v_min << endl;
//  salida << "coc_max " << v_max << endl;
// debug
	
	return *this;
}

// Funcion de transicion externa
Model &Cocina::externalFunction( const ExternalMessage &msg ) {

Time tc;

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Vacia:
			tc = tiempoCoccion();
			agrega(msg.value(), msg.time() + tc);					
			if (this->p + 1 < this->pm) {
				this->p = this->p + 1;
				this->estado = Cocinando;
				holdIn(active, this->tcoc.front() - msg.time());
			} else {
				this->p = this->p + 1;
				this->estado = Llena;
				holdIn(active, 0);
			}
// debug	
//	salida << "P " << this->p << endl;
//	salida << "tc " << tc << endl;
//	salida << "tiempo salida " << msg.time() + tc << endl;
//	salida << "tc del primero " << this->tcoc.front() << endl;
// debug
			break;
		case Cocinando:
			tc = tiempoCoccion();
			agrega(msg.value(), msg.time() + tc);					
			if (this->p + 1 < this->pm) {
				this->p = this->p + 1;
				this->estado = Cocinando;
				holdIn(active, this->tcoc.front() - msg.time());
			} else {
				this->p = this->p + 1;
				this->estado = Llena;
				holdIn(active, 0);
			}
// debug	
//	salida << "P " << this->p << endl;
//	salida << "tc " << tc << endl;
//	salida << "tiempo salida " << msg.time() + tc << endl;
//	salida << "tc del primero " << this->tcoc.front() << endl;
// debug
			break;
		default:
			break;
		}

// debug	
//	salida << msg.time() << " estado F " << this->estado << endl;
// debug
		
	return *this;	
}

// Funcion de transicion interna
Model &Cocina::internalFunction( const InternalMessage &msg ){

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Cocinando:
			this->pedidos.pop_front();
			this->tcoc.pop_front();
			if (this->aviso == V)
			{
				this->p = this->p - 1;
				this->estado = Avisando;
				holdIn(active, 0);
			} else {
				if (this->p == 1)
				{
					this->p = this->p - 1;
					this->estado = Vacia;
					passivate();
				} else {
					this->p = this->p - 1;
					this->estado = Cocinando;
					holdIn(active, this->tcoc.front() - msg.time());
				}
			}
// debug	
//	salida << "P " << this->p << endl;
//	salida << "tc del primero " << this->tcoc.front() << endl;
// debug
			break;
		case Avisando:
			this->aviso = F;
			if (this-> p==0)
			{
				this->estado = Vacia;
				passivate();
			} else {
				this->estado = Cocinando;
				holdIn(active, this->tcoc.front() - msg.time());
			}
// debug	
//	salida << "aviso " << this->aviso << endl;
// debug
			break;			
		case Llena:
			this->aviso = V;
			this->estado = Cocinando;
			holdIn(active, this->tcoc.front() - msg.time());
// debug	
//	salida << "aviso " << this->aviso << endl;
//	salida << "tc del primero " << this->tcoc.front() << endl;
// debug
			break;
		default:
			break;
	}
	
// debug	
//	salida << msg.time() << " estado F " << this->estado << endl;
// debug
	
	return *this;
}

// Funcion de salida
Model &Cocina::outputFunction( const InternalMessage &msg ) {

// debug	
//	salida << msg.time() << " estado OF " << this->estado << endl;
// debug

	switch (this->estado) {
		case Avisando:
			sendOutput(msg.time(), Lista_c, 1);
			break;
		case Cocinando:
			sendOutput(msg.time(), Sale_pedido, this->pedidos.front());
			break;
		case Llena:
			sendOutput(msg.time(), Ocupada_c, 1);
			break;
		default:
			break;
	}
	
	return *this;
}

Cocina::~Cocina()
{
	//debug
//	this->salida.close();
	//debug
}

Time Cocina::tiempoCoccion() {
// valor al azar entre el min y maxi pasados
// por parametro

int min;
int max;
Time t_cte;
Time rta;
int valor_rnd;
	
	min = this->coc_min;
	max = this->coc_max;
	t_cte = Time(0, 0, 1, 0);

//	srand( time(NULL) ); 
//	srand(random()); 

	valor_rnd = rand() % (max - min + 1) + min;

	// hay multiplicacion de time?
	// suma valor_rnd veces el tiempo basico
	for( int i = 0; i < valor_rnd + 1; i++ ) {
		rta = rta + t_cte;
	}
	return rta;
}

void Cocina::agrega(int new_p, Time t_coc) {

IdLLamList pi;
IdLLamList pf;
TimeList tci;
TimeList tcf;
int i;
int fin;

	fin = 0;

	if ( this->tcoc.back() <= t_coc ){
		// va al final
		this->pedidos.push_back(new_p);
		this->tcoc.push_back(t_coc);

	} else {
		// inserta ordenado, de menor a mayor tcoc
		// para = tcoc, ubica ultimo al nuevo

		//inicia
		pi.erase(pi.begin(), pi.end());
		tci.erase(tci.begin(), tci.end());
		pf.erase(pf.begin(), pf.end());
		tcf.erase(tcf.begin(), tcf.end());

		pf.assign (this->pedidos.begin(),this->pedidos.end());
		tcf.assign (this->tcoc.begin(),this->tcoc.end());
 
		while (!pf.empty() && fin==0) {
			if (tcf.front() > t_coc) {
				// posicion donde va el nuevo
				fin = 1;
			} else {
				pi.push_back(pf.front());
				tci.push_back(tcf.front());
				pf.pop_front();
				tcf.pop_front();
			}
		}

		// borra elementos
 		this->pedidos.erase(this->pedidos.begin(), this->pedidos.end());
		this->tcoc.erase(this->tcoc.begin(), this->tcoc.end());

		// agrego primeros
		this->pedidos.assign(pi.begin(),pi.end());
		this->tcoc.assign(tci.begin(),tci.end());

		// agrego actual
		this->pedidos.push_back(new_p);
		this->tcoc.push_back(t_coc);

		// agrego ultimos
		while (!pf.empty()) {
			this->pedidos.push_back(pf.front());
			this->tcoc.push_back(tcf.front());
			pf.pop_front();
			tcf.pop_front();
		}
	}

// debug	
//	i = 0;
//	tcf.assign (this->tcoc.begin(),this->tcoc.end());
//	while (!tcf.empty()) {
//	salida << " tcoc " << i << " " << tcf.front() << endl;
//	tcf.pop_front();
//	i = i +1;
//	}
// debug

}