[top]
components : llamada@Llamada
out : Ocupado
out : No_atiende
out : Recibe_ll
in : Llamada_in
in : Lista_ll
in : Parar_ll
in : Esperar
in : Libre
Link : Llamada_in Llamada_in@llamada
Link : Lista_ll Lista_ll@llamada
Link : Parar_ll Parar_ll@llamada
Link : Esperar Esperar@llamada
Link : Libre Libre@llamada
Link : Ocupado@llamada Ocupado
Link : No_atiende@llamada No_atiende
Link : Recibe_ll@llamada Recibe_ll

[llamada]
TNA : 00:00:00:015
# para debugs
# archivo : debug