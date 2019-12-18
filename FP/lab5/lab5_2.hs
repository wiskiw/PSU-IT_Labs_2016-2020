{-
	ВАРИАНТ 8
	
 ЗАДАНИЕ 1
	getByName, возвращающая информацию о человекес указанным именем (его телефон и дату рождения).

 ЗАДАНИЕ 2
 	getByLetter, возвращающая список людей, о которых есть 
	информация в записной книжке и чье имя начинается на указанную букву.


 ЗАДАНИЕ 3
	getAssignment, возвращающая по указанной дате список дел
	(информация о назначенных встречах и телефоны друзей, 
	которых нужно поздравить в этот день).
-}

import Data.Char


{----------- Структуры -----------}
data Date = 
		Dm {
			d :: Int,
			m :: Int
		}
		| Dmy {
			d :: Int,
			m :: Int,
			y :: Int
		}
	deriving (Eq, Show)	
				
data Record =
	-- Date of birth 
	Dob {
		name :: String,
		date :: Date
	}
	| Contact {
		name :: String,
		number :: Int
	}
	| Event {
		name :: String,
		date :: Date
	}
	deriving (Eq, Show)		

getDay (Dm d m) = d
getDay (Dmy d m y) = d

isDob(Dob _ _) = True
isDob(_) = False

isContact(Contact _ _) = True
isContact(_) = False

isEvent(Event _ _) = True
isEvent(_) = False


getPhone(Contact _ p) = p
getPhone(_) = -1


-- возвращает имя из записи
getName :: Record -> String
getName record = name record

-- возвращает дату из записи
getDate :: Record -> Date
getDate record = date record

-- Спискок записей
myList = [
			Contact "Vano1" 123, 
			Contact "Penka" 223,
			Dob "Vano2" Dm { d = 18, m = 9 },
			Event "Vano3" Dmy { d = 1, m = 12, y = 2016 }
		]



-- ЗАДАНИЕ 1
getByName :: String -> [Record]
getByName name = searchByName2 name myList
-- > getByName "Vano"

searchByName2 :: String -> [Record] -> [Record]
searchByName2 name records = filter (\a -> (getName a) == name) records  	
		
		
-- ЗАДАНИЕ 2	
getByLetter :: Char -> [Record]
getByLetter letter = searchByLetter2 letter myList
-- > 	

searchByLetter2 :: Char -> [Record] -> [Record]
searchByLetter2 letter records = filter (\a -> toUpper (head (getName a)) == toUpper letter) records  	

a :: [Record] -> [Int]
a l = concatMap (\a -> [(getPhone a) + 70000, (getPhone a) +3750000]) l 
-- a [Contact "Vano1" 1230, Contact "Penka" 2232]

-- ЗАДАНИЕ 3	
getAssignment :: Date -> [Record]
getAssignment date = searchByDate2 date myList
-- > getAssignment Dm {d = 3, m = 4}
-- > getAssignment Dm {d = 18, m = 9}	
	
searchByDate2 :: Date -> [Record] -> [Record]
searchByDate2 date records = filter (\a -> (not (isContact a) && (getDate a)==date)) records  	