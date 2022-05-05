TRABAJO PRACTICO N 1
Daniela Blanco
daniblanco@gmail.com

IMPLEMENTACION "DELIVERY" FORMALISMO DEVS

ARCHIVOS DE LA IMPLEMENTACION

[atomic]
	[cocina]
		cocina.h: header C++ del modelo at�mico Cocina
		cocina.cpp: c�digo fuente en C++ del modelo at�mico Cocina
		register.cpp: arhivo de registro en cd++ modelo atomico Cocina
	[entrega]
		entrega.h: header C++ del modelo at�mico Entrega
		entrega.cpp: c�digo fuente en C++ del modelo at�mico Entrega
		register.cpp: arhivo de registro en cd++ modelo atomico Entrega
	[llamada]
		llamada.h: header C++ del modelo at�mico Llamada
		llamada.cpp: c�digo fuente en C++ del modelo at�mico Llamada
		register.cpp: arhivo de registro en cd++ modelo atomico Llamada
	[moto]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		moto.h: header C++ del modelo at�mico Moto
		moto.cpp: c�digo fuente en C++ del modelo at�mico Moto
		register.cpp: arhivo de registro en cd++ modelo atomico Moto
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: c�digo fuente en C++ implementacion clase TipLlam
	[pedido]
		pedido.h: header C++ del modelo at�mico pedido
		pedido.cpp: c�digo fuente en C++ del modelo at�mico pedido
		register.cpp: arhivo de registro en cd++ modelo atomico pedido
	[selector]
		selector.h: header C++ del modelo at�mico selector
		selector.cpp: c�digo fuente en C++ del modelo at�mico selector
		register.cpp: arhivo de registro en cd++ modelo atomico selector
	[uc]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		uc.h: header C++ del modelo at�mico UC
		uc.cpp: c�digo fuente en C++ del modelo at�mico UC
		register.cpp: arhivo de registro en cd++ modelo atomico UC
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: c�digo fuente en C++ implementacion clase TipLlam
[coupled]
	[distribuidor]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		moto.h: header C++ del modelo at�mico Moto
		moto.cpp: c�digo fuente en C++ del modelo at�mico Moto
		selector.h: header C++ del modelo at�mico selector
		selector.cpp: c�digo fuente en C++ del modelo at�mico selector
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: c�digo fuente en C++ implementacion clase TipLlam
		register.cpp: arhivo de registro en cd++ modelo atomico moto y selector
	[mostrador]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		pedido.h: header C++ del modelo at�mico pedido
		pedido.cpp: c�digo fuente en C++ del modelo at�mico pedido
		uc.h: header C++ del modelo at�mico UC
		uc.cpp: c�digo fuente en C++ del modelo at�mico UC
		register.cpp: arhivo de registro en cd++ modelo atomico UC y pedido
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: c�digo fuente en C++ implementacion clase TipLlam
[top]
	ent.txt: archivo de parametrizacion de las entradas (requerido).
	cocina.h: header C++ del modelo at�mico Cocina
	cocina.cpp: c�digo fuente en C++ del modelo at�mico Cocina
	entrega.h: header C++ del modelo at�mico Entrega
	entrega.cpp: c�digo fuente en C++ del modelo at�mico Entrega
	llamada.h: header C++ del modelo at�mico Llamada
	llamada.cpp: c�digo fuente en C++ del modelo at�mico Llamada
	moto.h: header C++ del modelo at�mico Moto
	moto.cpp: c�digo fuente en C++ del modelo at�mico Moto
	pedido.h: header C++ del modelo at�mico pedido
	pedido.cpp: c�digo fuente en C++ del modelo at�mico pedido
	selector.h: header C++ del modelo at�mico selector
	selector.cpp: c�digo fuente en C++ del modelo at�mico selector
	uc.h: header C++ del modelo at�mico UC
	uc.cpp: c�digo fuente en C++ del modelo at�mico UC
	register.cpp: arhivo de registro en cd++ modelo atomico cocina, entrega,
		llamada, moto, pedido, selector, uc
	tipLlam.h: header C++ de la clase TipLlam
	tipLlam.cpp: c�digo fuente en C++ implementacion clase TipLlam


ARCHIVOS DE PRUEBA

En cada carpeta hay una subcarpeta TEST con los archivos
.ma y .ev para ejecutar las pruebas.
Se ejecutan con test.bat.
Los .out son ejecuciones previas

ARCHIVOS ADICIONALES:

informe_tp1.doc: informe del trabajo pr�ctico
