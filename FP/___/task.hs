data Transport =
	Car {
		weight :: Int,
		price :: Double,
		capacity :: Int,
		consumption :: Double
	} |
	Train {
		wagNumb :: Int,
		typ :: Char,
		capacity :: Int
	} |
	Plain {
		flyDistance :: Int,
		speed :: Int,
		capacity :: Int,
		owner :: String
	} |
	Ship {
		capacity :: Int,
		displacement :: Int, -- водоизмещение
		distance :: Int,
		typ :: Char
	} |
	Airship { -- Дирижабль
		size :: Int, -- Объем
		carryingCapacity :: Int, -- Грузоподъемность
		distance :: Int,
		createDate :: Int
	}
	deriving (Eq, Show)	
	
	
isCar (Car _ _ _ _) = True 	
isCar (_) = False

isTrain (Train _ _ _) = True 	
isTrain (_) = False

isPlain (Plain _ _ _ _) = True 	
isPlain (_) = False

isShip (Ship _ _ _ _) = True 	
isShip (_) = False

isAirship (Airship _ _ _ _) = True 	
isAirship (_) = False


-- Вместимость транспорта
getCapacity :: Transport -> Int
getCapacity t 
	| (isCar t) || (isTrain t) || (isShip t) || (isPlain t) = capacity t
	| otherwise = -1
-- getCapacity (Plain 12 12 123 "Hello")
-- getCapacity (Car 12 12.3 4 12.2)


-- Скорость
getSpeed :: Transport -> Int 
getSpeed t 
	| isPlain t = speed t
	| otherwise = -1
	
getCreateDate :: Transport -> Int 
getCreateDate t 
	| isAirship t = createDate t
	| otherwise = -1

-- Транспорт с максимальной вместимостью
getMaxCapacity :: [Transport] -> Transport
getMaxCapacity tList 
	| length tList == 0 = error "List cannot be empty" 
	| otherwise = _getMaxCapacity tList (head tList) 
_getMaxCapacity tList tMax 
	| (length tList) == 0 = tMax
	| otherwise = if(getCapacity (head tList) > getCapacity tMax) 
		then (_getMaxCapacity (tail tList) (head tList)) 
		else (_getMaxCapacity (tail tList) tMax)
		
-- getMaxCapacity [(Plain 12 12 123 "Hello"), (Plain 12 12 1232 "Plain 2")]

-- вывести дерижабль созданый в определенный промежуток времени
-- getAirshipDate
getAirshipsByDate :: [Transport] -> Int -> Int -> [Transport]
getAirshipsByDate tList sDate eDate = _getAirshipDate tList sDate eDate []
	
-- список -> дата С -> дата По -> Список найденных -> результат 
_getAirshipDate :: [Transport] -> Int -> Int -> [Transport] -> [Transport]
_getAirshipDate (t:tl) sDate eDate resL
						| isAirship t = if ((getCreateDate t) >= sDate && (getCreateDate t) <= eDate) then continue (resL++[t]) else continue resL
						| otherwise = continue resL
					where continue l = if (length tl == 0) then l else _getAirshipDate tl sDate eDate l
-- getAirshipsByDate [(Airship 12 12 123 12000), (Airship 12 12 1232 20000)] 10000 15000

{-
Airship { -- Дирижабль
		size :: Int, -- Объем
		carryingCapacity :: Int, -- Грузоподъемность
		distance :: Int,
		createDate :: Int
	}
-}



