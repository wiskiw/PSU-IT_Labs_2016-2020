{-|

signum :: Integer -> Integer 
-- signum x = if x > 0
-- then 1 else if x < 0 then -1 else 0

-}



-- Var 4
-- :load /home/wiskiw/Storage/uni/lvl2/2/FP/lab1/t1.hs


-- task 1 (кортежи)
-- [ [ [ (Integer,Bool) ] ] ]
-- [[[(42, True), (3, False), (666, True)]]]
-- snd (head (tail (head  (head [[[(42, True), (3, False)], [(333, True)]]]))))

-- (123, False): (tail (head (head [[[(42, True), (3, False)], [(333, True)]]])))




-- Task 2
bothTrue :: Bool -> Bool -> Bool
bothTrue a b = if (a) then (if(b) then True else False) else False 

threeTrue :: Bool -> Bool -> Bool -> Bool
threeTrue a b c = if (a) then (if(b) then True else (if(c) then True else False)) else (if(b) then (if(c) then True else False) else False)
{-|
 bothTrue True True
 bothTrue True False
 bothTrue False False
 bothTrue False True 
 
 
 threeTrue False True True
 threeTrue False True False
 threeTrue False False False
 
 threeTrue True True True
 threeTrue True True False
 threeTrue True False False
 
 threeTrue True False True
 threeTrue True True True
 threeTrue False True True
 
 
-}
