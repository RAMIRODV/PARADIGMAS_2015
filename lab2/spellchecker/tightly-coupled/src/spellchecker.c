#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//tamaño maximo de una palabra
#define MAX_WORD_SIZE 30

/* diccionario principal */
char **dict_main;
/*tamaño inicial del diccionario principal*/
int main_size = 10;

/* diccionario de palabras ignoradas */
char **dict_ignored;
/*tamaño inicial del diccionario de palabras ignoradas*/
int ignored_size = 0;

/* Documento de entrada */
FILE *doc_in;
/* Documento de salida */
FILE *doc_out;

/*******************************************************************
* NAME :            void dict_load(char *fname)
*
* DESCRIPTION :     Carga en memoria el diccionario principal desde 
*                   el archivo fname
*
* PARAMETERS:
*      INPUT:
*           char    *fname       Nombre del archivo que contiene el 
*                                diccionario
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
void dict_load(char *fname) {
/* completar aca */
    char **tmp = NULL;
    int c = 0,    // Caracter de cada palabra leida.
        i = 0,    // Indice de arreglo de diccionario principal.
        j = 0;    // Indice de lectura de caracteres de palabras.
    char word[MAX_WORD_SIZE];    // Palabra leida del diccionario principal.
    FILE *ficher = fopen(fname,"r");    // Abrir archivo de diccionario principal.
    if (ficher != NULL) {
        dict_main = (char **)calloc(main_size, sizeof(char *));
        if (dict_main != NULL) {
            while (feof(ficher) == 0) {    // No llego al EOF.
                if (i < main_size) {    // No llego al tamaño inicial del diccionario principal.
                    for (j=0; (c=fgetc(ficher))!='\n' && c!='\r' && c!=EOF; j++) {    // Toma un caracter del archivo, que sea distinto de \n, \r o EOF.
                        if (j<MAX_WORD_SIZE && isalpha(c)) {    // La palabra es menor al tamaño maximo y es alfabetica.
                            word[j] = c;
                        } else {    // La palabra es mayor al tamaño maximo, o no es alfabetico.
                            printf("Error: El diccionario posee palabras mayores al tamaño maximo permitido.\n");
                            exit(1);   // Salida forzosa del programa por ingresar un diccionario no valido.
                        }
                    }
                    word[j] = '\0';    // Agrega fin de string.
                    if (feof(ficher) == 0) {    // No llego al EOF.
                        dict_main[i] = calloc(MAX_WORD_SIZE, sizeof(char));
                        if (dict_main[i] != NULL) {
                            strcpy(dict_main[i], word);    // Copia palabra del archivo al diccionario principal.
                            i++;
                        } else {
                            printf("Error de memoria.\n");
                            exit(1);   // Salida forzosa del programa.
                        }
                    } else {    // Llego al EOF.
                        break;
                    }
                } else {    // Llego al tamaño inicial del diccionario principal. Asigna mas memoria.
                    main_size = main_size*10;
                    tmp = (char **)realloc(dict_main, main_size*sizeof(char *));
                    if (tmp != NULL) {
                        dict_main = tmp;
                        tmp = NULL;
                    } else {
                        printf("Error de memoria.\n");
                        exit(1);   // Salida forzosa del programa.
                    }
                }
            }
            main_size = i;   // Actualiza tamaño del diccionario principal.
            if (main_size != 0) {
                tmp = (char **)realloc(dict_main, main_size*sizeof(char *));    // Establece tamaño real del diccionario principal en memoria.
                if (tmp != NULL) {
                    dict_main = tmp;
                    tmp = NULL;
                } else {
                    printf("Error de memoria.\n");
                    exit(1);   // Salida forzosa del programa.
                }
            }
        } else {
            printf("Error de memoria.\n");
            exit(1);   // Salida forzosa del programa.
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
* NAME :            void dict_save(char *fname)
*
* DESCRIPTION :     Guarda el diccionario principal en el archivo 
*                   fname
*
* PARAMETERS:
*      INPUT:
*           char    *fname       Nombre del archivo donde se guardara
*                                el diccionario
* RETURN :
*           Type: void
*******************************************************************/
void dict_save(char *fname) {
/* completar aca  */
    char new_line = '\n';
    int i = 0;
    FILE *ficher = fopen(fname,"w");
    if (ficher != NULL) {
        while (main_size != i) {    // El diccionario no esta vacio.
            fputs(dict_main[i], ficher);    // Coloca palabra del diccionario en el archivo.
            putc(new_line, ficher);     // Coloca \n en el archivo.
            i++;
        }
        if (fclose(ficher) != 0) {
            printf("Error al cerrar el archivo.\n");
            exit(1);   // Salida forzosa del programa.
        }
        while (main_size != 0) {    // Libera memoria.
            main_size--;
            free(dict_main[main_size]);
        }
        free(dict_main);
    } else {
        printf("Error al abrir el archivo.\n");
        exit(1);   // Salida forzosa del programa.
    }
}

/*******************************************************************
* NAME :            void dict_add(char *word)
*
* DESCRIPTION :     Agrega una palabra al diccionario principal.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a ser agregada.
*
* RETURN :
*           Type: void
*
* OBSERVATIONS :
*    1) Recordar que la lista que representa el diccionario no tiene 
*       lugar "de sobra".
*******************************************************************/
void dict_add(char *word) {
/* completar aca */
    char **tmp = NULL;
    tmp = (char **)realloc(dict_main, (main_size+1)*sizeof(char *));    // Actualiza el tamaño.
    if (tmp != NULL) {
        dict_main = tmp;
        tmp = NULL;
    } else {
        printf("Error de memoria.\n");
        exit(1);   // Salida forzosa del programa.
    }
    dict_main[main_size] = calloc(MAX_WORD_SIZE, sizeof(char));    // Otorga memoria para palabra.
    if (dict_main[main_size] != NULL) {
        strcpy(dict_main[main_size], word);    // Copia nueva palabra.
        main_size++;
    } else {
        printf("Error de memoria.\n");
        exit(1);   // Salida forzosa del programa.
    }
}

/*******************************************************************
* NAME :            void ignored_add(char *word)
*
* DESCRIPTION :     Agrega una palabra al diccionario de palabras 
*                   ignoradas.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a ser agregada.

* RETURN :
*           Type: void
* OBSERVATIONS :
*    1) La lista que representa el diccionario de palabras ignoradas 
*       debe agrandarse a medida que se agregan palabras.
*******************************************************************/
void ignored_add(char *word) {
/* completar aca  */
    char **tmp = NULL;
    if (ignored_size == 0) {    // No hay palabras ignoradas.
        tmp = calloc(ignored_size+1, sizeof(char *));    // Otorga memoria.
        if (tmp != NULL) {
            dict_ignored = tmp;
            tmp = NULL;
        } else {
            printf("Error de memoria.\n");
            exit(1);   // Salida forzosa del programa.
        }
    } else {    // Hay palabras ignoradas.
        tmp = (char **)realloc(dict_ignored, (ignored_size+1)*sizeof(char *));    // Actualiza tamaño.
        if (tmp != NULL) {
            dict_ignored = tmp;
            tmp = NULL;
        } else {
            printf("Error de memoria.\n");
            exit(1);   // Salida forzosa del programa.
        }
    }
    dict_ignored[ignored_size] = calloc(MAX_WORD_SIZE, sizeof(char));    //  Otorga memoria para palabra.
    if (dict_ignored[ignored_size] != NULL) {
        strcpy(dict_ignored[ignored_size], word);    // Copia nueva palabra.
        ignored_size++;
    } else {
        printf("Error de memoria.\n");
        exit(1);   // Salida forzosa del programa.
    }
}

/*******************************************************************
* NAME :            int is_known(char *word)
*
* DESCRIPTION :     Verifica si una palabra es "conocida", ya sea 
*                   porque esta en el diccionario principal o en el 
*                   diccionario de palabras ignoradas. 
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a verificar.
*
* RETURN :
*           Type: int
*           Values: 1 si la palabra es conocida
*                   0 si la palabra no es conocida
*******************************************************************/
int is_known(char *word) {
/* completar aca  */
    int result = 0;
    int i = 0;     // Indice de palabras recorridas.
    while (i != main_size) {    // No llego a su tamaño.
        if (strcmp(dict_main[i], word) == 0) {    // Las palabras son iguales.
            result = 1;
            break;
        }
        i++;
    }
    if (result == 0 && ignored_size != 0) {    // No es una palabra conocida en el diccionario principal. Verifico en el diccionario de palabras ignoradas.
        i = 0;
        while (i != ignored_size) {    // No llego a su tamaño.
            if (strcmp(dict_ignored[i], word) == 0) {    // Las palabras son iguales.
                result = 1;
                break;
            }
            i++;
        }
    }
    return (result);
}

/*******************************************************************
* NAME :            int get_word(char *w)
*
* DESCRIPTION :     Lee una palabra del archivo de entrada, copiando 
*                   todo caracter de puntuacion precedente al archivo
*                   de salida.
* PARAMETERS:
*      OUTPUT:
*           char    *word       Palabra que se lee desde el archivo.
*
* RETURN :
*           Type: int
*           Values: 0 si no hay mas palabras para leer.  
*                   1 si hay mas palabras para leer.
*******************************************************************/
int get_word(char *word) {
/* completar aca */
    int character = 0,    // Caracter leido del documento.
        i = 0,    // Indice de word.
        flag = 0;     // Bandera de que se leyo un caracter alfabetico.
    while (feof(doc_in) == 0) {    // No llego al EOF.
        character = fgetc(doc_in);    // Toma un caracter.
        if (!isalpha(character)) {    // No es un caracter alfabetico.
            if (feof(doc_in) == 0) {    // No llego al EOF.
                if (flag == 0) {    // No se leyo antes un caracter alfabetico.    
                    putc(character, doc_out);    // Guarda en el archivo de salida el caracter precedente a la palabra.
                } else {    // Se leyo antes un caracter alfabetico.
                    word[i] = '\0';
                    fseek(doc_in,-1,SEEK_CUR);    // Se apunta al caracter no alfabetico para guardarlo despues.
                    return 1;    // Hay mas palabras para leer.
                }
            } else {    // Llego al EOF.
                return 0;    // No hay mas palabras para leer.
            }
        } else {    // Es un caracter alfabetico.
            if (i < MAX_WORD_SIZE) {
                word[i] = character;
                i++;
                flag = 1;    // Se leyo un caracter alfabetico.
            } else {
                printf("Error: El documento posee palabras mayores al tamaño maximo permitido.\n");
                exit(1);   // Salida forzosa del programa por ingresar un documento no valido.
            }
        }
    }
    return 0;    // No hay mas palabras para leer.
}

/*******************************************************************
* NAME :            void put_word(char *word)
*
* DESCRIPTION :     Escribe la palabra w al archivo de salida.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a escribir.
*
* RETURN :
*           Type: void
*******************************************************************/
void put_word(char *word) {
/* completar aca  */
    fputs(word, doc_out);
}

/*******************************************************************
* NAME :            void consult_user(char *word)
*
* DESCRIPTION :     Consulta al usuario sobre que accion realizar 
*                   (aceptar, ignorar o reemplazar) con la palabra w.
*                   Una vez que el usuario elige, realiza la accion 
*                   elegida.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra sobre la cual se consulta la 
*                            accion a realizar.
*
* RETURN :
*           Type: void
*******************************************************************/
void consult_user(char *word) {
    char ans[2];
    do {
        printf("Palabra no reconocida: %s\n Aceptar (a) - Ignorar (i) - Reemplazar (r): ", word);
        scanf("%s", ans);
    } while ((strcmp(ans,"r") != 0) && (strcmp(ans,"a") != 0) && (strcmp(ans,"i") != 0));
/* completar aca  */
    char new_word[MAX_WORD_SIZE];    // Variable para almacenar una palabra nueva.
    int flag = 0,    // Bandera de error.
        i = 0,       // Indice.
        lgd = 0;    // Longitud de una palabra.
    char c;    // Caracter de cada palabra.
    switch(ans[0]) {   // Opcion elegida.
        case 'a':                          // Agregar a diccionario principal.
                    dict_add(word);
                    break;
        case 'i':                         // Agrega a diccionario de palabras ignoradas.
                    ignored_add(word);
                    break;
        case 'r':                         // Reemplaza palabra desconocida.
                    getchar();    // Saca \n.
                    while (flag == 0) {    // No se ingreso una palabra valida.
                        printf("Ingrese una nueva palabra:");
                        while ((c = getchar()) != '\n') {    // Toma caracter por caracter de la nueva palabra.
                            if (i < MAX_WORD_SIZE) {    // Tamaño maximo de palabra.
                                new_word[i] = (char)c;    // Agrega caracter.
                                i++;
                            } else {
                                new_word[0] = '\0';    // Excedio el tamaño maximo.
                            }
                        }
                        if (new_word[0] != '\0') {    // No excedio tamaño maximo.
                            new_word[i] = '\0';    // Agrega fin de string.
                            lgd = i;
                            for (i=0; i < lgd; i++) {    // Verifica que sean caracteres alfabeticos.
                                if (isalpha(new_word[i])) {
                                    flag = 1;    // Palabra valida.
                                } else {    // Palabra no valida.
                                    printf("ERROR: Palabra no valida.\n");
                                    flag = 0;
                                    new_word[0] = '\0';
                                    i = 0;
                                    break;
                                }
                            }
                        } else {     // Palabra no valida.
                            printf("ERROR: Palabra no valida.\n");
                            i = 0;
                        }
                    }
                    strcpy(word, new_word);    // Copia la nueva palabra.
                    break;
    }
}

/*******************************************************************
* NAME :            void process_document(char *fname)
*
* DESCRIPTION :     Procesa el documento fname, palabra por palabra, 
*                   consultando al usuario sobre la accion a realizar 
*                   si la palabra no es conocida.
* PARAMETERS:
*      INPUT:
*           char    *fname   Nombre del archivo a procesar.
*
* RETURN :
*           Type: void
*******************************************************************/
void process_document(char *fname) {
    char current_word[MAX_WORD_SIZE];
/* completar aca */
    doc_in = fopen(fname,"r");    // Abrir documento de entrada.
    doc_out = fopen("out.txt","w");    // Abrir documento de salida.
    if (doc_in != NULL && doc_out != NULL) {
        while (get_word(current_word) == 1) {   // Lee una palabra del documento de entrada, y establece si hay mas palabras para leer.
            if (is_known(current_word) == 0) {    // Es una palabra desconocida?
                consult_user(current_word);    // Tratamiento de palabra desconocida.
            }
            put_word(current_word);    // Agrega palabra a documento de salida.
        }
        if (ignored_size != 0) {
            while (ignored_size != 0) {
                ignored_size--;
                free(dict_ignored[ignored_size]);
            }
            free(dict_ignored);
        }
        if (fclose(doc_in) != 0){    // Cierra documento de entrada.
            printf("Error al cerrar el archivo.\n");
            exit(1);   // Salida forzosa del programa.
        }
        if (fclose(doc_out) != 0){    // Cierra documento de salida.
            printf("Error al cerrar el archivo.\n");
            exit(1);   // Salida forzosa del programa.
        }
    } else {
        printf("Error al abrir el archivo.\n");
        exit(1);   // Salida forzosa del programa.
    }
}

/*******************************************************************
* NAME :            int main(int argc, char **argv)
*
* DESCRIPTION :     Punto de entrada principal. Abre el diccionario 
*                   principal, procesa el archivo especificado y 
*                   guarda los cambios realizados en el diccionario 
*                   principal.
*******************************************************************/
int main(int argc, char **argv) {
    char *dict;
    /* Verificamos el nro de argumentos. */
    if (argc <= 2) {
        printf("spellchecker.c: nro de argumentos erroneo. Deben ser <documento> [<diccionario>].\n");
        return (1);
    }
    /* si se especifico un diccionario lo usamos,  */
    /* caso contrario usamos el diccionario por defecto */
    dict = (argc >=3) ? argv[2] : "dict.txt";
/* completar aca */
    dict_load(argv[2]);    // Se carga el diccionario principal.
    process_document(argv[1]);    // Se procesa el documento.
    dict_save(argv[2]);    // Se guarda el diccionario principal.
    printf("El documento %s ha sido procesado. Resultados en out.txt\n", argv[1]);
}
