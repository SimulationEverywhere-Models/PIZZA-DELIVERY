/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Selector
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#include "selector.h"
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

// public functions
// Constructor
Selector::Selector(const string &name) : Atomic(name),
		//puertos de entrada
		Carga_in(addInputPort("Carga_in")),
		Lista_m1(addInputPort("Lista_m1")),
		Lista_m2(addInputPort("Lista_m2")),
		Lista_m3(addInputPort("Lista_m3")),
		Lista_m4(addInputPort("Lista_m4")),
		Esperar_m1(addInputPort("Esperar_m1")),
		Esperar_m2(addInputPort("Esperar_m2")),
		Esperar_m3(addInputPort("Esperar_m3")),
		Esperar_m4(addInputPort("Esperar_m4")),
		
		//puertos de salida
		Moto_ocupada(addOutputPort("Moto_ocupada")),
		Moto_libre(addOutputPort("Moto_libre")),
		Sel_out1(addOutputPort("Sel_out1")),
		Sel_out2(addOutputPort("Sel_out2")),
		Sel_out3(addOutputPort("Sel_out3")),
		Sel_out4(addOutputPort("Sel_out4"))
{
}

// Inicializacion
Model &Selector::initFunction(){

	//carga variables estado
	this->estado = Pasivo;
	//Creo la llamada vacia (id, calle1, calle2)
	//this->entrega.CrearLlamada(0, 0, 0);
	this->entrega = 0;
	this->m1 = L;
	this->m2 = L;
	this->m3 = L;
	this->m4 = L;
	this->aviso = F;
	this->carga = F;
	
	passivate();

// debug
//	this->salida.open(MainSimulator::Instance().getParameter(description(), "archivo").c_str(), ios::in);
// debug
	
	return *this;
}

