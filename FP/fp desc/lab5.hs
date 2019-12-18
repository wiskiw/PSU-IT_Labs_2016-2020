--Быстрая сортировка:
qSort :: Ord a => [a] -> [a]
qSort []     = []
qSort (x:xs) = qSort (filter (< x) xs) ++ [x] ++ qSort (filter (>= x) xs)


--Обобщенная qSort:
qSort' :: (a -> a -> Bool) -> [a] -> [a]
qSort' fc []     = []
qSort' fc (x:xs) = qSort' fc (filter (fc x) xs) ++ [x] ++ (qSort' fc (filter (\ y -> not $ fc x y) xs))

