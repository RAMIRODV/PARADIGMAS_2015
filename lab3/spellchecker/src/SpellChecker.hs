{-# LANGUAGE DoAndIfThenElse #-}

module SpellChecker (do_spellcheck) where

import CommandLine
import Dictionary
import Document

-- La funcion 'do_spellcheck' es la funcion que se encarga de manejar
-- el proceso de chequeo ortografico. Esto incluye, cargar el diccionario,
-- abrir el archivo a procesar, procesar el archivo y luego guardar el
-- diccionario y el archivo de entrada ya procesado.
-- Toma como argumento los argumentos de linea de comando de tipo 'Params'.
do_spellcheck :: Params -> IO ()
do_spellcheck filename dictionary = do
                dict <- dict_load dictionary
                doc <- doc_open filename "out.txt"
                dictToSave <- process_document doc dict dict_new
                dict_save filename dictToSave
                doc_close doc
        
-- La funcion 'process_document' ejecuta el proceso de chequeo ortografico.
-- Para ello, procesa el archivo palabra por palabra, copiandolas al archivo
-- de salida y consultando al usuario sobre que accion realizar ante una
-- palabra desconocida.
-- Cuando se termina de procesar el archivo, lo cual es señalizado mediante
-- una excepcion por 'doc_get_word', retorna el diccionario (el cual puede
-- haber sido modificado) para guardarlo.
process_document :: Document -> Dictionary -> Dictionary -> IO Dictionary
process_document (Document docIn docOut) (Dictionary n xs) (Dictionary i ys) =
                do
                    --excepcion VER!!!

-- Verifica si una palabra es conocida, en cuyo caso, continua
-- con el procesamiento del archivo, sin realizar ninguna accion.
-- Si la palabra no es conocida, pregunta al usuario que accion
-- realizar con la misma. Las acciones pueden ser aceptar, ignorar
-- o reemplazar.
consult_user ::  Word -> Dictionary -> Dictionary -> IO (Word, Dictionary, Dictionary)
consult_user word dicPrincipal dicIgnorados =
    let
        {------------------------------------------------------------------
            Funcion: Verifica si la palabra existe ya sea en el diccionario
            del usuario o en el diccionario de palabras ignoradas.

            Input: Word, Dictionary
            return: Bool
        ------------------------------------------------------------------}
        existe w dic dicIgn = do
            a <- dic_contains w dic
            b <- dic_contains w dicIgn
            return (a || b)

        {------------------------------------------------------------------
            Funcion: Reemplaza la palabra y devuelve la palabra reemplazada

            Input: Word
            return: Word
        ------------------------------------------------------------------}
        reemplazar w = do
            putStr "Reemplazar por: "
            r <- getLine
            return r
        
        -- Interaccion con el usuario
        preguntar = do
            putStr "\nLa palabra no existe que desea hacer? (a=aceptar, i=ignorar, r=reemplazar)"
            c <- getChar
            if c == 'a' || c == 'A'
                then do return (toLower c)
                else if  c == 'i' || c == 'I'
                    then do return (toLower c)
                    else if c == 'r' || c == 'R'
                        then do return (toLower c)
                        else preguntar
    in
        do
            e <- existe word dicPrincipal dicIgnorados
            if not e then do
                opc <- preguntar
                if opc == 'a'
                    then do dicMod <- dodict_add word dicPrincipal
                            return (word, dicMod, dicIgnorados)
                    else if opc == 'i'
                        then do dicMod <- dict_add word dicIgnorados
                            return (word, dicPrincipal, dicMod)
                        else if opc == 'r'
                            then do palabra <- reemplazar word
                                    consult_user palabra dicPrincipal dicIgnorados
