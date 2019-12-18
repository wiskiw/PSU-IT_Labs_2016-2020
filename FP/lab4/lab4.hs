
{-
	8. 	Иерархия должностей в некоторой организации образует древовид-
	ную структуру. Каждый работник, однозначно характеризующийся
	уникальным именем, имеет несколько подчиненных. Определите
	тип данных, представляющий такую иерархию и опишите следую-
	щие функции:
		1) getSubordinate, возвращающую список подчиненных ука-
	занного работника.
		2) getAllSubordinate, возвращающую список всех подчинен-
	ных данного работника, включая косвенных.
		3) getBoss, возвращающую начальника указанного работника.
		4) getList, возвращающую список пар, первым элементом ко-
	торых является имя работника, а вторым — количество его
	подчиненных (включая косвенных).

-}


{-
	foldr (a -> b -> b) -> b -> [a]    -> b
	It takes the second argument and the last item of the list and applies the function, 
		then it takes the penultimate item from the end and the result, and so on.
			> foldr (+) 1 [1,2]
			> 4

		
	It is used for function composition - for example if you wrote a function:
			> myFunc x = func1 (func2 x)
		you can re-write this to:
			> myFunc = func1 . func2
			
			
	concatMap (a -> [b]) -> [a] ->     [b]
	Creates a list from a list generating function by application of this function on all elements in a list passed as the second argument
			> concatMap (\x -> [(x,x+2,x/2)]) [1,3,5]
			> [(1.0,3.0,0.5),(3.0,5.0,1.5),(5.0,7.0,2.5)]
			
			> concatMap (enumFromTo 1) [1,3,5]
			> [1,1,2,3,1,2,3,4,5]
-}

data Stuff = 
	Stuff { 
		name :: String, 
		sub ::  [Stuff] 
	} deriving (Eq, Show)

hier = Stuff "Ival"[
				Stuff "Alexandr" [
					Stuff "Don" [
							Stuff "Egor" []
						],
				
					Stuff "Don2" []
					],
				Stuff "Jhon" []
            ]
			
hierList = [hier, Stuff "Don" [
					Stuff "Egor" [], 
					Stuff "Egor2" []
				]
			] 

-- ЗАДАНИЕ 1
-- Возвращает список подчиненных указанного работника
getSubordinates :: Stuff -> String -> [Stuff]
getSubordinates hs name1 = innerF hs
  where innerF x  
          | name x /= name1 = 
		  		foldr ((++) . innerF) [] (sub x) -- *
					-- ((++) . innerF) - function    =>    fun X = ++ (innerF X)
					-- [] - start list
					-- x - list of subs
          | otherwise = sub x
-- getSubordinates hier "Dons"


-- ЗАДАНИЕ 2
-- Возвращает список всех подчиненных данного работника, включая косвенных
getAllSubordinates :: Stuff -> String -> [Stuff]
getAllSubordinates hs = innerF . (getSubordinates hs)
  where innerF = concatMap (\x -> x : innerF (sub x)) -- *
-- getAllSubordinates hier
 
 
-- ЗАДАНИЕ 3
-- Возвращает начальника указанного работника.
getBoss :: Stuff -> String -> [Stuff]
getBoss hs name1 = innerF [] hs
  where innerF s x 
          | name x /= name1 = foldr ((++) . innerF [x]) [] (sub x)    
		  			-- ((++) . innerF) - function    =>    fun X = ++ (innerF [X])
					-- [] - start list
					-- x - list of subs
          | otherwise = s   
-- getBoss hier "Dons"	 
		  
 
-- ЗАДАНИЕ 4
-- Возвращающую список пар, первым элементом которых является имя работника, а вторым — количество его подчиненных (включая косвенных).
getList :: Stuff -> [(String, Int)]
getList hs = (name hs, length innerF) : innerF
  where innerF = concatMap getList (sub hs)
-- getList hier


-- найти сотрудника с максимальным число рабочих
getBigBoss :: [Stuff] -> Stuff -> Stuff
getBigBoss list prevStuff = if (length (sub (head list)) >= length (sub prevStuff)) then
									-- новый max
									innerF (head list)
								else 
									-- старый max
									innerF prevStuff
								where innerF newMaxStuff  = 
									if	(length (tail list) > 0) then 
											-- есть еще
											getBigBoss (tail list) newMaxStuff
										else newMaxStuff
-- getBigBoss sub hier (Stuff "" [])

 