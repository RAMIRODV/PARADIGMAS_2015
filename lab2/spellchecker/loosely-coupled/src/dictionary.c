#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

struct Dict {    // Estructura del diccionario.
    char **dict;
    int size;
};

/*******************************************************************
* NAME :            Dictionary dict_new (void)
*
* DESCRIPTION :     Crea una nueva estructura diccionario.
*
* PARAMETERS:
*      INPUT:
*           void
* RETURN :
*           Type: Dictionary
*******************************************************************/
Dictionary dict_new (void) {
    Dictionary dic = NULL;
    dic = calloc (1, sizeof (struct Dict));
    if (dic != NULL) {
        dic->dict = NULL;
        dic->size = 0;
    }
    return dic;
}

/*******************************************************************
* NAME :            void dict_load (Dictionary dic, char *fname, int max_word)
*
* DESCRIPTION :     Carga en memoria el diccionario desde 
*                   el archivo fname
*
* PARAMETERS:
*      INPUT:
*           Dictionary dic       Estructura que contiene al diccionario
*           char    *fname       Nombre del archivo que contiene el 
*                                diccionario
*           int max_word         Tamaño maximo de una palabra
* RETURN :
*           Type: void
*
* OBSERVATIONS :
*    1) El tamaño de la lista que contiene representa al diccionario 
*       debe coincidir con el nro de palabras en el diccionario. 
*       Esto implica que si es necesario hay que "agrandar" la lista, 
*       y si sobra espacio en la lista hay que "achicarla".
*    2) Recordar borrar el \n y \r al final de cada palabra y que los 
*       strings en C terminan en \0.
*******************************************************************/
void dict_load (Dictionary dic, char *fname, int max_word) {
    char **tmp = NULL;
    int c = 0,    // Caracter de cada palabra leida.
        i = 0,    // Indice de arreglo de diccionario principal.
        j = 0;    // Indice de lectura de caracteres de palabras.
    char word[max_word];    // Palabra leida del diccionario principal.
    FILE *ficher = fopen(fname,"rw");    // Abrir archivo de diccionario principal.
    if (ficher != NULL) {
        dic->size = 10;    // Tamaño inicial del diccionario principal.
        dic->dict = (char **)calloc(dic->size, sizeof(char *));
        if (dic->dict != NULL){
            while (feof(ficher) == 0) {    // No llego al EOF.
                if (i < (dic->size)) {    // No llego al tamaño inicial del diccionario principal.
                    for (j=0; (c=fgetc(ficher))!='\n' && c!='\r' && c!=EOF; j++) {    // Toma un caracter del archivo, que sea distinto de \n, \r o EOF.
                        if (j<max_word && isalpha(c)) {    // La palabra es menor al tamaño maximo y es alfabetica.
                            word[j] = c;
                        } else {    // La palabra es mayor al tamaño maximo, o no es alfabetico.
                            printf("Error: El diccionario posee palabras mayores al tamaño maximo permitido.\n");
                            exit(1);   // Salida forzosa del programa por ingresar un diccionario no valido.
                        }
                    }
                    word[j] = '\0';    // Agrega fin de string.
                    if (feof(ficher) == 0) {    // No llego al EOF.
                        dic->dict[i] = calloc(max_word, sizeof(char));
                        if (dic->dict[i] != NULL) {
                            strcpy(dic->dict[i], word);    // Copia palabra del archivo al diccionario principal.
                            i++;
                        } else {
                            printf("Error de memoria.\n");
                            exit(1);   // Salida forzosa del programa.
                        }
                    } else {    // Llego al EOF.
                        break;
                    }
                } else {    // Llego al tamaño inicial del diccionario principal. Asigna mas memoria.
                    dic->size = (dic->size)*10;
                    tmp = (char **)realloc(dic->dict, (dic->size)*sizeof(char *));
                    if (tmp != NULL) {
                        dic->dict = tmp;
                        tmp = NULL;
                    } else {
                        printf("Error de memoria.\n");
                        exit(1);   // Salida forzosa del programa.
                    }
                }
            }
            dic->size = i;
            if (dic->size != 0) {
                tmp = (char **)realloc(dic->dict, (dic->size)*sizeof(char *));    // Establece tamaño real del diccionario principal en memoria.
                if (tmp != NULL) {
                    dic->dict = tmp;
                    tmp = NULL;
                } else {
                    printf("Error de memoria.\n");
                    exit(1);   // Salida forzosa del programa.
                }
            } else {
                free(dic->dict);
            }
        } else {
            printf("Error de memoria.\n");
            exit(1);   // Salida forzosa del programa.
        }
        if (fclose(ficher) != 0) {
            printf("Error al cerrar el archivo.\n");
            exit(1);   // Salida forzosa del programa.
        }
    } /*else {    // Si el parametro diccionario.txt es obligatorio.
        printf("Error al abrir el archivo.\n");
        exit(1);   // Salida forzosa del programa.
    }*/
}

