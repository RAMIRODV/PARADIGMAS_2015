#!/bin/bash

FILE_DOC_IN=$1    # Documento de entrada.
FILE_DICT_MAIN=$2    # Diccionario principal.
FILE_DICT_OUT=""    # Diccionario de salida.
FILE_OUT="out.txt"    # Documento de salida.
dict_ignored=""    #Diccionario de palabras ignoradas.
word=""    # Palabra a procesar.
file_out=""    # Buffer de documento de salida.

process_document() {
    flag=0    # Si leyo un caracter alfabetico.
    while IFS= read -r -N 1 -u9 character    # Lee un caracter del documento.
    do
        if [[ $character = [a-zA-Z] ]]    # Es alfabetico?
        then
            word+=$character
            flag=1    # Leyo un caracter alfabetico.
        else    # No es alfabetico.
            if (($flag == 1))    # Leyo un caracter alfabetico antes.
            then
                is_know_dict=$(grep -ci $word $FILE_DICT_OUT)    # Es una palabra conocida en el diccionario principal?
                is_know_ignored=$(grep -ci $word $dict_ignored)    # Es una palabra conocida en el diccionario de palabras ignoradas?
                let is_know=is_know_dict+is_know_ignored
                if (( $is_know == 0))    # Palabra desconocida.
                then
                    while true;
                    do
                        echo "Palabra no reconocida: $word";
                        echo "Aceptar (a) - Ignorar (i) - Reemplazar (r): ";
                        read -p "Ingrese opcion: " op;
                        if [ "$op" == 'a' ]
                        then
                            echo $word >> $FILE_DICT_OUT    # La agrega al diccionario principal.
                            break
                        elif [ "$op" == 'i' ]
                        then
                            echo $word >> $dict_ignored    # La agrega al diccionario de palabras ignoradas.
                            break
                        elif [ "$op" == 'r' ]
                        then
                            read -p "Ingrese una nueva palabra: " res;
                            word=$res    # Reemplaza la palabra.
                            break
                        else
                            echo "ERROR: Opción Invalida.";
                        fi
                    done
                fi
                file_out+=$word    # La agrega al buffer del documento de salida.
                word=""
                flag=0
            fi
            if [[ "$character" == $'\n' ]];
            then
                file_out+="\n"
            elif [[ "$character" == $' ' ]];
            then
                file_out+=" "
            else
                file_out+=$character
            fi
        fi
    done 9< "${FILE_DOC_IN}"
}

main() {
    if (( $# < 1 )); then    # Analiza la cantidad de argumentos.
        echo "spellchecker.sh: nro de argumentos erroneo. Deben ser <documento> [<diccionario>]."
        exit
    elif (( $# == 1 )); then
        FILE_DICT_OUT="dict.txt"
        touch $FILE_DICT_OUT
    else
        FILE_DICT_OUT=$2
    fi
    dict_ignored="dict_ignored.txt"    # Crea el diccionario de palabras ignoradas.
    touch $dict_ignored
    FILE_DOC_IN=$1
    process_document    # Procesa el documento.
    touch $FILE_OUT
    rm $FILE_OUT
    printf "$file_out" >> $FILE_OUT    # Copia el contenido del buffer al documento de salida.
    rm $dict_ignored    # Elimina el diccionario de palabras ignoradas.
    echo "El documento '$FILE_DOC_IN' ha sido procesado. Resultados en out.txt"
}

main $FILE_DOC_IN $FILE_DICT_MAIN    # Ejecuta el script.
