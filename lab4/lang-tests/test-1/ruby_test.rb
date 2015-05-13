# En este test vamos a ver que Ruby es un lenguaje de progamacion dinamica.
# Para ello vamos a ver como no verifica el contenido en las variables y
# cuando se ejecuta tira error de tipo.

def algo()
    a = 3
    b = "hola"
    a = a+b
    return a
end

print algo()
