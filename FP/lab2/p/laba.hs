sp::Integer->[Integer]
sp 0 = []
sp n = sp(n-1) ++ [n*n]

sp2::Integer->[Integer]
sp2 0 = []
sp2 n = sp2(n-1) ++ [2^n]

substitute :: Char -> Char -> String -> String
substitute x y [] = []
substitute x y (h:t) = if(h == x) then [y] ++ sub-stitute x y t 
else [h] ++ substitute x y t

pow :: Integer -> Integer 
pow 0 = 1
pow n = 2 * pow (n-1)

twopow :: Integer -> Integer 
twopow 0 = 1
twopow x = if(even x == True) then pow(div x 2) * pow(div x 2)
else 2 * pow(div (x-1) 2) * pow(div (x-1) 2)

func :: Char -> Char -> String -> String
func x y [] = []
func x y (h:t) = if(h == x) then [] ++ func x y t
else if (h == y) then [h,h] ++ func x y t
else [h] ++ func x y t


