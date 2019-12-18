-- Task 1(1)
t21 :: Integer -> [Integer]
t21 n = [1..n]

-- Task 1(7)
{-
t1=1
t2=2+t1(1)=3
t3=3+t2(3)=6
...
-}
nTringle :: Integer -> Integer
nTringle 1 = 1
nTringle x = nTringle(x-1) + x

t22::Integer->[Integer]
t22 0 = []
t22 n = t22(n-1) ++ [nTringle(n)]


-- Task 2(9)
makePos :: [Integer] -> [Integer]
makePos [] = []
makePos (i:tl) = [if(i >= 0) then i else (i*(-1))] ++ makePos(tl)

-- Task 2(5)
-- 2^n
pow :: Integer -> Integer 
pow 0 = 1
pow n = 2 * pow (n-1)

twopow :: Integer -> Integer 
twopow 0 = 1
twopow x = if(even x) then pow(2 * (div x 2)) else 2 * pow(2 * (div (x-1) 2))


-- ADDITIONAL
addTask :: [Integer] -> [Integer]
addTask [] = []
addTask (i:tl) = [
					if(even i) 
					then i*(-1) 
					else 
						if	(i > 0) 
						then (i*5)
						else (i*(-1)+5)
				] ++ addTask(tl)




