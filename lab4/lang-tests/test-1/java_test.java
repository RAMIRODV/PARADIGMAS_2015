/* En este test vamos a ver que Java es un lenguaje de programacion de tipado
 * estatico.
 * Para ello vamos a ver como Java no compila porque al verificar los tipos de
 * las variables vera que no son compatibles y nos lanzara un error de tipo.
 */

/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
    public static void main (String[] args) throws java.lang.Exception
    {
        boolean a = true;
        int b = a;
    }
}
