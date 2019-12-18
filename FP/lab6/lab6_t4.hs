{-

	Программа, принимающая в командной строке число n и имя файла и выводящая на экран первые n строк файла 
	./lab6_t4 2 "readme.txt"
-}


import System.IO
import System.Environment
 
main = do
       (ns:fnam:etc) <- getArgs
       handle <- openFile fnam ReadMode
       contf <- hGetContents handle
       mapM (putStrLn (take (read ns) (lines contf)))
       hClose handle