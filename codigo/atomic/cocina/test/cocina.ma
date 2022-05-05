[top]
components : cocina@Cocina
out : Ocupada_c
out : Lista_c
out : Sale_pedido
in : Recibe_pedido
Link : Recibe_pedido Recibe_pedido@cocina
Link : Ocupada_c@cocina Ocupada_c
Link : Lista_c@cocina Lista_c
Link : Sale_pedido@cocina Sale_pedido

[cocina]
PM : 5
COC_MIN : 5
COC_MAX : 20
# para debugs
archivo : debug
