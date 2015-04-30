{-# LANGUAGE DoAndIfThenElse #-}

module Document (Document,
                 doc_open,
                 doc_close,
                 doc_get_word,
                 doc_put_word,
        ) 
where

import IO
import Data.Char
import Data.Bool
import Hugs.IOExts (unsafePerformIO)

type Word = String

-- Estructura del documento
data Document = Document Handle Handle deriving Show

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
                return ()

-- Obtiene una palabra del documento especificado,
-- copiando todos los caracteres no alfabeticos
-- precedentes al archivo de salida.
-- Cuando alcanza el final del documento, lo señaliza
-- con una excepcion.
doc_get_word :: Document -> IO Word
doc_get_word (Document docIn docOut) =
    let
    -- hgetchar
    -- hseek
        {-------------------------------------------------------------
            fun lee una palabra.
            input: Entrada, Salida (de tipo Handle)
            return: String
           
            Nota: Cuando lee el ultimo char lo manda a salida.
            Es decir, al leer "Hola como estas", lee "hola" y
            el puntero queda en el ' ' lo cual lo llevo a salida.
        -------------------------------------------------------------}
        palabra h sal = do 
            s <- hIsEOF h
            if s then return [] else do 
                c <- hGetChar h
                if isAlpha c then do
                    r <- palabra h sal
                    return (c:r)
                    else do
                            hPutChar sal c
                            return []

        {-------------------------------------------------------------
            fun lee un String
            Input: Entrada, Salida (de tipo Handle)
            return: String

            Nota: A diferencia de fun palabra, este le el string del
            estilo " hola", llevando el ' ' a la salida. Usa palabra
            para obtener "hola".
        -------------------------------------------------------------}
        leerConRaro h sal = do
            e <- hIsEOF h
            if e then return [] else do
                c <- hGetChar h
                if not (isAlpha c) then do -- Es char raro
                    pal <- palabra h sal -- Leo lo que viene despues del raro
                    hPutChar sal c
                    return pal 
                    else do
                        s <- palabra h sal
                        return (c:s)

    in
        do
            xs <- leerConRaro a b
            -- hClose a
            -- hClose b
            return xs

-- Escribe una palabra en el documento de salida.
doc_put_word :: Word -> Document -> IO ()
doc_put_word w (Document docIn docOut) = do
                    hPutStr docOut w
                    return ()
