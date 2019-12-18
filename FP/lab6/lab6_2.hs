import System.IO
import System.Environment
import Data.List
 
stringToBool :: String -> Bool
stringToBool x = (read x) :: Bool
 
bothTrue :: Bool -> Bool -> Bool
bothTrue a b = if (a) then (if(b) then True else False) else False 
 
task2 = do
	putStrLn "First bool:"
	a <- getLine
	putStrLn "Second bool:"
	b <- getLine
	putStrLn $ "both true: " ++ (show ( bothTrue (stringToBool a) (stringToBool b)) )


{-

	Main> task2
	First bool:
	True 
	Second bool:
	True
	both true: True

-}