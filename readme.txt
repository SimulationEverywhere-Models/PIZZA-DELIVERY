TRABAJO PRACTICO N 1
Daniela Blanco
daniblanco@gmail.com

IMPLEMENTACION "DELIVERY" FORMALISMO DEVS

ARCHIVOS DE LA IMPLEMENTACION

[atomic]
	[cocina]
		cocina.h: header C++ del modelo atómico Cocina
		cocina.cpp: código fuente en C++ del modelo atómico Cocina
		register.cpp: arhivo de registro en cd++ modelo atomico Cocina
	[entrega]
		entrega.h: header C++ del modelo atómico Entrega
		entrega.cpp: código fuente en C++ del modelo atómico Entrega
		register.cpp: arhivo de registro en cd++ modelo atomico Entrega
	[llamada]
		llamada.h: header C++ del modelo atómico Llamada
		llamada.cpp: código fuente en C++ del modelo atómico Llamada
		register.cpp: arhivo de registro en cd++ modelo atomico Llamada
	[moto]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		moto.h: header C++ del modelo atómico Moto
		moto.cpp: código fuente en C++ del modelo atómico Moto
		register.cpp: arhivo de registro en cd++ modelo atomico Moto
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: código fuente en C++ implementacion clase TipLlam
	[pedido]
		pedido.h: header C++ del modelo atómico pedido
		pedido.cpp: código fuente en C++ del modelo atómico pedido
		register.cpp: arhivo de registro en cd++ modelo atomico pedido
	[selector]
		selector.h: header C++ del modelo atómico selector
		selector.cpp: código fuente en C++ del modelo atómico selector
		register.cpp: arhivo de registro en cd++ modelo atomico selector
	[uc]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		uc.h: header C++ del modelo atómico UC
		uc.cpp: código fuente en C++ del modelo atómico UC
		register.cpp: arhivo de registro en cd++ modelo atomico UC
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: código fuente en C++ implementacion clase TipLlam
[coupled]
	[distribuidor]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		moto.h: header C++ del modelo atómico Moto
		moto.cpp: código fuente en C++ del modelo atómico Moto
		selector.h: header C++ del modelo atómico selector
		selector.cpp: código fuente en C++ del modelo atómico selector
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: código fuente en C++ implementacion clase TipLlam
		register.cpp: arhivo de registro en cd++ modelo atomico moto y selector
	[mostrador]
		ent.txt: archivo de parametrizacion de las entradas (requerido).
		pedido.h: header C++ del modelo atómico pedido
		pedido.cpp: código fuente en C++ del modelo atómico pedido
		uc.h: header C++ del modelo atómico UC
		uc.cpp: código fuente en C++ del modelo atómico UC
		register.cpp: arhivo de registro en cd++ modelo atomico UC y pedido
		tipLlam.h: header C++ de la clase TipLlam
		tipLlam.cpp: código fuente en C++ implementacion clase TipLlam
[top]
	ent.txt: archivo de parametrizacion de las entradas (requerido).
	cocina.h: header C++ del modelo atómico Cocina
	cocina.cpp: código fuente en C++ del modelo atómico Cocina
	entrega.h: header C++ del modelo atómico Entrega
	entrega.cpp: código fuente en C++ del modelo atómico Entrega
	llamada.h: header C++ del modelo atómico Llamada
	llamada.cpp: código fuente en C++ del modelo atómico Llamada
	moto.h: header C++ del modelo atómico Moto
	moto.cpp: código fuente en C++ del modelo atómico Moto
	pedido.h: header C++ del modelo atómico pedido
	pedido.cpp: código fuente en C++ del modelo atómico pedido
	selector.h: header C++ del modelo atómico selector
	selector.cpp: código fuente en C++ del modelo atómico selector
	uc.h: header C++ del modelo atómico UC
	uc.cpp: código fuente en C++ del modelo atómico UC
	register.cpp: arhivo de registro en cd++ modelo atomico cocina, entrega,
		llamada, moto, pedido, selector, uc
	tipLlam.h: header C++ de la clase TipLlam
	tipLlam.cpp: código fuente en C++ implementacion clase TipLlam


ARCHIVOS DE PRUEBA

En cada carpeta hay una subcarpeta TEST con los archivos
.ma y .ev para ejecutar las pruebas.
Se ejecutan con test.bat.
Los .out son ejecuciones previas

ARCHIVOS ADICIONALES:

informe_tp1.doc: informe del trabajo práctico
