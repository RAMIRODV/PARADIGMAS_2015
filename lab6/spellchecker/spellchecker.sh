#!/bin/bash

# Parameter to initialize awk script.
FILE_DICT_MAIN=$1
FILE_DOC_IN=$2
FILE_DICT_OUT="$1"
FILE_OUT="out.txt"

E_PARAMERR=85
dict_main=()
dict_ignored=()
file_out=()
current_word=""
word_is_known=false

first_chars=""
last_chars=""

dict_save() {
    printf "%s\n" "${dict_main[@]}" > "${FILE_DICT_OUT}"
}

dict_load() {
    i=0
    while read line
    do
        for word in $line; do
            dict_main[i]=$word
            i=$(($i + 1))
        done
    done < "${FILE_DICT_MAIN}"
}

dict_add() {
    dict_main+=($current_word)
}

is_known() {
    for e in "${dict_main[@]}"
    do
        if [ $e = $current_word ]
        then
            word_is_known=true
            break
        fi
    done
}

get_word() {
    word=""
    for c in "$current_word"
    do
        if [[ $c = [a-zA-Z] ]]
        then
            word=$word$s
        else
            file_out+=("$c")
        fi
    done
    current_word=$word
}

put_word() {
    file_out+=$current_word
}

consult_user() {
    echo -n "Aceptar(a) - Reemplazar(r) - Ignorar(i): "
    read op
    case $op in
        [aA] )
            dict_add
            ;;
        [rR] )
            echo -n "Reemplazar por: "
            read res
            current_word=$res
            ;;
        [iI] )
            dict_ignored+=("$current_word")
            ;;
        *)
            echo "Invalid input"
            current_word
            ;;
    esac
}

process_doc() {
    :
}

usage() {
    echo "Usage: spellchecker.sh <dict-file> <doc-file>" 2>&1
    # For example:   ./spellchecker.sh dict.txt doc.txt
    exit $E_PARAMERR  # Too few arguments passed to script.
}

# Verifica si se pasan bien los argumentos.
if [ ! -f "$1" ] || [ ! -f "$2" ]
then
    usage   # Print usage message and exit.
fi

# dict_load
# current_word="hola"
# is_known
# if [ "$word_is_known" = false ]
# then
#     dict_add
#     dict_save
# fi
VALOR='G'

if [[ $VALOR = [a-zA-Z] ]]
then
    echo "$VALOR"
fi
exit $?

# Por las dudas
#    for e in "${dict_main[@]}"
#    do
#        echo "$e"
#    done
