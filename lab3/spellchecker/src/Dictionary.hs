-- |
module Dictionary where

type Word = String
data Dictionary = Palabra Word (Dictionary) | Empty deriving Show

-- | Crea un nuevo diccionario vacio
dict_new :: Dictionary
dict_empty = Empty

-- | Agrega una palabra al diccionario especificado
dict_add :: Word -> Dictionary -> Dictionary
dict_add w Empty = Palabra w Empty
dict_add w (Palabra a d) = Palabra w (dict_add a d)

-- | Verifica la existencia de una palabra en el
-- diccionario especificado
dict_contains :: Word -> Dictionary -> Bool
dict_contains w Empty = False
dict_contains w (Palabra a d)   | (w == a) = True
                                | otherwise = dict_contains w d

-- | Carga un diccionario desde un archivo especificado.
dict_load :: FilePath -> IO Dictionary
dict_load f =
    let
        file2String :: FilePath -> IO String
        file2String f =
            do  handle <- openFile f ReadMode
                hGetContents handle -- no carga todo en memoria,
                                    -- es lazy,
                                    -- el archivo se cierra solo,

    {-
        Lleva a una lista de strings un string separando por el predicado
        Ej: Si el predicado es (/='\n') y el string
        "Hola\ncomo\n\nestas\n"
        ->
        ["Hola", "como", "", "estas", ""]
    -}
        subsecs :: (a -> Bool) -> [a] -> [[a]]
        subsecs p = foldr f [[]]
            where
                f x (ps:pss) | p x       = (x:ps):pss
                             | not (p x) = []:ps:pss

    {-  
        Limpio los "" de la lista de strings
        ["Hola", "como", "", "estas", ""]
        ->
        ["Hola", "como", "estas"]
    -}
        lineas :: String -> [String]
        lineas str = filter (/=[]) (subsecs (/='\n') str)

    {-
        Hace el proceso de un string a un diccionaio.
        Ej:
        "Hola\ncomo\n\nestas\n"
        ->
        Palabra "estas" (Palabra "como" (Palabra "Hola"))
    -}
        dictFromString :: String -> Dictionary
        dictFromString str = 
            foldr f dict_empty (lineas str)
                where
                    f k di = dict_add k di
    in
        do
            str <- file2String f
            return (dictFromString str)

-- | Guarda el diccionario en el archivo especificado.
dict_save :: FilePath -> Dictionary -> IO ()
dict_save f d =
    let
        intercal :: a -> [[a]] -> [a]
        intercal x [] = []
        intercal x [ys] = ys
        intercal x (ys:yss) = ys ++ (x: intercal x yss)
      
        LsWToString :: [Word] -> String
        LsWToString ls = intercal '\n' ls

        dict_toLsW :: Diccionario -> [Word]
        dict_toLsW Empty = []
        dict_toLsW (Palabra w d) = w : (dict_toLsW d)
    in
        do
            handle <- openFile f WriteMode
            hPutStr handle (LsWToString (dict_toLsW d))
            hClose handle
