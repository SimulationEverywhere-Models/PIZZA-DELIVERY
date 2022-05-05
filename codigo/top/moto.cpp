/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Moto
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#include "moto.h"
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

// Constructor
Moto::Moto(const string &name) : Atomic(name),
		//puertos de entrada
		Carga_mi(addInputPort("Carga_mi")),

		//puertos de salida
		Ocupada_mi(addOutputPort("Ocupada_mi")),
		Libre_mi(addOutputPort("Libre_mi")),
		Entrega_mi(addOutputPort("Entrega_mi"))
{	
}

// Inicializacion
Model &Moto::initFunction() {

 	//carga variables estado
	this->estado = Vacia;
	this->entregas.erase(entregas.begin(), entregas.end());
	this->distancias.erase(distancias.begin(), distancias.end());
	this->carga_in = 0;
	this->carga_out = 0;
	this->vuelta = Time(0, 0, 0, 0);
	this->t = Time(0, 0, 0, 0);

	//carga parametros
	int v_em = str2Int(MainSimulator::Instance().getParameter( description(), "EM" ));
	this->em = v_em;
	int v_c1 = str2Int(MainSimulator::Instance().getParameter( description(), "C1" ));
	this->cal1_del = v_c1;
	int v_c2 = str2Int(MainSimulator::Instance().getParameter( description(), "C2" ));
	this->cal2_del = v_c2;
	string time(MainSimulator::Instance().getParameter(description(), "TCU"));
	if( time != "" )
		this->tCuadra = time;
	string time2(MainSimulator::Instance().getParameter(description(), "TT"));
	if( time2 != "" )
		this->tToler = time2;
		
	passivate();
			
// debug
//	this->salida.open(MainSimulator::Instance().getParameter(description(), "archivo").c_str(), ios::in);
//	salida << "EM " << v_em << endl;
//	salida << "Call 1 " << v_c1 << endl;
//	salida << "Call 2 " << v_c2 << endl;
//	salida << "TCU " << tCuadra << endl;
//	salida << "TT " << tToler << endl;
// debug
			
	return *this;
}

// Funcion de transicion externa
Model &Moto::externalFunction(const ExternalMessage &msg) {

int dist;

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Vacia:
			dist = DistanciaDel(msg.value());
			agrega(msg.value(), dist);					
			if (this->carga_in + 1 < this->em) {
				this->carga_in = this->carga_in + 1;
				this-> t = this->tToler + msg.time();
				this->estado = Cargando;
				holdIn(active, this->tToler);
			} else {
				this->carga_in = this->carga_in + 1;
				this->estado = Llena;
				holdIn(active, 0);
			}
// debug	
//	salida << "carga_in " << this->carga_in << endl;
//	salida << "dist " << dist << endl;
//	salida << "tpo salida " << t << endl;
// debug
			break;
		case Cargando:
			dist = DistanciaDel(msg.value());
			agrega(msg.value(), dist);					
			if (this->carga_in + 1 < this->em) {
				this->carga_in = this->carga_in + 1;
				this->estado = Cargando;
				holdIn(active, this->t - msg.time());
			} else {
				this->carga_in = this->carga_in + 1;
				this->estado = Llena;
				holdIn(active, 0);
			}
// debug	
//	salida << "carga_in " << this->carga_in << endl;
//	salida << "dist " << dist << endl;
//	salida << "tpo salida " << t << endl;
// debug
			break;
		default:
			break;
		}

// debug	
//	salida << msg.time() <<  " estado F " << this->estado << endl;
// debug
	
	return *this;
}

