[top]
components : pedido@Pedido
out : Pedido_out
out : Parar_p
out : Libre_p
in : Pedido_in
in : Esperar_p
in : Listo_p
Link : Pedido_in Pedido_in@pedido
Link : Esperar_p Esperar_p@pedido
Link : Listo_p Listo_p@pedido
Link : Pedido_out@pedido Pedido_out
Link : Parar_p@pedido Parar_p
Link : Libre_p@pedido Libre_p

[pedido]
TE : 00:00:00:030
K : 5
# para debugs
archivo : debug
