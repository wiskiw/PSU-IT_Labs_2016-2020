import Data.List (nub)
 
data Prop = And Prop Prop 
			| Or Prop Prop 
			| Not Prop 
			| Var String deriving Show 
 
vars :: Prop -> [String]
vars = nub . go where 
    go (And a b) = concat [go a, go b] 
    go (Or a b)  = concat [go a, go b]
    go (Not a)   = go a
    go (Var s)   = [s]
 
unsafeLookup :: Eq a => a -> [(a, b)] -> b
unsafeLookup x t = case lookup x t of Just x -> x
 
truthValue :: [(String, Bool)] -> Prop -> Bool
truthValue table = go where
    go (And a b) = go a && go b
    go (Or a b)  = go a || go b
    go (Not a)   = not (go a)
    go (Var a)   = unsafeLookup a table
 
gen :: [a] -> [b] -> [[(a, b)]]
gen []     _  = [[]]
gen (x:xs) ys = concat[(p:) `map` gen xs ys | p <- [(x, y) | y <- ys]]
 
tautology :: Prop -> Bool
tautology prop = all (flip truthValue prop) $ gen (vars prop) [True, False]