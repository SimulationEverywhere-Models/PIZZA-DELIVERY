[top]
components : moto@Moto
out : Ocupada_mi
out : Libre_mi
out : Entrega_mi
in : Carga_mi
Link : Carga_mi Carga_mi@moto
Link : Ocupada_mi@moto Ocupada_mi
Link : Libre_mi@moto Libre_mi
Link : Entrega_mi@moto Entrega_mi

[moto]
EM : 3
C1 : 1
C2 : 1 
TCU : 00:00:00:030
TT : 00:00:03:000
# para debugs
archivo : debug
