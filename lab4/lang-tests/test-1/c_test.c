/* En este test vamos a ver que C es un lenguaje de programacion de tipado
 * estatico.
 * Para ello vamos a ver como C no compila porque al verificar los tipos de
 * las variables vera que no son compatibles y nos lanzara un error de tipo.
 */

#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int a = -23;
    char b[5];
    b = a;  // Aqui C, ve que no son del mismo tipo.
    return 0;
}