/*******************************************************************
* NAME :            void dict_save (Dictionary dic, char *fname)
*
* DESCRIPTION :     Guarda el diccionario en el archivo fname
*
* PARAMETERS:
*      INPUT:
*           Dictionary dic       Estructura que contiene al diccionario
*           char    *fname       Nombre del archivo donde se guardara
*                                el diccionario
* RETURN :
*           Type: void
*******************************************************************/
void dict_save (Dictionary dic, char *fname) {
    char new_line = '\n';
    int i = 0;
    FILE *ficher = fopen(fname,"w");
    if (ficher != NULL) {
        while (dic->size != i) {    // El diccionario no esta vacio.
            fputs(dic->dict[i], ficher);    // Coloca palabra del diccionario en el archivo.
            putc(new_line, ficher);    // Coloca \n en el archivo.
            i++;
        }
        if (fclose(ficher) != 0) {
            printf("Error al cerrar el archivo.\n");
            exit(1);   // Salida forzosa del programa.
        }
    } else {
        printf("Error al abrir el archivo.\n");
        exit(1);   // Salida forzosa del programa.
    }
}

/*******************************************************************
* NAME :            void dict_add (Dictionary dic, char *word, int max_word)
*
* DESCRIPTION :     Agrega una palabra al diccionario
*
* PARAMETERS:
*      INPUT:
*           Dictionary dic       Estructura que contiene al diccionario
*           char    *word        Palabra a ser agregada.
*           int max_word         Tamaño maximo de una palabra
* RETURN :
*           Type: void
*******************************************************************/
void dict_add (Dictionary dic, char *word, int max_word) {
    char **tmp = NULL;
    if (dic->size == 0) {    // No hay palabras.
        tmp = calloc((dic->size)+1, sizeof(char *));    // Otorga memoria.
        if (tmp != NULL) {
            dic->dict = tmp;
            tmp = NULL;
        } else {
            printf("Error de memoria.\n");
            exit(1);   // Salida forzosa del programa.
        }
    } else {    // Hay palabras.
        tmp = (char **)realloc(dic->dict, ((dic->size)+1)*sizeof(char *));    // Actualiza tamaño.
        if (tmp != NULL) {
            dic->dict = tmp;
            tmp = NULL;
        } else {
            printf("Error de memoria.\n");
            exit(1);   // Salida forzosa del programa.
        }
    }
    dic->dict[dic->size] = calloc(max_word, sizeof(char));    //  Otorga memoria para palabra.
    if (dic->dict[dic->size] != NULL) {
        strcpy(dic->dict[dic->size], word);    // Copia nueva palabra.
        (dic->size)++;
    } else {
        printf("Error de memoria.\n");
        exit(1);   // Salida forzosa del programa.
    }
}

/*******************************************************************
* NAME :            int dict_contains (Dictionary dic, char *word)
*
* DESCRIPTION :     Verifica si una palabra es "conocida", 
*                   porque esta en el diccionario 
*
* PARAMETERS:
*      INPUT:
*           Dictionary dic       Estructura que contiene al diccionario
*           char    *word        Palabra a verificar.
*
* RETURN :
*           Type: int
*           Values: 1 si la palabra es conocida
*                   0 si la palabra no es conocida
*******************************************************************/
int dict_contains (Dictionary dic, char *word) {
    int result = 0;
    int i = 0;    // Indice de palabras recorridas.
    while (i != dic->size) {    // No llego a su tamaño.
        if (strcmp(dic->dict[i], word) == 0) {    // Las palabras son iguales.
            result = 1;
            break;
        }
        i++;
    }
    return (result);
}

/*******************************************************************
* NAME :            Dictionary dict_destroy (Dictionary dic)
*
* DESCRIPTION :     Destruye el diccionario, liberando la memoria
*
* PARAMETERS:
*      INPUT:
*           Dictionary dic       Estructura que contiene al diccionario
*
* RETURN :
*           Type: Dictionary
*******************************************************************/
Dictionary dict_destroy (Dictionary dic) {
    if (dic->size != 0) {
        while (dic->size != 0) {    // Libera memoria.
            (dic->size)--;
            free(dic->dict[dic->size]);
        }
        free(dic->dict);
    }
    free(dic);
    dic = NULL;
    return dic;
}
