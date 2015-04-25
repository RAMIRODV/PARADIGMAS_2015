-- |
module Dictionary where


--| Crea un nuevo diccionario vacio
dict_new :: Dictionary

--| Agrega una palabra al diccionario especificado
dict_add :: Word -> Dictionary -> Dictionary

--| Verifica la existencia de una palabra en el
-- diccionario especificado
dict_contains :: Word -> Dictionary -> Bool

--| Carga un diccionario desde un archivo especificado.
dict_load :: FilePath -> IO Dictionary

--| Guarda el diccionario en el archivo especificado.
dict_save :: FilePath -> Dictionary -> IO ()





