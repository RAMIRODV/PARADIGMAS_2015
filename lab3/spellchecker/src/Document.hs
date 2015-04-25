
{-# LANGUAGE DoAndIfThenElse #-}
-- |

module Document where

type Word = String

data Document = 

--| Abre los archivos especificados por los paths
-- pasados como argumentos. El primer path repre-
-- senta el archivo de entrada a procesar, y el
-- segundo path representa el archivo de salida
-- donde se guarda el documento ya procesado.
doc_open :: FilePath -> FilePath -> IO Document

--| Cierra los archivos especificados
doc_close :: Document -> IO ()

--| Obtiene una palabra del documento especificado,
-- copiando todos los caracteres no alfabeticos
-- precedentes al archivo de salida.
-- Cuando alcanza el final del documento, lo señaliza
-- con una excepcion.
doc_get_word :: Document -> IO Word

--| Escribe una palabra en el documento de salida.
doc_put_word :: Word -> Document -> IO ()
