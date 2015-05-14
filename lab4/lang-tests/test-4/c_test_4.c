#include <stdio.h>
#include <stdbool.h>

void g(void) {
    char x[] = "estatico";
    printf("%s\n", x);
}

int main(void) {
    char x[] = "dinamico";
    printf("%s\n", x);
    g();
    printf("%s\n", x);
    return 0;
}
