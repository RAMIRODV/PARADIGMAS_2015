{- En este test vamos a probar que el lenguaje de programacion Haskell es
 - de tipado estatico.
 - Para ello vamos a ver como haskell verifica en tiempo de compilacion los
 - tipos de las "varialbes" y nos muestra error de tipo.
 -}
x :: Int
x = 0

y :: Char
y = x

z :: Int
z = y
    
main = print z
