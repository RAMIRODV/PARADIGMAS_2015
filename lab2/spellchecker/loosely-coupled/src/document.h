#ifndef DOCUMENT_H
#define DOCUMENT_H

typedef struct Doc *Document;

/* Abre los documentos de entrada y salida. */
Document doc_open (char *fname_in, char *fname_out);

/* Lee una palabra del documento de entrada. */
int doc_get_word (Document doc, char *word, int max_word);

/* Escribe una palabra en el documento de salida. */
void doc_put_word (Document doc, char *word);

/* Cierra los documentos. */
Document doc_close (Document doc);

#endif