// Funcion de transicion externa
Model &Selector::externalFunction( const ExternalMessage &msg ) {
	
// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Pasivo:
			if (msg.port() == Carga_in) {
				this->entrega = msg.value();
				if (this->m1 == L) {
					this->estado = EntregandoM1;
				} else {
					if (this->m2 == L) {
						this->estado = EntregandoM2;
					} else {
						if (this->m3 == L)
							this->estado = EntregandoM3;
						else
							this->estado = EntregandoM4;
					}
				}
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Carga_in" << endl;
// debug
			}
			if (msg.port() == Lista_m1) {
				this->m1 = L;
				if ( this->aviso = F) {
					this->estado = Pasivo;
					passivate();
				} else {
					this->estado = ConMotos;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Lista_m1" << endl;
// debug
			}
			if (msg.port() == Lista_m2) {
				this->m2 = L;
				if ( this->aviso == F) {
					this->estado = Pasivo;
					passivate();
				} else {
					this->estado = ConMotos;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Lista_m2" << endl;
// debug
			}
			if (msg.port() == Lista_m3) {
				this->m3 = L;
				if ( this->aviso == F) {
					this->estado = Pasivo;
					passivate();
				} else {
					this->estado = ConMotos;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Lista_m3" << endl;
// debug
			}
			if (msg.port() == Lista_m4) {
				this->m4 = L;
				if ( this->aviso == F) {
					this->estado = Pasivo;
					passivate();
				} else {
					this->estado = ConMotos;
					holdIn(active, 0);
				}
// debug	
//	salida << msg.time() << " port Lista_m4" << endl;
// debug
			}
			if (msg.port() == Esperar_m1) {
				this->m1 = O;
				if (this->m2 == L) {
					this->estado = PasivoM1;
					passivate();
				} else {
					if (this->m3 == L){
						this->estado = PasivoM1M2;
						passivate();
					} else {
						if (this->m4 == L){
							this->estado = PasivoM1M2M3;
							passivate();
						} else {
							this->estado = SinMotos;
							holdIn(active, 0);;
						}
					}
				}		
// debug	
//	salida << msg.time() << " port Esperar_m1" << endl;
// debug
			}			
			if (msg.port() == Esperar_m2) {
				this->m2 = O;
// debug	
//	salida << msg.time() << " port Esperar_m2" << endl;
// debug
			}			
			if (msg.port() == Esperar_m3) {
				this->m3 = O;
// debug	
//	salida << msg.time() << " port Esperar_m3" << endl;
// debug
			}			
			if (msg.port() == Esperar_m4) {
				this->m4 = O;
// debug	
//	salida << msg.time() << " port Esperar_m4" << endl;
// debug
			}			
			break;
		case PasivoM1:
			if (msg.port() == Carga_in) {
				this->carga = V;
				this->entrega = msg.value();
				this->estado = EntregandoM2;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Carga_in" << endl;
// debug
			}
			if (msg.port() == Lista_m1) {
				this->m1 = L;
				if (this->carga == F)
					this->estado = Pasivo;
				else
					this->estado = PasivoM1;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m1" << endl;
// debug
			}
			if (msg.port() == Lista_m3) {
				this->m3 = L;
				this->estado = PasivoM1;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m3" << endl;
// debug
			}
			if (msg.port() == Lista_m4) {
				this->m4 = L;
				this->estado = PasivoM1;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m4" << endl;
// debug
			}
			if (msg.port() == Esperar_m1) {
				this->m1 = O;
// debug	
//	salida << msg.time() << " port Esperar_m1" << endl;
// debug
			}			
			if (msg.port() == Esperar_m2) {
				this->m2 = O;
				this->carga = F;
				if (this->m1 == L) {
					this->estado = Pasivo;
					passivate();
				} else {
					if (this->m3 == L){
						this->estado = PasivoM1M2;
						passivate();
					} else {
						if (this->m4 == L){
							this->estado = PasivoM1M2M3;
							passivate();
						} else {
							this->estado = SinMotos;
							holdIn(active, 0);;
						}
					}
				}		
// debug	
//	salida << msg.time() << " port Esperar_m2" << endl;
// debug
			}			
			if (msg.port() == Esperar_m3) {
				this->m3 = O;
// debug	
//	salida << msg.time() << " port Esperar_m3" << endl;
// debug
			}			
			if (msg.port() == Esperar_m4) {
				this->m4 = O;
// debug	
//	salida << msg.time() << " port Esperar_m4" << endl;
// debug
			}			
			break;
		case PasivoM1M2:
			if (msg.port() == Carga_in) {
				this->carga = V;
				this->entrega = msg.value();
				this->estado = EntregandoM3;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Carga_in" << endl;
// debug
			}
			if (msg.port() == Lista_m1) {
				this->m1 = L;
				if (this->carga == F)
					this->estado = Pasivo;
				else
					this->estado = PasivoM1M2;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m1" << endl;
// debug
			}
			if (msg.port() == Lista_m2) {
				this->m2 = L;
				if (this->carga == F)
					this->estado = PasivoM1;
				else
					this->estado = PasivoM1M2;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m2" << endl;
// debug
			}
			if (msg.port() == Lista_m4) {
				this->m4 = L;
				this->estado = PasivoM1M2;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m4" << endl;
// debug
			}
			if (msg.port() == Esperar_m1) {
				this->m1 = O;
// debug	
//	salida << msg.time() << " port Esperar_m1" << endl;
// debug
			}			
			if (msg.port() == Esperar_m2) {
				this->m2 = O;
// debug	
//	salida << msg.time() << " port Esperar_m2" << endl;
// debug
			}			
			if (msg.port() == Esperar_m3) {
				this->m3 = O;
				this->carga = F;
				if (this->m1 == L) {
					this->estado = Pasivo;
					passivate();
				} else {
					if (this->m2 == L){
						this->estado = PasivoM1;
						passivate();
					} else {
						if (this->m4 == L){
							this->estado = PasivoM1M2M3;
							passivate();
						} else {
							this->estado = SinMotos;
							holdIn(active, 0);;
						}
					}
				}
// debug	
//	salida << msg.time() << " port Esperar_m3" << endl;
// debug
			}			
			if (msg.port() == Esperar_m4) {
				this->m4 = O;
// debug	
//	salida << msg.time() << " port Esperar_m4" << endl;
// debug
			}			
			break;
		case PasivoM1M2M3:
			if (msg.port() == Carga_in) {
				this->carga = V;
				this->entrega = msg.value();
				this->estado = EntregandoM4;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Carga_in" << endl;
// debug
			}
			if (msg.port() == Lista_m1) {
				this->m1 = L;
				if (this->carga == F)
					this->estado = Pasivo;
				else
					this->estado = PasivoM1M2M3;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m1" << endl;
// debug
			}
			if (msg.port() == Lista_m2) {
				this->m2 = L;
				if (this->carga == F)
					this->estado = PasivoM1;
				else
					this->estado = PasivoM1M2M3;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m2" << endl;
// debug
			}
			if (msg.port() == Lista_m3) {
				this->m3 = L;
				if (this->carga == F)
					this->estado = PasivoM1M2;
				else
					this->estado = PasivoM1M2M3;
				passivate();
// debug	
//	salida << msg.time() << " port Lista_m3" << endl;
// debug
			}
			if (msg.port() == Esperar_m1) {
				this->m1 = O;
// debug	
//	salida << msg.time() << " port Esperar_m1" << endl;
// debug
			}			
			if (msg.port() == Esperar_m2) {
				this->m2 = O;
// debug	
//	salida << msg.time() << " port Esperar_m2" << endl;
// debug
			}			
			if (msg.port() == Esperar_m3) {
				this->m3 = O;
// debug	
//	salida << msg.time() << " port Esperar_m3" << endl;
// debug
			}			
			if (msg.port() == Esperar_m4) {
				this->m4 = O;
				this->carga = F;
				if (this->m1 == L) {
					this->estado = Pasivo;
					passivate();
				} else {
					if (this->m2 == L){
						this->estado = PasivoM1;
						passivate();
					} else {
						if (this->m3 == L){
							this->estado = PasivoM1M2;
							passivate();
						} else {
							this->estado = SinMotos;
							holdIn(active, 0);;
						}
					}
				}
// debug	
//	salida << msg.time() << " port Esperar_m4" << endl;
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
Model &Selector::internalFunction( const InternalMessage &msg ){

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case EntregandoM1:
			this->estado = Pasivo;
			passivate();
			break;
		case EntregandoM2:
			this->estado = PasivoM1;
			passivate();
			break;
		case EntregandoM3:
			this->estado = PasivoM1M2;
			passivate();
			break;			
		case EntregandoM4:
			this->estado = PasivoM1M2M3;
			passivate();
			break;
		case ConMotos:
			this->aviso = F;
			this->estado = Pasivo;
			passivate();
			break;
		case SinMotos:
			this->aviso = V;
			this->estado = Pasivo;
			passivate();
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
Model &Selector::outputFunction( const InternalMessage &msg ) {

// debug	
//	salida << msg.time() << " estado OF " << this->estado << endl;
// debug

	switch (this->estado) {
		case EntregandoM1:
			sendOutput(msg.time(), Sel_out1, this->entrega);
			break;
		case EntregandoM2:
			sendOutput(msg.time(), Sel_out2, this->entrega);
			break;
		case EntregandoM3:
			sendOutput(msg.time(), Sel_out3, this->entrega);
			break;
		case EntregandoM4:
			sendOutput(msg.time(), Sel_out4, this->entrega);
			break;
		case SinMotos:
			sendOutput(msg.time(), Moto_ocupada, 1);
			break;
		case ConMotos:
			sendOutput(msg.time(), Moto_libre, 1);
			break;
		default:
			break;
	}
	return *this;
}
		
Selector::~Selector()
{
	//debug
//	this->salida.close();
	//debug
}