import System.IO

x = "dinamico"

main =
    do
        putStrLn x
        putStrLn (g x)
        putStrLn x

                
g :: String -> String
g x = "estatico"
            
