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
		t :: Char,
		name :: String,
		date :: Date
	}
	| Contact {
		t :: Char,
		name :: String,
		number :: Int
	}
	| Event {
		t :: Char,
		name :: String,
		date :: Date
	}
	deriving (Eq, Show)		

 -- Стандартныe конструкторы
dDob :: String -> Date -> Record
dDob mName mDate = Dob {t = dobType, name = mName, date = mDate}
dobType = 'b'

dContact :: String -> Int -> Record
dContact mName mNumber = Contact {t = contactType, name = mName, number = mNumber}
contactType = 'c'

dEvent :: String -> Date -> Record
dEvent mName mDate = Event {t = eventType, name = mName, date = mDate}
eventType = 'e'
{----------- ---------- -----------}

-- возвращает имя из записи
-- использование:
-- getName Contact {t = "c", name = "Abc", number = 123}
getName :: Record -> String
getName record = name record

-- возвращает тип записи
getType :: Record -> Char
getType record = t record

-- возвращает дату из записи
getDate :: Record -> Date
getDate record = date record


-- Спискок записей
myList = [
			dContact "Vano" 123, 
			dContact "Penka" 223,
			dDob "Vano" Dm { d = 18, m = 9 },
			dEvent "Vano" Dmy { d = 1, m = 12, y = 2016 }
		]

-- ЗАДАНИЕ 1
getByName :: String -> [Record]
getByName name = searchByName name myList
-- > getByName "Vano"

{-
 Поиск записией по имени
	Параметры: 
		name :: String - Имя для которого ищим записи
		records :: [Record] - Список записей
		
	Возвращает:
		Список записей с именем name
		Если таких нет - пустой список
-}
searchByName :: String -> [Record] -> [Record]
searchByName name records = _searchByName name records []
_searchByName _ [] resultList = resultList 
_searchByName name (firstRecord:restRecords) resultList = 
	if getName firstRecord == name 
		then _searchByName name restRecords (firstRecord:resultList)
		else _searchByName name restRecords resultList
		
		
		
-- ЗАДАНИЕ 2	
getByLetter :: Char -> [Record]
getByLetter letter = searchByLetter letter myList
-- > getByLetter 'V'

{-
 Поиск записей по первому символу их имени
	Параметры: 
		letter :: Char - первый символ имени для поиска
		records :: [Record] - Список записей
		
	Возвращает:
		Массив записей, имя у которых начинается с letter (без учета регистра)
		Если таких нет - пустой список
-}	
searchByLetter :: Char -> [Record] -> [Record]
searchByLetter letter records = _searchByLetter letter records []
_searchByLetter _ [] resultList = resultList 
_searchByLetter letter (firstRecord:restRecords) resultList = 
	let firstLetter = head (getName firstRecord) 
	in if toUpper firstLetter == toUpper letter 
		then _searchByLetter letter restRecords (firstRecord:resultList)
		else _searchByLetter letter restRecords resultList
		
		
-- ЗАДАНИЕ 3	
getAssignment :: Date -> [Record]
getAssignment date = searchByDate date myList
-- > getAssignment Dm {d = 3, m = 4}
-- > getAssignment Dm {d = 18, m = 9}	
	
	
{-
 Поиск записей по по дате (только по )
	Параметры: 
		date :: Date - дата для поиска
		records :: [Record] - Список записей
		
	Возвращает:
		Массив записей(Dob и Event только), дата которых совпадает с Date
		Если таких нет - пустой список
-}
searchByDate :: Date -> [Record] -> [Record]
searchByDate date records = _searchByDate date records []
_searchByDate _ [] resultList = resultList 
_searchByDate date (firstRecord:restRecords) resultList = 
	if getType firstRecord /= contactType && getDate firstRecord == date 
		then _searchByDate date restRecords (firstRecord:resultList)
		else _searchByDate date restRecords resultList