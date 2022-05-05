/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Pedido
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#include "pedido.h"
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

// public functions
// Constructor
Pedido::Pedido(const string &name) : Atomic(name),
		//puertos de entrada
		Pedido_in(addInputPort("Pedido_in")),
		Esperar_p(addInputPort("Esperar_p")),
		Listo_p(addInputPort("Listo_p")),
		
		//puertos de salida
		Pedido_out(addOutputPort("Pedido_out")),
		Parar_p(addOutputPort("Parar_p")),
		Libre_p(addOutputPort("Libre_p"))
{
}

// Inicializacion
Model &Pedido::initFunction(){

	//carga variables estado
	this->estado = Vacia;
	this->p = 0;
	this->aviso = F;
	this->lp.erase(lp.begin(), lp.end());

	//carga parametros
	string time( MainSimulator::Instance().getParameter( description(), "TE" ) ) ;
	if( time != "" )
		this->tEnvio = time;
	int vK = str2Int(MainSimulator::Instance().getParameter( description(), "K" ));
	this->k = vK;

	passivate();
	
// debug
//	this->salida.open(MainSimulator::Instance().getParameter(description(), "archivo").c_str(), ios::in);
//	salida << "tEnvio " << tEnvio << endl;
//	salida << "k " << k << endl;
// debug
	
	return *this;
}

// Funcion de transicion externa
Model &Pedido::externalFunction( const ExternalMessage &msg ) {
	
// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Vacia:
			if (msg.port() == Pedido_in) {
				this->t = msg.time() + tEnvio;
				lp.push_back(msg.value());
				if (this->p + 1 < k) {
					this->p = this->p + 1;
					this->estado = Entregando;
					holdIn(active, this->tEnvio);
				} else {
					this->p = this->p + 1;
					this->estado = Lleno;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Pedido_in" << endl;
//	salida << "P " << this->p << endl;
//	salida << "T " << this->t << endl;
// debug
			}
			if (msg.port() == Esperar_p) {
				this->estado = Pasivo;
				passivate();
// debug	
//	salida << msg.time() << " port Esperar_p" << endl;
// debug
			}
			break;
		case Entregando:
			if (msg.port() == Pedido_in) {
				lp.push_back(msg.value());
				if (this->p + 1 < k) {
					this->p = this->p + 1;
					this->estado = Entregando;
					holdIn(active, this->t - msg.time());
				} else {
					this->p = this->p + 1;
					this->estado = Lleno;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Pedido_in" << endl;
//	salida << "P " << this->p << endl;
// debug
			}
			if (msg.port() == Esperar_p) {
				this->estado = Pasivo;
				passivate();
// debug	
//	salida << msg.time() << " port Esperar_p" << endl;
// debug
			}
			break;
		case Pasivo:
			if (msg.port() == Pedido_in) {
				lp.push_back(msg.value());
				if (this->p + 1 < k) {
					this->p = this->p + 1;
					this->estado = Pasivo;
					passivate();			
				} else {
					this->p = this->p + 1;
					this->estado = PasivoLleno;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Pedido_in" << endl;
//	salida << "P " << this->p << endl;
// debug
			}
			if (msg.port() == Listo_p) {
				if (this->p == 0)
				{
					this->estado = Vacia;
					passivate();
				} else {
					this->estado = Entregando;
					if ((this->t - msg.time()) < 0)
						holdIn(active, 0);
					else
						holdIn(active, this->t - msg.time());
				}
// debug	
//	salida << msg.time() << " port Listo_p" << endl;
// debug
			}			
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
Model &Pedido::internalFunction( const InternalMessage &msg ){

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Entregando:
			lp.pop_front();
			if (this->aviso == V)
			{
				this->estado = Avisando;
					this->p = this->p - 1;
					holdIn(active, 0);
			} else {
				if (this->p == 1)
				{
					this->p = this->p - 1;
					this->estado = Vacia;
					passivate();
				} else {
					this->p = this->p - 1;
					this->estado = Entregando;
					holdIn(active, tEnvio);
				}
			}
// debug	
//	salida << "P " << this->p << endl;
// debug
			break;
		case Avisando:
			this->aviso = F;
			if (this-> p==0)
			{
				this->estado = Vacia;
				passivate();
			} else {
				this->estado = Entregando;
				holdIn(active, tEnvio);
			}
// debug	
//	salida << "P " << this->p << endl;
//	salida << "T " << this->t << endl;
// debug
			break;			
		case Lleno:
			this->aviso = V;
			this->estado = Entregando;
			if ((this->t - msg.time()) < 0)
				holdIn(active, 0);
			else
				holdIn(active, this->t - msg.time());
// debug	
//	salida << "aviso " << this->aviso << endl;
// debug
			break;
		case PasivoLleno:
			this->aviso = V;
			this->estado = Pasivo;
			passivate();
			break;			
// debug	
//	salida << "aviso " << this->aviso << endl;
// debug
		default:
			break;
	}
	
// debug	
//	salida << msg.time() << " estado F " << this->estado << endl;
// debug
	
	return *this;
}

// Funcion de salida
Model &Pedido::outputFunction( const InternalMessage &msg ) {

// debug	
//	salida << msg.time() << " estado OF " << this->estado << endl;
// debug

	switch (this->estado) {
		case Avisando:
			sendOutput(msg.time(), Libre_p, 1);
			break;
		case Entregando:
			sendOutput(msg.time(), Pedido_out, this->lp.front());
			break;
		case Lleno:
			sendOutput(msg.time(), Parar_p, 1);
			break;
		case PasivoLleno:
			sendOutput(msg.time(), Parar_p, 1);
			break;
		default:
			break;
	}
	
	return *this;
}

Pedido::~Pedido()
{
//debug
//	this->salida.close();
//debug
}