{-

	Программа, распечатывающая переданные в нее аргументы командной строки.

-}

import System.IO

main = do
       args <- getArgs
       mapM (putStrLn args)