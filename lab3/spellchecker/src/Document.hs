{-# LANGUAGE DoAndIfThenElse #-}

module Document (Document,
                 doc_open,
                 doc_close,
                 doc_get_word,
                 doc_put_word,
        )
where

import System.IO
import Data.Char

type Word = String
type DocIN = Handle
type DocOut = Handle

-- Estructura del documento
data Document = Document DocIN DocOut deriving Show

-- Abre los archivos especificados por los paths
-- pasados como argumentos. El primer path repre-
-- senta el archivo de entrada a procesar, y el
-- segundo path representa el archivo de salida
-- donde se guarda el documento ya procesado.
doc_open :: FilePath -> FilePath -> IO Document
doc_open fnameIn fnameOut = do
                docIn <- openFile fnameIn ReadMode
                docOut <- openFile fnameOut WriteMode
                return (Document docIn docOut)

-- Cierra los archivos especificados
doc_close :: Document -> IO ()
doc_close (Document docIn docOut) = do
                hClose docIn
                hClose docOut

-- Obtiene una palabra del documento especificado,
-- copiando todos los caracteres no alfabeticos
-- precedentes al archivo de salida.
-- Cuando alcanza el final del documento, lo señaliza
-- con una excepcion.
doc_get_word :: Document -> IO Word
doc_get_word document =
    let
        extract :: Word -> Document -> IO Word
        extract word (Document docIn docOut) = do
                character <- hGetChar docIn
                if isAlpha(character)
                    then do extract (word++[character]) (Document docIn docOut)
                    else if (length word) == 0
                            then do hPutChar docOut character
                                    extract word (Document docIn docOut)
                            else do hSeek docIn RelativeSeek (-1)
                                    return(word)

    in
        do
            currentWord <- (extract "" document)
            return(currentWord)

-- Escribe una palabra en el documento de salida.
doc_put_word :: Word -> Document -> IO ()
doc_put_word w (Document docIn docOut) = do
                    hPutStr docOut w
                    return ()
