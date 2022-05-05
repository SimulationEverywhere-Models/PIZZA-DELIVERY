/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"          // class Queue
#include "generat.h"        // class Generator
#include "cpu.h"            // class CPU

#include "llamada.h"        // class llamada
#include "uc.h"				// class unidad control
#include "pedido.h"        // class pedido
#include "cocina.h"        // class cocina
#include "entrega.h"        // class entrega
#include "selector.h"        // class selector
#include "moto.h"        // class moto

#include "transduc.h"       // class Transducer
#include "trafico.h"        // class Trafico

void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Llamada>() , "Llamada" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<UC>() , "UC" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Pedido>() , "Pedido" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Cocina>() , "Cocina" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Entrega>() , "Entrega" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Selector>() , "Selector" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Moto>() , "Moto" ) ;

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
}