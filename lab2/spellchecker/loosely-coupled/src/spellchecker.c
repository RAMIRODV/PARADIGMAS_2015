#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include "document.h"

/* tamaño maximo de una palabra */
#define MAX_WORD_SIZE 30

/* diccionario principal */
Dictionary main_dict;
/* diccionario de palabras ignoradas */
Dictionary ignored;
/* Documento a procesar */
Document doc;


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
    result = dict_contains(main_dict, word);    // Consulta si esta en el diccionario principal.
    if (result == 0 && ignored != NULL) {
        result = dict_contains(ignored, word);    // Consulta si esta en el diccionario de palabras ignoradas.
    }
    return (result);
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
    switch(ans[0]) {    // Opcion elegida.
        case 'a':                             // Agrega a diccionario principal.
                    dict_add(main_dict, word, MAX_WORD_SIZE);
                    break;
        case 'i':                            // Agrega a diccionario de palabras ignoradas.
                    if (ignored == NULL) {
                        ignored = dict_new();
                    }
                    dict_add(ignored, word, MAX_WORD_SIZE);
                    break;
        case 'r':
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
    ignored = NULL;
    doc = doc_open(fname, "out.txt");    // Abre documento de entrada y salida.
    while (doc_get_word(doc, current_word, MAX_WORD_SIZE) == 1) {    // Lee una palabra del documento de entrada, y establece si hay mas palabras par leer.
        if (is_known(current_word) == 0) {    // Es una palabra desconocida?
            consult_user(current_word);    // Tratamiento de palabra desconocida.
        }
        doc_put_word(doc, current_word);    // Agrega una palabra al documento de salida.
    }
    doc = doc_close(doc);    // Cierra el documento de entrada y de salida.
    if (ignored != NULL) {    // Si el diccionario de palabras ignoradas se creo.
        ignored = dict_destroy(ignored);    // Se destruye.
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
    main_dict = dict_new();    // Se crea un diccionario principal.
    dict_load(main_dict, argv[2], MAX_WORD_SIZE);    // Se carga el diccionario principal.
    process_document(argv[1]);    // Se procesa el documento.
    dict_save(main_dict, argv[2]);    // Se guarda el diccionario principal.
    main_dict = dict_destroy(main_dict);    // Se destruye el diccionario principal.
    printf("El documento %s ha sido procesado. Resultados en out.txt\n", argv[1]);
}
