/*******************************************************************
*
*  DESCRIPTION: Modelo Atomico Unidad de Control
*
*  AUTHOR: Daniela Blanco
*
*  DATE: 5/2008
*
*******************************************************************/

#include "uc.h"
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

// Constructor
UC::UC(const string &name) : Atomic(name),
		//puertos de entrada
		Atiende_uc(addInputPort("Atiende_uc")),
		Cerrar_uc(addInputPort("Cerrar_uc")),
		Abrir_uc(addInputPort("Abrir_uc")),
		Recibe_ent_uc(addInputPort("Recibe_ent_uc")),
		Lleno_ent_uc(addInputPort("Lleno_ent_uc")),
		Lista_ent_uc(addInputPort("Lista_ent_uc")),
		Moto_ocupada_uc(addInputPort("Moto_ocupada_uc")),
		Moto_libre_uc(addInputPort("Moto_libre_uc")),
		Lleno_p(addInputPort("Lleno_p")),
		Lista_p_uc(addInputPort("Lista_p_uc")),

		//puertos de salida
		Ocupado_uc(addOutputPort("Ocupado_uc")),
		Libre_uc(addOutputPort("Libre_uc")),
		Ll_error_uc(addOutputPort("Ll_error_uc")),	
		Encolar_p(addOutputPort("Encolar_p")),	
		Ocupada_ent_uc(addOutputPort("Ocupada_ent_uc")),	
		Libre_uc_ent(addOutputPort("Libre_uc_ent")),	
		Dist_out_uc(addOutputPort("Dist_out_uc")),	
		Lista_ll_uc(addOutputPort("Lista_ll_uc")),	
		Cerrado_uc(addOutputPort("Cerrado_uc")) {	
}

// Inicializacion
Model &UC::initFunction() {

 	//carga variables estado
	this->estado = Cerrado;
	this->ab = F;
	//Creo el pedido vacio (id, calle1, calle2)
	this->pedido.CrearLlamada(0, 0, 0);
	//Creo la entrega vacia (id, calle1, calle2)
	this->entrega.CrearLlamada(0, 0, 0);
	this->cant_p = 0;
	this->moto = L;
	this->lista = 0;

	//carga parametros
	string time(MainSimulator::Instance().getParameter(description(), "TR"));
	if( time != "" )
		this->tRecepcion = time;
	string time2(MainSimulator::Instance().getParameter(description(), "TE"));
	if( time2 != "" )
		this->tEnvio = time2;
		
	passivate();
			
// debug
//	this->salida.open(MainSimulator::Instance().getParameter(description(), "archivo").c_str(), ios::in);
//	salida << "tRecepcion " << tRecepcion << endl;
//	salida << "tEnvio " << tEnvio << endl;
// debug
			
	return *this;
}

