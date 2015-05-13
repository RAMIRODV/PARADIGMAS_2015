"""
En este test vamos a probar que Python es un lenguaje de programacion de
tipado Dinamico.
Para ello vamos a ver que cuando python compila no verifica los tipados de la
funcion, es decir, no nos tira error de tipo.
Python verifica el tipado en tiempo de ejecucion (dinamico).
Para la compilacion usamos:
    python -m compileall <nombre_de_archivo>
"""

def dinamycTest():
    st = "hola"
    # El operador binario (+) puede sumar dos numeros o puede concatenar dos
    # strings
    suma = st + 2  # Tratamos de sumar string + numero lo cual no es posible.
    return suma

"""
Al importarlo como modulo en un interprete como ipython podriamos usar la
funcion. Pej:
> import python_test
> python_test.dinamycTest()

Al ejecutar esta funcion python ira ejecutando linea a linea y verificando el
tipado; cuando llegue a la declaracion suma = st + 2 vera que no son del mismo 
tipo y lanzara un error de tipo.
"""
