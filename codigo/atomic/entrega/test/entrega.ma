[top]
components : entrega@Entrega
out : Ent_out
out : Parar_ent
out : Libre_ent
in : Ent_in
in : Esperar_ent
in : Lista_ent
Link : Ent_in Ent_in@entrega
Link : Esperar_ent Esperar_ent@entrega
Link : Libre_ent Libre_ent@entrega
Link : Ent_out@entrega Ent_out
Link : Parar_ent@entrega Parar_ent
Link : Lista_ent@entrega Lista_ent

[entrega]
TE : 00:00:00:030
K : 5
# para debugs
archivo : debug
