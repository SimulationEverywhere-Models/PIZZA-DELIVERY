/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Entrega
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#include "entrega.h"
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

// public functions
// Constructor
Entrega::Entrega(const string &name) : Atomic(name),
		//puertos de entrada
		Ent_in(addInputPort("Ent_in")),
		Esperar_ent(addInputPort("Esperar_ent")),
		Lista_ent(addInputPort("Lista_ent")),
		
		//puertos de salida
		Ent_out(addOutputPort("Ent_out")),
		Parar_ent(addOutputPort("Parar_ent")),
		Libre_ent(addOutputPort("Libre_ent"))
{
}

// Inicializacion
Model &Entrega::initFunction(){

	//carga variables estado
	this->estado = Vacia;
	this->p = 0;
	this->aviso = F;
	this->le.erase(le.begin(), le.end());

	//carga parametros
	string time( MainSimulator::Instance().getParameter( description(), "TE" ) ) ;
	if( time != "" )
		this->tEmpaq = time;
	int vK = str2Int(MainSimulator::Instance().getParameter( description(), "K" ));
	this->k = vK;

	passivate();
	
// debug
//	this->salida.open(MainSimulator::Instance().getParameter(description(), "archivo").c_str(), ios::in);
//	salida << "tEmpaq " << tEmpaq << endl;
//	salida << "k " << k << endl;
// debug
	
	return *this;
}

// Funcion de transicion externa
Model &Entrega::externalFunction( const ExternalMessage &msg ) {
	
// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Vacia:
			if (msg.port() == Ent_in) {
				this->t = msg.time() + tEmpaq;
				le.push_back(msg.value());
				if (this->p + 1 < k) {
					this->p = this->p + 1;
					this->estado = Empaquetando;
					holdIn(active, this->tEmpaq);
				} else {
					this->p = this->p + 1;
					this->estado = Lleno;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Ent_in" << endl;
//	salida << "P " << this->p << endl;
//	salida << "T " << this->t << endl;
// debug
			}
			if (msg.port() == Esperar_ent) {
				this->estado = Pasivo;
				passivate();
// debug	
//	salida << msg.time() << " port Esperar_ent" << endl;
// debug
			}
			break;
		case Empaquetando:
			if (msg.port() == Ent_in) {
				le.push_back(msg.value());
				if (this->p + 1 < k) {
					this->p = this->p + 1;
					this->estado = Empaquetando;
					holdIn(active, this->t - msg.time());
				} else {
					this->p = this->p + 1;
					this->estado = Lleno;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Ent_in" << endl;
//	salida << "P " << this->p << endl;
// debug
			}
			if (msg.port() == Esperar_ent) {
				this->estado = Pasivo;
				passivate();
// debug	
//	salida << msg.time() << " port Esperar_ent" << endl;
// debug
			}
			break;
		case Pasivo:
			if (msg.port() == Ent_in) {
				le.push_back(msg.value());
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
//	salida << msg.time() << " port Ent_in" << endl;
//	salida << "P " << this->p << endl;
// debug
			}
			if (msg.port() == Lista_ent) {
				if (this->p == 0)
				{
					this->estado = Vacia;
					passivate();
				} else {
					this->estado = Empaquetando;
					if ((this->t - msg.time()) < 0)
						holdIn(active, 0);
					else
						holdIn(active, this->t - msg.time());
				}
// debug	
//	salida << msg.time() << " port Libre_m_ent" << endl;
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
Model &Entrega::internalFunction( const InternalMessage &msg ){

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Empaquetando:
			le.pop_front();
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
					this->estado = Empaquetando;
					holdIn(active, tEmpaq);
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
				this->estado = Empaquetando;
				holdIn(active, tEmpaq);
			}
// debug	
//	salida << "P " << this->p << endl;
//	salida << "T " << this->t << endl;
// debug
			break;			
		case Lleno:
			this->aviso = V;
			this->estado = Empaquetando;
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
Model &Entrega::outputFunction( const InternalMessage &msg ) {

// debug	
//	salida << msg.time() << " estado OF " << this->estado << endl;
// debug

	switch (this->estado) {
		case Avisando:
			sendOutput(msg.time(), Libre_ent, 1);
			break;
		case Empaquetando:
			sendOutput(msg.time(), Ent_out, this->le.front());
			break;
		case Lleno:
			sendOutput(msg.time(), Parar_ent, 1);
			break;
		case PasivoLleno:
			sendOutput(msg.time(), Parar_ent, 1);
			break;
		default:
			break;
	}
	
	return *this;
}

Entrega::~Entrega()
{
	//debug
//	this->salida.close();
	//debug
}