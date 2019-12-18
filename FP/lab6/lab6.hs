import System.IO
import System.Environment
import Data.List
 
stringToInt :: String -> Int
stringToInt x = (read x) :: Int
 
task1 = do
	putStrLn "Enter first number:"
	a <- getLine
	putStrLn "Enter secound number:"
	b <- getLine
	putStrLn $ "a+b=" ++ (show ( (stringToInt a) + (stringToInt b)) )