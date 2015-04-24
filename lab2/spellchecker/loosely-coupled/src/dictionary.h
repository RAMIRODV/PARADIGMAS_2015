#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Dict *Dictionary;

/* Crea un diccionario vacío. */
Dictionary dict_new (void);

/* Carga el diccionario. */
void dict_load (Dictionary dic, char *fname, int max_word);

/* Guarda el diccionario. */
void dict_save (Dictionary dic, char *fname);

/* Agrega una palabra al diccionario. */
void dict_add (Dictionary dic, char *word, int max_word);

/* Pregunta si la palabra está en el diccionario. */
int dict_contains (Dictionary dic, char *word);

/* Destructor del diccionario. */
Dictionary dict_destroy (Dictionary dic);

#endif
