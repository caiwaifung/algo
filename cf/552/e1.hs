import Data.Char

type Pair = (Integer, Integer)

splitEvenOdd :: [a] -> ([a], [a])
splitEvenOdd = foldr f ([], []) where f v (xs, ys) = (ys, v:xs)

main = getLine >>= putStrLn . show . solve . splitEvenOdd

solve :: (String, String) -> Integer
solve (os, vs) = go (1, 0) os xs where
    xs = map (toInteger . digitToInt) vs

go :: Pair -> [Char] -> [Integer] -> Integer
go (u, v) [] (x:xs) = u * x + v
go (u, v) (o:os) (x:xs) = max ans1 ans2 where
    cur' = if o == '+' then (1, u * x + v) else (u * x, v)
    ans1 = go cur' os xs
    ans2 = go' (u, v) (o:os) (x:xs) 

go' l os (x:xs) = snd $ go'' l (x, 0) os xs

cal (lu, lv) (cu, cv) (ru, rv) = lv + lu * (cu + cv) * ru + rv

go'' :: Pair -> Pair -> [Char] -> [Integer] -> (Pair, Integer)
go'' l c [] []  = ((1, 0), cal l c (1, 0))
go'' l (u, v) (o:os) (x:xs) = (pair', ans') where
    cur' = if o == '+' then (x, u + v) else (u * x, v)
    (pair, ans) = go'' l cur' os xs
    r = if o == '+' then (1, fst pair * x + snd pair) else (fst pair * x, snd pair)
    ans' = max ans (cal l (u, v) r)
    pair' = r
--    (x * r + s) * u + v
--    + trace ((show $ (x * r + s)) ++ " " ++ (show (u,v)) ++ " " ++ (show os) ++ " " ++ (show (x:xs))) 0
--    where (r, s) = foldr (flip calc) (1, 0) (zip os xs)
--    
--
--
--
