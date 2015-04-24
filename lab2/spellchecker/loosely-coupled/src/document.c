#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "document.h"

struct Doc {    // Estructura del documento.
    FILE *doc_in;
    FILE *doc_out;
};

/*******************************************************************
* NAME :            Document doc_open (char *fname_in, char *fname_out)
*
* DESCRIPTION :     Abre los archivos de entrada y de salida,
*                   colocandolos en la estructura documento
* PARAMETERS:
*      INPUT:
*           char *fname_in      Archivo de entrada
*           char *fname_out     Archivo de salida
*
* RETURN :
*           Type: Document
*******************************************************************/
Document doc_open (char *fname_in, char *fname_out) {
    Document doc = NULL;
    doc = calloc (1, sizeof (struct Doc));
    if (doc != NULL) {
        doc->doc_in = fopen(fname_in,"r");    // Abrir documento de entrada.
        doc->doc_out = fopen(fname_out,"w");    // Abrir documento de salida.
    }
    if (doc->doc_in != NULL && doc->doc_out != NULL) {
        return doc;
    } else {
        printf("Error al abrir el archivo.\n");
        exit(1);   // Salida forzosa del programa.
    }
}

/*******************************************************************
* NAME :            int doc_get_word (Document doc, char *word, int max_word)
*
* DESCRIPTION :     Lee una palabra del archivo de entrada, copiando 
*                   todo caracter de puntuacion precedente al archivo
*                   de salida.
* PARAMETERS:
*      INPUT:
*           Document doc       Estructura que contiene a los documentos
*           int max_word         Tamaño maximo de una palabra
*      OUTPUT:
*           char    *word       Palabra que se lee desde el archivo.
*
* RETURN :
*           Type: int
*           Values: 0 si no hay mas palabras para leer.  
*                   1 si hay mas palabras para leer.
*******************************************************************/
int doc_get_word (Document doc, char *word, int max_word) {
    int character = 0,    // Caracter leido del documento.
        i = 0,    // Indice.
        flag = 0;    // Bandera de que se leyo un caracter alfabetico.
    while (feof(doc->doc_in) == 0) {    // No llego al EOF.
        character = fgetc(doc->doc_in);    // Toma un caracter.
        if (!isalpha(character)) {    // No es un caracter alfabetico.
            if (feof(doc->doc_in) == 0) {    // No llego al EOF.
                if (flag == 0) {   // No se leyo antes un caracter alfabetico.
                    putc(character, doc->doc_out);    // Guarda en el archivo de salida el caracter precedente a la palabra.
                } else {    // Se leyo antes un caracter alfabetico.
                    word[i] = '\0';
                    fseek(doc->doc_in,-1,SEEK_CUR);    // Se apunta al caracter no alfabetico para guardarlo despues.
                    return 1;    // Hay mas palabras para leer.
                }
            } else {    // Llego al EOF.
                return 0;    // No hay mas palabras para leer.
            }
        } else {    // Es un caracter alfabetico.
            if (i < max_word){
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
* NAME :            void doc_put_word(Document doc, char *word)
*
* DESCRIPTION :     Escribe la palabra word al archivo de salida.
*
* PARAMETERS:
*      INPUT:
*           Document doc       Estructura que contiene a los documentos
*           char    *word       Palabra a escribir.
*
* RETURN :
*           Type: void
*******************************************************************/
void doc_put_word(Document doc, char *word) {
    fputs(word, doc->doc_out);    // Guarda una palabra en el documento de salida.
}

/*******************************************************************
* NAME :            Document doc_close(Document doc)
*
* DESCRIPTION :     Cierra los archivos de entrada y de salida
*
* PARAMETERS:
*      INPUT:
*           Document doc       Estructura que contiene a los documentos
*
* RETURN :
*           Type: Document
*******************************************************************/
Document doc_close(Document doc) {
    if (fclose(doc->doc_in) != 0){    // Cierra documento de entrada.
        printf("Error al cerrar el archivo.\n");
        exit(1);   // Salida forzosa del programa.
    }
    if (fclose(doc->doc_out) != 0){    // Cierra documento de salida.
        printf("Error al cerrar el archivo.\n");
        exit(1);   // Salida forzosa del programa.
    }
    free(doc);    // Libera memoria.
    doc = NULL;
    return doc;
}