// Funcion de transicion interna
Model &Moto::internalFunction(const InternalMessage &msg) {

Time vT;

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Cargando:
			this->carga_out = 1;
			this->vuelta = tiempoViaje(this->distancias.front());
			this->estado = ViajandoIda;
			holdIn(active, this->vuelta);
// debug	
//	salida << msg.time() << " carga_out " << this->carga_out << endl;
//	salida << msg.time() << " vuelta " << this->vuelta << endl;
// debug
			break;
		case Llena:
			this->carga_out = 1;
			this->vuelta = tiempoViaje(this->distancias.front());
			this->estado = ViajandoIda;
			holdIn(active, this->vuelta);
// debug	
//	salida << msg.time() << " carga_out " << this->carga_out << endl;
//	salida << msg.time() << " vuelta " << this->vuelta << endl;
// debug
			break;
		case ViajandoIda:
			if (this->carga_out < this->carga_in)
			{
				this->carga_out = this->carga_out + 1;
				vT =  tiempoViaje(this->Distancia());
				this->vuelta = this->vuelta + vT;
				this->entregas.pop_front();
				this->estado = ViajandoIda;
				holdIn(active, vT);
			} else {
				this->carga_in = 0;
				this->entregas.pop_front();
				this->estado = ViajandoVuelta;
				holdIn(active, this->vuelta);
			}
// debug	
//	salida << msg.time() << " carga_out " << this->carga_out << endl;
//	salida << msg.time() << " vT " << vT << endl;
//	salida << msg.time() << " vuelta " << this->vuelta << endl;
// debug
			break;
		case ViajandoVuelta:
			this->estado = Vacia;
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
Model &Moto::outputFunction(const InternalMessage &msg) {

TipLlam vTl;

// debug	
//	salida << msg.time() << " estado OF " << this->estado << endl;
// debug

	switch (this->estado) {
		case Cargando:
			sendOutput(msg.time(), Ocupada_mi, 1);
			break;
		case Llena:
			sendOutput(msg.time(), Ocupada_mi, 1);
			break;
		case ViajandoIda:
			vTl = this->entregas.front();
			sendOutput(msg.time(), Entrega_mi, vTl.IdLlam());
			break;
		case ViajandoVuelta:
			sendOutput(msg.time(), Libre_mi, 1);
			break;
		default:
			break;
	}

	return *this;
}

TipLlam& Moto::obtenerDato(int p_idLlam){
// busca segun p_idLlam
// el resto de los campos
// y crea la llamada

string linea;
string sTemp;
size_t  pos;
int v_IdLlam;
int v_Calle1;
int v_Calle2;
int sale;
TipLlam rta;
ifstream db;

	db.open("ent.txt",ios::out);

	sale = 0;
	while ((!db.eof()) && (sale==0))
	{
		getline(db, linea);

		pos = linea.find(" ", 0);					// busca delimitador " "
		sTemp = (linea.substr(0, pos));			// obtiene id
		v_IdLlam = atoi(sTemp.c_str());
	
		if (v_IdLlam == p_idLlam) {
			// encontro datos
			sale = 1;

			linea.erase(0, pos + 1);			// saca id del texto
			pos = linea.find(" ", 0);			// busca delimitador " "
			sTemp = linea.substr(0, pos);		// obtiene calle1
			v_Calle1 = atoi(sTemp.c_str());
			linea.erase(0, pos + 1);			// saca calle1 del texto
			pos = linea.find(" ", 0);			// busca delimitador " "
			sTemp = linea.substr(0, pos);		// obtiene calle2
			v_Calle2 = atoi(sTemp.c_str());
		}
	}
	db.close();
	
	rta.CrearLlamada(v_IdLlam, v_Calle1, v_Calle2);

	return rta;
}
		
Moto::~Moto()
{
	//debug
//	this->salida.close();
	//debug
}

int Moto::DistanciaDel(int new_e) {
TipLlam e;
int x1, x2, y1, y2;
int dist;

// obtengo distancia al delivery
// sqrt (pow(x2-x1, 2) + pow(y2-y1, 2));
x1 = this->cal1_del;
y1 = this->cal2_del;
e = obtenerDato(new_e);
x2 = e.Calle1();
y2 = e.Calle2();
dist = sqrt (pow(x2-x1, 2) + pow(y2-y1, 2));

// debug	
//	salida << " new_e " << new_e << endl;
//	salida << " x1 " << x1 << endl;
//	salida << " y1 " << y1 << endl;
//	salida << " x2 " << x2 << endl;
//	salida << " y2 " << y2 << endl;
// debug

	return dist;
}

int Moto::Distancia() {
//distancia entre los dos primeros
//elementos de entregas

LLamList le;
TipLlam e;
int x1, x2, y1, y2;
int dist;

le.assign (this->entregas.begin(),this->entregas.end());

// sqrt (pow(x2-x1, 2) + pow(y2-y1, 2));
e = le.front();
x1 = e.Calle1();
y1 = e.Calle2();
le.pop_front();
e = le.front();
x2 = e.Calle1();
y2 = e.Calle2();
dist = sqrt (pow(x2-x1, 2) + pow(y2-y1, 2));

le.erase(le.begin(), le.end());

// debug	
//	salida << " x1 " << x1 << endl;
//	salida << " y1 " << y1 << endl;
//	salida << " x2 " << x2 << endl;
//	salida << " y2 " << y2 << endl;
//	salida << " dist " << dist << endl;
// debug

	return dist;
}

Time Moto::tiempoViaje(int distancia) {
// cuanto tarda en hacer la distancia
// * por tCuadra

Time rta;

rta = Time (0, 0, 0, 0);

	// hay multiplicacion de time?
	// suma tCuadra veces el tiempo de cuadra
	for( int i = 0; i < distancia; i++ ) {
		rta = rta + this->tCuadra;
	}

	return rta;
}

void Moto::agrega(int new_e, int dist) {

TipLlam vTL;
LLamList ei, ef;
DistList di, df;
int i, fin;

vTL = obtenerDato(new_e);

	fin = 0;

	if ( this->distancias.back() <= dist ){
		// va al final
		this->entregas.push_back(vTL);
		this->distancias.push_back(dist);

	} else {
		// inserta ordenado, de menor a mayor dist
		// para = dist, ubica ultimo al nuevo

		//inicia
		ei.erase(ei.begin(), ei.end());
		di.erase(di.begin(), di.end());
		ef.erase(ef.begin(), ef.end());
		df.erase(df.begin(), df.end());

		ef.assign (this->entregas.begin(),this->entregas.end());
		df.assign (this->distancias.begin(),this->distancias.end());
 
		while (!ef.empty() && fin==0) {
			if (df.front() > dist) {
				// posicion donde va el nuevo
				fin = 1;
			} else {
				ei.push_back(ef.front());
				di.push_back(df.front());
				ef.pop_front();
				df.pop_front();
			}
		}

		// borra elementos
 		this->entregas.erase(this->entregas.begin(), this->entregas.end());
		this->distancias.erase(this->distancias.begin(), this->distancias.end());

		// agrego primeros
		this->entregas.assign(ei.begin(),ei.end());
		this->distancias.assign(di.begin(),di.end());

		// agrego actual
		this->entregas.push_back(vTL);
		this->distancias.push_back(dist);

		// agrego ultimos
		while (!ef.empty()) {
			this->entregas.push_back(ef.front());
			this->distancias.push_back(df.front());
			ef.pop_front();
			df.pop_front();
		}
	}

// debug	
//	i = 0;
//	df.assign (this->distancias.begin(),this->distancias.end());
//	while (!df.empty()) {
//	salida << " dist " << i << " " << df.front() << endl;
//	df.pop_front();
//	i = i +1;
//	}
// debug

}