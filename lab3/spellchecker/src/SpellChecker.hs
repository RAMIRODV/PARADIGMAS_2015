{-# LANGUAGE DoAndIfThenElse #-}

module SpellChecker (do_spellcheck) where

import CommandLine
import Dictionary
import Document
import System.IO.Error

type Word = String

-- La funcion 'do_spellcheck' es la funcion que se encarga de manejar
-- el proceso de chequeo ortografico. Esto incluye, cargar el diccionario,
-- abrir el archivo a procesar, procesar el archivo y luego guardar el
-- diccionario y el archivo de entrada ya procesado.
-- Toma como argumento los argumentos de linea de comando de tipo 'Params'.
do_spellcheck :: Params -> IO ()
do_spellcheck (Params filenameIn dictionaryMain) =
    do
        dict <- dict_load dictionaryMain
        doc <- doc_open filenameIn "out.txt"
        dictToSave <- (process_document doc dict dict_new)
        dict_save dictionaryMain dictToSave
        doc_close doc
        putStr "El documento "
        putStr filenameIn
        putStr " ha sido procesado. Resultados en out.txt\n"
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
            currentWord <- (doc_get_word document)
            if ((dict_contains currentWord dictMain) || (dict_contains currentWord dictIgnored))
                then do doc_put_word currentWord document
                        dictMain' <- (process_document document dictMain dictIgnored)
                        return(dictMain')
                else do (word, dictMainM, dictIgnoredM) <- (consult_user currentWord dictMain dictIgnored)
                        doc_put_word word document
                        dictMain' <- (process_document document dictMainM dictIgnoredM)
                        return(dictMain')
        `catch`
        \e -> if isEOFError e then return(dictMain)
                else ioError e

-- Verifica si una palabra es conocida, en cuyo caso, continua
-- con el procesamiento del archivo, sin realizar ninguna accion.
-- Si la palabra no es conocida, pregunta al usuario que accion
-- realizar con la misma. Las acciones pueden ser aceptar, ignorar
-- o reemplazar.
consult_user ::  Word -> Dictionary -> Dictionary -> IO (Word, Dictionary, Dictionary)
consult_user wordUnknown dicMain dicIgnored =
    let
        replace :: IO Word
        replace = do
            putStrLn "Ingrese una nueva palabra: "
            newWord <- getLine
            return(newWord)

        ask :: Word -> IO Char
        ask word = do
            putStr "Palabra no reconocida: " 
            putStr word
            putChar '\n'
            putStrLn "Aceptar (a) - Ignorar (i) - Reemplazar (r): "
            c <- getChar
            putChar '\n'
            _ <- getLine
            case c of
                'a' -> return(c)
                'i' -> return(c)
                'r' -> return(c)
                _   -> ask word

    in
        do
            option <- ask wordUnknown
            case option of
                'a' -> return(wordUnknown, dict_add wordUnknown dicMain, dicIgnored)
                'i' -> return(wordUnknown, dicMain, dict_add wordUnknown dicIgnored)
                'r' -> do newWord <- replace
                          return(newWord, dicMain, dicIgnored)
                _   -> consult_user wordUnknown dicMain dicIgnored
