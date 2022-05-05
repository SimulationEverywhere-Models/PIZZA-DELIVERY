[top]
components : sel@Selector moto1@Moto moto2@Moto moto3@Moto moto4@Moto
out : Moto_libre_dist
out : Moto_ocupada_dist
out : Carga_out_dist
in : Carga_in_dist

Link : Carga_in_dist Carga_in@sel
Link : Moto_libre@sel Moto_libre_dist
Link : Moto_ocupada@sel Moto_ocupada_dist
Link : Entrega_mi@moto1 Carga_out_dist
Link : Entrega_mi@moto2 Carga_out_dist
Link : Entrega_mi@moto3 Carga_out_dist
Link : Entrega_mi@moto4 Carga_out_dist
Link : Sel_out1@sel Carga_mi@moto1
Link : Sel_out2@sel Carga_mi@moto2
Link : Sel_out3@sel Carga_mi@moto3
Link : Sel_out4@sel Carga_mi@moto4
Link : Ocupada_mi@moto1 Esperar_m1@sel
Link : Ocupada_mi@moto2 Esperar_m2@sel
Link : Ocupada_mi@moto3 Esperar_m3@sel
Link : Ocupada_mi@moto4 Esperar_m4@sel
Link : Libre_mi@moto1 Lista_m1@sel
Link : Libre_mi@moto2 Lista_m2@sel
Link : Libre_mi@moto3 Lista_m3@sel
Link : Libre_mi@moto4 Lista_m4@sel

[moto1]
EM : 3
C1 : 1
C2 : 1 
TCU : 00:00:00:030
TT : 00:00:03:000

[moto2]
EM : 5
C1 : 1
C2 : 1 
TCU : 00:00:00:030
TT : 00:00:03:000

[moto3]
EM : 5
C1 : 1
C2 : 1 
TCU : 00:00:00:030
TT : 00:00:03:000

[moto4]
EM : 3
C1 : 1
C2 : 1 
TCU : 00:00:00:030
TT : 00:00:03:000