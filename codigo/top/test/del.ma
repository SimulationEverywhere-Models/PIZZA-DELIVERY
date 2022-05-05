[top]
components : most cocina@Cocina dist entrega@Entrega llamada@Llamada
out : Ocupada_del
out : No_atiende_del
out : Error_del
out : Salida_del
in : Abrir_del
in : Cerrar_del
in : Llamada_del
Link : Abrir_del Abrir_m@most
Link : Cerrar_del Cerrar_m@most
Link : LLamada_del Llamada_in@llamada
Link : Ocupado@llamada Ocupada_del
Link : No_atiende@llamada No_atiende_del
Link : Ll_error_m@most Error_del
Link : Carga_out_dist@dist Salida_del
Link : Recibe_ll@llamada Atiende_m@most
Link : Manda_pedido@most Recibe_pedido@cocina
Link : Ocupada_ent_m@most Esperar_ent@entrega
Link : Libre_m_ent@most Lista_ent@entrega
Link : Dist_out_m@most Carga_in_dist@dist
Link : Lista_ll_m@most Lista_ll@llamada
Link : Cerrado_m@most Parar_ll@llamada
Link : Libre_m@most Libre@llamada
Link : Ocupado_m@most Esperar@llamada
Link : Ocupada_c@cocina Esperar_m@most
Link : Lista_c@cocina Listo_m@most
Link : Sale_pedido@cocina Ent_in@entrega
Link : Ent_out@entrega Recibe_ent_m@most
Link : Libre_ent@entrega Lista_ent_m@most
Link : Parar_ent@entrega Lleno_ent@most
Link : Moto_libre_dist@dist Moto_libre_m@most
Link : Moto_ocupada_dist@dist Moto_ocupada_m@most

[most]
components : uc@Uc pedido@Pedido
out : Ocupado_m
out : Libre_m
out : Ll_error_m
out : Manda_pedido
out : Ocupada_ent_m
out : Libre_m_ent
out : Dist_out_m
out : Lista_ll_m
out : Cerrado_m
in : Atiende_m
in : Cerrar_m
in : Abrir_m
in : Esperar_m
in : Listo_m
in : Recibe_ent_m
in : Lista_ent_m
in : Lleno_ent
in : Moto_ocupada_m
in : Moto_libre_m
Link : Atiende_m Atiende_uc@uc
Link : Cerrar_m Cerrar_uc@uc
Link : Abrir_m Abrir_uc@uc
Link : Esperar_m Esperar_p@pedido
Link : Listo_m Listo_p@pedido
Link : Recibe_ent_m Recibe_ent_uc@uc
Link : Lista_ent_m Lista_ent_uc@uc
Link : Lleno_ent Lleno_ent_uc@uc
Link : Moto_ocupada_m Moto_ocupada_uc@uc
Link : Moto_libre_m Moto_libre_uc@uc
Link : Ocupado_uc@uc Ocupado_m
Link : Libre_uc@uc Libre_m
Link : Ll_error_uc@uc Ll_error_m
Link : Pedido_out@pedido Manda_pedido
Link : Ocupada_ent_uc@uc Ocupada_ent_m
Link : Libre_uc_ent@uc Libre_m_ent
Link : Dist_out_uc@uc Dist_out_m
Link : Lista_ll_uc@uc Lista_ll_m
Link : Cerrado_uc@uc Cerrado_m
Link : Encolar_p@uc Pedido_in@pedido
Link : Parar_p@pedido Lleno_p@uc
Link : Libre_p@pedido Lista_p_uc@uc

[uc]
TR : 00:00:02:000
TE : 00:00:00:030

[pedido]
TE : 00:00:00:030
K : 5

[cocina]
PM : 5
COC_MIN : 5
COC_MAX : 20

[dist]
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

[entrega]
TE : 00:00:00:030
K : 5

[llamada]
TNA : 00:00:00:015