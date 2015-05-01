{-# LANGUAGE DoAndIfThenElse #-}

module Dictionary (Dictionary,
                   dict_new,
                   dict_add,
                   dict_contains,
                   dict_load,
                   dict_save
        )
where

import System.IO

type Word = String

-- Estructura del diccionario
data Dictionary = Dictionary [Word] deriving Show

-- Crea un nuevo diccionario vacio
dict_new :: Dictionary
dict_new = Dictionary []

-- Agrega una palabra al diccionario especificado
dict_add :: Word -> Dictionary -> Dictionary
dict_add w (Dictionary xs) = Dictionary ([w] ++ xs)

-- Verifica la existencia de una palabra en el diccionario especificado
dict_contains :: Word -> Dictionary -> Bool
dict_contains w (Dictionary []) = False
dict_contains w (Dictionary (x:xs)) |w==x = True
                                    |otherwise = dict_contains w (Dictionary xs)

-- Carga un diccionario desde un archivo especificado
dict_load :: FilePath -> IO Dictionary
dict_load fname =
    let
        file2String :: FilePath -> IO String    -- Carga el Diccionario principal
        file2String filename = do
                handle <- openFile filename ReadMode
                hGetContents handle

        {-alpha_char :: [String] -> Bool    -- La palabra posse caracteres especiales
        alpha_char [] = True
        alpha_char [[]] = True
        alpha_char ([]:xss) = alpha_char xss
        alpha_char ((x:xs):xss) |(isAlpha x) == False = False
                                |otherwise = alpha_char (xs:xss)

        max_word :: [Word] -> Bool    -- La palabra no cumple con el maximo permitido
        max_word [] = True
        max_word (x:xs) |(length x) > 30 = False
                        |otherwise  = max_word xs-}

        subsecs :: Ord a => (a -> Bool) -> [a] -> [[a]]    -- Sub-secuencias
        subsecs f [] = [[]]
        subsecs f (x:xs) |f x = (x:ps):pss
                         |otherwise = []:ps:pss
                where
                    ps:pss = subsecs f xs

        line :: String -> [Word]    -- Lista las lineas del diccionario
        line [] = []
        line (x:xs) = subsecs (/='\n') (x:xs)

        dictFromString :: [Word] -> Dictionary
        dictFromString list = 
            foldr f dict_new list
                where
                    f w dict = dict_add w dict

    in
        do
            str <- file2String fname            
            return(dictFromString (line str))
            {-isOK <- ((max_word list) && (alpha_char list))
            if isOK 
            then return (dictFromString list)
            else return (Dictionary (-1) [])-}

-- Guarda el diccionario en el archivo especificado.
dict_save :: FilePath -> Dictionary -> IO ()
dict_save fname (Dictionary xs) =
    let
        intercal :: a -> [[a]] -> [a]
        intercal x [] = []
        intercal x [ys] = ys
        intercal x (ys:yss) = ys ++ (x: intercal x yss)
  
        defsToString :: [Word] -> String
        defsToString list = intercal '\n' list

    in
        do
            handle <- openFile fname WriteMode
            hPutStr handle (defsToString xs)
            hClose handle
