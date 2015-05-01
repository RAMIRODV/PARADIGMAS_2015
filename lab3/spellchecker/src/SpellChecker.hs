{-# LANGUAGE DoAndIfThenElse #-}

module SpellChecker (do_spellcheck) where

import CommandLine
import Dictionary
import Document
--import Control.Exception
import System.IO

type Word = String

-- La funcion 'do_spellcheck' es la funcion que se encarga de manejar
-- el proceso de chequeo ortografico. Esto incluye, cargar el diccionario,
-- abrir el archivo a procesar, procesar el archivo y luego guardar el
-- diccionario y el archivo de entrada ya procesado.
-- Toma como argumento los argumentos de linea de comando de tipo 'Params'.
do_spellcheck :: Params -> IO ()
do_spellcheck (Params filename dictionary) =
    do
        dict <- dict_load dictionary
        doc <- doc_open filename "out.txt"
        dictToSave <- (process_document doc dict dict_new)
        dict_save filename dictToSave
        doc_close doc
        return()

-- La funcion 'process_document' ejecuta el proceso de chequeo ortografico.
-- Para ello, procesa el archivo palabra por palabra, copiandolas al archivo
-- de salida y consultando al usuario sobre que accion realizar ante una
-- palabra desconocida.
-- Cuando se termina de procesar el archivo, lo cual es señalizado mediante
-- una excepcion por 'doc_get_word', retorna el diccionario (el cual puede
-- haber sido modificado) para guardarlo.
process_document :: Document -> Dictionary -> Dictionary -> IO Dictionary
process_document document dictMain dictIgnored =
    do
    --catch (
        do
            currentWord <- (doc_get_word document)
            inMain <- (dict_contains currentWord dictMain)
            inIgnored <- (dict_contains currentWord dictIgnored)
            if (inMain || inIgnored)
                then do doc_put_word currentWord document
                        dictMain <- (process_document document dictMain dictIgnored)
                        return(dictMain)
                else do (word, dictMain, dictIgnored) <- (consult_user currentWord dictMain dictIgnored)
                        doc_put_word currentWord document
                        dictMain <- (process_document document dictMain dictIgnored)
                        return(dictMain)
            --) handleException
        --where
            --handleException :: SomeException -> IO ()
            --handleException _   = do
                                    --return(dictMain)
        `catch`
        \e -> if isEOFError e then return(dicMain)

-- Verifica si una palabra es conocida, en cuyo caso, continua
-- con el procesamiento del archivo, sin realizar ninguna accion.
-- Si la palabra no es conocida, pregunta al usuario que accion
-- realizar con la misma. Las acciones pueden ser aceptar, ignorar
-- o reemplazar.
consult_user ::  Word -> Dictionary -> Dictionary -> IO (Word, Dictionary, Dictionary)
consult_user word dicMain dicIgnored =
    let
        reemplazar :: Word -> Word
        reemplazar w = do
            putStr "Reemplazar por: "
            r <- getLine
            return(r)

        preguntar :: Char
        preguntar = do
            putStr "\nLa palabra no existe que desea hacer? (a=aceptar, i=ignorar, r=reemplazar)"
            c <- getChar
            case c of
                'a' -> return(c)
                'i' -> return(c)
                'r' -> return(c)
                _   -> preguntar

    in
        do
            option <- preguntar
            case option of
                'a' -> return(word, dict_add word dicMain, dicIgnored)
                'i' -> return(word, dicMain, dict_add word dicIgnored)
                'r' -> do newWord <- reemplazar word
                          return(newWord, dicMain, dicIgnored)
