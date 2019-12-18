{-
	foldr (a -> b -> b) -> b -> [a]    -> b
	It takes the second argument and the last item of the list and applies the function, 
		then it takes the penultimate item from the end and the result, and so on.
			> foldr (+) 1 [1,2]
			> 4
			> 4 = (1+(2+1))

	Обобщением этой функции является функция высшего порядка
			> sumList xs ys = zipWith (+) xs ys
			
-}

-- Функция вычисления арифметического среднего элементов списка вещественных чисел с использованием функции foldr. 
-- Функция должна осуществлять только один проход по списку.
-- fromIntegral - конвертирует Int в Double
average :: [Double] -> Double
average x = (foldr (\a b -> a+b) 0.0 x) / (fromIntegral (length x))
-- average [4.22, 1.22, 1.23, 1.0]


-- 2) Функция, вычисляющая скалярное произведение двух списков (используйте функции foldr и zipWith).
-- https://ru.wikipedia.org/wiki/%D0%A1%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D0%BE%D0%B5_%D0%BF%D1%80%D0%BE%D0%B8%D0%B7%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5#%D0%90%D0%BB%D0%B3%D0%B5%D0%B1%D1%80%D0%B0%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5_%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5
scalProd :: [Double] -> [Double] -> Double
scalProd x y =  foldr (\a b -> a+b) 0.0 (zipWith (\a b-> a*b) x y)
-- scalProd [1.22, 1.23, 1.0] [1.22, 1.23, 1.0]


-- Функция countEven, возвращающая количество четных элементов в списке
countEven :: [Int] -> Int
countEven l = length (filter even l)
-- countEven[1,2,3,4,5,6]


{-
	Функция quicksort, осуществляющая быструю сортировку
	списка по следующему рекурсивному алгоритму. Для того, чтобы отсортировать список xs, из него выбирается 
	первый элемент (обозначим его x). Остальной список делится на две части: список, состоящий из элементов xs, 
		меньших x и список элементов, 
		больших x. 
	Эти списки сортируются (здесь проявляется рекурсия, поскольку они сортируются этим же алгоритмов), а затем из них составляется результирующий
	список вида as ++ [x] ++ bs, где as и bs — отсортированные списки меньших и больших элементов соответственно.
-}

{-
 Класс Ord позволяет сравнивать элементы > < = >= <= 
 Наследуется от класса Eq
-}
quickSort :: Ord a => [a] -> [a]
quickSort []     = []
quickSort (x:xs) = quickSort (filter (\a -> a<x) xs) ++ [x] ++ quickSort (filter (\a -> a>=x) xs)
-- quickSort [1,221,31,41]


{-
Определенная в предыдущем пункте функция quicksort сортирует список в порядке возрастания. Обобщите ее: пусть
она принимает еще один аргумент — функцию сравнения типа a -> a -> Bool и сортирует список в соответствие с нею.

-}
quickSort2 :: (a -> a -> Bool) -> [a] -> [a]
quickSort2 fun []     = []
quickSort2 fun (x:xs) = quickSort2 fun (filter (fun x) xs) ++ [x] ++ (quickSort2 fun (filter (\a -> not(fun x a)) xs))
-- quickSort2 (\a b -> a > b) [1,23,4234,10]

