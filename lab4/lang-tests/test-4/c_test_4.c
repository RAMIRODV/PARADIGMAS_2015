/* Este test dira que alcance tiene C. Para ello nos vasamos en el siguiente
 * ejemplo del libro Concepts in Programming Langages.
 *
 * int x = 1;
 * function g(z) = x+z;
 * function f(y) = {
 *      int x = y+1;
 *      return g(y*x);
 * };
 * f(3);
 *
 */

#include <stdio.h>

char x[] = "estatico";

void g(void) {
    printf("C tiene alcance: %s\n", x);
}

void f(void) {
    char x[] = "dinamico";
    g();
}

int main(void) {
    f();
    return 0;
}
