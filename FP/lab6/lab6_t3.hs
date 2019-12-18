{-

	Программа, которая принимает в командной строке имя файла и распечатывает его на экране
	./lab6_t3 "readme.txt"
-}

import System.IO
import System.Environment

main = do
       (fnam:etc) <- getArgs
       handle <- openFile fnam ReadMode
       contf <- hGetContents handle
       putStr contf
       hClose handle