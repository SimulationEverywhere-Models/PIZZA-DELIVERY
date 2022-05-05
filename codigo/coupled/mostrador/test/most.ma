[top]
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