// Funcion de transicion externa
Model &UC::externalFunction(const ExternalMessage &msg) {

TipLlam vll;

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Cerrado:
			if (msg.port() == Abrir_uc) {
					this->ab = V;
					this->cant_p = 0;
					this->estado = Abriendo;
					holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Abrir_uc" << endl;
//	salida << msg.time() << " cant_p " << this->cant_p << endl;
//	salida << msg.time() << " ab "  << this->ab << endl;
// debug
			}	
			break;
		case Abierta:
			if (msg.port() == Cerrar_uc) {
				this->ab = F;
				if (this->cant_p == 0)
				{
					this->estado = Cerrando;
				} else {
					this->estado = CerrandoConPedidos;
				}
				holdIn(active, 0);						
// debug	
//	salida << msg.time() << " port Cerrar_uc" << endl;
//	salida << msg.time() << " ab " << this->ab << endl;
// debug
			}
			if (msg.port() == Atiende_uc) {
				vll = obtenerDato(msg.value());
				this->pedido = vll;
				this->estado = Atendiendo;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Atiende_uc" << endl;
// debug
			}
			if (msg.port() == Moto_ocupada_uc) {
					this->moto = O;
					this->estado = ProcesandoMoto;
					holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Moto_ocupada_uc" << endl;
//	salida << msg.time() << " moto " << this->moto << endl;
// debug
			}
			if (msg.port() == Moto_libre_uc) {
					this->moto = L;
					this->estado = ProcesandoMoto;
					holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Moto_libre_uc" << endl;
//	salida << msg.time() << " moto " << this->moto << endl;
// debug
			}
			if (msg.port() == Lista_ent_uc) {
				if (this->lista == 2)
					this->lista = 0;
				else
					this->lista = 1;
				this->estado = ListaEntregas;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Lista_ent_uc" << endl;
//	salida << msg.time() << " lista " << this->lista << endl;
// debug
			}
			if (msg.port() == Lista_p_uc) {
				if (this->lista == 1)
					this->lista = 0;
				else
					this->lista = 2;
				this->estado = ListoPedidos;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Lista_p_uc" << endl;
//	salida << msg.time() << " lista " << this->lista << endl;
// debug
			}
			if (msg.port() == Recibe_ent_uc) {
				vll = obtenerDato(msg.value());
				this->entrega = vll;
				this->estado = RecibeEntrega;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Recibe_ent_uc" << endl;
// debug
			}
			if (msg.port() == Lleno_p) {
				if (this->lista == 0)
					this->lista = 1;
				else
					this->lista = 3;
				this->estado = LlenoPedidos;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Lleno_p" << endl;
//	salida << msg.time() << " lista " << this->lista << endl;
// debug
			}
			if (msg.port() == Lleno_ent_uc) {
				if (this->lista == 0)
					this->lista = 2;
				else
					this->lista = 3;
				this->estado = LlenoEntregas;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Lleno_ent_uc" << endl;
//	salida << msg.time() << " lista " << this->lista << endl;
// debug
			}			
			break;
		case Derivando:
			if (msg.port() == Moto_ocupada_uc) {
				this->moto = O;
				this->estado = ProcesandoMoto;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Moto_ocupada_uc" << endl;
//	salida << msg.time() << " moto " << this->moto << endl;
// debug
			}
			if (msg.port() == Moto_libre_uc) {
					this->moto = L;
					this->estado = ProcesandoMoto;
					holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Moto_libre_uc" << endl;
//	salida << msg.time() << " moto " << this->moto << endl;
// debug
			}
			break;
		case Entregando:
			if (msg.port() == Atiende_uc) {
				vll = obtenerDato(msg.value());
				this->pedido = vll;
				this->estado = Atendiendo;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Atiende_uc" << endl;
// debug
			}
			if (msg.port() == Lleno_ent_uc) {
				if (this->lista == 0)
					this->lista = 2;
				else
					this->lista = 3;
				this->estado = LlenoEntregas;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Lleno_ent_uc" << endl;
//	salida << msg.time() << " lista " << this->lista << endl;
// debug
			}
			if (msg.port() == Moto_ocupada_uc) {
				this->moto = O;
				this->estado = PasivoEntrega;
				passivate();
// debug	
//	salida << msg.time() << " port Moto_ocupada_uc" << endl;
//	salida << msg.time() << " moto " << this->moto << endl;
// debug
			}
			break;
		case PasivoEntrega:
			if (msg.port() == Moto_libre_uc) {
				this->moto = L;
				this->estado = Entregando;
				if ((this->t - msg.time()) < 0)
				{
					holdIn(active, 0);
				} else {
					holdIn(active, this->t - msg.time());
				}
// debug	
//	salida << msg.time() << " port Moto_libre_uc" << endl;
//	salida << msg.time() << " moto " << this->moto << endl;
// debug
			}
			break;
		case CerradoConPedidos:
			if (msg.port() == Recibe_ent_uc) {
				vll = obtenerDato(msg.value());
				this->entrega = vll;
				this->estado = RecibeEntrega;
				holdIn(active, 0);
// debug	
//	salida << msg.time() << " port Recibe_ent_uc" << endl;
// debug
			}
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
Model &UC::internalFunction(const InternalMessage &msg) {

TipLlam tl;

// debug	
//	salida << msg.time() << " estado I " << this->estado << endl;
// debug

	switch (this->estado) {
		case Abriendo:
			this->estado = Abierta;
			passivate();
			break;
		case Cerrando:
			this->estado = Cerrado;
			passivate();
			break;
		case ProcesandoMoto:
			if (this->pedido.IdLlam()==0)
			{
				this->estado = Abierta;
				passivate();
			} else {
				this->estado = Derivando;
				holdIn(active, this->tRecepcion);
			}
			break;
		case Atendiendo:
			this->estado = Derivando;
			holdIn(active, this->tRecepcion);
			break;
		case ListaEntregas:
			this->estado = Abierta;
			passivate();
			break;
		case ListoPedidos:
			this->estado = Abierta;
			passivate();
			break;
		case Derivando:
			tl.CrearLlamada(0, this->pedido.Calle1(), this->pedido.Calle2());
			this->pedido = tl;
			if (this->pedido.Calle1()==0 && this->pedido.Calle2()==0)
			{
				this->estado = Error;
			} else {
				this->cant_p = this->cant_p + 1;
				this->estado = EnCocina;
			}
			holdIn(active, 0);
// debug	
//	salida << msg.time() << " cant_p " << this->cant_p << endl;
// debug
			break;
		case EnCocina:
			if (this->entrega.IdLlam()==0)
			{
				this->estado = Abierta;
				passivate();
			} else {
				this->estado = Entregando;
				if ((this->t - msg.time()) < 0)
				{
					holdIn(active, 0);
				} else {
					holdIn(active, this->t - msg.time());
				}
			}
			break;
		case Error:
			if (this->entrega.IdLlam()==0)
			{
				this->estado = Abierta;
				passivate();
			} else {
				this->estado = Entregando;
				if ((this->t - msg.time()) < 0)
				{
					holdIn(active, 0);
				} else {
					holdIn(active, this->t - msg.time());
				}
			}
			break;
		case RecibeEntrega:
			this->estado = Entregando;
			this->t = msg.time() + tEnvio;
			holdIn(active, this->tEnvio);
			break;
		case Entregando:
			if (this->moto == O)
			{
				this->estado = PasivoEntrega;
				passivate();
			} else {
				if ((this->cant_p - 1)<0)
					this->cant_p = 0;
				else
					this->cant_p = this->cant_p - 1;
				tl.CrearLlamada(0, this->entrega.Calle1(), this->entrega.Calle2());
				this->entrega = tl;				
				this->estado = EnDistribuidor;
				holdIn(active, 0);
			}
// debug	
//	salida << msg.time() << " cant_p " << this->cant_p << endl;
// debug
			break;
		case LlenoEntregas:
			if (this->entrega.IdLlam()==0)
			{
				this->estado = Abierta;
				passivate();
			} else {	
				this->estado = Entregando;
				if ((this->t - msg.time()) < 0)
					holdIn(active, 0);
				else
					holdIn(active, this->t - msg.time());
			}
			break;
		case LlenoPedidos:
			this->estado = Abierta;
			passivate();
			break;
		case EnDistribuidor:
			if (this->ab == V)
			{
				this->estado = Abierta;
				passivate();
			} else {
				if (this->cant_p == 0)
				{
					this->estado = Cerrado;
				} else {
					this->estado = CerradoConPedidos;
				}
				passivate();
			}
			break;
		case CerrandoConPedidos:
			this->estado = CerradoConPedidos;
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
Model &UC::outputFunction(const InternalMessage &msg) {

// debug	
//	salida << msg.time() << " estado OF " << this->estado << endl;
// debug

	switch (this->estado) {
		case Abriendo:
			sendOutput(msg.time(), Lista_ll_uc, 1);
			break;
		case Cerrando:
			sendOutput(msg.time(), Cerrado_uc, 1);
			break;
		case Atendiendo:
			sendOutput(msg.time(), Ocupado_uc, 1);
			break;
		case ListaEntregas:
			if (this->lista == 0)
				sendOutput(msg.time(), Lista_ll_uc, 1);
			break;
		case ListoPedidos:
			if (this->lista == 0)
				sendOutput(msg.time(), Lista_ll_uc, 1);
			break;
		case Derivando:
			if (this->pedido.Calle1() == 0 && this->pedido.Calle2() == 0)
				sendOutput(msg.time(), Ll_error_uc, 1);
			else
				sendOutput(msg.time(), Encolar_p, this->pedido.IdLlam());
			break;
		case EnCocina:
			sendOutput(msg.time(), Libre_uc, 1);
			break;
		case Error:
			sendOutput(msg.time(), Libre_uc, 1);
			break;
		case RecibeEntrega:
			sendOutput(msg.time(), Ocupada_ent_uc, 1);
			break;
		case Entregando:
			if (this->moto == L)
				sendOutput(msg.time(), Dist_out_uc, this->entrega.IdLlam());
			break;
		case LlenoEntregas:
			if (this->lista ==2)
				sendOutput(msg.time(), Cerrado_uc, 1);
			break;
		case LlenoPedidos:
			if (this->lista ==1)
				sendOutput(msg.time(), Cerrado_uc, 1);
			break;
		case EnDistribuidor:
			sendOutput(msg.time(), Libre_uc_ent, 1);
			break;
		case CerrandoConPedidos:
			sendOutput(msg.time(), Cerrado_uc, 1);
			break;
		default:
			break;
	}

	return *this;
}

TipLlam& UC::obtenerDato(int p_idLlam){
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
		
UC::~UC()
{
	//debug
//	this->salida.close();
	//debug
}