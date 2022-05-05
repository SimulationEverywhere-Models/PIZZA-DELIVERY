/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Llamadas
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#include "llamada.h"
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

// public functions
// Constructor
Llamada::Llamada(const string &name) : Atomic(name),
		//puertos de entrada
		Llamada_in(addInputPort("Llamada_in")),
		Lista_ll(addInputPort("Lista_ll")),
		Parar_ll(addInputPort("Parar_ll")),
		Esperar(addInputPort("Esperar")),
		Libre(addInputPort("Libre")),
		
		//puertos de salida
		Ocupado(addOutputPort("Ocupado")),
		No_atiende(addOutputPort("No_atiende")),
		Recibe_ll(addOutputPort("Recibe_ll"))
{
}

// Inicializacion
Model &Llamada::initFunction(){

	//carga variables estado
	this->estado = Cerrado;
	//Creo la llamada vacia (id, calle1, calle2)
	//this->ll.CrearLlamada(0, 0, 0);
	this->ll = 0;

	//carga parametros
	string time( MainSimulator::Instance().getParameter( description(), "TNA" ) ) ;
	if( time != "" )
		this->tNoAtiende = time ;

	passivate();

// debug
//	this->salida.open(MainSimulator::Instance().getParameter(description(), "archivo").c_str(), ios::in);
//	salida << "tNoAtiende " << tNoAtiende << endl;
// debug
	
	return *this;
}

// Funcion de transicion externa
Model &Llamada::externalFunction( const ExternalMessage &msg ) {
	
// debug	
//	salida << "estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case AbiertoSinRecibir:
			if (msg.port() == Llamada_in) {
// debug	
//	salida << "port Llamada_in" << endl;
// debug
					this->estado = AbiertoOcupado;
			}
			if (msg.port() == Libre) {
// debug	
//	salida << "port libre" << endl;
// debug					
					this->estado = Mandando;
			}
			if (msg.port() == Parar_ll) {
// debug	
//	salida << "port parar_ll" << endl;
// debug			
					this->estado = CerradoConLLamada;
			}			
			holdIn(active, 0);
			break;
		case Cerrado:
			if (msg.port() == Llamada_in) {
// debug	
//	salida << "port llamada_in" << endl;
// debug
				this->ll = msg.value();
				this->t = msg.time() + tNoAtiende;
				this->estado = CerradoSinRecibir;
				holdIn(active, this->tNoAtiende);
			}
			if (msg.port() == Lista_ll) {
// debug	
//	salida << "port lista_ll" << endl;
// debug				
				    this->estado = Recibiendo;
					passivate();
			}
			break;
		case CerradoSinRecibir:
			if (msg.port() == Llamada_in) {
// debug	
//	salida << "port llamada_in" << endl;
// debug					
				this->ll = msg.value();
				this->estado = CerradoOcupado;
				holdIn(active, 0);
			}		
			if (msg.port() == Lista_ll) {
// debug	
//	salida << "port Lista_ll" << endl;
// debug				
				this->estado = Mandando;
				holdIn(active, 0);
			}
			break;
		case Pasivo:
			if (msg.port() == Llamada_in) {
// debug	
//	salida << "port llamada_in" << endl;
// debug				
				this->ll = msg.value();
				this->t = msg.time() + tNoAtiende;
				this->estado = AbiertoSinRecibir;
				holdIn(active, this->tNoAtiende);
			}		
			if (msg.port() == Libre) {
// debug	
//	salida << "port Libre" << endl;
// debug
				    this->estado = Recibiendo;
					passivate();
			}
			if (msg.port() == Parar_ll) {
// debug	
//	salida << "port Parar_ll" << endl;
// debug
					this->estado = Cerrado;
					passivate();
			}
			break;
		case Recibiendo:
			if (msg.port() == Esperar) {
// debug	
//	salida << "port Esperar" << endl;
// debug
					this->estado = Pasivo;
					passivate();
			}
			if (msg.port() == Llamada_in) {
// debug	
//	salida << "port Llamada_in" << endl;
// debug				
				this->ll = msg.value();
				this->estado = Mandando;
				holdIn(active, 0);
			}
			if (msg.port() == Parar_ll) {
// debug	
//	salida << "port Parar_ll" << endl;
// debug
					this->estado = Cerrado;
					passivate();
			}
			break;
		default:
			break;
		}
		
// debug	
//	salida << "estado F " << this->estado << endl;
// debug

	return *this;	
}

// Funcion de transicion interna
Model &Llamada::internalFunction( const InternalMessage &msg ){

// debug	
//	salida << "estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case AbiertoOcupado:
			this->estado = AbiertoSinRecibir;
			holdIn(active, this->t - msg.time());
			break;
		case AbiertoSinRecibir:
			this->estado = Pasivo;
			passivate();
			break;
		case CerradoConLLamada:
			this->estado = Cerrado;
			passivate();
			break;			
		case CerradoOcupado:
			this->estado = CerradoSinRecibir;
			holdIn(active, this->t - msg.time());
			break;
		case CerradoSinRecibir:
			this->estado = Cerrado;
			passivate();
			break;
		case Mandando:
			this->estado = Recibiendo;
			passivate();
			break;			
		default:
			break;
	}

// debug	
//	salida << "estado F " << this->estado << endl;
// debug

	return *this;
}

// Funcion de salida
Model &Llamada::outputFunction( const InternalMessage &msg ) {

// debug	
//	salida << "estado OF " << this->estado << endl;
// debug

	switch (this->estado) {
		case AbiertoSinRecibir:
			sendOutput(msg.time(), No_atiende, 1);
			break;
		case CerradoConLLamada:
			sendOutput(msg.time(), No_atiende, 1);
			break;
		case CerradoSinRecibir:
			sendOutput(msg.time(), No_atiende, 1);
			break;
		case AbiertoOcupado:
			sendOutput(msg.time(), Ocupado, 1);
			break;
		case CerradoOcupado:
			sendOutput(msg.time(), Ocupado, 1);
			break;
		case Mandando:
			sendOutput(msg.time(), Recibe_ll, this->ll);
			break;
		default:
			break;
	}
	return *this;
}
		
Llamada::~Llamada()
{
	//debug
//	this->salida.close();
	//debug
}